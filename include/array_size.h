#ifndef INCLUDE_ARRAY_SIZE_H_
#define INCLUDE_ARRAY_SIZE_H_

#ifndef ARRAY_SIZE
#define ARRAY_SIZE( x ) ( sizeof( x ) / sizeof( ( x )[ 0 ] ) )
#endif

#endif /* INCLUDE_ARRAY_SIZE_H_ */
