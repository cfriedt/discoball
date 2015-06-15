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

static int server_setup( discoball_internal_context_t *ictx ) {
	return -ENOSYS;
}

int discoball_server_register( discoball_context_t *ctx, discoball_server_cb_t *ccb ) {
	int r;
	r = discoball_common_register( ctx, ccb, a_server );
	if ( r < 0 ) {
		errno = -r;
		E( "discoball_common_register" );
		goto out;
	}

	ictx = discoball_to_internal( ctx );

	r = server_setup( ictx );
	if ( r < 0 ) {
		errno = -r;
		E( "server_setup" );
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
		errno = -r;
		E( "discoball_common_deregister" );
		goto out;
	}

	ictx = discoball_to_internal( ctx );
	if ( NULL != ictx->view.peer.view.server.cb->cleanup ) {
		ictx->view.peer.view.server.cb->cleanup( ctx );
	}
	memset( ctx, 0, sizeof( *ctx ) );

out:
	return r;
}
