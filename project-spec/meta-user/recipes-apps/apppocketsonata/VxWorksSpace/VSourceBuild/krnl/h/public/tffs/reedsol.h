/* reedsol.h - True Flash File System */

/*
 * Copyright (c) 1984-2004, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/* FAT-FTL Lite Software Development Kit
 * Copyright (C) M-Systems Ltd. 1995-1997	*/

/*
modification history
--------------------
01b,29jul10,pad  Moved extern C statement after include statements.
01a,29jul04,alr  modified file header, restarted history
*/

#ifndef FLEDC_H
#define FLEDC_H

#include "flbase.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum { NO_EDC_ERROR, CORRECTABLE_ERROR, UNCORRECTABLE_ERROR, EDC_ERROR } EDCstatus;

EDCstatus flCheckAndFixEDC(char FAR1 *block, char *syndrom, FLBoolean byteSwap);

#ifdef __cplusplus
}
#endif

#endif /* FLEDC_H */
