/* vxdbgLib.h - VxWorks debug library (VxDBG) header file */

/*
 * Copyright (c) 2013-2014 Wind River Systems, Inc.  
 *
 * The right to copy, distribute, modify or otherwise make use of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
09oct14,elp  Added S_vxdbgLib_NOT_ENABLED (US40741).
16jun14,jmp  Added S_vxdbgLib_HW_BP_SUPPORT_DISABLED to report error
             when hardware breakpoint support is configured-in but not
             enabled by the hardware (US39045).
21mar14,jmp  Added new VxDBG errnos to report better HW BP planting errors
             (US11680).
27feb14,dbt  Updated vxdbgAttach prototype
20may13,rlp  Created from vxdbgLibP.h
*/

#ifndef __INCvxdbgLibh
#define __INCvxdbgLibh

/* includes */

#include <vxWorks.h>
#include <vsbConfig.h>
#include <vwModNum.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* Errno values */

#define S_vxdbgLib_INVALID_PARAMS       (M_vxdbgLib | 1)  /* params invalid */
#define S_vxdbgLib_INVALID_MEM_ACCESS   (M_vxdbgLib | 2)  /* memory fault */
#define S_vxdbgLib_INVALID_CTX          (M_vxdbgLib | 5)  /* bad context */
#define S_vxdbgLib_INVALID_BP           (M_vxdbgLib | 8)  /* no such bp */
#define S_vxdbgLib_INVALID_EVENT_TYPE   (M_vxdbgLib | 9)  /* invalid event */
                                                          /* type */
#define S_vxdbgLib_NO_HW_REGS           (M_vxdbgLib | 14) /* no hardware regs */
                                                          /* defined for MIPS */
#define S_vxdbgLib_HOOK_ALREADY_EXISTS  (M_vxdbgLib | 15)
#define S_vxdbgLib_HW_REGS_FULL         (M_vxdbgLib | 16) /* hw breakpoint */
                                                          /* regs full */
#define S_vxdbgLib_INVALID_HW_BP        (M_vxdbgLib | 17) /* invalid hw bp */
                                                          /* type */
#define S_vxdbgLib_INVALID_BP_DELETE_CLASS (M_vxdbgLib | 18) /* invalid bp */
                                                          /* delete class */
#define	S_vxdbgLib_INVALID_ALIGNMENT	(M_vxdbgLib | 19) /* memory alignment */
							  /* error */
#define	S_vxdbgLib_NOT_INITIALIZED	(M_vxdbgLib | 20) /* VxDBG library is */
							  /* not initialized */
#define S_vxdbgLib_INVALID_CLIENT_ID    (M_vxdbgLib | 21) /* invalid client */
#define S_vxdbgLib_UNSUPPORTED_HW_BP_SIZE (M_vxdbgLib | 22) /* unsupported */
                                                          /* hw bp size */
#define S_vxdbgLib_UNSUPPORTED_HW_BP_ACCESS_TYPE (M_vxdbgLib | 23)
                                                          /* unsupported hw */
                                                          /* bp access type */
#define S_vxdbgLib_NO_HW_BP_SUPPORT (M_vxdbgLib | 24)     /* no hw bp support */
#define S_vxdbgLib_HW_BP_SUPPORT_DISABLED (M_vxdbgLib | 25)
                                                          /* hw bp disabled */
#define	S_vxdbgLib_NOT_ENABLED	(M_vxdbgLib | 26)

#ifndef _ASMLANGUAGE

/* typedefs */

/* VxDBG status values */

typedef enum vxdbg_status
    {
    VXDBG_OK				= 0,	/* VxDBG OK status */
    VXDBG_ERR_INVALID_PARAMS,			/* params invalid */
    VXDBG_ERR_HOOK_TBL_FULL,			/* Hook table full */
    VXDBG_ERR_ILLEGAL_OPERATION,		/* illegal request */
    VXDBG_ERR_TIMEOUT,				/* request timeout */
    VXDBG_ERR_CPU_NOT_SUSPENDED,		/* CPU not stopped */
    VXDBG_ERR_INVALID_REGSET,			/* invalid regSet */
    VXDBG_ERR_INIT,				/* init error */
    VXDBG_ERR_IPI_EMIT,				/* debug IPI emit error */
    VXDBG_ERROR				= -1	/* VxDBG ERROR */
    } VXDBG_STATUS;

/* Debug client identifier type */

typedef struct vxdbg_clnt *     VXDBG_CLNT_ID;

/* Debug context identifier type */

typedef ULONG                   VXDBG_CTX_ID;

/* Debug context type */

typedef enum vxdbg_ctx_type
    {
    VXDBG_CTX_NONE      = 0,
    VXDBG_CTX_TASK      = 1,                    /* task context */
    VXDBG_CTX_RTP       = 2                     /* rtp context */
    } VXDBG_CTX_TYPE;

/* Debug context */

typedef struct vxdbg_ctx
    {
    VXDBG_CTX_ID        ctxId;                  /* context identifier */
    VXDBG_CTX_TYPE      ctxType;                /* context type */
    } VXDBG_CTX;


/* function declarations */

VXDBG_STATUS vxdbgAttach (VXDBG_CLNT_ID	pClnt, VXDBG_CTX * pCtx,
			  int * pIsStopped);
VXDBG_STATUS vxdbgDetach (VXDBG_CLNT_ID	pClnt, VXDBG_CTX * pCtx);

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif	/* __INCvxdbgLibh */
