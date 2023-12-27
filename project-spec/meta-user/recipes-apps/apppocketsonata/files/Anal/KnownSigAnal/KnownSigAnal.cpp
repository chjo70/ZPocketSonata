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
CKnownSigAnal::CKnownSigAnal(unsigned int uiCoMaxPdw, bool bDBThread, const char *pFileName, const char *pThreadName ) : CSigAnal(uiCoMaxPdw, bDBThread, pFileName, pThreadName )
{

    SetAnalType( enTRK_ANAL );

    m_uiMaxPdw = uiCoMaxPdw;

    float *pFvalue = g_pTheSysConfig->GetMargin();
    m_fFixedFreqMargin = pFvalue[0];
    m_fStableMargin = pFvalue[1];

    AllocMemory();

    // 하부 클래스 데이터 포인터 연결
	m_pSeg = GetPulseSeg();
	m_pGrPdwIndex = GetFrqAoaGroupedPdwIndex();

    Init();

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKnownSigAnal::~CKnownSigAnal
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-06-24 15:38:44
//
CKnownSigAnal::~CKnownSigAnal()
{
	_SAFE_DELETE( m_theGroup )
	_SAFE_DELETE( m_thePulExt )
	_SAFE_DELETE( m_theAnalPRI )
	_SAFE_DELETE( m_theMakeAET )

}

/**
 * @brief     AllocMemory
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-10-20 09:39:41
 * @warning
 */
void CKnownSigAnal::AllocMemory()
{
    m_pSEnvironVariable = GlobalMemberFunction::GetEnvrionVariable();

    m_theGroup = new CKGroup( this, m_uiMaxPdw, GetThreadName() );
    m_thePulExt = new CKPulExt( this, m_uiMaxPdw, GetThreadName() );
    m_theAnalPRI = new CKAnalPRI( this, m_uiMaxPdw, GetThreadName() );

    // 추적 개수 제한
    unsigned int uiCoMaxLOB = g_pTheSysConfig->GetMaxCountOfLOB();
    m_theMakeAET = new CKMakeAET( this, uiCoMaxLOB, GetThreadName() );

}

/////////////////////////////////////////////////////////////////////////
/*! \brief    CKnownSigAnal::Start
    \author   조철희
    \param    pPdwBank 인자형태 STR_PDWBANK *
    \param    pKwnAet 인자형태 STR_MANAET *
    \return   void
    \version  0.0.29
    \date     2008-07-10 12:43:16
    \warning
*/
void CKnownSigAnal::Start( STR_STATIC_PDWDATA *pstPDWData, SRxABTData *pTrkAet, ENUM_ROBUST_ANAL enRobustAnal, unsigned int uiGlobalCh, bool bDBInsert )
{
    struct timespec nowTime;
    CCommonUtils::GetCollectTime( &nowTime );

    char buffer[200];

    PrintFunction

	// 추적할 에미터를 복사한다.
    m_pTrkAet = pTrkAet;

    NextStep();

	// 신호 분석 관련 초기화.
    Init( pstPDWData );

    sprintf( buffer, "---------------- 추적 분석 시작[%dth, PDWID: %d, AET/ABT:%04d/%04d, 채널: %d, 수집 개수:%d/%d]", GetStep(), GetPDWID(), pTrkAet->uiAETID, pTrkAet->uiABTID, uiGlobalCh, m_uiCoPDW, m_uiColPDW );
    CCommonUtils::WallMakePrint( buffer, '-' );
    Log( enNormal, "%s", buffer );

    InsertRAWData( & m_stSavePDWData, _spZero, (int) -1, bDBInsert );

	// 펄스열 인덱스를 참조하여 행렬 값에 저장한다.
	_PDW *pPDW = pstPDWData->stPDW;
	unsigned int uiBand = (unsigned int) pstPDWData->GetBand();
    m_theGroup->MakePDWArray( pPDW, m_uiCoPDW, uiBand );

    // 수집한 PDW 파일 만들기...
    //m_pMidasBlue->SaveRawDataFile( SHARED_DATA_DIRECTORY, E_EL_SCDT_PDW, pPDWData );

	///////////////////////////////////////////////////////////////////////////////////
	// 추적 분석 시작
	StartOfTrackSignalAnalysis( bDBInsert, enRobustAnal );

	///////////////////////////////////////////////////////////////////////////////////
    // 잔여 펄스열에 대해서 탐지 신호 분석을 수행한다.
	StartOfNewSignalAnalysis( bDBInsert );

#if defined(_POCKETSONATA_) || defined(_712_)
#elif defined(_ELINT) || defined(_XBAND_)
#else
//         // 추적 에미터와 새로운 에미터와 상관성을 확인하여 추적 에미터 여부를 결정한다.
//         m_theMakeAET->MakeUpAET();
//
//         // 그룹화된 펄스열 저장하기
//         SaveGroupPdwFile();
//
//         // 수집 개수 초기화
//         // 에미터 전송 전에 수집 버퍼 초기화를 한다.
//         ClearColBuffer();
//
//         SendAllAet();
#endif

    sprintf( buffer, "---------------- 추적 분석 종료[%s] : %d[ns]", CSigAnal::GetRawDataFilename(), ( int ) ( ( CCommonUtils::GetDiffTime( &nowTime ) ) ) );
    CCommonUtils::WallMakePrint( buffer, '=' );
    Log( enNormal, "%s", buffer );

}

/**
 * @brief     StartOfTrackSignalAnalysis
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-02-05 14:28:49
 * @warning
 */
void CKnownSigAnal::StartOfTrackSignalAnalysis( bool bDBInsert, ENUM_ROBUST_ANAL enRobustAnal )
{
	bool bRet;

	// 그룹화 만들기
	// 기존에 추출 기능을 그대로 이용하기 위한 초기 설정함.
	m_theGroup->MakeKnownGroup();

	// 그룹화 만들기
	if (TRUE == m_theGroup->MakeGrIndex()) {
		// 펄스열 추출
		m_thePulExt->KnownPulseExtract();

		// PRI 분석
		m_theAnalPRI->KnownAnalysis( enRobustAnal );

		// 에미터 분석
		bRet = m_theMakeAET->KnownMakeAET( bDBInsert );

		// 추적 실패하면 마킹된 정보를 해지한다.
		if (bRet == FALSE) {
			memset(MARK, 0, sizeof(MARK));
		}
	}

// 	int iIdxUpdAet = m_theMakeAET->GetIdxUpdAet();
// 	if (iIdxUpdAet >= 0) {
//         //CLogMsg::Log(enNormal, "#### 추적 - 탐지 분석 시작[%dth, Co:%d] ####", GetStep(), m_uiCoPdw - m_theMakeAET->GetPulseCountFromKnownIndex((UINT)iIdxUpdAet));
// 	}
// 	else {
//         //CLogMsg::Log(enError, "에러 발생");
// 	}


}

/**
 * @brief     잔여 펄스들에 대해서 신규 신호를 분석한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-02-02 16:01:33
 * @warning
 */
void CKnownSigAnal::StartOfNewSignalAnalysis( bool bDBInsert )
{

	// 펄스열 추출 초기화
	m_thePulExt->CPulExt::Init();

	// PRI 분석 초기화
	m_theAnalPRI->CAnalPRI::Init();

	// AET 생성 초기화
	//m_theMakeAET->CMakeAET::Init();

	// 탐지 신호 분석을 그대로 분석한다.
	if (TRUE == m_theGroup->MakeGroup()) {
		CheckKnownByAnalysis();

		// 그룹화 만들기
		while (!m_theGroup->IsLastGroup() )
        {
			// 협대역 주파수 그룹화
			// 방위/주파수 그룹화에서 결정한 주파수 및 방위 범위에 대해서 필터링해서 PDW 데이터를 정한다.
			m_theGroup->MakeGrIndex();

			SaveGroupPDWFile(m_pGrPdwIndex, &m_stSavePDWData, GetPLOBIndex(), true);

			// 규칙성 및 불규칙성 펄스열 추출
			m_thePulExt->PulseExtract(&m_VecMatchRadarMode);

			// 나머지 잔여 펄스들은 Unknown 펄스열 추출에 저장한다.
			// m_thePulExt->UnknownExtract();

			// 하나의 그룹화에서 분석이 끝나면 다시 초기화를 한다.
			memset(&MARK, 0, sizeof(MARK));

			// PRI 분석
			m_theAnalPRI->Analysis();

			// 에미터 분석
			m_theMakeAET->MakeAET( bDBInsert );

			// 그룹화 생성 개수 증가
			++m_CoGroup;

		}

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
#elif defined(_POCKETSONATA_) || defined(_712_)

#elif defined(_ELINT) || defined(_XBAND_)
#else
    m_pPdwBank-> = 0;
#endif

}

/**
 * @brief     Init
 * @param     STR_STATIC_PDWDATA * pstPDWData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2005-06-24 16:03:22
 * @warning
 */
void CKnownSigAnal::Init( STR_STATIC_PDWDATA *pstPDWData )
{

    m_CoGroup = 0;

    // 시간 초기화
    CSigAnal::SetColTime(_spZero);
    CSigAnal::SetColTimeMs(_spZero);

	// 추적은 실패로 초기화 한다.
	m_CoUpdAet = 0;
	m_CoNewAet = 0;

	// 수집 버퍼 정의
    m_pstPDWData = pstPDWData;

	// 신호 수집 개수 정의
    if( pstPDWData != NULL ) {
		MakeAnalDirectory( &pstPDWData->x, false );
        MakeDebugDirectory( &pstPDWData->x, false );

        m_uiColPDW = m_pstPDWData->GetTotalPDW();

        memcpy( & m_stSavePDWData.x, & pstPDWData->x, sizeof( UNION_HEADER) );
        memcpy( m_stSavePDWData.pstPDW, & pstPDWData->stPDW[0], sizeof( _PDW ) * m_uiColPDW );

        // PDW 데이터로부터 정보를 신규 분석을 하기 위해 저장한다.
        SetPDWID( m_pstPDWData->GetPDWID());
        SetColTime( ( time_t ) m_pstPDWData->GetColTime() );

        CSigAnal::SetColTime( m_pstPDWData->GetColTime() );

#if defined(_ELINT_)
        CSigAnal::SetStorePDW( m_pstPDWData->x.el.uiIsStorePDW );

        SetBandWidth(m_pstPDWData->x.el.enBandWidth);
        SetTaskID(m_pstPDWData->x.el.aucTaskID);
        SetCollectorID(m_pstPDWData->x.el.GetCollectorID());

#elif defined(_XBAND_)
        CSigAnal::SetStorePDW( m_pstPDWData->x.xb.uiIsStorePDW );

        SetBandWidth(m_pstPDWData->x.xb.enBandWidth);
        SetTaskID(m_pstPDWData->x.xb.aucTaskID);
        SetCollectorID(m_pstPDWData->x.xb.GetCollectorID());

#elif defined(_SONATA_)
        CSigAnal::SetStorePDW( m_pstPDWData->x.so.uiIsStorePDW );

#else
#endif

        CheckValidData( pstPDWData );

    }
    else {
        // m_CoPdw = _spZero;

    }

    InitOfKnownSigAnal();

}

/**
 * @brief     InitOfKnownSigAnal
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-10-20 09:16:41
 * @warning
 */
void CKnownSigAnal::InitOfKnownSigAnal()
{
    // 단위 초기화
    CSigAnal::InitResolution();

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

#if defined(_POCKETSONATA_) || defined(_712_)
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
 * @brief     CheckKnownByAnalysis
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-27, 16:23
 * @warning
 */
bool CKnownSigAnal::CheckKnownByAnalysis()
{
    UINT i;
    UINT uiFreqMax, uiFreqMin;
    bool bRet;

    m_VecMatchRadarMode.clear();

    if (m_theGroup->GetPulseStat() == STAT_CW) {
        bRet = false;

        // DeletePointers(m_VecMatchRadarMode);
    }
    else {
        uiFreqMax = 0;
        uiFreqMin = UINT_MAX;
        for (i = 0; i < m_uiCoPDW; ++i) {
            uiFreqMax = max(FREQ[i], uiFreqMax);
            uiFreqMin = min(FREQ[i], uiFreqMin);
        }

        bRet = false;
        // bRet = m_pIdentifyAlg->IsThereFreqRange(&m_VecMatchRadarMode, uiFreqMin, uiFreqMax);
    }

    return bRet;
}

/**
 * @brief     GetPLOBIndex
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-07 13:12:45
 * @warning
 */
int CKnownSigAnal::GetPLOBIndex()
{
    int iPLOBIndex;
    int iCoFrqAoaPwIdx = (int) m_theGroup->GetCoFrqAoaPwIdx();

    iPLOBIndex = - ( iCoFrqAoaPwIdx + 1 );
    return iPLOBIndex;
}

/**
 * @brief     SaveDebug
 * @param     char * pSourcefile
 * @param     char * piLines
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-06 13:45:34
 * @warning
 */
void CKnownSigAnal::SaveDebug( const char *pSourcefile, int iLines )
{

}

/**
 * @brief     CheckValidData
 * @param     STR_STATIC_PDWDATA * pPDWData
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-10-19 20:28:17
 * @warning
 */
bool CKnownSigAnal::CheckValidData( STR_STATIC_PDWDATA *pPDWData )
{
    bool bRet = true;

#if defined(_XBAND_)
    if( pPDWData->x.xb.aucTaskID[0] == 0 ) {
        Log( enError, "PDW 데이터에 과제 정보가 없습니다. !!" );
        bRet = false;
    }

    if( !( pPDWData->x.xb.GetCollectorID() >= RADARCOL_1 && pPDWData->x.xb.GetCollectorID() <= RADARCOL_3 ) ) {
        Log( enError, "수집소 ID[%d]가 잘못됐습니다.", pPDWData->x.el.GetCollectorID() );
        bRet = false;
    }

#elif defined(_ELINT_)
    if( ( pPDWData->x.el.enBandWidth != ELINT::en5MHZ_BW && pPDWData->x.el.enBandWidth != ELINT::en50MHZ_BW ) ) {
        Log( enError, "수집 대역폭[%d]은 0 또는 1이 어야 합니다!!", pPDWData->x.el.enBandWidth );
        bRet = false;
    }
#elif defined(_POCKETSONATA_) || defined(_712_)

    // TOA 정렬하기 - 답이 없네... 그냥 코딩
    SortingTOAOfPDW( pPDWData );


#else

#endif

    m_uiCoPDW = pPDWData->GetTotalPDW();

    return bRet;
}
