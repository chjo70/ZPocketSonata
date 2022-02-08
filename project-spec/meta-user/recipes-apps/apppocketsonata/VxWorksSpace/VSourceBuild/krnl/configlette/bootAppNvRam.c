/* bootAppNvRam.c - bootapp NVRAM support */

/*
 * Copyright (c) 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
11mar15 yya  created (US55212)
*/

/*
DESCRIPTION

This configlette implements bootapp NVRAM support.
*/

#include "bootApp.h"

#ifdef INCLUDE_BOOTAPP_NVRAM_SUPPORT

STATUS (*bootAppNvSet)(char *, int, int);
STATUS (*bootAppNvGet)(char *, int, int);

#endif /* INCLUDE_BOOTAPP_NVRAM_SUPPORT */

#ifdef INCLUDE_BOOTAPP_NVRAM_SUPPORT
/*******************************************************************************
*
* bootAppNvRamSupportInit - register NVRAM functions to boot app
*
* This routine registers NVRAM functions to boot app.
*
* RETURNS: N/A
*
* ERRNO: N/A
*
* \NOMANUAL
*/

void bootAppNvRamSupportInit
    (
    STATUS (*set)(char *, int, int),
    STATUS (*get)(char *, int, int)
    )
    {
    bootAppNvSet = set;
    bootAppNvGet = get;
    }
#endif /* INCLUDE_BOOTAPP_NVRAM_SUPPORT */

/******************************************************************************
*
* bootAppLoadBootLine - bootline load function
*
* This routine loads the bootline from either NVRAM or DTB, according to whether
* the INCLUDE_BOOT_APP_NVRAM_SUPPORT component in BOOTAPP menu is enabled.
* If loading failed, or the content is invalid, the default bootline is used.
*
* RETURNS: N/A
*
* ERRNO: N/A
*
* \NOMANUAL
*/

void bootAppLoadBootLine (void)
    {
#ifdef INCLUDE_BOOTAPP_NVRAM_SUPPORT
    if (bootAppNvGet &&
        (bootAppNvGet ((char *)BOOT_LINE_ADRS, BOOT_LINE_SIZE, 0) == OK) &&
        (*((char *)(BOOT_LINE_ADRS)) != EOS) &&
        (*((char *)(BOOT_LINE_ADRS)) != (char) -1))
        {
        return;
        }
    bootAppPrintf("\nNOTE: load Bootline from NVRAM failed\n" ,0,0,0,0,0,0);
#endif /* INCLUDE_BOOTAPP_NVRAM_SUPPORT */

    if (vxFdtBootargsGet ((char *)BOOT_LINE_ADRS, BOOT_LINE_SIZE) != OK)
        {
#ifndef _WRS_ARCH_IS_SIMULATOR
        strncpy ((char *)BOOT_LINE_ADRS, DEFAULT_BOOT_LINE, BOOT_LINE_SIZE);
#endif /* _WRS_ARCH_IS_SIMULATOR */
        }
    }

/******************************************************************************
*
* bootAppSaveBootLine - bootline save function
*
* This routine saves the bootline to NVRAM if the INCLUDE_BOOT_APP_NVRAM_SUPPORT
* component in BOOTAPP menu is enabled. If this component is not enabled, the
* saving of bootline is not supported, and a message is printed on console to
* notify the user that bootline is not saved.
*
* RETURNS: N/A
*
* ERRNO: N/A
*
* \NOMANUAL
*/
 
void bootAppSaveBootLine
    (
    char *  buf,    /* source buffer to save */
    int     len     /* length of buffer to save */
    )
    {
#ifdef INCLUDE_BOOTAPP_NVRAM_SUPPORT
    if (bootAppNvSet == 0 || ERROR == bootAppNvSet (buf, len, 0))
        {
        bootAppPrintf("\nNOTE: Saving Bootline to NVRAM failed\n" ,0,0,0,0,0,0);
        }
#else
	bootAppPrintf("\nNOTE: Bootline obtained from DTB and needn't be written"
                  " back\n",0,0,0,0,0,0);
#endif /* INCLUDE_BOOTAPP_NVRAM_SUPPORT */
    }

#ifdef INCLUDE_BOOTAPP_GENERIC_NVRAM

/*******************************************************************************
*
* bootAppGenericNvRamGet - load function of BOOTAPP generic NVRAM
*
* This routine copies the contents of the NVRAM into a buffer specified by the
* caller, with specified maximum allow copy size.
*
* RETURNS: OK if operation succeeded; otherwise ERROR.
*
* ERRNO: N/A
*
* \NOMANUAL
*/

STATUS bootAppGenericNvRamGet
    (
    char *  buf,            /* start address to load to         */
    int     len,            /* maximum bytes allowed to copy    */
    int     offset          /* byte offset into NVRAM           */
    )
    {
    int fd = ERROR;
    
    if (offset < 0 || offset + len > BOOTAPP_GENERIC_NVRAM_SIZE)
        {
        DEBUG_MSG("bootAppGenericNvRamGet: write out of range.\n");
        return (ERROR);
        }
    
    fd = open(BOOTAPP_GENERIC_NVRAM_NAME, O_RDONLY, 0);
    if (ERROR == fd)
        {
        DEBUG_MSG("bootAppGenericNvRamGet: open %s failed.\n", BOOTAPP_GENERIC_NVRAM_NAME);
        return (ERROR);
        }

    if (ERROR == ioctl(fd, FIOSEEK, BOOTAPP_GENERIC_NVRAM_OFFSET + offset))
        {
        DEBUG_MSG("bootAppGenericNvRamGet: ioctl failed.\n");
        close (fd);
        return (ERROR);
        }

    if (len != read(fd, buf, len))
        {
        DEBUG_MSG("bootAppGenericNvRamGet: read failed.\n");
        close (fd);
        return (ERROR);
        }
    close (fd);
    return OK;
}

/*******************************************************************************
*
* bootAppGenericNvRamSet - save function of BOOTAPP generic NVRAM
*
* This routine saves to the NVRAM, the address of the content to saved and the 
* size are provided by the caller.
*
* RETURNS: OK if operation succeeded; otherwise ERROR.
*
* ERRNO: N/A
*
* \NOMANUAL
*/

STATUS bootAppGenericNvRamSet
    (
    char *  buf,            /* start address to be copied           */
    int     len,            /* maximum number of bytes to copy      */
    int     offset          /* byte offset into NVRAM               */
    )
    {
    int fd = ERROR;
    
    if (offset < 0 || offset + len > BOOTAPP_GENERIC_NVRAM_SIZE)
        {
        DEBUG_MSG("bootAppGenericNvRamSet: write out of range.\n");
        return (ERROR);
        }
    
    fd = open(BOOTAPP_GENERIC_NVRAM_NAME, O_WRONLY, 0);
    if (ERROR == fd)
        {
        DEBUG_MSG("bootAppGenericNvRamSet: open %s failed.\n", BOOTAPP_GENERIC_NVRAM_NAME);
        return (ERROR);
        }

    if (ERROR == ioctl(fd, FIOSEEK, BOOTAPP_GENERIC_NVRAM_OFFSET + offset))
        {
        DEBUG_MSG("bootAppGenericNvRamSet: ioctl failed.\n");
        close (fd);
        return (ERROR);
        }

    if (len != write(fd, buf, len))
        {
        DEBUG_MSG("bootAppGenericNvRamSet: write failed.\n");
        close (fd);
        return (ERROR);
        }
    close (fd);
    return OK;
    }

#endif /* INCLUDE_BOOTAPP_GENERIC_NVRAM */
