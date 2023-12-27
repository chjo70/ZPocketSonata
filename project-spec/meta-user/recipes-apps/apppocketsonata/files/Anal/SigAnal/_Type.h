/**

    @file      _Type.h
    @brief
    @details   ~
    @author    Cool Guy
    @date      18.06.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#pragma once

/****************************************************************************************
 파 일 명 : _type.h
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 목    적 :
 가    정 :
 저 자 명 : Jo Churl-hee
 변 경 자 :
 변경내용 : (목적)
 변경일시 : 99-05-03 4:33오후
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
 컴파일 일시 :
*****************************************************************************************/


#include <vector>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

#include <math.h>
#include <time.h>

#ifdef _MSC_VER
#include <sys/timeb.h>

#elif defined(__VXWORKS__)
#include <types/vxTypesOld.h>

#elif defined(__linux__)

#endif



#ifdef __linux__
#define _MAX_PATH               1024

#define UINT_MAX                0xffffffff
#define INT_MAX                 2147483647
#define ULONGLONG_MAX   (0xffffffffffffffff)

typedef bool BOOL;
typedef unsigned int UINT;
typedef unsigned char UCHAR;
typedef char TCHAR;
typedef unsigned short USHORT;

typedef string CString;
typedef unsigned int INT32;


typedef unsigned long DWORD;
typedef long LONG;

typedef string CString;

#define __time32_t              time_t


//#define _open                   open
#define _close                  close
#define	_write					write
#define	_read					read


#define sprintf_s               sprintf
#define strcpy_s                strcpy


#define _T(A)                   (A)

#define TRUE (true)
#define FALSE (false)

#define TRACE                   printf
#define TRACE0                  printf
#define TRACE1                  printf

#define _lseek                  lseek

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MFC 버젼
#elif _MSC_VER
#define MSG_DONTWAIT            (0)
#define IPC_NOWAIT              (04000)

#define IPC_PRIVATE             (0)

typedef int key_t;

#include <winsock.h>

//typedef timeval timespec;
#define timespec timeval

#define sleep(A)   Sleep(A*1000)


//#define sprintf_s               sprintf

#ifndef _T
#define _T(A)                   (A)
#endif

//#define open                    _open

#ifdef _CONSOLE

#else

#define	write					_write
#define	read					_read
#define	chmod					_chmod

#ifdef TRACE

#else
#define TRACE                   printf
#endif

#endif





//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VxWorks 버젼
#elif defined(__VXWORKS__)
#include <msgQLib.h>

#define _MAX_PATH               1024

//#define UINT_MAX                (0xffffffff)
#define ULONGLONG_MAX   		(0xffffffffffffffff)
// #define FLT_MAX                 (float) (3.402823466e+38F)

#define  IPC_NOWAIT          	(0)

typedef string CString;
#define key_t MSG_Q_ID

#define IPC_PRIVATE     		(0)

#define wsprintf                sprintf
#define __time32_t              time_t
#define	_time64					time
#define _lseek                  lseek
#define strcpy_s                strcpy
#define strnlen_s(A,B)          strlen(A)
typedef char TCHAR;
#define _T(A)                   (A)

//#define _open                   open
#define _close                  close
#define	_write					write
#define	_read					read

//#define sprintf_s               sprintf
//#define	wcslen					strlen
#define	wcscpy					strcpy
#define	_localtime64_s(A, B)	localtime_r(B, A)
#define	localtime_s(A, B)		localtime_r(B, A)


#define	_mktime32				mktime

#define TRACE                   printf
#define TRACE0                  printf
#define TRACE1                  printf

typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef long long __int64;
typedef unsigned int WORD;
typedef unsigned long long SIZE_T;


#define M_PI          3.14159265358979323846  /* pi */

#define	O_BINARY				(0)

typedef void             *LPVOID;
typedef unsigned long DWORD;
typedef long LONG;


#else
typedef bool BOOL;
typedef unsigned int UINT;
typedef unsigned char UCHAR;
typedef char TCHAR;
typedef unsigned short USHORT;

typedef string CString;
typedef unsigned int INT32;

#define ULONGLONG_MAX   (0xffffffffffffffff)

#define _T(A)                   (A)

#define TRUE (true)
#define FALSE (false)

#endif





