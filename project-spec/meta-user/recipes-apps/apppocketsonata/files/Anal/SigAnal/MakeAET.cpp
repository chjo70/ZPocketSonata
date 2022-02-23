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

#include "MakeAET.h"

#include "../../Include/globals.h"
#include "../../Utils/ccommonutils.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern int intparamCompare( const void *arg1, const void *arg2 );
extern int lliparamCompare( const void *arg1, const void *arg2 );

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

//    m_pParam = ( UINT * ) malloc( coMaxPdw * sizeof( UINT ) );
//    if( m_pParam == NULL ) {
//        bRet = FALSE;
//        printf( "\n [W] m_pParam's Memory allocation error !" );
//        WhereIs;
//    }
//     if( bRet == FALSE ) {
//         printf( "\n [W] 에미터 생성 클래스 생성자 실패 !" );
//     }

    m_CoAnalPdw = 0;

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
//    free( m_pParam );
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

    m_CoLOB = 0;
    m_nAnalEmitter = 0;
    m_pEmitter = GetEmitter();
    m_pSeg = GetPulseSeg();

    m_CoAnalPdw = 0;

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

    m_CoEmitter = GetCoEmitter();

    // 에미터 추출 개수를 저장
    m_CoMakeAet = m_CoLOB;

    pEmitter = & m_pEmitter[0];
    for( i=0 ; i < m_CoEmitter ; ++i, ++pEmitter ) {
        if( pEmitter->mark == NORMAL_EMITTER ) {
            // 에미터 생성하기
            MakeAETfromEmitter( pEmitter, i );

            // CW 에미터인 경우, PRI, 펄스폭을 강제 설정한다.
            // SetCWParameter( pNewAet );

            SaveEmitterPdwFile( pEmitter, m_CoLOB+1 );

            ++ m_CoLOB;
        }
    }

    /*! \bug  m_CoMakeAet 에서 m_CoAet 까지 에미터에서 펄스열이 겹쳐진 에미터를 제거한다.
        \date 2008-11-19 13:14:29, 조철희
    */
    //DiscardEmitter();
    //ReMakeEmitter();

    // 한번의 에미터 생성후에 만들어진 에미터 생성 개수
    m_CoMakeAet = m_CoLOB - m_CoMakeAet;

    m_nAnalEmitter = m_CoEmitter;

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
// 	MakePRIInfoInSeg( & pNewAet->aet.pri, pEmitter );
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
void CMakeAET::MakeFrqInfoInSeg( STR_FRQ *pFrq, STR_EMITTER *pEmitter )
{
    unsigned int i;
    int count;

    STR_PULSE_TRAIN_SEG *pSeg;

    memset( pFrq, 0, sizeof(STR_FRQ) );

    // 주파수 밴드 저장
    pSeg = & m_pSeg[ pEmitter->main_seg ];
    pFrq->band = m_pBAND[ pSeg->pdw.pIndex[0] ];

    // 주파수 타입 결정
    pFrq->type = pEmitter->freq_type;

    // 주파수 범위 결정
    switch( pEmitter->freq.type ) {
        case _FIXED :
            // 주파수의 노이즈를 고려해서 평균값을 계산하도록 한다.
            //-- 조철희 2006-05-09 12:26:19 --//
            pFrq->mean = CalcFreqMedian( pSeg );
            pFrq->min = pEmitter->freq.min;
            pFrq->max = pEmitter->freq.max;
            break;

        case _PATTERN_AGILE :
            pFrq->patPrd = UMUL( 1, pEmitter->freqPeriod );
            pFrq->patType = pEmitter->freq_patterntype;
            pFrq->type = _PATTERN_AGILE;

            // 펄스열로부터 주파수 최대값과 최소값을 얻는다.
            count = 0;
            pFrq->max = 0;
            pFrq->min = 0xffffff;
            pFrq->mean = 0;
            for( i=0 ; i < pEmitter->uiCoSeg ; ++i ) {
                pSeg = & m_pSeg[ pEmitter->seg_idx[i] ];
                pFrq->min = _min( pFrq->min, pSeg->freq.min );
                pFrq->max = _max( pFrq->max, pSeg->freq.max );
                pFrq->mean += ( pSeg->pdw.uiCount * pSeg->freq.mean );
                count += pSeg->pdw.uiCount;
            }
            pFrq->mean = UDIV( pFrq->mean, count );
            break;

        case _RANDOM_AGILE :
            if( pFrq->type == _HOPPING ) {
                pFrq->mean = pSeg->freq.mean;
                pFrq->min = pSeg->freq.min;
                pFrq->max = pSeg->freq.max;

            }
            else {
                // 펄스열로부터 주파수 최대값과 최소값을 얻는다.
                count = 0;
                pFrq->max = 0;
                pFrq->min = 0xffffff;
                pFrq->mean = 0;
                for( i=0 ; i < pEmitter->uiCoSeg ; ++i ) {
                    pSeg = & m_pSeg[ pEmitter->seg_idx[i] ];
                    pFrq->min = _min( pFrq->min, pSeg->freq.min );
                    pFrq->max = _max( pFrq->max, pSeg->freq.max );
                    pFrq->mean += ( pSeg->pdw.uiCount * pSeg->freq.mean );
                    count += pSeg->pdw.uiCount;
                }
                pFrq->mean = UDIV( pFrq->mean, count );
            }
            break;

        case _HOPPING :
            /*! \bug  주파수 호핑값을 계산한다.
                \date 2008-10-30 15:49:17, 조철희
            */
            pFrq->type = _HOPPING;
            pFrq->max = pEmitter->freq.max;
            pFrq->min = pEmitter->freq.min;
            pFrq->mean = pEmitter->freq.mean;

            // 호핑 레벨값을 산출한다.
            pFrq->swtLev = pEmitter->hop_level_cnt;
            memcpy( pFrq->swtVal, pEmitter->hop_level, _min( MAX_FREQ_PRI_STEP, pFrq->swtLev )*sizeof(int) );
            break;

        default:
            break;

    }

    // ConvertRealFreq( pFrq );

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CMakeAET::MakePRIInfoInSeg
// 반환되는 형  : void
// 함 수 인 자  : STR_PRI *pPri
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-13 14:56:16
//
//##ModelId=428832A201F6
void CMakeAET::MakePRIInfoInSeg(STR_PRI *pPri, STR_EMITTER *pEmitter)
{
    unsigned int i;
    
    int j, count;
    int min_index, min_stagger_level, stagger_level_index;

    STR_PULSE_TRAIN_SEG *pSeg;

    memset( pPri, 0, sizeof(STR_PRI) );

    // PRI 값을 산출할 때는 병합된 펄스열로부터 계산한다.
    // 이전에는 주 펄스열로부터 계산했는데 가장 많은 개수를 가진 펄스열이
    // 하모닉 신호이기 때문에 PRI 계산은 모든 펄스열로부터 계산한다.

    // PRI 타입을 결정한다.
    pPri->type = pEmitter->pri_type;

    // PRI 타입별 PRI 최대, 최소 저장
    switch( pEmitter->pri_type ) {
        // 스태거 또는 Dwell 일 때 스태거 레벨 값을 근거로 PRI 값을 설정한다.
        case _STAGGER :
            /*! \todo	스태거 레벨을 가장 작은 값부터 레벨값을 시작하게 한다. */
            // 스태거 레벨 에서 가장 작은 레벨값과 인덱스 값을 얻는다.
            min_index = 0;
            min_stagger_level = UDIV( pEmitter->stag_dwell_level[0], _spOneMicrosec );
            for( j=1 ; j < pEmitter->iStagDwellLevelCount && j < MAX_FREQ_PRI_STEP ; ++j ) {
                if( min_stagger_level > (int) UDIV( pEmitter->stag_dwell_level[j], _spOneMicrosec ) ) {
                    min_index = j;
                    min_stagger_level = UDIV( pEmitter->stag_dwell_level[j], _spOneMicrosec );
                }
            }
            /*! \bug  역방향으로 작은 레벨값을 검색해서 제일 작은 레벨 값을 시작으로 한다.
                \date 2006-08-16 20:18:43, 조철희
            */
            //
            stagger_level_index = min_index;
            for( j=1 ; j < pEmitter->iStagDwellLevelCount && j < MAX_FREQ_PRI_STEP ; ++j ) {
                stagger_level_index = ( pEmitter->iStagDwellLevelCount + stagger_level_index - 1 ) % pEmitter->iStagDwellLevelCount;
                if( TRUE == CompMeanDiff<_TOA>( pEmitter->stag_dwell_level[stagger_level_index], pEmitter->stag_dwell_level[min_index], ITTOAusCNV( (_TOA) 1) ) ) {
                    min_index = stagger_level_index;
                }
                else {
                    break;
                }
            }
            _EQUALS3( pPri->min, pPri->max, pEmitter->stag_dwell_level[min_index] );

            // 그 인덱스 값부터 에미터의 스태거단에 기록한다.
            // 그리고 PRI 범위와 평균값을 기록한다.
            pPri->mean = 0;
            for( j=0 ; j < (int) pEmitter->iStagDwellLevelCount && j < MAX_FREQ_PRI_STEP ; ++j ) {
                pPri->swtVal[j] = pEmitter->stag_dwell_level[(min_index+j) % pEmitter->iStagDwellLevelCount];
                pPri->min = _min( pPri->min, pPri->swtVal[j] );
                pPri->max = _max( pPri->max, pPri->swtVal[j] );
                pPri->mean += pPri->swtVal[j];
            }
            pPri->mean = UDIV( pPri->mean, j );

            // 이상 에미터 제원은 삭제 또는 제원을 변경한다.
            // 스태거일 때는 PRI 제원을 확인하여 Jitter율이 작거나 PRI 범위 STABLE_MARGIN 범위에 들면 STABLE로 간주한다.
            //-- 조철희 2005-09-29 15:53:46 --//
            pPri->jtrPer = FDIV( 100 * ( pPri->max - pPri->min ), pPri->mean );
            if( CompMeanDiff<_TOA>( pPri->max, pPri->min, 2*STABLE_MARGIN ) == TRUE ) {
                pPri->type = _STABLE;
            }
            // 지터율이 50%이상인 펄스열은 지터율로 정의 한다.
            else if( pPri->jtrPer >= MAX_JITTER_P ) {
                pSeg = & m_pSeg[ pEmitter->main_seg ];

                if( pSeg->pri_type == _STABLE ) {
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
                    pPri->min = pSeg->pri.min;
                    pPri->max = pSeg->pri.max;
                    pPri->mean = pSeg->pri.mean;

                    pPri->type = _JITTER_RANDOM;
                    memset( pPri->swtVal, 0, sizeof( pPri->swtVal ) );
                }

            }
            else {
                // PRI 타입을 결정한다.
                pPri->type = _STAGGER;
            }
            pPri->swtLev = pEmitter->iStagDwellLevelCount;
            break;

        case _DWELL :
            _EQUALS3( pPri->min, pPri->max, pEmitter->stag_dwell_element[0] );

            pPri->swtLev = _min( pEmitter->iStagDwellElementCount, MAX_FREQ_PRI_STEP );

            // 그 인덱스 값부터 에미터의 레벨단에 기록한다.
            // 그리고 PRI 범위와 평균값을 기록한다.
            for( i=1 ; i < pEmitter->iStagDwellElementCount && i < MAX_FREQ_PRI_STEP ; ++i ) {
                pPri->min = _min( pPri->min, pEmitter->stag_dwell_element[i] );
                pPri->max = _max( pPri->max, pEmitter->stag_dwell_element[i] );
            }

            _EQUALS3( pPri->mean, count, 0 );
            for( i=0 ; i < pEmitter->uiCoSeg ; ++i ) {
                pSeg = & m_pSeg[ pEmitter->seg_idx[i] ];
                pPri->mean += ( pSeg->pri.mean * pSeg->pdw.uiCount );
                count += pSeg->pdw.uiCount;
            }
            pPri->mean = UDIV( pPri->mean, count );

            // DWELL 레벨값들을 작은 값부터 정렬화한다.
            memcpy( pPri->swtVal, pEmitter->stag_dwell_element, sizeof(_TOA)*pPri->swtLev );
            qsort( pPri->swtVal, (size_t) pPri->swtLev, sizeof( _TOA ), lliparamCompare );

            //pPri->swtLev = pEmitter->stag_dwell_element_cnt;
            break;

        case _JITTER_RANDOM :
            /*! \bug  지터 신호에서 각 추출된 펄스열의 DTOA 간격을 구해서 이 구간이 Stable 형태 마진 안에 있으면
                                Stable 형태로 결정 한다.
                \date 2006-05-15 16:46:01, 조철희
            */
            /*! \todo	PRI 형태가 변화되는 것을 에미터 병합에서 변화되는 것을 확인해야 한다. */

            pPri->min = m_pSeg[ pEmitter->seg_idx[ 0 ] ].pri.min;
            pPri->max = m_pSeg[ pEmitter->seg_idx[ 0 ] ].pri.max;
            for( i=1 ; i < pEmitter->uiCoSeg ; ++i ) {
                pSeg = & m_pSeg[ pEmitter->seg_idx[ i ] ];
                pPri->min = _min( pPri->min, m_pSeg[ pEmitter->seg_idx[ 0 ] ].pri.min );
                pPri->max = _max( pPri->max, m_pSeg[ pEmitter->seg_idx[ 0 ] ].pri.max );
            }
            if( CompMeanDiff<_TOA>( pPri->max, pPri->min, 2*STABLE_MARGIN ) == TRUE ) {
                // pPri->type = _STABLE;
            }

            pSeg = & m_pSeg[ pEmitter->main_seg ];
            pPri->min = pSeg->pri.min;
            pPri->max = pSeg->pri.max;
            pPri->mean = pSeg->pri.mean;
            break;

        case _JITTER_PATTERN :
            pPri->patPrd = UMUL( 1, pEmitter->priPeriod );
            pPri->patType = pEmitter->pri_patterntype;
            pSeg = & m_pSeg[ pEmitter->main_seg ];
            pPri->min = pSeg->pri.min;
            pPri->max = pSeg->pri.max;
            pPri->mean = pSeg->pri.mean;
            break;

        case _STABLE :
            pPri->min = m_pSeg[ pEmitter->seg_idx[ 0 ] ].pri.min;
            pPri->max = m_pSeg[ pEmitter->seg_idx[ 0 ] ].pri.max;
            for( i=1 ; i < pEmitter->uiCoSeg ; ++i ) {
                pSeg = & m_pSeg[ pEmitter->seg_idx[ i ] ];
                pPri->min = _min( pPri->min, m_pSeg[ pEmitter->seg_idx[ 0 ] ].pri.min );
                pPri->max = _max( pPri->max, m_pSeg[ pEmitter->seg_idx[ 0 ] ].pri.max );
            }
            if( CompMeanDiff<_TOA>( pPri->max, pPri->min, 2*STABLE_MARGIN ) == FALSE ) {
                pPri->type = _JITTER_RANDOM;
            }

            // 하모닉 관계이면 제일 작은 PRI로 계산을 해야 한다.
            // 현재로서는 펄스열 중에서 제일 센 놈으로 한다.
            //-- 조철희 2005-10-12 13:22:47 --//
            pSeg = & m_pSeg[ pEmitter->main_seg ];
            pPri->min = pSeg->pri.min;
            pPri->max = pSeg->pri.max;
            pPri->mean = pSeg->pri.mean;
            break;

        default :
            pPri->max = 0;
            pPri->min = 0xffffff;
            pPri->mean = 0;
            // PRI 평균값을 계산상 버그
            for( i=0 ; i < pEmitter->uiCoSeg ; ++i ) {
                pSeg = & m_pSeg[ pEmitter->seg_idx[i] ];
                pPri->min = _min( pPri->min, pSeg->pri.min );
                pPri->max = _max( pPri->max, pSeg->pri.max );
                pPri->mean += ( pSeg->pdw.uiCount * pSeg->pri.mean );
            }
            pPri->mean = UDIV( pPri->mean, pEmitter->pdw.uiCount );
            break;
    }

    // 지터율 과 레벨값을 저장한다.
    pPri->jtrPer = FDIV( 100. * ( pPri->max - pPri->min ), pPri->mean );
    //pPri->swtLev = pEmitter->stag_dwell_element_cnt;

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
void CMakeAET::MakePWInfoInSeg(STR_MINMAX *pPw, STR_EMITTER *pEmitter)
{
    unsigned int i;
    STR_MINMAX pw;
    STR_PULSE_TRAIN_SEG *pSeg;

    pSeg = & m_pSeg[ pEmitter->main_seg ];

    // 펄스폭의 평균값 계산
    pPw->mean = pSeg->pw.mean;
    //-- 조철희 2005-05-20 11:01:44 --//
    // 중간값으로 PW의 평균을 결정한다.
    pPw->mean = VerifyPW( pEmitter->pdw.pIndex, pEmitter->pdw.uiCount );

    // 펄스폭의 최대/최소값 계산
    pw.max = 0;
    pw.min = 0xffffff;
    for( i=0 ; i < pEmitter->uiCoSeg ; ++i ) {
        pSeg = & m_pSeg[ pEmitter->seg_idx[i] ];
        if( i > 0 ) {
            pw.min = _min( pw.min, pSeg->pw.min );
            pw.max = _max( pw.max, pSeg->pw.max );
        }
        else {
            pw.min = pSeg->pw.min;
            pw.max = pSeg->pw.max;
        }
    }

    pPw->min = pw.min;
    pPw->max = pw.max;
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
void CMakeAET::MakePAInfoInSeg(STR_MINMAX *pPa, STR_EMITTER *pEmitter)
{
    unsigned int i;
    STR_MINMAX pa;
    STR_PULSE_TRAIN_SEG *pSeg;

    // 신호 세기의 최소 최대값은 모든 펄스열에서 최대, 최소 값으로 한다.
    pa.max = 0;
    pa.min = 0;
    for( i=0 ; i < pEmitter->uiCoSeg ; ++i ) {
        pSeg = & m_pSeg[ pEmitter->seg_idx[i] ];
        if( i > 0 ) {
            pa.min = _min( pa.min, pSeg->pa.min );
            pa.max = _max( pa.max, pSeg->pa.max );
        }
        else {
            pa.min = pSeg->pa.min;
            pa.max = pSeg->pa.max;
        }
    }
    pPa->min = pa.min;
    pPa->max = pa.max;

    // 신호 세기 평균은 매인 펄스열에서 선택한다.
    // pSeg = & m_pSeg[ pEmitter->main_seg ];
    pPa->mean = CalcPAMean( pEmitter->pdw.pIndex, pEmitter->pdw.uiCount );
}

/**
  * @brief
  * @param		STR_EMITTER * pEmitter
  * @return 	int
  * @date			2019/04/09 10:43
*/
int CMakeAET::MakeDIInfoInSeg( STR_EMITTER *pEmitter)
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
void CMakeAET::MakeAOAInfoInSeg(STR_MINMAX_SDEV *pAoa, STR_EMITTER *pEmitter)
{
    unsigned int i;
    int diffAoa, overAoa, frstAoaMax, frstAoaMin;
    STR_MINMAX aoa;
    STR_PULSE_TRAIN_SEG *pSeg;

    // 방위의 최소 최대값은 모든 펄스열에서 최대, 최소 값으로 한다.
    pSeg = & m_pSeg[ pEmitter->seg_idx[0] ];
    if( pEmitter->uiCoSeg == 1 ) {
        pAoa->max = pSeg->aoa.max;
        pAoa->min = pSeg->aoa.min;
    }
    else {
        aoa.max = -9999999;
        aoa.min = 0xffffff;
        frstAoaMax = pSeg->aoa.max;
        frstAoaMin = pSeg->aoa.min;

        for( i=0 ; i < pEmitter->uiCoSeg ; ++i ) {
            pSeg = & m_pSeg[ pEmitter->seg_idx[i] ];

            diffAoa = (int) pSeg->aoa.min - frstAoaMin;
            overAoa = _abs( diffAoa );
            if( overAoa > MAX_AOA/2 ) {
                if( frstAoaMin > MAX_AOA/2 ) {
                    diffAoa = diffAoa + MAX_AOA;
                }
                else {
                    diffAoa = diffAoa - MAX_AOA;
                }
            }
            aoa.min = _min( aoa.min, diffAoa );

            diffAoa = (int) pSeg->aoa.max - frstAoaMax;
            overAoa = _abs( diffAoa );
            if( overAoa > MAX_AOA/2 ) {
                if( frstAoaMax > MAX_AOA/2 ) {
                    diffAoa = diffAoa + MAX_AOA;
                }
                else {
                    diffAoa = diffAoa - MAX_AOA;
                }
            }
            aoa.max = _max( aoa.max, diffAoa );

        }
        pAoa->min = ( MAX_AOA + aoa.min + frstAoaMin ) % MAX_AOA;
        pAoa->max = ( MAX_AOA + aoa.max + frstAoaMax ) % MAX_AOA;

        diffAoa = pAoa->max - pAoa->min;
        if( diffAoa > MAX_AOA/2 ) {
            diffAoa = pAoa->max;
            pAoa->max = pAoa->min;
            pAoa->min = diffAoa;
        }

    }

    // 방위 값 산출시에 스캔형태가 고정형이면
    // 평균 통계 수식으로 값을 산출하고
    // 그 이외의 스캔형태는 신호세기에 의한 정렬으로 방위값을 산출한다.

    // 구현: 김경석
    // 수정: 조철희
    //-- 조철희 2005-07-12 16:39:34 --//
    pSeg = & m_pSeg[ pEmitter->main_seg ];
#if defined( _GSKIMF_AOAMEANALG_200505_1 )
  pAoa->mean = CalcAoaMean_GSKIMF_200505_1( pSeg );	// 김경석
#elif defined( _GSKIMF_AOAMEANALG_200505_2 )
  pAoa->mean = CalcAoaMean_GSKIMF_200505_2( pSeg );	// 김경석
#elif defined( _GSKIMF_AOAMEANALG_200505_3 )
    pAoa->mean = CalcAoaMean_GSKIMF_200505_3( pSeg );	// 김경석
#elif defined( _GSKIMF_AOAMEANALG_200505_6 )
    // 방위 히스토그램을 이용해서 방위를 계산함.
    pAoa->mean = CalcAoaMean_GSKIMF_200505_6( pEmitter );
#else// defined( _CHJO_AOAMEANALG_200503 )
    // 방위 평균은 메인 펄스열에서 선택한다.
    pAoa->mean = pSeg->aoa.mean;
#endif

    // 표준 편차 계산
    int iDiff;
    unsigned int uiSum=0;
    PDWINDEX *pPdwIndex = pEmitter->pdw.pIndex;
    for( i=0 ; i < pEmitter->pdw.uiCount ; ++i ) {
        iDiff = pAoa->mean - m_pAOA[ *pPdwIndex++ ];
        if( iDiff > MAX_AOA / 2 ) {
            iDiff = ( MAX_AOA - iDiff );
        }
        else if( iDiff < -MAX_AOA / 2 ) {
            iDiff = ( iDiff + MAX_AOA ) % MAX_AOA;
        }
        uiSum += ( iDiff * iDiff );

    }
    pAoa->fsdev = sqrt( FDIV( uiSum, pEmitter->pdw.uiCount ) );

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
    return CalcAoaMeanByHistAoa( & pEmitter->pdw );

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
void CMakeAET::MakeExtInfoInSeg( STR_EXT *pExt, STR_EMITTER *pEmitter )
{
    // int band;
    STR_PULSE_TRAIN_SEG *pSeg;

    // 주파수 밴드 저장
    pSeg = & m_pSeg[ pEmitter->main_seg ];

    pExt->noCol = m_nCoPdw;
    pExt->noExt = pEmitter->pdw.uiCount;

    // PDW STAT 를 에미터에 기록한다.
    //-- 조철희 2005-11-04 17:44:48 --//
    pExt->pt_stat = pSeg->stat;

    pExt->bOverId = FALSE;

    pExt->noMergeEMT = -1;

    // band = BAND[ pSeg->pdw.pIndex[0] ];
    pExt->frq.iLow = pEmitter->freq.min;
    pExt->frq.iHgh = pEmitter->freq.max;

    pExt->idxEmitter = -1;

    pExt->pt_maxchannel = CalMaxChannel( & pEmitter->pdw );

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

    SRxLOBData *pLOB;

    if( m_CoLOB == 0 ) {
        //printf( "\n\n LOB 개수 : None." );
        Log( enNormal, "LOB : None." );
    }
    else {
        //printf( "\n\n LOB 개수 : %d", m_CoLOB );
        Log( enNormal, "LOB : %d", m_CoLOB );
        pLOB = GetLOBData();		//& m_LOBData[0];

    // printf( "\n---- PAET[%3d] -----------------------------------------------------------------------------------------------------------" , m_CoMakeAet );
    //printf( "\n### AOA      Freq(MHz)                PRI(us)                PA(dB)        PW(ns)         AS(s)       SeenTime    IPL   T FSP    PPP");
    //printf( "\n              T       Mean   Min   Max T       Mean  Min  Max Mean Min Max  Mean  Min  Max T    Prd    First Last  C Am    (us)   (us)");
    //printf( "\n------------------------------------------------------------------------------------------------------------------------------------" );
        for( i=0 ; i < m_CoLOB ; ++i ) {
            //printf("\n\t\t[%02d]" , i+1 );
            DISP_FineAet( pLOB );
            //printf("\n");
            ++ pLOB;
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
/*! \brief    DISP_FineAet
        \author   조철희
        \param    pNewAet 인자형태 STR_NEWAET *
        \return   void
        \version  0.0.30
        \date     2008-07-18 16:55:09
        \warning
*/
// void CMakeAET::DISP_FineAet( SRxLOBData *pLOB )
// {
// 	int i;
// 	UINT temp;
//
// 	char buff1[20], buff2[20], buff3[20], buff4[20];
//
// 	Printf( "\n" );
//
// // 	if( pNewAet->ext.mark == DELETE_AET )
// // 		Printf( "%3d " , -1 );
// // 	else
// // 		Printf( "%3d " , pNewAet->aet.noEMT );
// 	Printf( "%03d(%03d,%03d)" , AOACNV( pLOB->fMeanDOA ), F_AOACNV( pLOB->fMinDOA ), C_AOACNV( pLOB->fMaxDOA ) );
// //
// // 	// 주파수
// // 	Printf( " %s" , aet_signal_type[pNewAet->aet.sigType] );
// // 	Printf( " %s" , aet_freq_type[pNewAet->aet.frq.type] );
// // 	temp = abs( pNewAet->aet.frq.max - pNewAet->aet.frq.min );
// // 	/*
// // 	sprintf_s( buff1, "%5d" , FRQCNV( pNewAet->aet.frq.band, pNewAet->aet.frq.mean ) );
// // 	if( pNewAet->aet.frq.band == (BAND1+1) || pNewAet->aet.frq.band == (BAND4+1) ) {
// // 		sprintf_s( buff2, "%5d" , F_FRQCNV( pNewAet->aet.frq.band, pNewAet->aet.frq.min ) );
// // 		sprintf_s( buff3, "%5d" , C_FRQCNV( pNewAet->aet.frq.band, pNewAet->aet.frq.max ) );
// // 	}
// // 	else {
// // 		sprintf_s( buff2, "%5d" , F_FRQCNV( pNewAet->aet.frq.band, pNewAet->aet.frq.max ) );
// // 		sprintf_s( buff3, "%5d" , C_FRQCNV( pNewAet->aet.frq.band, pNewAet->aet.frq.min ) );
// // 	}
// // 	*/
// // 	sprintf_s( buff1, "%5d" , FRQCNV( pNewAet->aet.frq.band, pNewAet->aet.frq.mean ) );
// // 	sprintf_s( buff2, "%5d" , FRQCNV( pNewAet->aet.frq.band, pNewAet->aet.frq.min ) );
// // 	sprintf_s( buff3, "%5d" , FRQCNV( pNewAet->aet.frq.band, pNewAet->aet.frq.max ) );
// // 	sprintf_s( buff4, "%3d" , TOAmsCNV( pNewAet->aet.frq.patPrd ) );
// // 	if( pNewAet->aet.frq.type == PATTERN_AGILE )
// // 		Printf( "%s(%s,%s)%s" , buff1, buff2, buff3, buff4 );
// // 	else {
// // 		// printf( "%s(%s∼%s)%3d" , Comma( buff1 ), Comma( buff2 ), Comma( buff3 ), FRQCNV( pNewAet->aet.frq.band, temp )-FRQCNV( pNewAet->aet.frq.band, 0 ) );
// // 		Printf( "%s(%s,%s)%3d" , buff1, buff2, buff3, FRQRESCNV( pNewAet->aet.frq.band, temp ) );
// // 	}
// //
// // 	// PRI
// // 	if( pNewAet->aet.pri.type == _JITTER_RANDOM )
// // 		Printf( " %s(%2d)" , aet_pri_type[pNewAet->aet.pri.type], pNewAet->aet.pri.jtrPer );
// // 	else if( pNewAet->aet.pri.type == STAGGER || pNewAet->aet.pri.type == DWELL )
// // 		Printf( " %s(%2d)" , aet_pri_type[pNewAet->aet.pri.type], pNewAet->aet.pri.swtLev );
// // 	else
// // 		Printf( " %s    " , aet_pri_type[pNewAet->aet.pri.type] );
// // 	sprintf_s( buff1, "%4d" , TOAusCNV(pNewAet->aet.pri.mean) );
// // 	sprintf_s( buff2, "%4d" , F_TOAusCNV(pNewAet->aet.pri.min) );
// // 	sprintf_s( buff3, "%4d" , C_TOAusCNV(pNewAet->aet.pri.max) );
// // 	Printf( "%s(%s,%s)" , buff1, buff2, buff3 );
// //
// // 	// PW
// // 	sprintf_s( buff1, "%4d" , PWCNV(pNewAet->aet.pw.mean) );
// // 	sprintf_s( buff2, "%4d" , PWCNV(pNewAet->aet.pw.min) );
// // 	sprintf_s( buff3, "%4d" , PWCNV(pNewAet->aet.pw.max) );
// // 	Printf( " %s(%s,%s)" , buff1, buff2, buff3 );
// //
// // 	// PA
// // 	sprintf_s( buff1, "%+03d" , PACNV(pNewAet->aet.pa.mean, pNewAet->aet.frq.band) );
// // 	sprintf_s( buff2, "%+03d" , F_PACNV(pNewAet->aet.pa.min, pNewAet->aet.frq.band) );
// // 	sprintf_s( buff3, "%+03d" , C_PACNV(pNewAet->aet.pa.max, pNewAet->aet.frq.band) );
// // 	Printf( " %s(%s,%s)" , buff1, buff2, buff3 );
// //
// // 	if( pNewAet->aet.pri.type == STAGGER || pNewAet->aet.pri.type == DWELL ) {
// // 		Printf( "\n\tPRI Stagger/Dwell Level[%2d] :" , pNewAet->aet.pri.swtLev );
// // 		for( i=0 ; i < pNewAet->aet.pri.swtLev ; ++i ) {
// // 			Printf( "[%d]" , TOAusCNV( pNewAet->aet.pri.swtVal[i] ) );
// // 		}
// // 	}
//
// }

//////////////////////////////////////////////////////////////////////////
/*! \brief    CMakeAET::DISP_FineAet
        \author   조철희
        \param    pManAet 인자형태 STR_MANAET *
        \return   void
        \version  0.0.35
        \date     2008-08-08 16:06:29
        \warning
*/
// void CMakeAET::DISP_FineAet( LOBDATA *pManAet )
// {
// 	UINT temp;
//
// 	char buff1[20], buff2[20], buff3[20], buff4[20];
//
// 	printf( "\n" );
//
// 	int noSymbol = 0; //GetNoSymbol( pNewAet->aet.noEMT );
// 	if( pManAet->loc.trackFI.bUse == TRUE ) {
// 		if( noSymbol != -1 )
// 			printf( "%1c%2dT%2d" , aet_stat[pManAet->loc.stat], pManAet->loc.trackFI.noFilter, noSymbol );
// 		else
// 			printf( "%1c%2d-" , aet_stat[pManAet->loc.stat], pManAet->loc.trackFI.noFilter );
// 	}
// 	else {
// 		if( pManAet->loc.noThreat != -1 )
// 			printf( "%1c-T%2d" , aet_stat[pManAet->loc.stat], noSymbol );
// 		else
// 			printf( "%1c--" , aet_stat[pManAet->loc.stat] );
// 	}
// 	printf( "%3d " , pManAet->aet.noEMT );
// 	printf( "%03d(%03d,%03d)" , AOACNV( pManAet->aet.aoa ), F_AOACNV( pManAet->ext.aoa.iLow ), C_AOACNV( pManAet->ext.aoa.iHgh ) );
//
// 	// 주파수
// 	printf( " %s" , aet_signal_type[pManAet->aet.sigType] );
// 	printf( " %s" , aet_freq_type[pManAet->aet.frq.type] );
// 	temp = abs( pManAet->aet.frq.max - pManAet->aet.frq.min );
// 	sprintf_s( buff1, "%5d" , FRQCNV( pManAet->aet.frq.band, pManAet->aet.frq.mean ) );
// 	if( pManAet->aet.frq.band == (BAND1+1) || pManAet->aet.frq.band == (BAND4+1) ) {
// 		sprintf_s( buff2, "%5d" , F_FRQCNV( pManAet->aet.frq.band, pManAet->aet.frq.min ) );
// 		sprintf_s( buff3, "%5d" , C_FRQCNV( pManAet->aet.frq.band, pManAet->aet.frq.max ) );
// 	}
// 	else {
// 		sprintf_s( buff2, "%5d" , F_FRQCNV( pManAet->aet.frq.band, pManAet->aet.frq.max ) );
// 		sprintf_s( buff3, "%5d" , C_FRQCNV( pManAet->aet.frq.band, pManAet->aet.frq.min ) );
// 	}
// 	sprintf_s( buff4, "%3d" , TOAmsCNV( pManAet->aet.frq.patPrd ) );
// 	if( pManAet->aet.frq.type == PATTERN_AGILE )
// 		printf( "%s(%s,%s)%s" , Comma( buff1 ), Comma( buff2 ), Comma( buff3 ), Comma( buff4 ) );
// 	else {
// 		// printf( "%s(%s∼%s)%3d" , Comma( buff1 ), Comma( buff2 ), Comma( buff3 ), FRQCNV( pNewAet->aet.frq.band, temp )-FRQCNV( pNewAet->aet.frq.band, 0 ) );
// 		printf( "%s(%s,%s)%3d" , buff1, buff2, buff3, FRQCNV( pManAet->aet.frq.band, temp )-FRQCNV( pManAet->aet.frq.band, 0 ) );
// 	}
//
// 	// PRI
// 	if( pManAet->aet.pri.type == _JITTER_RANDOM )
// 		printf( " %s(%2d)" , aet_pri_type[pManAet->aet.pri.type], pManAet->aet.pri.jtrPer );
// 	else if( pManAet->aet.pri.type == STAGGER || pManAet->aet.pri.type == DWELL )
// 		printf( " %s(%2d)" , aet_pri_type[pManAet->aet.pri.type], pManAet->aet.pri.swtLev );
// 	else
// 		printf( " %s    " , aet_pri_type[pManAet->aet.pri.type] );
// 	sprintf_s( buff1, "%4d" , TOAusCNV(pManAet->aet.pri.mean) );
// 	sprintf_s( buff2, "%4d" , F_TOAusCNV(pManAet->aet.pri.min) );
// 	sprintf_s( buff3, "%4d" , C_TOAusCNV(pManAet->aet.pri.max) );
// 	printf( "%s(%s,%s)" , buff1, buff2, buff3 );
//
// 	// PW
// 	sprintf_s( buff1, "%4d" , PWCNV(pManAet->aet.pw.mean) );
// 	sprintf_s( buff2, "%4d" , PWCNV(pManAet->aet.pw.min) );
// 	sprintf_s( buff3, "%4d" , PWCNV(pManAet->aet.pw.max) );
// 	printf( " %s(%s,%s)" , buff1, buff2, buff3 );
//
// 	// PA
// 	sprintf_s( buff1, "%+03d" , PACNV(pManAet->aet.pa.mean, pManAet->aet.frq.band) );
// 	sprintf_s( buff2, "%+03d" , F_PACNV(pManAet->aet.pa.min, pManAet->aet.frq.band) );
// 	sprintf_s( buff3, "%+03d" , C_PACNV(pManAet->aet.pa.max, pManAet->aet.frq.band) );
// 	printf( " %s(%s,%s)" , buff1, buff2, buff3 );
//
// 	// ID
// 	printf( " [%d][%d,%d,%d,%d,%d]" , pManAet->aet.id.coAmbi, pManAet->aet.id.noIPL[0], pManAet->aet.id.noIPL[1], pManAet->aet.id.noIPL[2], pManAet->aet.id.noIPL[3], pManAet->aet.id.noIPL[4] );

//}


//////////////////////////////////////////////////////////////////////////
/*! \brief    CMakeAET::DISP_HexFineAet
        \author   조철희
        \param    pNewAet 인자형태 STR_NEWAET *
        \return   void
        \version  0.0.33
        \date     2008-07-24 11:46:48
        \warning
*/
// void CMakeAET::DISP_HexFineAet(STR_NEWAET *pNewAet)
// {
// 	UINT temp;
//
// 	char buff1[20], buff2[20], buff3[20], buff4[20];
//
// 	printf( "\n" );
// 	printf( "%3x " , pNewAet->aet.noEMT );
// 	printf( "%03x(%03x,%03x)" , pNewAet->aet.aoa, pNewAet->ext.aoa.iLow, pNewAet->ext.aoa.iHgh );
//
// 	// 주파수
// 	printf( " %s" , aet_signal_type[pNewAet->aet.sigType] );
// 	temp = abs( pNewAet->aet.frq.max - pNewAet->aet.frq.min );
// 	sprintf_s( buff1, "%5x,%1x" , pNewAet->aet.frq.mean, pNewAet->aet.frq.band );
// 	if( pNewAet->aet.frq.band == (BAND1+1) || pNewAet->aet.frq.band == (BAND4+1) ) {
// 		sprintf_s( buff2, "%4x" , pNewAet->aet.frq.min );
// 		sprintf_s( buff3, "%4x" , pNewAet->aet.frq.max );
// 	}
// 	else {
// 		sprintf_s( buff2, "%4x" , pNewAet->aet.frq.max );
// 		sprintf_s( buff3, "%4x" , pNewAet->aet.frq.min );
// 	}
// 	sprintf_s( buff2, "%4x" , pNewAet->aet.frq.min );
// 	sprintf_s( buff3, "%4x" , pNewAet->aet.frq.max );
// 	sprintf_s( buff4, "%3x" , pNewAet->aet.frq.patPrd );
// 	if( pNewAet->aet.frq.type == PATTERN_AGILE )
// 		printf( "%s(%s,%s)%s" , Comma( buff1 ), Comma( buff2 ), Comma( buff3 ), Comma( buff4 ) );
// 	else {
// 		// printf( "%s(%s∼%s)%3d" , Comma( buff1 ), Comma( buff2 ), Comma( buff3 ), FRQCNV( pNewAet->aet.frq.band, temp )-FRQCNV( pNewAet->aet.frq.band, 0 ) );
// 		printf( "%s(%s,%s)%3d" , buff1, buff2, buff3, FRQCNV( pNewAet->aet.frq.band, temp )-FRQCNV( pNewAet->aet.frq.band, 0 ) );
// 	}
//
// 	// PRI
// 	if( pNewAet->aet.pri.type == _JITTER_RANDOM )
// 		printf( " %s(%2d)" , aet_pri_type[pNewAet->aet.pri.type], pNewAet->aet.pri.jtrPer );
// 	else if( pNewAet->aet.pri.type == STAGGER || pNewAet->aet.pri.type == DWELL )
// 		printf( " %s(%2d)" , aet_pri_type[pNewAet->aet.pri.type], pNewAet->aet.pri.swtLev );
// 	else
// 		printf( " %s    " , aet_pri_type[pNewAet->aet.pri.type] );
// 	sprintf_s( buff1, "%4x" , pNewAet->aet.pri.mean );
// 	sprintf_s( buff2, "%4x" , pNewAet->aet.pri.min );
// 	sprintf_s( buff3, "%4x" , pNewAet->aet.pri.max );
// 	printf( "%s(%s,%s)" , buff1, buff2, buff3 );
//
// 	// PW
// 	sprintf_s( buff1, "%4x" , pNewAet->aet.pw.mean );
// 	sprintf_s( buff2, "%4x" , pNewAet->aet.pw.min );
// 	sprintf_s( buff3, "%4x" , pNewAet->aet.pw.max );
// 	printf( " %s(%s,%s)" , buff1, buff2, buff3 );
//
// 	// PA
// 	sprintf_s( buff1, "%03x" , pNewAet->aet.pa.mean );
// 	sprintf_s( buff2, "%03x" , pNewAet->aet.pa.min );
// 	sprintf_s( buff3, "%03x" , pNewAet->aet.pa.max );
// 	printf( " %s(%s,%s)" , buff1, buff2, buff3 );
//
// 	// ID
// 	printf( " [%d][%d,%d,%d,%d,%d]" , pNewAet->aet.id.coAmbi, pNewAet->aet.id.noIPL[0], pNewAet->aet.id.noIPL[1], pNewAet->aet.id.noIPL[2], pNewAet->aet.id.noIPL[3], pNewAet->aet.id.noIPL[4] );
//
// }


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
    int i, max_channel;
    UINT hist[4];
    PDWINDEX *pPdwIndex;
    int count = pPdw->uiCount;

    pPdwIndex = pPdw->pIndex;
    _EQUALS5( hist[0], hist[1], hist[2], hist[3], 0 );
    for( i=0 ; i < count ; ++i ) {
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
    pFrq->mean = FRQCNV( pFrq->band, pFrq->mean );
    if( pFrq->band == (BAND1+1) || pFrq->band == (BAND4+1) ) {
        pFrq->min = F_FRQCNV( pFrq->band, pFrq->min );
        pFrq->max = C_FRQCNV( pFrq->band, pFrq->max );
    }
    else {
        int backup=pFrq->min;

        pFrq->min = F_FRQCNV( pFrq->band, pFrq->max );
        pFrq->max = C_FRQCNV( pFrq->band, backup );
    }
#endif

}

/**
 * @brief CMakeAET::MakeAETfromEmitter
 * @param pEmitter
 * @param idxEmitter
 */
void CMakeAET::MakeAETfromEmitter( STR_EMITTER *pEmitter, int idxEmitter )
{
    int i;
    STR_MINMAX stVal;
    STR_MINMAX_SDEV stVal2;
    SRxLOBData *pLOBData;

    float fDiff;

    STR_FRQ stFrq;
    STR_PRI stPri;

    pLOBData = GetLOBData( m_CoLOB );

    memset( pLOBData, 0, sizeof(SRxLOBData) );

    //////////////////////////////////////////////////////////////////////////

    pLOBData->uiLOBID = m_CoLOB + 1;
    pLOBData->uiABTID = 0;
    pLOBData->uiAETID = 0;

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
    pLOBData->iSignalType = pEmitter->signal_type;

    // 방위
    MakeAOAInfoInSeg( & stVal2, pEmitter );
    pLOBData->fDOAMean = FAOACNV( stVal2.mean );			//FTOAsCNV( stVal.mean );
    pLOBData->fDOAMax = FAOACNV( stVal2.max );				//FTOAsCNV( stVal.min );
    pLOBData->fDOAMin = FAOACNV( stVal2.min );				//FTOAsCNV( stVal.max );
    fDiff = pLOBData->fDOAMax - pLOBData->fDOAMin;
    if( fDiff < 0 ) {
        pLOBData->fDOADeviation = (float) 360.0 + fDiff;
    }
    else {
        pLOBData->fDOADeviation = fDiff;
    }

    pLOBData->fDOASDeviation = stVal2.fsdev;

    // DI 율
    pLOBData->iDIRatio = MakeDIInfoInSeg( pEmitter );							// [0.1%]

    // 주파수 정보 생성
    MakeFrqInfoInSeg( & stFrq, pEmitter );

    pLOBData->iFreqType = stFrq.type;
    pLOBData->iFreqPatternType = stFrq.patType;
    pLOBData->iFreqPositionCount = stFrq.swtLev;

    pLOBData->fFreqPatternPeriod = (float) FTOAsCNV( (_TOA) stFrq.patPrd );

#ifdef _POCKETSONATA_
    pLOBData->fFreqMean = FRQMhzCNV( g_enBoardId, stFrq.mean );      
    pLOBData->fFreqMax = FRQMhzCNV( g_enBoardId, stFrq.max );        
    pLOBData->fFreqMin = FRQMhzCNV( g_enBoardId, stFrq.min );        
    
    memset( pLOBData->fFreqSeq, 0, sizeof(pLOBData->fFreqSeq) );
    for( i=0 ; i < pLOBData->iFreqPositionCount ; ++i ) {
        pLOBData->fFreqSeq[i] = FRQMhzCNV( g_enBoardId, stFrq.swtVal[i] );
    }
#else
    pLOBData->fFreqMean = FMUL( stFrq.mean, (0.001) );      //FFRQCNV( 0, stFrq.mean );
    pLOBData->fFreqMax = FMUL( stFrq.max, (0.001) );        //FFRQCNV( 0, stFrq.max );
    pLOBData->fFreqMin = FMUL( stFrq.min, (0.001) );        //FFRQCNV( 0, stFrq.min );
    
    memset( pLOBData->fFreqSeq, 0, sizeof(pLOBData->fFreqSeq) );
    for( i=0 ; i < pLOBData->iFreqPositionCount ; ++i ) {
        pLOBData->fFreqSeq[i] = FMUL( stFrq.swtVal[i], (0.001) );		// FFRQCNV( stFrq.swtVal[i] );
    }
#endif
    pLOBData->fFreqDeviation = pLOBData->fFreqMax - pLOBData->fFreqMin;


    // PRI 정보 생성
    MakePRIInfoInSeg( & stPri, pEmitter );

    pLOBData->iPRIType = stPri.type;
    pLOBData->iPRIPatternType = stPri.patType;
#ifdef _POCKETSONATA_
    pLOBData->fPRIPatternPeriod = (float) FTOAsCNV( (_TOA) stPri.patPrd );
#else
    pLOBData->fPRIPatternPeriod = FTOAsCNV( (_TOA) stPri.patPrd );
#endif    
    pLOBData->fPRIMean = TOAusCNV( stPri.mean );
    pLOBData->fPRIMax = TOAusCNV( stPri.max );
    pLOBData->fPRIMin = TOAusCNV( stPri.min );
    pLOBData->fPRIDeviation = TOAusCNV( stPri.max-stPri.min );
    pLOBData->fPRIJitterRatio = stPri.jtrPer;
    pLOBData->iPRIPositionCount = stPri.swtLev;
    memset( pLOBData->fPRISeq, 0, sizeof(pLOBData->fPRISeq) );
    for( i=0 ; i < pLOBData->iPRIPositionCount ; ++i ) {
        pLOBData->fPRISeq[i] = TOAusCNV( stPri.swtVal[i] );
    }

    // 펄스폭 생성
    MakePWInfoInSeg( & stVal, pEmitter );
    pLOBData->fPWMean = PWCNV( stVal.mean );			//, _spOneMicrosec );
    pLOBData->fPWMax = PWCNV( stVal.max );				//, _spOneMicrosec );
    pLOBData->fPWMin = PWCNV( stVal.min );				//, _spOneMicrosec );
    pLOBData->fPWDeviation = pLOBData->fPWMax - pLOBData->fPWMin;

    // 신호 세기 생성
    MakePAInfoInSeg( & stVal, pEmitter );
    pLOBData->fPAMean = PACNV( stVal.mean );			//FPACNV( stVal.mean );
    pLOBData->fPAMax = PACNV( stVal.max );				//FPACNV( stVal.max );
    pLOBData->fPAMin = PACNV( stVal.min );				//FPACNV( stVal.min );
    pLOBData->fPADeviation = pLOBData->fPAMax - pLOBData->fPAMin;

    // 기타 정보 저장
    pLOBData->iIsStoreData = IsStorePDW();
    pLOBData->iNumOfPDW = pEmitter->pdw.uiCount;
#if defined(_ELINT_) || defined(_XBAND_)
    pLOBData->iCollectorID = GetCollectorID();
    memcpy( pLOBData->aucTaskID, GetTaskID(), sizeof(pLOBData->aucTaskID) );
#endif

    // 수집소 위치 정보 저장
#if defined(_ELINT_) || defined(_XBAND_)
    if( pLOBData->iCollectorID >= RADARCOL_1 && pLOBData->iCollectorID <= RADARCOL_3 ) {
         pLOBData->fRadarLatitude = (float) dRCLatitude[pLOBData->iCollectorID];
         pLOBData->fRadarLongitude = (float) dRCLongitude[pLOBData->iCollectorID];
    }
    else {
         pLOBData->fRadarLatitude = 0.0;
         pLOBData->fRadarLongitude = 0.0;
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

    DISP_FineAet( pLOBData );


}
