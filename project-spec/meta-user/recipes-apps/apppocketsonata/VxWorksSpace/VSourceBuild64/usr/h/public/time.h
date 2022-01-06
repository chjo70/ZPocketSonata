/* time.h standard header */
#ifndef _TIME
#define _TIME
#ifndef _YVALS
 #include <yvals.h>
#endif /* _YVALS */

#ifndef _NO_WINDRIVER_MODIFICATIONS
 #if __RTP__ && _HAS_POSIX_C_LIB
/* These functions have a different signature in VxWorks and POSIX. The "_"
 * versions of the functions will be taken from VxWorks and then used to
 * implement the VxWorks or POSIX functionality depending on the setting of
 * _VXWORKS_COMPATIBILITY_MODE */

/* prototype clock functions */

#include <clockLib.h>

/* prototype timer functions */

#include <timerLib.h>
#if defined(__cplusplus) && defined(_C_IN_NS)
_C_STD_BEGIN
using ::time_t;
using ::clockid_t;
#ifdef _CLOCK_T
using ::clock_t;
#endif
_C_STD_END
#endif
 #endif /* __RTP__ && _HAS_POSIX_C_LIB */
#endif /* !_NO_WINDRIVER_MODIFICATIONS */

_C_STD_BEGIN
		/* macros */
#ifdef _NO_WINDRIVER_MODIFICATIONS
 #define CLOCKS_PER_SEC _CPS
#else

#ifndef NULL
 #define NULL	_NULL
#endif /* NULL */

/* Used to convert the value returned by the clock() function into seconds. */
#if __RTP__
 #define CLOCKS_PER_SEC sysClkRateGet()
#else
#define CLOCKS_PER_SEC	_CPS
#endif
#endif /* !_NO_WINDRIVER_MODIFICATIONS */

		/* type definitions */
_C_STD_END

#if __RTP__
_C_LIB_DECL
extern int sysClkRateGet (void);
_END_C_LIB_DECL
#endif

#include <b_std_size_t.h>

_C_STD_BEGIN
 #if !defined(_CLOCK_T) && !defined(__clock_t_defined) \
	&& !defined(_BSD_CLOCK_T_DEFINED_)
  #define _CLOCK_T
  #define __clock_t_defined
  #define _BSD_CLOCK_T_DEFINED_
  #define _STD_USING_CLOCK_T
typedef long clock_t;
 #endif /* !defined(_CLOCK_T) etc. */

 #if !defined(_TIME_T) && !defined(__time_t_defined) \
	&& !defined(_BSD_TIME_T_DEFINED_) && !defined(_TIME_T_DEFINED)
  #define _TIME_T
  #define __time_t_defined
  #define _BSD_TIME_T_DEFINED_
  #define _TIME_T_DEFINED
  #define _STD_USING_TIME_T

typedef long time_t;
 #endif /* !defined(_TIME_T) etc. */

 #ifndef _TM_DEFINED
  #define _TM_DEFINED
struct tm
	{	/* date and time components */
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
	};
 #endif /* _TM_DEFINED */

 #if _HAS_POSIX_C_LIB

#ifndef _NO_WINDRIVER_MODIFICATIONS
  #if __RTP__
   #ifndef _TIMESPEC_DEFINED
    #define _TIMESPEC_DEFINED
struct timespec
        {
        time_t tv_sec;
        long tv_nsec;
        };
   #endif /* _TIMESPEC_DEFINED */

  #endif /* __RTP__ */ 
#else
  #if defined(__linux) || defined(__linux__) || defined(__CYGWIN__) \
	|| defined(__APPLE__) || 0x570 < __SUNPRO_CC

   #if !defined(_STRUCT_TIMESPEC)
    #define _STRUCT_TIMESPEC	1
struct timespec
	{	/* POSIX.4, needed for pthread_cond_timedwait */
	time_t tv_sec;
	long tv_nsec;
	};

    #if defined(__cplusplus) && 1 < _ALT_NS
_C_STD_END
using _CSTD timespec;
_C_STD_BEGIN
    #endif /* defined(__cplusplus) && 1 < _ALT_NS */

   #endif /* !defined(_STRUCT_TIMESPEC) */
  #endif /* defined(__linux) etc. */
#endif /* !_NO_WINDRIVER_MODIFICATIONS */

  #if !defined(_CLOCKID_T) && !defined(__clockid_t_defined)
   #define _CLOCKID_T
   #define __clockid_t_defined
   #define _STD_USING_CLOCKID_T
typedef int clockid_t;
  #endif /* !defined(_CLOCKID_T) && !defined(__clockid_t_defined) */

#ifndef _NO_WINDRIVER_MODIFICATIONS
  #if __RTP__
   #if !defined(_TIMER_T)
    #define _TIMER_T
struct __timer;
typedef struct __timer *timer_t;
   #endif /* !defined(_TIMER_T) */

#if (_POSIX_C_SOURCE != 200112L) || defined(_XOPEN_SOURCE) || \
        defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)  /* XSI options */
extern int   getdate_err;
extern int   daylight;
extern long  timezone;
#endif  /* _POSIX_xxx_SOURCE */
extern char  *tzname[];
  #endif /* __RTP__ */
#endif /* !_NO_WINDRIVER_MODIFICATIONS */

 #endif /* _HAS_POSIX_C_LIB */

_EXTERN_C	/* low-level functions */
time_t time(time_t *);
_END_EXTERN_C

_C_LIB_DECL	/* declarations */
char *asctime(const struct tm *);
clock_t clock(void);
char *ctime(const time_t *);
double difftime(time_t, time_t);
struct tm *gmtime(const time_t *);
struct tm *localtime(const time_t *);
time_t mktime(struct tm *);
size_t strftime(char *_Restrict, size_t,
	const char *_Restrict, const struct tm *_Restrict);

#ifndef _NO_WINDRIVER_MODIFICATIONS
 #if __RTP__ && _HAS_POSIX_C_LIB
/* These functions have a different signature in VxWorks and POSIX. The "_"
 * versions of the functions will be taken from VxWorks and then used to
 * implement the VxWorks or POSIX functionality depending on the setting of
 * _VXWORKS_COMPATIBILITY_MODE */
/* POSIX definitions - default */
char *asctime_r(const struct tm *, char *);             
char *ctime_r(const time_t *, char *);
struct tm *gmtime_r(const time_t *, struct tm *);
struct tm *localtime_r(const time_t *, struct tm *);
/* VxWorks definitions */
size_t _vxworks_asctime_r(const struct tm *, char *, size_t *);
char *_vxworks_ctime_r(const time_t *, char *, size_t *);
int _vxworks_gmtime_r(const time_t *, struct tm *);
int _vxworks_localtime_r(const time_t *, struct tm *);

  #ifdef _VXWORKS_COMPATIBILITY_MODE
   #define asctime_r(tm, buf, buflen)      _vxworks_asctime_r((tm), (buf), (buflen))
   #define ctime_r(tm, buf, buflen)        _vxworks_ctime_r((tm), (buf), (buflen))
   #define gmtime_r(tm, tmStruct)          _vxworks_gmtime_r((tm), (tmStruct))
   #define localtime_r(tm, tmStruct)       _vxworks_localtime_r((tm), (tmStruct))
  #endif /* _VXWORKS_COMPATIBILITY_MODE */

void tzset(void);

  #if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
       !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

   #ifndef _STATUS_DEFINED
    #define _STATUS_DEFINED
typedef int     STATUS;
   #endif /* _STATUS_DEFINED */

  #endif  /* _POSIX_xxx_SOURCE */
 #endif /* __RTP__ && _HAS_POSIX_C_LIB */
#endif /* !_NO_WINDRIVER_MODIFICATIONS */

_END_C_LIB_DECL

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

errno_t asctime_s(char *, rsize_t, const struct tm *);
errno_t ctime_s(char *, rsize_t, const time_t *);
struct tm *gmtime_s(const time_t *_Restrict,
	struct tm *_Restrict);
struct tm *localtime_s(const time_t *_Restrict,
	struct tm *_Restrict);
_END_C_LIB_DECL
 #endif /* __STDC_WANT_LIB_EXT1__ */
_C_STD_END
#endif /* _TIME */

 #if defined(_STD_USING)

  #ifdef _STD_USING_CLOCK_T
using _CSTD clock_t;
  #endif /* _STD_USING_CLOCK_T */

  #ifdef _STD_USING_SIZE_T
using _CSTD size_t;
  #endif /* _STD_USING_SIZE_T */

  #ifdef _STD_USING_TIME_T
using _CSTD time_t;
  #endif /* _STD_USING_TIME_T */

  #ifdef _STD_USING_CLOCKID_T
using _CSTD clockid_t;
  #endif /* _STD_USING_CLOCKID_T */

using _CSTD tm;
using _CSTD asctime; using _CSTD clock; using _CSTD ctime;
using _CSTD difftime; using _CSTD gmtime; using _CSTD localtime;
using _CSTD mktime; using _CSTD strftime; using _CSTD time;

 #if __STDC_WANT_LIB_EXT1__
using _CSTD errno_t;
using _CSTD rsize_t;

using _CSTD asctime_s;
using _CSTD ctime_s;
using _CSTD gmtime_s;
using _CSTD localtime_s;
 #endif /* __STDC_WANT_LIB_EXT1__ */

#if !defined(_NO_WINDRIVER_MODIFICATIONS)
  #if __RTP__ && _HAS_POSIX_C_LIB
    using _CSTD asctime_r; using _CSTD ctime_r;
    using _CSTD gmtime_r; using _CSTD localtime_r;
    using _CSTD tzset;
    #ifdef _VXWORKS_COMPATIBILITY_MODE
      using _CSTD _vxworks_asctime_r; using _CSTD _vxworks_ctime_r;
      using _CSTD _vxworks_gmtime_r; using _CSTD _vxworks_localtime_r;
    #endif /* _VXWORKS_COMPATIBILITY_MODE */
  #endif /* __RTP__ etc */
#endif /* _NO_WINDRIVER_MODIFICATIONS */

 #endif /* defined(_STD_USING) */

/*
 * Copyright (c) by P.J. Plauger. All rights reserved.
 * Consult your license regarding permissions and restrictions.
V6.50:1278 */
