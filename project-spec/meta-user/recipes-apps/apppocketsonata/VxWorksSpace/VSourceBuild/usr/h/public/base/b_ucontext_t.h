/* b_ucontext.h - base type ucontext_t definition header */

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

#ifndef __INCb_ucontexth
#define __INCb_ucontexth

#include <base/b_mcontext_t.h>
#include <base/b_sigset_t.h>
#include <base/b_stack_t.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _DEFINED_ucontext_t
#define _DEFINED_ucontext_t

typedef struct ucontext
    {
    mcontext_t          uc_mcontext;    /* register set */
    struct ucontext *   uc_link;        /* not used */
    sigset_t            uc_sigmask;     /* set of signals blocked */
    stack_t             uc_stack;       /* stack of context signaled */
    } ucontext_t;

#endif  /* !_DEFINED_ucontext_t */

#ifdef __cplusplus
}
#endif
#endif

