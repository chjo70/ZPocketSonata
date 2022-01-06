/* sched.h - POSIX scheduler header file */

/*
 * Copyright (c) 1984-1994, 2006, 2010, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
18feb15,pad  Removed K&R style prototypes. Added header inclusions for types.
29apr10,pad  Moved extern C statement after include statements.
21feb06,pes  Correct multiple definition protection for sched_param
             struct by using base/b_struct_sched_param.h.
11jan06,gls  added check that sched_param not already defined
05jan94,kdl	 removed include of private/schedP.h.
04nov93,dvs  written
*/

#ifndef __INCschedh
#define __INCschedh

#include <time.h>
#include <timers.h>
#include <base/b_pid_t.h>
#include <base/b_struct_timespec.h>
#include <base/b_struct_sched_param.h>

/* scheduling policies */

#define SCHED_FIFO	0x1	/* FIFO per priority scheduling policy */
#define SCHED_RR	0x2	/* round robin scheduling policy */
#define SCHED_OTHER	0x4	/* implementation defined; not currently used */

/* high/low priority values per scheduling policy POSIX numbering */

#define SCHED_FIFO_HIGH_PRI	255	/* POSIX highest priority for FIFO */
#define SCHED_FIFO_LOW_PRI	0	/* POSIX lowest priority for FIFO */
#define SCHED_RR_HIGH_PRI	255	/* POSIX highest priority for RR */
#define SCHED_RR_LOW_PRI	0	/* POSIX lowest priority for RR */

#ifdef __cplusplus
extern "C" {
#endif

/* Function declarations */

extern int sched_setparam (pid_t pid, const struct sched_param * param);
extern int sched_getparam (pid_t pid, struct sched_param * param);
extern int sched_setscheduler (pid_t pid, int policy, 
			       const struct sched_param * param);
extern int sched_getscheduler (pid_t pid);
extern int sched_yield (void);
extern int sched_get_priority_max (int policy);
extern int sched_get_priority_min (int policy);
extern int sched_rr_get_interval (pid_t pid, struct timespec * interval);

#ifdef __cplusplus
}
#endif

#endif /* __INCschedh */
