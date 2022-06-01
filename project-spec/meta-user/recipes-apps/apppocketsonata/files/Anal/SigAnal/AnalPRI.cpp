// AnalPRI.cpp: implementation of the CAnalPRI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"


#if defined(_ELINT_) || defined(_XBAND_)
#include "../OFP_Main.h"
#elif _POCKETSONATA_
#include "../INC/Macros.h"
#include "../Identify/ELUtil.h"

#else
#error "컴파일러에 DEFINE 을 추가해야 합니다."
#endif

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "../../Utils/MulDiv64.h"

#include "AnalPRI.h"

#include "../../Include/globals.h"



// 에미터로 인지하는 값 
// UINT _spdiffaoa[ 6 ] =
// {
//     0, 5 * KHARM_AOA_MAR, 5 * KHARM_AOA_MAR, 5 * KHARM_AOA_MAR, 5 * KHARM_AOA_MAR, 5 * KHARM_AOA_MAR
// } ;

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : incUSCompare
// 반환되는 형  : int
// 함 수 인 자  : const void *arg1
// 함 수 인 자  : const void *arg2
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2013-12-07 16:39:21
//
int incUSCompare( const void *arg1, const void *arg2 )
{
    int iRet;
    const unsigned short *p1, *p2;

    p1 = (const unsigned short *) arg1;
    p2 = (const unsigned short *) arg2;

    if( *p1 > *p2 ) {
        iRet = 1;
    }
    else if( *p1 < *p2 ) {
        iRet = -1;
    }
    else {
        iRet = 0;
    }

    return iRet;

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : pdwindexCompare
// 반환되는 형  : int
// 함 수 인 자  : const void *arg1
// 함 수 인 자  : const void *arg2
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-17 19:47:30
//
int pdwindexCompare(const void *arg1, const void *arg2)
{
    int iRet;

    const PDWINDEX *p1, *p2;

    p1 = (const PDWINDEX *)arg1;
    p2 = (const PDWINDEX *)arg2;

    if (*p1 > *p2) {
        iRet = 1;
    }
    else if (*p1 < *p2) {
        iRet = -1;
    }
    else {
        iRet = 0;
    }

    return iRet;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::CAnalPRI
// 함 수 인 자  : int coMaxPdw /*=NSP_MAX_PDW*/
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-07-28 13:18:51
//
//##ModelId=426C87D7003F
CAnalPRI::CAnalPRI( unsigned int uiCoMaxPdw )
{
    int i=0;

    BOOL bRet=TRUE;

    m_uiMaxPdw = min( uiCoMaxPdw, (unsigned int) MAX_PDW );

	// 시스템 변수 초기화
	m_spdiffaoa[ i++ ] = 5 * KHARM_AOA_MAR;
	m_spdiffaoa[ i++ ] = 5 * KHARM_AOA_MAR;
	m_spdiffaoa[ i++ ] = 5 * KHARM_AOA_MAR;
	m_spdiffaoa[ i++ ] = 5 * KHARM_AOA_MAR;
	m_spdiffaoa[ i++ ] = 5 * KHARM_AOA_MAR;
	m_spdiffaoa[ i ] = 5 * KHARM_AOA_MAR;

    m_pMergePdwIndex = ( PDWINDEX * ) malloc( sizeof( PDWINDEX ) * m_uiMaxPdw );
    if( m_pMergePdwIndex == NULL ) {
        bRet = FALSE;
        Log( enError, "[W] m_pMergePdwIndex's memory allocation error !" );
        WhereIs;
    }

    for( i=0 ; i < MAX_AET ; ++i ) {
        m_Emitter[i].stPDW.pIndex = ( PDWINDEX * ) malloc( sizeof( PDWINDEX ) * m_uiMaxPdw );
        if( m_Emitter[i].stPDW.pIndex == NULL ) {
            bRet = FALSE;
            Log( enError, "[W] m_Emitter[%d].pdw.pIndex's memory allocation error !" , i );
            WhereIs;
        }
    }

    m_pPulseDtoa = ( _TOA * ) malloc( sizeof( _TOA ) * m_uiMaxPdw );
    if( m_pPulseDtoa == NULL ) {
        bRet = FALSE;
        Log( enError, "[W] m_pPulseDtoa's memory allocation error !" );
        WhereIs;
    }
    m_pPulseToa = ( _TOA * ) malloc( sizeof( _TOA ) * m_uiMaxPdw );
    if( m_pPulseToa == NULL ) {
        bRet = FALSE;
        Log( enError, "[W] m_pPulseToa's memory allocation error !" );
        WhereIs;
    }
    m_pToaAcf = ( _TOA * ) malloc( sizeof( _TOA ) * m_uiMaxPdw );
    if( m_pToaAcf == NULL ) {
        bRet = FALSE;
        Log( enError, "[W] m_pToaAcf's memory allocation error !" );
        WhereIs;
    }
    m_pRefFramePri = ( _TOA * ) malloc( sizeof( _TOA ) * m_uiMaxPdw );
    if( m_pRefFramePri == NULL ) {
        bRet = FALSE;
        Log( enError, "[W] m_pRefFramePri's memory allocation error !" );
        WhereIs;
    }

    m_DwlSeg.pdw.pIndex = ( PDWINDEX * ) malloc( sizeof( _TOA ) * m_uiMaxPdw );
    if( m_DwlSeg.pdw.pIndex == NULL ) {
        bRet = FALSE;
        Log( enError, "[W] m_RefSeg.pdw.pIndex's memory allocation error !" );
        WhereIs;
    }

    m_pSampleToa = ( _TOA * ) malloc( sizeof( _TOA ) * m_uiMaxPdw );
    if( m_pSampleToa == NULL ) {
        bRet = FALSE;
        Log( enError, "[W] m_pSampleToa's memory allocation error !" );
        WhereIs;
    }

    m_pSampleData = ( int * ) malloc( sizeof( int ) * m_uiMaxPdw );
    if( m_pSampleData == NULL ) {
        bRet = FALSE;
        Log( enError, "[W] m_pSampleData's memory allocation error !" );
        WhereIs;
    }

    m_pNormData = ( int * ) malloc( sizeof( _TOA ) * m_uiMaxPdw );
    if( m_pNormData == NULL ) {
        bRet = FALSE;
        Log( enError, "[W] m_pNormData's memory allocation error !" );
        WhereIs;
    }

    m_pDataX = ( _TOA * ) malloc( sizeof( _TOA ) * m_uiMaxPdw );
    if( m_pDataX == NULL ) {
        bRet = FALSE;
        Log( enError, "[W] m_pDataX's memory allocation error !" );
        WhereIs;
    }

    m_pDataY = ( _TOA * ) malloc( sizeof( _TOA ) * m_uiMaxPdw );
    if( m_pDataY == NULL ) {
        bRet = FALSE;
        Log( enError, "[W] m_pDataX's memory allocation error !" );
        WhereIs;
    }

    m_pAcf = ( float * ) malloc( sizeof( float ) * m_uiMaxPdw );
    if( m_pAcf == NULL ) {
        bRet = FALSE;
        Log( enError, "[W] m_pAcf's memory allocation error !" );
        WhereIs;
    }

    m_pCanPeak = ( _TOA * ) malloc( sizeof( _TOA ) * m_uiMaxPdw );
    if( m_pCanPeak == NULL ) {
        bRet = FALSE;
        Log( enError, "[W] m_pCanPeak's memory allocation error !" );
        WhereIs;
    }

    m_p1PrimeData = ( int * ) malloc( sizeof( int ) * m_uiMaxPdw );
    if( m_p1PrimeData == NULL ) {
        bRet = FALSE;
        Log( enError, "[W] m_p1PrimeData's memory allocation error !" );
        WhereIs;
    }

    m_p2PrimeData = ( int * ) malloc( sizeof( int ) * m_uiMaxPdw );
    if( m_p2PrimeData == NULL ) {
        bRet = FALSE;
        Log( enError, "[W] m_p2PrimeData's memory allocation error !" );
        WhereIs;
    }

    if( bRet == FALSE ) {
        Log( enError, "[W] CAnalPRI Object is failed !" );
    }

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::~CAnalPRI
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-07-28 18:06:29
//
//##ModelId=426C87D70048
CAnalPRI::~CAnalPRI()
{
    free( m_pMergePdwIndex );

    for( int i=0 ; i < MAX_AET ; ++i ) {
        free( m_Emitter[i].stPDW.pIndex );
    }

    free( m_pPulseDtoa );
    free( m_pPulseToa );
    free( m_pSampleToa );
    free( m_pNormData );
    free( m_pSampleData );
    free( m_pDataX );
    free( m_pDataY );
    free( m_pToaAcf );
    free( m_pAcf );
    free( m_pCanPeak );
    free( m_pRefFramePri );

    free( m_p1PrimeData );
    free( m_p2PrimeData );

    if( m_DwlSeg.pdw.pIndex != NULL ) {
        free( m_DwlSeg.pdw.pIndex );
        m_DwlSeg.pdw.pIndex = NULL;
    }

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::Init
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-04-26 18:21:21
//
//##ModelId=42757D4D027B
void CAnalPRI::Init()
{
    int i = 0;

    m_spdiffaoa[i++] = 5 * KHARM_AOA_MAR;
    m_spdiffaoa[i++] = 5 * KHARM_AOA_MAR;
    m_spdiffaoa[i++] = 5 * KHARM_AOA_MAR;
    m_spdiffaoa[i++] = 5 * KHARM_AOA_MAR;
    m_spdiffaoa[i++] = 5 * KHARM_AOA_MAR;
    m_spdiffaoa[i] = 5 * KHARM_AOA_MAR;

    _EQUALS3( m_uiAnalEmitter, m_uiCoEmitter, _spZero )
    m_uiAnalSeg = 0;

    for( int i=0 ; i < MAX_AET ; ++i ) {
        m_Emitter[i].stPDW.uiCount = _spZero;
    }

    m_pSeg = GetPulseSeg();
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::Analysis
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-10 17:08:06
//
//##ModelId=428832A30305
void CAnalPRI::Analysis()
{
    PrintAllEmitter();
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CAnalPRI::PrintAllEmitter
//! \author   조철희
//! \return   void
//! \version  1.37
//! \date     2006-08-24 16:05:31
//! \warning
//
void CAnalPRI::PrintAllEmitter()
{
    //////////////////////////////////////////////////////////////////////////
    //
    // 가상 에미터 프린트
    STR_EMITTER *pEmitter;
    unsigned int i;

    char buffer[1000];
    int iCnt;

    char szEmitterMark[_SIZE_EMITTER_MARK] = { ' ', 'X' };

    pEmitter = & m_Emitter[m_uiAnalEmitter];
    if( m_uiCoEmitter == m_uiAnalEmitter ) {
        Log( enDebug, "No PAET !!" );
    }
    else {
        Log(enDebug, "PAET : %d" , m_uiCoEmitter-m_uiAnalEmitter );

        for( i=m_uiAnalEmitter ; i < m_uiCoEmitter ; ++i, ++pEmitter ) {
            iCnt=0;
            buffer[0] = NULL;
            for( unsigned int j=0 ; j < pEmitter->uiCoSeg ; ++j ) {
                iCnt += sprintf( & buffer[iCnt], "[%2d]" , pEmitter->uiSegIdx[j] );
            }
            Log(enDebug, "\t[%2d]%1c : Co(%2d, %s)" , i, szEmitterMark[pEmitter->mark], pEmitter->uiCoSeg, buffer );
            Log(enDebug, "\t\t F[%1d], P[%1d] (%5d -%5d)" , pEmitter->enFreqType, pEmitter->enPRIType, I_TOAusCNV( pEmitter->stPRI.tMin ), I_TOAusCNV( pEmitter->stPRI.tMax ) );

        }
    }

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::GroupingStable
// 반환되는 형  : void
// 함 수 인 자  : BOOL fDecisionEmitter
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-12 14:12:56
//
//##ModelId=428832A302E7
void CAnalPRI::GroupingStable( BOOL fDecisionEmitter )
{
    unsigned int i, j;

    BOOL bMakeEmitter, bOverlap;

    STR_EMITTER *pEmitter;
    STR_PULSE_TRAIN_SEG *pSeg1, *pSeg2;

    pSeg1 = & m_pSeg[m_uiAnalSeg];
    for( i=m_uiAnalSeg ; i < m_uiCoSeg ; ++i, ++pSeg1 ) {
        if( pSeg1->enMark == CHECKED_SEG || pSeg1->enMark == DELETE_SEG ) {
            continue;
        }

        /*! \bug  최대 에미터 개수 벗어날 조건 추가함.
            \date 2006-08-29 09:58:13, 조철희
        */
        if (m_uiCoEmitter >= MAX_AET) {
            break;
        }

        if( pSeg1->enPriType == _STABLE ) {
            bMakeEmitter = TRUE;

            pEmitter = & m_Emitter[ m_uiCoEmitter ];

            // 에미터 변수 초기화
            pEmitter->enPRIType = _STABLE;
            pEmitter->uiCoSeg = 0;
            pEmitter->uiSegIdx[ pEmitter->uiCoSeg++ ] = i;

            pSeg2 = & m_pSeg[i+1];
            bOverlap = FALSE;
            for( j=i+1 ; j < m_uiCoSeg ; ++j, ++pSeg2 ) {
                
                if( pSeg2->enMark == CHECKED_SEG || pSeg2->enMark == DELETE_SEG || pSeg2->enMark == OVERLAPPED_SEG ) {
                    continue;
                }

                // 유사 펄스열이 있고 시간적으로 겹쳐져 있으면 STABLE 로 마킹하지 않는다.
                // 다음 GroupStagger 단계에서 Stagger 타입으로 만들기 위함이다.
                if( pSeg2->enPriType == _STABLE && CompFreq( pSeg1, pSeg2 ) == TRUE ) {
                    if( CheckHarmonic( pSeg1, pSeg2 ) >= 1 ) {
                        //pSeg2->mark = CHECKED_SEG;
                        //pEmitter->seg_idx[ pEmitter->uiCoSeg++ ] = j;
                        if( OverlappedSeg( pSeg1, pSeg2 ) == false ) {
                            pSeg2->enMark = CHECKED_SEG;
                            pEmitter->uiSegIdx[ pEmitter->uiCoSeg++ ] = j;
                        }
                        else {
                            bOverlap = TRUE;
                            pSeg1->enMark = NORMAL_SEG;
                            pSeg2->enMark = OVERLAPPED_SEG;
                        }

                    }
                }
            }

            /*! \debug  겹쳐지지 않은 STABLE 끼리 까지 에미터를 생성하게 한다.
            	\author 조철희 (churlhee.jo@lignex1.com)
            	\date 	2022-04-20 14:06:24
            */
            //? 아래는 생략함... 왜 이 루틴을 집어 넣었지 

            // 겹쳐지지 않은 STABLE 일때만 에미터로 뺀다.            
            // if( bOverlap == TRUE || pSeg1->enMark == OVERLAPPED_SEG ) {
            //     bMakeEmitter = FALSE;
            // }

            // 겹쳐져 있지 않은 STABLE 펄스열에 대해서만 에미터를 생성한다.
            //-- 조철희 2005-10-28 16:15:45 --//
            if( bMakeEmitter == TRUE ) {
                pSeg1->enMark = CHECKED_SEG;

                MergePdwIndexInSeg( pEmitter );

                // 펄스열 로그 판단
                // 에미터로 생성 여부를 결정한다.
                if( fDecisionEmitter == TRUE || DecisionEmitter( pEmitter ) == TRUE ) {
                    // 레벨 값은 초기화한다.
                    //-- 조철희 2006-01-25 15:54:32 --//
                    pEmitter->uiStagDwellLevelCount = 0;

                    // 유사 PRI로 병합된 Stable 펄스열들에 대해서 다시 PRI 값을 재 산출해야 한다.
                    // 어떤 신호에 대해서는 원 신호의 2배 PRI가 추출될 수 있고 유사 PRI 펄스열 끼리
                    // 병합이 되면서 원 신호를 자세히 보면 원래의 PRI값을 찾을 수 있다.
                    //-- 조철희 2005-10-28 15:19:10 --//
                    pEmitter->mark = NORMAL_EMITTER;
                    pEmitter->enSignalType = AnalSignalType( pEmitter );

                    // PRI 범위 및 타입 결정
                    CalcEmitterPri( pEmitter );
                    pEmitter->enPRIType = _STABLE;

                    pEmitter->tFramePri = GetMinPulseTrainMean( pEmitter );

                    // 주파수 범위 및 타입 결정
                    CalcEmitterFrq( pEmitter );
                    pEmitter->enFreqType = AnalFreqType( pEmitter );

                    CalcEmitterPW( pEmitter );

                    ++ m_uiCoEmitter;
                }
                // UnknownExtract 펄스열에 삽입한다.
                else {
                    // 에미터 실패된 펄스열들은 모두 삭제된 펄스열로 등록한다.
                    // 추후에 펄스열들 끼리 병합을 수행한다.
                    for( j=0 ; j < pEmitter->uiCoSeg ; ++j )
                        m_pSeg[ pEmitter->uiSegIdx[j] ].enMark = DELETE_SEG;
                }
            }
        }
    }
}

/**
 * @brief CAnalPRI::GroupingDwell
 * @param fDecisionEmitter
 */
void CAnalPRI::GroupingDwell( BOOL fDecisionEmitter )
{
    unsigned int i, j, k;

    BOOL bMakeEmitter;

    STR_EMITTER *pEmitter;
    STR_PULSE_TRAIN_SEG *pSeg1, *pSeg2;

    pSeg1 = & m_pSeg[m_uiAnalSeg];
    for( i=m_uiAnalSeg ; i < m_uiCoSeg ; ++i, ++pSeg1 ) {
        if (pSeg1->enMark == CHECKED_SEG || pSeg1->enMark == DELETE_SEG) {
            continue;
        }

        /*! \bug  최대 에미터 개수 벗어날 조건 추가함.
            \date 2006-08-29 09:58:13, 조철희
        */
        if (m_uiCoEmitter >= MAX_AET) {
            break;
        }

        if( pSeg1->enPriType == _DWELL ) {
            bMakeEmitter = TRUE;

            pEmitter = & m_Emitter[ m_uiCoEmitter ];

            // 에미터 변수 초기화
            pEmitter->enPRIType = _DWELL;
            pEmitter->uiCoSeg = 0;
            pEmitter->uiSegIdx[ pEmitter->uiCoSeg++ ] = i;

            pSeg2 = & m_pSeg[i+1];
            for( j=i+1 ; j < m_uiCoSeg ; ++j, ++pSeg2 ) {
                if( pSeg2->enMark == CHECKED_SEG || pSeg2->enMark == DELETE_SEG ) {
                    continue;
                }

                // 유사 펄스열이 있고 시간적으로 겹쳐져 있으면 STABLE 로 마킹하지 않는다.
                // 다음 GroupStagger 단계에서 Stagger 타입으로 만들기 위함이다.
                if( pSeg2->enPriType == _DWELL && CompFreq( pSeg1, pSeg2 ) == TRUE ) {
                    if( CheckHarmonic( pSeg1, pSeg2 ) == 0 ) {
                        pSeg2->enMark = CHECKED_SEG;
                        pEmitter->uiSegIdx[ pEmitter->uiCoSeg++ ] = j;
/*
                        if( OverlappedSeg( pSeg1, pSeg2 ) == true ) {
                            pSeg2->mark = CHECKED_SEG;
                            pEmitter->seg_idx[ pEmitter->seg_count++ ] = j;
                        }
                        else {
                            bMakeEmitter = FALSE;
                            pSeg1->mark = NORMAL_SEG;
                            break;
                        }
*/
                    }
                }
            }

            // 겹쳐져 있지 않은 STABLE 펄스열에 대해서만 에미터를 생성한다.
            //-- 조철희 2005-10-28 16:15:45 --//
            if( bMakeEmitter == TRUE ) {
                pSeg1->enMark = CHECKED_SEG;

                MergePdwIndexInSeg( pEmitter );

                // 펄스열 로그 판단
                // 에미터로 생성 여부를 결정한다.
                if( fDecisionEmitter == TRUE || DecisionEmitter( pEmitter ) == TRUE ) {

                    // 유사 PRI로 병합된 Stable 펄스열들에 대해서 다시 PRI 값을 재 산출해야 한다.
                    // 어떤 신호에 대해서는 원 신호의 2배 PRI가 추출될 수 있고 유사 PRI 펄스열 끼리
                    // 병합이 되면서 원 신호를 자세히 보면 원래의 PRI값을 찾을 수 있다.
                    //-- 조철희 2005-10-28 15:19:10 --//
                    pEmitter->mark = NORMAL_EMITTER;
                    pEmitter->enSignalType = AnalSignalType( pEmitter );

                    // 주파수 범위 및 타입 결정
                    CalcEmitterFrq( pEmitter );
                    pEmitter->enFreqType = AnalFreqType( pEmitter );

                    // 레벨 값은 초기화한다.
                    //-- 조철희 2006-01-25 15:54:32 --//
                    if( pEmitter->uiCoSeg >= _spTwo ) {
                        pEmitter->uiStagDwellElementCount = pEmitter->uiCoSeg;

                        for( k=0 ; k < pEmitter->uiCoSeg ; ++k ) {
                            pEmitter->tStaggerDwellElement[k] = m_pSeg[ pEmitter->uiSegIdx[k] ].pri.tMean;
                        }

                        // PRI 범위 및 타입 결정
                        CalcEmitterPri( pEmitter );
                        pEmitter->enPRIType = _DWELL;
                    }
                    else {
                        // PRI 범위 및 타입 결정
                        CalcEmitterPri( pEmitter );
                        pEmitter->enPRIType = _STABLE;

                        pEmitter->uiStagDwellElementCount = 0;
                    }

                    CalcEmitterPW( pEmitter );

                    ++ m_uiCoEmitter;
                }
                // UnknownExtract 펄스열에 삽입한다.
                else {
                    // 에미터 실패된 펄스열들은 모두 삭제된 펄스열로 등록한다.
                    // 추후에 펄스열들 끼리 병합을 수행한다.
                    for( j=0 ; j < pEmitter->uiCoSeg ; ++j )
                        m_pSeg[ pEmitter->uiSegIdx[j] ].enMark = DELETE_SEG;
                }
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::GroupingStagger
// 반환되는 형  : void
// 함 수 인 자  : BOOL fDecisionEmitter
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-12 14:13:04
//
//##ModelId=428832A302D3
void CAnalPRI::GroupingStagger( BOOL fDecisionEmitter )
{
    unsigned int i, j;

    BOOL bCheck;

    STR_EMITTER *pEmitter;
    STR_PULSE_TRAIN_SEG *pSeg1, *pSeg2;

	pSeg1 = & m_pSeg[m_uiAnalSeg];
	for( i=m_uiAnalSeg ; i < m_uiCoSeg ; ++i, ++pSeg1 ) {
		// 스태거열 분석할 때는 삭제된 펄스열도 포함해서 본다.
		// 왜냐하면 펄스열 추출시에는 규칙성 펄스열 부족으로 짤라 낼수 있기 때문이다.
		if( pSeg1->enMark == CHECKED_SEG || pSeg1->enMark == DELETE_SEG ) {
			continue;
        }

        /*! \bug  최대 에미터 개수 벗어날 조건 추가함.
            \date 2006-08-29 09:58:13, 조철희
        */
        if (m_uiCoEmitter >= MAX_AET) {
            break;
        }

		if( pSeg1->enPriType == _STABLE ) {
			bCheck = TRUE;

			// 에미터 변수 초기화
			pEmitter = & m_Emitter[ m_uiCoEmitter ];
			pEmitter->enPRIType = _STABLE;
			pEmitter->uiCoSeg = _spZero;
			pEmitter->uiSegIdx[ pEmitter->uiCoSeg++ ] = (UINT)i;

			pSeg2 = & m_pSeg[i+1];
			for( j=i+1 ; j < m_uiCoSeg ; ++j, ++pSeg2 ) {
				if( pSeg2->enMark == CHECKED_SEG || pSeg2->enMark == DELETE_SEG )
					continue;

				if( CompFreq( pSeg1, pSeg2 ) == TRUE && pSeg2->enPriType == _STABLE &&
					CompMeanDiff<_TOA>( pSeg1->pri.tMean, pSeg2->pri.tMean, STABLE_MARGIN ) == TRUE ) {
					if( OverlappedSeg( pSeg1, pSeg2 ) == true && CheckPriInterval( pSeg1, pSeg2 ) == FALSE ) {
						bCheck = FALSE;

						pSeg2->enMark = CHECKED_SEG;
						pEmitter->uiSegIdx[ pEmitter->uiCoSeg++ ] = (UINT)j;
					}
				}
			}

			if( bCheck == FALSE ) {
				unsigned int k;
				_TOA priMean, priLow, priHgh;

				STR_PULSE_TRAIN_SEG *pSeg;
				
				pSeg1->enMark = CHECKED_SEG;
				MergePdwIndexInSeg( pEmitter );
				// 스태거 펄스열이면 병합된 PRI 값을 대충 파악해 본다. 
				priMean = VerifyPRI( pEmitter->stPDW.pIndex, pEmitter->stPDW.uiCount );
				priLow = m_pSeg[ pEmitter->uiSegIdx[0] ].pri.tMax;
                _EQUALS3( priHgh, pEmitter->stPRI.tMax, 0 )
				for( k=0 ; k < pEmitter->uiCoSeg ; ++k ) {
					pSeg = & m_pSeg[ pEmitter->uiSegIdx[k] ];
					priLow = _min( priLow, pSeg->pri.tMin );
					priHgh = _max( priHgh, pSeg->pri.tMax );
				}
				if( priMean > priLow ) {
					// 해당 펄스열 인덱스를 해지한다.
					for( k=0 ; k < pEmitter->uiCoSeg ; ++k ) {
						pSeg = & m_pSeg[ pEmitter->uiSegIdx[k] ];
						pSeg->enMark = NORMAL_SEG;
					}
				}
				else {
					// 펄스열 로그 판단
					// 에미터로 생성 여부를 결정한다.
					if( fDecisionEmitter == TRUE || DecisionEmitter( pEmitter ) == TRUE ) {
						pEmitter->mark = NORMAL_EMITTER;
						pEmitter->enSignalType = AnalSignalType( pEmitter );

						// 프레임 PRI는 규칙성 펄스열의 PRI로 한다.
						//-- 조철희 2005-11-23 10:31:30 --//
						pEmitter->tFramePri = pSeg1->pri.tMean;

						// PRI 범위 및 타입 결정
						CalcEmitterPri( pEmitter );
						pEmitter->enPRIType = _STAGGER_DWELL;

						// 주파수 범위 및 타입 결정
						CalcEmitterFrq( pEmitter );
						pEmitter->enFreqType = AnalFreqType( pEmitter );

						CalcEmitterPW( pEmitter );

						CopySeg( pEmitter );

						++ m_uiCoEmitter;
					}
					// UnknownExtract 펄스열에 삽입한다.
					else {
						// 에미터 실패된 펄스열들은 모두 삭제된 펄스열로 등록한다.
						// 추후에 펄스열들 끼리 병합을 수행한다.
						for( j=0 ; j < pEmitter->uiCoSeg ; ++j ) {
							m_pSeg[ pEmitter->uiSegIdx[j] ].enMark = DELETE_SEG;
                        }

					}
				}
			}
		}

	}

}

/**
 * @brief		CopySeg
 * @param		STR_EMITTER * pEmitter
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2022/01/03 14:52:31
 * @warning		
 */
void CAnalPRI::CopySeg(STR_EMITTER *pEmitter)
{
    unsigned int i;

    // 에미터의 펄스열 정보를 복사한다.
    for (i = 0; i < pEmitter->uiCoSeg ; i++) {
        memcpy( & pEmitter->stSeg[i], & m_pSeg[pEmitter->uiSegIdx[i]], sizeof(STR_PULSE_TRAIN_SEG) );

        // 현재 펄스열 정보가 main 펄스열일 경우 인덱스를 변환한다.
        if( pEmitter->uiSegIdx[i] == pEmitter->uiMainSeg) {
            pEmitter->uiMainSeg = (UINT)i;
        }
    }
}


//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::GroupingDwell
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-11-01 19:16:46
//
// void CAnalPRI::GroupingDwell()
// {
// 	int i;
//
// 	int maxPdwCount;
// 	int nMakeEmitter;
//
// 	STR_EMITTER *pEmitter, *pMakeEmitter;
//
// 	// 생성된 에미터가 없으면 Dwell 병합을 하지 않는다.
// 	if( m_nAnalEmitter == m_CoEmitter )
// 		return;
//
// 	pMakeEmitter = & m_Emitter[ m_CoEmitter ];
// 	pEmitter = & m_Emitter[ m_nAnalEmitter ];
//
// 	maxPdwCount = 0;
// 	nMakeEmitter = FALSE;
// 	pMakeEmitter->seg_count = 0;
// 	pMakeEmitter->stag_dwell_level_cnt = 0;
// 	// 생성된 에미터들로부터 DWELL 타입으로 된것을 추출한다.
// 	for( i=m_nAnalEmitter ; i < m_CoEmitter ; ++i ) {
// 		if( pEmitter->pri_type == _STABLE ) {
// 			++ nMakeEmitter;
//
// 			// 펄스열 인덱스
// 			memcpy( & pMakeEmitter->seg_idx[pMakeEmitter->seg_count], pEmitter->seg_idx, sizeof(UINT)*pEmitter->seg_count );
// 			pMakeEmitter->seg_count += pEmitter->seg_count;
//
// 			// 레벨 값
// 			pMakeEmitter->stag_dwell_level[ pMakeEmitter->stag_dwell_level_cnt++ ] = m_pSeg[ pEmitter->main_seg ].pri.mean;
//
// 			if( maxPdwCount < pEmitter->pdw.count ) {
// 				maxPdwCount = pEmitter->pdw.count;
// 				pMakeEmitter->main_seg = pEmitter->main_seg;
// 			}
// 		}
//
// 		++ pEmitter;
// 	}
//
// 	if( nMakeEmitter >= 1 ) {
// 		pEmitter = & m_Emitter[ m_nAnalEmitter ];
//
// 		// 펄스열 인덱스 복사
// 		memcpy( pEmitter->seg_idx, pMakeEmitter->seg_idx, sizeof( pMakeEmitter->seg_idx ) );
// 		pEmitter->seg_count = pMakeEmitter->seg_count;
//
// 		memcpy( pEmitter->stag_dwell_level, pMakeEmitter->stag_dwell_level, sizeof( pMakeEmitter->stag_dwell_level ) );
// 		pEmitter->stag_dwell_level_cnt = pMakeEmitter->stag_dwell_level_cnt;
//
// 		pEmitter->main_seg = pMakeEmitter->main_seg;
//
// 		MergePdwIndexInSeg( pEmitter );
//
// 		pEmitter->pri_type = _DWELL;
// 		pEmitter->mark = NORMAL_EMITTER;
// 		pEmitter->signal_type = AnalSignalType( pEmitter );
//
// 		// 주파수 범위 및 타입 결정
// 		CalcEmitterFrq( pEmitter );
// 		pMakeEmitter->freq_type = AnalFreqType( pEmitter );
//
// 		CalcEmitterPW( pEmitter );
//
// 		m_CoEmitter = m_nAnalEmitter + ( m_CoEmitter - ( nMakeEmitter - 1 ) );
// 	}
// }

/**
 * @brief     GroupingJitterWithJitter
 * @param     int iLoop
 * @param     BOOL bDecisionEmitter
 * @param     STR_PULSE_TRAIN_SEG * pRefSeg
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-27, 18:41
 * @warning
 */
void CAnalPRI::GroupingJitterWithJitter( STR_PULSE_TRAIN_SEG *pRefSeg, int iLoop, BOOL bDecisionEmitter )
{
    UINT j;

    unsigned int uiHarmonic;

    STR_EMITTER *pEmitter;

    STR_PULSE_TRAIN_SEG *pCmpSeg;

    if( pRefSeg->enPriType == _JITTER_RANDOM ) {
        pRefSeg->enMark = CHECKED_SEG;

        // 에미터 변수 초기화
        pEmitter = &m_Emitter[m_uiCoEmitter];
        pEmitter->enPRIType = _JITTER_RANDOM;
        pEmitter->uiCoSeg = 0;
        pEmitter->uiSegIdx[pEmitter->uiCoSeg++] = iLoop;

        pCmpSeg = &m_pSeg[iLoop + 1];
        for( j = iLoop + 1 ; j < m_uiCoSeg ; ++j, ++pCmpSeg ) {
            if( pCmpSeg->enMark == CHECKED_SEG || pCmpSeg->enMark == DELETE_SEG ) {
                continue;
            }

            // 탐지에서는 주파수 범위, PRI 타입 등을 체크한다.
            if( bDecisionEmitter == FALSE ) {
                /*! \todo	유사 지터열끼리의 병합은 펄스폭을 고려해서 병합 판단을 한다. */
                /*! \bug  방위 범위 비교까지 고려한다.
                    \date 2007-06-18 13:37:31, 조철희
                */
                // 펄스열 간의 병합시 서로간의 TOA가 안 겹쳐지도록 병합해야 함.
                if( pCmpSeg->enPriType == _JITTER_RANDOM && \
                    ( CompFreq( pRefSeg, pCmpSeg ) == TRUE && CompAoa( pRefSeg, pCmpSeg ) == TRUE && OverlappedSeg( pRefSeg, pCmpSeg ) == true ) ) {
                    uiHarmonic = CheckHarmonic( pRefSeg, pCmpSeg );
                    if( (uiHarmonic >= 1 && uiHarmonic <= 2) && OverlappedSeg( pRefSeg, pCmpSeg ) == false ) {
                        pCmpSeg->enMark = CHECKED_SEG;
                        pEmitter->uiSegIdx[pEmitter->uiCoSeg++] = j;
                    }
                }
            }

            // 추적에서 펄스열 추출된 펄스열들은 타입, 주파수, 하모닉에 상관없이 하나로 만든다.
            // 그러나, 시간적으로 겹쳐져 있는 것은 해당 펄스열들은 제거한다.
            else {
                if( OverlappedSeg( pRefSeg, pCmpSeg ) == false ) {
                    pCmpSeg->enMark = CHECKED_SEG;
                    pEmitter->uiSegIdx[pEmitter->uiCoSeg++] = j;
                }
                else {
                    // 추출된 펄스 개수가 작은 펄스열을 DELETE_SEG 마킹한다.
                    if( pRefSeg->pdw.uiCount < pCmpSeg->pdw.uiCount ) {
                        pRefSeg->enMark = DELETE_SEG;
                    }
                    else {
                        pCmpSeg->enMark = DELETE_SEG;
                    }
                }
            }
        }

        // 펄스열 병합
        MergePdwIndexInSeg( pEmitter );

        // 펄스열 로그 판단
        // 에미터로 생성 여부를 결정한다.
        if( bDecisionEmitter == TRUE || DecisionEmitter( pEmitter ) == TRUE ) {
            // 레벨 값은 초기화한다.
            //-- 조철희 2006-01-25 15:54:32 --//
            pEmitter->uiStagDwellLevelCount = 0;

            pEmitter->mark = NORMAL_EMITTER;
            pEmitter->enSignalType = AnalSignalType( pEmitter );

            // PRI 범위 및 타입 결정
            CalcEmitterPri( pEmitter );
            pEmitter->enPRIType = _JITTER_RANDOM;

            // 주파수 범위 및 타입 결정
            CalcEmitterFrq( pEmitter );
            pEmitter->enFreqType = AnalFreqType( pEmitter );

            CalcEmitterPW( pEmitter );

            ++m_uiCoEmitter;
        }
        // UnknownExtract 펄스열에 삽입한다.
        else {
            // 에미터 실패된 펄스열들은 모두 삭제된 펄스열로 등록한다.
            // 추후에 펄스열들 끼리 병합을 수행한다.
            for( j = 0; j < pEmitter->uiCoSeg; ++j ) {
                m_pSeg[pEmitter->uiSegIdx[j]].enMark = DELETE_SEG;
            }
        }
    }
}


/**
 * @brief     GroupingJitterWithStable
 * @param     int iLoop
 * @param     BOOL bDecisionEmitter
 * @param     STR_PULSE_TRAIN_SEG * pRefSeg
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-27, 18:44
 * @warning
 */
void CAnalPRI::GroupingJitterWithStable( STR_PULSE_TRAIN_SEG *pRefSeg, int iLoop, BOOL bDecisionEmitter )
{
    UINT j;
    BOOL bMakeEmitter;

    STR_EMITTER *pEmitter;

    STR_PULSE_TRAIN_SEG *pCmpSeg;

    // 규칙성 팔스열들이 Stagger 로 만들지도 못하고 Stable 도 만들지 못한 펄스열들은
    // Jitter로 병합을 한다.
    //-- 조철희 2005-10-28 17:26:30 --//
    if( pRefSeg->enPriType == _STABLE ) {
        bMakeEmitter = FALSE;

        pEmitter = &m_Emitter[m_uiCoEmitter];

        // 에미터 변수 초기화
        pEmitter->uiCoSeg = 0;
        pEmitter->uiSegIdx[pEmitter->uiCoSeg++] = iLoop;

        pCmpSeg = &m_pSeg[iLoop + 1];
        for( j = iLoop + 1 ; j < m_uiCoSeg ; ++j, ++pCmpSeg ) {
            if( pCmpSeg->enMark == CHECKED_SEG || pCmpSeg->enMark == DELETE_SEG ) {
                continue;
            }

            // 유사 펄스열이 있고 시간적으로 겹쳐져 있으면 STABLE 로 마킹하지 않는다.
            // 다음 GroupStagger 단계에서 Stagger 타입으로 만들기 위함이다.
            if( pCmpSeg->enPriType == _STABLE && CompFreq( pRefSeg, pCmpSeg ) == TRUE ) {
                if( CheckHarmonic( pRefSeg, pCmpSeg ) >= _spOne ) {
                    if( OverlappedSeg( pRefSeg, pCmpSeg ) == true ) {
                        pCmpSeg->enMark = CHECKED_SEG;
                        pEmitter->uiSegIdx[pEmitter->uiCoSeg++] = j;

                        bMakeEmitter = TRUE;
                    }
                }
            }
        }

        if( bMakeEmitter == TRUE ) {
            pRefSeg->enMark = CHECKED_SEG;

            MergePdwIndexInSeg( pEmitter );

            // 펄스열 로그 판단
            // 에미터로 생성 여부를 결정한다.
            if( bDecisionEmitter == TRUE || DecisionEmitter( pEmitter ) == TRUE ) {
                // 유사 PRI로 병합된 Stable 펄스열들에 대해서 다시 PRI 값을 재 산출해야 한다.
                // 어떤 신호에 대해서는 원 신호의 2배 PRI가 추출될 수 있고 유사 PRI 펄스열 끼리
                // 병합이 되면서 원 신호를 자세히 보면 원래의 PRI값을 찾을 수 있다.
                //-- 조철희 2005-10-28 15:19:10 --//
                pEmitter->mark = NORMAL_EMITTER;
                pEmitter->enSignalType = AnalSignalType( pEmitter );

                // PRI 범위 및 타입 결정
                CalcEmitterPri( pEmitter );
                pEmitter->enPRIType = _JITTER_RANDOM;

                // 주파수 범위 및 타입 결정
                CalcEmitterFrq( pEmitter );
                pEmitter->enFreqType = AnalFreqType( pEmitter );

                CalcEmitterPW( pEmitter );

                ++m_uiCoEmitter;
            }
            // UnknownExtract 펄스열에 삽입한다.
            else {
                // 에미터 실패된 펄스열들은 모두 삭제된 펄스열로 등록한다.
                // 추후에 펄스열들 끼리 병합을 수행한다.
                for( j = 0 ; j < pEmitter->uiCoSeg ; ++j )
                    m_pSeg[pEmitter->uiSegIdx[j]].enMark = DELETE_SEG;
            }
        }
    }

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::GroupingJitter
// 반환되는 형  : void
// 함 수 인 자  : BOOL fDecisionEmitter
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-12 14:13:13
//
//##ModelId=428832A302B5
void CAnalPRI::GroupingJitter( BOOL bDecisionEmitter )
{
    unsigned int i;

    STR_PULSE_TRAIN_SEG *pSeg;

    pSeg = & m_pSeg[m_uiAnalSeg];
    for( i=m_uiAnalSeg ; i < m_uiCoSeg ; ++i, ++pSeg ) {
        if( pSeg->enMark == CHECKED_SEG || pSeg->enMark == DELETE_SEG ) {
            continue;
        }

        /*! \bug  최대 에미터 개수 벗어날 조건 추가함.
            \date 2006-08-29 09:58:13, 조철희
        */
        if (m_uiCoEmitter >= MAX_AET) {
            break;
        }

        GroupingJitterWithJitter( pSeg, i, bDecisionEmitter );

        GroupingJitterWithStable( pSeg, i, bDecisionEmitter );

    }
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::GroupingUnknown
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-12 14:13:31
//
//##ModelId=428832A30297
void CAnalPRI::GroupingUnknown()
{
    // StaggerAnalysis();
    /*! \bug  최대 에미터 개수 벗어날 조건 추가함.
          \date 2006-08-29 09:58:13, 조철희
    */
    //if( m_CoEmitter >= MAX_AET )
    return;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::MakeDtoaHistogram
// 반환되는 형  : void
// 함 수 인 자  : PDWINDEX *pPdwIndex
// 함 수 인 자  : int count
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-12-21 11:54:49
//
void CAnalPRI::MakeDtoaHistogram( PDWINDEX *pPdwIndex, unsigned int uiCount, STR_MINMAX_TOA *pRange )
{
    unsigned int i;
    int dtoa_index;

    _TOA dtoa, toa, pre_toa;

    PDWINDEX *pIndex;

    if( uiCount <= 1 ) {
        _EQUALS3( m_DtoaHist.bin_range.iLow, m_DtoaHist.bin_range.iHgh, 0 )
    }
    else {
        // 메모리 초기화
        memset( & m_DtoaHist, 0, sizeof( m_DtoaHist) );

        m_DtoaHist.bin_range.iHgh = -1;
        m_DtoaHist.bin_range.iLow = 0xfffffff;

        pIndex = pPdwIndex;
        pre_toa = m_pTOA[ *pIndex++ ];
        //i = DTOA_BIN;
        for( i=1 ; i < uiCount; ++i ) {
            toa = m_pTOA[ *pIndex++ ];
            dtoa = toa - pre_toa;
            dtoa_index = F_UDIV( dtoa, DTOA_RES );

            pre_toa = toa;

            if( pRange != NULL && ( pRange->tMin > dtoa || pRange->tMax < dtoa ) ) {
                continue;
            }

            // DTOA_BIN 이내에 든 것만 히스토그램을 작성한다.
            if( DTOA_BIN > dtoa_index && dtoa_index >= 0 ) {
                ++ m_DtoaHist.hist[ dtoa_index ];
                m_DtoaHist.bin_range.iHgh = _max( m_DtoaHist.bin_range.iHgh, dtoa_index );
                m_DtoaHist.bin_range.iLow = _min( m_DtoaHist.bin_range.iLow, dtoa_index );
            }
        }

        m_DtoaHist.bin_count = DTOA_BIN - 1;
    }
}

/**
 * @brief     FindDwellLevel
 * @param     STR_EMITTER * pEmitter
 * @return    BOOL
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-08-20, 18:27
 * @warning
 */
BOOL CAnalPRI::FindDwellLevel( STR_EMITTER *pEmitter )
{
    unsigned int i;

    UINT *pSegIdx;
    STR_PULSE_TRAIN_SEG *pSeg;

    _TOA *pPeak;

    QSort( pEmitter->uiSegIdx, pEmitter->uiCoSeg, sizeof(UINT) );
    //, CAnalPRI::incSegPriMeanCompare );

    pSegIdx = pEmitter->uiSegIdx;
    pPeak = & m_DtoaHist.dtoa_peak[ 0 ];
    for( i=0 ; i < pEmitter->uiCoSeg ; ++i ) {
        pSeg = & m_pSeg[ *pSegIdx ];

        *pPeak = pSeg->pri.tMean;
        if( FindDtoa( *pPeak ) == FALSE ) {
            ++ pPeak;
            ++ m_DtoaHist.dtoa_peak_count;

            if( m_DtoaHist.dtoa_peak_count >= MAX_PEAK_DTOAHISTOGRAM-1 ) {
                Log( enError, "[W] 드웰 레벨 값을 확인하는 함수에서 에러 발생 !!" );
            }
        }
        ++ pSegIdx;

    }

    return m_DtoaHist.dtoa_peak_count >= _spTwo;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::FindDwellLevel
// 반환되는 형  : BOOL
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-12-21 14:10:43
//
BOOL CAnalPRI::FindDwellLevel()
{
    int i;
    UINT *puiPeak;
    PDWINDEX *pBin;

    m_DtoaHist.bin_peak_count = 0;

    puiPeak = & m_DtoaHist.bin_peak[ 0 ];
    pBin = & m_DtoaHist.hist[ m_DtoaHist.bin_range.iLow ];

    for( i=m_DtoaHist.bin_range.iLow ; i <= m_DtoaHist.bin_range.iHgh ; ++i ) {
        if( *pBin++ >= _spAnalMinPulseCount ) {
            *puiPeak = (unsigned int) ( ( i + 1 ) * DTOA_RES );
            if( FindBin( *puiPeak) == FALSE ) {
                ++ puiPeak;
                ++ m_DtoaHist.bin_peak_count;
            }
        }
    }

    return m_DtoaHist.bin_peak_count != 0;
}


/**
 * @brief		FindDtoa
 * @param		_TOA priMean
 * @return		BOOL
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/12/13 18:19:42
 * @warning		
 */
BOOL CAnalPRI::FindDtoa( _TOA priMean )
{
    int i;

    BOOL bRet=FALSE;
    _TOA *pPeak;

    pPeak = & m_DtoaHist.dtoa_peak[ 0 ];

    for( i=0 ; i < m_DtoaHist.dtoa_peak_count ; ++i ) {
        if( CheckHarmonic( *pPeak, priMean, ITOAusCNV((_TOA) 5) ) >= 1 ) {
            bRet = TRUE;
            break;
        }

        ++ pPeak;
    }

    return bRet;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::FindBin
// 반환되는 형  : BOOL
// 함 수 인 자  : UINT bin
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-12-21 18:04:12
//
BOOL CAnalPRI::FindBin( UINT bin )
{
    int i;
    UINT *pPeak;

    BOOL bRet=FALSE;

    pPeak = & m_DtoaHist.bin_peak[ 0 ];

    for( i=0 ; i < m_DtoaHist.bin_peak_count ; ++i ) {
        if( m_DtoaHist.bin_peak_count == MAX_PEAK_DTOAHISTOGRAM || CheckHarmonic( *pPeak, bin, DTOA_RES ) >= 1 ) {
            bRet = TRUE;
            break;
        }

        ++ pPeak;
    }

    return bRet;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::ExtractDwellPT
// 반환되는 형  : BOOL
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-12-22 09:16:31
//
BOOL CAnalPRI::ExtractDwellPT()
{
    int i;
    STR_PRI_RANGE_TABLE extRange;

    BOOL bRet=FALSE;

    //m_nAnalSeg = GetCoSeg();

    for( i=0 ; i < m_DtoaHist.dtoa_peak_count ; ++i ) {
        extRange.tMinPRI = ( m_DtoaHist.dtoa_peak[i] - ITOAusCNV(_TOA(5)) ) - ( STABLE_MARGIN );
        extRange.tMaxPRI = ( m_DtoaHist.dtoa_peak[i] + ITOAusCNV(_TOA(5)) ) + ( STABLE_MARGIN );
        bRet = ExtractDwellRefPT( & m_DwlSeg, & extRange );

        if( bRet == FALSE ) {
            break;
        }
    }
    //ExtractRefStable();

    //m_CoSeg = GetCoSeg();
    //PrintAllSeg();

    // 펄스열 추출 클래스의 m_nAlanSeg 값과 m_CoSeg 값을 동일하게 한다.
    // SetAnalSeg( m_CoSeg );

    return bRet;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::DwellAnalysis
// 반환되는 형  : BOOL
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-12-22 16:29:24
//
BOOL CAnalPRI::DwellAnalysis( STR_EMITTER *pEmitter )
{
    BOOL bRet=FALSE;

    //SaveEmitterPdwFile( pEmitter, 2000 );

    MakeDtoaHistogram( pEmitter->stPDW.pIndex, pEmitter->stPDW.uiCount, & pEmitter->stPRI );
    if( TRUE == FindDwellLevel(pEmitter) ) {
        // 펄스열 추출 클래스로 보내서
        // 가상 에미터로 추출된 펄스열을 제거하고
        // Dwell 값으로 재 추출한다.
        //DeleteAllSeg( pEmitter );
        if( TRUE == ExtractDwellPT() ) {
            memset( pEmitter->stPDW.pIndex, 0, sizeof(PDWINDEX)*m_uiMaxPdw );
            pEmitter->stPDW.uiCount = m_DwlSeg.pdw.uiCount;
            memcpy( pEmitter->stPDW.pIndex, m_DwlSeg.pdw.pIndex, sizeof(PDWINDEX)*m_DwlSeg.pdw.uiCount );
            // m_CoEmitter 값이 증가됨... 그래서 위에 m_CoEmitter 값을 end_emitter 에 보관함.
// 			pEmitter->seg_count = 0;
// 			for( i=m_nAnalSeg ; i < m_CoSeg ; ++i ) {
// 				pEmitter->seg_idx[ pEmitter->seg_count++ ] = i;
// 				MergePdwIndexInSeg( pEmitter );
// 			}

            pEmitter->mark = NORMAL_EMITTER;
            pEmitter->enSignalType = AnalSignalType( pEmitter );

            // 주파수 범위 및 타입 결정
            CalcEmitterFrq( pEmitter );
            pEmitter->enFreqType = AnalFreqType( pEmitter );

            // PRI 범위 및 타입 결정
            CalcEmitterPri( pEmitter );

            pEmitter->enPRIType = _DWELL;

            CalcEmitterPW( pEmitter );

            bRet = TRUE;

            // PRI 레벨 찾기
// 			if( TRUE == CalcPRILevel( pEmitter ) ) {
// 				pEmitter->framePri = m_pRefFramePri[0];
//
// 				pEmitter->pri_type = _DWELL;
//
// 				CalcEmitterPW( pEmitter );
//
// 				return TRUE;
// 			}
        }
        else {
            // 현재 Dwell로 의심한 에미터를 삭제 한다.
            pEmitter->mark = DELETE_EMITTER;
        }
    }

    return bRet;
}

/**
 * @brief     CalcPRILevel
 * @param     STR_EMITTER * pEmitter
 * @return    BOOL
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-14, 17:56
 * @warning
 */
BOOL CAnalPRI::CalcPRILevel( STR_EMITTER *pEmitter )
{
    bool bRet=FALSE;
    unsigned int uiCount;

    _TOA firstToa;
    _TOA refToa, preTOA, dTOA, refDtoa;

    PDWINDEX *pPdwIndex;

    STR_DWELL_LEVEL stDwellLevel;

    //count = pEmitter->pdw.count;

    // AddDwellLevel 관련 함수 초기화
    m_iCoDwellLevel = 0;

    preTOA = 0;
    uiCount = pEmitter->stPDW.uiCount;
    pEmitter->stPDW.pIndex[uiCount] = 0;
    pPdwIndex = pEmitter->stPDW.pIndex;
    firstToa = m_pTOA[ *pPdwIndex++ ];
    while( *pPdwIndex > 0 ) {
        refToa = m_pTOA[ *pPdwIndex++ ] - firstToa;
        refDtoa = ( refToa - preTOA );
        preTOA = refToa;

        if( *pPdwIndex == 0 ) {
            break;
        }

        // Step 1 : 첫번째 펄스열을 찾는다.
        stDwellLevel.iPulseCount1 = 0;
        do {
            refToa = m_pTOA[ *pPdwIndex++ ] - firstToa;
            dTOA = ( refToa - preTOA );

            preTOA = refToa;
            ++ stDwellLevel.iPulseCount1;
        }
        while( CompMeanDiff<_TOA>( refDtoa, dTOA, ITTOAusCNV(_DWELL_DTOA_MARGIN) ) == TRUE && *pPdwIndex > 0 );

        // Step 2 : 두번째 펄스열을 찾는다.
        if( *pPdwIndex > 0 && stDwellLevel.iPulseCount1 >= _DWELL_PULSECOUNT ) {
            stDwellLevel.bUsed = false;
            stDwellLevel.dtoa1 = refDtoa;
            _EQUALS3( stDwellLevel.dtoa2, refDtoa, dTOA )
            stDwellLevel.iPulseCount2 = 0;
            do {
                refToa = m_pTOA[ *pPdwIndex++ ] - firstToa;
                dTOA = ( refToa - preTOA );

                preTOA = refToa;
                ++ stDwellLevel.iPulseCount2;
            }
            while( CompMeanDiff<_TOA>( refDtoa, dTOA, ITTOAusCNV(_DWELL_DTOA_MARGIN) ) == TRUE && *pPdwIndex > 0 );

            if( stDwellLevel.iPulseCount2 >= _DWELL_PULSECOUNT ) {
                AddDwellLevel( & stDwellLevel );
            }

        }

        -- pPdwIndex;
        preTOA = m_pTOA[ *(pPdwIndex-1) ] - firstToa;

    }

    bRet = MakeDwellLevel( pEmitter );

    return bRet;

}

/**
 * @brief		MakeDwellLevel
 * @param		STR_EMITTER * pEmitter
 * @return		bool
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2022/01/03 14:38:55
 * @warning		
 */
bool CAnalPRI::MakeDwellLevel( STR_EMITTER *pEmitter )
{
    int i;
    bool bRet=false;

    STR_DWELL_LEVEL *pRefSTR_DWELL_LEVEL, *pCmpSTR_DWELL_LEVEL;

    if( m_iCoDwellLevel == 0 ) {
        pEmitter->uiStagDwellLevelCount = 0;
        bRet = true;
    }
    else if( m_iCoDwellLevel == 1 ) {
        pEmitter->uiStagDwellLevelCount = 2;
        pEmitter->tStaggerDwellLevel[0] = m_stDwellLevel[0].dtoa1;
        pEmitter->tStaggerDwellLevel[1] = m_stDwellLevel[0].dtoa2;
        bRet = true;
    }
    else {

        pRefSTR_DWELL_LEVEL = & m_stDwellLevel[0];
        pRefSTR_DWELL_LEVEL->bUsed = true;

        pCmpSTR_DWELL_LEVEL = & m_stDwellLevel[0];
        for( i=0 ; i < m_iCoDwellLevel ; ++i ) {
            if( pCmpSTR_DWELL_LEVEL->bUsed == false ) {

            }

            ++ pCmpSTR_DWELL_LEVEL;

        }
        bRet = true;
    }

    return bRet;
}

void CAnalPRI::AddDwellLevel( STR_DWELL_LEVEL *pSTR_DWELL_LEVEL )
{
    int i;
    bool bMatch=false;
    STR_DWELL_LEVEL *pstDwellLevel;

    //printf( "\n %d[us], %d->%d[us], %d" , TOAusCNV(pSTR_DWELL_LEVEL->dtoa1), pSTR_DWELL_LEVEL->iPulseCount1, TOAusCNV(pSTR_DWELL_LEVEL->dtoa2), pSTR_DWELL_LEVEL->iPulseCount2 );
    pstDwellLevel = & m_stDwellLevel[0];
    for( i=0 ; i < m_iCoDwellLevel ; ++i ) {
        if( CompMeanDiff<_TOA>( pstDwellLevel->dtoa1, pSTR_DWELL_LEVEL->dtoa1, ITTOAusCNV(_DWELL_DTOA_MARGIN) ) == TRUE &&
                CompMeanDiff<_TOA>( pstDwellLevel->dtoa2, pSTR_DWELL_LEVEL->dtoa2, ITTOAusCNV(_DWELL_DTOA_MARGIN) ) == TRUE ) {
            bMatch = true;
            break;
        }
    }

    if( bMatch == false ) {
        memcpy( & m_stDwellLevel[m_iCoDwellLevel], pSTR_DWELL_LEVEL, sizeof(STR_DWELL_LEVEL) );
        ++ m_iCoDwellLevel;
    }

}

/**
 * @brief		SortEmitter
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/12/13 18:07:18
 * @warning		
 */
void CAnalPRI::SortEmitter()
{
    unsigned int i, j;
    STR_EMITTER *pEmitter, *pEmitter2, *pFinalEmitter;

    _TOA iEmitterPriMean, iEmitterPriMean2;

    pEmitter = & m_Emitter[ m_uiAnalEmitter ];
    for( i=m_uiAnalEmitter ; i < m_uiCoEmitter ; ++i, ++ pEmitter ) {
        pEmitter2 = & m_Emitter[ i+1 ];
        pFinalEmitter = pEmitter;
        for( j=i+1; j < m_uiCoEmitter ; ++j, ++ pEmitter2 ) {
            iEmitterPriMean = GetMinPulseTrainMean( pEmitter );
            iEmitterPriMean2 = GetMinPulseTrainMean( pEmitter2 );
            if( iEmitterPriMean > iEmitterPriMean2 ) {
                pFinalEmitter = pEmitter2;
            }
        }

        SwapEmitter( & m_Emitter[ i ], pFinalEmitter );

    }

}

/**
 * @brief     GetMinPulseTrainMean
 * @param     STR_EMITTER * pEmitter
 * @return    _TOA
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-08-20, 18:27
 * @warning
 */
_TOA CAnalPRI::GetMinPulseTrainMean( STR_EMITTER *pEmitter )
{
    unsigned int i;
    UINT *pSegIdx;
    _TOA iMean;

    pSegIdx = pEmitter->uiSegIdx;
    iMean = m_pSeg[ *pSegIdx++ ].pri.tMean;
    for( i=1 ; i < pEmitter->uiCoSeg ; ++i ) {
        if( iMean > m_pSeg[ *pSegIdx ].pri.tMean ) {
            iMean = m_pSeg[ *pSegIdx ].pri.tMean;
        }
        ++ pSegIdx;
    }

    return iMean;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::DwellAnalysis
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-12-21 10:57:55
//
void CAnalPRI::DwellAnalysis()
{
    //bool bCheck;
    unsigned int ui, /*j , */ uiEndOfEmitter;
    STR_EMITTER *pEmitter; //, *pEmitter2;

    // SORT 정렬
    SortEmitter();

    // Dwell 로 타입으로 결정이 되면 DTOA 히스토그램을 이용해서 규칙성 펄스열을 찾고 그 PRI
    // 값을 근거로 규칙성 펄스열을 추출한다.
    //-- 조철희 2005-12-22 16:19:08 --//
    pEmitter = & m_Emitter[ m_uiAnalEmitter ];
    uiEndOfEmitter = m_uiCoEmitter;
    for( ui=m_uiAnalEmitter ; ui < uiEndOfEmitter; ++ui, ++ pEmitter ) {
        if( pEmitter->mark == DELETE_EMITTER ) {
            continue;
        }

        // 디버그
        // 확실한 Stagger 인 경우에만 정밀 분석해서 정확한 단을 찾는것이 나을수 있다.
        if( /*pEmitter->pri_type == _STABLE || */pEmitter->enPRIType == _STAGGER_DWELL ) {
//             // Dwell 값 초기화
//             pEmitter->iStagDwellElementCount = _spOne;
// 
//             if( pEmitter->pri_type == _STABLE ) {
//                 pEmitter->stag_dwell_element[0] = pEmitter->pri.mean;
//             }
//             else {
//                 pEmitter->stag_dwell_element[0] = pEmitter->pri.mean;
//             }
// 
//             bCheck = false;
//             pEmitter2 = & m_Emitter[ i+1 ];
//             for( j=m_nAnalEmitter+1 ; j < m_CoEmitter ; ++j, ++ pEmitter2 ) {
//                 if( pEmitter2->mark == DELETE_EMITTER )
//                     continue;
// 
//                 if( pEmitter2->pri_type == _STABLE || pEmitter2->pri_type == _STAGGER_DWELL ) {
//                     if( CheckContiStable( pEmitter, pEmitter2 ) == TRUE ) {
//                         MergeEmitter( pEmitter, pEmitter2, MERGE );
// 
//                         pEmitter->stag_dwell_element[pEmitter->iStagDwellElementCount] = pEmitter2->pri.mean;
//                         ++ pEmitter->iStagDwellElementCount;
// 
//                         pEmitter2->mark = DELETE_EMITTER;
//                         bCheck = true;
// 
//                     }
//                 }
// 
//             }

            DwellAnalysis( pEmitter );

//             if( bCheck == true || true ) {
//                 DwellAnalysis( pEmitter );
//             }
//             else {
//                 pEmitter->iStagDwellLevelCount = 0;
//                 pEmitter->iStagDwellElementCount = 0;
//             }
        }
    }
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::CheckContiStable
// 반환되는 형  : BOOL
// 함 수 인 자  : STR_EMITTER *pEmitter1
// 함 수 인 자  : STR_EMITTER *pEmitter2
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2013-12-04 13:41:45
//
BOOL CAnalPRI::CheckContiStable( STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2 )
{
    unsigned int i, j, k;

    UINT margin;

    BOOL bRet=FALSE;

    PDWINDEX *pIndex;
    _TOA last_toa;

    STR_PULSE_TRAIN_SEG *pSeg1, *pSeg2;

    for( i=0 ; i < pEmitter1->uiCoSeg ; ++i ) {
        pSeg1 = & m_pSeg[ pEmitter1->uiSegIdx[i] ];

        for( j=0 ; j < pEmitter2->uiCoSeg ; ++j ) {
            pSeg2 = & m_pSeg[ pEmitter2->uiSegIdx[j] ];

            margin = UMUL( ( pSeg1->pri.tMean + pSeg2->pri.tMean ) / 2, DWELL_PRI_MARGIN );

            //MergePdwIndexInSeg( pSeg1, pSeg2 );

            // CheckContiCountDTOA( m_pMergePdwIndex, margin );

            // DTOAHist();

            /*! \bug  PRI 평균값은 패턴인 경우 수집 시점에 따라서 평균치가 다르기 때문에 이를 중간값으로 수정함.
                                첫번째 펄스열 마지막 펄스가 두번째 펄스열에 있을 수 있기 때문에 마지막 펄스열을 비교로 찾는다.
                    \date 2019-07-24 14:22:32, 조철희
            */
            //last_toa = pSeg1->last_toa;
            if( pSeg1->pdw.uiCount-1 > 0 ) {
                pIndex = & pSeg1->pdw.pIndex[pSeg1->pdw.uiCount];
                last_toa = pSeg1->tLast;
                for( k=0 ; k < pSeg1->pdw.uiCount ; ++k ) {
                    -- pIndex;
                    last_toa = m_pTOA[*pIndex];

                    if( last_toa <= pSeg2->tFirst ) {
                        break;
                    }
                }

                if( k != pSeg1->pdw.uiCount && *pSeg1->pdw.pIndex != *pSeg2->pdw.pIndex &&
                    ( CompMeanDiff<_TOA>( last_toa, pSeg2->tFirst, margin ) || CompMeanDiff<_TOA>( pSeg1->tFirst, pSeg2->tLast, margin ) ) ) {
                    //MergeEmitter( pEmitter1, pEmitter2, MERGE );
                    //pEmitter2->mark = DELETE_EMITTER;

                    bRet = TRUE;
                    break;
                }
            }
        }

        if( bRet == TRUE ) {
            break;
        }

    }

    return bRet;

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::MergePdwIndexInSeg
// 반환되는 형  : void
// 함 수 인 자  : STR_PULSE_TRAIN_SEG *pSeg1
// 함 수 인 자  : STR_PULSE_TRAIN_SEG *pSeg2
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2013-12-05 20:31:32
//
void CAnalPRI::MergePdwIndexInSeg( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 )
{
    size_t szSize;

    szSize = pSeg1->pdw.uiCount + pSeg2->pdw.uiCount;

    // 데이터 초기화
    memset( m_pMergePdwIndex, 0, sizeof( PDWINDEX ) * m_uiMaxPdw );

    // PDW 인덱스 복사
    memcpy( m_pMergePdwIndex, pSeg1->pdw.pIndex, sizeof(PDWINDEX)*pSeg1->pdw.uiCount );
    memcpy( & m_pMergePdwIndex[pSeg1->pdw.uiCount], pSeg2->pdw.pIndex, sizeof(PDWINDEX)*pSeg2->pdw.uiCount );

    // PDW INDEX 순으로 정렬
    qsort( m_pMergePdwIndex, szSize, sizeof(PDWINDEX), incUSCompare );

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::StaggerAnalysis
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-12 19:32:38
//
//##ModelId=428832A30247
void CAnalPRI::StaggerAnalysis()
{
    unsigned int i;
    STR_EMITTER *pEmitter;

    pEmitter = & m_Emitter[ m_uiAnalEmitter ];
    for( i=m_uiAnalEmitter ; i < m_uiCoEmitter ; ++i, ++ pEmitter ) {
        if( pEmitter->mark == DELETE_EMITTER ) {
            continue;
        }

        // 디버그
        // 확실한 Stagger 인 경우에만 정밀 분석해서 정확한 단을 찾는것이 나을수 있다.
        switch( pEmitter->enPRIType ) {
            case _JITTER_RANDOM :
                // Auto-Correlation Function 으로 스태거 분석한다.
                if( TRUE == StaggerAnalysis( pEmitter ) ) {
                    MergePdwIndexInSeg( pEmitter );
                    CopySeg(pEmitter);
                }
                else {
//                     // 스태거로 분석되지 않은 지터 에미터의 PDW개수가 20개 미만이면 제거한다.
//                     if( _spAnalMinPulseJitterEmitter > pEmitter->stPDW.uiCount ) {
//                         pEmitter->mark = DELETE_EMITTER;
//                     }
                }
                break;

            case _STAGGER_DWELL :
				// Dwell 타입을 체크한다.
				/*
				if( FALSE == DwellAnalysis( pEmitter ) ) {
					// Stable N 개 펄스열로부터 스태거 분석이 실패가 되면,
					// 이 신호는 Jitter 0%로 분석된다. 그리고 이 신호를 엄밀히 살펴보면,
					// Stable 인것을 알수 있을 것이다.
					// 이러한 에미터는 버린다.
					// 아래 검증은 이러한 예외적인 에미터를 막기 위함이다.
					// 유사관계가 있는 N 개의 Stable 펄스열을 스태거 분석에서 실패하면 그 펄스열은 버린다.

				}
				*/
				pEmitter->enPRIType = _JITTER_RANDOM;

				// 규칙성 펄스열로써 Stagger 펄스열이 의심되기 때문에 그냥 스태거로 펄스열을 추출한다.
				if( FALSE == StaggerLevelAnalysis( pEmitter ) ) {
					pEmitter->mark = DELETE_EMITTER;
					// 김용준 수정
					// 스태거로 그룹핑되었다가 해제된 펄스열들이 다시 그룹핑될 수 있도록 초기화한다.
					InitSeg(pEmitter);
				}
				else {
					pEmitter->enPRIType = _STAGGER;
					CopySeg(pEmitter);
				}
				break;

            default:
                break;

        }

        MergePdwIndexInSeg( pEmitter );
    }
}

/**
 * @brief		InitSeg
 * @param		STR_EMITTER * pEmitter
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2022/01/03 17:23:28
 * @warning		
 */
void CAnalPRI::InitSeg(STR_EMITTER *pEmitter)
{
    unsigned int i;

    // 해당 에미터의 펄스열들을 전부 초기화한다.
    for( i=0 ; i < pEmitter->uiCoSeg ; i++ ) {
        m_pSeg[pEmitter->uiSegIdx[i]].enMark = NORMAL_SEG;
    }

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::PatternAnalysis
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-12 19:32:49
//
//##ModelId=428832A30233
void CAnalPRI::PatternAnalysis()
{
    unsigned int i, j;

    PDWINDEX *pPdwIndex;

    STR_EMITTER *pEmitter;

    pEmitter = & m_Emitter[ m_uiAnalEmitter ];
    for( i=m_uiAnalEmitter ; i < m_uiCoEmitter ; ++i, ++ pEmitter ) {
        /*! \bug  최대 에미터 개수 벗어날 조건 추가함.
            \date 2006-08-29 09:58:13, 조철희
        */
        if( m_uiCoEmitter >= MAX_AET ) {
            break;
        }

        if( pEmitter->mark == DELETE_EMITTER ) {
            continue;
        }

        // 주파수 패턴 분석
        if( pEmitter->stFreq.iType == _RANDOM_AGILE ) {
            // 데이터 변환
            /*! \bug  메인 펄스열을 근거로 해서 패턴 형태 및 주기를 분석한다.
                \date 2006-07-26 10:09:56, 조철희
            */
            pPdwIndex = m_pSeg[ pEmitter->uiMainSeg ].pdw.pIndex;
            m_uiCoData = m_pSeg[ pEmitter->uiMainSeg ].pdw.uiCount;
            for( j=0 ; j < m_uiCoData ; ++j ) {
                m_pDataX[j] = m_pTOA[ *pPdwIndex ];
                m_pDataY[j] = m_pFREQ[ *pPdwIndex ];
                ++ pPdwIndex;
            }

            pEmitter->fFreqPeriod = PatternAnalysis( pEmitter );
            if( pEmitter->fFreqPeriod > 0 ) {
                pEmitter->stFreq.iType = _PATTERN_AGILE;
                pEmitter->uiFreqPatternType = m_uiPatternType;
            }
        }

        // PRI 패턴 분석
        if( pEmitter->enPRIType == _JITTER_RANDOM || pEmitter->enPRIType == _JITTER_PATTERN ) {
            _TOA toaThreshold;
            STR_LOWHIGH_TOA pri;

            // 데이터 변환
            /*! \bug  메인 펄스열을 근거로 해서 패턴 형태 및 주기를 분석한다.
                \date 2006-07-26 10:09:56, 조철희
            */
            pPdwIndex = & m_pSeg[ pEmitter->uiMainSeg ].pdw.pIndex[1];
            m_uiCoData = m_pSeg[ pEmitter->uiMainSeg ].pdw.uiCount - 1;

            pri.tLow = m_pSeg[ pEmitter->uiMainSeg ].pri.tMin;
            pri.tHgh = m_pSeg[ pEmitter->uiMainSeg ].pri.tMax;

            toaThreshold = TDIV<_TOA>( pri.tHgh - pri.tLow, 2 );

            for( j=0 ; j < m_uiCoData ; ++j ) {
                _TOA dtoa;

                m_pDataX[j] = m_pTOA[ *pPdwIndex ];

                /*! \bug  DTOA 값을 계산해서 누락이 된다면 이전 값으로 한다.
                    \date 2006-07-25 12:14:32, 조철희
                */
                dtoa = m_pTOA[ *pPdwIndex ] - m_pTOA[ *(pPdwIndex-1) ];
                if( TRUE == CompMarginDiff<_TOA>( dtoa, pri.tLow, pri.tHgh, toaThreshold ) ) {
                    m_pDataY[j] = dtoa;
                }
                else {
                    if( j != 0 ) {
                        m_pDataY[j] = m_pDataY[j-1];
                    }
                    else {
                        m_pDataY[j] = m_pSeg[ pEmitter->uiMainSeg ].pri.tMean;
                    }
                }

                ++ pPdwIndex;
            }

            pEmitter->fPRIPeriod = PatternAnalysis( pEmitter );
            if( pEmitter->fPRIPeriod > 0 ) {
                pEmitter->enPRIType = _JITTER_PATTERN;
                pEmitter->uiPRIPatternType = m_uiPatternType;
#ifdef _MSC_VER
                PatternAnalysis( pEmitter );
#endif
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::CalcSamplingTime
// 반환되는 형  : void
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-11-04 18:11:13
//
void CAnalPRI::CalcSamplingTime( STR_EMITTER *pEmitter )
{
    _TOA spanTime;
    UINT sampleTimeByPulse;
    UINT sampleTimeByPri;

    STR_PRI pri;

    spanTime = m_pTOA[ pEmitter->stPDW.pIndex[ pEmitter->stPDW.uiCount-1 ] ] - m_pTOA[ *pEmitter->stPDW.pIndex ];

    // 샘플링 타임 계산
    sampleTimeByPulse = UDIV( spanTime, m_uiMaxPdw );

    MakePRIInfoFromSeg( & pri, pEmitter );

    /*! \bug  PRI 평균값은 패턴인 경우 수집 시점에 따라서 평균치가 다르기 때문에 이를 중간값으로 수정함.
        \date 2006-07-24 14:22:32, 조철희
    */
    // sampleTimeByPri = 5 * pri.mean;
    sampleTimeByPri = 2 * UDIV( pri.TMax+pri.TMin, 2 );

    /*! \bug  주파수 및 PRI에 대한 샘플링 시간은 수집 시간으로 결정한다.
        \date 2007-07-02 16:40:33, 조철희
    */
    if( sampleTimeByPulse < sampleTimeByPri ) {
        m_SamplingTime = sampleTimeByPri;
        // m_SamplingTime = sampleTimeByPulse;
    }
    else {
        m_SamplingTime = sampleTimeByPulse;
    }

    return;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::PatternAnalysis
// 반환되는 형  : float
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-11-04 17:58:11
//
float CAnalPRI::PatternAnalysis( STR_EMITTER *pEmitter )
{
    float fRet;

    // 샘플링 타임을 계산한다.
    CalcSamplingTime( pEmitter );

    // 수집한 PDW 데이터를 시간대 주파수로 샘플링 작업을 한다.
    SamplingProcess( pEmitter );

    ReplaceOffSampling();

    Interpolation();

    // ACF 연산을 쉽게 처리하기 위한 데이터 변환
    Normalize();

    // ACF 연산
    AutoCorerelation();

    // 주기 찾기
    FindPeriod();

    // 패턴형 찾기
    m_uiPatternType = HighIllustrationTest( pEmitter );

    //-- 조철희 2006-04-26 17:10:43 --//
    // 주파수 및 PRI 패턴 주기는 상한값을 갖게 되며 이상 값이 분석될 때는 무시한다.
    // 1초 이상인 놈은 버린다.
    if ( UDIV(m_Period, _spOneSec) >= 1 ) {
        fRet = -1;
    }
    else {
        fRet = m_Period;
    }

    return fRet;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CAnalPRI::HighIllustrationTest
        \author   조철희
        \param    pEmitter 인자형태 STR_EMITTER *
        \return   UINT
        \version  0.0.57
//! \date     2005-11-11 11:51:18, 2006-07-25 11:33:55
        \warning
*/
PATTERN_TYPE CAnalPRI::HighIllustrationTest( STR_EMITTER *pEmitter )
{
    PATTERN_TYPE uRet;

    if( m_Period < 0 ) {
        uRet = UNK;
    }

    // 샘플링 개수가 5개 미만이면 패턴 형태 판단은 취소한다.
    else if( m_CoSample < 5 ) {
        uRet = UNK;
    }
    else {
        // 주기를 찾았다 하더라도 Kurtosis 와 Skewness 를 구해서 패턴인가를 확인한다.
        KurtosisSkewness();
        // printf( "\n Skewness[%f], Kurtosis[%f]" , m_skewness, m_kurtosis );

        /*! \bug  skewness 는 절대치 값으로 비교해야 하기 때문에 abs() 함수를 추가함.
            \date 2008-01-17 09:48:28, 조철희
        */
        if( m_skewness > 1.0 || m_skewness < -1.0 ) {
            uRet = UNK;
        }
        else {
            // 패턴 분석
            /*! \todo  패턴 분석 모듈을 여기에 추가해서 패턴의 형태를 판단하게 한다. */

            // 2차 미분을 통해서 패텅 형태를 찾는다.
            // 패턴 형태는 사인형, 삼각-증가형, 삼각-감소형 그리고 Unknown 으로 구한다.

            // 샘플링 데이터를 근거로 2차 미분을 구한다.
            CalTwoPrime();

            PATTERN_TYPE saw_pattern_type;

            if( TRUE == CheckSawPattern( & saw_pattern_type ) ) {
                uRet = saw_pattern_type;
            }
            else {
                uRet = SINE;
            }
        }
    }

    return uRet;
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CAnalPRI::CheckSawPattern
//!	\author  조철희
//!	\param	 pSawPatternType	인자형태 int *
//!	\return	 BOOL
//! \version 1.0
//! \date		 2006-07-25 14:11:46
//! \warning
//
BOOL CAnalPRI::CheckSawPattern(PATTERN_TYPE *pSawPatternType )
{
    unsigned int i;
    int n_zero_crossing, co_dec, co_inc;

    int *p1PrimeData, *p2PrimeData;

    BOOL bRet=TRUE;

    UINT uiRatio;

    *pSawPatternType = UNK;

    _EQUALS4( n_zero_crossing, co_dec, co_inc, 0 )

    p1PrimeData = & m_p1PrimeData[1];
    p2PrimeData = & m_p2PrimeData[1];

    for( i=1 ; i < m_CoSample-1 ; ++i ) {
        /*! \bug  2차 미분에 대해서는 i는 2 이상인 것을 체크.
            \date 2007-08-07 18:56:52, 조철희
        */
        if( i >= 2 && TRUE == CompMeanDiff<_TOA>( *p2PrimeData, 0, ITOAusCNV((_TOA)2) /* 2*_spOneMicrosec */ ) ) {
            ++ n_zero_crossing;
        }

        if( *p1PrimeData < 0 ) {
            ++ co_dec;
        }
        else if( *p1PrimeData > 0 ) {
            ++ co_inc;
        }
        else {
        }

        ++ p1PrimeData;
        ++ p2PrimeData;
    }

    if( *p1PrimeData < 0 ) {
        ++ co_dec;
    }
    else {
        ++ co_inc;
    }

    uiRatio = UDIV( n_zero_crossing * 100, m_CoSample-2 );
    if(uiRatio >= THRESHOLD_SAW_PATTERN ) {
        if( co_dec > co_inc ) {
            uiRatio = UDIV( co_dec * 100, m_CoSample-1 );
            if(uiRatio > THRESHOLD_SAW_PATTERN ) {
#if defined(_ELINT_) || defined(_XBAND_)
#elif defined(_POCKETSONATA_)
                *pSawPatternType = SAW_INC;
#else
                int band=GetBand();
                if( band == BAND1 || band == BAND4 )
                    *pSawPatternType = SAW_DEC;
                else
                    *pSawPatternType = SAW_INC;
#endif
            }
            else {
                bRet = FALSE;
            }
        }
        else {
            uiRatio = UDIV( co_inc * 100, m_CoSample-1 );
            if(uiRatio > THRESHOLD_SAW_PATTERN ) {
#if defined(_ELINT_) || defined(_XBAND_)

#elif defined(_POCKETSONATA_)
                *pSawPatternType = SAW_DEC;

#else
                int band=GetBand();
                if( band == BAND1 || band == BAND4 )
                    *pSawPatternType = SAW_INC;
                else
                    *pSawPatternType = SAW_DEC;
#endif
            }
            else {
                bRet = FALSE;
            }
        }
        
    }
    else {
        bRet = FALSE;
    }

    return bRet;
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CAnalPRI::CheckSinePattern
//!	\author  조철희
//!	\return	 UINT
//! \version 1.0
//! \date		 2006-07-25 13:47:40
//! \warning
//
UINT CAnalPRI::CheckSinePattern()
{
    // UINT diff;

    // diff = CalPrimeDifference();

    /*! \todo	SINE 형 패턴 검증은 주기성만 있으면 SINE 형으로 한다. */
    return SINE;

    // total_diff 값이 차이의 제곱의 평균이기 때문에 임계값은 제곱으로 정한다.
    /*
    if( diff > 16 )
        return UNK;
    else
        return SINE;
    */
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CAnalPRI::CalPrimeDifference
//!	\author  조철희
//!	\return	 UINT
//! \version 1.0
//! \date		 2006-07-25 10:01:50
//! \warning
//
UINT CAnalPRI::CalPrimeDifference()
{
    unsigned int i;
    int *pPrimeData, *pSamplingData;

    int diff;
    UINT uiTotalDiff;

    uiTotalDiff = 0;

    pPrimeData = & m_p2PrimeData[1];
    pSamplingData = & m_pSampleData[1];
    for( i=1 ; i < m_CoSample-1 ; ++i ) {
        diff = *pPrimeData - *pSamplingData;
        uiTotalDiff += (unsigned int) ( diff * diff );
    }
    uiTotalDiff = UDIV( uiTotalDiff, ( m_CoSample - 2 ) );

    return uiTotalDiff;
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CAnalPRI::CalTwoPrime
//!	\author  조철희
//!	\return	 void
//! \version 1.0
//! \date		 2006-07-24 17:30:29
//! \warning
//
void CAnalPRI::CalTwoPrime()
{
    unsigned int i;
    int *p1PrimeData, *p2PrimeData;
    int *piSamplingData, *pi1SamplingData, *pi2SamplingData, *pi3SamplingData;

    piSamplingData = & m_pSampleData[2];
    pi1SamplingData = & m_pSampleData[2];
    pi2SamplingData = & m_pSampleData[1];
    pi3SamplingData = & m_pSampleData[0];

    m_p1PrimeData[0] = 0;
    m_p1PrimeData[1] = m_pSampleData[1] - m_pSampleData[0];

    m_p2PrimeData[0] = 0;
    m_p2PrimeData[1] = 0;

    p1PrimeData = & m_p1PrimeData[2];
    p2PrimeData = & m_p2PrimeData[2];
    for( i=2 ; i < m_CoSample-2 ; ++i ) {
        *p1PrimeData++ = *pi1SamplingData - *pi2SamplingData;
        *p2PrimeData++ = -( 2 * *pi2SamplingData ) + *pi1SamplingData + *pi3SamplingData;

        ++ piSamplingData;
        ++ pi1SamplingData;
        ++ pi2SamplingData;
        ++ pi3SamplingData;
    }
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 통계 함수인 Kurtosis 함수와 Skewness 함수를 구한다.
//!	\author  조철희
//!	\return	 void
//! \version 1.0
//! \date		 2006-05-15 17:55:29
//! \warning
//
void CAnalPRI::KurtosisSkewness()
{
    unsigned int i;

    UINT uiCount;
    double mds;
    double A, B, B3, B4, C, N;

    UINT uiMean;
    float sdevY;

    uiMean = UMUL( IMeanInArray( m_pSampleData, m_CoSample ), 1.0 );

    //sdevY = ISDevInArray( m_pSampleData, m_CoSample, uiMean);
    sdevY = SDevInArray<int>(m_pSampleData, m_CoSample, (float) uiMean );

    if( IS_ZERO(sdevY) == true ) {
        _EQUALS3( m_kurtosis, m_skewness, 5000.0 )
    }
    else {
        N = m_CoSample;
        A = ( N * ( N + 1 ) ) / ( ( N - 1 ) * ( N - 2 ) * ( N - 3 ) );
        C = ( 3 * ( N - 1 ) * ( N - 1 ) ) / ( ( N - 2 ) * ( N - 3 ) );

        _EQUALS3( B3, B4, 0. )

        uiCount = m_CoSample;
        for( i=0 ; i < uiCount; ++i ) {
            mds = (double) m_pSampleData[i] - uiMean;
            B = mds * mds * mds;

            B3 += ( B / sdevY );
            B4 += ( ( B * mds ) / sdevY );
        }

        m_kurtosis = (float) ( ( A * B4 ) - C );
        m_skewness = (float) ( B3 / N );
    }

    return;
}


//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::FindPeriod
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-11-07 13:39:51
//
void CAnalPRI::FindPeriod()
{
    unsigned int i, k;

    float *pAcf;
    float	maxPeak;

    unsigned int minPeriod;

    minPeriod = 1;

    maxPeak = 1.0;			// debug, 00-07-27 15:53:42
    pAcf = & m_pAcf[minPeriod];

    if( m_CoAcf >= MIN_CO_ACF+minPeriod ) {
        k = 0;
        m_coCanPeak = 0;
        for( i=minPeriod ; i < m_CoAcf-2 ; ++i ) {
            if( m_coCanPeak < m_uiMaxPdw &&
                *pAcf > 0 && ( *(pAcf-2) <= *(pAcf-1) && *(pAcf-1) <= *pAcf &&
                *pAcf >= *(pAcf+1) && *(pAcf+1) >= *(pAcf+2) ) ) {
                /*! \bug  ACF 값은 일정 값보다 커야 한다. 최소값은 0.2로 정했다.
                    \date 2006-07-24 14:37:23, 조철희
                */
                // 이전에는 0.4 로 정했는데 반복 파형이 3개 미만일 때 이보다 작은값을 산출할 수 있다.
                /* 상한 값보다 큰 값을 기준으로 Peak 값을 찾는다.	*/

                if( *pAcf < maxPeak ) {				// debug, 00-09-01 12:10:39
                    k = i;										// toa index
                    maxPeak = *pAcf;

                    m_pCanPeak[ m_coCanPeak ] = i;
                    ++ m_coCanPeak;
                }
            }

            ++ pAcf;
        }

        m_Period = -1.0;
        if( k != 0 ) {
            /*!
                    \bug  최소 피크 개수를 2개 이상으로 수정했다.
                                wm28_수원함.pdw 를 수정함.
                \date 2006-07-24 14:17:49, 조철희
            */

            /*!
                    \bug  최소 피크 개수를 3개 이상으로 한다.
                \date 2006-05-12 13:38:40, 조철희
            */
            if( m_coCanPeak >= 2 ) {
                //-- 조철희 2006-04-25 19:41:36 --//
                if( m_pAcf[ m_pCanPeak[0] ] < 0.4 ) {
                    //return;
                }

                else {
                    bool bRet=true;

                    // 주기 반복성 체크해서 존재해야 주기값을 인정한다.
                    for( i=1 ; i < m_coCanPeak ; ++i ) {
                        /*! \bug  ACF 값으로 차이값에 대한 가중치를 정해서 한다.
                                  즉, ACF 값이 0.2보다 작으면 오차를 크게 해서 비교하고
                                  ACF 값이 0.2보다 크면 오차를 작게 해서 비교한다.
                            \date 2006-07-24 16:23:29, 조철희
                        */
                        _TOA i_acf, iminus1_acf;
                        _TOA diff_iacf;

                        i_acf = m_pCanPeak[i];
                        iminus1_acf = m_pCanPeak[i-1];
                        diff_iacf = i_acf - iminus1_acf;
                        if( m_pAcf[ i_acf ] >= 0.2 && m_pAcf[ iminus1_acf ] >= 0.2 ) {
                            if( TRUE != CompMeanDiff<_TOA>( diff_iacf, m_pCanPeak[0], 2 ) ) {
                                bRet = false;
                                break;
                            }
                        }
                        else {
                            /*! \bug  ACF 오차는 멀어질수록 오차가 크기 때문에 이를 고려해서
                                      오차값을 7 대신에 4+(2*i) 로 수정함.
                                \date 2006-08-16 20:31:52, 조철희
                            */
                            _TOA toaThreshold;

                            toaThreshold = 3 + TMUL<_TOA>( 3, i );
                            if( diff_iacf >= 7 && TRUE != CompMeanDiff<_TOA>( diff_iacf, m_pCanPeak[0], toaThreshold ) ) {
                                bRet = false;
                                break;
                            }
                        }
                    }

                    if( bRet == true ) {
                        m_Period = FMUL( m_pCanPeak[0], m_SamplingTime );
                    }
                }

            }

            //-- 조철희 2006-01-09 14:39:46 --//
            // m17.npw 파일에서 잘못된 지터 신호인데 패턴 신호로 분석됨.
            // m_coCanPeak 가 1개로 판단하기에는 너무 부족하다고 생각함.
            // 스캐거 판단일 때는 가능하지만...
            // m28.npw 파일에서는 한 주기가 안됨.
    //         else if( m_coCanPeak == 2 ) {
    //             // 한개의 피크가 분석이 되면 시간 차원에서 주기를 체크해서
    //             // 주기가 존재하는지를 검증한다.
    //             m_Period = FMUL( k, m_SamplingTime );
    //             m_Period = -1.0;
    //         }
            else {
                // 피크 개수가 1개 이면, 무조건 패턴 주기 값은 못 찾은 것으로 한다.
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::AutoCorerelation
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-11-07 11:33:29
//
void CAnalPRI::AutoCorerelation()
{
    unsigned int i, j;

    float	refAcf;

    float	*pAcf;

    int *pxd1, *pxd2;

    memset( m_pAcf, 0, sizeof( float ) * m_uiMaxPdw );

    // pAcf = & m_Acf[0];
    m_CoAcf = m_CoSample;
    pxd1 = & m_pSampleData[0];
    for( i=0 ; i < m_CoSample ; ++i, ++pxd1 ) {
        pxd2 = & m_pSampleData[i];
        if( pxd2 != NULL ) {
            pAcf = & m_pAcf[0];
            for( j=i ; j < m_CoSample ; ++j ) {
                *pAcf += ( *pxd1 * *pxd2++ );
                ++ pAcf;
            }
        }
        else {

        }
    }

    refAcf = m_pAcf[0];
    pAcf = & m_pAcf[1];
    if( IS_NOT_ZERO( refAcf ) == true ) {
        for( i=1 ; i < m_CoAcf ; ++i ) {
            *pAcf++ /= refAcf;
        }
    }
    else {
        for( i=1 ; i < m_CoAcf ; ++i ) {
            *pAcf++ = 1 - FDIV( i, m_CoAcf );
        }
    }

    m_pAcf[0] = 1.0;

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::Normalize
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-11-07 11:05:58
//
void CAnalPRI::Normalize()
{
    unsigned int i;
    int iMean;

    int *pDataIndex;

    pDataIndex = & m_pSampleData[0];

    iMean = (int) ( MeanInArray( (UINT *) m_pSampleData, m_CoSample ) + 0.5 );

    for( i=0 ; i < m_CoSample ; ++i ) {
        if( pDataIndex != NULL ) {
            *pDataIndex = *pDataIndex - (int) iMean;
            ++ pDataIndex;
        }
    }

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::ReplaceOffSampling
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-11-09 16:06:28
//
void CAnalPRI::ReplaceOffSampling()
{
    unsigned int i, j;

    UINT missing;
    int preSampleData;

    missing = 0;

    /*! \bug  preSampleData 초기값을 저장한다.
        \date 2008-06-21 13:48:07, 조철희
    */
    preSampleData = 0;

    if( m_pSampleData != NULL ) {
        for( i=0 ; i < m_CoSample ; ++i ) {
            if( m_pSampleData[i] > 0 ) {
                preSampleData = m_pSampleData[0];
                break;
            }
        }

        // -1 로 된 샘플링 데이터를 교체한다.
        for( i=0 ; i < m_CoSample ; ++i ) {
            if( m_pSampleData[i] == -1 ) {
                ++ missing;
                if( missing >= CO_OFF_SAMPLING_THRESHOLD ) {
                    for( j=i ; j < m_CoSample && m_pSampleData[j] == -1 ; ++j )
                        m_pSampleData[j] = preSampleData;

                    // i 번째 루프를 정상 이동시키기 위한 설정
                    if( j != 0 ) {
                        i = j - 1;
                    }
                    // i 번째 루프를 정상 이동시키기 위한 설정
                    else {
                        i = 0;
                        WhereIs;
                    }

                    missing = 0;
                }
                else {
                    m_pSampleData[i] = preSampleData;
                }
            }
            else {
                missing = 0;
                preSampleData = m_pSampleData[i];
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CAnalPRI::Interpolation
//!	\author  조철희
//!	\return	 void
//! \version 1.0
//! \date		 2006-06-07 10:57:08
//! \warning
//
void CAnalPRI::Interpolation()
{
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::SamplingProcess
// 반환되는 형  : void
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-11-07 17:23:12
//
void CAnalPRI::SamplingProcess( STR_EMITTER *pEmitter )
{
    unsigned int i;
    UINT inpulse;
    _TOA sumY, maxY;
    _TOA *psx;
    int *psy;

    _TOA dShgh;

    UINT index;

    // Search maximum and minimum X of pulse train
    // SearchLowHghInArray( pPara, pEmitter->pdw.count, & gpScanPt->_pa );

    // 샘플링 데이터 초기화
    memset( m_pSampleData, 0, sizeof( int ) * m_uiMaxPdw );
    memset( m_pSampleToa, 0, sizeof( _TOA ) * m_uiMaxPdw );

    index = 0;

    m_CoSample = 0;
    psx = m_pSampleToa;
    psy = m_pSampleData;

    _EQUALS3( sumY, maxY, 0 )
    
    inpulse = 0;
    dShgh = m_pDataX[ 0 ] + m_SamplingTime;

    for( i=0 ; i < m_uiCoData ; ) {
        if( m_pDataX[ index ] < dShgh ) {
            sumY += m_pDataY[ index ];                    // Sampling 구간내의 PA의 전체 합
            if( maxY < m_pDataY[ index ] ) {                // Sampling 구간내의 PA의 최대 합
                maxY = m_pDataY[ index ];
            }

            ++ inpulse;
            ++ index;

            ++i;
        }
        else {
            if( m_CoSample >= m_uiMaxPdw ) {
                //printf( "\n Over Sample[%d]" , m_CoSample );
                //WhereIs;
                break;
            }

            if( psx != NULL ) {
                *psx = dShgh - m_SamplingTime;
            }

            if( psy != NULL ) {
                if( inpulse != 0 ) {
                    *psy = (int) UDIV( sumY, inpulse );       // Sampling 구간내의 평균치로 계산
                    // *psy = maxY;                    	// Sampling 구간내의 최대치로 계산
                    // preY = *psy;
                }
                else {
                    *psy = - 1;					// marking none sampling pulse
                    // *psy = _spZero;						// marking none sampling pulse
                }
            }

            dShgh += m_SamplingTime;

            ++ psx;
            ++ psy;
            _EQUALS3( sumY, maxY, 0 )
            
            inpulse = 0;

            ++ m_CoSample;
        }
    }

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::AnalSignalType
// 반환되는 형  : UINT
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-13 16:08:41
//
//##ModelId=428832A301E3
enSIGNAL_TYPE CAnalPRI::AnalSignalType( STR_EMITTER *pEmitter )
{
    unsigned int i;
    STR_PULSE_TRAIN_SEG *pSeg;

    enSIGNAL_TYPE enSiganlType=ST_NORMAL_PULSE;

    if( pEmitter->uiCoSeg == 0 ) {
        printf( "\n [W] Invalid emitter type !" );
        WhereIs;
    }
    else {
        pSeg = & m_pSeg[ pEmitter->uiSegIdx[0] ]; 
        if( m_pSTAT[ pSeg->pdw.pIndex[0] ] == STAT_NORMAL ) {

#if defined(_ELINT_) || defined(_XBAND_)

#elif defined(_POCKETSONATA_)

#else
            _TOA mean=0;
            for( i=0 ; i < pEmitter->uiCoSeg ; ++i ) {
                //STR_PULSE_TRAIN_SEG *pInSeg;

                //pInSeg = & m_pSeg[ pEmitter->seg_idx[i] ];
                mean += m_pSeg[pEmitter->uiSegIdx[i]]->pri.tMean;
            }

            mean = UDIV( mean, pEmitter->uiCoSeg );

            if( mean <= (_TOA) MIN_PRI ) {
                enSiganlType = ST_HIGHPRF;
            }
            else {
                //enSiganlType = ST_NORMAL_PULSE;
            }
#endif

        }

        else if( m_pSTAT[ pSeg->pdw.pIndex[0] ] == STAT_CW ) {
            for( i=1 ; i < pEmitter->uiCoSeg ; ++i ) {
                STR_PULSE_TRAIN_SEG *pSeg;

                pSeg = & m_pSeg[ pEmitter->uiSegIdx[i] ];
                if( m_pSTAT[ pSeg->pdw.pIndex[0] ] != STAT_CW ) {
                    printf( "\n Invalid Pulse type[%d] !" , i );
                    WhereIs;
                }
            }
            enSiganlType = ST_CW;
        }

        else {
        }

#if defined(_ELINT_) || defined(_XBAND_)
#elif defined(_POCKETSONATA_)
#else
        else if( STAT[ pSeg->pdw.pIndex[0] ] == PDW_FMOP ) {
            for( i=0 ; i < pEmitter->uiCoSeg ; ++i ) {
                STR_PULSE_TRAIN_SEG *pSeg;

                pSeg = & m_pSeg[ pEmitter->uiSegIdx[i] ];
                if( STAT[ pSeg->pdw.pIndex[0] ] != PDW_FMOP ) {
                    printf( "\n Invalid Pulse type[%d] !" , i );
                    WhereIs;
                }
            }
            enSiganlType = ST_FMOP;
        }
        else if( STAT[ pSeg->pdw.pIndex[0] ] == PDW_FMOP ) {
            for( i=1 ; i < pEmitter->uiCoSeg ; ++i ) {
                STR_PULSE_TRAIN_SEG *pSeg;

                pSeg = & m_pSeg[ pEmitter->uiSegIdx[i] ];
                if( STAT[ pSeg->pdw.pIndex[0] ] != PDW_FMOP ) {
                    printf( "\n Invalid Pulse type[%d] !" , i );
                    WhereIs;
                }
            }
            enSiganlType = ST_CW_FMOP;
        }
        else if( STAT[ pSeg->pdw.pIndex[0] ] == PDW_CW_FMOP ) {
            for( i=1 ; i < pEmitter->uiCoSeg ; ++i ) {
                STR_PULSE_TRAIN_SEG *pSeg;

                pSeg = & m_pSeg[ pEmitter->uiSegIdx[i] ];
                if( STAT[ pSeg->pdw.pIndex[0] ] != PDW_CW_FMOP ) {
                    printf( "\n Invalid Pulse type[%d] !" , i );
                    WhereIs;
                }
            }
            enSiganlType = ST_CW_FMOP;
        }
        else if( STAT[ pSeg->pdw.pIndex[0] ] == PDW_SHORTP ) {
            for( i=1 ; i < pEmitter->uiCoSeg ; ++i ) {
                STR_PULSE_TRAIN_SEG *pSeg;

                pSeg = & m_pSeg[ pEmitter->uiSegIdx[i] ];
                if( STAT[ pSeg->pdw.pIndex[0] ] != PDW_SHORTP ) {
                    printf( "\n Invalid Pulse type[%d] !" , i );
                    WhereIs;
                }
            }
            enSiganlType = ST_SHORT;
        }
        else {
            for( i=1 ; i < pEmitter->uiCoSeg ; ++i ) {
                STR_PULSE_TRAIN_SEG *pSeg;

                pSeg = & m_pSeg[ pEmitter->uiSegIdx[i] ];
                if( STAT[ pSeg->pdw.pIndex[0] ] != ST_ALL ) {
                    printf( "\n Invalid Pulse type[%d] !" , i );
                    WhereIs;
                }
            }
            enSiganlType = ST_ALL;
        }
#endif

    }

    return enSiganlType;

}

//////////////////////////////////////////////////////////////////////
//
//! \brief    주파수 형태를 판단하고 고정형 또는 랜덤형인지를 기록한다.
//! \author   조철희
//! \param    pEmitter 인자형태 STR_EMITTER *
//! \return   UINT
//! \version  0.0.1
//! \date     2005-05-13 16:16:44
//! \warning
//
enFREQ_TYPE CAnalPRI::AnalFreqType(STR_EMITTER *pEmitter)
{
    int coOkPdw = 0;
    int freqCenter;
    int threshold;

    UINT ui, uiCount;
    PDWINDEX *pPdwIndex;

    pEmitter->iCoHoppingLevel = 0;
    if( pEmitter->uiCoSeg == 0 ) {
        printf( "\n [W] 잘못된 주파수 형태입니다. !" );
        WhereIs;
        pEmitter->stFreq.iType = _FIXED;
    }
    

    // +-5 MHz 이하인 PDW개수가 전체 수집 개수의 95% 이하이면, 주파수 고정으로 결정한다.
#if defined(_ELINT_) || defined(_XBAND_)
    threshold = IFRQMhzCNV( 0, 5 );
#elif _POCKETSONATA_
    threshold = I_IFRQCNV( 0, 5 );

#else
    STR_PULSE_TRAIN_SEG *pSeg = & m_pSeg[ pEmitter->uiSegIdx[0] ];

    int first_pdw_index = pSeg->pdw.pIndex[0];
    int band = m_pBAND[ first_pdw_index ];
    threshold = abs( (int) C_UDIV( FIXED_FREQ_THRESHOLD, gFreqRes[band+1].fRes ) );
#endif

    // freqCenter = UDIV( pSeg->freq.max+pSeg->freq.min, 2 );
    freqCenter = pEmitter->stFreq.iMean;
    pPdwIndex = pEmitter->stPDW.pIndex;
    uiCount = pEmitter->stPDW.uiCount;
    for( ui=0 ; ui < uiCount; ++ui ) {
        UINT uiFreq;

        uiFreq = m_pFREQ[ *pPdwIndex++ ];
        if( CompMeanDiff<UINT>( freqCenter, (int) uiFreq, threshold ) == TRUE ) {
            ++ coOkPdw;
        }
    }

    // 주파수 변화폭 형태를 기록한다.
    //-- 조철희 2005-07-14 19:59:11 --//
    UINT ratio=UDIV( 100 * coOkPdw, uiCount);
    if( ratio >= FIXED_MATCH_RATIO ) {
        pEmitter->stFreq.iType = _FIXED;
    }
    else {
        // 호핑 레벨값 초기화
        pEmitter->iCoHoppingLevel = 0;

        /*! \bug  Hopping 체크를 해서 주파수 Hooping 형태를 기록한다.
            \date 2008-10-30 15:02:52, 조철희
        */
        if( TRUE == IsFreqHopping( pEmitter ) ) {
            pEmitter->stFreq.iType = _HOPPING;
            CalHopLevel( pEmitter );
        }
        else {
            pEmitter->stFreq.iType = _RANDOM_AGILE;
        }
    }

    return (enFREQ_TYPE) pEmitter->stFreq.iType;

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::MergePdwIndexInSeg
// 반환되는 형  : void
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-17 19:43:35
//
//##ModelId=428C21350192
void CAnalPRI::MergePdwIndexInSeg(STR_EMITTER *pEmitter)
{
    unsigned int i, j, max_count_compare=0;
    unsigned int uiCount, index;
    PDWINDEX *pSegPdwIndex, *pEmitterPdwIndex;
    PDWINDEX *pMergePdwIndex;
    STR_PULSE_TRAIN_SEG *pSeg;

    //pEmitter->pdw.count = 0;
    memset( m_pMergePdwIndex, 0, sizeof( PDWINDEX ) * m_uiMaxPdw );
    for( i=0 ; i < pEmitter->uiCoSeg ; ++i ) {
        pSeg = & m_pSeg[ pEmitter->uiSegIdx[i] ];
        uiCount = pSeg->pdw.uiCount;

        // memcpy( m_pMergePdwIndex+pEmitter->pdw.count, pSeg->pdw.pIndex, sizeof( PDWINDEX ) * pSeg->pdw.count );
        index = 0;
        pSegPdwIndex = pSeg->pdw.pIndex;
        for( j=0 ; j < uiCount; ++j ) {
            index = *pSegPdwIndex++;
            m_pMergePdwIndex[index] = 1;
        }

        /*! \bug  아래 비교 범위를 max() 값으로 찾아내서 비교 건수를 줄임.
            \date 2008-11-19 10:40:46, 조철희
        */
        max_count_compare = _max( max_count_compare, index );
    }

    pEmitterPdwIndex = pEmitter->stPDW.pIndex;
    pMergePdwIndex = m_pMergePdwIndex;
    uiCount = 0;
    for( i=0 ; i <= max_count_compare && i < (int) m_uiMaxPdw ; ++i ) {
        if( *pMergePdwIndex++ == 1 ) {
            pEmitterPdwIndex[uiCount] = i;
            ++uiCount;
        }
    }

    pEmitter->stPDW.uiCount = uiCount;

    // 에미터의 펄스열 SEG 중에서 주요한 SEG를 선택한다.
    SelectMainSeg( pEmitter );

    /* Sort remaining args using Quicksort algorithm: */
    // qsort( pEmitter->pdw.pIndex, (size_t) pEmitter->pdw.count, sizeof( PDWINDEX ), pdwindexCompare );
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    PRI 하모닉 관계와 펄스폭 관계를 체크해서 비교한다.
//! \author   조철희
//! \param    pEmitter1 인자형태 STR_EMITTER *
//! \param    pEmitter2 인자형태 STR_EMITTER *
//! \return   UINT
//! \version  1.37
//! \date     2006-08-29 14:03:11
//! \warning
//
UINT CAnalPRI::CheckHarmonicPW( STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2 )
{
    //int nHarmonic;
    UINT uRet;

    uRet = CheckHarmonic( pEmitter1, pEmitter2 );
    if( uRet >= 2 ) {
        if( CheckPW( pEmitter1, pEmitter2 ) == TRUE ) {
            // uRet = nHarmonic;
        }
        else {
            uRet = 0;
        }
    }

    return uRet;
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CAnalPRI::CheckPW
//! \author   조철희
//! \param    pEmitter1 인자형태 STR_EMITTER *
//! \param    pEmitter2 인자형태 STR_EMITTER *
//! \return   BOOL
//! \version  1.37
//! \date     2006-09-13 13:40:49
//! \warning
//
BOOL CAnalPRI::CheckPW( STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2 )
{
    if( 0 != CalOverlapSpace<_TOA>( pEmitter1->stPW.iMax, pEmitter1->stPW.iMin, pEmitter2->stPW.iMax, pEmitter2->stPW.iMin ) )
        return TRUE;
    else
        return FALSE;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::CheckHarmonic
// 반환되는 형  : UINT
// 함 수 인 자  : STR_EMITTER *pEmitter1
// 함 수 인 자  : STR_EMITTER *pEmitter2
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-06-08 11:28:04
//
//##ModelId=42AF7FEF00D5
UINT CAnalPRI::CheckHarmonic(STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2)
{
    UINT uiRet=0;
    STR_PULSE_TRAIN_SEG *pSeg1, *pSeg2;

    pSeg1 = & m_pSeg[ pEmitter1->uiMainSeg ];
    pSeg2 = & m_pSeg[ pEmitter2->uiMainSeg ];

    if( pEmitter1->enPRIType == _STABLE && pEmitter2->enPRIType == _STAGGER ) {
        uiRet = CheckHarmonic( pEmitter2->tFramePri, pSeg1->pri.tMean );
    }
    else if( pEmitter1->enPRIType == _STAGGER && pEmitter2->enPRIType == _STABLE ) {
        uiRet = CheckHarmonic( pEmitter1->tFramePri, pSeg2->pri.tMean );
    }
    else if( pEmitter1->enPRIType == _JITTER_RANDOM && pEmitter2->enPRIType == _JITTER_RANDOM ) {
        uiRet = CheckHarmonic( pSeg1, pSeg2 );
    }
    else if( ( pEmitter1->enPRIType == _STABLE && pEmitter2->enPRIType == _JITTER_RANDOM ) ||
                   ( pEmitter1->enPRIType == _JITTER_RANDOM && pEmitter2->enPRIType == _STABLE ) ) {
        /*! \bug  Jitter와 Stable 비교는 안되는 것으로 한다.
            \date 2006-06-02 09:21:27, 조철희
        */
        /* \bug  PRI 형태가 다르더라도 PRI 범위와 PRI 평균값이 일치하면 일치하는 것으로 리턴한다.
                            예를 들어서, D:\RSA-TFT\소나타 ES TFT\해상 신호\A06_9381MHz-J483\jiter_onelobe.pdw 에서
                            분석하게 되면 Stable 199(197,199) 와 Jitter 197(195,199)가 분석된다.
                            이를 방비하기 위함이다.
            \date 2006-06-29 14:16:27, 조철희
        */
        _TOA diff_min, diff_max;

        diff_min = pSeg1->pri.tMin - pSeg2->pri.tMin;
        diff_max = pSeg1->pri.tMax - pSeg2->pri.tMax;

        /*! \bug  && 에서 || 으로 변경함.
            \date 2008-11-06 13:04:15, 조철희
        */
        if( diff_min <= (_TOA)( 3*STABLE_MARGIN ) || diff_max <= (_TOA)( 3*STABLE_MARGIN ) ) {
            uiRet = 1;
        }
        else {
            uiRet = 0;
        }
        // return CheckHarmonic( pSeg1, pSeg2 );
    }
    else if( pEmitter1->enPRIType == _STABLE && pEmitter2->enPRIType == _STABLE ) {
        uiRet = CheckHarmonic( pSeg1, pSeg2 );
    }
    // 스태거 에미터에 대한 비교
    // 삭제된 규칙성 펄스열도 가상 에미터를 생성하기 때문에 Jitter 열에서 분석된 스태거와
    // 유사할 수 있기 때문에 여기서 하모닉 체크해서 제거한다.
    // 각 스테거레벨 마다 1:1 비교한다.
    //-- 조철희 2006-03-17 12:22:05 --//
    else if( pEmitter1->enPRIType == _STAGGER && pEmitter2->enPRIType == _STAGGER ) {
        unsigned int i;
        _TOA *pStaggerLevel1, *pStaggerLevel2;

        if( pEmitter1->uiStagDwellLevelCount == pEmitter2->uiStagDwellLevelCount ) {
            uiRet = 1;
            pStaggerLevel1 = & pEmitter1->tStaggerDwellLevel[0];
            pStaggerLevel2 = & pEmitter2->tStaggerDwellLevel[0];
            for( i=0 ; i < pEmitter1->uiStagDwellLevelCount ; ++i ) {
                if( TRUE != CompMeanDiff<_TOA>( *pStaggerLevel1++, *pStaggerLevel2++, 3*STABLE_MARGIN ) ) {
                    uiRet = 0;
                    break;
                }
            }

        }
    }
    /*! \bug  에미터 분석에서 jitter와 스태거 분석으로 나뉘어지면 이를 판단한다.
        \date 2006-07-07 11:41:49, 조철희
    */
    else if( pEmitter1->enPRIType == _STAGGER && pEmitter2->enPRIType == _JITTER_RANDOM ) {
//         if( pEmitter1->pri.min >= pEmitter2->pri.min && pEmitter1->pri.max <= pEmitter2->pri.max ) {
//             uiRet = 1;
//         }

        /*! \bug  Jitter 신호는 하모닉 체크해서 최대한 없앤다.
            \date 2006-08-25 09:37:36, 조철희
        */
        uiRet = CheckHarmonic( pSeg1, pSeg2 );
    }

    else if( pEmitter1->enPRIType == _JITTER_RANDOM && pEmitter2->enPRIType == _STAGGER ) {
//         if( pEmitter2->pri.min >= pEmitter1->pri.min && pEmitter2->pri.max <= pEmitter1->pri.max ) {
//             return 1;
//         }

        /*! \bug  Jitter 신호는 하모닉 체크해서 최대한 없앤다.
            \date 2006-08-25 09:37:36, 조철희
        */
        uiRet = CheckHarmonic( pSeg1, pSeg2 );
    }

    return uiRet;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::CheckHarmonic
// 반환되는 형  : UINT
// 함 수 인 자  : UINT priMean1
// 함 수 인 자  : UINT priMean2
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-07-28 09:50:05
//
//##ModelId=42E85F3B0046
UINT CAnalPRI::CheckHarmonic(_TOA priMean1, _TOA priMean2, _TOA uiThreshold )
{
    UINT uiRet = 0;
    _TOA max_mean, min_mean;

    if( priMean1 > priMean2 ) {
        max_mean = priMean1;
        min_mean = priMean2;
    }
    else {
        max_mean = priMean2;
        min_mean = priMean1;
    }

    // harmonic = max_mean % min_mean;

    // 10배수 이상이면 STABLE 마진 값을 두배로 해서 harmonic 체크한다.
    //UINT margin_th = UDIV( max_mean, STABLE_MARGIN*1000 );
    //margin_th = max( margin_th, 3 * _spOneMicrosec );

    // 하모닉 체크에서 배수만큼 더한 마진으로 체크한다.
    /*! \bug  나머지를 체크하는 것으로 수정함.
        \date 2008-11-05 23:27:37, 조철희
    */
    int ret=UDIV( max_mean, min_mean );
    _TOA tModular = (max_mean % min_mean);
    if( ( (UINT) tModular < uiThreshold ) ) {
        uiRet = (UINT) ret;
    }
    else {
        tModular = min_mean - tModular;
        if( tModular < uiThreshold ) {
            uiRet = (UINT) ret;
        }
    }

    return uiRet;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::CheckHarmonic
// 반환되는 형  : UINT
// 함 수 인 자  : STR_PULSE_TRAIN_SEG *pSeg1
// 함 수 인 자  : STR_PULSE_TRAIN_SEG *pSeg2
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-31 16:15:43
//
//##ModelId=428C21350105
UINT CAnalPRI::CheckHarmonic(STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2)
{
    UINT uRet;

    int ref_jitterp;
    int jitter_ratio1, jitter_ratio2;

    int div_jitter_ratio, jitter_ratio_threshold;

    STR_PULSE_TRAIN_SEG *pSegMax, *pSegMin;

    uRet = 0;

    if( ( pSeg1->enPriType == _STABLE || pSeg1->enPriType == _REFSTABLE || pSeg1->enPriType == _DWELL ) &&
        ( pSeg2->enPriType == _STABLE || pSeg2->enPriType == _REFSTABLE || pSeg1->enPriType == _DWELL ) ) {
        uRet = CheckHarmonic( pSeg1->pri.tMean, pSeg2->pri.tMean );
    }
    else {
        if( pSeg1->pri.tMean > pSeg2->pri.tMean ) {
            pSegMax = pSeg1;
            pSegMin = pSeg2;
            ref_jitterp = UMUL( pSeg2->fJitterRatio, 100. );
        }
        else {
            pSegMax = pSeg2;
            pSegMin = pSeg1;
            ref_jitterp = UMUL( pSeg1->fJitterRatio, 100. );
        }

        // PRI 하모닉 관계로 jitter 율은 1/K 배로 줄어들 수 있다.
        // Jitter 임계값을 이에 따라 변경해야 한다.
        //-- 조철희 2005-10-20 15:50:29 --//

        // 지터율 임계값 정의
        div_jitter_ratio = _max( 1, UDIV( pSegMax->pri.tMean, pSegMin->pri.tMean ) );
        jitter_ratio_threshold = HARMONIC_JITTER_P_THRESHOLD + ( ref_jitterp - UDIV( ref_jitterp, div_jitter_ratio ) );
        jitter_ratio_threshold = _max( HARMONIC_JITTER_P_THRESHOLD, jitter_ratio_threshold );

        // 펄스열에 따른 지터율 계산
        jitter_ratio1 = UMUL( pSeg1->fJitterRatio, 100. );
        jitter_ratio2 = UMUL( pSeg2->fJitterRatio, 100. );

        // 지터율 비교
        // PRI가 작으면 지터율이 큰 차이를 볼 수 있기 때문에 jitter_ratio_threshold 에 대한 기준값은
        // PRI 에 따라서 Linear 하게 변경해야 한다.
        // 그래서, 지터율 체크는 제외시켰다.
        if( FALSE == CompMeanDiff( jitter_ratio1, jitter_ratio2, jitter_ratio_threshold ) ) {
            // printf( "\n Jitter ratio : %d(%d,%d)" , jitter_ratio_threshold, jitter_ratio1, jitter_ratio2 );
            // return 0;
        }

        // 지터 범위 비교
#ifndef _JITTER_RANGE_IN_HARMONIC_
        _TOA harmonic;
        int halfdiff;
        int jitter_margin1, jitter_margin2;

        jitter_margin1 = UMUL( pSeg1->pri.tMean, pSeg1->fJitterRatio );
        jitter_margin2 = UMUL( pSeg2->pri.tMean, pSeg2->fJitterRatio );
        halfdiff = _max( jitter_margin1, jitter_margin2 );

        harmonic = pSegMax->pri.tMean % pSegMin->pri.tMean;

        if( harmonic < halfdiff )
            uRet = div_jitter_ratio;
        else if( pSegMin->pri.tMean-harmonic < halfdiff )
            uRet = div_jitter_ratio;
#else
        int overlap_ratio;
        int overlap_space;
        int exp_pri_min, exp_pri_max;

        float fdiv_jitter_ratio;

        fdiv_jitter_ratio = FDIV( pSegMax->pri.tMean, pSegMin->pri.tMean );
        exp_pri_min = UMUL( fdiv_jitter_ratio, pSegMin->pri.tMin );
        exp_pri_max = UMUL( fdiv_jitter_ratio, pSegMin->pri.tMax );

        overlap_space = CalOverlapSpace( pSegMax->pri.tMax, pSegMax->pri.tMin, exp_pri_max, exp_pri_min );
        if( overlap_space != 0 ) {
            overlap_ratio = UDIV( overlap_space * 100 , pSegMax->pri.tMax - pSegMax->pri.tMin );
            if( overlap_ratio < 80 ) {
                overlap_ratio = UDIV( ( pSegMax->pri.tMax - pSegMax->pri.tMin ) * 100 , overlap_space );
                if( overlap_ratio >= 80 )
                    uRet = (int) ( fdiv_jitter_ratio + 0.5 );
            }
            else
                uRet = (int) ( fdiv_jitter_ratio + 0.5 );
        }

#endif
    }

    /*
    else if( ( pSeg1->pri_type == _STABLE && pSeg2->pri_type == _JITTER ) ||
                     ( pSeg1->pri_type == _JITTER && pSeg2->pri_type == _STABLE ) ) {
        uRet = CheckHarmonic( pSeg1->pri.mean, pSeg2->pri.mean );
    }
    else if( ( pSeg1->pri_type == _JITTER || pSeg2->pri_type == _JITTER ) ) {
        jitter_margin1 = UMUL( pSeg1->pri.mean, pSeg1->jitter_p );
        jitter_margin2 = UMUL( pSeg2->pri.mean, pSeg2->jitter_p );
        halfdiff = _max( jitter_margin1, jitter_margin2 );

        harmonic = max_mean % min_mean;

        if( harmonic < halfdiff )
            uRet = TRUE;
        if( min_mean-harmonic < halfdiff )
            uRet = TRUE;
    }		*/

    return uRet;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::DecisionEmitter
// 반환되는 형  : BOOL
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-19 10:15:50
//
//##ModelId=428C213403B7
BOOL CAnalPRI::DecisionEmitter(STR_EMITTER *pEmitter)
{
    BOOL bRet=FALSE;
    UINT conti_threshold;

    // 최소 에미터 대상 펄스 개수 체크
    unsigned int coPulse=pEmitter->stPDW.uiCount;
    if( coPulse <= _spAnalMinPulseCount ) {
        bRet = FALSE;
    }
    else {
        // 주파수 호핑 폭이 일정값 이상이면 버린다.
        if( CheckFreqHopping( pEmitter ) == FALSE ) {
            bRet = FALSE;
        }

        // 에미터 타입에 따른 최소 펄스 개수 체크
        if( pEmitter->enPRIType == _STABLE ) {
            /*! \bug  패턴 신호 사이에서 STABLE 펄스열들이 추출될 수 있기 때문에 이를 확인해서 제거한다.
                                그래서 Stable 펄스열들 중에서 제일 큰 펄스열의 개수가 _spAnalMinPulseCount 보다 커야 한다.
                \date 2006-09-04 11:41:59, 조철희
            */
            unsigned int maxNoPulse;

            maxNoPulse = 0;
            for( unsigned int i=0 ; i < pEmitter->uiCoSeg ; ++i ) {
                maxNoPulse = _max( maxNoPulse, m_pSeg[ pEmitter->uiSegIdx[i] ].pdw.uiCount );
            }
            if( maxNoPulse < _spAnalMinPulseCount ) {
                bRet = FALSE;
            }

            if( coPulse >= _spAnalMinPulseStableEmitter ) {
                bRet = TRUE;
            }
        }
        else {
            if( coPulse >= _spAnalMinPulseJitterEmitter ) {
                bRet = TRUE;
            }
        }
    }

    if( bRet == FALSE ) {
        bRet = TRUE;
        //////////////////////////////////////////////////////////////////////
        // 여기서 부터는 최소 PDW 개수 이하일 때 에미터 생성 여부를 판단한다.
        // 펄스열의 연속성과 추출한 PDW의 방위 범위 등을 체크해서 에미터 생성여부를 판단한다.
        //
        // 펄스열의 연속성을 체크해서 에미터로 생성 여부를 판단한다.
        STR_PULSE_TRAIN_SEG *pSeg;

        pSeg = & m_pSeg[ pEmitter->uiMainSeg ];
        conti_threshold = GetContiThreshold( coPulse );
        if( pSeg->continuity < conti_threshold ) {
            // printf( "\n 펄스열 연속성 부족: %d, threshold[%d]" , pSeg->continuity, conti_threshold );
            // return FALSE;
        }

        // 방위 범위가 크면 버린다.
        int diffAoa;
        diffAoa = pSeg->aoa.iMax - pSeg->aoa.iMin;
        if( diffAoa < 0 )
            diffAoa += MAX_AOA;
        if( diffAoa > (int) m_spdiffaoa[ pSeg->uiBand ] ) {
            bRet = FALSE;
        }

        // DTOA의 Jitter율이 매우 크면 버린다.
        if( pSeg->fJitterRatio > MAX_JITTER_P/100. ) {
            bRet = FALSE;
        }

        // 04-06-25
        // 최소 개수 %이하일 때는 PRI 가 짧은 것은 에미터로 생성하지 않는다.
        // 530 us 는 해상레이더의 Long 모드 일때...
        // 펄스 개수가 _spAnalMinPulseCount 이상이고
        // _spAnalMinPulseStableEmitter 또는 _spAnalMinPulseJitterEmitter 이하일때
        // PRI 평균을 체크해서 로브 특성이 체크된다고 하더라도 반사파로 가정하여 버린다.
    /*
        int priMean = m_pNewSigAnal->VerifyPRI( & pEmitter->pdw.index[0], pEmitter->pdw.count );
        if( priMean <= 530 * _spOneMicrosec )
            return FALSE;

    */
        if( bRet == TRUE ) {
            bRet = AnalLobe( pEmitter );
        }
    }

    return bRet;
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CAnalPRI::CheckFreqHopping
//!	\author  조철희
//!	\param	 pEmitter	인자형태 STR_EMITTER *
//!	\return	 BOOL
//! \version 1.0
//! \date		 2006-06-02 11:15:13
//! \warning
//
BOOL CAnalPRI::CheckFreqHopping( STR_EMITTER *pEmitter )
{
    unsigned int i;
    int iBand;
    int freq_diff, max_freq_diff, pre_freq;

    unsigned int uiCount;
    PDWINDEX *pPdwIndex;

    BOOL bRet=TRUE;

    uiCount = pEmitter->stPDW.uiCount;
    pPdwIndex = pEmitter->stPDW.pIndex;

    iBand = m_pBAND[ *pPdwIndex ];
    pre_freq = m_pFREQ[ *pPdwIndex++ ];
    max_freq_diff = 0;
    for( i=1 ; i < uiCount; ++i ) {
        freq_diff = _abs( (int) m_pFREQ[ *pPdwIndex ] - pre_freq );
        max_freq_diff = _max( freq_diff, max_freq_diff );
        pre_freq = m_pFREQ[ *pPdwIndex++ ];
    }

    /*! \bug  주파수 편차 계산
        \date 2008-07-25 10:33:11, 조철희
    */
    // int freq=FRQCNV( band+1, max_freq_diff ) - gFreqRes[band+1].min;
#ifdef _POCKETSONATA_
    float freq=FRQMhzCNV(iBand +1, max_freq_diff );
#else
    int freq=FRQMhzCNV(iBand +1, max_freq_diff );
#endif

    //  WSA-423의 레이더 신호를 참조해서 정함.
    /*! \bug  anlfrq_6.pdw의 주파수 최대 편차는 약 500 MMz 가 된다.
        \date 2006-08-16 10:27:18, 조철희
    */
    if( freq >= MAX_FREQ_DEVIATION ) {
        bRet = FALSE;
    }
    return bRet;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CAnalPRI::IsFreqHopping
        \author   조철희
        \param    pEmitter 인자형태 STR_EMITTER *
        \return   BOOL
        \version  0.0.52
        \date     2008-10-30 15:16:56
        \warning
*/
BOOL CAnalPRI::IsFreqHopping( STR_EMITTER *pEmitter )
{
    unsigned int i;
    BOOL bRet=FALSE;

    unsigned int freq, next_freq;
    unsigned int max_freq, min_freq;

    unsigned int uiCount;
    int nZeroFreq, nHopLevel;
    UINT total_freq;
    
    PDWINDEX *pPdwIndex;

    BOOL bCheck;

    uiCount = pEmitter->stPDW.uiCount;
    pPdwIndex = pEmitter->stPDW.pIndex;

    // 디버깅 필요......

    nHopLevel = 0;
    for( i=1 ; i < uiCount; ++i ) {
        _EQUALS3( total_freq, nZeroFreq, 0 )
        _EQUALS4( max_freq, min_freq, freq, m_pFREQ[ *pPdwIndex++ ] )
		bCheck = FALSE;
		for(  ; i < uiCount; ++i ) {
			next_freq = m_pFREQ[ *pPdwIndex++ ];
			if( CompMeanDiff<unsigned int>( next_freq, freq, 5 ) == TRUE ) {
				++ nZeroFreq;
				total_freq += next_freq;
				max_freq = _max( max_freq, next_freq );
				min_freq = _min( min_freq, next_freq );
			}
			else {
				if( ( max_freq - min_freq ) <= 4 ) {
					bCheck = TRUE;
                }
				break;
			}
		}

		if( bCheck == TRUE && nZeroFreq >= 10 ) {
			++ nHopLevel;
		}
    }

    if( nHopLevel >= 2 ) {
        bRet = TRUE;
    }

    return bRet;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::GetContiThreshold
// 반환되는 형  : int
// 함 수 인 자  : int count
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-08-18 14:36:36%
//
int CAnalPRI::GetContiThreshold(int iCount)
{
    int iRet;

    if (iCount < _spContiThresholdMinPulseCount) {
        iRet = CONTI_THR_LOW_PULSE;
    }
    else {
        iRet = CONTI_THR_HIGH_PULSE;
    }

    return iRet;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::AnalLobe
// 반환되는 형  : BOOL
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-19 10:11:09
//
//##ModelId=428C2135001F
BOOL CAnalPRI::AnalLobe( STR_EMITTER *pEmitter )
{
    unsigned int i;
    unsigned int uiCount;
    PDWINDEX *pPdwIndex;
    STR_MINMAX pa;
    int diffPa;

    BOOL flag;
    PDWINDEX index;
    float ratio_total;
    int incline_count, decline_count;

    int pa_threshold, cline_threshold;

    STR_PULSE_TRAIN_SEG *pSeg;

    BOOL bRet;

    pa.iMax = 0;
    pa.iMin = INT32_MAX;
    for( i=0 ; i < pEmitter->uiCoSeg ; ++i ) {
        pSeg = & m_pSeg[ pEmitter->uiSegIdx[i] ];
        pa.iMax = _max( pSeg->pa.iMax, pa.iMax );
        pa.iMin = _min( pSeg->pa.iMin, pa.iMin );
    }

    int iPa = _abs(pa.iMax - pa.iMin);
    if( iPa >= IDIV( 6, _spAMPres ) ) {
        cline_threshold = 1;
        pa_threshold = 6;
    }
    else {
        cline_threshold = 0;
        pa_threshold = 1;
    }

  // 신호 세기의 증가 개수를 카운드
    uiCount = pEmitter->stPDW.uiCount;
    flag = TRUE;
    incline_count = 0;
    pPdwIndex = pEmitter->stPDW.pIndex;
    for( i=0 ; i < uiCount-1 ; ++i ) {
        index = *pPdwIndex++;
        diffPa = m_pPA[*pPdwIndex] - m_pPA[index];
        if( flag && diffPa >= cline_threshold ) {
            flag = TRUE;
            ++ incline_count;
        }

        flag = FALSE;
        if( diffPa >= 0 ) {
            flag = TRUE;
        }
    }

    // 신호 세기의 감소 개수를 카운드
    flag = TRUE;
    decline_count = 0;
    pPdwIndex = pEmitter->stPDW.pIndex;
    for( i=0 ; i < uiCount-1 ; ++i ) {
        index = *pPdwIndex++;
        diffPa = m_pPA[*pPdwIndex] - m_pPA[index];
        //-- 조철희 2005-09-27 17:27:32 --//
        // 등호는 감소개수 비교에서는 제외시켜서 카운트 한다.
        if( flag && diffPa < cline_threshold ) {
            flag = TRUE;
            ++ decline_count;
        }

        flag = FALSE;
        if( diffPa <= 0 ) {
            flag = TRUE;
        }
    }

    ratio_total = (float) ( incline_count + decline_count ) / (float) ( uiCount-3 );

    // 증가 개수율과 감소 개수율이 모두 80% ~이상일 때
    //-- 조철희 2005-09-27 17:28:45 --//
    // 증가/감소 개수가 0 이상일 때만 로브 조건 추가.
    if( ( ratio_total >= 0.6 ) && ( incline_count != 0 && decline_count != 0 ) && ( (UINT) _abs( pa.iMax - pa.iMin ) >= UDIV( pa_threshold, _spAMPres ) ) ) {
        bRet = TRUE;
    }
    else {
        bRet = FALSE;
    }

    return bRet;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::SelectMainSeg
// 반환되는 형  : void
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-19 19:49:28
//
//##ModelId=429A5BDD0270
void CAnalPRI::SelectMainSeg(STR_EMITTER *pEmitter)
{
    unsigned int i;
    STR_MINMAX_TOA pri;
    STR_PULSE_TRAIN_SEG *pSeg;

    if( pEmitter->uiCoSeg == 0 ) {
        
    }
    else {
        //
        // 에미터가 STABLE, JITTER일 경우에는 하모닉 관계에서 PRI 평균이 가장 작은 펄스열 중에서 .
        // 그 이외의 타입일 경우에는 펄스열 개수가 가장 많은 펄스열을 선택한다.
        if( pEmitter->enPRIType == _JITTER_RANDOM || pEmitter->enPRIType == _STABLE ) {
            unsigned int max_count=0;

            pri.tMin = 0xFFFFFF;
            pri.tMax = 0xFFFFFF;
            for( i=0 ; i < pEmitter->uiCoSeg ; ++i ) {
                pSeg = & m_pSeg[ pEmitter->uiSegIdx[i] ];

                if( CalOverlapSpace<_TOA>( pri.tMax, pri.tMin, pSeg->pri.tMax, pSeg->pri.tMin ) != 0 ) {
                    if( max_count < pSeg->pdw.uiCount ) {
                        pEmitter->uiMainSeg = pEmitter->uiSegIdx[i];
                        max_count = pSeg->pdw.uiCount;
                        pri.tMin = pSeg->pri.tMin;
                        pri.tMax = pSeg->pri.tMax;
                    }
                }
                else if( pri.tMax >= pSeg->pri.tMax ) {
                    pEmitter->uiMainSeg = pEmitter->uiSegIdx[i];
                    max_count = pSeg->pdw.uiCount;
                    pri.tMin = pSeg->pri.tMin;
                    pri.tMax = pSeg->pri.tMax;
                }
            }
        }
        else {
            unsigned int max_count=0;
            for( i=0 ; i < pEmitter->uiCoSeg ; ++i ) {
                pSeg = & m_pSeg[ pEmitter->uiSegIdx[i] ];

                if( max_count < pSeg->pdw.uiCount ) {
                    pEmitter->uiMainSeg = pEmitter->uiSegIdx[i];
                    max_count = pSeg->pdw.uiCount;
                }
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : incCompare
// 반환되는 형  : int
// 함 수 인 자  : const void *arg1
// 함 수 인 자  : const void *arg2
// 함 수 설 명  :
// 최 종 변 경  : RSA노트북, 2005-06-22 18:09:09
//
int incCompare( const void *arg1, const void *arg2 )
{
  UINT *p1, *p2;

  p1 = (UINT *) arg1;
  p2 = (UINT *) arg2;

  if( *p1 > *p2 )
    return( 1 );
  else if( *p1 < *p2 )
    return( -1 );
  else
    return( 0 );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : decCompare
// 반환되는 형  : int
// 함 수 인 자  : const void *arg1
// 함 수 인 자  : const void *arg2
// 함 수 설 명  :
// 최 종 변 경  : RSA노트북, 2005-06-22 18:09:09
//
int decCompare( const void *arg1, const void *arg2 )
{
  UINT *p1, *p2;

  p1 = (UINT *) arg1;
  p2 = (UINT *) arg2;

  if( *p1 < *p2 )
    return( 1 );
  else if( *p1 > *p2 )
    return( -1 );
  else
    return( 0 );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::StaggerLevelAnalysis
// 반환되는 형  : BOOL
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-11-23 09:25:07
//
BOOL CAnalPRI::StaggerLevelAnalysis( STR_EMITTER *pEmitter )
{
    unsigned int i, ui;
    _TOA stagger_level;
    int stagger_level_cnt;
    _TOA offset_steggerlevel;

    STR_PULSE_TRAIN_SEG *pSeg;

    BOOL bRet=TRUE;

    // 시간순으로 정렬
    //-- 조철희 2006-01-09 15:22:22 --//
    // pSeg 인덱스를 pEmitter 인덱스에 맞춰서 억세스 한다.
    //-- 조철희 2006-05-09 11:55:30 --//
    pEmitter->uiStagDwellLevelCount = 0;
    for( ui=0 ; ui < pEmitter->uiCoSeg ; ++ui, ++pSeg ) {
        pSeg = & m_pSeg[ pEmitter->uiSegIdx[ui] ];

        /*! \bug  펄스열 중에서 유사 펄스열을 골라서 제거한다.
                \date 2006-05-12 17:08:54, 조철희
        */
        if( FALSE == CompareAllStaggerLevel( pEmitter, pSeg ) ) {
            pEmitter->tStaggerDwellLevel[ pEmitter->uiStagDwellLevelCount ] = pSeg->tFirst % pEmitter->tFramePri;
            ++ pEmitter->uiStagDwellLevelCount;

            /*! \bug  스태거 레벨 개수 이상이면 Jitter 로 분석하기 위함이다.
                \date 2006-08-31 17:14:48, 조철희
            */
            if( (unsigned int) pEmitter->uiStagDwellLevelCount >= MAX_STAGGER_LEVEL_ELEMENT ) {
                pEmitter->uiStagDwellLevelCount = 0;
                bRet = FALSE;
            }
        }
    }

    if( bRet == TRUE ) {
        qsort( pEmitter->tStaggerDwellLevel, (size_t) pEmitter->uiStagDwellLevelCount, sizeof(UINT), incCompare );
        offset_steggerlevel = pEmitter->tStaggerDwellLevel[0];

        //////////////////////////////////////////////////////////////////////////
        // 스태거 레벨 계산
        stagger_level_cnt = 0;
        for( i=1 ; i < pEmitter->uiStagDwellLevelCount ; ++i ) {
            stagger_level = ( pEmitter->tStaggerDwellLevel[i] - pEmitter->tStaggerDwellLevel[i-1] ) % pEmitter->tFramePri;
            if( stagger_level != 0 ) {
                pEmitter->tStaggerDwellLevel[ stagger_level_cnt ] = stagger_level;
                ++ stagger_level_cnt;
            }
            else {
                //-- 조철희 2006-01-09 15:11:49 --//
                pEmitter->uiStagDwellLevelCount = 0;
                bRet = FALSE;
            }
        }

        if( bRet == TRUE ) {
            // 스태거 레벨의 마지막 레벨을 계산할 때, pEmitter->stag_dwell_level[i-1] - pEmitter->framePri 의 부호에 의해
            // 계산한다.
            //-- 조철희 2006-05-09 11:57:51 --//
            if( pEmitter->tStaggerDwellLevel[i-1] > pEmitter->tFramePri ) {
                pEmitter->tStaggerDwellLevel[ stagger_level_cnt ] = ( offset_steggerlevel + pEmitter->tStaggerDwellLevel[i-1] - pEmitter->tFramePri ) % pEmitter->tFramePri;
            }
            else {
                pEmitter->tStaggerDwellLevel[ stagger_level_cnt ] = ( offset_steggerlevel + pEmitter->tFramePri - pEmitter->tStaggerDwellLevel[i-1] ) % pEmitter->tFramePri;                
            }

            //! Unused Value help
            // ++ stagger_level_cnt;

            /*! \bug  스태거 레벨단을 하모닉 체크해서 버리게 한다.
                \date 2006-07-19 12:27:56, 조철희
            */
            CheckHarmonicStaggerLevel( pEmitter );

            /*! \bug  스태거 레벨 검증해서 스태거 타입을 확인하게 한다.
                                스태거 검증에서 에러로 판단이 되면 이 펄스열을 버린다.
                \date 2006-05-18 15:04:22, 조철희
            */
            if( VerifyStaggerLevel( pEmitter ) == FALSE ) {
                bRet = FALSE;
            }
            else {
                /*! \bug  스태거 레벨을 작은 값부터 정렬을 한다.
                    \date 2006-07-04 19:42:30, 조철희
                */
                MakeStaggerLevel( pEmitter->tStaggerDwellLevel, pEmitter->uiStagDwellLevelCount );

                // 스태거 PRI의 PRI 범위 및 평균을 계산한다.
                pEmitter->stPRI.tMean = 0;
                pEmitter->stPRI.tMin = pEmitter->tStaggerDwellLevel[0];
                pEmitter->stPRI.tMax = 0;
                for( i=0 ; i < (int) pEmitter->uiStagDwellLevelCount && i < MAX_FREQ_PRI_STEP ; ++i ) {
                    pEmitter->stPRI.tMin = _min( pEmitter->stPRI.tMin, pEmitter->tStaggerDwellLevel[i] );
                    pEmitter->stPRI.tMax = _max( pEmitter->stPRI.tMax, pEmitter->tStaggerDwellLevel[i] );
                    pEmitter->stPRI.tMean += pEmitter->tStaggerDwellLevel[i];
                }
                pEmitter->stPRI.tMean = UDIV( pEmitter->stPRI.tMean, i );
            }
        }
    }

    //-- 조철희 2006-01-09 14:05:45 --//
    //! \note Stagger 레벨로 추출해서 최종 확인해야 한다.
    return bRet;
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CAnalPRI::MakeStaggerLevel
//!	\author  조철희
//!	\param	 pStaggerLevel	인자형태 int *
//! \param	 CoStagger	인자형태 int
//!	\return	 void
//! \version 1.0
//! \date		 2006-07-05 13:50:12
//! \warning
//
void CAnalPRI::MakeStaggerLevel( _TOA *pStaggerLevel, int CoStagger )
{
    int i;
    int min_index;
    _TOA min_stagger_level, stagger_level_value;

    _TOA stagger_level[MAX_FREQ_PRI_STEP];

    if( CoStagger > 0 ) {
        min_index = 0;
        min_stagger_level = *pStaggerLevel;
        for( i=1 ; i < CoStagger && i < MAX_FREQ_PRI_STEP ; ++i ) {
            stagger_level_value = pStaggerLevel[i];
            if( min_stagger_level > stagger_level_value ) {
                min_index = i;
                min_stagger_level = stagger_level_value;
            }
        }

        // 그 인덱스 값부터 에미터의 스태거단에 기록한다.
        // 그리고 PRI 범위와 평균값을 기록한다.
        for( i=0 ; i < (int) CoStagger && i < MAX_FREQ_PRI_STEP ; ++i ) {
            stagger_level[i] = pStaggerLevel[ (min_index+i) % CoStagger ];
        }

        memcpy( pStaggerLevel, stagger_level, sizeof(_TOA) * CoStagger );
    }

}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CAnalPRI::VerifyStaggerLevel
//!	\author  조철희
//!	\param    pStaggerEmitter 인자형태 STR_EMITTER *
//!	\param    pEmitter 인자형태 STR_EMITTER *
//!	\return	 BOOL
//! \version 1.0
//! \date		 2006-05-18 15:10:51
//! \warning
//
BOOL CAnalPRI::VerifyStaggerLevel( STR_EMITTER *pStaggerEmitter, STR_EMITTER *pEmitter )
{
    int i;
    _TOA max_dtoa, min_dtoa;

    BOOL bRet=TRUE;

    int CoStagger;
    _TOA *pStaggerLevel;

    CoStagger = pStaggerEmitter->uiStagDwellLevelCount;
    pStaggerLevel = pStaggerEmitter->tStaggerDwellLevel;
    if( CoStagger <= _spOne || CoStagger > MAX_FREQ_PRI_STEP ) {
        bRet = FALSE;
    }
    else {
        // 스태거 레벨 단 중에서 가장 큰 값과 가장 작은 값의 차이가 2배 이상이면
        // 스태거 판단에서 에러로 보고한다.
        /*! \todo	스태거 판단에서 에러로 보고 된것은 재 분석해서
                            Jitter로 분석하는 것이 맞을 것이다.											*/
        max_dtoa = *pStaggerLevel;
        min_dtoa = *pStaggerLevel++;
        for( i=1 ; i < CoStagger ; ++i ) {
            max_dtoa = _max( max_dtoa, *pStaggerLevel );
            min_dtoa = _min( min_dtoa, *pStaggerLevel );
            ++ pStaggerLevel;
        }

        /*! \bug  에미터 구조체의 PRI 에 범위를 저장함.
            \date 2006-08-31 11:42:58, 조철희
        */
        pStaggerEmitter->stPRI.tMin = min_dtoa;
        pStaggerEmitter->stPRI.tMax = max_dtoa;

        //////////////////////////////////////////////////////////////////////////
        // 조건 1: 지터율이 50%가 안 넘도록 함.
        if( min_dtoa*2 <= max_dtoa ) {
            bRet = FALSE;
        }
        else {
            // 조건 2: 펄스열로 추출한 PRI 범위와 스태거로 추출한 PRI 범위를 체크함.
            if( NULL != pEmitter && FALSE == CompMarginDiff<_TOA>( pEmitter->stPRI.tMean, pStaggerEmitter->stPRI.tMin, pStaggerEmitter->stPRI.tMax, 0 ) ) {
                bRet = FALSE;
            }
        }
    }

    return bRet;
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CompareAllStaggerLevel
//!	\author  조철희
//!	\param	 pEmitter	인자형태 STR_EMITTER *
//! \param	 pSeg	인자형태 STR_PULSE_TRAIN_SEG *
//!	\return	 BOOL
//! \version 1.0
//! \date		 2006-05-12 17:17:21
//! \warning
//
BOOL CAnalPRI::CompareAllStaggerLevel( STR_EMITTER *pEmitter, STR_PULSE_TRAIN_SEG *pSeg )
{
    unsigned int i;
    _TOA harm_toa, threshold_toa;
    
    BOOL bRet=FALSE;

    threshold_toa = 2 * STABLE_MARGIN;

    harm_toa = pSeg->tFirst % pEmitter->tFramePri;
    for( i=0 ; i < pEmitter->uiStagDwellLevelCount ; ++i ) {
        _TOA toaDiff;

        toaDiff = harm_toa - pEmitter->tStaggerDwellLevel[i];
        if( toaDiff < threshold_toa ) {
            bRet = TRUE;
            break;
        }
        toaDiff = pEmitter->tFramePri - toaDiff;
        if( toaDiff < threshold_toa ) {
            bRet = TRUE;
            break;
        }
    }
    return FALSE;
}

/**
 * @brief     NormalizeTOA
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-27, 15:31
 * @warning
 */
void CAnalPRI::NormalizeTOA(STR_EMITTER *pEmitter )
{
    _TOA *pToa1;
    _TOA firstToa;

    PDWINDEX *pPdwIndex;

    unsigned int i, uiCount;

    uiCount = m_pSeg[pEmitter->uiMainSeg].pdw.uiCount;

    pToa1 = & m_pPulseToa[0];
    pPdwIndex = m_pSeg[pEmitter->uiMainSeg].pdw.pIndex;
    firstToa = m_pTOA[*pPdwIndex];
    for (i = 0; i < uiCount; ++i) {
        *pToa1++ = m_pTOA[*pPdwIndex++] - firstToa;
    }

}

/**
 * @brief     AnalyzeACF
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-27, 15:34
 * @warning
 */
void CAnalPRI::AnalyzeACF(STR_EMITTER *pEmitter)
{
    int search_index;
    unsigned int i, j, k, uiCount;

    _TOA refToa;
    _TOA cmpToa;
    _TOA idtoa;

    _TOA *pToaAcf;
    _TOA *pToa1, *pToa2;

    uiCount = m_pSeg[pEmitter->uiMainSeg].pdw.uiCount;

    memset(m_pToaAcf, 0, sizeof(_TOA) * m_uiMaxPdw);
    /*! \bug  i=1 에서 i=0 으로 수정함. 첫번째 ACF 값을 구하지 않게 된것을 수정함.
        \date 2006-08-25 16:33:43, 조철희
    */
    for (i = 0; i < uiCount; ++i) {
        pToaAcf = &m_pToaAcf[i];
        refToa = m_pPulseToa[i];
        _EQUALS3(pToa1, pToa2, &m_pPulseToa[0])

        _EQUALS3(k, search_index, 0)
            for (j = i; j < uiCount; ++j) {
                cmpToa = *pToa2 + refToa;
                pToa1 = &m_pPulseToa[search_index];
                k = search_index;

                // ACF를 계산하는데 수정 주의.
                while (k < uiCount) {
                    idtoa = cmpToa - *pToa1;
                    if (idtoa > (UINT64_MAX - 10)) {
                        break;
                    }
                    else if (idtoa <= 10) {
                        ++ *pToaAcf;
                        search_index = k;
                        break;
                    }
                    else {
                        ++pToa1;
                    }

                    ++k;
                }

                ++pToa2;
            }
    }
}



//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::StaggerAnalysis
// 반환되는 형  : BOOL
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-25 13:58:46
//
//##ModelId=429A5BDD0216
bool CAnalPRI::StaggerAnalysis( STR_EMITTER *pEmitter )
{
    unsigned int i, j;
    unsigned int uiCount;
    
    PDWINDEX *pPdwIndex;

    unsigned int uiExtStaggerLevel;

    _TOA preToa, dtoa;
    _TOA firstToa;
    _TOA *pPulseDtoa;

    _TOA *pToaAcf;

    STR_EMITTER *pStaggerEmitter;

    uiCount = m_pSeg[pEmitter->uiMainSeg].pdw.uiCount;

    pEmitter->enPRIType = _JITTER_RANDOM;

    // Step : 1
    // TOA 첫번째 값으로 정렬
    NormalizeTOA( pEmitter );

    // Step : 2
    // ACF 연산
    //-- 조철희 2005-10-07 20:10:39 --//
    AnalyzeACF(pEmitter);

    // Step : 3
    // Find Frame PRI 측정
    m_coCanPeak=0;
    m_nRefFramePri = 0;
    pToaAcf = & m_pToaAcf[1];
    for( i=1 ; i < uiCount-1 ; ++i ) {
        // 피크 조건
        if(	*(pToaAcf-1) < *pToaAcf && *pToaAcf > pToaAcf[1] ) {
            m_pCanPeak[ m_coCanPeak++ ] = i;
        }

        ++ pToaAcf;
    }
    if( m_coCanPeak == 0 ) {
        return false;
    }
    else if( m_coCanPeak == 1 ) {
        m_pRefFramePri[0] = m_pPulseToa[ m_pCanPeak[0] ];
    }
    else {
#ifdef _STAGGER_LEVEL_PERIOD_
        printf( "\n DTOA :" );
        m_RefFramePri[0] = m_pPulseToa[ m_pCanPeak[0] ];
        m_nRefFramePri = 1;
        for( i=1 ; i < coCanPeak ; ++i ) {
            dtoa = m_pPulseToa[ m_pCanPeak[i] ] - m_pPulseToa[ m_pCanPeak[i-1] ];
            printf( "[%d]" , dtoa );
            if( FALSE == FindRefFramePri( dtoa ) ) {
                m_RefFramePri[m_nRefFramePri++] = dtoa;
            }
        }
        qsort( m_RefFramePri, (size_t) m_nRefFramePri, sizeof(UINT), incCompare );

#else

        // 피크 찾기 에서는 최대 피크의 갯를 m_nMaxPeak에 저장한다.
        // 이 값을 근거로 스태거 형태 여부를 판정하는데 추가한다.
        FindPeak();

#endif
    }

    // STEP : 4
    // Frame PRI를 근거로 스태거 레벨을 추출한다.
    /*! \bug  최대 에미터 개수 벗어날 조건 추가함.
          \date 2006-08-29 09:58:13, 조철희
    */
    if( m_uiCoEmitter >= MAX_AET ) {
        return false;
    }
    else {
        pStaggerEmitter = & m_Emitter[m_uiCoEmitter];
        pStaggerEmitter->uiCoSeg = 0;

        pStaggerEmitter->tFramePri = m_pRefFramePri[0];
        uiExtStaggerLevel = ExtractStagger( & m_pSeg[pEmitter->uiMainSeg].pdw, pStaggerEmitter->tFramePri, pStaggerEmitter );
        if( uiExtStaggerLevel <= 1 )
            return false;
        else
            MergePdwIndexInSeg( pStaggerEmitter );

        // STEP : 5
        // 각 레벨을 찾는다.
        BOOL bStaggerConfidelity;
        pPdwIndex = & pStaggerEmitter->stPDW.pIndex[0];
        preToa = m_pTOA[ *pPdwIndex++ ];
        uiCount = pStaggerEmitter->stPDW.uiCount;

#ifdef _STAGGER_LEVEL_FIND_METHOD_
        total_dtoa = 0;
        bStaggerConfidelity = TRUE;
        m_CoTmpStaggerLevel = m_CoStaggerLevel = 0;

        // 디버그 : 각 레벨마다 카운트해서 가장 많은 카운트에 해당하는 레벨을 취해야 한다.
        //-- 조철희 2005-06-22 15:32:09 --//
        for( i=1 ; i < count ; ++i, ++pPdwIndex ) {
            int diff_dtoa;

            firstToa = TOA[ *pPdwIndex ];
            dtoa = firstToa - preToa;
            preToa = firstToa;

            total_dtoa += dtoa;
            diff_dtoa = total_dtoa - framePri;
            if( diff_dtoa < -STB_MARGIN ) {
                m_nTmpStaggerLevel[m_CoTmpStaggerLevel++] = dtoa;
            }
            else if( diff_dtoa <= STB_MARGIN ) {
                m_nTmpStaggerLevel[m_CoTmpStaggerLevel++] = dtoa;
                if( m_CoTmpStaggerLevel > m_CoStaggerLevel ) {
                    memcpy( m_nStaggerLevel, m_nTmpStaggerLevel, sizeof( UINT ) * m_CoTmpStaggerLevel );
                    m_CoStaggerLevel = m_CoTmpStaggerLevel;

                    total_dtoa = 0;
                    m_CoTmpStaggerLevel = 0;
                }
                else if( m_CoStaggerLevel == m_CoTmpStaggerLevel ) {
                    // 아직 미구현
                    // 동일 레벨이더라도 다른 레벨값일 때 이에 대한 처리 필요 예상.
                }
            }
            else {
                total_dtoa = 0;
                m_CoTmpStaggerLevel = 0;
            }
        }

#else
        // DTOA 를 m_pPulseToa에 저장해서 레벨값을 찾기 위한 중간 버퍼에 저장한다.
        //-- 조철희 2005-09-28 16:13:00 --//
        m_CoPulseDtoa = 0;
        pStaggerEmitter->uiStagDwellLevelCount = 0;
        pPulseDtoa = & m_pPulseDtoa[0];
        for( i=1 ; i < uiCount; ++i, ++pPdwIndex ) {
            firstToa = m_pTOA[ *pPdwIndex ];
            dtoa = firstToa - preToa;
            preToa = firstToa;

            *pPulseDtoa++ = dtoa;
            ++ m_CoPulseDtoa;
        }

        // 스태거 레벨 단을 검사한다.
        bStaggerConfidelity = FALSE;
        for( i=0 ; i < uiCount; ++i ) {
            _TOA sum_dtoa;

            sum_dtoa = 0;
            pPulseDtoa = & m_pPulseDtoa[i];
            pStaggerEmitter->uiStagDwellLevelCount = 0;
            for( j=i ; j < uiCount; ++j ) {
                pStaggerEmitter->tStaggerDwellLevel[pStaggerEmitter->uiStagDwellLevelCount++] = *pPulseDtoa;
                sum_dtoa += *pPulseDtoa++;

                if( sum_dtoa < pStaggerEmitter->tFramePri-STABLE_MARGIN ) {
                    continue;
                }
                else if( sum_dtoa <= pStaggerEmitter->tFramePri+STABLE_MARGIN ) {
                    if( pStaggerEmitter->uiStagDwellLevelCount >= 2 && pStaggerEmitter->uiStagDwellLevelCount <= uiExtStaggerLevel ) {
                        if( TRUE == CheckStaggerLevel( pEmitter, pStaggerEmitter, j-pStaggerEmitter->uiStagDwellLevelCount+1 ) ) {
                            bStaggerConfidelity = TRUE;
                            break;
                        }
                    }
                    else if( pStaggerEmitter->uiStagDwellLevelCount == 1 )
                        break;
                }
                else {
                    break;
                }
            }

            if( bStaggerConfidelity == TRUE ) {
                // 추출된 PDW 개수와 스태거 레벨을 비교하여 최소 추출 개수를 예상할 수 있다.
                // 실제로 이보다 작은 Frame 추출할 때의 PDW 개수보다 적으면 Jitter로 분석한다.
                // 스태거 레벨값을 참조해서 하모닉 관계이면 이를 제거하도록 한다.
                CheckHarmonicStaggerLevel( pStaggerEmitter );
                break;
            }
        }
#endif

        /*! \bug  지터로 펄스열을 추출한 PRI 범위와 스태거 레벨의 PRI 를 비교해서 스태거 여부를 결정한다.
            \date 2006-08-30 17:32:31, 조철희
        */
        if( VerifyStaggerLevel( pStaggerEmitter, pEmitter ) == FALSE ) {
            return false;
        }

        /*! \bug  nExtStaggerLevel 레벨 단 대신에 하모닉 체크를 해서 최종 스태거 레벨 단인
                            pStaggerEmitter->stag_dwell_level_cnt 을 참조해서 스태거 여부를 결정한다.
                            피크 찾기에서 찾은 최대 피크 개수와 레벨단으로 스태거 를 검증한다.
                            최대 피크 개수는 최소 4 이상(2단이며 최소 2번 반복)이어야 한다.
                            그리고 수집개수의 절반이 깨끗한 스태거 레벨로 간주해서 검증한다.
            \date 2006-05-18 12:11:17, 조철희
        */
        if( ( bStaggerConfidelity == TRUE ) &&
                ( pStaggerEmitter->uiStagDwellLevelCount >= 2 && pStaggerEmitter->uiStagDwellLevelCount <= MAX_FREQ_PRI_STEP ) &&
                ( m_nMaxPeak >= _max( 4, UMUL( m_pSeg[pEmitter->uiMainSeg].pdw.uiCount, 0.3 ) ) ) ) {
            // 스태거 타입으로 결정한다.
            pEmitter->enPRIType = _STAGGER;

            // 스태거 단 저장.
            pEmitter->uiStagDwellLevelCount = pStaggerEmitter->uiStagDwellLevelCount;
            memcpy( pEmitter->tStaggerDwellLevel, pStaggerEmitter->tStaggerDwellLevel, sizeof( UINT ) * pStaggerEmitter->uiStagDwellLevelCount );

            /*! \bug  스태거 레벨을 작은 값부터 시작해서 스태거 레벨을 저장한다.
                    \date 2006-07-04 19:42:30, 조철희
            */
            MakeStaggerLevel( pEmitter->tStaggerDwellLevel, pEmitter->uiStagDwellLevelCount );

            // Frame PRI 저장
            pEmitter->tFramePri = pStaggerEmitter->tFramePri;

            return true;
        }

        else if( uiExtStaggerLevel > MAX_FREQ_PRI_STEP ) {
            printf( "\n %d단 이상의 스테거 레벨열을 찾아서 지터로 보고 한다 !" , uiExtStaggerLevel );
            WhereIs;
        }

    }

    return false;
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CAnalPRI::CheckHarmonicStaggerLevel
//! \author   조철희
//! \param    pStaggerEmitter 인자형태 STR_EMITTER *
//! \return   void
//! \version  1.37
//! \date     2005-12-13 10:35:59
//! \warning
//
void CAnalPRI::CheckHarmonicStaggerLevel( STR_EMITTER *pStaggerEmitter )
{
    int i;
	UINT j, k;
    unsigned int div=1;
    /*! \bug
        \date 2008-06-21 14:10:57, 조철희
    */
    BOOL bMatch=FALSE;
    _TOA *pStaggerLevel;

    if( pStaggerEmitter->uiStagDwellLevelCount <= 1 ) {
        return;
    }
    else {
        pStaggerLevel = & pStaggerEmitter->tStaggerDwellLevel[0];
        for( i=(int) (pStaggerEmitter->uiStagDwellLevelCount-1) ; i >= 0 ; --i ) {
            if( i == 0 ) {
                bMatch = TRUE;
                div = 1;
                for( k=0 ; k < pStaggerEmitter->uiStagDwellLevelCount-1 ; ++k ) {
                    if( CompMeanDiff<_TOA>( pStaggerLevel[k], pStaggerLevel[k+1], STABLE_MARGIN ) == FALSE ) {
                        bMatch = FALSE;
                        break;
                    }
                }
            }
            else if( pStaggerEmitter->uiStagDwellLevelCount % i == 0 ) {
                div = pStaggerEmitter->uiStagDwellLevelCount / i;

                bMatch = TRUE;
                for( j=0 ; j < div ; ++j ) {
                    for( k=0 ; k < (UINT)(i-1) ; ++k ) {
                        if( CompMeanDiff<_TOA>( pStaggerLevel[j], pStaggerLevel[div*(k+1)+j], STABLE_MARGIN ) == FALSE ) {
                            j = div;
                            bMatch = FALSE;
                            break;
                        }
                    }
                }
            }

            if( bMatch == TRUE ) {
                pStaggerEmitter->tFramePri = pStaggerEmitter->tFramePri / ( pStaggerEmitter->uiStagDwellLevelCount / div );
                pStaggerEmitter->uiStagDwellLevelCount = div;
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 ACF 상에서 찾은 후보 피크중에서 기준값 이상인 피크를 고른다. 그래서
//!					 피크 개수가 1개이면, 그 피크에 해당하는 타임 정보를 m_pRefFramePri[0] 에 저장한다.
//!					 그리고 피크 개수가 2개 이상이면, 제일 짧은 DTOA를 주기로 리턴한다.
//!	\author  조철희
//!	\return	 void
//! \version 1.0
//! \date		 2005-10-10 10:36:51
//! \warning
//
void CAnalPRI::FindPeak()
{
    unsigned int i, k;

    _TOA *pPeak;

    _TOA max_Toa_index=UINT64_MAX - 1;

    // 제일 큰 피크값을 가진 TOA 점을 찾는다.
    pPeak = & m_pCanPeak[0];
    m_nMaxPeak = 0;
    for( i=0 ; i < m_coCanPeak ; ++i ) {
        if( m_pToaAcf[ m_pCanPeak[i] ] > m_nMaxPeak ) {
            max_Toa_index = *pPeak;
            m_nMaxPeak = m_pToaAcf[ *pPeak ];
        }

        ++ pPeak;
    }
    /*! \bug  max_Toa_index 값을 못 찾으면 빠져 나온다.
        \date 2008-06-21 13:46:26, 조철희
    */
    if( max_Toa_index < 0 ) {
        // return;
    }
    else {
        // 피크점의 ACF값이 특정값 이상인 피크점들을 검색한다.
        UINT threshold_peak;

        /*! \bug  ACF에서 최소 피크 개수는 3개 이상으로 한다.
            \date 2006-05-18 14:26:48, 조철희
        */
        threshold_peak = _max( 3, UMUL( m_nMaxPeak, 0.8 ) );
        k = m_coCanPeak;
        m_coCanPeak = 0;
        pPeak = & m_pCanPeak[0];
        for( i=0 ; i < k ; ++i ) {
            if( m_pToaAcf[ *pPeak ] >= threshold_peak ) {
                m_pCanPeak[ m_coCanPeak++ ] = *pPeak;
            }
            ++ pPeak;
        }

    #ifdef _FIND_PEAK_
        int left_peak, right_peak;

        // 좌/우측 피크가 있는지 검사하고 큰 피크와 위에서 구한 피크점을 가지고 주기를 계산한다.
        if( max_peak_index >= 1 )  {
            // 좌측 피크 존재 확인.
            left_peak = m_pCanPeak[max_peak_index-1];
            if( max_peak_index+1 < m_coCanPeak ) {
                // 좌/우측 피크점이 모두 있을 때...
                right_peak = m_pCanPeak[max_peak_index+1];
                if( left_peak > right_peak ) {
                    k = m_pPulseToa[max_Toa_index] - m_pPulseToa[left_peak];
                    m_pRefFramePri[0] = _abs( k );
                }
                else {
                    k = m_pPulseToa[max_Toa_index] - m_pPulseToa[right_peak];
                    m_pRefFramePri[0] = _abs( k );
                }
            }
            else {
                // 좌측 피크점만 있을 때...
                k = m_pPulseToa[max_Toa_index] - m_pPulseToa[left_peak];
                m_pRefFramePri[0] = _abs( k );
            }
        }
        else {
            // 우측 피크점만 있을 때...
            if( max_peak_index+1 < m_coCanPeak ) {
                right_peak = m_pCanPeak[max_peak_index+1];
                k = m_pPulseToa[ max_Toa_index ] - m_pPulseToa[ right_peak ];
                m_pRefFramePri[0] = _abs( k );
            }
            else
                m_pRefFramePri[0] = m_pPulseToa[max_Toa_index];
        }
    #else
        // 스태거 분석에서 ACF상에서 피크점 찾기에 대한 에러.
        // 펄스열이 앞 부분이 펄스열의 누락이 크면 N 배의 PRI를 찾을 수 있다.
        // 그래서 펄스열이 깨끗한 펄스열로 만들어서 스태거 분석을 하게 한다.
        //-- 조철희 2005-10-11 16:35:13 --//
        // ...
        // 피크점이 2개 이상일 때 제일 짧은 DTOA를 Frame PRI로 한다.
		if( m_coCanPeak == 0 ) {
		}
        else if( m_coCanPeak == 1 )
            m_pRefFramePri[0] = m_pPulseToa[max_Toa_index];
        else {
            _TOA min_dtoa;

            min_dtoa = 0xfffffffffffff;
            pPeak = & m_pCanPeak[0];
            for( i=0 ; i < m_coCanPeak-1 ; ++i ) {
                _TOA dtoa;

                dtoa = m_pPulseToa[ pPeak[0] ] - m_pPulseToa[ pPeak[1] ];
                //dtoa = _abs( dtoa );
                if( min_dtoa >= dtoa ) {
                    min_dtoa = dtoa;
                }
                ++ pPeak;
            }
            m_pRefFramePri[0] = min_dtoa;
        }
#endif
    }

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::CheckStaggerLevel
// 반환되는 형  : BOOL
// 함 수 인 자  : STR_EMITTER *pOrgEmitter
// 함 수 인 자  : STR_EMITTER *pStaggerEmitter
// 함 수 인 자  : int match_index
// 함 수 설 명  : 레벨별로 스태거 레벨 확인
// 최 종 변 경  : 조철희, 2005-09-28 17:20:41
//
BOOL CAnalPRI::CheckStaggerLevel( STR_EMITTER *pOrgEmitter, STR_EMITTER *pStaggerEmitter, int match_index )
{
    int i;
    int match;
    _TOA duration;
    int level_index;
    int stag_dwell_level_cnt;
    _TOA *pPulseDtoa;
    _TOA accum_dtoa;
    int level_count;

    STR_MINMAX_TOA pri;

    BOOL bRet=TRUE;

    int co_mismatch_backward, co_mismatch_forward;

    stag_dwell_level_cnt = pStaggerEmitter->uiStagDwellLevelCount;

    // 지터율을 계산해서 50% 이상이면 스태거 레벨은 실패로 한다.
    //-- 조철희 2005-11-25 17:51:58 --//
    /*! \bug  PRI 평균값 잘못 계산된 것을 수정함.
        \date 2007-06-18 14:07:18, 조철희
    */
    pri.tMean = pStaggerEmitter->tStaggerDwellLevel[0];

    _EQUALS4( pri.tMean, pri.tMin, pri.tMax, pStaggerEmitter->tStaggerDwellLevel[0] )
    
    for( i=1 ; i < (int) pStaggerEmitter->uiStagDwellLevelCount && i < MAX_FREQ_PRI_STEP ; ++i ) {
        pri.tMin = _min( pri.tMin, pStaggerEmitter->tStaggerDwellLevel[i] );
        pri.tMax = _max( pri.tMax, pStaggerEmitter->tStaggerDwellLevel[i] );
        pri.tMean += pStaggerEmitter->tStaggerDwellLevel[i];
    }

    /*! \bug  PRI 변화폭은 STABLE_MARGIN 보다 커야 한다.
        \date 2006-07-05 16:17:03, 조철희
    */
    if( ( pri.tMax - pri.tMin ) <= STABLE_MARGIN ) {
        bRet = FALSE;
    }
    else {
        pri.tMean = UDIV( pri.tMean, pStaggerEmitter->uiStagDwellLevelCount );
        int jitter_r = UDIV( 100 * ( pri.tMax - pri.tMin ), pri.tMean );
        if( jitter_r >= MAX_JITTER_P ) {
            bRet = FALSE;
        }
        else {
            level_count = 0;

            // 펄스열의 시간 차이를 구한다.
            duration = m_pTOA[ pStaggerEmitter->stPDW.pIndex[pStaggerEmitter->stPDW.uiCount-1] ] - m_pTOA[ pStaggerEmitter->stPDW.pIndex[0] ];

            // 역방향으로 스태거 레벨을 검사한다.
            level_index = stag_dwell_level_cnt - 1;
            co_mismatch_backward = 0;
            if( match_index >= 1 ) {
                pPulseDtoa = & m_pPulseDtoa[match_index-1];
                for( i=match_index-1 ; i >= 0 ; --i ) {
                    accum_dtoa = 0;
                    do {
                        accum_dtoa += pStaggerEmitter->tStaggerDwellLevel[level_index];
                        -- level_index;
                        if( level_index < 0 ) {
                            level_index = stag_dwell_level_cnt - 1;
                            ++ level_count;
                        }
                        level_index = level_index % stag_dwell_level_cnt;
                        if( TRUE == CompMeanDiff<_TOA>( *pPulseDtoa, accum_dtoa, STABLE_MARGIN ) ) {
                            break;
                        }

                        ++ co_mismatch_backward;

                        if( duration < accum_dtoa ) {
                            bRet = FALSE;
                            break;
                        }
                    }
                    while( TRUE );

                    if( bRet == FALSE ) {
                        break;
                    }

                    -- pPulseDtoa;
                }
            }

            // 순방향으로 스태거 레벨을 검사한다.
            if( bRet == TRUE ) {
                match = 0;
                level_index = 0;
                co_mismatch_forward = 0;
                pPulseDtoa = & m_pPulseDtoa[match_index];
                for( i=match_index ; i < (int) pStaggerEmitter->stPDW.uiCount-1 ; ++i ) {
                    accum_dtoa = 0;
                    do {
                        accum_dtoa += pStaggerEmitter->tStaggerDwellLevel[level_index];
                        ++ level_index;
                        if( level_index == stag_dwell_level_cnt ) {
                            level_index = 0;
                            ++ level_count;
                        }
                        // level_index = (++level_index) % stag_dwell_level_cnt;
                        if( TRUE == CompMeanDiff<_TOA>( *pPulseDtoa, accum_dtoa, STABLE_MARGIN ) ) {
                            ++ match;
                            break;
                        }

                        //-- 조철희 2005-10-27 15:26:44 --//
                        if( *pPulseDtoa < (UINT) accum_dtoa ) {
                            break;
                        }

                        ++ co_mismatch_forward;

                        if( duration < accum_dtoa ) {
                            bRet = FALSE;
                            break;
                        }
                    }
                    while( TRUE );

                    if( bRet == FALSE ) {
                        break;
                    }

                    ++ pPulseDtoa;
                }

                if( bRet == TRUE ) {
                    //////////////////////////////////////////////////////////////////////
                    // 메칭율을 정한다.
                    // int mis_match;
                    int /* mismatch_ratio, */ match_ratio;
                    int ratio_threshold;

                    // 추측한 레벨값으로 추출해서 펄스 추출율을 계산해본다.
                    //-- 조철희 2005-12-08 11:39:08 --//
                    match_ratio = UDIV( 100*match, pStaggerEmitter->stPDW.uiCount );

                    // mis_match = co_mismatch_forward + co_mismatch_backward;
                    // mismatch_ratio = UDIV( 100*pStaggerEmitter->pdw.count, pStaggerEmitter->pdw.count+mis_match );

                    // 매칭율 임계값은 두 주기간에 펄스 1개 미싱될 확률로 정한다.
                    // 즉, 스태거 레벨 개수가 N 이라고 하면
                    // threshold = ( 100 * ( 2*N-1 ) ) / (2*N) 의 확률로 한다.
                    if( pStaggerEmitter->stPDW.uiCount < _spAnalMinPulseJitterEmitter ) {
                        ratio_threshold = UDIV( 100 * (2 * stag_dwell_level_cnt - 1), 2 * stag_dwell_level_cnt );
                    }
                    else {
                        ratio_threshold = 10;
                    }

                    if( pStaggerEmitter->stPDW.uiCount >= _spAnalMinPulseCount &&
                        // pStaggerEmitter->pdw.count >= pOrgEmitter->pdw.count/2 &&
                        ( level_count >= MIN_REPEAT_STAGGER_LEVEL || match_ratio >= ratio_threshold ) &&
                        ( match_ratio > 40 ) ) {
                        bRet = TRUE;
                    }
                    else {
                        bRet = FALSE;
                    }
                }
            }
        }
    }

    return bRet;
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CAnalPRI::MergeGrouping
//! \author   조철희
//! \param    nAnalEmitter 인자형태 int
//! \return   void
//! \version  1.37
//! \date     2005-05-30 15:28:18
//! \warning
//
void CAnalPRI::MergeGrouping( int nAnalEmitter )
{
    unsigned int i, j;

    int nHarmonic;
    int nStartAnalEmitter;

    int nCompFreqLevel;
    UINT mergeOption;
    STR_EMITTER *pEmitter1, *pEmitter2;

    if( nAnalEmitter == ALL_MERGE )
        nStartAnalEmitter = 0;
    else
        nStartAnalEmitter = nAnalEmitter;

    // 유사한 에미터들에 대해서 병합한다.
    // Stable, Stagger 인 경우에도
    pEmitter1 = & m_Emitter[ nStartAnalEmitter ];
    for( i=nStartAnalEmitter ; i < m_uiCoEmitter ; ++i, ++pEmitter1 ) {
        if( pEmitter1->mark == NORMAL_EMITTER ) {
            pEmitter2 = & m_Emitter[ i+1 ];
            for( j=i+1 ; j < m_uiCoEmitter ; ++j, ++pEmitter2 ) {
                if( pEmitter2->mark != NORMAL_EMITTER )
                    continue;

                nCompFreqLevel = CompFreqLevel( pEmitter1, pEmitter2 );

                if( nCompFreqLevel == FIXED_TYPE || nCompFreqLevel == AGILE_TYPE ) {
                    nHarmonic = CheckHarmonicPW( pEmitter1, pEmitter2 );

                    if( 0 != nHarmonic ) {
                        // TRUE == IncludePulseTrain( pEmitter1, pEmitter2 ) ) {
                        // 에미터 간의 병합을 수행한다.
                        if( TRUE == SelectMainEmitter( pEmitter1, pEmitter2, & mergeOption ) )
                            MergeEmitter( pEmitter1, pEmitter2, mergeOption );
                        else {
                            MergeEmitter( pEmitter2, pEmitter1, mergeOption );
                            break;
                        }
                    }
                }
                else if( nCompFreqLevel == FORCED_FIXED ) {
                    if( 0 != CheckHarmonicPW( pEmitter1, pEmitter2 ) ) {
                        MergeEmitter( pEmitter1, pEmitter2, NO_MERGE );
                    }
                }
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::CompFreq
// 반환되는 형  : BOOL
// 함 수 인 자  : STR_PULSE_TRAIN_SEG *pSeg1
// 함 수 인 자  : STR_PULSE_TRAIN_SEG *pSeg2
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-07-15 09:43:06
//
//##ModelId=42E85F3B0104
BOOL CAnalPRI::CompFreq( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 )
{
    BOOL bRet=FALSE;

    if( pSeg1->uiFreqType == _RANDOM_AGILE ) {
        /*
        int diff;
        int agiFrq;

        diff = _min( pSeg1->freq.max - pSeg1->freq.min, pSeg2->freq.max - pSeg2->freq.min );
        // debug, 00-02-03 09:36:22
        agiFrq = _max( UDIV( 50*diff, 100 ), _sp.mg.agifrqpat[pSeg1->band] );

        if( TRUE == CompMarginDiff( pSeg1->freq.mean, pSeg2->freq.min, pSeg2->freq.max, agiFrq ) &&
                TRUE == CompMarginDiff( pSeg2->freq.mean, pSeg1->freq.min, pSeg1->freq.max, agiFrq ) ) {
            if( TRUE == CompMeanDiff( pSeg1->freq.min, pSeg1->freq.min, agiFrq ) &&
                    TRUE == CompMeanDiff( pSeg2->freq.max, pSeg2->freq.max, agiFrq ) )
                return TRUE;
        }
        */
        /*! \bug  펄스열 단계에서 Agile 주파수 비교는 무조건 TRUE 로 한다.
            \date 2006-08-10 16:06:40, 조철희
        */
        bRet = TRUE;
    }
    else {
#if defined(_ELINT_) || defined(_XBAND_)
        if( TRUE == CompMeanDiff<_TOA>( pSeg1->freq.iMean, pSeg2->freq.iMean, _sp.mg.fixfrq[pSeg1->uiBand] ) ) {
#else
        if( TRUE == CompMeanDiff<_TOA>( pSeg1->freq.iMean, pSeg2->freq.iMean, _sp.mg.fixfrq[pSeg1->uiBand] ) ) {
#endif
            bRet = TRUE;
        }
    }

    return bRet;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::CompAoa
// 반환되는 형  : BOOL
// 함 수 인 자  : STR_PULSE_TRAIN_SEG *pSeg1
// 함 수 인 자  : STR_PULSE_TRAIN_SEG *pSeg2
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2007-06-18 13:41:50
//
BOOL CAnalPRI::CompAoa( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 )
{
    BOOL bRet=FALSE;

    if( TRUE == CompAoaDiff<int>( pSeg1->aoa.iMean, pSeg2->aoa.iMean, _sp.mg.aoa[pSeg1->uiBand] ) ) {
        bRet = TRUE;
    }

    return bRet;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::CompFreqLevel
// 반환되는 형  : UINT
// 함 수 인 자  : STR_EMITTER *pEmitter1
// 함 수 인 자  : STR_EMITTER *pEmitter2
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-07-15 01:20:25
//
//##ModelId=42E85F3B0227
ANAL_FREQ_TYPE CAnalPRI::CompFreqLevel( STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2 )
{
    ANAL_FREQ_TYPE enRet=NOT_MATCH;
    STR_PULSE_TRAIN_SEG *pSeg1, *pSeg2;

    // 주파수 형태 비교 판단한다.
    if (pEmitter1->stFreq.iType == _FIXED && pEmitter2->stFreq.iType != _FIXED) {

    }
    else if (pEmitter1->stFreq.iType == _RANDOM_AGILE && (pEmitter2->stFreq.iType != _RANDOM_AGILE || pEmitter2->stFreq.iType != _PATTERN_AGILE)) {

    }
    else if (pEmitter1->stFreq.iType == _PATTERN_AGILE && (pEmitter2->stFreq.iType != _RANDOM_AGILE || pEmitter2->stFreq.iType != _PATTERN_AGILE)) {
    }
#if defined(_ELINT_) || defined(_XBAND_)
#elif defined(_POCKETSONATA_)
#else
    else if (pEmitter1->stFreq.iType == _PMOP && pEmitter2->stFreq.iType != _PMOP) {
    }
    else if (pEmitter1->stFreq.iType == _CHIRP_UP && pEmitter2->stFreq.iType != _CHIRP_UP) {
    }
    else if (pEmitter1->stFreq.iType == _CHIRP_DN && pEmitter2->stFreq.iType != _CHIRP_DN) {
    }
#endif
    else if (pEmitter1->stFreq.iType == _HOPPING || pEmitter2->stFreq.iType == _HOPPING) {
    }

    pSeg1 = & m_pSeg[ pEmitter1->uiMainSeg ];
    pSeg2 = & m_pSeg[ pEmitter2->uiMainSeg ];

    // 주파수 고정형 비교
    if( pEmitter1->stFreq.iType == _FIXED && pEmitter2->stFreq.iType == _FIXED ) {
        if( TRUE == CompMeanDiff<_TOA>( pSeg1->freq.iMean, pSeg2->freq.iMean, _sp.mg.fixfrq[pSeg1->uiBand] ) ) {
            enRet = FIXED_TYPE;
        }
    }
    // 주파수 변동형 비교
    else if( ( pEmitter1->stFreq.iType == _RANDOM_AGILE || pEmitter1->stFreq.iType == _PATTERN_AGILE ) ||
                     ( pEmitter2->stFreq.iType == _RANDOM_AGILE || pEmitter2->stFreq.iType == _PATTERN_AGILE ) ) {
        int diff, agiFrq;

        diff = _min( pSeg1->freq.iMax - pSeg1->freq.iMin, pSeg2->freq.iMax - pSeg2->freq.iMin );
        // debug, 00-02-03 09:36:22
        agiFrq = _max( UDIV( 50*diff, 100 ), _sp.mg.agifrqpat[pSeg1->uiBand] );

        if( TRUE == CompMarginDiff<int>( pSeg1->freq.iMean, pSeg2->freq.iMin, pSeg2->freq.iMax, agiFrq ) &&
            TRUE == CompMarginDiff<int>( pSeg2->freq.iMean, pSeg1->freq.iMin, pSeg1->freq.iMax, agiFrq ) ) {
            if( TRUE == CompMeanDiff<int>( pSeg1->freq.iMin, pSeg1->freq.iMin, agiFrq ) &&
                TRUE == CompMeanDiff<int>( pSeg2->freq.iMax, pSeg2->freq.iMax, agiFrq ) )
                enRet = AGILE_TYPE;
        }
    }

    return enRet;
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CAnalPRI::CalcEmitterPW
//! \author   조철희
//! \param    pEmitter 인자형태 STR_EMITTER *
//! \return   void
//! \version  1.37
//! \date     2006-08-29 14:20:27
//! \warning
//
void CAnalPRI::CalcEmitterPW( STR_EMITTER *pEmitter )
{
    int i, count;
    STR_MINMAX *pPw;
    PDWINDEX *pPdwIndex;

    pPdwIndex = pEmitter->stPDW.pIndex;
    count = pEmitter->stPDW.uiCount;
    pPw = & pEmitter->stPW;
    _EQUALS4( pPw->iMin, pPw->iMax, pPw->iMean, m_pPW[ *pPdwIndex ] )
    pPdwIndex++;
    for( i=1 ; i < count ; ++i ) {
        int pw;

        pw = m_pPW[ *pPdwIndex++ ];

        pPw->iMin = _min( pPw->iMin, pw );
        pPw->iMax = _max( pPw->iMax, pw );

        pPw->iMean += pw;
    }

    pPw->iMean = UDIV( pPw->iMean, count );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::CalcEmitterFrq
// 반환되는 형  : void
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-07-15 01:48:35
//
//##ModelId=42E85F3B01B8
void CAnalPRI::CalcEmitterFrq( STR_EMITTER *pEmitter )
{
    int i, count;
    STR_TYPEMINMAX *pFrq;
    PDWINDEX *pPdwIndex;

    pPdwIndex = pEmitter->stPDW.pIndex;
    count = pEmitter->stPDW.uiCount;
    pFrq = & pEmitter->stFreq;
    _EQUALS4( pFrq->iMin, pFrq->iMax, pFrq->iMean, m_pFREQ[ *pPdwIndex ] )
    pPdwIndex ++;
    for( i=1 ; i < count ; ++i ) {
        int freq;

        freq = m_pFREQ[ *pPdwIndex++ ];

        pFrq->iMin = _min( pFrq->iMin, freq );
        pFrq->iMax = _max( pFrq->iMax, freq );

        //pFrq->mean += freq;
    }

    // 주파수 평균은 Median 값으로 한다.
    //-- 조철희 2005-11-01 14:10:03 --//
    //pFrq->mean = UDIV( pFrq->mean, count );
    pFrq->iMean = MedianFreq( & pEmitter->stFreq, pEmitter->stPDW.pIndex, pEmitter->stPDW.uiCount );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::CalcEmitterPri
// 반환되는 형  : void
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-10-28 15:32:52
//
void CAnalPRI::CalcEmitterPri( STR_EMITTER *pEmitter )
{
    unsigned int i;
    UINT count=0;
    UINT *pIdxSeg;
    STR_PULSE_TRAIN_SEG *pSeg;

    pEmitter->stPRI.tMean = 0;
    pEmitter->stPRI.tMax = 0;
    pEmitter->stPRI.tMin = 0xffffff;

    pIdxSeg = & pEmitter->uiSegIdx[0];
    for( i=0 ; i < pEmitter->uiCoSeg ; ++i ) {
        pSeg = & m_pSeg[ *pIdxSeg++ ];

        pEmitter->stPRI.tMax = _max( pEmitter->stPRI.tMax, pSeg->pri.tMax );
        pEmitter->stPRI.tMin = _min( pEmitter->stPRI.tMin, pSeg->pri.tMin );
        pEmitter->stPRI.tMean += ( pSeg->pri.tMean * pSeg->pdw.uiCount );

        count += pSeg->pdw.uiCount;
    }
    pEmitter->stPRI.tMean = UDIV( pEmitter->stPRI.tMean, count );


}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CAnalPRI::MergeEmitter
//!	\author  조철희
//!	\param	 pDstEmitter	인자형태 STR_EMITTER *
//!	\param	 pSrcEmitter	인자형태 STR_EMITTER *
//!	\param	 nOption	인자형태 UINT
//!	\return	 void
//! \version 1.37
//! \date		 2006-07-26 15:11:23
//! \warning
//
void CAnalPRI::MergeEmitter(STR_EMITTER *pDstEmitter, STR_EMITTER *pSrcEmitter, UINT nOption )
{
    pSrcEmitter->mark = DELETE_EMITTER;

    if( nOption == MERGE ) {
        memcpy( & pDstEmitter->uiSegIdx[pDstEmitter->uiCoSeg], pSrcEmitter->uiSegIdx, sizeof(UINT)*pSrcEmitter->uiCoSeg );
        pDstEmitter->uiCoSeg += pSrcEmitter->uiCoSeg;

        pDstEmitter->uiMainSeg = pSrcEmitter->uiMainSeg;

        MergePdwIndexInSeg( pDstEmitter );

        pDstEmitter->stPRI.tMin = _min( pDstEmitter->stPRI.tMin, pSrcEmitter->stPRI.tMin );
        pDstEmitter->stPRI.tMax = _max( pDstEmitter->stPRI.tMax, pSrcEmitter->stPRI.tMax );
        pDstEmitter->stPRI.tMean = MulDiv64( 1, pDstEmitter->stPRI.tMean+pSrcEmitter->stPRI.tMean, 2 );
        //_mul128( )
    }
}

void CAnalPRI::SwapEmitter(STR_EMITTER *pDstEmitter, STR_EMITTER *pSrcEmitter )
{
    if( pDstEmitter != pSrcEmitter ) {
        STR_EMITTER backupEmitter;

        memcpy( & backupEmitter, pDstEmitter, sizeof(STR_EMITTER) );
        memcpy( pDstEmitter, pSrcEmitter, sizeof(STR_EMITTER) );
        memcpy( pSrcEmitter, & backupEmitter, sizeof(STR_EMITTER) );

    }

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::SelectMainEmitter
// 반환되는 형  : BOOL
// 함 수 인 자  : STR_EMITTER *pEmitter1
// 함 수 인 자  : STR_EMITTER *pEmitter2
// 함 수 인 자  : UINT *pMrgOption
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-06-03 21:45:50
//
//##ModelId=42A55D55037A
BOOL CAnalPRI::SelectMainEmitter(STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2, UINT *pMrgOption )
{
    // 아래의 조건은 에미터1으로 병합될 조건이다.
    // 비교할 에미터의 PRI 타입이 Stagger 일 경우에는 많은 펄스수를 가진 에미터로 선택한다.
    // 에미터1이 Stagger 이고 에미터2가 Stable 일 경우에는 에미터 1으로 병합된다.
    // 그리고 에미터1이 Stable이고 에미터2가 Stagger일 경우에는 에미터 2로 병합을 수행한다.
    *pMrgOption = MERGE;
    if( pEmitter1->enPRIType == _STAGGER && pEmitter2->enPRIType == _STAGGER ) {
        if( pEmitter1->stPDW.uiCount > pEmitter2->stPDW.uiCount )
            return TRUE;
    }
    else if( pEmitter1->enPRIType == _STABLE && pEmitter2->enPRIType == _STABLE ) {
        *pMrgOption = NO_MERGE;
        if( pEmitter1->stPDW.uiCount > pEmitter2->stPDW.uiCount )
            return TRUE;
    }
    else if( pEmitter1->enPRIType == _STAGGER ) {
        *pMrgOption = NO_MERGE;
        return TRUE;
    }
    else if( pEmitter2->enPRIType == _STAGGER ) {
        *pMrgOption = NO_MERGE;
        return FALSE;
    }
    else if( pEmitter1->enPRIType == _JITTER_RANDOM && pEmitter2->enPRIType == _JITTER_RANDOM ) {
        STR_MINMAX_TOA *pSegPri1, *pSegPri2;

        pSegPri1 = & m_pSeg[ pEmitter1->uiMainSeg ].pri;
        pSegPri2 = & m_pSeg[ pEmitter2->uiMainSeg ].pri;

        if( 0 != CalOverlapSpace<_TOA>( pSegPri1->tMax, pSegPri1->tMin, pSegPri2->tMax, pSegPri2->tMin ) ) {
            if( pEmitter1->stPDW.uiCount > pEmitter2->stPDW.uiCount ) {
                return TRUE;
            }
        }
        else if( pSegPri1->tMax < pSegPri2->tMax ) {
            return TRUE;
        }
    }
    else if( ( pEmitter1->enPRIType == _STABLE && pEmitter2->enPRIType == _JITTER_RANDOM ) ||
                     ( pEmitter1->enPRIType == _JITTER_RANDOM && pEmitter2->enPRIType == _STABLE ) ) {
        if( pEmitter1->stPDW.uiCount > pEmitter2->stPDW.uiCount )
            return TRUE;
    }

    return FALSE;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::CheckFramePRI
// 반환되는 형  : UINT
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-06-09 16:24:43
//
//##ModelId=42AF7FEE034B
_TOA CAnalPRI::CheckFramePRI(STR_EMITTER *pEmitter)
{
    int i;
    int coPdw;
    int max, max_index;

    ExtractFramePri( & pEmitter->stPDW, pEmitter->tFramePri );

    max = MIN_STAGGER_LEVEL_PERIOD;
    max_index = -1;
    printf( "\n CheckFramePRI" );
    for( i=0 ; i < m_nRefFramePri ; ++i ) {
        // coPdw = m_pNewSigAnal->ExtractFramePri( & m_pSeg[ pEmitter->main_seg ].pdw, m_RefFramePri[i] );
        coPdw = ExtractFramePri( & pEmitter->stPDW, m_pRefFramePri[i] );
        printf( "[%lld, %d]" , m_pRefFramePri[i], coPdw );
        if( max <= coPdw ) {
            max_index = i;
            max = coPdw;
        }
    }

    if( max_index < 0 )
        return 0;
    else {
        // pEmitter->coFramePri = max;
        return m_pRefFramePri[max_index];
    }
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::FindRefFramePri
// 반환되는 형  : BOOL
// 함 수 인 자  : UINT dtoa
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-06-09 18:03:19
//
//##ModelId=42AF7FEE02E7
BOOL CAnalPRI::FindRefFramePri(UINT dtoa)
{
    BOOL bRet=FALSE;
    int i, j;
    _TOA *pRefFramePri;

    pRefFramePri = & m_pRefFramePri[0];
    for( i=0 ; i < m_nRefFramePri ; ++i, ++pRefFramePri ) {
        if( 0 != CheckHarmonic( *pRefFramePri, dtoa ) ) {
            if( *pRefFramePri > dtoa ) {
                _TOA *pTmpFramePri;

                *pRefFramePri = dtoa;

                pTmpFramePri = & pRefFramePri[1];
                for( j=i+1 ; j < m_nRefFramePri ; ++j, ++pTmpFramePri ) {
                    if( 0 != CheckHarmonic( *pTmpFramePri, dtoa ) ) {
                        *pTmpFramePri = (UINT) -1;
                    }
                }
            }
            bRet = TRUE;
            break;
        }
    }

    return bRet;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::IncludePulseTrain
// 반환되는 형  : BOOL
// 함 수 인 자  : STR_EMITTER *pEmitter1
// 함 수 인 자  : STR_EMITTER *pEmitter2
// 함 수 설 명  :
// 최 종 변 경  : RSA노트북, 2005-06-30 16:00:43
//
//##ModelId=42D3079D0232
BOOL CAnalPRI::IncludePulseTrain( STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2 )
{
    int i;
    UINT match;
    int src_count, dst_count;

    STR_EMITTER *pSrcEmitter, *pDstEmitter;

    if( pEmitter1->stPDW.uiCount < pEmitter2->stPDW.uiCount ) {
        pSrcEmitter = pEmitter1;
        pDstEmitter = pEmitter2;
    }
    else {
        pSrcEmitter = pEmitter2;
        pDstEmitter = pEmitter1;
    }

    src_count = pSrcEmitter->stPDW.uiCount;
    dst_count = pDstEmitter->stPDW.uiCount;

    match = 0;
    for( i=0 ; i < src_count ; ++i ) {
        int search_value;

        search_value = pSrcEmitter->stPDW.pIndex[i];
        m_pBinSearchIndex = pDstEmitter->stPDW.pIndex;
        if( TRUE == BinSearchInPdwIndex( 0, dst_count, search_value ) )
            ++ match;
    }

    // UINT ratio=UDIV( src_count*70, 100 );
    if( match >= UDIV( src_count*7, 100 ) )
        return TRUE;
    else
        return FALSE;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::BinSearchInPdwIndex
// 반환되는 형  : BOOL
// 함 수 인 자  : int from
// 함 수 인 자  : int to
// 함 수 인 자  : int search_value
// 함 수 설 명  :
// 최 종 변 경  : RSA노트북, 2005-06-30 16:16:43
//
//##ModelId=42D3079D00F1
BOOL CAnalPRI::BinSearchInPdwIndex(int iFrom, int iTo, int search_value)
{
    int iCount;
    int iMid;

    BOOL bRet=TRUE;

    iCount = _spZero;
    iMid = (iFrom + iTo ) / 2;
    while( TRUE ) {
        ++ iCount;

        if( search_value < m_pBinSearchIndex[iMid] ) {
            iTo = iMid - 1;
            iMid = (iTo + iFrom ) / 2;
        }
        else if( search_value > m_pBinSearchIndex[iMid] ) {
            iFrom = iMid + 1;
            iMid = (iTo + iFrom) / 2;
        }
        else if( search_value == m_pBinSearchIndex[iMid] ) {
            break;
        }

        if(iCount > iTo ) {
            bRet = FALSE;
            break;
        }
            
    }

    return bRet;
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CAnalPRI::CalPRIRange
//!	\author  조철희
//!	\param	 pSeg	인자형태 STR_PULSE_TRAIN_SEG *
//!	\param	 priMean	인자형태 UINT
//!	\param	 dtoa_count	인자형태 UINT
//!	\return	 void
//! \version 1.0
//! \date		 2006-07-06 14:14:56
//! \warning
//
void CAnalPRI::CalPRIRange( STR_PULSE_TRAIN_SEG *pSeg, _TOA priMean, UINT dtoa_count )
{
    STR_LOWHIGH bin;

    // 지터이고 펄스개수가 특정 개수 이상일 때 PRI 범위를 계산한다.
    if( pSeg->enPriType == _JITTER_RANDOM && pSeg->pdw.uiCount >= _spAnalMinPulseJitterEmitter ) {
        MakeDtoaHistogram( pSeg->pdw.pIndex, pSeg->pdw.uiCount, & pSeg->pri );

        RemoveNoiseDtoa( pSeg->pdw.uiCount );

        if( GetDtoaRange( pSeg, & bin ) == TRUE ) {
            CalDtoaMeanMinMax( pSeg, & bin );
        }
        else {
            MakeDtoaHistogram( pSeg->pdw.pIndex, pSeg->pdw.uiCount, & pSeg->pri );
            GetDtoaRange( pSeg, & bin );
            printf( "\n 히스토그램 상에서 피크를 찾을 수 없어서 이전에 계산한 PRI 로 정한다." );
        }
    }
    else {
        /*
         \bug  평균값은 메디안 계산 방법에서 DTOA 평균값으로 대신한다.
                            D:\RSA-TFT\소나타 ES TFT\해상 신호\A20-2Step\jitter_2step.pdw 에서
                            메디안 계산 방법은 PRI 평균값이 잘못됨.
                \date 2006-07-19 14:06:06, 조철희
                */

        /*
        if( pSeg->pri_type == _JITTER )
            pSeg->pri.mean = VerifyPRI( pSeg->pdw.pIndex, pSeg->pdw.count; );
        else
        */
        pSeg->pri.tMean = UDIV( priMean, dtoa_count );
    }
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CAnalPRI::RemoveNoiseDtoa
//!	\author  조철희
//!	\param	 count	인자형태 UINT
//!	\return	 void
//! \version 1.0
//! \date		 2006-07-19 19:10:45
//! \warning
//
void CAnalPRI::RemoveNoiseDtoa( UINT count )
{
    int i;
    int unpass_count, start;

    PDWINDEX *pHistIndex;
    PDWINDEX *pEndHistIndex;

    /*! \bug  DTOA 히스토그램의 overflow로 인해서 제거를 수행하지 않게 함.
        \date 2006-08-16 11:09:19, 조철희
    */
    if( m_DtoaHist.bin_range.iLow == 0xfffffff || m_DtoaHist.bin_range.iHgh == -1 )
        return;

    // 히스트그램에서 짜를 BIN 개수는 총 펄스개수의 10% 로 한다.
    unpass_count = UDIV( count * 10, 200 );

    // 좌측부터 우측방향으로 가면서 짜른다.
    pEndHistIndex = & m_DtoaHist.hist[DTOA_BIN-1];
    start = m_DtoaHist.bin_range.iLow;
    pHistIndex = & m_DtoaHist.hist[start];
    for( i=start ; i < start+unpass_count ; ++i ) {
        if( *pHistIndex == 0 ) {
            while( *pHistIndex == 0 ) {
                if( pHistIndex == pEndHistIndex )
                    return;
                ++ pHistIndex;
            }
        }
        -- *pHistIndex;
    }

    // 우측부터 좌측방향으로 가면서 짜른다.
    pEndHistIndex = & m_DtoaHist.hist[0];
    start = m_DtoaHist.bin_range.iHgh;
    pHistIndex = & m_DtoaHist.hist[start];
    for( i=start ; i > start-unpass_count ; --i ) {
        if( *pHistIndex == 0 ) {
            while( *pHistIndex == 0 ) {
                if( pHistIndex == pEndHistIndex )
                    return;
                -- pHistIndex;
            }
        }
        -- *pHistIndex;
    }
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CAnalPRI::CalDtoaMinMax
//!	\author  조철희
//!	\param	 pSeg	인자형태 STR_PULSE_TRAIN_SEG *
//!	\param	 pRange	인자형태 STR_LOWHIGH *
//!	\return	 void
//! \version 1.0
//! \date		 2006-07-19 11:56:57
//! \warning
//
void CAnalPRI::CalDtoaMeanMinMax( STR_PULSE_TRAIN_SEG *pSeg, STR_LOWHIGH *pRange )
{
    int i, count;
    int index;

    int dtoa_count;
    _TOA sum_dtoa;

    _TOA toa, pre_toa, dtoa;

    PDWINDEX *pIndex;

    m_DtoaHist.bin_range.iHgh = 0;
    m_DtoaHist.bin_range.iLow = 0xfffffff;

    pSeg->pri.tMax = 0;
    pSeg->pri.tMin = 0xffffff;

    dtoa_count = 0;
    sum_dtoa = 0;
    pIndex = pSeg->pdw.pIndex;
    pre_toa = m_pTOA[ *pIndex++ ];
    count = pSeg->pdw.uiCount;
    for( i=1 ; i < count ; ++i ) {
        toa = m_pTOA[ *pIndex++ ];
        dtoa = toa - pre_toa;
        index = F_UDIV( dtoa, DTOA_RES );

        // DTOA_BIN 이내에 든 것만 히스토그램을 작성한다.
        if( pRange->iLow <= index && pRange->iHgh >= index ) {
            pSeg->pri.tMax =_max( pSeg->pri.tMax, dtoa );
            pSeg->pri.tMin =_min( pSeg->pri.tMin, dtoa );

            ++ dtoa_count;
            sum_dtoa += dtoa;
        }
        pre_toa = toa;
    }

    pSeg->pri.tMean = UDIV( sum_dtoa, dtoa_count );
    m_DtoaHist.bin_count = DTOA_BIN - 1;
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CAnalPRI::GetDtoaRange
//!	\author  조철희
//!	\param	 pSeg	인자형태 STR_PULSE_TRAIN_SEG *
//!	\param	 pRange	인자형태 STR_LOWHIGH *
//!	\return	 BOOL
//! \version 1.0
//! \date		 2006-07-24 09:04:43
//! \warning
//
BOOL CAnalPRI::GetDtoaRange( STR_PULSE_TRAIN_SEG *pSeg, STR_LOWHIGH *pRange )
{
    int i;
    int start, end;

    PDWINDEX *pHistIndex;

    BOOL bRet = TRUE;

    /*! \bug  DTOA 히스토그램의 overflow로 인해서 제거를 수행하지 않게 함.
        \date 2006-08-16 11:09:19, 조철희
    */
    if( m_DtoaHist.bin_range.iLow == 0xfffffff || m_DtoaHist.bin_range.iHgh == -1 ) {
        bRet = FALSE;
    }
    else {
        _EQUALS3( pRange->iLow, pRange->iHgh, -1 )

        start = m_DtoaHist.bin_range.iLow;
        end = m_DtoaHist.bin_range.iHgh;
        pHistIndex = & m_DtoaHist.hist[start];
        for( i=start ; i <= end ; ++i ) {
            if( *pHistIndex++ != 0 ) {
                pRange->iLow = i;
                break;
            }
        }

        pHistIndex = & m_DtoaHist.hist[end];
        for( i=end ; i >= start ; --i ) {
            if( *pHistIndex-- != 0 ) {
                pRange->iHgh = i;
                break;
            }
        }

        if( pRange->iLow == -1 || pRange->iHgh == -1 ) {
            bRet = FALSE;
        }
    }

    return bRet;
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CAnalPRI::GetDtoaRange
//!	\author  조철희
//!	\param	 peak_index	인자형태 int
//!	\param	 pRange	인자형태 STR_LOWHIGH *
//!	\return	 BOOL
//! \version 1.0
//! \date		 2006-07-06 17:43:23
//! \warning
//
BOOL CAnalPRI::GetDtoaRange( int peak_index, STR_LOWHIGH *pRange )
{
    int i;

    pRange->iLow = 0;
    pRange->iHgh = 0;

    //////////////////////////////////////////////////////////////////////
    // peak부터 좌로 범위를 설정
    // 좌측의 경계 찾기 (start)
    for( i=peak_index-1 ; i >= 0 ; --i ) {
        // 경계 조건
        if( m_DtoaHist.hist[i] <= 2 ) {
            pRange->iLow = i + 1;
            break;
        }
    }

    //////////////////////////////////////////////////////////////////////
    // peak부터 우로 범위를 설정
    for( i=peak_index+1 ; i < (int) m_DtoaHist.bin_count ; ++i ) {
        // 경계 조건
        if( m_DtoaHist.hist[i] <= 2 ) {
            pRange->iHgh = i - 1;
            break;
        }
    }

    if( pRange->iHgh == 0 )
        return FALSE;
    else {
        int diff, ratio;

        diff = ( pRange->iHgh - pRange->iLow ) + 1;
        ratio = UDIV( diff*100, peak_index );
        if( ratio > MAX_JITTER_P ) {
            printf( "\n [W] PRI를 계산하는 데 있어서 지터율을 초과했습니다." );
            WhereIs;
            return FALSE;
        }
    }

    return TRUE;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::OverlappedSeg
// 반환되는 형  : BOOL
// 함 수 인 자  : STR_PULSE_TRAIN_SEG *pSeg1
// 함 수 인 자  : STR_PULSE_TRAIN_SEG *pSeg2
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-06-01 15:30:57
//
//##ModelId=428C21350079
bool CAnalPRI::OverlappedSeg( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 )
{
    UINT ratio;
	bool bRet = false;
    _TOA overlapToa, diffToa;

    // 겹쳐진 영역중에서 누락 펄스열이 많이 존재하면 겹쳐지지 않은 것으로 해야 한다.
    //-- 조철희 2006-02-06 14:34:59 --//
    if( 0 != CalOverlapSpace<PDWINDEX>( pSeg1->last_idx, pSeg1->first_idx, pSeg2->last_idx, pSeg2->first_idx ) ) {
        if( pSeg1->last_idx < pSeg2->last_idx ) {
            overlapToa = pSeg1->tLast - pSeg2->tFirst;
		}
        else {
            overlapToa = pSeg2->tLast - pSeg1->tFirst;
		}

        diffToa = pSeg1->tLast - pSeg1->tFirst;
        ratio = UDIV( overlapToa * 100, diffToa );
        if( ratio >= THRESHOLD_OVERLAP ) {
            bRet = true;
		}

        diffToa = pSeg2->tLast - pSeg2->tFirst;
        ratio = UDIV( overlapToa * 100, diffToa );
        if( ratio >= THRESHOLD_OVERLAP ) {
            bRet = true;
		}

    }

    return bRet;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CAnalPRI::IMeanInArray
        \author   조철희
        \param    series 인자형태 int *
        \param    co 인자형태 UINT
        \return   float
        \version  0.0.1
        \date     2008-01-03 17:21:09
        \warning
*/
float CAnalPRI::IMeanInArray(int *series, UINT co)
{
    register UINT i;
    int sum;

    sum = 0;
    for( i=0 ; i < co ; ++i ) {
        sum += *series++;
    }

    return ( (float) sum / (float) co );
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CAnalPRI::MeanInArray
        \author   조철희
        \param    series 인자형태 UINT *
        \param    co 인자형태 UINT
        \return   float
        \version  0.0.1
        \date     2008-01-03 17:21:33
        \warning
*/
// float CAnalPRI::MeanInArray(UINT *series, UINT co)
// {
//     register UINT i;
//     UINT sum;
// 
//     sum = 0;
//     for( i=0 ; i < co ; ++i ) {
//         if( series != NULL ) {
//             sum += *series++;
//         }
//     }
// 
//     return ( (float) sum / (float) co );
// }


//////////////////////////////////////////////////////////////////////////
/*! \brief    CAnalPRI::CalHopLevel
        \author   조철희
        \param    pEmitter 인자형태 STR_EMITTER *
        \return   void
        \version  0.0.53
        \date     2008-10-30 16:05:13
        \warning
*/
void CAnalPRI::CalHopLevel( STR_EMITTER *pEmitter )
{
    int i, j, count, hop_count;
    int iBand;
    BOOL bMatch;

    PDWINDEX *pPdwIndex;
    int *pHopLevel;

    _EQUALS3( pEmitter->iCoHoppingLevel, hop_count, 0 )

    pPdwIndex = pEmitter->stPDW.pIndex;
    count = pEmitter->stPDW.uiCount;
    for( i=0 ; i < count ; ++i ) {
        int freq;

        freq = m_pFREQ[ *pPdwIndex++ ];

        bMatch = FALSE;
        pHopLevel = & pEmitter->iHopLevel[0];
        for( j=0 ; j < hop_count ; ++j ) {
            if( TRUE == CompMeanDiff( freq, *pHopLevel++, 10 ) ) {
                bMatch = TRUE;
                break;
            }
        }
        if( bMatch == FALSE ) {
            pEmitter->iHopLevel[hop_count] = freq;
            ++ hop_count;
            if( (UINT) hop_count > MAX_FREQ_PRI_STEP ) {
                printf( "\n [W] Hopping 레벨 값이 기본 레벨 크기를 초과했습니다." );
                hop_count = 0;
                // return;
            }
        }
    }

    if (hop_count != 0) {
        // 주파수 호핑 레벨값을 변환 값으로 저장한다.
        pHopLevel = &pEmitter->iHopLevel[0];
        pEmitter->iCoHoppingLevel = hop_count;
        iBand = m_pBAND[pEmitter->stPDW.pIndex[0]] + 1;
        for (i = 0; i < hop_count; ++i) {
            *pHopLevel = I_FRQMhzCNV(iBand, *pHopLevel);
            ++pHopLevel;
        }
    }

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CAnalPRI::DNSAnalysis
// 반환되는 형  : void
// 함 수 인 자  : void
// 함 수 설 명  : 
// 최 종 변 경  : 김용준, 2014-03-19 15:17:00
//
void CAnalPRI::DNSAnalysis()
{
	unsigned int i, j, k;
	unsigned int uiCount;
	STR_EMITTER *pEmitter1, *pEmitter2;
	BOOL bMakeEmitter, bFirst, bLevelExist;

	pEmitter1 = & m_Emitter[ m_uiAnalEmitter ];
	for( i=m_uiAnalEmitter ; i < m_uiCoEmitter ; ++i, ++ pEmitter1 ) {
		bMakeEmitter = FALSE;
		bFirst = TRUE;
		
        if (pEmitter1->mark == DELETE_EMITTER) {
            continue;
        }

		if (_STABLE != pEmitter1->enPRIType) {
			continue;
		}

		pEmitter2 = & m_Emitter[i+1];

		for (j = i+1; j < m_uiCoEmitter; ++j, ++ pEmitter2)
		{
			// 에미터1의 PRI 레벨 개수가 16을 넘는 경우 병합하지 않는다.
			if (pEmitter1->uiStagDwellElementCount >= MAX_STAGGER_LEVEL_ELEMENT) {
				break;
			}

			if (_STABLE != pEmitter2->enPRIType) {
				continue;
			}

			// D&S 병합 가능 여부를 판단한다.
			if (TRUE == CheckDNSPossibility(pEmitter1, pEmitter2)) {
				// 첫번째 병합이면 에미터1의 첫번째 레벨 값을 채운다.
				if (TRUE == bFirst)
				{
					pEmitter1->tStaggerDwellElement[ pEmitter1->uiStagDwellElementCount++ ] = pEmitter1->stSeg[pEmitter1->uiMainSeg].pri.tMean;
					bFirst = FALSE;
				}

				bMakeEmitter = TRUE;

				// 펄스열 인덱스 병합
				memcpy( & pEmitter1->uiSegIdx[pEmitter1->uiCoSeg], pEmitter2->uiSegIdx, sizeof(UINT)*(UINT)pEmitter2->uiCoSeg );
				memcpy( & pEmitter1->stSeg[pEmitter1->uiCoSeg], pEmitter2->stSeg, sizeof(STR_PULSE_TRAIN_SEG)*(UINT)pEmitter2->uiCoSeg );
				pEmitter1->uiCoSeg += pEmitter2->uiCoSeg;

				// 에미터1의 PRI 레벨 값을 확인하여 없는 값이면 추가한다.
				bLevelExist = FALSE;
				for (k = 0; k < pEmitter1->uiStagDwellLevelCount; k++)
				{
					if (TRUE == CompMeanDiff<_TOA>(pEmitter1->tStaggerDwellLevel[k], pEmitter2->stSeg[ pEmitter2->uiMainSeg ].pri.tMean, STABLE_MARGIN))
					{
						bLevelExist = TRUE;
						break;
					}
				}

				if (FALSE == bLevelExist) {
					pEmitter1->tStaggerDwellLevel[ pEmitter1->uiStagDwellLevelCount++ ] = pEmitter2->stSeg[ pEmitter2->uiMainSeg ].pri.tMean;
				}

				/*

				// PDW 개수가 많은 에미터의 main 펄스열을 병합되는 에미터의 main 펄스열로 설정
				if( pEmitter1->pdw.count < pEmitter2->pdw.count ) {
					pEmitter1->main_seg = pEmitter2->main_seg;
				}
				*/

				pEmitter2->mark = DELETE_EMITTER;

				// PRI 평균값 업데이트
                uiCount = pEmitter1->stPDW.uiCount + pEmitter2->stPDW.uiCount - 2;
				pEmitter1->stPRI.tMean = (pEmitter1->stPRI.tMean * (pEmitter1->stPDW.uiCount-1)) + (pEmitter2->stPRI.tMean * (pEmitter2->stPDW.uiCount-1));
				pEmitter1->stPRI.tMean = (int)UDIV( pEmitter1->stPRI.tMean, uiCount);

				// 에미터의 PRI 최대/최소값 재설정
				pEmitter1->stPRI.tMin = pEmitter1->tStaggerDwellLevel[0];
				pEmitter1->stPRI.tMax = pEmitter1->tStaggerDwellLevel[0];
				for (k = 1; k < pEmitter1->uiStagDwellLevelCount; k++)
				{
					pEmitter1->stPRI.tMin = _min(pEmitter1->stPRI.tMin, pEmitter1->tStaggerDwellLevel[k]);
					pEmitter1->stPRI.tMax = _max(pEmitter1->stPRI.tMax, pEmitter1->tStaggerDwellLevel[k]);
				}

			}
		}
		
		if (TRUE == bMakeEmitter)
		{
			MergePdwIndexInEmitter( pEmitter1 );

			// 주파수 범위 및 타입 결정
			CalcEmitterFrq( pEmitter1 );
			pEmitter1->enFreqType = AnalFreqType( pEmitter1 );

			// PRI 타입 결정
			if (pEmitter1->uiStagDwellLevelCount > _spOne ) {
				pEmitter1->enPRIType = _DWELL;
			}
			else {
				pEmitter1->enPRIType = _STABLE;
			}

			// PW 결정
			CalcEmitterPW( pEmitter1 );
		}
	}
}

/**
 * @brief		MergePdwIndexInEmitter
 * @param		STR_EMITTER * pEmitter
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2022/01/03 15:04:13
 * @warning		
 */
void CAnalPRI::MergePdwIndexInEmitter(STR_EMITTER *pEmitter)
{
    unsigned int i, j;
    UINT count, idx;
    PDWINDEX *pSegPdwIndex, *pEmitterPdwIndex;
    PDWINDEX *pMergePdwIndex;
    STR_PULSE_TRAIN_SEG *pSeg;

    pEmitter->stPDW.uiCount = 0;
    memset( m_pMergePdwIndex, 0, sizeof( unsigned char ) * (UINT) m_uiMaxPdw );
    for( i=0 ; i < pEmitter->uiCoSeg ; ++i ) {
        pSeg = & pEmitter->stSeg[i];
        count = (UINT)pSeg->pdw.uiCount;

        // memcpy( m_pMergePdwIndex+pEmitter->pdw.count, pSeg->pdw.pIndex, sizeof( PDWINDEX ) * pSeg->pdw.count );
        pSegPdwIndex = pSeg->pdw.pIndex;
        for( j=0 ; j < (int)count ; ++j ) {
            idx = *pSegPdwIndex++;

            //*(m_pMergePdwIndex+idx) = 1;
            m_pMergePdwIndex[idx] = 1;
        }
    }

    count = 0;
    pEmitterPdwIndex = pEmitter->stPDW.pIndex;
    pMergePdwIndex = m_pMergePdwIndex;
    for( i=0 ; i < m_uiMaxPdw ; ++i ) {
        if( *pMergePdwIndex++ == 1 ) {
            //*(pEmitterPdwIndex+count) = (UINT)i;
            *pEmitterPdwIndex++ = (UINT)i;
            ++ count;
        }
    }

    pEmitter->stPDW.uiCount = (int) count;
}

/**
 * @brief		CalcDiffAOA
 * @param		int iAOA1
 * @param		int iAOA2
 * @return		int
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2022/01/03 15:29:19
 * @warning		
 */
int CAnalPRI::CalcDiffAOA(int iAOA1, int iAOA2)
{
    int iDiffAOA;

    iDiffAOA = _diffabs<int>(iAOA1, iAOA2);
    if( iDiffAOA > MAX_AOA/2 ) {
        iDiffAOA = MAX_AOA - iDiffAOA;
    }

    return iDiffAOA;
}

/**
 * @brief		CheckOverlapSeg
 * @param		STR_EMITTER * pEmitter1
 * @param		STR_EMITTER * pEmitter2
 * @return		bool
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2022/01/03 15:29:15
 * @warning		
 */
bool CAnalPRI::CheckOverlapSeg(STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2)
{
    bool bResult = false;
    unsigned int i, j;

    for( i=0 ; i < pEmitter1->uiCoSeg ; i++ ) {
        for( j=0 ; j < pEmitter2->uiCoSeg ; j++) {
            // 에미터1과 에미터2의 펄스열이 겹치는지 확인한다.
            if (((pEmitter1->stSeg[i].tFirst < pEmitter2->stSeg[j].tLast) && (pEmitter1->stSeg[i].tFirst > pEmitter2->stSeg[j].tFirst)) ||
                ((pEmitter2->stSeg[j].tFirst < pEmitter1->stSeg[i].tLast) && (pEmitter2->stSeg[j].tFirst > pEmitter1->stSeg[i].tFirst))) {
                bResult = true;
                break;
            }
        }
    }

    return bResult;

}

/**
 * @brief		CheckDNSPossibility
 * @param		STR_EMITTER * pEmitter1
 * @param		STR_EMITTER * pEmitter2
 * @return		bool
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2022/01/03 14:58:45
 * @warning		
 */
bool CAnalPRI::CheckDNSPossibility(STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2)
{
    // bool bAOAResult = false, bTOAResult = false, bFreqResult = false, bResult = false;
    bool bResult = false;
    STR_MINMAX_SDEV stAOA1, stAOA2;

    CMakeAET* pMakeAET = GetMakeAET();

    pMakeAET->MakeAOAInfoFromSeg(&stAOA1, pEmitter1);
    pMakeAET->MakeAOAInfoFromSeg(&stAOA2, pEmitter2);

    /// 1. AOA의 평균값 차이가 마진을 벗어나면 병합 불가
    if (HOPPING_MERGE_AOA_MARGIN < CalcDiffAOA(stAOA1.iMean, stAOA2.iMean))
    {
        bResult = false;
    }
    /// 2. TOA가 겹치면 병합 불가
    else if (true == CheckOverlapSeg(pEmitter1, pEmitter2))
    {
        bResult = false;
    }
    /// 3. 주파수 형태가 유사하지 않으면 병합 불가
    else if (false == CheckFreqType(pEmitter1, pEmitter2))
    {
        bResult = false;
    }
    /// 4. 해당 사항 없으면 병합 가능
    else
    {
        bResult = true;
    }

    return bResult;

}

/**
 * @brief		CheckFreqType
 * @param		STR_EMITTER * pEmitter1
 * @param		STR_EMITTER * pEmitter2
 * @return		bool
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2022/01/03 15:31:20
 * @warning		
 */
bool CAnalPRI::CheckFreqType(STR_EMITTER *pEmitter1, STR_EMITTER *pEmitter2)
{
    bool bResult;

    // 에미터1이 주파수 고정인 경우 에미터2가 주파수 고정이고 주파수 값이 유사할 경우 매칭 판정
    if (pEmitter1->enFreqType == _FIXED)
    {
        if ((pEmitter2->enFreqType == _FIXED) && (TRUE == CompMeanDiff(pEmitter1->stFreq.iMean, pEmitter2->stFreq.iMean, FIXED_FREQ_MARGIN)))
        {
            bResult = true;
        }
        else
        {
            bResult = false;
        }
    }
    // 에미터1, 2가 둘다 주파수 고정이 아닌 경우 타입이 같으면 매칭 판정
    else if (/*(pEmitter1->freq_type != _FIXED) && */(pEmitter2->enFreqType != _FIXED))
    {
        if (pEmitter1->enFreqType == pEmitter2->enFreqType)
        {
            bResult = true;
        }
        else
        {
            bResult = false;
        }
    }
    // 나머지 경우 매칭 불가
    else
    {
        bResult = false;
    }

    return bResult;
}

/**
 * @brief		HoppingAnalysis
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2022/01/03 15:43:43
 * @warning		
 */
void CAnalPRI::HoppingAnalysis()
{
    unsigned int i;
    STR_EMITTER *pEmitter;

    pEmitter = & m_Emitter[ m_uiAnalEmitter ];
    for( i=m_uiAnalEmitter ; i < m_uiCoEmitter ; ++i, ++ pEmitter ) {

        if( pEmitter->mark == DELETE_EMITTER )
            continue;

        if (_RANDOM_AGILE != pEmitter->enFreqType)
        {
            continue;
        }

        /// 호핑 분석 정보 초기화
        memset(&m_HoppingData, 0, sizeof(STR_HOPPING_DATA));

        /// 1. 주파수 히스토그램을 그린다.
        MakeFreqHistogram(pEmitter);

        /// 2. 주파수 히스토그램을 기반으로 호핑 레벨을 추출한다.
        ExtractHoppingLevel(pEmitter);

        /// 3. 호핑 분석 정보를 기반으로 호핑 여부를 판정한다.
        if (TRUE == HoppingDecision(pEmitter)) {
            /// 호핑 가능으로 판정된 경우 호핑 정보를 재설정한다.
            pEmitter->enFreqType = _HOPPING;
            pEmitter->stFreq.iType = (int) _HOPPING;
            memcpy(pEmitter->iFreqLevel, m_HoppingData.hop_level, sizeof(int)*m_HoppingData.hop_level_cnt);
            pEmitter->iCoFreqLevel = (int)m_HoppingData.hop_level_cnt;
        }
    }
}

/**
 * @brief		MakeFreqHistogram
 * @param		STR_EMITTER * pEmitter
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2022/01/03 16:39:56
 * @warning		
 */
void CAnalPRI::MakeFreqHistogram(STR_EMITTER *pEmitter)
{
    unsigned int i;
    int band;
    float fResol = 0.0;
    UINT uiFreqBin = 0;
    PDWINDEX Idx = 0;
    PDWINDEX *pIndex;

    band = (int) m_pBAND[pEmitter->stPDW.pIndex[0]];
    fResol = gFreqRes[band+1].fRes;

    /// 주파수 히스토그램을 생성한다.
    pIndex = pEmitter->stPDW.pIndex;
    for( i=0 ; i < pEmitter->stPDW.uiCount ; i++ ) {
        //Idx = *(pEmitter->pdw.pIndex+i);
        Idx = *pIndex;
        ++pIndex;
        uiFreqBin = (UINT)((float) m_pFREQ[Idx] * fResol / (float)FREQ_BIN_WIDTH);

        if (uiFreqBin < FREQ_BIN) {
            m_HoppingData.hist[uiFreqBin][m_HoppingData.bin_count[uiFreqBin]] = Idx;
            m_HoppingData.bin_count[uiFreqBin]++;
        }
    }

}

/**
 * @brief		ExtractHoppingLevel
 * @param		STR_EMITTER * pEmitter
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2022/01/03 16:43:03
 * @warning		
 */
void CAnalPRI::ExtractHoppingLevel(STR_EMITTER *pEmitter)
{
    int i, j;
    PDWINDEX Idx1, Idx2, aLevelIdx[MAX_PDW];
    UINT uiLevelIdxCnt;

    // 주파수 히스토그램에서 호핑 레벨 임계치 이상인 것들에 대해 호핑 레벨을 추출한다.
    for (i = 0; i < FREQ_BIN; i++)
    {
        // 임계치 미만인 Bin은 체크하지 않음
        if (m_HoppingData.bin_count[i] < HOP_LEVEL_THREAT_CNT)
        {
            continue;
        }

        uiLevelIdxCnt = 0;
        memset(aLevelIdx, 0, sizeof(aLevelIdx));

        // Bin 내의 인덱스를 체크
        for (j = 1; j < (int)m_HoppingData.bin_count[i]; j++)
        {
            Idx1 = m_HoppingData.hist[i][j-1];
            Idx2 = m_HoppingData.hist[i][j];

            if (j == 1)
            {
                aLevelIdx[uiLevelIdxCnt] = Idx1;
                uiLevelIdxCnt++;
            }

            // 인덱스1-2의 차이가 최대 미싱 개수를 넘는 경우 처리
            if (_diffabs((UINT)Idx2, (UINT)Idx1) > MAX_FREQ_MISS_CNT)
            {
                // 호핑 레벨 개수가 임계치를 넘는 경우
                if (uiLevelIdxCnt >= HOP_LEVEL_THREAT_CNT)
                {
                    // 호핑 레벨의 인덱스 정보 추가
                    memcpy(m_HoppingData.pt_pdw_idx[m_HoppingData.pt_count], aLevelIdx, sizeof(PDWINDEX)*uiLevelIdxCnt);
                    m_HoppingData.pt_pdw_count[m_HoppingData.pt_count] = uiLevelIdxCnt;
                    m_HoppingData.pt_count++;
                }

                // 호핑 레벨 정보 초기화
                uiLevelIdxCnt = 0;
                memset(aLevelIdx, 0, sizeof(aLevelIdx));
            }
            else
            {
                aLevelIdx[uiLevelIdxCnt] = Idx2;
                uiLevelIdxCnt++;
            }
        }

        // 호핑 레벨 개수가 임계치를 넘는 경우
        if (uiLevelIdxCnt >= HOP_LEVEL_THREAT_CNT)
        {
            // 호핑 레벨의 인덱스 정보 추가
            memcpy(m_HoppingData.pt_pdw_idx[m_HoppingData.pt_count], aLevelIdx, sizeof(PDWINDEX)*uiLevelIdxCnt);
            m_HoppingData.pt_pdw_count[m_HoppingData.pt_count] = uiLevelIdxCnt;
            m_HoppingData.pt_count++;
        }
    }
}

/**
 * @brief		HoppingDecision
 * @param		STR_EMITTER * pEmitter
 * @return		BOOL
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2022/01/03 16:35:22
 * @warning		
 */
BOOL CAnalPRI::HoppingDecision(STR_EMITTER *pEmitter)
{
    BOOL bResult = TRUE;
    UINT i, j, uiTotalPDWCnt = 0;
    double dHopPercentage = 0.0;

    for (i = 0; i < m_HoppingData.pt_count; i++)
    {
        for (j = i+1; j < m_HoppingData.pt_count; j++)
        {
            // 호핑 레벨로 추출된 인덱스 배열을 서로 비교하여 겹치는지 확인한다.
            // 겹치는 부분이 있으면 호핑 불가로 판정한다.
            if (((UINT)m_HoppingData.pt_pdw_idx[i][0] < (UINT)m_HoppingData.pt_pdw_idx[j][0]) &&
                ((UINT)m_HoppingData.pt_pdw_idx[i][m_HoppingData.pt_pdw_count[i]-1] > (UINT)m_HoppingData.pt_pdw_idx[j][0]))
            {
                bResult = FALSE;
                break;
            }
        }
    }

    // 전체 에미터 PDW 개수 중 호핑으로 판정된 PDW 개수가 일정% 이상인지 확인한다.
    if (TRUE == bResult)
    {
        for (i = 0; i < m_HoppingData.pt_count; i++)
        {
            uiTotalPDWCnt += (UINT)m_HoppingData.pt_pdw_count[i];
        }

        // 호핑 백분율 계산
        dHopPercentage = (double)uiTotalPDWCnt / (double)pEmitter->stPDW.uiCount * 100.0;

        // 기준 백분율보다 작으면 호핑 불가로 판정한다.
        if (dHopPercentage < HOP_PDW_PERCENTAGE)
        {
            bResult = FALSE;
        }
    }

    // 호핑 레벨 값을 계산한다.
    if (TRUE == bResult)
    {
        SetHoppingInfo(pEmitter);

        // 호핑 레벨이 최대 개수를 넘어서면 호핑 불가로 판정한다.
        if (m_HoppingData.hop_level_cnt > MAX_HOPPING_LEVEL_ELEMENT)
        {
            bResult = FALSE;
        }
    }

    return bResult;
}

/**
 * @brief		SetHoppingInfo
 * @param		STR_EMITTER * pEmitter
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2022/01/03 16:35:37
 * @warning		
 */
void CAnalPRI::SetHoppingInfo(STR_EMITTER *pEmitter)
{
    BOOL bExist = FALSE;
    UINT i, j, uiFreqSum, uiFreqAvg, uiFreqThres;
    int band;

    // 추출한 호핑 레벨의 평균 주파수값을 계산한다.
    for (i = 0; i < m_HoppingData.pt_count; i++)
    {
        _EQUALS3( uiFreqSum, uiFreqAvg, 0 )
        for (j = 0; j < m_HoppingData.pt_pdw_count[i]; j++)
        {
            uiFreqSum += m_pFREQ[m_HoppingData.pt_pdw_idx[i][j]];
        }
        uiFreqAvg = UDIV(uiFreqSum, m_HoppingData.pt_pdw_count[i]);
        band = m_pBAND[m_HoppingData.pt_pdw_idx[i][0]];
        uiFreqThres = UDIV( FIXED_FREQ_MARGIN, gFreqRes[band+1].fRes );	

        bExist = FALSE;

        // 기존 호핑 정보에 포함되어 있는지 확인한다.
        for (j = 0; j < m_HoppingData.hop_level_cnt; j++)
        {
            if (TRUE == CompMeanDiff((int)uiFreqAvg, m_HoppingData.hop_level[j], (int)uiFreqThres))
            {
                bExist = TRUE;
                break;
            }
        }

        // 기존 호핑 정보에 포함되어 있지 않은 레벨이면 새로 추가한다.
        if (FALSE == bExist)
        {
            // 저장 가능한 호핑 레벨 개수를 넘어서면 중단한다.
            if ((MAX_HOPPING_LEVEL_ELEMENT*2) <= m_HoppingData.hop_level_cnt)
            {
                break;
            }
            else
            {
                m_HoppingData.hop_level[m_HoppingData.hop_level_cnt] = (int)uiFreqAvg;
                m_HoppingData.hop_level_cnt++;
            }
        }
    }
}
