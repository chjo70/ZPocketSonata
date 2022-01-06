/* fioLib.h - header for formatted i/o library */

/*
 * Copyright (c) 1984-1995, 2009-2010 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */

/*
modification history
--------------------
01r,15sep10,mcm  Updated FIOFORMATV_OUTPUT_FUNCPTR definition for LP64
01q,19jan10,pad  Applied C++ inline scheme for fioFormatV() and fioScanV().
01q,19jan10,pad  Removed usage of _WRS_KEEP_USING_FUNCPTR.
01p,26mar09,mcm  Updates for the LP64 data model; moved unpublished APIs out
01o,14may95,p_m  added fioLibInit() prototype.
01n,20jul92,jmm  removed declaration of itob()
01m,13nov92,dnw  made include of stdarg.h conditional on __STDC__
01l,22sep92,rrr  added support for c++
01k,02aug92,jcf  added printExc().
01j,04jul92,jcf  cleaned up.
01i,26may92,rrr  the tree shuffle
01h,04dec91,rrr  some more ansi cleanup.
01g,04oct91,rrr  passed through the ansification filter
		  -changed includes to have absolute path from h/
		  -fixed #else and #endif
		  -changed copyright notice
01f,24mar91,del  added include of varargs.h.
01e,05oct90,shl  added ANSI function prototypes.
                 added copyright notice.
                 made #endif ANSI style.
01d,07aug90,shl  added INCfioLibh to #endif.
01c,10jun90,dnw  removed S_fioLib_UNEXPECTED_EOF (no longer returned by fioRead)
		 This file is now just a place holder!
01b,24dec86,gae  changed stsLib.h to vwModNum.h.
01a,07aug84,ecs  written
*/

#ifndef __INCfioLibh
#define __INCfioLibh

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Type definitions for fioFormatV() and fioScanV()'s fully-qualified
 * function pointer parameter.
 */

typedef int  (*GET_NEXT_CHAR_FUNCPTR) (void *);

typedef STATUS (*FIOFORMATV_OUTPUT_FUNCPTR)
        (
        char *,
        size_t,
        _Vx_usr_arg_t
        );

/* function declarations */

extern void 	fioLibInit (void);
extern void 	fioBaseLibInit (void);
extern int 	fioFormatV 
    (
    const char *fmt, 
    va_list vaList,
    FIOFORMATV_OUTPUT_FUNCPTR outRoutine,
    _Vx_usr_arg_t outarg
    );
extern int 	fioScanV 
    (
    const char *fmt, 
    GET_NEXT_CHAR_FUNCPTR getRtn,
    void *getArg,
    int *pUnget, 
    va_list vaList
    );

extern ssize_t 	fioRead (int fd, char *buffer, size_t maxbytes);
extern ssize_t 	fioRdString (int fd, char string[], size_t maxbytes);

#ifdef __cplusplus
}

/*
 * inlined C++ wrapper for the old-style FUNCPTR based fioFormatV() and
 * fioScanV() function prototypes.
 */

extern int fioFormatV (const char *fmt, va_list vaList, FUNCPTR outRoutine,
                       _Vx_usr_arg_t outarg) \
	   _WRS_DEPRECATED ("please use fully qualified function pointer "
			    "version of API");

inline int fioFormatV
    (
    const char *fmt,
    va_list vaList,
    FUNCPTR outRoutine,
    _Vx_usr_arg_t outarg
    )
    {
    return fioFormatV (fmt, vaList, (FIOFORMATV_OUTPUT_FUNCPTR)outRoutine,
		       outarg);
    }

extern int fioScanV (const char *fmt, FUNCPTR getRtn, void *getArg,
		     int *pUnget, va_list vaList) \
	   _WRS_DEPRECATED ("please use fully qualified function pointer "
			    "version of API");

inline int fioScanV
    (
    const char *fmt,
    FUNCPTR getRtn,
    void *getArg,
    int *pUnget,
    va_list vaList
    )
    {
    return fioScanV (fmt, (GET_NEXT_CHAR_FUNCPTR)getRtn, getArg, pUnget,
		     vaList);
    }
#endif /* __cplusplus */

#endif /* __INCfioLibh */
