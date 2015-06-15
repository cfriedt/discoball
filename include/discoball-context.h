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
			int heartbeat:2; // 0b00 => disabled, 0b01 => 1s, 0b10 => 10s, 0b11 => 100s
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
