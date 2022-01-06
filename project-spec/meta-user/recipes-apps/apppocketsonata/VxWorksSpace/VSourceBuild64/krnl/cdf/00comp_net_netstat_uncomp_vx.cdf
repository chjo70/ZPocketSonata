/* 00comp_net_netstat_uncomp.cdf - Component configuration file */

/* Copyright 2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,29jan04,bwa  written
*/


Component INCLUDE_NETSTAT_UN_COMP
	{
	NAME		netstat for AF_LOCAL/COMP
	SYNOPSIS	netstat for AF_LOCAL/COMP
	INIT_RTN	netstatUncompInit ();
	MODULES		netstat_uncomp.o
}
