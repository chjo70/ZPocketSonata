/* shellDataLibP.h - private header for the shell data management module */

/* Copyright 2003, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01b,29apr10,pad  Moved extern C statement after include statements.
01a,28oct03,bpn  Written.
*/

#ifndef __INCshellDataLibPh
#define __INCshellDataLibPh

/* Includes */
#ifndef HOST
#include <vxWorks.h>
#else
#include <host.h>
#endif

#include <shellLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Defines */

/* Structures */

/* Function declarations */

void shellDataAllRemove (SHELL_ID shellId, BOOL finalize);

#ifdef __cplusplus
}
#endif

#endif /* __INCshellDataLibPh */
