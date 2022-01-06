/*
 * Copyright (c) 2011-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#if !defined(__st_inttypes_h)
#define __st_inttypes_h

#if defined(_MSC_VER)

#  define PRIx16  "I16x"
#  define PRIx32  "I32x"
#  define PRIx64  "I64x"

#  define PRIxPTR "Ix"

#elif defined(__VXWORKS__) && defined(_WRS_KERNEL)
#  include <vxWorks.h>  /* for VXWORKS_[MAJOR,MINOR] */
#  include <vsbConfig.h>  /* for _WRS_CONFIG_* */
#  ifndef _WRS_VXWORKS_MAINT
#    define _WRS_VXWORKS_MAINT 0
#  endif
#  if (_WRS_VXWORKS_MAJOR < 6) \
    || ((_WRS_VXWORKS_MAJOR == 6) && (_WRS_VXWORKS_MINOR < 9))
typedef unsigned long uintptr_t;
#endif
#  define PRIx16  "x"
#  define PRIxPTR "x"
#  define PRIx32  "x"
#  if defined(_WRS_CONFIG_LP64)
#    define PRIx64  "lx"
#  else
#    define PRIx64  "llx"
#endif

#else
#  include <inttypes.h>
#endif	/* _MSC_VER */
  
#endif /* if !defined(__st_inttypes_h) */
