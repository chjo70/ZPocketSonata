/* 10comp_fsutil.cdf - File System Utils component */

/*
 * Copyright 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
31jan14,elp  Removed SHELL dependencies.
24jan14,ghs  create
*/

/*
DESCRIPTION
This file contains the description for the File System Utils component.
*/

Component INCLUDE_DISK_UTIL 
    {
    NAME            File System and Disk Utilities
    SYNOPSIS        Target-resident File System utilities (cd, copy, ll, mkdir, etc)
    MODULES         usrFsLib.o
    LINK_SYMS       ioHelp
    REQUIRES        INCLUDE_IO_FILE_SYSTEM  \
                    INCLUDE_ANSI_STDIO      \
                    INCLUDE_ANSI_STDLIB     \
                    INCLUDE_ANSI_STRCMP     \
                    INCLUDE_ANSI_STRLEN     \
                    INCLUDE_ANSI_STRNCPY    \
                    INCLUDE_ANSI_TIME       \
                    INCLUDE_MEM_MGR_BASIC   \
                    INCLUDE_POSIX_DIRLIB    \
                    INCLUDE_FORMATTED_OUT_BASIC

    _CHILDREN       FOLDER_STORAGE
    }

Component INCLUDE_TAR
    {
    NAME            File System Backup and Archival
    SYNOPSIS        UNIX-compatible TAR facility
    MODULES         tarLib.o
    LINK_SYMS       tarHelp
    HDR_FILES       tarLib.h
    _CHILDREN       FOLDER_STORAGE
    }

