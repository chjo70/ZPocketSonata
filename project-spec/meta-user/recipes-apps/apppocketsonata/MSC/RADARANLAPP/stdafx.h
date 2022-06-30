
// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�.

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.

// MFC�� ���� �κа� ���� ������ ��� �޽����� ���� ����⸦ �����մϴ�.
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ����Դϴ�.
#include <afxext.h>         // MFC Ȯ���Դϴ�.


#include <afxdisp.h>        // MFC �ڵ�ȭ Ŭ�����Դϴ�.



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Windows ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC�� ���� �� ��Ʈ�� ���� ����



//////////////////////////////////////////////////////////////////////////
// �α� ���� �Լ�

#include <afxmt.h>

//#define LOG_DIRECTORY							"RADARANL_LOG"

extern CCriticalSection g_criticalLog;
extern CCriticalSection g_criticalDbg;
extern CCriticalSection g_criticalExe;

// �������Լ��� Lof��� �Լ� ����
//void Log( int nType, const char *fmt, ... );
CString GetFilePath();
BOOL CreateDir( char *pPath );

// �α� Ÿ�� ����ڰ� ���ϴ� ��� ����
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


// VS2012 �̻󿡼� TRACE�� �����ϱ� ����.
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

