/* wdLibP.h - private watchdog timer library header */

/* 
 * Copyright (c) 1984-1992, 1994, 2003, 2007-2010 Wind River Systems, Inc. 
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01i,29apr10,pad  Moved extern C statement after include statements.
01h,24aug09,gls  added commment about member order (WIND00112476)
01j,11may09,cww  Updated wdog struct to avoid padding
01i,29apr09,cww  LP64 update
01h,11feb09,zl   removed qLib.h inclusion
01g,27aug08,jpb  Renamed VSB header file
01f,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
01e,22jun07,lei  added WD_CANCEL; removed __STDC__ 
01d,26aug03,tcr  remove WindView InstClassId
01c,16jan94,c_s  added extern declaration for wdInstClassId.
01b,22sep92,rrr  added support for c++
01a,04jul92,jcf  created from v01h wdLib.h.
*/

#ifndef __INCwdLibPh
#define __INCwdLibPh

#include <vxWorks.h>
#include <vsbConfig.h>
#include <wdLib.h>
#include <classLib.h>
#include <private/qLibP.h>
#include <private/objLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* watchdog status values */

#define WDOG_OUT_OF_Q	0x0	/* valid watchdog not in tick queue */
#define WDOG_IN_Q	0x1	/* valid watchdog in tick queue */
#define WDOG_DEAD	0x2	/* terminated watchdog */

#ifdef _WRS_CONFIG_SMP
#define  WD_CANCEL(wdog)  wdCancelVerify (wdog)
#else
#define  WD_CANCEL(wdog)  wdCancel (wdog)
#endif /* _WRS_CONFIG_SMP  */

/*
 * NOTE:
 *
 * The objCore and tickNode members MUST remain the first and second in 
 * the watchdog structure.  This must match the TCB structure as the same
 * offset back from the tickNode is used to determine the address of the
 * objCore for both tasks and watchdogs.
 *
 * See defect WIND00112476.
 */

typedef struct wdog	/* WDOG */
    {
    OBJ_CORE	  objCore;	 /* 0x00/0x00 object management */
    Q_NODE	  tickNode;	 /* 0x40/0x80 multi-way queue node for tick \
					      queue */
    WD_RTN	  wdRoutine;	 /* 0x50/0xa0 routine to call upon expiration */
    _Vx_usr_arg_t wdParameter;	 /* 0x54/0xa8 arbitrary parameter to routine */
    USHORT	  status;	 /* 0x58/0xb0 status of watchdog */
    USHORT	  deferStartCnt; /* 0x5a/0xb2 number of wdStarts still in work \
					      queue */
    } WDOG;			 /* 0x5c/0xb8 total size */

/* variable definitions */

extern CLASS_ID wdClassId;		/* watchdog class id */

/* function declarations */

extern STATUS	wdInit (WDOG *pWdog);
extern STATUS	wdTerminate (WDOG_ID wdId);
extern STATUS	wdDestroy (WDOG_ID wdId, BOOL dealloc);
extern void	wdTick (void);

#ifdef _WRS_CONFIG_SMP
extern void     wdCancelVerify (WDOG_ID wdId);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCwdLibPh */
