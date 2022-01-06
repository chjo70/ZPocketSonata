/* tagCheckLibP.c - generic tag checker engine private header */

/*
 * Copyright (c) 2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software may be
 * licensed only pursuant to the terms of an applicable Wind River license
 * agreement.
 */

/*
modification history
--------------------
01b,15jul09,v_r  Cleanup for Clearcase integration.
01a,18apr09,f_b  Written.
*/

typedef struct tagchk_module {
    char * name;
} TAGCHK_MDL;

typedef TAGCHK_MDL * TAGCHK_MDL_ID;

TAGCHK_MDL_ID	tagCheckModuleAdd (const char * moduleName);
void	tagCheckModuleDel (TAGCHK_MDL_ID moduleId);
int	tagCheckStatementAdd (TAGCHK_MDL_ID moduleId, 
			      const char * statement, char * errorMsg, 
			      size_t maxSize);
int	tagCheckEvaluateAsserts (char * errorMsg, size_t maxSize);
