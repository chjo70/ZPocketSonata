/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#ifndef INCcafe_stdbool_h
#define INCcafe_stdbool_h

#if !defined(_C99) || defined(_MSC_VER)
#ifndef bool
  typedef int _cafebool;
#endif
#ifndef false
  #define false (0)
#endif
#ifndef true
  #define true (1)
#endif
#ifndef bool
  #define bool _cafebool
#endif
#else
#include <stdbool.h>
#endif	/* _MSC_VER */
  
#endif /* INCcafe_stdbool_h */
