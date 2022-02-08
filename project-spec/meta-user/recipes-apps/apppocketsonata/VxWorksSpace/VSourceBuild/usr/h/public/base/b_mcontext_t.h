/* b_struct_mcontext.h - base type mcontext definition header */

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
1a,30mar12,jpb  Created.
*/

#ifndef __INCb_struct_mcontexth
#define __INCb_struct_mcontexth

#include <regs.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _DEFINED_struct_mcontext_t
#define _DEFINED_struct_mcontext_t

typedef struct mcontext
    {
#ifdef _WRS_KERNEL
    REG_SET         regs;
#else
    _Vx_REG_SET     regs;
#endif /* _WRS_KERNEL */
    } mcontext_t;

#endif  /* _DEFINED_struct_mcontext_t */

#ifdef __cplusplus
}
#endif
#endif

