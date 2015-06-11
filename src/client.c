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

#include <discoball/discoball.h>

#include "discoball_internal.h"

/* API Consumers need to register with the library. In doing so,
 * the API Consumer supplies two items:
 *
 *   1) A pre-populated discoball_ops_t (an event listener) structure
 *      containing pertinent callbacks encoded as function pointers, and
 *   2) A pointer to a pre-allocated discoball_context_t. The size of the
 *      discoball_context_t is to be conveyed as a preprocessor define,
 *      so that the API Consumer does not require dynamic memory allocation
 *      facilities.
 *
 * In the same vein of minimal requirements, the loop for reading data from
 * a device, socket or file, is externalized. That way, neither a Process,
 * Task, Thread, nor Interrupt structure is imposed on the API Consumer.
 * However, as a separate resource, a userspace implementation using POSIX
 * threads, as well as a Linux kernel implementation using kernel threads,
 * will be made available.
 *
 * To further reduce system library requirements, the standard IO routines
 * of open / read / write / close, as well as related variants, are not
 * required as part of the core library. Similarly, a userspace
 * implementation that uses standard IO routines will be made available
 * as a separate resource.
 *
 * Some level of protection primitive is required, but in general,
 * API Consumers will not need to concern themselves with such matters
 * as they are internal to DiscoBall. There will be separate resources
 * demonstrating protection primitives e.g. in userspace, using POSIX
 * Mutexes, in the Linux kernel using kmutex, and on bare metal, by
 * disabling interrupts. Protection primitives are required so that
 * callbacks into the API Consumers can be accomplished uninterupted.
 * API Consumers can duplicate data in their own callbacks if required.
 * That way, their is no chance of reentrance and a dynamic allocator
 * is unnecessary.
 *
 * Each of the above minimization specifications are intended to allow
 * DiscoBall to be run as a library on virtually any platform -
 * supercomputer, server, laptop, or microcontroller.
 *
 */
