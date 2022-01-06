/* vxbFlashLib.h - vxBus flash subsystem interfaces module */

/*
 * Copyright (c) 2014, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/* 
modification history
--------------------
21nov16,ffu  add LP64 support in TFFS layer (F4496)
20nov14,pmr  conditionalize show routine with _WRS_CONFIG_DEBUG_FLAG
23feb16,ffu  add vxbflashLibInit function to called. (V7STO-337)
16jan14,ywu  created for VxBus GEN2
*/

/*
DESCRIPTION

This library provides the flash specific interfaces

*/

#ifndef _INC_vxbFlashLibH
#define _INC_vxbFlashLibH

/* includes */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct vxbFlashCtrl {
    SL_NODE     flashNode;    /* this node */
    VXB_DEV_ID  pDev;         /* pointer to the controller instance */
    char        devName[32];  /* controller driver name */
    UINT32      unitId;       /* controller unit ID */
    void      * flashChip;
    ULONG       private;

#ifdef _WRS_CONFIG_DEBUG_FLAG
    /* show info */
    STATUS (*flashShow)
        (
        VXB_DEV_ID  pDev,
        UINT32 verbose
        );
#endif
} VXB_FLASHCTRL;

STATUS vxbFlashLibInit (void);
extern STATUS vxbFlashChipAdd (VXB_FLASHCTRL *pCtrl);
extern void * vxbFlashChipFind (char * devName, UINT32 unitId);
#ifdef _WRS_CONFIG_DEBUG_FLAG
extern void   vxbFlashChipShow (UINT32 verbose);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _INC_vxbFlashLibH */

