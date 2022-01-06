/* 00comp_net_base.cdf - Component configuration file */

/* Copyright 2014 Wind River Systems, Inc. */

/*
modification history
--------------------
05may14,rjq  wrote. (V7NET-105)
*/

Component INCLUDE_NETBUFLIB {
	NAME		netBufLib
	SYNOPSIS	Network Buffer Library
	HDR_FILES	netBufLib.h
	INIT_RTN	netBufLibInitialize (NETBUF_LEADING_CLSPACE_DRV);
	MODULES		netBufLib.o 
	CFG_PARAMS	NETBUF_LEADING_CLSPACE_DRV
}

Parameter NETBUF_LEADING_CLSPACE_DRV {
	NAME		Leading pad space for END pool clusters
	SYNOPSIS	Leading cluster pad space to add for network pools \
with only one cluster size, where that cluster size is \
at least 1500 bytes.  The pad space is added to decrease \
the expense of prefixing additional headers to packets \
received from an END. The value chosen should generally \
be a multiple of the cache line size.
#ifdef _WRS_CONFIG_COMPONENT_IPIPSEC
    DEFAULT         128
#else
    DEFAULT         64
#endif        
	TYPE		uint
}

Component INCLUDE_NETBUFADVLIB {
	NAME		netBufAdvLib
	SYNOPSIS	Network Buffer Library Additional Features
	HDR_FILES	netBufLib.h
	INIT_RTN	netBufAdvLibInit ();
	MODULES		netBufAdvLib.o 
}

Component INCLUDE_NETPOOLSHOW {
	NAME		netBufLib show routines
	SYNOPSIS	Network Buffer Library Show routines
	HDR_FILES	netBufLib.h
	LINK_SYMS	netPoolShow
	MODULES		netPoolShow.o 
}

Component INCLUDE_NETBUFPOOL {
	NAME		netBufPool
	SYNOPSIS	netBufLib Generic Pool
	HDR_FILES	netBufLib.h
	INIT_RTN	netBufPoolInit ();
	MODULES		netBufPool.o 
	REQUIRES	INCLUDE_NETBUFLIB    
}

Component INCLUDE_LINKBUFPOOL {
	NAME		linkBufPool
	SYNOPSIS	Network Buffer Library
	HDR_FILES	netBufLib.h
	INIT_RTN	linkBufPoolInit ();
	MODULES		linkBufPool.o 
	REQUIRES	INCLUDE_NETBUFLIB    
}

Component INCLUDE_MBUF_UTIL1 {
	NAME		Commonly used legacy mbuf routines
	SYNOPSIS	Commonly used mbuf routines including m_prepend()
	HDR_FILES	net/mbuf.h
	LINK_SYMS	m_prepend
	MODULES		uipc_mbufutil1.o
	REQUIRES	INCLUDE_NETBUFPOOL
}

Component INCLUDE_MBUF_UTIL2 {
	NAME		Less commonly used legacy mbuf routines
	SYNOPSIS	Less commonly used legacy mbuf routines
	HDR_FILES	net/mbuf.h
	LINK_SYMS	m_pullup
	MODULES		uipc_mbufutil2.o
	REQUIRES	INCLUDE_NETBUFPOOL
}
