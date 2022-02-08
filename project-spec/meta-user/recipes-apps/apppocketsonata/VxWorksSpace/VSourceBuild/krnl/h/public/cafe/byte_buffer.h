/* cafe_byte_buffer.h -  */

/* Copyright (c) 2011-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

#if !defined(__byte_buffer_h)
#define __byte_buffer_h

#include <stddef.h>
#include <assert.h>
#include <string.h>
#include <cafe/cafe.h>

#if defined(__cplusplus)
extern "C" {
#endif


struct cafe_byte_buffer {
	char *data;
	size_t len;
	size_t capacity;
	const struct cafe_allocator *allocator;
};


/**
 * Initializes the byte buffer
 */
static inline
int cafe_bbuf_init(struct cafe_byte_buffer *bbuf,
		   const struct cafe_allocator *allocator,
		   size_t initial_capacity)
{
	assert(bbuf != NULL);
	if (initial_capacity > 0) {
		bbuf->data = (char *) CAFE_ALLOC(allocator, initial_capacity);
		if (bbuf->data == NULL)
			return CAFE_NOMEM;
	} else {
		bbuf->data = NULL;
	}
	bbuf->allocator = allocator;
	bbuf->len = 0;
	bbuf->capacity = initial_capacity;
	return CAFE_OK;
}


/**
 * Release the data used to manage the elements.
 */
static inline
void cafe_bbuf_release(struct cafe_byte_buffer *bbuf)
{
	assert(bbuf != NULL);
	if (bbuf->allocator != NULL)
		CAFE_FREE(bbuf->allocator, bbuf->data);
}


/**
 * Increase the given byte buffer's capacity to at least the new_capacity
 * specified by the caller.
 */
static inline
int cafe_bbuf_capacity_set(struct cafe_byte_buffer *bbuf, size_t new_capacity)
{
	char *new_buf;
	size_t curr_capacity;

	assert(bbuf != NULL);
	if (new_capacity < bbuf->capacity)
		return CAFE_OK;

	curr_capacity = bbuf->capacity ? bbuf->capacity : 1;
	while (curr_capacity <= new_capacity)
		curr_capacity *= 2;

	new_buf = (char *) CAFE_REALLOC(bbuf->allocator, bbuf->data,
					curr_capacity);
	if (new_buf == NULL)
		return CAFE_NOMEM;

	bbuf->capacity = curr_capacity;
	bbuf->data = new_buf;

	return CAFE_OK;
}


static inline
int cafe_bbuf_write(struct cafe_byte_buffer *bbuf, int byte)
{
	int rc = cafe_bbuf_capacity_set(bbuf, bbuf->len + 1);
	if (rc != CAFE_OK)
		return rc;

	bbuf->data[bbuf->len++] = (char) byte;
	return CAFE_OK;
}


static inline
int cafe_bbuf_append(struct cafe_byte_buffer *bbuf, const char *new_data,
		     size_t new_data_len)
{
	size_t required_len = bbuf->len + new_data_len;
	int rc = cafe_bbuf_capacity_set(bbuf, required_len);
	if (rc != CAFE_OK)
		return rc;

	memcpy(&bbuf->data[bbuf->len], new_data, new_data_len);
	bbuf->len = required_len;
	return CAFE_OK;
}


static inline
int cafe_bbuf_reserve(struct cafe_byte_buffer *bbuf, size_t new_data_len,
		      char **new_data)
{
	size_t required_len = bbuf->len + new_data_len;
	int rc = cafe_bbuf_capacity_set(bbuf, required_len);

	if (rc != CAFE_OK)
		return rc;

	*new_data = bbuf->data + bbuf->len;
	bbuf->len = required_len;
	return CAFE_OK;
}

#if defined(__cplusplus)
}
#endif

#endif	/* if !defined(__byte_buffer_h) */
