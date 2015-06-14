#ifndef DISCOBALL_ARRAY_SIZE_H_
#define DISCOBALL_ARRAY_SIZE_H_

#ifndef ARRAY_SIZE
#define ARRAY_SIZE( x ) ( sizeof( x ) / sizeof( ( x )[ 0 ] ) )
#endif

#endif /* DISCOBALL_ARRAY_SIZE_H_ */
