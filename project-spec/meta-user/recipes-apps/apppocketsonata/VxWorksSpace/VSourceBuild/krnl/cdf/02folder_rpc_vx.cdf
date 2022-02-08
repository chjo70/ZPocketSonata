/* 00folder_net_rpc.cdf - Folder configuration file */

/* Copyright 2002, 2014 Wind River Systems, Inc. */

/*
modification history
--------------------
24jan14,ghs  move to FOLDER_SERVICE
20jan14,zan  moving FOLDER_RPC to FOLDER_NFS
21feb02,ham  wrote.
*/

Folder FOLDER_RPC {
    NAME                RPC
	SYNOPSIS			This folder contains components and parameters that \
						can be used to implement the Remote Call Procedure.
    CHILDREN            INCLUDE_RPC      \
                        INCLUDE_XDR      \
                        INCLUDE_XDR_BOOL_T
    _CHILDREN           FOLDER_SERVICE
}
