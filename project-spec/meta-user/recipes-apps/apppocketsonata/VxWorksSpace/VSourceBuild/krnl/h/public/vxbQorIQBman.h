/* vxbQorIQBman.h - header file for QorIQ Buffer Manager driver */

/*
 * Copyright (c) 2008, 2012-2014, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
DESCRIPTION

This file contains register definitions for the Freescale QorIQ buffer
manafer configuration registers. These are mapped within the CCSBAR
region with the other peripheral registers.
*/

/*
modification history
--------------------
02may17,wch  added support for ARM (F8333)
12mar14,fao  corrected the modify history
25jan13,wap  Apply updates from review
13aug12,wap  Update Bman for T4240
24feb10,wap  Make reserved memory area sizing configurable via BSP
06jan09,wap  written
*/

#ifndef __INCvxbQorIQBmanh
#define __INCvxbQorIQBmanh

/* These registers are located in CCSBAR space at offset 0x31A000. */

/* Software portal depletion entry thresholds */

#define BMAN_POOL0_SWDET        0x00000000
#define BMAN_POOL63_SWDET       0x000000FC

/* Hardware portal depletion entry thresholds */

#define BMAN_POOL0_HWDET        0x00000100
#define BMAN_POOL63_HWDET       0x000001FC

/* Software portal depletion exit thresholds */

#define BMAN_POOL0_SWDXT        0x00000200
#define BMAN_POOL63_SWDXT       0x000002FC

/* Hardware portal depletion entry thresholds */

#define BMAN_POOL0_HWDXT        0x00000300
#define BMAN_POOL63_HWDXT       0x000003FC

/* Software portal depletion counts */

#define BMAN_POOL0_SWCNT        0x00000400
#define BMAN_POOL63_SWCNT       0x000004FC

/* Hardware portal depletion counts */

#define BMAN_POOL0_HWCNT        0x00000500
#define BMAN_POOL63_HWCNT       0x000006FC

/* Buffer count snapshots */

#define BMAN_POOL0_CONTENT      0x00000600
#define BMAN_POOL63_CONTENT     0x000006FC

/* Free pool count */

#define BMAN_FBPR_FPC           0x00000800
#define BMAN_FBPR_FP_LWIT       0x00000804

/* Performance monitor config registers */

#define BMAN_CMD_PM0_CFG        0x00000900
#define BMAN_CMD_PM7_CFG        0x0000091C
#define BMAN_FL_PM0_CFG         0x00000920
#define BMAN_FL_PM7_CFG         0x0000093C

/* Error capture registers */

#define BMAN_ECSR               0x00000A00
#define BMAN_ECIR               0x00000A04
#define BMAN_EADR               0x00000A08
#define BMAN_EDATA0             0x00000A10
#define BMAN_EDATA7             0x00000A2C
#define BMAN_SBET               0x00000A30
#define BMAN_SBEC0              0x00000A80
#define BMAN_SBEC1              0x00000A84

/* ID/rev registers */

#define BMAN_IP_REV1            0x00000BF8
#define BMAN_IP_REV2            0x00000BFC

#define BMAN_IP_ID              0xFFFF0000 /* IP indentifier */
#define BMAN_IP_MJ              0x0000FF00 /* Major revision */
#define BMAN_IP_MN              0x000000FF /* Minor revision */

#define BMAN_ID(x)              (((x) & BMAN_IP_ID) >> 16)
#define BMAN_MJ(x)              (((x) & BMAN_IP_MJ) >> 8)
#define BMAN_MN(x)              ((x) & BMAN_IP_MN)

#define BMAN_REVISION1          0x01
#define BMAN_REVISION2          0x02

/* CoreNet initiator memory window config registers */

#define BMAN_MW_FBPR_BARHI      0x00000C00
#define BMAN_MW_FBPR_BARLO      0x00000C04
#define BMAN_MW_FBPR_ATTR       0x00000C10
#define BMAN_MW_SRCIDR          0x00000D04 /* Bman source ID */
#define BMAN_MW_LIODNR          0x00000D08 /* Logical I/O device # */

/* Data structure attribute register */

#define BMAN_MW_ATTR_SIZE       0x000000FF /* Window size */
#define BMAN_MW_ATTR_HIPRIO     0x40000000 /* Transaction priority */

#define BMAN_MW_SIZE_4KB        0x0000000B
#define BMAN_MW_SIZE_8KB        0x0000000C
#define BMAN_MW_SIZE_16KB       0x0000000D
#define BMAN_MW_SIZE_32KB       0x0000000E
#define BMAN_MW_SIZE_64KB       0x0000000F
#define BMAN_MW_SIZE_128KB      0x00000010
#define BMAN_MW_SIZE_256KB      0x00000011
#define BMAN_MW_SIZE_512KB      0x00000012
#define BMAN_MW_SIZE_1MB        0x00000013
#define BMAN_MW_SIZE_2MB        0x00000014
#define BMAN_MW_SIZE_4MB        0x00000015
#define BMAN_MW_SIZE_8MB        0x00000016
#define BMAN_MW_SIZE_16MB       0x00000017
#define BMAN_MW_SIZE_32MB       0x00000018
#define BMAN_MW_SIZE_64MB       0x00000019
#define BMAN_MW_SIZE_128MB      0x0000001A
#define BMAN_MW_SIZE_256MB      0x0000001B
#define BMAN_MW_SIZE_512MB      0x0000001C
#define BMAN_MW_SIZE_1GB        0x0000001D

/* Error Interrupt registers */

#define BMAN_ERR_ISR            0x00000E00
#define BMAN_ERR_IER            0x00000E04
#define BMAN_ERR_ISDR           0x00000E08
#define BMAN_ERR_IIR            0x00000E0C

#define QORIQ_BMAN_NAME         "QorIQBman"

/* Default private region size of 1MB */

#define BMAN_FBPR_DEFAULT_SIZE   0x100000

typedef struct bman_drv_ctrl
    {
    VXB_DEV_ID          bmanDev;
    void *              bmanBar;
    VXB_RESOURCE *      pRes;
    void *              bmanHandle;
    SEM_ID              bmanSem;
    void *              bmanFbprMem;
    UINT32              bmanFbprSize;
    void *              bmanLawBase;
    UINT32              bmanLawSize;
    UINT32              bmanRev;
    int                 bmanPortalCnt;
    BPORTAL             bmanPortal[BPORTAL_PORTAL_CNT];
    } BMAN_DRV_CTRL;

#define BMAN_BAR(p)             ((BMAN_DRV_CTRL *)(p))->bmanBar
#define BMAN_HANDLE(p)          ((BMAN_DRV_CTRL *)(p))->bmanHandle

#define CSR_READ_4(pDev, addr)                                  \
        vxbRead32 (BMAN_HANDLE(pDev),                           \
        (UINT32 *)((char *)BMAN_BAR(pDev) + addr))

#define CSR_WRITE_4(pDev, addr, data)                           \
        vxbWrite32 (BMAN_HANDLE(pDev),                          \
        (UINT32 *)((char *)BMAN_BAR(pDev) + addr), (UINT32)data)

#define BMAN_READ(pDev, idx, addr)              \
        CSR_READ_4(pDev, addr + (idx * QORIQ_BMAN_SIZE))

#define BMAN_WRITE(pDev, idx, addr, data)       \
        CSR_WRITE_4(pDev, addr + (idx * QORIQ_BMAN_SIZE), data)
    
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbQorIQBmanh */
