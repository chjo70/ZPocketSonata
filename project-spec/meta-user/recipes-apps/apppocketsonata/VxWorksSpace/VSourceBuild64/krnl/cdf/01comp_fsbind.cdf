/* 01comp_fsbind.cdf - fs bind components */

/*
 * Copyright (c) 2013, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
10feb14,pcs  VXW7-1597 - POSIX components cleanup
15jan14,ghs  move to fs bind layer
08oct13,h_k  created.
*/

/*
DESCRIPTION
This file contains the description for the components utilized by vnode.
*/

Component INCLUDE_POSIX_ADVISORY_FILE_LOCKING {
	NAME		Advisory file locking
	SYNOPSIS	provides advisory file locking in POSIX file systems
	CONFIGLETTES	usrPosixAdvLock.c
	INIT_RTN	usrPosixAdvLockInit ();
	_CHILDREN	FOLDER_STORAGE
	_DEFAULTS	+= FOLDER_POSIX
}
