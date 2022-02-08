/* 01systemviewer.cdf - System Viewer component description file */

/*
 * Copyright (c) 2013-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */

/*
modification history
--------------------
20oct15,gxu  dataCollectorLib cannot log without System Viewer(US68020).
04nov14,wzc  enlarge stack size of upload task.(V7COR-2108)
07aug14,wzc  restore the config parameters.(WB4-3949)
20may14,sdt  Added INCLUDE_WINDVIEW_MODULE_CLASS - WB4-3207
22feb14,wzc  remove dependency on IPNET.(WB4-2724)
21feb14,wzc  remove dependency on STACKTRACE.(WB4-2682)
18feb14,to   moved USER_TIME* parameters here (VXW7-1860)
10feb14,pcs  VXW7-1597 - POSIX components cleanup
04feb14,sdt  Renamed folder to FOLDER_SYSTEMVIEWER - WB4-2594
27aug13,rlp  Removed INCLUDE_WVUPLOAD_TSFSSOCK component.
16jul13,wzc  Create.
*/

/*
DESCRIPTION
This file contains descriptions for system viewer components.
*/

Folder	FOLDER_SYSTEMVIEWER {
	NAME		System viewer
	SYNOPSIS	This folder contains components and parameters that can be used \
			to configure the System Viewer.
	CHILDREN	INCLUDE_WINDVIEW 	\
			INCLUDE_WINDVIEW_CLASS 	\
                        INCLUDE_WVNETD          \
                        INCLUDE_TRIGGERING	\
                        INCLUDE_DATACOLLECTOR	\
			SELECT_TIMESTAMP 	\
                        SELECT_WVUPLOAD 	\
                        SELECT_WV_BUFFER
	DEFAULTS	INCLUDE_WINDVIEW 	\
			INCLUDE_WINDVIEW_CLASS 	\
			SELECT_TIMESTAMP 	\
                        SELECT_WV_BUFFER	\
			SELECT_WVUPLOAD	
}

Selection	SELECT_WVUPLOAD {
	NAME		Upload path(s)
	SYNOPSIS	Choose among TSFS, NFS and/or TCP/IP.
	COUNT		1-
	CHILDREN	INCLUDE_WVUPLOAD_FILE	\
			INCLUDE_WVUPLOAD_SOCK
	DEFAULTS	INCLUDE_WVUPLOAD_FILE
}

Component INCLUDE_WVUPLOAD_FILE {
	NAME		File upload path initialization 
	SYNOPSIS	Initialize the path for the file upload.
	MODULES		wvFileUploadPathLib.o 
	INIT_RTN	wvFileUploadPathLibInit ();
	HDR_FILES	private/wvUploadPathP.h private/wvFileUploadPathLibP.h
	REQUIRES	INCLUDE_WINDVIEW
}

Component INCLUDE_WVUPLOAD_SOCK {
	NAME		TCP/IP socket upload path initialization 
	SYNOPSIS	Initialize path for the upload through TCP/IP sockets 
	MODULES		wvSockUploadPathLib.o 
	INIT_RTN	wvSockUploadPathLibInit ();
	HDR_FILES	private/wvUploadPathP.h private/wvSockUploadPathLibP.h
	REQUIRES	INCLUDE_WINDVIEW INCLUDE_IPNET
}

Selection	SELECT_TIMESTAMP {
	NAME		Select timestamping
	SYNOPSIS	Choose between sequential timestamping, user-defined timestamping \
			and system-defined timestamping.
	COUNT		1-1
	CHILDREN	INCLUDE_SYS_TIMESTAMP	\
			INCLUDE_USER_TIMESTAMP	\
			INCLUDE_SEQ_TIMESTAMP
	DEFAULTS	INCLUDE_SEQ_TIMESTAMP
}

Component INCLUDE_SYS_TIMESTAMP {
	NAME		System-defined timestamping
	SYNOPSIS	Supports BSP-specific timestamp routines. 
#ifdef _WRS_CONFIG_SV_INSTRUMENTATION
	INIT_RTN	wvTmrRegister ((UINTFUNCPTR) sysTimestamp,	\
				(UINTFUNCPTR) sysTimestampLock,	        \
				(FUNCPTR) sysTimestampEnable,	\
				(FUNCPTR) sysTimestampDisable,	\
				(FUNCPTR) sysTimestampConnect,	\
				(UINTFUNCPTR) sysTimestampPeriod,	\
				(UINTFUNCPTR) sysTimestampFreq);
#endif 
	HDR_FILES	wvTmrLib.h sysLib.h
	REQUIRES	INCLUDE_TIMESTAMP
}

Component INCLUDE_USER_TIMESTAMP {
	NAME		User-defined timestamping
	SYNOPSIS	Supports user-defined timestamp routines.
#ifdef _WRS_CONFIG_SV_INSTRUMENTATION
	INIT_RTN	wvTmrRegister ((UINTFUNCPTR) USER_TIMESTAMP,	\
				(UINTFUNCPTR) USER_TIMESTAMPLOCK,	\
				(FUNCPTR) USER_TIMEENABLE,		\
				(FUNCPTR) USER_TIMEDISABLE,		\
				(FUNCPTR) USER_TIMECONNECT,		\
				(UINTFUNCPTR) USER_TIMEPERIOD,		\
				(UINTFUNCPTR) USER_TIMEFREQ);
#endif
	CFG_PARAMS	USER_TIMESTAMP		\
			USER_TIMESTAMPLOCK	\
			USER_TIMEENABLE		\
			USER_TIMEDISABLE	\
			USER_TIMECONNECT	\
			USER_TIMEPERIOD		\
			USER_TIMEFREQ
	HDR_FILES	wvTmrLib.h
}

Component INCLUDE_SEQ_TIMESTAMP {
	NAME		Sequential timestamping
	SYNOPSIS	Supports sequential timestamping. This is recommended if you are \
			new to the System Viewer.
	MODULES		seqDrv.o
#ifdef _WRS_CONFIG_SV_INSTRUMENTATION
	INIT_RTN	wvTmrRegister ((UINTFUNCPTR) seqStamp,	\
				(UINTFUNCPTR) seqStampLock,	\
				(FUNCPTR) seqEnable,	\
				(FUNCPTR) seqDisable,	\
				(FUNCPTR) seqConnect,	\
				(UINTFUNCPTR) seqPeriod,	\
				(UINTFUNCPTR) seqFreq);
#endif
	HDR_FILES	wvTmrLib.h private/seqDrvP.h
}

Component INCLUDE_WINDVIEW {
	NAME		System Viewer library
	SYNOPSIS	Initialize and control event logging of the System Viewer.
	CONFIGLETTES	usrWindview.c
	MODULES		evtLogLib.o 
	INIT_RTN	windviewConfig ();
	CFG_PARAMS	WV_DEFAULT_BUF_MIN	\
			WV_DEFAULT_BUF_MAX	\
			WV_DEFAULT_BUF_SIZE	\
			WV_DEFAULT_BUF_THRESH	\
			WV_DEFAULT_BUF_OPTIONS	\
			WV_MAX_LOGS             \
			WV_UPLOAD_STACK_SIZE    \
			WV_UPLOAD_PRIORITY
	HDR_FILES	wvLib.h rBuffLib.h
#ifdef _WRS_CONFIG_STACKTRACE
	REQUIRES	SELECT_TIMESTAMP \
			SELECT_WVUPLOAD  \
			SELECT_WV_BUFFER \
			INCLUDE_WINDVIEW_CLASS \
			INCLUDE_STACKTRACE \
			INCLUDE_SV_DATACOLLECTOR
#else
	REQUIRES	SELECT_TIMESTAMP \
			SELECT_WVUPLOAD  \
			SELECT_WV_BUFFER \
			INCLUDE_WINDVIEW_CLASS \
			INCLUDE_SV_DATACOLLECTOR
#endif 
}

Component INCLUDE_SV_DATACOLLECTOR {
	NAME		System Viewer data collector library
	SYNOPSIS	Data collectors for System Viewer
	INIT_RTN	svDataCollectorLibInit ();
	MODULES		svDataCollectorLib.o
	REQUIRES	INCLUDE_DATACOLLECTOR
	_CHILDREN	FOLDER_NOT_VISIBLE
	HDR_FILES	private/svDataCollectorLibP.h
}

Component INCLUDE_DATACOLLECTOR {
	NAME		Generic data collector library
	SYNOPSIS	This component provides data collectors for generic analysis \
			tools. See the dataCollectorLib entry in the VxWorks 7 Kernel \
			DEBUG ANALYSIS API Reference for detailed description of 	\
			the different routines in this library. 
	INIT_RTN	dataCollectorLibInit ();
	MODULES		dataCollectorLib.o
        REQUIRES        INCLUDE_EVENTPOINT
	HDR_FILES	dataCollectorLib.h
}

Component INCLUDE_EVENTPOINT {
        NAME            Eventpoints library
        SYNOPSIS        eventpoints instrumentation
        INIT_RTN        eventPointLibInit ();
	PROTOTYPE	STATUS eventPointLibInit (void);
        MODULES         eventPointLib.o
	HDR_FILES	private/eventPointLibP.h
        REQUIRES        INCLUDE_EVENTPOINT_STUB
}

Component INCLUDE_EVENTPOINT_STUB {
        NAME            eventpoint stub library
        SYNOPSIS        stub eventpoint implementation
        INIT_RTN        eventPointStubLibInit ();
	PROTOTYPE	STATUS eventPointStubLibInit (void);
        MODULES         eventPointStubLib.o
	HDR_FILES	private/eventDefsP.h \
			private/eventPointStubLibP.h
}

Selection SELECT_WV_BUFFER {
	NAME		System Viewer buffer management library
	SYNOPSIS	Selects the buffer management library for the System Viewer; \
			either the rBuff library or an user-defined System Viewer \
			buffer manager. rBuff is the default.
	COUNT		1-1
	CHILDREN	INCLUDE_RBUFF INCLUDE_WV_BUFF_USER
	DEFAULTS	INCLUDE_RBUFF
}

Component INCLUDE_WINDVIEW_CLASS {
	NAME		System Viewer class instrumentation
	SYNOPSIS	Low-level kernel instrumentation needed by System Viewer
	INIT_RTN	wvLibInit ();
	MODULES		wvLib.o
}

Component INCLUDE_WINDVIEW_MODULE_CLASS {
	NAME		System Viewer class instrumentation module support
	SYNOPSIS	Module management support for the System Viewer library
	MODULES		wvModuleLib.o
	INCLUDE_WHEN	INCLUDE_WINDVIEW_CLASS INCLUDE_MODULE_MANAGER
	_CHILDREN	FOLDER_NOT_VISIBLE
}

Component INCLUDE_POSIX_TRACE {
	NAME		Trace
	SYNOPSIS	POSIX trace in RTP.
	MODULES		pxTraceStreamLib.o
        INIT_RTN        pxTraceStreamLibInit ();
	HDR_FILES	private/pxTraceStreamLibP.h
	_CHILDREN	FOLDER_POSIX
	REQUIRES	INCLUDE_RTP \
			INCLUDE_POSIX_CLOCKS	\
			INCLUDE_POSIX_TRACE_TIMESTAMP
}

Component INCLUDE_POSIX_TRACE_TIMESTAMP {
        NAME            POSIX trace timestamp
        MODULES         wvTmrLib.o
        INIT_RTN        traceTmrRegister ((UINTFUNCPTR) sysTimestamp,	\
				(FUNCPTR) sysTimestampEnable,	\
				(FUNCPTR) sysTimestampDisable,	\
				(FUNCPTR) sysTimestampConnect,	\
				(UINTFUNCPTR) sysTimestampPeriod,	\
				(UINTFUNCPTR) sysTimestampFreq);
        REQUIRES        INCLUDE_SYS_TIMESTAMP
        HDR_FILES       wvTmrLib.h
}

Component INCLUDE_WV_BUFF_USER {
	NAME		User-defined System Viewer buffer manager
	SYNOPSIS	User defined library for managing System Viewer buffers
	INIT_RTN	USER_WV_BUFF_INIT
	CFG_PARAMS	USER_WV_BUFF_INIT
}

Component INCLUDE_WVNETD {
        NAME            Network instrumentation
        SYNOPSIS        Adds support for dual stack Network Instrumentation (wvNetDLib).
        MODULES         wvNetDLib.o
        REQUIRES	INCLUDE_WINDVIEW
        INIT_RTN        wvNetDInit ();
        HDR_FILES       wvNetDLib.h
}

Component INCLUDE_TRIGGERING {
        NAME            Triggering library
        SYNOPSIS        Adds support for triggering for system and user events
        MODULES         trgLib.o
        INIT_RTN        trgLibInit ();
        HDR_FILES       trgLib.h private/trgLibP.h
        REQUIRES        INCLUDE_TRIG_DATACOLLECTOR
}

Component INCLUDE_TRIG_DATACOLLECTOR {
	NAME		Triggering data collector library
	SYNOPSIS	Data collectors for Triggering
	INIT_RTN	trgDataCollectorLibInit ();
	MODULES		trgDataCollectorLib.o
        REQUIRES        INCLUDE_DATACOLLECTOR
}

Component INCLUDE_TRIGGER_SHOW {
	NAME		Trigger show routine
	SYNOPSIS	This component provides the trgShow library. This library \
			provides routines to show event triggering information, \
			such as list of triggers, associated actions, trigger states, \
			and so on. The routine trgShowInit() links the triggering show \
			facility into the VxWorks system. It is called automatically \
			when this component is included.
	MODULES		trgShow.o
	INIT_RTN	trgShowInit ();
        HDR_FILES       trgLib.h private/trgLibP.h
	REQUIRES	INCLUDE_TRIGGERING
	INCLUDE_WHEN	INCLUDE_TRIGGERING \
			INCLUDE_SHOW_ROUTINES
}

Component INCLUDE_RBUFF_SHOW {
	NAME		rBuff show routine
	SYNOPSIS  	Displays rBuff information and statistics about ring buffer performance. \
			Optional and only available if you include RBUFF.
	MODULES		rBuffShow.o
	INIT_RTN	rBuffShowInit ();
        HDR_FILES       rBuffLib.h
	REQUIRES	INCLUDE_RBUFF
	INCLUDE_WHEN	INCLUDE_RBUFF \
			INCLUDE_SHOW_ROUTINES
}

Component INCLUDE_DATACOLLECTOR_SHOW {
	NAME		Data collector show routines
	SYNOPSIS	This component provides the dataCollectorShow library which contains \
			routines to display properties of registered dataCollectors.
	MODULES		dataCollectorShow.o
	INIT_RTN	dataCollectorShowInit ();
	HDR_FILES	dataCollectorShow.h
        REQUIRES        INCLUDE_DATACOLLECTOR
}

InitGroup usrWindviewInit {
	INIT_RTN	usrWindviewInit ();
#ifdef _WRS_CONFIG_STACKTRACE
	INIT_AFTER	INCLUDE_STACKTRACE
#endif /* _WRS_CONFIG_STACKTRACE */
	INIT_ORDER	INCLUDE_WINDVIEW	\
			INCLUDE_SYS_TIMESTAMP	\
			INCLUDE_USER_TIMESTAMP	\
			INCLUDE_SEQ_TIMESTAMP	\
			INCLUDE_RBUFF		\
			INCLUDE_WV_BUFF_USER	\
			INCLUDE_WVUPLOAD_SOCK	\
			INCLUDE_WVUPLOAD_FILE   \
                        INCLUDE_WVNETD		\
			INCLUDE_WVTIPC
}

Parameter USER_WV_BUFF_INIT {
        NAME            User-defined buffer manager
        SYNOPSIS        Sets the routine to initialize user-defined buffer manager.
}

Parameter USER_TIMESTAMP {
        NAME            Timestamp routine
        SYNOPSIS        User defined timestamp routine address
}

Parameter USER_TIMESTAMPLOCK {
        NAME            Timestamp with intLock
        SYNOPSIS        Same as Timestamp but with interrupts locked
}

Parameter USER_TIMEENABLE {
        NAME            Enable Timestamp routine
        SYNOPSIS        Enable a timestamp timer interrupt
}

Parameter USER_TIMEDISABLE {
        NAME            Disable Timestamp routine
        SYNOPSIS        Disable a timestamp timer interrupt
}

Parameter USER_TIMECONNECT {
        NAME            Connect Timestamp routine to interrupt
        SYNOPSIS        Connect a user routine to a timestamp timer interrupt
}

Parameter USER_TIMEPERIOD {
        NAME            Get the period of timestamp
        SYNOPSIS        Get the period of a timestamp timer
}

Parameter USER_TIMEFREQ {
        NAME            Get frequency of timestamp
        SYNOPSIS        Get a timestamp timer clock frequency
}

Parameter WV_DEFAULT_BUF_MIN {
        NAME		Minimum number of buffers
        SYNOPSIS        Sets the minimum number of buffers in the system viewer. 
        TYPE		int
        DEFAULT		4
}

Parameter WV_DEFAULT_BUF_MAX {
        NAME          Maximum number of buffers
        SYNOPSIS      Sets the maximum number of buffers in the system viewer.  
        TYPE          int
        DEFAULT       16
}

Parameter WV_DEFAULT_BUF_SIZE {
        NAME		Size of each buffer
        SYNOPSIS        Sets the default size of each buffer. 
        TYPE		int
        DEFAULT		0x8000
}

Parameter WV_DEFAULT_BUF_THRESH {
        NAME		Buffer threshold
        TYPE		int
        DEFAULT		0x4000
}

Parameter WV_DEFAULT_BUF_OPTIONS {
        NAME		Buffer options
        TYPE		int
        DEFAULT		0x0
}

Parameter WV_MAX_LOGS {
        NAME		Maximum number of Wind View logs
        SYNOPSIS		Maximum number of Wind View logs on target at any time.
        TYPE		int
        DEFAULT		5
}

Parameter WV_UPLOAD_STACK_SIZE {
        NAME		Stack allocated to System Viewer upload task
        SYNOPSIS		Stack allocated to System Viewer upload task
        TYPE		int
        DEFAULT		8192
}

Parameter WV_UPLOAD_PRIORITY {
        NAME		System Viewer upload task priority
        SYNOPSIS		Initial priority of System viewer upload task
        TYPE		int
        DEFAULT		51
}
