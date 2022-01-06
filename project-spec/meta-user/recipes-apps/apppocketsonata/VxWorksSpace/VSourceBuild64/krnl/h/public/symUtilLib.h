/* symUtilLib.h - symbol table utilities library header */

/* Copyright 1999-2004, 2010 Wind River Systems, Inc. */

/*
modification history
--------------------
01h,29apr10,pad  Moved extern C statement after include statements.
01g,18aug04,bpn  Modified to support C++ demangled symbol names in a better
                 way.
01f,04mar04,bpn  Added support for C++ symbol namespace.
01e,28jan04,bpn  Modified symListGet() API.
01d,08jul03,bpn  Updated symListGet() API.
01c,27jun03,bpn  Removed PD references.
01b,20dec99,rlp  modified the symListGet API and the MATCH_SYMBOL structure.
01a,18aug99,jmp  written.
*/

#ifndef __INCsymUtilLibh
#define __INCsymUtilLibh

#include <lstLib.h>
#include <symLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

typedef enum
    {
    STR_MATCH,		/* C symbol contains the string */
    C_MATCH,		/* C symbol begins by string */
    TERSE_MATCH,	/* Terse name begins by string */ 
    DEMANGLE_MATCH	/* Demangled name begins by string */
    } MATCH_SYMBOL_TYPE;

/* This structure is entirely allocated in one memory block */

typedef struct
    {
    NODE		node;
    char *		name;	/* matching C symbol name */
    char *		terseName; /* terse name or NULL */
    char *		signature; /* signature or NULL */
    MATCH_SYMBOL_TYPE	type;	/* matching type */
    } MATCH_SYMBOL;

extern void 	symListGet (SYMTAB_ID symTabId, const char * string,
			    BOOL demangleMatching, LIST * pSymList);

#ifdef __cplusplus
}
#endif

#endif /* __INCsymUtilLibh */
