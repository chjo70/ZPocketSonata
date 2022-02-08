/* 40vxbTeiEnd.cdf - TEI driver */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River License agreement.
 */

/*
modification history
--------------------
22sep14,wap  created (US41483)
*/
 
Component   DRV_VXBEND_TEI82598 {
        NAME            Intel PRO/10GbE VxBus enhanced network driver
        SYNOPSIS        This component creates a "tei" network \
                        interface for the following Intel devices: \
                        82598, 82599, x540, and x550EM PCI Express \
                        controller chips.
        _CHILDREN       FOLDER_NET_END_DRV
        MODULES         vxbTei82598End.o
        LINK_SYMS       teiDrv
        REQUIRES        INCLUDE_DMA_SYS \
                        INCLUDE_END \
                        INCLUDE_VXBUS
}
