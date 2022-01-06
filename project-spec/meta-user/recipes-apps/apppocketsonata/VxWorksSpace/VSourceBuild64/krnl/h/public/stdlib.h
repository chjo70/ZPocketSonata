/* stdlib.h - standard library header file */

/*
 * Copyright (c) 1990-1993, 1999-2001, 2004, 2010, 2011, 2013, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01dec16,hcl  Added strtoll() and strtoull() (V7IOT-1)
29jun16,lau  Added __noreturn__ attribute for exit (V7COR-4112)
12nov13,cww  Added getenv_s() (WIND00430431)
11oct11,mcm  Cleanup (WIND00288946)
01jul10,jpb  Removed alias for taskExit.
29apr10,pad  Moved extern C statement after include statements.
13sep04,yvp  Made taskExit an alias for exit().
26mar01,max  Fixing a type
26mar01,max  According to the AltiVec ABI, we need to introduce new
             functions for memory allocation/deallocation:
             vec_malloc, vec_calloc, vec_realloc, and vec_free.
             They should be 16-byte aligned and are supposed to be used
             for memory operations with AltiVec vector data.
10oct00,sn   deleted size_t, wchar_t definitions
17feb99,mrs  Add C++ support for NULL, (SPR #25079).
15oct93,cd   added #ifndef _ASMLANGUAGE.
05feb93,smb  corrected prototype for strtoul
22sep92,rrr  added support for c++
21sep92,smb  reordered prototype list.
24jul92,smb  replaced types.
24jul92,smb  added prototypes for div_r and ldiv_r
             removed the ifndef for types div_t, ldiv_t and wchar_T
20jul92,smb  replaced modification history.
19jul92,smb  rewritten
04jul92,jcf  cleaned up.
26may92,rrr  the tree shuffle
25nov91,llk  added ansi definitions EXIT_FAILURE, EXIT_SUCCESS, RAND_MAX,
             MB_CUR_MAX.
             included more function prototypes.  Some are commented out.
04oct91,rrr  passed through the ansification filter
             -fixed #else and #endif
             -changed copyright notice
10jun91.del  added pragma for gnu960 alignment.
19oct90,shl  fixed typo in modhist 01a.
05oct90,dnw  created
*/

#ifndef __INCstdlibh
#define __INCstdlibh

#include <types/vxANSI.h>	/* includes types div_t, ldiv_t, wchar_t */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ASMLANGUAGE

#define EXIT_FAILURE	_PARM_EXIT_FAILURE
#define EXIT_SUCCESS	_PARM_EXIT_SUCCESS
#define MB_CUR_MAX	_PARM_MB_CUR_MAX
#define RAND_MAX	_PARM_RAND_MAX

#ifndef NULL
#if defined __GNUG__
#define NULL (__null)
#else
#if !defined(__cplusplus) && 0
#define NULL ((void*)0)
#else
#define NULL (0)
#endif
#endif
#endif

/* AltiVec ABI extension. As soon as we decided to force VxWorks
   to do all memory allocations with 16-byte alignment (At least
   for the EAR) we can just alias standard "malloc"-family
   functions with appropriate "vec_malloc" functions.
*/

#ifdef __VEC__ /* PowerPC AltiVec technology */

#define vec_malloc(SIZE)	malloc (SIZE)
#define vec_calloc(N,SIZE)	calloc (N,SIZE)
#define vec_realloc(PTR,SIZE)	realloc(PTR,SIZE)
#define vec_free(PTR)		free   (PTR)

#endif

#ifdef _TYPE_div_t
_TYPE_div_t;
#undef _TYPE_div_t
#endif

#ifdef _TYPE_ldiv_t
_TYPE_ldiv_t;
#undef _TYPE_ldiv_t
#endif

typedef struct {		/* used by mblen and mbtowc */
	unsigned char __state;
	unsigned short __wchar;
	} _Mbsave;

extern void	abort (void);
extern int	abs (int __i);
extern int	atexit (void (*__func)(void));
extern double	atof (const char *__s);
extern int	atoi (const char *__s);
extern long	atol (const char *__s);
extern void *	bsearch (const void *__key, const void *__base,
		         size_t __nelem, size_t __size,
		         int  (*__cmp)(const void *__ck, const void *__ce));
extern div_t	div (int __numer, int __denom);
extern long	labs (long __i);
extern ldiv_t	ldiv (long __numer, long __denom);
extern int	mblen (const char *__s, size_t __n);
extern size_t	mbstowcs (wchar_t *__wcs, const char *__s, size_t __n);
extern int	mbtowc (wchar_t *__pwc, const char *__s, size_t __n);
extern void	qsort (void *__base, size_t __nelem, size_t __size,
		       int  (*__cmp)(const void *__e1, const void *__e2));
extern int	rand (void);
extern void *	srand (unsigned int __seed);
extern double	strtod (const char *__s, char **__endptr);
extern long	strtol (const char *__s, char **__endptr, int __base);
extern long long strtoll (const char *__s, char **__endptr, int __base);
extern unsigned long strtoul (const char *__s, char **__endptr, int __base);
extern unsigned long long strtoull (const char *__s, char **__endptr, int __base);
extern int	system (const char *__s);
extern size_t	wcstombs (char *__s, const wchar_t *__wcs, size_t __n);
extern int	wctomb (char *__s, wchar_t __wchar);

extern void *	calloc (size_t __nelem, size_t __size);
extern void	exit (int __status) __attribute__((__noreturn__));
extern void	free (void *__ptr);
extern char *	getenv (const char *__name);
extern void *	malloc (size_t __size);
extern void *	realloc (void *__ptr, size_t __size);

#if _EXTENSION_WRS
extern void     div_r (int numer, int denom, div_t * divStructPtr);
extern void     ldiv_r (long numer, long denom, ldiv_t * divStructPtr);

extern int	getenv_s (size_t * len, char * value, size_t maxsize,
			  const char * name);
#endif

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCstdlibh */
