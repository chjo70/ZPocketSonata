/*
 * Copyright (c) 2006-2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

#ifndef VXMUX_CONFIG_H
#define VXMUX_CONFIG_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 *
 * Configuration for VXMUX. Parameters that are macros can only be changed
 * before compiling, variables can be changed before compiling and linking.
 */

/*
 ****************************************************************************
 * 2                    INCLUDE FILES
 ****************************************************************************
 */

#include <ipcom_config.h>

#include <ipcom_type.h>
#include <ipcom_cstyle.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 ****************************************************************************
 * 3                    TYPES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 4                       CONFIGURATION
 ****************************************************************************
 */

/*
 *===========================================================================
 *                        VXMUX_USE_PKT_POOL_MIN
 *===========================================================================
 * Define this macro if you wish to use END2 drivers in an image without
 * the IPNET stack. Do NOT define it if the image will include IPNET.
 *
#define VXMUX_USE_PKT_POOL_MIN
 */

#ifdef __cplusplus
}
#endif

#endif /* VXMUX_CONFIG_H */


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */

