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

#ifndef _TYPE_H_
#define _TYPE_H_

#include <stddef.h>

#ifndef _WIN32
//#include <types/vxTypesOld.h>
#endif

/////////////////////////////////////////////////////////////////////////////////////////
//  레이더 징표분석기용 형 선언
//

#define TASK  void

#define TRUE 1
#define FALSE 0

typedef long long int _TOA;

#define DINT  int

#define WORD32  unsigned int
#define WORD16  unsigned short
#define WORD08  unsigned char

#ifdef _WIN32
#define RET_OK    1
#define BOOL  int
#define UINT  unsigned int
#define UCHAR unsigned char
#define USHORT  unsigned short

#endif

#ifdef _VXWORKS_
#define bool unsigned int

#else
#define TASK_TCB TCB

#endif

#endif  // #ifndef _TYPE_H_
