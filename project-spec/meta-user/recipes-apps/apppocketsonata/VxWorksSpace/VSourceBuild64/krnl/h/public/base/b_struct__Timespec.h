/* b_struct__Timespec.h - struct _Timespec definition header */

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
01c,10aug06,pad  Applied more appropriate naming conventions to the members.
01b,10aug06,pad  Renamed _Timespec structure's members.
01a,08aug06,pad  Created
*/

#ifndef __INCb_struct__Timespech
#define __INCb_struct__Timespech

#include <base/b_time_t.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _DEFINED_struct__Timespec
#define _DEFINED_struct__Timespec

/*
 * ATTENTION: the definition of the _Timespec structure must be kept in sync
 * with the definition of the timespec stucture in base/b_struct_timespec.h.
 * The _Timespec structure type is to be used by all POSIX structured types
 * that cannot make use of the timespec structure without breaking the
 * namespace isolation rules which control the context in which symbols may or
 * may not be visible.
 */

#if defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE) || \
        defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#undef tv_sec
#undef tv_nsec
#endif /* _POSIX_xxxx_SOURCE */

struct _Timespec
    {
    time_t tv_sec;
    long tv_nsec;
    };

#endif /* _DEFINED_struct__Timespec */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_struct__Timespech */
