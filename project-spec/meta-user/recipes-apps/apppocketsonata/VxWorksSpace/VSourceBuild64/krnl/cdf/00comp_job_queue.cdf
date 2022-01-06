/* 00comp_job_queue.cdf - job queue component configuration file */

/* Copyright 2013-2014 Wind River Systems, Inc. */

/*
modification history
--------------------
05may14,rjq  renamed this file. (V7NET-105)
04jun13,rlp  Created.
*/

Folder FOLDER_JOBQUEUE {
        NAME		Job queue
		SYNOPSIS	This folder contains components and parameters that can \
					be used to include and configure job queuing in your project.
        CHILDREN	INCLUDE_JOB_QUEUE \
                  INCLUDE_JOB_QUEUE_UTIL
        DEFAULTS	INCLUDE_JOB_QUEUE
        _CHILDREN FOLDER_SERVICE	
}


Component INCLUDE_JOB_QUEUE {
        NAME		Job queue support
        SYNOPSIS	Includes the jobQueueLib library. It provides a prioritized work deferral mechanism.
        HDR_FILES	jobQueueLib.h
        MODULES		jobQueueLib.o
        INIT_RTN	jobQueueLibInit();
        _INIT_ORDER	usrKernelExtraInit
        INIT_AFTER	hashLibInit
}

Component INCLUDE_JOB_QUEUE_UTIL {
        NAME		Job queue termination support and utilities
        SYNOPSIS	This component supports clean termination of job \
                  queue processing, and job queue and standard job pool \
			           deletion.
        HDR_FILES	jobQueueLib.h
        MODULES		jobQueueUtilLib.o
        INIT_RTN	jobQueueUtilInit ();
        _INIT_ORDER	usrKernelExtraInit
        INIT_AFTER	jobQueueLibInit
}

/* Later we may add parameters for creation of several job queues. */
