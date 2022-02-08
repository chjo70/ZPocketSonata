/* argLib.h - argument parsing library header file */

/*
 * Copyright (C) 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
26aug15,kjn  written
*/

#ifndef __INCargLibh
#define __INCargLibh

/* includes */

#include <netinet/in.h>
#include <types/vxTypes.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* defines */

/* typedefs */

struct argDef;

typedef enum argErr
    {
    ARG_OK,             /* all arguments parsed successfully */
    ARG_HELP,           /* parsing aborted as the help page is printed */
    ARG_ERR_UNKNOWN,    /* unkown argument encounter */
    ARG_ERR_PARSE       /* failed to parse argument value */
    } ARG_ERR;

/*
 * Should be considered private, argument type specific documentation routine.
 */
typedef void (*ARG_DOC_RTN)     (const struct argDef * def);

/*
 * Should be considered private, argument type specific parser.
 */
typedef BOOL (*ARG_PARSE_RTN)   (struct argDef * def, const char * str);

/*
 * Single choice selection, i.e. argument is one of the defined text strings.
 */
typedef struct argChs
    {
    const char * str;   /* selection text string */
    int          val;   /* value for this selection */
    const char * doc;   /* documentation for this selection */
    } ARG_CHS;

/*
 * Instance specific information
 */
typedef union argInfo
    {
    BOOL        boolDflt;	/* default value for boolean */
    int         af;             /* address family for Internet address */
    struct
        {
        int     minVal;		/* range minimum value, inclusive */
        int     maxVal;         /* range maximum value, inclusive */
        } intRng;
    struct
        {
        const ARG_CHS * lst;   	/* choice list */
        int     lstLen;   	/* choice list length */
        } ch;
    } ARG_INFO;

/*
 * Storage for a single argument definition. This type must be treated as
 * opaque, none of the members should be read/written to directly. The type is
 * defined here to make it possible to allocate storage space for an argument
 * in automatic variables.
 */
typedef struct argDef
    {
    struct argDef * next;       /* next argument or NULL */
    char            opt;        /* character identifier for argument */
    char            hasVal;     /* 1 if value is expected, 0 otherwise */
    const char *    longOpt;    /* long name for argument */
    const char *    doc;        /* documentation for argument */
    void *          storage;    /* storage for argument value */
    ARG_INFO        info;       /* additional information about instance */
    ARG_DOC_RTN     docRtn;     /* type specific documentation routine */
    ARG_PARSE_RTN   parseRtn;   /* parse routine */
    } ARG_DEF;

/*
 * The argument context hold the set of arguments relevant for the current
 * program.
 */
typedef struct argCtx
    {
    ARG_DEF * defs;     /* list of arguments associated with this context */
    int       idx;      /* number of arguments successfully parsed */
    ARG_ERR   err;      /* */
    ARG_DEF   help;     /* storage for the always included help option */
    } ARG_CTX;

/* function declarations */

extern void     argInit         (ARG_CTX * ctx);
extern BOOL     argParse        (ARG_CTX * ctx,
                                 const char * args[],
                                 int argLen);
extern int      argIdxGet       (const ARG_CTX * ctx);
extern ARG_ERR  argErrGet       (const ARG_CTX * ctx);

extern ARG_DEF * argDef         (ARG_CTX * ctx,
                                 ARG_DEF * def,
                                 char shortOpt,
                                 const char * longOpt,
                                 const char * optDoc);

extern void     argBool         (ARG_DEF * def,
                                 BOOL * val,
                                 BOOL defaultVal);
extern void     argInt          (ARG_DEF * def,
                                 int * val,
                                 int defaultVal);
extern void     argIntRange     (ARG_DEF * def,
                                 int * val,
                                 int defaultVal,
                                 int minVal,
                                 int maxVal);
extern void     argChoice       (ARG_DEF * def,
                                 int * val,
                                 int defaultVal,
                                 const ARG_CHS * chl,
                                 int chlLen);
extern void     argStr          (ARG_DEF * def,
                                 const char ** str,
                                 const char * defaultStr);
extern void     argInAddr       (ARG_DEF * def,
                                 struct in_addr * inAddr,
                                 const char * dfltAddr);
extern void     argIn6Addr      (ARG_DEF * def,
                                 struct in6_addr * inAddr,
                                 const char * dfltAddr);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __INCargLibh */
