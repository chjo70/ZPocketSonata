/* pthreadCommon.h - common header for user-side POSIX threads (pthreads) */
 
/*
 * Copyright (c) 2004, 2006 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */
 
/*
modification history
--------------------
01i,16feb06,pes  Removed pthread_attr_t include. Applications needing
		 pthread_attr_t definition should now include
		 base/b_pthread_attr_t.h
01h,29jan06,mil  Updated for POSIX namespace conformance.
01g,06jan06,gls  added pthread_attr_t
01f,09sep04,pad  created.
*/
 
#ifndef __INCpthreadCommonh
#define __INCpthreadCommonh

#if defined(__cplusplus)
extern "C" {
#endif	/* __cplusplus */

/*
 * The following set of macros ("Compile-Time Symbolic Constants") corresponds
 * to the supported set of POSIX set features supported for applications that
 * the kernel needs to know about.
 */

#define PTHREAD_CANCEL_ASYNCHRONOUS	0
#define PTHREAD_CANCEL_DEFERRED		1

#if defined(__cplusplus)
}
#endif	/* __cplusplus */

#endif /* __INCpthreadCommonh */
