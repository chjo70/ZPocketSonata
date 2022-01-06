/* readyQLibP.h - ready queue header file */

/*
 * Copyright (c) 2008-2009, 2014, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
08oct15,h_k  added _func_readyQRotateOrderListGet. (V7COR-3679)
18dec14,h_k  added _func_readyQReservationCheck. (V7COR-2389)
10feb09,zl   added readyQInit() parameters
20feb09,cww  Add dynamic CPU reservation support
27aug08,jpb  Renamed VSB header file
24jun08,jpb  Added include path for kernel configurations options set in
             vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
21apr08,zl   changed cpuIndex parameters to unsigned
10mar08,zl   added READY_Q_NODE_TO_TCB()
03mar08,zl   switched to multi-implementation API
22feb07,zl   written.
*/

#ifndef __INCreadyQLibPh
#define __INCreadyQLibPh

#include <vxWorks.h>
#include <vsbConfig.h>
#include <taskLib.h>
#include <private/qLibP.h>

#ifdef __cplusplus
extern "C" {
#endif


#ifdef	_WRS_CONFIG_SMP

/* ready queue access macros */

#define READY_Q_CPU_INIT(cpuIx, pTcb)	readyQCpuInit (cpuIx, pTcb)
#define READY_Q_TASK_INIT(pTcb)		readyQTaskInit (pTcb)
#define READY_Q_PUT(pTcb)		readyQPut (pTcb)
#define READY_Q_REMOVE(pTcb)		readyQRemove (pTcb)
#define READY_Q_RESORT(pTcb)		readyQResort (pTcb)
#define READY_Q_ROTATE(pTcb)		readyQRotate (pTcb)
#define READY_Q_PREEMPT_CHECK(pTcb)	readyQPreemptCheck (pTcb)
#define READY_Q_TASK_GET(cpuIx, pNext)	readyQTaskGet (cpuIx, pNext)
#define READY_Q_NEXT_CPU_GET(cpuIx)	readyQNextCpuGet (cpuIx)
#define READY_Q_NODE_TO_TCB(pNode)	readyQNodeToTcb (pNode)

#define SCHED_REQ_NONE			(-1)	/* no reschedule target CPU */
#define SCHED_REQ_DONE			(-2)	/* reschedule request done */


/* function declarations */

STATUS readyQInit (Q_CLASS_ID qClassId, int nPrio);
STATUS readyQCpuInit (UINT cpuIndex, WIND_TCB * pTcb);
STATUS readyQTaskInit (WIND_TCB * pTcb);
void   readyQPut (WIND_TCB * pTcb);
void   readyQRemove (WIND_TCB * pTcb);
void   readyQResort (WIND_TCB * pTcb);
BOOL   readyQRotate (WIND_TCB * pTcb);
void   readyQPreemptCheck (WIND_TCB * pTcb);
WIND_TCB * readyQTaskGet (UINT cpuIndex, int * pNextCpu);
int    readyQNextCpuGet (UINT cpuIndex);
WIND_TCB * readyQNodeToTcb (Q_NODE * pNode);

extern void readyQReservationCheck(UINT);

/* function pointer declarations */

extern void (*_func_readyQReservationCheck) (UINT);

extern WIND_TCB ** (*_func_readyQRotateOrderListGet) (void);

#else /* _WRS_CONFIG_SMP */

extern Q_HEAD	readyQHead;		/* queue for task ready queue */

#define READY_Q_PUT(pTcb)						\
	    Q_PUT (&readyQHead, &pTcb->qNode, pTcb->priority)
#define READY_Q_REMOVE(pTcb) 						\
	    Q_REMOVE (&readyQHead, &pTcb->qNode)
#define READY_Q_RESORT(pTcb)	 					\
	    Q_RESORT (&readyQHead, &pTcb->qNode, pTcb->priority)
#define READY_Q_ROTATE(pTcb)						\
	do  {								\
            Q_REMOVE (&readyQHead, &(pTcb)->qNode);			\
            Q_PUT (&readyQHead, &(pTcb)->qNode, (pTcb)->priority);	\
	    } while ((FALSE))
#define READY_Q_PREEMPT_CHECK(pTcb)	/* nop */
#define READY_Q_NODE_TO_TCB(pNode)	NODE_PTR_TO_TCB (pNode)

#endif /* _WRS_CONFIG_SMP */


#ifdef __cplusplus
}
#endif

#endif /* __INCreadyQLibPh */
