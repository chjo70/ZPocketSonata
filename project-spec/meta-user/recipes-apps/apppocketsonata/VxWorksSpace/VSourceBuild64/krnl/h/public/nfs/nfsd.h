/* nfsd.h - NFS Server Library Header */

/*
 * Copyright (c) 2003-2004, 2006-2007, 2008-2010, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01g,27jul12,txu  fix WIND00356753: Removal of compiling warnings
01f,29apr10,pad  Moved extern C statement after include statements.
01e,03feb10,y_t    update for LP64
01d,07jan07,mwv  remove VIRTUAL_STACK support
01c,07sep06,mwv  update include paths
01b,21jun04,vvv  added virtual stack support
01a,15sep03,msc  written
*/

#ifndef __INCnfsdh
#define __INCnfsdh

#include <limits.h>
#include <nfs/nfs2dLib.h>
#include <nfs/nfs3dLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Defines */
#define NFS_VERSION_2     0x01
#define NFS_VERSION_3     0x02
#define NFS_VERSION_ALL   0x00

#ifndef UNUSED_VAL
#define UNUSED_VAL       (-1U)
#endif

/* Data Structures */

/* Configuration structure for the initialization function nfsdInstInit() */

typedef struct nfsdCfgParams
    {
    CFG_DATA_HDR     cfgh;
    int              cfg_nServer;
    int              cfg_nExportedFs;
    int              cfg_priority;
    FUNCPTR          cfg_authHook;
    FUNCPTR          cfg_mountAuthHook;
    int              cfg_options;
    } NFSD_CFG_PARAMS;

/* svcudp_data is copied directly from svc_udp.c - DO NOT MODIFY */

struct svcudp_data {
        u_int   su_iosz;        /* byte size of send.recv buffer */
        u_int   su_xid;         /* transaction id */
        XDR     su_xdrs;        /* XDR handle */
        char    su_verfbody[MAX_AUTH_BYTES];    /* verifier body */
        char   *su_cache;       /* cached data, NULL if no cache - 4.0 */
};

typedef struct
    {
    int  version;
    union
       {
       NFS2D_ARGUMENT    nfs2Arg;
       NFS3D_ARGUMENT    nfs3Arg;
       }nfsArg_u;
    } NFSD_ARGUMENT;

typedef struct
    {
    FUNCPTR            routine;   /* nfsproc_*_2 routine to call */
    int                procNum;   /* NFS procedure number */
    NFSD_ARGUMENT *    argument;  /* argument to pass to nfsproc_*_2 */
    FUNCPTR            xdrArg;    /* XDR function pointer to convert argument */
    FUNCPTR            xdrResult; /* XDR function pointer to convert result */
    struct sockaddr_in sockAddr;  /* Address of the client socket */
    int                xid;       /* RPC XID of client request */
    int                socket;    /* Socket to use to send reply */
    void               *nfsCache; /* Server reply cache member */
    } NFS_Q_REQUEST;

typedef void (*NFSDCALLBACK) (struct svc_req * rqstp, SVCXPRT *transp);

/* Globals */

extern int nfsServMaxPath;
extern int nfsMaxFileName;
extern NFS2_SERVER_STATUS *pnfs2ServerStat;

extern int *pnfsdRebootTime;               /* time to be used for write verf */

#if defined(__STDC__) || defined(__cplusplus)

extern STATUS  nfsdInit (int nServers, int nExportedFs, int priority,
                         FUNCPTR nfsAuthHook, FUNCPTR mountAuthHook, 
                         int options);

extern void    nfsdRequestProcess (void);
extern void    nfsd (int);
#else

extern STATUS  nfsdInit ();
extern void    nfsdRequestProcess ();
extern void    nfsd ();

#endif  /* __STDC__ */

#ifdef __cplusplus
}
#endif

#endif /* __INCnfsdh */
