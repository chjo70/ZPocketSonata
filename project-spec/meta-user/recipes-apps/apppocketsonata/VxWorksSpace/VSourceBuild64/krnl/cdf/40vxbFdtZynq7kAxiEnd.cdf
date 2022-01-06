/* 40vxbFdtZynq7kAxiEnd.cdf - ZYNQ7K AXI ETHERNET controller configuration file */

/* Copyright (c) 2014, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
09aug16,sye  set _CHILDREN to FOLDER_NET_END_DRV (V7PRO-3187)
06aug14,y_c  written. (US40549)
*/

Component	DRV_END_FDT_XLNX_ZYNQ7K_AXI {
        NAME            XILINX ZYNQ7K AXI END Driver
        SYNOPSIS        XILINX ZYNQ7K AXI END Driver
        LINK_SYMS       zynq7kAxiEthDrv
        REQUIRES        INCLUDE_VXBUS \
                        DRV_BUS_FDT_ROOT
        _CHILDREN       FOLDER_NET_END_DRV
}
