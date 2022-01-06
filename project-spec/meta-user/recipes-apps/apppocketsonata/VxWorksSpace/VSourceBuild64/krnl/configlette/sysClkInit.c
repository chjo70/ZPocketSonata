/* sysClkInit.c - initialize the system clock */

/*
 * Copyright (c) 1988, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
/*
modification history
--------------------
03mar14,cww  ignore return values (US29395)
21apr98,ms   take from usrConfig.c
*/ 

/*
DESCRIPTION
Initialize the system clock
*/  

/******************************************************************************
*
* usrClock - user-defined system clock interrupt routine.
*/

void usrClock (void)
    {
    tickAnnounce();
    }

/******************************************************************************
*
* sysClkInit - initialize the system clock
*/ 

void sysClkInit (void)
    {
    /*
     * set up the system timer - there is no recourse if any of these fail, so
     * ignore the return values
     */

    (void) sysClkConnect ((FUNCPTR) usrClock, 0);  /* connect clock ISR */
    (void) sysClkRateSet (SYS_CLK_RATE);           /* set system clock rate */
    (void) sysClkEnable ();                        /* start it */
    }

