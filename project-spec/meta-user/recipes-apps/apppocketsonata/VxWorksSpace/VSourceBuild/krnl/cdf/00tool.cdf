/* 00tool.cdf - VxWorks Tool components */

/*
 * Copyright (c) 2013, 2015, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history            
--------------------
02may16,mcm  Added LLVM intrinsics to the list
16dec15,lau  removed the INCLUDE_NO_INTRINSICS Component (V7COR-2886)
23oct13,mcm  created out of legacy 01vxWorks.cdf contents
*/

/*
DESCRIPTION
This file contains descriptions for common VxWorks tool components 
*/

Selection SELECT_COMPILER_INTRINSICS {
        NAME            Downloadable kernel modules compiler support routines
        SYNOPSIS        Compiler support routines that may be needed to \
                        support dynamically downloaded object modules \
                        generated with the various toolchains. Note that \
                        this applies to C code only, as C++ binaries are \
                        not compatible between toolchains.
        COUNT           0
        CHILDREN        INCLUDE_GNU_INTRINSICS \
                        INCLUDE_DIAB_INTRINSICS \
                        INCLUDE_ICC_INTRINSICS \
			INCLUDE_LLVM_INTRINSICS
}
