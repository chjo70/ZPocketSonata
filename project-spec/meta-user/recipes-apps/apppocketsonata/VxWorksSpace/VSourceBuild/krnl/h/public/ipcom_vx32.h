/*
 * Copyright (c) 2006-2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
 modification history
 --------------------
*/

#ifndef IPCOM_VX32_H
#define IPCOM_VX32_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 * Interpeak VxWorks 32-bit compatibility macros.
 */


/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#ifdef __cplusplus
extern "C" {
#endif


/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

#if defined(IP_PORT_VXWORKS)
# define IPCOM_VX32_VER  IP_PORT_VXWORKS
#else
# include <version.h>
# if defined(RUNTIME_64BIT_NAME)
#  define IPCOM_VX32_VER  69
# elif defined(_WRS_VXWORKS_MAJOR) && defined(_WRS_VXWORKS_MINOR)
#  define IPCOM_VX32_VER  ((10 * _WRS_VXWORKS_MAJOR) + _WRS_VXWORKS_MINOR)
# endif
#endif

#if !defined(IPCOM_VX32_VER)
# error Cannot determine VxWorks version, please set IPCOM_VX32_VER
#endif

#if IPCOM_VX32_VER < 69

# if !defined(DRV_CREATE_PTR)
#  define DRV_CREATE_PTR FUNCPTR
# endif
# if !defined(DRV_REMOVE_PTR)
#  define DRV_REMOVE_PTR FUNCPTR
# endif
# if !defined(DRV_OPEN_PTR)
#  define DRV_OPEN_PTR   FUNCPTR
# endif
# if !defined(DRV_CLOSE_PTR)
#  define DRV_CLOSE_PTR  FUNCPTR
# endif
# if !defined(DRV_READ_PTR)
#  define DRV_READ_PTR   FUNCPTR
# endif
# if !defined(DRV_WRITE_PTR)
#  define DRV_WRITE_PTR  FUNCPTR
# endif
# if !defined(DRV_IOCTL_PTR)
#  define DRV_IOCTL_PTR  FUNCPTR
# endif
# if !defined(vxAtomic32Get)
#  define vxAtomic32Get  vxAtomicGet
# endif
# if !defined(vxAtomic32Set)
#  define vxAtomic32Set  vxAtomicSet
# endif
# if !defined(vxAtomic32Inc)
#  define vxAtomic32Inc  vxAtomicInc
# endif
# if !defined(vxAtomic32Dec)
#  define vxAtomic32Dec  vxAtomicDec
# endif
# if !defined(vxAtomic32Add)
#  define vxAtomic32Add  vxAtomicAdd
# endif
# if !defined(vxAtomic32Sub)
#  define vxAtomic32Sub  vxAtomicSub
# endif
# if !defined(vxAtomic32Cas)
#  define vxAtomic32Cas  vxAtomicCas
# endif
# if !defined(vxAtomicCas)
#  define vxAtomicCas  vxCas
# endif
# if !defined(atomic32_t)
#  define atomic32_t     atomic_t
# endif
# if !defined(SOCK_LIB_INIT_RTN)
# define SOCK_LIB_INIT_RTN FUNCPTR
# endif
# if !defined(SYM_VALUE)
#  define SYM_VALUE      void *
# endif
# if !defined(VXB_METHOD_ID)
#  define VXB_METHOD_ID  unsigned int
# endif
# if !defined(WD_RTN)
#  define WD_RTN         void *
# endif

# if !defined(IP_INT_SIZET)
#  define IP_INT_SIZET   int
# endif
# if !defined(IP_INT_VOIDP)
#  define IP_INT_VOIDP   int
# endif
# if !defined(IP_SEM_ID)
#  define IP_SEM_ID      int
# endif
# if !defined(IP_TASK_ID)
#  define IP_TASK_ID     int
# endif

#if !defined(TASK_ID_ERROR)
# define TASK_ID_ERROR   ((TASK_ID)(-1))
#endif

#elif defined(_WRS_KERNEL)

# if !defined(IP_INT_SIZET)
#  define IP_INT_SIZET   size_t
# endif
# if !defined(IP_INT_VOIDP)
#  define IP_INT_VOIDP   void *
# endif
# if !defined(IP_SEM_ID)
#  define IP_SEM_ID      SEM_ID
# endif
# if !defined(IP_TASK_ID)
#  define IP_TASK_ID     TASK_ID
# endif

#else

# if !defined(IP_INT_SIZET)
#  define IP_INT_SIZET   int
# endif
# if !defined(IP_INT_VOIDP)
#  define IP_INT_VOIDP   int
# endif
# if !defined(IP_SEM_ID)
#  define IP_SEM_ID      int
# endif
# if !defined(IP_TASK_ID)
#  define IP_TASK_ID     int
# endif

#endif

#ifdef __cplusplus
}
#endif

#endif

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
