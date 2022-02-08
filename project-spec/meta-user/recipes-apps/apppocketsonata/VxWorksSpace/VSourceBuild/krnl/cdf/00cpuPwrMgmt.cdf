/* 00cpuPwrMgmt.cdf - CPU Power management component description file */

/*
 * Copyright (c) 2007-2011, 2013, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02sep15,d_l  remove CPU power management from 64bit build. (V7PRO-2181)
26aug13,x_z  removed dependency with source directory. 
22aug11,rbc  WIND00294339 - Fix build error from moving cpuPwrLightLib.c
12mar10,rec  CPU performance management update
11aug09,cww  Placed cpuPwrFrameWorkInit directly into usrRoot
26aug08,jpb  Removed LAYER from components.
04aug08,dtr  Allow power mangement to be turned on for SMP.
06nov07,kk   disable power management support for VxWorks SMP.
21jun07,mmi  Created based on ../i86/00cpuPwrMgmt.cdf 01b 

DESCRIPTION

This file contains the CPU power Management components.
*/

/* CPU Power managment  */

#ifdef _WRS_CONFIG_PWR_MGMT

Component INCLUDE_CPU_LIGHT_PWR_MGR {
    NAME        Light CPU Power Management 
    SYNOPSIS    Idle-halt CPU power management
    STATUS_DETAILS this component is disabled because VSB option \
                _WRS_CONFIG_PWR_MGMT is selected
    REQUIRES    COMPONENT_NOT_SUPPORTED
}

#else /* !_WRS_CONFIG_PWR_MGMT */

#ifndef _WRS_CONFIG_LP64
Folder  FOLDER_PWR_MGMT {
    NAME        Power Management
    SYNOPSIS    Power Management Components
    _CHILDREN   FOLDER_OS
    CHILDREN    INCLUDE_CPU_PWR_ARCH \
                INCLUDE_CPU_LIGHT_PWR_MGR
    DEFAULTS    INCLUDE_CPU_LIGHT_PWR_MGR
}

Component INCLUDE_CPU_LIGHT_PWR_MGR {
    NAME        Light CPU Power Management 
    SYNOPSIS    Idle-halt CPU power management
    MODULES     cpuPwrLightLib.o
    HDR_FILES   cpuPwrMgr.h
    INIT_RTN    cpuPwrLightMgrInit (); \
                cpuPwrMgrEnable (TRUE);
    EXCLUDES    INCLUDE_CPU_PERFORMANCE_MGMT
    HDR_FILES   cpuPwrMgr.h
}

#endif /* ! _WRS_CONFIG_LP64 */
#endif /* _WRS_CONFIG_PWR_MGMT */
