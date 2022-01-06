/* usrPosixSc.c - POSIX system call initialization */

/* Copyright 2004, 2014-2015 Wind River Systems, Inc. */

/*
modification history
--------------------
24mar15,txu   Added call to umaskScLibInit() (US55492)
04jul14,pad   Added call to pxUserGroupScLibInit() (US40207).
01sep04,job   Renamed posixScLib to mqSemPxScLib
23aug04,job   written.
*/

/*
DESCRIPTION
This file configures POSIX system call support based on the level of 
POSIX support configured into the system.

SEE ALSO: usrExtra.c

NOMANUAL
*/

#ifndef  __INCusrPosixSc
#define  __INCusrPosixSc

/* includes */

#include <vxWorks.h>

extern void mqSemPxScInit (void);
extern int timerScLibInit (void);
extern int clockScLibInit (void);
extern int schedPxScLibInit (void);
extern STATUS pxUserGroupScLibInit (void);
extern STATUS umaskScLibInit(void);

/*******************************************************************************
*
* usrPosixScInit - initialize various POSIX system call interfaces
*
* RETURNS: OK or ERROR.
*
* SEE ALSO:
*/

void usrPosixScInit (void)
    {
#ifdef INCLUDE_POSIX_CLOCKS
    (void)clockScLibInit();
#endif /* INCLUDE_POSIX_CLOCKS */

#ifdef INCLUDE_POSIX_TIMERS
    (void)timerScLibInit();
#endif /* INCLUDE_POSIX_TIMERS */

#ifdef INCLUDE_POSIX_SCHED
    (void)schedPxScLibInit();
#endif /* INCLUDE_POSIX_SCHED */

#if defined (INCLUDE_POSIX_MQ) || defined (INCLUDE_POSIX_SEM)
    /* install POSIX message queue & semaphore system call handlers */
    mqSemPxScInit();	
#endif /* defined (INCLUDE_POSIX_MQ) || defined (INCLUDE_POSIX_SEM) */ 

#ifdef INCLUDE_POSIX_USER_GROUP
    /* System call handlers for setuid family of functions */

    (void)pxUserGroupScLibInit();
#endif /* INCLUDE_POSIX_USER_GROUP */

#ifdef INCLUDE_POSIX_UMASK
    /* System call handler for umask() */

    (void)umaskScLibInit();

#endif /* INCLUDE_POSIX_UMASK */
    }

#endif /* __INCusrPosixSc */
