/* vxbFlashCommon.h - Flash Driver Public Head File */

/*
 * Copyright (c) 2011-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01c,14jan13,y_y  add flash chip type.
01j,11jan13,x_z  added new APIs for lock functions and marked old APIs to be
                 obsoleted.
01i,20dec12,x_z  adjusted moving function capability defines.
01h,07dec12,x_z  adjusted Flash chip capability defines;
                 added Flash read/write flags;
                 removed OOB sequential access routines.
01g,01nov12,x_z  fixed documentation issue for FLASH_OP_WR_BAD_PAGE.
01f,01nov12,x_z  fixed documentation issues.
01e,25sep12,x_z  replaced scanBbt method with bbChk method;
                 updated description for sequential read/write parameter;
                 added read/write operations.
01f,20aug12,x_z  fixed compatibility issue with old Flash type defines.
01e,08aug12,m_y  modify FLASH_ERA_PARAM add opinion defines.
01d,07aug12,x_z  modified for new FTL/MTD/Flash interfaces.
01c,29may12,m_y  modify flash_ops.
01b,17apr12,x_z  fixed GNU compiling warnings.
01a,30dec11,x_z  created.
*/

#ifndef __INCvxbFlashCommonh
#define __INCvxbFlashCommonh

#include <flash.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Note: for all the read operations, if one ECC error is found for one page,
 * the operation will return, and the data for the previous pages (included the
 * error page) will be returned.
 */

/*
 * sequential read/write parameter
 *
 * Note:
 * 1. If the page data need only be read/written, the boundary is the page size;
 * 2. If the OOB need be read/written wit/without the page data, the boundary is
 * (page size + available OOB size);
 * 4. The data and OOB will be placed in the buffer by the following sequence:
 *
 *     <Page 0 Data> <Page 0 OOB> <Page 1 Data> <Page 1 OOB> ....
 * 5. The length to be read/written can be any value.
 */

typedef struct flash_seqrw_param
    {
    FLASH_ADDR_T        uAddr;      /* start address */
    UINT32              uLen;       /* length to be read/write */
    UINT8 *             pBuf;       /* pointer to buffer */
    FLASH_SIZE_T        uFinLen;    /* finished data length */
    FLASH_ADDR_T        uErrAddr;   /* error address */
    UINT32              uFlag;      /* flag */
    void *              pOp;        /* opinion */
    } FLASH_SEQRW_PARAM, *pFLASH_SEQRW_PARAM;

/* scatter-gather read/write parameter */

typedef struct flash_sgrw_param
    {
    FLASH_SGBUF_T *     pBuf;       /* pointer to buffer array */
    FLASH_SIZE_T        uBufCnt;    /* buffers count */
    FLASH_SGBUF_T *     pErrBuf;    /* pointer to first error buffer */
    UINT32              uFlag;      /* flag */
    void *              pOp;        /* opinion */
    } FLASH_SGRW_PARAM, *pFLASH_SGRW_PARAM;

/* flag defines */

/*
 * flag to wite page with bad data after uncorrectable ECC error is found
 *
 * Note: raw mode flag will be ignored if this flag is used, and the old ECC
 * will be used with bad data.
 */

#define FLASH_OP_WR_BAD_PAGE    0x01

#define FLASH_OP_WR_VERIFY      0x02    /* write page and read back to verify */
#define FLASH_OP_RW_RAW         0x04    /* read/write without ECC */
#define FLASH_OP_RW_OOB         0x08    /* OOB need be accessed */
#define FLASH_OP_RW_DA          0x10    /* data need be accessed */

/* enhanced block erase parameter */

typedef struct flash_blkera_param
    {
    FLASH_BLK_ADDR_T    uBlkAddr;   /* block address */
    FLASH_BLK_ADDR_T    uBlkCnt;    /* block number */
    FLASH_BLK_ADDR_T    uFinBlkCnt; /* finished block count */
    void *              pOp;        /* opinion */
    } FLASH_BLKERA_PARAM, *pFLASH_BLKERA_PARAM;

/*
 * move parameter
 *
 * Note:
 *  1. Source and distance address must be aligned with page size;
 *  2. Both data and OOB will be moved;
 *  3. all the pages must be in one block.
 */

typedef struct flash_mv_param
    {
    FLASH_ADDR_T        uSrcAddr;   /* source page address */
    FLASH_ADDR_T        uDstAddr;   /* distance page address */
    FLASH_SIZE_T        uPageCnt;   /* page count */
    FLASH_SIZE_T        uFinPageCnt;/* finished page count */
    void *              pOp;        /* opinion */
    } FLASH_MV_PARAM, *pFLASH_MV_PARAM;

/* block lock/unlock and lock status check parameter */

typedef struct flash_blklock_param
    {
    FLASH_BLK_ADDR_T    uBlkAddr;   /* block address */
    FLASH_BLK_ADDR_T    uBlkCnt;    /* block number */
    BOOL                lock;       /* TRUE - lock FALSE - unlock */
    FLASH_BLK_ADDR_T    uFinBlkCnt; /* finished block count */
    void *              pOp;        /* opinion */
    } FLASH_LOCK_PARAM, *pFLASH_LOCK_PARAM;

/* bad block check parameter */

 typedef struct flash_bbchk_param
    {
    FLASH_BLK_ADDR_T    uBlkAddr;   /* block address to be checked */
    BOOL                bBadBlk;    /* bad block flag */
    void *              pOp;        /* opinion */
    } FLASH_BBCHK_PARAM, *pFLASH_BBCHK_PARAM;

/* Flash chip operation structure */

struct flash_chip;
typedef struct flash_chip FLASH_CHIP, *pFLASH_CHIP, *FLASH_CHIP_ID;
typedef struct flash_ops
    {

    /* routine to reset Flash */

    int (*rst)
        (
        FLASH_CHIP_ID       pFlashChip
        );

    /* optional functions */

    /* routine to sequential read/write data from/to NAND Flash */

    int (*seqRead)
        (
        FLASH_CHIP_ID       pFlashChip,
        pFLASH_SEQRW_PARAM  pFlashParam
        );
    int (*seqWrite)
        (
        FLASH_CHIP_ID       pFlashChip,
        pFLASH_SEQRW_PARAM  pFlashParam
        );

    /* routine to read/write from/to Flash with Scatter-Gather mode */

    int (*sgRead)
        (
        FLASH_CHIP_ID       pFlashChip,
        pFLASH_SGRW_PARAM   pFlashParam
        );
    int (*sgWrite)
        (
        FLASH_CHIP_ID       pFlashChip,
        pFLASH_SGRW_PARAM   pFlashParam
        );

    /* enhanced routine to erase blocks */

    int (*eBlkErase)
        (
        FLASH_CHIP_ID       pFlashChip,
        pFLASH_BLKERA_PARAM pFlashParam
        );

    /* routine to move data on NAND Flash */

    int (*move)
        (
        FLASH_CHIP_ID       pFlashChip,
        pFLASH_MV_PARAM     pFlashParam
        );

    /* enhanced routine to lock/unlock blocks */

    int (*eBlkLock)
        (
        FLASH_CHIP_ID       pFlashChip,
        pFLASH_LOCK_PARAM   pFlashParam
        );

    /* routine to check lock status for blocks */

    int (*blkLockChk)
        (
        FLASH_CHIP_ID       pFlashChip,
        pFLASH_LOCK_PARAM   pFlashParam
        );

    /* routine to check factory bad block for NAND Flash */

    int (*bbChk)
        (
        FLASH_CHIP_ID       pFlashChip,
        pFLASH_BBCHK_PARAM  pFlashParam
        );

    /* functions to be obsoleted (will be removed in the future) */

    /*
     * routine to enable/disable the operations to Flash
     *
     * Note: this function has been  and will be removed in future,
     * but need be implemented to do nothing now.
     */

    int (*ena)
        (
        struct flash_chip * pFlashChip,
        BOOL                enable, /* TRUE- enable FALSE - disable*/
        void *              op      /* opinion */
        );

    /*
     * routine to read/write from/to Flash
     *
     * Note: the 2 routines have been obsoleted and will be removed in future.
     * .
     */

    int (*read)
        (
        struct flash_chip * pFlashChip,
        FLASH_ADDR_T        uAddr,      /* offset to Flash */
        UINT32              uBufCount,  /* buffer count */
        FLASH_SIZE_T        uBufLen,    /* length for every buffer */
        UINT8 **            ppBuf,      /* pointer to buffer array */
        void *              op          /* opinion */
        );

    int (*write)
        (
        struct flash_chip * pFlashChip,
        FLASH_ADDR_T        uAddr,      /* offset to Flash */
        UINT32              uBufCount,  /* buffer count */
        FLASH_SIZE_T        uBufLen,    /* length for every buffer */
        UINT8 **            ppBuf,      /* pointer to buffer array */
        void *              op          /* opinion */
        );

    /* routine to read/write OOB data from/to NAND Flash */

    int (*oobRead)
        (
        struct flash_chip * pFlashChip,
        FLASH_ADDR_T        uAddr,      /* page address */
        UINT32              uBufCount,  /* buffer count */
        UINT8  **           ppBuf,      /* pointer to buffer array */
        FLASH_SIZE_T        oobLen      /* length for every buffer */
        );

    int (*oobWrite)
        (
        struct flash_chip * pFlashChip,
        FLASH_ADDR_T        uAddr,      /* page address */
        UINT32              uBufCount,  /* buffer count */
        UINT8  **           ppBuf,      /* pointer to buffer array */
        FLASH_SIZE_T        oobLen      /* length for every buffer */
        );

    /*
     * routine to erase blocks
     *
     * Note: block address must be aligned with block size.
     */

    int (*blkErase)
        (
        struct flash_chip * pFlashChip,
        FLASH_ADDR_T        uBlkAdrs,   /* block address */
        UINT32              uBlks       /* block number */
        );

    /* routine to lock/unlock one block */

    int (*blkLock)
        (
        FLASH_CHIP_ID       pFlashChip,
        FLASH_ADDR_T        uBlkAdrs,   /* block address */
        BOOL                lock        /* TRUE- lock FALSE - unlock */
        );

    /* routine to get lock status for one block */

    int (*blkLockQry)
        (
        FLASH_CHIP_ID       pFlashChip,
        FLASH_ADDR_T        uBlkAdrs,   /* block address */
        BOOL *              pLock       /* TRUE- locked FALSE - unlocked */
        );
    }FLASH_OPS, *pFLASH_OPS;

/* Flash chip type defines */

typedef enum flash_chip_type
    {
    FLASH_CHIP_TYPE_NOR = 1,
    FLASH_CHIP_TYPE_NAND = 2,
    FLASH_CHIP_TYPE_SPI = 3
    } FLASH_CHIP_TYPE;

/* Flash chip interface */

#define FLASH_CHIP_NAME_LEN   64
struct flash_chip
    {
    void *              pDev; /* device handler to Flash chip */

    /* Chip Attribute */

    UINT8               chipName[FLASH_CHIP_NAME_LEN]; /* Flash chip name */
    FLASH_SIZE_T        uChipSize;   /* Flash chip size */
    FLASH_BLK_SIZE_T    uEraseSize;  /* size for one erase unit */
    FLASH_PAGE_SIZE_T   uPageSize;   /* page size (must be 0 for Flash */
                                     /* without page support, such as NOR) */
    FLASH_OOB_SIZE_T    uOobAvlSize; /* available OOB size */

    FLASH_CHIP_TYPE     uFlashType;  /* Flash chip type */
    UINT32              uCapability; /* Flash chip capabilities */
    FLASH_OPS           flashOPs;    /* Flash operation hooks */
    void *              pFlashInfo;  /* Flash private information */
    void *              pPriv;       /* reserve for future usage */
    };

typedef enum flash_err_type
    {
    FLASH_INV_PARAM_ERR = 1,
    FLASH_OP_FAIL_ERR,
    FLASH_CORRECT_ECC_ERR,
    FLASH_UNCORRECT_ECC_ERR,
    FLASH_FAKE_ECC_ERR,
    FLASH_OTHER_ERR
    } FLASH_ERR_TYPE;

/* Flash chip capability defines */

/* functions */

#define FLASH_CHIP_CAP_SEQRD        0x0001  /* sequential read from Flash */
#define FLASH_CHIP_CAP_SEQWR        0x0002  /* sequential write to Flash */
#define FLASH_CHIP_CAP_SGRD         0x0004  /* scatter-gather read from Flash */
#define FLASH_CHIP_CAP_SGWR         0x0008  /* scatter-gather write to Flash */
#define FLASH_CHIP_CAP_EBLKERA      0x0010  /* enhanced block erase */
#define FLASH_CHIP_CAP_MV           0x0020  /* move function */
#define FLASH_CHIP_CAP_EBLKLOCK     0x0040  /* enhanced block lock/unlock */
#define FLASH_CHIP_CAP_BLKLOCKCHK   0x0080  /* lock status check */
#define FLASH_CHIP_CAP_BBCHK        0x0100  /* bad block check */

/* function details (used with corresponding function bits) */

/*
 * move function limit
 *
 * Some NAND Flash has the moving function limit, or odd to odd block and even
 * to even block moving function are supported only, or only odd to odd page and
 * even to even page moving function are supported only.
 */

#define FLASH_CHIP_CAP_MV_O2EB_LIMT 0x00010000
#define FLASH_CHIP_CAP_MV_O2EP_LIMT 0x00020000

/*
 * non-sequential page write
 *
 * For NAND Flash, if this bit is set to 1, then all the pages within a block
 * can be programed in arbitrary order; or, all the pages within a block can
 * only be programed in order starting with page 0.
 */

#define FLASH_CHIP_CAP_NSEQ_PROG    0x00040000

/* functions to be obsoleted (will be removed in the future) */

#define FLASH_CHIP_CAP_RD           0x01000000  /* read from Flash */
#define FLASH_CHIP_CAP_WR           0x02000000  /* write to Flash */
#define FLASH_CHIP_CAP_OOBRD        0x04000000  /* OOB read */
#define FLASH_CHIP_CAP_OOBWR        0x08000000  /* OOB write */
#define FLASH_CHIP_CAP_BLKERA       0x10000000  /* block erase */
#define FLASH_CHIP_CAP_BLKLOCK      0x20000000  /* block lock/unlock */
#define FLASH_CHIP_CAP_BLKLOCKQRY   0x40000000  /* lock status query */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbFlashCommonh */

