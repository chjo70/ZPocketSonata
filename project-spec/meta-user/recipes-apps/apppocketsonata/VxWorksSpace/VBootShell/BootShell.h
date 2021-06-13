// BootShell.h: interface for the CBootShell class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOOTSHELL_H__F950734C_228A_4C0B_8B29_7547A0BA0978__INCLUDED_)
#define AFX_BOOTSHELL_H__F950734C_228A_4C0B_8B29_7547A0BA0978__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _WIN32
#include "moduleLib.h"

#endif

#include "Macros.h"

#include "BootShellMain.h"



// Ű���� ��ɾ�
enum { DOWNLOAD_APP=0, WRITE_APP_FLASH, RUN_APP, INSTALL_WEB, DOWNLOAD_UTEST_PROG, WRITE_UTEST_PROG, RUN_UTEST_PROG, WRITE_BOOT_PROG, RUN_BOOT_PROG } ;

// Ű���� Ÿ�� �ƿ� ������
#define KEYBOARD_TIMEOUT					(3)



//////////////////////////////////////////////////////////////////////////
// �� ����̺� �� ���� �� ���ϸ� ����

#define	EIDDISK										"EIDDISK:"
#define	RAMDRV										(char *) "/RAMDRV"
#define	RAMDRV_NO									(char *) ":0"
#define	TFFSDRV										(char *) "/tffs0"

#define	LOGDISK										"LOGDISK:"


//////////////////////////////////////////////////////////////////////
// 파일 정의
#define WEB_FILENAME				                ((char *) "Web.tar")
#define WEB_FOLDER				                    ((char *) "Web")

#define APP_FILENAME				                ((char *) "VSIGA.out")

//////////////////////////////////////////////////////////////////////
// 타스크명 정의
#define APP_TASKNAME				                ((char *) "tApp")


//////////////////////////////////////////////////////////////////////////

#ifdef INCLUDE_SHELL
static int _tShell_priority;
#endif

#ifdef INCLUDE_SHELL
#define	GetCharX					taskPriorityGet( taskNameToId( (char *)"tShell0" ), & _tShell_priority );	\
													taskPrioritySet( taskNameToId( (char *) "tShell0" ), 255 ); \
													getchar();	\
													taskPrioritySet( taskNameToId( (char *) "tShell0" ), _tShell_priority );
#else
#define GetCharX					getchar();
#endif


#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////////////////////////
// �Լ� ����
void BootShellMain();


//////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

class CBootShell  
{
private:
	MODULE *m_pModuleId;				// module�� �������� ������ ������ ����ü

public:
	void Run();
	CBootShell();
	virtual ~CBootShell();

};

#endif

#endif // !defined(AFX_BOOTSHELL_H__F950734C_228A_4C0B_8B29_7547A0BA0978__INCLUDED_)
