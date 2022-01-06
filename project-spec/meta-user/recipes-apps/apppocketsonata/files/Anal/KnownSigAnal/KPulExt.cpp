// KPulExt.cpp: implementation of the CKPulExt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "KnownSigAnal.h"
#include "KPulExt.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt
// 반환되는 형  : CKPulExt::CKPulExt(int coMaxPdw) :
// 함 수 인 자  : int coMaxPdw
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-07-28 14:10:33
//
//##ModelId=42E85F3303AD
CKPulExt::CKPulExt( void *pParent, int coMaxPdw ) : CPulExt( coMaxPdw )
{
	m_pKnownSigAnal = ( CKnownSigAnal * ) pParent;

    INIT_ANAL_VAR_(m_pKnownSigAnal)

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKPulExt::~CKPulExt
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-07-28 17:28:22
//
//##ModelId=42E85F3303B5
CKPulExt::~CKPulExt()
{

}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CKPulExt::Init
//! \author   조철희
//! \return   void
//! \version  1.37
//! \date     2006-08-29 10:46:19
//! \warning
//
void CKPulExt::Init()
{
	m_uiAnalSeg = m_uiCoSeg;

    m_pTrkAet = m_pKnownSigAnal->GetTrkAET();

	/*! \bug  하위 그룹에서 초기화하는 것으로 수정함.
	    \date 2008-07-30 13:29:53, 조철희
	*/
	CPulExt::Init();
	
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CKPulExt::PulseExtract
//! \author   조철희
//! \return   void
//! \version  1.37
//! \date     2006-08-24 15:54:03
//! \warning
//
void CKPulExt::PulseExtract()
{
	// 펄스열 초기화
	Init();

	//////////////////////////////////////////////////////////////////////////
	// DTOA 히스토그램을 이용해서 펄스열의 범위를 대략 구한다.
	GetStartEndPriLevel();
	
	//////////////////////////////////////////////////////////////////////////
	// 규칙성 펄스열 찾기
	SetRefStartSeg();

	// 규칙성 펄스열의 기준 PRI 값을 찾는다. 모든 전 구간에서 찾는다.
	FindRefStable();

	// 기준 PRI 로 펄스열 추출
	ExtractRefStable();

	// 펄스 개수가 작거나 펄스열의 마크가 DELETE_SEG 일때 버린다.
	// 펄스열 저장소를 정리한다.
	CleanPulseTrains();

	// 규칙성 펄스열을 찾은 펄스열 인덱스
	SetRefEndSeg();
	
    ClearAllMark();
    //memset( m_pMARK, 0, sizeof( m_pKnownSigAnal->MARK ) );

	//////////////////////////////////////////////////////////////////////////
	// 불규칙성 펄스열 찾기
	//
	// 펄스열 구간마다 불규칙성 펄스열과 불규칙성 펄스열을 같이 추출한다.
	// 펄스열은 각 단계마다 규칙성 펄스열과 불규칙성 펄스열을 동시에 수행한다.
	//-- 조철희 2005-12-09 16:11:27 --//
	ExtractJitter( _STABLE + _JITTER_RANDOM );

	// 펄스열의 인덱스를 조사해서 겹쳐져 있으면 그 중 한개를 버린다.
	DiscardPulseTrain();

    //CPulExt::PulseExtract();

}

/*

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKAnalPRI::GroupingKnownPri
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-09-30 14:24:19
//
void CKPulExt::GroupingKnownPri() {
	int i, j;
	STR_PULSE_TRAIN_SEG *pSeg1, *pSeg2;

	// 추적 에미터를 근거로 추출한 펄스열과 새로운 분석에서 추출한 펄스열 간의
	// 병합 판단을 체크해서 병합 판정이 되면 새로운 분석에서 추출한 펄스열은
	// 제거 하도록 한다.
	for( i=0 ; i < m_nAlanSeg ; ++i ) {
		pSeg1 = & m_pSeg[i];
		for( j=nAlanSeg ; j < nCoSeg ; ++j ) {
			pSeg2 = & m_pSeg[j];

			if( pSeg2->mark == CHECKED_SEG || pSeg2->mark == DELETE_SEG )
				continue;

			if( pSeg1->pri_type == _STABLE && pSeg2->pri_type == _JITTER ) {
				if( CheckHarmonic( pSeg1, pSeg2 ) != 0 && OverlappedSeg( pSeg1, pSeg2 ) == TRUE )
					pSeg2->mark = DELETE_SEG;
			}
		}
	}

}

	*/

//////////////////////////////////////////////////////////////////////
//
//! \brief    알고 있는 에미터 제원을 기반으로 펄스열을 추출하게 한다.
//! \author   조철희
//! \return   void
//! \version  1.37
//! \date     2006-08-24 14:07:54
//! \warning
//
void CKPulExt::KnownPulseExtract()
{
	int i;
	int diff;
	STR_PRI_RANGE_TABLE extRange;

    STR_PULSE_TRAIN_SEG *pSeg;

    pSeg = GetPulseSeg();
    
	// 타입에 따라서 펄스열 추출을 달리한다.
    //pPri = & SRxABTDatapri;

    switch( m_pTrkAet->iPRIType ) {
		case _STABLE :
            extRange.min_pri = ITOAusCNV( m_pTrkAet->fPRIMin ) - STABLE_MARGIN;
            extRange.max_pri = ITOAusCNV( m_pTrkAet->fPRIMax ) + STABLE_MARGIN;
			ExtractStablePT( & extRange, TRUE );
			break;

		case _STAGGER :
			// 추출할 펄스열의 범위폭을 계산한다.
            extRange.min_pri = ITOAusCNV( m_pTrkAet->fPRIMin ) - STABLE_MARGIN;
            extRange.max_pri = ITOAusCNV( m_pTrkAet->fPRIMax ) + STABLE_MARGIN;
			ExtractJitterPT( & extRange, UINT32_MAX, 3, TRUE );

			/*! \bug  추출하고자할 PRI 평균값을 중심으로 지터열을 추출하게 한다.
			    \date 2006-06-28 00:39:34, 조철희
			*/
            ExtractTrackPT( ITOAusCNV(m_pTrkAet->fPRIMean), FDIV( m_pTrkAet->fPRIJitterRatio, 100 ) );
			break;

		case _DWELL :
            for( i=0 ; i < m_pTrkAet->iPRIPositionCount ; ++i ) {
                extRange.min_pri = ITOAusCNV( m_pTrkAet->fPRISeq[i] ) - ( 2 * STABLE_MARGIN );
                extRange.max_pri = ITOAusCNV( m_pTrkAet->fPRISeq[i] ) + ( 2 * STABLE_MARGIN );
                ExtractDwellRefPT( pSeg, & extRange );
			}
			ExtractRefStable();
			break;

		case _JITTER_RANDOM :
			/*! \bug  규칙성 펄스열을 찾아서 제거한다. 그러나 겹쳐진 펄스열들은 삭제하지 않는다.
			    \date 2006-09-04 20:56:25, 조철희
			*/
			// 지터열 추출 마진 설정
            diff = UDIV( m_pTrkAet->fPRIMean * ( m_pTrkAet->fPRIJitterRatio+EXTRACT_JITTER_MARGIN ), 200 );
            extRange.min_pri = _max( (int)(m_pTrkAet->fPRIMean - diff), 2 );
            extRange.max_pri = ITOAusCNV( m_pTrkAet->fPRIMean ) + diff;
			ExtractStablePT( & extRange, TRUE );
			DiscardStablePT();

			/*! \bug  KHP RWR의 위협신호 발생기에서 최대 변이가 지터율로 발생함.
								이런 지터 신호가 정말 있는지 궁금. 실제환경에서 지터 신호를 좀더 수집 해봐야 하겠음.
								Stable은 기존대로 추출하며 Jitter열은 위협 신호 발생기를 고려해서 좀더 추출하게 함.
			    \date 2008-10-25 17:01:53, 조철희
			*/
            diff = UDIV( m_pTrkAet->fPRIMean * ( m_pTrkAet->fPRIJitterRatio+20 ), 200 );
            extRange.min_pri = _max( (int)(m_pTrkAet->fPRIMean - diff), 2 );
            extRange.max_pri = ITOAusCNV( m_pTrkAet->fPRIMean ) + diff;
			// 추출할 펄스열의 범위폭을 계산한다.
			ExtractJitterPT( & extRange, UINT_MAX, 3, TRUE );

			// D:\RSA-조철희\소나타 ES TFT\해상 신호\A21-Check_Pulse_Mege\chirp_up.pdw 인 
			// 하노닉 레이더 신호(?) 때문에 
			// 2배의 PRI도 추출하도록 한다.
			extRange.min_pri = 2 * extRange.min_pri;
			extRange.max_pri = 2 * extRange.max_pri;
			ExtractJitterPT( & extRange, UINT_MAX, 3, TRUE );
			break;

		case _JITTER_PATTERN :
			// 추출할 펄스열의 범위폭을 계산한다.
			diff = 200;
			//-- 조철희 2006-02-22 09:59:34 --//
            extRange.min_pri = ITOAusCNV( m_pTrkAet->fPRIMin ) - diff;
            extRange.max_pri = ITOAusCNV( m_pTrkAet->fPRIMax ) + diff;
			ExtractPatternPT( & extRange, 3, TRUE );
			break;

        default:
            break;
	}

    //CPulExt::PulseExtract();

}

//////////////////////////////////////////////////////////////////////
//
//! \brief    규칙성 펄스열들중에서 STABLE 펄스열들만 마킹한다.
//! \author   조철희
//! \return   void
//! \version  1.37
//! \date     2006-09-04 20:58:43
//! \warning
//
void CKPulExt::DiscardStablePT()
{
	//int j;
	STR_PULSE_TRAIN_SEG *pSeg; //, *pSeg1, *pSeg2;

	if( m_uiCoSeg == 0 ) {
    }
    else {
	    // STR_PDWINDEX *pGrPdwIndex = GetFrqAoaGroupedPdwIndex();

	    pSeg = GetPulseSeg();
        ClearAllMark();
        //memset( m_pMARK, 0, sizeof(USHORT)*pGrPdwIndex->count );

	    // 단일 규칙성 펄스열과 펄스열이 추출하지 않을때는 제거하지 않는다.
	    if( m_uiCoSeg == 1 ) {
		    MarkToPdwIndex( pSeg[0].pdw.pIndex, pSeg[0].pdw.uiCount, EXTRACT_MARK );
		    m_uiCoSeg = 0;
	    }
        else {
	        /*! \todo	스태거열을 찾아서 제거해야 한다. */

	        // Stagger 펄스열로 의심이 가는 펄스열들끼기 찾아서 제거시킨다.
	        // pSeg1 = pSeg + m_nAnalSeg;
// 	        for( i=m_nAnalSeg ; i < m_CoSeg ; ++i ) {
// 		        pSeg2 = pSeg + i + 1;
// 		        for( j=i+1 ; j < m_CoSeg ; ++j ) {
// 
// 		        }
// 	        }
        }
    }

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKPulExt::MarkToPdwIndex
// 반환되는 형  : void
// 함 수 인 자  : PDWINDEX *pPdwIndex
// 함 수 인 자  : int count
// 함 수 인 자  : int mark_type
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:04:15
//
void CKPulExt::MarkToPdwIndex( PDWINDEX *pPdwIndex, int count, int mark_type )
{
	m_pKnownSigAnal->MarkToPdwIndex( pPdwIndex, count, mark_type );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : *CKPulExt::GetFrqAoaGroupedPdwIndex
// 반환되는 형  : STR_PDWINDEX
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:05:53
//
STR_PDWINDEX *CKPulExt::GetFrqAoaGroupedPdwIndex()
{
	return m_pKnownSigAnal->GetFrqAoaGroupedPdwIndex();
}


//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CKPulExt::CalPRIRange
//!	\author  조철희
//!	\param	 pSeg	인자형태 STR_PULSE_TRAIN_SEG *
//!	\param	 priMean	인자형태 UINT
//!	\param	 dtoa_count	인자형태 UINT
//!	\return	 void
//! \version 1.0
//! \date		 2006-07-19 13:51:48
//! \warning
//
void CKPulExt::CalPRIRange( STR_PULSE_TRAIN_SEG *pSeg, _TOA priMean, UINT dtoa_count )
{
	m_pKnownSigAnal->CalPRIRange( pSeg, priMean, dtoa_count );
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CKPulExt::MakeDtoaHistogram
//! \author   조철희
//! \param		pPdwIndex	인자형태 PDWINDEX *
//! \param	  count	인자형태 int
//! \param	  pRange	인자형태 STR_MINMAX *
//! \return   void
//! \version  1.37
//! \date     2006-07-27 17:27:00
//! \warning
//
void CKPulExt::MakeDtoaHistogram( PDWINDEX *pPdwIndex, int count, STR_MINMAX_TOA *pRange )
{
	m_pKnownSigAnal->MakeDtoaHistogram( pPdwIndex, count, pRange );
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    *CSPulExt::GetDtoaHist
//! \author   조철희
//! \return   STR_DTOA_HISTOGRAM
//! \version  1.37
//! \date     2006-07-28 13:22:07
//! \warning
//
STR_DTOA_HISTOGRAM *CKPulExt::GetDtoaHist()
{
	return m_pKnownSigAnal->GetDtoaHist();
}


//////////////////////////////////////////////////////////////////////////
/*! \brief    CKPulExt::GetCoPdw
		\author   조철희
		\return   int
		\version  0.0.57
		\date     2008-11-11 21:40:41
		\warning
*/
int CKPulExt::GetCoPdw()
{
	return m_pKnownSigAnal->GetCoPdw();
}


/**
 * @brief CKPulExt::CheckHarmonic
 * @param priMean1
 * @param priMean2
 * @param uiThreshold
 * @return
 */
UINT CKPulExt::CheckHarmonic(_TOA priMean1, _TOA priMean2, _TOA uiThreshold )
{
    return m_pKnownSigAnal->CheckHarmonic( priMean1, priMean2, uiThreshold );
}


/**
 * @brief     ClearAllMark
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-01-05, 15:56
 * @warning
 */
void CKPulExt::ClearAllMark()
{
    memset( & m_pMARK[0], 0, sizeof( m_pKnownSigAnal->MARK ) );
}
