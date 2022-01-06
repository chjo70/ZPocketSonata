/* mmanP.h - POSIX memory management library private header file */

/* 
 * Copyright (c) 2004-2006, 2009-2010, 2015 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
22dec15,gls  Added _func_signalMmanHook back for CERT
28jan15,pcs  CERT: excluded _func_signalMmanHook
23jan15,pcs  CERT: excluded mmanRtpDeleteAll().
29sep10,zl   fixed ADDR_ADD() for 64-bit
08jun10,pcs  Add macros to access BLK and RNG virtual addresses.
18may10,pcs  Updated to add support for device memory objects.
29apr10,pad  Moved extern C statement after include statements.
08apr10,jpb  Added func binding prototypes.
23feb10,zl   replaced off_t64 with off64_t
19jan10,zl   added MMAN_MM_LIST_LOCK() and UNLOCK().
16dec09,pcs  updated for LP64 support.
05may06,pcm  changed MMAP_FILE filed inode to type ino_t
21mar06,pcs  Add fileOpenPerm to struct mmap_rng.
06mar06,pcs  Implemented code review suggestions.
23jan06,zl   added size field to MMAP_FILE
01jan06,zl   changed offset to 64-bit type.
23dec05,zl   changed per-RTP file reference tracking.
16dec05,zl   changed FUNC_MSYNC parameter list.
30nov05,pcs  moved fd from struct MAP_FILE to struct MMAP_RNG.
02nov05,zl   adding file mapping support.
25oct05,zl   added FUNC_MSYNC typedef.
08jul05,zl   added FUNC_MMAP and FUNC_MUNMAP typedefs
09apr04,tam  written
*/

#ifndef __INCmmanPh
#define __INCmmanPh

/* includes */

#include <vxWorks.h>
#include <vsbConfig.h>
#include <dllLib.h>
#include <scMemVal.h>           /* for SC_PROT_ATTR */ 
#include <private/semLibP.h>    /* for SEMAPHORE    */
#include <private/rtpLibP.h>    /* for RTP_UNLOCK() */

#ifdef __cplusplus
extern "C" {
#endif


/* defines */

#ifndef _ASMLANGUAGE

#define MM_POOL_INIT_COUNT	16
#define MM_POOL_INCR_COUNT	8

#define CACHE_ATTR_USE_DEFAULT   0
#define CACHE_ATTR_USE_EXPLICIT  1
#define CACHE_ATTR_DONOT_UPDATE  2

#define ADDR_ADD(ptr,off)	((void *) ((char *) (ptr) + (ULONG) (off)))

#define MM_LIST_GET(rtpId)						\
	(&((RTP_PAGE_MGR_GET(rtpId))->mmapList))
#define MM_FBNODE_TO_BLK(pNode)					\
	((MMAP_BLK *) ((char *) (pNode) - OFFSET(MMAP_BLK, fileBlkNode)))
#define MM_RNGNODE_TO_RNG(pNode)					\
	((MMAP_RNG *) ((char *) (pNode) - OFFSET(MMAP_RNG, rtpRngNode)))
#define MM_FILENODE_TO_FILE(pNode)					\
	((MMAP_FILE *) ((char *) (pNode) - OFFSET(MMAP_FILE, fileNode)))
#define MM_FDNODE_TO_FD(pNode)					\
	((MMAP_FD *) ((char *) (pNode) - OFFSET(MMAP_FD, fileFdNode)))

#define BLK_VIRT_ADDR(rtpId, pBlock)                                       \
        (((rtpId) == kernelId) ? (pBlock)->virtAddr : (pBlock)->rtpVirtAddr)
#define BLK_K_VIRT_ADDR(pBlock) i       ((pBlock)->virtAddr)
#define BLK_RTP_VIRT_ADDR(pBlock)       ((pBlock)->rtpVirtAddr)

#define RNG_VIRT_ADDR(pRange)           ((pRange)->virtAddr)

#define MMAN_FD_LIST_LOCK()	semTake(&mmanFileMutex, WAIT_FOREVER)
#define MMAN_FD_LIST_UNLOCK()	semGive(&mmanFileMutex)

/* 
 * For real RTPs the rtpVerifyAndLock() is used. For the kernel a simple 
 * semTake() is used since the kernel, as an RTP, is never deleted. 
 * mmanRtpLock() provides this without direct dependency on RTP support.
 */

#define MMAN_MM_LIST_LOCK(rtpId)	mmanRtpLock(rtpId)
#define MMAN_MM_LIST_UNLOCK(rtpId)	RTP_UNLOCK(rtpId)

/* typedefs */

/* mapped file info */

typedef struct mmap_file
    {
    DL_NODE		fileNode;	/* node in mapped files list */
    dev_t		devId;		/* file device ID */
    ino_t               inode;		/* file inode */
    BOOL		isShm;		/* is SHM object */
    BOOL                isDevMem;       /* is DEVMEM object */
    off64_t		size;		/* file size */
    DL_LIST		fileBlkList;	/* list of mmap blocks */
    DL_LIST		fileFdList;	/* list of per-RTP file descriptors */
    } MMAP_FILE;

/* generic mapped block */

typedef struct mmap_blk
    {
    DL_NODE		fileBlkNode;	/* node in the file's block list */
    struct mmap_blk *	rngBlkNext;	/* next node in the range's block list */
    off64_t		fileOffset;	/* offset to file of mapped block */
    VIRT_ADDR           rtpVirtAddr;    /* virtual address of mapped block */
    VIRT_ADDR		virtAddr;	/* virtual address of mapped block */
    PHYS_ADDR		physAddr;	/* physical address of mapped block */
    size_t		length;		/* size of mapped block */
    int			flags;		/* map flags */
    int			refCnt;		/* nb of times the block is mapped */
    } MMAP_BLK;

/* mapped range in an RTPs map list */

typedef struct mmap_rng
    {
    DL_NODE		rtpRngNode;	/* node in the RTP's range list */
    MMAP_FILE *		pMapFile;	/* pointer to mapped file */
    void *		addr;		/* start address for range */
    size_t		len;		/* length of range */
    int			fileOpenPerm;   /* file open permission */
    int			prot;		/* protections */
    UINT 		access;		/* access of range */
    int			flags;		/* map flags */
    struct mmap_blk *	rngBlkList;	/* block list of range */
    } MMAP_RNG;

/* per-RTP file descriptor node */

typedef struct mmap_fd
    {
    DL_NODE		fileFdNode;	/* node in the mapped file's FD list */
    int			fildes;		/* file descriptor */
    RTP_ID		rtpId;		/* RTP's ID */
    } MMAP_FD;

/* hooks for mapped files support */

typedef void * (* FUNC_MMAP) (void * addr, size_t len, int prot, int flags, 
			      int fildes, off64_t off);
typedef int (* FUNC_MUNMAP) (RTP_ID rtpId, struct mmap_rng * pRange);
typedef int (* FUNC_MSYNC) (RTP_ID rtpId, void * addr, size_t len, int flags);

/* globals */

extern DL_LIST     mmanFileList;
extern SEMAPHORE   mmanFileMutex;
extern FUNC_MMAP   _func_fdMap;
extern FUNC_MUNMAP _func_fdUnmap;
extern FUNC_MSYNC  _func_fdMsync;

/* private function declarations */

extern MMAP_RNG * mmanPrivateMap (void * addr, size_t len, int prot,
				  int flags, PHYS_ADDR physAddr);
extern STATUS	  mmanMemValidate (RTP_ID rtpId, const void * addr, size_t size,
				   SC_PROT_ATTR access, STATUS * pValid);
extern STATUS	  mmanProtectionSet (RTP_ID rtpId, void * adr, size_t len,
                                     int prot, int cacheAttrToUse, 
                                     int cacheAttr);
extern MMAP_RNG * mmanRangeInsert (RTP_ID rtpId, VIRT_ADDR addr,
				   PHYS_ADDR physAddr, size_t len, 
				   int flags, int prot);
extern MMAP_BLK * mmanBlockSplit (DL_LIST *pList, MMAP_BLK * pBlock, 
                                  size_t newLen);
#ifndef _WRS_CONFIG_CERT
extern STATUS	  mmanRtpDeleteAll (RTP_ID rtpId);
#endif /* !_WRS_CONFIG_CERT */
extern STATUS	  mmanRtpLock (RTP_ID rtpId);
extern void	  mmanMapListInit (PAGE_MGR_ID pgMgrId);

/* function pointer prototypes */

extern STATUS    (*_func_signalMmanHook)(int sigNum, 
                                         int sigCode, 
                                         void * faultAddr, 
                                         int * pSigNum, 
                                         int * pSigCode);
#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCmmanPh */
