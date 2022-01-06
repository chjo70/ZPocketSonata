/* nfs2Lib.h - Network File System library header */

/*
 * Copyright (c) 2004 - 2006, 2010, 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
21apr15,yjl Fix V7STO-141 Request for NFS client to support FIOLINK
01h,29apr10,pad  Moved extern C statement after include statements.
01g,07sep06,mwv  update include paths
01f,20apr06,pcm  added support for chmod()
01e,22mar06,pcm  fixed SPR 119426--invalidating client cache on NFSERR_STALE
01d,15dec05,pcm  changed structure of NFS_FD and renamed to NFS2_FD
01c,23aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
01b,28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
                 /main/vdt/base6_itn5_networking-int/1)
01a,10oct03,snd  written                               
*/

#ifndef __INCnfs2Libh
#define __INCnfs2Libh

#include <vwModNum.h>
#include <dirent.h>
#include <sys/stat.h>
#include <iosLib.h>
#include <nfs/nfsCommon.h>
#include <nfs/nfsDriver.h>
#include <nfs/xdr_mnt1.h>
#include <vnode.h>
#include <private/nfs/nfsCacheLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* nfs file descriptor */

typedef struct nfs2_fd                  /* NFS2_FD - NFS file descriptor */
    {
    NFS_DEV *   nfsDev;                /* pointer to this file's NFS device */
    SEM_ID       nfsFdSem;              /* accessing semaphore */
    NFS_CACHE *  pCache;                /* NFS Cache info */
    char         curFilename[NAME_MAX + 1];/* Current file name */
    voff_t       offset;                /* number of current byte in file */
    unsigned int mode;                  /* (O_RDONLY, O_WRONLY, O_RDWR) */

    nfs_fh2      fileHandle;            /* file's file handle */
    nfs_fh2      dirHandle;             /* file's directory file handle */
    fattr        fileAttr;              /* file's attributes */
    readdirres  *dirCache;              /* cache of dir list entries */
    } NFS2_FD;

/* function declarations */

extern void     nfs2ClientClose (void);
extern STATUS   nfs2DirMount (char *hostName, dirpath dirname,
                              nfs_fh2 *pFileHandle);

extern STATUS   nfs2DirUnmount (char * hostName, dirpath dirName);
extern STATUS   nfs2DirReadOne (NFS2_FD *pFd, DIR *pDir);
extern STATUS   nfs2ExportRead (char *hostName, exports *pExports);
extern void     nfs2FileAttrGet (fattr *pFattr, struct stat *pStat);

extern STATUS   nfs2FsAttrGet (char* pHostName,nfs_fh2* pDirHandle,
                               struct statfs* pArg );

extern int     nfs2FileRead (NFS2_FD * pNfsFd, voff_t offset,
                             unsigned int count, char *buf);

extern STATUS  nfs2FileRemove (char *hostName, nfs_fh2 *pMountHandle,
                               char *fullFileName);

extern int     nfs2FileWrite (NFS2_FD * pNfsFd, voff_t offset,
                              unsigned int count, char * data);
extern int     nfs2LookUpByName (char *hostName, char *fileName,
                                 nfs_fh2 *pMountHandle, diropres *pDirOpRes,
                                 nfs_fh2 *pDirHandle, BOOL removeFlag);
extern int     nfs2ThingCreate (char *hostName, char *fullFileName,
                                nfs_fh2 *pMountHandle, diropres *pDirOpRes,
                                nfs_fh2 *pDirHandle, u_int mode);
extern STATUS   nfs2MntUnmountAll (char *hostName);

extern STATUS   nfs2Rename (NFS2_FD * pNfsFd, char * newName);

extern STATUS   nfs2DevInfoGet (unsigned long nfsDevHandle, 
                                NFS_DEV_INFO * pnfsInfo);

extern STATUS   nfs2MntDump (char * hostName);
extern STATUS   nfs2ExportRead (char * hostName, exports * pExports);

extern STATUS   nfs2RpcAttrGet (char *  pHostName, nfs_fh2 *  pHandle,
                                fattr *  pAttr);
extern STATUS   nfs2RpcAttrSet (char *  pHostName, nfs_fh2 *  pHandle,
                                sattr *  pAttr);

extern STATUS   nfs2Link (NFS2_FD * pNfsFd, char * linkName);

#ifdef __cplusplus
}
#endif

#endif /* __INCnfs2Libh */
