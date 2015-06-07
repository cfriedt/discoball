#include "strlen.h"

size_t strlen( const char *s ) {
	size_t r = 0;

	char *q, *p;
	for( p = (char *)s, q = p; *q; q++ );
	r = (size_t)( p - q );

	return r;
}
