/* vxbIadtLib.h - IADT bus library header file */

/*
 * Copyright (C) 2013-2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01may14,j_l  US37558 - Create IA configuration configlettes for
                       VxBus GEN2 drivers
29apr14,j_l  US37556 - Convert *MPT* names to *IADT*
21apr14,j_l  US35957 - Add device list processing capability
10dec13,scm  US22915/US21593 initial GEN2 IA interrupt support...
*/

#ifndef __INCvxbIadtLibh
#define __INCvxbIadtLibh

#include <vxWorks.h>

#include <hwif/vxBus.h>
#include <hwif/util/vxbResourceLib.h>
#include <usrIadt.h>

#ifdef __cplusplus
extern "C" {
#endif

BUSTYPE_DECL(vxbIadtBus);

#define VXB_BUSID_IADT              BUSTYPE_ID(vxbIadtBus)

/* struct used for matching a device */

typedef struct vxbIadtDevId {
        char    name[MAX_DRV_NAME_LEN];
        char    type[MAX_DRV_NAME_LEN];
        char    compatible[128];
        const void *data;
} VXB_IADT_DEV_ID;

/* struct to describe the IADT device */

typedef struct vxbIadtDev {
        char                name[MAX_DRV_NAME_LEN];
        void              * iadt;
        UINT32              node;
        struct vxbIadtDev * pParIadtDev;
        USR_IADT_NODE     * pDevListNode;
        int                 unit;
} VXB_IADT_DEV;

typedef struct iadtBusDevInfo {
    struct vxbIadtDev vxbIadtDev;
    VXB_RESOURCE_LIST vxbResList;
} IADT_BUS_DEV_INFO;

typedef struct IadtBusDrvCtrl {
    struct vxbIadtDev vxbIadtDev;
} IADT_BUS_DRVCTRL;

IMPORT VXB_IADT_DEV * vxbIadtDevGet(VXB_DEV_ID pDev);
IMPORT void vxbIadtDevSetup
    (
    USR_IADT_NODE * pDevListNode,
    VXB_IADT_DEV  * pIadtDev
    );
STATUS vxbIadtDevMatch
    (
    VXB_DEV_ID               pDev,           /* device to do match */
    const VXB_IADT_DEV_ID *  pMatchTbl,      /* pointer to match table */
    VXB_IADT_DEV_ID       ** pMatchedEntry   /* best matched entry */
    );

#ifdef __cplusplus
}
#endif

#include <hwif/methods/vxbIadtMethod.h>

#endif /*__INCvxbIadtLibh*/
