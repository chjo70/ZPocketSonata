/* 10memDesc.cdf - memory descriptor stub file */

/*
 * Copyright (c) 2013-2014, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
14jun17,mjn  text updates (F8862)
27mar14,cww  added LOCAL_MEM_LOCAL_ADRS and SYS_MEM_DESC_NUM from core and arch
19aug13,x_z  created
*/

#ifdef _WRS_CONFIG_USE_MEMDESC
Component INCLUDE_MEM_DESC {
    NAME            Memory descriptor stub
    SYNOPSIS        This component provides the sysMemDescGet() function for the kernel to \
                    use during initialization to determine available RAM regions on the board \
                    when initializing the physical page pool.
    CONFIGLETTES    usrMemDesc.c
    CFG_PARAMS	    SYS_MEM_DESC_NUM
    _CHILDREN       FOLDER_MEMORY
}

Parameter SYS_MEM_DESC_NUM {
    NAME            Number of system memory descriptors
    SYNOPSIS        This parameter specifies the maximum number of system memory descriptors \
                    available to describe continuous blocks of physical memory.
    DEFAULT         8
}
#endif /* _WRS_CONFIG_USE_MEMDESC */

Parameter LOCAL_MEM_LOCAL_ADRS {
    NAME        Local memory address
    SYNOPSIS    This parameter specifies the the start of the on-board memory area.
    DEFAULT     0x0
}

