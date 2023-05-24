﻿// Macros.h: interface for the macro definetion
//
//////////////////////////////////////////////////////////////////////

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>

#ifdef BOOT_PRINT
#define Printf printf
#define WPrintf printf
#endif

// #ifndef WhereIs
// #ifdef _WIN32
// 
// #define WhereIs									TRACE( "...in %s 파일, %d 라인" , strrchr(__FILE__,'\\') ? strrchr(__FILE__,'\\')+1 : __FILE__ , __LINE__ )
// #else
// #define WhereIs									printf( "...in %s file, %d line(s)\n" , strrchr(__FILE__,'/'), __LINE__ )
// #endif
// #endif


//#define PrintErr(A)							{ WPrintf A; WhereIs; }

#define DPrintf(A)							theLogDebug->DebugPrintf(A)

// 수식 연산 정의
#define FMUL( A, B )                       ( (float) (A) * (float) (B) )
#define UMUL( A, B )                       (UINT) ( ( (float) (A) * (float) (B) ) + 0.5 )

#define F2I( A )                           (int) ( (float) A + (float) 0.5 ) 

// 변환 수식 정의
#define DB(A)								UDIV( 256 * ( (float) A + 74.6875 ), 80 )
#define CD_DB(A)							UDIV( ((float) A * 31.654) + 1713.77, 7.8125 )
#define FMOP(A)								UDIV( A, 1.25 )
#define CW(A)								UDIV( A, 0.2 )

// 
#define _EQUALS3( A, B, C )             B = C;  \
                                        A = B;

#define _EQUALS4( A, B, C, D )          C = D;  \
                                        B = C;  \
                                        A = B;

#define _EQUALS5( A, B, C, D, E )       D = E;  \
                                        C = D;  \
                                        B = C;  \
                                        A = B;

#define _EQUALS6( A, B, C, D, E, F )    E = F;  \
                                        D = E;  \
                                        C = D;  \
                                        B = C;  \
                                        A = B;


