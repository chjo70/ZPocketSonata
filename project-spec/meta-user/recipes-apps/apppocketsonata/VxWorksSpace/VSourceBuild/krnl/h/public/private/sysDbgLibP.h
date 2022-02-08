/* sysDbgLibP.h - system-debug flag library header file */

/*
 * Copyright (c) 2010-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01b,07apr11,rlp  Added sysDebugModeSetHookAdd and sysDebugModeSetHookDelete
                 prototypes.
01a,24sep10,rlp  created
*/

#ifndef __INCsysDbgLibP_h
#define __INCsysDbgLibP_h

#include <vxWorks.h>
#include <vsbConfig.h>
#include <sysDbgLib.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* externs */

/* function */

extern STATUS   sysDebugModeInit (void);
extern STATUS	sysDebugModeSetHookAdd (void (*hook)(BOOL mode));
extern STATUS	sysDebugModeSetHookDelete (void (*hook)(BOOL mode));

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCsysDbgLibP_h */
