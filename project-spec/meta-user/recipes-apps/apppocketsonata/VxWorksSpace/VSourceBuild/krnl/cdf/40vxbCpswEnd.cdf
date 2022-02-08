/* 40vxbCpswEnd.cdf - Component configuration file */

/*
 * Copyright (c) 2011, 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
15aug12,my_  fix build warnings (WIND00357420)
24aug11,my_  written.
*/

Component   DRV_VXBEND_TI_CPSW {
    NAME        TI 3 Port Switch Network Driver
    SYNOPSIS    TI 3 Port Switch Network Driver
    _CHILDREN   FOLDER_NET_END_DRV
    MODULES     vxbCpswEnd.o
    LINK_SYMS   cpswMaDrv cpswSlDrv
    REQUIRES    INCLUDE_DMA_SYS \
                INCLUDE_END
}
