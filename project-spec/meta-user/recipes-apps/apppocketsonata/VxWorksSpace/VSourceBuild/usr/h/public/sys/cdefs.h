/* cdefs.h - Header file containing generic tool configuration macros */

/*
 * Copyright (c) 2006, 2012, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
11dec14,brk  added __unused  for open source compatibility
26jan12,mcm  Fix for WIND00328927 - protecting the definition of
                 _Restrict.
08mar06,mcm  Fixing coding standard violations.
03mar06,mcm  Created

DESCRIPTION

This header file is meant to provide a portable definitions of toolchain
configuration macros.

1. The _Restrict macro - source files that intend to use the 'restrict' 
   keyword should use the _Restrict macro so that the usage is portable 
   across various compilers.

*/

#ifndef __INCcdefsh
#define __INCcdefsh

#if !defined(_Restrict)
#if (__STDC_VERSION__ >= 199901L)
#    if defined(__cplusplus)
#        define _Restrict
#    else
#        define _Restrict restrict
#    endif
#else
#    define _Restrict
#endif
#endif

#ifndef __unused
#ifdef __GCC__
#define __unused        __attribute__((__unused__))
#else
#define __unused
#endif /* __GCC__ */
#endif /* __unused */

#endif /* __INCcdefsh */
