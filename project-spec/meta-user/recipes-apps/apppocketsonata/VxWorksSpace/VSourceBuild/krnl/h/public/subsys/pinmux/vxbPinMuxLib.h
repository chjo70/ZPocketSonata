/* vxbPinMuxLib.h - vxBus pinmux interface header */

/*
 * Copyright (c) 2013-2014, 2016-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/* 
modification history
--------------------
18sep17,hcl  add multi-controller and non FDT device support (US103359)
18mar16,pmr  remove reference to vxbPinMuxShowMethod.h
12nov14,pmr  conditionalize show routine with _WRS_CONFIG_DEBUG_FLAG
25dec13,sye  updated API.
11jul13,c_t  written
*/

/*
DESCRIPTION

This library provides the pinmux specific interfaces.

*/

#ifndef __INCvxbPinMuxLibh
#define __INCvxbPinMuxLibh

/* includes */

#include <vxWorks.h>
#include <hwif/vxBus.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define PINMUX_DEFAULT_ID               (0)
#define PINMUX_ERROR_ID                 (0xffff)
#define PINMUX_DEFAULT_NAME             "default"

/* typedefs */

typedef struct vxbPinMuxCtrl 
    {
    SL_NODE     pNode;
    VXB_DEV_ID  pDev;           /* pointer to the controller instance */
    } VXB_PINMUX_CTRL;

/* function declarations */

STATUS vxbPinMuxLibInit (void);
STATUS vxbPinMuxRegister (VXB_PINMUX_CTRL * pCtrl);
STATUS vxbPinMuxUnregister (VXB_PINMUX_CTRL * pCtrl);
STATUS vxbPinMuxEnable (VXB_DEV_ID pDev);
STATUS vxbPinMuxDisable (VXB_DEV_ID pDev);
STATUS vxbPinMuxEnableById (VXB_DEV_ID pDev, UINT32 id);
STATUS vxbPinMuxDisableById (VXB_DEV_ID pDev, UINT32 id);
UINT32 vxbPinMuxGetIdByName (VXB_DEV_ID pDev, char * pName);

#ifdef _WRS_CONFIG_DEBUG_FLAG
void   vxbPinMuxShow (INT32 verbose);
#endif

#ifdef __cplusplus
}
#endif

#include <hwif/methods/vxbPinMuxMethod.h>

#endif /* __INCvxbPinMuxLibh */

