/*
 * Copyright (c) 2011, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
21jan15,tle  Fix potential buffer overrun using target filters (V7COR-2459)
*/

#ifndef INCallocator_h
#define INCallocator_h

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CAFE_ALLOC(A, SIZE) (((A) != NULL) ? ((A)->alloc)((A), (SIZE)): NULL)
#define CAFE_FREE(A, PTR) if ((A) != NULL) {((A)->free)((A), (PTR));}
#define CAFE_REALLOC(A, PTR, SIZE) (((A) != NULL) ? ((A)->realloc)((A), (PTR), (SIZE)) : NULL)

#ifdef  __GNUC__
#  define CAFE_ALLOCA(size)   __builtin_alloca(size)
#elif defined(__DCC__)
#  define CAFE_ALLOCA(size)   __alloca(size)
#elif defined(__ICC)
#  define CAFE_ALLOCA(size)   _alloca(size)
#endif

struct cafe_allocator {
	void *(*alloc)(const struct cafe_allocator *, size_t size);
	void *(*realloc)(const struct cafe_allocator *, void *p, size_t size);
	void (*free)(const struct cafe_allocator *, void *p);
};

extern struct cafe_allocator *cafe_allocator_create(void);
extern void cafe_allocator_delete(const struct cafe_allocator *allocator);
extern struct cafe_allocator *cafe_stdlib_allocator;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INCallocator_h */
