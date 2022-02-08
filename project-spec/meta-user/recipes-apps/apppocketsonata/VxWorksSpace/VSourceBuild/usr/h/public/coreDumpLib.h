/* coreDumpLib.h - user-level core dump library header file */

/* 
 * Copyright (c) 2008, 2010 Wind River Systems, Inc. 
 * 
 * The right to copy, distribute, modify, or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01x,29jul10,pad  Moved extern C statement after include statements.
01w,18jun08,jmp  Written.
*/

#ifndef __INCcoreDumpLibh
#define __INCcoreDumpLibh

/* includes */

#include "coreDumpLibCommon.h"

#ifdef __cplusplus
extern "C" {
#endif

/* externals */

extern STATUS	coreDumpMemFilterAdd	(void * addr, size_t size);
extern STATUS	coreDumpMemFilterDelete	(void * addr, size_t size);

#ifdef __cplusplus
}
#endif

#endif /* __INCcoreDumpLibh */
