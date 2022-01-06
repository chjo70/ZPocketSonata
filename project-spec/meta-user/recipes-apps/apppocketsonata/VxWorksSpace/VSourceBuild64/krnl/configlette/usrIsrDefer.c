/* usrIsrDefer.c - ISR deferral configuration file */

/*
 * Copyright (c) 2007, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
25apr16,pmr  make ISR deferral task stack size configurable (V7SP-978)
07may07,h_k  made the global ISR deferral mode configurable.
02mar07,h_k  removed obsoleted code.
07feb07,h_k  written.
*/

/*
DESCRIPTION

User configurable ISR deferral library intialization.
*/

#ifndef	ISR_DEFER_MODE
#define ISR_DEFER_MODE		ISR_DEFER_MODE_PER_CPU
#endif	/* ISR_DEFER_MODE */

#ifndef	ISR_DEFER_TASK_STACK_SIZE
#define ISR_DEFER_TASK_STACK_SIZE	8192
#endif	/* ISR_DEFER_TASK_STACK_SIZE */

void usrIsrDeferInit (void)
    {
    isrDeferLibInit (ISR_DEFER_MODE, ISR_DEFER_TASK_STACK_SIZE);
    }
