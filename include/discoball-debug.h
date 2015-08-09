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

#ifndef DISCOBALL_DEBUG_H_
#define DISCOBALL_DEBUG_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef DEBUG

#include <stdio.h>
#include <string.h>
#include <errno.h>

#define D( fmt, args... ) \
{ \
	fprintf( stderr, "D/ %s:%d:%s(): " fmt "\n", __FILE__, __LINE__, __FUNCTION__, ##args ); \
	fflush( stderr ); \
}

#define E( fmt, args... ) \
{ \
	if ( errno ) { \
		fprintf( stderr, "E/ %s:%d:%s(): %s (%d): " fmt "\n", __FILE__, __LINE__, __FUNCTION__, strerror( errno ), errno, ##args ); \
	} else { \
		fprintf( stderr, "E/ %s:%d:%s(): " fmt "\n", __FILE__, __LINE__, __FUNCTION__, ##args ); \
	} \
	fflush( stderr ); \
}

#define W( fmt, args... ) \
{ \
	fprintf( stderr, "W/ %s:%d:%s(): " fmt "\n", __FILE__, __LINE__, __FUNCTION__, ##args ); \
	fflush( stderr ); \
}

#else

#define D( fmt, args... )
#define E( fmt, args... )
#deine W( fmt, args... )

#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DISCOBALL_DEBUG_H_ */
