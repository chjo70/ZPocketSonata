/* 00comp_net_sc_socklib.cdf - Component configuration file */

/* Copyright 2003-2004i, 2006, 2016 Wind River Systems, Inc. */

/*
modification history
--------------------
27apr16,pee  add support for CERT / certKernel.o
01dev06,tlu  Added forward prototyping for sockScLibInit()
11nov04,job  Added INCLUDE_SC_SOCKLIB to usrScInit init group
02dec03,vvv  written
*/

Component INCLUDE_SC_SOCKLIB {
	NAME		Socket API System Call support
	SYNOPSIS	System call support for socket API
	INIT_RTN	sockScLibInit ();
	PROTOTYPE	STATUS sockScLibInit (void);
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
	MODULES		sockScLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
	INCLUDE_WHEN    INCLUDE_SOCKLIB INCLUDE_RTP
	REQUIRES        INCLUDE_SOCKLIB INCLUDE_RTP
	_INIT_ORDER     usrScInit
}
