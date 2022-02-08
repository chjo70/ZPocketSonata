/* vxdbgLibP.h - private VxWorks debug library (VxDBG) header file */

/*
 * Copyright (c) 2006-2016, 2018 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
25jan18,syc  Removed the definition of DBG_INST_ALIGN.
11may16,jmp  Adapted vxdbgEnable() to ease code sharing with VxWorks 6.x.
             Removed prototypes of obsolete routines.
14mar16,dee  move BP_ACTIONS_ALL into enum
07jan16,elp  Added pClnt parameter to vxdbgIsBpAddr() (V7COR-3910)
18nov15,jmp  Added vxdbgIsBpAddr() (V7COR-3738).
10jul15,vhe  enabled single-step using debug registers (F1122)
25jun15,jmp  Added RTP_ID parameter to vxdbgLepFind() (V7RAD-272).
24jun15,w_x  Remove some unnecessary VSB options according to HLD review (F2518)
26mar15,vhe  Added vxdbgLepFind for ppc64 ELFv2 (F1122) 
04nov14,jpb  removed funcBindP.h (V7COR-910)
20feb15,rlp  Added VXDBG_ACCESS_DATA_RW macro to fix build warning (V7COR-2597)
22oct14,rlp  Made VxDBG list routines available to VxDBG's clients (V7COR-1625).
14oct14,elp  added vxdbgIsEnabled() (V7COR-1773).
09oct14,elp  added EVT_RUNCTRL_STATE event (US40741).
22Sep14,afi  made VXDBG_CPU_REG_SET arch specific
14sep14,jmp  Added vxdbgCpuExtraRegsGet().
11jul14,jmp  Fixed vxdbgStopModeRegs[Read|Write] prototype.
08jul14,jmp  Added architecture specific routines for Stop Mode Agent (US40739).
26aug14,jmp  Added vxdbgMemProbe().
13jun14,jmp  Added vxdbgHwBpSupportEnabled() to check if the hardware does
             enable the hardware breakpoint support (US39045).
18apr14,jmp  Added vxdbgIsAttached() (US12259).
21mar14,jmp  Added vxdbgHwBpAdd() & vxdbgHwBpTypeValidate() prototypes
             (US11680).
18nov13,rlp  Added vxdbgEventCancel() prototype.
26aug13,jmp  Added userKey support: vxdbgBpUserKeySet() and
             vxdbgBpUserKeyGet().
23may13,rlp  Added EVT_EXC event.
21may13,rlp  Added EVT_CTX_CREATE/DELETE events.
20may13,rlp  Moved vxdbgXxxInit prototypes to vxdbgLibInit header.
23nov11,rlp  CQID: Fix WIND00306867. Fixed VXDBG_TEXT_UPDATE macro.
20oct10,jmp  Added VXDBG_TEXT_UPDATE() and VXDBG_PAGE_ADDR_GET() macros.
08oct10,jmp  Added vxdbgInstrCmp() prototype (CQ:WIND00185617).
             Added VXDBG_INSTR_CMP() macro.
25aug10,rlp  Added wdbDbgAddrCheck() prototype.
05may10,rlp  Added context stop/continue event mechanism.
             Added a client name to vxdbgClntRegister API.
             Modified VXDBG_CTX_STOP macro.
14apr10,rlp  Added vxdbgClntUnregister and vxdbgRunCtrlLibInit prototypes.
             Added S_vxdbgLib_INVALID_CLIENT_ID errno.
09apr10,rlp  Moved VxDBG function pointers from funcBindP.h.
29apr10,pad  Moved extern C statement after include statements.
25feb10,rlp  Added vxdbgModuleLibInit prototype.
10feb10,rlp  Moved VXDBG_INFO to source private header file,
             Fixed VXDBG_BP_BY_ADDR_RANGE_REMOVE macro,
             Reworked errno numbers, Added VXDBG_EVT_ID type,
             Added more prototypes.
19jun09,mze  replacing PAD64
11may09,rlp  Added Hardware breakpoint support for LP64 model.
04mar09,jmp  Updated for 64-bit support.
18feb09,jb   Adding 64-bit support
07jul09,rlp  Added VXDBG_MEM_WIDTH_READ/WRITE macros,
             Re-defined VXDBG_MEM_XXX macros,
             Added S_vxdbgLib_INVALID_ALIGNMENT errno (WIND00171075).
02jun09,rlp  Removed DBG_CRET macro (WIND00168837).
11feb09,rlp  Defined BP_ACTIONS_ALL macro (CQ:WIND00148042).
27aug08,jpb  Renamed VSB header file
23jul08,rlp  Added RTP overlapped memory support.
24jun08,jpb  Added include path for kernel configurations options set in
             vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
12mar08,rlp  Replaced ALL macro with VXDBG_ALL_TASKS (CQ:WIND00116252).
18feb08,dbt  Fixed status table generation broken by previous change.
12feb08,rlp  Properly handle Branch Delay Slot (CQ:WIND00116790).
08feb08,jmp  Added VXDBG_STATUS (CQ:WIND00116500).
             Mapped VxDBG errnos on VXDBG_STATUS values.
             Added VXDBG_ERROR_TO_ERRNO().
06dec07,rlg  fix for WIND00112570 - HW break point message
12oct07,rlp  Removed ignoreStep field (CQ:WIND00106823).
11oct07,rlp  Added more architecture dependent header files
             (CQ:WIND00107725).
09jul07,jmp  added vxdbgMipsLibP.h inclusion.
22jun07,rlp  Removed/Added some errnos.
11jun07,rlp  Reworked breakpoint deletion routines.
08jun07,jmp  added vxdbgPpcLibP.h inclusion.
05jun07,rlp  Moved RTP function pointers to vxdbgLibSP.h.
01jun07,jmp  added errnos for vxdbgCpuLib library.
02may07,rlp  Added vxdbgBpEach prototype.
13mar07,rlp  Added context and breakpoint control macros.
01mar07,rlp  Added memory access macros.
16jan07,rlp  Added software breakpoint support for SMP.
13nov06,rlp  Added hardware breakpoint support for SMP.
26oct06,rlp  Written
*/

#ifndef __INCvxdbgLibPh
#define __INCvxdbgLibPh

/* includes */

#include <vxWorks.h>
#include <vsbConfig.h>
#include <vxdbgLib.h>

#ifdef	_WRS_CONFIG_SMP
/*
 * For SMP system, software breakpoints are no longer installed during task
 * context switch but are always present in memory. In order to turn on this
 * behavior, the _WRS_PERSISTENT_SW_BP macro is defined. Note that this macro
 * can be defined for UP system as well if we want to change the way
 * breakpoints are installed.
 */

#define	_WRS_PERSISTENT_SW_BP
#endif	/* _WRS_CONFIG_SMP */

#if     CPU_FAMILY == ARM
#include <arch/arm/dbgArmLib.h>
#include <arch/arm/private/vxdbgArmLibP.h>
#endif  /* CPU_FAMILY == ARM */
#if     CPU_FAMILY == COLDFIRE
#include <arch/coldfire/dbgColdfireLib.h>
#endif  /* CPU_FAMILY == COLDFIRE */
#if     CPU_FAMILY==I80X86
#ifndef _WRS_CONFIG_LP64
#include <arch/i86/dbgI86Lib.h>
#include <arch/i86/private/vxdbgI86LibP.h>
#else
#include <arch/i86/x86_64/dbgX86_64Lib.h>
#include <arch/i86/x86_64/private/vxdbgX86_64LibP.h>
#endif /* LP64 */
#endif  /* CPU_FAMILY==I80X86 */
#if     CPU_FAMILY == MIPS
#include <arch/mips/dbgMipsLib.h>
#include <arch/mips/private/vxdbgMipsLibP.h>
#endif  /* CPU_FAMILY == MIPS */
#if     CPU_FAMILY == PPC
#include <arch/ppc/dbgPpcLib.h>
#include <arch/ppc/private/vxdbgPpcLibP.h>
#endif	/* CPU_FAMILY == PPC */
#if     CPU_FAMILY == SIMLINUX
#include <arch/simlinux/dbgSimlinuxLib.h>
#include <arch/simlinux/private/vxdbgSimlinuxLibP.h>
#endif  /* CPU_FAMILY == SIMLINUX */
#if     CPU_FAMILY == SIMNT
#include <arch/simnt/dbgSimntLib.h>
#include <arch/simnt/private/vxdbgSimntLibP.h>
#endif  /* CPU_FAMILY == SIMNT */
#if     CPU_FAMILY == SIMSPARCSOLARIS
#include <arch/simsolaris/dbgSimsolarisLib.h>
#include <arch/simsolaris/private/vxdbgSimsolarisLibP.h>
#endif  /* CPU_FAMILY == SIMSPARCSOLARIS */
#if     CPU_FAMILY == SH
#include <arch/sh/dbgShLib.h>
#endif  /* CPU_FAMILY == SH */
#if     CPU_FAMILY == SPARC
#include <arch/sparc/dbgSparcLib.h>
#endif  /* CPU_FAMILY == SPARC */

#ifndef _ASMLANGUAGE
#include <regs.h>
#include <lstLib.h>
#include <sllLib.h>
#include <string.h>
#ifdef	_WRS_CONFIG_SMP
#include <cpuset.h>
#endif	/* _WRS_CONFIG_SMP */

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* Default hardware macros if not defined in architecture specific files */

#ifndef DBG_HARDWARE_BP		/* support of hardware breakpoint */
#define DBG_HARDWARE_BP		0
#endif	/* DBG_HARDWARE_BP */

#ifndef VXDBG_HAS_HW_BP_SUPPORT_CHECK /* VxDBG provides hardware breakpoint */
                                      /* support detection */
#define VXDBG_HAS_HW_BP_SUPPORT_CHECK   0
#endif  /* VXDBG_HAS_HW_BP_SUPPORT_CHECK */


#ifndef	BRK_HARDMASK		/* hardware breakpoint mask */
#define BRK_HARDMASK		0
#endif	/* BRK_HARDMASK */

#ifndef	BRK_HARDWARE		/* hardware breakpoint bit */
#define BRK_HARDWARE		0
#endif	/*  BRK_HARDWARE*/

#ifndef DBG_NO_SINGLE_STEP	/* trace mode (single step) support */
#define DBG_NO_SINGLE_STEP	0
#endif	/* DBG_NO_SINGLE_STEP */

#ifndef DBG_STEP_AND_BP_SHARED_VEC	/* same vector for BP and STEP */
#define DBG_STEP_AND_BP_SHARED_VEC	0
#endif	/* DBG_STEP_AND_BP_SHARED_VEC */

#ifndef	_WRS_ADJUST_PC_AFTER_SW_BP
#define _WRS_ADJUST_PC_AFTER_SW_BP(pRegs)
#endif	/* _WRS_ADJUST_PC_AFTER_SW_BP */

#ifndef	_WRS_ADJUST_PC_FOR_BRANCH_DELAY
#define	_WRS_ADJUST_PC_FOR_BRANCH_DELAY(pReg)	{}
#endif	/* _WRS_ADJUST_PC_FOR_BRANCH_DELAY */

#ifndef _WRS_GET_PC_FOR_BRANCH_DELAY
#define _WRS_GET_PC_FOR_BRANCH_DELAY(pc, pReg)  (pc = (INSTR *) (pReg)->reg_pc)
#endif  /* _WRS_GET_PC_FOR_BRANCH_DELAY */

/*
 * Define our own macros to manipulate the list in order to be able to set
 * breakpoints on the lstLib library.
 */

#define	VXDBG_LST_FIRST(list)		list.node.next
#define	VXDBG_LST_LAST(list)		list.node.previous
#define	VXDBG_LST_NEXT(pNode)		pNode->next
#define	VXDBG_LST_PREVIOUS(pNode)	pNode->previous
#define	VXDBG_LST_COUNT(list)		list.count
#define	VXDBG_LST_ADD(list, pNode) \
	    vxdbgListInsert (&list, list.node.previous, pNode);
#define	VXDBG_LST_DELETE(list, pNode) \
	    vxdbgListDelete (&list, pNode);
#define	VXDBG_LST_INSERT(list, pPrev, pNode) \
	    vxdbgListInsert (&list, pPrev, pNode);
#define	VXDBG_LST_INIT(list) \
	    {	\
	    list.node.next  = NULL; \
	    list.node.previous  = NULL; \
	    list.count = 0; \
	    }

/* Context control macros */

#define	VXDBG_CTX_FUNCS_ARE_INSTALLED() \
	    (_func_vxdbgCtxStop != NULL)

#define	VXDBG_CTX_STOP(pClnt, pCtx, force) \
	    _func_vxdbgCtxStop (pClnt, pCtx, force)
#define	VXDBG_CTX_CONT(pClnt, pCtx) \
	    _func_vxdbgCtxCont (pClnt, pCtx)
	    
/* Breakpoint control macros */

#define	VXDBG_BP_FUNCS_ARE_INSTALLED() \
	    (_func_vxdbgBpDelete != NULL)

#define VXDBG_BP_DELETE(bpInfo, retVal) \
	    retVal = _func_vxdbgBpDelete (bpInfo)

#define VXDBG_BP_BY_ID_REMOVE(pClient, retVal, brkptId) \
	    { \
	    VXDBG_BP_DEL_INFO   bpInfo; \
	    \
	    bpInfo.type = BP_BY_ID_DELETE; \
	    bpInfo.pClnt = pClient; \
	    bpInfo.info.id.bpId = brkptId; \
	    \
	    VXDBG_BP_DELETE(bpInfo, retVal); \
	    }

#define VXDBG_BP_BY_ADDR_AND_CTX_REMOVE(pClient, retVal, address, pContext) \
	    { \
	    VXDBG_BP_DEL_INFO   bpInfo; \
	    \
	    bpInfo.type = BP_BY_ADDR_AND_CTX_DELETE; \
	    bpInfo.pClnt = pClient; \
	    bpInfo.info.addrCtx.addr = address; \
	    bpInfo.info.addrCtx.pCtx = pContext; \
	    \
	    VXDBG_BP_DELETE(bpInfo, retVal); \
	    }

#define VXDBG_BP_BY_CTX_REMOVE(pClient, retVal, pContext) \
	    VXDBG_BP_BY_ADDR_AND_CTX_REMOVE(pClient, retVal, NULL, pContext)

#define VXDBG_BP_BY_ADDR_RANGE_REMOVE(pClient, retVal, startAdrs, endAdrs) \
	    { \
	    VXDBG_BP_DEL_INFO   bpInfo; \
	    \
	    bpInfo.type = BP_BY_ADDR_RANGE_DELETE; \
	    bpInfo.pClnt = pClient; \
	    bpInfo.info.addrRange.startAddr = (void *) startAdrs; \
	    bpInfo.info.addrRange.endAddr = (void *) endAdrs; \
	    \
	    VXDBG_BP_DELETE(bpInfo, retVal); \
	    }

/* Memory access macros */

#define	VXDBG_MEM_FUNCS_ARE_INSTALLED() \
	    (_func_vxdbgMemRead != NULL)

#define	VXDBG_MEM_WIDTH_READ		vxdbgMemRead
#define	VXDBG_MEM_READ(pSrc, pDest, size)	\
	    VXDBG_MEM_WIDTH_READ(pSrc, pDest, size, 0)

#define	VXDBG_MEM_WIDTH_WRITE		vxdbgMemWrite
#define	VXDBG_MEM_WRITE(pSrc, pDest, size)	\
	    VXDBG_MEM_WIDTH_WRITE(pSrc, pDest, size, 0)

#define	VXDBG_MEM_WIDTH_ACCESS(mode, pSrc, pDest, size, width) \
	    if (mode == VX_READ) \
		vxdbgMemRead (pSrc, pDest, size, width); \
	    else \
		vxdbgMemWrite (pSrc, pDest, size, width);
#define	VXDBG_MEM_ACCESS(mode, pSrc, pDest, size) \
	    VXDBG_MEM_WIDTH_ACCESS(mode, pSrc, pDest, size, 0)

#define	VXDBG_MEM_MOVE(pSrc, pDest, size) \
	    vxdbgMemMove (pSrc, pDest, size);

#define	VXDBG_MEM_SCAN(pBuffer, pPattern, size, status) \
	    status = vxdbgMemScan (pBuffer, pPattern, size);
	
#define	VXDBG_INSTR_CMP			vxdbgInstrCmp

#define VXDBG_PAGE_ADDR_GET(addr)         \
                (void *) ((VIRT_ADDR)(addr) & ~(VM_PAGE_SIZE_GET() - 1))

/*
 * VXDBG_TEXT_UPDATE() - update protected or unprotected text code
 *
 * This macro can be used to modify text code whether it is managed by VM
 * or not.
 * If VM is installed and the piece of code we want to update is
 * write-protected, then we must use VM_CONTEXT_BUFFER_WRITE() to
 * bypass write protection, otherwise we can write directly to memory.
 *
 * SMP NOTE: Since this macro can be used while interrupts are locked on other
 * CPUs, this macro must not use VM_STATE_SET() or any other call that
 * may generate interprocessor interrupts: The generated interrupts would never
 * be handled, and this would lead to a live-lock situation.
 */

#define VXDBG_TEXT_UPDATE(pText,pNewText,textSize,pStatus)		       \
    {									       \
    UINT protState;	/* protection state of area to update */	       \
									       \
    *pStatus = VXDBG_ERR_INIT;						       \
									       \
    if ((VM_INSTALLED) &&						       \
	(VM_STATE_GET (NULL, VXDBG_PAGE_ADDR_GET(pText), &protState) == OK) && \
	((protState & (VM_STATE_MASK_VALID|VM_STATE_MASK_WRITABLE)) ==	       \
			    (VM_STATE_VALID|VM_STATE_WRITABLE_NOT)))	       \
	{								       \
	if (VM_CONTEXT_BUFFER_WRITE (NULL, (VIRT_ADDR)pNewText,		       \
				     (VIRT_ADDR)pText, textSize) == OK)	       \
	    *pStatus = VXDBG_OK;					       \
	}								       \
    else								       \
	{								       \
	bcopy ((char *)pNewText, (char *)pText, textSize);		       \
	*pStatus = VXDBG_OK;						       \
	}								       \
    }

/* Miscellaneous macros */

#define VXDBG_ALL_TASKS	0			/* BP applies to all tasks */
#define VXDBG_ALL_BPS	((VXDBG_BP_ID)(-1))	/* Command applies to all BPs */

#define VXDBG_DISABLE_REASON_MAX_LEN 160 
#define VXDBG_DISABLE_REASON_GET()      (vxdbgDisableReason)

/* data types */

/* Breakpoint identifier type */

typedef UINT32			VXDBG_BP_ID;

/* Breakpoint info structure */

typedef struct brkpt	 	VXDBG_BP_INFO;

/* Debug event identifier type */

typedef struct vxdbg_evt_node *	VXDBG_EVT_ID;

/* Define the type of the routine called when a BP is hit */

typedef void (*VXDBG_BP_CALL_RTN)
    (
    _Vx_usr_arg_t	bpCallArg,
    REG_SET *	pRegSet
    );

/* Define the type of the routine invoked from vxdbgBpEach() API.  */

typedef BOOL (*VXDBG_BP_EACH_RTN)
    (
    VXDBG_BP_INFO *	pBp,
    _Vx_usr_arg_t	arg
    );

/* Define the breakpoint delete information */

typedef enum vxdbg_bp_del_type
    {
    BP_BY_ID_DELETE = 0,	/* delete a specific BP. */
    BP_BY_ADDR_AND_CTX_DELETE,	/* delete BPs that match a specified */
    				/* address and context */
    BP_BY_ADDR_RANGE_DELETE	/* delete all BPs located in a specific */
    				/* range of addresses */
    } VXDBG_BP_DEL_TYPE;

typedef struct vxdbg_bp_del_info
    {
    VXDBG_BP_DEL_TYPE   type;		/* type of delete action */
    VXDBG_CLNT_ID       pClnt;		/* VxDBG client id */
    union
	{
	/* The following are only used for BP_BY_ID_DELETE action */

	struct
	    {
	    VXDBG_BP_ID bpId;		/* breakpoint id */
	    } id;

	/*
	 * The following are used for BP_BY_CTX_DELETE and
	 * BP_BY_ADDR_AND_CTX_DELETE actions.
	 */

	struct
	    {
	    VXDBG_CTX * pCtx;		/* breakpoint context */
	    void *	addr;		/* breakpoint address */
	    } addrCtx;

	/* The following are only used for BP_BY_ADDR_RANGE_DELETE action */

	struct
	    {
	    void *	startAddr;	/* start of the address range */
	    void *	endAddr;	/* end of the address range */
	    } addrRange;
	} info;
    } VXDBG_BP_DEL_INFO;

/* Internal breakpoint structure */

typedef struct brkpt
    {
    NODE		chain;		/* breakpoint chain */
    VXDBG_BP_ID		id;		/* breakpoint ID */
    void *		addr;		/* breakpoint address */
    struct vxdbg_ctx	ctx;		/* breakpoint context */
    struct vxdbg_clnt *	ownerId;	/* breakpoint owner task ID */
#ifdef        _WRS_PERSISTENT_SW_BP
    PHYS_ADDR		physAddr;       /* breakpoint physical address */
#endif        /* _WRS_PERSISTENT_SW_BP */
    VXDBG_BP_CALL_RTN	callRtn;	/* routine to call (if any) */
    _Vx_usr_arg_t	callArg;	/* called routine argument */
    void *		userKey;	/* client specific key */
    BOOL		isInstalled;	/* breakpoint is installed */
    UINT32		action;		/* action associated with breakpoint */
#ifdef	_WRS_CONFIG_SMP
    cpuset_t		cpus;		/* processors number where */
    					/* hardware BP is installed */
#endif	/* _WRS_CONFIG_SMP */
    UINT32		count;		/* breakpoint count */
    UINT16		access;		/* SW or HW breakpoint */
    INSTR		instr;		/* instruction at breakpoint address */
    UINT8		attr;		/* breapoint attribute */
    } BRKPT;

/*
 * List of breakpoint attributes. You can specify any number of those
 * attributes.
 *
 * A temporary breakpoint is a breakpoint that is removed whenever it is hit.
 * The BP_USER[1|2|3] can be used by a client to provide client specific
 * information for this breakpoint. This can be used later when displaying
 * the breakpoint list (e.g.). Note that this user attribute does not have
 * any impact on the breakpoint handling behavior.
 */

typedef enum bp_attr
    {
    BP_TMP_STEP_OVER	= 1,	/* temporary breakpoint used for step-over */
    BP_USER1		= 2,	/* user reserved attribute */
    BP_USER2		= 4,	/* user reserved attribute */
    BP_USER3		= 8	/* user reserved attribute */
    } VXDBG_BP_ATTR;

/* List of events that can occur during debugging */

typedef enum event_type	
    {
    EVT_TRACE		= 0x00000001,	/* trace exception */
    EVT_BP		= 0x00000002,	/* breakpoint exception */
    EVT_BP_ADD		= 0x00000004,	/* breakpoint add */
    EVT_BP_DELETE	= 0x00000008,	/* breakpoint delete */
    EVT_CTX_STOP	= 0x00000010,	/* context stop */
    EVT_CTX_CONT	= 0x00000020,	/* context continue */
    EVT_CTX_CREATE	= 0x00000040,	/* context creation */
    EVT_CTX_DELETE	= 0x00000080,	/* context deletion */
    EVT_EXC		= 0x00000100,	/* context deletion */
    EVT_RUNCTRL_STATE   = 0x00000200,   /* runcontrol status change */
    EVT_INVALID		= 0x00000201	/* mark end of event type list */
    } VXDBG_EVT_TYPE;

/* List of possible action to perform when a breakpoint is hit */

typedef enum bp_action_type
    {
    BP_ACTIONS_ALL      = -1,           /* all actions */
    BP_ACTION_CALL      = 0x00000001,   /* condition the evtpt via a proc */
    BP_ACTION_NOTIFY    = 0x00000002,   /* call notify hooks */
    BP_ACTION_STOP      = 0x00000004,   /* stop the task or process */
    BP_ACTION_ALL_STOP  = 0x00000008    /* stop RTP tasks, or kernel tasks */
    } VXDBG_BP_ACTION;

/* List of supported VxDBG hardware breakpoint access types (Can be OR'ed) */

typedef enum vxdbg_hwbp_access_type
    {
    VXDBG_ACCESS_DATA_READ      = 0x00000001,   /* data read access */
    VXDBG_ACCESS_DATA_WRITE     = 0x00000002,   /* data write access */
    VXDBG_ACCESS_DATA_RW        = 0x00000003,   /* data read/write access */
    VXDBG_ACCESS_INSTRUCTION    = 0x00000004,   /* instruction */
    } VXDBG_HWBP_ACCESS_TYPE;

/* externals */

extern char     vxdbgDisableReason[VXDBG_DISABLE_REASON_MAX_LEN];
extern LIST	vxdbgBpList;

/* function pointers declarations */

extern STATUS	(*_func_vxdbgCtxStop) (VXDBG_CLNT_ID pClnt,
						VXDBG_CTX * pCtx, BOOL force);
extern STATUS	(*_func_vxdbgCtxCont) (VXDBG_CLNT_ID pClnt, VXDBG_CTX * pCtx);
extern STATUS	(*_func_vxdbgBpDelete) (VXDBG_BP_DEL_INFO bpInfo);
extern size_t	(*_func_vxdbgMemRead) (void * pAddress, void * pBuffer,
						size_t numBytes, size_t width);
extern size_t	(*_func_vxdbgMemWrite) (void * pAddress, void * pBuffer,
						size_t numBytes, size_t width);
extern size_t	(*_func_vxdbgMemMove) (void * pSrc, void * pDest,
						size_t numBytes);
extern STATUS	(*_func_vxdbgMemScan) (void * pPtr, void * pPattern,
						size_t size);

/* function declarations */

extern VXDBG_CLNT_ID	vxdbgClntRegister (char * pName,
					VXDBG_EVT_TYPE evtMask);
extern STATUS		vxdbgClntUnregister (VXDBG_CLNT_ID pClnt);
#if (_WRS_VXWORKS_MAJOR < 7)
extern void		vxdbgEnable (BOOL enable);
#else
extern void		vxdbgEnable (BOOL enable, char * disableReason);
#endif
extern BOOL             vxdbgIsEnabled (void);
extern STATUS		vxdbgHookAdd (VXDBG_CLNT_ID pClnt,
				      VXDBG_EVT_TYPE type, void (*hook) ());
extern STATUS		vxdbgStep (VXDBG_CLNT_ID pClnt, VXDBG_CTX * pCtx,
					INSTR * startAddr, INSTR * endAddr);
extern STATUS		vxdbgStop (VXDBG_CLNT_ID pClnt,
					VXDBG_CTX * pCtx, BOOL force);
extern STATUS		vxdbgCont (VXDBG_CLNT_ID pClnt, VXDBG_CTX * pCtx);
extern STATUS		vxdbgBpAdd (VXDBG_CLNT_ID pClnt, VXDBG_CTX * pBpCtx,
					UINT16 bpAccessType,
					VXDBG_BP_ACTION bpAction,
					VXDBG_BP_CALL_RTN bpCallRtn,
					_Vx_usr_arg_t bpCallArg, void * bpAddr,
					VXDBG_BP_ATTR bpAttr, UINT32 bpCount,
					VXDBG_BP_ID * pBpId);
extern STATUS           vxdbgHwBpAdd (VXDBG_CLNT_ID pClnt, VXDBG_CTX * pBpCtx,
					UINT32 accessSize,
                                        VXDBG_HWBP_ACCESS_TYPE accessType,
					VXDBG_BP_ACTION bpAction,
					VXDBG_BP_CALL_RTN bpCallRtn,
					_Vx_usr_arg_t bpCallArg, void * bpAddr,
					VXDBG_BP_ATTR bpAttr, UINT32 bpCount,
					VXDBG_BP_ID * pBpId);
extern STATUS           vxdbgHwBpTypeValidate (
                                        VXDBG_HWBP_ACCESS_TYPE accessType,
                                        UINT32 accessSize);
extern STATUS		vxdbgBpDelete (VXDBG_BP_DEL_INFO bpInfo);

extern STATUS		vxdbgEventInject (VXDBG_EVT_ID pEvtId,
					void (*evtCallBack) (void * pEvtData),
					void * pEvtData);
extern BOOL		vxdbgEventCancel (VXDBG_EVT_ID pEvtId);
extern VXDBG_EVT_ID	vxdbgEventIdAlloc (void);
extern void		vxdbgEventIdFree (VXDBG_EVT_ID pEvtId);

extern size_t		vxdbgMemRead (void * pAdd, void * pBuf,
						size_t nBytes, size_t width);
extern size_t		vxdbgMemWrite (void * pAdd, void * pBuf,
						size_t nBytes, size_t width);
extern size_t		vxdbgMemMove (void * pAdd, void * pBuf, size_t nBytes);
extern STATUS		vxdbgMemScan (void * pAdd, void * pPat, size_t nBytes);
extern STATUS           vxdbgMemProbe (void * addr, size_t size, int mode,
                                       int width, BOOL preserve,
                                       size_t * pValidSize,
                                       size_t * pInvalidSize);
#ifdef	_WRS_CONFIG_SMP
extern STATUS		vxdbgRegsShow (VXDBG_CLNT_ID pClnt, VXDBG_CTX * pCtx);
extern VXDBG_BP_INFO *	vxdbgBpEach (VXDBG_BP_EACH_RTN rtn, _Vx_usr_arg_t arg);
#endif	/* _WRS_CONFIG_SMP */

extern STATUS		vxdbgBpAddrCheck (RTP_ID memCtx, INSTR * addr,
					INSTR * val);
extern BOOL		vxdbgInstrCmp (INSTR *, INSTR instr, INSTR mask);

extern int		wdbDbgTraceModeSet (REG_SET * pRegs);
extern void		wdbDbgTraceModeClear (REG_SET * pRegs, int traceData);
extern BOOL		wdbDbgSysCallCheck (REG_SET * pRegs);
#if	DBG_NO_SINGLE_STEP
extern INSTR *		wdbDbgGetNpc (REG_SET * pRegs);
#endif	/* DBG_NO_SINGLE_STEP */

#if 	DBG_HARDWARE_BP
extern void		wdbDbgRegsSet (DBG_REGS * pDbgReg);
extern void		wdbDbgRegsClear (void);

extern STATUS		wdbDbgHwBpSet (DBG_REGS * pDbgRegs, UINT16 type,
					void * addr);
extern STATUS		wdbDbgHwBpFind (DBG_REGS *  pDbgRegs, UINT16 * pType,
					void ** pAddr);
extern STATUS		wdbDbgHwAddrCheck (void * addr, UINT16 type,
					FUNCPTR memProbeRtn);
extern STATUS           vxdbgHwBpTypeGet (
                                        VXDBG_HWBP_ACCESS_TYPE vxdbgAccessType,
                                        UINT32 accessSize,
                                        UINT16 * pHwAccessType);
#if     VXDBG_HAS_HW_BP_SUPPORT_CHECK
extern BOOL             vxdbgHwBpSupportEnabled (void);
#endif 	/* VXDBG_HAS_HW_BP_SUPPORT_CHECK */
#endif 	/* DBG_HARDWARE_BP */
extern STATUS		wdbDbgAddrCheck (void * addr);
extern STATUS		vxdbgBpUserKeySet (VXDBG_CLNT_ID pClnt,
					   VXDBG_BP_ID vxdbgBpId,
					   void * userKey);
extern STATUS		vxdbgBpUserKeyGet (VXDBG_CLNT_ID pClnt,
					   VXDBG_BP_ID vxdbgBpId,
					   void ** pUserKey);

extern BOOL             vxdbgIsAttached (VXDBG_CLNT_ID pClnt, VXDBG_CTX * pCtx);
extern BOOL             vxdbgIsBpAddr (VXDBG_CLNT_ID pClnt, void * addr,
                                       VXDBG_CTX * pCtx);

#if (CPU_FAMILY == PPC) && (defined (_WRS_CONFIG_LP64))
extern void *           vxdbgLepFind (void * gep, RTP_ID rtpId); 
#endif 

/************************************************************************
*
* vxdbgListInsert - insert a node in a list after a specified node
*
* This routine inserts a specified node in a specified list.
* The new node is placed following the list node <pPrev>.
* If <pPrev> is NULL, the node is inserted at the head of the list.
*
* RETURNS: N/A
*/

_WRS_INLINE void vxdbgListInsert
    (
    FAST LIST *	pList,	/* pointer to list descriptor */
    FAST NODE *	pPrev,	/* pointer to node after which to insert */
    FAST NODE *	pNode	/* pointer to node to be inserted */
    )
    {
    FAST NODE *	pNext;

    if (pPrev == NULL)
	{				/* new node is to be first in list */
	pNext = pList->node.next;
	pList->node.next = pNode;
	}
    else
	{				/* make prev node point fwd to new */
        pNext = pPrev->next;
	pPrev->next = pNode;
	}

    if (pNext == NULL)
	pList->node.previous = pNode;	/* new node is to be last in list */
    else
	pNext->previous = pNode;	/* make next node point back to new */

    /* set pointers in new node, and update node count */

    pNode->next		= pNext;
    pNode->previous	= pPrev;
    pList->count++;
    }

/**************************************************************************
*
* vxdbgListDelete - delete a specified node from a list
*
* This routine deletes a specified node from a specified list.
*
* RETURNS: N/A
*/

_WRS_INLINE void vxdbgListDelete
    (
    FAST LIST *pList,	/* pointer to list descriptor */
    FAST NODE *pNode	/* pointer to node to be deleted */
    )
    {
    if (pNode->previous == NULL)
	pList->node.next = pNode->next;
    else
	pNode->previous->next = pNode->next;

    if (pNode->next == NULL)
	pList->node.previous = pNode->previous;
    else
	pNode->next->previous = pNode->previous;

    /* update node count */

    pList->count--;
    }
#endif	/* _ASMLANGUAGE */
#ifdef __cplusplus
}
#endif

#endif	/* __INCvxdbgLibPh */
