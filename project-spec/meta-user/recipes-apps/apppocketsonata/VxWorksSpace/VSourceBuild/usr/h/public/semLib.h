/* semLib.h - user-level semaphore library header file */

/*
 * Copyright (c) 2003-2005, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
*/

/*
modification history
--------------------
01e,29jul10,pad  Moved extern C statement after include statements.
01d,20apr05,kk   moved SEM_XXX types from semLibCommon.h, only used in RTPs
01c,28nov03,dcc  added semClose() prototype.
01b,27nov03,aeg  added inclusion of semSysCall.h
01a,26aug03,cjj  written 
*/

#ifndef __INCsemLibh
#define __INCsemLibh

#include "vxWorks.h"
#include "semLibCommon.h"
#include "semSysCall.h"

#ifdef __cplusplus
extern "C" {
#endif

/* the following options are valid only in the RTP environment */

#define SEM_KERNEL              0x100   /* semaphore created in kernel space */
#define SEM_USER                0x200   /* semaphore created in user space   */
#define SEM_KUTYPE_DEFAULT      0x000   /* semaphore created in default space*/
#define SEM_KUTYPE_MASK         0x300   /* mask for semaphore creation space */

/* function declarations */

extern STATUS semClose (SEM_ID semId);

#ifdef __cplusplus
}
#endif

#endif /* __INCsemLibh */
