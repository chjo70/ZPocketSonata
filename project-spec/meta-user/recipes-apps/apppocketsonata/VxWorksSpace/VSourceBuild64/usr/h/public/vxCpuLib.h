/* vxCpuLib.h - runtime identification header file */

/* 
 * Copyright (c) 2007 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 


/*
modification history
--------------------
01a,23aug07,kk  written
*/

#ifndef __INCvxCpuLibh
#define __INCvxCpuLibh

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

extern cpuset_t 	vxCpuEnabledGet (void);
extern unsigned int 	vxCpuConfiguredGet (void);

#ifdef __cplusplus
}
#endif

#endif /* __INCvxCpuLibh */
