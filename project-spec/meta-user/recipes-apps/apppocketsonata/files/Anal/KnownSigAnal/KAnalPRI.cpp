// KAnalPRI.cpp: implementation of the CKAnalPRI class.
//
//////////////////////////////////////////////////////////////////////

// PC용 상위 클래스에 전달하기 위한 선언
#ifdef _WIN32
#include "../../A50SigAnal/stdafx.h"
//#include "../../AdvSigAnal/AdvSigAnal.h"

//#include "../../AdvSigAnal/MainFrm.h"
//#include "../../AdvSigAnal/AdvSigAnalDoc.h"
//#include "../../AdvSigAnal/AdvSigAnalView.h"

#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "KnownSigAnal.h"
#include "KAnalPRI.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI
// 반환되는 형  : CKAnalPRI::CKAnalPRI(int coMaxPdw) :
// 함 수 인 자  : int coMaxPdw
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-07-28 14:09:52
//
//##ModelId=42E98F300153
CKAnalPRI::CKAnalPRI( void *pParent, int coMaxPdw ) : CAnalPRI( coMaxPdw )
{
	m_pKnownSigAnal = ( CKnownSigAnal * ) pParent;

    INIT_ANAL_VAR_(m_pKnownSigAnal)
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKAnalPRI::~CKAnalPRI
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-07-28 18:06:01
//
//##ModelId=42E98F30015C
CKAnalPRI::~CKAnalPRI()
{

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CKAnalPRI::Init
		\author   조철희
		\return   void
		\version  0.0.34
		\date     2008-07-30 13:35:38
		\warning
*/
void CKAnalPRI::Init()
{

	m_CoSeg = GetCoSeg();
	m_nAnalSeg = GetAnalSeg();

	m_nAnalEmitter = GetCoEmitter();

    m_pTrkAet = m_pKnownSigAnal->GetTrkAET();
	
	/*! \bug  하위 그룹에서 초기화하는 것으로 수정함.
    \date 2008-07-30 13:35:49, 조철희
	*/
	CAnalPRI::Init();

}

//////////////////////////////////////////////////////////////////////
//
//! \brief    추적 모듈의 PRI 분석 메인이다. 분석 흐름도는 아래와 같다.
//!						1) 규칙성 펄스열을 근거로 동일 PRI이면서 겹쳐진 Stagger 펄스열을 분석한다.
//!						2) 나머지 규칙성 펄스열을 Stable 에미터로 생성하게 한다.
//!						3) 불규칙성 팔스열들을 근거로 Jitter 에미터로 생성한다.
//!						4) Jitter 에미터를 대상으로 정밀 스태거 분석을 한다.
//!						5) 주파수 및 PRI 도메인 영역에서 패턴 분석을 한다.
//!						6) 현재까지 생성된 에미터들을 대상으로 정밀 스태거 분석을 한다.
//! \author   조철희
//! \return   void
//! \version  1.37
//! \date     2006-08-24 16:36:32
//! \warning
//
void CKAnalPRI::Analysis()
{
	// 펄스열 초기화
	Init();

	// Wide 펄스열들을 참조해서 Narrow 그룹화된 펄스열 제거 여부를 판단한다.
	// DeleteNarrowSeg();

	// 펄스열 그룹핑
	// 아래 함수 순서는 각 처리에 따라 호출되기 때문에
	// 변경할 때 주의해서 변경해야 한다.
	GroupingStagger();
	GroupingStable();
	GroupingJitter();
	GroupingUnknown();

	// 정밀 PRI 분석
	// 하모닉 Stable로 펄스열이 구성이 되면 Dwell을 의심해 본다.
	//-- 조철희 2005-12-22 16:09:50 --//
	// Dwell 분석시에 Dwell 펄스열 추출을 위해  
	// DwellAnalysis();
	StaggerAnalysis();
	PatternAnalysis();

	// 에미터 그룹핑
	// PRI 타입이 다르더라도 PRI 평균이 같은 에미터 단위는 하나로 형성한다.
	MergeGrouping( ALL_MERGE );

	CAnalPRI::Analysis();

	// 상속클래스의 PRI 분석
	// 처음부터 하모닉 체크를 한다.
	// GroupingKnownPri();
	
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKAnalPRI::KnownAnalysis
// 반환되는 형  : BOOL
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-07-28 18:06:05
//
//##ModelId=42E98F300152
BOOL CKAnalPRI::KnownAnalysis()
{
    //STR_PRI *pPri;
	
	m_CoSeg = GetCoSeg();

	// 타입에 따라서 펄스열 분석을 달리한다.
    //pPri = & stTrkAet.aet.pri;
    switch( m_pTrkAet->iPRIType ) {
		case _STABLE :
			// 추적에서는 로브 조건을 무시하도록 한다.
			GroupingStable( TRUE );
			PatternAnalysis();
			break;

		case _STAGGER :
			// 추적에서는 로브 조건을 무시하도록 한다.
			GroupingJitter( TRUE );
			StaggerAnalysis();
			PatternAnalysis();
			break;

		case _JITTER_RANDOM :
			// 추적에서는 로브 조건을 무시하도록 한다.
			GroupingJitter( TRUE );
			StaggerAnalysis();
			PatternAnalysis();
			break;

		case _JITTER_PATTERN :
			// 추적에서는 로브 조건을 무시하도록 한다.
			GroupingJitter( TRUE );
			PatternAnalysis();
			break;

		case _DWELL :
			// 추적에서는 로브 조건을 무시하도록 한다.
			// 추적할 에미터의 PRI 정보를 근거로 에미터를 생성한다.
			GroupingStable( TRUE );
			GroupingDwell();
			PatternAnalysis();
			break;

	}

	CAnalPRI::Analysis();

	return TRUE;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKAnalPRI::ExtractStagger
// 반환되는 형  : int
// 함 수 인 자  : STR_PDWINDEX *pPdwIndex
// 함 수 인 자  : UINT framePri
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 17:00:01
//
int CKAnalPRI::ExtractStagger(STR_PDWINDEX *pPdwIndex, _TOA framePri, STR_EMITTER *pEmitter )
{
	return m_pKnownSigAnal->ExtractStagger( pPdwIndex, framePri, pEmitter );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKAnalPRI::CheckPriInterval
// 반환되는 형  : BOOL
// 함 수 인 자  : STR_PULSE_TRAIN_SEG *pSeg1
// 함 수 인 자  : STR_PULSE_TRAIN_SEG *pSeg2
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:14:24
//
BOOL CKAnalPRI::CheckPriInterval( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 ) 
{	
	return m_pKnownSigAnal->CheckPriInterval( pSeg1, pSeg2 ); 
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKAnalPRI::DeleteAllSeg
// 반환되는 형  : void
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:14:21
//
void CKAnalPRI::DeleteAllSeg( STR_EMITTER *pEmitter ) 
{ 
	m_pKnownSigAnal->DeleteAllSeg( pEmitter ); 
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKAnalPRI::ExtractRefStable
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 16:59:48
//
void CKAnalPRI::ExtractRefStable() 
{ 
	m_pKnownSigAnal->ExtractRefStable(); 
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKAnalPRI::ExtractDwellRefPT
// 반환되는 형  : void
// 함 수 인 자  : STR_PRI_RANGE_TABLE *pExtRange
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 16:59:52
//
BOOL CKAnalPRI::ExtractDwellRefPT( STR_PULSE_TRAIN_SEG *pDwlSewg, STR_PRI_RANGE_TABLE *pExtRange )
{ 
    return m_pKnownSigAnal->ExtractDwellRefPT( pDwlSewg, pExtRange );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKAnalPRI::ExtractFramePri
// 반환되는 형  : UINT
// 함 수 인 자  : STR_PDWINDEX *pSrcPdwIndex
// 함 수 인 자  : UINT framePri
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:14:17
//
UINT CKAnalPRI::ExtractFramePri(STR_PDWINDEX *pSrcPdwIndex, _TOA framePri )
{	
	return m_pKnownSigAnal->ExtractFramePri( pSrcPdwIndex, framePri ); 
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKAnalPRI::GetCoSeg
// 반환되는 형  : int
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:14:14
//
int CKAnalPRI::GetCoSeg() 
{	
	return m_pKnownSigAnal->GetCoSeg(); 
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CKAnalPRI::GetAnalSeg
//! \author   조철희
//! \return   int
//! \version  1.37
//! \date     2006-08-25 09:00:21
//! \warning
//
int CKAnalPRI::GetAnalSeg() 
{	
	return m_pKnownSigAnal->GetAnalSeg(); 
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : *CKAnalPRI::GetPulseSeg
// 반환되는 형  : STR_PULSE_TRAIN_SEG
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:14:12
//
STR_PULSE_TRAIN_SEG *CKAnalPRI::GetPulseSeg() 
{ 
	return m_pKnownSigAnal->GetPulseSeg(); 
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKAnalPRI::GetMaxPdw
// 반환되는 형  : int
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:14:09
//
int CKAnalPRI::GetMaxPdw() 
{ 
	return m_pKnownSigAnal->GetMaxPdw(); 
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKAnalPRI::MakePRIInfoInSeg
// 반환되는 형  : void
// 함 수 인 자  : STR_PRI *pPri
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:14:07
//
void CKAnalPRI::MakePRIInfoInSeg( STR_PRI *pPri, STR_EMITTER *pEmitter ) 
{ 
	m_pKnownSigAnal->MakePRIInfoInSeg( pPri, pEmitter ); 
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CKAnalPRI::MedianFreq
//! \author   조철희
//! \param    pMinMax 인자형태 STR_TYPEMINMAX *
//! \param    pPdwIndex 인자형태 PDWINDEX *
//! \param    count 인자형태 int
//! \return   UINT
//! \version  1.00
//! \date     2006-01-23 10:14:02
//! \warning
//
UINT CKAnalPRI::MedianFreq( STR_TYPEMINMAX *pMinMax, PDWINDEX *pPdwIndex, int count ) 
{ 
	return m_pKnownSigAnal->MedianFreq( pMinMax, pPdwIndex, count ); 
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKAnalPRI::VerifyPRI
// 반환되는 형  : int
// 함 수 인 자  : PDWINDEX *pPdwIndex
// 함 수 인 자  : int count
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-06 14:44:01
//
_TOA CKAnalPRI::VerifyPRI( PDWINDEX *pPdwIndex, int count )
{
	return m_pKnownSigAnal->VerifyPRI( pPdwIndex, count );
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CKAnalPRI::FindPeakInHist
//!	\author  조철희
//!	\param	 count	인자형태 int
//!	\param	 pPdwIndex	인자형태 PDWINDEX *
//! \version 1.0
//! \date		 2006-07-06 17:28:14
//! \warning
//
int CKAnalPRI::FindPeakInHist( int count, PDWINDEX *pPdwIndex )
{
	return m_pKnownSigAnal->FindPeakInHist( count, pPdwIndex );
}

void CKAnalPRI::SaveEmitterPdwFile(STR_EMITTER *pEmitter, int index )
{
    m_pKnownSigAnal->SaveEmitterPdwFile( pEmitter, index );

}


int CKAnalPRI::GetBand()
{
    return m_pKnownSigAnal->GetBand();
}
