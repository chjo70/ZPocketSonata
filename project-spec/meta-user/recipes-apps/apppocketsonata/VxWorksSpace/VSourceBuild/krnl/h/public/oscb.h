/* oscb.h - oscb header file */

/* 
 * Copyright (c) 2011, 2014 Wind River Systems, Inc. 
 *
 * The right to copy, distribute, modify or otherwise make use 
 * of this software may be licensed only pursuant to the terms 
 * of an applicable Wind River license agreement. 
 */ 

/*
modification history
--------------------
31sep14,pcs  Removed code corresponding to Component INCLUDE_EDR_POLICY_HOOKS.
08apr11,h_w  Fix errores for marco OSCB_VX_CAP_PROTOCOLS
02apr11,h_w  Initial version.
*/

#ifndef __INCoscbh
#define __INCoscbh

#include <vxWorks.h>

#ifdef __cplusplus
extern "C" {
#endif

/* The OSCB version is a 16 bit integer that identifies the version of the OSCB.
   The 8 most significant bits represent OSCB's major version. The 8 least
   significant bits represent OSCB's minor version */
#define OSCB_VERSION		0x0100
#define OSCB_VENDOR_ID		"WR"

/* The signature macros are used to validate the OSCB header. The signature
   field is an array 4 bytes long with the values 0x05, 0xCB, 0xBC and 0x50
   written from the low index to high index */
#define OSCB_SIGN_0		0x05
#define OSCB_SIGN_1		0xCB
#define OSCB_SIGN_2		0xBC
#define OSCB_SIGN_3		0x50
#define OSCB_SIGN_SIZE	4

#define OSCB_ENDIAN_BIG			0
#define OSCB_ENDIAN_LITTLE		1
#define OSCB_ENDIAN_OTHER		2

#if _BYTE_ORDER == _BIG_ENDIAN
#define OSCB_ENDIAN			OSCB_ENDIAN_BIG
#elif _BYTE_ORDER == _LITTLE_ENDIAN
#define OSCB_ENDIAN			OSCB_ENDIAN_LITTLE
#else
#define OSCB_ENDIAN			OSCB_ENDIAN_OTHER
#endif

#define OSCB_PRO_MODEL_ILP32		0
#define OSCB_PRO_MODEL_LP64			1
#define OSCB_PRO_MODEL_ILP64		2

#if defined(_WRS_CONFIG_ILP64)
#define OSCB_PRO_MODEL		OSCB_PRO_MODEL_ILP64
#elif defined(_WRS_CONFIG_LP64)
#define OSCB_PRO_MODEL		OSCB_PRO_MODEL_LP64
#else
#define OSCB_PRO_MODEL		OSCB_PRO_MODEL_ILP32
#endif

struct OSCB_head 
	{
	/* Signature: 0x05, 0xCB, 0xBC, 0x50 */
	unsigned char signature[OSCB_SIGN_SIZE] ;
	/* Endianess identifier: 0=big, 1=little; 2=other */
	uint8_t endianess;
	/* Programming model used by compiler */
	uint8_t programming_mode;
	uint16_t oscb_version;
	char* vendor_id;
	char* os_name;
	char* os_version;
	void* oscb_location;
	};

/* Key/Value pairs identify certain characteristics of the OS. The key itself
   determines the nature of the following value and how it is interpreted.
   OSCB key numbers are broken up into the following ranges
   0x0000 - 0xFFFF: OSCB general keys
   0x10000 - 0x1FFFF: Vendor specific keys
   0x20000 - 0x2FFFF: OS specific keys
   0x30000 - 0x3FFFF: User specific keys
   0x40000 - 0xFFFFFFFFFFFFFFFE: Reserved
*/

#define OSCB_KEY_GENERAL						0x00000
#define OSCB_KEY_VENDOR_SPECIFIC				0x10000
#define OSCB_KEY_OS_SPECIFIC					0x20000

#define OSCB_TERM								0x0000

#define OSCB_OS_SIGNATURE						(0x0001 + OSCB_KEY_GENERAL)
#define OSCB_OS_BUILD_PATH						(0x0002 + OSCB_KEY_GENERAL)
#define OSCB_OS_STATE							(0x0003 + OSCB_KEY_GENERAL)
#define OSCB_TARGET_SIGNATURE					(0x0004 + OSCB_KEY_GENERAL)
#define OSCB_OS_BUILD_HOST						(0x0005 + OSCB_KEY_GENERAL)
#define OSCB_OS_HEARTBEAT						(0x0006 + OSCB_KEY_GENERAL)
#define OSCB_OS_HEARTBEAT_FREQ					(0x0007 + OSCB_KEY_GENERAL)
#define OSCB_OS_FLAGS							(0x0008 + OSCB_KEY_GENERAL)

#define OSCB_VX_BUILD_VARS						(0x0001 + OSCB_KEY_OS_SPECIFIC)
#define OSCB_VX_BUILD_VARS_END					(0x0002 + OSCB_KEY_OS_SPECIFIC)
#define OSCB_VX_BOOTLINE						(0x0003 + OSCB_KEY_OS_SPECIFIC)
#define OSCB_VX_EXC_RECORD						(0x0004 + OSCB_KEY_OS_SPECIFIC)
#define OSCB_VX_CAPABILITY_SET_PROTOCOLS		(0x0005 + OSCB_KEY_OS_SPECIFIC)
#define OSCB_VX_CAPABILITY_SET_KERNEL			(0x0006 + OSCB_KEY_OS_SPECIFIC)
#define OSCB_VX_EDR_LOG							(0x0007 + OSCB_KEY_OS_SPECIFIC)
#define OSCB_VX_SV_LOGS							(0x0008 + OSCB_KEY_OS_SPECIFIC)
#define OSCB_VX_KERNEL_CORE_DUMP				(0x0009 + OSCB_KEY_OS_SPECIFIC)
#define OSCB_VX_RTP_CORE_DUMP					(0x000A + OSCB_KEY_OS_SPECIFIC)

struct OSCB_key_value 
	{
	ptrdiff_t type;
	void* value;
	};

extern uint64_t vxAbsTicks;
extern struct wvLogList* wvCurrentLogList;
extern char _wrs_build_vars[];
extern char _wrs_build_vars_end[];
extern int sysProcNum;
extern char sysBootHost[];
extern char* sysBootLine;	/* address of boot line */
extern char* sysExcMsg;	/* address of exception message area */

#ifdef _WRS_CONFIG_WRHV_GUEST
#define OSCB_OS_FLAG_VIRTUALIZED	(1 << 1)
#else
#define OSCB_OS_FLAG_VIRTUALIZED	(0)
#endif

#ifdef _WRS_CONFIG_SMP
#define OSCB_OS_FLAG_SMP	(1 << 0)
#else
#define OSCB_OS_FLAG_SMP	(0)
#endif

#define OSCB_OS_FLAGS_VALUE	(OSCB_OS_FLAG_VIRTUALIZED | OSCB_OS_FLAG_SMP)

#ifdef INCLUDE_MIPC_SM
#define OSCB_VX_PROTOCOL_MIPC			(1 << 0)
#else
#define OSCB_VX_PROTOCOL_MIPC			(0)
#endif

#ifdef INCLUDE_IPV4
#define OSCB_VX_PROTOCOL_IPV4			(1 << 1)
#else
#define OSCB_VX_PROTOCOL_IPV4			(0)
#endif

#ifdef INCLUDE_IPV6
#define OSCB_VX_PROTOCOL_IPV6			(1 << 2)
#else
#define OSCB_VX_PROTOCOL_IPV6			(0)
#endif

#ifdef INCLUDE_TIPC
#define OSCB_VX_PROTOCOL_TIPC			(1 << 3)
#else
#define OSCB_VX_PROTOCOL_TIPC			(0)
#endif

#ifdef INCLUDE_WDB_PROXY_MIPC
#define OSCB_VX_PROTOCOL_PROXY_MIPC	(1 << 4)
#else
#define OSCB_VX_PROTOCOL_PROXY_MIPC	(0)
#endif

#ifdef INCLUDE_WDB_PROXY_TIPC
#define OSCB_VX_PROTOCOL_PROXY_TIPC	(1 << 5)
#else
#define OSCB_VX_PROTOCOL_PROXY_TIPC	(0)
#endif

#ifdef INCLUDE_WDB_PROXY_UDP
#define OSCB_VX_PROTOCOL_PROXY_UDP	(1 << 6)
#else
#define OSCB_VX_PROTOCOL_PROXY_UDP	(0)
#endif

#ifdef INCLUDE_WDB
#define OSCB_VX_PROTOCOL_WDB			(1 << 7)
#else
#define OSCB_VX_PROTOCOL_WDB			(0)
#endif

#ifdef INCLUDE_TCF
#define OSCB_VX_PROTOCOL_TCF			(1 << 8)
#else
#define OSCB_VX_PROTOCOL_TCF			(0)
#endif

#ifdef INCLUDE_WINDVIEW
#define OSCB_VX_PROTOCOL_SV				(1 << 9)
#else
#define OSCB_VX_PROTOCOL_SV				(0)
#endif

#define OSCB_VX_CAP_PROTOCOLS 	\
        (OSCB_VX_PROTOCOL_MIPC | OSCB_VX_PROTOCOL_IPV4 | \
         OSCB_VX_PROTOCOL_IPV6 | OSCB_VX_PROTOCOL_TIPC | \
         OSCB_VX_PROTOCOL_PROXY_MIPC | OSCB_VX_PROTOCOL_PROXY_TIPC | \
         OSCB_VX_PROTOCOL_PROXY_UDP | OSCB_VX_PROTOCOL_WDB | \
         OSCB_VX_PROTOCOL_TCF | OSCB_VX_PROTOCOL_SV)

#ifdef INCLUDE_LOADER
#define OSCB_VX_OS_LOADER					(1 << 0)
#else
#define OSCB_VX_OS_LOADER					(0)
#endif

#ifdef INCLUDE_RTP
#define OSCB_VX_OS_RTP						(1 << 1)
#else
#define OSCB_VX_OS_RTP						(0)
#endif

#ifdef INCLUDE_WINDVIEW
#define OSCB_VX_OS_SV						(1 << 2)
#else
#define OSCB_VX_OS_SV						(0)
#endif

#define OSCB_VX_OS_EDR						(0)

#ifdef INCLUDE_CORE_DUMP
#define OSCB_VX_OS_KERNEL_CORE_DUMP			(1 << 4)
#else
#define OSCB_VX_OS_KERNEL_CORE_DUMP			(0)
#endif

#ifdef INCLUDE_CORE_DUMP_RTP
#define OSCB_VX_OS_RTP_CORE_DUMP			(1 << 5)
#else
#define OSCB_VX_OS_RTP_CORE_DUMP			(0)
#endif

#define OSCB_VX_CAP_KERNEL \
        (OSCB_VX_OS_LOADER | OSCB_VX_OS_RTP | \
         OSCB_VX_OS_SV | OSCB_VX_OS_EDR | \
         OSCB_VX_OS_KERNEL_CORE_DUMP | OSCB_VX_OS_RTP_CORE_DUMP)

#ifdef __cplusplus
	}
#endif
		 
#endif /* __INCoscbh */

