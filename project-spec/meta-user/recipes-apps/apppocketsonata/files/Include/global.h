/*
 * 본 문서는 시스템을 정의하는 테이블과 운영체계 또는 컴파일러에 의존하여 정의한다.
 * */

#ifndef _GLOBAL_H
#define _GLOBAL_H

enum ENUM_ENDIAN_MODE {
    enLITTLE_ENDIAN=0,
    enBIG_ENDIAN,
    enUNKNOWN_ENDIAN

};

extern ENUM_ENDIAN_MODE g_enEndian;


// 전역 변수를 정의한다.
#ifdef _MAIN_GLOBALS_

// 메시지 큐 ID 정의합니다.
int g_iKeyId=1;
int g_iMode;

// 프로그램 에서 아규먼트 인자로 해석하여 저장하는 변수
ENUM_BoardID g_enBoardId=enPRC_Unknown;
char g_szPDWScinarioFile[100];

bool g_Loop=true;

bool g_AnalLoop=true;

//ENUM_ENDIAN_MODE g_enEndian;

/////////////////////////////////////////////////////////////////////////////////

bool g_bSaveFile=true;

char g_szCollectBank[4][10] = { "탐지", "추적", "스캔", "사용자" } ;

#ifdef __VXWORKS__
MSG_Q_ID g_ShmMemMsgQID;
#define _SHM_MEMORY_KEY             g_ShmMemMsgQID

int g_iClkTickPerSecond;

#else
#define _SHM_MEMORY_KEY             (333)
#endif

#else
extern int g_iKeyId;
extern int g_iMode;

extern ENUM_BoardID g_enBoardId;
extern char g_szPDWScinarioFile[100];

extern bool g_Loop;
extern bool g_AnalLoop;

extern bool g_bSaveFile;

extern char g_szCollectBank[4][10];

#ifdef __VXWORKS__
extern MSG_Q_ID g_ShmMemMsgQID;
#define _SHM_MEMORY_KEY             g_ShmMemMsgQID

extern int g_iClkTickPerSecond;
#else
#define _SHM_MEMORY_KEY             (333)
#endif

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
