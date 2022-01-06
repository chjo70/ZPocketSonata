/* semPxSysCall.h - POSIX semaphore system calls */

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
01f,14feb06,yvp  Added struct semHandlesCompareArgs.
01e,26jan06,kk   distinguish kernel and user paths to pxObjSysCall.h
01d,26jan06,yvp  Corrected path to pxObjSysCall.h.
01c,25jan06,yvp  Posix conformance: made pxSemWait timeout parameter const.
                 Updated copyright + #include now with angle-brackets.
01b,24mar04,mcm  Including time.h instead of sys/time.h in user-space
01a,17nov03,m_s  written
*/

#ifndef __INCsemPxSysCallh
#define __INCsemPxSysCallh

#include <objLib.h>
#include "pxObjSysCall.h"	/* must stay as a quoted include */
#include <dllLib.h>
#include <semaphore.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

/* structure for pxCtl system call */

struct semGetvalueArgs    /* PX_SEM_GETVALUE */
    {
    int * sval;
    };

struct semHandlesCompareArgs
    {
    OBJ_HANDLE newHandle;
    BOOL *     pMatched;
    };

/* system call function prototypes */

extern int pxSemWait   (OBJ_HANDLE handle, PX_WAIT_OPTION waitOption,
                        const struct timespec * timeout);
extern int pxSemPost   (OBJ_HANDLE handle);

#ifdef __cplusplus
}
#endif

#endif /* __INCsemPxSysCallh */
