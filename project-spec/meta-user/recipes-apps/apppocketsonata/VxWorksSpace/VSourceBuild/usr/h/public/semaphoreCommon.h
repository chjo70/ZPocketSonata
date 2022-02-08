/* semaphoreCommon.h - POSIX usr/kernel shared semaphore header file */

/*
 * Copyright (c) 2003, 2005-2006, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01j,28apr10,pad  Moved extern C statement after include statements.
01i,21jan09,cww  Made sem_timedwait prototype common (WIND00113044)
01h,14aug06,pad  Removed inclusion of limits.h for the RTP side (namespace
		 isolation).
01g,10mar06,kk   added _Restrict keyword for POSIX for the user side.
01f,06feb06,mil  Updated for POSIX namespace conformance.
01e,05jan06,jln  added definition of _VX_PX_SEM_NAME_MAX and _VX_PX_SEM_PATH_MAX
01d,22aug05,kk   moved sem_init() to RTP and kernel specific semaphore.h files
01c,02aug05,kk   move SEM_NSEMS_MAX  and SEM_VALUE_MAX into kernel 
		 semaphore.h, user side has these in limits.h
01b,18nov03,m_s  code-inspection changes
01a,31oct03,m_s  Written
*/

#ifndef __INCsemaphoreCommonh
#define __INCsemaphoreCommonh

/* includes */

#include <fcntl.h>

#ifndef _WRS_KERNEL
#include <sys/cdefs.h>          /* for _Restrict */
#else
#include <limits.h>
#include <base/b_struct_timespec.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define SEM_FAILED    ((sem_t *) -1)   /* failure for sem_open */

/* 
 * _VX_PX_SEM_NAME_MAX is the maximum number of bytes in a 
 * filename (not including terminating null)
 */

#define _VX_PX_SEM_NAME_MAX 	255	  

/* 
 * _VX_PX_SEM_PATH_MAX is the maximum number of bytes in a 
 * pathname, including the terminating null character 
 */

#define _VX_PX_SEM_PATH_MAX	255      

/* typedefs */

/* function declarations */

/* sem_init() is in semaphore.h */

extern int      sem_destroy  (sem_t *);
extern sem_t *  sem_open     (const char *, int, ...);
extern int      sem_close    (sem_t *);
extern int      sem_unlink   (const char *);
extern int      sem_wait     (sem_t *);
extern int      sem_trywait  (sem_t *);
extern int      sem_post     (sem_t *);

#ifdef _WRS_KERNEL
extern int      sem_getvalue (sem_t *, int *);
extern int	sem_timedwait (sem_t *, const struct timespec *);
#else
extern int      sem_getvalue (sem_t *, int * _Restrict);
extern int	sem_timedwait (sem_t * _Restrict, 
                               const struct timespec * _Restrict);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCsemaphoreCommonh */
