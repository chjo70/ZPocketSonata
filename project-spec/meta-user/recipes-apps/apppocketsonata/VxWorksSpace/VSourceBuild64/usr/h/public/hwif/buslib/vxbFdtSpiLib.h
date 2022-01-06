/* vxbFdtSpiLib.h - VxBus FDT SPI bus library header file*/

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
16mar15,y_f  created (V7PRO-1908)
*/

#ifndef __INCvxbFdtSpiLibh
#define __INCvxbFdtSpiLibh

#include <vxWorks.h>
#include <hwif/vxBus.h>
#include <hwif/buslib/vxbFdtLib.h>
#include <hwif/buslib/vxbSpiLib.h>

#if __cplusplus
extern "C" {
#endif /* __cplusplus */

/* function declarations */

IMPORT VXB_RESOURCE *   vxbSpiResAlloc (VXB_DEV_ID pDev, VXB_DEV_ID pChild,
                                        UINT32 id);
IMPORT STATUS           vxbSpiResFree (VXB_DEV_ID pDev, VXB_DEV_ID pChild,
                                       VXB_RESOURCE * pRes);
IMPORT VXB_FDT_DEV *    vxbSpiFdtDevGet (VXB_DEV_ID pDev, VXB_DEV_ID pChild);
IMPORT STATUS           vxbSpiCtrlRegister (VXB_DEV_ID pDev);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCvxbFdtSpiLibh */
