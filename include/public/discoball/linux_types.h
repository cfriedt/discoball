

/*
 * The compilation of software known as DiscoBall is distributed under the * following terms: *  * Copyright (c) 2015 Christopher Friedt. All rights reserved. *  * Redistribution and use in source and binary forms, with or without * modification, are permitted provided that the following conditions * are met: * 1. Redistributions of source code must retain the above copyright * notice, this list of conditions and the following disclaimer. * 2. Redistributions in binary form must reproduce the above copyright * notice, this list of conditions and the following disclaimer in the * documentation and/or other materials provided with the distribution. *  * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF * SUCH DAMAGE. */
#ifndef INCLUDE_LINUX_TYPES_H_
#define INCLUDE_LINUX_TYPES_H_

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

// define e.g. __u32 __s32 u32 s32 all in one statement
#undef _
#define _(x) \
	typedef uint##x##_t __u##x; \
	typedef int##x##_t __s##x; \
	typedef uint##x##_t u##x; \
	typedef int##x##_t s##x

_(64);
_(32);
_(16);
_(8);
#undef _

struct list_head;
struct list_head {
	struct list_head *prev;
	struct list_head *next;
};

struct hlist_head {
	struct hlist_node *first;
};

struct hlist_node;
struct hlist_node {
	struct hlist_node *next;
	struct hlist_node **pprev;
};

typedef size_t __kernel_size_t;
typedef unsigned gfp_t;
typedef off_t loff_t;

#define __must_check

#define MAX_ERRNO	4095
#define IS_ERR(x) 0
#define ERR_PTR(x) 0
#define PTR_ERR(x) 0
#define ERR_CAST(x) 0

#endif /* INCLUDE_LINUX_TYPES_H_ */
