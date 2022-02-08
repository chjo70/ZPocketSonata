/* nfs3Lib.h - Network File System library header */

/*
 * Copyright (c) 2004 - 2006, 2008, 2011-2012, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
09sep15,txu  fix V7STO-478 NFSV3 CLIENT : O_EXCL does not work in
             combination with O_CREAT
21apr15,yjl  Fix V7STO-141 Request for NFS client to support FIOLINK
14sep12,yjl  Fix WIND00376255, dosFs to be compatible with Windows FAT32
             naming rules for file/directory name length
06aug12,txu  Fix WIND00367917: NFS v3 client does not support READDIRPLUS
29jun12,txu  fix WIND00356231: UNSTABLE write is not working for the NFS 
             client with the haneWin NFS server 
21jun11,sjz  Improve NFS performance for the requirement WIND00236547.
29apr10,pad  Moved extern C statement after include statements.
09sep08,lyc  fix WIND00132892
07sep06,mwv  update include paths
18apr06,pcm  added support for chmod()
22mar06,pcm  fixed SPR 119426--invalidating client cache on NFSERR_STALE
23jan06,pcm  added nfs3StableWriteGet() and nfs3StableWriteSet()
20jan06,md   added pathconf support
19dec05,pcm  re-arranged structure of NFS3_FD
07dec05,pcm  changed structure of NFS3_FD
05nov04,vvv  added nfsCommon.h (SPR #103655)
23aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
             /main/vdt/base6_itn5_networking-int/1)
10oct03,snd  written                                      
*/

#ifndef __INCnfs3Libh
#define __INCnfs3Libh

#include <vwModNum.h>
#include <dirent.h>
#include <iosLib.h>
#include <ioLib.h>
#include <sys/stat.h>
#include <nfs/xdr_mnt3.h>
#include <nfs/xdr_nfs3.h>
#include <nfs/nfs3Defines.h>
#include <nfs/nfsCommon.h>
#include <vnode.h>
#include <private/nfs/nfsCacheLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _WRS_CONFIG_DOSFS_NAME_LENGTH_COMPAT
#define  NAME3_MAX 255
#else
#define USE_CHECK_NAMELENGTH
#ifdef USE_CHECK_NAMELENGTH
#define  NAME3_MAX 1020
#else
#define  NAME3_MAX 255
#endif
#endif

enum fattr3_st {
    NFS3ATTR_UPT = 1,  /* updated */
    NFS3ATTR_AST = 2   /* absolete */
};

/* nfs file descriptor */

typedef struct nfs3_fd              /* NFS3_FD - NFS file descriptor */
    {
    NFS3_DEV *     nfsDev;          /* Pointer to this file's NFS device */
    SEM_ID         nfsFdSem;        /* Accessing semaphore */
    NFS_CACHE *    pCache;          /* NFS Cache info */
    char           curFilename [NAME_MAX+1]; /* Current file name */    
    voff_t         offset;          /* Current offset in file */
    unsigned int   mode;            /* (O_RDONLY, O_WRONLY, O_RDWR) */

    nfs_fh3        fileHandle;      /* File's file handle */
    nfs_fh3        dirHandle;       /* File's directory file handle */
    fattr3         fileAttr;        /* File's attributes */
    cookie3 *      pdir_cookie;     /* This is the NFS3 directory cookie */
    cookieverf3    dir_cookieverf;  /* The directory entry's cookie verifier */
                                    /* Stored here because there is no space */
                                    /* in the Directory entry DIR structure */
    READDIR3res *  dirCache;        /* Cache of dir list entries */
    READDIRPLUS3res *  dirPlusCache;    /* Cache of dir plus list entries */
    enum fattr3_st fattr_st;        /* file attribute status */
    } NFS3_FD;

/* function declarations */

extern STATUS   nfs3DirMount (char * hostName, dirpath dirname,
                              nfs_fh3 * pFileHandle);

extern STATUS nfs3DirUnmount  (char * hostName, dirpath dirName);
extern STATUS nfs3ExportRead  (char * hostName, exports * pExports);
extern void   nfs3FileAttrGet (fattr3 * pFattr, struct stat * pStat);

extern STATUS nfs3FsAttrGet   (char * pHostName, nfs_fh3 * pDirHandle,
                               struct statfs * pArg);
extern STATUS nfs3FsAttrGet64 (char * pHostName, nfs_fh3 * pDirHandle,
                               struct statfs64 * pArg);

extern int    nfs3FileRead    (NFS3_FD * pNfsFd, voff_t offset,
                               unsigned int count, char * buf);
extern STATUS nfs3FileRemove  (char * hostName, nfs_fh3 * pMountHandle,
                               char * fullFileName);
extern int    nfs3FileWrite   (NFS3_FD * pNfsFd, voff_t offset,
                               unsigned int count, char * data);

extern STATUS nfs3FileCommit (NFS3_FD * pNfsFd, voff_t offset, unsigned count);

extern int    nfs3LookUpByName (char * hostName, char * fileName,
                                nfs_fh3 * pMountHandle, LOOKUP3res * pDirOpRes,
                                nfs_fh3 * pDirHandle, BOOL removeFlag);
extern int    nfs3ThingCreate  (char * hostName, char * fullFileName, 
                                nfs_fh3 * pMountHandle, CREATE3res * pDirOpRes,
                                nfs_fh3 * pDirHandle, int flags, u_int mode); 
                                 
extern STATUS nfs3DirReadOne  (NFS3_FD *pFd,DIR *  pDir);
extern STATUS nfs3DirReadPlusOne  (NFS3_FD *pFd, DIRPLUS *  pDir);

extern STATUS nfs3FsInfoGet   (char * pHostName, nfs_fh3 * pMountHandle,
                               nfsinfo * pArg);
extern STATUS nfs3Rename      (NFS3_FD * pNfsFd, char * newName);

extern STATUS nfs3Link	      (NFS3_FD * pNfsFd, char * linkName);

extern STATUS nfs3MntUnmountAll (char * hostName); 

extern STATUS nfs3MntDump       (char * hostName);

extern STATUS nfs3ExportRead    (char * hostName, exports * pExports);

extern stable_how nfs3StableWriteGet (void);
extern STATUS     nfs3StableWriteSet (stable_how howStable);

extern STATUS   nfs3PathconfGet (char * pHostName, nfs_fh3 * pDirHandle,
                                 nfs_pathconf * pArg);

extern STATUS nfs3RpcAttrGet (char * pHostName, nfs_fh3 * pHandle,
                              struct fattr3 * pAttr);
extern STATUS nfs3RpcAttrSet (char * pHostName, nfs_fh3 * pHandle,
                              sattr3 * pAttr, sattrguard3 * pGuard);

#ifdef __cplusplus
}
#endif

#endif /* __INCnfs3Libh */
