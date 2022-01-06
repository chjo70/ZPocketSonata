/* e_vxTypesOld.h - old VxWorks type definition header */

/*
 * Copyright (c) 1990-1997, 2000-2001, 2003-2006, 2009-2011, 2013, 2015, 2018
 * Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
04jan18,dlk  introduce parameter _WRS_CONFIG_FD_SET_SIZE (V7COR-5462)
11feb15,jxy  Define _VX_FD_SETSIZE to same as IP_FD_SETSIZE.  (VXWRAD-99)
19jul13,krz  Fixing _VX_FD_ISSET for defect WIND00417144.
26jan11,pad  Included types/vxTypes.h so as to bring the definitions of
             the "old" BSD types now that sys/types.h no longer brings them.
23aug10,pad  Added inclusion of vsbConfig.h
28apr10,pad  Moved extern C statement after include statements.
17mar10,lxj  fixed defect WIND00200304
14may09,zl   defined _Vx_VIRT_ADDR and _Vx_PHYS_ADDR for LP64
08sep06,jpb  Added check to see if VOID_FROM_CONST and CHAR_FROM_CONST have
             been defined.  Fixed VIRT_ADDR and PHYS_ADDR breaking bsp
	     (fix 64750).
31aug06,pad  Reworked definitions of _Vx_VIRT_ADDR and _Vx_PHYS_ADDR in
	     order to prevent double definition issue in types/vxTypesOld.h
	     (defect 63929 / fix 63938).
18may06,jpb  Removed old CPU_FAMILY checks
18jal06,mil  Updated for POSIX namespace conformance (P1).
01jul05,rec  coldfire review comments
23jun05,rec  remove INSTR typedef from coldfire arch for B6
24aug05,mcm  Adding protection for STATUS.
23aug05,mcm  Protecting definitions of the funcptr types to prevent
             redefinition errors.
18aug05,mcm  Adding a macro to detect the definition of fd_set etc.
01oct04,tam  defined PHYS_ADDR only for kernel side
30sep04,yvp  Added LOW32 and HIGH32 definitions.
29nov03,yp   moving ADDR to pgPoolLibP.h
14oct03,sru  Added 'signed' to INT8..INT32 typedefs; also, allow
	     VIRT_ADDR and PHYS_ADDR types to be defined in an
	     architecture-specific manner.
11aug03,yp   adding VIRT_ADDR and PHYS_ADDR
18aug03,dbt  Added PAL support for VxSim.
07may03,pes  PAL conditional compilation cleanup. Phase 2. Moving
	     arch-specific definitions out to arch files.
17apr03,dbt  Added SIMLINUX support. Removed SIMHPPA and SIMSPARCSUNOS.
05dec01,mem  Added INT64 and UINT64.
27nov01,sbs  changed FD_SETSIZE from 256 to 2048 (SPR #9377)
22oct01,dee  Merge from T2.1.0 ColdFire
18apr01,mem  Updated Arm/Thumb detection.
25feb00,frf  Add SH support for T2
15aug97,cym  added simnt support.
26mar97,cdp  added Thumb (ARM7TDMI_T) support.
28nov96,cdp  added ARM support.
28sep95,ms   removed "static __inline__" (SPR #4500)
12jul95,ism  added simsolaris support
19mar95,dvs  removed tron references.
01sep94,ism  fixed comment as per SPR# 1512.
02dec93,pme  added Am29K family support.
12jun93,rrr  vxsim.
26may94,yao  added PPC support.
09jun93,hdn  added support for I80X86
12feb93,srh  added C++ versions of FUNCPTR, et al.
13nov92,dnw  added definition of VOID (SPR #1781)
02oct92,srh  replaced conditional around volatile, const, and signed so
             they won't be elided when __STDC__ is defined.
	     added __cplusplus to __STDC__ condition.
22sep92,rrr  added support for c++
08sep92,smb  made some additions for the MIPS.
07sep92,smb  added __STDC__ and modes to maintain compatibility with 5.0
07jul92,rrr  moved STACK_GROW and ENDIAN to vxArch.h
03jul92,smb  changed name from vxTypes.h.
26may92,rrr  the tree shuffle
25nov91,llk  included sys/types.h.
04oct91,rrr  passed through the ansification filter
                  -fixed #else and #endif
		  -removed TINY and UTINY
		  -changed VOID to void
		  -changed ASMLANGUAGE to _ASMLANGUAGE
		  -changed copyright notice
01oct91,jpb  fixed MIPS conditional for undefined CPU_FAMILY.
20sep91,wmd  conditionalized out defines for const, unsigned and volatile
             for the MIPS architecture.
02aug91,ajm  added support for MIPS_R3k.
15may91,gae  added define for "signed" when not available for pre-ANSI.
29apr91,hdn  added defines and macros for TRON architecture.
28apr91,del  added defines of __volatile__ and __const__ if !_STDC_
             && _GNUC__
24mar91,del  added INSTR * define for I960.
28jan91,kdl  added DBLFUNCPTR and FLTFUNCPTR.
25oct90,dnw  changed void to void except when linting.
05oct90,shl  added copyright notice.
             made #endif ANSI style.
10aug90,dnw  added VOIDFUNCPTR
29may90,del  written.
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

#ifndef __INCe_vxTypesOldh
#define __INCe_vxTypesOldh

#include <vsbConfig.h>
#include <sys/types.h>
#include <types/vxTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/* vxWorks types */

typedef signed char     _Vx_INT8;
typedef signed short    _Vx_INT16;
typedef signed int      _Vx_INT32;
typedef signed long long _Vx_INT64;

typedef unsigned char   _Vx_UINT8;
typedef unsigned short  _Vx_UINT16;
typedef unsigned int    _Vx_UINT32;
typedef unsigned long long _Vx_UINT64;

typedef unsigned char   _Vx_UCHAR;
typedef unsigned short  _Vx_USHORT;
typedef unsigned int    _Vx_UINT;
typedef unsigned long   _Vx_ULONG;

typedef int             _Vx_BOOL;
typedef int             _Vx_ARGINT;
typedef void            _Vx_VOID;

#ifndef _VX_STATUS_DEFINED
#define _VX_STATUS_DEFINED
typedef int             _Vx_STATUS;
#endif /* _VX_STATUS_DEFINED */

#ifndef _VX_FUNCPTR_DEFINED
#define _VX_FUNCPTR_DEFINED
#ifdef __cplusplus
typedef int     (*_Vx_FUNCPTR) (...);       /* ptr to func returning int */
#else
typedef int     (*_Vx_FUNCPTR) ();          /* ptr to func returning int */
#endif /* __cplusplus */
#endif /* _VX__FUNCPTR_DEFINED */

#ifndef _VX_VOIDFUNCPTR_DEFINED
#define _VX_VOIDFUNCPTR_DEFINED
#ifdef __cplusplus
typedef void    (*_Vx_VOIDFUNCPTR) (...);   /* ptr to func returning void */
#else
typedef void    (*_Vx_VOIDFUNCPTR) ();      /* ptr to func returning void */
#endif /* __cplusplus */
#endif /* _VX_VOIDFUNCPTR_DEFINED */

#ifndef _VX_DBLFUNCPTR_DEFINED
#define _VX_DBLFUNCPTR_DEFINED
#ifdef __cplusplus
typedef double  (*_Vx_DBLFUNCPTR) (...);    /* ptr to func returning double */
#else
typedef double  (*_Vx_DBLFUNCPTR) ();       /* ptr to func returning double */
#endif /* __cplusplus */
#endif /* _VX_DBLFUNCPTR_DEFINED */

#ifndef _VX__FLTFUNCPTR_DEFINED
#define _VX__FLTFUNCPTR_DEFINED
#ifdef __cplusplus
typedef float   (*_Vx_FLTFUNCPTR) (...);    /* ptr to func returning float */
#else
typedef float   (*_Vx_FLTFUNCPTR) ();       /* ptr to func returning float */
#endif /* __cplusplus */
#endif /* _VX__FLTFUNCPTR_DEFINED */

/* This structure and the following definitions are needed to get rid
   of const warning produced by the GNU C compiler.
 */

/* these undefs should exist only in the POSIX case */
#undef pm_int
#undef pm_v
#undef pm_cv
#undef pm_c
#undef pm_uc

#undef pm_sc
#undef pm_cc
#undef pm_cuc
#undef pm_csc
#undef pm_s
#undef pm_us
#undef pm_cs
#undef pm_cus
#undef pm_i
#undef pm_ui
#undef pm_ci
#undef pm_cui
#undef pm_l
#undef pm_ul
#undef pm_cl
#undef pm_cul

#undef pm_i8
#undef pm_ui8
#undef pm_ci8
#undef pm_cui8
#undef pm_i16
#undef pm_ui16
#undef pm_ci16
#undef pm_cui16
#undef pm_i32
#undef pm_ui32
#undef pm_ci32
#undef pm_cui32
#if _ARCH_MOVE_SIZE > 4
#undef pm_i64
#undef pm_ci64
#if _ARCH_MOVE_SIZE > 8
#undef pm_i128
#undef pm_ci128
#endif
#endif

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
typedef union
    {
    long pm_int;
    void *pm_v;
    const void *pm_cv;
    char *pm_c;
    unsigned char *pm_uc;

    signed char *pm_sc;
    const char *pm_cc;
    const unsigned char *pm_cuc;
    const signed char *pm_csc;
    short *pm_s;
    ushort_t *pm_us;
    const short *pm_cs;
    const ushort_t *pm_cus;
    int *pm_i;
    uint_t *pm_ui;
    const int *pm_ci;
    const uint_t *pm_cui;
    long *pm_l;
    ulong_t *pm_ul;
    const long *pm_cl;
    const ulong_t *pm_cul;

    int8_t *pm_i8;
    uint8_t *pm_ui8;
    const int8_t *pm_ci8;
    const uint8_t *pm_cui8;
    int16_t *pm_i16;
    uint16_t *pm_ui16;
    const int16_t *pm_ci16;
    const uint16_t *pm_cui16;
    int32_t *pm_i32;
    uint32_t *pm_ui32;
    const int32_t *pm_ci32;
    const uint32_t *pm_cui32;
#if _ARCH_MOVE_SIZE > 4
    int64_t *pm_i64;
    const int64_t *pm_ci64;
#if _ARCH_MOVE_SIZE > 8
    int128_t *pm_i128;
    const int128_t *pm_ci128;
#endif
#endif
    } _Vx_pointer_mix_t;        /* _Vx_ for convenience, *_t already okay */
#endif  /* _POSIX_xxx_SOURCE */

#ifndef _VX_CHAR_FROM_CONST
#define _VX_CHAR_FROM_CONST(x)  (char *)(x)
#endif /* _VX_CHAR_FROM_CONST */
#ifndef _VX_VOID_FROM_CONST
#define _VX_VOID_FROM_CONST(x)  (void *)(x)
#endif /* _VX_VOID_FROM_CONST */

#define _VX_STACK_DIR           _ARCH_STACK_DIR
#define _VX_ALIGN_MEMORY        _ARCH_ALIGN_MEMORY
#define _VX_ALIGN_STACK         _ARCH_ALIGN_STACK
#define _VX_ALIGN_REGS          _ARCH_ALIGN_REGS

#ifndef _VX_NBBY
#define _VX_NBBY        8       /* number of bits in a byte */
#endif

/* modes - must match O_RDONLY/O_WRONLY/O_RDWR in ioLib.h! */

#ifndef _VX_READ
#define _VX_READ        0
#endif  /* _VX_READ */

#ifndef _VX_WRITE
#define _VX_WRITE       1
#endif  /* _VX_WRITE */

#ifndef _VX_UPDATE
#define _VX_UPDATE      2
#endif  /* _VX_UPDATE */

/*
 * Select uses bit masks of file descriptors in longs.
 * These macros manipulate such bit fields (the filesystem macros use chars).
 * FD_SETSIZE may be defined by the user, but the default here
 * should not be less than the NUM_FILES VIP parameter of INCLUDE_IO_BASIC.
 * See also usrIo.c.
 * If this define is changed, recompile the source, or else select() will
 * not work.
 * 2048 bits corresponds to an fd_set of 256 bytes.
 */

#ifndef _VX_FD_SETSIZE
#if defined(_WRS_CONFIG_FD_SET_SIZE)

#if defined(_WRS_CONFIG_NET_SOCK_MAX) &&                \
  (_WRS_CONFIG_NET_SOCK_MAX > _WRS_CONFIG_FD_SET_SIZE)
#define _VX_FD_SETSIZE     _WRS_CONFIG_NET_SOCK_MAX
#else
#define _VX_FD_SETSIZE  _WRS_CONFIG_FD_SET_SIZE
#endif

#else /* defined(_WRS_CONFIG_FD_SET_SIZE)*/

#if defined(_WRS_CONFIG_NET_SOCK_MAX)
#define _VX_FD_SETSIZE     _WRS_CONFIG_NET_SOCK_MAX
#else
#define _VX_FD_SETSIZE  2048
#endif

#endif /* defined(_WRS_CONFIG_FD_SET_SIZE) */
#endif  /* _VX_FD_SETSIZE */

#ifndef _VX_FD_MASK_DEFINED
#define _VX_FD_MASK_DEFINED
typedef long    _Vx_fd_mask;
#endif /* _VX_FD_MASK_DEFINED */

#ifndef _VX_NFDBITS
#define _VX_NFDBITS     (sizeof(_Vx_fd_mask) * _VX_NBBY)  /* bits per mask */
#endif /* _VX_NFDBITS */

#ifndef _VX_howmany
#define _VX_howmany(x, y)   ((unsigned int)(((x)+((y)-1)))/(unsigned int)(y))
#endif  /* _VX_howmany */

#ifndef _VX_FD_SET_DEFINED
#define _VX_FD_SET_DEFINED

#undef fds_bits         /* for POSIX namespace isolation */
typedef struct _Vx_fd_set
    {
    _Vx_fd_mask fds_bits[_VX_howmany(_VX_FD_SETSIZE, _VX_NFDBITS)];
    } _Vx_fd_set;
#endif  /* _VX_FD_SET_DEFINED */

#ifndef _VX_FD_FUNC_DEFINED
#define _VX_FD_FUNC_DEFINED
#define _VX_FD_SET(n, p) \
	((p)->fds_bits[(n)/_VX_NFDBITS] |= ((_Vx_fd_mask)1 << ((n) % _VX_NFDBITS)))
#define _VX_FD_CLR(n, p) \
	((p)->fds_bits[(n)/_VX_NFDBITS] &= ~((_Vx_fd_mask)1 << ((n) % _VX_NFDBITS)))
#define _VX_FD_ISSET(n, p) \
	((int)(((p)->fds_bits[(n)/_VX_NFDBITS] & \
            ((_Vx_fd_mask)1 << ((n) % _VX_NFDBITS))) != 0))
#define _VX_FD_ZERO(p) \
	bzero((char *)(p), sizeof(*(p)))
#endif /* _VX_FD_FUNC_DEFINED */

/* system III typedefs (used by netinet) */

typedef unsigned char   _Vx_u_char;
typedef unsigned short  _Vx_u_short;
typedef unsigned int    _Vx_u_int;
typedef unsigned long   _Vx_u_long;
typedef unsigned short  _Vx_ushort;

/* historical definitions - now obsolete */

typedef char            _Vx_TBOOL;              /* obsolete */

/* new memory management global defines */

#ifndef _TYPE_VIRT_ADDR
#ifndef _TYPE_VX_VIRT_ADDR
# ifdef _WRS_CONFIG_LP64
# define _TYPE_VX_VIRT_ADDR typedef _Vx_UINT64 _Vx_VIRT_ADDR
# else
# define _TYPE_VX_VIRT_ADDR typedef _Vx_UINT32 _Vx_VIRT_ADDR
# endif
#endif  /* _TYPE_VX_VIRT_ADDR */
#endif  /* _TYPE_VIRT_ADDR */
#ifdef _TYPE_VX_VIRT_ADDR
_TYPE_VX_VIRT_ADDR;
#endif  /* _TYPE_VX_VIRT_ADDR */

#ifdef _WRS_KERNEL
#ifndef _TYPE_PHYS_ADDR
#ifndef _TYPE_VX_PHYS_ADDR
# ifdef _WRS_CONFIG_LP64
# define _TYPE_VX_PHYS_ADDR typedef _Vx_UINT64 _Vx_PHYS_ADDR
# else
# define _TYPE_VX_PHYS_ADDR typedef _Vx_UINT32 _Vx_PHYS_ADDR
# endif
#endif  /* _TYPE_VX_PHYS_ADDR */
#endif  /* _TYPE_PHYS_ADDR */
#ifdef _TYPE_VX_PHYS_ADDR
_TYPE_VX_PHYS_ADDR;
#endif  /* _TYPE_VX_PHYS_ADDR */
#endif /* _WRS_KERNEL */

/* macro's for extracting 32-bit halves of a 64-bit number */

#define _VX_LOW32(x)  (long) (((long long)(x)) & (unsigned long) 0xffffffff)
#define _VX_HIGH32(x) (long) ((((long long)(x)) >> 32) & (unsigned long)0xffffffff)

/* ANSI type qualifiers */

#ifdef __cplusplus
}
#endif

#endif /* __INCe_vxTypesOldh */
