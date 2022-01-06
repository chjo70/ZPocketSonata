/* memPartCacheLibP.h - private memory cache  management library header file */

/* 
 * Copyright (c) 2013 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */

/*
modification history
--------------------
19jul13,pcs  update prototype of memPartCacheLibInit
15jul13,pcs  code review changes.
21may13,pcs  Moved typedef struct memPartCacheBin and typedef struct
             memPartCache from memPartCacheLib.c to here.
05may13,pcs  created
*/

#ifndef __INCmemPartCacheLibPh
#define __INCmemPartCacheLibPh

#ifdef __cplusplus
extern "C" {
#endif

/* Any C declaration should be added here */

#define MP_CACHE_BINS                    16
#define MP_CACHE_BIN_SIZE                 8

#define MP_CACHE_BLOCK_MAX_SIZE         512

#define MEM_PART_CACHE_SET(pTcb,cache)  (pTcb)->pMemCache = (void *) (cache)
#define MEM_PART_CACHE_GET(pTcb)        ((MP_CACHE *) ((pTcb)->pMemCache))

extern STATUS memPartCacheLibInit (BOOL enableGlobal);
extern UINT memPartCacheBinSizeGet (int binIndex);
typedef struct memPartCacheBin
    {
    void *                      pBlock[MP_CACHE_BIN_SIZE];
    UINT32                      ixmap;
    UINT32                      fillmap;
    off_t                       spacing;
    ULONG                       heapMallocCnt;
    ULONG                       heapFreeCnt;
    ULONG                       cacheMallocCnt;
    ULONG                       cacheFreeCnt;
    ULONG                       flushCnt;
    ULONG                       hitCnt;
    ULONG                       missCnt;
    } MP_CACHE_BIN;

typedef struct memPartCache
    {
    MP_CACHE_BIN                bins[MP_CACHE_BINS];
    ULONG                       hitCnt;
    ULONG                       missCnt;
    ULONG                       flushCnt[MP_CACHE_BIN_SIZE];
    } MP_CACHE;

#ifdef __cplusplus
}
#endif

#endif /* __INCmemPartCacheLibPh */

