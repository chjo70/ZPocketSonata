// Group.cpp: implementation of the CGroup class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//#include "../OFP_Main.h"

#if defined(_ELINT_) || defined(_XBAND_)
//#include "../OFP_Main.h"

#elif defined(_POCKETSONATA_)
#include "../Identify/ELUtil.h"

#else
#error "컴파일러에 DEFINE 을 추가해야 합니다."

#endif

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ISODATA.h"

#include "../../Utils/ccommonutils.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/**
 * @brief     CISODATA
 * @param     unsigned int uiCoMaxPdw
 * @return    
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-24, 16:32
 * @warning
 */
CISODATA::CISODATA( unsigned int uiN, unsigned int uiCoMaxPDW )
{
    unsigned int ui, uj;

    BOOL bRet = TRUE;

    m_uiN = uiN;

    m_pCluster = ( STR_CLUSTER * ) malloc( sizeof( STR_CLUSTER ) * MAX_AGRT );
    if( m_pCluster == NULL ) {
        bRet = FALSE;
        printf( "\n [W] m_pCluster's Memory allocation error !" );
        WhereIs;
    }
    else {
        for( ui = 0 ; ui < MAX_AGRT ; ++ui ) {
            m_pCluster[ui].stPDWIndex.pIndex = ( PDWINDEX * ) malloc( sizeof( PDWINDEX ) * SCN_COLLECT_PDW );
            if( m_pCluster[ui].stPDWIndex.pIndex == NULL ) {
                bRet = FALSE;
                printf( "\n [W] m_pCluster->pIndex's Memory allocation error !" );
                WhereIs;
            }

            m_pCluster[ui].ppstStat = ( STR_CLUSTER_STAT ** ) malloc( sizeof( STR_CLUSTER_STAT * ) * uiN );

            for( uj = 0 ; uj < uiN; ++uj ) {
                m_pCluster[ui].ppstStat[uj] = (STR_CLUSTER_STAT *) malloc( sizeof( STR_CLUSTER_STAT ) );
                if( m_pCluster[ui].ppstStat[uj] == NULL ) {
                    bRet = FALSE;
                    printf( "\n [W] m_pCluster[ui].ppstStat[uj]'s Memory allocation error !" );
                    WhereIs;
                }
            }

        }
    }

    m_ppfPDWParam = ( float ** ) malloc( sizeof( float * ) * uiN );
    if( m_ppfPDWParam == NULL ) {
        bRet = FALSE;
        printf( "\n [W] m_ppfPDWParam's Memory allocation error !" );
        WhereIs;
    }
    else {
        for( ui = 0 ; ui < uiN ; ++ui ) {
            *(m_ppfPDWParam + ui) = ( float * ) malloc( sizeof( float ) * uiCoMaxPDW );
            if( *(m_ppfPDWParam + ui) == NULL ) {
                bRet = FALSE;
                printf( "\n [W] *(m_ppfPDWParam + i)'s Memory allocation error !" );
                WhereIs;
            }
        }

    }

    m_ppPDWParam = ( unsigned int ** ) malloc( sizeof( unsigned int * ) * uiN );
    if( m_ppPDWParam == NULL ) {
        bRet = FALSE;
        printf( "\n [W] m_ppPdwParam's Memory allocation error !" );
        WhereIs;
    }
	else {
		for (ui = 0; ui < uiN; ++ui) {
			*(m_ppPDWParam + ui) = (unsigned int *)malloc(sizeof(unsigned int) * uiCoMaxPDW);
			if (*(m_ppPDWParam + ui) == NULL) {
				bRet = FALSE;
				printf("\n [W] *(m_ppPDWParam + i)'s Memory allocation error !");
				WhereIs;
			}
		}
	}

    if( bRet == FALSE ) {
        printf( "\n 그룹화 클래스 생성자 실패 !" );
    }

}

/**
 * @brief     클래스의 소멸 처리를 수행한다.
 * @return    
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-24, 16:32
 * @warning
 */
CISODATA::~CISODATA()
{
    unsigned int ui, uj;

    STR_CLUSTER *pCluster;

    for( ui = 0 ; ui < MAX_AGRT ; ++ui ) {
        pCluster = & m_pCluster[ui];
        free( pCluster->stPDWIndex.pIndex );

        for( uj = 0 ; uj < m_uiN; ++uj ) {
            free( pCluster->ppstStat[uj] );
        }
        free( pCluster->ppstStat );
    }
    free( m_pCluster );

    for( ui = 0 ; ui < m_uiN ; ++ui ) {
        free( *(m_ppfPDWParam + ui) );
    }
    free( m_ppfPDWParam );

	for (ui = 0; ui < m_uiN; ++ui) {
		free(*(m_ppPDWParam + ui));
	}
    free( m_ppPDWParam );
}


//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CGroup::ISODATA
// 반환되는 형  : void
// 함 수 인 자  : STR_PDWINDEX *pSrcIndex
// 함 수 인 자  : UINT *pPdw
// 함 수 설 명  :
// 최 종 변 경  : 조철희, 2005-12-28 13:23:43
//
#if defined(_ELINT_) || defined(_XBAND_)
#define		MAXIMUM_STANDARD_DEVIATION		(float) (1.0)
#define		MAXIMUM_DISTANCE_OF_CLUSTERS	UMUL( 1, _spRxdfAoa )		// 클러스터 사이간의 최대 길이

#elif defined(_POCKETSONATA_)
#define		MAXIMUM_STANDARD_DEVIATION		(float) (1.0)
#define		MAXIMUM_DISTANCE_OF_CLUSTERS	UMUL( 1, KHARM_AOA_MAR )		// 클러스터 사이간의 최대 길이

#else
#define		MAXIMUM_STANDARD_DEVIATION		UMUL( 1, _spRxdfAoaLow )		// 대역중에서 가장 큰 방위 오차
#define		MAXIMUM_DISTANCE_OF_CLUSTERS	UMUL( 1, _spRxdfAoaLow )		// 클러스터 사이간의 최대 길이
#endif

#define		NUMBER_OF_CLUSTER				( MAX_AOA_GROUP )						// 최대 클러스터 개수
#define		MINIMUM_NUMBER_OF_SAMPLES		( RJGPC )										// 클러스터 내의 가장 작은 샘플 개수
#define		NUMBER_OF_ITERATIONS			( 20 )
#define		SPLIT_RATIO						( 0.6 )

/**
 * @brief     입력한 특성 데이터를 입력하고 클러스터링을 수행한다. 클러스터링 정보는 멤버 변수에 저장된다.
 * @param     STR_PDWINDEX * pSrcIndex
 * @param     UINT * pPDW1
 * @param     UINT * pPDW2
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-24, 17:07
 * @warning
 */
void CISODATA::Run( STR_PDWINDEX *pSrcIndex, UINT *pPDW1, UINT *pPDW2 )
{
    unsigned int i, j, k;
    int nSplitCluster;

    STR_CLUSTER *pCluster;

    //-- 조철희 2006-01-05 10:54:31 --//
    if( pSrcIndex->uiCount <= MINIMUM_NUMBER_OF_SAMPLES ) {
        m_uiClusters = 0;
    }
    else {
        // 초기화
        InitOfISODATA( pSrcIndex, pPDW1, pPDW2 );

        // 클러스터링 시작
        for (i = 0; i < NUMBER_OF_ITERATIONS && m_uiClusters < (MAX_AGRT-2) ; ++i) {
            //
            nSplitCluster = 0;
            pCluster = &m_pCluster[0];
            for (j = 0; j < m_uiClusters; ++j) {
                if (TRUE == SplitCenter(pCluster, &m_pCluster[MAX_AGRT - 2])) {

                    for( k = m_uiClusters + nSplitCluster - 1; k >= j + nSplitCluster + 1; --k ) {
                        CopyCluster( &m_pCluster[k + 1], &m_pCluster[k] );
                    }

                    CopyCluster( pCluster++, &m_pCluster[MAX_AGRT - 1] );
                    CopyCluster( pCluster++, &m_pCluster[MAX_AGRT - 2] );

                    ++nSplitCluster;

                }
                else {
                    ++pCluster;
                }
            }

            // 클러스터링 내의 변동 사항이 없으면 루프를 빠져나온다.
            if( nSplitCluster == 0 ) {
                break;
            }

            m_uiClusters = m_uiClusters + nSplitCluster;

            MarkPDWIndexByAllCluster( &m_pCluster[MAX_AGRT - 1], pSrcIndex );
        }
    }

    MarkPDWIndexByAllCluster( &m_pCluster[MAX_AGRT - 1], pSrcIndex );
}

/**
 * @brief     지정된 클러스터의 PDWINEX에 클러스터링 된 번호를 마킹한다.
 * @param     STR_CLUSTER * pDstCluster
 * @param     STR_PDWINDEX * pSrcIndex
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-25, 15:26
 * @warning
 */
void CISODATA::MarkPDWIndexByAllCluster( STR_CLUSTER *pDstCluster, STR_PDWINDEX *pSrcIndex )
{
    unsigned int i, j, k;

    PDWINDEX *pPDWIndex, *pCIndex;
    STR_CLUSTER *pCluster;

    PDWINDEX usPDWIndex;

    TRACE( "\n ################################################" );

    pDstCluster->stPDWIndex.uiCount = pSrcIndex->uiCount;

    pPDWIndex = pDstCluster->stPDWIndex.pIndex;
    pCluster = &m_pCluster[0];
    for( i = 0; i < m_uiClusters; ++i ) {
        pCIndex = pCluster->stPDWIndex.pIndex;
        for( j = 0 ; j < pCluster->stPDWIndex.uiCount ; ++j ) {
            usPDWIndex = *pCIndex++;
            *(pPDWIndex+usPDWIndex) = i + 1;
        }

        TRACE( "\n 클러스터[#%2d] : %d\n\t", i + 1, pCluster->stPDWIndex.uiCount );
        for( k = 0 ; k < m_uiN ; ++k ) {
            TRACE( "[%7.3f]", pCluster->ppstStat[k]->fMean );
        }
        
        ++pCluster;
    }

}

/**
 * @brief     대상 클러스터를 목적 클러스터에 복사한다.
 * @param     STR_CLUSTER * pDstCluster
 * @param     STR_CLUSTER * pSrcCluster
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-25, 12:32
 * @warning
 */
void CISODATA::CopyCluster( STR_CLUSTER *pDstCluster, STR_CLUSTER *pSrcCluster )
{
    unsigned int i;

    // PDWINDEX 복사
    memcpy( pDstCluster->stPDWIndex.pIndex, pSrcCluster->stPDWIndex.pIndex, sizeof( PDWINDEX ) * pSrcCluster->stPDWIndex.uiCount );
    pDstCluster->stPDWIndex.uiCount = pSrcCluster->stPDWIndex.uiCount;

    // 거리? 복사
    pDstCluster->fDistance = pSrcCluster->fDistance;

    // 통계 정보 복사
    for( i = 0 ; i < m_uiN ; ++i ) {
        memcpy( pDstCluster->ppstStat[i], pSrcCluster->ppstStat[i], sizeof( STR_CLUSTER_STAT ) );
    }
    
}

/**
 * @brief     클러스터 분리 여부를 확인 후 클러스터 분리 작업을 한다.
 * @param     STR_CLUSTER * pCluster
 * @param     STR_CLUSTER * pDstCluster
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-25, 10:25
 * @warning
 */
bool CISODATA::SplitCenter( STR_CLUSTER *pCluster, STR_CLUSTER *pDstCluster )
{
    bool bRet=false;
    STR_CLUSTER *pCluster1, *pCluster2;

    /*! \bug  방위 그룹화 범위를 체크해서 빈 영역이 없는지를 검사한다.
        \date 2006-08-18 10:25:24, 조철희
    */
    pCluster1 = pDstCluster++;
    pCluster2 = pDstCluster;

    if ( IsSplitCluster(pCluster) == true ) {
        SplitCenter(pCluster1, pCluster2, pCluster);

        if( pCluster1->stPDWIndex.uiCount > MINIMUM_NUMBER_OF_SAMPLES && pCluster2->stPDWIndex.uiCount > MINIMUM_NUMBER_OF_SAMPLES) {
            bRet = true;
        }
        else {
            bRet = false;
        }
        // 클러스터 내의 모든 개수가 최소 클러스터 개수보다 커야 분리된다.
        // if( pCluster1->count > MINIMUM_NUMBER_OF_SAMPLES && pCluster2->count > MINIMUM_NUMBER_OF_SAMPLES )
        //-- 조철희 2006-01-04 15:52:41 --//
    }

    return bRet;
}

/**
 * @brief     클러스터링 분리 여부를 체크한다.
 * @param     STR_CLUSTER * pCluster
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-24, 17:19
 * @warning
 */
bool CISODATA::IsSplitCluster( STR_CLUSTER *pCluster )
{
    unsigned int i;
    bool bRet = false;

    if( pCluster->stPDWIndex.uiCount >= MINIMUM_NUMBER_OF_SAMPLES ) {
        for( i = 0 ; i < m_uiN ; ++i ) {
            if( pCluster->ppstStat[i]->fStandardDeviation > MAXIMUM_STANDARD_DEVIATION ) {
                bRet = true;
                break;
            }
        }
    }

    return bRet;
}

/**
 * @brief     클러스터의 중심 값을 이동해서 2개로 클러스터를 분리한다.
 * @param     STR_CLUSTER * pDstCluster1
 * @param     STR_CLUSTER * pDstCluster2
 * @param     STR_CLUSTER * pSrcCluster
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2005-12-29 10:39:58
 * @warning
 */
void CISODATA::SplitCenter( STR_CLUSTER *pDstCluster1, STR_CLUSTER *pDstCluster2, STR_CLUSTER *pSrcCluster )
{
    unsigned int i;
    
    float fDistance1, fDistance2;
    unsigned int uiCount1, uiCount2;

    PDWINDEX *pCIndex;
    PDWINDEX *pDstCIndex1, *pDstCIndex2;

    // 초기 설정
    pCIndex = & pSrcCluster->stPDWIndex.pIndex[0];
    pDstCIndex1 = & pDstCluster1->stPDWIndex.pIndex[0];
    pDstCIndex2 = & pDstCluster2->stPDWIndex.pIndex[0];

    _EQUALS3( uiCount1, uiCount2, _spZero )
    _EQUALS3( pDstCluster1->stPDWIndex.uiCount, pDstCluster2->stPDWIndex.uiCount, _spZero )

    // 분리할 클러스터의 중심 값을 계산한다.
    CalcSplitCluster( pDstCluster1, pDstCluster2, pSrcCluster );

    // 중심 값을 중심으로 가까운 클러스트에 PDWINDEX 를 삽입한다.
    pCIndex = pSrcCluster->stPDWIndex.pIndex;
    for( i = 0 ; i < pSrcCluster->stPDWIndex.uiCount ; ++i ) {
        fDistance1 = CalcDistance( pDstCluster1, *pCIndex );
        fDistance2 = CalcDistance( pDstCluster2, *pCIndex );

        if( fDistance1 < fDistance2 ) {
            pDstCluster1->stPDWIndex.pIndex[uiCount1++] = *pCIndex;
        }
        else {
            pDstCluster2->stPDWIndex.pIndex[uiCount2++] = *pCIndex;
        }

        ++pCIndex;
    }

    pDstCluster1->stPDWIndex.uiCount = uiCount1;
    pDstCluster2->stPDWIndex.uiCount = uiCount2;

    // 분리된 클러스터의 통계치를 계산하여 업데이트 한다.
    CalClusterInfo( pDstCluster1 );
    CalClusterInfo( pDstCluster2 );

}

/**
 * @brief     클러스터의 중심 값과 PDWINDEX 간의 거리차를 계산한다.
 * @param     STR_CLUSTER * pDstCluster
 * @param     PDWINDEX * pPDWIndex
 * @return    float
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-25, 13:48
 * @warning
 */
float CISODATA::CalcDistance( STR_CLUSTER *pDstCluster, PDWINDEX usPDWIndex )
{
    unsigned int i;

    float fMean, fDistance, fSumDistance = (float) 0.;
    float *pfPDWParam;

    for( i = 0 ; i < m_uiN ; ++i ) {
        pfPDWParam = m_ppfPDWParam[i];

        fMean = pDstCluster->ppstStat[i]->fMean;

        // 1차원 계산시
        if( m_uiN == _spOne ) {
            fDistance = abs( pfPDWParam[usPDWIndex] - fMean );
            fSumDistance += fDistance;
        }
        else {
            fDistance = pfPDWParam[usPDWIndex] - fMean;
            fSumDistance += ( fDistance * fDistance );
        }
    }

    return fSumDistance;
}

/**
 * @brief     분리할 클러스터의 중심 값을 계산한다.
 * @param     STR_CLUSTER * pDstCluster1
 * @param     STR_CLUSTER * pDstCluster2
 * @param     STR_CLUSTER * pSrcCluster
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-25, 10:28
 * @warning
 */
void CISODATA::CalcSplitCluster( STR_CLUSTER *pDstCluster1, STR_CLUSTER *pDstCluster2, STR_CLUSTER *pSrcCluster )
{
    unsigned int i, j;
    PDWINDEX *pPDWIndex;

    float fVector;
    float *pfPDWParam;

    for( i = 0 ; i < m_uiN ; ++i ) {
        pfPDWParam = m_ppfPDWParam[i];
        fVector = (float) 0.;

        pPDWIndex = pSrcCluster->stPDWIndex.pIndex;
        for( j = 0 ; j < pSrcCluster->stPDWIndex.uiCount ; ++j ) {
            fVector += pfPDWParam[*pPDWIndex];
            pPDWIndex++;

        }

        fVector /= pSrcCluster->stPDWIndex.uiCount;

        pDstCluster1->ppstStat[i]->fMean = pSrcCluster->ppstStat[i]->fMean + fVector;

        pDstCluster2->ppstStat[i]->fMean = pSrcCluster->ppstStat[i]->fMean - fVector;
        
    }

//     TRACE( "\n *****************************************" );
//     TRACE( "\n 분리 클러스터 1번\n\t" );
//     for( i = 0 ; i < m_uiN ; ++i ) {
//         TRACE( "[%7.3f]", pDstCluster1->ppstStat[i]->fMean );
//     }
//     TRACE( "\n 분리 클러스터 2번\n\t" );
//     for( i = 0 ; i < m_uiN ; ++i ) {
//         TRACE( "[%7.3f]", pDstCluster2->ppstStat[i]->fMean );
//     }

}

/**
 * @brief     클러스터링 수행 하기 위한 초기화를 수행한다.
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-23, 16:22
 * @warning
 */
void CISODATA::InitOfISODATA( STR_PDWINDEX *pSrcIndex, UINT *pPDW1, UINT *pPDW2 )
{
	unsigned int i;
    STR_MINMAX_SDEV stStat;

    STR_CLUSTER *pCluster;

	UINT *pPDWParam;

	pPDWParam = m_ppPDWParam[0];
	for (i = 0; i < pSrcIndex->uiCount; ++i) {
		*pPDWParam = UDIV( *pPDW1, 1 );
		++ pPDWParam;
		++pPDW1;
	}
    //m_ppPDWParam[0] = pPDW1;

    CalAOAStat( &stStat, m_ppPDWParam[0], pSrcIndex );
    MakeStandard( m_ppfPDWParam[0], &stStat, m_ppPDWParam[0], pSrcIndex );

    // PARAM1 과 PARAM2 의 표준화 작업 처리
    if( pPDW2 != NULL ) {
		pPDWParam = m_ppPDWParam[1];
		for (i = 0; i < pSrcIndex->uiCount; ++i) {
			*pPDWParam = UDIV( *pPDW2, 1 );
			++pPDWParam;
			++pPDW2;
		}
        //m_ppPDWParam[1] = pPDW2;
       
        CalParamStat( &stStat, m_ppPDWParam[1], pSrcIndex );
        MakeStandard( m_ppfPDWParam[1], & stStat, m_ppPDWParam[1], pSrcIndex );
    }

    m_uiClusters = _spOne;

    // 초기 클러스터링 설정
    pCluster = & m_pCluster[0];
    
    pCluster->stPDWIndex.uiCount = pSrcIndex->uiCount;
    memcpy( pCluster->stPDWIndex.pIndex, pSrcIndex->pIndex, sizeof( PDWINDEX )*pCluster->stPDWIndex.uiCount );

    CalClusterInfo( pCluster );

}

/**
 * @brief     평균값을 뺀 값에 분산 값을 나눈 값으로 표준화 데이터 처리를 한다.
 * @param     float * pfPDWParam
 * @param     STR_MINMAX_SDEV * pstStat
 * @param     UINT * pPDWParam
 * @param     STR_PDWINDEX * pSrcIndex
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-23, 17:29
 * @warning
 */
void CISODATA::MakeStandard( float *pfPDWParam, STR_MINMAX_SDEV *pstStat, UINT *pPDWParam, STR_PDWINDEX *pSrcIndex )
{
    unsigned int i;
    PDWINDEX *pPDWIndex;

    pPDWIndex = pSrcIndex->pIndex;

    for( i = 0 ; i < pSrcIndex->uiCount ; ++i ) {
        *pfPDWParam = ( (int) pPDWParam[*pPDWIndex] - pstStat->iMean ) / pstStat->fsdev;

        ++pPDWIndex;
        ++pfPDWParam;
    }
}

/**
 * @brief     방탐 정보에 대해서 통계값을 계산한다.
 * @param     int * piMean
 * @param     float * pfDev
 * @param     UINT * pPDW
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-23, 16:40
 * @warning
 */
void CISODATA::CalAOAStat( STR_MINMAX_SDEV *pstStat, UINT *pPDWParam, STR_PDWINDEX *pSrcIndex )
{
    unsigned int i;
    int iMean = 0, diffAoa, overAoa;

    PDWINDEX *pPDWIndex;

    pPDWIndex = pSrcIndex->pIndex;
    int frstAoa = pPDWParam[*pPDWIndex];

    // 평균 구하기
    _EQUALS3( pstStat->iMax, pstStat->iMin, frstAoa )

    for( i = 0 ; i < pSrcIndex->uiCount ; ++i ) {
        diffAoa = ( int ) pPDWParam[*pPDWIndex] - frstAoa;
        overAoa = _abs( diffAoa );
        if( overAoa > MAX_AOA / 2 ) {
            if( frstAoa > MAX_AOA / 2 )
                diffAoa = diffAoa + MAX_AOA;
            else
                diffAoa = diffAoa - MAX_AOA;
        }

        iMean += diffAoa;
        pstStat->iMax = max( pstStat->iMax, ( int ) diffAoa );
        pstStat->iMin = min( pstStat->iMin, ( int ) diffAoa );

        ++pPDWIndex;
    }

    pstStat->iMean = (MAX_AOA + IDIV( iMean, pSrcIndex->uiCount ) + frstAoa) % MAX_AOA;
    pstStat->iMax = (MAX_AOA + pstStat->iMax + frstAoa) % MAX_AOA;
    pstStat->iMin = (MAX_AOA + pstStat->iMin + frstAoa) % MAX_AOA;

    diffAoa = pstStat->iMax - pstStat->iMin;
    if( diffAoa > MAX_AOA / 2 ) {
        diffAoa = pstStat->iMax;
        pstStat->iMax = pstStat->iMin;
        pstStat->iMin = diffAoa;
    }

    // 분산 구하기
    iMean = 0;
    pPDWIndex = pSrcIndex->pIndex;
    for( i = 0 ; i < pSrcIndex->uiCount ; ++i ) {
        diffAoa = CCommonUtils::CalcDiffAOA( pPDWParam[*pPDWIndex], pstStat->iMean );
        iMean += ( diffAoa * diffAoa );

        ++pPDWIndex;
    }
    pstStat->fsdev = (float) ( sqrt( ( double ) iMean ) / pSrcIndex->uiCount );

}

/**
 * @brief     방위 정보 이외의 데이터에 대해서 통계값을 계산한다.
 * @param     int * piMean
 * @param     float * pfDev
 * @param     UINT * pPDW
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-23, 16:40
 * @warning
 */
void CISODATA::CalParamStat( STR_MINMAX_SDEV *pstStat, UINT *pPDWParam, STR_PDWINDEX *pSrcIndex )
{
    unsigned int i;
    int iMean = 0, diffVal;
	float fMean = (float) 0.;

    PDWINDEX *pPDWIndex;

    pPDWIndex = pSrcIndex->pIndex;
    int frstVal = pPDWParam[*pPDWIndex];

    // 평균 구하기
    pstStat->iMax = -frstVal;
    pstStat->iMin = frstVal;

    for( i = 0 ; i < pSrcIndex->uiCount ; ++i ) {
        diffVal = ( int ) pPDWParam[*pPDWIndex] - frstVal;

        iMean += diffVal;
        pstStat->iMax = max( pstStat->iMax, ( int ) diffVal );
        pstStat->iMin = min( pstStat->iMin, ( int ) diffVal );

        ++pPDWIndex;
    }

    pstStat->iMean = IDIV( iMean, pSrcIndex->uiCount ) + frstVal;
    pstStat->iMax = pstStat->iMax + frstVal;
    pstStat->iMin = pstStat->iMin + frstVal;


    // 분산 구하기
	fMean = 0;
    pPDWIndex = pSrcIndex->pIndex;
    for( i = 0 ; i < pSrcIndex->uiCount ; ++i ) {
        diffVal = pPDWParam[*pPDWIndex] - pstStat->iMean;
		fMean += (float) (diffVal * diffVal);

        ++pPDWIndex;
    }
    pstStat->fsdev = ( float ) (sqrt( ( double ) fMean ) / pSrcIndex->uiCount);

}

/**
 * @brief     모든 특성에 대해서 클러스터 통계값을 계산한다.
 * @param     STR_CLUSTER * pCluster
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-23, 18:16
 * @warning
 */
void CISODATA::CalClusterInfo( STR_CLUSTER *pCluster )
{
    unsigned int i;

    // 파라메타1, 파라메타2 에 대해서 통계 값을 계산한다.

    for( i = 0 ; i < m_uiN ; ++i ) {
        CalClusterInfo( pCluster, i );
    }

}

/**
 * @brief     한 특성에 대해서 클러스터 통계값을 계산한다.
 * @param     unsigned int uiN
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-24, 17:37
 * @warning
 */
void CISODATA::CalClusterInfo( STR_CLUSTER *pCluster, unsigned int uiN )
{
    unsigned int i;
    unsigned int *pPDWParam;

    PDWINDEX *pCIndex;

    STR_CLUSTER_STAT *pstClusterStat;

    float fDiff, fStdDev, fMean;

    float *pfPDWParam;

    // 파라메타1, 파라메타2 에 대해서 통계 값을 계산한다.

    // 1. 평균 계산
    fDiff = (float) 0.;
    pCIndex = pCluster->stPDWIndex.pIndex;

    pfPDWParam = & m_ppfPDWParam[uiN][0];
    pPDWParam = & m_ppPDWParam[uiN][0];

    pstClusterStat = pCluster->ppstStat[uiN];

    _EQUALS3( pstClusterStat->iLow, pstClusterStat->iHgh, pPDWParam[*pCIndex] )
    for( i = 0 ; i < pCluster->stPDWIndex.uiCount ; ++i ) {
        fDiff += pfPDWParam[*pCIndex];

        pstClusterStat->iLow = min( (unsigned int) pstClusterStat->iLow, pPDWParam[*pCIndex] );
        pstClusterStat->iHgh = max( ( unsigned int ) pstClusterStat->iHgh, pPDWParam[*pCIndex] );

        ++pCIndex;
    }

    if( pstClusterStat->iHgh - pstClusterStat->iHgh > MAX_AOA/2 ) {
        TRACE( "\n 방위가 반대로 설정해야 합니다. !!!" );
    }

    fMean = FDIV( fDiff, pCluster->stPDWIndex.uiCount );
    pstClusterStat->fMean = fMean;

    // 2. 거리 및 분산 계산
    pCIndex = pCluster->stPDWIndex.pIndex;
    fStdDev = ( float ) 0;
    for( i = 0 ; i < pCluster->stPDWIndex.uiCount ; ++i ) {
        fDiff = ( pfPDWParam[*pCIndex] - fMean);

        fStdDev += (fDiff * fDiff);

        ++pCIndex;

    }
    //pCluster->fDistance = ( float ) ( fDiff / pCluster->stPDWIndex.uiCount );
    pstClusterStat->fStandardDeviation = ( float ) (sqrt( fStdDev / pCluster->stPDWIndex.uiCount ));

}

