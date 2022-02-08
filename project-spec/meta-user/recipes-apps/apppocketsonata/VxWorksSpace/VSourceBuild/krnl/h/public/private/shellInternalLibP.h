/* shellInternalLibP.h - private header for the internal shell library */

/*
 * Copyright (c) 2003-2004, 2006, 2008-2010,2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
08jul15,elp  Added shellInternalStrToShort() (V7COR-3244).
29apr10,pad  Moved extern C statement after include statements.
02apr09,jmp  Completed 64-bit target side support:
             Added shellInternalFuncLongArgAdd and shellInternalStrToLong.
             Changed SHELL_FUNC_ARG_STACK arguments to longs.
03mar09,v_r  LP64 adaptation: used TASK_ID.
26feb08,v_r  Moved SHELL_OPTION to public header.
04aug06,dbt  Moved some header files needed for public APIs to
             shellLib.h (defect CQ:WIND00038942).
22sep04,bpn  Renamed shellInternalLibP.h. Updated shellInternalStrToInt()
             prototype.
09sep04,bpn  Added shellInternalStrToInt32() prototype.
01sep04,bpn  Removed shellInternalDemangleSymbolGet() prototype.
18aug04,bpn  Updated prototypes.
21jun04,p_b  modified shellInternalOptGet to take / or - as option token
11may04,bpn  Modified shellInternalTaskNameMatch() API.
15apr04,bpn  Added shellInternalDecValueDisplay() and
             shellInternalHexValueDisplay() prototypes.
11mar04,bpn  Added shellInternalHostFunctionCall() and 
             shellInternalFuncStringArgAdd() prototypes.
04mar04,bpn  Modified the symbol function API to support a namespace string.
26feb04,bpn  Moved prototypes to shellMemLib.h.
02feb04,bpn  Modified shellInternalRegFree() prototype. Added 
             shellInternalMemRegister(), shellInternalMemUnregister()
             shellInternalMemAllFree() prototypes.
21jan04,bpn  Modified shellInternalRegAllFree() prototype.
03dec03,bpn  Added shellInternalSymTblFromTaskGet() and
             shellInternalSymTblFromRtpGet() prototypes.
25nov03,lcs  Add prototype for routine to decode command arguments
             commencing with & or $ characters.
06oct03,bpn  Added shellInternalStrSpaceTokenize() prototype.
21oct03,bpn  Updated symbol related function API.
03oct03,bpn  Added shellInternalStrToFloat() prototype.
23sep03,bpn  Fixed build warning. Moved structures from shellLib.h.
22aug03,bpn  Added shellInternalOptGet() and shellInternalOptFree()
             prototypes.
19aug03,bpn  Added several functions in order the shell uses its own
             memory partition (partial fix of SPR #90221).
22jul03,bpn  Added shellInternalStrToChar(), shellInternalStrUnquote(),
             shellInternalStrTokenize() and shellInternalStrToInt()
             prototypes.
08jul03,bpn  Changed file shellInternalFuncArgAdd() to 
             shellInternalFuncIntArgAdd().
10jun03,bpn  Changed file name to shellInternalLib.h
13mar03,lcs  Add support for hostsh host function calls.
10mar03,lcs  Add support for host shell.
04mar03,bpn  Some definitions are only target specific.
17feb03,bpn  Written.
*/

#ifndef __INCshellInternalLibPh
#define __INCshellInternalLibPh

/* Includes */

#ifdef HOST
#include <host.h>
#endif

#include <lstLib.h>
#include <shellLib.h>
#include <shellInterpCmdLib.h>

#ifndef HOST
#include <hashLib.h>		/* needed by symLibP.h */
#include <private/semLibP.h>	/* needed by symLibP.h */
#include <private/symLibP.h>	/* needed for SYMTAB_ID */
#include <rtpLib.h>		/* needed for RTP_ID */
#else
#define SYMTAB_ID	int	/* WRS_XXX bpn - to change */
#define RTP_ID		int	/* WRS_XXX bpn - to change */
#define INSTR		void	/* WRS_XXX bpn - to change */
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Defines */

#define MAX_FUNC_ARGS	12	/* max number of args to any one function */
		/*  
		 * NOTE: The array indices in shellInternalFunctionCall()
		 *       must agree with MAX_FUNC_ARGS!!
		 */

/* Structures */

typedef enum shell_symbol_type
    {
    SHELL_SYM_ANY = 1,
    SHELL_SYM_TEXT,
    SHELL_SYM_DATA,
    SHELL_SYM_HOST,
    SHELL_SYM_NONE
    } SHELL_SYMBOL_TYPE;

typedef struct shell_func_arg_stack
    {
    UINT		numArgs;
    long		argsArray[MAX_FUNC_ARGS];
#ifdef HOST
    BOOL		isString[MAX_FUNC_ARGS];
#endif
    } SHELL_FUNC_ARG_STACK;

typedef enum shell_option_type	/* type of an option array */
    {
    SHELL_OPTION_ERROR = ERROR,
    SHELL_OPTION_GETOPT,
    SHELL_OPTION_ARGC_ARGV
    } SHELL_OPTION_TYPE;

/* Function definition */

extern SYMTAB_ID	shellInternalSymTblFromTaskGet (TASK_ID taskId,
							INSTR *	address);
extern SYMTAB_ID	shellInternalSymTblFromRtpGet (RTP_ID rtpId,
						       INSTR * address);

extern STATUS	shellInternalTextSymbolGet (SYMTAB_ID symTblId,
					    const char * symbolName,
					    SHELL_TYPE_VAL ** ppSymbolValue);

extern STATUS	shellInternalDataSymbolGet (SYMTAB_ID symTblId,
					    const char * symbolName,
					    SHELL_TYPE_VAL ** ppSymbolValue);

extern STATUS	shellInternalSymbolGet (SYMTAB_ID symTblId,
					const char * symbolName,
					SHELL_TYPE_VAL ** ppSymbolValue,
					SHELL_SYMBOL_TYPE * pSymTypeOut);

extern STATUS	shellInternalSymbolDisplay (SYMTAB_ID symTblId,
					    SHELL_TYPE_VAL * pSymbolVal,
					    const char * prefix,
					    const char * suffix);

extern STATUS	shellInternalDecValueDisplay (SHELL_TYPE_VAL * pValue,
					      BOOL unsignedVal,
					      SHELL_VALUE_TYPE type);

extern STATUS	shellInternalHexValueDisplay (SHELL_TYPE_VAL * pValue,
					      SHELL_VALUE_TYPE type);

extern STATUS	shellInternalValueDisplay (SYMTAB_ID symTblId,
					   SHELL_TYPE_VAL * pValue,
					   BOOL unsignedVal,
					   SHELL_VALUE_TYPE type);

extern STATUS	shellInternalKernelSymbolCreate (const char * symbolName,
						 SHELL_VALUE_TYPE type);

extern SHELL_FUNC_ARG_STACK * shellInternalArgStackAllocate (void);

extern STATUS	shellInternalFuncLongArgAdd (SHELL_FUNC_ARG_STACK * pArgStack,
					     long value);
#ifndef _WRS_CONFIG_LP64
extern STATUS	shellInternalFuncLLongArgAdd (SHELL_FUNC_ARG_STACK * pArgStack,
					      INT64 value);
#endif	/* !_WRS_CONFIG_LP64 */
extern STATUS	shellInternalFuncFloatArgAdd (SHELL_FUNC_ARG_STACK * pArgStack,
					      float value);

extern STATUS	shellInternalFuncDoubleArgAdd (SHELL_FUNC_ARG_STACK * pArgStack,
					       double value);

extern STATUS	shellInternalFunctionCall (SHELL_TYPE_VAL * pReturnValue,
					   SHELL_VALUE_TYPE funcType,
					   void * funcAddr,
					   SHELL_FUNC_ARG_STACK * pArgStack);

extern STATUS	shellInternalArgumentEval (const char * arg,
					   const char * interpreterName,
					   SHELL_EVAL_VALUE * pValue);

extern UINT	shellInternalTaskNameMatch (const char * substr, 
					    TASK_ID * pTaskId);

extern char *	shellInternalStrUnquote (char * string);
extern char *	shellInternalStrSpaceTokenize (char * string, char ** ppString);
extern char *	shellInternalStrTokenize (char * string,
					  const char * tokenSep,
					  char ** ppString);
extern int	shellInternalStrToChar (const char * string, char * pChar);
extern int	shellInternalStrToInt (const char * valueStr, 
				       SHELL_TYPE_VAL * pVal,
				       SHELL_VALUE_TYPE * pType,
				       BOOL * pIsUnsigned, BOOL autoType);
extern int	shellInternalStrToInt2 (const char * valueStr, 
				        SHELL_TYPE_VAL * pVal,
				        SHELL_VALUE_TYPE * pType,
				        BOOL * pIsUnsigned);
extern int	shellInternalStrToFloat (const char * valueStr,
					 SHELL_TYPE_VAL * pVal,
					 SHELL_VALUE_TYPE * pType);
extern STATUS	shellInternalStrToInt32 (const char * valueStr,
					 INT32 * pInt, const char * errorStr);
extern STATUS	shellInternalStrToShort (const char * valueStr,
					 INT16 * pShort, const char * errorStr);
extern STATUS	shellInternalStrToLong (const char * valueStr,
					long * pLong, const char * errorStr);

extern SHELL_OPTION_TYPE shellInternalOptGet (const char * options,
					      const char * argumentsStr,
					      const char optionToken,
					      SHELL_OPTION ** ppOptArray);
extern void	shellInternalOptFree (SHELL_OPTION * pOptArray);
extern STATUS   shellInternalSymbolsResolve (SHELL_OPTION * pOptArray, 
					     SYMTAB_ID symTabId);
#ifdef HOST
extern STATUS	shellInternalFuncStringArgAdd (SHELL_FUNC_ARG_STACK * pArgStack,
					       char * value);
extern STATUS	shellInternalHostFunctionCall (SHELL_TYPE_VAL * pReturnValue,
					       SHELL_VALUE_TYPE funcType,
					       void * funcAddr,
					       SHELL_FUNC_ARG_STACK * pArgStack,
					       BOOL isCmdForHost);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCshellInternalLibPh */
