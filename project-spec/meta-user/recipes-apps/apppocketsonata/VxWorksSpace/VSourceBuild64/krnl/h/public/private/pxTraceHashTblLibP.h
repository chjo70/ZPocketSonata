/* pxTraceHashTblLibP.h - private header for POSIX trace hashtable */

/* Copyright 2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01b,29apr10,pad  Moved extern C statement after include statements.
01a,10jan06,tcr  created
*/

/*
DESCRIPTION
This header contains contains the definitions for using the System Viewer hash
table to store names of events for the POSIX trace system.

*/

#ifndef __INCpxTraceHashTblLibP_h
#define __INCpxTraceHashTblLibP_h

#include <private/wvHashTblLibP.h>
#include <base/b_trace_event_id_t.h>

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

typedef struct
    {
    WV_HASH_TBL *       pWvHashTbl;
    int                 nextUserEvent;
    } TRACE_HASH_TBL;

typedef WV_ITER_KEY     TRACE_HASH_ITER_KEY;

/* function declarations */

extern TRACE_HASH_TBL * pxTraceHashTblCreate (void);
        
extern STATUS pxTraceHashTblDelete (TRACE_HASH_TBL *);

extern TRACE_HASH_ITER_KEY *pxTraceHashTblIterKeyCreate
    (
    TRACE_HASH_TBL *            pHashTbl
    );

extern STATUS pxTraceHashTblInsert
    (
    TRACE_HASH_TBL *    pTbl,
    const char *        eventName,
    size_t              eventNameSize,
    trace_event_id_t *  pEventId
    );

extern STATUS pxTraceHashTblLiteralInsert
    (
    TRACE_HASH_TBL *    pTbl,
    const char *        eventName,
    size_t              nameSize,
    trace_event_id_t    eventId
    );

extern STATUS pxTraceHashTblEventIdFind
    (
    TRACE_HASH_TBL *    pTbl,
    trace_event_id_t    eventId,
    char *              eventName,
    int *               unavailable
    );

extern void pxTraceHashTblIterKeyDelete
    (
    TRACE_HASH_TBL *            pHashTbl,
    TRACE_HASH_ITER_KEY *       pIter
    );

extern trace_event_id_t pxTraceHashTblIterNextGet
    (
    TRACE_HASH_TBL *            pHashTbl,
    TRACE_HASH_ITER_KEY *       pIter,
    int *                       pUnavailable
    );


#ifdef __cplusplus
}
#endif

#endif /* __INCpxTraceHashTblLibP_h */
