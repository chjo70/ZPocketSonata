/* vxbNandFlashLib.h - Generic NAND Flash Library Header */

/*
 * Copyright (c) 2012-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01jun16,ffu  add _WRS_CONFIG_NAND_INTERNAL_ECC to support nand auto ECC(F7019)
19may16,ffu  add _WRS_CONFIG_NAND_FLASH_ECC_FORMAT to support more complex ECC(F7019)
13may15,txu  fix V7STO-358 : wrong include after extern "C"
27may14,ywu  fixed address truncation of NAND_CMD_ISSUE. (V7STO-173)
             fixed NAND_OOB_BITMAP_SIZE() when oob size can't devided by 8
             on some MLC chip. (V7STO-173)
30jul13,ywu  add support for single cycle long address type
20dec12,x_z  adjusted moving function capability defines.
07dec12,x_z  added support for ONFI;
             adjusted NAND ID structure;
             added Manufacturer ID defines and small page size define.
23nov12,x_z  adopted for new NAND library interface;
             fixed debug message macros;
             added statistics counters.
01nov12,x_z  added support for cached command seuqences;
             added user space layout information;
             adjusted vxbNandCmdIssue().
26oct12,x_z  added defines for buffer verification;
             replaced nandDbgLevel with vxbNandDbgLevel.
12oct12,x_z  removed NAND ID defines.
27sep12,x_z  fixed NAND_CA_FROM_FA.
04sep12,x_z  written.
*/

#ifndef __INCvxbNandFlashLibh
#define __INCvxbNandFlashLibh

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <logLib.h>

#include <nand/vxbNandFlash.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* NAND Flash Manufacturer ID */

#define NAND_MFRID_AMD          0x01    /* AMD/SPasion */
#define NAND_MFRID_FUJITSU      0x04
#define NAND_MFRID_RENESAS      0x07
#define NAND_MFRID_STMICRO      0x20
#define NAND_MFRID_MICRON       0x2C
#define NAND_MFRID_NATIONAL     0x8F
#define NAND_MFRID_TOSHIBA      0x98
#define NAND_MFRID_HYNIX        0xAD
#define NAND_MFRID_SAMSUNG      0xEC

/*
 * If page size is equal (less, but not found now) than 512 bytes, the NAND
 * Flash chip is called Small Page NAND Flash, and other is called Large Page
 * NAND Flash.
 */

#define NAND_SMALL_PAGE_SIZE    512

/* address transfer macros */

/* get page/column address from flat address */

#define NAND_PA_FROM_FA(pNandDesc, addr)    \
    ((addr) >> ((pNandDesc)->uPageShift + 1))
#define NAND_CA_FROM_FA(pNandDesc, addr)    \
    ((addr) & (((pNandDesc)->nandId.uPageSize << 1) - 1))

/* form flat address from page/column address  */

#define NAND_PACA_TO_FA(pNandDesc, pageAddr, colAddr)   \
    (((pageAddr) << ((pNandDesc)->uPageShift + 1)) | colAddr)

/* transfer block address to global page address */

#define NAND_BA_TO_PA(pNandDesc, blkAddr)   \
    ((blkAddr) << ((pNandDesc)->uBlkShift - (pNandDesc)->uPageShift))

/* NAND command type */

typedef enum nand_cmd_type
    {
    NAND_CMD_TYPE_CTRL = 1,         /* control signal */
    NAND_CMD_TYPE_CMD,              /* command */
    NAND_CMD_TYPE_COL_ADDR,         /* 1-cycle column address */
    NAND_CMD_TYPE_COL_ADDR_2CYC,    /* 2-cycle column address */
    NAND_CMD_TYPE_COL_ADDR_NOADJ,   /* column address must NOT be adjusted */
    NAND_CMD_TYPE_PAGE_ADDR,        /* 1-cycle page address */
    NAND_CMD_TYPE_PAGE_ADDR_2CYC,   /* 2-cycle page address */
    NAND_CMD_TYPE_PAGE_ADDR_3CYC,   /* 3-cycle page address */
    NAND_CMD_TYPE_RDY_CHK,          /* ready(R/B#) status check */
    NAND_CMD_TYPE_WAIT,             /* wait for finish of erase/program */
    NAND_CMD_TYPE_TRUEWAIT,         /* wait for actual finish of program */
    NAND_CMD_TYPE_OTHERWAIT,        /* wait status for other */
    NAND_CMD_TYPE_DARD,             /* read data from NAND */
    NAND_CMD_TYPE_DAIN,             /* input data to NAND */
    NAND_CMD_TYPE_OTHERRD,          /* read other from NAND */
#ifdef _WRS_CONFIG_NAND_INTERNAL_ECC
    NAND_CMD_TYPE_OTHERWR           /* write other from NAND */
#endif
    } NAND_CMD_TYPE;

#define NAND_COL_ADDR_MAX_CYC   2   /* maximum cycle number of column address */
#define NAND_PAGE_ADDR_MAX_CYC  3   /* maximum cycle number of page address */

/* command descriptor define */

typedef struct nand_cmd_desc
    {
    NAND_CMD_TYPE   type;
    UINT16          uCtrl;
    UINT16          uCode;
    } NAND_CMD_DESC, *pNAND_CMD_DESC;

/* command sequence define */

typedef struct nand_cmd_seq
    {
    UINT8           uStepCnt;
    NAND_CMD_DESC   cmdDesc[NAND_MAX_CMD_STEP];
    } NAND_CMD_SEQ, *pNAND_CMD_SEQ;

/* NAND command sequence index defines */

typedef enum nand_cmd_seq_id
    {
    /* control & identify operations */

    NAND_CMD_SEQ_RST = 0,               /* reset */
    NAND_CMD_SEQ_ID_RD,                 /* NAND ID read  */

    /* basic operations */

    NAND_CMD_SEQ_PAGE_RD,               /* page read*/
    NAND_CMD_SEQ_PAGE_PROG,             /* page program  */
    NAND_CMD_SEQ_OOB_RD,                /* OOB read */
    NAND_CMD_SEQ_OOB_PROG,              /* OOB program  */
    NAND_CMD_SEQ_BLK_ERA,               /* block erase  */

    /* advance operations */

    /* large page NAND only operations */

    /*
     * Random Read operation can be used only be used after normal page read
     * operation is issued.
     *
     * BTW: supported only by large page NAND
     */

    NAND_CMD_SEQ_PAGE_RNDRD,

    /*
     * Cahce Read operations can only be used after normal page read operation
     * is issued, and can be used for sequential pages only.
     *
     * BTW: supported optionally by large page NAND
     */

    NAND_CMD_SEQ_CACHE_PAGE_RD_ENTRY,   /* entry */
    NAND_CMD_SEQ_CACHE_PAGE_RD,         /* read none-last pages */
    NAND_CMD_SEQ_CACHE_PAGE_RD_EXIT,    /* read last page and exit */

    /*
     * Cahce Program operations can only be used before normal program operation
     * is issued.
     *
     * BTW: supported optionally by large page NAND
     */

    NAND_CMD_SEQ_CACHE_PAGE_PROG,       /* program none-last pages */
    NAND_CMD_SEQ_CACHE_PAGE_PROG_EXIT,  /* program last page and exit */

    /*
     * Copyback(Move) operations must be used in pairs
     *
     * BTW: supported optionally by small and large page NAND
     */

    NAND_CMD_SEQ_CP_RD,                 /* read for internal data move(copy) */
    NAND_CMD_SEQ_CP_IN,                 /* input for internal data move(copy) */

#ifdef _WRS_CONFIG_NAND_INTERNAL_ECC
    NAND_CMD_SET_FEATURE,               /* set feature for nand flash */
    NAND_CMD_GET_FEATURE,               /* get feature for nand flash */
#endif

    NAND_CMD_SEQ_MAX
    } NAND_CMD_SEQ_ID;

/* OOB layout defines */

typedef struct nand_oob_layout_info
    {

    /* bad block flag positions must be filled after chip is identified */

    NAND_OOB_LAYOUT_DESC    badBlkInfo[NAND_OOB_LAYOUT_CNT];

    /* ECC positions */

    NAND_OOB_LAYOUT_DESC    eccInfo[NAND_OOB_LAYOUT_CNT];

    /* offset to OOB for 1-byte Faked ECC flag */

    FLASH_PAGE_ADDR_T       uFakedEccOffset;

    /* user space positions */

    NAND_OOB_LAYOUT_DESC    usrSpaceInfo[NAND_OOB_LAYOUT_CNT];

    /* OOB layout bitmap(1 bit is for 1 OOB byte) */

    UINT8 *                 pBitMap;
    } NAND_OOB_LAYOUT_INFO, *pNAND_OOB_LAYOUT_INFO;

/* OOB layout bit map access macros */

#define NAND_OOB_BITMAP_SIZE(n)     ((n + 7) >> 3)
#define NAND_OOB_BITMAP_BYTE(n)     ((n) >> 3)
#define NAND_OOB_BITMAP_BIT(n)      ((n) & 7)

/* NAND flash ID structure  */

#define ONFI_PARAM_PAGE_LEN     256
typedef struct nand_flash_id
    {
    char *              pName;      /* manufacture name */
    UINT8               uMfrID;     /* manufacture ID */
    UINT8               uDevID;     /* device ID */
    FLASH_SIZE_T        uChipSize;  /* chip size(byte) */

    /* must be set if can NOT be probed */

    FLASH_BLK_SIZE_T    uBlkSize;   /* block size in byte */
    FLASH_PAGE_SIZE_T   uPageSize;  /* page size in byte */
    FLASH_OOB_SIZE_T    uOobSize;   /* total OOB size */
    UINT32              uCap;       /* capabilities */
    } NAND_FLASH_ID, *pNAND_FLASH_ID;

/* NAND capability defines */

#define NAND_CAP_2BYTE_NANDID       0x00000001 /* 2-byte NAND ID only */
#define NAND_CAP_ONFI               0x00000002 /* ONFI compatible NAND */
#define NAND_CAP_X16                0x00000004 /* x16 device */
#define NAND_CAP_LP                 0x00000008 /* large page NAND */
#define NAND_CAP_MLC                0x00000010 /* MLC NAND */
#define NAND_CAP_WP                 0x08000020 /* write-protected (read-only) */

#define NAND_CAP_CACHE_RD           0x00000040 /* cache readsupported */
#define NAND_CAP_CACHE_PROG         0x00000080 /* cache programming supported */
#define NAND_CAP_MV                 0x00000100 /* moving(copyback) supported */
#define NAND_CAP_MV_O2EB_LIMIT      0x00000200 /* odd to odd block and even */
                                               /* to even block moving */
                                               /* (copyback) supported only */
#define NAND_CAP_MV_O2EP_LIMIT      0x00000400 /* odd to odd page and even to */
                                               /* even page moving(copyback) */
                                               /* supported only*/
#define NAND_CAP_NSEQ_PROG          0x00000400 /* non-sequential page */
                                               /* programming */
#define NAND_CAP_COL_ADDR           0x00000800 /* 1-cycle column address */
#define NAND_CAP_COL_ADDR_2CYC      0x00001000 /* 2-cycle column address */
#define NAND_CAP_PAGE_ADDR          0x00002000 /* 1-cycle page address */
#define NAND_CAP_PAGE_ADDR_2CYC     0x00004000 /* 2-cycle page address */
#define NAND_CAP_PAGE_ADDR_3CYC     0x00008000 /* 3-cycle page address */
#define NAND_CAP_LONG_ADDR          0x00010000 /* every address in 1-cycle */

/* factory bad block flag defines */

#define NAND_CAP_BBSCAN_POS_1_6     0x01000000 /* scan OOB byte 1 & 6 for bad */
                                               /* block */
#define NAND_CAP_BBSCAN_LPG         0x02000000 /* scan last page for bad */
                                               /* block */
#define NAND_CAP_BBSCAN_FLPG        0x04000000 /* scan first and last page */
                                               /* for bad block */

#define NAND_CAP_BBSCAN_MASK            \
    (NAND_CAP_BBSCAN_POS_1_6 | NAND_CAP_BBSCAN_LPG | NAND_CAP_BBSCAN_FLPG)

#define NAND_BBFLAG_PAGE_CNT        2 /* 2 pages for bad block flag at most */
#define NAND_BBFLAG_SIZE            2 /* bad block flag size at most */

/* NAND flash descriptor */

struct nand_flash_desc;
typedef struct nand_flash_desc NAND_FLASH_DESC, *pNAND_FLASH_DESC;
struct nand_flash_desc
    {
    NAND_FLASH_INFO         nandInfo;       /* NAND Flash information */
    NAND_FLASH_ID           nandId;         /* NAND flash ID */

    FLASH_BLK_ADDR_T        uBlkCnt;        /* block count */
    FLASH_PAGE_SIZE_T       uBlkShift;      /* block addres shift */
    FLASH_PAGE_ADDR_T       uPagesPerBlk;   /* page count per block */

    FLASH_SIZE_T            uPageCnt;       /* page count */
    FLASH_PAGE_SIZE_T       uPageShift;     /* page addres shift */

    FLASH_OOB_SIZE_T        uOobAvlSize;    /* avaliable OOB size */
    NAND_OOB_LAYOUT_INFO    oobLayout;      /* ECC layout information */

    UINT8 *                 pDataBuf;       /* data buffer */
    UINT8 *                 pOobBuf;        /* OOB buffer */
    UINT8 *                 pEccCalc;       /* ECC calculate buffer */
    UINT8 *                 pEccCode;       /* ECC code buffer */

    NAND_CMD_SEQ            cmdSeq[NAND_CMD_SEQ_MAX];
    SEM_ID                  opSem;          /* operation semaphore */
    void *                  pCmdSetSpec;    /* command set specific */

    /* buffer array */

    NAND_BUF_DESC           pBufDesc[NAND_BUF_MAX_CNT];

    /* roution to read one byte from chip without endianess */

    UINT8                   (*byteRdNoEnd)
        (
        pNAND_FLASH_DESC    pNandDesc
        );

#ifdef _WRS_CONFIG_NAND_INTERNAL_ECC
    /* roution to write one byte to chip without endianess */

    UINT8                   (*byteWrNoEnd)
        (
        pNAND_FLASH_DESC    pNandDesc,
        UINT8               uVal
        );
#endif

    /* statistics counters */

    FLASH_SIZE_T            uEraBlkCnt;
    FLASH_SIZE_T            uWrPageCnt;
    FLASH_SIZE_T            uWrByteCnt;
    FLASH_SIZE_T            uRdPageCnt;
    FLASH_SIZE_T            uRdByteCnt;
    };

/* NAND access functions */

#define NAND_CMD_ISSUE(pNandDesc, uCtrl, uData)     \
    (pNandDesc)->nandInfo.cmdIssue (&(pNandDesc)->nandInfo, (UINT16)(uCtrl), (UINT32)(uData))

#define NAND_BYTE_RD(pNandInfo)         (pNandInfo)->byteRd (pNandInfo)
#define NAND_BYTE_WR(pNandInfo, val)    (pNandInfo)->byteWr (pNandInfo, val)
#define NAND_WORD_RD(pNandInfo)         (pNandInfo)->wordRd (pNandInfo)
#define NAND_WORD_WR(pNandInfo, val)    (pNandInfo)->wordWr (pNandInfo, val)

#define NAND_BUF_RD(pNandDesc, pBufInfo)         \
    (pNandDesc)->nandInfo.bufRd (&(pNandDesc)->nandInfo, pBufInfo)
#define NAND_BUF_WR(pNandDesc, pBufInfo)         \
    (pNandDesc)->nandInfo.bufWr (&(pNandDesc)->nandInfo, pBufInfo)
#define NAND_BUF_VERIFY(pNandDesc, pBufInfo)     \
    (pNandDesc)->nandInfo.bufVerify (&(pNandDesc)->nandInfo, pBufInfo)
#if (_WRS_CONFIG_NAND_FLASH_ECC_FORMAT == 1)
#define NAND_BUF_COPY_FROM_DESC(pNandDesc, pBufDst, colAddr, uLen)    \
    (pNandDesc)->nandInfo.bufCopyFromDesc (&(pNandDesc)->nandInfo, pBufDst, colAddr, uLen)
#define NAND_BUF_COPY_TO_DESC(pNandDesc, pBufSrc, colAddr, uLen)    \
    (pNandDesc)->nandInfo.bufCopyToDesc (&(pNandDesc)->nandInfo, pBufSrc, colAddr, uLen)
#define NAND_BUF_RESET(pNandDesc, colAddrStart, uLen)    \
    (pNandDesc)->nandInfo.bufReset (&(pNandDesc)->nandInfo, colAddrStart, uLen)
#endif

/* debug macros */

#define NAND_FLASH_DBG
#ifdef NAND_FLASH_DBG

IMPORT UINT32 vxbNandDbgLevel;

#define NAND_NONE_DEBUG             0   /* hide messages */
#define NAND_ERR_DEBUG              1   /* show error messages only */
#define NAND_WARN_DEBUG             2   /* show error and warning messages */
#define NAND_NORMAL_DEBUG           3   /* show all messages */

#define NAND_ERR_MSG(fmt, arg1, arg2, arg3, arg4, arg5, arg6)   \
    do                                                          \
        {                                                       \
        if ((vxbNandDbgLevel >= NAND_ERR_DEBUG) &&              \
            (_func_logMsg != NULL))                             \
            _func_logMsg ("NAND Error:"fmt,                           \
                        (_Vx_usr_arg_t) (arg1),                 \
                        (_Vx_usr_arg_t) (arg2),                 \
                        (_Vx_usr_arg_t) (arg3),                 \
                        (_Vx_usr_arg_t) (arg4),                 \
                        (_Vx_usr_arg_t) (arg5),                 \
                        (_Vx_usr_arg_t) (arg6));                \
        } while (0)


#define NAND_WARN_MSG(fmt, arg1, arg2, arg3, arg4, arg5, arg6)  \
     do                                                         \
        {                                                       \
        if ((vxbNandDbgLevel >= NAND_WARN_DEBUG) &&             \
            (_func_logMsg != NULL))                             \
            _func_logMsg ("NAND Warning:"fmt,                   \
                        (_Vx_usr_arg_t) (arg1),                 \
                        (_Vx_usr_arg_t) (arg2),                 \
                        (_Vx_usr_arg_t) (arg3),                 \
                        (_Vx_usr_arg_t) (arg4),                 \
                        (_Vx_usr_arg_t) (arg5),                 \
                        (_Vx_usr_arg_t) (arg6));                \
        } while (0)

#define NAND_DBG_MSG(fmt, arg1, arg2, arg3, arg4, arg5, arg6)   \
    do                                                          \
        {                                                       \
        if ((vxbNandDbgLevel >= NAND_NORMAL_DEBUG) &&           \
            (_func_logMsg != NULL))                             \
            _func_logMsg ("NAND Debug:"fmt,                     \
                        (_Vx_usr_arg_t) (arg1),                 \
                        (_Vx_usr_arg_t) (arg2),                 \
                        (_Vx_usr_arg_t) (arg3),                 \
                        (_Vx_usr_arg_t) (arg4),                 \
                        (_Vx_usr_arg_t) (arg5),                 \
                        (_Vx_usr_arg_t) (arg6));                \
        } while (0)
#else
#define NAND_ERR_MSG(fmt, arg1, arg2, arg3, arg4, arg5, arg6)
#define NAND_WARN_MSG(fmt, arg1, arg2, arg3, arg4, arg5, arg6)
#define NAND_DBG_MSG(fmt, arg1, arg2, arg3, arg4, arg5, arg6)
#endif

/* NAND operation routines */

STATUS vxbNandIdentify (pNAND_FLASH_DESC pNandDesc);
STATUS vxbNandOnfiIdentify (pNAND_FLASH_DESC pNandDesc);
void   vxbNandOnfiShow (pNAND_FLASH_DESC pNandDesc);
STATUS vxbNandCmdIssue
    (
    pNAND_FLASH_DESC    pNandDesc,
    pNAND_CMD_SEQ       pCmdSeq,
    FLASH_ADDR_T        uPageAddr,
    FLASH_COL_ADDR_T    uColAddr,
    UINT8 *             pBuf,
    FLASH_SIZE_T        uLen,
    UINT32              uOp
    );

/* command issue operations */

#define NAND_CMD_ISSUE_OP_ECC       0x01
#define NAND_CMD_ISSUE_OP_WPCHK     0x02
#define NAND_CMD_ISSUE_OP_VERIFY    0x04
#if (_WRS_CONFIG_NAND_FLASH_ECC_FORMAT == 1)
#define NAND_CMD_ISSUE_OP_RDOTHER   0x08
#ifdef _WRS_CONFIG_NAND_INTERNAL_ECC
STATUS vxbNandSetInternalEcc(pNAND_FLASH_DESC pNandDesc, BOOL enableEcc);
#endif
#endif

#ifdef __cplusplus
    }
#endif

#endif /* __INCvxbNandFlashLibh*/

