/* b_cpuset_t.h - base type cpuset_t definition header */

/*
 * Copyright (c) 2006. 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
*/

/*
modification history
--------------------
01e,24mar10,cww  Added _ASMLANGUAGE protection
01d,18oct06,mmi  fixed CPUSET_SETALL_BUT_SELF(), and changed CPUSET_ISZERO 
01c,09oct06,mmi  add CPUSET_SETALL(), CPUSET_SETALL_BUT_SELF(),  
		 CPUSET_ATOMICCLR() and CPUSET_ATOMICSET() macros
01b,17jul06,mmi  added CPUSET_XX macros
01a,22jun06,mmi  Created.
*/

#ifndef __INCb_cpuset_th
#define __INCb_cpuset_th

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

#ifndef _DEFINED_cpuset_t
#define _DEFINED_cpuset_t

/* typedefs */

typedef unsigned int             cpuset_t;

#endif /* _DEFINED_cpuset_t */

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_cpuset_th */


