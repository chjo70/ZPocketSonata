/* rtpPthreadLibP.h - private header for user-side POSIX threads (pthreads) */
 
/* Copyright 2004-2006 Wind River Systems, Inc. */
 
/*
modification history
--------------------
01b,25aug06,pad  Removed PTHREAD_INFO type because no longer necessary.
01a,07sep04,pad  Created to share common type and macro definitions.
*/

/*
DESCRIPTION
This header file holds information that must be known to both the user-side
library for POSIX threads and the support code for this library located in the
kernel. These information, type definitions and macro definitions, represents
a convention between the two sides.
*/
 
#ifndef __INCrtpPthreadLibPh
#define __INCrtpPthreadLibPh

#if defined(__cplusplus)
extern "C" {
#endif	/* __cplusplus */

/* defines */

/*
 * POSIX defines zero as the return value on success for many routines. This
 * macro makes the code more readable.
 * XXX PAD - this likely should no longer be shared.
 */

#define _RETURN_PTHREAD_SUCCESS		0

/* typedefs */

#if defined(__cplusplus)
}
#endif	/* __cplusplus */

#endif /* __INCrtpPthreadLibPh */
