/* b_errno_t.h - base type size_t definition header */

/*
 * Copyright (C) 2016 Wind River Systems, Inc.
 * 
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
05apr16,rbo  Created
*/

#ifndef __INCb_errno_th
#define __INCb_errno_th

/* includes */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef _ERRNO_T
#define _ERRNO_T
typedef int errno_t;
#endif /* _ERRNO_T */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCb_errno_th */
