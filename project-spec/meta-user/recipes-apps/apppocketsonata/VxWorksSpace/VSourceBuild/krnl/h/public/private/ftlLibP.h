/* ftlLibP.h - generic ftl private header */

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
18oct13,jxu  cleanup of warnings
04sep13,jxu  fixed incorrect block version issue.
02sep13,jxu  added average age of all data blocks to meta header. 
23aug13,jxu  supported incremental log.
10jul13,jxu  supported clean unmount, and removed group wl info from
             map page and added grp_wl_sort, and supported per-device
             user configurations.
26jun13,jxu  fixed incorrect bits of blkVer in BLOCK_INFO. 
25jun13,jxu  optimized the alignment for the packed structures. 
08jun13,jxu  added page status to oob and few flags 
05jan13,jxu  added debugging tool for tracking lpn mapping and ppn status 
07nov12,jxu  added memory statistics for ftl 
06nov12,jxu  added support of ftl discard feature. 
08nov12,jxu  added more info to ftl identity and added wl info to meta log.
22oct12,jxu  added pFpioReqBmp to support doing mapping for multiple
             non-contiguous page read.
09jul12,jxu  adapted for integration.
18jun12,m_y  added wl related defines.
17may12,x_z  added bm related defines.
15may12,jxu  revised based on internal review.
29feb12,jxu  written.
*/

#ifndef __INCftlLibPh
#define __INCftlLibPh


/* includes */

/*
 * change following includes when the header files are moved to the
 * standard header file location
 */

#include <flash.h>
#include <ftlLib.h>
#include <private/ftlOsIf.h>
#include <private/ftlUtilP.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* defines */

#define FTL_DIAGNOSTIC          /* for diagnostic purpose */
#define FTL_CLEAN_UNMOUNT       /* clean unmount and re-format */
#define FTL_CHECKSUM_META       /* additional checksum for meta data */


/* user configuration bit position */

#define FTL_CACHE_ON            0x1
#define FTL_TASK_ON             0x2
#define FTL_DISCARD_ON          0x4

#define INIT_USER_CONFIG(pFtl) (((pFtl)->usrConfig = 0))

#define ENABLE_CACHE(pFtl) (((pFtl)->usrConfig |= FTL_CACHE_ON))
#define ENABLE_DISCARD(pFtl) (((pFtl)->usrConfig |= FTL_DISCARD_ON))
#define ENABLE_TASK(pFtl) (((pFtl)->usrConfig |= FTL_TASK_ON))

#define IS_CACHE_ENABLED(pFtl) (((pFtl)->usrConfig & FTL_CACHE_ON) != 0)
#define IS_DISCARD_ENABLED(pFtl) (((pFtl)->usrConfig & FTL_DISCARD_ON) != 0)
#define IS_TASK_ENABLED(pFtl) (((pFtl)->usrConfig & FTL_TASK_ON) != 0)

/* 
 * As for some arch like ARM, packing the necessary individual fields of a
 * structure is better for the compiler to optimize for performance.
 * It's also a good practice to defined the fields as self-aligned.
 * Accessing unaligned fields will need execute more memory load/store
 * instructions than aligned access. 
 */
#define _FTL_PACKED __attribute__((packed))
#define _FTL_PACK_ALIGN(bytes) _WRS_PACK_ALIGN(bytes)

/* FTL PIO error defines */

#define FTL_OK                  OK 
#define FTL_ERROR               ERROR   /* -1 */ 
#define FTL_ERR_BLANK           (FTL_ERROR - 1)
#define FTL_BM_ERR_ECC_RECV     (FTL_ERROR - 2) 
#define FTL_BM_ERR_ECC_UNRECV   (FTL_ERROR - 3) 
#define FTL_BM_ERR_ECC_UNRECV_FAKE  (FTL_ERROR - 4) 
#define FTL_BM_ERR_WRITE_FAIL   (FTL_ERROR - 5) 
#define FTL_BM_ERR_ERASE_FAIL   (FTL_ERROR - 6) 
#define FTL_BM_ERR_DEV_FAIL     (FTL_ERROR - 7) 

#define FTL_VER_1_0             0x0100
#define FTL_VER                 FTL_VER_1_0
#define FTL_MAGIC               0x5ACF  /* 'W' 'R' 'F' 'T' 'L' */
#define FTL_MODE_RDONLY         0x1
#define FTL_MODE_RW             0x2

#define FTL_UNMOUNT_REFCNT       0x100000

#define FTL_OOB_VER             0

#define FTL_FLAG_MNT_ERR_LOG    0x1
#define FTL_FLAG_MNT_ERR_MAP    0x2
#define FTL_FLAG_CHKSUM_META    0x4

#define META_FLAG_CHKSUM        0x1

/* the first two blocks for saving ftl identify */

#define FTL_NUM_ID_BLKS         2 

#define FTL_INVALID_LBN         UINT_MAX        /* maximum of fblock_t */ 
#define FTL_LBN_ANY             UINT_MAX        /* maximum of fblock_t */ 
#define FTL_INVALID_LPN         USHRT_MAX       /* maximum of fpage_t*/ 
#define FTL_INVALID_PBN         FTL_INVALID_LBN
#define FTL_INVALID_PPN         FTL_INVALID_LPN
#define FTL_INVALID_GRP         USHRT_MAX       /* maximum of UINT16 */
#define FTL_INVALID_AGE         UINT_MAX        /* maximum of blk_age_t */

#define INVALID_BLKINFO {FTL_INVALID_PBN, 0, 0}
#define INVALID_ADDR {FTL_INVALID_PBN, FTL_INVALID_PPN, 0}
#define ASSIGN_ADDR(pDestAddr, blkno, pageno, off) {  \
                ((FTL_ADDR *)(pDestAddr))->blkNo  = blkno;        \
                ((FTL_ADDR *)(pDestAddr))->pageNo = pageno;       \
                ((FTL_ADDR *)(pDestAddr))->offset = off;          \
            }

#define COPY_ADDR(destAddr, srcAddr) {        \
            ((FTL_ADDR *)(destAddr))->blkNo  = ((FTL_ADDR *)(srcAddr))->blkNo;  \
            ((FTL_ADDR *)(destAddr))->pageNo = ((FTL_ADDR *)(srcAddr))->pageNo; \
            ((FTL_ADDR *)(destAddr))->offset = ((FTL_ADDR *)(srcAddr))->offset; \
            }

/* ftl block types */

#define FTL_BLK_TYPE_BLANK      0x0
#define FTL_BLK_TYPE_META       0x1
#define FTL_BLK_TYPE_DATA       0x2
#define FTL_BLK_TYPE_ASSOC      0x3
#define FTL_BLK_TYPE_REPL       0x4

#define FTL_NUM_ASSOC_BLK_LIST  4       /* # of used associate block lists */

/* 
 * # of house keeping blocks for operations that could release
 * more blocks.
 */ 

#define FTL_NUM_HSKP_BLOCK      1       

#define FTL_FLAG_CHECK_FACTORY_BLK      0x1

#define FTL_BLANK_PATTERN       ((char)0xFF)

/* 
 * maximum number of associate block for one logical block, it's 
 * configurable and currently it is defined as one. Its up limit
 * is 8.  
 */

#define FTL_CFG_MAX_ASSOC_BLKS_PER_LBN  4      /* maximum configurable # */
#define FTL_MAX_ASSOC_BLKS_PER_LBN      1      /* current # */

#define FTL_DEV_NAME_LEN_MAX    64      /* FTL device name */

#define FTL_EMPTY_PATTERN       0       /* pattern for filling blank page */

/* flash I/O flags */

#define FIO_READ                0x1     /* read operation */
#define FIO_WRITE               0x2     /* write operation */
#define FIO_DATA                0x4     /* access data area of nand page */
#define FIO_OOB                 0x8     /* access oob area of nand page */
#define FIO_SG                  0x10    /* scatter-gather I/O */ 
#define FIO_INCACHE             0x20    /* in cache */
#define FIO_SYNC                0x40    /* synchronously I/O */
#define FIO_EXCL                0x80    /* involved in exclusive operation */   
#define FIO_BUSY                0x100   /* in busy */
#define FIO_DONE                0x200   /* completed */
#define FIO_ERROR               0x400   /* error */
#define FIO_DISCARD             0x1000  /* discarded fpio */
#define FIO_NO_MAPPING          0x2000  /* do not need mapping */
#define FIO_STOP_BLANK          0x4000  /* stop when meet blank page */ 
#define FIO_STOP_ERROR          0x8000  /* stop when meet error page */
#define FIO_STOP_OK             0x10000 /* stop when meet a good page */
#define FIO_WRITE_VERIFY        0x20000 /* verify data after write */ 
#define FIO_BUF_DMA             0x40000 /* DMA buffer */
#define FIO_CHECK_BLANK         0x80000 /* check blank page */
#define FIO_CHECK_FILLED_BLANK  0x100000 /* check filled blank page */
#define FIO_BYPASS_BBMT         0x200000 /* bypass checking bbmt */
#define FIO_BYPASS_BBM_ERR_HDL  0x400000 /* bypass bbm error handling */
#define FIO_COPY_FULL_PAGE      0x800000 /* copy full page */
#define FIO_RAW_DATA            0x1000000 /* read or write data without ecc */
#define FIO_WR_ERR_PAGE         0x2000000 /* write error page */
#define FIO_USER_DATA           0x4000000 /* read or write user data */
#define FIO_META_DATA           0x8000000 /* read or write meta data */
#define FIO_COPY_UPDATE_OOB     0x10000000 /* should update oob when copying */
#define FIO_TEST_BLANK_BITS     0x80000000 /* TEMP for testing */

/* lbn control flags */

/* #define LBN_FLAG_READ           0x1 */
/* #define LBN_FLAG_WRITE          0x2 */
#define LBN_FLAG_NO_WAIT        0x4
#define LBN_FLAG_EXCL           0x8

/* ftl ioctl commands */

#define FTL_IOC_DISCARD         0x1     /* discard command */
#define FTL_IOC_FLUSH           0x2     /* flush command */

#define FLUSH_OPT_NONE          0x0     /* no additional option */
#define FLUSH_OPT_ONE_BLK       0x1     /* flush one block */
#define FLUSH_OPT_RECLAIM_FBIO  0x2     /* reclaim fbio instance for use */

#define FTL_EMBED_FPIOS         1       /* how many fpios are embedded in a */
                                        /* fbio */

#define FTL_WL_OPT_ONCE         0x1

#define FTL_AGE_MAX             UINT_MAX
#ifdef FTL_DEBUG
#define FTL_AGE_THRESH_DELTA    100 
#else
#define FTL_AGE_THRESH_DELTA    100
#endif  /* FTL_DEBUG */

#define FTL_WL_LAZY_MODE_ENABLED FALSE 

/* meta data type */

#define FTL_META_TYPE_LOG       0x5A
#define FTL_META_TYPE_MAP       0xAC
#define FTL_SIZE_META_LOG(pFtl) (pFtl->pBm->pageSize)

#define META_HEADER_SIZE        (ROUND_UP (sizeof (FTL_META_HEADER), 4))

#define MAP_FLAG_INVALID        0x1     /* invalid block map */
#define MAP_FLAG_DIRTY          0x2     /* dirty block map */

/* flags for associate blocks management */

#define FTL_ASSOC_FLAG_READ     0x1     /* read */
#define FTL_ASSOC_FLAG_WRITE    0x2     /* write */
#define FTL_ASSOC_FLAG_RANDOM   0x4     /* random I/O */
#define FTL_ASSOC_FLAG_SEQ      0x8     /* sequential I/O */
#define FTL_ASSOC_FLAG_FULL     0x10    /* sequential I/O */
#define FTL_ASSOC_FLAG_USED     0x100   /* used */
#define FTL_ASSOC_FLAG_GC       0x200   /* allow GC */
#define FTL_ASSOC_FLAG_ALLOC    0x400   /* dynamically allocated */
#define FTL_ASSOC_FLAG_INVALID  0x800   /* invalid page mapping in RAM */ 
#define FTL_ASSOC_FLAG_HSKP     0x1000  /* house-keeping associate blocks */
#define FTL_ASSOC_FLAG_IN_TREE  0x2000  /* in tree */

#define IS_ASSOC_BLK_HSKP(pAssocBlk)    \
            IS_FLAG_SET((pAssocBlk)->flags, FTL_ASSOC_FLAG_HSKP)  

/* flags for background service task */

#define FTL_SVC_REQ_WL          0x1
#define FTL_SVC_REQ_GC          0x2
#define FTL_SVC_REQ_DISCARD     0x4
#define FTL_SVC_REQ_FLUSH       0x8

#define DISCARD_FLAG_ONE_BLK    0x1     /* discard one block */

/* macros help check the status of a fbio */

#define IS_FBIO_FREE(pFbio)       ( \
        (DLL_EMPTY (&(pFbio)->cleanFpioList)) && \
        (DLL_EMPTY (&(pFbio)->dirtyFpioList))    \
        )
#define IS_FBIO_CLEAN(pFbio)       ( \
        (!DLL_EMPTY (&(pFbio)->cleanFpioList)) && \
        (DLL_EMPTY (&(pFbio)->dirtyFpioList))    \
        )
#define IS_FBIO_DIRTY(pFbio)       ( \
        !DLL_EMPTY (&(pFbio)->dirtyFpioList)    \
        ) 

/* macros help get the container structure through a member of it */

#define CONTAINER_OF(ptr, type, member) \
                ((type*)((char *)(ptr) - OFFSET(type,member)))

#define DL_NODE_TO_BM_DESC(pNode) ((FTL_BM_DESC *)(pNode))
#define DL_NODE_TO_LBN_CTRL(node)       \
                CONTAINER_OF((node), struct lbn_ctrl_entry, listNode)
#define NODE_TO_FBIO(node)              \
                CONTAINER_OF((node), struct ftl_bio, listNode)
#define NODE_TO_FPIO(node)              \
                CONTAINER_OF((node), struct ftl_pio, fpioNode)
#define NODE_TO_MP_BUF(pNode)           \
                CONTAINER_OF(pNode, struct mp_buf_info, node)
#define NODE_TO_PG_MAP(pNode)           \
                CONTAINER_OF(pNode, struct lbn_pg_map, listNode)
#define DL_NODE_TO_ASSOC_BLK(pNode)     \
                CONTAINER_OF(pNode, struct assoc_blk_entry, listNode)
#define AVL_NODE_TO_ASSOC_BLK(pNode)    \
                CONTAINER_OF(pNode, struct assoc_blk_entry, avlNode)
#define AVL_NODE_TO_DISCARD_NODE(pNode)    \
                CONTAINER_OF(pNode, struct ftl_discard_node, avlNode)
#define DL_NODE_TO_DISCARD_NODE(pNode)     \
                CONTAINER_OF(pNode, struct ftl_discard_node, listNode)

#define ASSOC_HEAD(pPgMap)     ((pPgMap)->pAssocBlks)
#define ASSOC_TAIL(pNode, pHead)  do { \
                for (pNode = pHead; pNode->pNext != NULL; pNode = pNode->pNext); \
            }while(0)
#define ASSOC_NEXT(pNode)     ((pNode)->pNext)
#define ASSOC_FOREACH(pNode, pHead)             \
        for (((pNode) = (pHead));               \
             ((pNode) != NULL);                 \
             ((pNode) = (pNode)->pNext))

/* 
 * block version convention:
 * 1. Version is composed of major and minor version.
 * 2. The block which has lower major version is data block, otherwise
 *    it is associate block.
 * 3. For blocks which have equal major version, the block with higher
 *    minor version contains newer data.
 */

#define BLK_VER_MASK    ((0x1 << 6) - 1)
#define MAJOR_VER_MAX   0x7
#define MINOR_VER_MAX   0x7
#define MAJOR_VER_MASK  0x7
#define MINOR_VER_MASK  0x7
#define MINOR_VER_SHIFT 0       /* low 3 bits for minor version */
#define MAJOR_VER_SHIFT 3       /* high 3 bits for major version */
#define MAJOR_VER(ver)  (((ver) >> MAJOR_VER_SHIFT) & MAJOR_VER_MASK)
#define MINOR_VER(ver)  (((ver) >> MINOR_VER_SHIFT) & MINOR_VER_MASK)
#define MAJOR_VER_SET(ver, value) ((ver) = ((((value) << MAJOR_VER_SHIFT) | \
                (MINOR_VER(ver) << MINOR_VER_SHIFT)) & BLK_VER_MASK))
#define MINOR_VER_SET(ver, value) ((ver) = ((((value) << MINOR_VER_SHIFT) | \
                (MAJOR_VER(ver) << MAJOR_VER_SHIFT)) & BLK_VER_MASK))
#define MAJOR_VER_INC(ver) \
                MAJOR_VER_SET(ver, ((MAJOR_VER (ver) + 1) & MAJOR_VER_MASK));
#define MINOR_VER_INC(ver) \
                MINOR_VER_SET(ver, ((MINOR_VER (ver) + 1) & MINOR_VER_MASK));
#define MAJOR_VER_DEC(ver) \
                MAJOR_VER_SET(ver, ((MAJOR_VER (ver) - 1) & MAJOR_VER_MASK));
                                    /* for use by recovering */

#define MAJOR_VER_COMPARE(ver1, ver2) \
                blkVerCompare(ver1, ver2, TRUE)
#define MINOR_VER_COMPARE(ver1, ver2) \
                blkVerCompare(ver1, ver2, FALSE)

#define OOB_BLK_VER(pOob) (pOob->blkVer & BLK_VER_MASK)

/* maximum blocks to be written by a single fpio */

#define FPIO_MAX_WR_BLKS        3       /* a data block and two associate */
                                        /* block */

#ifdef FTL_DEBUG
#define FTL_DBG_FLAG_REBOOT_HINT 0x1
#endif /* FTL_DEBUG */

/* typedefs */

/* ftl memory budget */

typedef enum mem_budget_t
    {
    MEM_BDGT_TIGHT = 0,
    MEM_BDGT_MODEST,
    MEM_BDGT_ABUNDANT
    }MEM_BUDGET_T;

/* ftl oob type */

typedef enum flt_oob_type
    {
    FTL_OOB_TYPE_LARGE = 1,
    FTL_OOB_TYPE_SMALL
    }FTL_OOB_TYPE;

/* flash specific type definitions */

typedef UINT64  faddr_t; /* general size type */
typedef UINT32  fblock_t; /* block address type */
typedef UINT16  fpage_t;/* page address in block */
typedef UINT32  fbsize_t; /* block size type */
typedef UINT16  fpsize_t;/* page size type */

typedef UINT32  blk_age_t;      /* type of age of block */

typedef long    FTL_IOCTL_ARG_T;/* ftl ioctl third argument type */

/* flash block I/O completion function type */

struct ftl_bio;         /* forward declaration */
struct ftl_desc;        /* forward declaration */

typedef void (*FTL_BIO_DONE_FUNC)(struct ftl_bio *);
typedef int (*FTL_BLKDEV_CREATE_FUNC) (struct ftl_desc * pFtlDesc);
typedef int (*FTL_BLKDEV_DELETE_FUNC) (void * pBlkDev);

/* index of each sub-section of a log page */

typedef enum log_index
    {
    /*
     * Each item in this enumeration is defined as an index for a
     * sub-section of a mapping page.
     */

    LOG_IDX_EVENT = 0,  /* event */
    LOG_IDX_MP,         /* map page address table */
    LOG_IDX_ASSOC_BLK,  /* associate blocks */
    LOG_IDX_ASSOC_AGE,  /* age of associate blocks */
    LOG_IDX_MAX         /* maximum number of sections of mapping page */
    }LOG_INDEX;

typedef enum mp_index
    {

    /*
     * Each item in this enumeration is defined as an index for a
     * sub-section of a mapping page.
     */

    MP_IDX_MAP = 0,     /* mapping info */
    MP_IDX_BLK_INFO,    /* block info */
    MP_IDX_MAX          /* maximum number of sections of mapping page */
    }MP_INDEX;

/* ftl device status */

typedef enum ftl_status
    {
    FTL_STATUS_INVALID = 0,
    FTL_STATUS_FORMAT,  /* in formatting */
    FTL_STATUS_MOUNT,   /* in mounting */
    FTL_STATUS_UNMOUNT, /* is being unmounted */
    FTL_STATUS_READY,   /* ftl device ready */
    FTL_STATUS_RDONLY,  /* ftl device is read only */
    FTL_STATUS_PANIC,   /* ftl panic happened */
    FTL_STATUS_RECOVER  /* in recovering */
    }FTL_STATUS;

/* flash address type */

typedef struct ftl_addr_t
    {

    /*
     * Defining a uniform flash address type in a structure is more
     * flexible for future modification and evolvement.
     */

    fblock_t    blkNo;          /* global block number */
    fpage_t     pageNo;         /* page number in block */

    /*
     * The offset is supposed to be 0, which denotes the starting position
     * of a flash page, if the block layer uses the page size as its own
     * block size. However, there might be user of FTL which uses
     * fixed block size (e.g. 512 bytes) that is less than the flash page
     * size. To satisfy this kind of users, FTL has to support small block
     * emulation. As described in FTL-REQ-6 of the HLD, Wind River FTL will
     * support block emulation scaling from 512 byte to native page size
     * (e.g. 4KB) of SLC chips (in 1st phase) and other flash types (in
     * 2nd phase).
     */

    fpsize_t    offset;         /* offset in page */
    }FTL_ADDR;

/* flash page aligned address type */

typedef struct ftl_addr_al_t
    {
    fblock_t    blkNo;          /* global block number */
    fpage_t     pageNo;         /* page number in block */
    }_FTL_PACK_ALIGN(2) FTL_ADDR_AL;

typedef struct ftl_lbn_ctrl_pool        /* lbn control pool */
    {
    FTL_LOCK_T  lbnTrLock;              /* lbn control tree access lock */
    AVL_TREE    lbnTree;                /* lbn control tree */
    int         lbnCnt;                 /* current # of lbn controls */ 
    int         maxResLbnCtrls;         /* maximum # of resident lbn controls */
    DL_LIST     freeLbnCtrlList;        /* free fbio list */
    FTL_SEM_T   semCntFreeLbnCtrl;      /* count semphore tracking free fbios */
    }FTL_LBN_CTRL_POOL;

typedef struct fbio_pool                /* fbio pool */
    {
    FTL_LOCK_T  lock;                   /* lbn control tree access lock */
    int         fbioCnt;                /* current # of lbn controls */ 
    int         maxResFbios;            /* maximum # of resident lbn controls */
    DL_LIST     freeFbioList;           /* free fbio list */
    FTL_SEM_T   semCntFreeFbio;         /* count semphore tracking free fbios */
    }FBIO_POOL;

/* logical block access control */

typedef struct lbn_ctrl_entry
    {
    AVL_NODE    avlNode;        /* AVL tree node, must be first */
    fblock_t    lbn;            /* logical block number, as key */
    FTL_LOCK_RW_T       lbnRwLock;      /* read/write lock */
    FTL_ATOMIC32_T      refCnt;         /* reference count */
    DL_NODE             listNode;       /* free list node */
    }LBN_CTRL_ENTRY;

/* page mapping entry of associate blocks */

typedef struct assoc_pme
    {

    /*
     * This structure is for locating the physical page in a associate 
     * block for a page number of a logical block.
     */

    fblock_t    assocPbn;       /* pbn of associate block */
    fpage_t     ppn;            /* page number in a associate block */
    }ASSOC_PME;

typedef struct map_blk_info     /* block info of a physical block */
    {
    fblock_t   blkNo;  /* block number */
    UINT8      blkVer; /* block version */
    UINT32     blkAge; /* block age */
    }MAP_BLK_INFO;

typedef struct fpio_map_info    /* fpio mapping private info */ 
    {
    FTL_ADDR    physAddr;   /* physical address */ 
    ASSOC_PME * pPmeTbl;    /* associate page mapping */
    void *      pBlkInfo;   /* physical block info for this fpio */

    /* 
     * Following is a convention to use the mapping information 
     * contained in this structure.
     *
     * if (pPmeTbl is NULL) {
     *     use physAddr directly. 
     *     if (pFpio->fpioLen > pageSize) {
     *         physAddr implies multiple consecutive physical addresses.
     *     }
     * } else {
     *     use the pPmeTbl to get the physical address for each page.
     * }
     */

    }FPIO_MAP_INFO;

/* flash page I/O */

typedef struct ftl_pio
    {
    DL_NODE     fpioNode;       /* node of pioList of ftl_bio */ 

    /*
     * As an optimization, multiple page I/O requests might be
     * combined into one if their I/O address are consecutive
     * as well as their buffers. This optimization is only applied
     * to the case without cache. In the case of cache enabled,
     * the fpioLen is always equal to the size of one page.
     */

    FTL_ADDR    fromAddr;       /* starting flash I/O address */

    size_t      dataLen;        /* length of data */
    fpage_t     nPages;         /* will be figured out by LBD */
    char *      pBuf;           /* data buffer */
    char *      pOobBuf;        /* oob buffer */

    FPIO_MAP_INFO mapInfo;        /* mapping private information */

    int         flags;          /* FPIO_DIRTY, FPIO_CLEAN, FPIO_READ, */
                                        /* FPIO_WRITE, FPIO_BUSY, FPIO_DONE, */
                                        /* FPIO_DISCARD, FPIO_ERROR */
    int         error;          /* error status of the operation */
    FTL_ADDR    errAddr;        /* which page caused I/O failure */

    void *      owner;          /* owner of this pio, not used */
    }FTL_PIO;

/* flash block I/O */

typedef struct ftl_bio
    {
    DL_NODE             listNode;       /* node of fbio list */
    LBN_CTRL_ENTRY *    pLbnCtrl;       /* under which lbn control */

    /*
     * Since the main mapping method of this FTL is block oriented, it
     * would be better to support I/O operations on a block basis in
     * terms of performance because it saves cost of translation.
     */

    fblock_t            lbn;            /* logical block number */
    DL_LIST             fpioList;       /* requested page I/O list */
    DL_LIST *           pReqFpioList;   /* pointer to the fpio list */
    int                 fbioFlags;      /* FBIO_READ, FBIO_WRITE, FBIO_CACHE, */
                                        /* FBIO_DISCARD, FBIO_EXCL, ... */
    int                 error;          /* error status of the operation */
    FTL_BIO_DONE_FUNC   fbioDone;       /* Completion function of block I/O */

    /*
     * embedded a number of fpios in fbio to avoid dynamically
     * allocating memory too frequently. It's only useful in
     * the case of cache bypassed or disabled.
     */

    struct ftl_pio      fpios[FTL_EMBED_FPIOS]; /* embedded fpios */

    /*
     * cache-specific info. If cache module is disabled, following stuff
     * is meaningless. However, to simplify things, we don't pack them
     * into a seperate strcutrue.
     */

    FTL_ATOMIC32_T      hitCnt;         /* counter of cache hit */

    /*
     * We purge the dirty data in cache in block granularity.
     * The dirty blocks are linked in a LRU (least recently used)
     * fashion. When purging a dirty block, all of its dirty pages
     * will be written to the underlying flash device synchronously.
     */

    DL_LIST             dirtyFpioList;  /* dirty page I/O list */
    DL_LIST             cleanFpioList;  /* clean page I/O list */

    /*
     * We use a bitmap to track the cached fpios in above lists. With
     * the bitmap, we can determine which pages are cached and what
     * are not without searching the list each time we want to know
     * that.
     */

    UINT8 *             pFpioBmp;       /* bitmap of fpios */
    UINT8 *             pFpioReqBmp;    /* bitmap of requested fpios */
    int                 bmpLen;         /* length of fpio bit map in bytes */

    }FTL_BIO;

/* ftl discard support */

typedef struct ftl_discard_info         /* ftl discard information */
    {
    faddr_t  startAddr;      /* starting address */
    size_t  length;         /* length in bytes */
    }FTL_DISCARD_INFO;

typedef struct ftl_blk_discard_info     /* ftl block discard information */
    {
    fblock_t    blkAddr;        /* block number */
    fbsize_t    blkOff;         /* offset in block */
    fbsize_t    length;         /* length in bytes */
    void *      pMpInfo;        /* mapping private info */
    }FTL_BLK_DISCARD_INFO;

typedef struct ftl_discard_node         /* ftl block discard node */
    {
    AVL_NODE    avlNode;        /* node in the tree */

    fblock_t    lbn;            /* block number */
    void *      pDiscardBmp;    /* bitmap tracking discarded pages */
    UINT16      nDiscardedPages;
    UINT16      flags;          /* flags for the node */ 
    DL_NODE     listNode;       /* node for fully/partially discarded block */
    FTL_TICK_T  birthTime;      /* when the node came to live */ 
    }FTL_DISCARD_NODE;

typedef struct ftl_discard              /* ftl discard support */ 
    {
    FTL_LOCK_T  discardLock;            /* discard lock */
    int         curCnt;                 /* current # of discard nodes */ 
    int         maxResCnt;              /* maximum # of resident discard */
                                        /* nodes */
    int         discardBmpLen;          /* bmp length of discarded pages in */
                                        /* a block */
    AVL_TREE    discardTree;            /* discard tree */ 
    FTL_LOCK_T  discardListLock;        /* discarded block list lock */
    DL_LIST     discardList;            /* discard block list */
    FTL_TICK_T  birthTime;              /* when it comes to live */
    }FTL_DISCARD;

typedef struct ftl_mark_t
    {
    /* 
     * ftl erased block or written pages should always contains following 
     * mark
     */

    UINT8       ftlMark;        /* one byte is enough to mark if the block */
                                /* is touched by ftl or not */
    }_FTL_PACK_ALIGN(1) FTL_MARK_T;

/* ftl managed oob data, 9 bytes in total, suitable for <= 16bytes size oob */

typedef struct ftl_oob_small
    {
    UINT32      oobVer  : 2;    /* OOB version for future evolvement */
    UINT32      blkVer  : 6;    /* block version */
    UINT32      lbn     : 24;   /* logic block number */
    UINT32      lpn     : 10;   /* logic page number */
    UINT32      age     : 18;   /* age of block */
    UINT32      blank   : 1;    /* blank page */
    UINT32      error   : 1;    /* ecc unrecoverable error page */
    UINT32      resv    : 2;    /* reserved */
    UINT8       crc8;           /* checksum of oob */
    }_FTL_PACK_ALIGN(1) FTL_OOB_SMALL;

#define SMALL_OOB_INVALID_LBN   (FTL_INVALID_LBN & 0xFFFFFF)    /* 24bits */
#define SMALL_OOB_INVALID_LPN   (FTL_INVALID_LPN & 0x3FF)       /* 10bits */
#define SMALL_OOB_INVALID_AGE   (FTL_INVALID_AGE & 0x3FFFF)     /* 18bits */
#define SMALL_OOB_LBN(pOob) \
            ((pOob)->lbn == SMALL_OOB_INVALID_LBN ? FTL_INVALID_LBN : (pOob)->lbn)
#define SMALL_OOB_LPN(pOob) \
            ((pOob)->lpn == SMALL_OOB_INVALID_LPN ? FTL_INVALID_LPN : (pOob)->lpn)
#define SMALL_OOB_AGE(pOob) \
            ((pOob)->age == SMALL_OOB_INVALID_AGE ? FTL_INVALID_AGE : (pOob)->age)

/* ftl managed OOB data, 16 bytes in total, suitable for >= 16bytes size OOB */

typedef struct ftl_oob_large
    {
    UINT8       oobVer  : 2;    /* OOB version for future evolvement */
    UINT8       blkVer  : 6;    /* block version */
    UINT8       blank   : 1;    /* blank page */
    UINT8       error   : 1;    /* ecc unrecoverable error page */
    UINT8       resv1   : 6;    /* reserved */
    UINT8       resv2[2];       /* reserved */
    UINT32      lbn;            /* logic block number */
    UINT16      lpn;            /* logic page number in block */
    UINT32      age;            /* age of block */
    UINT8       resv3;          /* reserved */
    UINT8       crc8;           /* checksum of oob */
    }_FTL_PACK_ALIGN(1) FTL_OOB_LARGE;

typedef struct ftl_oob_ram      /* ftl oob in ram */
    {
    UINT8       oobVer; /* OOB version for future evolvement */
    UINT8       blkVer; /* block version */
    fblock_t    lbn;    /* logic block number */
    fpage_t     lpn;    /* logic page number in block */
    blk_age_t   age;    /* age of block */
    BOOL        blank;  /* blank page */
    BOOL        error;  /* error page */
    }FTL_OOB_RAM;

/* meta page header */

typedef struct ftl_meta_header
    {
    /* All meta pages are started with this header. */

    UINT32      magic;          /* magic number to identify a valid */
                                /* meta page */
    UINT8       flags;          /* set to 0 if no flags */
    UINT8       type;           /* meta data or log */
    UINT16      grpNo;          /* group number */
    UINT64      seqNo;          /* sequence number, useless */ 
    UINT32      ageAvg;         /* average age of all data blocks */
    UINT32      privBlk;        /* privious block */
    UINT8       reserved[4];    /* reserved */
    UINT32      dataLen;        /* data length of a map page */
    UINT32      dataChksum;     /* checksum of data part */
    UINT32      hdrChksum;      /* checksum of header and data */ 
    }_FTL_PACK_ALIGN(4) FTL_META_HEADER; /* 40 bytes in total */

typedef enum merge_t    /* merge type */
    {
    MERGE_INIT = 0,
    MERGE_FULL,
    MERGE_COPY,
    MERGE_SWITCH,
    MERGE_DISCARD,
    }MERGE_T;

typedef enum log_event
    {
    LOG_EVENT_INIT      = 0x11,
    LOG_EVENT_GC        = 0x22,
    LOG_EVENT_WL        = 0x33,
    LOG_EVENT_DISCARD   = 0x44,
    LOG_EVENT_RECOVER   = 0x55
    }LOG_EVENT;

typedef struct ftl_meta_log     /* ftl meta log */
    {
    /* info for the GC & WL operation that should be logged */

    UINT8       event;          /* what event is this log for */
    UINT8       subEvent;       /* the more specific event */
    UINT16      pad;            /* reserved */
    UINT32      lbn;            /* on which lbn the event happens */
    UINT32      dataPbn;        /* pbn for the lbn */
    UINT32      dataBlkAge;     /* age of the pbn */
    UINT32      assocIdx;       /* index of the assoc blk involved */
    UINT32      assocPbn;       /* pbn of the assoc blk involved */
    UINT32      nOldAssocBlks;  /* # of additional involved assoc blk */
    UINT32      oldAssocBlks[FTL_CFG_MAX_ASSOC_BLKS_PER_LBN];

    /* the last mp update address, saved for being checked by the next mount */

    UINT32      mpBlkNo;
    UINT32      mpPageNo;
#ifdef obsolete 
    FTL_ADDR_AL mpUpdateAddr; /* map page address for the update */ 
#endif

    /* wl info */

    UINT32      ageAvg;         /* average age */
    UINT32      wlAgeThresh;    /* weal-leveling threshold */
    UINT64      ageSum;         /* current total age of all blocks */
    UINT8       reserved[4];    /* reserved */
    }_WRS_PACK_ALIGN(4) FTL_META_LOG;   /* 60 bytes in total */

typedef struct grp_wl_info              /* wl info for each group */
    {
    UINT32      youngestBlk;        /* youngest block index */
    UINT32      youngestAge;        /* age of the block */
    UINT32      ageSum;             /* total age of this group */
    }GRP_WL_INFO;

typedef struct grp_wl_sort
    {
    fblock_t *  pBlks;          /*  blocks of the group */
    blk_age_t * pBlkAge;        /* age of each blocks */
    int         startIdx;       /* where to start sorting */
    int         endIdx;         /* when to stop sorting */

    /* youngest block in the current range of blocks */ 

    fblock_t    youngBlk;
    blk_age_t   youngAge;
    }GRP_WL_SORT;

typedef struct meta_log_buf_info        /* meta log buf info in RAM */ 
    {
    char *              pBuf;           /* the address of raw buffer */
    FTL_META_HEADER *   pLogHeader;     /* pointer to the log header */
    FTL_META_LOG *      pMetaLog;       /* pointer to the meta log */
    FTL_ADDR_AL *       pGrpMpAddr;     /* pointer to the grp/mp table */
    UINT32 *            pAssocBlks;     /* pointer to the associate blocks */
    UINT32 *            pAssocAge;      /* pointer to the associate block age */
    }META_LOG_BUF_INFO;

/* meta page layout entry */

typedef struct meta_layout
    {
    UINT32      offset;         /* offset of a section */
/*    UINT16      length;   */      /* length of a section, not necessary */
    }META_LAYOUT;

typedef struct block_info       /* block info saved with block map */
    {
    UINT32      blkVer  : 6;    /* both major and minor block version */ 
    UINT32      resv    : 2;    /* reserved */ 
    UINT32      age     : 24;   /* block age */
    }_FTL_PACK_ALIGN(1) BLOCK_INFO;

/* pointers to mapping page buffer */

typedef struct mp_buf_info
    {
    DL_NODE     node;           /* node in a used or free list */
    DL_NODE     hashNode;       /* node in hash list */
    UINT16      grpNo;          /* group number */
    UINT16      nDataBlks;      /* # of data blocks in this group */
    int         flags;          

    /*
     * This structure contains various pointers which point to each
     * sub-sections of a mapping page that are loaded in RAM. They
     * should be filled based on the layout of a mapping page (see
     * struct mp_layout).
     */

    FTL_META_HEADER *   pHeader;        /* pointer to meta page header */
    fblock_t *          pBlkMap;        /* pointer to mapping array which is
                                         * indexed with LBN */
    BLOCK_INFO *        pBlkInfo;       /* age, version, etc */
    }MP_BUF_INFO;

/* address of meta pages for a group */

typedef struct grp_mp_info
    {

    /*
     * This structure contains the address of the valid mapping and age
     * pages for a group. Each group should have a entry of this structure
     * type.
     */

    FTL_ADDR_AL *       pMpAddr;        /* valid physical address of map page */
    MP_BUF_INFO *       pMpBuf;         /* It's NULL if not loaded */
    }GRP_MP_INFO;

/* associate block list entry */

typedef struct assoc_blk_entry
    {

    /*
     * This structure is for managing associate blocks. Each associate
     * block has a entry of this type to track the next free page
     * number of the associate block and to which logical block is this
     * associate block is assigned.
     */

    fblock_t    assocPbn;       /* pbn of associate block */
    fblock_t    lbn;            /* logical block number */
    fpage_t     nextFpn;        /* next free page number, equal to */
                                        /* # of pages per block if full block */
    UINT16      index;          /* index of this associate block in */
                                        /* the global array */
    UINT8       blkVer;         /* block version */
    int         flags;          /* FTL_ASSOC_FLAG_XXX */
    void *      pPgMap;         /* page mapping of the lbn */

    /* 
     * used associate blocks are roughly sorted by used-space ratio. This
     * faciliate choosing the appropriate associate blocks for GC.
     */
    
    DL_NODE             listNode;       /* node in associate blocks list */
    DL_LIST *           pList;          /* which list this used node resides */

    /* 
     * avl self balanced tree for fast searching since finding the
     * associate block for a lbn is a much intensive operation. 
     * Besides, using avl tree has better scalability than list.
     * On the negative side, each tree node consumes 4 more bytes 
     * than each list node and there needs a little more effort in 
     * balancing the tree.
     */ 

    AVL_NODE            avlNode;        

    struct assoc_blk_entry * pNext;     /* list of blocks that are associated */
                                        /* with the same lbn */
    }ASSOC_BLK_ENTRY;

/* the page mapping for a logical block */

typedef struct lbn_pg_map
    {

    /*
     * The page mapping are maintained in associate block cache on
     * the LBN basis. Which means that either all the page mapping
     * of a LBN are loaded in associate block cache or none of them
     * are loaded. 
     */

    fblock_t  lbn;        /* logical block number */
    ASSOC_BLK_ENTRY * pAssocBlks; /* pointer to associate blocks */
                                /* associate blocks */
    ASSOC_PME *     pPmeTbl;    /* page mapping array which is indexed by LPN */
    int             index;      /* index of the next free slot of */
                                /* <pAssocBlks>, */
                                /* it is also used as version of the */
                                /* associate blocks. */
    int             flags;      /* RANDOM, SEQ (initial), BUSY (prevent it */
                                /* from reclaimed) */
    FTL_ATOMIC32_T  refCnt;     /* reference count */
    FTL_LOCK_T      lock;       /* lock it when the page map is being loaded */
                                /* have to protect the page mapping */
    DL_NODE         listNode;   /* node of the list of associate block cache */
    }LBN_PG_MAP;

#ifdef FTL_DEBUG
    struct map_track {                  /* for debug purpose */
        UINT32          pbn;            /* track the page map */
        UINT16          ppn;            /* track the page map */
        UINT16          status;         /* page status */ 
    };

#define FTL_DBG_PPN_BLANK       0xFF
#define FTL_DBG_PPN_FILL_BLANK  0xAA
#define FTL_DBG_PPN_VALID       0x55

    struct ppn_track {                  /* for debug purpose */
        UINT8           status;         /* blank, filled blank, valid */
    };
#endif /* FTL_DEBUG */

/* information of a hot block */

typedef struct hot_blk_info
    {
    fblock_t    lbn;        /* logical block number corresponding to pbn */
    fblock_t    pbn;        /* physical block number of the hot data */
                                /* block */
    fpage_t     nextFpn;    /* next free page number */
    UINT8       blkVer;     /* block version of data block */
    blk_age_t   blkAge;     /* block age */
    }HOT_BLK_INFO;

/* ftl managed device descriptor */

typedef struct ftl_desc
    {
    UINT32              ftlVersion;     /* ftl version */
    UINT32              ftlMagic;       /* magic number: FTL_MAGIC */
    int                 ftlMode;        /* rw or rdonly */
    int                 status;         /* current status of the ftl device: */
                                        /* FTL_INIT, FTL_READY, FTL_RECOVER */

#ifdef FTL_CLEAN_UNMOUNT
    FTL_ATOMIC32_T      refCnt;         /* # of active users of the ftl device */
    FTL_SEM_T           unmountSem;     /* wait on it for clean unmount */
#endif /* #ifdef FTL_CLEAN_UNMOUNT */

    UINT32              ftlFlags;       /* various flags */

    /* format options */

    UINT32              options;        /* user configurable options */

    /* user configurations */

    MEM_BUDGET_T        memBudget;      /* configurable memory budget */
    size_t              dataCacheSize;  /* configurable data cache size */
    UINT32              usrConfig;      /* user configurations */

    struct ftl_bm_desc * pBm;           /* pointer to BM instance */

    /* FTL device internal layout */

    /* meta blocks */

    fblock_t    blkStart;       /* starting block number */ 
    fblock_t    nBlksAvail;     /* total number of blocks available */ 

    fblock_t    metaBlkStart;   /* start block number of meta area */
    fblock_t    nMetaBlks;      /* total number of meta blocks */
    fblock_t    logBlkStart;    /* start block number of log area */
    fblock_t    logBlkEnd;      /* end block number of log area */
    fblock_t    nLogBlks;       /* total number of log blocks */
    fblock_t    mapBlkStart;    /* start block number of map area */
    fblock_t    nMapBlks;       /* total number of map blocks */

    /* data and associate blocks */

    fblock_t    dataBlkStart;   /* start block number of data area */
    fblock_t    nDataBlks;      /* total number of data blocks */
    fblock_t    nAssocBlks;     /* total number of associate blocks */

    /* grouping of data blocks */

    UINT16      nGroups;            /* total number of groups */
    fblock_t    nDataBlksPerGrp;    /* how many data blocks are */
                                            /* mapped in  each group */
    UINT16      lastGrpNo;          /* total number of groups */
    fblock_t    nDataBlksLastGrp;   /* how many data blocks are */
                                            /* mapped in the last group */

    /* replacement blocks: see bm_desc */

    /*
     * Following two arrays store the internal layout of a mapping and
     * age page respectively throught various offsets and length.
     * These values are calculated or filled at mount based on the
     * geometry of the flash device. The index of these arrays are
     * defined in two enumination type, mp_index and ap_index
     * respectively.
     */

    META_LAYOUT  mpLayout[MP_IDX_MAX];
    META_LAYOUT  logLayout[LOG_IDX_MAX];

    /* size of log/mp/ap unit */

    fbsize_t    logSize;        /* size of each meta log */
    fbsize_t    updateLogSize;  /* size of each meta log update */
    fbsize_t    mpSize;         /* size of each mp */
    fpage_t     nPagesPerMp;    /* # of pages per meta for a group */ 
    fbsize_t    nPagesPerLog;   /* # of pages per log data */ 
    FTL_OOB_TYPE oobType;        /* oob type */
    fpsize_t    ftlOobSize;     /* oob size used by FTL */

    /* flash block access control */

    FTL_LBN_CTRL_POOL   lbnCtrlPool;    /* lbn control pool */
    FBIO_POOL           fbioPool;       /* fbio pool */ 

    /*
     * exclusive access control: Wear-leveling, garbage collection,
     * and etc
     */

    FTL_LOCK_T          exclLock;       /* huge exclusively access lock */
    FTL_LOCK_T          gcLock;         /* use the exclLock */
    FTL_LOCK_T          wlLock;         /* use the exclLock */

    char *              pPageBuf;       /* page buffer for gc/wl */

    struct ftl_data_cache * pDataCache; /* data cache support */

    struct ftl_discard * pDiscard;      /* discard support */

    /* management of log area */

    FTL_ADDR            nextLogAddr;    /* next location to write log */
    FTL_META_LOG *      pMetaLog;       /* meta log */
    META_LOG_BUF_INFO * pLogBuf;        /* meta log buffer info */

    /* management of map blocks */ 

    FTL_LOCK_T          mpLock;         /* lock for hash operations */
    UINT64              seqNo;          /* Sequence number to track the */
                                        /* mapping and age pages */
    GRP_MP_INFO *       pGrpMpTbl;      /* the array address of meta pages */
                                        /* for each group. The group number */
                                        /* is the index of the array. */
    UINT8 *             pMpBlkBmp;      /* bitmap to track the free map */
                                        /* blocks */
    UINT32              mpBlkBmpLen;    /* length of the bitmap */
    fblock_t            nextFreeMapBlk;  
    FTL_LOCK_T *        pGrpLocks;      /* locks for each group */

    /* 
     * management of write-through block map cache. It is organized in the 
     * form of list of nodes of type MP_BUF_INFO. 
     */

    void *              pMpBufs;        /* buffer for caching mapping page */
    UINT16              nMpBufs;        /* # of mapping page buffers */
    DL_LIST             mpList;         /* used mapping page list - LRU */
    FTL_SEM_T           semCntMp;       /* count semphore to track the page */
                                        /* maps */

    /*
     * management of the associate blocks. The elementary type is
     * ASSOC_BLK_ENTRY.
     */

    FTL_LOCK_T          assocLock;      /* lock for associate block cache */
    void *              pAssocBlkMem;   /* memory for the associate blocks */
    DL_LIST             usedAssocBlkList[FTL_NUM_ASSOC_BLK_LIST];  
    UINT16              spacePerList;   /* used associate blocks list - */
                                        /* sorted in space usage ratio */
    DL_LIST             freeAssocBlkList; /* free associate blocks list */
    DL_LIST             hskpAssocBlkList; /* house keeping associate */
                                          /* blocks list */
    DL_LIST             hskpPgMapList;  /* house keeping page map list */
    AVL_TREE            assocTree;      /* associate block tree, lbn as key */
    fblock_t            nBlksPerHash;   /* how many blocks are mapped to each */
                                        /* hash list */
    fblock_t *          pAssocBlks;     /* associate block numbers */
    UINT16              maxAssocBlksPerLbn; /* maximum # of associate blocks */
                                        /* for a lbn. */

    /*
     * management of assoicate page map cache. It is organized in the 
     * form of list of nodes of type LBN_PG_MAP 
     */

    void *              pPgMapBufs;     /* buffer for caching page mapping */
    UINT16              nPgMapBufs;     /* # of page mapping buffers */
    DL_LIST             pgMapList;      /* page mapping buffer list in use - */
                                        /* LRU */
    DL_LIST             freePgMapList;  /* free page mapping buffer list */
    FTL_SEM_T           semCntPgMap;    /* count semphore to track the page */
                                        /* maps */

    /* management of the cursor cache. */

    FTL_LOCK_T          cursorCacheLock;/* cursor cache lock */
    UINT8 *             pCursorTable;   /* a full table tracking the next fpn */
                                        /* for each lbn */
    int                 cursorEntrySize;/* cursor entry size */
    HOT_BLK_INFO *      pHotDataBlks;   /* hot data blocks info */ 
    fblock_t            nHotBlkEntry;   /* # of hot block entries */

    FTL_TASK_T          svcTaskId;      /* background task for WL, GC, etc */ 
    int                 svcFlags;       /* service flags */
    FTL_SEM_T           svcSyncSem;     /* sync semophore to service task */
    FTL_LOCK_T          svcLock;        /* service lock */

    /* 
     * management of the age cache. It is organized in the form of
     * list of nodes of type FTL_META_BUF.
     */

    blk_age_t *         pAgeOfAssocBlks;/* age of associate blocks */
    int                 syncThresh;     /* the threshold to flush age cache */

    UINT64              ageSum;         /* sum of age of all blocks */
    UINT32              ageAvg;         /* sum of age of all blocks */
    UINT32              wlAgeThresh;    /* a dynamic threshold to determine */
                                        /* old blocks */ 
    GRP_WL_INFO *       pGrpWlInfo;     /* group wear-leveling info */
    GRP_WL_SORT *       pGrpWlSort;     /* for sorting group wl info */

    FTL_LOCK_T          wlListLock;     /* wear-leveling list lock */ 
    DL_LIST             wlReqList;      /* wear-leveling request list */

    /* garbage collection stuff */

    /*
     * Internal implementations of read, write and ioctl of FTL. They
     * might direct to different implemention based on different flash
     * type. Both read and write will share the some code flow for
     * translation.
     */

    STATUS (*ftlRead)  (struct ftl_desc * pFtl, struct ftl_bio * pFbio);
    STATUS (*ftlWrite) (struct ftl_desc * pFtl, struct ftl_bio * pFbio);
    STATUS (*ftlIoctl) (struct ftl_desc * pFtl, int cmd, FTL_IOCTL_ARG_T arg);

    void *              pBlkDev;

#ifdef FTL_DEBUG
    struct {
        FTL_ATOMIC64_T  mountTicks;

        FTL_ATOMIC64_T  wrPageCnt;
        FTL_ATOMIC64_T  wrTicks;        /* xbd visible */
        FTL_ATOMIC64_T  ftlWrTicks;     /* ftl visible */
        FTL_ATOMIC64_T  rdPageCnt;
        FTL_ATOMIC64_T  rdTicks;
        FTL_ATOMIC64_T  discardPageCnt;
        FTL_ATOMIC64_T  discardTicks;

        FTL_ATOMIC64_T  cacheHitCnt;
        FTL_ATOMIC64_T  cacheMissCnt;

        FTL_ATOMIC32_T  gcSwitchCnt;
        FTL_ATOMIC32_T  gcCopyCnt;
        FTL_ATOMIC32_T  gcFullCnt;
        FTL_ATOMIC32_T  wlCnt;
        FTL_ATOMIC32_T  wlCntEnforced;  /* enforced wl count for too old */
                                        /* blocks */
        FTL_ATOMIC32_T  discardCnt;     /* how many discards are accepted */ 
        FTL_ATOMIC32_T  discardCntFull; /* how many discarded blocks are */
                                        /* fully discarded */
        FTL_ATOMIC32_T  discardCntPartial; /* how many discarded blocks are */
                                        /* partially discarded */
        FTL_ATOMIC32_T  discardPagesPartial; /* how many pages are */
                                        /* partially discarded */
        FTL_ATOMIC32_T  discardGcCnt;
        FTL_ATOMIC32_T  discardWlCnt;

        FTL_ATOMIC32_T  discardCacheDirtyPageCnt;
        FTL_ATOMIC32_T  discardInternalPageCnt;

        /* meta cache */

        FTL_ATOMIC32_T  metaLogWrCnt;
        FTL_ATOMIC32_T  mpWrCnt;
        FTL_ATOMIC32_T  mpRdCnt;
        FTL_ATOMIC32_T  pgMapLoadCnt;

        FTL_ATOMIC32_T  cursorCacheHitCnt;
        FTL_ATOMIC32_T  cursorCacheMissCnt;

        FTL_ATOMIC32_T  mainBlkWritePageCnt;
        FTL_ATOMIC32_T  fillBlankPageCnt;

        /* background task contribution */

        FTL_ATOMIC32_T  bgTaskWakeupCnt;
        FTL_ATOMIC32_T  bgTaskGcCnt;
        FTL_ATOMIC32_T  bgTaskWlCnt;
        FTL_ATOMIC32_T  bgTaskFlushCnt;
        FTL_ATOMIC32_T  bgTaskDiscardCnt;

        FTL_ATOMIC32_T  memUseHigh;
        FTL_ATOMIC32_T  memUseCur;
    }dbgStat;

    struct {
        FTL_ATOMIC32_T  curMemCost;     /* total memory cost cost by ftl */
        size_t          ftlDesc;
        size_t          lbnCtrlPool;
        size_t          dataCache;
        size_t          blkMapCache;
        size_t          pageMapCache;
        size_t          cursorCache;
        size_t          assocBlks;
        size_t          metaLogBuf;
        size_t          grpMpTbl;
        size_t          grpLocks;
        FTL_ATOMIC32_T  discard;
        size_t          bbmtBuf;
        size_t          bbmtEntry;
    }memStat;

    struct map_track *   pMapTrack;
    struct ppn_track *   pPpnTrack;
#endif
    }FTL_DESC, *pFTL_DESC;

typedef struct ftl_dev_id               /* ftl identify saved in flash */    
    {
    /* 
     * endian field saves the endianess of all ftl meta data, 0 for
     * little endian, 0xFF for big endian.
     */

    UINT8               endian;         /* endianess of saved meta data */
    UINT8               pad[3];
    UINT32              magic;          /* ftl magic number */
    UINT8               version;        /* ftl version */ 
    UINT8               selfLen;        /* length of dev id itself in pages */ 
    UINT8               pad1[2];
    UINT16              options;        /* ftl options */
    UINT16              extFlags;       /* extension flags, set to 0 if no */
                                        /* flags are set */

    /* geometry information */

    UINT8               flashType;      /* flash type */
    UINT8               cellType;       /* for nand flash only */
    UINT16              pagesPerBlk;    /* number of pages per block */
    UINT64              totalSize;      /* total size of this device */
    UINT32              pageSize;       /* page size in bytes */
    UINT32              blkStart;       /* starting block number */ 
    UINT32              nBlks;          /* total number of flash blocks */
    UINT16              oobSize;        /* oob size */
    UINT16              oobSizeAvail;   /* available oob size to FTL */

    /* 
     * FTL layout, the following areas are not physical but logical blocks
     * that has to be mapped to physical block through bad block map.
     * The exceptions are the device id blocks and bbm blocks themselves.
     */

    /* meta blocks */

    UINT32              nBlksAvail;     /* number of blocks available to ftl */ 
                                        /* subtracted the bbm blocks */
    UINT32              metaBlkStart;   /* start block number of meta area */
    UINT32              nMetaBlks;      /* total number of meta blocks */
    UINT32              logBlkStart;    /* start block number of log area */
    UINT32              nLogBlks;       /* total number of log blocks */
    UINT32              mapBlkStart;    /* start block number of map area */
    UINT32              nMapBlks;       /* total number of map blocks */

    /* data and associate blocks */

    UINT32              dataBlkStart;   /* start block number of data area */
    UINT32              nDataBlks;      /* total number of data blocks */
    UINT32              nAssocBlks;     /* total number of associate blocks */

    UINT32              replBlkStart;   /* starting replacement block */
    UINT32              nReplBlks;      /* # of replacement blocks */

    UINT32              logLayout[LOG_IDX_MAX];
    UINT32              mpLayout[MP_IDX_MAX];

    /* grouping of data blocks */

    UINT32              nGroups;        /* total number of groups */
    UINT32              nDataBlksPerGrp;/* how many data blocks are */
                                        /* mapped in  each group */

    UINT16              oobType;
    UINT16              ftlOobSize;
    UINT32              logSize;
    UINT32              mpSize;

    UINT16              blkMarkPageNo;   /* block mark page in block */
    UINT16              blkMarkOffset;   /* block mark offset in page */

    /* static bbt offset */

    UINT32              badBlkInfoOff;  /* bad block info offset */
    UINT32              badBlkInfoLen;  /* bad block info length */
    UINT32              stBbtOff;       /* table of static bad blocks in bbm */
                                        /* area */
    UINT32              badBlkCnt;      /* # of bad blocks in bbm area */ 
    UINT32              stBbmtOff;      /* static bad block map table */
    UINT32              badBlkMapCnt;   /* # of static bad block in non-bbm */
                                        /* areas*/

    UINT8               reserved[16];
    UINT32              badBlkInfoChksum; /* bad block info checksum */
    UINT32              devIdChksum;    /* crc32 checksum */
    }_FTL_PACK_ALIGN(4) FTL_DEV_ID;     /* totally 188 bytes */

/* Mapping information descriptor flag */

#define FTL_MP_INFO_DESC_ERR_ADRS   0x01    /* incorrect physAddr */
#define FTL_MP_INFO_DESC_ERR_CNT    0x02    /* incorrect pageCnt */

/* function declarations */

STATUS ftlSaveIdentity (FTL_DESC * pFtl);
FTL_DEV_ID * ftlGetIdentity (void * pBm);
void ftlRelIdentity (FTL_DEV_ID * pFtlId);

STATUS ftlMountInternal (void * pBm);
STATUS ftlUnmountInternal (FTL_DESC * pFtl);

STATUS ftlUsrCfgInit (FTL_DESC * pFtl);
STATUS ftlDescInit (FTL_DESC * pFtl);
STATUS ftlDescCleanup (FTL_DESC * pFtl);
FTL_DESC * ftlDescGetByName (const char * pDevName);

/* ftl lbd module external routines */

int ftlLbdInit (FTL_DESC * pFtl);
int fbioInit (struct ftl_bio * pFbio);
int fpioInit (struct ftl_pio * pFpio);
int ftlLbdCleanup (FTL_DESC * pFtl);
int ftlLbdFlush (FTL_DESC * pFtl, BOOL isUnmount);
int ftlLbdDiscard (FTL_DESC * pFtl, FTL_DISCARD_INFO * pDiscardInfo);
int ftlLbnCtrlRel (FTL_DESC * pFtl, LBN_CTRL_ENTRY * pLbnCtrl);
int ftlFbioRel (FTL_DESC * pFtl, FTL_BIO * pFbio); 
int ftlLbdRW (FTL_DESC * pFtl, faddr_t ftlIoAddr,
            size_t ftlIoLen, char * pDataBuf, int rwFlag);
int ftlLbdBlkRW (FTL_DESC * pFtl, fblock_t blkAddr,
            fbsize_t blkOff, fbsize_t ioLen,
            char * pDataBuf, int rwFlag);
int ftlBlkRW (FTL_DESC * pFtl, FTL_BIO * pFbio, FTL_ADDR * pFromAddr,
            fbsize_t ioLen, char * pDataBuf, int rwFlags);
LBN_CTRL_ENTRY * ftlLbnCtrlGet (FTL_DESC * pFtl, fblock_t lbn,
            int rwFlag);
FTL_BIO * ftlFbioGet (FTL_DESC * pFtl, fblock_t lbn, int rwFlag);
LBN_CTRL_ENTRY * lbnCtrlFind (FTL_LBN_CTRL_POOL * pLbnCtrlPool,
            fblock_t lbn);

int lbnCtrlLock (LBN_CTRL_ENTRY * pLbnCtrl, int flags);
int lbnCtrlUnlock (LBN_CTRL_ENTRY * pLbnCtrl);
     
int lbnCompare (AVL_NODE * pNode, void * pKey); 

int fpioListAdd  (DL_LIST * pList, DL_NODE * pNode);
int fpioListMove (DL_LIST * pDstList, DL_LIST * pSrcList,
            DL_NODE * pNode);
int fpioListDel (DL_LIST * pList, DL_NODE * pNode);
int fpioListInit (DL_LIST * pList);
FTL_PIO * fpioListNext (DL_LIST * pList, DL_NODE * pNode);
FTL_PIO * fpioListFirst (DL_LIST * pList);
FTL_PIO * fpioListFind (DL_LIST * pList, fpage_t lpn);

/* ftl map module external routines */

int ftlMapInit (FTL_DESC * pFtl);
int ftlBlkMapInit (FTL_DESC * pFtl);
int ftlMapCleanup (FTL_DESC * pFtl);
int ftlCursorCacheFind (FTL_DESC * pFtl, fblock_t lbn,
            HOT_BLK_INFO * pInfo);
int cursorInvalidate (FTL_DESC * pFtl, fblock_t lbn,
            HOT_BLK_INFO * pInfo);
int ftlCursorCacheAdd (FTL_DESC * pFtl, HOT_BLK_INFO * pInfo, BOOL replace);
int ftlBlkMap (FTL_DESC * pFtl, fblock_t lbn, MAP_BLK_INFO * pBlkInfo);
MP_BUF_INFO * ftlBlkMapGet (FTL_DESC * pFtl, fblock_t lbn);
int ftlBlkMapRel (FTL_DESC * pFtl, MP_BUF_INFO * pMpBuf, BOOL dirty);
int ftlBlkMapLoad (FTL_DESC * pFtl, UINT16 grpNo, MP_BUF_INFO * pMpBuf);
int ftlBlkMapSave (FTL_DESC * pFtl,MP_BUF_INFO * pMpBuf);
MP_BUF_INFO * ftlMpBufGetDel (FTL_DESC * pFtl, UINT16 grpNo);
int ftlMpBufRel (FTL_DESC * pFtl, MP_BUF_INFO * pMpBuf);
int ftlAssocCacheInit (FTL_DESC * pFtl);
int ftlAssocCacheCleanup (FTL_DESC * pFtl);
int ftlFreeAssocBlkRel (FTL_DESC * pFtl, ASSOC_BLK_ENTRY * pAssocBlk);
ASSOC_BLK_ENTRY * ftlFreeAssocBlkGet (FTL_DESC * pFtl, int option);
ASSOC_BLK_ENTRY * ftlAssocBlkFind (FTL_DESC * pFtl, fblock_t lbn);
ASSOC_BLK_ENTRY * ftlGcGetUsedAssocBlk (FTL_DESC * pFtl, 
            LBN_CTRL_ENTRY ** ppLbnCtrl, BOOL bUrgent);
int ftlAssocBlkDel (FTL_DESC * pFtl, ASSOC_BLK_ENTRY * pAssocBlk);
LBN_PG_MAP * ftlAssocPgMapGet (FTL_DESC * pFtl, fblock_t lbn, int flags); 
int ftlAssocBlkAdd (FTL_DESC * pFtl, ASSOC_BLK_ENTRY * pAssocBlk);
int ftlUsedAssocBlkListAdd (FTL_DESC * pFtl, ASSOC_BLK_ENTRY * pAssocBlk);
int ftlAssocPgMapRel (FTL_DESC * pFtl, LBN_PG_MAP * pPgMap);
int ftlAssocPgMapLoad (FTL_DESC * pFtl, ASSOC_BLK_ENTRY * pAssocBlk,
            fblock_t lbn, LBN_PG_MAP * pPgMap);
STATUS ftlWlUpdatePgMap (FTL_DESC * pFtl, fblock_t lbn,
            fblock_t oldPbn, fblock_t newPbn);
int ftlPgMapCleanup (FTL_DESC * pFtl, LBN_PG_MAP * pPgMap);

#ifdef obsolete
int ftlWriteBlkMark (FTL_DESC * pFtl, fblock_t blkNo, int blkType,
            char * pBlkMarkBuf);
int ftlCheckBlkMark (FTL_DESC * pFtl, fblock_t blkNo, int blkType);
#endif /* obsolete */

int ftlWriteEraseMark (FTL_DESC * pFtl, fblock_t blkNo);
BOOL ftlCheckEraseMark (FTL_DESC * pFtl, fblock_t blkNo, BOOL bEraseBlk);
int ftlWriteBlkMark (FTL_DESC * pFtl, fblock_t blkNo, UINT8 blkMark);
BOOL ftlCheckBlkMark (FTL_DESC * pFtl, fblock_t blkNo, UINT8 blkMark);
int ftlWriteMetaLog (FTL_DESC * pFtl, META_LOG_BUF_INFO * pLogBuf);
int checkMeta (FTL_DESC * pFtl, char * pRawBuf);
int ftlLogNextGrpMpAddr (FTL_DESC * pFtl, fblock_t lbn);
int assocTreeCompare  (AVL_NODE * pNode, void * pKey);

/* wear-leveling module external routines */

int ftlWlInit (FTL_DESC * pFtl);
int ftlWlCleanup (FTL_DESC * pFtl);
int ftlWearLeveling (FTL_DESC * pFtl, int option); 
int ftlWlReqAdd (FTL_DESC * pFtl, ASSOC_BLK_ENTRY * pAssocBlk);
int ftlWlAssocBlk (FTL_DESC * pFtl, ASSOC_BLK_ENTRY * pAssocBlk);
int ftlWlMoveBlk (FTL_DESC * pFtl, fblock_t lbn, ASSOC_BLK_ENTRY * pAssocBlk);
int ftlAgeThreshUpdate (FTL_DESC * pFtl); 
void ftlAvgAgeUpdate (FTL_DESC * pFtl); 
int findYoungBlk (FTL_DESC * pFtl, fblock_t * pLbnIdx, blk_age_t * pAge);
int findGrpYoungBlk (FTL_DESC * pFtl, MP_BUF_INFO * pMpBuf, 
            fblock_t * pLbnIdx, blk_age_t * pAge, blk_age_t * pAgeSum);
BOOL ftlIsAssocBlkTooOld (FTL_DESC * pFtl, ASSOC_BLK_ENTRY * pAssocBlk);

int ftlSvcTaskCreate (FTL_DESC * pFtl);
int ftlSvcTaskDelete (FTL_DESC * pFtl);

/* garbage-collection module external routines */

int ftlGarbageCollection (FTL_DESC * pFtl, BOOL bUrgent);
int ftlGcMergeUrgent (FTL_DESC * pFtl, LBN_PG_MAP * pPgMap,
            HOT_BLK_INFO * pDataBlkInfo);
int ftlGcMergeNormal (FTL_DESC * pFtl, LBN_PG_MAP * pPgMap,
            HOT_BLK_INFO * pDataBlkInfo);

/* discard support */

int ftlDiscardInit (FTL_DESC * pFtl);
int ftlDiscardCleanup (FTL_DESC * pFtl);
int ftlDiscard (FTL_DESC * pFtl, int flags);
int ftlDiscardBlk (FTL_DESC * pFtl, FTL_BLK_DISCARD_INFO * pBlkDiscard);
int ftlDiscardCheck (FTL_DESC * pFtl, fblock_t lbn,
            fpage_t fromLpn, fpage_t endLpn);
int ftlDiscardUpdate (FTL_DESC * pFtl, fblock_t lbn,
            fpage_t fromLpn, fpage_t endLpn);
FTL_DISCARD_NODE * ftlDiscardFind (FTL_DESC * pFtl, fblock_t lbn);

/* misc */

int ftlOobInit (FTL_DESC * pFtl, char * pOobBuf, UINT8 oobVer);
int ftlOobSet (FTL_DESC * pFtl, char * pOobBuf, UINT8 blkVer,
            fblock_t lbn, fpage_t lpn, blk_age_t age);
int ftlOobSetFull (FTL_DESC * pFtl, char * pOobBuf, UINT8 blkVer,
            fblock_t lbn, fpage_t lpn, blk_age_t age, BOOL blank, BOOL error);
int ftlOobSetBlkInfo (FTL_DESC * pFtl, char * pOobBuf, UINT8 blkVer,
        blk_age_t age);
int ftlOobChksum (FTL_DESC * pFtl, char * pOobBuf);
fblock_t mapBlkAlloc (FTL_DESC * pFtl);
void mapBlkFree (FTL_DESC * pFtl, fblock_t blkNo);
FTL_OOB_LARGE * bufToLargeOob (FTL_DESC * pFtl, char * pBuf, 
            FTL_OOB_LARGE * pOobLarge);
FTL_OOB_SMALL * bufToSmallOob (FTL_DESC * pFtl, char * pBuf);
int checkPattern (const char * pBuf, size_t dataLen, char pattern, int * pBits);
int setPattern (char * pBuf, size_t dataLen, char pattern);
int ftlEraseBlk (FTL_DESC * pFtl, fblock_t blkNo, int blkType,
            int flags);
int ftlOobFlashToRam (FTL_DESC * pFtl, char * pOobBuf, FTL_OOB_RAM * pOobRam);
int blkVerCompare (UINT8 blkVer1, UINT8 blkVer2, BOOL major);

/* global configuration options */

extern BOOL ftlBgSvcTaskEnabled;
extern MEM_BUDGET_T ftlMemBudgetCfg;
extern BOOL ftlAutoMountEnabled;
extern BOOL ftlAutoRecvErrorEnabled;
extern BOOL ftlCacheEnabled;
extern size_t   ftlCacheSize;
extern BOOL ftlDiscardEnabled;

/* declaration of ftl cache component function pointers */

IMPORT int (* _func_ftlCacheInit) (FTL_DESC * pFtl);
IMPORT int (* _func_ftlCacheCleanup) (FTL_DESC * pFtl);
IMPORT int (* _func_ftlCacheBlkRW) (FTL_DESC * pFtl, fblock_t blkAddr,
            fbsize_t blkOff, fbsize_t ioLen, char * pDataBuf, 
            int rwFlag);
IMPORT int (* _func_ftlCacheFlush) (FTL_DESC * pFtl, int option);
IMPORT int (* _func_ftlCacheDiscard) (FTL_DESC * pFtl, 
            FTL_BLK_DISCARD_INFO * pBlkDiscardInfo);
IMPORT STATUS (* _func_ftlCacheCheckFlush) (FTL_DESC *  pFtl);

/* declaration of ftl discard component function pointers */

IMPORT int (* _func_ftlDiscardInit) (FTL_DESC * pFtl);
IMPORT int (* _func_ftlDiscardCleanup) (FTL_DESC * pFtl);
IMPORT int (* _func_ftlDiscard) (FTL_DESC * pFtl, int flags);
IMPORT int (* _func_ftlDiscardBlk) (FTL_DESC * pFtl, 
                FTL_BLK_DISCARD_INFO * pBlkDiscard);
IMPORT int (* _func_ftlDiscardCheck) (FTL_DESC * pFtl, fblock_t lbn,
                fpage_t fromLpn, fpage_t endLpn);
IMPORT int (* _func_ftlDiscardUpdate) (FTL_DESC * pFtl, fblock_t lbn,
                fpage_t fromLpn, fpage_t endLpn);
IMPORT FTL_DISCARD_NODE * (* _func_ftlDiscardFind) (FTL_DESC * pFtl, 
                fblock_t lbn);

#ifdef FTL_CLEAN_UNMOUNT
int ftlDevGet (FTL_DESC * pFtl);
int ftlDevPut (FTL_DESC * pFtl);
#endif /* FTL_CLEAN_UNMOUNT */

#ifdef FTL_DEBUG
IMPORT UINT32 ftlDbgFlags;

#define FTL_DBG_PAGE_BLANK      0xFF 
#define FTL_DBG_PAGE_VALID      0x5A 
#define FTL_DBG_PAGE_DISCARDED  0x0 

int ftlDbgPageMapUpdate (FTL_DESC * pFtl, fblock_t lbn, 
            fpage_t lpn, fblock_t pbn, fpage_t ppn);
int ftlDbgBlkMapUpdate (FTL_DESC * pFtl, fblock_t lbn, 
            fblock_t pbn);
int ftlDbgPageStatusUpdate (FTL_DESC * pFtl, fblock_t lbn, 
            fpage_t lpn, fpage_t nPages, UINT8 status);
int ftlDbgPageMapShow (const char * pDevName, fblock_t lbn, 
            fpage_t lpn, fpage_t nPages);
int ftlDbgPpnStatusUpdate (FTL_DESC * pFtl, fblock_t pbn, 
            fpage_t ppn, fpage_t nPages, UINT8 status);
int ftlDbgPpnStatusShow (const char * pDevName, fblock_t pbn, 
            fpage_t ppn, fpage_t nPages);
#endif /* FTL_DEBUG */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCftlLibPh */

