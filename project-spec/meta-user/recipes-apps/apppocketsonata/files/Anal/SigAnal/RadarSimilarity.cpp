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
            if( pLOBData->uiRadarIndex == 0 ) {
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
            }
            else {
                bRet = true;
            }

            break;

        case ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN:
            if( pLOBData->vFreqType == ENUM_AET_FRQ_TYPE::E_AET_FRQ_AGILE ) {
                fOverlapValue = FDIV( m_pSEnvironVariable->fMarginMinRqdFrqRangeNestedRatio * ( pABTData->fFreqMax - pABTData->fFreqMin ), 100.0 );
                bRet = TIsOverlapSpace<float>( pLOBData->fFreqMin, pLOBData->fFreqMax, pABTData->fFreqMin, pABTData->fFreqMax, fOverlapValue );
            }
            else if( pLOBData->vFreqType == ENUM_AET_FRQ_TYPE::E_AET_FRQ_PATTERN ) {
                if( pABTData->vFreqPatternType == pLOBData->vFreqPatternType || pLOBData->vFreqPatternType == ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_UNKNOWN ) {
                    fOverlapValue = FDIV( m_pSEnvironVariable->fMarginFrqModPeriodErrorRatio * ( pABTData->fFreqPatternPeriodMean ), 100.0 );
                    if( TCompMarginDiff<float>( pLOBData->fFreqPatternPeriod, pABTData->fFreqPatternPeriodMin, pABTData->fFreqPatternPeriodMax, fOverlapValue ) == TRUE ) {
                        fOverlapValue = FDIV( m_pSEnvironVariable->fMarginMinRqdFrqRangeNestedRatio * ( pABTData->fFreqMax - pABTData->fFreqMin ), 100.0 );
                        bRet = TIsOverlapSpace<float>( pLOBData->fFreqMin, pLOBData->fFreqMax, pABTData->fFreqMin, pABTData->fFreqMax, fOverlapValue );
                    }
                    else {
                        TRACE( "\n 주파수 패턴 주기 비교 병합 실패 !" );
                    }
                }
                else {
                    TRACE( "\n 주파수 패턴 형태 비교 실패 !" );
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
            bRet = TCompMeanDiff<float>( pABTData->fPRIMean, pLOBData->fPRIMean, m_fStableMargin );
            break;

        case ENUM_AET_PRI_TYPE::E_AET_PRI_JITTER:
            fOverlapValue = FDIV( m_pSEnvironVariable->fMarginMinRqdPriRangeNestedRatio * ( pABTData->fPRIMax - pABTData->fPRIMin ), 100.0 );
            bRet = TIsOverlapSpace<float>( pLOBData->fPRIMin, pLOBData->fPRIMax, pABTData->fPRIMin, pABTData->fPRIMax, fOverlapValue );
            if( bRet == false ) {
#ifdef _MSC_VER
                //bRet = TIsOverlapSpace<float>( pLOBData->fPRIMin, pLOBData->fPRIMax, pABTData->fPRIMin, pABTData->fPRIMax, fOverlapValue );
                //WhereIs;
#endif

            }
            break;

        case ENUM_AET_PRI_TYPE::E_AET_PRI_DWELL_SWITCH:
            if( pABTData->vPRIPositionCount > 1 && pLOBData->vPRIPositionCount > 1 ) {
                if( pABTData->vPRIPositionCount != pLOBData->vPRIPositionCount ) {
                    TRACE( "\n Dwell 차수가 다릅니다 [%d, %d] !!", pABTData->vPRIPositionCount, pLOBData->vPRIPositionCount );

                }
#ifdef __VXWORKS__
                float fLOBPRISeq[MAX_FREQ_PRI_STEP], fABTPRISeq[MAX_FREQ_PRI_STEP];
                memcpy( fLOBPRISeq, pLOBData->fPRISeq, sizeof( float ) * pLOBData->vPRIPositionCount );
                memcpy( fABTPRISeq, pABTData->fPRISeq, sizeof( float ) * pABTData->vPRIPositionCount );
                bRet = TCompSwitch2Level<float>( fLOBPRISeq, fABTPRISeq, pLOBData->vPRIPositionCount, pABTData->vPRIPositionCount, m_fStableMargin );
#else
                bRet = TCompSwitch2Level<float>( pLOBData->fPRISeq, pABTData->fPRISeq, pLOBData->vPRIPositionCount, pABTData->vPRIPositionCount, m_fStableMargin );
#endif

            }
            else {
                TRACE( "\n 에러.. Dwell/Stable 비교[%d/%d]", pABTData->vPRIPositionCount, pLOBData->vPRIPositionCount );
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
                if( pABTData->vPRIPatternType == pLOBData->vPRIPatternType || pLOBData->vPRIPatternType == ENUM_AET_FREQ_PRI_PATTERN_TYPE::E_AET_FREQ_PRI_UNKNOWN ) {
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
