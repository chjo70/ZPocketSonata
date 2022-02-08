/* vxbVirtLib.h - VxBus virtual device header file */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
11mar14,l_z  Initial version
*/

#ifndef __INCvxbVirtLibh
#define __INCvxbVirtLibh

#define VXB_BUSID_VIRT                BUSTYPE_ID(vxbVirtBus)

STATUS virtDevAdd (char * pName);
STATUS virtDevDel (char * pName, UINT32 unit);

#ifdef __cplusplus
}
#endif

#endif /*__INCvxbVirtLibh*/

