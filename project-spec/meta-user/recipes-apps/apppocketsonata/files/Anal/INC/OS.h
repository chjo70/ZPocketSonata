/**

    @file      OS.h
    @brief
    @details   ~
    @author    조철희
    @date      17.04.2023

**/

#pragma once


//////////////////////////////////////////////////////////////////////////
#ifdef __VXWORKS__
#include <types/vxTypesOld.h>
#include <sysLib.h>


#define RING_ID					UINT
//#define SEM_ID					UINT
#define IMPORT					extern
//#define WAIT_FOREVER		0
//#define VX_FP_TASK			0
#define timer_t					UINT
//#define CLOCK_REALTIME	0
//#define MODULE					char
#define NO_WAIT					0


#define ULONGLONG_MAX           (0xffffffffffffffff)


//#define UDF_RAMDISK_FILENAME	"c:\\tftpboot\\udf_1.udf"
#define UDF_RAMDISK_FILENAME	"C:\\LMS\\EidFiles\\udf_1.udf"

#define max( A, B )             ( (A) > (B) ? (A) : (B) )
#define min( A, B )             (((A) < (B)) ? (A) : (B))

#define OS_MILLISEC(A)          (int) (A/10.+0.5)
#define OS_SEC(A)               (A*100)

#define Sleep(A)                taskDelay(A*sysClkRateGet())		// 초 단위 대기

typedef long long __time64_t;

#define fscanf_s                fscanf
#define sscanf_s                sscanf

typedef unsigned int SOCKET;


#define _difftime64( A, B)      ( A > B ? ( A - B ) : ( B - A ) )

//////////////////////////////////////////////////////////////////////////
#elif defined(_GNUCC__)
#define WAIT_FOREVER		0

#define OS_MILLISEC(A)          (A*1000)
#define OS_SEC(A)               (A*1000000)


//////////////////////////////////////////////////////////////////////////
#elif _MSC_VER
#define WAIT_FOREVER		    0
#define VX_FP_TASK			    0

#if !defined(CLOCK_REALTIME) //modify for chekcing is not defined by shg1314 190225
#define CLOCK_REALTIME	        0
#endif


#define CLOCK_MONOTONIC         0

#define NO_WAIT					0

#define OS_MILLISEC(A)          (A)
#define OS_SEC(A)               (A*1000)


#define Sleep(A)                Sleep(A*1000)

#define STATUS					unsigned int

#define VXB_DEV_ID              UINT

#define _func_kprintf			TRACE

#define IMPORT					extern

#define MODULE					char

#define getcwd  _getcwd
#define mkdir   _mkdir
#define open    _open
#define write   _write

#define putenv  _putenv

#define OK      (0)

#endif


