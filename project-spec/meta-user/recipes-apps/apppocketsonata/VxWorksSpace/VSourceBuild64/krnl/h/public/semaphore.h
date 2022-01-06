/* semaphore.h - header for POSIX 1003.1b semaphore synchronization */

/*
 * Copyright (c) 1993-1994, 1999, 2003, 2005, 2010-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01j,15dec11,jpb  Moved SEM_VALUE_MAX and SEM_NSEMS_MAX to limits.h
01i,29apr10,pad  Moved extern C statement after include statements.
01h,22aug05,kk   moved kernel specific protoypes here
01g,02aug05,kk   move SEM_NSEMS_MAX SEM_VALUE_MAX from semaphoreCommon.h to here
01f,05dec03,m_s  code-inspection changes
01e,310ct03,m_s  moved the descriptor structure to private header file
                 ported to Base 6
01d,12mar99,elg  include private header to get semPxLibInit() (SPR 20532).
01c,08apr94,dvs  added pragma for gnu960 alignment.
01b,05jan94,kdl	 changed sem_t "close" field to "refCnt"; general cleanup.
01a,06apr93,smb	 written
*/

#ifndef __INCsemaphoreh
#define __INCsemaphoreh

/* includes */

/* defines */

/* typedefs */

/* the semaphore descriptor for kernel apps */

typedef void * sem_t;

/* include the common header file after defining the semaphore descriptor */

#include <semaphoreCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

/* others are in semaphoreCommon.h */

extern int      sem_init     (sem_t *, int, unsigned int);

#ifdef __cplusplus
}
#endif

#endif /* __INCsemaphoreh */
