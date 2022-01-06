/* demangler.h - WR wrapper around the toolchain's demangler */

/*
* Copyright (c) 2001,2003-2005, 2010-2011, 2016 Wind River Systems, Inc.
*
* The right to copy, distribute, modify or otherwise make use
* of this software may be licensed only pursuant to the terms
* of an applicable Wind River license agreement.
*/

/*
modification history
--------------------
17jun16,lau  Added prototypes for realDemangleToBufferEx and demangleToBufferEx
11oct11,mcm  Cleanup (WIND00288945)
27may10,pad  Moved extern C statement after include statements.
12dec05,sn   added demangleResultFree helper function
02aug04,sn   added demangleToBuffer entry point
16dec03,sn   DEBUG_DEMANGLER really no longer on by default!
05may03,sn   DEBUG_DEMANGLER no longer on by default
15apr03,sn   moved to share/src/demangler
10dec01,sn   move enum defs to demanglerTypes.h
28nov01,sn   wrote
*/

#ifndef __INCdemanglerh
#define __INCdemanglerh

/* includes */

#include <demanglerTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* typedefs */

char * demangle
    (
    const char * mangledSymbol,
    DEMANGLER_STYLE style,      /* the scheme used to mangle symbols */
    DEMANGLER_MODE mode         /* how hard to work */
    );

void demangleResultFree
    (
    char * demangleResult      /* value returned by demangle() */
    );

DEMANGLER_RESULT realDemangleToBufferEx
    (
    char * mangledSymbol,
    char * buffer,              /* output buffer for demangled name */
    size_t * pBufferSize,       /* in: actual buffer size / out: required buffer size */
    char * substBuffer,         /* substitution buffer used by the demangler (can be NULL, must be 4 byte aligned) */
    size_t * pSubstBufferSize,  /* in: size of substitution buffer in bytes (must be zero if substBuffer is NULL) / out : required size */
    DEMANGLER_MODE mode,
    char ** pResult       /* out: result string */
    );

DEMANGLER_RESULT demangleToBuffer
    (
    char * mangledSymbol,
    char * buffer,		/* output buffer for demangled name */
    size_t * pBufferSize,	/* in: actual buffer size / out: required buffer size */
    DEMANGLER_MODE mode,	
    char ** pResult		/* out: result string */
    );

DEMANGLER_RESULT demangleToBufferEx
    (
    char * mangledSymbol,
    char * buffer,		/* output buffer for demangled name */
    size_t * pBufferSize,	/* in: actual buffer size / out: required buffer size */
    char * substBuffer,		/* substitution buffer used by the demangler (can be NULL, must be 4 byte aligned) */
    size_t * pSubstBufferSize,   /* in: size of substitution buffer in bytes (must be zero if substBuffer is NULL) / out : required size */
    DEMANGLER_MODE mode,	
    char ** pResult		/* out: result string */
    );

DEMANGLER_STYLE demanglerStyleFromName
    (
    const char * styleName,
    DEMANGLER_STYLE defaultStyle
    );

const char * demanglerNameFromStyle
    (
    DEMANGLER_STYLE style
    );

/* Add #define DEBUG_DEMANGLER here to turn on debugging */

#ifdef DEBUG_DEMANGLER
#define debug_dmgl(fmt, x) (printf("debug_dmgl: "), printf((fmt), (x)))
#else
#define debug_dmgl(fmt, x)
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCdemanglerh */

