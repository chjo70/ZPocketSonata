// NewSigAnal.cpp: implementation of the CNewSigAnal class.
//
//////////////////////////////////////////////////////////////////////

#include "../SigAnal/stdafx.h"

#ifdef _USRDLL

#else
//#include "MainFrm.h"
//#include "ELINTOPDoc.h"
//#include "ELINTOPDoc.h"

#endif

#define _MAIN_

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#include "../OFP_Main.h"

#include <string.h>

#include "NewSigAnal.h"

#include "../../System/csysconfig.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNewSigAnal::CNewSigAnal( int coMaxPdw ) // : CMSSQL( & m_theMyODBC )
{
    //printf( "\n +++++++++++++++++++++++++++++ CNewSigAnal 시작 +++++++++++++++++++++++++++++ " );

    srand( (UINT) time(NULL) );

    // MSSQL 연결
    //CMSSQL::Init();

    m_bSaveFile = true;

    m_theGroup = new CNGroup( this, coMaxPdw );
    m_thePulExt = new CNPulExt( this, coMaxPdw );
    m_theAnalPRI = new CNAnalPRI( this, coMaxPdw );
    m_theMakeAET = new CNMakeAET( this, coMaxPdw );

    // 클래스 관련 초기화
    m_nMaxPdw = coMaxPdw;

    m_pGrPdwIndex = GetFrqAoaGroupedPdwIndex();
    m_pSeg = GetPulseSeg();

    m_CoPdw = 0;

    // 그룹화 초기화
    m_theGroup->CNGroup::Init();

    // 펄스열 추출 초기화
    m_thePulExt->CNPulExt::Init();

    // PRI 분석 초기화
    m_theAnalPRI->CNAnalPRI::Init();

    // AET 생성 초기화
    m_theMakeAET->CNMakeAET::Init();

    m_pMidasBlue = new CMIDASBlueFileFormat;

    //SWInit();

}

/**
 * @brief CNewSigAnal::~CNewSigAnal
 */
CNewSigAnal::~CNewSigAnal()
{
    delete m_pMidasBlue;

    delete m_theGroup;
    delete m_thePulExt;
    delete m_theAnalPRI;
    delete m_theMakeAET;

}

/**
 * @brief CNewSigAnal::Init
 */
void CNewSigAnal::Init()
{
    // m_AnalMode = analMode;
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

    _InitResolution();


    m_CoGroup = 0;

    m_iIsStorePDW = pPDWData->x.ps.iIsStorePDW;

#ifdef _ELINT_
    m_enCollectorID = ( EN_RADARCOLLECTORID ) pPDWData->iCollectorID;
#else
#endif

    // 수집 버퍼 정의
    m_pPDWData = pPDWData;

    // 신호 수집 개수 정의
    if( pPDWData != NULL ) {
        m_CoPdw = m_pPDWData->uiTotalPDW;
    }
    else {
        m_CoPdw = 0;
    }

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

#ifdef _ELINT_
    Printf( "\n\n ==== Start of New Signal Analysis[%dth, Co:%d] ====" , m_nStep, pPDWData->count );
    Log( enNormal, "==== Start of New Signal Analysis[%dth, Co:%d] ====" , m_nStep, pPDWData->count );
#else
    //Printf( "\n\n ==== Start of New Signal Analysis[%dth Band:%d, Co:%d] ====" , m_nStep, pPDWData->stPDW[0].item.band, pPDWData->count );
#endif

    ++ m_uiStep;

    // 신호 분석 관련 초기화.
    Init( pPDWData );

    if( pPDWData->uiTotalPDW <= RPC || pPDWData->uiTotalPDW > MAX_PDW ) {
        //Printf( "PDW 개수(%d)가 %d 이하 이거나 너무 초과되어 분석을 수행하지 않습니다. !!" , pPDWData->count, RPC );
        Log( enNormal, "PDW 개수(%d)가 %d 이하 이거나 너무 초과되어 분석을 수행하지 않습니다. !!" , pPDWData->uiTotalPDW, RPC );
        return;
    }

    CheckValidData( pPDWData );

    // 수집한 PDW 파일 만들기...
    m_pMidasBlue->SaveRawDataFile( SHARED_DATA_DIRECTORY, E_EL_SCDT_PDW, pPDWData, m_uiStep );

    if( pPDWData->x.ps.iIsStorePDW == 1 || true ) {
        // PDW 수집 상태 체크를 함.
        if( false == m_theGroup->MakePDWArray( m_pPDWData->stPDW, (int) m_pPDWData->uiTotalPDW ) ) {
#ifdef _ELINT
            printf(" \n [W] [%d] 싸이트에서 수집한 과제[%s]의 PDW 파일[%s]의 TOA 가 어긋났습니다. 확인해보세요.." , pPDWData->iCollectorID, pPDWData->aucTaskID, m_szPDWFilename );
            Log( enError, "[%d] 싸이트에서 수집한 과제[%s]의 PDW 파일[%s]의 TOA 가 어긋났습니다. 확인해보세요.." , pPDWData->iCollectorID, pPDWData->aucTaskID, m_szPDWFilename );
#else
            printf(" \n [W] [%d] 보드에서 수집한 PDW 파일[%s]의 TOA 가 어긋났습니다. 확인해보세요.." , pPDWData->x.ps.iBoardID, m_pMidasBlue->GetRawDataFilename() );
            Log( enError, "[%d] 보드에서 수집한 PDW 파일[%s]의 TOA 가 어긋났습니다. 확인해보세요.." , pPDWData->x.ps.iBoardID, m_pMidasBlue->GetRawDataFilename() );
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
                    m_thePulExt->PulseExtract( m_uiCoKnownRadarMode, & m_pRadarMode[0] );

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

        m_theMakeAET->PrintAllEmitter();

        // Printf( "\n ==== End of New Signal Analysis ====\n" );

        // 분석되지 못한 나머지 펄스열에 대한 파일 저장.
        SaveRemainedPdwFile();
    }

}

/**
 * @brief CNewSigAnal::CheckValidData
 */
bool CNewSigAnal::CheckValidData( STR_PDWDATA *pPDWData )
{
    bool bRet=true;

#ifdef _ELINT_
    if( pPDWData->aucTaskID[0] == 0 ) {
        Log( enError, "PDW 데이터에 과제 정보가 없습니다. !!"  );
        bRet = false;
    }

    if( !(pPDWData->iCollectorID >= RADARCOL_1 && pPDWData->iCollectorID <= RADARCOL_3) ) {
        Log( enError, "수집소 ID[%d]가 잘못됐습니다." , pPDWData->iCollectorID );
        bRet = false;
    }

    if( ( pPDWData->enBandWidth != en5MHZ_BW && pPDWData->enBandWidth != en50MHZ_BW ) ) {
        Log( enError, "수집 대역폭[%d]은 0 또는 1이 어야 합니다!!" , pPDWData->enBandWidth );
        bRet = false;
    }
#elif defined(_POCKETSONATA_)


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

    for( i=0 ; i < count ; ++i )
        MARK[ *pPdwIndex++ ] = mark_type;
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
    if( m_bSaveFile == true ) {

#ifdef _ELINT_
        UINT uiSize;
        char filename[100];
        char szDirectory[100];

        int i;
        CFile cFile;
        BOOL bRet;
        PDWINDEX *pPdwIndex;
        _PDW *pPDW;

        STR_PDWDATA stPDWData;

        sprintf_s( szDirectory, "%s\\수집소_%d\\%s", LOCAL_DATA_DIRECTORY_2, m_pPDWData->iCollectorID, m_pPDWData->aucTaskID );

        bRet = CreateDir( szDirectory );

        struct tm stTime;
        char buffer[100];
        __time32_t tiNow;

        tiNow = _time32(NULL);

        _localtime32_s( &stTime, & tiNow );
        strftime( buffer, 100, "%Y-%m-%d %H_%M_%S", & stTime);

        if( index > 1000 ) {
            wsprintf( filename, _T("%s/_COL%d_EMT_DEBUG_%02d.%s"), szDirectory, m_pPDWData->iCollectorID, index, PDW_EXT );
        }
        else {
            wsprintf( filename, _T("%s/_COL%d_LOB_%02d.%s"), szDirectory, m_pPDWData->iCollectorID, index, PDW_EXT );
        }

        cFile.Open( filename, CFile::modeCreate | CFile::modeReadWrite );

        uiSize = sizeof( STR_PDWDATA ) - ( MAX_PDW * sizeof(_PDW) );
        memcpy( & stPDWData, m_pPDWData, uiSize );
        stPDWData.iIsStorePDW = 0;
        stPDWData.count = pEmitter->pdw.count;
        //cFile.Write( m_pPDWData, uiHeaderSize );

        pPdwIndex = pEmitter->pdw.pIndex;
        for( i=0 ; i < pEmitter->pdw.count ; ++i ) {
            pPDW = & m_pPDWData->stPDW[ *pPdwIndex++ ];
            memcpy( & stPDWData.stPDW[i], pPDW, sizeof(_PDW) );

        }

        uiSize = sizeof( STR_PDWDATA ) - ( ( MAX_PDW - stPDWData.count ) * sizeof(_PDW) );
        cFile.Write( & stPDWData, uiSize );

        cFile.Close();

#else

#ifdef _DEBUG_MAKEPDW_NO
        int i;
        // int total_count;
        FILE *pdwfile;
        TNEW_PDW *pPDW;
        PDWINDEX *pPdwIndex;
        char filename[100];

        CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
        CA50SigAnalView *pView = ( CA50SigAnalView * ) pFrame->GetActiveView();

        CString strFilename=pView->GetFileTitle();

        LPTSTR p = strFilename.GetBuffer( 100 );

        sprintf( filename, "c:\\temp\\%03d_%03d_%s.new_emt.pdw", m_nStep, index, p );
        pdwfile = fopen( filename, "wb" );

        pPdwIndex = pEmitter->pdw.pIndex;
        for( i=0 ; i < pEmitter->pdw.count ; ++i ) {
            pPDW = & m_pPDWData->pPdw[ *pPdwIndex++ ];
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

#endif
    }

}

void CNewSigAnal::SaveGroupPdwFile( int index )
{
    if( m_bSaveFile == true ) {
#ifdef _ELINT_
        UINT uiSize;
        char filename[100];
        char szDirectory[100];

        int i;
        CFile cFile;
        BOOL bRet;
        PDWINDEX *pPdwIndex;
        _PDW *pPDW;

        STR_PDWDATA stPDWData;

        sprintf_s( szDirectory, "%s\\수집소_%d\\%s", LOCAL_DATA_DIRECTORY_2, m_pPDWData->iCollectorID, m_pPDWData->aucTaskID );

        bRet = CreateDir( szDirectory );

        struct tm stTime;
        char buffer[100];
        __time32_t tiNow;

        tiNow = _time32(NULL);

        _localtime32_s( &stTime, & tiNow );
        strftime( buffer, 100, "%Y-%m-%d %H_%M_%S", & stTime);

        wsprintf( filename, _T("%s/_COL%d_GR_%02d.%s"), szDirectory, m_pPDWData->iCollectorID, index, PDW_EXT );

        cFile.Open( filename, CFile::modeCreate | CFile::modeReadWrite );

        uiSize = sizeof( STR_PDWDATA ) - ( MAX_PDW * sizeof(_PDW) );
        memcpy( & stPDWData, m_pPDWData, uiSize );
        stPDWData.iIsStorePDW = 0;
        stPDWData.count = m_pGrPdwIndex->count;

        pPdwIndex = m_pGrPdwIndex->pIndex;
        for( i=0 ; i < m_pGrPdwIndex->count ; ++i ) {
            pPDW = & m_pPDWData->stPDW[ *pPdwIndex++ ];
            memcpy( & stPDWData.stPDW[i], pPDW, sizeof(_PDW) );

        }

        uiSize = sizeof( STR_PDWDATA ) - ( ( MAX_PDW - stPDWData.count ) * sizeof(_PDW) );
        cFile.Write( & stPDWData, uiSize );

        cFile.Close();

#else

#endif

    }
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
    if( freq >= 2000 && freq < 6000 )
        return BAND1;
    else if( freq >= 6000 && freq < 10000 )
        return BAND2;
    else if( freq >= 10000 && freq < 14000 )
        return BAND3;
    else if( freq >= 14000 && freq <= 19000 )
        return BAND4;
    return BAND5;

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

    m_uiCoKnownRadarMode = 0;
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

        //bRet = m_pIdentifyAlg->IsThereFreqRange( & m_uiCoKnownRadarMode, & m_pRadarMode[0], uiFreqMin, uiFreqMax );
        bRet = false;
    }

    return bRet;
}

char *CNewSigAnal::GetTaskID()
{
    return NULL;
}

