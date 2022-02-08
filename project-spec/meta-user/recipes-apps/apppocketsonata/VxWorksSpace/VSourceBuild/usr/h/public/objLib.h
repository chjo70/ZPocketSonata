/* objLib.h - user-level object library header file */

/*
 * Copyright (c) 2003-2004, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01f,29jul10,pad  Moved extern C statement after include statements.
01e,07jan10,jpb  Updated objInfo prototype.
01d,14apr04,dcc  added objUnlink() prototype. Moved OBJ_HANDLE definition 
		 to vxWind.h
01c,31oct03,dcc  moved objInfoGet and objDelete prototypes from objSysCall.h
01b,03sep03,aeg  moved system call definitions to objSysCall.h
01a,26aug03,cjj  written 
*/

#ifndef __INCobjLibh
#define __INCobjLibh

#include <vxWorks.h>
#include <objLibCommon.h>
#include <objSysCall.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

/* function declarations */

extern STATUS objInfoGet 	(OBJ_HANDLE handle, void *pInfo, 
				 size_t *pInfoSize, int level);
extern STATUS objDelete 	(OBJ_HANDLE handle, int options);
extern STATUS objUnlink		(const char * name, enum windObjClassType 
			         classType);

#endif /* #ifndef _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCobjLibh */
