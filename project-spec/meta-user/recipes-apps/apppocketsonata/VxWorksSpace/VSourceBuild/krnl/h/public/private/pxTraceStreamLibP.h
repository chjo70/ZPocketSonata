/* pxTraceStreamLibP.h - private header for POSIX trace */

/* Copyright 2005-2007, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01d,29apr10,pad  Moved extern C statement after include statements.
01c,27feb07,tcr  Fix warnings under gcc
01b,21jul06,tcr  remove pxTraceStreamCreate() prototype, fix format, fix stream
                 full handling in POSIX_TRACE_UNTIL_FULL mode
01a,04nov05,tcr  created
*/

/*
DESCRIPTION
This header contains definitions of kernel structures and functions to support
the POSIX trace facility in RTPs.
*/
  
#ifndef __INCpxTraceStreamLibPh
#define __INCpxTraceStreamLibPh

#include <base/b_trace_id_t.h>
#include <base/b_struct_posix_trace_status_info.h>
#include <base/b_struct_posix_trace_event_info.h>
#include <base/b_trace_event_set_t.h>

#include <private/pxTraceStreamBufferLibP.h>
#include <private/pxTraceStreamLogLibP.h>
#include <private/pxTraceHashTblLibP.h>

#include <private/pxTraceLibCommonP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

typedef enum    /* trace type (active or pre-recorded) */
    {
    TRACE_TYPE_STREAM_WITHOUT_LOG = 1,
    TRACE_TYPE_STREAM_WITH_LOG = 2,
    TRACE_TYPE_PRE_RECORDED = 4
    } TRACE_TYPE_ENUM;

typedef struct trace_stream
    {
    /* POSIX traces are Wind objects */
    OBJ_CORE                    objCore;
    
    /* an RTP has a list of attached traces. This is the node for that list */
    DL_NODE                     rtpAttachedTraceNode;

    /* indicate what operations are valid on this trace */
    TRACE_TYPE_ENUM             traceType;

    trace_attr_t                traceAttributes;

    /* pointer to in-memory stream data */
    TRACE_STREAM_BUFFER *       pStreamBuffer;

    /* policies and status indicators for stream (as POSIX) */
    POSIX_TRACE_STATUS_INFO     status;

    int                         streamFullPolicy;
    int                         logFullPolicy;

    /*
     * autoRestart indicates that logging for a stream was suspended
     * automatically, and will restart when the stream becomes empty
     */
    
    int                         autoRestart;
    
    /* trace owner */
    RTP_ID                      owningRtp;

    /* traced RTP */
    RTP_ID                      tracedRtp;

    /* pointer to control structure for file-based log */
    TRACE_STREAM_LOG *          pStreamLog;

    /* filter for stored events (set bits are filtered out) */
    trace_event_set_t           eventSet;

    /* For pre-recorded logs there will be no RTP to attach hash tbl to */
    TRACE_HASH_TBL *            pHashTbl;

    /* hash table iter key */
    TRACE_HASH_ITER_KEY *       pIterKey;

    } TRACE_STREAM;

/*
 * This structure is attached to the RTP being traced. It provides a place to
 * put a list of traces for a given RTP, and the hashtable for the names
 */

typedef struct trace_data
    {
    DL_LIST             traceList;
    TRACE_HASH_TBL *    pHashTbl;
    } TRACE_RTP_DATA;

/* function declarations */

extern STATUS pxTraceStreamLibInit (void);

extern int pxTraceStreamTraceCreate (RTP_ID rtpId, RTP_ID pidToTrace,
                                     trace_attr_t * pAttr,
                                     TRACE_TYPE_ENUM traceType, int fd,
                                     trace_id_t * trid);

extern STATUS pxTraceStreamDelete (TRACE_STREAM * pStream);

extern int pxTraceStreamLoggingStart (TRACE_STREAM * pStream,
                                      pthread_t posix_thread_id, void * pc);

extern int pxTraceStreamLoggingStop (TRACE_STREAM * pStream,
                                     pthread_t posix_thread_id, void * pc,
                                     int automatic);

extern int pxTraceStreamTraceEvent (RTP_ID rtpId, trace_event_id_t eventId,
                                    void * dataPtr, size_t dataLen,
                                    pthread_t posix_thread_id, void * pc);

extern int pxTraceStreamEventIdOpen (RTP_ID rtpId, const char * event_name, 
                                     trace_event_id_t * event_id);

extern int pxTraceStreamTridEventIdOpen (RTP_ID rtpId, TRACE_STREAM * pStream,
                                         const char * event_name,
                                         trace_event_id_t * event_id);

extern int pxTraceStreamEventIdGetName (RTP_ID rtpId, TRACE_STREAM * pStream,
                                        trace_event_id_t event_id,
                                        char * event_name);

extern int pxTraceStreamEventIdEqual (RTP_ID rtpId, TRACE_STREAM * pStream,
                                      trace_event_id_t id1,
                                      trace_event_id_t id2);
    
extern int pxTraceStreamEventTypeListGetNextId (RTP_ID rtpId,
                                                TRACE_STREAM * pStream,
                                                trace_event_id_t * event,
                                                int * unavailable);

extern int pxTraceStreamEventTypeListRewind (RTP_ID rtpId,
                                             TRACE_STREAM * pStream);

extern int pxTraceStreamGetNextEvent (TRACE_STREAM * pStream,
                                      struct posix_trace_event_info * event,
                                      void * data, size_t num_bytes,
                                      size_t * data_len,
                                      int * unavailable);

extern int pxTraceStreamTimedGetNextEvent (TRACE_STREAM * pStream,
                                          struct posix_trace_event_info * event,
                                           void * data, size_t num_bytes,
                                           size_t * data_len, int * unavailable,
                                           const struct timespec * absTimeout);

extern int pxTraceStreamClear (TRACE_STREAM * pStream);

extern int pxTraceStreamOpen (RTP_ID rtpId, int fd,trace_id_t * trid);
    
extern int pxTraceStreamClose (RTP_ID rtpId, trace_id_t trid);

extern int pxTraceStreamRewind (RTP_ID rtpId, trace_id_t trid);

extern int pxTraceStreamEventFilterGet (TRACE_STREAM * pStream,
                                        trace_event_set_t * pSet);

extern int pxTraceStreamStatusGet (TRACE_STREAM * pStream,
                                  struct posix_trace_status_info * status_info);

extern int pxTraceStreamEventFilterSet (TRACE_STREAM * pStream,    
                                        const trace_event_set_t * set, int how,
                                        pthread_t posix_thread_id, void * pc);

extern int pxTraceStreamAttrGet (TRACE_STREAM * pStream, trace_attr_t * pAttr);

extern int pxTraceStreamFlush (TRACE_STREAM * pStream,
                               pthread_t posix_thread_id,
                               void * pc);

extern int pxTraceStreamShutdown (TRACE_STREAM * pStream,
                                  pthread_t posix_thread_id, void * pc);

#ifdef __cplusplus
}
#endif

#endif /* __INCpxTraceStreamLibPh */
