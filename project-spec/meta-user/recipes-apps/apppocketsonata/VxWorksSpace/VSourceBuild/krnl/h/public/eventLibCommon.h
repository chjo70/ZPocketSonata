/* eventLibCommon.h - common events library header file */

/*
 * Copyright (c) 2001-2003, 2009-2010, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
20may17,dlk  Introduce eventReceiveEx() to control early return due to
             EINTR or EDOOM on a call-by-call basis (F5593).
16jun10,pcs  Change data type of timeout from an int to _Vx_ticks_t
28apr10,pad  Moved extern C statement after include statements.
12mar09,pcs  Updated to add support for the LP64 data model.
26feb04,dcc  moved VX_EVT_CTL_CMD definition to the not-assembly part of
             the file.
05sep03,dcc  written based on v01e of the kernel version of eventLib.h
*/

#ifndef __INCeventLibCommonh
#define __INCeventLibCommonh

#include "vxWorks.h"
#include "vwModNum.h"

#ifdef __cplusplus
extern "C" {
#endif

/* errnos */

#define S_eventLib_TIMEOUT			(M_eventLib | 0x0001)
#define S_eventLib_NOT_ALL_EVENTS		(M_eventLib | 0x0002)
#define S_eventLib_ALREADY_REGISTERED		(M_eventLib | 0x0003)
#define S_eventLib_EVENTSEND_FAILED		(M_eventLib | 0x0004)
#define S_eventLib_ZERO_EVENTS			(M_eventLib | 0x0005)
#define S_eventLib_TASK_NOT_REGISTERED		(M_eventLib | 0x0006)
#define S_eventLib_NULL_TASKID_AT_INT_LEVEL	(M_eventLib | 0x0007)

/* options */

#define EVENTS_WAIT_ALL		0x00	/* wait for all events to occur */
#define EVENTS_WAIT_ANY		0x01	/* wait for one of many events  */
#define EVENTS_RETURN_ALL	0x02	/* return all events received   */
#define EVENTS_KEEP_UNWANTED	0x04	/* don't clear unwanted events	*/
#define EVENTS_FETCH		0x80	/* return events received immediately */

/* resource-related options */

#define EVENTS_OPTIONS_NONE	0x00
#define EVENTS_SEND_ONCE	0x01  /* unregister events after eventSend   */
#define EVENTS_ALLOW_OVERWRITE	0x02  /* can overwrite previous registration */
#define EVENTS_SEND_IF_FREE	0x04  /* send events in xxxEvStart()         */

/* additional eventReceiveEx() options */

#define EVENTS_Q_INTERRUPTIBLE	    0x10000    /* signals wake up RTP tasks */
#define EVENTS_TASK_DELETION_WAKEUP 0x20000    /* attempt to delete a deletion-
                                                safe task waiting for events
                                                unpends the task (EDOOM) */

/*
 * Defines for all 24 events available to users. Events 25 to 32 are reserved
 * for system use and should never be used outside of that scope
 */

#define VXEV01 0x00000001
#define VXEV02 0x00000002
#define VXEV03 0x00000004
#define VXEV04 0x00000008
#define VXEV05 0x00000010
#define VXEV06 0x00000020
#define VXEV07 0x00000040
#define VXEV08 0x00000080
#define VXEV09 0x00000100
#define VXEV10 0x00000200
#define VXEV11 0x00000400
#define VXEV12 0x00000800
#define VXEV13 0x00001000
#define VXEV14 0x00002000
#define VXEV15 0x00004000
#define VXEV16 0x00008000
#define VXEV17 0x00010000
#define VXEV18 0x00020000
#define VXEV19 0x00040000
#define VXEV20 0x00080000
#define VXEV21 0x00100000
#define VXEV22 0x00200000
#define VXEV23 0x00400000
#define VXEV24 0x00800000

#define VXEV_USER_MASK 0x00ffffff

#ifndef	_ASMLANGUAGE

/* typedefs */

typedef struct events_desc
    {
    UINT32 wanted;		/* 0x00/0x00: events wanted			*/
    UINT32 received;		/* 0x04/0x04: all events received		*/
    UINT8  options;		/* 0x08/0x08: user options			*/
    } EVENTS_DESC;

typedef UINT32 _Vx_event_t;

/* function declaration */

extern STATUS eventSend (TASK_ID taskId, _Vx_event_t events);
extern STATUS eventReceive (
			    _Vx_event_t events,
			    UINT8 options,
			    _Vx_ticks_t timeout,
			    _Vx_event_t *eventsReceived
			   );
extern STATUS eventReceiveEx (_Vx_event_t events, UINT32 options,
                              _Vx_ticks_t timeout, _Vx_event_t * eventsReceived);
extern STATUS eventClear (void);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCeventLibCommonh */

