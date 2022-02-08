/* utfLib.h - Unicode encoding library header file */

/*
 * Copyright 2004 - 2006, 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01d,10sep10,jxu  LP64: update some API for using size_t instead of int.
01c,28apr10,jxu  added prototype proofUtf8
01b,07jul06,pcm  added utfLibInit().
01a,22mar04,rfr  written.
*/

#ifndef __INCutfLib
#define __INCutfLib

#ifdef __cplusplus
extern "C" {
#endif

/* Constants */
#define	UTF16_TO_8_MULT	3	/* UTF-16 string of length N (2N bytes long)
				   can require up to 3N bytes in UTF-8 format,
				   always not including terminating '\0's */

/* Error Codes */

#define UC_BUFFER 	-1	/* Target buffer cannot hold result */
#define UC_FORMAT	-2	/* Source is in illegal format */
#define UC_NOSRC	-3	/* Insufficient source for legal conversion */

void utfLibInit (void);

ssize_t utf8ToCP(
   const unsigned char *utf8,
   const size_t length,
   unsigned long *codePoint);

ssize_t utf16ToCP(
   const unsigned short *utf16,
   const size_t length,		/* Length is in shorts */
   const int littleEndian,
   unsigned long *codePoint);

ssize_t CPToUtf8(
   const unsigned long codePoint,
   unsigned char *utf8,
   const size_t length);

ssize_t CPToUtf16(
   const unsigned long codePoint,
   unsigned short *utf16,
   const size_t length,		/* Length is in shorts */
   const int littleEndian);


size_t utflen8(const unsigned char *utf8);

size_t utflen16(const unsigned short *utf16);

ssize_t proofUtf8String(const unsigned char *utf8);

ssize_t proofUtf8
    (
    const unsigned char *  utf8,
    const size_t           length
    );

ssize_t utf8ToUtf16String(
    const unsigned char *utf8,
    unsigned short *utf16,
    const size_t len16,
    int littleEndian);

ssize_t utf16ToUtf8String(
    const unsigned short *utf16,
    int littleEndian,
    unsigned char *utf8,
    const size_t len8);

ssize_t utf8ToUtf16StringBOM(
    const unsigned char *utf8,
    unsigned short *utf16,
    const size_t len16,
    int littleEndian);

ssize_t utf16ToUtf8StringBOM(
    const unsigned short *utf16,
    unsigned char *utf8,
    const size_t len8);

#ifdef __cplusplus
}
#endif

#endif
