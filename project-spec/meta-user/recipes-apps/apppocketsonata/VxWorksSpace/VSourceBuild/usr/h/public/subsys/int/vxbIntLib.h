/* vxbIntLib.h - VxBus Interrupt Support Library */

/*
 * Copyright (c) 2015, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
11apr15,wap  Add VXB_INTR_ENTRY structure
30sep15,wap  Created
*/

#ifndef __INCvxbIntLibh
#define __INCvxbIntLibh

#ifdef __cplusplus
extern "C" {
#endif

STATUS vxbIntLibInit (void);

typedef struct vxbIntrEntry
    {
    UINT32        node;
    UINT32 *      pProp;
    UINT32        numProp;
    } VXB_INTR_ENTRY;

typedef struct vxbResourceIrq
    {
    UINT32           hVec;     /* hardware vector */
    UINT32           lVec;     /* logic vector */
    VOIDFUNCPTR      pIsr;     /* ISR */
    void *           pArg;     /* parameter */
    UINT32           flag;
    struct vxbIntrEntry * pVxbIntrEntry;   /* store the bus specfic interrupt information */
    } VXB_RESOURCE_IRQ;

STATUS vxbIntConnect (VXB_DEV_ID pDev, VXB_RESOURCE * pRes, VOIDFUNCPTR pIsr, void * pArg);
STATUS vxbIntDisconnect (VXB_DEV_ID pDev, VXB_RESOURCE * pRes);
STATUS vxbIntEnable (VXB_DEV_ID pDev, VXB_RESOURCE * pRes);
STATUS vxbIntDisable (VXB_DEV_ID pDev, VXB_RESOURCE * pRes);

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbIntLibh */
