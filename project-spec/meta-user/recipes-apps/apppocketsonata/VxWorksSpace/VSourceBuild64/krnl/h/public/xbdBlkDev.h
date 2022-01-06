/* xbdBlkDev.h - BLK_DEV to XBD interface converter */

/*
 * Copyright (c) 2005-2007, 2011, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
17nov14,yjl  Provide a VSB or cdf configure to change
             the stack size of "tXbdService" task (V7STO-204)
01i,30dec11,zly  WIND00217466: add a direct mode for xbd.
01h,29apr10,pad  Moved extern C statement after include statements.
01g,24jan07,dee  Set geometry of block device to default if not set.
                 WIND00057345, WIND00086299
01f,12dec06,dcc  fixed defect WIND0070704:"xbdBlkDevCreate creates a task with
                 hardcoded priority."
01e,12apr06,dee  SPR 119990, WIND00037359 - add cplusplus constructs
01d,25aug05,pcm  added xbdBlkDevCreateSync()
01c,15jul05,pcm  added xbdBlkDevDelete()
01b,08mar05,pcm  added xbdBlkDevLibInit()
01a,31jan05,rfr  Fixed inclusion of xbd.h
*/

#ifndef __INCxbdBlkDevh
#define __INCxbdBlkDevh

#include <blkIo.h>
#include <drv/xbd/xbd.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Default values for disk geometry for block devices if
 * the block device driver doesn't initialize them
 */
#define DEFAULT_SECS_TRACK 63
#define DEFAULT_HEADS      255

extern STATUS   xbdBlkDevLibInit     (int xbdServiceTskPri,
                                      int xbdServiceTskStkSz, BOOL directMode);
extern device_t xbdBlkDevCreate      (BLK_DEV *bd, const char *name);
extern device_t xbdBlkDevCreateSync  (BLK_DEV *bd, const char *name);
extern STATUS   xbdBlkDevDelete      (device_t d, BLK_DEV **  ppbd);

#ifdef __cplusplus
}
#endif

#endif /* __INCxbdBlkDevh */
