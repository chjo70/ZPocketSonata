/* vxbSp25SpiFlash.h - Spansion S25XX serials SPI Flash Head File */

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
13may15,txu  fix V7STO-358 : wrong include after extern "C"
10mar15,c_l  support QSPI 32MB flash. (US55072)
10feb14,ywu  fix improper use of _WRS_CONFIG_FDT
16jan14,ywu  adopt to vxBus gen2
14Oct13,d_l  add cfi offset macros and remove structure cfi_ident
             WRS_PACK_ALIGN(1) attribute to eliminate a warning.
03sep13,x_z  fixed hwif header file path.
01feb13,ylu  Change the parameter flash from pointer to
             struct in pDrvCtrl.
24jan13,y_y  Added support for SST chips.
14sep12,y_y  created.
*/

#ifndef __INCvxbSp25SpiFlashh
#define __INCvxbSp25SpiFlashh


#include <vxbFlash.h>
#include <vxbFlashCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */
/* macros for mutex */

#define SPIFLASH_MUTEX_OPT   SEM_Q_PRIORITY |    \
                             SEM_DELETE_SAFE |   \
                             SEM_INVERSION_SAFE

#define SPIFLASH_LOCK(x)     semTake((SEM_ID)(x), WAIT_FOREVER)

#define SPIFLASH_UNLOCK(x)   semGive((SEM_ID)(x))

/* manufacturer ID */

#define SPANSION    (0x01)   /* The manufacturer id for SPANSION */
#define FUJITSU     (0x04)   /* The manufacturer id for FUJITSU  */
#define NEC         (0x10)   /* The manufacturer id for NEC      */
#define EON         (0x1C)   /* The manufacturer id for EON      */
#define ATMEL       (0x1F)   /* The manufacturer id for ATMEL    */
#define MICRO       (0x20)   /* The manufacturer id for MICRO    */
#define AMIC        (0x37)   /* The manufacturer id for AMIC     */
#define ESI         (0x4A)   /* The manufacturer id for ESI      */
#define INTEL       (0x89)   /* The manufacturer id for INTEL    */
#define ESMT        (0x8C)   /* The manufacturer id for ESMT     */
#define TOSHIBA     (0x98)   /* The manufacturer id for TOSHIBA  */
#define PMC         (0x9D)   /* The manufacturer id for PMC      */
#define HYUNDAI     (0xAD)   /* The manufacturer id for HYUNDAI  */
#define SHARP       (0xB0)   /* The manufacturer id for SHARP    */
#define SST         (0xBF)   /* The manufacturer id for SST      */
#define MXIC        (0xC2)   /* The manufacturer id for MXIC     */
#define SAMSUNG     (0xEC)   /* The manufacturer id for SAMSUNG  */
#define WINBOND     (0xEF)   /* The manufacturer id for SAMSUNG  */
#define MISSING     (0xFF)

/* Spansion SPI Flash Commands info */

#define SPI_WRSR_CMD                (0x01)
#define SPI_WRR_CMD                 (0x01)
#define SPI_PP_CMD                  (0x02)
#define SPI_READ_CMD                (0x03)
#define SPI_WRDI_CMD                (0x04)
#define SPI_RDSR_CMD                (0x05)
#define SPI_WREN_CMD                (0x06)
#define SPI_RDSR2_CMD               (0x07)
#define SPI_FAST_READ_CMD           (0x0B)
#define SPI_FAST_READ_4B_CMD        (0x0C)
#define SPI_FAST_READ_DDR_CMD       (0x0D)
#define SPI_FAST_READ_DDR_4B_CMD    (0x0E)
#define SPI_PP_4B_CMD               (0x12)
#define SPI_READ_4B_CMD             (0x13)
#define SPI_RABT_CMD                (0x14)
#define SPI_WABT_CMD                (0x15)
#define SPI_RBNK_CMD                (0x16)
#define SPI_WBNK_CMD                (0x17)
#define SPI_RECC_CMD                (0x18)
#define SPI_P4E_CMD                 (0x20)
#define SPI_P4E_4B_CMD              (0x21)
#define SPI_RASP_CMD                (0x2B)
#define SPI_WASP_CMD                (0x2F)
#define SPI_CLSR_CMD                (0x30)
#define SPI_QPP_CMD                 (0x32)
#define SPI_QPP_4B_CMD              (0x34)
#define SPI_RCR_CMD                 (0x35)
#define SPI_DUALIO_RD_CMD           (0x3B)
#define SPI_DUALIO_RD_4B_CMD        (0x3C)
#define SPI_P8E_CMD                 (0x40)
#define SPI_DLPRD_CMD               (0x41)
#define SPI_OTPP_CMD                (0x42)
#define SPI_PROGRAM_SECURITY_CMD    (0x42)  /* Program Security Register */
#define SPI_PNVDLR_CMD              (0x43)
#define SPI_ERASE_SECURITY_CMD      (0x44)  /* Erase Security Register */
#define SPI_READ_SECURITY_CMD       (0x48)  /* Read Security Register */
#define SPI_WVDLR_CMD               (0x4A)
#define SPI_OTPR_CMD                (0x4B)
#define SPI_READ_UNIQUE_ID_CMD      (0x4B)  /* Read Unique ID Number */
#define SPI_P8E_4B_CMD              (0x4C)
#define SPI_WRITE_VOLATILE_CMD      (0x50)  /* Write Enable for Volatile Status Register */
#define SPI_BE32KB_CMD              (0x52)  /* Block Erase 32KB */
#define SPI_READ_SFDP_CMD           (0x5A)  /* Read Serial Flash Discoverable Parameter Register */
#define SPI_BE1_CMD                 (0x60)
#define SPI_QUADIO_RD_CMD           (0x6B)
#define SPI_QUADIO_RD_4B_CMD        (0x6C)
#define SPI_ERS_SSP_CMD             (0x75)  /* Erase / Program Suspend */
#define SPI_SETBURSTWRAP_CMD        (0x77)  /* Set Burst with Wrap */
#define SPI_ERS_RES_CMD             (0x7A)  /* Erase / Program Resume */
#define SPI_PRG_SSP_CMD             (0x85)
#define SPI_PRG_RES_CMD             (0x8A)
#define SPI_READID_90_CMD           (0x90)
#define SPI_READID_DUAL_CMD         (0x92)
#define SPI_READID_QUAD_CMD         (0x94)
#define SPI_RDID_9F_CMD             (0x9F)
#define SPI_READ_ID_9F_CMD          (0x9F)
#define SPI_MPM_CMD                 (0xA3)
#define SPI_PLBWR_CMD               (0xA6)
#define SPI_PLBRD_CMD               (0xA7)
#define SPI_READ_ID_AB_CMD          (0xAB)
#define SPI_RDID_AB_CMD             (0xAB)
#define SPI_RES_CMD                 (0xAB)
#define SPI_SP_CMD                  (0xB9)
#define SPI_DP_CMD                  (0xB9)
#define SPI_DUALIO_HPRD_CMD         (0xBB)
#define SPI_DUALIO_HPRD_4B_CMD      (0xBC)
#define SPI_DDR_DUALIO_HPRD_CMD     (0xBD)
#define SPI_DDR_DUALIO_HPRD_4B_CMD  (0xBE)
#define SPI_BE_CMD                  (0xC7)
#define SPI_SE_CMD                  (0xD8)
#define SPI_SE_4B_CMD               (0xDC)
#define SPI_DYB_RD_CMD              (0xE0)
#define SPI_DYB_PG_CMD              (0xE1)
#define SPI_PPB_RD_CMD              (0xE2)
#define SPI_PPB_PG_CMD              (0xE3)
#define SPI_OCTALWORDREADQUAD_CMD   (0xE3)  /* Octal Word Read Quad */
#define SPI_PPB_ERS_CMD             (0xE4)
#define SPI_WDBRD_CMD               (0xE5)
#define SPI_WDBP_CMD                (0xE6)
#define SPI_RPWD_CMD                (0xE7)
#define SPI_WORDREADQUAD_CMD        (0xE7)  /* Word Read Quad */
#define SPI_WPWD_CMD                (0xE8)
#define SPI_PWDU_CMD                (0xE9)
#define SPI_QUADIO_HPRD_CMD         (0xEB)
#define SPI_QUADIO_HPRD_4B_CMD      (0xEC)
#define SPI_DDR_QUADIO_HPRD_CMD     (0xED)
#define SPI_DDR_QUADIO_HPRD_4B_CMD  (0xEE)
#define SPI_SOFTWARE_RESET          (0xF0)
#define SPI_RMB_CMD                 (0xFF)
#define SPI_READMODE_RESET_CMD      (0xFF)  /* Continuous Read Mode Reset */

/* SST OPERATION INSTRUCTIONS */

#define SST_AAI_WORD_CMD            (0xAD) /* Auto Address Increment Programming*/

/* Fast read */

#define FAST_READ

#ifdef  FAST_READ
#define SPI_READ_OPCODE             SPI_FAST_READ_CMD
#define READ_CMD_BYTE               5
#else
#define SPI_READ_OPCODE             SPI_READ_CMD
#define READ_CMD_BYTE               4
#endif

/* Generic JEDEC ID get func */

#ifndef JEDEC_ID_GET

#define JEDEC_ID_GET(pDev, jedecId, length)     \
      do                    \
        {                   \
        UINT8 cmd = SPI_READ_ID_9F_CMD;        \
        SPI_TRANSFER transInfo;          \
        memset(&transInfo, 0, sizeof(SPI_TRANSFER)); \
        transInfo.txBuf = &cmd;                \
        transInfo.txLen = 1;                   \
        transInfo.rxBuf = jedecId;             \
        transInfo.rxLen = length;              \
        (void)vxbSpiTransfer (pDev, &transInfo);     \
        }                   \
      while (0)
#endif

/* Spi Flash flags features */

#define NO_JEDEC_ID                 0x0001
#define JEDECID_NO_EXT              0x0002

/* define macros */

#define SR_SRWD                     0x80
#define SR_BP2                      0x10
#define SR_BP1                      0x08
#define SR_BP0                      0x04
#define SR_WEL                      0x02
#define SR_WIP                      0x01
#define MAX_CMD_SIZE                5
#define TIMEOUT                     2000000
#define SPI_3B_MAX                  0x1000000
#define DEFAULT_PP_TIME             500

/*
 * Device Interface Code Assignments from the "Common Flash Memory Interface
 * Publication 100" dated December 1, 2001.
 */

#define CFI_INTERFACE_X8_ASYNC                  0x0000
#define CFI_INTERFACE_X16_ASYNC                 0x0001
#define CFI_INTERFACE_X8_BY_X16_ASYNC           0x0002
#define CFI_INTERFACE_X32_ASYNC                 0x0003
#define CFI_INTERFACE_SINGLE_IO_SPI_ASYNC       0x0004
#define CFI_INTERFACE_MULTI_IO_SPI_ASYNC        0x0005
#define CFI_INTERFACE_NOT_ALLOWED               0xff

/* byte Swap  */

#if (_BYTE_ORDER == _BIG_ENDIAN)

#define CPU_TO_SPI_FLASH_16(bigEndian, x) \
    ((bigEndian != 0) ? (UINT16) (x) : vxbSwap16 (x))
#define CPU_TO_SPI_FLASH_32(bigEndian, x) \
    ((bigEndian != 0) ? (UINT32) (x) : vxbSwap32 (x))

#define SPI_FLASH_LE16_TO_CPU(x)  vxbSwap16 (x)
#define SPI_FLASH_LE32_TO_CPU(x)  vxbSwap32 (x)
#else
#define CPU_TO_SPI_FLASH_16(bigEndian, x) \
    ((bigEndian == 0) ? (UINT16) (x) : vxbSwap16 (x))
#define CPU_TO_SPI_FLASH_32(bigEndian, x) \
    ((bigEndian == 0) ? (UINT32) (x) : vxbSwap32 (x))

#define SPI_FLASH_LE16_TO_CPU(x)  ((UINT16) (x))
#define SPI_FLASH_LE32_TO_CPU(x)  ((UINT32) (x))
#endif /* _BIG_ENDIAN */

#define SPI_FLASH_16_TO_CPU(bigEndian, x) CPU_TO_SPI_FLASH_16 (bigEndian, x)
#define SPI_FLASH_32_TO_CPU(bigEndian, x) CPU_TO_SPI_FLASH_32 (bigEndian, x)

/* Basic Query Structure */

#define SPI_CFI_ERASE_REGIONS       4
#define CFI_MAGIC_STR_LEN           3
#define SPI_CFI_OFFSET              0x10  /* Start of CFI data in RDID result */

/*
 * Erase Block(s) within this Region are (blkSize) times 256 bytes
 * in size. The value blkSize = 0 is used for 128-byte block size.
 */

#define CFI_BLK_SIZE(x) (((x) == 0) ? 0x80 : ((x) << 8))

#define OFF_QS      (0)
#define OFF_PCS     (3)
#define OFF_PETA    (5)
#define OFF_ACS     (7)
#define OFF_AETA    (9)
#define OFF_VCCMIN  (11)
#define OFF_VCCMAX  (12)
#define OFF_VPPMIN  (13)
#define OFF_VPPMAX  (14)
#define OFF_WTO     (15)
#define OFF_WBTO    (16)
#define OFF_BETO    (17)
#define OFF_CETO    (18)
#define OFF_WTOM    (19)
#define OFF_WBTOM   (20)
#define OFF_BETOM   (21)
#define OFF_CETOM   (22)
#define OFF_DS      (23)
#define OFF_ID      (24)
#define OFF_WBL     (26)
#define OFF_RN      (28)
#define OFF_ERI0    (29)
#define OFF_ERI1    (33)
#define OFF_ERI2    (37)
#define OFF_ERI3    (41)

#define SPI_CFI_LEN (45)

struct cfi_ident
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
    UINT32  EraseRegionInfo[SPI_CFI_ERASE_REGIONS];
    };

/* CFI standard query structure region information */

struct cfi_region
    {
    UINT16  blkSize;    /* Erase Block Size devided by 256 */
    UINT16  blkNum;     /* Number of Erase Blocks - 1 */
    };

/* typedef */

typedef struct spiFlash_info
    {
    char   name[MAX_DRV_NAME_LEN];
    UINT16 manuId;
    UINT16 devId;
    UINT16 extId;
    UINT16 pageSize;
    UINT32 sectorSize;
    UINT32 sectorNum;
    UINT32 flags;
    }SPIFLASH_INFO;

/* SPI_NOR_FLASH device struct */

typedef struct spi_norFlash_drv_ctrl
    {
#ifndef _WRS_CONFIG_VXBUS_LEGACY
    VXB_DEV_ID    pDev;
    SPI_HARDWARE  hd;
    UINT32        sizeShift;
    UINT32        addrShift;
    UINT32        readCmd;
    UINT32        readDummy;
#else
    VXB_DEVICE_ID pDev;
#endif
    char          type[MAX_DRV_NAME_LEN];
    int           index;
    UINT32        chipSize;
    UINT32        ppTime;
    UINT8 *       pWrBuf;
    SEM_ID        muteSem;      /* operation semaphore */
    UINT8         addrWidth;    /* 4-byte or 3-byte address */
    BOOL          isProbeOk;    /* whether probe ok */
    FLASH_CHIP    mtd;          /* FileSystem used */
    VXB_SPI_MAST_SPEC * specialInfo;
    SPIFLASH_INFO flash;
    } SPI_FLASH_DEV;

#define PageSize(x)                 ((x)->flash.pageSize)
#define SectorSize(x)               ((x)->flash.sectorSize)
#define SectorNum(x)                ((x)->flash.sectorNum)
#define ChipSize(x)                 ((x)->chipSize)

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbSp25SpiFlashh */

