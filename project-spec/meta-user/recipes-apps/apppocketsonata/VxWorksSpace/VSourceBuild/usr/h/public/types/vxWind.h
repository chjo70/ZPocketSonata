/* vxWind.h - user-level WIND object types header file */

/*
* Copyright (c) 2003-2006, 2010, 2012-2013 Wind River Systems, Inc.
*
* The right to copy, distribute, modify or otherwise make use
* of this software may be licensed only pursuant to the terms
* of an applicable Wind River license agreement.
*/

/*
modification history
--------------------
020,22sep13,rfr  Added CONDVAR_ID
02o,29jun12,jpb  Reinstated _Vx_REG_SET.
02n,21mar12,jpb  Added _Vx_REG_SET (ucontext_t needs POSIX namepsace isolation
                 conforming definition.  Part of defect WIND000307800).
02m,29jul10,pad  Moved extern C statement after include statements.
02l,28aug06,jpb  Removed duplicate definitions.
02k,10aug06,pad  Added correct path to vxWindCommon.h inclusion.
02j,20jan06,mil  Updated for POSIX namespace conformance (P2).
02i,20apr04,dcc  added OBJ_HANDLE definition.
02h,29mar04,dcc  added inclusion of vxWindCommon.h
02g,18dec03,gls  added SD_ID
02f,17nov03,md   add semaphore types SEM_ID and SEM_ID_KERNEL
02e,14nov03,job  added HANDLE types
02d,24oct03,aeg  added MSQ_Q_ID.
02c,19sep03,kk   remerge to pick up PART_ID.
02b,15sep03,kk   added RTP_ID
02b,16sep03,zl   added PART_ID.
02a,04sep03,aeg  removed inclusion of vxWindCommon.h
01a,29aug03,cjj  written based on kernel version 01n of vxWind.h
*/

/*
DESCRIPTION
This file typedefs the opaque types for WIND kernel objects.  They
are typedef-ed here so that other header files can declare functions
containing more than one of these types as parameters without having
to include each other - which could cause circular header file
inclusion problems.

The Wind object type and handle type enumerations are also defined here.
*/

#ifndef __INCvxWindh
#define __INCvxWindh

#include <types/vxWindCommon.h> /* windObjClassType and handleType enums defs */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

typedef int                     _Vx_OBJ_HANDLE;
typedef _Vx_OBJ_HANDLE          _Vx_TASK_ID;
typedef _Vx_OBJ_HANDLE          _Vx_MSG_Q_ID;
typedef struct _Vx_mem_part *   _Vx_PART_ID;
typedef struct _Vx_semaphore *  _Vx_SEM_ID;
typedef _Vx_OBJ_HANDLE          _Vx_SEM_ID_KERNEL;
typedef _Vx_OBJ_HANDLE          _Vx_RTP_ID;
typedef _Vx_OBJ_HANDLE          _Vx_SD_ID;
typedef _Vx_OBJ_HANDLE		_Vx_CONDVAR_ID;
typedef struct _Vx_register_set    _Vx_REG_SET;

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
typedef _Vx_OBJ_HANDLE  	OBJ_HANDLE;
typedef OBJ_HANDLE 		TASK_ID;
typedef OBJ_HANDLE		MSG_Q_ID;
typedef _Vx_PART_ID 		PART_ID;
typedef _Vx_SEM_ID		SEM_ID;
typedef OBJ_HANDLE		SEM_ID_KERNEL;
typedef OBJ_HANDLE		RTP_ID;
typedef OBJ_HANDLE		SD_ID;
typedef OBJ_HANDLE		CONDVAR_ID;
typedef _Vx_REG_SET		REG_SET;
#endif  /* _POSIX_xxx_SOURCE */

#endif /* #ifndef _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxWindh */
