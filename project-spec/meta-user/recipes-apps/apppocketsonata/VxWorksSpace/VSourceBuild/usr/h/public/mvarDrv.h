/* mvarDrv.h - header for MVar test I/O system driver */

/*
 * Copyright (c) 2003-2007, 2010, 2013-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
22mar16,dlk  Written.
*/

#include <vsbConfig.h>
#include <sys/ioctl.h>

#ifndef __INCmvarDrvh
#define __INCmvarDrvh

#ifdef __cplusplus
extern "C" {
#endif

extern STATUS  mvarDevCreate (const char * devName, size_t maxFiles);
extern STATUS  mvarDrv (void);

#ifdef __cplusplus
}
#endif

#endif /* __INCmvarDrvh */

