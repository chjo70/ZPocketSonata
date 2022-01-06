/* vxbNfcCore.h -  core code header for NFC driver */

/*
 * Copyright (c) 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
13may15,txu  fix V7STO-358 : wrong include after extern "C"
11feb15,lxj  added K70 support (US50342)
17jul14,e_d  written
*/

#ifndef __INCvxbNfcCoreh
#define __INCvxbNfcCoreh

#include <vxWorks.h>
#include <stdlib.h>
#include <string.h>
#include <logLib.h>
#include <hwif/vxBus.h>
#include <nand/vxbNandFlash.h>
#include <nand/vxbNandFlashLib.h>
#include <nfc/vxbNfc.h>

#ifdef  __cplusplus
 extern "C" {
#endif

#define NFC_MAX_CS                    2

#define NFC_BUF_SIZE                  (512 * 1024)   /* 512K buffer size */

#define NAND_CMD_WAIT_IN_SECS         10 

/* NFC command1 Register Macros */

#define NFC_COMMAND1_BYTE3(x)         ((x & 0xFF) << 16)
#define NFC_COMMAND1_BYTE2(x)         ((x & 0xFF) << 24)

/* NFC command2 Register Macros */

#define NFC_COMMAND2_BYTE1(x)         ((x & 0xFF) << 24)
#define NFC_COMMAND2_CODE(x)          ((x & 0xFFFF) << 8)
#define NFC_COMMAND2_BUFNO(x)         ((x & 0x3) << 1)
#define NFC_COMMAND2_BUSYSAT          0x1

#define NFCCMD2_READ_PAGE_CMD_CODE          0x7EE0
#define NFCCMD2_PROGRAM_PAGE_CMD_CODE       0x7FC0
#define NFCCMD2_ERASE_CMD_CODE              0x4EC0
#define NFCCMD2_READ_ID_CMD_CODE            0x4804
#define NFCCMD2_RESET_CMD_CODE              0x4040
#define NFCCMD2_DMA_PROGRAM_PAGE_CMD_CODE	  0xFFC8
#define NFCCMD2_RANDOM_IN_CMD_CODE          0x7140
#define NFCCMD2_RANDOM_OUT_CMD_CODE         0x70E0
#define NFCCMD2_STATUS_READ_CMD_CODE        0x4068

/* NFC column address Register Macros */

#define NFC_CAR_BYTE1(x)        ((x & 0xFF))
#define NFC_CAR_BYTE2(x)        ((x & 0xFF) << 8)

/* NFC Row address Register Macros */

#define NFC_RAR_BYTE1(x)        ((x & 0xFF))
#define NFC_RAR_BYTE2(x)        ((x & 0xFF) << 8)
#define NFC_RAR_BYTE3(x)        ((x & 0xFF) << 16)

#define NFC_RAR_CS0_V0          (24)
#define NFC_RAR_RB0_V0          (28)
#define NFC_RAR_CS0_V1          (28)
#define NFC_RAR_RB0_V1          (24)

#define NFC_RAR_ADDRMASK        0xFF000000

/* NFC Row address increment Register Macros */

#define NFC_RAI_INC1(x)        ((x & 0xFF))
#define NFC_RAI_INC2(x)        ((x & 0xFF) << 8)
#define NFC_RAI_INC3(x)        ((x & 0xFF) << 16)

/* NFC DMA configuration Register Macros */

#define NFC_DMACFG_ACT2        0x1
#define NFC_DMACFG_ACT1        (1 << 1)
#define NFC_DMACFG_OFFSET2(x)  ((x & 0x0F) << 9)
#define NFC_DMACFG_COUNT2(x)   ((x & 0x7F) << 13)
#define NFC_DMACFG_COUNT1(x)   ((x & 0x0FFF) << 20)

/* NFC Cash swap Register Macros */

#define NFC_SWAP_ADDR2(x)      (x << 1)
#define NFC_SWAP_ADDR1(x)      (x << 17)

/* NFC Flash configuration Register Macros */

#define NFC_CFG_PAGECNT(x)     (x & 0x0F)
#define NFC_CFG_AIBN           (1 << 4)
#define NFC_CFG_AIAD           (1 << 5)
#define NFC_CFG_BTMD           (1 << 6)
#define NFC_CFG_BITWIDTH       (1 << 7)
#define NFC_CFG_TIMEOUT(x)     ((x & 0x1F) << 8)
#define NFC_CFG_IDCNT(x)       ((x & 0x7) << 13)
#define NFC_CFG_FAST           (1 << 16)
#define NFC_CFG_ECCMODE(x)     ((x & 0x7) << 17)
#define NFC_CFG_DMAREQ         (1 << 20)
#define NFC_CFG_ECCSRAM        (1 << 21)
#define NFC_CFG_ECCAD(x)       (x << 22)
#define NFC_CFG_STOPWERR       (1 << 31)

/* NFC Interrupt status Register Macros */

#define NFC_ISR_DMABN(x)       (x & 0x03)
#define NFC_ISR_ECCBN(x)       ((x & 0x03) << 2)
#define NFC_ISR_RESBN(x)       ((x & 0x03) << 4)
#define NFC_ISR_IDLECLR        (1 << 17)
#define NFC_ISR_DONECLR        (1 << 18)
#define NFC_ISR_WERRCLR        (1 << 19)
#define NFC_ISR_IDLEEN         (1 << 20)
#define NFC_ISR_DONEEN         (1 << 21)
#define NFC_ISR_WERREN         (1 << 22)
#define NFC_ISR_DMABUSY        (1 << 23)
#define NFC_ISR_ECCBUSY        (1 << 24)
#define NFC_ISR_RESBUSY        (1 << 25)
#define NFC_ISR_CMDBUSY        (1 << 26)
#define NFC_ISR_WERRNS         (1 << 27)
#define NFC_ISR_IDLE           (1 << 29)
#define NFC_ISR_DONE           (1 << 30)
#define NFC_ISR_WERR           (1 << 31)

/* register map */

#define NFC_BUFFER             0x0000
#define NFC_CMD1_REG           0x3F00
#define NFC_CMD2_REG           0x3F04
#define NFC_CAR_REG            0x3F08
#define NFC_RAR_REG            0x3F0C
#define NFC_RPT_REG            0x3F10
#define NFC_RAI_REG            0x3F14
#define NFC_SR1_REG            0x3F18 
#define NFC_SR2_REG            0x3F1C
#define NFC_DMA_CH1_REG        0x3F20 
#define NFC_DMA_CFG_REG        0x3F24
#define NFC_SWAP_REG           0x3F28 
#define NFC_SECSZ_REG          0x3F2C 
#define NFC_CFG_REG            0x3F30
#define NFC_DMA_CH2_REG        0x3F34
#define NFC_ISR_REG            0x3F38 

#define NFC_BUFFER_SIZE        0x1000
#define NFC_MAINBUF_ADRS(n)    (n * 0x1000)
#define NFC_SPARE_ADRS(n)      ((n + 1) * 0x800)

/* CS type */

typedef enum nfc_cs_type
   {
   NFC_CS_TYPE_OTHER = 0,
   NFC_CS_TYPE_NAND_8BIT,  /* 8-bit NAND Flash */
   NFC_CS_TYPE_NAND_16BIT  /* 16-bit NAND Flash */
   } NFC_CS_TYPE;

typedef struct send_nand_cmd
    {
    UINT32 nandCmd[6];
    UINT32 nandCtrl[6];
    UINT8 nandCmdSize;
    UINT32 pageAdr;
    UINT32 colAdr;
    BOOL  isData;
    }SEND_NAND_CMD;

/* controller information */

typedef struct nfc
    {
    VXB_DEV_ID                  pDev;
    void *                      pRegHandle;
    ULONG                       regBase;    /* register base */
    UINT32                      uPlatType;  /* platform type */
    UINT32                      uFlag;
    UINT32                      stsValue;
    BOOL                        oobRW;
    UINT8                       uNandCsCnt; /* CS count for NAND */
    UINT8                       uCs0Shift;
    UINT8                       uMaxBankCnt;
    SEND_NAND_CMD               sendNandCmd;
    DL_LIST                     chipList;
    VXB_RESOURCE_LIST           pResList;
    SEM_ID                      cmdDone;
    FLASH_COL_ADDR_T            tColAddr;   /* tmp coladdr for  mutl-cycle */
    FLASH_ADDR_T                tPageAddr;  /* tmp pageaddr for multi-cycle */
    UINT32                      tBufAddr;   /* tmp address for rw buffer */
    UINT32                      tBufIndex;  /* tmp index for rw buffer addr */
    VXB_RESOURCE *              intRes;
    } NFC, *pNFC;

/* address space dfines */

#define NFC_REG_BAR_ID          0          /* CCSBAR register address space */
#define NFC_CS_BAR_ID           1          /* NAND buffer address space */

/* controller access defines */

#define NFC_REG_READ(pNfc, reg)                             \
    vxbRead32 ((pNfc)->pRegHandle,                          \
               (void *)((pNfc)->regBase + (ULONG) (reg)))

#define NFC_REG_WRITE(pNfc, reg, data)                      \
    vxbWrite32 ((pNfc)->pRegHandle,                         \
                (void *)((pNfc)->regBase + (ULONG) (reg)),  \
                (UINT32) (data))

#define NFC_DBG_NONE        0
#define NFC_DBG_BASIC       1
#define NFC_DBG_VERBOSE     2
#define NFC_DBG_ALL         3

/* debug information */

#ifdef NFC_DEBUG
#define NFC_DBG_MSG(level, fmt, a, b, c, d, e, f)                           \
    do                                                                      \
        {                                                                   \
        if (((level) <= gNfcDbgLvl) && (_func_logMsg != NULL))              \
            _func_logMsg (NFC_DRV_NAME": "fmt, (long)(a), (long)(b),        \
                          (long)(c), (long)(d), (long)(e), (long)(f));      \
        } while (0)

#define NFC_DBG_ASSERT(val)                                                 \
    do                                                                      \
        {                                                                   \
        if ((gNfcDbgLvl > NFC_DBG_BASIC) &&                                 \
            (_func_logMsg != NULL) && (val))                                \
            printf ("!ASSERT FAIL at %s, %d\n",__FUNCTION__, __LINE__);     \
        } while (0)
#else
#define NFC_DBG_MSG(level, fmt, a, b, c, d, e, f)
#define NFC_DBG_ASSERT(val) 
#endif /* NFC_DEBUG */
 
/* Function Declaration */

int  vxbNfcFlashInit (pNFC pNfc, BOOL flag);
void vxbNfcFlashClean (pNFC pNfc);
STATUS vxbNfcShow (VXB_DEV_ID pDev, UINT32 verbose);
#ifdef  __cplusplus
}
#endif

#endif /* __INCvxbFcmCoreh */

