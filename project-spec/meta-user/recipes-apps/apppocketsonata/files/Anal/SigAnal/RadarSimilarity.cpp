/**

    @file      CRadarSimilarity.cpp
    @brief
    @details   ~
    @author    조철희
    @date      22.10.2023
    @copyright © LIGNex1, 2023. All right reserved.

**/

#include "stdafx.h"

#include "RadarSimilarity.h"
#include "../Identify/ELUtil.h"


/**
 * @brief     CRadarSimilarity
 * @param     float fFixedFreqMargin
 * @param     float m_fStableMargin
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-10-22 15:18:58
 * @warning
 */
CRadarSimilarity::CRadarSimilarity( SEnvironVariable *pSEnvironVariable, float fFixedFreqMargin, float fStableMargin )
{

    m_pSEnvironVariable = pSEnvironVariable;

    m_fFixedFreqMargin = fFixedFreqMargin;
    m_fStableMargin = fStableMargin;

#if 0
    float fLOBPRISeq[MAX_FREQ_PRI_STEP], fABTPRISeq[MAX_FREQ_PRI_STEP];

    fLOBPRISeq[0] = (float) 1322.;
    fLOBPRISeq[1] = ( float ) 1389.;

    fABTPRISeq[0] = ( float ) 1192;
    fABTPRISeq[1] = ( float ) 1389.;
    fABTPRISeq[2] = ( float ) 1322;

    TCompSwitch2Level<float>( fLOBPRISeq, fABTPRISeq, 2, 3, m_fStableMargin );

#endif


#ifdef __VECTORCAST__

    SRxABTData stABTData;
    SRxLOBData stLOBData;

    ///////////////////////////////////////////////////////////////////////////////////
    stABTData.enMOPType = E_MAX_MOP;
    stLOBData.enMOPType = E_MAX_MOP;
    CompMOPTypeMargin( & stABTData, & stLOBData );

    ///////////////////////////////////////////////////////////////////////////////////
    stABTData.vFreqType = ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED;
    stLOBData.vFreqType = ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    CompFreqMargin( & stABTData, & stLOBData );

    stABTData.vFreqType = ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED;
    stLOBData.vFreqType = ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    stLOBData.uiRadarIndex = 0;
    stLOBData.vFreqPositionCount = 1;
    stLOBData.fFreqSeq[0] = 1;
    stABTData.fFreqMean = 1;
    CompFreqMargin( & stABTData, & stLOBData );

    stABTData.vFreqType = ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    stLOBData.vFreqType = ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    stABTData.vFreqPatternType = ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_SLIDE_DEC;
    stLOBData.vFreqPatternType = ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_SLIDE_INC;
    CompFreqMargin( & stABTData, & stLOBData );

    stABTData.vFreqPatternType = ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_SLIDE_DEC;
    stLOBData.vFreqPatternType = ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_SLIDE_DEC;
    stABTData.fFreqPatternPeriodMean = (float) 10.;
    stLOBData.fFreqPatternPeriod = (float) 10.;
    stABTData.fFreqPatternPeriodMin = ( float ) 1000.;
    stABTData.fFreqPatternPeriodMax = ( float ) 2000.;
    CompFreqMargin( & stABTData, & stLOBData );

    stABTData.vFreqType = ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN;
    stLOBData.vFreqType = ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE;
    CompFreqMargin( & stABTData, & stLOBData );

    stABTData.vFreqType = ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING;
    stLOBData.uiRadarIndex = 1;
    CompFreqMargin( & stABTData, & stLOBData );

    stABTData.vFreqType = ENUM_AET_FRQ_TYPE::E_AET_MAX_FRQ_TYPE;
    CompFreqMargin( & stABTData, & stLOBData );

    ///////////////////////////////////////////////////////////////////////////////////
    stABTData.vPRIType = ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;
    stLOBData.vPRIType = ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;
    stLOBData.vPRIPatternType = ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_UNKNOWN;
    stABTData.vPRIPatternType = ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_UNKNOWN;
    stLOBData.fPRIPatternPeriod = ( float ) 10.;
    stABTData.fPRIPatternPeriodMin = ( float ) 1000.;
    stABTData.fPRIPatternPeriodMax = ( float ) 1000.;
    CompPRIMargin( & stABTData, & stLOBData );

    stLOBData.vPRIPatternType = ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_SINE;
    stABTData.vPRIPatternType = ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_UNKNOWN;
    CompPRIMargin( & stABTData, & stLOBData );

    stABTData.vPRIType = ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN;
    stLOBData.vPRIType = ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER;
    CompPRIMargin( & stABTData, & stLOBData );

    stABTData.vPRIType = ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH;
    stLOBData.vPRIType = ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED;
    CompPRIMargin( & stABTData, & stLOBData );

    stABTData.vPRIType = ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;
    stLOBData.vPRIType = ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER;
    stABTData.vPRIPositionCount = 1;
    stLOBData.vPRIPositionCount = 1;
    stABTData.fPRISeq[0] = (float) 1000.;
    stLOBData.fPRISeq[0] = ( float ) 2000.;
    CompPRIMargin( & stABTData, & stLOBData );

    stABTData.vPRIType = ENUM_AET_PRI_TYPE::E_AET_MAX_PRI_TYPE;
    CompPRIMargin( & stABTData, & stLOBData );

#endif

}

/**
 * @brief     ~CRadarSimilarity
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-10-22 15:18:54
 * @warning
 */
CRadarSimilarity::~CRadarSimilarity()
{


}

/**
 * @brief     CompMOPMargin
 * @param     SRxABTData * pABTData
 * @param     SRxLOBData * pLOBData
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-10-23 20:02:42
 * @warning
 */
bool CRadarSimilarity::CompSigTypeMargin( SRxABTData *pABTData, SRxLOBData *pLOBData )
{
    bool bRet = false;

    if( pABTData->vSignalType == pLOBData->vSignalType && pABTData->enMOPType == pLOBData->enMOPType ) {
        bRet = true;
    }

    return bRet;
}

/**
 * @brief     CompMOPTypeMargin
 * @param     SRxABTData * pABTData
 * @param     SRxLOBData * pLOBData
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-12-13 15:27:11
 * @warning
 */
bool CRadarSimilarity::CompMOPTypeMargin( SRxABTData *pABTData, SRxLOBData *pLOBData )
{
    bool bRet = false;

    switch( pABTData->enMOPType ) {
        case E_MOP_UNKNOWN:
            if( pLOBData->enMOPType == E_MOP_UNKNOWN ) {
                bRet = true;
            }
            break;

        case E_MOP_FMOP:
            if( pLOBData->enMOPType == E_MOP_FMOP ) {
                bRet = true;
            }
            break;

        case E_MOP_PMOP :
            if( pLOBData->enMOPType == E_MOP_PMOP ) {
                bRet = true;
            }
            break;

        default:
            break;
    }

    return bRet;
}

/**
 * @brief     CompFreqMargin
 * @param     SRxABTData * pABTData
 * @param     SRxLOBData * pLOBData
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-10-22 14:03:57
 * @warning
 */
bool CRadarSimilarity::CompFreqMargin( SRxABTData *pABTData, SRxLOBData *pLOBData )
{
    int i;
    bool bRet = false;

    float fOverlapValue;

    switch( pABTData->vFreqType ) {
        case ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED:
            if( pLOBData->vFreqType == ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED ) {
                bRet = TCompMeanDiff<float>( pABTData->fFreqMean, pLOBData->fFreqMean, m_fFixedFreqMargin );

            }
            else if( pLOBData->vFreqType == ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING ) {
                for( i = 0; i < pLOBData->vFreqPositionCount; ++i ) {
                    bRet = TCompMeanDiff<float>( pLOBData->fFreqSeq[i], pABTData->fFreqMean, m_fFixedFreqMargin );
                    if( bRet == true ) {
                        break;
                    }
                }

            }
            else {
            }

            break;

        case ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN:
            if( pLOBData->vFreqType == ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE ) {
                fOverlapValue = FDIV( m_pSEnvironVariable->fMarginMinRqdFrqRangeNestedRatio * ( pABTData->fFreqMax - pABTData->fFreqMin ), 100.0 );
                bRet = TIsOverlapSpace<float>( pLOBData->fFreqMin, pLOBData->fFreqMax, pABTData->fFreqMin, pABTData->fFreqMax, fOverlapValue );
            }
            else if( pLOBData->vFreqType == ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN ) {
                //! #추후 : 사인형 또는 삼각파의 패턴 형태를 오분석 가능성이 높기 때문에, SINE 형 또는 SAW 인 경우는 동일형으로 봄
                if( pABTData->vFreqPatternType == pLOBData->vFreqPatternType || pLOBData->vFreqPatternType == ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_UNKNOWN ||
                    ( ( pABTData->vFreqPatternType == ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_SINE && pLOBData->vFreqPatternType == ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_SAW_TRI ) ||
                      ( pABTData->vFreqPatternType == ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_SAW_TRI && pLOBData->vFreqPatternType == ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_SINE ) ) ) {
                    fOverlapValue = FDIV( m_pSEnvironVariable->fMarginFrqModPeriodErrorRatio * ( pABTData->fFreqPatternPeriodMean ), 100.0 );
                    if( TCompMarginDiff<float>( pLOBData->fFreqPatternPeriod, pABTData->fFreqPatternPeriodMin, pABTData->fFreqPatternPeriodMax, fOverlapValue ) == TRUE ) {
                        fOverlapValue = FDIV( m_pSEnvironVariable->fMarginMinRqdFrqRangeNestedRatio * ( pABTData->fFreqMax - pABTData->fFreqMin ), 100.0 );
                        bRet = TIsOverlapSpace<float>( pLOBData->fFreqMin, pLOBData->fFreqMax, pABTData->fFreqMin, pABTData->fFreqMax, fOverlapValue );
                    }
                    else {
#ifdef _MSC_VER
                        TRACE( "\n 주파수 패턴 주기 비교 병합 실패 !" );
#endif
                    }
                }
                else {
#ifdef _MSC_VER
                    TRACE( "\n 주파수 패턴 형태 비교 실패 !" );
#endif
                }

            }
            else {
            }
            break;

        case ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE:
            // 주파수 범위 체크
            fOverlapValue = FDIV( m_pSEnvironVariable->fMarginMinRqdFrqRangeNestedRatio * ( pABTData->fFreqMax - pABTData->fFreqMin ), 100.0 );
            bRet = TIsOverlapSpace<float>( pLOBData->fFreqMin, pLOBData->fFreqMax, pABTData->fFreqMin, pABTData->fFreqMax, fOverlapValue );
            break;

        case ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING:
            if( pLOBData->uiRadarIndex == 0 ) {
                if( pLOBData->vFreqType == ENUM_AET_FRQ_TYPE::E_AET_FRQ_FIXED ) {
                    for( i = 0; i < pABTData->vFreqPositionCount; ++i ) {

                        bRet = TCompMeanDiff<float>( pLOBData->fFreqMean, pABTData->fFreqSeq[i], m_fFixedFreqMargin );
                        if( bRet == true ) {
                            break;
                        }
                    }
                }
                else if( pLOBData->vFreqType == ENUM_AET_FRQ_TYPE::E_AET_FRQ_HOPPING ) {
                    /*! \debug  호핑 레벨값 보다는 범위로 비교하여 추적 성공 여부를 결정함.
                        \author 조철희 (churlhee.jo@lignex1.com)
                        \date 	2023-12-07 18:25:46
                    */
                    fOverlapValue = FDIV( m_pSEnvironVariable->fMarginMinRqdFrqRangeNestedRatio * ( pABTData->fFreqMax - pABTData->fFreqMin ), 100.0 );
                    bRet = TIsOverlapSpace<float>( pLOBData->fFreqMin, pLOBData->fFreqMax, pABTData->fFreqMin, pABTData->fFreqMax, fOverlapValue );

#ifdef __VXWORKS__
                    float fLOBFRQSeq[MAX_FREQ_PRI_STEP], fABTFRQSeq[MAX_FREQ_PRI_STEP];
                    memcpy( fLOBFRQSeq, pLOBData->fFreqSeq, sizeof( float ) * pLOBData->vFreqPositionCount );
                    memcpy( fABTFRQSeq, pABTData->fFreqSeq, sizeof( float ) * pABTData->vFreqPositionCount );
                    bRet = TCompSwitch2Level<float>( fLOBFRQSeq, fABTFRQSeq, pLOBData->vFreqPositionCount, pABTData->vFreqPositionCount, m_fStableMargin );

#else
                    // #추후 : 위쪽의 범위가 아니라, 레벨값으로 단을 확인해야 함.
                    if( bRet == false ) {
                        bRet = TCompSwitch2Level<float>( pLOBData->fFreqSeq, pABTData->fFreqSeq, pLOBData->vFreqPositionCount, pABTData->vFreqPositionCount, m_fStableMargin );
                    }

#endif


//                     for( i = 0; i < pABTData->vFreqPositionCount; ++i ) {
//                         float fFreqMean;
//
//                         bRet = false;
//                         fFreqMean = pABTData->fFreqSeq[i];
//                         for( j = 0; j < pLOBData->vFreqPositionCount; ++j ) {
//                             bRet = TCompMeanDiff<float>( pLOBData->fFreqSeq[j], fFreqMean, m_fFixedFreqMargin );
//                             if( bRet == true ) {
//                                 break;
//                             }
//                         }
//                         if( bRet == false ) {
//                             break;
//                         }
//                     }
                }
                else {
                }

            }
            else {
                bRet = true;
            }
            break;

        default:
            break;
    }

    return bRet;


}

/**
 * @brief     CompPRIMargin
 * @param     SRxABTData * pABTData
 * @param     SRxLOBData * pLOBData
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-10-22 15:34:03
 * @warning
 */
bool CRadarSimilarity::CompPRIMargin( SRxABTData *pABTData, SRxLOBData *pLOBData )
{
    int i;
    bool bRet = false;

    float fOverlapValue;

    switch( pABTData->vPRIType ) {
        case ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED:
            if( pLOBData->vPRIType == ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED ) {
                bRet = TCompMeanDiff<float>( pABTData->fPRIMean, pLOBData->fPRIMean, m_fStableMargin );
            }
            break;

        case ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER:
            if( pLOBData->vPRIType == ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER || pLOBData->vPRIType == ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER || \
                pLOBData->vPRIType == ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN ) {
                fOverlapValue = FDIV( m_pSEnvironVariable->fMarginMinRqdPriRangeNestedRatio * ( pABTData->fPRIMax - pABTData->fPRIMin ), 100.0 );
                bRet = TIsOverlapSpace<float>( pLOBData->fPRIMin, pLOBData->fPRIMax, pABTData->fPRIMin, pABTData->fPRIMax, fOverlapValue );
                if( bRet == false ) {
#ifdef _MSC_VER
                //bRet = TIsOverlapSpace<float>( pLOBData->fPRIMin, pLOBData->fPRIMax, pABTData->fPRIMin, pABTData->fPRIMax, fOverlapValue );
                //WhereIs;
#endif
                }
            }
            break;

        case ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH:
            if( pLOBData->vPRIType == ENUM_AET_PRI_TYPE::E_AET_PRI_FIXED ) {
#ifdef __VXWORKS__
                float fLOBPRISeq[MAX_FREQ_PRI_STEP], fABTPRISeq[MAX_FREQ_PRI_STEP];
                fLOBPRISeq[0] = pLOBData->fPRIMean;
                memcpy( fABTPRISeq, pABTData->fPRISeq, sizeof( float ) * pABTData->vPRIPositionCount );
                bRet = TCompSwitch2Level<float>( fLOBPRISeq, fABTPRISeq, 1, pABTData->vPRIPositionCount, m_fStableMargin );

#else
                bRet = TCompSwitch2Level<float>( & pLOBData->fPRIMean, pABTData->fPRISeq, 1, pABTData->vPRIPositionCount, m_fStableMargin );

#endif
            }
            else {
                if( pLOBData->vPRIPositionCount > 1 ) {

#ifdef __VXWORKS__
                    float fLOBPRISeq[MAX_FREQ_PRI_STEP], fABTPRISeq[MAX_FREQ_PRI_STEP];
                    memcpy( fLOBPRISeq, pLOBData->fPRISeq, sizeof( float ) * pLOBData->vPRIPositionCount );
                    memcpy( fABTPRISeq, pABTData->fPRISeq, sizeof( float ) * pABTData->vPRIPositionCount );
                    bRet = TCompSwitch2Level<float>( fLOBPRISeq, fABTPRISeq, pLOBData->vPRIPositionCount, pABTData->vPRIPositionCount, m_fStableMargin );
#else
                    bRet = TCompSwitch2Level<float>( pLOBData->fPRISeq, pABTData->fPRISeq, pLOBData->vPRIPositionCount, pABTData->vPRIPositionCount, m_fStableMargin );
#endif
                }

            }

            break;

        case ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER:
            if( pLOBData->vPRIType == ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER ) {
                fOverlapValue = FDIV( m_pSEnvironVariable->fMarginMinRqdPriRangeNestedRatio * ( pABTData->fPRIMax - pABTData->fPRIMin ), 100.0 );
                bRet = TIsOverlapSpace<float>( pLOBData->fPRIMin, pLOBData->fPRIMax, pABTData->fPRIMin, pABTData->fPRIMax, fOverlapValue );
            }
            else if( pLOBData->vPRIType == ENUM_AET_PRI_TYPE::E_AET_PRI_STAGGER ) {
                if( pABTData->vPRIPositionCount == pLOBData->vPRIPositionCount ) {
#ifdef __VXWORKS__
                    float fLOBPRISeq[MAX_FREQ_PRI_STEP], fABTPRISeq[MAX_FREQ_PRI_STEP];

                    memcpy( fLOBPRISeq, pLOBData->fPRISeq, sizeof( float ) * pLOBData->vPRIPositionCount );
                    memcpy( fABTPRISeq, pABTData->fPRISeq, sizeof( float ) * pABTData->vPRIPositionCount );
                    for( i = 0; i < pABTData->vPRIPositionCount; ++i ) {
                        bRet = TCompMeanDiff<float>( fABTPRISeq[i], fLOBPRISeq[i], m_fStableMargin );
                        if( bRet == false ) {
                            break;
                        }
                    }
#else
                    for( i = 0; i < pABTData->vPRIPositionCount; ++i ) {
                        bRet = TCompMeanDiff<float>( pABTData->fPRISeq[i], pLOBData->fPRISeq[i], m_fStableMargin );
                        if( bRet == false ) {
                            break;
                        }
                    }
#endif
                }
            }
            else {
            }
            break;

        case ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN:
            if( pLOBData->vPRIType == ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER ) {
                fOverlapValue = FDIV( m_pSEnvironVariable->fMarginMinRqdPriRangeNestedRatio * ( pABTData->fPRIMax - pABTData->fPRIMin ), 100.0 );
                bRet = TIsOverlapSpace<float>( pLOBData->fPRIMin, pLOBData->fPRIMax, pABTData->fPRIMin, pABTData->fPRIMax, fOverlapValue );
            }
            else if( pLOBData->vPRIType == ENUM_AET_PRI_TYPE::E_AET_PRI_PATTERN ) {
                if( pABTData->vPRIPatternType == pLOBData->vPRIPatternType || pLOBData->vPRIPatternType == ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_UNKNOWN || \
                    ( ( pABTData->vPRIPatternType == ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_SINE && pLOBData->vPRIPatternType == ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_SAW_TRI ) || \
                      ( pABTData->vPRIPatternType == ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_SAW_TRI && pLOBData->vPRIPatternType == ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_SINE ) ) ) {
                    fOverlapValue = FDIV( m_pSEnvironVariable->fMarginPriModPeriodErrorRatio * pABTData->fPRIPatternPeriodMean, 100.0 );
                    if( TCompMarginDiff<float>( pLOBData->fPRIPatternPeriod, pABTData->fPRIPatternPeriodMin, pABTData->fPRIPatternPeriodMax, fOverlapValue ) == TRUE ) {
                        fOverlapValue = FDIV( m_pSEnvironVariable->fMarginMinRqdPriRangeNestedRatio * ( pABTData->fPRIMax - pABTData->fPRIMin ), 100.0 );
                        bRet = TIsOverlapSpace<float>( pLOBData->fPRIMin, pLOBData->fPRIMax, pABTData->fPRIMin, pABTData->fPRIMax, fOverlapValue );
                    }
                    else {
                        TRACE( "\n PRI 패턴 주기 비교 병합 실패 !" );
                    }
                }
                else {
                    TRACE( "\n PRI 패턴 형태 비교 실패 !" );
                }
            }
            else {
            }
            break;

        default:
            break;

    }

    return bRet;

}
