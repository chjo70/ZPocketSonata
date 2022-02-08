/* fsimLibP.h - flash simulator private header file */ 

/*
 * Copyright (c) 2012-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
13aug15,dee  remove static analysis defects
13may15,txu  fix V7STO-358 : wrong include after extern "C"
10feb14,ywu  fix improper use of _WRS_CONFIG_FDT
16jan14,ywu  adopt to vxBus gen2
03oct13,dee  change unsigned int to size_t
22mar13,jxu  added support for NOR flash
15mar12,jxu  written
*/

#ifndef __INCfsimLibPh
#define __INCfsimLibPh


/* includes */

#include <vxWorks.h>

#ifndef _WRS_CONFIG_VXBUS_LEGACY
#include <subsys/timer/vxbTimerLib.h>
#else
#include <vxbTimerLib.h>
#endif

#include <rebootLib.h>
#include <sysLib.h>
#include <flash.h>
#include <mtd.h>
#include <fsimLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* simulator state */

typedef enum fsim_state
    {
    FSIM_STATE_NOT_STARTED = 0x0,
    FSIM_STATE_STOPPED,
    FSIM_STATE_RUNNING
    }FSIM_STATE;

/* typedefs */

typedef enum fsim_event
    {
    FSIM_EVENT_CREATION = 0,
    FSIM_EVENT_DELETION,
    FSIM_EVENT_MOUNT,
    FSIM_EVENT_UNMOUNT
    }FSIM_EVENT;

/* 
 * there is no page concept for NOR Flash, however, we simulate it so as to
 * unify the interface with simulated NAND Flash.
 */

#define FSIM_NOR_FLASH_PAGE_SIZE        512

/* accessing mode */

#define FSIM_CONFIG_FAST_MODE    /* without simulating flash internal logics */
/* #define FSIM_CONFIG_MIMIC_MODE */     /* not yet */

/* simulated flash medium layout */

#define FSIM_CHIP_LAYOUT_MIXED          0   /* mixed layout */
#define FSIM_CHIP_LAYOUT_SEPERATED      1   /* seperated layout */
#define FSIM_CHIP_LAYOUT_INDEPENDENT    2   /* independent layout */

#define FSIM_CONFIG_CHIP_LAYOUT    FSIM_CHIP_LAYOUT_SEPERATED

#define FSIM_CONFIG_CTRL_CACHE      0 
#define FSIM_CONFIG_CHIP_INTERLEAVE 0

#define FSIM_BUS_WIDTH_8BIT         0
#define FSIM_BUS_WIDTH_16BIT        1 
#define FSIM_CONFIG_BUS_WIDTH       FSIM_BUS_WIDTH_8BIT 

/* bad block type */

#define FSIM_GOOD_BLOCK         0x0
#define FSIM_BAD_BLOCK_RUNTIME  0x11
#define FSIM_BAD_BLOCK_FACTORY  0x77

/* flash basic operations */

#define FOP_READ      0x1
#define FOP_WRITE     0x2
#define FOP_ERASE     0x3

#define FSIM_DEV_TO_ID(pFSimDev)        ((FSIM_ID)(pFSimDev))
#define FSIM_ID_TO_DEV(fsimId)          ((FSIM_DEV *)(fsimId))

#define OVERHEAD_CHIP       sizeof(STAT_CHIP)
#define OVERHEAD_BLK        sizeof(STAT_BLK)
#define OVERHEAD_PAGE       sizeof(STAT_PAGE)
#define STAT_OVERHEAD(pChip, pageNum)    (   \
            OVERHEAD_CHIP +   \
            OVERHEAD_BLK  * ((pageNum)/(pChip)->chipInfo.nPagesPerBlk + 1) + \
            OVERHEAD_PAGE * ((pageNum) + 1) \
            )

#define OVERHEAD(pChip, pageNum) STAT_OVERHEAD(pChip, pageNum)

/* mutual exclusive access lock/unlock macros */

#define LOCK(lock)      (semTake((SEM_ID)lock, WAIT_FOREVER))
#define UNLOCK(lock)    (semGive((SEM_ID)lock))

#define CREATE_LOCK()   ((LOCK_T)semMCreate(SEM_Q_PRIORITY | SEM_DELETE_SAFE | \
            SEM_INVERSION_SAFE))
#define DELETE_LOCK(lock)   (semDelete((SEM_ID)lock))

#define CURRENT_TASK()  taskIdSelf()

#define SYS_REBOOT() reboot(BOOT_NORMAL)

/* errno related staff */

#define ERRNO_SET(errNo) (void) errnoSet(errNo)
#define ERRNO_GET()      errnoGet()
#define ERRNO_CLEAR()    (void) errnoSet(0)
#define RETURN(retVal, errno) do {     \
    (void) errnoSet (errno);                   \
    return (retVal);                    \
    }while(0)

#define FSIM_DELAY_US(delayTime) vxbUsDelay(delayTime) /* microseconds delay */ 
#define FSIM_DELAY_MS(delayTime) vxbMsDelay(delayTime) /* milliseconds delay */ 

/* default delay time for read, write and erase operations */

#if (FSIM_CONFIG_DELAY_READ_US > 0)
#define FSIM_DELAY_RD() \
            FSIM_DELAY_US(FSIM_CONFIG_DELAY_READ_US) 
#else
#define FSIM_DELAY_RD() 
#endif

#if (FSIM_CONFIG_DELAY_WRITE_US > 0)
#define FSIM_DELAY_WR() \
            FSIM_DELAY_US(FSIM_CONFIG_DELAY_WRITE_US) 
#else
#define FSIM_DELAY_WR() 
#endif

#if (FSIM_CONFIG_DELAY_ERASE_US > 0)
#define FSIM_DELAY_ER() \
            FSIM_DELAY_US(FSIM_CONFIG_DELAY_ERASE_US) 
#else
#define FSIM_DELAY_ER() 
#endif

#define FSIM_DEBUG

#ifdef FSIM_DEBUG

#define DBG_QUIET       0x1    /* quiet */
#define DBG_MUST        0x2    /* always print */
#define DBG_FATAL       0x4    /* fatal error */
#define DBG_ERROR       0x8    /* normal error */
#define DBG_WARN        0x10   /* warning */
#define DBG_FLOW        0x20   /* monitor where i am */
#define DBG_INFO        0x40   /* informative message for debug */
#define DBG_MASK        0x7F   /* */

#define DEBUG_SET       (DBG_MUST | DBG_FATAL | DBG_ERROR | DBG_WARN ) 
					/* set debug level */

/* 
 * the highest bit the level controls whether to print the msg for a
 * module, and the lower bits gives the type of the msg
 */
#define DBG_LEVEL(dbgAll, level) (((dbgAll != 0)? DEBUG_ALL : 0) | (level))
#define DEBUG_ALL       (0x1U << 31)
#define DEBUG_ON(level) ((((level) & DEBUG_ALL) != 0) || \
                         (((level) & DEBUG_SET) != 0))

#define FSIM_DBG_PRINTF(level, format, args...)  do {                    \
        if(DEBUG_ON(level))                                             \
            {                                                           \
            printf ("TID(0x%lx): %d: %s:" format,                       \
                    (long)taskIdCurrent, __LINE__, __FUNCTION__,        \
                    ## args);                                           \
            }                                                           \
        }while(0)

#define FSIM_DBG(level, format, args...)         \
            FSIM_DBG_PRINTF(DEBUG_ALL | level, format, ## args)

#define  FSIM_DBG_I_AM_HERE()   FSIM_DBG_PRINTF(DBG_FLOW, "I'm here!\n")

#else /* !FSIM_DEBUG */

#define FSIM_DBG_I_AM_HERE()                             /* nothing */ 
#define FSIM_DBG_PRINTF(level, format, args...)          /* nothing */ 
#define FSIM_DBG FSIM_DBG_PRINTF

#endif /* #ifdef FSIM_DEBUG */

#define FSIM_PRINTF(format, args...)  do {  \
            printf (format, ## args);       \
        }while (0)

/* typedefs */

/* chip-specific */

typedef enum state      /* state set for all commands */ 
    {
    STATE_READY,
    STATE_BUSY_READ,
    STATE_BUSY_WRITE,
    STATE_BUSY_ERASE
    }STATE;

typedef struct fsim_medium  /* flash simulating medium */   
    {
    int     layout;         /* mixed, seperated, independent */
    int     type;           /* RAM, Hard Disk, USB, etc */
    int     fd;             /* if interacting with FS to access 
                             * underlying hardware */
    int     chipOff;        /* start position for the chip */
    int     statOff;        /* start position for saving statistics, seperated
                             * layout only. */
    int     statFd;         /* fd for statistics, independent layout only */
#ifdef notyet
    int     raw;            /* raw access, RAM type only */
    void  * pMem;           /* memory for raw access, RAM type only */
#endif /* notyet */
    }FSIM_MEDIUM;

typedef struct stat_page    /* per page statistics */
    {
    UINT32  rdCount;        /* read count */
    UINT32  wrCount;        /* write count */
    INT32   error;          /* error in page */
    INT8    pad[4];
    }STAT_PAGE;

typedef struct stat_blk     /* per block statistics */
    {
    UINT32  age;            /* erase count of block */
    INT32   blkStatus;      /* good or factory bad or runtime bad */
    INT32   nextPpn;        /* next free ppn to be written */
    INT8    pad[4];         /* pad to be 16 bytes aligned */ 
    }STAT_BLK;

typedef struct stat_chip    /* per chip statistics */
    {
    INT32   version;        
    INT32   magic;         
    INT32   crc32;          /* crc32 checksum of this structure */
    UINT32  nBadBlks;       /* number of bad blocks */
    UINT32  totalAge;       /* total age of all blocks */
    INT8    pad[12];        /* pad to be 32 bytes aligned */ 
    }STAT_CHIP;

typedef struct fop_arg_t        /* argument type for basic flash operations */
    {
    int         opType;         /* operation type: read, write or erase */
    UINT32      blkNo;          /* block number to be operated, erase only */
    UINT32      pageNo;         /* page number to be operated, rdwr only */
    off_t       offInPage;      /* offset in page, rdwr only */
    char      * pBuf;           /* buffer for transfering data, rdwr only */
    size_t      bufLen;         /* length of buffer, rdwr only */
    size_t      dataLen;        /* length of data to read or written */
    int         error;          /* error caused the by operation */
    }FOP_ARG_T;

typedef struct chip_info    /* chip information */
    {
    /* organization */

    char        ids[FSIM_CONFIG_CHIP_IDS_SIZE]; /* factory id */
    FLASH_TYPE_T type;           /* NAND, NOR, OneNAND, etc */
    FLASH_CELL_T cellType;       /* SLC or MLC */
    int         interleave;     /* if two 8x interleave */ 
    int         busWidth;       /* 8-bit or 16-bit */
    UINT        planeNum;       /* multiple plane */
    UINT64      planeSize;      /* size per plane */

    /* geometry */

    UINT64      totalSize;      /* total size of this chip */
    UINT        blkSize;        /* erase unit */
    UINT        nBlks;          /* number of blocks */
    UINT        pageSize;       /* read/write unit */
    UINT        nPages;         /* number of pages */
    UINT        nPagesPerBlk;   /* number of pages per block */
    UINT        oobSize;        /* oob (or spare area) size */
    UINT        pageOobSize;    /* page size plus oob size */

    /* latency */

    int         tRdBusy;        /* latency for read */
    int         tWrBusy;        /* latency for write */
    int         tErBusy;        /* latency for erase */

    /* unerlying medium */

    const char * pMediumName;   /* underlying medium name */
    off_t       chipOff;        /* offset for the chip */

    }CHIP_INFO;

typedef struct chip_info CHIP_CFG;

typedef struct fsim_chip    /* flash chip description */ 
    {
    LOCK_T      lock;       
    CHIP_INFO   chipInfo;   /* basic chip information */

    STATE       state;      /* current state */

    char *      pPageReg;   /* page register */
    UINT        column;     /* byte/word offset into the page register */

    FSIM_MEDIUM    medium;  /* point to underlying medium decription */

    int     result;     /* result of latest flash operation */

#ifdef FSIM_CONFIG_UI
    /* reboot request for debugging */

    int     rebootReq;  /* reboot request */
    int     rebootType; /* reboot type: unclean or clean */
    long    rebootTask; /* reboot in which task's context */
    int     freeze;     /* before clean reboot */
    REBOOT_FUNCPTR  rebootFunc; /* call back */

#endif  /* FSIM_CONFIG_UI */

    int (* reset)  (struct fsim_chip * pChip);

#ifdef FSIM_CONFIG_MIMIC_MODE
    /* flash internal operations */

    int (* read)    (struct fsim_chip * pChip);  
    int (* program) (struct fsim_chip * pChip);  
    int (* erase)   (struct fsim_chip * pChip);  

    /* mimic interface with controller */

    int (* signal) (struct fsim_chip * pChip, int sig);
    int (* input)  (struct fsim_chip * pChip, char * dataBuf, int dataLen);
    int (* output) (struct fsim_chip * pChip, char * dataBuf, int bufLen, 
            int reqLen);
    int (* accept) (struct fsim_chip * pChip, char * dataBuf, int bufLen, 
            int sig);
    int (* fsm)    (struct fsim_chip * pChip);
#endif  /* FSIM_CONFIG_MIMIC_MODE */

    /* fast flash access */

    int (* read)    (struct fsim_chip * pChip, FOP_ARG_T * pArg); 
    int (* program) (struct fsim_chip * pChip, FOP_ARG_T * pArg); 
    int (* erase)   (struct fsim_chip * pChip, FOP_ARG_T * pArg); 

#ifdef FSIM_CONFIG_UI

    /* statistic funtionality */

    int (* statChip) (struct fsim_chip * pChip, char * pBuf, size_t bufLen);
    int (* statBlk)  (struct fsim_chip * pChip, int blkNo, char * pBuf, 
            size_t bufLen);
    int (* statPage) (struct fsim_chip * pChip, int pageNo, char * pBuf, 
            size_t bufLen);

    /* error injection */

    int (* markBad)   (struct fsim_chip * pChip, UINT blkNo);
    int (* unmarkBad) (struct fsim_chip * pChip, UINT blkNo);
    bool (* isBadBlk)  (struct fsim_chip * pChip, UINT blkNo);
    int (* isBlankPage)  (struct fsim_chip * pChip, UINT pageNo, BOOL * pResult);
    int (* injectError) (struct fsim_chip * pChip, UINT pageNo, int error);
    int (* removeError) (struct fsim_chip * pChip, UINT pageNo, int error);
    int (* errorGen) (struct fsim_chip * pChip);
    int (* bitFlip) (struct fsim_chip * pChip, UINT pageNo,
          int nBits);
    int (* corrupt) (struct fsim_chip * pChip, UINT pageNo);
    int (* reboot)  (struct fsim_chip * pChip, REBOOT_FUNCPTR rebootFunc, 
            int type, TASK_ID taskId);

    /* dump */

    int (* dump)   (struct fsim_chip * pChip, int option);

#endif  /* FSIM_CONFIG_UI */

    }FSIM_CHIP;

#ifdef obsolete 
/* controller-specific */

typedef struct fsim_ctrl        /* controller-specific information */
    {
    bool enableCtrl;    /* enable controller or not */

    /* ECC engine */

    bool enableEcc;     /* enable ECC or not */

    int eccType;        /* 1-bit, 4-bit, etc */
    int eccUnitSize;    /* 256/512 bytes */
    int eccBytes;       /* number of resulting ecc bytes per ecc unit */

    int (* eccEncode) (struct fsim_ctrl * pCtrl, char * dataBuf, 
            size_t dataLen, char * pEccBuf);
    int (* eccDecode) (struct fsim_ctrl * pCtrl, char * dataBuf, 
            size_t dataLen, char * pOldEccBuf);

#ifdef FSIM_CONFIG_MIMIC_MODE

    /* Registers */

    UINT    cmdReg;
    UINT    addrReg;
    UINT    dataReg;
    UINT    statusReg;
    UINT    eccReg;

    /* controller private info */
    
    void  * pCtrlPriv;

#endif /* FSIM_CONFIG_MIMIC_MODE */

#ifdef notyet
    /* cache function support */

    /* command scheduling */
#endif

    /* flash chips */

    UINT        ce;             /* each bit to chip select a single chip */
    UINT        chipBmp;        /* chip slot bitmap */
    FSIM_CHIP * pChips[FSIM_MAX_NUM_CHIPS];    
                                /* chips connected on this controller */

    /* Select a chip with given chip index */ 

    FSIM_CHIP * (* select) (struct fsim_ctrl * pCtrl, int chipIdx);

    /* Connect a chip to the controller */

    int (* connect) (struct fsim_ctrl *, FSIM_CHIP *);

    /* Disconnect a chip from the controller */

    int (* disconnect) (struct fsim_ctrl *, int chipNo); 

    /* I/O stop at controller */

    int (* readPage)  (struct fsim_ctrl * pCtrl, FSIM_CHIP * pChip,
            FOP_ARG_T * pArg);
    int (* writePage) (struct fsim_ctrl * pCtrl, FSIM_CHIP * pChip,
            FOP_ARG_T * pArg);
    int (* eraseBlk)  (struct fsim_ctrl * pCtrl, FSIM_CHIP * pChip,
            FOP_ARG_T * pArg);

    }FSIM_CTRL;
#endif /* obsolete */

typedef struct chip_desc 
    {
    FSIM_CHIP * pChip;          /* the flash chip */
    UINT        chipNo;         /* the chip number */

    /* the range of the block number represented by the chip in the
     * same group.
     */

    UINT        blkNoLow;       /* low block number */ 
    UINT        blkNoHigh;      /* high block number */
    }CHIP_DESC;

#define INVALID_MAP     0x0     /* not up to date */
#define VALID_MAP       0x1     /* up to date */
#define MAP_NUM_UNITS   1024    /* totally 512KB size */

typedef struct map_window       /* for NOR Flash only */
    {
    LOCK_T      lock;           /* for exclusive access */
    UINT64      flashAddr;      /* flash address mapped */
    size_t      mapSize;        /* flash page size aligned */
    size_t      startPage;      /* starting page mapped */
    size_t      nPages;         /* # of pages mapped */
    size_t      ioSize;         /* I/O size in batch */
    char *      pMapBuf;
    UINT8 *     pMapStatus;     /* one byte for each page in map window */ 
    }MAP_WINDOW;

typedef struct fsim_dev 
    {
    NODE        node;   /* hook to the linked list of flash simulators */
    int         magic;  /* magic number */
    LOCK_T      lock;   /* lock for the flash simulator */ 
    char        fsimName[FSIM_MAX_NAME_LEN];    /* simulator's name */
    char        mediumName[FSIM_MAX_NAME_LEN];  /* medium's name */

    /* write-through cache */

    /* user configuration */

    /* user control */

    FSIM_STATE  state;          /* running, stopped or not started */

    /* log */

    int         logLevel;       /* <result, op, blkNo, pageNo> */
    int         logFd;          /* log file */

    /* snapshot/dump */

    int         dumpFd;         /* stdout or a file */

    /* statistics */

    int         statFd;         /* stdout or a file */

    FLASH_TYPE_T flashType;     /* NAND, NOR, OneFlash, etc */
    FLASH_CELL_T cellType;      /* flash cell type */

    size_t      imgIdSize;      /* size of fsim image identity */ 
    size_t      imgSize;        /* image size of whole flash simulator */

    /* device organization */

    UINT64      totalSize;      /* total size of the simulated flash divice */
    UINT        nBlks;          /* total number of blocks */
    UINT        nPagesPerBlk;   /* number of pages per block */
    UINT        nPages;         /* number of pages */
    UINT        blkSize;        /* block size in bytes */
    UINT        pageSize;       /* page size in bytes */
    UINT        pageSizeShift;  /* page size in power of 2 */
    UINT        oobSize;        /* oob size in byte */ 
    UINT        oobAvailSize;   /* available oob size to user */

    UINT        cfgSize;        /* the space reserved for saving */
                                /* configuration, fsim-specific info. */

    UINT        oobDataPos;     /* the position where saves user data */
    UINT        oobEccPos;      /* the starting position where saves ECC */

    struct chip_desc    chipDesc[FSIM_MAX_NUM_CHIPS];    
                                /* chips for the fsim */ 
    int    freeChipNo;

    /* operations */

    int (* read) (FSIM_ID fsimId, UINT64 fromAddr, size_t length, 
                char * pBuf); 
    int (* write) (FSIM_ID fsimId, UINT64 fromAddr, size_t length, 
                char * pBuf); 
    int (* erase) (FSIM_ID fsimId, size_t blkNo, size_t nBlks);
    int (* readPage) (FSIM_ID fsimId, size_t pageNo, off_t offset, 
                size_t length, char * pBuf); 
    int (* writePage) (FSIM_ID fsimId, size_t pageNo, off_t offset, 
                size_t length, char * pBuf); 
    int (* readPages) (FSIM_ID fsimId, size_t fromPage, size_t nPages, 
                char * pBuf, size_t bufLen, int option);
    int (* writePages) (FSIM_ID fsimId, size_t fromPage, size_t nPages, 
                char * pBuf, size_t bufLen, int option);
    int (* isBlankPage) (FSIM_ID fsimId, size_t pageNo, BOOL * pResult);

    /* 
     * map mechanism to support access to flash through direct addressing,
     * like reading on a NOR Flash.
     */

    MAP_WINDOW *        pMap;

    int                 useCnt;         /* counter of users */
    void *              pUserPriv;      /* user private info */
    }FSIM_DEV;

typedef struct fsim_img_id
    {
    UINT32              magic;          /* magic number */
    UINT32              flashType;      /* flash type: NAND, NOR, etc */
    UINT32              cellType;       /* SLC or MLC, NAND flash only */
    UINT64              totalSize;      /* total size of the flash */
    UINT32              pageSize;       /* page size */
    UINT32              nPagesPerBlk;   /* number of pages per block */
    UINT32              imgIdSize;      /* size of fsim image id */
    UINT64              imgSize;        /* fsim image size */
    UINT8               reserved[20];   /* pad for 64 bytes aligned */
    UINT32              crc32;          /* checksum of this structure */
    }FSIM_IMG_ID;

/* declarations */

FSIM_CHIP * fsimChipCreate (CHIP_CFG * pChipCfg, int mount);
int fsimChipDelete (FSIM_CHIP * pChip, int unmount);

int fsimDevCreate (FSIM_DEV * pDev, FSIM_CFG * pCfg, int mount);
STATUS fsimDevDelete (FSIM_DEV * pDev, int unmount);

FSIM_CHIP * getChipBlkNo (FSIM_DEV * pDev, size_t blkNo);
FSIM_CHIP * getChipPageNo (FSIM_DEV * pDev, size_t pageNo);
int fsimDevPageRW (FSIM_DEV * pDev, size_t pageNo, off_t offset, size_t length, 
        char * pBuf, int rwFlag); 
int fsimDevPagesRW (FSIM_DEV * pDev, size_t fromPage, size_t nPages, 
        char * pBuf, size_t bufLen, int option, int rwFlag);

#ifdef useless
STATUS fsimDevCorrupt (FSIM_DEV * pDev, unsigned int pageNo);
STATUS fsimDevBitFlip (FSIM_DEV * pDev, unsigned int pageNo, int nBits);
#endif /* useless */

STATUS fsimDevStatPage (FSIM_DEV * pDev, unsigned int pageNo, char * pBuf,
            size_t bufLen);
STATUS fsimDevStatBlk (FSIM_DEV * pDev, unsigned int blkNo, char * pBuf, 
            size_t bufLen);
STATUS fsimDevStatChip (FSIM_DEV * pDev, char * pBuf, size_t bufLen);
STATUS fsimDevDump (FSIM_DEV * pDev, unsigned int pageNo, char * pBuf, 
            size_t bufLen);
STATUS fsimDevShow (FSIM_DEV * pDev);
STATUS fsimDevShowAll (void);
FSIM_DEV * fsimFind (const char * fsimName);
int fsimInvalidateMap (FSIM_ID fsimId);
int fsimIsPageMapped (FSIM_ID fsimId, size_t pageNo);
int fsimUpdateMapStatus (FSIM_ID fsimId, size_t pageNo, UINT8 status);

#ifdef __cplusplus
}
#endif

#endif /* __INCfsimLibPh */

