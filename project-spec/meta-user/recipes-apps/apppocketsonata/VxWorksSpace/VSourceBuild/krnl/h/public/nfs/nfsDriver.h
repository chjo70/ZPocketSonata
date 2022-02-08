/* nfsDriver.h - nfsDrv header */

/*
 * Copyright (c) 2005 - 2006, 2010, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01f,21dec12,xwu  Coverity issue of nfs
01e,03jul12,txu  fix WIND00359074: NFS API changes should be fixed
01d,29apr10,pad  Moved extern C statement after include statements.
01c,01mar10,y_t    update for LP64
01b,07sep06,mwv  update include paths
01a,10oct03,snd  written.
*/

#ifndef __INCnfsDriverh
#define __INCnfsDriverh

#include <vwModNum.h>
#include <limits.h>
#include <hostLib.h>
#include <nfs/xdr_mnt_common.h>
#include <nfs/xdr_nfs_common.h>

#ifdef __cplusplus
extern "C" {
#endif

/* globals */
typedef struct
    {

    char hostName   [MAXHOSTNAMELEN + 1];  /* Host of imported NFS     */
    char *remFileSys;                   /* Remote File System Name  */
    char *locFileSys;                   /* Local File System Name   */

    } NFS_DEV_INFO;

/* nfsDrv status codes */

#define  S_nfsDrv_INVALID_NUMBER_OF_BYTES	      (M_nfsDrv | 1)
#define  S_nfsDrv_BAD_FLAG_MODE			         (M_nfsDrv | 2)
#define  S_nfsDrv_CREATE_NO_FILE_NAME		      (M_nfsDrv | 3)
#define	S_nfsDrv_FATAL_ERR_FLUSH_INVALID_CACHE	(M_nfsDrv | 4)
#define	S_nfsDrv_WRITE_ONLY_CANNOT_READ		   (M_nfsDrv | 5)
#define	S_nfsDrv_READ_ONLY_CANNOT_WRITE		   (M_nfsDrv | 6)
#define	S_nfsDrv_NOT_AN_NFS_DEVICE		         (M_nfsDrv | 7)
#define	S_nfsDrv_NO_HOST_NAME_SPECIFIED		   (M_nfsDrv | 8)
#define	S_nfsDrv_PERMISSION_DENIED		         (M_nfsDrv | 9)
#define	S_nfsDrv_NO_SUCH_FILE_OR_DIR		      (M_nfsDrv | 10)
#define	S_nfsDrv_IS_A_DIRECTORY			         (M_nfsDrv | 11)

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

extern STATUS 	nfs2Drv (void);
extern STATUS  nfs3Drv (void);
extern int 	   nfsDrvNumGet (int version);
extern STATUS 	nfsMount (const char *host, const char *fileSystem, 
                          const char *localName);
extern STATUS 	nfsMountAll (const char *host, const char *clientName,
                         BOOL quiet);
extern void 	nfsDevShow (void);
extern STATUS 	nfsUnmount (const char *localName);
extern int     nfsDevListGet (unsigned long nfsDevList [], int listSize);
extern STATUS  nfsDevInfoGet (unsigned long nfsDevHandle, 
			      NFS_DEV_INFO  * pnfsInfo);
extern STATUS  nfsMntDump (const char * hostName);
#else

extern STATUS 	nfs2Drv ();
extern STATUS  nfs3Drv ();
extern int 	   nfsDrvNumGet ();
extern STATUS 	nfsMount ();
extern STATUS 	nfsMountAll ();
extern void 	nfsDevShow ();
extern STATUS 	nfsUnmount ();
extern int     nfsDevListGet ();
extern STATUS  nfsDevInfoGet ();
extern STATUS  nfsMntDump ();

#endif	/* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCnfsDriverh */
