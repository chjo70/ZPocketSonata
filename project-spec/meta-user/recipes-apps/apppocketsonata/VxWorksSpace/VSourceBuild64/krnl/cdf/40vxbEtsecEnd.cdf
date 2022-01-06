/* 40vxbEtsecEnd.cdf - Component configuration file */

/*
 * Copyright (c) 2013, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River License agreement.
 */

/*
modification history
--------------------
07jan16,l_z  correct file header. (V7PRO-2296)
20dec13,hll  Add _CHILDREN for INCLUDE_ETSEC_VXB_END.(VXW7-1219)
23may13,x_z  created
*/

Component   INCLUDE_ETSEC_VXB_END {
    NAME        Enhanced TSEC VxBus Enhanced Network Driver
    SYNOPSIS    Enhanced TSEC VxBus Enhanced Network Driver
    _CHILDREN   FOLDER_NET_END_DRV
    MODULES     vxbEtsecEnd.o
    LINK_SYMS   etsecDrv
    REQUIRES    INCLUDE_DMA_SYS \
                INCLUDE_END
}
 
