// BootShell.h: interface for the CBootShell class.
//
//////////////////////////////////////////////////////////////////////


#pragma once


#ifdef __VXWORKS__
#include <vxworks.h>
#include <memLib.h>
#include <moduleLib.h>


#endif


#include "../Anal/INC/OS.h"

#include "Macros.h"

#include "BootShellMain.h"



// 부트 쉘 명령어 정의
enum {
    RUN_APP=0,
	DOWNLOAD_APP,           // 운용 프로그램 다운로드

	WRITE_APP_FLASH,

	INSTALL_WEB,            // SBC 환경 설정

	DOWNLOAD_UTEST_PROG,
	WRITE_UTEST_PROG,
	RUN_UTEST_PROG,
	WRITE_BOOT_PROG,
	RUN_BOOT_PROG,

	DEBUG_APP
} ;

// 키보드 타임아웃 설정 값
#define KEYBOARD_TIMEOUT					(5)



//////////////////////////////////////////////////////////////////////////
// 장치 관련 드라이브 정의

#define	EIDDISK										"EIDDISK:"
#define	RAMDRV										(char *) "/RAMDRV"
#define	RAMDRV_NO									(char *) ":0"
#define	TFFSDRV										(char *) "/tffs1"

#if defined(__LP64__)
#define	ATADRV										(const char *) "/ata0"
#else
#ifdef _MSC_VER
#define	ATADRV										(char *) "/ata0:0"
#else
#define	ATADRV										(const char *) "/ata0:0"
#endif
#endif

#define	LOGDISK										"LOGDISK:"


//////////////////////////////////////////////////////////////////////
// 파일 정의
#define WEB_FILENAME				                ((char *) "tftpboot.tar")
#define WEB_FOLDER				                    ((char *) "Web")

//#define BLK_EMITTER_SQLITE_FILENAME					((char *) "emitter_blank.sqlite3")
//#define EMITTER_SQLITE_FILENAME						((char *) "emitter.sqlite3")
//#define SQLITE_FOLDER								((char *) "LIB")

//#define CEDEOB_SQLITE_FILENAME      				((char *) "cedeob.sqlite3")


//#define INI_FOLDER                  				((char *) "INI")
//#define INI_FILENAME                				((char *) "sysconfig.ini")

#define IMAGE_FOLDER                                "/BIN"

#ifdef __VXWORKS__
#if defined(__LP64__)
#define APP_FILENAME				                ((char *) "VSIGA64.out")
#else
#define APP_FILENAME				                ((char *) "VSIGA.out")
#endif
#else
#define APP_FILENAME				                ((char *) "VSIGA.out")
#endif

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
									taskPrioritySet( taskNameToId( (char *) "tShell0" ), _tShell_priority );

#else
#define GetCharX					getchar();
#endif


struct STR_NETMEM {
    unsigned int uiSBCID;

}  ;


#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////////////////////////
// 부투 메인 함수
void BootShellMain();


//////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

class CBootShell
{
private:
	MODULE *m_pModuleId;				// 시작 포인터

private:
	void KeyHook();

public:
	void Run();
	CBootShell();
	virtual ~CBootShell();

};

#endif


