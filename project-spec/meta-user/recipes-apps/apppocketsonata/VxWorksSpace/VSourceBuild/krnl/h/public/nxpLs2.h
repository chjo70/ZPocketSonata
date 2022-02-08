/* nxpLs2.h - NXP LS2 processor support header */

/*
 * Copyright (c) 2015, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
09jan17,wch  added ISC defines (F6376)
20aug15,sye  created. (US64410)
*/

#ifndef __INCnxpLs2h
#define __INCnxpLs2h

#ifdef __cplusplus
extern "C" {
#endif

/* Handy sizes */

#define SZ_1K                   (0x00000400)
#define SZ_4K                   (0x00001000)
#define SZ_8K                   (0x00002000)
#define SZ_16K                  (0x00004000)
#define SZ_32K                  (0x00008000)
#define SZ_64K                  (0x00010000)
#define SZ_128K                 (0x00020000)
#define SZ_256K                 (0x00040000)
#define SZ_512K                 (0x00080000)
#define SZ_1M                   (0x00100000)
#define SZ_2M                   (0x00200000)
#define SZ_4M                   (0x00400000)
#define SZ_8M                   (0x00800000)
#define SZ_16M                  (0x01000000)
#define SZ_32M                  (0x02000000)
#define SZ_64M                  (0x04000000)
#define SZ_128M                 (0x08000000)
#define SZ_256M                 (0x10000000)
#define SZ_512M                 (0x20000000)
#define SZ_1G                   (0x40000000)
#define SZ_2G                   (0x80000000)
#define SCTLR_BE                (0x02000000)

/* Interrupt Sampling Control defines */

#define LS2_EXT_IRQ_NUM         (12)
#define ISC_IRQCR_OFFSET        (0x14)
#define ISC_IRQCR_IRQ(x)        (0x1 << x)

/* SVR bit defines */

#define LS_SVR_ID(svr)          (((svr) >> 8) & 0xFFFFFE)       /* ID */
#define LS_SVR_SEC(svr)         ((svr) & 0x10000)               /* SEC */
#define LS_SVR_MAJ(svr)         (((svr) >> 4) & 0xF)            /* major rev */
#define LS_SVR_MIN(svr)         ((svr) & 0xF)                   /* minor rev */

/* DCFG */

#define DCFG_CCSR_SVR           (0xa4)

/* SOC Revision defines */

#define LS_SVR_SOC_LS2045       (0x870120)
#define LS_SVR_SOC_LS2080       (0x870110)
#define LS_SVR_SOC_LS2085       (0x870100)

/* QIXIS: 8 bit registers */

#define LS_QIXIS_ID             (0)
#define LS_QIXIS_VER            (1)
#define LS_QIXIS_QVER           (2)
#define LS_QIXIS_MINOR          (4)

#define LS2_READ_32(reg)            (*(volatile UINT32 *)(reg))
#define LS2_WRITE_32(reg, data)     (*((volatile UINT32 *)(reg)) = (data))
#define LS2_SETBIT_32(addr, val)    \
                    LS2_WRITE_32 (addr, LS2_READ_32(addr) | (val))
#define LS2_CLRBIT_32(addr, val)    \
                    LS2_WRITE_32 (addr, LS2_READ_32(addr) & ~(val))
#define LS2_READ_16(reg)            (*(volatile UINT16 *)(reg))
#define LS2_WRITE_16(reg, data)     (*((volatile UINT16 *)(reg)) = (data))
#define LS2_READ_8(reg)             (*(volatile UINT8 *)(reg))
#define LS2_WRITE_8(reg, data)      (*((volatile UINT8 *)(reg)) = (data))

/* function declarations */

IMPORT  BOOL    nxpLs2Probe (char * compat);
IMPORT  void    nxpLs2Init (void);
IMPORT  void    nxpLs2EarlyInit (void);
IMPORT  char *  nxpLs2Model (void);
IMPORT  void    nxpLs2UsDelay (int us);
IMPORT  void    nxpLs2Reset (int startType);
#ifdef _WRS_CONFIG_SMP
IMPORT  STATUS  nxpLs2CpuEnable (UINT32 cpuId, WIND_CPU_STATE * cpuState);
IMPORT  UINT32  nxpLs2CpuAvail (void);
#endif /*_WRS_CONFIG_SMP*/

#ifdef __cplusplus
}
#endif

#endif /* __INCnxpLs2h */
