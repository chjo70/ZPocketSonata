/* mmuTblPartheapSP.h -  */

/*
 * Copyright (c) 2012, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
24mar15,j_l  Initial modifications for IA 32 bit GEN2 support
20mar15,ylu  updated for PPC32 (F2518)
16mar15,w_x  Integrated to VxWorks 7 with update for PPC64 (F2518)
28jan04,zl   created
*/

#ifndef __INCmmuTblPartHeapSPh
#define __INCmmuTblPartHeapSPh



#ifdef __cplusplus
extern "C" {
#endif

typedef struct _mmuTblHeap
    {
    int		dummy;
    } _MMU_TBL_HEAP;


/*******************************************************************************
*
* mmuTblHeapInit -
*/

_WRS_INLINE STATUS mmuTblHeapInit
    (
    _MMU_TBL_HEAP *	pTblHeap
    )
    {
    return (OK);
    }

/*******************************************************************************
*
* mmuTblHeapProtectionEnable -
*/

_WRS_INLINE STATUS mmuTblHeapProtectionEnable
    (
    _MMU_TBL_HEAP *	pTblHeap
    )
    {
    return (OK);
    }

/*******************************************************************************
*
* mmuTblHeapGrow -
*/

_WRS_INLINE STATUS mmuTblHeapGrow
    (
    _MMU_TBL_HEAP *	pTblHeap
    )
    {
    return (ERROR);
    }

/*******************************************************************************
*
* mmuTblHeapDelete -
*/

_WRS_INLINE STATUS mmuTblHeapDelete
    (
    _MMU_TBL_HEAP *	pTblHeap
    )
    {
    return (OK);
    }

/*******************************************************************************
*
* mmuTblHeapAlloc -
*/

_WRS_INLINE void * mmuTblHeapAlloc
    (
    _MMU_TBL_HEAP *	pTblHeap,
    size_t		size,
    size_t		align
    )
    {
#ifndef _WRS_CONFIG_COMPAT69_ADR_SPACE
    return (kProxHeapAlignedAlloc (size, align));
#else
    return (KMEM_ALIGNED_ALLOC (size, align));
#endif
    }

/*******************************************************************************
*
* mmuTblHeapFree -
*/

_WRS_INLINE STATUS mmuTblHeapFree
    (
    _MMU_TBL_HEAP *	pTblHeap,
    void *		pTbl,
    size_t		size
    )
    {
#ifndef _WRS_CONFIG_COMPAT69_ADR_SPACE
    return (kProxHeapFree (pTbl));
#else /* _WRS_CONFIG_COMPAT69_ADR_SPACE */
    return (KMEM_FREE (pTbl));
#endif /* _WRS_CONFIG_COMPAT69_ADR_SPACE */
    }

#ifdef __cplusplus
    }
#endif

#endif /* __INCmmuTblPartHeapSPh */
