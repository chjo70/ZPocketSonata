/* timers.h - time header */

/* Copyright 1991-1992, 2010, 2015 Wind River Systems, Inc. */

/*
modification history
--------------------
11feb15,pad  Updated description.
29apr10,pad  Moved extern C statement after include statements.
29nov93,dvs  moved code to time.h
30sep92,smb  corrected STDC prototype listing.
22sep92,rrr  added support for c++
22jul92,gae  fixed clock_id types; more POSIXy.
25jul92,smb  moves contents of time.h to timers.h.
04jul92,jcf  cleaned up.
26may92,rrr  the tree shuffle
30apr92,rrr  some preparation for posix signals.
10feb91,gae  revised according to DEC review.
             defined sigevent and sigval structures according to Draft;
             added ENOSYS errno here, temporarily;
	     flagged definitions in wrong location with xPOSIX.
16oct91,gae  written.
*/

/*
DESCRIPTION
This file is kept for backward compatibility reasons. It simply includes the
POSIX time.h header which brings the POSIX time interface definitions.
*/

#ifndef __INCtimersh
#define __INCtimersh

#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCtimersh */
