/* bootLib.h - boot support subroutine library */

/*
 * Copyright (c) 1990-1992,1996-1997,2002-2003,2007, 2009, 2012, 2014-2017
 * Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
06dec17,dlk  Fix buffer length checking and NUL-termination issues in
             bootParamsPrompt(); introduce bootStructToStringExt(),
             bootParamsPromptBp(), and bootParamsPromptExt()  (V7COR-5250)
21jul16,j_l  add bootParamCheck() (V7PRO-3156)
29sep15,h_k  removed a duplicated BOOT_ADDR_LEN. (V7COR-3631)
12may15,elp  Increase simulator values (V7COR-1606).
13feb15,jpb  Removed bootScanNum which was replaced by strtol (VXCOR-2416)
12may14,jpb  US37960: provide means to insert and extract options saved
             in the boot line.  Add definition for bootParamsReserveGet() &
             bootParamsReserveSet() and added reserve field to BOOT_PARAMS.
31jan14,to   include vxWorks.h for IMPORT, etc.
13jan12,pgh  Add definition for boot line length.
16dec09,pgh  64-bit conversion
29aug07,tkf  Added BOOT_OTHER_FIELD_DELIMITER.
21oct03,bpn  Added bootStringToStructAdd() prototype.
13mar02,jkf  Fixed SPR#74251, increased BOOT_DEV_LEN, BOOT_FILE_LEN,
                 and BOOT_FIELD_LEN, changed copyright date to 2002.
15may97,spm  fixed SPR 8533: increased BOOT_PARAMS field sizes to prevent
                 overflow with DHCP client leases
30apr97,spm  moved unit number field to end of BOOT_PARAMS structure
16dec96,spm  removed conditional include from DHCP client code
03dec96,spm  added conditional include to DHCP client code
27nov96,spm  added support for DHCP client and network device unit numbers
22sep92,rrr  added support for c++
04jul92,jcf  cleaned up.
26may92,rrr  the tree shuffle
04oct91,rrr  passed through the ansification filter
                  -changed VOID to void
                  -changed copyright notice
05oct90,shl  added ANSI function prototypes.
                 added copyright notice.
10aug90,dnw  added declaration of bootParamsErrorPrint().
18jul90,dnw  written
*/

#ifndef __INCbootLibh
#define __INCbootLibh

#include <vxWorks.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * BOOT_PARAMS is a structure containing all the fields of the VxWorks
 * boot line.  The routines in bootLib convert this structure to and
 * from the boot line ascii string.
 */

#define BOOT_DEV_LEN            40      /* max chars in device name */
#define BOOT_HOST_LEN           20      /* max chars in host name */
#define BOOT_ADDR_LEN           30      /* max chars in net addr */
#define BOOT_TARGET_ADDR_LEN    50      /* IP address + mask + lease times */
#ifdef _WRS_ARCH_IS_SIMULATOR
#define BOOT_FILE_LEN           512     /* max chars in file name */
#else
#define BOOT_FILE_LEN           160     /* max chars in file name */
#endif
#define BOOT_USR_LEN            20      /* max chars in user name */
#define BOOT_PASSWORD_LEN       20      /* max chars in password */
#define BOOT_OTHER_LEN          80      /* max chars in "other" field */
#define BOOT_RESERVE_LEN        80      /* max chars in reserve field */

#ifdef _WRS_ARCH_IS_SIMULATOR
#define BOOT_FIELD_LEN          512 /* max chars in any boot field */
#else
#define BOOT_FIELD_LEN          160 /* max chars in any boot field */
#endif

#define BOOT_OTHER_FIELD_DELIMITER ';'  /* delimits different parameters
                                           specified in the other field */

typedef struct                          /* BOOT_PARAMS */
    {
    char bootDev [BOOT_DEV_LEN];        /* boot device code */
    char hostName [BOOT_HOST_LEN];      /* name of host */
    char targetName [BOOT_HOST_LEN];    /* name of target */
    char ead [BOOT_TARGET_ADDR_LEN];    /* ethernet internet addr */
    char bad [BOOT_TARGET_ADDR_LEN];    /* backplane internet addr */
    char had [BOOT_ADDR_LEN];           /* host internet addr */
    char gad [BOOT_ADDR_LEN];           /* gateway internet addr */
    char bootFile [BOOT_FILE_LEN];      /* name of boot file */
    char startupScript [BOOT_FILE_LEN]; /* name of startup script file */
    char usr [BOOT_USR_LEN];            /* user name */
    char passwd [BOOT_PASSWORD_LEN];    /* password */
    char other [BOOT_OTHER_LEN];        /* available for applications */
    char reserve [BOOT_RESERVE_LEN];    /* available for setting variables */
    int  procNum;                       /* processor number */
    int  flags;                         /* configuration flags */
    int  unitNum;                       /* network device unit number */
    } BOOT_PARAMS;

/* Note, MAX_BOOT_LINE_SIZE is intended to include the terminating NUL */

#ifdef _WRS_ARCH_IS_SIMULATOR
#define MAX_BOOT_LINE_SIZE      1500     /* Max length of boot line string */
#else
#define MAX_BOOT_LINE_SIZE      255     /* Max length of boot line string */
#endif /* _WRS_ARCH_IS_SIMULATOR */

/* function declarations */

IMPORT STATUS   bootBpAnchorExtract (char * string, char ** pAnchorAdrs);
IMPORT STATUS   bootLeaseExtract (char * string, u_long * pLeaseLen,
                                  u_long * pLeaseStart);
IMPORT STATUS   bootNetmaskExtract (char * string, int * pNetmask);
IMPORT STATUS   bootStructToString (char * paramString,
                                    BOOT_PARAMS * pBootParams);
IMPORT STATUS   bootStructToStringExt (char * paramString, size_t paramBufLen,
                                       BOOT_PARAMS * pBootParams);
IMPORT char *   bootStringToStruct (char * bootString,
                                    BOOT_PARAMS * pBootParams);
IMPORT char *   bootStringToStructAdd (char * bootString,
                                       BOOT_PARAMS * pBootParams);
IMPORT void     bootParamsErrorPrint (char * bootString, char * pError);
IMPORT void     bootParamsPrompt (char * string);
IMPORT STATUS   bootParamsPromptBp (BOOT_PARAMS * bp);
IMPORT STATUS   bootParamsPromptExt (const char * input,
                                     char * output, size_t outSize);
IMPORT void     bootParamsShow (char * paramString);
IMPORT STATUS   bootParamCheck (BOOT_PARAMS * pBootParams,
                                BOOL          minimal,
                                void          printFunc (char *        x,
                                                         _Vx_usr_arg_t a,
                                                         _Vx_usr_arg_t b,
                                                         _Vx_usr_arg_t c,
                                                         _Vx_usr_arg_t d,
                                                         _Vx_usr_arg_t e,
                                                         _Vx_usr_arg_t f));


#ifdef __cplusplus
}
#endif

#endif /* __INCbootLibh */
