/* aimMmuBaseLib.h - Base of the MMU Architecture Independent Manager */

/* Copyright 1984-2004, 2010, 2014-2015 Wind River Systems, Inc.
*
* The right to copy, distribute, modify or otherwise make use 
* of this software may be licensed only pursuant to the terms 
* of an applicable Wind River license agreement. 
*/

/*
modification history
--------------------
10mar14,ymz  fixed flexelint warning
20nov14,ylu  LP64 adaptation to support PPC64.(F2518)
14mar14,x_z  Moved MMU_ARCH_LIB_ATTRS to PPC ARCH. (US18830)
29apr10,pad  Moved extern C statement after include statements.
31aug04,dtr  Add new attribute available for tlb locking.
07jun04,sru  written
*/

#ifndef __INCaimMmuBaseLibh
#define __INCaimMmuBaseLibh

#include <vxWorks.h>

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

/* externs */

IMPORT STATUS aimMmuBaseLibInit ();
IMPORT size_t aimMmuBlockSize;
IMPORT size_t aimMmuPageSize;

#ifdef __cplusplus
}
#endif

#endif /* __INCaimMmuBaseLibh */
