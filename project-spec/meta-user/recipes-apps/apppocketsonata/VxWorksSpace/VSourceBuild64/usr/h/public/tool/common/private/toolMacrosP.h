/* toolMacros.h - compile time macros for GNU C compiler */

/*
 * Copyright (c) 2007-2009, 2014 Wind River Systems, Inc.
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
05feb14,h_k  added _WRS_UNINIT_WARNING_OVERRIDE() to work around compiler
             warnings for uninit variable on GCC.
08feb10,mcm  Fix for WIND00193234
27jan09,h_k  cleaned up a compiler warning.
21aug07,jmg  written
*/

#ifndef __INCtoolMacrosPh
#define __INCtoolMacrosPh
	
#include <types/vxArch.h>

/*
 * As soon as the diab compiler suports __attribute__ (alias) the
 * diab version and gnu will be the same.
 * At that point the macro _WRS_FUNC_ALIAS() should be made a
 * public macro.
 */

#if defined (__GNUC__)
#define _WRS_FUNC_ALIAS(func,aliasToFunc,retType) 			\
    retType aliasToFunc () __attribute__ ((alias (#func)));

#elif defined (__DCC__)

#define _WRS_ASM_ADD_QUOTES(x) _WRS_UNQUALIFIED_ASM ("	"#x)
	
#if defined (LEADING_UNDERSCORE) && (LEADING_UNDERSCORE == TRUE)
#define _WRS_FUNC_ALIAS(func,aliasToFunc,retType)			\
    _WRS_ASM_ADD_QUOTES (.globl _##func);				\
    _WRS_ASM_ADD_QUOTES (_##aliasToFunc = _##func);			\
    _WRS_ASM_ADD_QUOTES (.globl _##aliasToFunc)
#else	/* LEADING_UNDERSCORE */
#define _WRS_FUNC_ALIAS(func,aliasToFunc,retType)			\
    _WRS_ASM_ADD_QUOTES (.globl func);					\
    _WRS_ASM_ADD_QUOTES (aliasToFunc = func);				\
    _WRS_ASM_ADD_QUOTES (.globl aliasToFunc)	
#endif /* LEADING_UNDERSCORE */

#else /* __GNUC__ */
#error unsupported toolchain
#endif /* __GNUC__ */

/*
 * Work around the uninitialized variable compiler warnings mis-judged by GCC.
 * Other compilers do not need the workaround.
 */

#ifndef	_WRS_UNINIT_WARNING_OVERRIDE
#define _WRS_UNINIT_WARNING_OVERRIDE(var)	var
#endif	/* !_WRS_UNINIT_WARNING_OVERRIDE */

#endif /* __INCtoolMacrosPh */
