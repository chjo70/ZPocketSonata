/* taskDefs.h - Constants and other definitions required by taskLib */

/*
 * Copyright (c) 2005-2006,2008-2010, 2014-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
20may17,dlk  added VX_FLAG_DELETION_ATTEMPT (F5593)
22jan16,h_k  Increased task exception stack size for ARM64. (F5256)
21jul15,h_k  Increased task exception stack size further for PPC64 (F2518)
17feb15,jpb  Increased task exception stack size for PPC64 (V7COR-2452)
16oct14,jpb  Added comment concerning kernel exception stack sizes.
             (Req: WIND00195513)
29apr10,pad  Moved extern C statement after include statements.
19mar09,to   WIND00158413: increase KERNEL_TASK_EXC_STACK_SIZE for x86
07jan08,slk  defect 112288: fix CPU_FAMILY define for MIPS
             KERNEL_TASK_EXC_STACK_SIZE
16may06,pes  Increase KERNEL_TASK_EXC_STACK_SIZE for MIPS builds.
16may06,slk  modified to increase exception stack size for MIPS times 2
15aug05,yvp  written by extracting definitions from taskLib.h & taskLibP.h
*/

#ifndef __INCtaskDefsh
#define __INCtaskDefsh

/* includes */

#include <vxWorks.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* WIND_TCB options bits */

#define VX_USER_MODE		0x0000	 /* INTERNAL: tasks in user mode */
#define VX_SUPERVISOR_MODE	0x0001	 /* INTERNAL: tasks in sup mode */
#define VX_DEALLOC_STACK	0x0004	 /* INTERNAL: deallocate stack */
#define VX_TASK_OBJ_OWNER	0x0800	 /* INTERNAL: task owns objs directly */
#define VX_DEALLOC_EXC_STACK	0x1000	 /* INTERNAL: deallocate the exc stack */
#define VX_DEALLOC_TCB		0x8000	 /* INTERNAL: deallocate the task TCB */

/* WIND_TCB flags bits */

#define VX_FLAG_DELETION_ATTEMPT      0x00000001 /* INTERNAL: deletion attempt */
#define VX_FLAG_DELETION_WAKEUP_DELAY 0x00000002 /* INTERNAL: wake up pure delayed
                                                    task on deletion attempt */

/*
 * These defines are used for tasks that are statically defined using the macro
 * VX_TASK.  Changing the size of exception stacks for non-statically defined
 * kernel tasks should be done in the project settings.
 */

#ifndef	_WRS_ARCH_IS_SIMULATOR
#if (CPU_FAMILY==MIPS) || (CPU_FAMILY==I80X86)
#define KERNEL_TASK_EXC_STACK_SIZE (4096*2)
#elif (CPU_FAMILY == ARM) && (defined (_WRS_CONFIG_LP64))
#define KERNEL_TASK_EXC_STACK_SIZE (4096*2)
#elif (CPU_FAMILY == PPC) && (defined (_WRS_CONFIG_LP64))
#define KERNEL_TASK_EXC_STACK_SIZE (4096*3)
#else /* (CPU_FAMILY != MIPS) || (CPU_FAMILY!=I80X86) || (!(PPC && LP64)) */
#define KERNEL_TASK_EXC_STACK_SIZE (4096)
#endif /* (CPU_FAMILY==MIPS) || (CPU_FAMILY==I80X86) || (PPC & LP64) */
#else /* _WRS_ARCH_IS_SIMULATOR */
#define KERNEL_TASK_EXC_STACK_SIZE (4096*3)
#endif /* _WRS_ARCH_IS_SIMULATOR */


#ifdef __cplusplus
}
#endif

#endif /* __INCtaskDefsh */
