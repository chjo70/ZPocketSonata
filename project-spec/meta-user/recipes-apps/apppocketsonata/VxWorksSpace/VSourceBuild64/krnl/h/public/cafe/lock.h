/* lock.h - public api for cafe locks */

/*
 * Copyright (c) 2010-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#ifndef INClock_h
#define INClock_h


#include <cafe/stdbool.h>


#ifdef __cplusplus
extern "C" {
#endif


#define CAFE_LOCK()    __cafe_lock(__FILE__, __LINE__)
#define CAFE_UNLOCK()  __cafe_unlock(__FILE__, __LINE__)


/******************************************************************************
*
* __cafe_lock - acquire the Cafe global lock
*
* This routine blocks the caller until the lock becomes available.
* Locks cannot be held recursively.  Cafe clients should use the
* CAFE_UNLOCK() macro which automatically supplies parameters for
* filename and line number.
*
* RETURNS: N/A
*
* ERRNO: N/A
*
* SEE ALSO: __cafe_unlock(), cafe_islocked()
*/

extern void __cafe_lock
	(
	const char *file,	/* source filename */
	int line		/* source line number */
	);

/******************************************************************************
*
* __cafe_unlock - release the Cafe global lock
*
* Release the Cafe global lock.  Cafe clients should use the
* CAFE_UNLOCK() macro which automatically supplies parameters for
* filename and line number.
*
* RETURNS: N/A
*
* ERRNO: N/A
*
* SEE ALSO: __cafe_lock, cafe_islocked
*/

extern void __cafe_unlock
	(
	const char *file,	/* source filename */
	int line		/* source line number */
	);

extern int cafe_notify_signal
	(
	void
	);

extern int cafe_notify_wait
	(
	void
	);

/******************************************************************************
*
* cafe_islocked - returns true if the cafe lock is held
*
* RETURNS: TRUE if the lock is held, otherwise FALSE
*
* ERRNO: N/A
*/

extern bool cafe_islocked(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INClock_h */
