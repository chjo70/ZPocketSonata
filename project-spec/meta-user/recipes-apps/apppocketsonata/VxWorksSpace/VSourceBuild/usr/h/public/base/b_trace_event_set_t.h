/* b_trace_event_set_t.h - definition of trace_event_set_t for POSIX trace */

/*
 * Copyright (c) 2006 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
*/

/*
modification history
--------------------
01a,04jun06,tcr  created
*/

#ifndef __INCb_trace_event_set_th
#define __INCb_trace_event_set_th

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _DEFINED_trace_event_set_t
#define _DEFINED_trace_event_set_t

/*
 * For filters, a set bit represents an event which is filtered out. So a
 * default filter set, which allows everything through, is represented by a
 * structure where the arrays are all zeros.
 */

/* These are the sizes of the event id ranges */
    
#define _TRACE_NUM_IMPLDEF_SYS_EVENTS    64
#define _TRACE_NUM_SYS_EVENTS            64
#define _TRACE_NUM_USER_EVENTS           256
    
/* Calculate the number of bytes required to store the event set */

#define _TRACE_FILTER_ARRAY_SIZE(_NumEvents)        \
       ((_NumEvents + 7) / 8)

typedef struct
    {
    /* Implementation-defined system events */
    unsigned char       _ImplDefSysEventSet [
            _TRACE_FILTER_ARRAY_SIZE(_TRACE_NUM_IMPLDEF_SYS_EVENTS)];

    /* System events defined in POSIX 1003.1 */
    unsigned char       _SystemEventSet [
            _TRACE_FILTER_ARRAY_SIZE(_TRACE_NUM_SYS_EVENTS)];
    
    unsigned char       _UserEventSet [
            _TRACE_FILTER_ARRAY_SIZE(_TRACE_NUM_USER_EVENTS)];
    } _TRACE_EVENT_SET_DATA;
    
typedef struct
    {
    unsigned int                _EventSetMagic;  /* indicates set is initialized */
    _TRACE_EVENT_SET_DATA       _SetData;
    } _TRACE_EVENT_SET;

typedef _TRACE_EVENT_SET        trace_event_set_t;

#undef _TRACE_FILTER_ARRAY_SIZE


#endif /* _DEFINED_trace_event_set_t */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_trace_event_set_th */
