/* vxbGpmcCore.h -  core code header for GPMC driver */

/*
 * Copyright (c) 2012, 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
13may15,txu  fix V7STO-358 : wrong include after extern "C"
01k,10feb14,ywu  fix improper use of _WRS_CONFIG_FDT
01j,21jan14,ywu  adopt to vxBus gen2
01i,16jan14,ywu  disabled for vxBus gen2 temporarily
01h,26nov12,x_z  added CS count for NAND chips.
01g,23nov12,x_z  added CS type and CS byte access macros;
                 removed DMA control flag and adjusted ready pin connected flag.
01f,07nov12,x_z  added support for Mistral OMAP3530 EVM board;
                 added DMA transfer hook;
                 fixed debug message macro.
01e,01nov12,x_z  fixed compiling warnings.
01d,26oct12,x_z  added FIFO width defines for Prefecth/Postwrite engine;
                 modified NAND CS space access to 32-bit access.
01c,25oct12,x_z  added defines for Prefecth/Postwrite engine and CS config
                 registers;
                 added atmoic flags for ECC engine and
                 Prefecth/Postwrite engine;
                 added support for GPMC CS space access;
                 added DMA tags.
01b,12oct12,x_z  fixed ECC CS config defines and removed unused uCurEccCs from
                 controller information structure.
01a,20aug12,x_z  written based on vxbGpmc.h.
*/

#ifndef __INCvxbGpmcCoreh
#define __INCvxbGpmcCoreh


#include <vxWorks.h>
#include <stdlib.h>
#include <string.h>
#include <logLib.h>
#include <vxAtomicLib.h>

#ifndef _WRS_CONFIG_VXBUS_LEGACY
#include <hwif/vxBus.h>

#else
#include <hwif/vxbus/vxBus.h>
#include <hwif/util/vxbDmaLib.h>
#include <hwif/util/vxbDmaBufLib.h>
#include <hwif/dmaCtlr/vxbTiEdma3.h>
#undef DMA_DRV_NAME
#include <hwif/dmaCtlr/vxbOmap35xxDma.h>
#endif

#include <nand/vxbNandFlash.h>
#include <gpmc/vxbGpmc.h>

#ifdef  __cplusplus
 extern "C" {
#endif

#define GPMC_MAX_CS             8

/* register map */

/* global registers */

#define GPMC_REV                0x00    /* revision */
#define GPMC_SYSCFG             0x10    /* system config */
#define GPMC_SYSSTA             0x14    /* system status */
#define GPMC_IRQSTA             0x18    /* ISR status */
#define GPMC_IRQEN              0x1C    /* IRQ enable */
#define GPMC_TCTRL              0x40    /* timeout control */
#define GPMC_CFG                0x50    /* config */
#define GPMC_STA                0x54    /* status */

/* CS config registers */

#define GPMC_CSn_CFG1(cs)       (0x60 + (0x30 * (cs)))
#define GPMC_CSn_CFG2(cs)       (0x64 + (0x30 * (cs)))
#define GPMC_CSn_CFG3(cs)       (0x68 + (0x30 * (cs)))
#define GPMC_CSn_CFG4(cs)       (0x6C + (0x30 * (cs)))
#define GPMC_CSn_CFG5(cs)       (0x70 + (0x30 * (cs)))
#define GPMC_CSn_CFG6(cs)       (0x74 + (0x30 * (cs)))
#define GPMC_CSn_CFG7(cs)       (0x78 + (0x30 * (cs)))

#define GPMC_CSn_NAND_CMD(cs)   (0x7C + (0x30 * (cs)))
#define GPMC_CSn_NAND_ADDR(cs)  (0x80 + (0x30 * (cs)))
#define GPMC_CSn_NAND_DATA(cs)  (0x84 + (0x30 * (cs)))

/* prefetch registers */

#define GPMC_PREFETCH_CFG1      0x1E0 /* config */
#define GPMC_PREFETCH_CFG2      0x1E4
#define GPMC_PREFETCH_CTRL      0x1EC /* control */
#define GPMC_PREFETCH_STA       0x1F0 /* status */

/* ECC registers */

#define GPMC_ECC_CFG            0x1F4 /* config */
#define GPMC_ECC_CTRL           0x1F8 /* control */
#define GPMC_ECC_SIZE_CFG       0x1FC /* size config */

/* Hamming Code (1-bit) ECC result registers */

#define GPMC_ECC_RESULT_CNT             9
#define GPMC_ECC_RESULTn(n)             (0x200 + (((n) - 1) << 2))

/* BCH Code ECC result registers */

#define GPMC_BCH_RESULT_CNT             5   /* result count */
#define GPMC_BCH_RESULT_LEN             208 /* length for one result */
#define GPMC_BCH_RESULT_BUF_CNT         6   /* buffer count for one result */
#define GPMC_BCH_RESULT_BUF_ID(offset)  ((offset) >> 5)

#define GPMC_BCH_RESULTm_BUFn(m, n)     (0x240 + ((m) << 4) + ((n) << 2))
#define GPMC_BCH_SWDATA                 0x2D0

/* bit defines */

/* revsion register */

#define GPMC_REV_MAJ(x)             (((x) >> 4) & 0xF)  /* major */
#define GPMC_REV_MIN(x)             ((x) & 0xF)         /* minor */

/* system config register */

#define GPMC_SYSCFG_IMODE(mode)     ((mode) << 3)
#define GPMC_SYSCFG_IMODE_FIDLE     0       /* Force-idle */
#define GPMC_SYSCFG_IMODE_NIDLE     1       /* No-idle */
#define GPMC_SYSCFG_IMODE_SIDLE     2       /* Smart-idle */

#define GPMC_SYSCFG_SRST            0x02    /* software reset */

/* system status register */

#define GPMC_SYSSTA_RSTDONE         0x1

/* IRQ status/enable registers */

#define GPMC_IRQ_WAIT1  0x0200  /* wait pin 1 interrupt */
#define GPMC_IRQ_WAIT0  0x0100  /* wait pin 0 interrupt */
#define GPMC_IRQ_FIFO   0x0001  /* FIFO interrupt */

/* config register */

#define GPMC_CFG_WPOFF  0x0010  /* Write-protection disable */
#define GPMC_CFG_LADDR  0x0002  /* limited address device */

/* status register */

#define GPMC_STA_WRBUFEMPTY   0x01    /* write-buffer empty status */

/* CS config register*/

#define GPMC_CSn_CFG1_WAITREADMONITORING    0x00400000
#define GPMC_CSn_CFG1_WAITWRITEMONITORING   0x00200000

#define GPMC_CSn_CFG1_DEVSIZE               0x3000
#define GPMC_CSn_CFG1_DEVSIZE_8BIT          0x0000
#define GPMC_CSn_CFG1_DEVSIZE_16BIT         0x1000

#define GPMC_CSn_CFG1_DEVTYPE               0x0C00  /* device type */
#define GPMC_CSn_CFG1_NAND                  0x0800
#define GPMC_CSn_CFG1_NOR                   0x0000

#define GPMC_CSn_CFG1_LATENCY_X2            0x0010  /* ? latencies */

/* CS# signal timing */

#define GPMC_CSn_CFG2_CSWROFFTIME(n)    (((n) & 0x1F) << 16)
#define GPMC_CSn_CFG2_CSRDOFFTIME(n)    (((n) & 0x1F) << 8)
#define GPMC_CSn_CFG2_CSONTIME(n)       ((n) & 0xF)

/* ADV# signal timing */

#define GPMC_CSn_CFG3_ADVWROFFTIME(n)   (((n) & 0x1F) << 16)
#define GPMC_CSn_CFG3_ADVRDOFFTIME(n)   (((n) & 0x1F) << 8)
#define GPMC_CSn_CFG3_ADVONTIME(n)      ((n) & 0xF)

/* WE#/OE# signal timing */

#define GPMC_CSn_CFG4_WEOFFTIME(n)      (((n) & 0x1F) << 24)
#define GPMC_CSn_CFG4_WEONTIME(n)       (((n) & 0xF) << 16)
#define GPMC_CSn_CFG4_OEOFFTIME(n)      (((n) & 0x1F) << 8)
#define GPMC_CSn_CFG4_OEONTIME(n)       ((n) & 0xF)

/* cycle config */

#define GPMC_CSn_CFG5_RDACCESSTIME(n)       (((n) & 0x1F) << 16)
#define GPMC_CSn_CFG5_WRCYCLETIME(n)        (((n) & 0x1F) << 8)
#define GPMC_CSn_CFG5_RDCYCLETIME(n)        ((n) & 0x1F)

#define GPMC_CSn_CFG6_CYCLE2CYCLESAMECSEN   0x80
#define GPMC_CSn_CFG6_CYCLE2CYCLEDELAY(n)   (((n) & 0xF) << 8)
#define GPMC_CSn_CFG6_WRACCESSTIME(n)       (((n) & 0x1F) << 24)

/* chip select address config */

#define GPMC_CSn_CFG7_CS_SIZE_256MB         0
#define GPMC_CSn_CFG7_CS_SIZE_128MB         0x0800
#define GPMC_CSn_CFG7_CS_SIZE_64MB          0x0C00
#define GPMC_CSn_CFG7_CS_SIZE_32MB          0x0E00
#define GPMC_CSn_CFG7_CS_SIZE_16MB          0x0F00

#define GPMC_CSn_CFG7_CSVALID               0x40
#define GPMC_CSn_CFG7_CSBA(addr)            (((addr) >> 24) & 0x3F)

/* prefetch config 1 register */

#define GPMC_PREFETCH_CFG1_CS(x)                (((x) & 0x7) << 24)

#define GPMC_PREFETCH_CFG1_FIFOTHRESHOLD(x)     (((x) & 0x7F) << 8)
#define GPMC_PFPW_FIFO_LEN                      0x40
#define GPMC_PFPW_FIFO_LEN_SHIFT                6
#define GPMC_PFPW_FIFO_WIDTH                    4
#define GPMC_PFPW_FIFO_WIDTH_SHIFT              2

#define GPMC_PREFETCH_CFG1_EN                   0x80
#define GPMC_PREFETCH_CFG1_DMAMODE              0x04
#define GPMC_PREFETCH_CFG1_WRITEPOST            0x01

/* prefetch config 2 register */

#define GPMC_PREFETCH_CFG2_CNT(x)               ((x) & 0x3FFF)
#define GPMC_PREFETCH_CFG2_CNT_MAX              0x2000

/* prefetch control register */

#define GPMC_PREFETCH_CTRL_START                1

/* prefetch status register */

#define GPMC_PREFETCH_STA_FPTR(x)               (((x) >> 24) & 0x7F)
#define GPMC_PREFETCH_STA_RETCNT(x)             ((x) & 0x3FFF)

/* ECC config register */

#define GPMC_ECC_CFG_16B                    0x80    /* 16 bit or 8 bit width */
#define GPMC_ECC_CFG_TOPSECTOR(n)           (((n-1) << 4) & 0x70)
#define GPMC_ECC_CFG_CS(n)                  (((n) & 0x7) << 1)
#define GPMC_ECC_CFG_EN                     0x01

/* ECC control register */

#define GPMC_ECC_CTRL_CLR                   0x0100
#define GPMC_ECC_CTRL_POINTER(n)            ((n) & 0x0F)

/* ECC size register */

#define GPMC_ECC_SIZE1(n)               ((((n >> 1) - 1) & 0xFF) << 22)
#define GPMC_ECC_SIZE0(n)               ((((n >> 1) - 1) & 0xFF) << 12)
#define GPMC_ECC_RESULTn_SELSIZE1(n)    ((1) << ((n) - 1))

/* ECC result bits */

#define GPMC_ECC_TF(value)              ((value) ? 1 : 0)

#define GPMC_ECC_RESULT_P1E         (1 << 0)
#define GPMC_ECC_RESULT_P2E         (1 << 1)
#define GPMC_ECC_RESULT_P4E         (1 << 2)
#define GPMC_ECC_RESULT_P8E         (1 << 3)
#define GPMC_ECC_RESULT_P16E        (1 << 4)
#define GPMC_ECC_RESULT_P32E        (1 << 5)
#define GPMC_ECC_RESULT_P64E        (1 << 6)
#define GPMC_ECC_RESULT_P128E       (1 << 7)
#define GPMC_ECC_RESULT_P256E       (1 << 8)
#define GPMC_ECC_RESULT_P512E       (1 << 9)
#define GPMC_ECC_RESULT_P1024E      (1 << 10)
#define GPMC_ECC_RESULT_P2048E      (1 << 11)

#define GPMC_ECC_RESULT_P1O         (1 << 16)
#define GPMC_ECC_RESULT_P2O         (1 << 17)
#define GPMC_ECC_RESULT_P4O         (1 << 18)
#define GPMC_ECC_RESULT_P8O         (1 << 19)
#define GPMC_ECC_RESULT_P16O        (1 << 20)
#define GPMC_ECC_RESULT_P32O        (1 << 21)
#define GPMC_ECC_RESULT_P64O        (1 << 22)
#define GPMC_ECC_RESULT_P128O       (1 << 23)
#define GPMC_ECC_RESULT_P256O       (1 << 24)
#define GPMC_ECC_RESULT_P512O       (1 << 25)
#define GPMC_ECC_RESULT_P1024O      (1 << 26)
#define GPMC_ECC_RESULT_P2048O      (1 << 27)

#define GPMC_ECC_P2048e(val)    (GPMC_ECC_TF(val & GPMC_ECC_RESULT_P2048E) << 0)
#define GPMC_ECC_P2048o(val)    (GPMC_ECC_TF(val & GPMC_ECC_RESULT_P2048O) << 1)
#define GPMC_ECC_P1e(val)       (GPMC_ECC_TF(val & GPMC_ECC_RESULT_P1E)    << 2)
#define GPMC_ECC_P1o(val)       (GPMC_ECC_TF(val & GPMC_ECC_RESULT_P1O)    << 3)
#define GPMC_ECC_P2e(val)       (GPMC_ECC_TF(val & GPMC_ECC_RESULT_P2E)    << 4)
#define GPMC_ECC_P2o(val)       (GPMC_ECC_TF(val & GPMC_ECC_RESULT_P2O)    << 5)
#define GPMC_ECC_P4e(val)       (GPMC_ECC_TF(val & GPMC_ECC_RESULT_P4E)    << 6)
#define GPMC_ECC_P4o(val)       (GPMC_ECC_TF(val & GPMC_ECC_RESULT_P4O)    << 7)

#define GPMC_ECC_P8e(val)       (GPMC_ECC_TF(val & GPMC_ECC_RESULT_P8E)    << 0)
#define GPMC_ECC_P8o(val)       (GPMC_ECC_TF(val & GPMC_ECC_RESULT_P8O)    << 1)
#define GPMC_ECC_P16e(val)      (GPMC_ECC_TF(val & GPMC_ECC_RESULT_P16E)   << 2)
#define GPMC_ECC_P16o(val)      (GPMC_ECC_TF(val & GPMC_ECC_RESULT_P16O)   << 3)
#define GPMC_ECC_P32e(val)      (GPMC_ECC_TF(val & GPMC_ECC_RESULT_P32E)   << 4)
#define GPMC_ECC_P32o(val)      (GPMC_ECC_TF(val & GPMC_ECC_RESULT_P32O)   << 5)
#define GPMC_ECC_P64e(val)      (GPMC_ECC_TF(val & GPMC_ECC_RESULT_P64E)   << 6)
#define GPMC_ECC_P64o(val)      (GPMC_ECC_TF(val & GPMC_ECC_RESULT_P64O)   << 7)

#define GPMC_ECC_P128e(val)     (GPMC_ECC_TF(val & GPMC_ECC_RESULT_P128E)  << 0)
#define GPMC_ECC_P128o(val)     (GPMC_ECC_TF(val & GPMC_ECC_RESULT_P128O)  << 1)
#define GPMC_ECC_P256e(val)     (GPMC_ECC_TF(val & GPMC_ECC_RESULT_P256E)  << 2)
#define GPMC_ECC_P256o(val)     (GPMC_ECC_TF(val & GPMC_ECC_RESULT_P256O)  << 3)
#define GPMC_ECC_P512e(val)     (GPMC_ECC_TF(val & GPMC_ECC_RESULT_P512E)  << 4)
#define GPMC_ECC_P512o(val)     (GPMC_ECC_TF(val & GPMC_ECC_RESULT_P512O)  << 5)
#define GPMC_ECC_P1024e(val)    (GPMC_ECC_TF(val & GPMC_ECC_RESULT_P1024E) << 6)
#define GPMC_ECC_P1024o(val)    (GPMC_ECC_TF(val & GPMC_ECC_RESULT_P1024O) << 7)

/* CS type */

typedef enum gpmc_cs_type
   {
   GPMC_CS_TYPE_OTHER = 0,
   GPMC_CS_TYPE_NAND_8BIT,  /* 8-bit NAND Flash */
   GPMC_CS_TYPE_NAND_16BIT  /* 16-bit NAND Flash */
   } GPMC_CS_TYPE;

/* controller information */

typedef struct gpmc
    {
#ifndef _WRS_CONFIG_VXBUS_LEGACY
    VXB_DEV_ID                  pDev;
#else
    VXB_DEVICE_ID               pDev;
#endif
    void *                      pRegHandle;
    void *                      pCsHandle;
    ULONG                       uRegBase;   /* register base */
    ULONG                       uCsBase;    /* CS base */
    UINT32                      uPlatType;  /* platform type */
    UINT32                      uFlag;
    GPMC_CS_TYPE                uCsType[GPMC_MAX_CS];
    UINT8                       uNandCsCnt; /* CS count for NAND */
    DL_LIST                     chipList;
#ifndef _WRS_CONFIG_VXBUS_LEGACY
    VXB_RESOURCE_LIST           pResList;
#endif
    atomic32_t *                pEccUsed;   /* ECC engine used flag */
    atomic32_t *                pPfpwUsed;  /* prefetch/postwrite engine */
                                            /* used flag */
#ifdef _WRS_CONFIG_VXBUS_LEGACY
    /* DMA information */

    VXB_DMA_RESOURCE_ID         dmaCh;     /* DMA channel */
    VXB_DMA_TAG_ID              dmaParentTag;
    STATUS                      (*dmaTransfer)
        (
        pNAND_FLASH_INFO    pNandInfo,
        UINT8 *             pBuf,
        FLASH_PAGE_SIZE_T   uLen,
        BOOL                bIsWr
        );

    /* TI EDMA3 information */

    TI_EDMA3_CHAN_ALLOC_INFO    tiEdma3ChInfo;  /* channel information */
    TI_EDMA3_PARAM              tiEdma3Pram;    /* parameter description */

    /* TI Omap35xx DMA information */

    atomic32_t *                pTiOmap35xxDmaUsed;  /* DMA engine used flag */
    OMAP35XX_DMA_CHAN_PARAM     tiOmap35xxChDmaPram; /* channel parameter */
#endif
    } GPMC, *pGPMC;

#ifdef _WRS_CONFIG_VXBUS_LEGACY
/* buffer information */

typedef struct gpmc_buf_info
    {
    UINT32          uPhyAddr;
    VXB_DMA_TAG_ID  dmaTag;
    VXB_DMA_MAP_ID  dmaMap;
    } GPMC_BUF_INFO, *pGPMC_BUF_INFO;
#endif

/* address space dfines */

#define GPMC_REG_BAR_ID 0
#define GPMC_CS_BAR_ID  1

/* each CS has 16M bytes address space */

#define GPMC_CS_SZIE    0x01000000
#define GPMC_CS_SHIFT   24

/* flag defines */

#define GPMC_FLAG_RDPIN_CONN    0x0100  /* ready/busy pin connected */

/* controller access defines */

#define GPMC_REG_READ(pGpmc, offset)                    \
    vxbRead32 ((pGpmc)->pRegHandle,                     \
        (void *)((pGpmc)->uRegBase + (ULONG) (offset)))

#define GPMC_REG_WRITE(pGpmc, offset, data)             \
    vxbWrite32 ((pGpmc)->pRegHandle,                    \
                (void *)((pGpmc)->uRegBase + (ULONG)(offset)), (data))

#define GPMC_REG_READ_BYTE(pGpmc, offset)               \
    vxbRead8 ((pGpmc)->pRegHandle,                      \
        (void *)((pGpmc)->uRegBase + (ULONG) (offset)))

#define GPMC_REG_WRITE_BYTE(pGpmc, offset, data)        \
    vxbWrite8 ((pGpmc)->pRegHandle,                     \
                (void *)((pGpmc)->uRegBase + (ULONG) (offset)), (data))

#define GPMC_REG_READ_WORD(pGpmc, offset)               \
    vxbRead16 ((pGpmc)->pRegHandle,                     \
        (void *)((pGpmc)->uRegBase + (ULONG) (offset)))

#define GPMC_REG_WRITE_WORD(pGpmc, offset, data)        \
    vxbWrite16 ((pGpmc)->pRegHandle,                    \
                (void *)((pGpmc)->uRegBase + (ULONG) (offset)), (data))

/* CS access defines */

#define GPMC_CS_READ(pGpmc, cs)                         \
    vxbRead32 ((pGpmc)->pCsHandle,                      \
              (void *)((pGpmc)->uCsBase + ((cs) << GPMC_CS_SHIFT)))

#define GPMC_CS_WRITE(pGpmc, cs, data)                  \
    vxbWrite32 ((pGpmc)->pCsHandle,                     \
               (void *)((pGpmc)->uCsBase + ((cs) << GPMC_CS_SHIFT)), (data))

#define GPMC_CS_READ_BYTE(pGpmc, cs)                    \
    vxbRead8 ((pGpmc)->pCsHandle,                      \
              (void *)((pGpmc)->uCsBase + ((cs) << GPMC_CS_SHIFT)))

#define GPMC_CS_WRITE_BYTE(pGpmc, cs, data)             \
    vxbWrite8 ((pGpmc)->pCsHandle,                      \
               (void *)((pGpmc)->uCsBase + ((cs) << GPMC_CS_SHIFT)), (data))

#define GPMC_CS_READ_WORD(pGpmc, cs)                    \
    vxbRead16 ((pGpmc)->pCsHandle,                      \
              (void *)((pGpmc)->uCsBase + ((cs) << GPMC_CS_SHIFT)))

#define GPMC_CS_WRITE_WORD(pGpmc, cs, data)             \
    vxbWrite16 ((pGpmc)->pCsHandle,                     \
               (void *)((pGpmc)->uCsBase + ((cs) << GPMC_CS_SHIFT)), (data))

#define GPMC_DBG
#ifdef GPMC_DBG
#   define GPMC_DBG_MSG(fmt, a, b, c, d, e, f)                      \
    do                                                              \
        {                                                           \
        if (_func_logMsg != NULL)                                   \
            _func_logMsg (GPMC_DRV_NAME": "fmt, a, b, c, d, e, f);  \
        } while (0)
#else /* !GPMC_DBG */
#   define GPMC_DBG_MSG(fmt, ...)
#endif /* GPMC_DBG */

/* Function Declaration */

int vxbGpmcFlashInit (pGPMC pGpmc);
void vxbGpmcFlashClean (pGPMC pGpmc);
void vxbGpmcSoftRst (pGPMC pGpmc);

#ifndef _WRS_CONFIG_VXBUS_LEGACY
     STATUS vxbGpmcShow (VXB_DEV_ID pDev, int verbose);
#endif

#ifdef  __cplusplus
}
#endif

#endif /* __INCvxbGpmcCoreh */

