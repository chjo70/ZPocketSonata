/* ptyDrv.h - header file for ptyDrv.c */

/*
 * Copyright (c) 1984 - 2001, 2005-2007, 2009, 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
01l,16oct13,h_k  removed ioctl.h header inclusion when ipnet socket pkg is
                 uninstalled.
                 updated PTYIOEOF to be decoupled with ipnet socket pkg.
01k,21may09,lyc  LP64 support.
01j,08jun07,jlk  Updated for SMP.
01i,22jan06,dlk  Added PTYIOEOF ioctl.
01h,19apr05,hya  added multi open support.
01g,02nov01,brk  SPR65498 add SELECT functionality to master
01f,14feb01,spm  merged from version 01f of tor2_0_x branch (base 01e):
                 added removal of pty device (SPR #28675)
01e,22sep92,rrr  added support for c++
01d,04jul92,jcf  cleaned up.
01c,26may92,rrr  the tree shuffle
01b,04oct91,rrr  passed through the ansification filter
		  -fixed #else and #endif
		  -changed copyright notice
01a,05oct90,shl created.
*/

#ifndef __INCptyDrvh
#define __INCptyDrvh

#include <tyLib.h>
#ifdef	_WRS_CONFIG_SOCKET
#include <sys/ioctl.h>
#endif	/* _WRS_CONFIG_SOCKET */

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* for PTYIOEOF ioctl */

#define PTY_EOFMASTERREAD	0x00000001
#define PTY_EOFMASTERWRITE	0x00000100
#define PTY_EOFSLAVEREAD	0x00010000
#define PTY_EOFSLAVEWRITE	0x01000000

/*
 * When one of these 'modify' bits is set, the correspondig EOF bit above
 * is significant.
 */

#define PTY_EOFMASTERREAD_MOD	0x00000002
#define PTY_EOFMASTERWRITE_MOD	0x00000200
#define PTY_EOFSLAVEREAD_MOD	0x00020000
#define PTY_EOFSLAVEWRITE_MOD	0x02000000

#define PTY_EOFMASTERREAD_SHFT	0
#define PTY_EOFMASTERWRITE_SHFT	8
#define PTY_EOFSLAVEREAD_SHFT	16
#define PTY_EOFSLAVEWRITE_SHFT	24

#define PTYIOEOF	(_TYLIB_IOC(1))

/* function declarations */

extern STATUS 	ptyDevCreate (char *name, size_t rdBufSize, size_t wrtBufSize);
extern STATUS 	ptyDevRemove (char *pName);
extern STATUS 	ptyDrv (void);


typedef struct		/* PSEUDO_DEV */
    {
    TY_DEV	tyDev;
    DEV_HDR	slaveDev;
    atomic_t	slaveNumOpen;	/* number of open paths to slave */
    SEMAPHORE	masterReadSyncSem;
    UINT8	eofMasterRead;
    UINT8	eofMasterWrite;
    UINT8	eofSlaveRead;
    UINT8	eofSlaveWrite;
    SEL_WAKEUP_LIST masterSelWakeupList;
    } PSEUDO_DEV;


#ifdef __cplusplus
}
#endif

#endif /* __INCptyDrvh */
