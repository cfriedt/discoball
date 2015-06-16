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

#ifndef DISCOBALL_CONTEXT_H_
#define DISCOBALL_CONTEXT_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "discoball/discoball.h"

/* API Consumers can duplicate data in their own callbacks if required.
 * That way, dynamic allocation and freeing is unnecessary.
 */

typedef struct discoball_client_context {
	discoball_client_cb_t *cb;
} discoball_client_context_t;

typedef struct discoball_server_context {
	discoball_server_cb_t *cb;
} discoball_server_context_t;

typedef struct discoball_peer {
	union {
		struct _discoball_peer_bitwise {
			bool server:1;
			bool noack:1;
			int heartbeat:2; // see packet.h for values
		} bitwise;
		uint32_t raw;
	} flags;
	union {
		discoball_client_context_t client;
		discoball_server_context_t server;
	} view;
	CIRCLEQ_ENTRY( discoball_peer ) entries;
} discoball_peer_t;

static inline discoball_peer_t *discoball_client_to_peer( discoball_client_context_t *cli ) {
	return container_of( cli, discoball_peer_t, view.client );
}
static inline discoball_peer_t *discoball_server_to_peer( discoball_server_context_t *srv ) {
	return container_of( srv, discoball_peer_t, view.server );
}

typedef struct discoball_internal_context {
	union {
		discoball_peer_t peer;
		discoball_context_t opaque;
	} view;
} discoball_internal_context_t;

static inline discoball_internal_context_t *discoball_to_internal( discoball_context_t *ctx ) {
	return container_of( ctx, discoball_internal_context_t, view.opaque );
}

static inline discoball_peer_t *discoball_internal_to_peer( discoball_internal_context_t *ctx ) {
	return &ctx->view.peer;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DISCOBALL_CONTEXT_H_ */
