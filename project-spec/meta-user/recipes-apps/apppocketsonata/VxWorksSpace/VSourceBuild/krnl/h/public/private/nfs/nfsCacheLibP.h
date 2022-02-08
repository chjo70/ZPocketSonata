/* nfsCacheLibP.h - private NFS cache library */

/*
 * Copyright (c) 2005 - 2006, 2010, 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01e,31dec13,ghs  Remove useless head files (US29308)
01d,29apr10,pad  Moved extern C statement after include statements.
01c,24jan06,pcm  removed typedef of NFS_FD as it caused a gnu compile error
01b,15dec05,pcm  added support for NFS v2 cache
01a,07dec05,pcm  written.
*/

#ifndef __INCnfsCacheLibPh
#define __INCnfsCacheLibPh

/* includes */

#include <vxWorks.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define NFS_DIRTY_CACHE_LINE    0x01
#define NFS_VALID_CACHE_LINE    0x02

/* typedefs */

typedef int64_t voff_t;

typedef struct
    {
    char *     pData;
    UINT32     nBytes;
    UINT64     fileId;
    voff_t     offset;
    struct nfs_fd *   nfsFd;
    UINT32     flags;
    } NFS_CACHE_LINE;

typedef struct
    {
    NFS_CACHE_LINE *  pCacheLine;
    char *            pData;
    SEM_ID            semId;
    UINT32            flags;
    UINT32            numLines;
    UINT32            log2BytesPerLine;
    UINT32            bytesPerLine;
    } NFS_CACHE;

extern void     nfsCacheFileInvalidate (NFS_CACHE * pCache, UINT64 fileId);
extern int      nfsCacheFileFlush (struct nfs_fd *, BOOL clearNfsFd, int version);
extern int      nfsCacheLineFlush (NFS_CACHE_LINE * pCacheLine, int version);
extern STATUS   nfsCacheAlloc (NFS_CACHE * pCache, UINT32 numLines,
                               UINT32 lineLength, UINT32 options);
extern STATUS   nfsCacheFree (NFS_CACHE * pCache);
extern UINT32   nfsWhichCacheLine (NFS_CACHE * pCache, UINT64 fileId,
                                   voff_t offset);
extern int      nfsCacheLineWrite (struct nfs_fd * nfsFd, voff_t offset,
                                   char * pBuffer, int nBytes, int version);
extern int      nfsCacheLineRead (struct nfs_fd * nfsFd, voff_t offset,
                                  char * pBuffer, int nBytes, int version);

#ifdef __cplusplus
}
#endif

#endif
