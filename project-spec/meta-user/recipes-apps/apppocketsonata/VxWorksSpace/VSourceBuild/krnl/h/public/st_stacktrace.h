/* Copyright (c) 2001-2011, 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
16jan15,wzc  ppc64 support.(US49903)
*/

#if !defined(__st_stacktrace_h)
#define __st_stacktrace_h

#include <st_status.h>
#include <st_stdbool.h>
#include <st_arch.h>       /* for USES_[FP,SP] definitions */
/* pull in definition of REG_SET struct */
#if defined(__VXWORKS__)
#  include <vxWorks.h>
#  include <regs.h>
#elif defined(__linux__)
#  include <st_regs.h>
#endif
#if defined(__VXWORKS__)
#  include <private/rtpLibP.h>   /* for RTP_ID struct definition */
#endif

#ifdef __cplusplus
    extern "C" {
#endif

/* A simple range of target addresses.*/
typedef struct {
    ST_TARGET_ADDR_T pStart;
    ST_TARGET_ADDR_T pEnd;
} ADRS_RANGE;

#if defined(__linux__) && !defined(MODULE)
#include "st_linuxutils.h"  /* for MemoryMap definition */
/**
 *  Specifies the memory map for the current process.  This map is used
 * to validate the memory the Context package scans, and so should be kept
 * up to date with respect to the current process.  Before setting the
 * memory map with this function, only trivial address validation is
 * performed.  Passing zero as the argument also achieves this effect.
 *
 * Note:  this function is not thread safe.  It is the user of the Context
 *        package that is responsible for ensuring updates to a process'
 *        memory map are atomic with respect to calling CallingContextGet().
 */
extern void ST_SetMmap(const MemoryMap * map);
#endif  /* if defined(__linux__) && !defined(MODULE) */

/**
 *  The crawl_validation structure holds values which are used to expidite
 * validation of target addresses.  For example, the "tid" member can be used
 * to determine stack bounds, making validation of stack addresses trivial.
 * Task id (tid) is represented as an unsigned long, since Vx tids are
 * pointers, using the unsigned long type makes sure there's enough bitwidth
 * available for storage.
 */
typedef struct {
    unsigned long tid;
    ADRS_RANGE txtRng;
} crawl_validation;

extern unsigned int SUTILS_CONTEXT_LIB_VERSION;


/**
 * ST_context - this should be passed in and out of the
 *   Context package, but its members should not be accessed
 *   by external packages.  They are subject to change.
 */
typedef struct
{
    ST_TARGET_ADDR_T pc;    /* Program counter for this context */
#if RTITOOLS_CONTEXT_USES_FP
    void *       fp;    /* Frame pointer for this context */
#endif
#if RTITOOLS_CONTEXT_USES_SP
    void *       sp;    /* Stack pointer for this context */
#endif

    unsigned long gpregs[NUM_GPREGS];  /* general purpose registers used for
                                          tracing.  These are only valid for
                                          the first call frame. */

    bool       leaf;  /* false if no possibility of being a leaf */

    bool       firstInstruction; /* == true if we are at the first
                                  * instruction of a function */

    unsigned int  patchDepth;  /* counts number of patched functions we've
                                * passed through to get to this call stack
                                * frame. Needed to accurately trace callstacks
                                * with one patched function recursively calling
                                * itself and another patched function.
                                * Trust me. */

    crawl_validation validation_parms;   /* currently valid PC text range and 
                                            task id for this context */
#if defined(__VXWORKS__)
    unsigned int  taskStat;   /* task status; see defs for ST_TASK_xxx */
    RTP_ID        oldCtx;     /* non-NULL if context switched to user mode */
#endif
} ST_context;


/**
* ST_context_create - create a context for specified thread/task
*
* DESCRIPTION
* This routine creates a task context by initializing the specified
* ST_context structure with task-specific information captured
* on a task stack.
*
#if VXWORKS_VERSION_6_0_OR_BETTER
* If the task is a user application in an RTP, the calling tool's context
* is switched to that of the task so that the full task context is visible
* to the tool.
*
#endif
* When use of the specified ST_context structure is finished, the
* ST_context_delete() routine must be called so that the proper
* tool context is restored.  Failure to do this can cause a system crash!
*
* RETURNS: true if context created, false if error.
*
* ERRNOS:
* no errnos for this routine
*
* SEE ALSO: ST_context_delete()
*/
extern bool ST_context_create(
    const REG_SET * const    regs,          /* regs stored on stack */
    const unsigned long      tid,           /* ID of task owning context */
    const bool            firstInstruction, /* 1st instr of patched func */
    ST_context * const ctx);                /* context struct to initialize */


/**
* ST_context_delete - delete context for specified thread
*
* DESCRIPTION
* This routine deletes a task context by clearing key information in the
* specified ST_context structure.
*
#if VXWORKS_VERSION_6_0_OR_BETTER
* If the context was for a user application task in an RTP, the calling
* tool's context is restored.
*
#endif
* When use of the specified ST_context structure is finished, this
* routine must be called so that the proper tool context is restored.
* Failure to do this can cause a system crash!
*
* CAVEAT: No input arg checking; assumes caller does not pass NULL pointers!
*
* RETURNS: true if context deleted, false if error.
*
* ERRNOS
* no errnos for this routine
*
* SEE ALSO: ST_context_create()
*/
extern bool ST_context_delete(ST_context * const ctx);


/**
 * context_status ST_CallingContextGet(ST_context *child, 
                                       ST_context *parent)
 * Description:  Given the context 'child', discover the calling context
 *               and place the result in 'parent'.
 * Preconditions:  child != null, parent != null
 * Postconditions: if no error, parent is ready to be acted upon.  if error,
 *                 parent does not contain valid data.
 * Returns: ST_CONTEXT_OK on no error; ST_CONTEXT_TOP if the 
 *   top of the call stack has been reached; ST_CONTEXT_ERROR if the 
 *   calling context could not be discovered, or other error has occurred.
 *   Side effects:  May crash target or task if the memory access is bad and
 *   undetected.  This usually happens if the call stack is something we
 *   don't recognize and can't detect that we don't recognize it.
 */
extern context_status ST_CallingContextGet(ST_context * child,
                                           ST_context * parent);

extern void *  stKTxtEnd;

extern void *  stKTxtStart;


/**
* ST_context_init - initialize the context library
*
* DESCRIPTION
* This routine initializes the context library by establishing the start and
* end addresses of the kernel text region for use in the context_memtest
* module.  It also records the MMU page size, if available.
*
* RETURNS: true if context initialized, false if kernel text start or
* end address is NULL.
*
* ERRNOS
* no errnos for this routine
*/
extern bool ST_context_init(void * textStartAdrs, void * textEndAdrs);


/**
* ST_context_uninit - uninitialize the context library
*
* DESCRIPTION
* This routine uninitializes the context library by clearing the start and
* end addresses of the kernel text region for use in the context_memtest
* module.
*
* RETURNS: true if context uninitialized, false if any errors.
*
* ERRNOS
* no errnos for this routine
*/
extern bool ST_context_uninit(void);


/**
 *  This routine's sole purpose is to serve as a flag symbol to be used by
 * ST_perform_stack_trace() when we detect an error and cannot provide the
 * complete stack trace.
 */
extern void ST_trace_error(void);


/**
 *  This routine's sole purpose is to serve as a flag symbol to be used by
 * ST_perform_stack_trace() when we detect an incomplete stack trace.
 */
extern void ST_trace_truncated(void);


/**
 *  Given a Context structure (initialized using ContextCreate), iterate over
 * the described stack and populate the passed "stack" array with the return
 * addresses of each frame.  This routine will not write more than "depth"
 * entries to "stack".
 * Returns the number of entries written to "stack".
 */
extern unsigned int ST_perform_stack_trace(ST_context *context,
                                           void *stack[],
                                           const unsigned int depth);

#if defined(__VXWORKS__)

/**
 *  Given a Context structure, return true if the task is an RTP task,
 * and is executing a system call
 */
extern bool ST_task_in_sys_call(const ST_context *const context);

/**
 *  Given a Context structure, return true if the task is an RTP task and
 * is in user mode.
 */
extern bool ST_task_is_rtp_task(const ST_context *const context);

/**
 *  Given a Context structure, return true if the task is a kernel task,
 * and is executing normally.
 */
extern bool ST_task_is_kernel_task(const ST_context *const context);

/**
 *  Given a Context structure, return true if the task is a kernel task
 * executing exception code.
 */
extern bool ST_task_in_exc_mode(const ST_context *const context);

#endif /* __VXWORKS__ */

#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif  /* if !defined(__st_stacktrace_h) */
