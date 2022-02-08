/* devctl.h - device control header */

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
01c,29jul10,pad  Moved extern C statement after include statements.
01b,24aug06,pcm  changed 'restrict' keywork to '_Restrict' (WIND00063164)
01a,15jun06,pcm  written.
*/

#ifndef __INCdevctlh
#define __INCdevctlh

#include <sys/types.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int posix_devctl (int, int, void * _Restrict, size_t, int * _Restrict);

#ifdef __cplusplus
}
#endif

#endif
