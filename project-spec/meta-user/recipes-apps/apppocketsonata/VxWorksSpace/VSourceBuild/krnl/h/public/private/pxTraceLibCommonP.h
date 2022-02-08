/* pxTraceLibCommonP.h - common header for POSIX trace support */

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
01b,14aug06,tcr  make TRACE_EVENT_SIZE_TYPE a word
01a,04jul06,tcr  created
*/

#ifndef __INCpxTraceLibCommonPh
#define __INCpxTraceLibCommonPh

/*
DESCRIPTION
This header file holds definitions for the POSIX trace system which are required
to be shared between user-level and kernel.
*/

#ifdef __cplusplus
extern "C" {
#endif


/* defines */
    
#define TRACE_ATTR_MAGIC        0x61747472

#define TRACE_ATTR_VALID(attr)  (attr->_Trace_attr_magic == TRACE_ATTR_MAGIC)

/* each event in the stream has an associated size */
    
typedef unsigned int    TRACE_EVENT_SIZE_TYPE;

/*
 * The POSIX trace functions are multiplexed into a smaller set of system
 * calls. The command values are used to specify the required function 
 */
    
typedef enum
    {
        cmdPosixTraceCreate = 1,
        cmdPosixTraceCreateWithLog,
        cmdPosixTraceStart,
        cmdPosixTraceStop,
        cmdPosixTraceFlush,
        cmdPosixTraceClear,
        cmdPosixTraceShutdown,
        cmdPosixTraceGetAttr,
        cmdPosixTraceGetStatus,
        cmdPosixTraceGetFilter,
        cmdPosixTraceSetFilter,
        cmdPosixTraceEvent,
        cmdPosixTraceEventIdOpen,
        cmdPosixTraceEventIdGetName,
        cmdPosixTraceEventIdEqual,
        cmdPosixTraceTridEventIdOpen,
        cmdPosixTraceEventTypeListGetNextId,
        cmdPosixTraceEventTypeListRewind,
        cmdPosixTraceClose,        
        cmdPosixTraceOpen,
        cmdPosixTraceRewind,
        cmdPosixTraceGetNextEvent,
        cmdPosixTraceTimedGetNextEvent,
        cmdPosixTraceTryGetNextEvent
    } POSIX_TRACE_CMD;


#ifdef __cplusplus
}
#endif


#endif /* __INCpxTraceLibCommonPh */
