/*
 * Copyright (c) 2013-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#ifndef WR_HOSTFS_SERVICE_H
#define WR_HOSTFS_SERVICE_H

#if SERVICE_WR_HostFs 
#include <tcf/framework/protocol.h>

#define DEV_ID 		"WR_HOSTFS_DEV"	/* hostfs device ID */
#define MAX_DEVID_SIZE  (sizeof(DEV_ID)+10)	/* max size for a device  ID */
#define MAX_MNT_PER_DEV 40 			/* max mount point per devive */

typedef struct HostfsEvtArgs {
    void * channel;	/* TCF channel to send the event */	
    char * name;	/* event name */
    char * id;		/* device/mount point ID */
} HostfsEvtArgs;

extern void ini_wr_hostfs_service(Protocol * proto);
extern void send_wr_hostfs_evt (void * args);

#endif /* SERVICE_WR_HostFs */
#endif /* WR_HOSTFS_SERVICE_H */
