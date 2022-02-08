/* adrSpaceArchLibP.h - address space header file for PPC32 */

/*
 * Copyright (c) 2013-2014,2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
21jan17,syt  modified KERNEL_TLB_SIZE to 1GB size for PPC64.(V7PRO-3539)
24jun15,w_x  prevent access to non-canonical address (F2518)
20nov14,ylu  LP64 adaptation to support PPC64.(F2518)
24mar14,ylu  added the macros KERNEL_TLB_SIZE/KERNEL_TLB_MASK.
22aug13,pcs  updated macros SHARED_RGN_BASE and SHARED_RGN_SIZE.
21aug13,x_z  created.
*/

#ifndef __INCadrSpaceArchLibPh
#define __INCadrSpaceArchLibPh

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WRS_CONFIG_LP64

/* virtual memory region definitions */

#define KERNEL_SYS_MEM_RGN_BASE		0xffffffff80000000
#define KERNEL_SYS_MEM_RGN_SIZE		0x0000000080000000

#define KERNEL_VIRT_POOL_RGN_BASE	0xffff800000000000
#define KERNEL_VIRT_POOL_RGN_SIZE	0x0000080000000000

#define KERNEL_DIRECT_MAP_RGN_BASE	0xfffff00000000000
#define KERNEL_DIRECT_MAP_RGN_SIZE	0x0000080000000000

#ifdef _WRS_CONFIG_RTP
#define RTP_PRIVATE_RGN_BASE		0x0000000000200000UL
#define RTP_PRIVATE_RGN_SIZE	    0x000007ffffe00000UL
#endif /* _WRS_CONFIG_RTP */

#define SHARED_RGN_BASE			    0x0000780000000000
#define SHARED_RGN_SIZE			    0x0000080000000000

#define NON_CANONICAL_RGN_BASE	    0x0000800000000000UL
#define NON_CANONICAL_RGN_SIZE	    0xffff000000000000UL
#else /* _WRS_CONFIG_LP64 */

/* virtual memory region definitions */

#ifdef _WRS_CONFIG_RTP
#define KERNEL_SYS_MEM_RGN_BASE     0x00000000
#define KERNEL_SYS_MEM_RGN_SIZE     0x20000000

#define KERNEL_VIRT_POOL_RGN_BASE   0x20000000
#define KERNEL_VIRT_POOL_RGN_SIZE   0x60000000

#define RTP_PRIVATE_RGN_BASE        0x80000000
#define RTP_PRIVATE_RGN_SIZE        0x60000000

#define SHARED_RGN_BASE             0xE0000000
#define SHARED_RGN_SIZE             0x20000000
#else /* !_WRS_CONFIG_RTP */
#define KERNEL_SYS_MEM_RGN_BASE     0x00000000
#define KERNEL_SYS_MEM_RGN_SIZE     0x20000000

#define KERNEL_VIRT_POOL_RGN_BASE   0x20000000
#define KERNEL_VIRT_POOL_RGN_SIZE   0xC0000000

#define RTP_PRIVATE_RGN_BASE        0
#define RTP_PRIVATE_RGN_SIZE        0

#define SHARED_RGN_BASE             0xE0000000
#define SHARED_RGN_SIZE             0x20000000
#endif /* _WRS_CONFIG_RTP */
#endif /* _WRS_CONFIG_LP64 */

/*
 * The following macros are used to map the kernel system memory region to 
 * the TLB1 entries. So they must be the configuration supported by PowerPC 
 * E500, and must be updated with the kernel system memory region defines.
 *
 * Note that the start address of the first RAM bank must be aligned with the 
 * TLB size defined here.
 */

#ifdef _WRS_CONFIG_LP64
#define KERNEL_TLB_SIZE             0x40000000              /* 1GB */
#define KERNEL_TLB_SIZE_CODE        0x00000a00              /* _MMU_TLB_SZ_1G */
#else
#define KERNEL_TLB_SIZE             0x10000000              /* 256MB */
#define KERNEL_TLB_SIZE_CODE        0x00000900              /* _MMU_TLB_SZ_256M */
#endif /* _WRS_CONFIG_LP64 */

#define KERNEL_TLB_MASK             (KERNEL_TLB_SIZE-1)
#define KERNEL_TLB_NUM              2
#define KERNEL_TLB_PAGE_MASK_BITS   28
#ifdef _WRS_CONFIG_LP64
#define KERNEL_TLB_EPN_SHIFT        (63 - KERNEL_TLB_PAGE_MASK_BITS)
#else
#define KERNEL_TLB_EPN_SHIFT        (31 - KERNEL_TLB_PAGE_MASK_BITS)
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCadrSpaceArchLibPh */

