/* vnodeAffLibP.h - vnode/AFF interface private header */

/*
 * Copyright 2005, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
31jul17,ghs  integrate file system type magic number (F9150)
*/

#ifndef __INCvnodeAffLibP
#define __INCvnodeAffLibP

#include <vxWorks.h>
#include <mount.h>

#ifdef __cplusplus
extern "C" {
#endif

struct statvfs_id_map
    {
    long f_type;
    char * vfs_name;
    };

extern int vnodeAffDriverNumber;
int vn_makefiletable(struct mount *, int);
void vn_deletefiletable(struct mount *);
STATUS vnodeAffLibInit(int);

#ifdef __cplusplus
}
#endif

#endif /* __INCvnodeAffLibP */
