/* poolLibP.h - private header file for Wind Memory Pools */

/*
 * Copyright (c) 1998, 2003-2005, 2007-2011, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
06nov14,jpb  static analysis defects
01feb11,cww  Added freeCount to pool structure (WIND00247578)
17sep10,gls  made VX_POOL kernel only
28jun10,pad  Made so that _WRS_CONFIG_MEM_ALLOT option applies to the
             kernel environment only.
28apr10,pad  Moved extern C statement after include statements.
16dec09,zl   declare VX_POOL unconditionally, for small footprint
             VxWorks configuration as well.
14sep09,zl   added poolInitialize()
01apr09,jpb  Replaced lstLib with dllLib.
27may09,x_s  Wrapped some code with vsb option _WRS_CONFIG_MEM_ALLOT and 
             removed _BUILD_POOL_LIB.
27aug08,jpb  Renamed VSB header file.
18jun08,jpb  Added include path for kernel configurations options set in
             vsb.
08may08,jpb  Modifications for source build.   Renamed INCLUDE_MEM_ALLOT to 
             _WRS_CONFIG_MEM_ALLOT.
12feb07,jmg  Added declaration of poolLibInit().
12aug05,zl   exclude building in unsupported layers.
08aug05,zl   added POOL_CREATE and POOL_ITEM_GET macros. Embedded semaphore
             in pool structure.
27jul05,mil  Added support for minimal kernel.
18feb04,dat  POOL structure is private, not public
20aug03,zl   added item alignment support.
22feb98,dat, original version.  TOR 1.0.1/VXW 5.3 compatible.
	    mas,tm
*/

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef INCpoolLibPh
#define INCpoolLibPh

/* Includes */

#include <vxWorks.h>
#include <vsbConfig.h>
#include <private/semLibP.h>
#include <poolLib.h>
#include <dllLib.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Private macros */

#define POOL_SEM_CREATE_ATTRIB \
    (SEM_Q_PRIORITY | SEM_INVERSION_SAFE | SEM_DELETE_SAFE)

#define POOL_SEM_TAKE_ATTRIB	WAIT_FOREVER

/* indicator of a block that is provided by user */

#define BLOCK_DO_NOT_FREE	0x00000001

#ifndef _ASMLANGUAGE

#ifdef _WRS_KERNEL

/* macro used to statically declare memory pools */

#define VX_POOL(name) \
        _WRS_DATA_ALIGN_BYTES(VX_OBJ_ALIGN_SIZE) char name [sizeof(POOL)]

#ifdef _WRS_CONFIG_MEM_ALLOT

/*
 * for layers that don't support poolLib (MKL), simulate the API via
 * memAllotLib. There is no POOL_ITEM_RETURN() in this case.
 */

#define POOL_CREATE(name, itmSize, align, initCnt, incrCnt, partId, options)   \
	    memAllotPoolCreate(itmSize, align)
#define POOL_ITEM_GET(poolId)						       \
	    memAllot(poolId->sizItem, poolId->alignment)

typedef struct pool	/* Pool structure */
    {
    size_t		sizItem;	/* individual item size in bytes */
    size_t		alignment;	/* individual item alignment in bytes */
    } POOL;

extern void *  memAllot (unsigned size, unsigned alignment);
extern POOL_ID memAllotPoolCreate (unsigned itmSize, unsigned alignment);

#else	/* !_WRS_CONFIG_MEM_ALLOT */

#define POOL_LIST_LOCK()	semMTake (&poolListMutex, POOL_SEM_TAKE_ATTRIB)
#define POOL_LIST_UNLOCK()	(void) semMGive (&poolListMutex)
#define POOL_LOCK(poolId)	semMTake (&(poolId)->mutex, POOL_SEM_TAKE_ATTRIB)
#define POOL_UNLOCK(poolId)	(void) semMGive (&(poolId)->mutex)

#endif	/* _WRS_CONFIG_MEM_ALLOT */
#else   /* !_WRS_KERNEL */

#define POOL_LIST_LOCK()	semTake (&poolListMutex, POOL_SEM_TAKE_ATTRIB)
#define POOL_LIST_UNLOCK()	(void) semGive (&poolListMutex)
#define POOL_LOCK(poolId)	semTake (&(poolId)->mutex, POOL_SEM_TAKE_ATTRIB)
#define POOL_UNLOCK(poolId)	(void) semGive (&(poolId)->mutex)
#endif /* _WRS_KERNEL */

#if !(defined (_WRS_KERNEL) && defined (_WRS_CONFIG_MEM_ALLOT))

#define POOL_CREATE(name, itmSize, align, initCnt, incrCnt, partId, options)   \
	    poolCreate(name, itmSize, align, initCnt, incrCnt, partId, options)
#define POOL_ITEM_GET(poolId)						       \
	    poolItemGet(poolId)
#define POOL_ITEM_RETURN(poolId,pItem)					       \
	    poolItemReturn(poolId, pItem)

/* Pool Block records */

typedef struct pool_block
    {
    DL_NODE	blockNode;	/* block node for pool */
    void *	pItmBlk;	/* ptr to start of item pool block */
    ULONG	itemCnt;	/* count of items in this block */
    } POOL_BLOCK;

typedef struct pool	/* Pool structure */
    {
    DL_NODE		poolNode;	/* pool list for pond */
    const char *	poolName;	/* pool name */
    SEMAPHORE		mutex;		/* Mutex to use for thread-safe pools */
    size_t		sizItem;	/* individual item size in bytes */
    size_t		sizItmReal;	/* actual item size, due to alignment */
    size_t		alignment;	/* individual item alignment in bytes */
    ULONG		numIncr;	/* nr. of incrementally allocated itm */
    ULONG		numTotl;	/* total number of items created */
    PART_ID		partId;		/* memory partition ID */
    ULONG		options;	/* pool options word */
    DL_LIST		blockList;	/* allocated block list */
    DL_LIST		freeItems;	/* free item list */
    ULONG		freeCount;	/* length of freeItems list */
    POOL_BLOCK		staticBlock;	/* for the first static block */
    } POOL;

#endif	/* _WRS_KERNEL || _WRS_CONFIG_MEM_ALLOT */

/* private functions */

STATUS	poolLibInit	(void);
POOL_ID	poolInitialize	(char * pPool, const char * pName, size_t itmSize,
			 size_t alignemnt, ULONG initCnt, ULONG incrCnt,
			 PART_ID partId, ULONG options);
BOOL	poolFindItem	(DL_LIST * pList, DL_NODE * pItem);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  /* INCpoolLibPh */
