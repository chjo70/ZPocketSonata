/* vxIpiLib.h - VxWorks IPI management library */

/*
 * Copyright (C) 2013 Wind River Systems, Inc.
 * 
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */


/* 
modification history
--------------------
01a,14aug13,l_z  created from vxIpiLib.h(01j)
*/

#ifndef __INCvxIpiLibh
#define __INCvxIpiLibh

/* includes */

#include <hwif/vxBus.h>
#include <subsys/int/vxbIntLib.h>


#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define IPI_INTR_ID_CPC        0
#define IPI_INTR_ID_DEBUG    1
#define IPI_INTR_ID_SCHED    2
#define IPI_INTR_ID_MIPC    3

/* typedef */

typedef void   (*IPI_HANDLER_FUNC)	(void * pArg);

typedef struct vxIpiVec
    {
    UINT32       hVec;      /* hardware vector */
	UINT32       lVec;      /* logical vector  */
    VOIDFUNCPTR  pIsr;      /* ISR */
    void *       pArg;      /* parameter */
    } VXIPI_VEC;


typedef struct vxIpiCtrl
    {
    SL_NODE                ipiList;     /* Next IPI structure             */
    phys_cpuset_t          pCpus;       /* destination CPUs interruptable */
    VXB_DEV_ID             pCtlr;       /* Interrupt Controller           */
    INT32                  ipiCount;    /* Number of IPIs available       */
	VXIPI_VEC *            pIpiVec;     /* IPI vector */
    } VXIPI_CTRL, * VXIPI_CTRL_ID;

/* function prototypes */

IMPORT STATUS vxIpiLibInit        (void);
IMPORT STATUS vxIpiConnect        (INT32 ipiIntrptId,
                     IPI_HANDLER_FUNC ipiHandler,
                     void * ipiArg );
IMPORT STATUS vxIpiEnable        (INT32 ipiIntrptId);
IMPORT STATUS vxIpiEmit            (INT32 ipiIntrptId, cpuset_t cpus);
IMPORT STATUS vxIpiPhysEmit        (INT32 ipiIntrptId,
                     phys_cpuset_t phys_cpuset);
IMPORT STATUS vxIpiDisable        (INT32 ipiIntrptId);
IMPORT STATUS vxIpiDisconnect        (INT32 ipiIntrptId,
                     IPI_HANDLER_FUNC ipiHandler,
                     void * ipiArg);
IMPORT INT32  vxIpiAvailableAlloc    (void);
IMPORT STATUS vxIpiAvailableFree    (INT32 ipiId);
IMPORT STATUS vxIpiPrioGet        (INT32 ipiIntrptId);
IMPORT STATUS vxIpiPrioSet        (INT32 ipiIntrptId);

IMPORT void (*_func_ipiRegister)(VXIPI_CTRL *    pIpiCtrl);



#ifdef __cplusplus
}
#endif

#endif /* __INCvxIpiLibh */

