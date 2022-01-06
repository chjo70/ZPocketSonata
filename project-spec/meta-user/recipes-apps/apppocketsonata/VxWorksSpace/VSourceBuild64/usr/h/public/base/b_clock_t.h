/* b_clock_t.h - base type clock_t definition header */

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

#ifndef __INCb_clock_th
#define __INCb_clock_th

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_CLOCK_T) && !defined(__clock_t_defined) \
        && !defined(_BSD_CLOCK_T_DEFINED_)
#define _CLOCK_T
#define __clock_t_defined
#define _BSD_CLOCK_T_DEFINED_
#define _STD_USING_CLOCK_T
typedef long clock_t;
#endif /* !defined(_CLOCK_T) etc. */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_clock_th */


