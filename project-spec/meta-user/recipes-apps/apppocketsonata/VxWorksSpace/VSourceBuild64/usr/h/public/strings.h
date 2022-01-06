/* strings.h - POSIX string library header file */

/*
 * Copyright (c) 2003-2006, 2009-2011, 2014 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */
                                                                                
/*
modification history
--------------------
06oct15,clt  Added back binvert() (V7SP-537)
15sep14,prk  Removed binvert for CERT build
11nov11,jpb  Updated bswap signature.
12oct11,jpb  Defect WIND00264730. Updated signatures.  Moved swab into 
             unistd.h
17may11,pad  Fixed incorrect definition of size_t by including
             base/b_size_t.h.
27jan09,pcs  Update to add support for LP64 data model.
25sep06,pad  Added protection around non-POSIX API declarations
             (defect #65336 / fix #66618).
30aug05,mcm  Fix for SPR#110897 - strings.h should not include string.h
16dec04,aeg  added various function prototypes (SPR #105335).
26feb03,mcm  Including string.h
06dec03,mcm  Fixed prototypes for bzero etc.
04nov03,pad  created
*/

/*
 ******************************************************************************
 *                               IMPORTANT NOTE
 *
 * This is a POSIX header file. Any changes to this file must be done with care
 * to maintain the POSIX conformance. Symbols (macros, types, parameter names,
 * etc.) must all follow the POSIX naming conventions (symbol names prefixed
 * with one underscore followed with an upper case letter, or two underscores
 * followed with a lower case letter).
 *
 * Ideally, NO VxWorks-native symbols should be defined here and NO VxWorks-
 * native header files should be included in this header file. If it turns
 * impractical to avoid using VxWorks-native elements then make sure to use the
 * following exclusion logic around the offending elements:
 *
 * #if !defined (_POSIX_C_SOURCE) && !defined (_XOPEN_SOURCE) && \
 *     !defined (_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
 * ...
 * #endif  /@ _POSIX_xxx_SOURCE @/
 *
 *****************************************************************************
 */

#ifndef __INCstringsh
#define __INCstringsh

#include <base/b_size_t.h>
#include <base/b_swab.h>	/* 
                                 * For backwards compatibility.  swab() was
                                 * originially defined in this file
                                 */ 

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_POSIX_C_SOURCE) && !defined(_XOPEN_SOURCE) && \
    !defined(_POSIX_AEP_RT_CONTROLLER_C_SOURCE)
extern void	binvert     (void *, size_t);
extern void	bswap	    (void *, void *, size_t);
extern void	uswab	    (const void *, void *, size_t);
extern void	bcopyBytes  (const void *, void *, size_t);
extern void	bcopyWords  (const void *, void *, size_t);
extern void	bcopyLongs  (const void *, void *, size_t);
#ifdef _WRS_CONFIG_LP64
extern void     bcopyQuads  (const void *, void *, size_t);
#endif /* _WRS_CONFIG_LP64 */
extern void 	bfill	    (void *, size_t, int);
extern void	bfillBytes  (void *, size_t, int);
#endif  /* _POSIX_xxx_SOURCE */

extern int 	bcmp	    (const void *, const void *, size_t);
extern void 	bcopy	    (const void *, void *, size_t);
extern void 	bzero	    (void *, size_t); 
extern char *	index       (const char *, int);
extern char *	rindex      (const char *, int);

extern int      strcasecmp (const char *, const char *);
extern int      strncasecmp (const char *, const char *, size_t);

#if FALSE /* XXX PAD - not supported yet */
extern int	ffs (int);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __INCstringah */
