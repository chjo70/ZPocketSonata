/* vxbRtpLib.h - VxBus user-mode subsystem header file */

/*
 * Copyright (c) 2015, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
07jul16,wap  Add conditionals for _WRS_CONFIG_VXBUS_BASIC (when built
             in basic mode, devices can be borrowed but not returned)
12apr16,wap  Add node key and parent key
06oct15,wap  Correct C++ protection
05oct15,wap  Update prototype for vxbRtpDevRelease()
02oct15,wap  Created
*/

#ifndef __INCvxbRtpLibh
#define __INCvxbRtpLibh

#ifdef __cplusplus
extern "C" {
#endif

#include <hwif/util/vxbResourceLib.h>
#include <hwif/vxbus/vxbIoctlLib.h>
#include <hwif/vxbus/vxbRtpIoctlLib.h>

typedef struct vxbRtpNexusIvars
    {
    VXB_KEY		vxbNodeKey;
    VXB_KEY		vxbParentKey;
    int                 vxbDevFd;
    VXB_RESOURCE_LIST   vxbResList;
    char                vxbPath[PATH_MAX];
    } VXB_RTP_NEXUS_IVARS;

/*
 * Amount of uncached memory to allocate for an RTP
 * that uses VxBus.
 */

#define VXB_DMABUF_UNCACHED_MEM (65536 * 16)

/*
 * Amount of bounce-buffer memory that an RTP uses.
 */

#define VXB_DMABUF_BOUNCE_MEM 65536

/* Application-side helper functions */

IMPORT int vxbRtpDevFd;

IMPORT STATUS vxbRtpLibInit (void);
IMPORT STATUS vxbRtpDevAcquire (char * pName, UINT32 unit);
#ifndef _WRS_CONFIG_VXBUS_BASIC
IMPORT STATUS vxbRtpDevRelease (char * pName, UINT32 unit);
#endif /* _WRS_CONFIG_VXBUS_BASIC */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbRtpLibh */
