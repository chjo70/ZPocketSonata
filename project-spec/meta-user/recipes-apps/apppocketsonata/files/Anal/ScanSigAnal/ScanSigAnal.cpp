// ScanSigAnal.cpp: implementation of the CScanSigAnal class.
//
//////////////////////////////////////////////////////////////////////

// PC용 상위 클래스에 전달하기 위한 선언
#ifdef _MSC_VER
#include "../../A50SigAnal/stdafx.h"
#include "../../A50SigAnal/A50SigAnal.h"

#include "../../A50SigAnal/MainFrm.h"
#include "../../A50SigAnal/A50SigAnalDoc.h"
#include "../../A50SigAnal/A50SigAnalView.h"
#endif

#include <stdio.h>
#include <string.h>

#include "ScanSigAnal.h"

// CSColPdw *theSAPColPdw;
CScanSigAnal *theScanSigAnal;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : GetScanRes
// 반환되는 형  : void
// 함 수 인 자  : int *pScanType
// 함 수 인 자  : int *pScanPrd
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-16 11:00:59
//
void GetScanRes( unsigned int *pScanType, float *pScanPrd )
{
	theScanSigAnal->GetScanRes( pScanType, pScanPrd );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : ExtPul
// 반환되는 형  : UINT
// 함 수 인 자  : int noEMT
// 함 수 인 자  : UINT noCh
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-13 16:53:19
//
UINT ExtPul( int noEMT, UINT noCh ) {

	printf( "\n **************************************************************************" );

	// 변수 초기화
	theScanSigAnal->ScanExtractPulseInit( noEMT, noCh );

	// 펄스열 추출
    //theScanSigAnal->ExtractPulse();
	int count=theScanSigAnal->GetCoScanPulse();
	printf( "\n 스캔 펄스열 추출: %3d 번, %2d 채널, %d 개" , noEMT, noCh, count );

	printf( "\n **************************************************************************" );
	printf( "\n" );
	return count;

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : ScanSigAnal
// 반환되는 형  : int
// 함 수 인 자  : int noEMT
// 함 수 인 자  : int noCh
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-15 16:01:18
//
int ScanSigAnal( int noEMT, int noCh ) {

	printf( "\n **************************************************************************" );

	// 변수 초기화
	theScanSigAnal->ScanSigAnalInit( noEMT, noCh );

	printf( "\n 스캔 분석 시작: %3d 번, %2d 채널, %d 개" , noEMT, noCh, theScanSigAnal->GetCoScanPulse() );

	// 스캔 분석
    //int nResult=theScanSigAnal->AnalStart( noEMT, noCh );

	printf( "\n **************************************************************************" );
	printf( "\n" );

    return 0;

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CScanSigAnal::CScanSigAnal
// 함 수 인 자  : int coMaxPdw
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-27 10:41:42
//
CScanSigAnal::CScanSigAnal( int coMaxPdw )
{
	InitVar();

	// 신호 분석 관련 클래스 생성
	m_theGroup = new CSGroup( this, coMaxPdw );
	m_thePulExt = new CSPulExt( this, coMaxPdw );

	// 스캔 분석 관련 클래스 생성
    m_theAnalScan = new CSAnalScan( this, coMaxPdw );

	if( m_theGroup == NULL || m_thePulExt == NULL || m_theAnalScan == NULL ) {
		printf( "\n 메모리가 부족 합니다." );
		printf( "\n sap.def 에서 heap size를 늘려주세요." );
		printf( "\n m_theGroup:: this[%p]" , m_theGroup );
		printf( "\n m_thePulExt:: this[%p]" , m_thePulExt );
		printf( "\n m_theAnalScan:: this[%p]" , m_theAnalScan );
	}

	m_nMaxPdw = coMaxPdw;

	//-- 조철희 2006-02-17 15:23:06 --//
	m_noCh = 0;
	m_CoPdw = 0;
	m_noEMT = 0;

	m_pSeg = GetPulseSeg();

	m_pGrPdwIndex = GetFrqAoaGroupedPdwIndex();

    m_pMidasBlue = new CMIDASBlueFileFormat;

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CScanSigAnal::~CScanSigAnal
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-13 17:27:56
//
CScanSigAnal::~CScanSigAnal()
{
    delete m_pMidasBlue;

	delete m_theGroup;
	delete m_thePulExt;

	delete m_theAnalScan;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CScanSigAnal::AnalStart
// 반환되는 형  : UINT
// 함 수 인 자  : int noEMT
// 함 수 인 자  : int noCh
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-15 16:01:33
//
//UINT CScanSigAnal::AnalStart( int noEMT, int noCh )
//{
//    UINT nResult=0;

//    if( stScnAet.aet.noEMT == _spInvAET || stScnAet.aet.noEMT > _spMaxEMTNum ) {
//        printf( "\n\t Invalid Scan AET[%d] !" , noEMT );
//        WhereIs;
//        return (UINT) _spWarning;
//    }

//    nResult = m_theAnalScan->AnalScan();

//    SendScanResult( nResult );

//	return nResult;

//}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CScanSigAnal::Start
		\author   조철희
		\param    pPdwBank 인자형태 STR_PDWBANK *
		\param    pManAet 인자형태 STR_MANAET *
		\return   void
		\version  0.0.68
		\date     2009-01-05 13:41:21
		\warning
*/
void CScanSigAnal::Start( STR_PDWDATA *pPDWData, SRxABTData *pScnAet )
{
    // 추적할 에미터를 복사한다.
    m_pScnAet = pScnAet;

    ++ m_uiStep;

    // 신호 분석 관련 초기화.
    Init( pPDWData );

    // 펄스열 인덱스를 참조하여 행렬 값에 저장한다.
    m_theGroup->MakePDWArray( m_pPDWData->stPDW, (int) m_pPDWData->uiTotalPDW );

    // 수집한 PDW 파일 만들기...
    m_pMidasBlue->SaveRawDataFile( SHARED_DATA_DIRECTORY, E_EL_SCDT_PDW, pPDWData, m_uiStep );

    /*! \bug  그룹화는 생략하고 수집 펄스열을 하나의 그룹화 내에 올려 놓는다.
        \date 2009-03-03 17:05:22, 조철희
    */
    m_theGroup->MakeOneGroup();

    // 펄스열 추출
    m_thePulExt->KnownPulseExtract();

    // PRI 분석
    m_theAnalScan->KnownAnalysis();

	// 스캔 분석 수행한다.
    m_strScnResult.uiABTID = m_pScnAet->uiABTID;
    m_strScnResult.uiAETID = m_pScnAet->uiAETID;
    m_strScnResult.uiResult = (UINT) m_theAnalScan->AnalScan();
    GetScanRes( & m_strScnResult.uiScnTyp, & m_strScnResult.fScnPrd );

	// 스캔 분석 결과를 저장한다.
    //SaveScanInfo( nResult, m_pScnAet );

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CScanSigAnal::Start
		\author   조철희
		\param    pPdwBank 인자형태 STR_PDWBANK *
		\param    pUpdAet 인자형태 STR_UPDAET *
		\return   void
		\version  0.0.51
		\date     2008-10-11 12:39:03
		\warning
*/
//void CScanSigAnal::Start( STR_PDWBANK *pPdwBank, STR_UPDAET *pUpdAet )
//{
//	UINT nResult;

//	// 펄스열 및 추적 에미터 포인터, 수집 펄스열 저장
//	m_pUpdAet = pUpdAet;

//	// 스캔 분석 여부를 결정한다.
//	if( ! IsAnalScan() ) {
//		return;
//	}

//	// 스캔분석할 에미터 저장
//	memcpy( & stScnAet, pUpdAet, sizeof( STR_SCNAET ) );

//	// printf( "\n pPdwBank->count[%d]" , pPdwBank->count );
//	if( pPdwBank->count == 0 )
//		return;

//	// 분석 초기화
//	Init( pPdwBank );

//	// 스캔 분석하고자할 펄스열을 추출한다.
//	ExtractPulse();
	
//	// 스캔 분석을 수행한다.
//	nResult = m_theAnalScan->AnalScan();

//	// 스캔 분석 결과를 저장한다.
//	SaveScanInfo( nResult, pUpdAet, TRUE );

//}

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
	stScnAet[m_noEMT].aet.as.type = nScnTyp;
	stScnAet[m_noEMT].aet.as.prd = nScnPrd;

	if( nResult == _spAnalSuc ) 
		stScnAet[m_noEMT].aet.as.stat = SELF_SUCCESS;

 	pView->UpdateScanInfoFromSAP( & stScnAet[m_noEMT] );

	switch( nResult ) {
		case _spAnalSuc :
			printf( "\n Anal Sucess noEMT[%d], ScnTyp[%d], ScnPrd[%d ms]" , m_noEMT, nScnTyp, UDIV( nScnPrd, _spOneMilli ) );

   		SetScanAnalStep( m_noEMT, _spScnEnd );

			//////////////////////////////////////////////////////////////////////////
			// Qpost( SQ_MngScn, sndMsg ); 를 모의

			// 수집 버퍼 초기화
			ClearColBuffer();

			//CloseScanWindowCell( tskMsg.in.opData+1, tskMsg.in.stat1, _spTrue );

			tskMsg.in.opCode = MaetScan;
			tskMsg.in.opData = m_noEMT - 1;
			tskMsg.in.stat1 = _spRsaScn;
			ReqScanAnal( tskMsg );

			//////////////////////////////////////////////////////////////////////////
			// Qpost( SQ_SndPrc, tskMsg ); 를 모의
			

    CASE _spModWc :
			printf( "\n Anal Fail(ColCtl) of noEMT[%d]" , m_noEMT );

   		SetScanAnalStep( m_noEMT, _spSetWinC );

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
	return stScanPt.co;
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
void CScanSigAnal::MarkToPdwIndex(PDWINDEX *pPdwIndex, int count, int mark_type)
{
	for( int i=0 ; i < count ; ++i )
		MARK[ *pPdwIndex++ ] = mark_type;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CScanSigAnal::InitVar
		\author   조철희
		\return   void
		\version  0.0.52
		\date     2008-10-25 16:00:06
		\warning
*/
void CScanSigAnal::InitVar()
{
    m_uiStep = 0;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CScanSigAnal::Init
		\author   조철희
		\param    pPdwBank 인자형태 STR_PDWBANK *
		\return   void
		\version  0.0.73
		\date     2006-02-13 17:30:08
		\warning
*/
void CScanSigAnal::Init( STR_PDWDATA *pPDWData )
{
	// 스캔 신호 분석 초기화
//	ScanSigAnalInit( stScnAet.aet.noEMT, 0 );

    // 수집 버퍼 저장
    m_pPDWData = pPDWData;

    // 신호 수집 개수 정의
    m_CoPdw = pPDWData->uiTotalPDW;

    m_iIsStorePDW = pPDWData->x.ps.iIsStorePDW;

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
void CScanSigAnal::ScanExtractPulseInit( int noEMT, int noCh )
{
	// 스캔분석판 추적 채널 정의
	m_noCh = noCh;

	// PDW 버퍼 정의
// 	m_pPdwBank = & stSPDW;

	// 신호 수집 개수 정의
    m_CoPdw = 100; // m_pPdwBank->count;

	// stScnAet의 인덱스 저장
	m_noEMT = noEMT;

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
void CScanSigAnal::ScanSigAnalInit( int noEMT, int noCh )
{
	m_theAnalScan->Init( noEMT, noCh );
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
void CScanSigAnal::SaveEmitterPdwFile( STR_EMITTER *pEmitter, int index )
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

	total_count = pEmitter->pdw.count;

	pEmitterPdwIndex = pEmitter->pdw.pIndex;
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
		\param    bOnlyScanThreat 인자형태 BOOL
		\return   void
		\version  0.0.51
		\date     2008-10-11 15:18:42
		\warning
*/
void CScanSigAnal::SaveScanInfo( UINT nResult, STR_UPDAET *pUpdAet, BOOL bOnlyScanThreat )
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
//			// SaveEmitterPdwFile( & m_pSeg[m_pEmitter->main_seg].pdw, 0 );
//			break;

//		default :
//			pUpdAet->aet.as.stat = SELF_FAIL;
//			break;

//	}

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CScanSigAnal::IsAnalScan
		\author   조철희
		\return   BOOL
		\version  0.0.51
		\date     2008-10-11 15:46:59
		\warning
*/
//BOOL CScanSigAnal::IsAnalScan()
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
/*! \brief    CScanSigAnal::SaveEmitterPdwFile
		\author   조철희
		\param    pPdw 인자형태 STR_PDWINDEX *
		\param    index 인자형태 int
		\return   void
		\version  0.0.53
		\date     2008-11-03 22:49:58
		\warning
*/
void CScanSigAnal::SaveEmitterPdwFile( STR_PDWINDEX *pPdw, int index )
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

	total_count = pPdw->count;

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
