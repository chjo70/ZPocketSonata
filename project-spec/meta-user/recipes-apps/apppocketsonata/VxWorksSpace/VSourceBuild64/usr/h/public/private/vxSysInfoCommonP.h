/* vxSysInfoCommonP.h - private system information library header file */

/*
 * Copyright (c) 2007, 2010, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
10dec14,gls  added vxSysInfoGet() system call prototype
04nov14,pad  Added semRWLibMaxReaders field in _VX_SYS_INFO (US44415).
14oct10,jpb  Defect 233321: Edited macros _VX_IS_SYS_MODE_SMP and
             _VX_IS_SYS_MODE_UP to be true or false on global boolean
             variable that stores the value of vxSysMode member in _VX_SYS_INFO.
23aug07,kk   added vxSysCpuConfigured and vxSysCpuEnabled fields
23apr07,gls  added _VX_SYS_MODE_MASK
11apr07,gls   written.
*/

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef __INCvxSysInfoCommonPh
#define __INCvxSysInfoCommonPh

#include <vxWorks.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

/* typedefs */

/* _VX_SYS_INFO structure definition */

typedef struct __vx_sys_info
    {
    /*
     * WARNING:  
     *
     * The order and size of the members of this structure must not change.
     * Maintaining binary backwards compatibility for RTPs depends on this.
     * All changes must be additional in nature.  Also, the version number
     * must be incremented when this is done.
     */

    UINT32         version;           /* version number - MUST BE FIRST ENTRY */
    UINT32         vxSysMode;         /* system mode bit map */
    UINT32         vxFeatureSet;      /* feature set bit map */
    UINT32	   vxSysCpuConfigured;/* # of CPUs configured in the system */
    cpuset_t       vxSysCpuEnabled;   /* # of CPUs enabled in the system */
    UINT           semRWLibMaxReaders;/* # max concurrent readers R/W sems */
    } _VX_SYS_INFO;

/*
 * This macro defines the value used to statically initialize the __vx_sysInfo
 * global.  The version number must be incremented when the _VX_SYS_INFO
 * structure changes.
 *
 * Note that this defaults to UP mode.
 */

#define _VX_SYS_INFO_VERSION_1 {1, 0, 0}

#endif /* _ASMLANGUAGE */

/* vxSysMode bit definitions */

#define _VX_SYS_MODE_UP      0x0001
#define _VX_SYS_MODE_SMP     0x0002

extern BOOL vxSysModeSmp;

/* vxFeatureSet bit definitions */

#define _VX_SYS_ATOMIC_INSTR 0x0001

#if !defined(_WRS_KERNEL)
extern STATUS vxSysInfoGet (_VX_SYS_INFO * pVxSysInfo);

extern _VX_SYS_INFO __vx_sysInfo;

#define _VX_SYS_VERSION       __vx_sysInfo.version

#define _VX_IS_SYS_MODE_SMP (vxSysModeSmp)
#define _VX_IS_SYS_MODE_UP  (!vxSysModeSmp)

#define _VX_SYS_HAS_ATOMIC_INSTR  (__vx_sysInfo.vxFeatureSet &                 \
                                   _VX_SYS_ATOMIC_INSTR)

#define _VX_SYS_CPU_CONFIGURED (__vx_sysInfo.vxSysCpuConfigured)
#define _VX_SYS_CPU_ENABLED    (__vx_sysInfo.vxSysCpuEnabled)
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCvxSysInfoCommonPh */
