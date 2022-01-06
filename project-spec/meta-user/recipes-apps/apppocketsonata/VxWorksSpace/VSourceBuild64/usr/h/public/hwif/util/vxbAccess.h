/* vxbAccess.h - vxBus access routines header file */
/*
 * Copyright (c) 2005-2009,2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02oct15,wap  Move VXB_REG_DEF definition to vxbIoctlLib.h, remove unused
             macros
29sep15,wap  Add support for user-space VxBus interface (F2165)
30oct14,l_z  reserved C++ keyword. (V7PRO-1422)
18mar14,elp  added simulator support.
07dec09,h_k  added vxbRegUnmap() and vxbRegUnmapAll().
11mar09,h_k  updated for LP64 support. (CQ:160416)
31jul08,h_k  fixed dependency between drivers and vxbPci. (CQ:125581)
10jun08,h_k  removed vxbAccessList structure.
01may08,h_k  added vxbPciDevCfgRead/vxbPciDevCfgWrite.
14apr08,h_k  disabled legacy access support for all architectures.
20feb08,h_k  changed VXB_HANDLE_IO and ORDERED to optimize the I-cache
             line usages on PPC.
18jul07,h_k  corrected VXB_HANDLE_IO, VXB_HANDLE_ORDERED and
             VXB_HANDLE_SWAP offsets for SH.
06jul07,wap  Disable legacy access support for XSCALE
04jul07,wap  Add special option decoding macros
12jun07,tor  remove VIRT_ADDR
04may07,wap  Convert to new register access API
01jun06,wap  Add some utility macros
29sep05,mdo  Fix gnu warnings
20sep05,pdg  Fix for vxbus access routines errors (SPR #112197)
10aug05,mdo  Phase in new access method
01aug05,mdo  Updating bus access methods
15Jul05,gpd  written
*/

#ifndef __INCvxbAccessh
#define __INCvxbAccessh

#ifdef __cplusplus
extern "C" {
#else
/* reserved C++ keyword "virtual" was used as field name renamed to "virtAddr" */
#define virtual virtAddr
#endif

#include <vxWorks.h>
#include <hwif/util/vxbResourceLib.h>

#ifdef _WRS_KERNEL
#if (CPU_FAMILY == PPC)
#include <arch/ppc/vxbAccessArchLib.h>
#elif (CPU_FAMILY == I80X86)
#include <arch/i86/vxbAccessArchLib.h>
#elif(CPU_FAMILY == ARM)
#include <arch/arm/vxbAccessArchLib.h>
#elif(CPU_FAMILY == SIMLINUX)
#include <arch/simlinux/vxbAccessArchLib.h>
#elif(CPU_FAMILY == SIMNT)
#include <arch/simnt/vxbAccessArchLib.h>
#else
#error "unsupported ARCH"
#endif
#else /* _WRS_KERNEL */

typedef struct vxbRegHandle
    {
    int                 vxbResFd;
    VXB_RESOURCE *      pVxbRes;
    } VXB_REG_HANDLE;

IMPORT UINT64 vxbSwap64 (UINT64);
IMPORT UINT32 vxbSwap32 (UINT32);
IMPORT UINT16 vxbSwap16 (UINT16);
 
IMPORT UINT8 vxbRead8 (void *, UINT8 *);
IMPORT UINT16 vxbRead16 (void *, UINT16 *);
IMPORT UINT32 vxbRead32 (void *, UINT32 *);
IMPORT void vxbWrite8 (void *, UINT8 *, UINT8);
IMPORT void vxbWrite16 (void *, UINT16 *, UINT16);
IMPORT void vxbWrite32 (void *, UINT32 *, UINT32);

/*
 * General byte order swapping functions.
 */
#define bswap16(x)      ((LSB(x) << 8) | MSB(x))
#define bswap32(x)      LONGSWAP((UINT32)(x))
#define bswap64(x)      /* not yet */

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

#ifdef  _WRS_CONFIG_LP64
#define VXB_ADDR_LOW32(x)       (UINT32) ((ULONG)(x) & 0xffffffff)
#define VXB_ADDR_HIGH32(x)      (UINT32) (((ULONG)(x) >> 32) & 0xffffffff)
#else
#define VXB_ADDR_LOW32(x)       (UINT32) (x)
#define VXB_ADDR_HIGH32(x)      0
#endif  /* _WRS_CONFIG_LP64 */

#endif /* _WRS_KERNEL */

typedef struct vxbResourceAdr
    {
    PHYS_ADDR start;    /* resource range start */
    VIRT_ADDR virtAddr; /* virtual address, for memory mapped resources */
    size_t    size;     /* resource range size */
    void * pHandle;  /* phandle to access the device */
    } VXB_RESOURCE_ADR;

IMPORT STATUS vxbRegMap (VXB_RESOURCE *pRes);
IMPORT STATUS vxbRegUnmap (VXB_RESOURCE *pRes);

#ifdef	_WRS_CONFIG_LP64
IMPORT STATUS vxbRegUnmapAll (VXB_DEV_ID);
#endif	/* _WRS_CONFIG_LP64 */


#ifdef __cplusplus
}
#endif

#include <hwif/methods/vxbDevMethod.h>

#endif /* __INCvxbAccessh */

