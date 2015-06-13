#ifndef CONTAINER_OF_H_
#define CONTAINER_OF_H_

#ifndef container_of
#define container_of(ptr, type, member) \
({ \
	const typeof( ((type *)0)->member ) *__mptr = (ptr); \
	(type *)( (char *)__mptr - offsetof(type,member) ); \
})
#endif

#endif /* CONTAINER_OF_H_ */
