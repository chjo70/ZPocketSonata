/* excLibP.h - private exception handling subsystem header file */

/* 
 * Copyright (c) 1984-2006, 2009-2010, 2014, 2016 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
27oct16,cww  Removed faked intContext when calling EDR (V7COR-3939) and
             consolidated exception handling across arches
20sep16,dlk  Adding excJobAddDefer(). (V7COR-4588)
01oct14,jpb  V7COR-1690: removed comment on a to-do item
27aug14,pad  Added support for effective user and group IDs as well as saved
             set-user ID and saved set-group ID in ISR_JOB (US44512).
13jun14,pad  Added clientTid, clientUid and clientGid members in ISR_JOB to
             support the user identification inheritance feature (US40199).
08apr10,jpb  Added func binding prototypes.
26mar09,zl   updated for LP64 build. Moved jobAdd() to jobLibP.h,
             removed jobExcAdd().
17oct06,gls  made maxIsrJobs argument a UINT (Defect #00059580)
07jun05,yvp  Added prototype for jobAdd(). Updated copyright.
09mar05,yvp  Added ISR_JOB definition.
20jan05,yvp  Reverted prototype for excInit().
25aug04,ans  updated declaration of excInit()
13nov01,yvp  created.
*/

#ifndef __INCexcLibPh
#define __INCexcLibPh

#include <vxWorks.h>
#include <vsbConfig.h>
#include <edrLib.h>
#include <excLib.h>
#ifdef _WRS_CONFIG_USER_IDENTIFICATION_INHERITANCE
#include <private/pxUserGroupLibP.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef	_ASMLANGUAGE

/* defines */

#define ISR_JOB_MAX_ARGS     6

/* typedefs */

/* Structure describing ISR-level job deferral */

typedef struct
    {
    VOIDFUNCPTR	  func;                   /* pointer to function to invoke */
    _Vx_usr_arg_t arg [ISR_JOB_MAX_ARGS]; /* args for function */
#ifdef _WRS_CONFIG_USER_IDENTIFICATION_INHERITANCE
    TASK_ID           clientTid;          /* client's task Id */
    WIND_CREDENTIALS  credentials;        /* client's user and group IDs */
#endif /* _WRS_CONFIG_USER_IDENTIFICATION_INHERITANCE */
    } ISR_JOB;

/* Select extended (32-bit) calls from the vector table to handlers */

extern BOOL excExtendedVectors;

/* function declarations */

extern STATUS   excSigLibInit (void);
extern void     excSigArchLibInit (void);
extern STATUS 	excVecInit (void);
extern STATUS 	excInit    (UINT maxIsrJobs);

/*
 * excJobAddDefer() is callable from a routine deferred to the kernel work
 * queue
 */

extern STATUS   excJobAddDefer (VOIDFUNCPTR func,
                                _Vx_usr_arg_t arg1, _Vx_usr_arg_t arg2,
                                _Vx_usr_arg_t arg3, _Vx_usr_arg_t arg4,
                                _Vx_usr_arg_t arg5, _Vx_usr_arg_t arg6);

extern void     excGenericHandle     (EXC_INFO * pExcInfo, void * pEsf,
                                      REG_SET * pRegs, int vecNum);
extern void *   excArchFaultGet      (EDR_TASK_INFO * pEdrInfo);

/* function pointer prototypes */

extern STATUS  (*_func_excJobAdd)(VOIDFUNCPTR func,
				  _Vx_usr_arg_t arg1, _Vx_usr_arg_t arg2,
				  _Vx_usr_arg_t arg3, _Vx_usr_arg_t arg4,
				  _Vx_usr_arg_t arg5, _Vx_usr_arg_t arg6);

extern FUNCPTR     _func_excInfoShow;
extern FUNCPTR     _func_excPanicHook;
extern FUNCPTR     _func_excBaseHook;
extern FUNCPTR     _func_excIntHook;
extern FUNCPTR     excExcepHook;

extern STATUS    (*_func_excOnSigMap) (int vecNum, EXC_INFO * pExcInfo,
                                       int * pSignalNum, int * pSignalSubCode);
extern void      (*_func_excSigSend)  (WIND_TCB * pTcbCurrent, int signalNum,
                                       int signalSubcode, int vecNum,
                                       void * faultAddr, REG_SET * pRegs,
                                       char * edrErrStr);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCexcLibPh */
