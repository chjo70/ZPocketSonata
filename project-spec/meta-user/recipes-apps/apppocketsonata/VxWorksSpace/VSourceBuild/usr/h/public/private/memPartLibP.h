/* memPartLibP.h - private user memory partition library header file */

/* 
 * Copyright (c) 2003-2006, 2010, 2014, 2016-2017 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
13jan17,kk   make the _func_memPartCacheFree/Alloc funcptrs externs
10aug16,ajt  Added support for SMP-optimized memory allocator (F3925)
26jun14,pcs  CERT: Added external declaration for memAllocDisabled
11nov10,pcs  Make headGuard configurable for LP64.
26oct10,jpb  Fixed type-casting in macro MAX_ALLOWED_ALLOC_SIZE.
22oct10,pcs  add a macro MAX_ALLOWED_ALLOC_SIZE to represent the maximum
             allowed/possible single allocation in LP64.
01oct10,pcs  Updated to change the data type of end guard works from UINT to 
             ULONG.
29jul10,pad  Moved extern C statement after include statements.
27jul10,pcs  Fix issue with macro BLOCK_END_GUARD.
31mar10,pcs  typecast the return value of macro BYTE_SIZE_TO_SIZE to UINT32.
05jan10,pcs  Updated to add support for LP64.
07aug06,jpb  Renaming mem_part to _Vx_mem_part for posix conformance
07mar06,zl   added FUNC_PART_GROW typedef
27sep05,zl   added ED&R option bits to MEM_OPTIONS_MASK.
15apr05,zl   changed CHUNK_MIN_SIZE to larger minimum block.
03may04,zl   made cumWordsAllocated 64-bit, removed minBlockWords.
29jan04,zl   added allocated block guard signature support.
05nov03,md   added user level semaphores.
30oct03,zl   added create, delete, alloc, free, realloc hooks.
27oct03,zl   updated for new avlLib API.
19sep03,zl   fixed MEM_PART_LOCK_INIT.
10sep03,zl   created based on kernel version 01k.
*/

#ifndef __INCmemPartLibPh
#define __INCmemPartLibPh

#include <vxWorks.h>
#include <vwModNum.h>
#include <memLib.h>
#include <sllLib.h>
#include <avlUintLib.h>
#include <private/semLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WRS_CONFIG_LP64
extern size_t allocChunkHeadGuardSize;
#define ALLOC_CHUNK_HDR_SIZE    (sizeof(ALLOC_CHUNK_HDR) + \
                                 allocChunkHeadGuardSize)
#else
#define ALLOC_CHUNK_HDR_SIZE	sizeof(ALLOC_CHUNK_HDR)
#endif
#define MEM_SECTION_HDR_SIZE	max(_ALLOC_ALIGN_SIZE, sizeof(MEM_SECTION_HDR))

#define PREV_CHUNK_IS_FREE	1
#define CHUNK_SIZE_MASK 	(~(PREV_CHUNK_IS_FREE))

#define ALLOC_STATE_HEAP_ALLOC      0
#define ALLOC_STATE_MEM_CACHE_ALLOC 1
#define ALLOC_STATE_MEM_CACHE_FREE  2
#define ALLOC_STATE_MASK        (3)

#define GET_ALLOC_STATE(blkHdr)         ((ULONG)((blkHdr)->memPartId) & \
                                         (ALLOC_STATE_MASK))
#define IS_ALLOC_STATE_MEM_CACHE_ALLOC(blkHdr) \
    (((ULONG)((ALLOC_CHUNK_HDR *)blkHdr)->memPartId == \
    ((ULONG)ALLOC_STATE_MEM_CACHE_ALLOC | (ULONG)heapPartId)) ? TRUE : FALSE)

#define IS_ALLOC_STATE_MEM_CACHE_FREE(blkHdr) \
    (((ULONG)((ALLOC_CHUNK_HDR *)blkHdr)->memPartId == \
    ((ULONG)ALLOC_STATE_MEM_CACHE_FREE | (ULONG)heapPartId)) ? TRUE : FALSE)

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
#else
#define SIZE_SHIFT 2
#define BYTE_SIZE_TO_SIZE(blkSize) ((UINT32)((ULONG)(blkSize) >> SIZE_SHIFT))
#define SIZE_TO_BYTE_SIZE(blkSize) ((ULONG)((ULONG)(blkSize) << SIZE_SHIFT))
#define MAX_ALLOWED_ALLOC_SIZE     (((size_t)(-1U) << SIZE_SHIFT))
#endif

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
#define BLOCK_HEAD_GUARD(pHdr)  ((ULONG *) (((ULONG) (pHdr)) + \
                                            sizeof(ALLOC_CHUNK_HDR)))
#else
#define BLOCK_HEAD_GUARD(pHdr)  ((ULONG *) (&pHdr->headGuard))
#endif

/* macro to get to end guard */

#define BLOCK_END_GUARD(pHdr)	((ULONG *) (((ULONG) (pHdr)) +    \
                                        (SIZE_TO_BYTE_SIZE((pHdr)->size \
                                        & CHUNK_SIZE_MASK)) - \
					allocChunkEndGuardSize))

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
 * minimum meaningfull size for a chunk. This is due to the fact that:
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
 * plus a free block of size 0 plus a region header. Assume worst case with,
 * end guards enabled.
 */

#define REGION_START_OVERHEAD	(MEM_SECTION_OVERHEAD + ALLOC_CHUNK_HDR_SIZE + \
				 END_GUARD_WORDS * sizeof (ULONG) + \
				 CHUNK_FREE_OVERHEAD)
#define REGION_END_OVERHEAD	(2 * (ALLOC_CHUNK_HDR_SIZE + \
				      END_GUARD_WORDS * sizeof (ULONG)))

#define REGION_MIN_SIZE		(REGION_START_OVERHEAD + REGION_END_OVERHEAD)

/*
 * actual size of the data block within an allocated chunck, retrieved from
 * the chunk header address (BLOCK_SIZE) or the buffer address (MEM_BLOCK_SIZE)
 */

#define BLOCK_SIZE(pHdr) ((SIZE_TO_BYTE_SIZE((pHdr)->size & CHUNK_SIZE_MASK))- \
				 CHUNK_ALLOC_OVERHEAD)
#define	MEM_BLOCK_SIZE(pBlock)	memBlockSizeGet((void *)(pBlock))

#define ALIGN_NEXT(size,align)	((((ULONG)(size)) + align - 1) & (~(align - 1)))

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
#define HEAD_GUARD_WORDS                2
#define GUARD_PATTERN			0xa110cb1ca110cb1c
#else
#define GUARD_PATTERN			0xa110cb1c
#endif
#define END_GUARD_WORDS			4

#ifndef _ASMLANGUAGE

#define MEM_PART_SIGNATURE		0xa4e49a17
#define MEM_PART_VALID_SET(partId)				\
		(partId)->signature = MEM_PART_SIGNATURE
#define MEM_PART_INVALIDATE(partId)				\
		(partId)->signature = 0
#define MEM_PART_ID_VERIFY(partId)	\
		((((partId) != NULL) &&				\
		  (ALIGNED ((partId), sizeof (void *))) && 	\
		  ((partId)->signature == MEM_PART_SIGNATURE)) 	\
		 ? OK : ERROR)

/* mutual exclusion primitives */

#define MEM_PART_MUTEX_OPT		SEM_USER | 		\
					SEM_Q_PRIORITY | 	\
					SEM_DELETE_SAFE |	\
					SEM_INVERSION_SAFE

#define MEM_PART_LOCK_INIT(partId)				\
		(semMInit(&(partId)->sem, MEM_PART_MUTEX_OPT))
#define MEM_PART_LOCK(partId)					\
		semTake (&(partId)->sem, WAIT_FOREVER)
#define MEM_PART_VERIFIED_LOCK(partId)				\
		memPartVerifiedLock(partId)
#define MEM_PART_UNLOCK(partId)					\
		(void)semGive (&(partId)->sem)
#define MEM_PART_LOCK_DELETE(partId)				\
		(void)semDestroy (&(partId)->sem, FALSE)

/* typedefs */

typedef void * (*FUNC_ALLOC) (PART_ID partId, size_t nBytes, 
			      size_t alignment);
typedef STATUS (*FUNC_FREE) (PART_ID partId, char * pBlk);
typedef void * (*FUNC_REALLOC) (PART_ID partId, char * pBlk, size_t nBytes);
typedef STATUS (*FUNC_CREATE_HOOK) (PART_ID partId, FUNC_ALLOC allocFunc,
				    FUNC_FREE freeFunc, 
				    FUNC_REALLOC reallocFunc, 
				    size_t defAlign);
typedef void * (*FUNC_ALLOC_HOOK) (PART_ID partId, void * arg, size_t nBytes,
				   size_t alignment);
typedef STATUS (*FUNC_FREE_HOOK) (PART_ID partId, void * arg, char * ptr);
typedef void * (*FUNC_REALLOC_HOOK) (PART_ID partId, void * arg, char * ptr,
				     size_t nBytes);
typedef STATUS (*FUNC_DELETE_HOOK) (PART_ID partId, void * arg);
typedef void * (*FUNC_PART_GROW) (size_t reqSize, size_t * pActualSize);

typedef void (*FUNC_MEMPART_ALLOC_ERROR) (PART_ID pPart, size_t nBytes, 
                                          size_t alignment);
typedef void (*FUNC_MEMPART_BLOCK_ERROR) (PART_ID pPart, char *pBlock, 
                                          char *label);

/* 
 * Data structure for a memory section (i.e. piece of memory added to a
 * a partition via memPartAddToPool
 */

typedef struct mem_section_hdr
    {
    /* pointer to the next section part of the memory partition */

    SL_NODE 	sectionNode;

    /* size of this section */

    size_t	size;

    /* padding is done through MEM_SECTION_HDR_SIZE */

    } MEM_SECTION_HDR;

/* data structure for a free chunk */

typedef struct free_chunk_hdr
    {
    /* size of previous chunk */

    UINT			prevSize;

    /* size of current chunk + flag indicating if previous chunk is free */

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
    AVLU_NODE    	avlSize;        /* AVL tree sorted by the size key  */
    FREE_CHUNK_HDR *	next;		/* pointer to the first free chunck */
    FREE_CHUNK_HDR *	prev;		/* pointer to the last free chunck  */

    } MEM_PART_SIZE_NODE;

/* memory partition data structure */

typedef struct _Vx_mem_part
    {
    UINT	signature;		/* partition signature word */
    unsigned	options;		/* options */
    AVLU_TREE 	avlSize;		/* root of the size node AVL tree     */
    UINT	sizeNodeNb;		/* number of used avl size node       */

    UINT	freeSizeNodeNb;		/* number of remaining free size node */
    MEM_PART_SIZE_NODE * freeSizeNode;	/* pointer to first free size node    */

    SEMAPHORE	sem;			/* partition semaphore 		      */
    size_t	totalWords;		/* total number of words in partition */
    SL_LIST	sectionHdrLst;		/* list of sections in partition      */

    /* alloc hooks */

    FUNC_ALLOC_HOOK   allocHook;	/* hook for memPartAlignedAlloc       */
    FUNC_FREE_HOOK    freeHook;		/* hook for memPartFree               */
    FUNC_REALLOC_HOOK reallocHook;	/* hook for memPartRealloc            */
    FUNC_DELETE_HOOK  deleteHook;	/* hook for memPartDelete             */
    void *	      hookArg;		/* argument for hooks                 */ 

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

    /* automatic growth support fields */

    FUNC_PART_GROW  memPartGrowFuncPtr;

#ifdef ENABLE_LOCALITY_PRESERVATION
    /* locality preservation support */

    FREE_CHUNK_HDR * lastSplittedChunkHdr;
    size_t     	     lastSplittedChunkSize;
#endif
    } PARTITION;

/* data structure for an allocated chunk */

typedef struct alloc_chunk_hdr
    {
    /* size of previous chunk */

    UINT		prevSize;

    /* size of current chunk + flag indicating if previous chunk is free */

    UINT		size;

    /* partition ID */

    PART_ID		memPartId;

#ifndef _WRS_CONFIG_LP64
    /* head guard */

    size_t		headGuard;
#endif

    } ALLOC_CHUNK_HDR;

/* definitions for backward compatibility */

#define	BLOCK_HDR		ALLOC_CHUNK_HDR
#define	FREE_BLOCK		FREE_CHUNK_HDR
#define	BLOCK_TO_HDR(pBuf)	BLOCK_TO_CHUNK_HDR(pBuf)

/* variable declarations */

extern FUNC_MEMPART_BLOCK_ERROR  memPartBlockErrorRtn;	/* block error method */
extern FUNC_MEMPART_ALLOC_ERROR  memPartAllocErrorRtn;	/* alloc error method */
extern unsigned	memPartOptionsDefault;	/* default partition options */
extern size_t	memDefaultAlignment;	/* default alignment */

/* function declarations */

extern BOOL	memPartBlockIsValid (PART_ID partId, FREE_CHUNK_HDR *pHdr, 
				     BOOL isFree);
extern STATUS   memPartBlockValidate (PART_ID partId, char * pBlock);
extern STATUS	memPartCreateHookSet (FUNC_CREATE_HOOK createHook, 
				      BOOL guardEnable);
extern STATUS	memPartHooksInstall (PART_ID partId, void *  hookArg, 
				     FUNC_ALLOC_HOOK allocHook, 
				     FUNC_FREE_HOOK freeHook,
				     FUNC_REALLOC_HOOK reallocHook,
				     FUNC_DELETE_HOOK deleteHook);
extern size_t   memBlockSizeGet (void * pBlock);
extern STATUS   memPartGrowRtnSet (PART_ID partId, FUNC_PART_GROW growFuncPtr);
extern STATUS   memPartAllocN        (PART_ID partId, size_t size, 
                                      void ** pPtrArray, UINT count);
extern STATUS   memPartFreeN         (PART_ID partId, void ** pPtrArray, 
                                      UINT count);
#ifdef _WRS_CONFIG_CERT
extern BOOL memAllocDisabled;
#endif

/* function pointers */

#ifndef _WRS_CONFIG_CERT
extern STATUS   (*_func_memPartCacheFree)    (PART_ID partId, void * pBlock);
#endif /* _WRS_CONFIG_CERT */

extern void *   (*_func_memPartCacheAlloc)   (PART_ID partId, size_t nBytes, 
                                              size_t alignment);


#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCmemPartLibPh */
