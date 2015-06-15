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
	void **cbp;

	if ( NULL == ctx || ( true == _register || NULL == cb ) ) {
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
		memset( ctx, 0, sizeof( *ctx ) );
		ictx->view.peer.flags.bitwise.server = !!server;
		cbp = server ? (void **) &ictx->view.peer.view.server.cb : (void **) &ictx->view.peer.view.client.cb;
		*cbp = cb;
		CIRCLEQ_INSERT_TAIL( &head, peer, entries );
	} else {
		r = -ENOENT;
		CIRCLEQ_FOREACH( it, &head, entries ) {
			if ( peer == it && peer->flags.bitwise.server == server ) {
				if ( server ) {
					ictx->view.peer.view.server.cb->cleanup( ctx );
				}
				memset( ctx, 0, sizeof( *ctx ) );
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
