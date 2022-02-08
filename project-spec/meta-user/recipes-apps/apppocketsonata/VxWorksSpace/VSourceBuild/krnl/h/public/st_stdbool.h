/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#if !defined(__st_stdbool_h)
#define __st_stdbool_h

#if !defined(__STDC__) || !defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L \
    || defined(_MSC_VER)

#  if !defined(bool)
    typedef int bool;
#  endif
#  if !defined(false)
#    define false (0)
#  endif
#  if !defined(true)
#    define true (1)
#  endif
#else
#  include <stdbool.h>
#endif	/* _MSC_VER */
  
#endif /* if !defined(__st_stdbool_h) */
