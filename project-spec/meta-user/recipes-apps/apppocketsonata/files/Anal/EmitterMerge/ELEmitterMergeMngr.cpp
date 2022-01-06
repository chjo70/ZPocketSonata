/**
 * @file      ELEmitterMergeMngr.cpp
 * @brief     위협 관리 처리하는 클래스
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-07-19, 오후 2:02
 * @warning
 */

#include "stdafx.h"

#include <vector>

#include <string.h>

//#define _POSITION_ESTIMATION_MERGE_

// LOB/빔/벙사체의 SEQ 번호를 자동으로 하고 수행할 때
//#define _AUTO_SEQUENCE_

//#define UPDATETODB_THREAD

//#define _LOAD_CED_LIBRARY_

#include "ELEmitterMergeMngr.h"
#include "../Identify/Identify.h"
#include "../Identify/ELUtil.h"
#include "./PositionEstimationAlg.h"
#include "../../Anal/INC/AetIPL.h"
//#include "../Task/ELInsertDBMngr.h"

#include "./InverseMethod/CInverseMethod.h"

#include "./ELStringDefn.h"

#include "../../System/csysconfig.h"

#include "./UTM/UTM.h"

#include "../../Include/globals.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#define CRTDBG_MAP_ALLOC
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAX_AET_IDCANDIDATE				(1000+MAX_IDCANDIDATE)

bool CompareMergeCandidate( SELMERGE_CANDIDATE stMergeCanA, SELMERGE_CANDIDATE stMergeCanB );

int CELEmitterMergeMngr::m_CoInstance = 0;
int CELEmitterMergeMngr::m_nSeqNum = 0;

//////////////////////////////////////////////////////////////////////////
/*!
 * @brief     생성자로 CELEmitterMergeMngr 클래스를 생성하고 멤버 변수 초기화를 수행함.
                            그리고 메모리를 항당하고 DB를 검색하여 인덱스를 결정한다.
 * @param     bSimulator 모의기 여부 플레그
 * @return    리턴값 없음
 * @version   0.0.1
 * @date      2016-01-29 오후 5:30
 * @warning
 */
#ifdef _MSSQL_
CELEmitterMergeMngr::CELEmitterMergeMngr(bool bDBThread, CODBCDatabase *pMyODBC ) : CMSSQL( pMyODBC )
#else
CELEmitterMergeMngr::CELEmitterMergeMngr(bool bDBThread, const char *pFileName )
#endif
{
    // 멤머 변수 초기화...
    m_CoInstance = 0;

    m_bDBThread = bDBThread;

#ifdef _ELINT_
    m_lOpInitID = 0;
#else

#endif

#ifdef _SQLITE_
    try {
        m_pDatabase = new Kompex::SQLiteDatabase( pFileName, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, 0 );

    }
    catch( Kompex::SQLiteException &exception ) {
        std::cerr << "\nException Occured" << std::endl;
        exception.Show();
        std::cerr << "SQLite result code: " << exception.GetSqliteResultCode() << std::endl;
    }
    
#elif _NO_SQLITE_
#elif _MSSQL_
    // MSSQL 연결
    CMSSQL::Init();
#endif

    // 메모리 할당
    AllocMemory();

    // 초기화
    Init();

    LoadCEDLibrary( NULL, 0, 0 );

    // 최근 위협을 재로딩하여 위협 관리를 수행함.
    RecoverThreat();

    if( m_bDBThread == true ) {
        //GP_MGR_INSERTDB;
    }
    else {
        //CELInsertDBMngr::Cleanup();
    }

}

/**
 * @brief     위협 정보를 복구 하기 위한 처리
 * @param     void
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2018-02-10, 오전 9:45
 * @warning
 */
void CELEmitterMergeMngr::RecoverThreat()
{
    //LogPrint( "\n 최근 위협 테이블을 불러들여 위협 관리를 재로딩합니다." );

    // 방사체 제원을 불러들인다.

    // 빔 제원을 불러들인다.

}

//////////////////////////////////////////////////////////////////////////
/*!
 * @brief     소멸자로서 생성자에 소멸한 객체와 메모리를 해지한다.
 * @return    리턴값 없음
 * @version   0.0.1
 * @author    이정남 (jeongnam.lee@lignex1.com)
 * @date      2016-01-29 오후 5:30
 * @warning
 */
CELEmitterMergeMngr::~CELEmitterMergeMngr(void)
{

#ifdef _SQLITE_
    delete m_pDatabase;

#elif _MS_SQL_
    m_theMyODBC.Close();

#endif

    FreeMemory();

}

/**
 * @brief     이 클래스에서 사용할 모든 메모리(위협 관리 노드)를 생성한다.
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-05, 오후 2:32
 * @warning
 */
void CELEmitterMergeMngr::AllocMemory()
{
#ifdef _SQLITE_
    // SQLITE 파일명 생성하기
    char szSQLiteFileName[100];

    strcpy( szSQLiteFileName, CEDEOB_SQLITE_FOLDER );
    strcat( szSQLiteFileName, "/" );
    strcat( szSQLiteFileName, CEDEOB_SQLITE_FILENAME );       

    m_pIdentifyAlg = new CELSignalIdentifyAlg( szSQLiteFileName );

    m_pszSQLString = ( char *) malloc( MAX_SQL_SIZE );

#elif defined(_MSSQL_)
    CODBCDatabase *pMyODBC=GetDBCDatabase();
    m_pIdentifyAlg = new CELSignalIdentifyAlg( pMyODBC );

    m_pszSQLString = ( char *) malloc( MAX_SQL_SIZE );

#else
    m_pIdentifyAlg = new CELSignalIdentifyAlg( NULL );

#endif
    
    m_pUniThreat = ( UELTHREAT *) malloc( sizeof(UELTHREAT) * TOTAL_ITEMS_OF_THREAT_NODE );

    m_pABTtoH000 = ( unsigned short * ) malloc( sizeof(unsigned short) * TOTAL_UNDEF_ID_NUMBER );

    m_pVecLOBs = new std::vector<STR_LOBS> [TOTAL_ITEMS_OF_THREAT_NODE];

    g_pTheELEnvironVariable = new CELEnvironVariable();

    //m_piCandidate = ( int * ) malloc( sizeof(int) * MAX_AET_IDCANDIDATE );

    m_pTheThreatRoot = new CELThreat;

    // LOB/빔/방사체 결과 벡터
    m_VecLOBData.reserve( 100 );
    m_VecABTData.reserve( 100 );
    m_VecAETData.reserve( 100 );

}

/**
 * @brief     이 클래스에서 사용할 모든 메모리를 해지한다.
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-05, 오후 2:32
 * @warning
 */
void CELEmitterMergeMngr::FreeMemory()
{
#if defined(_SQLITE_) || defined(_MSSQL_)
    free( m_pszSQLString );
#else

#endif

    _SAFE_FREE( m_pUniThreat );
    _SAFE_FREE( m_pABTtoH000 );

    _SAFE_DELETE( m_pIdentifyAlg );
    _SAFE_DELETE( g_pTheELEnvironVariable );
    delete [] m_pVecLOBs;

    if( m_pTheThreatRoot != NULL ) {
        m_pTheThreatRoot->RemoveAll();
        delete m_pTheThreatRoot;
    }

}

/**
 * @brief     미식별 번호, 위협 관리 등을 초기화한다.
 * @param     void
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-07-23, 오전 10:32
 * @warning
 */
void CELEmitterMergeMngr::Init()
{
    //bool bRet;

    ResetToLoadCEDEOBLibrary();

    // 시스템 변수 초기화
    m_pSEnvironVariable = g_pTheELEnvironVariable->GetEnvrionVariable();

    // 미식별 테이블 초기화
    if( m_pABTtoH000 != nullptr )
    {
        unsigned short *pABTtoH000;
        pABTtoH000 = m_pABTtoH000;
        for( int i = 0; i < TOTAL_UNDEF_ID_NUMBER; ++i )
        {
            *pABTtoH000 = (unsigned short) -1;
            ++ pABTtoH000;
        }
    }

    // H0000 초기화
    m_szH0000[0] = 0;
    m_iH000 = 1;

    // 위협 관리 변수 초기화
    // 임무가 바뀌면 아래 함수를 호출해야 함.
    InitDataFromDB();

    //memset( m_aucTaskID, 0, sizeof(m_aucTaskID) );

    InitOfThreat();

    //m_bGenNewEmitter = false;

    //m_szELNOTFromGenNewEmitter[0] = NULL;

    m_pABTThreat = NULL;
    m_pAETThreat = NULL;

    //GP_MGR_INSERTDB->Init();

    //m_VecTaskID2NameTable.clear();

    Start();

}

/**
 * @brief     위협 관리 등을 초기화한다.
 * @param     void
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-07-23, 오전 10:32
 * @warning
 */
void CELEmitterMergeMngr::InitOfThreat()
{
    //m_bGenNewEmitter = false;

    if( m_pTheThreatRoot != NULL ) {
        m_pTheThreatRoot->RemoveAll();
    }

    //GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_MSG, E_WARNING_NONE, enumGMEO_DEVICE, enumGMEI_DEVICE, "위협 을 전부 삭제합니다 !!" );
}

/**
 * @brief CELEmitterMergeMngr::Start
 */
void CELEmitterMergeMngr::Start( bool bScanInfo )
{
    m_VecLOBData.clear();
    m_VecABTData.clear();
    m_VecAETData.clear();

    m_pAETThreat = NULL;
    m_pABTThreat = NULL;

    m_pUpdateAETThreat = NULL;
    m_pUpdateABTThreat = NULL;

}

//////////////////////////////////////////////////////////////////////////
/*!
 * @brief     수신한 LOB 데이터와 링크 번호, 필터링 조건, 재연 등의 값을 입력하여 위협 관리를 수행한다.
                            위협 관리를 수행할 메인 시작 위치이다.
 * @param     i_vecThreatInfo 위협 관리가 처리한 결과가 저장. LOB/빔/방사체 정보를 전시할 테이블의 인덱스 정보가 저장
 * @param     *i_pData LOB 메시지의 헤더 정보 데이터
 * @param     *i_pLOBDataGrp LOB 메시지의 실제 데이터
 * @param     i_nLinkNum 링크 번호
 * @param     i_bIsFilteredLOB 필터 여부 플레그 정보
 * @param     i_bIsMaster 마스터 사용여부 (연동기1/2 중에서 마스터 인 것을 선택) 이 플레그 값이 true 이면 따라 위협 처리를 수행하며 false 일때는 LOB 데이터만 DB에 저장하는 것으로 구분됨
 * @param     i_bCheckLOB LOB 체크 여부 플레그
 * @param     i_bReplay 재연 여부 플레그
 * @return    위협 관리가 정상적으로 처리되면 true 그렇지 않으면 false
 * @version   0.0.1
 * @author    이정남 (jeongnam.lee@lignex1.com)
 * @date      2016-01-29 오후 5:53
 * @warning
 */
bool CELEmitterMergeMngr::ManageThreat( SRxLOBHeader* pLOBHeader, SRxLOBData* pLOBData, SLOBOtherInfo *pLOBOtherInfo, bool bScanInfo, bool bIsFilteredLOB, bool bCheckLOB )
{
    bool bMerge;

    //DWORD dwTime = GetTickCount();
    SetScanInfo( bScanInfo );

#ifdef _POCKETSONATA_
    Log( enNormal, "[%4d] %s %5.1f [%s] (%7.1f,%7.1f)[MHz] [%s] (%7.1f,%7.1f)[us] (%7.1f,%7.1f)[ns] (%5.1f,%5.1f)[dBm], (%d,%5.1f[us]) [%d]" ,
        pLOBData->uiLOBID, g_szAetSignalType[pLOBData->iSignalType],
        pLOBData->fDOAMean,
        g_szAetFreqType[pLOBData->iFreqType], pLOBData->fFreqMin, pLOBData->fFreqMax,
        g_szAetPriType[pLOBData->iPRIType], pLOBData->fPRIMin, pLOBData->fPRIMax,
        pLOBData->fPWMin, pLOBData->fPWMax,
        pLOBData->fPAMin, pLOBData->fPAMax,
        pLOBData->iScanType, pLOBData->fScanPeriod,
        pLOBData->iNumOfPDW
        );
    // WhereIs;    */

#elif _ELINT_
    Log( enNormal, "[%s-%4d] %s %5.1f [%s] (%7.1f,%7.1f)[MHz] [%s] (%7.1f,%7.1f)[us] (%7.1f,%7.1f)[ns] (%5.1f,%5.1f)[dBm], [%d]" ,
        pLOBData->aucTaskID,
        pLOBData->uiLOBID, g_szAetSignalType[pLOBData->iSignalType],
        pLOBData->fDOAMean,
        g_szAetFreqType[pLOBData->iFreqType], pLOBData->fFreqMin, pLOBData->fFreqMax,
        g_szAetPriType[pLOBData->iPRIType], pLOBData->fPRIMin, pLOBData->fPRIMax,
        pLOBData->fPWMin, pLOBData->fPWMax,
        pLOBData->fPAMin, pLOBData->fPAMax,
        pLOBData->iNumOfPDW
        );
#else

#endif

    //m_pVecThreatInfo = GP_MGR_LOB->GetVecThreatInfo();

#ifdef _POCKETSONATA_
#elif _ELINT_
    // strcpy_s( szTaskID, pLOBData->aucTaskID );
#endif
    
    // LOB 데이터를 사전 세팅하기위한 함수
    LOBPreSetting( pLOBHeader, pLOBData, pLOBOtherInfo );
    
    // 0. 위협 라이브러러리 로딩
    LoadCEDLibrary( NULL, pLOBData->fFreqMin, pLOBData->fFreqMax );
    //LoadCEDLibrary( NULL, 0, 0 );
    
    // 위협 처리
    // 항공으로 수신한 위협 데이터 개수 만큼 로드하여 위협 관리를 처리한다. -> 의미가 없음. -> 없앰.
    // 1. CED 신호 식별을 수행한다.
    IdentifyLOB( pLOBData );
    
    // 2. LOB와 기존 위협 간의 비교
    bMerge = ManageThreat( & m_LOBDataExt, bCheckLOB );

    // 3. LOB 식별 결과를 DB에 기록한다. (식별 결과와 AET, ABT 번호를 할당하여 DB 테이블에 저장함.)
    InsertLOB( & m_LOBDataExt, bIsFilteredLOB );
    
    // 4. 미식별 ELNOT 값 생성
    if( bMerge == false ) {
        IncH0000( m_LOBDataExt.aetAnal.idInfo.nCoRadarModeIndex );
    }

    // 5. 전시할 에미터 번호를 기록한다.
    AddThreatInfo();

    //////////////////////////////////////////////////////////////////////////
    // 6. LOB 클러스터링 결과 수행
    // RunLOBClusteringResult();

    // 7. ABT/AET간 병합 수행, 연동기1 이고 운용자 요구 생성이 아니고 DB 가 연결되었을 때만 빔 병합을 수행
    // ManageABTs( bMerge & !m_bScanProcess );

    // 8. 위협 관리 삭제 처리
    //ResetABT();

    // DB 인덱스 번호 증가 : 매우 중요
    NextSeqNum();

    //LogPrint("\n========================================== ManageThreat 시간 : %d ms", (int)((GetTickCount() - dwTime) / 1));

    return bMerge;
}

/**
 * @brief CELEmitterMergeMngr::ManageThreat
 * @param pLOBHeader
 * @param pSCNData
 * @param pLOBOtherInfo
 * @param bIsFilteredLOB
 * @param bCheckLOB
 * @return
 */
bool CELEmitterMergeMngr::ManageThreat( SRxLOBHeader* pLOBHeader, SRxScanData* pSCNData, SLOBOtherInfo *pLOBOtherInfo, bool bIsFilteredLOB, bool bCheckLOB )
{

#ifdef _POCKETSONATA_
    //char szTaskID[LENGTH_OF_TASK_ID];

    printf( "[E%4d][B%4d] %d %.2f [ms]\n" ,
            pSCNData->uiAETID, pSCNData->uiABTID, pSCNData->uiScnTyp, pSCNData->fScnPrd );
    Log( enNormal, "[E%4d][B%4d] %d %.2f [ms]" , pSCNData->uiAETID, pSCNData->uiABTID, pSCNData->uiScnTyp, pSCNData->fScnPrd );
#else


#endif

    return true;

}

/**
 * @brief CELEmitterMergeMngr::PrintAllABTData
 */
void CELEmitterMergeMngr::PrintAllABTData()
{
    vector<SRxABTData>::iterator iter;

    for( iter=m_VecABTData.begin() ; iter != m_VecABTData.end() ; ++iter ) {
//         Log( enNormal, "[%4d-%4d] %s [%s] (%7.1f,%7.1f)[MHz] [%s] (%7.1f,%7.1f)[us] (%7.1f,%7.1f)[ns] (%5.1f,%5.1f)[dBm], [R%2d/T%2d], [%.4f/%.4f/%.1f/%.1f/%.1f/%.1f/%.1f]" ,
//             (*iter).uiAETID, (*iter).uiABTID,
//             g_szAetSignalType[(*iter).iSignalType],
//             g_szAetFreqType[(*iter).iFreqType], (*iter).fFreqMin, (*iter).fFreqMax,
//             g_szAetPriType[(*iter).iPRIType], (*iter).fPRIMin, (*iter).fPRIMax,
//             (*iter).fPWMin, (*iter).fPWMax,
//             (*iter).fPAMin, (*iter).fPAMax,
//             (*iter).iRadarModeIndex, (*iter).iThreatIndex,
//             (*iter).fLatitude, (*iter).fLongitude, (*iter).fCEP, (*iter).fMajorAxis, (*iter).fMinorAxis, (*iter).fTheta, (*iter).fDistanceErrorOfThreat
//             );

    }
}

/**
 * @brief     InitLOB
 * @param     void
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-10-23, 오후 11:46
 * @warning
 */
void CELEmitterMergeMngr::InitLOB()
{
    // m_pLOBData->uiABTID_LinkNum = 0;

}

/**
 * @brief     LoadCEDLibrary
 * @param     unsigned char * aucTaskID
 * @param     int fFreqMin
 * @param     int fFreqMax
 * @param     EnumLibType eCEDLibType
 * @param     EnumLibType eEOBLibType
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-02-21, 오후 1:28
 * @warning
 */
void CELEmitterMergeMngr::LoadCEDLibrary( char *aucTaskID, float fFreqMin, float fFreqMax )
{
    /*! \todo   아래를 쓰레드로 해야 함.
        \author 조철희 (churlhee.jo@lignex1.com)
        \date 	2017-08-22 22:42:45
    */
    if( m_nLoadCEDEOBLibrary > _spZero ) {
        Log( enNormal, "Loading CED/EOB library..." );

        m_pIdentifyAlg->LoadCEDLibrary2();
        m_pIdentifyAlg->LoadEOBLibrary2();

        DisableToLoadCEDEOBLibrary();
    }

}

/**
 * @brief     CED/EOB 불러온 후에 그 플레그 값을 초기화 한다.
 * @param     void
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-08-22, 오후 10:42
 * @warning
 */
void CELEmitterMergeMngr::DisableToLoadCEDEOBLibrary()
{
    -- m_nLoadCEDEOBLibrary;

    // 1 이상인 경우에 최대 1개로 설정한다.
    if( m_nLoadCEDEOBLibrary > 1 ) {
        m_nLoadCEDEOBLibrary = 1;
    }

    // 잘못 될 경우의 예외 처리 추가
    if( m_nLoadCEDEOBLibrary < 0 ) { //DTEC_Else
        ResetToLoadCEDEOBLibrary();
    }

}

/**
 * @brief     수신한 LOB 에 대해서 업데이트 변경건에 대해서 ABT 간 병합 비교 처리한다.
 * @param     bool bMerge
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-12-06, 오후 2:59
 * @warning
 */
void CELEmitterMergeMngr::ManageABTs( bool bMerge )
{
    bool bMatch=false, bRemoveAET;

    CELThreat *pThreatAET=NULL, *pThreatABT=NULL;

    SELAETDATA *pCmpAETData=NULL;

    SRxABTData *pRefABTData=NULL, *pCmpABTData=NULL;
    SELABTDATA_EXT *pRefABTExtData=NULL, *pCmpABTExtData=NULL;

    // 빔 병합 조건 : 병합된 LOB, 탐지 과제, 그리고 빔 개수가 1일 때만 병합 수행
    if( bMerge == true /* && GP_MGR_PARAM->IsEmitterMerge() */ ) {
        if( m_pUpdateAETThreat == NULL || m_pUpdateABTThreat == NULL ) {
            LogPrint( "\n 병합된 빔으로 빔 병합을 수행을 못합니다.!!!", m_pLOBData->uiLOBID );
        }
        else {
            pRefABTData = GetABTData( m_pUpdateABTThreat->m_nIndex );
            pRefABTExtData = GetABTExtData( m_pUpdateABTThreat->m_nIndex );

            pThreatAET = GetHeaderThreat( m_pTheThreatRoot );
            while( pThreatAET != NULL ) { //#FA_C_PotentialUnboundedLoop_T1
                pThreatABT = GetHeaderThreat( pThreatAET );
                while( pThreatABT != NULL ) { //#FA_C_PotentialUnboundedLoop_T1
                    if( pThreatAET != m_pUpdateAETThreat && pThreatABT != m_pUpdateABTThreat ) {
                        pCmpABTData = GetABTData( pThreatABT->m_nIndex );
                        pCmpABTExtData = GetABTExtData( pThreatABT->m_nIndex );

                        /*! \todo   제원 비교 추가해야 하는게 아닌지 ?CompDist
                                \author 조철희 (churlhee.jo@lignex1.com)
                                \date 	2016-11-29 00:09:41
                        */
                        if( /* CompTaskType( pCmpABTExtData, true ) == true && */
                                CompELNOT( pRefABTData, pRefABTExtData, pCmpABTData, pCmpABTExtData ) == true &&
                                // CompDist( pRefABTData, pRefABTExtData, pCmpABTData, pCmpABTExtData ) == true &&
                                CompPINNum( pRefABTData, pRefABTExtData, pCmpABTData, pCmpABTExtData ) == true ) {
                            bMatch = true;
                            break;
                        }
                    }
                    pThreatABT = GetNextThreat( pThreatABT );
                }

                if( bMatch == true ) {
                    break;
                }

                pThreatAET = GetNextThreat( pThreatAET );
            }

            // 빙 병합 성공시 처리
            if( bMatch == true ) {
                LogPrint( "\n 방사체/빔[%d/%d] 병합 수행 : 대상 방사체/빔[%d/%d]", pRefABTData->uiAETID, pRefABTData->uiABTID, pCmpABTData->uiAETID, pCmpABTData->uiABTID );

                // 0. DB 큐 버퍼 플러쉬
//                 if( /* false == GP_MGR_INSERTDB->WaitUntilQueueEmpty() */ false ) {
//                     LogPrint( "Insert할 데이터가 아직 있어서 빔(%d/%d) 병합을 수행하지 못합니다 !!!" , pRefABTData->uiAETID, pRefABTData->uiABTID );
//                 }

                // 1. DB 인덱스 번호 증가 : 매우 중요
                NextSeqNum();

                // 2. 삭제할 방사체, 변경할 업데이트 선택
                SelectUpdateAndDeleteABT( m_pUpdateABTThreat, pThreatABT );

                // 3. 노드 업데이트 및 삭제할 방사체 삭제
                //m_pMergeThreatABT->Link( m_pDeleteThreatABT, m_pDeleteThreatAET );
                m_pMergeThreatAET->Link( m_pDeleteThreatABT, m_pDeleteThreatAET );
                bRemoveAET = RemoveThreat( m_pDeleteThreatAET );
                if( bRemoveAET == true && m_pDeleteThreatAET == m_pAETThreat ) {
                    m_pAETThreat = NULL;
                }
                if( bRemoveAET == true ) {
                    m_pDeleteThreatAET = NULL;
                }

                // 4. 방사체 제원 업데이트(추가된 빔 정보)
                UpdateAET( m_pMergeThreatAET, m_pDeleteThreatABT, false, true );
                InsertAET( m_pMergeThreatAET, false, true, m_nSeqNum, 0, true );

                // 5. 삭제할 방사체의 방사체 제원 업데이트
                if( m_pDeleteThreatAET != NULL ) {
                    NextSeqNum();
                    UpdateAET( m_pDeleteThreatAET, NULL, false, false );
                    InsertAET( m_pDeleteThreatAET, false, true, m_nSeqNum, 0, true );
                }

                // 6. LOB/빔 제원 테이블 업데이트, 목록창의 정보 변경
                //GP_MGR_INSERTDB->WaitUntilQueueEmpty();
                UpdateMergedAETDB( bRemoveAET );
                UpdateMergedABTDB( true );
                UpdateMergedLOBDB( true );
            }
            else if( IsSeperatedAET() == true ) {
                LogPrint( "\n 방사체[%d]으로부터 빔[%d] 분리 수행", pRefABTData->uiAETID, pRefABTData->uiABTID );

                // 0. DB 큐 버퍼 플러쉬
//                 if( /* false == GP_MGR_INSERTDB->WaitUntilQueueEmpty() */ false ) {
//                     LogPrint( "Insert할 데이터가 아직 있어서 빔(%d/%d) 분리를 수행하지 못합니다 !!!" , pRefABTData->uiAETID, pRefABTData->uiABTID );
//                 }

                // 1. DB 인덱스 번호 증가 : 매우 중요
                NextSeqNum();

                // 2. 신규 방사체 생성
                CreateThreat( & m_LOBDataExt, true, true, m_nSeqNum, 0, 0, NULL, true );

                // 3. 삭제할 방사체, 변경할 업데이트 선택
                SelectCreateAndDeleteABT();

                // 3. 신규 방사체에 삭제할 빔을 연결한다.
                m_pAETThreat->Link( m_pDeleteThreatABT );
                m_pDeleteThreatAET->UnLink( m_pDeleteThreatABT );
                bRemoveAET = RemoveThreat( m_pDeleteThreatAET );
                if( bRemoveAET == true ) {
                    m_pDeleteThreatAET = NULL;
                }
// 				else {
// 					m_pDeleteThreatAET = m_pDeleteThreatAET;
// 				}

                // 4. 신규 방사체의 제원 업데이트
                UpdateAET( m_pAETThreat, NULL, false, false );
                InsertAET( m_pAETThreat, false, true, m_nSeqNum, 0, true );

                if( m_pDeleteThreatAET != NULL ) {
                    NextSeqNum();
                    UpdateAET( m_pDeleteThreatAET, NULL, false, false );
                    InsertAET( m_pDeleteThreatAET, false, true, m_nSeqNum, 0, true );
                }

                //GP_MGR_INSERTDB->WaitUntilQueueEmpty();
                UpdateMergedAETDB( bRemoveAET );
                UpdateMergedABTDB( false );
                UpdateMergedLOBDB( false );
            }
        }
    }

}

/**
 * @brief     빔 분리 여부를 결정한다.
 * @return    bool
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @warning
*/
bool CELEmitterMergeMngr::IsSeperatedAET()
{
    bool bRet=false;
    CELThreat *pAETTheThreat, *pABTTheThreat;

    SRxAETData *pParentAETData=NULL;
    SRxABTData *pUpdateABTData=NULL;

    pAETTheThreat = m_pTheThreatRoot->Find( m_pUpdateABTThreat->m_Idx.uiAET );
    pParentAETData = GetAETData( pAETTheThreat->m_nIndex );
    pABTTheThreat = m_pTheThreatRoot->Find( m_pUpdateABTThreat->m_Idx.uiAET, m_pUpdateABTThreat->m_Idx.uiABT );
    pUpdateABTData = GetABTData( pABTTheThreat->m_nIndex );

    // 빔 개수가 2개 이고 빔의 EOB가 서로 상이하다면 빔 분리를 수행한다. 구현은 방사체의 위협/장비 와 변경할 빔의 위협/장비 가 다를떄 빔 분리 작업을 처리한다.
    if( pParentAETData->uiCoABT >= _spTwo ) {
        if( ( pParentAETData->iThreatIndex != pUpdateABTData->iThreatIndex ) /* || ( pParentAETData->idInfo.nDeviceIndex != pUpdateABTData->idInfo.nDeviceIndex ) */ ) {
            bRet = true;
        }
    }

    return bRet;

}

/**
 * @brief     병합할 방사체 정보를 업데이트 한다.
 * @param     bool bMerge
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-12-06, 오전 10:29
 * @warning
 */
void CELEmitterMergeMngr::UpdateMergedAETDB( bool bRemoveAET )
{
// 	SELEmitterEdited stELEmitterEdited;
//
// 	CString strCondition = _T(""), strTemp = _T("");
// 	list<_FIELD_INFO> listFieldInfo;
//
// 	_FIELD_INFO stField("","");
//
// 	if( bRemoveAET == true ) {
// 		stField.strFieldName = "AET_ID";
// 		strTemp.Format( "%d", m_uiMergeAETID );
// 		stField.strFieldValue = strTemp;
// 		listFieldInfo.push_back( stField );
//
// 		strCondition.Format( "AET_ID='%d'", m_uiDeleteAETID );
// 		_CALL_DB( UpdateToDB( "E_AA_GMI_EMITTER", & listFieldInfo, nullptr, strCondition.GetBuffer(), NULL, false, true ) )
//
// 		LogPrint( "\n 방사체 테이블에서 이전 S[%d]를 A[%d]를 A[%d]로 변경.", m_uiDeleteAETSeqNum, m_uiDeleteAETID, m_uiMergeAETID );
//
// 		// 병합한 정보 전송
// 		stELEmitterEdited.nAETId = (int) m_uiDeleteAETID;
// 		stELEmitterEdited.nABTId = 0;
// 		stELEmitterEdited.nLOBId = 0;
// 		stELEmitterEdited.uiSeqNum = m_uiDeleteAETSeqNum;
// 		stELEmitterEdited.enEmitterStat = E_ES_UPDATE;
//
// 		AddThreatInfo( & stELEmitterEdited, E_MR_REMOVE_AET, 0, true, m_uiMergeAETSeqNum, false );
// 		LogPrint( "\n 방사체 목록창에서 S[%d] A[%d]를 삭제함.", m_uiDeleteAETSeqNum, m_uiDeleteAETID, m_uiMergeAETID );
// 	}


}

/**
 * @brief     AET/ABT/LOB DB 테이블을 업데이트 한다.
 * @param     bool bMerge
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-12-06, 오전 10:30
 * @warning
 */
void CELEmitterMergeMngr::UpdateMergedABTDB( bool bMerge )
{
// 	SELEmitterEdited stELEmitterEdited;
//
// 	CString strCondition = _T(""), strTemp = _T("");
// 	list<_FIELD_INFO> listFieldInfo;
//
// 	_FIELD_INFO stField("","");
//
// 	if( bMerge == true ) {
// 		stField.strFieldName = "AET_ID";
// 		strTemp.Format( "%d", m_uiMergeAETID );
// 		stField.strFieldValue = strTemp;
// 		listFieldInfo.push_back( stField );
//
// 		strCondition.Format( "AET_ID='%d' AND ABT_ID='%d' AND MISSION_ID='%s'", m_uiDeleteAETID, m_uiDeleteABTID, GetMissionID() );
// 		_CALL_DB( UpdateToDB( "E_AA_GMI_BEAM", & listFieldInfo, nullptr, strCondition.GetBuffer(), NULL, false, true ) )
// 		_CALL_DB( UpdateToDB( "E_AA_GMI_BEAM_ELMT_LIST", & listFieldInfo, nullptr, strCondition.GetBuffer(), NULL, false, true ) )
//
// 		LogPrint( "\n 빔 테이블에서 A[%d/%d]를 A[%d/%d]으로 변경 !", m_uiDeleteAETID, m_uiDeleteABTID, m_uiMergeAETID, m_uiMergeABTID );
//
// 		// 병합한 정보 전송
// 		stELEmitterEdited.nAETId = (int) m_uiDeleteAETID;
// 		stELEmitterEdited.nABTId = (int) m_uiDeleteABTID;
// 		stELEmitterEdited.nLOBId = 0;
// 		stELEmitterEdited.uiSeqNum = m_uiDeleteAETSeqNum;
// 		stELEmitterEdited.enEmitterStat = E_ES_UPDATE;
// 		stELEmitterEdited.iChangedAETID = m_uiMergeAETID;
// 		stELEmitterEdited.iChangedABTID = 0;
// 		AddThreatInfo( & stELEmitterEdited, E_MR_CHANGE, m_pMergeABTData->uiCoLOB, m_pMergeABTExtData->bIsFISINTTask, 0, false );
// 		LogPrint( "\n 빔/LOB 목록창에서 A[%d/%d]를 A[%d/%d]로 변경함.", m_uiDeleteAETID, m_uiDeleteABTID, m_uiMergeAETID, m_uiMergeABTID );
// 	}
// 	else {
// 		stField.strFieldName = "AET_ID";
// 		strTemp.Format( "%d", m_uiMergeAETID );
// 		stField.strFieldValue = strTemp;
// 		listFieldInfo.push_back( stField );
//
// 		strCondition.Format( "AET_ID='%d' AND ABT_ID='%d' AND MISSION_ID='%s'", m_uiDeleteAETID, m_uiDeleteABTID, GetMissionID() );
// 		_CALL_DB( UpdateToDB( "E_AA_GMI_BEAM", & listFieldInfo, nullptr, strCondition.GetBuffer(), NULL, false, true ) )
// 		_CALL_DB( UpdateToDB( "E_AA_GMI_BEAM_ELMT_LIST", & listFieldInfo, nullptr, strCondition.GetBuffer(), NULL, false, true ) )
//
// 		LogPrint( "\n 빔 테이블에서 A[%d/%d]를 A[%d/%d]으로 변경 !", m_uiDeleteAETID, m_uiDeleteABTID, m_uiMergeAETID, m_uiDeleteABTID );
//
// 		// 병합한 정보 전송
// 		stELEmitterEdited.nAETId = (int) m_uiDeleteAETID;
// 		stELEmitterEdited.nABTId = (int) m_uiDeleteABTID;
// 		stELEmitterEdited.nLOBId = 0;
// 		stELEmitterEdited.uiSeqNum = m_uiDeleteAETSeqNum;
// 		stELEmitterEdited.enEmitterStat = E_ES_UPDATE;
// 		stELEmitterEdited.iChangedAETID = m_uiMergeAETID;
// 		stELEmitterEdited.iChangedABTID = 0;								// 빔은 그대로 둠
// 		AddThreatInfo( & stELEmitterEdited, E_MR_CHANGE, m_pDeleteABTData->uiCoLOB, m_pDeleteABTExtData->bIsFISINTTask, 0, false );
// 		LogPrint( "\n 빔/LOB 목록창에서 A[%d/%d]를 A[%d/%d]로 변경함.", m_uiDeleteAETID, m_uiDeleteABTID, m_uiMergeAETID, m_uiDeleteABTID );
// 	}

}

/**
 * @brief     AET/ABT/LOB DB 테이블을 업데이트 한다.
 * @param     bool bMerge
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-12-06, 오전 10:17
 * @warning
 */
void CELEmitterMergeMngr::UpdateMergedLOBDB( bool bMerge )
{
// 	SELEmitterEdited stELEmitterEdited;
//
// 	CString strCondition = _T(""), strTemp = _T("");
// 	list<_FIELD_INFO> listFieldInfo;
//
// 	_FIELD_INFO stField("","");
//
// 	if( bMerge == true ) {
// 		stField.strFieldName = "AET_ID";
// 		strTemp.Format( "%d", m_uiMergeAETID );
// 		stField.strFieldValue = strTemp;
// 		listFieldInfo.push_back( stField );
//
// 		strCondition.Format( "AET_ID='%d' AND ABT_ID='%d' AND MISSION_ID='%s'", m_uiDeleteAETID, m_uiDeleteABTID, GetMissionID() );
// 		_CALL_DB( UpdateToDB( "E_AA_MSG_LOB", & listFieldInfo, nullptr, strCondition.GetBuffer(), NULL, false, true ) )
// 		_CALL_DB( UpdateToDB( "E_AA_MSG_LOB_ELMT_LIST", & listFieldInfo, nullptr, strCondition.GetBuffer(), NULL, false, true ) )
//
// 		LogPrint( "\n LOB 테이블에서 A[%d/%d]를 A[%d/%d]로 변경 !", m_uiDeleteAETID, m_uiDeleteABTID, m_uiMergeAETID, m_uiMergeABTID );
//
// 		// LOB 변경됨을 업데이트
// 		// SetIDLOBData( m_pUpdateABTData->uiAETID, m_pUpdateABTData->uiABTID, m_pLOBData->uiLOBID );
//
// 		// 빔 변경시 동일 코드로 처리하기 때문에 LOB 는 생략한다.
// 	// 	stELEmitterEdited.nAETId = (int) m_uiDeleteAETID;
// 	// 	stELEmitterEdited.nABTId = 0;
// 	// 	stELEmitterEdited.nLOBId = 0;
// 	// 	stELEmitterEdited.uiSeqNum = m_uiUpdateAETSeqNum;
// 	// 	stELEmitterEdited.enEmitterStat = E_ES_UPDATE;
// 	// 	stELEmitterEdited.iChangedAETID = m_pUpdateABTData->uiAETID;
// 	// 	stELEmitterEdited.iChangedABTID = 0;
// 	// 	AddThreatInfo( & stELEmitterEdited, E_MR_CHANGE, m_pUpdateABTData->uiCoLOB, m_pUpdateABTExtData->bIsFISINTTask, m_pUpdateABTExtData->uiSeqNum, false );
// 	}
// 	else {
// 		stField.strFieldName = "AET_ID";
// 		strTemp.Format( "%d", m_uiMergeAETID );
// 		stField.strFieldValue = strTemp;
// 		listFieldInfo.push_back( stField );
//
// 		strCondition.Format( "AET_ID='%d' AND ABT_ID='%d' AND MISSION_ID='%s'", m_uiDeleteAETID, m_uiDeleteABTID, GetMissionID() );
// 		_CALL_DB( UpdateToDB( "E_AA_MSG_LOB", & listFieldInfo, nullptr, strCondition.GetBuffer(), NULL, false, true ) )
// 		_CALL_DB( UpdateToDB( "E_AA_MSG_LOB_ELMT_LIST", & listFieldInfo, nullptr, strCondition.GetBuffer(), NULL, false, true ) )
//
// 		LogPrint( "\n LOB 테이블에서 A[%d/%d]를 A[%d/%d]로 변경 !", m_uiDeleteAETID, m_uiDeleteABTID, m_uiMergeAETID, m_uiMergeABTID );
//
// 	}

}

/**
 * @brief     LOB에 대해서 신호 식별을 수행한다. 미식별시 H000 번호 증가함.
 * @param     *pLOBDataGrp LOB 데이터
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-06-03, 오후 3:42
 * @warning   이 루틴은 LOB가 수신할 때 한번만 발생해야 함.
 */
void CELEmitterMergeMngr::IdentifyLOB( SRxLOBData *pLOBData )
{
    char *pRadarModeName;

    m_pIdentifyAlg->Identify( pLOBData, & m_LOBDataExt, NULL, false );

    pLOBData->iRadarModeIndex = m_LOBDataExt.aetAnal.idInfo.nRadarModeIndex[0];

    pRadarModeName = m_pIdentifyAlg->GetRadarModeName( pLOBData->iRadarModeIndex );

    if( pRadarModeName != NULL ) {
        strcpy_s( pLOBData->szRadarModeName, pRadarModeName );
        //strcpy_s( pLOBData->aucRadarName, pRadarName );
    }
    else {
        pLOBData->aucRadarName[0] = 0;
    }

    //pLOBData->iThreatIndex = 0;
    //LogPrint("\n========================================== LOB Identify 시간 : %d ms(L%d)", (int)((GetTickCount() - dwTime) / 1), pLOBDataGrp->uiLOBID );

}

/**
 * @brief     LOB 처리를 하기 위한 정보 세팅
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-04-12, 오후 5:00
 * @warning
 */
void CELEmitterMergeMngr::LOBPreSetting( SRxLOBHeader* pLOBHeader, SRxLOBData* pLOBData, SLOBOtherInfo *pLOBOtherInfo )
{
    int iDIValidLink;

    // 전역 데이터 포인터 저장
    m_pLOBHeader = pLOBHeader;
    m_pLOBData = pLOBData;

    if( pLOBOtherInfo != NULL ) {
        m_pLOBOtherInfo = pLOBOtherInfo;
    }
    else {
        m_pLOBOtherInfo = NULL;
    }

    // LOB 데이터 설정
    m_pLOBData->uiLOBID = m_uiLOBID++;

    //////////////////////////////////////////////////////////////////////////
    // LOB 확장 데이터 설정
    memset( & m_LOBDataExt, 0, sizeof( SELLOBDATA_EXT ) );

    // 빔 유효성
    iDIValidLink = g_pTheELEnvironVariable->GetMtskDVRatio();

    m_LOBDataExt.aetAnal.iBeamValidity = ( m_pLOBData->iDIRatio >= iDIValidLink ? E_VALID : E_INVALID );

    // 고감도 과제 식별을 하기 위한 설정
    //m_LOBDataExt.aetAnal.iTaskType = m_pLOBData->iTaskType;

    // 빔 생성 코드 초기화
    m_LOBDataExt.aetAnal.eBeamCode = E_UNKNOWN_CODE;

    m_LOBDataExt.aetAnal.tiAcqTime = m_pLOBData->tiContactTime;
    m_LOBDataExt.aetAnal.tiContactTimems = m_pLOBData->tiContactTimems;


#ifdef _ELINT_
    //m_LOBDataExt.aetData.lOpInitID = m_lOpInitID;
    memcpy( m_LOBDataExt.aetData.aucTaskID, m_pLOBData->aucTaskID, sizeof(m_pLOBData->aucTaskID) );
#endif

}

/**
 * @brief     방사체 관리가 Full 일때 오래된 방사체 결과를 리턴한다.
 * @param     CELThreat * pThreatAET
 * @param     CELThreat * pDeleteAET
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-12-06, 오전 9:08
 * @warning
 */
bool CELEmitterMergeMngr::CheckDeleteAET( CELThreat *pThreatAET, CELThreat *pDeleteAET )
{
    bool bRet=false;
    SRxAETData *pAETData, *pDelAETData;

    if( pDeleteAET == NULL || pThreatAET == NULL ) {
        bRet = true;
    }
    else {
        pAETData = GetAETData( pThreatAET->m_nIndex );
        pDelAETData = GetAETData( pDeleteAET->m_nIndex );

        /*! \todo		미식별 정보와 LOB 개수로 삭제 판단을 해야 한다.
                \author 조철희 (churlhee.jo@lignex1.com)
                \date 	2017-12-5 17:47:33
        */
        if( pDelAETData->tiLastSeenTime > pAETData->tiLastSeenTime ) {
            bRet = true;
        }
    }

    return bRet;
}

/**
 * @brief     방사체 중에서 오래된 위협을 강제 삭제한다.
 * @param     void
 * @return    UINT
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-12-06, 오전 9:08
 * @warning
 */
UINT CELEmitterMergeMngr::DeleteThreat()
{
    UINT uiAETID=0;
    CELThreat *pThreatAET, *pDeleteAET=NULL;

    pThreatAET = GetHeaderThreat( m_pTheThreatRoot );
    while( pThreatAET != NULL ) { //#FA_C_PotentialUnboundedLoop_T1
        if( CheckDeleteAET( pThreatAET, pDeleteAET ) == true ) {
            pDeleteAET = pThreatAET;
        }

        pThreatAET = GetNextThreat( pThreatAET );
    }

    if( pDeleteAET != NULL ) {
        SRxAETData *pAETData;

        pAETData = GetAETData( pDeleteAET->m_nIndex );
        DeleteThreat( pDeleteAET, true );

        uiAETID = pAETData->uiAETID;
    }

    return uiAETID;

}

/**
 * @brief     삭제 시간을 기준으로 비활동 위협을 찾아서 마킹한다.
 * @param     *pVecDelThreatInfo 비활동(삭제) 위협 정보
 * @param     bIsMaster 연동기 마스터 플레그
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-21, 오후 5:01
 * @warning
 */
void CELEmitterMergeMngr::DeleteThreat( std::vector<SThreatFamilyInfo> *pVecDelThreatInfo, bool bIsMaster, bool bIsReplay )
{
    int nCoDeleteCheck;
    int nCoDelThreat;
    char chDelThreat[200];

    CELThreat *pPrevThreat;
    CELThreat *pThreatAET;

    E_BEAM_EMITTER_STAT enEmitterStat;

    pVecDelThreatInfo->clear();

    if( ! bIsMaster || bIsReplay == true ) {
        // return;
    }
    else {
        //DWORD dwTime = GetTickCount();

        nCoDeleteCheck = 0;
        pThreatAET = GetHeaderThreat( m_pTheThreatRoot );
        pPrevThreat = pThreatAET;
        while( pThreatAET != NULL ) { //#FA_C_PotentialUnboundedLoop_T1
            CELThreat *pBackupThreat=NULL;

            // 최대 개수를 넘으면 빠져 나오고 다음번에 반영하도록 한다.
            if( pVecDelThreatInfo->size() >= MAX_DELETE_FAMILT_INFO ) {
                break;
            }

            /*! \todo   활동인 것만 체크해도 되는데....
                    \author 조철희 (churlhee.jo@lignex1.com)
                    \date 	2018-04-18 10:09:53
            */
            enEmitterStat = IsDeleteThreat( pThreatAET );
            switch( enEmitterStat ) {
            // 미활동 및 활동 중지 처리
            case E_ES_DELETE :
            case E_ES_REACTIVATED :
                UpdateEmitterBeamStatus( pThreatAET, enEmitterStat, true );
                break;

            case E_ES_DEACTIVATED :
                UpdateEmitterBeamStatus( pThreatAET, enEmitterStat, false );
                break;

            default :
                {	// DT10 예외 처리가 아님.
                }
                break;
            }
            pThreatAET = GetNextThreat( pThreatAET );

            ++ nCoDeleteCheck;
        }

        //LogPrint("\n========================================== [%d] 회를 미활동 검사를 했습니다. : %d ms", nCoDeleteCheck, (int)((GetTickCount() - dwTime) / 1));

        // 미활동 방사체 번호 출력
        nCoDelThreat = (int) pVecDelThreatInfo->size();
        if( nCoDelThreat > 0 ) {
            int i, iCnt=0;

            for( i=0 ; i < nCoDelThreat && i < 5 ; ++i ) {
#ifdef _MSC_VER
                iCnt += sprintf_s( & chDelThreat[iCnt], sizeof(chDelThreat)-iCnt, "[A%d,B%d]", pVecDelThreatInfo->at((UINT) i).iAETID, pVecDelThreatInfo->at((UINT) i).iABTID );
#else
                iCnt += sprintf( & chDelThreat[iCnt], "[A%d,B%d]", pVecDelThreatInfo->at((UINT) i).iAETID, pVecDelThreatInfo->at((UINT) i).iABTID );
#endif
            }
            LogPrint( "방사체[%s] %d 개수를 미활동으로 처리 했습니다.", chDelThreat, nCoDelThreat );
        }
    }
}

/**
 * @brief     방사체/빔 상태를 업데이트 한다.
 * @param     CELThreat * pThreatAET
 * @param     E_BEAM_EMITTER_STAT enEmitterStat
 * @param     bool bAddThreatInfo
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2018-04-11, 오전 10:23
 * @warning
 */
void CELEmitterMergeMngr::UpdateEmitterBeamStatus( CELThreat *pThreatAET, E_BEAM_EMITTER_STAT enEmitterStat, bool bAddThreatInfo )
{
    CELThreat *pThreatABT;

    SRxAETData *pAETData;
    SELAETDATA_EXT *pAETExtData;

    SRxABTData *pABTData;
    SELABTDATA_EXT *pABTExtData;

    SThreatFamilyInfo stThreatFamilyInfo;
    //SELEmitterEdited stELEmitterEdited;

    pAETData = GetAETData( pThreatAET->m_nIndex );
    pAETExtData = GetAETExtData( pThreatAET->m_nIndex );

    //pAETExtData->enBeamEmitterStat = enEmitterStat;
    pAETExtData->enBeamEmitterStat = UpdateEmitterStat( pAETExtData->enBeamEmitterStat, enEmitterStat );

    // 방사체 DB의 상태 정보 업데이트
    UpdateEmitterStatusToEmitterDB( pAETData, pAETExtData );

    pThreatABT = GetHeaderThreat( pThreatAET );
    while( pThreatABT != NULL ) { //#FA_C_PotentialUnboundedLoop_T1Co
        pABTData = GetABTData( pThreatABT->m_nIndex );
        pABTExtData = GetABTExtData( pThreatABT->m_nIndex );

        //pABTExtData->enBeamEmitterStat = enEmitterStat;
        pABTExtData->enBeamEmitterStat = UpdateEmitterStat( pABTExtData->enBeamEmitterStat, enEmitterStat );

        UpdateBeamStatusToEmitterDB( pABTData, pABTExtData );

        if( bAddThreatInfo == true ) {
// 			stELEmitterEdited.nAETId = (int) pABTData->uiAETID;
// 			stELEmitterEdited.nABTId = (int) pABTData->uiABTID;
// 			stELEmitterEdited.nLOBId = 0;
// 			stELEmitterEdited.uiSeqNum = pABTExtData->uiSeqNum;
// 			stELEmitterEdited.enEmitterStat = enEmitterStat;
// 			AddThreatInfo( & stELEmitterEdited, E_MR_UPDATE_STAT, pAETData->uiCoLOB, pAETExtData->bIsFISINTTask, pAETExtData->uiSeqNum, false );
        }

        pThreatABT = GetNextThreat( pThreatABT );
    }
}

/**
 * @brief     AET를 삭제하는데 그 중에서 오래된 빔을 삭제 처리한다. 그런데 빔이 1개 있을 때는 AET까지 삭제 처리한다.
 * @param     *pTheThreat 위협 관리에서 삭제할 위협 데이터 포인터
 * @return    삭제한 빔 번호를 리턴한다. 빔 삭제시 방사체 까지 삭제되면 0 으로 리턴한다.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-24, 오후 8:57
 * @warning
 */
int CELEmitterMergeMngr::DeleteThreat( CELThreat *pTheThreat, bool bDeleteAllABT )
{
    int nABT;

    //UELTHREAT *pUniThreat;
    SRxAETData *pAETData;

    //pUniThreat = m_pUniThreat + pTheThreat->m_nIndex;
    //pAETData = & pUniThreat->uniAET.stAETData;
    pAETData = GetAETData( pTheThreat->m_nIndex );


    // ABT가 여러개 있으면 빔 중에서 오래된 ABT를 삭제한다.
    if( pAETData->uiCoABT >= _spTwo && bDeleteAllABT == false ) {
        nABT = SelectTheDeletedABT( pTheThreat );

        // ABT 삭제 처리한다.
        RemoveThreat( (int) pAETData->uiAETID, nABT );

        // 속해 있는 ABT 개수를 빼줌.
        -- pAETData->uiCoABT;

    }
    // ABT가 단일 있으면 AET 를 포함하여 삭제 처리한다.
    else {
        CELThreat *pABTThreat=pTheThreat->GetLeftChild();

        if( pABTThreat != NULL ) {
            nABT = (int) pABTThreat->m_Idx.uiABT;
        }
        else {
            nABT = 0;
        }

        // AET 삭제 여부를 처리한다.
        RemoveThreat( (int) pAETData->uiAETID );
    }

    return nABT;

}

/**
 * @brief     지정된 방사체/빔 위협을 위협 관리에서 제거한다.
 * @param     CELThreat * pTheAETThreat
 * @param     CELThreat * pTheABTThreat
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2018-02-07, 오후 10:18
 * @warning
 */
bool CELEmitterMergeMngr::DeleteThreat( CELThreat *pTheAETThreat, CELThreat *pTheABTThreat )
{
    bool bRet = true;
    SRxAETData *pAETData;
    SRxABTData *pABTData;

    if( pTheAETThreat != NULL ) {
        pAETData = GetAETData( pTheAETThreat->m_nIndex );

        if( pAETData != NULL && pAETData->uiCoABT == _spOne ) {
            RemoveThreat( (int) pAETData->uiAETID );
            bRet = true;
        }
        else {
            if( pTheABTThreat != NULL ) {
                pABTData = GetABTData( pTheABTThreat->m_nIndex );
                if( pAETData != NULL && pABTData != NULL ) {
                    RemoveThreat( (int) pAETData->uiAETID, (int) pABTData->uiABTID );

                    pAETData->uiCoABT --;
                    // bRet = true;
                }
                else {
                    bRet = false;
                }
            }
        }

    }

    return bRet;
}

/**
 * @brief     방사체만 삭제한다. 방사체 이하 빔들이 있으면 모두 삭제한다.
 * @param     CELThreat * pTheThreat
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-12-08, 오후 5:18
 * @warning
 */
bool CELEmitterMergeMngr::RemoveThreat( CELThreat *pTheThreat )
{
    bool bRet=false;
    SRxAETData *pAETData;

    // 방사체 방사체 번호로 삭제
    if( pTheThreat->IsAET() == true ) {
        // AET 삭제 처리한다. false 일때 에러 처리
        if( pTheThreat->GetLeftChild() == NULL ) {
            pAETData = GetAETData( pTheThreat->m_nIndex );
            if( true == RemoveThreat( (int) pAETData->uiAETID ) ) {
                bRet = true;
                //GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_MSG, E_WARNING_NONE, enumGMEO_DEVICE, enumGMEI_DEVICE, "방사체[%d] 삭제 처리가 성공했습니다. !", pAETData->uiAETID );
            }
            else {
                LogPrint( "방사체[%d] 삭제 처리가 실패했습니다. !", pAETData->uiAETID );
            }
        }

    }
    else {
        LogPrint( "빔 삭제를 잘못 호출했습니다. !" );
        LogPrint( "\n [경고] 빔 삭제 처리는 수행하지 않는다 !!!" );
// 		SRxABTData *pABTData;
// 		CELThreat *pTheAETThreat;
//
// 		pTheAETThreat = m_pTheThreatRoot->Find( pTheThreat->m_Idx.uiAET );
// 		if( pTheAETThreat != NULL ) {
// 			pAETData = GetAETData( pTheAETThreat->m_nIndex );
//
// 			if( pAETData->uiCoABT >= _spTwo ) {
// 				pABTData = GetABTData( pTheThreat->m_nIndex );
// 				RemoveThreat( (int) pABTData->uiAETID, (int) pABTData->uiABTID );
//
// 				-- pAETData->uiCoABT;
// 			}
// 			else {
// 				RemoveThreat( (int) pAETData->uiAETID );
// 				bRet = true;
// 			}
// 		}

    }

    return bRet;

}

/**
 * @brief     빔 노드 중에서 가장 오래된 노드를 선택하여 삭제한다.
 * @param     *pTheThreat 방사체 노드 위협 포인터
 * @return    삭제할 빔 번호를 리턴
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-28, 오후 1:54
 * @warning
 */
int CELEmitterMergeMngr::SelectTheDeletedABT( CELThreat *pTheThreat )
{
    int iRet=-1;
    CELThreat *pThreatABT;
    CELThreat *pThreatDel;

    pThreatABT = GetHeaderThreat( pTheThreat );
    pThreatDel = pThreatABT;
    while( pThreatABT != NULL ) { //#FA_C_PotentialUnboundedLoop_T1
        pThreatABT = GetNextThreat( pThreatABT );

        // ABT들간의 병합 비교 수행
        if( WhichOfOldThreat( pThreatDel, pThreatABT ) ) {
            pThreatDel = pThreatABT;
        }

    }

    if( pThreatDel != NULL ) {
        //UELTHREAT *pUniThreat;
        SRxABTData *pABTData;

        //pUniThreat = m_pUniThreat + pThreatDel->m_nIndex;
        //pABTData = & pUniThreat->uniABT.stABTData;
        pABTData = GetABTData( pThreatDel->m_nIndex );

        iRet = (int) pABTData->uiABTID;
    }

    return iRet;
}

/**
 * @brief     두 위협 간의 오래된 위협을 알려준다.
 * @param     *pTheThreat1 비교 대상 1번 위협
 * @param     *pTheThreat2 비교 대상 2번 위협
 * @return    1번 위협이 크면 false, 2번 위협이면 true 로 리턴함
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-28, 오후 2:09
 * @warning
 */
bool CELEmitterMergeMngr::WhichOfOldThreat( CELThreat *pTheThreat1, CELThreat *pTheThreat2 )
{
    bool bRet=false;
    //UELTHREAT *pUniThreat;
    SRxABTData *pABTData1, *pABTData2;

    if( pTheThreat1 != NULL && pTheThreat2 != NULL ) {
        //pUniThreat = m_pUniThreat + pTheThreat1->m_nIndex;
        //pABTData1 = & pUniThreat->uniABT.stABTData;
        pABTData1 = GetABTData( pTheThreat1->m_nIndex );

        //pUniThreat = m_pUniThreat + pTheThreat2->m_nIndex;
        //pABTData2 = & pUniThreat->uniABT.stABTData;
        pABTData2 = GetABTData( pTheThreat2->m_nIndex );

        bRet = ( pABTData1->tiLastSeenTime < pABTData2->tiLastSeenTime );
    }

    return bRet;

}

#define DEFAULT_DELETE_TIME			(3600*100)						// 100 시간 이상이면 위협 삭제 처리
#define DEFAULT_REF_TIME            (20)
//#define MIN_EMITTER_DELETE_TIME     (180)
/**
 * @brief     삭제할 위협인지를 알려준다.
 * @param     *pTheThreat 위협할 위협 포인터
 * @return    삭제하면 true 아니면 false
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-21, 오후 10:01
 * @warning
 */
E_BEAM_EMITTER_STAT CELEmitterMergeMngr::IsDeleteThreat( CELThreat *pTheThreat )
{
    int refTime;

    time_t now;
    double duration;

    //UELTHREAT *pUniThreat;
    SRxAETData *pAETData;
    SELAETDATA_EXT *pAETExtData;

    E_BEAM_EMITTER_STAT bBeamEmitterStat=E_ES_NOT_AVAILABLE;

    pAETData = GetAETData( pTheThreat->m_nIndex );
    pAETExtData = GetAETExtData( pTheThreat->m_nIndex );

    // 빔 상태가 미활동이면 미처리 로 리턴한다.
    if( pAETExtData->enBeamEmitterStat == E_ES_DELETE ) {
        // bBeamEmitterStat = E_ES_NOT_AVAILABLE;
    }
    else {
        // 생성한 AET, ABT는 제외하고 삭제 판단을 함.
        // 	if( pAETData->uiCoABT == 1 && pAETData->uiCoLOB == 1 )
        // 		return false;

        now = time(NULL);

        if( now > 0 ) {
            duration = difftime( now, pAETData->tiLastSeenTime );

            // 미식별일 때는 시스템 변수로 비교 판단
            if( pAETData->iRadarModeIndex == 0 ) {
                refTime = (int) g_pTheSysConfig->GetEmmgEmitterDeleteTimeSec();
            }
            // 식별일 때는 CED 기반으로 비교 판단
            else {
                refTime = (int) m_pIdentifyAlg->GetUnknownEmitterTime( pAETData->iRadarModeIndex );
            }

            // 삭제 시간 기준 값이 0 이면 미식별 삭제 시간으로 설정한다.
            if( refTime <= 0 ) {
                refTime = (int) g_pTheSysConfig->GetEmmgEmitterDeleteTimeSec();
            }
            refTime = max( refTime, MIN_EMITTER_DELETE_TIME );

            bBeamEmitterStat = pAETExtData->enBeamEmitterStat;
            if( (int) duration > refTime ) {
                if( pAETExtData->enBeamEmitterStat == E_ES_NEW || pAETExtData->enBeamEmitterStat == E_ES_UPDATE || pAETExtData->enBeamEmitterStat == E_ES_REACTIVATED ) {
                    bBeamEmitterStat = E_ES_DEACTIVATED;					// 미활동
                }
                else if( pAETExtData->enBeamEmitterStat == E_ES_DEACTIVATED  ) {
                    bBeamEmitterStat = E_ES_DELETE;							// 삭제 처리
                }
                else {
                    // bBeamEmitterStat = pAETExtData->enBeamEmitterStat;
                }
            }
            // 		if( (int) duration > DEFAULT_DELETE_TIME ) {
            // 			return E_MR_DELETE;											// 미활동
            // 		}
        }
    }

    return bBeamEmitterStat;
}

/**
 * @brief CELEmitterMergeMngr::IsDeleteAET
 * @param uiAETID
 * @return
 */
bool CELEmitterMergeMngr::IsDeleteAET( unsigned int uiAETID )
{
    bool bRet=false;

    CELThreat *pThreatAET;

    E_BEAM_EMITTER_STAT enEmitterStat;

    if( m_pUpdateABTThreat == NULL ) {
        pThreatAET = m_pTheThreatRoot->Find( uiAETID );
    }
    else {
        pThreatAET = m_pUpdateAETThreat;
    }

    enEmitterStat = IsDeleteThreat( pThreatAET );
    // 삭제 또는 비활동 상태에만 업데이트를 한다.
    if( enEmitterStat == E_ES_DELETE || enEmitterStat == E_ES_DEACTIVATED ) {
        UpdateEmitterBeamStatus( pThreatAET, enEmitterStat, true );
    }

    switch( enEmitterStat ) {
        // 미활동 및 활동 중지 처리
        case E_ES_DELETE :
        case E_ES_DEACTIVATED :
            bRet = true;
            break;

        case E_ES_REACTIVATED :
            bRet = false;
            break;

        default :
            {	// DT10 예외 처리가 아님.
            }
            break;
    }

    return bRet;
}

/**
 * @brief     위협 노드에 정보를 저장한다.
 * @param     *pSELLOiValidity LOB 유효성 값
 * @param     eStat 위협 노드 상태 정보
 * @param     bIsFISINTTask FISINT 과제
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-06-16, 오후 10:54
 * @warning
 */
void CELEmitterMergeMngr::AddThreatInfo( SELLOBValidity *pSELLOiValidity, E_EMITTER_OPCODE enOpcode, bool bIsFISINTTask, bool bApplySearchFilter )
{
    SThreatFamilyInfo stThreatFamilyInfo;

    stThreatFamilyInfo.enOpcode = enOpcode;			// ( m_LOBDataExt.aetAnal.uiLOBID == 1 ? E_MR_NEW : E_MR_UPDATE );
    stThreatFamilyInfo.nSeqNum = m_nSeqNum;
    stThreatFamilyInfo.iAETID = (UINT) pSELLOiValidity->nAETId;
    stThreatFamilyInfo.iABTID = (UINT) pSELLOiValidity->nABTId;
    stThreatFamilyInfo.iLOBID = (unsigned int) -1;

    stThreatFamilyInfo.bApplySearchFilter = bApplySearchFilter;

    // FISINT 전용 과제 마크
    stThreatFamilyInfo.bIsFISINTTask = bIsFISINTTask;

    //m_pVecThreatInfo->push_back( stThreatFamilyInfo );

}

/**
 * @brief     위협 결과 데이터에 위협 관리 정보를 추가 저장
 * @param     *pSELEmitterEdited 수동 편집할 정보
 * @param     eStat LOB 활동 정보
 * @param     bIsFISINTTask FISINT 과제
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-07, 오후 4:32
 * @warning
 */
void CELEmitterMergeMngr::AddThreatInfo( SELEmitterEdited *pSELEmitterEdited, E_EMITTER_OPCODE enOpcode, int uiCoLOB, bool bIsFISINTTask, UINT uiSeqNum, bool bApplySearchFilter )
{
    SThreatFamilyInfo stThreatFamilyInfo;

    if( pSELEmitterEdited == NULL ) { // DT10 예외 처리가 아님.
// 		if( m_bReplay == true ) {
// 			stThreatFamilyInfo.enOpcode = enOpcode;
// 			stThreatFamilyInfo.enEmitterStat = m_LOBDataExt.aetAnal.enEmitterStat;			// ( m_LOBDataExt.aetAnal.uiLOBID == 1 ? E_MR_NEW : E_MR_UPDATE );
// 			stThreatFamilyInfo.nSeqNum = nSeqNum;
//
// 			if( GP_ENVI_VAR->GetEmmgNumOfMinLobToBeam() <= (UINT) uiCoLOB || m_bSimulator == true ) {
// 				stThreatFamilyInfo.iAETID = m_LOBDataExt.aetAnal.uiAETID;
// 				stThreatFamilyInfo.iABTID = m_LOBDataExt.aetAnal.uiABTID;
// 				}
// 			else {
// 				stThreatFamilyInfo.iAETID = 0;
// 				stThreatFamilyInfo.iABTID = 0;
// 			}
// 			stThreatFamilyInfo.iLOBID = m_LOBDataExt.aetAnal.uiLOBID;
//
// 			stThreatFamilyInfo.bApplySearchFilter = bApplySearchFilter;
//
// 			// FISINT 전용 과제 마크
// 			stThreatFamilyInfo.bIsFISINTTask = ( m_pLOBData->iIsFISINTTask > 0 );
//
// 			stThreatFamilyInfo.eBeamCode = m_LOBDataExt.aetAnal.eBeamCode;
//
// 			m_pVecThreatInfo->push_back( stThreatFamilyInfo );
//
// 			LogPrint( "\n >>>>> Opcode[%s], SEQ[%d] Stat[%s,%d], A%d, B%d, L%d" , strBeamEmitterOpcode[stThreatFamilyInfo.enOpcode], stThreatFamilyInfo.nSeqNum, strBeamEmitterStat[stThreatFamilyInfo.enEmitterStat], stThreatFamilyInfo.enEmitterStat, stThreatFamilyInfo.iAETID, stThreatFamilyInfo.iABTID, stThreatFamilyInfo.iLOBID );
// 		}
    }
    else {
// 		stThreatFamilyInfo.enOpcode = enOpcode;			// ( m_LOBDataExt.aetAnal.uiLOBID == 1 ? E_MR_NEW : E_MR_UPDATE );
// 		stThreatFamilyInfo.enEmitterStat = pSELEmitterEdited->enEmitterStat;
//
// 		stThreatFamilyInfo.nSeqNum = pSELEmitterEdited->uiSeqNum;
// 		//if( GP_ENVI_VAR->GetEmmgNumOfMinLobToBeam() <= (UINT) uiCoLOB || m_bSimulator == true ) {
// 		if( enOpcode == E_MR_REMOVE_AETABT || enOpcode == E_MR_REMOVE_AET || (int) GP_ENVI_VAR->GetEmmgNumOfMinLobToBeam() <= uiCoLOB || m_bSimulator == true ) {
// 			stThreatFamilyInfo.iAETID = (UINT) pSELEmitterEdited->nAETId;
// 			stThreatFamilyInfo.iABTID = (UINT) pSELEmitterEdited->nABTId;
// 			stThreatFamilyInfo.iLOBID = (UINT) pSELEmitterEdited->nLOBId;
//
// 			stThreatFamilyInfo.bApplySearchFilter = bApplySearchFilter;
//
// 			// FISINT 전용 과제 마크
// 			stThreatFamilyInfo.bIsFISINTTask = bIsFISINTTask;
//
// 			stThreatFamilyInfo.eBeamCode = E_UNKNOWN_CODE;
//
// 			stThreatFamilyInfo.ti_FirstTime = pSELEmitterEdited->ti_FirstTime;
// 			stThreatFamilyInfo.ti_FinalTime = pSELEmitterEdited->ti_FinalTime;
//
// 			stThreatFamilyInfo.iChangedAETID = pSELEmitterEdited->iChangedAETID;
// 			stThreatFamilyInfo.iChangedABTID = pSELEmitterEdited->iChangedABTID;
//
// 			m_pVecThreatInfo->push_back( stThreatFamilyInfo );
//
// 			LogPrint( "\n >>>>> Opcode[%s], SEQ[%d] Stat[%s,%d], A%d, B%d, L%d, Chg A%d, B%d", strBeamEmitterOpcode[stThreatFamilyInfo.enOpcode], stThreatFamilyInfo.nSeqNum, strBeamEmitterStat[stThreatFamilyInfo.enEmitterStat], stThreatFamilyInfo.enEmitterStat, stThreatFamilyInfo.iAETID, stThreatFamilyInfo.iABTID, stThreatFamilyInfo.iLOBID, stThreatFamilyInfo.iChangedAETID, stThreatFamilyInfo.iChangedABTID );
// 		}
// 		else {
// 			stThreatFamilyInfo.iAETID = 0;
// 			stThreatFamilyInfo.iABTID = 0;
// 		}

    }

}

/**
 * @brief     LOB를 기반으로 AET, ABT 데이터 저장소에 데이터를 생성한다.
 * @param     *pThreatDataExt 위협 추가 정보
 * @return    생성 성공하면 true, 실패하면 false 로 리턴함.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-06, 오후 2:19
 * @warning
 */
bool CELEmitterMergeMngr::CreateThreat( SELLOBDATA_EXT *pThreatDataExt, bool bCluster, bool bDBInsert, UINT nSeqNum, UINT uiAETID, UINT uiABTID, SELMERGE_CANDIDATE *pMergeCandidate, bool bOnlyMakeAET )
{ //#FA_Q_4020_T1 (Msg(6:4020) Multiple exit points found.)
    UINT uiDeleteAETID;
    bool bRet = true;
    CELThreat *pAETThreat, *pABTThreat;
    
    if( uiAETID == INVALID_INDEX ) {
        pAETThreat = new CELThreat( m_uiAETID, INVALID_INDEX, INVALID_INDEX );
    }
    else {
        pAETThreat = m_pTheThreatRoot->Find( uiAETID );
        if( pAETThreat == NULL ) {
            TRACE( "생성할 위협[E%d]을 찾지 못했습니다.", uiAETID );
            LogPrint( "생성할 위협[E%d]을 찾지 못했습니다.", uiAETID );
            bRet = false;
        }

    }

    if( bRet == true && bOnlyMakeAET == false ) {
        if( uiABTID == INVALID_INDEX ) {
            pABTThreat = new CELThreat( m_uiAETID, m_uiABTID, INVALID_INDEX );
        }
        else {
            pABTThreat = m_pTheThreatRoot->Find( uiAETID, uiABTID );
            if( pABTThreat == NULL ) {
                delete pAETThreat;

                TRACE( "생성할 위협[E%d,B%d]을 찾지 못했습니다.", uiAETID, uiABTID );
                LogPrint( "생성할 위협[E%d,B%d]을 찾지 못했습니다.", uiAETID, uiABTID );
                bRet = false;
            }
        }
    }
    else {
        uiABTID = (UINT) -1;
        pABTThreat = NULL;

    }

    if( bRet == true ) {
        if( pAETThreat->m_nIndex == INVALID_INDEX || ( pABTThreat != NULL && pABTThreat->m_nIndex == INVALID_INDEX ) ) {
            /*! \todo   위협 관리가 FULL 이 되어서 위협을 생성할 수 없습니다. 가장 오래된 위협을 삭제 하거나 버퍼수를 늘려야 한다.
                \author 조철희 (churlhee.jo@lignex1.com)
                \date 	2017-07-07 11:30:45
            */
            uiDeleteAETID = DeleteThreat();

            delete pAETThreat;
            pAETThreat = NULL;
            
            if( pABTThreat != NULL ) {
                delete pABTThreat;
            }

            pAETThreat = new CELThreat( m_uiAETID, INVALID_INDEX, INVALID_INDEX );
            if( bOnlyMakeAET == false ) {
                pABTThreat = new CELThreat( m_uiAETID, m_uiABTID, INVALID_INDEX );
            }

            LogPrint( "위협 노드가 FULL 입니다. 위협[%d]을 삭제 합니다.", uiDeleteAETID );
        }

        // 방사체/빔 위협 업데이트
        m_pAETThreat = pAETThreat;
        m_pABTThreat = pABTThreat;

        if( uiAETID == INVALID_INDEX || uiABTID == INVALID_INDEX ) {
            m_pTheThreatRoot->AppendChildNode( pAETThreat );
            pAETThreat->AppendChildNode( pABTThreat );
        }
        
        if( bOnlyMakeAET == false ) {
            // ABT 노드 생성
            CreateABTThreat( pABTThreat, m_pLOBHeader, m_pLOBData, pThreatDataExt, bCluster );
            
            // DB 테이블 추가
            InsertABT( pABTThreat, false, bDBInsert, nSeqNum, uiAETID, uiABTID, pMergeCandidate );
            
            // AET 노드 생성
            CreateAETThreat( pAETThreat, pABTThreat, m_pLOBData, pThreatDataExt );
            InsertAET( pAETThreat, false, bDBInsert, nSeqNum, uiAETID );

            //SetIDLOBData( m_uiAETID, m_uiABTID, m_pLOBData->uiLOBID );
            SetIDLOBData( uiAETID, uiABTID, m_pLOBData->uiLOBID );

            // LOB 클러스터링을 위한 LOB 데이터 추가
            InsertLOBPool( pABTThreat->m_nIndex, m_pLOBData, m_pLOBData->uiLOBID, true, bCluster && ( m_LOBDataExt.aetAnal.iBeamValidity == 1 ) );

            //GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_MSG, E_WARNING_NONE, enumGMEO_DEVICE, enumGMEI_DEVICE, "신규 방사체(%d)을 생성했습니다." , m_uiAETID );

            NextAETID();
            NextABTID();
        }
        else {
            CreateAETThreat( pAETThreat, pABTThreat, m_pLOBData, pThreatDataExt );
            //SetIDLOBData( m_uiAETID, m_uiABTID, m_pLOBData->uiLOBID );
            //SetIDLOBData( uiAETID, uiABTID, m_pLOBData->uiLOBID );

            // LOB 클러스터링을 위한 LOB 데이터 추가
            //InsertLOBPool( pABTThreat->m_nIndex, m_pLOBData, m_pLOBData->uiLOBID, true, bCluster && ( m_LOBDataExt.aetAnal.iBeamValidity == 1 ) );

            LogPrint( "빔 분리로 신규 방사체(%d)를 생성했습니다." , m_uiAETID );

            NextAETID();
        }

        //NextLOBID();
    }

    return bRet;
}

/**
 * @brief     빔 번호를 증가한다.
 * @param     void
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-01-10, 오후 4:45
 * @warning
 */
void CELEmitterMergeMngr::NextABTID()
{
    ++ m_uiABTID;

    // 한바뀌를 돌아서 0 값이 되면 ++1 을 더한다.
    if( m_uiABTID == INVALID_INDEX ) { //DTEC_Else
        ++ m_uiABTID;
    }

}

/**
 * @brief     방사체 번호를 증가한다.
 * @param     void
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-01-10, 오후 4:45
 * @warning
 */
void CELEmitterMergeMngr::NextAETID()
{
    ++ m_uiAETID;

    // 한바뀌를 돌아서 0 값이 되면 ++1 을 더한다.
    if( m_uiAETID == INVALID_INDEX ) { //DTEC_Else
        ++ m_uiAETID;
    }
}

/**
 * @brief     빔 중에서 어떤 빔을 선택할 것인지를 택한다.
 * @param     CELThreat * pMovedThreatABT 빔 위협 데이터
 * @param     CELThreat * pDestThreatABT 빔 위협 데이터
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2018-02-07, 오후 9:11
 * @warning
 */
void CELEmitterMergeMngr::SelectUpdateAndDeleteABT( CELThreat *pMovedThreatABT, CELThreat *pDestThreatABT )
{
    bool bRet;

    CELThreat *pMovedThreatAET, *pDestThreatAET;

    SRxAETData *pMovedAETData, *pDestAETData;

    pMovedThreatAET = m_pTheThreatRoot->Find( pMovedThreatABT->m_Idx.uiAET );
    pMovedAETData = GetAETData( pMovedThreatAET->m_nIndex );

    pDestThreatAET = m_pTheThreatRoot->Find( pDestThreatABT->m_Idx.uiAET );
    pDestAETData = GetAETData( pDestThreatAET->m_nIndex );

    // 2개 빔중에서 삭제될 방사체(위협)을 선택하고 병합할 빔에 데이터를 병합한다.
    bRet = IsSelectAET( pMovedAETData, pDestAETData );

    // 변경한 빔을 강제 삭제 처리하도록 한다.
    if( bRet == true && false ) {
        m_pMergeThreatAET = pMovedThreatAET;
        m_pMergeThreatABT = pMovedThreatABT;

        m_pDeleteThreatAET = pDestThreatAET;
        m_pDeleteThreatABT = pDestThreatABT;
    }
    else {
        m_pMergeThreatAET = pDestThreatAET;
        m_pMergeThreatABT = pDestThreatABT;

        m_pDeleteThreatAET = pMovedThreatAET;
        m_pDeleteThreatABT = pMovedThreatABT;
    }

    m_pMergeABTData = GetABTData( m_pMergeThreatABT->m_nIndex );
    m_pMergeABTExtData = GetABTExtData( m_pMergeThreatABT->m_nIndex );

    m_pMergeAETData = GetAETData( m_pMergeThreatAET->m_nIndex );
    m_pMergeAETExtData = GetAETExtData( m_pMergeThreatAET->m_nIndex );

    // 변경할 방사체 및 빔 번호
    m_uiMergeAETID = m_pMergeABTData->uiAETID;
    m_uiMergeABTID = m_pMergeABTData->uiABTID;
    m_uiMergeAETSeqNum = m_pMergeAETExtData->uiSeqNum;

    m_pDeleteABTData = GetABTData( m_pDeleteThreatABT->m_nIndex );
    m_pDeleteABTExtData = GetABTExtData( m_pDeleteThreatABT->m_nIndex );

    m_pDeleteAETData = GetAETData( m_pDeleteThreatAET->m_nIndex );
    m_pDeleteAETExtData = GetAETExtData( m_pDeleteThreatAET->m_nIndex );

    // 삭제할 방사체 및 빔 번호
    m_uiDeleteAETID = m_pDeleteABTData->uiAETID;
    m_uiDeleteABTID = m_pDeleteABTData->uiABTID;
    m_uiDeleteAETSeqNum = m_pDeleteAETExtData->uiSeqNum;

    LogPrint( "\n 삭제할 방사체/빔 번호 : %d/%d", m_uiDeleteAETID, m_uiDeleteABTID );
    LogPrint( "\n 추가할 방사체/빔 번호 : %d/%d", m_uiMergeAETID, m_uiMergeABTID );

    return;
}

/**
 * @brief     빔 중에서 어떤 빔을 선택할 것인지를 택한다.
 * @param     CELThreat * pDestThreatABT 빔 위협 데이터
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2018-02-07, 오후 9:11
 * @warning
 */
void CELEmitterMergeMngr::SelectCreateAndDeleteABT()
{
    //bool bRet;

    //CELThreat *pMovedThreatAET, *pDestThreatAET;

    //SELAETDATA *pMovedAETData, *pDestAETData;

    m_pMergeThreatAET = m_pAETThreat;
    m_pMergeAETData = GetAETData( m_pMergeThreatAET->m_nIndex );
    m_pMergeAETExtData = GetAETExtData( m_pMergeThreatAET->m_nIndex );
    m_pMergeThreatABT = NULL;
    m_pMergeABTData = NULL;
    m_pMergeABTExtData = NULL;

    // 변경할 방사체 및 빔 번호
    m_uiMergeAETID = m_pMergeAETData->uiAETID;
    m_uiMergeABTID = 0;
    m_uiMergeAETSeqNum = m_pMergeAETExtData->uiSeqNum;

    m_pDeleteThreatAET = m_pTheThreatRoot->Find( m_pUpdateABTThreat->m_Idx.uiAET );
    m_pDeleteAETData = GetAETData( m_pDeleteThreatAET->m_nIndex );
    m_pDeleteAETExtData = GetAETExtData( m_pDeleteThreatAET->m_nIndex );
    m_pDeleteThreatABT = m_pUpdateABTThreat;
    m_pDeleteABTData = GetABTData( m_pDeleteThreatABT->m_nIndex );
    m_pDeleteABTExtData = GetABTExtData( m_pDeleteThreatABT->m_nIndex );

    // 삭제할 방사체 및 빔 번호
    m_uiDeleteAETID = m_pDeleteABTData->uiAETID;
    m_uiDeleteABTID = m_pDeleteABTData->uiABTID;
    m_uiDeleteAETSeqNum = m_pDeleteAETExtData->uiSeqNum;

    LogPrint( "\n 삭제할 방사체/빔 번호 : %d/%d", m_uiDeleteAETID, m_uiDeleteABTID );
    LogPrint( "\n 생성할 방사체/빔 번호 : %d/%d", m_uiMergeAETID, m_uiMergeABTID );

    return;
}

/**
 * @brief     수신한 LOB와 연관된 THREAT 정보를 업데이트한다.
 * @param     *pThreatDataExt 위협 정보를 변경할 데이터 포인터
 * @return    변경한 방사체의 데이터 포인터
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-11, 오전 9:52
 * @warning
 */
CELThreat *CELEmitterMergeMngr::UpdateThreat( SELLOBDATA_EXT *pThreatDataExt, bool bCluster, vector<SELMERGE_CANDIDATE> *pIVecCanOfMergeLOB, bool bDBInsert, UINT nSeqNum, CELThreat *pSourceThreatAET, CELThreat *pSourceThreatABT, bool bRunCluster, bool bRunPE, bool bGenNewEmitter )
{
    int i;
    int nCoMerge;

    bool bEnable;

    SELMERGE_CANDIDATE *pMergeCandidate;
    vector<SELMERGE_CANDIDATE> *pVecCanOfMergeLOB;

    CELThreat *pTheABTThreat=NULL, *pTheAETThreat=NULL;

    //DWORD dwTime = GetTickCount();

    if( pIVecCanOfMergeLOB != NULL ) {
        pVecCanOfMergeLOB = pIVecCanOfMergeLOB;
    }
    else {
        pVecCanOfMergeLOB = & m_vecCanOfMergeLOB;
    }

    // 유사도가 낮은 순부터 Update를 한다. 그리고 가장 유사한 위협을 리턴한다.
    if( bGenNewEmitter == false ) {
        nCoMerge = (int) pVecCanOfMergeLOB->size();
    }
    else {
        nCoMerge = _spOne;
    }

    for( i=0 ; i < nCoMerge && i < _spOne /* nCoMerge */ ; ++i ) {
        if( bGenNewEmitter == false ) {
            pMergeCandidate = & pVecCanOfMergeLOB->at((UINT)i);
        }
        else {
            pMergeCandidate = NULL;
        }

        // ABT를 찾아서 업데이트를 함.
        if( pSourceThreatABT == NULL && pMergeCandidate != NULL ) {
            pTheABTThreat = m_pTheThreatRoot->Find( pMergeCandidate->idx.uiAET, pMergeCandidate->idx.uiABT );
        }
        else {
            pTheABTThreat = pSourceThreatABT;
        }

        if( pTheABTThreat != NULL ) {
            // LOB 클러스터링을 위한 LOB 데이터 추가
            InsertLOBPool( pTheABTThreat->m_nIndex, m_pLOBData, m_pLOBData->uiLOBID, false, ( bCluster && ( m_LOBDataExt.aetAnal.iBeamValidity == E_VALID ) ) && ( !bGenNewEmitter ) && ( !m_bScanProcess ) );
            
            //////////////////////////////////////////////////////////////////////////
            // ABT 업데이트 처리
            bEnable = UpdateABT( pTheABTThreat, pThreatDataExt, bRunCluster, bRunPE, bGenNewEmitter );
            
            // ABT 테이블에 추가
            InsertABT( pTheABTThreat, false, bEnable, nSeqNum, 0, 0, pMergeCandidate );
            
            //////////////////////////////////////////////////////////////////////////
            // AET를 찾아서 업데이트를 함.
            if( pSourceThreatAET == NULL && pMergeCandidate != NULL ) {
                pTheAETThreat = m_pTheThreatRoot->Find( pMergeCandidate->idx.uiAET );
            }
            else {
                pTheAETThreat = pSourceThreatAET;
            }
            
            if( pTheAETThreat != NULL ) {
                // AET 업데이트 처리
                UpdateAET( pTheAETThreat, pTheABTThreat, bGenNewEmitter );

                // AET 테이블에 추가
                InsertAET( pTheAETThreat, false, bEnable, nSeqNum );
            }

            // ABT 와 LOB 의 식별 후보를 재조정
            ReIdentifyLOB( pTheABTThreat );

            SetIDLOBData( pTheABTThreat->m_Idx.uiAET, pTheABTThreat->m_Idx.uiABT, m_pLOBData->uiLOBID );

        }

        // 업데이트한 위협 멤버 변수에 저장한다.
        m_pAETThreat = pTheAETThreat;
        m_pABTThreat = pTheABTThreat;

        // 변경된 빔 위협에 LOB에 저장
// 		if( nCoMerge >= _spOne ) {
// 			pMergeCandidate = & pVecCanOfMergeLOB->at(0);
//
// 			// ABT를 찾아서 업데이트를 함.
// 			pTheABTThreat = m_pTheThreatRoot->Find( & pMergeCandidate->idx );
// 		}
    }

    //LogPrint("\n========================================== UpdateThreat 시간 : %d ms", (int)((GetTickCount() - dwTime) / 1));

    return pTheAETThreat;

}

// 재식별을 수행한다.
void CELEmitterMergeMngr::ReIdentifyLOB( CELThreat *pTheABTThreat )
{
    bool bMatch;
    int i, j;

    //SRxABTData *pABTData;
    SELABTDATA_EXT *pABTExtData;

    STR_CEDEOBID_INFO *pLOBAetAnal, *pABTIDInfo;

    int nLOBRadarIndex;

    // 레이더 모드 인덱스 결과
    int nResultOfLOB[MAX_IDCANDIDATE];
    int nResultOfLOBCo=0;

    memset( nResultOfLOB, 0, sizeof(nResultOfLOB) );

    pLOBAetAnal = & m_LOBDataExt.aetAnal.idInfo;

    //pABTData = GetABTData( pTheABTThreat->m_nIndex );
    pABTExtData = GetABTExtData( pTheABTThreat->m_nIndex );

    pABTIDInfo = & pABTExtData->idInfo;

    //pRadarModeIndex = pLOBAetAnal->nRadarModeIndex;

    // 1. 레이더 모드 인덱스 업데이트
    for( i=0 ; i < pLOBAetAnal->nCoRadarModeIndex ; ++i ) {
        nLOBRadarIndex = pLOBAetAnal->nRadarModeIndex[i];
        bMatch = false;
        for( j=0 ; j < pABTIDInfo->nCoRadarModeIndex ; ++j ) {
            if( pABTExtData->idInfo.nRadarModeIndex[j] == nLOBRadarIndex ) {
                bMatch = true;
                break;
            }
        }

        //  빔에 레이더 인덱스가 없기 때문에 삭제 처리함.
        if( bMatch == true ) {
            nResultOfLOB[nResultOfLOBCo] = nLOBRadarIndex;
            ++ nResultOfLOBCo;
        }
    }
    pLOBAetAnal->nCoRadarModeIndex = nResultOfLOBCo;
    memcpy( pLOBAetAnal->nRadarModeIndex, nResultOfLOB, sizeof(int)*(UINT)nResultOfLOBCo );

    // 2. 레이더 인덱스 업데이트
// 	nResultOfLOBCo = 0;
// 	for( i=0 ; i < pLOBAetAnal->nCoRadarIndex ; ++i ) {
// 		nLOBRadarIndex = pLOBAetAnal->nRadarIndex[i];
// 		bMatch = false;
// 		for( j=0 ; j < pABTIDInfo->nCoRadarIndex ; ++j ) {
// 			if( pABTIDInfo->nRadarIndex[j] == nLOBRadarIndex ) {
// 				bMatch = true;
// 				break;
// 			}
// 		}
//
// 		//  빔에 레이더 인덱스가 없기 때문에 삭제 처리함.
// 		if( bMatch == true ) {
// 			nResultOfLOB[nResultOfLOBCo] = nLOBRadarIndex;
// 			++ nResultOfLOBCo;
// 		}
// 	}
// 	pLOBAetAnal->nCoRadarIndex = nResultOfLOBCo;
// 	memcpy( pLOBAetAnal->nRadarIndex, nResultOfLOB, sizeof(int)*(UINT)nResultOfLOBCo );

}

/**
 * @brief     수신한 빔 정보와 연관된 AET 정보를 업데이트한다.
 * @param     *pTheAETThreat 방사체 위협 정보 데이터 포인터
 * @param     *pTheABTThreat 빔 위협 정보 데이터 포인터
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-11, 오전 9:53
 * @warning
 */
void CELEmitterMergeMngr::UpdateAET( CELThreat *pTheAETThreat, CELThreat *pTheABTThreat, bool bGenNewEmitter, bool bMergeABT )
{
    if( pTheAETThreat != NULL ) {
        if( pTheABTThreat != NULL ) {
            SRxAETData *pAETData;
            SELAETDATA_EXT *pAETExtData;

            SRxABTData *pABTData;
            SELABTDATA_EXT *pABTExtData;

            pAETData = GetAETData( pTheAETThreat->m_nIndex );
            pAETExtData = GetAETExtData( pTheAETThreat->m_nIndex );

            pABTData = GetABTData( pTheABTThreat->m_nIndex );
            pABTExtData = GetABTExtData( pTheABTThreat->m_nIndex );

            // 변경된 위협의 방사체 번호로 매핑을 한다.
            pABTData->uiAETID = pTheABTThreat->m_Idx.uiAET;

            if( m_bScanProcess == false ) {
                //////////////////////////////////////////////////////////////////////////
                // 기본 정보 업데이트
                // 시간 정보
                UpdateSeenTime( pAETData, pAETExtData, pABTData, pABTExtData);

                // 방위 정보
                UpdateDOAInfo( pAETData, pAETExtData, pABTData, pABTExtData);

                // 주파수 정보
                UpdateFreqInfo( pAETData, pAETExtData, pABTData, pABTExtData );

                // PRI 정보
                UpdatePRIInfo( pAETData, pAETExtData, pABTData, pABTExtData );

                // 펄스폭 정보
                UpdatePWInfo( pAETData, pAETExtData, pABTData, pABTExtData );

                // 신호세기 정보
                UpdatePAInfo( pAETData, pAETExtData, pABTData, pABTExtData );

                // DB를 통한 분산, 표준편차, 평균 구하기
                // CalStatisticsFromAET( pAETData );

                // 위치 산출 정보
                UpdatePEInfo( pAETData, pAETExtData, pTheAETThreat );

                // 방사체 유효성 업데이트
                UpdateBeamValidity( pAETData, pAETExtData, pTheAETThreat );

                // CED/EOB 식별
                UpdateIDInfo( pAETData, pAETExtData, pTheAETThreat );

                //////////////////////////////////////////////////////////////////////////
                // 추가 정보 업데이트
                if( bMergeABT == false ) {
                    ++ pAETData->uiCoLOB;

                    pAETExtData->nCoTotalPdw += m_pLOBData->iNumOfPDW;
                    //pAETExtData->nCoTotalIQ += m_pLOBData->iNumOfIQ;
                }
                else {
                    pAETData->uiCoLOB += pABTData->uiCoLOB;
                    ++ pAETData->uiCoABT;

                    pAETExtData->nCoTotalPdw += pABTData->uiTotalOfPDW;
                    //pAETExtData->nCoTotalIQ += pABTExtData->nCoTotalIQ;

                    // 추가할 빔의 방사체 번호는 병합한 방사체 번호로 변경한다.
                    pABTData->uiAETID = pAETData->uiAETID;

                }
            }
            else {
                //////////////////////////////////////////////////////////////////////////
                // 기본 정보 업데이트
                // 시간 정보
                UpdateSeenTime( pAETData, pAETExtData, pABTData, pABTExtData);

                // CED/EOB 식별
                UpdateIDInfo( pAETData, pAETExtData, pTheAETThreat );

            }

            UpdateAETStat( pAETExtData, bGenNewEmitter );

            //pAETExtData->iTaskType = m_pLOBData->iTaskType / 2;

            pAETExtData->uiSeqNum = m_nSeqNum;

            //strcpy_s( pAETExtData->szELNOT, pABTExtData->szELNOT );
        }
        else {
            CELThreat *pABTThreat;

            SRxAETData *pUpdateAETData;
            SELAETDATA_EXT *pUpdateAETExtData;

            SRxABTData *pABTData;
            SELABTDATA_EXT *pABTExtData;

            pUpdateAETData = GetAETData( pTheAETThreat->m_nIndex );
            pUpdateAETExtData = GetAETExtData( pTheAETThreat->m_nIndex );

            pUpdateAETData->uiCoLOB = 0;
            pUpdateAETData->uiCoABT = 0;
            pUpdateAETExtData->nCoTotalPdw = 0;
            //pUpdateAETExtData->nCoTotalIQ = 0;

            pABTThreat = pTheAETThreat->GetLeftChild();
            while( pABTThreat != NULL ) {
                pABTData = GetABTData( pABTThreat->m_nIndex );
                pABTExtData = GetABTExtData( pABTThreat->m_nIndex );

                // 변경된 위협의 방사체 번호로 매핑을 한다.
                pABTData->uiAETID = pABTThreat->m_Idx.uiAET;

                //////////////////////////////////////////////////////////////////////////
                // 기본 정보 업데이트
                // 시간 정보
                UpdateSeenTime( pUpdateAETData, pUpdateAETExtData, pABTData, pABTExtData);

                // 주파수 정보
                UpdateFreqInfo( pUpdateAETData, pUpdateAETExtData, pABTData, pABTExtData );

                // PRI 정보
                UpdatePRIInfo( pUpdateAETData, pUpdateAETExtData, pABTData, pABTExtData );

                // 펄스폭 정보
                UpdatePWInfo( pUpdateAETData, pUpdateAETExtData, pABTData, pABTExtData );

                // 신호세기 정보
                UpdatePAInfo( pUpdateAETData, pUpdateAETExtData, pABTData, pABTExtData );

                //////////////////////////////////////////////////////////////////////////
                // 추가 카운트 업데이트
                pUpdateAETData->uiCoLOB += pABTData->uiCoLOB;
                ++ pUpdateAETData->uiCoABT;
                pUpdateAETExtData->nCoTotalPdw += pABTData->uiTotalOfPDW;
                //pUpdateAETExtData->nCoTotalIQ += pABTExtData->nCoTotalIQ;

                //pUpdateAETExtData->iTaskType = pABTExtData->iTaskType / 2;

                pABTThreat = pABTThreat->GetRightChild();
            }

            // 위치 산출 정보
            UpdatePEInfo( pUpdateAETData, pUpdateAETExtData, pTheAETThreat );

            // 방사체 유효성 업데이트
            UpdateBeamValidity( pUpdateAETData, pUpdateAETExtData, pTheAETThreat );

            // CED/EOB 식별
            UpdateIDInfo( pUpdateAETData, pUpdateAETExtData, pTheAETThreat );

            UpdateAETStat( pUpdateAETExtData, bGenNewEmitter );

            pUpdateAETExtData->uiSeqNum = m_nSeqNum;

        }
    }

}

/**
 * @brief     빔 정보를 변경 처리를 수행한다.
 * @param     *pTheABTThreat 방사에 데이터 포인터
 * @param     *pSELLOiValidity LOB 유효성 업데이트
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-06-16, 오후 9:20
 * @warning
 */
void CELEmitterMergeMngr::UpdateABT( CELThreat *pTheABTThreat, SELLOBValidity *pSELLOBValidity )
{
    SRxABTData *pABTData;
    SELABTDATA_EXT *pABTExtData;

    pABTData = GetABTData( pTheABTThreat->m_nIndex );
    pABTExtData = GetABTExtData( pTheABTThreat->m_nIndex );

    // 위치 산출 정보
    UpdatePEInfo( pABTData, pABTExtData, pTheABTThreat->m_nIndex );

    // 빔 유효성 업데이트
    UpdateBeamValidity( pABTData, pABTExtData, pTheABTThreat->m_nIndex );

    // CED/EOB 식별 정보
    IdentifyABT( pABTData, pABTExtData );
    UpdateIDInfo( pABTData, pABTExtData );

    //pABTExtData->xManualEdited.x.peInfo = false;

}

/**
 * @brief     AET 데이터를 ABT 데이터로 변환한다.
 * @param     *pABTData 빔 데이터 포인터
 * @param     *pAETData 방사체 데이터 포인터
 * @return    리턴값 없음

 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-06-07, 오후 4:05
 * @warning
 */
void CELEmitterMergeMngr::ConvertAET2ABT( SRxABTData *pABTData, SELAETDATA *pAETData )
{
// 	pABTData->freqInfo = pAETData->freqInfo;
// 	pABTData->priInfo = pAETData->priInfo;
// 	pABTData->pwInfo = pAETData->pwInfo;
// 	pABTData->paInfo = pAETData->paInfo;
//
// 	pABTData->peInfo = pAETData->peInfo;
// 	pABTData->idInfo = pAETData->idInfo;

}

/**
 * @brief     방사체 정보를 업데이트를 처리한다.
 * @param     *pTheAETThreat 위협 정보를 업데이트 할 데이터 포인터
 * @param     *pSELLOiValidity LOB 빔 유효성 데이터 포인터
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-06-16, 오후 10:41
 * @warning
 */
void CELEmitterMergeMngr::UpdateAET( CELThreat *pTheAETThreat, SELLOBValidity *pSELLOBValidity )
{
    SRxAETData *pAETData;
    SELAETDATA_EXT *pAETExtData;

    pAETData = GetAETData( pTheAETThreat->m_nIndex );
    pAETExtData = GetAETExtData( pTheAETThreat->m_nIndex );

    // 강제 위치 산출을 해지 하기 위한 정보
    //pAETExtData->xMannualEdited.x.peInfo = false;

    // 위치 산출 정보
    UpdatePEInfo( pAETData, pAETExtData, pTheAETThreat );

    // CED/EOB 식별
    UpdateIDInfo( pAETData, pAETExtData, pTheAETThreat );

    // 빔 유효성 업데이트
    UpdateBeamValidity( pAETData, pAETExtData, pTheAETThreat );

    UpdateAETStat( pAETExtData );

}

/**
 * @brief     해당 위협 정보에 수동으로 위협 정보를 변경 처리한다.
 * @param     *pTheAETThreat 변경할 위협 데이터 포인터
 * @param     *pSELEmitterEdited 변경할 세부 내용
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-06-07, 오후 3:24
 * @warning
 */
void CELEmitterMergeMngr::UpdateAET( CELThreat *pTheAETThreat )
{
// 	SELAETDATA *pAETData;
// 	SELAETDATA_EXT *pAETExtData;
//
// 	SRxABTData abtData=SRxABTData();
//
// 	pAETData = GetAETData( pTheAETThreat->m_nIndex );
// 	pAETExtData = GetAETExtData( pTheAETThreat->m_nIndex );
//
// 	//m_pVecThreatInfo->clear();
//
// 	//////////////////////////////////////////////////////////////////////////
// 	// 기본 정보 업데이트
// 	// 수동 신호 업데이트는 증가하지 않도록 함.
// 	// ++ pAETData->uiCoLOB;
//
// 	// 항공 시간 정보로 해야 하는데 POSN 또는 연동기의 시간은 무시한다.
// 	pAETData->tiLastSeenTime = time(NULL);
//
// 	// AET 를 ABT로 변환
// 	ConvertAET2ABT( & abtData, & pSELEmitterEdited->aetData );
//
// 	// 주파수 정보
// 	UpdateFreqInfo( pAETData, pAETExtData, & abtData, NULL, & pSELEmitterEdited->userManual );
//
// 	// PRI 정보
// 	UpdatePRIInfo( pAETData, pAETExtData, & abtData, NULL, & pSELEmitterEdited->userManual );
//
// 	// 펄스폭 정보
// 	UpdatePWInfo( pAETData, pAETExtData, & abtData, NULL, & pSELEmitterEdited->userManual );
//
// 	// 신호세기 정보
// 	UpdatePAInfo( pAETData, pAETExtData, & abtData, NULL, & pSELEmitterEdited->userManual );
//
// 	// DB를 통한 분산, 표준편차, 평균 구하기
// 	// CalStatisticsFromAET( pAETData );
//
// 	// 위치 산출 정보
// 	UpdatePEInfo( pAETData, pAETExtData, pTheAETThreat, & abtData, & pSELEmitterEdited->userManual );
//
// 	// CED/EOB 식별
// 	UpdateIDInfo( pAETData, pAETExtData, pTheAETThreat, pSELEmitterEdited );
//
// 	// 빔 유효성 업데이트
// 	// 빔 유효성 체크는 무시한다.
// 	//UpdateBeamValidity( pAETData, pAETExtData, pTheAETThreat );
//
// 	//////////////////////////////////////////////////////////////////////////
// 	// 추가 정보 업데이트
// 	//pAETExtData->nCoTotalPdw += m_pLOBData->iNumOfPDW;
// 	//pAETExtData->nCoTotalIQ += m_pLOBData->iNumOfIQ;
//
// 	UpdateAETStat( pAETExtData );
//
// 	// 수동 변경 비트맵 데이터
// 	pAETExtData->xMannualEdited.val32 = pSELEmitterEdited->userManual.val32;
//
// 	pAETExtData->bManualPosEstPreferred = pSELEmitterEdited->bManualPosEstPreferred;
//
// 	pAETExtData->uiSeqNum = pSELEmitterEdited->uiSeqNum;
//
// 	if( pSELEmitterEdited->aetData.peInfo.iManualLongitude != 0 ) {
// 		pAETData->peInfo.iManualLongitude = pSELEmitterEdited->aetData.peInfo.iManualLongitude;
// 	}
// 	if( pSELEmitterEdited->aetData.peInfo.iManualLatitude != 0 ) {
// 		pAETData->peInfo.iManualLatitude = pSELEmitterEdited->aetData.peInfo.iManualLatitude;
// 	}

    // pAETExtData->bIntraMop = ( pAETData->intraInfo.iType != E_AET_MOP_UNK ? true : pAETExtData->bIntraMop );

}

/**
 * @brief     에미터의 상태를 변경한다.
 * @param     SELAETDATA_EXT * pAETExtData 방사체 정보 데이터
 * @param     bool bGenNewEmitter 생성 여부 플레그
 * @return    void
*/
void CELEmitterMergeMngr::UpdateAETStat( SELAETDATA_EXT *pAETExtData, bool bGenNewEmitter )
{
    // 신규 생성일 때는 Update 처리시 상태 정보를 무시한다.
    if( bGenNewEmitter == false ) {
        pAETExtData->enBeamEmitterStat = UpdateEmitterStat( pAETExtData->enBeamEmitterStat, E_ES_UPDATE );
/*
        if( pAETExtData->enBeamEmitterStat == E_ES_DEACTIVATED ) {
            pAETExtData->enBeamEmitterStat = E_ES_REACTIVATED;
        }
        else if( pAETExtData->enBeamEmitterStat == E_ES_DELETE ) {
            pAETExtData->enBeamEmitterStat = E_ES_REACTIVATED;
        }
        else {
            pAETExtData->enBeamEmitterStat = E_ES_UPDATE;
        }           */
    }

}

/**
 * @brief     UpdateABT
 * @param     CELThreat * pTheABTThreat
 * @param     SELEmitterEdited * pSELEmitterEdited
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-11-01, 오전 11:36
 * @warning
 */
void CELEmitterMergeMngr::UpdateABT( CELThreat *pTheABTThreat, SELAETDATA *pAETData )
{
    SRxABTData *pABTData;
    SELABTDATA_EXT *pABTExtData;

    if( pTheABTThreat != NULL ) {
        pABTData = GetABTData( pTheABTThreat->m_nIndex );
        pABTExtData = GetABTExtData( pTheABTThreat->m_nIndex );

        pABTData->tiLastSeenTime = time(NULL);

        //pABTExtData->bManualPosEstPreferred = pSELEmitterEdited->bManualPosEstPreferred;

        //pABTExtData->uiSeqNum = pSELEmitterEdited->uiSeqNum;

// 		if( pSELEmitterEdited->aetData.peInfo.iManualLongitude != 0 ) {
// 			pABTData->peInfo.iManualLongitude = pSELEmitterEdited->aetData.peInfo.iManualLongitude;
// 		}
// 		if( pSELEmitterEdited->aetData.peInfo.iManualLatitude != 0 ) {
// 			pABTData->peInfo.iManualLatitude = pSELEmitterEdited->aetData.peInfo.iManualLatitude;
// 		}

        if( pAETData != NULL ) { // 방사체 정보가 수동으로 변경될 때 이하 빔 정보도 일부 자동 변경하도록 함.
            pABTExtData->idInfo.nThreatIndex = pAETData->idInfo.nThreatIndex;
            pABTExtData->idInfo.nDeviceIndex = pAETData->idInfo.nDeviceIndex;

        }
    }

}

/**
 * @brief     ABT에 의한 식별된 정보만 이용하여 신호 식별을 수헹한다.
 * @param     *pAETData 위협의 데이터 포인터
 * @param     *pAETExtData 위협 추가 정보의 데이터 포인터
 * @param     *pTheAETThreat 최상위 노드의 포인터
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-04-06, 오후 2:49
 * @warning
 */
void CELEmitterMergeMngr::IdentifyAET( SRxAETData *pAETData, SELAETDATA_EXT *pAETExtData, CELThreat *pTheAETThreat )
{
#ifdef _IDENTIFY_AET_
    int i, j, nCnt=0;

    int nRefRadarIndex;
    int nBeamRadarModeIndex;

    CELThreat *pTheThreat;

    SRxABTData *pABTData;

    SRadarMode *pRadarMode;
    STR_CEDEOBID_INFO *pIDInfo, *pAETIDInfo;

    int *pCandidate, *pIndex;

    if( m_piCandidate != NULL ) {
        pIndex = m_piCandidate;
        pCandidate = m_piCandidate;

        pAETIDInfo = & pAETData->idInfo;
        memset( pAETIDInfo, 0, sizeof(STR_CEDEOBID_INFO) );

        //////////////////////////////////////////////////////////////////////////
        // 레이더 인덱스 구성
        // 1. ABT 들에 대해서 후보 레이더 인덱스 정보를 구성한다.
        pTheThreat = GetHeaderThreat( pTheAETThreat );
        while( pTheThreat != NULL ) { //#FA_C_PotentialUnboundedLoop_T1
            pABTData = GetABTData( pTheThreat->m_nIndex );
            if( pABTData == NULL ) {
                break;
            }

            pIDInfo = & pABTData->idInfo;

            memcpy( (char *) pIndex, (char *) pIDInfo->nRadarIndex, sizeof(int) * (UINT) pIDInfo->nCoRadarIndex );
            pIndex += pIDInfo->nCoRadarIndex;

            nCnt += pIDInfo->nCoRadarIndex;
            // 버퍼보다 클때 까지 저장한다.
            if( nCnt > MAX_AET_IDCANDIDATE-(2*MAX_IDCANDIDATE) ) { //DTEC_Else
                // 에러 메시지 표시
                break;
            }

            pTheThreat = GetNextThreat( pTheThreat );
        }

        // 2. 중복된 레이더 인덱스를 제거하고 위협 순으로 정렬한다.
        //아래 정렬후 레이더 인덱스가 거꾸로 됨.
        //m_theIdentifyAlg.SortRadarIndex( & nCnt, pCandidate, MAX_AET_IDCANDIDATE );
        nCnt = _min( MAX_IDCANDIDATE, nCnt );

        // 3. 레이더 인덱스를 저장한다.
        memcpy( pAETIDInfo->nRadarIndex, pCandidate, sizeof(int)*(UINT)nCnt );
        pAETIDInfo->nCoRadarIndex = nCnt;

        //////////////////////////////////////////////////////////////////////////
        // 레이더모드 인덱스 구성
        // 4. 레이더 인덱스를 중심으로 레이더모드 인덱스를 체크한다.
        //루프가 더 있어야 함. 아래 정렬후 레이더 인덱스가 거꾸로 됨.
        nCnt = 0;
        pIndex = pCandidate;
        nBeamRadarModeIndex = 0;
        for( i=0 ; i < pAETIDInfo->nCoRadarIndex ; ++i ) {
            nRefRadarIndex = pAETIDInfo->nRadarIndex[i];
            pTheThreat = GetHeaderThreat( pTheAETThreat );
            while( pTheThreat != NULL ) { //#FA_C_PotentialUnboundedLoop_T1
                int *pRadarModeIndex;

                pABTData = GetABTData( pTheThreat->m_nIndex );
                pIDInfo = & pABTData->idInfo;

                if( nBeamRadarModeIndex == 0 ) {
                    nBeamRadarModeIndex = pIDInfo->nRadarModeIndex[0];
                }

                pRadarModeIndex = & pIDInfo->nRadarModeIndex[0];
                for( j=0 ; j < pIDInfo->nCoRadarModeIndex ; ++j ) {
                    pRadarMode = GP_MNGR_CED_LIB2->RTGetRadarModeDataFromMemory( *pRadarModeIndex, m_pSEnvironVariable->eCEDDefaultLibType );
                    if( pRadarMode == NULL ) {
                        continue;
                    }

                    //nRadarIndex = m_theIdentifyAlg.GetRadarIndexFromRadarModeIndex( *pRadarModeIndex, m_pSEnvironVariable->eCEDDefaultLibType );
                    if( pRadarMode->nRadarIndex == nRefRadarIndex ) {
                        *pIndex = *pRadarModeIndex;
                        ++ pIndex;
                        ++ nCnt;
                    }
                    ++ pRadarModeIndex;
                }
                pTheThreat = GetNextThreat( pTheThreat );
            }
        }

        // 5. 레이더 모드 인덱스를 저장한다.
        nCnt = _min( MAX_IDCANDIDATE, nCnt );
        memcpy( pAETIDInfo->nRadarModeIndex, pCandidate, sizeof(int)*(UINT)nCnt );
        pAETIDInfo->nCoRadarModeIndex = nCnt;

        // 6. 위협 순으로 정렬한다.
        // m_theIdentifyAlg.SortRadarModePriority( pAETIDInfo, m_pSEnvironVariable->eCEDDefaultLibType );

        // 7. 레이더 모드 식별을 참조하여 위치 산출 식별을 종합하여 최종 결과를 리턴한다.
        pTheThreat = GetHeaderThreat( pTheAETThreat );
        if( pTheThreat != NULL ) {
            pABTData = GetABTData( pTheThreat->m_nIndex );
        }
        else {
            pABTData = NULL;
        }
        m_theIdentifyAlg.IdentifyAET( pAETData, pAETExtData, m_nLinkNum, m_pSEnvironVariable->eCEDDefaultLibType, m_pSEnvironVariable->eEOBDefaultLibType, pABTData );

        if( pAETData->idInfo.nCoRadarModeIndex == 0 ) {
            pAETData->idInfo.nCoRadarModeIndex = 1;
            pAETData->idInfo.nRadarModeIndex[0] = nBeamRadarModeIndex;
        }

    }
#else
    float fmaxMajor;

    CELThreat *pTheABTThreat, *pTheMajorABTThreat;

    SRxABTData *pABTData=NULL;
    SELABTDATA_EXT *pABTExtData=NULL;

    fmaxMajor = (float) 99999999.; //_spZero;
    pTheABTThreat = GetHeaderThreat( pTheAETThreat );
    pTheMajorABTThreat = pTheABTThreat;
    while( pTheABTThreat != NULL ) { //#FA_C_PotentialUnboundedLoop_T1
        pABTData = GetABTData( pTheABTThreat->m_nIndex );
        if( pABTData->fCEP < fmaxMajor  ) {
            fmaxMajor = pABTData->fCEP;

            pTheMajorABTThreat = pTheABTThreat;
        }

        pTheABTThreat = GetNextThreat( pTheABTThreat );

    }

    if( pTheMajorABTThreat != NULL ) {
        pABTData = GetABTData( pTheMajorABTThreat->m_nIndex );
        pABTExtData = GetABTExtData( pTheMajorABTThreat->m_nIndex );

        memcpy( & pAETExtData->idInfo, & pABTExtData->idInfo, sizeof(STR_CEDEOBID_INFO) );

        pAETData->iRadarModeIndex = pABTData->iRadarModeIndex;
    }

    //pABTExtData = GetABTExtData( pTheMajorABTThreat->m_nIndex );
    //m_theIdentifyAlg.SetIDResult( pAETData, pAETExtData, pABTExtData, m_pSEnvironVariable->eCEDDefaultLibType, m_pSEnvironVariable->eEOBDefaultLibType );

    //strcpy_s( pAETExtData->szELNOT, pABTExtData->szELNOT );

#endif

}

/**
 * @brief     수신한 LOB와 연관된 ABT 정보를 업데이트한다.
 * @param     *pThreat 빔 데이터 포인터
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-11, 오전 9:54
 * @warning
 */
bool CELEmitterMergeMngr::UpdateABT( CELThreat *pThreat, SELLOBDATA_EXT *pLOBDataExt, bool bRunCluster, bool bRunPE, bool bGenNewEmitter )
{
    bool bEnable; //, bCheckBeamValidity;
    int nIndex=pThreat->m_nIndex;

    m_pABTData = GetABTData( nIndex );
    m_pABTExtData = GetABTExtData( nIndex );

    if( m_bScanProcess == false ) {
        //////////////////////////////////////////////////////////////////////////
        // 기본 정보 업데이트
        ++ m_pABTData->uiCoLOB;
        pLOBDataExt->aetAnal.uiCoLOB = (UINT) m_pABTData->uiCoLOB;

        /*! \todo   병합 비교할 때 같은 놈끼리 병합하기 떄문에 아래와 같은 업데이트가 불필요한데, 그냥 복사하는 것으로 함.
                \author 조철희 (churlhee.jo@lignex1.com)
                \date 	2016-03-11 10:55:16
        */
        UpdateSignalInfo( m_pABTData, m_pABTExtData );

        UpdateSeenTime( m_pABTData, m_pABTExtData );

        // 방위 정보
        UpdateDOAInfo( m_pABTData, m_pABTExtData );

        // 펄스 정보
        //UpdatePulseInfo( pABTData, pABTExtData );

        // 주파수 정보
        UpdateFreqInfo( m_pABTData, m_pABTExtData );

        // PRI 정보
        UpdatePRIInfo( m_pABTData, m_pABTExtData );

        // 펄스폭 정보
        UpdatePWInfo( m_pABTData, m_pABTExtData );

        // 신호세기 정보
        UpdatePAInfo( m_pABTData, m_pABTExtData );

        // DB를 통한 분산, 표준편차, 평균 구하기
        // CalStatisticsFromABT( pABTData );

        // 스캔 정보
        //UpdateScanInfo( pABTData, pABTExtData );

        // 인트라 정보
        //UpdateIntraInfo( pABTData, pABTExtData );

        // 위치 산출 정보
        UpdatePEInfo( m_pABTData, m_pABTExtData, nIndex, false, bRunCluster, bRunPE );

        // 빔 유효성 업데이트
        //bCheckBeamValidity = ( bRunCluster || bRunPE );
        bEnable = UpdateBeamValidity( m_pABTData, m_pABTExtData, nIndex, ( bRunCluster || bRunPE ) );

        // LOB 클러스터링,
        if( bRunCluster == true ) {
            ProcessTheLOBClustering( m_pABTData, m_pABTExtData );
        }

        // CED/EOB 식별 정보
        IdentifyABT( m_pABTData, m_pABTExtData );

        UpdateIDInfo( m_pABTData, m_pABTExtData );

        //////////////////////////////////////////////////////////////////////////
        // 추가 정보 업데이트
        m_pABTData->uiTotalOfPDW += m_pLOBData->iNumOfPDW;
        //pABTExtData->nCoTotalIQ += m_pLOBData->iNumOfIQ;

        //pABTExtData->bIntraMop = ( pABTData->intraInfo.iTy1pe >= E_AET_MOP_PSK ? true : pABTExtData->bIntraMop );

        //pABTExtData->iTaskType = m_pLOBData->iTaskType / 2;

        m_pABTExtData->enBeamEmitterStat = UpdateEmitterStat( m_pABTExtData->enBeamEmitterStat, E_ES_UPDATE );

        // 방사체간의 병합을 위해서 정보를 저장
        m_pABTExtData->fLastAOA = m_pLOBData->fDOAMean;
        m_pABTExtData->fRadarLatitude = m_pLOBData->fRadarLatitude;
        m_pABTExtData->fRadarLongitude = m_pLOBData->fRadarLongitude;

    #ifdef _ELINT_
        m_pABTExtData->uiSeqNum = m_nSeqNum;
    #endif

        m_pABTExtData->bCompFreq = m_ABTDataExt.aetAnal.bCompFreq;
        m_pABTExtData->bCompPRI = m_ABTDataExt.aetAnal.bCompPRI;
    }
    else {
        UpdateSeenTime( m_pABTData, m_pABTExtData );

        // 방위 정보
        UpdateDOAInfo( m_pABTData, m_pABTExtData );

        // 펄스폭 정보
        UpdatePWInfo( m_pABTData, m_pABTExtData );

        // 신호세기 정보
        UpdatePAInfo( m_pABTData, m_pABTExtData );

        // 스캔 정보
        UpdateScanInfo( m_pABTData, m_pABTExtData );

        // CED/EOB 식별 정보
        IdentifyABT( m_pABTData, m_pABTExtData );

        UpdateIDInfo( m_pABTData, m_pABTExtData );

        m_pABTExtData->enBeamEmitterStat = UpdateEmitterStat( m_pABTExtData->enBeamEmitterStat, E_ES_UPDATE );

#ifdef _ELINT_
        m_pABTExtData->uiSeqNum = m_nSeqNum;
#endif

        m_pABTExtData->bCompFreq = m_ABTDataExt.aetAnal.bCompFreq;
        m_pABTExtData->bCompPRI = m_ABTDataExt.aetAnal.bCompPRI;

        bEnable = true;
    }

    //LogPrint("\n========================================== UpdateABT 시간 : %d ms", (int)((GetTickCount() - dwTime) / 1));

    return bEnable;
}

/**
 * @brief CELEmitterMergeMngr::UpdateEmitterStat
 * @param enBeamEmitterStat
 * @param enUpdatedStat
 * @return
 */
E_BEAM_EMITTER_STAT CELEmitterMergeMngr::UpdateEmitterStat( E_BEAM_EMITTER_STAT enBeamEmitterStat, E_BEAM_EMITTER_STAT enUpdatedStat )
{
    E_BEAM_EMITTER_STAT enReturn=E_ES_NOT_AVAILABLE;

    if( enUpdatedStat == E_ES_NEW || enUpdatedStat == E_ES_DELETE || enUpdatedStat == E_ES_DEACTIVATED ) {
        enReturn = enUpdatedStat;
    }
    else if( enUpdatedStat == E_ES_UPDATE ){
        if( enBeamEmitterStat == E_ES_DEACTIVATED ) {
            enReturn = E_ES_REACTIVATED;
        }
        else if( enBeamEmitterStat == E_ES_REACTIVATED ) {
            enReturn = E_ES_UPDATE;
        }
        else {
            enReturn = enUpdatedStat;
        }
    }

    return enReturn;
}

/**
 * @brief     시간 정보를 업데이트 한다.
 * @param     *pABTData 빔 정보 데이터 포인터
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-11-14, 오후 5:45
 * @warning
 */
void CELEmitterMergeMngr::UpdateSeenTime( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
{
    SetupDateTime( & m_LOBDataExt );

    if( pABTData->tiLastSeenTime < m_LOBDataExt.aetAnal.tiAcqTime ) {
        pABTData->tiLastSeenTime = m_LOBDataExt.aetAnal.tiAcqTime;
        //pABTData->lastSeenMillisec = (UINT) m_LOBDataExt.aetAnal.tiContactTimems;
    }
    if( pABTData->tiFirstSeenTime > m_LOBDataExt.aetAnal.tiAcqTime ) {
        pABTData->tiFirstSeenTime = m_LOBDataExt.aetAnal.tiAcqTime;
        //pABTData->firstSeenMillisec = (UINT) m_LOBDataExt.aetAnal.tiContactTimems;
    }
}

/**
 * @brief     시간 정보를 업데이트 한다.
 * @param     *pABTData 빔 정보 데이터 포인터
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-11-14, 오후 5:45
 * @warning
 */
void CELEmitterMergeMngr::UpdateSeenTime( SRxAETData *pAETData, SELAETDATA_EXT *pAETExtData, SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
{

    if( pAETData->tiLastSeenTime < pABTData->tiLastSeenTime ) {
        pAETData->tiLastSeenTime = pABTData->tiLastSeenTime;
        //pAETData->lastSeenMillisec = pABTData->lastSeenMillisec;
    }
    if( pAETData->tiFirstSeenTime > pABTData->tiFirstSeenTime ) {
        pAETData->tiFirstSeenTime = pABTData->tiFirstSeenTime;
        //pAETData->firstSeenMillisec = pABTData->firstSeenMillisec;
    }
}

/**
 * @brief     방사체의 시간 정보를 업데이트 한다.
 * @param     SELAETDATA * pUpdateAETData
 * @param     SELAETDATA_EXT * pUpdateAETExtData
 * @param     SELAETDATA * pDeleteAETData
 * @param     SELAETDATA_EXT * pDeleteAETExtData
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @warning
*/
void CELEmitterMergeMngr::UpdateSeenTime( SRxAETData *pUpdateAETData, SELAETDATA_EXT *pUpdateAETExtData, SELAETDATA *pDeleteAETData, SELAETDATA_EXT *pDeleteAETExtData )
{
    if( pUpdateAETData->tiLastSeenTime < pDeleteAETData->tiLastSeenTime ) {
        pUpdateAETData->tiLastSeenTime = pDeleteAETData->tiLastSeenTime;
        //pUpdateAETData->lastSeenMillisec = pDeleteAETData->lastSeenMillisec;
    }
    if( pUpdateAETData->tiFirstSeenTime > pDeleteAETData->tiFirstSeenTime ) {
        pUpdateAETData->tiFirstSeenTime = pDeleteAETData->tiFirstSeenTime;
        //pUpdateAETData->firstSeenMillisec = pDeleteAETData->firstSeenMillisec;
    }
}

/**
 * @brief     빔 정보를 신호 식별을 수행한다.
 * @param     *pABTData 빔 정보 데이터 포인터
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-06-13, 오후 5:45
 * @warning
 */
void CELEmitterMergeMngr::IdentifyABT( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
{

    //m_ABTDataExt.aetAnal.iTaskType = m_pLOBData->iTaskType;
    m_pIdentifyAlg->Identify( pABTData, pABTExtData, & m_LOBDataExt, false );

    /*
    if( m_pLOBData->aucRadarName[0] != 0 ) {
#ifdef _MSC_VER
        strcpy_s( pABTData->aucRadarName, sizeof(pABTData->aucRadarName), m_pLOBData->aucRadarName );
#else
        strcpy_s( pABTData->aucRadarName, m_pLOBData->aucRadarName );
#endif
    }
    */

    //pABTData->iRadarModeIndex = m_pLOBData->iRadarModeIndex;

    //LogPrint("\n========================================== ABT Identify 시간 : %d ms(B%d, L%d)", (int)((GetTickCount() - dwTime) / 1), pABTData->uiABTID, m_pLOBData->uiLOBID );

}

/**
 * @brief     CouldIdentify
 * @param     SRxABTData * pABTData
 * @param     SELABTDATA_EXT * pABTExtData
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-02-21, 오후 2:40
 * @warning
 */
bool CELEmitterMergeMngr::CouldIdentify( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
{
    bool bRet = true;
    STR_ID_TYPE *pIDType;

    pIDType = & pABTExtData->stIDType;

    if( pABTData->iSignalType == pIDType->iSignalType && pABTData->iFreqType == pIDType->iFrqType && pABTData->iPRIType == pIDType->iPRIType /* && \
        pABTData->scanInfo.iType == pIDType->iScanType && pABTData->intraInfo.iType == pIDType->iMOPType */ ) {
        bRet = false;
    }

    return bRet;
}

/**
 * @brief     ABT 의 빔 유효성을 업데이트
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-29, 오후 3:56
 * @warning
 */
bool CELEmitterMergeMngr::UpdateBeamValidity( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData, int nIndex, bool bCheckBeamValidity )
{
    bool bRet=true;

    float fDist;

    if( bCheckBeamValidity == true ) {
        switch( pABTData->iPEValid ) {
        case E_EL_PESTAT_FAIL :
            pABTData->iValidity = false;
            break;

        case E_EL_PESTAT_SUCCESS :
            // 유효한 갯수를 비교하여 빔 유효성을 업데이트한다.

            if( pABTData->iValidity == false ) {
                // 항공기 위치와 위치 산출 위치가 가까운 경우를 고려해서 빔 유효성 체크함.
                fDist = (float) m_theInverseMethod.EllipsoidDistance( (double) pABTData->fLatitude, (double) pABTData->fLongitude, m_pLOBData->fRadarLatitude, m_pLOBData->fRadarLongitude );
                if( IsValidity( pABTData->uiCoLOB, (int) m_pSEnvironVariable->uiEmmgNumOfMinLobToBeam, pABTData->fCEP, m_pSEnvironVariable->fEobIndfRangeMeters, pABTData->fMajorAxis, pABTData->fMinorAxis, fDist ) == true )  {
                    // 위치 산출한 것을 기준으로 모든 LOB에 대해서 체크를 한다.
                    pABTData->iValidity = CheckValidityByAllLOB( & m_pVecLOBs[nIndex], pABTData );
                }
            }
            else {
                // 유효일 때 방위차 전시
                //PrintAllValidityByAllLOB( & m_pVecLOBs[nIndex], pABTData );
            }
            break;

        case E_EL_PESTAT_NOT_YET :
            pABTData->iValidity = false;
            break;

        case E_EL_PESTAT_IMPOSSIBILITY :
        default :
            {	//DTEC_Else
                pABTData->iValidity = false;
            }
            break;
        }
    }
    else {
// 		if( m_bGenNewEmitter == true ) {
// 			pABTData->iValidity = true;
// 		}
    }

    return bRet;
}

//////////////////////////////////////////////////////////////////////
/*!
 * @brief			LOB 클러스터링을 수행한다.
 * @return    void
 * @param     SRxABTData * pABTData
 * @param     SELABTDATA_EXT * pABTExtData
 * @version   0.0.1
 * @author    조철희(churlhee.jo@lignex1.com)
 * @date      2017-09-14 오후 10:32
 * @warning
 */
void CELEmitterMergeMngr::ProcessTheLOBClustering( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
{
    bool bCluster;
    //DWORD dwTime = GetTickCount();

    // DB가 끊겨져 있을 경우에는 LOB 클러스터링 체크를 중지한다.
    // CED 식별된것만 수행한다.
    if( pABTExtData->bApplayOfLOBClustering == false && ( pABTExtData->idInfo.nCoRadarModeIndex >= _spOne ) ) {
        UINT uiGetEmmgNumOfMinLobToBeam= g_pTheELEnvironVariable->GetEmmgNumOfMinLobToBeam();
        if( pABTData->iValidity == 0 && pABTData->uiCoLOB >= uiGetEmmgNumOfMinLobToBeam ) {
            // LOB 클러서링을 수행하여 유효 여부를 최종 확인함.
            if( true /* GP_MGR_PARAM->IsLOBClustering() == true */ ) {
                bCluster = LOBClustering( pABTExtData->iLOBPoolIndex, & pABTExtData->idInfo );

                // 클러스터링 존재 유무시에 신규 에미터로 생성할 에미터를 추린다.
                if( bCluster == true /* && iValidity == true */ ) {
                    UpdateClusterInfo( pABTData->uiAETID, pABTData->uiABTID, pABTExtData->iLOBPoolIndex );
                    pABTExtData->bApplayOfLOBClustering = true;

                }
            }
            //TRACE("\n========================================== ProcessTheLOBClustering 시간 : %d ms", (int)((GetTickCount() - dwTime) / 1));
        }
    }


}

//////////////////////////////////////////////////////////////////////
/*!
 * @brief
 * @return    void
 * @param     void
 * @version   0.0.1
 * @author    조철희(churlhee.jo@lignex1.com)
 * @date      2017-12-13 오전 11:15
 * @warning
 */
void CELEmitterMergeMngr::RunLOBClusteringResult()
{
    SRxLOBHeader *pLOBHeader;										///< 항공기에서 수신한 LOB 헤더 데이터 포인터
    SRxLOBData *pLOBData;						///< 항공기에서 수신한 LOB 메시지 데이터 포인터

    SELLOBDATA_EXT stLOBDataExt;

    // 1. 추가 LOB에 대해서 LOB 클러스터링을 수행
    if( IsThereClustering() == true ) {
        NextSeqNum();

        // LOB 데이터 복구
        pLOBHeader = m_pLOBHeader;
        pLOBData = m_pLOBData;
        stLOBDataExt = m_LOBDataExt;

        // LOB 결과 수행
        CreateThreatFromLOBClustering( CLOBClustering::m_uiABTID );

        // 클러스터링을 수행 안 하도록 한다.
        CloseClustering();

        // LOB 데이터 복구
        m_pLOBHeader = pLOBHeader;
        m_pLOBData = pLOBData;
        m_LOBDataExt = stLOBDataExt;

        // 2. 잔여 LOB에 대해서 LOB 클러스터링을 수행
        //SRxABTData *pABTData = GetABTData( m_pABTThreat->m_nIndex );
        //SELABTDATA_EXT *pABTExtData = GetABTExtData( m_pABTThreat->m_nIndex );
        // ProcessTheLOBClustering( pABTData, pABTExtData );

    }

}

/**
 * @brief     IsValidity
 * @param     int nCoBeamValidity
 * @param     int iEmmgNumOfMinLobToBeam
 * @param     int iCEP
 * @param     int iEobIndfRangeNM
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-02-22, 오후 4:55
 * @warning
 */
bool CELEmitterMergeMngr::IsValidity( int nCoBeamValidity, int iEmmgNumOfMinLobToBeam, float fCEP, float fEobIndfRangeMeter, float fMajorAxis, float fMinorAxis, float fDist )
{
    bool bRet = false;

    // FLTM 일때 거리가 짧아서 위치 산출이 된 경우를제거하기 위해서 거리 추가하여 체크
    bRet = ( nCoBeamValidity >= iEmmgNumOfMinLobToBeam ) &&
                 ( ( fCEP <= fEobIndfRangeMeter && fCEP > 0 ) ||
                 ( ( UDIV( fMajorAxis, 2 ) <= MAJOR_MAX_LIMIT ) && ( UDIV( fMinorAxis, 2 ) <= MINOR_MAX_LIMIT ) && ( fDist <= 20 /* GP_MGR_PARAM->GetEffectiveDist() */ ) ) );
    return bRet;
}

/**
 * @brief     LOB 클러스터링으로부터 방사체 및 빔을 생성한다.
 * @param     UINT uiABTID 빔 번호
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-02-22, 오전 10:10
 * @warning
 */
bool CELEmitterMergeMngr::CreateThreatFromLOBClustering( UINT uiABTID )
{
    bool bRet=true, bCreate;
    UINT i;

    bool bFirstNew=true, bFirstOld=true;
    SELMERGE_CANDIDATE mergeCandidateNew=SELMERGE_CANDIDATE();
    SELMERGE_CANDIDATE mergeCandidateOld=SELMERGE_CANDIDATE();

    vector<SELMERGE_CANDIDATE> vecCanOfMergeLOBNew;
    vector<SELMERGE_CANDIDATE> vecCanOfMergeLOBOld;

    SELABTDATA_EXT *pSourceABTExtData;
    SELABTDATA_EXT *pCreateABTExtData;
    SELABTDATA_EXT *pDestABTExtData;

    //SELEmitterEdited stSELEmitterEdited, stOldSELEmitterEdited;

    std::vector<SRxLOBHeader>::iterator itLOBHeader;
    std::vector<SRxLOBData>::iterator itLOBData;

    std::vector<SRxLOBHeader> vecLOBHeader;	///< DB에서 읽어온 LOB 데이터
    std::vector<SRxLOBData> vecLOBData;			///< DB에서 읽어온 LOB 헤더 데이터

    int nProcessLOBClustering=0, nLastProcessLOBClustering;
    int nProcessLOBClusteringOld=0, nLastProcessLOBClusteringOld;

    int nAETIDOfLOBCluster=0, nABTIDOfLOBCluster=0;

    CELThreat *pDestThreatAET=NULL, *pDestThreatABT=NULL, *pSourceThreatAET=NULL, *pSourceThreatABT=NULL;

    // 1. Queue Empty 확인
    if( true /* == GP_MGR_INSERTDB->WaitUntilQueueEmpty() */ ) {
        nLastProcessLOBClustering = GetCountOfOptimalLOBID();

        //DWORD dwTime = GetTickCount();

        // 0. 원본 위협 지정
        pDestThreatAET = m_pAETThreat;
        pDestThreatABT = m_pABTThreat;

        pDestABTExtData = GetABTExtData( pDestThreatABT->m_nIndex );

        // 0. 병합 후보 클리어
        m_vecCanOfMergeLOB.clear();

        // 1. 빔 번호로 LOB 데이터 갖고 오기
        //DWORD dwTime2 = GetTickCount();
        FetchLOBData( & vecLOBHeader, & vecLOBData, CLOBClustering::m_uiABTID );
        //LogPrint("\n========================================== FetchLOBData(%d) 시간 : %d ms", vecLOBData.size(), (int)((GetTickCount() - dwTime2) / 1));
        if( vecLOBData.size() != 0 ) {
            itLOBHeader = vecLOBHeader.begin();
            itLOBData = vecLOBData.begin();

            // LOB 목록에 있는 방사체, 빔 정보를 제거한다.
            //dwTime2 = GetTickCount();
            DeleteAllAETABTRecord( &(*itLOBData) );

            //stSELEmitterEdited.nAETId = (int) vecLOBData.data()->uiAETID;
            //stSELEmitterEdited.nABTId = (int) vecLOBData.data()->uiABTID_LinkNum;
            //stSELEmitterEdited.nLOBId = 0;

            nLastProcessLOBClusteringOld = (int) vecLOBData.size() - nLastProcessLOBClustering;

            // 2. LOB 데이터로 부터 방사체 및 빔 번호를 생성한다.
            LogPrint( "\n LOB 클러스터링 수행 [B%d]", uiABTID );
            for( i=0 ; i < vecLOBData.size() ; ++i ) { //#FA_C_PotentialUnboundedLoop_T2

                // 2. 신규 LOB에 대해서 식별 및 기초 작업을 수행한다. (클러스터링 된것을 방사체/빔 생성)
                LOBPreSetting( &(*itLOBHeader), &(*itLOBData), NULL );
                IdentifyLOB( m_pLOBData );

                if( IsThereOptimalLOBID( (int) m_pLOBData->uiLOBID ) == true ) {
                    ++ nProcessLOBClustering;
                    LogPrint( "\n##### 신규 생성 LOB : %d", m_pLOBData->uiLOBID );

                    if( bFirstNew == true ) {
                        // 동일한 방사체, SEQNUM 이기 떄문에 먼저 지우고 생성한다.
                        //DeleteAETABTRecord( m_LOBDataExt.aetAnal.iLinkNum, m_pLOBData );

                        //strcpy_s( mergeCandidateNew.szELNOT, pDestABTExtData->szELNOT );
                        bCreate = CreateThreat( & m_LOBDataExt, true, true, m_nSeqNum, 0, 0, & mergeCandidateNew );
                        if( bCreate == false ) {
                            TRACE( "\n [에러] 생성 에러[%d]", CLOBClustering::m_uiABTID );
                            continue;
                        }

                        pCreateABTExtData = GetABTExtData( m_pABTThreat->m_nIndex );

                        mergeCandidateNew.fLevel = 0;
                        mergeCandidateNew.idx.uiAET = m_LOBDataExt.aetAnal.uiAETID;
                        mergeCandidateNew.idx.uiABT = m_LOBDataExt.aetAnal.uiABTID;
                        mergeCandidateNew.idx.uiLOB = INVALID_INDEX;
                        //strcpy_s( mergeCandidateNew.szELNOT, pDestABTExtData->szELNOT );

                        vecCanOfMergeLOBNew.push_back( mergeCandidateNew );

                        bFirstNew = false;

                        IncH0000( m_LOBDataExt.aetAnal.idInfo.nCoRadarModeIndex );

                    }
                    else {
                        // 동일한 방사체, SEQNUM 이기 떄문에 먼저 지우고 생성한다.
                        //DeleteAETABTRecord( m_LOBDataExt.aetAnal.iLinkNum, m_pLOBData );

                        // 매번 위치 산출을 수행할 필요가 없고, LOB 클러스터링 할 필요가 없는데...
                        m_pABTThreat = UpdateThreat( & m_LOBDataExt, true, & vecCanOfMergeLOBNew, true, m_nSeqNum, NULL, NULL, false, nProcessLOBClustering == nLastProcessLOBClustering );
                        LogPrint( "\n # %d, AET %d, ABT : %d, LOB : %d", m_nSeqNum, m_LOBDataExt.aetAnal.uiAETID, m_LOBDataExt.aetAnal.uiABTID, m_pLOBData->uiLOBID );
                    }

                    // 3. 기존 LOB의 변경하고 전시한다.
                    LogPrint( "\n신규 생성" );
                    UpdateLOB();

                    //stSELEmitterEdited.uiSeqNum = pLOBData->uiFetchSeqNum;
                    //AddThreatInfo( & stSELEmitterEdited, E_MR_REMOVE_LOB, -1, (pLOBGrp->iIsFISINTTask >= 1), (UINT) pLOBGrp->uiFetchSeqNum );

                    if( nProcessLOBClustering == nLastProcessLOBClustering ) {
                        nAETIDOfLOBCluster = (int) m_LOBDataExt.aetAnal.uiAETID;
                        nABTIDOfLOBCluster = (int) m_LOBDataExt.aetAnal.uiABTID;

                        // LOB 목록창에 있는 방사체/빔 번호를 변경 -- 무시
                        //stSELEmitterEdited.nAETId = m_pLOBData->uiAETID;
                        //stSELEmitterEdited.nABTId = m_pLOBData->uiABTID_LinkNum;
                        //stSELEmitterEdited.nLOBId = 0;
                        //stSELEmitterEdited.uiSeqNum = m_pLOBData->uiFetchSeqNum;
                        //stSELEmitterEdited.enEmitterStat = E_MR_UPDATE;
                        //stSELEmitterEdited.iChangedAETID = (int) m_LOBDataExt.aetAnal.uiAETID;
                        //stSELEmitterEdited.iChangedABTID = (int) m_LOBDataExt.aetAnal.uiABTID;
                        //AddThreatInfo( & stSELEmitterEdited, E_MR_CHANGE, -1, m_pLOBData->iIsFISINTTask >= 1, (UINT) m_pLOBData->uiFetchSeqNum );
                    }
                }
                // 기존 LOB 를 기준으로 신규 방사체/빔 제원을 생성한다.
                else {
                    ++ nProcessLOBClusteringOld;
                    LogPrint( "\n##### 기존 변경 LOB : %d", m_pLOBData->uiLOBID );

                    if( bFirstOld == true ) {
                        // 동일한 방사체, SEQNUM 이기 떄문에 먼저 지우고 생성한다.
                        //DeleteAETABTRecord( m_LOBDataExt.aetAnal.iLinkNum, m_pLOBData );

                        bCreate = CreateThreat( & m_LOBDataExt, true, true, m_nSeqNum, m_pLOBData->uiAETID );
                        if( bCreate == false ) {
                            TRACE( "\n [에러] CLOBClustering::m_uiABTID[%d]", CLOBClustering::m_uiABTID );
                            continue;
                        }
                        //LogPrint( "\n # %d, AET %d, ABT : %d, LOB : %d", m_nSeqNum, m_pLOBData->uiAETID, m_pLOBData->uiABTID_LinkNum, m_pLOBData->uiLOBID );

                        // 0. 원본 위협 지정
                        pSourceThreatAET = m_pAETThreat;
                        pSourceThreatABT = m_pABTThreat;

                        pSourceABTExtData = GetABTExtData( pSourceThreatABT->m_nIndex );

                        mergeCandidateOld.fLevel = 0;
                        mergeCandidateOld.idx.uiAET = m_pLOBData->uiAETID;
                        //mergeCandidateOld.idx.uiABT = m_pLOBData->uiABTID_LinkNum;
                        mergeCandidateOld.idx.uiLOB = INVALID_INDEX;
                        if( pSourceABTExtData != NULL ) {
                            //strcpy_s( mergeCandidateOld.szELNOT, pSourceABTExtData->szELNOT );
                        }
                        else {
                            //mergeCandidateOld.szELNOT[0] = NULL;
                        }
                        vecCanOfMergeLOBOld.push_back( mergeCandidateOld );

                        bFirstOld = false;

                        IncH0000( m_LOBDataExt.aetAnal.idInfo.nCoRadarModeIndex );

                    }
                    else {
                        if( bCreate == false ) {
                            continue;
                        }

                        // 동일한 방사체, SEQNUM 이기 떄문에 먼저 지우고 생성한다.
                        //DeleteAETABTRecord( m_LOBDataExt.aetAnal.iLinkNum, m_pLOBData );

                        // 매번 위치 산출을 수행할 필요가 없는데...
                        UpdateThreat( & m_LOBDataExt, true, & vecCanOfMergeLOBOld, true, m_nSeqNum, pSourceThreatAET, pSourceThreatABT, false, nProcessLOBClusteringOld == nLastProcessLOBClusteringOld );
                        //LogPrint( "\n # %d, AET %d, ABT : %d, LOB : %d", m_nSeqNum, m_pLOBData->uiAETID, m_pLOBData->uiABTID_LinkNum, m_pLOBData->uiLOBID );
                    }

                    LogPrint( "\n기존 생성" );
                    UpdateLOB();
                    // InsertLOB( & m_LOBDataExt, false );

    // 				if( bCreate == true && nProcessLOBClusteringOld == nLastProcessLOBClusteringOld ) {
    // 					stSELEmitterEdited.nAETId = m_pLOBData->uiAETID;
    // 					stSELEmitterEdited.nABTId = m_pLOBData->uiABTID;
    // 					stSELEmitterEdited.nLOBId = 0;
    // 					//AddThreatInfo( & stSELEmitterEdited, (E_BEAM_EMITTER_STAT) E_MR_NO_UPDATE_LOB, m_pLOBData->uiCoLOB, m_pLOBData->iIsFISINTTask >= 1, m_pLOBData->iFetchSeqNum );
    // 				}

                }

                // 5. DB 인덱스 번호 증가 : 매우 중요
                NextSeqNum();

                ++ itLOBHeader;
                ++ itLOBData;
            }

            //LogPrint("\n========================================== CreateThreatFromLOBClustering(%d, 기존: B%d -> A%d,B%d) 시간 : %d ms", vecLOBData.size(), uiABTID, nAETIDOfLOBCluster, nABTIDOfLOBCluster, (int)((GetTickCount() - dwTime) / 1));

            // 6. 최종 방사체/빔 정보를 복사해한다.
            //CopyThreat( pDestThreatAET, pDestThreatABT, pSourceThreatAET, pSourceThreatABT );
            //DeleteThreat( pSourceThreatAET, pSourceThreatABT );

            // 7. LOB 클러스터링에서 해당 LOB를 제거한다.
            // DeleteAllLOBData();

        }
        else {
            bRet = false;

            LogPrint( "LOB DB에 기록이 안 되어 클러스터링을 수행하지 못 합니다 !!" );
        }
    }

    return bRet;

}

/**
 * @brief     DeleteAllAETABTRecord
 * @param     std::vector<SRxLOBData>* pVecLOBData
 * @param     std::vector<SRxLOBDataGroup>* pVecLOBGrp
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2018-01-10, 오후 12:25
 * @warning
 */
void CELEmitterMergeMngr::DeleteAllAETABTRecord( SRxLOBData *pLOBData )
{
// 	DWORD dwTime = GetTickCount();
// 	CString strCondition;
//
// 	// 기존 LOB 삭제
// 	//strCondition.Format( "MISSION_ID='%s' AND AET_ID='%d' AND ABT_ID='%d'", GetMissionID( iLinkNum ), pLOBDataGroup->uiAETID, pLOBDataGroup->uiABTID );
// 	//_CALL_DB( DeleteToDB( "E_AA_MSG_LOB", nullptr, (LPCTSTR) strCondition ) );
// 	//LogPrint( "\n LOB 정보[A%d, B%d]를 삭제합니다." , pLOBDataGroup->uiAETID, pLOBDataGroup->uiABTID );
//
// 	// 방사체 삭제
// 	strCondition.Format( "MISSION_ID='%s' AND AET_ID='%d'", GetMissionID( iLinkNum ), pLOBDataGroup->uiAETID );
// 	_CALL_DB( DeleteToDB( "E_AA_GMI_EMITTER", nullptr, (LPCTSTR) strCondition ) )
// 	LogPrint( "\n 방사체 정보[A%d]를 삭제합니다.", pLOBDataGroup->uiAETID );
//
// 	// 빔 삭제
// 	strCondition.Format( "MISSION_ID='%s' AND AET_ID='%d' AND ABT_ID='%d'", GetMissionID( iLinkNum ), pLOBDataGroup->uiAETID, pLOBDataGroup->uiABTID_LinkNum );
// 	_CALL_DB( DeleteToDB( "E_AA_GMI_BEAM", nullptr, (LPCTSTR) strCondition ) )
//
// 	// 빔 관련 엘리먼트 삭제
// 	_CALL_DB( DeleteToDB( "E_AA_GMI_BEAM_ELMT_LIST", nullptr, (LPCTSTR) strCondition ) )
// 	LogPrint( "\n 빔 및 엘리먼트 정보[A%d, B%d]를 삭제합니다.", pLOBDataGroup->uiAETID, pLOBDataGroup->uiABTID_LinkNum );
//
// 	LogPrint("\n========================================== DeleteAllAETABTRecord 시간 : %d ms", (int)((GetTickCount() - dwTime) / 1));

}

//////////////////////////////////////////////////////////////////////
/*!
 * @brief
 * @return    void
 * @param     void
 * @version   0.0.1
 * @author    조철희(churlhee.jo@lignex1.com)
 * @date      2017-12-13 오전 10:42
 * @warning
 */
void CELEmitterMergeMngr::UpdateLOB()
{
// 	DWORD dwTime = GetTickCount();
//
// 	SELEXTDB extDB=SELEXTDB();
//
// 	_FIELD_INFO stField("","");
// 	list<_FIELD_INFO> listFieldInfo;
// 	CString strCondition = _T(""), strTemp = _T("");
//
// 	SELEmitterEdited stSELEmitterEdited;
//
// 	string strTableName="E_AA_MSG_LOB";
//
// 	UpdateLOBData( false );
//
// 	// 업데이트할 데이터 작업을 수행한다.
// 	stField.strFieldName = "SEQ_NUM";
// 	strTemp.Format( "%d", m_nSeqNum );
// 	stField.strFieldValue = strTemp;
// 	listFieldInfo.push_back( stField );
//
// 	stField.strFieldName = "ABT_ID";
// 	strTemp.Format( "%d", m_LOBDataExt.aetAnal.uiABTID );
// 	stField.strFieldValue = strTemp;
// 	listFieldInfo.push_back( stField );
//
// 	stField.strFieldName = "AET_ID";
// 	strTemp.Format( "%d", m_LOBDataExt.aetAnal.uiAETID );
// 	stField.strFieldValue = strTemp;
// 	listFieldInfo.push_back( stField );
//
// // #ifdef UPDATETODB_THREAD
// // 	strcpy( extDB.acMissionID, GetMissionID( m_LOBDataExt.aetAnal.iLinkNum ) );
// // 	SendInsertDBThread( CMDCODE_UPDATEDB_LOBDATA_, m_pLOBData, m_pLOBData, & m_LOBDataExt, & extDB );
// // #else
// 	strCondition.Format( "SEQ_NUM ='%d' AND MISSION_ID='%s' AND LOB_ID='%d'", m_pLOBData->uiFetchSeqNum, GetMissionID( m_LOBDataExt.aetAnal.iLinkNum ), m_pLOBData->uiLOBID  );
// 	_CALL_DB( UpdateToDB( strTableName, & listFieldInfo, nullptr, strCondition.GetBuffer(), NULL, false, true ) )
//
// 	strTableName="E_AA_MSG_LOB_ELMT_LIST";
// 	_CALL_DB( UpdateToDB( strTableName, & listFieldInfo, nullptr, strCondition.GetBuffer(), NULL, false, true ) )
// //#endif
// 	//LogPrint( "\n DB 테이블에서 LOB 데이터[S%6d/A%6d/B%6d]를 [S%6d/A%6d/B%6d]로 변경한다." , m_pLOBData->uiFetchSeqNum, m_pLOBData->uiAETID, m_pLOBData->uiABTID_LinkNum, m_nSeqNum, m_LOBDataExt.aetAnal.uiABTID, m_LOBDataExt.aetAnal.uiAETID );
//
// 	stSELEmitterEdited.nAETId = (int) m_pLOBData->uiAETID;
// 	stSELEmitterEdited.nABTId = (int) m_pLOBData->uiABTID_LinkNum;
// 	stSELEmitterEdited.nLOBId = (int) m_pLOBData->uiLOBID;
// 	//AddThreatInfo( & stSELEmitterEdited, E_MR_REMOVE, pABTExtData->uiCoLOB, pABTExtData->bIsFISINTTask, m_pLOBData->iFetchSeqNum );
//
// 	stSELEmitterEdited.nAETId = (int) m_LOBDataExt.aetAnal.uiAETID;
// 	stSELEmitterEdited.nABTId = (int) m_LOBDataExt.aetAnal.uiABTID;
// 	stSELEmitterEdited.nLOBId = (int) m_LOBDataExt.aetAnal.uiLOBID;
// 	//AddThreatInfo( & stSELEmitterEdited, E_MR_UPDATE_LOB, pABTExtData->uiCoLOB, pABTExtData->bIsFISINTTask, m_pLOBData->iFetchSeqNum );
//
// 	LogPrint("\n========================================== UpdateLOB 시간 : %d ms", (int)((GetTickCount() - dwTime) / 1));

}
//
/**
 * @brief     AET 의 빔 유효성을 업데이트 한다.
 * @param     *pAETData 방사체 정보의 데이터 포인터
 * @param     *pAETExtData 빔 정보의 데이터 포인터
 * @param     *pTheAETThreat 방사체 정보의 데이터 포인터
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-29, 오후 5:37
 * @warning
 */
void CELEmitterMergeMngr::UpdateBeamValidity( SRxAETData *pAETData, SELAETDATA_EXT *pAETExtData, CELThreat *pTheAETThreat )
{
    CELThreat *pTheABTThreat;

    pAETData->iValidity = true;

    pTheABTThreat = GetHeaderThreat( pTheAETThreat );
    while( pTheABTThreat != NULL ) { //#FA_C_PotentialUnboundedLoop_T1
        //UELTHREAT *pUniThreat;
        SRxABTData *pABTData;

        //pUniThreat = m_pUniThreat + pTheABTThreat->m_nIndex;
        //pABTData = & pUniThreat->uniABT.stABTData;
        pABTData = GetABTData( pTheABTThreat->m_nIndex );

        if( pABTData->iValidity == false ) {
            pAETData->iValidity = false;
            break;
        }

        pTheABTThreat = GetNextThreat( pTheABTThreat );
    }

}

/**
 * @brief     방사체 정보의 위치 정보를 변경한다.
 * @param     *pAETData 방사체 정보의 데이터 포인터
 * @param     *pAETExtData 방사체 추가 정보의 데이터 포인터
 * @param     *pTheAETThreat 방사체 정보의 데이터 포인터
 * @param     *pManABTData 빔 정보의 데이터 포인터
 * @param     *pUELMANUALVAL 수동 위치 산출 정보의 데이터 포인터
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-29, 오후 8:44
 * @warning
 */
void CELEmitterMergeMngr::UpdatePEInfo( SRxAETData *pAETData, SELAETDATA_EXT *pAETExtData, CELThreat *pTheAETThreat, SRxABTData *pManABTData )
{
    int nC=0;
    //bool bRet;
    CELThreat *pTheABTThreat, *pTheMajorABTThreat;

    SRxABTData *pABTData=NULL;
    SELABTDATA_EXT *pABTExtData=NULL;

    double dPECoVar[4];
    //double dTargetLocDeg[4], dEEPData[4];

    // CASE 2.2 : 위치 산출 변경 업데이트 처리
    // 빔 갯수가 1개일 때는 빔의 위치 산출 정보로 업데이트
    if( pAETData->uiCoABT == _spOne ) {
        pTheABTThreat = GetHeaderThreat( pTheAETThreat );
        if( pTheABTThreat != NULL ) {
            pABTData = GetABTData( pTheABTThreat->m_nIndex );
            pABTExtData = GetABTExtData( pTheABTThreat->m_nIndex );

            // ABT의 위치 산출 정보를 AET의 위치 산출 정보에 대입
            if( pABTData != NULL ) {
                //memcpy( & pAETData->peInfo, & pABTData->peInfo, sizeof( STR_POSITION_ESTIMATION ) );
                pAETData->iPEValid = (int) pABTExtData->enValid;
                pAETData->fLatitude = pABTData->fLongitude;
                pAETData->fLatitude = pABTData->fLatitude;
                //pAETData->peInfo.iAltidude = pABTData->peInfo.iAltidude;
                pAETData->fCEP = pABTData->fCEP;
                pAETData->fMajorAxis = pABTData->fMajorAxis;
                pAETData->fMinorAxis = pABTData->fMinorAxis;
                pAETData->fTheta = pABTData->fTheta;
                pAETData->fDistanceErrorOfThreat = pABTData->fDistanceErrorOfThreat;
            }
        }
        else {

        }

    }
    else {
        float fmaxMajor;

        std::vector<STR_LOBS> *pVecLOB=NULL;

        // AET 중에서 빔이 유효한 정보만 갖고와서 위치 산출을 수행한다.
        fmaxMajor = (float) 99999999.; //_spZero;
        pTheABTThreat = GetHeaderThreat( pTheAETThreat );
        pTheMajorABTThreat = pTheABTThreat;

        // todo : 빔 중에서 가장 많은 LOB 중에서 위치 산출을 수행
        //pVecLOB = & m_pVecLOBs[ pTheABTThreat->m_nIndex ];
        while( pTheABTThreat != NULL ) { //#FA_C_PotentialUnboundedLoop_T1
            pVecLOB = & m_pVecLOBs[ pTheABTThreat->m_nIndex ];
            pABTData = GetABTData( pTheABTThreat->m_nIndex );
            pABTExtData = GetABTExtData( pTheABTThreat->m_nIndex );

            if( ( pABTData != NULL ) && ( pABTData->iValidity == 1 ) ) {
                if( nC >= _spOne ) {
                    //bRet = ST_PEA->CalculateTwoEclippse( dTargetLocDeg, dEEPData, & pABTData->peInfo, pABTExtData->dPECoVar, dPECoVar );
                    //if( bRet == true ) {
                        // bRet = ST_PEA->CalculateCovToEEP( dTargetLocDeg, dEEPData, pPEInfo, pABTExtData->dPECoVar, dPECoVar );
                    //}

                }

                //if( pABTData->uiCoLOB > maxLOB ) {
                if( pABTData->fCEP < fmaxMajor  ) {
                    pVecLOB = & m_pVecLOBs[ pTheABTThreat->m_nIndex ];
                    fmaxMajor = pABTData->fCEP;

                    pTheMajorABTThreat = pTheABTThreat;
                }

                ++ nC;

                memcpy( dPECoVar, pABTExtData->dPECoVar, sizeof(pABTExtData->dPECoVar) );
            }

            pTheABTThreat = GetNextThreat( pTheABTThreat );
        }

        /*! \todo   주 빔(LOB개수가 많은 것으로) 의 위치 산출 정보로 방사체 위치 산출을 결정
            \author 조철희 (churlhee.jo@lignex1.com)
            \date 	2018-02-08 16:45:30
        */
        if( fmaxMajor != _spZero ) {
            if( pTheMajorABTThreat != NULL ) {
                pABTData = GetABTData( pTheMajorABTThreat->m_nIndex );

                // ST_PEA->RunPositionEstimation( & pAETData->peInfo, NULL, pVecLOB );
                pAETData->iPEValid = pABTExtData->enValid;
                pAETData->fLongitude = pABTData->fLongitude;
                pAETData->fLatitude = pABTData->fLatitude;
                //pAETData->peInfo.iAltidude = pABTData->peInfo.iAltidude;
                pAETData->fCEP = pABTData->fCEP;
                pAETData->fMajorAxis = pABTData->fMajorAxis;
                pAETData->fMinorAxis = pABTData->fMinorAxis;
                pAETData->fTheta = pABTData->fTheta;
                pAETData->fDistanceErrorOfThreat = pABTData->fDistanceErrorOfThreat;
            }

        }

    }

}

/**
 * @brief     방사체 정보의 식별 정보를 변경한다.
 * @param     *pAETData 방사체 정보의 데이터 포인터
 * @param     *pAETExtData 방사체 추가 정보의 데이터 포인터
 * @param     *pTheAETThreat 방사체 정보의 데이터 포인터
 * @param     *pSELEmitterEdited 수동 변경 정보
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-04-04, 오후 1:00
 * @warning
 */
void CELEmitterMergeMngr::UpdateIDInfo( SRxAETData *pAETData, SELAETDATA_EXT *pAETExtData, CELThreat *pTheAETThreat )
{
    //STR_CEDEOBID_INFO *pIDInfo;
    //UELMANUALVAL *pUELMANUALVAL;

    //SThreat *pSThreat;
    CString strPINNum;

    // CASE 1 : 변경 무시 처리
    if( /* pSELEmitterEdited == NULL && */ pAETExtData->xMannualEdited.x.idInfo == (UINT) 1 ) {
        return;
    }
    else {
// 		if( pSELEmitterEdited != NULL ) {
// 			pUELMANUALVAL = & pSELEmitterEdited->userManual;
// 		}
//
        // CASE 2.1 : 신호 식별 수동 변경
        if( false /* pSELEmitterEdited != NULL && pUELMANUALVAL->x.idInfo == (UINT) 1 */ ) {
            // PIN 번호 변경
// 			pAETExtData->iPinNumber = pSELEmitterEdited->iPinNumber;
//
// 			m_theIdentifyAlg.SetIDResult( pAETData, pAETExtData, NULL, E_EL_LIB_TYPE_PRACTICAL, E_EL_LIB_TYPE_PRACTICAL, true );
//
// 			// PIN 번호 변경함에 따라 위협 번호 및 장비 인덱스 변경
// 			pIDInfo = & pAETData->idInfo;
//
// 			strPINNum.Format( "%d", pAETExtData->iPinNumber );
// 			pSThreat = GP_MNGR_CED_LIB2->RTGetThreatDataFromPINNum( & strPINNum, m_pSEnvironVariable->eEOBDefaultLibType );
//
// 			if( pSThreat != NULL ) {
// 				pIDInfo->nThreatIndex = pSThreat->nThreatIndex;
//
// 				// 장비가 있는지를 검사해서 그 중에서 제일 처음 장비로 매긴다.
// 				if( pSThreat->vecDevice.size() >= _spOne ) {
// 					pIDInfo->nDeviceIndex = pSThreat->vecDevice.front().nDeviceIndex;
// 				}
// 				else {
// 					pIDInfo->nDeviceIndex = 0;
// 				}
// 			}
// 			else {
// 				GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_MSG, E_WARNING_NONE, enumGMEO_DEVICE, enumGMEI_DEVICE, "PIN 번호(%d) 가 존조재하지 않습니다.", pSELEmitterEdited->iPinNumber );
// 			}
//
// 			memcpy( pAETExtData->szELNOT, pSELEmitterEdited->szELNOT, sizeof(char) * _MAX_ELNOT_STRING_SIZE_ );
        }
        else {
            IdentifyAET( pAETData, pAETExtData, pTheAETThreat );

        }
    }

}

/**
 * @brief     빔 위시 산출, ABT 들에 대해서 위치 산출을 수행하여 그 결과를 업데이트 한다.
 * @param     *pABTData 빔 정보의 데이터 포인터
 * @param     *pABTExtData 빔 추가 정보의 데이터 포인터
 * @param     bLOiValidityApplied LOB 적용 플레스
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-15, 오후 2:30
 * @warning
 */
void CELEmitterMergeMngr::UpdatePEInfo( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData, int nIndex, bool bLOiValidityApplied, bool bRunCluster, bool bRunPE )
{
    SELPE_RESULT stResult;
    std::vector<STR_LOBS> *pVecLOBs;

    pVecLOBs = & m_pVecLOBs[nIndex];

    // 수신한 LOB 추가
    AppendLOBs( nIndex );

    if( bLOiValidityApplied == true ) {
        // 위치 산출 호출
        m_thePositionEstimation.RunPositionEstimation( & stResult, pABTData, pABTExtData, pVecLOBs );

        // 빔 유효성 갯수 업데이트
        pABTExtData->nCoBeamValidity = (int) pVecLOBs->size();

    }
    else {
        PlatformCode::EnumPlatformCode enPlatform;
        //STR_POSITION_ESTIMATION backupPEInfo;
        
        // 빔 유효성 갯수 클리어
        pABTExtData->nCoBeamValidity = 0;

        // 현재 업데이트할 LOB가 방탐 유효성이 있을 때만 추가 위치 산출을 수행함.
        enPlatform = CheckPlatform( pABTData );
        if( m_LOBDataExt.aetAnal.iBeamValidity == 1 && enPlatform != PlatformCode::enumAir ) {

            if( true || ( bRunPE == true && NeedToRunPositionEstimation( pABTData, pABTExtData, pVecLOBs ) == true ) ) {
                m_thePositionEstimation.RunPositionEstimation( & stResult, pABTData, pABTExtData, pVecLOBs );
                if( stResult.bResult == true ) {
                    pABTData->iPEValid = _spOne;
                    pABTData->fLatitude = (float) stResult.dLatitude;
                    pABTData->fLongitude = (float) stResult.dLongitude;
                    pABTData->fMajorAxis = (float) stResult.dEEP_major_axis;		// dEEPData[0] * 2.0;
                    pABTData->fMinorAxis = (float) stResult.dEEP_minor_axis;			// dEEPData[1] * 2.0;
                    pABTData->fTheta = (float) stResult.dEEP_theta;					// M2Map( (int) ( dEEPData[2]*10. ) );
                    pABTData->fCEP = (float) stResult.dCEP_error;

                    // 위,경도 값 유효성 체크
#ifdef _ELINT_
                    if( ( pABTData->fLatitude > 40.0 || pABTData->fLatitude < 33 ) ||
                            ( pABTData->fLongitude > 135. || pABTData->fLongitude < 120. ) ||
                            ( 0 == _finite( pABTData->fLatitude ) ) ||
                            ( 0 == _finite( pABTData->fLongitude ) ) ) { //DTEC_Else
                        pABTData->iPEValid = _spZero;
                        pABTData->fCEP = -1.0;
                    }
#endif

                    PushPEInfoOfABTData( pABTExtData, pABTData );
                }
                else {
                    pABTData->iPEValid = _spZero;
                    pABTData->fCEP = -1.0;
                }

            }
            //LogPrint("\n========================================== RunPositionEstimation 시간 : %d ms", (int)((GetTickCount() - dwTime) / 1));

            // 빔 유효성 갯수 업데이트
            pABTExtData->nCoBeamValidity = (int) pVecLOBs->size();
        }

        //pABTData->peInfo.iAltidude = m_pLOBData->iAltitude;
    }

}

/**
 * @brief CELEmitterMergeMngr::CheckPlatform
 * @param pABTData
 * @return
 */
PlatformCode::EnumPlatformCode CELEmitterMergeMngr::CheckPlatform( SRxABTData *pABTData )
{
    return m_pIdentifyAlg->GetPlatformFromRadarMode( pABTData->iRadarModeIndex );

}

/**
 * @brief CELEmitterMergeMngr::PushPEInfoOfABTData
 * @param pABTExtData
 * @param pABTData
 */
void CELEmitterMergeMngr::PushPEInfoOfABTData( SELABTDATA_EXT *pABTExtData, SRxABTData *pABTData )
{
    double dEasting, dNorthing;

    if( pABTData->iPEValid == _spOne ) {
#if defined(_TM_POSITION_)
        m_theGeoCoordConv.SetSrcType(kWgs84, kGeographic );
        m_theGeoCoordConv.SetDstType(kWgs84, kTmWest );
        //m_theGeoCoordConv.Conv( *pLong, *pLat, *pX, *pY );
        m_theGeoCoordConv.Conv( (double) pABTData->fLongitude, (double) pABTData->fLatitude, dEasting, dNorthing );
#elif defined(_ENU_POSITION_)

#else
        LatLonToUTMXY( pABTData->fLatitude, pABTData->fLongitude, UTM_ZONE, dEasting, dNorthing ); 
#endif

        pABTExtData->dLatitude[ pABTExtData->uiPE ] = (double) pABTData->fLatitude;
        pABTExtData->dLongitude[ pABTExtData->uiPE ] = (double) pABTData->fLongitude;

        pABTExtData->dEasting[ pABTExtData->uiPE ] = dEasting;
        pABTExtData->dNorthing[ pABTExtData->uiPE ] = dNorthing;

        if( pABTExtData->uiPE >= (MAX_OF_LOBS_PE-1) ) {
            pABTExtData->bFullOfPE = true;
        }
        ++ pABTExtData->uiPE;
        pABTExtData->uiPE = pABTExtData->uiPE % MAX_OF_LOBS_PE;

        // printf( "\n pABTExtData->uiPE[%d]" , pABTExtData->uiPE );
    }

}

/**
 * @brief     위치 산출하기 위해 LOB 데이터를 추가한다.
 * @param     *pLiLOB LOB 데이터 포인터
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-30, 오전 11:02
 * @warning
 */
void CELEmitterMergeMngr::AppendLOBs( int nIndex, enELControlLOB enControlLOB )
{
    //BOOL bRet1, bRet2;

    if( nIndex >= 0 && nIndex < TOTAL_ITEMS_OF_THREAT_NODE ) {
        if( enControlLOB == REMOVE_LOB ) {
            RemoveLOBs( & m_pVecLOBs[nIndex] );

        }
        else if( ( m_LOBDataExt.aetAnal.iBeamValidity != E_INVALID ) ) {
            // 이동하는 타겟에 대해서는 최근 LOB로 위치 산출을 사용한다.
            if( m_pABTExtData->enPlatform == enPlatform_AIR || m_pABTExtData->enPlatform == enPlatform_MOVING_GROUND ) {
                // 자신의 방위/위/경도 값 추가
                AppendLOBs( & m_pVecLOBs[nIndex], false );
            }
            // 위협 식별한 LOB에서 가장 가까운 LOB들을 취해서 위치 산출을 적용한다.
            else {
                AppendLOBs( & m_pVecLOBs[nIndex], true );
            }

        }
        else {
            LogPrint( "LOB를 추가하지 못했습니다.", nIndex );
        }
    }
    else {
        LogPrint( "인덱스[%d]가 잘못되어 LOB 버퍼에 정보를 저장하지 못했습니다.", nIndex );
    }

}
//
// /**
//  * @brief     RemoveLOBs
//  * @param     SRxLOBData * pSRxLOBData
//  * @param     SRxLOBDataGroup * pSRxLOBDataGroup
//  * @return    void
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2017-11-03, 오전 10:21
//  * @warning
//  */
// void CELEmitterMergeMngr::RemoveLOBs( SRxLOBData *pSRxLOBData, SRxLOBDataGroup *pSRxLOBDataGroup )
// {
// 	CELThreat *pTheABTThreat;
//
// 	m_pLOBData = pSRxLOBData;
// 	m_pLOBData = pSRxLOBDataGroup;
//
// 	pTheABTThreat = m_pTheThreatRoot->Find( pSRxLOBDataGroup->uiAETID, pSRxLOBDataGroup->uiABTID_LinkNum );
//
// 	if( pTheABTThreat != NULL ) {
// 		AppendLOBs( pTheABTThreat->m_nIndex, REMOVE_LOB );
// 	}
// 	else {
// 		GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_MSG, E_WARNING_CRITICAL, enumGMEO_DEVICE, enumGMEI_DEVICE, "삭제할 LOB(%d,%d)가 존재하지 않아서 LOB 삭제 실패했습니다.", pSRxLOBDataGroup->uiAETID, pSRxLOBDataGroup->uiABTID_LinkNum );
// 	}
//
// }

/**
 * @brief     RemoveLOBs
 * @param     int nIndex
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-11-03, 오전 10:35
 * @warning
 */
void CELEmitterMergeMngr::RemoveLOBs( std::vector<STR_LOBS> *pVecLOBs )
{
    int nSize;

    std::vector<STR_LOBS>::iterator iter;

    nSize = (int) pVecLOBs->size();
    for( iter=pVecLOBs->begin() ; iter != pVecLOBs->end() ; ++iter ) {
        if( (*iter).uiLOBID == (int) m_pLOBData->uiLOBID ) {
            iter = pVecLOBs->erase( iter );
            break;
        }

   }

    if( iter != pVecLOBs->end() ) {
        LogPrint( "삭제할 LOB[%d]를 찾지 못했습니다.", m_pLOBData->uiLOBID );
    }

}

/**
 * @brief     AppendLOBs
 * @param     std::vector<STR_LOBS>* pVecLOBs
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-07-07, 오후 1:32
 * @warning
 */
void CELEmitterMergeMngr::AppendLOBs( std::vector<STR_LOBS> *pVecLOBs, bool bNormalMethod )
{
    STR_LOBS stLOB=STR_LOBS();

    if( bNormalMethod == true || m_pABTData == NULL) {
        // 필터링 체크
        if( pVecLOBs->size() >= MAX_OF_LOBS ) {
            pVecLOBs->erase( pVecLOBs->begin() );

        }

        // 자신의 방위/위/경도 값 추가
        stLOB.fDoa = m_pLOBData->fDOAMean;
        stLOB.fLatitude = (float) m_pLOBData->fRadarLatitude;
        stLOB.fLongitude = (float) m_pLOBData->fRadarLongitude;
        stLOB.uiLOBID = (int) m_pLOBData->uiLOBID;
        //stLOB.iCollectorID = (int) m_pLOBData->iCollectorID;

        pVecLOBs->push_back( stLOB );
    }
    else {
        UINT i, iIndex=(UINT) -1;
        UINT uiSize=pVecLOBs->size();
        std::vector<STR_LOBS>::iterator iter;

        SThreat *pThreat;

        float fTheta, fDiffTheta, fMaxTheta=-1.0;

        if( m_pABTData->iPEValid == _spOne ) {
            pThreat = m_pIdentifyAlg->GetThreatData( m_pABTData->iThreatIndex );
            fTheta = (float) m_theInverseMethod.GCAzimuth( m_pLOBData->fRadarLatitude, m_pLOBData->fRadarLongitude, (double) m_pABTData->fLatitude, (double) m_pABTData->fLongitude );

            for( i=-1, iter=pVecLOBs->begin() ; iter != pVecLOBs->end() ; ++iter, ++i ) {
                if( /* ppVecLOBs->iCollectorID == m_pLOBData->iCollectorID */ true ) {
                    if( CompAoaDiff( fTheta, (*iter).fDoa, 2.0 ) == false ) {
                        fDiffTheta = AoaDiff( fTheta, (*iter).fDoa );
                        if( iIndex == (UINT) (-1) || fMaxTheta < fDiffTheta ) {
                            iIndex = i;
                            fMaxTheta = fDiffTheta;
                        }
                    }
                }
            }
        }

        if( iIndex != -1 ) {
            pVecLOBs->erase( pVecLOBs->begin()+iIndex );
        }
        else if( pVecLOBs->size() >= MAX_OF_LOBS ) {
            pVecLOBs->erase( pVecLOBs->begin() );
        }

        // 자신의 방위/위/경도 값 추가
        stLOB.fDoa = m_pLOBData->fDOAMean;
        stLOB.fLatitude = (float) m_pLOBData->fRadarLatitude;
        stLOB.fLongitude = (float) m_pLOBData->fRadarLongitude;
        stLOB.uiLOBID = (int) m_pLOBData->uiLOBID;
        //stLOB.iCollectorID = (int) m_pLOBData->iCollectorID;

        pVecLOBs->push_back( stLOB );

    }

}

/**
 * @brief     ClearLOBs
 * @param     int nIndex
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-07-07, 오후 1:08
 * @warning
 */
void CELEmitterMergeMngr::ClearLOBs( int nIndex )
{
    if( nIndex >= 0 && nIndex < TOTAL_ITEMS_OF_THREAT_NODE ) {
        //m_pVecLOBs[nIndex].clear();
        m_pVecLOBs[nIndex].erase( m_pVecLOBs[nIndex].begin(), m_pVecLOBs[nIndex].end() );

    }
    else {
        LogPrint( "ClearLOBs 함수의 인덱스[%d]가 잘못되어 LOB 버퍼 클리어를 수행하지 못합니다.", nIndex );
    }
}

/**
 * @brief     빔 정보를 근거로 방사체 정보의 식별 정보를 변경한다.
 * @param     *pABTData 빔 정보의 데이터 포인터
 * @param     *pABTExtData 빔 추가 정보의 데이터 포인터
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-14, 오후 6:00
 * @warning
 */
void CELEmitterMergeMngr::UpdateIDInfo( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
{
    //CELThreat *pTheAETThreat;
    //SELAETDATA_EXT *pAETExtData;

    STR_CEDEOBID_INFO *pIDInfo;

    pIDInfo = & pABTExtData->idInfo;

    //pTheAETThreat = m_pTheThreatRoot->Find( pABTData->uiAETID );
    //pAETExtData = GetAETExtData( pTheAETThreat->m_nIndex );

    memcpy( pIDInfo, & m_ABTDataExt.aetAnal.idInfo, sizeof( STR_CEDEOBID_INFO ) );

}

// /**
//  * @brief     빔 정보를 근거로 방사체 정보의 인트라 정보를 변경한다.
//  * @param     *pABTData 빔 정보의 데이터 포인터
//  * @param     *pABTExtData 빔 추가 정보의 데이터 포인터
//  * @return    리턴값 없음
//
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-03-14, 오후 5:31
//  * @warning
//  */
// void CELEmitterMergeMngr::UpdateIntraInfo( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
// {
// 	STR_INTRA_INFO *pIntraInfo;
//
// 	pIntraInfo = & pABTData->intraInfo;
//
// 	switch( m_pLOBData->iMOPType ) {
// 	case E_AET_MOP_UNK :
// 		// ABT에 있던 데이터 그대로 나두면 됨.
// 		break;
//
// 	case E_AET_MOP_NM :
// 	case E_AET_MOP_PSK :
// 	case E_AET_MOP_FSK :
// 	case E_AET_MOP_LFM :
// 	case E_AET_MOP_NLFM :
// 		if( pABTData->intraInfo.iType == E_AET_MOP_UNK ) {
// 			pIntraInfo->iType = m_pLOBData->iMOPType;
// 			pIntraInfo->iDetailType = m_pLOBData->iDetailMOPType;
// 			pIntraInfo->fFreqMax = m_pLOBData->iMOPMaxFreq;
// 			pIntraInfo->fFreqMin = m_pLOBData->iMOPMinFreq;
// 			pIntraInfo->fFreqMean = m_pLOBData->iMOPMeanFreq;
// 			pIntraInfo->fFreqMaxDeviation = m_pLOBData->iMOPFreqDeviation;
// 			pIntraInfo->fFreqMinDeviation = m_pLOBData->iMOPFreqDeviation;
// 			pIntraInfo->fFreqMeanDeviation = m_pLOBData->iMOPFreqDeviation;
// 		}
// 		else {
// 			pIntraInfo->iType = m_pLOBData->iMOPType;
// 			pIntraInfo->iDetailType = m_pLOBData->iDetailMOPType;
// 			pIntraInfo->fFreqMax = _max( m_pLOBData->iMOPMaxFreq, pIntraInfo->fFreqMax );
// 			pIntraInfo->fFreqMin = _min( m_pLOBData->iMOPMinFreq, pIntraInfo->fFreqMin );
// 			pIntraInfo->fFreqMean = IMUL( 1000000., CalcMean( (float) (m_pLOBData->iMOPMeanFreq/1000000.), m_pLOBData->iNumOfIQ, (float) (pIntraInfo->fFreqMean/1000000.), pABTExtData->nCoTotalIQ ) );
// 			pIntraInfo->fFreqMaxDeviation = _max( pIntraInfo->fFreqMaxDeviation, m_pLOBData->iMOPFreqDeviation );
// 			pIntraInfo->fFreqMinDeviation = _min( pIntraInfo->fFreqMinDeviation, m_pLOBData->iMOPFreqDeviation );
// 			pIntraInfo->fFreqMeanDeviation = IMUL( 1000000., CalcMean( (float) (m_pLOBData->iMOPFreqDeviation/1000000.), m_pLOBData->iNumOfIQ, (float) (pIntraInfo->fFreqMeanDeviation/1000000.), pABTExtData->nCoTotalIQ ) );
// 		}
// 		break;
//
// 	default :
// 		break;
// 	}
//
// }

/**
* @brief     빔 정보를 근거로 방사체 정보의 스캔 정보를 변경한다.
* @param     *pABTData 빔 정보의 데이터 포인터
* @param     *pABTExtData 빔 추가 정보의 데이터 포인터
* @return    리턴값 없음
* @author    조철희 (churlhee.jo@lignex1.com)
* @version   0.0.1
* @date      2016-03-14, 오후 5:03
* @warning
*/
void CELEmitterMergeMngr::UpdateScanInfo( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
{

    // 안테나 스캔 세부 정보
    switch( m_pLOBData->iScanType ) {
        case E_AET_SCAN_UNKNOWN :
            break;

        case E_AET_SCAN_CIRCULAR :
        case E_AET_SCAN_UNI_DIRECTIONAL :
        case E_AET_SCAN_BI_DIRECTIONAL :
        case E_AET_SCAN_CONICAL :
        case E_AET_SCAN_STEADY :
            if( pABTData->iScanType == E_AET_SCAN_UNKNOWN ) {
                pABTData->iScanType = m_pLOBData->iScanType;
                pABTData->fMeanScanPeriod = FDIV( ( pABTData->fMeanScanPeriod + m_pLOBData->fScanPeriod ), 2.0 );			// [usec]
                pABTData->fMaxScanPeriod = _max( pABTData->fMeanScanPeriod, m_pLOBData->fScanPeriod );			// [usec]
                pABTData->fMinScanPeriod = _min( pABTData->fMeanScanPeriod, m_pLOBData->fScanPeriod );
            }
            else if( pABTData->iScanType == m_pLOBData->iScanType ) {
                pABTData->iScanType = m_pLOBData->iScanType;
                pABTData->fMeanScanPeriod = FDIV( ( pABTData->fMeanScanPeriod + m_pLOBData->fScanPeriod ), 2.0 );			// [usec]
                pABTData->fMaxScanPeriod = _max( pABTData->fMeanScanPeriod, m_pLOBData->fScanPeriod );			// [usec]
                pABTData->fMinScanPeriod = _min( pABTData->fMeanScanPeriod, m_pLOBData->fScanPeriod );            }
            else {
                pABTData->iScanType = m_pLOBData->iScanType;
                pABTData->fMeanScanPeriod = FDIV( ( pABTData->fMeanScanPeriod + m_pLOBData->fScanPeriod ), 2.0 );			// [usec]
                pABTData->fMaxScanPeriod = _max( pABTData->fMeanScanPeriod, m_pLOBData->fScanPeriod );			// [usec]
                pABTData->fMinScanPeriod = _min( pABTData->fMeanScanPeriod, m_pLOBData->fScanPeriod );
            }
            break;

        default :
            //LogPrint( "스캔 형태 업데이트[%d-%d] 에러 입니다.", m_pLOBData->iScanType, pScanInfo->iType );
            break;
    }

}

/**
 * @brief     빔 정보를 근거로 방사체 정보의 신호세기 정보를 변경한다.
 * @param     *pAETData 방사체 정보의 데이터 포인터
 * @param     *pAETExtData 방사체 추가 정보의 데이터 포인터
 * @param     *pABTData 빔 정보의 데이터 포인터
 * @param     *pABTExtData 빔 추가 정보의 데이터 포인터
 * @param     *pUELMANUALVAL 사용자가 수동으로 변경하려는 데이터 포인터
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-17, 오후 3:01
 * @warning
 */
void CELEmitterMergeMngr::UpdatePAInfo( SRxAETData *pAETData, SELAETDATA_EXT *pAETExtData, SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
{
    if( pABTExtData != NULL ) {
        pAETData->fPAMax = _max( pAETData->fPAMax, pABTData->fPAMax );
        pAETData->fPAMin = _min( pAETData->fPAMin, pABTData->fPAMin );
        if( pAETData->uiCoABT == _spOne ) {
            pAETData->fPAMean = pABTData->fPAMean;
        }
        else {
            pAETData->fPAMean = CalcMean( pAETData->fPAMean, pAETExtData->nCoTotalPdw, pABTData->fPAMean, pABTData->uiTotalOfPDW );
        }

        //pAETData->fPADeviation = CalcDeviation( pAETData->paInfo.fDeviation, pAETExtData->nCoTotalPdw, pABTData->paInfo.fDeviation, pABTExtData->nCoTotalPdw );
        pAETData->fPADeviation = pAETData->fPAMax - pAETData->fPAMin;

    }

}

/**
 * @brief     LOB 정보를 근거로 방사체 정보의 신호세기 정보를 변경한다.
 * @param     *pABTData 빔 정보의 데이터 포인터
 * @param     *pABTExtData 빔 추가 정보의 데이터 포인터
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-14, 오후 5:02
 * @warning
 */
void CELEmitterMergeMngr::UpdatePAInfo( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
{
    //STR_FREQ_PRI_PW_PA_INFO *pPAInfo;

    //pPAInfo = & pABTData->paInfo;

    pABTData->fPAMax = _max( pABTData->fPAMax, m_pLOBData->fPAMax );
    pABTData->fPAMin = _min( pABTData->fPAMin, m_pLOBData->fPAMin );
    pABTData->fPAMean = CalcMean( pABTData->fPAMean, pABTData->uiTotalOfPDW, m_pLOBData->fPAMean, m_pLOBData->iNumOfPDW );
    //pPAInfo->fDeviation = CalcDeviation( pPAInfo->fDeviation, pABTExtData->nCoTotalPdw, m_pLOBData->iPWDeviation, m_pLOBData->iNumOfPDW );

    pABTData->fPADeviation = pABTData->fPAMax - pABTData->fPAMin;

}

/**
 * @brief     빔 정보를 근거로 방사체 정보의 펄스폭 정보를 변경한다.
 * @param     *pAETData 방사체 정보의 데이터 포인터
 * @param     *pAETExtData 방사체 추가 정보의 데이터 포인터
 * @param     *pABTData 빔 정보의 데이터 포인터
 * @param     *pABTExtData 빔 추가 정보의 데이터 포인터
 * @param     *pUELMANUALVAL 사용자가 수동으로 변경하려는 데이터 포인터
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-17, 오후 2:48
 * @warning
 */
void CELEmitterMergeMngr::UpdatePWInfo( SRxAETData *pAETData, SELAETDATA_EXT *pAETExtData, SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
{
    if( pABTExtData != NULL ) {
        pAETData->fPWMax = _max( pAETData->fPWMax, pABTData->fPWMax );
        pAETData->fPWMin = _min( pAETData->fPWMin, pABTData->fPWMin );
        if( pAETData->uiCoABT == _spOne ) {
            pAETData->fPWMean = pABTData->fPWMean;
        }
        else {
            pAETData->fPWMean = CalcMean( pAETData->fPWMean, pABTData->uiTotalOfPDW, pABTData->fPWMean, pABTData->uiTotalOfPDW );
        }

        pAETData->fPWDeviation = pAETData->fPWMax - pAETData->fPWMin;
    }

}

/**
 * @brief     LOB 정보를 근거로 빔 정보의 펄스폭 정보를 변경한다.
 * @param     *pABTData 빔 정보의 데이터 포인터
 * @param     *pABTExtData 빔 추가 정보의 데이터 포인터
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-14, 오후 4:59
 * @warning
 */
void CELEmitterMergeMngr::UpdatePWInfo( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
{
    //STR_FREQ_PRI_PW_PA_INFO *pPWInfo;

    //pPWInfo = & pABTData->pwInfo;

    pABTData->fPWMax = _max( pABTData->fPWMax, m_pLOBData->fPWMax );
    pABTData->fPWMin = _min( pABTData->fPWMin, m_pLOBData->fPWMin );
    pABTData->fPWMean = CalcMean( pABTData->fPWMean, pABTData->uiTotalOfPDW, m_pLOBData->fPWMean, m_pLOBData->iNumOfPDW );

    pABTData->fPWDeviation = pABTData->fPWMax - pABTData->fPWMin;

}

/**
 * @brief     ABT 정보를 근거로 방사체 정보를 변경한다.
 * @param     *pAETData 방사체 정보의 데이터 포인터
 * @param     *pAETExtData 방사체 추가 정보의 데이터 포인터
 * @param     *pABTData 빔 정보의 데이터 포인터
 * @param     *pABTExtData 빔 추가 정보의 데이터 포인터
 * @param     *pUELMANUALVAL 사용자가 수동으로 변경하려는 데이터 포인터
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-17, 오후 2:47
 * @warning
 */
void CELEmitterMergeMngr::UpdatePRIInfo( SRxAETData *pAETData, SELAETDATA_EXT *pAETExtData, SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
{
    if( pABTExtData != NULL ) {
        pAETData->fPRIMax = _max( pAETData->fPRIMax, pABTData->fPRIMax );
        pAETData->fPRIMin = _min( pAETData->fPRIMin, pABTData->fPRIMin );
        if( pAETData->uiCoABT == _spOne ) {
            pAETData->fPRIMean = pABTData->fPRIMean;
        }
        else {
            pAETData->fPRIMean = CalcMean( pAETData->fPRIMean, pAETExtData->nCoTotalPdw, pABTData->fPRIMean, pABTData->uiTotalOfPDW );
        }
        //pAETData->priInfo.fDeviation = CalcDeviation( pAETData->priInfo.fDeviation, pAETExtData->nCoTotalPdw, pABTData->priInfo.fDeviation, pABTExtData->nCoTotalPdw );
        pAETData->fPRIDeviation = pAETData->fPRIMax - pAETData->fPRIMin;
    }
}

/**
 * @brief     ABT 정보를 근거로 PRI 정보를 변경한다.
 * @param     *pABTData 빔 정보의 데이터 포인터
 * @param     *pABTExtData 빔 추가 정보의 데이터 포인터
 * @return    리턴값 없음

 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-14, 오후 2:18
 * @warning
 */
void CELEmitterMergeMngr::UpdatePRIInfo( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
{
    //STR_FREQ_PRI_DINFO *pPRIDInfo;
    //STR_FREQ_PRI_PW_PA_INFO *pPRIInfo;

    //pPRIInfo = & pABTData->priInfo;
    //pPRIDInfo = & pABTData->priDInfo;

    // PRI 세부 정보
    switch( m_pLOBData->iPRIType ) {
    case E_AET_PRI_FIXED :
        pABTData->iPRIType = m_pLOBData->iPRIType;
        pABTData->iPRIPatternType = E_AET_FREQ_PRI_UNKNOWN;
        //pPRIDInfo->iIsPeriod = false;
        //pPRIDInfo->iChangePeriod = 0;
        pABTData->fPRIPatternPeriodMean = 0;
        pABTData->fPRIPatternPeriodMin = 0;
        pABTData->fPRIPatternPeriodMax = 0;

        if( m_pLOBData->iPRIPositionCount > 0 ) {
            pABTData->iPRIPositionCount = m_pLOBData->iPRIPositionCount;
            //pPRIDInfo->iElementCount = m_pLOBData->iPRIElementCount;
            memcpy( pABTData->fPRISeq, m_pLOBData->fPRISeq, sizeof(m_pLOBData->fPRISeq) );
        }
        break;

    case E_AET_PRI_JITTER :
        if( pABTData->iPRIType == E_AET_PRI_JITTER ) {
            pABTData->iPRIType = m_pLOBData->iPRIType;
            pABTData->iPRIPatternType = m_pLOBData->iPRIPatternType;
            //pPRIDInfo->iIsPeriod = m_pLOBData->iIsPRIPeriod;
            //pPRIDInfo->iChangePeriod = m_pLOBData->iPRIChangePeriod;
            pABTData->fPRIPatternPeriodMin = _min( m_pLOBData->fPRIPatternPeriod, pABTData->fPRIPatternPeriodMin );
            pABTData->fPRIPatternPeriodMax = _max( m_pLOBData->fPRIPatternPeriod, pABTData->fPRIPatternPeriodMax );;
            pABTData->fPRIPatternPeriodMean = m_pLOBData->fPRIPatternPeriod;
            pABTData->iPRIPositionCount = m_pLOBData->iPRIPositionCount;
            //pPRIDInfo->iElementCount = m_pLOBData->iPRIElementCount;
            memcpy( pABTData->fPRISeq, m_pLOBData->fPRISeq, sizeof(m_pLOBData->fPRISeq) );
        }
        else if( pABTData->iPRIType == E_AET_PRI_STAGGER ) {
            pABTData->iPRIType = E_AET_PRI_STAGGER;
        }
        else if( pABTData->iPRIType == E_AET_PRI_PATTERN ) {
            pABTData->iPRIType = E_AET_PRI_PATTERN;
        }
        else { //DTEC_Else
            LogPrint( "PRI 형태 업데이트[%d-%d] 에러 입니다.", m_pLOBData->iPRIType, pABTData->iPRIType );
        }
        break;

    case E_AET_PRI_DWELL_SWITCH :
        pABTData->iPRIType = m_pLOBData->iPRIType;
        pABTData->iPRIPatternType = m_pLOBData->iPRIPatternType;
        //pPRIDInfo->iIsPeriod = max( m_pLOBData->iIsPRIPeriod, pPRIDInfo->iIsPeriod );
        //pPRIDInfo->iChangePeriod = m_pLOBData->fPRIPatternPeriod;
        pABTData->fPRIPatternPeriodMin = _min( pABTData->fPRIPatternPeriodMin, m_pLOBData->fPRIPatternPeriod );
        pABTData->fPRIPatternPeriodMax = _max( pABTData->fPRIPatternPeriodMax, m_pLOBData->fPRIPatternPeriod );
        pABTData->fPRIPatternPeriodMean = CalcMean( pABTData->fPRIPatternPeriodMean, pABTData->uiTotalOfPDW, m_pLOBData->fPRIPatternPeriod, m_pLOBData->iNumOfPDW );
        pABTData->iPRIPositionCount = max( pABTData->iPRIPositionCount, m_pLOBData->iPRIPositionCount );
        //pPRIDInfo->iElementCount = max( pPRIDInfo->iElementCount, m_pLOBData->iPRIElementCount );
        if( pABTData->iPRIPositionCount <= m_pLOBData->iPRIPositionCount ) {
            //CalcPositionMean( pPRIDInfo->iSeq, pABTExtData->nCoTotalPdw, m_pLOBData->iPRISeq, m_pLOBData->iNumOfPDW, pPRIDInfo->iPositionCount );
            memcpy( pABTData->fPRISeq, m_pLOBData->fPRISeq, sizeof(pABTData->fPRISeq) );
        }
        break;

    case E_AET_PRI_STAGGER :
        if( pABTData->iPRIType == E_AET_PRI_STAGGER ) {
            pABTData->iPRIType = m_pLOBData->iPRIType;
            pABTData->iPRIPatternType = m_pLOBData->iPRIPatternType;
            //pPRIDInfo->iIsPeriod = m_pLOBData->iIsPRIPeriod;
            //pPRIDInfo->iChangePeriod = m_pLOBData->iPRIChangePeriod;
            pABTData->fPRIPatternPeriodMin = _min( pABTData->fPRIPatternPeriodMin, m_pLOBData->fPRIPatternPeriod );
            pABTData->fPRIPatternPeriodMax = _max( pABTData->fPRIPatternPeriodMax, m_pLOBData->fPRIPatternPeriod );
            pABTData->fPRIPatternPeriodMean = CalcMean( pABTData->fPRIPatternPeriodMean, pABTData->uiTotalOfPDW, m_pLOBData->fPRIPatternPeriod, m_pLOBData->iNumOfPDW );
            pABTData->iPRIPositionCount = m_pLOBData->iPRIPositionCount;
            //pPRIDInfo->iElementCount = m_pLOBData->iPRIElementCount;
            // CalcPositionMean( pPRIDInfo->iSeq, pABTExtData->nCoTotalPdw, m_pLOBData->iPRISeq, m_pLOBData->iNumOfPDW, pPRIDInfo->iPositionCount );
            memcpy( pABTData->fPRISeq, m_pLOBData->fPRISeq, sizeof(pABTData->fPRISeq) );
        }
        else if( pABTData->iPRIType == E_AET_PRI_JITTER ) {
            pABTData->iPRIType = m_pLOBData->iPRIType;
            pABTData->iPRIPatternType = m_pLOBData->iPRIPatternType;
            //pPRIDInfo->iIsPeriod = m_pLOBData->iIsPRIPeriod;
            //pPRIDInfo->iChangePeriod = m_pLOBData->iPRIChangePeriod;
            pABTData->fPRIPatternPeriodMin = _min( pABTData->fPRIPatternPeriodMin, m_pLOBData->fPRIPatternPeriod );
            pABTData->fPRIPatternPeriodMax = _max( pABTData->fPRIPatternPeriodMax, m_pLOBData->fPRIPatternPeriod );
            pABTData->fPRIPatternPeriodMean = CalcMean( pABTData->fPRIPatternPeriodMean, pABTData->uiTotalOfPDW, m_pLOBData->fPRIPatternPeriod, m_pLOBData->iNumOfPDW );
            pABTData->iPRIPositionCount = m_pLOBData->iPRIPositionCount;
            //pPRIDInfo->iElementCount = m_pLOBData->iPRIElementCount;
            //CalcPositionMean( pPRIDInfo->iSeq, pABTExtData->nCoTotalPdw, m_pLOBData->iPRISeq, m_pLOBData->iNumOfPDW, pPRIDInfo->iPositionCount );
            memcpy( pABTData->fPRISeq, m_pLOBData->fPRISeq, sizeof(pABTData->fPRISeq) );
        }
        else { //DTEC_Else
            LogPrint( "PRI 형태 업데이트[%d-%d] 에러 입니다.", m_pLOBData->iPRIType, pABTData->iPRIType );
        }
        break;

    case E_AET_PRI_PATTERN :
        if( pABTData->iPRIType == E_AET_PRI_PATTERN ) {
            pABTData->iPRIType = m_pLOBData->iPRIType;
            pABTData->iPRIPatternType = m_pLOBData->iPRIPatternType;
            //pPRIDInfo->iIsPeriod = m_pLOBData->iIsPRIPeriod;
            //pPRIDInfo->iChangePeriod = m_pLOBData->iPRIChangePeriod;
            pABTData->fPRIPatternPeriodMin = _min( pABTData->fPRIPatternPeriodMin, m_pLOBData->fPRIPatternPeriod );
            pABTData->fPRIPatternPeriodMax = _max( pABTData->fPRIPatternPeriodMax, m_pLOBData->fPRIPatternPeriod );
            pABTData->fPRIPatternPeriodMean = CalcMean( pABTData->fPRIPatternPeriodMean, pABTData->uiTotalOfPDW, m_pLOBData->fPRIPatternPeriod, m_pLOBData->iNumOfPDW );
            pABTData->iPRIPositionCount = m_pLOBData->iPRIPositionCount;
            //pPRIDInfo->iElementCount = m_pLOBData->iPRIElementCount;
            memcpy( pABTData->fPRISeq, m_pLOBData->fPRISeq, sizeof(pABTData->fPRISeq) );
        }
        else if( pABTData->iPRIType == E_AET_PRI_JITTER ) {
            pABTData->iPRIType = E_AET_PRI_PATTERN;
            pABTData->iPRIPatternType = m_pLOBData->iPRIPatternType;
            //pPRIDInfo->iIsPeriod = m_pLOBData->iIsPRIPeriod;
            //pPRIDInfo->iChangePeriod = m_pLOBData->iPRIChangePeriod;
            pABTData->fPRIPatternPeriodMin = _min( pABTData->fPRIPatternPeriodMin, m_pLOBData->fPRIPatternPeriod );
            pABTData->fPRIPatternPeriodMax = _max( pABTData->fPRIPatternPeriodMax, m_pLOBData->fPRIPatternPeriod );
            pABTData->fPRIPatternPeriodMean = CalcMean( pABTData->fPRIPatternPeriodMean, pABTData->uiTotalOfPDW, m_pLOBData->fPRIPatternPeriod, m_pLOBData->iNumOfPDW );
            pABTData->iPRIPositionCount = m_pLOBData->iPRIPositionCount;
            //pPRIDInfo->iElementCount = m_pLOBData->iPRIElementCount;
            memcpy( pABTData->fPRISeq, m_pLOBData->fPRISeq, sizeof(pABTData->fPRISeq) );
        }
        else { //DTEC_Else
            LogPrint( "PRI 형태 업데이트[%d-%d] 에러 입니다.", m_pLOBData->iPRIType, pABTData->iPRIType );
        }
        break;

// 	case E_AET_PRI_BEACON :
// 		pPRIDInfo->iType = m_pLOBData->iPRIType;
// 		pPRIDInfo->iPatternType = m_pLOBData->iPRIPatternType;
// 		pPRIDInfo->iIsPeriod = m_pLOBData->iIsPRIPeriod;
// 		pPRIDInfo->iChangePeriod = m_pLOBData->iPRIChangePeriod;
// 		pPRIDInfo->fChangePeriodMin = _min( pPRIDInfo->fChangePeriodMin, m_pLOBData->iPRIChangePeriod );
// 		pPRIDInfo->fChangePeriodMax = _max( pPRIDInfo->fChangePeriodMax, m_pLOBData->iPRIChangePeriod );
// 		pPRIDInfo->fChangePeriodMean = CalcMean( pPRIDInfo->fChangePeriodMean, pABTExtData->nCoTotalPdw, m_pLOBData->iPRIChangePeriod, m_pLOBData->iNumOfPDW );
// 		pPRIDInfo->iPositionCount = m_pLOBData->iPRIPositionCount;
// 		pPRIDInfo->iElementCount = m_pLOBData->iPRIElementCount;
// 		memcpy( pPRIDInfo->iSeq, m_pLOBData->iPRISeq, sizeof(pPRIDInfo->iSeq) );
// 		break;

    default:
        break;

    }

    // PRI 통계 정보
    pABTData->fPRIMax = _max( pABTData->fPRIMax, m_pLOBData->fPRIMax );
    pABTData->fPRIMin = _min( pABTData->fPRIMin, m_pLOBData->fPRIMin );
    pABTData->fPRIMean = CalcMean( pABTData->fPRIMean, pABTData->uiTotalOfPDW, m_pLOBData->fPRIMean, m_pLOBData->iNumOfPDW );
    //pPRIInfo->fDeviation = CalcDeviation( pPRIInfo->fDeviation, pABTExtData->nCoTotalPdw, m_pLOBData->iPRfDeviation, m_pLOBData->iNumOfPDW );
    pABTData->fPRIDeviation = pABTData->fPRIMax - pABTData->fPRIMin;

    pABTData->fPRIJitterRatio = CalcJitterRatio( pABTData, pABTExtData );

}

/**
 * @brief     지터율을 계산하여 빔 정보에 반영한다.
 * @param     *pABTData 빔 정보의 데이터 포인터
 * @param     *pABTExtData 빔 추가 정보의 데이터 포인터
 * @return    지터율

 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-14, 오후 4:40
 * @warning
 */
float CELEmitterMergeMngr::CalcJitterRatio( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
{
    float fRet;
    float fJitterRatio;

    fJitterRatio = (float) ( 50. * ( pABTData->fPRIMax - pABTData->fPRIMin ) );
    if( pABTData->fPRIMean == 0 || ! ( fJitterRatio > 0 || fJitterRatio < 0 ) ) { //DTEC_Else
        fRet = 0;
    }
    else {
        fRet = FDIV( fJitterRatio, pABTData->fPRIMean );
    }
    return fRet;
}

void CELEmitterMergeMngr::UpdateDOAInfo( SRxAETData *pAETData, SELAETDATA_EXT *pAETExtData, SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
{
// 	//STR_DOA_INFO *pDOAInfo;
//
// 	//pDOAInfo = & pABTData->doaInfo;
//
#ifdef _DOA_LOW_HIGH_
// 	int iDOALow, iDOAHigh, iDOADiff, iDOAOffset;
    // 수동으로 변경했으면 정보 유지
    if( pABTExtData->xManualEdited.x.peInfo == true && false ) {
        return;
    }

// 	// 수신한 방위 범위를 체크해서 방위 LOW, HIGH 를 계산함.
// 	iDOADiff = SubAOA( m_pLOBData->fDOAMax, m_pLOBData->fDOAMin );
// 	if( iDOADiff > ( MAX_AOA / 2 ) ) {
// 		iDOALow = m_pLOBData->fDOAMax;
// 		iDOAHigh = m_pLOBData->fDOAMin;
// 	}
// 	else {
// 		iDOALow = m_pLOBData->fDOAMin;
// 		iDOAHigh = m_pLOBData->fDOAMax;
// 	}
//
// 	// 방위 업데이트
// 	iDOAOffset = - iDOALow;
// 	iDOALow = 0;
// 	iDOAHigh = AddAOA( iDOAHigh, iDOAOffset );
//
// 	pDOAInfo->fMin = _min( iDOALow, m_pLOBData->fDOAMin );
// 	pDOAInfo->fMin = AddAOA( pDOAInfo->fMin, iDOAOffset );
// 	pDOAInfo->fMax = _max( iDOAHigh, m_pLOBData->fDOAMax );
// 	pDOAInfo->fMax = AddAOA( pDOAInfo->fMax, iDOAOffset );
// 	pDOAInfo->iMean = CalcMean( pDOAInfo->iMean, pABTExtData->nCoTotalPdw, m_pLOBData->iMeanDOA, m_pLOBData->iNumOfPDW );
// 	pDOAInfo->fDeviation = CalcDeviation( pDOAInfo->iMean, pABTExtData->nCoTotalPdw, m_pLOBData->iDOADeviation, m_pLOBData->iNumOfPDW );
// 	pDOAInfo->iSDeviation = 0;
#else
    pAETData->fDOAMin = pABTData->fDOAMin;
    pAETData->fDOAMax = pABTData->fDOAMax;
    pAETData->fDOAMean = pABTData->fDOAMean;
    pAETData->fDOADeviation = pABTData->fDOADeviation;

#endif

}

/**
 * @brief     빔 정보를 근거로 방사체의 주파수 정보를 변경한다.
 * @param     *pAETData 방사체 정보의 데이터 포인터
 * @param     *pAETExtData 방사체 추가 정보의 데이터 포인터
 * @param     *pABTData 빔 정보의 데이터 포인터
 * @param     *pABTExtData 빔 추가 정보의 데이터 포인터
 * @param     *pUELMANUALVAL 수동 변경 정보의 데이터 포인터
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-17, 오후 2:42
 * @warning
 */
void CELEmitterMergeMngr::UpdateFreqInfo( SRxAETData *pAETData, SELAETDATA_EXT *pAETExtData, SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
{
    // CASE 1 : 변경 무시 처리
// 	if( pUELMANUALVAL == NULL && pAETExtData->xMannualEdited.x.freqInfo == (UINT) 1 ) {
// 		//return;
// 	}
// 	else {

        if( pABTExtData != NULL ) {
            pAETData->fFreqMax = _max( pAETData->fFreqMax, pABTData->fFreqMax );
            pAETData->fFreqMin = _min( pAETData->fFreqMin, pABTData->fFreqMin );

            if( pAETData->uiCoABT == _spOne ) {
                pAETData->fFreqMean = pABTData->fFreqMean;
            }
            else {
                pAETData->fFreqMean = CalcMean( pAETData->fFreqMean, pAETExtData->nCoTotalPdw, pABTData->fFreqMean, pABTData->uiTotalOfPDW );
            }
        }
        else {

        }
        //pAETData->freqInfo.fDeviation = CalcDeviation( pAETData->freqInfo.fDeviation, pAETExtData->nCoTotalPdw, pABTData->freqInfo.fDeviation, pABTExtData->nCoTotalPdw );
        pAETData->fFreqDeviation = pAETData->fFreqMax- pAETData->fFreqMin;
/*	}*/

}

/**
 * @brief     주파수 변경 여부를 고려하여 빔 정보의 주파수 정보를 변경한다.
 * @param     *pABTData 빔 정보의 데이터 포인터
 * @param     *pABTExtData 빔 추가 정보의 데이터 포인터
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-11, 오후 2:33
 * @warning
 */
void CELEmitterMergeMngr::UpdateFreqInfo( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
{
    //STR_FREQ_PRI_DINFO *pFreqDInfo;

    //pFreqDInfo = & pABTData->freqDInfo;

    // 주파수 세부 정보
    switch( m_pLOBData->iFreqType ) {
    case E_AET_FRQ_FIXED :
        pABTData->iFreqType = m_pLOBData->iFreqType;

        // 추적 / 비콘 경우의 처리
        if( m_pLOBData->iFreqPositionCount > 0 ) {
            //pFreqDInfo->iElementCount = m_pLOBData->iFreqElementCount;
            pABTData->iFreqPositionCount = m_pLOBData->iFreqPositionCount;
            if( /* pFreqDInfo->iElementCount > 0 || */ pABTData->iFreqPositionCount > 0 ) {
                memcpy( pABTData->fFreqSeq, m_pLOBData->fFreqSeq, sizeof(m_pLOBData->fFreqSeq) );
            }
        }
        break;

    case E_AET_FRQ_HOPPING :
        pABTData->iFreqType = m_pLOBData->iFreqType;
        break;

// 	case E_AET_FRQ_BEACON :
// 		pFreqDInfo->iType = m_pLOBData->iFreqType;
// 		break;

    case E_AET_FRQ_AGILE :
        if( pABTData->iFreqType == E_AET_FRQ_AGILE ) {
            //pFreqDInfo->iIsPeriod = false;
            pABTData->iFreqPatternType = E_AET_FREQ_PRI_UNKNOWN;
            //pFreqDInfo->iChangePeriod = m_pLOBData->fFreqChangePeriod;
            pABTData->fFreqPatternPeriodMax = 0;
            pABTData->fFreqPatternPeriodMin = 0;
            pABTData->fFreqPatternPeriodMean = 0;
            pABTData->iFreqPositionCount = 0;
        }
        else if( pABTData->iFreqType == E_AET_FRQ_PATTERN ) {
            //pFreqDInfo->iIsPeriod = true;
            pABTData->iFreqPatternType = m_pLOBData->iFreqPatternType;
            //pABTData->fChangePeriodMin = min( pFreqDInfo->fChangePeriodMin, m_pLOBData->fFreqChangePeriod );
            //pABTData->fChangePeriodMax = max( pFreqDInfo->fChangePeriodMax, m_pLOBData->fFreqChangePeriod );
            //pABTData->fChangePeriodMean = CalcMean( pFreqDInfo->fChangePeriodMean, pABTExtData->nCoTotalPdw, m_pLOBData->fFreqMean, m_pLOBData->iNumOfPDW );
            pABTData->iFreqPositionCount = 0;
            //pABTData->iElementCount = 0;
        }
        else {
            LogPrint( "주파수 형태 업데이트[%d-%d] 에러 입니다.", m_pLOBData->iFreqType, pABTData->iFreqType );
        }
        break;

    case E_AET_FRQ_PATTERN :
        if( pABTData->iFreqType == E_AET_FRQ_AGILE ) {
            pABTData->iFreqType = E_AET_FRQ_PATTERN;
            //pFreqDInfo->iIsPeriod = false;
            //pFreqDInfo->iFreqPatternType = E_AET_FREQ_PRI_UNKNOWN;
            //pFreqDInfo->iChangePeriod = 0;
            //pFreqDInfo->fChangePeriodMin = 0;
            //pFreqDInfo->fChangePeriodMax = 0;
            //pFreqDInfo->fChangePeriodMean = 0;
            pABTData->iFreqPositionCount = 0;
            //pFreqDInfo->iElementCount = 0;
        }
        else if( pABTData->iFreqType == E_AET_FRQ_PATTERN ) {
            //pFreqDInfo->iIsPeriod = true;
            pABTData->iFreqPatternType = m_pLOBData->iFreqPatternType;
            //pFreqDInfo->iChangePeriod = m_pLOBData->fFreqChangePeriod;
            pABTData->fFreqPatternPeriodMin = min( pABTData->fFreqPatternPeriodMin, m_pLOBData->fFreqPatternPeriod );
            pABTData->fFreqPatternPeriodMax = max( pABTData->fFreqPatternPeriodMax, m_pLOBData->fFreqPatternPeriod );
            pABTData->fFreqPatternPeriodMean = CalcMean( pABTData->fFreqPatternPeriodMean, pABTData->uiTotalOfPDW, m_pLOBData->fFreqPatternPeriod, m_pLOBData->iNumOfPDW );
            pABTData->iFreqPositionCount = 0;
            //pFreqDInfo->iElementCount = 0;
        }
        else {
            LogPrint( "주파수 형태 업데이트[%d-%d] 에러 입니다.", m_pLOBData->iFreqType, pABTData->iFreqType );
        }
        memset( pABTData->fFreqSeq, 0, sizeof(pABTData->fFreqSeq) );
        break;

    default :
        {	//DTEC_Else
            LogPrint( "주파수 형태 업데이트[%d-%d] 에러 입니다.", m_pLOBData->iFreqType, pABTData->iFreqType );
        }
        break;

    }

    // 주파수 통계 정보
    pABTData->fFreqMax = _max( pABTData->fFreqMax, m_pLOBData->fFreqMax );
    pABTData->fFreqMin = _min( pABTData->fFreqMin, m_pLOBData->fFreqMin );
    pABTData->fFreqMean = CalcMean( pABTData->fFreqMean, pABTData->uiTotalOfPDW, m_pLOBData->fFreqMean, m_pLOBData->iNumOfPDW );
    //pABTData->freqInfo.fDeviation = CalcDeviation( pABTData->freqInfo.fDeviation, pABTExtData->nCoTotalPdw, m_pLOBData->iFreqDeviation, m_pLOBData->iNumOfPDW );
    //pABTData->freqInfo.fDeviation = pABTData->freqInfo.fMax - pABTData->freqInfo.fMin;

        // 추적 / 비콘 경우의 처리
    // 	pFreqDInfo->iElementCount = m_pLOBData->iFreqElementCount;
    // 	pFreqDInfo->iPositionCount = m_pLOBData->iFreqPositionCount;
    // 	if( pFreqDInfo->iElementCount > 0 || pFreqDInfo->iPositionCount > 0 ) {
    // 		memcpy( pFreqDInfo->iSeq, m_pLOBData->iFreqSeq, sizeof(pFreqDInfo->iSeq) );
    // 	}

}

/**
 * @brief     펄스 정보를 병합한다.
 * @param     SRxABTData * pABTData
 * @param     SELABTDATA_EXT * pABTExtData
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-09-28, 오전 11:53
 * @warning
 */
void CELEmitterMergeMngr::UpdateSignalInfo( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
{
    // 신호 형태
    pABTData->iSignalType = m_pLOBData->iSignalType;

}

// /**
//  * @brief     UpdatePolization
//  * @param     void
//  * @return    void
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2017-05-26, 오후 2:52
//  * @warning
//  */
// void CELEmitterMergeMngr::UpdatePolization( SELABTDATA_EXT *pABTExtData )
// {
// 	int iPolarization;
//
// 	iPolarization = m_pLOBData->iPolarization;
// 	if( iPolarization >= E_AET_POLIZATION_V && iPolarization <= E_AET_POLIZATION_LS ) {
// 		++ pABTExtData->nPolization[iPolarization];
// 	}
// }
//
// /**
//  * @brief     펄스 정보를 병합한다.
//  * @param     SRxABTData * pABTData
//  * @param     SELABTDATA_EXT * pABTExtData
//  * @return    void
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-09-28, 오전 11:53
//  * @warning
//  */
// void CELEmitterMergeMngr::UpdatePulseInfo( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
// {
// 	/*! \todo   펄스 정보는 큰 것으로 업데이트 한다.
// 			\author 조철희 (churlhee.jo@lignex1.com)
// 			\date 	2016-09-28 11:54:12
// 	*/
// 	if( m_pLOBData->iPulsePerGrp != 0 ) {
// 		pABTData->pulseDInfo.iPulsePerGrp = m_pLOBData->iPulsePerGrp;
// 	}
//
// 	memcpy( pABTData->pulseDInfo.iPRIPGSeq, m_pLOBData->iPRIPGSeq, sizeof(m_pLOBData->iPRIPGSeq) );
// 	memcpy( pABTData->pulseDInfo.iPAPGSeq, m_pLOBData->iPAPGSeq, sizeof(m_pLOBData->iPAPGSeq) );
// }

/**
 * @brief     빔 정보의 방위 정보를 변경 처리한다.
 * @param     *pABTData 빔 정보의 데이터 포인터
 * @param     *pABTExtData 빔 추가 정보의 데이터 포인터
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-11, 오전 11:08
 * @warning
 */
void CELEmitterMergeMngr::UpdateDOAInfo( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
{
// 	//STR_DOA_INFO *pDOAInfo;
//
// 	//pDOAInfo = & pABTData->doaInfo;
//
#ifdef _DOA_LOW_HIGH_
// 	int iDOALow, iDOAHigh, iDOADiff, iDOAOffset;
    // 수동으로 변경했으면 정보 유지
    if( pABTExtData->xManualEdited.x.peInfo == true && false ) {
        return;
    }

// 	// 수신한 방위 범위를 체크해서 방위 LOW, HIGH 를 계산함.
// 	iDOADiff = SubAOA( m_pLOBData->fDOAMax, m_pLOBData->fDOAMin );
// 	if( iDOADiff > ( MAX_AOA / 2 ) ) {
// 		iDOALow = m_pLOBData->fDOAMax;
// 		iDOAHigh = m_pLOBData->fDOAMin;
// 	}
// 	else {
// 		iDOALow = m_pLOBData->fDOAMin;
// 		iDOAHigh = m_pLOBData->fDOAMax;
// 	}
//
// 	// 방위 업데이트
// 	iDOAOffset = - iDOALow;
// 	iDOALow = 0;
// 	iDOAHigh = AddAOA( iDOAHigh, iDOAOffset );
//
// 	pDOAInfo->fMin = _min( iDOALow, m_pLOBData->fDOAMin );
// 	pDOAInfo->fMin = AddAOA( pDOAInfo->fMin, iDOAOffset );
// 	pDOAInfo->fMax = _max( iDOAHigh, m_pLOBData->fDOAMax );
// 	pDOAInfo->fMax = AddAOA( pDOAInfo->fMax, iDOAOffset );
// 	pDOAInfo->iMean = CalcMean( pDOAInfo->iMean, pABTExtData->nCoTotalPdw, m_pLOBData->iMeanDOA, m_pLOBData->iNumOfPDW );
// 	pDOAInfo->fDeviation = CalcDeviation( pDOAInfo->iMean, pABTExtData->nCoTotalPdw, m_pLOBData->iDOADeviation, m_pLOBData->iNumOfPDW );
// 	pDOAInfo->iSDeviation = 0;
#else
    pABTData->fDOAMin = m_pLOBData->fDOAMin;
    pABTData->fDOAMax = m_pLOBData->fDOAMax;
    pABTData->fDOAMean = m_pLOBData->fDOAMean;
    pABTData->fDOADeviation = m_pLOBData->fDOADeviation;


#endif

}

/**
 * @brief     LOB 데이터에 AET, ABT, LOB 번호를 저장한다.
 * @param     nAETID 방사체 번호
 * @param     nABTID 빔 번호
 * @param     nLOBID LOB 번호
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-07, 오후 12:07
 * @warning
 */
void CELEmitterMergeMngr::SetIDLOBData( UINT nAETID, UINT nABTID, UINT nLOBID )
{

    if( nAETID != 0 ) {
        m_pLOBData->uiAETID = nAETID;
        m_LOBDataExt.aetAnal.uiAETID = nAETID;
    }
    else {
        m_pLOBData->uiAETID = m_uiAETID;
        m_LOBDataExt.aetAnal.uiAETID = m_uiAETID;
    }

    if( nABTID != 0 ) {
        m_LOBDataExt.aetAnal.uiABTID = nABTID;
        m_pLOBData->uiABTID = nABTID;
    }
    else {
        m_pLOBData->uiABTID = m_uiABTID;
        m_LOBDataExt.aetAnal.uiABTID = m_uiABTID;
    }

    m_LOBDataExt.aetAnal.uiLOBID = nLOBID;

}

/**
 * @brief     AET 구조체에 LOB 데이터를 기반으로 생성한다.
 * @param     *pThreat 방사체 정보의 데이터 포인터
 * @param     *pLOBDataGrp LOB 정보의 데이터 포인터
 * @param     *pLOCDataExt LOB 추가 정보의 데이터 포인터
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-06, 오후 3:49
 * @warning
 */
void CELEmitterMergeMngr::CreateAETThreat( CELThreat *pAETThreat, CELThreat *pABTThreat, SRxLOBData *pLOBData, SELLOBDATA_EXT *pLOCDataExt )
{
    int nIndex=pAETThreat->m_nIndex;
    //UELTHREAT *pUniThreat;
    SRxAETData *pAETData;
    SELAETDATA_EXT *pAETExtData;

    //pUniThreat = m_pUniThreat + nIndex;

    //pAETData = & pUniThreat->uniAET.stAETData;
    pAETData = GetAETData( nIndex );
    //pAETExtData = & pUniThreat->uniAET.stAETExtData;
    pAETExtData = GetAETExtData( nIndex );

    pAETData->uiAETID = pAETThreat->m_Idx.uiAET;

    pAETData->uiCoLOB = _spOne;
    pAETData->uiCoABT = _spOne;

    pAETData->tiFirstSeenTime = pLOCDataExt->aetAnal.tiAcqTime;
    //pAETData->firstSeenMillisec = (UINT) pLOCDataExt->aetAnal.tiContactTimems;
    pAETData->tiLastSeenTime = pLOCDataExt->aetAnal.tiAcqTime;
    //pAETData->lastSeenMillisec = (UINT) pLOCDataExt->aetAnal.tiContactTimems;

    pAETData->iValidity = false;

    pAETData->fDOAMean = pLOBData->fDOAMean;
    pAETData->fDOAMax = pLOBData->fDOAMax;
    pAETData->fDOAMin = pLOBData->fDOAMin;
    pAETData->fDOADeviation = pLOBData->fDOADeviation;

    pAETData->fFreqMean = pLOBData->fFreqMean;
    pAETData->fFreqMax = pLOBData->fFreqMax;
    pAETData->fFreqMin = pLOBData->fFreqMin;
    pAETData->fFreqDeviation = pAETData->fFreqMax - pAETData->fFreqMin;

    pAETData->fPRIMean = pLOBData->fPRIMean;
    pAETData->fPRIMax = pLOBData->fPRIMax;
    pAETData->fPRIMin = pLOBData->fPRIMin;
    pAETData->fPRIDeviation = pAETData->fPRIMax - pAETData->fPRIMin;

    pAETData->fPWMean = pLOBData->fPWMean;
    pAETData->fPWMax = pLOBData->fPWMax;
    pAETData->fPWMin = pLOBData->fPWMin;
    pAETData->fPWDeviation = pAETData->fPWMax - pAETData->fPWMin;

    pAETData->fPAMean = pLOBData->fPAMean;
    pAETData->fPAMax = pLOBData->fPAMax;
    pAETData->fPAMin = pLOBData->fPAMin;
    pAETData->fPADeviation = pAETData->fPAMax - pAETData->fPAMin;

    // CED/EOB 식별 정보
    pAETData->iRadarModeIndex = pLOBData->iRadarModeIndex;
    pAETData->iThreatIndex = 0;
    pAETData->iPlatformType = 0;
    pAETData->iRadarPriority = 0;
    pAETData->iRadarModePriority = 0;
    pAETData->iThreatPriority = 0;

    // 위치 산출 정보
    pAETData->iPEValid = 0;
    pAETData->fLatitude = 0;							// [deg]
    pAETData->fLongitude = 0;							// [deg]
    pAETData->fAltidude = 0;							// [deg]
    pAETData->fCEP = -1;										// [m]
    pAETData->fMajorAxis = -1;							// [m]
    pAETData->fMinorAxis = 0;							// [m]
    pAETData->fTheta = 0;									// [0.1도]
    pAETData->fDistanceErrorOfThreat = -1;	// [m]

    //pAETData->peInfo.iAltidude = pLOBDataGrp->iAltitude;

    // 보고서 정보
    //pAETData->firstReportedTime = 0;
    //pAETData->finalReportedTime = 0;
    pAETData->tiFinalAlarmTime = 0;

    pAETData->iStat = 0;

    pAETData->szIDInfo[0] = 0;

    //////////////////////////////////////////////////////////////////////////
    // AET 추가 정보 초기화
    memset( pAETExtData, 0, sizeof(SELAETDATA_EXT) );

    pAETExtData->nCoTotalPdw = pLOBData->iNumOfPDW;
    //pAETExtData->nCoTotalIQ = pLOBDataGrp->iNumOfIQ;

    // 빔 중에서 미식별 번호
    if( pABTThreat != NULL ) {
        pAETExtData->nUnIDABTID = pABTThreat->m_Idx.uiABT;
    }
    else {
        if( m_pUpdateABTThreat != NULL ) {
            pAETExtData->nUnIDABTID = m_pUpdateABTThreat->m_Idx.uiABT;
        }
        else {
            LogPrint( "\n[경고] 방사체에 빔 번호[%d]를 입력해줘야 한다." , pAETExtData->nUnIDABTID );
        }
    }

    // pAETExtData->bIntraMop = ( pAETData->intraInfo.iType != E_AET_MOP_UNK ? true : false );

    pAETExtData->enBeamEmitterStat = UpdateEmitterStat( pAETExtData->enBeamEmitterStat, E_ES_NEW );

    //pAETExtData->enBeamEmitterStat = IsDeleteThreat( pAETThreat );

    //pAETExtData->bIsFISINTTask = ( m_pLOBData->iIsFISINTTask > 0 );

    //pAETExtData->iTaskType = m_pLOBData->iTaskType / 2;

    pAETExtData->uiSeqNum = m_nSeqNum;

}
//
/**
 * @brief     ABT 구조체에 LOB 데이터를 기반으로 생성한다.
 * @param     *pThreat 방사체 정보의 데이터 포인터
 * @param     *pLOBData LOB 헤더 정보의 데이터 포인터
 * @param     *pLOBDataGrp LOB 데이터 정보의 데이터 포인터
 * @param     *pThreatDataExt LOB 추가 정보의 데이터 포인터
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-06, 오후 3:49
 * @warning
 */
void CELEmitterMergeMngr::CreateABTThreat( CELThreat *pThreat, SRxLOBHeader *pLOBHeader, SRxLOBData *pLOBData, SELLOBDATA_EXT *pThreatDataExt, bool bCluster )
{
    int nIndex=pThreat->m_nIndex;

    m_pABTData = GetABTData( nIndex );
    m_pABTExtData = GetABTExtData( nIndex );

    // 초기화
    memset( m_pABTData, 0, sizeof(SRxABTData) );
    memset( m_pABTExtData, 0, sizeof(SELABTDATA_EXT) );

    // 자료 복사
    m_pABTData->uiAETID = pThreat->m_Idx.uiAET;
    m_pABTData->uiABTID = pThreat->m_Idx.uiABT;

    m_pABTData->iSignalType = pLOBData->iSignalType;
    //pABTData->sigInfo.modCode[0] = pThreatDataExt->aetAnal.modCode[0];
    //pABTData->sigInfo.modCode[1] = pThreatDataExt->aetAnal.modCode[1];
    //pABTData->sigInfo.iPolarization = pLOBDataGrp->iPolarization;

    //pABTData->pulseDInfo.iPulsePerGrp = pLOBDataGrp->iPulsePerGrp;
    //memcpy( pABTData->pulseDInfo.iPRIPGSeq, pLOBData->iPRIPGSeq, sizeof(pLOBData->iPRIPGSeq) );
    //memcpy( pABTData->pulseDInfo.iPAPGSeq, pLOBData->iPAPGSeq, sizeof(pLOBData->iPAPGSeq) );

    m_pABTData->uiCoLOB = _spOne;
    pThreatDataExt->aetAnal.uiCoLOB = _spOne;

    SetupDateTime( pThreatDataExt );
    m_pABTData->tiFirstSeenTime = pThreatDataExt->aetAnal.tiAcqTime;
    //pABTData->firstSeenMillisec = (UINT) pThreatDataExt->aetAnal.tiContactTimems;
    m_pABTData->tiLastSeenTime = pThreatDataExt->aetAnal.tiAcqTime;
    //pABTData->lastSeenMillisec = (UINT) pThreatDataExt->aetAnal.tiContactTimems;

    m_pABTData->iValidity = false;

    m_pABTData->fDOAMean = pLOBData->fDOAMean;
    m_pABTData->fDOAMax = pLOBData->fDOAMax;
    m_pABTData->fDOAMin = pLOBData->fDOAMin;
    m_pABTData->fDOADeviation = pLOBData->fDOADeviation;

    m_pABTData->iFreqType = pLOBData->iFreqType;
    m_pABTData->iFreqPatternType = pLOBData->iFreqPatternType;
    m_pABTData->fFreqPatternPeriodMean = pLOBData->fFreqPatternPeriod;
    m_pABTData->fFreqPatternPeriodMin = pLOBData->fFreqPatternPeriod;
    m_pABTData->fFreqPatternPeriodMax = pLOBData->fFreqPatternPeriod;
    m_pABTData->iFreqPositionCount = pLOBData->iFreqPositionCount;
    m_pABTData->iFreqElementCount = pLOBData->iFreqElementCount;
    m_pABTData->fFreqMean = pLOBData->fFreqMean;
    m_pABTData->fFreqMax = pLOBData->fFreqMax;
    m_pABTData->fFreqMin = pLOBData->fFreqMin;
    m_pABTData->fFreqDeviation = pLOBData->fFreqDeviation;
    memcpy( m_pABTData->fFreqSeq, pLOBData->fFreqSeq, sizeof( m_pABTData->fFreqSeq ) );

    m_pABTData->iPRIType = pLOBData->iPRIType;
    m_pABTData->iPRIPatternType = pLOBData->iPRIPatternType;

    m_pABTData->fPRIPatternPeriodMin = pLOBData->fPRIPatternPeriod;
    m_pABTData->fPRIPatternPeriodMax = pLOBData->fPRIPatternPeriod;
    m_pABTData->fPRIPatternPeriodMean = pLOBData->fPRIPatternPeriod;
    m_pABTData->iPRIPositionCount = pLOBData->iPRIPositionCount;
    m_pABTData->iPRIElementCount = pLOBData->iPRIElementCount;    
    memcpy( m_pABTData->fPRISeq, pLOBData->fPRISeq, sizeof( m_pABTData->fPRISeq ) );
    m_pABTData->fPRIMean = pLOBData->fPRIMean;
    m_pABTData->fPRIMax = pLOBData->fPRIMax;
    m_pABTData->fPRIMin = pLOBData->fPRIMin;
    m_pABTData->fPRIJitterRatio = CalcJitterRatio( m_pABTData, m_pABTExtData );
    m_pABTData->fPRIDeviation = pLOBData->fPRIDeviation;

    //pABTData->priInfo.fDeviation = pABTData->priInfo.fMax - pABTData->priInfo.fMin;

    m_pABTData->fPWMean = pLOBData->fPWMean;
    m_pABTData->fPWMax = pLOBData->fPWMax;
    m_pABTData->fPWMin = pLOBData->fPWMin;
    m_pABTData->fPWDeviation = pLOBData->fPWDeviation;


    m_pABTData->fPAMean = pLOBData->fPAMean;
    m_pABTData->fPAMax = pLOBData->fPAMax;
    m_pABTData->fPAMin = pLOBData->fPAMin;
    m_pABTData->fPADeviation = pLOBData->fPADeviation;
    //pABTData->paInfo.fDeviation = pABTData->paInfo.fMax - pABTData->paInfo.fMin;

    m_pABTData->uiTotalOfPDW = pLOBData->iNumOfPDW;

    m_pABTData->fCEP = -1.0;
    m_pABTData->fMajorAxis = -1.0;
    m_pABTData->fMinorAxis= -1.0;
    m_pABTData->fTheta = 0.0;

    // 알람 정보
    m_pABTData->tiFinalAlarmTime = 0;

    m_pABTData->iStat = 0;

    IdentifyABT( m_pABTData, m_pABTExtData );

    m_pABTExtData->bCompFreq = true;
    m_pABTExtData->bCompPRI = true;

    m_pABTExtData->nCoBeamValidity = ( m_LOBDataExt.aetAnal.iBeamValidity > 0 ? 1 : 0 );

    memset( & m_pABTExtData->idInfo, 0, sizeof( STR_CEDEOBID_INFO ) );

    m_pABTExtData->enBeamEmitterStat = E_ES_NEW;

    m_pABTExtData->enPlatform = enPlatform_UNKNOWN;

    m_pABTExtData->enValid = E_EL_PESTAT_NOT_YET;
    m_pABTExtData->bApplayOfLOBClustering = ! bCluster;

#ifdef _ELINT_   

    // 위치 산출 정보
    //memset( & pABTExtData->peInfo, 0, sizeof( STR_POSITION_ESTIMATION ) );

    //////////////////////////////////////////////////////////////////////////
    // ABT 추가 정보 설정
    //memset( & pABTExtData->xManualEdited, 0, sizeof(UELMANUALVAL) );
  
    //pABTExtData->bIsManualEdited = false;

    //pABTExtData->bManualPosEstPreferred = false;

    m_pABTExtData->uiSeqNum = m_nSeqNum;

    m_pABTExtData->uiOpInitID = m_lOpInitID;

#elif _POCKETSONATA_
    m_pABTExtData->tiSendLan = 0;

#endif

    memcpy( & m_ABTDataExt, & m_LOBDataExt, sizeof(SELLOBDATA_EXT) );

    m_pABTExtData->enBeamEmitterStat = UpdateEmitterStat( m_pABTExtData->enBeamEmitterStat, E_ES_NEW );

    m_pABTExtData->iLOBPoolIndex = nIndex;

    memset( & m_pABTExtData->stIDType, 0, sizeof( STR_ID_TYPE ) );

    //UpdatePolization( pABTExtData );

    //
    ClearLOBs( nIndex );
    AppendLOBs( nIndex );

}

/**
 * @brief     날짜 및 시간을 변경한다.
 * @param     *pThreatDataExt LOB 추가 정보의 데이터 포인터
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-05-13, 오후 3:15
 * @warning
 */
void CELEmitterMergeMngr::SetupDateTime( SELLOBDATA_EXT *pThreatDataExt )
{
    I_AET_ANAL *pAetAnal;

    pAetAnal = & pThreatDataExt->aetAnal;

    pAetAnal->tiAcqTime = m_pLOBData->tiContactTime;
    pAetAnal->tiContactTimems = m_pLOBData->tiContactTimems;

    if( pAetAnal->tiContactTimems > 999 ) { //DTEC_Else
        UINT uiTime;

        uiTime = (UINT) pAetAnal->tiContactTimems & 999;
        pAetAnal->tiContactTimems = (int) uiTime;
    }

}

/**
 * @brief     위협과 LOB 간의 비교한다.
 * @param     *pMergeCandidate 병합된 위협의 후보 목록
 * @param     *pThreatABT 위협 데이터 포인터
 * @param     *pThreatDataExt LOB 추가 정보의 데이터 포인터
 * @param     bLinkComp 링크 병합 여부
 * @return    병합되면 true, 아니면 false 로 리턴한다.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-06, 오후 6:17
 * @warning
 */
bool CELEmitterMergeMngr::CompMergeLOB( SELMERGE_CANDIDATE *pMergeCandidate, CELThreat *pThreatABT, SELLOBDATA_EXT *pThreatDataExt, bool bLinkComp )
{
    bool bRet=false;
    //int nIndex=pThreatABT->m_nIndex;
    SRxABTData *pABTData;
    SELABTDATA_EXT *pABTExtData;

    pABTData = GetABTData( pThreatABT->m_nIndex );
    pABTExtData = GetABTExtData( pThreatABT->m_nIndex );

    //m_nFreqBand = CalcFreqBand( m_pLOBData->fFreqMin );

    pMergeCandidate->fLevel = 0;

    // 미식별 ELNOT 초기화
    //m_szELNOT[0] = NULL;

    // 신호 형태가 동일해야 나머지 주파수, PRI, PW, 스캔 정보를 비교함.
    //if( m_pLOBOtherInfo->bUpdate == false || true ) {
    if( CompEmitterInfo( pABTData, pABTExtData ) == true ) {
        if( ( true == CompIDInfo( pABTData, pABTExtData ) ) && ( true == CompIDELNOTInfo( pABTData, pABTExtData ) ) ) {
            if( true == CompDist( pABTData, pABTExtData ) ) {
                pMergeCandidate->fLevel += CompDistRange( pABTData, pABTExtData );

                // 식별 정보가 다를때만 제원 비교를 본다 -> 변경
                CompELNOTInfo( pMergeCandidate, pABTData, pABTExtData );

                // 유효 병합 체크
                pMergeCandidate->fLevel += CompValid( pABTData );

                // 병합 레벨을 비교하여
                if( pMergeCandidate->fLevel >= THRESHOLD_OF_MIN_CANDIDATE_LEVEL ) {
                    bRet = false;
                }
                else {
                    pMergeCandidate->idx.uiAET = pABTData->uiAETID;
                    pMergeCandidate->idx.uiABT = pABTData->uiABTID;
                    pMergeCandidate->idx.uiLOB = INVALID_INDEX;

                    //strcpy_s( pMergeCandidate->szELNOT, pABTExtData->szELNOT );
// 					if( pABTExtData->szELNOT[0] =='H' ) {
// 						//strcpy_s( m_szELNOT, pABTExtData->szELNOT );
// 					}

                    bRet = true;
                }
            }
            else {
                /*! \todo  위치 산출 정보와 비교하여 병합 비교를 판단한다. 위치 산출 정보가 없으면 병합 비교 실패로 리턴한다.
                        \author 조철희 (churlhee.jo@lignex1.com)
                        \date 	2016-03-7 14:40:41
                */
                m_LOBDataExt.aetAnal.eBeamCode = E_CREATE_DIST_CODE;

// 				if( pABTExtData->szELNOT[0] =='H' ) {
// 					strcpy_s( m_szELNOT, pABTExtData->szELNOT );
// 				}
                bRet = false;
            }
        }
    }

    return bRet;
}

//
// /**
//  * @brief     입력한 주파수에 해당하는 주파수 밴드를 계산한다.
//  * @param     iFreq 주파수 값
//  * @return    주파수 밴드
//
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-03-07, 오후 2:07
//  * @warning
//  */
// enum FREQ_BAND CELEmitterMergeMngr::CalcFreqBand( int iFreq )
// {
// 	enum FREQ_BAND enBand;
//
// 	if( iFreq <= 200000 ) {
// 		enBand = BAND1;
// 	}
// 	else if( /* iFreq > 200000 && */ iFreq <= 600000 ) {
// 		enBand =BAND2;
// 	}
// 	else if( /* iFreq > 60000 && */ iFreq <= 1800000 ) {
// 		enBand = BAND3;
// 	}
// 	else {
// 		enBand = BAND4;
// 	}
// 	return enBand;
// }

/**
 * @brief     위치 산출 정보와 LOB 간의 거리 비교
 * @param     *pABTData 빔 정보의 데이터 포인터
 * @param     *pABTExtData 빔 추가 정보의 데이터 포인터
 * @return    거리 비교하여 병합되면 true, 아니면 false
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-06-13, 오후 10:27
 * @warning
 */
bool CELEmitterMergeMngr::CompDist( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
{
    bool bRet = false;

    //SEnvironVariable *pSEnvironVariable;

    float fTheta, fDiff, fDistance;

    if( m_bScanProcess == true ) {
        bRet = ( pABTData->uiABTID == m_pLOBData->uiABTID );
    }
    else {
        // 위치 산출 정보를 이용하여 거리 비교를 수행
        switch( pABTData->iPEValid ) {
        case E_EL_PESTAT_SUCCESS :
            if( pABTData->iValidity == 1 ) {
                /*! \debug  유효인 빔인 경우에는 LOB가 유효인 것만 병합을 수행한다.
                      \author 조철희 (churlhee.jo@lignex1.com)
                      \date 	2017-12-16 10:53:16
                */
                if( m_LOBDataExt.aetAnal.iBeamValidity == E_VALID ) {
                    fTheta = (float) m_theInverseMethod.GCAzimuth( m_pLOBData->fRadarLatitude, m_pLOBData->fRadarLongitude, (double) pABTData->fLatitude, (double) pABTData->fLongitude );
                    if( TRUE == CompAoaDiff( fTheta,  m_pLOBData->fDOAMean, 10 /* GP_MGR_PARAM->GetEffectiveDOADiff2()*/ ) ) {
                        fDiff = AoaDiff( fTheta, m_pLOBData->fDOAMean );
                        fDistance = (float) sin( DEGREE2RADIAN( fDiff ) ) * (float) m_theInverseMethod.EllipsoidDistance( m_pLOBData->fRadarLatitude, m_pLOBData->fRadarLongitude, (double) pABTData->fLatitude, (double) pABTData->fLongitude );
                        if( fDistance < m_pSEnvironVariable->fEobIndfRangeMeters ) {
                            // LOB와 점사이의 거리를 계산하여 LOB 검증을 비교한다.
                            bRet = true;
                        }
                        else {
                            bRet = false;
                            // LogPrint( "\n 빔[%5d]과 LOB[%5d] 간의 거리차[%f]가 커서 병합 실패로 처리합니다 !", pABTData->uiABTID, m_pLOBData->uiLOBID, fDistance );
                        }
                    }
                    else {
                        //GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_MSG, E_WARNING_NONE, enumGMEO_DEVICE, enumGMEI_DEVICE, "빔 번호(%d, %d) 간의 위치 산출 차이[%.3f]로 분리됨" , pABTData->uiAETID, pABTData->uiABTID, fTheta );
                        bRet = false;
                    }
                }
            }
            else {
                bRet = true;
            }
            break;

        case E_EL_PESTAT_FAIL :
        case E_EL_PESTAT_NOT_YET :
            bRet = true;
            break;

        case E_EL_PESTAT_IMPOSSIBILITY :
            bRet = true;
            break;

        default:
            break;
        }
    }

    return bRet;

}
//
// /**
//  * @brief     위치 산출 정보와 LOB 간의 거리 비교한다
//  * @param     *pABTData 빔 정보의 데이터 포인터
//  * @param     *pABTExtData 빔 추가 정보의 데이터 포인터
//  * @return    거리 비교하여 병합되면 true, 아니면 false
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-06-13, 오후 10:27
//  * @warning
//  */
// bool CELEmitterMergeMngr::CompDist( SRxABTData *pRefABTData, SELABTDATA_EXT *pRefABTExtData, SRxABTData *pCmpABTData, SELABTDATA_EXT *pCmpABTExtData )
// {
// 	bool bRet = false;
//
// 	float fDist;
//
// 	// 비교할 빔들은 탐지 과제끼리들만 비교를 수행
// 	if( pRefABTData->uiAETID != pCmpABTData->uiAETID ) {
// 		//if( (pRefABTExtData->iTaskType/2) == 0 && (pCmpABTExtData->iTaskType/2) == 0 ) {
// 		if( pRefABTExtData->iTaskType == pCmpABTExtData->iTaskType ) {
// 			if( pRefABTData->iValidity == true && pCmpABTData->iValidity == true ) {
// 				if( IsCompareIDInfo( pRefABTData, pRefABTExtData, pCmpABTData, pCmpABTExtData ) == true ) {
// 					fDist = (float) m_theInverseMethod.EllipsoidDistance( pRefABTData->peInfo.iLatitude/DEF_OF_RES_GEOPOS, pRefABTData->peInfo.iLongitude/DEF_OF_RES_GEOPOS, pCmpABTData->peInfo.iLatitude/DEF_OF_RES_GEOPOS, pCmpABTData->peInfo.iLongitude/DEF_OF_RES_GEOPOS );
// 					if( fDist <= GP_MGR_PARAM->GetDistanceForBeamMerge() ) {
// 						bRet = true;
// 					}
// 				}
// 			}
// 		}
// 	}
//
// 	return bRet;
// }

/**
 * @brief     장비 인덱스가 동일 여부를 판단한다.
 * @param     SRxABTData * pRefABTData
 * @param     SELABTDATA_EXT * pRefABTExtData
 * @param     SRxABTData * pCmpABTData
 * @param     SELABTDATA_EXT * pCmpABTExtData
 * @return    bool
 * @return    성공시 true, 실패시 false
*/
bool CELEmitterMergeMngr::CompPINNum( SRxABTData *pRefABTData, SELABTDATA_EXT *pRefABTExtData, SRxABTData *pCmpABTData, SELABTDATA_EXT *pCmpABTExtData )
{
    bool bRet = false;

    // 비교할 빔들은 탐지 과제끼리들만 비교를 수행
    if( IsComparePINInfo( pRefABTData, pRefABTExtData, pCmpABTData, pCmpABTExtData ) == true ) {
        bRet = true;
    }

    return bRet;
}

// /**
//  * @brief     IsCompareIDInfo
//  * @param     SRxABTData * pRefABTData
//  * @param     SELABTDATA_EXT * pRefABTExtData
//  * @param     SRxABTData * pCmpABTData
//  * @param     SELABTDATA_EXT * pCmpABTExtData
//  * @return    bool
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2017-01-16, 오후 1:35
//  * @warning
//  */
// bool CELEmitterMergeMngr::IsCompareIDInfo( SRxABTData *pRefABTData, SELABTDATA_EXT *pRefABTExtData, SRxABTData *pCmpABTData, SELABTDATA_EXT *pCmpABTExtData )
// {
// 	bool bRet = false;
//
// 	// ELNOT 비교를 레이더 인덱스로 비교함
// 	if( pRefABTData->idInfo.nRadarIndex[0] != 0 && pCmpABTData->idInfo.nRadarIndex[0] != 0 ) {
// 		if( pRefABTData->idInfo.nRadarIndex[0] == pCmpABTData->idInfo.nRadarIndex[0] ) {
// 			bRet = true;
// 		}
// 	}
// 	return bRet;
// }
//
/**
 * @brief     PIN 번호가 동일 여부를 판단한다.
 * @param     SRxABTData * pRefABTData
 * @param     SELABTDATA_EXT * pRefABTExtData
 * @param     SRxABTData * pCmpABTData
 * @param     SELABTDATA_EXT * pCmpABTExtData
 * @return    bool
 * @return    성공시 true, 실패시 false
*/
bool CELEmitterMergeMngr::IsComparePINInfo( SRxABTData *pRefABTData, SELABTDATA_EXT *pRefABTExtData, SRxABTData *pCmpABTData, SELABTDATA_EXT *pCmpABTExtData )
{
    bool bRet = false;

    // PIN 번호를 비교하는데 위협 인덱스만으로 비교함
    if( pRefABTExtData->idInfo.nThreatIndex != 0 && pCmpABTExtData->idInfo.nThreatIndex != 0 ) {
        if( pRefABTExtData->idInfo.nThreatIndex == pCmpABTExtData->idInfo.nThreatIndex ) {
            bRet = true;
        }
    }
    return bRet;
}

/**
 * @brief     비교할 빔의 ELNOT을 비교한다.
 * @param     SRxABTData * pRefABTData
 * @param     SELABTDATA_EXT * pRefABTExtData
 * @param     SRxABTData * pCmpABTData
 * @param     SELABTDATA_EXT * pCmpABTExtData
 * @return    bool
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-12-06, 오후 2:45
 * @warning
 */
bool CELEmitterMergeMngr::CompELNOT( SRxABTData *pRefABTData, SELABTDATA_EXT *pRefABTExtData, SRxABTData *pCmpABTData, SELABTDATA_EXT *pCmpABTExtData )
{
    bool bRet = false;

    if( pRefABTExtData->idInfo.nCoRadarModeIndex >= 1 && pCmpABTExtData->idInfo.nCoRadarModeIndex >= 1 ) {
        if( pRefABTExtData->idInfo.nRadarModeIndex[0] == pCmpABTExtData->idInfo.nRadarModeIndex[0] ) {
            bRet = true;
        }

    }

    return bRet;
}

//
// /**
//  * @brief     ABT 간 정보를 비교한다.
//  * @param     CELThreat * pRefThreat
//  * @param     CELThreat * pCmpThreat
//  * @return    bool
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-12-05, 오후 7:28
//  * @warning
//  */
// // bool CELEmitterMergeMngr::CompABTInfo( SRxABTData *pRefABTData, SELABTDATA_EXT *pRefABTExtData, SRxABTData *pCmpABTData, SELABTDATA_EXT *pCmpABTExtData )
// // {
// // 	bool bRet = false;
// //
// // 	float fDist;
// //
// // 	// 비교할 빔들은 탐지 과제끼리들만 비교를 수행
// // 	if( pRefABTExtData->iTaskType == pCmpABTExtData->iTaskType ) {
// // 		if( pRefABTData->iValidity == true && pCmpABTData->iValidity == true ) {
// // 			fDist = (float) m_theInverseMethod.EllipsoidDistance( pRefABTData->peInfo.iLatitude/DEF_OF_RES_GEOPOS, pRefABTData->peInfo.iLongitude/DEF_OF_RES_GEOPOS, pCmpABTData->peInfo.iLatitude/DEF_OF_RES_GEOPOS, pCmpABTData->peInfo.iLongitude/DEF_OF_RES_GEOPOS );
// // 			if( !( fDist > DELTA_DISTANCE_BT_POINT_AND_POINT ) ) {
// // 				bRet = true;
// // 			}
// // 		}
// //
// // 	}
// //
// // 	return bRet;
// // }
//
// /**
//  * @brief     인트라 형태 비교하여 결과를 리턴한다.
//  * @param     *pABTData 빔 정보의 데이터 포인터
//  * @return    병합이 정상이면 true, 그렇지 않으면 false
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-03-14, 오후 5:36
//  * @warning
//  */
// bool CELEmitterMergeMngr::CompIntraType( SRxABTData *pABTData )
// {
// 	bool bRet=true;
//
// 	switch( pABTData->intraInfo.iType ) {
// 	case E_AET_MOP_UNK :
// 		// bRet = true;
// 		break;
//
// 	case E_AET_MOP_NM :
// 	case E_AET_MOP_PSK :
// 	case E_AET_MOP_FSK :
// 	case E_AET_MOP_LFM :
// 	case E_AET_MOP_NLFM :
// 		if( ( m_pLOBData->iMOPType != E_AET_MOP_UNK ) && ( pABTData->intraInfo.iType != m_pLOBData->iMOPType ) ) {
// 			bRet = false;
// 			m_LOBDataExt.aetAnal.eBeamCode = E_CREATE_INTRA_TYPE_CODE;
// 		}
// 		break;
//
// 	default :
// 		{	//DTEC_Else
//
// 		}
// 		break;
// 	}
// 	return bRet;
// }
//
/**
 * @brief     주파수 형태 비교하여 결과를 리턴한다.
 * @param     *pABTData 빔 정보의 데이터 포인터
 * @return    병합이 정상이면 true, 그렇지 않으면 false
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-07, 오후 1:34
 * @warning
 */
bool CELEmitterMergeMngr::CompFreqType( SRxABTData *pABTData )
{
    bool bRet=false;

    switch( pABTData->iFreqType ) {
    case E_AET_FRQ_FIXED :
        if( m_pLOBData->iFreqType == E_AET_FRQ_FIXED ) {
            bRet = true;
        }
        break;

    case E_AET_FRQ_AGILE :
        if( m_pLOBData->iFreqType == E_AET_FRQ_AGILE ) {
            bRet = true;
        }
        break;

    case E_AET_FRQ_PATTERN :
        if( m_pLOBData->iFreqType == E_AET_FRQ_PATTERN ) {
            // 패턴일때 주기 및 형태 비교 수행
            if( /* pABTData->freqDInfo.iType == E_AET_FRQ_PATTERN && */ m_pLOBData->iFreqPatternType == E_AET_FRQ_PATTERN ) {
                switch( pABTData->iFreqPatternType ) {
                case E_AET_FREQ_PRI_UNKNOWN :
                    bRet = true;
                    break;

                case E_AET_FREQ_PRI_SINE :
                case E_AET_FREQ_PRI_SLIDE_INC :
                case E_AET_FREQ_PRI_SLIDE_DEC :
                case E_AET_FREQ_PRI_SAW_TRI :
                    if( pABTData->iFreqPatternType == m_pLOBData->iFreqPatternType ) {
                        bRet = true;
                    }
                    break;

                default:
                    break;
                }
            }
            else {
                bRet = true;
            }
        }
        break;

    case E_AET_FRQ_HOPPING :
        if( m_pLOBData->iFreqType == E_AET_FRQ_HOPPING ) {
            bRet = true;
        }
        break;

    default:
        break;

// 	case E_AET_FRQ_BEACON :
// 		if( m_pLOBData->iFreqType == E_AET_FRQ_BEACON ) {
// 			bRet = true;
// 		}
        // break;

    }

//     if( bRet == false ) {
//         m_LOBDataExt.aetAnal.eBeamCode = E_CREATE_FREQ_TYPE_CODE;
//     }

    return bRet;
}

/**
 * @brief     PRI 형태별 병합 비교한다. STABLE 인 경우는 동일한 형태를 비교하고...
 * @param     *pABTData 빔 정보의 데이터 포인터
 * @return    병합이 정상이면 true, 그렇지 않으면 false
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-07, 오후 2:16
 * @warning
 */
bool CELEmitterMergeMngr::CompPRIType( SRxABTData *pABTData )
{
    bool bRet=false;

    switch( pABTData->iPRIType ) {
    case E_AET_PRI_FIXED :
        /*! \todo   추적 비콘 레벨 수 비교
                \author 조철희 (churlhee.jo@lignex1.com)
                \date 	2017-01-11 16:25:55
        */
        if( m_pLOBData->iPRIType == E_AET_PRI_FIXED ) {
            bRet = true;
        }
        break;

    case E_AET_PRI_JITTER :
        if( m_pLOBData->iPRIType == E_AET_PRI_JITTER ) {
            bRet = true;
        }
        break;

    case E_AET_PRI_DWELL_SWITCH :
        if( m_pLOBData->iPRIType == E_AET_PRI_DWELL_SWITCH ) {
            bRet = true;
        }
        break;

    case E_AET_PRI_STAGGER :
        if( m_pLOBData->iPRIType == E_AET_PRI_STAGGER ) {
            bRet = true;
        }
        break;

    case E_AET_PRI_PATTERN :
        if( m_pLOBData->iPRIType == E_AET_PRI_PATTERN ) {
            switch( pABTData->iFreqPatternType ) {
                case E_AET_FREQ_PRI_UNKNOWN :
                    bRet = true;
                    break;

                case E_AET_FREQ_PRI_SINE :
                case E_AET_FREQ_PRI_SLIDE_INC :
                case E_AET_FREQ_PRI_SLIDE_DEC :
                case E_AET_FREQ_PRI_SAW_TRI :
                    if( m_pLOBData->iPRIPatternType == E_AET_FREQ_PRI_UNKNOWN ) {
                        bRet = true;
                    }
                    if( pABTData->iFreqPatternType == m_pLOBData->iPRIPatternType ) {
                        bRet = true;
                    }
                    break;

                default :
                    break;
            }
        }
        break;

// 	case E_AET_PRI_BEACON :
// 		if( m_pLOBData->iPRIType == E_AET_PRI_BEACON ) {
// 			bRet = true;
// 		}
// 		break;

    default :
        break;

    }

//     if( bRet == false ) {
//         m_LOBDataExt.aetAnal.eBeamCode = E_CREATE_PRI_TYPE_CODE;
//     }
    return bRet;
}

// /**
//  * @brief     스캔 형태 를 병합 비교한다. 스캔 형태가 UNKNOWN 이면 성공으로 리턴한다.
//  * @param     *pABTData 빔 정보의 데이터 포인터
//  * @return    병합이 정상이면 true, 그렇지 않으면 false
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-03-07, 오후 2:58
//  * @warning
//  */
// bool CELEmitterMergeMngr::CompScanType( SRxABTData *pABTData )
// {
// 	bool bRet=false;
//
// 	switch( pABTData->scanInfo.iType ) {
// 	case E_AET_SCAN_UNKNOWN :
// 		bRet = true;
//
// 	case E_AET_SCAN_TRACKING :
// 		if( m_pLOBData->iScanType == E_AET_SCAN_UNKNOWN || m_pLOBData->iScanType == E_AET_SCAN_TRACKING ) {
// 			bRet = true;
// 		}
// 		break;
//
// 	case E_AET_SCAN_SEARCH :
// 		if( m_pLOBData->iScanType == E_AET_SCAN_UNKNOWN || m_pLOBData->iScanType == E_AET_SCAN_SEARCH ) {
// 			bRet = true;
// 		}
// 		break;
//
// 	default :
// 		break;
//
// 	}
//
// 	return bRet;
// }
//
/**
 * @brief     주파수 범위를 비교하여 차이 값을 리턴한다.
 * @param     *pABTData 빔 정보의 데이터 포인터
 * @return    주파수 병합 차이
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-07, 오후 2:46
 * @warning
 */
int CELEmitterMergeMngr::CompFreqRange( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
{ //#FA_Q_4020_T1 (Msg(6:4020) Multiple exit points found.)
    BOOL bRet;

    //int iAgiFrq, iMopFreqDiff;
    float fDifferenceLevel=0;
    //UINT agiFrqIn, agiFrqOut;

    // Normal 신호 인 경우에는 주파수 정보를 보고 병합 판단
    if( pABTExtData->bCompFreq == true ) {
        switch( pABTData->iFreqType ) {
        case E_AET_FRQ_FIXED :
            // 주파수 변조폭인 경우에는 인트라 변화폭을 참조하여 병합
            bRet = CompMeanDiff<float>( pABTData->fFreqMean, m_pLOBData->fFreqMean, m_pSEnvironVariable->fMarginFrqError );

            if( bRet == _spFalse ) {
                return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
            }

            fDifferenceLevel = _diffabs<float>( pABTData->fFreqMean, m_pLOBData->fFreqMean );
            break;

        case E_AET_FRQ_AGILE :
        case E_AET_FRQ_PATTERN :
            fDifferenceLevel = _min( _abs( pABTData->fFreqMax - pABTData->fFreqMin ), _abs( m_pLOBData->fFreqMax - m_pLOBData->fFreqMin ) );

// 			agiFrqIn = _max( UDIV( (int)_sp.mg.agifrqin*iDifferenceLevel, 100), (UINT) _sp.mg.fixfrq[m_nFreqBand] );
// 			agiFrqOut = _max( UDIV( (int)_sp.mg.agifrqout*iDifferenceLevel, 100), (UINT) _sp.mg.fixfrq[m_nFreqBand] );
//
            // 패턴 대 패턴 비교
            if( pABTData->iFreqType == E_AET_FRQ_PATTERN && m_pLOBData->iFreqType == E_AET_FRQ_PATTERN ) {
// 				iAgiFrq = IDIV( (int) _sp.mg.frqPrd * _min( m_pLOBData->fFreqChangePeriod, pDInfo->fChangePeriodMin ), 100 );
// 				bRet = CompMarginDiff( m_pLOBData->fFreqChangePeriod, pDInfo->fChangePeriodMin, pDInfo->fChangePeriodMax, iAgiFrq );
// 				if( bRet == _spFalse && m_pLOBData->fFreqChangePeriod != 0 ) {
// 					return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
// 				}
// 	// 				bRet = CompMarginDiff( m_pLOBData->fFreqChangePeriod, pDInfo->fChangePeriodMin, pDInfo->fChangePeriodMax, _sp.mg.frqPrd );
// 	// 				if( bRet == _spFalse )
// 	// 					return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
//
// 				if( pDInfo->iPatternType != E_AET_FREQ_PRI_UNKNOWN ) {
// 					if( pDInfo->iPatternType != m_pLOBData->iFreqPatternType ) {
// 						return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
// 					}
// 				}
            }
            else {
// 				bRet = CompInOutDiff( pInfo->fMin, m_pLOBData->fFreqMin, (int) agiFrqIn, (int) agiFrqOut );
// 				if( bRet == _spFalse ) {
// 					return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
// 				}
//
// 				bRet = CompInOutDiff( pInfo->fMax, m_pLOBData->fFreqMax, (int) agiFrqIn, (int) agiFrqOut );
// 				if( bRet == _spFalse ) {
// 					return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
// 				}
            }
            break;

        case E_AET_FRQ_HOPPING :
            // 호핑 신호에 대한 병합 판단은 식별 정보를 이용하여 비교한다.
// 			pIDInfo = & m_LOBDataExt.aetAnal.idInfo;
// 			if( pIDInfo->nCoRadarModeIndex == 0 ) {
// 				// 미식별 경우에는 분석한 제원으로 비교한다.
// 				if( false == CompFreqPosition( pABTData ) ) {
// 					return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
// 				}
// 			}
// 			else {
// 				if( false == CompCEDFreqPosition() ) {
// 					return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
// 				}
// 			}
            break;

        default:
            break;

        }
    }

    //TRACE( "\n iDifferenceLevel[%d]" , iDifferenceLevel );
    return (int) ( fDifferenceLevel + 0.5 );
}
//
// /**
//  * @brief     CED 기반으로 호핑 레벨을 비교하여 병합 여부를 결정한다.
//  * @return    병합이 정상이면 true, 그렇지 않으면 false
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-03-07, 오후 5:25
//  * @warning
//  */
// bool CELEmitterMergeMngr::CompCEDFreqPosition()
// {
// 	{
// 		int i;
//
// 		bool bRet=true;
//
// 		STR_CEDEOBID_INFO *pIDInfo;
//
// 		char *pMopCode1;
// 		SRadarMode *pRadarMode;
//
// 		int iFreqSeq[MAX_FREQ_PRI_STEP];
//
// 		memset( iFreqSeq, 0, sizeof(iFreqSeq) );
//
// 		// 주파수 단 값을 10KHz 에서 1MHz 단위로 변환
// 		for( i=0 ; i < m_pLOBData->iFreqElementCount ; ++i ) {
// 			iFreqSeq[i] = _10KHZ_TO_1MHZ( m_pLOBData->iFreqSeq[i] );
// 		}
//
// 		pIDInfo = & m_LOBDataExt.aetAnal.idInfo;
//
// 		for( i=0 ; i < pIDInfo->nCoRadarModeIndex ; ++i ) {
// 			pRadarMode = m_theIdentifyAlg.GetRadarModeData( pIDInfo->nRadarModeIndex[i], m_pSEnvironVariable->eCEDDefaultLibType );
//
// 			if( pRadarMode == NULL ) { //DTEC_NullPointCheck
// 				LogPrint( "%d 번째 FREQ 병합 비교[%d]하는데서 문제가 발생했습니다.", i, pIDInfo->nRadarModeIndex[i] );
// 				bRet = false;
// 				break;			// return false;
// 			}
// 			else {
// 				pMopCode1 = pRadarMode->strModulationCode.GetBuffer();
//
// 				// B 코드가 아닐때만 호핑 레벨을 비교한다.
// 				if( *pMopCode1 != 'B' ) {
// 					for( auto iter = pRadarMode->mapRadarRF_Sequence.begin(); iter != pRadarMode->mapRadarRF_Sequence.end(); iter++ ) { //#FA_C_PotentialUnboundedLoop_T3
// 						SRadarRF_Sequence *pstSRadarRF_Sequence = & (*iter).second;
//
// 						SRadarRF_SequenceNumIndex *pRF_SequenceNumIndex;
// 						vector<SRadarRF_SequenceNumIndex> *pvecRF_NumIndex;
//
// 						pvecRF_NumIndex = & pstSRadarRF_Sequence->vecRF_NumIndex;
// 						pRF_SequenceNumIndex = & pvecRF_NumIndex->at(0);
//
// 						if( FALSE == m_theIdentifyAlg.CompSwitchLevel( iFreqSeq, & pRadarMode->vecRadarRF_Values, pRF_SequenceNumIndex, (UINT) m_pLOBData->iFreqElementCount ) ) {
// 							bRet = false;
// 							break;
// 						}
// 					}
// 				}
// 			}
//
// 		}
//
// 		return bRet;
// 	}
// }
//
// /**
//  * @brief     CED 호핑 엘리먼트에 있는 데이터를 갖고와서 병합 비교한다.
//
//  * @return    병합이 정상이면 true, 그렇지 않으면 false
//
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-03-08, 오전 11:32
//  * @warning
//  */
// bool CELEmitterMergeMngr::CompCEDPRIPosition()
// {
// 	int i;
//
// 	bool bRet=true;
//
// 	STR_CEDEOBID_INFO *pIDInfo;
//
// 	SRadarMode *pRadarMode;
//
// 	pIDInfo = & m_LOBDataExt.aetAnal.idInfo;
//
// 	for( i=0 ; i < pIDInfo->nCoRadarModeIndex ; ++i ) {
// 		pRadarMode = m_theIdentifyAlg.GetRadarModeData( pIDInfo->nRadarModeIndex[i], m_pSEnvironVariable->eCEDDefaultLibType );
//
// 		if( pRadarMode == NULL ) { //DTEC_NullPointCheck
// 			LogPrint( "%d 번째 PRI 병합 비교[%d]하는데서 문제가 발생했습니다.", i, pIDInfo->nRadarModeIndex[i] );
// 			bRet = false;
// 			break;		// return false;
// 		}
// 		else {
// 			for( auto iter = pRadarMode->mapRadarPRI_Sequence.begin(); iter != pRadarMode->mapRadarPRI_Sequence.end(); iter++ ) { //#FA_C_PotentialUnboundedLoop_T3
// 				SRadarPRI_Sequence *pstSRadarPRI_Sequence = & (*iter).second;
//
// 				SRadarPRI_SequenceNumIndex *pPRI_SequenceNumIndex;
// 				vector<SRadarPRI_SequenceNumIndex> *pvecPRI_NumIndex;
//
// 				pvecPRI_NumIndex = & pstSRadarPRI_Sequence->vecPRI_NumIndex;
// 				pPRI_SequenceNumIndex = & pvecPRI_NumIndex->at(0);
//
// 				//bRet = m_theIdentifyAlg.CompSwitchLevel( m_pLOBData->iPRISeq, & pRadarMode->vecRadarPRI_Values, pPRI_SequenceNumIndex, m_pLOBData->iPRIPositionCount );
// 				if( m_theIdentifyAlg.CompSwitchLevel( m_pLOBData->iPRISeq, m_pLOBData->iPRIPositionCount, & pRadarMode->vecRadarPRI_Values, pPRI_SequenceNumIndex, m_pLOBData->iPRIPositionCount ) == FALSE ) {
// 					bRet = false;
// 					break;
// 				}
// 			}
// 		}
//
// 	}
//
// 	return bRet;
// }
//
// #define THRESHOLD_OF_HOPPING_MATCH_RATIO	(50)
// /**
//  * @brief     주파수 호필 레벨을 비교 하여 병합 비교한다.
//  * @param     *pABTData 빔 정보의 데이터 포인터
//  * @return    병합이 정상이면 true, 그렇지 않으면 false
//
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-03-07, 오후 4:54
//  * @warning
//  */
// bool CELEmitterMergeMngr::CompFreqPosition( SRxABTData *pABTData )
// {
// 	int i, j;
// 	int comp_val, *pVal;
//
// 	bool bRet=false;
//
// 	int iMatch=0, iDivide, iThreshold;
//
// 	for( i=0 ; ( i < m_pLOBData->iFreqPositionCount ) && ( i < MAX_FREQ_PRI_STEP ) ; ++i ) {
// 		comp_val = m_pLOBData->iFreqSeq[i];
//
// 		pVal = pABTData->freqDInfo.iSeq;
// 		for( j=0 ; j < pABTData->freqDInfo.iPositionCount ; ++j ) {
// 			if( _spTrue == CompMeanDiff( comp_val, *pVal, (int) _sp.mg.fixfrq[m_nFreqBand] ) ) {
// 				++ iMatch;
// 				break;
// 			}
// 			++ pVal;
// 		}
// 	}
//
// 	//iDivide = _min( m_pLOBData->iFreqElementCount, pABTData->freqDInfo.iElementCount );
// 	iDivide = m_pLOBData->iFreqPositionCount;
// 	if( iMatch != 0 ) {
// 		iThreshold = IDIV( ( iMatch * 100 ), iDivide );
// 		if( iThreshold > THRESHOLD_OF_HOPPING_MATCH_RATIO ) {
// 			bRet = true;
// 		}
// 	}
//
// 	return bRet;
// }
//

#define THRESHOLD_OF_DWELL_MATCH_RATIO	(50)
/**
 * @brief     DWELL 레벨을 비교 하여 병합 비교한다.
 * @param     *pABTData 빔 정보의 데이터 포인터
 * @return    병합이 정상이면 true, 그렇지 않으면 false

 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-07, 오후 4:54
 * @warning
 */
bool CELEmitterMergeMngr::CompPRIPosition( SRxABTData *pABTData )
{
    bool bRet=false;

    if( pABTData->iPRIPositionCount == m_pLOBData->iPRIPositionCount ) {
        if( TRUE == CompSwitch2Level<float>( pABTData->fPRISeq, m_pLOBData->fPRISeq, pABTData->iPRIPositionCount, m_pLOBData->iPRIPositionCount, m_pSEnvironVariable->fMarginPriError ) ) {
            bRet = true;
        }
    }

    return bRet;
}
//
//
/**
 * @brief     PRI 범위 비교하여 병합 여부를 판단한다.
 * @param     *pABTData 빔 정보의 데이터 포인터
 * @return    PRI 병합 차이
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-08, 오전 9:51
 * @warning
 */
int CELEmitterMergeMngr::CompPRIRange( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
{ //#FA_Q_4020_T1 (Msg(6:4020) Multiple exit points found.)
    BOOL bRet;

    float fAgiPri;
    float fDifferenceLevel=0;

    //int iOverlapValue;
    float fOverlapSpace, fOverlapSpaceRatio, fTotalRange;

    STR_CEDEOBID_INFO *pIDInfo;

    //STR_FREQ_PRI_PW_PA_INFO *pInfo = & pABTData->priInfo;
    //STR_FREQ_PRI_DINFO *pDInfo = & pABTData->priDInfo;

    if( pABTExtData->bCompPRI == true ) {
        switch( pABTData->iPRIType ) {
        case E_AET_PRI_FIXED :
            bRet = CompMeanDiff<float>( pABTData->fPRIMean, m_pLOBData->fPRIMean, m_pSEnvironVariable->fMarginPriError );
            if( bRet == _spFalse ) {
                return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
            }

            fDifferenceLevel = _diffabs<float>( pABTData->fPRIMean, m_pLOBData->fPRIMean );
            break;

        case E_AET_PRI_JITTER :
            switch( m_pLOBData->iPRIType ) {
            case E_AET_PRI_JITTER :
                /*! \debug  지터율 비교 무시 - 항공에서 잘못된 지터율을 계산해서 무시하게 함.
                        \author 조철희 (churlhee.jo@lignex1.com)
                        \date 	2017-12-21 10:18:32
                */
    // 					bRet = CompMeanDiff( pDInfo->fPRIJitterRatio, m_pLOBData->fPRIJitterRatio, _sp.mg.jtrper*10 );
    // 					if( bRet == _spFalse ) {
    // 						return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
    // 					}

                /*! \todo   PRI 값도 확인해야 해서 break 문이 없음.
                        \author 조철희 (churlhee.jo@lignex1.com)
                        \date 	2016-07-18 20:26:07
                */
    // 					bRet = IsOverlapSpace( pDInfo->fMin, m_optParameter.pri.fMax, m_pLOBData->fPRIMin, m_pLOBData->fPRIMax, m_optParameter.pri.iOverlapRatio );
    // 					if( bret == _spFalse ) {
    // 						return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
    // 					}
    // 					break;
                if( false == IsOverlapSpace<float>( m_pLOBData->fPRIMin, m_pLOBData->fPRIMax, pABTData->fPRIMin, pABTData->fPRIMax, (float) 0 ) ) {
                    return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
                }
                else {
                    fOverlapSpace = CalOverlapSpace<float>( m_pLOBData->fPRIMax, m_pLOBData->fPRIMin, pABTData->fPRIMax, pABTData->fPRIMin );
                    fTotalRange = min( m_pLOBData->fPRIMax-m_pLOBData->fPRIMin, pABTData->fPRIMax-pABTData->fPRIMin );
                    fOverlapSpaceRatio = FDIV( fOverlapSpace * 100, fTotalRange );

                    if( fOverlapSpaceRatio < m_pSEnvironVariable->fMarginMinRqdPriRangeNestedRatio ) {
                        return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
                    }

// 					iOverlapValue = IDIV( m_pSEnvironVariable->fMarginMinRqdPriRangeNestedRatio * ( pABTData->fPRIMax - pABTData->fPRIMin ), 100 );
// 					if( false == m_pIdentifyAlg->IsOverlapSpace( m_pLOBData->fPRIMin, m_pLOBData->fPRIMax, pABTData->fPRIMin, pABTData->fPRIMax, (float) iOverlapValue ) ) {
// 						return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
// 					}
//
// 					iOverlapValue = IDIV( m_pSEnvironVariable->fMarginMinRqdPriRangeNestedRatio * ( m_pLOBData->fPRIMax - m_pLOBData->fPRIMin ), 100 );
// 					if( false == m_pIdentifyAlg->IsOverlapSpace( pABTData->fPRIMin, pABTData->fPRIMax, m_pLOBData->fPRIMin, m_pLOBData->fPRIMax, (float) iOverlapValue ) ) {
// 						return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
// 					}
                }

                //iDifferenceLevel = CalOverlapSpace( m_pLOBData->fPRIMax, m_pLOBData->fPRIMin, (int) pInfo->fMax, (int) pInfo->fMin );
                //iDifferenceLevel = _diffabs( pInfo->iMean, m_pLOBData->fPRIMean );
                //iDifferenceLevel = 0;
                break;

            case E_AET_PRI_STAGGER :
            case E_AET_PRI_PATTERN :
                fDifferenceLevel = _min( pABTData->fPRIMean, m_pLOBData->fPRIMean );

                fAgiPri = _max( pABTData->fPRIJitterRatio, m_pLOBData->fPRIJitterRatio );
                fAgiPri = _max( FDIV( fAgiPri * fDifferenceLevel, 100.), m_pSEnvironVariable->fMarginFrqError );
                if( _spFalse == CompMeanDiff( pABTData->fPRIMin, m_pLOBData->fPRIMin, fAgiPri ) ) {
                    return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
                }
                if( _spFalse == CompMeanDiff( pABTData->fPRIMax, m_pLOBData->fPRIMax, fAgiPri ) ) {
                    return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
                }

                fDifferenceLevel = _abs( pABTData->fPRIMin - m_pLOBData->fPRIMin ) + _abs( pABTData->fPRIMax - m_pLOBData->fPRIMax );
                break;

            default :
                break;
            }
            break;

        case E_AET_PRI_DWELL_SWITCH :
            // Dwell&Switch 신호에 대한 병합 판단은 식별 정보를 이용하여 비교한다.
            pIDInfo = & m_LOBDataExt.aetAnal.idInfo;

// 			if( m_pLOBData->iPRIElementCount != pDInfo->iElementCount ) {
// 				return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
// 			}

            // 미식별 경우에는 분석한 제원으로 비교한다.
            if( false == CompPRIPosition( pABTData ) ) {
                return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
            }

            //iDifferenceLevel = 0;
            break;

        case E_AET_PRI_STAGGER :
            if( m_pLOBData->iPRIType == E_AET_PRI_STAGGER ) {
                // 스태거 레벨 비교
// 				if( m_pLOBData->iPRIElementCount != pDInfo->iElementCount || m_pLOBData->iPRIPositionCount != pDInfo->iPositionCount ) {
// 					return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
// 				}
                // iDifferenceLevel = 0;

                bRet = m_pIdentifyAlg->CompSwitchLevel<float>( m_pLOBData->fPRISeq, pABTData->fPRISeq, m_pLOBData->iPRIPositionCount, m_pSEnvironVariable->fMarginPriError );
                if( bRet == _spFalse ) {
                    return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
                }

                /*! \todo		각 레벨간의 차이는 나중에 계산한다. 현재는 0 으로 리턴한다.
                        \author 조철희 (churlhee.jo@lignex1.com)
                        \date 	2016-03-8 17:10:02
                */
                return (int) ( fDifferenceLevel + 0.5 );
            }
            else if( m_pLOBData->iPRIType == E_AET_PRI_JITTER ) {
                fAgiPri = _max( pABTData->fPRIJitterRatio, m_pLOBData->fPRIJitterRatio );
                fAgiPri = _max( FDIV( fAgiPri * fDifferenceLevel, 100. ), m_pSEnvironVariable->fMarginFrqError );
                if( _spFalse == CompMarginDiff<float>( m_pLOBData->fPRIMin, pABTData->fPRIMin, pABTData->fPRIMax, fAgiPri ) ) {
                    return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
                }
                if( _spFalse == CompMarginDiff<float>( m_pLOBData->fPRIMax, pABTData->fPRIMin, pABTData->fPRIMax, fAgiPri ) ) {
                    return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
                }
                fDifferenceLevel = _abs( m_pLOBData->fPRIMin - pABTData->fPRIMin ) + _abs( m_pLOBData->fPRIMax - pABTData->fPRIMax );
                return (int) ( fDifferenceLevel + 0.5 );
            }
            else {

            }
            break;

        case E_AET_PRI_PATTERN :
            if( m_pLOBData->iPRIType == E_AET_PRI_PATTERN ) {
                fAgiPri = FDIV( m_pSEnvironVariable->fMarginPriModPeriodErrorRatio * _min( m_pLOBData->fPRIPatternPeriod, pABTData->fPRIPatternPeriodMean ), 100. );
                bRet = CompMarginDiff<float>( m_pLOBData->fPRIPatternPeriod, pABTData->fPRIPatternPeriodMin, pABTData->fPRIPatternPeriodMax, (float) fAgiPri );
                if( bRet == _spFalse && m_pLOBData->fPRIPatternPeriod != 0 ) {
                    return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
                }

                fAgiPri = _min( _abs( pABTData->fPRIMax - pABTData->fPRIMin ), _abs( m_pLOBData->fPRIMax - m_pLOBData->fPRIMin ) );
                fAgiPri = _max( FDIV( m_pSEnvironVariable->fMarginPriModPeriodErrorRatio*fAgiPri, 100), (float) m_pSEnvironVariable->fMarginPriError );
                bRet = CompMeanDiff( pABTData->fPRIMean, m_pLOBData->fPRIMean, fAgiPri );
                if( bRet == _spFalse ) {
                    return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
                }

                fDifferenceLevel = _abs( m_pLOBData->fPRIMin - pABTData->fPRIMin ) + _abs( m_pLOBData->fPRIMax - pABTData->fPRIMax );

            }
            else if( m_pLOBData->iPRIType == E_AET_PRI_JITTER ) {
                if( _spFalse == CompMarginDiff<float>( m_pLOBData->fPRIMin, pABTData->fPRIMin, pABTData->fPRIMax, m_pSEnvironVariable->fMarginFrqError ) ) {
                    return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
                }
                if( _spFalse == CompMarginDiff<float>( m_pLOBData->fPRIMax, pABTData->fPRIMin, pABTData->fPRIMax, m_pSEnvironVariable->fMarginFrqError ) ) {
                    return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
                }

                fDifferenceLevel = _abs( m_pLOBData->fPRIMin - pABTData->fPRIMin ) + _abs( m_pLOBData->fPRIMax - pABTData->fPRIMax );
                return (int) ( fDifferenceLevel + 0.5 );
            }
            else {

            }
            break;

// 		case E_AET_PRI_BEACON :
// 			if( m_pLOBData->iPRIType == E_AET_PRI_BEACON ) {
// 				if( m_pLOBData->iPulsePerGrp == pABTData->pulseDInfo.iPulsePerGrp ) {
// 					/*! \todo		현재는 PRI MIN, MAX 값 범위를 비교하여 병합 비교한다.
// 							\author 조철희 (churlhee.jo@lignex1.com)
// 							\date 	2016-03-8 16:49:02
// 					*/
// 					if( _spFalse == CompMarginDiff( m_pLOBData->fPRIMin, pInfo->fMin, pInfo->fMax, (int) m_pSEnvironVariable->fMarginFrqError ) ) {
// 						return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
// 					}
// 					if( _spFalse == CompMarginDiff( m_pLOBData->fPRIMax, pInfo->fMin, pInfo->fMax, (int) m_pSEnvironVariable->fMarginFrqError ) ) {
// 						return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
// 					}
//
// 					iDifferenceLevel = _abs( m_pLOBData->fPRIMin - pInfo->fMin ) + _abs( m_pLOBData->fPRIMax - pInfo->fMax );
// 					return iDifferenceLevel;
// 				}
// 			}
// 			break;
        default:
            break;

        }
    }

    return (int) ( fDifferenceLevel + 0.5 );
}

/**
 * @brief     빔 정보들간의 펄스폭 병합 비교를 수행한다.
 * @param     *pABTData 빔 정보의 데이터 포인터
 * @return    펄스폭 병합 차이

 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-08, 오후 5:18
 * @warning
 */
int CELEmitterMergeMngr::CompPWRange( SRxABTData *pABTData )
{
    // BOOL bRet;
    int iDifferenceLevel=0;

// 	bRet = CompMeanDiff( pABTData->pwInfo.fMin, m_pLOBData->fPWMin, _sp.mg.pw );
// 	if( bRet == _spFalse )
// 		return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
// 	bRet = CompMeanDiff( pABTData->pwInfo.fMax, m_pLOBData->fPWMax, _sp.mg.pw );
// 	if( bRet == _spFalse )
// 		return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
//
// 	iDifferenceLevel = _abs( m_pLOBData->fPWMin - pABTData->pwInfo.fMin ) + _abs( m_pLOBData->fPWMax - pABTData->pwInfo.fMax );
    return iDifferenceLevel;
}

// /**
//  * @brief     빔 정보들간의 스캔주기 병합 비교를 수행한다.
//  * @param     *pABTData 빔 정보의 데이터 포인터
//  * @return    스캔주기 병합 차이
//
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-03-08, 오후 5:31
//  * @warning
//  */
// int CELEmitterMergeMngr::CompScanRange( SRxABTData *pABTData )
// {
// 	BOOL bRet;
// 	int diff;
// 	int iDifferenceLevel=0;
//
// 	// 탐지형일 떄만 주기 범위를 비교하게 함.
// 	if( pABTData->scanInfo.iType == E_AET_SCAN_SEARCH || pABTData->scanInfo.iType == E_AET_SCAN_SECTOR ) {
// 		diff = IDIV( ( m_pLOBData->iScanPeriod * m_pSEnvironVariable->fMarginScanPeriodErrorRatio ), 100 );
// 		bRet = CompMarginDiff( m_pLOBData->iScanPeriod, pABTData->scanInfo.iPeriodMin, pABTData->scanInfo.iPeriodMax, diff );
// 		if( bRet == _spFalse ) {
// 			// return THRESHOLD_OF_MIN_CANDIDATE_LEVEL;
// 		}
// 		else {
// 			iDifferenceLevel = _abs( m_pLOBData->iScanPeriod - pABTData->scanInfo.iPeriodMin ) +
// 												_abs( m_pLOBData->iScanPeriod - pABTData->scanInfo.iPeriodMax );
// 		}
// 	}
//
// 	return iDifferenceLevel;
// }

/**
 * @brief			빔 방탐 유효성을 병합 비교한다.
 * @param     SRxABTData * pABTData 빔 데이터
 * @return    int 병합도
 * @return    성공시 true, 실패시 false
*/
int CELEmitterMergeMngr::CompValid( SRxABTData *pABTData )
{
    int iDifferenceLevel=0;

    if( pABTData->iValidity == 1 ) {
        // iDifferenceLevel = 0;
    }
    else {
        iDifferenceLevel = 100;
    }

    return iDifferenceLevel;
}

/**
 * @brief     빔과 LOB의 거리 병합을 계산한다.
 * @param     SRxABTData * pABTData 비교할 빔 데이터
 * @return    int 병합도
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-07-25, 오후 12:49
 * @warning
 */
float CELEmitterMergeMngr::CompDistRange( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
{
    float fDifferenceLevel=0;

    if( m_bScanProcess == true ) {

    }
    else {
        switch( pABTExtData->enValid ) {
        case E_EL_PESTAT_FAIL :
            fDifferenceLevel = PE_CANDIDATE_LEVEL;
            break;

        case E_EL_PESTAT_SUCCESS :
            if( pABTData->iValidity == false ) {
                fDifferenceLevel = PE_CANDIDATE_LEVEL;
            }
            else {
                fDifferenceLevel = _min( pABTData->fCEP, PE_CANDIDATE_LEVEL );
            }
            break;

        case E_EL_PESTAT_NOT_YET :
            fDifferenceLevel = PE_CANDIDATE_LEVEL;
            break;

        case E_EL_PESTAT_IMPOSSIBILITY :
            fDifferenceLevel = PE_CANDIDATE_LEVEL;
            break;

        default:
            break;

        }
    }

    return fDifferenceLevel;
}

// /**
//  * @brief     링크 번호를 비교한다.
//  * @param     *pABTExtData 빔 추가 정보의 데이터 포인터
//  * @return    병합이 정상이면 true, 그렇지 않으면 false
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-04-04, 오후 6:44
//  * @warning
//  */
// bool CELEmitterMergeMngr::CompLinkNum( SELABTDATA_EXT *pABTExtData )
// {
// 	bool bRet=false;
//
// 	// 링크 번호 비교
// 	if( pABTExtData->iLinkNum == m_nLinkNum ) {
// 		bRet = true;
// 	}
//
// 	return bRet;
// }
//
/**
 * @brief     위협 관리하고 ABT와 수신한 LOB와 신호 형태를 비교 여부를 참 또는 거짓을 리턴한다.
 * @param     *pABTData 빔 정보의 데이터 포인터
 * @return    병합이 정상이면 true, 그렇지 않으면 false
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-07, 오후 1:26
 * @warning
 */
bool CELEmitterMergeMngr::CompEmitterInfo( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
{
    bool bRet=false;

    if( m_bScanProcess == true ) {
        bRet = ( pABTData->uiABTID == m_pLOBData->uiABTID );
    }
    else {
        if( ( true == CompSigType( pABTData ) ) /* && ( true == CompIntraType( pABTData ) ) */ && ( true == CompFreqType( pABTData ) ) && ( true == CompPRIType( pABTData ) ) /* && ( true == CompScanType( pABTData ) ) */ ) {
            bRet = true;
        }
    }

    return bRet;
}

/**
 * @brief     위협 관리하고 ABT와 수신한 LOB와 신호 형태를 비교 여부를 참 또는 거짓을 리턴한다.
 * @param     *pABTData 빔 정보의 데이터 포인터
 * @return    병합이 정상이면 true, 그렇지 않으면 false
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-07, 오후 1:26
 * @warning
 */
bool CELEmitterMergeMngr::CompSigType( SRxABTData *pABTData )
{
    bool bRet=true;

    // 신호형태 비교
    if( pABTData->iSignalType != m_pLOBData->iSignalType ) {
        bRet = false;
        m_LOBDataExt.aetAnal.eBeamCode = E_CREATE_SIGNAL_TYPE_CODE;
    }

    // 그룹펄스 내 펄스 수 비교
// 	if( m_pLOBData->iPulsePerGrp != 0 && pABTData->pulseDInfo.iPulsePerGrp != m_pLOBData->iPulsePerGrp ) {
// 		bRet = false;
// 	}

    return bRet;
}

// /**
//  * @brief     과제 형태 비교를 수행한다.
//  * @param     *pABTExtData 빔 추가 정보의 데이터 포인터
//  * @return    병합이 정상이면 true, 그렇지 않으면 false
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-04-22, 오후 10:07
//  * @warning
//  */
// bool CELEmitterMergeMngr::CompTaskType( SELABTDATA_EXT *pABTExtData, bool bMerge )
// {
// 	bool bRet=false;
// 	int iABTTaskType, iLOBTaskType;
//
// 	iABTTaskType = pABTExtData->iTaskType;
// 	iLOBTaskType = m_pLOBData->iTaskType / 2;
//
// 	if( bMerge == true ) {
// 		if( iLOBTaskType == E_EL_TASK_SRCH ) {
// 			if( iABTTaskType == iLOBTaskType ) {
// 				bRet = true;
// 			}
// 		}
//
// 	}
// 	else {
// 		// 탐지 과제일때는
// 		if( iLOBTaskType == E_EL_TASK_SRCH ) {
// 			if( iABTTaskType == iLOBTaskType ) {
// 				bRet = true;
// 			}
// 		}
// 		// 고감도 과제일때는 링크 번호 참조하여 병합 비교 수행
// 		else {
// 			if( pABTExtData->iLinkNum == m_nLinkNum ) {
// 				if( iABTTaskType == iLOBTaskType ) {
// 					bRet = true;
// 				}
// 			}
// 		}
// 	}
//
// 	return bRet;
// }
//
/**
 * @brief     식별 결과를 비교한다.
 * @param     *pABTExtData 빔 추가 정보의 데이터 포인터
 * @return    병합이 정상이면 true, 그렇지 않으면 false
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-04-22, 오후 10:07
 * @warning
 */
bool CELEmitterMergeMngr::CompIDInfo( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
{
    bool bRet = true;

    if( m_bScanProcess == true ) {
        bRet = ( pABTData->uiABTID == m_pLOBData->uiABTID );
    }
    else {

    }
/*

// 	if( ( true == pABTExtData->stLOBOtherInfo.bUpdate ) || ( bOnlyCheckID == true ) ) {
// 		SLOBOtherInfo *pSLOBOtherInfo;
//
// 		if( m_pLOBOtherInfo->bUpdate == true ) {
// 			//GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_MSG, E_WARNING_NONE, enumGMEO_DEVICE, enumGMEI_DEVICE, "CompIDInfo() 처리 수행(%d, %d)", pABTExtData->stLOBOtherInfo.bUpdate, bOnlyCheckID );
// 			pSLOBOtherInfo = & pABTExtData->stLOBOtherInfo;
// 			if( strcmp( pSLOBOtherInfo->szElnotPri, m_pLOBOtherInfo->szElnotPri ) == 0 && \
// 			    strcmp( pSLOBOtherInfo->szModeCodePri, m_pLOBOtherInfo->szModeCodePri ) == 0 &&
// 			    strcmp( pSLOBOtherInfo->szModulationCode, m_pLOBOtherInfo->szModulationCode ) == 0 &&
// 			    strcmp( pSLOBOtherInfo->szNickName, m_pLOBOtherInfo->szNickName ) == 0 &&
// 			    strcmp( pSLOBOtherInfo->szPriFuncCode, m_pLOBOtherInfo->szPriFuncCode ) == 0 &&
// 			    strcmp( pSLOBOtherInfo->szElnotSec, m_pLOBOtherInfo->szElnotSec ) == 0 &&
// 			    strcmp( pSLOBOtherInfo->szModeCodeSec, m_pLOBOtherInfo->szModeCodeSec ) == 0 &&
// 			    strcmp( pSLOBOtherInfo->szElnotTert, m_pLOBOtherInfo->szElnotTert ) == 0 &&
// 			    strcmp( pSLOBOtherInfo->szModeCodeTert, m_pLOBOtherInfo->szModeCodeTert ) == 0 ) {
// 				// 위협 정보를 비교하여 업데이트 하려면 true 로 함.
// 				// bRet = true;
// 				bRet = false;
// 			}
// 			else {
// 				bRet = false;
// 			}
// 		}
//
// 	}
*/
    return bRet;
}

/**
 * @brief     CompELNOTInfo
 * @param     SRxABTData * pABTData
 * @param     SELABTDATA_EXT * pABTExtData
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-04-05, 오후 8:57
 * @warning
 */
bool CELEmitterMergeMngr::CompELNOTInfo( SELMERGE_CANDIDATE *pMergeCandidate, SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
{
    bool bRet=true;

    if( m_bScanProcess == true ) {
    }
    else {
        /*! \bug	지터 신호에 대해서 식별 정보를 참조
            \author 조철희 (churlhee.jo@lignex1.com)
            \date 	2018-01-15 11:00:32
        */
        if( pABTData->iPRIType == E_AET_PRI_JITTER && m_pLOBData->iPRIType == E_AET_PRI_JITTER ) {
            if( pABTExtData->idInfo.nRadarModeIndex[0] > _spZero && ( pABTExtData->idInfo.nRadarModeIndex[0] == m_LOBDataExt.aetAnal.idInfo.nRadarModeIndex[0] ) ) {
                pMergeCandidate->fLevel += CompFreqRange( pABTData, pABTExtData );
                //pMergeCandidate->fLevel += CompPRIRange( pABTData );
                pMergeCandidate->fLevel += CompPWRange( pABTData );
                //pMergeCandidate->fLevel += CompScanRange( pABTData );

                bRet = true;
            }
            else {
                pMergeCandidate->fLevel += CompFreqRange( pABTData, pABTExtData );
                pMergeCandidate->fLevel += CompPRIRange( pABTData, pABTExtData );
                pMergeCandidate->fLevel += CompPWRange( pABTData );
                //pMergeCandidate->fLevel += CompScanRange( pABTData );

                bRet = true;
            }
        }
        else {
            // 기본적인 병합 비교는 제원 비교를 수행한다.
            pMergeCandidate->fLevel += CompFreqRange( pABTData, pABTExtData );
            pMergeCandidate->fLevel += CompPRIRange( pABTData, pABTExtData );
            pMergeCandidate->fLevel += CompPWRange( pABTData );
            //pMergeCandidate->fLevel += CompScanRange( pABTData );

            bRet = true;
        }
    }

    return bRet;
}

/**
 * @brief     CompIDELNOTInfo
 * @param     SRxABTData * pABTData
 * @param     SELABTDATA_EXT * pABTExtData
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-04-12, 오후 9:21
 * @warning
 */
bool CELEmitterMergeMngr::CompIDELNOTInfo( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
{
    bool bRet=true;

    if( m_bScanProcess == true ) {
        bRet = ( pABTData->uiABTID == m_pLOBData->uiABTID );
    }
    else {
        // 1. 빔 식별과 LOB 미식별 된 것은 병합 하지 말것
        if( pABTData->iRadarModeIndex != m_pLOBData->iRadarModeIndex ) {
            bRet = false;
        }
    }

    return bRet;
}

/**
 * @brief     슬레이브 연동기에서 위협 관리된 LOB 정보를 읽어들인다.
 * @param     *pVecLOBData LOB 헤더 정보의 데이터 포인터
 * @param     *pVecLOBGrp LOB 데이터 정보의 데이터 포인터
 * @param     nLinkNum 링크 번호
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-04-11, 오후 8:44
 * @warning
 */
// void CELEmitterMergeMngr::FetchLOBData_LINK2( std::vector<SRxLOBData> *pVecLOBData, std::vector<SRxLOBDataGroup> *pVecLOBGrp, std::vector<int> *pVecLinkNum )
// {
// 	bool bRet=false;
// 	char szQuery[500];
// 	SELEXTDB extDB=SELEXTDB();
//
// 	CString strQuery;
// 	CString strTemp, strQueryLOB;
//
// 	UINT i,	uSize;
//
// 	//DWORD dwTime = GetTickCount();
//
// 	// 링크 2 로부터 데이터를 갖고 올때 아래를 처리를 수행한다.
// 	strQuery = "select A.SEQ_NUM, A.HOUR, A.MIN, A.SEC, A.ACQ_TIME, A.LINK_NUM, A.MISSION_ID, A.MISSION_NAME, A.TASK_ID, A.TASK_NAME, A.TASK_TYPE, A.SEARCH_BAND_ID, A.RXPATH, A.ANTDIRECTION, \
// 						 A.LOB_ID, A.ABT_ID, A.AET_ID, NVL(A.ELNOT_PRIM, '-') , A.MODE_CODE_PRIM, NVL(A.ELNOT_SECON,'-'), NVL(A.MODE_CODE_SECON,'-'), NVL(A.ELNOT_TERT,'-'), NVL(A.MODE_CODE_TERT,'-'), A.MODULATION_CODE, NVL( A.NICK_NAME, '-'), \
// 						 NVL(A.PRIM_FUNC_CODE,'-'), A.SIG_TYPE, A.POLIZATION, A.RATIOOFPOL, A.FISINTTASK, A.NUM_OF_PULSE_GRP, A.NUM_OF_PULSES, A.BL_STAT, A.FOV, A.DOA_MEAN, A.DOA_MIN, A.DOA_MAX, \
// 						 A.DOA_DEV, A.DOA_STD, A.DI_RATIO, A.FRQ_TYPE, A.FRQ_PATTN_TYPE, A.HAS_FRQ_MOD_PRD, A.FRQ_CHNG_PRD, \
// 						 A.NUM_OF_FRQ_POSITION, A.NUM_OF_FRQ_ELEMENT, A.FRQ_MEAN, A.FRQ_MAX, A.FRQ_MIN,  A.FRQ_DEV, A.PRI_TYPE, \
// 						 A.PRI_PATTN_TYPE, A.HAS_PRI_MOD_PRD, A.PRI_MOD_PRD, A.NUM_OF_PRI_POSITION, A.NUM_OF_PRI_ELEMENT, \
// 						 A.PRI_MEAN, PRI_MAX, A.PRI_MIN, A.PRI_DEV, A.PRI_JITTER_RTO, A.PW_MEAN, A.PW_MIN, A.PW_MAX, A.PW_DEV, \
// 						 A.PA_MEAN, A.PA_MIN, A.PA_MAX, A.PA_DEV, A.SCAN_TYPE, A.SCAN_TYPE_DETAIL, A.SCAN_PRD, A.INTRA_TYPE, \
// 						 A.INTRA_TYPE_DETAIL, A.INTRA_FRQ_MEAN, A.INTRA_FRQ_MIN, A.INTRA_FRQ_MAX, A.INTRA_FRQ_DEVIATION, \
// 						 A.AIRCRAFT_LAT, A.AIRCRAFT_LONG, A.AIRCRAFT_PITCH, A.AIRCRAFT_ROLL, A.AIRCRAFT_HEADING, A.AIRCRAFT_ALT, \
// 						 A.AIRCRAFT_FOM, A.IS_PDW_RESTORE, A.IS_IQ_RESTORE, A.IS_FILTERED, A.IS_MANUAL_INPUT, A.IS_VALIDITY, \
// 						 A.IS_CHECKPOSITION, A.FINAL_RPT_TIME, A.FIRST_RPT_TIME, A.ALOB_ID, A.AABT_ID, A.AAET_ID, A.EL_STAT, A.RCV_TIME, \
// 						 NVL(B.DATA_TYPE,'0'), NVL(B.ELEMENTS,'0'), NVL(B.SEQ_01,'0'), NVL(B.SEQ_02,'0'), NVL(B.SEQ_03,'0'), NVL(B.SEQ_04,'0'), NVL(B.SEQ_05,'0'), NVL(B.SEQ_06,'0'), NVL(B.SEQ_07,'0'), NVL(B.SEQ_08,'0'), NVL(B.SEQ_09,'0'), NVL(B.SEQ_10,'0'), \
// 						 NVL(B.SEQ_11,'0'), NVL(B.SEQ_12,'0'), NVL(B.SEQ_13,'0'), NVL(B.SEQ_14,'0'), NVL(B.SEQ_15,'0'), NVL(B.SEQ_16,'0'), NVL(B.SEQ_17,'0'), NVL(B.SEQ_18,'0'), NVL(B.SEQ_19,'0'), NVL(B.SEQ_20,'0'), \
// 						 NVL(B.SEQ_21,'0'), NVL(B.SEQ_22,'0'), NVL(B.SEQ_23,'0'), NVL(B.SEQ_24,'0'), NVL(B.SEQ_25,'0'), NVL(B.SEQ_26,'0'), NVL(B.SEQ_27,'0'), NVL(B.SEQ_28,'0'), NVL(B.SEQ_29,'0'), NVL(B.SEQ_30,'0'), \
// 						 NVL(B.SEQ_31,'0'), NVL(B.SEQ_32,'0'), NVL(B.SEQ_33,'0'), NVL(B.SEQ_34,'0'), NVL(B.SEQ_35,'0'), NVL(B.SEQ_36,'0'), NVL(B.SEQ_37,'0'), NVL(B.SEQ_38,'0'), NVL(B.SEQ_39,'0'), NVL(B.SEQ_40,'0'), \
// 						 NVL(B.SEQ_41,'0'), NVL(B.SEQ_42,'0'), NVL(B.SEQ_43,'0'), NVL(B.SEQ_44,'0'), NVL(B.SEQ_45,'0'), NVL(B.SEQ_46,'0'), NVL(B.SEQ_47,'0'), NVL(B.SEQ_48,'0'), NVL(B.SEQ_49,'0'), NVL(B.SEQ_50,'0'), \
// 						 NVL(B.SEQ_51,'0'), NVL(B.SEQ_52,'0'), NVL(B.SEQ_53,'0'), NVL(B.SEQ_54,'0'), NVL(B.SEQ_55,'0'), NVL(B.SEQ_56,'0'), NVL(B.SEQ_57,'0'), NVL(B.SEQ_58,'0'), NVL(B.SEQ_59,'0'), NVL(B.SEQ_60,'0'), \
// 						 NVL(B.SEQ_61,'0'), NVL(B.SEQ_62,'0'), NVL(B.SEQ_63,'0'), NVL(B.SEQ_64,'0') \
// 						 FROM E_AA_MSG_LOB_LINK2 A, E_AA_MSG_LOB_ELMT_LIST_LINK2 B  where A.LOB_ID != 0 AND A.LOB_ID = B.LOB_ID(+)";
//
//
// 	// ASC 로 해야 seqNum 를 제대로 읽을 수 있다. LINK2 데이터를 읽어 올때 사용함.
// #ifdef GET_SEQ_NUM
// 	sprintf_s( szQuery, 500, "SELECT * FROM E_AA_MSG_LOB_LINK2 WHERE LOB_ID='0' AND SEQ_NUM >= '%d' AND SEQ_NUM <= '%d' ORDER BY SEQ_NUM ASC", m_nGetSeqNum, m_nGetSeqNum+GP_MGR_PARAM->GetLOBNum()-1 );
// #else
// 	if( *GetMissionID(_LINK2) == NULL ) {
// 		sprintf_s( szQuery, 500, " AND A.SEQ_NUM >= '%d' AND A.SEQ_NUM < %d AND A.IS_FILTERED ='0' ORDER BY A.SEQ_NUM ASC", m_nGetSeqNum, m_nGetSeqNum+GP_MGR_PARAM->GetLOBNum() );
// 	}
// 	else {
// 		//sprintf_s( szQuery, 500, " AND A.MISSION_ID='%s' AND A.SEQ_NUM >= %d AND A.SEQ_NUM < %d ORDER BY A.SEQ_NUM ASC", "MI_20180725132844755", m_nGetSeqNum, m_nGetSeqNum+5 );
// 		sprintf_s( szQuery, 500, " AND A.MISSION_ID='%s' AND A.MISSION_ID=B.MISSION_ID(+) AND A.SEQ_NUM >= %d AND A.SEQ_NUM < %d ORDER BY A.SEQ_NUM ASC", GetMissionID(_LINK2), m_nGetSeqNum, m_nGetSeqNum+GP_MGR_PARAM->GetLOBNum() );
// 		// sprintf_s( szQuery, 500, " AND A.SEQ_NUM >= '%d' AND IS_FILTERED ='0' AND ROWNUM <= '%d' ORDER BY A.SEQ_NUM ASC", 128544286, GP_MGR_PARAM->GetLOBNum() );
// 	}
//
// 	strQuery += szQuery;
//
// #endif
//
// 	_CALL_DB2( bRet, GetAllDataFromDBArray( pVecLOBData, pVecLOBGrp, NULL, strQuery.GetBuffer(), GP_MGR_PARAM->GetLOBNum(), true ) )
// 	if( bRet == true ) {
// 		// ABT 번호가 0 일때는 2대 동시 운용시 사용했던 함수를 수행한다.
// 		uSize = pVecLOBGrp->size();
//
// 		// Fetch 타이머를 데이터에 따라서 간격을 조정하게 한다.
// 		GP_MGR_LOB->UpdateFetchLinkPeriod( uSize );
//
// 		if( uSize > 0 ) {
// 			// TRACE( "\n strQuery[%s]" , strQuery );
// 			LogPrint( "\n Fetch LOB#[%d]부터 %d개", m_nGetSeqNum, uSize );
//
// 			for( i=0 ; i < uSize ; ++i ) {
// 				SRxLOBDataGroup stSRxLOBDataGroup=pVecLOBGrp->at(i);
// 				LogPrint( "[Seq%d/L%d] ", stSRxLOBDataGroup.uiFetchSeqNum, stSRxLOBDataGroup.uiLOBID );
// 			}
// 			m_nGetSeqNum = m_nGetSeqNum + uSize;
// 		}
// 	}
// 	else {
//
// 	}
//
// 	//LogPrint("\n========================================== FetchLOBData 시간 : %d ms", (int)((GetTickCount() - dwTime) / 1));
//
// }
//
// // void CELEmitterMergeMngr::FetchLOBData_LINK2( std::vector<SRxLOBData> *pVecLOBData, std::vector<SRxLOBDataGroup> *pVecLOBGrp )
// // {
// // 	bool bRet=false;
// // 	char szQuery[500];
// // 	SELEXTDB extDB=SELEXTDB();
// //
// // 	CString strQuery;
// // 	CString strTemp, strQueryLOB;
// //
// // 	UINT i,	uSize;
// //
// // 	DWORD dwTime = GetTickCount();
// //
// // 	// 링크 2 로부터 데이터를 갖고 올때 아래를 처리를 수행한다.
// // 	strQuery = "select A.SEQ_NUM, A.HOUR, A.MIN, A.SEC, A.ACQ_TIME, A.LINK_NUM, A.MISSION_ID, A.MISSION_NAME, A.TASK_ID, A.TASK_NAME, A.TASK_TYPE, A.SEARCH_BAND_ID, A.RXPATH, A.ANTDIRECTION, \
// // 						 A.LOB_ID, A.ABT_ID, A.AET_ID, NVL(A.ELNOT_PRIM, '-') , A.MODE_CODE_PRIM, NVL(A.ELNOT_SECON,'-'), NVL(A.MODE_CODE_SECON,'-'), NVL(A.ELNOT_TERT,'-'), NVL(A.MODE_CODE_TERT,'-'), A.MODULATION_CODE, NVL( A.NICK_NAME, '-'), \
// // 						 NVL(A.PRIM_FUNC_CODE,'-'), A.SIG_TYPE, A.POLIZATION, A.RATIOOFPOL, A.FISINTTASK, A.NUM_OF_PULSE_GRP, A.NUM_OF_PULSES, A.BL_STAT, A.FOV, A.DOA_MEAN, A.DOA_MIN, A.DOA_MAX, \
// // 						 A.DOA_DEV, A.DOA_STD, A.DI_RATIO, A.FRQ_TYPE, A.FRQ_PATTN_TYPE, A.HAS_FRQ_MOD_PRD, A.FRQ_CHNG_PRD, \
// // 						 A.NUM_OF_FRQ_POSITION, A.NUM_OF_FRQ_ELEMENT, A.FRQ_MEAN, A.FRQ_MAX, A.FRQ_MIN,  A.FRQ_DEV, A.PRI_TYPE, \
// // 						 A.PRI_PATTN_TYPE, A.HAS_PRI_MOD_PRD, A.PRI_MOD_PRD, A.NUM_OF_PRI_POSITION, A.NUM_OF_PRI_ELEMENT, \
// // 						 A.PRI_MEAN, PRI_MAX, A.PRI_MIN, A.PRI_DEV, A.PRI_JITTER_RTO, A.PW_MEAN, A.PW_MIN, A.PW_MAX, A.PW_DEV, \
// // 						 A.PA_MEAN, A.PA_MIN, A.PA_MAX, A.PA_DEV, A.SCAN_TYPE, A.SCAN_TYPE_DETAIL, A.SCAN_PRD, A.INTRA_TYPE, \
// // 						 A.INTRA_TYPE_DETAIL, A.INTRA_FRQ_MEAN, A.INTRA_FRQ_MIN, A.INTRA_FRQ_MAX, A.INTRA_FRQ_DEVIATION, \
// // 						 A.AIRCRAFT_LAT, A.AIRCRAFT_LONG, A.AIRCRAFT_PITCH, A.AIRCRAFT_ROLL, A.AIRCRAFT_HEADING, A.AIRCRAFT_ALT, \
// // 						 A.AIRCRAFT_FOM, A.IS_PDW_RESTORE, A.IS_IQ_RESTORE, A.IS_FILTERED, A.IS_MANUAL_INPUT, A.IS_VALIDITY, \
// // 						 A.IS_CHECKPOSITION, A.FINAL_RPT_TIME, A.FIRST_RPT_TIME, A.ALOB_ID, A.AABT_ID, A.AAET_ID, A.EL_STAT, A.RCV_TIME, \
// // 						 NVL(B.DATA_TYPE,'0'), NVL(B.ELEMENTS,'0'), NVL(B.SEQ_01,'0'), NVL(B.SEQ_02,'0'), NVL(B.SEQ_03,'0'), NVL(B.SEQ_04,'0'), NVL(B.SEQ_05,'0'), NVL(B.SEQ_06,'0'), NVL(B.SEQ_07,'0'), NVL(B.SEQ_08,'0'), NVL(B.SEQ_09,'0'), NVL(B.SEQ_10,'0'), \
// // 						 NVL(B.SEQ_11,'0'), NVL(B.SEQ_12,'0'), NVL(B.SEQ_13,'0'), NVL(B.SEQ_14,'0'), NVL(B.SEQ_15,'0'), NVL(B.SEQ_16,'0'), NVL(B.SEQ_17,'0'), NVL(B.SEQ_18,'0'), NVL(B.SEQ_19,'0'), NVL(B.SEQ_20,'0'), \
// // 						 NVL(B.SEQ_21,'0'), NVL(B.SEQ_22,'0'), NVL(B.SEQ_23,'0'), NVL(B.SEQ_24,'0'), NVL(B.SEQ_25,'0'), NVL(B.SEQ_26,'0'), NVL(B.SEQ_27,'0'), NVL(B.SEQ_28,'0'), NVL(B.SEQ_29,'0'), NVL(B.SEQ_30,'0'), \
// // 						 NVL(B.SEQ_31,'0'), NVL(B.SEQ_32,'0'), NVL(B.SEQ_33,'0'), NVL(B.SEQ_34,'0'), NVL(B.SEQ_35,'0'), NVL(B.SEQ_36,'0'), NVL(B.SEQ_37,'0'), NVL(B.SEQ_38,'0'), NVL(B.SEQ_39,'0'), NVL(B.SEQ_40,'0'), \
// // 						 NVL(B.SEQ_41,'0'), NVL(B.SEQ_42,'0'), NVL(B.SEQ_43,'0'), NVL(B.SEQ_44,'0'), NVL(B.SEQ_45,'0'), NVL(B.SEQ_46,'0'), NVL(B.SEQ_47,'0'), NVL(B.SEQ_48,'0'), NVL(B.SEQ_49,'0'), NVL(B.SEQ_50,'0'), \
// // 						 NVL(B.SEQ_51,'0'), NVL(B.SEQ_52,'0'), NVL(B.SEQ_53,'0'), NVL(B.SEQ_54,'0'), NVL(B.SEQ_55,'0'), NVL(B.SEQ_56,'0'), NVL(B.SEQ_57,'0'), NVL(B.SEQ_58,'0'), NVL(B.SEQ_59,'0'), NVL(B.SEQ_60,'0'), \
// // 						 NVL(B.SEQ_61,'0'), NVL(B.SEQ_62,'0'), NVL(B.SEQ_63,'0'), NVL(B.SEQ_64,'0') \
// // 						 FROM E_AA_MSG_LOB_LINK2 A, E_AA_MSG_LOB_ELMT_LIST_LINK2 B  where A.LOB_ID != 0 AND A.LOB_ID = B.LOB_ID(+) ";
// //
// // 	//A.LOB_ID, A.ABT_ID, A.AET_ID, A.ELNOT_PRIM , A.MODE_CODE_PRIM, A.ELNOT_SECON, A.MODE_CODE_SECON, A.ELNOT_TERT, A.MODE_CODE_TERT, A.MODULATION_CODE, A.NICK_NAME, \
// // 	//A.PRIM_FUNC_CODE, A.SIG_TYPE, A.POLIZATION, A.RATIOOFPOL, A.FISINTTASK, A.NUM_OF_PULSE_GRP, A.NUM_OF_PULSES, A.BL_STAT, A.FOV, A.DOA_MEAN, A.DOA_MIN, A.DOA_MAX, \
// //
// // 	//B.DATA_TYPE, B.ELEMENTS, B.SEQ_01, B.SEQ_02, B.SEQ_03, B.SEQ_04, B.SEQ_05, B.SEQ_06, B.SEQ_07, B.SEQ_08, B.SEQ_09, B.SEQ_10, \
// // 	//B.SEQ_11, B.SEQ_12, B.SEQ_13, B.SEQ_14, B.SEQ_15, B.SEQ_16, B.SEQ_17, B.SEQ_18, B.SEQ_19, B.SEQ_20, \
// // 	//B.SEQ_21, B.SEQ_22, B.SEQ_23, B.SEQ_24, B.SEQ_25, B.SEQ_26, B.SEQ_27, B.SEQ_28, B.SEQ_29, B.SEQ_30, \
// // 	//B.SEQ_31, B.SEQ_32, B.SEQ_33, B.SEQ_34, B.SEQ_35, B.SEQ_36, B.SEQ_37, B.SEQ_38, B.SEQ_39, B.SEQ_40, \
// // 	//B.SEQ_41, B.SEQ_42, B.SEQ_43, B.SEQ_44, B.SEQ_45, B.SEQ_46, B.SEQ_47, B.SEQ_48, B.SEQ_49, B.SEQ_50, \
// // 	//B.SEQ_51, B.SEQ_52, B.SEQ_53, B.SEQ_54, B.SEQ_55, B.SEQ_56, B.SEQ_57, B.SEQ_58, B.SEQ_59, B.SEQ_60, \
// // 	//B.SEQ_61, B.SEQ_62, B.SEQ_63, B.SEQ_64 \
// // 	// FROM E_AA_MSG_LOB_LINK2 A, E_AA_MSG_LOB_ELMT_LIST_LINK2 B  where A.LOB_ID != 0 AND A.LOB_ID = B.LOB_ID(+)";
// //
// // 	// ASC 로 해야 seqNum 를 제대로 읽을 수 있다. LINK2 데이터를 읽어 올때 사용함.
// // #ifdef GET_SEQ_NUM
// // 	sprintf_s( szQuery, 500, "SELECT * FROM E_AA_MSG_LOB_LINK2 WHERE LOB_ID='0' AND SEQ_NUM >= '%d' AND SEQ_NUM <= '%d' ORDER BY SEQ_NUM ASC", m_nGetSeqNum, m_nGetSeqNum+GP_MGR_PARAM->GetLOBNum()-1 );
// // #else
// // 	if( *GetMissionID(_LINK2) == NULL ) {
// // 		sprintf_s( szQuery, 500, " AND A.SEQ_NUM >= '%d' AND A.IS_FILTERED ='0' AND ROWNUM <= '%d' ORDER BY A.SEQ_NUM ASC", m_nGetSeqNum, GP_MGR_PARAM->GetLOBNum() );
// // 	}
// // 	else {
// // 		sprintf_s( szQuery, 500, " AND A.MISSION_ID='%s' AND A.SEQ_NUM >= '%d' AND ROWNUM <= '%d' ORDER BY A.SEQ_NUM ASC", GetMissionID(_LINK2), m_nGetSeqNum, GP_MGR_PARAM->GetLOBNum() );
// // 		// sprintf_s( szQuery, 500, " AND A.SEQ_NUM >= '%d' AND IS_FILTERED ='0' AND ROWNUM <= '%d' ORDER BY A.SEQ_NUM ASC", 128544286, GP_MGR_PARAM->GetLOBNum() );
// // 	}
// //
// // 	strQuery += szQuery;
// //
// // #endif
// //
// // 	_CALL_DB2( bRet, GetAllDataFromDBArray( pVecLOBData, pVecLOBGrp, NULL, strQuery.GetBuffer(), GP_MGR_PARAM->GetLOBNum(), true ) )
// // 		if( bRet == true ) {
// // 			// ABT 번호가 0 일때는 2대 동시 운용시 사용했던 함수를 수행한다.
// // 			uSize = pVecLOBGrp->size();
// //
// // 			// Fetch 타이머를 데이터에 따라서 간격을 조정하게 한다.
// // 			GP_MGR_LOB->UpdateFetchLinkPeriod( uSize );
// //
// // 			if( uSize > 0 ) {
// // 				// TRACE( "\n strQuery[%s]" , strQuery );
// // 				LogPrint( "\n Fetch LOB#[%d]부터 %d개", m_nGetSeqNum, uSize );
// //
// // 				for( i=0 ; i < uSize ; ++i ) {
// // 					SRxLOBDataGroup stSRxLOBDataGroup=pVecLOBGrp->at(i);
// // 					LogPrint( "[Seq%d/L%d] ", stSRxLOBDataGroup.uiFetchSeqNum, stSRxLOBDataGroup.uiLOBID );
// // 				}
// // 				m_nGetSeqNum = m_nGetSeqNum + uSize;
// // 			}
// // 		}
// // 		else {
// //
// // 		}
// //
// // 		//LogPrint("\n========================================== FetchLOBData 시간 : %d ms", (int)((GetTickCount() - dwTime) / 1));
// //
// // }
//



/**
 * @brief     LOB 데이터를 일정 개수만큼 갖고온다.
 * @param     std::vector<SRxLOBData> * pVecLOBData LOB 헤더 데이터
 * @param     std::vector<SRxLOBDataGroup> * pVecLOBGrp LOB 데이터
 * @param     int nLinkNum 링크 번호
 * @param     UINT uiABTID 검색할 빔 번호
 * @param     SRxLOBDataAndGroupIdArray * pSRxLOBDataAndGroupIdArray 검색할 대상(LOB번호, SEQ_NUM 등) 멀티 조건
 * @return    void
*/
void CELEmitterMergeMngr::FetchLOBData( std::vector<SRxLOBHeader> *pVecLOBHeader, std::vector<SRxLOBData> *pVecLOBData, UINT uiABTID, SRxLOBDataAndGroupIdArray *pSRxLOBDataAndGroupIdArray )
{
// 	bool bRet=false;
// 	char szQuery[500];
// 	SELEXTDB extDB=SELEXTDB();
//
// 	CString strQuery;
// 	CString strTemp, strQueryLOB;
//
// 	UINT i, uSize;
//
// 	DWORD dwTime = GetTickCount();
//
// 	// 링크 2 로부터 데이터를 갖고 올때 아래를 처리를 수행한다.
// 	if( pSRxLOBDataAndGroupIdArray == NULL ) {
// 		if( uiABTID == 0 ) {
// 			strQuery = "select A.SEQ_NUM, A.HOUR, A.MIN, A.SEC, A.ACQ_TIME, A.LINK_NUM, A.MISSION_ID, A.MISSION_NAME, A.TASK_ID, A.TASK_NAME, A.TASK_TYPE, A.SEARCH_BAND_ID, A.RXPATH, A.ANTDIRECTION, \
// 								 A.LOB_ID, A.ABT_ID, A.AET_ID, NVL(A.ELNOT_PRIM, '-') , A.MODE_CODE_PRIM, NVL(A.ELNOT_SECON,'-'), NVL(A.MODE_CODE_SECON,'-'), NVL(A.ELNOT_TERT,'-'), NVL(A.MODE_CODE_TERT,'-'), A.MODULATION_CODE, NVL( A.NICK_NAME, '-'), \
// 								 NVL(A.PRIM_FUNC_CODE,'-'), A.SIG_TYPE, A.POLIZATION, A.RATIOOFPOL, A.FISINTTASK, A.NUM_OF_PULSE_GRP, A.NUM_OF_PULSES, A.BL_STAT, A.FOV, A.DOA_MEAN, A.DOA_MIN, A.DOA_MAX, \
// 								 A.DOA_DEV, A.DOA_STD, A.DI_RATIO, A.FRQ_TYPE, A.FRQ_PATTN_TYPE, A.HAS_FRQ_MOD_PRD, A.FRQ_CHNG_PRD, \
// 								 A.NUM_OF_FRQ_POSITION, A.NUM_OF_FRQ_ELEMENT, A.FRQ_MEAN, A.FRQ_MAX, A.FRQ_MIN,  A.FRQ_DEV, A.PRI_TYPE, \
// 								 A.PRI_PATTN_TYPE, A.HAS_PRI_MOD_PRD, A.PRI_MOD_PRD, A.NUM_OF_PRI_POSITION, A.NUM_OF_PRI_ELEMENT, \
// 								 A.PRI_MEAN, PRI_MAX, A.PRI_MIN, A.PRI_DEV, A.PRI_JITTER_RTO, A.PW_MEAN, A.PW_MIN, A.PW_MAX, A.PW_DEV, \
// 								 A.PA_MEAN, A.PA_MIN, A.PA_MAX, A.PA_DEV, A.SCAN_TYPE, A.SCAN_TYPE_DETAIL, A.SCAN_PRD, A.INTRA_TYPE, \
// 								 A.INTRA_TYPE_DETAIL, A.INTRA_FRQ_MEAN, A.INTRA_FRQ_MIN, A.INTRA_FRQ_MAX, A.INTRA_FRQ_DEVIATION, \
// 								 A.AIRCRAFT_LAT, A.AIRCRAFT_LONG, A.AIRCRAFT_PITCH, A.AIRCRAFT_ROLL, A.AIRCRAFT_HEADING, A.AIRCRAFT_ALT, \
// 								 A.AIRCRAFT_FOM, A.IS_PDW_RESTORE, A.IS_IQ_RESTORE, A.IS_FILTERED, A.IS_MANUAL_INPUT, A.IS_VALIDITY, \
// 								 A.IS_CHECKPOSITION, A.FINAL_RPT_TIME, A.FIRST_RPT_TIME, A.ALOB_ID, A.AABT_ID, A.AAET_ID, A.EL_STAT, A.RCV_TIME, \
// 								 NVL(B.DATA_TYPE,'0'), NVL(B.ELEMENTS,'0'), NVL(B.SEQ_01,'0'), NVL(B.SEQ_02,'0'), NVL(B.SEQ_03,'0'), NVL(B.SEQ_04,'0'), NVL(B.SEQ_05,'0'), NVL(B.SEQ_06,'0'), NVL(B.SEQ_07,'0'), NVL(B.SEQ_08,'0'), NVL(B.SEQ_09,'0'), NVL(B.SEQ_10,'0'), \
// 								 NVL(B.SEQ_11,'0'), NVL(B.SEQ_12,'0'), NVL(B.SEQ_13,'0'), NVL(B.SEQ_14,'0'), NVL(B.SEQ_15,'0'), NVL(B.SEQ_16,'0'), NVL(B.SEQ_17,'0'), NVL(B.SEQ_18,'0'), NVL(B.SEQ_19,'0'), NVL(B.SEQ_20,'0'), \
// 								 NVL(B.SEQ_21,'0'), NVL(B.SEQ_22,'0'), NVL(B.SEQ_23,'0'), NVL(B.SEQ_24,'0'), NVL(B.SEQ_25,'0'), NVL(B.SEQ_26,'0'), NVL(B.SEQ_27,'0'), NVL(B.SEQ_28,'0'), NVL(B.SEQ_29,'0'), NVL(B.SEQ_30,'0'), \
// 								 NVL(B.SEQ_31,'0'), NVL(B.SEQ_32,'0'), NVL(B.SEQ_33,'0'), NVL(B.SEQ_34,'0'), NVL(B.SEQ_35,'0'), NVL(B.SEQ_36,'0'), NVL(B.SEQ_37,'0'), NVL(B.SEQ_38,'0'), NVL(B.SEQ_39,'0'), NVL(B.SEQ_40,'0'), \
// 								 NVL(B.SEQ_41,'0'), NVL(B.SEQ_42,'0'), NVL(B.SEQ_43,'0'), NVL(B.SEQ_44,'0'), NVL(B.SEQ_45,'0'), NVL(B.SEQ_46,'0'), NVL(B.SEQ_47,'0'), NVL(B.SEQ_48,'0'), NVL(B.SEQ_49,'0'), NVL(B.SEQ_50,'0'), \
// 								 NVL(B.SEQ_51,'0'), NVL(B.SEQ_52,'0'), NVL(B.SEQ_53,'0'), NVL(B.SEQ_54,'0'), NVL(B.SEQ_55,'0'), NVL(B.SEQ_56,'0'), NVL(B.SEQ_57,'0'), NVL(B.SEQ_58,'0'), NVL(B.SEQ_59,'0'), NVL(B.SEQ_60,'0'), \
// 								 NVL(B.SEQ_61,'0'), NVL(B.SEQ_62,'0'), NVL(B.SEQ_63,'0'), NVL(B.SEQ_64,'0') \
// 								 FROM E_AA_MSG_LOB_LINK2 A, E_AA_MSG_LOB_ELMT_LIST_LINK2 B  where A.LOB_ID != 0 AND A.LOB_ID = B.LOB_ID(+)";
// 								 //FROM E_AA_MSG_LOB_LINK2 A, E_AA_MSG_LOB_ELMT_LIST_LINK2 B  where A.LOB_ID != 0 AND A.LOB_ID = B.LOB_ID(+) AND A.SEQ_NUM = B.SEQ_NUM(+)";
//
// 			// ASC 로 해야 seqNum 를 제대로 읽을 수 있다. LINK2 데이터를 읽어 올때 사용함.
// #ifdef GET_SEQ_NUM
// 			sprintf_s( szQuery, 500, "SELECT * FROM E_AA_MSG_LOB_LINK2 WHERE LOB_ID='0' AND SEQ_NUM >= '%d' AND SEQ_NUM <= '%d' ORDER BY SEQ_NUM ASC", m_nGetSeqNum, m_nGetSeqNum+GP_MGR_PARAM->GetLOBNum()-1 );
// #else
// 			if( *GetMissionID(nLinkNum) == NULL ) {
// 				sprintf_s( szQuery, 500, " AND A.SEQ_NUM >= '%d' AND A.IS_FILTERED ='0' AND ROWNUM <= '%d' ORDER BY A.SEQ_NUM ASC", m_nGetSeqNum, GP_MGR_PARAM->GetLOBNum() );
// 			}
// 			else {
// 				sprintf_s( szQuery, 500, " AND A.MISSION_ID='%s' AND A.SEQ_NUM >= '%d' AND A.IS_FILTERED ='0' AND ROWNUM <= '%d' ORDER BY A.SEQ_NUM ASC", GetMissionID(nLinkNum), m_nGetSeqNum, GP_MGR_PARAM->GetLOBNum() );
// 				//sprintf_s( szQuery, 500, " AND A.SEQ_NUM >= '%d' AND IS_FILTERED ='0' AND ROWNUM <= '%d' ORDER BY A.SEQ_NUM ASC", 128544286, GP_MGR_PARAM->GetLOBNum() );
// 			}
//
// 			strQuery += szQuery;
//
// #endif
//
// 			_CALL_DB2( bRet, GetAllDataFromDBArray( pVecLOBData, pVecLOBGrp, & extDB, strQuery.GetBuffer(), GP_MGR_PARAM->GetLOBNum() ) )
// 			if( bRet == true ) {
// 				// ABT 번호가 0 일때는 2대 동시 운용시 사용했던 함수를 수행한다.
// 				uSize = pVecLOBGrp->size();
// 				if( uSize > 0 ) {
// 					// TRACE( "\n strQuery[%s]" , strQuery );
// 					LogPrint( "\n Fetch LOB#[%d]부터 %d개", m_nGetSeqNum, uSize );
//
// 					for( i=0 ; i < uSize ; ++i ) {
// 						SRxLOBDataGroup stSRxLOBDataGroup=pVecLOBGrp->at(i);
// 						LogPrint( "[Seq%d/L%d] ", stSRxLOBDataGroup.uiFetchSeqNum, stSRxLOBDataGroup.uiLOBID );
// 					}
// 					m_nGetSeqNum = m_nGetSeqNum + uSize;
// 				}
// 			}
// 			else {
// 				// 쿼리문이 잘못될 때만 seq_num 다음번으로 이동해야 함.
// 				// ++ m_nGetSeqNum;
// 			}
//
// 		}
// 		// LOB 클러스터링으로 데이터를 갖고 올때
// 		else {
// 			strQuery = "select A.SEQ_NUM, A.HOUR, A.MIN, A.SEC, A.ACQ_TIME, A.LINK_NUM, A.MISSION_ID, A.MISSION_NAME, A.TASK_ID, A.TASK_NAME, A.TASK_TYPE, A.SEARCH_BAND_ID, A.RXPATH, A.ANTDIRECTION, \
// 								 A.LOB_ID, A.ABT_ID, A.AET_ID, NVL(A.ELNOT_PRIM, '-') , A.MODE_CODE_PRIM, NVL(A.ELNOT_SECON,'-'), NVL(A.MODE_CODE_SECON,'-'), NVL(A.ELNOT_TERT,'-'), NVL(A.MODE_CODE_TERT,'-'), A.MODULATION_CODE, NVL( A.NICK_NAME, '-'), \
// 								 NVL(A.PRIM_FUNC_CODE,'-'), A.SIG_TYPE, A.POLIZATION, A.RATIOOFPOL, A.FISINTTASK, A.NUM_OF_PULSE_GRP, A.NUM_OF_PULSES, A.BL_STAT, A.FOV, A.DOA_MEAN, A.DOA_MIN, A.DOA_MAX, \
// 								 A.DOA_DEV, A.DOA_STD, A.DI_RATIO, A.FRQ_TYPE, A.FRQ_PATTN_TYPE, A.HAS_FRQ_MOD_PRD, A.FRQ_CHNG_PRD, \
// 								 A.NUM_OF_FRQ_POSITION, A.NUM_OF_FRQ_ELEMENT, A.FRQ_MEAN, A.FRQ_MAX, A.FRQ_MIN,  A.FRQ_DEV, A.PRI_TYPE, \
// 								 A.PRI_PATTN_TYPE, A.HAS_PRI_MOD_PRD, A.PRI_MOD_PRD, A.NUM_OF_PRI_POSITION, A.NUM_OF_PRI_ELEMENT, \
// 								 A.PRI_MEAN, PRI_MAX, A.PRI_MIN, A.PRI_DEV, A.PRI_JITTER_RTO, A.PW_MEAN, A.PW_MIN, A.PW_MAX, A.PW_DEV, \
// 								 A.PA_MEAN, A.PA_MIN, A.PA_MAX, A.PA_DEV, A.SCAN_TYPE, A.SCAN_TYPE_DETAIL, A.SCAN_PRD, A.INTRA_TYPE, \
// 								 A.INTRA_TYPE_DETAIL, A.INTRA_FRQ_MEAN, A.INTRA_FRQ_MIN, A.INTRA_FRQ_MAX, A.INTRA_FRQ_DEVIATION, \
// 								 A.AIRCRAFT_LAT, A.AIRCRAFT_LONG, A.AIRCRAFT_PITCH, A.AIRCRAFT_ROLL, A.AIRCRAFT_HEADING, A.AIRCRAFT_ALT, \
// 								 A.AIRCRAFT_FOM, A.IS_PDW_RESTORE, A.IS_IQ_RESTORE, A.IS_FILTERED, A.IS_MANUAL_INPUT, A.IS_VALIDITY, \
// 								 A.IS_CHECKPOSITION, A.FINAL_RPT_TIME, A.FIRST_RPT_TIME, A.ALOB_ID, A.AABT_ID, A.AAET_ID, A.EL_STAT, A.RCV_TIME, \
// 								 NVL(B.DATA_TYPE,'0'), NVL(B.ELEMENTS,'0'), NVL(B.SEQ_01,'0'), NVL(B.SEQ_02,'0'), NVL(B.SEQ_03,'0'), NVL(B.SEQ_04,'0'), NVL(B.SEQ_05,'0'), NVL(B.SEQ_06,'0'), NVL(B.SEQ_07,'0'), NVL(B.SEQ_08,'0'), NVL(B.SEQ_09,'0'), NVL(B.SEQ_10,'0'), \
// 								 NVL(B.SEQ_11,'0'), NVL(B.SEQ_12,'0'), NVL(B.SEQ_13,'0'), NVL(B.SEQ_14,'0'), NVL(B.SEQ_15,'0'), NVL(B.SEQ_16,'0'), NVL(B.SEQ_17,'0'), NVL(B.SEQ_18,'0'), NVL(B.SEQ_19,'0'), NVL(B.SEQ_20,'0'), \
// 								 NVL(B.SEQ_21,'0'), NVL(B.SEQ_22,'0'), NVL(B.SEQ_23,'0'), NVL(B.SEQ_24,'0'), NVL(B.SEQ_25,'0'), NVL(B.SEQ_26,'0'), NVL(B.SEQ_27,'0'), NVL(B.SEQ_28,'0'), NVL(B.SEQ_29,'0'), NVL(B.SEQ_30,'0'), \
// 								 NVL(B.SEQ_31,'0'), NVL(B.SEQ_32,'0'), NVL(B.SEQ_33,'0'), NVL(B.SEQ_34,'0'), NVL(B.SEQ_35,'0'), NVL(B.SEQ_36,'0'), NVL(B.SEQ_37,'0'), NVL(B.SEQ_38,'0'), NVL(B.SEQ_39,'0'), NVL(B.SEQ_40,'0'), \
// 								 NVL(B.SEQ_41,'0'), NVL(B.SEQ_42,'0'), NVL(B.SEQ_43,'0'), NVL(B.SEQ_44,'0'), NVL(B.SEQ_45,'0'), NVL(B.SEQ_46,'0'), NVL(B.SEQ_47,'0'), NVL(B.SEQ_48,'0'), NVL(B.SEQ_49,'0'), NVL(B.SEQ_50,'0'), \
// 								 NVL(B.SEQ_51,'0'), NVL(B.SEQ_52,'0'), NVL(B.SEQ_53,'0'), NVL(B.SEQ_54,'0'), NVL(B.SEQ_55,'0'), NVL(B.SEQ_56,'0'), NVL(B.SEQ_57,'0'), NVL(B.SEQ_58,'0'), NVL(B.SEQ_59,'0'), NVL(B.SEQ_60,'0'), \
// 								 NVL(B.SEQ_61,'0'), NVL(B.SEQ_62,'0'), NVL(B.SEQ_63,'0'), NVL(B.SEQ_64,'0') \
// 								 FROM E_AA_MSG_LOB A, E_AA_MSG_LOB_ELMT_LIST B where A.LOB_ID = B.LOB_ID(+) AND A.MISSION_ID = B.MISSION_ID(+)";
// 								 // FROM E_AA_MSG_LOB A, E_AA_MSG_LOB_ELMT_LIST B where A.LOB_ID = B.LOB_ID(+) AND A.SEQ_NUM = B.SEQ_NUM(+)";
// 								//FROM E_AA_MSG_LOB A, E_AA_MSG_LOB_ELMT_LIST B where A.LOB_ID != 0 AND A.LOB_ID = B.LOB_ID(+)";
//
// 			if( *GetMissionID(nLinkNum) == NULL ) {
// 				sprintf_s( szQuery, 500, " AND A.IS_FILTERED ='0' AND A.ABT_ID='%d' ORDER BY A.SEQ_NUM ASC", uiABTID );
// 			}
// 			else {
// #ifdef _DB_TUNNING_
// 				sprintf_s( szQuery, 500, " AND A.MISSION_ID='%s' || SUBSTR(UID, 1, 0) AND A.ABT_ID='%d' ORDER BY A.SEQ_NUM ASC", GetMissionID(nLinkNum), uiABTID );
// #else
// 				sprintf_s( szQuery, 500, " AND A.MISSION_ID='%s' AND A.IS_FILTERED ='0' AND A.ABT_ID='%d' ORDER BY A.SEQ_NUM ASC", GetMissionID(nLinkNum), uiABTID );
// #endif
//
// 			}
//
// 			strQuery += szQuery;
//
// 			_CALL_DB( GetAllDataFromDBArray( pVecLOBData, pVecLOBGrp, & extDB, strQuery.GetBuffer() ) )
//
// 		}
// 	}
// 	else {
// 		strQuery = "select A.SEQ_NUM, A.HOUR, A.MIN, A.SEC, A.ACQ_TIME, A.LINK_NUM, A.MISSION_ID, A.MISSION_NAME, A.TASK_ID, A.TASK_NAME, A.TASK_TYPE, A.SEARCH_BAND_ID, A.RXPATH, A.ANTDIRECTION, \
// 							 A.LOB_ID, A.ABT_ID, A.AET_ID, NVL(A.ELNOT_PRIM, '-') , A.MODE_CODE_PRIM, NVL(A.ELNOT_SECON,'-'), NVL(A.MODE_CODE_SECON,'-'), NVL(A.ELNOT_TERT,'-'), NVL(A.MODE_CODE_TERT,'-'), A.MODULATION_CODE, NVL( A.NICK_NAME, '-'), \
// 							 NVL(A.PRIM_FUNC_CODE,'-'), A.SIG_TYPE, A.POLIZATION, A.RATIOOFPOL, A.FISINTTASK, A.NUM_OF_PULSE_GRP, A.NUM_OF_PULSES, A.BL_STAT, A.FOV, A.DOA_MEAN, A.DOA_MIN, A.DOA_MAX, \
// 							 A.DOA_DEV, A.DOA_STD, A.DI_RATIO, A.FRQ_TYPE, A.FRQ_PATTN_TYPE, A.HAS_FRQ_MOD_PRD, A.FRQ_CHNG_PRD, \
// 							 A.NUM_OF_FRQ_POSITION, A.NUM_OF_FRQ_ELEMENT, A.FRQ_MEAN, A.FRQ_MAX, A.FRQ_MIN,  A.FRQ_DEV, A.PRI_TYPE, \
// 							 A.PRI_PATTN_TYPE, A.HAS_PRI_MOD_PRD, A.PRI_MOD_PRD, A.NUM_OF_PRI_POSITION, A.NUM_OF_PRI_ELEMENT, \
// 							 A.PRI_MEAN, PRI_MAX, A.PRI_MIN, A.PRI_DEV, A.PRI_JITTER_RTO, A.PW_MEAN, A.PW_MIN, A.PW_MAX, A.PW_DEV, \
// 							 A.PA_MEAN, A.PA_MIN, A.PA_MAX, A.PA_DEV, A.SCAN_TYPE, A.SCAN_TYPE_DETAIL, A.SCAN_PRD, A.INTRA_TYPE, \
// 							 A.INTRA_TYPE_DETAIL, A.INTRA_FRQ_MEAN, A.INTRA_FRQ_MIN, A.INTRA_FRQ_MAX, A.INTRA_FRQ_DEVIATION, \
// 							 A.AIRCRAFT_LAT, A.AIRCRAFT_LONG, A.AIRCRAFT_PITCH, A.AIRCRAFT_ROLL, A.AIRCRAFT_HEADING, A.AIRCRAFT_ALT, \
// 							 A.AIRCRAFT_FOM, A.IS_PDW_RESTORE, A.IS_IQ_RESTORE, A.IS_FILTERED, A.IS_MANUAL_INPUT, A.IS_VALIDITY, \
// 							 A.IS_CHECKPOSITION, A.FINAL_RPT_TIME, A.FIRST_RPT_TIME, A.ALOB_ID, A.AABT_ID, A.AAET_ID, A.EL_STAT, A.RCV_TIME, \
// 							 NVL(B.DATA_TYPE,'0'), NVL(B.ELEMENTS,'0'), NVL(B.SEQ_01,'0'), NVL(B.SEQ_02,'0'), NVL(B.SEQ_03,'0'), NVL(B.SEQ_04,'0'), NVL(B.SEQ_05,'0'), NVL(B.SEQ_06,'0'), NVL(B.SEQ_07,'0'), NVL(B.SEQ_08,'0'), NVL(B.SEQ_09,'0'), NVL(B.SEQ_10,'0'), \
// 							 NVL(B.SEQ_11,'0'), NVL(B.SEQ_12,'0'), NVL(B.SEQ_13,'0'), NVL(B.SEQ_14,'0'), NVL(B.SEQ_15,'0'), NVL(B.SEQ_16,'0'), NVL(B.SEQ_17,'0'), NVL(B.SEQ_18,'0'), NVL(B.SEQ_19,'0'), NVL(B.SEQ_20,'0'), \
// 							 NVL(B.SEQ_21,'0'), NVL(B.SEQ_22,'0'), NVL(B.SEQ_23,'0'), NVL(B.SEQ_24,'0'), NVL(B.SEQ_25,'0'), NVL(B.SEQ_26,'0'), NVL(B.SEQ_27,'0'), NVL(B.SEQ_28,'0'), NVL(B.SEQ_29,'0'), NVL(B.SEQ_30,'0'), \
// 							 NVL(B.SEQ_31,'0'), NVL(B.SEQ_32,'0'), NVL(B.SEQ_33,'0'), NVL(B.SEQ_34,'0'), NVL(B.SEQ_35,'0'), NVL(B.SEQ_36,'0'), NVL(B.SEQ_37,'0'), NVL(B.SEQ_38,'0'), NVL(B.SEQ_39,'0'), NVL(B.SEQ_40,'0'), \
// 							 NVL(B.SEQ_41,'0'), NVL(B.SEQ_42,'0'), NVL(B.SEQ_43,'0'), NVL(B.SEQ_44,'0'), NVL(B.SEQ_45,'0'), NVL(B.SEQ_46,'0'), NVL(B.SEQ_47,'0'), NVL(B.SEQ_48,'0'), NVL(B.SEQ_49,'0'), NVL(B.SEQ_50,'0'), \
// 							 NVL(B.SEQ_51,'0'), NVL(B.SEQ_52,'0'), NVL(B.SEQ_53,'0'), NVL(B.SEQ_54,'0'), NVL(B.SEQ_55,'0'), NVL(B.SEQ_56,'0'), NVL(B.SEQ_57,'0'), NVL(B.SEQ_58,'0'), NVL(B.SEQ_59,'0'), NVL(B.SEQ_60,'0'), \
// 							 NVL(B.SEQ_61,'0'), NVL(B.SEQ_62,'0'), NVL(B.SEQ_63,'0'), NVL(B.SEQ_64,'0') \
// 							 FROM E_AA_MSG_LOB A, E_AA_MSG_LOB_ELMT_LIST B where A.LOB_ID = B.LOB_ID(+) AND A.ABT_ID = B.ABT_ID(+) AND A.MISSION_ID = B.MISSION_ID(+)";
// 							 //FROM E_AA_MSG_LOB A, E_AA_MSG_LOB_ELMT_LIST B where A.LOB_ID = B.LOB_ID(+) AND A.ABT_ID = B.ABT_ID(+) AND A.SEQ_NUM = B.SEQ_NUM(+)";
// 		//FROM E_AA_MSG_LOB A, E_AA_MSG_LOB_ELMT_LIST B where A.LOB_ID = B.LOB_ID(+) AND A.ABT_ID = B.ABT_ID(+)";
//
// 		strQuery += " AND (";
//
// 		for( i=0 ; i < (UINT) pSRxLOBDataAndGroupIdArray->nLobCount ; ++i ) {
// 			if( i >= 1 ) {
// 				strQueryLOB += " OR";
// 			}
//
// 			strTemp.Format( " (A.LOB_ID='%d' AND A.ABT_ID='%d' AND A.SEQ_NUM='%d')", pSRxLOBDataAndGroupIdArray->nLobId[i], pSRxLOBDataAndGroupIdArray->nAbtId[i], pSRxLOBDataAndGroupIdArray->ullSeqNum[i] );
//
// 			strQueryLOB += strTemp;
// 		}
//
// 		strQuery += strQueryLOB;
// 		strQuery += " )";
//
// 		_CALL_DB( GetAllDataFromDBArray( pVecLOBData, pVecLOBGrp, & extDB, strQuery.GetBuffer(), MAX_SIZE_OF_ARRAY_INSERT ) )
//
// 	}
//
// 	//LogPrint("\n========================================== FetchLOBData 시간 : %d ms", (int)((GetTickCount() - dwTime) / 1));

}

// // #ifdef _POLIZATION_DB_
// // /**
// //  * @brief     LOB 테이블에서 DOA 편차 및 분산 값을 얻는다.
// //  * @param     *pDOA DOA의 데이터 포인터
// //  * @param     nLinkNum 링크 번호
// //  * @param     nAETID 방사체 번호
// //  * @param     nABTID 빔 번호
// //  * @return    리턴값 없음
// //  * @author    조철희 (churlhee.jo@lignex1.com)
// //  * @version   0.0.1
// //  * @date      2016-04-15, 오후 10:56
// //  * @warning
// //  */
// // void CELEmitterMergeMngr::GetPolizationFromLOB( int *pPolization, int nLinkNum, int nAETID, int nABTID )
// // {
// // 	char buffer1[100], buffer2[200];
// //
// // 	/*! \todo   고감도 과제이면 pPolization 값을 6으로 강제 설정
// // 			\author 조철희 (churlhee.jo@lignex1.com)
// // 			\date 	2016-11-23 16:51:59
// // 	*/
// // 	sprintf_s( buffer1, 100, "LINK_NUM='%d' AND AET_ID = '%d' AND ABT_ID = '%d' AND IS_FILTERED ='0'" , nLinkNum, nAETID, nABTID );
// //
// // 	if( *GetMissionID(nLinkNum) == NULL ) { //DTEC_NullPointCheck
// // 		sprintf_s( buffer2, 200, "WHERE %s" , buffer1 );
// // 	}
// // 	else {
// // 		sprintf_s( buffer2, 200, "WHERE MISSION_ID='%s' AND %s", GetMissionID(nLinkNum), buffer1 );
// // 	}
// //
// // 	_CALL_DB( GetPolizationFromDB_LOB( pPolization, buffer2 ) );
// //
// // }
// // #endif
//
// /**
//  * @brief     LOB 테이블에서 DOA 편차 및 분산 값을 얻는다.
//  * @param     *pDOA DOA의 데이터 포인터
//  * @param     nLinkNum 링크 번호
//  * @param     nAETID 방사체 번호
//  * @param     nABTID 빔 번호
//  * @return    리턴값 없음
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-04-15, 오후 10:56
//  * @warning
//  */
// // void CELEmitterMergeMngr::GetStdSevDOAFromLOB( int *pDOA, int nLinkNum, int nAETID, int nABTID )
// // {
// // 	char buffer1[200], buffer2[500];
// //
// // 	sprintf_s( buffer1, 200, "LINK_NUM='%d' AND AET_ID = '%d' AND ABT_ID = '%d' AND IS_FILTERED ='0'" , nLinkNum, nAETID, nABTID );
// //
// // 	if( *GetMissionID(nLinkNum) == NULL ) { //DTEC_NullPointCheck
// // 		sprintf_s( buffer2, 500, "WHERE %s" , buffer1 );
// // 	}
// // 	else
// // 		sprintf_s( buffer2, 500, "WHERE MISSION_ID='%s' AND %s", GetMissionID(nLinkNum), buffer1 );
// // 	_CALL_DB( GetSTDDEVDOAFromDB_LOB( pDOA, buffer2 ) );
// //
// // }
//
// /**
//  * @brief     LOB에 대해서 병합 처리한다.
//  * @param     *pLOBDataExt LOB 추가 정보의 데이터 포인터
//  * @param     i_bCheckLOB LOB 체크 여부를 결정
//  * @return    리턴값 없음
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-03-05, 오후 2:29
//  * @warning
//  */
bool CELEmitterMergeMngr::ManageThreat( SELLOBDATA_EXT *pLOBDataExt, bool i_bCheckLOB )
{
    bool bIs;

    // 미식별 ELNOT 초기화
    //m_szELNOT[0] = NULL;
    m_vecCanOfMergeLOB.clear();

    m_pUpdateABTThreat = NULL;
    m_pUpdateAETThreat = NULL;

    m_pABTData = NULL;
    m_pABTExtData = NULL;
    
    // ABT 비교 : 동일 링크 번호간의 병합 : // 방탐을 고려한 비교
    bIs = CompMergeLOB( pLOBDataExt, true );
    
    if( bIs == true ) {
        // 4.2 위협 변경
        UpdateThreat( pLOBDataExt, true );

        m_pUpdateABTThreat = m_pABTThreat;
        m_pUpdateAETThreat = m_pAETThreat;
    }
    else {
        // 4.1 위협 생성
        CreateThreat( pLOBDataExt, true );

    }

    return bIs;

}

// 강제 방사체 생성을 종료한다.
// void CELEmitterMergeMngr::CloseGenNewEmitter()
// {
// 	SELAETDATA_EXT *pAETExtData;
//
// 	if( m_pAETThreat != NULL ) {
// 		pAETExtData = GetAETExtData( m_pAETThreat->m_nIndex );
//
// 		m_uiAETIDFromGenNewEmitter = m_pAETThreat->m_Idx.uiAET;
//
// 		strcpy_s( m_szELNOTFromGenNewEmitter, pAETExtData->szELNOT );
//
// 		// 업데이트 된 최종 방사체를 삭제한다.
// 		// UserRemoveThreat( m_uiAETIDFromGenNewEmitter );
// 	}
// 	else {
// 		m_uiAETIDFromGenNewEmitter = 0;
// 		m_szELNOTFromGenNewEmitter[0] = NULL;
// 	}
//
// 	//m_bGenNewEmitter = false;
//
// }
//
// /**
//  * @brief     방사체 정보의 빔 정보의 LOB와 LOB의 DOA를 비교하여 성공 여부를 리턴한다.
//  * @param     *pThreatDataExt LOB 추가 정보의 데이터 포인터
//  * @return    병합이 정상이면 true, 그렇지 않으면 false
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-04-22, 오후 9:41
//  * @warning
//  */
// // bool CELEmitterMergeMngr::CompLOBOfAET( SELLOBDATA_EXT *pThreatDataExt )
// // {
// // 	int i;
// // 	int nCoMerge;
// //
// // 	SRxABTData *pABTData;
// // 	SELABTDATA_EXT *pABTExtData;
// //
// // 	SELMERGE_CANDIDATE *pMergeCandidate;
// //
// // 	SELDISTLOB distlob;
// //
// // 	CELThreat *pTheABTThreat;
// //
// // 	nCoMerge = m_vecCanOfMergeLOB.size();
// // 	for( i=0 ; i < nCoMerge ; ++i ) {
// // 		pMergeCandidate = & m_vecCanOfMergeLOB.at(i);
// //
// // 		pTheABTThreat = m_theThreatRoot.Find( & pMergeCandidate->idx );
// //
// // 		pABTData = GetABTData( pTheABTThreat->m_nIndex );
// // 		pABTExtData = GetABTExtData( pTheABTThreat->m_nIndex );
// //
// // 		if( pABTData->peInfo.enValid == E_EL_PESTAT_SUCCESS ) {
// // 			int iLOB;
// //
// // 			m_theInverseMethod.VincentyInverse( & distlob, pABTExtData->dRadarCollectionLatitude, pABTExtData->dRadarCollectionLongitude, pABTData->peInfo.iLatitude/1000., pABTData->peInfo.iLongitude/1000. );
// // 			iLOB = (int) ( distlob.fwdlob + 0.5 );
// //
// // 			if( CompAoaDiff( iLOB, m_pLOBData->iMeanDOA, 10 ) == TRUE )
// // 				return true;
// //
// // 		}
// //
// // 	}
// //
// // 	return true;
// // }

/**
 * @brief     LOB와 병합 비교한다.
 * @param     *pThreatDataExt LOB 추가 정보의 데이터 포인터
 * @param     bLinkComp 링크 비교 여부 결정
 * @return    병합이 정상이면 true, 그렇지 않으면 false
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-04-22, 오전 1:18
 * @warning
 */
bool CELEmitterMergeMngr::CompMergeLOB( SELLOBDATA_EXT *pThreatDataExt, bool bLinkComp )
{
    bool bRet=false;
    CELThreat *pThreatAET, *pThreatABT;

    SELMERGE_CANDIDATE mergeCandidate;

    pThreatAET = GetHeaderThreat( m_pTheThreatRoot );

    // 스캔 LOB 는 병합 비교를 하지 않는다.
    while( pThreatAET != NULL ) { //#FA_C_PotentialUnboundedLoop_T1
        pThreatABT = GetHeaderThreat( pThreatAET );
        while( pThreatABT != NULL ) { //#FA_C_PotentialUnboundedLoop_T1
            // ABT들간의 병합 비교 수행
            if( CompMergeLOB( & mergeCandidate, pThreatABT, pThreatDataExt, bLinkComp ) == true ) {
                m_vecCanOfMergeLOB.push_back( mergeCandidate );
            }
            pThreatABT = GetNextThreat( pThreatABT );
        }

        pThreatAET = GetNextThreat( pThreatAET );
    }

    // 2. 병합 후보 중에서 레벨 값 적은 순으로 정렬한다.
    SortMergeCandidate();

    // 3. 후보 중에서 임계값 이하에서 결정한다.
    if( DecideMergeCandidate() == true ) {
        //strcpy_s( m_szELNOT, m_vecCanOfMergeLOB.at(0).szELNOT );

        bRet = true;
    }

    return bRet;

}

// /**
//  * @brief			위치 및 식별 결과를 이용한 두 방사체 간의 병합
//  * @return    리턴값 없음
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-03-29, 오후 8:31
//  * @warning
//  */
// // void CELEmitterMergeMngr::CheckMergeAET( CELThreat *pTheThreat )
// // {
// // 	SThreatFamilyInfo stThreatFamilyInfo;
// // 	CELThreat *pMatchThreat;
// //
// // 	// 방사체 간의 병합
// // 	pMatchThreat = MergeIdentifiedAET( pTheThreat );
// // 	if( pMatchThreat != NULL ) {
// // 		stThreatFamilyInfo.eStat = E_MR_UPDATE;
// // 		stThreatFamilyInfo.iAETID = pMatchThreat->m_Idx.nAET;
// // 		stThreatFamilyInfo.iABTID = INVALID_INDEX;
// // 		stThreatFamilyInfo.iLOBID = INVALID_INDEX;
// //
// // 		stThreatFamilyInfo.bApplySearchFilter = true;
// //
// // 		if( true == MergeAET( pTheThreat, pMatchThreat ) ) {
// // 			m_pVecThreatInfo->push_back( stThreatFamilyInfo );
// //
// // 			// 병합한 에미터데 대해서 삭제 처리
// // 			stThreatFamilyInfo.eStat = E_MR_DELETE;
// // 			stThreatFamilyInfo.iAETID = pMatchThreat->m_Idx.nAET;
// // 			stThreatFamilyInfo.iABTID = INVALID_INDEX;
// // 			stThreatFamilyInfo.iLOBID = INVALID_INDEX;
// //
// // 			stThreatFamilyInfo.bApplySearchFilter = true;
// //
// // 			// m_pVecThreatInfo->push_back( stThreatFamilyInfo );
// // 		}
// //
// // 	}
// //
// // }
//
// /**
//  * @brief     방사체 정보들을 병합을 수행한다.
//  * @param     *pThreatAET 위협 정보를 병합할 데이터 포인터
//  * @return    리턴값 없음
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-04-02, 오전 11:25
//  * @warning
//  */
// // CELThreat *CELEmitterMergeMngr::MergeIdentifiedAET( CELThreat *pThreatAET )
// // {
// // 	int nMaxThreatRadius;
// //
// // 	CELThreat *pNextThreatAET;
// //
// // 	SELAETDATA *pAETData, *pNextAETData;
// // 	SELAETDATA_EXT *pAETExtData, *pNextAETExtData;
// //
// // 	SRxABTData *pNextABTData;
// // 	SELABTDATA_EXT *pNextABTExtData;
// //
// // 	pAETData = GetAETData( pThreatAET->m_nIndex );
// // 	pAETExtData = GetAETExtData( pThreatAET->m_nIndex );
// //
// // 	pNextThreatAET = GetHeaderThreat( & m_theThreatRoot );
// //
// // 	nMaxThreatRadius = m_theIdentifyAlg.GetMaxThreatRadius( pAETData->idInfo.nThreatIndex, pAETData->idInfo.nDeviceIndex, m_pSEnvironVariable->eEOBDefaultLibType );
// //
// // 	// 위치 산출이 되고 EOB 식별이 될 때 다른 위협을 비교
// // 	if( pAETData->idInfo.nThreatIndex > 0 ) {
// // 		int iDiff;
// // 		int iLat1, iLong1, iLat2, iLong2;
// //
// // 		iLat1 = pAETData->peInfo.iLatitude;
// // 		iLong1 = pAETData->peInfo.iLongitude;
// //
// // 		if( pAETData->peInfo.enValid == E_EL_PESTAT_SUCCESS ) {
// // 			while( pNextThreatAET != NULL ) {
// // 				if( pNextThreatAET == pThreatAET ) {
// // 					pNextThreatAET = GetNextThreat( pNextThreatAET );
// // 					continue;
// // 				}
// //
// // 				// 병합 조건 판단
// // 				// 1. ELNOT 동일
// // 				pNextAETData = GetAETData( pNextThreatAET->m_nIndex );
// // 				pNextAETExtData = GetAETExtData( pNextThreatAET->m_nIndex );
// // 				if( strcmp( pAETExtData->szEOBELNOT, pNextAETExtData->szEOBELNOT ) == 0 ) {
// // 					// 2. 거리 반경 이내
// // 					iLat2 = pAETData->peInfo.iLatitude;
// // 					iLong2 = pAETData->peInfo.iLongitude;
// // 					iDiff = m_theIdentifyAlg.CalDistanceNM( iLat1, iLong1, iLat2, iLong2 );
// // 					if( iDiff < nMaxThreatRadius ) {
// // 						return pNextThreatAET;
// // 					}
// // 				}
// //
// // 				pNextThreatAET = GetNextThreat( pNextThreatAET );
// // 			}
// // 		}
// // 	}
// // 	else {
// // 		while( pNextThreatAET != NULL ) {
// // 			if( pNextThreatAET == pThreatAET ) {
// // 				pNextThreatAET = GetNextThreat( pNextThreatAET );
// // 				continue;
// // 			}
// //
// // 			//
// // 			pNextABTData = GetABTData( pNextThreatAET->m_nIndex );
// // 			pNextABTExtData = GetABTExtData( pNextThreatAET->m_nIndex );
// //
// // 			if( pAETData->peInfo.enValid == E_EL_PESTAT_SUCCESS ) { //DTEC_Else
// // 			}
// //
// // 			pNextThreatAET = GetNextThreat( pNextThreatAET );
// //
// // 		}
// //
// // 	}
// //
// // 	return NULL;
// //
// // }
//
// /**
//  * @brief     AET 노드 들을 합쳐서 하나로 만든다.
//  * @param     *pTheThreat 방사체(빔) 정보의 데이터 포인터
//  * @param     *pMatchThreat 병합할 위협 정보의 데이터 포인터
//  * @return    병합이 성공이면 true, 그렇지 않으면 false
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-04-02, 오후 12:54
//  * @warning
//  */
// // bool CELEmitterMergeMngr::MergeAET( CELThreat *pTheThreat, CELThreat *pMatchThreat )
// // {
// // 	CELThreat *pThePrevThreat;
// // 	CELThreat *pTheMatchABTThreat, *pTheLastABTThreat;
// //
// // 	// 연결할 마지막 ABT 노드를 얻는다.
// // 	pTheLastABTThreat = pTheThreat->GetLastThreat( pTheThreat );
// //
// // 	// 병합할 ABT 시작 주소를 얻는다.
// // 	pTheMatchABTThreat = pMatchThreat->GetLeftChild();
// //
// // 	if( pTheLastABTThreat != NULL && pTheMatchABTThreat != NULL ) {
// // 		// 두 ABT 그룹을 연결 시켜준다.
// // 		pTheLastABTThreat->Link( pTheMatchABTThreat );
// //
// // 		UpdateAETABTLOBID( pTheMatchABTThreat );
// //
// // 		// 삭제할 AET의 이전 노드와 다음 노드들을 연결 시켜준다.
// // 		//
// // 		pThePrevThreat = m_theThreatRoot.FindPrevThreat( pMatchThreat );
// // 		pThePrevThreat->Link( pMatchThreat->GetRightChild() );
// //
// // 		// 병합한 AET 노드만 삭제한다.
// // 		delete pMatchThreat;
// //
// // 		return true;
// // 	}
// //
// // 	return false;
// //
// // }


/**
 * @brief     두 빔간의 병합할 빔을 선정한다.
 * @param     SELAETDATA * pAETData 비교 방사체 1
 * @param     SELAETDATA * pMatchAETData 비교 방사체 2
 * @return    pAETData 빔으로 선택할 때는 true, pMatchAETData 일때는 false 로 리턴한다.
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-03-08, 오후 8:06
 * @warning
 */
bool CELEmitterMergeMngr::IsSelectAET( SRxAETData *pAETData, SRxAETData *pMatchAETData )
{
    bool bRet = false;

    if( pAETData->uiCoABT > pMatchAETData->uiCoABT ) {
        bRet = true;
    }
    else if( pAETData->uiCoLOB > pMatchAETData->uiCoLOB ) {
        bRet = true;
    }
    else {
        // bRet = false;
    }

    return bRet;

}
//
// // 두 빔간의 병합할 빔을 선정한다.
// /**
//  * @brief     IsSelectABT
//  * @param     SRxABTData * pABTData
//  * @param     SRxABTData * pMatchABTData
//  * @return    bool
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2017-03-08, 오후 8:06
//  * @warning
//  */
// // bool CELEmitterMergeMngr::IsSelectABT( SRxABTData *pABTData, SRxABTData *pMatchABTData )
// // {
// // 	bool bRet = false;
// //
// // 	if( pABTData->peInfo.enValid == E_EL_PESTAT_SUCCESS && pMatchABTData->peInfo.enValid == E_EL_PESTAT_SUCCESS ) {
// // 		// CEP 반경이 적은 빔을 선택
// // 		if( pABTData->peInfo.iCEP < pMatchABTData->peInfo.iCEP )
// // 			bRet = true;
// // 	}
// // 	else if( pABTData->peInfo.enValid == E_EL_PESTAT_SUCCESS ) {
// // 		bRet = true;
// // 	}
// // 	else {
// // 		if( pABTData->uiCoLOB > pMatchABTData->uiCoLOB )
// // 			bRet = true;
// // 	}
// //
// // 	return bRet;
// //
// // }
//
// /**
//  * @brief     빔 노드들을 병합한다.
//  * @param     *pTheThreat 방사체(빔) 정보의 데이터 포인터
//  * @param     *pMatchThreat 병합할 위협 정보의 데이터 포인터
//  * @return    병합이 성공이면 true, 그렇지 않으면 false
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-04-02, 오후 12:54
//  * @warning
//  */
// // void CELEmitterMergeMngr::MergeThreat( bool bMerge )
// // {
// //
// // 	// 빔 노드 병합
// // 	if( m_pUpdateThreatABT->IsABT() == true && m_pDeleteThreatABT->IsABT() == true ) {
// // 		// 빔 병합
// // 		MakeMergedABT( bMerge );
// //
// // 		// 방사체 위협 업데이트
// // 		UpdateMergedAET();
// // 	}
// // 	else { //DTEC_Else
// // 		TRACE( "\n 빔 병합[%d-%d]이 아닙니다.", m_pUpdateThreatABT->IsABT(), m_pDeleteThreatABT->IsABT() );
// // 	}
// //
// // }
//
// /**
//  * @brief     방사체/빔/LOB에 대해서 전시할 목록을 저장합니다.
//  * @param     std::vector<STR_UPDATE_LOB_ABT_AET>* pListMerge
//  * @param     ENUM_THREAT_TYPE enThreatType
//  * @param     bool bMerge
//  * @return    void
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-12-06, 오전 9:36
//  * @warning
//  */
// // void CELEmitterMergeMngr::AddMergeThreatInfo( std::vector<STR_UPDATE_LOB_ABT_AET> *pListMerge, ENUM_THREAT_TYPE enThreatType, bool bMerge )
// // {
// // 	UINT i;
// // 	SThreatFamilyInfo stThreatFamilyInfo;
// //
// // 	STR_UPDATE_LOB_ABT_AET *pSTR_UPDATE_LOB_ABT_AET, *pMatched;
// //
// // 	switch( enThreatType ) {
// // 		case ENUM_LOB_THREAT :
// // 			if( pListMerge->size() == 0 ) {
// // 				GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_MSG, E_WARNING_CRITICAL, enumGMEI_DEVICE, enumGMEI_DEVICE, "병합할 DB 테이블 목록(병합[%d], 삭제[%d])이 없습니다. " , m_pUpdateAETData->uiAETID, m_pDeleteAETData->uiAETID );
// // 			}
// // 			else {
// // 				if( bMerge == false ) {
// // 					// 삭제할 위협 등록
// // 					stThreatFamilyInfo.enOpcode = E_MR_REMOVE;
// // 					stThreatFamilyInfo.nSeqNum = 0;
// // 					stThreatFamilyInfo.iAETID = m_pDeleteAETData->uiAETID;
// // 					stThreatFamilyInfo.iABTID = 0;
// // 					stThreatFamilyInfo.iLOBID = 0;
// // 					stThreatFamilyInfo.bApplySearchFilter = true;
// // 					stThreatFamilyInfo.bIsFISINTTask = m_pDeleteAETExtData->bIsFISINTTask;
// // 					m_pVecThreatInfo->push_back( stThreatFamilyInfo );
// //
// // 					// 변경할 위협 등록
// // 					stThreatFamilyInfo.enOpcode = E_MR_UPDATE_INFO;
// // 					pSTR_UPDATE_LOB_ABT_AET = pListMerge->data();
// // 					for( i=1 ; i <= pListMerge->size() ; ++i ) {
// // 						stThreatFamilyInfo.nSeqNum = pSTR_UPDATE_LOB_ABT_AET->uiSeqNum;
// // 						stThreatFamilyInfo.iAETID = m_pUpdateABTData->uiAETID;
// // 						stThreatFamilyInfo.iABTID = m_pUpdateABTData->uiABTID;
// // 						stThreatFamilyInfo.iLOBID = pSTR_UPDATE_LOB_ABT_AET->uiLOBID;
// // 						stThreatFamilyInfo.bApplySearchFilter = true;
// //
// // 						if( m_pUpdateAETData->uiAETID == pSTR_UPDATE_LOB_ABT_AET->uiAETID )
// // 							stThreatFamilyInfo.bIsFISINTTask = m_pUpdateAETExtData->bIsFISINTTask;
// // 						else
// // 							stThreatFamilyInfo.bIsFISINTTask = m_pDeleteAETExtData->bIsFISINTTask;
// //
// // 						m_pVecThreatInfo->push_back( stThreatFamilyInfo );
// // 						++ pSTR_UPDATE_LOB_ABT_AET;
// // 					}
// //
// // 				}
// // 				else {
// // 					// 변경할 위협 등록
// // 					stThreatFamilyInfo.enOpcode = E_MR_UPDATE_INFO;
// // 					pSTR_UPDATE_LOB_ABT_AET = pListMerge->data();
// // 					for( i=1 ; i <= pListMerge->size() ; ++i ) {
// // 						/*! \todo   업데이트할 데이터가 너무 많기 떄문에 새로운 코드로 해야 할 것 같음.
// // 								\author 조철희 (churlhee.jo@lignex1.com)
// // 								\date 	2016-12-06 17:29:56
// // 						*/
// // 						if( true || pSTR_UPDATE_LOB_ABT_AET->uiABTID == m_pDeleteABTData->uiABTID ) {
// // 							stThreatFamilyInfo.nSeqNum = pSTR_UPDATE_LOB_ABT_AET->uiSeqNum;
// // 							stThreatFamilyInfo.iAETID = m_pUpdateABTData->uiAETID;
// // 							stThreatFamilyInfo.iABTID = m_pUpdateABTData->uiABTID;
// // 							stThreatFamilyInfo.iLOBID = pSTR_UPDATE_LOB_ABT_AET->uiLOBID;
// //
// // 							stThreatFamilyInfo.bApplySearchFilter = true;
// //
// // 							stThreatFamilyInfo.bIsFISINTTask = m_pDeleteAETExtData->bIsFISINTTask;
// //
// // 							m_pVecThreatInfo->push_back( stThreatFamilyInfo );
// // 						}
// // 						++ pSTR_UPDATE_LOB_ABT_AET;
// // 					}
// // 				}
// // 			}
// // 			break;
// //
// // 		case ENUM_ABT_THREAT :
// // 			if( pListMerge->size() <= 1 ) { //DTEC_Else
// // 				GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_MSG, E_WARNING_CRITICAL, enumGMEI_DEVICE, enumGMEI_DEVICE, "병합할 DB 테이블 목록(병합[%d], 삭제[%d])이 없습니다. " , m_pUpdateAETData->uiAETID, m_pDeleteAETData->uiAETID );
// // 			}
// // 			else {
// // 				if( bMerge == false ) {
// // 					// 삭제할 위협 등록
// // 					pMatched = NULL;
// // 					pSTR_UPDATE_LOB_ABT_AET = pListMerge->data();
// // 					for( i=0 ; i < pListMerge->size()-1 ; ++i ) {
// // 						if( m_pDeleteABTData->uiABTID == pSTR_UPDATE_LOB_ABT_AET->uiABTID ) {
// // 							pMatched = pSTR_UPDATE_LOB_ABT_AET;
// // 						}
// //
// // 						++ pSTR_UPDATE_LOB_ABT_AET;
// // 					}
// //
// // 					if( pMatched != NULL ) {
// // 						stThreatFamilyInfo.enOpcode = E_MR_REMOVE;
// // 						stThreatFamilyInfo.nSeqNum = 0;
// // 						stThreatFamilyInfo.iAETID = pMatched->uiAETID;
// // 						stThreatFamilyInfo.iABTID = pMatched->uiABTID;
// // 						stThreatFamilyInfo.iLOBID = 0;
// //
// // 						stThreatFamilyInfo.bApplySearchFilter = true;
// //
// // 						stThreatFamilyInfo.bIsFISINTTask = m_pDeleteAETExtData->bIsFISINTTask;
// //
// // 						m_pVecThreatInfo->push_back( stThreatFamilyInfo );
// // 					}
// // 					else { //DTEC_Else
// // 						GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_MSG, E_WARNING_CRITICAL, enumGMEI_DEVICE, enumGMEI_DEVICE, "병합[%d], 삭제[%d] 에러입니다." , m_pUpdateAETData->uiAETID, m_pDeleteAETData->uiAETID );
// // 					}
// //
// // 				}
// // 				else {
// // 					// 삭제할 위협 등록
// // 					pMatched = NULL;
// // 					pSTR_UPDATE_LOB_ABT_AET = pListMerge->data();
// // 					for( i=0 ; i < pListMerge->size()-1 ; ++i ) {
// // 						if( m_pDeleteABTData->uiABTID == pSTR_UPDATE_LOB_ABT_AET->uiABTID ) {
// // 							pMatched = pSTR_UPDATE_LOB_ABT_AET;
// // 						}
// //
// // 						++ pSTR_UPDATE_LOB_ABT_AET;
// // 					}
// //
// // 					if( pMatched != NULL ) {
// // 						stThreatFamilyInfo.enOpcode = E_MR_REMOVE;
// // 						stThreatFamilyInfo.nSeqNum = 0;
// // 						stThreatFamilyInfo.iAETID = pMatched->uiAETID;
// // 						stThreatFamilyInfo.iABTID = pMatched->uiABTID;
// // 						stThreatFamilyInfo.iLOBID = 0;
// //
// // 						stThreatFamilyInfo.bApplySearchFilter = true;
// //
// // 						stThreatFamilyInfo.bIsFISINTTask = m_pDeleteAETExtData->bIsFISINTTask;
// //
// // 						m_pVecThreatInfo->push_back( stThreatFamilyInfo );
// // 					}
// // 					else { //DTEC_Else
// // 						GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_MSG, E_WARNING_CRITICAL, enumGMEI_DEVICE, enumGMEI_DEVICE, "병합[%d], 삭제[%d] 에러입니다." , m_pUpdateAETData->uiAETID, m_pDeleteAETData->uiAETID );
// // 					}
// //
// // 				}
// // 			}
// // 			break;
// //
// // 		case ENUM_AET_THREAT :
// // 			if( pListMerge->size() > _spOne ) {
// // 				if( bMerge == false ) {
// // 					// LOB에서 방사체 번호를 부여했기 때문에 생략함.
// // 				}
// // 				else {
// // // 					// 삭제할 위협 등록
// // // 					pMatched = NULL;
// // // 					pSTR_UPDATE_LOB_ABT_AET = pListMerge->data();
// // // 					for( i=0 ; i < pListMerge->size()-2 ; ++i ) {
// // // 						if( m_pDeleteAETData->uiAETID == pSTR_UPDATE_LOB_ABT_AET->uiAETID ) {
// // // 							pMatched = pSTR_UPDATE_LOB_ABT_AET;
// // // 						}
// // //
// // // 						++ pSTR_UPDATE_LOB_ABT_AET;
// // // 					}
// // //
// // // 					if( pMatched != NULL ) {
// // // 						stThreatFamilyInfo.eStat = E_MR_REMOVE;
// // // 						stThreatFamilyInfo.nSeqNum = 0;
// // // 						stThreatFamilyInfo.iAETID = pMatched->uiAETID;
// // // 						stThreatFamilyInfo.iABTID = 0;
// // // 						stThreatFamilyInfo.iLOBID = 0;
// // //
// // // 						stThreatFamilyInfo.bIsFISINTTask = m_pDeleteAETExtData->bIsFISINTTask;
// // //
// // // 						m_pVecThreatInfo->push_back( stThreatFamilyInfo );
// // // 					}
// // // 					else {
// // // 						GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_MSG, E_WARNING_CRITICAL, enumGMEI_DEVICE, enumGMEI_DEVICE, "병합[%d], 삭제[%d] 에러입니다." , m_pUpdateAETData->uiAETID, m_pDeleteAETData->uiAETID );
// // // 					}
// // 				}
// // 			}
// // 			else { //DTEC_Else
// // 				GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_MSG, E_WARNING_CRITICAL, enumGMEI_DEVICE, enumGMEI_DEVICE, "병합할 DB 테이블 목록(병합[%d], 삭제[%d])이 없습니다. " , m_pUpdateAETData->uiAETID, m_pDeleteAETData->uiAETID );
// // 			}
// // 			break;
// //
// // 		case ENUM_UNK_THREAT :
// // 		default :
// // 			{ //DTEC_Else
// //
// // 			}
// // 			break;
// //
// // 	}
// //
// // }
//
// /**
//  * @brief     빔 병합 정보를 이용하여 방사체 정보를 업데이트 한다.
//  * @param     void
//  * @return    void
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2017-02-16, 오후 2:26
//  * @warning
//  */
// // void CELEmitterMergeMngr::UpdateMergedAET()
// // {
// //
// // 	if( m_pUpdateThreatAET != NULL ) {
// // 		m_pUpdateAETData->uiCoLOB = GetCountLOBInThreat( m_pUpdateThreatAET );
// //
// // 		m_pUpdateAETData->tiFirstSeenTime = min( m_pUpdateAETData->tiFirstSeenTime, m_pUpdateABTData->tiLastSeenTime );
// // 		m_pUpdateAETData->tiLastSeenTime = max( m_pUpdateAETData->tiLastSeenTime, m_pUpdateABTData->tiLastSeenTime );
// //
// // 		// 주파수 정보
// // 		UpdateFreqInfo( m_pUpdateAETData, m_pUpdateAETExtData, m_pUpdateABTData, m_pUpdateABTExtData );
// //
// // 		// PRI 정보
// // 		UpdatePRIInfo( m_pUpdateAETData, m_pUpdateAETExtData, m_pUpdateABTData, m_pUpdateABTExtData );
// //
// // 		// 펄스폭 정보
// // 		UpdatePWInfo( m_pUpdateAETData, m_pUpdateAETExtData, m_pUpdateABTData, m_pUpdateABTExtData );
// //
// // 		// 신호세기 정보
// // 		UpdatePAInfo( m_pUpdateAETData, m_pUpdateAETExtData, m_pUpdateABTData, m_pUpdateABTExtData );
// //
// // 		// 위치 산출 정보
// // 		UpdatePEInfo( m_pUpdateAETData, m_pUpdateAETExtData, m_pUpdateThreatAET );
// //
// // 		// CED/EOB 식별
// // 		UpdateIDInfo( m_pUpdateAETData, m_pUpdateAETExtData, m_pUpdateThreatAET );
// //
// // 		// 빔 유효성 업데이트
// // 		UpdateBeamValidity( m_pUpdateAETData, m_pUpdateAETExtData, m_pUpdateThreatAET );
// //
// // 		m_pUpdateAETExtData->nCoTotalPdw = GetCountPDWInThreat( m_pUpdateThreatAET );		// m_pLOBData->iNumOfPDW;
// // 		m_pUpdateAETExtData->nCoTotalIQ = GetCountIQInThreat( m_pUpdateThreatAET );		//+= m_pLOBData->iNumOfIQ;
// //
// // 		m_pUpdateAETExtData->enBeamEmitterStat = E_MR_UPDATE;
// //
// // 		m_pUpdateAETExtData->iTaskType = m_pLOBData->iTaskType / 2;
// //
// // 		// pAETExtData->bIntraMop = ( pAETData->intraInfo.iType != E_AET_MOP_UNK ? true : pAETExtData->bIntraMop );
// //
// // 		m_pUpdateAETExtData->uiSeqNum = m_nSeqNum;
// //
// // 	}
// //
// // }
//
// /**
//  * @brief     방사체 위협을 시작으로 빔의 LOB 갯수를 구한다.
//  * @param     CELThreat * pThreatAET
//  * @return    int
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2017-03-14, 오후 2:55
//  * @warning
//  */
// // int CELEmitterMergeMngr::GetCountPDWInThreat( CELThreat *pThreatAET )
// // {
// // 	SELABTDATA_EXT *pABTExtData;
// // 	CELThreat *pThreatABT;
// //
// // 	int nCoPDW=0;
// //
// // 	pThreatABT = GetHeaderThreat( pThreatAET );
// // 	while( pThreatABT != NULL ) {
// // 		pABTExtData = GetABTExtData( pThreatABT->m_nIndex );
// // 		nCoPDW += pABTExtData->nCoTotalPdw;
// // 		pThreatABT = GetNextThreat( pThreatABT );
// // 	}
// // 	return nCoPDW;
// // }
//
// /**
//  * @brief     방사체 위협을 시작으로 빔의 IQ 갯수를 구한다.
//  * @param     CELThreat * pThreatAET
//  * @return    int
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2017-03-14, 오후 2:55
//  * @warning
//  */
// // int CELEmitterMergeMngr::GetCountIQInThreat( CELThreat *pThreatAET )
// // {
// // 	SELABTDATA_EXT *pABTExtData;
// // 	CELThreat *pThreatABT;
// //
// // 	int nCoIQ=0;
// //
// // 	pThreatABT = GetHeaderThreat( pThreatAET );
// // 	while( pThreatABT != NULL ) {
// // 		pABTExtData = GetABTExtData( pThreatABT->m_nIndex );
// // 		nCoIQ += pABTExtData->nCoTotalIQ;
// // 		pThreatABT = GetNextThreat( pThreatABT );
// // 	}
// // 	return nCoIQ;
// // }
//
// /**
//  * @brief     방사체 위협을 시작으로 빔의 LOB 갯수를 구한다.
//  * @param     CELThreat * pThreatAET
//  * @return    int
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2017-03-14, 오후 3:03
//  * @warning
//  */
// // int CELEmitterMergeMngr::GetCountLOBInThreat( CELThreat *pThreatAET )
// // {
// // 	SRxABTData *pABTData;
// // 	CELThreat *pThreatABT;
// //
// // 	int uiCoLOB=0;
// //
// // 	pThreatABT = GetHeaderThreat( pThreatAET );
// // 	while( pThreatABT != NULL ) {
// // 		pABTData = GetABTData( pThreatABT->m_nIndex );
// // 		uiCoLOB += pABTData->uiCoLOB;
// //
// // 		pThreatABT = GetNextThreat( pThreatABT );
// // 	}
// // 	return uiCoLOB;
// // }
//
// /**
//  * @brief     빔 병합 정보를 이용하여 방사체 정보를 업데이트 한다.
//  * @param     void
//  * @return    void
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-12-06, 오후 5:47
//  * @warning
//  */
// // void CELEmitterMergeMngr::MakeMergedABT( bool bMerge )
// // {
// // 	// 빔 추가로 했을 때는 아래 루틴을 처리하지 말아야 함.
// // 	if( bMerge == true ) {
// // 		m_pUpdateABTData->uiCoLOB += m_pDeleteABTData->uiCoLOB;
// // 	}
// //
// // 	m_pUpdateABTData->tiFirstSeenTime = min( m_pUpdateABTData->tiFirstSeenTime, m_pDeleteABTData->tiFirstSeenTime );
// // 	m_pUpdateABTData->tiLastSeenTime = max( m_pUpdateABTData->tiLastSeenTime, m_pDeleteABTData->tiLastSeenTime );
// //
// // 	m_pUpdateABTData->firstReportedTime = min( m_pUpdateABTData->firstReportedTime, m_pDeleteABTData->firstReportedTime );
// // 	m_pUpdateABTData->finalReportedTime = max( m_pUpdateABTData->finalReportedTime, m_pDeleteABTData->finalReportedTime );
// // 	m_pUpdateABTData->finalAlarmTime = max( m_pUpdateABTData->finalAlarmTime, m_pDeleteABTData->finalAlarmTime );
// //
// // 	// 수동 위치 산출 관련 결과 미반영
// // // 	if( m_pDeleteAETExtData->bManualPosEstPreferred == true ) {
// // // 		m_pUpdateAETExtData->bManualPosEstPreferred = true;
// // // 	}
// // //
// // // 	if( m_pDeleteABTExtData->bManualPosEstPreferred == true ) {
// // // 		m_pUpdateABTExtData->bManualPosEstPreferred = true;
// // // 	}
// //
// // 	/*! \todo   나머지 주파수, PRI, 펄스폭, 신호세기 등은 2개 간의 병합을 해야 함.
// // 			\author 조철희 (churlhee.jo@lignex1.com)
// // 			\date 	2016-11-28 21:46:02
// // 	*/
// //
// // 	// 기타 정보
// // 	m_pUpdateABTExtData->nCoTotalPdw += m_pDeleteABTExtData->nCoTotalPdw;
// // 	m_pUpdateABTExtData->nCoTotalIQ += m_pDeleteABTExtData->nCoTotalIQ;
// //
// // 	m_pUpdateABTExtData->iLOBPoolIndex = 0;
// //
// // }
//
// /**
//  * @brief     ABT 노드 들을 합쳐서 하나로 만든다.
//  * @param     *pTheThreat 방사체(빔) 정보의 데이터 포인터
//  * @param     *pMatchThreat 병합할 위협 정보의 데이터 포인터
//  * @return    병합이 성공이면 true, 그렇지 않으면 false
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-04-02, 오후 12:54
//  * @warning
//  */
// // void CELEmitterMergeMngr::MergeABT( CELThreat *pTheThreat, CELThreat *pMatchThreat )
// // {
// // 	bool bRet;
// //
// // 	SRxABTData *pABTData, *pMatchABTData;
// // 	SELABTDATA_EXT *pABTExtData, *pMatchABTExtData;
// //
// // 	pABTData = GetABTData( pTheThreat->m_nIndex );
// // 	pABTExtData = GetABTExtData( pTheThreat->m_nIndex );
// //
// // 	pMatchABTData = GetABTData( pMatchThreat->m_nIndex );
// // 	pMatchABTExtData = GetABTExtData( pMatchThreat->m_nIndex );
// //
// // 	// 2개 빔중에서 삭제될 빔(위협)을 선택하고 병합할 빔에 데이터를 병합한다.
// // 	bRet = IsSelectABT( pABTData, pMatchABTData );
// //
// // 	// 멤버 변수 업데이트
// // 	if( bRet == true ) {
// // 		m_pUpdateThreatABT = pTheThreat;
// // 		m_pDeleteThreatABT = pMatchThreat;
// //
// // 		m_pUpdateABTData = pABTData;
// // 		m_pUpdateABTExtData = pABTExtData;
// // 		m_pDeleteABTData = pMatchABTData;
// // 		m_pDeleteABTExtData = pMatchABTExtData;
// // 	}
// // 	else {
// // 		m_pUpdateThreatABT = pMatchThreat;
// // 		m_pDeleteThreatABT = pTheThreat;
// //
// // 		m_pUpdateABTData = pMatchABTData;
// // 		m_pUpdateABTExtData = pMatchABTExtData;
// // 		m_pDeleteABTData = pABTData;
// // 		m_pDeleteABTExtData = pABTExtData;
// // 	}
// //
// // 	m_pUpdateThreatAET = m_pTheThreatRoot->Find( m_pUpdateThreatABT->m_Idx.nAET );
// // 	m_pUpdateAETData = GetAETData( m_pUpdateThreatAET->m_nIndex );
// // 	m_pUpdateAETExtData = GetAETExtData( m_pUpdateThreatAET->m_nIndex );
// //
// // 	m_pDeleteThreatAET = m_pTheThreatRoot->Find( m_pDeleteThreatABT->m_Idx.nAET );
// // 	m_pDeleteAETData = GetAETData( m_pDeleteThreatAET->m_nIndex );
// // 	m_pDeleteAETExtData = GetAETExtData( m_pDeleteThreatAET->m_nIndex );
// //
// // 	MergeThreat( true );
// //
// // 	return;
// //
// // }
//
// /**
//  * @brief     UpdateAETABTLOBID
//  * @param     *pTheThreat 위협 정보에
//  * @return    리턴값 없음
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-04-08, 오후 5:36
//  * @warning
//  */
// // void CELEmitterMergeMngr::UpdateAETABTLOBID( CELThreat *pTheThreat )
// // {
// // 	int nAET, nABT;
// // 	SELAETDATA *pAETData;
// // 	SRxABTData *pABTData;
// //
// // 	while( pTheThreat != NULL ) {
// // 		nAET = pTheThreat->m_Idx.nAET;
// // 		nABT = pTheThreat->m_Idx.nABT;
// //
// // 		pAETData = GetAETData( pTheThreat->m_nIndex );
// // 		pABTData = GetABTData( pTheThreat->m_nIndex );
// //
// // 		pAETData->uiAETID = nAET;
// //
// // 		pABTData->uiAETID = nAET;
// // 		pABTData->uiABTID = nABT;
// //
// // 		pTheThreat = pTheThreat->GetRightChild();
// // 	}
// // }
//
/**
 * @brief     유사도가 높은 순 부터 정렬한다.
 * @param     stMergeCanA 병합 후보 데이터
 * @param     stMergeCanB 병합 후보 데이터
 * @return    bool
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-14, 오후 5:28
 * @warning
 */
bool CompareMergeCandidate( SELMERGE_CANDIDATE stMergeCanA, SELMERGE_CANDIDATE stMergeCanB )
{
    bool bRet = false;

    if( stMergeCanA.fLevel < stMergeCanB.fLevel ) {
        bRet = true;
    }
    return bRet;
}

/**
 * @brief     DecideMergeCandidate
 * @return    bool
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-14, 오후 5:28
 * @warning
 */
bool CELEmitterMergeMngr::DecideMergeCandidate()
{
    unsigned int i;
    int nCoMerge;

    SELMERGE_CANDIDATE *pMergeCandidate;

    // 유효값 이상인 것 삭제함.
    nCoMerge = (int) m_vecCanOfMergeLOB.size();
    if( nCoMerge >= 1 ) {
        for( i=0 ; i < m_vecCanOfMergeLOB.size() ; ++i ) { //#FA_C_PotentialUnboundedLoop_T2
            pMergeCandidate = & m_vecCanOfMergeLOB.at(i);

            if( pMergeCandidate->fLevel >= THRESHOLD_OF_MIN_CANDIDATE_LEVEL ) {
                vector<SELMERGE_CANDIDATE>::iterator iterBegin=m_vecCanOfMergeLOB.begin() + (UINT) i;

                //m_vecCanOfMergeLOB.erase( m_vecCanOfMergeLOB.begin()+i, m_vecCanOfMergeLOB.end() );			// QAC 에러 수정 필요
                m_vecCanOfMergeLOB.erase( iterBegin, m_vecCanOfMergeLOB.end() );			// QAC 에러 수정 필요
                break;
            }
        }
    }

    /*! \todo   후보 중에서 위치 산출 정보와 식별 정보를 이용하여 가장 유력한 ABT를 결정한다. 현재는 ABT 간의 병합 레벨만 가지고 결정한다.
                \author 조철희 (churlhee.jo@lignex1.com)
                \date 	2016-03-10 17:53:11
    */
    // Decide...

    return m_vecCanOfMergeLOB.size() != 0;
}

/**
 * @brief     병합 후보 정보에 대해서 정렬을 수행한다.
 * @return    void
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-07-20, 오후 6:40
 * @warning
 */
void CELEmitterMergeMngr::SortMergeCandidate()
{
    sort( m_vecCanOfMergeLOB.begin(), m_vecCanOfMergeLOB.end(), CompareMergeCandidate );
}

/**
 * @brief     트리 노드에서 우측 포인터 노드를 리턴한다.
 * @param     *pThreatAET 위협 데이터 포인터
 * @return    노드
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-07-20, 오후 6:40
 * @warning
 */
CELThreat *CELEmitterMergeMngr::GetNextThreat( CELThreat *pThreatAET )
{
    return pThreatAET->GetRightChild();
}

/**
 * @brief     트리 노드에서 좌측 포인터 노드를 리턴한다.
 * @param     *pThreatAET 위협 데이터 포인터
 * @return    노드
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-07-20, 오후 6:40
 * @warning
 */
CELThreat *CELEmitterMergeMngr::GetHeaderThreat( CELThreat *pThreatAET )
{
    return pThreatAET->GetLeftChild();
}

// /**
//  * @brief     주어진 두 수 범위 안에 포함하는지를 결정한다.
//  * @param     x 입력값
//  * @param     y 입력값
//  * @param     threshIn 임계값
//  * @param     threshOut 임계값
//  * @return    범위안에 들면 true
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-03-07, 오후 4:06
//  * @warning
//  */
// bool CELEmitterMergeMngr::CompInOutDiff( int x, int y, int threshIn, int threshOut )
// {
// 	int diff;
// 	bool bRet;
//
// 	diff = x - y;
//
// 	if( diff >=0 ) {
// 		if( diff <= threshOut ) {
// 			bRet = true;
// 		}
// 		else {
// 			bRet = false;
// 		}
// 	}
// 	else {
// 		if( -diff <= threshIn ) {
// 			bRet = true;
// 		}
// 		else {
// 			bRet = false;
// 		}
// 	}
//
// 	return bRet;
// }

/**
 * @brief     식별 결과를 DB에 기록한다.
 * @param     *pExt LOB 추가 정보의 데이터 포인터
 * @param     i_bIsFilteredLOB 필터 여부 플레그
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-02-17, 오전 9:23
 * @warning
 */
void CELEmitterMergeMngr::InsertLOB( SELLOBDATA_EXT *pExt, bool i_bIsFilteredLOB )
{
    int iIndex;
    SRadarMode *pRadarMode;

    SELEXTDB extDB=SELEXTDB();

    // 식별 정보
    if( m_pLOBOtherInfo == NULL || m_pLOBOtherInfo->bUpdate == false ) {
        // Primary 식별 정보
        iIndex = pExt->aetAnal.idInfo.n3LevelRadarModeIndex[0];
        if( iIndex != 0 ) {
            pRadarMode = m_pIdentifyAlg->GetRadarMode( iIndex );
            strcpy( m_pLOBData->szPrimaryELNOT, pRadarMode->szELNOT );
            strcpy( m_pLOBData->szPrimaryModeCode, pRadarMode->szModeCode );
        }
        else {
            memset( m_pLOBData->szPrimaryELNOT, 0, sizeof(m_pLOBData->szPrimaryELNOT) );
            strcpy( m_pLOBData->szPrimaryModeCode, "ZZ" );
        }

        // Secondary 식별 정보
        iIndex = pExt->aetAnal.idInfo.n3LevelRadarModeIndex[1];
        if( iIndex != 0 ) {
            pRadarMode = m_pIdentifyAlg->GetRadarMode( iIndex );
            strcpy( m_pLOBData->szSecondaryELNOT, pRadarMode->szELNOT );
            strcpy( m_pLOBData->szSecondaryModeCode, pRadarMode->szModeCode );
        }
        else {
            memset( m_pLOBData->szSecondaryELNOT, 0, sizeof(m_pLOBData->szSecondaryELNOT) );
            strcpy( m_pLOBData->szSecondaryModeCode, "ZZ" );
        }

        // Third 식별 정보
        iIndex = pExt->aetAnal.idInfo.n3LevelRadarModeIndex[2];
        if( iIndex != 0 ) {
            pRadarMode = m_pIdentifyAlg->GetRadarMode( iIndex );
            strcpy( m_pLOBData->szTertiaryELNOT, pRadarMode->szELNOT );
            strcpy( m_pLOBData->szTertiaryModeCode, pRadarMode->szModeCode );
        }
        else {
            memset( m_pLOBData->szTertiaryELNOT, 0, sizeof(m_pLOBData->szTertiaryELNOT) );
            strcpy( m_pLOBData->szTertiaryModeCode, "ZZ" );
        }

        pRadarMode = m_pIdentifyAlg->GetRadarMode( m_pLOBData->iRadarModeIndex );

        if( pRadarMode != NULL ) {
            strcpy( m_pLOBData->szFuncCode, m_pIdentifyAlg->GetFunctionCode( pRadarMode->eFunctionCode ) );
            strcpy( m_pLOBData->szRadarModeName, pRadarMode->szRadarModeName );
            strcpy( m_pLOBData->szModulationCode, pRadarMode->szModulationCode );
            strcpy( m_pLOBData->szNickName, pRadarMode->szNickName );
        }
        else {
            memset( m_pLOBData->szFuncCode, 0, sizeof(m_pLOBData->szFuncCode) );
            memset( m_pLOBData->szRadarModeName, 0, sizeof(m_pLOBData->szRadarModeName) );
            memset( m_pLOBData->szModulationCode, 0, sizeof(m_pLOBData->szModulationCode) );
            memset( m_pLOBData->szNickName, 0, sizeof(m_pLOBData->szNickName) );
        }

    }
    // LOB 복사하여 신규 추가 처리(사용자)
    else {
/*        int nRadarIndex, nRadarModeIndex;

        GP_MNGR_CED_LIB2->RTGetRadarIndexFromELNOT( & nRadarIndex, m_pLOBOtherInfo->szElnotPri, m_pSELDBEnvVarIdnf->eCEDDefaultLibType );
        if( nRadarIndex > 0 ) {
            GP_MNGR_CED_LIB2->RTGetRadarModeIndexFromRadarIndexAndMode( & nRadarModeIndex, nRadarIndex, m_pLOBOtherInfo->szModeCodePri, m_pSELDBEnvVarIdnf->eCEDDefaultLibType );

            if( nRadarModeIndex > 0 ) {
                strcpy_s( extDB.szPrimaryELNOT, m_pLOBOtherInfo->szElnotPri );
                strcpy_s( extDB.szPrimaryModeCode, m_pLOBOtherInfo->szModeCodePri );
            }
            else { //DTEC_Else
                pChar = GetElintNotation( 0, (int) m_LOBDataExt.aetAnal.uiAETID, (int) m_LOBDataExt.aetAnal.uiABTID, m_pSELDBEnvVarIdnf->eCEDDefaultLibType, true );
                strcpy_s( extDB.szPrimaryELNOT, _MAX_ELNOT_STRING_SIZE_, pChar );
                strcpy_s( extDB.szPrimaryModeCode, "ZZ" );
            }
        }
        else {
            pRadarMode = NULL;
            if( m_pLOBOtherInfo->szElnotPri[0] == NULL ) {
                pRadarMode = GP_MNGR_CED_LIB2->RTGetRadarModeDataFromMemory( pExt->aetAnal.idInfo.nRadarModeIndex[0], m_pSELDBEnvVarIdnf->eCEDDefaultLibType );
                pChar = GetElintNotation( pRadarMode, (int) m_LOBDataExt.aetAnal.uiAETID, (int) m_LOBDataExt.aetAnal.uiABTID, m_pSELDBEnvVarIdnf->eCEDDefaultLibType, true );
                strcpy_s( extDB.szPrimaryELNOT, _MAX_ELNOT_STRING_SIZE_, pChar );

            }
            else {
                strcpy_s( extDB.szPrimaryELNOT, _MAX_ELNOT_STRING_SIZE_, m_pLOBOtherInfo->szElnotPri );
            }

            if( m_pLOBOtherInfo->szModeCodePri[0] == NULL ) {
                if( pRadarMode != NULL ) {
                    strcpy_s( extDB.szPrimaryModeCode, MAX_SIZE_OF_MODECODE, pRadarMode->stRadarModeLifeCycle.szModeCode );
                }
                else {
                    strcpy_s( extDB.szPrimaryModeCode, MAX_SIZE_OF_MODECODE, "ZZ" );
                }
            }
            else {
                strcpy_s( extDB.szPrimaryModeCode, m_pLOBOtherInfo->szModeCodePri );
            }

        }

        strcpy_s( extDB.szModulationCode, m_pLOBOtherInfo->szModulationCode );
        strcpy_s( extDB.szNickName, m_pLOBOtherInfo->szNickName );
        strcpy_s( extDB.szFunctioncode, m_pLOBOtherInfo->szPriFuncCode );

        strcpy_s( extDB.szSecondaryELNOT, m_pLOBOtherInfo->szElnotSec );
        strcpy_s( extDB.szSecondaryModeCode, m_pLOBOtherInfo->szModeCodeSec );

        strcpy_s( extDB.szThirdELNOT, m_pLOBOtherInfo->szElnotTert );
        strcpy_s( extDB.szThirdModeCode, m_pLOBOtherInfo->szModeCodeTert );     */
    }

    // 방사체/빔/LOB 번호 저장
    extDB.bIsManualEdited = false;

    // 시간 정보 생성
    // 날짜는 현재 날짜로 하고 나머지 시간은 LOB 메시지의 시간으로 설정
    SetupDateTime( pExt );

    //UpdateLOBData( i_bIsFilteredLOB );

    if( m_bScanProcess == false ) {
        if( i_bIsFilteredLOB == false ) {
            Log( enDebug, ".InsertLOB[A%d][B%d][L%d]" , m_pLOBData->uiAETID, m_pLOBData->uiABTID, m_pLOBData->uiLOBID );

            if( m_bDBThread == false ) {
                // LOB 데이터 저장
                InsertToDB_LOB( m_pLOBData, pExt, true );

                // FREQ 레벨값 저장
                if( m_pLOBData->iFreqPositionCount >= _spTwo ) {
                    InsertToDB_Position( m_pLOBData, pExt, true );
                }
                // PRI 레벨값 저장
                if( m_pLOBData->iPRIPositionCount >= _spTwo ) {
                    InsertToDB_Position( m_pLOBData, pExt, false );
                }
            }
            else {
                //m_sqMsg.uiOpcode = CMDCODE_INSERTDB_LOBDATA_;
                //m_sqMsg.usSize = sizeof(STR_LOBDATAEXT);
                //memcpy( & m_sqMsg.x.stLOBDataExt.stLOBData, m_pLOBData, sizeof(SRxLOBData) );
                //memcpy( & m_sqMsg.x.stLOBDataExt.stLOBDataExt, pExt, sizeof(SELLOBDATA_EXT) );

                //GP_MGR_INSERTDB->SendMessage( & m_sqMsg );
            }
        }

        // LOB 저장소에 추가 한다.
        PushLOBLANData( m_pLOBData );
    }

}

/**
 * @brief     ABT 데이터를 DB에 기록한다.
 * @param     *pTheThreat 방사체(빔) 정보의 데이터 포인터
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-15, 오전 10:49
 * @warning
 */
void CELEmitterMergeMngr::InsertABT( CELThreat *pTheThreat, bool bUpdateDB, bool bEnable, UINT nSeqNum, UINT uiAETID, UINT uiABTID, SELMERGE_CANDIDATE *pMergeCandidate )
{
    int iIndex;
    SRadarMode *pRadarMode;

    SRxABTData *pABTData;
    SELABTDATA_EXT *pABTExtData;

    if( pTheThreat != NULL ) {
        if( bEnable == true ) {
            pABTData = GetABTData( pTheThreat->m_nIndex );
            pABTExtData = GetABTExtData( pTheThreat->m_nIndex );

            iIndex = pABTData->iRadarModeIndex;
            if( iIndex != 0 ) {
                pRadarMode = m_pIdentifyAlg->GetRadarMode( iIndex );
                strcpy( pABTData->szPrimaryELNOT, pRadarMode->szELNOT );
                strcpy( pABTData->szPrimaryModeCode, pRadarMode->szModeCode );

                strcpy( pABTData->szFuncCode, m_pIdentifyAlg->GetFunctionCode( pRadarMode->eFunctionCode ) );
                strcpy( pABTData->szRadarModeName, pRadarMode->szRadarModeName );
                strcpy( pABTData->szModulationCode, pRadarMode->szModulationCode );
                strcpy( pABTData->szNickName, pRadarMode->szNickName );

                pABTData->iRadarModePriority = pRadarMode->iRadarModePriority;
                pABTData->iRadarPriority = pRadarMode->iRadarPriority;
            }
            else {
                memset( pABTData->szPrimaryELNOT, 0, sizeof(m_pLOBData->szPrimaryELNOT) );
                strcpy( pABTData->szPrimaryModeCode, "ZZ" );

                pABTData->szFuncCode[0] = 0;
                pABTData->szRadarModeName[0] = 0;
                pABTData->szModulationCode[0] = 0;
                pABTData->szNickName[0] = 0;
            }

            Log( enDebug, ".InsertABT[A%d][B%d]" , pABTData->uiAETID, pABTData->uiABTID );
            if( m_bDBThread == false ) {
                // 빔 레코드 추가
                InsertToDB_ABT( pABTData, pABTExtData, true );

                // FREQ 레벨값 저장
                if( pABTData->iFreqPositionCount >= _spTwo ) {
                    InsertToDB_Position( m_pLOBData, pABTData, pABTExtData, true );
                }
                // PRI 레벨값 저장
                if( pABTData->iPRIPositionCount >= _spTwo ) {
                    InsertToDB_Position( m_pLOBData, pABTData, pABTExtData, false );
                }

            }
            else {
                //m_sqMsg.uiOpcode = CMDCODE_INSERTDB_ABTDATA_;
                //m_sqMsg.usSize = sizeof(STR_ABTDATAEXT);
                //memcpy( & m_sqMsg.x.stABTDataExt.stLOBData, m_pLOBData, sizeof(SRxLOBData) );
                //memcpy( & m_sqMsg.x.stABTDataExt.stABTData, pABTData, sizeof(SRxABTData) );
                //memcpy( & m_sqMsg.x.stABTDataExt.stABTDataExt, pABTExtData, sizeof(SELABTDATA_EXT) );

                //GP_MGR_INSERTDB->SendMessage( & m_sqMsg );
            }

            PushABTLANData( pABTData );
        }

    }

}

void CELEmitterMergeMngr::PushLOBLANData( SRxLOBData *pLOBData )
{

// 	Log( enNormal, "\t[%8d/%8d/%8d] %s %5.1f [%s] %7.1f [%s] %7.1f %7.1f %5.1f R[%3d] T[%3d]" ,
// 		pLOBData->uiAETID, pLOBData->uiABTID, pLOBData->uiLOBID,
// 		aet_signal_type[pLOBData->iSignalType],
// 		pLOBData->fDOAMean,
// 		aet_freq_type[pLOBData->iFreqType], pLOBData->fFreqMean,
// 		aet_pri_type[pLOBData->iPRIType], pLOBData->fPRIMean,
// 		pLOBData->fPWMean,
// 		pLOBData->fPAMean,
// 		pLOBData->iRadarModeIndex,
// 		pLOBData->iThreatIndex
// 		);

    m_VecLOBData.push_back( *pLOBData );

}

/**
  * @brief
  * @param		CELThreat * pABTThreat
  * @return 	void
  * @date			2019/04/19 16:30
*/
void CELEmitterMergeMngr::PushABTLANData( CELThreat *pTheThreat )
{
    SRxABTData *pABTData;
    //SELABTDATA_EXT *pABTExtData;

    if( pTheThreat != NULL ) {
        pABTData = GetABTData( pTheThreat->m_nIndex );
        //pABTExtData = GetABTExtData( pTheThreat->m_nIndex );

        PushABTLANData( pABTData );
    }
}

/**
 * @brief CELEmitterMergeMngr::PushABTLANData
 * @param pABTData
 */
void CELEmitterMergeMngr::PushABTLANData( SRxABTData *pABTData )
{
    std::vector<SRxABTData>::iterator iter;

    for( iter=m_VecABTData.begin() ; iter != m_VecABTData.end() ; ++iter ) {
        if( (*iter).uiABTID == pABTData->uiABTID ) {
            iter = m_VecABTData.erase( iter );
            break;
        }

    }

// 	Log( enNormal, "\t[%8d/%8d] %s [%s] %7.1f [%s] %7.1f %7.1f %5.1f[dBm] R[%3d] T[%3d]" ,
// 		pABTData->uiAETID, pABTData->uiABTID,
// 		aet_signal_type[pABTData->iSignalType],
// 		aet_freq_type[pABTData->iFreqType], pABTData->fFreqMean,
// 		aet_pri_type[pABTData->iPRIType], pABTData->fPRIMean,
// 		pABTData->fPWMean,
// 		pABTData->fPAMean,
// 		pABTData->iRadarModeIndex,
// 		pABTData->iThreatIndex
// 		);

    m_VecABTData.push_back( *pABTData );

}

/**
 * @brief CELEmitterMergeMngr::PushAETLANData
 * @param pAETData
 */
void CELEmitterMergeMngr::PushAETLANData( SRxAETData *pAETData )
{
    std::vector<SRxAETData>::iterator iter;

    for( iter=m_VecAETData.begin() ; iter != m_VecAETData.end() ; ++iter ) {
        if( (*iter).uiAETID == pAETData->uiAETID ) {
            m_VecAETData.erase( iter );
            break;
        }

    }

// 	Log( enNormal, "\t[%8d/%8d] %s [%s] %7.1f [%s] %7.1f %7.1f %5.1f[dBm] R[%3d] T[%3d]" ,
// 		pABTData->uiAETID, pABTData->uiABTID,
// 		aet_signal_type[pABTData->iSignalType],
// 		aet_freq_type[pABTData->iFreqType], pABTData->fFreqMean,
// 		aet_pri_type[pABTData->iPRIType], pABTData->fPRIMean,
// 		pABTData->fPWMean,
// 		pABTData->fPAMean,
// 		pABTData->iRadarModeIndex,
// 		pABTData->iThreatIndex
// 		);

    m_VecAETData.push_back( *pAETData );

}

/**
 * @brief     방사체(AET) 내용을 DB 테이블에 기록한다.
 * @param     *pTheThreat 방사체(빔) 정보의 데이터 포인터
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-16, 오후 2:25
 * @warning
 */
void CELEmitterMergeMngr::InsertAET( CELThreat *pTheThreat, bool bUpdateDB, bool bEnable, UINT nSeqNum, UINT uiAETID, bool bDirectDB )
{
    int iLatitude=0, iLongitude=0;

    //char *pChar;
    int iIndex;
    CString strMsg;
    SELEXTDB extDB=SELEXTDB();

    SRxAETData *pAETData;
    SELAETDATA_EXT *pAETExtData;

    //STR_CEDEOBID_INFO *pIDInfo;
    SThreat *pThreat;
    SRadarMode *pRadarMode;

    if( pTheThreat != NULL && bEnable == true ) {
        pAETData = GetAETData( pTheThreat->m_nIndex );
        pAETExtData = GetAETExtData( pTheThreat->m_nIndex );

        Log( enDebug, ".InsertAET[A%d]" , pAETData->uiAETID );

        //pIDInfo = & pAETData->idInfo;

        // LOB 클러스터링으로 고정 ID 로 저장
        if( uiAETID != 0 ) {
            extDB.uiAETID = uiAETID;
        }
        else {
            // extDB.uiAETID = 0;
            // extDB.uiABTID = 0;
        }

#ifdef _POCKETSONATA_
#elif defined(_ELINT_)
#else
        // 추가 자료 만들기
        // 임무 정보
        memcpy( extDB.acMissionID, GetMissionID(m_nLinkNum), sizeof(char) * DEF_MISSION_ID_LENGTH );
        memcpy( extDB.acMissionName, GetMissionName(m_nLinkNum), sizeof(char) * DEF_MISSION_NAME_LENGTH );

        // 연동기 번호 즉 링크 번호 추가
        extDB.iLinkNum = m_nLinkNum;

        // 식별 정보
        strcpy_s( extDB.szIdInfo, MAX_SIZE_OF_IDINFO, & strIdResult[ pIDInfo->eIdResult ][0] );
#endif

        // 수동 위치 변경시 변경
        if( m_pLOBOtherInfo == NULL || m_pLOBOtherInfo->bUpdate == false ) {
            iIndex = pAETData->iRadarModeIndex;
            if( iIndex != 0 ) {
                pRadarMode = m_pIdentifyAlg->GetRadarMode( iIndex );
                strcpy( pAETData->szPrimaryELNOT, pRadarMode->szELNOT );
                strcpy( pAETData->szPrimaryModeCode, pRadarMode->szModeCode );

                strcpy( pAETData->szFuncCode, m_pIdentifyAlg->GetFunctionCode( pRadarMode->eFunctionCode ) );
                strcpy( pAETData->szRadarModeName, pRadarMode->szRadarModeName );
                strcpy( pAETData->szModulationCode, pRadarMode->szModulationCode );
                strcpy( pAETData->szNickName, pRadarMode->szNickName );

                pAETData->iPlatformType = pRadarMode->ePlatform;

                pAETData->iRadarModePriority = pRadarMode->iRadarModePriority;
                pAETData->iRadarPriority = pRadarMode->iRadarPriority;

            }
            else {
                pAETData->szPrimaryELNOT[0] = 0;
                strcpy( pAETData->szPrimaryModeCode, "ZZ" );

                pAETData->szFuncCode[0] = 0;
                pAETData->szRadarModeName[0] = 0;
                pAETData->szModulationCode[0] = 0;
                pAETData->szNickName[0] = 0;

                pAETData->iPlatformType = 0;

                pAETData->iRadarModePriority = 0;
                pAETData->iRadarPriority = 0;

                pAETData->iPinNum = 0;


            }

            iIndex = pAETData->iThreatIndex;
            if( iIndex != 0 ) {
                pThreat = m_pIdentifyAlg->GetThreat( iIndex );

                pAETData->iPinNum = pThreat->iPinNum;
                
                strcpy( pAETData->szPlaceNameKor, pThreat->szPlaceNameKor );

                pAETData->szThreatFuncCode[0] = 0;
                //strcpy( pAETData->szPlaceNameKor, pThreat->szThreatFuncCode );
                
            }
            else {
                pAETData->iPinNum = 0;

                pAETData->szPlaceNameKor[0] = 0;

                pAETData->szThreatFuncCode[0] = 0;
            }

// 			pRadarMode = GP_MNGR_CED_LIB2->RTGetRadarModeDataFromMemory( pIDInfo->nRadarModeIndex[0], m_pSEnvironVariable->eCEDDefaultLibType );
// 			pRadarMode1 = GP_MNGR_CED_LIB2->RTGetRadarModeDataFromMemory( pIDInfo->nRadarModeIndex[1], m_pSEnvironVariable->eCEDDefaultLibType );
// 			pRadarMode2 = GP_MNGR_CED_LIB2->RTGetRadarModeDataFromMemory( pIDInfo->nRadarModeIndex[2], m_pSEnvironVariable->eCEDDefaultLibType );
//
// 			if( pAETExtData->xMannualEdited.x.idInfo == (UINT) 1 ) {
// 				pChar = pAETExtData->szELNOT;
// 				strcpy_s( extDB.szPrimaryELNOT, _MAX_ELNOT_STRING_SIZE_, pChar );
// 			}
// 			else {
// 				if( pRadarMode != NULL ) {
// 					strcpy_s( extDB.szPrimaryELNOT, pRadarMode->szELNOT );
// 					strcpy_s( extDB.szPrimaryModeCode, MAX_SIZE_OF_MODECODE, pRadarMode->strModulationCode );
//
// 					strcpy_s( extDB.szNickName, pRadarMode->szNickName );
//
// 					strMsg = GP_MNGR_CED_LIB2->m_CELCEDComon.GetFunctionCodes( pRadarMode->eFunctionCode );
// 					strcpy_s( extDB.szFunctioncode, MAX_SIZE_OF_FUNCTIONCODE, strMsg.GetBuffer() );
//
// 					// AET 추가 정보
// 					pChar = GP_MNGR_CED_LIB2->m_CELCEDComon.GetSZPlatformCode( pRadarMode->ePlatform );
// 					strcpy_s( extDB.szPlatformCode, MAX_SIZE_OF_PLATFORMCODE, pChar );
//
// 					extDB.iRadarPriority = pRadarMode->nPriority;
// 					extDB.iRadarModePriority = pRadarMode->nRadarModenPriority;
//
// 				}
// 				else {
// 					pChar = GetElintNotation( NULL, (int) pAETData->uiAETID, (int) pAETExtData->nUnIDABTID, m_pSEnvironVariable->eCEDDefaultLibType, true );
//
// 					// 빔 정보로 ELNOT 변경
// 					if( pAETExtData->szELNOT[0] != NULL ) {
// 						strcpy_s( extDB.szPrimaryELNOT, pAETExtData->szELNOT );
// 					}
// 					else {
// 						strcpy_s( extDB.szPrimaryELNOT, _MAX_ELNOT_STRING_SIZE_, pChar );
// 					}
//
// 					extDB.szPrimaryModeCode[0] = NULL;
// 					extDB.szNickName[0] = NULL;
// 					extDB.szFunctioncode[0] = NULL;
// 					extDB.szPlatformCode[0] = NULL;
// 				}
// 			}
//
// 			// 2차 식별
// 			if( pRadarMode1 != NULL ) {
// 				strcpy_s( extDB.szSecondaryELNOT, _MAX_ELNOT_STRING_SIZE_, pRadarMode1->szELNOT );
// 				strcpy_s( extDB.szSecondaryModeCode, MAX_SIZE_OF_MODECODE, pRadarMode1->strModulationCode  );
// 			}
// 			else {
// 				extDB.szSecondaryELNOT[0] = NULL;
// 				extDB.szSecondaryModeCode[0] = NULL;
// 			}
//
// 			// 3차 식별
// 			if( pRadarMode2 != NULL ) {
// 				strcpy_s( extDB.szThirdELNOT, _MAX_ELNOT_STRING_SIZE_, pRadarMode2->szELNOT );
// 				strcpy_s( extDB.szThirdModeCode, MAX_SIZE_OF_MODECODE, pRadarMode2->strModulationCode  );
// 			}
// 			else {
// 				extDB.szThirdELNOT[0] = NULL;
// 				extDB.szThirdModeCode[0] = NULL;
// 			}
//
// 		}
// 		else {
// 			strcpy_s( extDB.szPrimaryELNOT, m_pLOBOtherInfo->szElnotPri );
// 			strcpy_s( extDB.szPrimaryModeCode, m_pLOBOtherInfo->szModeCodePri );
//
// 			strcpy_s( extDB.szNickName, m_pLOBOtherInfo->szNickName );
// 			strcpy_s( extDB.szModulationCode, m_pLOBOtherInfo->szModulationCode );
// 			strcpy_s( extDB.szFunctioncode, m_pLOBOtherInfo->szPriFuncCode );
//
// 			strcpy_s( extDB.szSecondaryELNOT, m_pLOBOtherInfo->szElnotSec );
// 			strcpy_s( extDB.szSecondaryModeCode, m_pLOBOtherInfo->szModeCodeSec );
//
// 			strcpy_s( extDB.szThirdELNOT, m_pLOBOtherInfo->szElnotTert );
// 			strcpy_s( extDB.szThirdModeCode, m_pLOBOtherInfo->szModeCodeTert );
//
// 			pChar = m_theIdentifyAlg.GetPlatformCode( pIDInfo->nRadarModeIndex[0], m_pSEnvironVariable->eCEDDefaultLibType );
// 			if( pChar != NULL ) {
// 				strcpy_s( extDB.szPlatformCode, pChar );
// 			}
            //extDB.iRadarPriority = m_pLOBOtherInfo->iRadarPriority;
            //extDB.iRadarModePriority = m_pLOBOtherInfo->iRadarModePriority;
        }

        // 방사체 정보 변경시 처리
//        if( pAETExtData->xMannualEdited.x.idInfo == (UINT) 1 ) {
//            extDB.iPinNumber = pAETExtData->iPinNumber;
//
//            UpdateIDInfo( extDB.szIdInfo, pAETExtData, & extDB );
//        }
//        else {
//            extDB.iPinNumber = (int) m_theIdentifyAlg.GetEOBPinNumber( pIDInfo->nThreatIndex, m_pSEnvironVariable->eEOBDefaultLibType );
//        }

// 		if( pIDInfo->nThreatIndex != 0 ) {
// 			//pChar = m_theIdentifyAlg.GetThreatName( pIDInfo->nThreatIndex, m_pSEnvironVariable->eEOBDefaultLibType );
// 			pChar = GP_MNGR_CED_LIB2->RTGetKoreaSiteName( pIDInfo->nThreatIndex, m_pSEnvironVariable->eEOBDefaultLibType );
// 			if( pChar != NULL ) {
// 				strcpy_s( extDB.szKoreaSiteName, _MAX_SIZE_OF_THREATNAME_, pChar );
// 			}
//
// 			pChar = GP_MNGR_CED_LIB2->RTGetEOBBENumber( pIDInfo->nThreatIndex, m_pSEnvironVariable->eEOBDefaultLibType );
// 			if( pChar != NULL ) {
// 				strcpy_s( extDB.szBENumber, MAX_SIZE_OF_BENUMBER, pChar );
// 			}
//
// 			pChar = GP_MNGR_CED_LIB2->RTGetEOBFunctionCode( pIDInfo->nThreatIndex, m_pSEnvironVariable->eEOBDefaultLibType );
// 			if( pChar != NULL ) {
// 				strcpy_s( extDB.szThreatFunctionCode, MAX_SIZE_OF_FUNCTIONCODE, pChar );
// 			}
// 		}
// 		else {
// 			extDB.szKoreaSiteName[0] = NULL;
// 			extDB.szBENumber[0] = NULL;
// 			extDB.szThreatFunctionCode[0] = NULL;
//
// 		}
//
// 		extDB.iThreatPriority = GP_MNGR_CED_LIB2->RTGetEOBPriority( pIDInfo->nThreatIndex, m_pSEnvironVariable->eEOBDefaultLibType );
// 		m_theIdentifyAlg.GetEOBLatLong( & iLatitude, & iLongitude, pIDInfo->nThreatIndex, pIDInfo->nDeviceIndex, m_pSEnvironVariable->eEOBDefaultLibType );
// 		extDB.iThreatDistance = m_theIdentifyAlg.CalDistanceNM( iLatitude, iLongitude, pAETData->peInfo.iLatitude, pAETData->peInfo.iLongitude );
// 		extDB.iEquipNumber = GetEquipNumber( pIDInfo );
//
// // #ifdef _AUTO_SEQUENCE_
// // 		extDB.uiSeqNum = 0;
// // #else
// 		extDB.uiSeqNum = nSeqNum;		// m_nSeqNum;
// //#endif
//
// 		extDB.iRadarModeIndex = pIDInfo->nRadarIndex[0];
// 		extDB.iThreatIndex = pIDInfo->nThreatIndex;
//
// 		//////////////////////////////////////////////////////////////////////////
// 		// extDB.iPinNumber, pData->peInfo.iLatitude, pData->peInfo.iLongitude,
// 		// extDB.szPrimaryELNOT
// 		//UpdateManaulInfo( pAETData, & extDB, pAETData->uiAETID );
// 		if( bUpdateDB == true ) {
// 			string strTableName="E_AA_GMI_EMITTER";
// 			CString strCondition = _T(""), strTemp = _T("");
// 			list<_FIELD_INFO> listFieldInfo;
//
// 			_FIELD_INFO stField("","");
//
// 			stField.strFieldName = "MANUALPOSESTPREFERRED";
// 			strTemp.Format( "%d", pAETExtData->bManualPosEstPreferred );
// 			stField.strFieldValue = strTemp;
// 			listFieldInfo.push_back( stField );
//
// 			if( pAETData->peInfo.iManualLongitude != 0 ) {
// 				stField.strFieldName = "MANUAL_POS_EST_LONG";
// 				strTemp.Format( "%d", pAETData->peInfo.iManualLongitude );
// 				stField.strFieldValue = strTemp;
// 				listFieldInfo.push_back( stField );
// 			}
// 			if( pAETData->peInfo.iManualLatitude != 0 ) {
// 				stField.strFieldName = "MANUAL_POS_EST_LAT";
// 				strTemp.Format( "%d", pAETData->peInfo.iManualLatitude );
// 				stField.strFieldValue = strTemp;
// 				listFieldInfo.push_back( stField );
// 			}
//
// 			strCondition.Format( "SEQ_NUM >='%d' AND MISSION_ID='%s'", pAETExtData->uiSeqNum, extDB.acMissionID );
// 			_CALL_DB( UpdateToDB( strTableName, & listFieldInfo, nullptr, strCondition.GetBuffer(), NULL, false, true ) )
//
// 		}

        // 방사체 레코드 추가
        if( m_bDBThread == false ) {
            InsertToDB_AET( pAETData, pAETExtData, & extDB );
        }
        else {
            //SendInsertDBThread( CMDCODE_INSERTDB_EMITTERDATA_, m_pLOBData, pAETData, pAETExtData, & extDB );
        }

        PushAETLANData( pAETData );

    }


}

// /**
//  * @brief     링크1/2의 임무ID를 갖고 오고 동일 여부를 결정하여 플레그에 반영한다.
//  * @return    리턴값 없음
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-03-16, 오전 11:43
//  * @warning
//  */
// // void CELEmitterMergeMngr::UpdateMissionInfo()
// // {
// // 	// 임무 ID 얻기
// // 	GP_MGR_MISSION->GetCurrentMission( & m_stMissionInfo[_LINK1-1], _LINK1 );
// // 	GP_MGR_MISSION->GetCurrentMission( & m_stMissionInfo[_LINK2-1], _LINK2 );
// //
// // 	//if( m_bSimulator == false || true ) {
// // 		if( false == GP_MGR_MISSION->GetCurrentMission( & m_stMissionInfo[_LINK1-1], _LINK1 ) )	// 임무 미생성
// // 		{
// // 			m_bIsNotSameMissionID = true;
// // 			strcpy_s( m_stMissionInfo[_LINK1-1].acMissionID, STR_TRAIN_MISSION );
// // 			strcpy_s( m_stMissionInfo[_LINK2-1].acMissionID, STR_TRAIN_MISSION );
// // 			GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_MSG, E_WARNING_CRITICAL, enumGMEI_DEVICE, enumGMEO_DEVICE, "임무가 생성되지 않았습니다. 임무 생성 후 다시 시도하세요.\n* 임무 ID가 없으면 비정상 위협 처리가 됩니다." );
// // 		}
// // 		else {
// // 			m_bIsNotSameMissionID = false;
// // 		}
// // 	//}
// // 	//else {
// // 		// 모의기일때는 임무 없는 것으로 강제 설정함.
// // 		//strcpy_s( m_stMissionInfo[_LINK1-1].acMissionID, STR_TRAIN_MISSION );
// // 		//strcpy_s( m_stMissionInfo[_LINK2-1].acMissionID, STR_TRAIN_MISSION );
// // 		//m_bIsNotSameMissionID = false;
// // 	//}
// //
// // 	return;
// // }
//
// /**
//  * @brief     IsNotSamePreviousMissionID
//  * @param     void
//  * @return    bool
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2017-06-28, 오후 8:12
//  * @warning
//  */
// bool CELEmitterMergeMngr::IsNotSamePreviousMissionID()
// {
// 	bool bRet=true;
// 	SGRDBMissionInfo stSGRDBMissionInfo;
//
// 	GP_MGR_MISSION->GetCurrentMission( & stSGRDBMissionInfo, _LINK1 );
//
// 	if( strcmp( m_stMissionInfo[_LINK1-1].acMissionID, stSGRDBMissionInfo.acMissionID ) == 0 ) {
// 		bRet = false;
// 	}
//
// 	return bRet;
//
// }
//
/**
 * @brief     위협 관리 클래스의 초기 값을 DB 테이블을 이용하여 초기화를 수행한다.
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-05, 오전 10:40
 * @warning
 */
void CELEmitterMergeMngr::InitDataFromDB()
{
    char buffer[400];

#ifdef _ELINT_
    sprintf_s( buffer, sizeof(buffer), "select max(OP_INIT_ID) from LOBDATA" );

    m_lOpInitID = GetLONGData( buffer ) + 1;

#endif

    //////////////////////////////////////////////////////////////////////////
    // 하나의 임무에서 Unique한 방사체 번호 얻기
#ifdef _MSC_VER
    sprintf_s( buffer, sizeof(buffer), "select max(AETID) from ABTDATA" );
#else
    sprintf( buffer, "select max(AETID) from ABTDATA" );
#endif
    m_uiAETID = (unsigned int) ( GetINTData( buffer ) + 1 );
    if( m_uiAETID == 0 ) {
        m_uiAETID = _spOne;
    }

    // LOB 테이블 조회
// #ifdef _DB_TUNNING_
// 	sprintf_s( buffer, sizeof(buffer), "SELECT AET_ID from (select * from E_AA_MSG_LOB order by AET_ID desc) where mission_id='%s' and rownum=1 ", pMissionID );
// #else
// 	sprintf_s( buffer, sizeof(buffer), "SELECT max(AET_ID) FROM E_AA_MSG_LOB where MISSION_ID='%s' ", GetMissionID( _LINK1 ) );
// #endif
#ifdef _MSC_VER
    //sprintf_s( buffer, sizeof(buffer), "select max(LOBID) from LOBDATA where OP_INIT_ID=%d" , m_uiOpInitID );
    sprintf_s( buffer, "select max(LOBID) from LOBDATA" );
#else
    sprintf( buffer, "select max(LOBID) from LOBDATA" );
#endif
    m_uiLOBID = (unsigned int) ( GetINTData( buffer ) + 1 );
    if( m_uiLOBID == 0 ) {
        m_uiLOBID = _spOne;
    }

// 	_CALL_DB( GetDataFromDB_LOB( & stLOBHeader, & stLOBData, buffer ) )
// 	m_uiAETID = _max( m_uiAETID, stLOBData.uiAETID );

//
// 	// ABT 테이블 조회
// #ifdef _DB_TUNNING_
// 	sprintf_s( buffer, sizeof(buffer), "SELECT /*+ INDEX_JOIN(V) */ AET_ID from (select * from E_AA_GMI_BEAM order by AET_ID desc) V where mission_id = '%s' || SUBSTR(UID, 1, 0) AND 1 = rownum AND mission_id = '%s' || SUBSTR(UID, rownum, 0) ", pMissionID, pMissionID );
// #else
// 	sprintf_s( buffer, sizeof(buffer), "SELECT MAX(AET_ID) FROM E_AA_GMI_BEAM where MISSION_ID='%s'", pMissionID );
// #endif
// 	_CALL_DB( GetDataFromDB_ABT( & stLOBHeader, & stLOBData, buffer ) )
// 	m_uiAETID = _max( m_uiAETID, stLOBData.uiAETID );
//
// 	// AET 테이블 조회
// #ifdef _DB_TUNNING_
// 	//sprintf_s( buffer, sizeof(buffer), "SELECT /*+ INDEX_JOIN(V) */ AET_ID from (select * from E_AA_GMI_EMITTER order by AET_ID desc) V where mission_id = '%s' || SUBSTR(UID, 1, 0) AND 1 = rownum AND mission_id = '%s' || SUBSTR(UID, rownum, 0) ", pMissionID, pMissionID );
// 	sprintf_s( buffer, sizeof(buffer), "SELECT MAX(AET_ID) FROM E_AA_GMI_EMITTER where MISSION_ID='%s' || SUBSTR(UID, 1, 0)", pMissionID );
// #else
// 	sprintf_s( buffer, sizeof(buffer), "SELECT MAX(AET_ID) FROM E_AA_GMI_EMITTER where MISSION_ID='%s' ", pMissionID );
// #endif
// 	_CALL_DB( GetDataFromDB_AET( & stLOBHeader, & stLOBData, buffer ) )
// 	m_uiAETID = _max( m_uiAETID, stLOBData.uiAETID );
//
// 	m_uiAETID = MakeUpperID( m_uiAETID );
//
    //////////////////////////////////////////////////////////////////////////
    // 빔 번호
    //stLOBData.uiAETID = 0;
// #ifdef _DB_TUNNING_
// 	//sprintf_s( buffer, sizeof(buffer), "SELECT /*+ INDEX_JOIN(V) */ ABT_ID from (select * from E_AA_GMI_BEAM order by ABT_ID desc) V where mission_id = '%s' || SUBSTR(UID, 1, 0) AND 1 = rownum AND mission_id = '%s' || SUBSTR(UID, rownum, 0) ", pMissionID, pMissionID );
// #else
// 	//sprintf_s( buffer, sizeof(buffer), "SELECT MAX(ABT_ID) FROM E_AA_GMI_BEAM where MISSION_ID='%s'", pMissionID );
// #endif
// 	//_CALL_DB( GetDataFromDB_ABT( & stLOBHeader, & stLOBData, buffer ) )
// 	//m_uiABTID = _max( m_uiABTID, stLOBData.uiAETID );
// 	//m_uiABTID = MakeUpperID( m_uiABTID );
// 	m_uiABTID = m_uiAETID;
#ifdef _MSC_VER
    //sprintf_s( buffer, sizeof(buffer), "select max(ABTID) from ABTDATA where OP_INIT_ID=%d" , m_uiOpInitID );
    sprintf_s( buffer, "select max(ABTID) from ABTDATA" );
#else
    sprintf( buffer, "select max(ABTID) from ABTDATA" );
#endif
    m_uiABTID = (unsigned int) ( GetINTData( buffer ) + 1 );
    if( m_uiABTID == 0 ) {
        m_uiABTID = _spOne;
    }


// 	GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_MSG, E_WARNING_NONE, enumGMEO_DEVICE, enumGMEI_DEVICE, "신규 생성한 위협은 방사체/빔 번호[%d /%d]로 시작합니다.", m_uiAETID, m_uiABTID );
//
// 	//////////////////////////////////////////////////////////////////////////
// 	// 2대 동시 운용하기 위해서 연동기1/2번의 데이터 공유를 위해서 일련 번호를 맞추게 함.
// 	/*! \todo   소프트웨어적으로 SEquence 번호를 할당하는데 DB에서 sequence 번호를 자동 할당하는 것으로 수정해야 함.
// 			\author 조철희 (churlhee.jo@lignex1.com)
// 			\date 	2016-05-22 15:26:42
// 	*/
    GetGlobalSequenceNum();

// 	//////////////////////////////////////////////////////////////////////////
// 	// 미식별 번호
// 	if( GP_MGR_PARAM->IsPOSN() == false || m_bSimulator == true ) {
// 		char ch='A';
//
// 		LogPrint("\n 미식별 번호를 찾고 있습니다. " );
// #ifdef _DB_TUNNING_
// 		sprintf_s( buffer, sizeof(buffer), "SELECT MAX(ELNOT_PRIM) from E_AA_MSG_LOB where MISSION_ID='%s' || SUBSTR(UID, 1, 0) AND ELNOT_PRIM like 'H999%%' ORDER BY ELNOT_PRIM DESC", GetMissionID( _LINK1 ) );
// #else
// 		sprintf_s( buffer, sizeof(buffer), "SELECT MAX(ELNOT_PRIM) from E_AA_MSG_LOB where MISSION_ID='%s' AND ELNOT_PRIM like 'H999%%' ORDER BY ELNOT_PRIM DESC", GetMissionID( _LINK1 ) );
// #endif
// 		_CALL_DB( GetDataFromDB_LOB( & m_iH000, & ch, buffer ) )
// 		if( m_iH000 == 0 ) {
// 			// 기본 값으로 설정
// 			ch = 'A';
//
// 			sprintf_s( buffer, sizeof(buffer), "SELECT MAX(ELNOT_PRIM) from E_AA_MSG_LOB where MISSION_ID='%s' AND ELNOT_PRIM like 'H%%%1c' ORDER BY ELNOT_PRIM DESC", GetMissionID( _LINK1 ), ch );
// 			_CALL_DB( GetDataFromDB_LOB( & m_iH000, & ch, buffer ) )
//
// 		}
// 		else {
// 			++ ch;
//
// 			if( ch > 'Z' ) {
// 				ch = 'A';
// 				m_iH000 = 0;
// 			}
// 			else {
// #ifdef _DB_TUNNING_
// 				sprintf_s( buffer, sizeof(buffer), "SELECT MAX(ELNOT_PRIM) from E_AA_MSG_LOB where MISSION_ID='%s' || SUBSTR(UID, 1, 0) AND ELNOT_PRIM like 'H%%%1c' ORDER BY ELNOT_PRIM DESC", GetMissionID( _LINK1 ), ch );
// #else
// 				sprintf_s( buffer, sizeof(buffer), "SELECT MAX(ELNOT_PRIM) from E_AA_MSG_LOB where MISSION_ID='%s' AND ELNOT_PRIM like 'H%%%1c' ORDER BY ELNOT_PRIM DESC", GetMissionID( _LINK1 ), ch );
// #endif
// 				_CALL_DB( GetDataFromDB_LOB( & m_iH000, & ch, buffer ) )
// 			}
// 		}
//
// 		if( ch >= 'A' && ch <= 'Z' ) {
// 			m_iH000 = m_iH000 + ( 1000 * ( ch - 'A' ) );
// 			/*! \bug		H999Z 가 있는 경우의 예외 처리
// 			    \author 조철희 (churlhee.jo@lignex1.com)
// 			    \date 	2018-01-10 11:09:48
// 			*/
// 			if( m_iH000 >= 25999 ) {
// 				m_iH000 = 0;
// 			}
// 		}
// 		else {
// 			ch = 'A';
// 			m_iH000 = 0;
// 		}
//
// 		++ m_iH000;
// 		MakeH000( NULL, 0 );
// 		LogPrint("미식별 번호[%d, %s]를 찾았습니다.", m_iH000, m_szH0000 );
// 		GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_MSG, E_WARNING_NONE, enumGMEO_DEVICE, enumGMEI_DEVICE, "미식별 번호[%s]를 설정합니다.", m_szH0000 );

    /*
    int nLOBData;

    SRxLOBData *pSRxLOBData;

    pSRxLOBData = (SRxLOBData *)malloc(sizeof(SRxLOBData) * 1000 );
    LoadLOBData( &nLOBData, pSRxLOBData, 1000 );

    free(pSRxLOBData);

        */

    Log( enNormal, "Starting the ID of LOB[%d], ABT[%d], AET[%d]" , m_uiLOBID, m_uiABTID, m_uiAETID );

}

// 	//////////////////////////////////////////////////////////////////////////
// 	// ABT 번호를 0 으로 만들기 위한 옵셋 값
// 	m_nABTOffset = m_uiABTID;
//
// 	return;
// }
//
// /**
//  * @brief     방사체, 빔, LOB 번호를 10 단위로 점프하게 설정함.
//  * @param     UINT nID
//  * @return    UINT
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-12-27, 오후 3:46
//  * @warning
//  */
// UINT CELEmitterMergeMngr::MakeUpperID( UINT nID )
// {
// 	UINT uRet;
//
// 	if( nID != 0 ) {
// 		uRet = ( ( (UINT) ( nID / 10 ) ) + 1 ) * 10;
// 	}
// 	else {
// 		uRet = 1;
// 	}
//
// 	return uRet;
//
// }
//
// /**
//  * @brief     입력한 링크 번호에 따라 임무 ID가 저장된 포인터를 리턴한다.
//  * @param     nLinkNum 링크 번호
//  * @return    임무ID의 데이터 포인터
//
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-03-05, 오전 10:43
//  * @warning
//  */
// char *CELEmitterMergeMngr::GetMissionID( int nLinkNum )
// {
// 	char *pChar;
//
// 	if( nLinkNum == _LINK2 ) {
// 		pChar = m_stMissionInfo[_LINK2-1].acMissionID;
// 	}
// 	else {
// 		pChar = m_stMissionInfo[_LINK1-1].acMissionID;
// 	}
//
// 	return pChar;
//
// }
//
// /**
//  * @brief     입력한 링크 번호에 따라 임무명이 저장된 포인터를 리턴한다.
//  * @param     nLinkNum 링크 번호
//  * @return    임무명의 데이터 포인터
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-03-05, 오전 10:47
//  * @warning
//  */
// char *CELEmitterMergeMngr::GetMissionName( int nLinkNum )
// {
// 	char *pRet;
// 	if( nLinkNum == _LINK2 ) {
// 		pRet = m_stMissionInfo[_LINK2-1].acMissionName;
// 	}
// 	else {
// 		pRet = m_stMissionInfo[_LINK1-1].acMissionName;
// 	}
//
// 	return pRet;
// }
//
#define THRESHOLD_OF_MAX_CALCMEAN				(50000)
/**
 * @brief     두 집단의 평균값들을 이용하여 전체 집단의 평균값(int)을 계산한다.
 * @param     iMean1 1번 집단의 평균값
 * @param     iCount1 1번 집단의 데이터 갯수
 * @param     iMean2 2번 집단의 평균값
 * @param     iCount2 2번 집단의 데이터 갯수
 * @return    평균값
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-11, 오전 10:20
 * @warning
 */
float CELEmitterMergeMngr::CalcMean( float fMean1, int iCount1, float fMean2, int iCount2 )
{
    int iCount;
    float fRet;
    float fDiv1, fDiv2;

    if( iCount1 == 0 || iCount2 == 0 ) { //DTEC_Else
        fRet = fMean1;
    }
    else if( iCount1 - iCount2 > THRESHOLD_OF_MAX_CALCMEAN ) { //DTEC_Else
        fRet = fMean1;
    }
    else {
        iCount = iCount1 + iCount2;
        fDiv1 = FDIV( iCount1, iCount );
        fDiv2 = FDIV( iCount2, iCount );
        fRet = FMUL( fMean1, fDiv1 );
        fRet += FMUL( fMean2, fDiv2 );

    }

    return fRet;

}

// int CELEmitterMergeMngr::CalcMean( int iMean, int iCount, int iElement )
// {
// 	int iRet;
// 	float fSum;
//
// 	if( iCount == 0 ) { //DTEC_Else
// 		iRet = iMean;
// 	}
// 	else if( iCount > THRESHOLD_OF_MAX_CALCMEAN ) { //DTEC_Else
// 		iRet = iMean;
// 	}
// 	else {
// 		fSum = ( iMean * iCount ) + iElement;
// 		fSum = FDIV( fSum, iCount+1 );
//
// 		iRet = (int) (fSum+0.5);
// 	}
//
// 	return iRet;
//
// }

//
// //
// void CELEmitterMergeMngr::CalcPositionMean( int *pPRISeq, int iCount1, int *pLOBSeq, int iCount2, int iPositionCount )
// {
// 	int i;
// 	int iMean;
//
// 	for( i=0 ; i < iPositionCount ; ++i ) {
// 		iMean = CalcMean( *pPRISeq, iCount1, *pLOBSeq, iCount2 );
// 		*pPRISeq = iMean;
//
// 		++ pPRISeq;
// 		++ pLOBSeq;
// 	}
// }
//
// /**
//  * @brief     두 집단의 평균값들을 이용하여 전체 집단의 평균값(float형)을 계산한다.
//  * @param     iMean1 1번 집단의 평균값
//  * @param     iCount1 1번 집단의 데이터 갯수
//  * @param     iMean2 2번 집단의 평균값
//  * @param     iCount2 2번 집단의 데이터 갯수
//  * @return    평균값
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-07-25, 오후 10:49
//  * @warning
//  */
// float CELEmitterMergeMngr::CalcMean( float iMean1, int iCount1, float iMean2, int iCount2 )
// {
// 	int iCount;
// 	float fVal;
// 	float fDiv1, fDiv2;
//
// 	if( iCount1 == 0 || iCount2 == 0 || ( iCount1 - iCount2 > THRESHOLD_OF_MAX_CALCMEAN ) ) {
// 		fVal = (float) iMean1;
// 	}
// 	else {
// 		iCount = iCount1 + iCount2;
// 		fDiv1 = FDIV( iCount1, iCount );
// 		fDiv2 = FDIV( iCount2, iCount );
// 		fVal = FMUL( iMean1, fDiv1 );
// 		fVal += FMUL( iMean2, fDiv2 );
// 	}
//
// 	return fVal;
//
// }
//
// #define THRESHOLD_OF_MAX_CALCDEVIATION			(50000)
// /**
//  * @brief     두 집단의 편차값들을 이용하여 전체 집단의 편차값을 계산한다.
//  * @param     iDev1 1번 집단의 평균값
//  * @param     iCount1 1번 집단의 데이터 갯수
//  * @param     iDev2 2번 집단의 평균값
//  * @param     iCount2 2번 집단의 데이터 갯수
//  * @return    편차값
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-03-11, 오전 10:20
//  * @warning
//  */
// int CELEmitterMergeMngr::CalcDeviation( int iDev1, int iCount1, int iDev2, int iCount2 )
// {
// 	int iVal;
//
// 	if( iCount1 - iCount2 > THRESHOLD_OF_MAX_CALCDEVIATION ) { //DTEC_Else
// 		iVal = iDev1;
// 	}
// 	else {
// 		/*! \todo   분산값은 일단 가중치로 계산한다.
// 				\author 조철희 (churlhee.jo@lignex1.com)
// 				\date 	2016-03-11 09:56:20
// 		*/
// 		iVal = ( iDev1 * iCount1 ) + ( iDev2 * iCount2 );
// 		iVal = (int) UDIV( iVal, ( iCount1 + iCount2 ) );
//
// 	}
//
// 	return iVal;
//
// }
//
// #define THRESHOLD_OF_MAX_CALCSDEVIATION			(50000)
// /**
//  * @brief     두 집단의 표준편차값들을 이용하여 전체 집단의 표준편차값을 계산한다.
//  * @param     iDev1 1번 집단의 평균값
//  * @param     iCount1 1번 집단의 데이터 갯수
//  * @param     iDev2 2번 집단의 평균값
//  * @param     iCount2 2번 집단의 데이터 갯수
//  * @return    표준편차
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-03-11, 오후 2:24
//  * @warning
//  */
// // int CELEmitterMergeMngr::CalcSDeviation( int iDev1, int iCount1, int iDev2, int iCount2 )
// // {
// // 	int iVal;
// //
// // 	if( iCount1 - iCount2 > THRESHOLD_OF_MAX_CALCSDEVIATION ) {
// // 		return iDev1;
// // 	}
// //
// // 	iVal = ( iDev1 * iCount1 ) + ( iDev2 * iCount2 );
// // 	iVal = UDIV( iVal, ( iCount1 + iCount2 ) );
// //
// // 	return iVal;
// //
// // }
//
// /**
//  * @brief     항공기 시간 정보로 시간을 얻는 함수
//  * @param     *pNow 항공기 시간 정보
//  * @param     nLink 링크 번호
//  * @return    리턴값 없음
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-05-13, 오전 12:08
//  * @warning
//  */
// void CELEmitterMergeMngr::GetAirGPSTime( time_t *pNow, int nLink )
// {
// 	struct tm tmTime;
// 	stringstream *psLink;
//
// 	if( nLink == _LINK1 ) {
// 		psLink = GP_MGR_AIRCRAFTDATAPROCESS->SSTimeInfo_LINK1();  // YY/MM/DD HH:MM:SS
// 	}
// 	else {
// 		psLink = GP_MGR_AIRCRAFTDATAPROCESS->SSTimeInfo_LINK2();  // YY/MM/DD HH:MM:SS
// 	}
//
// 	//TRACE( "\n 시간 : %s" , psLink1->str().c_str(), psLink2->str().c_str() );
// 	if( psLink->str().empty() != true ) { //DTEC_Else
// 		sscanf_s( psLink->str().c_str(), "%02d-%02d-%02d %02d:%02d:%02d", & tmTime.tm_year, & tmTime.tm_mon, & tmTime.tm_mday, & tmTime.tm_hour, & tmTime.tm_min, & tmTime.tm_sec );
//
// 		tmTime.tm_mon -= 1;
// 		tmTime.tm_year += 100;
// 		*pNow = mktime( & tmTime );
// 	}
// 	else {
// 		*pNow = time(NULL);
// 	}
//
// }
//
// /**
//  * @brief     방사체 정보를 업데이트한다.
//  * @param     *pvecThreatInfo 방사체에서 수동으로 편집한 데이터 포인터
//  * @param     *pSELEmitterEdited 방사체에서 수동으로 편집한 데이터 포인터
//  * @param     nLinkNum 링크 번호
//  * @return    리턴값 없음
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-06-07, 오후 2:06
//  * @warning
//  */
// void CELEmitterMergeMngr::UpdateEmitter( std::vector<SThreatFamilyInfo> *pvecThreatInfo, SELEmitterEdited *pSELEmitterEdited, int nLinkNum )
// {
// 	CELThreat *pTheAETThreat, *pTheABTThreat;
//
// 	m_pVecThreatInfo = pvecThreatInfo;
// 	m_pVecThreatInfo->clear();
//
// 	// AET를 찾아서 업데이트를 함.
// 	pTheAETThreat = m_pTheThreatRoot->Find( (UINT) pSELEmitterEdited->nAETId );
// 	if( pTheAETThreat != NULL ) {
// 		SELAETDATA *pAETData;
// 		SELAETDATA_EXT *pAETExtData;
//
// 		SRxABTData *pABTData;
//
// 		pAETData = GetAETData( pTheAETThreat->m_nIndex );
// 		pAETExtData = GetAETExtData( pTheAETThreat->m_nIndex );
//
// 		// 1. AET 업데이트 처리
// 		UpdateAET( pTheAETThreat, pSELEmitterEdited );
//
// 		// 2. AET 테이블에 추가
// 		InsertAET( pTheAETThreat, true );
//
// 		// 3. 빔 번호 추가
// 		pTheABTThreat = GetHeaderThreat( pTheAETThreat );
// 		while( pTheABTThreat != NULL ) { //#FA_C_PotentialUnboundedLoop_T1
// 			pABTData = GetABTData( pTheABTThreat->m_nIndex );
// 			UpdateABT( pTheABTThreat, pSELEmitterEdited, pAETData );
//
// 			InsertABT( pTheABTThreat, true );
//
// 			pTheABTThreat = GetNextThreat( pTheABTThreat );
//
// 			pSELEmitterEdited->nABTId = (int) pABTData->uiAETID;
// 			AddThreatInfo( pSELEmitterEdited, E_MR_UPDATE_INFO, pAETData->uiCoLOB, pAETExtData->bIsFISINTTask );
// 		}
//
// 		// 4. DB 인덱스 번호 증가 : 매우 중요
// 		NextSeqNum();
// 	}
// 	else { //DTEC_Else
// 		GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_MSG, E_WARNING_NONE, enumGMEO_DEVICE, enumGMEI_DEVICE, "방사체[%d], 빔[%d]가 존재하지 않습니다.", pSELEmitterEdited->nAETId, pSELEmitterEdited->nABTId );
// 	}
//
// }
//
// /**
//  * @brief     빔 정보를 수정한다.
//  * @param     std::vector<SThreatFamilyInfo>* pvecThreatInfo
//  * @param     SELEmitterEdited * pSELEmitterEdited
//  * @param     int nLinkNum
//  * @return    void
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-11-01, 오전 11:30
//  * @warning
//  */
// void CELEmitterMergeMngr::UpdateBeam( std::vector<SThreatFamilyInfo> *pvecThreatInfo, SELEmitterEdited *pSELEmitterEdited, int nLinkNum )
// {
// 	SELAETDATA *pAETData;
// 	SELAETDATA_EXT *pAETExtData;
// 	CELThreat *pTheABTThreat, *pTheAETThreat;
//
// 	m_pVecThreatInfo = pvecThreatInfo;
// 	m_pVecThreatInfo->clear();
//
// 	// AET를 찾아서 업데이트를 함.
// 	pTheABTThreat = m_pTheThreatRoot->Find( (UINT) pSELEmitterEdited->nAETId, (UINT) pSELEmitterEdited->nABTId );
// 	pTheAETThreat = m_pTheThreatRoot->Find( (UINT) pSELEmitterEdited->nAETId );
//
// 	if( pTheABTThreat != NULL || pTheAETThreat != NULL ) {
// 		// 1. ABT 업데이트 처리
// 		UpdateABT( pTheABTThreat, pSELEmitterEdited );
//
// 		// LOB 클러스터링을 위한 LOB 데이터 추가할 필요가 없음. 수동 위치 산출 값을 바꾸는 것이기 때문에
// 		// InsertLOBPool( pTheABTThreat->m_nIndex, pSELEmitterEdited );
//
// 		// 2. ABT 테이블에 업데이트
// 		InsertABT( pTheABTThreat, true );
//
// 		// 3. AET 테이블에 추가
// 		InsertAET( pTheAETThreat );
//
// 		// 4. 전시
// 		pAETData = GetAETData( pTheAETThreat->m_nIndex );
// 		pAETExtData = GetAETExtData( pTheAETThreat->m_nIndex );
// 		AddThreatInfo( pSELEmitterEdited, E_MR_UPDATE_INFO, pAETData->uiCoLOB, pAETExtData->bIsFISINTTask );
//
// 		// 5. DB 인덱스 번호 증가 : 매우 중요
// 		NextSeqNum();
// 	}
// 	else { //DTEC_Else
// 		GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_MSG, E_WARNING_NONE, enumGMEO_DEVICE, enumGMEI_DEVICE, "방사체[%d], 빔[%d]가 존재하지 않습니다.", pSELEmitterEdited->nAETId, pSELEmitterEdited->nABTId );
// 	}
//
// }
//
// /**
//  * @brief     LOB 방탐 유효성을 검사한다.
//  * @param     *pvecThreatInfo 위협 처리 결과의 데이터 포인터
//  * @param     *pSELLOiValidity LOB 유효성의 데이터 포인타
//  * @param     nLinkNum 링크 번호
//  * @return    리턴값 없음
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-06-16, 오후 8:16
//  * @warning
//  */
// void CELEmitterMergeMngr::UpdateLOiValidity( std::vector<SThreatFamilyInfo> *pvecThreatInfo, SELLOiValidity *pSELLOiValidity, int nLinkNum )
// {
// 	SELAETDATA *pAETData;
// 	SELAETDATA_EXT *pAETExtData;
// 	CELThreat *pTheAETThreat, *pTheABTThreat;
//
// 	m_pVecThreatInfo = pvecThreatInfo;
// 	m_pVecThreatInfo->clear();
//
// 	// 1. AET를 찾아서 업데이트를 함.
// 	pTheAETThreat = m_pTheThreatRoot->Find( (UINT) pSELLOiValidity->nAETId );
// 	pTheABTThreat = GetHeaderThreat( pTheAETThreat );
// 	while( pTheABTThreat != NULL ) { //#FA_C_PotentialUnboundedLoop_T1
// 		// ABT 업데이트 처리
// 		UpdateABT( pTheABTThreat, pSELLOiValidity );
//
// 		pTheABTThreat = GetNextThreat( pTheABTThreat );
// 	}
//
// 	// 2. AET 최종 업데이트
// 	UpdateAET( pTheAETThreat, pSELLOiValidity );
//
// 	// 3. AET 테이블에 추가
// 	InsertAET( pTheAETThreat );
//
// 	// 4. 전시할 에미터 번호를 기록한다.
// 	pAETData = GetAETData( pTheAETThreat->m_nIndex );
// 	pAETExtData = GetAETExtData( pTheAETThreat->m_nIndex );
// 	AddThreatInfo( pSELLOiValidity, E_MR_UPDATE_INFO, pAETExtData->bIsFISINTTask );
//
// 	// 4. DB 인덱스 번호 증가 : 매우 중요
// 	NextSeqNum();
//
// }
//
/**
 * @brief     미식별시에만 H000 코드를 증가하도록 함.
 * @param     coRadarModeIndex 레이더 모드 인덱스
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-06-03, 오후 5:17
 * @warning
 */
void CELEmitterMergeMngr::IncH0000( int coRadarModeIndex )
{
    char alphabet;

    // 미식별일때만 증가하도록 함.
    if( coRadarModeIndex == 0 ) {
        ++ m_iH000;

        alphabet = 'A' + ( m_iH000 / 1000 );
        if( alphabet > 'Z' ) { //DTEC_Else
            m_iH000 = 0;
        }

    }
}

// /**
//  * @brief     미식별 ELNOT 문자열 만드는 함수
//  * @param     *pszH000 미식별 ELNOT 정보 데이터
//  * @param     nABTID ABT 번호
//  * @return    리턴값 없음
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-06-03, 오후 3:31
//  * @warning
//  */
// void CELEmitterMergeMngr::MakeH000( char *pszH000, unsigned int nABTID )
// {
// 	char alphabet;
//
// 	if( nABTID == 0 ) { //DTEC_Else
// 		if( pszH000 != NULL || m_iH000 < 0 ) {
// 			if( pszH000 != NULL ) {
// 				*pszH000 = NULL;
// 			}
// 		}
// 		else {
// 			alphabet = 'A' + ( m_iH000 / 1000 );
// 			sprintf_s( m_szH0000, H0000_SIZE, "H%03d%1c", m_iH000 % 1000, alphabet );
// 		}
//
// 	}
// 	else {
// 		// 미식별 테이블에 번호 만들기
// 		int index = (int) nABTID - (int) m_nABTOffset;
//
// 		if( index < 0 ) {
// 			sprintf_s( m_szH0000, H0000_SIZE, "H%03dA", 0 );
// 		}
// 		else {
// 			int h0000;
//
// 			index = index % TOTAL_UNDEF_ID_NUMBER;
//
// 			h0000 = (int) m_pABTtoH000[(UINT)index];
// 			if( h0000 == (unsigned short) -1 ) {
// 				h0000 = m_iH000;
// 				m_pABTtoH000[index] = (USHORT) m_iH000;
// 			}
//
// 			if( h0000 < 0 ) {
// 				TRACE( "\n h0000[%d]", h0000 );
// 				sprintf_s( m_szH0000, H0000_SIZE, "H999Z" );
// 			}
// 			else {
// 				alphabet = 'A' + ( h0000 / 1000 );
// 				sprintf_s( m_szH0000, H0000_SIZE, "H%03d%1c", h0000 % 1000, alphabet );
// 			}
//
// 		}
//
// 		if( pszH000 != NULL ) {
// 			memcpy( pszH000, m_szH0000, sizeof(char) * H0000_SIZE );
// 		}
// 	}
//
// }
//
// /**
//  * @brief     미식별 ELNOT 문자열 만드는 함수
//  * @param     *pszH000 미식별 ELNOT 정보 데이터
//  * @return    리턴값 없음
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-06-03, 오후 3:31
//  * @warning
//  */
// void CELEmitterMergeMngr::UpdateReportTime( std::vector<SThreatFamilyInfo> *pvecThreatInfo, SELReportTime *pSELReportTime )
// {
// 	CELThreat *pTheAETThreat;
//
// 	// AET를 찾아서 업데이트를 함.
// 	pTheAETThreat = m_pTheThreatRoot->Find( (UINT) pSELReportTime->nAETId );
// 	if( pTheAETThreat != NULL ) {
// 		SELAETDATA *pAETData;
// 		SELAETDATA_EXT *pAETExtData;
//
// 		SELEmitterEdited stELEmitterEdited;
//
// 		m_pVecThreatInfo = pvecThreatInfo;
// 		m_pVecThreatInfo->clear();
//
// 		// 1. 방사체 정보 얻기
// 		if( pSELReportTime->nAETId > _spZero && pSELReportTime->nABTId <= _spZero && pSELReportTime->nLOBId <= _spZero ) {
// 			pAETData = GetAETData( pTheAETThreat->m_nIndex );
// 			pAETExtData = GetAETExtData( pTheAETThreat->m_nIndex );
//
// 			// 2. 방사체 시간 정보 업데이트
// 			if( pSELReportTime->tFirstReportTime != 0 ) {
// 				if( pAETData->firstReportedTime == 0 ) {
// 					pAETData->firstReportedTime = pSELReportTime->tFirstReportTime;
// 					pAETData->finalReportedTime = pSELReportTime->tFirstReportTime;
// 				}
// 				else {
// 					pAETData->finalReportedTime = pSELReportTime->tFirstReportTime;
// 				}
// 			}
//
// 			// 3. 방사체/빔 DB의 보고서 시간 정보 업데이트
// 			UpdateReportTimeToEmitterDB( pAETData, pAETExtData );
//
// 			stELEmitterEdited.nAETId = pSELReportTime->nAETId;
// 			stELEmitterEdited.nABTId = 0;
// 			stELEmitterEdited.nLOBId = 0;
// 			stELEmitterEdited.ti_FirstTime = pAETData->firstReportedTime;
// 			stELEmitterEdited.ti_FinalTime = pAETData->finalReportedTime;
// 			AddThreatInfo( & stELEmitterEdited, E_MR_REPORT_UPDATE, pAETData->uiCoLOB, pAETExtData->bIsFISINTTask, pAETExtData->uiSeqNum, false );
// 		}
//
// 		// 4. 빔 시간 정보 업데이트
// 		if( pSELReportTime->nAETId > _spZero && pSELReportTime->nABTId > _spZero && pSELReportTime->nLOBId <= _spZero ) {
// 			CELThreat *pTheABTThreat = GetHeaderThreat( pTheAETThreat );
// 			while( pTheABTThreat != NULL ) { //#FA_C_PotentialUnboundedLoop_T1
// 				SRxABTData *pABTData;
// 				SELABTDATA_EXT *pABTExtData;
//
// 				pABTData = GetABTData( pTheABTThreat->m_nIndex );
// 				pABTExtData = GetABTExtData( pTheABTThreat->m_nIndex );
//
// 				if( pABTData->uiABTID == pSELReportTime->nABTId ) {
// 					if( pSELReportTime->tFirstReportTime != 0 ) {
// 						if( pABTData->firstReportedTime == 0 ) {
// 							pABTData->firstReportedTime = pSELReportTime->tFirstReportTime;
// 						}
// 						else {
// 							pABTData->finalReportedTime = pSELReportTime->tFirstReportTime;
// 						}
// 					}
//
// 					UpdateReportTimeToEmitterDB( pABTData, pABTExtData );
//
// 					// 3. 전시 관련 정보 생성
// 					stELEmitterEdited.nAETId = pSELReportTime->nAETId;
// 					stELEmitterEdited.nABTId = (int) pABTData->uiABTID;
// 					stELEmitterEdited.nLOBId = 0;
// 					stELEmitterEdited.ti_FirstTime = pABTData->firstReportedTime;
// 					stELEmitterEdited.ti_FinalTime = pABTData->finalReportedTime;
// 					AddThreatInfo( & stELEmitterEdited, E_MR_REPORT_UPDATE, pABTData->uiCoLOB, pABTExtData->bIsFISINTTask, pABTExtData->uiSeqNum, false );
//
// 					break;
//
// 				}
//
// 				pTheABTThreat = GetNextThreat( pTheABTThreat );
//
// 			}
// 		}
//
// 		// 5. LOB 시간 정보 업데이트
// 		if( pSELReportTime->nAETId > _spZero && pSELReportTime->nABTId > _spZero && pSELReportTime->nLOBId > _spZero ) {
// 			CELThreat *pTheABTThreat = GetHeaderThreat( pTheAETThreat );
// 			while( pTheABTThreat != NULL ) { //#FA_C_PotentialUnboundedLoop_T1
// 				SRxABTData *pABTData;
// 				SELABTDATA_EXT *pABTExtData;
//
// 				pABTData = GetABTData( pTheABTThreat->m_nIndex );
// 				pABTExtData = GetABTExtData( pTheABTThreat->m_nIndex );
//
// 				if( pABTData->uiABTID == pSELReportTime->nABTId ) {
// 					if( pSELReportTime->tFirstReportTime != 0 ) {
// // 						if( pABTExtData->tiLOBfirstReportedTime == 0 ) {
// // 							pABTExtData->tiLOBfirstReportedTime = pSELReportTime->tFirstReportTime;
// // 						}
// // 						else {
// // 							pABTExtData->tiLOBfinalReportedTime = pSELReportTime->tFirstReportTime;
// // 						}
// 					}
//
// 					//UpdateReportTimeToEmitterDB( pABTData, pABTExtData );
//
// 					// 3. 전시 관련 정보 생성
// 					stELEmitterEdited.nAETId = pSELReportTime->nAETId;
// 					stELEmitterEdited.nABTId = pSELReportTime->nABTId;
// 					stELEmitterEdited.nLOBId = pSELReportTime->nLOBId;
// 					//stELEmitterEdited.ti_FirstTime = pABTExtData->tiLOBfirstReportedTime;
// 					//stELEmitterEdited.ti_FinalTime = pABTExtData->tiLOBfinalReportedTime;
// 					AddThreatInfo( & stELEmitterEdited, E_MR_REPORT_UPDATE, pABTData->uiCoLOB, pABTExtData->bIsFISINTTask, pABTExtData->uiSeqNum, false );
//
// 					break;
//
// 				}
//
// 				pTheABTThreat = GetNextThreat( pTheABTThreat );
//
// 			}
// 		}
//
// 	}
// 	else { //DTEC_Else
// 		// 1. 방사체 정보 업데이트
// 		if( pSELReportTime->nABTId <= _spZero ) {
// 			//UpdateReportTimeToEmitterDB( pSELReportTime->nAETId, & pSELReportTime->tFirstReportTime, & pSELReportTime->tFirstReportTime );
// 			//UpdateReportTimeToEmitterDB( pSELReportTime->nAETId, & pSELReportTime->tFirstReportTime, & pSELReportTime->finalReportedTime );
// 		}
//
// 		// 2. 빔 정보 업데이트
// 		if( pSELReportTime->nLOBId <= _spZero ) {
// 			//UpdateReportTimeToEmitterDB( pSELReportTime->nAETId, pSELReportTime->nABTId, & pSELReportTime->tFirstReportTime, & pSELReportTime->tFirstReportTime );
// 			//UpdateReportTimeToEmitterDB( pSELReportTime->nAETId, & pSELReportTime->tFirstReportTime, & pSELReportTime->finalReportedTime );
// 		}
//
// 		GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_MSG, E_WARNING_NONE, enumGMEO_DEVICE, enumGMEI_DEVICE, "보고서 생성 시간을 변경하려는데 해당 방사체[%d]가 존재하지 않습니다.", pSELReportTime->nAETId );
// 	}
//
// }
//
// /**
//  * @brief     방사체 정보에 보고서 시간 정보를 저장한다.
//  * @param     *pszH000 미식별 ELNOT 정보 데이터
//  * @return    리턴값 없음
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-06-03, 오후 3:31
//  * @warning
//  */
// // void CELEmitterMergeMngr::UpdateReportTimeToEmitterDB( SELAETDATA *pAETData, SELAETDATA_EXT *pAETExtData )
// // {
// // 	string strTableName="E_AA_GMI_EMITTER";
// // 	string strTemp;
// // 	CString strCondition = _T("");
// // 	list<_FIELD_INFO> listFieldInfo;
// //
// // 	_FIELD_INFO stField("","");
// //
// // 	stField.strFieldName = "FIRST_RPT_CRT_TIME";
// // 	strTemp = m_theELUtil.GetDBStyleTimeInfo( pAETData->firstReportedTime, 0 );
// // 	stField.strFieldValue = strTemp;
// // 	listFieldInfo.push_back( stField );
// //
// // 	stField.strFieldName = "FINAL_RPT_CRT_TIME";
// // 	strTemp = m_theELUtil.GetDBStyleTimeInfo( pAETData->finalReportedTime, 0 );
// // 	stField.strFieldValue = strTemp;
// // 	listFieldInfo.push_back( stField );
// //
// // 	strCondition.Format( "SEQ_NUM='%d' AND MISSION_ID='%s'", pAETExtData->uiSeqNum, GetMissionID() );
// // 	_CALL_DB( UpdateToDB( strTableName, & listFieldInfo, nullptr, strCondition.GetBuffer(), NULL, false, true ) )
// //
// // }
//
// // void CELEmitterMergeMngr::UpdateReportTimeToEmitterDB( UINT uiAETID, time_t *pFirstReportedTime, time_t *pFinalReportedTime )
// // {
// // 	string strTableName="E_AA_GMI_EMITTER";
// // 	string strTemp;
// // 	CString strCondition = _T("");
// // 	list<_FIELD_INFO> listFieldInfo;
// //
// // 	_FIELD_INFO stField("","");
// //
// // 	stField.strFieldName = "FIRST_RPT_CRT_TIME";
// // 	strTemp = m_theELUtil.GetDBStyleTimeInfo( *pFirstReportedTime, 0 );
// // 	stField.strFieldValue = strTemp;
// // 	listFieldInfo.push_back( stField );
// //
// // 	stField.strFieldName = "FINAL_RPT_CRT_TIME";
// // 	strTemp = m_theELUtil.GetDBStyleTimeInfo( *pFinalReportedTime, 0 );
// // 	stField.strFieldValue = strTemp;
// // 	listFieldInfo.push_back( stField );
// //
// // 	strCondition.Format( "AET_ID='%d' AND MISSION_ID='%s'", uiAETID, GetMissionID() );
// // 	_CALL_DB( UpdateToDB( strTableName, & listFieldInfo, nullptr, strCondition.GetBuffer(), NULL, false, true ) )
// //
// // }
//
// void CELEmitterMergeMngr::UpdateReportTimeToEmitterDB( UINT uiAETID, UINT uiABTID, time_t *pFirstReportedTime, time_t *pFinalReportedTime )
// {
// 	string strTableName="E_AA_GMI_BEAM";
// 	string strTemp;
// 	CString strCondition = _T("");
// 	list<_FIELD_INFO> listFieldInfo;
//
// 	_FIELD_INFO stField("","");
//
// 	stField.strFieldName = "FIRST_RPT_CRT_TIME";
// 	strTemp = m_theELUtil.GetDBStyleTimeInfo( *pFirstReportedTime, 0 );
// 	stField.strFieldValue = strTemp;
// 	listFieldInfo.push_back( stField );
//
// 	stField.strFieldName = "FINAL_RPT_CRT_TIME";
// 	strTemp = m_theELUtil.GetDBStyleTimeInfo( *pFinalReportedTime, 0 );
// 	stField.strFieldValue = strTemp;
// 	listFieldInfo.push_back( stField );
//
// 	strCondition.Format( "AET_ID='%d' AND ABT_ID='%d' AND MISSION_ID='%s'", uiAETID, uiABTID, GetMissionID() );
// 	_CALL_DB( UpdateToDB( strTableName, & listFieldInfo, nullptr, strCondition.GetBuffer(), NULL, false, true ) )
//
// }
//
// /**
//  * @brief     UpdateReportTimeToEmitterDB
//  * @param     SRxABTData * pABTData
//  * @param     SELABTDATA_EXT * pABTExtData
//  * @return    void
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2018-01-16, 오후 10:15
//  * @warning
//  */
// void CELEmitterMergeMngr::UpdateReportTimeToEmitterDB( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
// {
//
// 	string strTableName="E_AA_GMI_BEAM";
// 	string strTemp;
// 	CString strCondition = _T("");
// 	list<_FIELD_INFO> listFieldInfo;
//
// 	_FIELD_INFO stField("","");
//
// 	stField.strFieldName = "FIRST_RPT_CRT_TIME";
// 	strTemp = m_theELUtil.GetDBStyleTimeInfo( pABTData->firstReportedTime, 0 );
// 	stField.strFieldValue = strTemp;
// 	listFieldInfo.push_back( stField );
//
// 	stField.strFieldName = "FINAL_RPT_CRT_TIME";
// 	strTemp = m_theELUtil.GetDBStyleTimeInfo( pABTData->finalReportedTime, 0 );
// 	stField.strFieldValue = strTemp;
// 	listFieldInfo.push_back( stField );
//
// 	strCondition.Format( "SEQ_NUM='%d' AND MISSION_ID='%s'", pABTExtData->uiSeqNum, GetMissionID() );
// 	_CALL_DB( UpdateToDB( strTableName, & listFieldInfo, nullptr, strCondition.GetBuffer(), NULL, false, true ) )
//
// }
//
// /**
//  * @brief     미식별 ELNOT 문자열 만드는 함수
//  * @return    리턴값 없음
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-06-03, 오후 3:31
//  * @warning
//  */
// void CELEmitterMergeMngr::UpdateAlertTime( std::vector<SThreatFamilyInfo> *pvecThreatInfo, SELAlertTime *pSELAlertTime )
// {
// 	SELEmitterEdited stELEmitterEdited;
// 	CELThreat *pTheAETThreat;
//
// 	m_pVecThreatInfo = pvecThreatInfo;
// 	m_pVecThreatInfo->clear();
//
// 	// AET를 찾아서 업데이트를 함.
// 	pTheAETThreat = m_pTheThreatRoot->Find( (UINT) pSELAlertTime->nAETId );
// 	if( pTheAETThreat != NULL ) {
// 		SELAETDATA *pAETData;
// 		SELAETDATA_EXT *pAETExtData;
//
// 		pAETData = GetAETData( pTheAETThreat->m_nIndex );
// 		pAETExtData = GetAETExtData( pTheAETThreat->m_nIndex );
//
// 		/*! \todo   SeqNum 은 구조체에서 받아서 처리하는 것으로 함.
// 		    \author 조철희 (churlhee.jo@lignex1.com)
// 		    \date 	2017-12-30 21:36:14
// 		*/
// 		if( pSELAlertTime->tFinalAlarmTime != 0 && pAETData->finalAlarmTime == 0 ) {
// 			// 1. 방사체 경보 시간 정보 변경
// 			pAETData->finalAlarmTime = pSELAlertTime->tFinalAlarmTime;
//
// 			// 2. 방사체 DB의 경보 시간 정보 업데이트
// 			DWORD dwTime=GetTickCount();
// 			UpdateAlertTimeToEmitterDB( pAETData, pAETExtData );
// 			LogPrint("\n========================================== UpdateAlertTimeToEmitterDB[%d] 시간 : %d ms", pSELAlertTime->nAETId, (int)((GetTickCount() - dwTime) / 1));
//
// 			// 3. 경보 관련 정보 생성
// 			stELEmitterEdited.nAETId = pSELAlertTime->nAETId;
// 			stELEmitterEdited.nABTId = 0;
// 			stELEmitterEdited.nLOBId = 0;
// 			stELEmitterEdited.ti_FinalTime = pSELAlertTime->tFinalAlarmTime;
// 			//AddThreatInfo( & stELEmitterEdited, E_MR_ALERT_UPDATE, pAETData->uiCoLOB, pAETExtData->bIsFISINTTask, pAETExtData->uiSeqNum, false );
// 		}
//
// 		// ABT를 찾아서 업데이트를 함.
// 		CELThreat *pTheABTThreat = GetHeaderThreat( pTheAETThreat );
// 		while( pTheABTThreat != NULL ) { //#FA_C_PotentialUnboundedLoop_T1
// 			SRxABTData *pABTData;
// 			SELABTDATA_EXT *pABTExtData;
//
// 			pABTData = GetABTData( pTheABTThreat->m_nIndex );
// 			pABTExtData = GetABTExtData( pTheABTThreat->m_nIndex );
//
// 			// 1. 빔 경보 시간 정보 변경
// 			if( pSELAlertTime->tFinalAlarmTime != 0 && pABTData->finalAlarmTime == 0 ) {
// 				pABTData->finalAlarmTime = pSELAlertTime->tFinalAlarmTime;
//
// 				// 2. 빔 DB의 경보 시간 정보 업데이트
// 				DWORD dwTime=GetTickCount();
// 				UpdateAlertTimeToEmitterDB( pABTData, pABTExtData );
// 				LogPrint("\n========================================== UpdateAlertTimeToEmitterDB[%d/%d] 시간 : %d ms", pSELAlertTime->nAETId, pSELAlertTime->nABTId, (int)((GetTickCount() - dwTime) / 1));
//
// 				// 3. 경보 관련 정보 생성
// 				stELEmitterEdited.nAETId = pSELAlertTime->nAETId;
// 				stELEmitterEdited.nABTId = (int) pABTData->uiABTID;
// 				stELEmitterEdited.nLOBId = 0;
// 				stELEmitterEdited.ti_FinalTime = pSELAlertTime->tFinalAlarmTime;
// 				AddThreatInfo( & stELEmitterEdited, E_MR_ALERT_UPDATE, pABTData->uiCoLOB, pABTExtData->bIsFISINTTask, pABTExtData->uiSeqNum, false );
// 			}
//
// 			pTheABTThreat = GetNextThreat( pTheABTThreat );
// 		}
//
// 		GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_MSG, E_WARNING_NONE, enumGMEO_DEVICE, enumGMEI_DEVICE, "경보 생성[A%d/B%d]을 설정합니다.", pSELAlertTime->nAETId, pSELAlertTime->nABTId );
//
// 	}
// 	else { //DTEC_Else
// 		GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_MSG, E_WARNING_MINOR, enumGMEO_DEVICE, enumGMEI_DEVICE, "경보 생성을 변경하려는데 방사체 번호[%d]가 잘못 됐습니다. 이미 삭제 되었을수 있습니다.", pSELAlertTime->nAETId );
// 	}
//
// }
//
// /**
//  * @brief     방사체 정보에 보고서 시간 정보를 저장한다.
//  * @param     *pszH000 미식별 ELNOT 정보 데이터
//  * @return    리턴값 없음
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-06-03, 오후 3:31
//  * @warning
//  */
// void CELEmitterMergeMngr::UpdateAlertTimeToEmitterDB( SELAETDATA *pAETData, SELAETDATA_EXT *pAETExtData )
// {
// 	string strTableName="E_AA_GMI_EMITTER";
// 	string strTemp;
// 	CString strCondition = _T("");
// 	list<_FIELD_INFO> listFieldInfo;
//
// 	_FIELD_INFO stField("","");
//
// 	stField.strFieldName = "FINAL_ALARM_TIME";
// 	strTemp = m_theELUtil.GetDBStyleTimeInfo( pAETData->finalAlarmTime, 0 );
// 	stField.strFieldValue = strTemp;
// 	listFieldInfo.push_back( stField );
//
// 	strCondition.Format( "SEQ_NUM='%d' AND MISSION_ID='%s'", pAETExtData->uiSeqNum, GetMissionID() );
// 	_CALL_DB( UpdateToDB( strTableName, & listFieldInfo, nullptr, strCondition.GetBuffer(), NULL, false, true ) )
//
// }
//
// /**
//  * @brief     방사체 정보에 보고서 시간 정보를 저장한다.
//  * @param     *pszH000 미식별 ELNOT 정보 데이터
//  * @return    리턴값 없음
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2016-06-03, 오후 3:31
//  * @warning
//  */
// void CELEmitterMergeMngr::UpdateAlertTimeToEmitterDB( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
// {
// 	string strTableName="E_AA_GMI_BEAM";
// 	string strTemp;
// 	CString strCondition = _T("");
// 	list<_FIELD_INFO> listFieldInfo;
//
// 	_FIELD_INFO stField("","");
//
// 	stField.strFieldName = "FINAL_ALARM_TIME";
// 	strTemp = m_theELUtil.GetDBStyleTimeInfo( pABTData->finalAlarmTime, 0 );
// 	stField.strFieldValue = strTemp;
// 	listFieldInfo.push_back( stField );
//
// 	strCondition.Format( "SEQ_NUM='%d' AND MISSION_ID='%s'", pABTExtData->uiSeqNum, GetMissionID() );
// 	_CALL_DB( UpdateToDB( strTableName, & listFieldInfo, nullptr, strCondition.GetBuffer(), NULL, false, true ) )
//
// }
//
// /**
//  * @brief     CalDistanceNM
//  * @param     int iThreatIndex
//  * @param     int iLatitude
//  * @param     int iLongitude
//  * @return    float
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2017-04-11, 오후 11:30
//  * @warning
//  */
// // float CELEmitterMergeMngr::CalDistanceNM( SELDBGmiAbt *pAbt )
// // {
// // 	double dValue;
// // 	SThreat *pThreat;
// // 	float fDistance=-1.0;
// // 	int iThreatLat, iThreatLong;
// //
// // 	/*! \todo   추후에는 빔 필드에 거리 차를 두어서 하는 걸로 구현해야 한다.
// // 	    \author 조철희 (churlhee.jo@lignex1.com)
// // 	    \date 	2017-04-12 01:48:02
// // 	*/
// // 	pThreat = GP_MNGR_CED_LIB2->RTGetThreatData( pAbt->iThreatIndex, m_pSEnvironVariable->eCEDDefaultLibType );
// // 	if( pThreat != NULL ) {
// // 		iThreatLat = pThreat->GetILatitude();
// // 		dValue = iThreatLat / 10000.;
// // 		dValue = DegMinSec2Degree( dValue );
// // 		iThreatLat = (int) ( dValue * 1000000. + 0.5 );
// //
// // 		iThreatLong = pThreat->GetILongitude();
// // 		dValue = iThreatLong / 10000.;
// // 		dValue = DegMinSec2Degree( dValue );
// // 		iThreatLong = (int) ( dValue * 1000000. + 0.5 );
// //
// // 		fDistance = (float) m_theIdentifyAlg.CalDistanceNM( iThreatLat, iThreatLong, pAbt->iLatitude, pAbt->iLongitude );
// // 	}
// //
// // 	return fDistance;
// // }
//
// /**
//  * @brief     EOB 데이터로부터 PIN 번호 얻는다.
//  * @param     STR_CEDEOBID_INFO * pCEDEOBInfo EOB 정보 데이터
//  * @return    int 핀번호
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2017-07-03, 오후 6:20
//  * @warning
//  */
// int CELEmitterMergeMngr::GetEquipNumber( STR_CEDEOBID_INFO *pCEDEOBInfo )
// {
// 	int iEquipNumber;
//
// 	if( pCEDEOBInfo->eIdResult == E_EL_OLD_ID ) {
// 		iEquipNumber = pCEDEOBInfo->nDeviceIndex;
// 	}
// 	else {
// 		iEquipNumber = -1;
// 	}
//
// 	return iEquipNumber;
//
// }
//
/**
 * @brief     GetGlobalSequenceNum
 * @param     void
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-07-09, 오후 7:36
 * @warning
 */
void CELEmitterMergeMngr::GetGlobalSequenceNum()
{
    m_nSeqNum = 0;

#ifdef _SQLITE_
#elif _NO_SQLITE_
#elif _MSSQL_
    char buffer[100];

    sprintf_s( buffer, sizeof(buffer), "select max(SEQ_NUM) from LOBDATA" );    
    m_nSeqNum = _max( m_nSeqNum, GetINTData( buffer ) );

    sprintf_s( buffer, sizeof(buffer), "select max(SEQ_NUM) from ABTDATA" );
    m_nSeqNum = _max( m_nSeqNum, GetINTData( buffer ) );

    sprintf_s( buffer, sizeof(buffer), "select max(SEQ_NUM) from AETDATA" );
    m_nSeqNum = _max( m_nSeqNum, GetINTData( buffer ) );

    ++ m_nSeqNum;

#endif

    //LogPrint( "연동기1의 LOB_SEQ_NUM[%d]이고 연동기1/2(LINK2)의 LOB_SEQ_NUM[%d] 입니다.", m_nSeqNum, m_nGetSeqNum );

}

//
// /**
//  * @brief     방사체에서 내용 변경시 식별 상태를 업데이트해주는 루틴
//  * @param     char * pIDInfo
//  * @return    void
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2017-10-17, 오후 12:23
//  * @warning
//  */
// void CELEmitterMergeMngr::UpdateIDInfo( char *pIDInfo, SELAETDATA_EXT *pAETExtData, SELEXTDB *pExtDB )
// {
// 	int nRadarIndex;
//
// 	nRadarIndex = GP_MNGR_CED_LIB2->RTGetRadarIndexFromThreatMemory( pExtDB->szPrimaryELNOT, pAETExtData->iPinNumber );
//
// 	// 해당 PIN 번호로 레이더가 존재할 때
// 	if( nRadarIndex > 0 ) {
// 		// 기성 또는 신출로 결정
// 		strcpy_s( pIDInfo, MAX_SIZE_OF_IDINFO, & strIdResult[ E_EL_OLD_ID ][0] );
// 	}
// 	else {
// 		// 불명 또는 신출로 결정
// 		if( pExtDB->szPrimaryELNOT[0] == 'H' ) {
// 			strcpy_s( pIDInfo, MAX_SIZE_OF_IDINFO, & strIdResult[ E_EL_UNK_ID ][0] );
// 		}
// 		else {
// 			strcpy_s( pIDInfo, MAX_SIZE_OF_IDINFO, & strIdResult[ E_EL_NEW_ID ][0] );
// 		}
// 	}
//
// }
//
// /**
//  * @brief     SendInsertDBThread
//  * @param     SRxLOBData * pHeader
//  * @param     SRxABTData * pData
//  * @param     SELABTDATA_EXT * pExt
//  * @param     SELEXTDB * pExtDB
//  * @return    void
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2017-11-01, 오후 4:42
//  * @warning
//  */
// void CELEmitterMergeMngr::SendInsertDBThread( UCHAR opCode, SRxLOBData *pHeader, SRxABTData *pData, SELABTDATA_EXT *pExt, SELEXTDB *pExtDB )
// {
// 	int nSize=0;
//
// 	++ m_nInsertDB;
//
// 	m_sqMsg.uiOpcode = GP_CP->MakeOPCode( opCode, DEVICECODE_AEE, DEVICECODE_GMEO );
// 	m_sqMsg.usSize = sizeof(SRxLOBData) + sizeof(SRxABTData) + sizeof(SELABTDATA_EXT) + sizeof(SELEXTDB);
// 	m_sqMsg.usOperatorId = 0;
// 	m_sqMsg.nLinkNum = m_nLinkNum;
// 	m_sqMsg.bIsServer = false;
// 	m_sqMsg.bIsReplay = false;
// 	m_sqMsg.bIsFromPosition = false;
// 	m_sqMsg.bIsFromOtherSite = false;
// 	m_sqMsg.bIsFromDBOfPastMission = false;
//
// 	memcpy( & m_sqMsg.buf[nSize], pHeader, sizeof(SRxLOBData) );
// 	nSize += sizeof(SRxLOBData);
// 	memcpy( & m_sqMsg.buf[nSize], pData, sizeof(SRxABTData) );
// 	nSize += sizeof(SRxABTData);
// 	memcpy( & m_sqMsg.buf[nSize], pExt, sizeof(SELABTDATA_EXT) );
// 	nSize += sizeof(SELABTDATA_EXT);
// 	memcpy( & m_sqMsg.buf[nSize], pExtDB, sizeof(SELEXTDB) );
// 	GP_MGR_INSERTDB->UserReceive( & m_sqMsg );
//
// }
//
// /**
//  * @brief     SendInsertDBThread
//  * @param     UCHAR opCode
//  * @param     SRxLOBData * pHeader
//  * @param     SRxLOBDataGroup * pData
//  * @param     SELABTDATA_EXT * pExt
//  * @param     SELEXTDB * pExtDB
//  * @return    void
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2017-11-01, 오후 7:54
//  * @warning
//  */
// void CELEmitterMergeMngr::SendInsertDBThread( UCHAR opCode, SRxLOBData *pHeader, SRxLOBDataGroup *pData, SELLOBDATA_EXT *pExt, SELEXTDB *pExtDB, bool bLink2 )
// {
// 	int nSize=0;
//
// 	++ m_nInsertDB;
//
// 	m_sqMsg.uiOpcode = GP_CP->MakeOPCode( opCode, DEVICECODE_AEE, DEVICECODE_GMEO );
// 	m_sqMsg.usSize = sizeof(SRxLOBData) + sizeof(SRxLOBDataGroup) + sizeof(SELLOBDATA_EXT) + sizeof(SELEXTDB);
// 	m_sqMsg.usOperatorId = 0;
// 	m_sqMsg.nLinkNum = m_nLinkNum;
// 	m_sqMsg.bIsServer = false;
// 	m_sqMsg.bIsReplay = false;
// 	m_sqMsg.bIsFromPosition = false;
// 	m_sqMsg.bIsFromOtherSite = false;
// 	m_sqMsg.bIsFromDBOfPastMission = false;
//
// 	memcpy( & m_sqMsg.buf[nSize], pHeader, sizeof(SRxLOBData) );
// 	nSize += sizeof(SRxLOBData);
// 	memcpy( & m_sqMsg.buf[nSize], pData, sizeof(SRxLOBDataGroup) );
// 	nSize += sizeof(SRxLOBDataGroup);
// 	memcpy( & m_sqMsg.buf[nSize], pExt, sizeof(SELLOBDATA_EXT) );
// 	nSize += sizeof(SELLOBDATA_EXT);
// 	if( pExtDB != NULL ) {
// 		memcpy( & m_sqMsg.buf[nSize], pExtDB, sizeof(SELEXTDB) );
// 	}
// 	else {
// 		memset( & m_sqMsg.buf[nSize], 0, sizeof(SELEXTDB) );
// 	}
// 	nSize += sizeof(SELEXTDB);
// 	memcpy( & m_sqMsg.buf[nSize], & bLink2, sizeof(bool) );
// 	GP_MGR_INSERTDB->UserReceive( & m_sqMsg );
//
// }
//
// /**
//  * @brief     SendInsertDBThread
//  * @param     UCHAR opCode
//  * @param     SRxLOBData * pHeader
//  * @param     SELAETDATA * pData
//  * @param     SELAETDATA_EXT * pExt
//  * @param     SELEXTDB * pExtDB
//  * @return    void
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2017-11-01, 오후 9:31
//  * @warning
//  */
// void CELEmitterMergeMngr::SendInsertDBThread( UCHAR opCode, SRxLOBData *pHeader, SELAETDATA *pData, SELAETDATA_EXT *pExt, SELEXTDB *pExtDB )
// {
// 	int nSize=0;
//
// 	++ m_nInsertDB;
//
// 	m_sqMsg.uiOpcode = GP_CP->MakeOPCode( opCode, DEVICECODE_AEE, DEVICECODE_GMEO );
// 	m_sqMsg.usSize = sizeof(SRxLOBData) + sizeof(SELAETDATA) + sizeof(SELAETDATA_EXT) + sizeof(SELEXTDB);
// 	m_sqMsg.usOperatorId = 0;
// 	m_sqMsg.nLinkNum = m_nLinkNum;
// 	m_sqMsg.bIsServer = false;
// 	m_sqMsg.bIsReplay = false;
// 	m_sqMsg.bIsFromPosition = false;
// 	m_sqMsg.bIsFromOtherSite = false;
// 	m_sqMsg.bIsFromDBOfPastMission = false;
//
// 	memcpy( & m_sqMsg.buf[nSize], pHeader, sizeof(SRxLOBData) );
// 	nSize += sizeof(SRxLOBData);
// 	memcpy( & m_sqMsg.buf[nSize], pData, sizeof(SELAETDATA) );
// 	nSize += sizeof(SELAETDATA);
// 	memcpy( & m_sqMsg.buf[nSize], pExt, sizeof(SELAETDATA_EXT) );
// 	nSize += sizeof(SELAETDATA_EXT);
// 	memcpy( & m_sqMsg.buf[nSize], pExtDB, sizeof(SELEXTDB) );
// 	GP_MGR_INSERTDB->UserReceive( & m_sqMsg );
//
// }
//
// /**
//  * @brief     UserRemoveThreat
// * @param     int nAET
// * @return    bool
// * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2017-12-09, 오전 2:00
//  * @warning
//  */
// bool CELEmitterMergeMngr::UserRemoveThreat( int nAET )
// {
// 	bool bRet=false;
// 	SRxABTData *pABTData;
// 	SELAETDATA *pAETData;
// 	SELAETDATA_EXT *pAETExtData;
//
// 	SELEmitterEdited stELEmitterEdited;
//
// 	CELThreat *pTheAETThreat, *pTheThreat;
//
// 	pTheAETThreat = m_pTheThreatRoot->Find( (UINT) nAET );
// 	if( pTheAETThreat != NULL ) {
// 		pAETData = GetAETData( pTheAETThreat->m_nIndex );
// 		pAETExtData = GetAETExtData( pTheAETThreat->m_nIndex );
//
// 		pTheThreat = GetHeaderThreat( pTheAETThreat );
// 		while( pTheThreat != NULL ) { //#FA_C_PotentialUnboundedLoop_T1
// 			pABTData = GetABTData( pTheThreat->m_nIndex );
// 			if( pABTData == NULL ) {
// 				break;
// 			}
//
// 			ClearLOBs( pTheThreat->m_nIndex );
// 			InitOfLOBClustering( pTheThreat->m_nIndex );
//
// 			pTheThreat = GetNextThreat( pTheThreat );
// 		}
//
// 		// 위협 관리 삭제
// 		bRet = RemoveThreat( nAET );
// 		if( bRet == true ) {
// 			m_pVecThreatInfo->clear();
//
// 			// UpdateEmitterBeamStatus( pTheAETThreat, E_MR_DELETE, false );
//
// 			// 3. 전시 관련 정보 생성
// 			stELEmitterEdited.nAETId = nAET;
// 			stELEmitterEdited.nABTId = 0;
// 			stELEmitterEdited.nLOBId = 0;
// 			stELEmitterEdited.uiSeqNum = pAETExtData->uiSeqNum;
// 			//AddThreatInfo( & stELEmitterEdited, E_MR_REMOVE, pAETData->uiCoLOB, pAETExtData->bIsFISINTTask, pAETExtData->uiSeqNum, false );
// 		}
// 		else {
// 			GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_MSG, E_WARNING_NONE, enumGMEO_DEVICE, enumGMEI_DEVICE, "사용자 요구 방사체 삭제하려는데 해당 방사체[%d]가 존재하지 않습니다.", nAET );
// 		}
// 	}
//
// 	return bRet;
// }
//
// /**
//  * @brief     DeActiveThreat
//  * @param     int nAET
//  * @return    bool
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2017-12-08, 오후 5:16
//  * @warning
//  */
// bool CELEmitterMergeMngr::UserDeleteThreat( int nAET )
// {
// 	bool bRet=true;
//
// 	SELEmitterEdited stELEmitterEdited;
//
// 	CELThreat *pTheAETThreat; //, *pTheThreat;
//
//
// 	pTheAETThreat = m_pTheThreatRoot->Find( (UINT) nAET );
// 	if( pTheAETThreat != NULL ) {
// 		m_pVecThreatInfo->clear();
//
// 		UpdateEmitterBeamStatus( pTheAETThreat, E_ES_DELETE, true );
//
// // 		SELAETDATA_EXT *pAETExtData = GetAETExtData( pTheAETThreat->m_nIndex );
// // 		stELEmitterEdited.nAETId = nAET;
// // 		stELEmitterEdited.nABTId = 0;
// // 		stELEmitterEdited.nLOBId = 0;
// // 		stELEmitterEdited.enEmitterStat = E_MR_DELETE;
// // 		AddThreatInfo( & stELEmitterEdited, E_MR_UPDATE_STAT, pAETData->uiCoLOB, pAETExtData->bIsFISINTTask, pAETExtData->uiSeqNum, false );
//
// 	}
// 	else {
// 		//GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_MSG, E_WARNING_NONE, enumGMEO_DEVICE, enumGMEI_DEVICE, "보고서 생성 시간을 변경하려는데 해당 방사체[%d]가 존재하지 않습니다." , pSELReportTime->nAETId );
// 	}
//
// 	return bRet;
// }

/**
 * @brief     UpdateEmitterStatusToEmitterDB
 * @param     SELAETDATA * pAETData
 * @param     SELAETDATA_EXT * pAETExtData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-12-08, 오후 5:31
 * @warning
 */
void CELEmitterMergeMngr::UpdateEmitterStatusToEmitterDB( SRxAETData *pAETData, SELAETDATA_EXT *pAETExtData )
{
// // 	string strTableName="E_AA_GMI_EMITTER";
// // 	CString strTemp;
// // 	CString strCondition = _T("");
// // 	list<_FIELD_INFO> listFieldInfo;
// //
// // 	_FIELD_INFO stField("","");
// //
// // 	stField.strFieldName = "STAT";
// // 	strTemp.Format( "%d", pAETExtData->enBeamEmitterStat );
// // 	stField.strFieldValue = strTemp;
// // 	listFieldInfo.push_back( stField );
// //
// // 	strCondition.Format( "SEQ_NUM='%d' AND MISSION_ID='%s' AND AET_ID='%d'", pAETExtData->uiSeqNum, GetMissionID(), pAETData->uiAETID );
// // 	_CALL_DB( UpdateToDB( strTableName, & listFieldInfo, nullptr, strCondition.GetBuffer(), NULL, false, true ) )
//
}

//////////////////////////////////////////////////////////////////////
/*!
 * @brief
 * @return    void
 * @param     SRxABTData * pABTData
 * @param     SELABTDATA_EXT * pABTExtData
 * @version   0.0.1
 * @author    조철희(churlhee.jo@lignex1.com)
 * @date      2017-12-12 오후 11:11
 * @warning
 */
void CELEmitterMergeMngr::UpdateBeamStatusToEmitterDB( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData )
{
// // 	string strTableName="E_AA_GMI_BEAM";
// // 	CString strTemp;
// // 	CString strCondition = _T("");
// // 	list<_FIELD_INFO> listFieldInfo;
// //
// // 	_FIELD_INFO stField("","");
// //
// // 	stField.strFieldName = "STAT";
// // 	strTemp.Format( "%d", pABTExtData->enBeamEmitterStat );
// // 	stField.strFieldValue = strTemp;
// // 	listFieldInfo.push_back( stField );
// //
// // 	strCondition.Format( "SEQ_NUM='%d' AND MISSION_ID='%s' AND ABT_ID='%d'", pABTExtData->uiSeqNum, GetMissionID(), pABTData->uiABTID );
// // 	_CALL_DB( UpdateToDB( strTableName, & listFieldInfo, nullptr, strCondition.GetBuffer(), NULL, false, true ) )

}
//
// /**
//  * @brief     SetMissionIdAndMissionNameForDataRetransmitMode
//  * @param     char * i_szMissionId
//  * @param     char * i_szMissionName
//  * @return    void
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2017-12-30, 오후 9:49
//  * @warning
//  */
// void CELEmitterMergeMngr::SetMissionIdAndMissionNameForDataRetransmitMode(char* i_szMissionId, char* i_szMissionName)
// {
// 	// 임무 ID 재설정. (자료재전송 일괄처리 모드)
//
// 	strcpy_s(m_stMissionInfo[_LINK2-1].acMissionID, i_szMissionId );
// 	strcpy_s(m_stMissionInfo[_LINK1-1].acMissionID, i_szMissionId );
//
// 	strcpy_s(m_stMissionInfo[_LINK2-1].acMissionName, i_szMissionName );
// 	strcpy_s(m_stMissionInfo[_LINK1-1].acMissionName, i_szMissionName );
// }
//


/**
 * @brief     PrintAllValidityByAllLOB
 * @param     std::vector<STR_LOBS> * pVecLOBs
 * @param     SRxABTData * pABTData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-09-17, 11:52
 * @warning
 */
void CELEmitterMergeMngr::PrintAllValidityByAllLOB( std::vector<STR_LOBS> *pVecLOBs, SRxABTData *pABTData )
{
    UINT i;

    //bool bRet=false;
    //int iCoCheckIn1=0, iCoCheckIn2=0;

    float /* fSumTheta=0.0, */ fDiff;

    float fTheta;
    // std::vector<STR_LOBS>::pointer pLOBs;
    std::vector<STR_LOBS>::iterator iter;

    PrintFunction;

    Log( enNormal, "PE[%.5f/%.5f]", pABTData->fLatitude, (double) pABTData->fLongitude  );
    for( i=1, iter=pVecLOBs->begin() ; iter != pVecLOBs->end() ; ++ iter, ++i ) {
        fTheta = (float) m_theInverseMethod.GCAzimuth( (*iter).fLatitude, (*iter).fLongitude, (double) pABTData->fLatitude, (double) pABTData->fLongitude, true );

        fDiff = _abs( (float) fTheta - (*iter).fDoa );
        if( fDiff >= 180.0 ) {
            fDiff = (float) ( 360. - fDiff );
        }
        Log( enNormal, "%d : [레이더 방탐 #%d, %.5f/%.5f/%.2f(%.2f)]", i, (*iter).iCollectorID, (*iter).fLatitude, (*iter).fLongitude, (*iter).fDoa, fDiff );

    }

}

/**
 * @brief     빔 유효성을 체크한다.
 * @param     std::vector<STR_LOBS>* pVecLOBs LOB 벡터 데이터
 * @param     STR_POSITION_ESTIMATION * pPEInfo 위치 산출 정보
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-12-30, 오후 9:49
 * @warning
 */
bool CELEmitterMergeMngr::CheckValidityByAllLOB( std::vector<STR_LOBS> *pVecLOBs, SRxABTData *pABTData )
{
    UINT iSize;

    bool bRet=false;
    int iCoCheckIn1=0, iCoCheckIn2=0;

    float fDiff;

    float fTheta;
    std::vector<STR_LOBS>::iterator iter;

    iSize = pVecLOBs->size();
    for( iter=pVecLOBs->begin() ; iter != pVecLOBs->end() ; ++iter ) { //#FA_C_PotentialUnboundedLoop_T2
        fTheta = (float) m_theInverseMethod.GCAzimuth( (*iter).fLatitude, (*iter).fLongitude, (double) pABTData->fLatitude, (double) pABTData->fLongitude );

        fDiff = _abs( (float) fTheta - (*iter).fDoa );
        if( fDiff >= 180.0 ) {
            fDiff = (float) ( 360. - fDiff );
        }

        if( fDiff <= 100 /* GP_MGR_PARAM->GetEffectiveDOADiff1() */ ) {
            ++ iCoCheckIn1;
        }

        if( fDiff <= 100 /* GP_MGR_PARAM->GetEffectiveDOADiff2() */ ) {
            ++ iCoCheckIn2;
        }
    }


    if( UDIV( iCoCheckIn1 * 100, iSize ) >= DOADIFF_RATIO1 &&
        UDIV( iCoCheckIn2 * 100, iSize ) >= DOADIFF_RATIO2 ) {
        bRet = true;

    }
    //LogPrint( "\n 60퍼센트 조건: %d/%d, 90퍼센트 조건: %d/%d", iCoCheckIn1, iSize, iCoCheckIn2, iSize );
    Log( enNormal, "60퍼센트 조건: %d/%d, 90퍼센트 조건: %d/%d", iCoCheckIn1, iSize, iCoCheckIn2, iSize );

    return bRet;
}

/**
 * @brief     lob 유효 여부를 리턴준다.
 * @param     void
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2018-01-09, 오후 6:01
 * @warning
 */
bool CELEmitterMergeMngr::IsValidLOB()
{
    bool bRet=true;

    if( /* GP_MGR_PARAM->IsValidLOB() == */ true ) {
        // 드웰, 스태거, 지터 신호 중에서 평균 PRI가 100ms 인 것은 버림.
        if( m_pLOBData->iPRIType == E_AET_PRI_DWELL_SWITCH || m_pLOBData->iPRIType == E_AET_PRI_STAGGER || m_pLOBData->iPRIType == E_AET_PRI_JITTER ) {
            if( m_pLOBData->fPRIMean > VALID_MEANPRI ) {
                bRet = false;
            }
        }

        // 지터 신호 중에서 지터율이 큰 값은 버림.
        if( m_pLOBData->iPRIType == E_AET_PRI_JITTER || m_pLOBData->iPRIType == E_AET_PRI_PATTERN ) {
            if( m_pLOBData->fPRIJitterRatio > VALID_JITTERRATION ) {
                bRet = false;
            }
        }

    }

    return bRet;
}

// /**
//  * @brief     항공기 자세 유효를 체크한다.
//  * @param     void
//  * @return    bool
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2018-04-09, 오후 4:02
//  * @warning
//  */
// // bool CELEmitterMergeMngr::IsValidRollAndPitch()
// // {
// // 	bool bRet=true;
// // 	BOOL bRet1, bRet2;
// //
// // 	// 항공기 자세가 이상한 것은 버림.
// // 	bRet1 = CompMarginDiffFF( ELDecoder::DecodeAOA(m_pLOBData->iRollAngle), LOW_ROLLANGLE, HIGH_ROLLANGLE, 0 );
// // 	bRet2 = CompMarginDiffFF( ELDecoder::DecodeAOA(m_pLOBData->iPitchAngle), LOW_PITCHANGLE, HIGH_PITCHANGLE, 0 );
// // 	if( bRet1 == FALSE || bRet2 == FALSE ) {
// // 		bRet = false;
// // 	}
// //
// // 	return bRet;
// // }

/**
 * @brief     NeedToRunPositionEstimation
 * @param     SRxABTData * pABTData
 * @param     SELABTDATA_EXT * pABTExtData
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2018-01-09, 오후 6:01
 * @warning
 */
bool CELEmitterMergeMngr::NeedToRunPositionEstimation( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData, std::vector<STR_LOBS> *pVecLOBs )
{
    bool bRet=true;

    // 동일 방위, 위/경도 가 동일한 값이면 false 로 리턴한다.
// 	if( pVecLOBs->size() >= 50 ) {
// 		UINT i;
// 		std::vector<STR_LOBS>::pointer pLOBs;
//
// 		int iBeforeDoa;
// 		int iBeforeLatitude, iBeforeLongitude;
//
// 		STR_LOBS refLOBs;
//
// 		bRet = false;
// 		refLOBs = pVecLOBs->front();
// 		pLOBs = pVecLOBs->data();
// 		iBeforeDoa = pLOBs->iDoa;
// 		iBeforeLongitude = pLOBs->iLongitude;
// 		iBeforeLatitude = pLOBs->iLatitude;
//
// 		++ pLOBs;
// 		for( i=1 ; i < pVecLOBs->size() ; ++i ) {
// 			if( refLOBs.iLatitude != pLOBs->iLatitude || refLOBs.iLongitude != pLOBs->iLongitude ) {
// 				bRet = true;
// 				break;
// 			}
// 			else {
// 				if( CompMeanDiff( iBeforeDoa, pLOBs->iDoa, 20 ) != TRUE ) {
// 					bRet = true;
// 					break;
// 				}
// 			}
//
// 			iBeforeDoa = pLOBs->iDoa;
// 			++ pLOBs;
// 		}
// 	}
//
// 	if( bRet == false ) {
// 		LogPrint( "\n 방위, 위/경도 값이 동일하여 위치 산출을 하지 않도록 합니다." );
// 	}

    //////////////////////////////////////////////////////////////////////////
// 	if( pABTData->peInfo.enValid == E_EL_PESTAT_SUCCESS ) {
// 		if( pABTData->idInfo.nCoRadarModeIndex == _spZero ) {
// 			if( pABTData->peInfo.iCEP < 1000 ) {
// 				bRet = false;
// 			}
// 		}
// 		else {
// 			if( pABTData->idInfo.nThreatIndex != _spZero && pABTData->peInfo.iCEP < 1000 ) {
// 				bRet = true;
// 			}
// 		}
// 	}

    //////////////////////////////////////////////////////////////////////////
    // LOB가 특정 개수 이상이고 특정 CEP 이내이면 위치 산출 수행을 안한다.
    if( pABTData->uiCoLOB >= MAX_LOB_FOR_INHIBIT_PE ) {
        bRet = false;
    }

    //////////////////////////////////////////////////////////////////////////
    // 미식별이고 위치 산출이 실패한 30개 이상인 빔에 대해서는 위치 산출을 수행하지 않는다.
    if( pABTData->uiCoLOB >= MAX_LOB_FOR_CLUSTERING && pABTExtData->enValid != E_EL_PESTAT_SUCCESS && pABTExtData->idInfo.nCoRadarModeIndex == _spZero ) {
        bRet = false;
    }

    return bRet;
}

// /**
//  * @brief     DB 테이블러부터 과제명을 얻는다.
//  * @param     char * acTaskName
//  * @param     char * aucTaskID
//  * @return    bool
//  * @exception
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  * @version   0.0.1
//  * @date      2018-02-01, 오후 12:25
//  * @warning
//  */
// void CELEmitterMergeMngr::GetTaskNameFromTable( char *pacTaskName, char *paucTaskID )
// {
// 	bool bRet=false;
// 	UINT i, nSize;
// 	std::vector<SEL_STaskID2Name>::pointer pVecTaskID2NameTable;
//
// 	SEL_STaskID2Name stSTaskID2Name;
//
// 	char szTaskID[LENGTH_OF_TASK_ID];
//
// 	memcpy( szTaskID, paucTaskID, LENGTH_OF_TASK_ID );
// 	szTaskID[LENGTH_OF_TASK_ID] = NULL;
//
// 	nSize = m_VecTaskID2NameTable.size();
// 	pVecTaskID2NameTable = m_VecTaskID2NameTable.data();
// 	for( i=0 ; i < nSize ; ++i ) {
// 		if( strcmp( (*pVecTaskID2NameTable).szTaskID, szTaskID ) == 0 ) {
// 			//strcpy_s( acTaskName, (*pVecTaskID2NameTable).szTaskName );
// 			strcpy_s( pacTaskName, SIZE_OF_TASK_NAME, (*pVecTaskID2NameTable).szTaskName );
// 			bRet = true;			// 잘못된 CodeSonar 경보 (Unreachable Data Flow help)
// 			break;
// 		}
// 		++ pVecTaskID2NameTable;
// 	}
//
// 	if( bRet == false ) {		// 잘못된 CodeSonar 경보 (Redundant Condition help)
// 		_CALL_DB( GetTaskNameFromDB( pacTaskName, paucTaskID ) )
//
// 		strcpy_s( stSTaskID2Name.szTaskID, szTaskID );
// 		strcpy_s( stSTaskID2Name.szTaskName, pacTaskName );
//
// 		m_VecTaskID2NameTable.push_back( stSTaskID2Name );
// 	}
//
// }
//
/**
 * @brief     무효한 빔은 삭제 처리하여 재 클러스터링 하도록 한다.
 * @param     void
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2018-04-09, 오후 3:29
 * @warning
 */
void CELEmitterMergeMngr::ResetABT()
{
    //bool bIsFISINTTask;

    SELAETDATA_EXT *pAETExtData;

    SRxABTData *pABTData;
    SELABTDATA_EXT *pABTExtData;

    //SELEmitterEdited stELEmitterEdited;

    if( m_pAETThreat != NULL && m_pABTThreat != NULL ) {
        UINT iDeleteThreatWheuiCoLOB=20;//GP_MGR_PARAM->GetDeleteThreatWhenCoLOB();

        pAETExtData = GetAETExtData( m_pAETThreat->m_nIndex );

        pABTData = GetABTData( m_pABTThreat->m_nIndex );
        pABTExtData = GetABTExtData( m_pABTThreat->m_nIndex );
        
        //bIsFISINTTask = pAETExtData->bIsFISINTTask;

        // 식별된 중에서 탐지 과제이고, 유효성이 무효이고, LOB 개수(30개; 기본값) 이상일 때, 강제 삭제 처리 한다.
        if( iDeleteThreatWheuiCoLOB > 0 && pABTData->iValidity == _spZero && pABTData->uiCoLOB >= iDeleteThreatWheuiCoLOB && pABTExtData->idInfo.nCoRadarModeIndex != 0 ) {
            if( true == DeleteThreat( m_pAETThreat, m_pABTThreat ) ) {
                LogPrint( "무효한 빔으로 위협 관리에서 빔[%dB]을 삭제 성공합니다 !!", pABTData->uiABTID );
            }
            else {
                LogPrint( "무효한 빔으로 위협 관리에서 빔[%dB]을 삭제 실패합니다 !!", pABTData->uiABTID );
            }

            //stELEmitterEdited.nAETId = pABTData->uiAETID;
            //stELEmitterEdited.nABTId = pABTData->uiABTID;
            //stELEmitterEdited.nLOBId = 0;
            //stELEmitterEdited.uiSeqNum = pAETExtData->uiSeqNum;
            //stELEmitterEdited.enEmitterStat = E_ES_NOT_AVAILABLE;
            // AddThreatInfo( & stELEmitterEdited, E_MR_REMOVE, pABTData->uiCoLOB, bIsFISINTTask, uiSeqNum, false );
        }
    }

}

/**
 * @brief CELEmitterMergeMngr::UpdateCEDEOBLibrary
 */
void CELEmitterMergeMngr::UpdateCEDEOBLibrary()
{
    ++ m_nLoadCEDEOBLibrary;

}

/**
 * @brief CELEmitterMergeMngr::GetINTData
 * @param pSQLString
 * @return
 */
int CELEmitterMergeMngr::GetINTData( char *pSQLString )
{
#ifdef _SQLITE_
    int iValue=-1;

    try {
        Kompex::SQLiteStatement stmt( m_pDatabase );
        stmt.Sql( pSQLString );

        if( stmt.FetchRow() ) {
            // i = 0;
            iValue = stmt.GetColumnInt(0);
        }

        // do not forget to clean-up
        stmt.FreeQuery();
    }
    catch( Kompex::SQLiteException &exception ) {
        std::cerr << "\nException Occured" << std::endl;
        exception.Show();
        std::cerr << "SQLite result code: " << exception.GetSqliteResultCode() << std::endl;
    }

    return iValue;

#elif _NO_SQLITE_
    return 0;
#elif _MSSQL_
    int iValue=-1;

    DECLARE_BEGIN_CHECKODBC

    CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );

    theRS.Open( pSQLString );
    if( ! theRS.IsEof() ) {
        theRS.GetFieldValue( 0, & iValue );
    }

    theRS.Close();

    DECLARE_END_CHECKODBC

    return iValue;
#endif

}

/**
 * @brief     GetLONGData
 * @param     char * pSQLString
 * @return    LONG
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-22, 16:45
 * @warning
 */
LONG CELEmitterMergeMngr::GetLONGData( char *pSQLString )
{
#ifdef _SQLITE_
    return 0;
#elif _NO_SQLITE_
    return 0;

#elif _MSSQL_
    LONG lValue=0;

    DECLARE_BEGIN_CHECKODBC

    CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );

    theRS.Open( pSQLString );
    if( ! theRS.IsEof() ) {
        theRS.GetFieldValue( 0, & lValue );
    }

    theRS.Close();

    DECLARE_END_CHECKODBC

    return lValue;
#endif

}

/**
 * @brief CELEmitterMergeMngr::InsertToDB_Position
 * @param pLOBData
 * @param pExt
 */
bool CELEmitterMergeMngr::InsertToDB_Position( SRxLOBData *pLOBData, SELLOBDATA_EXT *pLOBExtData, bool bFreqSeq )
{

#ifdef _SQLITE_
    int iIndex, i;
    bool bRet=true;

    strcpy( m_pszSQLString, "INSERT INTO LOB_POSITION (SEQ_NUM, SEQ_TYPE, LOBID, ABTID, AETID, TASK_ID, POSITION_COUNT, " );
    iIndex = strlen( m_pszSQLString );
    for( i=1 ; i < pLOBData->iFreqPositionCount || i < pLOBData->iPRIPositionCount ; ++i ) {
        iIndex += sprintf( & m_pszSQLString[iIndex], "SEQ_%02d, " , i );
    }
    iIndex += sprintf( & m_pszSQLString[iIndex], "SEQ_%02d ) values ( ", i );
    
    if( bFreqSeq == true ) {
        iIndex += sprintf( & m_pszSQLString[iIndex], "'%d', '%d', '%d', '%d', '%d', '%s', '%d', " , m_nSeqNum, bFreqSeq, pLOBData->uiLOBID, pLOBData->uiABTID, pLOBData->uiAETID, pLOBData->aucTaskID, pLOBData->iFreqPositionCount );
        for( i=0 ; i < pLOBData->iFreqPositionCount-1 ; ++i ) {
            iIndex += sprintf( & m_pszSQLString[iIndex], "%f, " , pLOBData->fFreqSeq[i] );
        }        
        sprintf( & m_pszSQLString[iIndex], "%f )" , pLOBData->fFreqSeq[i] );
        
    }
    else {
        iIndex += sprintf( & m_pszSQLString[iIndex], "'%d', '%d', '%d', '%d', '%d', '%s', '%d', " , m_nSeqNum, bFreqSeq, pLOBData->uiLOBID, pLOBData->uiABTID, pLOBData->uiAETID, pLOBData->aucTaskID, pLOBData->iPRIPositionCount );
        for( i=0 ; i < pLOBData->iPRIPositionCount-1 ; ++i ) {
            iIndex += sprintf( & m_pszSQLString[iIndex], "%f, " , pLOBData->fPRISeq[i] );
        }        
        sprintf( & m_pszSQLString[iIndex], "%f )" , pLOBData->fPRISeq[i] );
    }

    try {
        Kompex::SQLiteStatement stmt( m_pDatabase );
        stmt.Sql( m_pszSQLString );

        // do not forget to clean-up
        stmt.FreeQuery();  
    }
    catch( Kompex::SQLiteException &exception ) {
        bRet = false;
        std::cerr << "\nException Occured" << std::endl;
        exception.Show();
        std::cerr << "SQLite result code: " << exception.GetSqliteResultCode() << std::endl;
    }

    return bRet;

#elif _NO_SQLITE_
    return true;

#elif _MSSQL_
    int i, iIndex;
    DECLARE_BEGIN_CHECKODBC

    CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );

    strcpy( m_pszSQLString, "INSERT INTO LOB_POSITION (SEQ_NUM, SEQ_TYPE, OP_INIT_ID, LOBID, ABTID, AETID, TASK_ID, POSITION_COUNT, " );
    iIndex = strlen( m_pszSQLString );
    for( i=1 ; i < pLOBData->iFreqPositionCount || i < pLOBData->iPRIPositionCount ; ++i ) {
        iIndex += sprintf_s( & m_pszSQLString[iIndex], MAX_SQL_SIZE-iIndex, "SEQ_%02d, " , i );
    }
    iIndex += sprintf_s( & m_pszSQLString[iIndex], MAX_SQL_SIZE-iIndex, "SEQ_%02d ) values ( ", i );

    if( bFreqSeq == true ) {
        iIndex += sprintf_s( & m_pszSQLString[iIndex], MAX_SQL_SIZE-iIndex, "'%d', '%d', '%ld', '%d', '%d', '%d', '%s', '%d', " , m_nSeqNum, bFreqSeq, m_lOpInitID, pLOBData->uiLOBID, pLOBData->uiABTID, pLOBData->uiAETID, pLOBExtData->aetData.aucTaskID, pLOBData->iFreqPositionCount );
        for( i=0 ; i < pLOBData->iFreqPositionCount-1 ; ++i ) {
            iIndex += sprintf_s( & m_pszSQLString[iIndex], MAX_SQL_SIZE-iIndex, "'%f', " , pLOBData->fFreqSeq[i] );
        }
        iIndex += sprintf_s( & m_pszSQLString[iIndex], MAX_SQL_SIZE-iIndex, "'%f' )", pLOBData->fFreqSeq[i] );    
    }
    else {
        iIndex += sprintf_s( & m_pszSQLString[iIndex], MAX_SQL_SIZE-iIndex, "'%d', '%d', '%ld', '%d', '%d', '%d', '%s', '%d', " , m_nSeqNum, bFreqSeq, m_lOpInitID, pLOBData->uiLOBID, pLOBData->uiABTID, pLOBData->uiAETID, pLOBExtData->aetData.aucTaskID, pLOBData->iPRIPositionCount );
        for( i=0 ; i < pLOBData->iPRIPositionCount-1 ; ++i ) {
            iIndex += sprintf_s( & m_pszSQLString[iIndex], MAX_SQL_SIZE-iIndex, "'%f', " , pLOBData->fPRISeq[i] );
        }
        iIndex += sprintf_s( & m_pszSQLString[iIndex], MAX_SQL_SIZE-iIndex, "'%f' )", pLOBData->fPRISeq[i] );

    }

    theRS.Open( m_pszSQLString );
    theRS.Close();

    DECLARE_END_CHECKODBC
    DECLARE_RETURN
#endif

}

/**
 * @brief CELEmitterMergeMngr::InsertToDB_LOB
 * @param pLOBData
 * @param pExt
 * @param bUpdateRadarMode
 */
bool CELEmitterMergeMngr::InsertToDB_LOB( SRxLOBData *pLOBData, SELLOBDATA_EXT *pExt, bool bUpdateRadarMode )
{

#ifdef _SQLITE_
    struct tm *pstTime;
    char buffer[100];

    bool bRet=true;
    pstTime = localtime( & pLOBData->tiContactTime );
    if( pstTime != NULL ) {
        printf( "\n %d, %d, %d, %d" , m_nSeqNum, pLOBData->uiLOBID, pLOBData->uiABTID, pLOBData->uiAETID );
        strftime( buffer, 100, "%Y-%m-%d %H:%M:%S", pstTime);
        sprintf( m_pszSQLString, "INSERT INTO LOBDATA ( \
                    SEQ_NUM, LOBID, ABTID, AETID, CONTACT_TIME, CONTACT_TIME_MS, PRIMARY_ELNOT, PRIMARY_MODECODE, SECONDARY_ELNOT, SECONDARY_MODECODE, TERTIARY_ELNOT, TERTIARY_MODECODE, MODULATION_CODE, RADARMODE_NAME, NICK_NAME, FUNC_CODE, RADARMODE_INDEX, POLIZATION, RATIOOFPOL, \
                    SIGNAL_TYPE, DOA_MEAN, DOA_MIN, DOA_MAX, DOA_DEV, DOA_STD, DI_RATIO, \
                    FREQ_TYPE, FREQ_PATTERN_TYPE, FREQ_PATTERN_PERIOD, FREQ_MEAN, FREQ_MIN, FREQ_MAX, FREQ_DEV, FREQ_POSITION_COUNT, FREQ_ELEMENT_COUNT, \
                    PRI_TYPE, PRI_PATTERN_TYPE, PRI_PATTERN_PERIOD, PRI_MEAN, PRI_MIN, PRI_MAX, PRI_DEV, PRI_JITTER_RATIO, PRI_POSITION_COUNT, PRI_ELEMENT_COUNT, \
                    PW_MEAN, PW_MIN, PW_MAX, PW_DEV, \
                    PA_MEAN, PA_MIN, PA_MAX, PA_DEV, \
                    SCAN_TYPE, SCAN_PRD, \
                    INTRA_TYPE, INTRA_TYPE_DETAIL, INTRA_FRQ_MEAN, INTRA_FRQ_MIN, INTRA_FRQ_MAX, INTRA_FRQ_DEVIATION, \
                    SHIP_LAT, SHIP_LONG, SHIP_PITCH, SHIP_ROLL, SHIP_HEADING, SHIP_ALT, IS_VALIDITY, \
                    IS_DATA_STORE, IS_FILTERED, NUM_PDW, NUM_IQ ) VALUES \
                    ( %d, %d, %d, %d, \"%s\", %d, \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", %d, %d, %d, \
                    %d, %f, %f, %f, %f, %f, %d, \
                    %d, %d, %f, %f, %f, %f, %f, %d, %d, \
                    %d, %d, %f, %f, %f, %f, %f, %f, %d, %d, \
                    %f, %f, %f, %f, \
                    %f, %f, %f, %f, \
                    %d, %f, \
                    %d, %d, %f, %f, %f, %f, \
                    %f, %f, %f, %f, %f, %f, %d, \
                    %d, %d, %d, %d )" , \
             m_nSeqNum, pLOBData->uiLOBID, pLOBData->uiABTID, pLOBData->uiAETID, buffer, pLOBData->tiContactTimems, pLOBData->szPrimaryELNOT, pLOBData->szPrimaryModeCode, pLOBData->szSecondaryELNOT, pLOBData->szSecondaryModeCode, pLOBData->szTertiaryELNOT, pLOBData->szTertiaryModeCode, pLOBData->szModulationCode, pLOBData->szRadarModeName, pLOBData->szNickName, pLOBData->szFuncCode, pLOBData->iRadarModeIndex, pLOBData->iPolarization, pLOBData->iRatioOfPOL, \
             pLOBData->iSignalType, pLOBData->fDOAMean, pLOBData->fDOAMin, pLOBData->fDOAMax, pLOBData->fDOADeviation, pLOBData->fDOASDeviation, pLOBData->iDIRatio, \
             pLOBData->iFreqType, pLOBData->iFreqPatternType, pLOBData->fFreqPatternPeriod, pLOBData->fFreqMean, pLOBData->fFreqMin, pLOBData->fFreqMax, pLOBData->fFreqDeviation, pLOBData->iFreqPositionCount, pLOBData->iFreqElementCount, \
             pLOBData->iPRIType, pLOBData->iPRIPatternType, pLOBData->fPRIPatternPeriod, pLOBData->fPRIMean, pLOBData->fPRIMin, pLOBData->fPRIMax, pLOBData->fPRIDeviation, pLOBData->fPRIJitterRatio, pLOBData->iPRIPositionCount, pLOBData->iPRIElementCount, \
             pLOBData->fPWMean, pLOBData->fPWMin, pLOBData->fPWMax, pLOBData->fPWDeviation, \
             pLOBData->fPAMean, pLOBData->fPAMin, pLOBData->fPAMax, pLOBData->fPWDeviation, \
             pLOBData->iScanType, pLOBData->fScanPeriod, \
             pLOBData->iMOPType, pLOBData->iDetailMOPType, pLOBData->fMOPMaxFreq, pLOBData->fMOPMinFreq, pLOBData->fMOPMeanFreq, pLOBData->fMOPFreqDeviation, \
             pLOBData->fShipLatitude, pLOBData->fShipLongitude, pLOBData->fPitchAngle, pLOBData->fRollAngle, pLOBData->fHeadingAngle, pLOBData->fAltitude, pLOBData->iValidity, \
             pLOBData->iIsStoreData, pExt->aetAnal.isFiltered, pLOBData->iNumOfPDW, pLOBData->iNumOfIQ );

        try {
            //LOGMSG1( enNormal, " m_pszSQLString[%s]" , m_pszSQLString );

            Kompex::SQLiteStatement stmt( m_pDatabase );
            stmt.SqlStatement( m_pszSQLString );

            // do not forget to clean-up
            stmt.FreeQuery();  

            if( bUpdateRadarMode == true && pLOBData->iRadarModeIndex > 0 ) {
                m_pIdentifyAlg->UpdateRadarMode( pLOBData );
            }

        }
        catch( Kompex::SQLiteException &exception ) {
            LOGMSG1( enNormal, " m_pszSQLString[%s]" , m_pszSQLString );
            bRet = false;
            std::cerr << "\nException Occured" << std::endl;
            exception.Show();
            std::cerr << "SQLite result code: " << exception.GetSqliteResultCode() << std::endl;
        }
    }

    return bRet;

#elif _NO_SQLITE_
    return true;

#else
    DECLARE_BEGIN_CHECKODBC

    struct tm stTime;
    char buffer[100];

    CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );

    _localtime32_s( &stTime, & pLOBData->tiContactTime );
    strftime( buffer, 100, "%Y-%m-%d %H:%M:%S", & stTime);
    sprintf_s( m_pszSQLString, MAX_SQL_SIZE, "INSERT INTO LOBDATA ( SEQ_NUM, OP_INIT_ID, LOBID, ABTID, AETID, TASK_ID, CONTACT_TIME, CONTACT_TIME_MS, SIGNAL_TYPE, DOA_MEAN, DOA_MIN, DOA_MAX, DI_RATIO, FREQ_TYPE, FREQ_PATTERN_TYPE, FREQ_PATTERN_PERIOD, FREQ_MEAN, FREQ_MIN, FREQ_MAX, FREQ_POSITION_COUNT, PRI_TYPE, PRI_PATTERN_TYPE, PRI_PATTERN_PERIOD, PRI_MEAN, PRI_MIN, PRI_MAX, PRI_JITTER_RATIO, PRI_POSITION_COUNT, PW_MEAN, PW_MIN, PW_MAX, PA_MEAN, PA_MIN, PA_MAX, IS_STORED_PDW, NUM_PDW, COLLECTOR_ID, RADAR_LATITUDE, RADAR_LONGGITUDE, RADAR_NAME, RADARMODE_INDEX ) values( '%d', '%ld', '%d', '%d', '%d', '%s', '%s', '%d', '%d', '%f', '%f', '%f', '%d', '%d', '%d', '%f', '%f', '%f', '%f', '%d', '%d', '%d', '%f', '%f', '%f', '%f', '%f', '%d', '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%d', '%d', '%f', '%f', '%s', '%d' )", \
        m_nSeqNum, m_lOpInitID, pLOBData->uiLOBID, pLOBData->uiABTID, pLOBData->uiAETID, pExt->aetData.aucTaskID, buffer, pLOBData->tiContactTimems, pLOBData->iSignalType, \
        pLOBData->fDOAMean, pLOBData->fDOAMin, pLOBData->fDOAMax, pLOBData->iDIRatio, \
        pLOBData->iFreqType, pLOBData->iFreqPatternType, pLOBData->fFreqPatternPeriod, pLOBData->fFreqMean, pLOBData->fFreqMin, pLOBData->fFreqMax, pLOBData->iFreqPositionCount, \
        pLOBData->iPRIType, pLOBData->iPRIPatternType, pLOBData->fPRIPatternPeriod, pLOBData->fPRIMean, pLOBData->fPRIMin, pLOBData->fPRIMax, pLOBData->fPRIJitterRatio, pLOBData->iPRIPositionCount, \
        pLOBData->fPWMean, pLOBData->fPWMin, pLOBData->fPWMax, pLOBData->fPAMean, pLOBData->fPAMin, pLOBData->fPAMax, \
        pLOBData->iIsStoreData, pLOBData->iNumOfPDW, pLOBData->iCollectorID, \
        pLOBData->fRadarLatitude, pLOBData->fRadarLongitude, \
        pLOBData->aucRadarName, pLOBData->iRadarModeIndex );

    theRS.Open( m_pszSQLString );

    if( bUpdateRadarMode == true && pLOBData->iRadarModeIndex > 0 ) {
        __time32_t nowTime=_time32(NULL);

        _localtime32_s( & stTime, & nowTime );
        strftime( buffer, 100, "%Y-%m-%d %H:%M:%S", & stTime);

        // RADARMODE 테이블에 DATE_LAST_SEEN에 현재 날짜 및 시간을 업데이트 함.
        sprintf_s( m_pszSQLString, MAX_SQL_SIZE, "UPDATE RADARMODE SET DATE_LAST_SEEN='%s' where RADAR_MODE_INDEX=%d", buffer, pLOBData->iRadarModeIndex );
        theRS.Open( m_pszSQLString );

        // RADARMODE 테이블에 DATE_FIRST_SEEN에 현재 날짜 및 시간을 업데이트 함.
        sprintf_s( m_pszSQLString, MAX_SQL_SIZE, "UPDATE RADARMODE SET DATE_FIRST_SEEN='%s' where ( RADAR_MODE_INDEX=%d and ISNULL( DATE_FIRST_SEEN, '')='' )", buffer, pLOBData->iRadarModeIndex );
        //theRS.Open( m_pszSQLString );

    }

    theRS.Close();

    DECLARE_END_CHECKODBC
    DECLARE_RETURN

#endif

}

/**
 * @brief CELEmitterMergeMngr::InsertToDB_Position
 * @param pLOBData
 * @param pABTData
 * @param pABTExtData
 */
bool CELEmitterMergeMngr::InsertToDB_Position( SRxLOBData *pLOBData, SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData, bool bFreqSeq )
{
#ifdef _SQLITE_
    int iIndex, i;
    bool bRet=true;

    strcpy( m_pszSQLString, "INSERT INTO ABT_POSITION (SEQ_NUM, SEQ_TYPE, ABTID, AETID, TASK_ID, POSITION_COUNT, " );

    iIndex = strlen( m_pszSQLString );
    for( i=1 ; i < pABTData->iFreqPositionCount || i < pABTData->iPRIPositionCount ; ++i ) {
        iIndex += sprintf( & m_pszSQLString[iIndex], "SEQ_%02d, " , i );
    }
    iIndex += sprintf( & m_pszSQLString[iIndex], "SEQ_%02d ) values ( ", i );

    if( bFreqSeq == true ) {
        iIndex += sprintf( & m_pszSQLString[iIndex], "'%d', '%d', '%d', '%d', '%s', '%d', " , m_nSeqNum, bFreqSeq, pABTData->uiABTID, pABTData->uiAETID, pLOBData->aucTaskID, pABTData->iFreqPositionCount );
        for( i=0 ; i < pLOBData->iFreqPositionCount-1 ; ++i ) {
            iIndex += sprintf( & m_pszSQLString[iIndex], "'%f', " , pABTData->fFreqSeq[i] );
        }
        iIndex += sprintf( & m_pszSQLString[iIndex], "'%f' )", pABTData->fFreqSeq[i] );    
    }
    else {
        iIndex += sprintf( & m_pszSQLString[iIndex], "'%d', '%d', '%d', '%d', '%s', '%d', " , m_nSeqNum, bFreqSeq, pABTData->uiABTID, pABTData->uiAETID, pLOBData->aucTaskID, pABTData->iPRIPositionCount );
        for( i=0 ; i < pLOBData->iPRIPositionCount-1 ; ++i ) {
            iIndex += sprintf( & m_pszSQLString[iIndex], "'%f', " , pABTData->fPRISeq[i] );
        }
        iIndex += sprintf( & m_pszSQLString[iIndex], "'%f' )", pABTData->fPRISeq[i] );

    }

    try {
        Kompex::SQLiteStatement stmt( m_pDatabase );
        stmt.SqlStatement( m_pszSQLString );

        // do not forget to clean-up
        stmt.FreeQuery();  
    }
    catch( Kompex::SQLiteException &exception ) {
        bRet = false;
        std::cerr << "\nException Occured" << std::endl;
        exception.Show();
        std::cerr << "SQLite result code: " << exception.GetSqliteResultCode() << std::endl;
    }

    return bRet;

#elif _NO_SQLITE_
    return true;

#elif _MSSQL_
    int i, iIndex;
    DECLARE_BEGIN_CHECKODBC

    CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );

    strcpy( m_pszSQLString, "INSERT INTO ABT_POSITION (SEQ_NUM, SEQ_TYPE, OP_INIT_ID, ABTID, AETID, TASK_ID, POSITION_COUNT, " );

    iIndex = strlen( m_pszSQLString );
    for( i=1 ; i < pABTData->iFreqPositionCount || i < pABTData->iPRIPositionCount ; ++i ) {
        iIndex += sprintf_s( & m_pszSQLString[iIndex], MAX_SQL_SIZE-iIndex, "SEQ_%02d, " , i );
    }
    iIndex += sprintf_s( & m_pszSQLString[iIndex], MAX_SQL_SIZE-iIndex, "SEQ_%02d ) values ( ", i );

    if( bFreqSeq == true ) {
        iIndex += sprintf_s( & m_pszSQLString[iIndex], MAX_SQL_SIZE-iIndex, "'%d', '%d', '%ld', '%d', '%d', '%s', '%d', " , m_nSeqNum, bFreqSeq, m_lOpInitID, pABTData->uiABTID, pABTData->uiAETID, pLOBData->aucTaskID, pABTData->iFreqPositionCount );
        for( i=0 ; i < pLOBData->iFreqPositionCount-1 ; ++i ) {
            iIndex += sprintf_s( & m_pszSQLString[iIndex], MAX_SQL_SIZE-iIndex, "'%f', " , pABTData->fFreqSeq[i] );
        }
        iIndex += sprintf_s( & m_pszSQLString[iIndex], MAX_SQL_SIZE-iIndex, "'%f' )", pABTData->fFreqSeq[i] );    
    }
    else {
        iIndex += sprintf_s( & m_pszSQLString[iIndex], MAX_SQL_SIZE-iIndex, "'%d', '%d', '%ld', '%d', '%d', '%s', '%d', " , m_nSeqNum, bFreqSeq, m_lOpInitID, pABTData->uiABTID, pABTData->uiAETID, pLOBData->aucTaskID, pABTData->iPRIPositionCount );
        for( i=0 ; i < pLOBData->iPRIPositionCount-1 ; ++i ) {
            iIndex += sprintf_s( & m_pszSQLString[iIndex], MAX_SQL_SIZE-iIndex, "'%f', " , pABTData->fPRISeq[i] );
        }
        iIndex += sprintf_s( & m_pszSQLString[iIndex], MAX_SQL_SIZE-iIndex, "'%f' )", pABTData->fPRISeq[i] );

    }

    theRS.Open( m_pszSQLString );
    theRS.Close();

    DECLARE_END_CHECKODBC
    DECLARE_RETURN
#endif


}

/**
 * @brief 빔 레코드 추가
 * @param pABTData
 * @param pABTExtData
 * @param bUpdateThreat
 */
bool CELEmitterMergeMngr::InsertToDB_ABT( SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData, bool bUpdateThreat )
{
#ifdef _SQLITE_
    bool bRet=true;
    struct tm *pstTime;
    char buffer1[100], buffer2[100], buffer3[100];

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

    sprintf( m_pszSQLString, \
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

    try {
        Kompex::SQLiteStatement stmt( m_pDatabase );
        stmt.SqlStatement( m_pszSQLString );

        // do not forget to clean-up
        stmt.FreeQuery();  

        if( bUpdateThreat == true && pABTData->iThreatIndex > 0 ) {
            time_t nowTime=time(NULL);

            pstTime = localtime( & nowTime );

            if( pstTime != NULL ) {
                strftime( buffer1, 100, "%Y-%m-%d %H:%M:%S", pstTime );

                // RADARMODE 테이블에 DATE_LAST_SEEN에 현재 날짜 및 시간을 업데이트 함.
                sprintf_s( m_pszSQLString, sizeof(m_pszSQLString), "UPDATE THREAT SET DATE_LAST_SEEN='%s' where THREAT_INDEX=%d", buffer1, pABTData->iThreatIndex );
                //Kompex::SQLiteStatement stmt( m_pDatabase );
                //stmt.SqlStatement( m_pszSQLString );
            }

            // do not forget to clean-up
            //stmt.FreeQuery();  
        }
    }
    catch( Kompex::SQLiteException &exception ) {
        // LOGMSG1( enNormal, " m_pszSQLString[%s]" , m_pszSQLString );
        bRet = false;
        std::cerr << "\nException Occured" << std::endl;
        exception.Show();
        std::cerr << "SQLite result code: " << exception.GetSqliteResultCode() << std::endl;
    }

    return bRet;

#elif _NO_SQLITE_
    return true;

#else
    DECLARE_BEGIN_CHECKODBC

    struct tm stTime;
    char buffer1[100], buffer2[100], buffer3[100];

    CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );

    _localtime32_s(& stTime, & pABTData->tiFirstSeenTime );
    strftime( buffer1, 100, "%Y-%m-%d %H:%M:%S", &stTime);
    _localtime32_s(&stTime, & pABTData->tiLastSeenTime );
    strftime( buffer2, 100, "%Y-%m-%d %H:%M:%S", &stTime);
    _localtime32_s(&stTime, & pABTData->tiFinalAlarmTime );
    strftime( buffer3, 100, "%Y-%m-%d %H:%M:%S", &stTime);
    sprintf_s( m_pszSQLString, MAX_SQL_SIZE, "INSERT INTO ABTDATA (SEQ_NUM, OP_INIT_ID, ABTID, AETID, FIRST_TIME, LAST_TIME, SIGNAL_TYPE, NUM_LOB, BEAM_VALIDITY, FREQ_TYPE, FREQ_PATTERN_TYPE, FREQ_PATTERN_PERIOD_MEAN, FREQ_PATTERN_PERIOD_MIN, FREQ_PATTERN_PERIOD_MAX, FREQ_MEAN, FREQ_MIN, FREQ_MAX, FREQ_POSITION_COUNT, PRI_TYPE, PRI_PATTERN_TYPE, PRI_PATTERN_PERIOD_MEAN, PRI_PATTERN_PERIOD_MIN, PRI_PATTERN_PERIOD_MAX, PRI_MEAN, PRI_MAX, PRI_MIN, PRI_JITTER_RATIO, PRI_POSITION_COUNT, PW_MEAN, PW_MIN, PW_MAX, PA_MEAN, PA_MIN, PA_MAX, TOTAL_PDW, RADAR_NAME, RADARMODE_INDEX, THREAT_INDEX, PE_VALID, PE_LATITUDE, PE_LONGGITUDE, PE_CEP, PE_MINOR_AXIS, PE_MAJOR_AXIS, PE_THETA, PE_DISTANCE, ALARM_TIME, STAT ) values( '%d', '%d', '%d', '%d', '%s', '%s', '%d', '%d', '%d', '%d', '%d', '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%d', '%d', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%s', '%d', '%d', '%d', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%s', '%d' )", \
                                                m_nSeqNum, pABTExtData->uiOpInitID, pABTData->uiABTID, pABTData->uiAETID, buffer1, buffer2, \
                                                pABTData->iSignalType, pABTData->uiCoLOB, pABTData->iValidity, \
                                                pABTData->iFreqType, pABTData->iFreqPatternType, pABTData->fFreqPatternPeriodMean, pABTData->fFreqPatternPeriodMin, pABTData->fFreqPatternPeriodMax, pABTData->fFreqMean, pABTData->fFreqMin, pABTData->fFreqMax, pABTData->iFreqPositionCount, \
                                                pABTData->iPRIType, pABTData->iPRIPatternType, pABTData->fPRIPatternPeriodMean, pABTData->fPRIPatternPeriodMin, pABTData->fPRIPatternPeriodMax, pABTData->fPRIMean, pABTData->fPRIMin, pABTData->fPRIMax, pABTData->fPRIJitterRatio, pABTData->iPRIPositionCount, \
                                                pABTData->fPWMean, pABTData->fPWMin, pABTData->fPWMax, pABTData->fPAMean, pABTData->fPAMin, pABTData->fPAMax, \
                                                pABTData->uiTotalOfPDW, pABTData->aucRadarName, pABTData->iRadarModeIndex, pABTData->iThreatIndex, \
                                                pABTData->iPEValid, pABTData->fLatitude, pABTData->fLongitude, pABTData->fCEP, pABTData->fMinorAxis, pABTData->fMajorAxis, pABTData->fTheta, pABTData->fDistanceErrorOfThreat, \
                                                buffer3, pABTData->iStat );


    theRS.Open( m_pszSQLString );

    if( bUpdateThreat == true && pABTData->iThreatIndex > 0 ) {
        __time32_t nowTime=_time32(NULL);

        _localtime32_s( & stTime, & nowTime );
        strftime( buffer1, 100, "%Y-%m-%d %H:%M:%S", & stTime);

        // RADARMODE 테이블에 DATE_LAST_SEEN에 현재 날짜 및 시간을 업데이트 함.
        sprintf_s( m_pszSQLString, MAX_SQL_SIZE, "UPDATE THREAT SET DATE_LAST_SEEN='%s' where THREAT_INDEX=%d", buffer1, pABTData->iThreatIndex );
        theRS.Open( m_pszSQLString );
    }

    theRS.Close();

    // 아래에서 다운이 되면 SQL 버퍼수를 늘히면 됩니다.
    DECLARE_END_CHECKODBC
    DECLARE_RETURN
#endif
}


/**
 * @brief 빔 레코드 추가
 * @param pABTData
 * @param pABTExtData
 * @param bUpdateThreat
 */
bool CELEmitterMergeMngr::InsertToDB_AET( SRxAETData *pAETData, SELAETDATA_EXT *pAETExtData, SELEXTDB *pExtDB )
{
#ifdef _SQLITE_
    bool bRet=true;
    struct tm *pstTime;
    char buffer1[100], buffer2[100], buffer3[100];

    //printf( "\n pAETData[%p], pAETExtData[%p], pExtDB[%p]" , pAETData, pAETExtData, pExtDB );

    pstTime = localtime( & pAETData->tiFirstSeenTime );
    if( pstTime != NULL ) {
        strftime( buffer1, 100, "%Y-%m-%d %H:%M:%S", pstTime);
    }
    else {
        strcpy( buffer1, "1970-01-01 00:00:00" );
    }

    pstTime = localtime( & pAETData->tiLastSeenTime );
    if( pstTime != NULL ) {
        strftime( buffer2, 100, "%Y-%m-%d %H:%M:%S", pstTime);
    }
    else {
        strcpy( buffer2, "1970-01-01 00:00:00" );
    }
    
    pstTime = localtime( & pAETData->tiFinalAlarmTime );
    if( pstTime != NULL ) {
        strftime( buffer3, 100, "%Y-%m-%d %H:%M:%S", pstTime );
    }
    else {
        strcpy( buffer3, "1970-01-01 00:00:00" );
    }

//     printf( "\n%d, \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", %d, %d" , \
//         pAETData->uiAETID, buffer1, buffer2, pAETData->szPrimaryELNOT, pAETData->szPrimaryModeCode, pAETData->szRadarModeName, pAETData->szNickName, pAETData->szFuncCode, m_pIdentifyAlg->GetPlatformCode( ( PlatformCode::EnumPlatformCode ) pAETData->iPlatformType ), pAETData->iRadarModePriority, pAETData->iRadarPriority, \
//         pAETData->iPinNum, pAETData->szPlaceNameKor, pAETData->szThreatFuncCode, pAETData->iThreatPriority );
    sprintf( m_pszSQLString, "INSERT INTO AETDATA (AETID, FIRST_TIME, LAST_TIME, PRIMARY_ELNOT, PRIMARY_MODECODE, RADARMODE_NAME, NICK_NAME, FUNC_CODE, PLATFORM_TYPE, RADAR_MODE_PRIORITY, RADAR_PRIORITY, \
                               PIN_NUM, PLACENAME_KOR, THREAT_FUNC_CODE, THREAT_PRIORITY, \
                               RADARMODE_INDEX, THREAT_INDEX, \
                               VALIDITY, DOA_MEAN, DOA_MIN, DOA_MAX, DOA_DEV, \
                               FRQ_MEAN, FRQ_MIN, FRQ_MAX, FRQ_DEV, \
                               PRI_MEAN,  PRI_MIN, PRI_MAX, PRI_DEV, \
                               PW_MEAN, PW_MIN, PW_MAX, PW_DEV, \
                               PA_MEAN, PA_MIN, PA_MAX, PA_DEV, \
                               PE_VALID, PE_LATITUDE, PE_LONGGITUDE, PE_HEIGHT, PE_CEP, PE_MAJOR_AXIS, PE_MINOR_AXIS, PE_THETA, PE_DISTANCE, \
                               IDINFO, NUM_OF_LOBS, NUM_OF_BEAMS, FINAL_ALARM_TIME, IS_MANUAL_INPUT, MANUALPOSESTPREFERRED, MANUAL_POS_EST_LAT, MANUAL_POS_EST_LONG, STAT ) VALUES \
        ( %d, \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", %d, %d, \
        %d, \"%s\", \"%s\", %d, \
        %d, %d, \
        %d, %f, %f, %f, %f, \
        %f, %f, %f, %f, \
        %f, %f, %f, %f, \
        %f, %f, %f, %f, \
        %f, %f, %f, %f, \
        %d, %f, %f, %f, %f, %f, %f, %f, %f, \
        \"%s\", %d, %d, \"%s\", %d, %d, %f, %f, %d )" , \
        pAETData->uiAETID, buffer1, buffer2, pAETData->szPrimaryELNOT, pAETData->szPrimaryModeCode, pAETData->szRadarModeName, pAETData->szNickName, pAETData->szFuncCode, m_pIdentifyAlg->GetPlatformCode( ( PlatformCode::EnumPlatformCode ) pAETData->iPlatformType ), pAETData->iRadarModePriority, pAETData->iRadarPriority, \
        pAETData->iPinNum, pAETData->szPlaceNameKor, pAETData->szThreatFuncCode, pAETData->iThreatPriority, \
        pAETData->iRadarModeIndex, pAETData->iThreatIndex, \
        pAETData->iValidity, pAETData->fDOAMean, pAETData->fDOAMin, pAETData->fDOAMax, pAETData->fDOADeviation, \
        pAETData->fFreqMean, pAETData->fFreqMin, pAETData->fFreqMax, pAETData->fFreqDeviation, \
        pAETData->fPRIMean, pAETData->fPRIMin, pAETData->fPRIMax, pAETData->fPRIDeviation, \
        pAETData->fPWMean, pAETData->fPWMin, pAETData->fPWMax, pAETData->fPWDeviation, \
        pAETData->fPAMean, pAETData->fPAMin, pAETData->fPAMax, pAETData->fPADeviation, \
        pAETData->iPEValid, pAETData->fLatitude, pAETData->fLongitude, pAETData->fAltidude, pAETData->fCEP, pAETData->fMajorAxis, pAETData->fMinorAxis, pAETData->fTheta, pAETData->fDistanceErrorOfThreat, \
        pAETData->szIDInfo, pAETData->uiCoLOB, pAETData->uiCoABT, buffer3, pAETExtData->bIsManualEdited, pAETExtData->bManualPosEstPreferred, pAETExtData->fManualLatitude, pAETExtData->fManualLongitude, pAETData->iStat );
    
    try {
        //LOGMSG1( enNormal, " m_pszSQLString[%s]" , m_pszSQLString );
        Kompex::SQLiteStatement stmt( m_pDatabase );
        stmt.SqlStatement( m_pszSQLString );

        // do not forget to clean-up
        stmt.FreeQuery();  
    }
    catch( Kompex::SQLiteException &exception ) {
        printf( "\nm_pszSQLString=%p" , m_pszSQLString );
        LOGMSG1( enNormal, " m_pszSQLString[%s]" , m_pszSQLString );
        bRet = false;
        std::cerr << "\nException Occured" << std::endl;
        exception.Show();
        std::cerr << "SQLite result code: " << exception.GetSqliteResultCode() << std::endl;
    }    

    /*
    if( bUpdateThreat == true && pAETData->iThreatIndex > 0 ) {
        __time32_t nowTime=_time32(NULL);

        _localtime32_s( & stTime, & nowTime );
        strftime( buffer1, 100, "%Y-%m-%d %H:%M:%S", & stTime);

        // RADARMODE 테이블에 DATE_LAST_SEEN에 현재 날짜 및 시간을 업데이트 함.
        sprintf_s( m_pszSQLString, "UPDATE THREAT SET DATE_LAST_SEEN='%s' where THREAT_INDEX=%d", buffer1, pABTData->iThreatIndex );
        exec( m_pszSQLString );
    }
    */

    return bRet;

#elif _NO_SQLITE_
    return true;

#else
    DECLARE_BEGIN_CHECKODBC

    CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );

    struct tm *pstTime;
    char buffer1[100], buffer2[100], buffer3[100];

    pstTime = localtime( & pAETData->tiFirstSeenTime );
    if( pstTime != NULL ) {
        strftime( buffer1, 100, "%Y-%m-%d %H:%M:%S", pstTime);
    }
    else {
        strcpy( buffer1, "1970-01-01 00:00:00" );
    }

    pstTime = localtime( & pAETData->tiLastSeenTime );
    if( pstTime != NULL ) {
        strftime( buffer2, 100, "%Y-%m-%d %H:%M:%S", pstTime);
    }
    else {
        strcpy( buffer2, "1970-01-01 00:00:00" );
    }

    pstTime = localtime( & pAETData->tiFinalAlarmTime );
    if( pstTime != NULL ) {
        strftime( buffer3, 100, "%Y-%m-%d %H:%M:%S", pstTime );
    }
    else {
        strcpy( buffer3, "1970-01-01 00:00:00" );
    }

    sprintf_s( m_pszSQLString, MAX_SQL_SIZE, "INSERT INTO AETDATA (SEQ_NUM, OP_INIT_ID, AETID, FIRST_TIME, LAST_TIME, PRIMARY_ELNOT, PRIMARY_MODECODE, RADARMODE_NAME, NICK_NAME, FUNC_CODE, PLATFORM_TYPE, RADARMODE_PRIORITY, RADAR_PRIORITY, \
                              PIN_NUM, PLACENAME_KOR, THREAT_FUNC_CODE, THREAT_PRIORITY, \
                              RADARMODE_INDEX, THREAT_INDEX, \
                              VALIDITY, DOA_MEAN, DOA_MIN, DOA_MAX, DOA_DEV, \
                              FRQ_MEAN, FRQ_MIN, FRQ_MAX, FRQ_DEV, \
                              PRI_MEAN,  PRI_MIN, PRI_MAX, PRI_DEV, \
                              PW_MEAN, PW_MIN, PW_MAX, PW_DEV, \
                              PA_MEAN, PA_MIN, PA_MAX, PA_DEV, \
                              PE_VALID, PE_LATITUDE, PE_LONGGITUDE, PE_HEIGHT, PE_CEP, PE_MAJOR_AXIS, PE_MINOR_AXIS, PE_THETA, PE_DISTANCE, \
                              IDINFO, NUM_OF_LOBS, NUM_OF_BEAMS, FINAL_ALARM_TIME, STAT ) VALUES \
                              ( '%d', '%d', '%d', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%d', '%d', \
                              '%d', '%s', '%s', '%d', \
                              '%d', '%d', \
                              '%d', '%f', '%f', '%f', '%f', \
                              '%f', '%f', '%f', '%f', \
                              '%f', '%f', '%f', '%f', \
                              '%f', '%f', '%f', '%f', \
                              '%f', '%f', '%f', '%f', \
                              '%d', '%f', '%f', '%f', '%f', '%f', '%f', '%f', '%f', \
                              '%s', '%d', '%d', '%s', '%d' )" , \
                              m_nSeqNum, m_lOpInitID, \
                              pAETData->uiAETID, buffer1, buffer2, pAETData->szPrimaryELNOT, pAETData->szPrimaryModeCode, pAETData->szRadarModeName, pAETData->szNickName, pAETData->szFuncCode, m_pIdentifyAlg->GetPlatformCode( ( PlatformCode::EnumPlatformCode ) pAETData->iPlatformType ), pAETData->iRadarModePriority, pAETData->iRadarPriority, \
                              pAETData->iPinNum, pAETData->szPlaceNameKor, pAETData->szThreatFuncCode, pAETData->iThreatPriority, \
                              pAETData->iRadarModeIndex, pAETData->iThreatIndex, \
                              pAETData->iValidity, pAETData->fDOAMean, pAETData->fDOAMin, pAETData->fDOAMax, pAETData->fDOADeviation, \
                              pAETData->fFreqMean, pAETData->fFreqMin, pAETData->fFreqMax, pAETData->fFreqDeviation, \
                              pAETData->fPRIMean, pAETData->fPRIMin, pAETData->fPRIMax, pAETData->fPRIDeviation, \
                              pAETData->fPWMean, pAETData->fPWMin, pAETData->fPWMax, pAETData->fPWDeviation, \
                              pAETData->fPAMean, pAETData->fPAMin, pAETData->fPAMax, pAETData->fPADeviation, \
                              pAETData->iPEValid, pAETData->fLatitude, pAETData->fLongitude, pAETData->fAltidude, pAETData->fCEP, pAETData->fMajorAxis, pAETData->fMinorAxis, pAETData->fTheta, pAETData->fDistanceErrorOfThreat, \
                              pAETData->szIDInfo, pAETData->uiCoLOB, pAETData->uiCoABT, buffer3, pAETData->iStat );

    theRS.Open( m_pszSQLString );
    theRS.Close();

    DECLARE_END_CHECKODBC
    DECLARE_RETURN

#endif
}

/**
 * @brief     GetABTData
 * @param     unsigned int uiAETID
 * @param     unsigned int uiABTID
 * @return    SRxABTData *
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-08-02, 13:48
 * @warning
 */
SRxABTData *CELEmitterMergeMngr::GetABTData( unsigned int uiAETID, unsigned int uiABTID )
{
    CELThreat *pABTTheThreat;

    pABTTheThreat = m_pTheThreatRoot->Find( uiAETID, uiABTID );
    return GetABTData( pABTTheThreat->m_nIndex );
}

/**
 * @brief     GetABTExtData
 * @param     unsigned int uiAETID
 * @param     unsigned int uiABTID
 * @return    SELABTDATA_EXT *
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-08-02, 13:48
 * @warning
 */
SELABTDATA_EXT *CELEmitterMergeMngr::GetABTExtData( unsigned int uiAETID, unsigned int uiABTID )
{
    CELThreat *pABTTheThreat;

    pABTTheThreat = m_pTheThreatRoot->Find( uiAETID, uiABTID );
    return GetABTExtData( pABTTheThreat->m_nIndex );
}

/**
 * @brief CELEmitterMergeMngr::GetELNOT
 * @param iRadarModeIndex
 * @return
 */
char *CELEmitterMergeMngr::GetELNOT( int iRadarModeIndex )
{
    char *pszELNOT;
    SRadarMode *pSRadarMode;

    pSRadarMode = m_pIdentifyAlg->GetRadarMode( iRadarModeIndex );

    if( pSRadarMode != NULL ) {
        pszELNOT = pSRadarMode->szELNOT;
    }
    else {
        pszELNOT = NULL;
    }

    return pszELNOT;
}

/**
 * @brief CELEmitterMergeMngr::GetRadarModeName
 * @param iRadarModeIndex
 * @return
 */
char *CELEmitterMergeMngr::GetRadarModeName( int iRadarModeIndex )
{
    char *pszELNOT;
    SRadarMode *pSRadarMode;

    pSRadarMode = m_pIdentifyAlg->GetRadarMode( iRadarModeIndex );

    if( pSRadarMode != NULL ) {
        pszELNOT = pSRadarMode->szRadarModeName;
    }
    else {
        pszELNOT = NULL;
    }

    return pszELNOT;
}

/**
 * @brief CELEmitterMergeMngr::GetThreatModeName
 * @param iRadarModeIndex
 * @return
 */
char *CELEmitterMergeMngr::GetThreatName( int iRadarModeIndex )
{
    char *pszThreat;

    SThreat *pSThreat;
    SRadarMode *pSRadarMode;

    pSRadarMode = m_pIdentifyAlg->GetRadarMode( iRadarModeIndex );

    if( pSRadarMode != NULL ) {
        pSThreat = m_pIdentifyAlg->GetThreat( pSRadarMode->iThreatIndex );
        if( pSThreat != NULL )
            pszThreat = pSThreat->szThreatName;
        else
            pszThreat = NULL;
    }
    else {
        pszThreat = NULL;
    }

    return pszThreat;
}


/**
 * @brief CEmitterMerge::IsTryAnalScan
 * @return
 */
bool CELEmitterMergeMngr::DoesAnalScanTry()
{
    bool bRet=false;
    SELABTDATA_EXT *pABTExtData = GetABTExtData();
    SRxABTData *pABTData = GetABTData();

    if( pABTData != NULL ) {
        if( pABTData->iScanType == E_AET_SCAN_UNKNOWN ) {
            if( pABTExtData->enBeamEmitterStat == E_ES_NEW || pABTExtData->enBeamEmitterStat == E_ES_REACTIVATED ) {
                bRet = true;
            }
        }
    }
    return bRet;
}

/**
 * @brief CELEmitterMergeMngr::SetStartOfAnalScan
 */
void CELEmitterMergeMngr::SetStartOfAnalScan()
{
    if( m_pABTExtData != NULL ) {

    }
}
