/* 00comp_net_getservbyname.cdf - Component configuration file */

/* Copyright 1984-2005 Wind River Systems, Inc. */

/*
modification history
--------------------
01c,31jul06,tkf  Make INCLUDE_GETSERVBYNAME dependent on
                 INCLUDE_IPWRAP_GETSERVBYNAME.
01b,10mar05,vvv  removed ctrl-M characters (SPR #102504)
01a,20feb03,ann  created from 00comp_net_host_tbl.cdf.
*/

Component INCLUDE_GETSERVBYNAME {
	NAME		    get servce by name
	SYNOPSIS	    get servce by name
    REQUIRES        INCLUDE_IPWRAP_GETSERVBYNAME
    INCLUDE_WHEN    INCLUDE_GETSERVBYPORT
}

Component INCLUDE_GETSERVBYPORT {
	NAME		    get servce by port
	SYNOPSIS	    get servce by port
    REQUIRES        INCLUDE_IPWRAP_GETSERVBYPORT
    INCLUDE_WHEN    INCLUDE_GETSERVBYNAME
}
