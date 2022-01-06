/* b_clockid_t.h - base type clockid_t definition header */

/*
 * Copyright (c) 2006, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
03mar14,h_k  moved the CLOCK_xxx and TIMER_xxx macros to clockLib.h.
22jan14,to   kernel support (US15931)
16feb06,pes  Created.
*/

#ifndef __INCb_clockid_th
#define __INCb_clockid_th

#ifdef _WRS_KERNEL
#include <vsbConfig.h>
#endif /* _WRS_KERNEL */

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_CLOCKID_T) && !defined(__clockid_t_defined)
  #define _CLOCKID_T
  #define __clockid_t_defined
  #define _STD_USING_CLOCKID_T

  #ifdef _WRS_KERNEL
    #ifdef _WRS_CONFIG_LP64
typedef unsigned long clockid_t;
    #else
typedef unsigned int clockid_t;
    #endif /* _WRS_CONFIG_LP64 */
  #else /* _WRS_KERNEL */
typedef int clockid_t;
  #endif /* _WRS_KERNEL */

#endif /* !defined(_CLOCKID_T) && !defined(__clockid_t_defined) */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_clockid_th */
