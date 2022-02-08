/* b_clockid_t.h - base type clockid_t definition header */

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

#ifndef __INCb_clockid_th
#define __INCb_clockid_th

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_CLOCKID_T) && !defined(__clockid_t_defined)
#define _CLOCKID_T
#define __clockid_t_defined
#define _STD_USING_CLOCKID_T
typedef int clockid_t;
#endif /* !defined(_CLOCKID_T) && !defined(__clockid_t_defined) */
    
#ifdef __cplusplus
}
#endif

#endif /* __INCb_clockid_th */


