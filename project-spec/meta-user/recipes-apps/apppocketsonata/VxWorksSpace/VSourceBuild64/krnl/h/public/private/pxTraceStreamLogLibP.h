/* pxTraceStreamLogLibP.h - private header for POSIX trace stream log */

/* Copyright 2005-2006, 2010, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01c,24jul12,wzc  WIND00358305 - Remove building warnings.
01b,29apr10,pad  Moved extern C statement after include statements.
01a,02dec05,tcr  created
*/

#ifndef __INCpxTraceStreamLogLibP_h
#define __INCpxTraceStreamLogLibP_h

#include <base/b_struct_posix_trace_event_info.h>
#include <base/b_trace_attr_t.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * These are event identifiers used in the log only. They are not specified
 *   by POSIX and are not seen by a POSIX analyzer process
 */
    
#define EVENT_POSIX_EVENTNAME   10
#define EVENT_BSP_NAME          11
#define EVENT_OS_VERSION        12
#define EVENT_SIZE_INFO         13
#define EVENT_ATTRIBUTES        14
#define EVENT_LOG_POSITIONS     15
#define EVENT_STATUS            16
    
/* typedefs */

typedef struct
    {
    struct trace_stream *       pStream;
    int                         fd;
    off_t                       writeIndex;
    off_t                       readIndex;
    size_t                      dataSize;
    size_t                      freeSpace;
    SEM_ID                      ptrUpdateSem;

    /* offset in file of event data region */
    off_t                       dataStartPos;
    
    /* offset where we should write position data when file is closed */
    off_t                       dataPositionPos;

    /* offset in file to start of name event data */
    off_t                       eventNameOffset;

    /* offset in file at which to start reading event data */
    off_t                       readPosition;
    } TRACE_STREAM_LOG;

/* function declarations */

extern STATUS pxTraceStreamLogWrite
    (
    TRACE_STREAM_LOG *                    pLog,           /* log to write to */
    const struct posix_trace_event_info * pEventInfo,     /* event info */
    const char *                          src,            /* data payload  */
    size_t                                payloadSize     /* data payload size */
    );

extern int pxTraceStreamLogCreate
    (
    int                         fd,
    trace_attr_t *              pAttr,
    struct trace_stream *       pStream
    );

extern int pxTraceStreamLogOpen
    (
    int                         fd,
    struct trace_stream *       pStream
    );

extern int pxTraceStreamLogDelete
    (
    TRACE_STREAM_LOG *  pLog
    );

extern int pxTraceStreamLogFinish
    (
    TRACE_STREAM_LOG *          pLog
    );
    
extern int pxTraceStreamLogClear
    (
    TRACE_STREAM_LOG *          pLog
    );
    
extern int pxTraceStreamLogEventRead
    (
    struct trace_stream *               pStream,
    struct posix_trace_event_info *     eventInfo,
    void *                              data,
    size_t                              num_bytes,
    size_t *                            data_len,
    int *                               unavailable
    );

extern int pxTraceStreamLogRewind
    (
    TRACE_STREAM_LOG *          pLog
    );

#ifdef __cplusplus
}
#endif

#endif /* __INCpxTraceStreamLogLibP_h */

