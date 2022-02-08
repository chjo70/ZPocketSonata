/* ppcDecoratedLoadStore.h - Freescale P4080 Decorated load and Store header */

/*
 * Copyright (c) 2009 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01b,03dec09,rab  fix decorated_store_32_inc_acc_32 macro and cleanup
01a,20aug09,rab  written
*/

#ifndef __INppcDecoratedLoadStoreh
#define __INppcDecoratedLoadStoreh

#ifdef __cplusplus
extern "C" {
#endif
#ifndef _ASMLANGUAGE

/* Decorated load instructions */

#define LOAD_DECORATION_CLEAR       0
#define LOAD_DECORATION_SET         1
#define LOAD_DECORATION_DEC         2
#define LOAD_DECORATION_INC         3

#if defined (__DCC__)

/* Decorated load. Decoration = Read-clear. Returns 32 bit value */

__asm ulong_t decorated_load_clear_32(volatile void *addr)
{
! "r3", "r4"
% reg addr;
    li      r4, LOAD_DECORATION_CLEAR
    lwdx    r3, r4, addr
}

/* Decorated load. Decoration = Read-set. Returns 32 bit value */

__asm ulong_t decorated_load_set_32(volatile void *addr)
{
! "r3", "r4"
% reg addr;
    li      r4, LOAD_DECORATION_SET
    lwdx    r3, r4, addr
}

/* Decorated load. Decoration = Read-dec. Returns 32 bit value */

__asm ulong_t decorated_load_dec_32(volatile void *addr)
{
! "r3", "r4"
% reg addr;
    li      r4, LOAD_DECORATION_DEC
    lwdx    r3, r4, addr
}

/* Decorated load. Decoration = Read-inc. Returns 32 bit value */

__asm ulong_t decorated_load_inc_32(volatile void *addr)
{
! "r3", "r4"
% reg addr;
    li      r4, LOAD_DECORATION_INC
    lwdx    r3, r4, addr
}

#elif	defined (__GNUC__)

/* Decorated load. Decoration = Read-clear. Returns 32 bit value */

static __inline__ ulong_t decorated_load_clear_32(volatile void *addr)
    {
	ulong_t r;
	enum LOAD_DECORATION dec = LOAD_DECORATION_CLEAR;
	__asm__
    (
    "lwdx    %0, %1, %2"
	: "=r" (r)
	: "r" (dec),
	"r" (addr)
	: "memory"
	);
	return r;
    }

/* Decorated load. Decoration = Read-set. Returns 32 bit value */

static __inline__ ulong_t decorated_load_set_32(volatile void *addr)
{
	ulong_t r;
	enum LOAD_DECORATION dec = LOAD_DECORATION_SET;
	__ASM(
		"lwdx    %0, %1, %2"
		: "=r" (r)
		: "r" (dec),
		  "r" (addr)
		: "memory"
	);
	return r;
}

/* Decorated load. Decoration = Read-dec. Returns 32 bit value */

static inline ulong_t decorated_load_dec_32(volatile void *addr)
{
	ulong_t r;
	enum LOAD_DECORATION dec = LOAD_DECORATION_DEC;
	__ASM(
		"lwdx    %0, %1, %2"
		: "=r" (r)
		: "r" (dec),
		  "r" (addr)
		: "memory"
	);
	return r;
}

/* Decorated load. Decoration = Read-inc. Returns 32 bit value */

static inline ulong_t decorated_load_inc_32(volatile void *addr)
{
	ulong_t r;
	enum LOAD_DECORATION dec = LOAD_DECORATION_INC;
	__ASM(
		"lwdx    %0, %1, %2"
		: "=r" (r)
		: "r" (dec),
		  "r" (addr)
		: "memory"
	);
	return r;
}

#endif /* __GNUC__ */

/* Decorated store instructions */

/*
 These decorated store functions utilize the decorated storage mechanism to
 atomically increment a particular 32-bit counter, and optionally
 simultaneously accumulate an associated 32-bit accumulator.  Both the
 accumulator and the counter must reside in the same aligned double-word.
 The accumulator must be in the most significant doubleword, and the counter
 is in the least significant doubleword.
  
 The decorated store transactions require the address operand to
 sometimes not point to the start of the structure they are updating,
 but to the value operand-LSB-aligned accumulator portion of the struture.
*/

#define STORE_DECORATION_ACC_64     0
#define STORE_DECORATION_ACC_32     1
#define STORE_DECORATION_INC_ACC_64 2
#define STORE_DECORATION_INC_ACC_32 3

#if defined (__DCC__)

/* Decorated store. Decoration = Write-accumulate. 32 bit accumulator update,
   32 bit argument */

__asm void decorated_store_32_acc_32(volatile void *addr, register ulong_t v)
{
! "r4"
% reg addr; reg v;
    li      r4, STORE_DECORATION_ACC_32
    stwdx   v, r4, addr
}

/* Decorated store. Decoration = Write-accumulator increment and update. 32 bit
   accumulator update, 32 bit argument 
*/

__asm void decorated_store_32_inc_acc_32(volatile void *addr, register ulong_t v)
{
! "r3", "r4"
% reg addr; reg v;
    mr      r3, addr
    addi    r3, r3, 4        /* point to the accumulator */
    li      r4, STORE_DECORATION_INC_ACC_32
    stwdx   v, r4, r3
}

#elif	defined (__GNUC__)

/* Decorated store. Decoration = Write-accumulate. 32 bit accumulator update,
   32 bit argument */

static inline void decorated_store_32_acc_32(volatile void *addr,
register uint32_t v)
{
	volatile void * address = addr;
	enum STORE_DECORATION dec = STORE_DECORATION_ACC_32;
	__ASM(
		"stwdx    %0, %1, %2"
		:
		: "r" (v),
		  "r" (dec),
		  "r" (address)
		: "memory"
	);
}

/* Decorated store. Decoration = Write-accumulator increment and update. 32 bit
   accumulator update, 32 bit argument */

static inline void decorated_store_32_inc_acc_32(volatile void *addr,
register uint32_t v)
{
	volatile void * address = (void *)((uintptr_t)addr + 4);
	enum STORE_DECORATION dec = STORE_DECORATION_INC_ACC_32;
	__ASM(
		"stwdx    %0, %1, %2"
		:
		: "r" (v),
		  "r" (dec),
		  "r" (address)
		: "memory"
	);
}

#endif /* __GNUC__ */

/* Decorated notify instructions */

#define NOTIFY_DECORATION_INC_64    0
#define NOTIFY_DECORATION_INC_32    1
#define NOTIFY_DECORATION_CLEAR_64  2
#define NOTIFY_DECORATION_CLEAR_32  3

#if defined (__DCC__)

/* Decorated notify. Decoration = increment. 32 bit accumulator */

__asm void decorated_notify_inc_32(volatile void *addr)
{
! "r4"
% reg addr;
    li      r4, NOTIFY_DECORATION_INC_32
    dsn     r4, addr
}

/* Decorated notify. Decoration = increment. 32 bit accumulator */

__asm void decorated_notify_clear_32(volatile void *addr)
{
! "r4"
% reg addr;
    li      r4, NOTIFY_DECORATION_CLEAR_32
    dsn     r4, addr
}

#elif	defined (__GNUC__)

/* Decorated notify. Decoration = increment. 32 bit accumulator */

static inline void decorated_notify_inc_32(volatile void *addr)
{
	register enum STORE_DECORATION dec = NOTIFY_DECORATION_INC_32;
	__ASM(
		"dsn    %0, %1"
		:
		: "r" (dec),
		  "r" (addr)
		: "memory"
	);
}

/* Decorated notify. Decoration = clear. 32 bit accumulator */

static inline void decorated_notify_clear_32(volatile void *addr)
{
	register enum STORE_DECORATION dec = NOTIFY_DECORATION_CLEAR_32;
	__ASM(
		"dsn    %0, %1"
		:
		: "r" (dec),
		  "r" (addr)
		: "memory"
	);
}

#endif /* __GNUC__ */

#endif /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INppcDecoratedLoadStoreh */
