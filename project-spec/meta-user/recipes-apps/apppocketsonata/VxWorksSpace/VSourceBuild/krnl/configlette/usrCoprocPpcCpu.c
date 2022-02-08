/* usrCoprocPpcCpu.c - PowerPC E500 coprocessor discovery & initialization */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
22feb14,x_z  written from usrCoprocPpc.c 01i.
*/

/*
DESCRIPTION

This module implements the process of discovery and initialization for PowerPC
E500 coprocessors (i.e. SPE). 

*/

/* externals */

#ifdef INCLUDE_SPE
IMPORT void speInit();
IMPORT STATUS speRegsGet (SPEREG_SET *, SPEREG_SET *);
IMPORT STATUS speRegsSet (SPEREG_SET *, SPEREG_SET *);
IMPORT SPE_CONTEXT * speCtxCreate (void);
IMPORT STATUS speCtxDelete (SPE_CONTEXT *);
IMPORT void speSave (SPE_CONTEXT *);
IMPORT void speRestore (SPE_CONTEXT *);
IMPORT void speEnable (void);
IMPORT void speDisable (void);
IMPORT void speCtxShow (SPE_CONTEXT *);
#endif /* INCLUDE_SPE */

/*******************************************************************************
*
* coprocsCpuDiscover - discover available and configured coprocessors 
*
* This routine detects which coprocessors are present and configured in
* the system. For each one found, a bitmask is placed into the pMasks array.
* coprocLibInit() will then allocate descriptor structures for each 
* coprocessor used in the system.
*
* RETURNS: N/A.
*
* ERRNO: N/A.
*
* SEE ALSO: 
* .pG "Basic OS"
*
* VARARGS5
*/

void coprocsCpuDiscover
    (
    UINT32 * pMasks
    )
    {
#ifdef INCLUDE_SPE
    speInit();

    if (speProbe () == OK)
	    {
	    *pMasks++ = VX_SPE_TASK;
	    }
#endif /* INCLUDE_SPE */
    }

/*******************************************************************************
*
* coprocDescriptorsCpuInit - initialize coprocessor descriptor
*
* This routine initializes the selected descriptor to point to their respective 
* library functions if necessary.
*
* RETURNS: N/A.
*
* ERRNO: N/A.
*
* SEE ALSO: 
* .pG "Basic OS"
*
* VARARGS5
*/

void coprocDescriptorsCpuInit
    (
    COPROC_DESC * pDesc
    )
    {
#ifdef INCLUDE_SPE
    if (pDesc->mask == VX_SPE_TASK)
        {
        pDesc->ctxSize        = sizeof (SPE_CONTEXT);
	    pDesc->ctxAlign       = 16;
        pDesc->pCtxCreateRtn  = (COPROC_CTX_CREATE_RTN) speCtxCreate;
        pDesc->pCtxDeleteRtn  = (COPROC_CTX_DELETE_RTN) speCtxDelete;
        pDesc->pEnableRtn     = (COPROC_ENABLE_RTN) speEnable;
        pDesc->pDisableRtn    = (COPROC_DISABLE_RTN) speDisable;
        pDesc->pCtxSaveRtn    = (COPROC_CTX_SAVE_RTN) speSave;
        pDesc->pCtxRestoreRtn = (COPROC_CTX_RESTORE_RTN) speRestore;
#   ifdef INCLUDE_SPE_SHOW
        pDesc->pShowRtn       = (COPROC_CTX_SHOW_RTN) speCtxShow;
#   endif /* INCLUDE_SPE_SHOW */
        }
#endif /* INCLUDE_SPE */
    }

