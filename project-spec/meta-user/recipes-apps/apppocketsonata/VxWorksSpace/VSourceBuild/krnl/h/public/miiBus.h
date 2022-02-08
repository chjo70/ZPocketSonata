/* miiBus.h - MII bus controller and API library */

/* Copyright (c) 2005-2008, 2012, 2014, 2016 Wind River Systems, Inc. */

/*
modification history
--------------------
26may16,dlk  Define END_DEV_INFO structure only in the kernel.
16mar16,wap  Add prototypes for miiBusParamSet() and miiBusLinkSet (F1921)
15mar16,wap  Add prototype for miiBusFdtLibInit() (F1921)
15apr14,y_y  rewrite the header file (US33490).
23jan14,ylu  fixed coverity and compling issues.
10jan12,rec  WIND00326681 - miiBusMonitor task polling inhibits power
             management.  Add miiBusQuiesce and miiBusWakeup.
04sep08,wap  Add miiBusIdleErrorCheck() routine (WIND00129165)
29mar07,tor  update methods
05sep06,kch  Replaced if_media.h include with endMedia.h.
20jun06,wap  Remove prototype for vxbNextUnitGet
25may06,wap  Add support for miibus device deletion
04dec05,wap  Written.
*/

#ifndef __INCmiiBush
#define __INCmiiBush

#include <hwif/vxBus.h>
#include <hwif/buslib/vxbFdtLib.h>
#include <vxbMiiLib.h>

#ifdef _WRS_KERNEL
typedef struct endDevInfo {
    struct vxbFdtDev vxbFdtDev;
    VXB_RESOURCE_LIST vxbResList;
} END_DEV_INFO;
#endif

IMPORT STATUS phyAttach(VXB_DEV_ID);
IMPORT STATUS mdioAttach(VXB_DEV_ID);
IMPORT STATUS miiFind (VXB_DEV_ID, FUNCPTR);
IMPORT void miiBusFdtLibInit (void);
IMPORT void miiBusFdtParamSet (VXB_DEV_ID, int);
IMPORT void miiBusFdtLinkSet (VXB_DEV_ID, VXB_DEV_ID);

#endif /* __INCmiiBush */
