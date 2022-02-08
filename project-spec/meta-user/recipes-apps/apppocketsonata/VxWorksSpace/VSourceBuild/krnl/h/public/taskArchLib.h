/* taskArchLib.h - header file for taskArchLib.c */

/*
 * Copyright (c) 1984-1992, 2009-2010, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
08mar14,gvm      enable taskTlsBaseSet for non-COMPAT69 builds
01p,13aug10,cww  added prototype for taskTlsBaseSet
01o,29apr10,pad  Moved extern C statement after include statements.
01n,20apr09,jb   Complete update to add support for the LP64 data model.
01m,23feb09,pcs  Updated to add support for the LP64 data model.
01l,08may03,pes  PAL conditional compilation cleanup. Phase 2.
01k,11oct01,cjj  removed Am29K support
01j,10dec93,hdn  added support for i86.
01j,02dec93,pme  added am29K family stack support.
01i,22sep92,rrr  added support for c++
01h,03jul92,jcf  cleaned up.
01g,26may92,rrr  the tree shuffle
01f,19mar92,yao  moved ANSI prototype for taskStackAllot() to taskLib.h.
01e,12mar92,yao  removed ANSI prototype for taskRegsShow().  added ANSI
		 prototype for taskRegsInit(), taskArgs{S,G}et(),
		 taskRtnValueSet().
01d,10jan92,jwt  added ANSI prototype for taskStackAllot().
01c,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed VOID to void
		  -changed copyright notice
01b,05oct90,dnw deleted private functions.
01a,05oct90,shl created.
*/

#ifndef __INCtaskArchLibh
#define __INCtaskArchLibh

#include <vxWorks.h>
#include <taskLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

#if !defined _WRS_SR_SIZE
#define _WRS_SR_SIZE	UINT16
#endif

extern STATUS 	taskSRSet	(TASK_ID tid, _WRS_SR_SIZE sr);
extern void 	taskRegsInit	(WIND_TCB * pTcb, char * pStackBase);
extern void 	taskArgsSet	(WIND_TCB * pTcb, char * pStackBase,
				 _Vx_usr_arg_t pArgs[]);
extern void 	taskArgsGet	(WIND_TCB * pTcb, char * pStackBase,
				 _Vx_usr_arg_t pArgs[]);
extern void 	taskRtnValueSet	(WIND_TCB * pTcb, int returnValue);

#if defined(_WRS_CONFIG_LP64) || !defined(_WRS_CONFIG_COMPAT69)
extern STATUS	taskTlsBaseSet	(TASK_ID tid, void * tlsbase);
#endif /* _WRS_CONFIG_LP64 */

#ifdef __cplusplus
}
#endif

#endif /* __INCtaskArchLibh */
