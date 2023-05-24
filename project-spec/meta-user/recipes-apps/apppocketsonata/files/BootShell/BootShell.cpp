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

//////////////////////////////////////////////////////////////////////////
// 전역 변수 및 객체 정의
CManSbc *theManSbc=0;
//CManFlash *theManFlash=0;
CBootShell *theBootShell=0;
CFileTar *theFileTar=0;

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

    OutputDebugString( buffer );

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

    time_t rawtime;
    struct tm * timeinfo;

	// floating format 연산 에러로 반드시 추가해야 함.
	// vxworks 에서 해준다하던데.. 실행이 안 되는 것 같음.
	//floatInit();

    theFileTar = new CFileTar;
    if( theFileTar == NULL ) {
        PrintErr( ( "\n [W] 기본 메모리(theFileTar)가 부족합니다 !" ) );
        WhereIs;
    }

#ifdef _NETMEM_
    theServerSocket = new ServerSocket( enMAXPRC, sizeof(STR_NETMEM) );
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

	theManSbc = new CManSbc;
	if( theManSbc == NULL ) {
        PrintErr( ( "\n [W] 기본 메모리(theManSbc)가 부족합니다 !" ) );
		WhereIs;
	}

	theBootShell = new CBootShell;
	if( theBootShell == NULL ) {
        PrintErr( ( "\n [W] 기본 메모리(theBootShell)가 부족합니다 !" ) );
		WhereIs;
	}

    time( & rawtime );
    timeinfo = localtime ( & rawtime );
    printf( "\n\n ---------------------------------------------------------------------" );
    printf ( "\n 실행 시간: %s", asctime (timeinfo) );
    printf( "\n\n ---------------------------------------------------------------------" );

	theBootShell->Run();

    delete theFileTar;
    delete theBootShell;
    delete theManSbc;

#ifdef _NETMEM_
    Sleep( 10 );

    delete theServerSocket;
#endif

}

void GetKey()
{
    int key;
    key = theManSbc->GetCommand();
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
    theManSbc->ShowNetMemory();

	printf( "\n\n 키 값 (기본=OFP Download/TFFS 파일 설치[w]/응용 프로그램 업데이트[1]/Run OFP in Flash) ? " );
    key = theManSbc->GetCommand();

    switch( key ) {
        case INSTALL_WEB :      // w 키
            theManSbc->InstallWeb();
            break;

        case RUN_APP :
        	theManSbc->InitDataBase();
            theManSbc->RunApp( enTffsApp );
            break;

        case WRITE_APP_FLASH :  // 1 키
            theManSbc->DownloadAndROMWriteApp();
            break;

        case DOWNLOAD_APP :
        	theManSbc->InitDataBase();
            theManSbc->DownloadApp();
            theManSbc->RunApp( enDownloadApp );
            break;

        default :
            break;
    }

}


