#ifndef DISCOBALL_ARRAY_SIZE_H_
#define DISCOBALL_ARRAY_SIZE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef ARRAY_SIZE
#define ARRAY_SIZE( x ) ( sizeof( x ) / sizeof( ( x )[ 0 ] ) )
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* DISCOBALL_ARRAY_SIZE_H_ */
