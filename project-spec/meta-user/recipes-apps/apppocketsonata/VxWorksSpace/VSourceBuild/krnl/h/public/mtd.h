/* mtd.h -  mtd user configure defines */

/*
 * Copyright (c) 2012, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
13may15,txu  fix V7STO-358 : wrong include after extern "C"
01nov12,x_z  fixed documentation issues.
22oct12,x_z  added support for Flash usage.
25sep12,x_z  added optional flags;
             replaced scanBbt method with bbChk method.
19sep12,x_z  added OOB access flag.
18sep12,x_z  added and adjusted MTD read/write flags.
18sep12,jxu  integration with ftl.
03sep12,x_z  rewritten MTD user config structure;
             merged from ftlMtd.h.
31may12,m_y  written.
*/

#ifndef __INCmtdh
#define __INCmtdh

/* includes */

#include <dllLib.h>
#include <flash.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define MTD_NAME_LEN    16

/* typedefs */

/* config structure */

/* MTD Flash chip config structure */

typedef struct mtd_flash_chip_cfg
    {
    DL_NODE             node;                   /* linked to chip list */
    char                devName[MTD_NAME_LEN];  /* Flash device name */
    UINT32              uDevUnit;               /* Flash device unit */
    UINT32              uChipId;                /* Flash chip index */
    DL_LIST             partList;               /* Flash physical */
                                                /* partition list */
    UINT32              uOp;
    } MTD_FLASH_CHIP_CFG, *pMTD_FLASH_CHIP_CFG;

/* MTD Flash partition config structure */

typedef struct mtd_flash_part_cfg
    {
    DL_NODE             node;                   /* linked to Flash */
                                                /* partition list */
    FLASH_BLK_ADDR_T    uBlkAddr;               /* start block address */
    FLASH_BLK_ADDR_T    uBlkCnt;                /* block count */
    char                mtdName[MTD_NAME_LEN];  /* MTD device name */
    UINT32              uGrpId;                 /* Flash group index */
    FLASH_USAGE_TYPE_T  flashUsage;             /* Flash usage */
    UINT32              uOp;                    /* opinion */
    } MTD_FLASH_PART_CFG, *pMTD_FLASH_PART_CFG;

/* MTD geometry structure */

typedef struct mtd_dev_node
    {
    DL_NODE             node;                   /* link to group list */
    char                mtdName[MTD_NAME_LEN];  /* MTD device name */
    FLASH_USAGE_TYPE_T  flashUsage;             /* Flash usage */
    DL_LIST             grpList;                /* Flash group list */
    UINT32              uOp;                    /* opinion */
    } MTD_DEV_NODE, *pMTD_DEV_NODE;

/* MTD group node structure */

typedef struct mtd_flash_group_node
    {
    DL_NODE             node;                   /* link to group list */
    DL_LIST             partList;               /* Flash physical */
                                                /* partition list */
    UINT32              uOp;                    /* opinion */
    } MTD_FLASH_GROUP_NODE, *pMTD_FLASH_GROUP_NODE;

/* MTD Flash partition node structure */

typedef struct mtd_flash_part_node
    {
    DL_NODE             node;                   /* link to part list */
    char *              pDevName;               /* Flash device name */
    UINT32              uDevUnit;               /* Flash device unit */
    UINT32              uChipId;                /* Flash chip index */
    FLASH_BLK_ADDR_T    uBlkAddr;               /* start block address */
    FLASH_BLK_ADDR_T    uBlkCnt;                /* block count */
    UINT32              uOp;                    /* opinion */
    } MTD_FLASH_PART_NODE, *pMTD_FLASH_PART_NODE;

/* MTD operation status */

typedef enum mtd_op_sta
    {
    MTD_OP_OK = 1,          /* succeeded for all the operations */
    MTD_OP_BAD_PARAM,       /* bad parameters for all the operations */
    MTD_OP_FAIL,            /* failed to write/erase/move */
    MTD_OP_ERR_CECC,        /* failed to read/move with correctable ECC */
                            /* error */
    MTD_OP_ERR_UCECC,       /* failed to read/move with uncorrectable ECC */
                            /* error */
    MTD_OP_ERR_FAKED_ECC,   /* OK to read with faked ECC error */
    MTD_OP_ERR              /* other error for all the operations */
    } MTD_OP_STA;

struct  mtd_desc;
typedef struct mtd_desc MTD_DESC;

/*
 * MTD operation parameter structure
 *
 * Note: for all the read operations, if one ECC error is found for one page,
 * the operation will return, and the data for the previous pages (included the
 * error page) will be returned.
 */

/*
 * normal read/write parameter
 *
 * Note:
 * 1. If the page data need only be read/written, the boundary is the page size;
 * 2. If the OOB need be read/written with/without the page data, the boundary
 * is (page size + available OOB size);
 * 4. The data and OOB will be placed in the buffer by the following sequence:
 *
 *     <Page 0 Data> <Page 0 OOB> <Page 1 Data> <Page 1 OOB> ....
 * 5. The length to be read/written can be any value.
 */

typedef struct mtd_rw_param
    {
    FLASH_NORM_ADDR_T       addr;       /* start address */
    FLASH_SIZE_T            uLen;       /* length to be read/write */
    UINT8 *                 pBuf;       /* pointer to buffer */
    FLASH_SIZE_T            uFinLen;    /* finished data length */
    FLASH_NORM_ADDR_AL_T    errAddr;    /* error address */
    UINT32                  uFlags;     /* flags */
    void *                  pOp;        /* opinion */
    } MTD_RW_PARAM, *pMTD_RW_PARAM;

/* scatter-gather read/write parameter */

typedef struct mtd_sgrw_param
    {
    FLASH_SGBUF_T *         pBuf;       /* pointer to buffer array */
    FLASH_SGBUF_T *         pErrBuf;    /* pointer to first error buffer */
    UINT32                  uFlags;     /* flags */
    void *                  pOp;        /* opinion */
    } MTD_SGRW_PARAM, *pMTD_SGRW_PARAM;

/* flag defines */

#define MTD_FLAG_WR_ERR_PAGE    0x01    /* write page with uncorrectable ECC */
#define MTD_FLAG_WR_VERIFY      0x02    /* write page and read back to verify */
#define MTD_FLAG_RW_RAW         0x04    /* read/write without ECC */
#define MTD_FLAG_RW_OOB         0x08    /* OOB need be accessed */

/* just for MTD internal, and ignored by MTD interfaces */

#define MTD_FLAG_RW_DATA        0x10    /* data need be accessed */
#define MTD_FLAG_RD             0x20    /* read operation */
#define MTD_FLAG_WR             0x40    /* write operation */

typedef struct mtd_era_param
    {
    FLASH_BLK_ADDR_T        uBlkAddr;   /* block address */
    FLASH_BLK_ADDR_T        uBlkCnt;    /* block number */
    FLASH_BLK_ADDR_T        uFinBlkCnt; /* finished block count */
    void *                  pOp;        /* opinion */
    } MTD_ERA_PARAM, *pMTD_ERA_PARAM;

/* all the pages must be in one block */

typedef struct mtd_mv_param
    {
    FLASH_NORM_ADDR_AL_T    srcAddr;        /* source page address */
    FLASH_NORM_ADDR_AL_T    dstAddr;        /* distance page address */
    FLASH_PAGE_ADDR_T       uPageCnt;       /* page count */
    FLASH_PAGE_ADDR_T       uFinPageCnt;    /* finished page count */
    void *                  pOp;            /* opinion */
    } MTD_MV_PARAM, *pMTD_MV_PARAM;/* MTD operation structure */

/* bad block check parameter */

 typedef struct mtd_bbchk_param
    {
    FLASH_BLK_ADDR_T    uBlkAddr;   /* block address to be checked */
    BOOL                bBadBlk;    /* bad block flag */
    void *              pOp;        /* opinion */
    } MTD_BBCHK_PARAM, *pMTD_BBCHK_PARAM;

/* MTD descriptor */

typedef struct mtd_desc
    {
    const char *        pMtdName;       /* MTD device name */

    FLASH_TYPE_T        flashType;      /* MTD device type */
    FLASH_CELL_T        cellType;       /* for nand flash only */
    FLASH_SIZE_T        uTotalSize;     /* total size of this device */
    FLASH_BLK_ADDR_T    uBlkCnt;        /* total number of flash blocks */
    FLASH_BLK_SIZE_T    uBlkSize;       /* block size */
    FLASH_SIZE_T        uPagesPerBlk;   /* page number per block */
    FLASH_PAGE_SIZE_T   uPageSize;      /* page size */
    FLASH_OOB_SIZE_T    uOobSizeAvail;  /* available OOB size to FTL */

    void *              pMtdDev;        /* private pointer for MTD device */

    int (*read)
        (
        MTD_DESC *          pMtdDesc,
        MTD_RW_PARAM *      pRwParam
        );

    int (*write)
        (
        MTD_DESC *          pMtdDesc,
        MTD_RW_PARAM *      pRwParam
        );

    /* routine to read/write from/to Flash with Scatter-Gather mode */

    int (*sgRead)
        (
        MTD_DESC *          pMtdDesc,
        MTD_SGRW_PARAM *    pSgParam
        );

    int (*sgWrite)
        (
        MTD_DESC *          pMtdDesc,
        MTD_SGRW_PARAM *    pSgParam
        );

     /* routine to read/write OOB datas */

    int (*oobRead)
        (
        MTD_DESC *          pMtdDesc,
        MTD_RW_PARAM *      pRwParam
        );

    int (*oobWrite)
        (
        MTD_DESC *          pMtdDesc,
        MTD_RW_PARAM *      pRwParam
        );

    /* routine to erase blocks */

    int (*blkErase)
        (
        MTD_DESC *          pMtdDesc,
        MTD_ERA_PARAM *     pEraParam
        );

    /* routine to move data */

    int (*move)
        (
        MTD_DESC *          pMtdDesc,
        MTD_MV_PARAM *      pMvParam
        );

    /* routine to check factory bad block */

    int (*bbChk)
        (
        MTD_DESC *          pMtdDesc,
        MTD_BBCHK_PARAM *   pBbChkParam
        );

    void *              pOp;            /* reserve for future usage */
    } MTD_DESC, *pMTD_DESC;

/* MTD module initialization */

IMPORT int mtdInit (DL_LIST * pChipList, DL_LIST * pMtdList);

/*
 * After MTD device has been created, the following attach/detach routine can be
 * used to attach/detach one MTD device with the specified usage or name to one
 * upper layer.
 *
 * Note: MTD list can be released after finish of attach operation.
 */

typedef STATUS (*pMTD_ATTACH_RTN) (pMTD_DESC pMtdDesc, void * pOp);

IMPORT STATUS mtdAttach
    (
    FLASH_USAGE_TYPE_T  flashUsage,
    pMTD_ATTACH_RTN     pMtdAttachRtn,
    void *              pOp
    );
IMPORT STATUS mtdDetach
    (
    char *              pMtdName,
    void *              pOp
    );

#ifdef __cplusplus
}
#endif

#endif /* __INCmtdh */

