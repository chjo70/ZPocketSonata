/* vxPortableArchP.h - PowerPC portable library configuration */

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
01a,14may07,jmg   created
*/

#ifndef __INCvxPortableArchPh
#define __INCvxPortableArchPh

#ifdef __cplusplus
extern "C" {
#endif

/*
 * This file is included from <private/vxPortableP.h>. It may undefine 
 * portable library definitions in order to enable architecture specific
 * implementation of a library or routine.
 */

/* the following can be overridden with PORTABLE */

#ifndef PORTABLE


#endif

/* the following cannot be overridden with PORTABLE */

#undef _WRS_PORTABLE_vxAtomicLib

#ifdef __cplusplus
}
#endif

#endif /* __INCvxPortableArchPh */
