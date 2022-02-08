/* 01comp_runtime_analysis.cdf - Runtime Analysis components */

/*
 * Copyright (c) 2009-2015, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
07sep17,zli  Fix wrong attribute in runtime analysis CDF file (V7COR-5316)
13jan15,tle  Add vxworks_polling event processor (US11628)
03nov14,tle  Disable cafe RTP comp when CORE_RTP is not enabled in VSB (V7COR-1999)
30oct14,vhe  Changed agent start mechanism (US36858)
26aug14,tle  Make system_info EP mandatory (US30550)
20May14,sdt  Added missing import for topDemoStart - WB4-3445
26feb14,sdt  Dissociate HPC folder definition
21feb14,sdt  Changed tag to 'EXPERIMENTAL:'
10feb14,sdt  Added 'Experimental' tag to HPC component - TA40129
20jan14,sdt  Added history.

DESCRIPTION

This file contains component descriptions for the Runtime Analysis.

*/

Folder FOLDER_RUNTIME_ANALYSIS {
        NAME            Runtime Analysis
        SYNOPSIS        Runtime Analysis components for target performance analysis
	_CHILDREN	FOLDER_TOOLS
	CHILDREN	FOLDER_ANALYSIS_OPTIONAL \
			FOLDER_ANALYSIS_DEMO \
			FOLDER_ANALYSIS_TEST \
			FOLDER_ANALYSIS_EVENT_PROC
	DEFAULTS	INCLUDE_ANALYSIS_AGENT \
			INCLUDE_ANALYSIS_SCRIPT \
			FOLDER_ANALYSIS_OPTIONAL
}

InitGroup usrAnalysisInit {
	INIT_RTN	usrAnalysisInit ();
	SYNOPSIS	Runtime Analysis initialization
	_INIT_ORDER	usrToolsInit
	INIT_AFTER 	usrWindviewInit
	INIT_BEFORE	INCLUDE_DEBUG_AGENT
	INIT_ORDER	INCLUDE_CAFE_EP_CAFE_NAMESPACE
}

Folder FOLDER_ANALYSIS_OPTIONAL {
        NAME            Optional Runtime Analysis components
        SYNOPSIS        Optional features for Runtime Analysis
	CHILDREN	INCLUDE_ANALYSIS_AUX_CLOCK
	DEFAULTS	INCLUDE_ANALYSIS_AUX_CLOCK
}

Folder FOLDER_ANALYSIS_DEMO {
        NAME            Analysis Demo components
        SYNOPSIS        Components for demonstrating Runtime Analysis
}

Folder FOLDER_ANALYSIS_TEST {
        NAME            Tests
        SYNOPSIS        Runtime Analysis Test Components
        _CHILDREN       FOLDER_NOT_VISIBLE
	CHILDREN	INCLUDE_ANALYSIS_TEST
	DEFAULTS	INCLUDE_ANALYSIS_TEST
}

Folder FOLDER_ANALYSIS_EVENT_PROC {
	NAME		Runtime Analysis Event Processor folder
	_CHILDREN       FOLDER_NOT_VISIBLE
	CHILDREN	INCLUDE_CAFE_EP_VXWORKS \
			INCLUDE_CAFE_RTP \
			INCLUDE_CAFE_EP_AGGREGATOR \
			INCLUDE_CAFE_EP_REALTIME \
			INCLUDE_CAFE_EP_TIMESTAMP_NORMALIZER \
			INCLUDE_CAFE_EP_ELOG \
			INCLUDE_CAFE_EP_TIMER \
			INCLUDE_CAFE_EP_TCF_UPLOAD \
			INCLUDE_CAFE_EP_SYS_CLOCK \
			INCLUDE_CAFE_EP_AUX_CLOCK \
			INCLUDE_CAFE_EP_PERFORMANCE_PROFILER \
			INCLUDE_CAFE_EP_SYSINFO \
			INCLUDE_CAFE_EP_CAFE_NAMESPACE \
			INCLUDE_CAFE_EP_STREAM_READER \
			INCLUDE_CAFE_EP_STREAM_WRITER \
			INCLUDE_CAFE_EP_PRINT \
			INCLUDE_CAFE_EP_VXWORKS_POLLING
}

Component INCLUDE_ANALYSIS_AGENT {
        NAME            Runtime Analysis Agent
        SYNOPSIS        Runtime Analysis Agent used for target profiling, monitoring and memory analysis.
	_CHILDREN	FOLDER_RUNTIME_ANALYSIS
	REQUIRES	INCLUDE_CAFE_EP_AGGREGATOR \
			INCLUDE_CAFE_EP_SYS_CLOCK \
			INCLUDE_CAFE_EP_ELOG \
			INCLUDE_CAFE_EP_PERFORMANCE_PROFILER \
			INCLUDE_CAFE_EP_TCF_UPLOAD \
			INCLUDE_CAFE_EP_TIMER \
			INCLUDE_CAFE_EP_TIMESTAMP_NORMALIZER \
			INCLUDE_CAFE_EP_VXWORKS \
			INCLUDE_CAFE_EP_SYSINFO \
			INCLUDE_CAFE_EP_VXWORKS_POLLING \
			INCLUDE_CAFE_TCF_SERVICE
}

Component INCLUDE_ANALYSIS_DEBUG_SUPPORT {
        NAME            Debug support components
        SYNOPSIS        Includes some helpful components to runtime Analysis tool such as print, stream reader or stream writer event processors. 
	_CHILDREN	FOLDER_ANALYSIS_OPTIONAL
	REQUIRES	INCLUDE_CAFE_PRINT \
			INCLUDE_CAFE_EP_PRINT \
			INCLUDE_CAFE_EP_STREAM_READER \
			INCLUDE_CAFE_EP_STREAM_WRITER \
			INCLUDE_CAFE_EP_REALTIME
}

Component INCLUDE_ANALYSIS_AUX_CLOCK {
	NAME		Use Auxiliary Clock ticks
	SYNOPSIS	Generates Analysis events based on auxiliary clock ticks
	_CHILDREN	FOLDER_ANALYSIS_OPTIONAL
	REQUIRES	INCLUDE_CAFE_EP_AUX_CLOCK
	INCLUDE_WHEN	INCLUDE_ANALYSIS_AGENT
}


Component INCLUDE_CAFE_EP_VXWORKS {
        NAME            Cafe event source for VxWorks
        SYNOPSIS        Source of VxWorks events for Cafe analysis tools
	HDR_FILES	cafe/cafe.h vxworks/ep/vxworks_kernel_vx.h
        INIT_RTN        cafeVxworksKernelInit ();
	_INIT_ORDER	usrAnalysisInit
	_CHILDREN	FOLDER_NOT_VISIBLE
	CONFIGLETTES	cafeConfigs.c
	REQUIRES	INCLUDE_EVENTPOINT INCLUDE_CAFE_EP_CAFE_NAMESPACE \
			INCLUDE_CAFE_VX_TIMESTAMP INCLUDE_LOADER_HOOKS
}

Component INCLUDE_CAFE_EP_VXWORKS_POLLING {
        NAME            Cafe polling event source for VxWorks
        SYNOPSIS        Emit vxworks data, like resource usage, triggered by input event
	HDR_FILES	vxworks/ep/vxworks_polling.h
	INIT_RTN	cafeVxWorksPollingInit();
	_INIT_ORDER	usrAnalysisInit
	_CHILDREN	FOLDER_NOT_VISIBLE
	CONFIGLETTES	cafeConfigs.c
	REQUIRES	INCLUDE_CAFE_EP_CAFE_NAMESPACE
}

#if defined(_WRS_CONFIG_RTP)
Component INCLUDE_CAFE_RTP {
	NAME            Cafe RTP support
	SYNOPSIS        Provides support for RTPs in Cafe
	HDR_FILES       vxworks/ep/vxworks_rtp.h
	INIT_RTN        cafe_rtp_init ();
	_INIT_ORDER     usrAnalysisInit
	_CHILDREN       FOLDER_NOT_VISIBLE
	REQUIRES        INCLUDE_RTP
	INCLUDE_WHEN    INCLUDE_CAFE_EP_VXWORKS INCLUDE_RTP
 }
#endif	/* _WRS_CONFIG_RTP */

Component INCLUDE_CAFE_EP_AGGREGATOR {
        NAME            Aggregator event processor
        SYNOPSIS        Generic event aggregator
	HDR_FILES	cafe/ep/aggregator.h
	INIT_RTN	cafeAggregatorInit ();
	_INIT_ORDER	usrAnalysisInit
	_CHILDREN	FOLDER_NOT_VISIBLE
	REQUIRES	INCLUDE_CAFE_EP_CAFE_NAMESPACE
	CONFIGLETTES	cafeConfigs.c
}

Component INCLUDE_ANALYSIS_SCRIPT {
        NAME            Runtime Analysis script runner
        SYNOPSIS        Enable scripted creation of Cafe instruments
        MODULES         script_vx.o script_parser.o
	_CHILDREN	FOLDER_RUNTIME_ANALYSIS
	REQUIRES	INCLUDE_CAFE_EP_CAFE_NAMESPACE
	LINK_SYMS	cafe_script_run
}

Component INCLUDE_CAFE_VX_TIMESTAMP {
        NAME            Cafe timestamp from Vxworks
        SYNOPSIS        Provide timestamp for Cafe, using VxWorks sysTimestamp
	HDR_FILES	vxworks/cafe_vx_timestamp.h
	INIT_RTN	cafe_vx_timestamp_init ();
	_INIT_ORDER	usrAnalysisInit
	_CHILDREN	FOLDER_NOT_VISIBLE
	REQUIRES	INCLUDE_SYS_TIMESTAMP
}

Component INCLUDE_CAFE_EP_REALTIME {
        NAME            Delay replay of events to realtime
        SYNOPSIS        Restore time spacing of events to realtime
        INIT_RTN        realTimeCfgRegister ();
	_INIT_ORDER	usrAnalysisInit
	_CHILDREN	FOLDER_NOT_VISIBLE
	HDR_FILES	cafe/ep/realtime_ep.h
	REQUIRES	INCLUDE_CAFE_EP_VXWORKS \
			INCLUDE_POSIX_TIMERS \
			INCLUDE_POSIX_CLOCKS
	CONFIGLETTES	cafeConfigs.c
}

Component INCLUDE_CAFE_EP_TIMESTAMP_NORMALIZER {
        NAME            Timestamp normalizer event processor
        SYNOPSIS        Handle target timestamp rollover for Cafe
        INIT_RTN        timestampNormalizerCfgRegister ();
	_INIT_ORDER	usrAnalysisInit
	_CHILDREN	FOLDER_NOT_VISIBLE
	HDR_FILES	cafe/ep/timestamp_normalizer.h
	REQUIRES	INCLUDE_CAFE_EP_VXWORKS
	CONFIGLETTES	cafeConfigs.c
}

Component INCLUDE_CAFE_EP_ELOG {
        NAME            Cafe event log
        SYNOPSIS        Event buffering for Cafe instruments on VxWorks target
        INIT_RTN        elog_native_cfg_init ();
	_INIT_ORDER	usrAnalysisInit
	_CHILDREN	FOLDER_NOT_VISIBLE
	HDR_FILES	cafe/ep/elog_native.h
	REQUIRES	INCLUDE_CAFE_EP_CAFE_NAMESPACE
}

Component INCLUDE_CAFE_EP_TIMER {
        NAME           	Timer event processor
        SYNOPSIS        Interval timer, using timestamps of incoming events
	INIT_RTN	cafeTimerRegister ();
	_INIT_ORDER	usrAnalysisInit
	_CHILDREN	FOLDER_NOT_VISIBLE
	HDR_FILES	cafe/ep/timer_ep.h
	REQUIRES	INCLUDE_CAFE_EP_CAFE_NAMESPACE
	CONFIGLETTES	cafeConfigs.c
}

Component INCLUDE_CAFE_EP_TCF_UPLOAD {
        NAME            TCF upload event processor
        SYNOPSIS        Stream event data to the host over TCF
	HDR_FILES	cafe/ep/tcf_upload.h
        INIT_RTN        cafeTcfUploadInit ();
	_INIT_ORDER	usrAnalysisInit
	_CHILDREN	FOLDER_NOT_VISIBLE
	CONFIGLETTES	cafeConfigs.c
	REQUIRES	INCLUDE_CAFE_EP_CAFE_NAMESPACE \
			INCLUDE_DEBUG_AGENT
}

Component INCLUDE_CAFE_EP_SYS_CLOCK {
	NAME		System Clock Cafe event source
	SYNOPSIS	Generates Cafe events based on system clock ticks
	HDR_FILES	vxworks/ep/sys_clock_ep.h
	INIT_RTN	sys_clock_ep_init ();
	_INIT_ORDER	usrAnalysisInit
	_CHILDREN	FOLDER_NOT_VISIBLE
	REQUIRES	INCLUDE_CAFE_EP_CAFE_NAMESPACE
}

Component INCLUDE_CAFE_EP_AUX_CLOCK {
	NAME		Auxiliary Clock Cafe event source
	SYNOPSIS	Generates Cafe events based on auxiliary clock ticks
	HDR_FILES	vxworks/ep/aux_clock_ep.h
	INIT_RTN	aux_clock_ep_init ();
	_INIT_ORDER	usrAnalysisInit
	_CHILDREN	FOLDER_NOT_VISIBLE
	REQUIRES	INCLUDE_CAFE_EP_CAFE_NAMESPACE \
			INCLUDE_AUX_CLK
}

Component INCLUDE_CAFE_EP_PERFORMANCE_PROFILER {
	NAME		Performance Profiler Cafe Event Processor
	SYNOPSIS	Statistical sampler based on arbitrary events
	HDR_FILES	vxworks/ep/performance_profiler_ep.h
	INIT_RTN	performance_profiler_od_ep_init ();
	_INIT_ORDER	usrAnalysisInit
	_CHILDREN	FOLDER_NOT_VISIBLE
	REQUIRES	INCLUDE_STACKTRACE
}

Component INCLUDE_CAFE_EP_SYSINFO {
        NAME            System Information event processor
        SYNOPSIS        Event processor providing bsp-specific information about the system
	HDR_FILES	cafe/ep/sysinfo.h
        INIT_RTN        cafeSysinfoInit ();
	_INIT_ORDER	usrAnalysisInit
	_CHILDREN	FOLDER_NOT_VISIBLE
	REQUIRES	INCLUDE_CAFE_EP_CAFE_NAMESPACE
	CONFIGLETTES	cafeConfigs.c
}

Component INCLUDE_CAFE_EP_CAFE_NAMESPACE {
        NAME            Cafe initialization
        SYNOPSIS        Initialize the Cafe system
	HDR_FILES	cafe/ep/cafe_namespace.h
        INIT_RTN        cafe_cfg_namespace_init ();
        _CHILDREN       FOLDER_NOT_VISIBLE
}

Component INCLUDE_CAFE_EP_STREAM_READER {
        NAME            Cafe event stream reader
        SYNOPSIS        Cafe event processor to read events from a file
	HDR_FILES	cafe/ep/file_stream_reader.h
	INIT_RTN	cafeFstreamReaderInit ();
	_INIT_ORDER	usrAnalysisInit
	_CHILDREN	FOLDER_NOT_VISIBLE
	CONFIGLETTES	cafeConfigs.c
	REQUIRES	INCLUDE_CAFE_EP_CAFE_NAMESPACE
	INCLUDE_WHEN	INCLUDE_ANALYSIS_SCRIPT
}

Component INCLUDE_CAFE_EP_STREAM_WRITER {
        NAME            Cafe event stream writer
        SYNOPSIS        Cafe event processor to write events to a file
	HDR_FILES	cafe/ep/file_stream_writer.h
	INIT_RTN	cafeFstreamWriterInit ();
	_INIT_ORDER	usrAnalysisInit
	_CHILDREN	FOLDER_NOT_VISIBLE
	CONFIGLETTES	cafeConfigs.c
	REQUIRES	INCLUDE_CAFE_EP_CAFE_NAMESPACE
	INCLUDE_WHEN	INCLUDE_ANALYSIS_SCRIPT
}

Component INCLUDE_CAFE_EP_PRINT {
        NAME            Cafe event print
        SYNOPSIS        Event processor which prints all event data it receives to the console
	HDR_FILES	cafe/ep/print.h
	INIT_RTN	cafePrintRegister();
	_INIT_ORDER	usrAnalysisInit
	_CHILDREN	FOLDER_NOT_VISIBLE
	CONFIGLETTES	cafeConfigs.c
	REQUIRES	INCLUDE_CAFE_EP_CAFE_NAMESPACE
}

Component INCLUDE_CAFE_PRINT {
        NAME            Cafe print routines
        SYNOPSIS        Print utilities for Cafe
        LINK_SYMS       cafe_ep_spec_print
        _CHILDREN       FOLDER_NOT_VISIBLE
}

Component INCLUDE_CAFE_TCF_SERVICE {
        NAME            Cafe TCF Service
        SYNOPSIS        Provides Cafe services for TCF
        MODULES         cafe_config_service.o
        LINK_SYMS       ini_cafe_config_service
        _CHILDREN       FOLDER_NOT_VISIBLE
        INIT_RTN        cafe_service_init(DEBUG_AGENT_TASK_PRIORITY);
        _INIT_ORDER     tcfServicesInit
        REQUIRES        INCLUDE_DEBUG_AGENT
        CONFIGLETTES    cafe_service_configlette.c
}

Component INCLUDE_ANALYSIS_TOP_DEMO {
        NAME            Top demo for Cafe on VxWorks
        SYNOPSIS        Routines to demonstrate top on VxWorks
	_CHILDREN	FOLDER_ANALYSIS_DEMO
        MODULES         topDemoLib.o
        LINK_SYMS       topDemoStart
	_INIT_ORDER	usrAnalysisInit
}

Component INCLUDE_ANALYSIS_TOP_DEMO_START {
        NAME            Automatically start Top demo for VxWorks
        SYNOPSIS        Starts top demonstration code for VxWorks
	_CHILDREN	FOLDER_ANALYSIS_DEMO
	REQUIRES	INCLUDE_ANALYSIS_TOP_DEMO
        PROTOTYPE       IMPORT STATUS topDemoStart (void);
        INIT_RTN        topDemoStart ();
	_INIT_ORDER	usrAnalysisInit
}

Component INCLUDE_ANALYSIS_CACHE_DEMO {
        NAME            Cache demo for Cafe on VxWorks
        SYNOPSIS        Routines to demonstrate cache statistics
	_CHILDREN	FOLDER_ANALYSIS_DEMO
        MODULES         cafe_cache_demo.o
        LINK_SYMS       cafe_cache_demo
	_INIT_ORDER	usrAnalysisInit
}

Component INCLUDE_ANALYSIS_MEM_DEMO {
        NAME            alloc/free demo for Cafe on VxWorks
        SYNOPSIS        Two examples of the impact of malloc and free
	_CHILDREN	FOLDER_ANALYSIS_DEMO
        MODULES         cafe_mem_demo.o
        LINK_SYMS       cafe_mem_demo_start
	_INIT_ORDER	usrAnalysisInit
}

Component INCLUDE_ANALYSIS_IO_DEMO {
        NAME            I/O demo for Cafe on VxWorks
        SYNOPSIS        Routines to demonstrate visiblity of read and write data
	_CHILDREN	FOLDER_ANALYSIS_DEMO
        MODULES         io_demo.o
        LINK_SYMS       cafe_io_demo_start
	_INIT_ORDER	usrAnalysisInit
}

Component INCLUDE_ANALYSIS_INTLATENCY_DEMO {
        NAME            Interrupt latency demo for Cafe on VxWorks
        SYNOPSIS        Routines to demonstrate impact of interrupt latency
	_CHILDREN	FOLDER_ANALYSIS_DEMO
        MODULES         cafe_intlatency_demo.o
        LINK_SYMS       cafe_intlatency_demo_start
	_INIT_ORDER	usrAnalysisInit
}

Component INCLUDE_ANALYSIS_USER_EVENT_DEMO {
        NAME            User event demo for Cafe on VxWorks
        SYNOPSIS        Routines to demonstrate custom user events
	_CHILDREN	FOLDER_ANALYSIS_DEMO
        MODULES         memdemo.o mybuffer.o
        LINK_SYMS       memdemo
	_INIT_ORDER	usrAnalysisInit
}

Component INCLUDE_ANALYSIS_TEST {
        NAME            Runtime Analysis tests
        SYNOPSIS        Unit tests for Runtime Analysis components. Execute cafe_unit_test from target shell to run tests.
	_CHILDREN	FOLDER_ANALYSIS_TEST
	REQUIRES	INCLUDE_CAFE_EP_ELOG \
                        INCLUDE_CAFE_EP_STREAM_READER \
			INCLUDE_CAFE_EP_STREAM_WRITER INCLUDE_CAFE_EP_VXWORKS \
			INCLUDE_SEM_READ_WRITE INCLUDE_SEM_READ_WRITE_CREATE \
			INCLUDE_CAFE_PRINT
        LINK_SYMS       cafe_unit_test
}

