// LOBClustering.h: CLOBClustering 헤더파일
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOBCLUSTERING_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)
#define AFX_IF2PDW_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Stack.h"

#include "../../OFP/EmitterMerge/PositionEstimationAlg.h"
#include "ELEmitterDataType.h"

#include "../Identify/Identify.h"
#include "../Identify/ELUtil.h"


// LOB를 보관하기 위한 버퍼 크기
#define QUEUE_LOB_POOL_SIZE														(100)	

// 최대 교차점 크기
#define	MAX_INTERSECTIONS															( (QUEUE_LOB_POOL_SIZE * ( QUEUE_LOB_POOL_SIZE - 1 ) ) / 2 )

// 항공기 헤딩을 수식 방위로 변환
#define ALGLE2MATH(A)																	((-A+900)/10.)
#define RADIAN2DEGREE(A)															((A*180.)/M_PI)
#define DEGREE2RADIAN(A)															((A*M_PI)/180.)

//
#define _LIMIT_OF_MAX_RANGE														(500.)																						// 최대 거리 정의
#define _LIMIT_OF_MAX_RANGE_FOR_DEGREE								(_LIMIT_OF_MAX_RANGE/KM_PER_DEGREE_FOR_LATITUDE)	// 최대 경도 차 정의

//#define _LIMIT_OF_MIN_RANGE														(1.)																						// 최소 거리 정의
#define _LIMIT_OF_MIN_RANGE_FOR_DEGREE								(_LIMIT_OF_MIN_RANGE/KM_PER_DEGREE_FOR_LATITUDE)	// 최대 경도 차 정의

//////////////////////////////////////////////////////////////////////////
// 클러스터링 정의
// 클러스터링 반복 횟수
//#define	NUMBER_OF_ITERATIONS													(10)

// 클러스터링 분리하기 위한 분산 정의
//#define MAXIMUM_STANDARD_DEVIATION										(0.03)			// [deg]

// 분산하기 위한 벡터 값 정의 - 미사용
//#define SPLIT_RATIO																		(0.6)

// 빔의 유효성 판단 임계값 (CheckValidityByAllLOB)
#define POWER_DIFF_OF_LOB_DOA													(DELTA_DEGREE_BT_LOB_AND_POINT*10)				// 단위: 0.1도

//#define MIN_LOB_FOR_CLUSTERING												(3)
#define MAX_LOB_FOR_CLUSTERING												(30)

//#define MAHALONOBIS_CONSTANT													(0.2) //(3.841)

// 항공기와 교차점간의 임계값을 계산하기 위한 율
#define RATIO_OF_MAXDISTANCE													(0.2)

// 클러스터링 확인 시 장축 최대 거리
#define MAJOR_MAX_LIMIT																(100000)				// 단위 : m

// 클러스터링 확인 시 단축 최대 거리
#define MINOR_MAX_LIMIT																(4000)					// 단위 : m

#define MAX_OPTIMAL_CLUSTERS													(3)							// 1보다는 큰 값으로 설정해야 함.

typedef unsigned int QueueIndex;


/**
 * @typedef   SELLOBDATA
 * @brief     LOB 목록을 큐로 관리하기 위한 구조체 정의
 * @author    조철희 (churlhee.jo@lignex1.com)
 */
typedef struct {
	SRxLOBData stELLOBData;
	SRxLOBHeader stELLOBHeader;

	//SELLOBDATA_EXT stELLOBDataExt;

} SELLOBDATA;

typedef struct  {
	// LOB 제원 정보
	float	fMeanDOA;			// [1.0 도]
	unsigned int uiLOBID;

	double dRadarCollectionLatitude;
	double dRadarCollectionLongitude;	

} SELLOBDATA_MINIMIZE ;

/**
 * @typedef   SELINTERSECTION
 * @brief     교차점 구조체 정의로 교차점 정보와 LOB 번호로 구성.
 * @author    조철희 (churlhee.jo@lignex1.com)
 */
typedef struct {
	// 교차점 정보, 단위는 degree.
	float fLongitude;
	float fLatitude;

	// LOB 번호
	QueueIndex nQueueIndex1;
	QueueIndex nQueueIndex2;

	bool bEnable;

	// 특정 항공기에서 교차점간의 거리
	float fDist;

} SELINTERSECTION;

typedef struct {
	float fx;
	float fy;

} STR_XYCOORDINATE ;

/**
 * @typedef   STR_LOBCLUSTER
 * @brief     단일 그룹화 정보로 그룹화 인덱스, 총 갯수, 중심값, 평균값, 편차값
 * @author    조철희 (churlhee.jo@lignex1.com)
 */
typedef struct {
	int iCount;
	QueueIndex *pQueueIndex;

	float fMaxDiffAoa;

} STR_LOBCLUSTER ;

typedef struct {
	int iCEP;
	int nLOB;

} STR_LOBCLUSTER_EXT ;

// GetEffectiveDOADiff1() 유효 백분율
#define DOADIFF_RATIO1																(60)		// 단위: 백분율

// GetEffectiveDOADiff2() 유효 백분율
#define DOADIFF_RATIO2																(90)		// 단위: 백분율

#define DOADIFF_RATIO1_BY_RATIO2											( FDIV( ( DOADIFF_RATIO1 * DOADIFF_RATIO2 ), 10000. ) )


/**
 * 
 * @class     CLOBClustering
 * @brief     
 * (1)　클래스 설명
 *  - LOB들간의 클로스터링 알고리즘을 사용하여 LOB들을 분류를 수행한다.
 * 
 * (2)　설계결정사항
 *  - 분류가 결정되면 이전 LOB 테이블에 저장된 LOB, 빔 번호를 업데이트 한다.
 * 
 * (3)　제한 및 예외처리
 *  - 해당사항 없음
 * 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-07-19, 오후 2:58 
 * @warning   
 */
class CLOBClustering
{
protected:
	int m_iInterSect;																///< 교차점 개수
	//UINT m_nClusetrCount;														///< 클러스터링 개수

	std::vector<STR_LOBS> m_VecLOBs;								///< LOB 데이터 저장소

	//CELSignalIdentifyAlg m_theIdentifyAlg;					///< CED/EOb 신호 식별 객체

	bool m_bCluster;										///<	최적의 클러스터 수행 여부를 플레그
	bool m_bIsSimulator;								///<  시뮬레이션 모드시 플레그 값

	UINT m_nCreateClustering;						///<	클러스터링 성공 개수
	UINT m_nCheckClustering;						///<	클러스터링 전체 시도 횟수

	UINT m_uiAETID;											///<	LOB 클러스터링 하기 위한 방사체 번호
	UINT m_uiABTID;											///<	LOB 클러스터링 하기 위한 빔 번호
	int m_iLOBPoolIndex;								///<	큐 인덱스

	vector<UINT> m_vecOptimalLODID;			///<  최적의 LOB 데이터 번호
	int m_nOptimalLOBID;								///<	최적의 클러스터에서 LOB 개수
	int *m_pOptimalLOBID;								///<	최적의 클러스터에서 LOB 번호 그룹

	// LOB 클러스터링을 하기 위한 저장소
	Queue<SELLOBDATA_MINIMIZE> *m_pQueLOBDataPool;			///<  LOB POOL 데이터 저장소

	//////////////////////////////////////////////////////////////////////////
	// 멤버 함수에서 클러스터링을 계산하기 위한 대상 큐 포인터
	Queue<SELLOBDATA_MINIMIZE> *m_pQueLOBData;					///<  클러스터링을 계산하기 위한 포인터

	int m_nLOB;													///<  LOB 갯수

	// 교처점 관련 변수
	int n_nTotalOfIntersection;					///<  교차점 갯수
	int m_nEffectOfIntersection;				///<  교차점 중에서 유효한 교차점 갯수
	int m_nMaxOfIntersection;						///<	LOB에 따른 최대 교차점 갯수
	SELINTERSECTION *m_pIntersect;			///<	교차점 저장소 포인터

	// 그룹화 관련 변수
	int m_nClusters;										///<  클러스터링 갯수
	STR_LOBCLUSTER *m_pCluster;						///<  클러스터링을 계산하기 위한 저장소

	int m_nOptimalCluster;							///<  최적 클러스터링 개수
	STR_LOBCLUSTER *m_pOptimalCluster[MAX_OPTIMAL_CLUSTERS];			///<  최적 클러스터링 저장소

private:
	bool CheckOptimalLOBID( STR_CEDEOBID_INFO *pCEDEOBInfo );
	void AddOptimalLOBID( UINT uiLOBID );

	void ShowCluster( STR_LOBCLUSTER *pCluster );

	bool AllocMemory();
	void FreeMemory();
	void PushQueueIndex( STR_LOBCLUSTER *pCluster, UINT nQueLOBDataIndex );
	void CalMaxDiffAoa( STR_LOBCLUSTER *pCluster );

	// 교차점 구하기
	int CalcIntersectionPoints( int nLines );
	bool CalIntersectionBetweenLOB( SELINTERSECTION *pRes, SELLOBDATA_MINIMIZE *pLOBData1, SELLOBDATA_MINIMIZE *pLOBData2 );
	void GroupOfIntersection();
	bool IsThereCluster( STR_LOBCLUSTER *pCluster );

	inline void ClearOptimalLOBID() { 
		m_vecOptimalLODID.clear(); 
		m_nOptimalLOBID=0; 
	};
	inline void ClearPEData() { m_VecLOBs.clear(); };

	void AddPEData( SELLOBDATA_MINIMIZE *pLOBData );

public:
	CLOBClustering();
	virtual ~CLOBClustering();

	void InitOfLOBClustering();
	void InitOfLOBClustering( int nIndex );

	SELLOBDATA_MINIMIZE *InsertLOBPool( int index, SRxLOBData *pSRxLOBData, UINT uiLOBID, bool bInit=false, bool bInsertLOB=true );
	void CopyLOBDataMinimizeFromLOBData( SELLOBDATA_MINIMIZE *pLOBData, SRxLOBData *pSRxLOBData, UINT uiLOBID );
	void AddLOBPool( int nDestIndex, int nSrcIndex );

	bool LOBClustering( int index, STR_CEDEOBID_INFO *pCEDEOBInfo );
	void CalculateIntersectionPoints();

	inline bool IsThereClustering() { return m_bCluster; }
	inline void CloseClustering() { 
		++ m_nCreateClustering; 
		m_bCluster=false; 
	}
	inline int GetCountOfOptimalLOBID() { return (int) m_vecOptimalLODID.size(); }

	// 클러스터링 선정
	void CalPEOfAllCluster();
	STR_LOBCLUSTER *SelectTheOptimalCluster();
	bool CalOptimalCluster( STR_CEDEOBID_INFO *pCEDEOBInfo );

	// 그룹화 관련 함수
	void CalClusterInfo( STR_LOBCLUSTER *pCluster, SELINTERSECTION *pRefInterSect=NULL );
	void FilteredIntersectionPoints();
	void UpdateClusterInfo( UINT uiAETID, UINT uiABTID, int iLOPPoolIndex );

	bool IsThereOptimalLOBID( int iLOBID );
	bool ReMakeOptimalCluster( STR_POSITION_ESTIMATION *pPEInfo, int nOptimalIndex );

};
 

#endif // !defined(AFX_LOBCLUSTERING_H__554E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)

