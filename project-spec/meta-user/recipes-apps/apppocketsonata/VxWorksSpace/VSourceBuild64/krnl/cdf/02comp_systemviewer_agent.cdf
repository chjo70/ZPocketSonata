/* 01comp_systemviewer_agent.cdf - system viewer agent components */

/*
 * Copyright (c) 2009-2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
04feb14,sdt  Moved SV agent to FOLDER_SYSTEMVIEWER

DESCRIPTION
This file contains component descriptions for the system viewer agent.

*/


Component INCLUDE_SYSTEMVIEWER_AGENT {
	NAME		    System Viewer Agent
	SYNOPSIS	    Network Agent for driving System Viewer from host-side tools.
	INIT_RTN	    init_system_viewer ();
	_INIT_ORDER	    tcfServicesInit
	REQUIRES	    INCLUDE_DEBUG_AGENT INCLUDE_WINDVIEW
	CONFIGLETTES	    usrSystemViewer.c
	_CHILDREN	    FOLDER_SYSTEMVIEWER
}
