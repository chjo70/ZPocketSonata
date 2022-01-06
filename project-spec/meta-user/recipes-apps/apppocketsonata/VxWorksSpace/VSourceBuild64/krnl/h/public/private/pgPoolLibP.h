/* pgPoolLibP.h - page pool library private header file */

/* 
 * Copyright (c) 1995-2006, 2009-2010, 2013-2015 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
13may15,pcs  Removed dependency of struct page_pool_obj on macro 
             _WRS_PHYS_ADDR_IS_64_BITS.
26jan15,pcs  CERT: Removed pgPoolFree and added macros PAGE_POOL_DELETE and
             PAGE_POOL_DELETE_IGNORE_RETURN to consolidate the CERT code
             changes.
16sep14,prk  CERT: Removed pgPoolDelete
16jun14,pcs  CERT: Added cert related errno.
12nov13,pcs  Fixed build failure on arches that uses 32-bit physical address
             (WIND00438914).
29apr10,pad  Moved extern C statement after include statements.
18sep09,zl   use fully qualified function pointer for PAGE_POOL_RANGE_EACH.
31aug09,zl   made state and option bits unsigned
17jun09,zl   updated for LP64 build
05jul06,zl   code inspection changes.
21jul05,zl   rewrite of pgPoolLib.
03jun05,yvp  Added #ifndef	_ASMLANGUAGE. 
             Updated copyright. #include now with angle-brackets.
28sep04,tam  changed ADDR type to unsigned int
13sep04,zl   error status code cleanup
14may04,pcs  Rearrange values of PG_POOL_OPT_PHYS_XXX due to rearranging
             of PAGE_MGR_ATTR_POOL_XXX values.
03dec03,yp   adding NO_ACTION ERROR flag
26nov03,zl   renamed avlLib to avlUintLib
29nov03,yp   moving ADDR from vxTypesOld.h to here
18nov03,yp   adding error code VM_NOT_INITIALIZED
20oct03,zl   updated for new avlLib API
08jul03,yp   merged from AE pgPoolLib.h and pgPoolLibP.h
*/

#ifndef __INCpgPoolLibPh
#define __INCpgPoolLibPh

#include <vxWorks.h>
#include <private/semLibP.h>
#include <avlUintLib.h>

#ifdef __cplusplus
extern "C" {
#endif


/* defines */

/* 
 * the following definitions are used in two ways: they represent the current
 * state (allocated or free) of a page in the pool; second they are used
 * to describe the type of operation to be performed on the pages.
 */

#define PAGES_ALLOCATED		1U
#define PAGES_FREE		2U
#define PAGES_REMOVE		3U

#define PG_POOL_OPT_TYPE_PHYS	0x00000001U	/* physical address space */
#define PG_POOL_OPT_TYPE_VIRT	0x00000002U	/* virtual address space */
#define PG_POOL_OPT_TYPE_MASK	0x00000003U	/* pool type mask */

#define PG_POOL_OPT_ALLOCATED	0x00000004U	/* pool object is allocated */

/* status codes */

#define	S_pgPoolLib_INVALID_PAGE_SIZE		(M_pgPoolLib | 1)
#define	S_pgPoolLib_INVALID_PAGE_COUNT		(M_pgPoolLib | 2)
#define S_pgPoolLib_INVALID_ALIGNMENT		(M_pgPoolLib | 3)
#define S_pgPoolLib_NOT_ENOUGH_FREE_PAGES	(M_pgPoolLib | 4)
#define S_pgPoolLib_PAGE_RANGE_OUT_OF_POOL	(M_pgPoolLib | 5)
#define S_pgPoolLib_PAGE_OVERLAP		(M_pgPoolLib | 6)
#define S_pgPoolLib_PAGES_NOT_FREE		(M_pgPoolLib | 7)
#define S_pgPoolLib_PAGES_NOT_ALLOCATED		(M_pgPoolLib | 8)
#define S_pgPoolLib_INVALID_POOL_TYPE		(M_pgPoolLib | 9)
#define S_pgPoolLib_INVALID_STATE		(M_pgPoolLib | 10)
#define S_pgPoolLib_ALLOC_ERROR_NO_ALLOC_SET    (M_pgPoolLib | 11)

#ifndef	_ASMLANGUAGE

#define PAGE_POOL_LOCK(poolId)		semTake (&(poolId)->sem, WAIT_FOREVER)
#define PAGE_POOL_UNLOCK(poolId)	semGive (&(poolId)->sem)

#ifdef _WRS_CONFIG_CERT
#define PAGE_POOL_DELETE(pgPoolId) 
#else
#define PAGE_POOL_DELETE(pgPoolId) pgPoolDelete (pgPoolId)
#endif

/* typedefs */

typedef unsigned int PG_POOL_OPT;

/* 
 * the next and prev fields in PAGE_POOL_ADDR_NODE must match the locations of
 * the first and last fields in PAGE_POOL_FREE_SIZE_NODE.
 */

typedef struct pgPoolAddrNode
    {
    AVLU_NODE			avlPgNum;	/* AVL sorted by pgNum */
    struct pgPoolAddrNode *     next;		/* next in free list, if free */
    struct pgPoolAddrNode *     prev;		/* prev in free list, if free */
    UINT			state;		/* state of block */
    UINT			numPages;	/* size of block */
    } PAGE_POOL_ADDR_NODE;

typedef struct pgPoolFreeSizeNode
    {     
    AVLU_NODE			avlSize;	/* AVL tree sorted by size */
    struct pgPoolAddrNode *     first;		/* first in free list */
    struct pgPoolAddrNode *     last;		/* last in free list */
    } PAGE_POOL_FREE_SIZE_NODE;

 
typedef struct page_pool_obj			/* PAGE_POOL_OBJ */
    {
    size_t			pageSize;	/* page size of the pool */
    SEMAPHORE			sem;		/* page pool semaphore */
    union 
	{
	PHYS_ADDR		p;
	VIRT_ADDR		v;
	} baseAddr;				/* base addres of the pool */
    union 
	{
	PHYS_ADDR		p;
	VIRT_ADDR		v;
	} addrMask;				/* mask to verify range */
    PG_POOL_OPT			options;	/* pool options */
    UINT			pgNumShift;	/* shift to translate address */
						/* to/from pgNum */
    UINT			numPages;	/* size of pool in pages */
    UINT			numFreePages;	/* free pages in pool */
    AVLU_TREE			pgNumTree;	/* tree sorted by page number */
    AVLU_TREE			sizeTree;	/* size-sorted AVL tree */
    } PAGE_POOL_OBJ;

/* page pool information/statistics structure */

typedef struct pgPoolInfo
    {
    size_t			pageSize;	/* size of a page in bytes */

    PG_POOL_OPT			options;	/* options of the page pool */
    UINT			numPages;	/* pages in the page pool */
    UINT			numFreePages;	/* free pages in pool */
    UINT			maxContigPages;	/* pages in the largest */
						/* contiguous free block */
    }  PAGE_POOL_INFO;

typedef struct pgPoolRangeEach
    {
    PAGE_POOL_ID		poolId;		/* page pool ID */
    UINT			stateMask;	/* page alloc state */
    union
        {
	STATUS (*p)				/* for physical page pools */
	    (
	    PHYS_ADDR physAddr, 
	    size_t numPages, 
	    UINT state, 
	    void * pArg
	    );
	STATUS (*v)				/* for virtual page pools */
	    (
	    VIRT_ADDR virtAddr, 
	    size_t numPages, 
	    UINT state, 
	    void * pArg
	    );
        } usrRtn;				/* user routine */
    void *			pArg;		/* user routine argument */
    } PAGE_POOL_RANGE_EACH;

/* function declarations */

extern STATUS	pgPoolLibInit (void);
extern STATUS	pgPoolShowInit(void);
extern PAGE_POOL_ID pgPoolCreate (size_t pageSize, PG_POOL_OPT options);
extern PAGE_POOL_ID pgPoolInit (PAGE_POOL_OBJ * pPool, size_t pageSize,
				PG_POOL_OPT options);
#ifndef _WRS_CONFIG_CERT
extern STATUS	pgPoolDelete (PAGE_POOL_ID);
extern STATUS	pgPoolFree (PAGE_POOL_ID pgPoolId, UINT startPage,
			    UINT numPages);
extern STATUS	pgPoolInfoGet (PAGE_POOL_ID pgPoolId, PAGE_POOL_INFO * pInfo);
extern STATUS	pgPoolBlockListShow (PAGE_POOL_ID pgPoolId, UINT stateMask);
extern STATUS	pgPoolShow (PAGE_POOL_ID pgPoolId, UINT verbose);
extern STATUS	pgPoolRemoveFromPool (PAGE_POOL_ID  pgPoolId, UINT startPage, 
				      UINT numPages);
#endif /* _WRS_CONFIG_CERT */
extern STATUS	pgPoolAddToPool (PAGE_POOL_ID pgPoolId, UINT startPage,
				 UINT numPages, UINT state);
extern UINT	pgPoolAvailAlloc (PAGE_POOL_ID pgPoolId, UINT numPagesReq,
				  UINT * pNumPagesGot);
extern UINT	pgPoolAlignedAlloc (PAGE_POOL_ID pgPoolId, UINT numPages,
				      UINT alignment);
extern UINT	pgPoolAllocAt (PAGE_POOL_ID pgPoolId, UINT startPage,
			       UINT numPages);
extern BOOL	pgPoolRangeVerify (PAGE_POOL_ID pgPoolId, UINT startPage,
				   UINT numPages);
extern BOOL	pgPoolRangeStateCheck (PAGE_POOL_ID poolId, UINT startAddr,
				       UINT numPages, UINT allocOrFree);
extern STATUS	pgPoolNextFreeGet (PAGE_POOL_ID pgPoolId, UINT pgNum, 
				   UINT * pPgNumFree, UINT * pNumPages);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCpgPoolLibPh */
