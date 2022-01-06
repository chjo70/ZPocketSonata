/* memPartLib.h - user-level memory partition management library header file */

/* 
 * Copyright (c) 2003-2006, 2010 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01e,29jul10,pad  Moved extern C statement after include statements.
01d,05jan10,pcs  Updated to add support for LP64.
01c,07mar06,zl   moved memPartGrowRtnSet() to private header
01b,05may04,zl   added memPartDelete() prototype.
01a,10sep03,zl   created.
*/

#ifndef __INCmemPartLibh
#define __INCmemPartLibh

#include <vxWorks.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

/* typedefs */

typedef struct mem_part_stats
    {
    size_t numBytesFree;     /* Number of Free Bytes in Partition             */
    size_t numBlocksFree;    /* Number of Free Blocks in Partition            */
    size_t maxBlockSizeFree; /* Maximum block size that is free.	      */
    size_t numBytesAlloc;    /* Number of Allocated Bytes in Partition        */
    size_t numBlocksAlloc;   /* Number of Allocated Blocks in Partition       */
    size_t maxBytesAlloc;    /* Maximum number of Allocated Bytes at any time */
    }  MEM_PART_STATS;

/* function declarations */

extern STATUS 	memPartLibInit ();
extern PART_ID 	memPartCreate (char *pPool, size_t poolSize);
extern STATUS 	memPartDelete (PART_ID partId);
extern STATUS 	memPartInit (PART_ID partId, char *pPool, size_t poolSize);
extern STATUS 	memPartAddToPool (PART_ID partId, char *pPool,
				  size_t poolSize);
extern void *	memPartAlloc (PART_ID partId, size_t nBytes);
extern void *   memPartAlignedAlloc (PART_ID partId, size_t nBytes,
				     size_t alignment);
extern STATUS 	memPartFree (PART_ID partId, char *pBlock);
extern STATUS 	memPartOptionsSet (PART_ID partId, unsigned options);
extern STATUS   memPartOptionsGet (PART_ID partId, UINT * pOptions);
extern size_t 	memPartFindMax (PART_ID partId);
extern void *	memPartRealloc (PART_ID partId, char *pBlock, size_t nBytes);
extern STATUS   memPartInfoGet (PART_ID	partId, MEM_PART_STATS * ppartStats);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCmemPartLibh */
