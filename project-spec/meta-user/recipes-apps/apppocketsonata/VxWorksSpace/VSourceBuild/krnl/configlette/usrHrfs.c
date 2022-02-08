/* usrHrfs.c - highly reliable file system library */

/*
 * Copyright 2005-2006, 2009, 2016, 2018 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
17jan18,ghs  add error handle configuration definitions (F10082)
27dec16,yjl  make priority of tHrfsCommit configurable (V7STO-758)
01jul09,hui  WIND142041 - HRFS performance improvement
01jun06,jlk  added commit policy stuff
18nov05,md   rework configlet, split close into r/o and r/w versions
03aug05,pcm  added parameters to usrHrfsInit()
27jul05,act  split commit op into start+end ops
23jul05,act  vop_readdir now takes a "struct dirent *"
06jul05,pcm  reworked initialization of hrfsOps and similar structures
20jun05,act  add rename
03jun05,pcm  added hrfsVopIoctl()
03jun05,pcm  written.
*/

/*
DESCRIPTION
*/

/* includes */

#include "vxWorks.h"

#include "fsMonitor.h"
#include "hrFsLib.h"
#include "vnode.h"
#include "private/hrFsLibP.h"

/* defines */

#ifndef HRFS_DEFAULT_COMMIT_TASK_PRIORITY
#define HRFS_DEFAULT_COMMIT_TASK_PRIORITY   2
#endif

#ifndef HRFS_DEFAULT_ERROR_HANDLE_POLICY
#define HRFS_DEFAULT_ERROR_HANDLE_POLICY    HRFS_ERR_HANDLE_STOP_IO
#endif

#ifndef HRFS_DEFAULT_ERROR_HANDLE_USER_FUNC
#define HRFS_DEFAULT_ERROR_HANDLE_USER_FUNC NULL
#endif

/* typedefs */

/* globals */

int hrfsCommitTaskPri = HRFS_DEFAULT_COMMIT_TASK_PRIORITY;

/* pointer to vnode operator tables used by HRFS */

const struct vfsops    * hrfsVfsOps     = NULL;
const struct vnode_ops * hrfsOps        = NULL;
const struct vnode_ops * hrfsDirOps     = NULL;
const struct vnode_ops * hrfsFileOps    = NULL;
const struct vnode_ops * hrfsSymLinkOps = NULL;

/* externs */

/***************************************************************************
*
* usrHrfsInit -
*/

STATUS usrHrfsInit
    (
    int  maxBufs,
    int  maxFiles,
    int  commitTskPri
    )
    {
    int  error;

#if defined(INCLUDE_HRFS)

    /* read-write version of HRFS */

    hrfsVfsOps     = &hrfsVfsOpsConfigRW;

    hrfsOps        = &hrfsOpsConfigRW;
    hrfsDirOps     = &hrfsDirOpsConfigRW;
    hrfsFileOps    = &hrfsFileOpsConfigRW;
    hrfsSymLinkOps = &hrfsSymLinkOpsConfigRW;

    hrfsWrLibInit (maxBufs, maxFiles);

#elif defined(INCLUDE_HRFS_READONLY)

    /* read-only version of HRFS */

    hrfsVfsOps     = &hrfsVfsOpsConfigRO;

    hrfsOps        = &hrfsOpsConfigRO;
    hrfsDirOps     = &hrfsDirOpsConfigRO;
    hrfsFileOps    = &hrfsFileOpsConfigRO;
    hrfsSymLinkOps = &hrfsSymLinkOpsConfigRO;

    hrfsDevLibInit (maxBufs, maxFiles);

#else

# error  Invalid HRFS configuration specified

#endif

#if defined(INCLUDE_HRFS_ACCESS_TIMESTAMP)
    hrfsAccessTimeStampEnabled = TRUE;
#endif

#if defined(INCLUDE_HRFS_HISPEED_WRITE_MODE)
    hrfsHighSpeedWriteMode = TRUE;
#endif

    hrfsUpdateErrHandlePolicy(HRFS_DEFAULT_ERROR_HANDLE_POLICY,
                              (HRFS_USER_DEF_HANDLER)HRFS_DEFAULT_ERROR_HANDLE_USER_FUNC);

    hrfsCommitTaskPri = commitTskPri;

    error = fsmProbeInstall (hrfsDiskProbe, hrfsDevCreate2);

    return ((error != OK) ? ERROR : OK);
    }

