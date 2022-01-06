/* vxCpuX.h - VxWorks CPU definitions undefine header */

/*
 * Copyright (c) 2006 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
 * vxCpuX.h is generated -- DO NOT EDIT
 *
 * The template for this file is vxCpuX.in
 * See also vxCpuXp.h and vxCpuXf.h
 *
 * This file is generated using the cpuGen tool.
 * To add CPU types or otherwise change the substance,
 * edit $WIND_BUILD/misc/architecturedb
 */

/*
modification history
--------------------
01d,11jul06,jpb  Removed undef _WRS_CPU_FAMILY_PREPENDS_UNDERSCORE
01c,20jun06,jpb  Updated for POSIX namespace conformance.  
		 Changed C preprocessor macro CPU to _VX_CPU.
01b,20feb06,mil  Converted to template for cpuGen.
01a,03feb06,mil  Created, manual version.
*/

/*
DESCRIPTION
The purpose of this file is to undefine unused CPU type and CPU family 
macros, in order to keep illegal names in the compilation environment 
to a minimum for strictly POSIX compliant applications (identified by 
any of the defined macros _POSIX_C_SOURCE, _XOPEN_SOURCE, or 
_POSIX_AEP_RT_CONTROLLER_C_SOURCE).  The CPU type and CPU family macros 
that are being used for a specific instance of compilation should remain 
defined and not affected.  e.g. if PPC604 is the CPU being used, then 
the values for both PPC604 and PPC should remain to be defined.
All others CPU types and families, such as PPC405 or I80X86, should be 
undefined.  A defined value should not have the value of negative one 
(-1).  This is because macros that are not defined will automatically 
gets -1.  e.g. if CPU is PPC604, and PPC604 is defined to a value of 94, 
the preprocessor conditional #if (CPU == PPC603) should evaluate to 
FALSE because 94 is not equal to -1.  Similar is true to the use of 
CPU_FAMILY.
*/

#ifndef __INCvxCpuXh
#define __INCvxCpuXh

/* -------------------- undef CPU types -------------------- */

#if 0
/* empty #if block */

#elif (_VX_CPU == _VX_MC68000)
#include <types/vxCpuXp.h>
#define _VX_MC68000	1
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define MC68000	_VX_MC68000
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_MC68010)
#include <types/vxCpuXp.h>
#define _VX_MC68010	2
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define MC68010	_VX_MC68010
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_MC68020)
#include <types/vxCpuXp.h>
#define _VX_MC68020	3
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define MC68020	_VX_MC68020
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_MC68030)
#include <types/vxCpuXp.h>
#define _VX_MC68030	4
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define MC68030	_VX_MC68030
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_MC68040)
#include <types/vxCpuXp.h>
#define _VX_MC68040	5
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define MC68040	_VX_MC68040
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_MC68LC040)
#include <types/vxCpuXp.h>
#define _VX_MC68LC040	6
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define MC68LC040	_VX_MC68LC040
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_MC68060)
#include <types/vxCpuXp.h>
#define _VX_MC68060	7
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define MC68060	_VX_MC68060
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_CPU32)
#include <types/vxCpuXp.h>
#define _VX_CPU32	8
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define CPU32	_VX_CPU32
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_SPARClite)
#include <types/vxCpuXp.h>
#define _VX_SPARClite	11
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define SPARClite	_VX_SPARClite
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_I960CA)
#include <types/vxCpuXp.h>
#define _VX_I960CA	21
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define I960CA	_VX_I960CA
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_I960KA)
#include <types/vxCpuXp.h>
#define _VX_I960KA	22
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define I960KA	_VX_I960KA
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_I960KB)
#include <types/vxCpuXp.h>
#define _VX_I960KB	23
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define I960KB	_VX_I960KB
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_I960JX)
#include <types/vxCpuXp.h>
#define _VX_I960JX	24
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define I960JX	_VX_I960JX
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_I960HX)
#include <types/vxCpuXp.h>
#define _VX_I960HX	25
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define I960HX	_VX_I960HX
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_G100)
#include <types/vxCpuXp.h>
#define _VX_G100	31
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define G100	_VX_G100
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_G200)
#include <types/vxCpuXp.h>
#define _VX_G200	32
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define G200	_VX_G200
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_MIPS32)
#include <types/vxCpuXp.h>
#define _VX_MIPS32	41
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define MIPS32	_VX_MIPS32
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_MIPS64)
#include <types/vxCpuXp.h>
#define _VX_MIPS64	42
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define MIPS64	_VX_MIPS64
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_MIPSI2)
#include <types/vxCpuXp.h>
#define _VX_MIPSI2	43
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define MIPSI2	_VX_MIPSI2
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_MIPSI3)
#include <types/vxCpuXp.h>
#define _VX_MIPSI3	44
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define MIPSI3	_VX_MIPSI3
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_MIPSI32)
#include <types/vxCpuXp.h>
#define _VX_MIPSI32	45
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define MIPSI32	_VX_MIPSI32
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_MIPSI32R2)
#include <types/vxCpuXp.h>
#define _VX_MIPSI32R2	46
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define MIPSI32R2	_VX_MIPSI32R2
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_MIPSI64)
#include <types/vxCpuXp.h>
#define _VX_MIPSI64	47
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define MIPSI64	_VX_MIPSI64
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_MIPSI64R2)
#include <types/vxCpuXp.h>
#define _VX_MIPSI64R2	48
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define MIPSI64R2	_VX_MIPSI64R2
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_MIPS64_64)
#include <types/vxCpuXp.h>
#define _VX_MIPS64_64	49
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define MIPS64_64	_VX_MIPS64_64
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_AM29030)
#include <types/vxCpuXp.h>
#define _VX_AM29030	51
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define AM29030	_VX_AM29030
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_AM29200)
#include <types/vxCpuXp.h>
#define _VX_AM29200	52
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define AM29200	_VX_AM29200
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_AM29035)
#include <types/vxCpuXp.h>
#define _VX_AM29035	53
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define AM29035	_VX_AM29035
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_I80386)
#include <types/vxCpuXp.h>
#define _VX_I80386	81
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define I80386	_VX_I80386
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_I80486)
#include <types/vxCpuXp.h>
#define _VX_I80486	82
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define I80486	_VX_I80486
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_PENTIUM)
#include <types/vxCpuXp.h>
#define _VX_PENTIUM	83
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define PENTIUM	_VX_PENTIUM
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_PENTIUM2)
#include <types/vxCpuXp.h>
#define _VX_PENTIUM2	84
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define PENTIUM2	_VX_PENTIUM2
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_PENTIUM3)
#include <types/vxCpuXp.h>
#define _VX_PENTIUM3	85
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define PENTIUM3	_VX_PENTIUM3
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_PENTIUM4)
#include <types/vxCpuXp.h>
#define _VX_PENTIUM4	86
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define PENTIUM4	_VX_PENTIUM4
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_PENTIUM64)
#include <types/vxCpuXp.h>
#define _VX_PENTIUM64	87
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define PENTIUM64	_VX_PENTIUM64
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_CORE2)
#include <types/vxCpuXp.h>
#define _VX_CORE2	88
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define CORE2	_VX_CORE2
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_X86_64)
#include <types/vxCpuXp.h>
#define _VX_X86_64	89
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define X86_64	_VX_X86_64
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_ULTRASPARC)
#include <types/vxCpuXp.h>
#define _VX_ULTRASPARC	111
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define ULTRASPARC	_VX_ULTRASPARC
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_SH7000)
#include <types/vxCpuXp.h>
#define _VX_SH7000	131
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define SH7000	_VX_SH7000
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_SH7600)
#include <types/vxCpuXp.h>
#define _VX_SH7600	132
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define SH7600	_VX_SH7600
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_SH7040)
#include <types/vxCpuXp.h>
#define _VX_SH7040	133
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define SH7040	_VX_SH7040
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_SH7700)
#include <types/vxCpuXp.h>
#define _VX_SH7700	134
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define SH7700	_VX_SH7700
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_SH7410)
#include <types/vxCpuXp.h>
#define _VX_SH7410	135
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define SH7410	_VX_SH7410
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_SH7729)
#include <types/vxCpuXp.h>
#define _VX_SH7729	136
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define SH7729	_VX_SH7729
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_SH7750)
#include <types/vxCpuXp.h>
#define _VX_SH7750	137
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define SH7750	_VX_SH7750
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_MCORE10)
#include <types/vxCpuXp.h>
#define _VX_MCORE10	151
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define MCORE10	_VX_MCORE10
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_MCORE15)
#include <types/vxCpuXp.h>
#define _VX_MCORE15	152
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define MCORE15	_VX_MCORE15
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_MCORE200)
#include <types/vxCpuXp.h>
#define _VX_MCORE200	153
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define MCORE200	_VX_MCORE200
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_MCORE300)
#include <types/vxCpuXp.h>
#define _VX_MCORE300	154
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define MCORE300	_VX_MCORE300
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_MCF5200)
#include <types/vxCpuXp.h>
#define _VX_MCF5200	161
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define MCF5200	_VX_MCF5200
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_MCF5400)
#include <types/vxCpuXp.h>
#define _VX_MCF5400	162
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define MCF5400	_VX_MCF5400
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_FR500)
#include <types/vxCpuXp.h>
#define _VX_FR500	171
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define FR500	_VX_FR500
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_MAP1000A)
#include <types/vxCpuXp.h>
#define _VX_MAP1000A	181
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define MAP1000A	_VX_MAP1000A
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_MAPCA)
#include <types/vxCpuXp.h>
#define _VX_MAPCA	182
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define MAPCA	_VX_MAPCA
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_ATOM)
#include <types/vxCpuXp.h>
#define _VX_ATOM	192
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define ATOM	_VX_ATOM
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_CORE)
#include <types/vxCpuXp.h>
#define _VX_CORE	193
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define CORE	_VX_CORE
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_NEHALEM)
#include <types/vxCpuXp.h>
#define _VX_NEHALEM	194
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define NEHALEM	_VX_NEHALEM
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_WESTMERE)
#include <types/vxCpuXp.h>
#define _VX_WESTMERE	195
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define WESTMERE	_VX_WESTMERE
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_SANDYBRIDGE)
#include <types/vxCpuXp.h>
#define _VX_SANDYBRIDGE	196
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define SANDYBRIDGE	_VX_SANDYBRIDGE
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_IVYBRIDGE)
#include <types/vxCpuXp.h>
#define _VX_IVYBRIDGE	197
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define IVYBRIDGE	_VX_IVYBRIDGE
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_HASWELL)
#include <types/vxCpuXp.h>
#define _VX_HASWELL	198
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define HASWELL	_VX_HASWELL
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_BROADWELL)
#include <types/vxCpuXp.h>
#define _VX_BROADWELL	199
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define BROADWELL	_VX_BROADWELL
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_SILVERMONT)
#include <types/vxCpuXp.h>
#define _VX_SILVERMONT	200
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define SILVERMONT	_VX_SILVERMONT
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_AIRMONT)
#include <types/vxCpuXp.h>
#define _VX_AIRMONT	201
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define AIRMONT	_VX_AIRMONT
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_SKYLAKE)
#include <types/vxCpuXp.h>
#define _VX_SKYLAKE	202
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define SKYLAKE	_VX_SKYLAKE
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_GOLDMONT)
#include <types/vxCpuXp.h>
#define _VX_GOLDMONT	203
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define GOLDMONT	_VX_GOLDMONT
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_ARMARCH7)
#include <types/vxCpuXp.h>
#define _VX_ARMARCH7	1125
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define ARMARCH7	_VX_ARMARCH7
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_ARMARCH7M)
#include <types/vxCpuXp.h>
#define _VX_ARMARCH7M	1127
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define ARMARCH7M	_VX_ARMARCH7M
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_ARMARCH8A)
#include <types/vxCpuXp.h>
#define _VX_ARMARCH8A	1128
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define ARMARCH8A	_VX_ARMARCH8A
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_PPCE500V2)
#include <types/vxCpuXp.h>
#define _VX_PPCE500V2	2001
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define PPCE500V2	_VX_PPCE500V2
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_PPCE6500)
#include <types/vxCpuXp.h>
#define _VX_PPCE6500	2002
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define PPCE6500	_VX_PPCE6500
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_PPC603)
#include <types/vxCpuXp.h>
#define _VX_PPC603	2003
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define PPC603	_VX_PPC603
#endif /* _WRS_KERNEL or non-POSIX */

#elif (_VX_CPU == _VX_PPC604)
#include <types/vxCpuXp.h>
#define _VX_PPC604	2004
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define PPC604	_VX_PPC604
#endif /* _WRS_KERNEL or non-POSIX */


#else  /* CPU */

/* else clause is needed for cases if value is both CPU and CPU_FAMILY */
# include <types/vxCpuXp.h>

#endif /* CPU */


/* ------------------- undef CPU families ------------------ */

#if (_VX_CPU_FAMILY == _VX_MC680X0)
#include <types/vxCpuXf.h>
#define _VX_MC680X0	9
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define MC680X0	_VX_MC680X0
#endif  /* _WRS_KERNEL or non-POSIX */
#endif  /* MC680X0 */

#if (_VX_CPU_FAMILY == _VX_SPARC)
#include <types/vxCpuXf.h>
#define _VX_SPARC	10
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define SPARC	_VX_SPARC
#endif /* _WRS_KERNEL or non-POSIX*/
#endif  /* SPARC */

#if (_VX_CPU_FAMILY == _VX_I960)
#include <types/vxCpuXf.h>
#define _VX_I960	20
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define I960	_VX_I960
#endif  /* _WRS_KERNEL or non-POSIX */
#endif  /* I960 */

#if (_VX_CPU_FAMILY == _VX_TRON)
#include <types/vxCpuXf.h>
#define _VX_TRON	30
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define TRON	_VX_TRON
#endif  /* _WRS_KERNEL or non-POSIX */
#endif  /* TRON */

#if (_VX_CPU_FAMILY == _VX_MIPS)
#include <types/vxCpuXf.h>
#define _VX_MIPS	40
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define MIPS	_VX_MIPS
#endif  /* _WRS_KERNEL or non-POSIX */
#endif  /* MIPS */

#if (_VX_CPU_FAMILY == _VX_AM29XXX)
#include <types/vxCpuXf.h>
#define _VX_AM29XXX	50
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define AM29XXX	_VX_AM29XXX
#endif  /* _WRS_KERNEL or non-POSIX */
#endif  /* AM29XXX */

#if (_VX_CPU_FAMILY == _VX_SIMSPARCSUNOS)
#include <types/vxCpuXf.h>
#define _VX_SIMSPARCSUNOS	60
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define SIMSPARCSUNOS	_VX_SIMSPARCSUNOS
#endif /* _WRS_KERNEL or non-POSIX*/
#endif  /* SIMSPARCSUNOS */

#if (_VX_CPU_FAMILY == _VX_SIMSPARCSOLARIS)
#include <types/vxCpuXf.h>
#define _VX_SIMSPARCSOLARIS	61
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define SIMSPARCSOLARIS	_VX_SIMSPARCSOLARIS
#endif /* _WRS_KERNEL or non-POSIX*/
#endif  /* SIMSPARCSOLARIS */

#if (_VX_CPU_FAMILY == _VX_SIMHPPA)
#include <types/vxCpuXf.h>
#define _VX_SIMHPPA	70
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define SIMHPPA	_VX_SIMHPPA
#endif /* _WRS_KERNEL or non-POSIX*/
#endif  /* SIMHPPA */

#if (_VX_CPU_FAMILY == _VX_I80X86)
#include <types/vxCpuXf.h>
#define _VX_I80X86	80
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define I80X86	_VX_I80X86
#endif  /* _WRS_KERNEL or non-POSIX */
#endif  /* I80X86 */

#if (_VX_CPU_FAMILY == _VX_SIMNT)
#include <types/vxCpuXf.h>
#define _VX_SIMNT	100
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define SIMNT	_VX_SIMNT
#endif /* _WRS_KERNEL or non-POSIX*/
#endif  /* SIMNT */

#if (_VX_CPU_FAMILY == _VX_SPARCV9)
#include <types/vxCpuXf.h>
#define _VX_SPARCV9	110
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define SPARCV9	_VX_SPARCV9
#endif  /* _WRS_KERNEL or non-POSIX */
#endif  /* SPARCV9 */

#if (_VX_CPU_FAMILY == _VX_ARM)
#include <types/vxCpuXf.h>
#define _VX_ARM	120
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define ARM	_VX_ARM
#endif  /* _WRS_KERNEL or non-POSIX */
#endif  /* ARM */

#if (_VX_CPU_FAMILY == _VX_SH32)
#include <types/vxCpuXf.h>
#define _VX_SH32	130
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define SH32	_VX_SH32
#endif /* _WRS_KERNEL or non-POSIX*/
#endif  /* SH32 */

#if (_VX_CPU_FAMILY == _VX_SH)
#include <types/vxCpuXf.h>
#define _VX_SH	130
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define SH	_VX_SH
#endif  /* _WRS_KERNEL or non-POSIX */
#endif  /* SH */

#if (_VX_CPU_FAMILY == _VX_MCORE)
#include <types/vxCpuXf.h>
#define _VX_MCORE	150
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define MCORE	_VX_MCORE
#endif  /* _WRS_KERNEL or non-POSIX */
#endif  /* MCORE */

#if (_VX_CPU_FAMILY == _VX_COLDFIRE)
#include <types/vxCpuXf.h>
#define _VX_COLDFIRE	160
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define COLDFIRE	_VX_COLDFIRE
#endif  /* _WRS_KERNEL or non-POSIX */
#endif  /* COLDFIRE */

#if (_VX_CPU_FAMILY == _VX_FRV)
#include <types/vxCpuXf.h>
#define _VX_FRV	170
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define FRV	_VX_FRV
#endif  /* _WRS_KERNEL or non-POSIX */
#endif  /* FRV */

#if (_VX_CPU_FAMILY == _VX_MAP1000)
#include <types/vxCpuXf.h>
#define _VX_MAP1000	180
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define MAP1000	_VX_MAP1000
#endif /* _WRS_KERNEL or non-POSIX*/
#endif  /* MAP1000 */

#if (_VX_CPU_FAMILY == _VX_MAP)
#include <types/vxCpuXf.h>
#define _VX_MAP	180
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define MAP	_VX_MAP
#endif  /* _WRS_KERNEL or non-POSIX */
#endif  /* MAP */

#if (_VX_CPU_FAMILY == _VX_SIMLINUX)
#include <types/vxCpuXf.h>
#define _VX_SIMLINUX	190
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define SIMLINUX	_VX_SIMLINUX
#endif /* _WRS_KERNEL or non-POSIX*/
#endif  /* SIMLINUX */

#if (_VX_CPU_FAMILY == _VX_PPCE500MC)
#include <types/vxCpuXf.h>
#define _VX_PPCE500MC	2000
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define PPCE500MC	_VX_PPCE500MC
#endif /* _WRS_KERNEL or non-POSIX*/
#endif  /* PPCE500MC */

#if (_VX_CPU_FAMILY == _VX_PPC)
#include <types/vxCpuXf.h>
#define _VX_PPC	2000
#if defined(_WRS_KERNEL) || (!defined(_POSIX_C_SOURCE) && \
	!defined(_XOPEN_SOURCE) && !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE))
#define PPC	_VX_PPC
#endif  /* _WRS_KERNEL or non-POSIX */
#endif  /* PPC */


/*
 * Check that _VX_CPU and _VX_CPU_FAMILY are still defined.
 */

#if !defined(_VX_CPU) || !defined(_VX_CPU_FAMILY)
#error _VX_CPU is not defined correctly
#endif

#endif /* __INCvxCpuXh */

