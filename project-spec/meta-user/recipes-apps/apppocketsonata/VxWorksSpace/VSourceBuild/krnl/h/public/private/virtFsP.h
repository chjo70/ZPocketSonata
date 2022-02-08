/* virtFsP.h - private header file for virtual file system driver */

/*
 * Copyright (c) 2014-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
27may16,dlk  Driver write routine now takes a const void * buffer.
15jul15,rpc  PPC64 Compiler warning reduction
14may14,h_k  created. (US35006)
*/

#ifndef __INCvirtFsPh
#define __INCvirtFsPh

#ifdef __cplusplus
extern "C" {
#endif

#include <ioLib.h>		/* for DEV_HDR */

typedef struct virtfs_funcs
    {
    STATUS  (*createRtn) (void ** cookie);
    STATUS  (*deleteRtn) (dev_t dev, ino_t inode, void * cookie);
    STATUS  (*openRtn) (void * cookie, int flags);
    STATUS  (*closeRtn) (void * cookie, int flags);
    ssize_t (*readRtn) (void * cookie, void * buffer, size_t bytes, int flags);
    ssize_t (*writeRtn) (void * cookie, const void * buffer, size_t bytes, int flags);
    STATUS  (*ioctlRtn) (void * cookie, int func, _Vx_usr_arg_t arg);
    STATUS  (*truncateRtn) (void * cookie, size_t size);
    STATUS  (*pathConfRtn) (void * cookie, long name, long * pRetVal);
    int     (*setflRtn) (void * cookie, int flags);
    } VIRTFS_FUNCS;

extern STATUS virtFsDrv (const char * devName, VIRTFS_FUNCS * pFuncs,
			 unsigned int type, DEV_HDR ** ppHdr);
extern struct virtfs_obj * virtFsObjCreate (DEV_HDR * pVdHdr, int mode);
extern struct virtfs_fd * virtFsObjOpen (DEV_HDR * pVdHdr,
					 struct virtfs_obj * pObj, int flags);
extern STATUS virtFsObjClose (DEV_HDR * pVdHdr, struct virtfs_fd * pFD);
extern STATUS virtFsObjDelete (DEV_HDR * pVdHdr, struct virtfs_obj * pObj);

#ifdef __cplusplus
}
#endif

#endif /* __INCvirtFsPh */
