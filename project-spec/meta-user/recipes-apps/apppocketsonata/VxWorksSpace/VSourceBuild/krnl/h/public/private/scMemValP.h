/* scMemValP.h - private header file for system call validation routines */

/* 
 * Copyright (c) 1993-2005, 2009-2010 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01j,30sep10,jpb  Removed _func_scMemValidate.
01i,18sep10,jpb  _func_scMemValidate was not extern.
01h,01sep10,jpb  Added function pointer _func_scMemValidate
01g,17may10,zl   added SC_PROT_ATOMIC_RMW to SC_PROT_MSK.
01f,29apr10,pad  Moved extern C statement after include statements.
01e,16dec09,pcs  Updated for LP64 support.
01d,15dec05,zl   added scMemPrivValidate() prototype.
01c,05nov04,zl   moved function prototype to public header.
01b,19apr04,tam  updated prototype
01a,23oct03,tam  written.
*/

#ifndef __INCscMemValPh
#define __INCscMemValPh

#include <scMemVal.h>

#ifdef __cplusplus
extern "C" {
#endif


/* protection mask */

#define SC_PROT_MSK	(SC_PROT_READ | SC_PROT_WRITE | SC_PROT_ATOMIC_RMW)

#ifndef _ASMLANGUAGE

STATUS scMemPrivValidate (const void * addr, size_t size, SC_PROT_ATTR access,
			  RTP_ID rtpId);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCscMemValPh */
