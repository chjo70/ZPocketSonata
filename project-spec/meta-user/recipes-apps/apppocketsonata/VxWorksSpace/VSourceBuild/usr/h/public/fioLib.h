/* fioLib.h - header for formatted i/o library */

/* 
 * Copyright (c) 2004, 2010 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */

/*
modification history
--------------------
04oct10,mcm  LP64 updates
29jul10,pad  Moved extern C statement after include statements.
20sep04,job  SPR #101911
19apr04,ans  added oprintf(), fdprintf(), printErr(), voprintf,
             vfdprintf()
12mar04,job  Created based on kernel version - this is a temporary
             version to supply fioFormatV & fdprintf.
             NOTE: fdprintf definition needs to move to stdio.h
             like the kernel version
*/

#ifndef __INCfioLibh
#define __INCfioLibh

#if defined(__STDC__) || defined(__cplusplus)
#include "stdarg.h"
#endif /* __STDC__ */

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef STATUS (*FIOFORMATV_OUTPUT_FUNCPTR)
	(
	const char *,
	size_t,
	_Vx_usr_arg_t
	);

typedef int (*OPRINTF_OUTPUT_FUNCPTR)
	(
	const char *, 
	size_t, 
	_Vx_usr_arg_t)
	;

/* function declarations */

extern void 	fioFltInstall (FUNCPTR formatRtn, FUNCPTR scanRtn);
extern int 	fioFormatV (const char *fmt, va_list vaList,
			    FIOFORMATV_OUTPUT_FUNCPTR outRoutine, _Vx_usr_arg_t outarg);

extern int oprintf (OPRINTF_OUTPUT_FUNCPTR prtFunc, _Vx_usr_arg_t prtArg, const char * fmt, ...);
extern int voprintf (OPRINTF_OUTPUT_FUNCPTR prtFunc, _Vx_usr_arg_t prtArg, const char * fmt,
                     va_list vaList);
extern int printErr ( const char *  fmt, ...);
extern int fdprintf ( int fd, const char *  fmt, ...);
extern int vfdprintf (int fd, const char *  fmt, va_list vaList);
extern ssize_t fioRead (int fd, char *buffer, size_t maxbytes);
extern ssize_t fioRdString (int fd, FAST char string[], size_t maxbytes);

#ifdef __cplusplus
}
#endif

#endif /* __INCfioLibh */
