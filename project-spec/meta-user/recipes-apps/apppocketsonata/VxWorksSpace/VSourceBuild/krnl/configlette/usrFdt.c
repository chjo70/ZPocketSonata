/* usrFdt.c - FDT library configlette */

/*
 * Copyright (c) 2013-2015 Wind River Systems, Inc. All rights are reserved.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
05aug15,j_l  Initial modifications for IA 32 bit GEN2 support
14may15,yya  fixed missing zero terminater (V7PRO-2056)
20apr15,yya  fixed component dependency issue (V7PRO-1988)
11mar15,yya  added DTB self-patch to support legacy bootloader (US55212)
01dec14,vhe  Fixed bootline issue when using uBoot (V7PRO-1463)
18apr14,elp  Simulator support.
29sep13,x_z  cleaned.
29may13,x_z  created.
*/

#include <vxWorks.h>
#include <sysLib.h>
#include <vxFdtLib.h>

/* globals */

/* initial DTB */

#ifdef _WRS_ARCH_IS_SIMULATOR
extern void * dt_blob_start;

void * gpDtbInit = &dt_blob_start;
#else
void * gpDtbInit = NULL;
#endif /* _WRS_ARCH_IS_SIMULATOR */

#ifdef INCLUDE_PATCH_STANDALONE_DTB
LOCAL STATUS usrFdtPatchBootline (void);
#endif /* INCLUDE_PATCH_STANDALONE_DTB */

/*****************************************************************************
*
* usrFdtInit - initialize FDT library
*
* This routine just call the initialization routine of VxWorks FDT library.
*
* RETURNS: N/A
*/

void usrFdtInit
    (
    void *  pDtbReloc,
    int     fdtLen
    )
    {
    if (vxFdtLibInit (gpDtbInit, pDtbReloc, (UINT32) fdtLen) != OK)
        {
        char * pErrMsg = "failed to initialize FDT library.";
#if defined(_WRS_CONFIG_ARCH_i86) && defined(INCLUDE_BOOT_APP)
        (void) sprintf (sysExcMsg, pErrMsg, strlen (pErrMsg));
#else
        sysExcMsg = strncat (sysExcMsg, pErrMsg, strlen (pErrMsg));
#endif /* _WRS_CONFIG_ARCH_i86 && INCLUDE_BOOT_APP */
        }

#ifdef INCLUDE_PATCH_STANDALONE_DTB
    if (usrFdtPatchBootline () != OK)
        {
#if !defined(_WRS_CONFIG_ARCH_i86) && !defined(INCLUDE_BOOT_APP)
        char * pErrMsg = "failed to patch DTB; original DTB is used.";
        sysExcMsg = strncat (sysExcMsg, pErrMsg, strlen(pErrMsg));
#endif /* !_WRS_CONFIG_ARCH_i86 && !INCLUDE_BOOT_APP */
        }
#endif /* INCLUDE_PATCH_STANDALONE_DTB */

    if (vxFdtBootargsGet ((char *)BOOT_LINE_ADRS, BOOT_LINE_SIZE) != OK)
        {
#ifndef _WRS_ARCH_IS_SIMULATOR
        strncpy ((char *)BOOT_LINE_ADRS,
                 DEFAULT_BOOT_LINE,
                 BOOT_LINE_SIZE)[BOOT_LINE_SIZE-1] = EOS;
#endif
        }
    }

#ifdef INCLUDE_PATCH_STANDALONE_DTB
/*******************************************************************************
*
* usrFdtPatchBootline - patch DTB to replace the bootline
*
* This routine patches the embedded DTB. This function overwrites the bootline
* in STANALONE_DTB with the bootline passed from the BOOTAPP, to make the OS be
* compatible with legacy bootloder that does not support DTB and instead passes
* bootline to vxWorks image.
*
* RETURNS: OK if successful; otherwise ERROR.
*
* ERRNO: N/A
*/

LOCAL STATUS usrFdtPatchBootline (void)
    {
    BOOT_PARAMS bootParams;
    int         offset;
    char *      bootline = (char *) BOOT_LINE_ADRS;

    /* check if non-null bootline is present */

    if (bootline == 0 || bootline[0] == EOS)
        {
        return ERROR;
        }

    /* try parsing bootline to check whether it is valid */

    bootline[BOOT_LINE_SIZE-1] = EOS;
    if (*bootStringToStruct (bootline, &bootParams) != EOS)
        {
        return ERROR;
        }

    /* try patching DTB */

    offset = vxFdtPathOffset ("/chosen");
    if (offset >= 0 && vxFdtPropSet(offset, "bootargs",
        (void *)bootline, strlen(bootline)+1) == 0)
        {
        return OK;
        }
    return ERROR;
    }
#endif /* INCLUDE_PATCH_STANDALONE_DTB */
