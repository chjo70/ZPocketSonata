/* cpuLib.h - cpu library header file */

/*
 * Copyright (c) 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
* 10dec14,w_x  Fix cpuSecStart() for LP64 SMP support (F2518)
* 19dec13,ylu  Added support for PPC E500V2 SMP.
* 19jul13,x_z  created.
*/

/* typdefs */

/* CPU utility function structure */

typedef struct vxCpuFuncs
    {
    STATUS  (*cpuStart) (void);
    STATUS  (*cpuShutdown) (void);
    void    (*cpuShow) (void);
#ifdef _WRS_CONFIG_SMP    
    void    (*cpuSecStart) (ULONG funcStart);
#endif /* _WRS_CONFIG_SMP */
    } VX_CPU_FUNCS;

/* globals */

/* initialization routine */

STATUS cpuLibInit (VX_CPU_FUNCS * pVxCpuFuncs);

/* utility routines */

STATUS cpuStart (void);
STATUS cpuShutdown (void);
void cpuShow (void);

