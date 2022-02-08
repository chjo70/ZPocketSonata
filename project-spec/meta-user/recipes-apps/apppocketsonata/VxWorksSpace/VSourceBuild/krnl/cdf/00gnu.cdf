/* 00gnu.cdf - VxWorks components */

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
20feb14,gvm  Fix for VXW7-1908
23oct13,mcm  Created from content in legacy 01vxWorks.cdf
*/

/*
DESCRIPTION
This file contains descriptions for VxWorks GNU components 
*/

Component INCLUDE_GNU_INTRINSICS {
        NAME            GNU compiler support routines
        SYNOPSIS        Compiler support routines that may be needed by \
                        dynamically downloaded object modules generated \
                        with the GNU toolchain. Note that this applies to C \
                        code only, as C++ binaries are not compatible between \
                        toolchains.
        REQUIRES        INCLUDE_SIGNALS
        CONFIGLETTES    intrinsics.c
}

