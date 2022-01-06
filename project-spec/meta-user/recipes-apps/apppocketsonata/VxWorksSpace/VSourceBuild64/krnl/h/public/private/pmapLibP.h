/* pmapLibP.h - private header for physical address mapping library */

/* 
 * Copyright (c) 2014 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
05apr14,pcs  Updated to add support for physically aligned allocation and free 
             routines. (US37959)
17apr14,pcs  Added typedef struct pmapInitParams (US34433)
24jan14,pcs  created.
*/

#ifndef __INCpmapLibPh
#define __INCpmapLibPh


#include <vxWorks.h>
#include <vmLib.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

/* definitions */

#define ADDR_ROUND_UP(x, align)    (((x) + (align - 1)) & ~(align - 1))
#define ADDR_ROUND_DOWN(x, align)   ((x) & ~(align - 1))

#define PMAP_ATTR_MASK    (MMU_ATTR_VALID_MSK | MMU_ATTR_PROT_MSK | \
                           MMU_ATTR_CACHE_MSK | MMU_ATTR_SPL_MSK)

/* typedefs */

typedef struct pmapInitParams
    {
    PHYS_MEM_DESC *     pPhysMemDesc;           /* physMemDesc pointer */
    int                 physMemDescNumEnt;      /* number of elements */
    VIRT_ADDR           localMemLocalAdrs;      /* where memory begins */
    VIRT_ADDR           kernelMemTop;           /* top of kernel mem (heap) */
    } PMAP_INIT_PARAMS; 
    
extern PMAP_INIT_PARAMS   pmapInitParms;

typedef struct 
    {
    VIRT_ADDR (*pPmapGlobalMapRtn)            /* pointer to pmapGlobalMap() */
        (
        PHYS_ADDR       physAddr,
        size_t          len,
        UINT            attr
        );
    STATUS (*pPmapGlobalUnmapRtn)          /* pointer to pmapGlobalUnmap() */
        (
        VIRT_ADDR       virtAddr,
        size_t          len
        );
    VIRT_ADDR (*pPmapPrivateMapRtn)            /* pointer to pmapPrivateMap() */
        (
        PHYS_ADDR       physAddr,
        size_t          len,
        UINT            attr
        );
    STATUS (*pPmapPrivateUnmapRtn)          /* pointer to pmapPrivateUnmap() */
        (
        VIRT_ADDR       virtAddr,
        size_t          len
        );
    /* pointer to pmapGlobalPhysAlignedAlloc() */
    VIRT_ADDR (*pPmapGlobalPhysAlignedAllocRtn) 
        (
        size_t          len,
        size_t          alignment,
        UINT            attr
        );
    /* pointer to pmapGlobalPhysAlignedFree() */
    STATUS (*pPmapGlobalPhysAlignedFreeRtn) 
        (
        VIRT_ADDR       virtAddr,
        size_t          len
        );
    /* pointer to pmapPrivatePhysAlignedAlloc() */
    VIRT_ADDR (*pPmapPrivatePhysAlignedAllocRtn)
        (
        size_t          len,
        size_t          alignment,
        UINT            attr
        );
    /* pointer to pmapPrivatePhysAlignedFree() */
    STATUS (*pPmapPrivatePhysAlignedFreeRtn)
        (
        VIRT_ADDR       virtAddr,
        size_t          len
        );
    } PMAP_LIB_FUNCS;

extern PMAP_LIB_FUNCS   pmapLibFuncs;

/* function declarations */


#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCpmapLibPh */
