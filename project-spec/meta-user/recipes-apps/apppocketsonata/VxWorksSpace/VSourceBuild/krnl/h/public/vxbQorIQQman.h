/* vxbQorIQQman.h - Queue Manager driver header for QorIQ */

/*
 * Copyright (c) 2008, 2010, 2012-2014, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
DESCRIPTION
This file contains register definitions for the Freescale QorIQ
Queue Manager. There Queue Manager actually has two different ranges
of registers. One is part of the CCB and resides inside the CCSBAR
space, starting at offset 0x318000. The others reside in a 2MB
window which is defined by one of the local access window (LAW)
registers.

This file contains just the definitions for the registers within
the CCSBAR region.
*/

/*
modification history
--------------------
02may17,wch  added support for ARM (F8333)
25apr14,fao  merged this file from vx6.9.3.3 and corrected the modify history
25jan13,wap  Apply updates from review
13aug12,wap  Update Qman for T4240
24feb10,wap  Make reserved memory area sizing configurable via BSP
10feb10,wap  Update LIO and IO configuration register definitions for rev
                 2.0 silicon
02dec08,wap  written
*/

#ifndef __INCvxbQorIQQmanh
#define __INCvxbQorIQQmanh

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Queue manager configuration and control registers.
 * These are relative to CCSBAR, starting at offset 0x318000.
 */

/* CoreNet software portal configuration registers */

#define QMAN_SP0                0x00000000
#define QMAN_SP1                0x00000010
#define QMAN_SP2                0x00000020
#define QMAN_SP3                0x00000030
#define QMAN_SP4                0x00000040
#define QMAN_SP5                0x00000050
#define QMAN_SP6                0x00000060
#define QMAN_SP7                0x00000070
#define QMAN_SP8                0x00000080
#define QMAN_SP9                0x00000090

#define QMAN_SP(x, y)           ((y) + QMAN_SP0 + (0x10 * (x)))

#define QMAN_SP_LIO             0x00000000 /* LIO config */
#define QMAN_SP_IO              0x00000004 /* I/O config */
#define QMAN_SP_DD              0x0000000C /* Dynamic Debug */

/* CoreNet Software LIO Configuration Register */

#define QMAN_SP_LIO_DLIODN      0x00000FFF /* DQRR Logical I/O dev # */
#define QMAN_SP_LIO_LIODN_OFF   0x03FF0000 /* LIODN offset */

#define QMAN_DLIODN(x)          ((x) & QMAN_SP_PID_DLIODN)
#define QMAN_LIODNOFF(x)        (((x) << 16) & QMAN_SP_LIO_LIODN_OFF)

/* CoreNet Software Portal IO Configuration Register */

#define QMAN_SP_IO_FLIODN       0x00000FFF /* Frame Data logical I/O dev # */
#define QMAN_SP_IO_SDEST        0x00070000 /* Stashing destination */

#define QMAN_SDEST(x)           (((x) << 16) & QMAN_SP_IO_SDEST)

/* Man CoreNet Software Portal Dynamic Debug Configuration Register */

#define QMAN_SP_DD_E_TP_CFG     0x000001FF
#define QMAN_SP_DD_ED_TP_CFG    0x01FF0000

/* Dynamic debug configuration registers */

#define QMAN_DD_CFG             0x00000200 /* Dynamic debug */
#define QMAN_DD_SP_IHRSR        0x00000210 /* Int. Halt Request Sts */
#define QMAN_DD_SP_IHRFR        0x00000214 /* Int. Halt Request Force */
#define QMAN_DD_SP_HASR         0x00000218 /* Halt Ack. Status */
#define QMAN_DD_DCP_IHRSR       0x00000220 /* Int. Halt Request Sts */
#define QMAN_DD_DCP_IHRFR       0x00000224 /* Int. Halt Request Force */
#define QMAN_DD_DCP_HASR        0x00000228 /* Halt Ack. Status */

#define QMAN_DD_CFG_MCFG        0x0000000F
#define QMAN_DD_CFG_MDD         0x00000030

/* Direct connect portal configuration registers */

#define QMAN_DCP0               0x00000300
#define QMAN_DCP1               0x00000310
#define QMAN_DCP2               0x00000320
#define QMAN_DCP3               0x00000330

#define QMAN_DCP(x, y)          ((y) + QMAN_DCP0 + (0x10 * (x)))

#define QMAN_DCP_CFG            0x00000000 /* Configuration */
#define QMAN_DCP_DD_CFG         0x00000004 /* Dyn. Debug config */
#define QMAN_DCP_DLM_CFG        0x00000008 /* Dyn. Latancy Monitor cfg */
#define QMAN_DCP_DLM_AVG        0x0000000C /* Dyn. LatMon Average */

/* Direct connect portal configuration register */

#define QMAN_DCP_CFG_SERND      0x0000001F /* reject destination */
#define QMAN_DCP_CFG_RJ_HW      0x00000100 /* rejection to hardware */

/* Direct connect portal configuration register for Qman Rev 3 */

#define QMAN_V3_DCP_CFG_SERND   0x000003FF /* reject destination */
#define QMAN_V3_DCP_CFG_RJ_HW   0x00001000 /* rejection to hardware */
#define QMAN_V3_DCP_CFG_CEETME  0xFFFF0000 /* customer edge traffic management enable */

/* Packed Frame Descriptor Record (PFDR) Manager Query Registers */

#define QMAN_PFDR_FPC           0x00000400 /* Free pool count */
#define QMAN_PFDR_HEAD          0x00000404 /* Head pointer */
#define QMAN_PFDR_TAIL          0x00000408 /* Tail pointer */
#define QMAN_PFDR_LWIT          0x00000410 /* Low wmark intr. thresh */
#define QMAN_PFDR_CFG           0x00000414 /* Configuration */

/* Single Frame Descriptor Record (SFDR) Manager Registers */

#define QMAN_SFDR_CFG           0x00000500 /* Configuration */

/* Work Queue Semaphore and Context Manager Registers */

#define QMAN_WQ_CFG0            0x00000600 /* WQ class sched cfg0 */
#define QMAN_WQ_CFG1            0x00000604 /* WQ class sched cfg1 */
#define QMAN_WQ_CFG2            0x00000608 /* WQ class sched cfg2 */
#define QMAN_WQ_CFG3            0x0000060C /* WQ class sched cfg3 */
#define QMAN_WQ_CFG4            0x00000610 /* WQ class sched cfg4 */
#define QMAN_WQ_CFG5            0x00000614 /* WQ class sched cfg5 */
#define QMAN_WQ_DFLT_WQID       0x00000630 /* default enqueue ID */
#define QMAN_WQ_DD_SW_CFGA      0x00000640 /* Dyn. SW Channel Dbg cfgA */
#define QMAN_WQ_DD_SW_CFGB      0x00000644 /* Dyn. SW Channel Dbg cfgB */
#define QMAN_WQ_DD_SW_CFGC      0x00000648 /* Dyn. SW Channel Dbg cfgC */
#define QMAN_WQ_DD_SW_CFGD      0x0000064C /* Dyn. SW Channel Dbg cfgD */
#define QMAN_WQ_DD_SW_CFGE      0x00000650 /* Dyn. SW Channel Dbg cfgE */
#define QMAN_WQ_DD_POOL_CFGA    0x00000680 /* Dyn. Pool Chan. Dbg cfgA */
#define QMAN_WQ_DD_POOL_CFGB    0x00000684 /* Dyn. Pool Chan. Dbg cfgB */
#define QMAN_WQ_DD_POOL_CFGC    0x00000688 /* Dyn. Pool Chan. Dbg cfgC */
#define QMAN_WQ_DD_POOL_CFGD    0x0000068C /* Dyn. Pool Chan. Dbg cfgD */
#define QMAN_WQ_DD_POOL_CFGE    0x00000690 /* Dyn. Pool Chan. Dbg cfgE */
#define QMAN_WQ_DD_POOL_CFGF    0x00000694 /* Dyn. Pool Chan. Dbg cfgF */
#define QMAN_WQ_DD_POOL_CFGG    0x00000698 /* Dyn. Pool Chan. Dbg cfgG */
#define QMAN_WQ_DD_POOL_CFGH    0x0000069C /* Dyn. Pool Chan. Dbg cfgH */
#define QMAN_WQ_DD_DCP0_CFGA    0x000006C0 /* Dyn. DCP Chan. Dbg cfgA */
#define QMAN_WQ_DD_DCP0_CFGB    0x000006C4 /* Dyn. DCP Chan. Dbg cfgB */
#define QMAN_WQ_DD_DCP0_CFGC    0x000006C8 /* Dyn. DCP Chan. Dbg cfgC */
#define QMAN_WQ_DD_DCP0_CFGD    0x000006CC /* Dyn. DCP Chan. Dbg cfgD */
#define QMAN_WQ_DD_DCP0_CFGE    0x000006D0 /* Dyn. DCP Chan. Dbg cfgE */
#define QMAN_WQ_DD_DCP0_CFGF    0x000006D4 /* Dyn. DCP Chan. Dbg cfgF */
#define QMAN_WQ_DD_DCP1_CFGA    0x00000700 /* Dyn. DCP Chan. Dbg cfgA */
#define QMAN_WQ_DD_DCP1_CFGB    0x00000704 /* Dyn. DCP Chan. Dbg cfgB */
#define QMAN_WQ_DD_DCP1_CFGC    0x00000708 /* Dyn. DCP Chan. Dbg cfgC */
#define QMAN_WQ_DD_DCP1_CFGD    0x0000070C /* Dyn. DCP Chan. Dbg cfgD */
#define QMAN_WQ_DD_DCP1_CFGE    0x00000710 /* Dyn. DCP Chan. Dbg cfgE */
#define QMAN_WQ_DD_DCP1_CFGF    0x00000714 /* Dyn. DCP Chan. Dbg cfgF */
#define QMAN_WQ_DD_DCP2_CFGA    0x00000740 /* Dyn. DCP Chan. Dbg cfgA */
#define QMAN_WQ_DD_DCP3_CFGA    0x00000780 /* Dyn. DCP Chan. Dbg cfgA */

/* Congestion Manager (CM) Registers */

#define QMAN_CM_CFG             0x00000800 /* Configuration */

/* Qman Error Capture Registers */

#define QMAN_EC_SR              0x00000A00 /* Status register */
#define QMAN_EC_IR              0x00000A04 /* Information register */
#define QMAN_EC_ECC_ADDR        0x00000A08 /* Address register */
#define QMAN_EC_ECC_DATA0       0x00000A10 /* Data 0 register */
#define QMAN_EC_ECC_DATA1       0x00000A14 /* Data 0 register */
#define QMAN_EC_ECC_DATA2       0x00000A18 /* Data 0 register */
#define QMAN_EC_ECC_DATA3       0x00000A1C /* Data 0 register */
#define QMAN_EC_ECC_DATA4       0x00000A20 /* Data 0 register */
#define QMAN_EC_ECC_DATA5       0x00000A24 /* Data 0 register */
#define QMAN_EC_ECC_DATA6       0x00000A28 /* Data 0 register */
#define QMAN_EC_ECC_DATA7       0x00000A2C /* Data 0 register */
#define QMAN_EC_ECC_DATA8       0x00000A30 /* Data 0 register */
#define QMAN_EC_ECC_DATA9       0x00000A34 /* Data 0 register */
#define QMAN_EC_ECC_DATA10      0x00000A38 /* Data 0 register */
#define QMAN_EC_ECC_DATA11      0x00000A3C /* Data 0 register */
#define QMAN_EC_ECC_DATA12      0x00000A40 /* Data 0 register */
#define QMAN_EC_ECC_DATA13      0x00000A44 /* Data 0 register */
#define QMAN_EC_ECC_DATA14      0x00000A48 /* Data 0 register */
#define QMAN_EC_ECC_DATA15      0x00000A4C /* Data 0 register */
#define QMAN_EC_ECC_SBET        0x00000A70 /* Single bit ECC err thr. */
#define QMAN_EC_ECC_COUNT0      0x00000A80 /* Single bit err. cnt 0 */
#define QMAN_EC_ECC_COUNT1      0x00000A84 /* Single bit err. cnt 1 */
#define QMAN_EC_ECC_COUNT2      0x00000A88 /* Single bit err. cnt 2 */
#define QMAN_EC_ECC_COUNT3      0x00000A8C /* Single bit err. cnt 3 */
#define QMAN_EC_ECC_COUNT4      0x00000A90 /* Single bit err. cnt 4 */
#define QMAN_EC_ECC_COUNT5      0x00000A94 /* Single bit err. cnt 5 */
#define QMAN_EC_ECC_COUNT6      0x00000A98 /* Single bit err. cnt 6 */

/*
 * Qman Initialization and Debug Control registers
 * (Do we really need more debug registers?)
 */

#define QMAN_MGR_CMDRES         0x00000B00 /* Command/result register */
#define QMAN_MGR_PARM0          0x00000B04 /* Parameter 0 */
#define QMAN_MGR_PARM1          0x00000B08 /* Parameter 1 */
#define QMAN_MGR_MR0            0x00000B20 /* Return register 0 */
#define QMAN_MGR_MR1            0x00000B24 /* Return register 1 */
#define QMAN_MGR_MR2            0x00000B28 /* Return register 2 */
#define QMAN_MGR_MR3            0x00000B2C /* Return register 3 */
#define QMAN_MGR_MR4            0x00000B30 /* Return register 4 */
#define QMAN_MGR_MR5            0x00000B34 /* Return register 5 */
#define QMAN_MGR_MR6            0x00000B38 /* Return register 6 */
#define QMAN_MGR_MR7            0x00000B3C /* Return register 7 */
#define QMAN_MGR_MR8            0x00000B40 /* Return register 8 */
#define QMAN_MGR_MR9            0x00000B44 /* Return register 9 */
#define QMAN_MGR_MR10           0x00000B48 /* Return register 10 */
#define QMAN_MGR_MR11           0x00000B4C /* Return register 11 */
#define QMAN_MGR_MR12           0x00000B50 /* Return register 12 */
#define QMAN_MGR_MR13           0x00000B54 /* Return register 13 */
#define QMAN_MGR_MR14           0x00000B58 /* Return register 14 */
#define QMAN_MGR_MR15           0x00000B5C /* Return register 15 */

/* Qman Management Command/Result Register */

#define QMAN_MGR_CMDRES_CMDRST  0xFF000000

#define QMAN_MGR_CMD_NULL       0x00000000
#define QMAN_MGR_CMD_INIT_PFDR  0x01000000 /* Init packed framedesc pool */
#define QMAN_MGR_CMD_READ_PFDR  0x02000000 /* Read one PFDR */
#define QMAN_MGR_CMD_GET_FQD_FL 0x10000000 /* Get FQD cache fill levels */
#define QMAN_MGR_CMD_GET_FQD_CT 0x11000000 /* Get FQD cache tags */
#define QMAN_MGR_CMD_GET_FQD_CC 0x12000000 /* Get FQD cache contents */

#define QMAN_MGR_RSLT_WAITING   0x00000000 /* Waiting for first command */
#define QMAN_MGR_RSLT_OK_NORES  0xF0000000 /* Cmd done, no err, no result */
#define QMAN_MGR_RSLT_OK_RES    0xF1000000 /* Cmd done, no err, with result */
#define QMAN_MGR_RSLT_ABORT     0xF8000000 /* Cmd aborted with error */
#define QMAN_MGR_RSLT_BADPTR    0xFF000000 /* Cnd aborted, bad stard/end ptr */

/* Qman ID/revision registers */

#define QMAN_IP_REV1            0x00000BF8 /* Block rev. 1 */
#define QMAN_IP_REV2            0x00000BFC /* Block rev. 2 */

#define QMAN_IP_ID              0xFFFF0000 /* IP indentifier */
#define QMAN_IP_MJ              0x0000FF00 /* Major revision */
#define QMAN_IP_MN              0x000000FF /* Minor revision */

#define QMAN_ID(x)              (((x) & QMAN_IP_ID) >> 16)
#define QMAN_MJ(x)              (((x) & QMAN_IP_MJ) >> 8)
#define QMAN_MN(x)              ((x) & QMAN_IP_MN)

#define QMAN_REVISION1          0x01
#define QMAN_REVISION2          0x02
#define QMAN_REVISION3          0x03

/* CoreNet Initiator Interface Memory Window Configuration Registers */

#define QMAN_MW_FQD_BARHI       0x00000C00 /* Extended base addr. */
#define QMAN_MW_FQD_BARLO       0x00000C04 /* Base address */
#define QMAN_MW_FQD_ATTR        0x00000C10 /* FQD attributes */
#define QMAN_MW_PFDR_BARHI      0x00000C20 /* Extended base addr. */
#define QMAN_MW_PFDR_BARLO      0x00000C24 /* Base address */
#define QMAN_MW_PFDR_ATTR       0x00000C30 /* PFDR attributes */
#define QMAN_MW_SP_BARHI        0x00000C80 /* Software portal bar */
#define QMAN_MW_SP_BARLO        0x00000C84 /* Software portal bar */
#define QMAN_MW_CISCHED_CFG     0x00000D00 /* CoreNet Initiator sched */
#define QMAN_MW_SRCID           0x00000D04 /* QMan source ID */
#define QMAN_MW_LIODNUM         0x00000D08 /* Logical I/O device # */
#define QMAN_MW_CIRLM_CFG       0x00000D10 /* Initiator Read LatMon cfg */
#define QMAN_MW_CIRLM_AVF       0x00000D14 /* Initiator Read LatMon avg */

/* FQD/PFDR window attributes */

#define QMAN_MW_ATTR_SIZE       0x000000FF /* Window size */
#define QMAN_MW_ATTR_CPCSTASH   0x20000000 /* CPC stashing enable */
#define QMAN_MW_ATTR_HIPRIO     0x40000000 /* Transaction priority */
#define QMAN_MW_ATTR_ENABLE     0x80000000 /* Access enable */

#define QMAN_MW_SIZE_4KB        0x0000000B
#define QMAN_MW_SIZE_8KB        0x0000000C
#define QMAN_MW_SIZE_16KB       0x0000000D
#define QMAN_MW_SIZE_32KB       0x0000000E
#define QMAN_MW_SIZE_64KB       0x0000000F
#define QMAN_MW_SIZE_128KB      0x00000010
#define QMAN_MW_SIZE_256KB      0x00000011
#define QMAN_MW_SIZE_512KB      0x00000012
#define QMAN_MW_SIZE_1MB        0x00000013
#define QMAN_MW_SIZE_2MB        0x00000014
#define QMAN_MW_SIZE_4MB        0x00000015
#define QMAN_MW_SIZE_8MB        0x00000016
#define QMAN_MW_SIZE_16MB       0x00000017
#define QMAN_MW_SIZE_32MB       0x00000018
#define QMAN_MW_SIZE_64MB       0x00000019
#define QMAN_MW_SIZE_128MB      0x0000001A
#define QMAN_MW_SIZE_256MB      0x0000001B
#define QMAN_MW_SIZE_512MB      0x0000001C
#define QMAN_MW_SIZE_1GB        0x0000001D

/* Qman Interrupt and error registers */

#define QMAN_ERR_ISR            0x00000E00 /* Interrupt status */
#define QMAN_ERR_IER            0x00000E04 /* Interrupt enable */
#define QMAN_ERR_IDR            0x00000E08 /* Interrupt disable */
#define QMAN_ERR_IIR            0x00000E0C /* Interrupt inhibit */
#define QMAN_ERR_HER            0x00000E14 /* Interrupt halt */

#define QMAN_ERR_ISR_IEQI       0x00000001 /* Invalid enqueue queue */
#define QMAN_ERR_ISR_IECI       0x00000002 /* Invalid enqueue channel */
#define QMAN_ERR_ISR_IESI       0x00000004 /* Invalid enqueue state */
#define QMAN_ERR_ISR_IEOI       0x00000008 /* Invalid enqueue overflow */
#define QMAN_ERR_ISR_IDQI       0x00000010 /* Invalid dequeue queue */
#define QMAN_ERR_ISR_IDSI       0x00000020 /* Invalid dequeue source */
#define QMAN_ERR_ISR_IDFI       0x00000040 /* Invalid dequeue FQ */
#define QMAN_ERR_ISR_IDDI       0x00000080 /* Invalid dequeue portal */
#define QMAN_ERR_ISR_ICVI       0x00001000 /* Invalid command verb */
#define QMAN_ERR_ISR_SBEI       0x01000000 /* ECC single bit error */
#define QMAN_ERR_ISR_MBEI       0x02000000 /* ECC multi-bit error */
#define QMAN_ERR_ISR_PLWI       0x04000000 /* PFDR low wmark */
#define QMAN_ERR_ISR_CITT       0x08000000 /* Invalid CoreNet target */
#define QMAN_ERR_ISR_CTDE       0x10000000 /* CoreNet tgt data error */
#define QMAN_ERR_ISR_CIDE       0x20000000 /* CoreNet initiator data err */

#define QORIQ_QMAN_NAME         "QorIQQman"

#define QMAN_DEFAULT_FQD_SIZE   0x100000
#define QMAN_DEFAULT_PFDR_SIZE  0x100000

typedef struct qman_drv_ctrl
    {
    VXB_DEV_ID      qmanDev;
    VXB_RESOURCE *  pRes;
    void *          qmanBar;
    void *          qmanHandle;
    SEM_ID          qmanSem;
    void *          qmanFqMem;
    UINT32          qmanFqSize;
    void *          qmanPfdrMem;
    UINT32          qmanPfdrSize;
    void *          qmanLawBase;
    UINT32          qmanLawSize;
    UINT32          qmanRev;
    int             qmanPortalCnt;
    QPORTAL         qmanPortal[QPORTAL_PORTAL_CNT];
    } QMAN_DRV_CTRL;

#define QMAN_BAR(p)   ((QMAN_DRV_CTRL *)(p))->qmanBar
#define QMAN_HANDLE(p)   ((QMAN_DRV_CTRL *)(p))->qmanHandle

#define CSR_READ_4(pDev, addr)                                  \
        vxbRead32 (QMAN_HANDLE(pDev),                           \
        (UINT32 *)((char *)QMAN_BAR(pDev) + addr))

#define CSR_WRITE_4(pDev, addr, data)                           \
        vxbWrite32 (QMAN_HANDLE(pDev),                          \
        (UINT32 *)((char *)QMAN_BAR(pDev) + addr), (UINT32)data)

#define QMAN_READ(pDev, idx, addr)      \
        CSR_READ_4(pDev, addr + (idx * QORIQ_QMAN_SIZE))

#define QMAN_WRITE(pDev, idx, addr, data)   \
        CSR_WRITE_4(pDev, addr + (idx * QORIQ_QMAN_SIZE), data)

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbQorIQQmanh */
