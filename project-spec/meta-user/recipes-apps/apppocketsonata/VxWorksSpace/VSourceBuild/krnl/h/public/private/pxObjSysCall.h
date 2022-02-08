/* pxObjSysCall.h - POSIX system calls */

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
01e,04may10,jpb  Update for LP64 adaptation.
01d,28apr10,pad  Moved extern C statement after include statements.
01c,11mar06,jln  added PX_MQ_HANDLES_COMPARE
01b,14feb06,yvp  Added PX_SEM_HANDLES_COMPARE.
01a,17nov03,m_s  written
*/

#ifndef __INCpxObjSysCallh
#define __INCpxObjSysCallh

/* includes */

#include <types/vxWind.h>

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

/*
 * Object types for pxOpen and pxUnlink system call.
 * Start the enum from 1 since 0 is prone to error.
 */
typedef enum
    {
    PX_MQ = 1,
    PX_SEM

    } PX_OBJ_TYPE;

/*
 * Waiting options.
 * Start the enum from 1 since 0 is prone to error.
 */
typedef enum
    {
    PX_NO_WAIT = 1,
    PX_WAIT_FOREVER,
    PX_TIMEDWAIT

    } PX_WAIT_OPTION;

/*
 * Command codes for pxCtl system call.
 * Start the enum from 1 since 0 is prone to error.
 */
typedef enum
    {
    PX_MQ_NOTIFY = 1,
    PX_MQ_ATTR_GET,
    PX_SEM_GETVALUE,
    PX_SEM_HANDLES_COMPARE_AND_DELETE,
    PX_MQ_HANDLES_COMPARE

    } PX_CTL_CMD_CODE;

/* system call function prototypes */

extern OBJ_HANDLE pxOpen     (PX_OBJ_TYPE objType, const char * name,
                              int objOpenMode, void * attr);
extern int        pxClose    (OBJ_HANDLE handle);
extern int        pxUnlink   (PX_OBJ_TYPE objType, const char * name);
extern STATUS     pxCtl      (OBJ_HANDLE handle, PX_CTL_CMD_CODE cmdCode,
                              void * pArgs, size_t * pArgSize);

#ifdef __cplusplus
}
#endif

#endif /* __INCpxObjSysCallh */
