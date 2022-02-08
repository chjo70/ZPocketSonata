/* 40vxbVirtBus.cdf - Component Definition file for virtual bus driver */

/*
 * Copyright (c) 2014, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
14jun17,mjn  text updates (F8862)
12mar14,l_z  created
*/

#ifdef _WRS_CONFIG_VXBUS_VIRT
Component       DRV_BUS_VIRT {
    NAME        VxBus virtual bus controller
    SYNOPSIS    This component provides the VxBus virtual bus controller driver. The virtual bus\
                allows a user to add user-defined VxBus nodes to the tree on the\
                fly at runtime. This is useful for implementing virtual devices which\
                aren't necessarily tied to real hardware, or for simple experimentation\
                with VxBus and driver design. Normally a device can not be added to the\
                tree except by a parent node that is already part of it, since vxbDevAdd()\
                requires a parent node handle. With the virtual bus driver, the root nexus\
                creates a virtual bus node which is the parent of all virtual devices, and\
                an API is provided for adding new children to this node.
    MODULES     vxbVirtBus.o
    LINK_SYMS   vxbVirtBusDrv
    REQUIRES    INCLUDE_VXBUS
    _CHILDREN   FOLDER_DRIVERS_BUS
}
#endif /* _WRS_CONFIG_VXBUS_VIRT */
