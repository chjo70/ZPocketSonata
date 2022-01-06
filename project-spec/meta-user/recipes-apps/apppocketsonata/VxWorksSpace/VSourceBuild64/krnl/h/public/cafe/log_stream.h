/* log_stream.h - Collects utilities around serializing event data. */

/*
 * Copyright (c) 2010-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#if !defined(__log_stream_h)
#define __log_stream_h

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <cafe/stdbool.h>
#include <cafe/types.h>
#include <cafe/inttypes.h>
#include <cafe/value_type.h>
#include <cafe/byte_buffer.h>
#include <cafe/event_map.h>
#include <cafe/log_buffer.h>

#ifdef __cplusplus
extern "C" {
#endif

struct cafe_slog_encoded_inst;
struct cafe_output_stream;


/* Version of the cafe event stream format used for new output streams */
extern const unsigned int cafe_slog_version;


/**
 *  Consume the stream header.  On success, sets 'version' to the file's format
 * version and returns CAFE_OK.
 */
extern int cafe_fdecode_stream_header(FILE *f, unsigned long *version);


extern int cafe_fdecode_event_header(FILE *msg, unsigned long long *size,
				     unsigned long long *event);

extern ssize_t cafe_fdecode_val(struct cafe_value_type *vt, void *arg,
				const struct cafe_allocator *allocator,
				struct cafe_event_map *event_map, FILE *in);

extern int cafe_fread_event_data(FILE *input,
				 const struct cafe_event_descr *event,
				 const struct cafe_allocator *allocator,
				 struct cafe_event_map *event_map,
				 struct cafe_byte_buffer *data);

extern int cafe_slog_encoded_create(
	struct cafe_instrument *session,
	struct cafe_output_stream *ostream,
	struct cafe_slog_encoded_inst **result);

extern void cafe_slog_encoded_delete(struct cafe_slog_encoded_inst *slog);

extern ssize_t cafe_slog_encoded_write(struct cafe_slog_encoded_inst *slog,
				       const struct cafe_event_descr *event,
				       void **event_data);

/**
 *  Consume the stream header.  On success, sets 'version' to the stream's
 * format version and returns CAFE_OK.
 */
extern int8_t *cafe_mdecode_stream_header(int8_t *msg, size_t msg_size,
					  unsigned long *version);


extern int8_t *cafe_mdecode_event_header(int8_t *msg, size_t msg_size,
					 unsigned long long *size,
					 unsigned long long *event);
extern int cafe_mread_event_data(int8_t *input,
				 const struct cafe_event_descr *event,
				 const struct cafe_allocator *allocator,
				 struct cafe_event_map *event_map,
				 struct cafe_byte_buffer *data);

extern int8_t *cafe_mdecode_val(struct cafe_value_type *vt, void *arg,
				const struct cafe_allocator *allocator,
				struct cafe_event_map *type_map, int8_t *in);

extern void cafe_release_values(const struct cafe_value_type *vt, void *arg,
				const struct cafe_allocator *allocator);

/**
 *  Calculate the number of bytes needed to encode the static porition of this
 * event.  This includes the event bookkeeping and its parameter values.  It
 * does NOT include any variable length data, such as strings or other
 * variable-size arrays.
 */
extern size_t calc_entry_size_static(const struct cafe_event_descr *event);

/**
 *  Calculate the number of bytes needed to encode any variable-length data
 * carried by the given event.
 */
extern size_t calc_entry_size_variable(const struct cafe_event_descr *event,
				       void *data[]);

/**
 *  Writes the given event to memory starting at the given "msg" address.
 *  Returns a pointer to the next unwritten byte.
 */
extern char *cafe_write_event(char *msg, unsigned long sequence,
			      unsigned long event,
			      const struct cafe_event_descr *event_dsecr,
			      void *data[],
			      size_t size_static, size_t size_variable);

/**
 *  Given a pointer to the beginning of an event record (in a message log),
 * populate "sequence" and "event" with the event sequence number and event id
 * respectively. Returns a pointer to the first address after the given event.
 */
extern const char *cafe_parse_event(const char *msg, unsigned long *sequence,
				    void **event, const void **args);


/**
 *  Create a new memory-buffered output stream, utilizing the given log buffer.
 * The result should be freed by the client when not in use.
 */
extern int cafe_logstream_open_output(struct cafe_log_buf *log,
				      const struct cafe_allocator *allocator,
				      struct cafe_output_stream **result,
				      void (*full_callback)(void *client_data),
				      void *client_data);

/**
 *  Create a new file output stream.  The result should be freed by the client
 * when not in use.
 */
extern int cafe_filestream_open_output(FILE *out,
				       const struct cafe_allocator *allocator,
				       struct cafe_output_stream **result);
#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif  /* if !defined(__log_stream_h) */
