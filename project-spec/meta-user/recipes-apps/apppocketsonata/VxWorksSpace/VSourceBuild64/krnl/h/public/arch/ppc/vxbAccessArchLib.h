/*  vxbAccessArchLib.h - VxBus access library header file */

/*
 * Copyright (c) 2013, 2015-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
16aug16,y_y  added VXB_ARCH_IO_UnMAP(), VXB_ARCH_MEM_UNMAP(). (V7PRO-3220)
14jul15,pmr  added VXB_REG_MAP_MMU_ATTR, VXB_ARCH_IO_MAP(), VXB_ARCH_MEM_MAP()
17jul13,l_z  Created
*/

#ifndef _INC_vxbAccessArchLibH
#define _INC_vxbAccessArchLibH

#ifdef __cplusplus
extern "C" {
#endif

IMPORT UINT64 vxbSwap64 (UINT64);
IMPORT UINT32 vxbSwap32 (UINT32);
IMPORT UINT16 vxbSwap16 (UINT16);
 
IMPORT UINT8 vxbRead8 (void *, UINT8 *);
IMPORT UINT16 vxbRead16 (void *, UINT16 *);
IMPORT UINT32 vxbRead32 (void *, UINT32 *);
IMPORT UINT64 vxbRead64 (void *, UINT64 *);
IMPORT void vxbWrite8 (void *, UINT8 *, UINT8);
IMPORT void vxbWrite16 (void *, UINT16 *, UINT16);
IMPORT void vxbWrite32 (void *, UINT32 *, UINT32);
IMPORT void vxbWrite64 (void *, UINT64 *, UINT64);
 
/*
 * Possible types of pre-defined I/O operations:
 *
 * VXB_HANDLE_MEM:      memory mapped access
 * VXB_HANDLE_IO:       i/o space access (strict ordering implied)
 * VXB_HANDLE_ORDERED:  memory mapped access, ordering enforced
 *
 * Each of these can also be qualified with:
 *
 * VXB_HANDLE_SWAP()
 *
 * To obtain the byte-swapped version of one of these routines.
 * For example:
 *
 * handle = VXB_HANDLE_SWAP(VXB_HANDLE_IO);
 *
 * Note that for 8 bit access routines, the VXB_HANDLE_SWAP() qualifier
 * has no effect.
 */
 
#define VXB_HANDLE_MEM          0
 
#define VXB_HANDLE_IO           8
#define VXB_HANDLE_ORDERED      24
#define VXB_HANDLE_SWAP(x)	((x) + 48)

#define VXB_HANDLE_OP_READ	0x00
#define VXB_HANDLE_OP_WRITE	0x10
#define VXB_HANDLE_WIDTH(x)	((x) & 0x0F)
#define VXB_HANDLE_OP(x)	((x) & 0xF0)

/*
 * General byte order swapping functions.
 */
#define bswap16(x)      ((LSB(x) << 8) | MSB(x))
#define bswap32(x)      LONGSWAP((UINT32)(x))
#define bswap64(x)	/* not yet */

#if _BYTE_ORDER == _LITTLE_ENDIAN
#define htobe16(x)      bswap16((x))
#define htobe32(x)      bswap32((x))
#define htobe64(x)      bswap64((x))
#define htole16(x)      ((UINT16)(x))
#define htole32(x)      ((UINT32)(x))
#define htole64(x)      ((UINT64)(x))

#define be16toh(x)      bswap16((x))
#define be32toh(x)      bswap32((x))
#define be64toh(x)      bswap64((x))
#define le16toh(x)      ((UINT16)(x))
#define le32toh(x)      ((UINT32)(x))
#define le64toh(x)      ((UINT64)(x))
#else /* _BYTE_ORDER != _LITTLE_ENDIAN */
#define htobe16(x)      ((UINT16)(x))
#define htobe32(x)      ((UINT32)(x))
#define htobe64(x)      ((UINT64)(x))
#define htole16(x)      bswap16((x))
#define htole32(x)      bswap32((x))
#define htole64(x)      bswap64((x))

#define be16toh(x)      ((UINT16)(x))
#define be32toh(x)      ((UINT32)(x))
#define be64toh(x)      ((UINT64)(x))
#define le16toh(x)      bswap16((x))
#define le32toh(x)      bswap32((x))
#define le64toh(x)      bswap64((x))
#endif /* _BYTE_ORDER == _LITTLE_ENDIAN */

/* macros for extracting 32-bit halves of a 64-bit number */

#ifdef	_WRS_CONFIG_LP64
#define VXB_ADDR_LOW32(x)	(UINT32) ((ULONG)(x) & 0xffffffff)
#define VXB_ADDR_HIGH32(x)	(UINT32) (((ULONG)(x) >> 32) & 0xffffffff)
#else
#define VXB_ADDR_LOW32(x)	(UINT32) (x)
#define VXB_ADDR_HIGH32(x)	0
#endif	/* _WRS_CONFIG_LP64 */

/* MMU attributes for accessing device registers */

#define VXB_REG_MAP_MMU_ATTR (MMU_ATTR_SUP_RW |     \
                              MMU_ATTR_CACHE_OFF |  \
                              MMU_ATTR_CACHE_GUARDED)

/* IO and MEM mapping/unmapping macros */

#define VXB_ARCH_IO_MAP(paddr, len) \
    ((VIRT_ADDR)pmapGlobalMap (paddr, len, VXB_REG_MAP_MMU_ATTR))
#define VXB_ARCH_IO_HANDLE VXB_HANDLE_ORDERED

#define VXB_ARCH_MEM_MAP(paddr, len) \
    ((VIRT_ADDR)pmapGlobalMap (paddr, len, VXB_REG_MAP_MMU_ATTR))
#define VXB_ARCH_MEM_HANDLE VXB_HANDLE_ORDERED

#define VXB_ARCH_IO_UNMAP(paddr, len) \
    (pmapGlobalUnmap (paddr, len))

#define VXB_ARCH_MEM_UNMAP(paddr, len) \
    (pmapGlobalUnmap (paddr, len))

#ifdef __cplusplus
}
#endif

#endif /* _INC_vxbAccessArchLibH */
