/* vmInvTblLibP.h - private header for vmInvTblLib.c */

/* 
 * Copyright (c) 2004, 2009-2010 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01d,26aug10,gls  adapted to LP64
01c,09aug10,cww  Updated length params for funcBind pointers
01b,04may09,zl   added _func_vmInvPageMap and _func_vmInvUnMap declarations.
01a,15apr04,gls	 written.
*/

#ifndef __INCvmInvTblLibPh
#define __INCvmInvTblLibPh

#include <vxWorks.h>

#ifndef _ASMLANGUAGE

#ifdef __cplusplus
extern "C" {
#endif

extern STATUS (*_func_vmInvPageMap)
		    (
		    PHYS_ADDR    physicalAddr,	/* physical address to map */
		    size_t       len,		/* length in bytes to map */
		    BOOL         noAlias	/* disallow aliasing */
		    );
extern STATUS (*_func_vmInvUnMap)
		    (
		    PHYS_ADDR	physicalAddr, 	/* physical address to unmap */
		    size_t	len             /* length to unmap */
		    );

IMPORT	STATUS	vmInvTblLibInit (void);
IMPORT	STATUS	vmInvPageMap	(PHYS_ADDR physicalAddr, size_t len,
				 BOOL noAlias);
IMPORT	STATUS	vmInvUnMap	(PHYS_ADDR physicalAddr, size_t len);

#ifdef __cplusplus
}
#endif

#endif

#endif /* __INCvmInvTblLibPh */
