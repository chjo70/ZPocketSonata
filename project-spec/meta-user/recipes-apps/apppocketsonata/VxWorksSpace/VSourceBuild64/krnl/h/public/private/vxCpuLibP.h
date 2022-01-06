/* vxCpuLibP.h - private header for runtime Identification */

/* 
 * Copyright (c) 2006-2010, 2015 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
24jun15,pmr  remove _WRS_PORTABLE_vxCpuLibInit (V7SP-214)
13feb15,ymz  added missing prototype (flexelint fix)
08jul10,cww  Removed vxCpuSetConfigured
29apr10,pad  Moved extern C statement after include statements.
02feb09,cww  Add dynamic CPU reservation
13may08,zl   added private API for CPU reservation.
08aug07,zl   added _WRS_CPUSET_CONFIGURED()
05feb07,pes  Remove 'const' designation from vxCpuConfigured definition.
26oct06,lei  Created based on vxCpuLib.h
*/

#ifndef __INCvxCpuLibPh
#define __INCvxCpuLibPh

#include <cpuset.h>

#ifdef __cplusplus
extern "C" {
#endif

/* extern */

extern cpuset_t vxCpuEnabled; /* set of CPUs enabled */

/* configuration parameter defined in a configlette, usrKernel.c */

extern unsigned int vxCpuConfigured; 
extern cpuset_t     vxCpuSetReserved;

/* macro */

#define _WRS_CPU_ENABLED()		(vxCpuEnabled) 
#define _WRS_CPU_CONFIGURED()		(vxCpuConfigured)
#define _WRS_CPUSET_RESERVED()		(vxCpuSetReserved)

/* private API */

#ifdef _WRS_CONFIG_SMP
extern void vxCpuReservedStringParse (char * pExplicitCpus);
#endif /* _WRS_CONFIG_SMP */

extern void vxCpuLibInit (void);
extern void vxCpuArchLibInit (void);

#ifdef __cplusplus
}
#endif

#endif /* __INCvxCpuLibPh */
