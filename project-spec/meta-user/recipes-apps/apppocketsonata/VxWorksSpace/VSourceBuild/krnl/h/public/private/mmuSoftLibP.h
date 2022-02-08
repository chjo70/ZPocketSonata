/* mmuSoftLibP.h - private header for software MMU simulation library */

/* 
 * Copyright (c) 2004, 2009 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01b,04may09,zl   updated for LP64 build
01a,08apr04,zl   written.
*/

#ifndef __INCmmuSoftLibPh
#define __INCmmuSoftLibPh

#ifdef __cplusplus
extern "C" {
#endif


STATUS  mmuSoftLibInit (size_t mmuPageSize, VIRT_ADDR startAddr, 
			VIRT_ADDR kernelTop);

#ifdef __cplusplus
}
#endif

#endif /* __INCvmLibPh */
