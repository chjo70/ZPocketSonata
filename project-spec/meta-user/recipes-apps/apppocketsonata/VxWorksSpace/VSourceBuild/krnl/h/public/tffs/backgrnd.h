/* backgrnd.h - True Flash File System */

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

#ifndef BACKGRND_H
#define BACKGRND_H

#include "flsocket.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BG_RESUME	1
#define	BG_SUSPEND	2

#ifdef BACKGROUND

extern int flForeground(int sendValue);
extern int flBackground(int sendValue);
extern int flStartBackground(unsigned volNo, void (*routine)(void *), void *object);
extern void flCreateBackground(void);

#else

#define flForeground(n)   BG_RESUME
#define flBackground(n)

#endif

#ifdef __cplusplus
}
#endif

#endif /* BACKGRND_H */

