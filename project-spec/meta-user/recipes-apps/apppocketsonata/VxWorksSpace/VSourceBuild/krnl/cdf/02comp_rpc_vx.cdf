/* 00comp_net_rpc.cdf - Component configuration file */

/*
 * Copyright (c) 2002, 2004 - 2006, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
22jan17,jbm  Fixed typo, removed tabs, minor editing
26dec06,kch  Removed usrNetRpc.c configlette and changed init routine
             to rpcInit().
31oct06,mwv  adding a requires INCLUDE_IPNET_SOCKET
29mar05,vvv  added NAME for XDR components (SPR #98613)
21jun04,vvv  added virtual stack support
16apr02,rvr  removed entry points and PREF_DOMAIN attribute (teamf1)
19feb02,ham  created from TOR3_1-FCS 01c.
*/

Component INCLUDE_RPC {
    NAME        RPC
    SYNOPSIS    This daemon is a Remote Procedure Call (RPC) server that acts \
                as a central registrar for RPC services running on the same \
                machine. RPC clients query the daemon to find out how to contact \
                the various servers.
    PROTOTYPE   IMPORT STATUS rpcInit (void);
    INIT_RTN    rpcInit ();
    MODULES     auth_none.o \
                auth_unix.o \
                authunix_pro.o \
                clnt_generic.o \
                clnt_perror.o \
                clnt_raw.o \
                clnt_simple.o \
                clnt_tcp.o \
                clnt_udp.o \
                get_myaddr.o \
                pmap_clnt.o \
                pmap_getmaps.o \
                pmap_getport.o \
                pmap_prot.o \
                pmap_prot2.o \
                portmap.o \
                rpcLib.o \
                rpc_callmsg.o \
                rpc_common.o \
                rpc_prot.o \
                svc.o \
                svc_auth.o \
                svc_auth_uni.o \
                svc_raw.o \
                svc_simple.o \
                svc_tcp.o \
                svc_udp.o \
                xdr_array.o \
                xdr_rec.o \
                xdr_ref.o 
    REQUIRES    INCLUDE_IPNET_SOCKET

}

Component INCLUDE_XDR_BOOL_T {
    NAME        XDR boolean support
    SYNOPSIS    This component includes modules that supply the XDR routine \
                for bool_ts. 
    MODULES     xdr_bool_t.o
}

Component INCLUDE_XDR {
    NAME         XDR
    SYNOPSIS     This component includes modules that implement the generic XDR \
                 (External Data Representation) routines as described in RFC 1014. 
    MODULES      xdr.o \
                 xdr_float.o \
                 xdr_mem.o
}
