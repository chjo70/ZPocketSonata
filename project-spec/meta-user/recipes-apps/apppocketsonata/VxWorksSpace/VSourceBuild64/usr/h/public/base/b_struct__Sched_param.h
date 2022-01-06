/* b_struct__Sched_param.h - struct _Sched_param definition header */

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
01c,28apr10,pad  Moved extern C statement after include statements.
01b,10aug06,pad  Applied more appropriate naming conventions for the members.
01a,08aug06,pad  Created.
*/

#ifndef __INCb_struct__Sched_paramh
#define __INCb_struct__Sched_paramh


#include <base/b_struct__Timespec.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _DEFINED_struct__Sched_param
#define _DEFINED_struct__Sched_param

/*
 * ATTENTION: the definition of the _Sched_param structure must be kept in
 * sync with the definition of the sched_param stucture in
 * base/b_struct_sched_param.h. The _Sched_param structure type is to be used
 * by all POSIX structured types that cannot make use of the sched_param
 * structure without breaking the namespace isolation rules which control the
 * context in which symbols may or may not be visible.
 */

#if defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE) || \
        defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#undef sched_priority
#ifndef _WRS_KERNEL
#if (_POSIX_SPORADIC_SERVER >= 0) || (_POSIX_THREAD_SPORADIC_SERVER >= 0)
#undef sched_ss_low_priority
#undef sched_ss_repl_period
#undef sched_ss_init_budget
#undef sched_ss_max_repl
#endif  /* _POSIX*_SPORADIC_SERVER >= 0 */
#endif  /* _WRS_KERNEL */
#endif /* _POSIX_xxxx_SOURCE */

struct _Sched_param				/* Scheduling param struct */
    {
    int			sched_priority;	/* scheduling priority */
#ifndef _WRS_KERNEL
#if (_POSIX_SPORADIC_SERVER >= 0) || (_POSIX_THREAD_SPORADIC_SERVER >= 0)
    int			sched_ss_low_priority;	/* low scheduling priority */
    struct _Timespec	sched_ss_repl_period;	/* replenishment period */
    struct _Timespec	sched_ss_init_budget;	/* initial budget */
    int			sched_ss_max_repl;	/* max pending replenishment */
#endif  /* _POSIX*_SPORADIC_SERVER >= 0 */
#endif  /* _WRS_KERNEL */
    };

#endif /* _DEFINED_struct__Sched_param */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_struct__Sched_paramh */

