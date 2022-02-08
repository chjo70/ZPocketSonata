/* pxTraceSysCall.h - system call definitions for POSIX trace */

/*
 * Copyright (c) 2005 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */

/*
modification history
--------------------
01a,21nov05,tcr  written
*/


#ifndef __INCpxTraceSysCallh
#define __INCpxTraceSysCallh

#ifdef __cplusplus
extern "C" {
#endif

/* prototypes for the system calls for POSIX trace */
    
extern int pxTraceCreation
    (
    int                         cmd,
    pid_t                       pid,
    const trace_attr_t *        attr,
    int                         fd,
    trace_id_t *                trid
    );
    
extern int pxTraceCtl
    (int                        cmd,
     trace_id_t                 trid,
     const trace_event_set_t *  filter,
     int                        how,
     pthread_t                  thread,
     void *                     pc,
     void *                     ptr_out
     );

extern int pxTraceEvent
    (
    int                         cmd,
    trace_event_id_t            id_in,
    const char *                data,
    size_t                      data_len,
    pthread_t                   thread,
    void *                      pc,
    trace_event_id_t *          id_out
    );

extern int pxTraceEventNameQuery
    (
    int                         cmd,
    trace_id_t                  trid,
    int                         id_in1,
    int                         id_in2,
    const char *                name,
    trace_event_id_t *          id_out,
    int *                       unavailable
    );

extern int pxTraceLog
    (
    int                         cmd,
    trace_id_t                  trid_in,
    int                         fd,
    trace_id_t *                trid_out
    );

extern int pxTraceEventGet
    (
    int                         cmd,
    trace_id_t                  trid,
    size_t                      num_bytes,
    const struct timespec *     timeout,
    struct posix_trace_event_info * event,
    void *                      data,
    size_t *                    data_len,
    int *                       unavailable
    );

    
#ifdef __cplusplus
}
#endif

#endif /* __INCpxTraceSysCallh */
