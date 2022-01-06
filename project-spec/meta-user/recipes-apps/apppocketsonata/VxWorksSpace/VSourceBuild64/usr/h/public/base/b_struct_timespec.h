/* b_struct_timespec.h - base type struct timespec definition header */

/*
 * Copyright (c) 2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
*/

/*
modification history
--------------------
01d,28apr10,pad  Moved extern C statement after include statements.
01c,08aug06,pad  Added comments regarding _Timespec structure.
01b,15jun06,jln  added _TIMESPEC_DEFINED checking  
01a,16feb06,pes  Created.
*/

#ifndef __INCb_struct_timespech
#define __INCb_struct_timespech

#include <base/b_time_t.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ATTENTION: any change to the definition of the timespec structure must be
 * reflected in the definition of the _Timespec structure
 * (base/b_struct__Timespec.h) which is required to conform to POSIX
 * namespace isolation rules.
 */

#if  !defined(_DEFINED_struct_timespec) && !defined(_TIMESPEC_DEFINED)
#define _DEFINED_struct_timespec
#define _TIMESPEC_DEFINED
struct timespec
    {
    time_t tv_sec;
    long tv_nsec;
    };
#endif /* _DEFINED_struct_timespec */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_struct_timespech */

