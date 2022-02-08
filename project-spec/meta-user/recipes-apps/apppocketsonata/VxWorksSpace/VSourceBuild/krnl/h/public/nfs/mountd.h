/* mountd.h - Mount protocol library header */

/*
 * Copyright (c) 2003-2004, 2006-2007, 2008-2010, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01f,29apr10,pad  Moved extern C statement after include statements.
01e,05feb10,y_t    update for LP64
01d,07jan07,mwv  remove VIRTUAL_STACK support
01c,07sep06,mwv  update include paths
01b,21jun04,vvv  added virtual stack support
01a,22oct03,msc  written
*/

#ifndef __INCmountdh
#define __INCmountdh

#include <nfs/xdr_mnt3.h>
#include <nfs/xdr_mnt1.h>
#include <lstLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* mountLib defaults */

#define MAX_EXPORTED_FILESYSTEMS 30
#define MOUNTD_PRIORITY_DEFAULT  55
#define MOUNTD_STACKSIZE_DEFAULT 10240

/* mountLib status codes */

#define S_mountLib_ILLEGAL_MODE             (M_mountLib | 1)

/* DATA STRUCTURES */

typedef struct
    {
    char * next;           /* next and prev are used by lstLib */
    char * prev;
    char   clientName [MAXHOSTNAMELEN + 1]; /* name of the host mounting this
                                             * directory 
                                             */
    /*
     * Mounted directory. Though it appears a single character, it is a char
     * array. The array is allocated when a MOUNT_CLIENT struct is allocated.
     * This change was required for adding configurable path length support.
     */

    char   directory [1];
    } MOUNT_CLIENT;

/* Exported file systems */

typedef struct
    {
    char * next;     /* next and prev are used by lstLib */
    char * prev;
    int    dirFd;    /* File descriptor for the exported directory */
    UINT  fsId;
    int    volumeId;            /* Identifier for the file system */
    BOOL   readOnly;

    /*
     * This is a character array - memory is allocated when the struct is
     * allocated. This change was required for adding configurable path
     * length support.
     */

    char   dirName [1];
    } NFS_EXPORT_ENTRY;

/* MOUNT version 3 Argument */
typedef union
    {
    dirpath mountproc_mnt_3_arg;
    dirpath mountproc_umnt_3_arg;
    } MOUNT3D_ARGUMENT;

/* MOUNT version 1 argument */
typedef union
    {
    dirpath mountproc_mnt_1_arg;
    dirpath mountproc_umnt_1_arg;
    } MOUNTD_ARGUMENT;

/* Call back function pointers for MOUNT v1 and v3 */
typedef void (*MOUNTCALLBACK)( struct svc_req *rqstp, register SVCXPRT *transp);

/* Extern declarations */
extern  SEM_ID  clientsSem;     /* Sem controlling access to nfsClients */
extern  FUNCPTR mountdAuthHook; /* Hook to run to authorize packets */
extern  LIST *  mountPoints;    /* Linked list of exported mount points */
extern  SEM_ID  mountSem;       /* Sem controlling access to mountPoints */
extern  LIST *  nfsClients;     /* Linked list of clients mounting fs's */
extern  int     fsIdNumber;     /* ID number for exported file systems */
extern int     mountdNExports;  /* max. num. exported FS's */

extern MOUNTCALLBACK mountv1CallBack;    /* call back function for MOUNT v1 */
extern MOUNTCALLBACK mountv3CallBack;    /* call back function for MOUNT v3 */

#if defined(__STDC__) || defined(__cplusplus)

extern STATUS mountdInit (int priority, int stackSize, FUNCPTR authHook,
                          int nExports, int options);

extern void mountd (int);

extern void mountdv1RequestProcess (struct svc_req *rqstp, 
                                    register SVCXPRT *transp);
extern void mount3dRequestProcess (struct svc_req *rqstp, 
                                   register SVCXPRT *transp);
extern void mount1dRequestProcess (struct svc_req *rqstp, 
                                   register SVCXPRT *transp);

extern STATUS nfsExport (char * directory, int id, int mode, int options);
extern STATUS nfsUnexport (char * dirName);
extern NFS_EXPORT_ENTRY * nfsExportFindByName (char * dirName);
extern NFS_EXPORT_ENTRY * nfsExportFindById (int volumeId);

extern MOUNT_CLIENT * mountListFind (struct svc_req * rqstp, dirpath * path);

extern int fdToInode (int fd);
extern int nameToInode (int, char * fileName);
extern char * svc_reqToHostName (struct svc_req * rqstp, char * hostName);

#else

extern STATUS mountdInit ();
extern void mountd ();
extern void mountdv1RequestProcess ();
extern void mount3dRequestProcess  ();
extern void mount1dRequestProcess  ();
extern STATUS nfsExport ();
extern STATUS nfsUnexport ();
extern NFS_EXPORT_ENTRY * nfsExportFindByName ();
extern NFS_EXPORT_ENTRY * nfsExportFindById ();
extern MOUNT_CLIENT * mountListFind ();
extern int fdToInode ();
extern int nameToInode ();
extern char * svc_reqToHostName ();

#endif   /* __STDC__ */

#ifdef __cplusplus
}
#endif	

#endif /* __INCmountdh */
