/* envLibP.h - private VxWorks environ library header file */

/* 
 * Copyright (c) 2009 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01a,27aug09,cww  Written
*/

#ifndef __INCenvLibPh
#define __INCenvLibPh

#ifdef __cplusplus
extern "C" {
#endif

extern char** (*_func_envGet) (TASK_ID taskId);

#ifdef __cplusplus
}
#endif

#endif /* __INCenvLibPh */
