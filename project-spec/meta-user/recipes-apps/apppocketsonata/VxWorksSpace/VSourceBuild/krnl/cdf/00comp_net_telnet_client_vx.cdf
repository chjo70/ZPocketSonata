/* 00comp_net_telnet_client.cdf - Component configuration file */

/* Copyright 1984-2000 Wind River Systems, Inc. */

/*
modification history
--------------------
01c,30aug06,tkf  Removed CONFIGLETTES and used telnetcInit() for INIT_RTN.
01b,20,jul04jwl  modified for virtualization
01a,22jan04  zhr organized.
*/

Component INCLUDE_TELNET_CLIENT {
	NAME		    TELNET client
	SYNOPSIS	    telnet client by use of telnet protocol
    HDR_FILES       telnetLib.h
    INIT_RTN        telnetcInit ();
	MODULES		    telnetcLib.o 
}

