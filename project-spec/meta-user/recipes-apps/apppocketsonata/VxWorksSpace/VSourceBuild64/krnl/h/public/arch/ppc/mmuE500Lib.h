/* mmuE500Lib.h - mmu library for PowerPC E500 series */

/*
 * Copyright (c) 2001-2005, 2007, 2009, 2011, 2013, 2016-2017
 * Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
26apr17,mcm  Fixed alignment of PPC_TLB_SAVE structure
12sep16,h_k  moved tlb1Esel field to mmuPpcTlbSaveArea for non-SMT.
             reordered members in TLB1ESEL structure.
             optimization in TLB miss handler.
             changed PPC_TLB_SAVE structure for _WRS_CONFIG_UNIFIED_MMU_LIB.
             (V7PRO-3268)
             shrank MMU page table to half in LP64.
16jul15,w_x  Rename new MMU library VSB option to UNIFIED_MMU_LIB (F2518)
21may15,syt  change the macro value of TLB1_ENTRY_START from 4 to 6 (F2518)
16mar15,w_x  Integrated new MMU library to VxWorks 7 for PPC64 (F2518)
26feb15,w_x  Support LP64 configurable virtual address bits to decode (F2518)
20nov14,ylu  LP64 adaptation to support PPC64.(F2518)
25nov13,syt  made the definitions _MMU_TLB_SZ_MULT, _MMU_TLB_SZ_MULT_SHIFT
                 and _MMU_TLB_SZ_MIN_SHIFT valided for e6500. 
17jul13,x_z  added TLB size macros and mmuE500EarlyInit().
30jan13,pcs  cleanup for code review.
10sep12,pcs  Add support for e6500
11nov11,ers  Fix for vmPageLock/Unlock. (WIND00297094)
                 N_TLB_ENTRIES for e500mc.  (WIND00322280)
29jun09,pmr  e500mc 36-bit addressing
10jun09,pmr  e500mc static TLB num.
19apr07,dtr  Add support for e200 VLE.
19jul05,dtr  Implement 36bit rpn.
11nov04,dtr  Add user permission flags for static TLBs.
07oct04,mdo  Documentation fixes for apigen.
09apr04,dtr  Add in MMU_LOCK mask and bit field in Pte.
18mar04,dtr  Mods fixes after formal inspection.
09feb04,dtr  Fix protection bits.
30jan04,mil  Updated for Base6.
13jun03,mil  Added TLB sizes.
07jan03,dtr  Adding support for static TLB entries.
*/

/*
DESCRIPTION

This header contains the public interface to the PowerPC E500 Core Memory
Management Library. It also defines private (internal) structures and
macros used to manipulate the E500 MMU.

Theory: the vmBaseLib and vmLib provide an application programmer
interface to the memory management and protection features of the E500
MMU. With the help of the aimMmuLib and mmuE500Lib layers, a data
structure is maintained which stores per-page attributes: validity,
protection, cacheability, and address translation. This data structure
represents each page as a page table entry (PTE).

The E500 MMU has two levels.  In level 1, instruction and data are
split, while they are unified in level 2.  Level 1 is maintained by
the hardware and level 2 is maintained by the OS.  The number of entries
are as follows:

Name      Level   Type No of pg sizes Assoc     #entries     filled by
I-L1VSP     L1    Instr     9         Full         4         TLB1 hit
I-L1TLB4K   L1    Instr   1(4k)       4-way        64         TLB0 hit
D-L1VSP     L1    Data      9         Full         4         TLB1 hit
D-L1TLB4K   L1    Data    1(4k)       4-way        64         TLB0 hit
TLB1        L2    I/D       9         Full        16         s/w tlbwe
TLB0        L2    I/D     1(4k)       2-way       256         s/w tlbwe

The VSP (variable sized page) are used as static entries like the BATs,
while the 4k page are dynamic entries that gets loaded with the PTEs.
When a TLB miss occur in TLB0, an exception occurs and the OS walks the
data structure and copies a PTE into a TLB0 entry.  Hence, TLB1 is 
filled with mapping from the sysStaticTlbDesc[] array, and TLB0 is 
filled with mapping from the sysPhysMemDesc[] array.

Note that the E500 MMU cannot be turned off.  Translation occurs at
all time, which it uses also the IS and DS bits while deciding a hit.
Real mode is simulated with both IS and DS bits set to zero.

This file provides data needed to coordinate the mmuE500Lib layer with
the aimMmuLib and vmLib/vmBaseLib layers, as well as definitions needed
to configure the sysStaticTlbDesc[] array.
*/

#ifndef __INCmmuE500Libh
#define __INCmmuE500Libh

#include <vmLib.h>
#include <arch/ppc/ppc85xx.h>
#include <aimMmuLib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#if defined (PPC_e6500)
#undef E6500MMU_HW_TLB_WALK
#endif

#ifndef _WRS_CONFIG_LP64
#undef  _WRS_MMU_FOUR_LEVEL_PT
#else
#define  _WRS_MMU_FOUR_LEVEL_PT
#endif /* _WRS_CONFIG_LP64 */


#define MMU_PAGE_SIZE           0x1000  /* pages are 4K bytes */
#define	MMU_MIN_PAGE_SIZE_BITS	12		/* minimu page size in bits */
#define	MMU_PAGE_SIZE_BITS	    MMU_MIN_PAGE_SIZE_BITS
						/* default page size in bits */

/*
 * MMU_I_ADDR_TRANS and MMU_D_ADDR_TRANS are used in the mmuE500Lib /
 * mmuPpcALib & cacheALib call interface. They are not useful at the
 * application programming level.
 */

#define MMU_I_ADDR_TRANS        0
#define MMU_D_ADDR_TRANS        1

/*
 * MMU_INST and MMU_DATA are used at the usrMmuInit
 * interface.  They are not useful at the application programming
 * level.
 */

#define MMU_INST                0x01
#define MMU_DATA                0x02

/*
 * MMU_STATE attributes
 *
 */
/* offsets to the entries to the TLB1ESEL structure. */

#define TLB1ESEL_LOCK_OFFSET	0
#define TLB1ESEL_NEXT_OFFSET	1
#define TLB1ESEL_START_OFFSET	2
#define TLB1ESEL_MAX_OFFSET	3

#if defined (PPC_e6500) && !defined (_WRS_CONFIG_UNIFIED_MMU_LIB)

/* V, WIMGE bits */
#define MMU_STATE_VALID                         0x00000001
#define MMU_STATE_VALID_NOT                     0x00000000
#define MMU_STATE_LOCK                          0x00002000
#define MMU_STATE_UNLOCK                        0x00000000
#define MMU_STATE_CACHEABLE_WRITETHROUGH        0x00800000
#define MMU_STATE_CACHEABLE_COPYBACK            0x00000000
#define MMU_STATE_CACHEABLE                     0x00000000
#define MMU_STATE_CACHEABLE_NOT                 0x00400000
#define MMU_STATE_MEM_COHERENCY                 0x00200000
#define MMU_STATE_MEM_COHERENCY_NOT             0x00000000
#define MMU_STATE_GUARDED                       0x00100000
#define MMU_STATE_GUARDED_NOT                   0x00000000
#define MMU_STATE_ENDIAN_BIG                    0x00000000
#define MMU_STATE_ENDIAN_LITTLE                 0x00080000

#define MMU_STATE_MASK_VALID                    0x00000001
#define MMU_STATE_MASK_LOCK                     0x00002000
#define MMU_STATE_MASK_WIMG                     0x00F80000
#define MMU_STATE_MASK_WRITETHROUGH             0x00800000
#define MMU_STATE_MASK_CACHEABLE                0x00C00000
#define MMU_STATE_MASK_MEM_COHERENCY            0x00200000
#define MMU_STATE_MASK_GUARDED                  0x00100000
#define MMU_STATE_MASK_ENDIAN                   0x00080000

/* UX/SX, UW/SW, UR/SR bits */

#define MMU_STATE_EXECUTE                       0x000000C0
#define MMU_STATE_EXECUTE_NOT                   0x00000000
#define MMU_STATE_WRITABLE                      0x00000030
#define MMU_STATE_WRITABLE_NOT                  0x00000000
#define MMU_STATE_MASK_EXECUTE                  0x000000C0
#define MMU_STATE_MASK_WRITABLE                 0x00000030
#define MMU_STATE_MASK_WRITABLE_EXECUTE         0x000000F0
#define MMU_STATE_MASK_WIMG_WRITABLE_EXECUTE    0x00000000 
#define MMU_STATE_MASK_PROTECTION               0x000000FC
#define MMU_STATE_PROTECTION_BIT_SHIFT          0

#else

/* V, WIMGE bits */
#define MMU_STATE_VALID                         0x80000000
#define MMU_STATE_VALID_NOT                     0x00000000
#define MMU_STATE_LOCK                          0x00800000
#define MMU_STATE_UNLOCK                        0x00000000
#define MMU_STATE_CACHEABLE_WRITETHROUGH        0x00000010
#define MMU_STATE_CACHEABLE_COPYBACK            0x00000000
#define MMU_STATE_CACHEABLE                     0x00000000
#define MMU_STATE_CACHEABLE_NOT                 0x00000008
#define MMU_STATE_MEM_COHERENCY                 0x00000004
#define MMU_STATE_MEM_COHERENCY_NOT             0x00000000
#define MMU_STATE_GUARDED                       0x00000002
#define MMU_STATE_GUARDED_NOT                   0x00000000
#define MMU_STATE_ENDIAN_BIG                    0x00000000
#define MMU_STATE_ENDIAN_LITTLE                 0x00000001

#define MMU_STATE_MASK_VALID                    0x80000000
#define MMU_STATE_MASK_LOCK                     0x00800000
#define MMU_STATE_MASK_WIMG                     0x0000001E
#define MMU_STATE_MASK_WRITETHROUGH             0x00000010
#define MMU_STATE_MASK_CACHEABLE                0x00000018
#define MMU_STATE_MASK_MEM_COHERENCY            0x00000004
#define MMU_STATE_MASK_GUARDED                  0x00000002
#define MMU_STATE_MASK_ENDIAN                   0x00000001

/* UX/SX, UW/SW, UR/SR bits */

  /* drice - need to look at these values */
#define MMU_STATE_EXECUTE                       0x00003000
#define MMU_STATE_EXECUTE_NOT                   0x00000000
#define MMU_STATE_WRITABLE                      0x00000c00
#define MMU_STATE_WRITABLE_NOT                  0x00000000
#define MMU_STATE_MASK_EXECUTE                  0x00003000
#define MMU_STATE_MASK_WRITABLE                 0x00000c00
#define MMU_STATE_MASK_WRITABLE_EXECUTE         0x00003c00
#define MMU_STATE_MASK_WIMG_WRITABLE_EXECUTE    0x00000000 
#define MMU_STATE_MASK_PROTECTION               0x00003f00
#define MMU_STATE_PROTECTION_BIT_SHIFT          8

#endif /* PPC_e6500 && _WRS_CONFIG_UNIFIED_MMU_LIB */

#ifdef _WRS_CONFIG_UNIFIED_MMU_LIB
/* defines */

#ifdef	_WRS_CONFIG_LP64
#   define VIRT_ADDR_BITS_MAX	        64
#else
#   define VIRT_ADDR_BITS_MAX	        32
#endif	/* _WRS_CONFIG_LP64 */

#ifdef _WRS_MMU_FOUR_LEVEL_PT

/* MMU levels index shift */

#define MMU_L1_INDEX_SHIFT              (MMU_L2_INDEX_SHIFT + MMU_L2_MAP_WIDTH)
#define MMU_L2_INDEX_SHIFT              (MMU_L3_INDEX_SHIFT + MMU_L3_MAP_WIDTH)
#define MMU_L3_INDEX_SHIFT              (MMU_L4_INDEX_SHIFT + MMU_L4_MAP_WIDTH)
#define MMU_L4_INDEX_SHIFT              MMU_PAGE_SIZE_BITS

/* The four MMU levels' map width */

#ifndef _WRS_CONFIG_LP64
#   define MMU_NO_USED_ADRS_BITS        0
#   define MMU_PHYS_ADRS_WIDTH          32

#   define MMU_L1_MAP_WIDTH             8           /* 8 bits width, 4G    */
#   define MMU_L2_MAP_WIDTH             4           /* 4 bits width, 16M   */
#   define MMU_L3_MAP_WIDTH             4           /* 4 bits width, 1M    */
#   define MMU_L4_MAP_WIDTH             4           /* 4 bits width, 64K   */

/* MMU levels index mask */

#   define MMU_L1_INDEX_MASK            0xff000000 
#   define MMU_L2_INDEX_MASK            0x00f00000
#   define MMU_L3_INDEX_MASK            0x000f0000
#   define MMU_L4_INDEX_MASK            0x0000f000

#   define MMU_L2_INDEX_OFFSET          4       /* 16 bytes offset */
#else   /* _WRS_CONFIG_LP64 */
#   define MMU_NO_USED_ADRS_BITS        16
#   define MMU_PHYS_ADRS_WIDTH          (VIRT_ADDR_BITS_MAX-MMU_NO_USED_ADRS_BITS)

#   define MMU_L1_MAP_WIDTH             12          /* 12 bits width, 256T */
#   define MMU_L2_MAP_WIDTH             10          /* 10 bits width, 64G  */
#   define MMU_L3_MAP_WIDTH             6           /* 6 bits width, 64M   */
#   define MMU_L4_MAP_WIDTH             8           /* 8 bits width, 1M    */

/* MMU levels index mask */

#   define MMU_L1_INDEX_MASK            0x0000fff000000000LL
#   define MMU_L2_INDEX_MASK            0x0000000ffc000000LL
#   define MMU_L3_INDEX_MASK            0x0000000003f00000LL
#   define MMU_L4_INDEX_MASK            0x00000000000ff000LL

#   define MMU_L2_INDEX_OFFSET          4       /* 16 bytes offset */
#endif  /* _WRS_CONFIG_LP64 */

#define MMU_L1_INDEX_OFFSET             _SIZE_OF_LONG_BITS

#define MMU_L1_INDEX_SHIFT_OFFSET       (MMU_NO_USED_ADRS_BITS+MMU_L1_MAP_WIDTH)
#define MMU_L1_INDEX_SHIFT_OFFSET_E     (MMU_L1_INDEX_SHIFT_OFFSET+MMU_L1_INDEX_OFFSET-32)
#define MMU_L1_INDEX_OFFSET_MASK_B      (VIRT_ADDR_BITS_MAX-MMU_L1_MAP_WIDTH)
#define MMU_L1_INDEX_OFFSET_MASK_BE     (32-MMU_L1_MAP_WIDTH-MMU_L1_INDEX_OFFSET)
#define MMU_L1_INDEX_OFFSET_MASK_E      (32-MMU_L1_INDEX_OFFSET-1)

#define MMU_L2_INDEX_SHIFT_OFFSET       (MMU_L1_INDEX_SHIFT_OFFSET+MMU_L2_MAP_WIDTH)
#define MMU_L2_INDEX_SHIFT_OFFSET_E     (MMU_L2_INDEX_SHIFT_OFFSET+MMU_L2_INDEX_OFFSET-32)
#define MMU_L2_INDEX_OFFSET_MASK_B      (VIRT_ADDR_BITS_MAX-MMU_L2_MAP_WIDTH)
#define MMU_L2_INDEX_OFFSET_MASK_BE     (32-MMU_L2_MAP_WIDTH-MMU_L2_INDEX_OFFSET)
#define MMU_L2_INDEX_OFFSET_MASK_E      (32-MMU_L2_INDEX_OFFSET-1)

#define MMU_L3_INDEX_OFFSET             MMU_L2_INDEX_OFFSET /* 16 bytes */
#define MMU_L3_INDEX_SHIFT_OFFSET       (MMU_L2_INDEX_SHIFT_OFFSET+MMU_L3_MAP_WIDTH)
#define MMU_L3_INDEX_SHIFT_OFFSET_E     (MMU_L3_INDEX_SHIFT_OFFSET+MMU_L3_INDEX_OFFSET-32)
#define MMU_L3_INDEX_OFFSET_MASK_B      (VIRT_ADDR_BITS_MAX-MMU_L3_MAP_WIDTH)
#define MMU_L3_INDEX_OFFSET_MASK_BE     (32-MMU_L3_MAP_WIDTH-MMU_L3_INDEX_OFFSET)
#define MMU_L3_INDEX_OFFSET_MASK_E      (32-MMU_L3_INDEX_OFFSET-1)

#define MMU_L4_INDEX_OFFSET             MMU_L2_INDEX_OFFSET /* 16 bytes */
#define MMU_L4_INDEX_SHIFT_OFFSET       (MMU_L3_INDEX_SHIFT_OFFSET+MMU_L4_MAP_WIDTH)
#define MMU_L4_INDEX_SHIFT_OFFSET_E     (MMU_L4_INDEX_SHIFT_OFFSET+MMU_L4_INDEX_OFFSET-32)
#define MMU_L4_INDEX_OFFSET_MASK_B      (VIRT_ADDR_BITS_MAX-MMU_L4_MAP_WIDTH)
#define MMU_L4_INDEX_OFFSET_MASK_BE     (32-MMU_L4_MAP_WIDTH-MMU_L4_INDEX_OFFSET)
#define MMU_L4_INDEX_OFFSET_MASK_E      (32-MMU_L4_INDEX_OFFSET-1)

/* MMU Levels' MAP size */

#ifndef _WRS_CONFIG_LP64
#   define MMU_L1_MAP_SIZE              (0x1<<(MMU_PHYS_ADRS_WIDTH-MMU_L1_MAP_WIDTH))
#   define MMU_L2_MAP_SIZE              (0x1<<(MMU_PHYS_ADRS_WIDTH-MMU_L1_MAP_WIDTH-MMU_L2_MAP_WIDTH))
#   define MMU_L3_MAP_SIZE              (0x1<<(MMU_PHYS_ADRS_WIDTH-MMU_L1_MAP_WIDTH-MMU_L2_MAP_WIDTH-MMU_L3_MAP_WIDTH))
#else
#   define MMU_L1_MAP_SIZE              (0x1LL<<(MMU_PHYS_ADRS_WIDTH-MMU_L1_MAP_WIDTH))
#   define MMU_L2_MAP_SIZE              (0x1LL<<(MMU_PHYS_ADRS_WIDTH-MMU_L1_MAP_WIDTH-MMU_L2_MAP_WIDTH))
#   define MMU_L3_MAP_SIZE              (0x1LL<<(MMU_PHYS_ADRS_WIDTH-MMU_L1_MAP_WIDTH-MMU_L2_MAP_WIDTH-MMU_L3_MAP_WIDTH))
#endif /* _WRS_CONFIG_LP64 */

#define MMU_L4_MAP_SIZE                 MMU_PAGE_SIZE     /* 4K */

/* MMU level 1 MAP defines */

#undef  _WRS_MMU_SUPPORTS_L1_MAP

#define MMU_L1_MAP_ALIGN                MMU_L1_MAP_SIZE
#define MMU_L1_ENTRY_COUNT              (0x01<<MMU_L1_MAP_WIDTH)
#define MMU_L1_INIT_ENTRY               0x00000000
#define MMU_L1_TBL_SIZE                 (MMU_L1_ENTRY_COUNT*sizeof(MMU_L1_ENTRY))
#define MMU_L1_TBL_ALIGN                MMU_L1_TBL_SIZE

/* MMU Level 2 MAP defines */

#define _WRS_MMU_SUPPORTS_L2_MAP
#undef  _WRS_MMU_L2_ALIASES_L1

#define MMU_L2_MAP_ALIGN                MMU_L2_MAP_SIZE
#define MMU_L2_ENTRY_COUNT              (0x01<<MMU_L2_MAP_WIDTH)
#define MMU_L2_TBL_SIZE                 (MMU_L2_ENTRY_COUNT*sizeof(MMU_L3_ENTRY))
#define MMU_L2_TBL_ALIGN                MMU_L2_TBL_SIZE

#define MMU_L2_ENTRY_INIT_W0            0x00001000        /* TS=1 */
#define MMU_L2_ENTRY_INIT_W1            MMU_STATE_CACHEABLE_NOT    /* cache disabled */
#define MMU_L2_ENTRY_INIT_W2            0xFFFFF000        /* no access */
#define MMU_L2_ENTRY_INIT_W3            0x00000000
#define MMU_L2_TYPE_MASK_W0             0x0000003F
#define MMU_L2_TYPE_L3_TBL              0x00000029

#ifndef _WRS_CONFIG_LP64
#   define MMU_L2_TLB_SIZE_W0           0x00000300        /* 1M */
#else
#   define MMU_L2_TLB_SIZE_W0           0x00000800        /* 64M */
#endif /* _WRS_CONFIG_LP64 */

/* MMU Level 3 MAP defines */

#define _WRS_MMU_SUPPORTS_L3_MAP
#undef  _WRS_MMU_L3_ALIASES_L2

#define MMU_L3_MAP_ALIGN                MMU_L3_MAP_SIZE
#define MMU_L3_ENTRY_COUNT              (0x01<<MMU_L3_MAP_WIDTH)
#define MMU_L3_TBL_SIZE                 (MMU_L3_ENTRY_COUNT*sizeof(MMU_L3_ENTRY))
#define MMU_L3_TBL_ALIGN                MMU_L3_TBL_SIZE

#define MMU_L3_ENTRY_INIT_W0            0x00001000        /* TS=1 */
#define MMU_L3_ENTRY_INIT_W1            MMU_STATE_CACHEABLE_NOT    /* cache disabled */
#define MMU_L3_ENTRY_INIT_W2            0xFFFFF000        /* no access */
#define MMU_L3_ENTRY_INIT_W3            0x00000000
#define MMU_L3_TYPE_MASK_W0             0x0000003F
#define MMU_L3_TYPE_L4_TBL              0x00000029

#ifndef _WRS_CONFIG_LP64
#   define MMU_L3_TLB_SIZE_W0           0x00000300        /* 64K */
#else
#   define MMU_L3_TLB_SIZE_W0           0x00000500        /* 1M */
#endif /* _WRS_CONFIG_LP64 */

/* MMU Level 4 MAP defines */

#define _WRS_MMU_SUPPORTS_L4_MAP
#undef  _WRS_MMU_L4_ALIASES_L3

#define MMU_L4_MAP_ALIGN                MMU_L4_MAP_SIZE
#define MMU_L4_ENTRY_COUNT              (0x01<<MMU_L4_MAP_WIDTH)
#define MMU_L4_TBL_SIZE                 (MMU_L4_ENTRY_COUNT*sizeof(MMU_L4_ENTRY))
#define MMU_L4_TBL_ALIGN                MMU_L4_TBL_SIZE
#define MMU_L4_ENTRY_INIT_W0            0x00001000        /* TS=1 */
#define MMU_L4_ENTRY_INIT_W1            MMU_STATE_CACHEABLE_NOT    /* cache disabled */
#define MMU_L4_ENTRY_INIT_W2            0xFFFFF000        /* no access */
#define MMU_L4_ENTRY_INIT_W3            0x00000000

#else /* _WRS_MMU_FOUR_LEVEL_PT */

/* The two level MMU PTE table only supported on ILP32 model */

#define MMU_PHYS_ADRS_WIDTH             32 

#define MMU_L1_MAP_WIDTH                10           /* 4G */
#define MMU_L1_INDEX_SHIFT              (MMU_L2_INDEX_SHIFT + MMU_L2_MAP_WIDTH)
#define MMU_L1_INDEX_MASK               0xffc00000
#define MMU_L1_ENTRY_COUNT              (0x01<<MMU_L1_MAP_WIDTH)      /* 1024 */
#define MMU_L1_INDEX_SHIFT_OFFSET_E     (MMU_L1_MAP_WIDTH+2)
#define MMU_L1_INDEX_OFFSET_MASK_BE     (VIRT_ADDR_BITS_MAX-MMU_L1_MAP_WIDTH-2)
#define MMU_L1_INDEX_OFFSET_MASK_E      (VIRT_ADDR_BITS_MAX-3)

#undef _WRS_MMU_SUPPORTS_L1_MAP
#define MMU_L1_MAP_SIZE                 (MMU_PAGE_SIZE*MMU_L1_ENTRY_COUNT) /* 0x100000 */
#define MMU_L1_MAP_ALIGN                MMU_L1_MAP_SIZE
#define MMU_L1_INIT_ENTRY               0x00000000
#define MMU_L1_TBL_SIZE                 (MMU_L1_ENTRY_COUNT*sizeof (MMU_L1_ENTRY))
#define MMU_L1_TBL_ALIGN                MMU_L1_TBL_SIZE

#define MMU_L2_MAP_WIDTH                10           /* 4M */
#define MMU_L2_INDEX_SHIFT              MMU_PAGE_SIZE_BITS
#define MMU_L2_INDEX_MASK               0x003ff000
#define MMU_L2_ENTRY_COUNT              (0x01<<MMU_L2_MAP_WIDTH)      /* 1024 */
#define MMU_L2_INDEX_SHIFT_OFFSET_E     (MMU_L1_MAP_WIDTH+MMU_L2_MAP_WIDTH+4)
#define MMU_L2_INDEX_OFFSET_MASK_BE     (VIRT_ADDR_BITS_MAX-MMU_L2_MAP_WIDTH-4)
#define MMU_L2_INDEX_OFFSET_MASK_E      (VIRT_ADDR_BITS_MAX-5)

#define _WRS_MMU_SUPPORTS_L2_MAP
#undef  _WRS_MMU_L2_ALIASES_L1

#define MMU_L2_MAP_SIZE                 MMU_PAGE_SIZE        /* 0x1000 */
#define MMU_L2_MAP_ALIGN                MMU_L2_MAP_SIZE

#define MMU_L2_TBL_SIZE                 (MMU_L2_ENTRY_COUNT*sizeof(MMU_L2_ENTRY))
#define MMU_L2_TBL_ALIGN                MMU_L2_TBL_SIZE
#define MMU_L2_ENTRY_INIT_W0            0x00001000        /* TS=1 */
#define MMU_L2_ENTRY_INIT_W1            MMU_STATE_CACHEABLE_NOT    /* cache disabled */
#define MMU_L2_ENTRY_INIT_W2            0xFFFFF000        /* no access */
#define MMU_L2_ENTRY_INIT_W3            0x00000000

#endif /* _WRS_MMU_FOUR_LEVEL_PT */

#define TLB1_ENTRY_START                6

#endif /* _WRS_CONFIG_UNIFIED_MMU_LIB */

/* entire max number bits among page and region table indexes */

#define MMU_TABLE_INDEX_BITS_MAX	\
	(VIRT_ADDR_BITS_DEC - MMU_PAGE_SIZE_BITS)

/* average of the max number bits among page and region table indexes */

#define MMU_TABLE_INDEX_BITS_MAX_AVE	\
    (MMU_TABLE_INDEX_BITS_MAX / (AIM_MMU_REGION_LEVEL + 1))

/* reminder of the max number bits among page and region table indexes */

#define MMU_TABLE_INDEX_BITS_MAX_REM	\
    (MMU_TABLE_INDEX_BITS_MAX % (AIM_MMU_REGION_LEVEL + 1))

/*
 * The next most significant MMU_PAGE_INDEX_BITS bits of the virtual
 * address are used as an index into the Page Table.
 *
 * The next most significant bits of the virtual address are used as an
 * index into the Page Table.  Note that MMU_PAGE_INDEX_BITS_MAX
 * describes the maximum number of bits to be used as a index to look up
 * an entry in the page table. 
 *
 * Each entry is of size 2 ^ MMU_PAGE_ENTRY_BITS, which is the size of
 * an MMUE500_PTE.
 */

#if	(MMU_TABLE_INDEX_BITS_MAX_REM == AIM_MMU_REGION_LEVEL)
#define MMU_PAGE_INDEX_BITS_MAX	MMU_TABLE_INDEX_BITS_MAX_AVE
#else
/* add the reminder to the page table index bits max */

#define MMU_PAGE_INDEX_BITS_MAX	\
	(MMU_TABLE_INDEX_BITS_MAX_AVE + MMU_TABLE_INDEX_BITS_MAX_REM)
#endif	/* MMU_TABLE_INDEX_BITS_MAX_REM == AIM_MMU_REGION_LEVEL */
					/* number of bits in index */
#define MMU_PAGE_TBL_ENTRIES_MAX (0x1 << MMU_PAGE_INDEX_BITS_MAX)
                                        /* max number of page table entries */
#if defined(PPC_e6500)
#define MMU_PAGE_ENTRY_BITS     3    /* MMUE500_PTE size in bytes as pwr of 2 */
#else
# ifdef	_WRS_CONFIG_LP64
#  define MMU_PAGE_ENTRY_BITS	5    /* MMUE500_PTE size in bytes as pwr of 2 */
# else
#  define MMU_PAGE_ENTRY_BITS   4    /* MMUE500_PTE size in bytes as pwr of 2 */
# endif  /* _WRS_CONFIG_LP64 */
#endif

/*
 * Each context's MMU pages are mapped using a max region level depth +1 level
 * page table scheme.  The level 1 through the max region level depth are
 * called the REGION table and the last level table is called a PAGE table.
 *
 * The most significant MMU_REGION_INDEX_BITS bits of the virtual
 * address are used as an index into the Region Table. Each entry is of
 * size 2 ^ MMU_REGION_ENTRY_BITS, a pointer to the next level REGION table or
 * a PAGE table.
 */

#if (MMU_TABLE_INDEX_BITS_MAX_REM == AIM_MMU_REGION_LEVEL)
/* add the reminder to each region table index bits max */

#define MMU_REGION_INDEX_BITS	(MMU_TABLE_INDEX_BITS_MAX_AVE + 1)
#else
#define MMU_REGION_INDEX_BITS	MMU_TABLE_INDEX_BITS_MAX_AVE
#endif	/* MMU_TABLE_INDEX_BITS_MAX_REM == AIM_MMU_REGION_LEVEL */
					/* number of bits in index */
#define MMU_REGION_TBL_ENTRIES	(0x1 << MMU_REGION_INDEX_BITS)
					/* number of regions in table */
#ifdef	_WRS_CONFIG_LP64
#define MMU_REGION_ENTRY_BITS	3	/* size in bytes as pwr of 3 */
#else
#define MMU_REGION_ENTRY_BITS	2	/* size in bytes as pwr of 2 */
#endif	/* _WRS_CONFIG_LP64 */

#define MMU_CONTEXT_TBL_SHIFT	MMU_REGION_ENTRY_BITS
					/* size in bytes as pwr of */

#if defined (PPC_e6500)
#define MMUE500_NO_BITS_PHYS_ADDR       40
#define MMUE500_PHYS_ADDR_EXT_MASK      0xff
#elif defined(PPC_e500v2) || defined(PPC_e500mc)
#define MMUE500_NO_BITS_PHYS_ADDR       36
#define MMUE500_PHYS_ADDR_EXT_MASK      0x0f
#endif

/*
 * If _WRS_CONFIG_COMPAT69_ADR_SPACE is not defined, MMU is enabled
 * in non-MMU exceptions, and SPRG4-7 must be used to save the context, 
 * so here SPRG4-7 couldn't be used; 
 * in other words, USE_SPRG7 could't be used.
 */

#undef  USE_SPRG4_7

/*
 * Protection Bits
 *
 * Each TLB entry controls access to one page of memory. The protection
 * mode is controlled by 6 bits in the TLB word, one for each of Read,
 * Write, Execute for Supervisor and User.
 *
 * These protection bits are mapped directly into MMU_STATE_* macros,
 * defined below:
 */

/* MMU_STATE_* protection mode sub-fields, mapping <<8 with hardware */

#if defined (PPC_e6500) && !defined (_WRS_CONFIG_UNIFIED_MMU_LIB)

#define _MMU_UX                 0x00000080
#define _MMU_SX                 0x00000040
#define _MMU_UW                 0x00000020
#define _MMU_SW                 0x00000010
#define _MMU_UR                 0x00000008
#define _MMU_SR                 0x00000004

#else

#define _MMU_UX                 0x00002000
#define _MMU_SX                 0x00001000
#define _MMU_UW                 0x00000800
#define _MMU_SW                 0x00000400
#define _MMU_UR                 0x00000200
#define _MMU_SR                 0x00000100

#endif

#define _MMU_URWX                  (_MMU_UR | _MMU_UW | _MMU_UX)

/* MMU_STATE_* protection modes macros */

#define MMU_STATE_SUP_R            (_MMU_SR)
#define MMU_STATE_SUP_RW           (_MMU_SR|_MMU_SW)
#define MMU_STATE_SUP_RX           (_MMU_SR|        _MMU_SX)
#define MMU_STATE_SUP_RWX          (_MMU_SR|_MMU_SW|_MMU_SX)

#define MMU_STATE_SUP_R_USR_R      (MMU_STATE_SUP_R   | _MMU_UR)
#define MMU_STATE_SUP_RW_USR_R     (MMU_STATE_SUP_RW  | _MMU_UR)
#define MMU_STATE_SUP_RX_USR_R     (MMU_STATE_SUP_RX  | _MMU_UR)
#define MMU_STATE_SUP_RWX_USR_R    (MMU_STATE_SUP_RWX | _MMU_UR)

#define MMU_STATE_SUP_R_USR_W      (MMU_STATE_SUP_R   | _MMU_UW)
#define MMU_STATE_SUP_RW_USR_W     (MMU_STATE_SUP_RW  | _MMU_UW)
#define MMU_STATE_SUP_RX_USR_W     (MMU_STATE_SUP_RX  | _MMU_UW)
#define MMU_STATE_SUP_RWX_USR_W    (MMU_STATE_SUP_RWX | _MMU_UW)

#define MMU_STATE_SUP_R_USR_RW     (MMU_STATE_SUP_R   | _MMU_UR | _MMU_UW)
#define MMU_STATE_SUP_RW_USR_RW    (MMU_STATE_SUP_RW  | _MMU_UR | _MMU_UW)
#define MMU_STATE_SUP_RX_USR_RW    (MMU_STATE_SUP_RX  | _MMU_UR | _MMU_UW)
#define MMU_STATE_SUP_RWX_USR_RW   (MMU_STATE_SUP_RWX | _MMU_UR | _MMU_UW)

#define MMU_STATE_SUP_R_USR_X      (MMU_STATE_SUP_R   | _MMU_UX)
#define MMU_STATE_SUP_RW_USR_X     (MMU_STATE_SUP_RW  | _MMU_UX)
#define MMU_STATE_SUP_RX_USR_X     (MMU_STATE_SUP_RX  | _MMU_UX)
#define MMU_STATE_SUP_RWX_USR_X    (MMU_STATE_SUP_RWX | _MMU_UX)

#define MMU_STATE_SUP_R_USR_RX     (MMU_STATE_SUP_R   | _MMU_UR | _MMU_UX)
#define MMU_STATE_SUP_RW_USR_RX    (MMU_STATE_SUP_RW  | _MMU_UR | _MMU_UX)
#define MMU_STATE_SUP_RX_USR_RX    (MMU_STATE_SUP_RX  | _MMU_UR | _MMU_UX)
#define MMU_STATE_SUP_RWX_USR_RX   (MMU_STATE_SUP_RWX | _MMU_UR | _MMU_UX)

#define MMU_STATE_SUP_R_USR_WX     (MMU_STATE_SUP_R   | _MMU_UW | _MMU_UX)
#define MMU_STATE_SUP_RW_USR_WX    (MMU_STATE_SUP_RW  | _MMU_UW | _MMU_UX)
#define MMU_STATE_SUP_RX_USR_WX    (MMU_STATE_SUP_RX  | _MMU_UW | _MMU_UX)
#define MMU_STATE_SUP_RWX_USR_WX   (MMU_STATE_SUP_RWX | _MMU_UW | _MMU_UX)

#define MMU_STATE_SUP_R_USR_RWX    (MMU_STATE_SUP_R   | _MMU_URWX)
#define MMU_STATE_SUP_RW_USR_RWX   (MMU_STATE_SUP_RW  | _MMU_URWX)
#define MMU_STATE_SUP_RX_USR_RWX   (MMU_STATE_SUP_RX  | _MMU_URWX)
#define MMU_STATE_SUP_RWX_USR_RWX  (MMU_STATE_SUP_RWX | _MMU_URWX)

/* RPN field offset in TLB Word 0 (left shift this number of bits) */

#define MMU_RPN_SHIFT                           12

/* EPN field bits number in TLB Word 1 */

#define MMU_EPN_BITS		(VIRT_ADDR_BITS_MAX - MMU_RPN_SHIFT)


/* TLB_ENTRY_DESC page attributes */


#if defined(PPC_e6500) 

#if !defined (_WRS_CONFIG_UNIFIED_MMU_LIB)
#define _MMU_TLB_TS_0           0x00000000      /* Translation Space 0 */
#define _MMU_TLB_TS_1           0x00002000      /* Translation Space 1 */
#else
#define _MMU_TLB_TS_0           0x00000000      /* Translation Space 0 */
#define _MMU_TLB_TS_1           0x00001000      /* Translation Space 1 */
#endif

#define TLB_GLOBAL_BIT  30      /* global page map bit is at bit 30 of word 1 */
#define TLB_LOCK_BIT    18      /* lock page map bit is at bit 18 of word 1 */

#define _MMU_TLB_SZ_4K          0x00000100      /* 4KB page size */
#define _MMU_TLB_SZ_8K          0x00000180      /* 8KB page size */
#define _MMU_TLB_SZ_16K         0x00000200      /* 16KB page size */
#define _MMU_TLB_SZ_32K         0x00000280      /* 32KB page size */
#define _MMU_TLB_SZ_64K         0x00000300      /* 64KB page size */
#define _MMU_TLB_SZ_128K        0x00000380      /* 128KB page size */
#define _MMU_TLB_SZ_256K        0x00000400      /* 256KB page size */
#define _MMU_TLB_SZ_512K        0x00000480      /* 512KB page size */
#define _MMU_TLB_SZ_1M          0x00000500      /* 1MB page size */
#define _MMU_TLB_SZ_2M          0x00000580      /* 2MB page size */
#define _MMU_TLB_SZ_4M          0x00000600      /* 4MB page size */
#define _MMU_TLB_SZ_8M          0x00000680      /* 8MB page size */
#define _MMU_TLB_SZ_16M         0x00000700      /* 16MB page size */
#define _MMU_TLB_SZ_32M         0x00000780      /* 32MB page size */
#define _MMU_TLB_SZ_64M         0x00000800      /* 64MB page size */
#define _MMU_TLB_SZ_128M        0x00000880      /* 128MB page size */
#define _MMU_TLB_SZ_256M        0x00000900      /* 256MB page size */
#define _MMU_TLB_SZ_512M        0x00000980      /* 512MB page size */
#define _MMU_TLB_SZ_1G          0x00000a00      /* 1GB page size */
#define _MMU_TLB_SZ_2G          0x00000a80      /* 2GB page size */
#define _MMU_TLB_SZ_4G          0x00000b00      /* 4GB page size */
#define _MMU_TLB_SZ_8G          0x00000b80      /* 8GB page size */
#define _MMU_TLB_SZ_16G         0x00000c00      /* 16GB page size */
#define _MMU_TLB_SZ_32G         0x00000c80      /* 32GB page size */
#define _MMU_TLB_SZ_64G         0x00000d00      /* 64GB page size */
#define _MMU_TLB_SZ_128G        0x00000d80      /* 128GB page size */
#define _MMU_TLB_SZ_256G        0x00000e00      /* 256GB page size */
#define _MMU_TLB_SZ_512G        0x00000e80      /* 512GB page size */
#define _MMU_TLB_SZ_1TB         0x00000f00      /* 1TB page size */
#define _MMU_TLB_SZ_MASK        0x00000f80      /* mask for page size field */
#define _MMU_TLB_SZ_SHIFT       7               /* offset of page size field */
#define _MMU_TLB_VALID          0x80000000      /* TLB is valid bit */
#define _MMU_TLB_IPROT          0x40000000      /* invalidate protection */

#define _MMU_TLB_ATTR_W         0x00000010      /* writethrough */
#define _MMU_TLB_ATTR_I         0x00000008      /* inhibit caching */
#define _MMU_TLB_ATTR_M         0x00000004      /* memory coherency */
#define _MMU_TLB_ATTR_G         0x00000002      /* guarded */
#define _MMU_TLB_ATTR_E         0x00000001      /* endianess */


#define _MMU_TLB_PERM_X         0x00000020      /* executable */
#define _MMU_TLB_PERM_W         0x00000040      /* writable */
#define _MMU_TLB_PERM_UR        0x00010000      /* user read */
#define _MMU_TLB_PERM_UW        0x00020000      /* user write */
#define _MMU_TLB_PERM_UX        0x00040000      /* user execute */

#define _MMU_TLB_EXRPN_MASK     0x000000ff      /* extend real page number mask */

#else

#define _MMU_TLB_TS_0           0x00000000      /* Translation Space 0 */
#define _MMU_TLB_TS_1           0x00001000      /* Translation Space 1 */

#define TLB_GLOBAL_BIT  25      /* global page map bit is at bit 0 of word 2 */
#define TLB_LOCK_BIT    26      /* lock page map bit is at bit 1 of word 2 */

#define _MMU_TLB_SZ_4K          0x00000100      /* 4KB page size */
#define _MMU_TLB_SZ_16K         0x00000200      /* 16KB page size */
#define _MMU_TLB_SZ_64K         0x00000300      /* 64KB page size */
#define _MMU_TLB_SZ_256K        0x00000400      /* 256KB page size */
#define _MMU_TLB_SZ_1M          0x00000500      /* 1MB page size */
#define _MMU_TLB_SZ_4M          0x00000600      /* 4MB page size */
#define _MMU_TLB_SZ_16M         0x00000700      /* 16MB page size */
#define _MMU_TLB_SZ_64M         0x00000800      /* 64MB page size */
#define _MMU_TLB_SZ_256M        0x00000900      /* 256MB page size */
#define _MMU_TLB_SZ_1G          0x00000a00      /* 1GB page size (e500v2/mc) */
#define _MMU_TLB_SZ_4G          0x00000b00      /* 4GB page size (e500v2/mc) */
#define _MMU_TLB_SZ_MASK        0x00000f00      /* mask for page size field */
#define _MMU_TLB_SZ_SHIFT       8               /* offset of page size field */

#ifdef PPC_e200
#define _MMU_TLB_ATTR_VLE       0x00080000      /* variable length encoding */
#endif

#define _MMU_TLB_ATTR_W         0x00000010      /* writethrough */
#define _MMU_TLB_ATTR_I         0x00000008      /* inhibit caching */
#define _MMU_TLB_ATTR_M         0x00000004      /* memory coherency */
#define _MMU_TLB_ATTR_G         0x00000002      /* guarded */
#define _MMU_TLB_ATTR_E         0x00000001      /* endianess */

#define _MMU_TLB_PERM_X         0x00000020      /* executable */
#define _MMU_TLB_PERM_W         0x00000040      /* writable */
#define _MMU_TLB_IPROT          0x00000080      /* invalidate protection */
#define _MMU_TLB_PERM_UR        0x00010000      /* user read */
#define _MMU_TLB_PERM_UW        0x00020000      /* user write */
#define _MMU_TLB_PERM_UX        0x00040000      /* user execute */

#define _MMU_TLB_EXRPN_MASK     0x0000000f      /* extend real page number mask */

#ifdef PPC_e200
#define _MMU_TLB_ATTR_VLE       0x00080000      /* variable length encoding */
#endif
#endif /* PPC_e6500 */

/* used to encode/decode size field of TLB/Page entry */

/* multiple for TLB size */

#define _MMU_TLB_SZ_MULT        4
#define _MMU_TLB_SZ_MULT_SHIFT  2

/* TLB size */

#define _MMU_TLB_SZ_MIN_SHIFT   12

#ifdef PPC_e500mc
#define N_TLB_ENTRIES_BITS      9               /* # TLB0: read TLB0CFG */
#define N_TLB_ENTRIES           512             /* # TLB0: read TLB0CFG */
#define MMUE500_NUM_STATIC_TLB_ENTIRES 0x40
#elif defined PPC_e6500
#define N_TLB_ENTRIES_BITS      10              /* # TLB0: read TLB0CFG */
#define N_TLB_ENTRIES           1024            /* # TLB0: read TLB0CFG */
#define N_TLB1_ENTRIES          64              /* # TLB1: read TLB1CFG */
#define MMUE500_NUM_STATIC_TLB_ENTIRES 0x40
#else
#define N_TLB_ENTRIES_BITS      8               /* # TLB0: read TLB0CFG */
#define N_TLB_ENTRIES           256             /* # TLB0: read TLB0CFG */
#define MMUE500_NUM_STATIC_TLB_ENTIRES 0x10
#endif

#ifdef _ASMLANGUAGE

#ifdef	_WRS_CONFIG_UNIFIED_MMU_LIB
#define R21_OFFSET               0
#define R18_OFFSET               (R21_OFFSET               + _PPC_REG_SIZE)
#define CR_OFFSET                (R18_OFFSET               + _PPC_REG_SIZE)
#define R19_OFFSET               (CR_OFFSET                + _PPC_REG_SIZE)
#define R20_OFFSET               (R19_OFFSET               + _PPC_REG_SIZE)

#ifdef	_WRS_CONFIG_SMP_SMT
#define TLB1ESEL_PTR_OFFSET      (R20_OFFSET               + _PPC_REG_SIZE)
#define PROT_OVERRIDE_VAL_OFFSET (TLB1ESEL_PTR_OFFSET      + _PPC_REG_SIZE)
#else
#define TLB1ESEL_OFFSET          (R20_OFFSET               + _PPC_REG_SIZE)
#define PROT_OVERRIDE_VAL_OFFSET (TLB1ESEL_OFFSET          + _PPC_REG_SIZE)
#endif	/* _WRS_CONFIG_SMP_SMT */

#define PROT_VIRT_ADDR_OFFSET    (PROT_OVERRIDE_VAL_OFFSET + _PPC_REG_SIZE)
#else
#define R3_OFFSET               0
#define R18_OFFSET              (R3_OFFSET  + _PPC_REG_SIZE)
#define R23_OFFSET              (R18_OFFSET + _PPC_REG_SIZE)

#ifdef  USE_SPRG4_7
#define R22_OFFSET              (R23_OFFSET + _PPC_REG_SIZE)
#else   /* USE_SPRG4_7 */
#define CR_OFFSET               (R23_OFFSET + _PPC_REG_SIZE)
# define R19_OFFSET             (CR_OFFSET  + _PPC_REG_SIZE)
# define R20_OFFSET             (R19_OFFSET + _PPC_REG_SIZE)
# define R21_OFFSET             (R20_OFFSET + _PPC_REG_SIZE)
# define R22_OFFSET             (R21_OFFSET + _PPC_REG_SIZE)
#endif  /* USE_SPRG4_7 */
#endif	/* _WRS_CONFIG_UNIFIED_MMU_LIB */

/* _PPC_REG_SIZE = 4 in ILP32 and = 8 in LP64 */

#define W0_OFFSET               0

#ifdef PPC_e6500
#define W1_OFFSET               (W0_OFFSET + sizeof(UINT32))
#else /* e500mc */
#define W1_OFFSET               (W0_OFFSET + _PPC_REG_SIZE)
#endif /* PPC_e6500 */
#define W2_OFFSET               (W1_OFFSET + _PPC_REG_SIZE)
#define W3_OFFSET               (W2_OFFSET + sizeof(UINT32))

#endif /* _ASMLANGUAGE */

#ifndef _ASMLANGUAGE

/* PPC registers temp save area for TLB miss handler functions */

typedef struct ppcTlbSave {
#ifdef	_WRS_CONFIG_UNIFIED_MMU_LIB
    ULONG    ppcR21;            /* R21 */
    ULONG    ppcR18;            /* R18 */
    ULONG    ppcCr;             /* CR  */
    ULONG    ppcR19;            /* R19 */
    ULONG    ppcR20;            /* R20 */

#ifdef	_WRS_CONFIG_SMP_SMT
    TLB1ESEL * pTlb1Esel;       /* TLB1ESEL pointer */
#else
    TLB1ESEL tlb1Esel;          /* TLB1 ESEL */
#ifdef	_WRS_CONFIG_LP64
    UINT32   reserved;          /* reserved field */
#endif	/* _WRS_CONFIG_LP64 */
#endif	/* _WRS_CONFIG_SMP_SMT */

    UINT32   protOverrideVal;   /* value to override protection attributes */
    VIRT_ADDR protVirtAddr;     /* address to override protection attributes */
#else
    ULONG   ppcR3;              /* R3  */
    ULONG   ppcR18;             /* R18 */
    ULONG   ppcR23;             /* R23 */
    ULONG   ppcCr;              /* CR  */
    ULONG   ppcR19;             /* R19 */
    ULONG   ppcR20;             /* R20 */
    ULONG   ppcR21;             /* R21 */
    ULONG   ppcR22;             /* R22 */
#endif	/* _WRS_CONFIG_UNIFIED_MMU_LIB */
} _WRS_DATA_ALIGN_BYTES (_CPU_CACHE_ALIGN_SIZE) PPC_TLB_SAVE; 

/* EPN field mask bits */

#define MMU_EPN_MASK		((0x1UL << MMU_EPN_BITS) - 1)

typedef union   /* e500 pte format */
    {
    UINT32 tlb1cfg;
    struct                      /* Bit field description */
        {
        UINT32 assoc:8;
        UINT32 minsize:4;
        UINT32 mazsize:4;
        UINT32 iprot:1;
        UINT32 avail:1;
        UINT32 :2;
        UINT32 nentry:12;
        } field;
    } E200_TLB1CFG;

#ifdef PPC_e6500
/*
* (PTE)
*
* | 0                                                             |28       31|
* |32                                                             |50       63|
* +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+--+--+--+--+--+--+--+
* |                                                               |           |
* |                              ARPN(0-28)                       |ARPN(29-31)|
* |                                                               |           |
* +---------------------------------------------------------------+-----------+
* |                               28                              |     4     |
*
* | 0       | 8| 9|10|11|12|13|14|15|16 |18 |19|20   |24|25|26|27|28|29|30 |31|
* |32       |40|41|42|43|44|45|46|47|48 |50 |51|52   |56|57|58|59|60|61|62 |63|
* +-+-+-+-+-+--+--+--+--+--+--+--+--+-+-+---+--+-----+--+--+--+--+--+---+--+--+
* |         |  |  |  |  |  |  |  |  |   |   |  |     |  |  |  |  |  |  |   |  |
* |  ARPN   |W |I |M |G |E |R |U0|U1| - |SW0|C |  PS |UX|SX|UW|SW|UR|SR|SW1|V |
* | (32-39) |  |  |  |  |  |  |  |  |   | L |  |     |  |  |  |  |  |  | G |  |
* +---------+--+--+--+--+--+--+--+--+---+---+--+-----+--+--+--+--+--+--+---+--+
* |    8    |1 |1 |1 |1 |1 |1 |1 |1 | 2 | 1 |1 |  4  |1 |1 | 1 |1 |1 |1 |1 | 1|
*
*
* ARPN  - Bbbreviated real page number
* WIMGE - Storage control attributes
* R     - Referenced bit
* U0    - User defined storage control bit 0
* U1    - User defined storage control bit 1
* SW0   - Available for SW use
* C     - Changed bit.
* PS    - Page size
* BAP   - Base access permissions
* SW1   - Available for SW use
* V     - Valid
*
*
* TLB Word 0:  (MAS1)
*
*
* | 0| 1   | 2                         |16  |18 |19|20       |25           31|
* |32|33   |34                         |48  |50 |51|52       |57           63|
* +--+-----+-+-+-+-+-+-+-+-+-+-+-+-+-+-'-+--+---+--+-+-+-+-+-+-+-+-+-+-+-+-+-+
* |  |     |                           |    |   |  |         |               |
* | V|IPROT|           TID             |    |IND|TS| TSIZE   |       -       |
* |  |     |                           |    |   |  |         |               |
* +_-+-----+---------------------------+----+---+--+---------+---------------+
* |1 |  1  |            14             | 2  | 1 |1 |   5     |     7         |
*
* V     - TLB Valid bit
* IPROT - Invalidate protect
* TID   - Translation ID
* IND   - Indirect
* TS    - Translation space
* TSIZE - Translation size
*
* TLB Word 1:  (MAS2)
*
* | 0                                     |20         |25|26|27|28|29|30|31|
* |32                                     |52         |57|58|59|60|61|62|63|
* +-+-+-+-+-+-+-+-'-+-+-+-+-+-+-+-'-+-+-+-+-+-+---+-'-+--+--+--+--+--+--+--+
* |                                                   |  |  |  |  |  |  |  |
* |                    EPN                |     -     |X0|X1|W |I |M |G |E |
* |                                       |           |  |  |  |  |  |  |  |
* +---------------'---------------'-------+-----------+--+--+--+--+--+--+--+
* |                   20                  |     5     |1 |1 |1 |1 |1 |1 |1 |
*
* EPN    - Effective (Virtual) address Page Number
* X0-X1  - Implementation dependant page attribute
* W     - Write-Through
* I     - Caching Inhibited
* M     - Memory Coherency required
* G     - Guarded
* E     - Endianess (Unused and set to zero.)
*
* TLB Word 2:  (MAS3)
*
* | 0                                   |20   |22     |26|27|28|29|30|31|
* |32                                   |52   |54     |58|59|60|61|62|63|
* +-+-+-+-+-+-+-+-'-+-+-+-+-+-+-+-'-+-+-+-+-+-+-+-'-+-+--+--+--+--+--+--+
* |                                     |     |       |  |  |  |  |  |  |
* |                    RPN              |  -  | U0-U3 |UX|SX|UW|SW|UR|SR|
* |                                     |     |       |  |  |  |  |  |  |
* +-------------------------------------+-----+-------+--------------+--+
* |                    RPN              |  -  | U0-U3 |    SPSIZE    |- |
* +-------------------------------------+-----+-------+--+--+--+--+--+--+
* |                   20                |  2  |   4   |       5      |1 |
*
* RPN    - Real (Physical) address Page Number
* U0-U3  - User bits
* UX     - User execute permission
* SX     - Supervisor execute permission
* UW     - User write permission
* SW     - Supervisor write permission
* UR     - User read permission
* SR     - Supervisor read permission
* SPSIZE - Sub-page size (4Kb for e6500)
*
*
* TLB Word 3:  (MAS7)
*
* | 0                                                    |24          31|
* |32                                                    |56          63|
* +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+--+--+--+--+--+
* |                                                      |              |
* |                          -                           |     RPN      |
* |                                                      |              |
* +------------------------------------------------------+--------------+
* |                         24                           |      8       |
*
* RPN    - Real (Physical) address Page Number 8 high order bits
*
*/
#else
/*
*
* E500 PTE descriptor definition 
* This stores most of the fields needed to update a TLB entry. Note that
* we store only 20 bits of the epn, since we support a minimum page size
* of 4K only. ERPN and variable page sizes are currently unimplemented.
*
* TLB fields are from ch. 6. PPCE500GP User's Manual, version 7, March
* 2002
*
* TLB Word 0:
*
* | 0|  1  | 2         | 8             |16   |19|20     |24           31|
* |32| 33  |34         |40             |48   |51|52     |56           63|
* +--+-----+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+-+-+-+-+-+-+-+-+-+
* |  |     |           |               |     |  |       |               |
* | V|IPROT|           |   TID         |     | T| TSIZE |               |
* |  |     |           |               |     | S|       |               |
* +--+-----+-----------+---------------+-----+--+-------+-+-+-+-+-+-+-+-+
* | 1|  1  |     6     |      8        |  3  | 1|   4   |       8       |    
*
* V     - TLB Valid bit
* IPROT - Invalidate protect 
* TID   - Translation ID
* TS    - Translation space
* TSIZE - Translation size 
*
*
* TLB Word 1:
*
* LP64 mode:
*  0                                                              31
* +-----------------------------------------------------------------+
* |                              EPN                                |
* |                                                                 |
* +-----------------------------------------------------------------+
* 32              40              48      52  54      57          63
* +-+-+-+-+-+-+-+-'-+-+-+-+-+-+-+-'-+-+-+-+-+-+---+-'-+-+-+-+-+-+-+-+
* |                    EPN                |   |SHA|   |X|X|W|I|M|G|E|
* |                                       |   |REN|   |1|0| | | | | |
* +---------------'---------------'-------+-+-+---+-'-+-+-+-+-+-+-+-+
*
* ILP32 mode:
* | 0                                     |20 |22 |23 |25         31|
* |32                                     |52 |54 |55 |57         63|
* +-+-+-+-+-+-+-+-'-+-+-+-+-+-+-+-'-+-+-+-+-+-+---+-'-+-+-+-+-+-+-+-+
* |                                       |   |   |   | | | | | | | |
* |                    EPN                |   |SHA|   |X|X|W|I|M|G|E|
* |                                       |   |REN|   |1|0| | | | | |
* +---------------'---------------'-------+-+-+---+-'-+-+-+-+-+-+-+-+
* |                 20                    | 2 | 1 | 2 |      7      |
*
* EPN    - Effective (Virtual) address Page Number
* SHAREN - Enable cache fills to use shared cache state
* X0-X1  - Implementation dependant page attribute 
* W     - Write-Through
* I     - Caching Inhibited
* M     - Memory Coherency required 
* G     - Guarded
* E     - Endianess (Unused and set to zero.)
*
*
* TLB Word 2:
*
* | 0                                     |20 |22     |26       31|
* |32                                     |52 |54     |58       63|
* +-+-+-+-+-+-+-+-'-+-+-+-+-+-+-+-'-+-+-+-+---+-------+-+-+-+-+-+-+
* |                                       |   |       | | | | | | |
* |                    RPN                |   | U0-U3 |U|S|U|S|U|S|
* |                                       |   |       |X|X|W|W|R|R|
* +---------------'---------------'-------+---+-+---+-+-+-+-+-+-+-+
* |                  20                   | 2 |   4   |1|1|1|1|1|1|
*
* RPN    - Real (Physical) address Page Number
* U0-U3  - User bits
* UX     - User execute permission
* SX     - Supervisor execute permission
* UW     - User write permission
* SW     - Supervisor write permission
* UR     - User read permission
* SR     - Supervisor read permission
*
*
*/
#endif /* PPC_e6500 */

/* XXX: Re-visit to make more efficient structure between ILP32 and LP64. */

typedef union e500_pte	/* e500 pte format */
    {
    struct			/* Bit field description */
	{
#if defined(PPC_e6500)
        /* pte format for e6500 */

        /* word 0 */

        UINT32 arpnHigh32:32;     /* real page number */

        /* word 1 */

        UINT32 arpnLow8:8;
        UINT32 w:1;             /* write thru/back */
        UINT32 i:1;             /* cache inhibited */
        UINT32 m:1;             /* memory coherent */
        UINT32 g:1;             /* memory guarded  */
        UINT32 e:1;             /* little endian bit */
        UINT32 r:1;
        UINT32 u0:1;            /* user attribute 0 */
        UINT32 u1:1;            /* user attribute 1 */
        UINT32 rsvd2:2;
        UINT32 lock:1;          /* lock bit label indicating static TLB used */
        UINT32 c:1;
        UINT32 psize:4;         /* translation size */
        UINT32 ux:1;            /* user execute protection */
        UINT32 sx:1;            /* supervisor execute protection */
        UINT32 uw:1;            /* user write protection */
        UINT32 sw:1;            /* supervisor write protection */
        UINT32 ur:1;            /* user read protection */
        UINT32 sr:1;            /* supervisor read protection */
        UINT32 global:1;        /* global bit for internal use */
        UINT32 v:1;             /* valid bit */

#else
        /* pte format for e500mc/e500v2/e200 */

        /* word 0 */

        UINT32 v:1;             /* valid bit */
        UINT32 iprot:1;         /* invalidate protect bit */
        UINT32 rsvd1:6;         /* reserved */
        UINT32 tid:8;           /* translation ID */
        UINT32 rsvd2:3;         /* reserved */
        UINT32 ts:1;            /* translation space */
        UINT32 tsize:4;         /* translation size */
        UINT32 rsvd3:8;         /* reserved */

#ifdef	_WRS_CONFIG_LP64
        UINT32 rsvd8:32;        /* pad descriptor table to power of 2 */
#endif	/* _WRS_CONFIG_LP64 */

        /* word 1 */

        ULONG epn:MMU_EPN_BITS; /* effective page number */
        ULONG rsvd4:2;          /* reserved */
        ULONG sharen:1;         /* enables cache fills to use shared cache state */
        ULONG rsvd5:2;          /* reserved */
        ULONG global:1;         /* global bit for internal use */

#ifdef PPC_e200 /* TLB0 not available on e200 so no lock bit reqd */
        ULONG vle:1;            /* variable length encoding */
#else
        ULONG lock:1;           /* lock bit label indicating static TLB used */
#endif
        ULONG w:1;              /* write thru/back */
        ULONG i:1;              /* cache inhibited */
        ULONG m:1;              /* memory coherent */
        ULONG g:1;              /* memory guarded  */
        ULONG e:1;              /* little endian bit */

        /* word 2 */

        UINT32 rpn:20;          /* real page number */
        UINT32 rsvd6:2;         /* reserved */
        UINT32 u0:1;            /* user attribute 0 */
        UINT32 u1:1;            /* user attribute 1 */
        UINT32 u2:1;            /* user attribute 2 */
        UINT32 u3:1;            /* user attribute 3 */
        UINT32 ux:1;            /* user execute protection */
        UINT32 sx:1;            /* supervisor execute protection */
        UINT32 uw:1;            /* user write protection */
        UINT32 sw:1;            /* supervisor write protection */
        UINT32 ur:1;            /* user read protection */
        UINT32 sr:1;            /* supervisor read protection */

        /* word3 */

#if defined(PPC_e500v2) || defined(PPC_e500mc)
        UINT32 rsvd7:28;        /* reserved*/
        UINT32 erpn:4;          /* extended real page number*/
#else
        UINT32 rsvd7:32;        /* pad descriptor table to power of 2 */
#endif

#ifdef  _WRS_CONFIG_LP64
        ULONG rsvd9:64;         /* pad descriptor table to power of 2 */
#endif  /* _WRS_CONFIG_LP64 */
#endif /* !PPC_e6500 */
	} field;

    struct 
        {
        UINT32 word0;           /* word 0 */
#if defined(_WRS_CONFIG_LP64) && defined(PPC_e500mc)
        UINT32 pad1;            /* pad word */
        ULONG  word1;           /* word 1 */
#else
        UINT32 word1;           /* word 1 */
#endif /* _WRS_CONFIG_LP64 && PPC_e500mc */
#if !defined(PPC_e6500)
        UINT32 word2;           /* word 2 */
#if defined(PPC_e500v2) || defined(PPC_e500mc)
        UINT32 word3;           /* word3 */
#else
        UINT32 pad0;            /* pad word */
#endif
#ifdef  _WRS_CONFIG_LP64
        ULONG pad2;             /* pad dword */
#endif  /* _WRS_CONFIG_LP64 */
#endif /* !PPC_e6500 */
        } words;

    } MMUE500_PTE;

/* TLB Entry description, used for mmu initialization */

typedef struct
    {
    ULONG       effAddr;        /* Effective address of base of page */
    UINT32      realAddrExt;    /* top 4 bits of real address */
    UINT32      realAddr;       /* rest of real address */
    UINT32      attr;           /* page attributes */
#ifdef _WRS_CONFIG_LP64
    UINT32      pad;
#endif /* _WRS_CONFIG_LP64 */
    } TLB_ENTRY_DESC;

#if defined(PPC_e6500)
typedef union e6500_pte  /* e6500 pte format */
    {
    struct                      /* Bit field description */
        {
        /* word 0 */
        UINT32 v:1;             /* valid bit */
        UINT32 iprot:1;         /* invalidate protect bit */
        UINT32 tid:14;           /* translation ID */
        UINT32 rsvd1:2;         /* reserved */
        UINT32 ind:1;            /* translation space */
        UINT32 ts:1;            /* translation space */
        UINT32 tsize:5;         /* translation size */
        UINT32 rsvd3:7;         /* reserved */

        /* word 1 */
        ULONG  epn:MMU_EPN_BITS;/* effective page number */
        ULONG  rsvd4:5;         /* reserved */
        ULONG  global:1;        /* global bit for internal use */
        ULONG  lock:1;          /* lock bit label indicating static TLB used */
        ULONG  w:1;             /* write thru/back */
        ULONG  i:1;             /* cache inhibited */
        ULONG  m:1;             /* memory coherent */
        ULONG  g:1;             /* memory guarded  */
        ULONG  e:1;             /* little endian bit */

        /* word 2 */
        UINT32 rpn:20;          /* real page number */
        UINT32 rsvd6:2;         /* reserved */
        UINT32 u0:1;            /* user attribute 0 */
        UINT32 u1:1;            /* user attribute 1 */
        UINT32 u2:1;            /* user attribute 2 */
        UINT32 u3:1;            /* user attribute 3 */
        UINT32 ux:1;            /* user execute protection */
        UINT32 sx:1;            /* supervisor execute protection */
        UINT32 uw:1;            /* user write protection */
        UINT32 sw:1;            /* supervisor write protection */
        UINT32 ur:1;            /* user read protection */
        UINT32 sr:1;            /* supervisor read protection */

        /* word3 */
        UINT32 rsvd7:24;        /* reserved*/
        UINT32 erpn:8;          /* extended real page number*/
        } field;

    struct 
        {
        UINT32 word0;           /* word 0 */
        ULONG  word1;           /* word 1 */
        UINT32 word2;           /* word 2 */
        UINT32 word3;           /* word 3 */

        } words;

    } MMUE6500_PTE;

#endif /* PPC_e6500 */

#ifdef PPC_e6500
#   define MMUBOOKE_PTE        MMUE6500_PTE
#else /* PPC_e500mc */
#   define MMUBOOKE_PTE        MMUE500_PTE
#endif /* PPC_e6500 */

/*
 * Reserved atomics provides storage for spin locks used to protect
 * resources from simultaneous access by multiple CPUs.  pReservedAtomics,
 * a pointer to this atomics storage, is set to a "well known" address:
 * RESERVED_ATOMICS_ADRS.  It's area is initialized in mmuE500LibInit().
 * The BSP must "allocate" this storage by having it MMU mapped but not used.
 * The storage must be at a "well known" address.
 * 
 * Spin locks fail if any part of the variable's cache line is accessed.
 * The lock fields are aligned to a cache line with the remainder of the
 * line unreferenced by aligning the subsequent field on a cache line.
 * The page containing reserved atomics must be accessible by all CPUs.
 * WARNING: a spin lock is not a sempahore, the caller does NOT block as a
 * result of using a spin lock.
 * 
 * An enumerated index is used rather than an xxCreate because callers on
 * different CPUs need some way to ID the item created.  Intended usage:
 * atomic32Cas(MMU_SYNC,0,1); ... atomic32Cas(MMU_SYNC,1,0);
 */

typedef long atomicM_t _WRS_DATA_ALIGN_BYTES(_CPU_CACHE_ALIGN_SIZE);


typedef struct
{
atomicM_t  arch1;
long       isInitialized;   /* unused atomic area */
atomicM_t  arch2;
atomicM_t  arch3;
atomicM_t  arch4;
atomicM_t  bsp1;
atomicM_t  bsp2;
atomicM_t  cust1;
atomicM_t  cust2;
atomicM_t  pad;  /* ensures cust2 gets an entire line. Do NOT use pad. */
} reservedAtomics_t;

IMPORT reservedAtomics_t  * pReservedAtomics; /* pointer defined in mmuE500Lib.c */

#ifndef RESERVED_ATOMICS_ADRS
#define RESERVED_ATOMICS_ADRS 0x5000
#endif

#define MMU_SYNC &(pReservedAtomics->arch1)
#define L3_SYNC  &(pReservedAtomics->arch2)

#define RA_INITIALIZED_VALUE  0x61746f6d /* ASCII for "atom", atomics cleared */

#if defined(__STDC__) || defined(__cplusplus)

#ifndef _WRS_CONFIG_COMPAT69_ADR_SPACE
extern STATUS mmuE500EarlyInit (PHYS_MEM_DESC * pPhysMemDesc, int physMemDescNum);
extern STATUS mmuE500LibInit (int mmuType);
#else /* _WRS_CONFIG_COMPAT69_ADR_SPACE */
extern STATUS mmuE500LibInit (int mmuType, int staticTlbNum, TLB_ENTRY_DESC * pStaticTlbDesc);
#endif /* !_WRS_CONFIG_COMPAT69_ADR_SPACE */

#else   /* __STDC__ */

#ifndef _WRS_CONFIG_COMPAT69_ADR_SPACE
extern STATUS mmuE500EarlyInit ();
#endif /* !_WRS_CONFIG_COMPAT69_ADR_SPACE */

extern STATUS mmuE500LibInit ();

#endif  /* __STDC__ */

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCmmuPpcE500Libh */
