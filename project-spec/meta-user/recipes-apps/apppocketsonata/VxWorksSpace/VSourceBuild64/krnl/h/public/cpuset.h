/* cpuset.h - cpuset_t and phys_cpuset_t access macros */

/*
 * Copyright (c) 2006-2007, 2010, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01h,15feb12,zl   use paranthesis around macro arguments (WIND00332849).
                 moved phys_cpuset access macros from cpusetCommon.h
01g,30mar10,cww  Added _ASMLANGUAGE protection
01f,25jan10,d_c  SMP M-N updates: Add access macros for phys_cpuset_t. Add
                 externs for cpuset_t <-> phys_cpuset_t conversion functions.
01e,25dec07,l_z  change cpuset computation so that
                 it works when vxCpuConfigured == 32. Needed especially
                 for Raza. 
01d,17oct07,kk   add comment to indicate updates here should also be done in
                 cpuset.c
01c,13jun07,jmg  Created cpusetCommon.h and moved most of the file there.
01b,01mar07,  remove CPUSET_ARG() macro
01a,25oct06,  created.
*/

#ifndef __INCcpuseth
#define __INCcpuseth

#include <cpusetCommon.h>
#include <vxCpuLib.h>
#include <base/b_phys_cpuset_t.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

/* defines */

/* 
 * WARNING: Any updates made here should also be
 * reviewed for doc updates in the src/os/cpuset.c file.
 */

/* 
 * set of macros to manipulate the cpuset_t type; the ones defined here are
 * for kernel space only. There are additional macros in cpusetCommon.h;
 * those are available for both kernel space and RTP space.
 */

#define CPUSET_SETALL(cpuset)						\
	((cpuset) = ~(0xFFFFFFFE << (vxCpuConfiguredGet()-1)))
#define CPUSET_SETALL_BUT_SELF(cpuset)					\
	((cpuset) = ~((0xFFFFFFFE << (vxCpuConfiguredGet()-1)) |	\
		      (1 << vxCpuIndexGet())))

/* set of macros to manipulate the phys_cpuset_t type */

#define PHYS_CPUSET_SET(phys_cpuset, n)     ((phys_cpuset) |= (1 << (n)))
#define PHYS_CPUSET_ISSET(phys_cpuset, n)   ((phys_cpuset) & (1 << (n)))
#define PHYS_CPUSET_CLR(phys_cpuset, n)     ((phys_cpuset) &= ~(1 << (n)))
#define PHYS_CPUSET_ZERO(phys_cpuset)       ((phys_cpuset) = 0)
#define PHYS_CPUSET_ISZERO(phys_cpuset)	    ((phys_cpuset) == 0)

#define PHYS_CPUSET_FIRST_SET(phys_cpuset)				\
	((int)(phys_cpuset) & (int)-(phys_cpuset))
#define PHYS_CPUSET_FIRST_INDEX(phys_cpuset)				\
	(FFS_LSB (phys_cpuset) - 1)
#define PHYS_CPUSET_LAST_INDEX(phys_cpuset)				\
	(FFS_MSB (phys_cpuset) - 1)
#define PHYS_CPUSET_ADD(phys_cpusetAugend, phys_cpusetAddend)		\
        ((phys_cpusetAugend) |= (phys_cpusetAddend))
#define PHYS_CPUSET_SUB(phys_cpusetMinuend,phys_cpusetSubtrahend)	\
	((phys_cpusetMinuend) &= ~(phys_cpusetSubtrahend))


/* function declarations */

extern void cpusetLogicalToPhys (cpuset_t, phys_cpuset_t *);
extern STATUS cpusetPhysToLogical (phys_cpuset_t, cpuset_t *);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCcpuseth */
