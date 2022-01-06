/* vxdbgLibInit.h - VxDBG library initialization header */

/*
 * Copyright (c) 2013,2014 Wind River Systems, Inc.  
 *
 * The right to copy, distribute, modify or otherwise make use  of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
10feb14,elp  Modified vxdbgHooksInit() prototype.
23may13,rlp  Added vxdbgExcLibInit prototype.
20may13,rlp  Created.
*/

#ifndef __INCvxdbgLibInith
#define __INCvxdbgLibInith

#include <vxdbgLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function declarations */

extern void		vxdbgLibInit (void);
extern void		vxdbgRunCtrlLibInit (void);
extern void		vxdbgModuleLibInit (void);
extern void		vxdbgExcLibInit (void);
extern VXDBG_STATUS	vxdbgHooksInit (void);
extern VXDBG_STATUS	vxdbgRtpLibInit (void);
extern VXDBG_STATUS	vxdbgEventLibInit (int priority, int options,
					   size_t stackSize);
extern VXDBG_STATUS	vxdbgCpuLibInit (void);


extern void		wdbDbgArchInit (void);
#ifdef __cplusplus
}
#endif

#endif /* __INCvxdbgLibInith */

