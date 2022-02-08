/* nfs2Drv.h - nfs2Drv header */

/*
 * Copyright (c) 2003, 2006, 2010, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01c,29apr10,pad  Moved extern C statement after include statements.
01b,07sep06,mwv  update includes
01a,10oct03,snd  written.
*/

#ifndef __INCnfs2Drvh
#define __INCnfs2Drvh

#include <vwModNum.h>
#include <limits.h>
#include <hostLib.h>
#include <nfs/xdr_nfs2.h>

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern STATUS     nfs2Drv (void);
extern int        nfs2DrvNumGet (void);
extern STATUS     nfs2Mount (char *host, char *fileSystem, char *localName);
extern STATUS     nfs2MountAll (char *host, char *clientName, BOOL quiet);
extern STATUS     nfs2UnmountAll (char *host);
#else

extern STATUS     nfs2Drv ();
extern int        nfs2DrvNumGet ();
extern STATUS     nfs2Mount ();
extern STATUS     nfs2MountAll ();
extern STATUS     nfs2UnMountAll ();

#endif    /* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCnfs2Drvh */
