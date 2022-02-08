/* usrVnic.h - vxbus IVNIC interface header file */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
06oct14,rec  US45792 - Initial version
*/

/*
DESCRIPTION
This file provides VNIC specific definitions.
*/

#ifndef __INCusrVnich
#define __INCusrVnich

#include <hwif/vxBus.h>

static const char VNIC_DRIVER_NAME[] = "vnic"; 

#ifdef __cplusplus
extern "C" {
#endif

/* Structure for driver configuration */
    
typedef struct usrVnicCfg
    {
    BOOL            valid;
    int             index;
    UINT32          rxDescCnt;
    UINT32          txDescCnt;
    } USR_VNIC_CFG;
    
IMPORT USR_VNIC_CFG usrVnicCfgList[];
IMPORT int usrVnicCfgListMaxCount;

#ifdef __cplusplus
}
#endif

#endif /* __INCusrVnich */
