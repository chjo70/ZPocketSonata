/**

    @file      cmain.cpp
    @brief     시작 함수 힙니다. 초기 작업 환경을 구성하고 타스크를 생성 합니다.
    @details   ~
    @author    조철희
    @date      27.03.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#include "stdafx.h"


#ifdef _MSC_VER

//#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <afxmt.h>
#include <direct.h>
//#include <xutility>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#elif defined(__VXWORKS__)


#include <memPartLib.h>
#include <stdlib.h>
#include <stdio.h>

#include <taskLib.h>
#include <private/kwriteLibP.h>
#include <usrFsLib.h>
#include <hostlib.h>

#include <nfs/nfsDriver.h>


#else

#endif

#include <iostream>

using namespace std;

// Main() 함수에 아래2가지를 정의해야 한다.
#define _MAIN_
#define _MAIN_GLOBALS_

#include <signal.h>
#include <cassert>

#include "cmain.h"
#include "./Thread/ctaskmngr.h"
#include "./Utils/clog.h"
//#include "./Utils/csingleserver.h"
#include "./Utils/csingleclient.h"
#include "./Thread/coperationconsole.h"
#include "./Thread/curbit.h"
#include "./Thread/csignalcollect.h"
#include "./Thread/ccgi.h"
#include "./Thread/cusercollect.h"

#include "./System/csysconfig.h"

#include "./Utils/ccommonutils.h"

#include "./Include/globals.h"

//char g_szPDWScinarioFile[100];



#ifdef __cplusplus

extern "C"
{
#endif

    void usrAppStart( int iArgc, char *iArgv[] );
    void ss();
    ENUM_BoardID GetBoardID();

    void pci_enable();
    void pci_disable();

    void MemotyTest( size_t iSize );

    void Check64bitArithmetic();

    extern vector<CThread *> g_vecThread;


#ifdef __cplusplus
}
#endif

void signalHandler( int signo );

void CreateMngrThread();
void CreateAnalThread();


enum ENUM_COPY_ERROR {
    ENUM_EMITTER_ERROR=0,
    ENUM_CEDEOB_ERROR
} ;


/**
 * @brief     InitDatabase
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-09-17, 10:48
 * @warning
 */
void CMain::InitDatabase()
{
    int iCopy = 1;

    char szSrcFilename[100], szDstFilename[100];

    // 1. 위협 라이브러리 존재 확인
    LOG_LINEFEED;

#ifdef _SQLITE_
    try {
        Log( enNormal, "#### SQLITE 모드 입니다. ####" );

#ifdef __linux__
        if( 0 == mkdir( EMITTER_SQLITE_FOLDER, 0766 ) || errno == EEXIST ) {
        }
#elif _MSC_VER
        char szSQLiteFileName[100];

        if( 0 == _mkdir( EMITTER_SQLITE_FOLDER ) || errno == EEXIST ) {
            // 1. 위협 관리 테이블
            strcpy( szSQLiteFileName, EMITTER_SQLITE_FOLDER );
            strcat( szSQLiteFileName, "/" );

#ifdef _MSC_VER
            sprintf( szDstFilename, "%s_%d.sqlite3", EMITTER_SQLITE_FILENAME, g_enBoardId );
            strcat( szSQLiteFileName, szDstFilename );
#else
            strcat( szSQLiteFileName, EMITTER_SQLITE_FILEEXTNAME );
#endif

            sprintf( szSrcFilename, "../../files/SQLite3.DB/%s", BLK_EMITTER_SQLITE_FILENAME );
            iCopy = CCommonUtils::CopySrcToDstFile( szSrcFilename, szSQLiteFileName, 1, 0077 );
            if( iCopy <= 0 ) {
                throw ENUM_EMITTER_ERROR;
            }

            // 2. 위협 라이브러리 관리 테이블
            strcpy( szSQLiteFileName, CEDEOB_SQLITE_FOLDER );
            strcat( szSQLiteFileName, "/" );
            strcat( szSQLiteFileName, CEDEOB_SQLITE_FILENAME );

            sprintf( szSrcFilename, "../../files/SQLite3.DB/%s", BLK_CEDEOB_SQLITE_FILENAME );
            iCopy = CCommonUtils::CopySrcToDstFile( szSrcFilename, szSQLiteFileName, 1, 0077 );
            if( iCopy <= 0 ) {
                throw ENUM_CEDEOB_ERROR;
            }

        }

#elif defined(__VXWORKS__)

#ifdef _POCKETSONATA_

        // 1. 위협 관리 테이블 복사
        sprintf( szSrcFilename, "%s/%s/%s", ATADRV, SQLITE_DIRECTORY, BLK_EMITTER_SQLITE_FILENAME );
        sprintf( szDstFilename, "%s%s/%s/%s", RAMDRV, RAMDRV_NO, SQLITE_DIRECTORY, EMITTER_SQLITE_FILEEXTNAME );
        Log( enNormal, "원본 위협관리 파일[%s]을 램 드라이브[%s]에 복사합니다.", szSrcFilename, szDstFilename );

        if( OK == mkdir( EMITTER_SQLITE_FOLDER ) || errno == EEXIST ) {
            iCopy = CCommonUtils::CopySrcToDstFile( szSrcFilename, szDstFilename, 1, 0077 );

            if( iCopy <= 0 ) {
                throw ENUM_EMITTER_ERROR;
            }
        }
        else {
            Log( enError, "[%s] 드라이브에 폴더를 생성하지 못합니다... 관리자에게 [%d] 문의하세요.", EMITTER_SQLITE_FOLDER, errno );
        }

        Log( enLineFeed, "" );

        // 2. CED/EOB 테이블 복사
        sprintf( szSrcFilename, "%s/%s/%s", ATADRV, SQLITE_DIRECTORY, CEDEOB_SQLITE_FILENAME );
        sprintf( szDstFilename, "%s%s/%s/%s", RAMDRV, RAMDRV_NO, SQLITE_DIRECTORY, CEDEOB_SQLITE_FILENAME );
        Log( enNormal, "원본 CED/EOB 파일[%s]을 램 드라이브[%s]에 복사합니다.", szSrcFilename, szDstFilename );

#if 1
        iCopy = CCommonUtils::CopySrcToDstFile( szSrcFilename, szDstFilename, 1, 0077 );

        if( iCopy <= 0 ) {
            throw ENUM_CEDEOB_ERROR;
        }
#else
        if( OK == mkdir( CEDEOB_SQLITE_FOLDER ) || errno == EEXIST ) {
            iCopy = CCommonUtils::CopySrcToDstFile( szSrcFilename, szDstFilename, 1, 0077 );

            if( iCopy <= 0 ) {
                throw ENUM_CEDEOB_ERROR;
            }
        }
        else {
            Log( enError, "[%s] 드라이브에 폴더를 생성하지 못합니다... 관리자에게 [%d] 문의하세요.", CEDEOB_SQLITE_FOLDER, errno );
        }
#endif

#else
        Log( enNormal, "CED/EOB 파일을 램 드라이브에 설치 합니다." );
        if( OK == mkdir( CEDEOB_SQLITE_FOLDER ) || errno == EEXIST ) {
            sprintf( szSrcFilename, "%s/%s/%s", TFFSDRV, SQLITE_FOLDER, CEDEOB_SQLITE_FILENAME );
            sprintf( szDstFilename, "%s%s/%s/%s", RAMDRV, RAMDRV_NO, SQLITE_DIRECTORY, CEDEOB_SQLITE_FILENAME );
            iCopy = CCommonUtils::CopySrcToDstFile( szSrcFilename, szDstFilename, 1, 0077 );

            if( iCopy <= 0 ) {
                throw ENUM_CEDEOB_ERROR;
            }
        }
        else {
            Log( enError, "[%s] 드라이브에 폴더를 생성하지 못합니다... 관리자에게 [%d] 문의하세요.", EMITTER_SQLITE_FOLDER, errno );
        }

#endif

#if 0
        Log( enNormal, "임시 파일을 램 드라이브에 설치 합니다." );
        if( OK == mkdir( CEDEOB_SQLITE_FOLDER ) || errno == EEXIST ) {
            sprintf( szSrcFilename, "%s/temp.log", ATADRV );
            sprintf( szDstFilename, "%s%s/%s/temp.log", RAMDRV, RAMDRV_NO, SQLITE_DIRECTORY );
            iCopy = CCommonUtils::CopySrcToDstFile( szSrcFilename, szDstFilename, 1, 0077 );

            if( iCopy <= 0 ) {
                throw ENUM_CEDEOB_ERROR;
            }
        }
        else {
            Log( enError, "[%s] 드라이브에 폴더를 생성하지 못합니다... 관리자에게 [%d] 문의하세요.", EMITTER_SQLITE_FOLDER, errno );
        }


#endif


#else
        if( 0 == mkdir( EMITTER_SQLITE_FOLDER ) || errno == EEXIST ) {
        }
#endif

    }
    catch( int eException ) {

        switch( eException ) {
            case ENUM_EMITTER_ERROR:
                Log( enError, "위협 관리 테이블[%s]이 SSD[%s]에 존재하지 않습니다. 관리자에게 문의하세요.", BLK_EMITTER_SQLITE_FILENAME, szSrcFilename );
                while( true ) {
                }

                break;

            case ENUM_CEDEOB_ERROR:
                Log( enError, "CED/EOB 테이블[%s]이 NFS[%s] 에 존재하지 않아 SDD에 있는 최근 파일로 대체 합니다. 운용 콘솔에서 다운로드 요청해서 동기화 부탁합니다 !", CEDEOB_SQLITE_FILENAME, szSrcFilename );
#ifdef __VXWORKS__
                // 2. CED/EOB 테이블 복사 (ATA0 드라이브부터)
                sprintf( szSrcFilename, "%s/%s/%s", ATADRV, SQLITE_DIRECTORY, CEDEOB_SQLITE_FILENAME );
                sprintf( szDstFilename, "%s%s/%s/%s", RAMDRV, RAMDRV_NO, SQLITE_DIRECTORY, CEDEOB_SQLITE_FILENAME );
                Log( enNormal, "CED/EOB 파일[%s]을 램 드라이브[%s]에 설치 합니다.", szSrcFilename, szDstFilename );

                iCopy = CCommonUtils::CopySrcToDstFile( szSrcFilename, szDstFilename, 1, 0077 );
                if( iCopy <= 0 ) {
                    Log( enError, "복사 실패했습니다 !" );
                }
#endif
                break;

            default:
                break;

        }

        WhereIs;
    }


#elif _MSSQL_
    Log( enNormal, "#### MSSQL 모드 입니다. ####" );

#else
    Log( enNormal, "#### NO_SQLITE 모드 입니다. ####" );

#endif


}

#if 0
#include "./NetMem/utils/PortableSocket.h"
#include "./NetMem/client/NetworkMemory2.h"
#include "./NetMem/server/ServerSocket.h"

NetworkMemory *pTheNetMem;

#define DISTRIB_LENGTH  10
#define NO_GENES_POOL   5

#endif

/**
 * @brief     Start
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-06-08, 11:43
 * @warning
 */
void Start( int iArgc, char *iArgv[], void *pParent )
{
    CMain theMain( "MAN" );

    //SetConsoleOutputCP(65001);
    g_enLogAnalType = enALL;

#if 0
    int port = 10001;

    INIT_SOCKETS_LIB;
    int noPages = NO_GENES_POOL + 1;
    ServerSocket *pTheServer = new ServerSocket( noPages, DISTRIB_LENGTH * 4 );

    //Initialize the first page with the number to be factorized
    unsigned long init10[10] = { 3,234,43,44,44,231,ULONG_MAX,34,2,2 };

    MemoryPage *page = pTheServer->pages[0];
    page->Lock( 0 );
    page->Unlock( ( unsigned char * ) init10, 0 );
    // srand( time( NULL ) );
    for( int i = 1; i < noPages; i++ ) {
        MemoryPage *page = pTheServer->pages[i];
        unsigned char *mem = page->Lock( 0 );
        for( int i = 0; i < DISTRIB_LENGTH; i++ ) {
            unsigned long tmp = rand();
            memcpy( mem + i * sizeof( long ), &tmp, sizeof( long ) );
        }

        page->Unlock( 0, 0 );
    }
    pTheServer->StartThreadSocket( port );

    RELEASE_SOCKETS_LIB;

    NetworkMemory netMem( "127.0.0.1", port );

    NetMemCommand command;
    command.offset = 0;
    netMem.ReadPage( &command );

#endif

#ifdef __VXWORKS__
    Check64bitArithmetic();

#endif

    // 로그 객체를 생성한다.
#ifdef __VXWORKS__
    g_pTheLog = new CLog( en_LOG_PRIORITY, ( const char * ) "LOG", true );
    g_pTheLog->Run();

#else
    // g_pTheLog = new CLog();
    g_pTheLog = new CLog( en_LOG_PRIORITY, ( const char * ) "LOG", true );
    g_pTheLog->Run();

#endif

    signal( SIGINT, signalHandler );
    signal( SIGABRT, signalHandler );
    signal( SIGTERM, signalHandler );


#ifdef __linux__
    signal( SIGHUP, signalHandler );
    signal( SIGSTOP, signalHandler );
#endif



#ifdef _MSC_VER
    setlocale( LC_ALL, "Korean" );
#else
    setlocale( LC_ALL, "C" );
#endif

#if 0
    char buffer[5100];

    int i;
    for( i = 0; i < 5000; ++i ) {
        buffer[i] = 'A' + ( i % 20 );
    }
    buffer[i] = 0;
    Log( enNormal, "[%s]", buffer );
#endif

    TRACE( "\n\n" );

    theMain.Run( iArgc, iArgv, pParent );

#ifdef __VXWORKS__
    Sleep( 100 );

#endif

}

/**
 * @brief     CMain
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2024-01-29 16:25:00
 * @warning
 */
CMain::CMain()
{

#if 0
    enum class ENUM_TYPE : unsigned char {
        enum_1,
        enum_2,
    };

    ENUM_TYPE enType;

    enType = ENUM_TYPE::enum_1;

    int c = sizeof( enType );
#endif

}


/**
 * @brief     CMain
 * @param     const char * pThreadName
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2024-01-31 19:12:05
 * @warning
 */
CMain::CMain( const char *pThreadName ) : CLogName( pThreadName )
{

}

/**
 * @brief     ~CMain
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-05-02 14:31:56
 * @warning
 */
CMain::~CMain()
{

}

/**
 * @brief     Run
 * @param     int iArgc
 * @param     char * iArgv[]
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-05-02 14:32:27
 * @warning
 */
void CMain::Run( int iArgc, char *iArgv[], void *pParent )
{
    //LOGENTRY;
    m_pParent = pParent;

    m_tiNow = time( NULL );

    ParsingArgument( iArgc, iArgv );

    _ShowProgramTitle();

    // 파일 정보를 전시 합니다.
    Log( enNormal, "[%s] 파일 위치는 [%s]에 입니다.", INI_FILENAME, INI_FOLDER );
    Log( enNormal, "NFS 드라이브는 [%s] 입니다.", SHARED_DATA_DIRECTORY );
    Log( enNormal, "로그 디렉토리는 [%s] 입니다.", g_pTheLog->GetLogDirectory() );
    Log( enNormal, "로그 파일명은 [%s] 입니다.", g_pTheLog->GetLogFullName() );

#ifdef _SQLITE_
    Log( enNormal, "CED/EOB 데이터베이스 파일 위치 및 파일명[%s, %s]", CEDEOB_SQLITE_FOLDER, CEDEOB_SQLITE_FILENAME );
    Log( enNormal, "에미터 데이터베이스 파일 위치 및 파일명[%s, %s]", EMITTER_SQLITE_FOLDER, EMITTER_SQLITE_FILEEXTNAME );

#endif

    InitDatabase();

    LOG_LINEFEED;
    LOG_LINEFEED;

#if 1

#if 0
    struct timespec tsDiff, tsCollectStart;

    int iRate;
    struct tm stTime;
    char szString[100];
    struct timespec stTimeSpec;

	iRate = sysClkRateGet();
    printf( "sysClkRateGet[%d]\n", iRate );

    struct timespec res;

    // 1. CLOCK_MONOTONIC
    clock_getres( CLOCK_MONOTONIC, &res );
    printf( "CLOCK_MONOTONIC: %ldns\n", res.tv_nsec );

    clock_gettime( CLOCK_MONOTONIC, & stTimeSpec );
    localtime_s( & stTime, & stTimeSpec.tv_sec );
    strftime( szString, sizeof(szString), "%Y_%m_%d %H_%M_%S", & stTime );
    printf( "현재 시간 : %s\n", szString );

    // 2. CLOCK_REALTIME
    clock_getres( CLOCK_REALTIME, & res );
    printf( "CLOCK_REALTIME: %ldns\n", res.tv_nsec );

    clock_gettime( CLOCK_REALTIME, & stTimeSpec );
    localtime_s( & stTime, & stTimeSpec.tv_sec );
    strftime( szString, sizeof( szString ), "%Y_%m_%d %H_%M_%S", & stTime );
    printf( "현재 시간 : %s\n", szString );

    CCommonUtils::GetCollectTime( & tsCollectStart );
    taskDelay( 1 );

    CCommonUtils::DiffTimespec( & tsDiff, & tsCollectStart );

    Log( enNormal, "소요 시간 [%d.%03d s]", tsDiff.tv_sec, tsDiff.tv_nsec / 1000000 );
#endif


#endif

#ifdef _MSC_VER
    char buffer[100];

    sprintf( buffer, "%s%s", SHARED_DATA_DIRECTORY, DDR_DIRECTORY );
    _mkdir( buffer );

#endif

    // 분석 관련 쓰레드를 생성합니다.
    CreateAnalThread();

    // 관리 관련 쓰레드를 생성합니다.
    CreateMngrThread();

#ifdef _MSC_VER
    // 공유 디렉토리의 수집 데이터 모두 삭제하기
    g_pTheDetectAnalysis->DeleteAllFiles();

#endif

#if 0
    _TOA *px;
    unsigned int *pux;

    int i, j;
    struct timespec nowTime;

    char buffer[200];

    px = ( _TOA * ) malloc( sizeof( _TOA ) * 10000 );
    pux = ( unsigned int * ) px;

    while( true ) {
        CCommonUtils::GetCollectTime( &nowTime );

        for( j = 0; j < 1000; ++j ) {
            for( i = 0; i < 10000; ++i ) {
                px[i] = i;
            }
            for( i = 0; i < 9999; ++i ) {
                px[i] = px[i + 1] - px[i];
            }
        }

        sprintf( buffer, "================ 64비트 소요 시간 : %d[ns]", ( int ) ( ( CCommonUtils::GetDiffTime( &nowTime ) ) ) );
        CCommonUtils::WallMakePrint( buffer, '=' );
        puts( buffer );

        CCommonUtils::GetCollectTime( &nowTime );
        for( j = 0; j < 1000; ++j ) {
            for( i = 0; i < 10000; ++i ) {
                pux[i] = i;
            }
            for( i = 0; i < 9999; ++i ) {
                pux[i] = pux[i + 1] - pux[i];
            }
        }

        sprintf( buffer, "================ 32비트 소요 시간 : %d[ns]", ( int ) ( ( CCommonUtils::GetDiffTime( &nowTime ) ) ) );
        CCommonUtils::WallMakePrint( buffer, '=' );
        puts( buffer );


        Sleep( 1 );
    }

    free( px );

    while( 1 );
#endif

#ifdef __VXWORKS__
    //WhereIs;
    //g_pTheTaskMngr->QMsgSnd( enREQ_OP_START, "CMain()" );

#endif

    // g_pTheTaskMngr->SetMode( enREADY_MODE );


    // 9. 마지막으로 키 입력 처리를 호출한다.
#ifndef _DAEMON_
    //PROMPT->Run( _MSG_PROMPT_KEY );
#endif

}

/**
 * @brief		CreateMngrThread
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/02/13 13:40:10
 * @warning
 */
void CMain::CreateMngrThread()
{

#ifdef __VXWORKS__
    //g_pTheSysConfig->DisplaySystemVar();

#else
    if( g_pTheSysConfig == NULL ) {
        g_pTheSysConfig = new CSysConfig();
    }
    else {
        g_pTheSysConfig->DisplaySystemVar();
    }

#endif

#ifdef _LOG_ANALTYPE_
#ifdef _MSC_VER

    g_enLogAnalType = enDETSCN_ANAL;

#else

    g_pTheSysConfig->DisplaySystemVar();
    if( g_pTheSysConfig->GetDevelop() == 0 ) {
        // 모든 로그 출력 최소화하게 설정
        g_enLogAnalType = enCLEAR_ANAL;
    }
    else {
        g_enLogAnalType = enDETSCN_ANAL; // enDETTRKSCN_ANAL; // enDET_ANAL; // enSCN_ANAL;
    }

#endif

#endif

    // 1. 쓰레드 관리 쓰레드를 호출한다.
#ifdef _SQLITE_
    char szSQLiteFileName[100];
    strcpy( szSQLiteFileName, CEDEOB_SQLITE_FOLDER );
    strcat( szSQLiteFileName, "/" );
    strcat( szSQLiteFileName, CEDEOB_SQLITE_FILENAME );

    g_pTheTaskMngr = new CTaskMngr( en_TASK_MANAGER_PRIORITY, ( const char * ) "MNG", true, ( char * ) szSQLiteFileName, m_tiNow );

#elif _MSSQL_
    // MSSQL 연결
    g_pTheTaskMngr = new CTaskMngr( g_iKeyId++, ( const char * ) "MNG", true );

#else
    g_pTheTaskMngr = new CTaskMngr( g_iKeyId++, "MNG", true, ( char * ) NULL );

#endif
    g_pTheTaskMngr->Run();

    // 2. 운용 관련 쓰레드를 호출한다.
    g_pTheUrBit = new CUrBit( en_BIT_PRIORITY, ( const char * ) "BIT", true );
    g_pTheUrBit->Run();

    // 3. ZYNQ 보드 및 CCU 장치의 랜 처리 쓰레드를 호출한다.
    //RECZYNQ->Run( _MSG_RECZYNQ_KEY );
    //RECCCU->Run();

    // 4. 브라우저의 CGI 메시지를 처리한다.
    //CGI->Run( _MSG_ZCGI_KEY );

#ifdef _MSC_VER
    // 5. 사용자 수집 함수 메시지를 처리한다.
    //g_pTheUserCollect = new CUserCollect(g_iKeyId++, (const char *) "CUserCollect", true);
    //g_pTheUserCollect->Run(_MSG_USERCOL_KEY);
#endif


    // 6. 마지막으로 랜 송신 및 수신 쓰레드를 호출한다.
    //g_pTheZYNQSocket = new CMultiServer( g_iKeyId++, (char *)"CZYNQSocket", PORT );
    //g_pTheZYNQSocket->Run( _MSG_ZYNQ_KEY );
    //if (g_pTheSysConfig->GetBoardID() == enMaster) {


    COperationConsole *ptheOperationConsole;

#ifdef _MSC_VER
    ptheOperationConsole = new COperationConsole( g_iKeyId++, "CO1", true );          // CCU_OperationConsole
    g_pTheCCUSocket = new CSingleClient( en_RECLAN_PRIORITY, ( const char * ) "CCU", ptheOperationConsole, CCU_PORT, NULL, m_pParent );
    g_pTheCCUSocket->Run( _MSG_CCU_KEY );

    ptheOperationConsole = new COperationConsole( g_iKeyId++, "CO2", true );   // CCU_DebugConsole
    g_pTheCCUDebugSocket = new CSingleClient( en_RECLAN2_PRIORITY, ( const char * ) "CCU_D", ptheOperationConsole, CCU_PORT, g_pTheSysConfig->GetDebugServerOfNetwork(), m_pParent );
    // g_pTheCCUDebugSocket->Run( _MSG_CCU_DEBUG_KEY );

#else
    ptheOperationConsole = new COperationConsole( g_iKeyId++, ( const char *) "CO1", true );
    g_pTheCCUSocket = new CSingleClient( en_RECLAN_PRIORITY, ( const char * ) "CCU", ptheOperationConsole, CCU_PORT, NULL, m_pParent );

    // 나머지 타스크가 준비 될때까지 기다란다...
    Sleep( 5 );

    g_pTheCCUSocket->Run( _MSG_CCU_KEY );

    //ptheOperationConsole = new COperationConsole( g_iKeyId++, "CCU_O", true );
    //g_pTheCCUDebugSocket = new CSingleClient( en_RECLAN2_PRIORITY, ( const char * ) "CCU_D", ptheOperationConsole, CCU_PORT, g_pTheSysConfig->GetDebugServerOfNetwork(), m_pParent );

#endif

    // g_pTheClockTimer = new CClockTimer( ( const char * ) "TIM" );

#ifdef _MSC_VER
    g_pTheSignalCollect->PreFilter( (float)350., (float)10., ( float ) 6900., (float) 7010. );

#endif

}

/**
 * @brief     CreateAnalThread
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-02-05 11:01:03
 * @warning
 */
void CMain::CreateAnalThread()
{
    g_pTheEmitterMerge = new CEmitterMerge( en_EMTMERGE_PRIORITY, ( const char * ) "MRG", true );
    g_pTheEmitterMerge->Run();
    g_pTheSignalCollect = new CSignalCollect( en_COLLECT_PRIORITY, ( const char * ) "COL", true );
    g_pTheSignalCollect->Run();

    g_pTheDetectAnalysis = new CDetectAnalysis( en_DETECT_ANAL_PRIORITY, ( const char * ) "DET", true );
    g_pTheDetectAnalysis->Run();
    g_pTheTrackAnalysis = new CTrackAnalysis( en_TRACK_ANAL_PRIORITY, ( const char * ) "TRK", true );
    g_pTheTrackAnalysis->Run();
	g_pTheScanAnalysis = new CScanAnalysis( en_SCAN_ANAL_PRIORITY, ( const char * ) "SCN", true );
	g_pTheScanAnalysis->Run();

}


#ifdef _MSC_VER
/**
 * @brief
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-14, 13:35
 * @warning
 */
void SIM_Start( bool bReqStart )
{
    STR_MessageData sndMsg;

    if( bReqStart ) {
        sndMsg.uiOpCode = enREQ_OP_START;
        sndMsg.soSocket = 0; //m_uiSocket;
        sndMsg.iArrayIndex = -1;
        sndMsg.uiArrayLength = 0;
        sndMsg.uiDataLength = 0;

    }
    else {
        sndMsg.uiOpCode = enREQ_OP_SHUTDOWN;
        sndMsg.soSocket = 0; //m_uiSocket;
        sndMsg.iArrayIndex = -1;
        sndMsg.uiArrayLength = 0;
        sndMsg.uiDataLength = 0;

    }

    g_pTheTaskMngr->QMsgSnd( & sndMsg, ( void * ) NULL, "MAIN" );

    Sleep( 1 );

}

/**
 * @brief     StopSigGen
 * @param     bool bEnable
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-12-16 11:58:00
 * @warning
 */
void StopSigGen( bool bEnable )
{
    if( g_pTheSignalCollect != NULL ) {
        g_pTheSignalCollect->StopSigGen( bEnable );
    }
}

/**
 * @brief     SIM_Library
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-27 13:05:28
 * @warning
 */
void SIM_Library()
{
    STR_MessageData sndMsg;

    sndMsg.uiOpCode = enREQ_RELOAD_LIBRARY;
    sndMsg.soSocket = 0;
    sndMsg.iArrayIndex = -1;
    sndMsg.uiArrayLength = 0;
    sndMsg.uiDataLength = sizeof( int );

    g_pTheEmitterMerge->QMsgSnd( &sndMsg, ( void * ) NULL, "MAIN" );

#if 0
    STR_MessageData sndMsg;

    sndMsg.uiOpCode = enMONITOR;
    sndMsg.soSocket = 0;
    sndMsg.iArrayIndex = -1;
    sndMsg.uiArrayLength = 0;
    sndMsg.uiDataLength = 0;

    g_pTheEmitterMerge->QMsgSnd( &sndMsg, ( void * ) NULL, "MAIN" );

#endif

}

#endif

/**
 * @brief     End
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-06-08, 11:43
 * @warning
 */
void End()
{
    // 분석 관련 쓰레드를 종료 한다.
    //PROMPT->ReleaseInstance();

    _SAFE_DELETE( g_pTheUrBit )

    // 신호 수집 관련 쓰레드 종료
    _SAFE_DELETE( g_pTheUserCollect )
    _SAFE_DELETE( g_pTheSignalCollect )

    // 분석 관련 쓰레드 종료
    _SAFE_DELETE( g_pTheDetectAnalysis )
    _SAFE_DELETE( g_pTheTrackAnalysis )
    _SAFE_DELETE( g_pTheScanAnalysis )

    // 위협 관리 관련 쓰레드 종료
    _SAFE_DELETE( g_pTheEmitterMerge )


    //_SAFE_DELETE( g_pTheClockTimer )

    // 외부 인터페이스 관련 쓰레드 종료
    _SAFE_DELETE( g_pTheCCUSocket )
    _SAFE_DELETE( g_pTheCCUDebugSocket )

    // 쓰레드 관리 관련 쓰레드 종료
    _SAFE_DELETE( g_pTheTaskMngr )


    //CGI->ReleaseInstance();

    //Log( enNormal, "[usrAppStart] 를 종료 처리 합니다..." );

    _SAFE_DELETE( g_pTheELEnvironVariable )

#ifdef _MSC_VER
    _SAFE_DELETE( g_pTheSysConfig )
#else

#endif

    _SAFE_DELETE( g_pTheLog )

#ifndef _MSC_VER
    exit( 0 );

#endif

    // _CrtDumpMemoryLeaks();

}

/**
 * @brief		signalHandler
 * @param		int signo
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2022/02/08 10:46:43
 * @warning
 */
void signalHandler( int signo )
{

    printf( "\n SIGNO[%d] Handler\n", signo );

    if( signo == 2 ) {
        exit( 0 );
    }

}

/**
 * @brief		ParsingArgument
 * @param		int iArgc
 * @param		char * iArgv[]
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/04/05 16:28:15
 * @warning
 */
void CMain::ParsingArgument( int iArgc, char *iArgv[] )
{

    SetUnitType();

#ifdef __VXWORKS__
    g_iClkTickPerSecond = sysClkRateGet();

#endif

    // Endian 모드를 체크한다.
    UpdateCPUMode();

    // 보드 ID 를 읽어온다.
    if( iArgc >= 2 ) {
        ++ iArgv;

        while( *iArgv != NULL ) {
            if( *iArgv[0] == '-' ) {
                switch( iArgv[0][1] ) {
                    case 'i':
#ifdef __VXWORKS__
                        if( iArgv[0][2] == '\0' ) {
#else
                        if( iArgv[0][2] == NULL ) {
#endif
                            g_enBoardId = enPRC3;

                            Log( enError, "기본값으로 마스터[%d]로 설정합니다.", g_enBoardId );
                            break;
                        }
                        else {
                            int iArgv0;

                            iArgv0 = atoi( iArgv[0] + 2 );

                            if( iArgv0 > 0 ) {
                                g_enBoardId = ( ENUM_BoardID) iArgv0;
                            }
                            else {
                                g_enBoardId = ENUM_BoardID::enPRC_Unknown;
                            }
                        }

                        // 아큐먼트 설정 값을 전시 합니다.
    //                     if( g_enBoardId == enMaster ) {
    //                         Log( enDebug, "마스터[%d]로 설정합니다.", g_enBoardId );
    //                     }
    //                     else {
    //                         Log( enDebug, "슬레이브[%d]로 설정합니다.", g_enBoardId );
    //                     }
                        break;

                    case 's':
#if 0
#ifdef __VXWORKS__
                        if( iArgv[0][2] == '\0' ) {
                            g_szPDWScinarioFile[0] = ( char ) 0;
#else
                        if( iArgv[0][2] == NULL ) {
                            g_szPDWScinarioFile[0] = NULL;
#endif

                            Log( enError, "PDW 시나리오 파일[%s]이 잘못 입력됐습니다.", iArgv[0] );
                            break;
                        }
                        else {
                            strcpy( g_szPDWScinarioFile, iArgv[0] + 2 );
                        }

                        // 아큐먼트 설정 값을 전시 합니다.
                        Log( enDebug, "PDW 시나리오 파일[%s]을 설정합니다.", g_szPDWScinarioFile );
#endif
                        break;

                    default:
                        break;
                    }
                }

            ++iArgv;

        }


    }
    else {
        Log( enDebug, "인자가 없어서 기본값으로 설정합니다..." );
        g_enBoardId = enMaster;
    }
}

/**
 * @brief     UpdateCPUMode
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-03-08, 11:55
 * @warning
 */
void UpdateCPUMode()
{
#if defined(__VXWORKS__) || defined(__linux__)
    int i = 1;

    g_enEndian = enUNKNOWN_ENDIAN;
    if( *( ( char * ) &i ) ) {
        TRACE( "리틀엔디안 모드 입니다.\n" );
        g_enEndian = enLITTLE_ENDIAN;
    }
    else if( *( ( char * ) &i + ( sizeof( int ) - 1 ) ) ) {
        TRACE( "빅 엔디안 모드 입니다.\n" );
        g_enEndian = enBIG_ENDIAN;
    }
    else {

    }
#else
    g_enEndian = enLITTLE_ENDIAN;

#endif

}


/**
 * @brief		cleanup_handler
 * @param		void * arg
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2022/02/08 10:45:31
 * @warning
 */
void cleanup_handler( void *arg )
{
    printf( "cleanup \n" );
    // close your socket
}

// void *execute_on_thread(void *arg)
// {
//     pthread_cleanup_push(cleanup_handler, NULL);
//     pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
//
//     while(1)
//     {
//         //sleep(1);
//         printf("Running\n");
//         //thread stuff
//     }
//
//     pthread_cleanup_pop(1);
//
//     return (void *) 0;
// }




#if defined(__VXWORKS__) || defined(__linux__)
/**
 * @brief 시작 프로그램 입니다.
 */
void usrAppStart( int iArgc, char *iArgv[] )
{


#ifdef __VXWORKS__
    memOptionsSet( MEM_ALLOC_ERROR_LOG_FLAG |
        MEM_BLOCK_CHECK |
        MEM_BLOCK_ERROR_LOG_FLAG );

#else

    while( true ) {
        sleep( 10 );
    }

#ifndef _MSC_VER
    // 쓰레드 종료
    End();

#endif

#endif

    // 쓰레드 생성 초기화
    Start( iArgc, iArgv, NULL );

    //printf( "\n usrAppStart" );

}

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main( int iArgc, char *iArgv[] )
{
    CMain theMain;


    theMain.Run( iArgc, iArgv );

    /////////////////////////////////////////////////////////////////////////////////
    // 아규먼트를 파싱하여 프로그램을 설정합니다.
    // theMain.ParsingArgument( argc, argv );

#ifdef _DAEMON_
    pid_t pid;

    pid = fork();

    // fork() 가 실패하면 프로그램을 종료한다.
    if( pid < 0 ) {
        exit( 0 );
    }
    // 부모프로세스를 종료한다.
    else if( pid != 0 ) {
        exit( 0 );
    }

    // 터미널 종료시 signal의 영향을 받지 않는다.
    signal( SIGHUP, SIG_IGN );
    //close( 0 );
    //close( 1 );
    //close( 2 );

    chdir( "/" );
    // 새로운 세션의 리더가 된다.
    setsid();
#endif

    // usrAppStart( argc, argv );

    /*
    pthread_t tid;
    pthread_create(&tid,NULL,execute_on_thread,NULL);

    sleep(10);

    if (!pthread_cancel(tid))
    {
        pthread_join(tid, NULL);
    }
    else
    {
        perror("pthread_cancel");
    }
    */

    return 0;
}

/**
 * @brief     Check64bitArithmetic
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-03 10:47:23
 * @warning
 */
void Check64bitArithmetic()
{
    bool bRet = true;

    _TOA x;

    x = 0xffffffffffffffff;
    x = x / 0xfffffffffffffff;
    if( x != 16 ) {
        bRet = false;
        TRACE( "\nSBC에 탑재된 프로세서는 64비트 연산을 지원하지 않습니다." );
    }

    x = 0xffffffffffff;
    x = x * 0x10000;
    if( x != 0xffffffffffff0000 ) {
        bRet = false;

        TRACE( "\nSBC에 탑재된 프로세서는 64비트 연산을 지원하지 않습니다." );
    }

    if( bRet == true ) {
        TRACE( "\nSBC에 탑재된 프로세서는 64비트 연산을 지원 합니다." );

    }
    TRACE( "\n" );

}

/**
 * @brief		ToggleTaskSuspend
 * @param		CThread * pThread
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/11/10 10:27:32
 * @warning
 */
void ToggleTaskSuspend( CThread * pThread )
{
    if( pThread != NULL ) {
        printf( "\n [%s]", pThread->GetThreadName() );
        if( true == pThread->GetTaskRunStat() ) {
            printf( "Suspend..." );
            pThread->SetTaskSuspend();
        }
        else {
            printf( "Resume..." );
            pThread->SetTaskResume();
        }
    }
}

/**
 * @brief		ShowTaskMessae
 * @param		CThread * pThread
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/11/11 13:33:42
 * @warning
 */
void ShowTaskMessae( CThread * pThread, int iLevel )
{
    if( pThread != NULL ) {
        pThread->ShowTaskMessae( iLevel );
    }
}

/**
 * @brief		메모리 체크를 수행합니다.
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2022/12/18 15:30:19
 * @warning
 */
void memCheck()
{
    MEM_PART_STATS sMemStats;

    if( memPartInfoGet( memSysPartId, &sMemStats ) == ERROR ) {
        printf( "\n Memory Check Error !" );
    }
    else {
        printf( "\n numBytesFree...[%ld]", sMemStats.numBytesFree );
        printf( "\n numBlocksFree...[%ld]", sMemStats.numBlocksFree );
        printf( "\n maxBlockSizeFree...[%ld]", sMemStats.maxBlockSizeFree );
        printf( "\n numBytesAlloc...[%ld]", sMemStats.numBytesAlloc );
        printf( "\n numBlocksAlloc...[%ld]", sMemStats.numBlocksAlloc );
        printf( "\n maxBytesAlloc...[%ld]", sMemStats.maxBytesAlloc );

    }

}

/**
 * @brief		ss
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/11/10 10:16:09
 * @warning
 */
void ss()
{
    vector<CThread *>::iterator iter;

    printf( "\n모든 타스크를 중지/실행 시킵니다." );
    for( const auto &cThread : g_vecThread ) {
        if( strcmp( cThread->GetThreadName(), "LOG" ) != 0 ) {
            ToggleTaskSuspend( cThread );
        }
    }

}

/**
 * @brief		전체 큐 메시지의 상태를 출력합니다.
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/11/11 13:36:20
 * @warning
 */
void qq( int iLevel )
{
    vector<CThread *>::iterator iter;

    printf( "모든 신호 분석 관련 큐 메시지를 보여줍니다." );
    for( const auto &cThread : g_vecThread ) {
        ShowTaskMessae( cThread, iLevel );
    }

}

/**
 * @brief		pci_enable
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/04/04 16:42:23
 * @warning
 */
void pci_enable()
{
    //g_pTheSignalCollect->m_pTheLeftCollectBank->StartCollecting();
    g_pTheSignalCollect->m_pTheRigtCollectBank->StartCollecting();

}

/**
 * @brief		pci_disable
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/04/04 16:42:24
 * @warning
 */
void pci_disable()
{
    //g_pTheSignalCollect->m_pTheLeftCollectBank->EndCollecting();
    g_pTheSignalCollect->m_pTheRigtCollectBank->EndCollecting();

}



/**
 * @brief		MemotyTest
 * @param		size_t iSize
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2022/02/07 14:59:23
 * @warning
 */
void MemotyTest( size_t iSize )
{
    size_t ii;
    char *pMemory;

    //char buffer[100]={0};

    //printf( "sizeof(size_t)=%d",sizeof(size_t) );
    if( iSize > 1024 * 1024 * 1024 ) {
        printf( "\n Starting the memory check...[%d]GB", iSize / 1024 / 1024 / 1024 );
    }
    else {
        printf( "\n Starting the memory check...[%d]MB", iSize / 1024 / 1024 );
    }

    pMemory = ( char * ) malloc( iSize );

    for( ii = 0; ii < iSize; ++ii ) {
        *( pMemory + ii ) = ( char ) ii;
        if( *( pMemory + ii ) != ( char ) ii ) {
            printf( "\n Memory Check Error in Address !" );
            break;
        }
    }

    printf( "\n\n\n Memory Check OK !" );
    free( pMemory );

}

/**
 * @brief		pcisetting
 * @param		CPCIDriver * pPCIDriver
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/03/11 10:44:57
 * @warning
 */
void pcisetting( CPCIDriver * pPCIDriver )
{
//     unsigned int uiValue;
//
//     pPCIDriver->StartCollecting();
//
//     uiValue = pPCIDriver->PCICtrlRead32( ANZ_IRQ_STATUS, false );
//     _func_kprintf( "\nPCICtrlRead32( ANZ_IRQ_STATUS )=0x%x", uiValue );
//
//     // pPCIDriver->PCICtrlWrite32( ANZ_REQ, 0 );
//     pPCIDriver->PCICtrlWrite32( OP_MODE, 1 );
//     pPCIDriver->PCICtrlWrite32( FILT_BYPASS, 0 );
//     pPCIDriver->PCICtrlWrite32( FILT_ADAPT, 0 );
//     pPCIDriver->PCICtrlWrite32( ANZ_CNT, 100 );
//     pPCIDriver->PCICtrlWrite32( PARAM_IDX_W, 1 );
//     //pPCIDriver->PCICtrlWrite32( ANZ_REQ, 1 );
//     pPCIDriver->PCICtrlRead32( ANZ_IRQ_STATUS, false );
//     _func_kprintf( "\nPCICtrlRead32( ANZ_IRQ_STATUS )=0x%x\n", uiValue );

}

void inte()
{
    CPCIDriver *pThePCIDriver;

    if( g_pTheSignalCollect->m_pTheLeftCollectBank != NULL ) {
        pThePCIDriver = g_pTheSignalCollect->m_pTheLeftCollectBank->m_pThePCI;
        pThePCIDriver->PCIInterruptEnable();
    }

    if( g_pTheSignalCollect->m_pTheRigtCollectBank != NULL ) {
        pThePCIDriver = g_pTheSignalCollect->m_pTheRigtCollectBank->m_pThePCI;
        pThePCIDriver->PCIInterruptEnable();
    }

}

void intd()
{
    CPCIDriver *pThePCIDriver;

    if( g_pTheSignalCollect->m_pTheLeftCollectBank != NULL ) {
        pThePCIDriver = g_pTheSignalCollect->m_pTheLeftCollectBank->m_pThePCI;
        pThePCIDriver->PCIInterruptDisable();
    }

    if( g_pTheSignalCollect->m_pTheRigtCollectBank != NULL ) {
        pThePCIDriver = g_pTheSignalCollect->m_pTheRigtCollectBank->m_pThePCI;
        pThePCIDriver->PCIInterruptDisable();
    }

}

/**
 * @brief		dl
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/03/11 10:45:00
 * @warning
 */
void dl()
{
    //CPCIDriver *pThePCIDriver;

    //pThePCIDriver = g_pTheSignalCollect->m_pTheLeftCollectBank->m_pThePCI;

    //_func_kprintf( "\n LEFT PCI Driver 설정 시험" );

    //pcisetting( pThePCIDriver );

}

/**
 * @brief		dr
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/03/11 10:45:02
 * @warning
 */
void dr()
{

    CPCIDriver *pThePCIDriver;

    pThePCIDriver = g_pTheSignalCollect->m_pTheRigtCollectBank->m_pThePCI;

    _func_kprintf( "\n RIGHT PCI Driver 설정 시험" );

    pcisetting( pThePCIDriver );

}

/**
 * @brief		ds
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/03/11 10:45:04
 * @warning
 */
void ds()
{
//     unsigned int uiValue;
//     CPCIDriver *pThePCIDriver;
//
//     pThePCIDriver = g_pTheSignalCollect->m_pTheLeftCollectBank->m_pThePCI;
//     uiValue = pThePCIDriver->PCICtrlRead32( ANZ_IRQ_STATUS, false );
//     _func_kprintf( "\nLeftPCICtrlRead32( ANZ_IRQ_STATUS )=0x%x", uiValue );
//
//     pThePCIDriver = g_pTheSignalCollect->m_pTheRigtCollectBank->m_pThePCI;
//     uiValue = pThePCIDriver->PCICtrlRead32( ANZ_IRQ_STATUS, false );
//     _func_kprintf( "\nRigtPCICtrlRead32( ANZ_IRQ_STATUS )=0x%x", uiValue );

}

/**
 * @brief     cpsq
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-22 09:56:24
 * @warning
 */
void cpsq()
{
    int iCopy;
    string strSrcFileName, strDestFilename;
    char buffer[100];

    // 목적지 디렉토리 생성
    sprintf( buffer, "%s/BRD_%d/%s", SHARED_DATA_DIRECTORY, g_enBoardId, SQLITE_DIRECTORY );
    if( CCommonUtils::CreateDir( buffer ) ) {
        CCommonUtils::getStringPresentTime( buffer, sizeof( buffer ), true );

        strSrcFileName = string_format( "%s%s/%s/%s", RAMDRV, RAMDRV_NO, SQLITE_DIRECTORY, EMITTER_SQLITE_FILEEXTNAME );
        strDestFilename = string_format( "%s/BRD_%d/%s/#%d_%s_%s", SHARED_DATA_DIRECTORY, g_enBoardId, SQLITE_DIRECTORY, (int) g_enBoardId, buffer, EMITTER_SQLITE_FILEEXTNAME );

        printf( "\n %s...%s", strSrcFileName.c_str(), strDestFilename.c_str() );
        iCopy = CCommonUtils::CopySrcToDstFile( strSrcFileName.c_str(), strDestFilename.c_str(), 1, 0077 );
        if( iCopy <= 0 ) {
            printf( "\n 복사 에러 입니다 !!!" );
        }
        else {
            printf( "\n 복사 정상 입니다 !!!" );
        }
    }
    else {
        printf( "\n 디렉토리[%s] 생성 실패 !", buffer );
    }

}

/**
 * @brief     cplog
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-22 09:57:48
 * @warning
 */
void cplog()
{
    int iCopy;
    string strSrcFileName, strDestFilename;
    char buffer[100];
    char dirName[100];

    sprintf( dirName, "%s%s", ATADRV, LOG_DIRECTORY );
    mkdir( dirName );

    CCommonUtils::getStringPresentTime( buffer, sizeof( buffer ), true );

    strSrcFileName = string_format( "%s%s/%s/%s", RAMDRV, RAMDRV_NO, LOG_DIRECTORY, LOG_FILENAME );
    strDestFilename = string_format( "%s%s/%s_%s", ATADRV, LOG_DIRECTORY, buffer, LOG_FILENAME );

    iCopy = CCommonUtils::CopySrcToDstFile( strSrcFileName.c_str(), strDestFilename.c_str(), 1, 0077 );
    if( iCopy <= 0 ) {
        printf( "\n %s...%s", strSrcFileName.c_str(), strDestFilename.c_str() );
        printf( "\n 복사 에러 입니다 !!!" );
    }
    else {
        printf( "\n %s...%s", strSrcFileName.c_str(), strDestFilename.c_str() );
        printf( "\n 복사 정상 입니다 !!!" );
    }

}

/**
 * @brief     saveon
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-10-10 16:30:44
 * @warning
 */
void saveon()
{
    g_pTheDetectAnalysis->SetSaveFile( true );
    g_pTheEmitterMerge->SetSaveFile( true );
}

/**
 * @brief     saveoff
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-10-10 16:30:41
 * @warning
 */
void saveoff()
{
    g_pTheDetectAnalysis->SetSaveFile( false );
    g_pTheEmitterMerge->SetSaveFile( false );
}

/**
 * @brief     logall
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-26 19:10:41
 * @warning
 */
void logall()
{
    g_enLogAnalType = enALL;

}

/**
 * @brief     logoff
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2024-01-26 19:07:14
 * @warning
 */
void logoff()
{
    g_enLogAnalType = enCLEAR_ANAL;

}

/**
 * @brief     logdet
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-26 19:10:43
 * @warning
 */
void logtdet()
{
    int iValue;

    iValue = ( int ) g_enLogAnalType;

    iValue ^= enDET_ANAL;
    g_enLogAnalType = ( ENUM_ANAL_TYPE ) iValue;

}

/**
 * @brief     logtrk
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-26 19:10:45
 * @warning
 */
void logttrk()
{
    int iValue;

    iValue = ( int ) g_enLogAnalType;

    iValue ^= enTRK_ANAL;
    g_enLogAnalType = ( ENUM_ANAL_TYPE ) iValue;

}

/**
 * @brief     logscn
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-26 19:10:47
 * @warning
 */
void logtscn()
{
    int iValue;

    iValue = ( int ) g_enLogAnalType;

    iValue ^= enSCN_ANAL;
    g_enLogAnalType = ( ENUM_ANAL_TYPE ) iValue;

}

/**
 * @brief     de
 * @param     unsigned int uiAETID
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2024-01-26 23:18:45
 * @warning
 */
void de( unsigned int uiAETID )
{
    STR_MessageData sndMsg;

    sndMsg.uiOpCode = enREQ_DELETE_THREAT_DATA;
    sndMsg.soSocket = 0;
    sndMsg.iArrayIndex = -1;
    sndMsg.uiArrayLength = 0;
    sndMsg.uiDataLength = sizeof( SELDELETE );

    sndMsg.x.stDelete.uiAETID = uiAETID;
    sndMsg.x.stDelete.uiABTID = 0;

    g_pTheEmitterMerge->QMsgSnd( &sndMsg, ( void * ) NULL, "MAIN" );

}

/**
 * @brief     rb
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-10-10 16:30:35
 * @warning
 */
void rb()
{
    STR_MessageData sndMsg;

    sndMsg.uiOpCode = enTHREAD_TIMER;
    sndMsg.soSocket = 0;
    sndMsg.iArrayIndex = -1;
    sndMsg.uiArrayLength = 0;
    sndMsg.uiDataLength = 0;

    g_pTheUrBit->QMsgSnd( &sndMsg, ( void * ) NULL, "MAIN" );

}

/**
 * @brief     dsv
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2024-01-14 11:04:36
 * @warning
 */
void dsv()
{
    ENUM_BoardID enBoardID;

    g_pTheSysConfig->DisplaySystemVar();

    enBoardID = GetBoardID();
    printf( "\n\n SBC 보드는 #%d 입니다." , (int) enBoardID );

}

/**
 * @brief     alive
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2024-01-25 22:41:24
 * @warning
 */
void a()
{
    STR_MessageData sndMsg;

    sndMsg.uiOpCode = enMONITOR;
    sndMsg.soSocket = 0;
    sndMsg.iArrayIndex = -1;
    sndMsg.uiArrayLength = 0;
    sndMsg.uiDataLength = 0;

    g_pTheEmitterMerge->QMsgSnd( &sndMsg, ( void * ) NULL, "MAIN" );

}

/**
 * @brief     sf
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2024-01-27 14:51:56
 * @warning
 */
void sf()
{

    // 시스템 폴더 및 파일명을 프린트 합니다.
    printf( "[%s] 파일 위치는 [%s]에 입니다.\n", INI_FILENAME, INI_FOLDER );
    printf( "NFS 드라이브는 [%s] 입니다.\n", SHARED_DATA_DIRECTORY );
    printf( "로그 디렉토리는 [%s] 입니다.\n", g_pTheLog->GetLogDirectory() );
    printf( "로그 파일명은 [%s] 입니다.\n", g_pTheLog->GetLogFullName() );

#ifdef _SQLITE_
    printf( "CED/EOB 데이터베이스 파일 위치 및 파일명[%s, %s]\n", CEDEOB_SQLITE_FOLDER, CEDEOB_SQLITE_FILENAME );
    printf( "에미터 데이터베이스 파일 위치 및 파일명[%s, %s]\n", EMITTER_SQLITE_FOLDER, EMITTER_SQLITE_FILEEXTNAME );

#endif

}

/**
 * @brief     GetBoardID
 * @return    ENUM_BoardID
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2024-01-25 15:08:16
 * @warning
 */
ENUM_BoardID GetBoardID()
{
    ENUM_BoardID enBoardID;

    CPCIDriver *pThePCIDriver;

    // SBC 보드 ID 읽기
    unsigned int uiPSBoardID;

    if( g_pTheSignalCollect->m_pTheLeftCollectBank != NULL ) {
        pThePCIDriver = g_pTheSignalCollect->m_pTheLeftCollectBank->m_pThePCI;
        uiPSBoardID = pThePCIDriver->PCICtrlRead32( IBRDID, false );
    }
    else if( g_pTheSignalCollect->m_pTheRigtCollectBank != NULL ) {
        pThePCIDriver = g_pTheSignalCollect->m_pTheRigtCollectBank->m_pThePCI;
        uiPSBoardID = pThePCIDriver->PCICtrlRead32( IBRDID, false );
    }
    else {
        printf( "\n 좌/우 AIX 버스가 작동하지 않습니다 ! 담당자에게 문의하세요... " );
    }

    switch( uiPSBoardID ) {
        // 2~3GHz(좌), 0.5~2 GHz(우)
        case 8:
        case 9:
            enBoardID = enPRC5;
            break;

            // 3~4.5 GHz(좌), 4.5~6GHz(우)
        case 6:
        case 7:
            enBoardID = enPRC4;
            break;

            // 8~10GHz(좌), 6~8 GHz(우)
        case 0:
        case 1:
            enBoardID = enPRC1;
            break;

            // 10~12 GHz(좌), 12~14GHz(우)
        case 2:
        case 3:
            enBoardID = enPRC2;       // 192.168.0.111
            break;

            // 16~18GHz(좌), 14~16 GHz(우)
        case 4:
        case 5:
            enBoardID = enPRC3;
            break;

        default:
            enBoardID = enPRC1;
            break;
    }

    printf( "\n SBC Board ID : %d (PS Board ID : %d)", (int) enBoardID, uiPSBoardID );

    return enBoardID;

}

/**
 * @brief     md
 * @param     char * pHostIPAddress
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2024-01-25 15:08:13
 * @warning
 */
bool md( char *pHostIPAddress )
{
    bool bRet = true;

    char szRemoteFileSystem[100] = "/d/rawdata";

#ifdef __VXWORKS__
    STATUS status;

    printf( "\nNFS 드라이브[%s:%s]를 연결하려 합니다 !", pHostIPAddress, szRemoteFileSystem );

    status = hostAdd( ( char * ) "NFS_HOST2", pHostIPAddress );
    status = nfsMount( "NFS_HOST2", szRemoteFileSystem, "/d/rawdata" );

    if( status == OK ) {
        printf( "\nNFS 드라이브[%s:%s]를 정상 연결했습니다 !", pHostIPAddress, szRemoteFileSystem );
    }
    else {
        printf( "\n[W] NFS 드라이브[%s:%s]를 마운트 하지 못 했습니다 !!!", pHostIPAddress, szRemoteFileSystem );
        WhereIs;

        bRet = false;
    }

#endif

    return bRet;

}

/**
 * @brief     tsp
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-10-10 16:30:37
 * @warning
 */
void tsp()
{

    printf( "\n 타이머 종료..." );
    //g_pTheClockTimer->Stop();

}

void pre( float fDOAMin, float fDOAMax, float fFreqMin, float fFreqMax )
{
    g_pTheSignalCollect->PreFilter( fDOAMin, fDOAMax, fFreqMin, fFreqMax );

}

/**
 * @brief     ioRedirect
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-10-16 08:37:02
 * @warning
 */
// void ioRedirect()
// {
//     int iShellTid = 0;
//     int iShellOpFd = 0;
//     int iGlobalStdFd = 0;
//
//     iShellTid = taskIdSelf();
//     iShellOpFd = ioTaskStdGet( iShellTid, 1 );
//     iGlobalStdFd = ioGlobalStdGet( 1 );
//
//     ( void ) logMsg( "\nLM:Initial task output.shellFd %d, GlobalFD %d.\n", iShellOpFd, iGlobalStdFd, 0, 0, 0, 0 );
//     printf( "\n 초기 타스크 출력 파일 인자 : %d.", iShellOpFd );
//
//     ioGlobalStdSet( 1, iShellOpFd );
//     iGlobalStdFd = ioGlobalStdGet( 1 );
//
//     logMsg( "\nLM:Initial task output.shellFd %d, GlobalFD change to %d.\n", iShellOpFd, iGlobalStdFd, 0, 0, 0, 0 );
//     printf( "\n전역 타스크 출력 파일 인자 : %d.", iGlobalStdFd );
//
// }

#else

#endif

