/* errors.h - cafe error handling */

/*
 * Copyright (c) 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#if !defined(__cafe_errors_h)
#define __cafe_errors_h


#include <cafe/byte_buffer.h>
#include <cafe/stdio.h>


#if defined(__cplusplus)
extern "C" {
#endif


/* Object used to capture the current error status.  The global instance is
   used to track errors during synchronous operations; those occurring while
   the Cafe lock is held. */
struct cafe_error_report {
	int rc;
	int os_errno;
	unsigned int n_messages;
	char **messages;
} cafe_error_cur;


/**
 *  Set the given error report object to the given Cafe error status, and
 * optionally store any associated error message.  If an error status is
 * already asserted, push the given message onto the message stack.
 */
extern void cafe_error_set(struct cafe_error_report *e,
			   int cafe_status, const char *fmt, ...);


/**
 *  Provide an optional OS-specific error value, e.g., "errno".
 */
extern void cafe_error_set_errno(struct cafe_error_report *e, int err);


/**
 *  Emit a representation of the given error object to the given output stream.
 * Seperates different message sections with the given delimiter string.
 */
extern void cafe_error_print(const struct cafe_error_report *e, FILE *out,
			     const char *delim);


/**
 *  Emits an error report to the given byte-buffer, separating each entry with
 * the provided delimiter string.
 */
extern int cafe_error_bbuf_write(const struct cafe_error_report *e,
				 struct cafe_byte_buffer *buf,
				 const char *err_msg, const char *delim);


/**
 *  Clear the given error report object, resetting status to CAFE_OK, and
 * releasing any messages and other allocated memory.
 */
extern void cafe_error_clear(struct cafe_error_report *e);


#if defined(__cplusplus)
}
#endif

#endif	/* if !defined(__cafe_errors_h) */
