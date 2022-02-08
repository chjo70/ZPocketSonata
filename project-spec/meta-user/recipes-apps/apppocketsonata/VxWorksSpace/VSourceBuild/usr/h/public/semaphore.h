/* semaphore.h - user-level header for POSIX semaphores */

/*
 * Copyright (c) 2003, 2005-2007, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01k,29jul10,pad  Moved extern C statement after include statements.
01j,21jan09,cww  Made sem_timedwait prototype common (WIND00113044)
01i,09aug07,pad  Used the new _Vx_BOOL type instead of _Bool (different size,
                 defect 100623).
01h,24jul06,jpb  Removed duplicate definition of sem_t.
01g,13mar06,kk   added _Restrict to POSIX APIs
01f,27jan06,mil  Updated for POSIX namespace conformance.
01e,25jan06,yvp  sem_timedwait prototype changed to conform to Posix std.
01d,05jan06,yvp  Added prototype for sem_timedwait().
01c,22aug05,kk   moved user specific prototypes here
01b,05dec03,m_s  code-inspection changes
01a,31oct03,m_s  Written
*/

#ifndef __INCsemaphoreh
#define __INCsemaphoreh

/* includes */

#include <sys/cdefs.h>		/* for _Restrict */

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

#include <objLib.h>
#include <semPxSysCall.h>

#else   /* _POSIX_xxx_SOURCE */

#include <types/vxWind.h>
#include <base/b_BOOL.h>

struct timespec;

#endif  /* _POSIX_xxx_SOURCE */

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* typedefs */

/* semaphore descriptor for users */

#if defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE) || \
    defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#undef semHandle
#undef named
#endif

typedef struct
    {
    _Vx_OBJ_HANDLE  semHandle;
#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
    BOOL           named;
#else
    _Vx_BOOL          named;
#endif
    } sem_t;

#ifdef __cplusplus
}
#endif

/* include the common header file after defining the descriptor */

#include <semaphoreCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/* function declaration */

/* other prototypes in semaphoreCommon.h */

extern int      sem_init     (sem_t *, int, unsigned);

#ifdef __cplusplus
}
#endif

#endif /* __INCsemaphoreh */
