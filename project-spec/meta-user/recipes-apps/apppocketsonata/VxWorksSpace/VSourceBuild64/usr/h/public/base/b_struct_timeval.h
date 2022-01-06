/* b_struct_timeval.h - base type struct timeval definition header */

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
01b,29jul10,pad  Moved extern C statement after include statements.
01a,16feb06,pes  Created.
*/

#ifndef __INCb_struct_timevalh
#define __INCb_struct_timevalh

#include <base/b_time_t.h>
#include <base/b_suseconds_t.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _DEFINED_struct_timeval
#define _DEFINED_struct_timeval
struct timeval {
        time_t		tv_sec;
        suseconds_t	tv_usec;
};
#endif  /* _DEFINED_struct_timeval */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_struct_timevalh */

