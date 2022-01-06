/* cplusLib.h - VxWorks C++ support */

/* 
 * Copyright (c) 1992, 1993, 2001, 2003-2004, 2016 Wind River Systems, Inc. 
 * 
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */

/*
modification history
--------------------
17jun16,lau  Fixed cplusXtorGet prototype
11oct04,jn   Add cplusXtorGet routine
14apr03,sn   include demanglerTypes.h rather than duplicating definitions
07dec01,sn   added demangler declarations
26apr93,srh  added cplus?torsLink declarations.
01jan93,srh  written.
*/

#ifndef __INCcplusLibh
#define __INCcplusLibh

#include "private/cplusLibP.h"
#include "demanglerTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

void cplusCtors (const char * moduleName);
void cplusDtors (const char * moduleName);
void cplusCtorsLink ();
void cplusDtorsLink ();
void cplusDemanglerSet (int mode);
void cplusDemanglerStyleSet (DEMANGLER_STYLE style);
void cplusXtorSet (int strategy);
int  cplusXtorGet (void);

#else   /* __STDC__ */

void cplusCtors ();
void cplusDtors ();
void cplusCtorsLink ();
void cplusDtorsLink ();
void cplusDemanglerSet ();
void cplusXtorSet ();
int  cplusXtorGet (void);

#endif  /* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCcplusLibh */
