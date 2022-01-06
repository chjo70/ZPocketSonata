/* vxTypes.h - POSIX compliant (_t) types header file */

/*
 * Copyright (c) 1991-1992, 2001, 2003-2006, 2009-2011, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
*/

/*
modification history
--------------------
19sep16,brk  Add useconds_t 
27jan11,pad  Do no include stdint.h when _POSIX_C_SOURCE is defined.
27jul10,jpb  Added include of _Vx_exit_code_t type.
16jun10,pcs  Add new data type _Vx_ticks_t
18may10,pad  Moved extern C statement after include statements.
25jan10,d_c  SMP M-N updates: add phys_cpuset_t data type
13jan10,jpb  Added vsbConfig.h to pick up _WRS_CONFIG_LP64.
02oct09,pad  Removed macros related to ANSI types int8_t, uint8_t, int16_t,
		 uint16_t, int32_t, uint32_t, int64_t and uint64_t. Those types
		 are now defined in stdint.h.
19feb09,pcs  Add new datatype _Vx_usr_arg_t.
22jun06,mmi  Use include base type file for cpuset_t and atomic_t.
14mar06,mil  Use include base type file for ssize_t and time_t.
01mar06,pes  Split out base type files.
22feb06,pes  Move pid_t typedef.
10feb06,jlk  Added blksize_t and blkcnt_t
03feb06,jlk  Changed dev_t to a unsigned long from a short.
23jan06,mil  Updated for POSIX namespace conformance (P2).
07dec05,mcm  Adding macro protection for the std. integer types.
08sep05,pad  Added protection around ssize_t type definition (SPR 112064).
24aug05,mcm  Adding the definition of the protection macros to help
                 prevent redefinition for ssize_t, time_t and fpos_t.
23aug05,mcm  Adding protection for type definitions like uid_t, off_t etc.
31mar05,kk   merged user and kernel version
28sep04,gls  changed off_t to long long
04dec03,mcm  Protecting the definition of fpos_t, time_t
29aug03,cjj  written based on kernel version 01d of vxTypes.h 
25jan05,vvv  added new types to support the dual-stack
28sep04,gls  added off_t64
05dec01,mem  Added support for 64-bit types.
13nov92,dnw  added include of vxANSI.h
		 pruned some non-POSIX stuff.
22sep92,rrr  added support for c++
08sep92,smb  made some MIPS specific additions.
07sep92,smb  added __STDC__ conditional and some documentation.
29jul92,smb  added fpos_t type for stdio.h
03jul92,smb  written.
*/

/*
DESCRIPTION
This file actually typedef's the system types defined in vxArch.h or
vxTypesBase.h.  

Architecture specific values for the standard types are defined in vxArch.h
as follows:

	#ifndef _TYPE_sometype_t
	#define _TYPE_sometype_t 	typedef unsigned int sometype_t
	#endif

Defaults for each type are provided in vxTypesBase.h as follows:

	#ifndef _TYPE_sometype_t
	#define _TYPE_sometype_t 	typedef int sometype_t
	#endif

When vxTypesBase.h is included following the include of vxArch.h,
_TYPE_sometype_t will already be defined and so will not be redefined
in vxTypesBase.h.

Alternatively, if it not defined in vxArch.h, it will be defined in
vxTypesBase.h.  So after vxArch.h and vxTypesBase.h are included all ANSI
and POSIX types will be defined but they will not have been typedef'ed yet.

The typedef happens in this file, vxTypes.h

	#ifdef _TYPE_sometype_t
	_TYPE_sometype_t
	#undef _TYPE_sometype_t
	#endif

The '#undef _TYPE_sometype_t' is necessary because a type may be defined in
different header files. For example, ANSI says that size_t must be defined
in time.h and stddef.h

               *               *               *

Some of the type definitions have evolved from the above description.  
In the new semantics, the two layer protection and definition approach
described above is no longer used.  Such types will not be present in 
vxTypesBase.h, and will not use the _TYPE_sometype_t style macro.  

The newer approach uses a single protection macro _DEFINED_someType_t
where someType_t is case sensitive.  The general style is as follows:

#ifndef _DEFINED_someType_t
#define _DEFINED_someType_t
typedef int someType_t;
#endif

The type definitions can reside in this file (vxTypes.h), and can be 
duplicated in any number of files.  There are cases where a third 
party header file uses and checks only their own protection macros.  
If the same type is to be defined in a VxWorks header file, all
forms of the protection macros should be checked against.  Header
files from third parties, BSD-style code bases, or legacy systems
are examples, and the following style is recommended:

#if !defined(_DEFINED_someType_t) &&
    !defined(_SOMETYPE_T) &&                 /@ from aaa.h @/
    !defined(SOMETYPE_T_DEFINED)             /@ from bbb.h @/
#define _DEFINED_someType_t
#define _SOMETYPE_T
#define SOMETYPE_T_DEFINED
typedef int someType_t;
#endif

If an architecture wants to override the generic definition, the 
mechanism of using vxArch.h can be used.  This single layer 
protection and definition approach (as compared to the previously
described method that involves vxTypesBase.h and the use of 
_TYPE_sometype_t) also relies on vxArch.h being included first, 
and the protection macro should prevent further typedefs from being 
effective.

Some of the types are now residing in a base type file in the "base"
directory.  Each of those files should define a single type, and 
should be self-contained meaning they should include definitions 
of the types they use.  Any header files that require a duplicated
copy of the definitions can simply include the base type files.  
This minimizes the chance of incompatible type definitions, as well
as avoiding use of different protection macros at different places.  
The base type files are for VxWorks header files use, and customer
applications should not include the base type files directly.  
Including the base type files directly poses risks of incompatibility
with future changes, such as the renaming of those files.  
*/

#ifndef __INCvxTypesh
#define __INCvxTypesh

#ifdef _WRS_KERNEL
#include <types/vxANSI.h>	/* includes kernel's stdint.h */
#else
#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
/*
 * The definitions brought by stdint.h may not be made visible through the
 * inclusion of many POSIX header files, including a number which - usually
 * indirectly - include types/vxTypes.h for some other reason. So we do _not_
 * include stdint.h when the application declares itself POSIX conforming.
 */
#include <stdint.h>	/* ANSI C / POSIX.1 type definitions */
#endif  /* _POSIX_xxx_SOURCE */
#endif /* _WRS_KERNEL */

/* typedef ssize_t */
#include <base/b_ssize_t.h>

/* typedef cpuset_t is not required for POSIX */

#include <base/b_cpuset_t.h>

/* typedef phys_cpuset_t is not required for POSIX nor RTPs */

#if !defined(__RTP__)  /* define only if not RTP */
#include <base/b_phys_cpuset_t.h>
#endif /* __RTP__ */

/* typedef atomic_t is not required for POSIX */

#include <base/b_atomic_t.h>

#if !defined(__RTP__)  /* define only if not RTP */
/* typedef time_t */
#include <base/b_time_t.h>
#endif /* __RTP__ */

/* POSIX required */

/* typedef dev_t */
#include <base/b_dev_t.h>

/* typedef gid_t */
#include <base/b_gid_t.h>

/* typedef ino_t */
#include <base/b_ino_t.h>

/* typedef mode_t */
#include <base/b_mode_t.h>

/* typedef nlink_t */
#include <base/b_nlink_t.h>

/* typedef off_t */
#include <base/b_off_t.h>

/* typedef pid_t.h */
#include <base/b_pid_t.h>

/* typedef uid_t */
#include <base/b_uid_t.h>

/* typedef blksize_t */
#include <base/b_blksize_t.h>

/* typedef blkcnt_t */
#include <base/b_blkcnt_t.h>

/* typedef useconds_t */
#include <base/b_useconds_t.h>

/* This is for VSB option _WRS_CONFIG_LP64 */
#include <vsbConfig.h> 

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(__RTP__)
#ifdef _TYPE_fpos_t
#define _FPOS_T
_TYPE_fpos_t;
#undef _TYPE_fpos_t
#endif
#endif /* __RTP__ */

/* The following types have been added to support the dual-stack */

#ifdef _TYPE_u_int8_t
_TYPE_u_int8_t;
#undef _TYPE_u_int8_t
#endif

#ifdef _TYPE_u_int16_t
_TYPE_u_int16_t;
#undef _TYPE_u_int16_t
#endif

#ifdef _TYPE_u_int32_t
_TYPE_u_int32_t;
#undef _TYPE_u_int32_t
#endif

#ifdef _TYPE_u_int64_t
_TYPE_u_int64_t;
#undef _TYPE_u_int64_t
#endif

#ifdef _TYPE_u_quad_t
_TYPE_u_quad_t;
#undef _TYPE_u_quad_t
#endif

#ifdef _TYPE_quad_t
_TYPE_quad_t;
#undef _TYPE_quad_t
#endif

/* old Berkeley definitions */

typedef unsigned char	uchar_t;
typedef unsigned short	ushort_t;
typedef unsigned int	uint_t;
typedef unsigned long	ulong_t;

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
typedef	struct	_quad { long val[2]; } quad;
#endif  /* _POSIX_xxx_SOURCE */
typedef	long	daddr_t;
typedef	char *	caddr_t;
typedef	char *	addr_t;
typedef	long	swblk_t;

/* Type for arbitrary user-supplied argument to a user-supplied routine. */
#ifdef _WRS_CONFIG_LP64
typedef long _Vx_usr_arg_t;
#else
typedef int _Vx_usr_arg_t;
#endif /* _WRS_CONFIG_LP64 */

typedef unsigned int _Vx_ticks_t;
typedef unsigned long long _Vx_ticks64_t;

#ifdef _WRS_CONFIG_LP64
typedef long _Vx_exit_code_t;
#else
typedef int  _Vx_exit_code_t;
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCvxTypesh */
