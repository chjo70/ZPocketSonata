// MakeAET.cpp: implementation of the CMakeAET class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#ifdef _WIN32
// PC용 상위 클래스에 전달하기 위한 선언
//#include "../../A50SigAnal/stdafx.h"

#endif

//#include <typeinfo>
#include <iostream>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#if defined(_ELINT_) || defined(_XBAND_)
#include "../OFP_Main.h"

#elif defined(_POCKETSONATA_) || defined(_712_)
#include "../Identify/ELUtil.h"
#include "../EmitterMerge/ELMsgDefn.h"

#else
#endif

#include "MakeAET.h"

#include "../../Include/globals.h"

#include "../EmitterMerge/ELStringDefn.h"

#include "../Identify/ELUtil.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



extern int intparamCompare( const void *arg1, const void *arg2 );
extern int lliparamCompare( const void *arg1, const void *arg2 );


/**
 * @brief     최빈값 계산을 수행한다.
 * @param     STR_EMITTER * pEmitter
 * @param     T * pData
 * @param     T mean
 * @return    T
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-06-30 10:37:34
 * @warning
 */
template <typename T>
T CalcMode( STR_EMITTER *pEmitter, T *pData, T mean )
{
    unsigned int i;

    size_t szSize;

    T tRet = 0;
    T *pArray, *pArrayTemp;

	szSize = CCommonUtils::CheckMultiplyOverflow((int) sizeof(T), (int) pEmitter->stPDW.uiCount);

	if(szSize != 0 ) {
		pArray = ( T * ) malloc( szSize );

		if (pArray != NULL) {
			// 초기화 : 데이터 복사가 발생하지 않은 경우가 있음.
			*pArray = 0;

			pArrayTemp = pArray;

			PDWINDEX *pPdwIndex = pEmitter->stPDW.pIndex;
			for (i = 0; i < pEmitter->stPDW.uiCount; ++i) {
				*pArrayTemp++ = pData[*pPdwIndex++];

			}

			szSize = pEmitter->stPDW.uiCount;

			// 1. 정렬하기
			if (typeid(T) == typeid(_TOA)) {
				qsort(pArray, szSize, sizeof(T), lliparamCompare);
			}
			else {
				qsort(pArray, szSize, sizeof(T), intparamCompare);
			}

			// 2. 최빈수 구하기
			int iMaxCount = 1, iCount = 1;

			tRet = *pArray;
			for (i = 1; i < pEmitter->stPDW.uiCount; ++i) {
				if (pArray[i] == pArray[i - 1]) {
					++iCount;
				}
				else {
					if (iCount > iMaxCount) {
						iMaxCount = iCount;
						tRet = pArray[i - 1];
					}
				}

			}

			// 최빈수 개수가 1 인 경우에는 평균값으로 최빈수 값을 정한다.
			if (iCount == _spOne) {
				tRet = mean;
			}

			free(pArray);
		}
		else {
			tRet = mean;
		}
    }
    else {
        tRet = mean;
    }

    return tRet;

}

/**
 * @brief     객체 생성시 멤버 변수를 초기화 한다.
 * @param     unsigned int uiCoMaxPdw
 * @return
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2005-09-30 16:33:17
 * @warning
 */
CMakeAET::CMakeAET( unsigned int uiCoMaxLOB, const char *pThreadName )
{
    //bool bRet=true;

    SetThreadName( pThreadName );

    // 고정형 주파수 및 규칙성 펄스열 마진
    float *pFvalue = g_pTheSysConfig->GetMargin();
    m_tStableMargin = ITOAusCNV( pFvalue[1] );

    unsigned int uiValue = g_pTheSysConfig->GetMaxCountOfLOB();
    m_uiCoMaxLOB = min( uiCoMaxLOB, uiValue );
    m_uiCoMaxLOB = min( m_uiCoMaxLOB, _DEFAULT_MAX_COUNT_OF_LOB_ );

    m_uiCoAnalPdw = 0;

    // LOB 데이터 메모리 할당
    m_vecLOBData.reserve( m_uiCoMaxLOB );
    // LOB - PDW 데이터 메모리 할당
    m_vecLOB2PDWData.reserve( m_uiCoMaxLOB );

#if 0
    STR_EMITTER strEmitter;

    _spOneMicrosec = FDIV( 1000, POCKETSONATA::_toaRes );

    strEmitter.uiStagDwellLevelCount = 4;
    strEmitter.tStaggerDwellLevel[0] = IMUL( 100, _spOneMicrosec );
    strEmitter.tStaggerDwellLevel[1] = IMUL( 120, _spOneMicrosec );
    strEmitter.tStaggerDwellLevel[2] = IMUL( 100, _spOneMicrosec );
    strEmitter.tStaggerDwellLevel[3] = IMUL( 100, _spOneMicrosec );
    TSortLevel<_TOA>( strEmitter.uiStagDwellLevelCount, strEmitter.tStaggerDwellLevel );

    strEmitter.tStaggerDwellLevel[0] = IMUL( 99.5, _spOneMicrosec );
    strEmitter.tStaggerDwellLevel[1] = IMUL( 120, _spOneMicrosec );
    strEmitter.tStaggerDwellLevel[2] = IMUL( 100, _spOneMicrosec );
    strEmitter.tStaggerDwellLevel[3] = IMUL( 100, _spOneMicrosec );
    TSortLevel<_TOA>( strEmitter.uiStagDwellLevelCount, strEmitter.tStaggerDwellLevel );

    strEmitter.tStaggerDwellLevel[0] = IMUL( 100, _spOneMicrosec );
    strEmitter.tStaggerDwellLevel[1] = IMUL( 120, _spOneMicrosec );
    strEmitter.tStaggerDwellLevel[2] = IMUL( 99.5, _spOneMicrosec );
    strEmitter.tStaggerDwellLevel[3] = IMUL( 100, _spOneMicrosec );
    TSortLevel<_TOA>( strEmitter.uiStagDwellLevelCount, strEmitter.tStaggerDwellLevel );
#endif

}

/**
 * @brief     소멸자 처리를 수행한다.
 * @return
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2006-01-11 13:48:55
 * @warning
 */
CMakeAET::~CMakeAET()
{

}

/**
 * @brief     신호분석 초기 분석시 초기화 해서 LOB 데이터 등을 초기화 한다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2005-04-26 18:18:35
 * @warning
 */
void CMakeAET::Init()
{

    // 펄스 수집 개수
    m_uiCoPdw = GetColPdw();

    m_iCoLOB = 0;
    m_iAnaledCoLOB = 0;

    m_pEmitter = GetEmitter();
    m_pSeg = GetPulseSeg();

    m_uiCoAnalPdw = 0;

    m_pPdwParam = GetPdwParam();

    //
    m_vecLOBData.clear();
    m_vecLOB2PDWData.clear();

}

/**
 * @brief     가상 에미터를 참고해서 LOB 를 생성합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2005-05-12 19:22:17
 * @warning
 */
void CMakeAET::MakeAET( bool bDBInsert )
{
    int i;
    STR_EMITTER *pEmitter;

    m_iCoEmitter = (int) GetCoEmitter();

    pEmitter = & m_pEmitter[0];


    for( i=0 ; i < m_iCoEmitter ; ++i, ++pEmitter ) {
        if( pEmitter->enMark == NORMAL_EMITTER && m_iCoLOB < (int) m_uiCoMaxLOB ) {
            // 에미터 생성하기
            MakeLOBDataFromEmitter(m_iCoLOB, pEmitter, i );

#ifdef __VXWORKS__
            m_vecLOB2PDWData.push_back( pEmitter->stPDW );
#else
            m_vecLOB2PDWData.emplace_back( pEmitter->stPDW );
#endif

            SetKnownIndexEmitter( (UINT) m_iCoLOB, i );

            // CW 에미터인 경우, PRI, 펄스폭을 강제 설정한다.
            // SetCWParameter( pNewAet );

            SaveEmitterPDWFile( pEmitter, m_iCoLOB+1, bDBInsert );

            ++ m_iCoLOB;
        }
    }

    /*! \bug  m_CoMakeAet 에서 m_CoAet 까지 에미터에서 펄스열이 겹쳐진 에미터를 제거한다.
        \date 2008-11-19 13:14:29, 조철희
    */
    //DiscardEmitter();
    //ReMakeEmitter();

}

/**
 * @brief     펄스열을 근거로 에미터 정보의 주파수 정보를 생성한다.
 * @param     STR_FRQ * pFrq
 * @param     STR_EMITTER * pEmitter
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2005-05-13 14:55:19
 * @warning
 */
void CMakeAET::MakeFrqInfoFromSeg( STR_FRQ *pFrq, STR_EMITTER *pEmitter )
{
    unsigned int i;
    unsigned int uiCount;

    float fFreqMean;

    STR_PULSE_TRAIN_SEG *pSeg;

    memset( pFrq, 0, sizeof( struct STR_FRQ) );

    // 주파수 밴드 저장
    pSeg = & m_pSeg[ pEmitter->uiMainSeg ];
    pFrq->iBand = m_pBAND[ pSeg->stPDW.pIndex[0] ];

    // 주파수 범위 결정
    switch( pEmitter->enFreqType ) {
        case _FREQ_FIXED :
            pFrq->iType = ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED;
            // 주파수의 노이즈를 고려해서 평균값을 계산하도록 한다.
            //-- 조철희 2006-05-09 12:26:19 --//
            pFrq->iMean = (int) CalcFreqMedian( pSeg );
            pFrq->iMin = pEmitter->stFreq.iMin;
            pFrq->iMax = pEmitter->stFreq.iMax;
            break;

        case _HOPPING:
            /*! \bug  주파수 호핑값을 계산한다.
                \date 2008-10-30 15:49:17, 조철희
            */
            pFrq->iType = ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
            pFrq->iMax = pEmitter->stFreq.iMax;
            pFrq->iMin = pEmitter->stFreq.iMin;
            pFrq->iMean = pEmitter->stFreq.iMean;

            // 호핑 레벨값을 저장한다.
            pFrq->iSwtLev = (int) pEmitter->uiFreqLevelCount;

            TSortLevel<unsigned int>( (int) pEmitter->uiFreqLevelCount, pEmitter->uiFreqLevel );
            memcpy( pFrq->iSwtVal, pEmitter->uiFreqLevel, sizeof(int) * pEmitter->uiFreqLevelCount );
            break;

        case _PATTERN_AGILE :
            pFrq->iType = ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
            pFrq->iPatPrd = (int) ( pEmitter->fFreqPeriod + (float) 0.5 );
            pFrq->iPatType = pEmitter->enFreqPatternType;

            // 펄스열로부터 주파수 최대값과 최소값을 얻는다.
            uiCount = 0;
            pFrq->iMax = 0;
            pFrq->iMin = INT_MAX;
            fFreqMean = (float) 0.;
            for( i=0 ; i < pEmitter->uiCoSeg ; ++i ) {
                pSeg = & m_pSeg[ pEmitter->uiSegIdx[i] ];
                pFrq->iMin = min( pFrq->iMin, pSeg->stFreq.iMin );
                pFrq->iMax = max( pFrq->iMax, pSeg->stFreq.iMax );
                fFreqMean += (float) ( (float) pSeg->stPDW.uiCount * (float) pSeg->stFreq.iMean );
                uiCount += pSeg->stPDW.uiCount;
            }
            pFrq->iMean = IDIV( fFreqMean, uiCount);
            break;

        case _RANDOM_AGILE :
			pFrq->iType = ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE;

            // 펄스열로부터 주파수 최대값과 최소값을 얻는다.
            uiCount = 0;
            pFrq->iMax = 0;
            pFrq->iMin = INT_MAX;
            fFreqMean = ( float ) 0.;
            for( i=0 ; i < pEmitter->uiCoSeg ; ++i ) {
                pSeg = & m_pSeg[ pEmitter->uiSegIdx[i] ];
                pFrq->iMin = min( pFrq->iMin, pSeg->stFreq.iMin );
                pFrq->iMax = max( pFrq->iMax, pSeg->stFreq.iMax );
                fFreqMean += ( float ) ( ( float ) pSeg->stPDW.uiCount * ( float ) pSeg->stFreq.iMean );
                uiCount += pSeg->stPDW.uiCount;
            }
            pFrq->iMean = IDIV( fFreqMean, uiCount );
            break;

        default:
            break;

    }

    pFrq->iMode = (int) CalcMode<unsigned int>( pEmitter, m_pFREQ, (unsigned int) pFrq->iMean );

}

/**
 * @brief     스태거 PRI 에 대해서 LOB 정보를 생성한다.
 * @param     STR_PRI * pPri
 * @param     STR_EMITTER * pEmitter
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-26, 10:25
 * @warning
 */
void CMakeAET::MakeStaggerPRIInfoFromSeg(STR_PRI *pPri, STR_EMITTER *pEmitter)
{
    UINT j;

    int min_index;

    STR_PULSE_TRAIN_SEG *pSeg;

    min_index = TSortLevel<_TOA>( (int) pEmitter->uiCoStagDwellLevelCount, pEmitter->tStaggerDwellLevel, false );

    _EQUALS3(pPri->tMin, pPri->tMax, pEmitter->tStaggerDwellLevel[0] )

    // 그 인덱스 값부터 에미터의 스태거단에 기록한다.
    // 그리고 PRI 범위와 평균값을 기록한다.
    pPri->tMean = 0;
    for (j = 0; j < pEmitter->uiCoStagDwellLevelCount && j < MAX_FREQ_PRI_STEP; ++j) {
        pPri->tSwtVal[j] = pEmitter->tStaggerDwellLevel[((UINT)min_index + j) % pEmitter->uiCoStagDwellLevelCount];
        pPri->tMin = _min(pPri->tMin, pPri->tSwtVal[j]);
        pPri->tMax = _max(pPri->tMax, pPri->tSwtVal[j]);
        pPri->tMean += pPri->tSwtVal[j];
    }
    pPri->tMean = UDIV(pPri->tMean, j);

    // 이상 에미터 제원은 삭제 또는 제원을 변경한다.
    // 스태거일 때는 PRI 제원을 확인하여 Jitter율이 작거나 PRI 범위 STABLE_MARGIN 범위에 들면 STABLE로 간주한다.
    //-- 조철희 2005-09-29 15:53:46 --//


    // pPri->fJtrPer = FDIV(100 * (pPri->tMax - pPri->tMin), pPri->tMean);
    pPri->fJtrPer = TCalcJitterPercent<_TOA>( pPri->tMax - pPri->tMin, pPri->tMean );

    if (TCompMeanDiff<_TOA>(pPri->tMax, pPri->tMin, 2 * m_tStableMargin ) == true) {
        pPri->iType = ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED;
    }
    // 지터율이 50%이상인 펄스열은 지터율로 정의 한다.
    else if (pPri->fJtrPer >= MAX_JITTER_P) {
        pSeg = &m_pSeg[pEmitter->uiMainSeg];

        if (pSeg->enPriType == _STABLE) {
            /*
            pPri->mean = UDIV( pSeg->pri.mean, pEmitter->stag_dwell_level_cnt );
            pPri->min = pPri->swtVal[0];
            pPri->max = pPri->swtVal[0];
            for( i=1 ; i < pEmitter->stag_dwell_level_cnt ; ++i ) {
                pPri->min = _min( pPri->min, pPri->swtVal[i] );
                pPri->max = _max( pPri->max, pPri->swtVal[i] );
            }	*/
        }
        else {
            pPri->tMin = pSeg->stPRI.tMin;
            pPri->tMax = pSeg->stPRI.tMax;
            pPri->tMean = pSeg->stPRI.tMean;

            pPri->iType = ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER;
            memset(pPri->tSwtVal, 0, sizeof(pPri->tSwtVal));
        }

    }
    else {
        // PRI 타입을 결정한다.
        pPri->iType = ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;
    }
    pPri->iSwtLev = (int) pEmitter->uiCoStagDwellLevelCount;


}

/**
 * @brief     MakeDwellPRIInfoInSeg
 * @param     STR_PRI * pPri
 * @param     STR_EMITTER * pEmitter
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-26, 10:27
 * @warning
 */
void CMakeAET::MakeDwellPRIInfoFromSeg(STR_PRI *pPri, STR_EMITTER *pEmitter)
{
    UINT i, uiCount;

    STR_PULSE_TRAIN_SEG *pSeg;

    _EQUALS3(pPri->tMin, pPri->tMax, pEmitter->tStaggerDwellLevel[0])

    pPri->iSwtLev = (int) min(pEmitter->uiCoStagDwellLevelCount, MAX_FREQ_PRI_STEP);

    // 그 인덱스 값부터 에미터의 레벨단에 기록한다.
    // 그리고 PRI 범위와 평균값을 기록한다.
    for (i = 1; i < pEmitter->uiCoStagDwellLevelCount && i < MAX_FREQ_PRI_STEP; ++i) {
        pPri->tMin = min(pPri->tMin, pEmitter->tStaggerDwellLevel[i]);
        pPri->tMax = max(pPri->tMax, pEmitter->tStaggerDwellLevel[i]);
    }

    _EQUALS3(pPri->tMean, uiCount, 0)
    for (i = 0; i < pEmitter->uiCoSeg; ++i) {
        pSeg = &m_pSeg[pEmitter->uiSegIdx[i]];
        pPri->tMean += (pSeg->stPRI.tMean * pSeg->stPDW.uiCount);
        uiCount += pSeg->stPDW.uiCount;
    }
    pPri->tMean = UDIV(pPri->tMean, uiCount);

    // DWELL 레벨값들을 작은 값부터 정렬화한다.
    //memcpy( pPri->tSwtVal, pEmitter->tStaggerDwellLevel, sizeof(_TOA)*(size_t) pPri->iSwtLev);
    //qsort( pPri->tSwtVal, (size_t)pPri->iSwtLev, sizeof(_TOA), lliparamCompare);
    TSortLevel<_TOA>( ( int ) pEmitter->uiFreqLevelCount, pEmitter->tStaggerDwellLevel );
    memcpy( pPri->tSwtVal, pEmitter->tStaggerDwellLevel, sizeof( _TOA ) * pEmitter->uiFreqLevelCount );


    //pPri->swtLev = pEmitter->stag_dwell_element_cnt;
}

/**
 * @brief     MakeDwellPRIInfoInSeg
 * @param     STR_PRI * pPri
 * @param     STR_EMITTER * pEmitter
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-26, 10:28
 * @warning
 */
void CMakeAET::MakeJitterPRIInfoFromSeg(STR_PRI *pPri, STR_EMITTER *pEmitter)
{
    UINT i;

    STR_PULSE_TRAIN_SEG *pSeg;

    /*! \bug  지터 신호에서 각 추출된 펄스열의 DTOA 간격을 구해서 이 구간이 Stable 형태 마진 안에 있으면
                        Stable 형태로 결정 한다.
        \date 2006-05-15 16:46:01, 조철희
    */
    /*! \todo	PRI 형태가 변화되는 것을 에미터 병합에서 변화되는 것을 확인해야 한다. */

    pPri->tMin = m_pSeg[pEmitter->uiSegIdx[0]].stPRI.tMin;
    pPri->tMax = m_pSeg[pEmitter->uiSegIdx[0]].stPRI.tMax;
    for (i = 1; i < pEmitter->uiCoSeg; ++i) {
        pSeg = &m_pSeg[pEmitter->uiSegIdx[i]];
        pPri->tMin = min(pPri->tMin, m_pSeg[pEmitter->uiSegIdx[0]].stPRI.tMin);
        pPri->tMax = max(pPri->tMax, m_pSeg[pEmitter->uiSegIdx[0]].stPRI.tMax);
    }
    //             if( CompMeanDiff<_TOA>( pPri->TMax, pPri->TMin, 2*STABLE_MARGIN ) == true ) {
    //                 // pPri->type = _STABLE;
    //             }

    pSeg = &m_pSeg[pEmitter->uiMainSeg];
    pPri->tMin = pSeg->stPRI.tMin;
    pPri->tMax = pSeg->stPRI.tMax;
    pPri->tMean = pSeg->stPRI.tMean;

}

/**
 * @brief     펄스열로부터 PRI 정보를 계산한다.
 * @param     STR_PRI * pPri
 * @param     STR_EMITTER * pEmitter
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-26, 10:31
 * @warning
 */
void CMakeAET::MakeStablePRIInfoFromSeg(STR_PRI *pPri, STR_EMITTER *pEmitter)
{
    UINT i;
    STR_PULSE_TRAIN_SEG *pSeg;

    pPri->tMin = m_pSeg[pEmitter->uiSegIdx[0]].stPRI.tMin;
    pPri->tMax = m_pSeg[pEmitter->uiSegIdx[0]].stPRI.tMax;
    for (i = 1; i < pEmitter->uiCoSeg; ++i) {
        pSeg = &m_pSeg[pEmitter->uiSegIdx[i]];
        pPri->tMin = min(pPri->tMin, m_pSeg[pEmitter->uiSegIdx[0]].stPRI.tMin);
        pPri->tMax = max(pPri->tMax, m_pSeg[pEmitter->uiSegIdx[0]].stPRI.tMax);
    }
    if (TCompMeanDiff<_TOA>(pPri->tMax, pPri->tMin, 2 * m_tStableMargin ) == false) {
        pPri->iType = ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER;
    }

    // 하모닉 관계이면 제일 작은 PRI로 계산을 해야 한다.
    // 현재로서는 펄스열 중에서 제일 센 놈으로 한다.
    //-- 조철희 2005-10-12 13:22:47 --//
    pSeg = &m_pSeg[pEmitter->uiMainSeg];
    pPri->tMin = pSeg->stPRI.tMin;
    pPri->tMax = pSeg->stPRI.tMax;
    pPri->tMean = pSeg->stPRI.tMean;

}

/**
 * @brief     펄스열 중에서 주요 펄스열 정보로부터 PRI 정보를 추출한다.
 * @param     STR_PRI * pPri
 * @param     STR_EMITTER * pEmitter
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-19, 15:57
 * @warning
 */
void CMakeAET::MakeDefaultPRIInfoFromEmitter( STR_PRI *pPri, STR_EMITTER *pEmitter )
{
    STR_PULSE_TRAIN_SEG *pSeg;

    // 펄스열 중에서 주요 펄스열 정보로부터 PRI 정보를 추출한다.
    //-- 조철희 2005-10-12 13:22:47 --//
    pSeg = &m_pSeg[pEmitter->uiMainSeg];
    pPri->tMin = pSeg->stPRI.tMin;
    pPri->tMax = pSeg->stPRI.tMax;
    pPri->tMean = pSeg->stPRI.tMean;

}

/**
 * @brief     스태거 레벨로부터 PRI 정보를 추출한다.
 * @param     STR_PRI * pPri
 * @param     STR_EMITTER * pEmitter
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-06-16, 13:01
 * @warning
 */
void CMakeAET::MakeStaggerPRIInfoFromEmitter( STR_PRI *pPRI, STR_EMITTER *pEmitter )
{
    unsigned int i;

    int min_index;

    min_index = TSortLevel<_TOA>( ( int ) pEmitter->uiCoStagDwellLevelCount, pEmitter->tStaggerDwellLevel, false );

    pPRI->tMean = _spZero;
    pPRI->tMin = pEmitter->tStaggerDwellLevel[0];
    pPRI->tMax = pEmitter->tStaggerDwellLevel[0];
    for( i = 0 ; i < pEmitter->uiCoStagDwellLevelCount && i < MAX_FREQ_PRI_STEP ; ++i ) {
        pPRI->tSwtVal[i] = pEmitter->tStaggerDwellLevel[( ( UINT ) min_index + i ) % pEmitter->uiCoStagDwellLevelCount];

        pPRI->tMin = min( pPRI->tMin, pEmitter->tStaggerDwellLevel[i] );
        pPRI->tMax = max( pPRI->tMax, pEmitter->tStaggerDwellLevel[i] );
        pPRI->tMean += pEmitter->tStaggerDwellLevel[i];
    }
    pPRI->tMean = TDIV<_TOA>( pPRI->tMean, pEmitter->uiCoStagDwellLevelCount);

    // 스태거 관련 정보 추가 저장
    pPRI->iSwtLev = ( int ) pEmitter->uiCoStagDwellLevelCount;
    //memcpy( pPRI->tSwtVal, pEmitter->tStaggerDwellLevel, sizeof( _TOA ) * ( size_t ) pPRI->iSwtLev );


}

/**
 * @brief     에미터 데이터로부터 PRI 정보를 계산한다.
 * @param     STR_PRI * pPRI
 * @param     STR_EMITTER * pEmitter
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-19, 15:47
 * @warning
 */
void CMakeAET::MakePRIInfoFromEmitter( STR_PRI *pPRI, STR_EMITTER *pEmitter )
{
    STR_PULSE_TRAIN_SEG *pSeg;

    memset( pPRI, 0, sizeof( STR_PRI ) );

    // PRI 값을 산출할 때는 병합된 펄스열로부터 계산한다.
    // 이전에는 주 펄스열로부터 계산했는데 가장 많은 개수를 가진 펄스열이
    // 하모닉 신호이기 때문에 PRI 계산은 모든 펄스열로부터 계산한다.

    // PRI 타입별 PRI 최대, 최소 저장
    switch( pEmitter->enPRIType ) {
    case _STABLE:
        pPRI->iType = ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED;
        MakeDefaultPRIInfoFromEmitter( pPRI, pEmitter );
        break;

    case _JITTER_RANDOM:
        pPRI->iType = ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER;
        MakeDefaultPRIInfoFromEmitter( pPRI, pEmitter );
        break;

    case _DWELL:
        pPRI->iType = ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;

        MakeDefaultPRIInfoFromEmitter( pPRI, pEmitter );

        // 드웰 레벨값을 저장한다.
        pPRI->iSwtLev = (int) pEmitter->uiCoStagDwellLevelCount;
        TSortLevel<_TOA>( (int) pEmitter->uiCoStagDwellLevelCount, pEmitter->tStaggerDwellLevel );
        memcpy( pPRI->tSwtVal, pEmitter->tStaggerDwellLevel, sizeof( _TOA ) * pEmitter->uiCoStagDwellLevelCount );
        break;

    // 스태거 또는 Dwell 일 때 스태거 레벨 값을 근거로 PRI 값을 설정한다.
    case _STAGGER:
    case _STABLE_STAGGER:
    case _JITTER_STAGGER:
        pPRI->iType = ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;
        MakeStaggerPRIInfoFromEmitter( pPRI, pEmitter );

        pPRI->tPatPrd = pEmitter->tFramePRI;
        break;

    case _JITTER_PATTERN:
        pPRI->iType = ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;
        pPRI->tPatPrd = UMUL( 1, pEmitter->fPRIPeriod );
        pPRI->iPatType = pEmitter->enPRIPatternType;
        pSeg = & m_pSeg[pEmitter->uiMainSeg];
        pPRI->tMin = pSeg->stPRI.tMin;
        pPRI->tMax = pSeg->stPRI.tMax;
        pPRI->tMean = pSeg->stPRI.tMean;
        break;

    default:
        Log( enError, "잘못된 PRI 형태 입니다. 계산을 수행하지 못했습니다." );
        break;
    }

    // 지터율 과 레벨값을 저장한다.
    //pPRI->fJtrPer = FDIV( 100. * (pPRI->tMax - pPRI->tMin), pPRI->tMean );
	pPRI->fJtrPer = TCalcJitterPercent<_TOA>( (pPRI->tMax - pPRI->tMin), pPRI->tMean );

    //pPri->swtLev = pEmitter->stag_dwell_element_cnt;

    pPRI->tMode = CalcMode<_TOA>( pEmitter, m_pTOA, pPRI->tMean );

}

/**
 * @brief     펄스열로부터 PRI 정보를추출한다.
 * @param     STR_PRI * pPri
 * @param     STR_EMITTER * pEmitter
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2005-05-13 14:56:16
 * @warning
 */
void CMakeAET::MakePRIInfoFromSeg(STR_PRI *pPri, STR_EMITTER *pEmitter)
{
    unsigned int i;

    STR_PULSE_TRAIN_SEG *pSeg;

    memset( pPri, 0, sizeof( STR_PRI) );

    // PRI 값을 산출할 때는 병합된 펄스열로부터 계산한다.
    // 이전에는 주 펄스열로부터 계산했는데 가장 많은 개수를 가진 펄스열이
    // 하모닉 신호이기 때문에 PRI 계산은 모든 펄스열로부터 계산한다.

    // PRI 타입별 PRI 최대, 최소 저장
    switch( pEmitter->enPRIType ) {
        case _STABLE:
            pPri->iType = ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED;
            MakeStablePRIInfoFromSeg(pPri, pEmitter);
            break;

        case _JITTER_RANDOM:
            pPri->iType = ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER;
            MakeJitterPRIInfoFromSeg(pPri, pEmitter);
            break;

        case _DWELL:
            pPri->iType = ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;
            MakeDwellPRIInfoFromSeg(pPri, pEmitter);
            break;

        // 스태거 또는 Dwell 일 때 스태거 레벨 값을 근거로 PRI 값을 설정한다.
        case _STABLE_STAGGER :
        case _JITTER_STAGGER :
        case _STAGGER :
            pPri->iType = ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;
            MakeStaggerPRIInfoFromSeg(pPri, pEmitter);
            break;

        case _JITTER_PATTERN:
            pPri->iType = ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;
            pPri->tPatPrd = UMUL( 1, pEmitter->fPRIPeriod );
            pPri->iPatType = pEmitter->enPRIPatternType;
            pSeg = & m_pSeg[ pEmitter->uiMainSeg ];
            pPri->tMin = pSeg->stPRI.tMin;
            pPri->tMax = pSeg->stPRI.tMax;
            pPri->tMean = pSeg->stPRI.tMean;
            break;

        default :
            pPri->tMax = 0;
#ifdef _SONATA_
            pPri->tMin = INT32_MAX;
#else
            pPri->tMin = INT64_MAX;
#endif
            pPri->tMean = 0;
            // PRI 평균값을 계산상 버그
            for( i=0 ; i < pEmitter->uiCoSeg ; ++i ) {
                pSeg = & m_pSeg[ pEmitter->uiSegIdx[i] ];
                pPri->tMin = min( pPri->tMin, pSeg->stPRI.tMin );
                pPri->tMax = max( pPri->tMax, pSeg->stPRI.tMax );
                pPri->tMean += ( pSeg->stPDW.uiCount * pSeg->stPRI.tMean );
            }
            pPri->tMean = UDIV( pPri->tMean, pEmitter->stPDW.uiCount );
            break;
    }

    // 지터율 과 레벨값을 저장한다.
    pPri->fJtrPer = FDIV( 100. * ( pPri->tMax - pPri->tMin ), pPri->tMean );
    //pPri->swtLev = pEmitter->stag_dwell_element_cnt;

    pPri->tMode = CalcMode<_TOA>( pEmitter, m_pTOA, pPri->tMean );

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CMakeAET::MakePWInfoInSeg
// 반환되는 형  : void
// 함 수 인 자  : STR_MINMAX *pPw
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-13 14:56:39
//
//##ModelId=428832A20173
void CMakeAET::MakePWInfoFromSeg(STR_MINMAX *pPW, STR_EMITTER *pEmitter)
{
    unsigned int i;
    STR_MINMAX pw;
    STR_PULSE_TRAIN_SEG *pSeg;

    pSeg = & m_pSeg[ pEmitter->uiMainSeg ];

    // 펄스폭의 평균값 계산
    pPW->iMean = pSeg->stPW.iMean;
    //-- 조철희 2005-05-20 11:01:44 --//
    // 중간값으로 PW의 평균을 결정한다.
    pPW->iMean = VerifyPW( pEmitter->stPDW.pIndex, pEmitter->stPDW.uiCount );

    // 펄스폭의 최대/최소값 계산
    pw.iMax = 0;
    pw.iMin = INT_MAX;
    for( i=0 ; i < pEmitter->uiCoSeg ; ++i ) {
        pSeg = & m_pSeg[ pEmitter->uiSegIdx[i] ];
        if( i > 0 ) {
            pw.iMin = _min( pw.iMin, pSeg->stPW.iMin );
            pw.iMax = _max( pw.iMax, pSeg->stPW.iMax );
        }
        else {
            pw.iMin = pSeg->stPW.iMin;
            pw.iMax = pSeg->stPW.iMax;
        }
    }

    pPW->iMin = pw.iMin;
    pPW->iMax = pw.iMax;

    pPW->iMode = (int) CalcMode<unsigned int>( pEmitter, m_pPW, (unsigned int) pPW->iMean );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CMakeAET::MakePAInfoInSeg
// 반환되는 형  : void
// 함 수 인 자  : STR_MINMAX *pPa
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-13 14:56:58
//
//##ModelId=428832A200F1
void CMakeAET::MakePAInfoFromSeg(STR_MINMAX *pPa, STR_EMITTER *pEmitter)
{
    unsigned int i;
    STR_MINMAX pa;
    STR_PULSE_TRAIN_SEG *pSeg;

    // 신호 세기의 최소 최대값은 모든 펄스열에서 최대, 최소 값으로 한다.
    pa.iMax = 0;
    pa.iMin = 0;
    for( i=0 ; i < pEmitter->uiCoSeg ; ++i ) {
        pSeg = & m_pSeg[ pEmitter->uiSegIdx[i] ];
        if( i > 0 ) {
            pa.iMin = _min( pa.iMin, pSeg->stPA.iMin );
            pa.iMax = _max( pa.iMax, pSeg->stPA.iMax );
        }
        else {
            pa.iMin = pSeg->stPA.iMin;
            pa.iMax = pSeg->stPA.iMax;
        }
    }
    pPa->iMin = pa.iMin;
    pPa->iMax = pa.iMax;

    // 신호 세기 평균은 매인 펄스열에서 선택한다.
    // pSeg = & m_pSeg[ pEmitter->main_seg ];
    pPa->iMean = CalcPAMean( pEmitter->stPDW.pIndex, pEmitter->stPDW.uiCount );

    pPa->iMode = CalcMode<int>( pEmitter, m_pPA, pPa->iMean );
}

/**
  * @brief
  * @param		STR_EMITTER * pEmitter
  * @return 	int
  * @date			2019/04/09 10:43
*/
unsigned int CMakeAET::MakeDIInfoFromSeg( STR_EMITTER *pEmitter)
{
//     unsigned int i;
//
//     //
//     for( i=0 ; i < pEmitter->uiCoSeg ; ++i ) {
// // 		pSeg = & m_pSeg[ pEmitter->seg_idx[i] ];
// // 		pa.min = _min( pa.min, pSeg->pa.min );
// // 		pa.max = _max( pa.max, pSeg->pa.max );
//     }
//
     return 100;

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CMakeAET::MakeAOAInfoInSeg
// 반환되는 형  : void
// 함 수 인 자  : STR_MINMAX *pAoa
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-13 14:57:56
//
//##ModelId=428832A2006F
void CMakeAET::MakeAOAInfoFromSeg(STR_MINMAX_SDEV *pAoa, STR_EMITTER *pEmitter)
{
    unsigned int i;
    int diffAoa, overAoa;

    PDWINDEX *pPdwIndex;

    // 방위의 최소 최대값은 모든 펄스열에서 최대, 최소 값으로 한다.
#if 0
    STR_PULSE_TRAIN_SEG *pSeg;

    int frstAoaMax, frstAoaMin;

    STR_MINMAX aoa;

    pSeg = &m_pSeg[pEmitter->uiSegIdx[0]];
    if( pEmitter->uiCoSeg == 1 ) {
        pAoa->iMax = pSeg->aoa.iMax;
        pAoa->iMin = pSeg->aoa.iMin;
    }
    else {
        aoa.iMax = -INT32_MAX;
        aoa.iMin = +INT32_MAX;
        frstAoaMax = pSeg->aoa.iMax;
        frstAoaMin = pSeg->aoa.iMin;

        for( i = 0 ; i < pEmitter->uiCoSeg ; ++i ) {
            pSeg = &m_pSeg[pEmitter->uiSegIdx[i]];

            diffAoa = ( int ) pSeg->aoa.iMin - frstAoaMin;
            overAoa = _abs( diffAoa );
            if( overAoa > MAX_AOA / 2 ) {
                if( frstAoaMin > MAX_AOA / 2 ) {
                    diffAoa = diffAoa + MAX_AOA;
                }
                else {
                    diffAoa = diffAoa - MAX_AOA;
                }
            }
            aoa.iMin = _min( aoa.iMin, diffAoa );

            diffAoa = ( int ) pSeg->aoa.iMax - frstAoaMax;
            overAoa = _abs( diffAoa );
            if( overAoa > MAX_AOA / 2 ) {
                if( frstAoaMax > MAX_AOA / 2 ) {
                    diffAoa = diffAoa + MAX_AOA;
                }
                else {
                    diffAoa = diffAoa - MAX_AOA;
                }
            }
            aoa.iMax = _max( aoa.iMax, diffAoa );

        }
        pAoa->iMin = (MAX_AOA + aoa.iMin + frstAoaMin) % MAX_AOA;
        pAoa->iMax = (MAX_AOA + aoa.iMax + frstAoaMax) % MAX_AOA;

        diffAoa = pAoa->iMax - pAoa->iMin;
        if( diffAoa > MAX_AOA / 2 ) {
            diffAoa = pAoa->iMax;
            pAoa->iMax = pAoa->iMin;
            pAoa->iMin = diffAoa;
        }

    }

#else
    int aoaMean=0;

    pPdwIndex = pEmitter->stPDW.pIndex;
    int frstAoa = (int) m_pAOA[*pPdwIndex];

    pAoa->iMax = -INT32_MAX;
    pAoa->iMin = +INT32_MAX;

    for( i = 0 ; i < pEmitter->stPDW.uiCount ; ++i ) {
        diffAoa = ( int ) m_pAOA[*pPdwIndex] - frstAoa;
        overAoa = _abs( diffAoa );
        if( overAoa > MAX_AOA_BIT / 2 ) {
            if( frstAoa > MAX_AOA_BIT / 2 ) {
                diffAoa = diffAoa + MAX_AOA_BIT;
            }
            else {
                diffAoa = diffAoa - MAX_AOA_BIT;
            }
        }

        aoaMean += diffAoa;
        pAoa->iMax = max( pAoa->iMax, ( int ) diffAoa );
        pAoa->iMin = min( pAoa->iMin, ( int ) diffAoa );

        ++pPdwIndex;
    }

    pAoa->iMean = (MAX_AOA_BIT + IDIV( aoaMean, pEmitter->stPDW.uiCount ) + frstAoa) % MAX_AOA_BIT;
    pAoa->iMax = (MAX_AOA_BIT + pAoa->iMax + frstAoa) % MAX_AOA_BIT;
    pAoa->iMin = (MAX_AOA_BIT + pAoa->iMin + frstAoa) % MAX_AOA_BIT;

    diffAoa = pAoa->iMax - pAoa->iMin;
    if( diffAoa > MAX_AOA_BIT / 2 ) {
        diffAoa = pAoa->iMax;
        pAoa->iMax = pAoa->iMin;
        pAoa->iMin = diffAoa;
    }

#endif

    // 방위 값 산출시에 스캔형태가 고정형이면
    // 평균 통계 수식으로 값을 산출하고
    // 그 이외의 스캔형태는 신호세기에 의한 정렬으로 방위값을 산출한다.

    // 구현: 김경석
    // 수정: 조철희
    //-- 조철희 2005-07-12 16:39:34 --//

#if defined( _GSKIMF_AOAMEANALG_200505_1 )
    pSeg = & m_pSeg[ pEmitter->uiMainSeg ];
  pAoa->iMean = CalcAoaMean_GSKIMF_200505_1( pSeg );	// 김경석
#elif defined( _GSKIMF_AOAMEANALG_200505_2 )
    pSeg = & m_pSeg[ pEmitter->uiMainSeg ];
  pAoa->iMean = CalcAoaMean_GSKIMF_200505_2( pSeg );	// 김경석
#elif defined( _GSKIMF_AOAMEANALG_200505_3 )
    pSeg = & m_pSeg[ pEmitter->uiMainSeg ];
    pAoa->iMean = CalcAoaMean_GSKIMF_200505_3( pSeg );	// 김경석
#elif defined( _GSKIMF_AOAMEANALG_200505_6 )
    pAoa->iMode = 0;
#if defined(_XBAND_) || defined(_701_)
    pAoa->iMode = (int) CalcMode<unsigned int>( pEmitter, m_pAOA, ( unsigned int ) pAoa->iMean );

#else
    pAoa->iMode = ( int ) CalcMode<unsigned int>( pEmitter, m_pAOA, (unsigned int) pAoa->iMean );

    // 방위 히스토그램을 이용해서 방위를 계산함.
    pAoa->iMean = (int) CalcAoaMean_GSKIMF_200505_6( pEmitter );

#endif


#else// defined( _CHJO_AOAMEANALG_200503 )
    // 방위 평균은 메인 펄스열에서 선택한다.
    pAoa->iMean = pSeg->stAOA.iMean;
#endif

    // 표준 편차 계산
    int iDiff;
    unsigned int uiSum=0;

    pPdwIndex = pEmitter->stPDW.pIndex;
    for( i=0 ; i < pEmitter->stPDW.uiCount ; ++i ) {
        iDiff = pAoa->iMean - (int) m_pAOA[ *pPdwIndex++ ];
        if( iDiff > MAX_AOA_BIT / 2 ) {
            iDiff = ( MAX_AOA_BIT - iDiff );
        }
        else if( iDiff < -MAX_AOA_BIT / 2 ) {
            iDiff = ( iDiff + MAX_AOA_BIT ) % MAX_AOA_BIT;
        }
		else {

		}
        uiSum += (unsigned int) ( iDiff * iDiff );

    }
    pAoa->fsdev = (float) sqrt( FDIV( uiSum, pEmitter->stPDW.uiCount ) );

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CMakeAET::CalcAoaMean_GSKIMF_200505_6
// 반환되는 형  : UINT
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-09-30 16:29:31
//
UINT CMakeAET::CalcAoaMean_GSKIMF_200505_6( STR_EMITTER *pEmitter ) {

    // 방위 히스토그램 계산
    return (UINT) CalcAoaMeanByHistAoa( & pEmitter->stPDW );

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CMakeAET::MakeExtInfoInSeg
// 반환되는 형  : void
// 함 수 인 자  : STR_EXT *pExt
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-16 14:08:56
//
// void CMakeAET::MakeExtInfoFromSeg( STR_EXT *pExt, STR_EMITTER *pEmitter )
// {
//     // int band;
//     STR_PULSE_TRAIN_SEG *pSeg;
//
//     // 주파수 밴드 저장
//     pSeg = & m_pSeg[ pEmitter->uiMainSeg ];
//
//     pExt->uinoCol = m_uiCoPdw;
//     pExt->uinoExt = pEmitter->stPDW.uiCount;
//
//     // PDW STAT 를 에미터에 기록한다.
//     //-- 조철희 2005-11-04 17:44:48 --//
//     pExt->uiPDWStat = pSeg->uiStat;
//
//     pExt->bOverId = false;
//
//     pExt->noMergeEMT = -1;
//
//     // band = BAND[ pSeg->pdw.pIndex[0] ];
//     pExt->stFreq.iLow = pEmitter->stFreq.iMin;
//     pExt->stFreq.iHigh = pEmitter->stFreq.iMax;
//
//     pExt->idxEmitter = -1;
//
//     pExt->uiMaxChannelOfPDW = (UINT) CalMaxChannel( & pEmitter->stPDW );
//
//     pExt->mark = NORMAL_AET;
//
// }

//////////////////////////////////////////////////////////////////////////
/*! \brief    CMakeAET::PrintAllEmitter
        \author   조철희
        \return   void
        \version  0.0.29
        \date     2008-07-12 13:09:47
        \warning
*/
void CMakeAET::PrintAllEmitter()
{
    int i;

    SRxLOBData *pLOBData;

    if( m_iCoLOB == 0 ) {
        Log( enNormal, "LOB : None." );
    }
    else {
        //printf( "\n\n LOB 개수 : %d", m_CoLOB );
        Log( enNormal, "LOB : %d", m_iCoLOB );
        pLOBData = GetLOBData();		//& m_LOBData[0];

        for( i=0 ; i < m_iCoLOB ; ++i ) {
            DISP_FineLOB(pLOBData);

            ++pLOBData;
        }
    }

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CMakeAET::Comma
        \author   조철희
        \param    pString 인자형태 char *
        \return   char *
        \version  0.0.29
        \date     2008-07-12 13:41:12
        \warning
*/
//char *CMakeAET::Comma( char *pString )
//{
//    int len=0;
//    int num_commas=0;
//    int comma_count=0;
//    int i=0;
//    int n=0;

//    /* count given string */
//    len = strlen( pString );
//    num_commas = (int) ( len / 3 );

//    m_Comma[len + num_commas] = '\0';
//    for( i=len-1, n=1 ; i >= 0 ; i--, n++ ) {
//        m_Comma[i + num_commas - comma_count] = pString[i];
//        if( ( n % 3 ) == 0 ) {
//            comma_count++;
//            m_Comma[i + num_commas - comma_count] = ',';
//        }
//    }
//  return & m_Comma[0];
//}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CMakeAET::CalMaxChannel
        \author   조철희
        \param    pPdw 인자형태 STR_PDWINDEX *
        \return   int
        \version  0.0.53
        \date     2008-11-03 19:14:45
        \warning
*/
// int CMakeAET::CalMaxChannel( STR_PDWINDEX *pPdw )
// {
//     int max_channel;
//     UINT i, hist[4];
//     PDWINDEX *pPdwIndex;
//     unsigned int uiCount = pPdw->uiCount;
//
//     pPdwIndex = pPdw->pIndex;
//     _EQUALS5( hist[0], hist[1], hist[2], hist[3], 0 )
//     for( i=0 ; i < uiCount; ++i ) {
//         max_channel = min( m_pMAXCHANNEL[ *pPdwIndex ], 3 );
//         ++ pPdwIndex;
//         ++ hist[ max_channel ];
//     }
//
//     max_channel = 0;
//     if( hist[1] > hist[max_channel] ) {
//         max_channel = 1;
//     }
//     if( hist[2] > hist[max_channel] ) {
//         max_channel = 2;
//     }
//     if( hist[3] > hist[max_channel] ) {
//         max_channel = 3;
//     }
//
//     // 최소 개수는 무의미하게 처리하게 함.
//     return max_channel;
// }

/**
 * @brief     에미터 정보로 LOB 데이터를 생성한다.
 * @param     int iLOBData
 * @param     STR_EMITTER * pEmitter
 * @param     int idxEmitter
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-19, 13:08
 * @warning
 */
void CMakeAET::MakeLOBDataFromEmitter( int iLOBData, STR_EMITTER *pEmitter, int idxEmitter )
{
    STR_MINMAX stVal;
    STR_MINMAX_SDEV stVal2;
    SRxLOBData stLOBData;

    float fDiff;

    // LOB 데이터를 생성하기 위한 LOB 데이터 얻기
    memset( & stLOBData, 0, sizeof( struct SRxLOBData) );

    //////////////////////////////////////////////////////////////////////////

    stLOBData.uiPDWID = GetPDWID();

    stLOBData.uiPLOBID = (unsigned int) ( iLOBData + 1 );
    stLOBData.uiLOBID = _spZero;
    stLOBData.uiABTID = _spZero;
    stLOBData.uiAETID = _spZero;

    // 시간 정보
    CCommonUtils::GetCollectTime( (unsigned int *) & stLOBData.tiContactTime, & stLOBData.tiContactTimems );

    // 신호 형태
#if defined(_POCKETSONATA_) || defined(_712_)
    stLOBData.vSignalType = (unsigned char) pEmitter->enSignalType;
#else
    pLOBData->vSignalType = ( int ) pEmitter->enSignalType;
#endif

    // 방위
    MakeAOAInfoFromSeg( & stVal2, pEmitter );
    stLOBData.fDOAMean = FAOACNV( stVal2.iMean );			//FTOAsCNV( stVal.mean );
    stLOBData.fDOAMax = FAOACNV( stVal2.iMax );
    stLOBData.fDOAMin = FAOACNV( stVal2.iMin );
    stLOBData.fDOAMode = FAOACNV( stVal2.iMode );
    fDiff = stLOBData.fDOAMax - stLOBData.fDOAMin;
    if( fDiff < 0 ) {
        stLOBData.fDOADeviation = (float) 360.0 + fDiff;
    }
    else {
        stLOBData.fDOADeviation = fDiff;
    }

    //stLOBData.fDOASDeviation = stVal2.fsdev;

    // DI 율
    stLOBData.uiDIRatio = MakeDIInfoFromSeg( pEmitter );							// [0.1%]

	//////////////////////////////////////////////////////////////////////////
	// 주파수 정보 생성
	MakeFreqLOBDataFromEmitter( & stLOBData, pEmitter);


    //////////////////////////////////////////////////////////////////////////
    // PRI 정보 생성
	MakePRILOBDataFromEmitter( & stLOBData, pEmitter);


    //////////////////////////////////////////////////////////////////////////
    // 펄스폭 생성
    MakePWInfoFromSeg( & stVal, pEmitter );
    stLOBData.fPWMean = PWCNV( stVal.iMean ); //CDecode::DecodePWns( stVal.iMean );			//, _spOneMicrosec );
    stLOBData.fPWMax = PWCNV( stVal.iMax );
    stLOBData.fPWMin = PWCNV( stVal.iMin );
    stLOBData.fPWMode = PWCNV( stVal.iMode );
    stLOBData.fPWDeviation = stLOBData.fPWMax - stLOBData.fPWMin;

    //////////////////////////////////////////////////////////////////////////
    // 신호 세기 생성
    MakePAInfoFromSeg( & stVal, pEmitter );
    stLOBData.fPAMax = PACNV( stVal.iMax );
    stLOBData.fPAMean = PACNV( stVal.iMean );
    stLOBData.fPAMin = PACNV( stVal.iMin );
    stLOBData.fPAMode = PACNV( stVal.iMode );
    stLOBData.fPADeviation = stLOBData.fPAMax - stLOBData.fPAMin;

    //////////////////////////////////////////////////////////////////////////
    // 인트라 생성
    MakeMOPInfoFromSeg( & stLOBData, pEmitter );

    //////////////////////////////////////////////////////////////////////////
    // 기타 정보 저장
    stLOBData.uiNumOfCollectedPDW = m_uiCoPdw;
    stLOBData.uiNumOfAnalyzedPDW = pEmitter->stPDW.uiCount;

#if defined(_ELINT_) || defined(_XBAND_)
	stLOBData.iIsStoreData = IsStorePDW();

    stLOBData.iCollectorID = GetCollectorID();
    memcpy( stLOBData.aucTaskID, GetTaskID(), sizeof(stLOBData.aucTaskID) );
#endif

    // 수집소 위치 정보 저장
#if defined(_ELINT_) || defined(_XBAND_)
    if( stLOBData.iCollectorID >= RADARCOL_1 && stLOBData.iCollectorID <= RADARCOL_3 ) {
         stLOBData.fCollectLatitude = (float) dRCLatitude[stLOBData.iCollectorID];
         stLOBData.fCollectLongitude = (float) dRCLongitude[stLOBData.iCollectorID];
    }
    else {
         stLOBData.fCollectLatitude = 0.0;
         stLOBData.fCollectLongitude = 0.0;
    }
#else
    //stLOBData.fCollectLatitude = 0.0;
    //stLOBData.fCollectLongitude = 0.0;

#endif

    //memset( stLOBData.aucRadarName, 0, sizeof(stLOBData.aucRadarName) );
    //stLOBData.uiRadarModeIndex = _spZero;
    //stLOBData.iThreatIndex = _spZero;

    //stLOBData.uiSeqNum = 0;

#if defined(_ELINT_) || defined(_XBAND_)
    //STR_PDWDATA *pPDWData = m_pNewSigAnal->GetPDWData();
    //memcpy( stLOBData.aucTaskID, GetTaskID(), sizeof(stLOBData.aucTaskID) );
#elif defined(_POCKETSONATA_) || defined(_712_)

#else

#endif

#ifdef _XBAND_
	stLOBData.uiOpInitID = GetOpInitID();

#endif

#ifdef __VXWORKS__
	m_vecLOBData.push_back( stLOBData );
#else
    m_vecLOBData.emplace_back( stLOBData );
#endif

}

/**
 * @brief     MakeFreqLOBDataFromEmitter
 * @param     SRxLOBData * pLOBData
 * @param     STR_EMITTER * pEmitter
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-02-02 15:40:33
 * @warning
 */
void CMakeAET::MakeFreqLOBDataFromEmitter( SRxLOBData *pLOBData, STR_EMITTER *pEmitter )
{
	int i;

	STR_FRQ stFrq;

    // 객체 초기화
    memset( &stFrq, 0, sizeof( struct STR_FRQ ) );

	MakeFrqInfoFromSeg(&stFrq, pEmitter);

	pLOBData->vFreqType = stFrq.iType;

	pLOBData->vFreqPatternType = stFrq.iPatType;
	pLOBData->vFreqPositionCount = (unsigned char ) stFrq.iSwtLev;

    pLOBData->fFreqPatternPeriod = ( float ) FTOAsCNV( ( _TOA ) stFrq.iPatPrd );

#if defined(_POCKETSONATA_) || defined(_712_)
    pLOBData->fFreqPatternPeriod = ( float ) FMUL( pLOBData->fFreqPatternPeriod, ( float ) 1000000. );
#else

#endif

	pLOBData->fFreqMean = FFRQMhzCNV(g_enBoardId, (unsigned int) stFrq.iMean);
	pLOBData->fFreqMax = FFRQMhzCNV(g_enBoardId, ( unsigned int ) stFrq.iMax);
	pLOBData->fFreqMin = FFRQMhzCNV(g_enBoardId, ( unsigned int ) stFrq.iMin);
	pLOBData->fFreqMode = FFRQMhzCNV(g_enBoardId, ( unsigned int ) stFrq.iMode);

    // 주파수 레벨 값
	memset(pLOBData->fFreqSeq, 0, sizeof(pLOBData->fFreqSeq));
	for (i = 0; i < pLOBData->vFreqPositionCount; ++i) {
		pLOBData->fFreqSeq[i] = FFRQMhzCNV(g_enBoardId, ( unsigned int ) stFrq.iSwtVal[i]);
	}

	pLOBData->fFreqDeviation = pLOBData->fFreqMax - pLOBData->fFreqMin;

}

/**
 * @brief     MakeMOPInfoFromSeg
 * @param     SRxLOBData * pLOBData
 * @param     STR_EMITTER * pEmitter
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-10-08 17:12:40
 * @warning
 */
void CMakeAET::MakeMOPInfoFromSeg( SRxLOBData *pLOBData, STR_EMITTER *pEmitter )
{
    // MOP 형태 설정
    if( pEmitter->uiStat >= (unsigned int) STAT_CHIRPTRI && pEmitter->uiStat <= ( unsigned int ) STAT_CW_CHIRPUK ) {
        pLOBData->enMOPType = E_MOP_FMOP;
        if( pEmitter->uiStat == ( unsigned int ) STAT_CHIRPTRI || pEmitter->uiStat == ( unsigned int ) STAT_CW_CHIRPTRI ) {
            pLOBData->ucDetailMOPType = 0;
        }
        else if( pEmitter->uiStat == ( unsigned int ) STAT_CHIRPUP || pEmitter->uiStat == ( unsigned int ) STAT_CW_CHIRPUP ) {
            pLOBData->ucDetailMOPType = 1;
        }
        else if( pEmitter->uiStat == ( unsigned int ) STAT_CHIRPDN || pEmitter->uiStat == ( unsigned int ) STAT_CW_CHIRPDN ) {
            pLOBData->ucDetailMOPType = 2;
        }
        else {
            pLOBData->ucDetailMOPType = 3;
        }
    }
    else if( pEmitter->uiStat >= ( unsigned int ) STAT_PMOP && pEmitter->uiStat <= ( unsigned int ) STAT_CW_PMOP ) {
        pLOBData->enMOPType = E_MOP_PMOP;
        pLOBData->ucDetailMOPType = 3;
    }
    else {
        pLOBData->enMOPType = E_MOP_UNKNOWN;
        pLOBData->ucDetailMOPType = 3;
    }

    // FMOP 통계치 설정
    pLOBData->fMOPMaxFreq = CPOCKETSONATAPDW::DecodeFMOPBW( pEmitter->stFMOPFreq.iMax );
    pLOBData->fMOPMinFreq = CPOCKETSONATAPDW::DecodeFMOPBW( pEmitter->stFMOPFreq.iMin );
    pLOBData->fMOPMeanFreq = CPOCKETSONATAPDW::DecodeFMOPBW( pEmitter->stFMOPFreq.iMean );
    pLOBData->fMOPFreqDeviation = pLOBData->fMOPMaxFreq - pLOBData->fMOPMinFreq;

}

/**
 * @brief     MakePRILOBDataFromEmitter
 * @param     SRxLOBData * pLOBData
 * @param     STR_EMITTER * pEmitter
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-02-02 15:43:04
 * @warning
 */
void CMakeAET::MakePRILOBDataFromEmitter(SRxLOBData *pLOBData, STR_EMITTER *pEmitter)
{
	int i;

	STR_PRI stPri;

	MakePRIInfoFromEmitter(&stPri, pEmitter);

	pLOBData->vPRIType = stPri.iType;
	pLOBData->vPRIPatternType = stPri.iPatType;

    pLOBData->fPRIPatternPeriod = ( float ) FTOAsCNV( ( _TOA ) stPri.tPatPrd );
#if defined(_POCKETSONATA_) || defined(_712_)
    pLOBData->fPRIPatternPeriod = ( float ) FMUL( pLOBData->fPRIPatternPeriod, (float) 1000000. );
#else

#endif

	pLOBData->fPRIMean = (float) TOAusCNV(stPri.tMean);
	pLOBData->fPRIMax = (float) TOAusCNV(stPri.tMax);
	pLOBData->fPRIMin = (float) TOAusCNV(stPri.tMin);
	pLOBData->fPRIDeviation = (float) TOAusCNV(stPri.tMax - stPri.tMin);
	pLOBData->fPRIMode = (float) TOAusCNV(stPri.tMode);
    pLOBData->fPRIJitterRatio = ( float ) stPri.fJtrPer;

#if defined(_POCKETSONATA_) || defined(_712_)
	pLOBData->vPRIPositionCount = (unsigned char) stPri.iSwtLev;
#else
    pLOBData->vPRIPositionCount = stPri.iSwtLev;
#endif

 	// 드웰 레벨 값
    memset( pLOBData->fPRISeq, 0, sizeof( pLOBData->fPRISeq ) );
	for (i = 0; i < pLOBData->vPRIPositionCount; ++i) {
		pLOBData->fPRISeq[i] = (float) TOAusCNV(stPri.tSwtVal[i]);
	}

}

/**
 * @brief     PrintAllAET
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-07 16:20:54
 * @warning
 */
void CMakeAET::PrintAllAET()
{
    int i;
    unsigned int j=0;

    Log( enDebug, "[%s] 에미터 생성 개수 : %d(개)", GetAnalName(), m_iCoLOB- m_iAnaledCoLOB );

    for( i = m_iAnaledCoLOB ; i < m_iCoLOB; ++i ) {
        DISP_FineLOB( GetLOBData((unsigned int) i) );
        ++j;
    }

}

