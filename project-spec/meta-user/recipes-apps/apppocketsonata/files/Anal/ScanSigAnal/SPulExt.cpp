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

/**
 * @brief     CSPulExt
 * @param     void * pParent
 * @param     unsigned int uiCoMaxPdw
 * @return    
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-10-23 10:15:56
 * @warning
 */
CSPulExt::CSPulExt( void *pParent, unsigned int uiCoMaxPdw, const char *pThreadName ) : CPulExt(uiCoMaxPdw, pThreadName )
{

    SetAnalType( enSCN_ANAL );

	m_pScanSigAnal = ( CScanSigAnal * ) pParent;

	m_uiMaxPdw = uiCoMaxPdw;

    INIT_ANAL_VAR_(m_pScanSigAnal)
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
	m_uinoEMT = m_pScanSigAnal->GetNoEMT();
	m_uinoCh = m_pScanSigAnal->GetScanNoCh();

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
    CPulExt::ExtractForKnownPRI( m_pScnAet );

    CPulExt::PulseExtract();

}

/**
 * @brief     DiscardStablePT
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-09-04 20:58:43
 * @warning
 */
void CSPulExt::DiscardStablePT()
{
    STR_PULSE_TRAIN_SEG *pSeg;

    if( m_uiCoSeg == _spZero ) {

    }
    else {
        //STR_PDWINDEX *pGrPdwIndex = GetFrqAoaGroupedPdwIndex();

        pSeg = GetPulseSeg();
        ClearAllMark();
        //memset( m_pMARK, 0, sizeof(USHORT)*pGrPdwIndex->count );

        // 단일 규칙성 펄스열과 펄스열이 추출하지 않을때는 제거하지 않는다.
        if (m_uiCoSeg == _spOne) {
            MarkToPDWIndex(&pSeg[0], enEXTRACT_MARK);
            m_uiCoSeg = 0;
        }
        else {
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
    }

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

/**
 * @brief     GetDtoaHist
 * @return    STR_DTOA_HISTOGRAM *
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-07-28 13:21:31
 * @warning
 */
STR_DTOA_HISTOGRAM *CSPulExt::GetDtoaHist()
{
	// NULL 함수
	return NULL;
}

/**
 * @brief     PDW 개수를 리턴한다.
 * @return    unsigned int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2008-11-11 21:42:36
 * @warning
 */
unsigned int CSPulExt::GetCoPdw()
{
	return m_pScanSigAnal->GetCoPDW();
}
