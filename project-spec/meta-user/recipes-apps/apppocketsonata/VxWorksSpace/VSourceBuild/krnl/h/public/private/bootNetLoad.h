/* bootNetLoad.h - Bootrom Application Network Load Support */

/* 
*  Copyright (c) 2005-2010 Wind River Systems, Inc.
* 
* The right to copy, distribute, modify or otherwise make use
* of this software may be licensed only pursuant to the terms
* of an applicable Wind River license agreement.
*/

/*
modification history
--------------------
01h,26may10,pad  Added 'extern C' statement.
01g,17dec09,pgh  64-bit conversion
01f,06jun08,pgh  Merge DHCP fixes
01e,10sep07,pgh  Add DHCP boot support to bootapp.
01d,23apr07,jmt  Defect 93088 - networking not setup correctly for some
                 bootline updates
01c,25jan07,jmt  Add Network update function prototype
01b,14nov06,jmt  Defect 81465: END Interrupt not disabled before jumping to
                 new image
01a,11may05,jmt   written
*/

/*
DESCRIPTION
This module holds the vxWorks Bootrom Application Network Load Support definitions.

INCLUDE FILES: 
*/ 

#ifndef INCbootNetLoadh
#define INCbootNetLoadh

#include <bootLib.h>

/* defines */

#ifdef __cplusplus
extern "C" {
#endif

/* typedefs */

/* Networking prototypes */

typedef STATUS bootNetLoadPrototype (char *hostName, char *fileName, char *usr,
             char *passwd, void **pEntry);
typedef void bootNetAdrAdjustPrototype ();
typedef STATUS bootNetDevStopAllPrototype (int timeout);
typedef STATUS bootNetSettingsUpdatePrototype (BOOT_PARAMS * pOldBootParams,
             BOOT_PARAMS * pBootParams);
typedef STATUS bootDhcpEnableDisablePrototype (int, char *);

/* global function declarations */

#ifdef __cplusplus
}
#endif

#endif /* INCbootNetLoadh */
