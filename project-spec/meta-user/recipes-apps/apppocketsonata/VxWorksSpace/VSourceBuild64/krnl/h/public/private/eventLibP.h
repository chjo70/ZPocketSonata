/* eventLibP.h - private VxWorks events library header file */

/*
 * Copyright (c) 2001-2010, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
20may17,dlk  Introduce eventReceiveEx() to control early return due to
             EINTR or EDOOM on a call-by-call basis (F5593)
31aug10,cww  Use dynamically generated offsets in offset macros
25aug10,kk   add _func_eventTaskShow and _func_eventRsrcShow
29jul10,gls  removed EVENTS_SYSFLAGS_WAITING (WIND00225732)
16jun10,pcs  Change data type of timeout from an int to _Vx_ticks_t
29apr10,pad  Moved extern C statement after include statements.
13apr10,jpb  Added function pointer declarations.
29may09,jmp  Added vxEventPendQ as external.
11may09,pcs  Change the datatype of parameter isRsrcFree, in fn.
             eventStart from FUNCPTR to OBJ_EV_IS_FREE_FUNC.
12mar09,pcs  Updated to add support for the LP64 data model.
23oct08,zl   added options parameter to eventLibInit().
11aug08,tcr  remove redundant funcptr
14aug07,zl   Added lockKey parameter to eventStart().
10jan05,job  Added EVENT_RTP_DELETE_STATE event definition (SPR#105375)
02sep04,ans  Added JOB_TASK_DONE_EVENT event definition
27may04,job  Added EVENT_RTP_NORMAL_STATE event definition.
15jul03,kam  merging from TOR2_2-CP1-F label
04jun03,bwa  Added '#include "eventLib.h'.
20jan03,bwa  Added EVENTS_SYSFLAGS_DEL_RSRC definition.
15jan02,bwa  Created list of events reserved for system use.
06nov01,aeg  added eventRsrcShow() and eventTaskShow() prototypes.
17oct01,bwa  Added eventRsrcSend() prototype.
20sep01,bwa  Created
*/

#ifndef __INCeventLibPh
#define __INCeventLibPh

#include <vxWorks.h>
#include <eventLib.h>
#include <private/qLibP.h>

#ifndef	_ASMLANGUAGE

#ifdef __cplusplus
extern "C" {
#endif

/* event structure needed in TCB */

typedef struct eventsCb
    {
    _Vx_event_t wanted;	/* 0x00/0x00: events wanted			     */
    volatile _Vx_event_t received; /* 0x04/0x04: all events received	     */
    UINT8  options;	/* 0x08/0x08: user options			     */
    UINT8  sysflags;	/* 0x09/0x09: flags used by internal code only	     */
    UINT8  pad[2];	/* 0x0a/0x0a: alignment on 32bit, possible extension */
    } EVENTS;		/* 0x0c/0x0c: total size			     */

/* EVENTS.options masks */

#define EVENTS_WAIT_MASK	0x01

/*
 * Presently two eventReceiveEx() option bits determine which event
 * pend queue is used.
 * The number of possible subsets of these two flags
 * is the number of global event pend queues:
 */
#define EVENT_PEND_QUEUES_NUM (1U << 2U)
/* Map the two flags to global event queue index */
#define EVENTS_QOPT_TO_IDX(x)   (((x) >> 16U) & (EVENT_PEND_QUEUES_NUM - 1))

/* Is the task pended on one of the global event queues? */
#define EVENT_PENDED_TCB(pTcb) \
  (((pTcb)->status & WIND_PEND) != 0 && EVENT_WAS_PENDED_TCB(pTcb))

#define EVENT_WAS_PENDED_TCB(pTcb)                             \
  ((pTcb)->pPendQ >= &vxEventPendQs[0] &&                      \
   (pTcb)->pPendQ < &vxEventPendQs[EVENT_PEND_QUEUES_NUM])

/* EVENTS system flags */

#define EVENTS_SYSFLAGS_DEL_RSRC  0x01	/* task is deleting rsrc on */
					/* which it is registered	*/
#define EVENTS_SYSFLAGS_UNUSED	  0xfe	/* unused, for future extension	*/

/* event structure needed in resource (semaphores, msg queues) structures */

typedef struct eventsResourceCb
    {
    TASK_ID taskId;	/* 0x00/0x00: task registered for that resource	  */
    UINT32  registered;	/* 0x04/0x08: events registered for that resource */
    UINT8   options;	/* 0x08/0x0c: user options			  */
    UINT8   pad[3];	/* 0x09/0x0d: alignment on 32bit, possible extension */
    } EVENTS_RSRC;	/* 0x0c/0x10: total size			  */

typedef BOOL (*OBJ_EV_IS_FREE_FUNC)        (OBJ_ID objId);

/* These events are for system use only. */

#define VXEV25 0x01000000
#define VXEV26 0x02000000
#define VXEV27 0x04000000
#define VXEV28 0x08000000
#define VXEV29 0x10000000
#define VXEV30 0x20000000
#define VXEV31 0x40000000
#define VXEV32 0x80000000

#define EVENT_RTP_NORMAL_STATE VXEV25		/* RTP -> NORMAL state event */
#define EVENT_RTP_DELETE_STATE VXEV26		/* RTP -> DELETE state event */
#define JOB_TASK_DONE_EVENT    VXEV27           /* client <-> tJobTask  */

#define VXEV_RESERVED 0xff000000

/* variable declarations */

extern Q_HEAD	vxEventPendQs [EVENT_PEND_QUEUES_NUM];

/* function declarations */

extern void 	eventLibInit	(UINT options);
extern void 	eventInit	(EVENTS_RSRC * pEvRsrc);
extern void 	eventTerminate 	(const EVENTS_RSRC * pEvRsrc);
extern void 	semEvLibInit	(void);
extern void 	msgQEvLibInit	(void);
extern STATUS 	eventStart	(OBJ_ID objId, EVENTS_RSRC * pEvRsrc,
				 OBJ_EV_IS_FREE_FUNC isRsrcFree,
                                 _Vx_event_t events, UINT8 options,
                                 int lockKey);
extern STATUS	eventRsrcSend	(TASK_ID taskId, _Vx_event_t events);
extern STATUS	eventRsrcShow	(EVENTS_RSRC * pEvRsrc);
extern STATUS   eventTaskShow	(TASK_ID tid);

/* function pointer declarations */

extern STATUS    (*_func_eventReceive) (_Vx_event_t events, UINT8 options,
                                        _Vx_ticks_t timeout,
                                        _Vx_event_t *eventsReceived);
extern STATUS    (*_func_eventRsrcSend)(TASK_ID taskId, _Vx_event_t events);
extern STATUS    (*_func_eventSend)(TASK_ID taskId, _Vx_event_t events);
extern void      (*_func_eventTerminate)(const EVENTS_RSRC * pEvRsrc);
extern STATUS    (*_func_eventTaskShow) (TASK_ID tid);
extern STATUS    (*_func_eventRsrcShow) (EVENTS_RSRC *pEvRsrc);

#ifdef __cplusplus
}
#endif

#endif  /* _ASMLANGUAGE */

#endif /* __INCeventLibPh */
