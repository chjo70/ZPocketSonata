/* vxbFdtLib.h - VxBus FDT bus lilbrary header file */

/*
 * Copyright (C) 2013-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
03oct16,wap  Update vxbFdtUnitAddrGet() for reentrancy
21sep16,wap  Add prototype for vxbFdtUnitAddrGet() (F7769)
11apr16,wap  Add support for building in user mode
12may15,wap  Put FDT_BUS_DEV_INFO here so that simpleBus can use
             it (F3973)
07may15,jmz  US55875 - Move definition for vxbIntrEntry to vxbIntLib.h
09jan14,y_y  clean gnu warnings
14aug13,l_z  created
*/

#ifndef __INCvxbFdtLibh
#define __INCvxbFdtLibh

#ifdef _WRS_KERNEL
#include <vxFdtLib.h>
#endif
#include <vxWorks.h>
#include <hwif/vxBus.h>
#include <hwif/util/vxbResourceLib.h>

#ifdef __cplusplus
extern "C" {
#endif

BUSTYPE_DECL(vxbFdtBus);

#define VXB_BUSID_FDT                BUSTYPE_ID(vxbFdtBus)

#ifdef _WRS_KERNEL
/* struct used for matching a device */

typedef struct vxbFdtDevMatchEntry
    {
    char    *compatible;
    const void *data;
    } VXB_FDT_DEV_MATCH_ENTRY;

/* struct to describe the FDT device */

typedef struct vxbFdtDev
    {
    char    name[FDT_NODE_NAME_LEN + 1];
    int     offset;
    } VXB_FDT_DEV;

typedef struct vxbFdtBusDevInfo
    {
    VXB_FDT_DEV vxbFdtDev;
    VXB_RESOURCE_LIST vxbResList;
    } VXB_FDT_BUS_DEV_INFO;

IMPORT STATUS vxbFdtDevMatch
    (
    VXB_DEV_ID pDev,                            /* device to do match */
    const VXB_FDT_DEV_MATCH_ENTRY *   pMatchTbl,      /* pointer to match table */
    VXB_FDT_DEV_MATCH_ENTRY **  pMatchedEntry   /* best matched entry */
    );

IMPORT void vxbFdtDevSetup (int, VXB_FDT_DEV *);
IMPORT VXB_FDT_DEV * vxbFdtDevGet (VXB_DEV_ID pDev);
IMPORT STATUS vxbFdtIntGet (VXB_RESOURCE_LIST * pResList, VXB_FDT_DEV * pFdtDev);
IMPORT STATUS vxbFdtRegGet (VXB_RESOURCE_LIST * pResList, VXB_FDT_DEV * pFdtDev);
IMPORT STATUS vxbFdtIoGet (VXB_RESOURCE_LIST * pResList, VXB_FDT_DEV * pFdtDev);
IMPORT void vxbFdtResFree (VXB_RESOURCE_LIST * pResList);
IMPORT char * vxbFdtUnitAddrGet (UINT32 offset, char *, UINT32);

#endif

#ifdef __cplusplus
}
#endif

#ifdef _WRS_KERNEL
#include <hwif/methods/vxbFdtMethod.h>
#endif

#endif /*__INCvxbFdtLibh*/
