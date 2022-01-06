/* tlsLibP.h - TLS private interface header */

/*
 * Copyright (c) 2006-2010, 2014-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
08sep16,f_l  Fixed Linux TLS ABI support (US78970)
11aug16,l_l  updated TLS_VAR_ADDR for standard TLS ABI (TCLLVM-25)
09aug16,l_l  added DKM TLS support in standard TLS ABI (US80079)
22jul16,h_k  moved TLS_DESC definition from tlsLibSP.h. (F6619)
01jun16,l_l  supported standard TLS ABI. (US80078)
04aug15,h_k  cleaned up compiler warnings at tlsLibInit() call. (F2518)
07feb14,jmp  Warning cleanup: Moved tlsModuleAdd|Remove from tlsLibSP.h.
10sep10,jpb  Added function pointer _func_tlsSizeGet.
23jul10,gvm  updates for 64-bit user side TLS ABI 
12jul10,gvm  ICC implements __tls_varp
14oct09,gvm  Fix for defect WIND00104917
23sep09,gvm  adapted to LP64
12apr08,mcm  Using the same definition of TLS_VAR_ADDR for both compilers
14jun07,jpb  Changed definition of TLS_VAR_ADDR based on compiler
25apr07,gls  ported to user side
19oct06,dbt  written
*/

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef __INCtlsLibPh
#define __INCtlsLibPh

#ifdef __cplusplus
extern "C" {
#endif

/* type declaration */

struct __tls__var;

/* variable declarations */

#ifdef _WRS_KERNEL
IMPORT UCHAR	wrs_kernel_tls_data_start [];
IMPORT UCHAR	wrs_kernel_tls_data_size [];
#ifdef _WRS_CONFIG_LANG_LIB_TLS_STD
IMPORT UCHAR	wrs_kernel_tls_mem_size [];
#else
IMPORT UCHAR	wrs_kernel_tls_vars_start [];
IMPORT UCHAR	wrs_kernel_tls_vars_size [];
#endif
IMPORT UCHAR	wrs_kernel_tls_data_align [];
#else
IMPORT UCHAR	__wrs_rtp_tls_data_start [];
IMPORT UCHAR	__wrs_rtp_tls_data_size [];
IMPORT UCHAR	__wrs_rtp_tls_vars_start [];
IMPORT UCHAR	__wrs_rtp_tls_vars_size [];
IMPORT UCHAR	__wrs_rtp_tls_data_align [];
#endif

typedef struct tls_desc			/* TLS task descriptor */
    {
    UINT32			maxModules;	/* number of slots available */
    struct tls_task_module_info * pTlsTaskModule; /* TLS task module */
						/* descriptors */
    void *			addr;		/* static module tls area */
    						/* address for this task */
    } TLS_DESC;

/* defines */

/* Get the pointer on a __thread variable structure given its name */

#if	defined(__RTP__) && defined(_WRS_CONFIG_LP64) || defined(_WRS_CONFIG_LANG_LIB_TLS_STD)
#define	TLS_VAR_ADDR(x)		(&(x))
#else
#define TLS_VAR_ADDR(x)		__tls_varp(&(x))
#if defined(__GNUC__) && !defined(__INTEL_COMPILER)
#define	__tls_varp		__builtin___tls_varp
#endif	/* __GNUC__ && !__INTEL_COMPILER */
#endif	/* __RTP__ && _WRS_CONFIG_LP64 */

/* function declarations */

#if	defined(__RTP__) && defined(_WRS_CONFIG_LP64)
extern void *	tlsByTaskLookup		(void * pTlsVar, TASK_ID tid);
#else
extern void *	tlsByTaskLookup		(struct __tls__var * pTlsVar,
					 TASK_ID tid);
#endif	/* __RTP__ && _WRS_CONFIG_LP64 */

#ifdef	_WRS_KERNEL
#ifdef _WRS_CONFIG_LANG_LIB_TLS_STD
extern void	tlsLibInit		(void * tlsDataAddr,
					 size_t tlsDataSize,
					 size_t tlsMemSize,
					 size_t tlsDataAlignment,
					 size_t tlsDkmSize);
#else
extern void	tlsLibInit		(void * tlsVarsAddr,
					 size_t tlsVarsSize,
					 void * tlsDataAddr,
					 size_t tlsDataSize,
					 size_t tlsDataAlignment);
#endif

extern void	tlsLoadLibInit		(void);

#ifdef  _WRS_CONFIG_LOADER
extern void 	tlsModuleAdd		(void * moduleId, void * tlsVarsAddr,
					 UINT32 tlsVarsSize, 
					 void * tlsDataAddr, UINT32 tlsDataSize,
					 UINT32 tlsDataAlignment);
extern void	tlsModuleRemove		(void * moduleId);
#ifdef _WRS_CONFIG_LANG_LIB_TLS_STD
extern STATUS 	tlsStdModuleAdd		(void * moduleId, size_t tlsBssSize,
					 void * tlsDataAddr, size_t tlsDataSize,
					 size_t tlsDataAlignment);
extern void	tlsStdModuleRemove		(void * moduleId);
extern off_t	tlsStdModuleBlockOffset		(void * moduleId);
#endif
#endif  /* _WRS_CONFIG_LOADER */
#endif	/* _WRS_KERNEL */

/* function pointers */

#ifndef _WRS_KERNEL
extern int     (*_func_tlsSizeGet)(void); 
#endif /* !_WRS_KERNEL */

#ifdef __cplusplus
}
#endif

#endif /* __INCtlsLibPh */
