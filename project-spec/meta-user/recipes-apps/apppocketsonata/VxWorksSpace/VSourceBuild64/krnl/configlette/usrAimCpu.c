/* usrAimCpuInit.c - Architecture Independent CPU initialization */

/*
 * Copyright (c) 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
20dec13,cww  clean up aimCpuLib naming scheme
20nov12,x_z  written based on usrCoreE6500.c/01r.
*/

/*
DESCRIPTION
This file is used to initialize the CPU.

NOMANUAL
*/

/* includes */

#include <vxWorks.h>
#include <edrLib.h>
#include <private/aimCpuLibP.h>
#include <private/kwriteLibP.h>        /* _func_kprintf */

/* defines */

#define CPU_DBG_MSG(fmt, args...)                   \
    do                                              \
        {                                           \
        if (_func_kprintf != NULL)                  \
            _func_kprintf (fmt, ##args);            \
        } while (FALSE)

/* globals */

/* externals */

#include "usrCpuArch.c"

/*******************************************************************************
*
* usrAimCpuInit - initialize primary CPU
*
* This routine initializes various features of the primary CPU.
*
* It is only called by boardInit() for primary CPU initialization.
*
* RETURNS: NONE
*
* \NOMANUAL
*/

void usrAimCpuInit (void)
    {
    UINT          err;
    UINT          ix;
    char *        pMsg;
    static char * pErrorMsg =
        "usrInit: cpu configuration failed, errno = 0x00000000\n";
    static char   digits[] = "0123456789abcdef";

    CPU_DBG_MSG ("initialize CPU\r\n");

    if (usrCpuArchInit() != OK)
	goto usrCpuPanic;

    CPU_DBG_MSG ("start CPU\r\n");

    aimCpuStart();

    return;

usrCpuPanic:

    CPU_DBG_MSG ("failed to initialize CPU\r\n", 0, 1, 2, 3, 4, 5);

    /* save error message with errno in system exception msg area */

    pMsg = pErrorMsg + strlen (pErrorMsg) - 2;
    err  = errno;

    for (ix = 0; ix < 8; ix++)
        {
        *pMsg-- = digits[err & 0xf];
        err >>= 4;
        }

    pMsg = pErrorMsg;

    while ((*(sysExcMsg++) = *(pMsg++)) != EOS)
    ;

    /*
     * Use ED&R to inject an error. In case ED&R is not included or not yet
     * initialized, the policy stub still will be called.
     */

    EDR_INIT_FATAL_INJECT (NULL, NULL, NULL, NULL, pErrorMsg);

    /* if EDR stub returned somehow... */

    reboot (BOOT_WARM_NO_AUTOBOOT);
    }


