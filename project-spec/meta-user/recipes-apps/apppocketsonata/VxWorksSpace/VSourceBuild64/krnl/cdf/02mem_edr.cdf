/* 02mem_edr.cdf - Memory ED&R component description file */

/*
 * Copyright (c) 2004, 2009, 2011, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */


/*
modification history
--------------------
17apr17,own  Improved NAME and SYNOPSIS descriptors (F8862).
01g,27sep11,pcs  Removed INIT_ORDER information for componentd INCLUDE_MEM_EDR
                 and INCLUDE_MEM_EDR2, since now they are explictly
                 initialized in the Initgroup usrRoot.
01f,11aug09,cww  Delayed memEdr initialization
01e,10nov04,zl   remove INCLUDE_WHEN for INCLUDE_MEM_EDR_RTP_SHOW.
01d,05aug04,tam  fixed compilation warning: SPR 100114
01c,29apr04,zl   added INCLUDE_MEM_EDR_RTP_SHOW
01b,18mar04,zl   added INCLUDE_EDR_ERRLOG as required component;
                 added INCLUDE_MEM_EDR_RTC component.
01a,26jan04,zl   written.
*/

/*
DESCRIPTION
This file contains descriptions for the memory error detection and
reporting components.
*/


Component INCLUDE_MEM_EDR {
	NAME		Memory error detection and reporting
	SYNOPSIS	This component provides memory error detection and \
			reporting support. It includes the basic memory \
			partition debugging functionality and instrumentation code.
	_CHILDREN	FOLDER_TOOLS
	MODULES		memEdrLib.o
	CONFIGLETTES	usrMemEdr.c
	INIT_RTN	memEdrInit ();
	CFG_PARAMS	MEDR_EXTENDED_ENABLE \
			MEDR_FILL_FREE_ENABLE \
			MEDR_FREE_QUEUE_LEN \
			MEDR_BLOCK_GUARD_ENABLE \
			MEDR_POOL_SIZE
	REQUIRES	INCLUDE_EDR_ERRLOG \
			INCLUDE_MEM_EDR2 \
			INCLUDE_MEM_MGR_FULL
}

Component INCLUDE_MEM_EDR2 {
	NAME		Memory error detection and reporting
	SYNOPSIS	Memory error detection and reporting.
	_CHILDREN	FOLDER_NOT_VISIBLE
	MODULES		memEdrLib.o
	CONFIGLETTES	usrMemEdr.c
	INIT_RTN	memEdrInit2();
}

Component INCLUDE_MEM_EDR_RTC {
	NAME		Compiler assisted run-time checker
	SYNOPSIS	This component provides compiler assisted run-time \
			checker support. It must be included to configure \
			VxWorks for kernel RTEC support.
	_CHILDREN	FOLDER_TOOLS
	MODULES		memEdrRtc.o
	REQUIRES	INCLUDE_MEM_EDR
}

Component INCLUDE_MEM_EDR_SHOW {
        NAME            Memory ED&R show routines
        SYNOPSIS        This component provides support for show functions in the \
				memory partitions and heap instrumentation in the kernel.
        MODULES         memEdrShow.o
	INIT_RTN	memEdrShowInit();
	_CHILDREN	FOLDER_SHOW_ROUTINES
	REQUIRES	INCLUDE_MEM_EDR
	_INIT_ORDER	usrShowInit
}

Component INCLUDE_MEM_EDR_RTP_SHOW {
        NAME            Memory ED&R show routines for RTPs
        SYNOPSIS        This  component can be used to provide show functions for \
				the heap and memory partition instrumentation.
        MODULES         memEdrRtpShow.o
	INIT_RTN	memEdrRtpShowInit();
	PROTOTYPE	STATUS memEdrRtpShowInit (void);
	_CHILDREN	FOLDER_SHOW_ROUTINES
	REQUIRES	INCLUDE_RTP
	_INIT_ORDER	usrShowInit
}

Parameter MEDR_EXTENDED_ENABLE
	{
	NAME		Enable extended memory block info (trace)
	SYNOPSIS	Set this parameter to TRUE to enable logging trace \
			information for each allocated block, but at the cost \
			of increased memory used to store entries in the \
			allocation database. The default setting is FALSE.
        TYPE 		BOOL
        DEFAULT 	FALSE
	}

Parameter MEDR_FILL_FREE_ENABLE
	{
	NAME		Enable filling freed blocks with pattern
	SYNOPSIS	Set this parameter to TRUE to enable pattern-filling \
			queued free blocks. This aids detecting writes into \
			freed buffers. The default setting is FALSE.
        TYPE 		BOOL
        DEFAULT 	FALSE
	}

Parameter MEDR_FREE_QUEUE_LEN
	{
	NAME		Length of the free block queue
	SYNOPSIS	This parameter defines the maximum length of the free \
			queue. When a memory block is freed, instead of \
			immediately returning it to the partition's memory \
			pool, it is kept in a queue. This is useful for \
			detecting references to a memory block after it has \
			been freed. When the queue reaches the maximum length \
			allowed, the blocks are returned to the respective \
			memory pool in a FIFO order. Queuing is disabled when \
			this parameter is 0. Default setting for this \
			parameter is 64.
        TYPE 		uint
        DEFAULT 	64
	}

Parameter MEDR_BLOCK_GUARD_ENABLE
	{
	NAME		Enable allocated block guard zone
	SYNOPSIS	This parameter is used to enable guard signatures in \
			the front and the end of each allocated block. \
			Enabling this feature aids in detecting buffer \
			overruns, underruns, and some heap memory corruption. \
			The default setting is FALSE.
        TYPE 		BOOL
        DEFAULT 	FALSE
	}

Parameter MEDR_POOL_SIZE
	{
	NAME		Size of the memory reserved for database
	SYNOPSIS	This parameter is used to set the size of the memory \
			pool used to maintain the memory block database. The \
			default setting in the kernel is 1MB. The database \
			uses 32 bytes per memory block without extended \
			information enabled, and 64 bytes per block with \
			extended information enabled (call stack trace). \
			This pool is allocated from the kernel heap.
        TYPE 		uint
        DEFAULT 	0x100000
	}
