/* cplusgnuIos.c - VxWorks iostreams class library initialization */

/*
 * Copyright 1995-1996, 1998, 2000-2001, 2003, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
03jun03,sn   added gcc 3.x support
06nov01,sn   use new prefixed names
24jan01,sn   use wrapper symbols
10oct00,sn   regenerated
03jun98,sn   moved the iostdio files to cplusIosTest.c
             unless INCLUDE_CPLUS_IOSTREAMS_FULL is defined only
             pull in what's required by iostream.o
05may98,sn   added the "iostdio" object files
             fixed a typo in the modification history
15jan98,sn   rewrote to force-link GNU iostreams
22jul96,jmb  fix comment attached to final endif
07jun95,srh  correct duplicate naming problem (SPR 5100)
14jun95,srh  written.
*/

/*
DESCRIPTION
This file is used to include the iostreams classes in the 
VxWorks build. The routines are only included when this file is 
included by usrConfig.c.

NOMANUAL
*/

#ifndef __INCcplusIosc
#define __INCcplusIosc

#ifdef INCLUDE_CPLUS_IOSTREAMS_FULL
#define INCLUDE_CPLUS_IOSTREAMS
#endif

#ifdef INCLUDE_CPLUS_IOSTREAMS
extern char __gnu_cplusplus_std_libraryInit;

char * __cplusIosObjs [] =
{
    &__gnu_cplusplus_std_libraryInit,
    0
};
#endif

#endif /* __INCcplusIosc */
