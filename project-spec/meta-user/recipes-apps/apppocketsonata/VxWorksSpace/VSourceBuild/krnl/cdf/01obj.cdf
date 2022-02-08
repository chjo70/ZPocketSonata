/* 01obj.cdf - object (semaphore, message queue, task, timer) components */

/*
 * Copyright (c) 2004, 2007, 2013, 2016, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
17apr17,own  Improved NAME and SYNOPSIS descriptors (F8862).
22apr16,emj  CERT: Update to produce partially linked objects (US79607)
01c,01oct13,rfr  added INCLUDE_CONDVAR_OPEN
01b,06apr07,zl   dependency on INCLUDE_OBJ_INFO
01a,26oct04,fr   created
*/

/*
DESCRIPTION
This file contains descriptions for INCLUDE_OBJ_OPEN components.
*/

Component INCLUDE_OBJ_OPEN {
	NAME		Extended object library
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
	MODULES		objOpen.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
	SYNOPSIS	This component supports the open/close/unlink interfaces for \
			message queues, semaphores, and POSIX timers.
	HDR_FILES	objLib.h
	_CHILDREN	FOLDER_KERNEL
	REQUIRES	INCLUDE_OBJ_INFO
}

Component INCLUDE_MSG_Q_OPEN {
	NAME		Extended message queue library
	SYNOPSIS	This component provides the open/close/unlink interfaces \
			for message queues.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
	MODULES		msgQOpen.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
	INIT_RTN	msgQOpenInit ();
	HDR_FILES	msgQLib.h
	_CHILDREN	FOLDER_NOT_VISIBLE
	REQUIRES	INCLUDE_MSG_Q
	INCLUDE_WHEN	INCLUDE_MSG_Q \
			INCLUDE_OBJ_OPEN
}

Component INCLUDE_SEM_OPEN {
	NAME		Extended semaphore library
	SYNOPSIS	This component provides the open/close/unlink interfaces \
			for semaphores.
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
	MODULES		semOpen.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
	INIT_RTN	semOpenInit ();
	HDR_FILES	semLib.h
	_CHILDREN	FOLDER_NOT_VISIBLE
	REQUIRES	INCLUDE_SEM_BINARY
	INCLUDE_WHEN	INCLUDE_SEM_BINARY \
			INCLUDE_OBJ_OPEN
}

Component INCLUDE_CONDVAR_OPEN {
	NAME		Extended condition variable library
	SYNOPSIS	This component provides the open/close/unlink interfaces \
			for condition variables.
	MODULES		condVarOpen.o
	INIT_RTN	condVarOpenInit ();
	HDR_FILES	condVarLib.h
	_CHILDREN	FOLDER_NOT_VISIBLE
	REQUIRES	INCLUDE_CONDVAR
	INCLUDE_WHEN	INCLUDE_CONDVAR \
			INCLUDE_OBJ_OPEN
}

Component INCLUDE_TASK_OPEN {
	NAME		Extended task management library
	SYNOPSIS	This component provides the open/close/unlink interfaces for tasks.
	INIT_RTN	taskOpenInit ();
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
	MODULES		taskOpen.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
	HDR_FILES	taskLib.h
	_CHILDREN	FOLDER_NOT_VISIBLE
	INCLUDE_WHEN	INCLUDE_OBJ_OPEN
}

Component INCLUDE_TIMER_OPEN {
	NAME		Extended timer library
	SYNOPSIS	This component provides the open/close/unlink interfaces for timers.
	MODULES		timerOpen.o
	INIT_RTN	timerOpenInit ();
	HDR_FILES	private/timerLibP.h
	_CHILDREN	FOLDER_NOT_VISIBLE
	REQUIRES	INCLUDE_POSIX_TIMERS
	INCLUDE_WHEN	INCLUDE_POSIX_TIMERS \
			INCLUDE_OBJ_OPEN
}
