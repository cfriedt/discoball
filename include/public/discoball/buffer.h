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

#ifndef DISCOBALL_BUFFER_H_
#define DISCOBALL_BUFFER_H_

#ifndef DISCOBALL_DISCOBALL_H_
#error discoball/client.h should not be directly included. It should be included by including discoball/discoball.h
#endif

/* In the same vein of minimal requirements, the API for reading and writing
 * data from a device, socket or file, is externalized. That way, no actual
 * mechanism for transmitting or receiving information is imposed.
 *
 * Externalizing that API also implies that the loop for transmitting and
 * receiving via that API is also externalized. Thus neither a Process, Task,
 * Thread, nor Interrupt structure is imposed on the API Consumer. However,
 * as a separate resource, a userspace implementation using POSIX threads,
 * as well as a Linux kernel implementation using kernel threads, will be
 * made available.
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

int discoball_buffer_append_data( discoball_context_t *ctx, void *data, size_t len );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DISCOBALL_BUFFER_H_ */
