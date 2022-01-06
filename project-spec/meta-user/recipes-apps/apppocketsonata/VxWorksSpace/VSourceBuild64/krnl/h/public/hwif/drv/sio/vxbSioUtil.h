/* vxbSioUtil.h - VxBus SIO Channel Utilities header */

/*
 * Copyright (c) 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
19dec13,l_z  created
*/

#ifndef __INCvxbSioUtilh
#define __INCvxbSioUtilh

#include <ttyLib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define VXB_SIO_RX_BUF_SIZE             512 /* read buffer size, in bytes */
#define VXB_SIO_TX_BUF_SIZE             512 /* write buffer size, in bytes */

int vxbSioNextGet (void);

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbSioUtilh */

