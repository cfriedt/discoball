#include "discoball-internal.h"

static CIRCLEQ_HEAD( circleq, entry ) head;

int discoball_init() {
	CIRCLEQ_INIT( &head );
}

int discoball_common_register( discoball_context_t *ctx, void *cb, bool server ) {

	int r;

	discoball_internal_context_t *ictx;

	if ( NULL == ctx || NULL == cb ) {
		r = -EINVAL;
		goto out;
	}

	ictx = (discoball_internal_context_t *) ctx;
	memset( ictx, 0, sizeof( *ictx ) );

	ictx->view.peer.flags.bitwise.server = !!server;

	if ( server ) {

	} else {

	}

out:
	return r;
}
