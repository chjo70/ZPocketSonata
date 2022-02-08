/* nfsCommon.h - nfsDrv header */

/*
 * Copyright (c) 2003-2007, 2011-2012, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
31jul17,ghs  integrate file system type magic number (F9150)
27jul12,txu  fix WIND00356753: Removal of compiling warnings
05jan12,txu  fix WIND00326552: NFS client cannot send a too large packet
31dec11,txu  fix WIND00325978: Nfsv3 client using enlarging NFS package size
             optimization will cause S_rpcLib_RPC_CANTSEND error.
07apr11,y_t  fix WIND00254003:nfs client not correctly handle jukebox error
             from server.
29apr10,pad  Moved extern C statement after include statements.
19jul07,jlk  Fixed defect WIND00099010
07sep06,mwv  update include paths
19dec05,pcm  added NFS_CACHE structure to NFS_DEV; created new structure
             NFS_FD that is identical to 1st part of both NFS2_FD & NFS3_FD
07dec05,pcm  added NFS cache to NFS3_DEV structure
26may05,mwv  SPR#109563 work around for to avoid closing socket FD from
             incorrect RTP context.
23aug04,rp   merged from COMP_WN_IPV6_BASE6_ITER5_TO_UNIFIED_PRE_MERGE
28may04,niq  Merging from base6 label POST_ITER5_FRZ16_REBASE (ver
             /main/vdt/base6_itn5_networking-int/1)
10oct03,snd  Written
*/

#ifndef __INCnfsCommonh
#define __INCnfsCommonh

#include <vwModNum.h>
#include <limits.h>
#include <hostLib.h>
#include <nfs/xdr_nfs_common.h>
#include <nfs/xdr_nfs2.h>
#include <nfs/xdr_nfs3.h>
#include <nfs/nfsDriver.h>
#include <iosLib.h>
#include <rpcLib.h>
#include <sys/socket.h>
#include <ctype.h>
#include <fioLib.h>
#include <private/nfs/nfsCacheLibP.h>
#include <vsbConfig.h>
#include <sys/stat.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#ifndef UNUSED_VAL
#define UNUSED_VAL        (-1U)
#endif

/* file status types -- from the nfs protocol spec, if these change,
   then the FSTAT values in ioLib.h should also be changed */

#define NFS_FSTAT_DIR           0040000         /* directory */
#define NFS_FSTAT_CHR           0020000         /* character special file */
#define NFS_FSTAT_BLK           0060000         /* block special file */
#define NFS_FSTAT_REG           0100000         /* regular file */
#define NFS_FSTAT_LNK           0120000         /* symbolic link file */
#define NFS_FSTAT_NON           0140000         /* named socket */

/* nfsLib status codes */

#define S_nfsLib_NFS_AUTH_UNIX_FAILED           (M_nfsLib | 1)
#define S_nfsLib_NFS_INAPPLICABLE_FILE_TYPE     (M_nfsLib | 2)

#define S_nfsLib_NFS_OK                 (M_nfsStat | (int) NFS_OK)
#define S_nfsLib_NFSERR_PERM            (M_nfsStat | (int) NFSERR_PERM)
#define S_nfsLib_NFSERR_NOENT           (M_nfsStat | (int) NFSERR_NOENT)
#define S_nfsLib_NFSERR_IO              (M_nfsStat | (int) NFSERR_IO)
#define S_nfsLib_NFSERR_NXIO            (M_nfsStat | (int) NFSERR_NXIO)
#define S_nfsLib_NFSERR_ACCESS          (M_nfsStat | (int) NFSERR_ACCESS)
#define S_nfsLib_NFSERR_EXIST           (M_nfsStat | (int) NFSERR_EXIST)
#define S_nfsLib_NFSERR_NODEV           (M_nfsStat | (int) NFSERR_NODEV)
#define S_nfsLib_NFSERR_NOTDIR          (M_nfsStat | (int) NFSERR_NOTDIR)
#define S_nfsLib_NFSERR_ISDIR           (M_nfsStat | (int) NFSERR_ISDIR)
#define S_nfsLib_NFSERR_INVAL           (M_nfsStat | (int) NFSERR_INVAL)
#define S_nfsLib_NFSERR_FBIG            (M_nfsStat | (int) NFSERR_FBIG)
#define S_nfsLib_NFSERR_NOSPC           (M_nfsStat | (int) NFSERR_NOSPC)
#define S_nfsLib_NFSERR_ROFS            (M_nfsStat | (int) NFSERR_ROFS)
#define S_nfsLib_NFSERR_NAMETOOLONG     (M_nfsStat | (int) NFSERR_NAMETOOLONG)
#define S_nfsLib_NFSERR_NOTEMPTY        (M_nfsStat | (int) NFSERR_NOTEMPTY)
#define S_nfsLib_NFSERR_DQUOT           (M_nfsStat | (int) NFSERR_DQUOT)
#define S_nfsLib_NFSERR_STALE           (M_nfsStat | (int) NFSERR_STALE)
#define S_nfsLib_NFSERR_WFLUSH          (M_nfsStat | (int) NFSERR_WFLUSH)
#define S_nfsLib_NFSERR_REMOTE          (M_nfsStat | (int) NFSERR_REMOTE)
#define S_nfsLib_NFSERR_BADHANDLE       (M_nfsStat | (int) NFSERR_BADHANDLE)
#define S_nfsLib_NFSERR_NOT_SYNC        (M_nfsStat | (int) NFSERR_NOT_SYNC)
#define S_nfsLib_NFSERR_BAD_COOKIE      (M_nfsStat | (int) NFSERR_BAD_COOKIE)
#define S_nfsLib_NFSERR_NOTSUPP         (M_nfsStat | (int) NFSERR_NOTSUPP)
#define S_nfsLib_NFSERR_TOOSMALL        (M_nfsStat | (int) NFSERR_TOOSMALL)
#define S_nfsLib_NFSERR_SERVERFAULT     (M_nfsStat | (int) NFSERR_SERVERFAULT)
#define S_nfsLib_NFSERR_BADTYPE         (M_nfsStat | (int) NFSERR_BADTYPE)
#define S_nfsLib_NFSERR_JUKEBOX         (M_nfsStat | (int) NFSERR_JUKEBOX)

/* default NFS parameters */

#define NFS_TIMEOUT_SEC         25
#define NFS_TIMEOUT_USEC        0

#ifdef _WRS_CONFIG_NFS3_BLKSIZE_FACTOR
#define NFS_SOCKOPTVAL		(_WRS_CONFIG_NFS3_BLKSIZE_FACTOR * 8800)
#else
#define NFS_SOCKOPTVAL		8800
#endif

#define NFS_REXMIT_SEC          5
#define NFS_REXMIT_USEC         0

#define NFS_RETRY_SEC           2

#define AUTH_UNIX_FIELD_LEN     50      /* UNIX authentication info */
#define MAX_GRPS                20      /* max. # of groups that user is in */

/* The max size for UDP packet payload,  63K = 64512  = 0xFC00   */
#define NFS_CLNT_UDPPKT_MAXSIZE          64512

/* Max number of versions supported for the MOUNT protocol */
#define MAX_MNT_VERSIONS 4
#define MAX_MNT_SUPPORTED_VERSIONS 2

#define WRITE_PERMISSION  2

#define NFS_CACHE_WRITE_THROUGH   0x1

/* typedefs */

typedef struct nfs_fd
    {
    void *         nfsDev;
    SEM_ID         nfsFdSem;
    NFS_CACHE *    pCache;
    char           curFilename [NAME_MAX + 1];
    voff_t         offset;
    unsigned int   mode;
    } NFS_FD;

/*
Static RPC information.
Set on initial NFS invocation and re-used during
subsequent calls on a per task basis.
*/

typedef struct moduleStatics
    {
    CLIENT *client;     /* pointer to client structure */
    int socket;         /* socket associated with this client */
    int oldprognum;     /* last program number used with this client */
    int oldversnum;     /* last version number used with this client */
    int authCount;      /* auth count this client was built with */
    int valid;          /* if TRUE, then this client information is valid */
    RTP_ID tempRtpId;   /* SPR#109563 */
    char oldhost [MAXHOSTNAMELEN + 1];
                        /* last host name that was used with this client */
    } NFS_MODULE_STATICS;

typedef struct      /* NFS_AUTH_UNIX_TYPE - UNIX authentication structure */
    {
    char machname [AUTH_UNIX_FIELD_LEN + 1];  /* host name where client is */
    int uid;                    /* client's UNIX effective uid */
    int gid;                    /* client's current group ID */
    int len;                    /* element length of aup_gids */
    int aup_gids [MAX_GRPS];    /* array of groups user is in */
    } NFS_AUTH_UNIX_TYPE ;

typedef struct                  /* NFS_DEV - nfs v2 device structure */
    {
    DEV_HDR     devHdr;                   /* nfs device header */
    char        host[MAXHOSTNAMELEN + 1];     /* host for this device */
    nfs_fh2      fileHandle;               /* handle for mounted file system */

    NFS_CACHE   nfsCache;

    /*
     * File system mounted on this dev - though it appears as a single
     * character, it is really a character array - the memory for the array
     * is allocated when an NFS_DEV struct is allocated. This change was
     * required for configurable file path length support.
     */

    char        fileSystem[1];
    } NFS_DEV;

typedef struct                  /* NFS_DEV - nfs device structure */
    {
    DEV_HDR     devHdr;                   /* nfs device header */
    char        host[MAXHOSTNAMELEN + 1];     /* host for this device */
    nfs_fh3     fileHandle;               /* handle for mounted file system */

    NFS_CACHE   nfsCache;

    /*
     * File system mounted on this dev - though it appears as a single
     * character, it is really a character array - the memory for the array
     * is allocated when an NFS_DEV struct is allocated. This change was
     * required for configurable file path length support.
     */

    char        fileSystem[1];
    } NFS3_DEV;

/* function declarations */

extern STATUS   nfsExportShow (char *hostName);
extern void     nfsAuthUnixGet (char *machname, int *pUid, int *pGid,
                                int *pNgids, int *gids);
extern void     nfsAuthUnixSet (char *machname, int uid, int gid,
                                int ngids, int *aup_gids);
extern void     nfsAuthUnixPrompt (void);
extern void     nfsAuthUnixShow (void);
extern void     nfsHelp (void);
extern void     nfsIdSet (int uid);
extern void     nfsClientClose (void);
extern STATUS   nfsDevInfoGet(unsigned long nfsDevHandle, NFS_DEV_INFO * pnfsinfo);
extern int      nfsDevListGet (unsigned long nfsDevList[], int listsize);
extern STATUS   nfsExportFree(char * pExports);
extern STATUS   nfsInit(void);
extern STATUS   nfsComponentInit(void);
extern STATUS   nfsClientCall(const char * host, u_int prognum, u_int versnum,
                u_int procnum, xdrproc_t inproc, char * in,
                xdrproc_t outproc, char * out);

extern int      nfsChkFilePerms (int nfsPerms, int ruid, int rgid, int perm);
extern void     nfsErrnoSet (enum nfsstat status);

#ifdef __cplusplus
}
#endif

#endif /* __INCnfsCommonh */
