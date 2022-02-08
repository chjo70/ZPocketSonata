/* b_struct_sched_param.h - base type sched_param definition header */

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
01e,28apr10,pad  Moved extern C statement after include statements.
01d,17oct06,pad  Removed conditional blocks related to _POSIX_SPORADIC_SERVER
                 because this macro requires the inclusion of unistd.h, which
                 is not allowed by POSIX.1 (defect #69419 / Fix #69420).
01c,10aug06,pad  Removed debug information.
01b,01aug06,pad  Updated comments.
01a,16feb06,pes  Created.
*/

#ifndef __INCb_struct_sched_paramh
#define __INCb_struct_sched_paramh


#ifndef _WRS_KERNEL
#include <base/b_struct_timespec.h>
#endif /* _WRS_KERNEL */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _DEFINED_struct_sched_param
#define _DEFINED_struct_sched_param

struct sched_param              /* Scheduling parameter structure */
    {
    int sched_priority;         /* scheduling priority */
#ifndef _WRS_KERNEL
    int             sched_ss_low_priority;
    struct timespec sched_ss_repl_period;
    struct timespec sched_ss_init_budget;
    int             sched_ss_max_repl;
#endif  /* _WRS_KERNEL */
    };

#endif  /* _DEFINED_struct_sched_param */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_struct_sched_paramh */

