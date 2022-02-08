/* usrDebugAgent.c - VxWorks Application Mode Agent module */

/*
 * Copyright (c) 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
17aug15,elp  Only print starting message if initialization succeeded.
15jul15,elp  Pass config string when starting agent (US60628). 
06mar15,f_l  Renamed Debug Agent to Application Mode Agent
05nov14,rlp  Fixed RTP dependencies (V7COR-1643)
05nov14,vhe  Fixed message.
20oct14,vhe  Created for new debug agent start mechanism (US36858)
*/

#include <vxWorks.h>
#include <sysDbgLib.h>
#include <debugAgent.h>

/* locals */

LOCAL BOOL debugAgentStarted = FALSE;

/******************************************************************************
*
* debugAgentStart - Start of the debug agent
*
* Start the debug agent manually or programmatically. 
* When the debug agent is included in the VxWorks image but not 
* started at boot, this routine can be called manually or
* programmatically to start the agent at any time. 
*
*
* RETURNS : OK or ERROR
*
*/
STATUS debugAgentStart 
    (
    char * config     /* configuration string */ 
    ) 
    {
    if (debugAgentStarted) 
	{
 	(void) printf ("Application Mode Agent already started.\n"); 
	return ERROR; 
	}

#ifdef	INCLUDE_RTP
    tcf_init_rtp_funcbind();
#endif	/* INCLUDE_RTP */

    tcfLibInit (DEBUG_AGENT_TASK_PRIORITY); /* Initialize TCF library */
    tcfServicesInit ();   /* Register subsystem services */
    
    /* Start the TCF agent: verbosity is TRUE: message is printed */

    tcfLibStart ((config == NULL) ? DEBUG_AGENT_CONFIG : config,
                 (unsigned int * ) &debugAgentStarted, TRUE);

    return OK; 
    }

/******************************************************************************
*
* tcfLibCheckStart - Detection of TCF initialization and start
*
* When the debug agent is included in VxWorks, it can be configured to be 
* started automatically (through the INCLUDE_DEBUG_AGENT_START component), 
* dynamically (through the system debug flag) or not started at all. 
* This routine checks the configuration and eventually initializes the TCF 
* library and start the TCF tools on target.
*
* RETURNS : N/A
*
* NOMANUAL
*/
void tcfLibCheckStart (void) {
#ifndef INCLUDE_DEBUG_AGENT_START
    if (sysDebugModeGet ())
#endif
	{    
	if (debugAgentStarted) 
	    {
	    (void) printf ("Application Mode Agent already started.\n"); 
	    }

#ifdef	INCLUDE_RTP
	tcf_init_rtp_funcbind();
#endif	/* INCLUDE_RTP */

	tcfLibInit (DEBUG_AGENT_TASK_PRIORITY); /* Initialize TCF library */
	tcfServicesInit ();   /* Register subsystem services */ 
       
       /* Start the TCF agent: verbosity is FALSE no message is printed */

	tcfLibStart (DEBUG_AGENT_CONFIG, (unsigned int * ) &debugAgentStarted,
		     FALSE);
	}
}

#ifdef INCLUDE_DEBUG_AGENT_BANNER
/******************************************************************************
*
* usrDebugAgentBannerInit - register the debug agent banner with usrBanner
*
* Add agent specific data to the VxWorks banner.
*
* RETURNS : N/A
*
* NOMANUAL
*/

void usrDebugAgentBannerInit (void)
    {
#ifdef INCLUDE_DEBUG_AGENT_START
    (void) bannerItemAdd     ("  Application Mode Agent", "Started (always)");
#else 
    if (sysDebugModeGet ())
	{
	(void) bannerItemAdd ("  Application Mode Agent", 
			      "Started (boot flag)");
	}
    else
	{
	(void) bannerItemAdd ("  Application Mode Agent", "Not started");
	}
#endif
    }
#endif
