/* b_time_t.h - base type time_t definition header */

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
01b,14mar06,mil  Moved kernel definition into this file, preserved unsigned.
01a,16feb06,pes  Created.
*/

#ifndef __INCb_time_th
#define __INCb_time_th

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WRS_KERNEL

#ifndef _TIME_T
#define _TIME_T
typedef unsigned long time_t;
#endif  /* _TIME_T */

#else  /* _WRS_KERNEL */

#if !defined(_TIME_T) && !defined(__time_t_defined) \
	&& !defined(_BSD_TIME_T_DEFINED_)
#define _TIME_T
#define __time_t_defined
#define _BSD_TIME_T_DEFINED_
#define _STD_USING_TIME_T
typedef long time_t;
#endif /* !defined(_TIME_T) etc. */

#endif  /* _WRS_KERNEL */


#ifdef __cplusplus
}
#endif

#endif /* __INCb_time_th */
