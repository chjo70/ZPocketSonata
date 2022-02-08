/* usrVdfs.c - virtual file system library */

/*
 * Copyright 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
-------------------- 
24oct17,jsp  written
*/

/*
DESCRIPTION
*/

/* includes */

#ifndef	__INCusrVdfsc
#define	__INCusrVdfsc

#include "vxWorks.h"

#ifdef	VDFS_PRIO_SCHED_TIMEOUT
const UINT32 vdFsPrioUsecTimeout = (VDFS_PRIO_SCHED_TIMEOUT);
#else
const UINT32 vdFsPrioUsecTimeout = 100;
#endif

#ifdef	VDFS_PRIO_SCHED_ENABLE
const BOOL vdFsPrioSchedEnable = TRUE;
#else
const BOOL vdFsPrioSchedEnable = FALSE;
#endif

#endif	/* __INCusrVdfsc */
