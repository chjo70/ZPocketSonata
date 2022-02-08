/* 40vxbFslPci.cdf - Component Definition file for Freescale PCI/PCIe */

/*
 * Copyright (c) 2013, 2015, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
14jun17,mjn  text updates (F8862)
10aug15,wap  Change dependency on VxBus to dependency on PCI bus
28may13,l_z  add law-bar require. (US37630)
23may13,j_z  created
*/

Component       DRV_FSL_PCI {
    NAME        VxBus Qoriq PCI controller
    SYNOPSIS    This component provides the VxBus Qoriq PCI controller driver.\
                The driver configures the controllers in root complex (RC) mode. Support\
                is available for both legacy INTx interrupts and MSI interrupts. Support\
                for extended configuration space accesses is also available.\
                \
                Each bridge requires a local access window (LAW) in which to map its outbound\
                data. If using this driver on a processor which also has the QorIQLaw device,\
                and if the QorIQLaw driver is present and registered on vxBus, this driver\
                will automatically use the QorIQLaw driver to allocate and set-up the outbound\
                windows. If the QorIQLaw is unavailable, it is the responsibility of the BSP\
                author to have created corresponding LAW's separately using whatever driver the\
                particular processor requires. Mappings for prefetchable and non-prefetchable\
                memio, io16 and io32 regions are all provided.
    MODULES     vxbFslPci.o
    LINK_SYMS   fslPciDrv
    REQUIRES    INCLUDE_PCI_BUS \
		INCLUDE_PCI_AUTOCONF
                DRV_FSL_LAW
    _CHILDREN   FOLDER_DRIVERS_PCI
}
