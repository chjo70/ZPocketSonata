/* nfsLib.h - Network File System library header */

/*
 * Copyright (c) 1988, 1990-1993, 1997, 2004, 2006 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01s,19sep06,mwv  update nfs include path (WIND00065965) 
01r,29jun04,dlk  Make this obsolete file include nfs2Lib.h and nfs3Lib.h;
		 remove other contents.
01q,20nov97,gnn  fix for spr#5436, need to support FIOFSTATFSGET
01p,28jul93,jmm  moved AUTH_UNIX_FIELD_LEN and MAX_GRPS definitions to here
01o,22sep92,rrr  added support for c++
01n,18sep92,jcf  removed ansi warnings.
01m,07sep92,smb  added includes xdr_nfs.h and sys/stat.h to remove ANSI warnings
01l,04jul92,jcf  cleaned up.
01k,26may92,rrr  the tree shuffle
01j,16dec91,gae  added missing prototypes for ANSI.
01i,04oct91,rrr  passed through the ansification filter
		  -changed VOID to void
		  -changed copyright notice
01h,08mar91,elh  added NFS_REXMIT_{SEC,USEC}.
01g,25oct90,dnw  deleted private function.
01f,05oct90,shl  added ANSI function prototypes.
                 made #endif ANSI style.
                 added copyright notice.
01e,10aug90,dnw  added declarations of nfsAuthUnix[GS]et().
01d,09sep88,llk  added NFS_TIMEOUT_SEC, NFS_TIMEOUT_USEC, NFS_SOCKOPTVAL.
01c,26aug88,gae  removed unused imports.
01b,04jun88,llk  moved FOLLOW_LINK, DEFAULT_FILE_PERM and DEFAULT_DIR_PERM
		   to ioLib.h.
01a,19apr88,llk  written.
*/

#ifndef __INCnfsLibh
#define __INCnfsLibh

#if 0
#error nfsLib.h is obsolete. Use nfs2Lib.h and/or nfs3Lib.h.
#endif

#include <nfs/nfs2Lib.h> /* brings in nfsCommon.h */
#include <nfs/nfs3Lib.h>

#endif /* __INCnfsLibh */
