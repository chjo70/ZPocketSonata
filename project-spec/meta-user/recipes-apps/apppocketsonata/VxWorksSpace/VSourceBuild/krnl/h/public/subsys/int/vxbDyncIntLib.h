/* vxbDyncIntLib.h - VxBus dynamic interrupt library header file */

/*
 * Copyright (c) 2013-2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
22apr14 b_m  remove useless members in VXB_DYNC_INT_ENTRY. (US37630)
17jul13,l_z  Created
*/

#ifndef _INC_vxbDyncIntLibH
#define _INC_vxbDyncIntLibH

#ifdef __cplusplus
extern "C" {
#endif

typedef struct vxbDyncIntEntry {
    UINT32 lVec;
    UINT32 hVec;
    UINT64 vecAddr;
    UINT32 vecVal;
} VXB_DYNC_INT_ENTRY;

#define VXB_DYNAMIC_INT_CTRL_MAX   8

IMPORT int (*_func_dyncIntAlloc)(UINT32 count, VXB_DYNC_INT_ENTRY *);
IMPORT void (*_func_dyncIntFree)(UINT32 count, VXB_DYNC_INT_ENTRY *);
IMPORT STATUS vxbDyncIntRegister(VXB_DEV_ID pDev, UINT32 irqs, UINT32 * pBase);

#ifdef __cplusplus
}
#endif

#include <hwif/methods/vxbDyncIntMethod.h>

#endif /* _INC_vxbDyncIntLibH */


