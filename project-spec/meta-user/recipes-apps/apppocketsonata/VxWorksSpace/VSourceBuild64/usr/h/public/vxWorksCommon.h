/* vxWorksCommon.h - VxWorks standard definitions header */

/*
 * Copyright (c) 1990-1992, 1994, 1996-1997, 1999, 2001, 2003-2010, 2014
 * Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
04feb14,cww  Removed _WRS_VXWORKS_5_X (VXW7-1004)
17jun10,pcs  Change the macro WAIT_FOREVER from -1 to -1U
19jan10,pad  Added logic allowing to keep using FUNCPTR/VOIDFUNCPTR in API
             on VxWorks 32-bit.
23jan09,pcs  Updated to add support for LP64 data model.
29oct08,cww  Remove max/min macros completely for C++
22aug08,cww  Changed conditions under which max and min are defined
	     (WIND00086197)
10may07,zl   added ARCH_HEADER macro.
09may07,mmi  move VX_MAX_SMP_CPUS outside #ifndef/#endif _WRS_KERNEL
27apr07,tkf  Removed network configuration parameters.
17apr07,kk   move VX_MAX_SMP_CPUS to here
23may06,jpb  Updated for POSIX namespace conformance.  
	     Changed C preprocessor macro TOOL_FAMILY to _VX_TOOL_FAMILY.
20jan06,mil  Updated for POSIX namespace conformance.
22jun05,mcm  Added _WRS_BIT_OR macro definition.
21jul05,yvp  Deleted inclusion of vxLayerConfig.h and prjComps.h
             Updated copyright. Includes now with angle brackets.
07jul05,pee  Added conditinal inclusion of prjComps for building projects from
	     source
17may05,yvp  Moved #include vxLayerConfig.h outside the _ASMLANGUAGE block.
26apr05,yvp  Added include for vxLayerConfig.h
23mar05,yvp  Added include for vxGlobal.h.
22oct04,mcm  Fix for SPR#102899 - min/max namespace pollution.
05may04,dat  move version number macros from vxWorks.c to version.h,
	     added parens around TRUE and FALSE
18mar04,job  Removed isascii and toascii macros as these have been
	     moved to ctypes.h. Refactored into common file.
	     Moved BUS definitions to kernel only version
	     Moved *_INSN_* macros to kernel only version.
	     Moved STACK, ALLOC & CACHE_ALIGN_SIZE macros to types/vxArch.h
09feb04,dat  New release id macros
02dec03,dat  removing NULL
14may03,pes  PAL conditional compilation cleanup. Phase 2.
25jun03,dcc  removed non-ANSI prototypes.
14mar03,dcc  added include of types/vxWind.h
27nov01,mrs  Fix to conform to ANSI standard for token pasting.
31oct01,tdl  Check for preexsiting __P def before defining it
18oct01,dat  Chg TOOLCHAIN to TOOL_FAMILY
24sep01,gls  Added definition of __P() macro (SPR #28330)
28sep01,rae  added #define _WRS_VXWORKS_5_X
19sep01,dat  Rework of gnu-diab changes
08sep01,dat  Gnu-Diab infrastructure
20aug01,dat  Gnu-Diab, added #include toolMacros.h
17feb99,mrs  Add C++ support for NULL, (SPR #25079).
25nov97,dat  added BUS_TYPE macros
26nov96,vin  modified BSD to 44.
23aug94,ism  added the MSW() and LSW() macros (SPR#3541)
22sep92,rrr  added support for c++
07sep92,smb  added #undef BSD to remove previous definition
11jul92,smb  moved CPU definitions to types/vxCpu.h
04jul92,jcf  cleaned up.
28jun92,smb  reworked for ANSI lib.
22jun92,rrr  added MIPS CPU_FAMILY
16jun92,jwt  added (CPU_FAMILY = SPARC) for (CPU == SPARClite).
26may92,rrr  the tree shuffle
17mar92,yao  added _STACK_GROWS_DOWN/UP.  added macros ROUND_UP/DOWN,
	     ALIGNED, MEM_ROUND_UP/DOWN, STACK_ROUND_UP/DOWN, MEM_ALIGNED.
	     changed copyright notice.  included arch.h.  moved ffsMSB
	     definitions for 960 to changed BYTE_ORDER to _BYTE_ORDER,
	     BIG/LITTLE_ENDIAN to _BIG/LITTLE_ENDIAN.  arch960.h.  removed
	     conditional include of r3k/arch.h.
09jan91,wmd  conditionalized out ffsMSB inline definition to shut up
 	     ansi warnings.
11nov91,jpb  added definition for R3K CPU_FAMILY.
28oct91,wmd  for lack of better place -  added Intel's 960 ffsMSB
	     inline definition here.
04oct91,rrr  passed through the ansification filter
	      -fixed #else and #endif
	      -changed READ, WRITE and UPDATE to O_RDONLY O_WRONLY and ...
	      -changed copyright notice
25sep91,yao  added CPU32.
10sep91,wmd  added MIPS to conditional for BIG_ENDIAN byte order.
20aug91,ajm  added MIPS_R3k support.
14aug91,del  (intel) added I960KA/KB defines.
29apr91,hdn  added defines and macros for TRON architecture
31mar91,del  added #define of BYTE_ORDER for network etc.
25oct90,dnw  changed to allow NULL to be redefined.
25oct90,shl  combined CPU test for I960KB and I960CA into one.
...deleted pre v2a history - see RCS
*/

#ifndef __INCvxWorksCommonh
#define __INCvxWorksCommonh


#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

#if	!defined(EOF) || (EOF!=(-1))
#define EOF		(-1)
#endif

#if	!defined(FALSE) || (FALSE!=(0))
#define FALSE		(0)
#endif

#if	!defined(TRUE) || (TRUE!=(1))
#define TRUE		(1)
#endif


#define NONE		(-1)	/* for times when NULL won't do */
#define EOS		'\0'	/* C string terminator */


/* return status values */

#define OK		0
#define ERROR		(-1)

/* timeout defines */

#define NO_WAIT		0
#define WAIT_FOREVER	(-1U)

/* low-level I/O input, output, error fd's */

#define	STD_IN	0
#define	STD_OUT	1
#define	STD_ERR	2

/* modes - must match O_RDONLY/O_WRONLY/O_RDWR in ioLib.h! */

#define VX_READ		0
#define VX_WRITE	1

/* SYSTEM types */

#define V7		1	/* ATT version 7 */
#define SYS_V		2	/* ATT System 5 */
#define BSD_4_2		3	/* Berkeley BSD 4.2 */

#if 0
/* 
 * These macros are not currently being used and have been removed.
 * In particular, the INET macro should not be defined in this file as
 * it would break IPv6Only stack builds.
 */
/* network configuration parameters */

#define	INET		/* include internet protocols */
#undef  BSD             /* remove any previous definition */
#define	BSD	44	/* BSD 4.4 like OS */
#define	BSDDEBUG	/* turn on debug */
#define	GATEWAY		/* tables to be initialized for gateway routing */
#endif

/* common macros */

#define MSB(x)	(((x) >> 8) & 0xff)	  /* most signif byte of 2-byte integer */
#define LSB(x)	((x) & 0xff)		  /* least signif byte of 2-byte integer*/
#define MSW(x) (((x) >> 16) & 0xffff) /* most signif word of 2-word integer */
#define LSW(x) ((x) & 0xffff) 		  /* least signif byte of 2-word integer*/

/* swap the MSW with the LSW of a 32 bit integer */
#define WORDSWAP(x) (MSW(x) | (LSW(x) << 16))

#define LLSB(x)	((x) & 0xff)		/* 32bit word byte/word swap macros */
#define LNLSB(x) (((x) >> 8) & 0xff)
#define LNMSB(x) (((x) >> 16) & 0xff)
#define LMSB(x)	 (((x) >> 24) & 0xff)
#define LONGSWAP(x) ((LLSB(x) << 24) | \
		     (LNLSB(x) << 16)| \
		     (LNMSB(x) << 8) | \
		     (LMSB(x)))

#define OFFSET(structure, member)	/* byte offset of member in structure*/\
		((long) &(((structure *) 0) -> member))

#define MEMBER_SIZE(structure, member)	/* size of a member of a structure */\
		(sizeof (((structure *) 0) -> member))

#define NELEMENTS(array)		/* number of elements in an array */ \
		(sizeof (array) / sizeof ((array) [0]))

#define FOREVER	for (;;)

/* 
 * min & max are C++ standard functions which are provided by the user 
 * side C++ libraries
 */

#if !defined(__cplusplus)

#ifndef max
#define max(x, y)	(((x) < (y)) ? (y) : (x))
#endif

#ifndef min
#define min(x, y)	(((x) < (y)) ? (x) : (y))
#endif

#endif /* !__cplusplus */

/* storage class specifier definitions */

#define FAST	register
#define IMPORT	extern
#define LOCAL	static

#endif  /* _POSIX_xxx_SOURCE */


#include <types/vxCpu.h>		/* must come before vxArch.h include */
#ifndef _WRS_KERNEL
#include <types/vxCpuX.h>
#endif  /* _WRS_KERNEL */
#include <types/vxArch.h>		/* must come before include of types */

#ifndef _ASMLANGUAGE
#include <types/vxParams.h>		/* must come before include of types */
#include <types/vxTypesBase.h>		/* must come between vxArch/vxTypes */
#include <types/vxTypes.h>
#include <types/vxTypesOld.h>
#include <types/vxWind.h>
#endif	/* _ASMLANGUAGE */


#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

#define ROUND_UP(x, align)	(((long) (x) + ((long) align - 1)) & \
                                 ~((long) align - 1))
#define ROUND_DOWN(x, align)	((long) (x) & ~((long) align - 1))
#define ALIGNED(x, align)	(((long) (x) & ((long) align - 1)) == 0)

/* In the kernel, the alignment sizes are a property of the specific
 * architecture varient we build for. In user mode, the alignment sizes
 * are passed from the kernel to the RTP via the aux_v mechanism, so we
 * need to override the definitions here. This needs to be done now,
 * rather than in types/vxArch.h because we're referencing variables of
 * type size_t, which aren't defined until vxTypes.h
 */

#ifndef _WRS_KERNEL
#ifndef _ASMLANGUAGE

/* XXX Note - there is probably an issue with Assembly builds with this
 * model. This needs to be fixed.
 */

extern size_t allocAlignSize;
extern size_t stackAlignSize;
extern size_t cacheAlignSize;
extern size_t vmPageSize;

#ifdef _ALLOC_ALIGN_SIZE
#undef _ALLOC_ALIGN_SIZE
#endif /* _ALLOC_ALIGN_SIZE */
#define _ALLOC_ALIGN_SIZE       allocAlignSize

#ifdef _STACK_ALIGN_SIZE
#undef _STACK_ALIGN_SIZE
#endif /* _STACK_ALIGN_SIZE */
#define _STACK_ALIGN_SIZE       stackAlignSize

#ifdef _CACHE_ALIGN_SIZE
#undef _CACHE_ALIGN_SIZE
#endif /* _CACHE_ALIGN_SIZE */
#define _CACHE_ALIGN_SIZE       cacheAlignSize

#define VM_PAGE_SIZE_GET()      vmPageSize


#endif /* _ASMLANGUAGE */
#endif /* _WRS_KERNEL */

#if defined(_ASMLANGUAGE) && !defined(_WRS_KERNEL)

/* XXX only exclude these macros if user mode & assembly build */

#else  /* defined(_ASMLANGUAGE) && !defined(_WRS_KERNEL) */

#define MEM_ROUND_UP(x)		ROUND_UP(x, _ALLOC_ALIGN_SIZE)
#define MEM_ROUND_DOWN(x)	ROUND_DOWN(x, _ALLOC_ALIGN_SIZE)
#define STACK_ROUND_UP(x)	ROUND_UP(x, _STACK_ALIGN_SIZE)
#define STACK_ROUND_DOWN(x)	ROUND_DOWN(x, _STACK_ALIGN_SIZE)
#define MEM_ALIGNED(x)		ALIGNED(x, _ALLOC_ALIGN_SIZE)

#endif /* defined(_ASMLANGUAGE) && !defined(_WRS_KERNEL) */

/* default SMP max CPUs value, in case arch specific code did not define it */

#ifndef VX_MAX_SMP_CPUS
#define VX_MAX_SMP_CPUS   4
#endif

/*
 * In case _TOOL_FAMILY isn't defined, we shall assume gnu for
 * backward compatibility.  All this is so we can include
 * the toolMacros.h file from the h/tool/$(_TOOL_FAMILY) directory
 * path.  This is needed because for host tool building we can't
 * always specify additional include paths for compiler tool
 * builds.
 */

#ifndef _VX_TOOL_FAMILY
#   define _VX_TOOL_FAMILY gnu
#endif 

/* All this to generate a string we can #include */

#define TOOL_HDR_STRINGIFY(x)  #x
#define TOOL_HDR(tc, file) TOOL_HDR_STRINGIFY(tool/tc/file)
#define TOOL_HEADER(file) TOOL_HDR(_VX_TOOL_FAMILY,file)

#define ARCH_HDR(dir,file)	TOOL_HDR_STRINGIFY(arch/dir/file)
#define ARCH_HEADER(file)	ARCH_HDR(_VX_ARCH_DIR,file)

/* Now include the correct header file */
#include TOOL_HEADER (toolMacros.h)
#include <tool/common/private/toolMacrosP.h>

#endif  /* _POSIX_xxx_SOURCE */


#ifdef _WRS_KERNEL
#include <version.h>	/* kernel version numbers */
#endif

/*
 * Before we insist on defining __P here make sure there
 * aren't any previous occurrences! __P may clash with
 * the compiler's definition of it.
 */

#ifndef __P
#define	__P(protos)	protos		/* Use ANSI C proto */
#endif

/*
 * The bitwise operator is denoted by ! in ColdFire assembly.
 * _WRS_BIT_OR should be used in macros that may be used in
 * both C and assembly sources.
 */
#ifndef _WRS_BIT_OR
#if defined(__coldfire) && defined(_ASMLANGUAGE)
#define _WRS_BIT_OR	!
#else
#define _WRS_BIT_OR	|
#endif
#endif

/*
 * In VxWorks 32-bit some API that were transitioned from using generic
 * function pointer parameters (FUNCPTR, VOIDFUNCPTR) to using fully-qualified
 * function pointers trigger compilation errors or warnings with legacy code.
 * Therefore the _WRS_KEEP_USING_FUNCPTR macro is defined to maintain the
 * usage of the generic function pointers parameters in those function's
 * signatures. Customers can switch to using the fully-qualified function
 * pointer parameters by defining _WRS_STOP_USING_FUNCPTR in their code,
 * prior to any inclusion of VxWorks header files, or on the compiler's
 * command line (via the -D option).
 *
 * Note that the _WRS_KEEP_USING_FUNCPTR macro is undefined for VxWorks 64-bit
 * so only the function signatures using fully-qualified function pointer
 * parameters are available on this variant of the system.
 */

#ifdef _WRS_CONFIG_LP64
#ifdef _WRS_KEEP_USING_FUNCPTR
#error Defining _WRS_KEEP_USING_FUNCPTR is not allowed in VxWorks 64-bit.
#endif /* _WRS_KEEP_USING_FUNCPTR */
#else
#ifndef _WRS_STOP_USING_FUNCPTR
#define _WRS_KEEP_USING_FUNCPTR
#endif /* _WRS_STOP_USING_FUNCPTR */
#endif /* _WRS_CONFIG_LP64 */

#endif /* __INCvxWorksCommonh */

