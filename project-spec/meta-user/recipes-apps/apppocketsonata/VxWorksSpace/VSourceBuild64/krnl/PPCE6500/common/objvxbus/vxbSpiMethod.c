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
#include <hwif/buslib/vxbSpiLib.h>
#include <hwif/methods/vxbSpiMethod.h>

VXB_DEVMETHOD_DEF(vxbSpiXfer, "VxBus SPI xfer method");

STATUS VXB_SPI_XFER (VXB_DEV_ID pDev, SPI_HARDWARE * pChild, SPI_TRANSFER * transfer)
    {
    vxbSpiXfer_t * func = (vxbSpiXfer_t *) vxbDevMethodFind (pDev, VXB_DEVMETHOD_CALL(vxbSpiXfer));

    if (func == NULL)
        return (STATUS)ERROR;

    return func (pDev, pChild, transfer);
    }


VXB_DEVMETHOD_DEF(vxbSpiSpecGet, "VxBus SPI Master Specific Info Get method");

STATUS VXB_SPI_SPEC_GET (VXB_DEV_ID pDev, VXB_SPI_MAST_SPEC ** ppSpecialInfo)
    {
    vxbSpiSpecGet_t * func = (vxbSpiSpecGet_t *) vxbDevMethodFind (pDev, VXB_DEVMETHOD_CALL(vxbSpiSpecGet));

    if (func == NULL)
        return (STATUS)ERROR;

    return func (pDev, ppSpecialInfo);
    }


