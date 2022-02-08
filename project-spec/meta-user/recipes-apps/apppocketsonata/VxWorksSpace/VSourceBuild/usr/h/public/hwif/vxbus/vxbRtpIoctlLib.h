/* vxbRtpIoctlLib.h - VxBus RTP IO device header file */

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
11apr16,wap  Add VXBIODEVMETHODCALL
23oct15,wap  Adjust _IOxx() definitions for regread, regwrite, dma32alloc
             and dmamap ioctl()s.
05oct15,wap  Add prototype for vxbRtpIoctlLibInit()
02oct15,wap  Created
*/

#ifndef __INCvxbRtpIoctlLibh
#define __INCvxbRtpIoctlLibh

#ifdef __cplusplus
extern "C" {
#endif

#include <limits.h>
#include <sys/ioctl.h>

#ifdef _WRS_KERNEL

#include <private/datasetP.h>

typedef STATUS (*VXB_METHOD_STUB)(void * pArg, UINT32 argLen);

typedef struct vxbMethodLink
    {
    char		vxbMethod[PATH_MAX];
    VXB_METHOD_STUB	vxbMethodStub;
    } VXB_METHOD_LINK;

#define VXB_METHOD_DEF(vxbMethod)	\
    DATA_SET(method, 0, vxbMethod);

#endif

/* RTP driver binding interface */

#define VXBIODEVBORROW    _IOW('v', 140, VXB_DEV_DESC *) /* Borrow a device from the kernel */
#define VXBIODEVRETURN    _IO('v', 141)                  /* Return a device to the kernel */

#define VXBIODEVRESGET    _IOW('v', 142, VXB_RES_DESC *) /* Get/list device resources */

/* RTP driver interrupt API */

#define VXBIODEVINTCONNECT	\
                          _IO('v', 143)                  /* Connect interrupt to RTP */
#define VXBIODEVINTDISCONNECT	\
                          _IO('v', 144)                  /* Disconnect interrupt from RTP */
#define VXBIODEVINTENABLE _IO('v', 145)                  /* Enable interrupt */
#define VXBIODEVINTDISABLE	\
                          _IO('v', 146)                  /* Disable interrupt */

#define VXBIODEVEOI       _IO('v', 147)                  /* Signal end of interrupt */
#define VXBIODEVWAKEUP    _IO('v', 148)                  /* Force wakeup of int task */

/* RTP driver register access API */

#define VXBIODEVREGREAD  _IOWR('v', 149, VXB_REG_DESC *) /* Read a register */
#define VXBIODEVREGWRITE  _IOW('v', 150, VXB_REG_DESC *) /* Write a register */

typedef struct vxbMemDesc
    {
    VIRT_ADDR		pVxbVirtKrn;
    VIRT_ADDR		pVxbVirtRtp;
    PHYS_ADDR		pVxbPhys;
    size_t		vxbLen;
    } VXB_MEM_DESC;

typedef struct vxbMethodDesc
    {
    char 		vxbMethod[PATH_MAX];
    VXB_KEY		vxbNode;
    void *		vxbArgs;
    UINT32		vxbArgLen;
    } VXB_METHOD_DESC;

#define VXBIODEVDMA32ALLOC _IOWR('v', 151, VXB_MEM_DESC *)/* Allocate bounce buffers */
#define VXBIODEVDMA32FREE   _IOW('v', 152, VXB_MEM_DESC *)/* Release bounce buffers */

#define VXBIODEVDMAMAP    _IOWR('v', 153, VXB_MEM_DESC *) /* Obtain DMA-safe mapping */
#define VXBIODEVDMAUNMAP   _IOW('v', 154, VXB_MEM_DESC *) /* Release DMA-safe mapping */

#define VXBIODEVMETHODCALL _IOWR('v', 155, VXB_METHOD_DESC *) /* Make a method call */

IMPORT STATUS vxbRtpIoctlLibInit (void);
IMPORT STATUS vxbRtpDevCreate (VXB_DEV_ID);
IMPORT STATUS vxbRtpDevDelete (VXB_DEV_ID);

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbRtpIoctlLibh */
