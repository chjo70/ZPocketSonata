/* 02shell_commands.cdf - Kernel shell commands components */

/*
 * Copyright (c) 2005-2007, 2011, 2012, 2014, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
10nov17,sub  Fix to include tipShellCmdInit in prjConfig.c (V7COR-5399)
17apr17,jla  Add list of commands included with each synopsis. 
             Fix whitespace (F8862)
10apr17,own  Made INCLUDE_RTP_APPL_INIT_CMD_SHELL_SCRIPT a child of FOLDER_RTP_STARTUP_FACILITY (F8862).
27may14,rlp  Fixed VxDBG dependency (V7COR-1214).
06may14,rlp  Made RTP commands available if RTP support is enabled.
29apr14,rlp  Fixed IPNET dependency (V7COR-1073).
29jan14,pad  Added user management command component (US19799).
09jan14,h_k  moved INCLUDE_RTP_APPL_INIT_CMD_SHELL_SCRIPT from 01rtp.cdf.
25jan12,cww  Fix typo in INCLUDE_MEM_EDR_SHELL_CMD synopsis (WIND00048161)
27sep11,rlp  Added INCLUDE_SPY_SHELL_CMD - CQID: WIND00285819.
01apr11,jmp  Added INCLUDE_TIP_CMD & INCLUDE_WRLOAD_CMD (CQ:WIND00144662).
14sep07,vhe  Improved component description as part of CQ:WIND00102457 fix
18jul07,v_r  Added shell history saving/loading mechanism (req CQ:WIND00005098).
12jan06,zl   added INCLUDE_MAPPED_FILES_SHOW_SHELL_CMD
31jan05,bpn  Written from version 01q,25jan05,bpn of 01shell.cdf.
*/

/*
DESCRIPTION

This file contains the definition for the commands components for the 
shell command interpreter.

The folder FOLDER_SHELL_CMD is defined in 01shell.cdf. 
*/

Component INCLUDE_DISK_UTIL_SHELL_CMD {
	NAME		File system shell commands
	SYNOPSIS	This component provides shell commands related to the \
			file system: cd, file list, pwd, file copy, file move, \
			file remove, file create, mkdir, file concat, more. \
			Aliases: ls (file list), cp (file copy), mv (file \
			move), rm (file remove), mkdir (file create -d), cat \
			(file concat).
	PROTOTYPE	IMPORT STATUS usrFsShellCmdInit ();
	MODULES		usrFsShellCmd.o
	INIT_RTN	usrFsShellCmdInit ();
	REQUIRES	INCLUDE_DISK_UTIL INCLUDE_SHELL_INTERP_CMD
	INCLUDE_WHEN	INCLUDE_DISK_UTIL INCLUDE_SHELL_INTERP_CMD
	_CHILDREN	FOLDER_SHELL_CMD
}

Component INCLUDE_EDR_SHELL_CMD {
	NAME		ED&R shell commands
	SYNOPSIS	This component provides shell commands related to \
			error detection and reporting: \
			edr show, edr show fatal, edr show info, \
			edr show interrupt, edr show init, edr show reboot, \
			edr show boot, edr show kernel, edr show user, edr \
			show rtp, edr clear. \
			Aliases: edrs (edr show), edrc (edr clear).
	PROTOTYPE	IMPORT STATUS edrShellCmdInit ();
	MODULES		edrShellCmd.o
	INIT_RTN	edrShellCmdInit ();
	REQUIRES	INCLUDE_EDR_SHOW INCLUDE_SHELL_INTERP_CMD
	INCLUDE_WHEN	INCLUDE_EDR_SHOW INCLUDE_SHELL_INTERP_CMD
	_CHILDREN	FOLDER_SHELL_CMD
}

Component INCLUDE_TASK_SHELL_CMD {
	NAME		Task shell commands
	SYNOPSIS	This component provides shell commands related to \
			tasks: task, task info, task spawn, task stack, \
			task delete, task default, task regs, task suspend, \
			task resume, task hooks, task stop, task wait. \
			Aliases: edrs (edr show), edrc (edr clear).
	PROTOTYPE	IMPORT STATUS taskShellCmdInit ();
	MODULES		taskShellCmd.o
	INIT_RTN	taskShellCmdInit ();
	REQUIRES	INCLUDE_SHELL_INTERP_CMD
	INCLUDE_WHEN	INCLUDE_SHELL_INTERP_CMD
	_CHILDREN	FOLDER_SHELL_CMD
}

#ifdef	_WRS_CONFIG_VXDBG
Component INCLUDE_DEBUG_SHELL_CMD {
	NAME		Debug shell commands
	SYNOPSIS	This component provides shell commands related to \
			debugging: task trace, task continue, task stepover, \
			task step, mem list, bp, dprintf. \
			Aliases: l (mem list), bd (bp -u), bdall (bp -u *), \
			b (bp), bi (bp -v), dp (dprintf), tt (task trace), s \
			(task step), so (task stepover), c (task continue), \
			cret (task continue -r).
	PROTOTYPE	IMPORT STATUS dbgShellCmdInit ();
	MODULES		dbgShellCmd.o
	INIT_RTN	dbgShellCmdInit ();
	REQUIRES	INCLUDE_DEBUG INCLUDE_SHELL_INTERP_CMD
	INCLUDE_WHEN	INCLUDE_DEBUG INCLUDE_SHELL_INTERP_CMD
	_CHILDREN	FOLDER_SHELL_CMD
}
#endif	/* _WRS_CONFIG_VXDBG */

Component INCLUDE_SYM_SHELL_CMD {
	NAME		Symbol shell commands
	SYNOPSIS	This component provides shell commands related to \
			symbol access: printf, set symbol, set, demangle, \
			lookup. Aliases: lkup (lookup), lkAddr (lookup -a).
	PROTOTYPE	IMPORT STATUS symShellCmdInit ();
	MODULES		symShellCmd.o
	INIT_RTN	symShellCmdInit ();
	REQUIRES	INCLUDE_SYM_TBL INCLUDE_SHELL_INTERP_CMD
	INCLUDE_WHEN	INCLUDE_SYM_TBL INCLUDE_SHELL_INTERP_CMD
	_CHILDREN	FOLDER_SHELL_CMD
}

Component INCLUDE_VM_SHOW_SHELL_CMD {
	NAME		Virtual memory show shell command
	SYNOPSIS	This component provides the 'vm context' shell command \
			which displays information on the virtual memory \
			context.
	MODULES		vmShowShellCmd.o
	PROTOTYPE	STATUS vmShowShellCmdInit (void);
	INIT_RTN	vmShowShellCmdInit ();
	HDR_FILES	vmLib.h
	REQUIRES	INCLUDE_VM_SHOW INCLUDE_SHELL_INTERP_CMD 
	INCLUDE_WHEN	INCLUDE_VM_SHOW INCLUDE_SHELL_INTERP_CMD
	_CHILDREN	FOLDER_SHELL_CMD
}

Component INCLUDE_ADR_SPACE_SHELL_CMD {
	NAME		Address space shell command
	SYNOPSIS	This component provides the 'adrsp' shell command \
			which displays information on the address space.
	MODULES		adrSpaceShellCmd.o
	PROTOTYPE	STATUS adrSpaceShellCmdInit (void);
	INIT_RTN	adrSpaceShellCmdInit ();
	HDR_FILES	adrSpaceLib.h
	REQUIRES	INCLUDE_ADR_SPACE_SHOW INCLUDE_SHELL_INTERP_CMD
	INCLUDE_WHEN	INCLUDE_ADR_SPACE_SHOW INCLUDE_SHELL_INTERP_CMD
	_CHILDREN	FOLDER_SHELL_CMD
}

Component INCLUDE_SHARED_DATA_SHOW_SHELL_CMD {
	NAME		Shared data show commands
	SYNOPSIS	This component provides shared data show shell \
			commands: sd, sd info.
	MODULES		sdShowShellCmd.o
	PROTOTYPE	STATUS sdShowShellCmdInit (void);
	INIT_RTN	sdShowShellCmdInit ();
	HDR_FILES	sdLib.h
	REQUIRES	INCLUDE_SHARED_DATA_SHOW INCLUDE_SHELL_INTERP_CMD
	INCLUDE_WHEN	INCLUDE_SHARED_DATA_SHOW INCLUDE_SHELL_INTERP_CMD
	_CHILDREN	FOLDER_SHELL_CMD
}

Component INCLUDE_MAPPED_FILES_SHOW_SHELL_CMD {
	NAME		Mapped files show command
	SYNOPSIS	This component provides the 'mmap list' shell command \
			which displays information on memory mapped objects.
	MODULES		mmanShowShellCmd.o
	PROTOTYPE	STATUS mmanShowShellCmdInit (void);
	INIT_RTN	mmanShowShellCmdInit ();
	REQUIRES	INCLUDE_MAPPED_FILES_SHOW INCLUDE_SHELL_INTERP_CMD
	INCLUDE_WHEN	INCLUDE_MAPPED_FILES_SHOW INCLUDE_SHELL_INTERP_CMD
	_CHILDREN	FOLDER_SHELL_CMD
}

Component INCLUDE_MEM_EDR_SHELL_CMD {
	NAME		Memory ED&R shell commands
	SYNOPSIS	This component provides memory error detection and \
			reporting shell commands: mem part list, mem block \
			list, mem block mark, mem block unmark, mem queue flush.
	MODULES		memEdrShellCmd.o
	PROTOTYPE	STATUS memEdrShellCmdInit (void);
	INIT_RTN	memEdrShellCmdInit ();
	REQUIRES	INCLUDE_MEM_EDR_SHOW INCLUDE_SHELL_INTERP_CMD
	INCLUDE_WHEN	INCLUDE_MEM_EDR_SHOW INCLUDE_SHELL_INTERP_CMD
	_CHILDREN	FOLDER_SHELL_CMD
}

#ifdef	_WRS_CONFIG_RTP
Component INCLUDE_MEM_EDR_RTP_SHELL_CMD {
	NAME		Memory ED&R shell commands for processes
	SYNOPSIS	This component provides memory error detection and \
			reporting shell commands related to processes: mem rtp \
			part list, mem rtp block list, mem rtp block mark, mem \
			rtp block unmark.
	MODULES		memEdrRtpShellCmd.o
	PROTOTYPE	STATUS memEdrRtpShellCmdInit (void);
	INIT_RTN	memEdrRtpShellCmdInit ();
	REQUIRES	INCLUDE_MEM_EDR_RTP_SHOW INCLUDE_SHELL_INTERP_CMD
	INCLUDE_WHEN	INCLUDE_MEM_EDR_RTP_SHOW INCLUDE_SHELL_INTERP_CMD
	_CHILDREN	FOLDER_SHELL_CMD
}
#endif	/* _WRS_CONFIG_RTP */

Component INCLUDE_MODULE_SHELL_CMD {
	NAME		Target loader shell commands
	SYNOPSIS	This component provides target loader shell commands: \
			module, module info, module load. \
			Aliases: ld (module load).
	PROTOTYPE	extern STATUS moduleShellCmdInit (void);
	INIT_RTN	moduleShellCmdInit();
	MODULES		moduleShellCmd.o
	REQUIRES	INCLUDE_LOADER INCLUDE_SHELL_INTERP_CMD
	INCLUDE_WHEN	INCLUDE_LOADER INCLUDE_SHELL_INTERP_CMD
	_CHILDREN	FOLDER_SHELL_CMD
}

Component INCLUDE_UNLOADER_SHELL_CMD {
	NAME		Unloader shell commands
	SYNOPSIS	This component provides the 'module unload' shell \
			command, and its alias 'unld', which is used to unload \
			an object module from the kernel.
	PROTOTYPE	extern STATUS unloadShellCmdInit (void);
	INIT_RTN	unloadShellCmdInit();
	MODULES		unloadShellCmd.o
	REQUIRES	INCLUDE_UNLOADER INCLUDE_MODULE_SHELL_CMD
	INCLUDE_WHEN	INCLUDE_UNLOADER INCLUDE_SHELL_INTERP_CMD
	_CHILDREN	FOLDER_SHELL_CMD
}

Component INCLUDE_SHL_SHELL_CMD {
	NAME		Shared library shell commands
	SYNOPSIS	This component provides shared library shell commands: \
			shl, shl info.
	MODULES		shlShellCmd.o
	INIT_RTN	shlShellCmdInit ();
	HDR_FILES	shlLib.h
	REQUIRES	INCLUDE_SHL INCLUDE_SHELL_INTERP_CMD
	INCLUDE_WHEN	INCLUDE_SHL INCLUDE_SHELL_INTERP_CMD
	_CHILDREN	FOLDER_SHELL_CMD
}

#ifdef	_WRS_CONFIG_RTP
Component INCLUDE_RTP_SHELL_CMD {
	NAME		Process shell commands
	SYNOPSIS	This component provides shell commands related to \
			real-time processes (RTPs): \
			rtp, rtp stop, rtp continue, rtp delete, \
			rtp exec, rtp attach, rtp detach, rtp symbols add, rtp \
			symbols remove, rtp symbols override, set cwc, rtp \
			background, rtp foreground.
			Aliases: rtps (rtp stop), rtpc (rtp continue), rtpd \
			(rtp delete), kill (rtp delete), rtpi (rtp task), run \
			(rtp exec), jobs (rtp attach), fg (rtp foreground), bg \
			(rtp background), attach (rtp attach), detach (rtp \
			detach), symsAdd (rtp symbols add), symsRm (rtp \
			symbols remove), symsOvrd (rtp symbols override).
	MODULES		rtpShellCmd.o
	INIT_RTN	rtpShellCmdInit ();
	HDR_FILES	rtpLib.h
	REQUIRES	INCLUDE_RTP INCLUDE_SHELL_INTERP_CMD
	INCLUDE_WHEN	INCLUDE_RTP INCLUDE_SHELL_INTERP_CMD
	_CHILDREN	FOLDER_SHELL_CMD
}

Component INCLUDE_RTP_SHOW_SHELL_CMD {
	NAME		Process show commands
	SYNOPSIS	This component provides real-time process (RTP) show \
			shell commands: rtp info, rtp list, rtp shl, syscall \
			hooks, rtp hooks, rtp meminfo, syscalls, syscall \
			monitor. \
			Aliases: info (rtp info), shls (rtp shl), sc \
			(syscalls), scm (syscall monitor), rtpm (rtp meminfo), \
			ps (rtp list).
	MODULES		rtpShowShellCmd.o
	PROTOTYPE	STATUS rtpShowShellCmdInit (void);
	INIT_RTN	rtpShowShellCmdInit ();
	HDR_FILES	rtpLib.h
	REQUIRES	INCLUDE_RTP_SHELL_CMD
	INCLUDE_WHEN	INCLUDE_RTP_SHELL_CMD INCLUDE_RTP_SHOW	
	_CHILDREN	FOLDER_SHELL_CMD
}
#endif	/* _WRS_CONFIG_RTP */

Component INCLUDE_HISTORY_FILE_SHELL_CMD {
	NAME		History shell commands
	SYNOPSIS	This component provides shell commands for saving and \
			loading shell command history: history save, history \
			load.
	MODULES		histShellCmd.o
	INIT_RTN	histShellCmdInit ();
	HDR_FILES	private/shellHistLibP.h
	REQUIRES	INCLUDE_SHELL_HISTORY_FILE
	INCLUDE_WHEN	INCLUDE_SHELL_INTERP_CMD INCLUDE_SHELL_HISTORY_FILE
	_CHILDREN	FOLDER_SHELL_CMD
}

Component INCLUDE_SPY_SHELL_CMD {
	NAME		Spy CPU activity shell commands
	SYNOPSIS	This component provides shell commands for the spy \
			library: spy, spy stop, spy report, spy clkstart, spy \
			clkstop. Aliases: spy start (spy).
	MODULES		spyShellCmd.o
	INIT_RTN	spyShellCmdInit ();
	HDR_FILES	private/shellCmdP.h
	REQUIRES	INCLUDE_SPY INCLUDE_SHELL_INTERP_CMD
	INCLUDE_WHEN	INCLUDE_SPY INCLUDE_SHELL_INTERP_CMD
	_CHILDREN	FOLDER_SHELL_CMD
}

#ifdef	_WRS_CONFIG_IPNET_COREIP
Component INCLUDE_TIP_CMD {
	NAME		Serial line connection shell command
	SYNOPSIS	This component provides the 'tip' shell command which \
			is used to connect to one or several remote systems \
			over serial lines.
	MODULES		tipShellCmd.o
	INIT_RTN	tipShellCmdInit ();
	HDR_FILES	private/shellCmdP.h
	REQUIRES	INCLUDE_TIP INCLUDE_SHELL_INTERP_CMD
	INCLUDE_WHEN	INCLUDE_TIP INCLUDE_SHELL_INTERP_CMD
	_CHILDREN	FOLDER_SHELL_CMD
}
#endif

Component INCLUDE_WRLOAD_CMD {
	NAME		Wind River multiprocessor boot loader shell command
	SYNOPSIS	This component provides the 'wrload' shell command \
			used for loading and starting an image in a \
			multiprocessor system.
	MODULES		wrloadShellCmd.o
	INIT_RTN	wrloadShellCmdInit ();
	HDR_FILES	private/shellCmdP.h
	REQUIRES	INCLUDE_WRLOAD INCLUDE_SHELL_INTERP_CMD
	INCLUDE_WHEN	INCLUDE_WRLOAD INCLUDE_SHELL_INTERP_CMD
	_CHILDREN	FOLDER_SHELL_CMD
}

#ifdef	_WRS_CONFIG_RTP
Component INCLUDE_RTP_APPL_INIT_CMD_SHELL_SCRIPT {
	NAME		8. Shell script 
	SYNOPSIS	This component allows you to launch a real-time \
			process (RTP) by executing a shell script.
	_CHILDREN	FOLDER_RTP_STARTUP_FACILITY
	CONFIGLETTES	usrRtpAppInitCmdShellScript.c
	INIT_RTN	usrRtpAppInitCmdShellScriptRun (RTP_APPL_CMD_SCRIPT_FILE);
	CFG_PARAMS	RTP_APPL_CMD_SCRIPT_FILE
	REQUIRES	INCLUDE_RTP INCLUDE_STARTUP_SCRIPT
	_INIT_ORDER	usrRoot
	HELP		RTP Application Startup facility
}

Parameter RTP_APPL_CMD_SCRIPT_FILE {
	NAME		Pathname
	SYNOPSIS	This parameter provides the full pathname of the file \
                        that contains the startup script for launching the \
			real-time process (RTP).
	TYPE		string
	DEFAULT		""
}
#endif	/* _WRS_CONFIG_RTP */

#ifdef _WRS_CONFIG_USER_MANAGEMENT
Component INCLUDE_USER_MGT_SHELL_CMD {
	NAME		User management shell commands
	SYNOPSIS	This component provides shell commands for the \
			management of users: user add, user del, user mod, \
			passwd, whoami. \
			Aliases: useradd (user add), userdel (user del), \
			usermod (user mod).
	MODULES		userMgtShellCmd.o
	INIT_RTN	userMgtShellCmdInit();
	INCLUDE_WHEN	INCLUDE_USER_IDENTIFICATION INCLUDE_SHELL_INTERP_CMD
	_CHILDREN	FOLDER_SHELL_CMD
}
#endif /* _WRS_CONFIG_USER_MANAGEMENT */

InitGroup usrShellCmdInit {
	INIT_RTN	usrShellCmdInit ();
	SYNOPSIS	The kernel shell commands initialization sequence
#if defined(_WRS_CONFIG_IPNET_COREIP)
	INIT_ORDER	INCLUDE_TASK_SHELL_CMD \
			INCLUDE_DEBUG_SHELL_CMD \
			INCLUDE_SYM_SHELL_CMD \
			INCLUDE_DISK_UTIL_SHELL_CMD \
			INCLUDE_EDR_SHELL_CMD \
			INCLUDE_VM_SHOW_SHELL_CMD \
			INCLUDE_ADR_SPACE_SHELL_CMD \
			INCLUDE_SHARED_DATA_SHOW_SHELL_CMD \
			INCLUDE_MAPPED_FILES_SHOW_SHELL_CMD \
			INCLUDE_MEM_EDR_SHELL_CMD \
			INCLUDE_MEM_EDR_RTP_SHELL_CMD \
			INCLUDE_MODULE_SHELL_CMD \
			INCLUDE_UNLOADER_SHELL_CMD \
			INCLUDE_RTP_SHELL_CMD \
			INCLUDE_RTP_SHOW_SHELL_CMD \
			INCLUDE_SHL_SHELL_CMD \
			INCLUDE_HISTORY_FILE_SHELL_CMD \
			INCLUDE_SPY_SHELL_CMD \
			INCLUDE_TIP_CMD	\
			INCLUDE_WRLOAD_CMD
#else
	INIT_ORDER	INCLUDE_TASK_SHELL_CMD \
			INCLUDE_DEBUG_SHELL_CMD \
			INCLUDE_SYM_SHELL_CMD \
			INCLUDE_DISK_UTIL_SHELL_CMD \
			INCLUDE_EDR_SHELL_CMD \
			INCLUDE_VM_SHOW_SHELL_CMD \
			INCLUDE_ADR_SPACE_SHELL_CMD \
			INCLUDE_SHARED_DATA_SHOW_SHELL_CMD \
			INCLUDE_MAPPED_FILES_SHOW_SHELL_CMD \
			INCLUDE_MEM_EDR_SHELL_CMD \
			INCLUDE_MEM_EDR_RTP_SHELL_CMD \
			INCLUDE_MODULE_SHELL_CMD \
			INCLUDE_UNLOADER_SHELL_CMD \
			INCLUDE_RTP_SHELL_CMD \
			INCLUDE_RTP_SHOW_SHELL_CMD \
			INCLUDE_SHL_SHELL_CMD \
			INCLUDE_HISTORY_FILE_SHELL_CMD \
			INCLUDE_SPY_SHELL_CMD \
			INCLUDE_WRLOAD_CMD
#endif /*if defined(_WRS_CONFIG_IPNET_COREIP)*/
	_INIT_ORDER	usrShellInit
	INIT_AFTER	INCLUDE_SHELL_INTERP_CMD
	INIT_BEFORE	INCLUDE_STARTUP_SCRIPT
}

#ifdef _WRS_CONFIG_USER_MANAGEMENT
InitGroup usrShellCmdInit {
	INIT_ORDER += INCLUDE_USER_MGT_SHELL_CMD
}
#endif /* _WRS_CONFIG_USER_MANAGEMENT */
