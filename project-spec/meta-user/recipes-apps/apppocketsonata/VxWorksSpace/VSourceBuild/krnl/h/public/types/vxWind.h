/* vxWind.h - WIND object types header file */

/*
 * Copyright (c) 1999-2005, 2007-2010, 2013 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
02o,21aug13,rfr  added CONDVAR_ID
02n,09jan13,cww  Fixed incorrect VX_SEMAPHORE_SIZE and VX_MSG_Q_SIZE
		 (WIND00398086). Also, added 64-bit sizes for semRW extensions
02m,06may10,cww  Updated VX_MSG_Q_SIZE
02l,29apr10,pad  Moved extern C statement after include statements.
02k,21jan10,gls  modified OBJ_CORE size
02j,15may09,cww  Updated msgQ size
02i,11may09,cww  Updated WDOG size
02h,26mar09,zl   fixed TASK_ID typedef for 64-bit.
02g,13mar09,pcs  update macro VX_SEMAPHORE_SIZE for LP64 data model.
02f,06feb09,pcs  Updated to add support for the LP64 data model.
02e,05sep08,cww  Removed semBMinimalXXX() and semMMinimalXXX() APIs 
		 (WIND00133039)
02d,07jan08,gls  fast semaphores renamed to minimal semaphores
02c,11dec07,gls  added SEM_FAST_ID
02b,29aug07,jmg  Added VX_MSG_NODE_SIZE adjusted VX_MSG_Q_SIZE. 
02a,06feb07,gls  adjusted VX_SEMAPHORE_SIZE
01z,26aug05,gls  updated VX_SEMAPHORE_SIZE (SPR #111547)
01y,11aug05,yvp  Added VX_xxx_SIZE macros.
01x,03feb05,kk   added OBJ_HANDLE typedef
01w,29mar04,dcc  moved enum definitions to vxWindCommon.h
01v,01mar04,dcc  modified handleTypeStart to be 100.
01u,02dec03,bwa  removed all MsgC/S references
01t,04nov03,kk   added windSdClass for shared data
01s,29oct03,kam  ISR Object code inspection mods
01r,30sep03,ans  Added windTimerClass
01q,04may03,kam  added windIsr class definition
01p,04jun03,bwa  Added 'windMsgCClass' and 'windMsgSClass' definitions.
01o,11jul03,rec  merge in vxWind.h@@/main/base6_itn1_kernel-int/5
01n,20jun03,bwa  added typedefs of MSG_C_ID and MSG_S_ID
01m,04jun03,bwa  Added 'windMsgCClass' and 'windMsgSClass' definitions.
01l,09may03,to   replace PD with RTP.
01k,28mar03,dcc  ported from AE1.1
01j,13mar01,ahm  Added windSetClass (SPR# 64431)
01i,19sep00,dbs  add hamHandleType to handleType enum
01h,24aug00,bwa  added #ifndef _ASMLANGUAGE
01g,18jul00,bwa  put typedefs of _ID here and removed them from their
                 respective files (SPR #32543)
01f,12jun00,aeg  added windOmsClass to windObjClassType.
01e,19jan00,jkf  added cbio handle type
01d,18jan00,jgn  add new handle type for environments
01c,07jan00,aeg  added handleType and windObjClassType enums.
01b,27jan99,aeg  changed OBJ_ID typedef to void *
01a,07jan99,mak  written.
*/

/*
DESCRIPTION
This file typedefs the opaque types for WIND kernel objects.  They
are typedef-ed here so that other header files can declare functions
containing more than one of these types as parameters without having
to include each other - which could cause circular header file
inclusion problems.

The Wind object type and handle type enumerations are also defined here.
*/

#ifndef __INCvxWindh
#define __INCvxWindh

#include <types/vxWindCommon.h>  /* windObjClassType and handleType enum defs */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WRS_CONFIG_LP64
#define VX_SEMAPHORE_SIZE	192	/* 0xc0 */
#define VX_MSG_Q_SIZE		320	/* 0x140 */
#define VX_MSG_NODE_SIZE	24	/* 0x18 */
#define VX_WDOG_SIZE		184	/* 0xb8 */

/* reader/writer semaphore extension sizes */

#define SEM_RW_LIST_ENTRY_SIZE	16	/* 0x10 */
#define SEM_RW_EXT_SIZE       	40	/* 0x28 */

#else /* !_WRS_CONFIG_LP64 */

#define VX_SEMAPHORE_SIZE	112	/* 0x70 */
#define VX_MSG_Q_SIZE		176	/* 0xb0 */
#define VX_MSG_NODE_SIZE	12	/* 0x0c */
#define VX_WDOG_SIZE		96	/* 0x60 */

/* reader/writer semaphore extension sizes */

#define SEM_RW_LIST_ENTRY_SIZE	12	/* 0x0c */
#define SEM_RW_EXT_SIZE		24	/* 0x18 */

#endif /* _WRS_CONFIG_LP64 */

#ifndef _ASMLANGUAGE

typedef int			OBJ_HANDLE;

typedef void *			OBJ_ID;
typedef struct wind_class *	CLASS_ID;
typedef struct wind_group *	GROUP_ID;

typedef struct msg_q *		MSG_Q_ID;
typedef struct semaphore *	SEM_ID;
typedef struct wind_rtp *	RTP_ID;
#ifdef _WRS_CONFIG_LP64
typedef struct windTcb *	TASK_ID;
#else
typedef int	                TASK_ID;
#endif
typedef struct wdog *		WDOG_ID;
typedef struct page_pool_obj *	PAGE_POOL_ID;
typedef struct pgMgrObj *	PAGE_MGR_ID;
typedef struct vm_context *	VM_CONTEXT_ID;
typedef struct mem_part *	PART_ID;
typedef struct wind_isr *       ISR_ID;
#if 0 /* XXX these will be moved here soon */
typedef struct wind_dms *	DMS_ID;
#endif
typedef struct wind_sd *	SD_ID;

typedef struct cond_var *	CONDVAR_ID;

#endif /* #ifndef _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCvxWindh */
