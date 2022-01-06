/* sdSysCall.h - Shared Data system call definitions */

/* 
 * Copyright (c) 2004, 2010 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01f,12nov10,zl   added SD_ID_ERROR definition
01e,29jul10,pad  Moved extern C statement after include statements.
01d,11feb10,jpb  Updated for LP64 adaptation.
01c,25oct04,gls  made pVirtAddress for sdOpen/Create a void **
01b,11oct04,gls  added mode parameter to _sdOpen (SPR #101348)
01a,02oct04,gls  written
*/

#ifndef __INCsdSysCallh
#define __INCsdSysCallh

#include <vxWorks.h>
#include <vmLibCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/* return value for unsuccessful _sdCreate() and _sdOpen() */

#define SD_ID_ERROR	((SD_ID) (-1))

/* system call function prototypes */

extern SD_ID	_sdCreate (char * name, int options, size_t size, 
			   off_t physAddress, MMU_ATTR attr, 
			   void ** pVirtAddress);

extern SD_ID	_sdOpen (char * name, int options, int mode, size_t size, 
			 off_t physAddress, MMU_ATTR attr, 
			 void ** pVirtAddress);

#ifdef __cplusplus
}
#endif

#endif /* __INCsdSysCallh */
