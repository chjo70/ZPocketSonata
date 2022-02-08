/* version.h - VxWorks version information */

/* 
 * Copyright (c) 1994-1996, 1998, 2000-2001, 2003-2015, 2017
 * Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */

/*
modification history
--------------------
06sep17,h_k  corrected service package version declaration to
             vxWorksVersionSvcPk. (V7COR-4893)
             deleted lines wrapped around with #ifdef _WRS_KERNEL/#endif.
05feb15,pfl  CERT: addressed FlexeLint warnings
06feb14,cww  updated runtimeName to VxWorks 7 (VXW7-1662)
19dec13,to   include vxWorks.h for IMPORT
16may13,mze  version now set to 7.0.0
12mar12,pad  Displayed digits of the version number are now handled on
	     their own (defect 273861). Full version number now presents
	     four digits if applicable.
02sep11,mdk  change MAINT_VERSION to 2
19may11,mdk  add minor number for 6.9.1
24nov10,pad  Removed EAR string from version info.
27jul10,pad  Bumped EAR number from 2 to 3. Moved this information into a
	     third qualifier.
05may10,pad  Cleaned-up now that both VxWorks 32-bit and 64-bit use the
             same minor version number.
28apr10,pad  Moved extern C statement after include statements.
31mar10,pad  Bumped 64-bit version name from EAR-1 to EAR-2.
24feb10,mdk  6.9 version update
01oct09,pad  Fixed a bug (missing space) in the definition of
             VXWORKS_VERSION. Also reverted to release number 6.8 for the
             32-bit VxWorks build until the host tools are ready for the
             release 6.9.
24sep09,pad  Replaced #ifndef HOST/#endif with #ifdef _WRS_KERNEL to also
             prevent the inclusion of vsbConfig.h when used on the user-side.
24sep09,pad  Added #ifndef HOST/#endif around the inclusion of vsbConfig.h.
18sep09,pad  Introduced RUNTIME_VERSION_EXTENDED to hold the complete
	     release string.
06jul09,kkz  Updating version number for VxWorks 6.8
29apr08,kkz  Updating version number to 6.7
05mar07,kk   update version number to 6.6
15nov06,cjj  Added definition for SMP
07sep06,kkz  Version number 6.5
16aug06,mmg  Update version string to 6.4
12may06,kkz  Changed RUNTIME_VERSION to 6.3
16dec05,tam  update version to 6.3 - Beta Release
28sep05,tam  removed RDR from version string
01sep05,pad  Moved #ifdef _WRS_KERNEL pragma lower in the file so as to
             allow for the build of the host-side part of vxsim.
24aug05,pad  this file is now shared between kernel and user sides
	     (SPR #105066) but only the _WRS_VXWORKS_xxx macros are visible
	     on the user side.
11aug05,kkz  Updating version strings for 6.2
12may05,tam  changed RUNTIME_VERSION to 6.1
22apr05,tam  changed RUNTIME_VERSION to 6.1 - Reference Design Release
17feb05,tam  changed RUNTIME_VERSION to 6.1 - Early Access Release
18oct04,dbt  change RUNTIME_VERSION to 6.0.
11may04,md   add global variables for VxWorks version numbers
05may04,dat  move version number macros from vxWorks.c to version.h,
	     change version to 'Beta'
16mar04,rhe  Change RUNTIME_VERSION to 6.0 - Technology Access Release 2
12dec03,dat  change release to 6.0, TAR version 1, added a space to
	     VXWORKS_VERSION between the name and the version.
05oct03,kk   change release to 5.5 (BASE 6 - Iter 2)
02jul03,job  change release to 5.5 (BASE 6 - Iter 1)
25mar03,sfp  update for CP-1 release: VxWorks 5.5.1
12sep01,fmk  change release to 5.5
17jan01,sn   simplify job of host val  
08dec00,cmf  changed release to 5.4.2
08jul98,ms   changed release to 5.4.
02oct96,p_m  changed release to 5.3.1.
             removed pre 02r history.
15mar96,p_m  changed release to 5.3 for everything except 960 K.
06mar96,dat  removed length macros, no longer needed
23jan96,tpr  changed release to 5.3-PowerPC-beta
06jun95,caf  changed release to 5.2-PowerPC-beta.
25oct95,ms   changed release to 5.3
21jun95,ms   changed release to 5.3-beta
29mar95,kdl  changed release to 5.2.
12nov94,dvs  changed release to 5.2-beta
*/

#ifndef __INCversionh
#define __INCversionh

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Release identification, major, minor, and maintenance numbers.
 * 
 * Current VxWorks release number is 7.0.0.0
 *
 * IMPORTANT NOTE: changing any of the release identification numbers requires
 * 		   coordination with the host tools so that the PAM (Product
 * 		   Activation Matrix) files are properly updated.
 */

#define _WRS_VXWORKS_MAJOR 7
#define _WRS_VXWORKS_MINOR 0
#define _WRS_VXWORKS_MAINT 0
#define _WRS_VXWORKS_SVCPK 0

/*
 * Macro controlling what version's digits are displayed in all banners using
 * the 'vxWorksVersion' and 'runtimeVersion' global variables. The possible
 * values are:
 *  - 4: the four digits of the version number are displayed.
 *  - 3: only the three highest digits of the version number are displayed.
 *  - 2: only the two highest digits of the version number are displayed.
 *
 * When asked to display more than 2 digits, only the useful digits are
 * actually displayed. For instance even if all digits are requested the full
 * version will have two digits only if the maintenance and service pack
 * numbers are equal to zero, or will have three digits only if only the
 * service pack number is equal to zero. A null minor version number is
 * always displayed.
 */

#define ALL_VERSION_DIGITS			4
#define MAJ_MIN_AND_MAINT_VERSION_DIGITS	3
#define MAJ_AND_MIN_VERSION_DIGITS		2

#define NUM_VERSION_DIGITS_TO_DISPLAY	MAJ_AND_MIN_VERSION_DIGITS
 
/*
 ****************************************************************************
			NO VERSION SETTINGS BELOW THIS POINT
 ****************************************************************************
 */

/*
 * Some "stringification" magic to automatically set RUNTIME_VERSION with the
 * proper major and minor release numbers.
 */

#define strLvl1(s)	#s
#define strLvl2(m)	strLvl1(m)

/*
 * Backward compatibility constraint: the RUNTIME_NAME should always hold the 
 * simple string "VxWorks 7".  RUNTIME_VERSION is a carryover from VxWorks 6
 * and should no longer be used.
 */

#define RUNTIME_NAME		"VxWorks 7"
#define RUNTIME_VERSION		strLvl2(_WRS_VXWORKS_MAJOR) "." \
				strLvl2(_WRS_VXWORKS_MINOR)

/*
 * Prepare the runtime's display and full version macros. 
 * We use only the digits that are to be displayed and are useful, per
 * the rules laid out above. For the full version macro, used by version(),
 * we use all the digits.
 */

#if ((NUM_VERSION_DIGITS_TO_DISPLAY == ALL_VERSION_DIGITS) && \
     (_WRS_VXWORKS_SVCPK != 0))
#define RUNTIME_VERSION_BANNER	strLvl2(_WRS_VXWORKS_MAJOR) "." \
				strLvl2(_WRS_VXWORKS_MINOR) "." \
				strLvl2(_WRS_VXWORKS_MAINT) "." \
				strLvl2(_WRS_VXWORKS_SVCPK)
#elif ((NUM_VERSION_DIGITS_TO_DISPLAY == MAJ_MIN_AND_MAINT_VERSION_DIGITS) && \
       (_WRS_VXWORKS_MAINT != 0))
#define RUNTIME_VERSION_BANNER	strLvl2(_WRS_VXWORKS_MAJOR) "." \
				strLvl2(_WRS_VXWORKS_MINOR) "." \
				strLvl2(_WRS_VXWORKS_MAINT)
#else
#define RUNTIME_VERSION_BANNER	strLvl2(_WRS_VXWORKS_MAJOR) "." \
				strLvl2(_WRS_VXWORKS_MINOR)
#endif

#if (_WRS_VXWORKS_SVCPK != 0)
#define RUNTIME_VERSION_FULL	strLvl2(_WRS_VXWORKS_MAJOR) "." \
				strLvl2(_WRS_VXWORKS_MINOR) "." \
				strLvl2(_WRS_VXWORKS_MAINT) "." \
				strLvl2(_WRS_VXWORKS_SVCPK)
#elif (_WRS_VXWORKS_MAINT != 0)
#define RUNTIME_VERSION_FULL	strLvl2(_WRS_VXWORKS_MAJOR) "." \
				strLvl2(_WRS_VXWORKS_MINOR) "." \
				strLvl2(_WRS_VXWORKS_MAINT)
#else
#define RUNTIME_VERSION_FULL	strLvl2(_WRS_VXWORKS_MAJOR) "." \
				strLvl2(_WRS_VXWORKS_MINOR)
#endif

/*
 * Additional macros used to set the qualifiers properly for all variants of
 * VxWorks.
 */

#define RUNTIME_SMP_NAME	"SMP"
#define RUNTIME_64BIT_NAME	"64-bit"

#ifdef _WRS_CONFIG_SMP
#define RUNTIME_QUALIFIER_1	" " RUNTIME_SMP_NAME
#else
#define RUNTIME_QUALIFIER_1	""
#endif

#ifdef _WRS_CONFIG_LP64
#define RUNTIME_QUALIFIER_2	" " RUNTIME_64BIT_NAME
#else
#define RUNTIME_QUALIFIER_2	""
#endif

#define RUNTIME_QUALIFIER_3	""	/* EAR version, etc. */

/*
 * The extended runtime version is the concatenation of the displayed release
 * number followed by qualifiers (currently three), possibly empty, covering the
 * variants of VxWorks.
 * For instance:
 *   RUNTIME_VERSION_EXTENDED | VERSION  QUALIFIER_1  QUALIFIER_2 QUALIFIER_3
 *   6.9                      |   6.9
 *   6.9 SMP                  |   6.9       SMP
 *   6.9 64-bit               |   6.9                   64-bit
 *   6.9 SMP 64-bit           |   6.9       SMP         64-bit
 *   6.9 64-bit EAR-1         |   6.9                   64-bit      EAR-1
 *   6.9 SMP 64-bit EAR-1     |   6.9       SMP         64-bit      EAR-1
 *
 * Note: for printLogo(), the max combined length is 44 characters.
 *
 * The extended full runtime version is essentially the same but uses all the
 * useful version digits.
 */

#define RUNTIME_VERSION_EXTENDED RUNTIME_VERSION_BANNER RUNTIME_QUALIFIER_1 \
				 RUNTIME_QUALIFIER_2 RUNTIME_QUALIFIER_3

#define RUNTIME_VERSION_FULL_EXTENDED RUNTIME_VERSION_FULL RUNTIME_QUALIFIER_1 \
				      RUNTIME_QUALIFIER_2 RUNTIME_QUALIFIER_3

/*
 * The VxWorks version is simply the concatenation of the runtime name,
 * "VxWorks", followed by a space followed by the extended runtime version
 * (as defined above).
 *
 * IMPORTANT NOTE: the order of the tokens in the VXWORKS_VERSION macro must
 *                 not be changed without coordination with the host tools.
 */

#define VXWORKS_VERSION RUNTIME_NAME " " RUNTIME_VERSION_EXTENDED

#ifdef __cplusplus
}
#endif

#endif /* __INCversionh */

