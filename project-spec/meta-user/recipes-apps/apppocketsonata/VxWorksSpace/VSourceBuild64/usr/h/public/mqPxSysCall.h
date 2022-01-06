/* mqPxSysCall.h - POSIX message queue system calls */

/*
 * Copyright (c) 2003-2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01g,28apr10,pad  Moved extern C statement after include statements.
01f,11mar06,jln  added mqHandlesCompareArgs structure
01e,26jan06,kk   distinguish kernel and user paths to pxObjSysCall.h
01d,26jan06,yvp  Corrected path to pxObjSysCall.h.
01c,25jan06,yvp  Posix conformance: made timeout parameter const for 
                 pxMqReceive and pxMqSend.
		 Updated copyright + #include now with angle brackets
01b,24mar04,mcm  Including time.h instead of sys/time.h in user space.
01a,17nov03,m_s  written
*/

#ifndef __INCmqPxSysCallh
#define __INCmqPxSysCallh

#include <objLib.h>
#ifdef _WRS_KERNEL
#include <private/pxObjSysCall.h>
#else
#include <pxObjSysCall.h>
#endif
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

/* structures for pxCtl system call */

struct mqNotifyArgs       /* PX_MQ_NOTIFY */
    {
    const struct sigevent * pNotification;
    };

struct mqAttrGetArgs      /* PX_MQ_ATTR_GET */
    {
    struct mq_attr * pOldMqStat;
    };

struct mqHandlesCompareArgs
    {
    OBJ_HANDLE newHandle;
    BOOL *     pMatched;
    };

/* system call function prototypes */

extern ssize_t pxMqReceive (OBJ_HANDLE handle, char * pMsg, size_t msgLen,
                            unsigned int * pMsgPrio, PX_WAIT_OPTION waitOption,
                            const struct timespec * time_out);
extern int     pxMqSend    (OBJ_HANDLE handle, const char * pMsg, size_t msgLen,
                            unsigned int msgPrio, PX_WAIT_OPTION waitOption,
                            const struct timespec * time_out);

#ifdef __cplusplus
}
#endif

#endif /* __INCmqPxSysCallh */
