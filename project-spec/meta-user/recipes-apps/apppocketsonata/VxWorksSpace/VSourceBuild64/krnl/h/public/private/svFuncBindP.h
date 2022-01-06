/* svFuncBind.h - System Viewer function pointer header file */

/*
 * Copyright (c) 2010-2011, 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01d,03jun13,wzc  Added stacktrace for system viewer.
01c,29aug11,wzc  Update to support dynamic power management (WIND00295115)
01b,27jul11,wzc  PPM for SV (WIND00214625)
01a,04feb10, tcr created
*/

#ifndef __svFuncBindh
#define __svFuncBindh

#include <dataCollectorLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* function pointers for evtLogLib.c */
extern STATUS (*_func_evtLogPayload)(event_t e, int withTs,
				     const void * addr, size_t nbytes, int st);
extern STATUS (*_func_evtLogPayloadString)(event_t e, int withTs,
					   const void * addr, size_t nbytes,
					   const void * stringAddr,
					   size_t strLen, int st);
extern STATUS (*_func_evtLogReserveTaskName)(_Vx_usr_arg_t key, event_t event, int nArgs,
					     _Vx_usr_arg_t arg1, _Vx_usr_arg_t arg2,
					     _Vx_usr_arg_t arg3, _Vx_usr_arg_t arg4,
					     _Vx_usr_arg_t arg5, _Vx_usr_arg_t arg6,
					     _Vx_usr_arg_t arg7, const char *name);
extern void (*_func_evtLogSyscall)(unsigned int,
				   const struct syscall_entry_state * pState, int st);
extern void (*_func_edrEvt)(event_t e, int kind, const char *filename, int linenumber,
			    const void * addr, const char * textPayload, int st);

extern STATUS (*_func_tmrConnect)(void (*routine)(),int arg);
extern void (*_func_tmrDisable) (void);
extern void (*_func_tmrEnable) (void);
extern int (*_func_tmrFreq)(void);
extern int (* _func_tmrPeriod)(void);
extern int (*_func_tmrStamp)(void);
extern int (*_func_tmrStampLock)(void);

extern DATA_COLLECTOR_FUNC_LIST_T * pDataCollectorFunctions;

#ifdef __cplusplus
}
#endif


#endif /* __svFuncBindh */
