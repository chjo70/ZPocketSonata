/* fsimLib.h - flash simulator header file */ 

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
03oct2013,dee  change unsigned int to size_t
15mar2012,jxu  written
*/

#ifndef __INCfsimLibh
#define __INCfsimLibh


/* includes */

#include <vxWorks.h>
#include <sys/types.h>
#include <memLib.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <semLib.h>
#include <taskLib.h>
#include <ioLib.h>
#include <unistd.h>
#include <lstLib.h>
#include <dllLib.h>
#include <stat.h>
#include <errnoLib.h>
#include <rebootLib.h>
#include <flash.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define true    1
#define false   0 

#define FSIM_ID_NULL    0 

/* flash cell type */

/* configuration */

#define FSIM_CONFIG_CHIP_IDS_SIZE       4
#define FSIM_CONFIG_CHIP_ID0            0x66   /* 'F' */
#define FSIM_CONFIG_CHIP_ID1            0x53   /* 'S' */
#define FSIM_CONFIG_CHIP_ID2            0x49   /* 'I' */
#define FSIM_CONFIG_CHIP_ID3            0x4D   /* 'M' */

/* the delay time in microseconds */

#define FSIM_CONFIG_DELAY_READ_US       0       /* no delay */ 
#define FSIM_CONFIG_DELAY_WRITE_US      0       /* no delay */ 
#define FSIM_CONFIG_DELAY_ERASE_US      0       /* no delay */  

#define FSIM_CONFIG_LOG_LEVEL   0       /* TBD */
#define FSIM_CONFIG_STAT        0       /* TBD */
    
#define FSIM_HW_ECC_NONE        0       /* no hardware ECC */ 
#define FSIM_HW_ECC_1BIT        1       /* 1-BIT hardware ECC */ 
#define FSIM_HW_ECC_4BIT        2       /* 4-BIT hardware ECC */ 
#define FSIM_CONFIG_HW_ECC      FSIM_HW_ECC_NONE 

/* latency for flash operations */

#define FSIM_CONFIG_CHIP_RD_LATENCY 0
#define FSIM_CONFIG_CHIP_WR_LATENCY 0
#define FSIM_CONFIG_CHIP_ER_LATENCY 0

#define FSIM_CONFIG_NUM_FACTORY_BAD_BLKS    10

#define FSIM_CONFIG_UI
#define FSIM_CONFIG_UI_STAT
#define FSIM_CONFIG_UI_LOG
#define FSIM_CONFIG_UI_ERROR_INJ
#define FSIM_CONFIG_UI_DUMP

#define FSIM_MAGIC              0x6653494D  /* 'F' 'S' 'I' 'M' */
#define FSIM_CFG_MAGIC          FSIM_MAGIC  

#define FSIM_MAX_NAME_LEN       64

#define FSIM_HW_ECC_UNIT_SIZE   256     /* ECC unit size in bytes */    
#define FSIM_HW_ECC_BYTES       3       /* ECC bytes for each ECC unit */      

#define FSIM_OOB_ECC_SIZE(pageSize) ((pageSize / FSIM_HW_ECC_UNIT_SIZE) * \
                                     FSIM_HW_ECC_BYTES)

#define FSIM_MAX_NUM_CHIPS      1  /* only one chip is supported currently */ 

/* fsim ioctl functions */

#define FSIM_IOCTL_GET_INFO     0x1     /* get the information */

/* Error status codes */

#define FSIM_OK     0
#define FSIM_ERROR  -1

#define S_fsimLib_EBASE         1000
#define S_fsimLib_EPARAM        (S_fsimLib_EBASE + 1)   /* invalid parameter */
#define S_fsimLib_EMEM          (S_fsimLib_EBASE + 2)   /* memory error */
#define S_fsimLib_EIO           (S_fsimLib_EBASE + 3)   /* IO error */
#define S_fsimLib_EREBOOT       (S_fsimLib_EBASE + 4)   /* system reboot */
#define S_fsimLib_EBADBLOCK     (S_fsimLib_EBASE + 5)   /* bad block */
#define S_fsimLib_ECHIP         (S_fsimLib_EBASE + 6)   /* chip error */
#define S_fsimLib_ENOTRUNNING   (S_fsimLib_EBASE + 7)   /* fsim not running */
#define S_fsimLib_ENOTSTARTED   (S_fsimLib_EBASE + 8)   /* fsim not started */
#define S_fsimLib_EDEV          (S_fsimLib_EBASE + 9)   /* fsim device error */
#define S_fsimLib_EECC_REC      (S_fsimLib_EBASE + 10)  /* ecc recoverable error */
#define S_fsimLib_EECC_NOTREC   (S_fsimLib_EBASE + 11)  /* ecc unrecoverable error */
#define S_fsimLib_EECC_NOTREC_FAKE (S_fsimLib_EBASE + 12)  /* fake ecc unrecoverable error */
#define S_fsimLib_ENOTREC       (S_fsimLib_EBASE + 13)  /* unrecoverable error page */
#define S_fsimLib_EID           (S_fsimLib_EBASE + 14)  /* invalid id */

#define FSIM_ERR_ECC_REC        0x1     /* when re-written, it is cleared */
#define FSIM_ERR_ECC_NOT_REC    0x2     /* when re-written, it is cleared */
#define FSIM_ERR_ECC_NOT_REC_FAKE 0x4   /* when re-written, it is cleared */
#define FSIM_ERR_NOT_REC        0x8     /* it is a permanent error */
#define FSIM_ERR_BAD_BLOCK      0x10
#define FSIM_ERR_PARAM          0x20    /* invalid parameter */
#define FSIM_ERR_CHIP           0x40    /* chip error */

#define FSIM_ECC_OK_PATTERN     0xFF

#define FSIM_MAX_PAGE_SIZE      (1 << 12)

/* reboot type */

#define FSIM_REBOOT_CLEAN       0 
#define FSIM_REBOOT_UNCLEAN     1 

#define FSIM_ECC_NOT_REC_BITS   6

/* options for I/O operations on simulated flash device */

#define FSIM_OPT_DATA           0x1
#define FSIM_OPT_OOB            0x2 
#define FSIM_OPT_ECC            0x4
#define FSIM_OPT_MASK           (FSIM_OPT_DATA | FSIM_OPT_OOB | FSIM_OPT_ECC) 

#define FSIM_DUMP_DATA          0x1        /* dump the data area of a page */
#define FSIM_DUMP_OOB           0x2        /* dump the oob area of a page */

#define FSIM_PRINT_LINE_LEN     16
/* #define FSIM_PRINT_BUF_ASCII */        

/* statistics type */

#define FSIM_STAT_CHIP  1       /* chip statistics */
#define FSIM_STAT_BLK   2       /* block statistics */
#define FSIM_STAT_PAGE  4       /* page statistics */

#define SIZE_KB     (1 << 10)
#define SIZE_MB     (1 << 20)
#define SIZE_GB     (1 << 30)

#define IS_POWER2(var)  (((var) & (var - 1)) == 0) 

#define OOB_UNIT_SIZE   512
#define NAND_OOB_SIZE(pageSize) (((pageSize) / (OOB_UNIT_SIZE)) * 16) 

/* typedefs */

typedef long  FSIM_ID;  /* flash simulator identity type */

typedef long  FSIM_IOCTL_ARG_T;       /* ioctl argument type */ 

typedef SEM_ID  LOCK_T;                 /* lock type */

typedef void (* REBOOT_FUNCPTR) (int);  /* reboot function pointer */

typedef int bool;
typedef unsigned int            UINT;
typedef unsigned long long      UINT64;

typedef struct fsim_cfg         /* flash simulator configuration type */
    {
    FLASH_TYPE_T        flashType;      /* flash type: NAND, NOR, etc */
    FLASH_CELL_T        cellType;       /* SLC or MLC, NAND flash only */
    UINT64              totalSize;      /* total size of the flash */
    int                 pageSize;       /* page size */
    int                 nPagesPerBlk;   /* number of pages per block */
    /* ... */
    }FSIM_CFG;

typedef struct fsim_info        /* basic information of flash simulator */
    {
    UINT64      totalSize;      /* total size of the simulated flash */ 
    size_t      pageSize;       /* page size */
    size_t      nPagesPerBlk;   /* number of pages per block */
    size_t      nBlks;          /* total number of blocks */
    size_t      nPages;         /* total number of pages */
    size_t      oobSize;        /* oob size in bytes */
    }FSIM_INFO;

/* declarations */

int     fsimInit (void);

#ifdef useless 
FSIM_ID fsimCreateCfg (const char * name, int type, int totalSize, 
          int pageSize, int pagesPerBlk, int mediumType, char * mediumName);
#endif /* useless */

FSIM_ID fsimCreate (const char * pFSimName, const char * pMediumName, 
            FSIM_CFG * pCfgArg); 
STATUS  fsimDelete (FSIM_ID fsimId); 
STATUS  fsimDeleteName (const char * pName); 

int fsimPrintBuf (int fd, char * pBuf, size_t bufLen, int width);

/* user control */

STATUS  fsimStart (FSIM_ID fsimId);
STATUS  fsimRun (FSIM_ID fsimId);
STATUS  fsimStop (FSIM_ID fsimId);

FSIM_ID fsimMount (const char * fsimName, const char * devName);
STATUS  fsimUnmount (FSIM_ID fsimId);

/* direct I/O */

int fsimRead (FSIM_ID fsimId, UINT64 fromAddr, size_t length, 
                char * pBuf); 
int fsimWrite (FSIM_ID fsimId, UINT64 fromAddr, size_t length, 
                char * pBuf); 
int fsimReadPage  (FSIM_ID fsimId, size_t pageNo, off_t offset, size_t len,
               char * pBuf);
int fsimWritePage (FSIM_ID fsimId, size_t pageNo, off_t offset, size_t len,
               char * pBuf);
int fsimReadPages  (FSIM_ID fsimId, size_t fromPage, size_t nPages, 
                    char * buf, size_t bufLen, int option);
int fsimWritePages (FSIM_ID fsimId, size_t fromPage, size_t nPages, 
                    char * buf, size_t bufLen, int option);
int fsimErase (FSIM_ID fsimId, size_t blkNo, size_t nBlks);

FSIM_ID fsimIoctl (FSIM_ID fsimId, int cmd, FSIM_IOCTL_ARG_T arg);

#ifdef useless
STATUS fsimCorrupt (FSIM_ID fsimId, unsigned int pageNo);
STATUS fsimBitFlip (FSIM_ID fsimId, unsigned int pageNo, int nBits);
#endif /* useless */

STATUS fsimInjectError (FSIM_ID fsimId, size_t pageNo, int error);
STATUS fsimRemoveError (FSIM_ID fsimId, size_t pageNo, int error);
STATUS fsimMarkBad     (FSIM_ID fsimId, size_t blkNo);
STATUS fsimUnmarkBad   (FSIM_ID fsimId, size_t blkNo);
bool   fsimIsBadBlock  (FSIM_ID fsimId, size_t blkNo);
int    fsimIsBlankPage (FSIM_ID fsimId, size_t pageNo, BOOL * pResult);

STATUS fsimStatPage (FSIM_ID fsimId, int statFd, size_t pageNo,
                     size_t nPages);
STATUS fsimStatBlk (FSIM_ID fsimId, int statFd, size_t blkNo, 
                    size_t nBlks);
STATUS fsimStatChip (FSIM_ID fsimId, int statFd);
#ifdef useless
STATUS fsimStat (FSIM_ID fsimId, int statFd, int type, unsigned int blkNo,
                 unsigned int nBlks);
#endif  /* useless */

STATUS fsimDump (FSIM_ID fsimId, int dumpFd, int type, size_t pageNo,
                 size_t nPages);

STATUS fsimShow (FSIM_ID);
STATUS fsimShowAll (void);

STATUS fsimReboot(FSIM_ID fsimId, int type, TASK_ID taskId, 
            REBOOT_FUNCPTR rebootFunc);

#ifdef __cplusplus
}
#endif

#endif /* __INCfsimLibh */

