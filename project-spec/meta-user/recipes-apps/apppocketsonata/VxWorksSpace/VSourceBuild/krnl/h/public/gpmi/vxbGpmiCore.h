/* vxbGpmiCore.h -  core code header for vxbGpmi driver */

/*
 * Copyright (c) 2014-2016 Wind River Systems, Inc.
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
05may14,ywu  add NAND flash support for imx6 AI. (US34699)
*/

#ifndef __INCvxbGpmiCoreh
#define __INCvxbGpmiCoreh


#include <vxWorks.h>
#include <stdlib.h>
#include <string.h>
#include <logLib.h>
#ifndef _WRS_CONFIG_VXBUS_LEGACY
#include <hwif/vxBus.h>
#include <nand/vxbNandFlash.h>
#include <nand/vxbNandFlashLib.h>
#include <gpmi/vxbGpmi.h>
#else
#include <hwif/vxbus/vxBus.h>
#include <flash/vxbNandFlash.h>
#include <flash/vxbNandFlashLib.h>
#include <flash/vxbGpmi.h>
#endif
#include <hwif/util/vxbDmaBufLib.h>
#include <logLib.h>		 /* _func_logMsg */

#ifdef  __cplusplus
 extern "C" {
#endif

#define GPMI_MAX_CS                 16         /* max chip select / channel */
#define GPMI_IMX6AI_MAX_CS          16
#define GPMI_IMX6AI_CS              0

#define GPMI_MAX_TIMEOUT            10000000
#define GPMI_MAX_CMDS               2
#define GPMI_CMD_BUF_SIZE           64
#define GPMI_MAX_XFER_COUNT         0xffff

typedef struct imx_ctrl_regs
    {
    UINT32 reg;                    /* 0x0 */
    UINT32 set;                    /* 0x4 */
    UINT32 clr;                    /* 0x8 */
    UINT32 tog;                    /* 0xc */
    } IMX_CTRL_REGS;

/* GPMI Base Register Macros */

#define GPMI_CTRL0_XFERCNT_MASK     0xffff      /* xfer count */
#define GPMI_CTRL0_ADDRINC_EN       (1 << 16)   /* address increment */
#define GPMI_CTRL0_ADDR_DATA        (0 << 17)   /* address */
#define GPMI_CTRL0_ADDR_CLE         (1 << 17)   /* address */
#define GPMI_CTRL0_ADDR_ALE         (2 << 17)   /* address */
#define GPMI_CTRL0_CS_OFF           20          /* chip select */
#define GPMI_CTRL0_WORDLEN_8BIT     (1 << 23)   /* word length */
#define GPMI_CTRL0_CMDMODE_WRITE    (0 << 24)   /* command mode */
#define GPMI_CTRL0_CMDMODE_READ     (1 << 24)   /* command mode */
#define GPMI_CTRL0_CMDMODE_RDCMP    (2 << 24)   /* command mode */
#define GPMI_CTRL0_CMDMODE_WTRDY    (3 << 24)   /* command mode */
#define GPMI_CTRL0_UDMA_EN          (1 << 26)   /* UDMA */
#define GPMI_CTRL0_LOCKCS_EN        (1 << 27)   /* lock chip select */
#define GPMI_CTRL0_DEVIRQ_EN        (1 << 28)   /* GPMI_IRQ asserted */
#define GPMI_CTRL0_RUN_BUSY         (1 << 29)   /* busy on runing / idle */
#define GPMI_CTRL0_CLKGATE_NO       (1 << 30)   /* clock gate */
#define GPMI_CTRL0_SFTRST_RST       (1 << 31)   /* block hold for reset state */

#define GPMI_ECCCTRL_ENCODE         (1 << 13)   /* Encode or decode */
#define GPMI_ECCCTRL_ENABLE         (1 << 12)   /* enable or disable bch ecc */
#define GPMI_ECCCTRL_BCH_AUXONLY    (0x100)
#define GPMI_ECCCTRL_BCH_PAGE       (0x1ff)

#define GPMI_ECCCOUNT_MASK          (0xffff)    /* Number of bytes to pass through ECC. */

#define GPMI_CTRL1_GPMIMODE_ATA     (1 << 0)    /* gpmi mode */
#define GPMI_CTRL1_CAM_MODE         (1 << 1)    /* camera mode */
#define GPMI_CTRL1_ATAIRQRP_HI      (1 << 2)    /* ATA IRQRDY polarity */
#define GPMI_CTRL1_DEVRESET_DIS     (1 << 3)    /* dev reset */
#define GPMI_CTRL1_ABORTWFD         4           /* abort wait for ready */
#define GPMI_CTRL1_ABORTWAIT        7           /* abort wait request */
#define GPMI_CTRL1_BURST_EN         (1 << 8)    /* burst enable */
#define GPMI_CTRL1_TIMEOUT_IRQ      (1 << 9)    /* device busy timeout */
#define GPMI_CTRL1_DEV_IRQ          (1 << 10)   /* ATA intr received */
#define GPMI_CTRL1_DMA2ECC_MODE     (1 << 11)   /* HWECC mode */
#define GPMI_CTRL1_RDNDELAY         12          /* read strobe delay */
#define GPMI_CTRL1_HALF_PERIOD      (1 << 16)   /* clock perriod > 16ns */
#define GPMI_CTRL1_DLL_ENABLE       (1 << 17)   /* DLL enable */
#define GPMI_CTRL1_BCHMODE_EN       (1 << 18)   /* BCH mode */
#define GPMI_CTRL1_GANG_RDYBSY      (1 << 19)   /* force r/b from RDY_BUSY0 */
#define GPMI_CTRL1_TOIRQ_EN         (1 << 20)   /* timeout irq enable */
#define GPMI_CTRL1_RSVD1            21          /* reserved */
#define GPMI_CTRL1_WRNDLYSEL        22          /* write strobe delay select */
#define GPMI_CTRL1_DECOULPE_CS      (1 << 24)   /* decouple chip select */
#define GPMI_CTRL1_SSYNC_MODE       (1 << 25)   /* sourcen sync mode */
#define GPMI_CTRL1_UPDATE_CS        (1 << 26)   /* force CS updated */
#define GPMI_CTRL1_CLKDEV2_EN       (1 << 27)   /* gpmi clock div2 enable */
#define GPMI_CTRL1_TOGGLE_MODE      (1 << 28)   /* enable samsung toggle mode */
#define GPMI_CTRL1_WRITECLK_STOP    (1 << 29)   /* write clock stop */
#define GPMI_CTRL1_SSYNCCLK_STOP    (1 << 30)   /* source sync stop */
#define GPMI_CTRL1_DEVCLK_STOP      (1 << 31)   /* dev clock stop */

#define GPMI_TIME0_DATA_HOLD_MASK   (0x0000ff00) /* time data-hold mask */
#define GPMI_TIME0_DATA_HOLD_SHIFT  (8)          /* time data-hold shift */
#define GPMI_TIME0_DATA_SETUP_MASK  (0x000000ff) /* time data-setup mask */
#define GPMI_TIME0_DATA_SETUP_SHIFT (0)          /* time data-setup shift */

#define GPMI_STAT_RBPIN_OFF         24          /* ready / busy pin offset */

/* register map */

typedef struct gpmi_regs
    {
    IMX_CTRL_REGS  gpmi_ctrl0;      /* 0x000 */

    UINT32  gpmi_ctrl0_compare;     /* 0x010 */
    UINT8   pad1 [0xc];             /* 0x014 - reserved */

    IMX_CTRL_REGS  gpmi_eccctrl;    /* 0x020 */

    UINT32  gpmi_ecccount;          /* 0x030 */
    UINT8   pad2 [0xc];             /* 0x034 - reserved */

    UINT32  gpmi_payload;           /* 0x040 */
    UINT8   pad3 [0xc];             /* 0x044 - reserved */

    UINT32  gpmi_auxiliary;         /* 0x050 */
    UINT8   pad4 [0xc];             /* 0x054 - reserved */

    IMX_CTRL_REGS  gpmi_ctrl1;      /* 0x060 */

    UINT32  gpmi_timing0;           /* 0x070 */
    UINT8   pad5 [0xc];             /* 0x074 - reserved */

    UINT32  gpmi_timing1;           /* 0x080 */
    UINT8   pad6 [0xc];             /* 0x084 - reserved */

    UINT32  gpmi_timing2;           /* 0x090 */
    UINT8   pad7 [0xc];             /* 0x094 - reserved */

    UINT32  gpmi_data;              /* 0x0a0 */
    UINT8   pad8 [0xc];             /* 0x0a4 - reserved */

    UINT32  gpmi_stat;              /* 0x0b0 */
    UINT8   pad9 [0xc];             /* 0x0b4 - reserved */

    UINT32  gpmi_debug;             /* 0x0c0 */
    UINT8   pad10 [0xc];            /* 0x0c4 - reserved */

    UINT32  gpmi_version;           /* 0x0d0 */
    UINT8   pad11 [0xc];            /* 0x0d4 - reserved */

    UINT32  gpmi_debug1;            /* 0x0e0 */
    UINT8   pad12 [0xc];            /* 0x0e4 - reserved */

    UINT32  gpmi_debug2;            /* 0x0f0 */
    UINT8   pad13 [0xc];            /* 0x0f4 - reserved */

    UINT32  gpmi_read_ctrl;         /* 0x100 */
    UINT8   pad14 [0xc];            /* 0x104 - reserved */

    UINT32  gpmi_write_ctrl;        /* 0x110 */
    UINT8   pad15 [0xc];            /* 0x114 - reserved */

    UINT32  gpmi_read_sts;          /* 0x120 */
    UINT8   pad16 [0xc];            /* 0x124 - reserved */

    UINT32  gpmi_write_sts;         /* 0x130 */
    UINT8   pad17 [0xc];            /* 0x134 - reserved */
    } GPMI_REGS;

/* APBH Base Register Macros */

#define GPMI_APBHDMA_MAX_PIO        16          /* APBHDMA max PIO number */

#define APBH_CTRL0_BURST_EN         (1 << 28)   /* burst8 enable */
#define APBH_CTRL0_BURST8_EN        (1 << 29)   /* burst enable */
#define APBH_CTRL0_CLKGATE_NO       (1 << 30)   /* clock gate */
#define APBH_CTRL0_SFTRST_RST       (1 << 31)   /* block hold for reset state */

#define APBH_CTRL1_IRQSTATUS_OFF    0           /* irq status offset */
#define APBH_CTRL1_IRQENABLE_OFF    16          /* irq enable offset */


#define APBH_CTRL2_ERRORIRQ_OFF     0           /* error irq offset */
#define APBH_CTRL2_ERRORSTATUS_OFF  16          /* error status offset */

#define APBH_CHANCTRL_FREEZE_OFF    0           /* chip select */
#define APBH_CHANCTRL_RESET_OFF     16          /* chip select */

#define APBH_CHANCMD_COMMAND_NX     0           /* no transfer */
#define APBH_CHANCMD_COMMAND_WR     1           /* DMA write from dev to mem */
#define APBH_CHANCMD_COMMAND_RD     2           /* DMA read from mem to dev */
#define APBH_CHANCMD_COMMAND_SE     3           /* DMA sense */
#define APBH_CHANCMD_CHAIN_EN       (1 << 2)    /* command chain enabled */
#define APBH_CHANCMD_IRQCOMP_EN     (1 << 3)    /* IRQ completion enable */
#define APBH_CHANCMD_NAND_LOCK      (1 << 4)    /* NAND lock */
#define APBH_CHANCMD_WAIT4_RDY      (1 << 5)    /* wait for ready */
#define APBH_CHANCMD_SEMDECR_EN     (1 << 6)    /* semaphore decrease enable */
#define APBH_CHANCMD_WAIT4_END      (1 << 7)    /* wait for cmd end */
#define APBH_CHANCMD_HALTON_TERM    (1 << 8)    /* halt on terminate */
#define APBH_CHANCMD_CMDWORD_OFF    12          /* cmd words offset */
#define APBH_CHANCMD_XFERCNT_OFF    16          /* transfer count offset */

#define APBH_CHANSEM_INCRSEM_OFF    0           /* semaphore increase enable */
#define APBH_CHANSEM_PHORE_OFF      16          /* current sema counter offset*/
#define APBH_CHANSEM_PHORE_MASK     0xff        /* current sema counter mask*/



typedef struct apbh_chan_regs
    {
    UINT32  apbh_chan_curcmdar;     /* 0x000 */
    UINT8   pad1 [0xc];             /* 0x004 - reserved */

    UINT32  apbh_chan_nxtcmdar;     /* 0x010 */
    UINT8   pad2 [0xc];             /* 0x014 - reserved */

    UINT32  apbh_chan_cmd;          /* 0x020 */
    UINT8   pad3 [0xc];             /* 0x024 - reserved */

    UINT32  apbh_chan_bar;          /* 0x030 */
    UINT8   pad4 [0xc];             /* 0x034 - reserved */

    UINT32  apbh_chan_sema;         /* 0x040 */
    UINT8   pad5 [0xc];             /* 0x044 - reserved */

    UINT32  apbh_chan_debug1;       /* 0x050 */
    UINT8   pad6 [0xc];             /* 0x054 - reserved */

    UINT32  apbh_chan_debug2;       /* 0x060 */
    UINT8   pad7 [0xc];             /* 0x064 - reserved */
    } APBH_CHAN_REGS;

typedef struct apbh_regs
    {
    IMX_CTRL_REGS   apbh_ctrl0;     /* 0x000 */

    IMX_CTRL_REGS   apbh_ctrl1;     /* 0x010 */

    IMX_CTRL_REGS   apbh_ctrl2;     /* 0x020 */

    IMX_CTRL_REGS   apbh_chan_ctrl; /* 0x030 */

    UINT32          apbh_devsel;    /* 0x040 */
    UINT8           pad1 [0xc];     /* 0x044 - reserved */

    UINT32          apbh_burst_size;/* 0x050 */
    UINT8           pad2 [0xc];     /* 0x054 - reserved */

    UINT32          apbh_debug;     /* 0x060 */
    UINT8           pad3 [0xc];     /* 0x064 - reserved */

    UINT8           pad4 [0x90];    /* 0x070 - reserved */

    APBH_CHAN_REGS  apbh_chan[0x10];/* 0x100 */

    UINT32          apbh_version;   /* 0x800 */
    UINT8           pad5 [0xc];     /* 0x804 - reserved */
    } APBH_REGS;

typedef struct apbh_cmd
    {
    UINT32          next;                       /* next command address */
    UINT32          cmd;                        /* APBH DMA command */
    UINT8 *         buf;                        /* pointer to DMA buffer */
    UINT32          pio [GPMI_APBHDMA_MAX_PIO]; /* PIO with DMA transfer */
    } APBH_CMD;

/* BCH Base Register Macros */

#define BCH_CTRL_CLKGATE_NO         (1 << 30)   /* clock gate */
#define BCH_CTRL_SFTRST_RST         (1 << 31)   /* block hold for reset state */
#define BCH_CTRL_COMPLETE_IRQ       (1 << 0)    /* COMPLETE_IRQ */
#define BCH_CTRL_COMPLETE_IRQ_EN    (1 << 8)    /* Enable COMPLETE_IRQ */

#define BCH_STATUS_BLK0_MASK        (0xff << 8)
#define BCH_STATUS_BLK0_UNCORRECTABLE (0xfe << 8)
#define BCH_STATUS_UNCORRECTABLE    (1 << 2)
#define BCH_STATUS_UNCORRECTABLE_MASK    (1 << 2)
#define BCH_STATUS_CORRECTED        (1 << 3)
#define BCH_STATUS_ALLONES          (1 << 4)
#define BCH_STATUS_COMPLETED_CE_MASK  (0xf << 16)

#define BCH_LAYOUT0_NBLK_OFF        24          /* subsequent block number */
#define BCH_LAYOUT0_MSIZE_OFF       16          /* metadata size */
#define BCH_LAYOUT0_ECC0_OFF        11          /* ecc level of first block */
#define BCH_LAYOUT0_GF1314_OFF      10          /* select GF13 or GF14 */
#define BCH_LAYOUT0_D0SIZE_OFF      0           /* data0 size in DWORDS */

#define BCH_LAYOUT1_PS_OFF          16          /* page size */
#define BCH_LAYOUT1_ECCN_OFF        11          /* ecc level of sebseq block */
#define BCH_LAYOUT1_GF1314_OFF      10          /* select GF13 or GF14 */
#define BCH_LAYOUT1_DNSIZE_OFF      0           /* sebseq data size in DWORDS */

typedef struct bch_bar_regs
    {
    UINT32 regs;                    /* 0x0 */
    UINT8  pad [0xc];               /* 0x4 */
    } BCH_BAR_REGS;

typedef struct bch_regs
    {
    IMX_CTRL_REGS   bch_ctrl;       /* 0x000 */
    BCH_BAR_REGS    bch_status0;    /* 0x010 */
    BCH_BAR_REGS    bch_mode;       /* 0x020 */
    BCH_BAR_REGS    bch_enbodeptr;  /* 0x030 */
    BCH_BAR_REGS    bch_dataptr;    /* 0x040 */
    BCH_BAR_REGS    bch_metaptr;    /* 0x050 */
    UINT8           pad1 [0x10];    /* 0x060 */
    BCH_BAR_REGS    bch_layoutsel;  /* 0x070 */
    BCH_BAR_REGS    bch_f0l0;       /* 0x080 */
    BCH_BAR_REGS    bch_f0l1;       /* 0x090 */
    BCH_BAR_REGS    bch_f1l0;       /* 0x0a0 */
    BCH_BAR_REGS    bch_f1l1;       /* 0x0b0 */
    BCH_BAR_REGS    bch_f2l0;       /* 0x0c0 */
    BCH_BAR_REGS    bch_f2l1;       /* 0x0d0 */
    BCH_BAR_REGS    bch_f3l0;       /* 0x0e0 */
    BCH_BAR_REGS    bch_f3l1;       /* 0x0f0 */
    BCH_BAR_REGS    bch_debug0;     /* 0x100 */
    BCH_BAR_REGS    bch_dbgkesread; /* 0x110 */
    BCH_BAR_REGS    bch_dbgcsferead;/* 0x120 */
    BCH_BAR_REGS    bch_dbgsyndread;/* 0x130 */
    BCH_BAR_REGS    bch_dbgahbmread;/* 0x140 */
    BCH_BAR_REGS    bch_blockname;  /* 0x150 */
    BCH_BAR_REGS    bch_version;    /* 0x160 */
    } BCH_REGS;

/* CS type */

typedef enum gpmi_cs_type
   {
   GPMI_CS_TYPE_OTHER = 0,
   GPMI_CS_TYPE_NAND_8BIT,  /* 8-bit NAND Flash */
   GPMI_CS_TYPE_NAND_16BIT  /* 16-bit NAND Flash */
   } GPMI_CS_TYPE;

/* controller information */

typedef struct gpmi_buf_info
    {
    UINT32          uPhyAddr;
    VXB_DMA_TAG_ID  dmaTag;
    VXB_DMA_MAP_ID  dmaMap;
    } GPMI_BUF_INFO, *pGPMI_BUF_INFO;

typedef struct gpmi
    {
#ifndef _WRS_CONFIG_VXBUS_LEGACY
    VXB_DEV_ID                  pDev;
#else
    VXB_DEVICE_ID               pDev;
#endif
    void *                      pRegHandle;
    void *                      pDmaHandle;
    void *                      pEccHandle;
    ULONG                       uRegBase;   /* register base */
    ULONG                       uDmaBase;   /* APBH DMA base */
    ULONG                       uEccBase;   /* BCH ECC base */
    UINT32                      uPlatType;  /* platform type */
    UINT32                      uFlag;
    APBH_CMD *                  pCmd;
    UINT32                      pCmdPhyAddr;
    UINT8 *                     pCmdBuf;
    UINT32                      pCmdBufPhyAddr;
    GPMI_CS_TYPE                uCsType[GPMI_MAX_CS];
    UINT8                       uNandCsCnt; /* CS count for NAND */
    UINT8                       uMaxBankCnt;/* max bank count */
#if ((_WRS_CONFIG_NAND_FLASH_ECC_FORMAT == 1) & (!defined(_WRS_CONFIG_NAND_INTERNAL_ECC)))
    /* Combined Metadata & Block 0, unbalanced ECC coverage */
    UINT32                      uBlockSize; /*512 or 1024*/
    UINT32                      uBlockNum; /*512 or 1024*/
    UINT32                      uMetaSize; /*Ecc fake plus usr data size*/
    UINT32                      uEccParitySize;/* parity size per block*/
    UINT8 *                     p0xffData; /*store 0xff data for reset buf*/
    UINT32                      hwEccStart;
    UINT32                      pAuxPhyAddr;
    UINT8 *                     pAuxBuf;
#endif
    DL_LIST                     chipList;
#ifndef _WRS_CONFIG_VXBUS_LEGACY
    VXB_RESOURCE_LIST           pResList;
#endif
    } GPMI, *pGPMI;

/* address space dfines */

#define GPMI_APBHDMA_BAR_ID 0       /* APBHDMA address space */
#define GPMI_REG_BAR_ID     1       /* GPMI register address space */
#define GPMI_BCH_BAR_ID     2       /* BCH address space */
#define GPMI_BAR_SIZE       0x2000  /* size for each bar */

#define GPMI_BCH_BLK_SIZE   1024

/* controller access defines */

#define GPMI_REG_READ(pGpmi, member)                                        \
    vxbRead32 ((pGpmi)->pRegHandle,                                         \
        (void *)((pGpmi)->uRegBase + (ULONG) (offsetof(GPMI_REGS, member))))

#define GPMI_REG_WRITE(pGpmi, member, data)                                 \
    vxbWrite32 ((pGpmi)->pRegHandle,                                        \
        (void *)((pGpmi)->uRegBase + (ULONG) (offsetof(GPMI_REGS, member))),\
        (ULONG) (data))

#define GPMI_APBH_READ(pGpmi, member)                                       \
    vxbRead32 ((pGpmi)->pDmaHandle,                                         \
        (void *)((pGpmi)->uDmaBase + (ULONG) (offsetof(APBH_REGS, member))))

#define GPMI_APBH_WRITE(pGpmi, member, data)                                \
    vxbWrite32 ((pGpmi)->pDmaHandle,                                        \
        (void *)((pGpmi)->uDmaBase + (ULONG) (offsetof(APBH_REGS, member))),\
        (ULONG) (data))

#define GPMI_BCH_READ(pGpmi, member)                                        \
    vxbRead32 ((pGpmi)->pEccHandle,                                         \
        (void *)((pGpmi)->uEccBase + (ULONG) (offsetof(BCH_REGS, member))))

#define GPMI_BCH_WRITE(pGpmi, member, data)                                 \
    vxbWrite32 ((pGpmi)->pEccHandle,                                        \
        (void *)((pGpmi)->uEccBase + (ULONG) (offsetof(BCH_REGS, member))), \
        (ULONG) (data))

#define GPMI_DBG_NONE        0
#define GPMI_DBG_BASIC       1
#define GPMI_DBG_VERBOSE     2
#define GPMI_DBG_ALL         3

/* debug information */

#define GPMI_DBG_MSG(level, fmt, a, b, c, d, e, f)                          \
    do                                                                      \
        {                                                                   \
        if (((level) <= gGpmiDbgLvl) && (_func_logMsg != NULL))                                         \
            (void)_func_logMsg (GPMI_DRV_NAME": "fmt, (_Vx_usr_arg_t)(a),   \
                                (_Vx_usr_arg_t)(b), (_Vx_usr_arg_t)(c),     \
                                (_Vx_usr_arg_t)(d), (_Vx_usr_arg_t)(e),     \
                                (_Vx_usr_arg_t)(f));                        \
        } while (0)

#define GPMI_DBG_ASSERT(val)                                                \
    do                                                                      \
        {                                                                   \
        if ((gGpmiDbgLvl > GPMI_DBG_BASIC) && (val))                        \
            (void)printf ("!ASSERT FAIL at %s, %d\n",__FUNCTION__, __LINE__);     \
        } while (0)

/* Function Declaration */

int  vxbGpmiFlashInit (pGPMI pGpmi, BOOL flag);
void vxbGpmiFlashClean (pGPMI pGpmi);

#ifndef _WRS_CONFIG_VXBUS_LEGACY
     STATUS vxbGpmiShow (VXB_DEV_ID pDev, int verbose);
#endif

#ifdef  __cplusplus
}
#endif

#endif /* __INCvxbGpmiCoreh */
