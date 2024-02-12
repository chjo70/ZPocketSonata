// AnalPRI.cpp: implementation of the CAnalPRI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "Hopping.h"

#include "../NewSigAnal/NewSigANal.h"

#include "../Identify/ELUtil.h"

#include "../../Utils/MulDiv64.h"

#include "../../Include/globals.h"

/**
 * @brief     CAnalPRI 객체를 실행시 메모리 및 변수를 초기화한다.
 * @param     unsigned int uiCoMaxPdw
 * @return
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2005-07-28 13:18:51
 * @warning
 */
CHopping::CHopping( void *pParent, ENUM_ANAL_TYPE enAnalType, unsigned int uiCoMaxPdw, const char *pThreadName ) : CLogName( pThreadName )
{
    int iValue;

    //m_uiMaxPdw = min( uiCoMaxPdw, ( unsigned int ) MAX_PDW );
    m_uiMaxPdw = min( MAX_PDW, uiCoMaxPdw );

    m_pTheNewSigAnal = NULL;
    m_pTheKnownSigAnal = NULL;
    m_pTheScanSigAnal = NULL;

#ifdef _DETECT_
    m_pTheNewSigAnal = ( CNewSigAnal * ) pParent;
    INIT_ANAL_VAR_( m_pTheNewSigAnal )

#else
    if( enAnalType == enDET_ANAL ) {
        m_pTheNewSigAnal = ( CNewSigAnal * ) pParent;
        INIT_ANAL_VAR_( m_pTheNewSigAnal )
    }
    else if( enAnalType == enTRK_ANAL ) {
        m_pTheKnownSigAnal = ( CKnownSigAnal * ) pParent;
        INIT_ANAL_VAR_( m_pTheKnownSigAnal )
    }
    else {
        m_pTheScanSigAnal = ( CScanSigAnal * ) pParent;
        INIT_ANAL_VAR_( m_pTheScanSigAnal )
    }
#endif

    float *pfValue = g_pTheSysConfig->GetMargin();
    //m_uiFixedFreqMargin = (unsigned int) FFRQMhzCNV( 0, ( unsigned int ) ( pfValue[0] * ( float ) 1000000. ) );
    m_uiFixedFreqMargin = ( unsigned int ) FFRQMhzCNV( 0, ( unsigned int ) ( 2.0 * ( float ) 1000000. ) );
    m_uiStableMargin = (unsigned int) ITOAusCNV( pfValue[1] );

    m_ptDataX = ( _TOA * ) malloc( sizeof( _TOA ) * m_uiMaxPdw );
#ifndef __VECTORCAST__
    if( m_ptDataX == NULL ) {
        TRACE( "[W] m_ptDataX's memory allocation error !" );
        WhereIs;
    }
#endif

    m_piDiffY = ( int * ) malloc( sizeof( int ) * m_uiMaxPdw );
#ifndef __VECTORCAST__
    if( m_piDiffY == NULL ) {
        TRACE( "[W] m_piDataY's memory allocation error !" );
        WhereIs;
    }
#endif

    m_puiDataY = ( unsigned int * ) malloc( sizeof( int ) * m_uiMaxPdw );
#ifndef __VECTORCAST__
    if( m_puiDataY == NULL ) {
        TRACE( "[W] m_puiDataY's memory allocation error !" );
        WhereIs;
    }
#endif

    m_pCanPeak = ( int * ) malloc( sizeof( int ) * m_uiMaxPdw );
#ifndef __VECTORCAST__
    if( m_pCanPeak == NULL ) {
        TRACE( "[W] m_pCanPeak's memory allocation error !" );
        WhereIs;
    }
#endif

    m_piSampleData = ( int * ) malloc( sizeof( int ) * m_uiMaxPdw );
#ifndef __VECTORCAST__
    if( m_piSampleData == NULL ) {
        TRACE( "[W] m_pSampleData's memory allocation error !" );
        WhereIs;
    }
#endif

    m_puiSampleDataY = ( unsigned int * ) malloc( sizeof( int ) * m_uiMaxPdw );
#ifndef __VECTORCAST__
    if( m_puiSampleDataY == NULL ) {
        TRACE( "[W] m_pSampleDataY's memory allocation error !" );
        WhereIs;
    }
#endif

    m_pSampleToa = ( _TOA * ) malloc( sizeof( _TOA ) * m_uiMaxPdw );
#ifndef __VECTORCAST__
    if( m_pSampleToa == NULL ) {
        TRACE( "[W] m_pSampleToa's memory allocation error !" );
        WhereIs;
    }
#endif

    m_pAcf = ( float * ) malloc( sizeof( float ) * m_uiMaxPdw );
#ifndef __VECTORCAST__
    if( m_pAcf == NULL ) {
        TRACE( "[W] m_pAcf's memory allocation error !" );
        WhereIs;
    }
#endif

    iValue = NEW_COLLECT_PDW / _spTwo;
    m_vecHopping.reserve( (size_t) iValue );

#if 0
    unsigned int i, j;
    SHoppingDwell stHopping;


    TCompMarginDiff<_TOA>( 10, 0, 40, 100 );
    TCompMarginDiff<_TOA>( 50, 0, 40, 100 );

    TCompMarginDiff<unsigned int>( 10, 0, 40, 20 );
    TCompMarginDiff<UINT>( 10, 0, 40, 20 );


    stHopping.uiCoSteps = 34;

    // IsRepeatable( & stHopping, 0, 2 );
    stHopping.iSteps[0] = 23119;
    stHopping.iSteps[1] = 30826;
    stHopping.iSteps[2] = 15413;
    stHopping.iSteps[3] = 16954;
    stHopping.iSteps[4] = 18495;
    stHopping.iSteps[5] = 20036;
    stHopping.iSteps[6] = 21578;
    stHopping.iSteps[7] = 23119;
    stHopping.iSteps[8] = 15413;
    stHopping.iSteps[9] = 16954;
    stHopping.iSteps[10] = 18495;
    stHopping.iSteps[11] = 20036;
    stHopping.iSteps[12] = 21578;
    stHopping.iSteps[13] = 23119;
    stHopping.iSteps[14] = 30826;
    stHopping.iSteps[15] = 15413;
    stHopping.iSteps[16] = 16954;
    stHopping.iSteps[17] = 18495;
    stHopping.iSteps[18] = 20036;
    stHopping.iSteps[19] = 21578;
    stHopping.iSteps[20] = 23119;
    stHopping.iSteps[21] = 15413;
    stHopping.iSteps[22] = 30826;
    stHopping.iSteps[23] = 15413;
    stHopping.iSteps[24] = 16954;
    stHopping.iSteps[25] = 18495;
    stHopping.iSteps[26] = 20036;
    stHopping.iSteps[27] = 21578;
    stHopping.iSteps[28] = 23119;
    stHopping.iSteps[29] = 15413;
    stHopping.iSteps[30] = 15413;
    stHopping.iSteps[31] = 16954;
    stHopping.iSteps[32] = 18495;
    stHopping.iSteps[33] = 20036;

    for( i = 0; i < stHopping.uiCoSteps ; ++i ) {
        stHopping.iSteps[i] = ( int ) TOAusCNV( stHopping.iSteps[i] ) * 100;
        // TRACE( "\n stHopping.iSteps[%d]=%d", i, ( int ) TOAusCNV( stHopping.iSteps[i] ) );
    }

    for( i = 0 ; i < stHopping.uiCoSteps / 2; ++i ) {
        if( IsRepeatable( & stHopping, i, 6 ) == true ) {
            TRACE( "\n 스텝수 : %d", i );
        }
    }

    for( i=2 ; i < stHopping.uiCoSteps/2 ; ++i ) {
        for( j=0 ; j < stHopping.uiCoSteps / 2 ; ++j ) {
            if( IsRepeatable( & stHopping, j, i ) == true ) {
                TRACE( "\n 스텝수 : %d", i );
                break;
            }
        }
    }


#endif


#ifdef __VECTORCAST__
    SHoppingDwell stHopping;

    stHopping.uiCoSteps = MAX_STAGGER_LEVEL_POSITION;
    RemoveRepeatableDwell( & stHopping );

#endif

}

/**
 * @brief     ~CHopping
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-14 09:38:57
 * @warning
 */
CHopping::~CHopping()
{
    free( m_ptDataX );
    free( m_puiDataY );
    free( m_piDiffY );
    free( m_pCanPeak );
    free( m_piSampleData );
    free( m_puiSampleDataY );
    free( m_pSampleToa );
    free( m_pAcf );
}

/**
 * @brief     MakeFreq
 * @param     STR_EMITTER * pEmitter
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-21 16:53:20
 * @warning
 */
void CHopping::MakeFREQ( STR_EMITTER *pEmitter )
{
    unsigned int i;
    PDWINDEX *pPdwIndex;

    unsigned int *pFREQ;

    pFREQ = m_puiDataY;

    pPdwIndex = pEmitter->stPDW.pIndex;

    for( i = 0; i < pEmitter->stPDW.uiCount; ++i ) {
        *pFREQ = m_pFREQ[*pPdwIndex++];
        ++ pFREQ;

    }

}

/**
 * @brief     MakeDTOA
 * @param     STR_EMITTER * pEmitter
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-21 16:36:53
 * @warning
 */
void CHopping::MakeDTOA( STR_EMITTER *pEmitter )
{
    unsigned int i;
    PDWINDEX *pPdwIndex;

    unsigned int *pDTOA;
    _TOA tPreTOA;

    pDTOA = m_puiDataY;

    pPdwIndex = pEmitter->stPDW.pIndex;

    tPreTOA = m_pTOA[*pPdwIndex++];
    for( i = 1 ; i < pEmitter->stPDW.uiCount; ++i ) {
        *pDTOA = (UINT) ( m_pTOA[*pPdwIndex] - tPreTOA );
        tPreTOA = m_pTOA[*pPdwIndex];

        ++ pPdwIndex;
        ++ pDTOA;

    }

}

/**
 * @brief     주파수 호핑 특성 여부를 리턴한다.
 * @param     STR_EMITTER * pEmitter
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2008-10-30 15:16:56
 * @warning
 */
bool CHopping::IsHopping( unsigned int uiMargin )
{
    unsigned int i, j;

    unsigned int value, next_value;
    unsigned int max_value, min_value;

    int iRatio=0;
    int nZeroValue, iCoZeroValue, iTotalZeroValue, nHopLevel;

    iTotalZeroValue = 0;

    nHopLevel = 0;
    for( i = 0 ; i < m_uiCoData; ) {
        iCoZeroValue = 1;
        nZeroValue = 1;
        _EQUALS4( max_value, min_value, value, m_puiDataY[i] )

        for( j = i+1 ; j < m_uiCoData; ++j ) {
            next_value = m_puiDataY[j];
            if( TCompMeanDiff<unsigned int>( next_value, value, uiMargin ) == true ) {
                ++ nZeroValue;
                ++ iCoZeroValue;
                max_value = max( max_value, next_value );
                min_value = min( min_value, next_value );
            }
            else {
                break;
            }
        }

        i = j;

        if( nZeroValue > 1 && ( max_value - min_value ) <= uiMargin ) {
            if( nZeroValue >= HOP_LEVEL_MIN_CNT ) {
                ++ nHopLevel;
            }

            if( nZeroValue >= 3 ) {
                iTotalZeroValue += iCoZeroValue;
            }
        }

    }

    if( m_uiCoData != 0 ) {
        iRatio = ( 100 * iTotalZeroValue ) / (int) m_uiCoData;
    }

    return iRatio >= HOP_RATIO && nHopLevel >= _spTwo;
}

/**
 * @brief     HoppingAnalysis
 * @param     STR_EMITTER * pEmitter
 * @param     ENHOPPING enHopping
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-21 19:32:04
 * @warning
 */
void CHopping::HoppingAnalysis( STR_EMITTER *pEmitter, ENUM_HOPPINGDWELL enHoppingDwell )
{
    m_enHoppingDwell = enHoppingDwell;

    if( m_enHoppingDwell == enFREQ_HOPPING ) {
        m_uiMargin = m_uiFixedFreqMargin;

        m_uiCoData = pEmitter->stPDW.uiCount;

        MakeFREQ( pEmitter );
    }
    else {
        //m_uiMargin = m_uiStableMargin / 2;
        m_uiMargin = m_uiStableMargin;

        m_uiCoData = pEmitter->stPDW.uiCount - 1;

        MakeDTOA( pEmitter );

    }

    HoppingAnalysis( pEmitter );

}

/**
 * @brief     HoppingAnalysis
 * @param     STR_EMITTER * pEmitter
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-14 09:39:09
 * @warning
 */
void CHopping::HoppingAnalysis( STR_EMITTER *pEmitter )
{
    unsigned int i;
    PDWINDEX *pPdwIndex;

    /*! \bug  Hopping 체크를 해서 주파수 Hooping 형태를 기록한다.
        \date 2008-10-30 15:02:52, 조철희
    */
    if( true == IsHopping( m_uiMargin ) ) {
        if( m_enHoppingDwell == enFREQ_HOPPING ) {
            pPdwIndex = pEmitter->stPDW.pIndex;

            // 1. 데이터 변환
            for( i = 0; i < m_uiCoData; ++i ) {
                m_ptDataX[i] = m_pTOA[*pPdwIndex];
                ++ pPdwIndex;
            }

            // 호핑 레벨값 초기화
            pEmitter->uiFreqLevelCount = 0;

        }
        else {
            pPdwIndex = pEmitter->stPDW.pIndex + 1;

            // 1. 데이터 변환
            for( i = 0; i < m_uiCoData; ++i ) {
                m_ptDataX[i] = m_pTOA[*pPdwIndex];
                ++ pPdwIndex;
            }

            // 호핑 레벨값 초기화
            pEmitter->uiCoStagDwellLevelCount = 0;

        }

        // 2. 샘플링 타임을 계산한다.
        CalcSamplingTime( pEmitter );

        // 3. 수집한 PDW 데이터를 시간대 주파수로 샘플링 작업을 한다.
        if( m_enHoppingDwell == enFREQ_HOPPING ) {
            SamplingFREQProcess( pEmitter, enVALUE );
        }
        else {
            SamplingDTOAProcess( pEmitter, enVALUE );
        }

        // 4. Y 값(주파수)에 대해서 미분한다.
        DifferentialY( pEmitter );

        // 5. ACF를 수행합니다.
        AutoCorerelation();

        // 6. 주기 찾기
        FindPeriod();

        // 7. 주기가 있어야 호핑 스텝을 계산합니다.
        if( m_iPeriod > _spZero ) {
            m_uiHoppingLevel = CalcHoppingStepByPeriod();

            if( m_uiHoppingLevel >= _spTwo ) {
                CalcHoppingStep();
            }
            // 주기는 있는데, 호핑레벨이 없을 때 비주기로 레벨을 찾는다.
            else {
                //CalcHoppingStepByNonPeriod2( pEmitter );
                CalcHoppingDwellStepByNonPeriod( pEmitter );
                CalcHoppingStep();
            }

        }
        else {
            CalcHoppingDwellStepByNonPeriod( pEmitter );

            CalcHoppingStep();

        }

        //! #디버깅 : 호핑 레벨이 6이 아닐때 확인하기 위함.
// #ifdef _DEBUG
//         if( m_uiHoppingLevel != 6 ) {
//             SamplingFREQProcess( pEmitter, enVALUE );
//             DifferentialY( pEmitter );
//             CalcHoppingDwellStepByNonPeriod( pEmitter );
//         }
// #endif

        MakeHoppingEmitter( pEmitter );
    }

}

/**
 * @brief     MakeHoppingEmitter
 * @param     STR_EMITTER * pEmitter
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-19 10:32:31
 * @warning
 */
void CHopping::MakeHoppingEmitter( STR_EMITTER *pEmitter )
{
    if( m_uiHoppingLevel >= 2 ) {
        unsigned int i;

        if( m_enHoppingDwell == enFREQ_HOPPING ) {
            unsigned int uiSum;

            pEmitter->enFreqType = _HOPPING;

            pEmitter->uiFreqLevelCount = m_uiHoppingLevel;
            memcpy( pEmitter->uiFreqLevel, m_uiSteps, sizeof( UINT ) * m_uiHoppingLevel );

            uiSum = _spZero;
            pEmitter->stFreq.iMin = (int) pEmitter->uiFreqLevel[0];
            pEmitter->stFreq.iMax = ( int ) pEmitter->uiFreqLevel[0];
            for( i = 0; i < m_uiHoppingLevel && i < MAX_FREQ_PRI_STEP; ++i ) {
                pEmitter->stFreq.iMin = min( pEmitter->stFreq.iMin, (int) pEmitter->uiFreqLevel[i] );
                pEmitter->stFreq.iMax = max( pEmitter->stFreq.iMax, ( int ) pEmitter->uiFreqLevel[i] );
                uiSum += pEmitter->uiFreqLevel[i];
            }
            pEmitter->stFreq.iMean = IDIV( uiSum, i );

            pEmitter->fFreqPeriod = m_fPeriod;
        }
        else {
            _TOA tSum;

            pEmitter->enPRIType = _DWELL;

            pEmitter->uiCoStagDwellLevelCount = m_uiHoppingLevel;

            for( i = 0; i < m_uiHoppingLevel ; ++i ) {
                pEmitter->tStaggerDwellLevel[i] = (_TOA) m_uiSteps[i];
            }

            tSum = _spZero;
            pEmitter->stPRI.tMin = pEmitter->tStaggerDwellLevel[0];
            pEmitter->stPRI.tMax = pEmitter->tStaggerDwellLevel[0];
            for( i = 0; i < m_uiHoppingLevel && i < MAX_FREQ_PRI_STEP; ++i ) {
                pEmitter->stPRI.tMin = min( pEmitter->stPRI.tMin, pEmitter->tStaggerDwellLevel[i] );
                pEmitter->stPRI.tMax = max( pEmitter->stPRI.tMax, pEmitter->tStaggerDwellLevel[i] );
                tSum += pEmitter->tStaggerDwellLevel[i];
            }
            pEmitter->stPRI.tMean = TDIV<_TOA>( tSum, i );

            pEmitter->fPRIPeriod = m_fPeriod;
        }
    }
    else {

    }

}

/**
 * @brief     compareHoppingSteps
 * @param     const SHoppingSteps & a
 * @param     const SHoppingSteps & b
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-19 10:01:36
 * @warning
 */
bool compareHoppingSteps( const SHoppingDwell &a, const SHoppingDwell &b )
{
    bool bRet=true;

    // 호핑 정렬은 개수 가 많은 순으로 정렬합니다.
    bRet = ( a.uiCoSteps > b.uiCoSteps && a.uiAccumulated >= b.uiAccumulated );

    return bRet;
}

/**
 * @brief     CheckHoppingStep
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-16 18:56:52
 * @warning
 */
unsigned int CHopping::CalcHoppingStepByPeriod()
{
    unsigned int i, j, k;

    SHoppingDwell stHopping;

    int *piSampleData;
    int iFirstSampleDataY;

    m_uiHoppingLevel = 0;

    m_vecHopping.clear();

    // 단계적으로 스태게 레벨 찾기
    piSampleData = & m_piSampleData[m_uiStartSample];
    for( i=m_uiStartSample ; i < m_uiCoSample; ) {
        bool bRet;

        // 데이터 값 클리어
        memset( & stHopping, 0, sizeof( stHopping ) );

        // 한 주기 내에서 Dwell 들 찾기
        for( j = 0; j < ( unsigned int ) m_iPeriod && i < m_uiCoSample; ) {
            iFirstSampleDataY = *piSampleData;

            // Dwell 찾기
            k = 0;
            while( TCompMeanDiff<int>( iFirstSampleDataY, *piSampleData, (int) m_uiMargin ) ) {
                ++piSampleData;
                ++i;
                ++j;
                ++k;
                if( j >= (unsigned int) m_iPeriod || i >= m_uiCoSample ) {
                    break;
                }
            }

            if( k >= HOP_LEVEL_MIN_CNT ) {
                stHopping = iFirstSampleDataY;
            }

        }

        if( stHopping.IsValid() == true ) {
            bRet = false;
            TSortLevel<int>( ( int ) stHopping.uiCoSteps, stHopping.iSteps );

            for( auto &stElement : m_vecHopping ) {
                if( stHopping  == stElement ) {
                    ++ stElement.uiAccumulated;

                    bRet = true;
                    break;
                }
            }

            if( bRet == false ) {
                stHopping.uiAccumulated = _spOne;
                m_vecHopping.push_back( stHopping );
            }
        }

    }

    // 정렬하기
    sort( m_vecHopping.begin(), m_vecHopping.end(), compareHoppingSteps );

    if( m_vecHopping.size() > 0 && m_vecHopping[0].uiAccumulated > 2 ) {
        m_uiHoppingLevel = m_vecHopping[0].uiCoSteps;
    }

    return m_uiHoppingLevel;

}

/**
 * @brief     CalcHoppingStep
 * @param     unsigned int uiStep
 * @return    unsigned int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-18 14:34:29
 * @warning
 */
void CHopping::CalcHoppingStep()
{
    SHoppingDwell *pstSHoppingSteps;

    pstSHoppingSteps = & m_vecHopping[0];

    memcpy( & m_uiSteps, pstSHoppingSteps->iSteps, sizeof( m_uiSteps ) );

}

/**
 * @brief     AutoCorerelation
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2005-11-07 11:33:29
 * @warning
 */
void CHopping::AutoCorerelation()
{
    unsigned int i, j;

    float refAcf;
    float *pAcf;

    int *pxd1, *pxd2;

    memset( m_pAcf, 0, sizeof( float ) * m_uiMaxPdw );

    m_CoAcf = m_uiCoSample;
    pxd1 = & m_piDiffY[0];
    for( i = 0; i < m_uiCoSample-m_uiStartSample ; ++i, ++pxd1 ) {
        pxd2 = & m_piDiffY[i];

        // zero 값이 대부분이기 떄문에 이 조건을 추가함.
        if( pxd2 != NULL && *pxd1 != 0 ) {
            pAcf = & m_pAcf[0];
            for( j = i; j < m_uiCoSample- m_uiStartSample ; ++j ) {
                *pAcf += ( ( float ) *pxd1 * ( float ) *pxd2++ );
                ++ pAcf;
            }
        }
        else {

        }
    }

    refAcf = m_pAcf[0];
    pAcf = & m_pAcf[1];
    if( is_not_zero<float>( refAcf ) == true ) {
        for( i = 1; i < m_CoAcf; ++i ) {
            *pAcf++ /= refAcf;
        }
    }
    else {
        for( i = 1; i < m_CoAcf; ++i ) {
            *pAcf++ = 1 - FDIV( i, m_CoAcf );
        }
    }

    m_pAcf[0] = 1.0;

}

/**
 * @brief     CalcSamplingTimeForHopping
 * @param     STR_EMITTER * pEmitter
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-13 14:23:01
 * @warning
 */
void CHopping::CalcSamplingTime( STR_EMITTER *pEmitter )
{

    m_SamplingTime = ( UINT ) ( pEmitter->stPRI.tMin + pEmitter->stPRI.tMax ) / 2;
#ifdef _MSV_VER
    TRACE( "\n m_SamplingTime[%d]\n", m_SamplingTime );

#endif

    return;
}

/**
 * @brief     DifferentialY
 * @param     STR_EMITTER * pEmitter
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-14 09:19:37
 * @warning
 */
void CHopping::DifferentialY( STR_EMITTER *pEmitter )
{
    unsigned int i;
    int iDataY;
    int iDataYNow;

    int *piDiffY;
    int *piSampleData;

    piSampleData = & m_piSampleData[m_uiStartSample];
    piDiffY = & m_piDiffY[0];
    *piDiffY = 0;

    iDataY = *piSampleData;

    ++ piSampleData;
    ++ piDiffY;
    for( i = m_uiStartSample+1 ; i < m_uiCoSample ; ++i ) {

        iDataYNow = *piSampleData;
        if( TCompMeanDiff<int>( iDataY, iDataYNow, ( int ) m_uiMargin ) == true ) {
            *piDiffY = 0;
        }
        else {
            *piDiffY = iDataYNow - iDataY;

        }

        iDataY = iDataYNow;

        ++ piDiffY;
        ++ piSampleData;

    }

}

/**
 * @brief     SamplingDTOAProcess
 * @param     STR_EMITTER * pEmitter
 * @param     ENUM_SAMPLING_OPTION enSamplingOption
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-27 19:37:42
 * @warning
 */
void CHopping::SamplingDTOAProcess( STR_EMITTER *pEmitter, ENUM_SAMPLING_OPTION enSamplingOption )
{
    unsigned int i, j;

    UINT uiMiss;
    //UINT index = 0, uiMiss;

    UINT *puiDataY;

    STR_MINMAX_TOA *pstPRI;

    int *psy, iDTOA, iPrevValue;

    // 샘플링 데이터 초기화
    memset( m_piSampleData, 0, sizeof( int ) * m_uiMaxPdw );
    //memset( m_puiSampleDataY, 0, sizeof( int ) * m_uiMaxPdw );

    m_uiCoSample = 0;
    psy = m_piSampleData;
    puiDataY = m_puiDataY;
    iPrevValue = *puiDataY;
    pstPRI = & pEmitter->stPRI;

    m_uiStartSample = UINT_MAX;

    for( i = 0; i < m_uiCoData; ++i ) {
        /*! \debug  하모닉 고료해서 최소값은 0 부터 찾는 것으로 합니다.
        	\author 조철희 (churlhee.jo@lignex1.com)
        	\date 	2023-07-18 09:29:20
        */
        //if( TCompMarginDiff<_TOA>( (_TOA) *puiDataY, pstPRI->tMin, pstPRI->tMax, m_uiMargin ) == true ) {
        if( TCompMarginDiff<_TOA>( ( _TOA ) *puiDataY, 0, pstPRI->tMax, (_TOA) m_uiMargin ) == true ) {
            if( m_uiStartSample == UINT_MAX ) {
                m_uiStartSample = m_uiCoSample;
            }
            *psy = *puiDataY;
            iPrevValue = *psy++;
            ++ m_uiCoSample;
        }
        else {
            // uiMiss = CheckMissingPulse( *puiDataY, pstPRI, m_uiMargin ) + 1;
            uiMiss = UDIV( *puiDataY, ( unsigned int ) pstPRI->tMean );
            uiMiss = max( 2, uiMiss );

            iDTOA = (int) ( *puiDataY / uiMiss );
            for( j = 0; j < uiMiss; ++j ) {
                if( enSamplingOption == enAVERAGE ) {
                    *psy++ = iDTOA;
                }
                else if( enSamplingOption == enVALUE ) {
                    *psy++ = iPrevValue;
                }
                else {
                    *psy = *( psy - 1 );
                    psy++;
                }

                ++ m_uiCoSample;

                if( m_uiCoSample > m_uiMaxPdw ) {
                    break;
                }
            }
        }

        if( m_uiCoSample > m_uiMaxPdw ) {
            break;
        }

        ++ puiDataY;
    }

    //
    if( m_uiStartSample == UINT_MAX ) {
        m_uiStartSample = m_uiCoSample;
    }

}

/**
 * @brief     SamplingProcessForHopping
 * @param     STR_EMITTER * pEmitter
 * @param     ENUM_SAMPLING_OPTION enSamplingOption
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-13 16:10:15
 * @warning
 */
void CHopping::SamplingFREQProcess( STR_EMITTER *pEmitter, ENUM_SAMPLING_OPTION enSamplingOption )
{
    unsigned int i;
    UINT inpulse;
    int sumY, maxY;

    unsigned int uisx=0, uisy=0, uisyy=0;

    _TOA dShgh;

    UINT index=0;

    // 샘플링 데이터 초기화
    memset( m_pSampleToa, 0, sizeof( _TOA ) * m_uiMaxPdw );
    memset( m_piSampleData, 0, sizeof( int ) * m_uiMaxPdw );
    memset( m_puiSampleDataY, 0, sizeof( int ) * m_uiMaxPdw );

    m_uiCoSample = 0;
    m_uiStartSample = 0;

    _EQUALS3( sumY, maxY, 0 )

    inpulse = 0;
    dShgh = m_ptDataX[0] + m_SamplingTime;

    for( i = 0; i < m_uiCoData; ) {
        if( m_ptDataX[index] < dShgh ) {
            sumY += (int) m_puiDataY[index];                    // Sampling 구간내의 PA의 전체 합
            maxY = max( maxY, (int) m_puiDataY[index] );

            ++ inpulse;
            ++ index;

            ++i;
        }
        else {
            if( m_uiCoSample >= m_uiMaxPdw ) {
                break;
            }

            m_pSampleToa[uisx] = dShgh - m_SamplingTime;

            if( inpulse != 0 ) {
                // Sampling 구간내의 평균치로 계산
                if( enSamplingOption == enAVERAGE ) {
                    m_piSampleData[uisy] = ( int ) UDIV( sumY, inpulse );
                }
                // Sampling 구간내의 최대치로 계산
                else if( enSamplingOption == enMAXHOLD ) {
                    m_piSampleData[uisy] = maxY;
                }
                else {
                    m_piSampleData[uisy] = ( int ) m_puiDataY[index];
                }

            }
            else {
                m_piSampleData[uisy] = ( int ) m_puiDataY[index];
            }

            m_puiSampleDataY[uisyy] = m_puiDataY[index];

            dShgh += m_SamplingTime;

            ++ uisx;
            ++ uisy;
            ++ uisyy;

/*
            if( psx != NULL ) {
                *psx = dShgh - m_SamplingTime;
            }

            if( psy != NULL ) {
                if( inpulse != 0 ) {
                    // Sampling 구간내의 평균치로 계산
                    if( enSamplingOption == enAVERAGE ) {
                        *psy = ( int ) UDIV( sumY, inpulse );
                    }
                    // Sampling 구간내의 최대치로 계산
                    else if( enSamplingOption == enMAXHOLD ) {
                        *psy = maxY;
                    }
                    else {
                        *psy = (int) m_puiDataY[index];
                    }

                }
                else {
                    *psy = (int) m_puiDataY[index];
                }

                *psyy = m_puiDataY[index];
            }

            dShgh += m_SamplingTime;

            if( psx < m_pSampleToa + m_uiMaxPdw ) {
                ++ psx;
            }

            if( psy < m_piSampleData + m_uiMaxPdw ) {
                ++ psy;
            }

            if( psyy < m_puiSampleDataY + m_uiMaxPdw ) {
                ++ psyy;
            }
            */

            _EQUALS3( sumY, maxY, 0 )

            inpulse = 0;

            ++ m_uiCoSample;
        }
    }

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::FindPeriod
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-11-07 13:39:51
//
void CHopping::FindPeriod()
{
    unsigned int i, k;

    float *pAcf;
    float maxPeak;

    unsigned int minPeriod;

    minPeriod = 1;

    maxPeak = 1.0;			// debug, 00-07-27 15:53:42
    pAcf = & m_pAcf[minPeriod];

    if( m_CoAcf >= MIN_CO_ACF + minPeriod ) {
        k = 0;
        m_coCanPeak = 0;
        for( i = minPeriod; i < m_CoAcf - 2; ++i ) {
            if( m_coCanPeak < m_uiMaxPdw &&
                *pAcf >= MINIMUM_ACF_FOR_HOPPING &&
                *pAcf > 0 && ( *( pAcf - 1 ) <= *pAcf && *pAcf >= *( pAcf + 1 ) ) ) {
                /*! \bug  ACF 값은 일정 값보다 커야 한다. 최소값은 0.2로 정했다.
                    \date 2006-07-24 14:37:23, 조철희
                */
                // 이전에는 0.4 로 정했는데 반복 파형이 3개 미만일 때 이보다 작은값을 산출할 수 있다.
                /* 상한 값보다 큰 값을 기준으로 Peak 값을 찾는다.	*/

                if( *pAcf < maxPeak ) {				// debug, 00-09-01 12:10:39
                    k = i;										// toa index
                    maxPeak = *pAcf;

                    m_pCanPeak[m_coCanPeak] = (int) i;
                    ++ m_coCanPeak;
                }
            }

            ++ pAcf;
        }

        if( m_coCanPeak >= _spTwo && k != 0 ) {
            m_iPeriod = m_pCanPeak[0];
            m_fPeriod = FMUL( m_iPeriod, m_SamplingTime );
        }
        else {
            m_iPeriod = -1;
            m_fPeriod = 0;
        }
    }
}

/**
 * @brief     CalcHoppingStepByNonPeriod2
 * @return    unsigned int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-29 13:43:28
 * @warning
 */
// unsigned int CHopping::CalcHoppingStepByNonPeriod2( STR_EMITTER *pEmitter )
// {
//     unsigned int i, k;
//
//     SHoppingDwell stHopping;
//
//     //int *piSampleData;
//     unsigned int *puiDataY, uiFirstDataY;
//
//     m_uiHoppingLevel = 0;
//
//     // 데이터 값 클리어
//     memset( & stHopping, 0, sizeof( stHopping ) );
//
//     m_vecHopping.clear();
//
//     // 단계적으로 스태게 레벨 찾기
//     puiDataY = m_puiDataY;
//     for( i = 0; i < m_uiCoData; ) {
//
//         // 한 주기 내에서 Dwell 들 찾기
//         uiFirstDataY = ( unsigned int ) *puiDataY;
//
//         // Dwell 찾기
//         if( TCompMarginDiff<_TOA>( uiFirstDataY, pEmitter->stPRI.tMin, pEmitter->stPRI.tMax, m_uiMargin ) ) {
//             k = 0;
//             while( TCompMeanDiff<unsigned int>( uiFirstDataY, *puiDataY, m_uiMargin ) ) {
//                 ++puiDataY;
//                 ++i;
//                 ++k;
//                 if( i >= m_uiCoSample ) {
//                     break;
//                 }
//             }
//
//             if( k > HOP_LEVEL_MIN_CNT ) {
//                 stHopping.AddSteps( ( int ) uiFirstDataY );
//             }
//
//         }
//         else {
//             ++puiDataY;
//             ++i;
//         }
//
//     }
//
//     // 저장하기
//     m_vecHopping.push_back( stHopping );
//
//     m_uiHoppingLevel = stHopping.uiCoSteps;
//
//     return m_uiHoppingLevel;
//
// }

/**
 * @brief     CalcDwellStepByNonPeriod
 * @param     STR_EMITTER * pEmitter
 * @return    unsigned int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-07-03 20:34:27
 * @warning
 */
unsigned int CHopping::CalcHoppingDwellStepByNonPeriod( STR_EMITTER *pEmitter )
{
    bool bRet;
    unsigned int i, k;

    SHoppingDwell stHopping;

    //int *piSampleData;
    int *piSampleData, iFirstDataY;

    m_uiHoppingLevel = 0;

    // 데이터 값 클리어
    memset( & stHopping, 0, sizeof( stHopping ) );

    m_vecHopping.clear();

    // 단계적으로 스태게 레벨 찾기
    if( m_enHoppingDwell == enFREQ_HOPPING ) {
        piSampleData = m_piSampleData;
        for( i = 0; i < m_uiCoSample; ) {

            // 한 주기 내에서 Dwell 들 찾기
            iFirstDataY = *piSampleData;

            // Dwell 찾기
            bRet = TCompMarginDiff<int>( iFirstDataY, pEmitter->stFreq.iMin, pEmitter->stFreq.iMax, ( int ) m_uiMargin );

            if( bRet == true ) {
                k = 0;

                while( TCheckHarmonic<int>( iFirstDataY, *piSampleData, ( int ) m_uiMargin ) ) {
                    ++piSampleData;
                    ++i;
                    ++k;
                    if( i >= m_uiCoSample ) {
                        break;
                    }
                }

                if( k >= HOP_LEVEL_MIN_CNT_NONPRD ) {
                    stHopping.AddSteps( ( int ) iFirstDataY );
                }

            }
            else {
                ++piSampleData;
                ++i;
            }

        }

    }
    else {
        piSampleData = m_piSampleData;
        for( i = 0; i < m_uiCoSample; ) {

            // 한 주기 내에서 Dwell 들 찾기
            iFirstDataY = *piSampleData;

            // Dwell 찾기
            bRet = TCompMarginDiff<_TOA>( ( _TOA ) iFirstDataY, pEmitter->stPRI.tMin, pEmitter->stPRI.tMax, ( _TOA ) m_uiMargin );
            if( bRet == true ) {
                k = 0;

                while( TCheckHarmonic<int>( iFirstDataY, *piSampleData, ( int ) m_uiMargin ) ) {
                    ++piSampleData;
                    ++i;
                    ++k;
                    if( i >= m_uiCoSample ) {
                        break;
                    }
                }

                if( k >= HOP_LEVEL_MIN_CNT_NONPRD ) {
                    stHopping.AddSteps( ( int ) iFirstDataY );
                }

            }
            else {
                ++piSampleData;
                ++i;
            }

        }

    }


    // 반복 구간 찾아서 제거하기
    RemoveRepeatableDwell( & stHopping );

    // 저장하기
    m_vecHopping.push_back( stHopping );

    m_uiHoppingLevel = stHopping.uiCoSteps;

    return m_uiHoppingLevel;

}

/**
 * @brief     RemoveRepeatableDwell
 * @param     SHoppingSteps * pstHopping
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-07-03 20:56:10
 * @warning
 */
void CHopping::RemoveRepeatableDwell( SHoppingDwell *pstHopping )
{
    unsigned int ui;

    if( pstHopping->uiCoSteps > 1 ) {
        for( ui = 2; ui < MAX_STAGGER_LEVEL_POSITION; ++ui ) {
            if( IsRepeatable( pstHopping, 0, ui ) == true ) {
                pstHopping->uiCoSteps = ui;
                break;
            }

        }
    }
    else {

    }

    // 32단이 넘을 경우 찾은 드웰 값을 0 으로 초기화 합니다.
    if( pstHopping->uiCoSteps > MAX_STAGGER_LEVEL_POSITION ) {
        pstHopping->uiCoSteps = 0;
    }

}

/**
 * @brief     IsRepeatable
 * @param     SHoppingSteps * pstHopping
 * @param     unsigned int uiSteps
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-07-03 21:03:43
 * @warning
 */
bool CHopping::IsRepeatable( SHoppingDwell *pstHopping, unsigned int uiStart, unsigned int uiSteps )
{
    bool bRet=true;
    unsigned int ui, uj;
    unsigned int uIndex;

    int *piSteps;

    int iMatch = 0;

    piSteps = pstHopping->iSteps;

    //TRACE( "\n 시작 위치 : %d, 스텝[%d] 체크" , uiStart, uiSteps );
    if( pstHopping->uiCoSteps > 1 ) {
        for( ui = uiStart ; ui < pstHopping->uiCoSteps; ui += uiSteps ) {
            for( uj = ui ; uj < ui+uiSteps && uj+uiSteps < pstHopping->uiCoSteps ; ++uj ) {
                uIndex = uj; // %uiSteps;
                //TRACE( "\n (%d, %d)", uIndex, uj+uiSteps );

                //if( TCompMeanDiff<int>( piSteps[uIndex], piSteps[uj + uiSteps], ( int ) m_uiStableMargin ) == false ) {
                if( TCheckHarmonic<int>( piSteps[uIndex], piSteps[uj + uiSteps], (int) m_uiStableMargin ) == false ) {
                    bRet = false;
                    break;
                }
                else {
                    ++ iMatch;
                }
            }
            if( bRet == false ) {
                break;
            }
            //TRACE( "\n" );
        }
    }
    else {
        bRet = false;
    }

    return bRet;
}

/**
 * @brief     주파수 호핑 레벨을 계산한다.
 * @param     STR_EMITTER * pEmitter
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2008-10-30 16:05:13
 * @warning
 */
// void CHopping::CalcHoppingStepByNonPeriod()
// {
//     unsigned int i, j;
//
//     bool bMatch;
//
//     PDWINDEX pPdwIndex;
//     unsigned int *puiSteps;
//
//     m_uiHoppingLevel = 0;
//
//     memset( m_uiSteps, 0, sizeof( m_uiSteps ) );
//
//     pPdwIndex = 0;
//     for( i = 0; i < m_uiCoData; ++i ) {
//         unsigned int uiValue;
//
//         uiValue = m_puiDataY[pPdwIndex++];
//
//         bMatch = false;
//         puiSteps = & m_uiSteps[0];
//         for( j = 0; j < m_uiHoppingLevel; ++j ) {
//             if( true == TCompMeanDiff<UINT>( uiValue, *puiSteps++, m_uiMargin ) ) {
//             //if( 0 != TCheckHarmonic<UINT>( uiValue, *puiSteps++, m_uiMargin ) ) {
//                 bMatch = true;
//                 break;
//             }
//         }
//         if( bMatch == false ) {
//             m_uiSteps[m_uiHoppingLevel] = uiValue;
//             ++ m_uiHoppingLevel;
//             if( ( UINT ) m_uiHoppingLevel > MAX_FREQ_PRI_STEP ) {
//                 Log( enError, "호핑 레벨 값[%d]이 기본 레벨 크기[%d]를 초과했습니다." , m_uiHoppingLevel, MAX_FREQ_PRI_STEP );
//                 m_uiHoppingLevel = 0;
//             }
//         }
//     }
//
// }

/**
 * @brief     DifferentialFreq
 * @param     STR_EMITTER * pEmitter
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-09 19:41:33
 * @warning
 */
 // void CAnalPRI::DifferentialFreq( STR_EMITTER *pEmitter )
 // {
 //     int iDiff;
 //     unsigned int i, uiCoData, uiFreq, uiFreqNow;
 //
 //     PDWINDEX *pPdwIndex;
 //
 //     _TOA *pSampleToa;
 //     int *pSampleData;
 //
 //     pPdwIndex = pEmitter->stPDW.pIndex;
 //     uiCoData = pEmitter->stPDW.uiCount;
 //
 //     pSampleToa = & m_pSampleToa[0];
 //     pSampleData = & m_pSampleData[0];
 //     uiFreq = m_pFREQ[*pPdwIndex];
 //     ++ pPdwIndex;
 //     for( i = 1 ; i < uiCoData; ++i ) {
 //         *pSampleToa++ = m_pTOA[*pPdwIndex];
 //
 //         uiFreqNow = m_pFREQ[*pPdwIndex];
 //         iDiff = (int) uiFreq - (int) uiFreqNow;
 //
 //         if( CompMeanDiff<unsigned int>( uiFreq, uiFreqNow, 10 ) == true ) {
 //             *pSampleData++ = 0;
 //         }
 //         else {
 //             *pSampleData++ = iDiff;
 //         }
 //
 //
 //         uiFreq = uiFreqNow;
 //
 //         ++ pPdwIndex;
 //     }
 //
 //     m_CoSample = uiCoData - 1;
 //
 // }
