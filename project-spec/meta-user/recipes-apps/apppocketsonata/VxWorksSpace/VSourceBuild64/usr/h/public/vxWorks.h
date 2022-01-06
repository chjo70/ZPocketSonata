/* vxWorks.h - user-level version of VxWorks standard definitions header */

/*
 * Copyright (c) 2004-2006, 2010, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
04dec14,chm  Enable OpenSSL in vx7 RTP.(US48545) 
29jul10,pad  Moved extern C statement after include statements.
14jun10,cww  Added syscall_long prototype
22feb10,jpb  Updated syscall prototype.
20jan06,mil  Updated for POSIX namespace conformance (P1).
08sep05,yvp  Fix SPR 108467 - Added prototype for syscall().
             Also updated copyright and made #include use angle brackets.
18mar04,job  Refactored file to use vxWorksCommon.h
11nov03,pes  Add Arch-specific includes. Removed NULL. Added vxParams.h
22sep03,job  Removed isascii() and toascii() definitions as they are
		     provided in libc
16sep03,zl   added _ALLOC_ALIGN_SIZE, _STACK_ALIGN_SIZE definitions.
05sep03,aeg  added inclusion of toolMacros.h
29aug03,cjj  written based on kernel version 03s of vxWorks.h
*/

#ifndef __INCvxWorksh
#define __INCvxWorksh

/* includes */
#include <vsbConfig.h>

#include <vxWorksCommon.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE
/* externals */

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
extern int	syscall		(_Vx_usr_arg_t arg1, _Vx_usr_arg_t arg2,
				 _Vx_usr_arg_t arg3, _Vx_usr_arg_t arg4,
				 _Vx_usr_arg_t arg5, _Vx_usr_arg_t arg6,
				 _Vx_usr_arg_t arg7, _Vx_usr_arg_t arg8,
				 int scn);

extern long	syscall_long	(_Vx_usr_arg_t arg1, _Vx_usr_arg_t arg2,
		      		 _Vx_usr_arg_t arg3, _Vx_usr_arg_t arg4,
		      		 _Vx_usr_arg_t arg5, _Vx_usr_arg_t arg6,
		      		 _Vx_usr_arg_t arg7, _Vx_usr_arg_t arg8,
				 int scn);

#endif  /* _POSIX_xxx_SOURCE */

#endif	/* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxWorksh */
