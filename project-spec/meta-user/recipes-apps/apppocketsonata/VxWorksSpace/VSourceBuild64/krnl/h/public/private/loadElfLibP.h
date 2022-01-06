/* loadElfLibP.h - private ELF loader library header */

/*
 * Copyright (c) 2001-2005, 2008-2010, 2015, 2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement.
 */

/*
modification history
--------------------
28jun17,yat  Add ELF_SYM_SIZE for secure loader decryption (F9210)
12jul17,h_k  implemented branch island support. (F8938)
05may17,yat  Add ELF_HDR_SH_PTR for secure loader changes (F7459)
15jul15,vhe  Additional support for PPC64 relocations
15jan15,vhe  Added support for PPC64 relocations (US50408)
08sep10,rlp  Fixed previous merge.
10aug10,v_r  Architecture-specific symbol hook now able to modify symbol
             characteristics.
27jan10,v_r  Added architecture-specific fully-qualified hook function
             pointer typedef (part of ARM BE-8 support, req 
    	     CQ:WIND00213215, merged from iter14_bsp_cortex_a9be8).
29apr10,pad  Moved extern C statement after include statements.
15apr10,v_r  Added ability to configure the parser in ELF32-only mode.
23feb10,v_r  Revert structure fields reorganization until we can update
             host side as well.
22feb10,v_r  LP64 TODOS cleanup + structure reorganization.
    	     Moved SYMTBL_REFS to loadRtpLib.
29jan10,v_r  Added loadElfSymbolEntryRead() and
    	     loadElfSectionHeaderReadAndCheck() declarations.
22jun09,v_r  Removed ELF_CLASS macro.
16jun09,v_r  LP64 adaptation: went on w/ relocation abstraction usage and
    	     updated SEGMENT_INFO_DESC to size_t.
09jun09,v_r  LP64 adaptation: added relocation abstraction, allowing to
    	     handle REL/RELA 32/64 bits relocs in a unified manner.
04jun09,v_r  LP64 adaptation: added ELF abstraction, allowing to handle
    	     ELF64 and ELF32 files in an unified manner.
06may09,v_r  LP64 adaptation (phase #1) : updated code following adaptation
             guidelines.
    	     Removed unused RA_MSK, GPR13_MSK and GPR2_MSK macros and
    	     SYMADDR_REFS type.
29apr08,v_r  Now provide ELF header to elfArchVerify() routine (req
    	     CQ:WIND00090099).
01mar05,v_r  No longer use segment_type.
21feb05,dbt  Cleanup.
06oct04,jn   Clean up comments
18sep04,jn   Move towards shared files between host and target loaders
07apr04,jn   Fix loading problems on SH
04apr04,jn   Clean up - remove unused declarations and 
             development-related comments
04nov03,jn   Make sparc relocation routines available to RTP loader
22oct03,jn   Make some internal elf functions public for use of rtp loader
07may03,pes  PAL conditional compilation cleanup. Phase 2.
17apr03,dbt  Added SIMLINUX support.
04mar03,jmp  added SIMNT support.
16may02,fmk  move the definition of SYM_ADRS to loadLibP.h
08feb02,jn   Add comments about CHECK_FITS and SIGN_EXTEND for ARM. 
09jan02,jn   Reinstate previous definition of CHECK_FITS for ARM.  Keep new
             definition for MIPS.
03jan02,jn   put back LO_VALUE macro for PPC 
27nov01,pad  Added macro definitions (SIGN_EXTEND, etc.)
05sep01,jn   created from loadElfLib.h@@/main/3 - moved utility macros 
             and private type and structure definitions here
*/

#ifndef __INCloadElfLibPh
#define __INCloadElfLibPh

/*
 * WRS_XXX The inclusion of elf.h is needed only so that internal ELF load
 * functions prototypes can be included here, for use by the RTP
 * loader. It should be removed when those function declarations are
 * removed from this header file. 
 */

#include <elf.h>
#include <symLib.h>
#include <private/loadLibP.h>
#include <private/loadFileLibP.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Defines */

#define CHECK_LOW14(val)        (((val & 0xffff8000) == 0) ||           \
                                 ((val & 0xffff8000) == 0xffff8000))

#define CHECK_LOW16(val)        (((val & 0xffff8000) == 0) ||           \
                                 ((val & 0xffff8000) == 0xffff8000))

#define CHECK_LOW16_STRICT(val) (((val & 0xffff0000) == 0) ||           \
                                 ((val & 0xffff0000) == 0xffff0000))

#define CHECK_LOW24(val)        (((val & 0xfe000000) == 0) ||           \
                                 ((val & 0xfe000000) == 0xfe000000))

#ifndef _WRS_LOADER_NO_ELF64_SUPPORT
#define CHECK64_LOW14(val)        (((val & 0xffffffffffff8000) == 0) ||           \
                                   ((val & 0xffffffffffff8000) == 0xffffffffffff8000))
#define CHECK64_LOW16(val)        (((val & 0xffffffffffff8000) == 0) ||           \
                                   ((val & 0xffffffffffff8000) == 0xffffffffffff8000))
#define CHECK64_LOW24(val)        (((val & 0xfffffffffe000000) == 0) ||           \
                                   ((val & 0xfffffffffe000000) == 0xfffffffffe000000))
#define CHECK64_LOW32(val)        (((val & 0xffffffff00000000) == 0) ||           \
                                   ((val & 0xffffffff00000000) == 0xffffffff00000000))
#endif

#define INSERT(buf,value,mask) \
			((buf) = (((buf) & ~(mask)) | ((value) & (mask))))

#define LOW14_INSERT(buf,value) INSERT ((buf), (value), 0x0000fffc)

#define LOW16_VALUE(val)	((val) & 0x0000ffff)
#define LOW16_INSERT(buf,value)	INSERT ((buf), (value), 0x0000ffff)

#define LOW26_VALUE(val)	((val) & 0x03ffffff)
#define LOW26_INSERT(buf,value) INSERT ((buf), (value), 0x03ffffff)

#define LO_VALUE(val)           ((val) & 0x0000ffff)

#define HI_VALUE(val)           (((val) >> 16) & 0x0000ffff)

#define HA_VALUE(val)           ((((val) >> 16)+(((val) >> 15) & 0x1)) & 0xffff)

/* Macro to check if the alignment is a power of 2 */

#define CHECK_2_ALIGN(x)        (((x) & ((x) - 1)) == 0)

/* The binary number that is "n" 1's */

#define MASK(n)		((1 << (n)) - 1)

/* Mask to get the most significant bit of a value on n bit */

#define SIGN_BIT_MASK(n) (1 << ((n) - 1))

/*
 * Sign extension macro. Sign extension replaces all higher bits in <val>
 * with copies of the most significant bit on <nBits>.
 *    <val> is the value we want to sign extend.
 *    <nBits> is the number of significant bits in <val>.
 *
 * Note: the assumption is that the storage is greater than <nBits>.
 */

#define SIGN_EXTEND(val, nBits) \
	(((MASK(nBits) & (val)) ^ SIGN_BIT_MASK(nBits)) - SIGN_BIT_MASK(nBits))

/*
 * Overflow verification macro. It checks that the signed value <val> does
 * not overflow the number of bits specified by <nBits>. The overflow for
 * signed binary numbers is defined as occuring if and only if at least one
 * of the bits beyond <nBits> is not equal to the sign bit of the value
 * truncated on <nBits>.
 *
 * The expression evaluation gives 1 when the value overflows, 0 otherwise.
 *
 * Note: the assumption is that the maximum storage is on 32 bits.
 */

#define CHECK_SIGNED_OVERFLOW(val,nBits) \
	(!(SIGN_EXTEND((val),(nBits)) == (val)))

/* DLL encapsulation */

#ifdef HOST
#define EXTERNAL extern DLL_EXPORT
#else
#define EXTERNAL extern
#endif

/* 
 * In 32-bit mode, remove ELF64 support. It is mandatory for VxWorks64 though.
 * Note that this applies to the host as well (where _WRS_CONFIG_LP64 is never
 * defined).
 */

#ifndef _WRS_CONFIG_LP64
#define _WRS_LOADER_NO_ELF64_SUPPORT
#else /* !_WRS_CONFIG_LP64 */
#ifdef _WRS_LOADER_NO_ELF64_SUPPORT
#error "Cannot remove ELF64 parser support on VxWorks64!"
#endif /* _WRS_LOADER_NO_ELF64_SUPPORT */
#endif /* _WRS_CONFIG_LP64 */

/*
 * Macros to access the ELF header transparently without depending on the
 * 32/64 bitness.
 *
 * These macros (and all of the non _PTR variants below) rely on the fact that
 * the two arithmetic members of the :? operator (as are the structure fields we
 * are accessing) are promoted to a common arithmetic type. In our case, this
 * will be a 64 bits wide value, sufficient to hold both types.
 */

#ifdef _WRS_LOADER_NO_ELF64_SUPPORT
#define ELF_HDR_E_FIELD(pEhdr, field) ((pEhdr)->elf.hdr32.e_##field)
#else /* _WRS_LOADER_NO_ELF64_SUPPORT */
#define ELF_HDR_E_FIELD(pEhdr, field) ((pEhdr)->type == ELF32 ? \
                                         (pEhdr)->elf.hdr32.e_##field : \
                                         (pEhdr)->elf.hdr64.e_##field)
#endif /* !_WRS_LOADER_NO_ELF64_SUPPORT */

#define ELF_HDR_E_IDENT(pEhdr)          ELF_HDR_E_FIELD (pEhdr, ident)
#define ELF_HDR_E_TYPE(pEhdr)           ELF_HDR_E_FIELD (pEhdr, type)
#define ELF_HDR_E_MACHINE(pEhdr)        ELF_HDR_E_FIELD (pEhdr,machine)
#define ELF_HDR_E_VERSION(pEhdr)        ELF_HDR_E_FIELD (pEhdr,version)
#define ELF_HDR_E_ENTRY(pEhdr)          ELF_HDR_E_FIELD (pEhdr,entry)
#define ELF_HDR_E_SHNUM(pEhdr)          ELF_HDR_E_FIELD (pEhdr,shnum)
#define ELF_HDR_E_PHNUM(pEhdr)          ELF_HDR_E_FIELD (pEhdr,phnum)
#define ELF_HDR_E_PHOFF(pEhdr)          ELF_HDR_E_FIELD (pEhdr,phoff)
#define ELF_HDR_E_SHOFF(pEhdr)          ELF_HDR_E_FIELD (pEhdr,shoff)
#define ELF_HDR_E_FLAGS(pEhdr)          ELF_HDR_E_FIELD (pEhdr,flags)
#define ELF_HDR_E_EHSIZE(pEhdr)         ELF_HDR_E_FIELD (pEhdr,ehsize)
#define ELF_HDR_E_PHENTSIZE(pEhdr)      ELF_HDR_E_FIELD (pEhdr,phentsize)
#define ELF_HDR_E_SHENTSIZE(pEhdr)      ELF_HDR_E_FIELD (pEhdr,shentsize)
#define ELF_HDR_E_SHSTRNDX(pEhdr)       ELF_HDR_E_FIELD (pEhdr,shstrndx)

/*
 * Macros to access an ELF program header without depending on the 32/64
 * bitness.
 */

#ifdef _WRS_LOADER_NO_ELF64_SUPPORT
#define ELF_HDR_P_FIELD(pPhdr, field) ((pPhdr)->elf.progHdr32.p_##field)
#else /* _WRS_LOADER_NO_ELF64_SUPPORT */
#define ELF_HDR_P_FIELD(pPhdr, field) ((pPhdr)->type == ELF32 ? \
                                       (pPhdr)->elf.progHdr32.p_##field : \
                                       (pPhdr)->elf.progHdr64.p_##field)
#endif /* !_WRS_LOADER_NO_ELF64_SUPPORT */

#define ELF_HDR_P_TYPE(pPhdr)       ELF_HDR_P_FIELD(pPhdr,type)
#define ELF_HDR_P_FLAGS(pPhdr)      ELF_HDR_P_FIELD(pPhdr,flags)
#define ELF_HDR_P_OFFSET(pPhdr)     ELF_HDR_P_FIELD(pPhdr,offset)
#define ELF_HDR_P_VADDR(pPhdr)      ELF_HDR_P_FIELD(pPhdr,vaddr)
#define ELF_HDR_P_PADDR(pPhdr)      ELF_HDR_P_FIELD(pPhdr,paddr)
#define ELF_HDR_P_FILESZ(pPhdr)     ELF_HDR_P_FIELD(pPhdr,filesz)
#define ELF_HDR_P_MEMSZ(pPhdr)      ELF_HDR_P_FIELD(pPhdr,memsz)
#define ELF_HDR_P_ALIGN(pPhdr)      ELF_HDR_P_FIELD(pPhdr,align)

/*
 * Macros to access an ELF section header without depending on the 32/64
 * bitness.
 */

#ifdef _WRS_LOADER_NO_ELF64_SUPPORT
#define ELF_HDR_SH_FIELD(pShdr, field) ((pShdr)->elf.scnHdr32.sh_##field)
#else /* _WRS_LOADER_NO_ELF64_SUPPORT */
#define ELF_HDR_SH_FIELD(pShdr, field) ((pShdr)->type == ELF32 ? \
                                       (pShdr)->elf.scnHdr32.sh_##field : \
                                       (pShdr)->elf.scnHdr64.sh_##field)
#endif /* !_WRS_LOADER_NO_ELF64_SUPPORT */

#define ELF_HDR_SH_NAME(pShdr)       ELF_HDR_SH_FIELD(pShdr,name)
#define ELF_HDR_SH_TYPE(pShdr)       ELF_HDR_SH_FIELD(pShdr,type)
#define ELF_HDR_SH_FLAGS(pShdr)      ELF_HDR_SH_FIELD(pShdr,flags)
#define ELF_HDR_SH_ADDR(pShdr)	     ELF_HDR_SH_FIELD(pShdr,addr)
#define ELF_HDR_SH_OFFSET(pShdr)     ELF_HDR_SH_FIELD(pShdr,offset)
#define ELF_HDR_SH_SIZE(pShdr)	     ELF_HDR_SH_FIELD(pShdr,size)
#define ELF_HDR_SH_LINK(pShdr)	     ELF_HDR_SH_FIELD(pShdr,link)
#define ELF_HDR_SH_INFO(pShdr)       ELF_HDR_SH_FIELD(pShdr,info)
#define ELF_HDR_SH_ADDRALIGN(pShdr)  ELF_HDR_SH_FIELD(pShdr,addralign)
#define ELF_HDR_SH_ENTSIZE(pShdr)    ELF_HDR_SH_FIELD(pShdr,entsize)

/*
 * Macros to access an ELF symbol without depending on the 32/64
 * bitness.
 */

#ifdef _WRS_LOADER_NO_ELF64_SUPPORT
#define ELF_SYM_ST_FIELD(pSym, field) ((pSym)->elf.sym32.st_##field)
#else /* _WRS_LOADER_NO_ELF64_SUPPORT */
#define ELF_SYM_ST_FIELD(pSym, field) ((pSym)->type == ELF32 ?		\
				       (pSym)->elf.sym32.st_##field :	\
				       (pSym)->elf.sym64.st_##field)
#endif /* !_WRS_LOADER_NO_ELF64_SUPPORT */

#define ELF_SYM_ST_NAME(pSym)	    ELF_SYM_ST_FIELD(pSym,name)
#define ELF_SYM_ST_VALUE(pSym)	    ELF_SYM_ST_FIELD(pSym,value)
#define ELF_SYM_ST_SIZE(pSym)	    ELF_SYM_ST_FIELD(pSym,size)
#define ELF_SYM_ST_INFO(pSym)	    ELF_SYM_ST_FIELD(pSym,info)
#define ELF_SYM_ST_OTHER(pSym)	    ELF_SYM_ST_FIELD(pSym,other)
#define ELF_SYM_ST_SHNDX(pSym)	    ELF_SYM_ST_FIELD(pSym,shndx)

#ifdef _WRS_LOADER_NO_ELF64_SUPPORT
#define ELF_SYM_ST_BIND(pSym)	(ELF32_ST_BIND ((pSym)->elf.sym32.st_info))
#define ELF_SYM_ST_TYPE(pSym)	(ELF32_ST_TYPE ((pSym)->elf.sym32.st_info))
#else /* _WRS_LOADER_NO_ELF64_SUPPORT */
#define ELF_SYM_ST_BIND(pSym)	((pSym)->type == ELF32 ? \
				ELF32_ST_BIND ((pSym)->elf.sym32.st_info) : \
				ELF64_ST_BIND ((pSym)->elf.sym64.st_info))
#define ELF_SYM_ST_TYPE(pSym)	((pSym)->type == ELF32 ? \
				ELF32_ST_TYPE ((pSym)->elf.sym32.st_info) : \
				ELF64_ST_TYPE ((pSym)->elf.sym64.st_info))
#endif /* !_WRS_LOADER_NO_ELF64_SUPPORT */

/* Macros to access the unified reloc structure */

#ifdef _WRS_LOADER_NO_ELF64_SUPPORT
#define ELF_RELOC_R_FIELD(pRel, field)  ((pRel)->reloc_type == REL_32 ?	    \
					 (pRel)->reloc.rel32.r_##field :    \
					  ((pRel)->reloc_type == RELA_32 ?  \
					   (pRel)->reloc.rela32.r_##field : 0))
#else /* _WRS_LOADER_NO_ELF64_SUPPORT */
#define ELF_RELOC_R_FIELD(pRel, field)  ((pRel)->reloc_type == REL_32 ?	    \
					 (pRel)->reloc.rel32.r_##field :    \
					  ((pRel)->reloc_type == RELA_32 ?  \
					   (pRel)->reloc.rela32.r_##field : \
					   ((pRel)->reloc_type == REL_64 ?  \
					    (pRel)->reloc.rel64.r_##field : \
					    (pRel)->reloc.rela64.r_##field)))
#endif /* !_WRS_LOADER_NO_ELF64_SUPPORT */

#define ELF_RELOC_R_OFFSET(pRel)    ELF_RELOC_R_FIELD(pRel,offset)
#define ELF_RELOC_R_INFO(pRel)      ELF_RELOC_R_FIELD(pRel,info)

#ifdef _WRS_LOADER_NO_ELF64_SUPPORT
#define ELF_RELOC_R_ADDEND(pRel)	((pRel)->reloc_type == RELA_32 ?    \
					 (pRel)->reloc.rela32.r_addend : 0)
#else /* _WRS_LOADER_NO_ELF64_SUPPORT */
#define ELF_RELOC_R_ADDEND(pRel)	((pRel)->reloc_type == RELA_32 ?    \
					 (pRel)->reloc.rela32.r_addend :    \
					  ((pRel)->reloc_type == RELA_64 ?  \
					   (pRel)->reloc.rela64.r_addend : 0))
#endif /* !_WRS_LOADER_NO_ELF64_SUPPORT */

#ifdef _WRS_LOADER_NO_ELF64_SUPPORT
#define ELF_RELOC_R_SUB(pRel,sub)   ((pRel)->reloc_type == REL_32 ?	       \
			    ELF32_R_##sub ((pRel)->reloc.rel32.r_info) :       \
			     ((pRel)->reloc_type == RELA_32 ?		       \
			      ELF32_R_##sub ((pRel)->reloc.rela32.r_info) : 0))
#else /* _WRS_LOADER_NO_ELF64_SUPPORT */
#define ELF_RELOC_R_SUB(pRel,sub)   ((pRel)->reloc_type == REL_32 ?	       \
			    ELF32_R_##sub ((pRel)->reloc.rel32.r_info) :       \
			     ((pRel)->reloc_type == RELA_32 ?		       \
			      ELF32_R_##sub ((pRel)->reloc.rela32.r_info) :    \
			       ((pRel)->reloc_type == REL_64 ?		       \
			        ELF64_R_##sub ((pRel)->reloc.rel64.r_info) :   \
			         ELF64_R_##sub ((pRel)->reloc.rela64.r_info))))
#endif /* !_WRS_LOADER_NO_ELF64_SUPPORT */
				       
#define ELF_RELOC_R_TYPE(pRel)	    ELF_RELOC_R_SUB(pRel,TYPE) 
#define ELF_RELOC_R_SYM(pRel)	    ELF_RELOC_R_SUB(pRel,SYM) 

/*
 * Macros to access the ELF header transparently without depending on the
 * 32/64 bitness (pointer versions).
 *
 * Note how we have to cast the union fields to void, otherwise the compiler
 * will complain as both operands of the ?: operator don't have the same type
 * (when the ELF32 and ELF64 types differ).
 */

#ifdef _WRS_LOADER_NO_ELF64_SUPPORT
#define ELF_HDR_E_FIELD_PTR(pEhdr, field)   \
					((void *) &(pEhdr)->elf.hdr32.e_##field)
#else /* _WRS_LOADER_NO_ELF64_SUPPORT */
#define ELF_HDR_E_FIELD_PTR(pEhdr, field) ((pEhdr)->type == ELF32 ? \
                                    ((void *) &(pEhdr)->elf.hdr32.e_##field) :\
                                    ((void *) &(pEhdr)->elf.hdr64.e_##field))
#endif /* !_WRS_LOADER_NO_ELF64_SUPPORT */

#define ELF_HDR_E_TYPE_PTR(pEhdr)       ELF_HDR_E_FIELD_PTR (pEhdr,type)
#define ELF_HDR_E_MACHINE_PTR(pEhdr)    ELF_HDR_E_FIELD_PTR (pEhdr,machine)
#define ELF_HDR_E_VERSION_PTR(pEhdr)    ELF_HDR_E_FIELD_PTR (pEhdr,version)
#define ELF_HDR_E_ENTRY_PTR(pEhdr)      ELF_HDR_E_FIELD_PTR (pEhdr,entry)
#define ELF_HDR_E_PHOFF_PTR(pEhdr)      ELF_HDR_E_FIELD_PTR (pEhdr,phoff)
#define ELF_HDR_E_SHOFF_PTR(pEhdr)      ELF_HDR_E_FIELD_PTR (pEhdr,shoff)
#define ELF_HDR_E_FLAGS_PTR(pEhdr)      ELF_HDR_E_FIELD_PTR (pEhdr,flags)
#define ELF_HDR_E_EHSIZE_PTR(pEhdr)     ELF_HDR_E_FIELD_PTR (pEhdr,ehsize)
#define ELF_HDR_E_PHENTSIZE_PTR(pEhdr)  ELF_HDR_E_FIELD_PTR (pEhdr,phentsize)
#define ELF_HDR_E_PHNUM_PTR(pEhdr)      ELF_HDR_E_FIELD_PTR (pEhdr,phnum)
#define ELF_HDR_E_SHENTSIZE_PTR(pEhdr)  ELF_HDR_E_FIELD_PTR (pEhdr,shentsize)
#define ELF_HDR_E_SHNUM_PTR(pEhdr)      ELF_HDR_E_FIELD_PTR (pEhdr,shnum)
#define ELF_HDR_E_SHSTRNDX_PTR(pEhdr)   ELF_HDR_E_FIELD_PTR (pEhdr,shstrndx)

/*
 * Macros to access an ELF header program header without depending on the
 * 32/64 bitness (pointer versions).
 *
 * Same remark as above regarding the casts which are done.
 */

#ifdef _WRS_LOADER_NO_ELF64_SUPPORT
#define ELF_HDR_P_FIELD_PTR(pPhdr, field) \
				    ((void *) &(pPhdr)->elf.progHdr32.p_##field)
#else /* _WRS_LOADER_NO_ELF64_SUPPORT */
#define ELF_HDR_P_FIELD_PTR(pPhdr, field) ((pPhdr)->type == ELF32 ?	    \
			    ((void *) &(pPhdr)->elf.progHdr32.p_##field) :  \
			    ((void *) &(pPhdr)->elf.progHdr64.p_##field))
#endif /* !_WRS_LOADER_NO_ELF64_SUPPORT */

#define ELF_HDR_P_TYPE_PTR(pPhdr)       ELF_HDR_P_FIELD_PTR(pPhdr,type)
#define ELF_HDR_P_FLAGS_PTR(pPhdr)      ELF_HDR_P_FIELD_PTR(pPhdr,flags)
#define ELF_HDR_P_OFFSET_PTR(pPhdr)     ELF_HDR_P_FIELD_PTR(pPhdr,offset)
#define ELF_HDR_P_VADDR_PTR(pPhdr)      ELF_HDR_P_FIELD_PTR(pPhdr,vaddr)
#define ELF_HDR_P_PADDR_PTR(pPhdr)      ELF_HDR_P_FIELD_PTR(pPhdr,paddr)
#define ELF_HDR_P_FILESZ_PTR(pPhdr)     ELF_HDR_P_FIELD_PTR(pPhdr,filesz)
#define ELF_HDR_P_MEMSZ_PTR(pPhdr)      ELF_HDR_P_FIELD_PTR(pPhdr,memsz)
#define ELF_HDR_P_ALIGN_PTR(pPhdr)      ELF_HDR_P_FIELD_PTR(pPhdr,align)

/*
 * Macros to access an ELF header section header without depending on the
 * 32/64 bitness (pointer versions).
 *
 * Same remark as above regarding the casts which are done.
 */

#ifdef _WRS_LOADER_NO_ELF64_SUPPORT
#define ELF_HDR_SH_PTR(pShdr)                                                  \
                        ((void *) &(pShdr)->elf.scnHdr32)
#define ELF_HDR_SH_FIELD_PTR(pShdr, field)                                     \
                        ((void *) &(pShdr)->elf.scnHdr32.sh_##field)
#else /* _WRS_LOADER_NO_ELF64_SUPPORT */
#define ELF_HDR_SH_PTR(pShdr)           ((pShdr)->type == ELF32 ?              \
                        ((void *) &(pShdr)->elf.scnHdr32) :                    \
                        ((void *) &(pShdr)->elf.scnHdr64))
#define ELF_HDR_SH_FIELD_PTR(pShdr, field) ((pShdr)->type == ELF32 ?           \
                        ((void *) &(pShdr)->elf.scnHdr32.sh_##field) :         \
                        ((void *) &(pShdr)->elf.scnHdr64.sh_##field))
#endif /* !_WRS_LOADER_NO_ELF64_SUPPORT */

#define ELF_HDR_SH_NAME_PTR(pShdr)       ELF_HDR_SH_FIELD_PTR(pShdr,name)
#define ELF_HDR_SH_TYPE_PTR(pShdr)       ELF_HDR_SH_FIELD_PTR(pShdr,type)
#define ELF_HDR_SH_FLAGS_PTR(pShdr)      ELF_HDR_SH_FIELD_PTR(pShdr,flags)
#define ELF_HDR_SH_ADDR_PTR(pShdr)       ELF_HDR_SH_FIELD_PTR(pShdr,addr)
#define ELF_HDR_SH_OFFSET_PTR(pShdr)     ELF_HDR_SH_FIELD_PTR(pShdr,offset)
#define ELF_HDR_SH_SIZE_PTR(pShdr)       ELF_HDR_SH_FIELD_PTR(pShdr,size)
#define ELF_HDR_SH_LINK_PTR(pShdr)       ELF_HDR_SH_FIELD_PTR(pShdr,link)
#define ELF_HDR_SH_INFO_PTR(pShdr)       ELF_HDR_SH_FIELD_PTR(pShdr,info)
#define ELF_HDR_SH_ADDRALIGN_PTR(pShdr)  ELF_HDR_SH_FIELD_PTR(pShdr,addralign)
#define ELF_HDR_SH_ENTSIZE_PTR(pShdr)    ELF_HDR_SH_FIELD_PTR(pShdr,entsize)

/*
 * Macros to access an ELF symbol without depending on the 32/64 bitness
 * (pointer versions).
 *
 * Same remark as above regarding the casts which are done.
 */

#ifdef _WRS_LOADER_NO_ELF64_SUPPORT
#define ELF_SYM_ST_FIELD_PTR(pSym, field) \
					((void *) &(pSym)->elf.sym32.st_##field)
#else /* _WRS_LOADER_NO_ELF64_SUPPORT */
#define ELF_SYM_ST_FIELD_PTR(pSym, field) ((pSym)->type == ELF32 ?	 \
			    ((void *) &(pSym)->elf.sym32.st_##field) :   \
			    ((void *) &(pSym)->elf.sym64.st_##field))
#endif /* !_WRS_LOADER_NO_ELF64_SUPPORT */

#define ELF_SYM_ST_NAME_PTR(pSym)       ELF_SYM_ST_FIELD_PTR(pSym,name)
#define ELF_SYM_ST_VALUE_PTR(pSym)      ELF_SYM_ST_FIELD_PTR(pSym,value)
#define ELF_SYM_ST_SIZE_PTR(pSym)       ELF_SYM_ST_FIELD_PTR(pSym,size)
#define ELF_SYM_ST_INFO_PTR(pSym)       ELF_SYM_ST_FIELD_PTR(pSym,info)
#define ELF_SYM_ST_OTHER_PTR(pSym)      ELF_SYM_ST_FIELD_PTR(pSym,other)
#define ELF_SYM_ST_SHNDX_PTR(pSym)      ELF_SYM_ST_FIELD_PTR(pSym,shndx)

/*
 * Macros to access the unified reloc structure without depending on the 32/64
 * bitness (pointer versions).
 *
 * Same remark as above regarding the casts which are done.
 */

#ifdef _WRS_LOADER_NO_ELF64_SUPPORT
#define ELF_RELOC_R_FIELD_PTR(pRel, field)  ((pRel)->reloc_type == REL_32 ?   \
				((void *) &(pRel)->reloc.rel32.r_##field) :   \
					  ((pRel)->reloc_type == RELA_32 ?    \
			    ((void *) &(pRel)->reloc.rela32.r_##field) : NULL))
#else /* _WRS_LOADER_NO_ELF64_SUPPORT */
#define ELF_RELOC_R_FIELD_PTR(pRel, field)  ((pRel)->reloc_type == REL_32 ?   \
				((void *) &(pRel)->reloc.rel32.r_##field) :   \
					  ((pRel)->reloc_type == RELA_32 ?    \
				((void *) &(pRel)->reloc.rela32.r_##field) :  \
					   ((pRel)->reloc_type == REL_64 ?    \
				((void *) &(pRel)->reloc.rel64.r_##field) :   \
				((void *) &(pRel)->reloc.rela64.r_##field))))
#endif /* !_WRS_LOADER_NO_ELF64_SUPPORT */


#define ELF_RELOC_R_OFFSET_PTR(pRel)    ELF_RELOC_R_FIELD_PTR(pRel,offset)
#define ELF_RELOC_R_INFO_PTR(pRel)      ELF_RELOC_R_FIELD_PTR(pRel,info)

#ifdef _WRS_LOADER_NO_ELF64_SUPPORT
#define ELF_RELOC_R_ADDEND_PTR(pRel)	((pRel)->reloc_type == RELA_32 ?      \
			    ((void *) &(pRel)->reloc.rela32.r_addend) : NULL)
#else /* _WRS_LOADER_NO_ELF64_SUPPORT */
#define ELF_RELOC_R_ADDEND_PTR(pRel)	((pRel)->reloc_type == RELA_32 ?      \
				((void *) &(pRel)->reloc.rela32.r_addend) :   \
					  ((pRel)->reloc_type == RELA_64 ?    \
			    ((void *) &(pRel)->reloc.rela64.r_addend) : NULL))
#endif /* !_WRS_LOADER_NO_ELF64_SUPPORT */

/* 
 * ELF abstraction field sizes. The UCHAR one is not really necessary but this
 * allows clean code abstraction.
 */

#ifdef _WRS_LOADER_NO_ELF64_SUPPORT
#define ELF_FIELD_SIZE(pEhdr, field)	(sizeof (Elf32_##field))
#else /* _WRS_LOADER_NO_ELF64_SUPPORT */
#define ELF_FIELD_SIZE(pEhdr, field) ((pEhdr)->type == ELF32 ? \
                            sizeof (Elf32_##field) : sizeof (Elf64_##field))
#endif /* !_WRS_LOADER_NO_ELF64_SUPPORT */

#define ELF_HALF_SIZE(pEhdr)    ELF_FIELD_SIZE(pEhdr,Half)
#define ELF_WORD_SIZE(pEhdr)    ELF_FIELD_SIZE(pEhdr,Word)
#define ELF_XWORD_SIZE(pEhdr)   ELF_FIELD_SIZE(pEhdr,Xword)
#define ELF_SWORD_SIZE(pEhdr)   ELF_FIELD_SIZE(pEhdr,Sword)
#define ELF_SXWORD_SIZE(pEhdr)  ELF_FIELD_SIZE(pEhdr,Sxword)
#define ELF_ADDR_SIZE(pEhdr)    ELF_FIELD_SIZE(pEhdr,Addr)
#define ELF_OFF_SIZE(pEhdr)	ELF_FIELD_SIZE(pEhdr,Off)
#define ELF_EHDR_SIZE(pEhdr)    ELF_FIELD_SIZE(pEhdr,Ehdr)
#define ELF_PHDR_SIZE(pEhdr)    ELF_FIELD_SIZE(pEhdr,Phdr)
#define ELF_SHDR_SIZE(pEhdr)    ELF_FIELD_SIZE(pEhdr,Shdr)
#define ELF_UCHAR_SIZE(pEhdr)   (sizeof (unsigned char))

#ifdef _WRS_LOADER_NO_ELF64_SUPPORT
#define ELF_SYM_SIZE(pSym)      sizeof (Elf32_Sym)
#define ELF_RELOC_SIZE(pRel)	((pRel)->reloc_type == REL_32 ?		\
				 sizeof (Elf32_Rel) :			\
				  ((pRel)->reloc_type == RELA_32 ?	\
				   sizeof (Elf32_Rela) : 0))
#define ELF_RELOC_IS_32BITS(pRel)   TRUE
#define ELF_WORD_OR_XWORD_SIZE(pEhdr)	(sizeof (Elf32_Word))
#define ELF_SWORD_OR_SXWORD_SIZE(pEhdr)	(sizeof (Elf32_Sword))
#else /* _WRS_LOADER_NO_ELF64_SUPPORT */
#define ELF_SYM_SIZE(pSym)      ((pSym)->type == ELF32 ?                \
                                 sizeof (Elf32_Sym) : sizeof (Elf64_Sym))
#define ELF_RELOC_SIZE(pRel)	((pRel)->reloc_type == REL_32 ?		\
				 sizeof (Elf32_Rel) :			\
				  ((pRel)->reloc_type == RELA_32 ?	\
				   sizeof (Elf32_Rela) :		\
				    ((pRel)->reloc_type == REL_64 ?	\
				     sizeof (Elf64_Rel) :		\
				      ((pRel)->reloc_type == RELA_64 ?	\
				       sizeof (Elf64_Rela) : 0))))

#define ELF_RELOC_IS_32BITS(pRel)   ((pRel)->reloc_type == REL_32 ||	\
				     (pRel)->reloc_type == RELA_32)

#define ELF_WORD_OR_XWORD_SIZE(pEhdr)	(pEhdr->type == ELF32 ? \
					 sizeof (Elf32_Word) :	\
					 sizeof (Elf64_Xword))

#define ELF_SWORD_OR_SXWORD_SIZE(pEhdr)	(pEhdr->type == ELF32 ? \
					 sizeof (Elf32_Sword) :	\
					 sizeof (Elf64_Sxword))
#endif /* !_WRS_LOADER_NO_ELF64_SUPPORT */

/* Sync an abstraction ELF class with one another */

#ifdef _WRS_LOADER_NO_ELF64_SUPPORT
#define ELF_ABSTR_CLASS_SYNC(pTgtAbstr,pOrigAbstr)
#else /* _WRS_LOADER_NO_ELF64_SUPPORT */
#define ELF_ABSTR_CLASS_SYNC(pTgtAbstr,pOrigAbstr) \
					((pTgtAbstr)->type = (pOrigAbstr)->type)
#endif /* !_WRS_LOADER_NO_ELF64_SUPPORT */

/* Check whether an ELF abstraction is ELF32 or ELF64 */

#ifdef _WRS_LOADER_NO_ELF64_SUPPORT
#define ELF_ABSTR_IS_ELF64(pAbstr)  0
#define ELF_ABSTR_IS_ELF32(pAbstr)  1
#else /* _WRS_LOADER_NO_ELF64_SUPPORT */
#define ELF_ABSTR_IS_ELF64(pAbstr) ((pAbstr)->type == ELF64)
#define ELF_ABSTR_IS_ELF32(pAbstr) ((pAbstr)->type == ELF32)
#endif /* !_WRS_LOADER_NO_ELF64_SUPPORT */

/* ELF abstractions type debug outputs */

#ifdef _WRS_LOADER_NO_ELF64_SUPPORT
#define ELF_ABSTR_CLASS_TO_STR(pAbstr)	("ELF32")
#define ELF_RELOC_ABSTR_TO_STR(pReloc) \
				((pReloc)->reloc_type == REL_32 ? "REL_32" :   \
				((pReloc)->reloc_type == RELA_32 ? "RELA_32" : \
				"Unknown"))
#else /* _WRS_LOADER_NO_ELF64_SUPPORT */
#define ELF_ABSTR_CLASS_TO_STR(pAbstr)	((pAbstr)->type == ELF32 ? "ELF32" :   \
					 ((pAbstr)->type == ELF64 ? "ELF64" :  \
					 "Unknown"))
#define ELF_RELOC_ABSTR_TO_STR(pReloc) \
				((pReloc)->reloc_type == REL_32 ? "REL_32" :   \
				((pReloc)->reloc_type == RELA_32 ? "RELA_32" : \
				((pReloc)->reloc_type == REL_64 ? "REL_64" :   \
				((pReloc)->reloc_type == RELA_64 ? "RELA_64" : \
				"Unknown"))))
#endif /* !_WRS_LOADER_NO_ELF64_SUPPORT */

/* Relocation internal type modification */

#ifdef _WRS_LOADER_NO_ELF64_SUPPORT
#define ELF_RELOC_TYPE_SET(pRelHdr, pRel)			    \
		    if (ELF_HDR_SH_TYPE (pRelHdr) == SHT_REL)	    \
			(pRel)->reloc_type = REL_32;		    \
		    else if (ELF_HDR_SH_TYPE (pRelHdr) == SHT_RELA) \
			(pRel)->reloc_type = RELA_32;
#else /* _WRS_LOADER_NO_ELF64_SUPPORT */
#define ELF_RELOC_TYPE_SET(pRelHdr, pRel)			    \
		    if (ELF_HDR_SH_TYPE (pRelHdr) == SHT_REL)	    \
			{					    \
			if (ELF_ABSTR_IS_ELF32 (pRelHdr))	    \
			    (pRel)->reloc_type = REL_32;	    \
			else					    \
			    (pRel)->reloc_type = REL_64;	    \
			}					    \
		    else if (ELF_HDR_SH_TYPE (pRelHdr) == SHT_RELA) \
			{					    \
			if (ELF_ABSTR_IS_ELF32 (pRelHdr))	    \
			    (pRel)->reloc_type = RELA_32;	    \
			else					    \
			    (pRel)->reloc_type = RELA_64;	    \
			}
#endif /* !_WRS_LOADER_NO_ELF64_SUPPORT */

/* Typedefs */

typedef struct segment_info_desc /* Info about a loadable segment      */
    {
    SL_NODE	segInfoNode;	/* Point to next node in list 		    */
    SL_LIST	scnInfoList;	/* List of info nodes about sections in seg */
    UINT32	type;		/* segment's type                           */
    void *      address;	/* segment's address                        */
    size_t	size;		/* segment's size                        */
    off_t	offset;		/* segment's offset in file                */
    off_t	offsetInMem;	/* seg's offset from start of mem alloc'd */
    size_t	alignment;      /* segment alignment */
    BOOL        memAllocatedByCaller; /* True iff the caller allocated mem. */
    BOOL        segHasMemFootprint; /* segment size */
    } SEGMENT_INFO_DESC;

typedef struct
    {
    UINT32 *    pLoadScnHdrIdxs;        /* loadable sections header index tbl */
    UINT32 *    pSymTabScnHdrIdxs;      /* sym table sections header idx tbl */
    UINT32 *    pRelScnHdrIdxs;         /* reloc info sections header idx tbl */
    UINT32 *    pStrTabScnHdrIdxs;      /* str table sections header idx tbl */
    } IDX_TBLS;

#ifndef _WRS_LOADER_NO_ELF64_SUPPORT
/* 
 * ELF abstraction type field. We start our enum at 1 so that we can more easily
 * detect when no type is set (as we bzero the ELF abstraction structure).
 */

typedef enum elf_type
    {
    ELF32 = 1,
    ELF64
    } ELF_TYPE;
#endif /* _WRS_LOADER_NO_ELF64_SUPPORT */

/* 
 * ELF relocation type field. Same remark as above concerning the fact that we
 * start at 1.
 */

typedef enum reloc_type
    {
    REL_32 = 1,
#ifndef _WRS_LOADER_NO_ELF64_SUPPORT
    REL_64,
    RELA_64,
#endif /* !_WRS_LOADER_NO_ELF64_SUPPORT */
    RELA_32
    } RELOC_TYPE;

/* ELF file header encapsulation (managed by the ELF_HDR_E_XXX macros) */

typedef struct elf_ehdr
    {
#ifndef _WRS_LOADER_NO_ELF64_SUPPORT
    ELF_TYPE     type;
    void *       tocBase;
    BOOL         tocFound; 
#endif
    union
        {
        Elf32_Ehdr  hdr32;
#ifndef _WRS_LOADER_NO_ELF64_SUPPORT
        Elf64_Ehdr  hdr64;
#endif
        } elf;
    } ELF_EHDR;

/* ELF program header encapsulation (managed by the ELF_HDR_P_XXX macros) */

typedef struct elf_phdr
    {
#ifndef _WRS_LOADER_NO_ELF64_SUPPORT
    ELF_TYPE     type;
#endif
    union
        {
        Elf32_Phdr progHdr32; 
#ifndef _WRS_LOADER_NO_ELF64_SUPPORT
        Elf64_Phdr progHdr64;
#endif
        } elf;
    } ELF_PHDR;

/* ELF section header encapsulation (managed by the ELF_HDR_SH_XXX macros) */

typedef struct elf_shdr
    {
#ifndef _WRS_LOADER_NO_ELF64_SUPPORT
    ELF_TYPE     type;
#endif
    union
        {
        Elf32_Shdr scnHdr32;
#ifndef _WRS_LOADER_NO_ELF64_SUPPORT
        Elf64_Shdr scnHdr64;
#endif
        } elf;
    } ELF_SHDR;

/* ELF object file encapsulation */

typedef struct elf_desc
    {
    ELF_EHDR	header;		/* ELF file header */
    ELF_PHDR *	pProgHdr;	/* ELF program headers table */
    ELF_SHDR *	pSecHdr;	/* ELF section headers table */
    ELF_SHDR *	pSymtabHdr;	/* ELF symbol table header */
    } ELF_DESC;

/* ELF symbol encapsulation (managed by the ELF_SYM_ST_XXX macros) */

typedef struct elf_sym
    {
#ifndef _WRS_LOADER_NO_ELF64_SUPPORT
    ELF_TYPE     type;
#endif
    union
        {
        Elf32_Sym sym32;
#ifndef _WRS_LOADER_NO_ELF64_SUPPORT
        Elf64_Sym sym64;
#endif
        } elf;
    } ELF_SYM;

/* ELF relocation encapsulation (managed by the ELF_RELOC_R_XXX macros) */

typedef struct elf_reloc
    {
    RELOC_TYPE	reloc_type;
    union
	{
	Elf32_Rel   rel32;
	Elf32_Rela  rela32;
#ifndef _WRS_LOADER_NO_ELF64_SUPPORT
	Elf64_Rel   rel64;
	Elf64_Rela  rela64;
#endif
	} reloc;
    } ELF_RELOC;

typedef Elf32_Word ABI_TYPE;
typedef Elf32_Word ISA_TYPE;

typedef STATUS (* ELF_ARCH_INIT_HOOK) (void);
typedef STATUS (* ELF_ARCH_SYM_PROCESS_HOOK) (char * symName, 
					      void ** pSymAddr,
					      UINT32 * pSymAssoc,
                                              ELF_SYM * pElfSym,
                                              SYM_EXT_TYPE * pSymExtType,
                                              SL_NODE ** ppScnInfoTbl,
                                              MODULE_ID moduleId,
                                              LOAD_FLAG_T loadFlag,
                                              ELF_EHDR * pEhdr);
typedef STATUS (* ELF_ARCH_MDL_LOAD_HOOK) (MODULE_ID moduleId,
                                           LOAD_FLAG_T loadFlag,
                                           BOOL swapIsRequired,
                                           LOAD_MODULE_INFO * pLdMdlInfo,
                                           SL_LIST * pSegDescList,
                                           SL_NODE ** ppScnInfoTbl,
                                           SYM_INFO_TBL symInfoTbl,
                                           STATUS loadStatus);

/* Function declarations */

EXTERNAL STATUS loadElfKernelAbiAndIsaGet (ABI_TYPE * pKernelAbi, 
					   ISA_TYPE * pKernelIsa);
EXTERNAL STATUS loadElfRelUEntryRead (LOAD_MODULE_INFO * pLoadModuleInfo,
				      ELF_EHDR * pEhdr, ELF_RELOC * pReloc, 
				      BOOL swapIsRequired);
EXTERNAL STATUS loadElfRelEntryRead (LOAD_MODULE_INFO * pLoadModuleInfo, 
				     Elf32_Rel * pReloc, BOOL swapIsRequired);
EXTERNAL STATUS loadElfRelaEntryRead (LOAD_MODULE_INFO * pLoadModuleInfo, 
				      Elf32_Rela * pReloc, BOOL swapIsRequired);
EXTERNAL STATUS loadElf32SectionHeaderCheck (Elf32_Shdr * pScnHdr,
                                          Elf32_Half scnHdrNum);
EXTERNAL STATUS loadElfSectionHeaderCheck (ELF_SHDR * pScnHdr); 
EXTERNAL STATUS loadElfProgramHeaderTableReadAndCheck (
					    LOAD_MODULE_INFO * pLoadModuleInfo, 
					    ELF_EHDR *   pEhdr,
					    ELF_PHDR *   pPhdr,
					    BOOL swapIsRequired);
EXTERNAL STATUS loadElf32ProgramHeaderTableReadAndCheck (
                                           LOAD_MODULE_INFO * pLoadModuleInfo,
					    Elf32_Phdr * pProgHdrTbl, 
                                           Elf32_Off offset,
                                           Elf32_Half progHdrNumber,
					    BOOL swapIsRequired);
EXTERNAL STATUS loadElfFileHeaderReadAndCheck (LOAD_MODULE_INFO * pLoadMdlInfo,
					       ELF_EHDR * pElfHdr,
					       BOOL * swapIsRequired,
					       BOOL forcedLoad);
EXTERNAL STATUS loadElf32FileHeaderReadAndCheck 
					      (LOAD_MODULE_INFO * pLoadMdlInfo,
					       Elf32_Ehdr * pHdr, 
					       BOOL * swapIsRequired,
					       BOOL forcedLoad);
EXTERNAL STATUS elfArchReloc (BOOL swapNeeded, 
			      LOAD_MODULE_INFO * pLoadModuleInfo,
			      ELF_EHDR * pEhdr, ELF_SHDR * pRelHdr, 
			      SCN_ADRS scnAddr, 
			      INT64 deltaBaseAddr, SYM_INFO_TBL symInfoTbl);
EXTERNAL STATUS elfArch32Reloc (BOOL swapNeeded, 
				LOAD_MODULE_INFO * pLoadModuleInfo,
			      Elf32_Shdr * pRelHdr, SCN_ADRS scnAddr, 
			      INT64 deltaBaseAddr, SYM_INFO_TBL symInfoTbl);
EXTERNAL BOOL	elfArchVerify (ELF_EHDR * pEhdr);
EXTERNAL STATUS loadElfSymbolEntryRead (LOAD_MODULE_INFO * pLoadModuleInfo,
					ELF_EHDR * pEhdr, ELF_SYM * pSymbol,
					BOOL swapIsRequired);
EXTERNAL STATUS loadElfSectionHeaderReadAndCheck (LOAD_MODULE_INFO * pMdlInfo,
						  ELF_EHDR * pEhdr, 
						  ELF_SHDR * pScnHdrTbl,
						  BOOL swapIsRequired);

#ifdef  _WRS_CONFIG_BRANCH_ISLAND_SUPPORT
EXTERNAL size_t elfArchBISizeGet (void);
EXTERNAL BOOL   elfArchBIRTypeCheck (ELF_RELOC * pRelocCmd);
#endif  /* _WRS_CONFIG_BRANCH_ISLAND_SUPPORT */

#ifndef HOST
extern STATUS elfArmStandaloneThumbSymTblAdd (SYMBOL_ID symId);
#endif /* !HOST */

#ifdef __cplusplus
}
#endif

#endif /* __INCloadElfLibPh */
