/* nxpLayerscape.h - NXP Layerscape processor support header */

/*
 * Copyright (c) 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
06feb17,swu  created (F7615)
*/

#ifndef __INCnxpLayerscapeh
#define __INCnxpLayerscapeh

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Interrupt Sampling Control defines */

#define LS_EXT_IRQ_NUM         (12)
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

#define LS_SVR_SOC_LS1020A      (0x870010)
#define LS_SVR_SOC_LS1021A      (0x870011)
#define LS_SVR_SOC_LS1022A      (0x870012)
#define LS_SVR_SOC_LS1043A      (0x879204)
#define LS_SVR_SOC_LS1046A      (0x870700)

/* QIXIS: 8 bit registers */

#define LS_QIXIS_ID             (0)
#define LS_QIXIS_VER            (1)
#define LS_QIXIS_QVER           (2)
#define LS_QIXIS_MINOR          (4)

#define LS_READ_32(reg)            (*(volatile UINT32 *)(reg))
#define LS_WRITE_32(reg, data)     (*((volatile UINT32 *)(reg)) = (data))
#define LS_SETBIT_32(addr, val)    \
                    LS_WRITE_32 (addr, LS_READ_32(addr) | (val))
#define LS_CLRBIT_32(addr, val)    \
                    LS_WRITE_32 (addr, LS_READ_32(addr) & ~(val))
#define LS_READ_16(reg)            (*(volatile UINT16 *)(reg))
#define LS_WRITE_16(reg, data)     (*((volatile UINT16 *)(reg)) = (data))
#define LS_READ_8(reg)             (*(volatile UINT8 *)(reg))
#define LS_WRITE_8(reg, data)      (*((volatile UINT8 *)(reg)) = (data))

#define NXP_LS_DEFAULT_UART              "fsl,ns16550"
#define NXP_LS_ARM_GIC                   "arm,gic"
#define NXP_LS_DCFG                      "fsl,ls-dcfg"
#define NXP_LS_SCFG                      "fsl,ls-scfg"
#define NXP_LS_CSU                       "fsl,ls-csl"
#define NXP_LS_SYSCNT                    "fsl,ls-syscnt"
#define NXP_LS_CLOCKGEN                  "nxp,ls-clockgen"

/* function declarations */

IMPORT  BOOL    nxpLayerscapeProbe (char * compat);
IMPORT  void    nxpLayerscapeInit (void);
IMPORT  void    nxpLayerscapeEarlyInit (void);
IMPORT  char *  nxpLayerscapeModel (void);
IMPORT  void    nxpLayerscapeUsDelay (int us);
IMPORT  void    nxpLayerscapeReset (int startType);
#ifdef _WRS_CONFIG_SMP
IMPORT  STATUS  nxpLayerscapeCpuEnable (UINT32 cpuId, WIND_CPU_STATE * cpuState);
#endif /*_WRS_CONFIG_SMP*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCnxpLayerscapeh */
