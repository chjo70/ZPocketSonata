/* 00comp_vxmux_pkt_pool.cdf - configuration file for minimal packet pool */

/*
 * Copyright (c) 2008 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01a,29jun08,dlk  Written.
*/

Component INCLUDE_VXMUX_PKT_POOL_MIN {
    NAME            Minimal VXMUX Ipcom_pkt packet pool
    SYNOPSIS        In absence of the IPNET stack, this will provide support for the Ipcom_pkt packet pool.
    EXCLUDES        INCLUDE_IPNET
    INIT_RTN        vxmux_pkt_pool_init (VXMUX_PKT_POOL_LIMIT, VXMUX_PKT_POOL_USE_NULL_POOL, VXMUX_PKT_POOL_MAX_LINKHDR, VXMUX_PKT_POOL_BUF_ALIGN);
    PROTOTYPE       int vxmux_pkt_pool_init(int mem_pool_limit, BOOL use_null_pool,  int max_link_hdr, int bufAlign);
    CFG_PARAMS      VXMUX_PKT_POOL_LIMIT \
                    VXMUX_PKT_POOL_USE_NULL_POOL \
                    VXMUX_PKT_POOL_MAX_LINKHDR \
                    VXMUX_PKT_POOL_BUF_ALIGN
}

Parameter VXMUX_PKT_POOL_LIMIT {
    NAME            Memory limit for VXMUX memory pool
    SYNOPSIS        This parameter sets the maximum allocation, in bytes, from the memory pool \
underlying the VXMUX minimal packet pool slab caches.
    TYPE            int
    DEFAULT         (20 * 1024 * 1024)
}

Parameter VXMUX_PKT_POOL_USE_NULL_POOL {
    NAME            M_LINK allocation in VXMUX packet pool
    SYNOPSIS        Set this parameter to "true" to enable VXMUX minimal packet pool support for M_BLK oriented protocols and drivers.
    TYPE            BOOL
    DEFAULT         TRUE
}

Parameter VXMUX_PKT_POOL_MAX_LINKHDR {
    NAME            Per-packet link header space to reserve
    SYNOPSIS        The number of bytes of space reserved at the start of \
each packet in the VXMUX minimal packet pool for link-level headers \
including tunnelling and similar headers.
    TYPE            int
    DEFAULT         18
}

Parameter VXMUX_PKT_POOL_BUF_ALIGN {
    NAME            Alignment of packet buffers
    SYNOPSIS        The alignment, measured in bytes, of packet data \
buffers in packets allocated from the VXMUX minimal packet pool. \This must be a positive integral power of two.
    TYPE            int
    DEFAULT         64
}

Component INCLUDE_VXMUX_SLAB {
    NAME            VXMUX memory pools and slab caches
    SYNOPSIS        Slab cache memory allocator for use in absence of IPNET.
    INIT_RTN        vxmux_slab_init(NULL);
    PROTOTYPE       int vxmux_slab_init(void *unused);
    MODULES         vxmux_slab.o
}

Component INCLUDE_VXMUX_CMD_VXSLAB {
    NAME            Display VXMUX memory pools and slab caches
    SYNOPSIS       This component includes the 'vxslab' command interpreter shell show routine \
for VXMUX slab memory caches.
    INIT_RTN        vxmux_cmd_slab_init(NULL);
    PROTOTYPE       int vxmux_cmd_slab_init(void *unused);
    MODULES         vxmux_cmd_vxslab.o
}
