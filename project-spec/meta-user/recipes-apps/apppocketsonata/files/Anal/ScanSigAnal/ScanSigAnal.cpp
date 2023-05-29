// ScanSigAnal.cpp: implementation of the CScanSigAnal class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#ifdef _MSC_VER

#else
#include <unistd.h>

#endif


#include <stdio.h>
#include <string.h>

#include "../OFP_Main.h"

#include "ScanSigAnal.h"

#include "../../System/csysconfig.h"

#include "../../Include/globals.h"

#include "../../Utils/ccommonutils.h"

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CScanSigAnal::CScanSigAnal
// 함 수 인 자  : int coMaxPdw
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-27 10:41:42
//
CScanSigAnal::CScanSigAnal(unsigned int uiCoMaxPdw, bool bDBThread, const char *pFileName) : CSigAnal(uiCoMaxPdw, bDBThread, pFileName)
{

	InitVar();

	// 신호 분석 관련 클래스 생성
	m_theGroup = new CSGroup( this, uiCoMaxPdw);
	m_thePulExt = new CSPulExt( this, uiCoMaxPdw);

	// 스캔 분석 관련 클래스 생성
    m_theAnalScan = new CSAnalScan( this, uiCoMaxPdw);

	m_uiMaxPdw = uiCoMaxPdw;

	//-- 조철희 2006-02-17 15:23:06 --//
	m_uiNoCh = _spZero;
	m_uiCoPdw = _spZero;
	m_uinoEMT = _spZero;

	m_pSeg = GetPulseSeg();

	m_pGrPdwIndex = GetFrqAoaGroupedPdwIndex();

}

/**
 * @brief     스캔 분석 객체를 소멸 처리합니다.
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-02-13 17:27:56
 * @warning
 */
CScanSigAnal::~CScanSigAnal()
{

	delete m_theGroup;
	delete m_thePulExt;

	delete m_theAnalScan;
}

/**
 * @brief     스캔 분석을 시작합니다.
 * @param     STR_STATIC_PDWDATA * pPDWData
 * @param     SRxABTData * pScnAet
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2009-01-05 13:41:21
 * @warning
 */
void CScanSigAnal::Start( STR_STATIC_PDWDATA *pPDWData, SRxABTData *pScnAet )
{
    unsigned int uiTotalPDW;
    char buffer[200];

    // 추적할 에미터를 복사한다.
    m_pScnAet = pScnAet;

    NextStep();

    // 신호 분석 관련 초기화.
    Init( pPDWData );

    sprintf( buffer, "==== 스캔 분석 시작[%dth, Co:%d]", GetStep(), m_uiCoPdw );
    CCommonUtils::WallMakePrint( buffer, '=' );
    Log( enNormal, buffer );

    uiTotalPDW = pPDWData->GetTotalPDW();

    // 펄스열 인덱스를 참조하여 행렬 값에 저장한다.
    m_theGroup->MakePDWArray( m_pstPDWData->stPDW, uiTotalPDW);

    /*! \bug  그룹화는 생략하고 수집 펄스열을 하나의 그룹화 내에 올려 놓는다.
        \date 2009-03-03 17:05:22, 조철희
    */
    m_theGroup->MakeOneGroup();

    SaveGroupPDWFile( m_pGrPdwIndex, pPDWData, -1, true );

    // 펄스열 추출
    m_thePulExt->KnownPulseExtract();

    // PRI 분석
    m_theAnalScan->KnownAnalysis();

	// 스캔 분석 수행한다.
    //m_strScnResult.uiABTID = m_pScnAet->uiABTID;
    //m_strScnResult.uiAETID = m_pScnAet->uiAETID;
	EN_SCANRESULT enResult = m_theAnalScan->AnalScan();
	m_strScnResult.enResult = enResult;
    GetScanRes( & m_strScnResult.uiScanType, & m_strScnResult.fScanPeriod );

	// 스캔 분석 결과를 저장한다.
    //SaveScanInfo( nResult, m_pScnAet );

    sprintf( buffer, "================ 스캔 분석 종료 : [%s(%d)] %.2f[ms]", g_szAetScanType[m_strScnResult.uiScanType], m_strScnResult.uiScanType, m_strScnResult.fScanPeriod );
    CCommonUtils::WallMakePrint( buffer, '=' );
    Log( enNormal, buffer );

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CScanSigAnal::SendScanResult
// 반환되는 형  : void
// 함 수 인 자  : UINT nResult
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-02-16 11:42:38
//
void CScanSigAnal::SendScanResult( UINT nResult )
{

#ifdef _WIN321
	STR_TSK_MSG tskMsg;

	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CAdvSigAnalView *pView = ( CAdvSigAnalView * ) pFrame->GetActiveView();

	int nScnTyp, nScnPrd;
	GetScanRes( & nScnTyp, & nScnPrd );
	stScnAet[m_uinoEMT].aet.as.iType = nScnTyp;
	stScnAet[m_uinoEMT].aet.as.iPrd = nScnPrd;

	if( nResult == _spAnalSuc )
		stScnAet[m_uinoEMT].aet.as.iStat = SELF_SUCCESS;

 	pView->UpdateScanInfoFromSAP( & stScnAet[m_uinoEMT] );

	switch( nResult ) {
		case _spAnalSuc :
			printf( "\n Anal Sucess noEMT[%d], ScnTyp[%d], ScnPrd[%d ms]" , m_uinoEMT, nScnTyp, UDIV( nScnPrd, _spOneMilli ) );

   		SetScanAnalStep( m_uinoEMT, _spScnEnd );

			//////////////////////////////////////////////////////////////////////////
			// Qpost( SQ_MngScn, sndMsg ); 를 모의

			// 수집 버퍼 초기화
			ClearColBuffer();

			//CloseScanWindowCell( tskMsg.in.opData+1, tskMsg.in.stat1, _spTrue );

			tskMsg.in.opCode = MaetScan;
			tskMsg.in.opData = m_uinoEMT - 1;
			tskMsg.in.stat1 = _spRsaScn;
			ReqScanAnal( tskMsg );

			//////////////////////////////////////////////////////////////////////////
			// Qpost( SQ_SndPrc, tskMsg ); 를 모의


    CASE _spModWc :
			printf( "\n Anal Fail(ColCtl) of noEMT[%d]" , m_uinoEMT );

   		SetScanAnalStep( m_uinoEMT, _spSetWinC );

	}


#else


#endif
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CScanSigAnal::GetCoScanPulse
// 반환되는 형  : UINT
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-02-15 14:11:19
//
UINT CScanSigAnal::GetCoScanPulse()
{
	return stScanPt.uiCount;
}
//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CScanSigAnal::ClearColBuffer
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-02-17 15:18:27
//

void CScanSigAnal::ClearColBuffer()
{

	// if( m_noCh <= SAF_noCell )
	// stSPDW[m_noCh].count = 0;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CScanSigAnal::MarkToPdwIndex
// 반환되는 형  : void
// 함 수 인 자  : PDWINDEX *pPdwIndex
// 함 수 인 자  : int count
// 함 수 인 자  : int mark_type
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-27 14:07:35
//
void CScanSigAnal::MarkToPdwIndex(PDWINDEX *pPdwIndex, unsigned int uiCount, USHORT usMarkType)
{
	for( unsigned int i=0 ; i < uiCount; ++i ) {
		MARK[ *pPdwIndex++ ] = usMarkType;
}
}

/**
 * @brief     멤버 변수를 초기화한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2008-10-25 16:00:06
 * @warning
 */
void CScanSigAnal::InitVar()
{
    // m_uiStep = 0;
}

/**
 * @brief     스캔 분석을 초기화한다.
 * @param     STR_STATIC_PDWDATA * pstPDWData
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-02-13 17:30:08
 * @warning
 */
void CScanSigAnal::Init( STR_STATIC_PDWDATA *pstPDWData)
{
	// 스캔 신호 분석 초기화
//	ScanSigAnalInit( stScnAet.aet.noEMT, 0 );

    // 시간 초기화
    SetColTime(0);
    SetColTimeMs(0);

    // 수집 버퍼 정의
    m_pstPDWData = pstPDWData;

    // 신호 수집 개수 정의
    if (pstPDWData != NULL) {
		MakeAnalDirectory( &pstPDWData->x, false );

        memcpy(&m_stSavePDWData.x, &pstPDWData->x, sizeof(UNION_HEADER));

        // PDW 데이터로부터 정보를 신규 분석을 하기 위해 저장한다.
        SetPDWID(m_pstPDWData->GetPDWID());
		SetColTime( m_pstPDWData->GetColTime() );
		SetStorePDW( m_pstPDWData->GetStorePDW() );
		// SetBandWidth( m_pstPDWData->GetBandWidth() );

        // 신호 수집 개수 정의
        m_uiCoPdw = pstPDWData->GetTotalPDW();

    }
    else {
        SetPDWID(_spZero);

        m_uiCoPdw = _spZero;

        SetStorePDW( _spZero );

    }

	// 그룹화 초기화
	m_theGroup->Init();

	// 펄스열 추출 초기화
	m_thePulExt->Init();

    // 펄스열 초기화
    m_theAnalScan->Init();

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CScanSigAnal::ScanExtractPulseInit
// 반환되는 형  : void
// 함 수 인 자  : int noEMT
// 함 수 인 자  : int noCh
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-27 10:32:42
//
void CScanSigAnal::ScanExtractPulseInit( unsigned int uinoEMT, unsigned int uinoCh )
{
	// 스캔분석판 추적 채널 정의
	m_uiNoCh = uinoCh;

	// PDW 버퍼 정의
// 	m_pPdwBank = & stSPDW;

	// 신호 수집 개수 정의
    m_uiCoPdw = 100; // m_pPdwBank->count;

	// stScnAet의 인덱스 저장
	m_uinoEMT = uinoEMT;

	// 그룹화 초기화
	m_theGroup->Init();

	// 펄스열 추출 초기화
	m_thePulExt->Init();

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CScanSigAnal::ScanSigAnalInit
// 반환되는 형  : void
// 함 수 인 자  : int noCh
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-02-13 17:22:40
//
void CScanSigAnal::ScanSigAnalInit( unsigned int uinoEMT, int noCh )
{
	m_theAnalScan->Init(uinoEMT, noCh );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : *CScanSigAnal::GetScanPulseTrain
// 반환되는 형  : STR_SCANPT
// 함 수 인 자  : int noCh
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-02-16 11:02:31
//
STR_SCANPT *CScanSigAnal::GetScanPulseTrain( int noCh )
{
	// return m_theAnalScan->GetScanPulseTrain( noCh );
	return NULL;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CScanSigAnal::GetScanRes
// 반환되는 형  : void
// 함 수 인 자  : int *pScanType
// 함 수 인 자  : int *pScanPrd
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-02-16 11:02:34
//
void CScanSigAnal::GetScanRes( unsigned int *pScanType, float *pScanPrd )
{
    UINT uiScnPrd;

    m_theAnalScan->GetScanRes( pScanType, & uiScnPrd );

    *pScanPrd = TOAmsCNV( uiScnPrd );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CScanSigAnal::SaveEmitterPdwFile
// 반환되는 형  : void
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 인 자  : int index
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-27 14:37:39
//
void CScanSigAnal::SaveEmitterPDWFile( STR_EMITTER *pEmitter, int iPLOBID, bool bSaveFile )
{

#ifdef _WIN321
	int i;
	int total_count;
	FILE *pdwfile;
	TNEW_PDW *pPDW;
	PDWINDEX *pPdwIndex;
	PDWINDEX *pEmitterPdwIndex;

	char filename[100];

	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CAdvSigAnalView *pView = ( CAdvSigAnalView * ) pFrame->GetActiveView();

	CString strFilename=pView->GetFileTitle();

	LPTSTR p = strFilename.GetBuffer( 100 );

	pPdwIndex = & m_pGrPdwIndex->pIndex[0];
	sprintf( filename, "c:\\temp\\%s_emitter_%02d_ksp.pdw", p, index );
	pdwfile = fopen( filename, "wb" );

	total_count = pEmitter->stPDW.uiCount;

	pEmitterPdwIndex = pEmitter->stPDW.pIndex;
	for( i=0 ; i < total_count ; ++i ) {
		pPDW = & m_pPdwBank->pPdw[ *pEmitterPdwIndex++ ];
		fwrite( pPDW, sizeof( TNEW_PDW ), 1, pdwfile );
	}

	fclose( pdwfile );

	strFilename.ReleaseBuffer();

#endif

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CScanSigAnal::SaveScanInfo
		\author   조철희
		\param    nResult 인자형태 UINT
		\param    pUpdAet 인자형태 STR_UPDAET *
		\param    bOnlyScanThreat 인자형태 bool
		\return   void
		\version  0.0.51
		\date     2008-10-11 15:18:42
		\warning
*/
void CScanSigAnal::SaveScanInfo( UINT nResult, STR_UPDAET *pUpdAet, bool bOnlyScanThreat )
{
//	switch( nResult ) {
//		case _spAnalSuc :
//			// 분석할 스캔 형태가 Steady, Conical이면 이 결과만 저장할 수 있도록 함.
//			if( bOnlyScanThreat == TRUE ) {
//				int scanType, scanPrd;

//				m_theAnalScan->GetScanRes( & scanType, & scanPrd );
//				// 섹터형이면 결과를 버리게 함.
//				if( scanType == CIRCULAR ) {
//					pUpdAet->aet.as.stat = SELF_FAIL;
//					break;
//				}
//			}

//			pUpdAet->aet.as.stat = SELF_SUCCESS;
//			m_theAnalScan->GetScanRes( & pUpdAet->aet.as.type, & pUpdAet->aet.as.prd );
//			// SaveEmitterPDWFile( & m_pSeg[m_pEmitter->main_seg].pdw, 0 );
//			break;

//		default :
//			pUpdAet->aet.as.stat = SELF_FAIL;
//			break;

//	}

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CScanSigAnal::IsAnalScan
		\author   조철희
		\return   bool
		\version  0.0.51
		\date     2008-10-11 15:46:59
		\warning
*/
//bool CScanSigAnal::IsAnalScan()
//{
//	STR_AS *pAetAs;

//	// 수집 개수 체크

//	// 스캔 결과 체크
//	pAetAs = & m_pUpdAet->aet.as;
//	if( pAetAs->stat == SELF_SUCCESS ) {
//		if( pAetAs->type == STEADY )
//			return FALSE;
//	}

//	return TRUE;

//}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CScanSigAnal::SaveEmitterPDWFile
		\author   조철희
		\param    pPdw 인자형태 STR_PDWINDEX *
		\param    index 인자형태 int
		\return   void
		\version  0.0.53
		\date     2008-11-03 22:49:58
		\warning
*/
void CScanSigAnal::SaveEmitterPDWFile( STR_PDWINDEX *pPdw, int iPLOBID )
{
#ifdef _DEBUG_MAKEPDW
	int i;
	int total_count;
	FILE *pdwfile;
	TNEW_PDW *pPDW;
	PDWINDEX *pPdwIndex;
	PDWINDEX *pEmitterPdwIndex;

	char filename[100];

	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CA50SigAnalView *pView = ( CA50SigAnalView * ) pFrame->GetActiveView();

	CString strFilename=pView->GetFileTitle();

	LPTSTR p = strFilename.GetBuffer( 100 );

	pPdwIndex = & m_pGrPdwIndex->pIndex[0];
	int nStep = theSigAnal->m_theNewSigAnal->GetCoStep();
	sprintf( filename, "c:\\temp\\%03d_%03d_%s.scn_emt.pdw", nStep, index, p );
	pdwfile = fopen( filename, "wb" );

	total_count = pPdw->uiCount;

	pEmitterPdwIndex = pPdw->pIndex;
	for( i=0 ; i < total_count ; ++i ) {
		pPDW = & m_pPdwBank->pPdw[ *pEmitterPdwIndex++ ];
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


