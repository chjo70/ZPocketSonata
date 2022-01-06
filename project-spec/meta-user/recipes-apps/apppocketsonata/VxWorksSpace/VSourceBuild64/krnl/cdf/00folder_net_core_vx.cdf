/* 00folder_net_core.cdf - Folder configuration file */

/*
 * Copyright (c) 2001-2008,2014,2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
07dec16,mca  Break hard dependency between END and IPNET. (US85582)
27may14,rjq  Remove obsolete component. (V7NET-373)
05may14,rjq  Decouple END with COREIP. (V7NET-105)
15jan14,h_s  Remove GTF support. (US19989)
04jul08,dlk  Added INCLUDE_VXMUX_SLAB, INCLUDE_VXMUX_CMD_VXSLAB, and
             INCLUDE_VXMUX_PKT_POOL_MIN.
17jun08,dlk  Rename INCLUDE_NULLBUFPOOL as INCLUDE_VXMUX_NULLBUFPOOL.
             Added INCLUDE_VXMUX_MBLK.
20may08,dlk  Removed INLCUDE_NPT.
09may08,dlk  Added INCLUDE_END2_LINKBUFPOOL.
03mar07,dlk  Update for MUX2.
26jan07,tkf  Remove INCLUDE_USE_IPCOM_SHELL.
02jan07,dlk  Added INCLUDE_MBUF_UTIL1 and INCLUDE_MBUF_UTIL2
18nov06,kch  Corrected default configurations.
06oct06,kch  Added INCLUDE_NET_INIT and removed SELECT_NET_INIT.
23sep06,kch  Added INCLUDE_IPNET_LOOPBACK_CONFIG to default configuration.
22sep06,tkf  Move IPCOM Core Components to here.
12jun06,dlk  Added INCLUDE_NULLBUFPOOL for IPCOM support.
08feb06,dlk  Replace INCLUDE_NET_STACK_START with
         INCLUDE_NET_INIT_SKIP, which has the opposite sense.
29sep05,dlk  Add INCLUDE_NET_STACK_START.
08aug05,wap  Add polled stats component
25jul05,dlk  Added INCLUDE_NETBUFADVLIB.
         INLCUDE_NETPOOLSHOW is on by default.
18nov03,rhe  Added INCLUDE_NETBUFPOOL reuired for netBufLib
15may03,vvv  modified for INCLUDE_DEFER_NET_INIT
27jun02,ppp  merged from t3
06jun02,rvr  added INCLUDE_NETWORK (teamf1)
06may02,ham  back to old netBufLib.
21feb02,ham  moved DAEMON to private folder.
15feb02,ham  added NET_POOL.
26nov01,ham  revised from TOR3_1-FCS (01b).
*/

Folder FOLDER_NET_CORE {
    SYNOPSIS    This folder contains the core components of the network.
    CHILDREN    INCLUDE_MUX2        \
                INCLUDE_MUX_OVER_END2 \
                INCLUDE_MUX2_OVER_END \
                INCLUDE_MUXTK_OVER_END2 \
                INCLUDE_VXMUX_MBLK \
                INCLUDE_NET_INIT    \
                INCLUDE_NET_POOL    \
                INCLUDE_END2_LINKBUFPOOL \
                INCLUDE_VXMUX_NULLBUFPOOL \
                INCLUDE_VXMUX_PKT_POOL_MIN \
                INCLUDE_VXMUX_SLAB \
                INCLUDE_VXMUX_CMD_VXSLAB \
                INCLUDE_IPCOM \
                FOLDER_IPWRAP
    DEFAULTS    INCLUDE_MUX2 \
                INCLUDE_VXMUX_NULLBUFPOOL \
                INCLUDE_VXMUX_MBLK \
                INCLUDE_IPCOM
}
