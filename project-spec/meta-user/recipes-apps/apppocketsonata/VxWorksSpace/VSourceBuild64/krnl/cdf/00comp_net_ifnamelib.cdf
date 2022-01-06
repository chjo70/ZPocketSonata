/* 00comp_net_ifnamelib.cdf - Component configuration file */

/*
 * Copyright (c) 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */

/*
modification history
--------------------
16aug16,mca  created
*/

Component INCLUDE_IFNAMELIB {
    NAME            ifNameLib
    SYNOPSIS        Mappings between network interface names and indexes.
    REQUIRES        INCLUDE_SOCKLIB
    MODULES         ifNameLib.o
    LINK_SYMS       if_indextoname
}
