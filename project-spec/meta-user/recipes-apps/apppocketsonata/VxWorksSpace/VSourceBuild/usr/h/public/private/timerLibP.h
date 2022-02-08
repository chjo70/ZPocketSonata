/* timerLibP.h - private POSIX 1003.4 Clocks & Timers header */

/*
 * Copyright (c) 2003-2007, 2010, 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
26feb15,ymz  fixed flexelint errors and non coding conventions
14feb14,h_k  cleaned up compiler warnings in Diab 5.9.4.
16mar10,cww  LP64 adaptation
12feb10,kk   modified TV_CONVERT_TO_TICK() to compensate for partial tick
             added TV_CONVERT_TO_TICK_NO_PARTIAL() (WIND00186253)
07feb07,jmg  Changed comments from vxTicks to vxAbsTicks
26jun06,gls  Added sigeventId to __timer
11jan06,yvp  Added TICK_CONVERT_TO_TV macro.
             Updated copyright + #include now with angle-brackets.
24mar04,mcm  Including time.h instead of sys/time.h
04dec03,pad  Added definition of struct clock type.
03dec03,ans  code inspection comments.
13nov03,mcm  Using sys/time.h
30sep03,ans  written.
*/

/*
DESCRIPTION
This file provides header information for the
POSIX 1003.4 Timers interface per Draft 12.
*/

#ifndef __INCtimerLibPh
#define __INCtimerLibPh

#include <sys/types.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __timer
    {
    OBJ_HANDLE kTimerId;    		   /* handle returned by _timer_open */
    void       (*routine)(timer_t, _Vx_usr_arg_t);  /* user's routine */
    long       arg;         		   /* argument to user's routine */
    void *     sigeventId;  		   /* sigevent structure pointer */
    } TIMER;

typedef struct clock
    {
    UINT64 tickBase;            /* vxAbsTicks when time set */
    struct timespec timeBase;   /* time set */
    } CLOCK;

/* macros for "time value" manipulation */

#define BILLION         1000000000	/* 1000 million nanoseconds / second */

#define TV_EQ(a,b)	\
        (((a).tv_sec == (b).tv_sec) && ((a).tv_nsec == (b).tv_nsec))
#define TV_GT(a,b)	\
        (((a).tv_sec  > (b).tv_sec) ||	\
        (((a).tv_sec == (b).tv_sec) && ((a).tv_nsec > (b).tv_nsec)))
#define TV_LT(a,b)	\
        (((a).tv_sec  < (b).tv_sec) ||	\
        (((a).tv_sec == (b).tv_sec) && ((a).tv_nsec < (b).tv_nsec)))
#define TV_ISZERO(a)	\
        (((a).tv_sec == 0) && ((a).tv_nsec == 0))
#define TV_SET(a,b)	\
        {(a).tv_sec = (b).tv_sec; (a).tv_nsec = (b).tv_nsec;}
#define TV_ADD(a,b)	\
        {(a).tv_sec += (b).tv_sec; (a).tv_nsec += (b).tv_nsec; TV_NORMALIZE(a);}
#define TV_SUB(a,b)	\
        {(a).tv_sec -= (b).tv_sec; (a).tv_nsec -= (b).tv_nsec; TV_NORMALIZE(a);}
#define	TV_NORMALIZE(a)	\
	if ((a).tv_nsec >= BILLION)	\
	    { (a).tv_sec++; (a).tv_nsec -= BILLION; }	\
	else if ((a).tv_nsec < 0)	\
	    { (a).tv_sec--; (a).tv_nsec += BILLION; }
#define TV_VALID(a)	\
        (((a).tv_nsec >= 0) && ((a).tv_nsec < BILLION))
#define TV_ZERO(a)	\
        (a).tv_sec = 0; (a).tv_nsec = 0

#define TV_CONVERT_TO_SEC(a,b)  \
        do { \
        register UINT32 hz = CLOCKS_PER_SEC; \
	(a).tv_sec  = (time_t)((b) / hz);   \
	(a).tv_nsec = (ULONG)(((b) % hz) * (BILLION / hz)); \
        } while (0)

#define TV_CONVERT_TO_TICK(a,b) \
        do { \
        register UINT32 hz = CLOCKS_PER_SEC; \
        register UINT32 res = (BILLION / hz); \
        if (((UINT64)((b).tv_nsec) % res) != 0UL)               \
            {                                                   \
            (a) = (ULONG)(((UINT64) ((b).tv_sec) * hz) +	\
		      ((UINT64) ((b).tv_nsec) / res)) + 2UL; 	\
            }                                                   \
        else                                                    \
            {                                                   \
            (a) = (ULONG)(((UINT64) ((b).tv_sec) * hz) +	\
		      ((UINT64) ((b).tv_nsec) / res)) + 1UL; 	\
            }                                                   \
        } while (0)

#define TV_CONVERT_TO_TICK_NO_PARTIAL(a,b) \
        do {                                                    \
        register UINT32 hz = CLOCKS_PER_SEC;                    \
        register UINT32 res = (BILLION / hz);                   \
        ULONG    roundCnt;                                      \
                                                                \
        if (((UINT64)((b).tv_nsec) % res) != 0UL)               \
            {                                                   \
            roundCnt = 2UL;                                     \
            }                                                   \
        else                                                    \
            {                                                   \
            roundCnt = 1UL;                                     \
            }                                                   \
        (a) = (ULONG)(((UINT64) ((b).tv_sec) * hz) +	        \
		     ((UINT64) ((b).tv_nsec) / res)) + roundCnt;\
        } while (0)

#define TV_CONVERT_TO_TICK32(a,b) \
        do {                                                    \
        register UINT32 hz = CLOCKS_PER_SEC;                    \
        register UINT32 res = (BILLION / hz);                   \
        ULONG    roundCnt;                                      \
                                                                \
        if (((UINT64)((b).tv_nsec) % res) != 0UL)               \
            {                                                   \
            roundCnt = 1UL;                                     \
            }                                                   \
        else		                                        \
            {                                                   \
            roundCnt = 0UL;                                     \
            }                                                   \
        (a) = (ULONG)(((UINT64) ((b).tv_sec) * hz) +	        \
	              (UINT64) ((b).tv_nsec) / res) + roundCnt; \
        } while (0)

#define TICK_CONVERT_TO_TV(tk,tv)                         \
        do {                                              \
           register UINT32 hz = CLOCKS_PER_SEC;           \
           register UINT32 res = (BILLION / hz);          \
           ((tv).tv_sec) = (time_t) ((tk) / hz);          \
	   ((tv).tv_nsec) = (ULONG) (res * ((tk) % hz));  \
        } while (0)

#ifdef __cplusplus
}
#endif

#endif /* __INCtimerLibPh */
