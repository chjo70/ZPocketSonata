/* workQLibP.h - private kernel work queue header file */

/*
 * Copyright (c) 1992, 2000, 2004, 2006, 2008-2010, 2017
 * Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
/*
modification history
--------------------
30jan17,cww  Added workQPanicCheck
16aug10,cww  Use dynamically generated offsets in offset macros
29apr10,pad  Moved extern C statement after include statements.
05nov09,jpb  Updated isrTag type.
30jul09,gls  added _WRS_WORK_Q_WORK_IN_PROGRESS() (Defect WIND00153717)
29may09,cww  Changed 3rd param in workQAdd2
20feb09,cww  Add LP64 support
27aug08,jpb  Renamed VSB header file
24jun08,jpb  Added include path for kernel configurations options set in
             vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
05dec06,jln  replace UINT16 with UINT32 for read/write index
14sep06,gls  cleaned up VX_KERNEL_VARS support
09aug06,mmi  ported workQ to SMP
03may04,cjj  Mods for code inspection of version 01d.
	     Removed useless WORK_JOB_BASE.
21apr04,cjj  Mods for configurable workQ size
18dec00,pes  Correct compiler warnings
22sep92,rrr  added support for c++
04jul92,jcf  extracted from v2i of wind.h.
*/

#ifndef __INCworkQLibPh
#define __INCworkQLibPh

#ifndef	_ASMLANGUAGE
#include <vxWorks.h>
#include <vsbConfig.h>
#include <vwModNum.h>
#ifdef	_WRS_CONFIG_SMP
#include <private/vxSmpP.h>
#endif	/* _WRS_CONFIG_SMP */

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

typedef void (* WORK_Q_ADD_0_FUNC) (void);
typedef void (* WORK_Q_ADD_1_FUNC) (void *);    
typedef void (* WORK_Q_ADD_2_FUNC) (void *, _Vx_usr_arg_t);  

typedef struct		/* JOB */
    {
    WORK_Q_ADD_2_FUNC function;	/* 0x00/0x00: function to invoke */
    void *	      arg1;	/* 0x04/0x08: argument 1 */
    _Vx_usr_arg_t     arg2;	/* 0x08/0x16: argument 2 */
    ULONG 	      isrTag;	/* 0x12/0x24: tag of ISR that queued up work */
    } JOB;

/* variable declarations */

/* 
 * In SMP, since WORK_Q_IX structure is embedded in <kernelVars>, 
 * the structure is within the cache line since <kernelVars> is 
 * expected to be in a cache line. 
 */

/*
 * The bitmask member of WORK_Q_IX is always used whenever one
 * or the other index is used so it is located between them to ensure
 * it will at least be in the same cache line as one of them.
 */

typedef struct
    {
    volatile    UINT32 read;	/* workQ read index */
    UINT32             bitmask; /* workQ index bitmask */
    volatile    UINT32 write;   /* workQ write index */
    } WORK_Q_IX;

#ifdef _WRS_CONFIG_SMP
extern JOB   pJobPool[][VX_MAX_SMP_CPUS]; /* pointer to a row of 2xD array */
#else /* _WRS_CONFIG_SMP */
extern WORK_Q_IX	workQIx;	/* workQ indices struct */
extern JOB 		pJobPool[];	/* pool of memory for jobs */
extern volatile BOOL    workQIsEmpty;	/* TRUE if work queue is empty */
#endif

extern char*     (*_func_workQDbgTextDump) (void *, BOOL, BOOL);

extern int              workQWorkInProgress; /* CPU ID of core procesing */
                                             /* the work queue */

extern FUNCPTR          workQPanicHook; /* undocumented hook for */
					/* testing/debugging */

/* function declarations */

extern void	workQInit	(UINT queueSize);
extern void	workQDoWork	(void);
extern void	workQPanic	(void);
extern STATUS   workQPanicCheck (int key);
extern void	workQAdd0 	(WORK_Q_ADD_0_FUNC func);
extern void	workQAdd1 	(WORK_Q_ADD_1_FUNC func, void * arg1);
extern void	workQAdd2 	(WORK_Q_ADD_2_FUNC func,
                                 void * arg1, 
                                 _Vx_usr_arg_t arg2);

#ifdef __cplusplus
}
#endif

#else	/* _ASMLANGUAGE */

/*
 * offset macros must be in an ASM section due to a circular dependency when
 * compiling offsets.c
 *
 * WARNING: the old offset macros are provided temporarily only for a
 * transitionary phase.  They will be removed once existing references are
 * updated to use the dynamically generated offsets.
 */

#ifndef _WRS_CONFIG_LP64
#define JOB_FUNCPTR	JOB_function_OFFSET
#define JOB_ARG1	JOB_arg1_OFFSET
#define JOB_ARG2	JOB_arg2_OFFSET
#define JOB_ISR_TAG	JOB_isrTag_OFFSET

#define WORK_READ_IX	WORK_Q_IX_read_OFFSET
#define WORK_BITMASK	WORK_Q_IX_bitmask_OFFSET
#define WORK_WRITE_IX	WORK_Q_IX_write_OFFSET
#endif /* _WRS_CONFIG_LP64 */

#endif	/* _ASMLANGUAGE */

#endif /* __INCworkQLibPh */
