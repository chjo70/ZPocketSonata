/**
 * @file      LOB 클러스터링 관련 클래스
 * @brief     
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-06-22, 오후 2:33 
 * @warning   
 */

#ifdef _MSC_VER
#include "stdafx.h"

#endif

using namespace std;

#include <algorithm>

#include "LOBClustering.h"
#include "ELDecoder.h"
//#include "../../../ELINT/ELCOMMON/IsNumber.h"

//#include "../../../COMMON/MNGR/GRLogMngr.h"
//#include "../../../COMMON/COMMIF/CGRCommIF.h"
#include "../ParamMngr.h"
//#include "../../../COMMON/MNGR/GRLoginMngr.h"

//#include "../../../ELINT/MNGR/ELOperationCtrlMngr.h"
//#include "../../../ELINT/MNGR/ELEmitterMergeMngr.h"

#include "./constants.h"
#include "../EmitterMerge/InverseMethod/CInverseMethod.h"

//#include "../../MNGR/ELEnvironVariableMngr.h"
#include "../EmitterMerge/ELPosEstDataType.h"
#include "../EmitterMerge/PositionEstimationAlg.h"
#include "../EmitterMerge/ELEnvironVariableMngr.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#define CRTDBG_MAP_ALLOC
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


int incClusterCompare( const void *arg1, const void *arg2 )
{
	int iRet;
	const STR_LOBCLUSTER *p1, *p2;

	p1 = (const STR_LOBCLUSTER *) arg1;
	p2 = (const STR_LOBCLUSTER *) arg2;

	if( p1->iCount < p2->iCount ) {
		iRet = 1;
	}
	else if( p1->iCount > p2->iCount ) {
		iRet = -1;
	}
	else {
		iRet = 0;
	}

	return iRet;
}

/**
 * @brief     생성자로서 모의기 모드 플레그 반영, LOB POOL 버퍼를 할당한다.
 * @param     해당사항 없음
 * @return    해당사항 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-07-19, 오후 1:09 
 * @warning   
 */
CLOBClustering::CLOBClustering()
{
	int i;

	m_bIsSimulator = false;	// ST_OCM->IsSimulatorMode();

	// 연동기 또는 모의기 할 때만 아래를 수행하게 함.
	if( m_bIsSimulator == true || GP_MGR_PARAM->IsPOSN() == false ) {
		// LOB Pool 할당
		m_pQueLOBDataPool = new Queue<SELLOBDATA_MINIMIZE> [TOTAL_ITEMS_OF_THREAT_NODE];

		for( i=0 ; i < TOTAL_ITEMS_OF_THREAT_NODE ; ++i ) {
			m_pQueLOBDataPool[i].Init( QUEUE_LOB_POOL_SIZE );
		}

		// m_pfDist = ( float * ) malloc( sizeof(float) * MAX_INTERSECTIONS );

	}
	else {
		m_pQueLOBDataPool = NULL;

	}

	m_nCreateClustering = 0;
	m_nCheckClustering = 0;

	AllocMemory();
}

/**
 * @brief     소멸자로서 해당 처리가 없음
 * @param     해당사항 없음
 * @return    해당사항 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-07-19, 오후 1:09 
 * @warning   
 */
CLOBClustering::~CLOBClustering()
{
	FreeMemory();

	// 소멸자에세 객체를 메모리에서 해지함.
	delete [] m_pQueLOBDataPool;

}

//////////////////////////////////////////////////////////////////////
/*!
 * @brief     LOB 클러스터링을 초기화한다.
 * @return    void
 * @param     void
 * @version   0.0.1
 * @author    조철희(churlhee.jo@lignex1.com)
 * @date      2017-09-18 오후 2:01 
 * @warning   
 */
void CLOBClustering::InitOfLOBClustering()
{
	int i;

	TRACE( "\n #### 클러스터링 시도 횟수 : %d" , m_nCheckClustering );
	TRACE( "\n #### 클러스터링 성공 횟수 : %d" , m_nCreateClustering );

	for( i=0 ; i < TOTAL_ITEMS_OF_THREAT_NODE ; ++i ) {
		m_pQueLOBDataPool[i].Init( QUEUE_LOB_POOL_SIZE );
	}

	m_nCreateClustering = _spZero;
	m_nCheckClustering = _spZero;

}

/**
 * @brief     InitOfLOBClustering
 * @param     int nIndex LOB 큐 인덱스
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2018-01-16, 오후 9:56 
 * @warning   
 */
void CLOBClustering::InitOfLOBClustering( int nIndex )
{

	if( nIndex >= 0 && nIndex < TOTAL_ITEMS_OF_THREAT_NODE ) {
		m_pQueLOBDataPool[nIndex].Init( QUEUE_LOB_POOL_SIZE );
	}
	else {
		LogPrint( "InitOfLOBClustering() 함수의 인덱스[%d]가 잘못되어 LOB 버퍼 클리어를 수행하지 못합니다." , nIndex );
	}

}

/**
 * @brief     LOB 큐에 저장된 데이터를 교체한다.
 * @param     int nDestIndex 소스 큐 인덱스
 * @param     int nSrcIndex 목적지 큐 인덱스
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-02-16, 오후 2:16 
 * @warning   
 */
void CLOBClustering::AddLOBPool( int nDestIndex, int nSrcIndex )
{
	SELLOBDATA_MINIMIZE stLOBData;
	Queue<SELLOBDATA_MINIMIZE> *pSrcQueLOBDataPool, *pDestQueLOBDataPool;

	pSrcQueLOBDataPool = m_pQueLOBDataPool + nSrcIndex;
	pDestQueLOBDataPool = m_pQueLOBDataPool + nDestIndex;

	int qCount = pSrcQueLOBDataPool->Count();
	for( int i=0 ; i < qCount ; ++i ) {
		pSrcQueLOBDataPool->Pop( & stLOBData );

		pDestQueLOBDataPool->Push( stLOBData );
	}
	
}

/**
 * @brief     LOB 데이터를 LOB POOL에 삽입함. POOL이 꽉 차면 제일 오래된 LOB 데이터를 버린다.
 * @param     pSRxLOBDataGroup LOB 데이터 내용
 * @param     pSRxLOBData LOB 헤더
 * @param     pSELLOBDATA_EXT LOB 데이터의 확장영역의 데이터
 * @return    SELLOBDATA 포인터로 실제 저장할 LOB POOL의 포인터를 리턴
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-06-22, 오후 1:13 
 * @warning   
 */
SELLOBDATA_MINIMIZE *CLOBClustering::InsertLOBPool( int index, SRxLOBData *pSRxLOBData, UINT uiLOBID, bool bInit, bool bInsertLOB )
{
	SELLOBDATA_MINIMIZE *pLOBData=NULL;

	Queue<SELLOBDATA_MINIMIZE> *pQueLOBDataPool;

	if( bInsertLOB == true ) {
		pQueLOBDataPool = m_pQueLOBDataPool + index;

		// 큐 버퍼 초기화
		if( bInit == true ) {
				pQueLOBDataPool->Reset();
		}

		pLOBData = pQueLOBDataPool->PushAt();
		if( pLOBData != NULL ) { 
			// LOB POOL에 LOB 관련 정보 저장
			CopyLOBDataMinimizeFromLOBData( pLOBData, pSRxLOBData, uiLOBID );
		}
		else { //DTEC_Else
			pQueLOBDataPool->Pop( NULL );

			/*! \todo  버퍼가 풀일 때는 예전 것을 없애고 새것으로 추가한다.
					\author 조철희 (churlhee.jo@lignex1.com)
					\date 	2017-02-16 13:19:56
			*/
			pLOBData = pQueLOBDataPool->PushAt();
			CopyLOBDataMinimizeFromLOBData( pLOBData, pSRxLOBData, uiLOBID );

		}
	}

	return pLOBData;

}

/**
 * @brief     LOB 데이터로부터 클러스터링 데이터를 추출한다.
 * @param     SELLOBDATA_MINIMIZE * pLOBData
 * @param     SRxLOBDataGroup * pSRxLOBDataGroup
 * @param     UINT uiLOBID
 * @return    void
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-02-22, 오후 3:14 
 * @warning   
 */
void CLOBClustering::CopyLOBDataMinimizeFromLOBData( SELLOBDATA_MINIMIZE *pLOBData, SRxLOBData *pSRxLOBData, UINT uiLOBID )
{
	if( pLOBData != NULL ) {
        pLOBData->fMeanDOA = pSRxLOBData->fDOAMean;

		pLOBData->uiLOBID = uiLOBID;

		// 항공기 관련 정보
		//pLOBData->iRollAngle = pSRxLOBDataGroup->iRollAngle;
		//pLOBData->iPitchAngle = pSRxLOBDataGroup->iPitchAngle;
		//pLOBData->iHeadingAngle = pSRxLOBDataGroup->iHeadingAngle;
		//pLOBData->iAltitude = pSRxLOBDataGroup->iAltitude;	
        pLOBData->fRadarLatitude = pSRxLOBData->fRadarLatitude;
        pLOBData->fRadarLongitude = pSRxLOBData->fRadarLongitude;
	}

}

/**
 * @brief     LOB POOL 에 있는 데이터로부터 LOB 클러스터링을 수행한다.
 * @param     입력값 없음
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-06-22, 오후 12:51 
 * @warning   
 */
bool CLOBClustering::LOBClustering( int index, STR_CEDEOBID_INFO *pCEDEOBInfo )
{
	m_bCluster = false;

	m_pQueLOBData = m_pQueLOBDataPool + index;
	m_nLOB = m_pQueLOBData->Count();

	if( m_nLOB >= (int) GP_ENVI_VAR->GetEmmgNumOfMinLobToBeam() && m_nLOB < MAX_LOB_FOR_CLUSTERING ) {
        //DWORD dwTime = GetTickCount();

		// 0. LOB 클러스터링을 계산하기 위한 사전 데이터 할당
		m_nMaxOfIntersection = CalcIntersectionPoints( m_nLOB );

		// 0.1 클러스터링을 수행하기 위한 변수 정의
		// 1. 교차점 구하기
		CalculateIntersectionPoints();

		// 2. 교차점 제거
		FilteredIntersectionPoints();

		// 2. 위치 그룹화
		GroupOfIntersection();

		// 3. 최적의 LOB 그룹 결정
		m_bCluster = CalOptimalCluster( pCEDEOBInfo );

		++ m_nCheckClustering;

        //LogPrint("\n========================================== LOBClustering 시간 : %d ms", (int)((GetTickCount() - dwTime) / 1));

	}

	return m_bCluster;

}

//////////////////////////////////////////////////////////////////////
/*!
 * @brief     이 객체에 필요한 메모리를 할당받는다.
 * @return    void
 * @param     void
 * @version   0.0.1
 * @author    조철희(churlhee.jo@lignex1.com)
 * @date      2017-09-13 오후 7:14 
 * @warning   
 */
bool CLOBClustering::AllocMemory()
{
	unsigned int i;
	bool bRet=true;

	// 교차점 메모리 할당
	m_uiInterSect = CalcIntersectionPoints( QUEUE_LOB_POOL_SIZE );
	m_pIntersect = ( SELINTERSECTION * ) malloc( sizeof(SELINTERSECTION) * m_uiInterSect );
	if( m_pIntersect == NULL ) { //DTEC_NullPointCheck
		bRet = false;
	}

	m_pOptimalLOBID = ( int * ) malloc( sizeof(int) * QUEUE_LOB_POOL_SIZE );

	m_pCluster = ( STR_LOBCLUSTER * ) malloc( sizeof(STR_LOBCLUSTER) * m_uiInterSect );
	if( m_pCluster == NULL ) { //DTEC_NullPointCheck
		bRet = false;
	}
	else {
		for( i=0 ; i < m_uiInterSect ; ++i ) {
			// LOB 관리를 위해서 +2 개를 더한다.
			m_pCluster[i].pQueueIndex = ( unsigned int * ) malloc( sizeof(QueueIndex) * (UINT) ( m_uiInterSect + 2 ) );
			if( m_pCluster[i].pQueueIndex == NULL ) { //DTEC_NullPointCheck
				bRet = false;
			}
		}
	}

	m_VecLOBs.reserve( QUEUE_LOB_POOL_SIZE );

	return bRet;

}


//////////////////////////////////////////////////////////////////////
/*!
 * @brief     객체에 사용한 메모리를 해지한다.
 * @return    void
 * @param     void
 * @version   0.0.1
 * @author    조철희(churlhee.jo@lignex1.com)
 * @date      2017-09-13 오후 7:14 
 * @warning   
 */
void CLOBClustering::FreeMemory()
{
	int i;
	int iInterSect;

	iInterSect = CalcIntersectionPoints( QUEUE_LOB_POOL_SIZE );

	free( m_pOptimalLOBID );

	free( m_pIntersect );
	for( i=0 ; i < iInterSect ; ++i ) {
		free( m_pCluster[i].pQueueIndex );
	}
	free( m_pCluster );

}

/**
 * @brief     LOB POOl 에 있는 모든 LOB 들에 대해서 교차점을 구한다.
 * @param     입력값 업음
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-06-24, 오전 10:13 
 * @warning    
 */
void CLOBClustering::GroupOfIntersection()
{
	int i;
	STR_LOBCLUSTER *pCluster;

	// 초기 설정
	m_nClusters = 0;
	pCluster = m_pCluster;

	for( i=0 ; i < n_nTotalOfIntersection ; ++i ) {
		if( m_pIntersect[i].bEnable == true ) {
			CalClusterInfo( pCluster, m_pIntersect+i );
			if( pCluster->iCount >= (int) GP_ENVI_VAR->GetEmmgNumOfMinLobToBeam() ) { // && pCluster->iCount != (int) m_nLOB ) {
				//ShowCluster( pCluster );

				if( false == IsThereCluster( pCluster ) ) {
					++ m_nClusters;
					++ pCluster;
				}
			}
		}
	}

}

/**
 * @brief     클러스터 내에 이미 존재하는지를 검사한다.
 * @param     STR_LOBCLUSTER * pCluster
 * @return    bool
 * @return    성공시 true, 실패시 false
*/
bool CLOBClustering::IsThereCluster( STR_LOBCLUSTER *pCluster )
{
	int i, j;
	bool bRet=false;

	QueueIndex *pQueueIndex1, *pQueueIndex2;
	STR_LOBCLUSTER *pCompCluster;

	// 중복된 클러스터링 제거
	// qsort( m_pCluster, (size_t) m_nClusters, sizeof( STR_LOBCLUSTER ), incClusterCompare );

	pQueueIndex1 = m_pCluster->pQueueIndex;
	pCompCluster = & m_pCluster[0];
 	for( i=0 ; i < m_nClusters ; ++i ) {
		if( pCluster->iCount == pCompCluster->iCount ) {
			bRet = true;
			pQueueIndex2 = pCluster->pQueueIndex;
			for( j=0 ; j < pCompCluster->iCount ; ++j ) {
				if( pQueueIndex1[j] != pQueueIndex2[j] ) {
					bRet = false;
					break;
				}
			}

			if( bRet == true ) {
				break;
			}

		}

		++ pCompCluster;

 	}

	return bRet;

}

//////////////////////////////////////////////////////////////////////
/*!
 * @brief     클러스터 정보를 출력창으로 전시한다.
 * @return    void
 * @param     STR_LOBCLUSTER * pCluster 클러스터 데이터 정보
 * @version   0.0.1
 * @author    조철희(churlhee.jo@lignex1.com)
 * @date      2017-12-12 오후 2:58 
 * @warning   
 */
void CLOBClustering::ShowCluster( STR_LOBCLUSTER *pCluster )
{
	int i;
	SELLOBDATA_MINIMIZE *pLOBData;

	QueueIndex *pQueueIndex = pCluster->pQueueIndex;

	LogPrint( "\n 클러스터 정보 [%d개]; LOB" , pCluster->iCount );
	for( i=0 ; i < pCluster->iCount ; ++i ) {
		pLOBData = m_pQueLOBData->GetPointerByIndex( *pQueueIndex );

		LogPrint( "[%d]" , pLOBData->uiLOBID );

		++ pQueueIndex;
	}

}

/**
 * @brief     클러스터에 LOB 인덱스를 저장한다.
 * @param     STR_LOBCLUSTER * pCluster 클러스터 데이터 정보
 * @param     UINT nQueLOBDataIndex 클러스터 인덱스
 * @return    void
*/
void CLOBClustering::PushQueueIndex( STR_LOBCLUSTER *pCluster, UINT nQueLOBDataIndex )
{
	QueueIndex *pQueueIndex;

	pQueueIndex = & pCluster->pQueueIndex[pCluster->iCount];

	*pQueueIndex = nQueLOBDataIndex;
	++ pCluster->iCount;

}

//////////////////////////////////////////////////////////////////////
/*!
 * @brief     입력 클러스터링 정보의 LOB의 방위 범위를 계산한다.
 * @return    void
 * @param     STR_LOBCLUSTER * pCluster 클러스터 데이터 정보
 * @version   0.0.1
 * @author    조철희(churlhee.jo@lignex1.com)
 * @date      2017-09-14 오전 11:03 
 * @warning   
 */
void CLOBClustering::CalMaxDiffAoa( STR_LOBCLUSTER *pCluster )
{
	int i, iCount;
	float firstDOA;
	int iMaxAoa, iMinAoa;

	QueueIndex *pQueueIndex;
	SELLOBDATA_MINIMIZE *pLOBData;

	iCount = pCluster->iCount;

	pCluster->fMaxDiffAoa = 0.0;

	if( iCount != _spZero ) {
		//LogPrint( "\n CalMaxDiffAoa" );

		pQueueIndex = pCluster->pQueueIndex;

		pLOBData = m_pQueLOBData->GetPointerByIndex( *pQueueIndex );
		firstDOA = pLOBData->fMeanDOA;
		iMaxAoa = (int) ( firstDOA + 0.5 );
		iMinAoa = (int) ( firstDOA - 0.5 );
		++ pQueueIndex;
		for( i=1 ; i < iCount ; ++i ) {
			pLOBData = m_pQueLOBData->GetPointerByIndex( *pQueueIndex );

			// iDiffAoa = _abs( pLOBData->iMeanDOA - pLOBData2->iMeanDOA );

			iMaxAoa = (int) ( ( 360.0 + firstDOA + pLOBData->fMeanDOA + 0.5 ) ) % 360;
			iMinAoa = (int) ( ( 360.0 + firstDOA + pLOBData->fMeanDOA - 0.5 ) ) % 360;

			//LogPrint( "\n Low[%d], High[%d]" , iMinAoa, iMaxAoa );

			++ pQueueIndex;
		}

		pCluster->fMaxDiffAoa = (float) ( iMaxAoa - iMinAoa );

	}

}

/**
 * @brief     하나의 크러스터링 내에서 중김값, 편차 등을 계산한다.
 * @param     pCluster 계산할 클러스터링 포인터
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-06-28, 오전 11:56 
 * @warning   
 */
void CLOBClustering::CalClusterInfo( STR_LOBCLUSTER *pCluster, SELINTERSECTION *pRefInterSect )
{
	int i;

	bool bFirst=true;

	float fTheta, fDiff;
	SELINTERSECTION *pIntersect;

	QueueIndex *pQueueIndex;

	SELLOBDATA_MINIMIZE *pLOBData;

	pQueueIndex = pCluster->pQueueIndex;

	pIntersect = m_pIntersect;

	pCluster->iCount = 0;

	//LogPrint( "\n ###### 클러스터링 그룹화[%.4f/%.4f]" , pRefInterSect->fLatitude, pRefInterSect->fLongitude );
	for( i=0 ; i < m_nLOB ; ++i ) {
		pLOBData = m_pQueLOBData->GetPointerByIndex( (UINT) i );

		// fDist = CalDistance( pRefInterSect, pIntersect );
        fTheta = (float) ST_IMA->GCAzimuth( (double) pLOBData->fRadarLatitude, (double) pLOBData->fRadarLongitude, pRefInterSect->fLatitude, pRefInterSect->fLongitude );
		fDiff = _abs( (float) fTheta - pLOBData->fMeanDOA );

		//LogPrint( "D-DOA[%d, %.3f] " , pLOBData->iLOBID, fDiff/10. );

		if( fDiff <= (GP_MGR_PARAM->GetEffectiveDOADiff2()) ) {
		//if( fDiff/10. <= GP_MGR_TEST_PARAM->GetEffectiveDOADiff3() ) {
			// SELLOBDATA_MINIMIZE *pLOBData1, *pLOBData2;
			PushQueueIndex( pCluster, (UINT) i );

		}
	}

	// LOB 집합에서 제일 큰 방향 각도 계산
	CalMaxDiffAoa( pCluster );

}

/**
 * @brief     N 개의 라인에서 최대 교차점 갯수를 구한다.
 * @param     nLines LOB 라인 갯수
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-06-23, 오전 10:13 
 * @warning   
 */
unsigned int CLOBClustering::CalcIntersectionPoints( int nLines )
{
	return ( nLines * ( nLines - 1 ) ) / 2;
}

/**
 * @brief     LOB 들로부터 교차점을 저장한다.
 * @param     입력값 업음
 * @return    리턴값 없음
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-06-22, 오후 1:29 
 * @warning   
 */
void CLOBClustering::CalculateIntersectionPoints()
{
 	int i, j;
 	SELLOBDATA_MINIMIZE *pLOBData1, *pLOBData2;

 	SELINTERSECTION *pIntersect;

	n_nTotalOfIntersection = 0;
	pIntersect = m_pIntersect;

	for( i=0 ; i < m_nLOB ; ++i ) { //#FA_C_PotentialUnboundedLoop_T2
		pLOBData1 = m_pQueLOBData->GetPointerByIndex( (UINT) i );
		for( j=i+1 ; j < m_nLOB ; ++j ) {
			pLOBData2 = m_pQueLOBData->GetPointerByIndex( (UINT) j );

			if( true == CalIntersectionBetweenLOB( pIntersect, pLOBData1, pLOBData2 ) ) {
				pIntersect->nQueueIndex1 = (UINT) i;
				pIntersect->nQueueIndex2 = (UINT) j;

				//LogPrint( "\n [%d, %d]의 교차점 위/경도 : %.4f, %.4f" , pLOBData1->iLOBID, pLOBData2->iLOBID, pIntersect->fLatitude, pIntersect->fLongitude );

				++ pIntersect;

				++ n_nTotalOfIntersection;
			}
		}
	}

}

//////////////////////////////////////////////////////////////////////
/*!
 * @brief     교차점들에 대해서 무효한 교차점들을 제거한다.
 * @return    void
 * @param     void
 * @version   0.0.1
 * @author    조철희(churlhee.jo@lignex1.com)
 * @date      2017-09-14 오전 11:51 
 * @warning   
 */
void CLOBClustering::FilteredIntersectionPoints()
{
	int i;

	float fDiff, fDiff2, fMaxDist=0, fThresholdDist;
    float fLatitude, fLongitude;

	SELLOBDATA_MINIMIZE *pLOBData;
	SELINTERSECTION *pIntersect;

	pIntersect = m_pIntersect;

	// 첫번째 항공기에서 교차점 간의 거리가 가장 큰 거리의 일정 값 이하는 모든 교차점은 제거한다.
	pLOBData = m_pQueLOBData->GetPointerByIndex( pIntersect->nQueueIndex1 );

    fLatitude = pLOBData->fRadarLatitude;
    fLongitude = pLOBData->fRadarLongitude;
	for( i=0 ; i < n_nTotalOfIntersection ; ++i ) {
        fDiff = fLatitude - pIntersect->fLatitude;
		fDiff2 = fDiff * fDiff;
        fDiff = fLongitude - pIntersect->fLongitude;
		fDiff2 += ( fDiff * fDiff );

		pIntersect->fDist = sqrt( fDiff2 );
		fMaxDist = max( fMaxDist, pIntersect->fDist );

		++ pIntersect;
	}

	m_nEffectOfIntersection = 0;
	pIntersect = m_pIntersect;
	//fThresholdDist = FMUL( fMaxDist, RATIO_OF_MAXDISTANCE );
	fThresholdDist = (float) 0.1;
	for( i=0 ; i < n_nTotalOfIntersection ; ++i, ++ pIntersect ) {
		if( pIntersect->fDist >= fThresholdDist ) {
			pIntersect->bEnable = true;
			++ m_nEffectOfIntersection;
			continue;
		}
		pIntersect->bEnable = false;
	}

}

/**
 * @brief     두 LOB 간의 거리를 계산함
 * @param     pRes 교차점을 저장할 포인터
 * @param     pLOBData1 1번 LOB
 * @param     pLOBData2 2번 LOB
 * @return    교차점을 구할수 있으면 true 없으면 false 로 리턴
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-06-23, 오후 2:31 
 * @warning   
 */
bool CLOBClustering::CalIntersectionBetweenLOB( SELINTERSECTION *pRes, SELLOBDATA_MINIMIZE *pLOBData1, SELLOBDATA_MINIMIZE *pLOBData2 )
{
	bool bRet=false;

	double dx, dy, dDist;

	double fDistAircraftLongitude, fDistAircraftLatitude;
	double fSquareOfSinLat, fSquareOfSinLong;
	double fSinLat, fSinLong;

	double fBearingOf12, fBearingOf21, fBearingOf1, fBearingOf2;

	double fDistAngular12, fDistAngular3;

	double fAlpha1, fAlpha2, fAlpha3;
	double fCosOfAlpha1, fCosOfAlpha2, fCosOfAlpha3;
	double fSinOfAlpha1, fSinOfAlpha2;

	double fDiffLong;

	// LOB 각도 설정
	fBearingOf1 = ( deg2rad * pLOBData1->fMeanDOA ); // ALGLE2MATH( pLOBData1->iMeanDOA );
	fBearingOf2 = ( deg2rad * pLOBData2->fMeanDOA ); // ALGLE2MATH( pLOBData2->iMeanDOA );

	// 두 지점간의 각도 거리 계산
    fDistAircraftLongitude = deg2rad * ( pLOBData2->fRadarLongitude - pLOBData1->fRadarLongitude ) / 2.;
    fDistAircraftLatitude = deg2rad * ( pLOBData2->fRadarLatitude - pLOBData1->fRadarLatitude ) / 2.;
	fSinLat = sin( fDistAircraftLatitude );
	fSquareOfSinLat = ( fSinLat * fSinLat );
	fSinLong = sin( fDistAircraftLongitude );
	fSquareOfSinLong = ( fSinLong * fSinLong );
    fDistAngular12 = 2. * asin( sqrt( ( fSquareOfSinLat + cos( deg2rad * pLOBData1->fRadarLatitude ) * cos( deg2rad * pLOBData2->fRadarLatitude ) * fSquareOfSinLong ) ) );
	if( Is_FZero( (float) fDistAngular12 ) == false ) {
		// 두 지점간의 초기 방위각 계산
        fBearingOf12 = acos( ( sin( deg2rad * pLOBData2->fRadarLatitude ) - sin( deg2rad * pLOBData1->fRadarLatitude ) * cos( fDistAngular12 ) ) / ( sin( fDistAngular12 ) * cos( deg2rad * pLOBData1->fRadarLatitude ) ) );
        fBearingOf21 = acos( ( sin( deg2rad * pLOBData1->fRadarLatitude ) - sin( deg2rad * pLOBData2->fRadarLatitude ) * cos( fDistAngular12 ) ) / ( sin( fDistAngular12 ) * cos( deg2rad * pLOBData2->fRadarLatitude ) ) );

		if( sin( fDistAircraftLongitude ) > 0 ) {
			fBearingOf21 = 2. * M_PI - fBearingOf21; 
		}
		else {
			fBearingOf12 = 2. * M_PI - fBearingOf12;
		}

		// 방위차 계산(지점1,지점2,방위)
		fAlpha1 = fBearingOf1 - fBearingOf12;			//fmod( ( fBearingOf1 - fBearingOf12 ) + M_PI, 2 * M_PI ) - M_PI;
		fAlpha2 = fBearingOf21 - fBearingOf2;			//fmod( ( fBearingOf21 - fBearingOf2 ) + M_PI, 2 * M_PI ) - M_PI;

		fSinOfAlpha1 = sin( fAlpha1 );
		fSinOfAlpha2 = sin( fAlpha2 );
		fCosOfAlpha1 = cos( fAlpha1 );		
		fCosOfAlpha2 = cos( fAlpha2 );	//#FA_C_IgnoredReturnValue_T2
		//if( ( fSinOfAlpha1 != 0 || fSinOfAlpha2 != 0 ) || ( fSinOfAlpha1 * fSinOfAlpha2 > 0 ) ) {
		if( Is_DNotZero( fSinOfAlpha1 ) == true || Is_DNotZero( fSinOfAlpha2 ) == true || ( fSinOfAlpha1 * fSinOfAlpha2 > 0 ) ) {
			fAlpha3 = acos( -fCosOfAlpha1 * fCosOfAlpha2 + fSinOfAlpha1 * fSinOfAlpha2 * cos( fDistAngular12 ) );
			fCosOfAlpha3 = cos( fAlpha3 );

			// 각도 거리 계산
			fDistAngular3 = atan2( sin( fDistAngular12 ) * fSinOfAlpha1 * fSinOfAlpha2, fCosOfAlpha2 + fCosOfAlpha1 * fCosOfAlpha3 );

			// 교차점 계산
			double dLatitude, dLongitude;
            dLatitude = asin( sin( deg2rad * pLOBData1->fRadarLatitude ) * cos( fDistAngular3 ) + cos( deg2rad * pLOBData1->fRadarLatitude ) * sin( fDistAngular3 ) * cos( fBearingOf1 ) );
            fDiffLong = atan2( sin( fBearingOf1 ) * sin( fDistAngular3 ) * cos( deg2rad * pLOBData1->fRadarLatitude ), cos( fDistAngular3 ) - ( sin( deg2rad * pLOBData1->fRadarLatitude ) * sin( dLatitude ) ) );
            dLongitude = ( pLOBData1->fRadarLongitude + ( fDiffLong * rad2deg ) );
			dLatitude = ( rad2deg * dLatitude );

			pRes->fLatitude = (float) dLatitude;
			pRes->fLongitude = (float) dLongitude;

			if( pRes->fLatitude < 0 || pRes->fLongitude < 0 ) {
				bRet = false;
			}

			//LogPrint( "\n [%d, %d]의 교차점 위/경도 : %.4f, %.4f" , pLOBData1->iLOBID, pLOBData2->iLOBID, pRes->fLatitude, pRes->fLongitude );
			// 대략적인 거리 산출
            dx = ( pRes->fLongitude - pLOBData1->fRadarLongitude ) * KM_PER_DEGREE_FOR_LONGITUDE;
            dy = ( pRes->fLatitude - pLOBData1->fRadarLatitude ) * KM_PER_DEGREE_FOR_LATITUDE;

			dDist = sqrt( dx*dx + dy*dy );

			// 항공기에서 너무 가깝거나 너무 먼 것은 제외한다.
			if( dDist > _LIMIT_OF_MAX_RANGE /* || dDist < _LIMIT_OF_MIN_RANGE */ ) {
				bRet = false;
			}
			else {
				bRet = true;
			}
		}
	}

	return bRet;
}

/**
 * @brief     최적의 클러스터링을 결정한다.
 * @param     bool bProcess
 * @return    STR_LOBCLUSTER *
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-02-20, 오후 6:17 
 * @warning   
 */
bool CLOBClustering::CalOptimalCluster( STR_CEDEOBID_INFO *pCEDEOBInfo )
{
	int i, j;
	bool bRet=false;

	//STR_POSITION_ESTIMATION peInfo;

	int iCount=0;
	float fMaxDiffAoa=0.;

	STR_LOBCLUSTER *pCluster=NULL;
	m_nOptimalCluster = 0;
    memset( m_pOptimalCluster, 0, sizeof(m_pOptimalCluster) );

	if( m_nClusters >= _spOne ) {
		pCluster = m_pCluster;

		// 1. 최적의 클러스터링 산정 : 최대 방위값으로 설정
		for( i=0 ; i < m_nClusters ; ++i ) { //#FA_C_PotentialUnboundedLoop_T2
			if( ( pCluster->iCount > iCount ) || 
				  ( ( pCluster->iCount == iCount ) && ( pCluster->fMaxDiffAoa > fMaxDiffAoa ) ) ) {
				m_pOptimalCluster[0] = pCluster;

 				for( j=1 ; j < MAX_OPTIMAL_CLUSTERS ; ++j ) {
 					m_pOptimalCluster[j] = m_pOptimalCluster[j-1];
 				}
				++ m_nOptimalCluster;

				fMaxDiffAoa = pCluster->fMaxDiffAoa;
				iCount = pCluster->iCount;
			}
			++ pCluster;

		}

		// 최적 개수를 상한으로 결정
		m_nOptimalCluster = min( m_nOptimalCluster, MAX_OPTIMAL_CLUSTERS );

		// 3. 최적의 LOB 번호 얻기
		bRet = CheckOptimalLOBID( pCEDEOBInfo );

		// 클러스터링 결과가 동일하지 않을 때만 처리한다.
		if( bRet == true && m_pOptimalCluster[0]->iCount < m_nLOB ) {
			bRet = true;
		}
		else {
			bRet = false;
		}
	}

	return bRet;

}

//////////////////////////////////////////////////////////////////////
/*!
 * @brief     최적의 클러스터 정보를 찾아 낸다.
 * @return    void
 * @param     void
 * @version   0.0.1
 * @author    조철희(churlhee.jo@lignex1.com)
 * @date      2017-12-12 오후 2:36 
 * @warning   
 */
bool CLOBClustering::CheckOptimalLOBID( STR_CEDEOBID_INFO *pCEDEOBInfo )
{
	int i, j;
	bool bRet=false;

	QueueIndex *pQueueIndex;
	SELLOBDATA_MINIMIZE *pLOBData;

	STR_POSITION_ESTIMATION peInfo;

	//SELDBEnvVarIdnf *pstDBEnvVarIdnf;

	STR_POSESTDATA stPosEstData;
	SPosEstData stResPosEstData;

	STR_LOBCLUSTER *pOptimalCluster;

	//GP_MGR_ENVI_VAR->GetIdnfWeightAndMargin( stDBEnvVarIdnf );

	pOptimalCluster = m_pOptimalCluster[0];
	for( i=0 ; i < m_nOptimalCluster ; ++i ) {
		if( pOptimalCluster == NULL ) {
			continue;
		}

		pQueueIndex = pOptimalCluster->pQueueIndex;

		ClearOptimalLOBID();
		ClearPEData();

		for( j=0 ; j < pOptimalCluster->iCount ; ++j ) {
			//if( *pQueueIndex < m_nClusetrCount ) {
			pLOBData = m_pQueLOBData->GetPointerByIndex( *pQueueIndex );
			if( pLOBData != NULL ) {
				AddOptimalLOBID( pLOBData->uiLOBID );
				AddPEData( pLOBData );

			}

			++ pQueueIndex;
		}

		// 2. 위치 산출을 수행하여 반경 체크해서 리턴한다.
		ST_PEA->RunPositionEstimation( & peInfo, NULL, & m_VecLOBs );
		//LogPrint( "\n [%d] %.2f/%.2f" , i, peInfo.fLatitude, peInfo.fLongitude );
		ShowCluster( pOptimalCluster );

		// 3. EOB 식별하여 EOB 메칭이 안된 클러스터링은 실패로 처리 한다.
		stPosEstData.dEstLatitude = (double) peInfo.fLatitude;
		stPosEstData.dEstLongitude = (double) peInfo.fLongitude;
		stResPosEstData.dCEP = (double) peInfo.fCEP;
		//stResPosEstData.nRadarIndex = pCEDEOBInfo->nRadarIndex[0];
		// 위치 산출 수행함.
		//m_theIdentifyAlg.IdentifyPosition( pCEDEOBInfo, & stPosEstData, & stResPosEstData, stDBEnvVarIdnf.eCEDDefaultLibType, stDBEnvVarIdnf.eEOBDefaultLibType, GP_MGR_TEST_PARAM->GetEffectiveDistOfEOB() );

		// 4. 기성인 것만 LOB 클러스터링을 시도하게 함.
		if( stResPosEstData.nRadarIndex != _spZero ) { // || ST_OCM->IsSimulatorMode() == true ) {
 			if( peInfo.fCEP == 0.0 || peInfo.fCEP > GP_ENVI_VAR->GetEobIndfRangeMeters() ) {
				LogPrint( "\n CEP[%f m] 반경이 벗어 났습니다!" , peInfo.fCEP );
 				bRet = false;
				continue;
 			}
			else {
				bRet = ReMakeOptimalCluster( & peInfo, i );

				ST_PEA->RunPositionEstimation( & peInfo, NULL, & m_VecLOBs );
				// 장축/단축 비교를 추가 
				if( bRet == true && peInfo.fCEP != 0. && \
					( peInfo.fCEP <= GP_ENVI_VAR->GetEobIndfRangeMeters() ) || ( peInfo.fMajorAxis/2 <= MAJOR_MAX_LIMIT && peInfo.fMinorAxis/2 <= MINOR_MAX_LIMIT ) ) {
					LogPrint( "\n CEP[%d m] 반장축[%f m] 반단축[%f m] 반경 안에 들었습니다!" , peInfo.fCEP, peInfo.fMajorAxis/2, peInfo.fMinorAxis/2 );
					bRet = true;
					break;
				}
				else {
					bRet = false;
					LogPrint( "\n 2차 그룹으로 CEP[%f m] 반경이 벗어 났습니다!" , peInfo.fCEP );
					continue;
				}
			}
		}

		++ pOptimalCluster;
	}

	return bRet;

}

//////////////////////////////////////////////////////////////////////
/*!
 * @brief     LOB 데이터를 클러스터링 할 저장소(큐)에 입력한다.
 * @return    void
 * @param     SELLOBDATA_MINIMIZE * pLOBData 입력할 LOB 데이터
 * @version   0.0.1
 * @author    조철희(churlhee.jo@lignex1.com)
 * @date      2017-12-13 오후 4:01 
 * @warning   
 */
void CLOBClustering::AddPEData( SELLOBDATA_MINIMIZE *pLOBData )
{
	STR_LOBS stLOBs;

	stLOBs.fDoa = pLOBData->fMeanDOA;
    stLOBs.fLatitude = (float) pLOBData->fRadarLatitude;
    stLOBs.fLongitude = (float) pLOBData->fRadarLongitude;
	stLOBs.uiLOBID = pLOBData->uiLOBID;
	m_VecLOBs.push_back( stLOBs );

}

//////////////////////////////////////////////////////////////////////
/*!
 * @brief     클러스터링 정보를 큐에 저장한다.
 * @return    void
 * @param     int iLOBID 입력할 LOB 번호
 * @version   0.0.1
 * @author    조철희(churlhee.jo@lignex1.com)
 * @date      2017-12-13 오후 12:32 
 * @warning   
 */
void CLOBClustering::AddOptimalLOBID( UINT uiLOBID )
{
	if( std::find( m_vecOptimalLODID.begin(), m_vecOptimalLODID.end(), uiLOBID ) == m_vecOptimalLODID.end() ) {
		m_vecOptimalLODID.push_back( uiLOBID );
	}

}

//////////////////////////////////////////////////////////////////////
/*!
 * @brief     최적의 클러스터링 LOB 번호를 리턴한다.
 * @return    bool
 * @param     int iLOBID
 * @version   0.0.1
 * @author    조철희(churlhee.jo@lignex1.com)
 * @date      2017-12-13 오후 12:34 
 * @warning   
 */
bool CLOBClustering::IsThereOptimalLOBID( int iLOBID )
{
	bool bRet=true;

	if( std::find( m_vecOptimalLODID.begin(), m_vecOptimalLODID.end(), iLOBID ) == m_vecOptimalLODID.end() ) {
		bRet = false;
	}

	return bRet;

}

//////////////////////////////////////////////////////////////////////
/*!
 * @brief     클러스터링할 빔 제원 정보를 저장한다.
 * @return    void
 * @param     UINT uiABTDID
 * @param     int iLOBPoolIndex
 * @version   0.0.1
 * @author    조철희(churlhee.jo@lignex1.com)
 * @date      2017-12-12 오후 10:38 
 * @warning   
 */
void CLOBClustering::UpdateClusterInfo( UINT uiAETID, UINT uiABTID, int iLOBPoolIndex )
{
	m_iLOBPoolIndex = iLOBPoolIndex;
	m_uiABTID = uiABTID;
	m_uiAETID = uiAETID;

}

//////////////////////////////////////////////////////////////////////
/*!
 * @brief     최적의 클러서링 정보에서 검증을 통하여 최적 클러스링 정보를 추출한다.
 * @return    bool
 * @param     std::vector<STR_LOBS>* pVecLOBs
 * @param     STR_POSITION_ESTIMATION * pPEInfo
 * @version   0.0.1
 * @author    조철희(churlhee.jo@lignex1.com)
 * @date      2017-12-13 오후 4:19 
 * @warning   
 */
bool CLOBClustering::ReMakeOptimalCluster( STR_POSITION_ESTIMATION *pPEInfo, int nOptimalIndex )
{
	int i;
	bool bRet=false;
	float fTheta;
	int iCoGetEffectiveDOADiff1 = 0;
	int iCoGetEffectiveDOADiff2 = 0;

	QueueIndex *pQueueIndex;

	SELLOBDATA_MINIMIZE *pLOBData=NULL;

	ClearOptimalLOBID();
	ClearPEData();

	pQueueIndex = m_pOptimalCluster[nOptimalIndex]->pQueueIndex;
	m_pOptimalCluster[nOptimalIndex]->iCount = _spZero;

	// 전체 LOB에 대해서 위치 산출을 기준으로 그룹화를 재수행한다.
	//LogPrint( "\n 최적의 LOB 번호 계산하기"  );
	for( i=0 ; i < m_pQueLOBData->Count() ; ++i ) { //#FA_C_PotentialUnboundedLoop_T2
		pLOBData = m_pQueLOBData->GetPointerByIndex( (UINT) i );

        fTheta = (float) ST_IMA->GCAzimuth( pLOBData->fRadarLatitude, pLOBData->fRadarLongitude, (double) pPEInfo->fLatitude, (double) pPEInfo->fLongitude );
		if( TRUE == CompAoaDiff( fTheta, pLOBData->fMeanDOA, GP_MGR_PARAM->GetEffectiveDOADiff2() ) ) {
			AddOptimalLOBID( pLOBData->uiLOBID );

			AddPEData( pLOBData );

			//LogPrint( "\n %2d [%d]" , i, pLOBData->iLOBID );

			++ iCoGetEffectiveDOADiff2;
			*pQueueIndex = (UINT) i;
			++ pQueueIndex;

			++ m_pOptimalCluster[nOptimalIndex]->iCount;
		}

		if( TRUE == CompAoaDiff( fTheta, pLOBData->fMeanDOA, GP_MGR_PARAM->GetEffectiveDOADiff1() ) ) { 
			++ iCoGetEffectiveDOADiff1;
		}

	}

// 	float x=DOADIFF_RATIO1_BY_RATIO2;		// 0.66
// 	if( iCoGetEffectiveDOADiff2 >= (int) GP_MGR_ENVI_VAR->GetEmmgNumOfMinLobToBeam() && UMUL( iCoGetEffectiveDOADiff1, 0.66 ) <= (UINT) iCoGetEffectiveDOADiff1 ) {
// 		//m_pOptimalCluster[nOptimalIndex]->iCount = iCoGetEffectiveDOADiff1;
// 		bRet = true;
// 	}

	if( UDIV( iCoGetEffectiveDOADiff1 * 100, m_pOptimalCluster[nOptimalIndex]->iCount ) >= DOADIFF_RATIO1 &&
			UDIV( iCoGetEffectiveDOADiff2 * 100, m_pOptimalCluster[nOptimalIndex]->iCount ) >= DOADIFF_RATIO2 ) {
		bRet = true;
	}

	return bRet;
}

