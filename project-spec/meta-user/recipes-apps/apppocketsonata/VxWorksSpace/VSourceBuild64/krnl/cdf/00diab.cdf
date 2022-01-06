/* 00diab.cdf - VxWorks components */

/*
 * Copyright (c) 2013, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history            
--------------------
18feb15,pmr  CERT restriction
23oct13,mcm  Created from content in the legacy 01vxWorks.cdf file
*/

/*
DESCRIPTION
This file contains descriptions for VxWorks Diab components 
*/

#ifndef _WRS_CONFIG_CERT
Component INCLUDE_DIAB_INTRINSICS {
        NAME            Diab compiler support routines
        SYNOPSIS        Compiler support routines that may be needed by \
                        dynamically downloaded object modules generated \
                        with the Diab toolchain. Note that this applies to C \
                        code only, as C++ binaries are not compatible between \
                        toolchains.
        CONFIGLETTES    intrinsics.c
}
#endif /* _WRS_CONFIG_CERT */
