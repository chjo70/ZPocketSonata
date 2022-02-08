/* pgPoolPhysLibP.h - physical page pool object library header file */

/* 
 * Copyright (c) 2003-2006, 2009-2010, 2015 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
25jan15,pcs  CERT: Removed API's not used in CERT and added macros to 
             consolidate the CERT code.
29apr10,pad  Moved extern C statement after include statements.
18sep09,zl   use fully qualified function pointer for pgPoolPhysRangeEach().
17jun09,zl   updated for LP64 build
07jul06,zl   updated the pgPoolPhysAvailAlloc() arguments.
21jul05,zl   updated pgPoolLib API
13sep04,zl   converted to private header file
30nov03,yp   adding error code for address out of range
08jul03,yp   written.
*/

#ifndef __INCpgPoolPhysLibPh
#define __INCpgPoolPhysLibPh

/* includes */

#include <vxWorks.h>
#include <vsbConfig.h>
#include <private/pgPoolLibP.h>

#ifdef __cplusplus
extern "C" {
#endif


#ifndef	_ASMLANGUAGE

/* defines */

#ifdef _WRS_CONFIG_CERT
#define PAGE_POOL_PHYS_FREE_IGNORE_RETURN(pgPoolId, startAddr, numPages)
#else
#define PAGE_POOL_PHYS_FREE_IGNORE_RETURN(pgPoolId, startAddr, numPages) \
        ((void) pgPoolPhysFree (pgPoolId, startAddr, numPages)) 
#endif

/* function declarations */

extern STATUS	 pgPoolPhysLibInit (void);
extern STATUS	 pgPoolPhysAddToPool (PAGE_POOL_ID poolId, PHYS_ADDR addr, 
				      size_t numPages, UINT state);
#ifndef _WRS_CONFIG_CERT
extern STATUS	 pgPoolPhysFree (PAGE_POOL_ID poolId, PHYS_ADDR startAddr,
				 size_t numPages);
extern STATUS	 pgPoolPhysRemoveFromPool (PAGE_POOL_ID poolId, PHYS_ADDR addr,
					   size_t numPages);
extern BOOL	 pgPoolPhysRangeIsFree (PAGE_POOL_ID poolId, 
                                        PHYS_ADDR startAddr, size_t numPages);
extern STATUS	 pgPoolPhysNextFreeGet (PAGE_POOL_ID poolId, PHYS_ADDR refAddr,
					PHYS_ADDR * pFreeAddr, 
					size_t * pNumPages);
#endif /* !_WRS_CONFIG_CERT */
extern PHYS_ADDR pgPoolPhysAlloc (PAGE_POOL_ID poolId, size_t numPages);
extern PHYS_ADDR pgPoolPhysAlignedAlloc (PAGE_POOL_ID poolId, size_t numPages,
					 size_t alignment);
extern PHYS_ADDR pgPoolPhysAllocAt (PAGE_POOL_ID poolId, PHYS_ADDR startAddr,
				    size_t numPages);
extern PHYS_ADDR pgPoolPhysAvailAlloc (PAGE_POOL_ID poolId, size_t numPagesReq,
				       size_t * pNumPagesGot);
extern BOOL	 pgPoolPhysRangeIsAllocated (PAGE_POOL_ID poolId,
					     PHYS_ADDR startAddr,
					     size_t numPages);
extern BOOL	 pgPoolPhysRangeVerify (PAGE_POOL_ID poolId,
					PHYS_ADDR pageAddr, size_t numPages);
extern STATUS	 pgPoolPhysRangeEach (PAGE_POOL_ID poolId, UINT state,
				      STATUS (*usrRtn) 
					(
					PHYS_ADDR physAddr, 
					size_t numPages, 
					UINT state, 
					void * pArg
					), 
				      void * pArg);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCpgPoolPhysLibPh */
