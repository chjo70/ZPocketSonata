/* stddef.h standard header */
#ifndef _STDDEF
#define _STDDEF
#ifndef _YVALS
 #include <yvals.h>
#endif /* _YVALS */

_C_STD_BEGIN
		/* macros */
#if !defined(_NO_WINDRIVER_MODIFICATIONS)
 #if defined(_STDDEF) || defined(__need_NULL)
  #undef NULL
  #undef __need_NULL
  #ifdef __cplusplus
   #if defined(__GNUG__) || defined(__DCC__)
    #define NULL __null
   #else
    #define NULL 0
   #endif /* __GNUG__ etc */
  #else
   #ifdef __vxworks__
    #define NULL 0
   #else
    #define NULL ((void *)0)
   #endif /* __vxworks__ */
  #endif /* __cplusplus */
 #endif /* _STDDEF etc */
#else
 #ifndef NULL
  #define NULL  _NULL
 #endif /* NULL */
#endif /* _NO_WINDRIVER_MODIFICATIONS */

#ifndef offsetof

 #if __EDG__
  #define offsetof(T, member) ((_Sizet)__INTADDR__(&(((T *)0)->member)))

 #elif defined(__cplusplus) && ((__GNUC__ == 3) && (3 < __GNUC_MINOR__))
  #define offsetof(T, member) \
	(__offsetof__ (reinterpret_cast<_CSTD size_t> \
	(&reinterpret_cast<char &> \
	(static_cast<T *>(0)->member))))

 #else /* __EDG__ */
  #define offsetof(T, member)	((_CSTD size_t)&(((T *)0)->member))
 #endif /* __EDG__ */

#endif /* offsetof */

		/* type definitions */

 #if !defined(_PTRDIFF_T) && !defined(_PTRDIFFT) \
	&& !defined(_PTRDIFF_T_DEFINED)
  #define _PTRDIFF_T
  #define _PTRDIFFT
  #define _PTRDIFF_T_DEFINED
  #define _STD_USING_PTRDIFF_T
typedef _Ptrdifft ptrdiff_t;
 #endif /* !defined(_PTRDIFF_T) etc. */
_C_STD_END

#include <b_std_size_t.h>

_C_STD_BEGIN
 #if !defined(_WCHART) && !defined(_WCHAR_T_DEFINED)
  #define _WCHART
  #define _WCHAR_T_DEFINED
typedef _Wchart wchar_t;
 #endif /* _WCHART etc. */

 #if defined(__need_wint_t) && defined (__CYGWIN__)
  #ifndef _WINTT
   #define _WINTT
typedef _Wintt wint_t;
  #endif /* _WINTT */

 #endif /* defined(__need_wint_t) && defined (__CYGWIN__) */

 #if __STDC_WANT_LIB_EXT1__

  #if !defined(_RSIZE_T_DEFINED)
   #define _RSIZE_T_DEFINED
typedef size_t rsize_t;
  #endif /* _RSIZE_T_DEFINED */

 #endif /* __STDC_WANT_LIB_EXT1__ */

 #ifdef __cplusplus

 #if _HAS_NULLPTR_T
typedef decltype(nullptr) nullptr_t;

 #else /* _HAS_NULLPTR_T */
typedef void *nullptr_t;
 #endif /* _HAS_NULLPTR_T */

typedef double max_align_t;	// NOT long double
 #endif /* __cplusplus */
_C_STD_END
#endif /* _STDDEF */

 #if defined(_STD_USING)

  #ifdef _STD_USING_PTRDIFF_T
using _CSTD ptrdiff_t;
  #endif /* _STD_USING_PTRDIFF_T */

  #ifdef _STD_USING_SIZE_T
using _CSTD size_t;
  #endif /* _STD_USING_SIZE_T */

 #if __STDC_WANT_LIB_EXT1__
using _CSTD rsize_t;
 #endif /* __STDC_WANT_LIB_EXT1__ */

 #ifdef __cplusplus
#if !defined(_NO_WINDRIVER_MODIFICATIONS)
using _CSTD nullptr_t;
using _CSTD max_align_t;
#else
_STD_BEGIN
using _CSTD nullptr_t;
using _CSTD max_align_t;
_STD_END
#endif /* _NO_WINDRIVER_MODIFICATIONS */
 #endif /* __cplusplus */

 #endif /* defined(_STD_USING) */

/*
 * Copyright (c) by P.J. Plauger. All rights reserved.
 * Consult your license regarding permissions and restrictions.
V6.50:1278 */
