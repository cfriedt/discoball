/*
 * The compilation of software known as DiscoBall is distributed under the
 * following terms:
 *
 * Copyright (c) 2015 Christopher Friedt. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
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

static CIRCLEQ_HEAD( circleq, discoball_peer ) head;
static bool head_initialized;
static DISCOBALL_MUTEX_DECLARE( head_mutex );

static void discoball_init() {
	DISCOBALL_MUTEX_LOCK( head_mutex );
	if ( ! head_initialized ) {
		CIRCLEQ_INIT( &head );
		head_initialized = true;
	}
	DISCOBALL_MUTEX_UNLOCK( head_mutex );
}

/* API Consumers need to register with the library. In doing so,
 * the API Consumer supplies two items:
 *
 *   1) A pre-populated discoball_ops_t (an event listener) structure
 *      containing pertinent callbacks encoded as function pointers, and
 *   2) A pointer to a pre-allocated and uninitialized discoball_context_t.
 *      The size of the discoball_context_t is to be conveyed as a
 *      preprocessor define, so that the API Consumer does not require
 *      dynamic memory allocation facilities. The discoball_context_t is
 *      opaque.
 */

static int _discoball_common_register( discoball_context_t *ctx, void *cb, bool server, bool _register ) {

	int r;

	discoball_internal_context_t *ictx;
	discoball_peer_t *peer;
	discoball_peer_t *it;

	if ( NULL == ctx || ( true == _register && NULL == cb ) ) {
		r = -EINVAL;
		goto out;
	}

	discoball_init();

	ictx = discoball_to_internal( ctx );
	peer = discoball_internal_to_peer( ictx );

	DISCOBALL_MUTEX_LOCK( head_mutex );

	if ( _register ) {
		r = 0;
		CIRCLEQ_FOREACH( it, &head, entries ) {
			if ( peer == it ) {
				r = -EEXIST;
				goto unlock;
			}
		}
		if ( peer->flags.bitwise.server ) {
			peer->view.server.cb = cb;
		} else {
			peer->view.client.cb = cb;
		}
		CIRCLEQ_INSERT_TAIL( &head, peer, entries );
	} else {
		r = -ENOENT;
		CIRCLEQ_FOREACH( it, &head, entries ) {
			if ( peer == it && peer->flags.bitwise.server == server ) {
				CIRCLEQ_REMOVE( &head, peer, entries );
				r = 0;
				goto unlock;
			}
		}
	}

unlock:
	DISCOBALL_MUTEX_UNLOCK( head_mutex );

out:
	return r;
}

int discoball_common_register( discoball_context_t *ctx, void *cb, bool server ) {
	return _discoball_common_register( ctx, cb, server, true );
}

int discoball_common_deregister( discoball_context_t *ctx, bool server ) {
	return _discoball_common_register( ctx, NULL, server, false );
}
