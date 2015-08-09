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

#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <stddef.h>

#include "discoball/tcpip-pthread/server.h"
#include "discoball-container-of.h"
#include "discoball-debug.h"

static const discoball_tcpip_pthread_server_context_t prototype_tcpip_pthread_server = {
	.server_thread_status = SERVER_STATUS_NOT_INITIALIZED,
	.server_af = DISCOBALL_TCPIP_PTHREAD_SERVER_AF_DEFAULT,
	.server_pf = DISCOBALL_TCPIP_PTHREAD_SERVER_PF_DEFAULT,
	.server_port = DISCOBALL_TCPIP_PTHREAD_SERVER_PORT_DEFAULT,
	.server_socket = -1,
	.interrupt_pair = { -1, -1, },
	.client_socket = -1,
};

#if !defined __GNUC__
static inline discoball_tcpip_pthread_server_context_t *__to_tps_container_of( void *p ) {
	discoball_tcpip_pthread_server_context_t *r;
	const discoball_context_t *__mptr = p;
	r = (discoball_tcpip_pthread_server_context_t *)( (char *)__mptr - offsetof(discoball_tcpip_pthread_server_context_t,ctx) );
	return r;
}
#undef container_of
#define container_of( ptr, type, member) __to_tps_container_of( ptr )
#endif

static inline discoball_tcpip_pthread_server_context_t *to_tps( discoball_context_t *ctx ) {
	discoball_tcpip_pthread_server_context_t *r;
	r = container_of( ctx, discoball_tcpip_pthread_server_context_t, ctx );
	return r;
}

static void *server_thread( void *data ) {
	int r;

	discoball_tcpip_pthread_server_context_t *ctx;
	socklen_t addr_len;
	struct sockaddr_storage addr;

	ctx = (discoball_tcpip_pthread_server_context_t *) data;
	addr_len = sizeof( addr );
	memset( &addr, 0, addr_len );

	for( ; SERVER_STATUS_SHOULD_FINALIZE != ctx->server_thread_status; ) {

		r = accept( ctx->server_socket, (struct sockaddr *) &addr, &addr_len );
		if ( -1 == r ) {
			ctx->server_thread_return = errno;
			E( "accept" );
			ctx->server_thread_status = SERVER_STATUS_SHOULD_FINALIZE;
			goto out;
		}

		ctx->client_socket = r;

		r = socketpair( AF_UNIX, SOCK_STREAM, 0, ctx->interrupt_pair );
		if ( -1 == r ) {
			ctx->server_thread_return = errno;
			E( "socketpair" );
			ctx->server_thread_status = SERVER_STATUS_SHOULD_FINALIZE;
			goto close_client_socket;
		}

		//r = discoball_server_register();
		r = 0;


	close_socket_pair:
		close( ctx->interrupt_pair[ 0 ] );
		close( ctx->interrupt_pair[ 1 ] );
		ctx->interrupt_pair[ 0 ] = -1;
		ctx->interrupt_pair[ 1 ] = -1;

	close_client_socket:
		close( ctx->client_socket );
		ctx->client_socket = -1;

	out:
		continue;
	}

	return & ctx->server_thread_return;
}

static int discoball_tcpip_pthread_server_init( discoball_context_t *ctx ) {
	int r;
	discoball_tcpip_pthread_server_context_t *_ctx = to_tps( ctx );
	memcpy( _ctx, &prototype_tcpip_pthread_server, sizeof ( prototype_tcpip_pthread_server ) );
	r = 0;
	return r;
}

static int discoball_tcpip_pthread_server_fini( discoball_context_t *ctx ) {
	int r;
	discoball_tcpip_pthread_server_context_t *_ctx = to_tps( ctx );

	if ( SERVER_STATUS_FINALIZED != _ctx->server_thread_status ) {
		r = -EBUSY;
		goto out;
	}

	r = 0;
	goto out;

out:
	return r;
}

static int discoball_tcpip_pthread_server_start( discoball_context_t *ctx ) {
	int r;
	discoball_tcpip_pthread_server_context_t *_ctx = to_tps( ctx );

	struct addrinfo hints, *servinfo, *p;

	char port_str[ 8 ];

	memset(&hints, 0, sizeof hints);
	hints.ai_family = _ctx->server_pf;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	snprintf( port_str, sizeof( port_str ), "%u", (unsigned short)_ctx->server_port );

	r = getaddrinfo( NULL, port_str, &hints, &servinfo );
	if ( 0 != r ) {
		E("getaddrinfo");
		goto out;
	}

	for( p = servinfo; NULL != p; p = p->ai_next ) {
		_ctx->server_socket = socket( p->ai_family, p->ai_socktype, p->ai_protocol );
		if ( -1 == _ctx->server_socket ) {
			E( "socket" );
			continue;
		}
		r = bind( _ctx->server_socket, p->ai_addr, p->ai_addrlen );
		if ( -1 == r ) {
			E( "bind" );
			close( _ctx->server_socket );
			_ctx->server_socket = -1;
		}
		break;
	}

	freeaddrinfo( servinfo );

	if ( -1 == _ctx->server_socket ) {
		errno = ENOENT;
		E( "unable to find suitable socket" );
		r = -1;
		goto out;
	}

	r = listen( _ctx->server_socket, 1 /* point to point */ );
	if ( -1 == r ) {
		r = -errno;
		E( "listen" );
		goto close_socket;
	}

	_ctx->server_thread_status = SERVER_STATUS_INITIALIZED;

	r = pthread_create( &_ctx->server_thread, NULL, server_thread, _ctx );
	if ( 0 != r ) {
		errno = r;
		E( "listen" );
		goto close_socket;
	}

	r = 0;
	goto out;

close_socket:
	close( _ctx->server_socket );
	_ctx->server_socket = -1;

out:
	return r;
}

static int discoball_tcpip_pthread_server_stop( discoball_context_t *ctx ) {
	int r;
	discoball_tcpip_pthread_server_context_t *_ctx = to_tps( ctx );
	r = -ENOSYS;
	return r;
}

static int discoball_tcpip_pthread_server_write( discoball_context_t *ctx, void *data, size_t size ) {
	int r;
	discoball_tcpip_pthread_server_context_t *_ctx = to_tps( ctx );
	r = -ENOSYS;
	return r;
}

const discoball_server_cb_t discoball_tcpip_pthread_server_cb = {
	.init = discoball_tcpip_pthread_server_init,
	.fini = discoball_tcpip_pthread_server_fini,
	.start = discoball_tcpip_pthread_server_start,
	.stop = discoball_tcpip_pthread_server_stop,
	.write = discoball_tcpip_pthread_server_write,
};
