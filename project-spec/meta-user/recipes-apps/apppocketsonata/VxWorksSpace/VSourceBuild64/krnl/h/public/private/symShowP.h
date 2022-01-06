/* symShowP.h - private symbol show routines header file */

/*
 * Copyright (c) 2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01b,29apr10,pad  Moved extern C statement after include statements.
01a,21jul06,v_r  Written.
*/

#ifndef __INCsymShowPh
#define __INCsymShowPh

#include <symbol.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* structure definitions */

/* function declarations */

char * symTypeToStringConvert (SYM_TYPE symType);

#ifdef __cplusplus
}
#endif

#endif /* __INCsymShowPh */

