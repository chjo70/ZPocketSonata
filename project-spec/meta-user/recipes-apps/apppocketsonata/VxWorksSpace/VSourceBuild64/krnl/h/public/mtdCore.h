/* mtdCore.h - mtd module code */

/*
 * Copyright (c) 2012, 2013, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
04feb16,dee  fix diab compiler warnings, after suppressions remove, after suppressions removed
29oct13,ywu  fixed compilling warning for WIND00440928.
24dec12,x_z  added statistics support.
07dec12,x_z  removed unused OOB access macros.
01nov12,x_z  fixed compiling warnings.
22oct12,x_z  added support for Flash usage.
10oct12,x_z  adjusted MTD device and Flash operation information structure;
             adjusted for mtd.h.
25sep12,x_z  adjusted MTD Flash operation information structure;
             replaced scanBbt method with bbChk method.
03sep12,x_z  redefine MTD device to support sequential/parallel
             partition support for one MTD;
             added Flash access macros;
             code clean.
15aug12,x_z  fixed compiling issue.
31may12,m_y  written.
*/

#ifndef __INCMtdh
#define __INCMtdh

#include <vxWorks.h>
#include <memLib.h>
#include <dllLib.h>
#include <logLib.h>
#include <semLib.h>

#include <flash.h>
#include <vxbFlashCommon.h>
#include <mtd.h>

#ifdef  __cplusplus
extern "C" {
#endif

/* MTD Flash partition structure */

typedef struct mtd_flash_part
    {
    char *              pDevName;       /* Flash device name */
    UINT32              uDevUnit;       /* Flash device unit */
    UINT32              uChipId;        /* Flash chip index */
    FLASH_BLK_ADDR_T    uBlkAddr;       /* start block address */
    FLASH_CHIP_ID       pFlashChip;     /* Flash chip ID */
    UINT32              uOp;            /* opinion */
    } MTD_FLASH_PART, *pMTD_FLASH_PART;

/* MTD group structure */

typedef struct mtd_flash_group
    {
    pMTD_FLASH_PART     pPart;          /* Flash physical */
                                        /* partition information */
    FLASH_BLK_ADDR_T    uMtdBlkAddr;    /* mapped MTD block address */
    FLASH_BLK_ADDR_T    uBlkCnt;        /* block count in group */
    FLASH_BLK_ADDR_T    uBlkCntPerPart; /* block count per */
                                        /* partition */
    UINT32              uOp;            /* opinion */
    } MTD_FLASH_GROUP, *pMTD_FLASH_GROUP;

/* MTD device structure */

typedef struct mtd_dev
    {
    DL_NODE             node;           /* linked to MTD device list */
    char *              pMtdName;       /* MTD device name */
    FLASH_USAGE_TYPE_T  flashUsage;     /* Flash usage */
    FLASH_CHIP_TYPE     chipType;       /* Flash chip type */
    UINT32              uGrpCnt;        /* Flash group count */
    pMTD_FLASH_GROUP    pGrp;           /* Flash group information */
    FLASH_SIZE_T        uTotalSize;     /* total size */
    UINT32              uPartPerGrp;    /* partition count per group */
    FLASH_BLK_ADDR_T    uBlkCnt;        /* block count */
    FLASH_BLK_SIZE_T    uBlkSize;       /* Block size in byte */
    FLASH_PAGE_ADDR_T   uPagesPerBlk;   /* page count per block */
    FLASH_PAGE_SIZE_T   uPageSize;      /* Page size in byte */
    FLASH_OOB_SIZE_T    uOobAvlSize;    /* OOB available size for upper layer */
    UINT32              uBlkAddrShift;  /* block address shift */
    UINT32              uPageAddrShift; /* page address shift */
    UINT32              uCap;           /* common Flash chip capabilities */

    MTD_DESC            mtdDesc;        /* pointer to attached MTD descriptor */
    UINT8 *             pPageBuf;       /* page buffer */
    SEM_ID              opSem;          /* operation semaphore */
    UINT32              uFlag;          /* flag */

    /* statistics counters */

    FLASH_SIZE_T            uEraBlkCnt;
    FLASH_SIZE_T            uWrPageCnt;
    FLASH_SIZE_T            uRdPageCnt;
    } MTD_DEV, *pMTD_DEV;

/* MTD flag defines */

#define MTD_DEV_FLAG_ATTCHED    0x01    /* attached to upper layer */

/* MTD Flash operation information */

typedef struct mtd_flash_opinfo
    {
    UINT32              uGrpId;         /* group index */
    UINT32              uPartId;        /* partition index */
    pMTD_FLASH_GROUP    pGrp;           /* group information */
    pMTD_FLASH_PART     pPart;          /* partition information */
    FLASH_CHIP_ID       pFlashChip;     /* Flash chip ID */
    FLASH_BLK_ADDR_T    uPartBlkAddr;   /* block address to partition */
    FLASH_BLK_ADDR_T    uFlashBlkAddr;  /* block address to Flash */
    } MTD_FLASH_OPINFO, *pMTD_FLASH_OPINFO;

/* Flash operations */

#define MTD_RD(pOpInfo, pOpsParam)      \
    (pOpInfo)->pFlashChip->flashOPs.seqRead ((pOpInfo)->pFlashChip, pOpsParam)

#define MTD_WR(pOpInfo, pOpsParam)      \
    (pOpInfo)->pFlashChip->flashOPs.seqWrite ((pOpInfo)->pFlashChip, pOpsParam)

#define MTD_SGRD(pOpInfo, pOpsParam)    \
    (pOpInfo)->pFlashChip->flashOPs.sgRead ((pOpInfo)->pFlashChip, pOpsParam)
#define MTD_SGWR(pOpInfo, pOpsParam)    \
    (pOpInfo)->pFlashChip->flashOPs.sgWrite ((pOpInfo)->pFlashChip, pOpsParam)

#define MTD_BLKERA(pOpInfo, pOpsParam)  \
    (pOpInfo)->pFlashChip->flashOPs.eBlkErase ((pOpInfo)->pFlashChip, pOpsParam)

#define MTD_BBCHK(pOpInfo, pOpsParam)    \
    (pOpInfo)->pFlashChip->flashOPs.bbChk ((pOpInfo)->pFlashChip, pOpsParam)

#define MTD_MV(pOpInfo, pOpsParam)      \
    (pOpInfo)->pFlashChip->flashOPs.move ((pOpInfo)->pFlashChip, pOpsParam)

/* define to enable debug information */

#define MTD_DBG
#ifdef MTD_DBG
#   define MTD_MSG(fmt, a, b, c, d, e, f)           \
        if (_func_logMsg != NULL)                       \
            _func_logMsg ("MTD: "fmt, (_Vx_usr_arg_t) (a), \
                          (_Vx_usr_arg_t) (b), (_Vx_usr_arg_t) (c), \
                          (_Vx_usr_arg_t) (d), (_Vx_usr_arg_t) (e), \
                          (_Vx_usr_arg_t) (f))
#else /* !MTD_DBG */
#   define MTD_MSG(fmt, ...)
#endif /* MTD_DBG */

/* MTD operation routines */

IMPORT pMTD_DEV mtdDevMatch
    (
    char *              pMtdName,
    FLASH_USAGE_TYPE_T  flashUsage,
    pMTD_DEV *          ppStartMtdDev
    );
IMPORT int mtdRw
    (
    pMTD_DEV            pMtdDev,
    MTD_RW_PARAM *      pMtdOpsParam,
    UINT32              uOpType
    );

/* MTD read/write operation */

#define MTD_RW_OP_RD    0x01
#define MTD_RW_OP_WR    0x02
#define MTD_RW_OP_DATA  0x04
#define MTD_RW_OP_OOB   0x08

/* statistics counter enabled flag */

IMPORT BOOL mtdStatCntEn;

/* MTD chip/device information */

IMPORT DL_LIST *   pMtdChipList;
IMPORT DL_LIST     mtdDevList;

#ifdef  __cplusplus
     }
#endif

#endif
