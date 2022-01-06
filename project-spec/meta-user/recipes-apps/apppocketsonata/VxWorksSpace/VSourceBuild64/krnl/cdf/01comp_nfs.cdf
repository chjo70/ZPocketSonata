/* 01comp_nfs.cdf - NFS Component configuration file */

/*
 * Copyright (c) 2005 - 2007, 2013, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
27feb17,yjl  add requires INCLUDE_BOOT_LINE_INIT for 
             INCLUDE_NFS_MOUNT_ALL (V7STO-781)
22jan17,jbm  Fixing line continuation issues, editing, removed tabs
22feb13,yjl  Fix WIND00403400, To enhance nfs debugging, add some debug
             information
27sep07,dcc  added INCLUDE_IO_FILE_SYSTEM to REQUIRES list
30oct06,mwv  remove INCLUDE_PACKET_POOL_3 due to changes in packet pool
             organization.
19sep06,mwv  fix a type-o in INCLUDE_CORE_NFS_SERVER (WIND00065978)
07sep06,mwv  update HDR_FILES paths
31jul06,mwv  update CONFIGLETTES
24jul06,mwv  modify to support updated stack 
13mar06,pcm  fixed parameters in call to usrNfs3CacheInit() (SPR 118964)
06feb06,pcm  added nfs3StableWriteSet() to INCLUDE_NFS3_CLIENT
16dec05,pcm  merged all NFS cdf files into one.
*/

Parameter NFS2_CLIENT_CACHE_DEFAULT_NUM_LINES
    {
    NAME        Default number of cache lines
    SYNOPSIS    The NFS client implementation uses a persistent cache, which is \
                structured as a multi-line buffer cache. This parameter configures \
                the default number of lines in the NFS v2 client cache. The default \
                value is 16. You can decrease this value to as low as 1, or increase \
                it. You can modify the number of cache lines, either at build time or \
                at run time. To configure the cache at run time, call the function \
                usrNfs2CacheInit( ): usrNfs2CacheInit \
                (UINT32 numLines, UINT32 lineSize, UINT32 options);
    TYPE        UINT32
    DEFAULT     16
    }

Parameter NFS2_CLIENT_CACHE_DEFAULT_LINE_SIZE
    {
    NAME        Default number of bytes in the cache line
    SYNOPSIS    The NFS client implementation uses a persistent cache, which is \
                structured as a multi-line buffer cache. The cache line size \
                must be a power of two. This parameter configures the default size \
                of the NFS v2 client cache line. The default value for this is \
                16384 (16 KB). When combined with the default number of cache lines, \
                this yields a default cache size of 256 KB. You can modify the \
                cache line size, either at build time or at run time. To configure the \
                cache at run time, call the function usrNfs2CacheInit( ): \
                usrNfs2CacheInit (UINT32 numLines, UINT32 lineSize, UINT32 options); \
                Changing the size of the cache does not affect any existing cache. \
                It only impacts future caches.
    TYPE        UINT32
    DEFAULT     16384
    }

Parameter NFS2_CLIENT_CACHE_DEFAULT_OPTIONS
    {
    NAME        Default cache options
    SYNOPSIS    This parameter configures the default options for the NFS v2 client cache. \
                If it is set to 0, the default value, the cache collects the \
                written data and only sends it to the server when the cache line is \
                full, or it needs to be flushed (no options). If set to 1, the cache \
                is write-through. You can modify the cache options, either at \
                build time or at run time. To configure the cache at run time, call the \
                function usrNfs2CacheInit( ): usrNfs2CacheInit (UINT32 numLines, UINT32 lineSize, UINT32 options);
    TYPE        UINT32
    DEFAULT     0
    }

Component INCLUDE_NFS2_CLIENT
    {
    NAME            NFS v2 client
    SYNOPSIS        This component provides nfs2Lib and nfs2Drv, \
                    which provide support for an NFS version two client. Using this \
                    client, you can mount exported NFS (version two) directories to \
                    your VxWorks target. This component requires the INCLUDE_CORE_NFS_CLIENT \
                    component. This component initializes the NFS v2 client at boot time \
                    with a call to nfs2Drv( ), as well as a call to nfsAuthUnixSet( ) as \
                    follows: nfsAuthUnixSet ( sysBootParams.hostName, NFS_USER_ID, \
                    NFS_GROUP_ID, 0, (int *) 0); Values for the NFS_USER_ID and \
                    NFS_GROUP_ID parameters are taken from the corresponding \
                    INCLUDE_CORE_NFS_CLIENT component parameters.
    HDR_FILES       nfs/nfs2Lib.h   \
                    nfs/nfs2Drv.h   \
                    nfs/nfsCommon.h
    CONFIGLETTES    usrNfs.c 
    MODULES         nfs2Lib.o \
                    nfs2Drv.o
    REQUIRES        INCLUDE_CORE_NFS_CLIENT
    INIT_RTN        usrNfsInit (2);                                          \
                    usrNfs2CacheInit (NFS2_CLIENT_CACHE_DEFAULT_NUM_LINES,   \
                                      NFS2_CLIENT_CACHE_DEFAULT_LINE_SIZE,   \
                                      NFS2_CLIENT_CACHE_DEFAULT_OPTIONS);
    CFG_PARAMS      NFS2_CLIENT_CACHE_DEFAULT_NUM_LINES  \
                    NFS2_CLIENT_CACHE_DEFAULT_LINE_SIZE  \
                    NFS2_CLIENT_CACHE_DEFAULT_OPTIONS
    }

Parameter NFS3_CLIENT_CACHE_DEFAULT_NUM_LINES
    {
    NAME        Default number of cache lines
    SYNOPSIS    The NFS client implementation uses a persistent cache, which is structured \
                as a multi-line buffer cache. This parameter configures the default number of \
                lines in the NFS v3 client cache. The default value is 16. The value can be \
                decreased to as low as 1, or increased. You can modify the number of cache \
                lines, either at build time or at run time. To configure the cache at run \
                time, call the function usrNfs3CacheInit( ): usrNfs3CacheInit \
                (UINT32 numLines, UINT32 lineSize, UINT32 options);
    TYPE        UINT32
    DEFAULT     16
    }

Parameter NFS3_CLIENT_CACHE_DEFAULT_LINE_SIZE
    {
    NAME        Default number of bytes in the cache line
    SYNOPSIS    The NFS client implementation uses a persistent cache, which is \
                structured as a multi-line buffer cache. The cache line size \
                must be a power of two. This parameter configures the default size \
                of the NFS v3 client cache line. The default value for this is \
                16384 (16 KB). When combined with the default number of cache lines, \
                this yields a default cache size of 256 KB. You can modify the \
                cache line size, either at build time or at run time. To configure the \
                cache at run time, call the function usrNfs3CacheInit( ): \
                usrNfs3CacheInit (UINT32 numLines, UINT32 lineSize, UINT32 options); \
                Changing the size of the cache does not affect any existing cache. \
                It only impacts future caches.   
    TYPE        UINT32
    DEFAULT     16384
    }

Parameter NFS3_CLIENT_CACHE_DEFAULT_OPTIONS
    {
    NAME        Default cache options
    SYNOPSIS    This parameter configures the default options for the NFS v3 client cache. \
                If it is set to 0, the default value, the cache collects the \
                written data and only sends it to the server when the cache line is \
                full, or it needs to be flushed (no options). If set to 1, the cache \
                is write-through. You can modify the cache options, either at \
                build time or at run time. To configure the cache at run time, call the \
                function usrNfs3CacheInit( ): usrNfs3CacheInit \
                (UINT32 numLines, UINT32 lineSize, UINT32 options);
    TYPE        UINT32
    DEFAULT     0
    }

Component INCLUDE_NFS3_CLIENT
    {
    NAME            NFS v3 client
    SYNOPSIS        The INCLUDE_NFS3_CLIENT component provides the nfs3Lib and \
                    nfs3Drv libraries, which provide support for an NFS version \
                    three client. Using this client, you can mount exported NFS \
                    (version three) directories to your VxWorks target. This \
                    component requires the INCLUDE_CORE_NFS_CLIENT component. \
                    This component initializes the NFS v3 client at boot time \
                    with a call to nfs3Drv( ), as well as a call to \
                    nfsAuthUnixSet( ) as follows: nfsAuthUnixSet \
                    ( sysBootParams.hostName, NFS_USER_ID, NFS_GROUP_ID, 0, \
                    (int *) 0); Values for the NFS_USER_ID and NFS_GROUP_ID \
                    parameters are taken from the corresponding \
                    INCLUDE_CORE_NFS_CLIENT component parameters. 
    HDR_FILES       nfs/nfs3Lib.h   \
                    nfs/nfs3Drv.h   \
                    nfs/nfsCommon.h
    CONFIGLETTES    usrNfs.c
    MODULES         nfs3Lib.o \
                    nfs3Drv.o
    REQUIRES        INCLUDE_CORE_NFS_CLIENT
    INIT_RTN        usrNfsInit (3);                                          \
                    usrNfs3CacheInit (NFS3_CLIENT_CACHE_DEFAULT_NUM_LINES,   \
                                      NFS3_CLIENT_CACHE_DEFAULT_LINE_SIZE,   \
                                      NFS3_CLIENT_CACHE_DEFAULT_OPTIONS);    \
                    nfs3StableWriteSet (0);
    CFG_PARAMS      NFS3_CLIENT_CACHE_DEFAULT_NUM_LINES  \
                    NFS3_CLIENT_CACHE_DEFAULT_LINE_SIZE  \
                    NFS3_CLIENT_CACHE_DEFAULT_OPTIONS
    }

Component INCLUDE_NFS_CLIENT_ALL
    {
    NAME            NFS client all
    SYNOPSIS        Including this component is equivalent to selecting both \
                    INCLUDE_NFS2_CLIENT and INCLUDE_NFS3_CLIENT because it \
                    provides support for NFS version 2 and version 3.
    REQUIRES        INCLUDE_NFS2_CLIENT INCLUDE_NFS3_CLIENT
    }

Component INCLUDE_CORE_NFS_CLIENT 
    {
    NAME            Core NFS client
    SYNOPSIS        This component includes nfsCommon, a library that provides \
                    core functionality for NFS clients. This library also \
                    provides parameters that you can use to specify the NFS user ID, \
                    group identifier, and the maximum length of the pathname for a file.
    HDR_FILES       nfs/nfsCommon.h
    MODULES         nfsCommon.o
    REQUIRES        INCLUDE_IO_FILE_SYSTEM INCLUDE_RPC
    CFG_PARAMS      NFS_USER_ID NFS_GROUP_ID NFS_MAXPATH
    }

Parameter NFS_USER_ID
    {
    NAME            User identifier for NFS access
    SYNOPSIS        Use this parameter to set the user identifier for NFS access. \
                    By default, it is set to 2001.
    TYPE            int
    DEFAULT         2001
    }

Parameter NFS_GROUP_ID
    {
    NAME            Group identifier for NFS access
    SYNOPSIS        Use this parameter to set the group identifier for NFS access. \
                    By default, it is set to 100.
    TYPE            int
    DEFAULT         100
    }

Parameter NFS_MAXPATH
    {
    NAME            Maximum file path length
    SYNOPSIS        Indicates maximum length of a file path excluding the file \
                    name. By default, it is set to 255. 
    DEFAULT         255
    }

Component INCLUDE_NFS_MOUNT_ALL
    {
    NAME            NFS mount all
    SYNOPSIS        This component mounts all remote file systems at boot time.
    CONFIGLETTES    usrNfs.c
    INIT_RTN        usrNfsMountAll();
    REQUIRES        INCLUDE_NFS_CLIENT_ALL \
                    INCLUDE_BOOT_LINE_INIT
    CFG_PARAMS      GROUP_EXPORTS
    }

Parameter GROUP_EXPORTS
    {
    NAME        Remove check for GroupName during MountAll
    SYNOPSIS    An NFS server can specify that an exported file system is intended \
                for a particular group of clients. Before mounting an exported \
                file system, a client typically checks that it is a group member. \
                If the client is not a group member, it does not mount the file \
                system. To configure the client to skip this check, set this \
                parameter to TRUE. The default value (FALSE) ensures that the \
                check occurs.
    TYPE        BOOL
    DEFAULT     FALSE
    }

Component INCLUDE_NFS2_SERVER
    {
    NAME            NFS server v2
    SYNOPSIS        This component includes a Network File System (version 2) \
                    server. This component provides the nfs2dLib and \
                    mount1Lib libraries.
    HDR_FILES       nfs/nfs2dLib.h \
                    nfs/mountd.h
    CONFIGLETTES    usrNfsd.c
    MODULES         nfs2dLib.o \
                    mount1Lib.o
    INIT_RTN        usrNfsdInit (1);
    REQUIRES        INCLUDE_CORE_NFS_SERVER INCLUDE_NFS_SERVER_INSTALL
    }

Component INCLUDE_NFS3_SERVER
    {
    NAME            NFS server V3
    SYNOPSIS        This component includes the Network File System (version 3) \
                    server. This component provides the nfs3dLib and mount3Lib \
                    libraries.
    HDR_FILES       nfs/nfs3dLib.h
    CONFIGLETTES    usrNfsd.c
    MODULES         nfs3dLib.o
    INIT_RTN        usrNfsdInit (2);
    REQUIRES        INCLUDE_CORE_NFS_SERVER INCLUDE_NFS_SERVER_INSTALL
    }

Component INCLUDE_NFS_SERVER_ALL
    {
    NAME            NFS server All
    SYNOPSIS        Including this component is equivalent to selecting both \
                    INCLUDE_NFS3_SERVER and INCLUDE_NFS2_SERVER.
    HDR_FILES       nfs/nfsd.h
    REQUIRES        INCLUDE_NFS3_SERVER INCLUDE_NFS2_SERVER \
                    INCLUDE_NFS_SERVER_INSTALL
    }

Component INCLUDE_CORE_NFS_SERVER
   {
   NAME         NFS server
   SYNOPSIS     This component provides nfsd, the library that supplies the NFS \
                server daemon initialization routines. For more information on \
                these routines, see the nfsd reference entry. This component also \
                supplies configuration parameters that set basic configuration \
                values for the server. \
                NOTE: The NFS server maintains a reply cache of up to 64 recently \
                transmitted reply messages. The purpose of this cache is to deal \
                with RPC retransmissions. If the XID of an incoming NFS request \
                matches that of a previously replied message, the cached reply is \
                sent back instead of actually executing the NFS request. Each \
                entry in the server reply cache requires 8800 bytes for the \
                entry itself and 48 bytes for each cache node. Thus, if there are \
                three entries in the cache, the memory usage is 26,544 \
                bytes, which is (3 * 8800) + (3 * 48) bytes. If there are the full \
                64 entries in the cache, the memory usage is 566,272 bytes. \
                If you think you have noticed a memory leak in NFS, consider \
                whether this memory use accounts for the discrepancy.
   HDR_FILES    nfs/nfsd.h
   MODULES      nfsd.o
   REQUIRES     INCLUDE_RPC
   CFG_PARAMS   NFS_USER_ID NFS_GROUP_ID NFS_MAXPATH NFS_MAXFILENAME
   }

Parameter NFS_MAXPATH
    {
    NAME        Maximum file path length
    SYNOPSIS    Indicates maximum length of a file path excluding the file name. \
                By default, it is set to 255. The maximum value of this parameter \
                is 1024.
    DEFAULT     255
    }

Parameter NFS_USER_ID
    {
    NAME        User identifier for NFS access
    SYNOPSIS    This parameter sets the user identifier for NFS access. By \
                default, it is set to 2001.
    TYPE        int
    DEFAULT     2001
    }

Parameter NFS_MAXFILENAME
    {
    NAME        Maximum file name length
    SYNOPSIS    Indicates the maximum length of a file name. If a file name \
                is longer than this value then it is truncated before it is \
                returned to the client. This parameter must be set carefully \
                because it affects the amount of memory allocated by the \
                server. Valid values range from 1 to 99.
    DEFAULT     40
    }

Parameter NFS_GROUP_ID
    {
    NAME        Group identifier for NFS access
    SYNOPSIS    This parameter sets the group identifier for NFS access. By \
                default, it is set to 100.
    TYPE        int
    DEFAULT     100
    }

Component INCLUDE_NFS_SERVER_INSTALL
   {
   NAME             Install NFS server
   SYNOPSIS         This component installs the Network File System (NFS) \
                    server(s). 
   CONFIGLETTES     usrNfsd.c
   INIT_RTN         usrNfsdInitInternal();
   REQUIRES         INCLUDE_CORE_NFS_SERVER
   }

Parameter NFS_DEBUG_LEVEL
    {
    NAME            NFS debug level
    SYNOPSIS        This parameter sets the Network File System (NFS) debug \
                    level. When this value greater than the corresponding \
                    ERROR or NORMAL information level, debug information \
                    can be output. NFS_NONE_DEBUG 0, NFS_ERROR_DEBUG 1, \
                    NFS_WARNING_DEBUG 2, NFS_NORMAL_DEBUG 3, \
                    NFS_VERBOSE_DEBUG 4.
    TYPE            int
    DEFAULT         0
    }

Component INCLUDE_NFS_DEBUG
    {
    NAME            NFS debug
    SYNOPSIS        This component implements the Network File System (NFS) \
                    debug information. 
    HDR_FILES       nfs/nfsDebug.h
    MODULES         nfsDebug.o
    INIT_RTN        nfsDebugInit(NFS_DEBUG_LEVEL);
    CFG_PARAMS      NFS_DEBUG_LEVEL
    }

Folder FOLDER_NFS
    {
    NAME        NFS components
    SYNOPSIS    This folder contains components and parameters used to configure \
                the Network File System (NFS).
    _CHILDREN   FOLDER_FILESYSTEM
    CHILDREN    INCLUDE_CORE_NFS_CLIENT \
                INCLUDE_CORE_NFS_SERVER \
                INCLUDE_NFS_MOUNT_ALL \
                INCLUDE_NFS_CLIENT_ALL \
                INCLUDE_NFS3_CLIENT    \
                INCLUDE_NFS2_CLIENT   \
                INCLUDE_NFS_SERVER_ALL \
                INCLUDE_NFS2_SERVER \
                INCLUDE_NFS3_SERVER \
                INCLUDE_NFS_DEBUG \
                INCLUDE_NFS_SERVER_INSTALL
    }

