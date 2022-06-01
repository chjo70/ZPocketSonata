// MakeAET.cpp: implementation of the CMakeAET class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#ifdef _WIN32
// PC용 상위 클래스에 전달하기 위한 선언
//#include "../../A50SigAnal/stdafx.h"

#endif

#if defined(_ELINT_) || defined(_XBAND_)
#include "../OFP_Main.h"

#elif _POCKETSONATA_
#include "../Identify/ELUtil.h"
#include "../EmitterMerge/ELMsgDefn.h"

#else
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "MakeAET.h"

#include "../../Include/globals.h"

#include "../EmitterMerge/ELStringDefn.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////




<<<<<<< HEAD






=======
>>>>>>> 598fc7475f45e541dd7f9944a98d8fd4f39ef723
extern int intparamCompare( const void *arg1, const void *arg2 );
extern int lliparamCompare( const void *arg1, const void *arg2 );


template <typename T>
T CalcMode( STR_EMITTER *pEmitter, T *pData, T mean ) {
    unsigned int i;

    size_t szSize;

    T tRet = 0;
    T *pArray, *pArrayTemp;

    pArray = ( T * ) malloc( sizeof( T ) * pEmitter->stPDW.uiCount );
    pArrayTemp = pArray;

    PDWINDEX *pPdwIndex = pEmitter->stPDW.pIndex;
    for( i = 0 ; i < pEmitter->stPDW.uiCount ; ++i ) {
        *pArrayTemp++ = pData[*pPdwIndex++];

    }

    szSize = pEmitter->stPDW.uiCount;

    // 1. 정렬하기
    if( typeid(T) == typeid( _TOA ) ) {
        qsort( pArray, szSize, sizeof( T ), lliparamCompare );
    }
    else {
        qsort( pArray, szSize, sizeof( T ), intparamCompare );
    }

    // 2. 최빈수 구하기
    int iMaxCount = 1, iCount=1;

    tRet = *pArray;
    for( i = 1 ; i < pEmitter->stPDW.uiCount ; ++i ) {
        if( pArray[i] == pArray[i - 1] ) {
            ++iCount;
        }
        else {
            if( iCount > iMaxCount ) {
                iMaxCount = iCount;
                tRet = pArray[i - 1];
            }
        }

    }

    // 최빈수 개수가 1 인 경우에는 평균값으로 최빈수 값을 정한다.
    if( iCount == _spOne ) {
        tRet = mean;
    }

    free( pArray );

    return tRet;

}

<<<<<<< HEAD

=======
>>>>>>> 598fc7475f45e541dd7f9944a98d8fd4f39ef723
//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CMakeAET::CMakeAET
// 함 수 인 자  : int coMaxPdw /*=NSP_MAX_PDW*/
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-09-30 16:33:17
//
//##ModelId=426C87D70020
CMakeAET::CMakeAET( int coMaxPdw /*=NSP_MAX_PDW*/ )
{
    BOOL bRet=TRUE;

    m_nMaxPdw = coMaxPdw;

//     m_dRCLatitude[0] = 0.0;
//     m_dRCLatitude[1] = 37.485168456889;
//     m_dRCLatitude[2] = 37.454452514694;
//     m_dRCLatitude[3] = 37.453517913889;
// 
//     m_dRCLongitude[0] = 0.0;
//     m_dRCLongitude[1] = 126.457916259694;
//     m_dRCLongitude[2] = 126.481880188111;
//     m_dRCLongitude[3] = 126.423416137778;

    m_uiCoAnalPdw = 0;

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CMakeAET::~CMakeAET
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-01-11 13:48:55
//
//##ModelId=426C87D70021
CMakeAET::~CMakeAET()
{

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CMakeAET::Init
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-04-26 18:18:35
//
//##ModelId=42757D4C0360
void CMakeAET::Init()
{

    // 펄스 수집 개수
    m_nCoPdw = GetColPdw();

    m_iCoLOB = 0;
    //m_nAnalEmitter = 0;
    m_pEmitter = GetEmitter();
    m_pSeg = GetPulseSeg();

    m_uiCoAnalPdw = 0;

    m_pPdwParam = GetPdwParam();

    // m_Aet[0].aet.noEMT = 0;

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CMakeAET::MakeAET
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-12 19:22:17
//
//##ModelId=428832A20386
void CMakeAET::MakeAET()
{
    int i;
    STR_EMITTER *pEmitter;

    m_iCoEmitter = GetCoEmitter();

    pEmitter = & m_pEmitter[0];
    for( i=0 ; i < m_iCoEmitter ; ++i, ++pEmitter ) {
        if( pEmitter->mark == NORMAL_EMITTER ) {
            // 에미터 생성하기
            MakeLOBDataFromEmitter(m_iCoLOB, pEmitter, i );

            SetKnownIndexEmitter( (UINT) m_iCoLOB, i );

            // CW 에미터인 경우, PRI, 펄스폭을 강제 설정한다.
            // SetCWParameter( pNewAet );

            SaveEmitterPdwFile( pEmitter, m_iCoLOB+1, true );

            ++ m_iCoLOB;
        }
    }

    /*! \bug  m_CoMakeAet 에서 m_CoAet 까지 에미터에서 펄스열이 겹쳐진 에미터를 제거한다.
        \date 2008-11-19 13:14:29, 조철희
    */
    //DiscardEmitter();
    //ReMakeEmitter();

    // LOB 생성한 개수로 재지정한다.
    //m_nAnalEmitter = m_CoLOB;    // m_CoEmitter;

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CMakeAET::MakeAETfromEmitter
// 반환되는 형  : void
// 함 수 인 자  : STR_NEWAET *pNewAet
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 인 자  : int idxEmitter
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-13 10:08:07
//
//##ModelId=428832A20304
// void CMakeAET::MakeAETfromEmitter(STR_NEWAET *pNewAet, STR_EMITTER *pEmitter, int idxEmitter )
// {
// 	STR_MINMAX aoa;
//
// 	// 새로운 에미터 데이터 초기화
// 	memset( pNewAet, 0, sizeof( STR_NEWAET ) );
//
// 	// 에미터 번호는 PAET 로 0 번으로 생성
// 	pNewAet->aet.noEMT = 0;
//
// 	// 에미터 타입 저장
// 	pNewAet->aet.sigType = pEmitter->signal_type;
//
// 	// 주파수 부분 저장
// 	MakeFrqInfoInSeg( & pNewAet->aet.frq, pEmitter );
//
// 	// PRI 부분 저장
// 	MakePRIInfoFromSeg( & pNewAet->aet.pri, pEmitter );
//
// 	// 펄스폭 부분 저장
// 	MakePWInfoInSeg( & pNewAet->aet.pw, pEmitter );
//
// 	// 신호세기 부분 저장
// 	MakePAInfoInSeg( & pNewAet->aet.pa, pEmitter );
//
// 	// 스캔 부분 저장
// 	pNewAet->aet.as.stat = pNewAet->aet.as.type = pNewAet->aet.as.prd = 0;
//
// 	// 방위 부분 저장
// 	MakeAOAInfoInSeg( & aoa, pEmitter );
// 	pNewAet->aet.aoa = aoa.mean;
// 	pNewAet->ext.aoa.iLow = aoa.min;
// 	pNewAet->ext.aoa.iHgh = aoa.max;
//
// 	// 접촉시간 부분 저장
// 	pNewAet->aet.seen.frst = pNewAet->aet.seen.last = 0;
//
// 	// 기타 에미터 정보 저장
// 	MakeExtInfoInSeg( & pNewAet->ext, pEmitter );
//
// 	pNewAet->ext.idxEmitter = idxEmitter;
//
// 	m_CoAnalPdw += pNewAet->ext.noExt;
//
// }

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CMakeAET::MakeFrqInfoInSeg
// 반환되는 형  : void
// 함 수 인 자  : STR_FRQ *pFrq
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-13 14:55:19
//
//##ModelId=428832A20282
void CMakeAET::MakeFrqInfoFromSeg( STR_FRQ *pFrq, STR_EMITTER *pEmitter )
{
    unsigned int i;
    unsigned int uiCount;

    STR_PULSE_TRAIN_SEG *pSeg;

    memset( pFrq, 0, sizeof(STR_FRQ) );

    // 주파수 밴드 저장
    pSeg = & m_pSeg[ pEmitter->uiMainSeg ];
    pFrq->iBand = m_pBAND[ pSeg->pdw.pIndex[0] ];

    // 주파수 범위 결정
    switch( pEmitter->stFreq.iType ) {
        case _FIXED :
            pFrq->iType = E_AET_FRQ_FIXED;
            // 주파수의 노이즈를 고려해서 평균값을 계산하도록 한다.
            //-- 조철희 2006-05-09 12:26:19 --//
            pFrq->iMean = CalcFreqMedian( pSeg );
            pFrq->iMin = pEmitter->stFreq.iMin;
            pFrq->iMax = pEmitter->stFreq.iMax;
            break;

        case _HOPPING:
            /*! \bug  주파수 호핑값을 계산한다.
                \date 2008-10-30 15:49:17, 조철희
            */
            pFrq->iType = E_AET_FRQ_HOPPING;
            pFrq->iMax = pEmitter->stFreq.iMax;
            pFrq->iMin = pEmitter->stFreq.iMin;
            pFrq->iMean = pEmitter->stFreq.iMean;

            // 호핑 레벨값을 산출한다.
            pFrq->iSwtLev = pEmitter->iCoHoppingLevel;
            memcpy(pFrq->iSwtVal, pEmitter->iHopLevel, _min(MAX_FREQ_PRI_STEP, pFrq->iSwtLev) * sizeof(int));
            break;

        case _PATTERN_AGILE :
            pFrq->iType = E_AET_FRQ_PATTERN;
            pFrq->iPatPrd = UMUL( 1, pEmitter->fFreqPeriod );
            pFrq->iPatType = pEmitter->uiFreqPatternType;            

            // 펄스열로부터 주파수 최대값과 최소값을 얻는다.
            uiCount = 0;
            pFrq->iMax = 0;
            pFrq->iMin = 0xffffff;
            pFrq->iMean = 0;
            for( i=0 ; i < pEmitter->uiCoSeg ; ++i ) {
                pSeg = & m_pSeg[ pEmitter->uiSegIdx[i] ];
                pFrq->iMin = _min( pFrq->iMin, pSeg->freq.iMin );
                pFrq->iMax = _max( pFrq->iMax, pSeg->freq.iMax );
                pFrq->iMean += ( pSeg->pdw.uiCount * pSeg->freq.iMean );
                uiCount += pSeg->pdw.uiCount;
            }
            pFrq->iMean = UDIV( pFrq->iMean, uiCount);
            break;

        case _RANDOM_AGILE :
			pFrq->iType = E_AET_FRQ_AGILE;

            // 펄스열로부터 주파수 최대값과 최소값을 얻는다.
            uiCount = 0;
            pFrq->iMax = 0;
            pFrq->iMin = 0xffffff;
            pFrq->iMean = 0;
            for( i=0 ; i < pEmitter->uiCoSeg ; ++i ) {
                pSeg = & m_pSeg[ pEmitter->uiSegIdx[i] ];
                pFrq->iMin = _min( pFrq->iMin, pSeg->freq.iMin );
                pFrq->iMax = _max( pFrq->iMax, pSeg->freq.iMax );
                pFrq->iMean += ( pSeg->pdw.uiCount * pSeg->freq.iMean );
                uiCount += pSeg->pdw.uiCount;
            }
            pFrq->iMean = UDIV( pFrq->iMean, uiCount);
            break;

        default:
            break;

    }

    pFrq->iMode = (int) CalcMode<unsigned int>( pEmitter, m_pFREQ, pFrq->iMean );

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
    int min_index, min_stagger_level, stagger_level_index;

    STR_PULSE_TRAIN_SEG *pSeg;

    /*! \todo	스태거 레벨을 가장 작은 값부터 레벨값을 시작하게 한다. */
    // 스태거 레벨 에서 가장 작은 레벨값과 인덱스 값을 얻는다.
    min_index = 0;
    min_stagger_level = UDIV(pEmitter->tStaggerDwellLevel[0], _spOneMicrosec);
    for (j = 1; j < pEmitter->uiStagDwellLevelCount && j < MAX_FREQ_PRI_STEP; ++j) {
        if (min_stagger_level > (int) UDIV(pEmitter->tStaggerDwellLevel[j], _spOneMicrosec)) {
            min_index = j;
            min_stagger_level = UDIV(pEmitter->tStaggerDwellLevel[j], _spOneMicrosec);
        }
    }
    /*! \bug  역방향으로 작은 레벨값을 검색해서 제일 작은 레벨 값을 시작으로 한다.
        \date 2006-08-16 20:18:43, 조철희
    */
    //
    stagger_level_index = min_index;
    for (j = 1; j < pEmitter->uiStagDwellLevelCount && j < MAX_FREQ_PRI_STEP; ++j) {
        stagger_level_index = (pEmitter->uiStagDwellLevelCount + stagger_level_index - 1) % pEmitter->uiStagDwellLevelCount;
        if (TRUE == CompMeanDiff<_TOA>(pEmitter->tStaggerDwellLevel[stagger_level_index], pEmitter->tStaggerDwellLevel[min_index], ITTOAusCNV((_TOA)1))) {
            min_index = stagger_level_index;
        }
        else {
            break;
        }
    }
    _EQUALS3(pPri->TMin, pPri->TMax, pEmitter->tStaggerDwellLevel[min_index])

    // 그 인덱스 값부터 에미터의 스태거단에 기록한다.
    // 그리고 PRI 범위와 평균값을 기록한다.
    pPri->TMean = 0;
    for (j = 0; j < (int)pEmitter->uiStagDwellLevelCount && j < MAX_FREQ_PRI_STEP; ++j) {
        pPri->TSwtVal[j] = pEmitter->tStaggerDwellLevel[(min_index + j) % pEmitter->uiStagDwellLevelCount];
        pPri->TMin = _min(pPri->TMin, pPri->TSwtVal[j]);
        pPri->TMax = _max(pPri->TMax, pPri->TSwtVal[j]);
        pPri->TMean += pPri->TSwtVal[j];
    }
    pPri->TMean = UDIV(pPri->TMean, j);

    // 이상 에미터 제원은 삭제 또는 제원을 변경한다.
    // 스태거일 때는 PRI 제원을 확인하여 Jitter율이 작거나 PRI 범위 STABLE_MARGIN 범위에 들면 STABLE로 간주한다.
    //-- 조철희 2005-09-29 15:53:46 --//
    pPri->fJtrPer = FDIV(100 * (pPri->TMax - pPri->TMin), pPri->TMean);
    if (CompMeanDiff<_TOA>(pPri->TMax, pPri->TMin, 2 * STABLE_MARGIN) == TRUE) {
        pPri->iType = _STABLE;
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
            pPri->TMin = pSeg->pri.tMin;
            pPri->TMax = pSeg->pri.tMax;
            pPri->TMean = pSeg->pri.tMean;

            pPri->iType = _JITTER_RANDOM;
            memset(pPri->TSwtVal, 0, sizeof(pPri->TSwtVal));
        }

    }
    else {
        // PRI 타입을 결정한다.
        pPri->iType = _STAGGER;
    }
    pPri->iSwtLev = pEmitter->uiStagDwellLevelCount;

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

    _EQUALS3(pPri->TMin, pPri->TMax, pEmitter->tStaggerDwellElement[0])

    pPri->iSwtLev = _min(pEmitter->uiStagDwellElementCount, MAX_FREQ_PRI_STEP);

    // 그 인덱스 값부터 에미터의 레벨단에 기록한다.
    // 그리고 PRI 범위와 평균값을 기록한다.
    for (i = 1; i < pEmitter->uiStagDwellElementCount && i < MAX_FREQ_PRI_STEP; ++i) {
        pPri->TMin = _min(pPri->TMin, pEmitter->tStaggerDwellElement[i]);
        pPri->TMax = _max(pPri->TMax, pEmitter->tStaggerDwellElement[i]);
    }

    _EQUALS3(pPri->TMean, uiCount, 0)
    for (i = 0; i < pEmitter->uiCoSeg; ++i) {
        pSeg = &m_pSeg[pEmitter->uiSegIdx[i]];
        pPri->TMean += (pSeg->pri.tMean * pSeg->pdw.uiCount);
        uiCount += pSeg->pdw.uiCount;
    }
    pPri->TMean = UDIV(pPri->TMean, uiCount);

    // DWELL 레벨값들을 작은 값부터 정렬화한다.
    memcpy(pPri->TSwtVal, pEmitter->tStaggerDwellElement, sizeof(_TOA)*pPri->iSwtLev);
    qsort(pPri->TSwtVal, (size_t)pPri->iSwtLev, sizeof(_TOA), lliparamCompare);

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

    pPri->TMin = m_pSeg[pEmitter->uiSegIdx[0]].pri.tMin;
    pPri->TMax = m_pSeg[pEmitter->uiSegIdx[0]].pri.tMax;
    for (i = 1; i < pEmitter->uiCoSeg; ++i) {
        pSeg = &m_pSeg[pEmitter->uiSegIdx[i]];
        pPri->TMin = _min(pPri->TMin, m_pSeg[pEmitter->uiSegIdx[0]].pri.tMin);
        pPri->TMax = _max(pPri->TMax, m_pSeg[pEmitter->uiSegIdx[0]].pri.tMax);
    }
    //             if( CompMeanDiff<_TOA>( pPri->TMax, pPri->TMin, 2*STABLE_MARGIN ) == TRUE ) {
    //                 // pPri->type = _STABLE;
    //             }

    pSeg = &m_pSeg[pEmitter->uiMainSeg];
    pPri->TMin = pSeg->pri.tMin;
    pPri->TMax = pSeg->pri.tMax;
    pPri->TMean = pSeg->pri.tMean;

}

/**
 * @brief     MakeStablePRIInfoInSeg
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

    pPri->TMin = m_pSeg[pEmitter->uiSegIdx[0]].pri.tMin;
    pPri->TMax = m_pSeg[pEmitter->uiSegIdx[0]].pri.tMax;
    for (i = 1; i < pEmitter->uiCoSeg; ++i) {
        pSeg = &m_pSeg[pEmitter->uiSegIdx[i]];
        pPri->TMin = _min(pPri->TMin, m_pSeg[pEmitter->uiSegIdx[0]].pri.tMin);
        pPri->TMax = _max(pPri->TMax, m_pSeg[pEmitter->uiSegIdx[0]].pri.tMax);
    }
    if (CompMeanDiff<_TOA>(pPri->TMax, pPri->TMin, 2 * STABLE_MARGIN) == FALSE) {
        pPri->iType = _JITTER_RANDOM;
    }

    // 하모닉 관계이면 제일 작은 PRI로 계산을 해야 한다.
    // 현재로서는 펄스열 중에서 제일 센 놈으로 한다.
    //-- 조철희 2005-10-12 13:22:47 --//
    pSeg = &m_pSeg[pEmitter->uiMainSeg];
    pPri->TMin = pSeg->pri.tMin;
    pPri->TMax = pSeg->pri.tMax;
    pPri->TMean = pSeg->pri.tMean;

}

/**
 * @brief     MakeStablePRIInfoFromEmitter
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

    // 하모닉 관계이면 제일 작은 PRI로 계산을 해야 한다.
    // 현재로서는 펄스열 중에서 제일 센 놈으로 한다.
    //-- 조철희 2005-10-12 13:22:47 --//
    pSeg = &m_pSeg[pEmitter->uiMainSeg];
    pPri->TMin = pSeg->pri.tMin;
    pPri->TMax = pSeg->pri.tMax;
    pPri->TMean = pSeg->pri.tMean;

}


/**
 * @brief     MakePRIInfoFromEmitter
 * @param     STR_PRI * pPri
 * @param     STR_EMITTER * pEmitter
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-19, 15:47
 * @warning
 */
<<<<<<< HEAD
void CMakeAET::MakePRIInfoFromEmitter( STR_PRI *pPRI, STR_EMITTER *pEmitter )
=======
void CMakeAET::MakePRIInfoFromEmitter( STR_PRI *pPri, STR_EMITTER *pEmitter )
>>>>>>> 598fc7475f45e541dd7f9944a98d8fd4f39ef723
{
    unsigned int i;

    STR_PULSE_TRAIN_SEG *pSeg;

<<<<<<< HEAD
    memset( pPRI, 0, sizeof( STR_PRI ) );
=======
    memset( pPri, 0, sizeof( STR_PRI ) );
>>>>>>> 598fc7475f45e541dd7f9944a98d8fd4f39ef723

    // PRI 값을 산출할 때는 병합된 펄스열로부터 계산한다.
    // 이전에는 주 펄스열로부터 계산했는데 가장 많은 개수를 가진 펄스열이
    // 하모닉 신호이기 때문에 PRI 계산은 모든 펄스열로부터 계산한다.

    // PRI 타입을 결정한다.
<<<<<<< HEAD
    pPRI->iType = pEmitter->enPRIType;
=======
    pPri->iType = pEmitter->enPRIType;
>>>>>>> 598fc7475f45e541dd7f9944a98d8fd4f39ef723

    // PRI 타입별 PRI 최대, 최소 저장
    switch( pEmitter->enPRIType ) {
    case _STABLE:
<<<<<<< HEAD
        pPRI->iType = E_AET_PRI_FIXED;
        MakeDefaultPRIInfoFromEmitter( pPRI, pEmitter );
        break;

    case _JITTER_RANDOM:
        pPRI->iType = E_AET_PRI_JITTER;
        MakeDefaultPRIInfoFromEmitter( pPRI, pEmitter );
        break;

    case _DWELL:
        pPRI->iType = E_AET_PRI_DWELL_SWITCH;
        MakeDefaultPRIInfoFromEmitter( pPRI, pEmitter );
=======
        pPri->iType = E_AET_PRI_FIXED;
        MakeDefaultPRIInfoFromEmitter( pPri, pEmitter );
        break;

    case _JITTER_RANDOM:
        pPri->iType = E_AET_PRI_JITTER;
        MakeDefaultPRIInfoFromEmitter( pPri, pEmitter );
        break;

    case _DWELL:
        pPri->iType = E_AET_PRI_DWELL_SWITCH;
        MakeDefaultPRIInfoFromEmitter( pPri, pEmitter );
>>>>>>> 598fc7475f45e541dd7f9944a98d8fd4f39ef723
        break;

        // 스태거 또는 Dwell 일 때 스태거 레벨 값을 근거로 PRI 값을 설정한다.
    case _STAGGER:
<<<<<<< HEAD
        pPRI->iType = E_AET_PRI_STAGGER;
        MakeDefaultPRIInfoFromEmitter( pPRI, pEmitter );

        // 스태거 관련 정보 추가 저장
        pPRI->iSwtLev = pEmitter->uiStagDwellLevelCount;
        memcpy( pPRI->TSwtVal, pEmitter->tStaggerDwellLevel, sizeof( _TOA )*pPRI->iSwtLev );
        pPRI->iPatPrd = pEmitter->tFramePri;
        break;

    case _JITTER_PATTERN:
        pPRI->iType = E_AET_PRI_PATTERN;
        pPRI->iPatPrd = UMUL( 1, pEmitter->fPRIPeriod );
        pPRI->iPatType = pEmitter->uiPRIPatternType;
        pSeg = & m_pSeg[pEmitter->uiMainSeg];
        pPRI->TMin = pSeg->pri.tMin;
        pPRI->TMax = pSeg->pri.tMax;
        pPRI->TMean = pSeg->pri.tMean;
        break;

    default:
        pPRI->TMax = 0;
        pPRI->TMin = 0xffffffffff;
        pPRI->TMean = 0;
        // PRI 평균값을 계산상 버그
        for( i = 0 ; i < pEmitter->uiCoSeg ; ++i ) {
            pSeg = &m_pSeg[pEmitter->uiSegIdx[i]];
            pPRI->TMin = _min( pPRI->TMin, pSeg->pri.tMin );
            pPRI->TMax = _max( pPRI->TMax, pSeg->pri.tMax );
            pPRI->TMean += (pSeg->pdw.uiCount * pSeg->pri.tMean);
        }
        pPRI->TMean = UDIV( pPRI->TMean, pEmitter->stPDW.uiCount );
=======
        pPri->iType = E_AET_PRI_STAGGER;
        MakeDefaultPRIInfoFromEmitter( pPri, pEmitter );
        break;

    case _JITTER_PATTERN:
        pPri->iType = E_AET_PRI_PATTERN;
        pPri->iPatPrd = UMUL( 1, pEmitter->fPRIPeriod );
        pPri->iPatType = pEmitter->uiPRIPatternType;
        pSeg = & m_pSeg[pEmitter->uiMainSeg];
        pPri->TMin = pSeg->pri.tMin;
        pPri->TMax = pSeg->pri.tMax;
        pPri->TMean = pSeg->pri.tMean;
        break;

    default:
        pPri->TMax = 0;
        pPri->TMin = 0xffffff;
        pPri->TMean = 0;
        // PRI 평균값을 계산상 버그
        for( i = 0 ; i < pEmitter->uiCoSeg ; ++i ) {
            pSeg = &m_pSeg[pEmitter->uiSegIdx[i]];
            pPri->TMin = _min( pPri->TMin, pSeg->pri.tMin );
            pPri->TMax = _max( pPri->TMax, pSeg->pri.tMax );
            pPri->TMean += (pSeg->pdw.uiCount * pSeg->pri.tMean);
        }
        pPri->TMean = UDIV( pPri->TMean, pEmitter->stPDW.uiCount );
>>>>>>> 598fc7475f45e541dd7f9944a98d8fd4f39ef723
        break;
    }

    // 지터율 과 레벨값을 저장한다.
<<<<<<< HEAD
    pPRI->fJtrPer = FDIV( 100. * (pPRI->TMax - pPRI->TMin), pPRI->TMean );
    //pPri->swtLev = pEmitter->stag_dwell_element_cnt;

    pPRI->TMode = CalcMode<_TOA>( pEmitter, m_pTOA, pPRI->TMean );
=======
    pPri->fJtrPer = FDIV( 100. * (pPri->TMax - pPri->TMin), pPri->TMean );
    //pPri->swtLev = pEmitter->stag_dwell_element_cnt;

    pPri->TMode = CalcMode<_TOA>( pEmitter, m_pTOA, pPri->TMean );
>>>>>>> 598fc7475f45e541dd7f9944a98d8fd4f39ef723

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CMakeAET::MakePRIInfoFromSeg
// 반환되는 형  : void
// 함 수 인 자  : STR_PRI *pPri
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-13 14:56:16
//
//##ModelId=428832A201F6
void CMakeAET::MakePRIInfoFromSeg(STR_PRI *pPri, STR_EMITTER *pEmitter)
{
    unsigned int i;
    
    STR_PULSE_TRAIN_SEG *pSeg;

    memset( pPri, 0, sizeof(STR_PRI) );

    // PRI 값을 산출할 때는 병합된 펄스열로부터 계산한다.
    // 이전에는 주 펄스열로부터 계산했는데 가장 많은 개수를 가진 펄스열이
    // 하모닉 신호이기 때문에 PRI 계산은 모든 펄스열로부터 계산한다.

    // PRI 타입을 결정한다.
    pPri->iType = pEmitter->enPRIType;

    // PRI 타입별 PRI 최대, 최소 저장
    switch( pEmitter->enPRIType ) {
        case _STABLE:
            pPri->iType = E_AET_PRI_FIXED;
            MakeStablePRIInfoFromSeg(pPri, pEmitter);
            break;

        case _JITTER_RANDOM:
            pPri->iType = E_AET_PRI_JITTER;
            MakeJitterPRIInfoFromSeg(pPri, pEmitter);
            break;

        case _DWELL:
            pPri->iType = E_AET_PRI_DWELL_SWITCH;
            MakeDwellPRIInfoFromSeg(pPri, pEmitter);
            break;

        // 스태거 또는 Dwell 일 때 스태거 레벨 값을 근거로 PRI 값을 설정한다.
        case _STAGGER :
            pPri->iType = E_AET_PRI_STAGGER;
            MakeStaggerPRIInfoFromSeg(pPri, pEmitter);
            break;

        case _JITTER_PATTERN :
            pPri->iType = E_AET_PRI_PATTERN;
            pPri->iPatPrd = UMUL( 1, pEmitter->fPRIPeriod );
            pPri->iPatType = pEmitter->uiPRIPatternType;
            pSeg = & m_pSeg[ pEmitter->uiMainSeg ];
            pPri->TMin = pSeg->pri.tMin;
            pPri->TMax = pSeg->pri.tMax;
            pPri->TMean = pSeg->pri.tMean;
            break;

        default :
            pPri->TMax = 0;
            pPri->TMin = 0xffffff;
            pPri->TMean = 0;
            // PRI 평균값을 계산상 버그
            for( i=0 ; i < pEmitter->uiCoSeg ; ++i ) {
                pSeg = & m_pSeg[ pEmitter->uiSegIdx[i] ];
                pPri->TMin = _min( pPri->TMin, pSeg->pri.tMin );
                pPri->TMax = _max( pPri->TMax, pSeg->pri.tMax );
                pPri->TMean += ( pSeg->pdw.uiCount * pSeg->pri.tMean );
            }
            pPri->TMean = UDIV( pPri->TMean, pEmitter->stPDW.uiCount );
            break;
    }

    // 지터율 과 레벨값을 저장한다.
    pPri->fJtrPer = FDIV( 100. * ( pPri->TMax - pPri->TMin ), pPri->TMean );
    //pPri->swtLev = pEmitter->stag_dwell_element_cnt;

<<<<<<< HEAD
    pPri->TMode = CalcMode<_TOA>( pEmitter, m_pTOA, pPri->TMean );
=======
    pPri->TMode = 0;
>>>>>>> 598fc7475f45e541dd7f9944a98d8fd4f39ef723

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
    pPW->iMean = pSeg->pw.iMean;
    //-- 조철희 2005-05-20 11:01:44 --//
    // 중간값으로 PW의 평균을 결정한다.
    pPW->iMean = VerifyPW( pEmitter->stPDW.pIndex, pEmitter->stPDW.uiCount );

    // 펄스폭의 최대/최소값 계산
    pw.iMax = 0;
    pw.iMin = 0xffffff;
    for( i=0 ; i < pEmitter->uiCoSeg ; ++i ) {
        pSeg = & m_pSeg[ pEmitter->uiSegIdx[i] ];
        if( i > 0 ) {
            pw.iMin = _min( pw.iMin, pSeg->pw.iMin );
            pw.iMax = _max( pw.iMax, pSeg->pw.iMax );
        }
        else {
            pw.iMin = pSeg->pw.iMin;
            pw.iMax = pSeg->pw.iMax;
        }
    }

    pPW->iMin = pw.iMin;
    pPW->iMax = pw.iMax;

    pPW->iMode = (int) CalcMode<unsigned int>( pEmitter, m_pPW, pPW->iMean );
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
            pa.iMin = _min( pa.iMin, pSeg->pa.iMin );
            pa.iMax = _max( pa.iMax, pSeg->pa.iMax );
        }
        else {
            pa.iMin = pSeg->pa.iMin;
            pa.iMax = pSeg->pa.iMax;
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
int CMakeAET::MakeDIInfoFromSeg( STR_EMITTER *pEmitter)
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
    
    STR_PULSE_TRAIN_SEG *pSeg;

    PDWINDEX *pPdwIndex;

    // 방위의 최소 최대값은 모든 펄스열에서 최대, 최소 값으로 한다.
#if 0
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
    int frstAoa = m_pAOA[*pPdwIndex];

<<<<<<< HEAD

    pAoa->iMax = -INT32_MAX;
    pAoa->iMin = +INT32_MAX;
=======
	pAoa->iMin = MAX_AOA;
	pAoa->iMax = -MAX_AOA;
>>>>>>> 598fc7475f45e541dd7f9944a98d8fd4f39ef723

    for( i = 0 ; i < pEmitter->stPDW.uiCount ; ++i ) {
        diffAoa = ( int ) m_pAOA[*pPdwIndex] - frstAoa;
        overAoa = _abs( diffAoa );
        if( overAoa > MAX_AOA / 2 ) {
            if( frstAoa > MAX_AOA / 2 )
                diffAoa = diffAoa + MAX_AOA;
            else
                diffAoa = diffAoa - MAX_AOA;
        }

        aoaMean += diffAoa;
        pAoa->iMax = max( pAoa->iMax, ( int ) diffAoa );
        pAoa->iMin = min( pAoa->iMin, ( int ) diffAoa );

        ++pPdwIndex;
    }

    pAoa->iMean = (MAX_AOA + IDIV( aoaMean, pEmitter->stPDW.uiCount ) + frstAoa) % MAX_AOA;
    pAoa->iMax = (MAX_AOA + pAoa->iMax + frstAoa) % MAX_AOA;
    pAoa->iMin = (MAX_AOA + pAoa->iMin + frstAoa) % MAX_AOA;

    diffAoa = pAoa->iMax - pAoa->iMin;
    if( diffAoa > MAX_AOA / 2 ) {
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
    pSeg = & m_pSeg[ pEmitter->uiMainSeg ];
#if defined( _GSKIMF_AOAMEANALG_200505_1 )
  pAoa->iMean = CalcAoaMean_GSKIMF_200505_1( pSeg );	// 김경석
#elif defined( _GSKIMF_AOAMEANALG_200505_2 )
  pAoa->iMean = CalcAoaMean_GSKIMF_200505_2( pSeg );	// 김경석
#elif defined( _GSKIMF_AOAMEANALG_200505_3 )
    pAoa->iMean = CalcAoaMean_GSKIMF_200505_3( pSeg );	// 김경석
#elif defined( _GSKIMF_AOAMEANALG_200505_6 )
#ifdef _XBAND_
<<<<<<< HEAD
    // pAoa->iMean = pAoa->aoa.iMean;
=======
>>>>>>> 598fc7475f45e541dd7f9944a98d8fd4f39ef723
    pAoa->iMode = (int) CalcMode<unsigned int>( pEmitter, m_pAOA, pAoa->iMean );

#else
    // 방위 히스토그램을 이용해서 방위를 계산함.
    pAoa->iMean = CalcAoaMean_GSKIMF_200505_6( pEmitter );

#endif


#else// defined( _CHJO_AOAMEANALG_200503 )
    // 방위 평균은 메인 펄스열에서 선택한다.
    pAoa->iMean = pSeg->aoa.iMean;
#endif

    // 표준 편차 계산
    int iDiff;
    unsigned int uiSum=0;

    pPdwIndex = pEmitter->stPDW.pIndex;
    for( i=0 ; i < pEmitter->stPDW.uiCount ; ++i ) {
        iDiff = pAoa->iMean - m_pAOA[ *pPdwIndex++ ];
        if( iDiff > MAX_AOA / 2 ) {
            iDiff = ( MAX_AOA - iDiff );
        }
        else if( iDiff < -MAX_AOA / 2 ) {
            iDiff = ( iDiff + MAX_AOA ) % MAX_AOA;
        }
        uiSum += ( iDiff * iDiff );

    }
    pAoa->fsdev = sqrt( FDIV( uiSum, pEmitter->stPDW.uiCount ) );

    // 최빈수 방위 계산

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
    return CalcAoaMeanByHistAoa( & pEmitter->stPDW );

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
//##ModelId=428832A10399
void CMakeAET::MakeExtInfoFromSeg( STR_EXT *pExt, STR_EMITTER *pEmitter )
{
    // int band;
    STR_PULSE_TRAIN_SEG *pSeg;

    // 주파수 밴드 저장
    pSeg = & m_pSeg[ pEmitter->uiMainSeg ];

    pExt->noCol = m_nCoPdw;
    pExt->noExt = pEmitter->stPDW.uiCount;

    // PDW STAT 를 에미터에 기록한다.
    //-- 조철희 2005-11-04 17:44:48 --//
    pExt->pt_stat = pSeg->uiStat;

    pExt->bOverId = FALSE;

    pExt->noMergeEMT = -1;

    // band = BAND[ pSeg->pdw.pIndex[0] ];
    pExt->frq.iLow = pEmitter->stFreq.iMin;
    pExt->frq.iHgh = pEmitter->stFreq.iMax;

    pExt->idxEmitter = -1;

    pExt->pt_maxchannel = CalMaxChannel( & pEmitter->stPDW );

    pExt->mark = NORMAL_AET;

}

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
            DISP_FineAet(pLOBData);

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
int CMakeAET::CalMaxChannel( STR_PDWINDEX *pPdw )
{
    int max_channel;
    UINT i, hist[4];
    PDWINDEX *pPdwIndex;
    unsigned int uiCount = pPdw->uiCount;

    pPdwIndex = pPdw->pIndex;
    _EQUALS5( hist[0], hist[1], hist[2], hist[3], 0 )
    for( i=0 ; i < uiCount; ++i ) {
        max_channel = _min( m_pMAXCHANNEL[ *pPdwIndex ], 3 );
        ++ pPdwIndex;
        ++ hist[ max_channel ];
    }

    max_channel = 0;
    if( hist[1] > hist[max_channel] ) {
        max_channel = 1;
    }
    if( hist[2] > hist[max_channel] ) {
        max_channel = 2;
    }
    if( hist[3] > hist[max_channel] ) {
        max_channel = 3;
    }

    // 최소 개수는 무의미하게 처리하게 함.
    return max_channel;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CMakeAET::SetCWParameter
        \author   조철희
        \param    pNewAet 인자형태 STR_NEWAET *
        \return   void
        \version  0.0.57
        \date     2008-11-13 16:05:22
        \warning
*/
//void CMakeAET::SetCWParameter( STR_NEWAET *pNewAet )
//{
//    // CW 신호 이면 PRI 및 PW 를 강제 설정한다.
//    if( pNewAet->aet.sigType == ST_CW || pNewAet->aet.sigType == ST_CW_FMOP ) {
//        pNewAet->aet.pri.type = _STABLE;
//        pNewAet->aet.pri.mean = pNewAet->aet.pri.min = pNewAet->aet.pri.max = UMUL( 140, _spOneMicrosec );
//        pNewAet->aet.pw.mean = pNewAet->aet.pw.min = pNewAet->aet.pw.max = UMUL( INIT_CW_PULSEWIDTH, _spOneMicrosec );
//
//    }
//
//
//}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CMakeAET::DiscardEmitter
        \author   조철희
        \return   void
        \version  0.0.59
        \date     2008-11-19 11:41:21
        \warning
*/
// void CMakeAET::DiscardEmitter()
// {
// 	int i, j, k, coMatch, pdw_count;
// 	UINT *pParam;
// 	UINT ratioRef, ratioCmp;
// 	PDWINDEX *pRefPdwIndex, *pCmpPdwIndex;
// 	STR_NEWAET *pRefMakeAet, *pCmpMakeAet;
// 	STR_EMITTER *pRefEmitter, *pCmpEmitter;
//
// 	pRefMakeAet = & m_Aet[m_CoMakeAet];
// 	for( i=m_CoMakeAet ; i < m_CoAet ; ++i ) {
// 		if( pRefMakeAet->ext.mark == DELETE_AET )
// 			continue;
//
// 		// 비교 PDW 펄스열 인덱스 초기화
// 		pParam = m_pPdwParam->pParam;
// 		memset( pParam, 0, sizeof( UINT ) * m_nMaxPdw );
//
// 		pRefEmitter = & m_pEmitter[pRefMakeAet->ext.idxEmitter];
// 		pdw_count = pRefEmitter->pdw.count;
//
// 		pRefPdwIndex = pRefEmitter->pdw.pIndex;
// 		for( j=0 ; j < pdw_count ; ++j )
// 			pParam[ *pRefPdwIndex++ ] = 1;
//
// 		pCmpMakeAet = & m_Aet[i+1];
// 		for( j=i+1 ; j < m_CoAet ; ++j ) {
// 			if( pCmpMakeAet->ext.mark == DELETE_AET )
// 				continue;
//
// 			pCmpEmitter = & m_pEmitter[pCmpMakeAet->ext.idxEmitter];
// 			pdw_count = pdw_count = pCmpEmitter->pdw.count;
//
// 			pCmpPdwIndex = pCmpEmitter->pdw.pIndex;
// 			for( k=coMatch=0 ; k < pdw_count ; ++k ) {
// 				if( pParam[ *pCmpPdwIndex++ ] == 1 )
// 					++coMatch;
// 			}
//
// 			ratioRef = UDIV( 100 * coMatch, pRefEmitter->pdw.count );
// 			ratioCmp = UDIV( 100 * coMatch, pCmpEmitter->pdw.count );
//
// 			if( ratioRef >= 70 || ratioCmp >= 70 ) {
// 				if( pRefEmitter->pdw.count > pCmpEmitter->pdw.count )
// 					pCmpMakeAet->ext.mark = DELETE_AET;
// 				else {
// 					pRefMakeAet->ext.mark = DELETE_AET;
// 					break;
// 				}
// 			}
//
// 			++ pCmpMakeAet;
//
// 		}
//
// 		++ pRefMakeAet;
// 	}
//
// 	// PrintAllEmitter();
//
// }

//////////////////////////////////////////////////////////////////////////
/*! \brief    CMakeAET::ReMakeEmitter
        \author   조철희
        \return   void
        \version  0.0.59
        \date     2008-11-19 13:19:48
        \warning
*/
// void CMakeAET::ReMakeEmitter()
// {
// 	int i, aet_index;
// 	int co_delete_aet, remains;
// 	STR_NEWAET *pMakeAet;
// 	STR_EMITTER *pEmitter;
//
// 	co_delete_aet = aet_index = 0;
// 	pMakeAet = & m_Aet[m_CoMakeAet];
// 	for( i=m_CoMakeAet ; i < m_CoAet ; ++i ) {
// 		if( pMakeAet->ext.mark == DELETE_AET ) {
// 			++ co_delete_aet;
// 			remains = m_CoAet - i - 1;
//
// 			memcpy( pMakeAet, pMakeAet+1, sizeof(STR_NEWAET)*remains );
// 		}
// 		else {
// 			pEmitter = & m_pEmitter[pMakeAet->ext.idxEmitter];
//
// 			// 에미터로 작성한 펄스열 저장하기
// 			SaveEmitterPdwFile( pEmitter, aet_index );
//
// 			++ aet_index;
// 			++ pMakeAet;
//
// 		}
//
// 	}
//
// 	m_CoAet -= co_delete_aet;
//
// }

//////////////////////////////////////////////////////////////////////////
/*! \brief    CMakeAET::ConvertRealFreq
        \author   조철희
        \param    pFrq 인자형태 STR_FRQ *
        \return   void
        \version  0.0.62
        \date     2008-12-05 14:37:35
        \warning
*/
void CMakeAET::ConvertRealFreq( STR_FRQ *pFrq )
{
#ifdef _REAL_FREQ_
    pFrq->iMean = FRQCNV( pFrq->iBand, pFrq->iMean );
    if( pFrq->iBand == (BAND1+1) || pFrq->iBand == (BAND4+1) ) {
        pFrq->iMin = F_FRQCNV( pFrq->iBand, pFrq->iMin );
        pFrq->iMax = C_FRQCNV( pFrq->iBand, pFrq->iMax );
    }
    else {
        int backup=pFrq->iMin;

        pFrq->iMin = F_FRQCNV( pFrq->iBand, pFrq->iMax );
        pFrq->iMax = C_FRQCNV( pFrq->iBand, backup );
    }
#endif

}

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
    int i;
    STR_MINMAX stVal;
    STR_MINMAX_SDEV stVal2;
    SRxLOBData *pLOBData;

    float fDiff;

    STR_FRQ stFrq;
    STR_PRI stPri;

    // LOB 데이터를 생성하기 위한 LOB 데이터 얻기
    pLOBData = GetLOBData(iLOBData);

    memset( pLOBData, 0, sizeof(SRxLOBData) );

    //////////////////////////////////////////////////////////////////////////
    
    pLOBData->uiPDWID = GetPDWID();

    pLOBData->uiPLOBID = iLOBData + 1;
    pLOBData->uiLOBID = _spZero;
    pLOBData->uiABTID = _spZero;
    pLOBData->uiAETID = _spZero;

    // 시간 정보
    struct timespec tsNow;

    GetCollectTime( & tsNow );

    pLOBData->tiContactTime = tsNow.tv_sec;
#ifdef _MSC_VER
    pLOBData->tiContactTimems = tsNow.tv_usec / 1000;
#else
    pLOBData->tiContactTimems = tsNow.tv_nsec;
#endif

    // 신호 형태
    pLOBData->iSignalType = pEmitter->enSignalType;

    // 방위
    MakeAOAInfoFromSeg( & stVal2, pEmitter );
    pLOBData->fDOAMean = FAOACNV( stVal2.iMean );			//FTOAsCNV( stVal.mean );
    pLOBData->fDOAMax = FAOACNV( stVal2.iMax );
    pLOBData->fDOAMin = FAOACNV( stVal2.iMin );
    pLOBData->fDOAMode = FAOACNV( stVal2.iMode );
    fDiff = pLOBData->fDOAMax - pLOBData->fDOAMin;
    if( fDiff < 0 ) {
        pLOBData->fDOADeviation = (float) 360.0 + fDiff;
    }
    else {
        pLOBData->fDOADeviation = fDiff;
    }

    //pLOBData->fDOASDeviation = stVal2.fsdev;

    // DI 율
    pLOBData->iDIRatio = MakeDIInfoFromSeg( pEmitter );							// [0.1%]

    //////////////////////////////////////////////////////////////////////////
    // 주파수 정보 생성
    MakeFrqInfoFromSeg( & stFrq, pEmitter );

    pLOBData->iFreqType = stFrq.iType;
    pLOBData->iFreqPatternType = stFrq.iPatType;
    pLOBData->iFreqPositionCount = stFrq.iSwtLev;

    pLOBData->fFreqPatternPeriod = (float) FTOAsCNV( (_TOA) stFrq.iPatPrd );

#ifdef _POCKETSONATA_
    pLOBData->fFreqMean = FRQMhzCNV( g_enBoardId, stFrq.iMean );      
    pLOBData->fFreqMax = FRQMhzCNV( g_enBoardId, stFrq.iMax );        
    pLOBData->fFreqMin = FRQMhzCNV( g_enBoardId, stFrq.iMin );        
    pLOBData->fDOAMode = FRQMhzCNV( g_enBoardId, stFrq.iMode );
    //pLOBData->fFreqMean = CPOCKETSONATAPDW::DecodeRealFREQMHz( stFrq.iMean, iCh, ( int ) g_enBoardId );
    
    memset( pLOBData->fFreqSeq, 0, sizeof(pLOBData->fFreqSeq) );
    for( i=0 ; i < pLOBData->iFreqPositionCount ; ++i ) {
        pLOBData->fFreqSeq[i] = FRQMhzCNV( g_enBoardId, stFrq.iSwtVal[i] );
    }
#else
    pLOBData->fFreqMean = FMUL( stFrq.iMean, (0.001) );      //FFRQCNV( 0, stFrq.mean );
    pLOBData->fFreqMax = FMUL( stFrq.iMax, (0.001) );        //FFRQCNV( 0, stFrq.max );
    pLOBData->fFreqMin = FMUL( stFrq.iMin, (0.001) );        //FFRQCNV( 0, stFrq.min );
    pLOBData->fFreqMode = FMUL( stFrq.iMode, (0.001) );        //FFRQCNV( 0, stFrq.min );
    
    memset( pLOBData->fFreqSeq, 0, sizeof(pLOBData->fFreqSeq) );
    for( i=0 ; i < pLOBData->iFreqPositionCount ; ++i ) {
        pLOBData->fFreqSeq[i] = FMUL( stFrq.iSwtVal[i], (0.001) );		// FFRQCNV( stFrq.swtVal[i] );
    }
#endif
    pLOBData->fFreqDeviation = pLOBData->fFreqMax - pLOBData->fFreqMin;

    //////////////////////////////////////////////////////////////////////////
    // PRI 정보 생성
    MakePRIInfoFromEmitter( & stPri, pEmitter );

    pLOBData->iPRIType = stPri.iType;
    pLOBData->iPRIPatternType = stPri.iPatType;
#ifdef _POCKETSONATA_
    pLOBData->fPRIPatternPeriod = (float) FTOAsCNV( (_TOA) stPri.iPatPrd );
#else
    pLOBData->fPRIPatternPeriod = FTOAsCNV( (_TOA) stPri.iPatPrd );
#endif    
    pLOBData->fPRIMean = TOAusCNV( stPri.TMean );
    pLOBData->fPRIMax = TOAusCNV( stPri.TMax );
    pLOBData->fPRIMin = TOAusCNV( stPri.TMin );
    pLOBData->fPRIDeviation = TOAusCNV( stPri.TMax-stPri.TMin );
    pLOBData->fPRIMode = TOAusCNV( stPri.TMode );
    pLOBData->fPRIJitterRatio = stPri.fJtrPer;
    pLOBData->iPRIPositionCount = stPri.iSwtLev;
    memset( pLOBData->fPRISeq, 0, sizeof(pLOBData->fPRISeq) );
    for( i=0 ; i < pLOBData->iPRIPositionCount ; ++i ) {
        pLOBData->fPRISeq[i] = TOAusCNV( stPri.TSwtVal[i] );
    }

    //////////////////////////////////////////////////////////////////////////
    // 펄스폭 생성
    MakePWInfoFromSeg( & stVal, pEmitter );
    pLOBData->fPWMean = PWCNV( stVal.iMean ); //CDecode::DecodePWns( stVal.iMean );			//, _spOneMicrosec );
    pLOBData->fPWMax = PWCNV( stVal.iMax );
    pLOBData->fPWMin = PWCNV( stVal.iMin );
    pLOBData->fPWMode = PWCNV( stVal.iMode );
    pLOBData->fPWDeviation = pLOBData->fPWMax - pLOBData->fPWMin;

    //////////////////////////////////////////////////////////////////////////
    // 신호 세기 생성
    MakePAInfoFromSeg( & stVal, pEmitter );
    pLOBData->fPAMean = PACNV( stVal.iMean );			//FPACNV( stVal.mean );
    pLOBData->fPAMax = PACNV( stVal.iMax );				//FPACNV( stVal.max );
    pLOBData->fPAMin = PACNV( stVal.iMin );				//FPACNV( stVal.min );
    pLOBData->fPAMode = PACNV( stVal.iMode );				//FPACNV( stVal.min );
    pLOBData->fPADeviation = pLOBData->fPAMax - pLOBData->fPAMin;

    //////////////////////////////////////////////////////////////////////////
    // 기타 정보 저장
    pLOBData->iIsStoreData = IsStorePDW();
    pLOBData->iNumOfPDW = pEmitter->stPDW.uiCount;
#if defined(_ELINT_) || defined(_XBAND_)
    pLOBData->iCollectorID = GetCollectorID();
    memcpy( pLOBData->aucTaskID, GetTaskID(), sizeof(pLOBData->aucTaskID) );
#endif

    // 수집소 위치 정보 저장
#if defined(_ELINT_) || defined(_XBAND_)
    if( pLOBData->iCollectorID >= RADARCOL_1 && pLOBData->iCollectorID <= RADARCOL_3 ) {
         pLOBData->fLatitude = (float) dRCLatitude[pLOBData->iCollectorID];
         pLOBData->fLongitude = (float) dRCLongitude[pLOBData->iCollectorID];
    }
    else {
         pLOBData->fLatitude = 0.0;
         pLOBData->fLongitude = 0.0;
    }
#else

#endif

    //memset( pLOBData->aucRadarName, 0, sizeof(pLOBData->aucRadarName) );
    pLOBData->iRadarModeIndex = _spZero;
    //pLOBData->iThreatIndex = _spZero;

    //pLOBData->uiSeqNum = 0;

#if defined(_ELINT_) || defined(_XBAND_)
    //STR_PDWDATA *pPDWData = m_pNewSigAnal->GetPDWData();
    //memcpy( pLOBData->aucTaskID, GetTaskID(), sizeof(pLOBData->aucTaskID) );
#elif defined(_POCKETSONATA_)

#else

#endif

#ifdef _XBAND_
	pLOBData->uiOpInitID = GetOpInitID();

#endif

    DISP_FineAet( pLOBData );


}
