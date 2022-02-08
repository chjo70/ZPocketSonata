/* sched.h - POSIX scheduler header file */

/*
 * Copyright (c) 2004-2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01g,29jul10,pad  Moved extern C statement after include statements.
01f,17feb06,pes  Move typedef of sched_param and pid_t.
01e,28jan06,mil  Updated for POSIX namespace conformance.
01d,11jan06,gls  added check that sched_param not already defined
01c,07jan06,jln  added SCHED_SPORADIC definition
01b,23aug05,kk   clean up inclusion of timer header, include time.h instead.
01a,24nov03,pad  Created, based on kernel version "01b,05jan94,kdl".
*/

#ifndef __INCschedh
#define __INCschedh

#include <time.h>

/* typedef pid_t */
#include <base/b_pid_t.h>

/* scheduling policies */

#define SCHED_FIFO	0x1	/* FIFO per priority scheduling policy */
#define SCHED_RR	0x2	/* round robin scheduling policy */
#define SCHED_OTHER	0x4	/* implementation defined */
#define SCHED_SPORADIC  0x8     /* sporadic scheduling policy - not used */

/* high/low priority values per scheduling policy POSIX numbering */

#define SCHED_FIFO_HIGH_PRI	255	/* POSIX highest priority for FIFO */
#define SCHED_FIFO_LOW_PRI	0	/* POSIX lowest priority for FIFO */
#define SCHED_RR_HIGH_PRI	255	/* POSIX highest priority for RR */
#define SCHED_RR_LOW_PRI	0	/* POSIX lowest priority for RR */

/* Following two priority definitions for SCHED_SPORADIC are not used */

#define SCHED_SPORADIC_HIGH_PRI	255  /* POSIX highest priority for SPORADIC */
#define SCHED_SPORADIC_LOW_PRI	0    /* POSIX lowest priority for SPORADIC */

/* typedef sched_param */
#include <base/b_struct_sched_param.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function declarations */

extern int sched_setparam (pid_t, const struct sched_param *);
extern int sched_getparam (pid_t, struct sched_param *);
extern int sched_setscheduler (pid_t, int, const struct sched_param *);
extern int sched_getscheduler (pid_t);
extern int sched_yield (void);
extern int sched_get_priority_max (int);
extern int sched_get_priority_min (int);
extern int sched_rr_get_interval (pid_t, struct timespec *);

#ifdef __cplusplus
}
#endif

#endif /* __INCschedh */
