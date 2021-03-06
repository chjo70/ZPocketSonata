﻿// NPulExt.cpp: implementation of the NPulExt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"


#include "../OFP_Main.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "NewSigAnal.h"
#include "NPulExt.h"
#include "NewSigAnal.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt
// 반환되는 형  : CNPulExt::CNPulExt(void *pParent, int coMaxPdw) :
// 함 수 인 자  : void *pParent
// 함 수 인 자  : int coMaxPdw
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-23 10:03:29
//
CNPulExt::CNPulExt( void *pParent, int coMaxPdw ) : CPulExt( coMaxPdw )
{
    m_pNewSigAnal = ( CNewSigAnal * ) pParent;

    m_CoPulseTrains = 0;

    INIT_ANAL_VAR_(m_pNewSigAnal)
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CNPulExt::~CNPulExt
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-25 13:31:47
//
CNPulExt::~CNPulExt()
{

}

//////////////////////////////////////////////////////////////////////
//
//! \brief    클래스를 초기화한다.
//! \author   조철희
//! \return   void
//! \version  1.37
//! \date     2006-08-29 09:34:26
//! \warning
//
void CNPulExt::Init()
{
    m_CoPulseTrains = 0;

    m_enBandWidth = m_pNewSigAnal->GetBandWidth();

    /*! \bug  하위 그룹에서 초기화하는 것으로 수정함.
        \date 2008-07-30 13:25:17, 조철희
    */
    CPulExt::Init();

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    탐지 펄스열 추출의 메인 흐름도이다.

                            1차 추출과 2차 추출로 나뉘어 펄스열을 추출한다. 1차 추출에서는
                            모든 입력 펄스열에 대해서 펄스열을 추출한다. 그리고 2차 추출에서는
                            규칙성 펄스열을 제거한 나머지 펄스열에 대해서 펄스열을 추출하도록 한다.
        \author   조철희
        \return   void	없음.
        \version  1.37
        \date     2006-08-23 22:25:42
        \warning
*/
void CNPulExt::PulseExtract( UINT uiCoKnownRadarMode, SRadarMode **pRadarMode )
{
    PrintFunction

    /*! \todo	하나의 그룹화에서는 펄스열 인덱스를 최기화해서 펄스열 자원을 활용할수 있게 한다.*/
    Init();

    if( uiCoKnownRadarMode == 0 ) {
#ifdef _EXTRACT_PULSE_METHOD1_
        // 규칙성 펄스열을 먼저 추출하고서 나머지 잔여 펄스를 불규칙성 펄스열로 추출하는 것을 말함.
        PulseExtract( STEP_WIDE );

#elif defined( _EXTRACT_PULSE_METHOD2_ )
        // 펄스열 추출 간격을 중간영역 까지 규칙성 펄스열을 먼저 추출하고서 나머지 잔여 펄스열에 대해서
        // 불규칙성 펄스열로 추출한다. 그리고 나머지 추출 간격을 마찬가지 방법으로 한다.
        PulseExtract( STEP1 );
        PulseExtract( STEP2 );

#elif defined( _EXTRACT_PULSE_METHOD3_ )

        // 규칙성 펄스열의 기준 PRI 값을 찾는다.
        FindRefStable();

        // 기준 PRI 로 펄스열 추출
        ExtractRefStable();

        m_nRefSeg = m_CoSeg;

        // 모든 펄스열을 초기화한 상태에서 불규칙성 펄스열을 추출하도록 한다.
        memset( MARK, 0, sizeof( MARK ) );

        // 규칙성 펄스열의 기준 PRI 값을 찾는다.
        ExtractJitterPT();

#elif defined( _EXTRACT_PULSE_METHOD4_ )

        //////////////////////////////////////////////////////////////////////////
        // 규칙성 펄스열 찾기
        m_Start_pri_level = 0;
        m_End_pri_level = MAX_PRI_RANGE - 1;

        m_nRefStartSeg = m_CoSeg;

        // 규칙성 펄스열의 기준 PRI 값을 찾는다. 모든 전 구간에서 찾는다.
        FindRefStable();

        // 기준 PRI 로 펄스열 추출
        ExtractRefStable();

        // 펄스 개수가 작거나 펄스열의 마크가 DELETE_SEG 일때 버린다.
        // 펄스열 저장소를 정리한다.
        CleanPulseTrains( nRefSeg, m_CoSeg );

        // 규칙성 펄스열을 찾은 펄스열 인덱스
        m_nRefEndSeg = m_CoSeg;

        memset( MARK, 0, sizeof( MARK ) );

        //////////////////////////////////////////////////////////////////////////
        // 불규칙성 펄스열 찾기
        //
        // 펄스열 구간마다 불규칙성 펄스열과 불규칙성 펄스열을 같이 추출한다.
        // 펄스열은 각 단계마다 규칙성 펄스열과 불규칙성 펄스열을 동시에 수행한다.
        //-- 조철희 2005-12-09 16:11:27 --//

        int nExtSeg = m_CoSeg;

        for( i=0 ; i < MAX_PRI_RANGE ; ++i )
            PulseExtract( i );

        /*! \bug  기본 규칙성 펄스열에서 추출한 펄스열과 펄스열 추출후의 펄스열 끼리
                            비교해서 유사 펄스열이면, 기본 규칙성 펄스열을 제거한다.
                \date 2006-05-19 17:59:24, 조철희
        */
        DiscardPulseTrain( nRefSeg, nExtSeg );

#elif defined( _EXTRACT_PULSE_METHOD5_ )

        if( GetPulseStat() == STAT_CW ) {
            MakeCWPulseTrain();
        }
        else {
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
            ExtractJitter( _STABLE + _JITTER_RANDOM );

            // 펄스열의 인덱스를 조사해서 겹쳐져 있으면 그 중 한개를 버린다.
            DiscardPulseTrain();

            //////////////////////////////////////////////////////////////////////////
            // 2차 펄스열 추출
            //  [7/2/2007 조철희]
            //-
            if( MustDo2ndPulseExtract() == TRUE ) {
                //Printf( "\n 2-Pass" );
                ClearAllMark();
                MarkStablePulseTrain();

                ResetJitterSeg();
                ExtractJitter( _JITTER_RANDOM );
            }
        }

#else
        #pragma message( "펄스열 추적 알고리즘을 선택해야 합니다." __FILE__ )

#endif
    }
    else {
        ExtractPulseTrainByLibrary( uiCoKnownRadarMode, pRadarMode );
    }

    m_CoPulseTrains = m_CoSeg;
    m_CoRefSeg = m_CoSeg;

    CPulExt::PulseExtract();

}

/**
 * @brief CNPulExt::ExtractPulseTrainByLibrary
 * @param uiCoKnownRadarMode
 * @param pRadarMode
 */
void CNPulExt::ExtractPulseTrainByLibrary( UINT uiCoKnownRadarMode, SRadarMode **pRadarMode )
{
    UINT i;
    int j;

    STR_PRI_RANGE_TABLE extRange;

    Init();

    ClearAllMark();
    //memset( m_pMARK, 0, sizeof( m_pNewSigAnal->MARK ) );

    STR_PULSE_TRAIN_SEG *pSeg;

    vector <SRadarMode_Sequence_Values>::pointer pVecPRISequenceValues;

    pSeg = GetPulseSeg();
    for( i=0 ; i < uiCoKnownRadarMode ; ++i ) {
        switch( (*pRadarMode)->ePRI_Type ) {
            case RadarModePRIType::enumStable :
                extRange.min_pri = ITOAusCNV( (*pRadarMode)->fPRI_TypicalMin );
                extRange.max_pri = ITOAusCNV( (*pRadarMode)->fPRI_TypicalMax );
                ExtractJitterPT( & extRange, -1, _sp.cm.Rpc, TRUE , JITTER_MARK, TRUE );
                break;

            case RadarModePRIType::enumDwellSWITCH :
                pVecPRISequenceValues = (*pRadarMode)->vecRadarMode_PRISequenceValues.data();
                for( j=0 ; j < (*pRadarMode)->nPRI_NumPositions ; ++j ) {
                    extRange.min_pri = ITOAusCNV( pVecPRISequenceValues->f_Min );
                    extRange.max_pri = ITOAusCNV( pVecPRISequenceValues->f_Max );
                    if( TRUE == ExtractDwellRefPT( pSeg, & extRange ) ) {
                        ++ m_CoSeg;

                        ++ pSeg;
                    }

                    ++ pVecPRISequenceValues;
                }
                break;

            case RadarModePRIType::enumJITTER :
            case RadarModePRIType::enumSTAGGER :
            case RadarModePRIType::enumPATTERN :
                extRange.min_pri = ITOAusCNV( (*pRadarMode)->fPRI_TypicalMin );
                extRange.max_pri = ITOAusCNV( (*pRadarMode)->fPRI_TypicalMax );
                ExtractJitterPT( & extRange, -1, _sp.cm.Rpc, TRUE , JITTER_MARK, TRUE );
                break;

            default :
                break;
        }

        ++ pRadarMode;
    }

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CNPulExt::MarkToPdwIndex
// 반환되는 형  : void
// 함 수 인 자  : PDWINDEX *pPdwIndex
// 함 수 인 자  : int count
// 함 수 인 자  : int mark_type
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-23 10:03:32
//
void CNPulExt::MarkToPdwIndex( PDWINDEX *pPdwIndex, int count, int mark_type )
{
    m_pNewSigAnal->MarkToPdwIndex( pPdwIndex, count, mark_type );

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : *CNPulExt::GetFrqAoaGroupedPdwIndex
// 반환되는 형  : STR_PDWINDEX
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-23 10:03:36
//
UINT CNPulExt::CheckHarmonic(_TOA priMean1, _TOA priMean2, _TOA uiThreshold )
{
    return m_pNewSigAnal->CheckHarmonic( priMean1, priMean2, uiThreshold );

}

STR_PDWINDEX *CNPulExt::GetFrqAoaGroupedPdwIndex()
{
    return m_pNewSigAnal->GetFrqAoaGroupedPdwIndex();

}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CNPulExt::CalPRIRange
//!	\author  조철희
//!	\param	 pSeg	인자형태 STR_PULSE_TRAIN_SEG *
//! \param	 priMean	인자형태 UINT
//! \param	 dtoa_count	인자형태 UINT
//!	\return	 void
//! \version 1.0
//! \date		 2006-07-06 16:56:07
//! \warning
//
void CNPulExt::CalPRIRange( STR_PULSE_TRAIN_SEG *pSeg, _TOA priMean, UINT dtoa_count )
{
    m_pNewSigAnal->CalPRIRange( pSeg, priMean, dtoa_count );

}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CNPulExt::MakeDtoaHistogram
//! \author   조철희
//! \param	  pPdwIndex	인자형태 PDWINDEX *
//! \param	  count	인자형태 int
//! \param	  pRange	인자형태 STR_MINMAX_TOA *
//! \return   void
//! \version  1.37
//! \date     2006-07-27 17:16:36
//! \warning
//
void CNPulExt::MakeDtoaHistogram( PDWINDEX *pPdwIndex, int count, STR_MINMAX_TOA *pRange )
{
    m_pNewSigAnal->MakeDtoaHistogram( pPdwIndex, count, pRange );
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    *CNPulExt::GetDtoaHist
//! \author   조철희
//! \return   STR_DTOA_HISTOGRAM
//! \version  1.37
//! \date     2006-07-28 13:19:17
//! \warning
//
STR_DTOA_HISTOGRAM *CNPulExt::GetDtoaHist()
{
    return m_pNewSigAnal->GetDtoaHist();
}


//////////////////////////////////////////////////////////////////////////
/*! \brief    CNPulExt::GetCoPdw
        \author   조철희
        \return   int
        \version  0.0.57
        \date     2008-11-11 21:41:20
        \warning
*/
int CNPulExt::GetCoPdw()
{
    return m_pNewSigAnal->GetCoPdw();
}

int CNPulExt::GetPulseStat()
{
    return m_pNewSigAnal->GetPulseStat();
}

void CNPulExt::ClearAllMark()
{
    memset( & m_pMARK[0], 0, sizeof( m_pNewSigAnal->MARK ) );
}
