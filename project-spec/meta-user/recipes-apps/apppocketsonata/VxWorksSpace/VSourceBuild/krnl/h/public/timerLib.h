/* timerLib.h - VxWorks timer library interface header */

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
03mar14,h_k  moved the CLOCK_xxx and TIMER_xxx macros from base/b_clockid_t.h
             to clockLib.h.
04feb14,to   moved timerLib function prototypes here from time.h (US15931)
*/

#ifndef __INCtimerLibh
#define __INCtimerLibh

/* typedef _Vx_usr_arg_t */

#include <types/vxTypes.h>

/* typedef STATUS */

#include <types/vxTypesOld.h>

/* typedef timer_t */

#include <base/b_timer_t.h>

#include <clockLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* forward declaration of sigevent (eliminates need to include sigevent.h). */

struct sigevent;

typedef void (*TIMER_CONNECT_FUNC) (timer_t timerId, _Vx_usr_arg_t arg);

struct itimerspec
    {
    struct timespec it_interval;        /* timer period (reload value) */
    struct timespec it_value;           /* timer expiration */
    };

/* function declarations */

extern int     timer_create     (clockid_t clock_id, struct sigevent * evp,
                                 timer_t * ptimer);
extern int     timer_delete     (timer_t timerid);
extern int     timer_gettime    (timer_t timerid, struct itimerspec * value);
extern int     timer_settime    (timer_t timerid, int flags,
                                 const struct itimerspec * value,
                                 struct itimerspec * ovalue);
extern int     timer_getoverrun (timer_t timerid);
extern int     timer_connect    (timer_t timerid, TIMER_CONNECT_FUNC routine,
                                 _Vx_usr_arg_t arg);
extern int     timer_cancel     (timer_t timerid);
extern int     nanosleep        (const struct timespec * rqtp,
                                 struct timespec * rmtp);
extern timer_t timer_open       (const char * name, int mode, clockid_t clockId,
                                 struct sigevent * evp, void * context);
extern STATUS  timer_close      (timer_t timerId);
extern STATUS  timer_unlink     (const char * name);

extern int     timer_show       (timer_t timerid, int verbose);
extern STATUS  timer_modify     (timer_t timerId, struct sigevent * pSigev);

#ifdef __cplusplus
}
#endif

#endif /* __INCtimerLibh */
