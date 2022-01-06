/*
 * Copyright (c) 2010-2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/* Cafe/OS Integer Types. */

#ifndef INCinttypes_h
#define INCinttypes_h

#if defined(__MINGW32__)
  #include <inttypes.h>
#elif defined(_MSC_VER)
  /* Turn off message: warning C4142: benign redefinition of type */
  #pragma warning (disable: 4142)

  typedef unsigned char uint8_t;
  typedef unsigned short uint16_t;
  typedef unsigned long uint32_t;
  typedef unsigned __int64 uint64_t;
  typedef char int8_t;
  typedef short int16_t;
  typedef long int32_t;
  typedef __int64 int64_t;
  #define PRIoPTR "Io"
  #define PRIuPTR "Iu"
  #define PRIxPTR "Ix"
  #define PRIXPTR "IX"
  #define PRIx64 "I64x"
  #define PRIX64 "I64X"
#elif defined(_WRS_KERNEL)
  #include <vsbConfig.h>  /* for _WRS_CONFIG_* */
  /* VxWorks userland (i.e., !_WRS_KERNEL) actually has an inttypes.h */
  #include <types/vxTypesBase.h>
  #ifdef _C99
    typedef long long intmax_t;
  #else
     typedef unsigned long long intmax_t;
  #endif /* _C99 */
  #define PRIoff_t "d"
  #define PRIsize_t "u"
  #define PRIssize_t "d"
  #define PRIuPTR "lu"
  #if defined(_WRS_CONFIG_LP64)
    #define PRIx64 "lx"
  #else
    #define PRIx64 "llx"
  #endif
#else
  /* We always have 64-bit file I/O on Unix/Linux. */
  #include <inttypes.h>
  #define PRIoff_t "lld"
  #define PRIsize_t "zu"
  #define PRIssize_t "zd"
#endif	/* __MINGW32__ */

#if defined(__MINGW32__) || defined(_MSC_VER)
  #if defined(_WIN64)
    typedef __int64 ssize_t;
    #define PRIsize_t "llu"
    #define PRIssize_t "lld"
  #elif defined(_WIN32)
    typedef long ssize_t;
    #define PRIsize_t "u"
    #define PRIssize_t "d"
  #endif  /* _WIN64 */
  /* We always have 64-bit file I/O on Windows. */
  #define PRIoff_t PRId64

  #ifndef PRId64
    #define PRId64 "I64d"
  #endif
#endif  /* defined(__MINGW32__) || defined(_MSC_VER) */

#ifndef PRIsize_t
#error "no printf format specifier defined for size_t"
#endif

#ifndef PRIssize_t
#error "no printf format specifier defined for ssize_t"
#endif

#endif	/* INCinttypes_h */
