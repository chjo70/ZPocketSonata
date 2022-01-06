/* mmuTblBuddyHeapSP.h -  */

/*
 * Copyright (c) 2012, 2015, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
13sep16,h_k  added 32KB support to mmuTblHeapAlloc() and mmuTblHeapFree().
             (V7PRO-3268)
03sep15,zl   fixed mmuTblHeapBlockFree. General cleanup.
27apr15,j_l  Initial modifications for IA 32 bit GEN2 support
20mar15,ylu  updated for PPC32 (F2518)
16mar15,w_x  Integrated to VxWorks 7 with update for PPC64 (F2518)
28jan04,zl   created
*/

#ifndef __INCmmuTblBuddyHeapSPh
#define __INCmmuTblBuddyHeapSPh

#include <vxWorks.h>
#include <dllLib.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void * mmuTblHeapBlockAlloc (size_t size, size_t align,
                                    unsigned long * pAllocId);
extern STATUS mmuTblHeapBlockAttrSet (VIRT_ADDR addr, size_t numPages,
                                      unsigned long allocId,
                                      MMU_ARCH_ATTR * pSavedAttr);
extern STATUS mmuTblHeapBlockFree (void * pBlock, size_t size,
                                   unsigned long allocId,
                                   MMU_ARCH_ATTR savedAttr);

#define ADDR_ADD(ptr,off)	((void *) ((char *) (ptr) + (ULONG) (off)))
#define ADDR_DIFF(ptr1, ptr2)	((UINT32) ((char *) (ptr1) - (char *) (ptr2)))
#define ADDR_ROUND_DOWN(p,sz)	((void *) ((long) (p) & ~(sz - 1)))

#define SIZE64K			(64 * 1024)
#define SIZE32K			(32 * 1024)
#define SIZE16K			(16 * 1024)
#define SIZE4K			(4 * 1024)
#define SIZE1K			(1024)
#define SIZE256			(256)

#define MAPSZ1K			2	/* 64k / 1k / bits in UINT32 */
#define MAPSZ256 		8 	/* 64k / 256 / bits in UINT32 */

#define BUDDY_CNT		4	/* four buddies */
#define BUDDY_MASK		0xf	/* one bit for each four buddies */
#define BUDDY_SETS		8	/* buddy sets per 32-bit bitmap */

    typedef struct _mmuHeap
    {
        DL_LIST 		list;		/* block list head */
    } _MMU_TBL_HEAP;

    typedef struct _mmuHeapNode
    {
        DL_NODE		node;			/* block list node */
        void *		pBlock;			/* block address */
        unsigned long	allocId;		/* identify source of block */
        MMU_ARCH_ATTR	savedAttr;		/* heap attributes */
        UINT32		map16k;			/* uses 4 bits (64k / 16k) */
        UINT32		map4k;			/* uses 16 bits (64k / 4k) */
        UINT32		map1k[MAPSZ1K];		/* uses 64 bits (64k / 1k) */
        UINT32		map256[MAPSZ256];	/* uses 256 bits (64k / 256) */
    } _MMU_HEAP_NODE;

/*******************************************************************************
*
* mmuTblHeapInit - initialize the page table heap
*
* This function initialize a page table heap.
*
* RETURNS: OK
*/

_WRS_INLINE STATUS mmuTblHeapInit
    (
        _MMU_TBL_HEAP *	pTblHeap
    )
    {
    DLL_INIT (&pTblHeap->list);

    return (OK);
    }

/*******************************************************************************
*
* mmuTblHeapGrow - add a new 64k block to the page table heap
*
* This functions adds a new 64k block to the page table heap when an allocation
* could not be satisfied from the current blocks.
*
* RETURNS: OK on success, or ERROR 
*/

_WRS_INLINE STATUS mmuTblHeapGrow
    (
    _MMU_TBL_HEAP *	pTblHeap
    )
    {
    _MMU_HEAP_NODE *	pNode;
    int			ix;

#ifndef _WRS_CONFIG_COMPAT69_ADR_SPACE
    pNode = kProxHeapAlloc (sizeof (_MMU_HEAP_NODE));
#else
    pNode = KMEM_ALLOC (sizeof (_MMU_HEAP_NODE));
#endif

    if (pNode == NULL)
        {
        return (ERROR);
        }

    /* allocate a 64k block with page alignment */

    pNode->pBlock = mmuTblHeapBlockAlloc (SIZE64K, _MMU_PAGE_SIZE,
                                          &pNode->allocId);

    if (pNode->pBlock == NULL)
        {
#ifndef _WRS_CONFIG_COMPAT69_ADR_SPACE
        (void)kProxHeapFree (pNode->pBlock);
#else
        (void)KMEM_FREE (pNode->pBlock);
#endif
        return (ERROR);
        }

    pNode->savedAttr = 0;

    /*
     * mark the four 16k buddies free, all the smaller block sizes are
     * unavailable without splitting first.
     */

    pNode->map16k   = 0xF;
    pNode->map4k    = 0;
    for (ix = 0; ix < MAPSZ1K; ix++)
	    {
        pNode->map1k[ix] = 0;
        }
    for (ix = 0; ix < MAPSZ256; ix++)
        {
        pNode->map256[ix] = 0;
        }

    DLL_ADD (&pTblHeap->list, &pNode->node);

    /*
     * set protection after block was added; this is to avoid recursion
     * in case we need to de-optimize when setting the attributes.
     */

    return (mmuTblHeapBlockAttrSet ((VIRT_ADDR)pNode->pBlock,
                                    SIZE64K / _MMU_PAGE_SIZE,
                                    pNode->allocId, &pNode->savedAttr));
    }

/*******************************************************************************
*
* mmuTblHeapProtectionEnable - write-protect page tables
*
* This function is used to write protect the page tables allocated prior to
* enabling the dynamic MMU mode; it is called once during bootup from mmuEnable.
*
* RETURNS: OK on success, or ERROR
*/

_WRS_INLINE STATUS mmuTblHeapProtectionEnable
    (
    _MMU_TBL_HEAP *	pTblHeap
    )
    {
    _MMU_HEAP_NODE *	pNode;

    pNode = (_MMU_HEAP_NODE *) DLL_FIRST (&pTblHeap->list);

    while (pNode != NULL)
        {
        /*
         * protect previously allocated blocks; this retrieves previous
         * attribute so it can be restored when the blocks are freed.
         */

        if (mmuTblHeapBlockAttrSet ((VIRT_ADDR)pNode->pBlock, 16,
                                    pNode->allocId,
                                    &pNode->savedAttr) == ERROR)
            {
            return (ERROR);
            }

        pNode = (_MMU_HEAP_NODE *) DLL_NEXT (&pNode->node);
        }

    return (OK);
    }

/*******************************************************************************
*
* mmuTblHeapDelete - delete page table heap
*
* This function deletes a page table heap by freeing all blocks added to it.
*
* RETURNS: OK on success, or ERROR
*/

_WRS_INLINE STATUS mmuTblHeapDelete
    (
    _MMU_TBL_HEAP *	pTblHeap
    )
    {
    STATUS		rVal = OK;
    _MMU_HEAP_NODE *	pNode;

    /* free all blocks previously added to the heap */

    while (TRUE)
        {
        DLL_GET (&pTblHeap->list, pNode);

        if (pNode == NULL)
            {
            break;
            }

        if (mmuTblHeapBlockFree (pNode->pBlock, SIZE64K,
                                 pNode->allocId,
                                 pNode->savedAttr) == ERROR)
            {
            rVal = ERROR;
            }

#ifndef _WRS_CONFIG_COMPAT69_ADR_SPACE
        (void)kProxHeapFree (pNode);
#else
        KMEM_FREE (pNode);
#endif
        }

    return (rVal);
    }

/*******************************************************************************
*
* mmuTblHeapAlloc - allocate page table
*
* This function allocates a page table of requested size from a page table
* heap. Currently it supports 256bytes, 1k, 4k and 16k sizes. Alignemnt
* is implicitly ensured by the allocation method, but it cannot be larger
* than the requieted size.
*
* This function is meant to be called with <size> argument a constant value so
* that the compiler can optimize out unnecesary code paths.
*
* RETURNS: pointer to page table, or NULL
*/

_WRS_INLINE void * mmuTblHeapAlloc
    (
    _MMU_TBL_HEAP *	pTblHeap,
    size_t		size,
    size_t		align
    )
    {
    _MMU_HEAP_NODE *	pNode;
    UINT		ix;
    UINT		bIx;
    UINT		offset;
    UINT		mapIx;
    UINT		bitIx;
    UINT32		buddyMap;

    /* verify supported sizes */

    if ((size != SIZE256) &&
	(size != SIZE1K)  && (size != SIZE4K) &&
	(size != SIZE16K) && (size != SIZE32K))
	{
	return (NULL);
	}

    if (align > size)
	{
	return (NULL);
	}

    pNode = (_MMU_HEAP_NODE *) DLL_FIRST (&pTblHeap->list);

    while (pNode != NULL)
	{
	while (TRUE)
	    {
retry:
	    if (size == SIZE256)
		{
		/* search the 256-byte bitmap for a free page table */

		for (ix = 0; ix < MAPSZ256; ix++)
		    {
		    if (pNode->map256[ix] != 0)
			{
			/* found at least one free */

			bIx = ffsLsb (pNode->map256[ix]) - 1;

			/* pick the first one and mark it unavailable */

			pNode->map256[ix] &= ~(1 << bIx);
			offset = (ix * 32 + bIx) * SIZE256;

			return (ADDR_ADD (pNode->pBlock, offset));
			}
		    }

		/*
		 * we didn't find a free one; we'll search for a bigger one
		 * and split it, then return to start all over.
		 */
		}

	    if (size <= SIZE1K)
		{
		/* search the 1k bitmap for a free page table */

		for (ix = 0; ix < MAPSZ1K; ix++)
		    {
		    if (pNode->map1k[ix] != 0)
			{
			/* found at least one free */

			bIx = ffsLsb (pNode->map1k[ix]) - 1;

			/* pick the first one and mark it unavailable */

			pNode->map1k[ix] &= ~(1 << bIx);

			if (size == SIZE1K)
			    {
			    /* if allocating 1k size, return that block */

			    offset = (ix * 32  + bIx) * SIZE1K;

			    return (ADDR_ADD (pNode->pBlock, offset));
			    }
			else
			    {
			    /*
			     * allocating smaller size; split the 1k entry
			     * into four free 256 bytes entries and restart
			     * allocation.
			     *
			     * this needs to convert from the 1k bitmap
			     * indexes (ix, bIx) to the 256 byte bitmap
			     * indexes (mapIx, bitIx).
			     */

			    mapIx = ix * BUDDY_CNT + bIx / BUDDY_SETS;
			    bitIx = (bIx % BUDDY_SETS) * BUDDY_CNT;
			    buddyMap = BUDDY_MASK << bitIx;

			    pNode->map256[mapIx] |= buddyMap;

			    goto retry;
			    }
			}
		    }
		}

	    if (size <= SIZE4K)
		{
		/* search the 4k bitmap for a free page table */

		if (pNode->map4k != 0)
		    {
		    /* found at least one free */

		    bIx = ffsLsb (pNode->map4k) - 1;

		    /* pick the first one and mark it unavailable */

		    pNode->map4k &= ~(1 << bIx);

		    if (size == SIZE4K)
			{
			/* if allocating 4k size, return that block */

			offset = bIx * SIZE4K;

			return (ADDR_ADD (pNode->pBlock, offset));
			}
		    else
			{
			/*
			 * allocating smaller size, split into four
			 * free 1K entries, and restart allocation.
			 *
			 * this needs to convert from the 4k bitmap
			 * indexes (ix, bIx) to the 1k bitmap indexes
			 * (mapIx, bitIx).
			 */

			mapIx = bIx / BUDDY_SETS;
			bitIx = (bIx % BUDDY_SETS) * BUDDY_CNT;
			buddyMap = BUDDY_MASK << bitIx;

			pNode->map1k[mapIx] |= buddyMap;

			goto retry;
			}
		    }
		}

	    if (pNode->map16k == 0)
		{
		/* 16k map is empty - allocation failed in this 64k block */

		break;
		}

	    /*
	     * at least one 16k block is free; pick the first free one and
	     * mark it unavailbale.
	     */

	    if (size == SIZE32K)
		{
		/* search two contiguous 16k free pages aligned on 32KB */

		if ((pNode->map16k & 0x3) == 0x3)
		    {
		    bIx = 0;
		    }
		else if ((pNode->map16k & 0xc) == 0xc)
		    {
		    bIx = 2;
		    }
		else
		    {
		    break;
		    }

		/* pick the first ones and mark them unavailable */

		pNode->map16k &= ~(3 << bIx);

		/* allocating 32k, return that one */

		offset = bIx * SIZE16K;

		return (ADDR_ADD (pNode->pBlock, offset));
		}
	    else
		{
		/* pick the first one and mark it unavailable */

		bIx = ffsLsb (pNode->map16k) - 1;
		pNode->map16k &= ~(1 << bIx);

		if (size == SIZE16K)
		    {
		    /* allocating 16k, return that one */

		    offset = bIx * SIZE16K;

		    return (ADDR_ADD (pNode->pBlock, offset));
		    }
		else
		    {
		    /*
		     * allocating smaller size; split into four
		     * free 4K entries, and restart allocation.
		     */

		    pNode->map4k |= (BUDDY_MASK << (bIx * BUDDY_CNT));
		    }
		}
	    }

	pNode = (_MMU_HEAP_NODE *) DLL_NEXT (&pNode->node);
	}

    return (NULL);
    }

/*******************************************************************************
*
* mmuTblHeapFree - free a page table in a page table heap
*
* This function marks a page table of requested size free in a page table
* heap. Currently it supports 256bytes, 1k, 4k and 16k sizes.
*
* This function is meant to be called with <size> argument a constant value so
* that the compiler can optimize out unnecesary code paths.
*
* RETURNS: OK on success, or ERROR
*/

_WRS_INLINE STATUS mmuTblHeapFree
    (
    _MMU_TBL_HEAP *	pTblHeap,
    void *		pTbl,
    size_t		size
    )
    {
    int			ix;
    int			bIx;
    UINT32		mask;
    _MMU_HEAP_NODE *	pNode;

    /* search for matching 64k block based on table address */

    pNode = (_MMU_HEAP_NODE *) DLL_FIRST (&pTblHeap->list);

    while (pNode != NULL)
	{
	if ((pTbl >= pNode->pBlock) &&
	    (pTbl < ADDR_ADD (pNode->pBlock, SIZE64K)))
	    {
	    /* found the 64k block that table belongs to */

	    if (size == SIZE256)
		{
		/*
		 * Set the bit(s) in the 256-byte bitmap to indicate it's free.
		 */

		bIx = ADDR_DIFF (pTbl, pNode->pBlock) / SIZE256;
		ix  = bIx / 32;
		bIx = bIx % 32;

		pNode->map256[ix] |= (1 << bIx);

		/* check if the four buddies are all free */

		mask = BUDDY_MASK << ROUND_DOWN (bIx, BUDDY_CNT);

		if ((pNode->map256[ix] & mask) != mask)
		    {
		    /* not all are free, we are done */

		    return (OK);
		    }

		/*
		 * the four buddies are free; replace them with a single 1k
		 * block to be freed, and continue.
		 */

		pNode->map256[ix] &= ~mask;
		pTbl = ADDR_ROUND_DOWN (pTbl, SIZE1K);
		size = SIZE1K;
		}

	    if (size == SIZE1K)
		{
		/* set the bit(s) in the 1k bitmap to indicate it's free */

		bIx = ADDR_DIFF (pTbl, pNode->pBlock) / SIZE1K;
		ix  = bIx / 32;
		bIx = bIx % 32;

		pNode->map1k[ix] |= (1 << bIx);

		/* check if the four buddies are all free */

		mask = BUDDY_MASK << ROUND_DOWN (bIx, BUDDY_CNT);

		if ((pNode->map1k[ix] & mask) != mask)
		    {
		    /* not all are free, we are done */

		    return (OK);
		    }

		/*
		 * the four buddies are free; replace them with a single 4k
		 * block to be freed, and continue.
		 */

		pNode->map1k[ix] &= ~mask;
		pTbl = ADDR_ROUND_DOWN (pTbl, SIZE4K);
		size = SIZE4K;
		}

	    if (size == SIZE4K)
		{
		/* set the bit(s) in the 4k bitmap to indicate it's free */

		bIx = ADDR_DIFF (pTbl, pNode->pBlock) / SIZE4K;

		pNode->map4k |= (1 << bIx);

		/* check if the four buddies are all free */

		mask = BUDDY_MASK << ROUND_DOWN (bIx, BUDDY_CNT);

		if ((pNode->map4k & mask) != mask)
		    {
		    /* not all are free, we are done */

		    return (OK);
		    }

		/*
		 * the four buddies are free; replace them with a single 4k
		 * block to be freed, and continue.
		 */

		pNode->map4k &= ~mask;

		pNode->map16k |= (1 << (bIx / BUDDY_CNT));

		return (OK);
		}

	    if ((size == SIZE16K) || (size == SIZE32K))
		{
		/* mark the 16k block(s) free */

		bIx = ADDR_DIFF (pTbl, pNode->pBlock) / SIZE16K;

		if (size == SIZE32K)
		    {
		    pNode->map16k |= (3 << bIx);
		    }
		else
		    {
		    pNode->map16k |= (1 << bIx);
		    }

		return (OK);
		}

	    /* unsupported size */

	    return (ERROR);
	    }

	pNode = (_MMU_HEAP_NODE *) DLL_NEXT (&pNode->node);
	}

    return (ERROR);
    }

#ifdef __cplusplus
}
#endif

#endif /* __INCmmuTblBuddyHeapSPh */
