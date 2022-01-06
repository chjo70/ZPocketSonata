﻿/*
 *
 *
* Placeholder PetaLinux user application.
*
* Replace this with your application code

* Copyright (C) 2013 - 2016  Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person
* obtaining a copy of this software and associated documentation
* files (the "Software"), to deal in the Software without restriction,
* including without limitation the rights to use, copy, modify, merge,
* publish, distribute, sublicense, and/or sell copies of the Software,
* and to permit persons to whom the Software is furnished to do so,
* subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
* CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in this
* Software without prior written authorization from Xilinx.
*
*/

#include "stdafx.h"

#ifdef _MSC_VER


#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <afxmt.h>
#include <direct.h>
#include <xutility>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#elif defined(__VXWORKS__)


#include <memPartLib.h>
#include <stdlib.h>

#else

#endif

#include <iostream>

using namespace std;

#define _MAIN_
#define _MAIN_GLOBALS_

#include <signal.h>
#include <cassert>

#include "cmain.h"
#include "./Thread/ctaskmngr.h"
#include "./Utils/clog.h"
#include "./Utils/cmultiserver.h"
#include "./Utils/csingleserver.h"
#include "./Utils/csingleclient.h"
#include "./Thread/creclan.h"
#include "./Thread/cprompt.h"
#include "./Thread/curbit.h"
#include "./Thread/cpulsetrk.h"
#include "./Thread/csignalcollect.h"
#include "./Thread/cjamtech.h"
#include "./Thread/ccgi.h"
#include "./Thread/cusercollect.h"

#include "./System/csysconfig.h"

#include "./Utils/ccommonutils.h"

#include "./Include/globals.h"

#ifdef __cplusplus
extern "C"
{
#endif

void usrAppStart( int iArgc, char *iArgv[] );
void ss();

void MemotyTest( size_t iSize );

#ifdef __cplusplus
}
#endif

void signalHandler(int signo);

////////////////////////////////////////////////////////////////////////////////////////
// 아래에 타스크 관련 클래스를 정의합니다.
//CMySocket g_theZYNQSocket( g_iKeyId++, (char *)"CZYNQSocket" );
//CMySocket g_theCCUSocket( g_iKeyId++, (char *)"CCCUSocket" );
//CMySocket g_thePMCSocket( g_iKeyId++, (char *)"CPMCSocket" );




/**
 * @brief     InitDatabase
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-09-17, 10:48
 * @warning
 */
void InitDatabase()
{
    char szSQLiteFileName[100];

    // 1. 위협 라이브러리 존재 확인
    strcpy( szSQLiteFileName, EMITTER_SQLITE_FOLDER );
    strcat( szSQLiteFileName, "/" );
    strcat( szSQLiteFileName, EMITTER_SQLITE_FILENAME );

#ifdef _SQLITE_    
    
#ifdef __linux__
    if( 0 == mkdir( EMITTER_SQLITE_FOLDER, 0766 ) || errno == EEXIST ) {
    }
#elif _MSC_VER
    if( 0 == _mkdir( EMITTER_SQLITE_FOLDER ) || errno == EEXIST ) {
         CCommonUtils::CopyFile( BLK_EMITTER_SQLITE_FILENAME, szSQLiteFileName, 1, 0077 );
     }

#elif __VXWORKS__
    char szSrcFilename[100], szDstFilename[100];

    if( OK == mkdir( EMITTER_SQLITE_FOLDER ) || errno == EEXIST ) {
    	printf( "\n *** 위협 관리 파일을 램 드라이브에 설치 합니다.***" );
        sprintf( szSrcFilename, "%s/%s/%s" , TFFSDRV, SQLITE_FOLDER, BLK_EMITTER_SQLITE_FILENAME );
        sprintf( szDstFilename, "%s%s/%s/%s" , RAMDRV, RAMDRV_NO, SQLITE_FOLDER, EMITTER_SQLITE_FILENAME );
        CCommonUtils::CopyFile( szSrcFilename, szDstFilename, 1, 0077 );
        //WhereIs;
    }

    if( OK == mkdir( CEDEOB_SQLITE_FOLDER ) || errno == EEXIST ) {
        //printf( "\n *** CED/EOB 파일을 램 드라이브에 설치 합니다.***" );
        sprintf( szSrcFilename, "%s/%s/%s" , TFFSDRV, SQLITE_FOLDER, CEDEOB_SQLITE_FILENAME );
        sprintf( szDstFilename, "%s%s/%s/%s" , RAMDRV, RAMDRV_NO, SQLITE_FOLDER, CEDEOB_SQLITE_FILENAME );
        CCommonUtils::CopyFile( szSrcFilename, szDstFilename, 1, 0077 );
        WhereIs;
    }

#else
    if( 0 == mkdir( EMITTER_SQLITE_FOLDER ) || errno == EEXIST ) {
    }
#endif

        
#elif _NO_SQLITE_
    printf( "\n #### NO_SQLITE 모드 입니다. ####" );

#elif _MSSQL_

#endif


}


/**
 * @brief     Start
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-06-08, 11:43
 * @warning
 */
void Start( int iArgc, char *iArgv[] )
{
    ParsingArgument( iArgc, iArgv );
    
    LOGENTRY;
    _ShowProgramTitle();

    signal( SIGINT, signalHandler);
    signal( SIGABRT, signalHandler);
    signal( SIGTERM, signalHandler);

#ifdef __linux__
    signal( SIGHUP, signalHandler);
    signal( SIGSTOP, signalHandler);
#endif

    // CPOCKETSONATAPDW::Test();
    {
        //std::vector<int> *m_pVecLOBs;
#define TOTAL_ITEMS_OF_THREAT_NODE			(100000)
//         m_pVecLOBs = new std::vector<int> [TOTAL_ITEMS_OF_THREAT_NODE];
//         //m_pVecLOBs.reserve( TOTAL_ITEMS_OF_THREAT_NODE )
// 
// //         for( i=0 ; i < ) {
// //             AppendLOBs( & m_p
// //         }
// 
//         delete [] m_pVecLOBs;
// 
//         TRACE( "TEST..." );

    }

    InitDatabase();

    g_pTheSysConfig = new CSysConfig();

    // 1. 쓰레드 관리 쓰레드를 호출한다.
    char szSQLiteFileName[100];
    strcpy( szSQLiteFileName, CEDEOB_SQLITE_FOLDER );
    strcat( szSQLiteFileName, "/" );
    strcat( szSQLiteFileName, CEDEOB_SQLITE_FILENAME );
    g_pTheTaskMngr = new CTaskMngr( g_iKeyId++, (char*) "CTaskMngr", true, (char*) szSQLiteFileName );
    g_pTheTaskMngr->Run( _MSG_TMNGR_KEY );

    // 2. 운용 관련 쓰레드를 호출한다.
    g_pTheUrBit = new CUrBit( g_iKeyId++, (char*) "CUrBit", true );
    g_pTheUrBit->Run( _MSG_URBIT_KEY );

    // 3. 분석 및 재밍 관련 쓰레드를 호출한다.
    //PULTRK->Run( _MSG_PULTRK_KEY );
    //JAMTEC->Run( _MSG_JAMTEC_KEY );

    // 4. ZYNQ 보드 및 CCU 장치의 랜 처리 쓰레드를 호출한다.
    //RECZYNQ->Run( _MSG_RECZYNQ_KEY );
    RECCCU->Run( _MSG_RECCCU_KEY );

    // 6. 브라우저의 CGI 메시지를 처리한다.
    //CGI->Run( _MSG_ZCGI_KEY );

    // 7. 사용자 수집 함수 메시지를 처리한다.
    g_pTheUserCollect = new CUserCollect( g_iKeyId++, (char*) "CUserCollect", true );
    g_pTheUserCollect->Run( _MSG_USERCOL_KEY );

    // 8. 마지막으로 랜 송신 및 수신 쓰레드를 호출한다.
    //g_pTheZYNQSocket = new CMultiServer( g_iKeyId++, (char *)"CZYNQSocket", PORT );
    //g_pTheZYNQSocket->Run( _MSG_ZYNQ_KEY );
    if( g_pTheSysConfig->GetBoardID() == enMaster ) {
        g_pTheCCUSocket = new CSingleClient( g_iKeyId++, (char *)"CCCUSocket", CCU_PORT, g_pTheSysConfig->GetPrimeServerOfNetwork() );
        g_pTheCCUSocket->Run( _MSG_CCU_KEY );

        //g_pThePMCSocket = new CSingleClient( g_iKeyId++, (char *)"CPMCSocket", PMC_PORT, PMC_SERVER );
        //g_pThePMCSocket->Run( _MSG_CCU_KEY );
    }

    g_AnalLoop = true;

    g_pTheEmitterMerge = new CEmitterMerge( g_iKeyId++, (char*) "CEmitterMerge", true );
    g_pTheEmitterMerge->Run();
    g_pTheSignalCollect = new CSignalCollect( g_iKeyId++, (char*) "CSignalCollect", true );
    g_pTheSignalCollect->Run();
    g_pTheDetectAnalysis = new CDetectAnalysis( g_iKeyId++, (char*) "CDetectAnalysis", true );
    g_pTheDetectAnalysis->Run();
    g_pTheTrackAnalysis = new CTrackAnalysis( g_iKeyId++, (char*) "CTrackAnalysis", true );
    g_pTheTrackAnalysis->Run();
    g_pTheScanAnalysis = new CScanAnalysis( g_iKeyId++, (char*) "CScanAnalysis", true );
    g_pTheScanAnalysis->Run();

    // 9. 마지막으로 키 입력 처리를 호출한다.
#ifndef _DAEMON_
    //PROMPT->Run( _MSG_PROMPT_KEY );
#endif

    }

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
    
    _SAFE_DELETE( g_pTheCCUSocket );
    //delete g_pThePMCSocket;
    //g_pThePMCSocket = NULL;

    _SAFE_DELETE( g_pTheUrBit );

    //delete g_pTheZYNQSocket;
    // 
    _SAFE_DELETE( g_pTheUserCollect );

    _SAFE_DELETE( g_pTheEmitterMerge );
    _SAFE_DELETE( g_pTheSignalCollect );    
    _SAFE_DELETE( g_pTheDetectAnalysis );    
    _SAFE_DELETE( g_pTheTrackAnalysis );    
    _SAFE_DELETE( g_pTheScanAnalysis );    

    _SAFE_DELETE( g_pTheTaskMngr );    

    //CGI->ReleaseInstance();

    //RECZYNQ->ReleaseInstance();
    RECCCU->ReleaseInstance();

    //JAMTEC->ReleaseInstance();
    //PULTRK->ReleaseInstance();
    // 
    
    // 마지막 타스크 관리자 쓰레드를 종료 한다.
    
       

    LOGMSG( enNormal, "[usrAppStart] 를 종료 처리 합니다..." );

    _SAFE_DELETE( g_pTheSysConfig ); 

    _SAFE_DELETE( g_pTheLog );

#ifndef _MSC_VER
    exit(0);
#endif

}

/**
 * @brief signalHandler
 * @param signo
 */
void signalHandler( int signo )
{

    printf( "\n SIGNO[%d] Handler\n" , signo );

    if( signo == 2 ) {
        g_Loop = false;
        exit(0);
    }

}

/**
 * @brief ParsingArgument
 * @param iArgc
 * @param iArgv
 */
void ParsingArgument( int iArgc, char *iArgv[] )
{

    // 로그 객체를 생성한다.
    g_pTheLog = new CLog();

#ifdef __VXWORKS__
    g_iClkTickPerSecond = sysClkRateGet();

#endif

    // Endian 모드를 체크한다.
    {
        int i = 1;

        if( *((char *) &i) ) {
            printf( "Little Endian mode(Auto Check)." );
            g_enEndian = enLITTLE_ENDIAN;
        }
        else if( *((char *) &i + (sizeof(int) - 1)) ) {
            printf( "Big Endian mode(Auto Check)." );
            g_enEndian = enBIG_ENDIAN;
        }
        else {
            printf( "[W] Unknown Processor mode..." );
            g_enEndian = enUNKNOWN_ENDIAN;
            WhereIs;
        }

    }

    // 보드 ID 를 읽어온다.
    if( iArgc >= 2 ) {
        -- iArgc;
        ++ iArgv;
        while(iArgc--) {
            g_enBoardId = (ENUM_BoardID) atoi( *iArgv );
            // cout << *iArgv++ << endl;
        }
        if( g_enBoardId == enMaster ) {
            LOGMSG1( enDebug, "마스터[%d]로 설정합니다." , g_enBoardId );
        }
        else {
            LOGMSG1( enDebug, "슬레이브[%d]로 설정합니다." , g_enBoardId );
        }
    }
    else {
        LOGMSG( enDebug, "The reason that no arguments inputs, it will set up the default..." );
        g_enBoardId = enMaster;
    }
}

void cleanup_handler(void *arg )
{
    printf("cleanup \n");
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

    // 쓰레드 생성 초기화
    Start( iArgc, iArgv );
    
#ifdef __VXWORKS__
    memOptionsSet (MEM_ALLOC_ERROR_LOG_FLAG | 
        MEM_BLOCK_CHECK |
        MEM_BLOCK_ERROR_LOG_FLAG);

#else

    while( true ) {
        sleep(10);
    }

#ifndef _MSC_VER
    // 쓰레드 종료
    End();
    
#endif
    
#endif    

}

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{

    /////////////////////////////////////////////////////////////////////////////////
    // 아규먼트를 파싱하여 프로그램을 설정합니다.
    ParsingArgument( argc, argv );

#ifdef _DAEMON_
    pid_t pid;

    pid = fork();

    // fork() 가 실패하면 프로그램을 종료한다.
    if( pid < 0 ) {
        exit(0);
    }
    // 부모프로세스를 종료한다.
    else if( pid != 0 ) {
        exit(0);
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

    usrAppStart( argc, argv );

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
 * @brief		ToggleTaskSuspend
 * @param		CThread * pThread
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/11/10 10:27:32
 * @warning		
 */
void ToggleTaskSuspend( CThread *pThread )
{
    if( pThread != NULL ) {
        printf( "\n [%s]" , pThread->GetThreadName() );
		if( true == pThread->GetTaskRunStat() ) {
            printf( "Suspend...");
            pThread->SetTaskSuspend();
		}
		else {
            printf( "Resume...");
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
void ShowTaskMessae( CThread *pThread, int iLevel )
{
    if( pThread != NULL ) {
        pThread->ShowTaskMessae( iLevel );
    }
}

void memCheck()
{
    MEM_PART_STATS sMemStats;

    if( memPartInfoGet( memSysPartId, &sMemStats ) == ERROR ) {
    	printf( "\n Memory Check Error !" );
    }
    else {
    	printf( "\n numBytesFree...[%ld]" , sMemStats.numBytesFree );
        printf( "\n numBlocksFree...[%ld]" , sMemStats.numBlocksFree );
        printf( "\n maxBlockSizeFree...[%ld]" , sMemStats.maxBlockSizeFree );
        printf( "\n numBytesAlloc...[%ld]" , sMemStats.numBytesAlloc );
        printf( "\n numBlocksAlloc...[%ld]" , sMemStats.numBlocksAlloc );
        printf( "\n maxBytesAlloc...[%ld]" , sMemStats.maxBytesAlloc );

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
    TASK_ID taskID;

    taskID = taskIdSelf();
    for( iter=g_vecThis.begin() ; iter != g_vecThis.end() ; ++iter ) {
        ToggleTaskSuspend( *iter );
    }

	printf( "모든 신호 분석 관련 타스크를 중지/실행 시킵니다." );

}


/**
 * @brief		qq
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/11/11 13:36:20
 * @warning		
 */
void qq( int iLevel )
{
    vector<CThread *>::iterator iter; 

    for( iter=g_vecThis.begin() ; iter != g_vecThis.end() ; ++iter ) {
        ShowTaskMessae( *iter, iLevel );
    }
    
    //printf( "모든 신호 분석 관련 큐 메시지를 보여줍니다." );

}



void MemotyTest( size_t iSize )
{
    size_t ii;
    char *pMemory;

    char buffer[100]={0};

    //printf( "sizeof(size_t)=%d",sizeof(size_t) );
    if( iSize > 1024 * 1024 * 1024 ) {
    	printf( "\n Starting the memory check...[%d]GB" , iSize/1024/1024/1024 );
    }
    else {
    	printf( "\n Starting the memory check...[%d]MB" , iSize/1024/1024 );
    }
    
    pMemory = ( char * ) malloc( iSize );

    for( ii=0 ; ii < iSize ; ++ii ) {
        *(pMemory+ii) = (char ) ii;
        if( *(pMemory+ii) != (char ) ii ) {
            printf( "\n Memory Check Error in Address !" );
            break;
        }
    }	

    printf( "\n\n\n Memory Check OK !" );
    free( pMemory );

    /////
    struct tm *pstTime;

    char szSQLString[1024*2];
    char buffer1[100], buffer2[100], buffer3[100];

    SRxABTData stSRxABTData;
    SELABTDATA_EXT stABTExtData;

    SELABTDATA_EXT *pABTExtData = & stABTExtData;
    SRxABTData *pABTData = & stSRxABTData;

    memset( pABTData, 0, sizeof(SRxABTData) );
    memset( pABTExtData, 0, sizeof(SELABTDATA_EXT) );

    pstTime = localtime( & pABTData->tiFirstSeenTime );
    if( pstTime != NULL ) {
        strftime( buffer1, 100, "%Y-%m-%d %H:%M:%S", pstTime);
    }
    else {
        strcpy( buffer1, "1970-01-01 00:00:00" );
    }
    pstTime = localtime( & pABTData->tiLastSeenTime );
    if( pstTime != NULL ) {
        strftime( buffer2, 100, "%Y-%m-%d %H:%M:%S", pstTime);
    }
    else {
        strcpy( buffer2, "1970-01-01 00:00:00" );
    }

    pstTime = localtime( & pABTData->tiFinalAlarmTime );
    if( pstTime != NULL ) {
        strftime( buffer3, 100, "%Y-%m-%d %H:%M:%S", pstTime);
    }
    else {
        strcpy( buffer3, "1970-01-01 00:00:00" );
    }    

    for( int i=0 ; i < 10 ; ++i ) {
        sprintf_s( szSQLString, \
            "INSERT INTO ABTDATA (ABTID, AETID, FIRST_TIME, LAST_TIME, \
            PRIMARY_ELNOT, PRIMARY_MODECODE, MODULATION_CODE, RADARMODE_NAME, PLACENAME_KOR, NICK_NAME, FUNC_CODE, PLATFORM_TYPE, RADAR_MODE_PRIORITY, RADAR_PRIORITY, \
            RADARMODE_INDEX, THREAT_INDEX, POLIZATION, \
            SIGNAL_TYPE, DOA_MEAN, DOA_MIN, DOA_MAX, DOA_DEV, \
            FREQ_TYPE, FREQ_PATTERN_TYPE, FREQ_PATTERN_PERIOD_MEAN, FREQ_PATTERN_PERIOD_MIN, FREQ_PATTERN_PERIOD_MAX, FREQ_MEAN, FREQ_MIN, FREQ_MAX, FREQ_DEV, FREQ_POSITION_COUNT, FREQ_ELEMENT_COUNT, \
            PRI_TYPE, PRI_PATTERN_TYPE, PRI_PATTERN_PERIOD_MEAN, PRI_PATTERN_PERIOD_MIN, PRI_PATTERN_PERIOD_MAX, PRI_MEAN, PRI_MIN, PRI_MAX, PRI_DEV, PRI_JITTER_RATIO, PRI_POSITION_COUNT, PRI_ELEMENT_COUNT, \
            PW_MEAN, PW_MIN, PW_MAX, PW_DEV, \
            PA_MEAN, PA_MIN, PA_MAX, PA_DEV, \
            SCAN_TYPE, SCAN_PRD_MEAN_SEC, SCAN_PRD_MIN_SEC, SCAN_PRD_MAX_SEC, \
            HAS_INTRA_MOD, INTRA_FRQ_CHNG_WID_MAX, INTRA_FRQ_CHNG_WID_MIN, \
            PE_VALID, PE_LATITUDE, PE_LONGGITUDE, PE_HEIGHT, PE_CEP, PE_MAJOR_AXIS, PE_MINOR_AXIS, PE_THETA, PE_DISTANCE, \
            IS_VALIDITY, TOTAL_PDW, NUM_LOB, ALARM_TIME, STAT, \
            IS_MANUAL_INPUT, MANUALPOSESTPREFERRED, MANUAL_POS_EST_LAT, MANUAL_POS_EST_LONG ) VALUES \
            ( %d, %d, \"%s\", \"%s\", \
            \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", %d, %d, \
            %d, %d, %d, \
            %d, %f, %f, %f, %f, \
            %d, %d, %f, %f, %f, %f, %f, %f, %f, %d, %d, \
            %d, %d, %f, %f, %f, %f, %f, %f, %f, %f, %d, %d, \
            %f, %f, %f, %f, \
            %f, %f, %f, %f, \
            %d, %f, %f, %f, \
            %d, %f, %f, \
            %d, %f, %f, %f, %f, %f, %f, %f, %f, \
            %d, %d, %d, \"%s\", %d, \
            %d, %d, %f, %f )" , \
            pABTData->uiABTID, pABTData->uiAETID, buffer1, buffer2, \
            pABTData->szPrimaryELNOT, pABTData->szPrimaryModeCode, pABTData->szModulationCode, pABTData->szRadarModeName, pABTData->szPlaceNameKor, pABTData->szNickName, pABTData->szFuncCode, pABTData->szPlatform, pABTData->iRadarModePriority, pABTData->iRadarPriority, \
            pABTData->iRadarModeIndex, pABTData->iThreatIndex, pABTData->iPolarization, \
            pABTData->iSignalType, pABTData->fDOAMean, pABTData->fDOAMin, pABTData->fDOAMax, pABTData->fDOADeviation, \
            pABTData->iFreqType, pABTData->iFreqPatternType, pABTData->fFreqPatternPeriodMean, pABTData->fFreqPatternPeriodMin, pABTData->fFreqPatternPeriodMax, pABTData->fFreqMean, pABTData->fFreqMin, pABTData->fFreqMax, pABTData->fFreqDeviation, pABTData->iFreqPositionCount, pABTData->iFreqElementCount, \
            pABTData->iPRIType, pABTData->iPRIPatternType, pABTData->fPRIPatternPeriodMean, pABTData->fPRIPatternPeriodMin, pABTData->fPRIPatternPeriodMax, pABTData->fPRIMean, pABTData->fPRIMin, pABTData->fPRIMax, pABTData->fPRIDeviation, pABTData->fPRIJitterRatio, pABTData->iPRIPositionCount, pABTData->iPRIElementCount, \
            pABTData->fPWMean, pABTData->fPWMin, pABTData->fPWMax, pABTData->fPWDeviation, \
            pABTData->fPAMean, pABTData->fPAMin, pABTData->fPAMax, pABTData->fPADeviation, \
            pABTData->iScanType, pABTData->fMeanScanPeriod, pABTData->fMinScanPeriod, pABTData->fMaxScanPeriod, \
            pABTData->iHasIntraMod, pABTData->fMaxIntraMod, pABTData->fMinIntraMod, \
            pABTData->iPEValid, pABTData->fLatitude, pABTData->fLongitude, pABTData->fHeight, pABTData->fCEP, pABTData->fMajorAxis, pABTData->fMinorAxis, pABTData->fTheta, pABTData->fDistanceErrorOfThreat, \
            pABTData->iValidity, pABTData->uiTotalOfPDW, pABTData->uiCoLOB, buffer3, pABTData->iStat, \
            pABTExtData->bIsManualEdited, pABTExtData->bManualPosEstPreferred, pABTExtData->fManualLatitude, pABTExtData->fManualLatitude );
    
        printf( "[%s]" , szSQLString );
    }

}

#else

#endif

