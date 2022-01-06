/* vxbFcmCore.h -  core code header for FCM driver */

/*
 * Copyright (c) 2013-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
06aug15,dee  fix diab LP64 compiler warnings
13may15,txu  fix V7STO-358 : wrong include after extern "C"
10feb14,ywu  fix improper use of _WRS_CONFIG_FDT
16jan14,ywu  adopt to vxBus gen2
30jul13,ywu  written based on vxbFcm.h.
*/

#ifndef __INCvxbFcmCoreh
#define __INCvxbFcmCoreh


#include <vxWorks.h>
#include <stdlib.h>
#include <string.h>
#include <logLib.h>
#ifndef _WRS_CONFIG_VXBUS_LEGACY
#include <hwif/vxBus.h>
#else
#include <hwif/vxbus/vxBus.h>
#endif
#include <nand/vxbNandFlash.h>
#include <nand/vxbNandFlashLib.h>
#include <fcm/vxbFcm.h>

#ifdef  __cplusplus
 extern "C" {
#endif

#define FCM_MAX_CS              13
#define FCM_P2020_MAX_CS        8
#define FCM_MP8313_MAX_CS       4

#define FCM_BUF_SIZE            (512 * 1024)   /* 512K buffer size */

/* FCM Base Register Macros */

#define FCM_BR_VALID_BIT        (0x1 << 0)      /* valid bit */

#define FCM_BR_ATOM_RAWA        (0x1 << 2)      /* read-after-write-atomic */
#define FCM_BR_ATOM_WARA        (0x2 << 2)      /* write-after-read-atomic */
#define FCM_BR_ATOM_MASK        (0x3 << 2)      /* read/write atomic mask*/

#define FCM_BR_MSEL_GPCM        (0x0 << 5)      /* GPCM selected */
#define FCM_BR_MSEL_FCM         (0x1 << 5)      /* FCM selected */
#define FCM_BR_MSEL_UPMA        (0x4 << 5)      /* UPMA selected */
#define FCM_BR_MSEL_UPMB        (0x5 << 5)      /* UPMB selected */
#define FCM_BR_MSEL_UPMC        (0x6 << 5)      /* UPMC selected */
#define FCM_BR_MSEL_MASK        (0x7 << 5)      /* machine select mask */

#define FCM_BR_WP_RW            (0x0 << 8)      /* read/write allowed */
#define FCM_BR_WP_RO            (0x1 << 8)      /* only read allowed */
#define FCM_BR_WP_MASK          (0x1 << 8)      /* write protect mask */

#define FCM_BR_DECC_DIS         (0x0 << 9)      /* error checking disabled */
#define FCM_BR_DECC_PAR         (0x1 << 9)      /* parity checking enabled */
#define FCM_BR_DECC_ECC         (0x2 << 9)      /* ECC checking enabled */
#define FCM_BR_DECC_MASK        (0x3 << 9)      /* error checking mask */

#define FCM_BR_PW_8BIT          (0x1 << 11)     /* 8-bit port width */
#define FCM_BR_PW_16BIT         (0x2 << 11)     /* 16-bit port width */
#define FCM_BR_PW_MASK          (0x3 << 11)     /* port width mask */

#define FCM_BR_BA_MASK          0x7fff          /* 17 bit base address mask */

/* FCM Flash Mode Register Macros */

#define FCM_FMR_OP_NORM         (0x0 << 0)      /* Normal Operation */
#define FCM_FMR_OP_SIM_AUTOBOOT (0x1 << 0)      /* simulate auto-boot block */
#define FCM_FMR_OP_EXEC_WP      (0x2 << 0)      /* exec cmdseq in fir with wp */
#define FCM_FMR_OP_EXEC_RW      (0x3 << 0)      /* exec cmdseq in fir w/o wp */
#define FCM_FMR_OP_MASK         (0x3 << 0)      /* FMR flash operation mask */

#define FCM_FMR_AL_2BYTE        (0x0 << 4)      /* 2byte page address */
#define FCM_FMR_AL_3BYTE        (0x1 << 4)      /* 3byte page address */
#define FCM_FMR_AL_4BYTE        (0x2 << 4)      /* 4byte page address */
#define FCM_FMR_AL_MASK         (0x3 << 4)      /* FMR Address Length */

#define FCM_FMR_ECCM_6_8        (0x0 << 8)      /* ecc offsets 6, 7, 8*/
#define FCM_FMR_ECCM_8_10       (0x1 << 8)      /* ecc offsets 8, 9, 10 */
#define FCM_FMR_ECCM_MASK       (0x1 << 8)      /* FMR ecc offsets mask */

#define FCM_FMR_BOOT_AUTO       (0x0 << 11)     /* normal boot */
#define FCM_FMR_BOOT_NORM       (0x1 << 11)     /* auto-load 4k boot block */
#define FCM_FMR_BOOT_MASK       (0x1 << 11)     /* FMR boot mode mask */

#define FCM_FMR_CWTO_OFFSET     12              /* FMR cmd wait timeout offs */

/* FCM Option Register Macros */

#define FCM_OR_TRLXETHR_OFF     1               /* 17 bit AM mask */
#define FCM_OR_RST_OFF          3               /* 17 bit AM mask */
#define FCM_OR_SCY_OFF          4               /* 17 bit AM mask */
#define FCM_OR_CHT_OFF          7               /* 17 bit AM mask */
#define FCM_OR_CST_OFF          8               /* 17 bit AM mask */
#define FCM_OR_CSCT_OFF         9               /* 17 bit AM mask */
#define FCM_OR_PGS_OFF          10              /* page size mask */

#define FCM_OR_BCTLD_ON         (0x0 << 12)     /* buf control disabled */
#define FCM_OR_BCTLD_OFF        (0x1 << 12)     /* buf control enabled */
#define FCM_OR_BCTLD_MASK       (0x1 << 12)     /* buf control disable mask */

#define FCM_OR_AM_MASK          0x7ffff         /* 512KB AM mask */

/* FCM Flash Instruction Register Macros */

#define FCM_FIR_OP_NOP          0x0             /* nop or end of op sequence */
#define FCM_FIR_OP_CA           0x1             /* issue column addr in FPAR */
#define FCM_FIR_OP_PA           0x2             /* issue page addr in FBAR */
#define FCM_FIR_OP_UA           0x3             /* issue user addr from MDR */
#define FCM_FIR_OP_CMD0         0x4             /* issue cmd in FCR[CMD0] */
#define FCM_FIR_OP_CMD1         0x5             /* issue cmd in FCR[CMD1] */
#define FCM_FIR_OP_CMD2         0x6             /* issue cmd in FCR[CMD2] */
#define FCM_FIR_OP_CMD3         0x7             /* issue cmd in FCR[CMD3] */
#define FCM_FIR_OP_WB           0x8             /* write FBCR byte from buf */
#define FCM_FIR_OP_WS           0x9             /* write one byte from MDR */
#define FCM_FIR_OP_RB           0xa             /* read FBCR bytes to buffer */
#define FCM_FIR_OP_RS           0xb             /* read one byte to MDR */
#define FCM_FIR_OP_CW0          0xc             /* wait then issue FCR[CMD0] */
#define FCM_FIR_OP_CW1          0xd             /* wait then issue FCR[CMD1] */
#define FCM_FIR_OP_RBW          0xe             /* wait then read FBCR bytes */
#define FCM_FIR_OP_RSW          0xf             /* wait and read 1byte to MDR */

#define FCM_FIR_OP0_OFFSET      28              /* FIR OP0 offset */
#define FCM_FIR_OP1_OFFSET      24              /* FIR OP1 offset */
#define FCM_FIR_OP2_OFFSET      20              /* FIR OP2 offset */
#define FCM_FIR_OP3_OFFSET      16              /* FIR OP3 offset */
#define FCM_FIR_OP4_OFFSET      12              /* FIR OP4 offset */
#define FCM_FIR_OP5_OFFSET      8               /* FIR OP5 offset */
#define FCM_FIR_OP6_OFFSET      4               /* FIR OP6 offset */
#define FCM_FIR_OP7_OFFSET      0               /* FIR OP7 offset */


/* FCM Flash Command Register Macros */

#define FCM_FCR_CMD0_OFFSET     24              /* FCR CMD0 offset */
#define FCM_FCR_CMD1_OFFSET     16              /* FCR CMD1 offset */
#define FCM_FCR_CMD2_OFFSET     8               /* FCR CMD2 offset */
#define FCM_FCR_CMD3_OFFSET     0               /* FCR CMD3 offset */


/* FCM Page Addr register Macros */

#define FCM_FPAR_SP_CI_OFFSET   0               /* FPAR Column Index offset */
#define FCM_FPAR_SP_MS_OFFSET   9               /* Main/Spare locator offset */
#define FCM_FPAR_SP_PI_OFFSET   10              /* FPAR Page Index offset */
#define FCM_FPAR_SP_PI_BITS     5               /* FPAR Page Index bits */
#define FCM_FPAR_SP_PI_MASK     0x1F            /* FPAR Page Index mask */

#define FCM_FPAR_LP_CI_OFFSET   0               /* FPAR Column Index offset */
#define FCM_FPAR_LP_MS_OFFSET   11              /* Main/Spare locator offset */
#define FCM_FPAR_LP_PI_OFFSET   12              /* FPAR Page Index offset */
#define FCM_FPAR_LP_PI_BITS     6               /* FPAR Page Index bits */
#define FCM_FPAR_LP_PI_MASK     0x3F            /* FPAR Page Index mask */

/* FCM Transfer Error Status Regsiter Macros */

#define FCM_LTESR_CC_DONE       1               /* FCM Operation complete */
#define FCM_LTESR_CS            (1 << 19)       /* FCM Operation complete */
#define FCM_LTESR_WP            (1 << 26)       /* FCM Write Protect error */
#define FCM_LTESR_PAR           (1 << 29)       /* FCM Parity or Ecc Error */
#define FCM_LTESR_FCT           (1 << 30)       /* FCM Command Timeout */

/* FCM Data register Macros */

#define FCM_MDR_AS0_OFFSET      0               /* MDR AS0 offset */
#define FCM_MDR_AS1_OFFSET      8               /* MDR AS1 offset */
#define FCM_MDR_AS2_OFFSET      16              /* MDR AS2 offset */
#define FCM_MDR_AS3_OFFSET      24              /* MDR AS3 offset */

/* FCM Transfer Error ECC register Macros */

#define FCM_LTECCR_MBUE_OFFSET  0               /* multi-bit error offset */
#define FCM_LTECCR_SBCE_OFFSET  16              /* single bit error offset */

/* FCM  ECC register Macros */

#define FCM_FECC_ECC_OFFSET     0               /* 24bit ecc offset */
#define FCM_FECC_VALID_OFFSET   31              /* Valid bit offset */

/* register map */

typedef struct fcm_bank_reg {
    UINT32  br;     /* base register */
    UINT32  or;     /* option register */
    } FCM_BANK_REG;

typedef struct fcm_regs
    {
    FCM_BANK_REG    bank [13];
    /*
     * 0x000 - bank reg, the actual number of bank register could be less
     * than 13, and rest part should be reserved unused. The reason to keep
     * all of them  defined is in order to unify reg struct of different
     * platforms, the real access should be controlled by pFcm->uMaxBankCnt.
     */
    UINT32          mar;                /* 0x068 - UPM addr reg */
    UINT8           pad1 [0x4];         /* 0x06c - reserved */
    UINT32          mamr;               /* 0x070 - UPMA mode reg */
    UINT32          mbmr;               /* 0x074 - UPMB mode reg */
    UINT32          mcmr;               /* 0x078 - UPMC mode reg */
    UINT8           pad2 [0x8];         /* 0x07c - reserved */
    UINT32          mrtpr;              /* 0x084 - mem refresh timer prescale */
    UINT32          mdr;                /* 0x088 - UPM/FCM data reg */
    UINT8           pad3 [0x4];         /* 0x08c - reserved */
    UINT32          lsor;               /* 0x090 - special operation init reg */
    UINT8           pad4 [0xc];         /* 0x094 - reserved */
    UINT32          lurt;               /* 0x0a0 - UPM refresh timer */
    UINT8           pad5 [0xc];         /* 0x0a4 - reserved */
    UINT32          ltesr;              /* 0x0b0 - transfer error status reg */
    UINT32          ltedr;              /* 0x0b4 - transfer error disable reg */
    UINT32          lteir;              /* 0x0b8 - transfer error intr reg */
    UINT32          lteatr;             /* 0x0bc - transfer error attr reg */
    UINT32          ltear;              /* 0x0c0 - transfer error addr reg */
    UINT32          lteccr;             /* 0x0c4 - transfer error ECC reg */
    UINT8           pad6 [0x8];         /* 0x0c8 - reserved */
    UINT32          lbcr;               /* 0x0d0 - configuration reg */
    UINT32          lcrr;               /* 0x0d4 - clock ratio reg */
    UINT8           pad7 [0x8];         /* 0x0d8 - reserved */
    UINT32          fmr;                /* 0x0e0 - flash mode reg */
    UINT32          fir;                /* 0x0e4 - flash instruction reg */
    UINT32          fcr;                /* 0x0e8 - flash command reg */
    UINT32          fbar;               /* 0x0ec - flash block addr reg */
    UINT32          fpar;               /* 0x0f0 - flash page addr reg */
    UINT32          fbcr;               /* 0x0f4 - flash byte count reg */
    UINT8           pad8 [0x8];         /* 0x0f8 - reserved */
    UINT32          fecc[4];            /* 0x100 - flash ecc reg */
    } FCM_REGS;

/* CS type */

typedef enum fcm_cs_type
   {
   FCM_CS_TYPE_OTHER = 0,
   FCM_CS_TYPE_NAND_8BIT,  /* 8-bit NAND Flash */
   FCM_CS_TYPE_NAND_16BIT  /* 16-bit NAND Flash */
   } FCM_CS_TYPE;

/* controller information */

typedef struct fcm
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
    FCM_CS_TYPE                 uCsType[FCM_MAX_CS];
    UINT8                       uNandCsCnt; /* CS count for NAND */
    UINT8                       uMaxBankCnt;/* max bank count */
    DL_LIST                     chipList;
#ifndef _WRS_CONFIG_VXBUS_LEGACY
    VXB_RESOURCE_LIST           pResList;
#endif
    FLASH_COL_ADDR_T            tColAddr;   /* tmp coladdr for  mutl-cycle */
    FLASH_ADDR_T                tPageAddr;  /* tmp pageaddr for multi-cycle */
    UINT32                      tBufAddr;   /* tmp address for rw buffer */
    UINT32                      tBufIndex;  /* tmp index for rw buffer addr */
    } FCM, *pFCM;

/* address space dfines */

#define FCM_REG_BAR_ID 0    /* CCSBAR register address space */
#define FCM_CS_BAR_ID  1    /* NAND buffer address space */

/* controller access defines */

#define FCM_REG_READ(pFcm, member)                                          \
    vxbRead32 ((pFcm)->pRegHandle,                                          \
        (void *)((pFcm)->uRegBase + (ULONG) (offsetof (FCM_REGS, member))))

#define FCM_REG_WRITE(pFcm, member, data)                                   \
    vxbWrite32 ((pFcm)->pRegHandle,                                         \
        (void *)((pFcm)->uRegBase + (ULONG) (offsetof (FCM_REGS, member))), \
        (data))

#define FCM_DBG_NONE        0
#define FCM_DBG_BASIC       1
#define FCM_DBG_VERBOSE     2
#define FCM_DBG_ALL         3

/* debug information */

#define FCM_DBG_MSG(level, fmt, a, b, c, d, e, f)                           \
    do                                                                      \
        {                                                                   \
        if (((level) <= gFcmDbgLvl) && (_func_logMsg != NULL))              \
            _func_logMsg (FCM_DRV_NAME": "fmt, (long)(a), (long)(b),        \
                          (long)(c), (long)(d), (long)(e), (long)(f));      \
        } while (0)

#define FCM_DBG_ASSERT(val)                                                 \
    do                                                                      \
        {                                                                   \
        if ((gFcmDbgLvl > FCM_DBG_BASIC) &&                                 \
            (_func_logMsg != NULL) && (val))                                \
            (void) printf ("!ASSERT FAIL at %s, %d\n",__FUNCTION__, __LINE__);     \
        } while (0)

/* Function Declaration */

int  vxbFcmFlashInit (pFCM pFcm, BOOL flag);
void vxbFcmFlashClean (pFCM pFcm);

#ifndef _WRS_CONFIG_VXBUS_LEGACY
     STATUS vxbFcmShow (VXB_DEV_ID pDev, int verbose);
#endif

#ifdef  __cplusplus
}
#endif

#endif /* __INCvxbFcmCoreh */

