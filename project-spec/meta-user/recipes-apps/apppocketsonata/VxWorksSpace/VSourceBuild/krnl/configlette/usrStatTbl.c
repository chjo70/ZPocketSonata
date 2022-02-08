/* usrStatTbl.c - error status symbol table initialization library */

/*
 * Copyright (c) 1998, 2005, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
04nov14,jpb  added header file for _func_printErr (V7COR-910)
27jul05,lei  added error checking (SPR#105895)
03jun98,ms   written
*/

/*
DESCRIPTION
Initialize the error status table used by perror and printErrno.
*/

#include <private/fioLibP.h>	/* _func_printErr */

/******************************************************************************
*
* usrStatTblInit - initialize the error status table
*/ 

void usrStatTblInit (void)
    {
    int ix;

    statSymTbl = symTblCreate (STAT_TBL_HASH_SIZE_LOG2, FALSE, memSysPartId);

    if (statSymTbl == NULL)
        {
        if (_func_printErr != NULL)
            _func_printErr ("usrRoot: error creating the error status table\n");
        }
    else
        {
        /* fill in from builtin table*/

        for (ix = 0; ix < statTblSize; ix ++)       
            symTblAdd (statSymTbl, &(statTbl [ix]));
        }
    }
