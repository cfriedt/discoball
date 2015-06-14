#ifndef DISCOBALL_CONTAINER_OF_H_
#define DISCOBALL_CONTAINER_OF_H_

#ifndef container_of
#define container_of(ptr, type, member) \
({ \
	const typeof( ((type *)0)->member ) *__mptr = (ptr); \
	(type *)( (char *)__mptr - offsetof(type,member) ); \
})
#endif

#endif /* DISCOBALL_CONTAINER_OF_H_ */
