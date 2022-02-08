/* 01comp_hostFs.cdf - Debug Agent Host filesystem components */

/*
 * Copyright (c) 2013-2014 Wind River Systems, Inc.  
 *
 * The right to copy, distribute, modify or otherwise make use  of this 
 * software may be licensed only pursuant to the terms of an applicable Wind 
 * River license agreement.
 */

/*
modification history
--------------------
30oct14,vhe  Changed agent start mechanism (US36858)
02jun14,rlp  Added dependency on INCLUDE_OBJ_OWNERSHIP component (V7COR-1258).
16mayrlp,14  Moved INCLUDE_DEBUG_AGENT_HOSTFS component to invisible folder.
31may13,rlp  Written.

DESCRIPTION

This file contains descriptions for Debug Agent Host filesystem component.
*/

Component INCLUDE_DEBUG_AGENT_HOSTFS {
	NAME		Debug Agent Host filesystem
	SYNOPSIS	Provides a virtual file I/O driver for use with the Debug Agent.  I/O is performed on this virtual I/O device exactly as it would be on any device referencing a VxWorks file system.  File operations, such as read() and write(), move data over a virtual I/O channel created between the Debug Agent and a Workbench TCF client
	MODULES		hostFsLib.o
	INIT_RTN	hostFsLibInit ();
	HDR_FILES	hostFsLib.h
	_INIT_ORDER	tcfServicesInit
#ifdef _WRS_CONFIG_OBJECT_OWNERSHIP
	REQUIRES	INCLUDE_DEBUG_AGENT INCLUDE_OBJ_OWNERSHIP
#else	/* _WRS_CONFIG_OBJECT_OWNERSHIP */
	REQUIRES	INCLUDE_DEBUG_AGENT
#endif	/* _WRS_CONFIG_OBJECT_OWNERSHIP */
	_CHILDREN	FOLDER_NOT_VISIBLE
}
