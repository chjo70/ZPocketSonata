/* usrSma.c - configuration file for Stop Mode Agent support */

/*
 * Copyright (c) 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
18mar15,f_l  Updated banner alignment for Application Mode Agent.
04nov14,jpb  add header file for _func_printErr (V7COR-910)
24nov14,jmp  Fixed RTP dependency (V7COR-2267).
19nov14,sdt  Added exceptions support (US44279)
13nov14,vhe  Removed extraneous message (V7COR-2203)
04nov14,vhe  Fixed startup messages, added init check (US46081)
30oct14,vhe  Removed duplicate message
21oct14,vhe  Changed start mechanism (US46081)
16jul14,rlp  Written
*/

/*
DESCRIPTION

This library configures and initializes the Stop Mode Agent support
*/

/* Includes */

#include <sysDbgLib.h>
#ifdef INCLUDE_EDR_POLICY_HOOKS
#include <private/edrLibP.h>
#endif /* INCLUDE_EDR_POLICY_HOOKS */
#include <private/fioLibP.h>			/* _func_printErr */

/* extern */

extern STATUS usrSmaDevInit (char * config); /* provided by device configlette */

/* Defines */

#define	STOP_MODE_STACK_ARRAY_SIZE (STOP_MODE_AGENT_STACK_SIZE/ \
				    sizeof(unsigned long))

/* Static */

LOCAL unsigned long	stopModeAgentStackArray [STOP_MODE_STACK_ARRAY_SIZE];

/* locals */

LOCAL BOOL stopModeAgentStarted = FALSE;

/******************************************************************************
*
* stopModeAgentStart - Start the Stop Mode Agent unconditionally 
*
* When the stop mode debug agent is included in VxWorks, but not started 
* automatically, this routine can be used from the Kernel Shell or 
* programmatically to start the stop mode debug agent at any time. 
*
* RETURNS : OK or ERROR
*/
STATUS stopModeAgentStart 
    (
    char * config      /* configuration string */  
    )
    {
    void *	pStackBase;

    if (stopModeAgentStarted)
        {
        printf ("Stop Mode Agent already started.\n"); 
        return ERROR; 
        }
	    
#if     _STACK_DIR == _STACK_GROWS_DOWN
    pStackBase = (caddr_t)&stopModeAgentStackArray
					[STOP_MODE_STACK_ARRAY_SIZE];
    pStackBase = (caddr_t)STACK_ROUND_DOWN (pStackBase);
#else   /* _STACK_DIR == _STACK_GROWS_UP */
    pStackBase = (caddr_t)stopModeAgentStackArray;
    pStackBase = (caddr_t)STACK_ROUND_UP (pStackBase);
#endif  /* _STACK_DIR == _STACK_GROWS_DOWN */

    if (smaInit (pStackBase) == ERROR)
        {
        if (_func_printErr != NULL)
            _func_printErr (
                "usrSmaInit error: smaInit failed\n");
        return ERROR; 
        }

#ifdef INCLUDE_RTP
    if (smaRtpLibInit () == ERROR)
        {
        if (_func_printErr != NULL)
            _func_printErr (
                "usrSmaInit error: smaRtpLibInit failed\n");
        return ERROR; 
        }
#endif  /* INCLUDE_RTP */

#ifdef INCLUDE_EDR_POLICY_HOOKS
    if (edrPolicyHandlerHookAdd (smaExcHandle) == ERROR)
	{
        if (_func_printErr != NULL)
            _func_printErr (
                "usrSmaInit error: smaExcHandle EDR hook add failed\n");
        return ERROR; 
	}
#endif  /* INCLUDE_EDR_POLICY_HOOKS */

    if (usrSmaDevInit (config) == ERROR)
        return ERROR;

    stopModeAgentStarted = TRUE; 

#ifndef INCLUDE_STOP_MODE_AGENT_START
    if (!sysDebugModeGet ())
	printf ("Stop Mode Agent Started. Reboot your system to stop the agent.\n");
#endif 
    return OK; 

    }

/******************************************************************************
*
* usrSmaInit - configure and start the Stop Mode Agent
* 
* One of the 2 start conditions (start component or system debug flag) must 
* be true for the agent to be started. 
*
*/

void usrSmaInit (void)
    {
#ifndef INCLUDE_STOP_MODE_AGENT_START
    if (sysDebugModeGet ())
#endif
	(void) stopModeAgentStart(NULL);
    }

#ifdef INCLUDE_STOP_MODE_AGENT_BANNER
/******************************************************************************
*
* usrSmaBannerInit - register the Stop Mode Agent banner with usrBanner
*
* Add stop mode agent specific data to the VxWorks banner.
*
* RETURNS : N/A
*
* NOMANUAL
*/

void usrSmaBannerInit (void)
    {
#ifdef INCLUDE_STOP_MODE_AGENT_START
    (void) bannerItemAdd     ("         Stop Mode Agent", "Started (always)");
#else 
    if (sysDebugModeGet ())
        {
        (void) bannerItemAdd ("         Stop Mode Agent", 
			      "Started (boot flag)");
        }
    else
        {
        (void) bannerItemAdd ("         Stop Mode Agent", "Not started");
        }
#endif
    }
#endif
