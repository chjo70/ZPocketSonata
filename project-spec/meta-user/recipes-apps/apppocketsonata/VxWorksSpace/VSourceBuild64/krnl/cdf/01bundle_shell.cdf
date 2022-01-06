/* 01bundle_shell.cdf - VxWorks kernel shell component bundles */

/*
 * Copyright (c) 2003-2004, 2006-2007, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
17apr17,jla  Clean up NAME and SYNOPSIS text. Adjust modhistory format. (F8862)
18jul07,v_r  Added the persistent shell history mechanism (req
             CQ:WIND00005098).
10may06,tfo  remove FOLDER_BUNDLES
06apr04,bpn  Added INCLUDE_SHELL_EMACS_MODE and INCLUDE_SHELL_VI_MODE
             components.
11feb04,bpn  Add these components to FOLDER_BUNDLES.
20nov03,fle  written
*/

Bundle BUNDLE_STANDALONE_SHELL {
	NAME		Standalone kernel shell
	SYNOPSIS	This bundle provides kernel shell tools with \
			a standalone symbol table.
	HELP		shell
	COMPONENTS	INCLUDE_STANDALONE_SYM_TBL \
			INCLUDE_SHELL \
			INCLUDE_SHELL_EMACS_MODE \
			INCLUDE_SHELL_VI_MODE \
			INCLUDE_SHELL_HISTORY_FILE \
			INCLUDE_LOADER \
			INCLUDE_DISK_UTIL \
			INCLUDE_SHOW_ROUTINES \
			INCLUDE_STAT_SYM_TBL \
			INCLUDE_DEBUG \
			INCLUDE_UNLOADER \
			INCLUDE_MEM_SHOW \
			INCLUDE_SYM_TBL_SHOW \
			INCLUDE_CPLUS 
}

Bundle BUNDLE_NET_SHELL {
	NAME		Network kernel shell
	SYNOPSIS	This bundle provides kernel shell tools with \
			a networking symbol table.
	HELP		shell
	COMPONENTS	INCLUDE_NET_SYM_TBL \
			INCLUDE_SHELL \
			INCLUDE_SHELL_EMACS_MODE \
			INCLUDE_SHELL_VI_MODE \
			INCLUDE_SHELL_HISTORY_FILE \
			INCLUDE_LOADER \
			INCLUDE_DISK_UTIL \
			INCLUDE_SHOW_ROUTINES \
			INCLUDE_STAT_SYM_TBL \
			INCLUDE_DEBUG \
			INCLUDE_UNLOADER \
			INCLUDE_MEM_SHOW \
			INCLUDE_SYM_TBL_SHOW \
			INCLUDE_CPLUS
}
