/* memPartLibP.h - private memory management library header file */

/*
 * Copyright (c) 1992, 1996, 2001, 2003-2010, 2013-2015, 2017
 * Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */


/*
modification history
--------------------
26aug17,dlk  added memSysPartCouldBeOwner() (V7COR-5296)
20may15,zl   resource allocation control support for non-CERT (F788)
10feb15,cww  added _func_resAllocRequest and _func_resAllocDealloc (V7COR-2561)
05nov14,cww  fix static analysis issues
01oct14,jpb  V7COR-1690: removed fix me comment
12sep14,rgo  CERT: update two prototypes
29aug14,rgo  CERT: Fixed flex Elint Errors and apply coding std.
26jun14,pcs  CERT: Added external declaration for memAllocDisabled
25nov13,pcs  changes corresponding to MMU-less kernel support.
02aug13,pcs  updated to use config option _WRS_CONFIG_COMPAT69_ADR_SPACE
08jul13,pcs  Fix macro GET_ALLOC_STATE.
08jul13,pcs  Code review changes.
23may13,pcs  Fix macro CLEAR_ALLOC_STATE.
03may13,pcs  Add support for SMP-optimized memory allocator.
11nov10,pcs  Make headGuard configurable for LP64.
01nov10,pcs  Fix typo in previous checkin.
26oct10,jpb  Fixed type-casting in macro MAX_ALLOWED_ALLOC_SIZE
21oct10,pcs  add a macro MAX_ALLOWED_ALLOC_SIZE to represent the maximum
             allowed/possible single allocation in LP64.
30sep10,pcs  Change the typecase of the return value of macro
             BLOCK_END_GUARD from (ULONG *) to (UINT *)
27jul10,pcs  Fix issue with macro BLOCK_END_GUARD.
17feb10,pch  small footprint
13may10,cww  64-bit SMP update
19apr10,jpb  Added function pointers.
31mar10,pcs  typecast the return value of macro BYTE_SIZE_TO_SIZE to
	     UINT32.
30mar10,pad  Moved declaration of extern C block for C++ after the
	     inclusion of header files.
04nov09,pcs  Updated to reflect the name changes to the 64bit heaps.
24sep09,pcs  Add support for heap growth in 64bit vxWorks.
08sep09,pcs  Updated to add support for multiple heaps for 64bit vxWorks.
31may09,dlk  Fix GET_SIZE and GET_SIZE_IN_BYTES for LP64 case.
06may09,pcs  Updated macro NEXT_CHUNK_HDR to properly use paranthesis.
30apr09,pcs  Update macros to use paranthesis around parameters.
24mar09,pcs  Updated to add support for the LP64 data model.
14apr09,zl   partial 64-bit updates.
13aug09,gls  revamped refCnt (WIND00166706)
27aug08,jpb  Renamed VSB header file
18jun08,jpb  Added include path for kernel configurations options set in vsb.
08may08,jpb  Modifications for source build.  Renamed INCLUDE_MEM_ALLOT
	     to _WRS_CONFIG_MEM_ALLOT, _WRS_VX_SMP to _WRS_CONFIG_SMP.
05feb07,pcs  Add refCnt support for SMP.
08jan07,jmg  Added _func_memRealloc (Req WIND0008666).
16jun06,zl   added memPartFreeListWalk()
27sep05,zl   added ED&R option bits to MEM_OPTIONS_MASK.
09aug05,zl   use semMTake() and semMGive() in the lock/unlock macros.
26jul05,mil  Added prototype for memAllotLibInit.
12jul05,mil  Added memAllot support to minimal kernel.
14apr05,zl   changed CHUNK_MIN_SIZE to larger minimum block
16feb05,aeg  added memBlockSizeGet() function prototype (SPR #106381).
03may04,zl   made cumWordsAllocated 64-bit, removed minBlockWords.
03feb04,zl   added allocated block guard signature support.
03nov03,zl   added create, delete, alloc, free, realloc hooks.
20oct03,zl   updated for new avlLib API.
27jun03,tam  merge with latest VxWorks AE version
14mar03,pch  runtime sizing of BLOCK_HDR for PPC32
23oct01,tam  re-organized FREE_BLOCK
19oct01,tam  added definition for KMEM_XXX macros
25sep01,tam  added definition of the KHEAP_XXX macros
19aug96,dbt  removed memPartAlignedAlloc prototype (fixed SPR #6898).
05aug96,kkk  made padding in BLOCK_HDR generic to all arch with alignment
	     at 16.
22sep92,rrr  added support for c++
28jul92,jcf  added external declaration for memPartOptionsDefault.
19jul92,pme  added external declarations for sm partition functions.
01jul92,jcf  extracted from memLib v3r.
*/

#ifndef __INCmemPartLibPh
#define __INCmemPartLibPh

#include <vxWorks.h>
#include <vsbConfig.h>
#include <vwModNum.h>
#include <memLib.h>
#include <sllLib.h>
#include <avlUintLib.h>
#include <private/semLibP.h>
#include <classLib.h>
#include <private/objLibP.h>
#include <private/kernelLibP.h>
#include <vxAtomicLib.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/*
 * Kernel memory allocation macros (KHEAP and KMEM macros)
 *
 * NOTE: They should not be used by any application code.
 * It is also needed by code being back-ported from VxWorks AE 1.x. to VxWorks
 * 5.5.x.
 */

/*
 * KHEAP macros:
 *
 *	*******************************************************
 *	*******************************************************
 *	*** The KHEAP macros are deprecated in VxWorks 6.x. ***
 *	*** Use the KMEM macros instead.                    ***
 *	*******************************************************
 *	*******************************************************
 *
 * These macros are defined simply for cosmetic reasons, to make it more
 * obvious that buffers are allocated or freed from the kernel heap, also
 * called the system memory partition.
 * No guaranty is given that the buffer allocated from the Kernel
 * Heap via KHEAP_ALLOC has a known and constant virtual to physical mapping
 * (1 to 1 mapping for instance) if virtual memory support is included (i.e.
 * INCLUDE_MMU_BASIC or INCLUDE_MMU_FULL components).
 *
 * NOTE: with the exception of KHEAP_REALLOC(), the definitions are based
 *       on API from memPartLib.c, to prevent any requirements on
 *       INCLUDE_MEM_MGR_FULL (memLib.c).
 */

#define KHEAP_ALLOC(nBytes)						\
	memPartAlloc(memSysPartId, (nBytes))
#define KHEAP_FREE(pChar)						\
	memPartFree(memSysPartId, (char *)(pChar))
#define KHEAP_ALIGNED_ALLOC(nBytes, alignment)				\
	memPartAlignedAlloc(memSysPartId, (nBytes), (alignment))
#define KHEAP_REALLOC(pChar, newSize)					\
	memPartRealloc(memSysPartId, (pChar), (newSize))

/*
 * KMEM macros:
 * If a known and constant virtual to physical mapping is required for
 * buffer allocated, KMEM macros should be used instead of KHEAP macros.
 * For instance memory block dynamically allocated that may be accessed when
 * the processor MMU is turned off or on should always be allocated using
 * KMEM_ALLOC() or KMEM_ALIGNED_ALLOC(). Good examples are memory blocks used
 * to store MMU translation information on some processors, or memory blocks
 * accessed by DMA devices.
 *
 * NOTE: With VxWorks 5.5.x, there's no differences between KHEAP_XXX and
 * KMEM_XXX macros. However this will change in future releases.
 */

#ifdef _WRS_CONFIG_MEM_ALLOT

/* minimal kernel definitions, KMEM_FREE is not available */

#define KMEM_ALLOC(nBytes)                                              \
	memAllot((nBytes), 0)
#define KMEM_ALIGNED_ALLOC(nBytes, alignment)                           \
	memAllot((nBytes), (alignment))

extern void * memAllot (unsigned size, unsigned alignment);
extern STATUS memAllotLibInit (char * pPool, unsigned poolSize);

#else /* _WRS_CONFIG_MEM_ALLOT */

#define KMEM_ALLOC(nBytes)                                              \
	memPartAlloc(memSysPartId, (nBytes))
#define KMEM_FREE(pChar)                                                \
	memPartFree(memSysPartId, (pChar))
#define KMEM_ALIGNED_ALLOC(nBytes, alignment)                           \
	memPartAlignedAlloc(memSysPartId, (nBytes), (alignment))
#endif  /* _WRS_CONFIG_MEM_ALLOT */


/*
 * For PowerPC, _ALLOC_ALIGN_SIZE is a variable whose runtime value is not
 * known when compiling generic code (i.e. with CPU=PPC32), so the conditional
 * padding in the ALLOC_CHUNK_HDR and MEM_SECTION_HDR definitions does not work.
 * The folowing definitions are based on the size of ALLOC_CHUNK_HDR being 16,
 * and the size of MEM_SECTION_HDR being 8.
 * NOTE: The assembly code will be slightly longer for PowerPC CPUs than
 * for architectures for which _ALLOC_ALIGN_SIZE value can be resolved by the
 * processor.
 */

extern UINT allocChunkEndGuardSize;
#ifdef _WRS_CONFIG_LP64
extern UINT allocChunkHeadGuardSize;
#define ALLOC_CHUNK_HDR_SIZE	(sizeof(ALLOC_CHUNK_HDR) + \
                                 allocChunkHeadGuardSize)
#else
#define ALLOC_CHUNK_HDR_SIZE	sizeof(ALLOC_CHUNK_HDR)
#endif
#define MEM_SECTION_HDR_SIZE	max(_ALLOC_ALIGN_SIZE, sizeof(MEM_SECTION_HDR))


#define PREV_CHUNK_IS_FREE	1U
#define CHUNK_SIZE_MASK 	(~(PREV_CHUNK_IS_FREE))

#define ALLOC_STATE_HEAP_ALLOC		0
#define ALLOC_STATE_MEM_CACHE_ALLOC	1
#define ALLOC_STATE_MEM_CACHE_FREE	2
#define ALLOC_STATE_MASK 		(3)

#define GET_ALLOC_STATE(blkHdr)         ((ULONG)((blkHdr)->memPartId) & \
                                         (ALLOC_STATE_MASK))
#define IS_ALLOC_STATE_MEM_CACHE_ALLOC(blkHdr) \
    (((ULONG)((ALLOC_CHUNK_HDR *)blkHdr)->memPartId == \
    ((ULONG)ALLOC_STATE_MEM_CACHE_ALLOC | (ULONG)memSysPartId)) ? TRUE : FALSE)

#define IS_ALLOC_STATE_MEM_CACHE_FREE(blkHdr) \
    (((ULONG)((ALLOC_CHUNK_HDR *)blkHdr)->memPartId == \
    ((ULONG)ALLOC_STATE_MEM_CACHE_FREE | (ULONG)memSysPartId)) ? TRUE : FALSE)

#define SET_ALLOC_STATE_MEM_CACHE_ALLOC(blkHdr) \
    ((((ALLOC_CHUNK_HDR *)blkHdr)->memPartId) = \
    ((PART_ID)(((ULONG)(((ALLOC_CHUNK_HDR *)blkHdr)->memPartId) & \
    ~ALLOC_STATE_MASK) | ALLOC_STATE_MEM_CACHE_ALLOC)))

#define SET_ALLOC_STATE_MEM_CACHE_FREE(blkHdr) \
    ((((ALLOC_CHUNK_HDR *)blkHdr)->memPartId) = \
    ((PART_ID)(((ULONG)(((ALLOC_CHUNK_HDR *)blkHdr)->memPartId) & \
    ~ALLOC_STATE_MASK) | ALLOC_STATE_MEM_CACHE_FREE)))

#define CLEAR_ALLOC_STATE(blkHdr) \
    ((((ALLOC_CHUNK_HDR *)blkHdr)->memPartId) = \
     ((PART_ID)(((ULONG)(blkHdr)->memPartId) & ~ALLOC_STATE_MASK)))

#define GET_MEM_PART_ID(blkHdr) \
    ((PART_ID)((ULONG)(((ALLOC_CHUNK_HDR *)blkHdr)->memPartId) & \
    (~ALLOC_STATE_MASK)))

#ifndef _WRS_CONFIG_LP64
#define BYTE_SIZE_TO_SIZE(blkSize)   (blkSize)
#define SIZE_TO_BYTE_SIZE(blkSize)   (blkSize)
#else	/* _WRS_CONFIG_LP64 */
#define SIZE_SHIFT 2
#define BYTE_SIZE_TO_SIZE(blkSize) ((UINT32)((ULONG)(blkSize) >> SIZE_SHIFT))
#define SIZE_TO_BYTE_SIZE(blkSize) ((ULONG)((ULONG)(blkSize) << SIZE_SHIFT))
#define MAX_ALLOWED_ALLOC_SIZE    (((size_t)(-1U) << SIZE_SHIFT))
#endif	/* _WRS_CONFIG_LP64 */

#define GET_SIZE(blkHdr)           ((blkHdr)->size & CHUNK_SIZE_MASK)
#define GET_SIZE_IN_BYTES(blkHdr) \
    (SIZE_TO_BYTE_SIZE((blkHdr)->size & CHUNK_SIZE_MASK))
#define IS_PREV_CHUNK_FREE(blkHdr) \
    (((blkHdr)->size & PREV_CHUNK_IS_FREE) ? TRUE : FALSE)


/* macros for getting to next and previous blocks */

#define NEXT_CHUNK_HDR(pHdr)	((FREE_CHUNK_HDR *) (((ULONG) (pHdr)) +    \
				 (SIZE_TO_BYTE_SIZE((pHdr)->size & \
				  CHUNK_SIZE_MASK))))
#define PREV_CHUNK_HDR(pHdr)	((FREE_CHUNK_HDR *) (((ULONG) (pHdr)) -    \
					(SIZE_TO_BYTE_SIZE((pHdr)->prevSize))))


/*
 * macros for converting between the "block" that caller knows
 * (actual available data area) and the chunk header in front of it
 * The memory chunck is the header plus the data block.
 */

#define BLOCK_TO_CHUNK_HDR(pBlock) ((ALLOC_CHUNK_HDR *) (((ULONG) (pBlock)) - \
						ALLOC_CHUNK_HDR_SIZE))
#define CHUNK_HDR_TO_BLOCK(pHdr)   ((char *) (((ULONG) (pHdr)) + 	      \
						ALLOC_CHUNK_HDR_SIZE))


/* macro to get to head guard */

#ifdef _WRS_CONFIG_LP64
#define BLOCK_HEAD_GUARD(pHdr)	((ULONG *) (((ULONG) (pHdr)) + \
                                            sizeof(ALLOC_CHUNK_HDR)))
#else
#define BLOCK_HEAD_GUARD(pHdr)	((&pHdr->headGuard))
#endif


/* macro to get to end guard */

#define BLOCK_END_GUARD(pHdr)	((ULONG *) (((ULONG) (pHdr)) +    \
					   ((SIZE_TO_BYTE_SIZE((pHdr)->size \
					   & CHUNK_SIZE_MASK)) - \
					   allocChunkEndGuardSize)))

/*
 * optimized version of NEXT_CHUNK_HDR for cases where we know that
 * the current block is free (so the previous one can not be free !)
 */

#define NEXT_CHUNK_HDR_FREE(pHdr) ((CHUNK_HDR *) (((ULONG) (pHdr)) + 	\
					  (SIZE_TO_BYTE_SIZE((pHdr)->size))))


/* overhead of allocated, free chunks and region */

#define CHUNK_ALLOC_OVERHEAD 	(ALLOC_CHUNK_HDR_SIZE + allocChunkEndGuardSize)
#define CHUNK_FREE_OVERHEAD 	(sizeof(FREE_CHUNK_HDR))
#define MEM_SECTION_OVERHEAD 	(MEM_SECTION_HDR_SIZE)
#define MIN_BLOCK_WORDS		((CHUNK_FREE_OVERHEAD) >> 1)

/*
 * minimum meaningful size for a chunk. This is due to the fact that:
 *	- any allocted chunk must be convertible into a free chunk eventually.
 *	- a free chunk should accomodate allocation of at least 16 bytes to
 *        avoid creation of very small free blocks that could cause
 *        fragmentation.
 */

#define CHUNK_MIN_SIZE 		(max (CHUNK_FREE_OVERHEAD, 	\
				      CHUNK_ALLOC_OVERHEAD + MEM_ROUND_UP(16)))

/*
 * minimum size of a memory region added via memPartAddToPool. This is due to
 * the fact that any region has to host at least 3 allocated blocks of size 0
 * plus a free block of size 0 plus a region header. Assume worst case with
 * end guards enabled.
 */

#define REGION_START_OVERHEAD	(MEM_SECTION_OVERHEAD + ALLOC_CHUNK_HDR_SIZE + \
				 (END_GUARD_WORDS * sizeof (ULONG)) + \
				 CHUNK_FREE_OVERHEAD)
#define REGION_END_OVERHEAD	(2 * (ALLOC_CHUNK_HDR_SIZE + \
				      (END_GUARD_WORDS * sizeof (ULONG))))

#define REGION_MIN_SIZE		(REGION_START_OVERHEAD + REGION_END_OVERHEAD)

/*
 * actual size of the data block within an allocated chunck, retrieved from
 * the chunk header address (BLOCK_SIZE) or the buffer address (MEM_BLOCK_SIZE)
 */

#define	BLOCK_SIZE(pHdr) ((SIZE_TO_BYTE_SIZE((pHdr)->size & CHUNK_SIZE_MASK))- \
				 CHUNK_ALLOC_OVERHEAD)
#define	MEM_BLOCK_SIZE(pBlock)	memBlockSizeGet((void *)(pBlock))

#define	MEM_PART_SHOW_LOG_LVL_1	1 /* memPartShow: display numbers of free    */
				  /* blocks of a given size                  */
#define	MEM_PART_SHOW_LOG_LVL_2	2 /* memPartShow: display numbers of free    */
				  /* blocks of a given size plus the address */
				  /* of each free block                      */

#define SIZE_NODE_MIN_NB	4	/* minimum number of available bin  */
					/* size nodes at any time           */
#define SIZE_NODE_INIT_NB	8	/* number of available bin at the   */
					/* creation of the partition should */
					/* NOT be LESS than                 */
					/* SIZE_NODE_MIN_NB                 */
#define SIZE_NODE_DEFAULT_NB	8	/* number of bin size nodes         */
					/* allocated at a time by default   */

/* partition option mask */

#define MEM_OPTIONS_MASK (MEM_BLOCK_CHECK |			\
			  MEM_ALLOC_ERROR_EDR_FATAL_FLAG |	\
			  MEM_ALLOC_ERROR_EDR_WARN_FLAG |	\
			  MEM_ALLOC_ERROR_LOG_FLAG | 		\
			  MEM_ALLOC_ERROR_SUSPEND_FLAG |	\
			  MEM_BLOCK_ERROR_EDR_FATAL_FLAG |	\
			  MEM_BLOCK_ERROR_EDR_WARN_FLAG |	\
			  MEM_BLOCK_ERROR_LOG_FLAG |		\
			  MEM_BLOCK_ERROR_SUSPEND_FLAG |	\
			  MEM_ALLOC_ERROR_MASK |		\
			  MEM_BLOCK_ERROR_MASK)


/* pattern to fill guard zones */

#ifdef _WRS_CONFIG_LP64
#define GUARD_PATTERN			0xa110cb1ca110cb1c
#else
#define GUARD_PATTERN			0xa110cb1c
#endif
#define END_GUARD_WORDS			4
#ifdef _WRS_CONFIG_LP64
#define HEAD_GUARD_WORDS		2
#endif
/* for memPartFreeListWalk() */

#define MEM_WALK_UP		0
#define MEM_WALK_DOWN		1


#ifndef _ASMLANGUAGE

#ifdef _WRS_CONFIG_SMP
#define TYPE_1_SPIN_LOCK

#ifdef TYPE_1_SPIN_LOCK

extern spinlockIsr_t memPartClassLock;
#define MEM_PART_SPIN_LOCK_TAKE(lock)				\
	    SPIN_LOCK_ISR_TAKE (lock)

#define MEM_PART_SPIN_LOCK_GIVE(lock)				\
	    SPIN_LOCK_ISR_GIVE (lock)

#else	/* TYPE_1_SPIN_LOCK */

extern spinlockTask_t memPartClassLock;
#define MEM_PART_SPIN_LOCK_TAKE(lock)				\
	    SPIN_LOCK_TASK_TAKE (lock)

#define MEM_PART_SPIN_LOCK_GIVE(lock)				\
	    SPIN_LOCK_TASK_GIVE (lock)

#endif	/* TYPE_1_SPIN_LOCK */

#endif	/* _WRS_CONFIG_SMP */

#ifdef	_WRS_CONFIG_SMP
/* Note: REF_CNT_INC needs to be called with the spinlock taken. */
#define REF_CNT_INC(partId)					\
                (void) vxAtomic32Inc (&partId->refCnt)
#else	/* _WRS_CONFIG_SMP */
#define REF_CNT_INC(partId)
#endif	/* _WRS_CONFIG_SMP */


#ifdef	_WRS_CONFIG_SMP
/*
 * Reference counting mechanism is not implemented for
 * system memory partition (kernel heap), since the system
 * memory partion cannot be deleted.
 */

#define REF_CNT_DEC(partId)					\
                vxAtomic32Dec (&partId->refCnt)
#else	/* _WRS_CONFIG_SMP */
#define REF_CNT_DEC(partId)
#endif	/* _WRS_CONFIG_SMP */


#define MEM_PART_ID_VERIFY(partId)				\
		(((partId) == NULL) ? ERROR :			\
		 OBJ_VERIFY ((partId), memPartClassId))
#define MEM_PART_INVALIDATE(partId)				\
		objCoreInvalidate (&(partId)->objCore)

#define MEM_PART_LOCK(partId)					\
		semMTake (&(partId)->sem, WAIT_FOREVER)
#define MEM_PART_VERIFIED_LOCK(partId)				\
		memPartVerifiedLock(partId)
#define MEM_PART_UNLOCK(partId)					\
		(void) semMGive (&(partId)->sem)

/* typedefs */

typedef void * (*FUNC_ALLOC) (PART_ID partId, size_t nBytes,
			      size_t alignment);
typedef STATUS (*FUNC_FREE) (PART_ID partId, char * pBlk);
typedef void * (*FUNC_REALLOC)		(PART_ID partId, char * pBlk,
					 size_t nBytes);
typedef STATUS (*FUNC_CREATE_HOOK) (PART_ID partId, FUNC_ALLOC allocFunc,
				    FUNC_FREE freeFunc,
				    FUNC_REALLOC reallocFunc,
				    size_t defAlign);
typedef void * (*FUNC_ALLOC_HOOK)	(PART_ID partId, void * arg,
					 size_t nBytes, size_t alignment);
typedef STATUS (*FUNC_FREE_HOOK)	(PART_ID partId, void * arg,
					 char * ptr);
typedef void * (*FUNC_REALLOC_HOOK) (PART_ID partId, void * arg, char * ptr,
				     size_t nBytes);
typedef STATUS (*FUNC_DELETE_HOOK) (PART_ID partId, void * arg);
typedef STATUS (*FUNC_FREE_WALK_CB)	(void * pMemBlock, size_t size,
					 void * cbArg, BOOL * pCont);
typedef void * (*FUNC_MEM_PART_REALLOC) (PART_ID partId, char * pBlock,
					size_t nBytes);
typedef void * (*FUNC_PART_GROW) (size_t reqSize, size_t * pActualSize);

typedef void (*FUNC_MEMPART_ALLOC_ERROR) (PART_ID pPart, size_t nBytes,
                                          size_t alignment);
typedef void (*FUNC_MEMPART_BLOCK_ERROR) (PART_ID pPart, char * pBlock,
                                          char * label, char * pMsg);
/*
 * Data structure for a memory section (i.e. piece of memory added to a
 * a partition via memPartAddToPool
 */

typedef struct mem_section_hdr
    {
    /* pointer to the next section part of the memory partition */

    SL_NODE	sectionNode;

    /* size of this section */

    size_t	size;

    /* padding is done through MEM_SECTION_HDR_SIZE */

    } MEM_SECTION_HDR;

/* data structure for a free chunk */

typedef struct free_chunk_hdr
    {
    /*
     * size of previous chunk.
     * For ILP32, the size = number of bytes.
     * For LP64, the size = (number of bytes) >> 2.
     *           This allows for supporting upto 16GBytes.
     */

    UINT			prevSize;

    /*
     * size of current chunk + flag indicating if previous chunk is free.
     * For ILP32, the size = number of bytes.
     * For LP64, the size = (number of bytes) >> 2.
     *           This allows for supporting upto 16GBytes.
     */

    UINT			size;

    /*
     * pointers to previous and next free chunks of the same size
     */

    struct free_chunk_hdr *	next;
    struct free_chunk_hdr *	prev;

    } FREE_CHUNK_HDR;

/* the order of the fields in MEM_PART_SIZE_NODE is important */

typedef struct
    {
    AVLU_NODE		avlSize;	/* AVL tree sorted by the size key  */
    FREE_CHUNK_HDR *	next;		/* pointer to the first free chunck */
    FREE_CHUNK_HDR *	prev;		/* pointer to the last free chunck  */

    } MEM_PART_SIZE_NODE;

/* memory partition data structure */

typedef struct mem_part
    {
    OBJ_CORE	objCore;		/* object management */

    AVLU_TREE	avlSize;		/* root of the size node AVL tree     */
    MEM_PART_SIZE_NODE * freeSizeNode;	/* pointer to first free size node    */
    UINT	sizeNodeNb;		/* number of used avl size node       */

    UINT	freeSizeNodeNb;		/* number of remaining free size node */

    SEMAPHORE	sem;			/* partition semaphore 		      */
    size_t	totalWords;		/* total number of words in partition */
    unsigned	options;		/* options */
#ifdef	_WRS_CONFIG_LP64
    unsigned	pad;			/* explicit padding */
#endif	/* _WRS_CONFIG_LP64 */
    SL_LIST	sectionHdrLst;		/* list of sections in partition      */

    /* alloc hooks */

    FUNC_ALLOC_HOOK	allocHook;	/* hook for memPartAlignedAlloc       */
    FUNC_FREE_HOOK	freeHook;	/* hook for memPartFree               */
    FUNC_REALLOC_HOOK	reallocHook;	/* hook for memPartRealloc            */
    FUNC_DELETE_HOOK	deleteHook;	/* hook for memPartDelete             */
    void *		hookArg;	/* argument for hooks                 */

    /* allocation statistics */

    size_t	curBlocksFreed;		/* current # of blocks freed          */
    size_t	curWordsFreed;		/* current # of words freed           */
    size_t	curBlocksAllocated;	/* current # of blocks allocated      */
    size_t	curWordsAllocated;	/* current # of words allocated       */
    UINT64	cumBlocksAllocated;	/* cumulative # of blocks allocated   */
    UINT64	cumWordsAllocated;	/* cumulative # of words allocated    */
    size_t	maxWordsAllocated;	/* peak # of words allocated  	      */
    size_t	curBlocksAllocatedInternal; /* current # of blocks allocated  */
    					/* for internal use		      */
    size_t	curWordsAllocatedInternal; /* current # of words allocated    */
    					/* for internal use		      */
#ifndef	_WRS_CONFIG_COMPAT69_ADR_SPACE
    /* automatic growth support fields */

    FUNC_PART_GROW  memPartGrowFuncPtr;
#endif	/* _WRS_CONFIG_COMPAT69_ADR_SPACE */

#ifdef	ENABLE_LOCALITY_PRESERVATION
    /* locality preservation support */

    FREE_CHUNK_HDR *	lastSplittedChunkHdr;
    size_t		lastSplittedChunkSize;
#endif	/* ENABLE_LOCALITY_PRESERVATION */

#ifdef	_WRS_CONFIG_SMP
    Q_HEAD	deleterPendQ;	/* deleter pend queue */
    atomic32_t	refCnt;			/* reference count for SMP */
#endif	/* _WRS_CONFIG_SMP */

    } PARTITION;


/* data structure for an allocated chunk */

typedef struct alloc_chunk_hdr
    {
    /*
     * size of previous chunk.
     * For ILP32, the size = number of bytes.
     * For LP64, the size = (number of bytes) >> 2.
     *           This allows for supporting upto 16GBytes.
     */

    UINT		prevSize;

    /*
     * size of current chunk + flag indicating if previous chunk is free.
     * For ILP32, the size = number of bytes.
     * For LP64, the size = (number of bytes) >> 2.
     *           This allows for supporting upto 16GBytes.
     */

    UINT		size;

    /* partition ID */

    PART_ID		memPartId;

#ifndef _WRS_CONFIG_LP64
    /* head guard */

    ULONG		headGuard;
#endif

    } ALLOC_CHUNK_HDR;


/* definitions for backward compatibility */

#define	BLOCK_HDR		ALLOC_CHUNK_HDR
#define	FREE_BLOCK		FREE_CHUNK_HDR
#define	BLOCK_TO_HDR(pBuf)	BLOCK_TO_CHUNK_HDR(pBuf)

/* variable declarations */

extern CLASS_ID memPartClassId;		/* memory partition class id */
extern FUNC_MEMPART_BLOCK_ERROR memPartBlockErrorRtn;	/* block error method */
extern FUNC_MEMPART_ALLOC_ERROR memPartAllocErrorRtn;	/* alloc error method */
extern unsigned	memPartOptionsDefault;	/* default partition options */
extern size_t	memDefaultAlignment;	/* default alignment */
extern PART_ID	kProxHeapPartId;	/* Kernel Proximity Heap part Id. */
#ifdef _WRS_CONFIG_MMULESS_KERNEL
extern char * kProxHeapStart;           /* Kernel Proximity Heap start addr. */
extern size_t kProxHeapSize;            /* Kernel Proximity Heap size */
#endif

/* shared memory manager function pointers */

extern FUNCPTR	smMemPartAddToPoolRtn;
extern FUNCPTR	smMemPartFreeRtn;
extern FUNCPTR	smMemPartAllocRtn;


/* function declarations */

extern BOOL	memPartBlockIsValid  (PART_ID partId, FREE_CHUNK_HDR *pHdr,
				      BOOL isFree);
extern STATUS	memPartBlockValidate (PART_ID partId, char * pBlock);
extern STATUS	memPartCreateHookSet (FUNC_CREATE_HOOK createHook,
				      BOOL guardEnable);
extern STATUS	memPartHooksInstall  (PART_ID partId, void *  hookArg,
				      FUNC_ALLOC_HOOK allocHook,
				      FUNC_FREE_HOOK freeHook,
				      FUNC_REALLOC_HOOK reallocHook,
				      FUNC_DELETE_HOOK deleteHook);
extern STATUS	memPartVerifiedLock  (PART_ID partId);
extern size_t	memBlockSizeGet      (void * pBlock);
extern STATUS	memInfoInit          (void);
extern STATUS	memInit              (char *pPool, size_t poolSize,
				      unsigned options);
extern STATUS	kProxHeapInit        (char *pPool, size_t heapSize);
extern STATUS	kCommonHeapInit      (size_t heapInitialSize,
				      size_t heapIncrSize);
extern STATUS	memPartLibInit       (char *pPool, size_t poolSize);
extern STATUS	memPartFreeListWalk  (PART_ID partId, int order,
				      FUNC_FREE_WALK_CB cbRtn, void * cbArg);
extern STATUS	memPartGrowRtnSet    (PART_ID partId,
				      FUNC_PART_GROW memPartGrowFunc);
extern STATUS	memPartAllocN        (PART_ID partId, size_t size,
                                      void ** pPtrArray, UINT count);
extern STATUS	memPartFreeN         (PART_ID partId, void ** pPtrArray,
                                      UINT count);

extern int      memSysPartCouldBeOwner (TASK_ID taskId);

#ifdef _WRS_CONFIG_CERT
extern BOOL memAllocDisabled;
#endif

/* function pointers */

extern void *	(*_func_valloc)		     (size_t size);
extern void *	(*_func_memalign)	     (size_t alignment, size_t size);
extern void *	(*_func_memPartCacheAlloc)   (PART_ID partId, size_t nBytes,
					      size_t alignment);
extern STATUS	(*_func_memPartCacheFree)    (PART_ID partId, void * pBlock);
extern STATUS	(*_func_memPartCacheInfoGet) (MEM_PART_STATS * pPartStats);

/* resource allocation control definitions and declarations */

#ifdef _WRS_CONFIG_CORE_SAFETY

#define RES_ALLOC_MEM	1
#define RES_ALLOC_SHM	2

extern STATUS	(*_func_resAllocRequest) (size_t nBytes, int type);
extern void	(*_func_resAllocDealloc) (size_t nBytes, int type);
extern void	(*_func_resAllocCtxSet) (struct windTcb * pTcb,
                                             void * resAllocCtx);
extern void     (*_func_resAllocCtxDefaultSet) (struct windTcb * pTcb);
extern void *   (*_func_resAllocRtpCtxGet) (struct wind_rtp * pRtp);
#endif

#endif	/* _ASMLANGUAGE */

#ifdef	__cplusplus
}
#endif	/* __cplusplus */

#endif	/* __INCmemPartLibPh */
