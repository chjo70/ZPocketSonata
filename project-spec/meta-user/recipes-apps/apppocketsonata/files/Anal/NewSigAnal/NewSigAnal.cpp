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

#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "../OFP_Main.h"

#include "NewSigAnal.h"

#include "../../System/csysconfig.h"

#include "../../Include/globals.h"

#include "../../Utils/ccommonutils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CNewSigAnal::CNewSigAnal(unsigned int uiCoMaxPdw, bool bDBThread, const char *pFileName ) : CSigAnal(uiCoMaxPdw, bDBThread, pFileName )
{
    //printf( "\n +++++++++++++++++++++++++++++ CNewSigAnal 시작 +++++++++++++++++++++++++++++ " );


#ifdef _SQLITE_
    // SQLITE 파일명 생성하기
    char szSQLiteFileName[100];

    strcpy( szSQLiteFileName, CEDEOB_SQLITE_FOLDER );
    strcat( szSQLiteFileName, "/" );
    strcat( szSQLiteFileName, CEDEOB_SQLITE_FILENAME );  

    m_pIdentifyAlg = new CELSignalIdentifyAlg( szSQLiteFileName );

#elif _MSSQL_
    CODBCDatabase *pMyODBC;
    pMyODBC = GetCODBCDatabase();
    m_pIdentifyAlg = new CELSignalIdentifyAlg(pMyODBC);

#else
    m_pIdentifyAlg = new CELSignalIdentifyAlg( NULL );

#endif

    m_VecMatchRadarMode.reserve( MAX_MATCH_RADARMODE );

    m_theGroup = new CNGroup( this, uiCoMaxPdw);
    m_thePulExt = new CNPulExt( this, uiCoMaxPdw);
    m_theAnalPRI = new CNAnalPRI( this, uiCoMaxPdw);
    m_theMakeAET = new CNMakeAET( this, uiCoMaxPdw);    

    // 클래스 관련 초기화
    m_uiMaxPdw = uiCoMaxPdw;

    m_pGrPdwIndex = GetFrqAoaGroupedPdwIndex();
    m_pSeg = GetPulseSeg();

    m_uiCoPdw = _spZero;

    Init();

}

/**
 * @brief CNewSigAnal::~CNewSigAnal
 */
CNewSigAnal::~CNewSigAnal()
{
    _SAFE_DELETE( g_pTheELEnvironVariable )

    _SAFE_DELETE( m_pIdentifyAlg )
    
    _SAFE_DELETE( m_theGroup )
    _SAFE_DELETE( m_thePulExt )
    _SAFE_DELETE( m_theAnalPRI )
    _SAFE_DELETE( m_theMakeAET )

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
    m_pIdentifyAlg->LoadCEDLibrary();
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
    SetColTime(0);
    SetColTimeMs(0);

    // 신호 수집 개수 정의
    if( pPDWData != NULL ) {
        memcpy( & m_stSavePDWData.x, & pPDWData->x, sizeof(UNION_HEADER) );

        // PDW 데이터로부터 정보를 신규 분석을 하기 위해 저장한다.
		SetPDWID(pPDWData->GetPDWID());

        m_uiCoPdw = pPDWData->GetTotalPDW();

        SetColTime(pPDWData->GetColTime());

        SetStorePDW( pPDWData->GetStorePDW() );

#if defined(_ELINT_)
        SetBandWidth(pPDWData->x.el.enBandWidth );
        SetTaskID( pPDWData->x.el.aucTaskID);        
        SetCollectorID( pPDWData->x.el.GetCollectorID() );

#elif defined(_XBAND_)
        SetBandWidth(pPDWData->x.xb.enBandWidth);
        SetTaskID(pPDWData->x.xb.aucTaskID);
        SetCollectorID(pPDWData->x.xb.GetCollectorID());

#elif _POCKETSONATA_
        

#else
#endif

    }
    else {
		SetPDWID(_spZero);

        m_uiCoPdw = 0;
        SetStorePDW(_spZero);

#if defined(_ELINT_) || defined(_XBAND_)
#ifdef _ELINT_
        SetBandWidth( ELINT::en5MHZ_BW );
#else
        SetBandWidth( XBAND::en5MHZ_BW );
#endif

        SetCollectorID(RADARCOL_Unknown);
#else
#endif
    }      

    CSigAnal::InitResolution();

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
    DWORD dwTime = CCommonUtils::GetTickCount();

    Log( enLineFeed, "" );

    PrintFunction

    NextStep();

    // 신호 분석 관련 초기화.
    Init( pPDWData );

    Log( enNormal, "==== 탐지 분석 시작[%dth, Co:%d] ====" , GetStep(), m_uiCoPdw );

    if( m_uiCoPdw <= RPC /* || m_uiCoPdw > MAX_PDW */ ) {
        Log( enNormal, "PDW(%d/%d) 데이터 개수가 모자랍니다 !!" , m_uiCoPdw, RPC );
    }
    else {
        CheckValidData( pPDWData );

        // 수집한 PDW 파일 저장하기...
        InsertRAWData( pPDWData, _spZero );
        
        // PDW 수집 상태 체크를 함.
        if( false == m_theGroup->MakePDWArray( m_pPDWData->pstPDW, (int) m_uiCoPdw, m_pPDWData->GetBand() ) ) {
#if defined(_ELINT_) || defined(_XBAND_)
            //printf(" \n [W] [%d] 싸이트에서 수집한 과제[%s]의 PDW 파일[%s]의 TOA 가 어긋났습니다. 확인해보세요.." , pPDWData->iCollectorID, pPDWData->aucTaskID, m_szPDWFilename );
            Log( enError, "Invalid of PDW Data at the [%s:%d]Site !! Check the file[%s] ..." , pPDWData->GetTaskID(), pPDWData->GetCollectorID(), m_pMidasBlue->GetRawDataFilename() );
#elif defined(_POCKETSONATA_)
            printf(" \n [W] [%d] 보드에서 수집한 PDW 파일[%s]의 TOA 가 어긋났습니다. 확인해보세요.." , pPDWData->x.ps.uiBoardID, m_pMidasBlue->GetRawDataFilename() );
            Log( enError, "Invalid of PDW Data at the [%d]Site !! Check the file[%s] ..." , pPDWData->x.ps.uiBoardID, m_pMidasBlue->GetRawDataFilename() );
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
        // 분석되지 못한 나머지 펄스열에 대한 파일 저장.
        SaveRemainedPdwFile();

    }

    Log(enNormal, "================ 탐지 분석 종료[%s] : %d[ms] =================" , CSigAnal::GetRawDataFilename(), (int)((CCommonUtils::GetTickCount() - dwTime)) );

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

    if( !(pPDWData->x.el.GetCollectorID() >= RADARCOL_1 && pPDWData->x.el.GetCollectorID() <= RADARCOL_3) ) {
        Log( enError, "수집소 ID[%d]가 잘못됐습니다." , pPDWData->x.el.GetCollectorID() );
        bRet = false;
    }

#ifdef _ELINT_
    if( ( pPDWData->x.el.enBandWidth != ELINT::en5MHZ_BW && pPDWData->x.el.enBandWidth != ELINT::en50MHZ_BW ) ) {
        Log( enError, "수집 대역폭[%d]은 0 또는 1이 어야 합니다!!" , pPDWData->x.el.enBandWidth );
        bRet = false;
    }
#else
    if ((pPDWData->x.el.enBandWidth != XBAND::en5MHZ_BW && pPDWData->x.el.enBandWidth != XBAND::en120MHZ_BW)) {
        Log(enError, "수집 대역폭[%d]은 0 또는 1이 어야 합니다!!", pPDWData->x.el.enBandWidth);
        bRet = false;
    }
#endif


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
void CNewSigAnal::MarkToPdwIndex(PDWINDEX *pPdwIndex, unsigned int uiCount, USHORT usMarkType)
{
    unsigned int i;

    for( i=0 ; i < uiCount ; ++i ) {
        MARK[ *pPdwIndex++ ] = usMarkType;
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
    m_AnalMode = analMode;

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
 * @brief     위협 라이브러리 기반 신호 분석 플레그를 반환한다.
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-15, 12:51
 * @warning
 */
bool CNewSigAnal::CheckKnownByAnalysis()
{
    UINT i;
    UINT uiFreqMax, uiFreqMin;
    bool bRet;

    if( m_theGroup->GetPulseStat() == STAT_CW ) {
        bRet = false;

        DeletePointers( m_VecMatchRadarMode );
    }
    else {
        uiFreqMax = 0;
        uiFreqMin = 0x7FFFFFFF;
        for( i=0 ; i < m_uiCoPdw ; ++i ) {
            uiFreqMax = max( FREQ[i], uiFreqMax );
            uiFreqMin = min( FREQ[i], uiFreqMin );
        }

        bRet = m_pIdentifyAlg->IsThereFreqRange( & m_VecMatchRadarMode, uiFreqMin, uiFreqMax );
    }

    return bRet;
}

