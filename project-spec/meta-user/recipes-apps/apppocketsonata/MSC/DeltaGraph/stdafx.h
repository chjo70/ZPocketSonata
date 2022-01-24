
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

#define _INTSAFE_H_INCLUDED_
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


//#define LOG_DIRECTORY					_T("DELTAGRAPH_LOG")
#define	LOG_SUBDIRECTORY				_T("RWRSuite ����")
#define GLOBAL_LOG_DIRECTORY			_T("\\\\192.168.0.41\\Files")
#define GLOBAL_LOG_DIRECTORY2			_T("\\\\192.168.0.41")

// �α� Ÿ�� ����ڰ� ���ϴ� ��� ����
enum LogType {
	enDebug=0,
	enNormal,
	enLineFeed,
	enError,
	enEnd,
};

void Log( int nType, const TCHAR *fmt, ... );
CString GetFilePath();
BOOL CreateDir( TCHAR *pPath );
void SetLocal( bool bLocal );
CString GetIpAddress();
int UnicodeToUtf8( char* pUtf8, TCHAR* pUnicode);

#define BUILTIN_IP					_T("192.168.0.66")
#define OFFICE_IP					_T("10.29.52.175")
#define MYHOME_IP					_T("192.168.0.156")
#define MYHOME_IP_2					_T("192.168.0.178")
#define MYHOME_SUBNET				_T("192.168.10")
#define NO_NETWORK_IP				_T("127.0.0.1")

typedef enum {
	enBuiltIn=0,
	enOffice,
	enMyHome,
	enNoNetwork
} enPosition;

enPosition GetPosition();





#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


