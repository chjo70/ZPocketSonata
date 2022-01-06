/* usrStartup.c - first routine called from usrInit */

/*
 * Copyright (c) 1998-1999, 2002, 2004-2005, 2007-2009, 2012, 2014
 *     Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */ 

/*
modification history
--------------------
19feb14,rbc  VXW7-1583 - Remove INCLUDE_UEFI_BOOT_SUPPORT
10jan12,zl   initialize sysExcMsg string (WIND00318907). Removed i960 code.
             Coding conventions cleanup.
07sep10,cww  LP64 adaptation
20oct09,slk  remove _WRS_MIPS_SDA_SUPPORTED macro so vxSdaInit is called
             for MIPS
16sep09,cww  Add call to sysMemDescInit
13jul09,pch  Add support for INCLUDE_TM_TIMING_FRAMEWORK
13oct08,rbc  Update for efi header move.
27aug08,slk  enable SDA support for MIPS
22aug08,rbc  Changes for passing EFI memory map and ACPI table pointer.
15jul07,dcc  Added SDA initialization for MIPS, although not yet enabled.
30apr07,dcc  Added PPC SDA initialization in sysStart().
11may05,slk  Fix warning for MIPS builds from palInit
22sep04,yvp  Fix SPR 99907: eliminated calls to ioGlobalStdSet to break
             coupling with ioLib. Global stdio is initialized in ioLib. 
01jun04,mem  added call to palInit().
04apr02,pch  SPR 74348: Enable PPC Machine Check exception ASAP
20jan99,jpd  moved FREE_RAM_START_ADRS definition to usrKernel.c.
19jan99,jgn  add sysHwInit0() facility
29oct98,ms   added I960 hack.
14jul98,ms   moved "IMPORT char end[]" to generated sysConfig.c.
20apr98,ms   written from usrConfig.c
*/ 

/*
DESCRIPTION
This moduele contains the routine that performs critical early system 
initialization.
*/  

/* externals */

#if (CPU_FAMILY == MIPS)
IMPORT void palInit	(void);
IMPORT void vxSdaInit	(void);
#endif  /* (CPU_FAMILY == MIPS) */

#if (CPU_FAMILY == PPC)
IMPORT void vxSdaInit	(void);
#endif	/* (CPU_FAMILY == PPC) */

#ifdef	INCLUDE_TM_TIMING_FRAMEWORK

/* "beginning of startup" timestamp */

TM_TIMESTAMP_TYPE tmTfwImageStartTime = TM_TIMESTAMP_INIT_VAL;

#endif	/* INCLUDE_TM_TIMING_FRAMEWORK */

/*******************************************************************************
*
* sysStart - first C code executed from usrInit
*
* This is the first routine called from usrInit(), basically the first C 
* code executed during system initialization (excluding the function call 
* itself). It initializes BSS, SDA and other important data as needed for
* correct code execution, hardware operation, and early error handling.
*
* RETURN: n/a
*/ 

void sysStart
    (
    int					startType
    )
    {
#if (CPU_FAMILY == PPC) || (CPU_FAMILY == MIPS)

    /* 
     * For PPC and MIPS, the call to vxSdaInit() must be the first operation 
     * in sysStart(). This is because vxSdaInit() sets the SDA registers
     * (r2 and r13 on PPC, gp on MIPS) to the SDA base values. No C code 
     * must be placed before this call.
     */

    _WRS_ASM ("");   /* code barrier to prevent compiler moving vxSdaInit() */
    vxSdaInit ();    /* this MUST be the first operation in usrInit() for PPC */
    _WRS_ASM ("");   /* code barrier to prevent compiler moving vxSdaInit() */

#endif	/* (CPU_FAMILY == PPC) || (CPU_FAMILY == MIPS) */

#ifndef INCLUDE_BOOT_APP
    /* 
     * initialize the exception message string for VxWorks images;
     * bootApp images must preserve the string so they can display it
     * when rebooting VxWorks due to non-recoverable errors.
     */

    sysExcMsg[0] = EOS;
#endif /* INCLUDE_BOOT_APP */

#ifdef INCLUDE_TM_TIMING_FRAMEWORK

    /*
     * Capture a "beginning of startup" timestamp as early in init as
     * possible, but must follow vxSdaInit() on arch that support it
     * -- the global in which the timestamp is saved may be in the SDA.
     */

    TM_TIMESTAMP_GET (tmTfwImageStartTime);

#endif	/* INCLUDE_TM_TIMING_FRAMEWORK */

#if (CPU_FAMILY == MIPS)
    palInit ();
#endif	/* (CPU_FAMILY == MIPS) */

#if (CPU_FAMILY == SPARC)
    excWindowInit ();                           /* SPARC window management */
#endif

#ifdef INCLUDE_SYS_HW_INIT_0
    /*
     * Perform any BSP-specific initialisation that must be done before
     * cacheLibInit() is called and/or BSS is cleared.
     */

    SYS_HW_INIT_0 ();
#endif /* INCLUDE_SYS_HW_INIT_0 */


#ifdef	CLEAR_BSS
	bzero (edata, end - edata);
#endif	/* CLEAR_BSS */

    sysStartType = startType;
    intVecBaseSet ((FUNCPTR *) VEC_BASE_ADRS);

#if (CPU_FAMILY == PPC) && defined(INCLUDE_EXC_SHOW)
    /*
     * Do this ahead of excVecInit() to set up _func_excPanicHook, in case
     * the enabling of Machine Check there allows a pending one to occur.
     * excShowInit() will be called again later, harmlessly.
     */

    excShowInit ();
#endif  /* CPU_FAMILY == PPC && defined(INCLUDE_EXC_SHOW) */

#ifdef _WRS_CONFIG_USE_MEMDESC
    sysMemDescInit ();
#endif
    }

