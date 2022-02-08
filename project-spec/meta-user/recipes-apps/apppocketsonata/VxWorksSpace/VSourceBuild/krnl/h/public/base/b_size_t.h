/* b_size_t.h - base type size_t definition header */

/*
 * Copyright (c) 2006, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
*/

/*
modification history
--------------------
01c,23aug10,pad  Added inclusion of vsbConfig.h
01b,30jan09,pcs  Updated to support LP64 data model.
01a,16feb06,pes  Created.
*/

#ifndef __INCb_size_th
#define __INCb_size_th

#include <vsbConfig.h> 

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _SIZE_T
#define _SIZE_T
#ifdef _WRS_CONFIG_LP64
typedef unsigned long size_t;
#else
typedef unsigned int size_t;
#endif
#endif /* _SIZE_T */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_size_th */
