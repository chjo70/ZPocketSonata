// KnownSigAnal.cpp: implementation of the CKnownSigAnal class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include <stdio.h>
#include <string.h>

#include "../OFP_Main.h"

#include "KnownSigAnal.h"

#include "../../Include/globals.h"

#include "../../Utils/ccommonutils.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET
// 반환되는 형  : CKnownSigAnal::CKnownSigAnal(int coMaxPdw) : CKGroup(coMaxPdw), CKPulExt(coMaxPdw), CKAnalPRI(coMaxPdw),
// 함 수 인 자  : int coMaxPdw
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-06-24 15:41:08
//
//##ModelId=429A5BDA0153
#ifdef _MSSQL_
CKnownSigAnal::CKnownSigAnal( int coMaxPdw, bool bDBThread ) : CMSSQL( & m_theMyODBC )
#else
CKnownSigAnal::CKnownSigAnal( int coMaxPdw, bool bDBThread, const char *pFileName )
#endif
{
    size_t szSize;

    m_bDBThread = bDBThread;

    CCommonUtils::SetUnitType();

    // MSSQL 연결
#ifdef _SQLITE_
    try {
        m_pDatabase = new Kompex::SQLiteDatabase( pFileName, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, 0 );

    }
    catch( Kompex::SQLiteException &exception ) {
        std::cerr << "\nException Occured" << std::endl;
        exception.Show();
        std::cerr << "SQLite result code: " << exception.GetSqliteResultCode() << std::endl;
    }

    m_pszSQLString = ( char *) malloc( MAX_SQL_SIZE );

#elif _MSSQL_
    CMSSQL::Init();

    m_pszSQLString = ( char *) malloc( MAX_SQL_SIZE );

#else
    
#endif

	InitVar();

	m_theGroup = new CKGroup( this, coMaxPdw );
	m_thePulExt = new CKPulExt( this, coMaxPdw );
	m_theAnalPRI = new CKAnalPRI( this, coMaxPdw );
	m_theMakeAET = new CKMakeAET( this, coMaxPdw );

	if( m_theGroup == NULL || m_thePulExt == NULL || m_theAnalPRI == NULL || m_theMakeAET == NULL ) {
#ifndef _WIN32
		printf( "\n 메모리가 부족 합니다." );
		printf( "\n ksp.def 에서 heap size를 늘려주세요." );
		printf( "\n m_theGroup:: this[%p]" , m_theGroup );
		printf( "\n m_thePulExt:: this[%p]" , m_thePulExt );
		printf( "\n m_theAnalPRI:: this[%p]" , m_theAnalPRI );
		printf( "\n m_theMakeAET:: this[%p]" , m_theMakeAET );
#endif

	}
	
	m_nMaxPdw = coMaxPdw;

	m_pSeg = GetPulseSeg();

	m_pGrPdwIndex = GetFrqAoaGroupedPdwIndex();

    m_pMidasBlue = new CMIDASBlueFileFormat;

    m_stSavePDWData.pstPDW = NULL;
    szSize = CCommonUtils::CheckMultiplyOverflow( sizeof(_PDW), coMaxPdw );
    _SAFE_MALLOC( m_stSavePDWData.pstPDW, _PDW, szSize )

    InitDataFromDB();

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKnownSigAnal::~CKnownSigAnal
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-06-24 15:38:44
//
//##ModelId=429A5BDA0154
CKnownSigAnal::~CKnownSigAnal()
{
    _SAFE_DELETE( m_pMidasBlue )

	_SAFE_DELETE( m_theGroup )
	_SAFE_DELETE( m_thePulExt )
	_SAFE_DELETE( m_theAnalPRI )
	_SAFE_DELETE( m_theMakeAET )

    _SAFE_FREE( m_pszSQLString )

    _SAFE_FREE( m_stSavePDWData.pstPDW )
	
}

/**
 * @brief CKnownSigAnal::Init
 */
void CKnownSigAnal::Init()
{

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CKnownSigAnal::Start
		\author   조철희
		\param    pPdwBank 인자형태 STR_PDWBANK *
		\param    pKwnAet 인자형태 STR_MANAET *
		\return   void
		\version  0.0.29
		\date     2008-07-10 12:43:16
		\warning
*/
void CKnownSigAnal::Start( STR_STATIC_PDWDATA *pstPDWData, SRxABTData *pTrkAet )
{
    Log( enLineFeed, "" );

    PrintFunction;

	BOOL bRet;

	// 추적할 에미터를 복사한다.
    m_pTrkAet = pTrkAet;

    ++ m_uiStep;

	// 신호 분석 관련 초기화.
    Init( pstPDWData );

    Log( enNormal, "#### 추적 분석 시작[%dth, Co:%d] ####" , m_uiStep, m_CoPdw );

    InsertRAWData( & m_stSavePDWData, _spZero, true );

	// 펄스열 인덱스를 참조하여 행렬 값에 저장한다.
    m_theGroup->MakePDWArray( & pstPDWData->stPDW[0], (int) m_CoPdw, pstPDWData->GetBand() );

    // 수집한 PDW 파일 만들기...
    //m_pMidasBlue->SaveRawDataFile( SHARED_DATA_DIRECTORY, E_EL_SCDT_PDW, pPDWData );

	// 그룹화 만들기
	// 기존에 추출 기능을 그대로 이용하기 위한 초기 설정함.
	m_theGroup->MakeGroup();

	// 그룹화 만들기
    if( TRUE == m_theGroup->MakeGrIndex() ) {
        // 펄스열 추출
        m_thePulExt->KnownPulseExtract();
        
        // PRI 분석
        m_theAnalPRI->KnownAnalysis();
        
        // 에미터 분석
        bRet = m_theMakeAET->KnownMakeAET();
        
        //////////////////////////////////////////////////////////////////////////
        // printf( "\n 새로운 에미터 분석 시작" );

        // 추적 추출이 성공이면 나머지 잔여 펄스들에 대해서 펄스열 추출해서 에미터를 분석한다.
        if( bRet == TRUE ) {
            // 그룹화 만들기
            m_theGroup->MakeFreqAoaPwGroup();
            m_theGroup->MakeGrIndex();
        }
        else {
            /*! \bug  추적이 실패가 되면 수집된 펄스열로부터 새로운 탐지 분석을 하게 한다.
                \date 2006-06-27 12:19:01, 조철희
            */

            memset( MARK, 0, sizeof( MARK ) );

            // 펄스열 추출 초기화
            m_thePulExt->CPulExt::Init();

            // PRI 분석 초기화
            m_theAnalPRI->CAnalPRI::Init();

            // AET 생성 초기화
            m_theMakeAET->CMakeAET::Init();
        }

        ////////////////////////////////////////////////////////////////////
        // 새로운 에미터 분석

        ////////////////////////////////////////////////////////////////////
        // 잔여 펄스들에 대해서 새로운 에미터 분석
        // 1) 처음부터 다시 새로운 에미터 분석 ?
        // 2) 추출한 펄스열은 제거한 상태에서 분석 ?
        m_thePulExt->PulseExtract();

        // 나머지 잔여 펄스들은 Unknown 펄스열 추출에 저장한다.
        // m_thePulExt->CPulExt::UnknownExtract();

        // PRI 분석을 실시한다.
        m_theAnalPRI->Analysis();

        // 상속클래스의 에미터 분석
        m_theMakeAET->MakeAET();

#ifdef _POCKETSONATA_
#elif defined(_ELINT) || defined(_XBAND_)
#else
        // 추적 에미터와 새로운 에미터와 상관성을 확인하여 추적 에미터 여부를 결정한다.
        m_theMakeAET->MakeUpAET();

        // 그룹화된 펄스열 저장하기
        SaveGroupPdwFile();

        // 수집 개수 초기화
        // 에미터 전송 전에 수집 버퍼 초기화를 한다.
        ClearColBuffer();

        SendAllAet();
#endif

        // printf( "\n !!!! End of Known Signal Analysis !!!!" );
    }

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKnownSigAnal::ClearColBuffer
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-08-30 09:20:30
//
void CKnownSigAnal::ClearColBuffer()
{
#ifdef __GNUC__
    //m_pPdwBank->count = 0;
#elif _POCKETSONATA_

#elif defined(_ELINT) || defined(_XBAND_)
#else
    m_pPdwBank-> = 0;
#endif

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CKnownSigAnal::InitVar
		\author   조철희
		\return   void
		\version  0.0.52
		\date     2008-10-25 15:59:18
		\warning
*/
void CKnownSigAnal::InitVar()
{
    m_uiStep = 0;

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CKnownSigAnal::Init
		\author   조철희
		\param    pPdwBank 인자형태 STR_PDWBANK *
		\return   void
		\version  0.0.29
		\date     2005-06-24 16:03:22
		\warning
*/
void CKnownSigAnal::Init( STR_STATIC_PDWDATA *pstPDWData )
{

    // 시간 초기화
    m_tColTime = 0;
    m_tColTimeMs = 0;

	// 추적은 실패로 초기화 한다.
	m_CoUpdAet = 0;
	m_CoNewAet = 0;

	// 수집 버퍼 정의
    m_pstPDWData = pstPDWData;

	// 신호 수집 개수 정의
    if( pstPDWData != NULL ) {
        memcpy( & m_stSavePDWData.x, & pstPDWData->x, sizeof(UNION_HEADER) );

        m_CoPdw = m_pstPDWData->GetTotalPDW();

        m_tColTime = m_pstPDWData->GetColTime();

        m_uiPDWID = m_pstPDWData->GetPDWID();

        m_iIsStorePDW = m_pstPDWData->x.ps.iIsStorePDW;
    }
    else {
        // m_CoPdw = _spZero;

    }

    m_uiABTID = m_pTrkAet->uiABTID;

	/*! \bug  클래스별 클리어를 하게 한다.
	    \date 2008-07-30 13:22:13, 조철희
	*/

	// 그룹화 초기화
	m_theGroup->CKGroup::Init();

	// 펄스열 추출 초기화
	m_thePulExt->CKPulExt::Init();

	// PRI 분석 초기화
	m_theAnalPRI->CKAnalPRI::Init();

	// AET 생성 초기화
	m_theMakeAET->CKMakeAET::Init();

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKnownSigAnal::MarkToPdwIndex
// 반환되는 형  : void
// 함 수 인 자  : PDWINDEX *pPdwIndex
// 함 수 인 자  : int count
// 함 수 인 자  : int mark_type
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-07-28 11:49:37
//
//##ModelId=42E85F3401B8
void CKnownSigAnal::MarkToPdwIndex( PDWINDEX *pPdwIndex, int count, USHORT usMarkType)
{
	for( int i=0 ; i < count ; ++i )
		MARK[ *pPdwIndex++ ] = usMarkType;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKnownSigAnal::SaveEmitterPdwFile
// 반환되는 형  : void
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 인 자  : int index
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-07-28 13:59:41
//
//##ModelId=42E98F2F02C3
void CKnownSigAnal::SaveEmitterPdwFile(STR_EMITTER *pEmitter, int iPLOBID, bool bSaveFile )
{
    unsigned int i;

    PDWINDEX *pPdwIndex;
    _PDW *pPDW;

    m_stSavePDWData.SetTotalPDW( pEmitter->pdw.uiCount );

    pPdwIndex = pEmitter->pdw.pIndex;
    for( i=0 ; i < pEmitter->pdw.uiCount ; ++i ) {
        pPDW = & m_pstPDWData->stPDW[ *pPdwIndex++ ];
        memcpy( & m_stSavePDWData.pstPDW[i], pPDW, sizeof(_PDW) );

    }

    // 수집한 PDW 파일 저장하기...
    InsertRAWData( & m_stSavePDWData, iPLOBID, bSaveFile );

// 
// #ifdef _DEBUG_MAKEPDW
// 	int i;
// 	int total_count;
// 	FILE *pdwfile;
// 	TNEW_PDW *pPDW;
// 	PDWINDEX *pPdwIndex;
// 	PDWINDEX *pEmitterPdwIndex;
// 
// 	char filename[100];
// 
// 	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
// 	CA50SigAnalView *pView = ( CA50SigAnalView * ) pFrame->GetActiveView();
// 
// 	CString strFilename=pView->GetFileTitle();
// 
// 	LPTSTR p = strFilename.GetBuffer( 100 );
// 
// 	pPdwIndex = & m_pGrPdwIndex->pIndex[0];
// 	int nStep = theSigAnal->m_theNewSigAnal->GetCoStep();
// 	sprintf( filename, "c:\\temp\\%03d_%03d_%s.kwn_emt.pdw", nStep, iPLOBID, p );
// 	pdwfile = fopen( filename, "wb" );
// 
// 	total_count = pEmitter->pdw.uiCount;
// 
// 	pEmitterPdwIndex = pEmitter->pdw.pIndex;
// 	for( i=0 ; i < total_count ; ++i ) {
// 		pPDW = & m_pPdwBank->pPdw[ *pEmitterPdwIndex++ ];
// 
// #ifdef _A50_RWR
// 		TNEW_PDW pdw;
// 
// 		pdw.word[0] = ntohl( pPDW->word[0] );
// 		pdw.word[1] = ntohl( pPDW->word[1] );
// 		pdw.word[2] = ntohl( pPDW->word[2] );
// 		pdw.word[3] = ntohl( pPDW->word[3] );
// 
// 		fwrite( & pdw, sizeof( TNEW_PDW ), 1, pdwfile );
// #else
// 		fwrite( pPDW, sizeof( TNEW_PDW ), 1, pdwfile );
// #endif
// 	}
// 
// 	fclose( pdwfile );
// 
// 	strFilename.ReleaseBuffer();
// 
// #endif

}

/**
 * @brief     InsertRAWData
 * @param     STR_PDWDATA * pPDWData
 * @param     int iPLOBID
 * @param     bool bSaveFile
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-05, 19:55
 * @warning
 */
void CKnownSigAnal::InsertRAWData( STR_PDWDATA *pPDWData, int iPLOBID, bool bSaveFile )
{
    bool bRet=true;
    char buffer[100]={0};
    TCHAR szDirectory[500], szRawDataPathname[600];

    struct tm *pstTime;
    struct timespec tiNow;

    GetCollectTime( & tiNow );
    pstTime = localtime( & tiNow.tv_sec );

#ifdef _ELINT_
    sprintf_s( szDirectory, "%s\\수집소_%d\\%s", SHARED_DATA_DIRECTORY, pPDWData->x.el.iCollectorID, pPDWData->x.el.aucTaskID );

#elif _XBAND_
    //sprintf_s( szDirectory, "%s\\수집소_%d\\%s\\%s", SHARED_DATA_DIRECTORY, pPDWData->x.el.iCollectorID, buffer, pPDWData->x.el.aucTaskID );
    sprintf_s( szDirectory, "%s\\수집소_%d\\%s", SHARED_DATA_DIRECTORY, pPDWData->x.el.GetCollectorID(), pPDWData->x.el.aucTaskID );

#elif _POCKETSONATA_
    sprintf( szDirectory, _T("%s/%s/BRD_%d/%s"), SHARED_DATA_DIRECTORY, buffer, pPDWData->x.ps.uiBoardID, g_szCollectBank[pPDWData->x.ps.iBank] );

#else
    sprintf( szDirectory, "%s/BRD", pLocalDirectory );

#endif

    if( pstTime != NULL && bSaveFile == true ) {
        // 1. 폴더명 생성하기
        strftime( buffer, 100, "%Y-%m-%d", pstTime );

        bRet = CreateDir( szDirectory );
    }

    if( pstTime != NULL && bRet == true ) {
        if( bSaveFile == true ) {
            // 2. 파일명 생성하기
            strftime( buffer, 100, "%Y-%m-%d_%H_%M_%S", pstTime );

#if defined(_ELINT_) || defined(_XBAND_)
            sprintf( m_szRawDataFilename, _T("%d_%s_%010d_%d%s"), pPDWData->x.el.GetCollectorID(), buffer, m_uiPDWID, iPLOBID, PDW_EXT );

#elif _POCKETSONATA_
            sprintf( m_szRawDataFilename, _T("%d_%s_%010d_%d.%s.%s"), pPDWData->x.ps.uiBoardID, buffer, m_uiPDWID, iPLOBID, PDW_TYPE, MIDAS_EXT );
            //         if( enDataType == E_EL_SCDT_PDW ) {
            //             sprintf( szRawDataFilename, "%s/%s_COL%d_%s_%06d.%s.%s", szDirectory, g_szCollectBank[pPDWData->x.ps.iBank], pPDWData->x.ps.iBoardID, buffer, m_uiStep, PDW_TYPE, MIDAS_EXT );
            //         }
            //         else {
            //             sprintf( szRawDataFilename, "%s/%s_COL%d_%s_%06d.%s", szDirectory, g_szCollectBank[pPDWData->x.ps.iBank], pPDWData->x.ps.iBoardID, buffer, m_uiStep, PDW_EXT );
            //         }

#else

#endif
            sprintf( szRawDataPathname, _T("%s\\%s"), szDirectory, m_szRawDataFilename );
            m_pMidasBlue->SaveRawDataFile( szRawDataPathname, E_EL_SCDT_PDW, pPDWData );
        }
        else {
            m_szRawDataFilename[0] = NULL;
        }

        if( m_bDBThread == false ) {
            // RAWDATA 데이터 저장
            InsertToDB_RAW( pPDWData, iPLOBID ); 
        }
        else {
            TRACE( "Push the data for InsertToDB_RAW()" );
        }

    }

}

/**
 * @brief     InsertToDB_RAW
 * @param     STR_PDWDATA * pPDWData
 * @param     int iPLOBID
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-05, 20:20
 * @warning
 */
bool CKnownSigAnal::InsertToDB_RAW( STR_PDWDATA *pPDWData, int iPLOBID )
{
    struct timespec tiNow;

    char buffer[100];

    GetCollectTime( & tiNow );
    CCommonUtils::getStringDesignatedTime( buffer, sizeof(buffer), tiNow.tv_sec );

#ifdef _MSSQL_
#ifdef _POCKETSONATA_
    sprintf_s( m_pszSQLString, MAX_SQL_SIZE, "INSERT INTO RAWDATA ( OP_INIT_ID, PDWID, PLOBID, CREATE_TIME, CREATE_TIME_MS, COUNTOFDATA, FILENAME, DATA_TYPE, COL_BANK ) values( \
                                             '%ld', '%d', '%d', '%s', '0', '%d', '%s', '%d', '%d' )", \
                                             m_lOpInitID, m_uiPDWID, iPLOBID, buffer, pPDWData->GetTotalPDW(), m_szRawDataFilename, E_EL_SCDT_PDW, pPDWData->x.ps.iBank );

#elif defined(_ELINT_) || defined(_XBAND_)
    sprintf_s( m_pszSQLString, MAX_SQL_SIZE, "INSERT INTO RAWDATA ( OP_INIT_ID, PDWID, PLOBID, TASK_ID, CREATE_TIME, CREATE_TIME_MS, COUNTOFDATA, FILENAME, DATA_TYPE ) values( \
                                             '%ld', '%d', '%d', '%s', '%s', '%d', '%d', '%s', '%d' )", \
                                             m_lOpInitID, m_uiPDWID, iPLOBID, pPDWData->x.el.aucTaskID, buffer, iPLOBID, pPDWData->GetTotalPDW(), m_szRawDataFilename, E_EL_SCDT_PDW );

#else
    sprintf_s( m_pszSQLString, MAX_SQL_SIZE, "INSERT INTO RAWDATA ( OP_INIT_ID, PDWID, PLOBID, TASK_ID, CREATE_TIME, CREATE_TIME_MS, COUNTOFDATA, FILENAME, DATA_TYPE ) values( \
                                             '%ld', '%d', '%d', '%s', '%s', '%d', '%d', '%s', '0' )", \
                                             m_lOpInitID, m_uiPDWID, pPDWData->x.el.aucTaskID, buffer, iPLOBID, pPDWData->GetTotalPDW(), m_szRawDataFilename );

#endif

#elif _SQLITE_
#ifdef _POCKETSONATA_
    sprintf( m_pszSQLString, "INSERT INTO RAWDATA ( PDWID, PLOBID, CREATE_TIME, CREATE_TIME_MS, COUNTOFDATA, FILENAME, DATA_TYPE, COL_BANK ) values( \
                                             '%d', '%d', '%s', '0', '%d', '%s', '%d', '%d' )", \
                                             m_uiPDWID, iPLOBID, buffer, pPDWData->GetTotalPDW(), m_szRawDataFilename, E_EL_SCDT_PDW, pPDWData->x.ps.iBank );

#elif defined(_ELINT_) || defined(_XBAND_)
    sprintf_s( m_pszSQLString, MAX_SQL_SIZE, "INSERT INTO RAWDATA ( PDWID, PLOBID, TASK_ID, CREATE_TIME, CREATE_TIME_MS, COUNTOFDATA, FILENAME, DATA_TYPE, COL_BANK ) values( \
                                             '%d', '%d', '%s', '%s', '%d', '%d', '%s', '0' )", \
                                             m_uiPDWID, iPLOBID, buffer, pPDWData->GetTotalPDW(), m_szRawDataFilename, E_EL_SCDT_PDW, pPDWData->x.ps.iBank );

#else
    sprintf_s( m_pszSQLString, MAX_SQL_SIZE, "INSERT INTO RAWDATA ( PDWID, PLOBID, TASK_ID, CREATE_TIME, CREATE_TIME_MS, COUNTOFDATA, FILENAME, DATA_TYPE, COL_BANK ) values( \
                                             '%d', '%d', '%s', '%s', '%d', '%d', '%s', '0' )", \
                                             m_uiPDWID, iPLOBID, buffer, pPDWData->GetTotalPDW(), m_szRawDataFilename, E_EL_SCDT_PDW, pPDWData->x.ps.iBank );


#endif

#endif

#ifdef _MSSQL_
    DECLARE_BEGIN_CHECKODBC

    CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );

    theRS.Open( m_pszSQLString );
    Log( enDebug, ".InsertRAW[O%d, P%d, P%d]" , m_lOpInitID, m_uiPDWID, iPLOBID );

    theRS.Close();

    DECLARE_END_CHECKODBC
    DECLARE_RETURN

#elif _SQLITE_
    bool bRet=true;
    
    if( m_pszSQLString[0] != NULL ) {
        try {
            Kompex::SQLiteStatement stmt( m_pDatabase );
            stmt.SqlStatement( m_pszSQLString );
            Log( enDebug, ".InsertRAW[O%d, P%d, P%d]" , m_lOpInitID, m_uiPDWID, iPLOBID );

            // do not forget to clean-up
            stmt.FreeQuery();  
        }
        catch( Kompex::SQLiteException &exception ) {
            LOGMSG1( enError, " m_pszSQLString[%s]" , m_pszSQLString );
            bRet = false;
            std::cerr << "\nException Occured" << std::endl;
            exception.Show();
            std::cerr << "SQLite result code: " << exception.GetSqliteResultCode() << std::endl;
        }
    }
    else {
        bRet = false;
    }

    return bRet;

#else
    return true;

#endif

}

/**
 * @brief     InitDataFromDB
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-05, 20:43
 * @warning
 */
void CKnownSigAnal::InitDataFromDB()
{

#ifdef _MSSQL_

#if defined(_ELINT_) || defined(_XBAND_) || defined(_POCKETSONATA_)
    char buffer[400];

    sprintf_s( buffer, sizeof(buffer), "select max(OP_INIT_ID) from LOBDATA" );
    m_lOpInitID = GetINTData( buffer ) + 1;

    sprintf_s( buffer, sizeof(buffer), "select max(OP_INIT_ID) from RAWDATA" );
    m_lOpInitID = _max( m_lOpInitID, GetINTData( buffer ) + 1 );

#endif

#else
    m_lOpInitID = _spOne;


#endif

}

#ifdef _POCKETSONATA_
#elif defined(_ELINT)
#else
//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKnownSigAnal::SendAllAet
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-07-29 09:49:57
//
//##ModelId=42E98F2E01E5
void CKnownSigAnal::SendAllAet()
{
	int i, count;

	m_CoNewAet = 0;

    SRxLOBData *pNewAet;
    SRxLOBData *pUpdAet;
    SRxLOBData *pDstAet;

	// 추적 성공 또는 실패인지를 검사한다.
	pUpdAet = m_theMakeAET->GetUpdLOB();
	if( pUpdAet != NULL ) {
		SendUpdAet( pUpdAet );
		m_CoUpdAet = 1;
	}
	else {
		SendLostAet();
		m_CoUpdAet = 0;
	}

// 	if( CO_MAX_KSP_NEW_AET >= 0 ) {
// 		// m_theMakeAET->SetCoNewAet( 0 );
// 		return;
// 	}
// 
// 	// 두개 이상의 추적 성공 에미터 제외한다.
// 	count = m_theMakeAET->GetCoNewAet();
// 
//     pNewAet = m_theMakeAET->GetLOBData();
// 
// 	int inEMT;
// 
// 	inEMT = m_theMakeAET->GetIndexNewAet();
// 
// 	/*! \bug  새로운 에미터에 대한 포인터
// 	    \date 2008-07-30 13:06:51, 조철희
// 	*/
// 	pDstAet = pNewAet + inEMT;
// 
// 	for( i=0 ; i < count ; ++i ) {
// 		if( pUpdAet == NULL ||
//             ( pUpdAet != NULL && m_theMakeAET->CheckHarmonic<SRxLOBData>( pUpdAet, (pNewAet+inEMT) ) == 0 ) ) {
// 			// CheckHarmonic() 에서는 PRI 값으로 펄스열 병합을 수행하고
// 			// 실패된 펄스열에 대해서 이제는 펄스열 인덱스를 비교해서 두 펄스열간의 병합을 최종 판단한다.
// 			//-- 조철희 2005-10-31 13:59:43 --//
// 			//if( TRUE == CheckPdwHarmonic( pUpdAet, pNewAet ) )
// 			{
// 				SendNewAet( pNewAet, inEMT );
// 
// 				memcpy( pDstAet, & pNewAet[inEMT], sizeof( STR_NEWAET ) );
// 				++ pDstAet;
// 
// 				// 추적에서 새로운 에미터 개수를 제한한다.
// 				++ m_CoNewAet;
// 				if( m_CoNewAet >= CO_MAX_KSP_NEW_AET ) {
// 					// m_theMakeAET->SetCoNewAet( m_CoNewAet );
// 					return;
// 				}
// 			}
// 		}
// 
// 		++ inEMT;
// 	}

	// m_theMakeAET->SetCoNewAet( CoNewAet );

}
#endif

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKnownSigAnal::SendUpdAet
// 반환되는 형  : void
// 함 수 인 자  : STR_UPDAET *pUpdAet
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-07-29 10:46:25
//
//##ModelId=42E98F2E0131
void CKnownSigAnal::SendUpdAet( SRxLOBData *pUpdAet )
{
	// m_theMakeAET->DISP_FineAet( pUpdAet );

#ifdef _WIN32

#else
	// SendKSPUpdAet( pUpdAet );

#endif


}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKnownSigAnal::SendLostAet
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-07-29 10:49:25
//
//##ModelId=42E98F2E00FF
void CKnownSigAnal::SendLostAet()
{
#ifdef _WIN321
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CAdvSigAnalView *pView = ( CAdvSigAnalView * ) pFrame->GetActiveView();

	gUpdAet[m_KwnAet.aet.noEMT].aet.noEMT = 0;
	pView->UpdateUpdAetInfo( & gUpdAet[stTrkAet.aet.noEMT], m_pPdwBank );
	SendKSPLostAet( & stTrkAet, _spInsuPul );
#else
	// SendKSPLostAet( & stTrkAet, _spInsuPul );

#endif

#if defined(_ELINT_) || defined(_XBAND_)
	//Log( enNormal, "Lost[%d]" , stTrkAet.aet.noEMT );
#else
#endif

    //if( stTrkAet.aet.noEMT == -1 ) {
    //	while( true );
    //}

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKnownSigAnal::SendNewAet
// 반환되는 형  : void
// 함 수 인 자  : STR_NEWAET *pNewAet
// 함 수 인 자  : int inEMT
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-07-29 10:50:28
//
//##ModelId=42E98F2E004B
void CKnownSigAnal::SendNewAet(SRxLOBData *pNewAet, int inEMT )
{

	// m_theMakeAET->DISP_FineAet( pNewAet+inEMT );

#ifdef _WIN32

#else
	// SendKSPNewAet( pNewAet, inEMT );

#endif


}

/**
 * @brief     
 * @param     struct timespec * pTimeSpec
 * @return    void
 * @author    議곗쿋??(churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022/01/26 21:57:51
 * @warning   
 */
void CKnownSigAnal::GetCollectTime( struct timespec *pTimeSpec )
{
	if( m_tColTime == 0 ) {
		clock_gettime( CLOCK_REALTIME, pTimeSpec );
	}
	else {
		pTimeSpec->tv_sec = m_tColTime;
#ifdef _MSC_VER
		pTimeSpec->tv_usec = m_tColTimeMs * 1000;
#else
		pTimeSpec->tv_nsec = m_tColTimeMs * 1000000;
#endif

	}

	return;

}
