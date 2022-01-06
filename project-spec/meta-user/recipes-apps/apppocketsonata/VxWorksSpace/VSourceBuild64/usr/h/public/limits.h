/* limits.h - RTP POSIX limits header file */

/*
 * Copyright (c) 1991-1994, 2001, 2004-2007, 2010, 2012-2013, 2015
 * Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
31mar16,a_p  Added preliminary support for llvm
05apr16,dlk  Correct comment: PATH_MAX is the maximum pathname length
             _including_ EOS.
07oct15,lau  Corrected the value of LLONG_MIN (V7COR-3575)
19aug15,lau  updated the toolchains specific limits.h to include ICC too (V7COR-3238)
27sep13,h_k  updated IOV_MAX to synch with kernel's.
13jan12,pad  Set SSIZE_MAX appropriately depending on the data model
             (defect 315132).
29jul10,pad  Moved extern C statement after include statements.
01feb07,jpb  Edited check on tool include file (Defect# 85160).
03nov06,pad  Set SSIZE_MAX accordingly to the implementation of the ssize_t
             type (defect #68078/fix #71280).
18sep06,pad  Added TRACE_SYS_MAX in the list of non-provided macros for
             which sysconf() must be used instead.
10aug06,pad  Replaced _TOOL_HEADER macro logic with something more
             straightforward albeit less flexible.
31jul06,jpb  Renamed TOOL_FAMILY to _VX_TOOL_FAMILY for Namespace
             Isolation
08may06,tcr  add trace items
21mar06,pad  Fixed conformance issues with some macro definitions (SPR
             119358)
07feb06,gls  updated RTSIG_MAX and _POSIX_RTSIG_MAX (SPR #117568)
25jan06,pad  Fixed _POSIX_THREAD_KEYS MAX as per the POSIX.1 standard.
20jan06,pad  Set _POSIX_OPEN_MAX to the proper POSIX.1 value.
24oct05,md   changed PATH_MAX count to include null terminator
07sep05,mcm  Fix for SPR#111963 - value of COLL_WEIGHTS_MAX corrected.
19aug05,pad  Fixed spelling mistake in _POSIX_THREAD_THREADS_MAX.
18aug05,kk   updated RTSIG_MAX to 7
12aug05,pad  Removed definition of NGROUPS_MAX. The value should be
             obtained via sysconf(). Updated RTSIG_MAX as per PSE52 profile.
02aug05,kk   update for kernel values
16jul05,pad  Yet more POSIX macro definitions.
02jun05,pad  Added more _POSIX macro definitions.
01mar05,gls  added _POSIX macros definitins from time.h (SPR #105358)
05may04,pad  set NGROUPS_MAX and SSIZE_MAX to, respectively,
             _POSIX_NGROUPS_MAX and _POSIX_SSIZE_MAX (SPR 94100).
07dec01,sn   use toolchain specific limits.h
01may94,kdl  added missing mod hist for 01f.
06dec93,dvs  added POSIX AIO defines.
24sep92,smb  removed POSIX ifdef.
22sep92,rrr  added support for c++
04jul92,jcf  cleaned up.
03jul92,smb  merged ANSI limits
29jul91,rrr  written.
*/

#ifndef __INClimitsh
#define __INClimitsh

#include <types/vxANSI.h>

#if defined(__INTEL_COMPILER)
#include "tool/icc/limits.h"
#elif defined(__DCC__)
#include "tool/diab/limits.h"
#elif defined (__clang__)
#include "tool/llvm/limits.h"
#else
#include "tool/gnu/limits.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Pathname Variable Values */

#if !defined(_POSIX_C_SOURCE)
#define NAME_MAX        _PARM_NAME_MAX	/* max filename length excluding EOS */
#define PATH_MAX        _PARM_PATH_MAX	/* max pathname length including EOS */
#endif

/* Runtime Increasable Values */

#define COLL_WEIGHTS_MAX	_POSIX2_COLL_WEIGHTS_MAX

/* Runtime Invariant Values */

#define AIO_LISTIO_MAX		10
#define AIO_PRIO_DELTA_MAX	254	/* max async IO prio decrease */
#define AIO_MAX			_POSIX_AIO_MAX
#define ARG_MAX			_POSIX_ARG_MAX
#define ATEXIT_MAX		32	/* max num of registered functions */
#define DELAYTIMER_MAX		_POSIX_DELAYTIMER_MAX 
#define HOST_NAME_MAX		_POSIX_HOST_NAME_MAX
#define IOV_MAX			1024	/* max 1K of iov's */
#define LOGIN_NAME_MAX		_POSIX_LOGIN_NAME_MAX
#define MQ_PRIO_MAX		_POSIX_MQ_PRIO_MAX
#define PTHREAD_DESTRUCTOR_ITERATIONS	_POSIX_THREAD_DESTRUCTOR_ITERATIONS
#define PTHREAD_KEYS_MAX	256
#define PTHREAD_STACK_MIN	4096	/* min thread stack size (bytes) */
#define RTSIG_MAX		16	/* max num of signals for apps use */
#define SEM_VALUE_MAX		_POSIX_SEM_VALUE_MAX
#define SIGQUEUE_MAX		_POSIX_SIGQUEUE_MAX
#define STREAM_MAX		20	/* must be same as FOPEN_MAX (stdio.h)*/
#define SYMLOOP_MAX		_POSIX_SYMLOOP_MAX
#define TTY_NAME_MAX		_POSIX_TTY_NAME_MAX
#define TZNAME_MAX		_POSIX_TZNAME_MAX
#define TRACE_NAME_MAX          64
#define TRACE_USER_EVENT_MAX    256
#define TRACE_EVENT_NAME_MAX    64

/*
The following invariants do not have definite limits or corresponds to features
that cannot be supported as per POSIX 1003.1. Use sysconf() to know whether
an invariant value is undefinite, has a finite value different from what POSIX 
1003.1 requires, or is related to an unsupported feature.

CHILD_MAX	-> sysconf (_SC_CHILD_MAX)
MQ_OPEN_MAX	-> sysconf (_SC_MQ_OPEN_MAX)
NGROUPS_MAX	-> sysconf (_SC_NGROUPS_MAX)
OPEN_MAX	-> sysconf (_SC_OPEN_MAX)
PAGE_SIZE	-> sysconf (_SC_PAGE_SIZE)
PAGESIZE	-> sysconf (_SC_PAGESIZE)
PTHREAD_THREAD_MAX -> sysconf (_SC_THREAD_THREADS_MAX)
SEM_NSEMS_MAX	-> sysconf (_SC_SEM_NSEMS_MAX)
SS_REPL_MAX	-> sysconf (_SC_SS_REPL_MAX)
SYMLOOP_MAX	-> sysconf (_SC_SYMLOOP_MAX)
TIMER_MAX	-> sysconf (_SC_TIMER_MAX)
TRACE_SYS_MAX	-> sysconf (_SC_TRACE_SYS_MAX)
*/

/* Maximum Values */

#define	_POSIX_CLOCKRES_MIN	20000000	/* clock resolution (ns) */

/* Minimum Values */

#define _POSIX_AIO_LISTIO_MAX	2	/* num of IO ops in a list IO call */
#define _POSIX_AIO_MAX		1	/* num of outstanding async IO ops */
#define _POSIX_ARG_MAX		4096	/* max length of argument */
#define _POSIX_CHILD_MAX	25	/* max num of processes per real uid */
#define	_POSIX_DELAYTIMER_MAX	32	/* num of timer expiration overruns */
#define _POSIX_HOST_NAME_MAX	255	/* max length of host name */
#define _POSIX_LINK_MAX		8	/* max num of links to a single file */
#define _POSIX_LOGIN_NAME_MAX	9	/* max length of login name */
#define _POSIX_MAX_CANON	255	/* num of bytes in term canon input Q */
#define _POSIX_MAX_INPUT	255	/* max num of bytes in term input Q */
#define _POSIX_MQ_OPEN_MAX	8	/* max num of msg queues in process */
#define _POSIX_MQ_PRIO_MAX	32	/* max number of message priorities */
#define _POSIX_NAME_MAX		14	/* max num bytes in a filename */
#define _POSIX_NGROUPS_MAX	8	/* max num of group IDs per process */
#define _POSIX_OPEN_MAX		20	/* max num of open files per process */
#define _POSIX_PATH_MAX		256	/* max num of bytes in a pathname */
#define _POSIX_PIPE_BUF		512	/* max num of bytes for atomic write */
#define _POSIX_RE_DUP_MAX	255	/* max num repeated BRE occurrences */
#define _POSIX_RTSIG_MAX	8	/* num of reserved RT signals for apps*/
#define _POSIX_SEM_NSEMS_MAX	256	/* max num of semaphores in a process */
#define _POSIX_SEM_VALUE_MAX	32767	/* maximum value of a semaphore */
#define _POSIX_SIGQUEUE_MAX	32	/* max num of queued signals */
#define _POSIX_SSIZE_MAX	32767	/* storage value for ssize_t */
#define _POSIX_SS_REPL_MAX	4	/* max replenishment (sporadic sched) */
#define _POSIX_STREAM_MAX	8	/* max num of open streams in process */
#define _POSIX_SYMLINK_MAX	255	/* max num of bytes in symbolic link */
#define _POSIX_SYMLOOP_MAX	8	/* max num of symlinks depth */
#define _POSIX_THREAD_DESTRUCTOR_ITERATIONS 4 /* max attempts to destroy
						 thread specific data */
#define _POSIX_THREAD_KEYS_MAX	128	/* max num of data keys per process */
#define _POSIX_THREAD_THREADS_MAX 64	/* max num of threads per process */
#define	_POSIX_TIMER_MAX	32	/* max num of timers per process */
#define	_POSIX_TRACE_EVENT_NAME_MAX	30 /* length of a trace event name */
#define	_POSIX_TRACE_NAME_MAX	8	/* length of a trace stream name */
#define	_POSIX_TRACE_SYS_MAX	8	/* max num of concurrent trace streams*/
#define	_POSIX_TRACE_USER_EVENT_MAX	32 /* max user event types */
#define _POSIX_TTY_NAME_MAX	9	/* max num bytes in term device name */
#define _POSIX_TZNAME_MAX	6	/* max num of bytes in timezone name */

#define	_POSIX2_COLL_WEIGHTS_MAX	2 /* max num of weights for LC_COLLATE*/

#define	_XOPEN_IOV_MAX		16	/* max num of iovec struct in a RTP */

/* Numerical Limits */

#define LLONG_MIN	(-9223372036854775807LL-1LL)
#define LLONG_MAX	+9223372036854775807LL
#define ULLONG_MAX	18446744073709551615ULL
#ifndef _WRS_CONFIG_LP64
#define SSIZE_MAX	INT_MAX		/* max value for 32-bit ssize_t */
#else
#define SSIZE_MAX	LONG_MAX	/* max value for 64-bit ssize_t */
#endif /* _WRS_CONFIG_LP64 */

#ifdef __cplusplus
}
#endif

#endif /* __INClimitsh */
