/* 00cplus.cdf - cplus components */

/*
 * Copyright (c) 2013-2014, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history            
--------------------
21jul17,mjn    Apply requested NAME fix. (F8862)
10apr17,jla    Enhance clarity of synopses. Remove redundancy in names. (F8862)
19nov14,gvm    INCLUDE_CPLUS now pulls in INCLUDE_CPLUS_LANG (TCGNU-3747)
01oct13,mcm    created based on content from the common 00vxWorks.cdf 
               in version 6.9
*/

/*
DESCRIPTION
Components that are part of kernel cplus 
*/

Folder  FOLDER_CPLUS {
        NAME            C++
        SYNOPSIS        This folder includes the components and parameters \
                        needed to include C++ support in your VxWorks project.
        CHILDREN        INCLUDE_CTORS_DTORS     \
                        INCLUDE_CPLUS           \
                        INCLUDE_CPLUS_LANG      \
                        FOLDER_CPLUS_STDLIB
        DEFAULTS        INCLUDE_CPLUS           \
                        INCLUDE_CPLUS_LANG
}

Component INCLUDE_CPLUS {
        NAME            Core runtime
        SYNOPSIS        This component includes basic support for C++ \
                        applications. It is typically used in conjunction with \
                        INCLUDE_CPLUS_LANG.
        INIT_RTN        usrCplusLibInit ();
        HDR_FILES       private/cplusLibP.h
        MODULES         cplusCore.o \
                        cplusInit.o \
                        cplusLib.o \
                        cxa_atexit.o
        CONFIGLETTES    usrCplus.c
        REQUIRES        INCLUDE_CTORS_DTORS INCLUDE_CPLUS_LANG
}

Component INCLUDE_CPLUS_LANG {
        NAME            Compiler support routines
        SYNOPSIS        This component includes support for C++ language \
                        features such as exception handling, new, delete, and \
                        so forth.
}

Component INCLUDE_CTORS_DTORS {
        NAME            Run static initializers
        SYNOPSIS        Ensures that compiler-generated initialization \
                        functions, including initializers for C++ static \
                        objects, are called at kernel start up time.
        INIT_RTN        cplusCtorsLink ();
        HDR_FILES       cplusLib.h
        MODULES         cplusXtors.o
}

Folder FOLDER_CPLUS_STDLIB {
        NAME            Standard library
        SYNOPSIS        This folder contains components to add support for the \
                        C++ standard library.
        CHILDREN        INCLUDE_CPLUS_IOSTREAMS
        DEFAULTS        INCLUDE_CPLUS_IOSTREAMS
}

Component INCLUDE_CPLUS_DEMANGLER {
        NAME            Symbol demangler
        SYNOPSIS        Includes the C++ demangler, which is useful when \
                        using the kernel shell loader because it provides for \
                        returning demangled symbol names to kernel shell \
                        symbol table queries. This component is added by \
                        default if both the INCLUDE_CPLUS and INCLUDE_SYM_TBL \
                        components are included in VxWorks.
        INIT_RTN        cplusDemanglerInit ();
        MODULES         cplusDem.o
        INCLUDE_WHEN    INCLUDE_CPLUS INCLUDE_SYM_TBL
}

