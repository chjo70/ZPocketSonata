/* 00comp_net_remlib.cdf - Component configuration file */

/* Copyright 1984 - 2005 Wind River Systems, Inc. */

/*
modification history
--------------------
01e,27aug07,tkf  Add REM_NUM_CONN_RETRIALS config parameter.
01d,03mar05,wap  Add NET_SYSCTL dependency
01c,14may03,vvv  removed adv_net.h
01b,16apr02,rvr  removed entry points and PREF_DOMAIN attribute (teamf1)
01a,06mar02,ham  ported from TOR3_1-FCS (01e)
*/

Component INCLUDE_REMLIB {
	NAME		Remote Command
	SYNOPSIS	Remote Command Library
	HDR_FILES	remLib.h
	MODULES		remLib.o
	CFG_PARAMS	RSH_STDERR_SETUP_TIMEOUT REM_NUM_CONN_RETRIALS
	INIT_RTN	remLibInit(RSH_STDERR_SETUP_TIMEOUT);
}

Component INCLUDE_REMLIB_SYSCTL {
	NAME		Remote Command sysctl support
	SYNOPSIS	Network sysctl tree support for remlib
	HDR_FILES	remLib.h
	MODULES		remlib_sysctl.o
	INIT_RTN	remLibSysctlInit();
	INCLUDE_WHEN	INCLUDE_RTP \
			INCLUDE_REMLIB
}

Parameter RSH_STDERR_SETUP_TIMEOUT {
        NAME            Timeout interval for second RSH connection if any
        SYNOPSIS        Time limit for optional rcmd() stderr connection
        TYPE            long
        DEFAULT         -1
}

Parameter REM_NUM_CONN_RETRIALS {
        NAME            Number of connect retrials
        SYNOPSIS        Number of times to retry if connect fails.
        TYPE            long
        DEFAULT         3
}
