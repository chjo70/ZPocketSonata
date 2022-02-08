/* pipeDrv.h - header file for pipeDrv.c */

/*
 * Copyright 1984-2003, 2009-2011, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
09nov17,dlk  adding pipeAnonCreate()
24jun11,jxu  defined default max number of open fds (WIND00271309).
08jun10,jxu  LP64: changed pipeDevCreate() prototype.
08jul09,lyc  LP64 support
03nov03,dat  adding const to char arguments, remove old decl's
05oct01,dcb  Fix SPR 9434.  Add pipeDevDelete() call.  Code merged back
             from the AE tree (created for AE under SPR 26204).
22sep92,rrr  added support for c++
04jul92,jcf  cleaned up.
26may92,rrr  the tree shuffle
04oct91,rrr  passed through the ansification filter
             -fixed #else and #endif
             -changed copyright notice
05oct90,shl  created.
*/

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef __INCpipeDrvh
#define __INCpipeDrvh

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

/* default maximum number of open fds for each pipe device */

#define PIPE_DEF_MAX_FDS        16

/* function declarations */

extern STATUS 	pipeDevCreate (const char *name, size_t nMessages, size_t nBytes);
extern STATUS   pipeDevDelete (const char *name, BOOL force);
extern STATUS   pipeAnonCreate (size_t nMessages, size_t nBytes,
                                unsigned flags, int * pFd);
extern STATUS 	pipeDrv (int maxOpenFds);

#ifdef __cplusplus
}
#endif

#endif /* __INCpipeDrvh */
