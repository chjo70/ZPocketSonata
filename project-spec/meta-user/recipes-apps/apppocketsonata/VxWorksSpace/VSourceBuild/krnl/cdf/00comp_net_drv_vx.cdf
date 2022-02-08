/* 00comp_net_drv.cdf - Component configuration file */

/* Copyright 1984-2003, 2016 Wind River Systems, Inc. */

/*
modification history
--------------------
27jan16,dlk  Adding NETDRV_OPTIONS.
13may03,ppp  removed inclusion of adv_net.h
16apr02,rvr  removed entry points and PREF_DOMAIN attribute
06mar02,ham  ported from TOR3_1-FCS (01b).
*/

Component INCLUDE_NET_DRV {
	NAME			NetDrv for remote IO 
	SYNOPSIS		Allows access to file system on boot host
	HDR_FILES		netDrv.h
	MODULES			netDrv.o 
	REQUIRES                INCLUDE_NET_REM_IO
        CFG_PARAMS              NETDRV_OPTIONS
}

Parameter NETDRV_OPTIONS {
    NAME           Options for netDrvEx()
    SYNOPSIS       Options passed to netDrvEx() to initialize the netDrv \
                   driver code. Currently, there is only one option bit \
                   defined: \
                   NETDRV_CHDIR_REMOTE_CHECK -- When changing to a directory \
                   accessed via a netDrv device, or changing directory within \
                   a netDrv device, perform an actual check of the remote \
                   directory's existence via FTP or RSH.  Without this flag, \
                   no such check is made.
    TYPE           UINT32
    DEFAULT        0
}
