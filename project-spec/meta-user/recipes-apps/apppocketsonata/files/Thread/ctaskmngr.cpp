// CTaskMngr.cpp: implementation of the CTaskMngr class.
//
//////////////////////////////////////////////////////////////////////

/*
 * 모든 타스크를 관리해 주는 입니다.
 * */

#include "stdafx.h"

#include <signal.h>
#include <cassert>

#include "ctaskmngr.h"

#ifdef __ZYNQ_BOARD__
#include "cjamtech.h"
#endif

#include "cpulsetrk.h"
#include "csignalcollect.h"
#include "cdetectanalysis.h"
#include "ctrackanalysis.h"
#include "cscananalysis.h"
#include "cemittermerge.h"
#include "cusercollect.h"

#include "curbit.h"
#include "cprompt.h"
#include "creclan.h"

//#include "../Utils/clog.h"
#include "../Utils/chwio.h"
#include "../System/csysconfig.h"

#include "../Utils/csingleclient.h"
#include "../Utils/ccommonutils.h"

#include "../Include/globals.h"



#define _DEBUG_

/**
 * @brief CTaskMngr::CTaskMngr
 */
#ifdef _MSSQL_
CTaskMngr::CTaskMngr( int iKeyId, char *pClassName, bool bArrayLanData ) : CThread( iKeyId, pClassName, bArrayLanData ), CMSSQL( & m_theMyODBC )
#else
CTaskMngr::CTaskMngr( int iKeyId, char *pClassName, bool bArrayLanData, const char *pFileName ) : CThread( iKeyId, pClassName, bArrayLanData )
#endif
{
    LOGENTRY;

    Init();

#ifdef _SQLITE_
    try {
        m_pDatabase = new Kompex::SQLiteDatabase( pFileName, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, 0 );
    }
    catch( Kompex::SQLiteException &exception ) {
        std::cerr << "\nException Occured" << std::endl;
        exception.Show();
        std::cerr << "SQLite result code: " << exception.GetSqliteResultCode() << std::endl;
    }
#elif _MSSQL_
    // MSSQL 연결
    CMSSQL::Init();

#else

#endif

}

/**
 * @brief CTaskMngr::~CTaskMngr
 */
CTaskMngr::~CTaskMngr(void)
{

    //GP_SYSCFG->SetMode( enMode );
    //CreateAllAnalysisThread( false );

#ifdef _SQLITE_
    delete m_pDatabase;

#elif _MSSQL_
    m_theMyODBC.Close();


#else

#endif

}

/**
 * @brief 초기화를 수행합니다.
 */
void CTaskMngr::Init()
{
    LOGENTRY;

    InitVar();

    //STR_MessageData sndMsg;

    //CThread theThread1(10), theThread2(11);

    /*

    theThread1.Run( thread_routine );
    theThread2.Run( thread_routine );

    sndMsg.mtype = 1;
    sndMsg.x.opCode = 0x1234;

    int i=0;

    printf("\ntid:%lx\n",pthread_self());
    while( true ){
        printf("main:%d\n",i);
        i++;
        sleep(1);

        if(msgsnd( theThread1.GetKeyId(), (void *)& sndMsg, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) <0)
        {
            perror("msg snd error" );
            printf("KeyID[%d]\n", theThread1.GetKeyId() );

        }
        if(msgsnd( theThread2.GetKeyId(), (void *)& sndMsg, sizeof(STR_MessageData)-sizeof(long), IPC_NOWAIT) <0)
        {
            perror("msg snd error" );
            printf("KeyID[%d]\n", theThread2.GetKeyId() );
        }

        //theThread1.Pend();
        //theThread1.Stop();

    }

    */

}

/**
 * @brief 변수를 초기화 한다.
 */
void CTaskMngr::InitVar()
{
    // 보드 ID를 설정한다.
    g_pTheSysConfig->SetBoardID( GetBoardID() );

}

/**
 * @brief CMain::Run
 */
void CTaskMngr::Run( key_t key )
{
    LOGENTRY;

    CThread::Run( key );

}

/**
 * @brief CMain::_routine
 */
void CTaskMngr::_routine()
{
    LOGENTRY;
    bool bWhile=true;

    m_pMsg = GetDataMessage();

    while( bWhile ) {
        if( QMsgRcv() == -1 ) {
            perror( "QMsgRcv() 에러");
            //break;
        }
        else {
            if( CCommonUtils::IsValidLanData( m_pMsg ) == true ) {
                switch( m_pMsg->uiOpCode ) {
                    case enTHREAD_MODE :
                        SetMode();
                        break;

                    case enTHREAD_DETECTANAL_START :
                        AnalysisStart();
                        break;

                    case enTHREAD_REQ_SHUTDOWN :
                        Shutdown();
                        bWhile = false;
                        break;

                    // 오디오 설정 메시지
                    case enREQ_AUDIO :
                        ReqAudio();
                        break;
                    case enREQ_AUDIO_PARAM :
                        ReqAudioParam();
                        break;

                    // 수집 제어 관련 메시지
                    case enREQ_STOP :
                        StopUserCollecting();
                        break;

                    // 수신기 설정 메시지
                    case enREQ_Band_Enable :
                        BandEnable();
                        break;
                    case enREQ_FMOP_Threshold :
                        FMOPThreshold();
                        break;
                    case enREQ_PMOP_Threshold :
                        PMOPThreshold();
                        break;
                    case enREQ_RX_Threshold :
                        RxThreshold();
                        break;

                    // IPL 관련 메시지
                    case enREQ_IPL_START :
                    case enREQ_IPL_DOWNLOAD :
                    case enREQ_IPL_END :
                        IPLDownload();
                        break;

                    case enTHREAD_REQ_IPLVERSION :
                        ReqIPLVersion();
                        break;

                    // 시스템 변수 관련 메시지
                    case enREQ_SYS :
                        ReqSystemVar();
                        break;

                    case enSYSERROR :
                        printf( "****************************************************************" );
                        break;

                    default:
                        LOGMSG1( enError, "잘못된 명령(0x%x)을 수신하였습니다 !!", m_pMsg->uiOpCode );
                        break;
                }
        }
        else {
            // 아래 메시지는 랜이 끊어진 경우에 에러 메시지를 보여준다.
                 LOGMSG1( enError, "메시지 흐름[0x%X]이 잘못 됐습니다. !!", m_pMsg->uiOpCode );
            }
        }
    }

}

/**
 * @brief 모드 명령을 처리한다.
 */
void CTaskMngr::SetMode()
{
    ENUM_MODE enMode, enMode2;

    _EQUALS3( enMode2, enMode, (ENUM_MODE) m_pMsg->x.uiData );

    LOGMSG1( enDebug, "Set Mode[%d]", enMode );

    g_pTheSysConfig->SetMode( enMode );

    switch( enMode ) {
        case enES_MODE :
        case enEW_MODE :
            CCommonUtils::SendLan( enRES_MODE, & enMode, sizeof(int) );
            break;

        case enREADY_MODE :            
            g_pTheCCUSocket->Stop();

            g_pTheSignalCollect->QMsgSnd( m_pMsg, GetThreadName() );
            g_pTheUserCollect->QMsgSnd( enTHREAD_REQ_COLEND, GetThreadName() );

            ProcessSummary();

            CCommonUtils::SendLan( enRES_MODE, & enMode, sizeof(int) );

            CCommonUtils::CloseSocket();

            g_pTheCCUSocket->Run( _MSG_CCU_KEY );
            LOGMSG( enDebug, "================================================================" );
            break;

        default :
            break;
    }

}

/**
 * @brief 분석 시작 명령을 처리한다.
 */
void CTaskMngr::AnalysisStart()
{

    g_pTheSysConfig->SetMode( enANAL_Mode );

	// 수집 시작
    g_pTheUserCollect->QMsgSnd( enTHREAD_REQ_COLSTART, GetThreadName() );

    // 분석 관련 쓰레드를 삭제한다.
    // CreateAllAnalysisThread();
    
    // 시간 정보로 설정한 후에 시작 명령을 처리한다.
#ifdef _MSC_VER
    
#elif __VXWORKS__
    // time_t tiNow = (time_t) m_pMsg->x.tiNow;    

    struct timespec time_spec;
    
    time_spec.tv_sec = m_pMsg->x.tiNow;
    clock_settime( CLOCK_REALTIME, &time_spec );
    
#elif __linux__
    // tiNow = (time_t) m_pMsg->x.tiNow;    

    // 환경 변수로 타겟 보드일때만 아래 함수를 수행한다.
    stime( & m_pMsg->x.tiNow );
    
#else    
    
#endif

    g_pTheSignalCollect->QMsgSnd( m_pMsg, GetThreadName() );

#ifdef __ZYNQ_BOARD__
    CHWIO::StartCollecting( REG_UIO_DMA_1 );
#endif

}

/**
 * @brief ZYNC 보드의 ID 값을 리턴한다.
 */
ENUM_BoardID CTaskMngr::GetBoardID()
{
    ENUM_BoardID enBoardID=enMaster;

#ifdef _AUTO_ID_

    STR_CONFIG_VAR g_strConfigVar;

#else

    if( g_enBoardId == enPRC_Unknown ) {
        char *pEnv=getenv( "DESKTOP_SESSION" );

        if( pEnv != NULL ) {
            if( strcmp( pEnv, "ubuntu" ) == 0 ) {
                enBoardID = enMaster;
            }
            else {
                enBoardID = enPRC1;
            }
        }
        else {
            enBoardID = enPRC1;
        }
    }
    else {
        enBoardID = g_enBoardId;
    }

    return enBoardID;

#endif

}

/**
 * @brief CTaskMngr::Shutdown
 */
void CTaskMngr::Shutdown()
{
    // 모든 쓰레드에세 SHUTDOWN 메시지를 전송한다.


    //sleep( 1 );

    // 쓰레드 객체를 소멸한다.
    //JAMTEC->ReleaseInstance();
    //PULTRK->ReleaseInstance();
    //SIGCOL->ReleaseInstance();
    //URBIT->ReleaseInstance();
    //PROMPT->ReleaseInstance();
    //RECLAN->ReleaseInstance();

    //ReleaseInstance();

#ifdef __ZYNQ_BOARD__	
    QMsgSnd( JAMTEC->GetKeyId(), enTHREAD_REQ_SHUTDOWN );
    QMsgSnd( PULTRK->GetKeyId(), enTHREAD_REQ_SHUTDOWN );
#endif
    
    //QMsgSnd( URBIT->GetKeyId(), enTHREAD_REQ_SHUTDOWN );    
    //QMsgSnd( SIGCOL->GetKeyId(), enTHREAD_REQ_SHUTDOWN );
    //QMsgSnd( RECCCU->GetKeyId(), enTHREAD_REQ_SHUTDOWN );

    g_Loop = false;

}

/**
 * @brief 시스템의 자원과 운용 소프트웨어 상에서 자원 정보를 출력한다.
 */
void CTaskMngr::ProcessSummary()
{
    LOGMSG( enDebug, "--------------------------------------------------------" );
    LOGMSG2( enDebug, "  Total of Thread : %d\t   Total of Thread : %d" , GetCoThread(), GetCoThread() );
    LOGMSG( enDebug, "--------------------------------------------------------" );
}

/**
 * @brief CTaskMngr::IPLVersion
 */
void CTaskMngr::ReqIPLVersion()
{
    STR_IPL_VERSION strIPLVersion;

    strIPLVersion.uiIPLVersion = (m_theIPL.getIPLStart())->uiIPLVersion;
    strIPLVersion.uiStatus = strIPLVersion.uiIPLVersion != _spZero ? _spPass : _spFail;
    CCommonUtils::SendLan( enIPL_VERSION, & strIPLVersion, sizeof(strIPLVersion) );
}

/**
 * @brief CTaskMngr::IPLDownload
 */
void CTaskMngr::IPLDownload()
{
    int iWriteStatus;
    UNI_LAN_DATA *pLanData;

    pLanData = ( UNI_LAN_DATA * ) & m_pMsg->x.szData[0];

    switch( m_pMsg->uiOpCode ) {
    case enREQ_IPL_START :
        m_theIPL.setIPLStart( & pLanData->strIPLStart );
        DeleteIPL();
        break;

    case enREQ_IPL_DOWNLOAD :
        m_theIPL.trIPL( (STR_IPL *) GetRecvData() );
        m_theIPL.setIPL( (STR_IPL *) GetRecvData() );
        InsertIPL( m_theIPL.GetTotalIPL()-1 );        

        iWriteStatus = (int) ( 0.5 + ( 100. * m_theIPL.GetTotalIPL() ) / (m_theIPL.getIPLStart())->uiCountOfIPL );
        CCommonUtils::SendLan( enIPL_WRITESTATUS, & iWriteStatus, sizeof(int) );
        LOGMSG1( enNormal, "IPL WriteStatus[%d]" , iWriteStatus );
        break;

    case enREQ_IPL_END :
        if( g_pTheEmitterMerge != NULL ) { g_pTheEmitterMerge->QMsgSnd( m_pMsg, GetThreadName() ); }
        break;

    default :
        break;

    }
}

/**
 * @brief CTaskMngr::DeleteIPL
 * @param pszELNOT
 */
void CTaskMngr::DeleteIPL( char *pszELNOT )
{

#ifdef _SQLITE_
    if( pszELNOT != NULL ) {
        int iRadarIndex, iRadarModeIndex;

        sprintf( m_szSQLString, "SELECT RADAR_INDEX FROM RADAR WHERE ELNOT='%s'" , pszELNOT );

        try {
            Kompex::SQLiteStatement stmt( m_pDatabase );
            stmt.Sql( m_szSQLString );

            if( stmt.FetchRow() ) {
                iRadarIndex = stmt.GetColumnInt(0);

                sprintf( m_szSQLString, "SELECT RADAR_MODE_INDEX FROM RADAR_MODE_LIFECYCLE WHERE RADAR_INDEX='%d'" , iRadarIndex );
                stmt.Sql( m_szSQLString );

                if( stmt.FetchRow() ) {
                    iRadarModeIndex = stmt.GetColumnInt(0);

                    sprintf( m_szSQLString, "DELETE FROM RADAR_MODE WHERE RADAR_MODE_INDEX='%d'", iRadarModeIndex );
                    stmt.Sql( m_szSQLString );
                }

                sprintf( m_szSQLString, "DELETE FROM RADAR WHERE RADAR_INDEX='%d'", iRadarIndex );
                stmt.Sql( m_szSQLString );

                sprintf( m_szSQLString, "DELETE FROM RADAR_MODE_LIFECYCLE WHERE RADAR_INDEX='%d'", iRadarIndex );
                stmt.Sql( m_szSQLString );
            }

            // do not forget to clean-up
            stmt.FreeQuery();
        }
        catch( Kompex::SQLiteException &exception ) {
            std::cerr << "\nException Occured" << std::endl;
            exception.Show();
            std::cerr << "SQLite result code: " << exception.GetSqliteResultCode() << std::endl;
        }

        //-- m_iTotalIPL;
    }
    else {
        try {
            Kompex::SQLiteStatement stmt( m_pDatabase );

            // 레이더
            sprintf( m_szSQLString, "DELETE FROM RADAR" );
            stmt.SqlStatement( m_szSQLString );

            // 레이더 모드
            sprintf( m_szSQLString, "DELETE FROM RADAR_MODE" );
            stmt.SqlStatement( m_szSQLString );

            // 레이더 & 레이더 모드 관계
            sprintf( m_szSQLString, "DELETE FROM RADAR_MODE_LIFECYCLE" );
            stmt.SqlStatement( m_szSQLString );

            // do not forget to clean-up
            stmt.FreeQuery();  
        }
        catch( Kompex::SQLiteException &exception ) {
            std::cerr << "\nException Occured" << std::endl;
            exception.Show();
            std::cerr << "SQLite result code: " << exception.GetSqliteResultCode() << std::endl;
        }

    }

#elif _MSSQL_

#endif

}

/**
 * @brief CTaskMngr::InsertIPL
 */
void CTaskMngr::InsertIPL( int iIndex )
{
#ifdef _SQLITE_
    STR_IPL *pstrIPL;
    char szDate[100]={0};

    int iRadarIndex, iRadarModeIndex=0;

    pstrIPL = m_theIPL.getIPL( iIndex );

    CCommonUtils::getStringPresentTime( szDate );

    // 업데이트 처리
    try {
        Kompex::SQLiteStatement stmt( m_pDatabase );

        iRadarIndex = IsThrereELNOT( pstrIPL->elintNot );
        if( iRadarIndex >= 0 ) {
            // DeleteIPL( pstrIPL->elintNot );
            sprintf( m_szSQLString, "UPDATE RADAR SET PRIORITY='%d', DATE_LAST_UPDATED='%s' WHERE RADAR_INDEX='%d'" , pstrIPL->thrLev, szDate, iRadarIndex );
            stmt.SqlStatement( m_szSQLString );

            sprintf( m_szSQLString, "UPDATE RADAR_MODE SET DATE_LAST_UPDATED='%s', SIGNAL_TYPE='%s', \
    RF_TYPICAL_MIN='%d', RF_TYPICAL_MAX='%d', RF_NUM_POSITIONS='%d', RF_PATTERN_PERIOD_MIN='%d', RF_PATTERN_PERIOD_MAX='%d', \
    PRI_TYPICAL_MIN='%d', PRI_TYPICAL_MAX='%d', PRI_NUM_POSITIONS='%d', PRI_PATTERN_PERIOD_MIN='%d', PRI_PATTERN_PERIOD_MAX='%d', \
    PRIORITY='%d', RF_TYPE='%d', PRI_TYPE='%d', PD_TYPICAL_MIN='%d', PD_TYPICAL_MAX='%d', \
    SCAN_PRIMARY_TYPE='%d', SCAN_PRIMARY_TYPICAL_MIN='%d', SCAN_PRIMARY_TYPICAL_MAX='%d', \
    WHERE RADAR_MODE_INDEX='%d'" , \
            szDate, _SignalType[pstrIPL->sigType], \
            pstrIPL->frq.low, pstrIPL->frq.hgh, pstrIPL->frq.swtLev, pstrIPL->frq.ppLow, pstrIPL->frq.ppHgh, \
            pstrIPL->pri.low, pstrIPL->pri.hgh, pstrIPL->pri.swtLev, pstrIPL->pri.ppLow, pstrIPL->pri.ppHgh, \
            pstrIPL->thrLev, pstrIPL->frq.type, pstrIPL->pri.type, pstrIPL->pw.low, pstrIPL->pw.hgh, \
            pstrIPL->as.type, pstrIPL->as.prdLow, pstrIPL->as.prdHgh, iRadarModeIndex );
            stmt.SqlStatement( m_szSQLString );

        }
        else {
            // 레이더
            sprintf( m_szSQLString, "INSERT INTO RADAR ( RADAR_INDEX, DATE_LAST_UPDATED, ELNOT, NICKNAME, FUNCTION_CODE, PRIORITY ) VALUES \
                                    ( %d, '%s', '%s', 'NICK%d', 'ZZ', %d )" , \
                                    pstrIPL->noIPL, szDate, pstrIPL->elintNot, pstrIPL->noIPL, pstrIPL->thrLev );
            stmt.SqlStatement( m_szSQLString );

            // 레이더 모드
            sprintf( m_szSQLString, "INSERT INTO RADAR_MODE ( RADAR_MODE_INDEX, FUNCTION_CODE, SIGNAL_TYPE, \
                                    DATE_CREATED, \
                                    RF_TYPICAL_MIN, RF_TYPICAL_MAX, RF_NUM_POSITIONS, RF_PATTERN_PERIOD_MIN, RF_PATTERN_PERIOD_MAX, \
                                    PRI_TYPICAL_MIN, PRI_TYPICAL_MAX, PRI_NUM_POSITIONS, PRI_PATTERN_PERIOD_MIN, PRI_PATTERN_PERIOD_MAX, \
                                    PRIORITY, RF_TYPE, PRI_TYPE, \
                                    PD_TYPICAL_MIN, PD_TYPICAL_MAX, \
                                    SCAN_PRIMARY_TYPE, SCAN_PRIMARY_TYPICAL_MIN, SCAN_PRIMARY_TYPICAL_MAX ) VALUES \
                                    ( %d, 'ZZ', '%s', \
                                    '%s', \
                                    %d, %d, %d, %d, %d, \
                                    %d, %d, %d, %d, %d, \
                                    %d, %d, %d, \
                                    %d, %d, \
                                    %d, %d, %d )" , \
                                    pstrIPL->noIPL, _SignalType[pstrIPL->sigType], \
                                    szDate, \
                                    pstrIPL->frq.low, pstrIPL->frq.hgh, pstrIPL->frq.swtLev, pstrIPL->frq.ppLow, pstrIPL->frq.ppHgh, \
                                    pstrIPL->pri.low, pstrIPL->pri.hgh, pstrIPL->pri.swtLev, pstrIPL->pri.ppLow, pstrIPL->pri.ppHgh, \
                                    pstrIPL->thrLev, pstrIPL->frq.type, pstrIPL->pri.type, \
                                    pstrIPL->pw.low, pstrIPL->pw.hgh, \
                                    pstrIPL->as.type, pstrIPL->as.prdLow, pstrIPL->as.prdHgh );
            stmt.SqlStatement( m_szSQLString );

            // 레이더 모드 라이프 사이클
            sprintf( m_szSQLString, "INSERT INTO RADAR_MODE_LIFECYCLE ( RADAR_INDEX, RADAR_MODE_INDEX, RADAR_MODE_NAME, MODE_CODE ) VALUES ( %d, %d, '%s', 'ZZ' )" , \
                pstrIPL->noIPL, pstrIPL->noIPL, pstrIPL->elintName );
            stmt.SqlStatement( m_szSQLString );

        }

        // do not forget to clean-up
        stmt.FreeQuery();  

    }
    catch( Kompex::SQLiteException &exception ) {
        std::cerr << "\nException Occured" << std::endl;
        exception.Show();
        std::cerr << "SQLite result code: " << exception.GetSqliteResultCode() << std::endl;
    }
#elif _MSSQL_

#else

#endif

}

/**
 * @brief CTaskMngr::IsThrereELNOT
 * @param pszELNOT
 * @return
 */
int CTaskMngr::IsThrereELNOT( char *pszELNOT )
{
    int iRadarIndex=-1;

#ifdef _SQLITE3_
    Database *pDatabase;

    pDatabase = GetDatabase();

    sprintf( m_szSQLString, "SELECT RADAR_INDEX FROM RADAR WHERE ELNOT='%s'", pszELNOT );
    SQLite::Statement query( *pDatabase, m_szSQLString );

    if( query.executeStep() ) {
        iRadarIndex = query.getColumn(0).getInt();
    }
#endif

    return iRadarIndex;
}

/**
 * @brief CTaskMngr::ReqAudio
 */
void CTaskMngr::ReqAudio()
{
    UNI_LAN_DATA *pLanData;

    pLanData = ( UNI_LAN_DATA * ) GetRecvData();

    LOGMSG1( enNormal, "오디오 [%s] 합니다." , on_off[pLanData->bAudioSW] );

}

/**
 * @brief CTaskMngr::ReqAudioParam
 */
void CTaskMngr::ReqAudioParam()
{
    char buffer[100];
    STR_AUDIO_PARAM *pstrAudioParam;

    pstrAudioParam = ( STR_AUDIO_PARAM * ) GetRecvData();

    sprintf( buffer, "%d,%d/%d,%d/%d,%d/%d,%d" , pstrAudioParam->iLowerBC, pstrAudioParam->iUpperBC, pstrAudioParam->iFromAoa, pstrAudioParam->iToAoa, pstrAudioParam->iLowerFrq, pstrAudioParam->iUpperFrq, pstrAudioParam->iFromPa, pstrAudioParam->iToPa );
    LOGMSG1( enNormal, "오디오 [%s] 설정 합니다." , buffer );

}

/**
 * @brief CTaskMngr::BaneEnable
 */
void CTaskMngr::BandEnable()
{
    //char buffer[100];

    STR_BAND_ENABLE *pstrBandEnable;

    pstrBandEnable = ( STR_BAND_ENABLE * ) GetRecvData();

    if( pstrBandEnable->iBand != 0 ) {
        //CCommonUtils::GetStringBand( buffer, pstrBandEnable->iBand );

        LOGMSG2( enNormal, "대역[%d]을 설정[%d] 합니다." , pstrBandEnable->iBand, pstrBandEnable->iOnOff );
    }
    else {
        LOGMSG( enNormal, "대역 설정을 전혀 수행하지 않습니다." );
    }

}

/**
 * @brief CTaskMngr::FMOPThreshold
 */
void CTaskMngr::FMOPThreshold()
{
    //char buffer[100];

    STR_FMOP_THRESHOLD *pstrBandEnable;

    pstrBandEnable = ( STR_FMOP_THRESHOLD * ) GetRecvData();

    if( pstrBandEnable->iBand != 0 ) {
        //CCommonUtils::GetStringBand( buffer, pstrBandEnable->iBand );

        LOGMSG2( enNormal, "대역[%d]을 FMOP 임계값[%d]을 설정 합니다." , pstrBandEnable->iBand, pstrBandEnable->iThreshold );
    }
    else {
        LOGMSG( enNormal, "대역 설정을 전혀 수행하지 않습니다." );
    }
}

/**
 * @brief CTaskMngr::PMOPThreshold
 */
void CTaskMngr::PMOPThreshold()
{
    //char buffer[100];

    STR_PMOP_THRESHOLD *pstrBandEnable;

    pstrBandEnable = ( STR_PMOP_THRESHOLD * ) GetRecvData();

    if( pstrBandEnable->iBand != 0 ) {
        //CCommonUtils::GetStringBand( buffer, pstrBandEnable->iBand );

        LOGMSG2( enNormal, "대역[%d]을 PMOP 임계값[%d]을 설정 합니다." , pstrBandEnable->iBand, pstrBandEnable->iThreshold );
    }
    else {
        LOGMSG( enNormal, "대역 설정을 전혀 수행하지 않습니다." );
    }
}

/**
 * @brief CTaskMngr::RxThreshold
 */
void CTaskMngr::RxThreshold()
{
    //char buffer[100];

    STR_RX_THRESHOLD *pstrRxThreshold;

    pstrRxThreshold = ( STR_RX_THRESHOLD * ) GetRecvData();

    if( pstrRxThreshold->iBand != 0 ) {
        //CCommonUtils::GetStringBand( buffer, pstrRxThreshold->iBand );

#ifdef __ZYNQ_BOARD__
        CHWIO::WriteReg( BRAM_CTRL_PPFLT, DET_THD_COR, pstrRxThreshold->uiCorThreshold );
        CHWIO::WriteReg( BRAM_CTRL_PPFLT, DET_THD_MAG, pstrRxThreshold->uiMagThreshold );
        CHWIO::WriteReg( BRAM_CTRL_PPFLT, DET_ONLY_COR, 0x0 );
#endif

        LOGMSG2( enNormal, "대역 [%d]을 설정[%d] 합니다." , pstrRxThreshold->iBand, pstrRxThreshold->iThreshold );
    }
    else {
        LOGMSG( enNormal, "대역 설정을 전혀 수행하지 않습니다." );
    }
}

/**
 * @brief CTaskMngr::StopUserCollecting
 */
void CTaskMngr::StopUserCollecting()
{
    LOGMSG( enDebug, " 수집 설정을 종료합니다." );

#ifdef __ZYNQ_BOARD__
    CHWIO::StopCollecting( REG_UIO_DMA_1 );
#endif

}

/**
 * @brief		ReqSystemVar
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/11/23 19:55:29
 * @warning		
 */
void CTaskMngr::ReqSystemVar()
{
    STR_SYSCONFIG *pstrSysConfig;
    
    pstrSysConfig = g_pTheSysConfig->GetSysConfig();
    CCommonUtils::SendLan( enRES_SETSYS, pstrSysConfig, sizeof(STR_SYSCONFIG) );
}