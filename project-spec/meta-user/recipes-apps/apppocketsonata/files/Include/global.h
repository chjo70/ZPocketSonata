/*
 * 본 문서는 시스템을 정의하는 테이블과 운영체계 또는 컴파일러에 의존하여 정의한다.
 * */

#ifndef _GLOBAL_H
#define _GLOBAL_H


// 전역 변수를 정의한다.
#ifdef _MAIN_GLOBALS_


// 메시지 큐 ID 정의합니다.
int g_iKeyId=1;
int g_iMode;

// 프로그램 에서 아규먼트 인자로 해석하여 저장하는 변수
ENUM_BoardID g_enBoardId=enPRC_Unknown;
bool g_Loop=true;

bool g_AnalLoop=true;

/////////////////////////////////////////////////////////////////////////////////

bool g_bSaveFile=true;


#else
extern int g_iKeyId;
extern int g_iMode;

extern ENUM_BoardID g_enBoardId;


extern bool g_Loop;
extern bool g_AnalLoop;

extern bool g_bSaveFile;

#endif


#ifdef __cplusplus
extern "C"
{
#endif

extern void _ShowProgramTitle( void );
extern char *_GetProgramVersion();

#ifdef __cplusplus
}
#endif




#endif // _SYSTEM_H
