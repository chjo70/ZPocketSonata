/* vxInlineArch.h - PPC inline macro configuration */

/* 
 * Copyright (c) 2007-2008, 2010, 2012 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01f,15nov12,wyt  remove _WRS_INLINE_QorIQlwsync
01e,01apr10,wap  Add dcbzl
01d,21dec08,wap  Add Freescale QorIQ queue manager primitives
01c,07mar08,to   added _WRS_INLINE_vxAtomicGet
01b,14dec07,gls  added _WRS_INLINE_vxCas
01a,19jun07,zl   created
*/

#ifndef __INCvxInlineArchh
#define __INCvxInlineArchh

#ifdef __cplusplus
extern "C" {
#endif

/*
 * This file is included from <vxInline.h>. It may define _WRS_INLINE_xxx 
 * build configuration macros in order to enable architecture specific
 * inlined implementation of a macro definition.
 */

#define _WRS_INLINE_ffsLsb
#define _WRS_INLINE_ffsMsb
#define _WRS_INLINE_vxAtomicGet
#define _WRS_INLINE_vxCas

#define _WRS_INLINE_QorIQdcbi
#define _WRS_INLINE_QorIQdcbt
#define _WRS_INLINE_QorIQdcbf
#define _WRS_INLINE_QorIQdcbzl

#ifdef __cplusplus
}
#endif

#endif /* __INCvxInlineArchh */
