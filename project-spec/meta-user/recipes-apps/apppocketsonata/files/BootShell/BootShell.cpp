// BootShell.cpp: implementation of the CBootShell class.
//
//////////////////////////////////////////////////////////////////////

#include "pch.h"

#include <time.h>
#include <math.h>
#include <ctype.h>
#include <stdio.h>

#ifdef __VXWORKS__
#include <ioLib.h>
#include <errnoLib.h>
#include <sysSymTbl.h>
#include <loadLib.h>
#include <usrLib.h>
#include <cacheLib.h>

#include <iv.h>
#include <sysLib.h>
#include <intLib.h>
#include <arch/ppc/vxPpcLib.h>

//#include "lsv70a.h"

#include <rebootLib.h>
//#include <usrConfig.h>

#include "prjParams.h"

#endif

#include "BootShellMain.h"

#include "ManSbc.h"
//#include "ManFlash.h"

#include "./Untar/FileTar.h"

#include "BootShell.h"

#ifdef _NETMEM_
#include "../NetMem/server/ServerSocket2.h"
#include "../NetMem/utils/PortableSocket.h"

#endif

#include "../Anal/INC/PDW.h"

#include "../System/csysconfig.h"

//////////////////////////////////////////////////////////////////////////
// 전역 변수 및 객체 정의
CManSbc *g_theManSbc=0;
//CManFlash *theManFlash=0;
CBootShell *theBootShell=0;
CFileTar *g_theFileTar=0;

CSysConfig *g_pTheSysConfig;

#ifdef _NETMEM_
ServerSocket *theServerSocket=0;

#endif

#ifdef __cplusplus
extern "C" {
#endif

IMPORT int USER_FLASH_Unlock();

#ifdef __VXWORKS__
IMPORT BOOT_PARAMS g_stBootParams;
#endif


void re();

void GetKey();


#ifdef __cplusplus
}
#endif

ENUM_UnitType g_enUnitType;
char g_szBitResult[2][10] = { "비정상", "정상" };

#ifdef _MSC_VER
void _TRACE( char *format, ... )
{
    char buffer[1000];
    va_list argptr;

    va_start( argptr, format );
    vsprintf( buffer, format, argptr );
    va_end( argptr );

    printf( buffer );

    //return true;

}

#endif


//////////////////////////////////////////////////////////////////////////
/*! \brief    BootShellMain
		\author   조철희
		\return   void
		\version  0.0.1
		\date     2008-04-18 09:58:51
		\warning
*/
void BootShellMain()
{

    g_theFileTar = new CFileTar;
    if( g_theFileTar == NULL ) {
        PrintErr( ( "\n [W] 기본 메모리(theFileTar)가 부족합니다 !" ) );
        WhereIs;
    }

#ifdef _NETMEM_
    theServerSocket = new ServerSocket( enMAXPRC, sizeof( struct STR_NETMEM) );
    if( theServerSocket == NULL ) {
        PrintErr( ( "\n [W] 기본 메모리(theServerSocket)가 부족합니다 !" ) );
        WhereIs;
    }
    else {
//        int i;
//         for( i=0 ; i < enMAXPRC; i++ ) {
//             MemoryPage *page = theServerSocket->pages[i];
//
//             unsigned char *mem = page->Lock( 0 );
//             memcpy( mem + i * sizeof( long ), &tmp, sizeof( long ) );
//             page->Unlock( 0, 0 );
//         }

        theServerSocket->StartThreadSocket( NET_MEM_PORT );

    }
#endif

#ifdef __VXWORKS__
    // ATA 드라이브, PS 로직 마운트 때문에 지연 추가
    printf( "\n PS 로직 부팅으로 무려 30초씩이나 대기 합니다...\n" );
    Sleep( 30 );
    printf( "\n $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" );

#endif

    g_theManSbc = new CManSbc;
    if( g_theManSbc == NULL ) {
        PrintErr( ( "\n [W] 기본 메모리(theManSbc)가 부족합니다 !" ) );
        WhereIs;
    }

    g_pTheSysConfig = new CSysConfig();
    if( g_pTheSysConfig == NULL ) {
        PrintErr( ( "\n [W] 기본 메모리(g_pTheSysConfig)가 부족합니다 !" ) );
        WhereIs;
    }
    else {
        g_pTheSysConfig->SetBoardID( g_theManSbc->GetBoardID() );

        g_pTheSysConfig->DisplaySystemVar();
    }

    // 네트워크 설정
    g_theManSbc->AutoIPAddress();

    // 마운트
    g_theManSbc->MountDrive();

    // 네트워크 설정
    g_theManSbc->SetTimeBySNMP();

    //
    g_theManSbc->CreateUDPServer();

    //
    g_theManSbc->KeyboardHooking();

	theBootShell = new CBootShell;
	if( theBootShell == NULL ) {
        PrintErr( ( "\n [W] 기본 메모리(theBootShell)가 부족합니다 !" ) );
		WhereIs;
	}

//     time_t rawtime;
//     struct tm *timeinfo;
//     time( & rawtime );
//     timeinfo = localtime ( & rawtime );
//     char *pStr = asctime( timeinfo );
//     printf( "\n 실행 시간: %s", pStr );

	theBootShell->Run();

    delete g_theFileTar;
    delete theBootShell;

#ifdef _MSC_VER
    delete g_theManSbc;
#endif

    // 시스템 환경 설정은 살려둡니다.
    // delete g_pTheSysConfig;


#ifdef _NETMEM_
    Sleep( 10 );

    delete theServerSocket;
#endif

}

void GetKey()
{
    int key;
    key = g_theManSbc->GetCommand();
    printf( "\n key=[%d]" , key );

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    Run
	\author   조철희
	\return   void
	\version  0.0.29
	\date     2008-07-10 16:03:52
	\warning
*/
void re()
{
	//theBootShell->Unload();
	//theBootShell->DeleteAllTask();
	//theBootShell->Run();
	// unld( )
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**
 * @brief     CBootShell
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-05 12:53:52
 * @warning
 */
CBootShell::CBootShell()
{

}

/**
 * @brief		~CBootShell
 * @return
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/04/21 10:58:50
 * @warning
 */
CBootShell::~CBootShell()
{

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CBootShell::Run
		\author   조철희
		\return   void
		\version  0.0.1
		\date     2008-04-18 09:59:26
		\warning
*/
void CBootShell::Run()
{
	UCHAR key;

    // 네트워크 메모리 값 전시합니다.
    g_theManSbc->ShowNetMemory();

	printf( "\n\n 키 값 (기본=이미지 실행[1]/기본 파일 설치[w]/소프트웨어 업데이트[!]) ? " );
    key = g_theManSbc->GetCommand();

    key = DOWNLOAD_APP;

    printf( "\n\n" );
    switch( key ) {
        case INSTALL_WEB :
            g_theManSbc->InstallWeb();
            break;

        case RUN_APP :
        	g_theManSbc->InitDataBase();
            g_theManSbc->RunApp( enATAApp );
            break;

        case WRITE_APP_FLASH :
            g_theManSbc->DownloadAndROMWriteApp();
            g_theManSbc->RunApp( enATAApp );
            break;

        case DOWNLOAD_APP :
        	g_theManSbc->InitDataBase();
            g_theManSbc->DownloadApp();
            g_theManSbc->RunApp( enDownloadApp );
            break;

        default :
            break;
    }

}


