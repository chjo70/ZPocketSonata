/* coprocLibP.h - coprocessor management library private header */

/*
 * Copyright (c) 2003, 2004, 2006, 2009-2012, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
04mar15,pfl  Cert: addressed FlexeLint warnings
17feb15,dot  V7COR-2604 - Fix warnings when building VSB based on itl_64_vx7 BSP.
31aug12,jmp  Re-introduced a COPROCS_ALL macro to avoid backward
             compatibility issue when rebuilding a project created for
             a release older than 6.9.2.2.
15may12,jmp  CQID: Fix WIND00309977 : Removed obsolete COPROCS_ALL macro.
02nov11,swu  add _func_fppTaskRegsShow. (WIND00245382)
28jun10,jc0  add protoTypes in coproLibP.h header file (WIND00211499).
29apr10,pad  Moved extern C statement after include statements.
17sep09,cww  Use fully qualified pointers in COPROC_DESC
28may09,cww  Add LP64 support
31aug06,zl   Removed pLastTask from COPROC_DECS and added pLastEntry
02oct04,yvp  Added new members to COPROC_DESC for mRegs support.
21mar03,yvp  written.
*/

#ifndef __INCcoprocLibPh
#define __INCcoprocLibPh

#ifndef	_ASMLANGUAGE

#include <vxWorks.h>
#include <fppLib.h>
#include <taskLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define COPROCS_MAX        8       /* Max. number of coprocessors per task */

/* Coprocessor option bits occupy the upper 8 bits of the task option word */

#define COPROC_FIELD_MASK  \
    (VX_COPROC1_TASK | VX_COPROC2_TASK | VX_COPROC3_TASK | VX_COPROC4_TASK | \
     VX_COPROC5_TASK | VX_COPROC6_TASK | VX_COPROC7_TASK | VX_COPROC8_TASK )

/*
 * The following macro is no longer use since VxWorks 6.9.2.2 release.
 * However, it must exist to avoid backward compatibility issue when rebuilding
 * a project created for a release older than 6.9.2.2.
 */
#define COPROCS_ALL	COPROC_FIELD_MASK

/* generic status codes */

#define S_coprocLib_ALLOC_FAILED                  (M_coprocLib | 1)
#define S_coprocLib_COPROC_ENABLE_FAILED          (M_coprocLib | 2)
#define S_coprocLib_COPROC_DISABLE_FAILED         (M_coprocLib | 3)
#define S_coprocLib_EXCHANDLER_REGISTER_FAILED    (M_coprocLib | 4)
#define S_coprocLib_HOOK_ATTACH_FAILED            (M_coprocLib | 5)
#define S_coprocLib_INVALID_ARGUMENT              (M_coprocLib | 6)
#define S_coprocLib_INVALID_OPERATION             (M_coprocLib | 7)
#define S_coprocLib_NO_COPROC_SUPPORT             (M_coprocLib | 8)

/* Function pointer types */

typedef void * (*COPROC_CTX_CREATE_RTN)(TASK_ID tid);
typedef STATUS (*COPROC_CTX_DELETE_RTN)(void *pCtx);
typedef STATUS (*COPROC_ENABLE_RTN)(void);
typedef STATUS (*COPROC_DISABLE_RTN)(void);
typedef void   (*COPROC_CTX_SAVE_RTN)(void *pCtx);
typedef void   (*COPROC_CTX_RESTORE_RTN)(void *pCtx);
typedef void   (*COPROC_CTX_GET_RTN)(void *pCtx, void *pRegSet);
typedef void   (*COPROC_CTX_SET_RTN)(void *pRegSet, void *pCtx);
typedef STATUS (*COPROC_EXC_HANDLER_REGISTER_RTN)(void);
typedef void   (*COPROC_CTX_SHOW_RTN)(void *pCtx);
typedef STATUS (*COPROC_MREGS_RTN)(TASK_ID tid, void *pCtx, char *regName, 
				   BOOL *pFound);
typedef void   (*COPROC_REG_LIST_SHOW_RTN)(void);

/* Coprocessor Descriptor structure */

typedef struct coprocDesc 
    {
    struct coprocDesc * next;              /* next descriptor in list */
    size_t ctxSize;                   	   /* context size in bytes */
    size_t ctxAlign;                  	   /* memory alignment for context */
    COPROC_CTX_CREATE_RTN  pCtxCreateRtn;  /* allocate & init coprocessor ctx */
    COPROC_CTX_DELETE_RTN  pCtxDeleteRtn;  /* delete the coprocessor ctx */
    COPROC_ENABLE_RTN      pEnableRtn;     /* enable the coprocessor */
    COPROC_DISABLE_RTN     pDisableRtn;    /* disable the coprocessor */
    COPROC_CTX_SAVE_RTN    pCtxSaveRtn;    /* context save routine */
    COPROC_CTX_RESTORE_RTN pCtxRestoreRtn; /* context restore routine */
    COPROC_CTX_GET_RTN 	   pCtxGetRtn;	   /* get the coprocessor context */
    COPROC_CTX_SET_RTN     pCtxSetRtn;     /* set the coprocessor context */
    FUNCPTR pDsmRtn;                   	   /* disassembly routine */
    COPROC_EXC_HANDLER_REGISTER_RTN pExcHandlerRegisterRtn;   /* register exc.
                                                                 handlers */
    COPROC_CTX_SHOW_RTN    pShowRtn;       /* show the coprocessor context */
    FUNCPTR pAboutRtn;                 	   /* displays a short description */
    COPROC_MREGS_RTN       pMRegsRtn;	   /* interactively modify reg values */
    COPROC_REG_LIST_SHOW_RTN pRegListShowRtn;	/* show list of available 
						   registers */
    struct coprocTblEntry * pLastEntry; /* last TblEntry to use this coproc. */
    UINT32 mask;                   	/* bit mask position in task option */
    BOOL   showOnDebug;            	/* show registers on debug events */
    ULONG spare1; 
    ULONG spare2; 
    } COPROC_DESC;  

/* Coprocessor Table Entry structure */

typedef struct coprocTblEntry
    {
    void *           pCtx;              /* points to coprocessor REG_SET */
    COPROC_DESC *    pDescriptor;       /* points to associated descriptor */
    struct windTcb * pTask;		/* points back to the task's TCB */
    } COPROC_TBL_ENTRY;
    
/* Globals */    

extern COPROC_DESC *pCoprocDescList;
#if defined (_WRS_PAL_COPROC_LIB)
extern void (*_func_coprocShow)(void);
extern void (*_func_coprocTaskRegsShow)(TASK_ID tid, int mask);
#if defined (_WRS_DSP_SUPPORT)
extern FUNCPTR     _func_dspProbe;
#endif /* _WRS_DSP_SUPPORT */
#else /* !_WRS_PAL_COPROC_LIB */
extern void (*_func_fppTaskRegsShow)(TASK_ID);
extern FUNCPTR     _func_sseTaskRegsShow;
#ifdef _WRS_ALTIVEC_SUPPORT
extern FUNCPTR     _func_altivecTaskRegsShow;
extern FUNCPTR     _func_altivecProbe;
#endif /* _WRS_ALTIVEC_SUPPORT */
#ifdef _WRS_SPE_SUPPORT
extern FUNCPTR     _func_speTaskRegsShow;
#endif /* _WRS_SPE_SUPPORT */
#endif /* _WRS_PAL_COPROC_LIB */
    
/* function declarations */

STATUS coprocLibInit (void);
void   coprocShowInit (void);
STATUS coprocEnable (int);
STATUS coprocDisable (int);
void   coprocTaskCreateHook (WIND_TCB *);
void   coprocTaskDeleteHook (WIND_TCB *);
void   coprocTaskSwapHook (WIND_TCB *, WIND_TCB *);
STATUS coprocTaskRegsGet (TASK_ID, int, void *);
STATUS coprocTaskRegsSet (TASK_ID, int, void *);
size_t coprocCtxStorageSizeGet (int);
int    coprocShowOnDebug (BOOL, int);
IMPORT void   coprocSave (int);
void   coprocShow (void);
void   coprocTaskRegsShow (TASK_ID, int);
void * coprocCtxReplicate (TASK_ID, int);
STATUS coprocMRegs (TASK_ID, char *, BOOL *);
void   coprocRegListShow (void);
extern void coprocsDiscover (UINT32 *);
extern void coprocDescriptorsInit (COPROC_DESC *);

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCcoprocLibPh */
