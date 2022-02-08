/* nfs3Drv.h - nfs3Drv header */

/*
 * Copyright (c) 2005 - 2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01d,29apr10,pad  Moved extern C statement after include statements.
01c,07sep06,mwv  update include paths
01b,05nov04,vvv  added nfsDriver.h (SPR #103655)
01a,10oct03,snd  written                                 
*/

#ifndef __INCnfs3Drvh
#define __INCnfs3Drvh

#include <vwModNum.h>
#include <limits.h>
#include <hostLib.h>
#include <nfs/xdr_nfs3.h>
#include <nfs/nfsDriver.h>

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern STATUS  nfs3Drv (void);
extern int     nfs3DrvNumGet (void);
extern STATUS  nfs3Mount (char *host, char *fileSystem, char *localName);
extern STATUS  nfs3MountAll (char *host, char *clientName, BOOL quiet);
extern STATUS  nfs3UnmountAll (char *host);
extern STATUS  nfs3DevInfoGet (unsigned long nfsDevHandle,NFS_DEV_INFO * info);

#else

extern STATUS  nfs3Drv ();
extern int     nfs3DrvNumGet ();
extern STATUS  nfs3Mount ();
extern STATUS  nfs3MountAll ();
extern STATUS  nfs3UnmountAll ();
extern NFS3_DEV * nfsDevFind ();
extern STATUS   nfs3DevInfoGet ();

#endif    /* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCnfs3Drvh */
