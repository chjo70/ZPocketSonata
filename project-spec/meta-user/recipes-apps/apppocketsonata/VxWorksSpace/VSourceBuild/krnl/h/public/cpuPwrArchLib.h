/* cpuPwrArchLib.h - CPU dynamic power management */

/*
 * Copyright (c) 2010, 2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01f,06jul11,rdl  move common APIs to the common header file
01e,05jul11,scm  WIND00255355, arch header file name change...
01d,01jun11,scm  WIND00255355. point to IA arch specific header...
01c,16sep10,rec  add ARM support
01b,26may10,rec  add CPU_PSTATE_MAX
01a,25feb10,rec  created

*/
#ifndef __INCcpuPwrArchLibh
#define __INCcpuPwrArchLibh

#ifndef _ASMLANGUAGE

#ifdef __cplusplus
extern "C" {
#endif
 
#define CPU_PSTATE_MAX 16   /* Intel SDRM par 14.3.4 */

/* Architecture independent API definitions */

IMPORT STATUS cpuPwrArchLibInit (void);
IMPORT STATUS cpuPwrArchEnable (void);
IMPORT STATUS cpuPwrArchDisable (void);
IMPORT UINT32 cpuPwrArchPStateSet (UINT32 cpuPState);
IMPORT UINT32 cpuPwrArchPStateGet (void);
IMPORT void   vxC1StateSet (void);

#if (CPU_FAMILY == I80X86)

#include <arch/i86/cpuPwrArchI86Lib.h>

#endif /* CPU_FAMILY==I80X86 */


#if (CPU_FAMILY == ARM)
/* 
 * Some architectures don't have a standardized method for setting 
 * CPU P-States.  This structure provides a set of function pointers that can
 * be filled by the BSP during initialization to be used by the image at 
 * runtime.
 */

typedef struct archcpuPwrFuncStruct 
    {
    STATUS   (*_func_cpuPwrArchLibInit) (void);
    STATUS   (*_func_cpuPwrArchEnable) (void);
    STATUS   (*_func_cpuPwrArchDisable) (void);
    UINT32   (*_func_cpuPwrArchPStateSet) (UINT32 cpuPState);
    UINT32   (*_func_cpuPwrArchPStateGet) (void);
    } ARCH_CPU_PWR_FUNC;

IMPORT ARCH_CPU_PWR_FUNC cpuPwrArchFunc;

#endif /* CPU_FAMILY == ARM */

#ifdef __cplusplus
}
#endif

#endif /* _ASMLANGUAGE */

#endif /* __INCcpuPwrArchLib */

