/*
Copyright 1998-2001, 2017 Wind River Systems, Inc.

modification history
--------------------
21jul17,mjn  Apply requested NAME fix. (F8862)
13apr17,jla  Enhance synopsis clarity. Reformat modhistory (F8862)
03jun03,sn   added gcc 3.x support
20mar02,sn   SPR 71699 - Name and synopsis of INCLUDE_CPLUS_LANG now
             defined for all toolchains in 00vxWorks.cdf
07nov01,rbl  remove unnecessary dependency on INCLUDE_GNU_64BIT
06nov01,sn   use new prefixed names
06nov01,sn   wrote

DESCRIPTION

This file contains descriptions for the GNU toolchain specific C++
compiler support and standard library components.
*/

Component INCLUDE_CPLUS_LANG {
	CONFIGLETTES	cplusgnuLang.c
}

Component INCLUDE_CPLUS_IOSTREAMS {
	NAME		I/O streams and other standard libraries
	SYNOPSIS	This component includes C++ standard library support \
				in your VxWorks project.
	REQUIRES        INCLUDE_CPLUS
	CONFIGLETTES    cplusgnuIos.c
}
