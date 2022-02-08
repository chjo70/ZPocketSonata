/* mmuLibSP.h - Architecture dependent MMU library header */

/*
 * Copyright (c) 2012, 2015-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
10feb17,cfm  cleaned the mmuArchLibP.h including path
10jun16,h_k  fixed unexpected page table deletion on kernel VM context.
08jun16,wqi  fixed mmu map/unmap issue. (V7RAD-1543)
12may16,wqi  supported ARMV8A. (US79684)
29apr16,d_l  add taskCpuLock to protect mmuTlbInvalidate. (V7PRO-3050)
03sep15,h_k  moved S_mmuLib_INVALID_XXX macros to mmuLib.h. (V7COR-3487)
15may15,rbc  US58442 Modifications for New MMU
27apr15,j_l  Initial modifications for IA 32 bit GEN2 support
16mar15,w_x  Integrated to VxWorks 7 with update for PPC64 (F2518)
28jan12,zl   created
*/

#ifndef __INCmmuLibSPh
#define __INCmmuLibSPh

#include <vxWorks.h>
#include <bmpLib.h>
#include <private/memPartLibP.h>
#include <private/kwriteLibP.h> /* _func_kprintf */

#define _MMU_CTXID_ERROR          -1U
#define _MMU_TLB_ENTRY_ALL        -1U
#define _MMU_DEBUG_ENABLE         0

#define _MMU_TBL_PART_HEAP_ENABLE   0

#if _MMU_DEBUG_ENABLE
#define MMU_DEBUG_MSG(fmt, args...)                 \
    do                                              \
        {                                           \
        if (_func_kprintf != NULL)                  \
            {                                       \
            _func_kprintf ("%s %d ", __FUNCTION__, __LINE__);        \
            _func_kprintf (fmt, ##args);            \
            }                                       \
        } while (FALSE)
#else
#define MMU_DEBUG_MSG(fmt, args...)
#endif

#include ARCH_HEADER (private/mmuArchLibP.h)

#if _MMU_TBL_PART_HEAP_ENABLE
#include <private/mmuTblPartHeapSP.h>
#else
#include <private/mmuTblBuddyHeapSP.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif


#define MMU_ATTR_SPL_INDEX_SHIFT         12

#define MMU_TRANS_TBL_ID_TO_PGTBL(id)    ((MMU_PG_TBL *)id)

#define MMU_L1_GBL_MAP_WORDS             ((MMU_L1_ENTRY_COUNT + 31) / 32)


#ifdef _WRS_MMU_HAS_STATIC_MAP_INFO

/* first three entries must overlap with VIRT_EXTRA_MAP_INFO */

typedef struct mmu_static_map_info
    {
    VIRT_ADDR        virtAddr;
    size_t           size;
    PHYS_ADDR        physAddr;
    MMU_ARCH_ATTR    mmuAttr;
    } MMU_STATIC_MAP_INFO;

#endif /* _WRS_MMU_HAS_STATIC_MAP_INFO */


#ifdef _WRS_MMU_USES_OS_IMPL_ATTR

#if (MMU_IMPL_ATTR_CNT == 0)
#error "MMU library uses implementation attributes but MMU_IMPL_ATTR_CNT is 0"
#endif

#define MMU_L1_IMPL_ATTR_WORDS            \
    ((MMU_L1_ENTRY_COUNT * MMU_IMPL_ATTR_CNT + 31) / 32)
#define MMU_L2_IMPL_ATTR_WORDS            \
    ((MMU_L2_ENTRY_COUNT * MMU_IMPL_ATTR_CNT + 31) / 32)
#define MMU_L3_IMPL_ATTR_WORDS            \
    ((MMU_L3_ENTRY_COUNT * MMU_IMPL_ATTR_CNT + 31) / 32)
#define MMU_L4_IMPL_ATTR_WORDS            \
    ((MMU_L4_ENTRY_COUNT * MMU_IMPL_ATTR_CNT + 31) / 32)


#ifdef _WRS_MMU_FOUR_LEVEL_PT

typedef struct mmuL4Tbl
    {
    MMU_L4_ENTRY *    pL4EntryTbl;
    UINT32            implAttrMap[MMU_L4_IMPL_ATTR_WORDS];
    } MMU_L4_TBL;

typedef struct mmuL3Tbl
    {
    MMU_L3_ENTRY *    pL3EntryTbl;
    UINT32            implAttrMap[MMU_L3_IMPL_ATTR_WORDS];
    MMU_L4_TBL *      pL4Tbl[MMU_L3_ENTRY_COUNT];
    } MMU_L3_TBL;

#endif /* _WRS_MMU_FOUR_LEVEL_PT */

typedef struct mmuL2Tbl
    {
    MMU_L2_ENTRY *    pL2EntryTbl;
    UINT32            implAttrMap[MMU_L2_IMPL_ATTR_WORDS];
#ifdef _WRS_MMU_FOUR_LEVEL_PT
    MMU_L3_TBL *      pL3Tbl[MMU_L2_ENTRY_COUNT];
#endif /* _WRS_MMU_FOUR_LEVEL_PT */
    } MMU_L2_TBL;

typedef struct mmuL1Tbl
    {
    MMU_L1_ENTRY *   pL1EntryTbl;    /* MMU table pointer */
    UINT32           gblMap[MMU_L1_GBL_MAP_WORDS];
    UINT32           implAttrMap[MMU_L1_IMPL_ATTR_WORDS];
    MMU_L2_TBL *     pL2Tbl[MMU_L1_ENTRY_COUNT];
    } MMU_L1_TBL;

#else /* _WRS_MMU_USES_OS_IMPL_ATTR */

#ifdef _WRS_MMU_FOUR_LEVEL_PT

typedef MMU_L4_ENTRY    MMU_L4_TBL;
typedef MMU_L3_ENTRY    MMU_L3_TBL;

#endif /* _WRS_MMU_FOUR_LEVEL_PT */

typedef MMU_L2_ENTRY    MMU_L2_TBL;

typedef struct mmuL1Tbl
    {
    MMU_L1_ENTRY *    pL1EntryTbl;      /* MMU table pointer */
    UINT32            gblMap[MMU_L1_GBL_MAP_WORDS];
    } MMU_L1_TBL;

#endif /* _WRS_MMU_USES_OS_IMPL_ATTR */

typedef struct mmuPgTbl
    {
    /*
     * xxx - ctxId must be first for E500, see AIM_MMU_CTX_ID_GET()
     *       MMU_CTX_TBASE must be first for IA, see taskRegsInit()
     */

#if (_VX_CPU_FAMILY == _VX_PPC)
    MMU_CTX_ID       ctxId;            /* context id */
    MMU_CTX_TBASE    transBase;        /* MMU translation base */
#else
    MMU_CTX_TBASE    transBase;        /* MMU translation base */
    MMU_CTX_ID       ctxId;            /* context id */
#endif
    _MMU_TBL_HEAP    tblHeap;          /* page table heap */
    MMU_L1_TBL       mmuL1Tbl;         /* private L1 table */
#ifdef _WRS_MMU_SUPPORTS_GLOBAL_TABLE
    MMU_L1_TBL *     pGblL1Tbl;        /* global L1 table (shared) */
#endif
    } MMU_PG_TBL;

extern BOOL   mmuIsEnabled;

#ifdef _WRS_MMU_HAS_STATIC_MAP_INFO
extern MMU_STATIC_MAP_INFO staticMapInfo[_MMU_STATIC_MAP_ENTRY_COUNT];
extern UINT staticMapCount;
#endif


extern void * mmuEntryTableAlloc (MMU_PG_TBL * pPgTbl, size_t size,
                                  size_t align);
extern STATUS mmuEntryTableFree (MMU_PG_TBL * pPgTbl, void * pTbl,
                                 size_t size);
extern STATUS mmuStaticMapCheck (VIRT_ADDR virtAddr, size_t size);

#ifdef _WRS_MMU_SUPPORTS_L1_MAP
extern STATUS mmuL1Deoptimize (MMU_PG_TBL * pPgTbl, MMU_L1_TBL * pL1, size_t iL1,
                               VIRT_ADDR virtAddr, MMU_CTX_ID ctxId);
#endif

#if defined (_WRS_MMU_SUPPORTS_L2_MAP) && defined (_WRS_MMU_FOUR_LEVEL_PT)
extern STATUS mmuL2Deoptimize (MMU_PG_TBL * pPgTbl, MMU_L2_TBL * pL2, size_t iL2,
                               VIRT_ADDR virtAddr, MMU_CTX_ID ctxId);
#endif

#ifdef _WRS_MMU_SUPPORTS_L3_MAP
extern STATUS mmuL3Deoptimize (MMU_PG_TBL * pPgTbl, MMU_L3_TBL * pL3, size_t iL3,
                               VIRT_ADDR virtAddr, MMU_CTX_ID ctxId);
#endif

#if defined (_WRS_CONFIG_SMP) && defined (_WRS_MMU_SW_TLB_COHERENCY)
void mmuTlbInvalidateCpcInvoke (VIRT_ADDR virtAddr, size_t entrySize,
                                MMU_CTX_ID ctxId, size_t count);
#endif

#ifdef _WRS_MMU_USES_OS_IMPL_ATTR
#define _MMU_L1_ENTRY_TBL(pL1)      ((pL1)->pL1EntryTbl)
#define _MMU_L2_ENTRY_TBL(pL2)      ((pL2)->pL2EntryTbl)
#define _MMU_L3_ENTRY_TBL(pL3)      ((pL3)->pL3EntryTbl)
#define _MMU_L4_ENTRY_TBL(pL4)      ((pL4)->pL4EntryTbl)
#define _MMU_L1_ENTRY_PTR(pL1,iL1)    (&(pL1)->pL1EntryTbl[iL1])
#define _MMU_L2_ENTRY_PTR(pL2,iL2)    (&(pL2)->pL2EntryTbl[iL2])
#define _MMU_L3_ENTRY_PTR(pL3,iL3)    (&(pL3)->pL3EntryTbl[iL3])
#define _MMU_L4_ENTRY_PTR(pL4,iL4)    (&(pL4)->pL4EntryTbl[iL4])
#else
#define _MMU_L1_ENTRY_TBL(pL1)      ((pL1)->pL1EntryTbl)
#define _MMU_L2_ENTRY_TBL(pL2)      ((MMU_L2_ENTRY *)(pL2))
#define _MMU_L3_ENTRY_TBL(pL3)      ((MMU_L3_ENTRY *)(pL3))
#define _MMU_L4_ENTRY_TBL(pL4)      ((MMU_L4_ENTRY *)(pL4))
#define _MMU_L1_ENTRY_PTR(pL1,iL1)    (&(pL1)->pL1EntryTbl[iL1])
#define _MMU_L2_ENTRY_PTR(pL2,iL2)    (&((MMU_L2_ENTRY *)(pL2))[iL2])
#define _MMU_L3_ENTRY_PTR(pL3,iL3)    (&((MMU_L3_ENTRY *)(pL3))[iL3])
#define _MMU_L4_ENTRY_PTR(pL4,iL4)    (&((MMU_L4_ENTRY *)(pL4))[iL4])
#endif


/*******************************************************************************
*
* mmuMemAlloc -
*/

_WRS_INLINE void * mmuMemAlloc
    (
    size_t size
    )
    {
    return (KMEM_ALLOC (size));
    }

/*******************************************************************************
*
* mmuMemFree -
*/

_WRS_INLINE STATUS mmuMemFree
    (
    void * pBlock
    )
    {
#ifdef _WRS_CONFIG_MEM_ALLOT
    return (OK);
#else
    return (KMEM_FREE (pBlock));
#endif
    }

#ifdef _WRS_MMU_USES_OS_IMPL_ATTR
/*******************************************************************************
*
* mmuImplAttrSet -
*/

_WRS_INLINE void mmuImplAttrSet
    (
    UINT32 *    pImpl,
    size_t      ix,
    size_t      count,
    UINT        implAttr
    )
    {
    size_t        stopIx;
    UINT        temp;

    stopIx = ix + count;

    /* xxx - optimize (and make it atomic) */

    for ( ; ix < stopIx; ix++)
        {
        temp  = *(pImpl + ix * MMU_IMPL_ATTR_CNT / 32);
        temp &= ~(((1 << MMU_IMPL_ATTR_CNT) - 1) <<
                  ((ix * MMU_IMPL_ATTR_CNT) % 32));
        temp |= implAttr << ((ix * MMU_IMPL_ATTR_CNT) % 32);
        *(pImpl + ix * MMU_IMPL_ATTR_CNT / 32) = temp;
        }
    }

/*******************************************************************************
*
* mmuImplAttrGet -
*/

_WRS_INLINE MMU_ARCH_ATTR mmuImplAttrGet
    (
    UINT32 *    pImpl,
    size_t      ix
    )
    {
    UINT32           implAttr;

    /* Note: MMU_IMPL_ATTR_CNT must be power of two */

    implAttr = *(pImpl + ix * MMU_IMPL_ATTR_CNT / 32) >>
               ((ix * MMU_IMPL_ATTR_CNT) % 32);

    implAttr &= (1 << MMU_IMPL_ATTR_CNT) - 1;

    return (implAttr);
    }
#endif /* _WRS_MMU_USES_OS_IMPL_ATTR */

/*******************************************************************************
*
* mmuL1TableGet -
*/

_WRS_INLINE MMU_L1_TBL * mmuL1TableGet
    (
    MMU_PG_TBL *    pTbl,
    VIRT_ADDR       virtAddr
    )
    {
#ifdef _WRS_MMU_SUPPORTS_GLOBAL_TABLE
    if (mmuAddrIsGlobal (virtAddr))
        {
	return (pTbl->pGblL1Tbl);
	}
    else
	{
	return &pTbl->mmuL1Tbl;
	}
#else
    return (&pTbl->mmuL1Tbl);
#endif
    }

/*******************************************************************************
*
* mmuL2TableGet -
*/

_WRS_INLINE MMU_L2_TBL * mmuL2TableGet
    (
    MMU_L1_TBL *    pL1,
    size_t          iL1,
    BOOL *          pGlobal
    )
    {
    MMU_L2_TBL *    pL2;
#if (_VX_CPU == _VX_ARMARCH8A)
    if (pL1 == NULL)
        return NULL;
#endif
#ifdef _WRS_MMU_USES_OS_IMPL_ATTR
    pL2 = pL1->pL2Tbl[iL1];
#else /* _WRS_MMU_USES_OS_IMPL_ATTR */
    pL2 = (MMU_L2_TBL *) mmuL2EntryTableGet (_MMU_L1_ENTRY_PTR(pL1, iL1));
#endif /* _WRS_MMU_USES_OS_IMPL_ATTR */

    if ((pL2 != NULL) && (pGlobal != NULL))
        *pGlobal = (bitGet (iL1, pL1->gblMap) != 0);

    return (pL2);
    }

/*******************************************************************************
*
* mmuL2TableSet -
*/

_WRS_INLINE void mmuL2TableSet
    (
    MMU_L1_TBL *    pL1,
    size_t          iL1,
    MMU_L2_TBL *    pL2,
    BOOL            global
    )
    {
#ifdef _WRS_MMU_USES_OS_IMPL_ATTR
    pL1->pL2Tbl[iL1] = pL2;
    mmuImplAttrSet (pL1->implAttrMap, iL1, 1, 0);
#endif

#ifndef _WRS_MMU_L2_ALIASES_L1
    mmuL2EntryTableSet (_MMU_L1_ENTRY_PTR(pL1, iL1), _MMU_L2_ENTRY_TBL(pL2));
#endif

    /* global mappings are identified at an L1 index */

    if (global)
        bitSet (iL1, pL1->gblMap);
    else
        bitClear (iL1, pL1->gblMap);
    }

/*******************************************************************************
*
* mmuL2TableClearForce -
*/

_WRS_INLINE void mmuL2TableClearForce
    (
    MMU_L1_TBL *    pL1,
    size_t          iL1
    )
    {
#ifdef _WRS_MMU_USES_OS_IMPL_ATTR
    pL1->pL2Tbl[iL1] = NULL;
    mmuImplAttrSet (pL1->implAttrMap, iL1, 1, 0);
#endif

#ifndef _WRS_MMU_L2_ALIASES_L1
    mmuL1EntryClear (_MMU_L1_ENTRY_PTR(pL1, iL1), (size_t) 1);
#endif

    /* global mappings are identified at an L1 index */

    bitClear (iL1, pL1->gblMap);
    }

/*******************************************************************************
*
* mmuL2TableClear -
*/

_WRS_INLINE void mmuL2TableClear
    (
    MMU_L1_TBL *    pL1,
    size_t          iL1
    )
    {
#if (_VX_CPU == _VX_ARMARCH8A)
    /* if the entry is global, don't clear the table */

    if (bitGet (iL1, pL1->gblMap) != 0)
	return;
#endif
    mmuL2TableClearForce (pL1, iL1);
    }

#ifdef _WRS_MMU_FOUR_LEVEL_PT
/*******************************************************************************
*
* mmuL3TableGet -
*/

_WRS_INLINE MMU_L3_TBL * mmuL3TableGet
    (
    MMU_L2_TBL *    pL2,
    size_t          iL2
    )
    {
#ifdef _WRS_MMU_USES_OS_IMPL_ATTR
    return (pL2->pL3Tbl[iL2]);
#else /* _WRS_MMU_USES_OS_IMPL_ATTR */
    return ((MMU_L3_TBL *) mmuL3EntryTableGet (_MMU_L2_ENTRY_PTR(pL2, iL2)));
#endif /* _WRS_MMU_USES_OS_IMPL_ATTR */
    }

/*******************************************************************************
*
* mmuL3TableSet -
*/

_WRS_INLINE void mmuL3TableSet
    (
    MMU_L2_TBL *    pL2,
    size_t          iL2,
    MMU_L3_TBL *    pL3
    )
    {
#ifdef _WRS_MMU_USES_OS_IMPL_ATTR
    pL2->pL3Tbl[iL2] = pL3;
    mmuImplAttrSet (pL2->implAttrMap, iL2, 1, 0);
#endif

#ifndef _WRS_MMU_L3_ALIASES_L2

    mmuL3EntryTableSet (_MMU_L2_ENTRY_PTR(pL2, iL2), _MMU_L3_ENTRY_TBL(pL3));
#endif
    }

/*******************************************************************************
*
* mmuL3TableClear -
*/

_WRS_INLINE void mmuL3TableClear
    (
    MMU_L2_TBL *    pL2,
    size_t          iL2
    )
    {
#ifdef _WRS_MMU_USES_OS_IMPL_ATTR
    pL2->pL3Tbl[iL2] = NULL;
    mmuImplAttrSet (pL2->implAttrMap, iL2, 1, 0);
#endif

#ifndef _WRS_MMU_L3_ALIASES_L2
    mmuL2EntryClear (_MMU_L2_ENTRY_PTR(pL2, iL2), 1);
#endif
    }

/*******************************************************************************
*
* mmuL4TableGet -
*/

_WRS_INLINE MMU_L4_TBL * mmuL4TableGet
    (
    MMU_L3_TBL *    pL3,
    size_t          iL3
    )
    {
#ifdef _WRS_MMU_USES_OS_IMPL_ATTR
    return (pL3->pL4Tbl[iL3]);
#else /* _WRS_MMU_USES_OS_IMPL_ATTR */
    return ((MMU_L4_TBL *) mmuL4EntryTableGet (_MMU_L3_ENTRY_PTR(pL3, iL3)));
#endif /* _WRS_MMU_USES_OS_IMPL_ATTR */
    }

/*******************************************************************************
*
* mmuL4TableSet -
*/

_WRS_INLINE void mmuL4TableSet
    (
    MMU_L3_TBL *    pL3,
    size_t          iL3,
    MMU_L4_TBL *    pL4
    )
    {
#ifdef _WRS_MMU_USES_OS_IMPL_ATTR
    pL3->pL4Tbl[iL3] = pL4;
    mmuImplAttrSet (pL3->implAttrMap, iL3, 1, 0);
#endif

#ifndef _WRS_MMU_L4_ALIASES_L3
    mmuL4EntryTableSet (_MMU_L3_ENTRY_PTR(pL3, iL3), _MMU_L4_ENTRY_TBL(pL4));
#endif
    }
#endif /* _WRS_MMU_FOUR_LEVEL_PT */

#ifdef _WRS_MMU_SUPPORTS_L1_MAP
/*******************************************************************************
*
* mmuL1Set -
*/

_WRS_INLINE STATUS mmuL1Set
    (
    MMU_L1_TBL *        pL1,
    size_t              iL1,
    VIRT_ADDR           virtAddr,
    PHYS_ADDR           physAddr,
    size_t              count,
    MMU_ARCH_ATTR       attr,
    MMU_CTX_ID          ctxId,
    BOOL                isNew
    )
    {
    STATUS      stat = OK;

#ifdef _WRS_MMU_USES_OS_IMPL_ATTR
    UINT        implAttr;

    if (pL1->pL2Tbl[iL1] != NULL)
        return (ERROR);

    stat = mmuL1EntrySet (_MMU_L1_ENTRY_PTR(pL1, iL1), virtAddr, physAddr,
                          count, attr & ~_MMU_MASK_IMPL, ctxId, isNew);

    if (stat == OK)
        {
        implAttr = (attr & _MMU_MASK_IMPL) >> _MMU_IMPL_SHIFT;
        implAttr |= _MMU_IMPL_MAPPED;
        mmuImplAttrSet (pL1->implAttrMap, iL1, count, implAttr);
        }
#else
    stat = mmuL1EntrySet (_MMU_L1_ENTRY_PTR(pL1, iL1), virtAddr, physAddr,
                          count, attr, ctxId, isNew);
#endif

    return (stat);
    }

/*******************************************************************************
*
* mmuL1Get -
*/

_WRS_INLINE STATUS mmuL1Get
    (
    MMU_L1_TBL *        pL1,
    size_t              iL1,
    PHYS_ADDR *         pPhysAddr,
    MMU_ARCH_ATTR *     pAttr
    )
    {
#ifdef _WRS_MMU_USES_OS_IMPL_ATTR
    UINT        implAttr;

    implAttr = mmuImplAttrGet (pL1->implAttrMap, iL1);

    if ((implAttr & _MMU_IMPL_MAPPED) != _MMU_IMPL_MAPPED)
        return (ERROR);

    if (mmuL1EntryGet (_MMU_L1_ENTRY_PTR(pL1, iL1), pPhysAddr, pAttr) == ERROR)
        return (ERROR);

    if (pAttr != NULL)
        *pAttr |= (implAttr & ~_MMU_IMPL_MAPPED) << _MMU_IMPL_SHIFT;

    return (OK);
#else
    return (mmuL1EntryGet (_MMU_L1_ENTRY_PTR(pL1, iL1), pPhysAddr, pAttr));
#endif
    }

/*******************************************************************************
*
* mmuL1Clear -
*/

_WRS_INLINE void mmuL1Clear
    (
    MMU_L1_TBL *  pL1,
    size_t        iL1,
    size_t        count
    )
    {
    mmuL1EntryClear (_MMU_L1_ENTRY_PTR(pL1, iL1), count);

#ifdef _WRS_MMU_USES_OS_IMPL_ATTR
    mmuImplAttrSet (pL1->implAttrMap, iL1, count, 0);
#endif
    }
#endif /* _WRS_MMU_SUPPORTS_L1_MAP */

#ifdef _WRS_MMU_SUPPORTS_L2_MAP
/*******************************************************************************
*
* mmuL2Set -
*/

_WRS_INLINE STATUS mmuL2Set
    (
    MMU_L2_TBL *    pL2,
    size_t          iL2,
    VIRT_ADDR       virtAddr,
    PHYS_ADDR       physAddr,
    size_t          count,
    MMU_ARCH_ATTR   attr,
    MMU_CTX_ID      ctxId,
    BOOL            isNew
    )
    {
    STATUS        stat = OK;

#ifdef _WRS_MMU_USES_OS_IMPL_ATTR
    UINT        implAttr;

#ifdef _WRS_MMU_FOUR_LEVEL_PT
    if (pL2->pL3Tbl[iL2] != NULL)
        return (ERROR);
#endif /* _WRS_MMU_FOUR_LEVEL_PT */

    stat = mmuL2EntrySet (_MMU_L2_ENTRY_PTR(pL2, iL2), virtAddr, physAddr,
                          count, attr & ~_MMU_MASK_IMPL, ctxId, isNew);

    if (stat == OK)
        {
        implAttr = (attr & _MMU_MASK_IMPL) >> _MMU_IMPL_SHIFT;
        implAttr |= _MMU_IMPL_MAPPED;
        mmuImplAttrSet (pL2->implAttrMap, iL2, count, implAttr);
        }
#else /* _WRS_MMU_USES_OS_IMPL_ATTR */

    stat = mmuL2EntrySet (_MMU_L2_ENTRY_PTR(pL2, iL2), virtAddr, physAddr,
                          count, attr, ctxId, isNew);

#endif /* _WRS_MMU_USES_OS_IMPL_ATTR */

    return (stat);
    }

/*******************************************************************************
*
* mmuL2Get -
*/

_WRS_INLINE STATUS mmuL2Get
    (
    MMU_L2_TBL *        pL2,
    size_t              iL2,
    PHYS_ADDR *         pPhysAddr,
    MMU_ARCH_ATTR *     pAttr
    )
    {
#ifdef _WRS_MMU_USES_OS_IMPL_ATTR
    UINT        implAttr;

    implAttr = mmuImplAttrGet (pL2->implAttrMap, iL2);

    if ((implAttr & _MMU_IMPL_MAPPED) != _MMU_IMPL_MAPPED)
        return (ERROR);

    if (mmuL2EntryGet (_MMU_L2_ENTRY_PTR(pL2, iL2), pPhysAddr, pAttr) == ERROR)
        return (ERROR);

    if (pAttr != NULL)
        *pAttr |= (implAttr & ~_MMU_IMPL_MAPPED) << _MMU_IMPL_SHIFT;

    return (OK);
#else /* _WRS_MMU_USES_OS_IMPL_ATTR */

    return (mmuL2EntryGet (_MMU_L2_ENTRY_PTR(pL2, iL2), pPhysAddr, pAttr));

#endif /* _WRS_MMU_USES_OS_IMPL_ATTR */
    }

/*******************************************************************************
*
* mmuL2Clear -
*/

_WRS_INLINE void mmuL2Clear
    (
    MMU_L2_TBL *    pL2,
    size_t          iL2,
    size_t          count
    )
    {
    mmuL2EntryClear (_MMU_L2_ENTRY_PTR(pL2, iL2), count);

#ifdef _WRS_MMU_USES_OS_IMPL_ATTR
    mmuImplAttrSet (pL2->implAttrMap, iL2, count, 0);
#endif
    }
#endif /* _WRS_MMU_SUPPORTS_L2_MAP */

#ifdef _WRS_MMU_SUPPORTS_L3_MAP
/*******************************************************************************
*
* mmuL3Set -
*/

_WRS_INLINE STATUS mmuL3Set
    (
    MMU_L3_TBL *    pL3,
    size_t          iL3,
    VIRT_ADDR       virtAddr,
    PHYS_ADDR       physAddr,
    size_t          count,
    MMU_ARCH_ATTR   attr,
    MMU_CTX_ID      ctxId,
    BOOL            isNew
    )
    {
    STATUS        stat = OK;

#ifdef _WRS_MMU_USES_OS_IMPL_ATTR
    UINT        implAttr;

    if (pL3->pL4Tbl[iL3] != NULL)
        return (ERROR);

    stat = mmuL3EntrySet (_MMU_L3_ENTRY_PTR(pL3, iL3), virtAddr, physAddr,
                          count, attr & ~_MMU_MASK_IMPL, ctxId, isNew);

    if (stat == OK)
        {
        implAttr = (attr & _MMU_MASK_IMPL) >> _MMU_IMPL_SHIFT;
        implAttr |= _MMU_IMPL_MAPPED;
        mmuImplAttrSet (pL3->implAttrMap, iL3, count, implAttr);
        }
#else /* _WRS_MMU_USES_OS_IMPL_ATTR */

    stat = mmuL3EntrySet (_MMU_L3_ENTRY_PTR(pL3, iL3), virtAddr, physAddr,
                          count, attr, ctxId, isNew);

#endif /* _WRS_MMU_USES_OS_IMPL_ATTR */

    return (stat);
    }

/*******************************************************************************
*
* mmuL3Get -
*/

_WRS_INLINE STATUS mmuL3Get
    (
    MMU_L3_TBL *        pL3,
    size_t              iL3,
    PHYS_ADDR *         pPhysAddr,
    MMU_ARCH_ATTR *     pAttr
    )
    {
#ifdef _WRS_MMU_USES_OS_IMPL_ATTR
    UINT        implAttr;

    implAttr = mmuImplAttrGet (pL3->implAttrMap, iL3);

    if ((implAttr & _MMU_IMPL_MAPPED) != _MMU_IMPL_MAPPED)
        return (ERROR);

    if (mmuL3EntryGet (_MMU_L3_ENTRY_PTR(pL3, iL3), pPhysAddr, pAttr) == ERROR)
        return (ERROR);

    if (pAttr != NULL)
        *pAttr |= (implAttr & ~_MMU_IMPL_MAPPED) << _MMU_IMPL_SHIFT;

    return (OK);
#else /* _WRS_MMU_USES_OS_IMPL_ATTR */

    return (mmuL3EntryGet (_MMU_L3_ENTRY_PTR(pL3, iL3), pPhysAddr, pAttr));

#endif /* _WRS_MMU_USES_OS_IMPL_ATTR */
    }

/*******************************************************************************
*
* mmuL3Clear -
*/

_WRS_INLINE void mmuL3Clear
    (
    MMU_L3_TBL *    pL3,
    size_t          iL3,
    size_t          count
    )
    {
    mmuL3EntryClear (_MMU_L3_ENTRY_PTR(pL3, iL3), count);

#ifdef _WRS_MMU_USES_OS_IMPL_ATTR
    mmuImplAttrSet (pL3->implAttrMap, iL3, count, 0);
#endif
    }
#endif /* _WRS_MMU_SUPPORTS_L3_MAP */

#ifdef _WRS_MMU_SUPPORTS_L4_MAP
/*******************************************************************************
*
* mmuL4Set -
*/

_WRS_INLINE STATUS mmuL4Set
    (
    MMU_L4_TBL *    pL4,
    size_t          iL4,
    VIRT_ADDR       virtAddr,
    PHYS_ADDR       physAddr,
    size_t          count,
    MMU_ARCH_ATTR   attr,
    MMU_CTX_ID      ctxId,
    BOOL            isNew
    )
    {
    STATUS          stat = OK;
#ifdef _WRS_MMU_USES_OS_IMPL_ATTR
    UINT            implAttr;

    stat = mmuL4EntrySet (_MMU_L4_ENTRY_PTR(pL4, iL4), virtAddr, physAddr,
                          count, attr & ~_MMU_MASK_IMPL, ctxId, isNew);

    if (stat == OK)
        {
        implAttr = (attr & _MMU_MASK_IMPL) >> _MMU_IMPL_SHIFT;
        implAttr |= _MMU_IMPL_MAPPED;
        mmuImplAttrSet (pL4->implAttrMap, iL4, count, implAttr);
        }
#else /* _WRS_MMU_USES_OS_IMPL_ATTR */

    stat = mmuL4EntrySet (_MMU_L4_ENTRY_PTR(pL4, iL4), virtAddr, physAddr,
                          count, attr, ctxId, isNew);

#endif /* _WRS_MMU_USES_OS_IMPL_ATTR */

    return (stat);
    }

/*******************************************************************************
*
* mmuL4Get -
*/

_WRS_INLINE STATUS mmuL4Get
    (
    MMU_L4_TBL *        pL4,
    size_t              iL4,
    PHYS_ADDR *         pPhysAddr,
    MMU_ARCH_ATTR *     pAttr
    )
    {
#ifdef _WRS_MMU_USES_OS_IMPL_ATTR
    UINT        implAttr;

    implAttr = mmuImplAttrGet (pL4->implAttrMap, iL4);

    if ((implAttr & _MMU_IMPL_MAPPED) != _MMU_IMPL_MAPPED)
        return (ERROR);

    if (mmuL4EntryGet (_MMU_L4_ENTRY_PTR(pL4, iL4), pPhysAddr, pAttr) == ERROR)
        return (ERROR);

    if (pAttr != NULL)
        *pAttr |= (implAttr & ~_MMU_IMPL_MAPPED) << _MMU_IMPL_SHIFT;

    return (OK);
#else /* _WRS_MMU_USES_OS_IMPL_ATTR */

    return (mmuL4EntryGet (_MMU_L4_ENTRY_PTR(pL4, iL4), pPhysAddr, pAttr));

#endif /* _WRS_MMU_USES_OS_IMPL_ATTR */
    }

/*******************************************************************************
*
* mmuL4Clear -
*/

_WRS_INLINE void mmuL4Clear
    (
    MMU_L4_TBL *    pL4,
    size_t          iL4,
    size_t          count
    )
    {
    mmuL4EntryClear (_MMU_L4_ENTRY_PTR(pL4, iL4), count);

#ifdef _WRS_MMU_USES_OS_IMPL_ATTR
    mmuImplAttrSet (pL4->implAttrMap, iL4, count, 0);
#endif /* _WRS_MMU_USES_OS_IMPL_ATTR */
    }
#endif /* _WRS_MMU_SUPPORTS_L4_MAP */

/*******************************************************************************
*
* mmuL2TableAlloc -
*/

_WRS_INLINE MMU_L2_TBL * mmuL2TableAlloc
    (
    MMU_PG_TBL *    pPgTbl,
    MMU_L1_TBL *    pL1,
    size_t          iL1
    )
    {
#ifdef _WRS_MMU_USES_OS_IMPL_ATTR
    MMU_L2_TBL *    pTbl;
    size_t          ix;
#endif
    MMU_L2_ENTRY *  pEntryTbl = NULL;

#ifdef _WRS_MMU_USES_OS_IMPL_ATTR

    pTbl = mmuMemAlloc (sizeof (MMU_L2_TBL));
    if (pTbl == NULL)
        return (NULL);

#ifdef _WRS_MMU_L2_ALIASES_L1
    pTbl->pL2EntryTbl = pL1->pL1EntryTbl[iL1];
#else /* _WRS_MMU_L2_ALIASES_L1 */
    pEntryTbl = mmuEntryTableAlloc (pPgTbl, MMU_L2_TBL_SIZE, MMU_L2_TBL_ALIGN);

    if (pEntryTbl == NULL)
        {
        (void) mmuMemFree (pTbl);
        return (NULL);
        }

    mmuL2EntryClear (pEntryTbl, MMU_L2_ENTRY_COUNT);

    pTbl->pL2EntryTbl = pEntryTbl;
#endif /* _WRS_MMU_L2_ALIASES_L1 */

#ifdef _WRS_MMU_FOUR_LEVEL_PT
    for (ix = 0; ix < MMU_L2_ENTRY_COUNT; ix++)
        pTbl->pL3Tbl[ix] = NULL;
#endif /* _WRS_MMU_FOUR_LEVEL_PT */

    mmuImplAttrSet (pTbl->implAttrMap, 0, MMU_L2_ENTRY_COUNT, 0);

    return (pTbl);

#else /* _WRS_MMU_USES_OS_IMPL_ATTR */

    pEntryTbl = mmuEntryTableAlloc (pPgTbl, MMU_L2_TBL_SIZE, MMU_L2_TBL_ALIGN);

    if (pEntryTbl == NULL)
        return (NULL);

    mmuL2EntryClear (pEntryTbl, MMU_L2_ENTRY_COUNT);

    return ((MMU_L2_TBL *) pEntryTbl);

#endif /* _WRS_MMU_USES_OS_IMPL_ATTR */
    }

/*******************************************************************************
*
* mmuL2TableFree -
*/

_WRS_INLINE STATUS mmuL2TableFree
    (
    MMU_PG_TBL *    pPgTbl,
    MMU_L2_TBL *    pTable
    )
    {
#ifdef _WRS_MMU_USES_OS_IMPL_ATTR
#ifndef _WRS_MMU_L2_ALIASES_L1
    if (mmuEntryTableFree (pPgTbl, pTable->pL2EntryTbl, MMU_L2_TBL_SIZE) == ERROR)
        return (ERROR);
#endif /* _WRS_MMU_L2_ALIASES_L1 */

    return (mmuMemFree (pTable));
#else /* _WRS_MMU_USES_OS_IMPL_ATTR */
    return (mmuEntryTableFree (pPgTbl, pTable, MMU_L2_TBL_SIZE));
#endif /* _WRS_MMU_USES_OS_IMPL_ATTR */
    }

#ifdef _WRS_MMU_FOUR_LEVEL_PT
/*******************************************************************************
*
* mmuL3TableAlloc -
*/

_WRS_INLINE MMU_L3_TBL * mmuL3TableAlloc
    (
    MMU_PG_TBL *    pPgTbl,
    MMU_L2_TBL *    pL2,
    size_t          iL2
    )
    {
#ifdef _WRS_MMU_USES_OS_IMPL_ATTR
    MMU_L3_TBL *    pTbl;
    size_t          ix;
#endif
    MMU_L3_ENTRY *    pEntryTbl = NULL;

#ifdef _WRS_MMU_USES_OS_IMPL_ATTR
    pTbl = mmuMemAlloc (sizeof (MMU_L3_TBL));

    if (pTbl == NULL)
        return (NULL);

#ifdef _WRS_MMU_L3_ALIASES_L2
    pTbl->pL3EntryTbl = pL2->pL2EntryTbl[iL2];
#else /* _WRS_MMU_L3_ALIASES_L2 */
    pEntryTbl = mmuEntryTableAlloc (pPgTbl, MMU_L3_TBL_SIZE, MMU_L3_TBL_ALIGN);

    if (pEntryTbl == NULL)
        {
        (void) mmuMemFree (pTbl);
        return (NULL);
        }

    mmuL3EntryClear (pEntryTbl, MMU_L3_ENTRY_COUNT);

    pTbl->pL3EntryTbl = pEntryTbl;
#endif /* _WRS_MMU_L3_ALIASES_L2 */

    for (ix = 0; ix < MMU_L3_ENTRY_COUNT; ix++)
        pTbl->pL4Tbl[ix] = NULL;

    mmuImplAttrSet (pTbl->implAttrMap, 0, MMU_L3_ENTRY_COUNT, 0);

    return (pTbl);

#else /* _WRS_MMU_USES_OS_IMPL_ATTR */

    pEntryTbl = mmuEntryTableAlloc (pPgTbl, MMU_L3_TBL_SIZE, MMU_L3_TBL_ALIGN);

    if (pEntryTbl == NULL)
        return (NULL);

    mmuL3EntryClear (pEntryTbl, MMU_L3_ENTRY_COUNT);

    return ((MMU_L3_TBL *) pEntryTbl);
#endif /* _WRS_MMU_USES_OS_IMPL_ATTR */
    }

/*******************************************************************************
*
* mmuL3TableFree -
*/

_WRS_INLINE STATUS mmuL3TableFree
    (
    MMU_PG_TBL *    pPgTbl,
    MMU_L3_TBL *    pTable
    )
    {
#ifdef _WRS_MMU_USES_OS_IMPL_ATTR
#ifndef _WRS_MMU_L3_ALIASES_L2
    if (mmuEntryTableFree (pPgTbl, pTable->pL3EntryTbl, MMU_L3_TBL_SIZE) == ERROR)
        return (ERROR);
#endif

    return (mmuMemFree (pTable));
#else /* _WRS_MMU_USES_OS_IMPL_ATTR */
    return (mmuEntryTableFree (pPgTbl, pTable, MMU_L3_TBL_SIZE));
#endif /* _WRS_MMU_USES_OS_IMPL_ATTR */
    }

/*******************************************************************************
*
* mmuL4TableAlloc -
*/

_WRS_INLINE MMU_L4_TBL * mmuL4TableAlloc
    (
    MMU_PG_TBL *    pPgTbl,
    MMU_L3_TBL *    pL3,
    size_t          iL3
    )
    {
#ifdef _WRS_MMU_USES_OS_IMPL_ATTR
    MMU_L4_TBL *    pTbl;
#endif
    MMU_L4_ENTRY *    pEntryTbl = NULL;

#ifdef _WRS_MMU_USES_OS_IMPL_ATTR
    pTbl = mmuMemAlloc (sizeof (MMU_L4_TBL));

    if (pTbl == NULL)
        return (NULL);

#ifdef _WRS_MMU_L4_ALIASES_L3
    pTbl->pL4EntryTbl = pL3->pL3EntryTbl[iL3];
#else /* _WRS_MMU_L4_ALIASES_L3 */
    pEntryTbl = mmuEntryTableAlloc (pPgTbl, MMU_L4_TBL_SIZE, MMU_L4_TBL_ALIGN);

    if (pEntryTbl == NULL)
        {
        (void) mmuMemFree (pTbl);
        return (NULL);
        }

    mmuL4EntryClear (pEntryTbl, MMU_L4_ENTRY_COUNT);

    pTbl->pL4EntryTbl = pEntryTbl;
#endif /* _WRS_MMU_L4_ALIASES_L3 */

    mmuImplAttrSet (pTbl->implAttrMap, 0, MMU_L4_ENTRY_COUNT, 0);

    return (pTbl);

#else /* _WRS_MMU_USES_OS_IMPL_ATTR */

    pEntryTbl = mmuEntryTableAlloc (pPgTbl, MMU_L4_TBL_SIZE, MMU_L4_TBL_ALIGN);

    if (pEntryTbl == NULL)
        return (NULL);

    mmuL4EntryClear (pEntryTbl, MMU_L4_ENTRY_COUNT);

    return ((MMU_L4_TBL *) pEntryTbl);
#endif /* _WRS_MMU_USES_OS_IMPL_ATTR */
    }

/*******************************************************************************
*
* mmuL4TableFree -
*/

_WRS_INLINE STATUS mmuL4TableFree
    (
    MMU_PG_TBL *    pPgTbl,
    MMU_L4_TBL *    pTable
    )
    {
#ifdef _WRS_MMU_USES_OS_IMPL_ATTR
#ifndef _WRS_MMU_L4_ALIASES_L3
    if (mmuEntryTableFree (pPgTbl, pTable->pL4EntryTbl, MMU_L4_TBL_SIZE) == ERROR)
        return (ERROR);
#endif

    return (mmuMemFree (pTable));
#else /* _WRS_MMU_USES_OS_IMPL_ATTR */
    return (mmuEntryTableFree (pPgTbl, pTable, MMU_L4_TBL_SIZE));
#endif /* _WRS_MMU_USES_OS_IMPL_ATTR */
    }
#endif /* _WRS_MMU_FOUR_LEVEL_PT */

/*******************************************************************************
*
* mmuTlbInvalidate -
*/

_WRS_INLINE void mmuTlbInvalidate
    (
    VIRT_ADDR    virtAddr,
    size_t       entrySize,
    MMU_CTX_ID   ctxId,
    size_t       count
    )
    {

    /* before MMU translation is enabled there is nothing to be done */

    if (!mmuIsEnabled)
        return;

    (void) taskCpuLock ();

#if defined (_WRS_CONFIG_SMP) && defined (_WRS_MMU_SW_TLB_COHERENCY)
    mmuTlbInvalidateCpcInvoke (virtAddr, entrySize, ctxId, count);
#endif

    for ( ; count > 0; count--)
        {
        mmuTlbInvalidateEntry (virtAddr, entrySize, ctxId);
        virtAddr += entrySize;
        }

    (void) taskCpuUnlock ();

    }

#ifdef _WRS_MMU_HAS_STATIC_MAP_INFO
/******************************************************************************
*
* mmuStaticMapInfoAdd - add and entry to the static mapping information
*
* This routine enters information about a
*
* RETURNS: OK, or ERROR if the static map info table is full.
*
* \NOMANUAL
*/

_WRS_INLINE STATUS mmuStaticMapInfoAdd
    (
    VIRT_ADDR        virtAddr,    /* virtual address */
    size_t           length,      /* block length */
    PHYS_ADDR        physAddr,    /* physical address */
    MMU_ARCH_ATTR    mmuAttr      /* MMU attributes */
    )
    {
    if (staticMapCount == _MMU_STATIC_MAP_ENTRY_COUNT)
        return (ERROR);

    staticMapInfo[staticMapCount].virtAddr = virtAddr;
    staticMapInfo[staticMapCount].size = length;
    staticMapInfo[staticMapCount].physAddr = physAddr;
    staticMapInfo[staticMapCount].mmuAttr = mmuAttr;

    staticMapCount++;

    return (OK);
    }
#endif /* _WRS_MMU_HAS_STATIC_MAP_INFO */

#ifdef __cplusplus
    }
#endif

#endif /* __INCmmuLibSPh */
