// NewSigAnal.cpp: implementation of the CNewSigAnal class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#ifdef _MSC_VER

#else
#include <unistd.h>

#endif


#ifdef _USRDLL

#else

#endif

#include <sys/types.h>
#include <sys/stat.h>


#include "../OFP_Main.h"

#include <string.h>

#include "NewSigAnal.h"

#include "../../System/csysconfig.h"

#include "../../Include/globals.h"

#include "../../Utils/ccommonutils.h"

#ifdef _POCKETSONATA_
char g_szCollectBank[4][10] = { "탐지", "추적", "스캔", "사용자" } ;

#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#ifdef _MSSQL_
CNewSigAnal::CNewSigAnal( int coMaxPdw, bool bDBThread ) : CMSSQL( & m_theMyODBC )
#else
CNewSigAnal::CNewSigAnal( int coMaxPdw, bool bDBThread )
#endif
{
    //printf( "\n +++++++++++++++++++++++++++++ CNewSigAnal 시작 +++++++++++++++++++++++++++++ " );

    m_bDBThread = bDBThread;

    srand( time(NULL) & 0xFFFF );

    // MSSQL 연결
#ifdef _SQLITE_
    // SQLITE 파일명 생성하기
    char szSQLiteFileName[100];

    strcpy( szSQLiteFileName, CEDEOB_SQLITE_FOLDER );
    strcat( szSQLiteFileName, "/" );
    strcat( szSQLiteFileName, CEDEOB_SQLITE_FILENAME );  

    m_pIdentifyAlg = new CELSignalIdentifyAlg( szSQLiteFileName );

    m_pszSQLString = ( char *) malloc( MAX_SQL_SIZE );
#elif _MSSQL_
    CMSSQL::Init();
    m_pIdentifyAlg = new CELSignalIdentifyAlg( & m_theMyODBC );

    m_pszSQLString = ( char *) malloc( MAX_SQL_SIZE );

#else
    m_pIdentifyAlg = new CELSignalIdentifyAlg( NULL );
#endif

    m_bSaveFile = true;

    m_VecMatchRadarMode.reserve( MAX_MATCH_RADARMODE );

    m_theGroup = new CNGroup( this, coMaxPdw );
    m_thePulExt = new CNPulExt( this, coMaxPdw );
    m_theAnalPRI = new CNAnalPRI( this, coMaxPdw );
    m_theMakeAET = new CNMakeAET( this, coMaxPdw );

    m_pMidasBlue = new CMIDASBlueFileFormat;

    // 클래스 관련 초기화
    m_nMaxPdw = coMaxPdw;

    m_pGrPdwIndex = GetFrqAoaGroupedPdwIndex();
    m_pSeg = GetPulseSeg();

    m_CoPdw = 0;

    m_uiStep = 0;

    Init();

    // DB 관련 변수 초기화
    InitDataFromDB();

    //SWInit();

}

/**
 * @brief CNewSigAnal::~CNewSigAnal
 */
CNewSigAnal::~CNewSigAnal()
{
    _SAFE_DELETE( g_pTheELEnvironVariable );

    _SAFE_DELETE( m_pIdentifyAlg );
    _SAFE_DELETE( m_pMidasBlue );

    _SAFE_DELETE( m_theGroup );
    _SAFE_DELETE( m_thePulExt );
    _SAFE_DELETE( m_theAnalPRI );
    _SAFE_DELETE( m_theMakeAET );

#if defined(_SQLITE_) || defined(_MSSQL_)
    free( m_pszSQLString );
#endif

}

/**
 * @brief     LoadCEDLibrary
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-09, 10:01
 * @warning
 */
void CNewSigAnal::LoadCEDLibrary()
{
    m_pIdentifyAlg->LoadCEDLibrary2();
}

/**
 * @brief CNewSigAnal::SetSaveFile
 * @param bEnable
 */
void CNewSigAnal::SetSaveFile( bool bEnable )
{
    m_bSaveFile = bEnable;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CNewSigAnal::Init
        \author   조철희
        \param    pPDWData 인자형태 STR_PDWDATA *
        \return   void
        \version  0.0.1
        \date     2008-01-04 09:07:28
        \warning
*/
void CNewSigAnal::Init( STR_PDWDATA *pPDWData )
{

    m_CoGroup = 0;

    // 시간 초기화
    m_tColTime = 0;
    m_tColTimeMs = 0;

    // 신호 수집 개수 정의
    if( pPDWData != NULL ) {
        // PDW 데이터로부터 정보를 신규 분석을 하기 위해 저장한다.
        m_tColTime = pPDWData->tColTime;
        m_enBandWidth = pPDWData->x.el.enBandWidth;

        m_CoPdw = pPDWData->uiTotalPDW;

#if defined(_ELINT_) || defined(_XBAND_)
        memcpy( m_szTaskID, pPDWData->x.el.aucTaskID, sizeof(m_szTaskID) );
        m_iIsStorePDW = pPDWData->x.el.iIsStorePDW;
        m_enCollectorID = ( EN_RADARCOLLECTORID ) pPDWData->x.el.iCollectorID;
#elif _POCKETSONATA_
        m_iIsStorePDW = pPDWData->x.ps.iIsStorePDW;
#else
#endif

    }
    else {
        m_CoPdw = 0;
        m_iIsStorePDW = 0;

        m_enBandWidth = en5MHZ_BW;

#if defined(_ELINT_) || defined(_XBAND_)
        m_enCollectorID = RADARCOL_Unknown;
#else
#endif
    }      

    InitResolution();


    //////////////////////////////////////////////////////////////////////////////////////////
    // 수집 버퍼 정의
    m_pPDWData = pPDWData;

    // 그룹화 초기화
    m_theGroup->CNGroup::Init();

    // 펄스열 추출 초기화
    m_thePulExt->CNPulExt::Init();

    // PRI 분석 초기화
    m_theAnalPRI->CNAnalPRI::Init();

    // AET 생성 초기화
    m_theMakeAET->CNMakeAET::Init();



}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CNewSigAnal::Start
        \author   조철희
        \param    pPDWData 인자형태 STR_PDWDATA *
        \return   void
        \version  0.0.1
        \date     2007-12-28 11:53:42
        \warning
*/
void CNewSigAnal::Start( STR_PDWDATA *pPDWData )
{
    Log( enLineFeed, "" );

    PrintFunction;

    ++ m_uiStep;

    Log( enNormal, "==== Start of New Signal Analysis[%dth, Co:%d] ====" , m_uiStep, pPDWData->uiTotalPDW );

    // 신호 분석 관련 초기화.
    Init( pPDWData );

#ifdef _TESTSBC_
    if( pPDWData->uiTotalPDW <= RPC || pPDWData->uiTotalPDW > MAX_PDW ) {
        Log( enNormal, "A insufficient num of PDWs(%d/%d) !!" , pPDWData->uiTotalPDW, RPC );
    }
    else {
        CheckValidData( pPDWData );

        // 수집한 PDW 파일 저장하기...
        InsertRAWData( pPDWData );

        // PDW 수집 상태 체크를 함.
        if( false == m_theGroup->MakePDWArray( m_pPDWData->stPDW, (int) m_pPDWData->uiTotalPDW ) ) {
#if defined(_ELINT_) || defined(_XBAND_)
            //printf(" \n [W] [%d] 싸이트에서 수집한 과제[%s]의 PDW 파일[%s]의 TOA 가 어긋났습니다. 확인해보세요.." , pPDWData->iCollectorID, pPDWData->aucTaskID, m_szPDWFilename );
            Log( enError, "Invalid of PDW Data at the [%s:%d]Site !! Check the file[%s] ..." , pPDWData->x.el.aucTaskID, pPDWData->x.el.iCollectorID, m_pMidasBlue->GetRawDataFilename() );
#elif _POCKETSONATA_
            printf(" \n [W] [%d] 보드에서 수집한 PDW 파일[%s]의 TOA 가 어긋났습니다. 확인해보세요.." , pPDWData->x.ps.iBoardID, m_pMidasBlue->GetRawDataFilename() );
            Log( enError, "Invalid of PDW Data at the [%d]Site !! Check the file[%s] ..." , pPDWData->x.ps.iBoardID, m_pMidasBlue->GetRawDataFilename() );
#endif
        }
        else {

            // 라이브러리 기반 펄스열 추출
             if( TRUE == m_theGroup->MakeGroup() ) {
                 CheckKnownByAnalysis();
 
                 // 그룹화 만들기
                while( ! m_theGroup->IsLastGroup() ) {
                    // 협대역 주파수 그룹화
                    // 방위/주파수 그룹화에서 결정한 주파수 및 방위 범위에 대해서 필터링해서 PDW 데이터를 정한다.
                    m_theGroup->MakeGrIndex();

                    SaveGroupPdwFile( m_CoGroup+1 );

                    // 규칙성 및 불규칙성 펄스열 추출
                    m_thePulExt->PulseExtract( & m_VecMatchRadarMode );

                    // 나머지 잔여 펄스들은 Unknown 펄스열 추출에 저장한다.
                    // m_thePulExt->UnknownExtract();

                    // 하나의 그룹화에서 분석이 끝나면 다시 초기화를 한다.
                    memset( & MARK, 0, sizeof( MARK ) );

                    // PRI 분석
                    m_theAnalPRI->Analysis();

                    // 에미터 분석
                    m_theMakeAET->MakeAET();

                    // 그룹화 생성 개수 증가
                    ++ m_CoGroup;

                }
            }
        }

        //m_theMakeAET->PrintAllEmitter();

        // Printf( "\n ==== End of New Signal Analysis ====\n" );

        // 분석되지 못한 나머지 펄스열에 대한 파일 저장.
        SaveRemainedPdwFile();
    }

#else
    if( pPDWData->uiTotalPDW <= RPC || pPDWData->uiTotalPDW > MAX_PDW ) {
        Log( enNormal, "A insufficient num of PDWs(%d/%d) !!" , pPDWData->uiTotalPDW, RPC );
    }
    else {
        CheckValidData( pPDWData );

        // 수집한 PDW 파일 저장하기...
        InsertRAWData( pPDWData );

        // PDW 수집 상태 체크를 함.
        if( false == m_theGroup->MakePDWArray( m_pPDWData->stPDW, (int) m_pPDWData->uiTotalPDW ) ) {
#if defined(_ELINT_) || defined(_XBAND_)
            //printf(" \n [W] [%d] 싸이트에서 수집한 과제[%s]의 PDW 파일[%s]의 TOA 가 어긋났습니다. 확인해보세요.." , pPDWData->iCollectorID, pPDWData->aucTaskID, m_szPDWFilename );
            Log( enError, "Invalid of PDW Data at the [%s:%d]Site !! Check the file[%s] ..." , pPDWData->x.el.aucTaskID, pPDWData->x.el.iCollectorID, m_pMidasBlue->GetRawDataFilename() );
#elif _POCKETSONATA_
            printf(" \n [W] [%d] 보드에서 수집한 PDW 파일[%s]의 TOA 가 어긋났습니다. 확인해보세요.." , pPDWData->x.ps.iBoardID, m_pMidasBlue->GetRawDataFilename() );
            Log( enError, "Invalid of PDW Data at the [%d]Site !! Check the file[%s] ..." , pPDWData->x.ps.iBoardID, m_pMidasBlue->GetRawDataFilename() );
#endif
        }
        else {

            // 라이브러리 기반 펄스열 추출
            if( TRUE == m_theGroup->MakeGroup() ) {
                CheckKnownByAnalysis();

                // 그룹화 만들기
                while( ! m_theGroup->IsLastGroup() ) {
                    // 협대역 주파수 그룹화
                    // 방위/주파수 그룹화에서 결정한 주파수 및 방위 범위에 대해서 필터링해서 PDW 데이터를 정한다.
                    m_theGroup->MakeGrIndex();

                    SaveGroupPdwFile( m_CoGroup+1 );

                    // 규칙성 및 불규칙성 펄스열 추출
                    m_thePulExt->PulseExtract( & m_VecMatchRadarMode );

                    // 나머지 잔여 펄스들은 Unknown 펄스열 추출에 저장한다.
                    // m_thePulExt->UnknownExtract();

                    // 하나의 그룹화에서 분석이 끝나면 다시 초기화를 한다.
                    memset( & MARK, 0, sizeof( MARK ) );

                    // PRI 분석
                    m_theAnalPRI->Analysis();

                    // 에미터 분석
                    m_theMakeAET->MakeAET();

                    // 그룹화 생성 개수 증가
                    ++ m_CoGroup;

                }
            }
        }

        //m_theMakeAET->PrintAllEmitter();

        // Printf( "\n ==== End of New Signal Analysis ====\n" );

        // 분석되지 못한 나머지 펄스열에 대한 파일 저장.
        SaveRemainedPdwFile();
    }
#endif

    // DB 인덱스 번호 증가 : 매우 중요
    NextSeqNum();

}

/**
 * @brief CNewSigAnal::CheckValidData
 */
bool CNewSigAnal::CheckValidData( STR_PDWDATA *pPDWData )
{
    bool bRet=true;

#if defined(_ELINT_) || defined(_XBAND_)
    if( pPDWData->x.el.aucTaskID[0] == 0 ) {
        Log( enError, "PDW 데이터에 과제 정보가 없습니다. !!"  );
        bRet = false;
    }

    if( !(pPDWData->x.el.iCollectorID >= RADARCOL_1 && pPDWData->x.el.iCollectorID <= RADARCOL_3) ) {
        Log( enError, "수집소 ID[%d]가 잘못됐습니다." , pPDWData->x.el.iCollectorID );
        bRet = false;
    }

    if( ( pPDWData->x.el.enBandWidth != en5MHZ_BW && pPDWData->x.el.enBandWidth != en50MHZ_BW ) ) {
        Log( enError, "수집 대역폭[%d]은 0 또는 1이 어야 합니다!!" , pPDWData->x.el.enBandWidth );
        bRet = false;
    }
#elif defined(_POCKETSONATA_)

#else

#endif

    return bRet;
}


//////////////////////////////////////////////////////////////////////////
/*! \brief    CNewSigAnal::MarkToPdwIndex
        \author   조철희
        \param    pPdwIndex 인자형태 PDWINDEX *
        \param    count 인자형태 int
        \param    mark_type 인자형태 int
        \return   void
        \version  0.0.1
        \date     2008-01-03 16:40:48
        \warning
*/
void CNewSigAnal::MarkToPdwIndex(PDWINDEX *pPdwIndex, int count, int mark_type)
{
    int i;

    for( i=0 ; i < count ; ++i ) {
        MARK[ *pPdwIndex++ ] = mark_type;
    }

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CNewSigAnal::SaveEmitterPdwFile
        \author   조철희
        \param    pEmitter 인자형태 STR_EMITTER *
        \param    index 인자형태 int
        \return   void
        \version  0.0.1
        \date     2008-01-03 17:15:04
        \warning
*/
void CNewSigAnal::SaveEmitterPdwFile(STR_EMITTER *pEmitter, int index)
{
//     if( m_bSaveFile == true ) {
// 
//#if defined(_ELINT_) || defined(_XBAND_)
//         UINT uiSize;
//         char filename[100];
//         char szDirectory[100];
// 
//         int i;
//         CFile cFile;
//         BOOL bRet;
//         PDWINDEX *pPdwIndex;
//         _PDW *pPDW;
// 
//         STR_PDWDATA stPDWData;
// 
//         sprintf_s( szDirectory, "%s\\수집소_%d\\%s", LOCAL_DATA_DIRECTORY_2, m_pPDWData->x.el.iCollectorID, m_pPDWData->x.el.aucTaskID );
// 
//         bRet = CreateDir( szDirectory );
// 
//         struct tm stTime;
//         char buffer[100];
//         __time32_t tiNow;
// 
//         tiNow = _time32(NULL);
// 
//         _localtime32_s( &stTime, & tiNow );
//         strftime( buffer, 100, "%Y-%m-%d %H_%M_%S", & stTime);
// 
//         if( index > 1000 ) {
//             wsprintf( filename, _T("%s/_COL%d_EMT_DEBUG_%02d.%s"), szDirectory, m_pPDWData->x.el.iCollectorID, index, PDW_EXT );
//         }
//         else {
//             wsprintf( filename, _T("%s/_COL%d_LOB_%02d.%s"), szDirectory, m_pPDWData->x.el.iCollectorID, index, PDW_EXT );
//         }
// 
//         cFile.Open( filename, CFile::modeCreate | CFile::modeReadWrite );
// 
//         uiSize = sizeof( STR_PDWDATA ) - ( MAX_PDW * sizeof(_PDW) );
//         memcpy( & stPDWData, m_pPDWData, uiSize );
//         stPDWData.iIsStorePDW = 0;
//         stPDWData.count = pEmitter->pdw.count;
//         //cFile.Write( m_pPDWData, uiHeaderSize );
// 
//         pPdwIndex = pEmitter->pdw.pIndex;
//         for( i=0 ; i < pEmitter->pdw.count ; ++i ) {
//             pPDW = & m_pPDWData->stPDW[ *pPdwIndex++ ];
//             memcpy( & stPDWData.stPDW[i], pPDW, sizeof(_PDW) );
// 
//         }
// 
//         uiSize = sizeof( STR_PDWDATA ) - ( ( MAX_PDW - stPDWData.count ) * sizeof(_PDW) );
//         cFile.Write( & stPDWData, uiSize );
// 
//         cFile.Close();
// 
// #else
// 
// #ifdef _DEBUG_MAKEPDW_NO
//         int i;
//         // int total_count;
//         FILE *pdwfile;
//         TNEW_PDW *pPDW;
//         PDWINDEX *pPdwIndex;
//         char filename[100];
// 
//         CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
//         CA50SigAnalView *pView = ( CA50SigAnalView * ) pFrame->GetActiveView();
// 
//         CString strFilename=pView->GetFileTitle();
// 
//         LPTSTR p = strFilename.GetBuffer( 100 );
// 
//         sprintf( filename, "c:\\temp\\%03d_%03d_%s.new_emt.pdw", m_nStep, index, p );
//         pdwfile = fopen( filename, "wb" );
// 
//         pPdwIndex = pEmitter->pdw.pIndex;
//         for( i=0 ; i < pEmitter->pdw.count ; ++i ) {
//             pPDW = & m_pPDWData->pPdw[ *pPdwIndex++ ];
// #ifdef _A50_RWR
//             TNEW_PDW pdw;
// 
//             pdw.word[0] = ntohl( pPDW->word[0] );
//             pdw.word[1] = ntohl( pPDW->word[1] );
//             pdw.word[2] = ntohl( pPDW->word[2] );
//             pdw.word[3] = ntohl( pPDW->word[3] );
// 
//             fwrite( & pdw, sizeof( TNEW_PDW ), 1, pdwfile );
// #else
//             fwrite( pPDW, sizeof( TNEW_PDW ), 1, pdwfile );
// #endif
// 
//         }
// 
//         fclose( pdwfile );
// 
//         strFilename.ReleaseBuffer();
// 
// #endif
// 
// #endif
//     }

}

void CNewSigAnal::SaveGroupPdwFile( int index )
{
//     if( m_bSaveFile == true ) {
// #if defined(_ELINT_) || defined(_XBAND_)
//         UINT uiSize;
//         char filename[100];
//         char szDirectory[100];
// 
//         int i;
//         CFile cFile;
//         BOOL bRet;
//         PDWINDEX *pPdwIndex;
//         _PDW *pPDW;
// 
//         STR_PDWDATA stPDWData;
// 
//         sprintf_s( szDirectory, "%s\\수집소_%d\\%s", LOCAL_DATA_DIRECTORY_2, m_pPDWData->x.el.iCollectorID, m_pPDWData->x.el.aucTaskID );
// 
//         bRet = CreateDir( szDirectory );
// 
//         struct tm stTime;
//         char buffer[100];
//         __time32_t tiNow;
// 
//         tiNow = _time32(NULL);
// 
//         _localtime32_s( &stTime, & tiNow );
//         strftime( buffer, 100, "%Y-%m-%d %H_%M_%S", & stTime);
// 
//         wsprintf( filename, _T("%s/_COL%d_GR_%02d.%s"), szDirectory, m_pPDWData->iCollectorID, index, PDW_EXT );
// 
//         cFile.Open( filename, CFile::modeCreate | CFile::modeReadWrite );
// 
//         uiSize = sizeof( STR_PDWDATA ) - ( MAX_PDW * sizeof(_PDW) );
//         memcpy( & stPDWData, m_pPDWData, uiSize );
//         stPDWData.iIsStorePDW = 0;
//         stPDWData.count = m_pGrPdwIndex->count;
// 
//         pPdwIndex = m_pGrPdwIndex->pIndex;
//         for( i=0 ; i < m_pGrPdwIndex->count ; ++i ) {
//             pPDW = & m_pPDWData->stPDW[ *pPdwIndex++ ];
//             memcpy( & stPDWData.stPDW[i], pPDW, sizeof(_PDW) );
// 
//         }
// 
//         uiSize = sizeof( STR_PDWDATA ) - ( ( MAX_PDW - stPDWData.count ) * sizeof(_PDW) );
//         cFile.Write( & stPDWData, uiSize );
// 
//         cFile.Close();
// 
// #else
// 
// #endif
// 
//     }
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CNewSigAnal::InitAllVar
        \author   조철희
        \return   void
        \version  0.0.1
        \date     2008-01-04 09:51:51
        \warning
*/
void CNewSigAnal::InitAllVar()
{
    m_uiStep = 0;

}

/**
 * @brief     InitVar
 * @param     enum ANALYSIS_MODE analMode
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-06, 15:59
 * @warning
 */
void CNewSigAnal::InitVar( enum ANALYSIS_MODE analMode )
{
    m_uiStep = 0;
    m_AnalMode = analMode;

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CNewSigAnal::SaveRemainedPdwFile
        \author   조철희
        \return   void
        \version  0.0.1
        \date     2008-01-22 12:40:25
        \warning
*/
void CNewSigAnal::SaveRemainedPdwFile()
{
#ifdef _DEBUG_MAKEPDW_NO
    CMainFrame *pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
    CA50SigAnalView *pView = ( CA50SigAnalView * ) pFrame->GetActiveView();

    UINT i;
    FILE *pdwfile;
    TNEW_PDW *pPDW;
    char filename[100];

    CString strFilename=pView->GetFileTitle();

    LPTSTR p = strFilename.GetBuffer( 100 );

    m_theMakeAET->MarkAllAetToPdwIndex();

    sprintf( filename, "c:\\temp\\%03d_rem_%s.pdw", m_nStep, p );
    pdwfile = fopen( filename, "wb" );
    for( i=0 ; i < m_pPDWData->count ; ++i ) {
        if( MARK[i] == EXTRACT_MARK )
            continue;

        pPDW = & m_pPDWData->pPdw[ i ];
#ifdef _A50_RWR
        TNEW_PDW pdw;

        pdw.word[0] = ntohl( pPDW->word[0] );
        pdw.word[1] = ntohl( pPDW->word[1] );
        pdw.word[2] = ntohl( pPDW->word[2] );
        pdw.word[3] = ntohl( pPDW->word[3] );

        fwrite( & pdw, sizeof( TNEW_PDW ), 1, pdwfile );
#else
        fwrite( pPDW, sizeof( TNEW_PDW ), 1, pdwfile );
#endif

    }

    fclose( pdwfile );

    strFilename.ReleaseBuffer();

#endif
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CNewSigAnal::GetBand
        \author   조철희
        \param    freq 인자형태 int
        \return   enum FREQ_BAND
        \version  0.1.114
        \date     2009-11-16 11:33:14
        \warning
*/
enum FREQ_BAND CNewSigAnal::GetBand( int freq )
{
    enum FREQ_BAND enBand;

    if( freq >= 2000 && freq < 6000 ) {
        enBand = BAND1;
    }
    else if( freq >= 6000 && freq < 10000 ) {
        enBand = BAND2;
    }
    else if( freq >= 10000 && freq < 14000 ) {
        enBand = BAND3;
    }
    else if( freq >= 14000 && freq <= 19000 ) {
        enBand = BAND4;
    }
    else {
        enBand = BAND5;
    }

    return enBand;

}

/**
 * @brief 위협 라이브러리 기반 신호 분석 플레그를 반환한다.
 * @return
 */
bool CNewSigAnal::CheckKnownByAnalysis()
{
    UINT i;
    UINT uiFreqMax, uiFreqMin;
    bool bRet;

    if( m_theGroup->GetPulseStat() == STAT_CW ) {
        bRet = false;
    }
    else {
        uiFreqMax = 0;
        uiFreqMin = 0x7FFFFFFF;
        for( i=0 ; i < m_pPDWData->uiTotalPDW ; ++i ) {
            uiFreqMax = max( FREQ[i], uiFreqMax );
            uiFreqMin = min( FREQ[i], uiFreqMin );
        }

        bRet = m_pIdentifyAlg->IsThereFreqRange( & m_VecMatchRadarMode, uiFreqMin, uiFreqMax );
    }

    return bRet;
}

/**
 * @brief     GetTaskID
 * @return    char *
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-21, 17:49
 * @warning
 */
char *CNewSigAnal::GetTaskID()
{
#if defined(_ELINT_) || defined(_XBAND_)
    return (char *) & m_szTaskID[0];
#else
    return NULL;

#endif

}


/**
 * @brief     InitResolution
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-06, 15:37
 * @warning
 */
void CNewSigAnal::InitResolution()
{
#if defined(_ELINT_) || defined(_XBAND_)
    //STR_PDWDATA *pPDWData;
    //m_enBandWidth = pPDWData->x.el.enBandWidth;

    _spOneSec = FDIV( 1000000000, _toaRes[m_enBandWidth] );
    _spOneMilli = FDIV( 1000000, _toaRes[m_enBandWidth] );
    _spOneMicrosec = FDIV( 1000, _toaRes[m_enBandWidth] );
    _spOneNanosec = FDIV( 1, _toaRes[m_enBandWidth] );

    _spAOAres = (float) 0.01;
    _spAMPres = (float) (0.25);
    _spPWres = _spOneMicrosec;

#elif defined(_POCKETSONATA_)
    _spOneSec = FDIV( 1000000000, 6.48824007 );
    _spOneMilli = FDIV( 1000000, 6.48824007 );
    _spOneMicrosec = FDIV( 1000, 6.48824007 );
    _spOneNanosec = FDIV( 1, 6.48824007 );

    _spAOAres = (float) ( 0.351562 );
    _spAMPres = (float) (0.351562);
    _spPWres = _spOneMicrosec;

#elif defined(_SONATA_)
    _spOneSec = 20000000.;
    _spOneMilli = FDIV( _spOneSec, 1000. );
    _spOneMicrosec = FDIV( _spOneMilli, 1000. );
    _spOneNanosec = FDIV( _spOneMicrosec, 1000. );

    _spAOAres = (float) ( 0.351562 );
    _spAMPres = (float) (0.351562);
    _spPWres = (float) ( 50 );

#endif
}


/**
 * @brief     InsertRAWData
 * @param     STR_PDWDATA * pPDWData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-01-23, 17:53
 * @warning
 */
void CNewSigAnal::InsertRAWData( STR_PDWDATA *pPDWData )
{
    bool bRet;
    char buffer[100]={0};
    TCHAR szDirectory[500], szRawDataPathname[500];

    struct tm *pstTime;
	struct timespec tiNow;

#ifdef _XBAND_
    Log( enDebug, ".InsertRAWData[S%d]" , m_uiStep );
#else

#endif

    GetCollectTime( & tiNow );
    pstTime = localtime( & tiNow.tv_sec );

    // 1. 폴더명 생성하기
    strftime( buffer, 100, "%Y-%m-%d", pstTime );
#if defined(_ELINT_)
    sprintf_s( szDirectory, "%s\\수집소_%d\\%s", SHARED_DATA_DIRECTORY, pPDWData->x.el.iCollectorID, pPDWData->x.el.aucTaskID );

#elif defined(_XBAND_)
    //sprintf_s( szDirectory, "%s\\수집소_%d\\%s\\%s", SHARED_DATA_DIRECTORY, pPDWData->x.el.iCollectorID, buffer, pPDWData->x.el.aucTaskID );
	sprintf_s( szDirectory, "%s\\수집소_%d\\%s", SHARED_DATA_DIRECTORY, pPDWData->x.el.iCollectorID, pPDWData->x.el.aucTaskID );

#elif _POCKETSONATA_
    sprintf( szDirectory, _T("%s/%s/BRD_%d/%s"), SHARED_DATA_DIRECTORY, buffer, pPDWData->x.ps.iBoardID, g_szCollectBank[pPDWData->x.ps.iBank] );
#else
    sprintf( szDirectory, "%s/BRD", pLocalDirectory );

#endif

    printf( "\n Create the Dir[%s]" , szDirectory );
    bRet = CreateDir( szDirectory );

    if( bRet == true ) {
        // 2. 파일명 생성하기
        strftime( buffer, 100, "%Y-%m-%d_%H_%M_%S", pstTime );

#if defined(_ELINT_) || defined(_XBAND_)
        sprintf( m_szRawDataFilename, _T("%d_%s_%010d.%s"), pPDWData->x.el.iCollectorID, buffer, m_uiStep, PDW_EXT );
        sprintf( szRawDataPathname, _T("%s\\%s"), szDirectory, m_szRawDataFilename );

#elif _POCKETSONATA_
        sprintf( m_szRawDataFilename, _T("%d_%s_%010d.%s.%s"), pPDWData->x.ps.iBoardID, buffer, m_uiStep, PDW_TYPE, MIDAS_EXT );
        sprintf( szRawDataPathname, "%s/%s", szDirectory, m_szRawDataFilename );
//         if( enDataType == E_EL_SCDT_PDW ) {
//             sprintf( szRawDataFilename, "%s/%s_COL%d_%s_%06d.%s.%s", szDirectory, g_szCollectBank[pPDWData->x.ps.iBank], pPDWData->x.ps.iBoardID, buffer, m_uiStep, PDW_TYPE, MIDAS_EXT );
//         }
//         else {
//             sprintf( szRawDataFilename, "%s/%s_COL%d_%s_%06d.%s", szDirectory, g_szCollectBank[pPDWData->x.ps.iBank], pPDWData->x.ps.iBoardID, buffer, m_uiStep, PDW_EXT );
//         }
#else

#endif

		if( m_bDBThread == false ) {
			// RAWDATA 데이터 저장
			InsertToDB_RAW( pPDWData ); 
		}
		else {
            TRACE( "Push the data for InsertToDB_RAW()" );
		}

        m_pMidasBlue->SaveRawDataFile( szRawDataPathname, E_EL_SCDT_PDW, pPDWData );

    }

}

/**
 * @brief     
 * @param     STR_PDWDATA * pPDWData
 * @return    bool
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022/01/23 23:33:21
 * @warning   
 */
bool CNewSigAnal::InsertToDB_RAW( STR_PDWDATA *pPDWData )
{

#ifdef _SQLITE_
	//struct tm *pstTime;
	char buffer[100]={0};

	bool bRet=true;
// 	pstTime = localtime( & pLOBData->tiContactTime );
// 	if( pstTime != NULL ) {
// 		printf( "\n %d, %d, %d, %d" , m_nSeqNum, pLOBData->uiLOBID, pLOBData->uiABTID, pLOBData->uiAETID );
// 		strftime( buffer, 100, "%Y-%m-%d %H:%M:%S", pstTime);
// 		sprintf( m_pszSQLString, "INSERT INTO LOBDATA ( \
// 								 SEQ_NUM, LOBID, ABTID, AETID, CONTACT_TIME, CONTACT_TIME_MS, PRIMARY_ELNOT, PRIMARY_MODECODE, SECONDARY_ELNOT, SECONDARY_MODECODE, TERTIARY_ELNOT, TERTIARY_MODECODE, MODULATION_CODE, RADARMODE_NAME, NICK_NAME, FUNC_CODE, RADARMODE_INDEX, POLIZATION, RATIOOFPOL, \
// 								 SIGNAL_TYPE, DOA_MEAN, DOA_MIN, DOA_MAX, DOA_DEV, DOA_STD, DI_RATIO, \
// 								 FREQ_TYPE, FREQ_PATTERN_TYPE, FREQ_PATTERN_PERIOD, FREQ_MEAN, FREQ_MIN, FREQ_MAX, FREQ_DEV, FREQ_POSITION_COUNT, FREQ_ELEMENT_COUNT, \
// 								 PRI_TYPE, PRI_PATTERN_TYPE, PRI_PATTERN_PERIOD, PRI_MEAN, PRI_MIN, PRI_MAX, PRI_DEV, PRI_JITTER_RATIO, PRI_POSITION_COUNT, PRI_ELEMENT_COUNT, \
// 								 PW_MEAN, PW_MIN, PW_MAX, PW_DEV, \
// 								 PA_MEAN, PA_MIN, PA_MAX, PA_DEV, \
// 								 SCAN_TYPE, SCAN_PRD, \
// 								 INTRA_TYPE, INTRA_TYPE_DETAIL, INTRA_FRQ_MEAN, INTRA_FRQ_MIN, INTRA_FRQ_MAX, INTRA_FRQ_DEVIATION, \
// 								 SHIP_LAT, SHIP_LONG, SHIP_PITCH, SHIP_ROLL, SHIP_HEADING, SHIP_ALT, IS_VALIDITY, \
// 								 IS_DATA_STORE, IS_FILTERED, NUM_PDW, NUM_IQ ) VALUES \
// 								 ( %d, %d, %d, %d, \"%s\", %d, \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", %d, %d, %d, \
// 								 %d, %f, %f, %f, %f, %f, %d, \
// 								 %d, %d, %f, %f, %f, %f, %f, %d, %d, \
// 								 %d, %d, %f, %f, %f, %f, %f, %f, %d, %d, \
// 								 %f, %f, %f, %f, \
// 								 %f, %f, %f, %f, \
// 								 %d, %f, \
// 								 %d, %d, %f, %f, %f, %f, \
// 								 %f, %f, %f, %f, %f, %f, %d, \
// 								 %d, %d, %d, %d )" , \
// 								 m_nSeqNum, pLOBData->uiLOBID, pLOBData->uiABTID, pLOBData->uiAETID, buffer, pLOBData->tiContactTimems, pLOBData->szPrimaryELNOT, pLOBData->szPrimaryModeCode, pLOBData->szSecondaryELNOT, pLOBData->szSecondaryModeCode, pLOBData->szTertiaryELNOT, pLOBData->szTertiaryModeCode, pLOBData->szModulationCode, pLOBData->szRadarModeName, pLOBData->szNickName, pLOBData->szFuncCode, pLOBData->iRadarModeIndex, pLOBData->iPolarization, pLOBData->iRatioOfPOL, \
// 								 pLOBData->iSignalType, pLOBData->fDOAMean, pLOBData->fDOAMin, pLOBData->fDOAMax, pLOBData->fDOADeviation, pLOBData->fDOASDeviation, pLOBData->iDIRatio, \
// 								 pLOBData->iFreqType, pLOBData->iFreqPatternType, pLOBData->fFreqPatternPeriod, pLOBData->fFreqMean, pLOBData->fFreqMin, pLOBData->fFreqMax, pLOBData->fFreqDeviation, pLOBData->iFreqPositionCount, pLOBData->iFreqElementCount, \
// 								 pLOBData->iPRIType, pLOBData->iPRIPatternType, pLOBData->fPRIPatternPeriod, pLOBData->fPRIMean, pLOBData->fPRIMin, pLOBData->fPRIMax, pLOBData->fPRIDeviation, pLOBData->fPRIJitterRatio, pLOBData->iPRIPositionCount, pLOBData->iPRIElementCount, \
// 								 pLOBData->fPWMean, pLOBData->fPWMin, pLOBData->fPWMax, pLOBData->fPWDeviation, \
// 								 pLOBData->fPAMean, pLOBData->fPAMin, pLOBData->fPAMax, pLOBData->fPWDeviation, \
// 								 pLOBData->iScanType, pLOBData->fScanPeriod, \
// 								 pLOBData->iMOPType, pLOBData->iDetailMOPType, pLOBData->fMOPMaxFreq, pLOBData->fMOPMinFreq, pLOBData->fMOPMeanFreq, pLOBData->fMOPFreqDeviation, \
// 								 pLOBData->fShipLatitude, pLOBData->fShipLongitude, pLOBData->fPitchAngle, pLOBData->fRollAngle, pLOBData->fHeadingAngle, pLOBData->fAltitude, pLOBData->iValidity, \
// 								 pLOBData->iIsStoreData, pExt->aetAnal.isFiltered, pLOBData->iNumOfPDW, pLOBData->iNumOfIQ );
// 
// 		try {
// 			//LOGMSG1( enNormal, " m_pszSQLString[%s]" , m_pszSQLString );
// 
// 			Kompex::SQLiteStatement stmt( m_pDatabase );
// 			stmt.SqlStatement( m_pszSQLString );
// 
// 			// do not forget to clean-up
// 			stmt.FreeQuery();  
//         
// 			if( bUpdateRadarMode == true && pLOBData->iRadarModeIndex > 0 ) {
// 				m_pIdentifyAlg->UpdateRadarMode( pLOBData );
// 			}
// 
//     }
// 		catch( Kompex::SQLiteException &exception ) {
// 			LOGMSG1( enNormal, " m_pszSQLString[%s]" , m_pszSQLString );
// 			bRet = false;
// 			std::cerr << "\nException Occured" << std::endl;
// 			exception.Show();
// 			std::cerr << "SQLite result code: " << exception.GetSqliteResultCode() << std::endl;
// 		}
// 	}

	return bRet;

#elif _MSSQL_
	DECLARE_BEGIN_CHECKODBC

	struct tm stTime;
	char buffer[100];

	struct timeval tiNow;

	CODBCRecordset theRS = CODBCRecordset( m_pMyODBC );

	GetCollectTime( & tiNow );

	_localtime32_s( &stTime, & tiNow.tv_sec );
	strftime( buffer, 100, "%Y-%m-%d %H:%M:%S", & stTime);
  	sprintf_s( m_pszSQLString, MAX_SQL_SIZE, "INSERT INTO RAWDATA ( SEQ_NUM, OP_INIT_ID, PDW_ID, TASK_ID, CREATE_TIME, CREATE_TIME_MS, COUNTOFDATA, FILENAME ) values( \
        '%d', '%ld', '%d', '%s', '%s', '%d', '%d', '%s' )", \
  		m_nSeqNum, m_lOpInitID, m_iPDWID, pPDWData->x.el.aucTaskID, buffer, 0, pPDWData->uiTotalPDW, m_szRawDataFilename );
 
 	theRS.Open( m_pszSQLString );
 
 	theRS.Close();

 	DECLARE_END_CHECKODBC
 	DECLARE_RETURN

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
 * @date      2022-01-25, 16:04
 * @warning
 */
void CNewSigAnal::InitDataFromDB()
{
    
    m_lOpInitID = 0;
    m_nSeqNum = 0;
    m_iPDWID = 0;

#ifdef _MSSQL_

#if defined(_ELINT_) || defined(_XBAND_)
	char buffer[400];

    sprintf_s( buffer, sizeof(buffer), "select max(OP_INIT_ID) from LOBDATA" );
    m_lOpInitID = GetLONGData( buffer ) + 1;

    sprintf_s( buffer, sizeof(buffer), "select max(SEQ_NUM) from RAWDATA" );
    m_nSeqNum = GetINTData( buffer ) + 1;

    sprintf_s( buffer, sizeof(buffer), "select max(PDW_ID) from RAWDATA" );
    m_iPDWID = GetINTData( buffer ) + 1;

#endif

#else


#endif

}

/**
 * @brief     
 * @return    __time32_t
 * @author    議곗쿋??(churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022/01/26 21:22:00
 * @warning   
 */
void CNewSigAnal::GetCollectTime( struct timespec *pTimeSpec )
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