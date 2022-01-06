/* taskPxLibP.h - header for POSIX thread support in VxWorks task */

/*
 * Copyright (c) 2005-2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01h,17may10,jpb  Updated TASK_PX_SS_SCHED_INFO struct.
01g,04may10,jpb  Updated for LP64 adaptation.  Added function binding
                 prototypes.
01f,29apr10,pad  Moved extern C statement after include statements.
01e,07jun06,jln  added support for SCHED_SPORADIC thread
01d,28feb06,jln  added taskPxAttrCreate()
01c,20jan06,jln  added TASK_PX_SCHED_INFO structure
01b,05aug05,jln  added taskPxWindTickAnnounceHook
01a,25jun05,jln  Created
*/

#ifndef __INCtaskPxLibPh
#define __INCtaskPxLibPh

#include <private/taskLibP.h>
#include <private/taskPxLibCommonP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* typedef */

/* 
 * Base structure for schedInfo. Adding new members to this structure 
 * will change the offset in TASK_PX_SS_SCHED_INFO.
 */

typedef struct px_base_sched_info
   {
   UINT64          execTick;       /* thread execution tick */
   Q_HEAD          execTickQHead;  /* tick queue for CPU-time clock */
   UINT32          schedPolicy;    /* scheduling policy */
   } PX_BASE_SCHED_INFO;

/* POSIX thread scheduling information */

typedef struct task_px_sched_info
    {
    PX_BASE_SCHED_INFO  pxBaseSched;
    } TASK_PX_SCHED_INFO;

/* SCHED_SPORADIC thread replenishment event structure */

typedef struct px_ss_repl_event
    {
    UINT64         replTime;	    /* replenishment time */
    UINT32         replAmt;	    /* replenishment amount in tick */
    UINT32         flag;	    /* attribute (not used yet) */
    } PX_SS_REPL_EVENT;

/* POSIX SCHED_SPORADIC thread scheduler information */

typedef struct task_px_ss_sched_info
    {
    PX_BASE_SCHED_INFO  pxBaseSched;/* 0x00/0x00: common sched structure */
    UINT32 	    curState;	    /* 0x1c/0x2c: current sched_sporadic state */

    /* don't add any field before this to ensure valid offset value */ 

    UINT64          replTime;       /* 0x20/0x30: next replenishment time */
    ULONG	    replPeriod;     /* 0x28/0x38: replenishment period */
    TASK_ID	    tid;            /* 0x2c/0x40: task ID */
    ULONG 	    execCapacity;   /* 0x30/0x48: execution capacity in tick */
    ULONG           initBudget;     /* 0x34/0x50: initial exec budget in tick */
    Q_NODE	    ssTickNode;     /* 0x38/0x58 : delta time queue node */
    PX_SS_REPL_EVENT * pSsReplList; /* 0x48/0x78: replenishment event list */
    struct timespec ssReplPeriod;   /* 0x4c/0x80: original replenishment period */
    struct timespec ssInitBudget;   /* 0x54/0x90: original initial budget */
    UINT32          accuExecTime;   /* 0x5c/0xA0: accu exec time since ACTIVE */
    UINT32          regPrio;        /* 0x60/0xA4: SCHED_SPORADIC normal priority */
    UINT32          lowPrio;        /* 0x64/0xA8: SCHED_SPORADIC low priority */
    int		    replPutIx;      /* 0x68/0xAC: put index for replenishment list */    
    int             replGetIx;      /* 0x6C/0xB0: get index for replenishment list */
    int             maxReplNum;     /* 0x70/0xB4: maximum replenishment number */
    int             replNum;        /* 0x74/0xB8: pending replenishment number */
    } TASK_PX_SS_SCHED_INFO;

/* define */

/* SCHED_SPOARDIC state definition */

#define PX_SS_STATE_INIT		0x01
#define PX_SS_STATE_ACTIVE		0x02
#define PX_SS_STATE_BLOCK		0x04
#define PX_SS_STATE_LOWPRIO		0x08
#define PX_SS_STATE_STARTEXEC           0x10
#define PX_SS_STATE_PREEMPTED           0x20

/* Function declarations */

extern STATUS 		taskPxLibInit (void);
extern STATUS 		taskPxAttrSet (TASK_ID tid, void * pAttr);
extern STATUS           taskPxAttrGet (TASK_ID tid, void * pAttr);
extern STATUS 		taskPxAttrCreate (TASK_ID tid, void * pAttr);
extern void		taskPxWindTickAnnounceHook (WIND_TCB *);

extern void 		pxSSThreadStateActive(TASK_PX_SS_SCHED_INFO * pSsInfo,
					      ULONG * newPrio);
extern void 		pxSSThreadStateBlock (TASK_PX_SS_SCHED_INFO * pSsInfo);
extern void 		pxSSThreadStateInit  (WIND_TCB * pTcb, 
					      TASK_PX_ATTR * pAttr,
                                   	      PX_SS_REPL_EVENT * pReplList, 
					      PX_SS_REPL_EVENT ** pOldReplList);
extern void 		pxSSThreadLibInit   (void);

/* function pointer declarations */

extern STATUS  (*_func_taskPxAttrSet)(TASK_ID, void *);
extern STATUS  (*_func_taskPxAttrGet)(TASK_ID, void *);
extern STATUS  (*_func_taskPxAttrCreate)(TASK_ID, void *);

extern void    (*_func_pxSSThreadIntHook)(void);
extern void    (*_func_pxSSThreadStateInit)(WIND_TCB * pTcb, 
	                                    TASK_PX_ATTR * pAttr, 
	                                    PX_SS_REPL_EVENT * pReplList, 
	                                    PX_SS_REPL_EVENT ** pOldReplList);

#ifdef __cplusplus
}
#endif

#endif /* __INCtaskPxLibPh */
