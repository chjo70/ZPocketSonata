/* ftlBm.h - FTL BM/BBM Head File */

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
11oct13,ghs  Correct compile error (WIND00438400)
04sep13,jxu  adapted path of includes for vx7 
08jun13,jxu  added ftlBmCopy to help copy pages for gc/wl/bbm 
             added a block mark for bbm to identify runtime bad blocks
08nov12,jxu  added more device geometry info to bm identity.
01sep12,jxu  rewritten for conceptual integrity.
15may12,x_z  created.
*/

#ifndef __INCftlBmh
#define __INCftlBmh


/* includes */

#include <private/ftlLibP.h>
#include <mtd.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define BM_STATUS_NOTIFIED      0x0
#define BM_STATUS_FORMATTING    0x1
#define BM_STATUS_MOUNTED       0x2

#define AVL_NODE_TO_BBMT_ENTRY(pNode)    \
                CONTAINER_OF(pNode, struct bbmt_entry_ram, avlNode)

/* erase options */

#define BM_ERASE_OPT            0x01    

#define BM_MAGIC                0x42424d54      /* 'B' 'B' 'M' 'T' */

#define BBMT_TYPE_INIT          0 
#define BBMT_TYPE_ID            0x11
#define BBMT_TYPE_START_REPL    0x22
#define BBMT_TYPE_CANCEL_REPL   0x33    /* cancel the on-going replacement */
#define BBMT_TYPE_FINISH_REPL   0x44    /* runtime bad block table */
#define BBMT_TYPE_UNDO_REPL     0x55    /* undo the finished replacement */

#define BBMT_NUM_COPY           2
#define BM_NUM_ID_BLKS          2 
#define BBMT_NUM_BLK_MARK       8

#define BBM_FLAG_CHECK_BAD_BLK  0x1     /* check if the error block is bad */

/* block copy related definitions */

struct copy_info;
typedef int (*COPY_FUNC) (FTL_DESC * pFtl, struct copy_info * pCopyInfo);
typedef struct copy_info
    {
    FTL_ADDR    srcAddr;
    BOOL        multiSrc;       /* pages from multiple blocks */
    FTL_ADDR    destAddr;
    MAP_BLK_INFO destBlkInfo;
    fpage_t     nPages;
    char *      pPageBuf;
    int         flags;
    COPY_FUNC   start;          /* callback before read the src page */
    COPY_FUNC   check;          /* callback before write to the dest page */
    long        priv;           /* private to caller */
    BOOL        stopped;        /* stop copy */ 
    BOOL        skipped;        /* TRUE if not copy current page */
    fpage_t     curPageNo;      /* last page copied well */
    fpage_t     copiedLast;     /* last page copied well */
    fpage_t     copiedPages;    /* # of copied pages */
    fpage_t     stopBlankPage;  /* stop blank starting from this page */
    }COPY_INFO;

#define DECLARE_COPY_INFO(name) \
            COPY_INFO name = {INVALID_ADDR, FALSE, INVALID_ADDR, INVALID_BLKINFO, \
                              0, NULL, 0, NULL, NULL, 0, FALSE, FALSE, FTL_INVALID_PPN,   \
                              FTL_INVALID_PPN, 0, FTL_INVALID_PPN};

#define ERASE_MARK              0       /* bitflip safe */
#define BAD_MARK                0       /* bitflip safe */

/* typedefs */

typedef struct blk_mark
    {
    UINT8       erase;
    UINT8       bad;
    }_FTL_PACK_ALIGN(1) BLK_MARK;

/* bad block check parameter */

typedef struct bbmt_blk_mark    /* block mark for bbmt blocks */
    {
    UINT32      bbmtId;         /* bbmt identity */
    UINT32      crc32;          /* checksum of this block mark */
    }_FTL_PACK_ALIGN(4) BBMT_BLK_MARK;

typedef struct bbmt_entry       /* bad block replacement entry */
    {
    UINT32      badBlkNo;       /* bad block */
    UINT32      replBlkNo;      /* replacement block */
    }_FTL_PACK_ALIGN(4) BBMT_ENTRY;

typedef struct bbmt_header      /* bbmt header */
    {
    UINT32      magic;          /* bbmt magic number */
    UINT8       extFlags;       /* set to 0 if no extension flag is set */
    UINT8       type;           /* replacement or undo-replacement */
    UINT8       nPagesPerBbmt;  /* currently not used */ 
    UINT8       copyNo;         /* copy number */
    UINT32      seqNo;          /* sequence number */
    INT32       error;          /* error type */
    UINT32      nBbmtEntry;     /* # of bbmt entries */
    UINT32      bbmtOff;        /* offset of the bbmt entries */
    UINT32      bbmtLen;        /* length of the bbmt entries */
    BBMT_ENTRY  newEntry;       /* new bbmt entry to be added */
    UINT8       reserved[4];    /* reserved for future */ 
    UINT32      dataChksum;     /* checksum of bbmt data */
    UINT32      hdrChksum;      /* checksum of bbmt header */
    }_FTL_PACK_ALIGN(4) BBMT_HEADER;    /* 48 bytes in total */

typedef struct bbmt_entry_ram   /* bbmt entry in ram */
    {
    AVL_NODE    avlNode;        /* node in tree */
    UINT32      badBlkNo;       /* bad block number */
    UINT32      replBlkNo;      /* replacement block number */
    }BBMT_ENTRY_RAM;

/* ftl BM (block management) desc */

typedef struct ftl_bm_desc      
    {
    DL_NODE     bmNode;         /* linked to BM list */

    /* FTL information */

    char       devName[FTL_DEV_NAME_LEN_MAX + 1];
    FTL_DESC * pFtlDesc;       /* related FTL descriptor */
    void *     pDevDesc;       /* descriptor of flash devices */

    UINT32     bmFlag;         /* flag for BM and FTL core */
    UINT32     status;         /* BM status */
    char *     pPageBuf;       /* page buffer (OOB included) */

    /* geometry information */

    FLASH_TYPE_T flashType;      /* flash type */
    FLASH_CELL_T cellType;       /* for nand flash only */

    UINT64      totalSize;      /* total size of this device */
    fpsize_t    pageSize;       /* page size in bytes */
    fpsize_t    pageSizeShift;  /* page size in bytes */
    fbsize_t    blkSize;        /* block size in bytes */
    fpage_t     pagesPerBlk;    /* number of pages per block */
    fblock_t    blkStart;       /* starting block number */ 
    fblock_t    nBlks;          /* total number of flash blocks */
    fpsize_t    oobSize;        /* oob size */
    fpsize_t    oobSizeAvail;   /* available oob size to FTL */
    fpsize_t    pageOobSize;    /* page size plus oob available size */

    fpage_t     blkMarkPageNo;  /* the page for writting bad mark */
    fpsize_t    blkMarkOffset;  /* bad mark offset in the page */

    /* BBM stuff */

    FTL_LOCK_T  bbmLock;        /* bad block management lock */
    FTL_LOCK_T  bbmTrLock;      /* bad block management tree lock */

    fblock_t    replBlkStart;   /* start block of consecutive */
                                        /* replacement blocks */
    fblock_t    nReplBlks;      /* number of good replacement blocks */
                                        /* in bbm area */

    fblock_t    freeReplBlkStart; /* first free block in bbm area */
    fblock_t    freeReplBlkEnd;   /* last free block in bbm area */

    fblock_t    bbmtBlkStart;    /* start block of saving bbmt */

    fblock_t *  pStBbt;         /* static bad block table */
    size_t      stBadBlkCnt;    /* # of bad blocks in bbm area */
    BBMT_ENTRY * pStBbmt;        /* static bad block map table */
    size_t      stBadBlkMapCnt; /* # of bad blocks in non-bbm area */

    AVL_TREE    badBlkTree;     /* bad block replacment search tree */

    /* address of next bbmt for each copy */

    FTL_ADDR    copyInfo[BBMT_NUM_COPY];    

    UINT32      seqNo;          /* sequence number to track the */
                                        /* latest bbmt */

    char *      pBbmtBuf;       /* buffer */
    size_t      bbmtSize;       /* current size of bbmt data */
    size_t      bbmtSizeAl;     /* aligned size of bbmt data */

#ifdef FTL_DEBUG
    struct {
        FTL_ATOMIC32_T  errorCnt;
        FTL_ATOMIC32_T  writeErrorCnt;
        FTL_ATOMIC32_T  eraseErrorCnt;
        FTL_ATOMIC32_T  eccRecvErrorCnt;
        FTL_ATOMIC32_T  eccIrrecvErrorCnt;
        FTL_ATOMIC32_T  knownEccIrrecvErrorCnt;
        FTL_ATOMIC32_T  unknownErrorCnt;
        FTL_ATOMIC32_T  stBadBlkCnt;            /* static bad block */
        FTL_ATOMIC32_T  rtBadBlkCnt;            /* run-time bad block */

        FTL_ATOMIC32_T  memUseHigh;
        FTL_ATOMIC32_T  memUseCur;
    }dbgStat;
#endif
    }FTL_BM_DESC;

/* function declarations */

STATUS ftlBmSaveId (FTL_DESC * pFtl, FTL_DEV_ID * pFtlId);
int ftlFormatBm (void * pBm, size_t sizeBBM, BOOL bPreserve);
int ftlMountBm (void * pBm, FTL_DEV_ID * pFtlId); 
int ftlUnmountBm (FTL_BM_DESC * pBm);
int ftlBmNotify (MTD_DESC * pMtdDesc, void * pArg);
int ftlBmCleanup (FTL_BM_DESC * pBm);
FTL_BM_DESC * ftlBmFind (const char * pFtlDevName);
int ftlBmRead (FTL_DESC * pFtl, FTL_ADDR * pFromAddr,
            size_t dataLen, char * pBuf, int rwFlags);
int ftlBmWrite (FTL_DESC * pFtl, FTL_ADDR * pFromAddr,
            size_t dataLen, char * pBuf, int rwFlags);
int ftlBmRW (FTL_DESC * pBm, FTL_ADDR * pFromAddr,
            size_t dataLen, char * pBuf, int rwFlags);
#ifdef obsolete
int ftlBmEraseBlk (FTL_DESC * pFtl, fblock_t blkNo, int option);
#endif
int ftlBmErase (FTL_DESC * pFtl, fblock_t blkNo, 
            fblock_t nBlks, int flags);
int ftlBmIsBadBlk (FTL_DESC * pFtl, fblock_t blkNo, int option);
int ftlBmFillBlankPages (FTL_DESC * pFtl, FTL_ADDR * pFromAddr,
            fpage_t nPages, MAP_BLK_INFO * pBlkInfo);
int ftlBmIsBlankBlk (FTL_DESC * pFtl, fblock_t blkNo, int flags);
int ftlBmIsBlankPage (FTL_DESC * pFtl, FTL_ADDR * pAddr, int option);
int ftlBmIsFilledBlankPage (FTL_DESC * pFtl, FTL_ADDR * pAddr, int option);
int ftlBmScanPages (FTL_DESC * pFtl, FTL_ADDR * pFromAddr,
            fpage_t nPages, char * pBuf, FTL_ADDR * pOkAddr,
            FTL_ADDR * pBlankAddr, int flags);
int ftlBmCopyPages (FTL_DESC * pFtl, FTL_ADDR * pDestAddr,
            FTL_ADDR * pSrcAddr, fpage_t nPages, int flags);
int ftlBmCopyBlk (FTL_DESC * pFtl, fblock_t destBlk,
            fblock_t srcBlk, int flags);
UINT16 ftlBmBlkNextFpn (FTL_DESC * pFtl, fblock_t blkNo);

extern MTD_DESC * ftlFindMtd (FTL_BM_DESC * pBm, fblock_t blkNo);
int bmIsBlankPage (FTL_BM_DESC * pBm, fblock_t blkNo, 
            fpage_t pageNo);
int ftlBbmCleanup (FTL_BM_DESC * pBm);
int bbmReplace (FTL_BM_DESC * pBm, BBMT_ENTRY * pBbmtEntry, int error);
int bbmBadBlkMap (FTL_BM_DESC * pBm, fblock_t blkNo,
            fblock_t * pReplBlkNo);
int bbmUndoReplace (FTL_BM_DESC * pBm, BBMT_ENTRY * pBbmtEntry, int error);
int copyCheckFunc (FTL_DESC * pFtl, COPY_INFO * pInfo);
int ftlBmCopy (FTL_DESC * pFtl, COPY_INFO * pInfo);
int ftlBmWriteRaw (FTL_BM_DESC * pBm, FTL_ADDR * pFromAddr, 
            size_t dataLen, char * pBuf, int flags);
int ftlBmReadRaw (FTL_BM_DESC * pBm, FTL_ADDR * pFromAddr, 
            size_t dataLen, char * pBuf, int flags);
int ftlBmCheckSeqPgMap (FTL_DESC * pFtl, fblock_t blkNo, fpage_t pageNo,
            int nPages);
int checkBlank (FTL_BM_DESC * pBm, const char * pBuf, size_t len, int flags);
#ifdef FTL_DEBUG
int ftlBmCheckBlankPages (FTL_DESC * pFtl, fblock_t blkNo, fpage_t pageNo,
            int nPages);
int ftlBmCheckAnyBlankPages (FTL_DESC * pFtl, fblock_t blkNo, fpage_t pageNo,
            int nPages);
#endif /* FTL_DEBUG */

#ifdef __cplusplus
}
#endif

#endif /* __INCftlBmh */

