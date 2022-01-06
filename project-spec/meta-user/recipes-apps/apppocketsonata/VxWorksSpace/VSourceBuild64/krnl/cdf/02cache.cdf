/* 02cache.cdf - cache component description file */

/*
 * Copyright (c) 2012, 2013, 2016, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
17apr17,own  Minor changes to SYNOPSIS and NAME descriptors (F8862).
02dec16,kk   fixed V7COR-4700, make INCLUDE_CACHE_ENABLE hidden for SMP
21apr16,emj  CERT: Update to produce partially linked objects (US79607)
01a,16sep13,x_z  created. 
*/

Folder FOLDER_MEMORY {
	NAME		Memory
	SYNOPSIS	This folder hosts memory components.
	CHILDREN	INCLUDE_MEMORY_CONFIG	\
			    INCLUDE_CACHE_SUPPORT	\
			    INCLUDE_CACHE_ENABLE    \
			    INCLUDE_USER_RESERVED_MEMORY
}

Component INCLUDE_CACHE_SUPPORT {
	NAME		Cache support
	SYNOPSIS	This component is used to include cache support.
	INIT_RTN	cacheLibInit (USER_I_CACHE_MODE, USER_D_CACHE_MODE);
	_CHILDREN   FOLDER_MEMORY
	SOURCE		$(WIND_BASE)/target/src/os/mm
#ifndef _WRS_CONFIG_CERT_KERNEL_OBJECT
	MODULES		cacheLib.o
#else
        _REQUIRES INCLUDE_KERNEL
#endif
	CFG_PARAMS	USER_I_CACHE_MODE USER_D_CACHE_MODE
	HDR_FILES	cacheLib.h
}

Component INCLUDE_CACHE_ENABLE {
	NAME		    Enable caches
	SYNOPSIS	    This component can be used to optionally enable caches.
	CONFIGLETTES	usrCache.c
	INIT_RTN	    usrCacheEnable ();
	CFG_PARAMS	    USER_I_CACHE_ENABLE USER_D_CACHE_ENABLE
	REQUIRES	    INCLUDE_CACHE_SUPPORT
	INCLUDE_WHEN	INCLUDE_CACHE_SUPPORT
	HDR_FILES	    cacheLib.h
#ifdef _WRS_CONFIG_SMP
	_CHILDREN       FOLDER_HIDDEN
#else
	_CHILDREN       FOLDER_MEMORY
#endif
}

Parameter USER_D_CACHE_MODE {
	NAME		Data cache mode
	DEFAULT		CACHE_WRITETHROUGH
}

Parameter USER_I_CACHE_MODE {
	NAME		Instruction cache mode
	DEFAULT		CACHE_WRITETHROUGH
}

Parameter USER_I_CACHE_ENABLE {
	NAME		Enable instruction cache
	TYPE		exists
	DEFAULT		TRUE
}

Parameter USER_D_CACHE_ENABLE {
	NAME		Enable data cache
	TYPE		exists
	DEFAULT		TRUE
}


