/*
 * Copyright (c) 2014-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/* modification history
-------------------------
22nov16,rjq  Fix crash when using NTP in 64bit board. (V7NET-1123)
16aug16,rjq  Upgrade ntp version to 4.2.8p8. (F7258)
20jan16,rjq  Upgrade ntp version to 4.2.8p4. (US71091)
15jun15,rjq  Upgrade ntp version to 4.2.8p2. (V7NET-498)
*/


#ifndef IPNTP_CONFIG_H
#define IPNTP_CONFIG_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * SNTP compile time configuration.
 */

/*
 ****************************************************************************
 * 2                    INCLUDE FILES
 ****************************************************************************
 */

#include <ipcom_config.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 3                    DEFINES
 ****************************************************************************
 */

#ifdef IPTESTENGINE
#if !defined(IPNTP_USE_TEST)
#define IPNTP_USE_TEST
#endif
#define WORDS_LITTLEENDIAN
#else
#include <types/vxCpu.h>        /* must come before vxArch.h include */
#include <types/vxArch.h>
#if (_BYTE_ORDER == _LITTLE_ENDIAN )
#define WORDS_LITTLEENDIAN
#elif (_BYTE_ORDER == _BIG_ENDIAN )
#define WORDS_BIGENDIAN
#endif
#endif

#ifdef _WRS_CONFIG_OPENSSL
#ifndef OPENSSL_FIPS
#define OPENSSL
#define AUTOKEY
#define USE_OPENSSL_CRYPTO_RAND
#define ISC_PLATFORM_OPENSSLHASH
#endif
#endif

#define NTP_VXWORKS_6
#define NTP_VXWORKS_7
#define SYS_VXWORKS
#define HAVE_ADDRINFO
#define ULONG_CONST(a) a ## UL

#ifndef NTP_VXWORKS_6 
typedef int socklen_t;
#endif

/* Directory separator, usually / or \ */
#define    DIR_SEP    '/'

/* Constant definitions for openlog() */
#ifndef USHRT_MAX
#define USHRT_MAX 65535
#endif
#ifndef UCHAR_MAX
#define UCHAR_MAX 255
#endif
#ifndef SHRT_MAX
#define SHRT_MAX 32767
#endif
#ifndef SHRT_MIN
#define SHRT_MIN -32768
#endif
#ifndef CHAR_MIN
#define CHAR_MIN -128
#endif
#ifndef CHAR_MAX 
#define CHAR_MAX 127
#endif
#ifndef CHAR_BIT
#define CHAR_BIT 8
#endif
#ifndef RAND_MAX
#define RAND_MAX 32767
#endif

#define HAVE_LONG_LONG_INT              1
#define HAVE_UNSIGNED_LONG_LONG_INT     1
#define HAVE_SIZE_T                     1 

#define HAVE_PTRDIFF_T      1
#define HAVE_SYS_TIME_H     1
#define HAVE_ALLOCA         1
#define HAVE_MKTIME         1
#define HAVE_TIMEGM         1   /* actually _mkgmtime */
#define HAVE_STRUCT_TIMESPEC  1

#define GETSOCKNAME_SOCKLEN_TYPE socklen_t

#define NEED_S_CHAR_TYPEDEF
#define SIZEOF_SIGNED_CHAR	1
#define SIZEOF_SHORT        2
#define SIZEOF_INT          4
#ifdef _WRS_CONFIG_LP64
#define SIZEOF_LONG         8
#else
#define SIZEOF_LONG         4
#endif
#define SIZEOF_LONG_LONG	8

#define OPEN_BCAST_SOCKET
#define REFCLOCK
#define CLOCK_LOCAL
#define MILLION             1000000     /* used for USECS_PER_SEC */
#define STDC_HEADERS
#define MAXHOSTNAMELEN      64
#define NTP_KEYSDIR         ""
#define MCAST

#ifdef MCAST
 #define TYPEOF_IP_MULTICAST_LOOP u_int
#endif

/* Bug 2978 mitigation -- unless defined elsewhere, do it here*/
#ifndef DYNAMIC_INTERLEAVE
#define DYNAMIC_INTERLEAVE 0
#endif


/* From Diab compiler info, Diab does NOT support "designated initializer" , like .tag = a, .display = b */
#define MISSING_C99_STRUCT_INIT    1  /* see [Bug 2728] */

/* C99 exact size integer support. */
#if defined(_MSC_VER) && _MSC_VER<1800
# define MISSING_INTTYPES_H         1  /* not provided by VS2012 and earlier */
# define MISSING_STDBOOL_H          1  /* not provided by VS2012 and earlier */
#else
#if defined(_MSC_VER) && _MSC_VER>=1800
/* VS2013 and above support C99 types */
# define HAVE_INT8_T                1
# define HAVE_UINT8_T               1
# define HAVE_INT16_T               1
# define HAVE_UINT16_T              1
# define HAVE_INT32_T               1
# define HAVE_UINT32_T              1
#endif
#endif


#define HAVE_ALLOCA        1


/* Functions */
#define HAVE_MEMMOVE
#define HAVE_SETVBUF
#define HAVE_CLOCK_SETTIME
#define HAVE_CLOCK_GETTIME
#define HAVE_SIGSUSPEND
#define HAVE_VSPRINTF
#define HAVE_VPRINTF
#define HAVE_STRERROR       1
#define HAVE_STRDUP         1
#define HAVE_STRSTR         1

/* Missing Functions */
#define NO_RENAME           1

#define HAVE_SNPRINTF
#define HAVE_VSNPRINTF

/* Types */
#define HAVE_INT8_T
#define HAVE_UINT8_T
#define HAVE_INT16_T
#define HAVE_UINT16_T
#define HAVE_UINT_T
#define HAVE_INT32_T
#define HAVE_UINT32_T
#define SIZEOF_TIME_T	4

/* Include files */
#define HAVE_STRING_H		1
#define HAVE_UNISTD_H
#define HAVE_UTIME_H
#define HAVE_LIMITS_H
#define HAVE_FCNTL_H
#define HAVE_STRCHR
#define HAVE_DIRENT_H
/*#define HAVE_SYS_MMAN_H*/
#define HAVE_SYS_SOCKET_H
#define HAVE_SYS_SELECT_H
#define HAVE_NETINET_IN_H
#define HAVE_ERRNO_H
#define HAVE_SYS_IOCTL_H	1

#define inline __inline__

/* the following macro is added to avoid modifying ntp_filegen.c */
#define SetLastError(a)     (errno=a)

/* VxWorks does not provide inet_ntop() */                             
/*#define ISC_PLATFORM_NEEDNTOP
#define ISC_PLATFORM_NEEDPTON*/
#ifdef NTP_VXWORKS_7
#define ISC_PLATFORM_NEEDPORTT
#endif
#define HAVE_SA_LEN_IN_STRUCT_SOCKADDR


/* use time adjustment function from bsp/usrTime.c */               
#define DECL_ADJTIME_0
#define HAVE_VXWORKS_ADJTIME

#ifdef IPCOM_USE_INET6
#define ISC_PLATFORM_HAVEIPV6
#define WANT_IPV6
#define ISC_PLATFORM_HAVEIN6PKTINFO
#define ISC_PLATFORM_HAVESCOPEID
#endif

#undef  HAVE_RTC

#define QSORT_USES_VOID_P

/* The following macros is for testing or debugging only */
#if 0
/* It will be defined in ipntp.mk */
#define NTP_DEBUG
#endif


#ifdef __cplusplus
}
#endif


#endif /* __ipntp_config */
