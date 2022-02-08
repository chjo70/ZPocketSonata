/* usrWarmBootLib.c - warm boot library configure file */

/*
 * Copyright (c) 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
07apr15,l_z  created. (F3387)
*/

#include <vxWorks.h>
#include <warmBootLib.h>
#include <vmLib.h>
#ifdef INCLUDE_DEBUG
#include <rebootLib.h>
#include <dbgLib.h>
#endif /* INCLUDE_DEBUG */


#ifdef INCLUDE_WARM_BOOT_PROTECT
UINT32 warmBootDataAlign = VM_PAGE_SIZE;
#else
UINT32 warmBootDataAlign = 1;
#endif

IMPORT BOOL   dbgInstalled;
IMPORT STATUS warmBootLibInit (void);

#ifdef INCLUDE_DEBUG
/*****************************************************************************
*
* bpDeleteAll - delete all break points
*
* This routine delete all break points.
*
* ERRNO: N/A
*
* RETURNS: void
*/

LOCAL void bpDeleteAll()
    {
    if (dbgInstalled == TRUE)
        bdall (0);
    }
#endif /* INCLUDE_DEBUG */

/*****************************************************************************
*
* usrWarmBootLibInit - init warm data library
*
* This routine init warm data library.
*
* ERRNO: N/A
*
* RETURNS: void
*/

 void usrWarmBootLibInit
    (
    )
    {
    warmBootLibInit();

#ifdef INCLUDE_DEBUG

    /* register bpDeleteAll to rebootHookLib */

    (void) rebootHookAdd((REBOOT_HOOK)bpDeleteAll);
#endif /* INCLUDE_DEBUG */

#ifdef INCLUDE_WARM_BOOT_PROTECT

    (void) vmStateSet (0, WARM_DATA_ADDR, warmBootDataEndGet() - WARM_DATA_ADDR,
                      MMU_ATTR_PROT_MSK,(MMU_ATTR_PROT_SUP_READ));
#endif /* INCLUDE_WARM_BOOT_PROTECT */

    }
