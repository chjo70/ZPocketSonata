/* vxANSI.h - ANSI header file */

/*
* Copyright (c) 1992, 2006, 2009-2010 Wind River Systems, Inc.
*
* The right to copy, distribute, modify or otherwise make use
* of this software may be licensed only pursuant to the terms
* of an applicable Wind River license agreement.
*/

/*
modification history
--------------------
01h,27jan11,pad  Do not include stdin.h in case of inclusion by a POSIX
                 conforming application.
01g,28apr10,pad  Moved extern C statement after include statements.
01f,02oct09,pad  Now includes stdint.h
01e,28jan06,mil  Updated for POSIX namespace conformance.
01d,13nov92,dnw  added define for _EXTENSION_POSIX_1003
01c,22sep92,rrr  added support for c++
01b,07sep92,smb  added documentation.
01a,03jul92,smb  written.
*/

/*
DESCRIPTION
This header file includes the minimum configuration necessary for
an ANSI compatible file.

stdint.h      contains ANSI C / POSIX.1 type definitions.
vxCpu.h       contains CPU_FAMILY definition
vxArch.h      contains architecture specific definitions
vxParams.h    contains system parameters specified by ANSI or POSIX standards
vxTypesBase.h contains type definitions for ALL types specified by ANSI or
	      POSIX not already defined in vxArch.h
*/

#ifndef __INCvxANSIh
#define __INCvxANSIh

/*
 * The following defines enable various extensions to strict ANSI definitions.
 * To achieve strict ANSI compliance without extensions, define these
 * to be 0.
 */

#define _EXTENSION_POSIX_1003		1    /* include POSIX extensions */
#define _EXTENSION_POSIX_REENTRANT	1    /* include POSIX reentrant ext. */
#define _EXTENSION_WRS			1    /* include WRS extensions */

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
        !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
/*
 * The definitions brought by stdint.h may not be made visible through the
 * inclusion of many POSIX header files, including a number which - usually
 * indirectly - include types/vxTypes.h for some other reason. So we do  _not_
 * include stdint.h when the application declares itself POSIX conforming.
 */
#include <stdint.h>			/* ANSI C / POSIX.1 type definitions */
#endif  /* _POSIX_xxx_SOURCE */
#include <types/vxCpu.h>		/* CPU family definition */
#ifndef _WRS_KERNEL
#include <types/vxCpuX.h>
#endif  /* _WRS_KERNEL */
#include <types/vxArch.h>		/* architecture definitions */

#include <types/vxParams.h>		/* system defaults */
#include <types/vxTypesBase.h>	 	/* defaults for machine dependant */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCvxANSIh */
