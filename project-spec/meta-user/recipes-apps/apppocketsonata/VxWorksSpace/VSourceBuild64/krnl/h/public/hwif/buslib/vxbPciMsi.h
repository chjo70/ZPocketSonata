/* vxbPciMsi.h - PCI lib header file for vxBus */

/*
 * Copyright (c) 2013-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
10aug15,wap  Add library init routine
22jul15,wap  Add prototypes for vxbPciMsiProgram() and vxbPciMsiXProgram()
16jun15,wap  Correct prototype for vxbPciMsiXfree()
08jun15,wap  Add initial support for MSI-X (F3973)
30oct14,l_z  Fix wrong routine declaration. (V7PRO-1428)
28apr14,l_z  Fix typo error. (US37630)
12jul13,j_z  Created.
*/

#ifndef __INCvxbPciMsiH
#define __INCvxbPciMsiH

/* dynamic vectors */

IMPORT STATUS vxbPciMsiInit (void);

IMPORT int vxbPciMsiAlloc (VXB_DEV_ID pDev, UINT32 cnt);
IMPORT STATUS vxbPciMsiFree (VXB_DEV_ID pDev, UINT32 cnt);
IMPORT int vxbPciMsiXAlloc (VXB_DEV_ID pDev, UINT32 cnt);
IMPORT STATUS vxbPciMsiXFree (VXB_DEV_ID pDev, UINT32 cnt);

IMPORT STATUS vxbPciMsiProgram (VXB_DEV_ID pDev);
IMPORT STATUS vxbPciMsiXProgram (VXB_DEV_ID pDev);

#endif /* __INCvxbPciMsiH */

