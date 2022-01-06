/* cpusetP.h - private header file for cpuset */

/*
 * Copyright (c) 2008, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01d,29apr10,pad  Moved extern C statement after include statements.
01c,26jan10,d_c  SMP M-N updates: Add phys_cpu_t access macros.
01b,20feb09,cww  Add dynamic CPU reservation support
01a,14may08,zl   created.
*/

#ifndef __INCcpusetPh
#define __INCcpusetPh

#include <cpuset.h>

#ifdef __cplusplus
extern "C" {
#endif

/* A few simple operations on CPU sets */

#define _WRS_CPUSET_COPY(res, set)		((res) = (set))
#define _WRS_CPUSET_INTERSECT(res, s1, s2)	((res) = (s1) & (s2))
#define _WRS_CPUSET_UNION(res, s1, s2)		((res) = (s1) | (s2))
#define _WRS_CPUSET_IS_SUBSET(s1, s2)		((s1 & ~s2) == 0)
#define _WRS_CPUSET_INVERT(s1)			(s1 = ~s1)

/* The same operations on physical CPU sets */

#define _WRS_PHYS_CPUSET_COPY(res, set)		((res) = (set))
#define _WRS_PHYS_CPUSET_INTERSECT(res, s1, s2)	((res) = (s1) & (s2))
#define _WRS_PHYS_CPUSET_UNION(res, s1, s2)	((res) = (s1) | (s2))
#define _WRS_PHYS_CPUSET_IS_SUBSET(s1, s2)	((s1 & ~s2) == 0)
#define _WRS_PHYS_CPUSET_INVERT(s1)		(s1 = ~s1)

/* initialize a global CPU set variable based on the CPU count */

#define _WRS_CPUSET_INIT(cnt)			((2  << ((cnt) - 1)) - 1)

#ifdef __cplusplus
}
#endif

#endif /* __INCcpusetPh */
