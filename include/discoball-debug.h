#ifndef DISCOBALL_DEBUG_H_
#define DISCOBALL_DEBUG_H_

#ifdef DEBUG

#include <stdio.h>
#include <string.h>
#include <errno.h>

#define D( fmt, args... ) \
{ \
	fprintf( stderr, "%s:%d:%s(): " fmt "\n", __FILE__, __LINE__, __FUNCTION__, ##args ); \
	fflush( stderr ); \
}

#define E( fmt, args... ) \
{ \
	if ( errno ) { \
		fprintf( stderr, "%s:%d:%s(): %s (%d): " fmt "\n", __FILE__, __LINE__, __FUNCTION__, strerror( errno ), errno, ##args ); \
	} else { \
		fprintf( stderr, "%s:%d:%s(): " fmt "\n", __FILE__, __LINE__, __FUNCTION__, ##args ); \
	} \
	fflush( stderr ); \
}

#else

#define D( fmt, args... )
#define E( fmt, args... )

#endif

#endif /* DISCOBALL_DEBUG_H_ */
