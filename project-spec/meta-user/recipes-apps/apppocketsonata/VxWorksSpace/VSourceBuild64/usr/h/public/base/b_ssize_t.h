/* b_ssize_t.h - base type ssize_t definition header */

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

#ifndef __INCb_ssize_th
#define __INCb_ssize_th

#include <vsbConfig.h> 

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _DEFINED_ssize_t
#define _DEFINED_ssize_t
#ifdef _WRS_CONFIG_LP64
typedef long ssize_t;
#else
typedef int ssize_t;
#endif
#endif /* _DEFINED_ssize_t */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_ssize_th */
