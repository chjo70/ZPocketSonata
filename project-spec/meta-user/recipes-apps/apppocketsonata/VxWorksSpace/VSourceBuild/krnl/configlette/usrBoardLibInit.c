/* usrBoardLibInit.c - Board subsystem initialization */

/*
 * Copyright (c) 2013-2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
24jan14,ylu  fixed coverity and compling issues.
01a,20nov12,x_z  created.
*/

/*
DESCRIPTION
This file is used to initialize the CPU.

NOMANUAL
*/

#include <vxWorks.h>
#include <boardLib.h>
#include <sysLib.h>

/* globals */

int         sysBus      = BUS_TYPE_NONE;    /* system bus type */
int         sysCpu      = CPU;              /* system CPU type */
char *      sysBootLine = (char *) BOOT_LINE_ADRS;   /* address of boot line */
char *      sysExcMsg   = (char *) EXC_MSG_ADRS;     /* catastrophic message area */
int         sysProcNum  = 0;                /* processor number of this CPU */

/*****************************************************************************
*
* usrBoardLibInit - initialize Board subsystem
*
* This routine just call the initialization routine of Board subsystem library.
*
* RETURNS: N/A
*/

void usrBoardLibInit ()
    {
    static char * pErrMsg = " failed to initializate board subsystem. ";

    if (boardLibInit () != OK)
        sysExcMsg = strncat (sysExcMsg, pErrMsg, strlen (pErrMsg));
    }

/*******************************************************************************
*
* sysBspRev - return BSP package version
*
* This function returns a pointer to a BSP version for BSP package.
*
* RETURNS: A pointer to BSP version string.
*
* ERRNO: N/A
*/

char * sysBspRev (void)
    {
    return (BSP_VERSION);
    }

