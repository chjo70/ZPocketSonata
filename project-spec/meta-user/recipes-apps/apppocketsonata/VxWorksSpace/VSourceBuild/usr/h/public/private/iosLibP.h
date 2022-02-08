/* iosLibP.h - private I/O system header file */

/*
 * Copyright (c) 2015-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
13oct16,dlk  Adding CERT memory pool functions & macros.
07jul16,dlk  Declare fcntl_dup().
06jul16,dlk  Introduce FIOKERNFDVAL ioctl for UMIOS drivers managing
             kernel-level pass-through file descriptors (sockLib and iosKfdLib),
             providing the way to encode a duplicated kernel-level file
             descriptor as a driver value.
01jul16,dlk  _FKERN flag identifies kernel-level files.
             Add iosKfdNew();
29jun16,dlk  Renaming iosFdReserveFd() as iosFdClaim().
             Remove <flags> argument from iosFdEntrySet().
             Rename _umiosfd() as _umiosFdGet() and remove its argument.
04jun16,dlk  UMIOS RTP file descriptor inheritance.
             Also, replace FD_ENTRY_LINK/UNLINK with inline functions
             iosFdEntryAddRef()/iosFdEntryReleaseRef().
             Added declarations of iosFdDrvValue() and iosFdValueDrvNum().
13apr16,dlk  Do not allow device matches against a partial path component.
             Change signature of iosDevMatchEx() to be more directly useful.
30mar16,dlk  Add UIOS_DEV_PREFIX_MAXSIZE;
12mar16,dlk  Fix build warnings.
11aug15,zl   created based on kernel version of iosLibP.h
*/

#ifndef __INCiosLibPh
#define __INCiosLibPh


#include <vxWorks.h>
#include <iosLib.h>
#include <dllLib.h>
#include <errnoLib.h>
#include <private/semLibP.h>
#ifdef _WRS_KERNEL
#include <taskLib.h>		/* taskIdCurrent */
#include <private/rtpLibP.h>	/* WIND_RTP */
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct drvEntry         /* DRV_ENTRY - entries in driver jump table */
    {
    DRV_REMOVE_PTR      de_delete;
    DRV_OPEN_PTR        de_open;
    DRV_CLOSE_PTR       de_close;
    DRV_READ_PTR        de_read;
    DRV_WRITE_PTR       de_write;
    DRV_IOCTL_PTR       de_ioctl;
    BOOL                de_inuse;
    } DRV_ENTRY;

/* DEV_HDR structure is in ioLib.h */

typedef struct fdObjEntry       /* FD_ENTRY - entries in file table */
    {
    char *      name;
    DEV_HDR *   pDevHdr;        /* device header for this file */
    void *      value;          /* driver open file cookie, maybe reloaded */
    void *      driverCookie;   /* driver open file cookie */
    atomic_t    refCnt;         /* reference count */
    int         flags;          /* fd flags */
#define _FKERN ((int)0x80000000)   /* Identifies a kernel-level (pass-through) file */

    DRV_ENTRY * pDrvEntry;      /* dev driver, remove support, invalidated fd drv */
    } FD_ENTRY;

typedef struct fdTable
    {
    FD_ENTRY ** pEntryTbl;
    size_t	tableSize;
    SEMAPHORE   sem;
    } FD_TABLE;

/*
 * The argument to the FIOKERNFDVAL ioctl, supported by UMIOS drivers that
 * handle kernel-level pass-through file descriptors, points to a
 * struct fioKernFdValue_s.
 */

struct fioKernFdValue_s
    {
    int    kernFd;   /* IN: (duplicate) kernel-level pass-through FD */
    void * fdValue;  /* OUT: corresponding driver file value */
    };

/* macros */

/*
 * The maximum length of the path prefix identifying a user-mode I/O system path.
 * Includes the terminating NUL character.
 */
#define UIOS_PATH_PREFIX_MAXSIZE   16

/* values for driver to return */
#define DRV_VAL_OK          ((void *) 0)
#define DRV_VAL_ERROR       ((void *) -1)

#define FD_RESERVED ((FD_ENTRY *) -1)
#define FD_CNTRL    ((FD_ENTRY *) -2)
#define FD_ENTRY_VALID(pFd) \
    ((pFd) != NULL && (pFd) != FD_RESERVED && (pFd) != FD_CNTRL)

_WRS_INLINE void iosFdEntryAddRef
    (
    FD_ENTRY * pFd
    )
    {
    (void)vxAtomicInc (&pFd->refCnt);
    }

_WRS_INLINE atomicVal_t iosFdEntryReleaseRef
    (
    FD_ENTRY * pFd
    )
    {
    return vxAtomicDec (&pFd->refCnt);
    }


#define CUR_WORK_DIR	ioDefPath


_WRS_INLINE FD_TABLE * iosFdTableGet (void)
    {
#ifdef _WRS_KERNEL
    return (taskIdCurrent->rtpId->pFdTable);
#else
    extern FD_TABLE * pIosFdTable;
    return (pIosFdTable);
#endif
    }

#ifndef  _WRS_CONFIG_CERT

#define IOS_MEM_ALLOC(nBytes)      malloc((nBytes))
#define IOS_MEM_FREE(pItem)        free((pItem))

#else

#define IOS_MEM_ALLOC(nBytes)      iosCertMemPoolAlloc((nBytes))
#define IOS_MEM_FREE(pItem)        iosCertMemPoolFree((pItem))

#endif /* !_WRS_CONFIG_CERT */


/* variable declarations */

extern DL_LIST 		iosDvList;
extern DRV_ENTRY *	drvTable;
extern int 		iosMaxDrivers;
extern int 		iosMaxFiles;
extern char             uiosPathPrefix [UIOS_PATH_PREFIX_MAXSIZE];

/*
 * driver entry to handle dangling fds of deleted devices.
 * This is seperated from drvTable to hide it from show routine.
 * This driver also is used to handle open, creat and remove of deleted
 * devices.
 */
extern DRV_ENTRY 	fdInvalidDrv;

/*
 * driver entry to hold default device driver read, write, ioctl and close.
 * This is used by iosDrvShow to hide those internal slot fillings and
 * avoid confusion.
 */
extern DRV_ENTRY 	defaultDrv;

extern void    iosDrvInit (DRV_ENTRY * drvTable, int nullDrvNum);

extern STATUS (*pIosDevCloseRtn) (DEV_HDR * pDev);
extern STATUS (*pIosFdInvalidRtn) (DEV_HDR * pDev);

extern int      iosFdNew (DEV_HDR * pDevHdr, const char * name, void * value);
#ifdef _WRS_CONFIG_USER_MODE_IOS
extern int      iosFdNewEx (DEV_HDR * pDevHdr, const char * name, void * value,
                            int flags, int kernFd);
#endif
extern void *   iosFdDrvValue (int fd, int drvNum);
extern int      iosFdValueDrvNum (int fd, void ** pVal);

extern FD_ENTRY * iosFdMap (int fd);
extern DEV_HDR * iosDevMatch (const char * name);
extern DEV_HDR * iosDevMatchEx ( const char * name, const char ** pTail);
extern FD_ENTRY * iosFdEntryGet (void);
extern STATUS iosFdEntryReturn (FD_ENTRY * pFdEntry);
extern void   iosFdEntryRelease (FD_ENTRY * pFdEntry);
extern STATUS iosFdTableLock (FD_TABLE * pFdTbl);
extern void   iosFdTableUnlock (FD_TABLE * pFdTbl);
extern STATUS iosFdEntryLink (FD_TABLE * pFdTbl, int fd, FD_ENTRY * pFdEntry);

extern FD_ENTRY * iosFdEntryUnlink (FD_TABLE * pFdTbl, int fd, int unmapFlags);
extern BOOL iosDevCloseOrInvalidate (FD_TABLE * pFdTbl, DEV_HDR * pDev,
                                     BOOL forceClose);
extern STATUS iosFdEntrySet (FD_ENTRY * pFdEntry, DEV_HDR * pDevHdr,
                             const char * name, void * value);
extern int iosFdUnlink (FD_TABLE * pFdTbl, int fd, int unmapFlags);
extern int iosFdEntryIoctl (FD_ENTRY * pFdEntry, int function,
                            _Vx_ioctl_arg_t arg, BOOL syscall);
extern int iosFdClaim (FD_TABLE * pFdTbl, FD_ENTRY * pFdEntryOld,
                       FD_ENTRY * pFdEntry, int fd);
extern STATUS iosFdLibInit (void);
extern STATUS iosFdTableInit (FD_TABLE * pFdTbl);
extern FD_ENTRY * iosFdTblEntryGet (FD_TABLE * pFdTbl, int fd);
extern STATUS iosFdDup (int fromFd, int toFd);

extern STATUS iosKfdInit();
extern int iosKfdOpen (const char *name, int flags, int mode);
extern int iosKfdRemove (const char * name);
extern int iosKfdClose (void * unused);
extern int iosKfdNew (int kernFd);

extern STATUS ioPathResolve (const char *pathName, const char *pCwd,
                             DEV_HDR **  ppDevHdr, char * fullFileName);

extern void * iosOpen (DEV_HDR * pDevHdr, const char * fileName,
                       int flags, int mode);
extern int      iosDelete (DEV_HDR * pDevHdr, const char * fileName);
extern ssize_t  iosRead (int fd, char * buffer, size_t maxbytes);
extern ssize_t  iosWrite (int fd, const char * buffer, size_t nbytes);
extern int      iosIoctl (int fd, int function, _Vx_usr_arg_t arg);
extern int      iosClose (int fd);

extern int fcntl_dup (int fd, int startFd);

#ifdef _WRS_CONFIG_CERT
extern void * iosCertMemPoolAlloc (size_t nBytes);
extern STATUS iosCertMemPoolFree (void * pItem);
extern STATUS iosCertMemPoolInit (int max_files, int max_io_concurrent);
#endif /* _WRS_CONFIG_CERT */


/* system calls */

extern int _umiosFdGet (void);

#ifdef __cplusplus
}
#endif

#endif /* __INCiosLibPh */
