/* usrPmap.c - physical address mapping library initialization */

/*
 * Copyright 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */

/*
modification history
--------------------
02jun14,pcs  Fixed gnu build warning. (V7COR-1208)
17apr14,pcs  Update to reflect change in signatute of pmapBaseLibInit (US34433)
24jan14,pcs  created
*/

/*
DESCRIPTION
The file contains routines for configuring the physical address mapping library.

SEE ALSO: pmapBaseLib, pmapLib
*/

/* includes */

#include <vxWorks.h>
#include <private/pmapLibP.h>
#include <vmLib.h>
#include <sysLib.h>

/* external functions */

#ifdef INCLUDE_ADR_SPACE_LIB
extern STATUS  pmapLibInit ();
#else
extern STATUS  pmapBaseLibInit (PMAP_INIT_PARAMS * pmapInitParam);
#endif

/* local variables */

#ifndef INCLUDE_ADR_SPACE_LIB
LOCAL PMAP_INIT_PARAMS pmapInitParam;
#endif

/*******************************************************************************
*
* pmapInit - init routine for physical address mapping library initialization
*
* This routine performs library initialization that must be done before the
* physical address mapping library can be used.
*
* RETURNS: N/A
*
* NOMANUAL
*/

void pmapInit (void)
    {
#ifdef INCLUDE_ADR_SPACE_LIB
    pmapLibInit();
#else
#if !defined (_WRS_CONFIG_MMULESS_KERNEL) &&  \
    defined (_WRS_CONFIG_COMPAT69_ADR_SPACE)
    pmapInitParam.pPhysMemDesc       = sysPhysMemDesc;
    pmapInitParam.physMemDescNumEnt  = sysPhysMemDescNumEnt;
    pmapInitParam.localMemLocalAdrs  = LOCAL_MEM_LOCAL_ADRS;
    pmapInitParam.kernelMemTop       = (VIRT_ADDR) memPoolEndAdrs;
#endif /* !_WRS_CONFIG_MMULESS_KERNEL && _WRS_CONFIG_COMPAT69_ADR_SPACE */

    if (pmapBaseLibInit (&pmapInitParam) == ERROR)
        {
        sysExcMsg += sprintf (sysExcMsg, "pmapBaseLib: Initialization"
                              " Failed.\n");
        /* 
         * Use ED&R to inject an error. In case ED&R is not included or not yet 
         * initialized, the policy stub still will be called.
         */

        EDR_INIT_FATAL_INJECT (NULL, NULL, NULL, NULL, "pmapBaseLib: "
                               "Initialization Failed.\n");

        /* if EDR stub returned somehow... */

        reboot (BOOT_WARM_NO_AUTOBOOT);
        }
#endif /* INCLUDE_ADR_SPACE_LIB */
    }

