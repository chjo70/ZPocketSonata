/* iosLibP.h - private I/O system header file */

/*
 * Copyright (c) 1992-2011, 2014-2016, 2018 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
04jan18,dlk  Add usrFdSetFdBound() prototype (V7COR-5462)
13oct16,dlk  Remove FCNTL pool, as fcntl_dup() is now implemented without
             requiring buffer allocation.
09jul16,dlk  Fix FD_ENTRY_UNLINK usage. Use atomic ops even for UP builds.
06jul16,dlk  Adding fcntl_dup(), iosRtpFdReserveFor().
29jun16,dlk  Rename _umiosfd() as _umiosFdGet() and remove its argument.
03jun16,dlk  Add declaration for _umiosfd() function / system call.
12mar16,dlk  Make 'buffer' argument to iosWrite() be const char *.
28aug15,gws  US64063: update iosCertMemPoolAlloc(), iosFcntlMemAlloc()
01may15,rr   Removed de_create from drvEntry structure
             Removed iosCreate() (V7COR-2660)
20feb15,gls  removed iosRtpFdTableSizeGet() and iosRtpTableSizeSet()
14dec14,ymz  added _func_iosMemPoolAlloc, _func_iosMemPoolFree (CERT)
03nov14,h_k  added kernel object access control support. (F2160)
10nov14,jpb  fixed static analysis warnings
14may14,h_k  added _func_pipe2. (US35006)
26feb14,pad  Updated prototype of iosRtpFdInvalid() (side-effect of issue
             VXW7-2012).
10feb14,tlu  Added iosFdValueDrvNum()
22apr11,jxu  Added support for kernel per-task CWD feature (WIND00131452).
09nov10,jxu  Added _func_netChDirByName.
25sep10,jxu  Added _func_ioTaskStdSet, _func_ioGlobalStdGet and
	     _func_consoleOut.
31aug10,jxu  Moved IOS related hooks from funcBind.c to this file.
29apr10,pad  Moved extern C statement after include statements.
23feb10,zl   replaced off_t64 with off64_t
27jan10,lxj  added iosRtpTableSizeSet()
09nov09,lyc  remove error for merge
12jun09,lxj  WIND00161785 - remove references of setLib API from core IO
             libraries
22apr09,hps  LP64: no need drv_val_t any more
21apr09,hps  LP64: move drv_val_t to private header iosLibP.h
16mar09,hps  LP64 support
27aug08,jpb  Renamed VSB header file
24jun08,jpb  Added include path for kernel configurations options set in
             vsb.  Renamed _WRS_VX_SMP to _WRS_CONFIG_SMP.
01aug07,act  io footprint work (from pcm)
13nov06,act  SMP: per-fd refCnt uses atomics
30mar06,act  an FD_CNTRL entry should not be considered "valid"
             (FD_ENTRY_VALID macro); make iosRtpFdUnmap smarter
14feb06,md   added flags member to FD_ENTRY
07feb06,zl   added _func_ftruncateMmanHook in iosIoctlInLine()
07feb06,jlk  Added iosRtpIoTableSizeSet() and iosRtpIoTableSizeGet()
21jul05,tcr  add System Viewer instrumentation
13jul05,hya  made removability change.
13apr05,hya  removed iosFdEntryXXX call from iosXXXInLine.
01mar05,hya  change for user memory validation in ioctl
24jan05,aeg  added prototypes for iosRtpFdReserve, etc. (SPR #106381).
28apr04,dat  remove iosCloseInLine(), 96826
27feb04,dat  merging iosLib with rtpIoLib
17feb04,dat  separating public/private APIs
05jan04,dat  92873, improved test for valid FD_ENTRY
21nov03,dat  adding new refCnt macros, removing obsolete, auxValue,
             and reserved fields from FD_ENTRY.
11nov03,dat  refactored routines
27oct03,dat  Adding RTP ios support, new fields
20jun03,ymz  added iosObjIdFdGet and iosFdObjIdGet prototype.
02apr03,ymz  objectized FDs.
22dec98,lrn  add more fields to FD_ENTRY, added obsolete state
09nov93,rrr  added aio support
22sep92,rrr  added support for c++
23aug92,jcf  written.
*/

#ifndef __INCiosLibPh
#define __INCiosLibPh

#include <vsbConfig.h>
#include <private/classLibP.h>
#include <private/objLibP.h>
#include <private/kernelBaseLibP.h>
#include <iosLib.h>
#include <dllLib.h>
#include <errnoLib.h>
#include <poolLib.h>
#include <taskLib.h>            /* for taskIdCurrent */
#ifdef _WRS_CONFIG_SMP
#include <vxAtomicLib.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

typedef struct drvEntry         /* DRV_ENTRY - entries in driver jump table */
    {
    DRV_REMOVE_PTR      de_delete;
    DRV_OPEN_PTR        de_open;
    DRV_CLOSE_PTR       de_close;
    DRV_READ_PTR        de_read;
    DRV_WRITE_PTR       de_write;
    DRV_IOCTL_PTR       de_ioctl;
    DRV_IOCTL_PTR       de_ioctlMemValidate;
    BOOL                de_inuse;
    } DRV_ENTRY;

/* DEV_HDR structure is in ioLib.h */

typedef struct fdObjEntry       /* FD_ENTRY - entries in file table */
    {
    OBJ_CORE    objCore;        /* FDs are objects */
    DEV_HDR *   pDevHdr;        /* device header for this file */
    void *      value;          /* driver open file cookie, maybe reloaded */
    void *      driverCookie;   /* driver open file cookie */
    atomic32_t  refCnt;         /* reference count */
    int         flags;          /* fd flags */
    DRV_ENTRY * pDrvEntry;      /* dev driver, remove support, invalidated fd drv */
    DRV_ENTRY * pDevDrvEntry;   /* device driver entry slot pointer */
    } FD_ENTRY;

typedef void (*FTRUNC_HOOK_FUNCPTR) (int fd, off64_t off);

typedef struct devClose         /* device close arguments */
    {
    DEV_HDR *   pDevHdr;        /* device header for close */
    BOOL        forceClose;     /* indicate force close or invalidated */
    } DEV_CLOSE;

typedef struct cwdInfo          /* task's private CWD info */
    {
    char *      pCwd;           /* pointer to cwd */
    size_t      cwdLen;         /* length of cwd buffer */
    } CWD_INFO;

/* macros */

/* values for driver to return */
#define DRV_VAL_OK          ((void *) 0)
#define DRV_VAL_ERROR       ((void *) -1)

#define fdClassId     (&fdClass)
#define fdInstClassId (&fdInstClass)

#define FD_RESERVED ((FD_ENTRY *) -1)
#define FD_CNTRL    ((FD_ENTRY *) -2)
#define FD_ENTRY_VALID(pFd) \
    ((pFd) != NULL && (pFd) != FD_RESERVED && (pFd) != FD_CNTRL)

/* memory allocation routines for coreIO */

#ifndef  _WRS_CONFIG_CERT

#define IOS_KMEM_ALLOC(nBytes)      KMEM_ALLOC((nBytes))
#define IOS_KMEM_FREE(pItem)        KMEM_FREE((pItem))

#else
#define IOS_KMEM_ALLOC(nBytes)      iosCertMemPoolAlloc(nBytes)
#define IOS_KMEM_FREE(pItem)        iosCertMemPoolFree(pItem)

#endif /* !_WRS_CONFIG_CERT */


/*
 * Most aspects of file descriptors are protected by a per-RTP lock,
 * but FD_ENTRYs can be shared across separate RTPs, so we
 * must atomically adjust these reference counts.
 */

_WRS_INLINE void FD_ENTRY_LINK
    (
    FD_ENTRY * pFd
    )
    {
    (void) vxAtomic32Inc (&pFd->refCnt);
    }

_WRS_INLINE atomic32Val_t FD_ENTRY_UNLINK
    (
    FD_ENTRY * pFd
    )
    {
    return vxAtomic32Dec (&pFd->refCnt);
    }

#define iosRtpFdUnmap(pRtp, fd) iosRtpFdUnmap2(pRtp, fd, 0)

/* To obtain current working directory and check if the CWD is
 * private or global.
 */

#ifdef _WRS_CONFIG_PERTASK_CWD

#define TASK_CWD_INFO(tid)                      \
    (                                           \
    (CWD_INFO *)(((WIND_TCB *)tid)->pCwdInfo)   \
    )

#define TASK_CWD_BUF(tid)                       \
    (                                           \
    TASK_CWD_INFO(tid)->pCwd                    \
    )

#define IS_CWD_PRIVATE(tid) (TASK_CWD_INFO(tid) != NULL)

#define CUR_WORK_DIR                            \
    (                                           \
    (IS_CWD_PRIVATE(taskIdCurrent)  ?           \
        TASK_CWD_BUF(taskIdCurrent) : CUR_RTP_ID->defPath)            \
    )

#define CWD_BUF_LEN                             \
    (                                           \
    (IS_CWD_PRIVATE(taskIdCurrent)  ?           \
        TASK_CWD_INFO(taskIdCurrent)->cwdLen: CUR_RTP_ID->defPathLen) \
    )

#else /* !_WRS_CONFIG_PERTASK_CWD */

#define IS_CWD_PRIVATE(tid) (FALSE)
#define CUR_WORK_DIR     (CUR_RTP_ID->defPath)

#endif /* _WRS_CONFIG_PERTASK_CWD */

/* We use iosLock to protect CWD, before change it to other lock,
 * make sure that each reference to the global CWD are protected
 * by the lock.
 */

#define IOS_CWD_LOCK()   iosLock()
#define IOS_CWD_UNLOCK() (void) iosUnlock()

/* conditional lock/unlock, no protection is needed for accessing
 * current task's private CWD by itself.
 */

#define IOS_CWD_LOCK_COND()                  \
    do {                                     \
        if (!IS_CWD_PRIVATE(taskIdCurrent))  \
            (void) IOS_CWD_LOCK();           \
    }while (0)

#define IOS_CWD_UNLOCK_COND()                \
    do {                                     \
        if (!IS_CWD_PRIVATE(taskIdCurrent))  \
            (void) IOS_CWD_UNLOCK();         \
    }while (0)

/* variable declarations */

IMPORT OBJ_CLASS    fdClass;
IMPORT char         ioDefPath[];
IMPORT DL_LIST      iosDvList;
IMPORT int          iosMaxDrivers;
IMPORT DRV_ENTRY *  drvTable;
IMPORT int          iosMaxFiles;
IMPORT FD_ENTRY **  iosFdTable;
IMPORT POOL_ID      iosFdEntryPool;

IMPORT FTRUNC_HOOK_FUNCPTR _func_ftruncMmanHook;

/* functions that are available but not public */

IMPORT  int     iosObjIdFdGet (OBJ_ID objId);
IMPORT  OBJ_ID  iosFdObjIdGet (int fd);

/* Refactored routines to be more obj oriented these are PRIVATE */

IMPORT  int     iosKernelFdFind (void);
IMPORT  int     iosFdEntryIoctl (FD_ENTRY *, int cmd, _Vx_usr_arg_t arg, BOOL sc);
IMPORT  STATUS  iosFdEntrySet (FD_ENTRY *, DEV_HDR * pDevHdr,
                               const char * name, void * value);
IMPORT  FD_ENTRY *  iosFdEntryGet (void);
IMPORT  STATUS  iosFdEntryReturn (FD_ENTRY *);

IMPORT  STATUS  iosLock (void);
IMPORT  STATUS  iosUnlock (void);

IMPORT  STATUS  iosFdTableLock (RTP_ID pRtp);
IMPORT  void    iosFdTableUnlock (RTP_ID pRtp);

IMPORT  int     iosRtpFdReserve (RTP_ID pRtp);
IMPORT  int     iosRtpFdReserveFor (RTP_ID pRtp, int startFd, FD_ENTRY * pRsvEntry);
IMPORT  int     iosRtpFdReserveCntrl (RTP_ID pRtp);
IMPORT  int     iosRtpFdUnmap2 (RTP_ID pRtp, int fd, int flags);
IMPORT  STATUS  iosRtpFdSetup (RTP_ID pRtp, FD_ENTRY * pFdEntry, int  fd,
                               DEV_HDR * pDevHdr, const char * name, void * value);
IMPORT  STATUS  iosRtpDefPathSet (RTP_ID pRtp, const char * pBuff);
IMPORT  STATUS  iosRtpDefPathGet (RTP_ID pRtp, char * pBuff, size_t length);
IMPORT  STATUS  iosRtpFdEntryMap (RTP_ID pRtp, int fd, FD_ENTRY * pFdEntry);

#ifdef _WRS_CONFIG_PERTASK_CWD
IMPORT  STATUS  iosTaskCwdGet (TASK_ID taskId, char *pBuff, size_t length);
IMPORT  STATUS  iosTaskCwdSet (TASK_ID taskId, const char *pBuff);
#endif /* _WRS_CONFIG_PERTASK_CWD */

IMPORT  void    iosDrvInit (DRV_ENTRY * drvTable, int nullDrvNum);

/* Routines that used to be in iosLib.h, now 'private' */

extern int      iosFdNew (DEV_HDR * pDevHdr, const char * name, void * value);
extern void *   iosFdDrvValue (int fd, int drvNum);
extern int      iosFdValueDrvNum (int fd, void ** pVal);

IMPORT void *   iosOpen (DEV_HDR * pDevHdr, const char * fileName,
                         int flags, int mode);
IMPORT int      iosDelete (DEV_HDR * pDevHdr, const char * fileName);
IMPORT int      iosClose (int fd);
IMPORT ssize_t  iosRead (int fd, char * buffer, size_t maxbytes);
IMPORT ssize_t  iosWrite (int fd, const char * buffer, size_t nbytes);
IMPORT int      iosIoctl (int fd, int function, _Vx_usr_arg_t arg);
IMPORT int      iosIoctlInternal (int fd, int function,
                                  _Vx_usr_arg_t arg, BOOL syscall);

IMPORT STATUS   iosFdSet (int fd, DEV_HDR * pDevHdr, const char * name, void * value);

IMPORT FD_ENTRY *   iosFdMap (int fd);
extern BOOL     iosRtpDevCloseOrInvalidate (RTP_ID pRtp, DEV_CLOSE * pDevClose);
extern STATUS   iosDrvIoctlMemValSet (int drvnum, DRV_IOCTL_PTR pIoctlMemVal);
extern int      iosDrvIoctl (int drvNum, int function, _Vx_usr_arg_t arg);
extern size_t   iosRtpIoTableSizeGet (RTP_ID pRtp);
extern STATUS   iosRtpIoTableSizeSet (RTP_ID pRtp, size_t newSize);

extern STATUS   ioDefPathValidate (const char * pBuff);

extern STATUS   iosRtpFdInvalid (RTP_ID pRtp, DEV_HDR *pDev);
extern void *   iosFdValue (int fd)
        _WRS_DEPRECATED("use iosFdDrvValue instead");

extern DEV_HDR * iosDevMatch (const char * name);
extern int      _umiosFdGet (void);
extern int      fcntl_dup (int fd, int startFd);
extern int      iosDriverClose (FD_ENTRY * pFdEntry);

/* usrFdSetFdBound() is defined in the configlette usrIo.c */
extern size_t   usrFdSetFdBound (void);

/* APIs that no longer exist */

IMPORT VOIDFUNCPTR  iosFdNewHookRtn _WRS_DEPRECATED("no longer exists");
IMPORT VOIDFUNCPTR  iosFdFreeHookRtn _WRS_DEPRECATED("no longer exists");

/* Hooks for IO subsystem */

extern size_t (*_func_iosRtpIoTableSizeGet)	(RTP_ID pRtp);

extern STATUS (*_func_iosRtpIoTableSizeSet)	(RTP_ID pRtp, size_t newSize);

extern STATUS (*_func_ioTaskStdSet)	(TASK_ID taskId, int stdFd,
					 int newFd);

extern int	(*_func_ioGlobalStdGet)	(int stdFd);

extern ssize_t	(*_func_consoleOut)	(int fd, const char* buf, size_t len);

extern STATUS (* _func_netChDirByName) (const char* dirName);

#ifdef _WRS_CONFIG_CERT
extern void * iosCertMemPoolAlloc (size_t nBytes);
extern STATUS iosCertMemPoolFree (void * pItem);

extern STATUS iosCertMemPoolInit (int max_files, int max_io_concurrent);
extern STATUS dirCertMemPoolInit (int max_files);
#endif /* _WRS_CONFIG_CERT */

#ifdef  _WRS_CONFIG_CORE_SAFETY
extern STATUS (*_func_objAccessCtrlIoVerify) (char * pName,
					      const char * pDevName, int flags);
#endif  /* _WRS_CONFIG_CORE_SAFETY */

/* Hook for POSIX pipe */

extern int (* _func_pipe2) (int fildes[2], int flags);



#ifdef __cplusplus
}
#endif

#endif /* __INCiosLibPh */
