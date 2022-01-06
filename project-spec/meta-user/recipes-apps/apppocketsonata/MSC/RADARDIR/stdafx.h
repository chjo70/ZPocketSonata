// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE 클래스입니다.
#include <afxodlgs.h>       // MFC OLE 대화 상자 클래스입니다.
#include <afxdisp.h>        // MFC 자동화 클래스입니다.
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC 데이터베이스 클래스입니다.
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO 데이터베이스 클래스입니다.
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT


//////////////////////////////////////////////////////////////////////////
// 로그 관련 함수

#include <afxmt.h>

#define BUILTIN_IP							"192.168.0.66"
#define MYHOME_IP							"192.168.0.156"


// 레이더 수집소 위치
#define RADARDIR_1_IP_ADDRESS				"192.168.0.14"
#define RADARDIR_2_IP_ADDRESS				"192.168.0.24"
#define RADARDIR_3_IP_ADDRESS				"192.168.0.34"

#define DB_SERVER_IP_ADDRESS				"192.168.0.41"

//#define LOG_DIRECTORY						"RADARDIR_LOG"
#define LOG_SUB_DIRECTORY					"레이더 방탐"
#define GLOBAL_LOG_DIRECTORY				"\\\\192.168.0.41\\Files"
#define GLOBAL_LOG_DIRECTORY2				"\\\\192.168.0.41"

extern CCriticalSection g_criticalLog;
extern CCriticalSection g_criticalDbg;
extern CCriticalSection g_criticalExe;

// 가변인함수로 Lof라는 함수 선언
void Log( int nType, char *fmt, ... );
CString GetFilePath();
BOOL _CreateDir( char *pPath );
BOOL CheckPing();

// #ifndef _LOG_TYPE_
// #define _LOG_TYPE_
// // 로그 타입 사용자가 원하는 대로 정의
// enum LogType {
// 	enDebug=0,
// 	enNormal,
// 	enLineFeed,
// 	enError,
// 	enEnd,
// };
// #endif

//////////////////////////////////////////////////////////////////////////

CString GetIpAddress();

void SetWindowHandler( HWND hWnd );
void SetMute( bool bEnable );
void SetLocal( bool bLocal );


//enum EN_RADARCOLLECTORID { RADARCOL_Unknown=0, RADARCOL_1=1, RADARCOL_2, RADARCOL_3, RADARCOL_MAX };

typedef enum {
	enBuiltIn=0,
	enOffice,
	enMyHome
} enPosition;

enPosition GetPosition();

#ifdef __cplusplus
extern "C" {
#endif
	int Printf(char *format, ...);
	int WPrintf(char *format, ...);

#ifdef __cplusplus
}
#endif