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

int discoball_common_register( discoball_context_t *ctx, void *cb, bool server ) {

	int r;

	discoball_internal_context_t *ictx;
	discoball_peer_t *peer;
	discoball_peer_t *it;

	if ( NULL == ctx || NULL == cb ) {
		r = -EINVAL;
		goto out;
	}

	discoball_init();

	ictx = discoball_to_internal( ctx );
	peer = discoball_internal_to_peer( ictx );

	DISCOBALL_MUTEX_LOCK( head_mutex );

	CIRCLEQ_FOREACH( it, &head, entries ) {
		if ( peer == it ) {
			r = -EEXIST;
			goto unlock;
		}
	}

	memset( ctx, 0, sizeof( *ctx ) );

	ictx->view.peer.flags.bitwise.server = !!server;

	if ( server ) {
		ictx->view.peer.view.server.cb = (discoball_server_cb_t *) cb;
	} else {
		ictx->view.peer.view.client.cb = (discoball_client_cb_t *) cb;
	}

	CIRCLEQ_INSERT_TAIL( &head, peer, entries );

unlock:
	DISCOBALL_MUTEX_UNLOCK( head_mutex );

	r = 0;

out:
	return r;
}

int discoball_common_deregister( discoball_context_t *ctx, bool server ) {

	int r;

	discoball_internal_context_t *ictx;
	discoball_peer_t *peer;
	discoball_peer_t *it;

	if ( NULL == ctx ) {
		r = -EINVAL;
		goto out;
	}

	discoball_init();

	ictx = discoball_to_internal( ctx );
	peer = discoball_internal_to_peer( ictx );

	DISCOBALL_MUTEX_LOCK( head_mutex );

	r = -ENOENT;
	CIRCLEQ_FOREACH( it, &head, entries ) {
		if ( peer == it && peer->flags.bitwise.server == server ) {
			memset( ctx, 0, sizeof( *ctx ) );
			CIRCLEQ_REMOVE( &head, peer, entries );
			r = 0;
			break;
		}
	}

unlock:
	DISCOBALL_MUTEX_UNLOCK( head_mutex );

out:
	return r;
}
