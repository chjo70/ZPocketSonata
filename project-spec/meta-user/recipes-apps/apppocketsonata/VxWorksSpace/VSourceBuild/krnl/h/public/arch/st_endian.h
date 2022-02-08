/* st_endian.h - ensure endianness is defined for host and target arches */

/* Copyright (c) 2010-2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

#if !defined(__ST_ENDIAN_H_)
#define __ST_ENDIAN_H_

#if !defined(ST_TARGET_LITTLE_ENDIAN) && !defined(ST_TARGET_BIG_ENDIAN)
#if defined(__VXWORKS__)
#  if (_BYTE_ORDER == _LITTLE_ENDIAN)
#    define ST_TARGET_LITTLE_ENDIAN
#  else
#    define ST_TARGET_BIG_ENDIAN
#  endif
#elif defined(__LITTLE_ENDIAN__)
#  define ST_TARGET_LITTLE_ENDIAN
#elif defined(__BIG_ENDIAN__)
#  define ST_TARGET_BIG_ENDIAN
#else
#    error Target endianness not defined
#endif
#endif  /* if !defined(ST_TARGET_LITTLE_ENDIAN) && !defined(ST_TARGET_BIG_ENDIAN) */

#endif  /* if !defined(__ST_ENDIAN_H_) */
