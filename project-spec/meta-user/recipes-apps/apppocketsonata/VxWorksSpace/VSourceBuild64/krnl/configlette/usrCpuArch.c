/* usrCpuArchInit.c - Architecture specific CPU initialization */

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
04aug14,syt  Added supported for PPC_60x.(F2505)
28jan14,wap  That should have been _WRS_CONFIG_PPC_E500
28jan14,wap  Switch from using CPU macro to _WRS_CONFIG_PPC_xxx macro.
20dec13,cww  created
*/

/*
DESCRIPTION
This file contains architecture specific code used to initialize the CPU.  It
is included by the generic usrAimCpuInit.c
*/

/* externals */

#ifdef _WRS_CONFIG_PPC_E500
extern STATUS cpuE500LibInit();
#endif /* _WRS_CONFIG_PPC_E500 */

#ifdef _WRS_CONFIG_PPC_60x
extern STATUS cpu60xLibInit (void);
#endif /* _WRS_CONFIG_PPC_60x */

/*******************************************************************************
*
* usrCpuArchInit - initialize primary CPU
*
* This routine initializes various features of the primary CPU.
*
* It is only called from usrAimCpuInit() for primary CPU initialization.
*
* RETURNS: NONE
*
* \NOMANUAL
*/

STATUS usrCpuArchInit (void)
    {
#ifdef _WRS_CONFIG_PPC_E500
    return cpuE500LibInit();
#endif

#ifdef _WRS_CONFIG_PPC_60x
    return cpu60xLibInit();
#endif

    return OK;
    }
