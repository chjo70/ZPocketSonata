/* vxTypesOld.h - old VxWorks type definition header */

/*
 * Copyright (c) 1990-1997, 2000-2001, 2003-2007, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
*/

/*
modification history
--------------------
03i,18may10,pad  Moved extern C statement after include statements.
03h,25jul07,mfj  Removing superfluous semi-colons (defect WIND00092997)
03g,08sep06,jpb  Added check to see if VOID_FROM_CONST and CHAR_FROM_CONST
                 have been defined.  Fixed VIRT_ADDR and PHYS_ADDR breaking
		 bsp (fix 64750).
03f,07sep06,jpb  Added _TYPE_VIRT_ADDR and _TYPE_PHYS_ADDR definition 
                 (continuation of defect 63929 / fix 63938)
03e,31aug06,pad  Reworked definitions of VIRT_ADDR and PHYS_ADDR in order to
                 prevent double definition issue (defect 63929 / fix 63938).
03d,23aug06,jpb  Allowed this file to be shared between kernel and user
                 (WIND00063000)
03c,20jun06,jpb  Removed old CPU_FAMILY checks
03b,22feb06,pes  Elaborate on comment regarding the inclusion of
                 e_vxTypesOld.h. Move BOOL typedef into b_BOOL.h
03a,23jan06,mil  Updated for POSIX namespace conformance (P1).
02z,01jul05,rec  coldfire review comments
02y,23jun05,rec  remove INSTR typedef from coldfire arch for B6
02x,24aug05,mcm  Adding protection for STATUS.
02w,23aug05,mcm  Protecting definitions of the funcptr types to prevent
                 redefinition errors.
02v,18aug05,mcm  Adding a macro to detect the definition of fd_set etc.
02u,01oct04,tam  defined PHYS_ADDR only for kernel side
02t,30sep04,yvp  Added LOW32 and HIGH32 definitions.
02s,29nov03,yp   moving ADDR to pgPoolLibP.h
02r,14oct03,sru  Added 'signed' to INT8..INT32 typedefs; also, allow 
		 VIRT_ADDR and PHYS_ADDR types to be defined in an
		 architecture-specific manner.
02q,11aug03,yp	 adding VIRT_ADDR and PHYS_ADDR
02p,18aug03,dbt  Added PAL support for VxSim.
02o,07may03,pes  PAL conditional compilation cleanup. Phase 2. Moving
		 arch-specific definitions out to arch files.
02n,17apr03,dbt  Added SIMLINUX support. Removed SIMHPPA and SIMSPARCSUNOS.
02m,05dec01,mem  Added INT64 and UINT64.
02l,27nov01,sbs  changed FD_SETSIZE from 256 to 2048 (SPR #9377)
02k,22oct01,dee  Merge from T2.1.0 ColdFire
02j,18apr01,mem  Updated Arm/Thumb detection.
02i,25feb00,frf  Add SH support for T2
02h,15aug97,cym  added simnt support.
02g,26mar97,cdp  added Thumb (ARM7TDMI_T) support.
02f,28nov96,cdp  added ARM support.
02e,28sep95,ms	 removed "static __inline__" (SPR #4500)
02d,12jul95,ism  added simsolaris support
02c,19mar95,dvs  removed tron references.
02b,01sep94,ism  fixed comment as per SPR# 1512.
02a,02dec93,pme  added Am29K family support.
01z,12jun93,rrr  vxsim.
01y,26may94,yao  added PPC support.
01x,09jun93,hdn  added support for I80X86
01w,12feb93,srh  added C++ versions of FUNCPTR, et al.
01v,13nov92,dnw  added definition of VOID (SPR #1781)
01u,02oct92,srh  replaced conditional around volatile, const, and signed so
		 they won't be elided when __STDC__ is defined.
		 added __cplusplus to __STDC__ condition.
01t,22sep92,rrr  added support for c++
01s,08sep92,smb  made some additions for the MIPS.
01r,07sep92,smb  added __STDC__ and modes to maintain compatibility with 5.0
01q,07jul92,rrr  moved STACK_GROW and ENDIAN to vxArch.h
01p,03jul92,smb  changed name from vxTypes.h.
01o,26may92,rrr  the tree shuffle
01n,25nov91,llk  included sys/types.h.
01m,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -removed TINY and UTINY
		  -changed VOID to void
		  -changed ASMLANGUAGE to _ASMLANGUAGE
		  -changed copyright notice
01l,01oct91,jpb  fixed MIPS conditional for undefined CPU_FAMILY.
01k,20sep91,wmd  conditionalized out defines for const, unsigned and volatile
		 for the MIPS architecture.
01j,02aug91,ajm  added support for MIPS_R3k.
01i,15may91,gae  added define for "signed" when not available for pre-ANSI.
01h,29apr91,hdn  added defines and macros for TRON architecture.
01g,28apr91,del  added defines of __volatile__ and __const__ if !_STDC_
		 && _GNUC__
01f,24mar91,del  added INSTR * define for I960.
01e,28jan91,kdl  added DBLFUNCPTR and FLTFUNCPTR.
01d,25oct90,dnw  changed void to void except when linting.
01c,05oct90,shl  added copyright notice.
                 made #endif ANSI style.
01b,10aug90,dnw  added VOIDFUNCPTR
01a,29may90,del  written.
*/

/*
DESCRIPTION
This header file contains a mixture of stuff.
1) the old style typedefs (ie. POSIX now says they must end with _t).
   These will be phased out gradually.
2) a mechanism for getting rid of const warning which are produced by the
   GNU C compiler. Hopefully, this will be removed in the future.
3) macros that are so longer needed for vxWorks source code but maybe needed
   by some customer applications and are therefore provided for backward
   compatability.
4) system III typedefs (used by netinet) which do not fit in anywhere else.

*/

#ifndef __INCvxTypesOldh
#define __INCvxTypesOldh

/*
 * NOTE - this file should not be updated.  Any update should be in
 *        base/e_vxTypesOld.h. Non-kernel and non-POSIX uses of this file 
 *        will see both VxWorks type names as well as POSIX type names
 *        (e.g. both INT8 and _Vx_INT8) for easier future transition
 *        to define VxWorks types based on POSIX types.
 */

#include <base/e_vxTypesOld.h>  /* posix conforming equiv of this file
                                 * which also includes sys/types.h */

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
#include <base/b_BOOL.h>	/* typedef BOOL */
#endif  /* _POSIX_xxx_SOURCE */

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

/* vxWorks types */

typedef _Vx_INT8        INT8;
typedef _Vx_INT16       INT16;
typedef _Vx_INT32       INT32;
typedef _Vx_INT64       INT64;

typedef _Vx_UINT8       UINT8;
typedef _Vx_UINT16      UINT16;
typedef _Vx_UINT32      UINT32;
typedef _Vx_UINT64      UINT64;

typedef _Vx_UCHAR       UCHAR;
typedef _Vx_USHORT      USHORT;
typedef _Vx_UINT        UINT;
typedef _Vx_ULONG       ULONG;

typedef _Vx_ARGINT 	ARGINT;
typedef _Vx_VOID	VOID;

#ifndef _STATUS_DEFINED
#define _STATUS_DEFINED
typedef	_Vx_STATUS	STATUS;
#endif /* _STATUS_DEFINED */

#ifndef _FUNCPTR_DEFINED
#define _FUNCPTR_DEFINED
#ifdef __cplusplus
typedef int 		(*FUNCPTR) (...);     /* ptr to function returning int */
#else
typedef _Vx_FUNCPTR 	FUNCPTR;	   /* ptr to function returning int */
#endif /* __cplusplus */
#endif /* _FUNCPTR_DEFINED */

#ifndef _VOIDFUNCPTR_DEFINED
#define _VOIDFUNCPTR_DEFINED
#ifdef __cplusplus
typedef void 		(*VOIDFUNCPTR) (...); /* ptr to function returning void */
#else
typedef _Vx_VOIDFUNCPTR VOIDFUNCPTR; /* ptr to function returning void */
#endif /* __cplusplus */
#endif /* _VOIDFUNCPTR_DEFINED */

#ifndef _DBLFUNCPTR_DEFINED
#define _DBLFUNCPTR_DEFINED
#ifdef __cplusplus
typedef double 		(*DBLFUNCPTR) (...);  /* ptr to function returning double*/
#else
typedef _Vx_DBLFUNCPTR 	DBLFUNCPTR;  /* ptr to function returning double*/
#endif /* __cplusplus */
#endif /* _DBLFUNCPTR_DEFINED */

#ifndef _FLTFUNCPTR_DEFINED
#define _FLTFUNCPTR_DEFINED
#ifdef __cplusplus
typedef float 		(*FLTFUNCPTR) (...);  /* ptr to function returning float */
#else
typedef _Vx_FLTFUNCPTR	FLTFUNCPTR;  /* ptr to function returning float */
#endif /* __cplusplus */
#endif /* _FLTFUNCPTR_DEFINED */


/* This structure and the following definitions are needed to get rid
   of const warning produced by the GNU C compiler.
 */

typedef _Vx_pointer_mix_t	pointer_mix_t;

#ifndef CHAR_FROM_CONST
#define CHAR_FROM_CONST(x)	_VX_CHAR_FROM_CONST(x)
#endif /* CHAR_FROM_CONST */
#ifndef VOID_FROM_CONST
#define VOID_FROM_CONST(x)	_VX_VOID_FROM_CONST(x)
#endif /* VOID_FROM_CONST */

#define STACK_DIR		_VX_STACK_DIR
#define ALIGN_MEMORY		_VX_ALIGN_MEMORY
#define ALIGN_STACK		_VX_ALIGN_STACK
#define ALIGN_REGS		_VX_ALIGN_REGS

#ifndef NBBY
#define	NBBY	_VX_NBBY		/* number of bits in a byte */
#endif

/* modes - must match O_RDONLY/O_WRONLY/O_RDWR in ioLib.h! */

#ifndef READ
#define READ            _VX_READ
#endif  /* READ */

#ifndef WRITE
#define WRITE           _VX_WRITE
#endif  /* WRITE */

#ifndef UPDATE
#define UPDATE          _VX_UPDATE
#endif  /* UPDATE */

/* Select uses bit masks of file descriptors in longs.
 * These macros manipulate such bit fields (the filesystem macros use chars).
 * FD_SETSIZE may be defined by the user, but the default here
 * should be >= maxFiles parameter in iosInit call found in usrConfig.c.
 * If this define is changed, recompile the source, or else select() will
 * not work.(The user can set the number lower, but not higher).
 *
 * Changing the default to 2048 adds 224 bytes to the size of the fd_set
 * structure.
 */

#ifndef	FD_SETSIZE
#define	FD_SETSIZE	_VX_FD_SETSIZE
#endif	/* FD_SETSIZE */

#ifndef _FD_MASK_DEFINED
#define _FD_MASK_DEFINED
typedef _Vx_fd_mask	fd_mask;
#endif /* _FD_MASK_DEFINED */

#ifndef NFDBITS
#define NFDBITS	_VX_NFDBITS	/* bits per mask */
#endif /* NFDBITS */

#ifndef howmany
#define	howmany(x, y)	_VX_howmany (x,y)
#endif	/* howmany */

#ifndef _FD_SET_DEFINED
#define _FD_SET_DEFINED
typedef	struct fd_set
    {
    _Vx_fd_mask	fds_bits[howmany(FD_SETSIZE, NFDBITS)];
    } fd_set;
#endif

#ifndef _FD_FUNC_DEFINED
#define _FD_FUNC_DEFINED
#define _FD_FUNC_DEFINED
#define FD_SET(n, p)    _VX_FD_SET (n, p)
#define FD_CLR(n, p)    _VX_FD_CLR (n, p)
#define FD_ISSET(n, p)  _VX_FD_ISSET (n, p)
#define FD_ZERO(p)      _VX_FD_ZERO (p)
#endif /* _FD_FUNC_DEFINED */

/* system III  typedefs (used by netinet) */

typedef	_Vx_u_char	u_char;
typedef	_Vx_u_short	u_short;
typedef	_Vx_u_int	u_int;
typedef	_Vx_u_long	u_long;
typedef	_Vx_ushort	ushort;


/* historical definitions - now obsolete */

typedef _Vx_TBOOL		TBOOL;		/* obsolete */

/* new memory management global defines */

#ifndef _TYPE_VIRT_ADDR
#define _TYPE_VIRT_ADDR typedef _Vx_VIRT_ADDR VIRT_ADDR
#endif
_TYPE_VIRT_ADDR;

#ifdef _WRS_KERNEL
#ifndef _TYPE_PHYS_ADDR
#define _TYPE_PHYS_ADDR typedef _Vx_PHYS_ADDR PHYS_ADDR
#endif
_TYPE_PHYS_ADDR;
#endif	/* _WRS_KERNEL */

/* macro's for extracting 32-bit halves of a 64-bit number */

#define LOW32(x)  _VX_LOW32(x)
#define HIGH32(x) _VX_HIGH32(x)

#endif  /* _POSIX_xxx_SOURCE */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxTypesOldh */
