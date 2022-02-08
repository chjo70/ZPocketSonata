/* pathUtilLib.h - path utility library header file */

/* Copyright 2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01c,09jan12,h_x  Move extern "C" after last header file include.
01b,07jan05,syy  Fixed compile error for RTP
01a,14dec04,syy  written.
*/

#ifndef __INCpathUtilLibh
#define __INCpathUtilLibh

/* includes */
#include <vxWorks.h>

#ifdef __cplusplus
extern "C" {
#endif
    
/* function declarations */

extern STATUS   pathUtilBuild (const char ** nameArray, char ** nameArrayEnd,
                               char *destString);
extern STATUS   pathUtilCat (const char *dirName, const char *fileName,
                             char *result);
extern void     pathUtilCondense (char *pathName);
extern void     pathUtilParse (const char *longName, char ** nameArray,
                               char *nameBuf);
extern void     pathUtilArrayReduce (char **nameArray);
extern BOOL     pathUtilIsSubDir (const char *s1, const char *s2);

#ifdef __cplusplus
}
#endif

#endif /* __INCpathUtilLibh */
