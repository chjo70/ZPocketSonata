/*
 * Copyright (c) 2006-2013, 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
#ifndef IPCOM_ATOMIC_H
#define IPCOM_ATOMIC_H

/*
modification history
--------------------
09mar16,wjf Fix compiler and static analysis warnings
*/

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */

/*
DESCRIPTION
API for IPCOM atomic types
*/

/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

#include "ipcom_config.h"

/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#include "ipcom_os.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/*
 * The size of type is very dependent on the architecture
 */
typedef struct { int val; } Ipcom_atomic_t;

#if !defined(IPCOM_USE_ATOMIC_MACROS) && defined(__GNUC__)
#define IPCOM_USE_ATOMIC_MACROS
#endif

#if defined(__GNUC__) && defined(IPARCH_arm)
#define IPCOM_USE_ATOMIC_GENERIC_CODE
#undef IPCOM_USE_ATOMIC_MACROS
#endif
#ifdef IPCOM_USE_ATOMIC_MACROS
/*
 * These macros works fine with the generic IPCOM implementation
 * <IPCOM>/port/src/ipcom_atomic.c
 */
# define ipcom_atomic_inc(v)               ipcom_atomic_add(v, 1)
# define ipcom_atomic_dec(v)               ipcom_atomic_add(v, -1)
# define ipcom_atomic_sub(v, i)            ipcom_atomic_add(v, -(i))
# define ipcom_atomic_sub_and_return(v, i) ipcom_atomic_add_and_return(v, -(i))
# define ipcom_atomic_or(v, i)      ((void)ipcom_atomic_get_and_or(v, i))
# define ipcom_atomic_and(v, i)     ((void)ipcom_atomic_get_and_and(v, i))
#endif /* IPCOM_USE_ATOMIC_MACROS */

/*
 ****************************************************************************
 * 6                 PUBLIC FUNCTIONS
 ****************************************************************************
 */

/*******************************************************************************
 *
 * ipcom_atomic_get - get a value
 *
 * This routine get a value from a atomic variable.
 *
 * Parameters:
 * \is
 * \i <v>
 * Pointer to an atmomic variable
 * \ie
 *
 * RETURNS: The value of the atomic type
 *
 * ERRNO: None.
 */
#if defined(__GNUC__) && !defined(IPCOM_USE_ATOMIC_GENERIC_CODE)
#define ipcom_atomic_get(v) (v)->val
#else
IP_PUBLIC int ipcom_atomic_get
(
     Ipcom_atomic_t *v
);
#endif


/*******************************************************************************
 *
 * ipcom_atomic_set - set a value
 *
 * This routine sets an atomic variable to a value
 *
 * Parameters:
 * \is
 * \i <v>
 * Pointer to an atmomic variable
 * \i <i>
 * Value to set
 * \ie
 *
 * RETURNS: \&N/A.
 *
 * ERRNO: None.
 */
#if defined(__GNUC__) && !defined(IPCOM_USE_ATOMIC_GENERIC_CODE)
#define ipcom_atomic_set(v, i)   (v)->val = i
#else
IP_PUBLIC void ipcom_atomic_set
(
     Ipcom_atomic_t *v,
     int             i
);
#endif


/*******************************************************************************
 *
 * ipcom_atomic_ptr_cas - replace one pointer-width value with another
 *
 * This routine atomically compares the value pointed to by the first argument
 * with the second argument and replaces the value pointed to by the
 * first argument with the third argument if the comparison matches.
 *
 * Parameters:
 * \is
 * \i <v>
 * Pointer to a memory area large enough to hold a pointer
 * \i <old_v>
 * Expected value pointed to by the first argument.
 * \i <new_v>
 * New value if the swap is successful.
 * \ie
 *
 * NOTE: Use ipcom_atomic_cas() instead for a version that works specifically
 * with 32-bit quantities.
 *
 * RETURNS: IP_TRUE if the swap took place, IP_FALSE otherwise.
 * ERRNO: None.
 */
#if defined(__GNUC__) && !defined(IPCOM_USE_ATOMIC_GENERIC_CODE)
IP_INLINE Ip_bool
ipcom_atomic_ptr_cas
(
    Ip_ptrdiff_t *v,
    Ip_ptrdiff_t  old_v,
    Ip_ptrdiff_t  new_v
)
{
    return __sync_bool_compare_and_swap(v, old_v, new_v);
}
#else
IP_PUBLIC Ip_bool ipcom_atomic_ptr_cas
(
    Ip_ptrdiff_t *v,
    Ip_ptrdiff_t  old_v,
    Ip_ptrdiff_t  new_v
);
#endif

/*******************************************************************************
 *
 * ipcom_atomic_cas - replace one 32-bit value atomically with another
 *
 * This routine atomically compares the value pointed to by the first argument
 * with the second argument and replaces the value pointed to by the
 * first argument with the third argument if the comparison matches.
 *
 * Parameters:
 * \is
 * \i <v>
 * Pointer to a 32-bit memory area
 * \i <old_v>
 * Expected value pointed to by the first argument.
 * \i <new_v>
 * New value if the swap is successful.
 * \ie
 *
 * NOTE: Use ipcom_atomic_ptr_cas() instead for a version that works
 * specifically with pointer-width quantities.
 *
 * RETURNS: IP_TRUE if the swap took place, IP_FALSE otherwise.
 * ERRNO: None.
 */
#if defined(__GNUC__) && !defined(IPCOM_USE_ATOMIC_GENERIC_CODE)
IP_INLINE Ip_bool
ipcom_atomic_cas
(
    Ipcom_atomic_t  *v,
    int              old_v,
    int              new_v
)
{
    return __sync_bool_compare_and_swap(&v->val, old_v, new_v);
}
#else
IP_PUBLIC Ip_bool ipcom_atomic_cas
(
    Ipcom_atomic_t  *v,
    int              old_v,
    int              new_v
);
#endif


/*******************************************************************************
 *
 * ipcom_atomic_add - add an integer
 *
 * This routine adds an integer to an atomic type
 *
 * Parameters:
 * \is
 * \i <v>
 * Pointer to an atomic variable
 * \i <i>
 * Value to add
 * \ie
 *
 * RETURNS: \&N/A.
 *
 * ERRNO: None.
 */
#if defined(__GNUC__) && !defined(IPCOM_USE_ATOMIC_GENERIC_CODE)
#define ipcom_atomic_add(v,i) (void)__sync_add_and_fetch(&(v)->val, i)
#else
IP_PUBLIC void ipcom_atomic_add
(
     Ipcom_atomic_t *v,
     int             i
);
#endif


/*******************************************************************************
 *
 * ipcom_atomic_add_and_return - add an integer and returns the result
 *
 * This routine adds an integer to an atomic type and returns the result
 *
 * Parameters:
 * \is
 * \i <v>
 * Pointer to an atomic variable
 * \i <i>
 * Value to add
 * \ie
 *
 * RETURNS: The result
 *
 * ERRNO: None.
 */
#if defined(__GNUC__) && !defined(IPCOM_USE_ATOMIC_GENERIC_CODE)
#define ipcom_atomic_add_and_return(v,i) __sync_add_and_fetch(&(v)->val, i)
#else
IP_PUBLIC int ipcom_atomic_add_and_return
(
     Ipcom_atomic_t *v,
     int             i
);
#endif

/*******************************************************************************
 *
 * ipcom_atomic_get_and_or - atomic OR variable with a value, returning original value
 *
 * This routine performs an atomic bitwise OR of an atomic variable
 * with an integer value.  The atomic variable is updated with the result.
 * The value returned is the original value of the atomic variable before the
 * operation.
 *
 * Parameters:
 * \is
 * \i <v>
 * Pointer to an atomic variable
 * \i <i>
 * Value to bitwise OR with the atomic variable
 * \ie
 *
 * RETURNS: Original value of the atomic variable before the operation.
 *
 * ERRNO: None.
 */
#if defined(__GNUC__) && !defined(IPCOM_USE_ATOMIC_GENERIC_CODE)
#define ipcom_atomic_get_and_or(v,i) __sync_fetch_and_or(&(v)->val, i)
#else
IP_PUBLIC int ipcom_atomic_get_and_or
(
     Ipcom_atomic_t *v,
     int             i
);
#endif

/*******************************************************************************
 *
 * ipcom_atomic_get_and_and - atomic AND variable with a value, returning original value
 *
 * This routine performs an atomic bitwise AND of an atomic variable
 * with an integer value.  The atomic variable is updated with the result.
 * The value returned is the original value of the atomic variable before the
 * operation.
 *
 * Parameters:
 * \is
 * \i <v>
 * Pointer to an atomic variable
 * \i <i>
 * Value to bitwise AND with the atomic variable
 * \ie
 *
 * RETURNS: Original value of the atomic variable before the operation.
 *
 * ERRNO: None.
 */
#if defined(__GNUC__) && !defined(IPCOM_USE_ATOMIC_GENERIC_CODE)
#define ipcom_atomic_get_and_and(v,i) __sync_fetch_and_and(&(v)->val, i)
#else
IP_PUBLIC int ipcom_atomic_get_and_and
(
     Ipcom_atomic_t *v,
     int             i
);
#endif
#if !defined( __GNUC__) || defined (IPARCH_arm)
IP_PUBLIC void ipcom_atomic_and(Ipcom_atomic_t *v, int i);
#endif

#ifndef IPCOM_USE_ATOMIC_MACROS
/*******************************************************************************
 *
 * ipcom_atomic_inc - add one
 *
 * This routine add one to an atomic type
 *
 * Parameters:
 * \is
 * \i <v>
 * Pointer to an atomic variable
 * \ie
 *
 * RETURNS: \&N/A.
 *
 * ERRNO: None.
 */
IP_PUBLIC void ipcom_atomic_inc
(
     Ipcom_atomic_t *v
);


/*******************************************************************************
 *
 * ipcom_atomic_dec - subtract one
 *
 * This routine subtract one from an atomic type
 *
 * Parameters:
 * \is
 * \i <v>
 * Pointer to an atomic variable
 * \ie
 *
 * RETURNS: \&N/A.
 *
 * ERRNO: None.
 */
IP_PUBLIC void ipcom_atomic_dec
(
     Ipcom_atomic_t *v
);


/*******************************************************************************
 *
 * ipcom_atomic_sub - subtract an integer
 *
 * This routine subtract an integer from an atomic type
 *
 * Parameters:
 * \is
 * \i <v>
 * Pointer to an atomic variable
 * \i <i>
 * Value to subtract
 * \ie
 *
 * RETURNS: \&N/A.
 *
 * ERRNO: None.
 */
IP_PUBLIC void ipcom_atomic_sub
(
     Ipcom_atomic_t *v,
     int             i
);


/*******************************************************************************
 *
 * ipcom_atomic_sub_and_return - subtracts an integer and returns the result
 *
 * This routine subtracts an integer from an atomic type and returns the result
 *
 * Parameters:
 * \is
 * \i <v>
 * Pointer to an atomic variable
 * \i <i>
 * Value to subtract
 * \ie
 *
 * RETURNS: The result
 *
 * ERRNO: None.
 */
IP_PUBLIC int ipcom_atomic_sub_and_return
(
     Ipcom_atomic_t *v,
     int             i
);


/*******************************************************************************
 *
 * ipcom_atomic_or - bitwise OR an atomic variable with a value
 *
 * This routine performs an atomic bitwise OR of an atomic variable
 * with an integer value.  The atomic variable is updated with the result.
 *
 * Parameters:
 * \is
 * \i <v>
 * Pointer to an atomic variable
 * \i <i>
 * Value to bitwise OR with the atomic variable
 * \ie
 *
 * RETURNS: \&N/A.
 *
 * ERRNO: None.
 */
IP_PUBLIC void ipcom_atomic_or
(
     Ipcom_atomic_t *v,
     int             i
);

#endif /* !IPCOM_USE_ATOMIC_MACROS */

#ifdef __cplusplus
}
#endif

#endif /* IPCOM_ATOMIC_H */

/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */

