/* speExcCommon.h - common definitions for IEEE-754 compatibility FP handler  */

/*
 * Copyright (c) 2012 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01b,20jul12,zgl  WIND00364435: corrected some definitions
01a,17may12,vp   Written.
*/

#ifndef __INCspeExcCommonh
#define __INCspeExcCommonh

#ifdef __cplusplus
extern "C" {
#endif

/* defines */

#define _SPEFSCR_SOVH   (0x80000000)
#define _SPEFSCR_OVH    (0x40000000)
#define _SPEFSCR_FGH    (0x20000000)
#define _SPEFSCR_FXH    (0x10000000)
#define _SPEFSCR_FINVH  (0x08000000) /* Status bit: invalid op. for high vector operations    */
#define _SPEFSCR_FDBZH  (0x04000000) /* Status bit: divide by zero for high vector operations */
#define _SPEFSCR_FUNFH  (0x02000000) /* Status bit: underflow for high vector operations      */
#define _SPEFSCR_FOVFH  (0x01000000) /* Status bit: overflow for high vector operations       */
#define _SPEFSCR_FINXS  (0x00200000) /* Sticky */
#define _SPEFSCR_FINVS  (0x00100000) /* Sticky */
#define _SPEFSCR_FDBZS  (0x00080000) /* Sticky */
#define _SPEFSCR_FUNFS  (0x00040000) /* Sticky */
#define _SPEFSCR_FOVFS  (0x00020000) /* Sticky */
#define _SPEFSCR_SOV    (0x00008000)
#define _SPEFSCR_OV     (0x00004000)
#define _SPEFSCR_FG     (0x00002000)
#define _SPEFSCR_FX     (0x00001000) /* Status bit: inexact                                         */
#define _SPEFSCR_FINV   (0x00000800) /* Status bit: invalid op. for scalar/low vector operations    */
#define _SPEFSCR_FDBZ   (0x00000400) /* Status bit: divide by zero for scalar/low vector operations */
#define _SPEFSCR_FUNF   (0x00000200) /* Status bit: underflow for scalar/low vector operations      */
#define _SPEFSCR_FOVF   (0x00000100) /* Status bit: overflow for scalar/low vector operations       */
#define _SPEFSCR_EXC_ENABLE_MASK (0x0000007C)
#define _SPEFSCR_FINXE  (0x00000040) /* Exception Enable bit */
#define _SPEFSCR_FINVE  (0x00000020) /* Exception Enable bit */
#define _SPEFSCR_FDBZE  (0x00000010) /* Exception Enable bit */
#define _SPEFSCR_FUNFE  (0x00000008) /* Exception Enable bit */
#define _SPEFSCR_FOVFE  (0x00000004) /* Exception Enable bit */
#define _SPEFSCR_FRMC   (0x00000003) /* Rounding mode */

#define _SPEFSCR_FRMC_NRST (0x00000000) /* Round to nearest        */
#define _SPEFSCR_FRMC_ZERO (0x00000001) /* Round towards zero      */
#define _SPEFSCR_FRMC_PINF (0x00000002) /* Round towards +Infinity */
#define _SPEFSCR_FRMC_NINF (0x00000003) /* Round towards -Infinity */

/* typedefs */

typedef enum
    {
    POSITIVE = 0,
    NEGATIVE = 1
    } SIGN_TYPE;


typedef enum
    {
    EQUAL          = 0,
    LESS_THAN      = 1,
    GREATER_THAN   = 2,
    UNORDERED      = 3
    } COMP_CODE;

/* forward declarations */

IMPORT unsigned int vxEfdctui(double);
IMPORT unsigned int vxEfdctuiz(double);
IMPORT   signed int vxEfdctsi(double);
IMPORT   signed int vxEfdctsiz(double);
IMPORT unsigned int vxEfdctuf(double);
IMPORT   signed int vxEfdctsf(double);

IMPORT unsigned int vxEfsctui(float);
IMPORT unsigned int vxEfsctuiz(float);
IMPORT   signed int vxEfsctsi(float);
IMPORT   signed int vxEfsctsiz(float);
IMPORT unsigned int vxEfsctuf(float);
IMPORT   signed int vxEfsctsf(float);

#ifdef __cplusplus
}
#endif

#endif /* __INCspeExcCommonh */

