/* sdLib.h - shared data library header file */

/*
 * Copyright (c) 2003-2004, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01l,27may10,pad  Added 'extern C' statement.
01k,04mar10,jpb  Updated for LP64 adaptation.
01j,23feb10,zl   replaced off_t64 with off64_t
01i,25oct04,gls  made pVirtAddress a void **
01h,11oct04,gls  added mode parameter to sdOpen (SPR #101348)
01g,02oct04,gls  moved sdLibInit() and sdShowInit() declarations to sdLibP.h
01f,29sep04,gls  made physicalAddr parameter type off_t
01e,20jul04,gls  added hookTblSize parameter to sdLibInit()
01d,01apr04,gls  added sdLibInit() and sdShowInit()
01c,17feb04,gls  fixed copyright
01b,11dec03,gls  added functionality
01a,04nov03,kk   written from AE 1.1 version
*/

#ifndef __INCsdLibh
#define __INCsdLibh

#include <vxWorks.h>
#include <vwModNum.h>
#include <sdLibCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/* functional API to the library */

SD_ID		sdCreate	(char *		name,
				 int		options,
				 size_t		size,
				 off64_t	physAddress,
				 MMU_ATTR	attr,
				 void ** 	pVirtAddress);
				 
SD_ID		sdOpen  	(char *		name,
				 int		options,
				 int		mode,
				 size_t		size,
				 off64_t	physAddress,
				 MMU_ATTR	attr,
				 void ** 	pVirtAddress);

#ifdef __cplusplus
}
#endif

#endif /* __INCsdLibh */
