/* times.h - UNIX-style timeval structure defenition */

/*
 * Copyright (c) 1987, 1990-1992, 2011 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02e,17nov11,jpb  Moved timeval into sys/time.h.
02d,22sep92,rrr  added support for c++
02c,19aug92,smb  moved from systime.h
02b,31jul92,gae  changed INCtimeh to INCsystimeh.
02a,04jul92,jcf  cleaned up.
01g,26may92,rrr  the tree shuffle
01f,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed copyright notice
01e,10jun91.del  added pragma for gnu960 alignment.
01d,25oct90,dnw  changed name from utime.h to systime.h.
		 added test for SunOS headers already included.
01c,05oct90,shl  added copyright notice.
01b,04nov87,dnw  removed unnecessary stuff.
01a,15oct87,rdc  written
*/

#ifndef __INCtimesh
#define __INCtimesh

#include <sys/time.h>  /* timeval defined per posix specs */

#endif /* __INCtimesh */
