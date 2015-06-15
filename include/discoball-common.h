#ifndef DISCOBALL_COMMON_H_
#define DISCOBALL_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdbool.h>

struct discoball_context;
typedef struct discoball_context discoball_context_t;

int discoball_common_register( discoball_context_t *ctx, void *cb, bool server );
int discoball_common_deregister( discoball_context_t *ctx, bool server );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DISCOBALL_COMMON_H_ */
