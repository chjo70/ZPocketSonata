/* 01symbols.cdf - symbol table components */

/* 
 * Copyright (c) 2013-2014 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
*/ 

/*
modification history
--------------------
21oct14,rlp  Added a CDF dependency between INCLUDE_SYM_TBL and
	     INCLUDE_SEM_READ_WRITE components (V7COR-1666).
04mar14,ten  Added ctype.h as needed header file for INCLUDE_NET_SYM_TBL
03sep13,rlp  Written from version 01s of 01loader.cdf.


DESCRIPTION

This file contains the definition for the symbol table components.
*/

Component INCLUDE_SYM_TBL_SHOW {
	NAME		symbol table show routine
	SYNOPSIS	Routines to display information about symbols and symbol tables
	MODULES		symShow.o
	INIT_RTN	symShowInit ();
	_CHILDREN	FOLDER_SHOW_ROUTINES
	_INIT_ORDER	usrShowInit
	INIT_BEFORE	INCLUDE_VM_SHOW
	INCLUDE_WHEN	INCLUDE_SYM_TBL \
			INCLUDE_SHOW_ROUTINES
}

Folder FOLDER_SYMTBL {
	NAME		symbol table components
	SYNOPSIS	VxWorks Symbol table management
	_CHILDREN	FOLDER_TOOLS
	CHILDREN	INCLUDE_STAT_SYM_TBL	\
			INCLUDE_CPLUS_DEMANGLER	\
			INCLUDE_SYM_TBL \
			FOLDER_SYM_TBL_INIT
	DEFAULTS	INCLUDE_SYM_TBL \
			INCLUDE_SYM_TBL_INIT
}

Component INCLUDE_SYM_TBL {
	NAME		target symbol table
	SYNOPSIS	Set of routines to manipulate symbols and symbol tables
	MODULES		symLib.o
	INIT_RTN	symLibInit ();
	HDR_FILES	symLib.h
	_INIT_ORDER	usrKernelExtraInit
	INIT_AFTER	INCLUDE_HASH
	REQUIRES	INCLUDE_SEM_READ_WRITE
}

Component INCLUDE_STAT_SYM_TBL {
	NAME		error status table
	SYNOPSIS	Table of error strings for perror()
	CONFIGLETTES	usrStatTbl.c
	MODULES		statTbl.o
	INIT_RTN	usrStatTblInit ();
	CFG_PARAMS	STAT_TBL_HASH_SIZE_LOG2
	HDR_FILES	sysLib.h symLib.h stdio.h sysSymTbl.h
	HELP		errnoLib perror
}

Folder FOLDER_SYM_TBL_INIT {
	NAME		symbol table initialization components
	SYNOPSIS	Initialize symbol table
	CHILDREN 	INCLUDE_SYM_TBL_INIT \
			SELECT_SYM_TBL_INIT
	DEFAULTS	INCLUDE_SYM_TBL_INIT \
			SELECT_SYM_TBL_INIT
}

Component INCLUDE_SYM_TBL_INIT {
	NAME 		system symbol table initialization
	SYNOPSIS	initialize system symbol table
	CFG_PARAMS	SYM_TBL_HASH_SIZE_LOG2
	CONFIGLETTES	usrSysSymTbl.c
	INIT_RTN	usrSysSymTblInit ();
	REQUIRES	INCLUDE_SYM_TBL \
			SELECT_SYM_TBL_INIT
}

Selection SELECT_SYM_TBL_INIT {
	NAME		select symbol table initialization
	SYNOPSIS	Method for populating the system symbol table
	COUNT		1-1
	CHILDREN	INCLUDE_STANDALONE_SYM_TBL \
			INCLUDE_NET_SYM_TBL
	DEFAULTS	INCLUDE_STANDALONE_SYM_TBL
}

Component INCLUDE_STANDALONE_SYM_TBL {
	NAME		built-in symbol table
	SYNOPSIS	Preferred method if not booting from the network
	CONFIGLETTES	usrStandalone.c
	INIT_RTN	usrStandaloneInit ();
	HDR_FILES	sysLib.h symLib.h stdio.h sysSymTbl.h
	HELP		loadLib symLib
	REQUIRES	INCLUDE_SYM_TBL \
			INCLUDE_SYM_TBL_INIT
}

Component INCLUDE_NET_SYM_TBL {
	NAME		downloaded symbol table
	SYNOPSIS	Preferred method if booting from the network
	CONFIGLETTES	usrLoadSym.c
	INIT_RTN	usrLoadSyms ();
	HDR_FILES	loadLib.h string.h sysLib.h sysSymTbl.h symLib.h \
			stdio.h fcntl.h ctype.h
	REQUIRES	INCLUDE_LOADER \
			INCLUDE_BOOT_LINE_INIT \
			INCLUDE_SYM_TBL \
			INCLUDE_SYM_TBL_INIT
	HELP		loadLib symLib
}

Parameter SYM_TBL_HASH_SIZE_LOG2 {
	NAME		symbol table hash size (as a power of 2)
	SYNOPSIS	The size of the symbol hash table is specified as a power of two. For example, if SYM_TBL_HASH_SIZE_LOG2 is 8, a 256-entry hash table is created.
	TYPE		uint
	DEFAULT		8
}

Parameter STAT_TBL_HASH_SIZE_LOG2 {
	NAME		error status table hash size (as a power of 2)
	SYNOPSIS	The size of the error status hash table is specified as a power of two. For example, if STAT_TBL_HASH_SIZE_LOG2 is 6, a 64-entry hash table is created.
	TYPE		uint
	DEFAULT		6
}

InitGroup usrSymTblInit {
	INIT_RTN	usrSymTblInit ();
	SYNOPSIS	Enable onboard symbol tables
	_INIT_ORDER	usrToolsInit
	INIT_AFTER	usrLoaderInit
	INIT_BEFORE	INCLUDE_TRIGGERING
	INIT_ORDER	INCLUDE_SYM_TBL_INIT \
			INCLUDE_NET_SYM_TBL \
			INCLUDE_PASSFS_SYM_TBL \
			INCLUDE_STANDALONE_SYM_TBL \
			INCLUDE_STAT_SYM_TBL
}

