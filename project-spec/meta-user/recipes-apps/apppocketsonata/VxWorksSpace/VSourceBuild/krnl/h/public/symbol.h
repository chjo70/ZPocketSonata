/* symbol.h - symbol structure header */

/*
 * Copyright (c) 1989-1002,1996-1997,2001,2004-2006, 2009-2010, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
09mar15,vhe  Added offset for PPC64v2 symbols 
29apr10,pad  Moved extern C statement after include statements.
24feb09,jmp  64-bit support: Defined SYM_VALUE, SYM_GROUP, SYM_REF types.
20jan06,v_r  Fixed SPR#110049 (symbol group changed from UINT16 to
             UINT32).
07mar05,v_r  Cleanups + code conventions compliancy work.
             Moved SYMBOL struct here as it's needed by published APIs.
18sep04,jn   Apply code review changes
01apr04,jn   Change values of symbol type macros.  Symbol types 
             should now only be examined using the SYM_IS_...
    	     family of macros defined here.
29oct01,jn   create symbolP.h
25jul97,cdp  added SYM_THUMB.
26mai96,dbt  added support for PowerPC SDA-related symbols.
22sep92,rrr  added support for c++
14jul92,jmm  added define of SYM_MASK_EXACT for symTblRemove
04jul92,jcf  cleaned up.
26may92,rrr  the tree shuffle
30apr92,jmm  Added support for group numbers
04oct91,rrr  passed through the ansification filter
    	     -fixed #else and #endif
    	     -changed TINY and UTINY to INT8 and UINT8
    	     -changed copyright notice
19may91,gae  changed UINT8 to unsigned char.
05oct90,shl  added copyright notice.
10dec89,jcf  written by pulling out of symLib.h.
*/

#ifndef __INCsymbolh
#define __INCsymbolh

#include <sllLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* symbol types */

typedef char *		SYM_VALUE;
typedef unsigned char	SYM_TYPE;
typedef UINT16		SYM_GROUP;
typedef ULONG		SYM_REF;

typedef struct symbol           /* SYMBOL - entry in symbol table */
    {
    SL_NODE     nameHNode;      /* hash node (must come first) */
    char *	name;		/* pointer to symbol name */
    SYM_VALUE	value;		/* symbol value */
    SYM_REF	symRef;		/* Id of module, or predefined SYMREF. */
    SYM_GROUP	group;          /* symbol group */
    SYM_TYPE    type;           /* symbol type */
    unsigned char other;        /* st_other field */
    } SYMBOL;

typedef SYMBOL * SYMBOL_ID;

/* 
 * NOTE: Do not use these symbol type macro definitions directly.  Instead 
 * use the SYM_IS_<TYPE> masks, defined below, to test whether a symbol 
 * is global, absolute, etc.  This will prevent backwards and/or forwards
 * compatibility issues in the case that it becomes necessary to change 
 * the values of these macros or method of storing the symbol type. 
 */

#define SYM_UNDF        0x0     /* undefined (lowest 8 bits only) */  
#define SYM_GLOBAL      0x1     /* global (external) */
#define SYM_ABS         0x2     /* absolute */
#define SYM_TEXT        0x4     /* text */
#define SYM_DATA        0x8     /* data */             
#define SYM_BSS        0x10     /* bss */              
#define SYM_COMM       0x20     /* common symbol */    
#define SYM_LOCAL      0x40     /* local */            
#define SYM_THUMB      0x80	/* Thumb function */

#define SYM_IS_UNDF(symType)   (!(symType))
#define SYM_IS_GLOBAL(symType) ((symType) & SYM_GLOBAL) 
#define SYM_IS_LOCAL(symType)  ((symType) & SYM_LOCAL) 
#define SYM_IS_TEXT(symType)   ((symType) & SYM_TEXT) 
#define SYM_IS_DATA(symType)   ((symType) & SYM_DATA) 
#define SYM_IS_BSS(symType)    ((symType) & SYM_BSS) 
#define SYM_IS_ABS(symType)    ((symType) & SYM_ABS) 
#define SYM_IS_COMMON(symType) ((symType) & SYM_COMM) 

/* symbol masks */ 

#define SYM_MASK_ALL	0xff            /* all bits of symbol type valid */
#define SYM_MASK_NONE	0x00		/* no bits of symbol type valid */
#define SYM_MASK_EXACT	0x1ff		/* match symbol pointer exactly */

#define SYM_MASK_ANY_TYPE    SYM_MASK_NONE  /* ignore type in searches */
#define SYM_MASK_EXACT_TYPE  SYM_MASK_ALL   /* match type exactly in searches */

#ifdef __cplusplus
}
#endif

#endif /* __INCsymbolh */
