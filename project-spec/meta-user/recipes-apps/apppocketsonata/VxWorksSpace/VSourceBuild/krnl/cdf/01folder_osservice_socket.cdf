/* 00folder_osutil_socket.cdf - Folder configuration file */

/*
 * Copyright (c) 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
01b,14jan14,zan  move FOLDER_SOCKET from FOLDER_UTILITIES to FOLDER_SERVICE.
01a,04jan14,zan  create.
*/

Folder FOLDER_SOCKET {
	NAME		Socket
	SYNOPSIS	This folder contains components and parameters related to sockets.
	CHILDREN	INCLUDE_SOCKLIB \
			INCLUDE_SC_SOCKLIB
	DEFAULTS	INCLUDE_SOCKLIB
    _CHILDREN   FOLDER_SERVICE	
}
