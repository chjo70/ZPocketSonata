/* vxbSpiFlash.h - SPI Flash Head File */

/*
 * Copyright (c) 2015-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
13jun17,l_z  add rxNbits to SPI_FLASH_DEV (F9216)
12jan17,mw1  update for i.MX6 SoloX QSPI NOR flash support (US89250)
02feb16,wqi  fixed status check issue of SPI flash 'n25q512' (US66526)
13apr15,y_f  created from vxbSp25SpiFlash.h. (V7PRO-1908)
*/

#ifndef __INCvxbSpiFlashh
#define __INCvxbSpiFlashh

#ifdef __cplusplus
extern "C" {
#endif

#include <vxbFlash.h>
#include <vxbFlashCommon.h>

/* defines */

#define SPI_FLASH_NAME                          "spiflash"

/* manufacturer ID */

#define SPANSION                                (0x01)
#define FUJITSU                                 (0x04)
#define NEC                                     (0x10)
#define EON                                     (0x1C)
#define ATMEL                                   (0x1F)
#define MICRO                                   (0x20)
#define AMIC                                    (0x37)
#define ESI                                     (0x4A)
#define INTEL                                   (0x89)
#define ESMT                                    (0x8C)
#define TOSHIBA                                 (0x98)
#define PMC                                     (0x9D)
#define HYUNDAI                                 (0xAD)
#define SHARP                                   (0xB0)
#define SST                                     (0xBF)
#define MXIC                                    (0xC2)
#define SAMSUNG                                 (0xEC)
#define WINBOND                                 (0xEF)
#define MISSING                                 (0xFF)

/* Spansion SPI Flash Commands info */

#define SPI_WRSR_CMD                            (0x01)
#define SPI_WRR_CMD                             (0x01)
#define SPI_PP_CMD                              (0x02)
#define SPI_READ_CMD                            (0x03)
#define SPI_WRDI_CMD                            (0x04)
#define SPI_RDSR_CMD                            (0x05)
#define SPI_WREN_CMD                            (0x06)
#define SPI_RDSR2_CMD                           (0x07)
#define SPI_FAST_READ_CMD                       (0x0B)
#define SPI_FAST_READ_4B_CMD                    (0x0C)
#define SPI_FAST_READ_DDR_CMD                   (0x0D)
#define SPI_FAST_READ_DDR_4B_CMD                (0x0E)
#define SPI_PP_4B_CMD                           (0x12)
#define SPI_READ_4B_CMD                         (0x13)
#define SPI_RABT_CMD                            (0x14)
#define SPI_WABT_CMD                            (0x15)
#define SPI_RBNK_CMD                            (0x16)
#define SPI_WBNK_CMD                            (0x17)
#define SPI_RECC_CMD                            (0x18)
#define SPI_P4E_CMD                             (0x20)
#define SPI_P4E_4B_CMD                          (0x21)
#define SPI_RASP_CMD                            (0x2B)
#define SPI_WASP_CMD                            (0x2F)
#define SPI_CLSR_CMD                            (0x30)
#define SPI_QPP_CMD                             (0x32)
#define SPI_QPP_4B_CMD                          (0x34)
#define SPI_RCR_CMD                             (0x35)
#define SPI_DUALIO_RD_CMD                       (0x3B)
#define SPI_DUALIO_RD_4B_CMD                    (0x3C)
#define SPI_P8E_CMD                             (0x40)
#define SPI_DLPRD_CMD                           (0x41)
#define SPI_OTPP_CMD                            (0x42)
#define SPI_PROGRAM_SECURITY_CMD                (0x42)  /* Program Security Register */
#define SPI_PNVDLR_CMD                          (0x43)
#define SPI_ERASE_SECURITY_CMD                  (0x44)  /* Erase Security Register */
#define SPI_READ_SECURITY_CMD                   (0x48)  /* Read Security Register */
#define SPI_WVDLR_CMD                           (0x4A)
#define SPI_OTPR_CMD                            (0x4B)
#define SPI_READ_UNIQUE_ID_CMD                  (0x4B)  /* Read Unique ID Number */
#define SPI_P8E_4B_CMD                          (0x4C)
#define SPI_CLEAR_FLAG_CMD                      (0x50)  /* Clear flag status register */
#define SPI_BE32KB_CMD                          (0x52)  /* Block Erase 32KB */
#define SPI_READ_SFDP_CMD                       (0x5A)  /* Read Serial Flash Discoverable Parameter Register */
#define SPI_BE1_CMD                             (0x60)
#define SPI_QUADIO_RD_CMD                       (0x6B)
#define SPI_QUADIO_RD_4B_CMD                    (0x6C)
#define SPI_RDFSR_CMD                           (0x70)
#define SPI_ERS_SSP_CMD                         (0x75)  /* Erase / Program Suspend */
#define SPI_SETBURSTWRAP_CMD                    (0x77)  /* Set Burst with Wrap */
#define SPI_ERS_RES_CMD                         (0x7A)  /* Erase / Program Resume */
#define SPI_PRG_SSP_CMD                         (0x85)
#define SPI_PRG_RES_CMD                         (0x8A)
#define SPI_READID_90_CMD                       (0x90)
#define SPI_READID_DUAL_CMD                     (0x92)
#define SPI_READID_QUAD_CMD                     (0x94)
#define SPI_READID_9F_CMD                       (0x9F)
#define SPI_MPM_CMD                             (0xA3)
#define SPI_PLBWR_CMD                           (0xA6)
#define SPI_PLBRD_CMD                           (0xA7)
#define SPI_READ_ID_AB_CMD                      (0xAB)
#define SPI_RDID_AB_CMD                         (0xAB)
#define SPI_RES_CMD                             (0xAB)
#define SPI_SP_CMD                              (0xB9)
#define SPI_DP_CMD                              (0xB9)
#define SPI_DUALIO_HPRD_CMD                     (0xBB)
#define SPI_DUALIO_HPRD_4B_CMD                  (0xBC)
#define SPI_DDR_DUALIO_HPRD_CMD                 (0xBD)
#define SPI_DDR_DUALIO_HPRD_4B_CMD              (0xBE)
#define SPI_W_EAR_CMD                           (0xC5)  /* Write Extended Address Register */
#define SPI_BE_CMD                              (0xC7)
#define SPI_R_EAR_CMD                           (0xC8)  /* Read Extended Address Register */
#define SPI_SE_CMD                              (0xD8)
#define SPI_SE_4B_CMD                           (0xDC)
#define SPI_DYB_RD_CMD                          (0xE0)
#define SPI_DYB_PG_CMD                          (0xE1)
#define SPI_PPB_RD_CMD                          (0xE2)
#define SPI_PPB_PG_CMD                          (0xE3)
#define SPI_OCTALWORDREADQUAD_CMD               (0xE3)  /* Octal Word Read Quad */
#define SPI_PPB_ERS_CMD                         (0xE4)
#define SPI_WDBRD_CMD                           (0xE5)
#define SPI_WDBP_CMD                            (0xE6)
#define SPI_RPWD_CMD                            (0xE7)
#define SPI_WORDREADQUAD_CMD                    (0xE7)  /* Word Read Quad */
#define SPI_WPWD_CMD                            (0xE8)
#define SPI_PWDU_CMD                            (0xE9)
#define SPI_QUADIO_HPRD_CMD                     (0xEB)
#define SPI_QUADIO_HPRD_4B_CMD                  (0xEC)
#define SPI_DDR_QUADIO_HPRD_CMD                 (0xED)
#define SPI_DDR_QUADIO_HPRD_4B_CMD              (0xEE)
#define SPI_SOFTWARE_RESET                      (0xF0)
#define SPI_RMB_CMD                             (0xFF)
#define SPI_READMODE_RESET_CMD                  (0xFF)  /* Continuous Read Mode Reset */

/* SST OPERATION INSTRUCTIONS */

/* Auto Address Increment Programming*/

#define SST_AAI_WORD_CMD                        (0xAD)

/* Enter/Exit 4-byte mode */

#define SPI_EN4B_CMD                            (0xB7) /* Enter 4-byte mode */
#define SPI_EX4B_CMD                            (0xE9) /* Exit 4-byte mode */

#define SR_SRWD                                 0x80
#define SR_BP2                                  0x10
#define SR_BP1                                  0x08
#define SR_BP0                                  0x04
#define SR_WEL                                  0x02
#define SR_WIP                                  0x01

#define FSR_BUSY                                0x80
#define FSR_ERR                                 0x32

#define MAX_CMD_SIZE                            32
#define DEFAULT_WAIT_TIME                       (2 * 1000 * 1000)   /* microsecond */
#define DEFAULT_PP_TIME                         500                 /* microsecond */
#define DEFAULT_CHIP_ERASE_TIME                 300                 /* seconds */
#define SPI_3B_MAX                              0x1000000

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

/* Basic Query Structure */

#define SPI_CFI_ERASE_REGIONS                   4
#define CFI_MAGIC_STR_LEN                       3

/* Start of CFI data in RDID result */

#define SPI_CFI_OFFSET                          0x10

/*
 * Erase Block(s) within this Region are (blkSize) times 256 bytes
 * in size. The value blkSize = 0 is used for 128-byte block size.
 */

#define CFI_BLK_SIZE(x)                         (((x) == 0) ? 0x80 : ((x) << 8))

#define OFF_QS                                  (0)
#define OFF_PCS                                 (3)
#define OFF_PETA                                (5)
#define OFF_ACS                                 (7)
#define OFF_AETA                                (9)
#define OFF_VCCMIN                              (11)
#define OFF_VCCMAX                              (12)
#define OFF_VPPMIN                              (13)
#define OFF_VPPMAX                              (14)
#define OFF_WTO                                 (15)
#define OFF_WBTO                                (16)
#define OFF_BETO                                (17)
#define OFF_CETO                                (18)
#define OFF_WTOM                                (19)
#define OFF_WBTOM                               (20)
#define OFF_BETOM                               (21)
#define OFF_CETOM                               (22)
#define OFF_DS                                  (23)
#define OFF_ID                                  (24)
#define OFF_WBL                                 (26)
#define OFF_RN                                  (28)
#define OFF_ERI0                                (29)
#define OFF_ERI1                                (33)
#define OFF_ERI2                                (37)
#define OFF_ERI3                                (41)

#define SPI_CFI_LEN                             (45)

#define PageSize(x)                             ((x)->flash.pageSize)
#define SectorSize(x)                           ((x)->flash.sectorSize)
#define SectorNum(x)                            ((x)->flash.sectorNum)
#define ChipSize(x)                             ((x)->chipSize)

#define SPI_FLASH_FAST_READ_CLK                 50000000

/* typedef */

typedef struct cfiIdentify
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
    UINT32  eraseRegionInfo[SPI_CFI_ERASE_REGIONS];
    }CFI_IDENTIFY;

/* CFI standard query structure region information */

typedef struct cfiRegion
    {
    UINT16  blkSize;    /* Erase Block Size divided by 256 */
    UINT16  blkNum;     /* Number of Erase Blocks - 1 */
    }CFI_REGION;

typedef struct spiFlashInfo
    {
    char    name[MAX_DRV_NAME_LEN];
    UINT16  manuId;
    UINT16  devId;
    UINT16  extId;
    UINT16  pageSize;
    UINT32  sectorSize;
    UINT32  sectorNum;
    }SPI_FLASH_INFO;

/* SPI_NOR_FLASH device structure */

typedef struct spiFlashDev
    {
    VXB_DEV_ID          pDev;
    SPI_HARDWARE        hd;
    UINT8               readCmd;
    UINT8               readDummy;
    UINT32              readNbits;
    char                chipName[MAX_DRV_NAME_LEN];
    UINT32              chipSize;
    UINT32              chipEraseTime;  /* typical timeout for chip erase */
    UINT32              ppTime;
    UINT8 *             pWrBuf;
    SEM_ID              muteSem;        /* operation semaphore */
    UINT8               addrWidth;      /* 4-byte or 3-byte address */
    UINT8               addrMode;       /* addressing mode */
    FLASH_CHIP          mtd;            /* FileSystem used */
    VXB_SPI_MAST_SPEC * specialInfo;
    SPI_FLASH_INFO      flash;
    UINT32              base;
    } SPI_FLASH_DEV;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCvxbSpiFlashh */
