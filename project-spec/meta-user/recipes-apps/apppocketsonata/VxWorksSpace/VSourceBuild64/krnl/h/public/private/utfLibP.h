/* utfLibP.h - Unicode encoding function binding library header file */

/*
 * Copyright 2010 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01b,14sep10,jxu LP64: update the APIs for using type size_t intead of int.
01a,31aug10,jxu Create.
*/

#ifndef __INCutfLibP
#define __INCutfLibP

#ifdef __cplusplus
extern "C" {
#endif

extern ssize_t (*_func_utf8ToCP)
    (
    const unsigned char *  utf8,
    const size_t           length,
    unsigned long *        codePoint
    );

extern ssize_t (*_func_utf16ToCP)
    (
    const unsigned short *  utf16,
    const size_t            length,
    const int               littleEndian,
    unsigned long *         codePoint
    );

extern ssize_t (*_func_CPToUtf8)
    (
    const unsigned long  codePoint,
    unsigned char *      utf8,
    const size_t         length
    );

extern ssize_t (*_func_CPToUtf16)
    (
    const unsigned long  codePoint,
    unsigned short *     utf16,
    const size_t         length,
    const int            littleEndian
    );

extern size_t (*_func_utflen8)
    (
    const unsigned char *  utf8
    );

extern size_t (*_func_utflen16)
    (
    const unsigned short *  utf16
    );

extern ssize_t (*_func_proofUtf8String)
    (
    const unsigned char *  utf8
    );

extern ssize_t (*_func_utf8ToUtf16String)
    (
    const unsigned char *  utf8,
    unsigned short *       utf16,
    const size_t           len16,
    int                    littleEndian
    );

extern ssize_t (*_func_utf16ToUtf8String)
    (
    const unsigned short *  utf16,
    int                     littleEndian,
    unsigned char *         utf8,
    const size_t            len8
    );

extern ssize_t (*_func_utf8ToUtf16StringBOM)
    (
    const unsigned char *  utf8,
    unsigned short *       utf16,
    const size_t           len16,
    int                    littleEndian
    );

extern ssize_t (*_func_utf16ToUtf8StringBOM)
    (
    const unsigned short *  utf16,
    unsigned char *         utf8,
    const size_t            len8
    );

#ifdef __cplusplus
}
#endif

#endif

