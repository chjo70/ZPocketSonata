/* strings.h - POSIX Extensions to ISO C string library */

/*
 * Copyright (c) 2006, 2010 Wind River Systems, Inc.
 * 
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */

/*
modification history
--------------------
01b,29apr10,pad  Moved extern C statement after include statements.
01a,25apr06,mcm  written and documented.
*/

#ifndef __INCstringsh
#define __INCstringsh

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int 	strcasecmp(const char *, const char *);
extern int 	strncasecmp(const char *, const char *, size_t);

#ifdef __cplusplus
}
#endif

#endif /* __INCstringsh */
