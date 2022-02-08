/* b_rsize_t.h - base type size_t definition header */

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

#ifndef __INCb_rsize_th
#define __INCb_rsize_th

/* includes */

#include <vsbConfig.h> 

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifndef _RSIZE_T
#define _RSIZE_T
#ifdef _WRS_CONFIG_LP64
typedef unsigned long rsize_t;
#else
typedef unsigned int rsize_t;
#endif
#endif /* _RSIZE_T */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCb_rsize_th */
