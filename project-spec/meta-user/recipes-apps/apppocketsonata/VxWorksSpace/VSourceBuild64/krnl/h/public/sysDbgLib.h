/* sysDbgLib.h - system-debug flag library header file */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01a,24sep10,rlp  created
*/

#ifndef __INCsysDbgLib_h
#define __INCsysDbgLib_h

#include <vxWorks.h>
#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* function */

extern BOOL	sysDebugModeGet (void);
extern void	sysDebugModeSet (BOOL mode);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCsysDbgLib_h */
