/* 40vxbNexus.cdf - Component Definition file for the default VxBus root nexus driver */

/*
 * Copyright (c) 2015-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
16jun17,mjn  text updates (F8862)
26apr16,emj  CERT: Update to produce partially linked objects
13may15,wap  Created.
*/

Component       DRV_NEXUS_GENERIC {
    NAME        Generic VxBus root nexus
    SYNOPSIS    This component provides the default root nexus support driver. It may be \
                overridden by a platform-specific or BSP-specific driver if desired.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
    MODULES	vxbNexus.o
    LINK_SYMS	vxbRootDrv
#else
        _REQUIRES INCLUDE_KERNEL
#endif
    REQUIRES	INCLUDE_VXBUS
    INCLUDE_WHEN	INCLUDE_VXBUS
    _CHILDREN	FOLDER_DRIVERS_OTHER
}
