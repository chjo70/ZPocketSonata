/* iosLib.h - I/O system header file */

/*
 * Copyright 1984-2007, 2009-2010, 2014-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
13oct16,dlk  Remove iosInit() prototype for UMIOS.
07oct16,mca  Fixed iosInit prototype for _WRS_CONFIG_CERT
17may16,ljl  added definition of security event IDs (F3805)
08mar16,dlk  Remove unneeded vwModNum.h include.
01may15,rr   Removed iosCreat() (V7COR-2660)
19dec14,ymz  modified iosInit based for CERT
19may10,pad  Restored #endif removed by mistake.
18may10,pad  Removed unnecessary C++ inline routines.
30mar10,pad  Moved 'extern "C"' statement and applied C++ inline scheme
             for iosDrvInstall().
19jan10,pad  Removed usage of _WRS_KEEP_USING_FUNCPTR.
21apr09,hps  LP64: move drv_val_t to private header iosLibP.h
16mar09,hps  LP64 support
01aug07,act  io footprint work (from pcm)
02jun07,jon  SMP ready
09feb06,jlk  updated iosInit() prototype to take PSE52 mode parameter
19aug05,hya  added iosDevResume().
09aug05,hya  added iosDevReplace() & iosDevSuspend().
26jul05,hya  Added iosDevDelCallback().
20jun05,hya  Added NOSTATTBL mark to errno defines.
03may04,dat  adding new API iosFdDrvValue, SPR 96744
01mar04,dat  new API iosFdMaxFiles().
17feb04,dat  Separating public and private APIs
02dec03,dat  POSIX error values
07nov03,dat  adding const to arguments
31oct03,dat  new ios interfaces for FD_ENTRYs
28jul03,dat  moved DEV_HDR to ioLib.h, removed non-ANSI prototypes,
             changed args to iosDevFind to (const char *).
03oct01,dcb  Fix SPR 20033.  iosFdSet uses malloc without checking return
             code.
15jan93,wmd  added S_iosLib_INVALID_ETHERNET_ADDRESS
22sep92,rrr  added support for c++
23aug92,jcf  added iosShowInit() prototype.
             changed to use dllLib.
04jul92,jcf  cleaned up.
26may92,rrr  the tree shuffle
04oct91,rrr  passed through the ansification filter
             -changed VOID to void
             -changed copyright notice
05oct90,dnw  deleted private routines.
05oct90,shl  added ANSI function prototypes.
             made #endif ANSI style.
             added copyright notice.
10aug90,dnw  added declaration of iosFdFree().
07may90,hjb  added IMPORT declaration of iosFdDevFind().
30jun88,llk  added definition of iosNextDevGet().
04jun88,llk  removed S_iosLib_INVALID_DEVICE_NAME.
12apr88,gae  moved defn's of FD_ENTRY & DRV_ENTRY to iosLib.c.
16dec87,jlf  changed de_dummy field in DRV_ENTRY to de_inuse.
30sep87,gae  added name field to FD_ENTRY.
29apr87,dnw  added S_iosLib_CONTROLLER_NOT_PRESENT.
24dec86,gae  changed stsLib.h to vwModNum.h.
01dec86,dnw  changed DEV_HDR.name to be ptr to name instead array of name.
07aug84,ecs  added status codes and include of stsLib.h
08jun84,dnw  written
*/

#ifndef __INCiosLibh
#define __INCiosLibh

#include <vxWorks.h>
#include <ioLib.h>
#include <dllLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* security event ID */
#define SEC_EVENT_IOS_FDRESERVE_FAILED      (M_iosLib | 1)

/* status codes
 *
 * NOSTATTBL mark at end will exclude those errno definitions from being
 * included into statSymTbl, which may hide generic errno strings by
 * those IO specifics in printErrno, etc.
 */

#define S_iosLib_DEVICE_NOT_FOUND           ENODEV  /* NOSTATTBL */
#define S_iosLib_DRIVER_GLUT                ENOMEM  /* NOSTATTBL */
#define S_iosLib_INVALID_FILE_DESCRIPTOR    EBADF   /* NOSTATTBL */
#define S_iosLib_TOO_MANY_OPEN_FILES        EMFILE  /* NOSTATTBL */
#define S_iosLib_CONTROLLER_NOT_PRESENT     ENXIO   /* NOSTATTBL */
#define S_iosLib_DUPLICATE_DEVICE_NAME      EINVAL  /* NOSTATTBL */
#define S_iosLib_INVALID_ETHERNET_ADDRESS   EINVAL  /* NOSTATTBL */

/* PUBLIC function declarations */

#ifdef _WRS_KERNEL
extern STATUS   iosInit (int max_drivers, int max_files,
#ifdef _WRS_CONFIG_CERT
                         int max_io_concurrent,
#endif
                         const char * nullDevName);
#endif /* _WRS_KERNEL */

extern void     iosPathLibInit (void);
extern STATUS   iosRmvLibInit (void);
extern STATUS   iosPxLibInit (BOOL pseMode);
extern void     iosRtpLibInit (void);
extern void     iosShowInit (void);
extern int      iosDrvInstall (DRV_CREATE_PTR   pCreate,
                               DRV_REMOVE_PTR   pRemove,
                               DRV_OPEN_PTR     pOpen,
                               DRV_CLOSE_PTR    pClose,
                               DRV_READ_PTR     pRead,
                               DRV_WRITE_PTR    pWrite,
                               DRV_IOCTL_PTR    pIoctl);
extern STATUS   iosDrvRemove (int drvnum, BOOL forceClose);
extern void     iosDrvShow (void);
extern STATUS   iosDevAdd (DEV_HDR * pDevHdr, const char * name, int drvnum);
extern STATUS   iosDevReplace (DEV_HDR * pDevHdr,
                               const char * name, int drvnum);
extern STATUS   iosDevReplaceExt (DEV_HDR * pDevHdr,
                                  const char * name, int drvnum);
extern STATUS   iosDevSuspend (DEV_HDR * pDevHdr);
extern STATUS   iosDevResume (DEV_HDR * pDevHdr);
extern int      iosDevDelete (DEV_HDR * pDevHdr);
extern int      iosDevDelDrv (DEV_HDR * pDevHdr);
extern STATUS   iosDevDelCallback (DEV_HDR * pDevHdr, FUNCPTR pCallback);
extern void     iosDevShow (void);
extern void     iosFdShow (void);
extern DEV_HDR *iosFdDevFind (int fd);
extern void     iosFdFree (int fd);
extern size_t   iosFdMaxFiles (void);
extern DEV_HDR *iosDevFind (const char * name, const char ** pNameTail);
extern DEV_HDR *iosNextDevGet (DEV_HDR * pDev);
extern STATUS   iosLock(void);
extern STATUS   iosUnlock(void);

/* PRIVATE function declarations */

#ifndef __INCiosLibPh

extern void *   iosOpen (DEV_HDR * pDevHdr, const char * fileName,
                         int flags, int mode)
       _WRS_DEPRECATED("not a public API");
extern int      iosDelete (DEV_HDR * pDevHdr, const char * fileName)
       _WRS_DEPRECATED("not a public API");
extern int      iosClose (int fd)
       _WRS_DEPRECATED("not a public API");
extern ssize_t  iosRead (int fd, char * buffer, size_t maxbytes)
       _WRS_DEPRECATED("not a public API");
extern ssize_t  iosWrite (int fd, const char * buffer, size_t nbytes)
       _WRS_DEPRECATED("not a public API");
extern int      iosIoctl (int fd, int function, _Vx_usr_arg_t arg)
       _WRS_DEPRECATED("not a public API");

#endif /* __INCiosLibPh */

#ifdef __cplusplus
}
#endif

#endif /* __INCiosLibh */
