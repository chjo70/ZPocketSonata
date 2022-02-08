/* toolMacros.h - compile time macros for GNU C compiler */

/*
 * Copyright (c) 2001-2006, 2008-2010, 2014, 2016 Wind River Systems, Inc.
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
14apr16,gls  Added _WRS_SECTION_SET
14jan14,vhe removed reference to SIMPENTIUM build
02a,22jul11,mcm  Fix for WIND00283661.
01z,12may10,cww  Added _WRS_SECTION_RODATA and _WRS_SECTION_TEXT
01y,08feb10,mcm  Fix for WIND00193234
01x,05nov09,mcm  LP64 updates
01w,24jul09,kk   added macro _WRS_USAGE_WARNING()
01w,11feb09,cww  update _WRS_LIKELY and _WRS_UNLIKELY macros for LP64
01v,15jul08,to   renamed expect macros to _WRS_LIKELY and _WRS_UNLIKELY
                 moved SDA macros out of _WRS_NO_SPECIAL_SECTIONS conditionals
01u,16jun08,zl   added _WRS_BARRIER()
01t,13may08,dlk  Revert previous workaround, there's a better one.
01s,09may08,dlk  Workaround for diab .data.fast/SDA conflict (WIND00123084).
01r,29apr08,zl   added expect and prefetch macros
01q,25mar08,to   added _WRS_SDA_DATA, _WRS_SDA_BSS and _WRS_SDA_CONST
01p,18dec06,aeg  added _WRS_FUNC_NORETURN
01o,07jun06,jpb  Updated for POSIX namespace conformance.
		 Changed C preprocessor macro CPU_FAMILY to _VX_CPU_FAMILY.
01n,09sep05,jln  added _WRS_ABSOLUTE_EXTERN
01m,08aug05,wap  Add section relocation macros
01l,02oct04,mcm  Fixing definition of _WRS_ABSOLUTE_ for Pentium.
01k,25aug04,h_k  updated _WRS_ABSOLUTE for the arches which require
                 specific semantics, such as arm and sh. (SPR #100726)
01j,30jul04,mcm  Undefining WRS_GNU_VAR_MACROS since GCC 3.3.2 supports the
                 ANSI syntax
01i,17mar04,dat  remove leading underscore from _absSymbols_xxx (95052)
01h,05mar04,dat  fix abs symbols
01g,05feb04,dat  add macros for _WRS_ABSOLUTE
01f,26nov03,dat  Adding INLINE and DEPRECATED
01e,16oct03,dat  New macros for INLINE both C and ASM
01d,23sep03,zl   added _WRS_CONSTRUCTOR definition
01c,26nov01,dat  New macros for alignment checking and unaligned copies
01b,14nov01,dat  Adding underscores to macro names
01a,18apr01,dat  written
*/

#ifndef __INCtoolMacrosh
#define __INCtoolMacrosh

#define _WRS_PACK_ALIGN(x) __attribute__((packed, aligned(x)))

#define _WRS_ASM(x) __asm__ volatile (x)

#define _WRS_UNQUALIFIED_ASM(x) __asm__ (x)

#define _WRS_BARRIER(x) __asm volatile (x ::: "memory")

#define _WRS_DATA_ALIGN_BYTES(x) __attribute__((aligned(x)))

#undef _WRS_GNU_VAR_MACROS	/* GCC 3.3.2 supports the ANSI syntax */

/* Macros for alignment issues */

#define _WRS_ALIGNOF(x)		__alignof__(x)

#define _WRS_ALIGN_CHECK(ptr, type) \
	(((int)(ptr) & ( _WRS_ALIGNOF(type) - 1)) == 0 ? TRUE : FALSE)

#define _WRS_UNALIGNED_COPY(pSrc, pDest, size) \
	( __builtin_memcpy ((pDest), (void *)(pSrc), size))

/*
 * Macros to force code or data into specific sections. These
 * can be used to force the compiler to place a given piece of
 * code or data into a separate section. The idea is to improve
 * cache usage by either clustering frequently referenced code
 * close together, or moving infrequently used code (i.e. "run-once"
 * init routines that are only used during bootstrap) out of the
 * way. The "init" sections are used for the latter case, while
 * the "fast" sections are used to group performance-critical
 * routines together.
 *
 * Note: _WRS_FASTDATA or _WRS_INITDATA should occur at the
 * start of a declaration rather than at the end, as a workaround
 * for WIND00123084. For example, use
 * \cs
 *   extern _WRS_FASTDATA void * myFastPtr;
 * \ce
 * rather than
 * \cs
 *   extern void * myFastPtr _WRS_FASTDATA;
 * \ce
 */

#ifndef _WRS_NO_SPECIAL_SECTIONS
#define _WRS_INITTEXT	__attribute__ ((__section__ (".text.init")))
#define _WRS_FASTTEXT	__attribute__ ((__section__ (".text.fast")))
#define _WRS_INITDATA	__attribute__ ((__section__ (".data.init")))
#define _WRS_FASTDATA	__attribute__ ((__section__ (".data.fast")))
#else
#define _WRS_INITTEXT
#define _WRS_FASTTEXT
#define _WRS_INITDATA
#define _WRS_FASTDATA
#endif

/* Standard sections */

#define _WRS_SECTION_TEXT	__attribute__ ((__section__ (".text")))
#define _WRS_SECTION_RODATA	__attribute__ ((__section__ (".rodata")))

/* SDA section macros */

#define _WRS_SDA_DATA	__attribute__ ((__section__ (".sdata")))
#define _WRS_SDA_BSS	__attribute__ ((__section__ (".sbss")))
#define _WRS_SDA_CONST	__attribute__ ((__section__ (".sdata2")))

/* general purpose section set macro */

#define _WRS_SECTION_SET(sectionName) \
    __attribute__ ((__section__ (sectionName)))

/*
 * macro for static initializer (constructor) definitions; assumes
 * GCC 3.3 or later with C constructor support.
 */

#define _WRS_CONSTRUCTOR(rtn,lvl) \
	__attribute__((constructor(lvl))) void _STI__##lvl##__##rtn (void)

/*
 * New Basix macros, (Portable Coding Guide, v7)
 *
 * HAS_GCC_ASM_SYNTAX if Gnu inline assembly syntax is supported.
 * HAS_DCC_ASM_SYNTAX if Diab inline assembly function syntax is supported.
 * INLINE for static inline C functions,
 * DEPRECATED for obsolete API warnings.
 * USAGE_WARNING for API warnings - currently same as DEPRECATED, future plan 
 *                                  to add this.
 */


#define _WRS_HAS_GCC_ASM_SYNTAX
#undef  _WRS_HAS_DCC_ASM_SYNTAX
#define _WRS_INLINE		static __inline__
#define _WRS_DEPRECATED(x)	__attribute__((deprecated))
#define _WRS_USAGE_WARNING(x)	_WRS_DEPRECATED(x)

#ifndef	LEADING_UNDERSCORE
#define	LEADING_UNDERSCORE	FALSE	/* default in B6 except SH arch */
#endif	/* LEADING_UNDERSCORE */

#if	(LEADING_UNDERSCORE == TRUE)
#define _WRS_ABSOLUTE(name,value)	_WRS_ABSOLUTE_(_##name,value)
#else	/* LEADING_UNDERSCORE == FALSE */
#define _WRS_ABSOLUTE(name,value)	_WRS_ABSOLUTE_(name,value)
#endif	/* LEADING_UNDERSCORE == TRUE */

/* (New V7) For absolute symbol support. (use with semicolon) */

#if	(_VX_CPU_FAMILY == _VX_ARM) || (_VX_CPU_FAMILY == _VX_ARM_THUMB)
/*
 * GNU/ARM backend does not have a proper operand modifier which does not
 * produces prefix # followed by value, such as %0 for PPC, PENTIUM, MIPS
 * and %O0 for SH. The workaround made here is using %B0 which converts
 * the value to ~(value). Thus "n"(~(value)) is set in operand constraint
 * to output (value) in the ARM specific _WRS_ABSOLUTE macro.
 * (The related SPR is #101463.)
 */

#define _WRS_ABSOLUTE_(name,value) \
        __asm__ (".globl\t"#name \
                "\n\t.equ\t"#name",%B0" \
                "\n\t.type\t"#name",%%object" \
                :: "n"(~(value)))

#elif	(_VX_CPU_FAMILY == _VX_SH)
#define _WRS_ABSOLUTE_(name,value) \
        __asm__ (".globl\t"#name \
                "\n\t.equ\t"#name",%O0" \
                "\n\t.type\t"#name",@object" \
                :: "n"(value))

#elif	(_VX_CPU_FAMILY == _VX_I80X86) || (_VX_CPU_FAMILY == _VX_SIMNT) || (_VX_CPU_FAMILY == _VX_SIMLINUX)
#define _WRS_ABSOLUTE_(name,value) \
        __asm__ (".globl\t"#name \
                "\n\t.equ\t"#name",%P0" \
                "\n\t.type\t"#name",@object" \
                :: "n"(value))

#else	/* _VX_CPU_FAMILY != _VX_ARM && _VX_CPU_FAMILY != _VX_ARM_THUMB && _VX_CPU_FAMILY != _VX_SH && _VX_CPU_FAMILY != _VX_PENTIUM */
#define _WRS_ABSOLUTE_(name,value) \
        __asm__ (".globl\t"#name \
                "\n\t.equ\t"#name",%0" \
                "\n\t.type\t"#name",@object" \
                :: "n"(value))

#endif	/* _VX_CPU_FAMILY == _VX_ARM || _VX_CPU_FAMILY == _VX_ARM_THUMB || _VX_CPU_FAMILY == _VX_SH && _VX_CPU_FAMILY != _VX_PENTIUM */

#define _WRS_ABSOLUTE_EXTERN(name)  \
	extern const char name[]

/* code optimization macros using compiler extensions */

#define _WRS_FUNC_NORETURN		__attribute__((noreturn))

#define _WRS_LIKELY(x)			__builtin_expect((long)!!(x), 1L)
#define _WRS_UNLIKELY(x)		__builtin_expect((long)!!(x), 0L)

#define _WRS_READ_PREFETCH(ptr)		__builtin_prefetch((ptr),0)
#define _WRS_WRITE_PREFETCH(ptr)	__builtin_prefetch((ptr),1)


/* Prefix and suffix for assembly declarations (private function) */

#define _WRS_ABSOLUTE_BEGIN(x) \
	extern STATUS absSymbols_##x (void); \
        STATUS absSymbols_##x (void) {

#define _WRS_ABSOLUTE_END   \
        return OK; }


/*
 * For compatibility with v5 of portable C coding guide
 *
 * These versions are obsolete, please don't use them
 */

#define WRS_PACK_ALIGN(x)	_WRS_PACK_ALIGN(x)
#define WRS_ASM(x)		_WRS_ASM(x)
#define WRS_DATA_ALIGN_BYTES(x)	_WRS_DATA_ALIGN_BYTES(x)
#undef WRS_GNU_VAR_MACROS

#endif /* __INCtoolMacrosh */
