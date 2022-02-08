/* b_struct_itimerval.h - base type itimerval definition header */

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

#ifndef __INCb_struct_itimervalh
#define __INCb_struct_itimervalh

#include <base/b_struct_timeval.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _DEFINED_struct_itimerval
#define _DEFINED_struct_itimerval
struct itimerval {
	struct timeval it_interval;
	struct timeval it_value;
};
#endif  /* _DEFINED_struct_itimerval */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_struct_itimervalh */

