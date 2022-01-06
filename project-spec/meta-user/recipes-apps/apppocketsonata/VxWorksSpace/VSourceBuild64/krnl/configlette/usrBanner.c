/* usrBanner.c - print the startup banner */

/*
 * Copyright (c) 1998, 2001-2002, 2004-2005, 2007-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
21jul15,vhe  Fixed banner alignment (F1122)
18mar15,f_l  Updated banner alignment for Application Mode Agent.
07may15,h_k  temporary pend tLogTask while outputting the banner. (V7COR-2909)
02jun14,h_k  changed the kernelVersion() to the Core Kernel version.
             (V7COR-1067)
27may15,dlk  Fix compiler warning in 64-bit icc builds.
18mar15,f_l  Updated banner alignment for Application Mode Agent.
24mar14,pcs  updated to use sysMemSizeGet to get the memory size for vx7 bsps.
10feb14,cww  removed use of sysMemTop for non-legacy builds (US16511)
	     added CPU information
06feb14,cww  Updated runtime name to VxWorks 7 (VXW7-1662)
24oct13,cww  Moved BSP version into logo
08oct13,cww  Removed unused local variable physMemTop
15aug13,cww  Removed dependencies on non core packages
09jul13,cww  Made this the default banner on startup
28nov12,bvu  Add Usable RAM top and OS Memory size outputs
25mar11,rlp  Added SSL support.
16nov10,rlp  Fixed LP64 build warning.
22oct10,rlp  Modified WDB banner message (WIND00227819).
13sep10,v_r  Fixed build warning.
28may10,jpb  Added more support for LP64 adaptation.
20may10,rlp  Removed warnings.
23sep09,pad  Changed memory size computation for VxWorks 64-bit.
07may09,jmp  Adapted for 64-bit support.
             Modified banner to also display memory size in MBytes.
24feb09,rlp  Removed unsupported INCLUDE_WDB_COMM_NETROM components.
28jul08,dbt  Added support for WDB MIPC.
16mar07,v_r  Account for HITACHI_SH_KERNEL_ON_SDRAM in usrBanner().
04jun05,dbt  Added support for WDB TIPC.
29jul04,md   Added ED&R info; SPR 78837
29jan02,g_h  Added WDB_COMM_VTMD as a possible WDB_COMM_TYPE_STR
12sep01,jhw  Added WDB_PIPE as a possible WDB_COMM_TYPE_STR
             Fixed display alignment of WDB Comm Type.
21aug01,jhw  Added WDB_COMM_TYPE to banner (SPR 9559)
02jun98,ms   written
*/

/*
DESCRIPTION

This configlette outputs the startup banner
*/

#include <vsbConfig.h>
#include <stdio.h>
#include <sysLib.h>
#include <kernelLib.h>
#include <semLib.h>
#include <private/logLibP.h>

#ifdef _WRS_CONFIG_SMP
#include <base/b_cpuset_t.h>
#endif

/* globals */

void (*_func_bannerLogo)(void) = NULL;

/* function prototypes */

STATUS	   bannerItemAdd	(char * name, char * value);
LOCAL void printBannerLogo	(void);

#define NUM_BANNER_ITEMS	 8

struct bannerItem
    {
    char * name;
    char * value;
    };

LOCAL struct bannerItem itemPool[NUM_BANNER_ITEMS];
LOCAL int 		numItems = 0;

#ifdef _WRS_CONFIG_SMP
LOCAL int numSetBits (cpuset_t i)
    {
    i = i - ((i >> 1) & 0x55555555);
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
    return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
    }
#endif

/******************************************************************************
*
* usrBanner - print the banner information to the Target Shell
*
* This routine prints out the banner information to the Target Shell.
*
* RETURNS :
* None
*
* NOMANUAL
*/
 
void usrBanner (void)
    {
    int    i;
    UINT64 memSize; /* memory size in bytes */
    unsigned long nMBytes; /* memory size in megabytes */
#ifdef _WRS_CONFIG_SMP
    int    cpusConfigured;
    int    cpusEnabled;
#endif /* _WRS_CONFIG_SMP */

#ifdef	INCLUDE_LOGGING
    PEND_LOG_MSG	pendLogMsg;
    _Vx_ticks_t		timeout;
    BOOL		logTaskIsPended = FALSE;

    /* create an empty binary semaphore */

    pendLogMsg.semId = semBCreate (SEM_Q_FIFO, SEM_EMPTY);

    if (pendLogMsg.semId != SEM_ID_NULL)
	{
	/* set three seconds time out */

	timeout = sysClkRateGet () * 3;

	/* send a meesage to tLogTask to synch up */

	pendLogMsg.msgType = PEND_LOG_MSG_TYPE;

	if (msgQSend (logMsgQId, (char *) &pendLogMsg, sizeof (pendLogMsg),
	    timeout, MSG_PRI_NORMAL) == OK)
	    {
	    logTaskIsPended = TRUE;

	    /* wait for binary semaphore sent by tLogTask */

	    (void) semTake (pendLogMsg.semId, timeout);
	    }
	}
#endif	/* INCLUDE_LOGGING */

    memSize = sysMemSizeGet();

    if (_func_bannerLogo != NULL)
	_func_bannerLogo ();
    else
	printBannerLogo ();

    printf ("                   Board: %s\n", sysModel ());
#ifdef _WRS_CONFIG_SMP
    cpusConfigured = vxCpuConfiguredGet ();
    cpusEnabled    = numSetBits (vxCpuEnabledGet());

    if (cpusConfigured == cpusEnabled)
	{
	printf ("               CPU Count: %d\n", cpusConfigured);
	}
    else
	{
	printf ("               CPU Count: %d (%d enabled)\n", cpusConfigured,
		cpusEnabled);
	}
#endif /* _WRS_CONFIG_SMP */

    nMBytes = (unsigned long)(memSize >> 20);

    printf ("          OS Memory Size: ");
    if (nMBytes > 0)
        {
        if ((UINT32)memSize & 0xFFFFF) /* exact multiple of 1MB? */
            printf ("~");
        printf ("%luMB", nMBytes);
        }
    printf ("\n");

    printf ("        ED&R Policy Mode: %s\n",
#ifdef INCLUDE_EDR_SYSDBG_FLAG
	    edrIsDebugMode() ? "Lab" : "Deployed");
#else
	    "Permanently Deployed");
#endif /* INCLUDE_EDR_SYSDBG_FLAG */

    i = 0;

    while ((itemPool[i].name != NULL) && (i < numItems))
	{
	printf ("%16s: %s\n", itemPool[i].name,	itemPool[i].value);
	i++;
	}

    printf ("\n");

#ifdef	INCLUDE_LOGGING
    if (logTaskIsPended)
	{
	/* send a binary semaphore to tLogTask */

	(void) semGive (pendLogMsg.semId);

	(void) semDelete (pendLogMsg.semId);
	}
#endif	/* INCLUDE_LOGGING */
    }

/******************************************************************************
*
* bannerItemAdd - add information to be displayed in the banner
*
* This routine accepts two strings that will be used to construct a
* "name: value" line that will be displayed as part of the banner.
* The caller must ensure that the string pointers are valid at the time
* when the banner is printed.
*
* RETURNS : OK if the line was successfully added, ERROR if the
*	    pre-allocated storage space for the pointers have been exhausted
*
* NOMANUAL
*/

STATUS bannerItemAdd
    (
    char * name,
    char * value
    )
    {
    if (numItems == NUM_BANNER_ITEMS)
	return ERROR;

    itemPool[numItems].name = name;
    itemPool[numItems].value = value;
    numItems++;

    return OK;
    }

/******************************************************************************
*
* printBannerLogo - print copyright information to the banner
*
* This routine prints the copyright and version numbers on the banner
*
* RETURNS : N/A
*
* NOMANUAL
*/

LOCAL void printBannerLogo (void)
    {
    printf ("\n\n%23s%s\n\n",runtimeName,
	    RUNTIME_QUALIFIER_1 RUNTIME_QUALIFIER_2);
    printf ("Copyright 1984-%s Wind River Systems, Inc.\n\n", (__DATE__ + 7));
    printf ("     %s\n", kernelVersion ());
    printf ("              Build date: %s\n", creationDate);
    }

