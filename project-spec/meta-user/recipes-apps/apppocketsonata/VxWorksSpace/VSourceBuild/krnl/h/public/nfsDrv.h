/* nfsDrv.h - nfsDrv header */

/*
 * Copyright (c) 1988, 1990-1993, 1995, 1998, 
 *              2001, 2004, 2006 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01s,19sep06,mwv  update nfs include path (WIND00065965)
01r,29jun04,dlk  Make this obsolete file include nfsDriver.h; remove
		 other contents
01q,05nov01,vvv  made max. path length configurable (SPR #63551)
01p,10oct01,rae  merge from truestack ver 01o base 01n (added xdr_nfs.h)
01o,07feb01,spm  merged from version 01o of tor3_x branch (base version 01n):
                 added permission checks to nfsOpen() routine
01n,16dec98,cjtc added prototype for nfsDrvNumGet
01m,28mar95,kdl  added includes of limits.h and hostLib.h (SPR 4157)..
01l,01dec93,jag  added NFS_DEV_INFO, nfsDevListGet(), and nfsDevInfoGet().
01k,22sep92,rrr  added support for c++
01j,04jul92,jcf  cleaned up.
01i,26may92,rrr  the tree shuffle
01h,04oct91,rrr  passed through the ansification filter
		  -changed VOID to void
		  -changed copyright notice
01g,05oct90,dnw  changed nfsMountAll() arg from verbose to quiet.
01f,05oct90,shl  added ANSI function prototypes.
                 made #endif ANSI style.
                 added copyright notice.
01e,07aug90,shl  added IMPORT type to function declarations.
01d,01may90,llk  added function declarations.
01c,30sep88,llk  removed S_nfsDrv_UNKNOWN_HOST.
01b,30jun88,llk  added S_nfsDrv_NO_HOST_NAME_SPECIFIED.
01a,19apr88,llk  written.
*/

#ifndef __INCnfsDrvh
#define __INCnfsDrvh

#if 0
#error nfsDrv.h is obsolete. Use nfsDriver.h.
#endif

#include <nfs/nfsDriver.h>

#endif /* __INCnfsDrvh */
