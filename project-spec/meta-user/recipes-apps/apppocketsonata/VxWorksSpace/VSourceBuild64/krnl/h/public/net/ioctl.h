/* net/ioctl.h - socket ioctl header file */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
12mar14,pad  RTP-side ipnet/ipioctl.h exists only if RTP-side IPNET is enabled
             (issue VXW7-2554).
19feb14,cww  created from sys/ioctl.h
*/

#ifndef __INCnetIoctlh
#define __INCnetIoctlh

#include <sys/ioctl.h>

/* socket i/o controls */

#define	SIOCSHIWAT	_IOW('s',  0, int)		/* set high watermark */
#define	SIOCGHIWAT	_IOR('s',  1, int)		/* get high watermark */
#define	SIOCSLOWAT	_IOW('s',  2, int)		/* set low watermark */
#define	SIOCGLOWAT	_IOR('s',  3, int)		/* get low watermark */
#define	SIOCATMARK	_IOR('s',  7, int)		/* at oob mark? */
#define	SIOCSPGRP	_IOW('s',  8, int)		/* set process group */
#define	SIOCGPGRP	_IOR('s',  9, int)		/* get process group */

/* tunnel ioctl to mux layer */
#define SIOCMUXPASSTHRU	 _IOW('e', 122, MUX_PASSTHRU)

/* tunnel layer 2 ioctl to mux layer */
#define SIOCMUXL2PASSTHRU _IOW('e', 123, MUX_PASSTHRU)

/* Duplicate of END ioctl to prevent include file dependencies. */

#define SIOCGMTU _IOR('e', 26, MTU_QUERY *)  /* get mtu for PMP case */

/*
 * network stack ioctl commands are now defined in ipioctl.h which can be
 * found in $WIND_BASE/target/h/wrn/coreip/ipnet.
 */

#if defined (_WRS_CONFIG_IPNET_COREIP) || defined (_WRS_CONFIG_IPNET_USRSPACE)
#include <ipnet/ipioctl.h>
#endif

#endif /* __INCnetIoctlh */
