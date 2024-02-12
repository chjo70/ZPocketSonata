// NPulExt.cpp: implementation of the NPulExt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"


#include "../OFP_Main.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "NewSigAnal.h"
#include "NPulExt.h"
#include "NewSigAnal.h"

#include "../../Include/globals.h"

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
CNPulExt::CNPulExt( void *pParent, unsigned int uiCoMaxPdw, const char *pThreadName ) : CPulExt(uiCoMaxPdw, pThreadName )
{
    SetAnalType( enDET_ANAL );

    m_pNewSigAnal = ( CNewSigAnal * ) pParent;

    //m_CoPulseTrains = 0;

    INIT_ANAL_VAR_( m_pNewSigAnal )

#ifdef __VECTORCAST__
    //! #동적 시험으로 함수를 타기위해서 그냥 호출
    CheckHarmonic( 0, 0, 0 );
    MarkToPDWIndex( NULL, 0, enUnMark );

#endif

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
    m_uiCoFrqAoaPwIdx =  m_pNewSigAnal->GetCoFrqAoaPwIdx();
    //m_CoPulseTrains = 0;

    //m_enBandWidth = m_pNewSigAnal->GetBandWidth();

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
void CNPulExt::PulseExtract( vector<SRadarMode *> *pVecMatchRadarMode )
{
    struct timespec nowTime;

    CCommonUtils::GetCollectTime( &nowTime );
    PrintFunction

    /*! \todo	하나의 그룹화에서는 펄스열 인덱스를 최기화해서 펄스열 자원을 활용할수 있게 한다.*/
    Init();

    // CED 라이브러리 기반 펄스열 추출
    ExtractPulseTrainByLibrary( pVecMatchRadarMode );

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

    m_nRefSeg = m_uiCoSeg;

    // 모든 펄스열을 초기화한 상태에서 불규칙성 펄스열을 추출하도록 한다.
    memset( MARK, 0, sizeof( MARK ) );

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
    CleanPulseTrains( nRefSeg, m_uiCoSeg );

    // 규칙성 펄스열을 찾은 펄스열 인덱스
    m_uiRefEndSeg = m_uiCoSeg;

    CPulExt::ClearAllMark( true );

    //////////////////////////////////////////////////////////////////////////
    // 불규칙성 펄스열 찾기
    //
    // 펄스열 구간마다 불규칙성 펄스열과 불규칙성 펄스열을 같이 추출한다.
    // 펄스열은 각 단계마다 규칙성 펄스열과 불규칙성 펄스열을 동시에 수행한다.
    //-- 조철희 2005-12-09 16:11:27 --//

    int nExtSeg = m_uiCoSeg;

    for( i=0 ; i < MAX_PRI_RANGE ; ++i ) {
        PulseExtract( i );
    }

    /*! \bug  기본 규칙성 펄스열에서 추출한 펄스열과 펄스열 추출후의 펄스열 끼리
                        비교해서 유사 펄스열이면, 기본 규칙성 펄스열을 제거한다.
            \date 2006-05-19 17:59:24, 조철희
    */
    DropPulseTrain( nRefSeg, nExtSeg );

#elif defined( _EXTRACT_PULSE_METHOD5_ )

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

    ClearAllMark();

    // 불규칙성 펄스열을 찾은 펄스열 인덱스 저장
    SetRefEndSeg();

    // 불규칙성 펄스열의 기준 PRI 값을 찾는다. 모든 전 구간에서 찾는다.
    FindRefJitter();

    // 기준 PRI 로 펄스열 추출
    ExtractRefJitter();

    ClearAllMark();

    //////////////////////////////////////////////////////////////////////////
    // 불규칙성 펄스열 찾기
    //
    //TODO: Stable 펄스열 추출 처럼 기분 펄스열을 모두 찾고 펄스열을 추출해야 되나 ?
    //date 	2023-07-16 19:40:36

    // 펄스열 구간마다 규칙성 펄스열과 불규칙성 펄스열을 같이 추출한다.
    // 펄스열은 각 단계마다 규칙성 펄스열과 불규칙성 펄스열을 동시에 수행한다.
    //-- 조철희 2005-12-09 16:11:27 --//
    //ExtractJitter( _STABLE + _JITTER_RANDOM );

    // 펄스열의 인덱스를 조사해서 겹쳐져 있으면 그 중 한개를 버린다.
    DropPulseTrain();

#ifdef _MSC_VER
    char buffer[200];

    sprintf( buffer, "---------------- 기준 펄스열 추출 : %2d[ns]", ( int ) ( ( CCommonUtils::GetDiffTime( &nowTime ) ) ) );
    CCommonUtils::WallMakePrint( buffer, '-' );
    Log( enDebug, "%s", buffer );

#endif

    //////////////////////////////////////////////////////////////////////////
    // 2차 펄스열 추출
    //  [7/2/2007 조철희]
    //-
    if( MustDo2ndPulseExtract() == true ) {
        // Log( enNormal, "2-차 펄스열 추출" );
//             m_pNewSigAnal->ClearAllMark();
//
//             MarkStablePulseTrain();
//
//             ResetJitterSeg();
//             ExtractJitter( _JITTER_RANDOM );
    }

#else
    _MSG( "펄스열 추적 알고리즘을 선택해야 합니다." );

#endif

    //m_CoPulseTrains = m_uiCoSeg;
    m_uiCoRefSeg = m_uiCoSeg;

    CPulExt::PulseExtract();

}

/**
 * @brief     위협 라이브러리 기반으로 펄스열을 추출한다.
 * @param     vector<SRadarMode * > * pVecMatchRadarMode
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-30, 16:52
 * @warning
 */
void CNPulExt::ExtractPulseTrainByLibrary( vector<SRadarMode *> *pVecMatchRadarMode )
{
#ifdef _MSC_VER

#elif __VXWORKS__

#else
    UINT i, uiCoSeg=0;

    STR_PRI_RANGE_TABLE extRange;

    SRadarMode *pRadarMode;

    vector <SRadarMode_Sequence_Values>::iterator iter;


    STR_PULSE_TRAIN_SEG *pSeg=GetPulseSeg();

    // 위협 라이브러리의 주파수 범위로 필터링...

    if( pVecMatchRadarMode->size() > 0 ) {
        pRadarMode = pVecMatchRadarMode->at(0);

        // 시작 펄스열 추출 얻기
        for( i=0 ; i < pVecMatchRadarMode->size() ; ++i ) {
            switch( pRadarMode->ePRI_Type ) {
                case RadarModePRIType::enumStable :
                    //extRange.tMinPRI = ITOAusCNV( pRadarMode->fPRI_TypicalMin );
                    //extRange.tMaxPRI = ITOAusCNV( pRadarMode->fPRI_TypicalMax );
                    //ExtractStablePT( & extRange, 0, false, enLIBRARY_MARK, LIBRARY_SEG );
                    break;

                case RadarModePRIType::enumDwellSWITCH :
                    break;

                case RadarModePRIType::enumSTAGGER:
                case RadarModePRIType::enumPATTERN:
                    break;

                case RadarModePRIType::enumJITTER :
                    extRange.tMinPRI = ITOAusCNV( pRadarMode->fPRI_TypicalMin );
                    extRange.tMaxPRI = ITOAusCNV( pRadarMode->fPRI_TypicalMax );
                    ExtractJitterPT( & extRange, UINT32_MAX, _sp.cm.Rpc, true , enLIBRARY_MARK, true, LIBRARY_SEG);

                    if( m_uiCoSeg != uiCoSeg ) {
                        Log( enDebug, "#[%05d] F%d[%5.1f~%5.1f] P%d[%5.1f~%5.1f]", pRadarMode->uiRadarModeIndex, pRadarMode->eRF_Type, pRadarMode->fRF_TypicalMin, pRadarMode->fRF_TypicalMax, pRadarMode->ePRI_Type, pRadarMode->fPRI_TypicalMin, pRadarMode->fPRI_TypicalMax );
                        PrintSeg( (int) uiCoSeg, & pSeg[uiCoSeg] );
                        uiCoSeg = m_uiCoSeg;
                    }
                    break;

                default :
                    break;
            }

            ++ pRadarMode;
        }

        Log( enNormal, "위협 라이브러리 기반 펄스열 추출: %d 개", m_uiCoSeg - m_uiAnalSeg );
        PrintAllSeg();

    }

    m_uiAnalSeg = m_uiCoSeg;

#endif

}

/**
 * @brief     추출한 펄스열을 마킹하도록 부 클래스로 호출한다.
 * @param     PDWINDEX * pPdwIndex
 * @param     unsigned int uiCount
 * @param     PULSE_EXTRACT_MARK usMarkType
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2006-01-23 10:03:32
 * @warning
 */
void CNPulExt::MarkToPDWIndex( PDWINDEX *pPdwIndex, unsigned int uiCount, PULSE_MARK enMarkType)
{
    CPulExt::MarkToPDWIndex( pPdwIndex, uiCount, enMarkType);

}

/**
 * @brief     PRI 하모닉을 부 클래스로 호출한다.
 * @param     _TOA priMean1
 * @param     _TOA priMean2
 * @param     _TOA uiThreshold
 * @return    UINT
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2006-01-23 10:03:36
 * @warning
 */
UINT CNPulExt::CheckHarmonic(_TOA priMean1, _TOA priMean2, _TOA uiThreshold )
{
    return m_pNewSigAnal->CheckHarmonic( priMean1, priMean2, uiThreshold );

}

/**
 * @brief     그룹화 포인터를 얻는다.
 * @return    STR_PDWINDEX *
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-30, 17:34
 * @warning
 */
STR_PDWINDEX *CNPulExt::GetFrqAoaGroupedPdwIndex()
{
    return m_pNewSigAnal->GetFrqAoaGroupedPdwIndex();

}

/**
 * @brief     펄스열의 PRI 정보를 계산한다.
 * @param     STR_PULSE_TRAIN_SEG * pSeg
 * @param     _TOA priMean
 * @param     UINT dtoa_count
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-30, 17:35
 * @warning
 */
void CNPulExt::CalPRIRange( STR_PULSE_TRAIN_SEG *pSeg, _TOA priMean, UINT dtoa_count )
{
    m_pNewSigAnal->CalPRIRange( pSeg, priMean, dtoa_count );

}

/**
 * @brief     DTOA 히스토그램을 계산한다. 이 계산은 PRI 범위를 찾을때 사용한다.
 * @param     PDWINDEX * pPdwIndex
 * @param     unsigned int uiCount
 * @param     STR_MINMAX_TOA * pRange
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2006-07-27 17:16:36
 * @warning
 */
void CNPulExt::MakeDtoaHistogram( PDWINDEX *pPdwIndex, unsigned int uiCount, STR_MINMAX_TOA *pRange )
{
    m_pNewSigAnal->MakeDtoaHistogram( pPdwIndex, uiCount, pRange );
}

/**
 * @brief     DTOA 히스토그램 데이터 포인터를 리턴한다.
 * @return    STR_DTOA_HISTOGRAM *
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2006-07-28 13:19:17
 * @warning
 */
STR_DTOA_HISTOGRAM *CNPulExt::GetDtoaHist()
{
    return m_pNewSigAnal->GetDtoaHist();
}

/**
 * @brief     펄스 개수를 얻는다.
 * @return    unsigned int
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2008-11-11 21:41:20
 * @warning
 */
unsigned int CNPulExt::GetCoPdw()
{
    return m_pNewSigAnal->GetCoPdw();
}

/**
 * @brief     부 클래스에 요청하여 펄스 정보를 얻는다.
 * @return    int
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-30, 17:36
 * @warning
 */
// int CNPulExt::GetPulseStat()
// {
//     return m_pNewSigAnal->GetPulseStat();
// }


/**
 * @brief     펄스 마킹을 초기화 한다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-04 16:20:09
 * @warning
 */
void CNPulExt::ClearAllMark()
{
    CPulExt::ClearAllMark();

}

#ifdef _LOG_ANALTYPE_
/**
 * @brief     GetLogAnalType
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-09-21 11:57:45
 * @warning
 */
bool CNPulExt::IsLogAnalType( LogType enLogType )
{
    return m_pNewSigAnal->IsLogAnalType( enLogType );
}

#endif