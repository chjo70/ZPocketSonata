/* array - resizable array */

/* Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

#ifndef INCarray_h
#define INCarray_h

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define cafe_array_len(A) ((A)->len)
#define cafe_array_element_size(A) ((A)->element_size)
#define cafe_array_capacity(A) ((A)->capacity)
#define cafe_array_val(A, TYPE, IDX) (((TYPE *)(void *)(A)->data)[(IDX)])
#define cafe_array_val_ptr(A, TYPE, IDX) (&((TYPE *)(void *)(A)->data)[(IDX)])

struct cafe_array {
	void *data;
	size_t len;
	size_t capacity;
	size_t element_size;
	const struct cafe_allocator *allocator;
};

/* Initializes the array.
 *
 * Its initial capacity and length is 0.
 *
 * @array	 - pointer to array to initialize
 * @allocator	 - memory allocator
 * @element_size - size of one element (e.g., sizeof(int)).
 */
extern void cafe_array_init
	(
	struct cafe_array *array,
	const struct cafe_allocator *allocator,
	size_t element_size
	);

/* Increase the capacity to NEW_CAPACITY.
 *
 * Return CAFE_OK on success, otherwise CAFE_NOMEM if the array could
 * not be expanded.
 */
extern int cafe_array_capacity_set
	(
	struct cafe_array *array,
	size_t new_capacity
	);

/* Release the data used to manage the elements. */

extern void cafe_array_release
	(
	struct cafe_array *array
	);

/* Add element to the end of the array, expanding the array if necessary.
 *
 * Returns CAFE_OK on success, otherwise CAFE_NOMEM if the array could
 * not be expanded.
 *
 * @val - value to insert
 */
extern int cafe_array_append
	(
	struct cafe_array *array,
	const void *val
	);

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* INCarray_h */
