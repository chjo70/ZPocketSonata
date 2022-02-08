/* cpuPwrLibP.h - CPU power library private header file */

/*
 * Copyright (c) 2005, 2007, 2010, 2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01g,28jul11,rbc  WIND00238999 - Add VSB _WRS_CONFIG_PWR_MGMT
01f,26may10,rec  remove framework
01e,29apr10,pad  Moved extern C statement after include statements.
01d,12jul07,mmi  add funcBindP.h
01c,09sep05,mmi  mods for coding standard compliance 
01b,27aug05,mmi  adapt the file for all flavours of IA32 cpu's
01a,27Jul05,mmi  created
*/

#ifndef __INCcpuPwrLibPh
#define __INCcpuPwrLibPh

#include <vxWorks.h>
#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* typedef's */

#ifdef _WRS_ARCH_HAS_CPU_PWR_MGMT
extern volatile VOIDFUNCPTR _func_cpuPwrIdleEnter;
#endif /* _WRS_ARCH_HAS_CPU_PWR_MGMT */

#if (defined _WRS_CONFIG_PWR_MGMT) || (defined _WRS_CONFIG_CPU_PWR_MGMT)
/* cpu power management glue to the wind kernel library */

extern VOIDFUNCPTR _func_cpuPwrIntExitHook;
extern VOIDFUNCPTR _func_cpuPwrIntEnterHook;
extern VOIDFUNCPTR _func_cpuPwrPriorityRaise;
extern VOIDFUNCPTR _func_cpuPwrLoadContext;
#endif /* (defined _WRS_CONFIG_PWR_MGMT) || (defined _WRS_CONFIG_CPU_PWR_MGMT) */

#ifdef __cplusplus
}
#endif

#endif /* __INCcpuPwrLibP */
