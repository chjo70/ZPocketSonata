/* private/cplusLoadP.h - VxWorks loader shared C++ support */

/* 
 * Copyright (c) 2005 Wind River Systems, Inc. 
 * 
 * The right to copy, distribute, modify, or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
15jan13,v_r  Moved C++ xtors call to a dedicated routine (CQID WIND00400546).
05sep05,v_r  Written. Moved loader-specific includes from cplusLibP.h
*/

#ifndef __INCcplusLoadPh
#define __INCcplusLoadPh

#ifdef HOST
#include <host.h>
#else
#include <vxWorks.h>
#endif

#include <moduleLib.h>
#include <symLib.h>

/* Type declarations */

typedef enum 
    {
    XTOR_CALL	        = 0,
    NO_XTOR_CALL	= 1,
    NO_OVERRIDE         = 2 
    } CPLUS_XTOR_OVERRIDE;

/* Function declarations, C linkage */

#ifdef __cplusplus
extern "C" {
#endif

extern STATUS cplusLoadFixup (MODULE_ID module, SYMTAB_ID symTab, 
			      CPLUS_XTOR_OVERRIDE callCtors);

extern STATUS cplusUnloadFixup (MODULE_ID module, 
				CPLUS_XTOR_OVERRIDE callDtors);

extern void cplusLoadCtorsCall (MODULE_ID module,
                                CPLUS_XTOR_OVERRIDE callCtors);

#ifdef __cplusplus
}
#endif

#endif /* __INCcplusLoadPh */
