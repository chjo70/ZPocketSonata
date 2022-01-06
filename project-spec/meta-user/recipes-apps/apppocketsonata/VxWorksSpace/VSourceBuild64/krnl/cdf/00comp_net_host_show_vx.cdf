/* 00comp_net_host_show.cdf - Component configuration file */

/* Copyright 1984 - 2005 Wind River Systems, Inc. */

/*
modification history
--------------------
01b,08apr05,vvv  added netShow.h to HDR_FILES (SPR #104973)
01a,07apr03,ann  written - SPR# 86899
*/


Component INCLUDE_NET_HOST_SHOW
	{
	NAME		Network host show routines
	SYNOPSIS	This component includes support for the hostShow library in your \
			VxWorks image project.  The hostShow library supplies the hostShow( ) \
			function. This function provides a list of remote hosts, \
			along with their Internet addresses and aliases.
	HDR_FILES       netShow.h
	INIT_RTN	hostShowInit();
	MODULES		hostShow.o
	REQUIRES	INCLUDE_HOST_TBL
}
