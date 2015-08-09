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

#ifndef DISCOBALL_TCPIP_PTHREAD_SERVER_H_
#define DISCOBALL_TCPIP_PTHREAD_SERVER_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <discoball/discoball.h>

#include <pthread.h>

#define DISCOBALL_TCPIP_PTHREAD_SERVER_AF_DEFAULT AF_INET
#define DISCOBALL_TCPIP_PTHREAD_SERVER_PF_DEFAULT PF_INET
#define DISCOBALL_TCPIP_PTHREAD_SERVER_PORT_DEFAULT 1234

enum {
	SERVER_STATUS_NOT_INITIALIZED,
	SERVER_STATUS_INITIALIZED,
	SERVER_STATUS_RUNNING,
	SERVER_STATUS_SHOULD_FINALIZE,
	SERVER_STATUS_FINALIZED,
};

typedef struct discoball_tcpip_pthread_server_context {
	discoball_context_t ctx;
	pthread_t server_thread;
	int server_thread_status;
	int server_thread_return;
	int server_af;
	int server_pf;
	int server_port;
	int server_socket;
	int interrupt_pair[2];
	int client_socket;
} discoball_tcpip_pthread_server_context_t;

extern const discoball_server_cb_t discoball_tcpip_pthread_server_cb;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DISCOBALL_TCPIP_PTHREAD_SERVER_H_ */
