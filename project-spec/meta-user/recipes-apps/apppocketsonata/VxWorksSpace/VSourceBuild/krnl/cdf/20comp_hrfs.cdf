/* 20comp_hrfs.cdf - Highly Reliable File System component */

/*
 * Copyright 2014, 2016, 2018 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
17jan18,ghs  add error handle parameters (F10082)
27dec16,yjl  to change the priority of tHrfsCommit is configurable (V7STO-758)
17feb14,ghs  re-write
*/

/*
DESCRIPTION
This file contains the description for Highly Reliable File System component.
*/

/* HRFS - Highly Reliable File System component */

Parameter HRFS_DEFAULT_MAX_FILES
    {
    NAME            Default Max Open Files (HRFS)
    SYNOPSIS        Maximum number of files that can be open on an HRFS volume
    TYPE            int
    DEFAULT         10
    }

Parameter HRFS_DEFAULT_MAX_BUFFERS
    {
    NAME            Default Max Buffers (HRFS)
    SYNOPSIS        Maximum number of buffers
    TYPE            int
    DEFAULT         16
    }

Parameter HRFS_DEFAULT_COMMIT_TASK_PRIORITY
    {
    NAME           Default Commit Task Priority (HRFS)
    SYNOPSIS       Default commit task priority
    TYPE           int
    DEFAULT        2
    }

Parameter HRFS_DEFAULT_ERROR_HANDLE_POLICY
    {
    NAME           HRFS Default Error Handle Policy
    SYNOPSIS       HRFS default error handle policy, the value could be: \
                   HRFS_ERR_HANDLE_STOP_IO - (0), \
                   HRFS_ERR_HANDLE_STOP_IO_SILENT - (1), \
                   HRFS_ERR_HANDLE_TO_EDR - (2), \
                   HRFS_ERR_HANDLE_TO_USER_FUNC - (3), \
                   HRFS_ERR_HANDLE_IGNORE - (4)
    TYPE           int
    DEFAULT        HRFS_ERR_HANDLE_STOP_IO
    }

Parameter HRFS_DEFAULT_ERROR_HANDLE_USER_FUNC
    {
    NAME           HRFS User Defined Error Handle Routine
    SYNOPSIS       HRFS user defined error handle routine, \
                   only valid when HRFS_DEFAULT_ERROR_HANDLE_POLICY is \
                   HRFS_ERR_HANDLE_TO_USER_FUNC
    TYPE           FUNCPTR
    DEFAULT        NULL
    }

Component INCLUDE_HRFS_DEFAULT_WRITE_MODE
    {
    NAME            HRFS Default Write Mode
    SYNOPSIS        Commits performed every write
    REQUIRES        INCLUDE_HRFS
    }

Component INCLUDE_HRFS_HISPEED_WRITE_MODE
    {
    NAME            HRFS High Speed Write Mode
    SYNOPSIS        Commits performed when cache usage is over 40% or when 5 seconds have elapsed, if current transaction still active
    REQUIRES        INCLUDE_HRFS
    }

Component INCLUDE_HRFS
    {
    NAME            Highly Reliable File System
    SYNOPSIS        Highly Reliable File System
    INIT_RTN        usrHrfsInit (HRFS_DEFAULT_MAX_BUFFERS,     \
                                 HRFS_DEFAULT_MAX_FILES,       \
                                 HRFS_DEFAULT_COMMIT_TASK_PRIORITY);
    CONFIGLETTES    usrHrfs.c
    HDR_FILES       hrFsLib.h
    EXCLUDES        INCLUDE_HRFS_READONLY
    CFG_PARAMS      HRFS_DEFAULT_MAX_BUFFERS     \
                    HRFS_DEFAULT_MAX_FILES       \
                    HRFS_DEFAULT_COMMIT_TASK_PRIORITY \
                    HRFS_DEFAULT_ERROR_HANDLE_POLICY \
                    HRFS_DEFAULT_ERROR_HANDLE_USER_FUNC
    REQUIRES        INCLUDE_XBD                  \
                    INCLUDE_IO_FILE_SYSTEM       \
                    INCLUDE_FS_MONITOR           \
                    SELECT_HRFS_WRITE_MODE_INIT
    }

Component INCLUDE_HRFS_READONLY
    {
    NAME            Read-Only Highly Reliable File System
    SYNOPSIS        Read-Only Highly Reliable File System
    INIT_RTN        usrHrfsInit (HRFS_DEFAULT_MAX_BUFFERS,     \
                                 HRFS_DEFAULT_MAX_FILES,       \
                                 HRFS_DEFAULT_COMMIT_TASK_PRIORITY);
    CONFIGLETTES    usrHrfs.c
    HDR_FILES       hrFsLib.h
    CFG_PARAMS      HRFS_DEFAULT_MAX_BUFFERS    \
                    HRFS_DEFAULT_MAX_FILES      \
                    HRFS_DEFAULT_COMMIT_TASK_PRIORITY \
                    HRFS_DEFAULT_ERROR_HANDLE_POLICY \
                    HRFS_DEFAULT_ERROR_HANDLE_USER_FUNC
    EXCLUDES        SELECT_HRFS_WRITE_MODE_INIT \
                    INCLUDE_HRFS
    REQUIRES        INCLUDE_XBD                 \
                    INCLUDE_IO_FILE_SYSTEM      \
                    INCLUDE_FS_MONITOR
    }

Component INCLUDE_HRFS_ACCESS_TIMESTAMP
    {
    NAME            Highly Reliable File System Access Time Stamp
    SYNOPSIS        Support access time stamp on HRFS volumes
    REQUIRES        INCLUDE_HRFS
    }

Component INCLUDE_HRFS_FORMAT
    {
    NAME            HRFS Format
    SYNOPSIS        Module for formatting backing media for HRFS
    MODULES         hrfsFormatLib.o
    INIT_RTN        hrfsFormatLibInit ();
    HDR_FILES       hrFsLib.h
    REQUIRES        INCLUDE_RAWFS \
                    INCLUDE_HRFS
    INIT_AFTER      INCLUDE_RAWFS
    }

Component INCLUDE_HRFS_CHKDSK
    {
    NAME            HRFS File System Consistency Checker
    SYNOPSIS        HRFS File System Consistency Checker
    MODULES         hrfsChkDskLib.o
    LINK_SYMS       hrfsChkDsk
    REQUIRES        INCLUDE_HRFS
    }

Selection SELECT_HRFS_WRITE_MODE_INIT
    {
    NAME            select HRFS work mode
    SYNOPSIS        default mode or high speed mode
    COUNT           1-1
    CHILDREN        INCLUDE_HRFS_DEFAULT_WRITE_MODE \
                    INCLUDE_HRFS_HISPEED_WRITE_MODE
    DEFAULTS        INCLUDE_HRFS_DEFAULT_WRITE_MODE
    }

Folder FOLDER_HRFS
    {
    NAME            Highly Reliable File System Components (HRFS)
    SYNOPSIS        Highly Reliable File System, and related components
    _CHILDREN       FOLDER_FILESYSTEM
    CHILDREN        SELECT_HRFS_WRITE_MODE_INIT   \
                    INCLUDE_HRFS                  \
                    INCLUDE_HRFS_READONLY         \
                    INCLUDE_HRFS_ACCESS_TIMESTAMP \
                    INCLUDE_HRFS_FORMAT           \
                    INCLUDE_HRFS_CHKDSK
    DEFAULTS        INCLUDE_HRFS
                    SELECT_HRFS_WRITE_MODE_INIT
    }

