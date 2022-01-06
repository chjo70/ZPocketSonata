/* nfsdLib.h - Network File System Server library header */

/*
 * Copyright (c) 1994, 2004, 2006 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01e,19sep06,mwv  update nfs include path (WIND00065965)
01d,01jul04,dlk  Make this header include nfsdCommon.h and nfsd.h;
                 remove other contents.
01c,21apr94,jmm  more cleanup of prototypes; added NFSD_ARGUMENT
01b,20apr94,jmm  added new prototypes
01a,31mar94,jmm  written.
*/

#ifndef __INCnfsdLibh
#define __INCnfsdLibh

#if 0
#error nfsdLib.h is obsolete. Use nfsdCommon.h and/or nfsd.h.
#endif

#include <nfs/nfsdCommon.h>
#include <nfs/nfsd.h>

#endif /* __INCnfsdLibh */
