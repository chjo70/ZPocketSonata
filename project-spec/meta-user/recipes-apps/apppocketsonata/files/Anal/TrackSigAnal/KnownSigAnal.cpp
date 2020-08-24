// KnownSigAnal.cpp: implementation of the CKnownSigAnal class.
//
//////////////////////////////////////////////////////////////////////

// PC용 상위 클래스에 전달하기 위한 선언
#ifdef _WIN32
#include "../../AdvSigAnal/stdafx.h"
#include "../../AdvSigAnal/AdvSigAnal.h"

#include "../../AdvSigAnal/MainFrm.h"
#include "../../AdvSigAnal/AdvSigAnalDoc.h"
#include "../../AdvSigAnal/AdvSigAnalView.h"

#endif

#include <stdio.h>
#include <string.h>

#include "KnownSigAnal.h"

CKColPdw *theKSPColPdw;
CKnownSigAnal *theKnownSigAnal;

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CreateKnownSigAnalClass
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-10 18:34:10
//
void CreateKnownSigAnalClass()
{
	theKSPColPdw = new CKColPdw( KSP_MAX_PDW );
	theKnownSigAnal = new CKnownSigAnal( KSP_MAX_PDW );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : DeleteKnownSigAnalClass
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-11 16:53:26
//
void DeleteKnownSigAnalClass()
{
	delete theKSPColPdw;
	delete theKnownSigAnal;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : KnownSigAnal
// 반환되는 형  : int
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-06-24 15:38:31
//
int KnownSigAnal( int noSbc, int noCh ) {

	// 변수 초기화
	theKnownSigAnal->Init( noSbc, noCh );

	printf( "\n **************************************************************************" );
	STR_PDWBANK *pPdwBank=theKnownSigAnal->GetPdwBank();
	printf( "\n 추적 분석 시작: %d 개수" , pPdwBank->count );

	// 추적 분석
	theKnownSigAnal->AnalStart( noSbc, noCh );

	printf( "\n 추적 분석 종료(추적 " );
	if( theKnownSigAnal->m_CoUpdAet == 1 )		printf( "성공, " );
	else																			printf( "실패, " );
	printf( "새 에미터:%d)", theKnownSigAnal->m_CoNewAet );
	printf( "\n **************************************************************************" );
	printf( "\n" );

	return 0;

} 

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
CKnownSigAnal::CKnownSigAnal( int coMaxPdw )
{
	m_theGroup = new CKGroup( this, coMaxPdw );
	m_thePulExt = new CKPulExt( this, coMaxPdw );
	m_theAnalPRI = new CKAnalPRI( this, coMaxPdw );
	m_theMakeAET = new CKMakeAET( this, coMaxPdw );

	if( m_theGroup == NULL || m_thePulExt == NULL || m_theAnalPRI == NULL || m_theMakeAET == NULL ) {
		printf( "\n 메모리가 부족 합니다." );
		printf( "\n ksp.def 에서 heap size를 늘려주세요." );
		printf( "\n m_theGroup:: this[%p]" , m_theGroup );
		printf( "\n m_thePulExt:: this[%p]" , m_thePulExt );
		printf( "\n m_theAnalPRI:: this[%p]" , m_theAnalPRI );
		printf( "\n m_theMakeAET:: this[%p]" , m_theMakeAET );
	}
	
	m_nMaxPdw = coMaxPdw;

	m_pSeg = GetPulseSeg();

	m_pGrPdwIndex = GetFrqAoaGroupedPdwIndex();

	m_CoNewAet = 0;

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
	delete m_theGroup;
	delete m_thePulExt;
	delete m_theAnalPRI;
	delete m_theMakeAET;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKnownSigAnal::AnalStart
// 반환되는 형  : void
// 함 수 인 자  : int noSbc
// 함 수 인 자  : int noCh
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-23 23:56:58
//
//##ModelId=429A5BDA0149
void CKnownSigAnal::AnalStart( int noSbc, int noCh )
{
	BOOL bRet;

	// 펄스열 인덱스를 참조하여 행렬 값에 저장한다.
	m_theGroup->MakePDWArray( m_pPdwBank->pPdw, (int) m_pPdwBank->count );

	// 수집한 PDW 파일 만들기...
	SaveAllPdwFile();

	// 그룹화 만들기
	// 기존에 추출 기능을 그대로 이용하기 위한 초기 설정함.
	m_theGroup->MakeGroup();

	// 그룹화 만들기
	if( FALSE == m_theGroup->MakeGrIndex() )
		return;

	// 펄스열 추출
	m_thePulExt->KnownPulseExtract();

	// PRI 분석
	m_theAnalPRI->KnownAnalysis();

	// 에미터 분석
	bRet = m_theMakeAET->KnownMakeAET();

	//////////////////////////////////////////////////////////////////////////
	printf( "\n **************************************************************************" );
	printf( "\n 새로운 에미터 분석 시작" );

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

	// 추적 에미터와 새로운 에미터와 상관성을 확인하여 추적 에미터 여부를 결정한다.
	m_theMakeAET->MakeUpAET();

	// 그룹화된 펄스열 저장하기
	// SaveGroupPdwFile();

	// 수집 개수 초기화
	// 에미터 전송 전에 수집 버퍼 초기화를 한다.
	ClearColBuffer();

	SendAllAet();

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
#ifndef _WIN32
	m_pPdwBank->count = 0;
#endif
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKnownSigAnal::Init
// 반환되는 형  : void
// 함 수 인 자  : int noSbc
// 함 수 인 자  : int noCh
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-06-24 16:03:22
//
//##ModelId=42D3079B0058
void CKnownSigAnal::Init( int noSbc, int noCh )
{

	// 추적분석판 번호와 추적 채널 정의
	m_noSbc = noSbc;
	m_noCh = noCh;

	// PDW 버퍼 정의
#ifdef _WIN32
	m_pPdwBank = & stKPDW[noSbc][noCh];
#else
	m_pPdwBank = & stKPDW[noCh];
#endif

	// 신호 수집 개수 정의
	m_CoPdw = m_pPdwBank->count;

	// 그룹화 초기화
	m_theGroup->CGroup::Init();

	// 펄스열 추출 초기화
	m_thePulExt->CPulExt::Init();

	// PRI 분석 초기화
	m_theAnalPRI->CAnalPRI::Init();

	// AET 생성 초기화
	m_theMakeAET->CMakeAET::Init();

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
void CKnownSigAnal::MarkToPdwIndex(PDWINDEX *pPdwIndex, int count, int mark_type)
{
	for( int i=0 ; i < count ; ++i )
		MARK[ *pPdwIndex++ ] = mark_type;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKnownSigAnal::SaveAllPdwFile
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-20 11:38:34
//
//##ModelId=42E85F34029E
void CKnownSigAnal::SaveAllPdwFile()
{
#ifdef _WIN32
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CAdvSigAnalView *pView = ( CAdvSigAnalView * ) pFrame->GetActiveView();

	int i;
	FILE *pdwfile;
	TNEW_PDW *pPDW;
	PDWINDEX *pPdwIndex;
	char filename[100];

	CString strFilename=pView->GetFileTitle();

	LPTSTR p = strFilename.GetBuffer( 100 );

	pPdwIndex = & m_pGrPdwIndex->pIndex[0];
	sprintf( filename, "c:\\temp\\%s_debug_ksp.pdw", p );
	pdwfile = fopen( filename, "wb" );
	for( i=0 ; i < m_pPdwBank->count ; ++i ) {
		pPDW = & m_pPdwBank->pPdw[ i ];
		fwrite( pPDW, sizeof( TNEW_PDW ), 1, pdwfile );
	}

	fclose( pdwfile );

	strFilename.ReleaseBuffer();

#endif
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
void CKnownSigAnal::SaveEmitterPdwFile(STR_EMITTER *pEmitter, int index )
{

#ifdef _WIN32
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

	STR_NEWAET *pNewAet;
	STR_UPDAET *pUpdAet;

	// 추적 성공 또는 실패인지를 검사한다.
	pUpdAet = m_theMakeAET->GetUpdAet();
	if( pUpdAet != NULL ) {
		SendUpdAet( pUpdAet );
		m_CoUpdAet = 1;
	}
	else {
		SendLostAet();
		m_CoUpdAet = 0;
	}

	// 두개 이상의 추적 성공 에미터 제외한다.
	count = m_theMakeAET->GetCoNewAet();

#ifdef _WIN32
	STR_NEWAET *pDstAet;
	pDstAet = pNewAet = m_theMakeAET->CMakeAET::GetAet();

#else
	pNewAet = m_theMakeAET->CMakeAET::GetAet();

#endif

	int inEMT;

	inEMT = m_theMakeAET->GetIndexNewAet();
	for( i=0 ; i < count ; ++i ) {
		if( pUpdAet == NULL ||
			( pUpdAet != NULL && m_theMakeAET->CheckHarmonic( & pUpdAet->aet, & (pNewAet+inEMT)->aet ) == 0 ) ) {
			// CheckHarmonic() 에서는 PRI 값으로 펄스열 병합을 수행하고
			// 실패된 펄스열에 대해서 이제는 펄스열 인덱스를 비교해서 두 펄스열간의 병합을 최종 판단한다.
			//-- 조철희 2005-10-31 13:59:43 --//
			//if( TRUE == CheckPdwHarmonic( pUpdAet, pNewAet ) )
			{
				SendNewAet( pNewAet, inEMT );

#ifdef _WIN32
				memcpy( pDstAet, pNewAet+inEMT, sizeof( STR_NEWAET ) );
				++ pDstAet;
#endif

				// 추적에서 새로운 에미터 개수를 제한한다.
				++ m_CoNewAet;
				if( m_CoNewAet >= CO_MAX_KSP_NEW_AET )
					return;
			}
		}

		++ inEMT;
	}

	m_theMakeAET->SetCoNewAet( m_CoNewAet );

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKnownSigAnal::SendUpdAet
// 반환되는 형  : void
// 함 수 인 자  : STR_UPDAET *pUpdAet
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-07-29 10:46:25
//
//##ModelId=42E98F2E0131
void CKnownSigAnal::SendUpdAet(STR_UPDAET *pUpdAet)
{
#ifdef _WIN32
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CAdvSigAnalView *pView = ( CAdvSigAnalView * ) pFrame->GetActiveView();

	// 추적 변경 에미터 버퍼에 복사한다.
	memcpy( gUpdAet+pUpdAet->aet.noEMT, pUpdAet, sizeof( STR_UPDAET) );

	pView->UpdateUpdAetInfo( pUpdAet, m_pPdwBank );
	SendKSPUpdAet( pUpdAet );
#else
	SendKSPUpdAet( pUpdAet );

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
#ifdef _WIN32
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CAdvSigAnalView *pView = ( CAdvSigAnalView * ) pFrame->GetActiveView();

	gUpdAet[stTrkAet.aet.noEMT].aet.noEMT = 0;
	pView->UpdateUpdAetInfo( & gUpdAet[stTrkAet.aet.noEMT], m_pPdwBank );
	SendKSPLostAet( & stTrkAet, _spInsuPul );
#else
	SendKSPLostAet( & stTrkAet, _spInsuPul );

#endif
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
void CKnownSigAnal::SendNewAet(STR_NEWAET *pNewAet, int inEMT )
{
#ifdef _WIN32
	CMainFrame *pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CAdvSigAnalView *pView = ( CAdvSigAnalView * ) pFrame->GetActiveView();

	pView->UpdateNewAetInfoFromKSP( pNewAet+inEMT, m_pPdwBank );
	SendKSPNewAet( pNewAet, inEMT );
#else
	SendKSPNewAet( pNewAet, inEMT );

#endif
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : __pure_virtual
// 반환되는 형  : extern "C" void
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2014-05-08 10:29:05
//
#ifndef _WIN32
extern "C" void __pure_virtual()
{
	while( 1 ) { printf("error" ); }
}
#endif

