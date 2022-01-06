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
#include <hwif/util/vxbParamLib.h>
#include <hwif/methods/vxbParamMethod.h>

VXB_DEVMETHOD_DEF(vxbParamChg, "VxBus device parameter change notify method");

STATUS VXB_PARAM_CHG (VXB_DEV_ID pDev, VXB_PARAMS * pParam)
    {
    vxbParamChg_t * func = (vxbParamChg_t *) vxbDevMethodFind (pDev, VXB_DEVMETHOD_CALL(vxbParamChg));

    if (func == NULL)
        return (STATUS)VXB_NO_METHOD;

    return func (pDev, pParam);
    }


