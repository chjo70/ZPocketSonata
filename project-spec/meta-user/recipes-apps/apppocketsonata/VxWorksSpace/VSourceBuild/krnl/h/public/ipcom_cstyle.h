/*
 * Copyright (c) 2006-2013, 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
19aug15,dlk  Fix C++ build errors due to implicit casts (V7NET-672).
*/

#ifndef IPCOM_CSTYLE_H
#define IPCOM_CSTYLE_H

/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
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

#include "ipcom_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/*
 *===========================================================================
 *            must define IP_LITTLE_ENDIAN or IP_BIG_ENDIAN
 *===========================================================================
 */

/* Define endianness if it has not been */
#if defined(IP_PORT_VXWORKS) && !defined(IP_LITTLE_ENDIAN) && !defined(IP_BIG_ENDIAN)
#include <vxWorks.h>
#if (_BYTE_ORDER == _LITTLE_ENDIAN )
#define IP_LITTLE_ENDIAN
#elif (_BYTE_ORDER == _BIG_ENDIAN )
#define IP_BIG_ENDIAN
#endif
#endif /* defined(IP_PORT_VXWORKS && !defined(IP_LITTLE_ENDIAN) && !defined(IP_BIG_ENDIAN) */

#ifndef _shroud
#if !defined(IP_LITTLE_ENDIAN) && !defined(IP_BIG_ENDIAN)
#error must_define_IP_LITTLE_ENDIAN_or_IP_BIG_ENDIAN
#endif
#endif


/*
 *===========================================================================
 *                         scope
 *===========================================================================
 */

/* API functions */
#define IP_PUBLIC

/* Functions used by multiple files in a product. */
#ifndef IP_GLOBAL
#define IP_GLOBAL
#endif

/* static functions */
#define IP_STATIC   static

/* static inline */
#if defined(__GNUC__) || defined(__DCC__)
#define IP_INLINE static __inline__
#else
#define IP_INLINE static
#endif

/* external keyword */
#define IP_EXTERN   extern


/*
 *===========================================================================
 *                         IP_CONST
 *===========================================================================
 */
#define IP_CONST  const


/*
 *===========================================================================
 *                         IP_PACKED
 *===========================================================================
 * Deprecated mechanism to inhibit compiler padding in structures. Please use
 * the ipcom_align16.h mechanism for new designs.
 */
#if defined(__GNUC__)
#define IP_PACKED /*__attribute__((packed))*/
#else
#define IP_PACKED
#endif

/*
 *===========================================================================
 *                         IP_ALIGNED
 *===========================================================================
 * Mark data needing large alignment (e.g. nominal CPU cache line alignment)
 */
#if defined(__GNUC__) || defined(_DIAB_TOOL)
#define IP_ALIGNED(x) __attribute__((aligned(x)))
#else
#define IP_ALIGNED(x)
#endif

/*
 *===========================================================================
 *                         IP_NOMINAL_CACHE_LINE
 *===========================================================================
 * Nominal cache line size in bytes. Used for compile-time alignment of
 * certain structures.
 */
#ifndef IP_NOMINAL_CACHE_LINE
#define IP_NOMINAL_CACHE_LINE 128
#endif

/*
 *===========================================================================
 *                       IPCOM_UNUSED_ARG
 *===========================================================================
 * Used to acknowledge that its OK for that argument to be unused within
 * the function
 */
#define IPCOM_UNUSED_ARG(x)  (void) x


/*
 *===========================================================================
 *                       IP_FLAG_FC_XXX
 *===========================================================================
 * Generic function call (FC) flags.
 */

/* Ok for function call to block (used when default is non-blocking) */
#define IP_FLAG_FC_BLOCKOK        0x1

/* Function call may not block (used when default is blocking) */
#define IP_FLAG_FC_NOBLOCK        0x2

/* Function is called from ISR (interrupt context). */
#define IP_FLAG_FC_ISRCONTEXT     0x4

/* Function is called from stack (IPNET/IPLITE) context and code-locked. */
#define IP_FLAG_FC_STACKCONTEXT   0x8

/* Function is called from unknown context, event must be rescheduled. */
#define IP_FLAG_FC_SAFECONTEXT    0x10

/* Allocate multiple packets, they will be chained through the 'next' pointer. */
#define IP_FLAG_FC_MULTIPLE       0x20


/*
 *===========================================================================
 *                         bit macros
 *===========================================================================
 */

#if defined(__GNUC__) || defined(__DCC__)
#define IP_TYPEOF(x)    __typeof(x)
#define IP_CAST(x)      (IP_TYPEOF(x))
#else
#define IP_TYPEOF(x)
#define IP_CAST(x)
#endif

#define IP_BIT_SET(xflag, xbit)      (void) ((xflag) = IP_CAST(xflag) ((xflag) | IP_CAST(xflag) (xbit)))
/* Bitwise operators are automatically promoted to INT  -- need cast before NOT */
#define IP_BIT_CLR(xflag, xbit)      (void) ((xflag) = IP_CAST(xflag) ((xflag) & ~(xbit)))
#define IP_BIT_ISSET(xflag, xbit)    ((xflag) & (IP_CAST(xflag) (xbit)))
#define IP_BIT_ARESET(xflag, xbits)  (IP_CAST(xflag) ((xflag) & (xbits)) == IP_CAST(xflag) (xbits))

#define IP_BIT_ISFALSE(xflag, xbit)  (!((xflag) & (xbit)))
#define IP_BIT_ISTRUE(xflag, xbit)   (!IP_BIT_ISFALSE(xflag, xbit))

#define IP_BIT_VAL(xbit)             (1 << (xbit))
#define IP_BIT_UVAL(xbit)            (1u << (xbit))
#define IP_BIT_GET(xmask,xbit)       (IP_BIT_ISSET((xmask),IP_BIT_VAL((xbit))) ? 1 : 0)
#define IP_BIT_VAL64(xbit)           (1ll << (xbit))
#define IP_BIT_UVAL64(xbit)          (1ull << (xbit))


/*
 *===========================================================================
 *                         comparisons/numbers
 *===========================================================================
 */

/* Maximum and minimum value. */
#define IP_MAX(xa,xb)        (((xa) > (xb)) ? (xa) : (xb))
#define IP_MIN(xa,xb)        (((xa) < (xb)) ? (xa) : (xb))

/* Absolute value, i.e. non-negative. */
#define IP_ABS(xa)           (((xa) < 0) ? (-(xa)) : (xa))

/* 'val' is rounded up to 'to' */
#define IP_ROUNDUP(val, to)  ((val) % (to) ? ((val) + (to)) - ((val) % (to)) : (val))


/*
 *===========================================================================
 *                         alignment
 *===========================================================================
 */

/* Align 'ptr' to 'align' size */
#define IP_PTR_ALIGN(ptr, align) \
  (void *)(((Ip_ptrdiff_t)(ptr) + (Ip_ptrdiff_t)(align) - 1) & ~((Ip_ptrdiff_t)(align) - 1))


/*
 *===========================================================================
 *                         C safety
 *===========================================================================
 */
#ifdef IPCOM_USE_ANDORNOT
#define AND    &&
#define OR     ||
#define NOT    !
#endif


/*
 *===========================================================================
 *                         ip_offsetof
 *===========================================================================
 */
#define ip_offsetof(xs,xm)      (Ip_size_t)(&(((xs *)0)->xm))

/*
 *===========================================================================
 *                         ip_ssizeof/ip_sizeof
 *===========================================================================
 */
#define ip_sizeof(t)            sizeof(t)
#define ip_ssizeof(t)           (Ip_ssize_t)ip_sizeof(t)



/*
 *===========================================================================
 *                         endian
 *===========================================================================
 */

/* IP_LITTLE_ENDIAN */
#if defined(IP_LITTLE_ENDIAN)
#define IP_SWAP32(xx)       ((((Ip_u32)(xx) << 24) & (Ip_u32)0xff000000U) | \
                             (((Ip_u32)(xx) <<  8) & (Ip_u32)0x00ff0000U) | \
                             (((Ip_u32)(xx) >>  8) & (Ip_u32)0x0000ff00U) | \
                             (((Ip_u32)(xx) >> 24) & (Ip_u32)0x000000ffU)) /*lint !e778 */
#define IP_SWAP16(xx)       (Ip_u16) (((((xx) << 8) & 0xff00) | (((xx) >> 8) & 0x00ff))) /*lint !e778 */

/* IP_BIG_ENDIAN = network endian. */
#elif defined(IP_BIG_ENDIAN)
#define IP_SWAP32(xx)       (xx)
#define IP_SWAP16(xx)       (xx)
#endif


/*
 *===========================================================================
 *                         weak ref
 *===========================================================================
 */

#ifdef __ARMCC_VERSION
#define IP_WEAK_REF(func) __weak func
#elif defined(__GNUC__)
#define IP_WEAK_REF(func) func __attribute__((weak))
#else
#define IP_WEAK_REF(func) func
#endif


/*
 *===========================================================================
 *                 Macros for 16-bit aligned 32 bit variables.
 *===========================================================================
 */

#ifdef IPCOM_32ON16_OK
#define IP_SET_32ON16(xxaddr, yyval)   *(Ip_u32 *)(xxaddr) = (yyval)
#define IP_GET_32ON16(xxaddr)          *(Ip_u32 *)(xxaddr)

#elif defined(IP_LITTLE_ENDIAN)
#if 0
#define IP_SET_32ON16(xxaddr, yyval) do { \
   Ip_u16 *tmp;\
   tmp = (Ip_u16 *)xxaddr;\
   *tmp = (Ip_u16)((yyval) & 0xffff);\
   ((Ip_u16 *)(xxaddr))[1] = (Ip_u16)(((yyval) >> 16) & 0xffff); \
} while((0))

#define IP_GET_32ON16(xxaddr) \
  ((Ip_u32)(((Ip_u32)((Ip_u16 *)(xxaddr))[1]) << 16 | \
            ((Ip_u32)((Ip_u16 *)(xxaddr))[0])))
#else

IP_INLINE void 
IP_SET_32ON16(void * xxaddr, int yyval)
{    
    Ip_u16 *xaddrT;

    xaddrT = (Ip_u16 *)xxaddr;
    xaddrT[0] = (Ip_u16)((yyval) & 0xffff);    
    xaddrT[1] = (Ip_u16)(((yyval) >> 16) & 0xffff);    
}

IP_INLINE Ip_u32 
IP_GET_32ON16(void * xxaddr)
{    
    Ip_u16 *xaddrT;

    xaddrT = (Ip_u16 *)xxaddr;
    return ((Ip_u32)xaddrT[1]) << 16 | ((Ip_u32)xaddrT[0]); 
}

#endif

#else /*IP_LITTLE_ENDIAN*/

#if 0
#define IP_SET_32ON16(xxaddr, yyval) do { \
   ((Ip_u16 *)(xxaddr))[0] = (Ip_u16)(((yyval) >> 16) & 0xffff); \
   ((Ip_u16 *)(xxaddr))[1] = (Ip_u16)((yyval) & 0xffff); \
} while((0))
#define IP_GET_32ON16(xxaddr) \
  ((Ip_u32)(((Ip_u32)((Ip_u16 *)(xxaddr))[0]) << 16 | \
            ((Ip_u32)((Ip_u16 *)(xxaddr))[1])))
#else
    
IP_INLINE void 
IP_SET_32ON16(void * xxaddr, int yyval)
{    
    Ip_u16 *xxaddrT;

    xxaddrT = (Ip_u16 *)xxaddr;
    xxaddrT[0] = (Ip_u16)(((yyval) >> 16) & 0xffff);    
    xxaddrT[1] = (Ip_u16)((yyval) & 0xffff);    
}

IP_INLINE Ip_u32 
IP_GET_32ON16(void * xxaddr)
{    
    Ip_u16 *xxaddrT;

    xxaddrT = (Ip_u16 *)xxaddr;
    return ((Ip_u32)xxaddrT[0]) << 16 | ((Ip_u32)xxaddrT[1]); 
}
    
#endif

#endif /*IP_LITTLE_ENDIAN*/



/*
 *===========================================================================
 *                 Macros for 8-bit aligned 32 bit variables.
 *===========================================================================
 */

#ifdef IPCOM_32ON8_OK
#define IP_SET_32ON8(xxaddr, yyval)   *(Ip_u32 *)(xxaddr) = (yyval)
#define IP_GET_32ON8(xxaddr)          *(Ip_u32 *)(xxaddr)

#elif defined(IP_LITTLE_ENDIAN)
#define IP_GET_32ON8(xxaddr) \
  ((Ip_u32)(((Ip_u32)((Ip_u8 *)(xxaddr))[3]) << 24 | \
            ((Ip_u32)((Ip_u8 *)(xxaddr))[2]) << 16 | \
            ((Ip_u32)((Ip_u8 *)(xxaddr))[1]) <<  8 | \
            ((Ip_u32)((Ip_u8 *)(xxaddr))[0])))
#define IP_SET_32ON8(xxaddr, yyval) do { \
   ((Ip_u8 *)(xxaddr))[0] = (Ip_u8) (((Ip_u32)(yyval)) & 0xff); \
   ((Ip_u8 *)(xxaddr))[1] = (Ip_u8)((((Ip_u32)(yyval)) >>  8) & 0xff); \
   ((Ip_u8 *)(xxaddr))[2] = (Ip_u8)((((Ip_u32)(yyval)) >> 16) & 0xff); \
   ((Ip_u8 *)(xxaddr))[3] = (Ip_u8)((((Ip_u32)(yyval)) >> 24) & 0xff); \
} while((0))
#else

#define IP_SET_32ON8(xxaddr, yyval) do { \
   ((Ip_u8 *)(xxaddr))[0] = (Ip_u8)((((Ip_u32)(yyval)) >> 24) & 0xff); \
   ((Ip_u8 *)(xxaddr))[1] = (Ip_u8)((((Ip_u32)(yyval)) >> 16) & 0xff); \
   ((Ip_u8 *)(xxaddr))[2] = (Ip_u8)((((Ip_u32)(yyval)) >>  8) & 0xff); \
   ((Ip_u8 *)(xxaddr))[3] = (Ip_u8) (((Ip_u32)(yyval)) & 0xff); \
} while((0))
#define IP_GET_32ON8(xxaddr) \
  ((Ip_u32)(((Ip_u32)((Ip_u8 *)(xxaddr))[0]) << 24 | \
            ((Ip_u32)((Ip_u8 *)(xxaddr))[1]) << 16 | \
            ((Ip_u32)((Ip_u8 *)(xxaddr))[2]) <<  8 | \
            ((Ip_u32)((Ip_u8 *)(xxaddr))[3])))
#endif


/*
 *===========================================================================
 *       Endian conversion macros for set/get 64-bit on any alignment
 *===========================================================================
 */

#define IP_SET_HTON64(xxaddr, yyval) do { \
   ((Ip_u8 *)(xxaddr))[0] = (Ip_u8)((((yyval)) >> 56) & 0xff); \
   ((Ip_u8 *)(xxaddr))[1] = (Ip_u8)((((yyval)) >> 48) & 0xff); \
   ((Ip_u8 *)(xxaddr))[2] = (Ip_u8)((((yyval)) >> 40) & 0xff); \
   ((Ip_u8 *)(xxaddr))[3] = (Ip_u8)((((yyval)) >> 32) & 0xff); \
   ((Ip_u8 *)(xxaddr))[4] = (Ip_u8)((((yyval)) >> 24) & 0xff); \
   ((Ip_u8 *)(xxaddr))[5] = (Ip_u8)((((yyval)) >> 16) & 0xff); \
   ((Ip_u8 *)(xxaddr))[6] = (Ip_u8)((((yyval)) >>  8) & 0xff); \
   ((Ip_u8 *)(xxaddr))[7] = (Ip_u8) (((yyval)) & 0xff); \
} while((0))
#define IP_SET_NTOH64(xxaddr, yyval) IP_SET_HTON64(xxaddr,yyval)

#define IP_GET_HTON64(xxaddr) \
  ((Ip_u64)(((Ip_u64)((Ip_u8 *)(xxaddr))[0]) << 56 | \
            ((Ip_u64)((Ip_u8 *)(xxaddr))[1]) << 48 | \
            ((Ip_u64)((Ip_u8 *)(xxaddr))[2]) << 40 | \
            ((Ip_u64)((Ip_u8 *)(xxaddr))[3]) << 32 | \
            ((Ip_u64)((Ip_u8 *)(xxaddr))[4]) << 24 | \
            ((Ip_u64)((Ip_u8 *)(xxaddr))[5]) << 16 | \
            ((Ip_u64)((Ip_u8 *)(xxaddr))[6]) << 8  | \
            ((Ip_u64)((Ip_u8 *)(xxaddr))[7])))
#define IP_GET_NTOH64(xxaddr)  IP_GET_HTON64(xxaddr)


/*
 *===========================================================================
 *       Endian conversion macros for set/get 32-bit on any alignment
 *===========================================================================
 */

#ifdef IPCOM_32ON8_OK
#define IP_SET_HTONL(xxaddr, yyval)  IP_SET_32ON8(xxaddr, IP_SWAP32(yyval))
#define IP_GET_HTONL(xxaddr)         IP_SWAP32(IP_GET_32ON8(xxaddr))

#else /* !IPCOM_32ON8_OK */
#define IP_SET_HTONL(xxaddr, yyval) do {                            \
       Ip_u32 yyvalT = (Ip_u32)yyval;                               \
       ((Ip_u8 *)(xxaddr))[0] = (Ip_u8)((((yyvalT)) >> 24) & 0xff); \
       ((Ip_u8 *)(xxaddr))[1] = (Ip_u8)((((yyvalT)) >> 16) & 0xff); \
       ((Ip_u8 *)(xxaddr))[2] = (Ip_u8)((((yyvalT)) >>  8) & 0xff); \
       ((Ip_u8 *)(xxaddr))[3] = (Ip_u8) (((yyvalT)) & 0xff); \
    } while((0))

#define IP_GET_HTONL(xxaddr) \
  ((Ip_u32)(((Ip_u32)((Ip_u8 *)(xxaddr))[0]) << 24 | \
            ((Ip_u32)((Ip_u8 *)(xxaddr))[1]) << 16 | \
            ((Ip_u32)((Ip_u8 *)(xxaddr))[2]) << 8  | \
            ((Ip_u32)((Ip_u8 *)(xxaddr))[3])))
#endif /* !IPCOM_32ON8_OK */

#define IP_SET_NTOHL(xxaddr, yyval) IP_SET_HTONL(xxaddr,yyval)
#define IP_GET_NTOHL(xxaddr)        IP_GET_HTONL(xxaddr)


/*
 *===========================================================================
 *       Endian conversion macros for set/get 16-bit on any alignment
 *===========================================================================
 */

#define IP_SET_HTONS(xxaddr, yyval) do {                            \
        ((Ip_u8 *)(xxaddr))[0] = (Ip_u8)(((yyval) >>  8) & 0xff);   \
        ((Ip_u8 *)(xxaddr))[1] = (Ip_u8)((yyval) & 0xff);           \
} while((0))
#define IP_SET_NTOHS(xxaddr, yyval) IP_SET_HTONS(xxaddr,yyval)

#define IP_GET_HTONS(xxaddr)                            \
    ((Ip_u16)(((Ip_u16)((Ip_u8 *)(xxaddr))[0]) << 8 |   \
              ((Ip_u16)((Ip_u8 *)(xxaddr))[1])))
#define IP_GET_NTOHS(xxaddr)   IP_GET_HTONS(xxaddr)


/*
 *===========================================================================
 *              Macros for accessing 8-bit vars stored in 16-bit
 *===========================================================================
 */
#ifdef IP_LITTLE_ENDIAN
#define IP_GET_16LO8(x)       (((x) >> 8) & 0xff)
#define IP_GET_16HI8(x)       ((x) & 0xff)
#define IP_SET_16LO8(x,val)   x = (Ip_u16)(((x & 0xff) | (val << 8)))
#define IP_SET_16HI8(x,val)   x = (Ip_u16)(((x & 0xff00) | (val & 0xff)))
#else
#define IP_GET_16LO8(x)       ((x) & 0xff)
#define IP_GET_16HI8(x)       (((x) >> 8) & 0xff)
#define IP_SET_16LO8(x,val)   x = (Ip_u16)(((x & 0xff00) | (val & 0xff)))
#define IP_SET_16HI8(x,val)   x = (Ip_u16)(((x & 0xff) | (val << 8)))
#endif /* IP_LITTLE_ENDIAN */

/*
 *===========================================================================
 *     Macros for constructing a 16-bit big-endian quantity from two bytes
 *===========================================================================
 */
#ifdef IP_LITTLE_ENDIAN
#define IP_TWO_BYTES(b1, b2)  ((Ip_u16)((b1) | ((b2) << 8)))
#else
#define IP_TWO_BYTES(b1, b2)  ((Ip_u16)(((b1) << 8) | (b2)))
#endif /* IP_LITTLE_ENDIAN */

#ifdef __cplusplus
#define IP_STATIC_CAST(ptrtype,ptrval) (static_cast<ptrtype>(ptrval))
#else
#define IP_STATIC_CAST(ptrtype,ptrval) ((ptrtype)(ptrval))
#endif

IP_INLINE Ip_u16
IP_U16_DEREF(void * pu16)
{
    Ip_u16 *p = IP_STATIC_CAST(Ip_u16 *, pu16);
    return *p;
}

IP_INLINE Ip_u32
IP_U32_DEREF(void * pu32)
{
    Ip_u32 *p = IP_STATIC_CAST(Ip_u32 *, pu32);
    return *p;
}

IP_INLINE void
IP_U16_STORE(void *pu16, Ip_u16 val)
{
    Ip_u16 *p = IP_STATIC_CAST(Ip_u16 *, pu16);
    *p = val;
}

IP_INLINE void
IP_U32_STORE(void *pu32, Ip_u32 val)
{
    Ip_u32 *p = IP_STATIC_CAST(Ip_u32 *, pu32);
    *p = val;
}

/*
 *===========================================================================
 *                         IPCOM debug printf's
 *===========================================================================
 */
#ifdef IP_DEBUG
#define IP_DBGPRINTF0(fm) \
  ipcom_debug_printf(fm)
#define IP_DBGPRINTF1(fm,a1) \
  ipcom_debug_printf(fm,a1)
#define IP_DBGPRINTF2(fm,a1,a2) \
  ipcom_debug_printf(fm,a1,a2)
#define IP_DBGPRINTF3(fm,a1,a2,a3) \
  ipcom_debug_printf(fm,a1,a2,a3)
#define IP_DBGPRINTF4(fm,a1,a2,a3,a4) \
  ipcom_debug_printf(fm,a1,a2,a3,a4)
#define IP_DBGPRINTF5(fm,a1,a2,a3,a4,a5) \
  ipcom_debug_printf(fm,a1,a2,a3,a4,a5)
#define IP_DBGPRINTF6(fm,a1,a2,a3,a4,a5,a6) \
  ipcom_debug_printf(fm,a1,a2,a3,a4,a5,a6)
#define IP_DBGPRINTF7(fm,a1,a2,a3,a4,a5,a6,a7) \
  ipcom_debug_printf(fm,a1,a2,a3,a4,a5,a6,a7)
#define IP_DBGPRINTF8(fm,a1,a2,a3,a4,a5,a6,a7,a8) \
  ipcom_debug_printf(fm,a1,a2,a3,a4,a5,a6,a7,a8)
#define IP_DBGPRINTF9(fm,a1,a2,a3,a4,a5,a6,a7,a8,a9) \
  ipcom_debug_printf(fm,a1,a2,a3,a4,a5,a6,a7,a8,a9)
#else
#define IP_DBGPRINTF0(fm)                            IP_NOOP
#define IP_DBGPRINTF1(fm,a1)                         IP_NOOP
#define IP_DBGPRINTF2(fm,a1,a2)                      IP_NOOP
#define IP_DBGPRINTF3(fm,a1,a2,a3)                   IP_NOOP
#define IP_DBGPRINTF4(fm,a1,a2,a3,a4)                IP_NOOP
#define IP_DBGPRINTF5(fm,a1,a2,a3,a4,a5)             IP_NOOP
#define IP_DBGPRINTF6(fm,a1,a2,a3,a4,a5,a6)          IP_NOOP
#define IP_DBGPRINTF7(fm,a1,a2,a3,a4,a5,a6,a7)       IP_NOOP
#define IP_DBGPRINTF8(fm,a1,a2,a3,a4,a5,a6,a7,a8)    IP_NOOP
#define IP_DBGPRINTF9(fm,a1,a2,a3,a4,a5,a6,a7,a8,a9) IP_NOOP
#endif


/*
 *===========================================================================
 *                         IP_DEBUGLINE
 *===========================================================================
 */
#ifdef IP_DEBUG
#define IP_DEBUGLINE(x)    x
#else
#define IP_DEBUGLINE(x)    IP_NOOP
#endif


/*
 *===========================================================================
 *                         __IP_LINESTR__
 *===========================================================================
 * Source code line as string:  __IP_LINESTR__
 */
#define __IP_LINESTR(line) #line
#define __IP_LINESTR_(line) __IP_LINESTR(line)

#define __IP_LINESTR__ __IP_LINESTR_(__LINE__)


/*
 *===========================================================================
 *                         BRANCH PREDICTION
 *===========================================================================
 * The vxWorks 5.4 and 5.5 compilers are gcc 2.96. gcc 2.96 does not
 * support __builtin*.
 * The vxWorks 6.0 compiler is gcc 3.3 and it supports these macros
 * Added (long) cast to quiet -Wconversion warnings
 */
#if __GNUC__ > 2
#define IP_LIKELY(pred)           __builtin_expect((long)!!(pred), 1L)
#define IP_UNLIKELY(pred)         __builtin_expect((long)!!(pred), 0L)
#define IP_PREPARE_FOR_READ(ptr)  __builtin_prefetch((const void *)(ptr))
#else
#define IP_LIKELY(pred)           (pred)
#define IP_UNLIKELY(pred)         (pred)
#define IP_PREPARE_FOR_READ(ptr)
#endif


/*
 *===========================================================================
 *                         SECTION OPTIMIZATIONS
 *===========================================================================
 */
#if defined(IP_PORT_VXWORKS) && IP_PORT_VXWORKS >= 63 && !defined(_WRS_NO_SPECIAL_SECTIONS) &&\
    (defined(__GNUC__) || defined(__DCC__))
#define IP_INITTEXT   __attribute__ ((__section__ (".text.init")))
#define IP_FASTTEXT   __attribute__ ((__section__ (".text.fast")))
#define IP_INITDATA   __attribute__ ((__section__ (".data.init")))
#define IP_FASTDATA   __attribute__ ((__section__ (".data.fast")))
#else
#define IP_INITTEXT
#define IP_FASTTEXT
#define IP_INITDATA
#define IP_FASTDATA
#endif


/*
 ****************************************************************************
 * 5                    GCC BOUNDSCHECKING
 ****************************************************************************
 * Unofficial non-supported GCC boundschecking utility macros.
 */

#if defined(IPBOUNDS) || defined(__BOUNDS_CHECKING_ON)

#ifndef _BOUNDS_DDEBUG_NO_CHECK_TYPE
#define _BOUNDS_DDEBUG_NO_CHECK_TYPE
extern int __bounds_debug_no_checking;
#endif

#define BOUNDS_CHECKING_OFF   __bounds_debug_no_checking = 1
#define BOUNDS_CHECKING_ON    __bounds_debug_no_checking = 0

#define BOUNDS_CHECKING_OFF_ISR  Ip_u32 isr; do { isr = ipcom_interrupt_disable(); __bounds_debug_no_checking = 1; } while((0))
#define BOUNDS_CHECKING_ON_ISR   do { ipcom_interrupt_enable(isr); __bounds_debug_no_checking = 0; } while((0))

#else
#define BOUNDS_CHECKING_OFF      IP_NOOP
#define BOUNDS_CHECKING_ON       IP_NOOP

#define BOUNDS_CHECKING_OFF_ISR  IP_NOOP
#define BOUNDS_CHECKING_ON_ISR   IP_NOOP
#endif


/*
 * Make a C string out of the definition of a pre-processor define.
 * Ex:
 * The defintion
 * #define A_INT_LITERAL 1234
 * will evaluate the string "1234" by IPCOM_MAKE_STR(A_INT_LITERAL)
 *
 * IPCOM_MAKE_STR_X() is just a helper and should never be used
 * directly.
 */
#define IPCOM_MAKE_STR(x)   IPCOM_MAKE_STR_X(x)
#define IPCOM_MAKE_STR_X(x) #x


/*
 ****************************************************************************
 * 6                    EXTERN PROTOTYPES
 ****************************************************************************
 */

IP_EXTERN const char *ipcom_version;

#ifdef __cplusplus
}
#endif

#endif


/*
 ****************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */
