/* ptr_array - dynamic array */

/* Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

#ifndef INCptr_array_h
#define INCptr_array_h

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define cafe_ptr_array_len(A) ((A)->len)
#define cafe_ptr_array_capacity(A) ((A)->capacity)
#define cafe_ptr_array_val(A, IDX) ((A)->data[(IDX)])

struct cafe_ptr_array {
	void **data;
	size_t len;
	size_t capacity;
	const struct cafe_allocator *allocator;
};

/* Initializes the array.
 *
 * Its initial capacity and length is 0.
 *
 * @array        - pointer to array to initialize
 * @allocator    - memory allocator
 */
extern void cafe_ptr_array_init
	(
	struct cafe_ptr_array *array,
	const struct cafe_allocator *allocator
	);

/* Increase the capacity to NEW_CAPACITY.
 *
 * Return CAFE_OK on success, otherwise CAFE_NOMEM if the array could
 * not be expanded.
 */
extern int cafe_ptr_array_capacity_set
	(
	struct cafe_ptr_array *array,
	size_t new_capacity
	);

/* Release the array's values. */

extern void cafe_ptr_array_release
	(
	struct cafe_ptr_array *array
	);

/* Append element to the array.
 *
 * Returns CAFE_OK on success, otherwise CAFE_NOMEM if the array could
 * not be expanded.
 *
 * @val - value to insert
 */
extern int cafe_ptr_array_append
	(
	struct cafe_ptr_array *array,
	void *val
	);

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif	/* INCptr_array_h */
