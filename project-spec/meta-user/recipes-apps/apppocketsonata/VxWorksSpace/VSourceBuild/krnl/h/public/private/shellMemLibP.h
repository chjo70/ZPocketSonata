/* shellMemLibP.h - private header for the shell memory library */

/*
 * Copyright (c) 2004, 2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this
 * software may be licensed only pursuant to the terms of an applicable Wind
 * River license agreement.
 */

/*
modification history
--------------------
01f,29apr10,pad  Moved extern C statement after include statements.
01e,23feb09,v_r  Addressed issues brought out by the LP64 review process.
01d,23sep04,bpn  Added definitions from shellMemLib.h.
01c,25aug04,bpn  Added shellMemStringIsAllocated() prototype.
01b,06apr04,bpn  Fixed scalability issue with memShow.o
01a,23feb04,bpn  Written.
*/

#ifndef __INCshellMemLibPh
#define __INCshellMemLibPh

/* Includes */

#include <lstLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Structures */

typedef struct shell_alloc
    {
    NODE	node;
    void *	pMem;	/* memory area address allocated */
    INT32	flags;	/* flags associated to that memory */
    } SHELL_ALLOC;

/* Function definition */

#if !defined(HOST) && defined(DEBUG)
extern void	shellMemShow (int type);
#endif

extern void	shellMemRegAllFree (INT32 flags, INT32 mask, LIST * pList);
extern void	shellMemAllRegFree (INT32 flags, INT32 mask,
				    void (* freeRtn) (void * ptr), 
				    LIST * pList);
extern BOOL	shellMemStringIsAllocated (SHELL_ID shellId,
					   const char * string);
/* WRS_XXX bpn - needed by usrLib.c */

extern char *	shellMemStringAdd (SHELL_ID shellId, const char * string);
extern STATUS	shellMemStringFree (SHELL_ID shellId, const char * string);
extern void	shellMemStringShow (SHELL_ID shellId);

#ifdef __cplusplus
}
#endif

#endif /* __INCshellMemLibPh */
