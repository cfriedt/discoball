#ifndef DISCOBALL_BUFFER_H_
#define DISCOBALL_BUFFER_H_

#ifndef DISCOBALL_DISCOBALL_H_
#error discoball/client.h should not be directly included. It should be included by including discoball/discoball.h
#endif

/* In the same vein of minimal requirements, the API for reading and writing
 * data from a device, socket or file, is externalized. That way, no actual
 * mechanism for transmitting or receiving information is imposed.
 *
 * Externalizing that API also implies that the loop for transmitting and
 * receiving via that API is also externalized. Thus neither a Process, Task,
 * Thread, nor Interrupt structure is imposed on the API Consumer. However,
 * as a separate resource, a userspace implementation using POSIX threads,
 * as well as a Linux kernel implementation using kernel threads, will be
 * made available.
 */

int discoball_buffer_append_data( discoball_context_t *ctx, void *data, size_t len );

#endif /* DISCOBALL_BUFFER_H_ */
