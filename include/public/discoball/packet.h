#ifndef DISCOBALL_PACKET_H_
#define DISCOBALL_PACKET_H_

#include <stdint.h>

/*###########################################################################
 #                            ENDPOINTS
 ###########################################################################*/

typedef enum {
	DISCOBALL_CONTROL_ENDPOINT = 0, // the control endpoint that handles the discoball protocol
} discoball_endpoint_t;

/*###########################################################################
 #                            BASIC FRAME
 ###########################################################################*/

typedef struct discoball_packet_header {
	uint8_t packet_length;
	uint8_t packet_type;
	uint8_t frame_no;
	uint8_t endpoint;
	uint8_t data[];
} discoball_packet_header_t __attribute__(( packed ));

typedef discoball_packet_header_t discoball_packet_t;

typedef struct discoball_packet_footer {
	uint16_t crc16; //
} discoball_packet_footer_t __attribute__(( packed ));

/*###########################################################################
 #                            FRAME TYPES
 ###########################################################################*/

enum {
	DISCOBALL_PACKET_TYPE_HEARTBEAT = 0,
	DISCOBALL_PACKET_TYPE_ACK,
	DISCOBALL_PACKET_TYPE_ERROR,
	DISCOBALL_PACKET_TYPE_DATA,
};

/*###########################################################################
 #                            HEARTBEAT
 ###########################################################################*/

typedef struct discoboall_packet_heartbeat {
	discoball_packet_header_t hdr;
	discoball_packet_footer_t ftr;
} discoball_packet_heartbeat_t __attribute__(( packed ));

/*###########################################################################
 #                       ACK / NACK / RETRANSMIT
 ###########################################################################*/

typedef enum {
	DISCOBALL_ACK_RX_OK = 1,    // 0 indicates corrupt packet / retransmission request
	DISCOBALL_ACK_PROTO_OK = 2, // 0 indicates protocol error
	DISCOBALL_ACK_ALL_OK = ( DISCOBALL_ACK_RX_OK | DISCOBALL_ACK_PROTO_OK ),
} discoball_packet_ack_status_t;

typedef struct discoboall_packet_ack {
	discoball_packet_header_t hdr;
	union {
		struct {
			uint8_t retransmit_frame_no;
			uint8_t flags; // normally, this reads DISCOBALL_ACK_ALL_OK
		} field;
		uint16_t raw;
	} status;
	discoball_packet_footer_t ftr;
} discoball_packet_ack_t __attribute__(( packed ));

/*###########################################################################
 #                                ERROR
 ###########################################################################*/

typedef enum {
	// if not set, both client and server should reset their internal state machines
	DISCOBALL_ERR_RECOVERABLE = 1,
} discoball_packet_error_t;

typedef struct discoboall_packet_error {
	discoball_packet_header_t hdr;
	union {
		struct {
			uint8_t err_frame_no;
			uint8_t type;
			uint16_t errno;
		} field;
		uint32_t raw;
	} status;
	discoball_packet_footer_t ftr;
} discoball_packet_error_t __attribute__(( packed ));

/*###########################################################################
 #                          GENERIC DATA / ARRAY TYPES
 ###########################################################################*/

typedef enum {

	// integer types
	DISCOBALL_DATA_U8,
	DISCOBALL_DATA_S8,
	DISCOBALL_DATA_U16,
	DISCOBALL_DATA_S16,
	DISCOBALL_DATA_U32,
	DISCOBALL_DATA_S32,
	DISCOBALL_DATA_U64,
	DISCOBALL_DATA_S64,

	// floating point types
	DISCOBALL_DATA_F32,
	DISCOBALL_DATA_F64,

	// character types
	DISCOBALL_DATA_UTF8,

	// array types
	DISCOBALL_DATA_ARRAY,

} discoball_data_t;

typedef struct discoball_array {
	uint8_t type; // must not be DISCOBALL_DATA_ARRAY; only 1-dimensional arrays are supported!
	uint32_t total_length; // total length of the array
	uint32_t segment_offset; // if 0, first array segment, otherwise, subsequent-array segment. offset in terms of array index, not bytes offset in larger part of array
	uint8_t  segment_length; // if 0, first array segment, otherwise, subsequent-array segment. offset in terms of array index, not bytes offset in larger part of array
	uint8_t data[];
} discoball_array_t;

// header portion of raw data frame, always followed by a footer
typedef struct discoboall_packet_data {
	discoball_packet_header_t hdr;
	uint8_t wrt_frame_no; // 0 for no-related-frame, nonzero for query frame, iso-initializing frame, or previous array data frame
	uint8_t type;
	uint8_t data[];
} discoball_packet_data_t __attribute__(( packed ));

// header portion of raw array data frame, always followed by a footer at a given offset
typedef struct discoboall_packet_array_data {
	discoball_packet_data_t data;
	discoball_array_t array;
} discoball_packet_array_data_t __attribute__(( packed ));

// a human-readable string is simply an array with data.type set to UTF8
typedef discoball_packet_array_data_t discoboall_packet_data_string_t;

/*###########################################################################
 #                          GET / SET ATTRIBUTE PACKETS
 ###########################################################################*/

typedef enum {
	DISCOBALL_PROPERTY_SET = 1, // 1 if the intension of the packet is to write a value to the property, otherwise a read
	DISCOBALL_PROPERTY_RO  = 2, // if SET bit is clear, indicates property is read-only
} discoball_property_flag_t;

// header portion of raw property frame, always followed by a key and footer at a given offset, and an optional value
typedef struct discoboall_packet_property {
	discoball_packet_header_t hdr;
	uint8_t flags;
	uint8_t data[];
} discoball_packet_property_t __attribute__(( packed ));

// int discoball_packet_property_getkey( discoball_packet_t *pkt, discoboall_packet_data_string_t **key );
// int discoball_packet_property_getval( discoball_packet_t *pkt, discoball_packet_data_t **val );

#endif /* DISCOBALL_PACKET_H_ */
