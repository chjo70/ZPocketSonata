/* pxTraceEventSetLibCommonP.h - private header for trace event sets */

/* Copyright 2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01b,28apr10,pad  Moved extern C statement after include statements.
01a,05jul06,tcr  created
*/

/*
DESCRIPTION

This header contains definitions and macros for manipulating POSIX trace event
sets. They are available in kernel and user-level.

*/

#ifndef __INCpxTraceEventSetLibPh
#define __INCpxTraceEventSetLibPh

#include <base/b_trace_event_id_t.h>
#include <base/b_trace_event_set_t.h>

#ifdef __cplusplus
extern "C" {
#endif

    
/* defines */

#define OP_ADD  0
#define OP_DEL  1
#define OP_TEST 2

#define EVENT_SET_MAGIC 0x65736574
    
#define TRACE_EVENT_SET_VALID(eventSet) (eventSet != NULL && \
                                         eventSet->_EventSetMagic == EVENT_SET_MAGIC)

/*
 * macro evaluates non-zero if event id is in the system event range
 */
    
#define POSIX_EVENT_IS_SYSTEM_EVENT(eventId)                            \
    ((eventId >= _TRACE_SYS_EVENTS_START) &&                            \
     (eventId < (_TRACE_SYS_EVENTS_START + _TRACE_NUM_SYS_EVENTS)))

/*
 * macro evaluates non-zero if event id is in the implementation-defined system
 * event range
 */
    
#define POSIX_EVENT_IS_IMPLDEF_SYS_EVENT(eventId)                       \
    ((eventId >= _TRACE_IMPLDEF_SYS_EVENTS_START) &&                    \
    (eventId < (_TRACE_IMPLDEF_SYS_EVENTS_START + _TRACE_NUM_IMPLDEF_SYS_EVENTS)))

/*
 * macro evaluates non-zero if event id is in the user event range
 */
    
#define POSIX_EVENT_IS_USER_EVENT(eventId)                              \
    ((eventId >= _TRACE_USR_EVENTS_START) &&                            \
     (eventId < (_TRACE_USR_EVENTS_START + TRACE_USER_EVENT_MAX)))

    
#ifdef _WRS_KERNEL
extern int traceEventSetTest
    (
    trace_event_id_t            event_id,
    trace_event_set_t *         set
    );

extern int pxTraceEventSetUpdate
    (
    trace_event_set_t *         pDest,
    const trace_event_set_t *   pSrc,
    int how
    );
    
extern int pxTraceEventSetGet
    (
    trace_event_set_t *         pDest,
    const trace_event_set_t *   pSrc
    );

    
#endif /* _WRS_KERNEL */

#ifdef __cplusplus
}
#endif

#endif /* __INCpxTraceEventSetLibP_h */
