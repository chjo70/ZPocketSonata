/* warmBootLib.h - warm boot library header file*/

/*
 * Copyright (c) 2015 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
07apr15,l_z  created. (F3387)
*/

#ifndef _INC_WARMBOOTLIB_H
#define _INC_WARMBOOTLIB_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

IMPORT char wrs_kernel_bss_end[];

#define WARM_DATA_ADDR ROUND_UP((ULONG)wrs_kernel_bss_end, warmBootDataAlign)

IMPORT UINT32 warmBootDataAlign;

typedef struct warmData {
    UINT32 textCrc32;
    UINT32 dataCrc32;
    ULONG  dataOffset;
    ULONG  dataLength;
    ULONG  offset;
} WARM_DATA;

ULONG warmBootDataEndGet ();
void warmBootStart (void * entryPoint);
#ifdef _WRS_CONFIG_SMP
void warmBootSlaveDisable (UINT32 cpuId);
void warmBootSlaveEnable (UINT32 cpuId,void * initFunc,WIND_CPU_STATE * cpuState);
#endif /* _WRS_CONFIG_SMP */

#ifdef __cplusplus
    }
#endif /* __cplusplus */

#endif /* _INC_WARMBOOTLIB_H */


