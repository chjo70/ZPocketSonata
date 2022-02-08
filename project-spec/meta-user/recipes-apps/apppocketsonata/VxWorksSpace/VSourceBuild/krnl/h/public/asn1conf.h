/* $Header: /home/interpeak/CVSRoot/vxcompat/include/asn1conf.h,v 1.1 2008/06/09 23:03:44 zruan Exp $ */

/*
 * Copyright (C) 1999-2005 Wind River Systems, Inc.
 * All rights reserved.  Provided under license only.
 * Distribution or other use of this software is only
 * permitted pursuant to the terms of a license agreement
 * from Wind River Systems (and is otherwise prohibited).
 * Refer to that license agreement for terms of use.
 */


/****************************************************************************
 *  Copyright 1993-1997 Epilogue Technology Corporation.
 *  Copyright 1998 Integrated Systems, Inc.
 *  All rights reserved.
 ****************************************************************************/

/*
 * $Log: asn1conf.h,v $
 * Revision 1.1  2008/06/09 23:03:44  zruan
 * *** empty log message ***
 *
 * Revision 1.3  2003/01/15 13:58:56  josh
 * directory structure shifting
 *
 * Revision 1.2  2001/11/06 21:50:40  josh
 * second (and hopefully final) pass of new path hacking
 *
 * Revision 1.1.1.1  2001/11/05 17:47:22  tneale
 * Tornado shuffle
 *
 * Revision 9.9.4.3  2001/09/21 19:14:28  josh
 * an extra check:  can't install coexistence if neither SNMPv1
 * nor SNMPv2 are installed
 *
 * Revision 9.9.4.2  2001/08/24 14:32:10  josh
 * a variety of option checks to make sure we don't have conflicting
 * options installed
 *
 * Revision 9.9.4.1  2001/06/28 18:22:56  josh
 * Seeding the Cormorant branch with the code from the old
 * cormorant branch
 *
 * Revision 9.9  2001/04/11 20:58:32  josh
 * we are overwriting the trunk's copy of this file with
 * the file from the kingfisher branch
 *
 * Revision 9.8  2001/01/19 22:22:02  paul
 * Update copyright.
 *
 * Revision 9.7  2000/07/10 15:55:13  mrf
 * Add configuration for Cygnus NT environment with associated changes.
 *
 * Revision 9.6  2000/06/09 14:54:12  josh
 * modifications due to new installation options, new proxy code
 * moved some definitions from sendntfy.h into v3_trgt.h so they'd
 * be built with the target code
 *
 * Revision 9.5.4.1  2001/04/11 20:48:29  josh
 * moving cormorant-specific changes off to the cormorant
 * branch
 *
 * Revision 9.5.2.2  2001/03/12 22:07:50  tneale
 * Updated copyright
 *
 * Revision 9.5.2.1  2000/09/21 21:14:52  josh
 * bringing branch include files in line with root
 *
 * Revision 9.5  2000/03/17 19:48:28  meister
 * Update copyright notice
 *
 * Revision 9.4  2000/03/09 20:58:32  tneale
 * All structure definitions are now bracketted with a test that
 * potentially sets an alignment pragma.  This is to maintain compatibility
 * with the code base that had been distributed by Wind River.
 *
 * Revision 9.3  2000/03/09 16:54:09  tneale
 *  Added #ifdef for C++ to declare extern C if needed
 *
 * Revision 9.2  1999/06/01 15:46:14  josh
 * Moving some installation option checking.
 *
 * Revision 9.1  1999/04/09 20:36:59  josh
 * Obsoleting ENVOY_SNMP_VERSON_USEC and ENVOY_40_VB_FREE_COMPAT
 *
 * Revision 9.0  1998/10/16 22:10:04  sar
 * Update version stamp to match release
 *
 * Revision 8.8  1998/08/04 02:02:17  sar
 * Added some macros for use with longer term storage, if the user
 * hasn't defined them they default to the standard ones.
 *
 * Revision 8.7  1998/06/23 20:28:23  sar
 * Added requirement for view2275 if v3 is installed
 *
 * Revision 8.6  1998/06/09 21:34:56  sar
 * Added MEMCMP_NULLOK
 *
 * Revision 8.5  1998/06/08 19:42:10  sar
 * Create a define to tell us if we need the stats group in general
 *
 * Revision 8.4  1998/05/29 03:53:54  sar
 * Add and use defines for v2 types and v2 protocol pieces.  This allows
 * us to include the types and pieces for other versions, such as v3,
 * without having to touch all of the seperate files that use the
 * types or pieces.
 *
 * Revision 8.3  1998/05/23 19:55:38  sar
 * As part of adding rfc2275 made a switch to mesh 2275 and 1445.
 *
 * Revision 8.2  1998/02/25 15:21:23  sra
 * Finish moving types.h, bug.h, and bugdef.h to common/h/.
 *
 * Revision 8.1  1998/02/25 04:50:22  sra
 * Update copyrights.
 *
 * Revision 8.0  1997/11/18 00:56:20  sar
 * Updated revision to 8.0
 *
 * Revision 7.5  1997/10/30 04:23:16  sar
 * Update type information mostly convert bits16_ts to ALENGTH_Ts
 * also add MAX_ALENGTH
 *
 * Revision 7.4  1997/10/22 03:07:28  sar
 * Mofied the agentx and older subagent schemes install options
 *
 * Revision 7.3  1997/08/21 17:23:44  sra
 * Begin moving configuration stuff that's common to all products to common.h
 * Minor cleanups to common/lib/prng.c.  Add pnrg seed function to snarkbsd.
 *
 * Revision 7.2  1997/03/20 06:47:59  sra
 * DFARS-safe copyright text.  Zap!
 *
 * Revision 7.1  1997/02/25 10:49:26  sra
 * Update copyright notice, dust under the bed.
 *
 */

/* [clearcase]
modification history
-------------------
01a, 05jun08,zhr update for GPP
*/


#if !defined(asn1conf_inc)
#define asn1conf_inc

#define MAX_IP_ADDR_LEN 4
	/* various sizes of integers */
typedef int           sbits32_t;
typedef unsigned int  bits32_t;
typedef signed short  bits16_t;
typedef short         sbits16_t;
typedef unsigned char bits8_t;


typedef sbits32_t	INT_32_T;
typedef bits32_t	UINT_32_T;
typedef sbits16_t	INT_16_T;
typedef bits16_t 	UINT_16_T;
typedef bits8_t		UINT_8_T;
typedef bits8_t		OCTET_T ;
typedef bits16_t 	ATVALUE_T;	/* ASN.1 type values		*/
typedef bits16_t 	ALENGTH_T;	/* ASN.1 contents field	lengths	*/

typedef int boolean_t;

	/* this is used as both a maximum and a mask */
#define MAX_ALENGTH     0xFFFF


#define OCTETS_PER_INT32    (sizeof(INT_32_T)/sizeof(OCTET_T))
#define OCTETS_PER_INT16    (sizeof(INT_16_T)/sizeof(OCTET_T))

#define snmpdMemoryAlloc(size)     \
       malloc (size)
#define SNMP_memory_alloc(size)     \
       malloc (size)


#ifndef SNMP_memory_alloc_lt
#define SNMP_memory_alloc_lt(need) SNMP_memory_alloc(need)
#endif

#ifndef SNMP_memory_free_lt
#define SNMP_memory_free_lt(buf) SNMP_memory_free(buf)
#endif

/*****************************************************************
 * Set the size of object identifier components.  32 bits is recommended
 * but 16 bits may work and may save a little space.
 * This may be overridden in <oemtypes.h> by defining __TYPES_HAVE_OIDC_T_
 *****************************************************************/
#ifndef __TYPES_HAVE_OIDC_T_
typedef	bits32_t	OIDC_T;
#endif

/* min and max macros if not provided by the system */
#if (!defined(max))
#define max(a,b)    (((a) > (b)) ? (a) : (b))
#endif
#if (!defined(min))
#define min(a,b)    (((a) < (b)) ? (a) : (b))
#endif

/* These are the standard C functions that we use in Envoy.  If the
 * customer's compiler supplies these correctly then nothing more need be
 * done.  If not, then <envoy.h> can override.  The most common case is
 * that the system provides them but with the wrong type arguments (char *
 * instead of void *).  The macros can then fix this with casts. */
#ifndef MEMCPY
#define MEMCPY(dst, src, n) memcpy(dst, src, n)
#endif
#ifndef MEMSET
#define MEMSET(dst, val, n) memset(dst, val, n)
#endif
#ifndef MEMCMP
#define MEMCMP(s1, s2, n) memcmp(s1, s2, n)
#endif
#ifndef STRLEN
#define STRLEN(s) strlen(s)
#endif

#ifndef MEMCMP_NULLOK
#define MEMCMP_NULLOK(s1, s2, n) (n ? MEMCMP(s1, s2, n) : 0)
#endif

#endif /* asn1conf_inc */
