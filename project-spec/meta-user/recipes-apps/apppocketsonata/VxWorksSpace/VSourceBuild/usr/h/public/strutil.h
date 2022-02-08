/* strutil.h - sweet string utilities header file */

/*
 * Copyright (c) 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software may be
 * licensed only pursuant to the terms of an applicable Wind River license
 * agreement.
 */

/*
modification history
--------------------
06apr16,dlk  Written.
*/

#ifndef __INCstrutilh
#define __INCstrutilh

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

extern char * strendcpy (char * dst, char * end, const char * src);
extern const char * skipPrefix (const char * prefix, const char *str);

#ifdef __cplusplus
}
#endif

#endif /* __INCstrutilh */
