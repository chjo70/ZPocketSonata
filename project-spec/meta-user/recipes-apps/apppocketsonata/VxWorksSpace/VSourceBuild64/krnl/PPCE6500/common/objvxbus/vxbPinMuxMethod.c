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
#include <hwif/vxbus/vxbLib.h>
#include <subsys/pinmux/vxbPinMuxLib.h>
#include <hwif/methods/vxbPinMuxMethod.h>

VXB_DEVMETHOD_DEF(vxbPinMuxEnable, "VxBus PinMux enable method");

STATUS VXB_PIN_MUX_ENABLE (VXB_DEV_ID pDev, INT32 offset)
    {
    vxbPinMuxEnable_t * func = (vxbPinMuxEnable_t *) vxbDevMethodFind (pDev, VXB_DEVMETHOD_CALL(vxbPinMuxEnable));

    if (func == NULL)
        return (STATUS)ERROR;

    return func (pDev, offset);
    }


VXB_DEVMETHOD_DEF(vxbPinMuxDisable, "VxBus PinMux disable method");

STATUS VXB_PIN_MUX_DISABLE (VXB_DEV_ID pDev, INT32 offset)
    {
    vxbPinMuxDisable_t * func = (vxbPinMuxDisable_t *) vxbDevMethodFind (pDev, VXB_DEVMETHOD_CALL(vxbPinMuxDisable));

    if (func == NULL)
        return (STATUS)ERROR;

    return func (pDev, offset);
    }


VXB_DEVMETHOD_DEF(vxbPinMuxShow, "VxBus PinMux show method");

void VXB_PIN_MUX_SHOW (VXB_DEV_ID pDev, INT32 verbose)
    {
    vxbPinMuxShow_t * func = (vxbPinMuxShow_t *) vxbDevMethodFind (pDev, VXB_DEVMETHOD_CALL(vxbPinMuxShow));

    if (func == NULL)
        return;

    func (pDev, verbose);
    }


