﻿
// pch.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.

#include "stdafx.h"


//
// #ifdef _MSC_VER
//
// #pragma once
//
// #define _INTSAFE_H_INCLUDED_
//
// #ifdef _QT_MAKE_
// #define _AFXDLL
// #endif
//
// #ifndef _SECURE_ATL
// #define _SECURE_ATL 1
// #endif
//
// #ifndef VC_EXTRALEAN
// #define VC_EXTRALEAN            // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// #endif
//
// #include "targetver.h"
//
// #define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 일부 CString 생성자는 명시적으로 선언됩니다.
//
// // MFC의 공통 부분과 무시 가능한 경고 메시지에 대한 숨기기를 해제합니다.
// #define _AFX_ALL_WARNINGS
//
// #include <afxwin.h>         // MFC 핵심 및 표준 구성 요소입니다.
// #include <afxext.h>         // MFC 확장입니다.
//
//
// #include <afxdisp.h>        // MFC 자동화 클래스입니다.
//
//
//
// #ifndef _AFX_NO_OLE_SUPPORT
// #include <afxdtctl.h>           // Internet Explorer 4 공용 컨트롤에 대한 MFC 지원입니다.
// #endif
// #ifndef _AFX_NO_AFXCMN_SUPPORT
// #include <afxcmn.h>             // Windows 공용 컨트롤에 대한 MFC 지원입니다.
// #endif // _AFX_NO_AFXCMN_SUPPORT
//
// #include <afxcontrolbars.h>     // MFC의 리본 및 컨트롤 막대 지원
//
//
// #include <afxsock.h>            // MFC 소켓 확장
//
//
//
//
//
//
//
// #ifdef _UNICODE
// #if defined _M_IX86
// #pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
// #elif defined _M_X64
// #pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
// #else
// #pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
// #endif
// #endif
//
//
// #define _USE_MATH_DEFINES
//
//
// // VS2012 이상에서 TRACE를 변경하기 위함.
// #if _MSC_VER > 1600
//
//
// #ifdef _MSC_VER
//
// #ifdef _LOG_ANALTYPE_
// #define printf  _TRACE
// #else
//
//
// #endif
//
// #endif
//
//
// #undef TRACE
// #ifdef _LOG_ANALTYPE_
// #define TRACE _TRACE
// #else
// #define TRACE printf
// #endif
//
// #ifdef _DEBUG
//
//
//
// #else
//
// //#define TRACE false && _TRACE
//
// #endif
//
//
//
// #ifdef __cplusplus
// extern "C" {
// #endif
// void _TRACE(char *format, ...);
//
// //bool _TRACE(CString strFormat, ...);
//
// #ifdef __cplusplus
// }
// #endif
//
//
//
// #endif
//
// #endif // _MSC_VER
//
//
//