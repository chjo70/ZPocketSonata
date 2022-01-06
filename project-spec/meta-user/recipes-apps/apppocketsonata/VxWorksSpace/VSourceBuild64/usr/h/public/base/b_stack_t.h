/* b_stack_t.h - definition of stack_t */

/*
 * Copyright (c) 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
*/

/*
modification history
--------------------
01b,03jul12,jpb  Updated fields to match POSIX specs.
01a,30mar12,jpb  created
*/

#ifndef __INCb_stack_th
#define __INCb_stack_th

#include <base/b_size_t.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _DEFINED_stack_t
#define _DEFINED_stack_t

typedef struct
    {
    void * ss_sp;
    size_t ss_size;
    int    ss_flags;
    } stack_t;

#endif /* _DEFINED_stack_t */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_stack_th */

