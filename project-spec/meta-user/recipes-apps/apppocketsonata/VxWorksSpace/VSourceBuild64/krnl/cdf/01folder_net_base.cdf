/* 00folder_net_base.cdf - Net base folder configuration file */

/* Copyright 2014,2016-2017 Wind River Systems, Inc. */

/*
modification history
--------------------
02jan17,mca  Make INCLUDE_IFNAMELIB visible. (V7NET-1223)
07dec16,mca  Break hard dependency between END and IPNET (US85582)
16aug16,mca  Added FOLDER_NET_BASE_LIBC
25may14,rjq  FOLDER_NET_END should be in
             FOLDER_NETWORK_ADVANCED. (V7NET-365)
05may14,rjq  wrote. (V7NET-105)
*/

Folder FOLDER_NETWORK {
    NAME        Network Components
}

Folder FOLDER_NET_BASE {
    NAME        Network Base Components
    SYNOPSIS    Network Base componet for END, MIB and IPNET.
    CHILDREN    INCLUDE_NETBUFLIB     \
                INCLUDE_NETBUFADVLIB  \
                INCLUDE_NETBUFPOOL    \
                INCLUDE_LINKBUFPOOL   \
                INCLUDE_MBUF_UTIL1    \
                INCLUDE_MBUF_UTIL2    \
                INCLUDE_NET_DAEMON
    _CHILDREN   FOLDER_NETWORK
    DEFAULTS    INCLUDE_NETBUFLIB   \
                INCLUDE_NETBUFPOOL  \
                INCLUDE_LINKBUFPOOL \
                INCLUDE_NET_DAEMON
}

Folder FOLDER_NET_BASE_LIBC {
    NAME        Libc networking APIs
    SYNOPSIS    This folder contains components which provide various
                networking related APIs.
    CHILDREN    INCLUDE_ARPAINETLIB \
                INCLUDE_IFNAMELIB
    _CHILDREN   FOLDER_NET_BASE
}
