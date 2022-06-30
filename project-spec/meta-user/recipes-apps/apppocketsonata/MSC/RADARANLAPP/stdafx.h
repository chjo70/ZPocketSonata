
// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다.

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.

// MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
#include <afxext.h>         // MFC 확장입니다.


#include <afxdisp.h>        // MFC 자동화 클래스입니다.



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows 공용 컨트롤에 대한 MFC 지원입니다.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC의 리본 및 컨트롤 막대 지원



//////////////////////////////////////////////////////////////////////////
// 로그 관련 함수

#include <afxmt.h>

//#define LOG_DIRECTORY							"RADARANL_LOG"

extern CCriticalSection g_criticalLog;
extern CCriticalSection g_criticalDbg;
extern CCriticalSection g_criticalExe;

// 가변인함수로 Lof라는 함수 선언
//void Log( int nType, const char *fmt, ... );
CString GetFilePath();
BOOL CreateDir( char *pPath );

// 로그 타입 사용자가 원하는 대로 정의
// enum LogType {
// 	enDebug=0,
// 	enNormal,
// 	enLineFeed,
// 	enError,
// 	enEnd,
// };

//////////////////////////////////////////////////////////////////////////

CString GetIpAddress();
int Printf(char *format, ...);
void SetWindowHandler( HWND hWnd );


// #define BUILTIN_IP					"192.168.0.66"
// #define MYHOME_IP						"192.168.0.156"
// #define OFFICE_IP						"10.29.52.175"
// 
// typedef enum {
// 	enBuiltIn=0,
// 	enOffice,
// 	enMyHome
// } enPosition;
// 
// enPosition GetPosition();



#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


// VS2012 이상에서 TRACE를 변경하기 위함.
#if _MSC_VER > 1600

#ifdef _DEBUG

bool _TRACE(char *format, ...);
bool _TRACE(CString strFormat, ...);

#undef TRACE
#define TRACE _TRACE

#else

bool _TRACE(char *format, ...);
bool _TRACE(CString strFormat, ...);

#undef TRACE
#define TRACE _TRACE

//#define TRACE false && _TRACE

#endif

#endif

