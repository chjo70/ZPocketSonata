// KAnalPRI.cpp: implementation of the CKAnalPRI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../OFP_Main.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "KnownSigAnal.h"
#include "KAnalPRI.h"

STR_PULSE_TRAIN_SEG *CKAnalPRI::m_pSeg=NULL;


/**
 * @brief     펄스열들을 정렬시 PRI 평균값으로 오름차순으로 정렬하기 위한 함수입니다.
 * @param     const void * arg1
 * @param     const void * arg2
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-08-25 19:35:13
 * @warning
 */
// int CKAnalPRI::incSegPriMeanCompare( const void *arg1, const void *arg2 )
// {
//     int iRet;
//     const UINT *p1, *p2;
//     STR_PULSE_TRAIN_SEG *pSeg1, *pSeg2;
//
//     p1 = (const UINT *) arg1;
//     p2 = (const UINT *) arg2;
//
//     pSeg1 = & m_pSeg[ *p1 ];
//     pSeg2 = & m_pSeg[ *p2 ];
//
//     if( pSeg1->stPRI.tMean > pSeg2->stPRI.tMean ) {
//         iRet = 1;
//     }
//     else if( pSeg1->stPRI.tMean < pSeg2->stPRI.tMean ) {
//         iRet = (-1);
//     }
//     else {
//         iRet = 0;
//     }
//
//     return iRet;
// }

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
CKAnalPRI::CKAnalPRI( void *pParent, unsigned int uiCoMaxPdw, const char *pThreadName ) : CAnalPRI( pParent, enTRK_ANAL, uiCoMaxPdw, pThreadName )
{
    SetAnalType( enTRK_ANAL );

	m_pKnownSigAnal = ( CKnownSigAnal * ) pParent;

    INIT_ANAL_VAR_(m_pKnownSigAnal)
}

/**
 * @brief     추적용 PRI 분석 객체를 소멸시 처리를 수행한다.
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2005-07-28 18:06:01
 * @warning
 */
CKAnalPRI::~CKAnalPRI()
{

}

/**
 * @brief     초기화 처리를 수행한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2008-07-30 13:35:38
 * @warning
 */
void CKAnalPRI::Init()
{

	m_uiCoSeg = GetCoSeg();
	m_uiAnalSeg = GetAnalSeg();

    //m_uiAnalEmitter = GetCoEmitter();

    m_pTrkABT = m_pKnownSigAnal->GetTrkAET();

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
void CKAnalPRI::Analysis()
{
    // 초기화
    Init();

    // 고정펄스열들에 대하여 스태거 그룹핑 수행하여 스태거 신호인지 분석한다.
    //GroupingStagger();
    //StaggerAnalysis();
    //PrintAllEmitter( 0, "[1/8] 그룹핑 Stable PRI 기반 스태거 분석", _UNKNOWN_FREQ, _STAGGER );

    // 고정펄스열 그룹핑은 스태거 그룹핑 후 검증하여 해제된 펄스열들에 대해 한다.
    GroupingStable();
    PrintAllEmitter( 0, "[2/8] 스테이블 PRI 분석", _UNKNOWN_FREQ, _STABLE );

    GroupingJitter();
    PrintAllEmitter( 0, "[3/8] 지터 PRI 분석", _UNKNOWN_FREQ, _JITTER_RANDOM );

    ///////////////////////////////////////////////////////////////////////////////////
    // 기존 에미터 분석한 결과에서 세부 분석을 수행 합니다.
    // 지터 그룹핑된 이후 스태거 분석을 한번 더 수행한다.(Jitter 펄스열들에 대해 Auto-Correlation Function으로 스태거 분석 수행)
    MergeGrouping();
    StaggerAnalysis();
    PrintAllEmitter( 0, "[4/8] 스태거 PRI 분석", _UNKNOWN_FREQ, _JITTER_STAGGER );

    // PRI 고정으로 분석된 에미터들에 대해 D&S 분석을 수행한다.
    DwellNSwitchAnalysis();
    PrintAllEmitter( 0, "[5/8] 드웰 PRI 분석", _UNKNOWN_FREQ, _DWELL );

    // Agile 형태 에미터를 대상으로 Hopping 여부를 분석한다.
    HoppingAnalysis();
    PrintAllEmitter( 0, "[6/8] 호핑 PRI 분석", _HOPPING, _UNKNOWN_PRI );

    // 주파수/PRI 패턴 분석을 수행한다.
    PatternAnalysis();
    PrintAllEmitter( 0, "[7-1/8] 주파수 패턴 분석", _PATTERN_AGILE, _UNKNOWN_PRI );
    PrintAllEmitter( 0, "[7-2/8] PRI 패턴 분석", _UNKNOWN_FREQ, _JITTER_PATTERN );

    // 에미터 그룹핑
    // PRI 타입이 다르더라도 PRI 평균이 같은 에미터 단위는 하나로 형성한다.
    MergeGrouping();
    PrintAllEmitter( 0, "[8/8] 유사 PRI 병합" );

    CAnalPRI::Analysis();

}

/**
 * @brief     추적용 PRI 분석을 처리한다. 알고 있는 제원으로 분석한다.
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2005-07-28 18:06:05
 * @warning
 */
bool CKAnalPRI::KnownAnalysis( ENUM_ROBUST_ANAL enRobustAnal )
{
    bool bFreqPattern; //, bPRIPattern;

    // 펄스열 추출 업데이트
	m_uiCoSeg = GetCoSeg();

	// 정밀 분석 요청
    //TODO: 주파수 및 PRI 형태에 따라 정밀 분석을 요청 합니다. 위협 관리에서 CED 라이브러리를 참조해서 정밀 분석을 요청하게 합니다.
    //date 	2023-10-30 11:47:55
    bFreqPattern = ( enRobustAnal == enFREQ_ROBUST_ANALYSIS || enRobustAnal == enFREQ_PRI_ROBUST_ANALYSIS ? true : false );
    //bPRIPattern = ( enRobustAnal == enPRI_ROBUST_ANALYSIS || enRobustAnal == enFREQ_PRI_ROBUST_ANALYSIS ? true : false );
    switch( m_pTrkABT->vPRIType ) {
		case ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED :
			// 추적에서는 로브 조건을 무시하도록 한다.
			GroupingStable( TRUE );

            if( m_pTrkABT->vFreqType == ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING ) {
                HoppingAnalysis();
            }
            else {
			    PatternAnalysis( bFreqPattern, false );
            }
			break;

		case ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER :
			// 추적에서는 로브 조건을 무시하도록 한다.
			GroupingJitter( TRUE );

            if( m_pTrkABT->vFreqType == ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING ) {
                HoppingAnalysis();
            }

			PatternAnalysis( bFreqPattern, false );
            StaggerAnalysis();
			break;

		case ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER :
			// 추적에서는 로브 조건을 무시하도록 한다.
			GroupingJitter( TRUE );

            if( m_pTrkABT->vFreqType == ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING ) {
                HoppingAnalysis();
            }

            StaggerAnalysis();
			PatternAnalysis( bFreqPattern, true );
			break;

		case ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN :
			// 추적에서는 로브 조건을 무시하도록 한다.
			GroupingJitter( TRUE );

            if( m_pTrkABT->vFreqType == ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING ) {
                HoppingAnalysis();
            }

			PatternAnalysis( bFreqPattern, true );
			break;

		case ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH :
			// 추적에서는 로브 조건을 무시하도록 한다.
			// 추적할 에미터의 PRI 정보를 근거로 에미터를 생성한다.
            GroupingJitter();

            if( m_pTrkABT->vFreqType == ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING ) {
                HoppingAnalysis();
            }

            PatternAnalysis( bFreqPattern, false );
            DwellNSwitchAnalysis();
			break;

        default:
            break;

	}

	CAnalPRI::Analysis();

	return TRUE;
}

/**
 * @brief     스태거 신호를 추적한다.
 * @param     STR_PDWINDEX * pPdwIndex
 * @param     _TOA framePri
 * @param     STR_EMITTER * pEmitter
 * @return    unsigned int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-01-23 17:00:01
 * @warning
 */
unsigned int CKAnalPRI::ExtractStagger( _TOA framePri, STR_EMITTER *pEmitter )
{
	return m_pKnownSigAnal->ExtractStagger( framePri, pEmitter );
}

/**
 * @brief     펄스열 간의 하모닉 체크를 수행한다.
 * @param     STR_PULSE_TRAIN_SEG * pSeg1
 * @param     STR_PULSE_TRAIN_SEG * pSeg2
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-01-23 10:14:24
 * @warning
 */
bool CKAnalPRI::CheckPriInterval( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 )
{
	return m_pKnownSigAnal->CheckPriInterval( pSeg1, pSeg2 );
}

/**
 * @brief     가상 에미터에 지정한 펄스열에 대해서 삭제 마킹을 한다.
 * @param     STR_EMITTER * pEmitter
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-01-23 10:14:21
 * @warning
 */
// void CKAnalPRI::DeleteAllSeg( STR_EMITTER *pEmitter )
// {
// 	m_pKnownSigAnal->DeleteAllSeg( pEmitter );
// }

/**
 * @brief     기준 펄스열을 추출한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-01-23 16:59:48
 * @warning
 */
void CKAnalPRI::ExtractRefStable()
{
	m_pKnownSigAnal->ExtractRefStable();
}

/**
 * @brief     드웰 기준 펄스열을 추출한다.
 * @param     STR_PULSE_TRAIN_SEG * pDwlSewg
 * @param     STR_PRI_RANGE_TABLE * pExtRange
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-01-23 16:59:52
 * @warning
 */
bool CKAnalPRI::ExtractDwellRefPT( STR_PULSE_TRAIN_SEG *pDwlSewg, STR_PRI_RANGE_TABLE *pExtRange )
{
    return m_pKnownSigAnal->ExtractDwellRefPT( pDwlSewg, pExtRange );
}

/**
 * @brief     FramePRI 펄스열을 추출한다.
 * @param     STR_PDWINDEX * pSrcPdwIndex
 * @param     _TOA framePri
 * @return    UINT
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-01-23 10:14:17
 * @warning
 */
// UINT CKAnalPRI::ExtractFramePri(STR_PDWINDEX *pSrcPdwIndex, _TOA framePri )
// {
// 	return m_pKnownSigAnal->ExtractFramePri( pSrcPdwIndex, framePri );
// }

/**
 * @brief     펄스열추출 단계에서의 펄스열 개수를 얻는다.
 * @return    unsigned int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-01-23 10:14:14
 * @warning
 */
unsigned int CKAnalPRI::GetCoSeg()
{
	return m_pKnownSigAnal->GetCoSeg();
}

/**
 * @brief     펄스열추출 단계에서의 펄스열 개수를 얻는다.
 * @return    unsigned int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-08-25 19:41:47
 * @warning
 */
unsigned int CKAnalPRI::GetAnalSeg()
{
	return m_pKnownSigAnal->GetAnalSeg();
}

/**
 * @brief     펄스열추출 단계에서의 펄스열 포인터를 리턴한다.
 * @return    STR_PULSE_TRAIN_SEG *
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-08-25 19:42:07
 * @warning
 */
STR_PULSE_TRAIN_SEG *CKAnalPRI::GetPulseSeg()
{
	return m_pKnownSigAnal->GetPulseSeg();
}

/**
 * @brief     수집한 PDW 개수를 리턴한다.
 * @return    unsigned int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-01-23 10:14:09
 * @warning
 */
unsigned int CKAnalPRI::GetMaxPDW()
{
	return m_pKnownSigAnal->GetMaxPdw();
}

/**
 * @brief     MakePRIInfoFromSeg
 * @param     STR_PRI * pPri
 * @param     STR_EMITTER * pEmitter
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-01-23 10:14:07
 * @warning
 */
// void CKAnalPRI::MakePRIInfoFromSeg( STR_PRI *pPri, STR_EMITTER *pEmitter )
// {
// 	m_pKnownSigAnal->MakePRIInfoFromSeg( pPri, pEmitter );
// }

/**
 * @brief     주파수 메디안 값을 계산한다.
 * @param     STR_TYPEMINMAX * pMinMax
 * @param     PDWINDEX * pPdwIndex
 * @param     unsigned int uiCount
 * @return    UINT
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-01-23 10:14:02
 * @warning
 */
UINT CKAnalPRI::MedianFreq( STR_MINMAX *pMinMax, PDWINDEX *pPdwIndex, unsigned int uiCount )
{
	return m_pKnownSigAnal->MedianFreq( pMinMax, pPdwIndex, uiCount );
}

/**
 * @brief     PRI 검증을 수행한다.
 * @param     PDWINDEX * pPdwIndex
 * @param     unsigned int uiCount
 * @return    _TOA
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-02-06 14:44:01
 * @warning
 */
_TOA CKAnalPRI::VerifyPRI( PDWINDEX *pPdwIndex, unsigned int uiCount )
{
	return m_pKnownSigAnal->VerifyPRI( pPdwIndex, uiCount);
}

/**
 * @brief     히스토그램 상에서 큰 값을 찾는다.
 * @param     unsigned int uiCount
 * @param     PDWINDEX * pPdwIndex
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-07-06 17:28:14
 * @warning
 */
int CKAnalPRI::FindPeakInHist(unsigned int uiCount, PDWINDEX *pPdwIndex )
{
	return m_pKnownSigAnal->FindPeakInHist(uiCount, pPdwIndex );
}

/**
 * @brief     PDW 데이터를 파일로 저장한다.
 * @param     STR_EMITTER * pEmitter
 * @param     int iPLOBID
 * @param     bool bSaveFile
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-08-26 14:22:44
 * @warning
 */
// void CKAnalPRI::SaveEmitterPDWFile(STR_EMITTER *pEmitter, int iPLOBID, bool bSaveFile )
// {
//     m_pKnownSigAnal->SaveEmitterPDWFile( pEmitter, iPLOBID, bSaveFile );
// 
// }

/**
 * @brief     추적 수집한 PDW 데이터의 대역을 리턴한다.
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-08-26 14:23:15
 * @warning
 */
int CKAnalPRI::GetBand()
{
    return m_pKnownSigAnal->GetBand();
}

/**
 * @brief     QSort 정렬을 수행한다.
 * @param     unsigned int * pIdx
 * @param     unsigned int uiCount
 * @param     unsigned int uiSizeof
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-08-26 14:23:39
 * @warning
 */
// void CKAnalPRI::QSort( unsigned int *pIdx, unsigned int uiCount, unsigned int uiSizeof )
// {
//     qsort( pIdx, uiCount, uiSizeof, incSegPriMeanCompare );
//     return;
// }

/**
 * @brief     LOB 데이터 포인터를 리턴한다.
 * @return    CMakeAET*
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022/01/03 15:24:27
 * @warning
 */
CMakeAET* CKAnalPRI::GetMakeAET()
{
    return m_pKnownSigAnal->GetMakeAET();
}

/**
 * @brief		호핑 분석을 호출한다.
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2022/01/03 15:41:15
 * @warning
 */
void CKAnalPRI::HoppingAnalysis()
{
    CAnalPRI::HoppingAnalysis();
}


/**
 * @brief     펄스열 추출로 규칙성 펄스열을 검증한다.
 * @param     _TOA * pnHarmonic
 * @param     STR_PULSE_TRAIN_SEG * pSeg1
 * @param     STR_PULSE_TRAIN_SEG * pSeg2
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-06-15, 11:30
 * @warning
 */
bool CKAnalPRI::CheckStablePT( _TOA *pnHarmonic, STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2, int iMaxMiss, bool bForceMerge )
{
    return m_pKnownSigAnal->CheckStablePT( pnHarmonic, pSeg1, pSeg2, iMaxMiss, bForceMerge );
}


/**
 * @brief     SaveDebug
 * @param     char * pSourcefile
 * @param     char * piLines
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-06 13:44:31
 * @warning
 */
void CKAnalPRI::SaveDebug( const char *pSourcefile, int iLines )
{
    m_pKnownSigAnal->SaveDebug( pSourcefile, iLines );

}

