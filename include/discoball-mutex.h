#ifndef DISCOBALL_MUTEX_H_
#define DISCOBALL_MUTEX_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

/* Some level of protection primitive is required, but in general,
 * API Consumers will not need to concern themselves with such matters
 * as they are internal to DiscoBall. There will be separate resources
 * demonstrating protection primitives e.g. in userspace, using POSIX
 * Mutexes, in the Linux kernel using struct mutex, and on bare metal by
 * using either atomic operations or simply disabling interrupts.
 * Protection primitives are required so that callbacks into the API
 * Consumers can be accomplished uninterupted.
 */

#if defined( HAVE_PTHREAD_H )

#if defined( DISCOBALL_MUTEX_DEFINED )
#error DISCOBALL_MUTEX_DEFINED already defined elsewhere
#endif

#include <pthread.h>

#define DISCOBALL_MUTEX_DECLARE( _name ) pthread_mutex_t _name = PTHREAD_MUTEX_INITIALIZER
#define DISCOBALL_MUTEX_LOCK( _name ) { \
	int _r = pthread_mutex_lock( & _name ); \
	if ( 0 != _r ) { \
		errno = _r; \
		E( "failed to lock mutex %s", #_name ); \
	} \
}
#define DISCOBALL_MUTEX_UNLOCK( _name ) { \
	int _r = pthread_mutex_unlock( & _name ); \
	if ( 0 != _r ) { \
		errno = _r; \
		E( "failed to unlock mutex %s", #_name ); \
	} \
}

#define DISCOBALL_MUTEX_DEFINED

#endif

#if defined( __LINUX_MUTEX_H )

#if defined( DISCOBALL_MUTEX_DEFINED )
#error DISCOBALL_MUTEX_DEFINED already defined elsewhere
#endif

#define DISCOBALL_MUTEX_DECLARE( _name ) DEFINE_MUTEX( _name  )
#define DISCOBALL_MUTEX_LOCK( _name ) mutex_lock( _name )
#define DISCOBALL_MUTEX_UNLOCK( _name ) mutex_unlock( _name )

#define DISCOBALL_MUTEX_DEFINED

#endif

// TODO: make a simple mutex implementation using atomic operations (i.e. spinlocks)

// TODO: make a simple mutex implementation disabling interrupts (for bare-metal systems)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DISCOBALL_MUTEX_H_ */
