/* symLibP.h - private symbol library header file */

/*
 * Copyright (c) 2001,2003-2005, 2009-2010,2013,2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01dec14,v_r  Added _func_symTblCreate prototype.
24jun13,elp  Replaced mutex with RW semahore, added symEachCall()
		 (CQ:WIND00409243).
29apr10,pad  Moved extern C statement after include statements.
22jun09,jmp  Moved symLib function pointers from funcBindP.h.
23feb09,jmp  64-bit support: Used new symbol types.
		 Moved non public APIs from symLib.h.
07mar05,v_r  Fixed SPR #98274 (loader backward compatibility errno review).
		 Cleanups + code conventions compliancy work.
24jan05,aeg  added symTblSymSetRemove prototype (SPR #106381).
06oct04,jn   Clean up comments
05apr04,jn   Clean up - remove unused declarations and development-related
                 comments
03apr03,to   replaced OBJ_CORE with HANDLE in SYMTAB (de-classify).
15oct01,jn   created.
*/

#ifndef __INCsymLibPh
#define __INCsymLibPh

#include <hashLib.h>
#include <symLib.h>

#ifdef HOST
#include <vmutex.h>
#else
#include <private/semLibP.h>
#include <private/handleLibP.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#ifdef HOST
/* size of hash table given number of elements in hash table log 2 */
#ifndef HASH_TBL_SIZE
#define HASH_TBL_SIZE(sizeLog2)                                         \
        (((1 << sizeLog2) * sizeof (SL_LIST)) + sizeof (HASH_TBL))
#endif /* ndef HASH_TBL_SIZE */
#endif /* HOST */

/* allow write access to symbol table through symEachCall() */

#define SYM_EACH_CALL_WRITE 0x1	

/* Maximum number of concurrent symbol table reader */

#define MAX_SYM_READERS 10

/* typedefs */

typedef BOOL (*SYM_EACH_RTN_FUNCPTR)	(char * name, SYM_VALUE val,
					 SYM_TYPE type, _Vx_usr_arg_t arg,
					 SYM_GROUP group);

/* structure definitions */

typedef struct symtab	/* SYMTAB - symbol table */
    {
#ifdef HOST
    OBJ_CORE	handle;		/* handle management */
#else
    HANDLE	handle;		/* object maintanance */
#endif /* HOST */
    HASH_ID	nameHashId;	/* hash table for names */
    PART_ID	symPartId;	/* memory partition id for symbols */
    BOOL	sameNameOk;	/* symbol table name clash policy */
    ULONG	nsymbols;	/* current number of symbols in table */
    SEMAPHORE   symRWSem;       /* symbol table mutual exclusion sem */
#ifdef _WRS_KERNEL
    SEM_RW_EXT	symRWSemExt;
    SEM_RW_LIST_ENTRY symRWSemEntryPtr[MAX_SYM_READERS];
#endif /* _WRS_KERNEL */
    } SYMTAB;

/* Hooks for symbol management library */

extern SYMBOL_ID (* _func_symEach)
    (
    SYMTAB_ID	symTblId,	/* ID of symbol table to look in */
    BOOL	(*routine)	/* func to call for each tbl entry	*/
		    (
		    char * name,	/* symbol/entry name		*/
		    SYM_VALUE val,	/* symbol/entry value		*/
		    SYM_TYPE type,	/* symbol/entry type		*/
		    _Vx_usr_arg_t arg,	/* arbitrary user-supplied arg	*/
		    SYM_GROUP group	/* symbol/entry group number	*/
		    ),
    _Vx_usr_arg_t routineArg	/* arbitrary user-supplied arg */
    );

extern SYMBOL_ID (* _func_symEachCall)
    (
    SYMTAB_ID	symTblId,	/* ID of symbol table to look in */
    BOOL	(*routine)	/* func to call for each tbl entry	*/
		    (
		    char * name,	/* symbol/entry name		*/
		    SYM_VALUE val,	/* symbol/entry value		*/
		    SYM_TYPE type,	/* symbol/entry type		*/
		    _Vx_usr_arg_t arg,	/* arbitrary user-supplied arg	*/
		    SYM_GROUP group	/* symbol/entry group number	*/
		    ),
    _Vx_usr_arg_t routineArg,	/* arbitrary user-supplied arg */
    int		flags
    );

extern STATUS (* _func_symFind)
    (
    SYMTAB_ID		symTblId,	/* ID of symbol table to look in */
    SYMBOL_DESC *	pSymDesc	/* pointer to symbol descriptor */
    ) ;

extern STATUS (* _func_symFindSymbol)
    (
    SYMTAB_ID   symTblId,       /* symbol table ID */
    char *      name,           /* name to search for */
    SYM_VALUE	value,		/* value of symbol to search for */
    SYM_TYPE    type,           /* symbol type */
    SYM_TYPE    mask,           /* type bits that matter */
    SYMBOL_ID * pSymbolId       /* where to return id of matching symbol */
    );

extern STATUS (* _func_symNameGet)
    (
    SYMBOL_ID  symbolId,	/* symbol table ID */
    char **    pName		/* pointer to symbol name */
    );

extern STATUS (* _func_symValueGet)
    (
    SYMBOL_ID   symbolId,       /* symbol table ID */
    SYM_VALUE * pValue          /* pointer to symbol value */
    );

extern STATUS (* _func_symTypeGet)
    (
    SYMBOL_ID  symbolId,	/* symbol table ID */
    SYM_TYPE * pType		/* pointer to symbol type */
    );

extern SYMBOL_ID (* _func_symRegister)
    (
    SYMTAB_ID	symTblId,	/* Symbol table to add symbol to      */
    char *	name,		/* Pointer to symbol name string      */
    SYM_VALUE	value,		/* Symbol's address 		      */
    SYM_TYPE    type,           /* Symbol's type  */
    SYM_GROUP	group,          /* symbol group */
    SYM_REF 	symRef,		/* module id, SYMREF_SHELL, or SYMREF_NONE */ 
    BOOL        callSyncRtn     /* Try to call the synchronization rtn? */
    );

extern STATUS (* _func_symTblShutdown)
    (
    SYMTAB_ID symTblId          /* ID of symbol table to delete */
    );

extern SYMTAB_ID (* _func_symTblCreate)
    (
    int     hashSizeLog2,       /* size of hash table as a power of 2 */
    BOOL    sameNameOk,         /* allow 2 symbols of same name & type */
    PART_ID symPartId           /* memory part ID for symbol allocation */
    );

/* function declarations */

extern STATUS	symByCNameFind		(SYMTAB_ID symTblId, char * name,
					 SYM_VALUE * pValue, SYM_TYPE * pType);
#ifdef HOST
extern SYMBOL * symEachSym		(SYMTAB_ID symTblId,
					 SYM_EACH_RTN_FUNCPTR routine,
					 _Vx_usr_arg_t routineArg);
#endif
extern STATUS	symFindSymbol		(SYMTAB_ID symTblId, char * name,
					 SYM_VALUE value, SYM_TYPE type,
					 SYM_TYPE mask, SYMBOL_ID * pSymbolId);
extern STATUS	symNameGet		(SYMBOL_ID symbolId, char ** pName);
extern SYMBOL_ID symRegister		(SYMTAB_ID symTblId, char * name,
					 SYM_VALUE value, SYM_TYPE type,
					 SYM_GROUP group, SYM_REF symRef, 
					 BOOL callSyncRtn);
extern STATUS	symTblShutdown		(SYMTAB_ID symTblId );
extern STATUS	symTblSymSetRemove	(SYMTAB_ID symTblId,
					 SYM_REF reference, SYM_TYPE type,
					 SYM_TYPE typeMask);
extern STATUS	symTypeGet		(SYMBOL_ID symbolId, SYM_TYPE * pType);
extern STATUS	symValueGet		(SYMBOL_ID symbolId,
					 SYM_VALUE * pValue);
extern STATUS	symFree			(SYMTAB_ID symTblId, SYMBOL * pSymbol);
extern STATUS	symTblAdd		(SYMTAB_ID symTblId, SYMBOL * pSymbol);
extern STATUS	symTblRemove		(SYMTAB_ID symTblId, SYMBOL * pSymbol);
extern SYMBOL_ID symEachCall 		(SYMTAB_ID symTblId,
					 SYM_EACH_RTN_FUNCPTR routine,
					 _Vx_usr_arg_t routineArg, int flags);


#ifdef __cplusplus
}
#endif

#endif /* __INCsymLibPh */
