/* eventLibP.h - private VxWorks events library header file */

/* 
 * Copyright 2001-2003, 2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01d,29jul10,pad  Moved extern C statement after include statements.
01c,24jul06,jpb  Removed duplicated definition of EVENTS_RSRC.
01b,26jun06,jpb  Updated for POSIX namespace conformance.
                 Removed reference to I960
01a,20jan04,hya  created
*/

#ifndef __INCeventLibPh
#define __INCeventLibPh

#ifndef	_ASMLANGUAGE
#include "vxWorks.h"

#include "private/base/b_struct_vx_eventsResourceCb.h"

#ifdef __cplusplus
extern "C" {
#endif

			/* needed for _Vx_EVENTS_RSRC definition */

extern VOIDFUNCPTR eventEvtRtn; /* windview - level 1 event logging */

/* event structure needed in TCB */

typedef struct eventsCb
    {
    UINT32 wanted;	/* 0x00: events wanted				*/
    volatile UINT32 received;	/* 0x04: all events received		*/
    UINT8  options;	/* 0x08: user options				*/
    UINT8  sysflags;	/* 0x09: flags used by internal code only	*/
    UINT8  pad[2];	/* 0x0a: alignment on 32bit, possible extension	*/
    } EVENTS;		/* 0x0c: total size				*/

/* EVENTS.options masks */

#define EVENTS_WAIT_MASK	0x01

/* EVENTS system flags */

#define EVENTS_SYSFLAGS_WAITING	  0x01	/* task is waiting for events 	*/
#define EVENTS_SYSFLAGS_DEL_RSRC  0x02	/* task is deleting rsrc on */
					/* which it is registered	*/
#define EVENTS_SYSFLAGS_UNUSED	  0xfc	/* unused, for future extension	*/

/* event structure needed in resource (semaphores, msg queues) structures */

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
typedef _Vx_EVENTS_RSRC EVENTS_RSRC;
#endif

/* These events are for system use only. */

#define VXEV25 0x01000000
#define VXEV26 0x02000000
#define VXEV27 0x04000000
#define VXEV28 0x08000000
#define VXEV29 0x10000000
#define VXEV30 0x20000000
#define VXEV31 0x40000000
#define VXEV32 0x80000000

#define VXEV_RESERVED 0xff000000

#if defined(__STDC__) || defined(__cplusplus)

extern STATUS	rscEventSend (EVENTS_RSRC *);
extern void     eventInit (EVENTS_RSRC *);

#else /* __STDC__ */

extern STATUS	rscEventSend ();
extern void     eventInit ();

#endif /* __STDC */

#else	/* _ASMLANGUAGE */

#define EVENTS_RSRC_REGISTERED		0x0
#define EVENTS_RSRC_TASKID		0x4
#define EVENTS_RSRC_OPTIONS		0x8

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCeventLibPh */

