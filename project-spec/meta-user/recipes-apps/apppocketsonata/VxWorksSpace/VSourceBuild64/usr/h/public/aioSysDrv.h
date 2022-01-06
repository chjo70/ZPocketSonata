/* aioSysDrv.h - AIO system driver header file */

/*
 * Copyright (c) 1993, 1994, 2004, 2005, 2010, 2014, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
08mar16,dlk  Shared build for user space and kernel space.
10feb14,cww  made aio tasks unbreakable (VXW7-1221)
24jun10,jxu  LP64: changed API  STATUS aioSysInit (int, int, int) to
             STATUS aioSysInit (int, int, size_t);
28apr10,pad  Moved extern C statement after include statements.
07feb05,hya  added missing prototype
30jan04,dat  Rework for RTP compatibility
12jan94,kdl  changed name from aioSysPxLib to aioSysDrv; general cleanup.
06dec93,dvs  removed S_aioSysPxLib_NO_PIPES
04apr93,elh  written.
*/

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef __INCaioSysDrvh
#define __INCaioSysDrvh

/* includes */

#include <aio.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* project configurable AIO task parameters */

#define AIO_IO_TASKS_DFLT       2               /* number of I/O tasks */
#define AIO_IO_STACK_DFLT       0x7000          /* I/O task stack size */
#define AIO_IO_PRIO_DFLT        50              /* I/O task priority */

/* hardcoded parameters */

#ifdef _WRS_KERNEL
#define AIO_TASK_OPT            VX_UNBREAKABLE  /* task options */
#else
#define AIO_TASK_OPT            0		/* task options */
#endif

#define AIO_WAIT_STACK          0x7000          /* wait task stack size */

/* forward declarations */

extern STATUS aioSysInit (int numTasks, int taskPrio, size_t taskStackSize);
extern STATUS aioSysInsert (struct aiocb *pAiocb, int prio);

#ifdef __cplusplus
}
#endif

#endif /* __INCaioSysDrvh */
