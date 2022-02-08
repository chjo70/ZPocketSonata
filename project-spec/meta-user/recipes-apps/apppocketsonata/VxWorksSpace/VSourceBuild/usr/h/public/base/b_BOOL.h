/* b_BOOL.h - base type BOOL definition header */

/*
 * Copyright (c) 2006-2007 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
*/

/*
modification history
--------------------
01b,08aug07,pad  Added POSIX-conforming _Vx_BOOL type as equivalent of BOOL
                 for POSIX applications (defect 100623).
01a,16feb06,pes  Created.
*/

#ifndef __INCb_BOOLh
#define __INCb_BOOLh

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)

#ifndef _DEFINED_BOOL
#define _DEFINED_BOOL
typedef int BOOL;
#endif /* _DEFINED_BOOL */

#else /* _POSIX_xxx_SOURCE */

#ifndef _DEFINED__Vx_BOOL
#define _DEFINED__Vx_BOOL
typedef int _Vx_BOOL;
#endif /* _DEFINED__Vx_BOOL */

#endif /* _POSIX_xxx_SOURCE */

#ifdef __cplusplus
}
#endif

#endif /* __INCb_BOOLh */


