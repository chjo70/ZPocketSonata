/* vxbMiiLib.h - MII lib header file for vxBus */

/*
 * Copyright (c) 2014-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
21jun16,wap  Add missing prototype for miiBusMonitorTaskInit()
16mar16,wap  Minor cleanups, change type fields to flags fields in
             Ivars and DrvCtrl structures (F1921)
15mar16,wap  Add clause 45 support, add new bus management APIs (F1921)
05oct15,wap  Add support for user-space VxBus interface (F2165)
08jan15,sye  added vxbPhyDevMatch(). (V7PRO-1574)
14oct14,p_x  add declaration miiBusLpiModeGet(). (US47526)
08oct14,m_w  removed vxbFdtDev in PHY_HARDWARE. (V7PRO-1297)
21aug14,m_w  add vxbFdtDev in PHY_HARDWARE (V7PRO-1195)
23apr14,fao  add pMacCtrl in MII_DRV_CTRL.(US34958)
08jan14,y_y  created from miiBus.h. (US33490)
*/

#ifndef __INCvxbMiiLibH
#define __INCvxbMiiLibH

#include <hwif/vxBus.h>
#include <lstLib.h>
#include <miiLib.h>
#include <endCommon.h>
#include <endMedia.h>

#ifdef __cplusplus
extern "C" {
#endif

BUSTYPE_DECL(vxbMiiBus);

#define VXB_BUSID_MII       BUSTYPE_ID(vxbMiiBus) /* Mii class device */

/*
 * Distinguish between clause 22 and clause 45 MDIO protocol
 * interfaces. Clause 45 is used for 10 gigabit devices, while
 * clause 22 is used for 10/100/1000 devices.
 */

#define VXB_MDIO_FLAG_CLAUSE22		0x000000001
#define VXB_MDIO_FLAG_CLAUSE45		0x000000002

#define IDR2_OUILSB     0xfc00  /* OUI LSB */
#define IDR2_MODEL      0x03f0  /* vendor model */
#define IDR2_REV        0x000f  /* vendor revision */

#define MII_OUI(id1, id2)       (((id1) << 6) | ((id2) >> 10))
#define MII_MODEL(id2)          (((id2) & IDR2_MODEL) >> 4)
#define MII_REV(id2)            ((id2) & IDR2_REV)

typedef struct vxbPhyDev {
    UINT16		phyId1;
    UINT16		phyId2;
    UINT8		phyAddr;
    UINT32		phyFlags;	/* Clause 22, Clause 45, etc */
    VXB_DEV_ID		phyParent;	/* Parent MAC device */
    int			offset;
    VXB_RESOURCE_LIST	vxbResList;
} PHY_HARDWARE;

typedef struct miiDrvCtrl
    {
    NODE        miiNode;
    VXB_DEV_ID  miiSelf;
    VXB_DEV_ID  miiParent;
    VXB_DEV_ID  miiActivePhy;
    int         miiPhyCnt;
    VXB_DEV_ID  miiPhyList[32];
    BOOL        miiInitialized;
    UINT32      miiPhyAddr;
    UINT16      miiId1;
    UINT16      miiId2;
    UINT16      miiSts;
    UINT32	miiFlags;
    BOOL        miiLeaving;
    END_MEDIALIST   *miiMediaList;
    VXB_DEV_ID  pInst;
    VXB_DEV_ID  pEndInst;
    VOID *      pMacCtrl;
    } MII_DRV_CTRL;

typedef struct miiDevHook
    {
    NODE        node;
    VXB_DEV_ID  pDev;
    int         offset;
    FUNCPTR     setMiiDev;
    } MII_DEV_HOOK;

typedef struct vxbPhyDevMatchEntry {
    UINT16      miiOui;
    UINT16      miiModel;
    const void *data;
} VXB_PHY_DEV_MATCH_ENTRY;

IMPORT void miiBusLibInit (void);
IMPORT void miiBusMonitorTaskInit (void);
IMPORT STATUS miiBusMediaUpdate(VXB_DEV_ID);
IMPORT STATUS miiBusMediaAdd(VXB_DEV_ID, UINT32);
IMPORT STATUS miiBusMediaDel(VXB_DEV_ID, UINT32);
IMPORT STATUS miiBusMediaDefaultSet(VXB_DEV_ID, UINT32);
IMPORT STATUS miiBusMediaListGet(VXB_DEV_ID, END_MEDIALIST **);
IMPORT STATUS miiBusIdleErrorCheck(VXB_DEV_ID);
IMPORT void miiDevListAdd(VXB_DEV_ID);
IMPORT void miiDevListDel (VXB_DEV_ID);
IMPORT void miiBusDevInstConnect(VXB_DEV_ID pDev);
IMPORT STATUS miiBusModeGet (VXB_DEV_ID, UINT32 *, UINT32 *);
IMPORT STATUS miiBusModeSet (VXB_DEV_ID, UINT32);
IMPORT STATUS miiBusRead (VXB_DEV_ID, UINT32, UINT32, UINT16 *);
IMPORT STATUS miiBusWrite (VXB_DEV_ID, int, int, UINT16);
IMPORT STATUS miiBus45Read (VXB_DEV_ID, UINT8, UINT8, UINT16, UINT16 *);
IMPORT STATUS miiBus45Write (VXB_DEV_ID, UINT8, UINT8, UINT16, UINT16);
IMPORT STATUS miiBusLpiModeGet(VXB_DEV_ID, UINT16 *);
IMPORT STATUS vxbPhyDevMatch (VXB_DEV_ID, const VXB_PHY_DEV_MATCH_ENTRY *,
                              VXB_PHY_DEV_MATCH_ENTRY **);
IMPORT STATUS miiBusCreate (VXB_DEV_ID, UINT32);
IMPORT STATUS miiBusDelete (VXB_DEV_ID);
#ifdef __cplusplus
}
#endif

#include <hwif/methods/vxbMiiMethod.h>

#endif /* __INCvxbMiiLibH */
