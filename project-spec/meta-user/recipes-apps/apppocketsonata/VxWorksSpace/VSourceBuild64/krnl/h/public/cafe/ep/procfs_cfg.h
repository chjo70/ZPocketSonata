/*
 * Copyright (c) 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#if !defined(__procfs_cfg_h)
#define __procfs_cfg_h

#ifdef __cplusplus
extern "C" {
#endif

extern int procfs_cfg_register(void);
extern void procfs_cfg_unregister(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* if !defined(__procfs_cfg_h) */
