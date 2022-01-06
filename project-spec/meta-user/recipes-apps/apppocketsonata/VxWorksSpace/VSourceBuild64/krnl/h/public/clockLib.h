/* clockLib.h - VxWorks clock library interface header */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
03mar14,h_k  moved the CLOCK_xxx and TIMER_xxx macros from base/b_clockid_t.h.
04feb14,to   moved clockLib function prototypes here from time.h (US15931)
*/

#ifndef __INCclockLibh
#define __INCclockLibh

/* typedef clockid_t */

#include <base/b_clockid_t.h>

/* typedef struct timespec */

#include <base/b_struct_timespec.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CLOCK_REALTIME                  0x0 /* system wide realtime clock */
#define CLOCK_MONOTONIC                 0x1 /* system wide monotonic clock */
#define CLOCK_PROCESS_CPUTIME_ID        0x2 /* process CPU-time clock */
#define CLOCK_THREAD_CPUTIME_ID         0x3 /* thread CPU-time clock */

#define TIMER_ABSTIME   0x1                 /* absolute time */
#define TIMER_RELTIME   (~TIMER_ABSTIME)    /* relative time */

extern int clock_gettime   (clockid_t clock_id, struct timespec * tp);
extern int clock_settime   (clockid_t clock_id, const struct timespec * tp);
extern int clock_adjtime   (clockid_t clock_id, const struct timespec * delta,
                            struct timespec * olddelta);
extern int clock_getres    (clockid_t clock_id, struct timespec * res);
extern int clock_nanosleep (clockid_t clock_id, int flags,
                            const struct timespec * rqtp,
                            struct timespec * rmtp);

#ifdef __cplusplus
}
#endif

#endif /* __INCclockLibh */
