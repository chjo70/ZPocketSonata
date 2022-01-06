/* string.h - string library header file */

/*
 * Copyright (c) 1992-1999, 2009-2011, 2014-2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
31mar16,rbo  Added memset_s
06oct15,clt  Added back binvert() (V7SP-537)
15sep14,prk  Removed binvert for CERT build
11nov11,jpb  Fixed conflicting type for bcopyQuads.
12oct11,jpb  Defect WIND00264730. Changed signature of bLib functions.
12may11,jpb  Added memmem function declaration.
29apr10,pad  Moved extern C statement after include statements.
11dec09,pcs  Add prototype for bcopyQuads a new API for 64bit VxWorks.
22jan09,pcs  Updated to add support for LP64 data model.
20sep04,ans  Added strdup()
10sep03,aim  added strlcat, strlcpy
00oct00,sn   Removed size_t typedef
17feb99,mrs  Add C++ support for NULL, (SPR #25079).
22sep92,rrr  added support for c++
14sep92,smb  added const to the prototype of bcopy.
07sep92,smb  removed macros for memcpy and memset.
30jul92,smb  added macros for memcpy and memset.
09jul92,smb  removed extra memmove declarations.
04jul92,jcf  cleaned up.
03jul92,smb  macro override for strerror added.
29jul91,rrr  written.
*/

#ifndef __INCstringh
#define __INCstringh

#include <vsbConfig.h>      /* to pull in macro _WRS_CONFIG_LP64 */
#include <types/vxANSI.h>
#include <base/b_swab.h>    /*
                             * For backwards compatibility.  swab() was
                             * originially defined in this file.
                             */

#include <base/b_rsize_t.h>
#include <base/b_errno_t.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NULL
#if defined __GNUG__
#define NULL (__null)
#else
#if !defined(__cplusplus) && 0
#define NULL ((void*)0)
#else
#define NULL (0)
#endif
#endif
#endif

extern void *	memchr (const void *__s, int __c, size_t __n);
extern int 	memcmp (const void *__s1, const void *__s2, size_t __n);
extern void *	memcpy (void *__s1, const void *__s2, size_t __n);
extern void *	memmove (void *__s1, const void *__s2, size_t __n);
extern void *	memset (void *__s, int __c, size_t __n);
extern errno_t  memset_s(void *dest, rsize_t destsz, int ch, rsize_t count);

extern char *	strcat (char *__s1, const char *__s2);
extern char *	strchr (const char *__s, int __c);
extern int 	strcmp (const char *__s1, const char *__s2);
extern int 	strcoll (const char *__s1, const char *__s2);
extern char *	strcpy (char *__s1, const char *__s2);
extern size_t 	strcspn (const char *__s1, const char *__s2);
extern char *   strdup (const char * str);
extern size_t 	strlen (const char *__s);
extern char *	strncat (char *__s1, const char *__s2, size_t __n);
extern int 	strncmp (const char *__s1, const char *__s2, size_t __n);
extern char *	strncpy (char *__s1, const char *__s2, size_t __n);
extern char *	strpbrk (const char *__s1, const char *__s2);
extern char *	strrchr (const char *__s, int __c);
extern size_t 	strspn (const char *__s1, const char *__s2);
extern char *	strstr (const char *__s1, const char *__s2);
extern char *	strtok (char *__s, const char *__sep);
extern size_t 	strxfrm (char *__s1, const char *__s2, size_t __n);
extern char *	strerror(int __errcode);

#if _EXTENSION_POSIX_REENTRANT		/* undef for ANSI */
extern char *	strtok_r (char *__s, const char *__sep, char **__ppLast);
#endif

#if _EXTENSION_WRS		 	/* undef for ANSI */
extern int	strerror_r (int __errcode, char *__buf);
extern void 	bcopy (const void *source, void *dest, size_t nbytes);
extern void 	bcopyBytes (const void *source, void *dest, size_t nbytes);
extern void 	bcopyWords (const void *source, void *dest, size_t nwords);
extern void 	bcopyLongs (const void *source, void *dest, size_t nlongs);
#ifdef _WRS_CONFIG_LP64
extern void 	bcopyQuads (const void *source, void *dest, size_t nquads);
#endif
extern void 	bfill (void *buf, size_t nbytes, int ch);
extern void 	bfillBytes (void *buf, size_t nbytes, int ch);
extern void 	bzero (void *buffer, size_t nbytes);
extern int 	bcmp (const void *buf1, const void *buf2, size_t nbytes);
extern void 	binvert (void *buf, size_t nbytes);
extern void 	bswap (void *buf1, void *buf2, size_t nbytes);
extern void 	uswab (const void *source, void *destination, size_t nbytes);
extern char *	index (const char *s, int c);
extern char *	rindex (const char *s, int c);
extern size_t	strlcat (char *dst, const char *src, size_t siz);
extern size_t   strlcpy (char *dst, const char *src, size_t siz);
extern void *   memmem (const void * haystack, size_t haystackLen,
                        const void * needle, size_t needleLen);
extern void *   memimem (const void * haystack, size_t haystackLen,
                         const void * needle, size_t needleLen);
#endif /* _EXTENSION_WRS */

#ifdef __cplusplus
}
#endif

#endif /* __INCstringh */
