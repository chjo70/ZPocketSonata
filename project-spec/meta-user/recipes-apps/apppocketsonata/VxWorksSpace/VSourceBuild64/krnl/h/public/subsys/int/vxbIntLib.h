/* vxbIntLib.h - VxBus Interrupt Support Library */

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
05aug16,wap  Add prototype for init routine, remove no longer needed
             deferral list size macro (V7PRO-3177)
03mar16,wap  Remove unused macros and prototypes
23feb16,wap  Add new data structure and flags for interrupt deferral
             mechanism
28jan16,wap  Remove platform-specific code, correct spelling error
             in enum name (F6448)
26jan16,wap  Add isr/ipi reserve/release APIs (F6448)
14may15,wap  Reactivate vxbIntReroute() and vxbIntToCpuRoute() (F3973)
07may15,jmz  US55875 - Add common definitions for interrupt structures
15oct14,to   US45794 - define VXB_IOAPIC_LVEC_BASE as IOAPIC lVec base
22aug14,sye  added system interrupt enable flag functions. (V7PRO-1197)
18jul14,scm  US42878 - conform to vxbus hVec usage...
08jan14,y_y  code clean
10dec13,scm  US24478 - initial mods for GEN2 test image...
09oct13,x_z  Added vxbIntReroute() and vxbIntToCpuRoute() for SMP.
27aug13,l_z  Created
*/


#ifndef _INCvxbIntLibh
#define _INCvxbIntLibh

#include <subsys/int/vxbIsrHandler.h>
#include <hwif/util/vxbResourceLib.h>
#include <subsys/int/vxbDyncIntLib.h>

#ifdef _WRS_CONFIG_FDT
#include <hwif/buslib/vxbFdtLib.h>
#endif /* _WRS_CONFIG_FDT */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct vxb_int_defer
    {
    VXB_RESOURCE *	pRes;
    UINT32		flags;
    cpuset_t		cpuset;
    } VXB_INT_DEFER;

#define VXB_INT_DEFER_FLAG_VALID	0x00000001
#define VXB_INT_DEFER_FLAG_REROUTE	0x00000002
#define VXB_INT_DEFER_FLAG_CONNECT	0x00000004
#define VXB_INT_DEFER_FLAG_ENABLE	0x00000008

#define VXB_INT_CONTRL_MAX      32

#define VXB_INT_FLAG_STATIC     0x1
#define VXB_INT_FLAG_DYNAMIC    0x2

#define VXB_INT_FLAG_ALLOCATED  0x1

typedef enum intr_trigger {
    INTR_TRIGGER_CONFORM = 0,
    INTR_TRIGGER_EDGE = 1,
    INTR_TRIGGER_LEVEL = 2
}INTR_TRIGGER;

#define INTR_TRIGER INTR_TRIGGER

typedef enum intr_polarity {
    INTR_POLARITY_CONFORM = 0,
    INTR_POLARITY_HIGH = 1,
    INTR_POLARITY_LOW = 2,
    INTR_POLARITY_BOTH   /* valid for edge only, e.g. double edge trigger */
}INTR_POLARITY;

/*
 * These macros provide suggested meanings for the fields in
 * the pProps array of the vxbIntrEntry structure. A given platform
 * may choose to use its own internal meanings for these fields
 * instead.
 */

#define INTR_PROP_TYPE		0
#define INTR_PROP_PIN		1
#define INTR_PROP_TRIGGER	2
#define INTR_PROP_POLARITY	3

typedef struct vxbIntrEntry {
   UINT32        node;
   UINT32 *      pProp;
   UINT32        numProp;
} VXB_INTR_ENTRY;

typedef struct vxbIntContrl {
    VXB_DEV_ID       pDev;    /* interrupt controller device handle */
    UINT32           node;    /* interrupt instance node ID */
    UINT32           irqBase; /* starting irq hVec value */
    UINT32           irqs;    /* number of irq */
    UINT32           ipiBase; /* starting ipi hVec value */
    UINT32           ipis;    /* number of ipi */
    UINT32           base;    /* vxbIntrVecs[] table base (lVec value) */
    UINT32           flag;
}VXB_INT_CONTRL;

typedef struct vxbResourceIrq
    {
    UINT32           hVec;     /* hardware vector */
    UINT32           lVec;     /* logic vector */
    VOIDFUNCPTR      pIsr;     /* ISR */
    void *           pArg;     /* parameter */
    UINT32           flag;
    struct vxbIntrEntry * pVxbIntrEntry;   /* store the bus specfic interrupt information */
    } VXB_RESOURCE_IRQ;

IMPORT STATUS vxbIntMap
    (
    VXB_RESOURCE *pRes
    );

IMPORT STATUS vxbIntConnect
    (
    struct vxbDev * pDev,
    VXB_RESOURCE  * pRes,
    VOIDFUNCPTR     pIsr,
    void *      pArg
    );

IMPORT STATUS vxbIntDisconnect
    (
    struct vxbDev * pDev,
    VXB_RESOURCE  * pRes
    );

IMPORT STATUS vxbIntEnable
    (
    struct vxbDev * pDev,
    VXB_RESOURCE  * pRes
    );

IMPORT STATUS vxbIntDisable
    (
    struct vxbDev * pDev,
    VXB_RESOURCE  * pRes
    );

IMPORT STATUS vxbIntRegister
    (
    VXB_DEV_ID    pDev, /* interrupt controller id */
    UINT32        node, /* interrupt instance node */
    UINT32        nirq, /* number of interrupt */
    UINT32        nipi, /* number of ipi interrupt */
    UINT32      * pBase /* interupt vector base */
    );

IMPORT STATUS vxbIntReserve (VXB_DEV_ID pDev, UINT32 node, UINT32 irqBase, UINT32 irqs, UINT32 * pBase);
IMPORT STATUS vxbIpiReserve (VXB_DEV_ID pDev, UINT32 node, UINT32 ipiBase, UINT32 ipis, UINT32 * pBase);

IMPORT int vxbIntAlloc
    (
    UINT32                 count, /* number of interrupt to request */
    VXB_DYNC_INT_ENTRY   * vxbDyncIntEntry
    );

IMPORT void vxbIntFree
    (
    UINT32               count,
    VXB_DYNC_INT_ENTRY * vxbDyncIntEntry
    );

IMPORT STATUS vxbDevMatch
    (
    VXB_DEV_ID pDev
    );

IMPORT STATUS vxbIntReroute (VXB_RESOURCE * pRes, cpuset_t destCpu);
#ifdef _WRS_CONFIG_SMP
IMPORT STATUS vxbIntToCpuRoute (unsigned int destCpu);
#endif /* _WRS_CONFIG_SMP */

IMPORT STATUS vxbIntLibInit (UINT32 numDefer);

IMPORT BOOL sysIntEnableFlagGet (void);
IMPORT void sysIntEnableFlagSet (void);

#ifdef __cplusplus
}
#endif

#include <hwif/methods/vxbIntMethod.h>

#endif /* _INCvxbIntLibh */
