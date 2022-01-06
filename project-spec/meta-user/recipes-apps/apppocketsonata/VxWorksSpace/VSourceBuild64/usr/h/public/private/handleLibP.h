/* handleLibP.h - handle management library header */

/*
 * Copyright (c) 1998-2003, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01j,16aug10,cww  Use dynamically generated offsets in offset macros
01i,28apr10,pad  Moved extern C statement after include statements.
01h,20jan10,gls  added non-locking object validation for SMP
01g,25sep09,zl   change showType of handleShow() to _Vx_usr_arg_t
01f,13may09,jmp  Made type argument of handleShow() 64-bit compatible.
01e,17feb09,zl   updated for LP64 support
01d,02mar04,dcc  modified attributes to be 16 bits wide.
01c,02nov03,dcc  modified HANDLE to comply with ANSI standards.
01b,02jul03,to   added offsets into HANDLE.
01a,23jun03,dcc  ported from AE1.1
*/

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef __INChandleLibPh
#define __INChandleLibPh

#include <vxWorks.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HANDLE_SAFECNT_INVALID   0xffffffff
#define HANDLE_SAFECNT_INC       0x1

#ifndef _ASMLANGUAGE

/* typedefs */

enum handleContextType
    {
    handleContextTypeNone   = 0,
    handleContextTypeUser,
    handleContextTypeOms,
    handleContextTypeCOM,
    handleContextTypeI2O
    };

typedef struct
    {
    ULONG     magic;	      /* 0x00/0x00: magic. Used in HANDLE_VERIFY() */
    UINT32    safeCnt;	      /* 0x04/0x08: safe count */
    UINT16    attributes;     /* 0x08/0x0c: attribute bit set */
    INT8      type;           /* 0x0a/0x0e: enum windObjClassType */
    UINT8     contextType;    /* 0x0b/0x0f: enum handleContextType */
    void *    context;        /* 0x0c/0x10: WRS defined context */
    } HANDLE;

typedef HANDLE * HANDLE_ID;		/* handle id */

typedef STATUS (*HANDLE_SHOW_FUNC) (HANDLE_ID handleId, _Vx_usr_arg_t arg);

/* function declarations */

extern STATUS   handleContextGet        (HANDLE_ID handleId, void **pContext,
					 enum handleContextType *pContextType);
extern void	handleContextGetBase	(HANDLE_ID handleId, void **pContext,
					 enum handleContextType *pContextType);
extern STATUS   handleContextSet        (HANDLE_ID handleId, void *context,
					 enum handleContextType contextType);
extern STATUS	handleInit	 	(HANDLE_ID handleId, enum handleType);
extern STATUS	handleVerify	 	(HANDLE_ID handleId, enum handleType);
extern STATUS	handleTerminate  	(HANDLE_ID handleId);
extern STATUS	handleShow	 	(HANDLE_ID handleId, 
					 _Vx_usr_arg_t arg);
extern STATUS	handleShowConnect	(enum handleType,
					 HANDLE_SHOW_FUNC showRtn);
extern enum handleType handleTypeGet	(HANDLE_ID handleId);

/* macro declarations */

#define HANDLE_VERIFY(handle,handleType)				\
    (									\
        (								\
	    (((HANDLE_ID) (handle))->magic == (ULONG)(handle))		\
	&&								\
	    (((HANDLE_ID) (handle))->type == (INT8)(handleType))	\
	)								\
    ? 									\
	OK								\
    :									\
	ERROR								\
    )

#ifdef __cplusplus
}
#endif

#else /* _ASMLANGUAGE */

/*
 * offsets into HANDLE - these must be in an ASM section due to a circular
 * dependency when compiling offsets.c
 *
 * WARNING: the old offset macros are provided temporarily only for a
 * transitionary phase.  They will be removed once existing references are
 * updated to use the dynamically generated offsets.
 */

#include <private/offsetMacrosP.h>

# define HANDLE_MAGIC	HANDLE_magic_OFFSET
# define HANDLE_SAFECNT	HANDLE_safeCnt_OFFSET
# define HANDLE_ATTRIB	HANDLE_attributes_OFFSET
# define HANDLE_TYPE	HANDLE_type_OFFSET
# define HANDLE_SIZE    HANDLE_objSize_OFFSET

#endif /* _ASMLANGUAGE */

#endif /* __INChandleLibPh */
