/* vxbResourceLib.h - VxBus resource library header file */

/*
 * Copyright (c) 2013-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
08nov16,l_z  Remove resListSemId. (V7PRO-3297)
09may15,wap  Add serial number to resource structure (F3973)
09mar15,l_z  protect the resource list. (V7PRO-242).
04nov14,l_z  fix typo. (V7PRO-1443)
27aug13,l_z  Created
*/

#ifndef __INCvxbResourceLibh
#define __INCvxbResourceLibh

#ifdef __cplusplus
extern "C" {
#endif

#include <sllLib.h>

/* resource type define */

#define VXB_RES_MEMORY  1
#define VXB_RES_IO      2
#define VXB_RES_IRQ     3

#define VXB_RES_IDX(x)  ((x) & 0x0000FFFF)
#define VXB_RES_TYPE(x) (((x) & 0x00FF0000) >> 16)
#define VXB_RES_ID(x)   ((x)& 0xFFFFFF)

#define VXB_RES_ID_CREATE(type, idx)	\
    ((((type) & 0xFF) << 16) | ((idx) & 0xFFFF))

/* flag bits 24-31 */

#define VXB_RES_FLAG_MAPPED   0x01000000

typedef struct vxbResource
    {
    SL_NODE node;     /* to make a resource list */
    UINT32 id;        /* IDX and type */
    void * pRes;      /* resource description */
    VXB_DEV_ID owner; /* device using this resource */
    VXB_KEY vxbSerial;/* Serial number */
    } VXB_RESOURCE;

typedef void vxbResourceTravelFunc (void * pArg, VXB_RESOURCE * pRes);

typedef struct vxbDevList {
    SL_LIST     list;
} VXB_RESOURCE_LIST;

STATUS vxbResourceInit(VXB_RESOURCE_LIST * pResList);
VXB_RESOURCE * vxbResourceFind(VXB_RESOURCE_LIST * pResList, UINT32 id);
STATUS vxbResourceAdd(VXB_RESOURCE_LIST * pResList, VXB_RESOURCE * pAddRes);
STATUS vxbResourceRemove(VXB_RESOURCE_LIST * pResList, VXB_RESOURCE * pRevRes);
STATUS vxbResourceIterate(VXB_RESOURCE_LIST *, vxbResourceTravelFunc ,void *);
VXB_RESOURCE * vxbResourceAlloc(VXB_DEV_ID pDev, UINT16 type, UINT16 idx);
STATUS vxbResourceFree(VXB_DEV_ID pDev, VXB_RESOURCE *res);
VXB_RESOURCE_LIST * vxbResourceListGet(VXB_DEV_ID pDev);


#ifdef __cplusplus
}
#endif

#include <hwif/methods/vxbResourceMethod.h>


#endif /* __INCvxbResourceLibh */


