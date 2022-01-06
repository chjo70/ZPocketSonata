/* dosFsVerP.h - dosFs2 vxWorks version header file */

/*
 * Copyright (c) 2001, 2003, 2010, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
04feb14,cww  Removed references to _WRS_VXWORKS_5_X (VXW7-1004)
29apr10,pad  Moved extern C statement after include statements.
21dec03,jkf  moving define of _WRS_DOSFS2_VXWORKS_AE to dosFsVerP.h
20sep01,jkf  written - SPR#69031, common code for both AE & 5.x.
*/

#ifndef __INCdosFsVerPh
#define __INCdosFsVerPh

/* This WRS private header file is subject to change by WRS without notice. */

/* include's */

#include <vxWorks.h>
#include <memPartLib.h>

/* XXX temporary workaround for Base6 */    
#define _WRS_DOSFS2_VXWORKS_AE

#ifdef _WRS_DOSFS2_VXWORKS_AE

/* XXX temporary workaround for Base6 */    
/* #   include "pdLib.h" */

#   include "private/handleLibP.h"	/* for VxWorks AE, use HANDLE */

#   ifndef KHEAP_REALLOC
#       define KHEAP_REALLOC(pBuf,newsize) \
	       memPartRealloc(memPartIdKernel,pBuf,newsize)
#   endif /* KHEAP_REALLOC */

#else /* _WRS_DOSFS2_VXWORKS_AE */

#   include "classLib.h"		/* for VxWorks 5.x, use OBJ_CORE */
#   include "objLib.h"
#   include "private/objLibP.h"

#endif /* DOSFS2_VXWORKS_AE */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCdosFsVerPh */
