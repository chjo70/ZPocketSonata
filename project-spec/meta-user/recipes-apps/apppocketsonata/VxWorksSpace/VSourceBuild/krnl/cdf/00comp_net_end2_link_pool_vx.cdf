/* 00comp_net_end2_link_pool.cdf - configuration for END2 legacy linkBufPool */

/*
 * Copyright (c) 2008 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01a,08may08,dlk  Written.
*/

Component INCLUDE_END2_LINKBUFPOOL {
	NAME		Legacy linkBufPool for END2 devices
	SYNOPSIS	This component creates a single linkBufPool \
			to be shared by all END2 devices for the benefit of M_BLK-oriented \
			protocols that allocate tuples out of an END device's private network \
			pool. Note that such allocation is not a recommended practice, but some \
			legacy protocols engage in it.
	HDR_FILES	netBufLib.h endLib.h
	CONFIGLETTES	usrNetEnd2LinkPool.c
	INIT_RTN	_end2_linkBufPool = usrLinkPoolCreate \
(END2_LINKBUFPOOL_NTUPLES, END2_LINKBUFPOOL_CLSIZE);
	CFG_PARAMS	END2_LINKBUFPOOL_NTUPLES \
			END2_LINKBUFPOOL_CLSIZE
	REQUIRES	INCLUDE_NETBUFLIB  \
	                INCLUDE_LINKBUFPOOL
	INCLUDE_WHEN	INCLUDE_END2 INCLUDE_WDB_COMM_END
}

Parameter END2_LINKBUFPOOL_NTUPLES {
	NAME		Number of END2 tuples
	SYNOPSIS	Number of tuples in the END2 legacy linkBufPool. By default, it is set to eight.
     	DEFAULT         8
	TYPE		int
}

Parameter END2_LINKBUFPOOL_CLSIZE {
	NAME		END2 linkBufPool cluster size
	SYNOPSIS	Size of tuple clusters in END2 legacy linkBufPool. \
			Note that multiple devices, possibly with different MTUs, share the \
			same pool; so choose a size sufficient for the maximum MTU value.
        DEFAULT         1600
	TYPE		uint
}
