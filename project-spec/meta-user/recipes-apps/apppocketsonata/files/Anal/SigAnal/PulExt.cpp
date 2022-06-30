﻿// PulExt.cpp: implementation of the CPulExt class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#if defined(_ELINT_) || defined(_XBAND_)
#include "../OFP_Main.h"

#elif _POCKETSONATA_
#include "../OFP_Main.h"
#include "../INC/Macros.h"
#include "../Identify/ELUtil.h"

#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "PulExt.h"


#include "../../Include/globals.h"

#include "../../files/Utils/ccommonutils.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt::CPulExt
// 함 수 인 자  : int coMaxPdw /*=NSP_MAX_PDW*/
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-30 18:34:46
//
//##ModelId=426C87D7000C
CPulExt::CPulExt( int coMaxPdw /*=NSP_MAX_PDW*/ )
{
    int i;
    BOOL bRet=TRUE;

    // PRI 범위를 계산하기 위해서 TOA를 몇번 쉬프트를 해야할지를 찾는다.
    _TOA iValue, powervalue;

    iValue = ITOAusCNV( (_TOA)4 );		// * _spOneMicrosec;
    powervalue = 1;
    for( i=0 ; i < 10 ; ++i ) {
        if( powervalue > iValue ) {
            break;
        }
        powervalue *= 2;
    }
    m_nToaShift = i;

    //-- 조철희 2005-12-15 14:04:21 --//
    /*! \todo	 m_nMaxPdw 개수는 초대 스태거 레벨을 계산할 때 필요하기에 최대 개수로 설정할 수 있도록 함. */
    m_uiMaxPdw = min( (UINT) coMaxPdw, MAX_PDW );
    m_uiMaxSeg = MAX_SEG;

    // 멤버 변수 메모리 할당
    for( i=0 ; i < m_uiMaxSeg ; ++i ) {
        m_Seg[i].stPDW.pIndex = ( PDWINDEX * ) malloc( sizeof( PDWINDEX ) * m_uiMaxPdw );
        if( m_Seg[i].stPDW.pIndex == NULL ) {
            bRet = FALSE;
            printf( "\n [W] m_Seg[%d].pdw.pIndex's memory allocation error !" , i );
            WhereIs;
        }
    }

    m_RefSeg.stPDW.pIndex = ( PDWINDEX * ) malloc( sizeof( PDWINDEX ) * m_uiMaxPdw );
    if( m_RefSeg.stPDW.pIndex == NULL ) {
        bRet = FALSE;
        printf( "\n [W] m_RefSeg.pdw.pIndex's memory allocation error !" );
        WhereIs;
    }

    m_PdwParam.pTOAParam = ( _TOA * ) malloc( sizeof( _TOA ) * m_uiMaxPdw );
    if( m_PdwParam.pTOAParam == NULL ) {
        printf( "\n [W] m_PdwParam.pTOAParam's memory allocation error !" );
        WhereIs;
    }
    m_PdwParam.puiParam = ( UINT * ) malloc( sizeof( UINT ) * m_uiMaxPdw );
    if( m_PdwParam.pTOAParam == NULL ) {
        printf( "\n [W] m_PdwParam.puiParam's memory allocation error !" );
        WhereIs;
    }
    m_PdwParam.piParam = ( int * ) malloc( sizeof( int ) * m_uiMaxPdw );
    if( m_PdwParam.pTOAParam == NULL ) {
        printf( "\n [W] m_PdwParam.piParam's memory allocation error !" );
        WhereIs;
    }

    m_pRemovePdwIndex = ( unsigned char * ) malloc( sizeof( unsigned char ) * m_uiMaxPdw );
    if( m_pRemovePdwIndex == NULL ) {
        printf( "\n [W] m_pRemovePdwIndex's memory allocation error !" );
        WhereIs;
    }

    if( bRet == FALSE ) {
        printf( "\n [W] 펄스열 추출 클래스 생성자 실패 !" );
    }
}

/**
 * @brief     펄스열 추출 객체의 소멸자 처리를 한다.
 * @return    
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2005-05-30 18:34:54
 * @warning
 */
CPulExt::~CPulExt()
{
    for( unsigned int i=0 ; i < m_uiMaxSeg ; ++i ) {
        free( m_Seg[i].stPDW.pIndex );
        m_Seg[i].stPDW.pIndex = NULL;
    }

    if( m_RefSeg.stPDW.pIndex != NULL ) {
        free( m_RefSeg.stPDW.pIndex );
        m_RefSeg.stPDW.pIndex = NULL;
    }

    if( m_PdwParam.pTOAParam != NULL ) {
        free( m_PdwParam.pTOAParam );
        m_PdwParam.pTOAParam = NULL;
    }
    if( m_PdwParam.puiParam != NULL ) {
        free( m_PdwParam.puiParam );
        m_PdwParam.puiParam = NULL;
    }
    if( m_PdwParam.piParam != NULL ) {
        free( m_PdwParam.piParam );
        m_PdwParam.piParam = NULL;
    }
    if( m_pRemovePdwIndex != NULL ) {
        free( m_pRemovePdwIndex );
        m_pRemovePdwIndex = NULL;
    }
}

/**
 * @brief     펄스열 초기화를 처리한다. 분석 시작시 이 함수를 최소한 호출해야 한다.
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2005-04-26 18:18:46
 * @warning
 */
void CPulExt::Init()
{
    _EQUALS3( m_uiCoSeg, m_uiAnalSeg, (UINT) 0 );

	m_uiRefStartSeg = INT32_MAX;
    m_uiRefEndSeg = INT32_MAX;

    // PRI 밴드 초기화
    m_uiStart_pri_level = 0;
    m_uiEnd_pri_level = MAX_PRI_RANGE - 1;

    m_pGrPdwIndex = GetFrqAoaGroupedPdwIndex();

    m_CoPdw = GetCoPdw();

    STR_PRI_RANGE_TABLE *pRange;

    // 지터 펄스열 추출 밴드 구성
    int i;
    _TOA temp_pri;
    pRange = & m_jit_pri_table[0];
    int power_2=1;
    temp_pri = (_TOA) IFTOAusCNV( (float) 1.5 ); //ITOAusCNV( (_TOA)( 1.5 * power_2 ) );			// 2 * power_2 * _spOneMicrosec;
    for( i=0 ; i < MAX_PRI_RANGE ; ++i ) {
        pRange->tMinPRI = temp_pri;

		temp_pri = TMULDIV<_TOA>( (_TOA) 2, temp_pri, (_TOA)1 );

        //power_2 = power_2 * 2;
        pRange->tMaxPRI = temp_pri;
        /*! \bug  하모닉을 고려해서 2배까지 PRI 밴드로 한다.
            \date 2006-08-25 11:30:14, 조철희
        */
        // pRange->max_pri = UMUL( pRange->max_pri, 1.1 );

        ++ pRange;
    }
    //-- 조철희 2006-01-06 09:59:55 --//
    // m_jit_pri_table[MAX_PRI_RANGE-1].max_pri = 10000 * _spOneMicrosec;
    /*
        m_jit_pri_table[ 0] =	      2.00 *_spOneMicrosec;	m_jit_pri_table[ 0] =      3.50 *_spOneMicrosec;	++ pRange;
        m_jit_pri_table[ 1] =       3.50 *_spOneMicrosec;	m_jit_pri_table[ 1] =      6.13 *_spOneMicrosec;	++ pRange;
        m_jit_pri_table[ 2] =       6.13 *_spOneMicrosec;	m_jit_pri_table[ 2] =     10.72 *_spOneMicrosec;	++ pRange;
        m_jit_pri_table[ 3] =      10.72 *_spOneMicrosec;	m_jit_pri_table[ 3] =     18.76 *_spOneMicrosec;	++ pRange;
        m_jit_pri_table[ 4] =      18.76 *_spOneMicrosec;	m_jit_pri_table[ 4] =     32.83 *_spOneMicrosec;	++ pRange;
        m_jit_pri_table[ 5] =      32.83 *_spOneMicrosec;	m_jit_pri_table[ 5] =     57.45 *_spOneMicrosec;	++ pRange;
        m_jit_pri_table[ 6] =      57.45 *_spOneMicrosec;	m_jit_pri_table[ 6] =    100.53 *_spOneMicrosec;	++ pRange;
        m_jit_pri_table[ 7] =     100.53 *_spOneMicrosec;	m_jit_pri_table[ 7] =    175.93 *_spOneMicrosec;	++ pRange;
        m_jit_pri_table[ 8] =     175.93 *_spOneMicrosec;	m_jit_pri_table[ 8] =    307.87 *_spOneMicrosec;	++ pRange;
        m_jit_pri_table[ 9] =     307.87 *_spOneMicrosec;	m_jit_pri_table[ 9] =    538.78 *_spOneMicrosec;	++ pRange;
        m_jit_pri_table[10] =     538.78 *_spOneMicrosec;	m_jit_pri_table[10] =    942.86 *_spOneMicrosec;	++ pRange;
        m_jit_pri_table[11] =     942.86 *_spOneMicrosec;	m_jit_pri_table[11] =  1,650.01 *_spOneMicrosec;	++ pRange;
        m_jit_pri_table[12] =   1,650.01 *_spOneMicrosec;	m_jit_pri_table[12] =  2,887.52 *_spOneMicrosec;	++ pRange;
        m_jit_pri_table[13] =   2,887.52 *_spOneMicrosec;	m_jit_pri_table[13] =  5,053.16 *_spOneMicrosec;	++ pRange;
        m_jit_pri_table[14] =   5,053.16 *_spOneMicrosec;	m_jit_pri_table[14] =  8,843.02 *_spOneMicrosec;	++ pRange;
        m_jit_pri_table[15] =   8,843.02 *_spOneMicrosec;	m_jit_pri_table[15] = 15,475.29 *_spOneMicrosec;	++ pRange;
        m_jit_pri_table[16] =  15,475.29 *_spOneMicrosec;	m_jit_pri_table[16] = 27,081.76 *_spOneMicrosec;	++ pRange;
    */
}

/**
 * @brief     펄스열을 추출한다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2005-11-16 17:22:59
 * @warning
 */
void CPulExt::PulseExtract()
{
    //////////////////////////////////////////////////////////////////////////
    // 펄스열 추출 정보를 프린트한다.
    PrintAllSeg();
}

/**
 * @brief     시작 및 종료 PRI 측정 범위를 알아낸다.
 * @param     unsigned int * pStart_pri_level
 * @param     unsigned int * pEnd_pri_level
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-08-08 12:20:28
 * @warning
 */
void CPulExt::GetStartEndPriLevel( unsigned int *pStart_pri_level, unsigned int *pEnd_pri_level )
{
    MakeDtoaHistogram( m_pGrPdwIndex->pIndex, m_pGrPdwIndex->uiCount, NULL );

    STR_LOWHIGH pri_level;
    CalPRILevel( & pri_level, GetDtoaHist() );

    *pStart_pri_level = (UINT) pri_level.iLow;
    *pEnd_pri_level = (UINT) pri_level.iHgh;
}

/**
 * @brief     DTOA 히스토그램으로부터 PRI 레벨 값을 얻는다.
 * @param     STR_LOWHIGH * pPRILevel
 * @param     STR_DTOA_HISTOGRAM * pDtoaHist
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-07-28 13:31:16
 * @warning
 */
void CPulExt::CalPRILevel( STR_LOWHIGH *pPRILevel, STR_DTOA_HISTOGRAM *pDtoaHist )
{
    int i;
    UINT sum_dtoa;

    _TOA prilevel_low, prilevel_hgh;

    STR_PRI_RANGE_TABLE *pRange;

    /*! \bug  DTOA  히스토그램 상에서 overflow 발생시 좌, 우 레벨의 상/하한값을 결정하게 함.
        \date 2006-08-16 11:19:48, 조철희
    */
    if( pDtoaHist->bin_range.iLow == INT32_MAX)
        prilevel_low = DTOA_RES * ( pDtoaHist->bin_count + 1 );
    else
        prilevel_low = UMUL( pDtoaHist->bin_range.iLow, DTOA_RES );

    if( pDtoaHist->bin_range.iHgh == -1 )
        prilevel_hgh = m_jit_pri_table[ MAX_PRI_RANGE - 1 ].tMaxPRI;
    else {
        UINT max_dtoa;
        max_dtoa = UDIV( m_jit_pri_table[ MAX_PRI_RANGE - 1 ].tMaxPRI, DTOA_RES );

        sum_dtoa = 0;
        for( i=pDtoaHist->bin_range.iLow ; i <= pDtoaHist->bin_range.iHgh ; ++i ) {
            if( pDtoaHist->hist[i] != 0 )
                sum_dtoa += (UINT) i;
            if( sum_dtoa > max_dtoa )
                break;
        }
        /*! \bug  최소 DTOA 값은 DTOA RES 값.
            \date 2006-10-16 15:17:36, 조철희
        */
        /*! \bug  다음번째까지 구간 검색을 하도록 함.
            \date 2008-11-03 20:44:52, 조철희
        */
        prilevel_hgh = _max( DTOA_RES, UMUL( sum_dtoa+1, DTOA_RES ) );
    }

    // PRI 레벨을 찾음.
    pRange = & m_jit_pri_table[MAX_PRI_RANGE-1];
    pPRILevel->iLow = 0;
    for( i=MAX_PRI_RANGE-1 ; i >= 0 ; --i ) {
        if( prilevel_low > (UINT) pRange->tMinPRI ) {
            pPRILevel->iLow = i;
            break;
        }
        -- pRange;
    }

    pPRILevel->iHgh = MAX_PRI_RANGE - 1;
    pRange = & m_jit_pri_table[pPRILevel->iLow];
    for( i=pPRILevel->iLow ; i < MAX_PRI_RANGE ; ++i ) {
        if( prilevel_hgh < (UINT) pRange->tMaxPRI ) {
            pPRILevel->iHgh = i;
            break;
        }
        ++ pRange;
    }
}

/**
 * @brief     추출한 나머지 펄스에 대해서 나머지 펄스에 대해서 잔여 펄스로 넘긴다.
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-08-24 15:07:55
 * @warning
 */
void CPulExt::DiscardPulseTrain()
{
//     RemoveStablePulseTrain();
//     DiscardPulseTrain( m_uiRefStartSeg, m_uiRefEndSeg );

	// Stable 열과 Stable 열을 펄스열을 비교하여 서로 유사한 펄스열을 제거한다.
	DiscardPulseTrain( m_uiRefStartSeg, m_uiRefEndSeg, (UINT) -1 );

	// Stable 열과 Stable+Jitter 펄스열을 비교하여 서로 유사한 펄스열을 제거한다.
	DiscardPulseTrain( m_uiRefStartSeg, m_uiRefEndSeg, m_uiRefEndSeg );

	/*! \bug  Stable+Jitter 열 중에서 서로 유사한 펄스열을 제거한다.
	    \date 2011-08-30 11:37:09, 조철희
	*/
	DiscardPulseTrain( m_uiRefEndSeg, m_uiCoSeg, m_uiRefEndSeg+1 );

}

/**
 * @brief     규칙성 펄스열과 불규칙성 펄스열끼리 펄스열 인덱스를 고려해서
 *	 	      유사 펄스열을 제거한다.
 *			  startseg2 값이 -1 일 때는 startseg ~ endseg 끼리 비교 한다.
 * @param     unsigned int startseg
 * @param     unsigned int endseg
 * @param     unsigned int startseg2
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-05-19 09:23:05
 * @warning
 */
void CPulExt::DiscardPulseTrain( unsigned int startseg, unsigned int endseg, unsigned int startseg2 )
{
	if( startseg == endseg )
	{
	}
	else {
		unsigned int i;
        unsigned int j, k, endseg2;
		int coMatch;

		int ref_ratio, cmp_ratio;

		UINT *pParam;
		PDWINDEX *pPdwIndex;

		STR_PULSE_TRAIN_SEG *pRefSeg, *pCmpSeg;

		pRefSeg = & m_Seg[ startseg ];
		for( i=startseg ; i < endseg ; ++i, ++pRefSeg ) {
			if( pRefSeg->enMark == DELETE_SEG ) {
				continue;
            }

			// 기준 펄스열 인덱스 설정
			pParam = m_PdwParam.puiParam;
			m_PdwParam.uiCount = pRefSeg->stPDW.uiCount;
			memset( pParam, 0, sizeof( UINT ) * (UINT)m_uiMaxPdw );
			pPdwIndex = pRefSeg->stPDW.pIndex;
			for( j=0 ; j < pRefSeg->stPDW.uiCount ; ++j ) {
				pParam[ *pPdwIndex++ ] = EXTRACT_MARK;
            }

			// 펄스열 추출한 것과 펄스열 비교해서 유사 참조 펄스열들은 제거한다.
			if( startseg2 == (UINT) -1 ) {
				j = i + 1;
				endseg2 = endseg;
			}
			else {
				j = startseg2;
				endseg2 = m_uiCoSeg;
			}

			pCmpSeg = & m_Seg[ j ];
			for( ; j < endseg2 ; ++j, ++ pCmpSeg ) {
				/*! \bug  펄스열 추출할 때 자신과 자신을 비교할 때 제거하지 않도록 한다.
				    \date 2012-09-05 20:47:43, 조철희
				*/
				if( pRefSeg == pCmpSeg || pCmpSeg->enMark == DELETE_SEG ) {
					continue;
                }

				pPdwIndex = pCmpSeg->stPDW.pIndex;
				coMatch = 0;
				for( k=0 ; k < pCmpSeg->stPDW.uiCount ; ++k ) {
					if( pParam[ *pPdwIndex++ ] == EXTRACT_MARK ) {
						++ coMatch;
                    }
				}

				// 매칭 기준 임계값보다 클때 그 펄스열을 삭제 마킹을 한다.
				/*! \bug  jitter_2step.pdw에서 stable 9개의 펄스열이 jitter와 7개의 펄스열이 중복되어 있는데도 
									삭제 판단이 안됨. 그래서 임계값을 0.9 에서 0.7 로 수정함.
				    \date 2006-09-01 11:16:00, 조철희
				*/
				/*
				int threshold_match;

				threshold_match = UMUL( pRefSeg->pdw.count, 0.7 );
				if( threshold_match <= coMatch ) {
					pRefSeg->mark = DELETE_SEG;
					break;
				}
				threshold_match = UMUL( pExtSeg->pdw.count, 0.7 );
				if( threshold_match <= coMatch ) {
					pExtSeg->mark = DELETE_SEG;
				}
				*/

				/*! \bug  매칭된 펄스 개수를 비교해서 규칙성 펄스열과 불규칙성 펄스열에 대한
									비율이 확연히 차이가 날 수록 Jitter를 선택하고 그렇치 않을 때는 Stable 펄스열을 선택한다.

				    \date 2007-06-20 15:56:28, 조철희
				*/
				ref_ratio = (int)UDIV( 100 * coMatch, pRefSeg->stPDW.uiCount );
				cmp_ratio = (int)UDIV( 100 * coMatch, pCmpSeg->stPDW.uiCount );
/*
				// 두 펄스열이 모두 Stable인 경우
				// RefSeg쪽이 더 작은 PRI를 가지므로 ExtSeg의 삭제 여부를 판단한다.
				if ((_STABLE == pRefSeg->pri_type) && (_STABLE == pExtSeg->pri_type))
				{
					if(stable_ratio >= 70 )
						pExtSeg->mark = DELETE_SEG;
				}
				// 나머지 경우
				else
*/
				// 유사하면 비교 펄스열을 삭제한다.
				if( ref_ratio > 90 && cmp_ratio > 90 ) {
					pCmpSeg->enMark = DELETE_SEG;
				}
				else if( ref_ratio > cmp_ratio && ref_ratio > 70 ) {
					pRefSeg->enMark = DELETE_SEG;
				}
				// 비교펄스열율이 더 크면  비교펄스열을 삭제한다.
				else if( ref_ratio < cmp_ratio && cmp_ratio > 70 ) {
					pCmpSeg->enMark = DELETE_SEG;
				}
				else {
				}
			}
		}
	}
}

/**
 * @brief     규칙성 펄스열을 제거한다.
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2008-11-11 20:13:05
 * @warning
 */
void CPulExt::RemoveStablePulseTrain()
{
    unsigned int i, j, k;
    unsigned int uiPdwCount;
    int coMatch;

    PDWINDEX *pPdwIndex;
    STR_PULSE_TRAIN_SEG *pRefSeg, *pExtSeg;

    pRefSeg = & m_Seg[ m_uiRefEndSeg ];
    for( i=m_uiRefEndSeg ; i < m_uiCoSeg ; ++i, ++pRefSeg ) {
        if( pRefSeg->enPriType != _STABLE ) {
            continue;
        }

        pExtSeg = & m_Seg[ 0 ];
        for( j=0 ; j < m_uiRefEndSeg ; ++j, ++pExtSeg ) {
            if( pExtSeg->enPriType != _STABLE ) {
                continue;
            }

            memset( m_pRemovePdwIndex, 0, sizeof(char)*m_CoPdw );

            uiPdwCount = pRefSeg->stPDW.uiCount;
            pPdwIndex = pRefSeg->stPDW.pIndex;
            for( k=0 ; k < uiPdwCount ; ++k ) {
                m_pRemovePdwIndex[*pPdwIndex++] = 1;
            }

            uiPdwCount = pExtSeg->stPDW.uiCount;
            pPdwIndex = pExtSeg->stPDW.pIndex;
            coMatch = 0;
            for( k=0 ; k < uiPdwCount ; ++k ) {
                if( m_pRemovePdwIndex[*pPdwIndex++] == 1 ) {
                    ++ coMatch;
                }
            }

            int ratio1, ratio2;
            ratio1 = UDIV( 100*coMatch, pExtSeg->stPDW.uiCount );
            ratio2 = UDIV( 100*coMatch, pRefSeg->stPDW.uiCount );

            if( ratio1 > 70 || ratio2 > 70 ) {
                pRefSeg->enMark = DELETE_SEG;
            }
        }
    }
}

/**
 * @brief     지정한 범위 내의 펄스열에 대해서 클리어한다.
 * @param     int startseg
 * @param     int endseg
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2006-05-19 16:48:26
 * @warning
 */
void CPulExt::CleanPulseTrains( int startseg, int endseg )
{
    int i;

    STR_PULSE_TRAIN_SEG *pSeg, *pDestSeg;

    _EQUALS3( pDestSeg, pSeg, & m_Seg[ startseg ] )
    for( i=startseg ; i < endseg ; ++i ) {
        if( pSeg->stPDW.uiCount > (int) _sp.cm.Rpc && pSeg->enMark != DELETE_SEG ) {
            MemcpySeg( pDestSeg, pSeg );
            ++ pDestSeg;
        }
        else {
            --m_uiCoSeg;
        }

        ++ pSeg;
    }
}

/**
 * @brief     펄스열을 복사한다.
 * @param     STR_PULSE_TRAIN_SEG * pDestSeg
 * @param     STR_PULSE_TRAIN_SEG * pSrcSeg
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2006-05-19 16:57:45
 * @warning
 */
void CPulExt::MemcpySeg( STR_PULSE_TRAIN_SEG *pDestSeg, STR_PULSE_TRAIN_SEG *pSrcSeg )
{
    if( pDestSeg != pSrcSeg ) {
        memcpy( pDestSeg->stPDW.pIndex, pSrcSeg->stPDW.pIndex, sizeof( PDWINDEX ) * pSrcSeg->stPDW.uiCount );
        pDestSeg->stPDW.uiCount = pSrcSeg->stPDW.uiCount;

        // 나머지 기타 정보를 복사한다.
        memcpy( & pDestSeg->uiMiss, & pSrcSeg->uiMiss, sizeof( STR_PULSE_TRAIN_SEG ) - sizeof( STR_PDWINDEX ) );
    }
}

/**
 * @brief     지터 펄스열을 추출한다.
 * @param     int type
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2005-05-02 10:05:35
 * @warning
 */
void CPulExt::ExtractJitter( int type )
{
    int i;

    STR_PRI_RANGE_TABLE ext_range;

    // 펄스열 기본 추출
    for( i=m_uiStart_pri_level ; i <= (int) m_uiEnd_pri_level ; ++i ) {
        // PRI 범위 구하기
        ext_range.tMinPRI = m_jit_pri_table[ i ].tMinPRI;
        ext_range.tMaxPRI = m_jit_pri_table[ i ].tMaxPRI;

#ifdef _JITTER_PULSE_EXTRACT_METHOD1_
        //-- 조철희 2005-05-30 17:46:15 --//
        // 기존의 펄스열 추출은 여러가지 문제가 있다.
        // 첫째로 Dwell&Switch 인 경우에 레벨이 PRI, 3*PRI1 = 2*PRI2 인경우에 4배 PRI 가 추출된다.
        // 둘째로 Jitter 펄스열 안에 Stable 펄스열이 존재하면 누락된 Jitter 펄스열이 생길수 있으며
        //			  Jitter PRI 값과 유사한 Stable 펄스열이 추출된다. 이 결과는 유사한 에미터가 이중으로
        //			  보고되는 수 가 있다.
        //
        // 이러한 문제들을 해결하기 위한 방법으로...
        // 기준 규칙성 펄스열을 사전에 찾아서 불규칙성 펄스열을 추출 후에 이전에 찾은 기준 규칙성
        // 펄스열을 찾는다. 이렇게 되면 첫번째 및 두번째 문제는 해결할 수 있다.
        //
        // 정리해 보면
        // 1) 규칙성 펄스열의 기준 PRI 값을 찾는다.
        // 2) 불규칙성 펄스열을 추출한다.
        // 3) 1)에서 찾은 PRI로 시작하여 규칙성 펄스열을 추출한다.
        // 4) 규칙성 펄스열을 추출한다.

        // 정리해 보면
        // 1) 규칙성 펄스열의 기준 PRI 값을 찾는다.
        // ) 규칙성 펄스열 추출과 불규칙성 펄스열 추출은 별도로 한다.

        // 한 구간에서 규칙성 펄스열은 무시하고 지터열을 추출해 본다.
        memcpy( RSMK, MARK, sizeof( USHORT ) * m_uiMaxPdw );

        // 규칙성 펄스열의 추출
        int nStartStableSeg = m_uiCoSeg;
        ExtractStablePT();

        // 펄스열의 인덱스를 조사해서 겹쳐져 있으면 그중 한개를 버린다.
        DiscardStablePulseTrain();

        // 불규칙성 펄스열의 추출
        // 규칙성 펄스열에서 로브 조건에서 실패한 펄스열은 불규칙성 펄스열에서 재 추출하도록 한다.
        //nStartJitterSeg = m_CoSeg;
        // ExtractJitterPT();

        ExtractJitterPT( & ext_range, i );

        // CompStablesJitters( nStartStableSeg, nStartJitterSeg );

        // 추출된 펄스열들을 정리한다.
        // 하모닉 체크 를 수행하여 유사한 펄스열 들을 제거한다.
        // 규칙성 펄스열들과 뷸규칙성 펄스열을 조사하여 하나로 만든다.
        // CleanRefSeg();

        // 잘못된 처리 : 추출된 것이더라도 에미터로 생성하지 않은 것들은 나둔다.
        // PDW의 MARK 열에 펄스열 추출된 열은 모두 삭제된 마킹을 한다.
        // AllExtSegMark();

        // 추출한 마크를 복원한다.
        memcpy( MARK, RSMK, sizeof( USHORT ) * m_uiMaxPdw );
        MarkSegForExt( nStartStableSeg, m_uiCoSeg );

#elif defined( _JITTER_PULSE_EXTRACT_METHOD2_ )
        if( type == _STABLE + _JITTER_RANDOM ) {
            // 한 구간에서 규칙성 펄스열은 무시하고 지터열을 추출해 본다.
            //memcpy( RSMK, MARK, sizeof( USHORT ) * m_nMaxPdw );

            // 규칙성 펄스열의 추출
            //ExtractStablePT( & ext_range, i );

            // 불규칙성 펄스열의 추출
            ExtractJitterPT( & ext_range, i );

            // 추출한 마크를 복원한다.
            //memcpy( MARK, RSMK, sizeof( USHORT ) * m_nMaxPdw );
            //MarkSegForExt( nStartStableSeg, m_CoSeg );
        }
        else if( type == _JITTER_RANDOM ) {
            // 불규칙성 펄스열의 추출
            ExtractJitterPT( & ext_range, i );
        }

#endif
    }
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CPulExt::MarkSegForExt
//!	\author  조철희
//!	\param	 nStartSeg	인자형태 int
//! \param	 nEndSeg	인자형태 int
//!	\return	 void
//! \version 1.0
//! \date		 2006-05-19 12:06:28
//! \warning
//
void CPulExt::MarkSegForExt( int nStartSeg, int nEndSeg )
{
    int i;
    STR_PULSE_TRAIN_SEG *pSeg;

    for( i=nStartSeg ; i < nEndSeg ; ++i ) {
        pSeg = & m_Seg[i];
        if( pSeg->enMark == DELETE_SEG )
            continue;
        else {
            if( pSeg->enPriType == _STABLE )
                MarkToPDWIndex( pSeg, STABLE_MARK );
            else
                MarkToPDWIndex( pSeg, JITTER_MARK );
        }
    }
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CPulExt::MarkStablePulseTrain

                            추출한 펄스열 중에서 규칙성 펄스열만 마킹한다.
        \author   조철희
        \return   void
        \version  1.37
        \date     2007-06-29 12:46:21
        \warning
*/
void CPulExt::MarkStablePulseTrain()
{
    unsigned int i;
    STR_PULSE_TRAIN_SEG *pSeg;

    pSeg = & m_Seg[m_uiAnalSeg];
    for( i=m_uiAnalSeg ; i < m_uiCoSeg ; ++i, ++pSeg ) {
        if( pSeg->enMark == DELETE_SEG )
            continue;
        else {
            if( pSeg->enPriType == _STABLE )
                MarkToPDWIndex( pSeg, EXTRACT_MARK );
        }
    }
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CPulExt::MustDo2ndPulseExtract

                            2차 펄스열을 분석 여부를 결정한다. 즉, 규칙성 펄스열에서
                            펄스열 개수가 추출되면 2차 펄스열 분석을 하게 한다.
        \author   조철희
        \return   BOOL
        \version  1.37
        \date     2007-07-02 10:49:44
        \warning
*/
BOOL CPulExt::MustDo2ndPulseExtract()
{
    unsigned int i;
    STR_PULSE_TRAIN_SEG *pSeg;

    pSeg = & m_Seg[m_uiAnalSeg];
    for( i=m_uiAnalSeg ; i < m_uiCoSeg ; ++i, ++pSeg ) {
        if( pSeg->enMark == DELETE_SEG )
            continue;
        else {
            if( pSeg->enPriType == _STABLE )
                return TRUE;
            else
                break;
        }
    }

    return FALSE;
}

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CompStablesJitters
//!	\author  조철희
//!	\param	 nStartStableSeg	인자형태 int
//!	\param	 nStartJitterSeg	인자형태 int
//!	\return	 void
//! \version 1.0
//! \date		 2006-05-19 11:38:43
//! \warning
//
void CPulExt::CompStablesJitters( unsigned int uiStartStableSeg, unsigned int uiStartJitterSeg )
{
    // 규칙성 펄스열을 찾지 못했을 때는 비교할 필요가 없다.
    if( uiStartStableSeg != uiStartJitterSeg ) {
        unsigned int i, j;

        STR_PULSE_TRAIN_SEG *pStableSeg, *pJitterSeg;

        for( i=uiStartStableSeg ; i < uiStartJitterSeg ; ++i ) {
            pStableSeg = & m_Seg[i];
            for( j=uiStartJitterSeg ; j < m_uiCoSeg ; ++j ) {
                pJitterSeg = & m_Seg[j];
                if( CompMarginDiff<_TOA>( pStableSeg->stPRI.tMin, pJitterSeg->stPRI.tMin, pJitterSeg->stPRI.tMax, 0 ) == TRUE &&
                        CompMarginDiff<_TOA>( pStableSeg->stPRI.tMax, pJitterSeg->stPRI.tMin, pJitterSeg->stPRI.tMax, 0 ) == TRUE ) {
                    pStableSeg->enMark = DELETE_SEG;
                    break;
                }
            }
        }

        // 규칙성 펄스열이 불규칙성 펄스열에 포함이 된 펄스열은 제거해서 메모리를 줄인다.
        CleanPulseTrains( uiStartStableSeg, m_uiCoSeg );
    }
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt::ExtractStablePT
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-02 10:06:30
//
//##ModelId=42757D4C01E4
void CPulExt::ExtractStablePT()
{
    int i;

    _TOA largest_pri;
    STR_PRI_RANGE_TABLE ext_range;

    // 추출되는 펄스열은 gSeg[]에 저장되며
    // 펄스열의 수는 gSeg_cnt에 의해 count 된다.
    // 펄스열의 추출은
    //			기준 펄스열 추출(extractRefPT()),
    //			후진 펄스열 추출(extractBackPT()),
    //			전진 펄스열 추출(extractForPT()),
    //			단순 펄스열 추출(extractSimpleJitterPT()),
    // 순으로 이루어지며 한번의 pass가 이루어지면 에미터가 하나 증가한다. gEmitter.count증가
    // 기준, 후진,전진 펄스열추출의 pass가 이루어지면 하나의 펄스열이 만들어지며
    // 펄스열의 수 gSeg_cnt가 증가 한다.
    // 하나의 에미터에는 동일한 PRI의 펄스열이 여러개 존재할수 있다.

    largest_pri = ( m_pTOA[ m_pGrPdwIndex->pIndex[m_pGrPdwIndex->uiCount-1] ] - m_pTOA[ m_pGrPdwIndex->pIndex[0] ] ) / _sp.cm.Rpc;

    if( largest_pri > m_jit_pri_table[ m_uiEnd_pri_level-1 ].tMaxPRI )
        largest_pri = m_jit_pri_table[ m_uiEnd_pri_level-1 ].tMaxPRI;

    // 펄스열 기본 추출
    for( i=m_uiStart_pri_level ; i < (int) m_uiEnd_pri_level ; ++i ) {
        // PRI 범위 구하기
        ext_range.tMinPRI = m_jit_pri_table[ i ].tMinPRI;
        ext_range.tMaxPRI = m_jit_pri_table[ i ].tMaxPRI;

        if( ext_range.tMaxPRI > largest_pri && ext_range.tMinPRI < largest_pri)
            ext_range.tMaxPRI = largest_pri;

        ExtractStablePT( & ext_range, i );
    }
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CPulExt::ExtractStablePT
//! \author   조철희
//! \param    pExtRange 인자형태 STR_PRI_RANGE_TABLE *
//! \param    nPriBand 인자형태 int
//! \param    flagMargin 인자형태 BOOL
//! \param    mark 인자형태 BOOL
//! \return   void
//! \version  1.37
//! \date     2006-08-28 13:29:41
//! \warning
//
void CPulExt::ExtractStablePT(STR_PRI_RANGE_TABLE *pExtRange, int nPriBand, BOOL flagMargin, int iMark )
{
    int ref_idx;
    UINT margin;

    STR_PULSE_TRAIN_SEG *pSeg;

    if( m_pGrPdwIndex->uiCount <= 2 )
        return;

    if( flagMargin == TRUE )
        margin = UDIV( pExtRange->tMaxPRI - pExtRange->tMinPRI, 2 );
    else
        margin = 0;

    // 시작 PDW 인덱스
    ref_idx = 0;

    // 누락 펄스가 없을 때 고려한 펄스열 추출
    for( ;; ) {
        if( m_uiCoSeg >= m_uiMaxSeg )
            return;

        pSeg = & m_Seg[ m_uiCoSeg ];

        // 기준 펄스열 추출을 찾아서 존재하지 않으면 다음 밴드를 선택한다.
        if( TRUE == ExtractRefPT( pExtRange, _STABLE, pSeg, ref_idx, m_pGrPdwIndex, _sp.cm.Rpc, flagMargin ) ) {
            ref_idx = pSeg->gr_ref_idx;
            ExtractBackPT( pSeg, _STABLE, m_pGrPdwIndex, margin );

            ExtractForPT( pSeg, _STABLE, m_pGrPdwIndex, margin );

            // 펄스열은 기준펄스열로 추출된 것 이상인것만 체크한다.
            if( pSeg->stPDW.uiCount > (int) _sp.cm.Rpc ) {
                // 추출된 펄스열의 제원의 계산
                CalcSegParam( pSeg );

                if( nPriBand > 0 ) {
                    pSeg->uiPRI_Band = nPriBand;
                }
                else {
                    pSeg->uiPRI_Band = 0;
                }

                /*! \bug  기준 펄스열로 추출했다는 것으 마킹한다.
                    \date 2006-08-11 12:27:14, 조철희
                */
                pSeg->uiExtractStep = _STABLE;

                // 추출된 펄스 Marking
                MarkToPDWIndex( pSeg, iMark );

                // 펄스열 증가
                ++ m_uiCoSeg;
            }

            ++ ref_idx;
        }
        else {
            break;
        }
    }
}

/**
 * @brief     펄스열 추출시 펄스열 간의 오차를 정한다.
 * @param     STR_LOWHIGH_TOA * pStrMargin
 * @param     STR_PRI_RANGE_TABLE * pPriRange
 * @param     int ext_type
 * @param     BOOL bFlagMargin
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-19, 16:24
 * @warning
 */
void CPulExt::ChooseTOAMargin(STR_LOWHIGH_TOA *pStrMargin, STR_PRI_RANGE_TABLE *pPriRange, _TOA tDtoa, int ext_type, BOOL bFlagMargin )
{
    if (bFlagMargin == FALSE) {
        if (ext_type == _STABLE || ext_type == _REFSTABLE || ext_type == _DWELL) {
            pStrMargin->tLow = 0;
            if (pPriRange->tMaxPRI > ITOAusCNV((_TOA)10)) {
                pStrMargin->tHgh = STABLE_MARGIN;
            }
            else {
                pStrMargin->tHgh = ITOAusCNV((float) 0.1);
            }
        }
        else {
#ifdef _EXTRACT_PULSE_METHOD3_
            pStrMargin->tLow = STABLE_MARGIN;
#else
            pStrMargin->tLow = 0;
#endif
            pStrMargin->tHgh = TMULDIV<_TOA>(tDtoa, MAX_JITTER_P, 100 );

        }
    }
    else {
        pStrMargin->tLow = 0;
        pStrMargin->tHgh = ( pPriRange->tMaxPRI - pPriRange->tMinPRI );
    }

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt::ExtractRefPT
// 반환되는 형  : BOOL
// 함 수 인 자  : STR_PRI_RANGE_TABLE *pPriRange
// 함 수 인 자  : int ext_type
// 함 수 인 자  : STR_PULSE_TRAIN_SEG *pSeg
// 함 수 인 자  : int start_idx
// 함 수 인 자  : STR_PDWINDEX *pColPdwIndex
// 함 수 인 자  : int coRefPulse
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-02 19:24:13
//
//##ModelId=427F25130204
BOOL CPulExt::ExtractRefPT( STR_PRI_RANGE_TABLE *pPriRange, int ext_type, STR_PULSE_TRAIN_SEG *pSeg, int start_idx, STR_PDWINDEX *pColPdwIndex, unsigned int coRefPulse, BOOL bFlagMargin, BOOL bIgnoreJitterP )
{
    int i1, i2, i3;
    int index1, index2, index3;
    int last_index1, last_index2, last_index3;

    _TOA diff;
    _TOA dtoa1, dtoa2;
    _TOA first_toa, second_toa;

    PDWINDEX *pPdwIndex;

    STR_LOWHIGH_TOA margin;

    pPdwIndex = & pColPdwIndex->pIndex[0];

    last_index1 = max( 0, (int) ( pColPdwIndex->uiCount - coRefPulse ) );
    for( i1=start_idx ; i1 <= last_index1 ; ++i1 ) {
        index1 = pPdwIndex[i1];

        // 추출된 펄스 제외
        if (m_pMARK[index1] != UnMark) {
            continue;
        }            

        first_toa = m_pTOA[ index1 ];

        last_index2 = _max( 0, pColPdwIndex->uiCount - coRefPulse + 1 );
        for( i2=i1+1 ; i2 <= last_index2 ; ++i2 ) {
            index2 = pPdwIndex[i2];

            // 추출된 펄스 제외
            if (m_pMARK[index2] != UnMark) {
                continue;
            }

            dtoa1 = m_pTOA[ index2 ] - first_toa;

            // PRI 범위 미만
            if (dtoa1 < pPriRange->tMinPRI) {
                continue;
            }

            /*! \bug  처음 DTOA1의 값의 최대 상한값은 정의하지 않음.
                \date 2006-05-25 14:19:47, 조철희
            */
            // PRI 범위를 벗어남
            //if( dtoa1 > pPriRange->max_pri )
            //	break;

            // 밴드별 경계로 인해서 최대 값 체크하는 것은 무시하도록 한다.
            //-- 조철희 2006-01-09 14:33:04 --//
            // PRI 범위를 벗어남
            /*
             \bug  펄스열 추출단계에서 큰 PRI 값은 다음 단계에서 추출하도록 한다.
                    .D:\RSA-TFT\소나타 ES TFT\해상 신호\A00_소나타체계신호\m6.npw 파일에서
                    에미터가 분리되어  분석됨.
                    .D:\RSA-TFT\소나타 ES TFT\해상 신호\A00_소나타체계신호\filtered.npw 파일에서
                    큰 PRI 로 분석이 됨.
                    \date 2006-06-19 11:13:02, 조철희
            */
            /*
             \bug  STABLE PRI를 추적하고자 할 때 첫번째 DTOA 값은 1.0배로 하게 한다.
                \date 2006-07-19 12:17:31, 조철희
            */
            /*
            if( flagMargin == TRUE ) {
                if( dtoa1 > pPriRange->max_pri )
                    break;
            }
            else {
                // \충주함\sps-64(short)_3.pdw 에서 PRI가 2배 PRI를 추출할 수 있다.
                // 그래서 1배로 수정함. 1.5 -> 1
                if( dtoa1 > (pPriRange->max_pri) )
                    break;
            }
            */
            if( dtoa1 > pPriRange->tMaxPRI ) {
                break;
            }

            second_toa = m_pTOA[ index2 ];

            // TOA margin 선정
            ChooseTOAMargin( & margin, pPriRange, dtoa1, ext_type, bFlagMargin );

            pSeg->stPDW.uiCount = 2;

            // 기준 펄스수를 만족 (성공)
            if( pSeg->stPDW.uiCount >= coRefPulse ) {
                pSeg->stPDW.pIndex[0] = index1;
                pSeg->stPDW.pIndex[1] = index2;

                // 아래의 idx 변수는 그룹화된 펄스열의 인덱스를 가리킨다.
                pSeg->gr_ref_idx = i1;
                pSeg->first_idx = i1;
                pSeg->last_idx = i2;

                pSeg->fJitterRatio = CalcRefPRI( pSeg->stPDW.pIndex, pSeg->stPDW.uiCount, & pSeg->stPRI );

                // 추적 펄스열 추출에서 PRI 범위는 분석된 에미터의 PRI 범위로 강제 설정한다.
                //-- 조철희 2005-10-18 19:02:16 --//
                if( bFlagMargin == TRUE && ext_type == _JITTER_RANDOM ) {
                    pSeg->stPRI.tMin = pPriRange->tMinPRI;
                    pSeg->stPRI.tMax = pPriRange->tMaxPRI;
                }

                /*! \bug  기본 펄스열의 PRI 형태를 저장
                    \date 2006-08-29 08:45:08, 조철희
                */
                // pSeg->pri_type = _STABLE;
                if( ext_type == _STABLE || ext_type == _REFSTABLE )
                    pSeg->enPriType = _STABLE;
                else if( ext_type == _DWELL )
                    pSeg->enPriType = _DWELL;
                else
                    pSeg->enPriType = _JITTER_RANDOM;

                // 선택한 펄스열의 초기화를 여기서 처리한다.
                pSeg->uiMiss = 0;
                pSeg->enMark = NORMAL_SEG;

                /*! \bug  기준 펄스열의 주파수 정보를 저장한다.
                        \date 2006-08-11 10:42:15, 조철희
                */
                CalcEmitterFrq( pSeg );

                /*! \bug  기준 펄스열의 펄스폭 정보를 저장한다.
                    \date 2007-06-20 11:23:47, 조철희
                */
                CalcEmitterPW( pSeg );

                // 밴드 코드 설정
#if defined(_ELINT_) || defined(_XBAND_)
                pSeg->uiBand = m_pBAND[ pSeg->stPDW.pIndex[0] ];
#else
                pSeg->uiBand = m_pBAND[ pSeg->stPDW.pIndex[0] ] + 1;
#endif

                pSeg->uiStat = m_pSTAT[ pSeg->stPDW.pIndex[0] ];

                pSeg->uiFreqType = AnalFreqType( pSeg );

                return TRUE;
            }

            last_index3 = pColPdwIndex->uiCount;
            for( i3=i2+1 ; i3 < last_index3 ; ++i3 ) {
                index3 = pPdwIndex[i3];

                // 추출된 펄스 제외
                if( m_pMARK[ index3 ] != UnMark )
                    continue;

                dtoa2 = m_pTOA[ index3 ] - second_toa;

                // PRI 범위 미만
                if( dtoa2 < pPriRange->tMinPRI )
                    continue;

                if(bFlagMargin == TRUE && dtoa1 > pPriRange->tMaxPRI )
                    break;

                // DTOA1 과 DTOA2의 차이가 너무 적으면 건너뛴다.
                //-- 조철희 2005-11-16 11:12:09 --//
                //if( ext_type == _JITTER && _diffabs( dtoa1, dtoa2 ) <= STABLE_MARGIN )
                //	continue;

                // PRI 범위 미만
                if( dtoa2 < ( dtoa1 - margin.tHgh ) )
                    continue;

                // PRI 범위를 벗어남
                diff = _diffabs<_TOA>( dtoa1, dtoa2 );
                if( diff > margin.tHgh || diff < margin.tLow )
                    break;

                // 펄스열의 정보를 저장한다.
                // pSeg->pri.mean = DivideBy2( dtoa1, dtoa2 );
                pSeg->stPDW.pIndex[ pSeg->stPDW.uiCount++ ] = index3;
                second_toa = m_pTOA[ index3 ];

                //-- 조철희 2005-11-18 14:37:57 --//
                dtoa1 = dtoa2;

                // 기준 펄스수를 만족 (성공)
                if( pSeg->stPDW.uiCount >= coRefPulse ) {
                    pSeg->stPDW.pIndex[0] = index1;
                    pSeg->stPDW.pIndex[1] = index2;

                    // 아래의 idx 변수는 그룹화된 펄스열의 인덱스를 가리킨다.
                    pSeg->gr_ref_idx = i1;
                    pSeg->first_idx = i1;
                    pSeg->last_idx = i3;

                    pSeg->fJitterRatio = CalcRefPRI( pSeg->stPDW.pIndex, pSeg->stPDW.uiCount, & pSeg->stPRI );
                    //-- 조철희 2005-11-11 13:58:07 --//
                    // pSeg->jitter_p = 0.5;
                    //-- 조철희 2005-10-07 16:53:21 --//
                    // 불규칙성 펄스열로 추출하려고 하는데 지터율이 0이라면 강제 +- 50%로 해서
                    // 나머지 펄스열을 추출하게 한다.
                    // 이렇게 하지 않으면 이전에 추출했던 규칙성 펄스열이 생길수 있기 때문이다.
                    if( ext_type == _JITTER_RANDOM && pSeg->fJitterRatio == 0 ) {
                        pSeg->fJitterRatio = (float) 0.40;
                    }

                    // 추적 펄스열 추출에서 PRI 범위는 분석된 에미터의 PRI 범위로 강제 설정한다.
                    //-- 조철희 2005-10-18 19:02:16 --//
                    if(bFlagMargin == TRUE && ext_type == _JITTER_RANDOM ) {
                        pSeg->stPRI.tMin = pPriRange->tMinPRI;
                        pSeg->stPRI.tMax = pPriRange->tMaxPRI;
                    }

                    /*! \bug  PRI 평균값은 최대 PRI로 정한 값 이내이어야 한다. 이 보다 크면 버린다.
                        \date 2006-07-05 16:27:42, 조철희
                    */
                    if( (UINT) pSeg->stPRI.tMean >= m_jit_pri_table[MAX_PRI_RANGE-1].tMaxPRI ) {
                        break;
                    }

                    // 기준 펄스열의 PRI 최대/최소값이 STABLE_MARGIN 이내이면 이 기준 펄스열은 무시한도록 한다.
                    if( ( ext_type == _STABLE || ext_type == _REFSTABLE || ext_type == _DWELL ) ||
                        ( ext_type == _JITTER_RANDOM && ( pSeg->fJitterRatio < MAX_JITTER_R || bIgnoreJitterP == TRUE ) && (_TOA) ( pSeg->stPRI.tMax-pSeg->stPRI.tMin ) > STABLE_MARGIN ) ) {
                        // pSeg->pri_type = AnalPRIType( pSeg, ext_type );
                        if( ext_type == _STABLE || ext_type == _REFSTABLE ) {
                            pSeg->enPriType = _STABLE;
                        }
                        else if( ext_type == _DWELL  ) {
                            pSeg->enPriType = _DWELL;
                        }
                        else {
                            pSeg->enPriType = _JITTER_RANDOM;
                        }

                        // 선택한 펄스열의 초기화를 여기서 처리한다.
                        pSeg->uiMiss = 0;
                        pSeg->enMark = NORMAL_SEG;

                        pSeg->tFirst = m_pTOA[ i1 ];
                        pSeg->tLast = m_pTOA[ i3 ];

                        /*! \bug  기준 펄스열의 주파수 정보를 저장한다.
                            \date 2006-08-11 10:42:15, 조철희
                        */
                        CalcEmitterFrq( pSeg );

                        /*! \bug  기준 펄스열의 펄스폭 정보를 저장한다.
                                \date 2007-06-20 11:23:47, 조철희
                        */
                        CalcEmitterPW( pSeg );

                        // 밴드 코드 설정
#if defined(_ELINT_) || defined(_XBAND_)
                        pSeg->uiBand = m_pBAND[ pSeg->stPDW.pIndex[0] ];
#else
                        pSeg->uiBand = m_pBAND[ pSeg->stPDW.pIndex[0] ] + 1;
#endif
                        pSeg->uiStat = m_pSTAT[ pSeg->stPDW.pIndex[0] ];

                        pSeg->uiFreqType = AnalFreqType( pSeg );

                        return TRUE;
                    }
                }
            }
        }
    }

    return FALSE;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt::CalcEmitterPW
// 반환되는 형  : void
// 함 수 인 자  : STR_PULSE_TRAIN_SEG *pSeg
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2007-06-20 11:24:42
//
void CPulExt::CalcEmitterPW( STR_PULSE_TRAIN_SEG *pSeg )
{
    int i, count;
    STR_MINMAX *pPw;
    PDWINDEX *pPdwIndex;

    pPdwIndex = pSeg->stPDW.pIndex;
    count = pSeg->stPDW.uiCount;
    pPw = & pSeg->pw;
    _EQUALS4( pPw->iMin, pPw->iMax, pPw->iMean, m_pPW[ *pPdwIndex ] )
    pPdwIndex ++;
    for( i=1 ; i < count ; ++i, ++pPdwIndex ) {
        int pw;

        pw = m_pPW[ *pPdwIndex ];

        pPw->iMin = _min( pPw->iMin, pw );
        pPw->iMax = _max( pPw->iMax, pw );

        pPw->iMean += pw;
    }

    // 펄스 평균은 Median 값으로 한다.
    //-- 조철희 2005-11-01 14:10:03 --//
    pPw->iMean = UDIV( pPw->iMean, count );
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CPulExt::CalcEmitterFrq
//! \author   조철희
//! \param    pSeg 인자형태 STR_PULSE_TRAIN_SEG *
//! \return   void
//! \version  1.37
//! \date     2006-08-11 10:44:09
//! \warning
//
void CPulExt::CalcEmitterFrq( STR_PULSE_TRAIN_SEG *pSeg )
{
    int i, count;
    STR_MINMAX_MEDIAN *pFrq;
    PDWINDEX *pPdwIndex;

    pPdwIndex = pSeg->stPDW.pIndex;
    count = pSeg->stPDW.uiCount;
    pFrq = & pSeg->freq;
    _EQUALS4( pFrq->iMin, pFrq->iMax, pFrq->iMean, m_pFREQ[ *pPdwIndex++ ] )
    for( i=1 ; i < count ; ++i, ++pPdwIndex ) {
        int freq;

        freq = m_pFREQ[ *pPdwIndex ];

        pFrq->iMin = _min( pFrq->iMin, freq );
        pFrq->iMax = _max( pFrq->iMax, freq );

        pFrq->iMean += freq;
    }

    // 주파수 평균은 Median 값으로 한다.
    //-- 조철희 2005-11-01 14:10:03 --//
    pFrq->iMean = UDIV( pFrq->iMean, count );
    pFrq->iMedian = MedianFreq( NULL, pSeg->stPDW.pIndex, pSeg->stPDW.uiCount );

}

/**
 * @brief     기준 펄스열의 기준 펄스를 시작으로 이전시간에 존재하는 펄스열을 추출한다.
 *            동일한 PRI로 추출 MAX_MISS를 고려 하여 추출한다. 해당 펄스열에 속한 펄스를 최대한 걸러내어 다음 stage에서 분석에 혼란을 줄이는 것이 목적이다.
 * @param     STR_PULSE_TRAIN_SEG * pSeg
 * @param     int ext_type
 * @param     STR_PDWINDEX * pColPdwIndex
 * @param     _TOA margin
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2005-05-03 22:55:53
 * @warning
 */
void CPulExt::ExtractBackPT( STR_PULSE_TRAIN_SEG *pSeg, int ext_type, STR_PDWINDEX *pColPdwIndex, _TOA margin )
{
    int index;
    UINT max_miss;
    UINT uiMiss;

    _TOA dtoa_margin;

    int bak_count;

    _TOA pre_toa, dtoa;

    STR_LOWHIGH_TOA pri_range;

    PDWINDEX *pGrPdwIndex, *pSegPdwIndex, *pLastIndex;

    // 경고 메시지 처리
    if( m_uiMaxPdw <= pSeg->stPDW.uiCount+1 ) {
        Log( enError, "펄스열의 인덱스가 잘못됐습니다.[%d] !" , pSeg->stPDW.uiCount );
        WhereIs;
    }
    else {

        // 규칙성 또는 불규칙성 펄스열 추출에 대한 마킹 타입 결정
        //if( ext_type == _STABLE )		markType = STABLE_MARK;
        //else												markType = JITTER_MARK;

        // PRI 타입에 따른 최대 누락 개수 및 DTOA 마진 설정
        if( margin == 0 ) {
            dtoa_margin = CalDtoaMargin( ext_type, pSeg );
            pri_range.tLow = max( pSeg->stPRI.tMean - dtoa_margin, ITTOAusCNV((_TOA)1) );
            pri_range.tHgh = max( pSeg->stPRI.tMean + dtoa_margin, ITTOAusCNV((_TOA)1) );
        }
        else {
            /*! \bug  추적 펄스열에서는 기본 팔스열의 PRI 범위로 추적하게 한다.
                \date 2006-08-28 09:27:28, 조철희
            */
            pri_range.tLow = max( pSeg->stPRI.tMin, ITTOAusCNV((_TOA)1) );
            pri_range.tHgh = max( pSeg->stPRI.tMax, ITTOAusCNV((_TOA)1) );
        }

        // 누락 개수 정의
        max_miss = CalMaxMiss( ext_type ) + 1;

        pLastIndex = NULL;

        // 저장된 PDW 인덱스열을 맨 뒤로 복사한다.
        bak_count = pSeg->stPDW.uiCount;
        memcpy( & pSeg->stPDW.pIndex[ m_uiMaxPdw-bak_count ], pSeg->stPDW.pIndex, bak_count * sizeof( PDWINDEX ) );

        // PDW 인덱스는 0번째부터 저장한다.
        pGrPdwIndex = & pColPdwIndex->pIndex[pSeg->gr_ref_idx];
        pSegPdwIndex = & pSeg->stPDW.pIndex[ m_uiMaxPdw-bak_count-1 ];
        pre_toa = m_pTOA[ pSeg->stPDW.pIndex[0] ];
    
        while( pGrPdwIndex != pColPdwIndex->pIndex ) {
            -- pGrPdwIndex;
            index = *pGrPdwIndex;
            if( m_pMARK[index] != 0 ) {
                continue;
            }

            /*! \bug  주파수 정보를 이용한 펄스열 추출 추가함.
                \date 2006-08-11 11:21:28, 조철희
            */
            if( margin != 0 && IsValidPDW( index, pSeg ) == FALSE ) {
                continue;
            }

            dtoa = pre_toa - m_pTOA[index];

            // 펄스
            if( dtoa < (UINT) pri_range.tLow ) {
                continue;
            }

            // 펄스 존재시에 처리를 한다.
            else if( TRUE == CompMarginDiff<_TOA>( dtoa, pri_range.tLow, pri_range.tHgh, 0 ) ) {
                pLastIndex = pSegPdwIndex;

                pre_toa = m_pTOA[index];

                // 펄스열 정보에 PDW 한개 추가함.
                *pSegPdwIndex-- = index;
                ++ pSeg->stPDW.uiCount;

                pSeg->first_idx = ( pGrPdwIndex-pColPdwIndex->pIndex );
            }
            // 펄스가 누락 처리 또는 다른 신호인지를 검사한다.
            else if( dtoa > (UINT) pri_range.tHgh ) {
                uiMiss = CheckHarmonicTOA<_TOA>( dtoa, pSeg->stPRI.tMean, (_TOA) ITTOAusCNV((_TOA)5) );

                if( uiMiss <= max_miss ) {
                    if( uiMiss > _spOne && TRUE == CompMarginDiff<_TOA>( dtoa, uiMiss*pri_range.tLow, uiMiss*pri_range.tHgh, 0 ) ) {
                        pLastIndex = pSegPdwIndex;

                        pre_toa = m_pTOA[index];

                        // 펄스열 정보에 PDW 한개 추가함.
                        *pSegPdwIndex-- = index;
                        ++ pSeg->stPDW.uiCount;
                        pSeg->first_idx = ( pGrPdwIndex-pColPdwIndex->pIndex );

                        pSeg->uiMiss += ( uiMiss - 1 );
                    }
                }
                else {
                    break;
                }
            }
            else if( dtoa > (UINT) ( max_miss * pri_range.tHgh ) ) {
                break;
            }
        }

        if( pLastIndex != NULL ) {
            memcpy( & pSeg->stPDW.pIndex[0], & pSeg->stPDW.pIndex[ m_uiMaxPdw-pSeg->stPDW.uiCount ], pSeg->stPDW.uiCount * sizeof( PDWINDEX ) );
        }
    }

    return;
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    기준 펄스열의 주파수 및 펄스폭  정보를 비교해서 입력한 PDW 정보와 유사한지를 판단한다.
//! \author   조철희
//! \param    index 인자형태 int
//! \param    pSeg 인자형태 STR_PULSE_TRAIN_SEG *
//! \return   BOOL
//! \version  1.37
//! \date     2006-08-11 11:21:28
//! \warning
//
BOOL CPulExt::IsValidPDW( int index, STR_PULSE_TRAIN_SEG *pSeg )
{
    BOOL bRet;

    if( pSeg->uiFreqType == _FIXED ) {
        int threshold;

        int iBand = m_pBAND[index];
        threshold = IFRQMhzCNV( 0, FIXED_FREQ_MARGIN );

// #if defined(_ELINT_) || defined(_XBAND_)
//         threshold = IFRQMhzCNV( 0, FIXED_FREQ_MARGIN );
// 
// #elif _POCKETSONATA_
//         threshold = (UINT) IFRQMhzCNV( 0, FIXED_FREQ_MARGIN );
// 
// #else
//         int band;
// 
//         band = m_pBAND[ index ];
//         threshold = 2 * abs( (int) IDIV( FIXED_FREQ_MARGIN, gFreqRes[band+1].fRes ) );
// #endif

        if( CompMeanDiff<UINT>( m_pFREQ[ index ], pSeg->freq.iMean, threshold ) == TRUE ) {
            bRet = true;
        }
        else {
            bRet = false;
        }
    }
    // Random Agile 일 경우...
    else {
        int diff;
        /*! \bug  기준 펄스열의 펄스폭을 고려해서 펄스 추출할 대상을 비교한다.
            \date 2007-06-19 18:01:57, 조철희
        */
        diff = 2 * ( pSeg->pw.iMax - pSeg->pw.iMin );
        if( CompMarginDiff<UINT>( m_pPW[index], pSeg->pw.iMin, pSeg->pw.iMax, diff ) ) {
            bRet = true;
        }
        else {
            bRet = false;
        }
    }

    return bRet;
}

/**
 * @brief     기준 펄스열을 기준으로 고정/지터 펄스열을 추출한다.
 * @param     STR_PULSE_TRAIN_SEG * pSeg
 * @param     int ext_type
 * @param     STR_PDWINDEX * pColPdwIndex
 * @param     _TOA margin
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2005-05-04 17:53:41
 * @warning
 */
void CPulExt::ExtractForPT(STR_PULSE_TRAIN_SEG *pSeg, int ext_type, STR_PDWINDEX *pColPdwIndex, _TOA margin )
{
    int index;

    _TOA dtoa_margin;
	UINT uiMiss, uiMaxMiss;

    _TOA pre_toa, dtoa;

    STR_LOWHIGH_TOA pri_range;

    PDWINDEX *pGrPdwIndex, *pSegPdwIndex;

    if( pSeg->stPDW.uiCount <= _spOne ) {
        printf( "\n [W] PDW index error[%d] !" , pSeg->stPDW.uiCount );
        WhereIs;
    }
    else {
        pGrPdwIndex = & pColPdwIndex->pIndex[pSeg->last_idx+1];
        if( pGrPdwIndex > & pColPdwIndex->pIndex[pColPdwIndex->uiCount-1] ) {
            // return;
        }
        else {
            // 규칙성 또는 불규칙성 펄스열 추출에 대한 마킹 타입 결정
            //if( ext_type == _STABLE )		markType = STABLE_MARK;
            //else												markType = JITTER_MARK;

            // PRI 타입에 따른 최대 누락 개수 및 DTOA 마진 설정
            if( margin == 0 ) {
                dtoa_margin = CalDtoaMargin( ext_type, pSeg );
                pri_range.tLow =_max(pSeg->stPRI.tMean - dtoa_margin, (_TOA) ITOAusCNV((_TOA)1) );
                pri_range.tHgh = max(pSeg->stPRI.tMean + dtoa_margin, (_TOA) ITOAusCNV((_TOA)1) );
            }
            else {
                /*! \bug  추적 펄스열에서는 기본 팔스열의 PRI 범위로 추적하게 한다.
                    \date 2006-08-28 09:27:28, 조철희
                */
                pri_range.tLow = max(pSeg->stPRI.tMin, (_TOA) ITOAusCNV((_TOA)1) );
                pri_range.tHgh = max(pSeg->stPRI.tMax, (_TOA) ITOAusCNV((_TOA)1) );
            }

            // 누락 개수 정의
            uiMaxMiss = CalMaxMiss( ext_type ) + 1;

            pSegPdwIndex = & pSeg->stPDW.pIndex[ pSeg->stPDW.uiCount ];

            pre_toa = m_pTOA[ pColPdwIndex->pIndex[pSeg->last_idx] ];
            //for( i=pSeg->last_idx+1 ; i < pColPdwIndex->count ; ++i ) {
            while( pGrPdwIndex != & pColPdwIndex->pIndex[pColPdwIndex->uiCount] ) {
                index = *pGrPdwIndex++;
                if( m_pMARK[index] != 0 )
                    continue;

                /*! \bug  주파수 정보를 이용한 펄스열 추출 추가함.
                    \date 2006-08-11 11:21:28, 조철희
                */
                if( margin != 0 && IsValidPDW( index, pSeg ) == FALSE ) {
                    continue;
                }

                dtoa = m_pTOA[index] - pre_toa;

                // 펄스
                if( dtoa < (UINT) pri_range.tLow ) {
                    continue;
                }

                // 펄스 존재시에 처리를 한다.
                else if( TRUE == CompMarginDiff<_TOA>( dtoa, pri_range.tLow, pri_range.tHgh, 0 ) ) {
                    pre_toa = m_pTOA[index];

                    // 펄스열 정보에 PDW 한개 추가함.
                    *pSegPdwIndex++ = index;
                    ++ pSeg->stPDW.uiCount;

                    pSeg->last_idx = ( pGrPdwIndex-pColPdwIndex->pIndex ) - 1;
                }
                // 펄스가 누락 처리 또는 다른 신호인지를 검사한다.
                else if( dtoa > (UINT) pri_range.tHgh ) {
                    uiMiss = CheckHarmonicTOA<_TOA>( dtoa, pSeg->stPRI.tMean, (_TOA) ITOAusCNV((_TOA)5) );

                    if( uiMiss <= uiMaxMiss ) {
                        if( uiMiss > _spOne && TRUE == CompMeanDiff<_TOA>( dtoa, uiMiss*pSeg->stPRI.tMean, ( _TOA ) ITOAusCNV( ( _TOA ) 5 ) ) ) {
                            pre_toa = m_pTOA[index];

                            // 펄스열 정보에 PDW 한개 추가함.
                            *pSegPdwIndex++ = index;
                            ++pSeg->stPDW.uiCount;
                            pSeg->last_idx = (pGrPdwIndex - pColPdwIndex->pIndex) - 1;

                            pSeg->uiMiss += (uiMiss - 1);
                        }
                    }
                    else {
                        break;
                    }

                }
            }
        }
    }

    return;
}

/**
 * @brief     추출한 펄스열에 대해서 지터율을 계산한다.
 * @param     PDWINDEX * pPdwIndex
 * @param     UINT count
 * @param     STR_MINMAX_TOA * pPRI
 * @return    float
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2005-05-04 16:24:18
 * @warning
 */
float CPulExt::CalcRefPRI( PDWINDEX *pPdwIndex, UINT count, STR_MINMAX_TOA *pPRI )
{
    int i;
    _TOA dtoa, total_dtoa, pre_toa, toa;

    float jitter_p=(float) -1.0;

    if( count <= 1 ) {
    }
    else {
        total_dtoa = 0;
        //jitter_p = 0.0;

        pPRI->tMax = 0;
        pPRI->tMin = ( _TOA ) (-1);

        pre_toa = m_pTOA[*pPdwIndex++];
        for( i = 1 ; i < ( int ) count ; ++i ) {
            toa = m_pTOA[*pPdwIndex++];
            dtoa = toa - pre_toa;
            pre_toa = toa;

            total_dtoa += dtoa;
            pPRI->tMax = max( pPRI->tMax, dtoa );
            pPRI->tMin = min( pPRI->tMin, dtoa );
        }

        pPRI->tMean = TDIV<_TOA>( total_dtoa, count - 1 );
        dtoa = pPRI->tMax - pPRI->tMin;
        jitter_p = ( float ) dtoa / (float) pPRI->tMean;
        //jitter_p = ( float ) (pPRI->tMax - pPRI->tMin) / pPRI->tMean;
    }

    return jitter_p;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt::DiscardStablePulseTrain
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-19 15:17:58
//
//##ModelId=429A5BDB0119
void CPulExt::DiscardStablePulseTrain()
{
    unsigned int i, j;
    int nCoDiscard;

    BOOL bCheck;

    STR_PULSE_TRAIN_SEG *pSeg1, *pSeg2;

    nCoDiscard = 0;
    pSeg1 = & m_Seg[m_uiAnalSeg];
    for( i=m_uiRefStartSeg ; i < m_uiCoSeg ; ++i, ++pSeg1 ) {
        if( pSeg1->enMark == DELETE_SEG ) {
            continue;
        }

        if( pSeg1->enPriType == _STABLE ) {
            bCheck = TRUE;
            pSeg2 = & m_Seg[i+1];

            for( j=i+1 ; j < m_uiCoSeg ; ++j, ++pSeg2 ) {
                if( pSeg2->enMark == DELETE_SEG ) {
                    continue;
                }

                if( pSeg2->enPriType == _STABLE && CompMeanDiff<_TOA>( pSeg1->stPRI.tMean, pSeg2->stPRI.tMean, STABLE_MARGIN ) == TRUE ) {
                    if( OverlappedSeg( pSeg1, pSeg2 ) == true ) {
                        bCheck = FALSE;

                        // 버릴 SEG의 인덱스를 표시한다.
                        pSeg2->enMark = DELETE_SEG;

                        MarkToPDWIndex( pSeg2, UnMark );
                    }
                }
            }

            if( bCheck == FALSE ) {
                // 버릴 SEG의 인덱스를 표시한다.
                pSeg1->enMark = DELETE_SEG;

                MarkToPDWIndex( pSeg1, UnMark );
            }
        }
    }

    // SEG 열을 정리한다. m_nDiscardSeg 열에 저장된 인덱스를 참조한다.
    nCoDiscard = 0;
    pSeg1 = & m_Seg[m_uiAnalSeg];
    for( i=m_uiAnalSeg ; i < m_uiCoSeg ; ++i ) {
        if( pSeg1->enMark == DELETE_SEG ) {
            ++ nCoDiscard;

            //size = sizeof( STR_PULSE_TRAIN_SEG ) * ( m_CoSeg - i - 1 );
            //memcpy( pSeg1, pSeg1+1, size );
            pSeg2 = pSeg1;
            for( j=0 ; j < m_uiCoSeg - i - 1 ; ++j ) {
                PDWINDEX *bakup1;

                bakup1 = pSeg2->stPDW.pIndex;
                memcpy( pSeg2, & pSeg2[1], sizeof( STR_PULSE_TRAIN_SEG ) );
                pSeg2[1].stPDW.pIndex = bakup1;

                ++ pSeg2;
            }
        }

        ++ pSeg1;
    }

    m_uiCoSeg = m_uiCoSeg - nCoDiscard;
}

/**
 * @brief     펄스열의 마킹 정보를 설정한다.
 * @param     STR_PULSE_TRAIN_SEG * pSeg
 * @param     int usMarkType
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2005-05-08 01:18:36
 * @warning
 */
// void CPulExt::MarkToPDWIndex( STR_PULSE_TRAIN_SEG *pSeg, USHORT usMarkType )
// {
//     MarkToPDWIndex( pSeg->stPDW.pIndex, pSeg->stPDW.uiCount, usMarkType );
// 
// }

/**
 * @brief     펄스열의 마킹 정보를 설정한다.
 * @param     PDWINDEX * pPDWIndex
 * @param     UINT uiCount
 * @param     USHORT usMarkType
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-06-16, 10:52
 * @warning
 */
void CPulExt::MarkToPDWIndex( PDWINDEX *pPDWIndex, UINT uiCount, USHORT usMarkType )
{
    unsigned int i;

    for( i = 0 ; i < uiCount ; ++i ) {
        m_pMARK[*pPDWIndex++] = usMarkType;
    }

}

/**
 * @brief     펄스열 정보를 계산한다.
 * @param     STR_PULSE_TRAIN_SEG * pSeg
 * @param     BOOL bIgnoreJitterP
 * @return    BOOL
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2005-05-08 01:22:38
 * @warning
 */
BOOL CPulExt::CalcSegParam(STR_PULSE_TRAIN_SEG *pSeg, BOOL bIgnoreJitterP )
{
	BOOL bRet=TRUE;

    unsigned int i;
    int val;
	PDWINDEX *pPdwIndex;

    int dtoa_count;
    int frstAoa, aoaMean, diffAoa, overAoa;
    _TOA preToa, dtoa, toa;
    UINT freqMean, pwMean;
    int paMean;
    _TOA priMean;

    unsigned int uiCount;

    STR_LOWHIGH_TOA dtoa_range;

    if( bIgnoreJitterP == FALSE ) {
        priMean = UDIV( pSeg->stPRI.tMin + pSeg->stPRI.tMax, 2 );
        dtoa_range.tLow = _max( ITTOAusCNV((_TOA)2), UDIV( 2 * priMean, 3 ) );
        dtoa_range.tHgh = _max( ITTOAusCNV((_TOA)2), UDIV( 4 * priMean, 3 ) );

        //pSeg->pri.max = pSeg->pri.min = priMean = pSeg->pri.mean;
    }
    else {
        //priMean = UDIV( pSeg->pri.min + pSeg->pri.max, 2 );
        dtoa_range.tLow = 1;
        dtoa_range.tHgh = pSeg->stPRI.tMax;

        pSeg->stPRI.tMax = 0;
        pSeg->stPRI.tMin = UINT64_MAX;
    }

    // 펄스열의 최초시간 및 마지막 시간 설정
    pSeg->tLast = m_pTOA[ m_pGrPdwIndex->pIndex[ pSeg->last_idx ] ];
    pSeg->tFirst = m_pTOA[ m_pGrPdwIndex->pIndex[ pSeg->first_idx ] ];

    _EQUALS5( freqMean, pwMean, paMean, aoaMean, _spZero )
    _EQUALS5( pSeg->freq.iMax, pSeg->stPA.iMax, pSeg->pw.iMax, pSeg->stAOA.iMax, INT32_MIN)
    _EQUALS5( pSeg->freq.iMin, pSeg->stPA.iMin, pSeg->pw.iMin, pSeg->stAOA.iMin, INT32_MAX )

    /*! \bug  priMean 값의 최기값으로 pSeg->pri.mean 값으로 했기 때문에 dtoa_count의 초기값은 1로 함.
        \date 2006-08-25 15:47:53, 조철희
    */
	priMean = 0;
    dtoa_count = 0;
	
    pPdwIndex = & pSeg->stPDW.pIndex[0];
    preToa = m_pTOA[*pPdwIndex];
    uiCount = pSeg->stPDW.uiCount;
    frstAoa = m_pAOA[*pPdwIndex];
    for( i=0 ; i < uiCount; ++i ) {
        toa = m_pTOA[*pPdwIndex];
        dtoa = toa - preToa;

        if( i == 0 ) {
            frstAoa = m_pAOA[*pPdwIndex];

            _EQUALS3( pSeg->freq.iMax, pSeg->freq.iMin, m_pFREQ[*pPdwIndex] )
            _EQUALS3( pSeg->stPA.iMax, pSeg->stPA.iMin, m_pPA[*pPdwIndex] )
            _EQUALS3( pSeg->pw.iMax, pSeg->pw.iMin, m_pPW[*pPdwIndex] )
            _EQUALS3( pSeg->stAOA.iMax, pSeg->stAOA.iMin, 0 )
        }

        // DTOA 계산
        preToa = toa;
        if( CompMarginDiff<_TOA>( dtoa, dtoa_range.tLow, dtoa_range.tHgh, 0 ) == TRUE ) {
            priMean += dtoa;
            pSeg->stPRI.tMax = max( pSeg->stPRI.tMax, dtoa );
            pSeg->stPRI.tMin = min( pSeg->stPRI.tMin, dtoa );

            ++ dtoa_count;
        }

        // 주파수 평균 계산
        val = m_pFREQ[*pPdwIndex];
        freqMean += val;
        pSeg->freq.iMax = max( pSeg->freq.iMax, val );
        pSeg->freq.iMin = min( pSeg->freq.iMin, val );

        // 펄스폭 평균 계산
        val = m_pPW[*pPdwIndex];
        pwMean += val;
        pSeg->pw.iMax = max( pSeg->pw.iMax, val );
        pSeg->pw.iMin = min( pSeg->pw.iMin, val );

        // 신호 세기 평균 계산
        val = m_pPA[*pPdwIndex];
        paMean += val;
        pSeg->stPA.iMax = max( pSeg->stPA.iMax, val );
        pSeg->stPA.iMin = min( pSeg->stPA.iMin, val );

        // 방위 평균 계산
        //-- 조철희 2005-10-12 14:32:18 --//
        diffAoa = (int) m_pAOA[*pPdwIndex] - frstAoa;
        overAoa = _abs( diffAoa );
        if( overAoa > MAX_AOA/2 ) {
            if( frstAoa > MAX_AOA/2 )
                diffAoa = diffAoa + MAX_AOA;
            else
                diffAoa = diffAoa - MAX_AOA;
        }

        aoaMean += diffAoa;
        pSeg->stAOA.iMax = max( pSeg->stAOA.iMax, (int) diffAoa );
        pSeg->stAOA.iMin = min( pSeg->stAOA.iMin, (int) diffAoa );

        ++ pPdwIndex;
    }

    // 평균값 계산, 신호세기, 펄스폭, 주파수, 방위
    pSeg->stPA.iMean = UDIV( paMean, uiCount);
    pSeg->pw.iMean = UDIV( pwMean, uiCount);
    pSeg->freq.iMean = UDIV( freqMean, uiCount);
    pSeg->stAOA.iMean = ( MAX_AOA + IDIV( aoaMean, uiCount) + frstAoa ) % MAX_AOA;
    pSeg->stAOA.iMax = ( MAX_AOA + pSeg->stAOA.iMax + frstAoa ) % MAX_AOA;
    pSeg->stAOA.iMin = ( MAX_AOA + pSeg->stAOA.iMin + frstAoa ) % MAX_AOA;
    diffAoa = pSeg->stAOA.iMax - pSeg->stAOA.iMin;
    if( diffAoa > MAX_AOA/2 ) {
        diffAoa = pSeg->stAOA.iMax;
        pSeg->stAOA.iMax = pSeg->stAOA.iMin;
        pSeg->stAOA.iMin = diffAoa;
    }

    // 전방위로 방위가 분포가 될 때 방위 최소/최대값이 잘못 될수 있다.
    // 그룹화의 방위 범위를 보고 방위의 최소/최대 값을 결정한다.
// 	if( ( pSeg->aoa.min <= pSeg->aoa.mean && pSeg->aoa.max >= pSeg->aoa.mean ) || ( pSeg->aoa.min <= pSeg->aoa.mean && ( pSeg->aoa.max + MAX_AOA ) >= pSeg->aoa.mean ) ) {
// 	}
// 	else {
// 		int swap;
//
// 		swap = pSeg->aoa.min;
// 		pSeg->aoa.min = pSeg->aoa.max;
// 		pSeg->aoa.max = swap;
// 	}

    // PRI 의 최대/최소 및 평군값을 계산한다.
    CalPRIRange( pSeg, priMean, dtoa_count );

    // PRI 타입 변경
    // 펄스열 추출한 후에 PRI 평균이 규칙성 펄스열 범위 안에 들면 RPI 타입을 변경한다.
    if( pSeg->enPriType == _JITTER_RANDOM ) {
        dtoa = pSeg->stPRI.tMax - pSeg->stPRI.tMin;
        // 1% 지터율 이상인 것은 STABLE 펄스열로 간주한다.
        if( dtoa < STABLE_MARGIN || pSeg->fJitterRatio <= 0.009 ) {
            // 일단 생략함...
            //-- 조철희 2005-11-25 17:31:19 --//
            // pSeg->pri_type = _STABLE;
        }
    }

    // 밴드 코드 설정
#if defined(_ELINT_) || defined(_XBAND_)
    pSeg->uiBand = m_pBAND[ pSeg->stPDW.pIndex[0] ];
#else
    pSeg->uiBand = m_pBAND[ pSeg->stPDW.pIndex[0] ] + 1;
#endif
    pSeg->uiStat = m_pSTAT[ pSeg->stPDW.pIndex[0] ];

    pSeg->uiFreqType = AnalFreqType( pSeg );

    // 펄스 연속성 연산
    _TOA span_time=pSeg->tLast - pSeg->tFirst;
    // pSeg->continuity = UDIV( 100 * pSeg->pdw.count, pSeg->pdw.count + 누락 개수);
    pSeg->uiContinuity = _min( 100, UDIV( ( (pSeg->stPDW.uiCount-1) * pSeg->stPRI.tMean * 100 ), span_time ) );

    if( ( bIgnoreJitterP == FALSE ) && ( ( pSeg->enPriType == _JITTER_RANDOM ) && ( TRUE == CompMeanDiff<_TOA>( pSeg->stPRI.tMax, pSeg->stPRI.tMin, STABLE_MARGIN ) ) ) )
        bRet = FALSE;

    return bRet;
}

/**
 * @brief     펄스열에 대해서 주파수 형태를 분석한다.
 * @param     STR_PULSE_TRAIN_SEG * pSeg
 * @return    UINT
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2005-07-15 10:22:10
 * @warning
 */
UINT CPulExt::AnalFreqType( STR_PULSE_TRAIN_SEG *pSeg )
{
    unsigned int i;
    unsigned int uiCount, coOkPdw;
    int freqMean;
    int threshold;

    UINT uiFreqType;

    PDWINDEX *pPdwIndex;

    /*! \bug  주파수 범위차가 10MHz 이내이면 FIXED 로 한다.
        \date 2006-08-24 12:08:01, 조철희
    */

    threshold = IFRQMhzCNV( pSeg->uiBand, FIXED_TYPE_FREQ_MARGIN );
    // freq = abs( (int) IDIV( 10, gFreqRes[ pSeg->uiBand ].fRes ) );

    if( CompMeanDiff( pSeg->freq.iMax, pSeg->freq.iMin, threshold ) == TRUE ) {
        uiFreqType = _FIXED;
    }
    else {
        //int band = m_pBAND[pSeg->stPDW.pIndex[0]];
        threshold = IFRQMhzCNV( pSeg->uiBand, FIXED_FREQ_MARGIN );

// #if defined(_ELINT_) || defined(_XBAND_)
//         threshold = IFRQMhzCNV( iBnad, FIXED_FREQ_MARGIN );
// #else
//         threshold = abs( (int) IDIV( FIXED_FREQ_MARGIN, gFreqRes[band+1].fRes ) );	// 2MHz
// #endif

        freqMean = pSeg->freq.iMedian;
        pPdwIndex = pSeg->stPDW.pIndex;
        uiCount = pSeg->stPDW.uiCount;
        coOkPdw = 0;
        for( i=0 ; i < uiCount; ++i ) {
            int freq;

            freq = m_pFREQ[ *pPdwIndex ];
            if( CompMeanDiff( freqMean, freq, threshold ) == TRUE ) {
                ++ coOkPdw;
            }
            ++ pPdwIndex;
        }

        int ratio=UDIV( 100 * coOkPdw, uiCount);

        //-- 조철희 2005-07-14 19:59:11 --//
        if( ratio >= FREQ_MEAN_MARGIN_THRESHOLD || (uiCount -coOkPdw) <= _spTwo )
            uiFreqType = _FIXED;
        else
            uiFreqType = _RANDOM_AGILE;
    }

    return uiFreqType;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt::ExtractJitterPT
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-10 16:39:50
//
//##ModelId=428832A10078
void CPulExt::ExtractJitterPT()
{
    int i;

    _TOA largest_pri;
    STR_PRI_RANGE_TABLE ext_range;

    // 추출되는 펄스열은 gSeg[]에 저장되며
    // 펄스열의 수는 gSeg_cnt에 의해 count 된다.
    // 펄스열의 추출은
    //			기준 펄스열 추출(extractRefPT()),
    //			후진 펄스열 추출(extractBackPT()),
    //			전진 펄스열 추출(extractForPT()),
    //			단순 펄스열 추출(extractSimpleJitterPT()),
    // 순으로 이루어지며 한번의 pass가 이루어지면 에미터가 하나 증가한다. gEmitter.count증가
    // 기준, 후진,전진 펄스열추출의 pass가 이루어지면 하나의 펄스열이 만들어지며
    // 펄스열의 수 gSeg_cnt가 증가 한다.
    // 하나의 에미터에는 동일한 PRI의 펄스열이 여러개 존재할수 있다.

    largest_pri = ( m_pTOA[ m_pGrPdwIndex->pIndex[m_pGrPdwIndex->uiCount-1] ] - m_pTOA[ m_pGrPdwIndex->pIndex[0] ] ) / _sp.cm.Mjpc;

    if( largest_pri > m_jit_pri_table[ m_uiEnd_pri_level-1 ].tMaxPRI )
        largest_pri = m_jit_pri_table[ m_uiEnd_pri_level-1 ].tMaxPRI;

    // 펄스열 기본 추출
    for( i=m_uiStart_pri_level ; i < (int) m_uiEnd_pri_level ; ++i ) {
        // PRI 범위 구하기
        ext_range.tMinPRI = m_jit_pri_table[ i ].tMinPRI;
        ext_range.tMaxPRI = m_jit_pri_table[ i ].tMaxPRI;

        if( ext_range.tMaxPRI > largest_pri && ext_range.tMinPRI < largest_pri )
            ext_range.tMaxPRI = largest_pri;

        ExtractJitterPT( & ext_range, i );
    }
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt::ExtractJitterPT
// 반환되는 형  : void
// 함 수 인 자  : STR_PRI_RANGE_TABLE *pExtRange
// 함 수 인 자  : int coRef
// 함 수 인 자  : BOOL flagMargin
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-07-28 17:56:09
//
//##ModelId=42E98F300347
void CPulExt::ExtractJitterPT( STR_PRI_RANGE_TABLE *pExtRange, unsigned int uiPriBand, unsigned int uiCoRef, BOOL flagMargin, int iMark, BOOL bIgnoreJitterP )
{
    int ref_idx;

    int startSeg;

    STR_PULSE_TRAIN_SEG *pSeg;

    if( m_pGrPdwIndex->uiCount == 0 ) {
        // return;
    }
    else {
        // 시작 PDW 인덱스
        ref_idx = 0;

        startSeg = m_uiCoSeg;

        for( ;; ) {
            if( m_uiCoSeg >= m_uiMaxSeg ) {
                break;
            }
            else {
                pSeg = & m_Seg[ m_uiCoSeg ];

                // 기준 펄스열 추출을 찾아서 존재하지 않으면 다음 밴드를 선택한다.
                if( TRUE == ExtractRefPT( pExtRange, _JITTER_RANDOM, pSeg, ref_idx, m_pGrPdwIndex, uiCoRef, flagMargin, bIgnoreJitterP ) ) {
                    ref_idx = pSeg->gr_ref_idx;
                    ExtractBackPT( pSeg, _JITTER_RANDOM, m_pGrPdwIndex, flagMargin );

                    ExtractForPT( pSeg, _JITTER_RANDOM, m_pGrPdwIndex, flagMargin );

                    // 펄스열은 기준펄스열로 추출된 것 이상인것만 체크한다.
                    if( ( flagMargin == TRUE && pSeg->stPDW.uiCount > (int) _sp.cm.Rpc ) || flagMargin == FALSE ) {
                    //-- 조철희 2005-12-07 14:45:52 --//
                        // 추출된 펄스열의 제원의 계산
                        // 지터로 추출하지 못할 때는 해당 펄스열을 버린다.
                        //-- 조철희 2005-12-19 15:18:29 --//
                        if( TRUE == CalcSegParam( pSeg, bIgnoreJitterP ) ) {
                            pSeg->uiPRI_Band = uiPriBand;

                            /*! \todo		주파수 그룹화에서 넓게 열어서 펄스열을 추출하기 때문에 시간적인 하모닉 관계가
                                                    있는 신호들이 같이 추출할 수 있다. 그래서, 추출한 펄스열에서
                                                    상세 펄스열 분석해서 펄스열 분리를 해야 한다.

                                                    그 방안으로 규칙성 펄스열에서 찾은 펄스열과 펄스열의 총 시간과
                                                    비교해서 신호 분리를 판단 한다.
                            */
                            // 추출된 펄스 Marking
                            MarkToPDWIndex( pSeg, iMark );

                            // 펄스열 인덱스 증가
                            ++ m_uiCoSeg;
                        }
                        else {
                            MarkToPDWIndex( pSeg, STABLE_MARK );
                        }
                    }

                    ++ ref_idx;
                }
                else {
                    break;
                }
            }
        }

            /*! \bug  지터 펄스열로 추출한 펄스열들중에서 유사 펄스열들을 병합시킨다.
                    \date 2006-08-23 10:53:25, 조철희
            */
            MergeJitterPulseTrain( startSeg, m_uiCoSeg, bIgnoreJitterP );

    }


}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt::ExtractPatternPT
// 반환되는 형  : void
// 함 수 인 자  : STR_PRI_RANGE_TABLE *pExtRange
// 함 수 인 자  : int coRef
// 함 수 인 자  : BOOL flagMargin
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-02-22 10:47:17
//
void CPulExt::ExtractPatternPT( STR_PRI_RANGE_TABLE *pExtRange, unsigned int uiCoRef, BOOL flagMargin )
{
    int ref_idx;
    _TOA margin;
    STR_PULSE_TRAIN_SEG *pSeg;

    if( m_pGrPdwIndex->uiCount == 0 )
        return;

    // 패턴으로 추출할 때 마진값은 PRI의 최대 최소값 차이로 한다.
    //-- 조철희 2006-02-22 13:23:58 --//
    margin = ( pExtRange->tMaxPRI - pExtRange->tMinPRI ) / 2;

    // 시작 PDW 인덱스
    ref_idx = 0;
    for( ;; ) {
        if( m_uiCoSeg >= m_uiMaxSeg )
            return;

        pSeg = & m_Seg[ m_uiCoSeg ];

        // 기준 펄스열 추출을 찾아서 존재하지 않으면 다음 밴드를 선택한다.
        if( TRUE == ExtractRefPT( pExtRange, _JITTER_RANDOM, pSeg, ref_idx, m_pGrPdwIndex, uiCoRef, flagMargin ) ) {
            ref_idx = pSeg->gr_ref_idx;

            // PRI 의 평균을 구한다.
            pSeg->stPRI.tMean = pSeg->stPRI.tMin + ( pSeg->stPRI.tMax - pSeg->stPRI.tMin ) / 2;

            ExtractBackPT( pSeg, _JITTER_RANDOM, m_pGrPdwIndex, margin );

            ExtractForPT( pSeg, _JITTER_RANDOM, m_pGrPdwIndex, margin );

            // 펄스열은 기준펄스열로 추출된 것 이상인것만 체크한다.
            // if( pSeg->pdw.count > (int) _sp.cm.Rpc )
            //-- 조철희 2005-12-07 14:45:52 --//
            {
                // 추출된 펄스열의 제원의 계산
                // 지터로 추출하지 못할 때는 해당 펄스열을 버린다.
                //-- 조철희 2005-12-19 15:18:29 --//
                if( TRUE == CalcSegParam( pSeg ) ) {
                    // 추출된 펄스 Marking
                    MarkToPDWIndex( pSeg, JITTER_MARK );

                    // 펄스열 증가
                    ++ m_uiCoSeg;
                }
            }

            ++ ref_idx;
        }
        else
            break;
    }
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt::ExtractDwellRefPT
// 반환되는 형  : void
// 함 수 인 자  : STR_PRI_RANGE_TABLE *pExtRange
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-12-22 09:21:38
//
BOOL CPulExt::ExtractDwellRefPT( STR_PULSE_TRAIN_SEG *pDwlSeg, STR_PRI_RANGE_TABLE *pExtRange )
{
    unsigned int i, ref_idx, count=0;

    UINT margin;

    BOOL bRet=FALSE;

    PDWINDEX *pPdwIndex;

    pPdwIndex = & m_pGrPdwIndex->pIndex[0];

    margin = UDIV( pExtRange->tMaxPRI - pExtRange->tMinPRI, 2 );

    ref_idx = 0;

    pDwlSeg->stPDW.uiCount = 0;

    pDwlSeg->uiMiss = 0;

    pDwlSeg->enPriType = _DWELL;

    pDwlSeg->first_idx = m_pGrPdwIndex->uiCount;
    pDwlSeg->last_idx = 0;

    pDwlSeg->stPRI.tMin = 0xffffffff;
    pDwlSeg->stPRI.tMax = 0;

    pDwlSeg->stPA.iMin = 0xffffff;
    pDwlSeg->stPA.iMax = 0;

    pDwlSeg->gr_ref_idx = 0xffff;

    pDwlSeg->enMark = NORMAL_SEG;

    // 추출되는 펄스열은 gSeg[]에 저장되며
    // 펄스열의 수는 gSeg_cnt에 의해 count 된다.
    // 펄스열의 추출은
    //			기준 펄스열 추출(extractRefPT()),
    //			후진 펄스열 추출(extractBackPT()),
    //			전진 펄스열 추출(extractForPT()),
    //			단순 펄스열 추출(extractSimpleJitterPT()),
    // 순으로 이루어지며 한번의 pass가 이루어지면 에미터가 하나 증가한다. gEmitter.count증가
    // 기준, 후진,전진 펄스열추출의 pass가 이루어지면 하나의 펄스열이 만들어지며
    // 펄스열의 수 gSeg_cnt가 증가 한다.
    // 하나의 에미터에는 동일한 PRI의 펄스열이 여러개 존재할수 있다.
    while( ref_idx < ( m_pGrPdwIndex->uiCount - _sp.cm.Rpc ) ) {
        if( TRUE == ExtractRefPT( pExtRange, _DWELL, & m_RefSeg, ref_idx, m_pGrPdwIndex, _sp.cm.Rpc ) ) {
            ExtractBackPT( & m_RefSeg, _DWELL, m_pGrPdwIndex, 0 );
            ExtractForPT( & m_RefSeg, _DWELL, m_pGrPdwIndex, 0 );

            //ref_idx = (int) m_RefSeg.gr_ref_idx + 1;
            ref_idx = m_RefSeg.gr_ref_idx;
            for( i=0 ; i < m_RefSeg.stPDW.uiCount ; ++i ) {
                if( pPdwIndex[ref_idx] < m_RefSeg.stPDW.pIndex[i] ) {
                    if( pPdwIndex[ref_idx] != m_RefSeg.stPDW.pIndex[i] ) {
                        if( i == 0 ) {
                            ++ ref_idx;
                        }
                        break;
                    }
                }
                ++ ref_idx;
            }

            // PDW 인덱스 복시
            MergePulseTrain( pDwlSeg, & m_RefSeg );
            //memcpy( & pDwlSeg->pdw.pIndex[count], m_RefSeg.pdw.pIndex, m_RefSeg.pdw.count * sizeof(PDWINDEX) );
            //count += m_RefSeg.pdw.count;

            pDwlSeg->gr_ref_idx = _min( pDwlSeg->gr_ref_idx, ref_idx );

            // PRT 최대 최소 값 저장
            pDwlSeg->stPRI.tMin = _min( pDwlSeg->stPRI.tMin, m_RefSeg.stPRI.tMin );
            pDwlSeg->stPRI.tMax = _max( pDwlSeg->stPRI.tMax, m_RefSeg.stPRI.tMax );

            // 펄스열의 최초시간 및 마지막 시간 설정
            pDwlSeg->last_idx = max( pDwlSeg->last_idx, m_RefSeg.last_idx );
            pDwlSeg->first_idx = min( pDwlSeg->first_idx, m_RefSeg.first_idx );
        }
        else {
            ++ ref_idx;
        }

    }

    pDwlSeg->stPRI.tMean = TDIV<_TOA>( ( pDwlSeg->stPRI.tMax + m_RefSeg.stPRI.tMin ), 2 );

    // 펄스열은 기준펄스열로 추출된 것 이상인것만 체크한다.
    if( pDwlSeg->stPDW.uiCount > (int) _sp.cm.Rpc ) {

        // 추출된 펄스열의 제원의 계산
        CalcSegParam( pDwlSeg );

        pDwlSeg->uiPRI_Band = (UINT) -1;

        /*! \bug  기준 펄스열로 추출했다는 것으 마킹한다.
                \date 2006-08-11 12:27:14, 조철희
        */
        pDwlSeg->uiExtractStep = _STABLE;

        // 추출된 펄스 Marking
        MarkToPDWIndex( pDwlSeg, STABLE_MARK );

        // 펄스열 증가
        //++ m_CoRefSeg;
        bRet = TRUE;
    }

    // 기준 펄스열로 추출한 펄스열에 대해서 Unmark 하게 한다.
    count=m_pGrPdwIndex->uiCount;
    PDWINDEX *pIndex=m_pGrPdwIndex->pIndex;
    for( i=0 ; i < count ; ++i ) {
        if( m_pMARK[ *pIndex ] == REFSTB_MARK )
            m_pMARK[ *pIndex ] = UnMark;
        ++ pIndex;
    }

    return bRet;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt::UnknownExtract
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-12 14:02:05
//
//##ModelId=428832A10027
void CPulExt::UnknownExtract()
{
    unsigned int i;
    int index;

    BOOL bIdx;

    PDWINDEX *pGrPdwIndex, *pSegPdwIndex;
    STR_PULSE_TRAIN_SEG *pSeg;

    //-- 조철희 2006-02-06 10:16:20 --//
    if( m_uiCoSeg >= m_uiMaxSeg )
        return;

    pSeg = & m_Seg[ m_uiCoSeg ];

    pSeg->enPriType = MAX_PRITYPE;

    bIdx = FALSE;
    pSegPdwIndex = & pSeg->stPDW.pIndex[0];
    pGrPdwIndex = & m_pGrPdwIndex->pIndex[0];
    pSeg->stPDW.uiCount = 0;
    for( i=0 ; i < m_pGrPdwIndex->uiCount ; ++i ) {
        index = *pGrPdwIndex++;

        // 추출된 펄스 제외
        if( m_pMARK[ index ] != UnMark )
            continue;

        // 아래의 idx 변수는 그룹화된 펄스열의 인덱스를 가리킨다.
        if( bIdx == FALSE ) {
            pSeg->gr_ref_idx = i;
            pSeg->first_idx = i;
            bIdx = TRUE;
        }

        *pSegPdwIndex++ = index;

        pSeg->last_idx = i;

        ++ pSeg->stPDW.uiCount;
    }

    // 펄스열은 기준펄스열로 추출된 것 이상인것만 체크한다.
    if( pSeg->stPDW.uiCount > (int) _sp.cm.Rpc ) {
        pSeg->fJitterRatio = CalcRefPRI( pSeg->stPDW.pIndex, pSeg->stPDW.uiCount, & pSeg->stPRI );

        // 추출된 펄스열의 제원의 계산
        CalcSegParam( pSeg );

        // 추출된 펄스 Marking
        MarkToPDWIndex( pSeg, UNKNOWN_MARK );

        ++ m_uiCoSeg;

        m_uiAnalSeg = m_uiCoSeg;
    }
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt::CalDtoaMargin
// 반환되는 형  : int
// 함 수 인 자  : int type
// 함 수 인 자  : STR_PULSE_TRAIN_SEG *pSeg
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-18 11:08:19
//
//##ModelId=428C213300D0
_TOA CPulExt::CalDtoaMargin( int type, STR_PULSE_TRAIN_SEG *pSeg )
{
    _TOA margin;

    // 추출관련 변수 설정
    if( type == _STABLE || type == _REFSTABLE || type == _DWELL ) {
        return STABLE_MARGIN;
    }
    else {
        // -- 조철희 2005-05-18 15:39:27 --//
        // 현재 방안
        //margin = pSeg->pri.max - pSeg->pri.min;
        //if( margin == 0 ) {
            // 탐지에서는 RPC로 추출한 펄스열의 평균 PRI를 근거로 추출한다.
            // 이전 방안
        //    margin = (UINT)( ( pSeg->pri.mean / 2. ) * pSeg->jitter_p );
        //}

        // 5개의 펄스열로 계산된 지터율을 이용하여 추후 펄스열을 추출하는데서
        // 펄스열 추출이 안될 수 있다.
        // 예를 들어서 8개의 스태거 레벨이었다고 할 때 5개의 추출된 지터율로써
        // 모든 펄스열을 제대로 추출하지 못할 수 있다.
        //-- 조철희 2005-11-16 15:55:55 --//

#if defined( _EXTRACT_PULSE_METHOD3_ )
        margin = (UINT)( ( pSeg->stPRI.tMean / 2. ) * ( MAX_JITTER_P / 100. ) );
#elif defined( _EXTRACT_PULSE_METHOD4_ )
        // 펄스간의 DTOA를 추출할 때 적용함
        //-- 조철희 2005-11-21 14:45:33 --//
        margin = UMUL( ( pSeg->stPRI.tMax - pSeg->stPRI.tMin ), 1.2 );
        margin = UMUL( pSeg->stPRI.tMean, 0.25 );
#elif defined( _EXTRACT_PULSE_METHOD5_ )
        /*! \bug  지터율을 이용한 마진과 DTOA의 최대/최소값을 이용한 마진 값 중에서 가장 큰 갑으로 정한다.
            \date 2006-08-11 11:51:43, 조철희
        */
        /*! \bug  m6.pdw 파일의 지터율 41% PRI 패턴 신호인 경우에 지터율을 +5% 더해서 추출하게 한다.
            \date 2006-08-23 15:32:00, 조철희
        */
        margin = (UINT)( ( pSeg->stPRI.tMean / 2. ) * ( (MAX_JITTER_P+10) / 100. ) );
        margin = _max( margin, UMUL( ( pSeg->stPRI.tMax - pSeg->stPRI.tMin ), 1.2 ) );

#else
        margin = (UINT)( ( pSeg->stPRI.tMean / 2. ) * ( ( MAX_JITTER_P + 5 ) / 100. ) );
#endif
        // margin 값은 최소 stable margin 보다 크게 정한다.
        margin = _max( margin, STABLE_MARGIN );
    }

    return margin;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt::RecalcDtoaMargin
// 반환되는 형  : void
// 함 수 인 자  : int ext_type
// 함 수 인 자  : STR_PULSE_TRAIN_SEG *pSeg
// 함 수 인 자  : UINT dtoa
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-30 17:26:18
//
//##ModelId=42A55D540120
_TOA CPulExt::RecalcDtoaMargin(int ext_type, STR_PULSE_TRAIN_SEG *pSeg, UINT dtoa)
{
    _TOA margin;

    if( ext_type == _STABLE || ext_type == _REFSTABLE ) {
        margin = CalDtoaMargin( ext_type, pSeg );
    }
    else {
        pSeg->stPRI.tMean = UDIV( pSeg->stPRI.tMean * pSeg->stPDW.uiCount + dtoa, pSeg->stPDW.uiCount + 1 );
        pSeg->stPRI.tMin = _min( (int) dtoa, pSeg->stPRI.tMin );
        pSeg->stPRI.tMax = _max( (int) dtoa, pSeg->stPRI.tMax );
        margin = CalDtoaMargin( ext_type, pSeg );
    }

    return margin;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt::CalMaxMiss
// 반환되는 형  : int
// 함 수 인 자  : int type
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-18 10:50:25
//
//##ModelId=428C21330080
UINT CPulExt::CalMaxMiss(int type)
{
    int iMaxOmittedPulses;

    // 추출관련 변수 설정
    if( type == _STABLE ) {
        /*! \bug  비교 개수가 3이상이어야 한다.
            \date 2008-01-24 19:27:57, 조철희
        */
        iMaxOmittedPulses = max( (UINT) 3, _sp.cm.Stb_Max_Miss );
    }

    else if( type == _REFSTABLE ) {
        /*! \bug  비교 개수가 3이상이어야 한다.
            \date 2008-01-24 19:27:57, 조철희
        */
        iMaxOmittedPulses = max( (UINT) 3, 2 * _sp.cm.Jit_Max_Miss );
    }
    else if( type == _DWELL ) {
        iMaxOmittedPulses = 1000;
    }

    else {
        // 탐지에서는 RPC로 추출한 펄스열의 평균 PRI를 근거로 추출한다.
        iMaxOmittedPulses = _sp.cm.Jit_Max_Miss;
    }

    return iMaxOmittedPulses;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : uiparamCompare
// 반환되는 형  : int
// 함 수 인 자  : const void *arg1
// 함 수 인 자  : const void *arg2
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-30 19:45:14
//
int uiparamCompare( const void *arg1, const void *arg2 )
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

int intparamCompare( const void *arg1, const void *arg2 )
{
    int *p1, *p2;

    p1 = (int *) arg1;
    p2 = (int *) arg2;

    if( *p1 > *p2 )
        return( 1 );
    else if( *p1 < *p2 )
        return( -1 );
    else
        return( 0 );
}

int lliparamCompare( const void *arg1, const void *arg2 )
{
    _TOA *p1, *p2;

    p1 = (_TOA *) arg1;
    p2 = (_TOA *) arg2;

    if( *p1 > *p2 )
        return( 1 );
    else if( *p1 < *p2 )
        return( -1 );
    else
        return( 0 );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt::VerifyPRI
// 반환되는 형  : void
// 함 수 인 자  : STR_PULSE_TRAIN_SEG *pSeg
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-18 17:00:37
//
//##ModelId=428C21330026
void CPulExt::VerifyPRI(STR_PULSE_TRAIN_SEG *pSeg)
{
    pSeg->stPRI.tMean = VerifyPRI( pSeg->stPDW.pIndex, pSeg->stPDW.uiCount );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt::VerifyPRI
// 반환되는 형  : int
// 함 수 인 자  : PDWINDEX *pPdwIndex
// 함 수 인 자  : int count
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-19 14:04:40
//
//##ModelId=428C21320382
_TOA CPulExt::VerifyPRI( PDWINDEX *pPdwIndex, unsigned int uiCount )
{
    unsigned int i;
    _TOA dtoa, preToa, toa;
    _TOA *pPdwParamIndex;

    if(uiCount == 1 ) {
        printf( "\n [W] 펄스 개수가 너무 부족해서 PRI 평균을 못 구합니다 !" );
        WhereIs;
        return 0;
    }

    // m_PdwParam 에 DTOA 값을 저장
    pPdwParamIndex = m_PdwParam.pTOAParam;
    preToa = m_pTOA[ *pPdwIndex++ ];
    for( i=1 ; i < uiCount; ++i ) {
        toa = m_pTOA[ *pPdwIndex++ ];
        dtoa = toa - preToa;
        preToa = toa;

        *pPdwParamIndex++ = dtoa;
    }
    m_PdwParam.uiCount = uiCount - 1;

    if( m_PdwParam.uiCount > 0 ) {
        // Qsort...
        qsort( m_PdwParam.pTOAParam, (size_t) m_PdwParam.uiCount, sizeof( _TOA ), lliparamCompare );
    }
    else {

    }

    /*! \bug  PRI 평균값은 DTOA 크기를 작은 순위로 정렬했을 때의 중간값 에서
                        1/3 지점으로 택했다.
                        jitter_2step.pdw 에서
                        지터평균을 구하게 되면 평균값은 최대값 근처로 가게 된다.
        \date 2006-07-19 13:59:02, 조철희
    */
    int median = m_PdwParam.uiCount / 2;
    return m_PdwParam.pTOAParam[ median ];
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 중간값으로 주파수 평균값을 구하고 노이즈를 고려해서 최대/최소 값을 구한다.
//!	\author  조철희
//!	\param	 pMinMax	인자형태 STR_TYPEMINMAX *
//!	\param	 pPdwIndex	인자형태 PDWINDEX *
//!	\param	 count	인자형태 int
//!	\return	 UINT
//! \version 1.37
//! \date		 2005-11-01 13:57:28
//! \warning
//
UINT CPulExt::MedianFreq( STR_TYPEMINMAX *pMinMax, PDWINDEX *pPdwIndex, unsigned int uiCount )
{
    unsigned int i;
    UINT *pPdwParamIndex;

    int unpass_count;
    int freq_min_median;
    int freq_max_median;

    if( uiCount == _spOne ) {
        printf( "\n [W] Invalid count !" );	WhereIs;
        return 0;
    }

    // m_PdwParam 에 DTOA 값을 저장
    pPdwParamIndex = m_PdwParam.puiParam;
    for( i=0 ; i < uiCount ; ++i ) {
        *pPdwParamIndex++ = m_pFREQ[ *pPdwIndex++ ];
    }

    m_PdwParam.uiCount = uiCount;

    // Qsort...
    qsort( m_PdwParam.puiParam, (size_t) m_PdwParam.uiCount, sizeof( UINT ), uiparamCompare );

  /*! \bug  주파수가 고정일 때는 주파수 노이즈를 감안해서 주파수 최대 최소값은 다시 계산한다.
      \date 2006-07-26 15:03:47, 조철희
  */
    if( pMinMax != NULL ) {
        unpass_count = UDIV( 0 /* count */ * 10, 200 );
        freq_min_median = unpass_count;
        freq_max_median = m_PdwParam.uiCount - unpass_count - 1;

        pMinMax->iMin = m_PdwParam.puiParam[ freq_min_median ];
        pMinMax->iMax = m_PdwParam.puiParam[ freq_max_median ];
    }

    int freq_median = m_PdwParam.uiCount / 2;
    return m_PdwParam.puiParam[ freq_median ];
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt::OverlappedSeg
// 반환되는 형  : BOOL
// 함 수 인 자  : STR_PULSE_TRAIN_SEG *pSeg1
// 함 수 인 자  : STR_PULSE_TRAIN_SEG *pSeg2
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-19 16:12:20
//
//##ModelId=429A5BDB008D
bool CPulExt::OverlappedSeg(STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2)
{
    UINT ratio;
    UINT nExpPulse;
    _TOA overlapToa;
    _TOA spantime1, spantime2;

    STR_PULSE_TRAIN_SEG *pRefSeg;

    overlapToa = CalOverlapSpace<_TOA>( pSeg1->tFirst, pSeg1->tLast, pSeg2->tFirst, pSeg2->tLast );
    spantime1 = pSeg1->tLast - pSeg1->tFirst;
    spantime2 = pSeg2->tLast - pSeg2->tFirst;
    if( spantime1 < spantime2 ) {
        pRefSeg = pSeg1;
    }
    else if( spantime1 > spantime2 ) {
        pRefSeg = pSeg2;
    }
    else {
        if( pSeg1->stPDW.uiCount > pSeg2->stPDW.uiCount ) {
            pRefSeg = pSeg1;
        }
        else {
            pRefSeg = pSeg2;
        }
    }

    nExpPulse = UDIV( overlapToa, pRefSeg->stPRI.tMean );
    ratio = UDIV( nExpPulse * 100, pRefSeg->stPDW.uiCount + pRefSeg->uiMiss - 1 );
    return ( ratio >= OVERLAP_SEG_THRESHOLD );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt::FindRefStable
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-30 17:55:42
//
//##ModelId=42A55D540102
void CPulExt::FindRefStable()
{
    unsigned int i;

    _TOA largest_pri;

    STR_PULSE_TRAIN_SEG *pSeg;
    STR_PRI_RANGE_TABLE ext_range;

    // 추출되는 펄스열은 gSeg[]에 저장되며
    // 펄스열의 수는 gSeg_cnt에 의해 count 된다.
    // 펄스열의 추출은
    //			기준 펄스열 추출(extractRefPT()),
    //			후진 펄스열 추출(extractBackPT()),
    //			전진 펄스열 추출(extractForPT()),
    //			단순 펄스열 추출(extractSimpleJitterPT()),
    // 순으로 이루어지며 한번의 pass가 이루어지면 에미터가 하나 증가한다. gEmitter.count증가
    // 기준, 후진,전진 펄스열추출의 pass가 이루어지면 하나의 펄스열이 만들어지며
    // 펄스열의 수 gSeg_cnt가 증가 한다.
    // 하나의 에미터에는 동일한 PRI의 펄스열이 여러개 존재할수 있다.

    /*! \bug  펄스 개수가 0개 이면 바로 리턴 처리한다.
        \date 2008-08-11 09:45:24, 조철희
    */
    if( m_pGrPdwIndex->uiCount > _spThree ) {
        largest_pri = ( m_pTOA[ m_pGrPdwIndex->pIndex[m_pGrPdwIndex->uiCount-1] ] - m_pTOA[ m_pGrPdwIndex->pIndex[0] ] ) / _sp.cm.Rpc;

        if( largest_pri > m_jit_pri_table[ MAX_PRI_RANGE-1 ].tMaxPRI ) {
            largest_pri = m_jit_pri_table[ MAX_PRI_RANGE-1 ].tMaxPRI;
        }

        // 펄스열 기본 추출
        for( i=m_uiStart_pri_level ; i <= m_uiEnd_pri_level ; ++i ) {
            // PRI 범위 구하기
            ext_range.tMinPRI = m_jit_pri_table[ i ].tMinPRI;
            ext_range.tMaxPRI = m_jit_pri_table[ i ].tMaxPRI;

            if( ext_range.tMaxPRI > largest_pri ) {
                ext_range.tMaxPRI = largest_pri;
            }

            FindRefStableSeg( & ext_range, i );
        }

        // 기준 펄스열로 추출한 펄스열에 대해서 Unmark 하게 한다.
        // 추출된 펄스 Marking
        pSeg = & m_Seg[ m_uiAnalSeg ];
        for( i=m_uiAnalSeg ; i < m_uiCoSeg ; ++i ) {
            if( pSeg->enPriType == _REFSTABLE ) {
                // 추출된 펄스 Marking해서 Jitter 펄스열 추출하지 못하도록 한다.
                MarkToPDWIndex( pSeg, UnMark );
            }

            ++ pSeg;
        }
    }
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    추출한 펄스열에 대해서 마킹하지 않고 규칙성 펄스열을 추출한다.
//! \author   조철희
//! \param    pExtRange 인자형태 STR_PRI_RANGE_TABLE *
//! \param    nPriBand 인자형태 int
//! \return   void
//! \version  1.37
//! \date     2005-11-04 13:25:22
//! \warning
//
void CPulExt::FindRefStableSeg( STR_PRI_RANGE_TABLE *pExtRange, int nPriBand )
{
    int ref_idx;
    int nStartSeg;

    bool bRet;

    PDWINDEX *pPdwIndex;

    pPdwIndex = & m_pGrPdwIndex->pIndex[0];

    nStartSeg = m_uiAnalSeg;
    //-- 조철희 2005-12-22 17:02:12 --//
    // nStartSeg = m_CoSeg;

    // 시작 PDW 인덱스
    ref_idx = 0;

    // 누락 펄스가 없을 때 고려한 펄스열 추출
    while( m_uiCoSeg < m_uiMaxSeg ) {
        // 기준 펄스열 추출을 찾아서 존재하지 않으면 다음 밴드를 선택한다.
        if( FALSE == ExtractRefPT( pExtRange, _REFSTABLE, & m_RefSeg, ref_idx, m_pGrPdwIndex, _sp.cm.Rpc ) ) {
            break;
        }

        /*! \bug  다음번째 PDW 인덱스를 선택할 때 +1 만큼한 것으로 하는 대신에 추출열을 보고 다음번째열을 설정한다.
            \date 2008-11-19 11:18:00, 조철희
        */
        // ref_idx = m_RefSeg.ref_idx + 1;
        ref_idx = m_RefSeg.gr_ref_idx;
        for( unsigned int i=0 ; i < m_RefSeg.stPDW.uiCount ; ++i ) {
            if( pPdwIndex[ref_idx] != m_RefSeg.stPDW.pIndex[i] ) {
                if( i == 0 ) {
                    ++ ref_idx;
                }
                break;
            }
            ++ ref_idx;
        }

        //-- 조철희 2005-11-01 17:33:32 --//
        // 기존에 추출된 펄스열과 하모닉 관계가 있을 수 있기 때문에 모든 대역에서 추출한 펄스열이 DTOA 관계를
        // 이용해서 제거한다.
        //-- 조철희 2005-12-28 09:58:17 --//
        //PrintSeg( -1, & m_RefSeg );
        bRet = FindStableSeg( & m_RefSeg, nStartSeg, m_uiCoSeg );    

        if( bRet == false ) {
            // 추출된 펄스 Marking
            MarkToPDWIndex( & m_RefSeg, REFSTB_MARK );

            m_RefSeg.uiPRI_Band = nPriBand;

            // 추가할 펄스열을 생성한다.
            m_RefSeg.enPriType = _REFSTABLE;

            MemcpySeg( & m_Seg[ m_uiCoSeg ], & m_RefSeg );

            // 펄스열 인덱스 증가
            ++ m_uiCoSeg;
        }
    }
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt::ExtractRefStable
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-30 17:56:06
//
//##ModelId=42A55D5400DA
void CPulExt::ExtractRefStable()
{
#ifdef _EXTRACL_ALL_STABLE_
    int i, j;

    int CoNewSeg, nSeg, start_seg;

    int ref_idx;

    STR_PULSE_TRAIN_SEG *pSeg, *pNewSeg;

    STR_PRI_RANGE_TABLE ext_range;

    CoNewSeg = m_uiCoSeg;
    pNewSeg = & m_Seg[ CoNewSeg ];

    nSeg = 0;

    // 펄스열 기본 추출
    for( i=m_uiCoSeg-1 ; i >= m_uiAnalSeg ; --i ) {
        pSeg = & m_Seg[ i ];

        // 하나의 STABLE PRI를 근거로 그룹화한 펄스중에서 모든 펄스열을 검색해본다.
        //-- 조철희 2005-11-18 14:52:23 --//
        if( pSeg->enPriType == _REFSTABLE ) {
            start_seg = CoNewSeg;

            ref_idx = pSeg->gr_ref_idx;

            // PRI 범위 구하기
            ext_range.tMinPRI = pSeg->stPRI.tMin;
            ext_range.tMaxPRI = pSeg->stPRI.tMax;

            while( CoNewSeg < m_uiMaxSeg ) {
                if( TRUE == ExtractRefPT( & ext_range, _STABLE, pNewSeg, ref_idx, m_pGrPdwIndex, _sp.cm.Rpc ) ) {
                    if( start_seg == CoNewSeg ) {
                        // 전방향 추출
                        ExtractBackPT( pNewSeg, _STABLE, m_pGrPdwIndex );
                    }

                    // 후방향 추출
                    ExtractForPT( pNewSeg, _STABLE, m_pGrPdwIndex );

                    // 펄스열은 기준펄스열로 추출된 것 이상인것만 체크한다.
                    if( pNewSeg->stPDW.uiCount > (int) _sp.cm.Rpc ) {
                        // 추출된 펄스 Marking
                        MarkToPDWIndex( pNewSeg, STABLE_MARK );

                        // 추출된 펄스열의 제원의 계산
                        CalcSegParam( pNewSeg );

                        // 펄스열의 PRI 평균값으로 모든 펄스들을 추출한다.
                        // 위에서 추출한 것이기 때문에 이 부분은 무시한다.
                        //-- 조철희 2005-12-21 11:42:42 --//
                        // ExtractSimpleStablePT( pNewSeg, _STABLE, m_pGrPdwIndex );

                        // 펄스열 추출 후에 PRI 타입을 재결정한다.
                        pNewSeg->enPriType = AnalPRIType( pNewSeg );

                        ++ CoNewSeg;
                        ++ pNewSeg;

                        ++ nSeg;
                    }

                    ref_idx = pNewSeg->gr_ref_idx + 1;
                }
                else
                    break;
            }

            // Unmark 한다.
            for( j=start_seg ; j < CoNewSeg ; ++j ) {
                MarkToPDWIndex( & m_Seg[ j ], UnMark );
            }
        }
    }

    //
    CopyPulseTrains( & m_Seg[m_uiAnalSeg], & m_Seg[m_uiCoSeg], nSeg );
    m_uiCoSeg = nSeg + m_uiAnalSeg;

#elif defined( _EXTRACT_PULSE_METHOD3_ )
    int i;

    int ref_idx;

    STR_PULSE_TRAIN_SEG *pSeg;

    STR_PRI_RANGE_TABLE ext_range;

    // 펄스열 기본 추출
    for( i=m_uiCoSeg-1 ; i >= m_uiAnalSeg ; --i ) {
        pSeg = & m_Seg[ i ];

        // 하나의 STABLE PRI를 근거로 그룹화한 펄스중에서 모든 펄스열을 검색해본다.
        //-- 조철희 2005-11-18 14:52:23 --//
        if( pSeg->enPriType == _REFSTABLE ) {
            ref_idx = pSeg->gr_ref_idx;

            // PRI 범위 구하기
            ext_range.tMinPRI = pSeg->stPRI.tMin;
            ext_range.tMaxPRI = pSeg->stPRI.tMax;

            if( TRUE == ExtractRefPT( & ext_range, _STABLE, pSeg, ref_idx, m_pGrPdwIndex, _sp.cm.Rpc ) ) {
                // 전방향 추출
                ExtractBackPT( pSeg, _STABLE, m_pGrPdwIndex );

                // 후방향 추출
                ExtractForPT( pSeg, _STABLE, m_pGrPdwIndex );

                // 추출된 펄스 Marking
                // MarkToPdwIndex( pSeg, STABLE_MARK );

                // 추출된 펄스열의 제원의 계산
                CalcSegParam( pSeg );

                // 펄스열의 PRI 평균값으로 모든 펄스들을 추출한다.
                // 위에서 추출한 것이기 때문에 이 부분은 무시한다.
                //-- 조철희 2005-12-21 11:42:42 --//
                // ExtractSimpleStablePT( pNewSeg, _STABLE, m_pGrPdwIndex );

                // 펄스열 추출 후에 PRI 타입을 재결정한다.
                pSeg->enPriType = AnalPRIType( pSeg );

                // 규칙성 펄스열이 아닌것은 제거 마킹한다.
                if( pSeg->enPriType != _STABLE )
                    pSeg->enMark = DELETE_SEG;

                ref_idx = pSeg->gr_ref_idx + 1;
            }
            else
                break;
        }
    }

    // 규칙성 펄스열을 추출하면서 기존에 펄스열 추출된것은 무시하지 않은 채로 추출하도록 한다.
    //-- 조철희 2005-12-26 15:35:47 --//
    for( i=m_uiAnalSeg ; i < m_uiCoSeg ; ++i ) {
        if( pSeg->enPriType == _STABLE && pSeg->enMark == NORMAL_SEG )
            MarkToPDWIndex( & m_Seg[ i ], STABLE_MARK );
    }

#elif defined( _EXTRACT_PULSE_METHOD4_ ) || defined( _EXTRACT_PULSE_METHOD5_ )
    unsigned int i;

    int ref_idx;

    STR_PULSE_TRAIN_SEG *pSeg;

    STR_PRI_RANGE_TABLE ext_range;

    // startSeg = m_nAnalSeg;

    // 펄스열 기본 추출
    //for( i=m_CoSeg-1 ; i >= m_nAnalSeg ; --i ) {
    //priMean = 0;
    pSeg = NULL;
    for( i=m_uiAnalSeg ; i < m_uiCoSeg ; ++i ) {
        pSeg = & m_Seg[ i ];

        // 하나의 STABLE PRI를 근거로 그룹화한 펄스중에서 모든 펄스열을 검색해본다.
        //-- 조철희 2005-11-18 14:52:23 --//
        if( pSeg->enPriType == _REFSTABLE ) {
            ref_idx = pSeg->gr_ref_idx;

            // PRI 범위 구하기
            ext_range.tMinPRI = pSeg->stPRI.tMin;
            ext_range.tMaxPRI = pSeg->stPRI.tMax;

            if( TRUE == ExtractRefPT( & ext_range, _REFSTABLE, pSeg, ref_idx, m_pGrPdwIndex, _sp.cm.Rpc ) ) {
                // 전방향 추출
                ExtractBackPT( pSeg, _REFSTABLE, m_pGrPdwIndex );

                // 후방향 추출
                ExtractForPT( pSeg, _REFSTABLE, m_pGrPdwIndex );

                // 추출된 펄스열의 제원의 계산
                CalcSegParam( pSeg );

                // 펄스열 추출 후에 PRI 타입을 재결정한다.
                pSeg->enPriType = AnalPRIType( pSeg );

                /*! \bug  기준 펄스열로 추출했다는 것으 마킹한다.
                    \date 2006-08-11 12:27:14, 조철희
                */
                pSeg->uiExtractStep = _REFSTABLE;

                /*! \bug  _spAnalMinPulseStableEmitter 대신에 _sp.cm.Rpc 로 하향 조정함.
                    \date 2006-08-17 12:16:55, 조철희
                */
                if( pSeg->stPDW.uiCount < (int) _sp.cm.Rpc /* _spAnalMinPulseStableEmitter */ )
                    pSeg->enMark = DELETE_SEG;
            }
            else
                break;
        }

        // 이전에 추출한 PRI값과 현재 추출한 PRI 값이 다르면 이전에 추출한 펄스열에 대한 MARK을 UnMark 시킨다.
        //-- 조철희 2006-02-13 08:58:44 --//

        //if( pSeg->pri.mean != (pSeg+1)->pri.mean )
        /*
        if( priMean != pSeg->pri.mean ) {
            // 규칙성 펄스열을 추출하면서 기존에 펄스열 추출된것은 무시하지 않은 채로 추출하도록 한다.
            //-- 조철희 2005-12-26 15:35:47 --//
            pSeg = & m_Seg[ startSeg ];
            for( j=startSeg ; j <= i ; ++j ) {
                if( pSeg->pri_type == _STABLE && pSeg->mark == NORMAL_SEG )
                    MarkToPdwIndex( & m_Seg[ i ], UnMark );
                ++ pSeg;

                ++ startSeg;
            }
        }			*/
    }

    // 규칙성 펄스열을 추출하면서 기존에 펄스열 추출된것은 무시하지 않은 채로 추출하도록 한다.
    //-- 조철희 2005-12-26 15:35:47 --//
    for( i=m_uiAnalSeg ; i < m_uiCoSeg ; ++i ) {
        if( pSeg->enPriType == _STABLE && pSeg->enMark == NORMAL_SEG ) {
            MarkToPDWIndex( & m_Seg[ i ], EXTRACT_MARK );
        }
    }

#endif
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : 기준 펄스열들 간의 유사성을 확인하여 유사하면 true, 아니면 false 로 한다. 
// 반환되는 형  : UINT
// 함 수 인 자  : STR_PULSE_TRAIN_SEG *pRefSeg
// 함 수 인 자  : int start
// 함 수 인 자  : int end
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-30 18:48:55
//
//##ModelId=42A55D5303D2
bool CPulExt::FindStableSeg(STR_PULSE_TRAIN_SEG *pRefSeg, int start, int end )
{
    int i;
    bool bRet=false;
    _TOA nHarmonic=0;

    STR_PULSE_TRAIN_SEG *pSeg;

    pSeg = & m_Seg[start];
    for( i=start ; i < end ; ++i, ++pSeg ) {
        // 하모닉 체크
        //-- 조철희 2006-01-04 14:52:32 --//
        bRet = CheckStablePT( & nHarmonic, pRefSeg, pSeg );

        if( bRet == true ) {
            break;
        }

    }

    return bRet;
}

/**
 * @brief     규칙성 펄스열을 추출한다.
 * @param     STR_PULSE_TRAIN_SEG * pSeg
 * @param     int ext_type
 * @param     STR_PDWINDEX * pColPdwIndex
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2005-05-30 19:41:39
 * @warning
 */
void CPulExt::ExtractSimpleStablePT(STR_PULSE_TRAIN_SEG *pSeg, int ext_type, STR_PDWINDEX *pColPdwIndex )
{
    unsigned int ref_idx;

    STR_PRI_RANGE_TABLE ext_range;

    // PRI 범위 구하기
    ext_range.tMinPRI = pSeg->stPRI.tMin;
    ext_range.tMaxPRI = pSeg->stPRI.tMax;

    // 펄스열의 마지막열부터 다시 추출한다.
    ref_idx = pSeg->last_idx + 1;

    while( ref_idx < pColPdwIndex->uiCount ) {
        // 기준 펄스열 추출을 찾아서 존재하지 않으면 다음 밴드를 선택한다.
        if( TRUE == ExtractRefPT( & ext_range, _STABLE, & m_RefSeg, ref_idx, pColPdwIndex, _sp.cm.Rpc ) ) {
            memcpy( & pSeg->stPDW.pIndex[pSeg->stPDW.uiCount], m_RefSeg.stPDW.pIndex, m_RefSeg.stPDW.uiCount * sizeof( PDWINDEX ) );
            pSeg->stPDW.uiCount += m_RefSeg.stPDW.uiCount;
            pSeg->last_idx = m_RefSeg.last_idx;

            // 기준 PRI로 추출한 상태이기 때문에 전방향만 펄스열을 추출한다.
            // 전방향 추출
            ExtractForPT( pSeg, _STABLE, pColPdwIndex );

            // 추출된 펄스열의 제원의 계산
            CalcSegParam( pSeg );

            //++ ref_idx;
            ref_idx = pSeg->last_idx + 1;
        }
        else {
            break;
            // ++ ref_idx;
        }
    }
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt::AnalPRIType
// 반환되는 형  : UINT
// 함 수 인 자  : STR_PULSE_TRAIN_SEG *pSeg
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-31 15:10:09
//
//##ModelId=42A55D530291
enPRI_TYPE CPulExt::AnalPRIType(STR_PULSE_TRAIN_SEG *pSeg, enPRI_TYPE ext_type )
{
    _TOA diff;
    enPRI_TYPE enRet;

    // 펄스열을 근거로 PRI 타입을 결정할 때 아래 루틴을 적용한다.
    if( ext_type == _UNKNOWN_PRI || ext_type == _REFSTABLE ) {
        diff = pSeg->stPRI.tMax - pSeg->stPRI.tMin;

        if( diff > 2*STABLE_MARGIN )
            enRet = _JITTER_RANDOM;
        else
            enRet = _STABLE;
    }
    //-- 조철희 2005-08-30 11:37:07 --//
    // 불규칙성 펄스열 추출할 때는 강제 JITTER 마킹을 한다.
    else {
        enRet = ext_type;
    }

	return enRet;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt::CleanRefSeg
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-31 15:57:48
//
//##ModelId=42A55D530273
void CPulExt::CleanRefSeg()
{
    unsigned int i, j;
    STR_PULSE_TRAIN_SEG *pSeg1, *pSeg2;

    pSeg1 = & m_Seg[m_uiAnalSeg];
    for( i=m_uiAnalSeg ; i < m_uiRefEndSeg ; ++i, ++pSeg1 ) {
        if( pSeg1->enMark == DELETE_SEG )
            continue;

        pSeg2 = & m_Seg[m_uiRefEndSeg];
        for( j=m_uiRefEndSeg ; j < m_uiCoSeg ; ++j, ++pSeg2 ) {
            _TOA nHarmonic;

            if( pSeg2->enMark == DELETE_SEG )
                continue;

            nHarmonic = CheckHarmonic( pSeg1, pSeg2 );
            if( pSeg1->enPriType == _STABLE && pSeg2->enPriType == _STABLE ) {
                if( nHarmonic != 0 && OverlappedSeg( pSeg1, pSeg2 ) == true ) {
                    // 규칙성 펄스열인 경우에는 긴 PRI를 삭제하게 한다.
                    // 버릴 SEG의 인덱스를 표시한다.
                    if( nHarmonic >= 2 && pSeg1->stPRI.tMean > pSeg2->stPRI.tMean ) {
                        pSeg1->enMark = DELETE_SEG;
                        break;
                    }
                    else
                        pSeg2->enMark = DELETE_SEG;
                }
            }
            else {
                if( nHarmonic != 0 && OverlappedSeg( pSeg1, pSeg2 ) == true ) {
                    // 버릴 SEG의 인덱스를 표시한다.
                    //-- 조철희 2005-10-31 11:42:57 --//
                    // nHarmonic 조건을 생략한다.
                    if( pSeg1->enPriType == _STABLE && pSeg2->enPriType == _JITTER_RANDOM ) {
                    //-- 조철희 2005-11-16 13:41:12 --//
                    //if( pSeg1->pri_type == _STABLE && pSeg2->pri_type == _JITTER ) {
                    //-- 조철희 2005-11-18 17:22:59 --//
                    // 예1) 1140, 1522 인 2단 스태거라고 하면 2개의 Stable 펄스열이 추출하고 Jitter열이 추출하게 된다.
                    // 이때 nHarmonic 값이 2 이상일 때 단지 PRI 값으로 제거할 펄스열을 선택하면 안 된다.
                    // 왜냐하면 Stable 로 추출한 펄스열이 다 제거 되기 때문이다.
                        if( nHarmonic == 1 )
                            pSeg2->enMark = DELETE_SEG;
                        else {
                            if( pSeg1->stPRI.tMean > pSeg2->stPRI.tMean ) {
                                pSeg1->enMark = DELETE_SEG;
                                break;
                            }
                            else
                                pSeg2->enMark = DELETE_SEG;
                        }
                    }

                    else {
                        pSeg1->enMark = DELETE_SEG;
                        break;
                    }
                }
            }
        }
    }
}

/**
 * @brief     두 펄스열 간의 하모닉 체크를 수행한다.
 * @param     STR_PULSE_TRAIN_SEG * pSeg1
 * @param     STR_PULSE_TRAIN_SEG * pSeg2
 * @return    _TOA
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2005-05-31 16:15:43
 * @warning
 */
_TOA CPulExt::CheckHarmonic(STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2)
{
    _TOA iHarmonic;

    if( ( pSeg1->enPriType == _STABLE || pSeg1->enPriType == _REFSTABLE ) &&
        ( pSeg2->enPriType == _STABLE || pSeg2->enPriType == _REFSTABLE ) ) {
        iHarmonic = CheckHarmonicTOA<_TOA>( pSeg1->stPRI.tMean, pSeg2->stPRI.tMean, 2*STABLE_MARGIN );
       
    }
    else {
        iHarmonic = CheckHarmonic( pSeg1->stPRI.tMean, pSeg1->fJitterRatio, pSeg2->stPRI.tMean, pSeg2->fJitterRatio );
    }
    /*
    else if( ( pSeg1->pri_type == _STABLE && pSeg2->pri_type == _JITTER ) ||
                     ( pSeg1->pri_type == _JITTER && pSeg2->pri_type == _STABLE ) ) {
        bRet = CheckHarmonic( pSeg1->pri.mean, pSeg2->pri.mean );
    }
    else if( ( pSeg1->pri_type == _JITTER || pSeg2->pri_type == _JITTER ) ) {
        jitter_margin1 = UMUL( pSeg1->pri.mean, pSeg1->jitter_p );
        jitter_margin2 = UMUL( pSeg2->pri.mean, pSeg2->jitter_p );
        halfdiff = _max( jitter_margin1, jitter_margin2 );

        harmonic = max_mean % min_mean;

        if( harmonic < halfdiff )
            bRet = TRUE;
        if( min_mean-harmonic < halfdiff )
            bRet = TRUE;
    }		*/

    return iHarmonic;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt::CheckHarmonic
// 반환되는 형  : UINT
// 함 수 인 자  : UINT mean1
// 함 수 인 자  : float jitter_p1
// 함 수 인 자  : UINT mean2
// 함 수 인 자  : float jitter_p2
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-09-08 11:21:44
//
_TOA CPulExt::CheckHarmonic(_TOA mean1, float jitter_p1, _TOA mean2, float jitter_p2)
{
    int halfdiff;
    int jitter_margin1, jitter_margin2;

    _TOA toaRet=0;
    _TOA harmonic;
    _TOA max_mean, min_mean;

    max_mean = mean1;
    min_mean = mean2;
    if( mean1 < mean2 ) {
        max_mean = mean2;
        min_mean = mean1;
    }

    jitter_margin1 = UMUL( mean1, jitter_p1 );
    jitter_margin2 = UMUL( mean2, jitter_p2 );
    halfdiff = _max( jitter_margin1, jitter_margin2 );

    harmonic = max_mean % min_mean;

    if( harmonic < halfdiff || min_mean-harmonic < halfdiff ) {
        toaRet = UDIV( max_mean, min_mean );
    }

    return toaRet;
}


//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt::AllExtSegMark
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-06-01 10:43:25
//
//##ModelId=42A55D5301AB
void CPulExt::AllExtSegMark()
{
    unsigned int i;
    STR_PULSE_TRAIN_SEG *pSeg;

    pSeg = & m_Seg[m_uiAnalSeg];
    for( i=m_uiAnalSeg ; i < m_uiCoSeg ; ++i, ++pSeg ) {
        if( pSeg->enMark == DELETE_SEG ) {
            continue;
        }

        MarkToPDWIndex( pSeg, EXTRACT_MARK );
    }
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt::ExtractFramePri
// 반환되는 형  : UINT
// 함 수 인 자  : STR_PDWINDEX *pSrcPdwIndex
// 함 수 인 자  : UINT framePri
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-06-09 19:20:59
//
UINT CPulExt::ExtractFramePri(STR_PDWINDEX *pSrcPdwIndex, _TOA framePri )
{
    int coExtPdw;
    unsigned int i, j, k;
    unsigned int uiCount;

    int miss, max_miss;
    int index1, index2, index3;
    int maxExtPdw;

    _TOA dtoa1, dtoa2;
    _TOA maxMissFramePri;

    PDWINDEX *pPdwIndex;

    uiCount = pSrcPdwIndex->uiCount;
    pPdwIndex = & pSrcPdwIndex->pIndex[0];

    // Frame PRI를 찾는 최대 누락 허용 개수
    max_miss = 20;
    maxMissFramePri = max_miss * framePri;

    maxExtPdw = 0;
    miss = 0;
    for( i=0 ; i < uiCount -3 ; ++i ) {
        index1 = pPdwIndex[i];

        for( j=i+1 ; j < uiCount -2 ; ++j ) {
            index2 = pPdwIndex[j];

            dtoa1 = m_pTOA[index2] - m_pTOA[index1];

            if( dtoa1 < framePri - STABLE_MARGIN ) {
                continue;
            }
            else if( dtoa1 <= framePri + STABLE_MARGIN ) {
                coExtPdw = 2;
                for( k=j+1 ; k < uiCount; ++k ) {
                    index3 = pPdwIndex[k];
                    dtoa2 = m_pTOA[index3] - m_pTOA[index2];

                    if( dtoa2 < framePri - STABLE_MARGIN ) {
                        continue;
                    }
                    else if( dtoa2 <= framePri + STABLE_MARGIN ) {
                        ++ coExtPdw;
                        index2 = index3;
                    }
                    else if( dtoa2 > maxMissFramePri ) {
                        break;
                    }
                    else {
                        if( 0 != CheckHarmonicTOA<_TOA>( framePri, dtoa2, (_TOA) 20 ) ) {
                            ++ coExtPdw;
                            miss += UDIV( dtoa2, framePri );
                        }
                    }
                }

                maxExtPdw = _max( maxExtPdw, coExtPdw );
            }
            else {
                break;
            }
        }
    }

    return maxExtPdw;
}

/**
 * @brief     스태거 단을 기준으로 Jitter 펄스열에서 스태거열을 추출한다.
 * @param     STR_PDWINDEX * pPdwIndex
 * @param     _TOA framePri
 * @param     STR_EMITTER * pEmitter
 * @return    unsigned int
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2005-06-09 19:11:50
 * @warning
 */
unsigned int CPulExt::ExtractStagger(STR_PDWINDEX *pPdwIndex, _TOA framePri, STR_EMITTER *pEmitter )
{
    bool bBreak=false;
    STR_PULSE_TRAIN_SEG *pSeg;
    STR_PRI_RANGE_TABLE ext_range;

    unsigned int uiCount;
    unsigned int uiRefidx;

    unsigned int coStaggerLevel=0, coSeg;

    memcpy( & m_pBKMK[0], & m_pMARK[0], sizeof( USHORT ) * m_uiMaxPdw );
    memset( & m_pMARK[0], 0, sizeof( USHORT ) * m_uiMaxPdw );

    // PRI 범위 구하기
    if( framePri >= STABLE_MARGIN ) {
        ext_range.tMinPRI = max( ITTOAusCNV( ( _TOA ) 2 ), framePri - STABLE_MARGIN );
    }
    else {
        ext_range.tMinPRI = ITTOAusCNV( ( _TOA ) 2 );
    }
    ext_range.tMaxPRI = max( ITTOAusCNV((_TOA)2), framePri + STABLE_MARGIN );

    // 펄스열 기본 추출
    // 누락 펄스가 없을 때 고려한 펄스열 추출
    coSeg = m_uiCoSeg;
    pEmitter->uiCoSeg = _spZero;
    uiRefidx = _spZero;
    uiCount = pPdwIndex->uiCount;
    while(uiRefidx < uiCount) {
        if( coSeg >= m_uiMaxSeg ) {
            Log( enError, "[W] 할당된 펄스열 개수(%d) 보다 많게 추출 되었음. !", m_uiMaxSeg );
            WhereIs;
            bBreak = true;

            break;
        }

        pSeg = & m_Seg[ coSeg ];

        // 기준 펄스열 추출을 찾아서 존재하지 않으면 다음 밴드를 선택한다.
        if( TRUE == ExtractRefPT( & ext_range, _STABLE, pSeg, uiRefidx, m_pGrPdwIndex, _spTwo ) ) {
            ExtractBackPT( pSeg, _STABLE, m_pGrPdwIndex);

            ExtractForPT( pSeg, _STABLE, m_pGrPdwIndex);

            /*! \bug  펄스개수가 특정 최소 개수보다 커야 펄스열을 마킹하는 것으로 한다.
                \date 2006-07-24 12:30:40, 조철희
            */
            /*! \bug  항해 레이더 같은 경우 펄스 2개밖에 추출되 않음. 그래서 무시하게 함.
                \date 2006-08-23 16:20:05, 조철희
            */
            CalcSegParam( pSeg );

            // 추출된 펄스 Marking
            MarkToPDWIndex( pSeg, STABLE_MARK );

            pEmitter->uiSegIdx[ pEmitter->uiCoSeg++ ] = coSeg++;

            uiRefidx = uiRefidx + 1;
        }
        else {
            // 펄스열이 존재하지 않기 때문에 빠져 나온다.
            break;
        }
    }

    // 이전에 마킹된 것으로 돌린다.
    memcpy( & m_pMARK[0], & m_pBKMK[0], sizeof( USHORT ) * m_uiMaxPdw );

    if( bBreak == false ) {
        // 추출한 규칙성 펄스열의 첫번째 TOA와 FramePRI 값을 근거로 유사 펄스열을 제거한다.
        coStaggerLevel = CheckStaggerLevel( framePri, pEmitter );
    }

    return coStaggerLevel;
}

/**
 * @brief     스태거 레벨로 펄스열을 추출한다.
 * @param     _TOA framePri
 * @param     STR_EMITTER * pEmitter
 * @return    UINT
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2005-10-10 14:23:59
 * @warning
 */
UINT CPulExt::CheckStaggerLevel( _TOA framePri, STR_EMITTER *pEmitter )
{
    unsigned int i, j;
    unsigned int uiCount;

    _TOA tDTOA;
    _TOA tFirst;

    UINT *pSegIdx;
    STR_PULSE_TRAIN_SEG *pSeg;

    STR_MINMAX_TOA level_pri;

	unsigned int uiCoStaggerLevel;

    // 시작 TOA를 구한다.
    int min_pdw_index=m_uiMaxPdw;

    uiCount = pEmitter->uiCoSeg;

	if (uiCount < MAX_FREQ_PRI_STEP) {
		for (i = 0; i < uiCount; ++i) {
			pSeg = &m_Seg[pEmitter->uiSegIdx[i]];
			if (min_pdw_index > *pSeg->stPDW.pIndex) {
				min_pdw_index = *pSeg->stPDW.pIndex;
			}
		}
		tFirst = m_pTOA[min_pdw_index];

		// 추출 펄스열의 TOA를 시작 TOA로 정렬화하고 FramePRI 값으로 모듈화한다.
		pSegIdx = &pEmitter->uiSegIdx[0];
		for (i = 0; i < uiCount; ++i) {
			pSeg = &m_Seg[*pSegIdx++];
			pEmitter->tStaggerDwellLevel[i] = (m_pTOA[*pSeg->stPDW.pIndex] - tFirst) % framePri;
		}

		//////////////////////////////////////////////////////////////////////////
		// 펄스열의 정렬화된 TOA를 근거로 유사 TOA는 표시하고 펄스열을 카운팅한다.
		_TOA *pSegToa1, *pSegToa2;

		pSegToa1 = &pEmitter->tStaggerDwellLevel[0];
		uiCoStaggerLevel = 1;
		for (i = 0; i < uiCount; ++i) {
			pSegToa2 = &pEmitter->tStaggerDwellLevel[i];
			for (j = i + 1; j < uiCount; ++j) {
				++pSegToa2;
				pSeg = &m_Seg[pEmitter->uiSegIdx[j]];

				if (pSeg->enMark == CHECKED_SEG) {
					continue;
				}

				if (TRUE == CompMeanDiff<_TOA>(*pSegToa1, *pSegToa2, 5 * STABLE_MARGIN)) {
					pSeg->enMark = CHECKED_SEG;
				}
			}

			++pSegToa1;
		}

		uiCoStaggerLevel = _spZero;
		pSeg = &m_Seg[m_uiCoSeg];
		for (i = 0; i < uiCount; ++i) {
			if (pSeg->enMark != CHECKED_SEG) {
				++uiCoStaggerLevel;
			}
			++pSeg;
		}

		// 스태거 레벨을 체크해서 모든 단이 일정하면 스태거 분석 실패로 한다.
		//-- 조철희 2005-11-03 17:40:34 --//
		level_pri.tMin = INT64_MAX;
		level_pri.tMax = 0;
		pEmitter->tStaggerDwellLevel[uiCount] = framePri;
		for (i = 0; i < uiCount; ++i) {
			tDTOA = pEmitter->tStaggerDwellLevel[i + 1] - pEmitter->tStaggerDwellLevel[i];
			level_pri.tMin = min(level_pri.tMin, tDTOA);
			level_pri.tMax = max(level_pri.tMax, tDTOA);
		}

		/*! \bug  스태거 레벨 값 중에서 제일 작은 값과 제일 큰 값을 찾아서
							그 차이가 1.5 us 이내이면 지터로 보고한다.
			\date 2006-05-19 14:47:56, 조철희
		*/
		if (uiCoStaggerLevel <= 1 || CompMeanDiff<_TOA>(level_pri.tMax, level_pri.tMin, UMUL(1.5, _spOneMicrosec)) == TRUE) {
			uiCoStaggerLevel = _spZero;
		}

		/*
			refToa = ( TOA[ *m_Seg[ m_CoSeg+coStaggerSeg ].pdw.pIndex ] - TOA[ *m_pGrPdwIndex->pIndex ] ) % framePri;

			for( i=0 ; i < coStaggerSeg ; ++i ) {
				pSeg = & m_Seg[ m_CoSeg+i ];

				if( TRUE == CompMeanDiff( refToa, pSeg->first_toa, STABLE_MARGIN ) ) {
					PDWINDEX *pTmp;

					pTmp = pSeg->pdw.pIndex;
					memcpy( pSeg, & m_Seg[ m_CoSeg+coStaggerSeg ], sizeof( STR_PULSE_TRAIN_SEG ) );
					m_Seg[ m_CoSeg+coStaggerSeg ].pdw.pIndex = pTmp;

					return FALSE;
				}
			}	*/

			// m_Seg[ m_CoSeg+i ].first_toa = refToa;
	}
	else {
		uiCoStaggerLevel = 0;
	}

    return uiCoStaggerLevel;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt::VerifyPW
// 반환되는 형  : int
// 함 수 인 자  : PDWINDEX *pPdwIndex
// 함 수 인 자  : int count
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-20 11:03:01
//
//##ModelId=429A5BDB0000
int CPulExt::VerifyPW(PDWINDEX *pPdwIndex, unsigned int uiCount)
{
    unsigned int i;
    int iRet;
    UINT *pPdwParamIndex;

    if (uiCount == 1) {
        iRet = m_pPW[*pPdwIndex];
    }
    else {
        // m_PdwParam 에 DTOA 값을 저장
        pPdwParamIndex = m_PdwParam.puiParam;
        for (i = 0; i < uiCount; ++i)
            *pPdwParamIndex++ = m_pPW[*pPdwIndex++];

        m_PdwParam.uiCount = uiCount;

        // Qsort...
        qsort(m_PdwParam.puiParam, (size_t)m_PdwParam.uiCount, sizeof(UINT), uiparamCompare);

        int median = m_PdwParam.uiCount / 2;
        iRet = m_PdwParam.puiParam[median];
    }

    return iRet;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt::CalcPAMean
// 반환되는 형  : int
// 함 수 인 자  : PDWINDEX *pPdwIndex
// 함 수 인 자  : int count
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-05-20 22:46:07
//
//##ModelId=42E85F37005E
int CPulExt::CalcPAMean(PDWINDEX *pPdwIndex, unsigned int uiCount)
{
    /*! \debug  아래 루프에서 ( m_PdwParam.uiCount - PA_MEAN_ITEM ) 값이 음의 값이 나올 수 있기 때문에 이 값은  반드시 int 해야함.
    	\author 조철희 (churlhee.jo@lignex1.com)
    	\date 	2022-04-25 11:56:53
    */
    int i;      
    int *pPdwParamIndex;

    int iRet;

    if(uiCount == _spOne ) {
        iRet = m_pPA[ *pPdwIndex ];
    }
    else {
        // m_PdwParam 에 DTOA 값을 저장
        pPdwParamIndex = m_PdwParam.piParam;
        for (i = 0; i < (int) uiCount; ++i) {
            *pPdwParamIndex++ = m_pPA[*pPdwIndex++];
        }
        
        m_PdwParam.uiCount = uiCount;

        // Qsort...
        qsort(m_PdwParam.piParam, (size_t)m_PdwParam.uiCount, sizeof(int), intparamCompare);

        int paMean = 0;
        int item = 0;
        for (i = m_PdwParam.uiCount - 1; i >= 0 && i >= (int)( m_PdwParam.uiCount - PA_MEAN_ITEM ); --i) {
            paMean += m_PdwParam.piParam[i];
            ++item;
        }

        iRet = IDIV(paMean, item);
    }

    return iRet;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt::CopyOnePulseTrain
// 반환되는 형  : void
// 함 수 인 자  : STR_PULSE_TRAIN_SEG *pDstSeg
// 함 수 인 자  : STR_PULSE_TRAIN_SEG *pSrcSeg
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-11-18 16:13:50
//
void CPulExt::CopyOnePulseTrain( STR_PULSE_TRAIN_SEG *pDstSeg, STR_PULSE_TRAIN_SEG *pSrcSeg )
{
  PDWINDEX *pBackupIndex;

    // 펄스열 구조의 내부 변수 복사
    pBackupIndex = pDstSeg->stPDW.pIndex;
    memcpy( pDstSeg, pSrcSeg, sizeof( STR_PULSE_TRAIN_SEG ) );
    pDstSeg->stPDW.pIndex = pBackupIndex;

    // 펄스열 구조의 포인터 값 복사
    memcpy( pDstSeg->stPDW.pIndex, pSrcSeg->stPDW.pIndex, pSrcSeg->stPDW.uiCount * sizeof( PDWINDEX ) );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt::CopyPulseTrains
// 반환되는 형  : void
// 함 수 인 자  : STR_PULSE_TRAIN_SEG *pDstSeg
// 함 수 인 자  : STR_PULSE_TRAIN_SEG *pSrcSeg
// 함 수 인 자  : int coSeg
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-11-18 16:19:10
//
void CPulExt::CopyPulseTrains( STR_PULSE_TRAIN_SEG *pDstSeg, STR_PULSE_TRAIN_SEG *pSrcSeg, int coSeg )
{
    int i;

    for( i=0 ; i < coSeg ; ++i ) {
        CopyOnePulseTrain( & pDstSeg[i], & pSrcSeg[i] );
    }
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt::DeleteAllSeg
// 반환되는 형  : void
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-12-22 13:13:22
//
void CPulExt::DeleteAllSeg( STR_EMITTER *pEmitter )
{
    int i;
    UINT *pSegIdx;

    qsort( pEmitter->uiSegIdx, (size_t) pEmitter->uiCoSeg, sizeof( int ),  intparamCompare );

    pSegIdx = & pEmitter->uiSegIdx[ pEmitter->uiCoSeg-1 ];
    for( i=pEmitter->uiCoSeg ; i > 0 ; --i ) {
        -- m_uiCoSeg;
        CopyPulseTrains( & m_Seg[*pSegIdx], & m_Seg[(*pSegIdx)+1], m_uiCoSeg-(*pSegIdx) );
        -- pSegIdx;

        //PrintAllSeg();
    }

// 	pSegIdx = & pEmitter->seg_idx[ pEmitter->seg_count-1 ];
// 	for( i=pEmitter->seg_count ; i > 0 ; --i ) {
// 		-- m_CoSeg;
// 		CopyPulseTrains( m_Seg+(*pSegIdx), m_Seg+(*pSegIdx)+1, m_CoSeg-(*pSegIdx) );
// 		-- pSegIdx;
//
// 		PrintAllSeg();
// 	}

    m_uiAnalSeg = m_uiCoSeg;
}

/**
 * @brief     PRI 간격을 체크해서 같은 펄스열인지 검증한다.
 * @param     STR_PULSE_TRAIN_SEG * pSeg1
 * @param     STR_PULSE_TRAIN_SEG * pSeg2
 * @return    BOOL
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2006-01-06 16:27:20
 * @warning
 */
BOOL CPulExt::CheckPriInterval( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 )
{
    BOOL bRet = FALSE;
    _TOA dTOA;

    if( pSeg1->first_idx < pSeg2->first_idx )
        dTOA = pSeg2->tFirst - pSeg1->tFirst;
    else
        dTOA = pSeg1->tFirst - pSeg2->tFirst;

    dTOA = dTOA % pSeg1->stPRI.tMean;

    /*! \bug  오차를 고려해서 STABLE_MARGIN에 1.2배를 한 값으로 한다.
        \date 2006-08-08 09:11:54, 조철희
    */
    if( CompMeanDiff<_TOA>( dTOA, 0, UMUL( 2, STABLE_MARGIN ) ) == TRUE ||
        CompMeanDiff<_TOA>( dTOA, pSeg1->stPRI.tMean, UMUL( 2, STABLE_MARGIN ) ) == TRUE ||
        CompMeanDiff<_TOA>( dTOA, pSeg2->stPRI.tMean, UMUL( 2, STABLE_MARGIN ) ) == TRUE ) {
        bRet = TRUE;
    }

    return bRet;
}

/**
 * @brief     2두 펄스열 간의 누락된 펄스열 을 검증한다.
 * @param     STR_PULSE_TRAIN_SEG * pSeg1
 * @param     STR_PULSE_TRAIN_SEG * pSeg2
 * @return    BOOL
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-01-10, 18:10
 * @warning
 */
bool CPulExt::CheckOmittedPulse( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 )
{
    bool bRet=true;

    _TOA dtoa;
	int iMaxMiss;

    if( CalOverlapSpace<PDWINDEX>( pSeg1->first_idx, pSeg1->last_idx, pSeg2->first_idx, pSeg2->last_idx ) != 0 ) {
        bRet = false;
    }
	else {
		_TOA r;
		iMaxMiss = CalMaxMiss( pSeg1->enPriType );

		if( pSeg1->last_idx < pSeg2->first_idx ) {
			dtoa = pSeg2->tFirst - pSeg1->tLast;
		}
		else {			
			dtoa = pSeg1->tFirst - pSeg2->tLast;       
		}

		r = MulDiv64( 1, dtoa, pSeg1->stPRI.tMean );
		if( r > (_TOA) iMaxMiss ) {
			bRet = false;
		}
		

	}

    return bRet;
}

/**
 * @brief     2개의 펄시열의 유사성을 확인하여 유사성이 있으면 TRUE, 아니면 FALSE 를 리턴한다.
 * @param     _TOA * pnHarmonic
 * @param     STR_PULSE_TRAIN_SEG * pRefSeg
 * @param     STR_PULSE_TRAIN_SEG * pCmpSeg
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-01-10, 15:23
 * @warning
 */
bool CPulExt::CheckStablePT( _TOA *pnHarmonic, STR_PULSE_TRAIN_SEG *pRefSeg, STR_PULSE_TRAIN_SEG *pCmpSeg )
{
    bool bRet;

    *pnHarmonic = CheckHarmonic( pRefSeg, pCmpSeg );

    if( CalOverlapSpace<PDWINDEX>( pRefSeg->first_idx, pRefSeg->last_idx, pCmpSeg->first_idx, pCmpSeg->last_idx ) != 0 ) {
        bRet = FALSE;
    }
    else {
        bRet = IsSamePulseTrain( pRefSeg, pCmpSeg );

        if( bRet == TRUE ) {
            bRet = CheckOmittedPulse( pRefSeg, pCmpSeg );
        }
    }

    return bRet;

}

/**
 * @brief     두 펄스열이 서로 연속 관계인지를 체크한다.
 * @param     STR_PULSE_TRAIN_SEG * pSeg1
 * @param     STR_PULSE_TRAIN_SEG * pSeg2
 * @return    BOOL
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-06-14, 16:45
 * @warning
 */
bool CPulExt::IsSamePulseTrain( STR_PULSE_TRAIN_SEG *pSeg1, STR_PULSE_TRAIN_SEG *pSeg2 )
{
    bool bRet;

    if( pSeg1->last_idx < pSeg2->first_idx ) {
        bRet = IsSamePulse<_TOA>( pSeg1->tLast, pSeg2->tFirst, pSeg1->stPRI.tMean, 2*STABLE_MARGIN ) == TRUE;
    }
    else {
        bRet = IsSamePulse<_TOA>( pSeg2->tLast, pSeg1->tFirst, pSeg2->stPRI.tMean, 2*STABLE_MARGIN ) == TRUE;
    }

    return bRet;

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt::GetCoExtPulse
// 반환되는 형  : int
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-02-15 14:07:46
//
int CPulExt::GetCoExtPulse()
{
    unsigned int i;
    unsigned int count=0;

    STR_PULSE_TRAIN_SEG *pSeg;

    pSeg = & m_Seg[0];
    for( i=0 ; i < m_uiCoSeg ; ++i ) {
        if (pSeg->enMark == NORMAL_SEG) {
            count += pSeg->stPDW.uiCount;
        }
    }
    return count;
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CPulExt::MergeJitterPulseTrain
//! \author   조철희
//! \param    startSeg 인자형태 int
//! \param    endSeg 인자형태 int
//! \return   void
//! \version  1.37
//! \date     2006-08-23 10:56:05
//! \warning
//
void CPulExt::MergeJitterPulseTrain( int startSeg, int endSeg, BOOL bIgnoreJitterP )
{
    int i;
    _TOA nHarmonic;
    int iCount, merged_index[MAX_SEG];

    STR_PULSE_TRAIN_SEG *pMainSeg, *pSeg;

	//PrintAllSeg();

    pMainSeg = GetMainSeg( startSeg, endSeg );
    while( NULL != pMainSeg ) {
        pMainSeg->enMark = MERGED_SEG;

        pSeg = & m_Seg[ startSeg ];
        iCount = 0;
        for( i=startSeg ; i < endSeg ; ++i, ++pSeg ) {
            if( pSeg->enMark == DELETE_SEG || pSeg->enMark == MERGED_SEG ) {
                continue;
            }

            if( pMainSeg->uiFreqType != pSeg->uiFreqType ) {
                continue;
            }

            /*! \bug  주파수 고정일때 주파수 값을 범위를 확인해서 펄스열을 병합하게 함.
                \date 2006-09-11 10:33:10, 조철희
            */
            if( pMainSeg->uiFreqType == _FIXED ) {
                if( FALSE == CompMarginDiff( pMainSeg->freq.iMean, pSeg->freq.iMin, pSeg->freq.iMax, 0 ) ) {
                    continue;
                }
                if( FALSE == CompMarginDiff( pSeg->freq.iMean, pMainSeg->freq.iMin, pMainSeg->freq.iMax, 0 ) ) {
                    continue;
                }
            }

            if( pMainSeg == pSeg ) {
                continue;
            }

            nHarmonic = CheckHarmonic( pMainSeg, pSeg );
            if( ( ( nHarmonic != 0 && OverlappedSeg( pMainSeg, pSeg ) == false && CheckOmittedPulse( pMainSeg, pSeg ) == TRUE ) ) || bIgnoreJitterP == TRUE ) {
                pSeg->enMark = MERGED_SEG;
                merged_index[iCount++ ] = i;
            }
        }

        // 펄스열을 병합한다.
        for( i=0 ; i < iCount; ++i ) {
            pSeg = & m_Seg[ merged_index[ i ] ];
            MergePulseTrain( pMainSeg, pSeg );
        }
        CalcSegParam( pMainSeg );

        pMainSeg = GetMainSeg( startSeg, endSeg );
    }

    // MERED_SEG 마킹 펄스열들을 NORMAL 펄스열로 바꾼다.
    ChangeMarkTo( startSeg, endSeg, MERGED_SEG, NORMAL_SEG );

    CleanPulseTrains( startSeg, endSeg );
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CPulExt::ChangeMarkTo
//! \author   조철희
//! \param    startSeg 인자형태 int
//! \param    endSeg 인자형태 int
//! \param    from_mark 인자형태 UINT
//! \param    to_mark 인자형태 UINT
//! \return   void
//! \version  1.37
//! \date     2006-08-23 14:08:34
//! \warning
//
void CPulExt::ChangeMarkTo( int startSeg, int endSeg, UINT from_mark, SEG_MARK to_mark )
{
    int i;

    STR_PULSE_TRAIN_SEG *pSeg;

    pSeg = & m_Seg[ startSeg ];
    for( i=startSeg ; i < endSeg ; ++i, ++pSeg ) {
        if( pSeg->enMark == from_mark ) {
            pSeg->enMark = to_mark;
        }
    }
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CPulExt::MergePulseTrain
//! \author   조철희
//! \param    pMrgSeg 인자형태 STR_PULSE_TRAIN_SEG *
//! \param    pSrcSeg 인자형태 STR_PULSE_TRAIN_SEG *
//! \return   void
//! \version  1.37
//! \date     2006-08-23 11:47:37
//! \warning
//
void CPulExt::MergePulseTrain( STR_PULSE_TRAIN_SEG *pMrgSeg, STR_PULSE_TRAIN_SEG *pSrcSeg )
{
    unsigned int i;
    int mrg_count;

    int *pParam;

    PDWINDEX *pPdwIndex;

    // PDW 인덱스 초기화
    memset( m_PdwParam.piParam, 0, sizeof( int ) * m_uiMaxPdw );

    // 기준 펄스열 인덱스 설정
    pParam = m_PdwParam.piParam;
    pPdwIndex = pMrgSeg->stPDW.pIndex;
    for( i=0 ; i < pMrgSeg->stPDW.uiCount ; ++i ) {
        pParam[ *pPdwIndex ] = 1;
        pPdwIndex ++;
    }

    // 병합시킬 펄스열 인덱스 설정
    pParam = m_PdwParam.piParam;
    m_PdwParam.uiCount = pSrcSeg->stPDW.uiCount;
    pPdwIndex = pSrcSeg->stPDW.pIndex;
    for( i=0 ; i < pSrcSeg->stPDW.uiCount ; ++i ) {
        pParam[ *pPdwIndex ] = 1;
        pPdwIndex++;
    }

    // m_PdwParam.count = _max( pMrgSeg->last_idx, pSrcSeg->last_idx );
    pParam = m_PdwParam.piParam;
    pPdwIndex = pMrgSeg->stPDW.pIndex;
    /*! \bug  비교 대상 개수는 최대 256개로 한다.
        \date 2008-01-16 18:04:36, 조철희
    */
    mrg_count = 0;
    for( i=0 ; i < m_uiMaxPdw ; ++i ) {
        if( *pParam++ == 1 ) {
            *pPdwIndex++ = i;
            ++ mrg_count;
        }
    }
    pMrgSeg->stPDW.uiCount = mrg_count;

    // 병합한 펄스열 정보 업데이트.
    pMrgSeg->uiMiss += pSrcSeg->uiMiss;
    pMrgSeg->last_idx = max( pMrgSeg->last_idx, pSrcSeg->last_idx );
    pMrgSeg->first_idx = min( pMrgSeg->first_idx, pSrcSeg->first_idx );

    pSrcSeg->enMark = DELETE_SEG;
}

//////////////////////////////////////////////////////////////////////
//
//! \brief    추출한 펄스열 중에서 메인 펄스열을 한개 선택한다.
//! \author   조철희
//! \param    startSeg 인자형태 int
//! \param    endSeg 인자형태 int
//! \return   STR_PULSE_TRAIN_SEG
//! \version  1.37
//! \date     2006-08-23 11:21:09
//! \warning
//
STR_PULSE_TRAIN_SEG *CPulExt::GetMainSeg( int startSeg, int endSeg )
{
    int i;
    BOOL bMainSeg;

    STR_PULSE_TRAIN_SEG *pSeg, *pMainSeg;

    if( startSeg >= endSeg-1 )
        return NULL;

    bMainSeg = FALSE;

    pMainSeg = NULL;
    pSeg = & m_Seg[ startSeg ];
    for( i=startSeg ; i < endSeg ; ++i, ++pSeg ) {
        if( pSeg->enMark == DELETE_SEG )
            continue;

        if( pSeg->enMark == MERGED_SEG )
            continue;

        if( bMainSeg == FALSE ) {
            bMainSeg = TRUE;
            pMainSeg = pSeg;
            continue;
        }

        // 펄스열 선택은 펄스개수가 가장 많은 펄스열로 선택한다.
        if( pMainSeg->stPDW.uiCount < pSeg->stPDW.uiCount )
            pMainSeg = pSeg;
    }
    return pMainSeg;
}

/**
 * @brief     펄스열 추출 정보를 프린트한다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2006-08-24 15:04:21
 * @warning
 */
void CPulExt::PrintAllSeg()
{
#ifdef _MSC_VER
    unsigned int i, uiCoSeg;
    STR_PULSE_TRAIN_SEG *pSeg;

    //////////////////////////////////////////////////////////////////////////
    // 펄스열 프린트
    if( m_uiCoSeg == m_uiAnalSeg ) {
        //printf( "\n\n No Pulse Train !" );
        Log( enNormal, "No Pulse Train !" );
    }
    else {
        //printf( "\n\n 펄스열 추출 개수 : %d" , m_CoSeg-m_nAnalSeg );
        Log( enDebug, "펄스열 : 총 %d(개)" , m_uiCoSeg-m_uiAnalSeg );

        if(m_uiRefStartSeg != INT32_MAX ) {
            uiCoSeg = m_uiRefStartSeg - m_uiAnalSeg;
            Log( enDebug, "규칙성 펄스열 : %d(개)", uiCoSeg );
            pSeg = &m_Seg[m_uiAnalSeg];
            for( i = 0 ; i < uiCoSeg ; ++i, ++pSeg ) {
                PrintSeg( i+ m_uiRefStartSeg, pSeg );
                PrintAllSegPDW( pSeg );
            }

            uiCoSeg = m_uiCoSeg - m_uiRefStartSeg;
            Log( enDebug, "불규칙성 펄스열 : %d(개)", uiCoSeg );
            pSeg = &m_Seg[m_uiRefStartSeg];
            for( ; i < uiCoSeg ; ++i, ++pSeg ) {
                PrintSeg( i+ m_uiRefStartSeg, pSeg );
                PrintAllSegPDW( pSeg );
            }
        }
        else {
            pSeg = &m_Seg[0];
            for( i = 0 ; i < m_uiCoSeg ; ++i, ++pSeg ) {
                PrintSeg( i, pSeg );
                PrintAllSegPDW( pSeg );
            }
        }

    }
    printf( "\n" );
#endif

}

/**
 * @brief     펄스열 정보를 출력한다.
 * @param     int iSeg
 * @param     STR_PULSE_TRAIN_SEG * pSeg
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-01-10, 15:56
 * @warning
 */
void CPulExt::PrintSeg( int iSeg, STR_PULSE_TRAIN_SEG *pSeg )
{
#ifdef _MSC_VER
    char szPulseTrainMark[CHECKED_SEG+1] = { '#', 'X', 'M', 'C' };
    char szFreqType[MAX_FRQTYPE][3] = { "F_", "HO", "RA", "PA", "UK", "IF" } ;
    char szPRIType[MAX_PRITYPE][3] = { "ST", "DW", "JR", "JP", "SG", "SS", "JS" } ;

    Log( enDebug, "\t[%2d]%1c: Co(%3d), %s (%5d-%5d), %s %5d(%5d-%5d)/%2d, PW(%5d -%5d), I(%3d(0x%0llx),%3d -%3d)" ,
        iSeg,
        szPulseTrainMark[pSeg->enMark],
        pSeg->stPDW.uiCount,
        szFreqType[pSeg->uiFreqType], I_FRQMhzCNV( pSeg->uiBand, pSeg->freq.iMin ), I_FRQMhzCNV( pSeg->uiBand, pSeg->freq.iMax ),
        szPRIType[pSeg->enPriType], I_TOAusCNV( pSeg->stPRI.tMean ), I_TOAusCNV( pSeg->stPRI.tMin ), I_TOAusCNV( pSeg->stPRI.tMax ), IMUL( pSeg->fJitterRatio, 100 ),
        I_PWCNV( pSeg->pw.iMin ), I_PWCNV( pSeg->pw.iMax ),
        m_pGrPdwIndex->pIndex[pSeg->gr_ref_idx], m_pTOA[m_pGrPdwIndex->pIndex[pSeg->gr_ref_idx]], m_pGrPdwIndex->pIndex[pSeg->first_idx], m_pGrPdwIndex->pIndex[pSeg->last_idx] );

#endif

}

/**
 * @brief     펄스열 추출한 PDW의 인덱스를 출력한다.
 * @param     STR_PULSE_TRAIN_SEG * pSeg
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-06-14, 13:45
 * @warning
 */
void CPulExt::PrintAllSegPDW( STR_PULSE_TRAIN_SEG *pSeg )
{
#ifdef _MSC_VER
    unsigned int i, iCnt=0;
    char szBuffer[5000];

    PDWINDEX refIdx;

    refIdx = m_pGrPdwIndex->pIndex[pSeg->gr_ref_idx];

    for( i=1 ; i < pSeg->stPDW.uiCount && i < m_uiMaxPdw ; ++i ) {
        if( refIdx == pSeg->stPDW.pIndex[i] ) {
#ifdef _MSC_VER
            iCnt += sprintf_s( &szBuffer[iCnt], sizeof( szBuffer ) - iCnt, ",*%3d", pSeg->stPDW.pIndex[i] );
#else
            iCnt += sprintf( &szBuffer[iCnt], ",*%3d", pSeg->stPDW.pIndex[i] );
#endif
        }
        else {
#ifdef _MSC_VER
            iCnt += sprintf_s( &szBuffer[iCnt], sizeof( szBuffer ) - iCnt, ", %3d", pSeg->stPDW.pIndex[i] );
#else
            iCnt += sprintf( &szBuffer[iCnt], ", %3d", pSeg->stPDW.pIndex[i] );
#endif
        }
    }

    if( refIdx == pSeg->stPDW.pIndex[0] )
        Log( enDebug, "\t\t(%3d:*%3d%s)", pSeg->stPDW.uiCount, pSeg->stPDW.pIndex[0], szBuffer );
    else
        Log( enDebug, "\t\t(%3d: %3d%s)", pSeg->stPDW.uiCount, pSeg->stPDW.pIndex[0], szBuffer );

#endif

}


//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CPulExt::ExtractTrackPT
//!	\author  조철희
//! \param    refPriMean 인자형태 UINT
//! \param    refJitRat 인자형태 float
//!	\return	 void
//! \version 1.0
//! \date		 2006-06-28 01:16:34
//! \warning
//
void CPulExt::ExtractTrackPT( _TOA refPriMean, float refJitRat )
{
    unsigned int i;
    _TOA nHarmonic;
    STR_PULSE_TRAIN_SEG *pSeg;

    pSeg = & m_Seg[0];
    for( i=0 ; i < m_uiCoSeg ; ++i ) {
        nHarmonic = CheckHarmonic( refPriMean, refJitRat, pSeg->stPRI.tMean, pSeg->fJitterRatio );
        if( nHarmonic == 0 ) {
            pSeg->enMark = DELETE_SEG;
        }
        ++ pSeg;
    }
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CPulExt::SavePdwParamIndex
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2006-02-15 14:24:27
//
void CPulExt::SavePdwParamIndex()
{
    unsigned int i, j;

    STR_PULSE_TRAIN_SEG *pSeg;

    int *pParam;
    PDWINDEX *pPdwIndex;

    // 펄스열 인덱스 초기화
    pParam = m_PdwParam.piParam;
    memset( pParam, 0, sizeof( UINT ) * m_uiMaxPdw );

    pSeg = & m_Seg[0];
    for( i=0 ; i < m_uiCoSeg ; ++i ) {
        if( pSeg->enMark == NORMAL_SEG ) {
            pPdwIndex = pSeg->stPDW.pIndex;
            for( j=0 ; j < pSeg->stPDW.uiCount ; ++j ) {
                /*! \bug  펄스열 추출의 입력 인덱스를 포인터함.
                    \date 2006-08-24 15:38:52, 조철희
                */
                pParam[ m_pGrPdwIndex->pIndex[ *pPdwIndex++ ] ] = 1;
            }
        }

        ++ pSeg;
    }
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CPulExt::ResetJitterSeg

                            마지막으로 불규칙성 펄스열이 추출한 펄스열의 인덱스로 초기화한다.
        \author   조철희
        \return   void
        \version  1.37
        \date     2007-07-02 11:41:27
        \warning
*/
void CPulExt::ResetJitterSeg()
{
    unsigned int i;
    STR_PULSE_TRAIN_SEG *pSeg;

    pSeg = & m_Seg[m_uiAnalSeg];
    for( i=m_uiAnalSeg ; i < m_uiCoSeg ; ++i, ++pSeg ) {
        if( pSeg->enPriType == _JITTER_RANDOM ) {
            m_uiCoSeg = i;
            break;
        }
    }
}

/**
 * @brief     MakeCWPulseTrain
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-07-07, 09:44
 * @warning
 */
void CPulExt::MakeCWPulseTrain()
{
    STR_PULSE_TRAIN_SEG *pSeg;

    PDWINDEX *pPdwIndex;

    pPdwIndex = & m_pGrPdwIndex->pIndex[0];

    pSeg = & m_Seg[ m_uiCoSeg ];

    memcpy( pSeg->stPDW.pIndex, pPdwIndex, sizeof(PDWINDEX) * m_pGrPdwIndex->uiCount );
    pSeg->stPDW.uiCount = m_pGrPdwIndex->uiCount;

    pSeg->stPRI.tMin = 0;
	pSeg->stPRI.tMax = 500002; // UINT64_MAX;
	pSeg->stPRI.tMean = 0;

    pSeg->gr_ref_idx = 0;
    pSeg->first_idx = 0;
    pSeg->last_idx = pSeg->stPDW.uiCount - 1;
    pSeg->uiMiss = 0;
    pSeg->enMark = NORMAL_SEG;
    pSeg->enPriType = _STABLE;
    CalcSegParam( pSeg, TRUE );

    ++ m_uiCoSeg;

}


