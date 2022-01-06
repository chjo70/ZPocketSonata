/* kernelLockLibP.h - kernellock library private header */

/*
 * Copyright (c) 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * License agreement.
 */

/*
modification history
--------------------
01c,17aug10,cww  Added header file inclusions
01b,27apr10,cww  LP64 adaptation
01a,01may09,pee  created
*/

#include <vxWorks.h>
#include <base/b_atomic_t.h>
#include <private/kernelLockLibP.h>

typedef struct vxKernelLock
    {
    union
	{
	/*
	 * Defect #124069.
	 *
	 * For those architectures that use a reserved load/store conditional
	 * model for atomic operations it is necessary to ensure that <tkt_ctr>
	 * is on its own cache line.
	 */

        char pad [_WRS_KERNEL_LOCK_ALIGN_tkt_ctr];

	atomic_t    tkt_ctr;	/* ticket counter       	     */ 
	} tkt_ctrAligned;

    atomic_t    svc_ctr;	/* ticket currently being serviced   */
    int         cpuIndex;	/* Owner cpu identifier		     */
    int         flags;		/* Reserved for system use           */
#ifdef KERNEL_LOCK_TRACE
    char *	file;		/* file in which lock taken          */
    int		line;		/* line on which lock taken          */
#endif /* KERNEL_LOCK_TRACE */
    } KERNEL_LOCK_VAR _WRS_DATA_ALIGN_BYTES (_WRS_KERNEL_LOCK_VAR_ALIGN);


