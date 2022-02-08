/* b_struct_posix_trace_event_info.h - header defining posix_trace_event_info */

/*
 * Copyright (c) 2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
*/

/*
modification history
--------------------
01c,05nov10,wzc  Fix posix_pid definition in kernel;(WIND00230158)
01b,28apr10,pad  Moved extern C statement after include statements.
01a,04Jul06,tcr  created
*/

#ifndef __INCb_struct_posix_trace_event_infoh
#define __INCb_struct_posix_trace_event_infoh

#include <base/b_trace_event_id_t.h>
#include <base/b_pid_t.h>

#if defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE) || \
    defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

#include <base/b_struct_timespec.h>

#else

#include <time.h>
#endif

#include <base/b_pthread_t.h>

#ifdef __cplusplus
extern "C" {
#endif

    
#ifndef _DEFINED_struct_posix_trace_event_info
#define _DEFINED_struct_posix_trace_event_info

/*
 *  The <trace.h> header shall define the posix_trace_event_info structure that
 *  includes at least the following members:
 */

struct posix_trace_event_info
    {        
    trace_event_id_t    posix_event_id;
#ifdef _WRS_KERNEL
    OBJ_HANDLE          posix_pid;
#else
    pid_t               posix_pid;
#endif
    void *              posix_prog_address;
    int                 posix_truncation_status;
    struct timespec     posix_timestamp;
    pthread_t           posix_thread_id;
    size_t              _Posix_eventdata_length;
    };

#ifdef _WRS_KERNEL
typedef struct posix_trace_event_info   POSIX_TRACE_EVENT_INFO;
#endif

#endif  /* _DEFINED_struct_posix_trace_event_info */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_struct_posix_trace_event_infoh */
