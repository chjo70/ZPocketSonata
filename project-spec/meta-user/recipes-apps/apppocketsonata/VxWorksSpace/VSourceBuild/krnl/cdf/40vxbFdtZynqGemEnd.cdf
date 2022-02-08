/* 40vxbZynqGemEnd.cdf - Xilinx zynq end */

/*
 * Copyright (c) 2014, 2016-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
26dec17,g_x  added rx/tx BD number parameters (V7PRO-4194)
27sep17,g_x  added INCLUDE_PINMUX_SYS requires (F6169)
27dec16,swu  rename 40vxbZynq7kGemEnd.cdf to 40vxbZynqGemEnd.cdf (F5261)
12dec16,g_x  added INCLUDE_DEVCLK_SYS requires (F7695)
09aug16,sye  set _CHILDREN to FOLDER_NET_END_DRV (V7PRO-3187)
11feb14,y_c  created.(US34090)
*/

Component DRV_END_FDT_XLNX_ZYNQ7K {
    NAME            (Deprecated) Xilinx Zynq-7000 GEM enhanced network driver
    SYNOPSIS        (Deprecated) Xilinx Zynq-7000 GEM enhanced network driver
    HELP            (Deprecated) It has been deprecated in favor of the \
                    DRV_END_FDT_XLNX_ZYNQ component.
    REQUIRES        DRV_END_FDT_XLNX_ZYNQ
    _CHILDREN       FOLDER_NET_END_DRV
}

Component DRV_END_FDT_XLNX_ZYNQ {
    NAME            Xilinx Zynq GEM enhanced network driver
    SYNOPSIS        This component provides Xilinx Zynq GEM enhanced network \
                    driver (END) support.
    LINK_SYMS       zynqGemDrv
    REQUIRES        INCLUDE_DMA_SYS \
                    INCLUDE_END \
                    DRV_BUS_FDT_ROOT \
                    INCLUDE_DEVCLK_SYS \
                    INCLUDE_PINMUX_SYS
    _CHILDREN       FOLDER_NET_END_DRV
    CFG_PARAMS      XLNX_ZYNQ_END_BD_RX_NUM \
                    XLNX_ZYNQ_END_BD_TX_NUM
}

Parameter XLNX_ZYNQ_END_BD_RX_NUM {
    NAME            Receive Buffer Descriptor Number
    SYNOPSIS        This parameter specifies the number of receive buffer \
                    descriptor that is used in the driver.
    TYPE            int
    DEFAULT         192
}

Parameter XLNX_ZYNQ_END_BD_TX_NUM {
    NAME            Transmit Buffer Descriptor Number
    SYNOPSIS        This parameter specifies the number of transmit buffer \
                    descriptor that is used in the driver.
    TYPE            int
    DEFAULT         192
}

