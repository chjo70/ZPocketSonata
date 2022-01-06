/* elftypes.h - typedefs of ELF types for host and target */

/* 
 * Copyright (c) 2003-2005, 2009-2010 Wind River Systems, Inc. 
 * 
 * The right to copy, distribute, modify, or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. 
 */

/*
modification history
--------------------
01i,29apr10,pad  Moved extern C statement after include statements.
01h,22feb10,v_r  LP64 TODOS cleanup.
01g,02oct09,pad  Removed temporary types usage.
01f,10jun09,v_r  Used VxWorks types instead of C99 ones for host portability.
01e,12may09,v_r  Added ELF64 support.
01d,25jul05,v_r  Updated copyright.
01c,27mar04,jn   Make elf.h and elftypes.h shared with the host (target
                 server)
01b,20jun03,nwd  Deliver of Tornado 2.2 Cumulative Patch 1
01a,30apr03,jn   derived from Diab elftypes.h header file 
                 /vobs/rome_diab_lib/dlib/include/include.unx/
		 elftypes.h@@/main/1
		 and /.wind_vxw_h/river/target/h/vxWorks.h@@/main/tor2/1 
		 (for elements of Wind River coding standards)
*/

#ifndef __INCelftypesh
#define __INCelftypesh

#ifndef HOST
#include <vxWorks.h>
#else
#include <host.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**************	Exported data, types and macros	*****************/

/* 
 * Using [U]INTXX_t types allows to have the proper length whatever bitness we
 * are building for (32 or 64bits).
 *
 * Original ELF spec definitions are :
 * 32-Bit Data Types
 * 
 * Name	         Size	Alignment   Purpose
 * Elf32_Addr    4	4           Unsigned program address
 * Elf32_Off     4	4           Unsigned file offset
 * Elf32_Half    2	2           Unsigned medium integer
 * Elf32_Word    4      4           Unsigned integer
 * Elf32_Sword   4      4           Signed integer
 * unsigned char 1      1           Unsigned small integer
 * 
 * 64-Bit Data Types
 * 
 * Name	        Size	Alignment   Purpose
 * Elf64_Addr    8	8           Unsigned program address
 * Elf64_Off     8	8           Unsigned file offset
 * Elf64_Half    2	2	    Unsigned medium integer
 * Elf64_Word    4	4	    Unsigned integer
 * Elf64_Sword   4      4	    Signed integer
 * Elf64_Xword   8      8	    Unsigned long integer
 * Elf64_Sxword	 8      8	    Signed long integer
 * unsigned char 1      1	    Unsigned small integer
 */

/* Note: this part also applies to the host side (32bits) */

typedef UINT32		Elf32_Addr;
typedef UINT32		Elf32_Off;
typedef UINT16		Elf32_Half;
typedef UINT32		Elf32_Word;
typedef INT32		Elf32_Sword;

typedef UINT64		Elf64_Addr;
typedef UINT64		Elf64_Off;
typedef UINT16		Elf64_Half;
typedef UINT32		Elf64_Word;
typedef INT32		Elf64_Sword;
typedef UINT64		Elf64_Xword;
typedef INT64		Elf64_Sxword;

#ifdef __cplusplus
}
#endif

#endif /* __INCelftypesh */
