/* 
 * Copyright (c) 2013-2017 Wind River Systems, Inc. 
 * 
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */
 
/*-
 * Copyright (c) 2002 Marcel Moolenaar
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD: src/sbin/gpt/gpt.h,v 1.11 2006/06/22 22:05:28 marcel Exp $
 */

/*
modification history
--------------------
16oct17,ghs  clear build warning
01jun15,jsp  added MBR_BOOTFLAG definition
13may15,txu  fix V7STO-358 : wrong include after extern "C"
13nov14,txu  fix 64-bit data type problem in GPT (V7STO-247)
27jul14,m_y  remove crc32 declaration.
16oct13,m_y  add declaration for gpt parttion create.
06oct13,m_y  added.
*/

/*
DESCRIPTION

This file contains the data structures used by GPT
(Globally Unique Identifier Partition Table).

*/

#ifndef _GPT_H_
#define	_GPT_H_

#include <uuid.h>
#include <lstLib.h>
#include <drv/manager/device.h>
#include <drv/xbd/bio.h>
#include <logLib.h>     /* _func_logMsg */

#ifdef __cplusplus
extern "C" {
#endif

#define	GPT_HDR_SIG		    "EFI PART"
#define	GPT_HDR_REVISION	0x00010000

typedef struct gpt_hdr
    {
    char    hdr_sig[8];
    UINT32	hdr_revision;
    UINT32	hdr_size;
    UINT32	hdr_crc_self;
    UINT32	__reserved;
    UINT64	hdr_lba_self;
    UINT64	hdr_lba_alt;
    UINT64	hdr_lba_start;
    UINT64	hdr_lba_end;
    struct  uuid	hdr_uuid;
    UINT64	hdr_lba_table;
    UINT32	hdr_entries;
    UINT32	hdr_entsz;
    UINT32	hdr_crc_table;
    /*
     * The header as defined in the EFI spec is not a multiple of 8 bytes
     * and given that the alignment requirement is on an 8 byte boundary,
     * padding will happen. We make the padding explicit so that we can
     * correct the value returned by sizeof() when we put the size of the
     * header in field hdr_size, or otherwise use offsetof().
     */
    UINT32	padding;
    }GPT_HDR, *pGPT_HDR;

typedef struct gpt_ent
    {
    struct uuid	ent_type;
    struct uuid	ent_uuid;
    UINT64	ent_lba_start;
    UINT64	ent_lba_end;
    UINT64	ent_attr;
    UINT16	ent_name[36];		/* UTF-16. */
    }GPT_ENT, *pGPT_ENT;

#define	GPT_ENT_ATTR_PLATFORM		        (1ULL << 0)
#define	GPT_ENT_ATTR_NO_BLOCK_IO_PROTOCOL	(1ULL << 1)
/* UEFI won't recognize file system */
#define	GPT_ENT_ATTR_LEGACY_BIOS_BOOTABLE	(1ULL << 2)
/* legacy BIOS boot partition */

#define	GPT_ENT_ATTR_BOOTME		(1ULL << 59)
#define	GPT_ENT_ATTR_BOOTONCE		(1ULL << 58)
#define	GPT_ENT_ATTR_BOOTFAILED		(1ULL << 57)

#define	GPT_ENT_TYPE_UNUSED		\
	{0x00000000,0x0000,0x0000,0x00,0x00,{0x00,0x00,0x00,0x00,0x00,0x00}}
#define	GPT_ENT_TYPE_EFI		\
	{0xc12a7328,0xf81f,0x11d2,0xba,0x4b,{0x00,0xa0,0xc9,0x3e,0xc9,0x3b}}
#define	GPT_ENT_TYPE_MBR		\
	{0x024dee41,0x33e7,0x11d3,0x9d,0x69,{0x00,0x08,0xc7,0x81,0xf3,0x9f}}
#define	GPT_ENT_TYPE_FREEBSD		\
	{0x516e7cb4,0x6ecf,0x11d6,0x8f,0xf8,{0x00,0x02,0x2d,0x09,0x71,0x2b}}
#define	GPT_ENT_TYPE_FREEBSD_SWAP	\
	{0x516e7cb5,0x6ecf,0x11d6,0x8f,0xf8,{0x00,0x02,0x2d,0x09,0x71,0x2b}}
#define	GPT_ENT_TYPE_FREEBSD_UFS	\
	{0x516e7cb6,0x6ecf,0x11d6,0x8f,0xf8,{0x00,0x02,0x2d,0x09,0x71,0x2b}}
#define	GPT_ENT_TYPE_FREEBSD_VINUM	\
	{0x516e7cb8,0x6ecf,0x11d6,0x8f,0xf8,{0x00,0x02,0x2d,0x09,0x71,0x2b}}
#define	GPT_ENT_TYPE_FREEBSD_ZFS	\
	{0x516e7cba,0x6ecf,0x11d6,0x8f,0xf8,{0x00,0x02,0x2d,0x09,0x71,0x2b}}
#define	GPT_ENT_TYPE_FREEBSD_BOOT	\
	{0x83bd6b9d,0x7f41,0x11dc,0xbe,0x0b,{0x00,0x15,0x60,0xb8,0x4f,0x0f}}
#define GPT_ENT_TYPE_VXWORKS \
	{0x83bd6b9d,0x7f41,0x11dc,0xbe,0x0b,{0x56,0x78,0x57,0x6F,0x72,0x6b}}

/*
 * The following are unused but documented here to avoid reuse.
 *
 * GPT_ENT_TYPE_FREEBSD_UFS2	\
 *	{0x516e7cb7,0x6ecf,0x11d6,0x8f,0xf8,{0x00,0x02,0x2d,0x09,0x71,0x2b}}
 */

/*
 * Foreign partition types that we're likely to encounter. Note that Linux
 * apparently choose to share data partitions with MS. I don't what the
 * advantage might be. I can see how sharing swap partitions is advantageous
 * though.
 */
#define	GPT_ENT_TYPE_MS_RESERVED	\
	{0xe3c9e316,0x0b5c,0x4db8,0x81,0x7d,{0xf9,0x2d,0xf0,0x02,0x15,0xae}}
#define	GPT_ENT_TYPE_MS_BASIC_DATA	\
	{0xebd0a0a2,0xb9e5,0x4433,0x87,0xc0,{0x68,0xb6,0xb7,0x26,0x99,0xc7}}
#define	GPT_ENT_TYPE_MS_LDM_METADATA	\
	{0x5808c8aa,0x7e8f,0x42e0,0x85,0xd2,{0xe1,0xe9,0x04,0x34,0xcf,0xb3}}
#define	GPT_ENT_TYPE_MS_LDM_DATA	\
	{0xaf9b60a0,0x1431,0x4f62,0xbc,0x68,{0x33,0x11,0x71,0x4a,0x69,0xad}}

#define	GPT_ENT_TYPE_LINUX_DATA		GPT_ENT_TYPE_MS_BASIC_DATA
#define	GPT_ENT_TYPE_LINUX_RAID		\
	{0xa19d880f,0x05fc,0x4d3b,0xa0,0x06,{0x74,0x3f,0x0f,0x84,0x91,0x1e}}
#define	GPT_ENT_TYPE_LINUX_SWAP		\
	{0x0657fd6d,0xa4ab,0x43c4,0x84,0xe5,{0x09,0x33,0xc8,0x4b,0x4f,0x4f}}
#define	GPT_ENT_TYPE_LINUX_LVM		\
	{0xe6d6d379,0xf507,0x44c2,0xa2,0x3c,{0x23,0x8f,0x2a,0x3d,0xf9,0x28}}

#define	GPT_ENT_TYPE_VMFS		\
	{0xaa31e02a,0x400f,0x11db,0x95,0x90,{0x00,0x0c,0x29,0x11,0xd1,0xb8}}
#define	GPT_ENT_TYPE_VMKDIAG		\
	{0x9d275380,0x40ad,0x11db,0xbf,0x97,{0x00,0x0c,0x29,0x11,0xd1,0xb8}}
#define	GPT_ENT_TYPE_VMRESERVED		\
	{0x9198effc,0x31c0,0x11db,0x8f,0x78,{0x00,0x0c,0x29,0x11,0xd1,0xb8}}

#define	GPT_ENT_TYPE_APPLE_BOOT		\
	{0x426F6F74,0x0000,0x11aa,0xaa,0x11,{0x00,0x30,0x65,0x43,0xec,0xac}}
#define	GPT_ENT_TYPE_APPLE_HFS		\
	{0x48465300,0x0000,0x11aa,0xaa,0x11,{0x00,0x30,0x65,0x43,0xec,0xac}}
#define	GPT_ENT_TYPE_APPLE_UFS		\
	{0x55465300,0x0000,0x11aa,0xaa,0x11,{0x00,0x30,0x65,0x43,0xec,0xac}}
#define	GPT_ENT_TYPE_APPLE_ZFS		\
	{0x6a898cc3,0x1dd2,0x11b2,0x99,0xa6,{0x08,0x00,0x20,0x73,0x66,0x31}}
#define	GPT_ENT_TYPE_APPLE_RAID		\
	{0x52414944,0x0000,0x11aa,0xaa,0x22,{0x00,0x30,0x65,0x43,0xec,0xac}}
#define	GPT_ENT_TYPE_APPLE_RAID_OFFLINE	\
	{0x52414944,0x5f4f,0x11aa,0xaa,0x22,{0x00,0x30,0x65,0x43,0xec,0xac}}
#define GPT_ENT_TYPE_APPLE_LABEL	\
    	{0x4C616265,0x6c00,0x11aa,0xaa,0x11,{0x00,0x30,0x65,0x43,0xec,0xac}}
#define	GPT_ENT_TYPE_APPLE_TV_RECOVERY	\
    	{0x5265636f,0x7665,0x11AA,0xaa,0x11,{0x00,0x30,0x65,0x43,0xec,0xac}}

#define	GPT_ENT_TYPE_NETBSD_FFS		\
	{0x49f48d5a,0xb10e,0x11dc,0xb9,0x9b,{0x00,0x19,0xd1,0x87,0x96,0x48}}
#define	GPT_ENT_TYPE_NETBSD_LFS		\
	{0x49f48d82,0xb10e,0x11dc,0xb9,0x9b,{0x00,0x19,0xd1,0x87,0x96,0x48}}
#define	GPT_ENT_TYPE_NETBSD_SWAP	\
	{0x49f48d32,0xb10e,0x11dc,0xB9,0x9B,{0x00,0x19,0xd1,0x87,0x96,0x48}}
#define	GPT_ENT_TYPE_NETBSD_RAID	\
	{0x49f48daa,0xb10e,0x11dc,0xb9,0x9b,{0x00,0x19,0xd1,0x87,0x96,0x48}}
#define	GPT_ENT_TYPE_NETBSD_CCD		\
	{0x2db519c4,0xb10f,0x11dc,0xb9,0x9b,{0x00,0x19,0xd1,0x87,0x96,0x48}}
#define	GPT_ENT_TYPE_NETBSD_CGD		\
	{0x2db519ec,0xb10f,0x11dc,0xb9,0x9b,{0x00,0x19,0xd1,0x87,0x96,0x48}}
#define	GPT_ENT_TYPE_NETBSD_RAIDFRAME	\
	{0x49f48daa,0xb10e,0x11dc,0xb9,0x9b,{0x00,0x19,0xd1,0x87,0x96,0x48}}

/*
 * Boot partition used by GRUB 2.
 */
#define	GPT_ENT_TYPE_BIOS		\
	{0x21686148,0x6449,0x6e6f,0x74,0x4e,{0x65,0x65,0x64,0x45,0x46,0x49}}

/*
 * XXX struct gpt_hdr is not a multiple of 8 bytes in size and thus
 * contains padding we must not include in the size.
 */
#define GPT_SIZE offsetof(struct gpt_hdr, padding)

void	le_uuid_dec(void const *, uuid_t *);
void	le_uuid_enc(void *, uuid_t const *);

struct mbr_part
    {
    UINT8		part_flag;		/* bootstrap flags */
    UINT8		part_shd;		/* starting head */
    UINT8		part_ssect;		/* starting sector */
    UINT8		part_scyl;		/* starting cylinder */
    UINT8		part_type;		/* partition type */
    UINT8		part_ehd;		/* end head */
    UINT8		part_esect;		/* end sector */
    UINT8		part_ecyl;		/* end cylinder */
    UINT32      part_start;
    UINT32      part_size;
    };

struct mbr
    {
    UINT8		mbr_code[446];
    struct mbr_part	mbr_part[4];
    UINT16	    mbr_sig;
    }WRS_PACK_ALIGN(1);

typedef struct gpt_part_vec{
    UINT64      part_start;
    UINT64      part_size;
    }GPT_PART_VEC, *pGPT_PART_VEC;

#define MBR_BOOTFLAG	0x80
#define	MBR_SIG		0xAA55

int gptMbrParse
    (
    device_t          dev,
    sector_t          startBlock    /* location of partition table */
    ) ;
int gptParse
    (
    device_t          dev,
    sector_t          startBlock     /* location of partition table */
    );
int gptCheckMap
    (
    LIST *           pMapList,
    UINT32           uFlag
    );
int  gptCreate
    (
    device_t dev,
    BOOL     bUpdate
    );
int gptAdd
    (
    device_t dev,
    UINT64    offset,
    UINT64    size,
    BOOL     bUpdate
    );
void gptRemove
    (
    device_t  dev
    );
int xbdGptPartStart
    (
    char *    devName
    );
int xbdGptPartAdd
    (
    char *    devName,
    UINT64    parStart,
    UINT64    parSize
    );
int xbdGptPartFin
    (
    char *    devName
    );
int xbdGptPartVecAdd
    (
    char *          devName,
    int             nParts,
    pGPT_PART_VEC   pPGptPartVec
    );

#define GPT_NONE_DEBUG                 0   /* Show NONE msgs       */
#define GPT_ERROR_DEBUG                1   /* Show ERROR msgs      */
#define GPT_WARNING_DEBUG              2   /* Show WARNING msgs    */
#define GPT_NORMAL_DEBUG               3   /* Show NORMAL msgs     */
#define GPT_VERBOSE_DEBUG              4   /* Show VERBOSE msgs    */

#ifdef  GPT_ENABLE

#define GPT_ERR(class, fmt, arg1, arg2, arg3, arg4, arg5, arg6)  \
    do {                                                         \
        if (((class##Debug) >= GPT_ERROR_DEBUG) &&               \
            (_func_logMsg != NULL))                              \
            {                                                    \
            _func_logMsg(                                        \
                    "ERROR: " #class " - " fmt,                  \
                    (_Vx_usr_arg_t)(arg1),                       \
                    (_Vx_usr_arg_t)(arg2),                       \
                    (_Vx_usr_arg_t)(arg3),                       \
                    (_Vx_usr_arg_t)(arg4),                       \
                    (_Vx_usr_arg_t)(arg5),                       \
                    (_Vx_usr_arg_t)(arg6));                      \
            }                                                    \
    } while (FALSE)

#define GPT_WARN(class, fmt, arg1, arg2, arg3, arg4, arg5, arg6) \
    do {                                                         \
        if (((class##Debug) >= GPT_WARNING_DEBUG) &&             \
            (_func_logMsg != NULL))                              \
            {                                                    \
            _func_logMsg("WARN: " #class " - " fmt,              \
                    (_Vx_usr_arg_t)(arg1),                       \
                    (_Vx_usr_arg_t)(arg2),                       \
                    (_Vx_usr_arg_t)(arg3),                       \
                    (_Vx_usr_arg_t)(arg4),                       \
                    (_Vx_usr_arg_t)(arg5),                       \
                    (_Vx_usr_arg_t)(arg6));                      \
            }                                                    \
    } while (FALSE)

#define GPT_DBG(class, fmt, arg1, arg2, arg3, arg4, arg5, arg6)  \
    do {                                                         \
        if (((class##Debug) >= GPT_NORMAL_DEBUG) &&              \
            (_func_logMsg != NULL))                              \
            {                                                    \
            _func_logMsg("DBG: " #class " - " fmt,               \
                    (_Vx_usr_arg_t)(arg1),                       \
                    (_Vx_usr_arg_t)(arg2),                       \
                    (_Vx_usr_arg_t)(arg3),                       \
                    (_Vx_usr_arg_t)(arg4),                       \
                    (_Vx_usr_arg_t)(arg5),                       \
                    (_Vx_usr_arg_t)(arg6));                      \
            }                                                    \
    } while (FALSE)

#define GPT_VDBG(class, fmt, arg1, arg2, arg3, arg4, arg5, arg6) \
    do {                                                         \
        if (((class##Debug) >= GPT_VERBOSE_DEBUG) &&             \
            (_func_logMsg != NULL))                              \
            {                                                    \
            _func_logMsg("VDBG: " #class " - " fmt,              \
                    (_Vx_usr_arg_t)(arg1),                       \
                    (_Vx_usr_arg_t)(arg2),                       \
                    (_Vx_usr_arg_t)(arg3),                       \
                    (_Vx_usr_arg_t)(arg4),                       \
                    (_Vx_usr_arg_t)(arg5),                       \
                    (_Vx_usr_arg_t)(arg6));                      \
            }                                                    \
    } while (FALSE)

#define GPT_INFO(class, fmt, arg1, arg2, arg3, arg4, arg5, arg6) \
    do {                                                         \
        if (_func_logMsg != NULL)                                \
            {                                                    \
            _func_logMsg("INFO: " #class " - " fmt,              \
                    (_Vx_usr_arg_t)(arg1),                       \
                    (_Vx_usr_arg_t)(arg2),                       \
                    (_Vx_usr_arg_t)(arg3),                       \
                    (_Vx_usr_arg_t)(arg4),                       \
                    (_Vx_usr_arg_t)(arg5),                       \
                    (_Vx_usr_arg_t)(arg6));                      \
            }                                                    \
    } while (FALSE)

#else

#define GPT_ERR(class, fmt, arg1, arg2, arg3, arg4, arg5, arg6)
#define GPT_DBG(class, fmt, arg1, arg2, arg3, arg4, arg5, arg6)
#define GPT_VDBG(class, fmt, arg1, arg2, arg3, arg4, arg5, arg6)
#define GPT_INFO(class, fmt, arg1, arg2, arg3, arg4, arg5, arg6)
#define GPT_WARN(class, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#endif

#define GPT_CORE_ERR(fmt, arg1, arg2, arg3, arg4, arg5, arg6)   \
    GPT_ERR(gptCore, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#define GPT_CORE_DBG(fmt, arg1, arg2, arg3, arg4, arg5, arg6)   \
    GPT_DBG(gptCore, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#define GPT_CORE_VDBG(fmt, arg1, arg2, arg3, arg4, arg5, arg6)  \
    GPT_VDBG(gptCore, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#define GPT_CORE_INFO(fmt, arg1, arg2, arg3, arg4, arg5, arg6)  \
    GPT_INFO(gptCore, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#define GPT_CORE_WARN(fmt, arg1, arg2, arg3, arg4, arg5, arg6)  \
    GPT_WARN(gptCore, fmt, arg1, arg2, arg3, arg4, arg5, arg6)


#define GPT_MAP_ERR(fmt, arg1, arg2, arg3, arg4, arg5, arg6)   \
    GPT_ERR(gptMap, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#define GPT_MAP_DBG(fmt, arg1, arg2, arg3, arg4, arg5, arg6)   \
    GPT_DBG(gptMap, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#define GPT_MAP_VDBG(fmt, arg1, arg2, arg3, arg4, arg5, arg6)  \
    GPT_VDBG(gptMap, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#define GPT_MAP_INFO(fmt, arg1, arg2, arg3, arg4, arg5, arg6)  \
    GPT_INFO(gptMap, fmt, arg1, arg2, arg3, arg4, arg5, arg6)

#define GPT_MAP_WARN(fmt, arg1, arg2, arg3, arg4, arg5, arg6)  \
    GPT_WARN(gptMap, fmt, arg1, arg2, arg3, arg4, arg5, arg6)


#ifdef __cplusplus
}
#endif

#endif /* _GPT_H_ */
