/* 40vxbFdtTiCpswEnd.cdf - Component configuration file */

/*
 * Copyright (c) 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
05jan16,m_w  create. (V7PRO-2729)
*/

Component   DRV_END_FDT_TI_CPSW {
    NAME        TI 3 Port Switch Network Driver
    SYNOPSIS    TI 3 Port Switch Network Driver
    _CHILDREN   FOLDER_NET_END_DRV
    MODULES     vxbFdtTiCpswEnd.o
    LINK_SYMS   cpswSwCtrlDrv cpswPortDrv
    REQUIRES    INCLUDE_END
}
