/* timerLib.h - VxWorks timer library interface header */

/*
 * Copyright (c) 2014, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
10mar16,wfl  Avoid compilation errors when certain header files are used in C++ (V7COR-3972)
27feb14,h_k  created based on the 04feb14,to timerLib.h in kernel.(US15931)
*/

#ifndef __INCtimerLibh
#define __INCtimerLibh

#ifndef _YVALS
 #include <yvals.h>
#endif /* _YVALS */

/* typedef timer_t */

#include <base/b_timer_t.h>

#include <clockLib.h>

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
     !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

 #ifndef _STATUS_DEFINED
  #define _STATUS_DEFINED
typedef int	STATUS;
 #endif /* _STATUS_DEFINED */

#include <types/vxTypesBase.h>  /* trigger definitions of u_int32_t etc. */
#include <types/vxTypes.h>  /* _Vx_usr_arg_t */
#endif /* _POSIX_xxx_SOURCE */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ITIMERSPEC_DEFINED
 #define _ITIMERSPEC_DEFINED
struct itimerspec
    {
    struct timespec it_interval;        /* timer period (reload value) */
    struct timespec it_value;           /* timer expiration */
    };
#endif /* _ITIMERSPEC_DEFINED */

/* forward declaration of sigevent (eliminates need to include sigevent.h). */

struct sigevent;

/* function declarations */

extern int     timer_create     (clockid_t clock_id,
                                 struct sigevent *_Restrict evp,
                                 timer_t *_Restrict ptimer);
extern int     timer_delete     (timer_t timerid);
extern int     timer_gettime    (timer_t timerid, struct itimerspec * value);
extern int     timer_settime    (timer_t timerid, int flags,
                                 const struct itimerspec *_Restrict value,
                                 struct itimerspec *_Restrict ovalue);
extern int     timer_getoverrun (timer_t timerid);
extern int     nanosleep        (const struct timespec * rqtp,
                                 struct timespec * rmtp);

  /* POSIX definitions - default */

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
     !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
typedef void (*TIMER_CONNECT_FUNC) (timer_t timerId, _Vx_usr_arg_t arg);

extern int     timer_connect    (timer_t timerid, TIMER_CONNECT_FUNC routine,
                                 _Vx_usr_arg_t arg);
extern int     timer_cancel     (timer_t timerid);
extern timer_t timer_open       (const char * name, int mode, clockid_t clockId,
                                 struct sigevent * evp, void * context);
extern STATUS  timer_close      (timer_t timerId);
extern STATUS  timer_unlink     (const char * name);
#endif /* _POSIX_xxx_SOURCE */

#ifdef __cplusplus
}

 #if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
     !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

  #ifndef _VOIDFUNCPTR_DEFINED
   #define _VOIDFUNCPTR_DEFINED

typedef void    (*VOIDFUNCPTR) (...);  /* ptr to function returning void */

  #endif /* _VOIDFUNCPTR_DEFINED */

extern "C++" {
inline int timer_connect
    (
    timer_t timerid,
    VOIDFUNCPTR routine,
    _Vx_usr_arg_t arg
    )
    {
    return timer_connect (timerid, (TIMER_CONNECT_FUNC) routine,
			  arg);
    }
}
 #endif /* _POSIX_xxx_SOURCE */
#endif /* __cplusplus */

#endif /* __INCtimerLibh */
