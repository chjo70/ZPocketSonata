// Macros.h: interface for the macro definetion
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MACRO_H__93E04DDF_CE5E_4DB7_95B5_D35B77F287E7__INCLUDED_)
#define AFX_MACRO_H__93E04DDF_CE5E_4DB7_95B5_D35B77F287E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>

#ifdef BOOT_PRINT
#define Printf printf
#define WPrintf printf
#endif

#ifndef WhereIs
#define WhereIs									printf( "...in %s file, %d line(s)" , __FILE__, __LINE__ )
#endif


#define PrintErr(A)							{ WPrintf A; WhereIs; }

#define DPrintf(A)							theLogDebug->DebugPrintf(A)

// 수식 연산 정의
#define FMUL( A, B )            ( (float) (A) * (float) (B) )
//#define UDIV( A, B )            (UINT) ( (float) (A) / (float) (B) + 0.5 )
#define UMUL( A, B )            (UINT) ( ( (float) (A) * (float) (B) ) + 0.5 )

#define _TOADIV( A, B )         (_TOA) ( (double) (A) / (double) (B) + 0.5 )

// 변환 수식 정의
#define DB(A)										UDIV( 256 * ( (float) A + 74.6875 ), 80 )
#define CD_DB(A)								UDIV( ((float) A * 31.654) + 1713.77, 7.8125 )
#define FMOP(A)									UDIV( A, 1.25 )
#define CW(A)										UDIV( A, 0.2 )

// 이진 타이머 수식
#define	BINARY_TIMER( A, N )		( ( A % (2*N) ) / N )


#endif // !defined(AFX_MACRO_H__93E04DDF_CE5E_4DB7_95B5_D35B77F287E7__INCLUDED_)
