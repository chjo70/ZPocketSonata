/* compiler.h - handle compiler differences */

/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#ifndef INCccdiff_h
#define INCccdiff_h

#if defined(__GNUC__) || defined(__DCC__)
  #define cafe_likely(x)   __builtin_expect(!!(x), 1)
  #define cafe_unlikely(x) __builtin_expect(!!(x), 0)
#else
  #define cafe_likely(x)   (x)
  #define cafe_unlikely(x) (x)
#endif  /* if defined(__GNUC__) || defined(__DCC__) */

/* Try to get a reasonable __func__ substitute in place. */

#if defined(_MSC_VER)
  /* MSVC compilers before VC7 don't have __func__; later ones
   * call it __FUNCTION__. */
  #if _MSC_VER < 1300
    #define __func__ "????"
  #else
    #define __func__ __FUNCTION__
  #endif
#elif defined(__DCC__)
  #ifdef __func__
  #undef __func__
  #endif
  #define __func__ __FUNCTION__
#endif	/* _MSC_VER */

/* Try to get a reasonable inline substitute in place. */

#if defined(_MSC_VER)
  #define inline __inline
#elif defined(__DCC__)
  #define inline __inline__
#elif defined(__STRICT_ANSI__)
  #define inline __inline__
#endif

/* MSVC/ICC macros for importing/exporting symbols from DLLs. */

#if defined(cafe_EXPORTS)
  #if defined(__INTEL_COMPILER) || defined(_MSC_VER)
    #define CAFE_EXPORT __declspec(dllexport)
  #endif
#elif defined(cafe_IMPORTS)
  #if defined(__INTEL_COMPILER) || defined(_MSC_VER)
    #define CAFE_EXPORT __declspec(dllimport)
  #endif
#else
  #define CAFE_EXPORT
#endif

#endif	/* INCccdiff_h */
