/* symLib.h - symbol table subroutine library header */

/*
 * Copyright (c) 1983-1986, 1988-1992, 1996-1998, 2001, 2003-2006,
 *               2009-2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
04p,27apr10,jmp  Updated documentation following review.
04o,23mar10,jmp  Added nameLen field to SYMBOL_DESC, and updated name field
		 description (CQ:WIND00203351).
04p,01apr10,pad  Added C++ inline wrapper for symEach(). Moved 'extern "C" {'
                 statement after last '#include' statement.
04o,19jan10,pad  Removed usage of _WRS_KEEP_USING_FUNCPTR.
04n,16apr09,jmp  Fixed typo in _WRS_KEEP_USING_FUNCPTR test.
04m,23feb09,jmp  64-bit support:
		 - Added SYMBOL_DESC and SYM_FIND_MASK types.
		 - Added S_symLib_INVALID_ARGS errno for symFind().
		 Moved non public APIs to symLibP.h.
04l,22nov06,v_r  Mark obsoleted routine as such for req CQ:WIND00068611
                 implementation.
04k,14apr05,v_r  Marked obsolete errnos.
04j,03mar05,v_r  Fixed SPR #98274 (loader backward compatibility errno review).
		 Cleanups + code conventions compliancy work.
04i,06apr04,jn   Clean up - remove unused declarations and development-related
                 comments (merge work done in AE loader here)
04h,03apr03,to   added status codes.
04g,15oct01,jn   move private funcs into symLibP.h
04f,04sep98,cdp  make Thumb-specific changes dependent on ARM_THUMB.
04e,02dec97,cdp  added thumbSymTblAdd().
04d,30oct96,elp  Added syncSymAddRtn, symSymRemoveRtn function pointers and
		 symSAdd().
04c,22sep92,rrr  added support for c++
04b,28jul92,jmm  added prototype for symAdd
04a,04jul92,jcf  cleaned up.
03t,22jun92,jmm  removed symFooWithGroup, added parameter to routines instead
03s,26may92,rrr  the tree shuffle
03r,15may92,jmm  Changed "symFooGroup" to "symFooWithGroup"
03i,30apr92,jmm  Added support for goup numbers
03h,02jan92,gae  used UINT's for value in symFindByValue{AndType}.
03g,13dec91,gae  made symFindByCName() consistent with other symFind* routines.
03f,26nov91,llk  added symName().
03e,04oct91,rrr  passed through the ansification filter
		  -changed copyright notice
03d,05oct90,dnw  deleted private functions.
03c,05oct90,shl  added ANSI function prototypes.
                 added copyright notice.
03b,26jun90,jcf  removed symbol table id error.
03a,22nov89,jcf  changed for hasing/multiple access implementation
02d,30may88,dnw  changed to v4 names.
02c,24dec86,gae  changed stsLib.h to vwModNum.h.
02b,05jun86,dnw  changed SYMTAB structure to have ptr to symbol array
		   instead of imbedded array.
02a,11oct85,dnw  changed SYMTAB structure to have maxSymbols instead of
		   string table pool pointer.
		 deleted obsolete definition of MAX_SYM_LENGTH.
01g,11jun85,rdc  added maxSymLength and free to the SYMTAB structure.
		 These were necessary
		 for variable symbol length.
01f,13aug84,ecs  deleted status code S_sysLib_EMPTY_SYMBOL_TABLE.
01e,08aug84,ecs  added include of stsLib.h, symLib status codes.
01d,27jun84,ecs  changed length of name in SYMBOL to allow room for EOS.
01c,15jun84,dnw  moved typedefs for SYMBOL and SYMTAB here from symLib.c.
		 added typedef for SYMTAB_ID.
01b,27jan84,ecs  added inclusion test.
01a,03aug83,dnw  written
*/

#ifndef __INCsymLibh
#define __INCsymLibh

#ifdef HOST
#include <tgtmem.h>
#endif

#include <symbol.h>

#ifdef __cplusplus
extern "C" {
#endif

/* status codes */

#define S_symLib_SYMBOL_NOT_FOUND	(M_symLib | 1)
#define S_symLib_NAME_CLASH		(M_symLib | 2)
#define S_symLib_TABLE_NOT_EMPTY	(M_symLib | 3)
#define S_symLib_SYMBOL_STILL_IN_TABLE	(M_symLib | 4) /* obsoleted */
#define S_symLib_INVALID_SYMBOL_NAME	(M_symLib | 5)
#define S_symLib_INVALID_SYMTAB_ID	(M_symLib | 12)
#define S_symLib_INVALID_SYM_ID_PTR     (M_symLib | 13)
#define S_symLib_INVALID_ARGS		(M_symLib | 14)

/* Type definitions */

typedef struct symtab * SYMTAB_ID;

/* Supported search type for symFind() routine (Can be OR'ed) */

typedef enum			/* symFind() mask values (Can be OR'ed) */
    {
    SYM_FIND_BY_NAME	= 0x1,		/* 0x1: Search symbol by name */
    SYM_FIND_BY_VALUE	= 0x2,		/* 0x2: Search symbol by value */
    SYM_FIND_BY_TYPE	= 0x4		/* 0x4: Search symbol by type */
    } SYM_FIND_MASK;

typedef struct symbol_desc   /* SYMBOL_DESC - symbol descriptor for symFind() */
    {
    SYM_FIND_MASK   mask;	/* In: Search filter mask */
    char *          name;     /* In - If SYM_FIND_BY_NAME not specified:      */
                              /*      Pointer to buffer to return symbol name.*/
                              /*      NULL to let symFind() allocate buffer   */
                              /* Out: Pointer to buffer that holds symbol     */
                              /*      name. This pointer has to be freed by   */
                              /*      the caller if a NULL pointer value      */
                              /*      was provided (buffer allocated by       */
                              /*      symFind() itself)                       */
    size_t          nameLen;  /* In:  Length of <name> buffer if provided     */
                              /* Out: Length of entire symbol name with EOS   */
    SYM_VALUE       value;	/* In: Value of symbol to find */
    				/* Out: Exact symbol value */
    SYM_TYPE        type;	/* In: Type of symbol to find */
    				/* Out: Exact symbol type */
    SYM_TYPE        typeMask; /* In:  Bits in <type> to pay attention to      */
    } SYMBOL_DESC; 

/* default group number */

extern SYM_GROUP symGroupDefault;

/* function pointers for symbol table synchronization */

extern void (*syncSymAddRtn)	(SYMBOL_ID symbolId, SYMTAB_ID symTblId);
extern void (*syncSymRemoveRtn)	(SYMBOL_ID symbolId);

/* function declarations */

extern STATUS	symLibInit	(void);
extern STATUS	symAdd		(SYMTAB_ID symTblId, char * name,
				 SYM_VALUE value, SYM_TYPE type,
				 SYM_GROUP group);
extern STATUS	symRemove	(SYMTAB_ID symTblId, char * name,
				 SYM_TYPE type);
extern SYMTAB_ID symTblCreate	(int hashSizeLog2, BOOL sameNameOk, 
				 PART_ID symPartId);
extern STATUS	symTblDelete	(SYMTAB_ID symTblId);

extern SYMBOL_ID symEach	(SYMTAB_ID symTblId,
				 BOOL (*routine) (char * name, SYM_VALUE val,
				 		  SYM_TYPE type,
						  _Vx_usr_arg_t arg,
						  SYM_GROUP group),
				 _Vx_usr_arg_t routineArg);
extern void	symShowInit	(void);
extern STATUS	symShow		(SYMTAB_ID symTblId, char * substr);
extern STATUS	symFind		(SYMTAB_ID symTblId, SYMBOL_DESC * pSymbol);

/* 32-bits only symXxxFind and symFindXxx APIs (DEPRECATED APIs) */

#ifndef _WRS_CONFIG_LP64
extern STATUS	symByValueAndTypeFind	(SYMTAB_ID symTblId, UINT value,
					 char ** pName, int * pValue,
					 SYM_TYPE * pType, SYM_TYPE sType, 
					 SYM_TYPE mask)
		_WRS_DEPRECATED ("please use symFind() instead");
extern STATUS	symByValueFind		(SYMTAB_ID symTblId, UINT value,
					 char ** pName, int * pValue,
					 SYM_TYPE * pType)
		_WRS_DEPRECATED ("please use symFind() instead");
extern STATUS	symFindByNameAndType	(SYMTAB_ID symTblId, char * name, 
					 char ** pValue, SYM_TYPE * pType, 
					 SYM_TYPE sType, SYM_TYPE mask)
		_WRS_DEPRECATED ("please use symFind() instead");
extern STATUS	symFindByName		(SYMTAB_ID symTblId, char * name,
					 char ** pValue, SYM_TYPE * pType)
		_WRS_DEPRECATED ("please use symFind() instead");
extern STATUS	symFindByValueAndType	(SYMTAB_ID symTblId, UINT value, 
					 char * name, int * pValue, 
					 SYM_TYPE * pType, SYM_TYPE sType,
					 SYM_TYPE mask)
		_WRS_DEPRECATED ("please use symFind() instead");
extern STATUS	symFindByValue		(SYMTAB_ID symTblId, UINT value,
					 char * name, int * pValue,
					 SYM_TYPE * pType)
		_WRS_DEPRECATED ("please use symFind() instead");
#endif	/* !_WRS_CONFIG_LP64 */

#ifdef __cplusplus
}

extern SYMBOL_ID symEach (SYMTAB_ID symTblId, FUNCPTR routine,
			  _Vx_usr_arg_t routineArg) \
	   _WRS_DEPRECATED ("Please use fully qualified function pointer "
			    "version of API");

/*
 * Inlined C++ wrapper for the old-style FUNCPTR based symEach() function
 * prototype.
 */

inline SYMBOL_ID symEach
    (
    SYMTAB_ID symTblId,
    FUNCPTR routine,
    _Vx_usr_arg_t routineArg
    )
    {
    return symEach (symTblId,
                    (BOOL (*)(char *, SYM_VALUE, SYM_TYPE, _Vx_usr_arg_t,
			      SYM_GROUP)) routine, routineArg);
    }
#endif /* __cplusplus */

#endif /* __INCsymLibh */
