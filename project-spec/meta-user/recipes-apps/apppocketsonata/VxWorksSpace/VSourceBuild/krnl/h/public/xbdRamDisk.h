/* xbdRamDisk.h - Ramdisk Block Device conforming to the XBD interface */

/*
 * Copyright 2005-2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01e,29apr10,pad  Moved extern C statement after include statements.
01d,12apr06,dee  SPR 119990, WIND00037359 - add cplusplus constructs
01c,26jul05,jlk  Updated xbdRamDiskDevCreate() prototype to take an extra 
                 parameter.
01b,11jul05,jlk  Added xbdRamDiskDevDelete() prototype
01a,31jan05,rfr  Fixed inclusion of xbd.h
*/

#ifndef __INCxbdRamDiskh
#define __INCxbdRamDiskh

#include <drv/xbd/xbd.h>

#ifdef __cplusplus
extern "C" {
#endif


extern device_t xbdRamDiskDevCreate(unsigned BlockSize, unsigned TotalSize, 
                                    BOOL flag, const char *name);
extern STATUS   xbdRamDiskDevDelete(device_t d);

#ifdef __cplusplus
}
#endif

#endif /* __INCxbdRamDiskh */
