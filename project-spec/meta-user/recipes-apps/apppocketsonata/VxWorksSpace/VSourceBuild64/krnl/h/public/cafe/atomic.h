/* cafe_atomic.h - atomic operations */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#ifndef INCcafe_atomic_h
#define INCcafe_atomic_h

#include <cafe/stdbool.h>

typedef long cafe_atomic_val;

/* Atomically increment atomic value by 1.  Returns the old value. */
extern cafe_atomic_val cafe_atomic_val_inc(volatile cafe_atomic_val *v);

/* Atomically add the given value.  Returns the old value. */
extern cafe_atomic_val cafe_atomic_val_add(volatile cafe_atomic_val *v,
					   cafe_atomic_val addend);

/* Atomically decrement atomic value by 1.  Returns the old value. */
extern cafe_atomic_val cafe_atomic_val_dec(volatile cafe_atomic_val *v);

/* Atomically subtract the given value.  Returns the old value. */
extern cafe_atomic_val cafe_atomic_val_sub(volatile cafe_atomic_val *v,
					   cafe_atomic_val addend);

/* Atomically exchange target with new value.  Returns the old value. */
extern void *cafe_atomic_swap_ptr(volatile void *volatile *target,
				  void *newval);

/* Atomically get a memory location. */
extern cafe_atomic_val cafe_atomic_get(volatile cafe_atomic_val *target);

/* Atomically set a memory location.  Returns the old value. */
extern cafe_atomic_val cafe_atomic_set(volatile cafe_atomic_val *target,
				       cafe_atomic_val value);

/* Atomically compare and swap the contents of a memory location.
 *
 * If the current value of *TARGET is OLDVAL, then write NEWVAL into
 * *TARGET.  Returns true if the values are equal and NEWVAL was
 * written.
 */
extern bool cafe_atomic_cas(volatile cafe_atomic_val *target,
			    cafe_atomic_val oldval,
			    cafe_atomic_val newval);

#endif	/* INCcafe_atomic_h */
