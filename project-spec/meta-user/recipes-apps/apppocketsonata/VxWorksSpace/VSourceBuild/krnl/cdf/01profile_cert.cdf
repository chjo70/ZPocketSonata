/* 01profile_cert.cdf - profile for safety-certified VxWorks */

/*
 * Copyright (c) 2014-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
17apr17,own  Updated SYNOPSIS (F8862).
10aug16,i_l  maked this profile available for cert only.(V7COR-4393)
15sep15,gls  removed PROFILE_SAFETY_CERT
15jun15,gls  added INCLUDE_FLOATING_POINT, INCLUDE_POSIX_FTRUNC, 
             INCLUDE_CACHE_DMA32_LIB, and INCLUDE_VXMEMPROBE_INIT to profiles
11aug15,pfl  added INCLUDE_VXMEMPROBE_INIT to profiles
01jun15,kk   comment out PROFILE_CERT, will be removed later.
29apr15,gls  added INCLUDE_DLL_CREATE_DELETE, INCLUDE_SLL_CREATE_DELETE, and
             INCLUDE_DEBUG_KPUTS to profiles
24apr15,gls  removed INCLUDE_SEM_READ_WRITE from PROFILE_CERT
23apr15,gls  added INCLUDE_TASK_INFO to profiles
10apr15,pfl  fixed typos
04apr15,gls  added INCLUDE_SOCKLIB to PROFILE_SAFETY_CERT_RTP
             removed INCLUDE_IO_FILE_SYSTEM and INCLUDE_ROMFS from 
             PROFILE_SAFETY_CERT
31mar15,pfl  fixed typos - removed extra spaces that affected build
18mar15,gls  added INCLUDE_SYSCALL_HOOKS to PROFILE_SAFETY_CERT_RTP
             added INCLUDE_TLS to profiles
19feb15,gls  added the PROFILE_SAFETY_CERT and PROFILE_SAFETY_CERT_RTP profiles
21nov14,rgo  updated the cert profile with INCLUDE_POSIX_SHM_API
10sep14,cww  update cert component list to be more in line with requirements
31jul14,pcs  Added INCLUDE_EDR_USER_POLICY
31jul14,pcs  Added INCLUDE_EDR_CUSTOM_POLICY
15may14,cww  written

DESCRIPTION
This file contains the definition for the configuration profile used
with the certified version of VxWorks.
*/

#ifdef _WRS_CONFIG_CERT
Profile PROFILE_SAFETY_CERT_RTP {
    NAME	VxWorks7 certified safety profile including RTP support
    SYNOPSIS	Using this profile will configure a VxWorks kernel image with the certifiable core.
    PROFILES    BSP_DEFAULT
    COMPONENTS	INCLUDE_KERNEL				\
		INCLUDE_NO_INTRINSICS			\
                INCLUDE_SYSCLK_INIT			\
		INCLUDE_EDR_CUSTOM_POLICY		\
		INCLUDE_SEM_BINARY			\
		INCLUDE_SEM_MUTEX			\
		INCLUDE_SEM_COUNTING			\
		INCLUDE_SEM_EXCHANGE			\
		INCLUDE_SEM_BINARY_CREATE		\
		INCLUDE_SEM_MUTEX_CREATE		\
		INCLUDE_SEM_COUNTING_CREATE		\
		INCLUDE_MSG_Q				\
		INCLUDE_MSG_Q_CREATE_DELETE		\
		INCLUDE_VXEVENTS			\
		INCLUDE_WATCHDOGS			\
		INCLUDE_WATCHDOGS_CREATE_DELETE		\
		INCLUDE_TASK_HOOKS			\
		INCLUDE_TASK_CREATE_HOOKS		\
		INCLUDE_EXC_TASK			\
		INCLUDE_JOB_TASK			\
		INCLUDE_DEBUG_KPRINTF			\
		INCLUDE_ANSI_ASSERT			\
		INCLUDE_ANSI_CTYPE			\
		INCLUDE_ANSI_LOCALE			\
		INCLUDE_ANSI_LONGJMP			\
		INCLUDE_ANSI_STDIO			\
		INCLUDE_ANSI_STDLIB			\
		INCLUDE_ANSI_STRING			\
		INCLUDE_ANSI_TIME			\
		INCLUDE_POSIX_CLOCKS			\
		INCLUDE_POSIX_SHM			\
		INCLUDE_POSIX_SHM_API			\
		INCLUDE_SELECT				\
		INCLUDE_ROMFS				\
		INCLUDE_EDR_USER_POLICY			\
		INCLUDE_SIO				\
		INCLUDE_TIME_PART_SCHEDULER		\
                INCLUDE_TIME_PART_SWITCH_HOOKS          \
                INCLUDE_PROTECT_TEXT                    \
                INCLUDE_PROTECT_VEC_TABLE               \
                INCLUDE_PROTECT_TASK_STACK              \
                INCLUDE_PROTECT_INTERRUPT_STACK         \
                INCLUDE_TASK_INFO                       \
                INCLUDE_TASK_STACK_NO_EXEC              \
                INCLUDE_TLS                             \
                INCLUDE_SLL_CREATE_DELETE               \
                INCLUDE_DLL_CREATE_DELETE               \
                INCLUDE_DEBUG_KPUTS                     \
                INCLUDE_BMPLIB                          \
                INCLUDE_HASH                            \
                INCLUDE_FLOATING_POINT                  \
                INCLUDE_POSIX_FTRUNC                    \
                INCLUDE_CACHE_DMA32_LIB                 \
                INCLUDE_VXMEMPROBE_INIT                 \
		INCLUDE_RTP                             \
		INCLUDE_RTP_HOOKS                       \
                INCLUDE_SYSCALL_HOOKS                   \
                INCLUDE_SYSCALL_ACCESS_CTRL             \
                INCLUDE_OBJ_ACCESS_CTRL                 \
                INCLUDE_RESOURCE_ALLOC_CTRL             \
                INCLUDE_SOCKLIB
    EXCLUDES	INCLUDE_NETWORK				\
		INCLUDE_SW_FP				\
		INCLUDE_ISR_OBJECTS			\
		INCLUDE_POSIX_TIMERS			\
		INCLUDE_EDR_PM				\
		INCLUDE_XBD
}
#endif 
