/* fslLs102x.h - Freescale LS102X processor support header */

/*
 * Copyright (c) 2014-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
14dec16,y_f  replaced fslLs102xCpuAvail() by vxFdtCpuAvail (V7PRO-3433)
07sep15,yya  added warm reboot support. (US63670)
09oct14,sye  Created. (US46489)
*/

#ifndef __INCfslLs102xh
#define __INCfslLs102xh

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

/* SVR bit defines */

#define LS_SVR_ID(svr)          (((svr) >> 8) & 0xFFF7FF)       /* ID */
#define LS_SVR_SEC(svr)         ((svr) & 0x80000)               /* SEC */
#define LS_SVR_MAJ(svr)         (((svr) >> 4) & 0xF)            /* major rev */
#define LS_SVR_MIN(svr)         ((svr) & 0xF)                   /* minor rev */

/* SOC Revision defines */

#define LS_SVR_SOC_LS1020A      (0x870010)
#define LS_SVR_SOC_LS1021A      (0x870011)
#define LS_SVR_SOC_LS1022A      (0x870012)

#define LS102X_READ_32(reg)             (*((volatile UINT32 *)(reg)))
#define LS102X_WRITE_32(reg, data)      (*((volatile UINT32 *)(reg)) = (data))
#define LS102X_SETBIT_32(addr, val)  \
                        LS102X_WRITE_32(addr, LS102X_READ_32(addr) | (val))
#define LS102X_CLRBIT_32(addr, val)  \
                        LS102X_WRITE_32(addr, LS102X_READ_32(addr) & ~(val))
#define LS102X_READ_16(reg)             (*((volatile UINT16 *)(reg)))
#define LS102X_WRITE_16(reg, data)      (*((volatile UINT16 *)(reg)) = (data))
#define LS102X_READ_8(reg)              (*((volatile UINT8 *)(reg)))
#define LS102X_WRITE_8(reg, data)       (*((volatile UINT8 *)(reg)) = (data))

#define LS102X_DCFG_DRIVER_NAME         "fsl,ls102x-dcfg"
#define LS102X_SCFG_DRIVER_NAME         "fsl,ls102x-scfg"

/* function declarations */

IMPORT  BOOL    fslLs102xProbe (char * compat);
IMPORT  void    fslLs102xInit (void);
IMPORT  void    fslLs102xEarlyInit (void);
IMPORT  char *  fslLs102xModel (void);
IMPORT  void    fslLs102xUsDelay (int us);
IMPORT  void    fslLs102xReset (int startType);
#ifdef _WRS_CONFIG_SMP
IMPORT  STATUS  fslLs102xCpuEnable (UINT32 cpuId, WIND_CPU_STATE * cpuState);

/* define this macro for compatible with old BSP */

#define fslLs102xCpuAvail   vxFdtCpuAvail
#endif /*_WRS_CONFIG_SMP*/

IMPORT BOOL fslLs102xProbe (char * compat);

#ifdef __cplusplus
}
#endif

#endif /* __INCfslLs102xh */
