/* pxTraceStreamBufferLibP.h - private header for POSIX trace buffer */

/* Copyright 2005-2006, 2010, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01d,23jul12,wzc  WIND00358305 - Remove building warnings.
01c,29apr10,pad  Moved extern C statement after include statements.
01b,01aug06,tcr  fix format
01a,15nov05,tcr  created
*/

/*
DESCRIPTION
This file contains definitions for the in-memory buffer of the POSIX trace
facility in RTPs.
*/

#ifndef __INCpxTraceStreamBufferLibPh
#define __INCpxTraceStreamBufferLibPh

#include <base/b_pthread_t.h>
#include <base/b_trace_attr_t.h>
#include <base/b_trace_event_id_t.h>
#include <base/b_struct_posix_trace_event_info.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * overrunState tracks whether, and how much, of the overrun data has been
 * handled.
 *
 * 0 - No overrun
 * 1 - Overrun detected, no events transmitted
 * 2 - Overrun over, OVERRUN event transmitted but not RESUME
 *
 *
 * State      Condition                    Action                    Next state
 *
 * 0    | Read                  |                                          |  0
 * 0    | Write - No event loss |                                          |  0
 * 0    | Write - Event lost    | Drop event, and save time of lost event  |  1
 *      |                       | in overrunStart                          |
 * 1    | Event read            | Send OVERRUN event                       |  2
 * 1    | Write                 |                                          |  2
 * 2    | Read                  | Send RESUME event, with time of next     |  0
 *      |                       | event in buffer                          |
 * 2    | Write                 |                                          |  1
 *
 */
 
/* typedefs */

typedef struct trace_stream_buffer
    {
    struct trace_stream *       pStream;
    size_t                      readIndex;
    size_t                      writeIndex;
    size_t                      freeSpace;
    char *                      dataBlockStart;
    size_t                      dataBlockSizeRequested;
    size_t                      dataBlockSizeActual;    
    SEM_ID                      ptrUpdateSem;
    SEM_ID                      dataAvailableSem;
    int                         overrunState;
    struct timespec             overrunStartTime;
    pid_t                       overrunPid;
    pthread_t                   overrunThreadId;
    void *                      overrunProgAddress;
    } TRACE_STREAM_BUFFER;

typedef unsigned char           TRACE_EVENT_TRUNCATION_TYPE;

/* function declarations */

extern int pxTraceStreamBufferCreate (trace_attr_t * pAttr,
                                      struct trace_stream * pStream);

extern void pxTraceStreamBufferDelete (TRACE_STREAM_BUFFER * pBuffer);

extern void pxTraceStreamBufferClear (TRACE_STREAM_BUFFER * pBuffer);

extern STATUS pxTraceStreamBufferWrite (TRACE_STREAM_BUFFER * pBuffer,
                                        struct posix_trace_event_info * evtInfo,
                                        char * src);
extern int pxTraceStreamBufferRead (TRACE_STREAM_BUFFER * pBuffer,
                                       struct posix_trace_event_info * evtInfo,
                                       char * dest, size_t dataSize,
                                       size_t * pNumBytesRead,
                                       int * pUnavailable, int timeout);

#ifdef __cplusplus
}
#endif

#endif /* __INCpxTraceStreamBufferLibPh */

