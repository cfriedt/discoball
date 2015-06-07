#ifndef INCLUDE_LINUX_TYPES_H_
#define INCLUDE_LINUX_TYPES_H_

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

#define _(x) typedef uint##x##_t __u##x; typedef int##x##_t __s##x; typedef uint##x##_t u##x; typedef int##x##_t s##x
_(64);
_(32);
_(16);
_(8);

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

#endif /* INCLUDE_LINUX_TYPES_H_ */
