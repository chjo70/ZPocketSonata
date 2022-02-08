/* 00iadtBus.cdf - IADT component description file */

/*
 * Copyright (c) 2013-2014, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
15jun17,mjn  text updates (F8862)
29apr14,j_l  US37556 - Convert *MPT* names to *IADT*
10dec13,scm  US24478 - initial mods for GEN2 test image...
*/

Component DRV_BUS_IADT_ROOT {
    NAME            IADT bus
    SYNOPSIS        This component provides the Intel Architecture Device Table (IADT) bus support library. \
                    The IADT bus contains devices configured by the BIOS or UEFI.
    MODULES         vxbIadtBus.o
    LINK_SYMS       vxbIadtBusDrv
    _CHILDREN       FOLDER_DRIVERS_BUS
    REQUIRES        INCLUDE_VXBUS
}

