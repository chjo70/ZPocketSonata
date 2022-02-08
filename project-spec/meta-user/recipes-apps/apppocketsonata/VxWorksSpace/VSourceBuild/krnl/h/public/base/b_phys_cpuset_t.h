/* b_phys_cpuset_t.h - base type phys_cpuset_t definition header */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
*/

/*
modification history
--------------------
01b,30mar10,cww  Added _ASMLANGUAGE protection
01a,25jan10,d_c  Created.
*/

#ifndef __INCb_phys_cpuset_th
#define __INCb_phys_cpuset_th

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

#ifndef _DEFINED_phys_cpuset_t
#define _DEFINED_phys_cpuset_t

/* typedefs */

/* physical CPU set */

typedef unsigned int             phys_cpuset_t;

#endif /* _DEFINED_phys_cpuset_t */

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_phys_cpuset_th */


