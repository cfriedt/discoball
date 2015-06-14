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

#ifndef DISCOBALL_INTERNAL_H_
#define DISCOBALL_INTERNAL_H_

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif /* HAVE_CONFIG_H */

/*###########################################################################
 #                       STANDARD / SYSTEM HEADERS
 ###########################################################################*/

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include <sys/queue.h>

#include <string.h>
#include <errno.h>

#ifdef HAVE_PTHREAD_H
#include <pthread.h>
#endif

/*###########################################################################
 #                       LINUX TYPES
 ###########################################################################*/

#ifdef __APPLE__

#ifndef _LINUX_ERR_H
#define _LINUX_ERR_H
#endif /* _LINUX_ERR_H */
#ifndef _UAPI_LINUX_TYPES_H
#define _UAPI_LINUX_TYPES_H
#endif /* _UAPI_LINUX_TYPES_H */
#ifndef _LINUX_TYPES_H
#define _LINUX_TYPES_H
#endif /* _LINUX_TYPES_H */
#ifndef _LINUX_STDDEF_H
#define _LINUX_STDDEF_H
#endif /* _LINUX_STDDEF_H */
#ifndef _LINUX_SEQ_FILE_H
#define _LINUX_SEQ_FILE_H
#endif /* _LINUX_SEQ_FILE_H */
#ifndef _LINUX_RADIX_TREE_H
#define _LINUX_RADIX_TREE_H
#endif /* _LINUX_RADIX_TREE_H */
#ifndef _SECURE__STRING_H_
#define _SECURE__STRING_H_
#endif /* _SECURE__STRING_H_ */

#include "linux-types.h"

#endif

/*###########################################################################
 #                       LINUX STRUCTS
 ###########################################################################*/

#include "linux-support.h"

/*###########################################################################
 #                           DISCOBALL
 ###########################################################################*/

#include "discoball/discoball.h"

#include "discoball-array-size.h"
#include "discoball-common.h"
#include "discoball-container-of.h"
#include "discoball-context.h"
#include "discoball-debug.h"
#include "discoball-mutex.h"

#endif /* DISCOBALL_INTERNAL_H_ */
