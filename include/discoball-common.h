#ifndef DISCOBALL_COMMON_H_
#define DISCOBALL_COMMON_H_

#include "discoball-internal.h"

int discoball_common_register( discoball_context_t *ctx, void *cb, bool server );
int discoball_common_deregister( discoball_context_t *ctx, bool server );

#endif /* DISCOBALL_COMMON_H_ */
