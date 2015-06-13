#ifndef ARRAY_SIZE_H_
#define ARRAY_SIZE_H_

#ifndef ARRAY_SIZE
#define ARRAY_SIZE( x ) ( sizeof( x ) / sizeof( ( x )[ 0 ] ) )
#endif

#endif /* ARRAY_SIZE_H_ */
