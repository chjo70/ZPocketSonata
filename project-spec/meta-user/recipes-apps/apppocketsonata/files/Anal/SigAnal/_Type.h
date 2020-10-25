﻿/****************************************************************************************
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

#ifndef _TYPE_H_
#define _TYPE_H_

#include <stddef.h>

#include <vector>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

#include <math.h>
#include <time.h>
#include <sys/timeb.h>
//#include <sys/timeb.h>

#ifdef _MSC_VER

#elif defined(_VXWORKS_)
#include <types/vxTypesOld.h>

#else

/////////////////////////////////////////////////////////////////////////////////////////
// 리눅스용 컴파일 추가
typedef bool BOOL;
typedef unsigned int UINT;
typedef unsigned char UCHAR;
typedef char TCHAR;
typedef unsigned short USHORT;
#ifndef _WIN32
typedef time_t __time32_t;
#endif

typedef string CString;
typedef unsigned int INT32;

#define _T(A)                   (A)

#define sscanf_s(A,B,C,D,E)     sscanf(A,B,C,D)

#define sprintf_s               sprintf
#define wsprintf                sprintf

#define strcpy_s                strcpy

#define _finite                 finite

#define _time32(A)              time(A)
#define __time32_t              time_t
#define __timeb32               timeb
#define _ftime32_s              ftime
#define _localtime32_s(A,B)     localtime_r(B,A)

#define AfxMessageBox           printf


#define TRACE                   printf
#define TRACE0                  printf
#define TRACE1                  printf

#define FLT_MIN                 1.175494351e-38F        /* min positive value */

#ifndef _WIN32
#define _MAX_PATH               1024
#endif

#include "../../Utils/cfile.h"



#endif



/////////////////////////////////////////////////////////////////////////////////////////
//  레이더 징표분석기용 형 선언
//

#define TASK  void

#define TRUE (true)
#define FALSE (false)

#ifndef _TOA
typedef unsigned long long int _TOA;
#endif

#define DINT  int

#define WORD32  unsigned int
#define WORD16  unsigned short
#define WORD08  unsigned char

#ifdef _WIN32
//#define RET_OK    1
//#define BOOL  int
//#define UINT  unsigned int
//#define UCHAR unsigned char
//#define USHORT  unsigned short

#endif

#ifdef _VXWORKS_
#define bool unsigned int

#else
#define TASK_TCB TCB

#endif

#endif  // #ifndef _TYPE_H_
