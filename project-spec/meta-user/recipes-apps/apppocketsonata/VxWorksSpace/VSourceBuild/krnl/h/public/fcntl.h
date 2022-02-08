/* fcntl.h - standard header */

/*
 * Copyright (c) 1991-1992, 2005-2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01m,18may10,pad  Moved extern C statement after include statements.
01l,30mar06,mil  Replaced include vxTypes.h with b_mode_t.h.
01k,28feb06,pes  Remove parameter names in function prototypes (per POSIX).
01j,12feb06,mil  Updated for POSIX namespace conformance (P2).
01i,06aug05,pad  Fixed usage of _WRS_KERNEL macro and updated copyright.
01h,03aug05,hya  added fcntl()
01g,09may05,hya  changed user APIs for POSIX compliance.
01f,22sep92,rrr  added support for c++
01e,18sep92,smb  added prototypes for open and creat.
01d,29jul92,smb  rearranged for the stdio library.
01c,04jul92,jcf  cleaned up.
01b,26may92,rrr  the tree shuffle
01a,05dec91,rrr  written.
*/

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef __INCfcntlh
#define __INCfcntlh

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#include <types/vxANSI.h>
#endif  /* _POSIX_xxx_SOURCE */
#include <sys/fcntlcom.h>
#ifndef _WRS_KERNEL
#include <base/b_mode_t.h>
#endif /* _WRS_KERNEL */

#define	O_NDELAY	_FNDELAY	/* Non-blocking I/O (4.2 style) */

#ifdef __cplusplus
extern "C" {
#endif

int		fcntl (int, int, ...);

#ifdef _WRS_KERNEL

extern int	open (const char *, int, int);
extern int	creat (const char *, int);

#else /* !_WRS_KERNEL */

extern int      open (const char *, int, ...);
extern int      creat (const char *, mode_t );

#endif	/* _WRS_KERNEL */

#ifdef __cplusplus
}
#endif

#endif /* __INCfcntlh */
