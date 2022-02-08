/* sysComms.c - common block symbols needed by many VxWorks libraries */

/*
 * Copyright (c) 1998-2011, 2013, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
06may14,cww  added include adrSpaceLibP.h
27mar14,cww  remove memory related definitions when using memory descriptors
18oct13,h_k  excluded symLib.h header inclusion unless _WRS_CONFIG_OSTOOLS
             is defined.
23aug11,ers  Generic support for INCLUDE_WRLOAD_IMAGE_BUILD load bias.
04aug11,slk  add support for wrload loadbias feature
27apr11,m_h  ARM support for wrload
04oct10,slk  updates for MIPS large memory model support
06jul10,v_r  Added login security facility boolean (req CQ:WIND00190686).
26apr10,scm  clean up duplicate code from merge, WIND00185760
14jul09,mdk  merge from networking branch
19jan09,rab  Add global symbols for IA32 multicore
16oct08,kab  Add global symbols for multicore
16sep04,sru  Added global variable for text protection state.
03jun98,ms   updated
*/

/*
DESCRIPTION
System common block symbol definitions.
*/

#ifdef	_WRS_CONFIG_OSTOOLS
#include <symLib.h>
#endif	/* _WRS_CONFIG_OSTOOLS */

#include <bootLib.h>
#include <private/adrSpaceLibP.h>

/* globals */

int             consoleFd = NONE;	/* fd of initial console device      */
#ifdef	_WRS_CONFIG_OSTOOLS
SYMTAB_ID       statSymTbl;		/* error status symbol table id      */
SYMTAB_ID       sysSymTbl;		/* symbol table id                   */
#endif	/* _WRS_CONFIG_OSTOOLS */
BOOT_PARAMS     sysBootParams;		/* parameters from boot line         */
int             sysStartType;		/* type of boot (WARM, COLD, etc)    */
BOOL		sysCplusEnable;		/* no cplus support by default       */
BOOL		sysAdaEnable;		/* no ada support by default         */
int		sysFlags;               /* boot flags                        */
char		sysBootHost [BOOT_FIELD_LEN]; /* name of boot host           */
char		sysBootFile [BOOT_FIELD_LEN]; /* name of boot file           */
#ifdef INCLUDE_PROTECT_TEXT
int		sysTextProtect = 1;
#else  /* INCLUDE_PROTECT_TEXT */
int		sysTextProtect = 0;
#endif /* INCLUDE_PROTECT_TEXT */
BOOL		systemSecurityIsEnabled = FALSE;

/*
 * Symbols used by wrload/multicore to discover OS image RAM footprint.
 *
 * Set these to the actual image map; any load bias or shift is set separately
 * in the BSP and handled by the tools. See the VxWorks BSP Developer's Guide
 * for more information on wrload and _wrload_bias_...
 */

#if defined (INCLUDE_WRLOAD_IMAGE_BUILD)
_WRS_ABSOLUTE_BEGIN(wrloadImageBuild)
_WRS_ABSOLUTE(_wrload_bias_high_32,((UINT64)WRLOAD_IMAGE_BUILD_PHYS_BIAS>> 32));
_WRS_ABSOLUTE(_wrload_bias_low_32,          WRLOAD_IMAGE_BUILD_PHYS_BIAS);
_WRS_ABSOLUTE_END
#endif /* (INCLUDE_WRLOAD_IMAGE_BUILD) */

#ifndef _WRS_CONFIG_USE_MEMDESC
#if (CPU_FAMILY == PPC) || (CPU_FAMILY == I80X86) || (CPU_FAMILY == ARM)

_WRS_ABSOLUTE_BEGIN(Bounds)
_WRS_ABSOLUTE(sysAbsSymPhysMemBottom, LOCAL_MEM_LOCAL_ADRS);
_WRS_ABSOLUTE(sysAbsSymPhysMemSize, LOCAL_MEM_SIZE);
_WRS_ABSOLUTE_END

const char *    sysSymPhysMemBottom = (char *)LOCAL_MEM_LOCAL_ADRS;
const long      sysSymPhysMemSize = LOCAL_MEM_SIZE;

#elif (CPU_FAMILY == MIPS)

#ifndef INCLUDE_LARGE_MEMORY_MODEL
_WRS_ABSOLUTE_BEGIN(Bounds)
_WRS_ABSOLUTE(_wrload_sysAbsSymVirtOffset, K0_TO_PHYS(LOCAL_MEM_LOCAL_ADRS));
_WRS_ABSOLUTE(_wrload_sysAbsSymUnmappedBaseAdrs, LOCAL_MEM_LOCAL_ADRS);
_WRS_ABSOLUTE(_wrload_sysAbsSymUnmappedKernel, TRUE);
_WRS_ABSOLUTE(sysAbsSymPhysMemBottom, KM_TO_PHYS(LOCAL_MEM_LOCAL_ADRS));
_WRS_ABSOLUTE(sysAbsSymPhysMemSize, LOCAL_MEM_SIZE);
_WRS_ABSOLUTE_END

const long      sysSymVirtOffset = (long)LOCAL_MEM_LOCAL_ADRS;
const char *    sysSymPhysMemBottom = (char *)KM_TO_PHYS(LOCAL_MEM_LOCAL_ADRS);
const long      sysSymPhysMemSize = (long)LOCAL_MEM_SIZE;
#else  /* INCLUDE_LARGE_MEMORY_MODEL */
_WRS_ABSOLUTE_BEGIN(Bounds)
_WRS_ABSOLUTE(_wrload_sysAbsSymVirtOffset, (LOCAL_MEM_LOCAL_ADRS - \
                                            LOCAL_MEM_PHYS_ADRS));
_WRS_ABSOLUTE(_wrload_sysAbsSymUnmappedBaseAdrs, \
              K0_TO_PHYS(LOCAL_UNMAPPED_BASE_ADRS));
_WRS_ABSOLUTE(_wrload_sysAbsSymUnmappedKernel, FALSE);

_WRS_ABSOLUTE(sysAbsSymPhysMemBottom, LOCAL_MEM_PHYS_ADRS);
_WRS_ABSOLUTE(sysAbsSymPhysMemSize, LOCAL_MEM_SIZE);
_WRS_ABSOLUTE_END

const long      sysSymVirtOffset = \
                        (long)(LOCAL_MEM_LOCAL_ADRS - LOCAL_MEM_PHYS_ADRS);
const char *    sysSymPhysMemBottom = (char *)LOCAL_MEM_PHYS_ADRS;
const long      sysSymPhysMemSize = (long)LOCAL_MEM_SIZE;
#endif /* INCLUDE_LARGE_MEMORY_MODEL */

#endif /* CPU-specific wrload syms */
#endif /* _WRS_CONFIG_USE_MEMDESC */
