/* vxCpuLib.h - runtime identification header file */

/* 
 * Copyright (c) 2006, 2009-2010 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 


/*
modification history
--------------------
01e,30mar10,cww  Added _ASMLANGUAGE protection
01d,25jan10,d_c  SMP M-N updates: Add CPU_LOGICAL_TO_PHYS and
                 CPU_PHYS_TO_LOGICAL macros. Add cpuid_t type.
		 Add extern of vxBaseCpuPhysIndex.
01c,02feb09,cww  Add dynamic CPU reservation API
01b,25oct06,lei  moved macros to private/vxCpuLibP.h
01a,05jul06,mmi  Created based on ../i86/vxCpuLib.h
*/

#ifndef __INCvxCpuLibh
#define __INCvxCpuLibh

#include <vwModNum.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

/* defines */

#define S_vxCpuLib_INVALID_ARGUMENT	(M_vxCpuLib | 1)
#define S_vxCpuLib_NO_CPU_AVAILABLE	(M_vxCpuLib | 2)

#define CPU_LOGICAL_TO_PHYS(logicalIndex) (logicalIndex + vxBaseCpuPhysIndex)
#define CPU_PHYS_TO_LOGICAL(physIndex)    (physIndex - vxBaseCpuPhysIndex)

/* typedefs */

typedef unsigned int cpuid_t;	/* hardware CPU identification */

/* globals */

/* Physical CPU index corresponding to logical CPU index 0 */

extern unsigned int vxBaseCpuPhysIndex;

/* function declarations */

/* The following functions are generally implemented in architecture
 * code.  In some cases they may be overridden and implemented in the
 * BSP. vxCpuLibInit() is also implemented in architecture code, but
 * is prototyped in the INCLUDE_VXCPULIB component. INCLUDE_VXCPULIB
 * is defined in target/config/comps/vxWorks/00vxWorks.cdf.
 */

extern cpuid_t vxCpuIdGet (void);
extern unsigned int vxCpuIndexGet (void);
extern unsigned int vxCpuPhysIndexGet (void);
extern unsigned int vxCpuIdToPhysIndex (cpuid_t cpuId);
extern cpuid_t vxCpuPhysIndexToId (unsigned int physCpuIndex);

/* implemented in vxCpuLib.c */

extern cpuset_t     vxCpuEnabledGet (void);
extern unsigned int vxCpuConfiguredGet (void);
extern STATUS       vxCpuReservedGet (cpuset_t*);
extern STATUS	    vxCpuReserve (cpuset_t, cpuset_t*);
extern STATUS	    vxCpuUnreserve (cpuset_t);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxCpuLibh */
