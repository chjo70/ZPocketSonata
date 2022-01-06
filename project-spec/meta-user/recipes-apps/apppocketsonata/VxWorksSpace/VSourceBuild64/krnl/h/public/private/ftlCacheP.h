/* ftlCacheP.h - ftl data cache private header file */ 

/*
 * Copyright (c) 2012-2013, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
13may15,txu  fix V7STO-358 : wrong include after extern "C"
04sep13,jxu  adapted path of includes for vx7 
04sep13,jxu  turn off the trace of io pattern.
15jun12,jxu  written.
*/

#ifndef __INCftlCachePh
#define __INCftlCachePh


/* includes */

#include <private/ftlOsIf.h>
#include <private/ftlLibP.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* defines */

/* #define TRACE_IO_PATTERN */

/* typedefs */

typedef DL_LIST FBIO_LIST;
typedef DL_NODE FBIO_NODE;

#ifdef TRACE_IO_PATTERN
typedef struct io_window
    {
    UINT16 start;       /* start of this window */
    UINT16 end;         /* end of this window */
    UINT32 lastHit;     /* save the "time" when this window is hit */ 
    }IO_WINDOW;
#endif /* TRACE_IO_PATTERN */

typedef struct ftl_data_cache 
    {
    size_t      nPageBufs;      /* how many page buffers */ 
    void *      pPageBuf;       /* memory used for flash page buffers in */
                                /* data cache */
    DL_LIST     freeFpioList;   /* free fpio list */
    FTL_ATOMIC32_T nDirtyPageBufs;    /* # of dirty page buffers */

    /* 
     * Following two lists are protected by lbn tree lock instead of
     * data cache lock. It's a little weird, but simplifies things.
     */

    FBIO_LIST   usedFbioList;      /* used fbios */ 
    int         repPolicy;      /* cache replacement policy */

    FTL_LOCK_T  dataCacheLock;  /* lock for protecting following stuff */

#ifdef TRACE_IO_PATTERN
    /* Statistics to help determine the current access pattern */

    int         ioPattern;      /* random or sequential access pattern */

    /* total I/O count under the current access pattern */  

    UINT32      ioCnt;                  

    /* 
     * If cache miss rate since the last cache hit goes higher than 
     * the threshold, the access pattern is determined as sequential.
     */

    int         missCnt;        /* cache miss rate */
    int         missRateThresh; /* cache miss rate threshold */ 

    /* 
     * We use a couple of I/O windows to track the changing access
     * pattern.
     */

    UINT16      nIoWindows;     /* number of I/O windows */
    IO_WINDOW * pIoWindows;     /* pointer to the I/O windows */
    UINT16      maxInterval;    /* the maximum "time" between two consecutive */
                                /* hits in the same window */
#endif /* #ifdef TRACE_IO_PATTERN */
    }FTL_DATA_CACHE;

/* function declarations */

BOOL ftlIsCacheEnabled (FTL_DESC * pFtl);
int ftlCacheInit (FTL_DESC * pFtl);
int ftlCacheCleanup (FTL_DESC * pFtl);
STATUS ftlCacheFlush (FTL_DESC * pFtl, int option);
STATUS ftlCacheDiscard (FTL_DESC * pFtl, 
            FTL_BLK_DISCARD_INFO * pBlkDiscardInfo);
int ftlCacheBlkRW(FTL_DESC * pFtl, fblock_t blkAddr,
            fbsize_t blkOff, fbsize_t ioLen, char * pDataBuf, 
            int rwFlag);
STATUS ftlCacheCheckFlush (FTL_DESC * pFtl);
int fbioCacheDelete (FBIO_LIST * pPool, FBIO_NODE * pNode);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCftlCachePh */

