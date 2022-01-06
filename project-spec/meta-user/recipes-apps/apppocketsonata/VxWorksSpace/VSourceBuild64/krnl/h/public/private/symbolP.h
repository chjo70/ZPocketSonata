/* symbolP.h - private symbol structure header */

/*
 * Copyright (c) 2001,2004-2005,2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01g,29apr10,pad  Moved extern C statement after include statements.
01f,18jan10,rlp  Added UNDEF_SYM and COMMON_SYM for symbol management.
01e,24feb09,jmp  Added 64-bit support.
01d,07mar05,v_r  Cleanups + code conventions compliancy work.
		 Moved SYMBOL structure back into public header as needed by
		 published APIs.
01c,18sep04,jn   Move toward shared code on host and target
01b,01apr04,jn   Fix display of symbol types
01b,17feb04,pad  Extended symbol's group field from 16 bits to 32 bits (to
		 support shared libraries).
01a,29oct01,jn   created from HIDDEN part of symbol.h
*/

#ifndef __INCsymbolPh
#define __INCsymbolPh

#include <symbol.h>

#ifdef HOST
#include <dllLib.h>
#else /* HOST */
#include <sllLib.h>
#endif /* HOST */

#ifdef __cplusplus
extern "C" {
#endif

typedef UINT32 SYM_EXT_TYPE;	    /* internal symbol type (SYM_TYPE is still
				     * an unsigned char) */

#define SYM_EXT_NO_TYPE        0x0  /* no internal type information */
#define SYM_EXT_WEAK       0x10000  /* weak symbol */            
#define SYM_EXT_SEC        0x20000  /* section descriptor */            
#define SYM_EXT_UPDATE    0x100000  /* symbol to update (symtbl sync.) */

/*
 * pre-defined symbol references:
 * The symRef field will usually hold a MODULE_ID, to identify the module that
 * the symbol belongs to. Therefore we can use any addresses between (sizeof
 * (MODULE) - 1) and zero to indicate the source of symbols that are not
 * associated with any module.
 */

#define SYMREF_NONE	((SYM_REF)NULL)		/* no reference */
#define SYMREF_SHELL	((SYM_REF)~0x0L)	/* symbols created by shell */
#define SYMREF_KERNEL	((SYM_REF)~0x1L)	/* kernel symbols */
#define SYMREF_WTX	((SYM_REF)~0x2L)	/* symbols created by WTX */

#ifndef HOST
typedef struct
    {
    SL_NODE     commonSymNode;	/* singly-linked list node information */
    SYMBOL_ID	pSymbol;	/* pointer on the symbol structure in */
    				/* the system symbol table. */
    } COMMON_SYM;

typedef COMMON_SYM * COMMON_SYM_ID;
#endif	/* HOST */

/* Undefined symbols structure */

typedef struct
    {
#ifdef HOST
    DL_NODE     undefSymNode;   /* double-linked list node information */
#else	/* HOST */
    SL_NODE     undefSymNode;   /* singly-linked list node information */
#endif	/* HOST */
    char *      name;           /* name of the undefined symbol */
    } UNDEF_SYM;

typedef UNDEF_SYM * UNDEF_SYM_ID;

#ifdef __cplusplus
}
#endif

#endif /* __INCsymbolPh */

