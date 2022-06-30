// SPulExt.cpp: 스캔 펄스열 추출 클래스 입니다.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "../OFP_Main.h"

#include <stdio.h>

#include "ScanSigAnal.h"
#include "SGroup.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSPulExt::CSPulExt( void *pParent, unsigned int uiCoMaxPdw ) : CPulExt(uiCoMaxPdw)
{
	m_pScanSigAnal = ( CScanSigAnal * ) pParent;

	m_uiMaxPdw = uiCoMaxPdw;

    INIT_ANAL_VAR_(m_pScanSigAnal);
}

/**
 * @brief     ~CSPulExt
 * @return    
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-18, 15:19
 * @warning
 */
CSPulExt::~CSPulExt()
{

}

/**
 * @brief     스캔 객체의 초기화를 수행한다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2006-08-29 15:17:18
 * @warning
 */
void CSPulExt::Init()
{
	m_noEMT = m_pScanSigAnal->GetNoEMT();
	m_noCh = m_pScanSigAnal->GetScanNoCh();

    m_uiAnalSeg = m_uiCoSeg;

    m_pScnAet = m_pScanSigAnal->GetScnAET();

	CPulExt::Init();
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : *CSPulExt::GetFrqAoaGroupedPdwIndex
// 반환되는 형  : STR_PDWINDEX
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-15 13:38:06
//
STR_PDWINDEX *CSPulExt::GetFrqAoaGroupedPdwIndex()
{
	return m_pScanSigAnal->GetFrqAoaGroupedPdwIndex();
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CSPulExt::KnownPulseExtract
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-15 13:37:52
//
void CSPulExt::KnownPulseExtract()
{
	int i;
	int diff;
    //STR_PRI *pPri;
	STR_PRI_RANGE_TABLE extRange;

    STR_PULSE_TRAIN_SEG *pSeg;

    pSeg = GetPulseSeg();

	// 타입에 따라서 펄스열 추출을 달리한다.
    switch( m_pScnAet->iPRIType ) {
		case _STABLE :
            extRange.tMinPRI = ITOAusCNV( m_pScnAet->fPRIMin ) - STABLE_MARGIN;
            extRange.tMaxPRI = ITOAusCNV( m_pScnAet->fPRIMax ) + STABLE_MARGIN;
            ExtractStablePT( & extRange, TRUE );
            break;

		case _STAGGER :
            // 추출할 펄스열의 범위폭을 계산한다.
            extRange.tMinPRI = ITOAusCNV( m_pScnAet->fPRIMin ) - STABLE_MARGIN;
            extRange.tMaxPRI = ITOAusCNV( m_pScnAet->fPRIMax ) + STABLE_MARGIN;
            ExtractJitterPT( & extRange, UINT_MAX, 3, TRUE );

            /*! \bug  추출하고자할 PRI 평균값을 중심으로 지터열을 추출하게 한다.
                \date 2006-06-28 00:39:34, 조철희
            */
            ExtractTrackPT( ITOAusCNV(m_pScnAet->fPRIMean), FDIV( m_pScnAet->fPRIJitterRatio, 100 ) );
			break;

		case _DWELL :
            for( i=0 ; i < m_pScnAet->iPRIPositionCount ; ++i ) {
                extRange.tMinPRI = ITOAusCNV(m_pScnAet->fPRISeq[i]) - ( 2 * STABLE_MARGIN );
                extRange.tMaxPRI = ITOAusCNV(m_pScnAet->fPRISeq[i]) + ( 2 * STABLE_MARGIN );
                ExtractDwellRefPT( pSeg, & extRange );
            }
            ExtractRefStable();
			break;

        case _JITTER_RANDOM :
            /*! \bug  규칙성 펄스열을 찾아서 제거한다. 그러나 겹쳐진 펄스열들은 삭제하지 않는다.
                \date 2006-09-04 20:56:25, 조철희
            */
            // 지터열 추출 마진 설정
            diff = UDIV( m_pScnAet->fPRIMean * ( m_pScnAet->fPRIJitterRatio+EXTRACT_JITTER_MARGIN ), 200 );
            extRange.tMinPRI = _max( (int)(m_pScnAet->fPRIMean - diff), 2 );
            extRange.tMaxPRI = ITOAusCNV( m_pScnAet->fPRIMean + diff );
            ExtractStablePT( & extRange, TRUE );
            DiscardStablePT();

            /*! \bug  KHP RWR의 위협신호 발생기에서 최대 변이가 지터율로 발생함.
                                이런 지터 신호가 정말 있는지 궁금. 실제환경에서 지터 신호를 좀더 수집 해봐야 하겠음.
                                Stable은 기존대로 추출하며 Jitter열은 위협 신호 발생기를 고려해서 좀더 추출하게 함.
                \date 2008-10-25 17:01:53, 조철희
            */
            diff = UDIV( m_pScnAet->fPRIMean * ( m_pScnAet->fPRIJitterRatio+20 ), 200 );
            extRange.tMinPRI = _max( (int)(m_pScnAet->fPRIMean - diff), 2 );
            extRange.tMaxPRI = ITOAusCNV( m_pScnAet->fPRIMean + diff );
            // 추출할 펄스열의 범위폭을 계산한다.
            ExtractJitterPT( & extRange, UINT_MAX, 3, TRUE );

            // D:\RSA-조철희\소나타 ES TFT\해상 신호\A21-Check_Pulse_Mege\chirp_up.pdw 인
            // 하노닉 레이더 신호(?) 때문에
            // 2배의 PRI도 추출하도록 한다.
            extRange.tMinPRI = 2 * extRange.tMinPRI;
            extRange.tMaxPRI = 2 * extRange.tMaxPRI;
            ExtractJitterPT( & extRange, UINT_MAX, 3, TRUE );
            break;

        case _JITTER_PATTERN :
            // 추출할 펄스열의 범위폭을 계산한다.
            diff = 200;
            //-- 조철희 2006-02-22 09:59:34 --//
            extRange.tMinPRI = ITOAusCNV( m_pScnAet->fPRIMin - diff );
            extRange.tMaxPRI = ITOAusCNV( m_pScnAet->fPRIMax + diff );
            ExtractPatternPT( & extRange, 3, TRUE );
            break;

        default:
            break;
    }

	// 추출한 펄스열을 저장
    //SaveScanPulse();

    CPulExt::PulseExtract();

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
void CSPulExt::DiscardStablePT()
{
    //int i;//, j;
    STR_PULSE_TRAIN_SEG *pSeg; //, *pSeg2;

    if( m_uiCoSeg == 0 ) {
        return;
    }

    //STR_PDWINDEX *pGrPdwIndex = GetFrqAoaGroupedPdwIndex();

    pSeg = GetPulseSeg();
    ClearAllMark();
    //memset( m_pMARK, 0, sizeof(USHORT)*pGrPdwIndex->count );

    // 단일 규칙성 펄스열과 펄스열이 추출하지 않을때는 제거하지 않는다.
    if( m_uiCoSeg == 1 ) {
        MarkToPDWIndex( & pSeg[0], EXTRACT_MARK );
        m_uiCoSeg = 0;
        return;
    }

    /*! \todo	스태거열을 찾아서 제거해야 한다. */

    // Stagger 펄스열로 의심이 가는 펄스열들끼기 찾아서 제거시킨다.
    // pSeg1 = pSeg + m_nAnalSeg;
//     for( i=m_nAnalSeg ; i < m_CoSeg ; ++i ) {
//         pSeg2 = pSeg + i + 1;
//         for( j=i+1 ; j < m_CoSeg ; ++j ) {
// 
//         }
//     }

}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CSPulExt::SaveScanPulse
//! \author   조철희
//! \return   void
//! \version  1.37
//! \date     2006-08-24 15:49:05
//! \warning
//
void CSPulExt::SaveScanPulse()
{
	//int i;

	//UINT count;
	//UINT *pScanTOA, *pScanPA;

	//STR_SCANPT *pScanPT;
	//STR_PDWPARAM *pPdwParam;
	//UINT *pParamIndex;

	CPulExt::SavePdwParamIndex();

//	pPdwParam = GetPdwParam();
//	pParamIndex = pPdwParam->pParam;

//	pScanPT = & stScanPt; // & stScanPt[m_noCh];
//	pScanPA = & pScanPT->pa[0];
//	pScanTOA = & pScanPT->toa[0];
//	count = 0;
//	for( i=0 ; i < m_nMaxPdw ; ++i ) {
//		if( pParamIndex[i] == 1 ) {
//			*pScanTOA++ = TOA[i];
//			*pScanPA++ = PA[i];
//			++ count;
//		}
//	}

	//pScanPT->co = count;

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CSPulExt::SaveScanPulse
		\author   조철희
		\param    pPdwIndex 인자형태 STR_PDWINDEX *
		\return   void
		\version  0.0.51
		\date     2008-10-11 13:08:03
		\warning
*/
void CSPulExt::SaveScanPulse( STR_PDWINDEX *pPdwIndex )
{
// 	int i, count, pdw_count;
// 
// 	PDWINDEX *pIndex;
// 	STR_SCANPT *pScanPT;
// 	UINT *pScanTOA, *pScanPA;

//	pScanPT = & stScanPt; // & stScanPt[m_noCh];
//	pScanPA = & pScanPT->pa[0];
//	pScanTOA = & pScanPT->toa[0];
//	pIndex = pPdwIndex->pIndex;
//	pdw_count = pPdwIndex->count;
//	for( i=count=0 ; i < m_nMaxPdw && i < pdw_count ; ++i ) {
//		int idx;

//		idx = *pIndex++;
//		*pScanTOA++ = TOA[idx];
//		*pScanPA++ = PA[idx];
//		++ count;

//	}

	//pScanPT->co = count;

}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CSPulExt::CalPRIRange
//!	\author  조철희
//!	\param	 pSeg	인자형태 STR_PULSE_TRAIN_SEG *
//!	\param	 priMean	인자형태 UINT
//!	\param	 dtoa_count	인자형태 UINT
//!	\return	 void
//! \version 1.0
//! \date		 2006-07-06 14:12:51
//! \warning
//
void CSPulExt::CalPRIRange( STR_PULSE_TRAIN_SEG *pSeg, _TOA priMean, UINT dtoa_count )
{
	// NULL 함수
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CSPulExt::MakeDtoaHistogram
//! \author   조철희
//! \param		pPdwIndex	인자형태 PDWINDEX *
//! \param	  count	인자형태 int
//! \param	  pRange	인자형태 STR_MINMAX *
//! \return   void
//! \version  1.37
//! \date     2006-07-27 17:27:00
//! \warning
//
void CSPulExt::MakeDtoaHistogram( PDWINDEX *pPdwIndex, unsigned int uiCount, STR_MINMAX_TOA *pRange )
{
	// NULL 함수
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    *CSPulExt::GetDtoaHist
//! \author   조철희
//! \return   STR_DTOA_HISTOGRAM
//! \version  1.37
//! \date     2006-07-28 13:21:31
//! \warning
//
STR_DTOA_HISTOGRAM *CSPulExt::GetDtoaHist()
{
	// NULL 함수
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CSPulExt::GetCoPdw
		\author   조철희
		\return   int
		\version  0.0.57
		\date     2008-11-11 21:42:36
		\warning
*/
int CSPulExt::GetCoPdw()
{
	return m_pScanSigAnal->GetCoPdw();
}
