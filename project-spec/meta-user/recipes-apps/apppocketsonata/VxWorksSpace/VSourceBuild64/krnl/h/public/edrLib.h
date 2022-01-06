/* edrLib.h - Error Detection and Reporting subsystem */

/*
 * Copyright (c) 2003-2005, 2008-2011, 2014-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
27oct16,cww  added EDR_FACILITY_SYSTEM (V7COR-3939)
30jul15,pcs  Fix for uninitialized struct entry msg.
27feb15,pfl  unconditionally include edrErrorInjectStub prototype
07dec14,jpb  Edit EDR inject macros to fill missing fields (US45760)
19nov14,jmp  Added posix support to ED&R (V7COR-2239).
09sep14,cww  fixed static analysis errors
19aug14,yl0  eliminated build warning for GNU
31jul14,pcs  Updated for CERT.
20jan11,cww  Save 32-bit tick in records to avoid ILP32 misaligned access
             (WIND00251544)
22oct10,rlp  Made edrSystemDebugXXX routine deprecated.
18aug10,cww  Additional 64-bit updates
13apr10,cww  Updated edrPmArena signature
03jun09,pcs  Updated to add support for LP64 data model.
11dec08,gls  made trace in EDR_REBOOT_INJECT contingent on valid
             taskIdCurrent (WIND00036637)
27aug08,jpb  Renamed VSB header file
02jun08,jpb  Removed include of vxLibCfgDefsP.h.  Added include path for 
             kernel configurations options set in vsb.
08may08,jpb  Modifications for source build.  Renamed INCLUDE_FULL_EDR_STUBS
             to _WRS_CONFIG_FULL_EDR_STUBS.
12aug05,yvp  Moved vxLibCfgDefsP.h to h/sys.
25may05,md   fix for SMP support
25jul04,md   added scalability of injection macros
23sep04,md   fix macros to avoid warnings
25may05,md   fix for SMP support
23sep04,md   fix macros to avoid warnings
10sep04,md   added passing injection message to policy handlers
26aug04,md   make record size configurable
23aug04,md   added new style hook routines
29jul04,md   added edrSystemDebugModeInit()
21jul04,md   add text injection hook prototypes
30jun04,md   fix for SPR 98727
07jun04,md   add additional fields for a memory map
21may04,md   added inject options
11may04,md   added support for encoding OS version
06may04,md   added prototype for edrShellCmdInit() 
28apr04,elg  Modify EDR macro prototype.
06apr04,pes  clean up compilation warnings.
20apr04,md   move private entries to edrLibP.h
30mar04,md   convert some fields to ascii instead of binary data
11mar04,md   add ED&R printf like output routines
03feb04,md   move common RTP defines to edrLibCommon.h
11nov03,dbs  update policy handler prototypes
06nov03,dbs  add INIT facility
04nov03,dbs  move error-log and record structures into edrErrLogLib.h
31oct03,dbs  add support for user-mode (RTP) error injection
24oct03,dbs  re-implement stack tracing
15oct03,dbs  add API to get boot count
06oct03,dbs  re-introduce optional stack-trace arg to EDR_USER_INJECT
29sep03,dbs  use setjmp() to get current regs in user-inject case
25sep03,dbs  implement ED&R system policies
24sep03,dbs  add prototype for edrHelp, add stack trace to REBOOT event
18sep03,dbs  add user inject macro
17sep03,dbs  add pre- and post-hooks
17sep03,dbs  add hook for error-injection
12sep03,dbs  reduce interrupt latency, introduce N-deep buffering
11sep03,dbs  record init failures, display in edrShow as necessary
10sep03,dbs  add edrErrorInject wrapper, remove reliance on funcptr
29aug03,dbs  update after review comments
19aug03,dbs  add ED&R system debug mode flag
18aug03,dbs  fix error codes
18aug03,dbs  add _func_edrErrorInject
13aug03,aim  added symbol names to stack trace
11aug03,aim  added boot count to error log header
07aug03,dbs  add extended ED&R show routines
06aug03,dbs  allow for more than one PM arena
04aug03,dbs  move 'missed errors' count into error-log
31jul03,dbs  use named constants for stack-trace and code-dump
31jul03,dbs  add separate edrShow component
31jul03,dbs  add transaction-like guards against errors early in boot
30jul03,dbs  add edrErrorRecordShow routine
28jul03,dbs  change 'location' to 'facility' and allow more of them
28jul03,dbs  add more error codes
25jul03,dbs  add fields to allow version checking
             introduce EDR_ERROR_LOG structure
18jul03,dbs  improve printing of error records
18jul03,dbs  update for memLogLib changes
17jul03,dbs  add error codes
15jul03,dsellars  created
*/

#ifndef __INCedrLib_h
#define __INCedrLib_h

#include <vxWorks.h>
#include <vsbConfig.h>
#include <stdlib.h>
#include <setjmp.h>
#ifdef  _WRS_CONFIG_FULL_EDR_STUBS
#include <edrErrLogLib.h>
#endif
#include <regs.h>
#include <excLib.h>
#include <edrLibCommon.h>
#include <taskLib.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* version of ED&R record format we're currently using */

#define EDR_VERSION             1

#ifdef _WRS_CONFIG_FULL_EDR_STUBS
/*
 * IMPORTANT: do NOT add members to the middle of this structure, only
 * to the end (but before 'text'). Offsets to the textual data are
 * stored as offsets from the beginning of the structure, so it it
 * still possible to read an OLDER kind of error-record.
 *
 * The 'size' field determines the actual number of bytes in the
 * entire record, including all the trailing text. The 'size_of' field
 * indicates the size of the structure (i.e. sizeof(EDR_ERROR_RECORD)
 * at the time the system which generated this record was
 * compiled. This allows edrLib to handle error records from older
 * systems compatibly.
 */

typedef struct edr_error_record
    {
    UINT32	  version;		/* version identifier		*/
    size_t	  size;			/* actual size of entire record */
					/* incl. trailing text		*/
    size_t	  size_of;		/* sizeof (EDR_ERROR_RECORD)	*/
    UINT32	  kind;			/* severity / facility		*/
    UINT32	  flags;		/* error-record options		*/
#ifdef _WRS_CONFIG_LP64
    _Vx_ticks64_t ticks;		/* VxWorks time stamp		*/
#else
    _Vx_ticks_t   ticks;		/* VxWorks time stamp		*/
#endif /* _WRS_CONFIG_LP64 */
    time_t	  time;			/* calendar time		*/
    UINT32	  osVersion;		/* version of OS/ED&R		*/
    UINT32	  cpuNumber;		/* CPU number (e.g. for MP) 	*/
    UINT32	  cpuType;		/* WindRiver CPU type code	*/
    UINT32        bootCycle;	        /* the bootCount this error     */
					/* was recorded in.             */
    TASK_ID	  taskId;		/* ID of executing task		*/
    RTP_ID	  rtpId;		/* ID of executing RTP		*/
    void *	  rtpAddrStart;		/* start address of RTP space	*/
    void *	  rtpAddrEnd;		/* end address of RTP space	*/
    INSTR *	  codeAddress;		/* address of code fragment	*/
    int		  lineNumber;		/* line number in source file	*/
    int		  reserved[8];		/* reserved for future use	*/
    ptrdiff_t	  offsetFileName;	/* offset to source file name	*/
    ptrdiff_t	  offsetTaskName;	/* offset to task name		*/
    ptrdiff_t	  offsetRtpName;	/* offset to RTP name		*/
    ptrdiff_t	  offsetMemoryMap;	/* offset to memory map	        */
    ptrdiff_t	  offsetExcinfo;	/* offset to exception info     */
    ptrdiff_t	  offsetRegisters;	/* offset to registers	        */
    ptrdiff_t	  offsetDisassembly;	/* offset to code disassembly	*/
    ptrdiff_t	  offsetTraceback;	/* offset to stack traceback	*/
    ptrdiff_t	  offsetPayload;	/* offset to text payload	*/
    /*************** IMPORTANT: ADD NEW FIELDS HERE! ********************/
    char	  text [4];		/* beginning of all textual info*/
    } EDR_ERROR_RECORD;
#endif /* _WRS_CONFIG_FULL_EDR_STUBS */

/* mask and shift counts for encoding version number in osVersion field */

#ifdef _WRS_CONFIG_FULL_EDR_STUBS
#define	EDR_OS_VERSION_MAJOR_MASK	0xff
#define	EDR_OS_VERSION_MAJOR_SHIFT	16
#define	EDR_OS_VERSION_MINOR_MASK	0xff
#define	EDR_OS_VERSION_MINOR_SHIFT	8
#define	EDR_OS_VERSION_MAINT_MASK	0xff
#define	EDR_OS_VERSION_MAINT_SHIFT	0
#endif /* _WRS_CONFIG_FULL_EDR_STUBS */

/* optional information which may be provided for RTP policy handling */

typedef struct
    {
    RTP_ID	 rtpId;		/* RTP's id				*/
    TASK_ID	 taskId;	/* task id within RTP			*/
    int		 options;	/* options to use when deleting		*/
    int		 status;	/* exit status to provide when deleting	*/
    int		 vector;	/* exception vector number		*/
    char *	 pEsf;		/* exception frame pointer		*/
    REG_SET *	 pRegs;		/* exception register set		*/
    EXC_INFO *	 pExcInfo;	/* exception information		*/
    BOOL	 isException;	/* are we handling an exception?	*/
    const char * msg;		/* ED&R record optional message		*/
    int          signalNum;     /* POSIX signal number */
    int          signalSubcode; /* POSIX "si_code" */
    } EDR_RTP_INFO;

/* optional information which may be provided for task policy handling */

typedef struct
    {
    TASK_ID		taskId;		/* task's id			    */
    _Vx_exit_code_t	status;		/* exit status to use when deleting */
    int			vector;		/* exception vector number	    */
    char *		pEsf;		/* exception frame pointer	    */
    REG_SET *		pRegs;		/* exception register set	    */
    EXC_INFO *		pExcInfo;	/* exception information	    */
    BOOL		isException;	/* are we handling an exception?    */
    const char *	msg;		/* ED&R record optional message	    */
    int                 signalNum;      /* POSIX signal number */
    int                 signalSubcode;  /* POSIX "si_code" */
    } EDR_TASK_INFO;

/* optional information which may be provided for system policy handling */

typedef struct
    {
    TASK_ID		taskId;		/* task's id			    */
    int			vector;		/* exception vector number	    */
    char *		pEsf;		/* exception frame pointer	    */
    REG_SET *		pRegs;		/* exception register set	    */
    EXC_INFO *		pExcInfo;	/* exception information	    */
    BOOL		isException;	/* are we handling an exception?    */
    const char *	msg;		/* ED&R record optional message	    */
    int                 signalNum;      /* POSIX signal number */
    int                 signalSubcode;  /* POSIX "si_code" */
    } EDR_SYSTEM_INFO;

/* optional information which may be provided for interrupt policy handling */

typedef struct
    {
    int		 vector;	/* exception vector number		*/
    char *	 pEsf;		/* exception frame pointer		*/
    REG_SET *	 pRegs;		/* exception register set		*/
    EXC_INFO *	 pExcInfo;	/* exception information		*/
    BOOL	 isException;	/* are we handling an exception?	*/
    const char * msg;		/* ED&R record optional message		*/
    int          signalNum;     /* POSIX signal number */
    int          signalSubcode; /* POSIX "si_code" */
    } EDR_INTERRUPT_INFO;

/* optional information which may be provided for init policy handling */

typedef struct
    {
    int		 vector;	/* exception vector number		*/
    char *	 pEsf;		/* exception frame pointer		*/
    REG_SET *	 pRegs;		/* exception register set		*/
    EXC_INFO *	 pExcInfo;	/* exception information		*/
    BOOL	 isException;	/* are we handling an exception?	*/
    const char * msg;		/* ED&R record optional message		*/
    int          signalNum;     /* POSIX signal number */
    int          signalSubcode; /* POSIX "si_code" */
    } EDR_INIT_INFO;

#ifdef _WRS_CONFIG_FULL_EDR_STUBS
/*
 * The type of a hook-function for error injection. It gets called
 * back for every error that is injected.
 */

typedef void (*EDR_ERRINJ_HOOK_FUNCPTR) (
		int          kind,	 /* severity | facility		*/
		const char * fileName,	 /* name of source file		*/
		int          lineNumber, /* line number of source code	*/
		void *       address,	 /* faulting address		*/
		const char * msg	 /* additional text string	*/
		);

/*
 * The type of a hook-function for additional text error injection. It gets
 * called back for every error that is injected.
 */

typedef size_t (*EDR_ERRINJ_TEXT_HOOK_FUNCPTR) (
		char *       p,		 /* pointer to buffer		*/
		size_t	     size,	 /* size of buffer		*/
		int          kind,	 /* severity | facility		*/
		const char * fileName,	 /* name of source file		*/
		int          lineNumber, /* line number of source code	*/
		void *       address	 /* faulting address		*/
		);

/* 
 * The type of a hook-function for pre/post hooks.
 */

typedef void (*EDR_HOOK_FUNCPTR) (
		int          type	/* pre/post injection indicator	*/
		);

#define	EDR_HOOK_TYPE_PRE	0	/* hook called pre injection	*/
#define	EDR_HOOK_TYPE_POST	1	/* hook called post injectsion	*/
#endif

/* defines */

/* init status - 0,1 are boolean uninit/init, negative values are errors */

#ifdef _WRS_CONFIG_FULL_EDR_STUBS
#define EDR_INIT_UNINITIALIZED		(0)
#define EDR_INIT_OK			(1)
#define EDR_INIT_edrErrLogCreate_FAILED	(-1)
#define EDR_INIT_edrErrLogAttach_FAILED	(-2)
#define EDR_INIT_pmRegionSize_FAILED	(-3)
#define EDR_INIT_pmRegionAddr_FAILED	(-4)
#define EDR_INIT_pmRegionProtect_FAILED	(-5)
#define EDR_INIT_pmRegionCreate_FAILED	(-6)
#define EDR_INIT_PM_FAILURE		(-7)
#define EDR_INIT_ERROR_LOG_NEWER	(-8)

/* maximum number of inject hook callout routines */

#define EDR_MAX_INJECT_HOOK_RTNS	16	/* general injection hooks  */
#define EDR_MAX_INJECT_TEXT_HOOK_RTNS	16	/* text injection hooks     */
#define EDR_MAX_INJECT_PP_HOOK_RTNS	16	/* pre/post injection hooks */
#endif /* _WRS_CONFIG_FULL_EDR_STUBS */

/* system generated ED&R fatal messages */

/* 
 * In below macros, the EDR Info structure maybe populated but
 * without the message.  If this is the case, we copy the reason
 * into the message field.
 */

/* Kernel fatal errors */

#define EDR_KERNEL_FATAL_INJECT(taskInfo, regs, excinfo, pc, reason)    \
    do {                                                                \
    EDR_TASK_INFO *p = taskInfo;                                        \
    EDR_TASK_INFO tmpTaskInfo;                                          \
    EDR_FATAL_INJECT(EDR_SEVERITY_FATAL | EDR_FACILITY_KERNEL,          \
                   __FILE__, __LINE__, regs, excinfo, pc, reason);      \
    if ((p == NULL))                                                    \
        {                                                               \
        p = &tmpTaskInfo;                                               \
        p->taskId = (TASK_ID)taskIdCurrent;                             \
        p->status = 0;                                                  \
        p->vector = 0;                                                  \
        p->pEsf = (char *) NULL;                                        \
        p->pRegs = regs;                                                \
        p->pExcInfo = excinfo;                                          \
        p->isException = FALSE;                                         \
        p->msg = reason;                                                \
        }                                                               \
    else                                                                \
        {                                                               \
        p->msg = reason;                                                \
        }                                                               \
    edrKernelFatalPolicyHandler(p);                                     \
    } while ((0))

/* System fatal errors (reboot required) */

#define	EDR_SYSTEM_FATAL_INJECT_FULL(sysInfo, regs, excinfo, pc, reason) \
    do									 \
	{								 \
	EDR_SYSTEM_INFO * p = sysInfo;					 \
	EDR_INJECT(EDR_SEVERITY_FATAL | EDR_FACILITY_SYSTEM,		 \
		   __FILE__, __LINE__, regs, excinfo, pc, reason);	 \
	if ((p != NULL))						 \
	    p->msg = reason;						 \
	edrSystemFatalPolicyHandler(sysInfo); 				 \
	} while ((0))

#ifdef _WRS_CONFIG_FULL_EDR_STUBS
#define EDR_SYSTEM_FATAL_INJECT(sysInfo, regs, excinfo, pc, reason)	\
	 EDR_SYSTEM_FATAL_INJECT_FULL(sysInfo, regs, excinfo, pc, reason)
#else
#define EDR_SYSTEM_FATAL_INJECT(sysInfo, regs, excinfo, pc, reason)	\
	 edrSystemFatalPolicyHandler(sysInfo)
#endif /* _WRS_CONFIG_FULL_EDR_STUBS */

/* Interrupt fatal errors */

#define EDR_INTERRUPT_FATAL_INJECT(intInfo, regs, excinfo, pc, reason) 	\
    do {                                                                \
    EDR_INTERRUPT_INFO *p = intInfo;                                    \
    EDR_INTERRUPT_INFO tmpIntInfo;                                      \
    EDR_FATAL_INJECT(EDR_SEVERITY_FATAL | EDR_FACILITY_INTERRUPT,       \
                   __FILE__, __LINE__, regs, excinfo, pc, reason);      \
    if ((p == NULL))                                                    \
        {                                                               \
        p = &tmpIntInfo;                                                \
        p->vector = 0;                                                  \
        p->pEsf = (char *) NULL;                                        \
        p->pRegs = (REG_SET *) regs;                                    \
        p->pExcInfo = excinfo;                                          \
        p->isException = FALSE;                                         \
        p->msg = reason;                                                \
        }                                                               \
    else                                                                \
        {                                                               \
        p->msg = reason;                                                \
        }                                                               \
    edrInterruptFatalPolicyHandler(p);                                  \
    } while ((0))

/* Init fatal errors */

#define EDR_INIT_FATAL_INJECT(initInfo, regs, excinfo, pc, reason)      \
    do {                                                                \
    EDR_INIT_INFO *p = initInfo;                                        \
    EDR_INIT_INFO tmpInitInfo;                                          \
    EDR_FATAL_INJECT(EDR_SEVERITY_FATAL | EDR_FACILITY_INIT,            \
                   __FILE__, __LINE__, regs, excinfo, pc, reason);      \
    if ((p == NULL))                                                    \
        {                                                               \
        p = &tmpInitInfo;                                               \
        p->vector = 0;                                                  \
        p->pEsf = (char *) NULL;                                        \
        p->pRegs = (REG_SET *) regs;                                    \
        p->pExcInfo = excinfo;                                          \
        p->isException = FALSE;                                         \
        p->msg = reason;                                                \
        }                                                               \
    else                                                                \
        {                                                               \
        p->msg = reason;                                                \
        }                                                               \
    edrInitFatalPolicyHandler(p);                                       \
    } while ((0))

/* RTP fatal errors */

#define EDR_RTP_FATAL_INJECT(rtpInfo, regs, excinfo, pc, reason)        \
    do {                                                                \
    EDR_RTP_INFO *p = rtpInfo;                                          \
    EDR_RTP_INFO tmpRtpInfo;                                            \
    EDR_FATAL_INJECT(EDR_SEVERITY_FATAL | EDR_FACILITY_RTP,             \
                   __FILE__, __LINE__, regs, excinfo, pc, reason);      \
   if ((p == NULL))                                                     \
        {                                                               \
        p = &tmpRtpInfo;                                                \
        p->rtpId = taskIdCurrent->rtpId;                                \
        p->taskId = (TASK_ID) taskIdCurrent;                            \
        p->options = 0;                                                 \
        p->status = 0;                                                  \
        p->vector = 0;                                                  \
        p->pEsf = (char *) NULL;                                        \
        p->pRegs = regs;                                                \
        p->pExcInfo = excinfo;                                          \
        p->isException = FALSE;                                         \
        p->msg = reason;                                                \
        }                                                               \
    else                                                                \
        {                                                               \
        p->msg = reason;                                                \
        }                                                               \
    edrRtpFatalPolicyHandler(p);                                        \
    } while ((0))

/* system generated ED&R boot/reboot messages */

#define EDR_BOOT_INJECT(msg) \
    EDR_INJECT_TRACE(EDR_SEVERITY_INFO, EDR_FACILITY_BOOT, \
		     EDR_EXCLUDE_MEMORYMAP, FALSE, msg)

#define EDR_REBOOT_INJECT(msg) \
    EDR_INJECT_TRACE(EDR_SEVERITY_INFO, EDR_FACILITY_REBOOT, \
		     EDR_EXCLUDE_REGISTERS, (taskIdCurrent != NULL), msg)


/* user generated ED&R messages */

#define EDR_USER_INFO_INJECT(trace, msg) \
	EDR_INJECT_TRACE(EDR_SEVERITY_INFO, EDR_FACILITY_USER, 0, trace, msg)

#define EDR_USER_WARNING_INJECT(trace, msg) \
	EDR_INJECT_TRACE(EDR_SEVERITY_WARNING, EDR_FACILITY_USER, 0, trace, msg)
    
#define EDR_USER_FATAL_INJECT(trace, msg) \
	EDR_INJECT_TRACE(EDR_SEVERITY_FATAL, EDR_FACILITY_USER, 0, trace, msg)


/* macros for injecting ED&R records */

/* 
 * EDR_FATAL_INJECT was introduced here because in the fatal macros above,
 * we only want to inject errors if _WRS_CONFIG_FULL_EDR_STUBS is configured.  
 * We would have used the EDR_INJECT macro but EDR_INJECT is used in the source 
 * and by having EDR_INJECT do nothing in the case where 
 * _WRS_CONFIG_FULL_EDR_STUBS is configured causes a compilation error because 
 * we cast the return of EDR_INJECT to void to satisfy static analysis warnings
 * in the source.
 */

#ifdef _WRS_CONFIG_FULL_EDR_STUBS
#define EDR_FATAL_INJECT(kind, file, line, regs, exc, addr, msg) \
	EDR_INJECT(kind, file, line, regs, exc, addr, msg)
#else
#define EDR_FATAL_INJECT(kind, file, line, regs, exc, addr, msg)
#endif /* _WRS_CONFIG_FULL_EDR_STUBS */

#define EDR_INJECT(kind, file, line, regs, exc, addr, msg) \
        (void) edrErrorInjectStub (kind, file, line, regs, exc, addr, msg)

#ifdef _WRS_CONFIG_FULL_EDR_STUBS
#define EDR_INJECT_TRACE_FULL(sev, fac, opt, trace, msg) \
    do { \
	REG_SET *pRegs = NULL; \
	jmp_buf env; \
	int doTrace=trace; \
	if ((doTrace != 0) && (setjmp(env) == 0)) { pRegs = &env[0].reg; } \
	EDR_INJECT(sev|fac|opt, __FILE__, __LINE__, pRegs, NULL, NULL, msg); \
    } while ((0))
#endif /* _WRS_CONFIG_FULL_EDR_STUBS */

#ifdef	_WRS_CONFIG_FULL_EDR_STUBS
# define EDR_INJECT_TRACE(sev, fac, opt, trace, msg) \
	 EDR_INJECT_TRACE_FULL(sev, fac, opt, trace, msg)
#else
# define EDR_INJECT_TRACE(sev, fac, opt, trace, msg) \
	 EDR_INJECT(sev|fac|opt, NULL, 0, NULL, NULL, NULL, msg)
#endif /* _WRS_CONFIG_FULL_EDR_STUBS */


/* globals */

/* functions */

extern STATUS edrErrorInjectStub
    (
    int			kind,		/* severity | facility		*/
    const char *	fileName,	/* name of source file		*/
    int			lineNumber,	/* line number of source code	*/
    const REG_SET *	pRegSet,	/* current register values	*/
    const EXC_INFO *	pExcInfo,	/* CPU-specific exception info	*/
    void *		addr,		/* faulting address (e.g. PC)	*/
    const char *	msg		/* additional text string	*/
    );

#ifdef _WRS_CONFIG_FULL_EDR_STUBS
extern void * edrPmArena    (size_t * pSize);
extern int    edrPmRegion   (void);

extern STATUS edrErrorInject
    (
    int			kind,		/* severity | facility | option	*/
    const char *	fileName,	/* name of source file		*/
    int			lineNumber,	/* line number of source code	*/
    const REG_SET *	pRegSet,	/* current register values	*/
    const EXC_INFO *	pExcInfo,	/* CPU-specific exception info	*/
    void *		addr,		/* faulting address (e.g. PC)	*/
    const char *	msg		/* additional text string	*/
    );

extern STATUS edrErrorRecordDecode
    (
    EDR_ERROR_RECORD *  pER,            /* pointer to error record	*/
    char *              pBuf,           /* pointer to output buffer	*/
    size_t              bufSize         /* size of output buffer	*/
    );

extern STATUS	edrErrorLogClear	(void);
extern int	edrBootCountGet		(void);
extern int	edrErrorRecordCount	(void);

/* debug flag manipulation routines */

extern BOOL   edrSystemDebugModeGet	(void)
		_WRS_DEPRECATED ("please use sysDebugModeGet() instead");
extern void   edrSystemDebugModeSet	(BOOL mode)
		_WRS_DEPRECATED ("please use sysDebugModeSet() instead");
extern BOOL   edrIsDebugMode		(void);
extern int    edrFlagsGet		(void);

/* hook manipulation routines */

extern STATUS edrErrorInjectHookAdd	(EDR_ERRINJ_HOOK_FUNCPTR hook);
extern STATUS edrErrorInjectHookDelete	(EDR_ERRINJ_HOOK_FUNCPTR hook);
    
extern STATUS edrErrorInjectPrePostHookAdd	(EDR_HOOK_FUNCPTR hook);
extern STATUS edrErrorInjectPrePostHookDelete	(EDR_HOOK_FUNCPTR hook);

extern STATUS edrErrorInjectTextHookAdd	   (EDR_ERRINJ_TEXT_HOOK_FUNCPTR hook);
extern STATUS edrErrorInjectTextHookDelete (EDR_ERRINJ_TEXT_HOOK_FUNCPTR hook);
#endif /* _WRS_CONFIG_FULL_EDR_STUBS */

/* system policy routines */

extern void edrKernelFatalPolicyHandler		(EDR_TASK_INFO * pInfo);
extern void edrInterruptFatalPolicyHandler	(EDR_INTERRUPT_INFO * pInfo);
extern void edrRtpFatalPolicyHandler		(EDR_RTP_INFO * pInfo);
extern void edrInitFatalPolicyHandler		(EDR_INIT_INFO * pInfo);
extern void edrSystemFatalPolicyHandler		(EDR_SYSTEM_INFO * pInfo);

/* show routines */

#ifdef _WRS_CONFIG_FULL_EDR_STUBS
extern STATUS edrShow		(int start, int count, int facility,
				 int severity);
extern STATUS edrFatalShow	(int start, int count);
extern STATUS edrInfoShow	(int start, int count);
extern STATUS edrIntShow	(int start, int count);
extern STATUS edrInitShow	(int start, int count);
extern STATUS edrRebootShow	(int start, int count);
extern STATUS edrBootShow	(int start, int count);
extern STATUS edrKernelShow	(int start, int count);
extern STATUS edrUserShow	(int start, int count);
extern STATUS edrRtpShow	(int start, int count);

/* misc routines */

extern STATUS edrClear		(void);
extern STATUS edrHelp		(void);
#endif /* _WRS_CONFIG_FULL_EDR_STUBS */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCedrLib_h */

