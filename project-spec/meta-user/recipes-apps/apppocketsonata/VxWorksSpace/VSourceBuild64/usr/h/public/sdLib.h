/* sdLib.h - user-level shared data library header file */

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
01h,29jul10,pad  Moved extern C statement after include statements.
01g,11feb10,jpb  Updated for LP64 adaptation.
01f,25oct04,gls  made pVirtAddress a void **
01e,11oct04,gls  added mode parameter to sdOpen (SPR #101348)
01d,02oct04,gls  added include of sdSysCall.h
01c,29sep04,gls  made physicalAddr parameter type off_t
01b,04mar04,gls  moved include of vmLibCommon.h before sdLibCommon.h
01a,28jan04,gls  created based on sdLib.h
*/

#ifndef __INCsdLibh
#define __INCsdLibh

#include <vxWorks.h>
#include <vmLibCommon.h>
#include <sdLibCommon.h>
#include <sdSysCall.h>

#ifdef __cplusplus
extern "C" {
#endif

/* functional API to the library */

SD_ID		sdCreate	(char *		name,
				 int		options,
				 size_t		size,
				 off_t  	physAddress,
				 MMU_ATTR	attr,
				 void ** 	pVirtAddress);
				 
SD_ID		sdOpen		(char *		name,
				 int		options,
				 int		mode,
				 size_t		size,
				 off_t  	physAddress,
				 MMU_ATTR	attr,
				 void ** 	pVirtAddress);

#ifdef __cplusplus
}
#endif	/* __cplusplus */

#endif /* __INCsdLibh */
