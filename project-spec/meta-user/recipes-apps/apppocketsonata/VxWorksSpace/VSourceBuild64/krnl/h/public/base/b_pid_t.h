/* b_pid_t.h - base type pid_t definition header */

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
01d,23aug10,pad  Added inclusion of vsbConfig.h
01c,23dec09,jpb  Updated for LP64 adaptation.
01b,23feb06,pes  Consolidated pid_t typedef to use 'int' type. (Some
                 typedefs were using unsigned short. POSIX requirement.)
01a,16feb06,pes  Created.
*/

#ifndef __INCb_pid_th
#define __INCb_pid_th

#include <vsbConfig.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _DEFINED_pid_t
#define _DEFINED_pid_t
#if (defined _WRS_KERNEL) && (defined _WRS_CONFIG_LP64)
typedef long pid_t;
#else
typedef int pid_t;
#endif /* _WRS_KERNEL && _WRS_CONFIG_LP64 */
#endif /* _DEFINED_pid_t */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_pid_th */
