/* trcLibP.h - private trace library header file */

/*
 * Copyright (c) 2004, 2007-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01k,07oct10,jmp  Fixed TRC_MEM_INST_READ() macro to call
                 VXDBG_MEM_WIDTH_READ() without specifying a width since this
                 macro can be used on address which are not aligned on the
                 size of the specified type (CQ:WIND00234981).
01j,28apr10,pad  Moved extern C statement after include statements.
01i,11feb10,rlp  Added vxdbgLibP header file.
01h,07jul09,rlp  Replaced VXDBG_MEM_READ macro with VXDBG_MEM_WIDTH_READ
                 (WIND000171075).
01h,13may09,jpb  Updated for LP64 support.
01g,27aug08,jpb  Renamed VSB config file.
01f,24jun08,jpb  Added include path for kernel configurations options set in
                 vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
01e,30apr07,jmp  added TRC_MEM_INST_READ() and TRC_INST_CMP() macros.
01d,14may04,zl   reordered TRC_LIB_FUNCS fields.
01c,02apr04,jmp  added pc argument to TRC_LVL_ARGS_GET().
01b,19mar04,zl   updated for user build.
01a,18feb04,zl 	 created
*/

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef __INCtrcLibPh
#define __INCtrcLibPh


#include <vxWorks.h>
#ifdef _WRS_KERNEL
#include <vsbConfig.h>
#include <regs.h>
#include <private/syscallLibP.h>
#include <private/vxdbgLibP.h>
#endif /* _WRS_KERNEL */

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/*
 * Defines macros to read and compare the instruction at a given address.
 * VXDBG_MEM_WIDTH_READ() is used to hide persistent breakpoints and/or
 * dynamic printf that could be set at the address to read.
 *
 * NOTE: For now, VXDBG_MEM_WIDTH_READ() is only used in the kernel
 * (_WRS_KERNEL).
 *	 This means that invoking the stack trace library from user land
 *	 can results in an incorrect stack trace if breakpoints (persistents,
 *	 dynamic printf) are set on the code beeing traced.
 *	 This issue could be fixed by creating a system call for vxdbgMemRead().
 */

#if (defined(_WRS_CONFIG_SMP) && defined (_WRS_KERNEL))
#define TRC_MEM_INST_READ(src,dest,type)	\
			VXDBG_MEM_WIDTH_READ((void *)src, \
					(void *)dest,sizeof(type),0)
#else	/* _WRS_CONFIG_SMP & _WRS_KERNEL */
#define TRC_MEM_INST_READ(src,dest,type)	(*(type *)dest = *(type *)src)
#endif	/* _WRS_CONFIG_SMP & _WRS_KERNEL */

#define	TRC_INST_CMP(addr,inst,mask)	((*(addr) & (mask)) == (inst))

#ifndef	_ASMLANGUAGE

/* structure passed to the arch primitives */

typedef struct trc_os_ctx
    {
    char *		stackBase;	/* stack base */
    char *		stackEnd;	/* stack end */
    STATUS (*pcValidateRtn)		/* routine to validate PC */
            (INSTR * 	 pc,		/* PC to validate */
	     struct trc_os_ctx * pCtx	/* OS info structure */
	    );
#ifdef _WRS_KERNEL
    REG_SET *		pRegs;		/* register set */
    BOOL		isSyscall;	/* TRU if tracing a system call */
#endif
    } TRC_OS_CTX;

/* structure passed to OS trace routine */

typedef struct trc_ctx
    {
    STATUS (*usrRtn)(INSTR * callAdrs, INSTR *	funcAdrs, int nArgs, 
	             _Vx_usr_arg_t * args, TASK_ID taskId, BOOL isKernelAdrs, 
	             void * usrCtx);
    TASK_ID	    taskId;
    BOOL	    isKernelAdrs;
    TRC_OS_CTX *    pOsCtx;
    void *	    usrCtx;
    int		    nArgs;
    _Vx_usr_arg_t * pArgs;
    BOOL	    verbose;
    } TRC_CTX;

/* primitives provided by architecture specific trace libraries */

typedef STATUS (* TRC_LVL_INFO_GET) (char * fp, INSTR * pc, TRC_OS_CTX * pCtx,
				     char ** pPrevFp, INSTR ** pPrevPc, 
				     INSTR ** pFuncAddr);
typedef int (* TRC_LVL_ARGS_GET) (INSTR * pc, INSTR * funcAddr, char * fp, 
				  _Vx_usr_arg_t pArgBuf[], int argMax, 
				  _Vx_usr_arg_t ** ppArgs);

#ifdef _WRS_KERNEL
typedef STATUS (* TRC_TOP_INFO_GET) (TRC_OS_CTX * pCtx, char ** pFp, 
				     char ** pPrevFp, INSTR ** pPrevPc, 
				     INSTR ** pFuncAddr);

typedef void (* TRC_SYSCALL_CHECK) (SYSCALL_ENTRY_STATE * pScState,
				    TRC_OS_CTX * pCtx);
#endif

/* structure for trace library primitives */

typedef struct trc_lib_funcs
    {
    TRC_LVL_INFO_GET	lvlInfoGet;	/* routine to get frame info */
    TRC_LVL_ARGS_GET	lvlArgsGet;	/* routine to get arguments */
#ifdef _WRS_KERNEL
    TRC_TOP_INFO_GET	topInfoGet;	/* routine to get top frame info */
    TRC_SYSCALL_CHECK	syscallCheck;	/* routine check if syscall */
#endif
    } TRC_LIB_FUNCS;

/* private global variable declarations */

extern TRC_LIB_FUNCS trcLibFuncs;

/* private function declarations */

#ifdef _WRS_KERNEL
extern STATUS	trcStackTrace	(REG_SET * pRegs, TRC_CTX * pCtx);
#endif

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCtrcLibPh */
