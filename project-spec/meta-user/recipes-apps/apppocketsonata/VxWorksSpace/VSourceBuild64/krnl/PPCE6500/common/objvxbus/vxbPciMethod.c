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

#include <vxWorks.h>
#include <hwif/vxBus.h>
#include <hwif/buslib/vxbPciLib.h>
#include <hwif/methods/vxbPciMethod.h>

VXB_DEVMETHOD_DEF(vxbPciCfgRead, "VxBus PCI Config read method");

STATUS VXB_PCI_CFG_READ (VXB_DEV_ID pDev,  PCI_HARDWARE * pciDev, UINT32 offset, UINT32 width, void * data)
    {
    vxbPciCfgRead_t * func = (vxbPciCfgRead_t *) vxbDevMethodFind (pDev, VXB_DEVMETHOD_CALL(vxbPciCfgRead));

    if (func == NULL)
        return (STATUS)ERROR;

    return func (pDev, pciDev, offset, width, data);
    }


VXB_DEVMETHOD_DEF(vxbPciCfgWrite, "VxBus PCI Config write method");

STATUS VXB_PCI_CFG_WRITE (VXB_DEV_ID pDev,  PCI_HARDWARE * pciDev, UINT32 offset,UINT32 width, UINT32 data)
    {
    vxbPciCfgWrite_t * func = (vxbPciCfgWrite_t *) vxbDevMethodFind (pDev, VXB_DEVMETHOD_CALL(vxbPciCfgWrite));

    if (func == NULL)
        return (STATUS)ERROR;

    return func (pDev, pciDev, offset, width, data);
    }


VXB_DEVMETHOD_DEF(vxbPciIntAssign, "VxBus PCI interrupt assign method");

STATUS VXB_PCI_INT_ASSIGN (VXB_DEV_ID pDev, PCI_HARDWARE * pciDev, int pin, UINT8 * interrupt, VXB_INTR_ENTRY * pIntrEntry)
    {
    vxbPciIntAssign_t * func = (vxbPciIntAssign_t *) vxbDevMethodFind (pDev, VXB_DEVMETHOD_CALL(vxbPciIntAssign));

    if (func == NULL)
        return (STATUS)ERROR;

    return func (pDev, pciDev, pin, interrupt, pIntrEntry);
    }


VXB_DEVMETHOD_DEF(vxbPcieErrRecovery, "VxBus PCI Express Error Recovery method");

STATUS VXB_PCIE_ERR_RECOVERY (VXB_DEV_ID pDev)
    {
    vxbPcieErrRecovery_t * func = (vxbPcieErrRecovery_t *) vxbDevMethodFind (pDev, VXB_DEVMETHOD_CALL(vxbPcieErrRecovery));

    if (func == NULL)
        return (STATUS)ERROR;

    return func (pDev);
    }


VXB_DEVMETHOD_DEF(vxbPcieLinkReset, "VxBus PCI Express UpStream-port Link Reset method");

STATUS VXB_PCIE_LINK_RESET (VXB_DEV_ID pDev)
    {
    vxbPcieLinkReset_t * func = (vxbPcieLinkReset_t *) vxbDevMethodFind (pDev, VXB_DEVMETHOD_CALL(vxbPcieLinkReset));

    if (func == NULL)
        return (STATUS)ERROR;

    return func (pDev);
    }

