/* aimMmuLibP.h - MMU library portion of the Architecture Independent Manager */

/*
 * Copyright (c) 2007, 2010 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01e,20sep10,jpb  Reverted changes and include aimMmuLib.h
01d,18sep10,jpb  Removed include of aimMmuLib.h
01c,31aug10,jpb  Added function pointer _func_aimMmuLockRegionsImport.
01b,29apr10,pad  Moved extern C statement after include statements.
01a,02may07,zl   created
*/

#ifndef __INCaimMmuLibPh
#define __INCaimMmuLibPh

#include <vxWorks.h>
#include <aimMmuLib.h>
#include <private/vmLibP.h>		/* for VM_MMU_TRANS_TBL_GET() */

#ifdef __cplusplus
extern "C" {
#endif

#define AIM_MMU_CTX_ID_GET(vmCtx)	(VM_MMU_TRANS_TBL_GET(vmCtx)->context)

/* function pointers */

extern STATUS (*_func_aimMmuLockRegionsImport)(void);

#ifdef __cplusplus
}
#endif

#endif /* __INCaimMmuLibPh */

