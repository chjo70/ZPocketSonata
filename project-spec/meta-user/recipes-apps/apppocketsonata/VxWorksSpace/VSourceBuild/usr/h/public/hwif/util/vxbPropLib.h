/* vxbPropLib.h - VxBus property library header file */

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
21nov14,wap Created
*/

#ifndef __INCvxbPropLibh
#define __INCvxbPropLibh

#ifdef __cplusplus
extern "C" {
#endif

IMPORT STATUS vxbPropertyGet (VXB_DEV_ID pDev, char * pCompatName,
    int unit, char * pPropName, void * pPropVal, int pPropLen);
IMPORT STATUS vxbPropertySet (VXB_DEV_ID pDev, char * pCompatName,
    int unit, char * pPropName, void * pPropVal, int propLen);

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbPropLibh */


