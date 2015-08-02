/* The compilation of software known as DiscoBall is distributed under the
 * following terms:
 *
 * Copyright (c) 2015 Christopher Friedt. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "discoball-internal.h"

static const bool a_server = true;

static const discoball_internal_context_t prototype_server_context = {
	.view.peer = {
		.flags.bitwise = {
			.server    = true,
			.noack     = false,
			.heartbeat = DISCOBALL_HEARTBEAT_1s,
		},
	},
};

static int discoball_setup_server( discoball_internal_context_t *ictx ) {
	int r;

	discoball_server_cb_t cb;
	discoball_context_t *ctx;
	ctx = discoball_from_internal( ictx );
	cb = ictx->view.peer.view.server.cb;

	r = 0;

	if ( NULL != cb->init ) {
		r = cb->init( ctx );
		if ( 0 != r ) {
			E( "init callback returned %d", r );
			goto out;
		}
	}

	if ( NULL != cb->start ) {
		r = cb->start( ctx );
		if ( 0 != r ) {
			E( "start callback returned %d", r );
			goto out;
		}
	}

out:
	return r;
}

static int discoball_teardown_server( discoball_internal_context_t *ictx ) {
	int r;

	int r1, r2;

	discoball_server_cb_t cb;
	discoball_context_t *ctx;
	ctx = discoball_from_internal( ictx );
	cb = ictx->view.peer.view.server.cb;

	r = 0;

	if ( NULL != cb->stop ) {
		r = cb->stop( ctx );
		if ( 0 != r ) {
			W( "stop callback returned %d", r );
		}
	}

	if ( NULL != cb->fini ) {
		r = cb->fini( ctx );
		if ( 0 != r ) {
			W( "fini callback returned %d", r );
		}
	}

out:
	return r;
}

int discoball_server_register( discoball_context_t *ctx, discoball_server_cb_t *ccb ) {
	int r;

	discoball_internal_context_t *ictx;

	r = discoball_common_register( ctx, ccb, a_server );
	if ( r < 0 ) {
		E( "discoball_common_register failed (%d)", r );
		goto out;
	}

	ictx = discoball_to_internal( ctx );

	r = discoball_server_setup( ictx );
	if ( r < 0 ) {
		E( "discoball_server_setup failed (%d)", r );
		goto dereg;
	}

	r = 0;
	goto out;

dereg:
	discoball_server_deregister( ctx );

out:
	return r;
}

int discoball_server_deregister( discoball_context_t *ctx ) {
	int r;

	discoball_internal_context_t *ictx;

	r = discoball_common_deregister( ctx, a_server );
	if ( r < 0 ) {
		E( "discoball_common_deregister failed (%d)", r );
		goto out;
	}

	ictx = discoball_to_internal( ctx );

	r = discoball_teardown_server( ictx );
	if ( 0 != r ) {
		W( "discoball_common_deregister failed (%d)", r );
	}

	memset( ctx, 0, sizeof( *ctx ) );

out:
	return r;
}
