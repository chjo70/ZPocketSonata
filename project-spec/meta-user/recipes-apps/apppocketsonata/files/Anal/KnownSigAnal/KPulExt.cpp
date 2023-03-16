// KPulExt.cpp: implementation of the CKPulExt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../OFP_Main.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "KnownSigAnal.h"
#include "KPulExt.h"


#include "../../Include/globals.h"

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
CKPulExt::CKPulExt( void *pParent, unsigned int uiCoMaxPdw ) : CPulExt(uiCoMaxPdw)
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

    m_CoPulseTrains = 0;

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

void CKPulExt::ExtractPulseTrainByLibrary(vector<SRadarMode *> *pVecMatchRadarMode)
{
    UINT i;

    STR_PRI_RANGE_TABLE extRange;

    SRadarMode *pRadarMode;

    //ClearAllMark();
    //memset( m_pMARK, 0, sizeof( m_pNewSigAnal->MARK ) );

    STR_PULSE_TRAIN_SEG *pSeg;

    vector <SRadarMode_Sequence_Values>::iterator iter;

    if (pVecMatchRadarMode->size() > 0) {
        pRadarMode = pVecMatchRadarMode->at(0);

        pSeg = GetPulseSeg();
        for (i = 0; i < pVecMatchRadarMode->size(); ++i) {
            switch (pRadarMode->ePRI_Type) {
            case RadarModePRIType::enumStable:
                extRange.tMinPRI = ITOAusCNV(pRadarMode->fPRI_TypicalMin);
                extRange.tMaxPRI = ITOAusCNV(pRadarMode->fPRI_TypicalMax);
                ExtractStablePT(&extRange, 0);
                break;

            case RadarModePRIType::enumDwellSWITCH:
                for (iter = pRadarMode->vecRadarMode_PRISequenceValues.begin(); iter != pRadarMode->vecRadarMode_PRISequenceValues.end(); ++iter) {
                    extRange.tMinPRI = ITOAusCNV((*iter).f_Min);
                    extRange.tMaxPRI = ITOAusCNV((*iter).f_Max);
                    if (TRUE == ExtractDwellRefPT(pSeg, &extRange)) {
                        ++m_uiCoSeg;

                        ++pSeg;
                    }

                }
                break;

            case RadarModePRIType::enumJITTER:
            case RadarModePRIType::enumSTAGGER:
            case RadarModePRIType::enumPATTERN:
                extRange.tMinPRI = ITOAusCNV(pRadarMode->fPRI_TypicalMin);
                extRange.tMaxPRI = ITOAusCNV(pRadarMode->fPRI_TypicalMax);
                ExtractJitterPT(&extRange, UINT_MAX, _sp.cm.Rpc, TRUE, enJITTER_MARK, TRUE);
                break;

            default:
                break;
            }

            ++pRadarMode;
        }
    }

}


/**
 * @brief     PulseExtract
 * @param     vector<SRadarMode * > * pVecMatchRadarMode
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-27, 16:33
 * @warning
 */
void CKPulExt::PulseExtract(vector<SRadarMode *> *pVecMatchRadarMode)
{
    PrintFunction

    /*! \todo	하나의 그룹화에서는 펄스열 인덱스를 최기화해서 펄스열 자원을 활용할수 있게 한다.*/
    Init();

    ExtractPulseTrainByLibrary(pVecMatchRadarMode);

#ifdef _EXTRACT_PULSE_METHOD1_
    // 규칙성 펄스열을 먼저 추출하고서 나머지 잔여 펄스를 불규칙성 펄스열로 추출하는 것을 말함.
    PulseExtract(STEP_WIDE);

#elif defined( _EXTRACT_PULSE_METHOD2_ )
    // 펄스열 추출 간격을 중간영역 까지 규칙성 펄스열을 먼저 추출하고서 나머지 잔여 펄스열에 대해서
    // 불규칙성 펄스열로 추출한다. 그리고 나머지 추출 간격을 마찬가지 방법으로 한다.
    PulseExtract(STEP1);
    PulseExtract(STEP2);

#elif defined( _EXTRACT_PULSE_METHOD3_ )

    // 규칙성 펄스열의 기준 PRI 값을 찾는다.
    FindRefStable();

    // 기준 PRI 로 펄스열 추출
    ExtractRefStable();

    m_nRefSeg = m_uiCoSeg;

    // 모든 펄스열을 초기화한 상태에서 불규칙성 펄스열을 추출하도록 한다.
    memset(MARK, 0, sizeof(MARK));

    // 규칙성 펄스열의 기준 PRI 값을 찾는다.
    ExtractJitterPT();

#elif defined( _EXTRACT_PULSE_METHOD4_ )

    //////////////////////////////////////////////////////////////////////////
    // 규칙성 펄스열 찾기
    m_uiStart_pri_level = 0;
    m_uiEnd_pri_level = MAX_PRI_RANGE - 1;

    m_uiRefStartSeg = m_uiCoSeg;

    // 규칙성 펄스열의 기준 PRI 값을 찾는다. 모든 전 구간에서 찾는다.
    FindRefStable();

    // 기준 PRI 로 펄스열 추출
    ExtractRefStable();

    // 펄스 개수가 작거나 펄스열의 마크가 DELETE_SEG 일때 버린다.
    // 펄스열 저장소를 정리한다.
    CleanPulseTrains(nRefSeg, m_uiCoSeg);

    // 규칙성 펄스열을 찾은 펄스열 인덱스
    m_uiRefEndSeg = m_uiCoSeg;

    memset(MARK, 0, sizeof(MARK));

    //////////////////////////////////////////////////////////////////////////
    // 불규칙성 펄스열 찾기
    //
    // 펄스열 구간마다 불규칙성 펄스열과 불규칙성 펄스열을 같이 추출한다.
    // 펄스열은 각 단계마다 규칙성 펄스열과 불규칙성 펄스열을 동시에 수행한다.
    //-- 조철희 2005-12-09 16:11:27 --//

    int nExtSeg = m_uiCoSeg;

    for (i = 0; i < MAX_PRI_RANGE; ++i) {
        PulseExtract(i);
    }

    /*! \bug  기본 규칙성 펄스열에서 추출한 펄스열과 펄스열 추출후의 펄스열 끼리
                        비교해서 유사 펄스열이면, 기본 규칙성 펄스열을 제거한다.
            \date 2006-05-19 17:59:24, 조철희
    */
    DiscardPulseTrain(nRefSeg, nExtSeg);

#elif defined( _EXTRACT_PULSE_METHOD5_ )
    SetRefStartSeg();

    //     if( GetPulseStat() == STAT_CW && false ) {
    //         // MakeCWPulseTrain();
    //     }
    //     else 
    {
        //////////////////////////////////////////////////////////////////////////
        // 1차 펄스열 추출

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

        //////////////////////////////////////////////////////////////////////////
        // 불규칙성 펄스열 찾기
        //
        // 펄스열 구간마다 규칙성 펄스열과 불규칙성 펄스열을 같이 추출한다.
        // 펄스열은 각 단계마다 규칙성 펄스열과 불규칙성 펄스열을 동시에 수행한다.
        //-- 조철희 2005-12-09 16:11:27 --//
        ExtractJitter(_STABLE + _JITTER_RANDOM);

        // 펄스열의 인덱스를 조사해서 겹쳐져 있으면 그 중 한개를 버린다.
        DiscardPulseTrain();

        //////////////////////////////////////////////////////////////////////////
        // 2차 펄스열 추출
        //  [7/2/2007 조철희]
        //-
        if (MustDo2ndPulseExtract() == TRUE) {
            //Printf( "\n 2-Pass" );
            ClearAllMark();
            MarkStablePulseTrain();

            ResetJitterSeg();
            ExtractJitter(_JITTER_RANDOM);
        }
    }

#else
#pragma message( "펄스열 추적 알고리즘을 선택해야 합니다." __FILE__ )

#endif

    m_CoPulseTrains = m_uiCoSeg;
    m_uiCoRefSeg = m_uiCoSeg;

    CPulExt::PulseExtract();

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
				if( CheckHarmonic( pSeg1, pSeg2 ) != 0 && OverlappedSeg( pSeg1, pSeg2 ) == true )
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

    switch( m_pTrkAet->ucPRIType ) {
		case _STABLE :
            extRange.tMinPRI = ITOAusCNV( m_pTrkAet->fPRIMin ) - STABLE_MARGIN;
            extRange.tMaxPRI = ITOAusCNV( m_pTrkAet->fPRIMax ) + STABLE_MARGIN;
			ExtractStablePT( & extRange, TRUE );
			break;

		case _STAGGER :
			// 추출할 펄스열의 범위폭을 계산한다.
            extRange.tMinPRI = ITOAusCNV( m_pTrkAet->fPRIMin ) - STABLE_MARGIN;
            extRange.tMaxPRI = ITOAusCNV( m_pTrkAet->fPRIMax ) + STABLE_MARGIN;
			ExtractJitterPT( & extRange, UINT32_MAX, 3, TRUE );

			/*! \bug  추출하고자할 PRI 평균값을 중심으로 지터열을 추출하게 한다.
			    \date 2006-06-28 00:39:34, 조철희
			*/
            ExtractTrackPT( ITOAusCNV(m_pTrkAet->fPRIMean), FDIV( m_pTrkAet->fPRIJitterRatio, 100 ) );
			break;

		case _DWELL :
            for( i=0 ; i < m_pTrkAet->ucPRIPositionCount ; ++i ) {
                extRange.tMinPRI = ITOAusCNV( m_pTrkAet->fPRISeq[i] ) - ( 2 * STABLE_MARGIN );
                extRange.tMaxPRI = ITOAusCNV( m_pTrkAet->fPRISeq[i] ) + ( 2 * STABLE_MARGIN );
                ExtractDwellRefPT( pSeg, & extRange );
			}
			ExtractRefStable();
			break;

		case _JITTER_RANDOM :
			/*! \bug  규칙성 펄스열을 찾아서 제거한다. 그러나 겹쳐진 펄스열들은 삭제하지 않는다.
			    \date 2006-09-04 20:56:25, 조철희
			*/
			// 지터열 추출 마진 설정
            diff = (int) UDIV( m_pTrkAet->fPRIMean * ( m_pTrkAet->fPRIJitterRatio+EXTRACT_JITTER_MARGIN ), 200 );
            extRange.tMinPRI = (_TOA) max( (int)(m_pTrkAet->fPRIMean - diff), 2 );
            extRange.tMaxPRI = ITOAusCNV( m_pTrkAet->fPRIMean ) + (_TOA) diff;
			ExtractStablePT( & extRange, TRUE );
			DiscardStablePT();

			/*! \bug  KHP RWR의 위협신호 발생기에서 최대 변이가 지터율로 발생함.
								이런 지터 신호가 정말 있는지 궁금. 실제환경에서 지터 신호를 좀더 수집 해봐야 하겠음.
								Stable은 기존대로 추출하며 Jitter열은 위협 신호 발생기를 고려해서 좀더 추출하게 함.
			    \date 2008-10-25 17:01:53, 조철희
			*/
            diff = (int) UDIV( m_pTrkAet->fPRIMean * ( m_pTrkAet->fPRIJitterRatio+20 ), 200 );
            extRange.tMinPRI = (_TOA) max( (int)(m_pTrkAet->fPRIMean - diff), 2 );
            extRange.tMaxPRI = ITOAusCNV( m_pTrkAet->fPRIMean ) + (_TOA) diff;
			// 추출할 펄스열의 범위폭을 계산한다.
			ExtractJitterPT( & extRange, UINT32_MAX, 3, TRUE );

			// D:\RSA-조철희\소나타 ES TFT\해상 신호\A21-Check_Pulse_Mege\chirp_up.pdw 인 
			// 하노닉 레이더 신호(?) 때문에 
			// 2배의 PRI도 추출하도록 한다.
			extRange.tMinPRI = 2 * extRange.tMinPRI;
			extRange.tMaxPRI = 2 * extRange.tMaxPRI;
			ExtractJitterPT( & extRange, UINT32_MAX, 3, TRUE );
			break;

		case _JITTER_PATTERN :
			// 추출할 펄스열의 범위폭을 계산한다.
			diff = 200;
			//-- 조철희 2006-02-22 09:59:34 --//
            extRange.tMinPRI = ITOAusCNV( m_pTrkAet->fPRIMin ) - (_TOA) diff;
            extRange.tMaxPRI = ITOAusCNV( m_pTrkAet->fPRIMax ) + (_TOA) diff;
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
            MarkToPDWIndex( & pSeg[0], enEXTRACT_MARK );
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
void CKPulExt::MakeDtoaHistogram( PDWINDEX *pPdwIndex, unsigned int uiCount, STR_MINMAX_TOA *pRange )
{
	m_pKnownSigAnal->MakeDtoaHistogram( pPdwIndex, uiCount, pRange );
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
unsigned int CKPulExt::GetCoPdw()
{
	return m_pKnownSigAnal->GetCoPdw();
}

/**
 * @brief     하모닉을 체크한다.
 * @param     _TOA priMean1
 * @param     _TOA priMean2
 * @param     _TOA uiThreshold
 * @return    UINT
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-12-08 13:31:33
 * @warning
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
