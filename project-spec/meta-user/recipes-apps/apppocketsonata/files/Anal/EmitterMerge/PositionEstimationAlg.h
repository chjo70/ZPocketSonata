//////////////////////////////////////////////////////////////////////////
/*!
 * @file      PositionEstimationAlg.h
 * @brief     위치 산출 알고리즘
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-09-09 오후 3:53 
 * @warning   
 */

#pragma once

//using namespace std;
#include <vector>

using namespace std;

#include "./PositionEstimation.h"

#include "./GeoCoordConv/GeoCoordConv.h"

#include "./Quadratic/Quadratic.h"
#include "./DistanceLeastSquare/DistanceLeastSquare.h"
#include "./LinearLS/LinearLS.h"
#include "./NonlinearLS/NonLinearLS.h"

#include "./InverseMethod/CInverseMethod.h"

#include "./Coordinate/Coordinate.h"


//#include "../Library/EGeoLocCommonDll.h"

// 프로젝트에 따라서 이전 위치 산출 추정치 이력 관련 구조체를 선언해야 한다.
// ELINT용 위치 산출 정보 구초체를 추가함.
//#include "./ElintRsltDataTypedb.h"
#include "./ELEmitterDataType.h"


#define _POSITION_ESTIMATION_OPTION					(1)



// UTM 계로 위치 산출
//#define _UTM_POSITION_
//#define _TM_POSITION_

/*!
 * @def				LOB2AOA
 * @brief			LOB 값을 AOA 값으로 변환해주는 것
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-09-14 오전 10:28 
 */
#define LOB2AOA(A)		(double) ( ( 360.0 - (double) A ) + 90. )

/**
 * @def       UPPER_LIMIT_OF_LOB
 * @brief     EEP를 계산하기 위한 최소 위치 타겟 개수
 * @author    조철희 (churlhee.jo@lignex1.com)
 */
#define UPPER_LIMIT_OF_LOB					(20)						// 단위 : 개수

/**
 * @def       MAX_OF_LOB
 * @brief     위치 산출하기 위한 최대 LOB 개수
 * @author    조철희 (churlhee.jo@lignex1.com)
 */
#define MAX_OF_LOB									(1000)

/**
* [식별자 : CLS-GMU-EL-L-PEA]
*
* [추적성 : SRS-G-SAFR-012]
*
* @class	CPositionEstimationAlg
* @brief	위치 산출해주는 클래스
*
* (1) 클래스 설명
* - 본 클래스는 LOB 들에 대해서 위치 산출하여 CED/EEP 결과를 리턴해주는 클래스이다.
*
* (2) 설계결정사항
* - 위치 산출 라이브러리는 Geolocation_CLobsDll.dll 이다.
*
* (3) 제한 및 예외처리
* - 해당사항 없음
*/
class CPositionEstimationAlg
{
private:
    // 위치 산출 알고리즘 
	CDistanceLeastSquare m_theDistanceLeastSquare;
	CQuadratic m_theQuadratric;

	UINT m_nLob;																				///< 위치 산출할 LOB 개수
	SELPE_RESULT m_estEmitterXY;													///< 위치 산출 결과

	double *m_pLob;																			///< 위치 산출 라이브러리에 사용할 LOB 데이터
	SELSensorPosition m_Sensor;													///< 위치 산출 라이브러리에 사용할 항공기 센서 좌표

#if defined(_TM_POSITION_)
	CGeoCoordConv m_theGeoCoordConv;
#endif

    CInverseMethod m_theInverseMethod;

	STR_LOBS *m_pR1;
	STR_LOBS *m_pR2;
	STR_LOBS *m_pR3;
	STR_LOBS *m_pR4;

    // ENUN 일때 기본 좌표계
#if defined(_ENU_POSITION_)
    SLlhPos m_stOrgLlh;
#endif

public:
	CPositionEstimationAlg(void);
	~CPositionEstimationAlg(void);

	void ConvertLatLong2( int nLob, SELSensorPosition *pSensor );

    void RunPositionEstimation( SELPE_RESULT *pSELPE_RESULT, int nLob, STR_LOBS *pstrLOB );
	void RunPositionEstimation( STR_POSITION_ESTIMATION *pPEInfo, SELABTDATA_EXT *pABTExtData, std::vector<STR_LOBS> *pVecLOB );
    void RunPositionEstimation( SELPE_RESULT *pSELPE_RESULT, SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData, std::vector<STR_LOBS> *pVecLOB );

	void RunPositionEstimation( SELPE_RESULT *pSELPE_RESULT, std::vector<STR_LOBS> *pVecLOB );

	double EstimatedAltitude( SEnuPos *pstEnuPos );
	//////////////////////////////////////////////////////////////////////////

private:
	void RunPositionEstimation( SELPE_RESULT *pSELPE_RESULT, EL_POSIOTN_ESTIMATION_ALGORITHM_OPTION eOption, EL_TARGET_STATE_OPTION eTargetState=STOP, STR_POSITION_ESTIMATION *pPEInfo=NULL );

	bool VerifyOfPositionEstimation( SELPE_RESULT *pResult, SELSensorPosition *pSensor );
	void VerifyOfPositionEstimation( SELPositionEstimationResult *pResult );
	void VerifyOfLOB( SRxABTData *pABTData );

	void FilteredByCensorPosition();

	//bool AllocateBuffer( int isize );
	//void ReleaseBuffer();

	void AllocSensors( int nLob );
	void CommonRunPositionEstimation( SELPE_RESULT *pSELPE_RESULT, STR_POSITION_ESTIMATION *pPEInfo=NULL );
	void FreeSensors();
	float M2Map( int iEEPTiltAngle );

	bool IsVerifyLOB();

};

