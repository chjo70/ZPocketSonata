/* tlsLibP.h - TLS private interface header */

/*
 * Copyright (c) 2006-2010, 2014-2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
12sep15,dms  Fix TLS initialization segment alignment for variant II (TCICC-277)
22jul15,dms  Add support for TLS ABI variant II (V7COR-1369)
02mar14,gvm  VXW7-1877
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

#if	!defined(_WRS_CONFIG_COMPAT69) 
#define	_WRS_TLS_ABI_SVR4

/* Temporary workaround until all architectures fully support the ABI.  */
#if (_VX_CPU_FAMILY == _VX_I80X86) || (_VX_CPU_FAMILY == _VX_SIMNT) || (_VX_CPU_FAMILY == _VX_SIMLINUX)
#define	_TLS_VARIANT	2
#else
#define	_TLS_VARIANT	1
#endif

/* Truncate or round up x to a multiple of y, which is a power of 2.  */
#define	TLSMEM_ALIGN(x, y)	((x) & ~((y) - 1))
#define	TLSMEM_ROUND_UP(x, y)	TLSMEM_ALIGN((x) + (y) - 1, (y))

#elif (defined(__RTP__) && defined(_WRS_CONFIG_LP64))
#define	_WRS_TLS_ABI_SVR4
#else
#define	_WRS_TLS_ABI_VXWORKS
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef	_WRS_TLS_ABI_VXWORKS
/* type declaration */

struct __tls__var;

/* variable declarations */

#ifdef _WRS_KERNEL
IMPORT UCHAR	wrs_kernel_tls_data_start [];
IMPORT UCHAR	wrs_kernel_tls_data_size [];
IMPORT UCHAR	wrs_kernel_tls_vars_start [];
IMPORT UCHAR	wrs_kernel_tls_vars_size [];
IMPORT UCHAR	wrs_kernel_tls_data_align [];
#else
IMPORT UCHAR	__wrs_rtp_tls_data_start [];
IMPORT UCHAR	__wrs_rtp_tls_data_size [];
IMPORT UCHAR	__wrs_rtp_tls_vars_start [];
IMPORT UCHAR	__wrs_rtp_tls_vars_size [];
IMPORT UCHAR	__wrs_rtp_tls_data_align [];
#endif
#endif	/* _WRS_TLS_ABI_VXWORKS */

/* defines */

/* Get the pointer on a __thread variable structure given its name */

#if	defined(_WRS_TLS_ABI_SVR4)
#define	TLS_VAR_ADDR(x)		(&(x))
#else
#define TLS_VAR_ADDR(x)		__tls_varp(&(x))
#if defined(__GNUC__) && !defined(__INTEL_COMPILER)
#define	__tls_varp		__builtin___tls_varp
#endif	/* __GNUC__ && !__INTEL_COMPILER */
#endif	/* _WRS_TLS_ABI_SVR4 */

/* function declarations */

#if	defined(_WRS_TLS_ABI_SVR4)
extern void *	tlsByTaskLookup		(void * pTlsVar, TASK_ID tid);
#else
extern void *	tlsByTaskLookup		(struct __tls__var * pTlsVar,
					 TASK_ID tid);
#endif	/* _WRS_TLS_ABI_SVR4 */

#ifdef	_WRS_KERNEL
extern void	tlsLibInit		(void * tlsVarsAddr,
					 UINT32 tlsVarsSize,
					 void * tlsDataAddr,
					 UINT32 tlsDataSize,
					 UINT32 tlsDataAlignment);

extern void	tlsLoadLibInit		(void);

#ifdef  _WRS_CONFIG_LOADER
extern void 	tlsModuleAdd		(void * moduleId, void * tlsVarsAddr,
					 UINT32 tlsVarsSize, 
					 void * tlsDataAddr, UINT32 tlsDataSize,
					 UINT32 tlsDataAlignment);
extern void	tlsModuleRemove		(void * moduleId);
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
