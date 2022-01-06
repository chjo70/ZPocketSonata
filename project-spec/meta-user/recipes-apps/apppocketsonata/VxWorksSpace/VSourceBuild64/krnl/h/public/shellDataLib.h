/* shellDataLib.h - header for the shell data management module */

/* Copyright 2003-2004, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01d,29apr10,pad  Moved extern C statement after include statements.
01c,23sep04,bpn  Added SHELL_DATA_FUNCPTR definition.
01b,07apr04,bpn  Modified shellDataFirst() and shellDataNext() API.
01a,28oct03,bpn  Written.
*/

#ifndef __INCshellDataLibh
#define __INCshellDataLibh

/* Includes */
#ifdef HOST
#include <host.h>
#endif

#include <shellLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Defines */

/* Structures */

/* Typedefs */

typedef void (*SHELL_DATA_FUNCPTR) (SHELL_ID shellId, const char * key,
				    void * pData);

/* Function declarations */

extern STATUS	shellDataFromNameAdd (const char * taskName,
				      const char * key, void * pData,
				      SHELL_DATA_FUNCPTR finalizeRtn);

extern STATUS	shellDataAdd (SHELL_ID shellId, const char * key,
			      void * pData, SHELL_DATA_FUNCPTR finalizeRtn);

extern void	shellDataRemove (SHELL_ID shellId, const char * key,
				 BOOL finalize);

extern STATUS	shellDataFromNameGet (const char * taskName,
				      const char * key, void ** ppData);

extern STATUS	shellDataGet (SHELL_ID shellId, const char * key,
			      void ** ppData);

extern SHELL_ID	shellDataFirst (const char * key, void ** ppData);
extern SHELL_ID	shellDataNext (const char * key, SHELL_ID shellId,
			       void ** ppData);

#ifdef __cplusplus
}
#endif

#endif /* __INCshellDataLibh */
