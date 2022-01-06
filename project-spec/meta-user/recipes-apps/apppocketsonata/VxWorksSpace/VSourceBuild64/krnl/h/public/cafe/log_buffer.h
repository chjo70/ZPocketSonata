/* log_buffer.h - memory-based byte-oriented ring buffer */

/* Copyright (c) 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
  This buffer internally handles reader/writer interlocks, but the client must
  handle any possibility of multiple readers and/or multiple writers.

  Differentiates itself from rngLib.c by:
  - providing a non-malloc-based creation usage
  - when needed, mallocing everything in one chunk
  - "zero copy" read and writes

  Differentiates itself from rBuffLib.c by:
  - being simpler
  - not providing ability to grow dynamically

  To support the zero-copy-based interface, read and write pointers returned to
  callers always represent contiguous memory.
  Does not attempt to support the flight-recorder usecase, since that doesn't
  require read/write synchronization.
*/


#if !defined(__log_buffer_h)
#define __log_buffer_h

#include <stddef.h>  /* for size_t */
#include <cafe/stdbool.h>
#include <cafe/types.h>

#if defined(__cplusplus)
extern "C" {
#endif

/* td: read and write head should be atomics */
struct cafe_log_buf {
	size_t size;		/* size (bytes) of the data area */
	char *write_head;	/* first currently writeable byte in the log */
	char *read_head;	/* last read byte in the log */
	char *trailing_top;	/* pointer to the first unwritten byte
				   after the write_head has wrapped around. */
	char data[0];
};


/**
 *  Initialize the given address as a new log buffer.  This can be useful for
 * creating a log buffer based on pre-allocated memory.  It can also be useful
 * if the client wants to pre-fill the area with a pattern (to check high-water
 * marks, etc.).
 */
extern bool cafe_log_init(struct cafe_log_buf *log, size_t size);


/**
 *  Allocates space for a buffer of the given size and initializes the buffer.
 * When using this routine, it is the caller's responsibility to free() the
 * returned pointer when the buffer is no longer in use, using the same
 * allocator as is passed to log_create().
 */
extern struct cafe_log_buf *cafe_log_create(
	size_t size,
	const struct cafe_allocator *allocator);


/**
 *  Reserve enough space in the log for the given byte size.  Returns 0 on
 * failure and a pointer to the writeable area on success.  The bytes written
 * to the area are not available to be read until commit() is called.  It is
 * the caller's responsibility to not write more than "size" bytes to the
 * returned pointer.
 * Note that the write head will always point at an empty byte.  This acts as
 * a flag so we can tell whether the buffer is completely full or completely
 * empty.  Otherwise, when read == write, then we have no way of knowing.
 */
extern char *cafe_log_write_reserve(struct cafe_log_buf *buf, size_t size);


/**
 *  Reserve as much log space as possible for writing data. Returns 0
 * if the minimum number of bytes are not available, and a pointer to the
 * writeable area on success.  The bytes written to the area are not available
 * to be read until commit() is called.  It is the caller's responsibility to
 * not write more than "available" bytes to the returned pointer.
 * Note that the write head will always point at an empty byte.  This acts as
 * a flag so we can tell whether the buffer is completely full or completely
 * empty.  Otherwise, when read == write, then we have no way of knowing.
 */
extern char *cafe_log_write_reserve_min(struct cafe_log_buf *buf, size_t min,
					size_t *available);


/**
 *  Flags the currently available write-area as being finished and available
 * for reading.  Callers may pass a smallersize here than what they actually
 * reserved, but they must never pass a greater size.  It is currently the
 * client's responsibility to ensure the reserve() and commit() routines are
 * always called in matching pairs.
 */
extern void cafe_log_write_commit(struct cafe_log_buf *buf, size_t size);


/**
 *  Get a pointer to the next readable section of the buffer.  The size of the
 * readable area is returned in the "size" parameter, will be 0 if there's no
 * bytes currently written to the buffer.  The readable bytes will remain so
 * on successive calls to this function, until commit() is called.
 * It is the caller's responsibility to not read more than *size bytes from the
 * returned pointer.
 */
extern char *cafe_log_read_reserve(struct cafe_log_buf *buf, size_t *size);


/**
 *  Advances the buffer's read head bye "size" bytes.  The given size must
 * never exceed the value returned by a preceeding call to read_reserve(), but
 * may be less than that value if the client consumed less than the currently
 * available buffer.
 */
extern void cafe_log_read_commit(struct cafe_log_buf *buf, size_t size);

#ifdef __cplusplus
}	/* extern "C" */
#endif

#endif /* if !defined(__log_buffer_h) */
