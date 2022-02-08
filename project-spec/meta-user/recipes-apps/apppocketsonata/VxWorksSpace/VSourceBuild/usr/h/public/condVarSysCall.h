/* condVarSysCall.h - VxWorks condition variable system call definitions */

/* Copyright 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01a,23sep13,rfr   written
*/

#ifndef __INCcondVarSysCallh
#define __INCcondVarSysCallh

#include <vxWorks.h>

#ifdef __cplusplus
extern "C" {
#endif


/* CONDVAR_ID_ERROR can be returned by _condVarOpen() */
#define CONDVAR_ID_ERROR	((CONDVAR_ID) (-1))

/* system call function prototypes */


extern CONDVAR_ID     _condVarOpen (const char * name, int options, int mode, 
				 void * context);
extern STATUS 	     _condVarWait  (CONDVAR_ID cvId, SEM_ID_KERNEL mutex,
				    _Vx_ticks_t timeout);
extern STATUS 	     _condVarSignal (CONDVAR_ID cvId, int broadcast);

#ifdef __cplusplus
}
#endif

#endif /* __INCcondVarSysCallh */



