/* pxCpuTimeLibP.h - header for POSIX thread CPU-time library */

/*
 * Copyright (c) 2006-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01h,29apr10,pad  Moved extern C statement after include statements.
01g,29sep09,jpb  Removed inclusion of timerLibP.h which caused a circular 
                 dependancy.
01f,02sep09,jpb  Updated for LP64 support.
01e,27aug08,jpb  Renamed VSB header file
01d,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
01c,22jun07,lei  added PX_CPU_TIMER_CANCEL; moved the prototype of 
                 pxCpuTimerCancelVerify here
01b,22feb06,jln  replace the WDOG with PX_CPUTIMER
01a,25jan06,jln  Created
*/

#ifndef __INCpxCpuTimeLibPh
#define __INCpxCpuTimeLibPh

#include <vxWorks.h>
#include <vsbConfig.h>
#include <private/qLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define PX_CPUTIMER_OUT_OF_Q   0x0     /* CPU-time node not in tick queue */
#define PX_CPUTIMER_IN_Q       0x1     /* CPU-time node in tick queue */

#ifdef _WRS_CONFIG_SMP
#define  PX_CPU_TIMER_CANCEL(pxCpuTimerId, tid)    \
               _func_pxCpuTimerCancelVerify (pxCpuTimerId, tid)        
#else
#define  PX_CPU_TIMER_CANCEL(pxCpuTimerId, tid)    \
               _func_pxCpuTimerCancel (pxCpuTimerId, tid)
#endif /* _WRS_CONFIG_SMP  */

/* typedef */

/* NOTE: tickNode shall be the first, don't change the position */

typedef struct px_cputimer	/* low-level CPU-time timer structure */
    {
    Q_NODE      tickNode;       /* multi-way queue node for tick queue */
    USHORT      status;         /* status of node */
    timer_t     timerId;        /* high-level timer ID associated */
    } PX_CPUTIMER;

/* Function declarations */

extern void 	pxCpuTimeLibInit   (void);
extern PX_CPUTIMER * pxCpuTimerCreate (void);
extern STATUS   pxCpuTimerStart     (timer_t, int);
extern STATUS   pxCpuTimerCancel    (PX_CPUTIMER *, TASK_ID);
extern STATUS   pxCpuTimerDelete    (PX_CPUTIMER *, TASK_ID);

#ifdef _WRS_CONFIG_SMP
extern void pxCpuTimerCancelVerify (PX_CPUTIMER *, TASK_ID);
#endif /* _WRS_CONFIG_SMP */

#ifdef __cplusplus
}
#endif

#endif /* __INCpxCpuTimeLibPh */
