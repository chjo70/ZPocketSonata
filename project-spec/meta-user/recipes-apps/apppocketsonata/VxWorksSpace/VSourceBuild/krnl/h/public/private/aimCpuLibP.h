/* aimCpuLib.h - cpu library header file */

/*
 * Copyright (c) 2013-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
10dec14,w_x  Fix cpuSmpLoop() for LP64 SMP support (F2518)
10may14,ylu  removed the PPCE6500 dependency for cpuSmpLoop.(US34958)
21apr14,ylu  added support for PPC E6500 SMP.(US34480)
20dec13,cww  clean up symbol names
12dec13,ylu  added support for SMP feature.
19jul13,x_z  created.
*/

/* typdefs */

/* CPU utility function structure */

typedef struct aimCpuFuncs
    {
    STATUS  (*cpuStart) (void);
    STATUS  (*cpuShutdown) (void);
    void    (*cpuShow) (void);
#ifdef _WRS_CONFIG_SMP
    void    (*cpuSmpLoop) (ULONG funcStart, UINT32 physCpuIndex);
#endif /* _WRS_CONFIG_SMP */
    } AIM_CPU_FUNCS;

/* globals */

/* initialization routine */

STATUS	aimCpuLibInit (AIM_CPU_FUNCS * pVxCpuFuncs);

/* utility routines */

STATUS	aimCpuStart (void);
STATUS	aimCpuShutdown (void);
void	aimCpuShow (void);

