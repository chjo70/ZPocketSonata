/* rngLib.h - ring buffer subroutine library header */

/*
 * Copyright (c) 1984, 1987-1988, 1990-1992, 2004, 2009, 2015-2016
 * Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
20may16,dlk  Fix build warning from unused/uninitialized temp variable passed
             to RNG_ELEM_PUT() and RNG_ELEM_GET().
23feb15,pad  Recoded RNG_ELEM_PUT and RNG_ELEM_GET as inline functions (CERT)
14apr09,jpb  Updated for LP64 support.
22oct04,aeg  removed rngCreateKernel() and rngDeleteKernel() (SPR #102956)
23mar04,job  Removed special handling of STDC for function prototypes
20jan04,dat  Adding rngCreateKernel for 88437
22sep92,rrr  added support for c++
04jul92,jcf  cleaned up.
26may92,rrr  the tree shuffle
04oct91,rrr  passed through the ansification filter
               -changed VOID to void
               -changed copyright notice
06apr91,gae  added NOMANUAL to avoid fooling mangen.
05oct90,shl  added ANSI function prototypes.
             made #endif ANSI style.
             added copyright notice.
10aug90,dnw  added declaration of rngFlush().
07aug90,shl  moved function declarations to end of file.
22aug88,gae  removed incorrect comment about using 'shorts' for optimization.
30may88,dnw  changed to v4 names.
10nov87,dnw  changed ring pointers from shorts to ints.
             rings can now be > 32K bytes.
15aug84,dnw  removed several macros, now routines in rngLib.cs;
             only rngGetC and rngPutC remain as macros.
06jun84,dnw  culled from old drvLib.h
*/

/*
 * Note: This file contains definitions that must be maintained in both kernel
 * and user space
 */

#ifndef __INCrngLibh
#define __INCrngLibh

#include <base/b_BOOL.h>        /* for BOOL */
#include <base/b_size_t.h>      /* for size_t */

#ifdef __cplusplus
extern "C" {
#endif


/* HIDDEN */

/* typedefs */

typedef struct		/* RING - ring buffer */
    {
    size_t pToBuf;      /* offset from start of buffer where to write next */
    size_t pFromBuf;	/* offset from start of buffer where to read next */
    size_t bufSize;	/* size of ring in bytes */
    char *buf;		/* pointer to start of buffer */
    } RING;

/* END_HIDDEN */

typedef RING *RING_ID;


/*
 * The following macros are designed to do various operations on
 * the RING object.  By using them, users can avoid having to know
 * the structure of RING.  However they are intended to be very
 * efficient and this is why they are macros in the first place.
 * In general the parameters to them should be register variables
 * for maximum efficiency.
 */

/*******************************************************************************
*
* RNG_ELEM_GET - get one character from a ring buffer
*
* This macro gets a single character from the specified ring buffer.
* Must be supplied with a temporary variable (register size_t) 'fromP'.
*
* NOTE: The temporary 'fromP' variable is only present for backwards
* compatibility. It is not used when RNG_ELEM_GET() is defined in
* terms of rngElemGet_inline().
*
* RETURNS: 1 if there was a char in the buffer to return, 0 otherwise
* \NOMANUAL
*/

#define RNG_ELEM_GET(ringId, pCh, fromP) \
    ((void)fromP, rngElemGet_inline ((ringId), (pCh)))

_WRS_INLINE size_t rngElemGet_inline
    (
    RING_ID ringId,
    char *  pCh
    )
    {
    size_t  fromP = ringId->pFromBuf;

    if (ringId->pToBuf == fromP)
        {
        return 0;
        }

    *pCh = ringId->buf[fromP];
    if (++fromP == ringId->bufSize)
        {
        ringId->pFromBuf = 0;
        }
    else
        {
        ringId->pFromBuf = fromP;
        }

    return 1;
    }

/*******************************************************************************
*
* RNG_ELEM_PUT - put one character into a ring buffer
*
* This macro puts a single character into the specified ring buffer.
* Must be supplied with a temporary variable (register size_t) 'toP'.
*
* NOTE: The temporary 'toP' variable is only present for backwards
* compatibility. It is not used when RNG_ELEM_PUT() is defined in
* terms of rngElemPut_inline().
*
* RETURNS: 1 if there was room in the buffer for the char, 0 otherwise
* \NOMANUAL
*/

#define RNG_ELEM_PUT(ringId, ch, toP) \
    ((void)toP, rngElemPut_inline ((ringId), (ch)))

_WRS_INLINE size_t rngElemPut_inline
    (
    RING_ID ringId,
    char    ch
    )
    {
    size_t toP = ringId->pToBuf;

    if (toP == (ringId->pFromBuf - 1))
        {
        return 0;
        }

    if (toP == (ringId->bufSize - 1))
        {
        if (ringId->pFromBuf == 0)
            {
            return 0;
            }
        else
            {
            ringId->buf[toP] = ch;
            ringId->pToBuf = 0;
            return 1;
            }
        }
    else
        {
        ringId->buf[toP] = ch;
        ringId->pToBuf++;
        return 1;
        }
    }

/* function declarations */

extern BOOL 	rngIsEmpty (RING_ID ringId);
extern BOOL 	rngIsFull (RING_ID ringId);
extern RING_ID 	rngCreate (size_t nbytes);
extern size_t 	rngBufGet (RING_ID rngId, char *buffer, size_t maxbytes);
extern size_t 	rngBufPut (RING_ID rngId, char *buffer, size_t nbytes);
extern size_t 	rngFreeBytes (RING_ID ringId);
extern size_t 	rngNBytes (RING_ID ringId);
extern void 	rngDelete (RING_ID ringId);
extern void 	rngFlush (RING_ID ringId);
extern void 	rngMoveAhead (RING_ID ringId, size_t n);
extern void 	rngPutAhead (RING_ID ringId, char byte, size_t offset);

#ifdef __cplusplus
}
#endif

#endif /* __INCrngLibh */
