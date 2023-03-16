// BootShellmain.h: interface for the BootShellMain
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOOTSHELLMAIN_H__93E04DDF_CE5E_4DB7_95B5_D35B77F287E7__INCLUDED_)
#define AFX_BOOTSHELLMAIN_H__93E04DDF_CE5E_4DB7_95B5_D35B77F287E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Macros.h"

#define VERSION					"Ver 1.0"

//#define tPRI_Ref				90

// MBIT 프로그램, 사용자 프로그램, 부트 쉘 프로그램의 메인 타스크의 Priority
enum { tPRI_HTTPDAEMON=150, tPRI_BOOTSHEL=1, tPRI_App=200 };

#define CTRL_X						(24)
#define REBOOT						CTRL_X


//////////////////
// SNTP 프로토콜 정의
#define TRY_GETSNTP                 (3)
#define SNTP_SERVER_IP				((char *)"192.168.1.100")

void LoadBootParameter();
void PCIConfigSetting();

//////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif

void BootShellMain();

//void SetRtcClock( UINT date, UINT time );
//UINT GetDate( char *pDate );
//UINT GetTime( char *pTime );

IMPORT UINT32 univBaseAdrs;

#ifdef __cplusplus
}
#endif


#endif // !defined(AFX_BOOTSHELLMAIN_H__93E04DDF_CE5E_4DB7_95B5_D35B77F287E7__INCLUDED_)
