/* nfsDebug.h - nfsDebug header */

/*
 * Copyright (c) 2013, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
26apr15, lyj Fix V7STO-141 Request for NFS client to support FIOLINK
13jan24, lyj written
*/

#ifndef __INCnfsDebugh
#define __INCnfsDebugh

#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Defines */

#define NFS_MOD_VERSION_2         0x01
#define NFS_MOD_VERSION_3         0x02
#define NFS_MOD_VERSION_ALL       0x04
#define NFS_MOD_VERSION_MASK      0x07

#define NFS_MOD_CLIENT_CACHE      0x01  /* nfsCommon.c */
#define NFS_MOD_CLIENT_COMMON     0x02  /* nfsCommon.c */
#define NFS_MOD_CLIENT_DRV_V2     0x03  /* nfs2Drv.c */
#define NFS_MOD_CLIENT_DRV_V3     0x04  /* nfs3Drv.c */
#define NFS_MOD_CLIENT_LIB_V2     0x05  /* nfs2Lib.c */
#define NFS_MOD_CLIENT_LIB_V3     0x06  /* nfs3Lib.c */

#define NFS_MOD_SERVER_CACHE      0x07  /* nfsHash.c */
#define NFS_MOD_SERVER_DEAMON     0x08  /* nfsd.c  */
#define NFS_MOD_SERVER_COMMON     0x09  /* nfsdCommon.c  */
#define NFS_MOD_SERVER_LIB_V2     0x0a /* nfs2dLib.c */
#define NFS_MOD_SERVER_LIB_V3     0x0b /* nfs3dLib.c */


#define NFS_MOD_MOUNT_DEAMON      0x0c /* mountd.c */
#define NFS_MOD_MOUNT_LIB_V2      0x0d /* mount1Lib.c */
#define NFS_MOD_MOUNT_LIB_V3      0x0e  /*  mount3Lib.c  */

#define NFS_NONE_DEBUG            0   /* Show NONE msgs       */
#define NFS_ERROR_DEBUG           1   /* Show ERROR msgs      */
#define NFS_WARNING_DEBUG         2   /* Show WARNING msgs    */
#define NFS_NORMAL_DEBUG          3   /* Show NORMAL msgs     */
#define NFS_VERBOSE_DEBUG         4   /* Show VERBOSE msgs    */


#if 0
#define NFS_LOG_FD    ioStdFd[2]
#else
#define NFS_LOG_FD  2
#endif


IMPORT int nfsDebugLevel;
IMPORT int noFileFlag;

#define NFS_ERR( module, lvl, fd, fmt,arg1, arg2, arg3, arg4, arg5, arg6 ) \
     { \
     if( (lvl) >= NFS_ERROR_DEBUG )                 \
         { \
         if (noFileFlag)     \
             (void) fdprintf( fd, "ERR: MODULE %d, %s , " fmt,             \
                       module,  __TIME__, arg1,arg2,   \
                       arg3,arg4,arg5,arg6 );\
         else  \
             (void) fdprintf( fd, "ERR: MODULE %d, %s , %d , %s , " fmt,             \
                       module, __FILE__, __LINE__, __TIME__,arg1,arg2,   \
                       arg3,arg4,arg5,arg6 ); \
         } \
     }

#define NFS_WARN( module, lvl, fd, fmt, arg1,arg2,arg3,arg4,arg5,arg6 )       \
     {  \
     if( (lvl) >= NFS_WARNING_DEBUG )                 \
         { \
         if (noFileFlag )     \
             (void) fdprintf( fd, "WARN: MODULE %d, %s , " fmt,             \
                       module,  __TIME__, arg1,arg2,   \
                       arg3,arg4,arg5,arg6 );\
         else  \
             (void) fdprintf( fd, "WARN: MODULE %d, %s , %d , %s , " fmt,             \
                       module, __FILE__, __LINE__, __TIME__,arg1,arg2,   \
                       arg3,arg4,arg5,arg6 ); \
         }\
     }

#define NFS_NORM( module, lvl, fd, fmt, arg1,arg2,arg3,arg4,arg5,arg6)       \
     { \
     if( (lvl) >= NFS_NORMAL_DEBUG )                 \
         { \
         if (noFileFlag )     \
             (void) fdprintf( fd, "NORM: MODULE %d, %s , " fmt,             \
                       module,  __TIME__, arg1,arg2,   \
                       arg3,arg4,arg5,arg6 );\
         else  \
             (void) fdprintf( fd, "NORM: MODULE %d, %s , %d , %s , " fmt,             \
                       module, __FILE__, __LINE__, __TIME__,arg1,arg2,   \
                       arg3,arg4,arg5,arg6 ); \
         }  \
    }

#define NFS_VERB( module, lvl, fd, fmt, arg1,arg2,arg3,arg4,arg5,arg6 )       \
     { \
     if( (lvl) >= NFS_VERBOSE_DEBUG )                 \
         {\
         if (noFileFlag )     \
             (void) fdprintf( fd, "VERB: MODULE %d, %s , " fmt,             \
                       module,  __TIME__, arg1,arg2,   \
                       arg3,arg4,arg5,arg6 );\
         else  \
              (void) fdprintf( fd, "VERB: MODULE %d, %s , %d , %s , " fmt,             \
                        module, __FILE__, __LINE__, __TIME__,arg1,arg2,   \
                        arg3,arg4,arg5,arg6 ); \
         } \
     }


extern void nfsDebugInit (int debugLevel);

#ifdef __cplusplus
}
#endif

#endif /* __INCnfsDebugh */

