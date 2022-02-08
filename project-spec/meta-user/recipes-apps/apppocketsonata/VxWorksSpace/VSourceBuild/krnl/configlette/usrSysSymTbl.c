/* usrSysSymTbl.c - system symbol table initialization */

/*
 * Copyright (c) 2006, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software may be
 * licensed only pursuant to the terms of an applicable Wind River license
 * agreement. No license to Wind River intellectual property rights is granted
 * herein. All rights not licensed by Wind River are reserved by Wind River.
 */

/*
modification history
--------------------
04nov14,jpb  added header file for _func_printErr (V7COR-910)
10jan06,bpn  Written
*/

/*
DESCRIPTION
Initialize the system symbol table.
*/

#include <private/fioLibP.h>		/* _func_printErr */

/******************************************************************************
*
* usrSysSymTblInit - initialize the system symbol table
*
* This routine initializes the system symbol table <sysSymTbl>.
*
* RETURNS: N/A
*
*/ 

void usrSysSymTblInit (void)
    {

    sysSymTbl = symTblCreate (SYM_TBL_HASH_SIZE_LOG2, TRUE, memSysPartId);

    if (sysSymTbl == NULL && _func_printErr != NULL)
       _func_printErr ("usrSysSymTblInit: error creating the system symbol "\
       		       "table.\n");

    }

