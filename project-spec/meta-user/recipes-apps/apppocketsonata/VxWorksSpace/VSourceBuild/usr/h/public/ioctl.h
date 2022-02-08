/* ioctl.h - obsolete vxWorks 5.0 header file */

/*
 * Copyright (c) 1993, 2013, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01b,16oct13,h_k  removed ioctl.h header inclusion when ipnet socket pkg is
                 uninstalled.
01a,09feb93,rrr  written for compatibility with 5.0
*/

#ifdef  _WRS_CONFIG_SOCKET
#include <sys/ioctl.h>
#endif	/* _WRS_CONFIG_SOCKET */
