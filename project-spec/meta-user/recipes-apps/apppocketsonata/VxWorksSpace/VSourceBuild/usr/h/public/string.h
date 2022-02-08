/* string.h standard header */
#ifndef _STRING
#define _STRING

#ifndef _YVALS
 #include <yvals.h>
#endif /* _YVALS */

_C_STD_BEGIN
		/* macros */
#ifndef NULL
 #define NULL	_NULL
#endif /* NULL */

		/* type definitions */
_C_STD_END

#include <b_std_size_t.h>

_C_STD_BEGIN
		/* declarations */
_C_LIB_DECL
int memcmp(const void *, const void *, size_t);
void *memcpy(void *_Restrict, const void *_Restrict, size_t);
void *memset(void *, int, size_t);
char *strcat(char *_Restrict, const char *_Restrict);
int strcmp(const char *, const char *);
char *strcpy(char *_Restrict, const char *_Restrict);
size_t strlen(const char *);

void *memmove(void *, const void *, size_t);
int strcoll(const char *, const char *);
size_t strcspn(const char *, const char *);
char *strerror(int);
char *strncat(char *_Restrict, const char *_Restrict, size_t);
int strncmp(const char *, const char *, size_t);
char *strncpy(char *_Restrict, const char *_Restrict, size_t);
size_t strspn(const char *, const char *);
char *strtok(char *_Restrict, const char *_Restrict);
size_t strxfrm(char *_Restrict, const char *_Restrict, size_t);

#if !defined(_NO_WINDRIVER_MODIFICATIONS)
void *memmem(const void *, size_t, const void *, size_t);
void *memimem(const void *, size_t, const void *, size_t);
#endif /* !_NO_WINDRIVER_MODIFICATIONS */

#ifdef __RTP__
char *strtok_r(char *, const char *, char **);
int strerror_r(int, char *, size_t);
#ifdef _VXWORKS_COMPATIBILITY_MODE
int (_vxworks_strerror_r)(int , char *);
#define strerror_r(x, y, z)     _vxworks_strerror_r((x), (y))
#endif /* _VXWORKS_COMPATIBILITY_MODE */
#endif

#if !defined(__STRICT_ANSI__)
#define __USE_POSIX
#endif

#ifdef __USE_POSIX
void *memccpy(void *, const void *, int, size_t);
char *strdup(const char *);
#endif

 #if _ADDED_C_LIB
char *strdup(const char *);
int strcasecmp(const char *, const char *);
int strncasecmp(const char *, const char *, size_t);
char *strtok_r(char *, const char *, char **);
 #endif /* _ADDED_C_LIB */

_END_C_LIB_DECL

 #if defined(__cplusplus) && !defined(_NO_CPP_INLINES)
		// INLINES AND OVERLOADS, for C++
 #define _Const_return const

_C_LIB_DECL
const char *strchr(const char *, int);
const char *strpbrk(const char *, const char *);
const char *strrchr(const char *, int);
const char *strstr(const char *, const char *);
_END_C_LIB_DECL

extern "C++" {
inline char *strchr(char *_Str, int _Ch)
	{	// call with const first argument
	return ((char *)_CSTD strchr((const char *)_Str, _Ch));
	}

inline char *strpbrk(char *_Str1, const char *_Str2)
	{	// call with const first argument
	return ((char *)_CSTD strpbrk((const char *)_Str1, _Str2));
	}

inline char *strrchr(char *_Str, int _Ch)
	{	// call with const first argument
	return ((char *)_CSTD strrchr((const char *)_Str, _Ch));
	}

inline char *strstr(char *_Str1, const char *_Str2)
	{	// call with const first argument
	return ((char *)_CSTD strstr((const char *)_Str1, _Str2));
	}
}	// extern "C++"

 #else /* defined(__cplusplus) && !defined(_NO_CPP_INLINES)*/
_C_LIB_DECL
 #define _Const_return

char *strchr(const char *, int);
char *strpbrk(const char *, const char *);
char *strrchr(const char *, int);
char *strstr(const char *, const char *);
_END_C_LIB_DECL
 #endif /* defined(__cplusplus) && !defined(_NO_CPP_INLINES) */

 #ifndef _MEMCHR
  #define _MEMCHR

  #if defined(__cplusplus) && !defined(_NO_CPP_INLINES)
_C_LIB_DECL
const void *memchr(const void *, int, size_t);
_END_C_LIB_DECL

extern "C++" {
inline void *memchr(void *_Str, int _Ch, size_t _Num)
	{	// call with const first argument
	return ((void *)_CSTD memchr((const void *)_Str, _Ch, _Num));
	}
}	// extern "C++"

  #else /* defined(__cplusplus) && !defined(_NO_CPP_INLINES) */
_C_LIB_DECL
void *memchr(const void *, int, size_t);
_END_C_LIB_DECL
  #endif /* defined(__cplusplus) && !defined(_NO_CPP_INLINES) */

 #endif /* _MEMCHR */

 #if __STDC_WANT_LIB_EXT1__
_C_LIB_DECL

  #if !defined(_ERRNO_T_DEFINED)
   #define _ERRNO_T_DEFINED
typedef int errno_t;
  #endif /* _ERRNO_T_DEFINED */

  #if !defined(_RSIZE_T_DEFINED)
   #define _RSIZE_T_DEFINED
typedef size_t rsize_t;
  #endif /* _RSIZE_T_DEFINED */

errno_t memcpy_s(void *_Restrict, rsize_t,
	const void *_Restrict, rsize_t);
errno_t memmove_s(void *, rsize_t,
	const void *, rsize_t);
#if !defined(_CSTRING_)
_END_C_LIB_DECL
_C_STD_END
_C_LIB_DECL
_CSTD errno_t  memset_s(void *, _CSTD rsize_t,
	int, _CSTD rsize_t);
_END_C_LIB_DECL
_C_STD_BEGIN
_C_LIB_DECL
#endif
errno_t strcpy_s(char *_Restrict, rsize_t,
	const char *_Restrict);
errno_t strncpy_s(char *_Restrict, rsize_t,
	const char *_Restrict, rsize_t);
errno_t strcat_s(char *_Restrict, rsize_t,
	const char *_Restrict);
errno_t strncat_s(char *_Restrict, rsize_t,
	const char *_Restrict, rsize_t);
char *strtok_s(char *_Restrict, rsize_t *_Restrict,
	const char *_Restrict, char **_Restrict);

errno_t strerror_s(char *, rsize_t, errno_t);
size_t strerrorlen_s(errno_t);

size_t strnlen_s(const char *_Restrict, size_t);
_END_C_LIB_DECL
 #endif /* __STDC_WANT_LIB_EXT1__ */

#if !defined(_NO_WINDRIVER_MODIFICATIONS)
  #if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
    size_t strlcpy(char *, const char *, size_t);
    size_t strlcat(char *, const char *, size_t);
  #endif  /* _POSIX_xxx_SOURCE */
#endif /* !_NO_WINDRIVER_MODIFICATIONS */

_C_STD_END
#endif /* _STRING */

 #if defined(_STD_USING)

  #ifdef _STD_USING_SIZE_T
using _CSTD size_t;
  #endif /* _STD_USING_SIZE_T */

using _CSTD memchr; using _CSTD memcmp;
using _CSTD memcpy; using _CSTD memmove; using _CSTD memset;
using _CSTD strcat; using _CSTD strchr; using _CSTD strcmp;
using _CSTD strcoll; using _CSTD strcpy; using _CSTD strcspn;
using _CSTD strerror; using _CSTD strlen; using _CSTD strncat;
using _CSTD strncmp; using _CSTD strncpy; using _CSTD strpbrk;
using _CSTD strrchr; using _CSTD strspn; using _CSTD strstr;
using _CSTD strtok; using _CSTD strxfrm;

 #if _ADDED_C_LIB
using _CSTD strdup; using _CSTD strcasecmp;
using _CSTD strncasecmp; using _CSTD strtok_r;
 #endif /* _ADDED_C_LIB */

 #if __STDC_WANT_LIB_EXT1__
using _CSTD errno_t;
using _CSTD rsize_t;

using _CSTD memcpy_s;
using _CSTD memmove_s;
using _CSTD strcpy_s;
using _CSTD strncpy_s;
using _CSTD strcat_s;
using _CSTD strncat_s;
using _CSTD strtok_s;
using _CSTD strerror_s;
using _CSTD strerrorlen_s;
using _CSTD strnlen_s;
 #endif /* __STDC_WANT_LIB_EXT1__ */

#if !defined(_NO_WINDRIVER_MODIFICATIONS)
  #ifdef __RTP__
    using _CSTD strerror_r; using _CSTD strtok_r;
    #ifdef _VXWORKS_COMPATIBILITY_MODE
      using _CSTD _vxworks_strerror_r;
    #endif /* _VXWORKS_COMPATIBILITY_MODE */
  #endif /* __RTP__ */
#endif /* _NO_WINDRIVER_MODIFICATIONS */

 #endif /* defined(_STD_USING) */

/*
 * Copyright (c) by P.J. Plauger. All rights reserved.
 * Consult your license regarding permissions and restrictions.
V6.50:1278 */
