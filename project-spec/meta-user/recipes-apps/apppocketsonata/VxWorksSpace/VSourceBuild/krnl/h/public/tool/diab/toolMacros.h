/* toolMacros.h - compile time macros for Diab C compiler */

/*
 * Copyright (c) 2001-2006, 2008-2010, 2014-2016 Wind River Systems, Inc.
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
21jul15,dlk  Make PREFETCH macros no-ops also for diab version <= 5.9.1.0
             (V7COR-3265)
18jun15,dlk  Make PREFETCH macros no-ops for ARM, as __builtin_prefetch()
             is not yet supported.
10nov14,ylu  Added _WRS_TOC_DATA for PPC64 (F2518)
12may10,cww  Added _WRS_SECTION_TEXT and _WRS_SECTION_RODATA
08feb10,mcm  Fix for WIND00193234
05nov09,mcm  LP64 updates
24jul09,kk   added macro _WRS_USAGE_WARNING()
15jul08,to   renamed expect macros to _WRS_LIKELY and _WRS_UNLIKELY
             moved SDA macros out of _WRS_NO_SPECIAL_SECTIONS conditionals
16jun08,zl   added _WRS_BARRIER()
13may08,dlk  Revert previous workaround, there's a better one.
09may08,dlk  Workaround for diab .data.fast/SDA conflict (WIND00123084).
29apr08,zl   added expect and prefetch macros.
25mar08,to   added _WRS_SDA_DATA, _WRS_SDA_BSS and _WRS_SDA_CONST
19dec06,aeg  added _WRS_FUNC_NORETURN()
09sep05,jln  added _WRS_ABSOLUTE_EXTERN
08aug05,wap  Add section relocation macros
17mar04,dat  remove leading underscore from _absSymbols_xxx (95052)
05mar04,dat  temp fix for c++ and deprecated
05feb04,dat  add macros for _WRS_ABSOLUTE
26nov03,dat  Adding INLINE and DEPRECATED
12oct03,dat  new macros for V7 of portable C guide.
23sep03,zl   added _WRS_CONSTRUCTOR definition
26nov01,dat  New macros for alignment checking and unaligned copies
14nov01,dat  Adding underscores to macro names
18oct01,jab  fixed WRS_ASM macro
04sep01,dat  written (assumes Diab 4.4b or later)
*/

#ifndef __INCtoolMacrosh
#define __INCtoolMacrosh

#define _WRS_PACK_ALIGN(x) __attribute__((packed, aligned(x)))

#define _WRS_ASM(x) __asm volatile (x)

#define _WRS_UNQUALIFIED_ASM(x) __asm (x)

#define _WRS_BARRIER(x) __asm volatile (x)

#define _WRS_DATA_ALIGN_BYTES(x) __attribute__((aligned(x)))

/* This tool uses the ANSI variadic macro style */

#undef  _WRS_GNU_VAR_MACROS	/* Diab uses ANSI syntax */

/* New macros for alignment issues */

#define _WRS_ALIGNOF(x)		sizeof(x,1)

#define _WRS_UNALIGNED_COPY(pSrc, pDest, size) \
	(memcpy ((pDest), (pSrc), (size)))

#define _WRS_ALIGN_CHECK(ptr, type) \
	(((int)(ptr) & ( _WRS_ALIGNOF(type) - 1)) == 0 ? TRUE : FALSE)

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
 * start of the declaration rather than at the end, as a workaround
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

/* TOC section macros */

#define _WRS_TOC_DATA	__attribute__ ((__section__ (".toc")))

/* general purpose section set macro */

#define _WRS_SECTION_SET(sectionName) \
    __attribute__ ((__section__ (sectionName)))

/*
 * macro for static initializer (constructor) definitions; assumes
 * Diab 5.2 or later with constructor support.
 */

#define _WRS_CONSTRUCTOR(rtn,lvl) \
	__attribute__((constructor(lvl))) void _STI__##lvl##__##rtn (void)

/*
 * New Basix macros, (Portable Coding Guide, v7)
 *
 * HAS_GCC_ASM_SYNTAX if Gnu inline assembly syntax is supported.
 * HAS_DCC_ASM_SYNTAX if Diab inline assembly function syntax is supported.
 * INLINE for static inline C functions, (prefix)
 * DEPRECATED for obsolete API warnings. (postfix)
 * USAGE_WARNING for API warnings - currently replicate of DEPRECATED. Future
 *                                  plan to add this.
 */

#undef  _WRS_HAS_GCC_ASM_SYNTAX
#define _WRS_HAS_DCC_ASM_SYNTAX
#define _WRS_INLINE		static __inline__

#ifdef __cplusplus
#define _WRS_DEPRECATED(x)	/* temp workaround for c++ compiler failure */
#else
#define _WRS_DEPRECATED(x)	__attribute__((deprecated(x)))
#endif

#define _WRS_USAGE_WARNING(x)	_WRS_DEPRECATED(x)

/* (New V7) For absolute symbol support. (use with semicolon) */

#define _WRS_ABSOLUTE(name,value) \
	const long name __attribute__((absolute)) = (long)value

#define _WRS_ABSOLUTE_EXTERN(name) \
	extern const char name[]


/* code optimization macros using compiler extensions */

#define _WRS_FUNC_NORETURN		__attribute__((noreturn))

#define _WRS_LIKELY(x)			__builtin_expect(!!(x), 1)
#define _WRS_UNLIKELY(x)		__builtin_expect(!!(x), 0)

#if _VX_CPU_FAMILY == _VX_ARM || __VERSION_NUMBER__ <= 5910
/*
 * TCDIAB-13419: dcc for ARM does not yet support __builtin_prefetch().
 * TCDIAB-13552: diab version 5.9.1.0 build error when __builtin_prefetch()
 * is used.
 * If either of these is fixed, adjust the test above.
 */
#define _WRS_READ_PREFETCH(ptr)         do { } while ((0))
#define _WRS_WRITE_PREFETCH(ptr)        do { } while ((0))
#else
#define _WRS_READ_PREFETCH(ptr)         __builtin_prefetch((ptr),0)
#define _WRS_WRITE_PREFETCH(ptr)        __builtin_prefetch((ptr),1)
#endif


/* prefix and suffix to surround absolute symbol declarations (nops for diab)*/

#define _WRS_ABSOLUTE_BEGIN(x) \
	extern STATUS absSymbols_##x (void); \
	STATUS absSymbols_##x (void) {return OK;}
#define _WRS_ABSOLUTE_END


/*
 * For backward compatibility with v5 of portable C coding guide.
 *
 * These are now obsolete, please don't use them.
 */

#define WRS_PACK_ALIGN(x)	_WRS_PACK_ALIGN(x)
#define WRS_ASM(x)		_WRS_ASM(x)
#define WRS_DATA_ALIGN_BYTES(x)	_WRS_DATA_ALIGN_BYTES(x)
#undef WRS_GNU_VAR_MACROS

#endif /* __INCtoolMacrosh */
