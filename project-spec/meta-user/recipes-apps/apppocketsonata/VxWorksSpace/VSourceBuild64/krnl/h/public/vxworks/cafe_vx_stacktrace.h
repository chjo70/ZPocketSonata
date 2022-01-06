/* cafe_vx_stacktrace.h - header for Cafe stacktrace */

/*
 * Copyright (c) 2011-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#ifndef __cafe_vx_stacktraceh
#define __cafe_vx_stacktraceh

#include <st_stacktrace.h>
#include <vxworks/cafe_vx_types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Markers for user or kernel functions in stacktrace */
#define VXWORKS_CONTEXT_KERNEL (unsigned long)-128
#define VXWORKS_CONTEXT_USER   (unsigned long)-512

extern unsigned int cafe_vx_stacktrace(const REG_SET *regs, TASK_ID_TYPE tid,
				       void *stack[], unsigned int max_depth,
				       unsigned int skip);
#ifdef __cplusplus
}
#endif


#endif /* __cafe_vx_stacktraceh */
