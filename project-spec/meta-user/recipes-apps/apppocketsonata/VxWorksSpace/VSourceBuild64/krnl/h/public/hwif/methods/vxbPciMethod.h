/*
 * Copyright (c) 2021 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
 *  DO NOT MODIFY THIS FILE MANUALLY
 *
 *  This file is automatically generated from
 *  the method file (extended with *.m).
 *
 */

#ifndef _INCvxbPciMethodh
#define _INCvxbPciMethodh

#ifdef __cplusplus
extern "C" {
#endif

VXB_DEVMETHOD_DECL(vxbPciCfgRead)
typedef STATUS vxbPciCfgRead_t (VXB_DEV_ID pDev,  PCI_HARDWARE * pciDev, UINT32 offset, UINT32 width, void * data);
STATUS VXB_PCI_CFG_READ (VXB_DEV_ID pDev,  PCI_HARDWARE * pciDev, UINT32 offset, UINT32 width, void * data);

VXB_DEVMETHOD_DECL(vxbPciCfgWrite)
typedef STATUS vxbPciCfgWrite_t (VXB_DEV_ID pDev,  PCI_HARDWARE * pciDev, UINT32 offset,UINT32 width, UINT32 data);
STATUS VXB_PCI_CFG_WRITE (VXB_DEV_ID pDev,  PCI_HARDWARE * pciDev, UINT32 offset,UINT32 width, UINT32 data);

VXB_DEVMETHOD_DECL(vxbPciIntAssign)
typedef STATUS vxbPciIntAssign_t (VXB_DEV_ID pDev, PCI_HARDWARE * pciDev, int pin, UINT8 * interrupt, VXB_INTR_ENTRY * pIntrEntry);
STATUS VXB_PCI_INT_ASSIGN (VXB_DEV_ID pDev, PCI_HARDWARE * pciDev, int pin, UINT8 * interrupt, VXB_INTR_ENTRY * pIntrEntry);

VXB_DEVMETHOD_DECL(vxbPcieErrRecovery)
typedef STATUS vxbPcieErrRecovery_t (VXB_DEV_ID pDev);
STATUS VXB_PCIE_ERR_RECOVERY (VXB_DEV_ID pDev);

VXB_DEVMETHOD_DECL(vxbPcieLinkReset)
typedef STATUS vxbPcieLinkReset_t (VXB_DEV_ID pDev);
STATUS VXB_PCIE_LINK_RESET (VXB_DEV_ID pDev);

#ifdef __cplusplus
}
#endif

#endif /* _INCvxbPciMethodh */

