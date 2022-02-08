/* fsMagic.h - File System Magic Number Define Header */

/*
 * Copyright (c) 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
27jul17,ghs  created (F9150)

*/

#ifndef __INCfsMagich
#define __INCfsMagich

#ifdef __cplusplus
extern "C" {
#endif

#define CDROMFS_NAME    "CD-ROM File System"
#define VDFS_NAME       "Virtual Disk File System"
#define RAWFS_NAME      "Raw File System"
#define DOSFS_NAME      "MS-DOS Compatible File System"
#define ROMFS_NAME      "Read-Only Memory File System"
#define VRFS_NAME       "Virtual Root File System"
#define NFSV2_NAME      "Network File System (Version 2)"
#define NFSV3_NAME      "Network File System (Version 3)"
#define HRFS_NAME       "Highly Reliable File System"

char * fsTypeToName (long ftype);

int deviceFsInfoShow (char * pDevName);

#ifdef __cplusplus
}
#endif

#endif /* __INCfsMagich */

