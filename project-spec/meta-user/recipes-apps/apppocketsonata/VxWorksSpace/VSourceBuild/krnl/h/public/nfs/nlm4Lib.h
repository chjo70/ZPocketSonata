/* nlm4Lib.h - NLM protocol library header */

/*
 * Copyright (c) 2003-2004, 2007, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01d,29apr10,pad  Moved extern C statement after include statements.
01c,07jan07,mwv  remove VIRTUAL_STACK support
01b,21jun04,vvv  added virtual stack support
01a,21aug03,snd  written.
*/

#ifndef __INCnlm4Libh
#define __INCnlm4Libh

#include "xdr_nlm4.h"

#ifdef __cplusplus
extern "C" {
#endif

/* nlmLib defaults */

#define NLMD_PRIORITY_DEFAULT  55
#define NLMD_STACKSIZE_DEFAULT 10240

/* IMPORTS */

/* DATA STRUCTURES */

typedef union 
    {
    nlm4_testargs nlmproc4_test_4_arg;
    nlm4_lockargs nlmproc4_lock_4_arg;
    nlm4_cancargs nlmproc4_cancel_4_arg;
    nlm4_unlockargs nlmproc4_unlock_4_arg;
    nlm4_testargs nlmproc4_granted_4_arg;
    nlm4_testargs nlmproc4_test_msg_4_arg;
    nlm4_lockargs nlmproc4_lock_msg_4_arg;
    nlm4_cancargs nlmproc4_cancel_msg_4_arg;
    nlm4_unlockargs nlmproc4_unlock_msg_4_arg;
    nlm4_testargs nlmproc4_granted_msg_4_arg;
    nlm4_testres nlmproc4_test_res_4_arg;
    nlm4_res nlmproc4_lock_res_4_arg;
    nlm4_res nlmproc4_cancel_res_4_arg;
    nlm4_res nlmproc4_unlock_res_4_arg;
    nlm4_res nlmproc4_granted_res_4_arg;
    nlm4_shareargs nlmproc4_share_4_arg;
    nlm4_shareargs nlmproc4_unshare_4_arg;
    nlm4_lockargs nlmproc4_nm_lock_4_arg;
    nlm4_notify nlmproc4_free_all_4_arg;
    } NLMD_ARGUMENT;
 
#if defined(__STDC__) || defined(__cplusplus)

extern STATUS nlmdInit (int priority, int stackSize, 
			  int options);
extern void nlmd (void);

#else 

extern STATUS nlmdInit ();
extern void nlmd ();

#endif	/* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCnlm4Libh */
