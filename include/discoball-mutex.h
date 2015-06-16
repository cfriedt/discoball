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
