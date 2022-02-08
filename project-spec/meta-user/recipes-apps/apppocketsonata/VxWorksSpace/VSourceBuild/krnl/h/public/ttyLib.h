/* ttyLib.h - header file for terminal drivers on top of sio core drivers */

/*
 * Copyright (c) 1995, 2004, 2009, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */


/*
modification history
--------------------
06jan14,l_z  Add ttyDevDelete()
01e,20mar09,lyc  LP64 support
01d,05may04,dat  fix ttyDrv declaration, 96824
01c,15jun95,ms   updated for new serial driver.
01b,22may95,ms   removed unneded include file.
01a,21feb95,ms   written.
*/

#ifndef __INCttyLibh
#define __INCttyLibh

#include "types/vxTypes.h"
#include "sioLib.h"

#ifdef __cplusplus
extern "C" {
#endif

extern STATUS ttyDrv (void);
extern STATUS ttyDevCreate (char * name, SIO_CHAN * pChan,
                            int rdBufSize, int wrtBufSize);
extern STATUS ttyDevDelete ( char *      name);

#ifdef __cplusplus
}
#endif

#endif  /* __INCttyLibh */

