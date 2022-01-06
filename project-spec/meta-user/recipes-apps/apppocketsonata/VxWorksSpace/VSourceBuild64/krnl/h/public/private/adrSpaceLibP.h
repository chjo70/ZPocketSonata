/* adrSpaceLibP.h - Address Space Library header */

/* 
 * Copyright (c) 2004-2005,2007-2010,2013,2015,2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
07aug17,pcs  Changes corresponding to making the kernel virtual memory pool
             region size configurable using configuration parameter 
             KERNEL_VIRT_POOL_REGION_SIZE.(V7COR-5102)
24mar15,j_l  Initial modifications for IA 32 bit GEN2 support
03may15,pcs  Updated with changes corresponding to moving out the Direct Map 
             Region routines to adrSpaceDirectMap.c and moving mmuDirectPageMap
             to struct MMU_LIB_FUNCS.
22jan15,pcs  CERT: Added macros ADR_SPACE_PAGE_FREE_IGNORE_RETURN and 
             ADR_SPACE_PAGE_FREE to consolidate the CERT code changes and 
             removed adrSpacePageUnmap() and adrSpacePageFree().
29apr15,rr   Added greater than 32-bit physical address support to
             adrSpaceOptimizedSizeGet() in ILP32.(V7COR-883)
02aug13,pcs  updated to use config option _WRS_CONFIG_COMPAT69_ADR_SPACE
08sep10,pcs  Add an entry to represent the global virtual memory region
             size to struct adrSpaceInitParams.
02jun10,elp  added SIMNT/SIMLINUX 64 bits support.
29apr10,pad  Moved extern C statement after include statements.
14apr10,jpb  Added function pointer declarations.
09mar10,pad  Reorganized ADR_SPACE_INIT_PARAMS structure so that only the
             localMemLocalAdrs field is defined for VxWorks 64-bit.
27oct09,pcs  Rearranged struct adrSpaceInitParams entries while adding
             support for RTP's in LP64.
12oct09,zl   added adrSpaceOptimizedSizeGet()and RAM pool allocation option
17sep09,zl   added directMapRAMSize.
24aug09,zl   updated map and alloc options; added 64-bit arch header
22jun09,zl   updated for LP64 build
18apr08,pcs  Add prototypes for adrSpaceOverlapPageAlloc and
             adrSpaceOverlapNodesRemove.
24apr07,pcs  Add prototype for adrSpacePageVirtPhysFree.
09sep05,zl   removed ADR_SPACE_RGN_CTL structure.
27jun05,zl   added new alloc, free, map, unmap APIs and options.
22sep04,zl   post-inspection fixes.
31aug04,zl   created.
*/

#ifndef __INCadrSpaceLibPh
#define __INCadrSpaceLibPh

/* includes */

#include <vxWorks.h>
#include <vsbConfig.h>
#include <vmLib.h>
#include <private/vmLibP.h>		/* VIRT_SEG_INFO */
#include <private/pgPoolLibP.h>

#ifndef _WRS_CONFIG_COMPAT69_ADR_SPACE
#include ARCH_HEADER(private/adrSpaceArchLibP.h)
#endif /* _WRS_CONFIG_COMPAT69_ADR_SPACE */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WRS_CONFIG_CERT
/* For CERT, these macros are no-ops. */

#define ADR_SPACE_PAGE_FREE_IGNORE_RETURN(vmContext, virtAddr, numPages, \
                                          options)
#else
#define ADR_SPACE_PAGE_FREE_IGNORE_RETURN(vmContext, virtAddr, numPages, \
                                          options) \
                                          ((void) adrSpacePageFree (vmContext, \
                                                                    virtAddr, \
                                                                    numPages, \
                                                                    options))
#endif

/* address space types */

#define ADR_SPACE_TYPE_KERNEL		0x00000001
#define ADR_SPACE_TYPE_RTP		0x00000000
#define ADR_SPACE_TYPE_MASK		0x00000001

/* 
 * the alloc and map options are defined so that they don't 
 * overlap with the MMU attributes and VM mapping options, since they
 * can be OR-ed together. MMU attributes use 0x000fffff. VM
 * map options use 0x00f00000.
 */

#define ADR_SPACE_OPT_CONTIG		0x80000000
#define ADR_SPACE_OPT_NONCONTIG		0x00000000
#define ADR_SPACE_OPT_CONTIG_MASK	0x80000000

#define ADR_SPACE_OPT_MAPPED		0x40000000
#define ADR_SPACE_OPT_UNMAPPED		0x00000000
#define ADR_SPACE_OPT_MAPPED_MASK	0x40000000

#define ADR_SPACE_OPT_OPTIMIZED		0x20000000
#define ADR_SPACE_OPT_UNOPTIMIZED	0x00000000
#define ADR_SPACE_OPT_OPTIMIZE_MASK	0x20000000

#define ADR_SPACE_OPT_NOPHYSALLOC	0x10000000
#define ADR_SPACE_OPT_PHYSALLOC		0x00000000
#define ADR_SPACE_OPT_PHYSALLOC_MASK	0x10000000

#define ADR_SPACE_OPT_RGN_KERNEL	0x08000000
#define ADR_SPACE_OPT_RGN_DIRECT	0x04000000
#define ADR_SPACE_OPT_RGN_SHM		0x02000000
#define ADR_SPACE_OPT_RGN_MASK		0x0e000000

/*
 * the address space map attributes are a combination of the MMU attributes,
 * the VM mapping options, the contiguous and optimized mapping options.
 * 
 * The address space allocation attributes are a combination of all of 
 * the above, plus the region and the mapped options.
 */

#define ADR_SPACE_OPT_MAP_MASK		(ADR_SPACE_OPT_CONTIG_MASK   | \
					 ADR_SPACE_OPT_OPTIMIZE_MASK | \
					 ADR_SPACE_OPT_PHYSALLOC_MASK| \
					 VM_MAP_OPTIONS_MASK	     | \
					 VM_ATTR_ALL)

#define ADR_SPACE_OPT_ALLOC_MASK	(ADR_SPACE_OPT_MAP_MASK      | \
					 ADR_SPACE_OPT_MAPPED_MASK   | \
					 ADR_SPACE_OPT_RGN_MASK)

/* unmap and free attributes */

#define ADR_SPACE_OPT_PHYS_NOFREE	0x00000001
#define ADR_SPACE_OPT_PHYS_FREE		0x00000000
#define ADR_SPACE_OPT_PHYS_FREE_MASK	0x00000001

/* address space model configuration values */

#define ADR_SPACE_MODEL_FLAT            1
#define ADR_SPACE_MODEL_OVERLAPPED      2

#ifndef _ASMLANGUAGE

/* typedefs */

typedef struct adrSpaceInitParams
    {
#ifdef _WRS_CONFIG_USE_MEMDESC
    VIRT_ADDR   	localMemLocalAdrs;	/* where memory begins */
    size_t        	kernelVirtPoolRgnSize;	/* kernel virt pool rgn size */
#else /* _WRS_CONFIG_USE_MEMDESC */
    PHYS_MEM_DESC *	pPhysMemDesc;		/* physMemDesc pointer */
    int 		physMemDescNumEnt;	/* number of elements */
    VIRT_ADDR   	localMemLocalAdrs;	/* where memory begins */
    VIRT_ADDR   	kernelMemTop;		/* top of kernel mem (heap) */
    VIRT_ADDR   	rtpRgnBase;		/* RTP overlapped rgn base */
    size_t        	rtpRgnSize;		/* RTP overlapped rgn size */
    size_t        	globalVirtMemRgnSize;	/* global virt mem rgn size */
    BOOL		rtpRgnIsOverlapped;     /* is RTP space overlapped? */
#endif /* _WRS_CONFIG_USE_MEMDESC */
    } ADR_SPACE_INIT_PARAMS;

/* globals */

#ifdef _WRS_CONFIG_COMPAT69_ADR_SPACE
extern UINT		adrSpaceModel;		/* flat or overlapped  */
#endif
extern PAGE_POOL_OBJ    globalRAMPgPool;
extern PAGE_POOL_ID	globalRAMPgPoolId;
extern PAGE_POOL_OBJ    kernelVirtPgPool;
extern PAGE_POOL_ID	kernelVirtPgPoolId;
#ifndef _WRS_CONFIG_COMPAT69_ADR_SPACE
extern PAGE_POOL_ID	shmRgnPgPoolId;
#else
extern PAGE_POOL_ID	userRgnPoolId;
extern PAGE_POOL_ID	kernelRgnPoolId;
#endif
extern size_t		rtpCodeSize;
extern VIRT_ADDR	rtpCodeStart;
extern PHYS_ADDR        lowestRAMAddress;
extern PHYS_ADDR        highestRAMAddress;

extern ADR_SPACE_INIT_PARAMS * pAsInitParams;
extern int              asMemDescNumEnt;
extern PHYS_MEM_DESC *  pAsMemDesc;

/* base level function prototypes */

extern STATUS 	adrSpaceLibInit (ADR_SPACE_INIT_PARAMS * pInitParams);
extern STATUS 	adrSpaceShowInit (void);

extern VIRT_ADDR adrSpacePageAlloc (VM_CONTEXT_ID vmContext, VIRT_ADDR virtAddr,
				    PHYS_ADDR physAddr, size_t numPages,
				    UINT options);
#ifndef _WRS_CONFIG_CERT
extern STATUS	adrSpacePageFree (VM_CONTEXT_ID vmContext, VIRT_ADDR virtAddr,
				  size_t numPages, UINT options);
extern STATUS	adrSpacePageUnmap (VM_CONTEXT_ID vmContext, VIRT_ADDR virtAdr, 
				   size_t numPages, UINT options);
#endif /* !_WRS_CONFIG_CERT */
extern STATUS	adrSpacePageMap (VM_CONTEXT_ID vmContext, VIRT_ADDR virtAdr, 
				 PHYS_ADDR physAdr, size_t numPages, 
				 UINT options);
extern STATUS	adrSpacePageVirtPhysFree (VM_CONTEXT_ID vmContext, 
                                  VIRT_ADDR virtAddr, PHYS_ADDR physAddr,
                                  size_t numPages, UINT options);
extern STATUS	adrSpaceOptimizedSizeGet (PHYS_ADDR addr, size_t numPages,
					  size_t * pAlignSize, 
					  size_t * pNumPages);

#ifdef _WRS_CONFIG_LP64
extern STATUS adrSpaceDirectMapInit (void);
#endif

/* function pointer prototypes */

extern VIRT_SEG_INFO *       (*_func_virtSegInfoGet)(UINT * pNumElems);
extern VIRT_EXTRA_MAP_INFO * (*_func_virtExtraMapInfoGet)(int descNum);
extern VIRT_ADDR (*_func_adrSpacePageAllocDirect)(size_t numPages, UINT attr);
extern STATUS    (*_func_adrSpacePageFreeDirect)(VM_CONTEXT_ID vmContext,
                                                 VIRT_ADDR virtAdr, 
                                                 size_t numPages, 
                                                 UINT options);
extern VIRT_ADDR (*_func_adrSpaceDirectBaseGet)(void);
extern size_t (*_func_adrSpaceDirectSizeGet)(void);
#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCadrSpaceLibPh */
