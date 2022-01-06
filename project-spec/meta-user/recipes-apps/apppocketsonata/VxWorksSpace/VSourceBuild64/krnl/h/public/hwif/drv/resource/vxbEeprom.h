/* vxbEeprom.h - VxBus EEPROM interfaces header file */

/*
 * Copyright (c) 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01b,27sep12,ylu  add typedef name of vxbEepromInfo. (WIND00379558)
01a,24jul12,y_y  written
*/

/*
DESCRIPTION

This library provides the EEPROM specific interfaces

*/

#ifndef __INCvxbEepromh
#define __INCvxbEepromh 

#ifdef __cplusplus
extern "C" {
#endif

/* typedef */

typedef struct vxbEepromInfo
    {
    char   eepromName[MAX_DRV_NAME_LEN + 1];
    UINT32 chipSize;
    STATUS (*epRead) (VXB_DEV_ID pInst, UINT32 addr, UINT8 *buf, UINT32 len, 
                      UINT32* realByte);
    STATUS (*epWrite)(VXB_DEV_ID pInst, UINT32 addr, UINT8 *buf, UINT32 len, 
                      UINT32* realByte); 
    } VXB_EEPROM_INFO;

IMPORT UINT32 eepromDrvNextUnit();
IMPORT STATUS eepromDevCreate(char * name, VXB_DEV_ID pDev, VXB_EEPROM_INFO * pCandidate);
IMPORT STATUS eepromDevRemove(char * name);

#ifdef __cplusplus
}
#endif

#endif /* __INCvxbEepromh */

