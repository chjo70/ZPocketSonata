/* pathLib.h - path library header file */

/* Copyright 1984-2003, 2010, 2016 Wind River Systems, Inc. */

/*
modification history
--------------------
06apr16,dlk  Adding pathSkipPrefix().
06apr16,dlk  Adding pathCondenseTo().
05apr16,dlk  Adding pathCatEnd().
29apr10,pad  Moved extern C statement after include statements.
28jul03,dat  strict const char * prototypes, removed non-ANSI prototypes
22sep92,rrr  added support for c++
04jul92,jcf  cleaned up.
26may92,rrr  the tree shuffle
04oct91,rrr  passed through the ansification filter
             -fixed #else and #endif
             -changed VOID to void
             -changed copyright notice
05oct90,dnw  removed private functions.
05oct90,shl  added ANSI function prototypes.
             made #endif ANSI style.
             added copyright notice.
30jul90,dnw  added pathLastNamePtr() and changed pathLastName() to void.
01may90,llk  changed pathBuild() and pathCat() to return STATUS.
01apr90,llk  deleted pathArrayFree().
06jul89,llk  written.
*/

#ifndef __INCpathLibh
#define __INCpathLibh

#include "vwModNum.h"

#ifdef __cplusplus
extern "C" {
#endif

/* pathCondenseTo() flags */
  
#define PATH_BACKSLASH_SEP     (0x1U)  /* translate '\\' to '/' */
#define PATH_CONDENSE_DOT_DOT  (0x2U)  /* condense "comp/.." ==> "" */
#define PATH_ROOT_DOT_DOT      (0x4U)  /* condense root "/.." to "/" */

/* function declarations */

extern STATUS 	pathBuild (const char ** nameArray, char ** nameArrayEnd,
			   char *destString);
extern STATUS 	pathCat (const char *dirName, const char *fileName,
			   char *result);
extern STATUS   pathCatEnd (const char * dirName, const char * fileName,
                            char * result, char * end);
extern char *	pathLastNamePtr (const char *pathName);
extern void 	pathCondense (char *pathName);
extern char *   pathCondenseTo (char * out, char * end, const char * in, UINT32 flags);
extern void 	pathLastName (char *pathName, char ** pLastName);
extern void 	pathParse (const char *longName, char ** nameArray,
				char *nameBuf);
extern void 	pathSplit (const char *fullFileName, char *dirName,
				char *fileName);
extern const char * pathSkipPrefix (const char * p1, const char * p2);

#ifdef __cplusplus
}
#endif

#endif /* __INCpathLibh */
