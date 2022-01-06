/* timerSysCall.h - POSIX timer system call definitions */

/*
 * Copyright (c) 2003-2008, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01h,27apr10,jpb  Updated timerCtl prototype to fix mismatch.
01g,17mar10,cww  LP64 adaptation
01f,09feb10,jpb  Updated clockCtl and timerCtl prototype.
01e,25feb08,jpb  Added new field TIMER_CTL_SIGEVENT_GET so user-side can
                 retrieve sigevent info from kernel.
01d,26jan06,yvp  Added CLOCK_CTL_CMD enum and clockNanosleepArgs.
                 Updated copyright + #include now with angle-brackets.
01c,22apr04,dcc  added 'context' parameter to _timer_open().
01b,02dec03,ans  code inspection comments.
01a,02oct03,ans  written
*/

#ifndef __INCtimerSysCallh
#define __INCtimerSysCallh

#include <vxWorks.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

/* command codes for the timerCtl() system call */

typedef enum
    {
    TIMER_CTL_GETTIME,
    TIMER_CTL_SETTIME,
    TIMER_CTL_GETOVERRUN,
    TIMER_CTL_MODIFY,
    TIMER_CTL_GETSIGEVENT
    } TIMER_CTL_CMD;

/* command codes for the clockCtl() system call */

typedef enum
    {
    CLOCK_CTL_NANOSLEEP
    } CLOCK_CTL_CMD;

/* argument structures for the clockCtl system call */

struct clockNanosleepArgs	/* CLOCK_CTL_NANOSLEEP */
    {
    int flags;
    const struct timespec * rqtp;
    struct timespec * rmtp;
    };

/* system call function prototypes */

extern STATUS	  timerCtl      (TIMER_CTL_CMD cmdCode, OBJ_HANDLE timerHandle, 
                                 void * pArgs, size_t argSize);
extern OBJ_HANDLE _timer_open   (const char * name, int mode, clockid_t clockId,
                                 struct sigevent * evp, void * context);

extern STATUS	  clockCtl	(clockid_t clock_id, CLOCK_CTL_CMD cmdCode,
				 void * pArgStruct, size_t * pArgSize);

#ifdef __cplusplus
}
#endif

#endif /* __INCtimerSysCallh */
