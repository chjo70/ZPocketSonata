/* ctype.h - ANSI standard ctype functions header */

/* Copyright 1992, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01l,29apr10,pad  Moved extern C statement after include statements.
01k,22jan07,mcm  Fix for WIND00068130 - type-casting the input to be an
                 unsigned char
01j,18mar04,mcm  Fix for SPR 95066 - moving isascii/toascii from vxWorks.h
01i,24mar04,sn   fixed __toupper and __tolower to only evaluate arg once
01h,30nov01,f_b  Remove is*() macros when compiling in C++ mode
01g,19aug93,dvs  added outside parens for __toupper & __tolower (SPR #2340)
01f,25jan93,smb  added __STDC__ wrapper for __ctype table, SPR 1924.
01e,22sep92,rrr  added support for c++
01d,19aug92,smb  fixed SPR #1471, toupper & tolower checks for valid argument.
01d,11jul92,smb  reversed order of function decl. and defines.
01c,11jul92,smb  added __STDC__.
01b,04jul92,jcf  cleaned up.
01a,03jul92,smb  written
*/

#ifndef __INCctypeh
#define __INCctypeh

#include "types/vxANSI.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__STDC__) || defined(__cplusplus)

extern int      isalnum(int __c);
extern int      isalpha(int __c);
extern int      iscntrl(int __c);
extern int      isdigit(int __c);
extern int      isgraph(int __c);
extern int      islower(int __c);
extern int      isprint(int __c);
extern int      ispunct(int __c);
extern int      isspace(int __c);
extern int      isupper(int __c);
extern int      isxdigit(int __c);
extern int      tolower(int __c);
extern int      toupper(int __c);

#else   /* __STDC__ */

extern int      isalnum();
extern int      isalpha();
extern int      iscntrl();
extern int      isdigit();
extern int      isgraph();
extern int      islower();
extern int      isprint();
extern int      ispunct();
extern int      isspace();
extern int      isupper();
extern int      isxdigit();
extern int      tolower();
extern int      toupper();

#endif  /* __STDC__ */

#define _C_UPPER         0x1
#define _C_LOWER         0x2
#define _C_NUMBER        0x4
#define _C_WHITE_SPACE   0x8
#define _C_PUNCT         0x10
#define _C_CONTROL       0x20
#define _C_HEX_NUMBER    0x40
#define _C_B             0x80

#if defined(__STDC__) || defined(__cplusplus)
extern  const unsigned char *__ctype;
extern  const unsigned char *__ctype_tolower;
extern  const unsigned char *__ctype_toupper;
#else   /* __STDC__ */
extern  unsigned char *__ctype;
extern  unsigned char *__ctype_tolower;
extern  unsigned char *__ctype_toupper;
#endif  /* __STDC__ */

#define __isalpha(c)    (__ctype[(unsigned char)(c)] & (_C_UPPER | _C_LOWER))
#define __isupper(c)    (__ctype[(unsigned char)(c)] & (_C_UPPER))
#define __islower(c)    (__ctype[(unsigned char)(c)] & (_C_LOWER))
#define __isdigit(c)    (__ctype[(unsigned char)(c)] & (_C_NUMBER))
#define __isxdigit(c)   (__ctype[(unsigned char)(c)] & (_C_HEX_NUMBER))
#define __isspace(c)    (__ctype[(unsigned char)(c)] & (_C_WHITE_SPACE | _C_CONTROL))
#define __ispunct(c)    (__ctype[(unsigned char)(c)] & (_C_PUNCT))
#define __isalnum(c)    (__ctype[(unsigned char)(c)] & (_C_UPPER | _C_LOWER | _C_NUMBER))
#define __isprint(c)    (__ctype[(unsigned char)(c)] & (_C_PUNCT | _C_UPPER | _C_LOWER | \
				       _C_WHITE_SPACE | _C_NUMBER))
#define __isgraph(c)    (__ctype[(unsigned char)(c)] & (_C_PUNCT | _C_UPPER | _C_LOWER | \
				       _C_NUMBER))
#define __iscntrl(c)    (__ctype[(unsigned char)(c)] & (_C_CONTROL | _C_B))
#define __toupper(c)    (__ctype_toupper[(unsigned char)(c)])
#define __tolower(c)    (__ctype_tolower[(unsigned char)(c)])

#ifndef __cplusplus
#define isalpha(c)      __isalpha((unsigned char)(c))
#define isupper(c)      __isupper((unsigned char)(c))
#define islower(c)      __islower((unsigned char)(c))
#define isdigit(c)      __isdigit((unsigned char)(c))
#define isxdigit(c)     __isxdigit((unsigned char)(c))
#define isspace(c)      __isspace((unsigned char)(c))
#define ispunct(c)      __ispunct((unsigned char)(c))
#define isalnum(c)      __isalnum((unsigned char)(c))
#define isprint(c)      __isprint((unsigned char)(c))
#define isgraph(c)      __isgraph((unsigned char)(c))
#define iscntrl(c)      __iscntrl((unsigned char)(c))
#define toupper(c)      __toupper((unsigned char)(c))
#define tolower(c)      __tolower((unsigned char)(c))
#endif

#define isascii(c)	((unsigned char)(c) <= 0177)
#define toascii(c)	((unsigned char)(c) & 0177)

#ifdef __cplusplus
}
#endif

#endif /* __INCctypeh */
