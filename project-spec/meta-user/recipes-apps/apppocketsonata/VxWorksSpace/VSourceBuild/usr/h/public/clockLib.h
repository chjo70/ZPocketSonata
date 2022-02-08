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
27feb14,h_k  created based ion the clockLib.h 04feb14,to in kernel (US15931).
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

/* The identifier of the system-wide realtime clock. */

#define CLOCK_REALTIME			0x0

/* The identifier for the system-wide monotonic clock. */

#define CLOCK_MONOTONIC			0x1

/*
 * The identifier of the CPU-time clock associated with the process making
 * a clock() or timer*() function call.
 */ 

#define CLOCK_PROCESS_CPUTIME_ID	0x2

/*
 * The identifier of the CPU-time clock associated with the thread making
 * a clock() or timer*() function call.
 */

#define CLOCK_THREAD_CPUTIME_ID		0x3

/* Flag indicating time is absolute. */

#define TIMER_ABSTIME			0x1

/* Flag indicating time is relative */

#define TIMER_RELTIME			(~TIMER_ABSTIME)

extern int clock_gettime   (clockid_t clock_id, struct timespec * tp);
extern int clock_settime   (clockid_t clock_id, const struct timespec * tp);
extern int clock_getres    (clockid_t clock_id, struct timespec * res);
extern int clock_nanosleep (clockid_t clock_id, int flags,
                            const struct timespec * rqtp,
                            struct timespec * rmtp);

#ifdef __cplusplus
}
#endif

#endif /* __INCclockLibh */
