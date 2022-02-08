#ifndef __Idiab_xmacros
#define __Idiab_xmacros
/*
 * #defines which are compatible with those from the 
 * Dinkum libraries.  This allows modified header files
 * to work in the C environment.  In a Dinkum only
 * library these would be defined in yvals.h
 */


/* NAMESPACE CONTROL */
#if !defined(__DCC__) || defined(__ETOA__)
#define _SUPPORTS_NAMESPACES 1
#else
#define _SUPPORTS_NAMESPACES 0
#endif

#ifdef __cplusplus

#if _SUPPORTS_NAMESPACES

#ifdef _STD_USING
  #define _C_STD_BEGIN	namespace std {
  #define _C_STD_END	}
#if 0
  #define _CSTD		std::
#endif
#else /* _STD_USING */
  #define _C_STD_BEGIN	/* empty */
  #define _C_STD_END	/* empty */
#if 0
  #define _CSTD		::
#endif
  #define _GLOBAL_USING
#endif /* _STD_USING */

#ifdef _STD_LINKAGE
#define _C_LIB_DECL	extern "C++" {
#define _END_C_LIB_DECL }
#else /* _STD_LINKAGE */
#define _C_LIB_DECL	extern "C" {
#define _END_C_LIB_DECL }
#endif /* _STD_LINKAGE */ 

#define _STD_BEGIN	namespace std {
#define _STD_END	}
#if 0
#define _STD		std::
#endif

#else  /* _SUPPORTS_NAMESPACES */

#define _C_STD_BEGIN	/* empty */
#define _C_STD_END	/* empty */
#define _CSTD		::

#define _C_LIB_DECL	extern "C" {
#define _END_C_LIB_DECL }

#define _STD_BEGIN
#define _STD_END
#define _STD

#define _USING_NAMESPACE_STD

#endif /* _SUPPORTS_NAMESPACES */

#define _EXTERN_C	extern "C" {
#define _END_EXTERN_C	}

#ifdef __STRICT_ANSI__
#define __NO_LONG_LONG 1
#endif
#else  /* __cplusplus */

#undef	_STD_USING

#define _C_STD_BEGIN
#define _C_STD_END
#define _CSTD

#define _C_LIB_DECL
#define _END_C_LIB_DECL

#define _STD_BEGIN
#define _STD_END
#define _STD

#define _EXTERN_C
#define _END_EXTERN_C

#endif /* __cplusplus */

/* END OF NAMESPACE CONTROL */

#ifndef __RESTRICT
#define __RESTRICT
#endif

#ifndef __size_t
#ifndef	_TYPE_size_t
#if defined(_LP64)
#define	_TYPE_size_t	typedef unsigned long size_t
#else
#define	_TYPE_size_t	typedef unsigned int size_t
#endif /* _LP64 */
#endif /* _TYPE_size_t */
#endif

#ifndef	__wchar_t
#ifndef	_TYPE_wchar_t
#define	_TYPE_wchar_t	typedef unsigned short wchar_t
#endif /* _TYPE_wchar_t */
#endif

#ifndef	_TYPE_wint_t
#define	_TYPE_wint_t	typedef unsigned short wint_t
#endif /* _TYPE_wint_t */

#endif /* __Idiab_xmacros */
