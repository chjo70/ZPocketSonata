/* vxbNorFlashLib.h - NOR-Flash Driver Library Head File */

/*
 * Copyright (c) 2012, 2014, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
21nov16,ffu  add LP64 support in TFFS layer (F4496)
21nov16,mw1  change parameter of dataForm for UINT8 to UINT32 (V7STO-712)
16jan14,ywu  adopt to vxBus gen2
09mar12,x_z  created.
*/

#ifndef __INCvxbNorFlashLibh
#define __INCvxbNorFlashLibh

#ifdef __cplusplus
extern "C" {
#endif

/* Block status */

#define NOR_FLASH_BLK_LOCKED        0x100
#define NOR_FLASH_BLK_UNLOCKED      0x101

/* data after the block(sector)is erased */

#define NOR_FLASH_DATA_ERASED       0xFFFFFFFF

/* CFI standard query structure */

#define CFI_INFO_BASE               0x10 /* base address for CFI query info */
#define CFI_MAGIC_STR_LEN           3

typedef struct cfi_stand_info
    {

    /* CFI Query Identification String */

    UINT8   qryStr[CFI_MAGIC_STR_LEN]; /* Query-unique ASCII string */
    UINT16  priCmdSet;      /* Primary Vendor Command Set and Control */
                            /* Interface ID code */
    UINT16  priExtTblAdrs;  /* Address for Primary Algorithm extended Query */
                            /* table */
    UINT16  altCmdSet;      /* Alternate Vendor Command Set and Control */
                            /* Interface ID code */
    UINT16  altExtTblAdrs;  /* Address for Alternate Algorithm extended Query */
                            /* table */

    /* CFI Query System Interface Information */

    /* Vcc Logic Supply Minimum/Maximum Write/Erase voltage */

    UINT8   vccMin;
    UINT8   vccMax;

    /* Vpp [Programming] Supply Minimum/Maximum Write/Erase voltage */

    UINT8   vppMin;
    UINT8   vppMax;

    /*
     * Typical timeout per single byte/word write (buffer write count = 1),
     * 2**N microsecond
     */

    UINT8   wrTimeout;

    /*
     * Typical timeout for minimum-size buffer write, 2**N microsecond
     * (if supported; 00h=not supported)
     */

    UINT8   wrBufTimeout;

    /* Typical timeout per individual block erase, 2**N millisecond */

    UINT8   blkEraseTimeout;

    /*
     * Typical timeout for full chip erase, 2**N millisecond
     * (if supported; 00h=not supported)
     */

    UINT8   chipEraseTimeout;

    /* Maximum timeout for byte/word write, 2**N times typical */

    UINT8   wrTimeoutMax;

    /* Maximum timeout for buffer write, 2**N times typical */

    UINT8   wrBufTimeoutMax;

    /* Maximum timeout per individual block erase, 2**N times typical */

    UINT8   blkEraseTimeoutMax;

    /* Maximum timeout per individual block erase, 2**N times typical */

    UINT8   chipEraseTimeoutMax;

    /* Device Geometry Definition */

    UINT8   devSize;    /* Device Size(2**n in number of bytes) */
    UINT16  ifDesc;     /* Flash Device Interface description */
    UINT16  wrBufLen;   /* Maximum number of bytes in multi-byte write = 2**n */
    UINT8   regionNum;  /* Number of Erase Block Regions within device */
    }_WRS_PACK_ALIGN (1) CFI_STAND_INFO;

/* Command Set */

#define NOR_FLASH_CMDSET_NULL               0x0000
#define NOR_FLASH_CMDSET_ITL_EXT            0x0001
#define NOR_FLASH_CMDSET_AMD_STD            0x0002
#define NOR_FLASH_CMDSET_ITL_STD            0x0003
#define NOR_FLASH_CMDSET_AMD_EXT            0x0004
#define NOR_FLASH_CMDSET_WINBOND            0x0006
#define NOR_FLASH_CMDSET_ST_ADV             0x0020
#define NOR_FLASH_CMDSET_MITSUBISHI_STD     0x0100
#define NOR_FLASH_CMDSET_MITSUBISHI_EXT     0x0101
#define NOR_FLASH_CMDSET_SST_PAGE           0x0102
#define NOR_FLASH_CMDSET_SST_OLD            0x0701
#define NOR_FLASH_CMDSET_ITL_PERFORMANCE    0x0200
#define NOR_FLASH_CMDSET_ITL_DATA           0x0210
#define NOR_FLASH_CMDSET_RESERVED           0xFFFF

/*
 * Vcc Logic Supply Minimum/Maximum Write/Erase voltage
 *
 * bits 7 - 4 : BCD value for Vcc or HEX value for Vpp in volts
 * bits 3 - 0 : BCD value in 100 millivolts
 */

#define CFI_INFO_VLOT(x)        (((x) >> 4) & 0xF)
#define CFI_INFO_VLOT_FRAG(x)   ((x) & 0xF)

/* Bit pattern for Flash Device Interface description */

#define CFI_IFDESC_X8           1
#define CFI_IFDESC_X16          2
#define CFI_IFDESC_X32          4

#define CFI_IFDESC_MODE_PRESENT(ifDesc, mode)   ((((ifDesc) + 1) & mode) != 0)
#define CFI_IFDESC(x)                           ((x) - 1)

/* CFI standard query structure region information */

typedef struct cfi_region_info
    {
    UINT16  blkSize;    /* Erase Block Size devided by 256 */
    UINT16  blkNum;     /* Number of Erase Blocks - 1 */
    } CFI_REGION_INFO;

/*
 * Erase Block(s) within this Region are (blkSize) times 256 bytes
 * in size. The value blkSize = 0 is used for 128-byte block size.
 */

#define CFI_BLK_SIZE(x) (((x) == 0) ? 0x80 : ((x) << 8))

/* Primary/Alternate Vendor-Specific Extended Query Table Header */

typedef struct cfi_exttbl_hdr
    {
    UINT8   magic[CFI_MAGIC_STR_LEN]; /* unique ASCII string("PRI" or "ALT") */
    UINT8   major; /* Major version number, ASCII */
    UINT8   minor; /* Minor version number, ASCII */
    } _WRS_PACK_ALIGN (1) CFI_EXTTBL_HDR;

/*
 * JEDEC vendor Id interafce
 *
 * The JEDEC vendor Id is one 8-bit code, which includes 7 data bits and 1 odd
 * parity bit.  So 127 vendors are support at most. To expand the the maximum
 * number of the vendor Id, a continuation scheme has been defined:
 *
 *  1. There can be several banks for vendor Id in one Flash chips;
 *  2. Every bank has 256 words;
 *  3. The vendor Id with the value 0x7F indicates the current bank is one
 *  invalid bank, and the valid bank is one of the following banks.
 */

#define JEDEC_VID_BANK_MAX      8
#define JEDEC_VID_OFFSET(bank)  ((bank) << 8)   /* vendor Id offset */
#define JEDEC_VID_INVALID       0x7F
#define JEDEC_VID_MASK          0xFF
#define JEDEC_VID_FORM(bank, vendorId)  \
    ((bank) << 8 | ((vendorId) & JEDEC_VID_MASK))

/* JEDEC vendor ID defines */

#define JEDEC_VID_AMD   JEDEC_VID_FORM (0, 0x0001)
#define JEDEC_VID_ITL   JEDEC_VID_FORM (0, 0x0089)

/*
 * JEDEC device Id
 *
 * AMD/Spansion chips has 2 additional device IDs
 */

#define JEDEC_FLASH_DID_NUM     3
#define JEDEC_DID_OFFSET        1 /* device Id offset */

#define JEDEC_AMD_DID_OFFSET1   0xE
#define JEDEC_AMD_DID_OFFSET2   0xF
#define JEDEC_AMD_DID_OFFSET(x) (0xE + (x) - 1) /* x must be 1 or 2 */

#define JEDEC_DID_ADJ(mode, devId)  \
    (((mode) == NOR_FLASH_WIDTH_8BIT_CODE) ? ((devId) & 0xFF) : \
    ((devId) & 0xFFFF))

/* JEDEC Flash description */

#define JEDEC_FLASH_NAME_LEN        32

typedef struct jedec_flash_devinfo
    {
    char            name[JEDEC_FLASH_NAME_LEN];
    UINT16          vendorId;
    UINT16          devId[JEDEC_FLASH_DID_NUM]; /* must be set to 0 for */
                                                /* unused elements */
    UINT32          features;   /* supported features*/

    /* Faked CFI query data, see structure CFI_STAND_INFO */

    UINT16          cmdSet;
    UINT8           wrTimeout;
    UINT8           wrBufTimeout;
    UINT8           blkEraseTimeout;
    UINT8           wrTimeoutMax;
    UINT8           wrBufTimeoutMax;
    UINT8           blkEraseTimeoutMax;
    UINT32          devSize;
    UINT16          resv;
    UINT16          ifDesc;
    UINT16          wrBufLen;
    UINT16          numRegion;
    CFI_REGION_INFO region[NOR_FLASH_REGION_NUM_MAX];
    } JEDEC_FLASH_DEVINFO;

/* command description */

typedef struct nor_flash_cmd_desc
    {
    ULONG   adrs;
    UINT32  cmd;
    UINT16  adrsType;
    UINT16  cmdType;
    } NOR_FLASH_CMD_DESC;

/* adrsType filed defines */

#define NOR_FLASH_CMD_TYPE_CA       0x0001 /* command address */
#define NOR_FLASH_CMD_TYPE_DELAY    0x0002 /* delay (<adrs> field will be */
                                           /* ignored for this type) */
#define NOR_FLASH_CMD_TYPE_ULKA1    0x0003 /* unlock address 1 */
#define NOR_FLASH_CMD_TYPE_ULKA2    0x0004 /* unlock address 2 */
/*
 * For the following address type,
 *
 * 1. <adrs> filed will be ignored, and the real address must be saved in the
 * address buffer and send to command issue routine;
 *
 * 2. The index to the address buffer will be transfered from <adrsType> by
 * the following macro;
 *
 * 3. The lenght and macro for the index to the address buffer must be fixed if
 * the defines for <adrsType> are modified;
 */

#define NOR_FLASH_CMD_TYPE_PA       0x0005 /* program address */
#define NOR_FLASH_CMD_TYPE_BA       0x0006 /* block(sector) address */
#define NOR_FLASH_CMD_TYPE_WBL      0x0007 /* byte/word location for */
                                           /* write-to-buffer */

/* address buffer defines */

#define NOR_FLASH_CMD_ADRS_ID(type) ((type) - 5) /* index to address buffer */
#define NOR_FLASH_CMD_ADRS_BUF_LEN  3            /* buf length */

/* some address must be fixed for non-max-buswidth mode */

#define NOR_FLASH_ADRS_FIX_NEEDED(offset)     (((offset) & 0xFF) == 0xAA)

/* cmdType filed defines */

#define NOR_FLASH_CMD_TYPE_CMD      0x0001 /* command */

/*
 * For the following command type,
 *
 * 1. <cmd> filed will be ignored, and the real address must be saved in the
 * address buffer and send to command issue routine;
 *
 * 2. The index to the address buffer will be transfered from <adrsType> by
 * the following macro;
 *
 * 3. The lenght and macro for the index to the address buffer must be fixed if
 * the defines for <adrsType> are modified.
 */

#define NOR_FLASH_CMD_TYPE_PD       0x0002 /* program data */
#define NOR_FLASH_CMD_TYPE_WC       0x0003 /* byte/word count for */
                                           /* write-to-buffer */
#define NOR_FLASH_CMD_TYPE_PTR      0x0004 /* pointer to buffer to be loaded */
                                           /* into write buffer */
#define NOR_FLASH_CMD_TYPE_US       0x0005 /* delay count in us */
#define NOR_FLASH_CMD_TYPE_MS       0x0006 /* delay count in ms */

/* command buffer defines */

#define NOR_FLASH_CMD_ID(type)      ((type) - 2) /* index to command buffer */
#define NOR_FLASH_CMD_BUF_LEN       5            /* buf length */

/* command sequence structure */

#define NOR_FLASH_CMDSEQ_STEPS   8

typedef struct nor_flash_cmdseq
    {
    UINT16              steps;
    UINT16              type;
    NOR_FLASH_CMD_DESC  cmd[NOR_FLASH_CMDSEQ_STEPS];
    } NOR_FLASH_CMDSEQ;

#define NOR_FLASH_CMDSEQ_TYPE_CFI_QRY       0x01 /* CFI Query */
#define NOR_FLASH_CMDSEQ_TYPE_ID_RD         0x02 /* Vendor/Device ID Read */
#define NOR_FLASH_CMDSEQ_TYPE_RST           0x03 /* Reset to read mode */
#define NOR_FLASH_CMDSEQ_TYPE_PG            0x04 /* Program */
#define NOR_FLASH_CMDSEQ_TYPE_WR_BUFF       0x05 /* Write to buffer */
#define NOR_FLASH_CMDSEQ_TYPE_BLK_ERA       0x06 /* Block erase */
#define NOR_FLASH_CMDSEQ_TYPE_CHIP_ERA      0x07 /* Chip erase */
#define NOR_FLASH_CMDSEQ_TYPE_BLK_LOCK      0x08 /* Block lock */
#define NOR_FLASH_CMDSEQ_TYPE_BLK_UNLOCK    0x09 /* Block unlock */
#define NOR_FLASH_CMDSEQ_TYPE_BLK_LOCK_QRY  0x0A /* Block lock status query */
#define NOR_FLASH_CMDSEQ_TYPE_STA_RD        0x0A /* Status read */

/* Flash Device operation timing(microsecond) information */

typedef struct nor_flash_optime_info
    {

    /* timeout per single byte/word write */

    UINT32          wrTimeout;
    UINT32          wrTimeoutMax;

    /* timeout for minimum-size buffer write */

    UINT32          wrBufTimeout;
    UINT32          wrBufTimeoutMax;

    /* timeout per individual block erase */

    UINT32          blkEraseTimeout;
    UINT32          blkEraseTimeoutMax;
    } NOR_FLASH_OPTIME_INFO;

/* Flash command set information */

#define NOR_FLASH_CMDSET_NAME_LEN   32
typedef struct nor_flash_cmdset_info
    {

    /* common */

    void *                  pFlashInfo;
    void *                  pInfo; /* commmand set library private */
                                   /* information */
    BOOL                    cfiCompat;  /* compatible with CFI standard */
    char                    name[NOR_FLASH_CMDSET_NAME_LEN];
    UINT16                  vendorId;   /* chip vendor ID */
    UINT16                  devId[JEDEC_FLASH_DID_NUM]; /* chip device ID */
    UINT32                  features;
    UINT32                  wordLength; /* length for one word */
    NOR_FLASH_OPTIME_INFO   opTimeInfo; /* operation timing */

    /*
     * CFI query output information
     *
     * JEDEC/legacy probe routines should fill these information with fake data.
     */

    CFI_STAND_INFO          cfiStandInfo;
    CFI_REGION_INFO         cfiRegInfo[NOR_FLASH_REGION_NUM_MAX];
    CFI_EXTTBL_HDR          cfiPriExtHdr;
    CFI_EXTTBL_HDR          cfiAltExtHdr;

    /* saved copy for JEDEC Flash */

    JEDEC_FLASH_DEVINFO *   pJedecInfo;

    /* command sequences */

    NOR_FLASH_CMDSEQ *      pQueryCmdSeq;
    NOR_FLASH_CMDSEQ *      pIdRdCmdSeq;
    NOR_FLASH_CMDSEQ *      pRstCmdSeq;
    NOR_FLASH_CMDSEQ *      pPgCmdSeq;
    NOR_FLASH_CMDSEQ *      pWrBufCmdSeq;
    NOR_FLASH_CMDSEQ *      pBlkEraCmdSeq;
    NOR_FLASH_CMDSEQ *      pLockCmdSeq;
    NOR_FLASH_CMDSEQ *      pUnLockCmdSeq;
    NOR_FLASH_CMDSEQ *      pLockQryCmdSeq;

    /* routines  for command set libraries */

    void    (*dataWr)
        (
        struct nor_flash_cmdset_info *  pCmdSetInfo,
        ULONG                           adrs,   /* actual address */
        UINT32                          data    /* actual data */
        );

    UINT32  (*dataRd)
        (
        struct nor_flash_cmdset_info *  pCmdSetInfo,
        ULONG                           adrs,   /* actual address */
        UINT32                          flag    /* access type */
        );

    STATUS (*dataComp)
        (
        struct nor_flash_cmdset_info *  pCmdSetInfo,
        ULONG                           adrs,
        UINT32                          cnt,    /* word count */
        char *                          pBuf,   /* buffer to be written */
        UINT32                          flag    /* access type */
        );

    UINT32  (*dataForm)
        (
        struct nor_flash_cmdset_info *  pCmdSetInfo,
        UINT32                          data    /* original data */
        );

    ULONG   (*adrsMap)
        (
        struct nor_flash_cmdset_info *  pCmdSetInfo,
        ULONG                           offset, /* original offset */
        UINT32                          flag    /* offset type defined later */
        );

    STATUS (*cmdIssue)
        (
        struct nor_flash_cmdset_info *  pCmdSetInfo,
        NOR_FLASH_CMDSEQ *              cmdSeq,
        ULONG *                         pAdrsBuf,   /* address buffer */
        ULONG *                         pCmdBuf     /* cmd buffer */
        );

    STATUS (*idRd)
        (
        struct nor_flash_cmdset_info *  pCmdSetInfo,
        NOR_FLASH_CMDSEQ *              pCmdSeq
        );

    STATUS (*devMatch)
        (
        struct nor_flash_cmdset_info *  pCmdSetInfo,
        UINT16                          vendorId,   /* vendor Id */
        UINT16 *                        pDeviceId   /* buffer for device Id */
        );

    /* routines hooked by commmand set libraries */

    void (*rst)
        (
        struct nor_flash_cmdset_info *  pCmdSetInfo
        );

    STATUS (*pg)
        (
        struct nor_flash_cmdset_info *  pCmdSetInfo,
        ULONG                           adrs,   /* offset to Flash */
        UINT32                          data    /* data to be written */
        );

    STATUS (*bufWr)
        (
        struct nor_flash_cmdset_info *  pCmdSetInfo,
        ULONG                           blkAdrs,    /* block address to Flash */
        ULONG                           adrs,       /* start address to Flash */
        UINT32                          cnt,        /* word count */
        char *                          pBuf        /* buffer to be written */
        );

    STATUS (*blkEra)
        (
        struct nor_flash_cmdset_info *  pCmdSetInfo,
        ULONG                           blkAdrs /* block address to Flash */
        );

    STATUS (*blkLock)
        (
        struct nor_flash_cmdset_info *  pCmdSetInfo,
        ULONG                           blkAdrs, /* block address to Flash */
        BOOL                            lock     /* TRUE- lock FALSE - unlock */
        );

    STATUS (*blkLockQry)
        (
        struct nor_flash_cmdset_info *  pCmdSetInfo,
        ULONG                           blkAdrs, /* block address to Flash */
        BOOL *                          pLock    /* TRUE- lock FALSE - unlock */
        );

    STATUS (*poll)
        (
        struct nor_flash_cmdset_info *  pCmdSetInfo,
        ULONG                           pollAdrs,   /* polling address */
        UINT32                          cmdSeqType  /* command sequence type */
        );
    } NOR_FLASH_CMDSET_INFO;

/* features(operations) defines */

#define NOR_FLASH_CMDSET_FEATURE_WR_BUFF        0x0002 /* Write to buffer */
#define NOR_FLASH_CMDSET_FEATURE_BLK_LOCK       0x0004 /* Block lock */
#define NOR_FLASH_CMDSET_FEATURE_BLK_LOCK_QRY   0x0008 /* Block lock query */

/* offset type for adrsMap () */

#define NOR_FLASH_ADRSMAP_TYPE_QRY  0   /* query, vendor/device ID, */
                                        /* or other Flash registers */
#define NOR_FLASH_ADRSMAP_TYPE_CMD  1   /* command */
#define NOR_FLASH_ADRSMAP_TYPE_DA   2   /* data */

/* Command set register routine */

typedef  STATUS (*NOR_FLASH_CMDSET_INIT_RTN) (NOR_FLASH_CMDSET_INFO * pCmdSetInfo);
typedef  void   (*NOR_FLASH_CMDSET_CLEAN_RTN) (NOR_FLASH_CMDSET_INFO * pCmdSetInfo);
void vxbNorFlashCmdSetReg
    (
    UINT32                      cmdSet,
    NOR_FLASH_CMDSET_INIT_RTN   initRtn,
    NOR_FLASH_CMDSET_CLEAN_RTN  cleanRtn
    );

/* NOR Flash library initialization/clean/show routines */

STATUS vxbNorFlashLibInit
    (
    NOR_FLASH_INFO *   pFlashInfo
    );
void vxbNorFlashLibClean
    (
    NOR_FLASH_INFO *   pFlashInfo
    );
STATUS vxbNorFlashShow
    (
    NOR_FLASH_INFO *    pFlashInfo,
    int                 verbose
    );

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbNorFlashLibh */

