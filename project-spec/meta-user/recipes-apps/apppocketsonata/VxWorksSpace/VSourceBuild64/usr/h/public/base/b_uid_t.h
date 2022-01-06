/* b_uid_t.h - base type uid_t definition header */

/*
 * Copyright (c) 2006 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
*/

/*
modification history
--------------------
01a,16feb06,pes  Created.
*/

#ifndef __INCb_uid_th
#define __INCb_uid_th

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _DEFINED_uid_t
#define _DEFINED_uid_t
/* POSIX requires uid_t to be an int type, signedness not specified */
typedef unsigned short  uid_t;
#endif /* _DEFINED_uid_t */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_uid_th */


