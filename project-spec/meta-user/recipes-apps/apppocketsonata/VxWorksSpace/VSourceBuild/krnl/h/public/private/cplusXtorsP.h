/* private/cplusXtorsP.h - VxWorks loader shared C++ Xtors definitions */

/* 
 * Copyright (c) 2005 Wind River Systems, Inc.
 * 
 * The right to copy, distribute, modify, or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01b,13sep05,bpn  Remove cplusXtorGet() prototype.
01a,05sep05,v_r  Written. Moved C++ strategies and Xtors routines definitions
		 from cplusLibP.h
*/

#ifndef __INCcplusXtorsPh
#define __INCcplusXtorsPh

#ifdef HOST
#include <host.h>
#else
#include <vxWorks.h>
#endif

/* Type declarations */

typedef enum
    {
    MANUAL      = 0,
    AUTOMATIC   = 1
    } CPLUS_XTOR_STRATEGIES;

/* Function declarations, C linkage */

#ifdef __cplusplus
extern "C" {
#endif

extern void cplusCallCtors (VOIDFUNCPTR * ctors);
extern void cplusCallDtors (VOIDFUNCPTR * dtors);

#ifdef __cplusplus
}
#endif

#endif /* __INCcplusXtorsPh */
