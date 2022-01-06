/* vxbNandFlash.h - Generic NAND Flash Header */

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
12jul16,ffu  modify NAND_OOB_SIZE to fit ftl(F7019)
01jun16,ffu  add _WRS_CONFIG_NAND_INTERNAL_ECC to support nand auto ECC(F7019)
19may16,ffu  add _WRS_CONFIG_NAND_FLASH_ECC_FORMAT to support more complex ECC(F7019)
11may16,pmr  conditionalize show routine (V7SP-1402)
13may15,txu  fix V7STO-358 : wrong include after extern "C"
21aug14,e_d  add extern flag to nand flash command issue. (US45086)
27may14,ywu  fixed address truncation of nand_flash_info->cmdIssue. (V7STO-173)
30jul13,ywu  add support for single cycle long address type
07dec12,x_z  removde small page size define and chip size defines for
             address cycles.
23nov12,x_z  added buffer descriptor and adjusted NAND library interface;
             added NAND library control flags.
01nov12,x_z  adjusted cache read macro; fixed bufAlloc() parameters.
26oct12,x_z  added bufVerify() hooks for verification operation.
25oct12,x_z  added bufAlloc()/bufFreee() hooks for DMA framework.
04sep12,x_z  moved controller independent code out;
             redesigned command descriptor and NAND flash information;
             code clean.
31may12,m_y  written.
*/

#ifndef __INCvxbNandFlashh
#define __INCvxbNandFlashh

#include <dllLib.h>
#include <semLib.h>
#include <flash.h>
#include <vxbFlashCommon.h>

#ifdef __cplusplus
    extern "C" {
#endif

/* defines */

/* command definations */

#define NAND_MAX_CMD_STEP       8

/* NAND command status */

#define NAND_CMD_STA_FAIL       0x01    /* failed to program/erase */
#define NAND_CMD_STA_FAIL_EXT   0x02    /* failed to program/erase for MLC */
#define NAND_CMD_STA_TRUE_RDY   0x20    /* ready for actual program */
#define NAND_CMD_STA_RDY        0x40    /* ready(followed by R/B# signal) */
#define NAND_CMD_STA_WP         0x80    /* NOT protected for write operation */

/* NAND command control */

#define NAND_CMD_CTRL_CE        0x01    /* chip enable */
#define NAND_CMD_CTRL_CLE       0x02    /* command latch */
#define NAND_CMD_CTRL_ALE       0x04    /* address latch */
#define NAND_CMD_CTRL_CHG       0x08    /* control change */
#define NAND_CMD_CTRL_ALE_PA    0x10    /* address latch for page address */
#define NAND_CMD_CTRL_ALE_CA    0x20    /* address latch for column address */
#define NAND_CMD_CTRL_ISSUE     0x40    /* command issue */
#define NAND_DATA_CTRL_ISSUE    0x80    /* data send flag */

/*
 * NAND command code
 *
 * Note:
 *  1. For NAND chips with small page(page size is equal with 512 bytes), there
 *  is only 1 column address cycle, so one page is divided into 3 areas for X8
 *  devices, and 2 areas for X16 devices, and 3 pointer commands can be used to
 *  set up the start area for all the read/program operation.
 *
 *  For X16 devices, Read 0 command (0x00) sets the pointer to the entire
 *  256-word main area, and Read OOB command (0x50) sets the pointer to 8-word
 *  OOB area;

 *  For X8 devices, Read 0 command (0x00) sets the pointer to the first 256
 *  bytes of the main area, and Read 1 command (0x01) sets the pointer to the
 *  second 256 bytes of the main area, and Read OOB command (0x50) sets the
 *  pointer to 16-byte OOB area.
 *
 *  Note: The pointer only set the start area, and the areas after the start
 *  area can be accessed too.
 *
 *  2. For NAND chips with large page(page size is larger than 512 bytes), the
 *  Read 1 command (0x01) and Read OOB command (0x50) are unsupported, but one
 *  Read Start command (0x30) is is necessary for the read operations.
 */

#define NAND_CMD_CODE_RD0           0x00    /* read 0 */
#define NAND_CMD_CODE_RD1           0x01    /* read 1 */
#define NAND_CMD_CODE_RNDRD         0x05    /* random read */
#define NAND_CMD_CODE_PROG          0x10    /* page program */
#define NAND_CMD_CODE_CPROG         0x15    /* cache page program(large page) */
#define NAND_CMD_CODE_RDSTART       0x30    /* read start(large page) */
#define NAND_CMD_CODE_CRD           0x31    /* cache read */
#define NAND_CMD_CODE_CPRD          0x35    /* copy read(read for copy(move)) */
#define NAND_CMD_CODE_CRD_EXIT      0x3F    /* last cache read */
#define NAND_CMD_CODE_OOBRD         0x50    /* OOB read(small page) */
#define NAND_CMD_CODE_ERA           0x60    /* erase */
#define NAND_CMD_CODE_STARD         0x70    /* status read */
#define NAND_CMD_CODE_SEQIN         0x80    /* sequential input */
#define NAND_CMD_CODE_RNDIN         0x85    /* random/copy input */
#define NAND_CMD_CODE_CPBK          0x8A    /* copy back program(small page) */
#define NAND_CMD_CODE_IDRD          0x90    /* ID read */
#define NAND_CMD_CODE_RNDRD_START   0xE0    /* random read start(large page) */
#define NAND_CMD_CODE_PPRD          0xEC    /* parameter page read(ONFI) */
#define NAND_CMD_CODE_ERA_START     0xD0    /* erase start */
#define NAND_CMD_CODE_RST           0xFF    /* reset */
#ifdef _WRS_CONFIG_NAND_INTERNAL_ECC
#define NAND_CMD_CODE_SETFEATURE    0xEF    /* set feature */
#define NAND_CMD_CODE_GETFEATURE    0xEE    /* get feature */
#endif

/* ECC type defination */

typedef enum nand_ecc_type
    {
    NAND_ECC_HW = 0,
    NAND_ECC_SOFT
    } NAND_ECC_TYPE;

/* OOB layout descriptor */

#define NAND_OOB_LAYOUT_CNT  8
typedef struct nand_oob_layout_desc
    {
    FLASH_PAGE_ADDR_T   uOffset;    /* offset to OOB */
    FLASH_OOB_SIZE_T    uSize;
    } NAND_OOB_LAYOUT_DESC, *pNAND_OOB_LAYOUT_DESC;

/* ECC control code defination */

typedef enum nand_ecc_ctrl_code
    {
    NAND_ECC_RD = 0,    /* switch ECC module to read mode */
    NAND_ECC_WR         /* switch ECC module to write mode */
    } NAND_ECC_CTRL_CODE;

/* page buffer descriptor */

typedef struct nand_buf_desc
    {
    FLASH_PAGE_ADDR_T   uOffset;    /* offset to page data */
    FLASH_PAGE_SIZE_T   uLen;       /* length to be read/written */
    UINT8 *             pBuf;       /* pointer to buffer */
    UINT32              uFlag;      /* flag */
    } NAND_BUF_DESC, *pNAND_BUF_DESC;

#define NAND_BUF_VALID_DATA     0x01    /* valid data for NAND library */

#if (_WRS_CONFIG_NAND_FLASH_ECC_FORMAT == 1)
#define NAND_OOB_SIZE_SMALL        (0x09 + 2)
#define NAND_OOB_SIZE_LARGE        (0x10 + 2)
#endif

/*
 * page buffer information
 *
 * Note:
 *  1. one buffer array CAN ONLY be for one page;
 *  2. all the data blocks to be accessed MUST NOT be overlapped and MUST be
 *  continuous;
 *  3. the start offset to the page MUST be aligend with the chip width;
 *  4. the buffer array CAN ONLY include one data buffer and one OOB buffer if
 *  zero-copy mode is disabled;
 *  5. one OOB buffer CAN ONLY exist in one buffer array.
 */

#define NAND_BUF_MAX_CNT  8   /* maximum buffer descriptor count for one page */
typedef struct nand_buf_info
    {
    pNAND_BUF_DESC      pBufDesc;       /* buffer descriptor array */
    UINT8               uDescCnt;       /* descriptor count */
    UINT8               uStartId;       /* index of start buffer */
    FLASH_PAGE_SIZE_T   uStartOffset;   /* offset to start buffer */
    FLASH_PAGE_SIZE_T   uLen;           /* length to be read/written */
    } NAND_BUF_INFO, *pNAND_BUF_INFO;

/* ECC control information */

struct nand_flash_info;
typedef struct nand_flash_info NAND_FLASH_INFO, *pNAND_FLASH_INFO;
typedef struct nand_ecc_ctrl
    {
    NAND_ECC_TYPE           uType;  /* ECC type */
    FLASH_PAGE_SIZE_T       uSize;  /* bytes that ECC algorithm can calculate */
    FLASH_OOB_SIZE_T        uByte;  /* bytes for ECC result */
    FLASH_PAGE_SIZE_T       uShift; /* shift for ECC size */

    /* used to overwrite automatical ECC layout */

    NAND_OOB_LAYOUT_DESC    eccLayout[NAND_OOB_LAYOUT_CNT];

    /* routine to control ECC module */

    int (*ctrl)
        (
        pNAND_FLASH_INFO    pNandInfo,
        NAND_ECC_CTRL_CODE  ctrlCode,
        void *              pArg
        );

    /* routine to calculate ECC */

    int (*calc)
        (
        pNAND_FLASH_INFO    pNandInfo,
        pNAND_BUF_INFO      pBufInfo,   /* buffer to be calculated */
        UINT8 *             pEccCalc    /* calculated ECC code */
        );

    /* routine to correct data by ECC */

    int (*corr)
        (
        pNAND_FLASH_INFO    pNandInfo,
        pNAND_BUF_INFO      pBufInfo,   /* buffer to be corrected */
        UINT8 *             pEccCode,   /* saved ECC result */
        UINT8 *             pEccCalc    /* calculated ECC result */
        );
    }NAND_ECC_CTRL, *pNAND_ECC_CTRL;

/* NAND flash information structure */

struct nand_flash_info
    {
    DL_NODE                 node;       /* linked to chip list */
    void *                  pCtrl;      /* Flash controller */
    UINT8                   byteReadNum;  
    UINT32                  uCs;        /* NAND chip select */
    UINT32                  uCap;       /* NAND chip capability */
    UINT32                  uChipDelay; /* delay for ready check(us) */
    NAND_ECC_CTRL           eccCtrl;    /* ECC control */
    FLASH_CHIP              flashChip;  /* Flash chip information */

    /* operations */

    /* basic operations */

    int (*cmdIssue)
        (
        pNAND_FLASH_INFO    pNandInfo,
        UINT16              uCtrl,
        UINT32              uData
        );
    UINT8 (*byteRd)
        (
        pNAND_FLASH_INFO    pNandInfo
        );
    int (*byteWr)
        (
        pNAND_FLASH_INFO    pNandInfo,
        UINT8               uVal
        );
    UINT16 (*wordRd)
        (
        pNAND_FLASH_INFO    pNandInfo
        );
    int (*wordWr)
        (
        pNAND_FLASH_INFO    pNandInfo,
        UINT16              uVal
        );

    /* buffer operations (optional) */

    void * (*bufAlloc)
        (
        pNAND_FLASH_INFO    pNandInfo,
        size_t              uLen
        );
    void (*bufFree)
        (
        pNAND_FLASH_INFO    pNandInfo,
        void *              pBuf
        );
    int (*bufRd)
        (
        pNAND_FLASH_INFO    pNandInfo,
        pNAND_BUF_INFO      pBufInfo
        );
    int (*bufWr)
        (
        pNAND_FLASH_INFO    pNandInfo,
        pNAND_BUF_INFO      pBufInfo
        );
    int (*bufVerify)
        (
        pNAND_FLASH_INFO    pNandInfo,
        pNAND_BUF_INFO      pBufInfo
        );
#if (_WRS_CONFIG_NAND_FLASH_ECC_FORMAT == 1)
    int (*bufCopyFromDesc)
        (
        pNAND_FLASH_INFO    pNandInfo,
        void*               pBufDst,
        UINT32              colAddr,
        UINT32              uLen
        );
    int (*bufCopyToDesc)
        (
        pNAND_FLASH_INFO    pNandInfo,
        void*               pBufSrc,
        UINT32              colAddr,
        UINT32              uLen
        );
    int (*bufReset)
        (
        pNAND_FLASH_INFO    pNandInfo,
        UINT32              colAddrStart,
        UINT32              uLen
        );
#endif

    /* check R/B# pin (optional) */

    int (*rdyChk)
        (
        pNAND_FLASH_INFO    pNandInfo
        );
    };

/* NAND chip capability defines */

#define NAND_INFO_CAP_16BIT     0x01    /* 16-bit NAND */
#define NAND_INFO_CAP_CACHEDIS  0x02    /* NAND Cache disabled */
#define NAND_INFO_CAP_ZCOPYDIS  0x04    /* zero-copy disabled */

/* NAND library routines */

pNAND_FLASH_INFO vxbNandInfoCreate (void);
int vxbNandInfoInit (pNAND_FLASH_INFO pNandInfo);
void vxbNandInfoDel (pNAND_FLASH_INFO pNandInfo);
#ifdef _WRS_CONFIG_DEBUG_FLAG
STATUS vxbNandFlashShow (pNAND_FLASH_INFO pNandInfo, int verbose);
#endif /* _WRS_CONFIG_DEBUG_FLAG */

int vxbNandBufRd (pNAND_FLASH_INFO pNandInfo,pNAND_BUF_INFO pBufInfo);
int vxbNandBufRd16 (pNAND_FLASH_INFO pNandInfo,pNAND_BUF_INFO pBufInfo);
int vxbNandBufWr (pNAND_FLASH_INFO pNandInfo,pNAND_BUF_INFO pBufInfo);
int vxbNandBufWr16(pNAND_FLASH_INFO pNandInfo,pNAND_BUF_INFO pBufInfo);
#ifdef __cplusplus
    }
#endif

#endif /* __INCvxbNandFlashh*/

