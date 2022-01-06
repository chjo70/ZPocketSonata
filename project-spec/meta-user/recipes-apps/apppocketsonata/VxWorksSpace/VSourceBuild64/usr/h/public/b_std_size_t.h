/* b_std_size_t.h - base type size_t definition header */

/*
 * Copyright (c) 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
*/

/*
modification history
--------------------
13oct15,lau  Created.
*/


#ifndef __INCb_std_size_th
#define __INCb_std_size_th

_C_STD_BEGIN

 #if !defined(_SIZE_T) && !defined(_SIZET) && !defined(_SIZE_T_DEFINED) \
        && !defined(_BSD_SIZE_T_DEFINED_)
  #if !defined(_C_IN_NS)
    /* Type is going into the global namespace, so define these to prevent any other header (base/b_size_t.h) from defining the same type. */
    #define _SIZE_T
    #define _SIZET
    #define _BSD_SIZE_T_DEFINED_
    #define _SIZE_T_DEFINED
  #endif /* _C_IN_NS */
  #define _STD_USING_SIZE_T
  typedef _Sizet size_t;
 #else
  #if defined(_C_IN_NS)
   typedef ::size_t size_t;
  #endif /* _STD_USING */
 #endif /* !defined(_SIZE_T) etc. */

_C_STD_END

#endif /* __INCb_std_size_th */
