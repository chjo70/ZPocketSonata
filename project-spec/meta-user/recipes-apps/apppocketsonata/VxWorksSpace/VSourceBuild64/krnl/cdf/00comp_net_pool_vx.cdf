/* 00comp_net_pool.cdf - Component configuration file */

/* Copyright 2002-2006 Wind River Systems, Inc. */

/*
modification history
--------------------
01p,12sep06,dlk  Added HDR_FILES netLib.h to INCLUDE_NET_POOL.
01o,09sep06,dlk  Decrease number of 64-byte clusters in data pool,
                 increase number of 128-byte clusters.
01n,08sep06,dlk  Decrease default M_BLK/CL_BLK/cluster numbers.
                 Remove INCLUDE_DS_ALLOC.
01m,25jun06,dlk  Added INCLUDE_DS_ALLOC.
01l,26jun05,dlk  Default to zero nominal size 2048 system pool clusters.
                 Change NUM_SYS_MBLKS and NUM_SYS_CLBLKS defaults to 20.
01k,06may04,vvv  fixed values of MBLKS and CLBLKS (SPR #89778)
01j,18nov03,rhe  Added INCLUDE_NETBUFPOOL reuired for netBufLib
01i,12sep03,vvv  updated configlette path
01h,08sep03,vvv  merged from ACCORDION_BASE6_MERGE_BASELINE
01g,16may03,ppp  changing 1024 size cluster buffer from 1140 to 1144
01f,14may03,vvv  removed adv_net.h
01e,10jan03,ann  merged in Team-F1's changes for IPSec
                 - changed the default count for the clusters (4K-64K) 
                   to zero
                 - added support for large clusters (4K-64K)
01d,27jun02,ppp  merged changes from t3
01c,12jun02,pas  added system pool sizes
01b,06may02,ham  changed in response to netBufLib rollback.
01a,15feb02,ham  wrote.
*/

Component INCLUDE_NET_POOL {
	NAME		Network Stack Memory Pool Configuration
	SYNOPSIS	Network Stack Memory Pool Configuration
	HDR_FILES	netBufLib.h netLib.h
	CONFIGLETTES	usrNetPool.c
	INIT_RTN	usrNetPoolConfig ();
	CFG_PARAMS	NUM_SYS_MBLKS   \
			NUM_SYS_CLBLKS  \
			PMA_SYSPOOL     \
			PMS_SYSPOOL     \
			SIZ_SYS_16      \
			NUM_SYS_16      \
			PMA_SYS_16      \
			PMS_SYS_16      \
			SIZ_SYS_32      \
			NUM_SYS_32      \
			PMA_SYS_32      \
			PMS_SYS_32      \
			SIZ_SYS_64      \
			NUM_SYS_64      \
			PMA_SYS_64      \
			PMS_SYS_64      \
			SIZ_SYS_128     \
			NUM_SYS_128     \
			PMA_SYS_128     \
			PMS_SYS_128     \
			SIZ_SYS_256     \
			NUM_SYS_256     \
			PMA_SYS_256     \
			PMS_SYS_256     \
			SIZ_SYS_512     \
			NUM_SYS_512     \
			PMA_SYS_512     \
			PMS_SYS_512     \
			SIZ_SYS_1024    \
			NUM_SYS_1024    \
			PMA_SYS_1024    \
			PMS_SYS_1024    \
			SIZ_SYS_2048    \
			NUM_SYS_2048    \
			PMA_SYS_2048    \
			PMS_SYS_2048    \
			NUM_DAT_MBLKS   \
			NUM_DAT_CLBLKS  \
			PMA_DATPOOL     \
			PMS_DATPOOL     \
			NUM_DAT_64      \
			PMA_DAT_64      \
			PMS_DAT_64      \
			NUM_DAT_128     \
			PMA_DAT_128     \
			PMS_DAT_128     \
			NUM_DAT_256     \
			PMA_DAT_256     \
			PMS_DAT_256     \
			NUM_DAT_512     \
			PMA_DAT_512     \
			PMS_DAT_512     \
			NUM_DAT_1024    \
			PMA_DAT_1024    \
			PMS_DAT_1024    \
			NUM_DAT_2048    \
			PMA_DAT_2048    \
			PMS_DAT_2048	\
			NUM_DAT_4096    \
			PMA_DAT_4096    \
			PMS_DAT_4096	\
			NUM_DAT_8192    \
			PMA_DAT_8192    \
			PMS_DAT_8192	\
			NUM_DAT_16384    \
			PMA_DAT_16384    \
			PMS_DAT_16384	\
			NUM_DAT_32768    \
			PMA_DAT_32768    \
			PMS_DAT_32768	\
			NUM_DAT_65536    \
			PMA_DAT_65536    \
			PMS_DAT_65536	
	REQUIRES	INCLUDE_NETBUFLIB  \
	                INCLUDE_NETBUFPOOL
}

Parameter NUM_SYS_MBLKS {
	NAME		NUM_SYS_MBLKS
	SYNOPSIS	# of MBLKS in System Pool
        DEFAULT         2
	TYPE		uint
}

Parameter NUM_SYS_CLBLKS {
	NAME		NUM_SYS_CLBLKS
	SYNOPSIS	# of CLBLKS in System Pool
        DEFAULT         2
	TYPE		uint
}

Parameter PMA_SYSPOOL {
        NAME            PMA_SYSPOOL
        SYNOPSIS        Preallocated Memory Address (memArea) of System Pool
        DEFAULT         0
        TYPE            uint
}

Parameter PMS_SYSPOOL {
        NAME            PMS_SYSPOOL
        SYNOPSIS        Preallocated Memory Size (memSize) of System Pool
        DEFAULT         0
        TYPE            uint
}

Parameter SIZ_SYS_16 {
	NAME		size of 16 byte clusters in System Pool
	SYNOPSIS	size of 16 byte clusters in System Pool
        DEFAULT         20
	TYPE		uint
}

Parameter NUM_SYS_16 {
	NAME		# of 16 byte clusters in System Pool
	SYNOPSIS	# of 16 byte clusters in System Pool
        DEFAULT         2
	TYPE		uint
}

Parameter PMA_SYS_16 {
	NAME		memArea of 16 byte clusters in System Pool
	SYNOPSIS	Preallocated Memory Address (memArea) of 16 byte clusters in System Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMS_SYS_16 {
	NAME		memSize of 16 byte clusters in System Pool
	SYNOPSIS	Preallocated Memory Size (memSize) of 16 byte clusters in System Pool
        DEFAULT         0
	TYPE		uint
}

Parameter SIZ_SYS_32 {
	NAME		size of 32 byte clusters in System Pool
	SYNOPSIS	size of 32 byte clusters in System Pool
        DEFAULT         44
	TYPE		uint
}

Parameter NUM_SYS_32 {
	NAME		# of 32 byte clusters in System Pool
	SYNOPSIS	# of 32 byte clusters in System Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMA_SYS_32 {
	NAME		memArea of 32 byte clusters in System Pool
	SYNOPSIS	Preallocated Memory Address (memArea) of 32 byte clusters in System Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMS_SYS_32 {
	NAME		memSize of 32 byte clusters in System Pool
	SYNOPSIS	Preallocated Memory Size (memSize) of 32 byte clusters in System Pool
        DEFAULT         0
	TYPE		uint
}

Parameter SIZ_SYS_64 {
	NAME		size of 64 byte clusters in System Pool
	SYNOPSIS	size of 64 byte clusters in System Pool
        DEFAULT         96
	TYPE		uint
}

Parameter NUM_SYS_64 {
	NAME		# of 64 byte clusters in System Pool
	SYNOPSIS	# of 64 byte clusters in System Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMA_SYS_64 {
	NAME		memArea of 64 byte clusters in System Pool
	SYNOPSIS	Preallocated Memory Address (memArea) of 64 byte clusters in System Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMS_SYS_64 {
	NAME		memSize of 64 byte clusters in System Pool
	SYNOPSIS	Preallocated Memory Size (memSize) of 64 byte clusters in System Pool
        DEFAULT         0
	TYPE		uint
}

Parameter SIZ_SYS_128 {
	NAME		size of 128 byte clusters in System Pool
	SYNOPSIS	size of 128 byte clusters in System Pool
        DEFAULT         172
	TYPE		uint
}

Parameter NUM_SYS_128 {
	NAME		# of 128 byte clusters in System Pool
	SYNOPSIS	# of 128 byte clusters in System Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMA_SYS_128 {
	NAME		memArea of 128 byte clusters in System Pool
	SYNOPSIS	Preallocated Memory Address (memArea) of 128 byte clusters in System Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMS_SYS_128 {
	NAME		memSize of 128 byte clusters in System Pool
	SYNOPSIS	Preallocated Memory Size (memSize) of 128 byte clusters in System Pool
        DEFAULT         0
	TYPE		uint
}


Parameter SIZ_SYS_256 {
	NAME		size of 256 byte clusters in System Pool
	SYNOPSIS	size of 256 byte clusters in System Pool
        DEFAULT         292
	TYPE		uint
}

Parameter NUM_SYS_256 {
	NAME		# of 256 byte clusters in System Pool
	SYNOPSIS	# of 256 byte clusters in System Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMA_SYS_256 {
	NAME		memArea of 256 byte clusters in System Pool
	SYNOPSIS	Preallocated Memory Address (memArea) of 256 byte clusters in System Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMS_SYS_256 {
	NAME		memSize of 256 byte clusters in System Pool
	SYNOPSIS	Preallocated Memory Size (memSize) of 256 byte clusters in System Pool
        DEFAULT         0
	TYPE		uint
}

Parameter SIZ_SYS_512 {
	NAME		size of 512 byte clusters in System Pool
	SYNOPSIS	size of 512 byte clusters in System Pool
        DEFAULT         664
	TYPE		uint
}

Parameter NUM_SYS_512 {
	NAME		# of 512 byte clusters in System Pool
	SYNOPSIS	# of 512 byte clusters in System Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMA_SYS_512 {
	NAME		memArea of 512 byte clusters in System Pool
	SYNOPSIS	Preallocated Memory Address (memArea) of 512 byte clusters in System Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMS_SYS_512 {
	NAME		memSize of 512 byte clusters in System Pool
	SYNOPSIS	Preallocated Memory Size (memSize) of 512 byte clusters in System Pool
        DEFAULT         0
	TYPE		uint
}

Parameter SIZ_SYS_1024 {
	NAME		size of 1024 byte clusters in System Pool
	SYNOPSIS	size of 1024 byte clusters in System Pool
        DEFAULT         1144
	TYPE		uint
}

Parameter NUM_SYS_1024 {
	NAME		# of 1024 byte clusters in System Pool
	SYNOPSIS	# of 1024 byte clusters in System Pool
        DEFAULT         2
	TYPE		uint
}

Parameter PMA_SYS_1024 {
	NAME		memArea of 1024 byte clusters in System Pool
	SYNOPSIS	Preallocated Memory Address (memArea) of 1024 byte clusters in System Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMS_SYS_1024 {
	NAME		memSize of 1024 byte clusters in System Pool
	SYNOPSIS	Preallocated Memory Size (memSize) of 1024 byte clusters in System Pool
        DEFAULT         0
	TYPE		uint
}

Parameter SIZ_SYS_2048 {
	NAME		size of 2048 byte clusters in System Pool
	SYNOPSIS	size of 2048 byte clusters in System Pool
        DEFAULT         2048
	TYPE		uint
}

Parameter NUM_SYS_2048 {
	NAME		# of 2048 byte clusters in System Pool
	SYNOPSIS	# of 2048 byte clusters in System Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMA_SYS_2048 {
	NAME		memArea of 2048 byte clusters in System Pool
	SYNOPSIS	Preallocated Memory Address (memArea) of 2048 byte clusters in System Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMS_SYS_2048 {
	NAME		memSize of 2048 byte clusters in System Pool
	SYNOPSIS	Preallocated Memory Size (memSize) of 2048 byte clusters in System Pool
        DEFAULT         0
	TYPE		uint
}


Parameter NUM_DAT_MBLKS {
	NAME		NUM_DAT_MBLKS
	SYNOPSIS	# of MBLKS in Data Pool
        DEFAULT         NUM_DAT_CLBLKS
	TYPE		uint
}

Parameter NUM_DAT_CLBLKS {
	NAME		NUM_DAT_CLBLKS
	SYNOPSIS	# of CLBLKS in Data Pool
	DEFAULT		NUM_DAT_64   + \
			NUM_DAT_128  + \
			NUM_DAT_256  + \
			NUM_DAT_512  + \
			NUM_DAT_1024 + \
			NUM_DAT_2048 + \
			NUM_DAT_4096 + \
			NUM_DAT_8192 + \
			NUM_DAT_16384 + \
			NUM_DAT_32768 + \
			NUM_DAT_65536
	TYPE		uint
}

Parameter NUM_DAT_64 {
	NAME		# of 64 byte clusters in Data Pool
	SYNOPSIS	# of 64 byte clusters in Data Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMA_DAT_64 {
	NAME		memArea of 64 byte clusters in Data Pool
	SYNOPSIS	Preallocated Memory Address (memArea) of 64 byte clusters in Data Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMS_DAT_64 {
	NAME		memSize of 64 byte clusters in Data Pool
	SYNOPSIS	Preallocated Memory Size (memSize) of 64 byte clusters in Data Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMA_DATPOOL {
        NAME            PMA_DATPOOL
        SYNOPSIS        Preallocated Memory Address (memArea) of Data Pool
        DEFAULT         0
        TYPE            uint
}

Parameter PMS_DATPOOL {
        NAME            PMS_DATPOOL
        SYNOPSIS        Preallocated Memory Size (memSize) of Data Pool
        DEFAULT         0
        TYPE            uint
}

Parameter NUM_DAT_128 {
	NAME		# of 128 byte clusters in Data Pool
	SYNOPSIS	# of 128 byte clusters in Data Pool
        DEFAULT         128
	TYPE		uint
}

Parameter PMA_DAT_128 {
	NAME		memArea of 128 byte clusters in Data Pool
	SYNOPSIS	Preallocated Memory Address (memArea) of 128 byte clusters in Data Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMS_DAT_128 {
	NAME		memSize of 128 byte clusters in Data Pool
	SYNOPSIS	Preallocated Memory Size (memSize) of 128 byte clusters in Data Pool
        DEFAULT         0
	TYPE		uint
}

Parameter NUM_DAT_256 {
	NAME		# of 256 byte clusters in Data Pool
	SYNOPSIS	# of 256 byte clusters in Data Pool
        DEFAULT         4
	TYPE		uint
}

Parameter PMA_DAT_256 {
	NAME		memArea of 256 byte clusters in Data Pool
	SYNOPSIS	Preallocated Memory Address (memArea) of 256 byte clusters in Data Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMS_DAT_256 {
	NAME		memSize of 256 byte clusters in Data Pool
	SYNOPSIS	Preallocated Memory Size (memSize) of 256 byte clusters in Data Pool
        DEFAULT         0
	TYPE		uint
}

Parameter NUM_DAT_512 {
	NAME		# of 512 byte clusters in Data Pool
	SYNOPSIS	# of 512 byte clusters in Data Pool
        DEFAULT         4
	TYPE		uint
}

Parameter PMA_DAT_512 {
	NAME		memArea of 512 byte clusters in Data Pool
	SYNOPSIS	Preallocated Memory Address (memArea) of 512 byte clusters in Data Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMS_DAT_512 {
	NAME		memSize of 512 byte clusters in Data Pool
	SYNOPSIS	Preallocated Memory Size (memSize) of 512 byte clusters in Data Pool
        DEFAULT         0
	TYPE		uint
}

Parameter NUM_DAT_1024 {
	NAME		# of 1024 byte clusters in Data Pool
	SYNOPSIS	# of 1024 byte clusters in Data Pool
        DEFAULT         4
	TYPE		uint
}

Parameter PMA_DAT_1024 {
	NAME		memArea of 1024 byte clusters in Data Pool
	SYNOPSIS	Preallocated Memory Address (memArea) of 1024 byte clusters in Data Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMS_DAT_1024 {
	NAME		memSize of 1024 byte clusters in Data Pool
	SYNOPSIS	Preallocated Memory Size (memSize) of 1024 byte clusters in Data Pool
        DEFAULT         0
	TYPE		uint
}

Parameter NUM_DAT_2048 {
	NAME		# of 2048 byte clusters in Data Pool
	SYNOPSIS	# of 2048 byte clusters in Data Pool
        DEFAULT         4
	TYPE		uint
}

Parameter PMA_DAT_2048 {
	NAME		memArea of 2048 byte clusters in Data Pool
	SYNOPSIS	Preallocated Memory Address (memArea) of 2048 byte clusters in Data Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMS_DAT_2048 {
	NAME		memSize of 2048 byte clusters in Data Pool
	SYNOPSIS	Preallocated Memory Size (memSize) of 2048 byte clusters in Data Pool
        DEFAULT         0
	TYPE		uint
}

Parameter NUM_DAT_4096 {
	NAME		# of 4096 byte clusters in Data Pool
	SYNOPSIS	# of 4096 byte clusters in Data Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMA_DAT_4096 {
	NAME		memArea of 4096 byte clusters in Data Pool
	SYNOPSIS	Preallocated Memory Address (memArea) of 4096 byte clusters in Data Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMS_DAT_4096 {
	NAME		memSize of 4096 byte clusters in Data Pool
	SYNOPSIS	Preallocated Memory Size (memSize) of 4096 byte clusters in Data Pool
        DEFAULT         0
	TYPE		uint
}
Parameter NUM_DAT_8192 {
	NAME		# of 8192 byte clusters in Data Pool
	SYNOPSIS	# of 8192 byte clusters in Data Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMA_DAT_8192 {
	NAME		memArea of 8192 byte clusters in Data Pool
	SYNOPSIS	Preallocated Memory Address (memArea) of 8192 byte clusters in Data Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMS_DAT_8192 {
	NAME		memSize of 8192 byte clusters in Data Pool
	SYNOPSIS	Preallocated Memory Size (memSize) of 8192 byte clusters in Data Pool
        DEFAULT         0
	TYPE		uint
}
Parameter NUM_DAT_16384 {
	NAME		# of 16384 byte clusters in Data Pool
	SYNOPSIS	# of 16384 byte clusters in Data Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMA_DAT_16384 {
	NAME		memArea of 16384 byte clusters in Data Pool
	SYNOPSIS	Preallocated Memory Address (memArea) of 16384 byte clusters in Data Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMS_DAT_16384 {
	NAME		memSize of 16384 byte clusters in Data Pool
	SYNOPSIS	Preallocated Memory Size (memSize) of 16384 byte clusters in Data Pool
        DEFAULT         0
	TYPE		uint
}
Parameter NUM_DAT_32768 {
	NAME		# of 32768 byte clusters in Data Pool
	SYNOPSIS	# of 32768 byte clusters in Data Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMA_DAT_32768 {
	NAME		memArea of 32768 byte clusters in Data Pool
	SYNOPSIS	Preallocated Memory Address (memArea) of 32768 byte clusters in Data Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMS_DAT_32768 {
	NAME		memSize of 32768 byte clusters in Data Pool
	SYNOPSIS	Preallocated Memory Size (memSize) of 32768 byte clusters in Data Pool
        DEFAULT         0
	TYPE		uint
}
Parameter NUM_DAT_65536 {
	NAME		# of 65536 byte clusters in Data Pool
	SYNOPSIS	# of 65536 byte clusters in Data Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMA_DAT_65536 {
	NAME		memArea of 65536 byte clusters in Data Pool
	SYNOPSIS	Preallocated Memory Address (memArea) of 65536 byte clusters in Data Pool
        DEFAULT         0
	TYPE		uint
}

Parameter PMS_DAT_65536 {
	NAME		memSize of 65536 byte clusters in Data Pool
	SYNOPSIS	Preallocated Memory Size (memSize) of 65536 byte clusters in Data Pool
        DEFAULT         0
	TYPE		uint
}
