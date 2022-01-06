/* sys/time.h - POSIX.1 time types */

/*
 * Copyright (c) 2005-2006, 2010-2011, 2014-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
*/

/*
modification history
--------------------
03feb16,mst  Removed unsupported function prototypes setitimer() and getitimer()
17dec15,brk  Added inclusion of b_useconds_t.h
25sep14,pad  Added inclusion of sys/cdefs.h for conformance (US44509).
18oct11,jpb  Added settimeofday.
29jul10,pad  Moved extern C statement after include statements.
10feb06,mil  Updated for POSIX namespace conformance (PN). 
14sep05,mcm  Fix for SPR#106575 - suseconds_t should be of type "signed 
             long" per the standard.
17aug05,mcm  Initial version
*/

#ifndef _SYS_TIME_H_
#define _SYS_TIME_H_

/* typedef time_t */
#include <base/b_time_t.h>

/* typedef suseconds_t */
#include <base/b_suseconds_t.h>

/* typedef useconds_t */
#include <base/b_useconds_t.h>

/* typedef struct timeval */
#include <base/b_struct_timeval.h>

/* typedef itimerval */
#include <base/b_struct_itimerval.h>

#include <sys/cdefs.h>          /* for _Restrict */

/*
 * timeval struct is used in select.h, so make sure the inclusion of
 * b_struct_timeval.h above precedes this include.
 */
#include <sys/select.h>         /* for fd_set, FD_* and func prototypes */

 #ifdef  __cplusplus
extern "C" {
 #endif

/* Decrement types for getitimer() and setitimer() */
#define ITIMER_REAL     0       /* real time */
#define ITIMER_VIRTUAL  1       /* process virtual time */
#define ITIMER_PROF     2       /* both process virtual time and when system
                                   is running on behalf of the process. */

int   gettimeofday(struct timeval *_Restrict, void *_Restrict);
int   utimes(const char *, const struct timeval [2]); 

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
int   settimeofday(struct timeval *_Restrict, void *_Restrict);
#endif /* _POSIX_xxx_SOURCE */

#ifdef  __cplusplus
}
#endif

#endif /* _SYS_TIME_H_ */

