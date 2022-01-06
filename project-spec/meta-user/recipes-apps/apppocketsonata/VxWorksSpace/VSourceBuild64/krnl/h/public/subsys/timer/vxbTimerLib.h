/* vxbTimerLib.h - vxbus timer interfaces header file */

/*
 * Copyright (c) 2014,2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
25jan17,xxy  Add support for TSN Clocks and Timers(F6548)
14jan14,l_z  create from vxbTimerLib.h(01o)
*/

/*
DESCRIPTION

This library provides the timer specific interfaces

*/

#ifndef _INC_vxbTimerLibH
#define _INC_vxbTimerLibH

#include <sllLib.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <hwif/vxBus.h>

/* features provided by the timer */

/* the timer can interrupt */

#define VXB_TIMER_CAN_INTERRUPT             0x00000001

/* the timer provides interface to read intermediate count values */

#define VXB_TIMER_INTERMEDIATE_COUNT        0x00000002

/* the timer size is 16 bits */

#define VXB_TIMER_SIZE_16                   0x00000004

/* the timer size is 32 bits */

#define VXB_TIMER_SIZE_32                   0x00000008

/* the timer size is 64 bits */

#define VXB_TIMER_SIZE_64                   0x00000010

/* the timer cannot be disabled */

#define VXB_TIMER_CANNOT_DISABLE            0x00000020

/* the timer stops couting while the current count value is read */

#define VXB_TIMER_STOP_WHILE_READ           0x00000040

/* the timer can automatically reload the maximum counter after an interrupt */

#define VXB_TIMER_AUTO_RELOAD               0x00000080

/* counter is a free-running counter, rollover value cannot be modified */

#define VXB_TIMER_CANNOT_MODIFY_ROLLOVER    0x00000100

/*
 * the timer cannot support all frequencies between the maximum
 * and minimum frequency ranges. It supports only some frequencies
 * within the range.
 */

#define VXB_TIMER_CANNOT_SUPPORT_ALL_FREQS  0x00000200

#define VXB_TIMER_SIZE_23                   0x00000400

/* the timer can do IEEE1588 timer capability */

#define VXB_TIMER_IEEE1588                 0x00000800

/* the timer can do generic timer deadline capability */

#define VXB_TIMER_DEADLINE                 0x00001000

/* frequency values to be used during system clock selection */

#define SYSCLK_OPTIMUM_MINFRQ       10
#define SYSCLK_OPTIMUM_MAXFRQ       5000
#define SYSCLK_MINFRQ_LIMIT         60
#define SYSCLK_MAXFRQ_LIMIT         300

/* frequency values to be used during the auxiliary clock selection */

#define AUXCLK_OPTIMUM_MINFRQ       10
#define AUXCLK_OPTIMUM_MAXFRQ       50000
#define AUXCLK_MINFRQ_LIMIT         60
#define AUXCLK_MAXFRQ_LIMIT         1000

/* freuency value to be used by the timestamp timer */

#define TS_OPTIMUM_MAXFRQ           50000

/* maximum value of integer - used during timer selection */

#define MAXINT                      0x7FFFFFFF

/* typedefs */

typedef struct vxbTimerFunctionality*    timerHandle_t;


struct vxbTimerFunctionality
    {
    SL_NODE timerNode; /* must always be first element */
    BOOL    allocated;  /* flag used to denote timer allocation */
    UINT32  clkFrequency;   /* clock frequency */
    UINT32  minFrequency;   /* min period timer can provide */
    UINT32  maxFrequency;   /* max period timer can provide */
    UINT32  features;   /* features of timer */
    UINT32  ticksPerSecond; /* ticks per second */
    char    timerName[MAX_DRV_NAME_LEN + 1] ; /* timer Name */
    UINT32  timerNo;  /* timer number */
    UINT32  rolloverPeriod; /* rollover period of the timer in seconds */

    /* allocate dedicated timer */
    STATUS (*timerAllocate)
        (
        void *      pCookie,     /* IN */
        UINT32      flags    /* IN */
        );

    /* release dedicated timer */
    STATUS (*timerRelease)
        (
        void *      pCookie  /* IN */
        );

    /* get count between rollover/ISR events */
    STATUS (*timerRolloverGet)
        (
        void *  pCookie,    /* IN */
        UINT32 *  count     /* OUT */
        );

    /*
     * get current timestamp timer count value.
     * The driver should ensure returning the count as that of
     * an up counter.
     */
    STATUS (*timerCountGet)
        (
        void *      pCookie,    /* IN */
        UINT32 *        count       /* OUT */
        );

    /* disable the timer */

    STATUS (*timerDisable)
        (
        void *  pCookie     /* IN */
        );

    /* enable the timer */

    STATUS (*timerEnable)
        (
        void *  pCookie,    /* IN */
        UINT32  maxTimerCount   /* IN */
        );

    /* set the function to be called on every interrupt */

    STATUS (*timerISRSet)
        (
        void *  pCookie,        /* IN */
        void   (*pIsr)(_Vx_usr_arg_t),  /* IN */
        _Vx_usr_arg_t   arg     /* IN */
        );

    /* enable the timer */

    STATUS (*timerEnable64)
        (
        void *  pCookie,    /* IN */
        UINT64  maxTimerCount   /* OUT */
        );

    /* get count between rollover/ISR events */

    STATUS (*timerRolloverGet64)
        (
        void *  pCookie,    /* IN */
        UINT64 *count       /* IN */
        );

    /*
     * get current timestamp timer count value.
     * The driver should ensure returning the count as that of
     * an up counter.
     */
    STATUS (*timerCountGet64)
        (
        void *      pCookie,    /* IN */
        UINT64 *    count       /* OUT */
        );
    

/*
* timerDeadlineEnable is used to implement one-snot events as well as to start
* cyclic interrupts at specific start time.It works as follows:
* - When timer counter reaches deadlineCount the routine set by timerISRSet 
* is called. (One-shot event will utilize deadline method)
* - If maxTimerCount != 0 the cyclic interrupt will start when deadlineCount
* has expired. Deadline interrupt starts cyclic interrupt with period
* maxTimerCount.(Cyclic interrupt with specific start time can use this feature)
*/

    STATUS (*timerDeadlineEnable)
        (
        void *  pCookie,         /* IN */
        UINT64  deadlineCount,   /* IN */
        UINT64  maxTimerCount   /* IN */
        );
    };

typedef int (*VXB_TIMER_ITERATE_FUNC)
    (
    timerHandle_t pCandidate
    );

void vxbTimerRegister
    (
    timerHandle_t pCandidate
    );

timerHandle_t  vxbTimerEval
    (
    VXB_TIMER_ITERATE_FUNC timerEvalFunc
    );


/* globals */

extern char *   pSysClkName;
extern UINT32   sysClkTimerNo;
extern char *   pAuxClkName;
extern UINT32   auxClkTimerNo;
extern char *   pTimestampTimerName;
extern UINT32   timestampTimerNo;

extern void (*_vxb_msDelayRtn)
    (
    int delayTime
    );

extern void (*_vxb_usDelayRtn)
    (
    int delayTime
    );

extern void vxbMsDelay
    (
    int delayTime
    );

extern void vxbUsDelay
    (
    int delayTime
    );

extern timerHandle_t sysClkHandleGet (void);
extern timerHandle_t sysAuxClkHandleGet (void);
extern timerHandle_t sysTimestampHandleGet (void);

extern STATUS vxbTimerFeaturesGet
    (
    timerHandle_t   timer,
    UINT32 *        pMinFreq,
    UINT32 *        pMaxFreq,
    UINT32 *        pFeatures
    );

extern void vxbSysClkShow (void);
extern void vxbAuxClkShow (void);
extern void vxbTimestampShow (void);
extern void vxbDelayClkShow (void);

extern STATUS vxbDelayLibInit (void);
extern void vxbTimerStubInit (void);

extern STATUS vxbSysClkLibInit (void);

extern STATUS vxbSysClkConnect
    (
    FUNCPTR     routine,   /* routine called at each system clock interrupt */
    _Vx_usr_arg_t arg       /* argument with which to call routine        */
    );

extern void vxbSysClkEnable (void);
extern void vxbSysClkDisable (void);
extern int vxbSysClkRateGet (void);

extern STATUS vxbSysClkRateSet
    (
    int ticksPerSecond      /* number of clock interrupts per second */
    );

extern void vxbSysClkShowInit (void);
extern STATUS vxbAuxClkLibInit (void);

extern STATUS vxbAuxClkConnect
    (
    FUNCPTR routine,    /* routine called at each aux clock interrupt    */
    _Vx_usr_arg_t arg   /* argument to auxiliary clock interrupt routine */
    );

extern void vxbAuxClkDisable (void);
extern void vxbAuxClkEnable (void);
extern int vxbAuxClkRateGet (void);

extern STATUS vxbAuxClkRateSet
    (
    int ticksPerSecond  /* number of clock interrupts per second */
    );

extern void vxbAuxClkShowInit (void);

extern STATUS vxbTimestampLibInit (void);

extern STATUS vxbTimestampConnect
    (
    FUNCPTR     routine,
    _Vx_usr_arg_t arg
    );

/*
 * The following 10 functions are defined in src/hwif/util/vxbTimeStampLib.c
 * They call a vxBus timestamp driver unless the driver function is overriden
 * by the overrides above.
 */

/* timestamp enable/disable functions */

extern STATUS vxbTimestampEnable (void);
extern STATUS vxbTimestampDisable (void);

/* 32-bit timestamp access functions */

extern UINT32 vxbTimestampPeriod (void);
extern UINT32 vxbTimestampFreq (void);
extern UINT32 vxbTimestamp (void);
extern UINT32 vxbTimestampLock (void);

/* 64-bit timestamp access functions */

extern UINT64 vxbTimestamp64Period (void);
extern UINT64 vxbTimestamp64Freq (void);

extern STATUS vxbTimestamp64
    (
    UINT64 *  countVal  /* pointer to return 64-bit counter value */
    );

extern STATUS vxbTimestamp64Lock
    (
    UINT64 *  countVal  /* pointer to return 64-bit counter value */
    );

extern void vxbTimestampShowInit (void);

#ifdef __cplusplus
}
#endif

#endif /* _INC_vxbTimerLibH */

