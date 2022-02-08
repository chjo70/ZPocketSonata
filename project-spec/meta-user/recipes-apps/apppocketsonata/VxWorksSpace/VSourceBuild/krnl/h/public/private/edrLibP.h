/* edrLibP.h - private ED&R library header file */

/*
 * Copyright (c) 2004, 2010, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
31jul14,pcs  Updated for CERT.
22oct10,rlp  Moved edrPolicyHandlerHook prototypes from edrLib.h.
17sep10,pcs  Update to use avlUintLib for ILP32 and avlUint64Lib for LP64.
18aug10,cww  Additional 64-bit updates
14jul10,pcs  Updated to add support for LP64 data model.
19may10,jpb  Removed system call prototypes.
29apr10,pad  Moved extern C statement after include statements.
10feb10,jpb  Added edrScXXX prototypes.
17sep04,md   added DSM hook
20apr04,md   moved private info from edrLib.h
12mar04,zl   renamed EDR_TASK_INFO to EDR_TCB_INFO.
10feb04,zl   created
*/

#ifndef __INCedrLibPh
#define __INCedrLibPh

#include <vxWorks.h>
#include <edrLib.h>
#ifdef _WRS_CONFIG_LP64
#include <avlUint64Lib.h>
#else
#include <avlUintLib.h>
#endif

/* definitions */

/* number of bytes to save for a code snapshot */

#if _WRS_CONFIG_FULL_EDR_STUBS
#define EDR_CODE_FRAG_SIZE  16
#endif

#ifndef	_ASMLANGUAGE

/* hook function type for ED&R policy handler */

typedef BOOL (*EDR_POLICY_HANDLER_HOOK)
		(
		int     type,           /* exception type */
		void *  pInfo,          /* information on exception */
		BOOL    debug           /* debug flags */
		);

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

/* hook-function type for private DSM error injection hook. */
#if _WRS_CONFIG_FULL_EDR_STUBS
typedef void (*EDR_ERRINJ_DSM_HOOK_FUNCPTR) (
		EDR_ERROR_RECORD * pER,	       /* pointer to error record    */
		int		   kind,       /* severity | facility	     */
		const char *	   fileName,   /* name of source file	     */
		int		   lineNumber, /* line number of source code */
		void *		   address,    /* faulting address	     */
		const char *	   msg	       /* additional text string     */
		);

/* structure for task-local data, accessed with the pEdrInfo field of the TCB */

typedef struct edr_tcb_info
    {
#ifdef _WRS_CONFIG_LP64
    AVLUINT64_TREE memEdrLocals;	/* local variables */
#else
    AVLU_TREE      memEdrLocals;	/* local variables */
#endif
    UINT     	     memEdrCtrl;	/* control of memEdrLib features */
    } EDR_TCB_INFO;

/* buffer structure used by printToEDRbuf() for oprintf output */

typedef struct
    {
    char *	buf;		/* pointer to buffer */
    ssize_t 	size;		/* size of buffer */
    } EDR_PRINTF_BUFFER;

/* DSM Hook */

extern EDR_ERRINJ_DSM_HOOK_FUNCPTR	edrErrorInjectDsmHook;

/* Hook tables */

extern EDR_ERRINJ_HOOK_FUNCPTR		edrErrorInjectHookTable[];
extern EDR_ERRINJ_TEXT_HOOK_FUNCPTR	edrErrorInjectTextHookTable[];
extern EDR_HOOK_FUNCPTR			edrErrorInjectPrePostHookTable[];

/* Private globals */

extern int		edrInitStatus;
extern atomic32_t	edrMissedErrors;

/* Routine declarations */

extern const char *	edrStatusMsg	(int statusCode);
extern void *		edrLogBaseGet	(void);
extern ssize_t		edrLogSizeGet	(void);

/*
 * buffered output routines - the edrPrintfBuf param should be of type
 * (EDR_PRINTF_BUFFER *).
 */

extern STATUS		printToEDRbuf	(char * buf, size_t nbytes,
					 _Vx_usr_arg_t edrPrintfBuf);

/* init routines */

extern STATUS		edrScInit	(void);
extern STATUS		edrShowInit	(void);
extern STATUS		edrShellCmdInit	(void);
extern STATUS		edrLibInit	(BOOL isNew, size_t recordSize);
#endif

extern STATUS edrPolicyHandlerHookAdd (EDR_POLICY_HANDLER_HOOK hook);
extern STATUS edrPolicyHandlerHookRemove (void);
extern EDR_POLICY_HANDLER_HOOK edrPolicyHandlerHookGet (void);

#ifdef __cplusplus
}
#endif

#endif	/* _ASMLANGUAGE */
#endif /* __INCedrLibPh */
