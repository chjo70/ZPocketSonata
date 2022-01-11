// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.

#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ����Դϴ�.
#include <afxext.h>         // MFC Ȯ���Դϴ�.

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE Ŭ�����Դϴ�.
#include <afxodlgs.h>       // MFC OLE ��ȭ ���� Ŭ�����Դϴ�.
#include <afxdisp.h>        // MFC �ڵ�ȭ Ŭ�����Դϴ�.
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC �����ͺ��̽� Ŭ�����Դϴ�.
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO �����ͺ��̽� Ŭ�����Դϴ�.
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Internet Explorer 4 ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // Windows ���� ��Ʈ�ѿ� ���� MFC �����Դϴ�.
#endif // _AFX_NO_AFXCMN_SUPPORT


//////////////////////////////////////////////////////////////////////////
// �α� ���� �Լ�

#include <afxmt.h>

// #define BUILTIN_IP						"192.168.0.66"
// #define OFFICE_IP						"10.29.52.175"
// #define MYHOME_IP						"192.168.0.156"
// #define ONPOOM_IP						"30.30.30.54"



//#define LOG_DIRECTORY					"RADARANL_LOG"
#define	LOG_SUBDIRECTORY				"���̴� �м�"
#define GLOBAL_LOG_DIRECTORY			"\\\\192.168.0.41\\Files"
#define GLOBAL_LOG_DIRECTORY2			"\\\\192.168.0.41"


// X ��� �϶� DB ���� ��巹��
#define DB_SERVER_IP_ADDRESS			"30.30.30.54"
// ��õ����
// #define DB_SERVER_IP_ADDRESS			"192.168.0.41"



extern CCriticalSection g_criticalLog;
extern CCriticalSection g_criticalDbg;
extern CCriticalSection g_criticalExe;

// �������Լ��� Lof��� �Լ� ����
void Log( int nType, const char *fmt, ... );
CString GetFilePath();
BOOL CreateDir( char *pPath );
BOOL CheckPing();


CString GetIpAddress();

typedef enum {
	enBuiltIn=0,
	enOffice,
	enMyHome,
	enOnpoom,

	enLAST_COM
} enPosition;

// SOCKADDR g_ComIPAddress[enLAST_COM][30] = { { "192.168.0.66" },
// 									  { "10.29.52.175" },
// 									  { "192.168.0.156" },
// 									  { "30.30.30.54" } } ;



//enum EN_RADARCOLLECTORID { RADARCOL_Unknown=0, RADARCOL_1=1, RADARCOL_2, RADARCOL_3, RADARCOL_MAX };

enPosition GetPosition();

#ifdef __cplusplus
extern "C" {
#endif
	int Printf(char *format, ...);
	int WPrintf(char *format, ...);

#ifdef __cplusplus
}
#endif

void SetWindowHandler( HWND hWnd );
void SetLocal( bool bLocal );
bool GetLocal();
