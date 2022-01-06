/* adrSpaceLib.h - Address Space Library header */

/* 
 * Copyright (c) 1998-2005, 2008-2010, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01z,11sep13,pcs  Added S_adrSpaceLib_INVALID_CONTEXT
01z,19jun12,zl   added physContigPages to ADR_SPACE_INFO (WIND00354507).
01y,29apr10,pad  Moved extern C statement after include statements.
01x,29jun09,zl   updated for LP64 build.
01w,26sep08,pcs  Added S_adrSpaceLib_MMU_NOT_ENABLED
01v,23jul08,pad  Added prototype of adrSpaceIsOverlapped().
01u,08sep05,zl   added adrSpaceVirtReserve() and adrSpaceRAMReserve()
                 prototypes
01t,07jul05,zl   added new errno-s.
01s,22sep04,zl   more comments
01r,31aug04,zl   moved private APIs to private header file
01q,07jun04,tam  added definition for option ADR_SPACE_OPT_RTP
01p,15apr04,yp   Adding sysPhysMemDesc and numElems to ADR_SPACE_INFO for
                 testing
		 Added prototype for adrSpaceRAMAddToPool()
01o,05apr04,yp   reworking adrSpaceLibInit call
01n,18mar04,yp   removing unused prototype adrSpaceReserve
		 adding the kernel virtual page pool ID to ADR_SPACE_INFO
		 adding adrSpaceLibInit params to ADR_SPACE_INFO
01m,25nov03,yp   using reserved field in page pool options for kernel space
01m,30nov03,yp   adding error ADDRESS_OUT_OF_RANGE and removing PD related
                 errors; fixing prototype for adrSpaceLibInit;
01l,11nov03,yp   adjusting ADR_SPACE_INFO structure for base 6
01k,16oct03,yp   proted to base 6
01j,31aug00,pfl  added S_adrSpaceLib_ALLOC_UNIT_IS_INVALID
01i,17aug00,tam  added ADR_SPACE_OPT_KERNEL_PD
01h,13jun99,map  added master page pools to ADR_SPACE_INFO struct.
01g,27mar00,map  support for shared library and IO address space.
01f,05nov99,map  added support for virtual regions.
01e,30apr99,map  added support for appl PD region. removed sub-region support.
01d,28apr99,wkn  added #include pgPoolLibP.h
01c,06apr99,map  added adrSpace options, fixed prototypes.
01b,08feb99,tam  added adrSpaceBaseGet().
01a,16sep98,map  written.
*/

#ifndef __INCadrSpaceLibh
#define __INCadrSpaceLibh

/* includes */

#include <vxWorks.h>

#ifdef __cplusplus
extern "C" {
#endif

/* errnos */

#define	S_adrSpaceLib_LIB_NOT_INITIALIZED	(M_adrSpaceLib | 1)
#define	S_adrSpaceLib_CANNOT_REINITIALIZE	(M_adrSpaceLib | 2)
#define	S_adrSpaceLib_PARAMETER_NOT_ALIGNED	(M_adrSpaceLib | 3)
#define	S_adrSpaceLib_REGION_NOT_AVAILABLE	(M_adrSpaceLib | 4)
#define	S_adrSpaceLib_VIRT_ADRS_NOT_ALIGNED	(M_adrSpaceLib | 5)
#define	S_adrSpaceLib_SIZE_IS_INVALID        	(M_adrSpaceLib | 6)
#define	S_adrSpaceLib_INVALID_PARAMETER		(M_adrSpaceLib | 7)
#define	S_adrSpaceLib_VIRTUAL_OVERLAP		(M_adrSpaceLib | 8) 
#define S_adrSpaceLib_PHYSICAL_OVERLAP		(M_adrSpaceLib | 9)
#define S_adrSpaceLib_ADDRESS_OUT_OF_RANGE	(M_adrSpaceLib |10)
#define S_adrSpaceLib_INSUFFICIENT_SPACE_IN_RGN	(M_adrSpaceLib |11)
#define S_adrSpaceLib_REGION_CONFLICT		(M_adrSpaceLib |12)
#define S_adrSpaceLib_MMU_LESS_NONIDENTITY	(M_adrSpaceLib |13)
#define S_adrSpaceLib_NO_PHYS_PAGES		(M_adrSpaceLib |14)
#define S_adrSpaceLib_NO_CONTIG_PHYS_PAGES	(M_adrSpaceLib |15)
#define S_adrSpaceLib_MMU_NOT_ENABLED    	(M_adrSpaceLib |16)
#define	S_adrSpaceLib_INVALID_REGION		(M_adrSpaceLib |17)
#define	S_adrSpaceLib_REGION_NOT_CONFIGURED	(M_adrSpaceLib |18)
#define	S_adrSpaceLib_INVALID_CONTEXT   	(M_adrSpaceLib |19)

#ifndef	_ASMLANGUAGE

/* typedefs */

typedef struct adr_space_info
    {
    size_t	physAllocUnit;		/* physical space allocation unit */
    size_t	physTotalPages;		/* total system RAM physical pages*/
    size_t	physFreePages;		/* unmapped system RAM physical pages */
    size_t	physMaxSize;		/* largest unmapped RAM block */
    size_t	physContigPages;	/* largest unmapped RAM block in pages */
    size_t	kernelAllocUnit;	/* kernel region allocation unit */
    size_t	kernelTotalPages;	/* kernel region total pages */
    size_t	kernelFreePages;	/* kernel region unmapped pages */
    size_t	kernelMaxSize;		/* largest unmapped blk in kernel rgn */
    size_t	userAllocUnit;		/* user region allocation unit */
    size_t	userTotalPages;		/* user region total pages */
    size_t	userFreePages;		/* user region unmapped pages */
    size_t	userMaxSize;		/* largest unmapped blk in user rgn */
    } ADR_SPACE_INFO;

/* function prototypes */

extern STATUS	 adrSpaceInfoGet (ADR_SPACE_INFO *pInfo);
extern STATUS 	 adrSpaceRAMAddToPool (PHYS_ADDR startAddr, size_t size);
extern PHYS_ADDR adrSpaceRAMReserve (PHYS_ADDR startAddr, size_t size);
extern VIRT_ADDR adrSpaceVirtReserve (VIRT_ADDR startAddr, size_t numPages);
extern BOOL	 adrSpaceIsOverlapped (void);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCadrSpaceLibh */
