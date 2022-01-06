/* sys/unistd.h - RTP POSIX standard feature macro file */

/*
* Copyright (c) 2006, 2014 Wind River Systems, Inc.
*
* The right to copy, distribute or otherwise make use of this software
* may be licensed only pursuant to the terms of an applicable Wind River
* license agreement.
*/
                                                                                
/*
modification history
--------------------
14oct14,jpb  V7COR-1642: update posix barrier support
14aug06,tcr  detect POSIX trace at runtime
05jul06,jln  defined _POSIX_THREAD_SPORADIC_SERVER as 200112L
18jun06,pcm  added _POSIX_26_VERSION
29mar06,pad  Defined _POSIX2_C_BIND as 200112L (SPR 119716).
15mar06,mil  Added comment on _SPORADIC_SERVER macros.
22feb06,pad  Thread sporadic server is not yet a supported option.
30jan06,mil  Created from h/unistd.h for namespace isolation.
*/

#ifndef __INCsysunistdh
#define __INCsysunistdh

#ifdef __cplusplus
extern "C" {
#endif


/* POSIX version info */

#define _POSIX_VERSION                  200112L /* IEEE 1003.1-2001 */
#define _POSIX_AEP_REALTIME_CONTROLLER  200312L /* IEEE 1003.13-2003 */
#define _POSIX_AEP_REALTIME_LANG_C99            /* IEEE 1003.13-2003 */
#define _XOPEN_VERSION                  600     /* per PSE52 profile only */
#define _POSIX_26_VERSION               200312L /* IEEE 1003.26-2003 */

/*
 * Constants for Options and Option Groups.
 *
 * A value of -1 indicates that the option is not supported.
 * A value of 0 indicates that a call to sysconf(), pathconf() or fpathconf()
 * is required in order to find out whether the option is actually supported.
 * A value of 200112L indicates that the option is always supported.
 *
 * Note on _POSIX_SPORADIC_SERVER and _POSIX_THREAD_SPORADIC_SERVER
 * 
 * The size of the structure sched_param may change depending on the
 * SPORADIC_SERVER options.  If either _POSIX_SPORADIC_SERVER or 
 * _POSIX_THREAD_SPORADIC_SERVER is defined, extra members will 
 * be present in struct sched_param which is currently shared 
 * by the kernel and user code.  The size of pthread_attr_t, which 
 * is also shared, may change as well.  Hence if _POSIX_SPORADIC_SERVER or 
 * _POSIX_THREAD_SPORADIC_SERVER option is to be turned on, the impact to 
 * the kernel side will need to be evaluated.  
 *
 * _POSIX_THREAD_SPORADIC_SERVER is now turned on in user side (RTP) starting 
 * from VxWorks 6.4, but the POSIX threads in kernel domain have not supported 
 * _POSIX_THREAD_SPORADIC_SERVER yet. This implies that sched_param structure
 * is different between POSIX threads in RTPs and POSIX threads in kernel.
 * However, there is no need to share the sched_param for Kernel and RTP 
 * threads at this point. 
 */

#define _POSIX_ADVISORY_INFO		-1
#define _POSIX_ASYNCHRONOUS_IO		200112L
#define _POSIX_BARRIERS			200112L
#define _POSIX_CHOWN_RESTRICTED		1
#define _POSIX_CLOCK_SELECTION		200112L
#define _POSIX_CPUTIME			-1
#define _POSIX_FSYNC			200112L
#define _POSIX_JOB_CONTROL		-1
#define _POSIX_IPV6			-1
#define _POSIX_MAPPED_FILES		200112L
#define _POSIX_MEMLOCK			200112L
#define _POSIX_MEMLOCK_RANGE		200112L
#define _POSIX_MEMORY_PROTECTION	200112L
#define _POSIX_MESSAGE_PASSING		200112L
#define _POSIX_MONOTONIC_CLOCK		200112L
#define _POSIX_NO_TRUNC			1
#define _POSIX_PRIORITIZED_IO		-1
#define _POSIX_PRIORITY_SCHEDULING	-1
#define _POSIX_RAW_SOCKETS		-1
#define _POSIX_READER_WRITER_LOCKS	-1
#define _POSIX_REALTIME_SIGNALS		200112L
#define _POSIX_REGEXP			-1
#define _POSIX_SAVED_IDS		-1
#define _POSIX_SEMAPHORES		200112L
#define _POSIX_SHARED_MEMORY_OBJECTS	200112L
#define _POSIX_SHELL			-1
#define _POSIX_SPAWN			-1
#define _POSIX_SPIN_LOCKS		-1
#define _POSIX_SPORADIC_SERVER		-1      /* see notes above */
#define _POSIX_SYNCHRONIZED_IO		200112L
#define _POSIX_THREAD_ATTR_STACKADDR	200112L
#define _POSIX_THREAD_ATTR_STACKSIZE	200112L
#define _POSIX_THREAD_CPUTIME		200112L
#define _POSIX_THREAD_PRIO_INHERIT	200112L
#define _POSIX_THREAD_PRIO_PROTECT	200112L
#define _POSIX_THREAD_PRIORITY_SCHEDULING	200112L
#define _POSIX_THREAD_PROCESS_SHARED	-1
#define _POSIX_THREAD_SAFE_FUNCTIONS	200112L	/* per PSE52 profile only */
#define _POSIX_THREAD_SPORADIC_SERVER	200112L /* see notes above */
#define _POSIX_THREADS			200112L	/* per PSE52 profile only */
#define	_POSIX_TIMEOUTS			200112L
#define	_POSIX_TIMERS			200112L
#define _POSIX_TRACE			0
#define _POSIX_TRACE_EVENT_FILTER	0
#define _POSIX_TRACE_INHERIT		-1
#define	_POSIX_TRACE_LOG		0
#define _POSIX_TYPED_MEMORY_OBJECTS	-1
/* _POSIX_VDISABLE is unsupported but may not be defined as -1 (POSIX.1 2001) */
#define _POSIX_V6_ILP32_OFF32		-1
#define _POSIX_V6_ILP32_OFFBIG		200112L
#define _POSIX_V6_LP64_OFF64		-1
#define _POSIX_V6_LPBIG_OFFBIG		-1

#define	_POSIX2_C_BIND			200112L
#define	_POSIX2_C_DEV			200112L
#define	_POSIX2_CHAR_TERM		-1
#define	_POSIX2_FORT_DEV		-1
#define	_POSIX2_FORT_RUN		-1
#define	_POSIX2_LOCALEDEF		-1
#define _POSIX2_PBS			-1
#define _POSIX2_PBS_ACCOUNTING		-1
#define _POSIX2_PBS_CHECKPOINT		-1
#define _POSIX2_PBS_LOCATE		-1
#define _POSIX2_PBS_MESSAGE		-1
#define _POSIX2_PBS_TRACK		-1
#define _POSIX2_SW_DEV			200112L
#define _POSIX2_UPE			-1

#define	_XBS5_ILP32_OFF32		-1
#define	_XBS5_ILP32_OFFBIG		-1
#define	_XBS5_LP64_OFF64		-1
#define	_XBS5_LPBIG_OFFBIG		-1

/* _XOPEN_CRYPT is unsupported */
/* _XOPEN_ENH_I18N is unsupported but may not be defined as -1 (POSIX.1 2001) */
/* _XOPEN_LEGACY is unsupported */
#define	_XOPEN_REALTIME			200112L	/* per PSE52 profile only */
#define	_XOPEN_REALTIME_THREADS		200112L	/* per PSE52 profile only */
/* _XOPEN_SHM is unsupported but may not be defined as -1 (POSIX.1 2001) */
/* _XOPEN_STREAMS is unsupported */
/* _XOPEN_UNIX is unsupported */


/* Constants for confstr() */

#define _CS_PATH				0
#define _CS_POSIX_V6_ILP32_OFF32_CFLAGS		1
#define _CS_POSIX_V6_ILP32_OFF32_LDFLAGS 	2
#define _CS_POSIX_V6_ILP32_OFF32_LIBS		3
#define _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS	4
#define _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS	5
#define _CS_POSIX_V6_ILP32_OFFBIG_LIBS		6
#define _CS_POSIX_V6_LP64_OFF64_CFLAGS		7
#define _CS_POSIX_V6_LP64_OFF64_LDFLAGS		8
#define _CS_POSIX_V6_LP64_OFF64_LIBS		9
#define _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS	10
#define _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS	11
#define _CS_POSIX_V6_LPBIG_OFFBIG_LIBS		12
#define _CS_POSIX_V6_WIDTH_RESTRICTED_ENVS	13
#define _CS_XBS5_ILP32_OFF32_CFLAGS		14
#define _CS_XBS5_ILP32_OFF32_LDFLAGS 		15
#define _CS_XBS5_ILP32_OFF32_LIBS		16
#define _CS_XBS5_ILP32_OFF32_LINTFLAGS		17
#define _CS_XBS5_ILP32_OFFBIG_CFLAGS		18
#define _CS_XBS5_ILP32_OFFBIG_LDFLAGS		19
#define _CS_XBS5_ILP32_OFFBIG_LIBS		20
#define _CS_XBS5_ILP32_OFFBIG_LINTFLAGS		21
#define _CS_XBS5_LP64_OFF64_CFLAGS		22
#define _CS_XBS5_LP64_OFF64_LDFLAGS		23
#define _CS_XBS5_LP64_OFF64_LIBS		24
#define _CS_XBS5_LP64_OFF64_LINTFLAGS		25
#define _CS_XBS5_LPBIG_OFFBIG_CFLAGS		26
#define _CS_XBS5_LPBIG_OFFBIG_LDFLAGS		27
#define _CS_XBS5_LPBIG_OFFBIG_LIBS		28
#define _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS		29


#ifdef __cplusplus
}
#endif

#endif /* __INCsysunistdh */
