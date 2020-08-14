//////////////////////////////////////////////////////////////////////////
/*!
 * @file      PositionEstimationAlg.cpp
 * @brief     위치 산출을 계산하기 위한 메인 클래스.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-09-09 오후 3:54
 * @warning
 */

#include "stdafx.h"

#include <math.h>
#include <float.h>

// #include "Eigen/Dense"

#include "./IsNumber.h"
#include "../OFP/SigAnal/_Define.h"
#include "./PositionEstimationAlg.h"

//#include "./Matrix/Matrix.h"

//#include "./Geo2UTM/Geo2UTM.h"

#include "./UTM.h"
#include "./GeoCoordConv.h"
#include "../Identify/ELUtil.h"
//#include "../../MNGR/Codec/ELDecoder.h"
//#include "../../../COMMON/MNGR/GRTestParamMngr.h"
#include "../Identify/ELCEDLibDataType2.h"
#include "../EmitterMerge/CInverseMethod.h"
#include "../EmitterMerge/VincentyParam.h"


#define UDIV( A, B )            (UINT) ( (float) (A) / (float) (B) + 0.5 )
//#define _abs(a)                 ( (int) (a) >= 0 ? (a) : -(a) )

#define	IS_VALID_LL( A, B )			( ( ( IsNumber(A) == true ) && ( IsNumber(B) == true ) && ( !( ( A > 360. ) || ( A < -360. ) || ( B > 360. ) || ( B < -360. ) ) ) ) == true )
#define	IS_NOT_ZERO_LL( A, B )	( ( ( A > 0 || A < 0 ) == true ) && ( ( B > 0 || B < 0 ) == true ) )

#define MAX_LOBS																			(100000)

#define THRESHOLD_OF_LOB_FOR_PE												(20)

#define ITEMS_FOR_TWO_ECLPISE													(5)


//#include "../../MNGR/ELElintUtilMngr.h"

//#include "../PositionEstimation/VincentyInverse/CInverseMethod.h"

CPositionEstimationAlg*  CPositionEstimationAlg::m_pInstance = 0;				///< 정적 초기화


/**
 * @brief     위치 산출 생성자 클래스: 초기화 및 메모리 할당한다.
 * @param     void
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-03-07, 오후 2:38
 * @warning
 */
CPositionEstimationAlg::CPositionEstimationAlg(void)
{

	m_pdCoVar = (double **) malloc( 2 * sizeof(double *) );

	if( m_pdCoVar != NULL ) {
		*(m_pdCoVar+0) = (double * ) malloc( 2 * sizeof(double) );
		*(m_pdCoVar+1) = (double * ) malloc( 2 * sizeof(double) );
	}

}


/**
 * @brief     ~CPositionEstimationAlg
 * @param     void
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-03-07, 오후 2:38
 * @warning
 */
CPositionEstimationAlg::~CPositionEstimationAlg(void)
{
	// 소멸자에세 객체를 메모리에서 해지함.

	free( *(m_pdCoVar+0) );
	free( *(m_pdCoVar+1) );
	free( m_pdCoVar );

}

/**
 * @brief     클래스의 인스턴스를 해지한다.
 * @param     void
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-03-07, 오후 2:47
 * @warning
 */
void CPositionEstimationAlg::ReleaseInstance()
{
	if( m_pInstance != NULL ) {
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////
/*!
 * @brief     위치 산출 알고리즘 객채를 리턴하며 비생성시에 생성하여 객체 값을 리턴한다.
 * @param     void
 * @return    CPositionEstimationAlg *
 * @version   0.0.1
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-09-09 오후 3:59
 * @warning
 */
CPositionEstimationAlg* CPositionEstimationAlg::GetInstance()
{
	if( m_pInstance == NULL ) {
		m_pInstance = new CPositionEstimationAlg();
	}

	return m_pInstance;
}

/**
 * @brief     이전의 빔 위치 산출 결과와 LOB 들을 이용하여 위치 산출 결과를 계산한다.
 * @param     SELPositionEstimationResult * pResult
 * @param     SELABTDATA_EXT * pABTExtData
 * @param     std::vector<STR_LOBS>* pVecLOB
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2016-03-17, 오후 3:47
 * @warning
 */
void CPositionEstimationAlg::RunPositionEstimation( SELPE_RESULT *pSELPE_RESULT, SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData, std::vector<STR_LOBS> *pVecLOB )
{
	int nLob;
	double *pLatitude, *pLongitude, *pLob;

	SELPositionEstimationResult result;

	std::vector<STR_LOBS>::pointer ppVecLOB;

	// 1. 센서 좌표에 대한 메모리 할당
	nLob = (int) pVecLOB->size();
	AllocSensors( nLob );

	// 2. 항공기 위치와 LOB 저장
	pLatitude = m_Sensor.pLatitude;
	pLongitude = m_Sensor.pLongitude;
	pLob = m_Sensor.pLob;
	ppVecLOB = pVecLOB->data() + ( nLob-1 );
	for( UINT i=0 ; i < m_Sensor.n ; ++i ) {
		*pLatitude = (double) ppVecLOB->fLatitude;
		*pLongitude = (double) ppVecLOB->fLongitude;
		*pLob	= (double) ppVecLOB->fDoa;

		++ pLatitude;
		++ pLongitude;
		++ pLob;

		-- ppVecLOB;

	}

	// 3. 위치 산출
	CommonRunPositionEstimation( pSELPE_RESULT, pABTData, pABTExtData );

	// 4. 메모리 해지
	FreeSensors();

}

void CPositionEstimationAlg::RunPositionEstimation( STR_POSITION_ESTIMATION *pPEInfo, SELABTDATA_EXT *pABTExtData, std::vector<STR_LOBS> *pVecLOB )
{
	int nLob;
	double *pLatitude, *pLongitude, *pLob;

	SRxABTData stABTData;

	std::vector<STR_LOBS>::pointer ppVecLOB;

	// 1. 센서 좌표에 대한 메모리 할당
	nLob = (int) pVecLOB->size();
	AllocSensors( nLob );

	// 2. 항공기 위치와 LOB 저장
	pLatitude = m_Sensor.pLatitude;
	pLongitude = m_Sensor.pLongitude;
	pLob = m_Sensor.pLob;
	ppVecLOB = pVecLOB->data() + ( nLob-1 );
	for( UINT i=0 ; i < m_Sensor.n ; ++i ) {
		*pLatitude = (double) ppVecLOB->fLatitude;
		*pLongitude = (double) ppVecLOB->fLongitude;
		*pLob	= (double) ppVecLOB->fDoa;

		++ pLatitude;
		++ pLongitude;
		++ pLob;

		-- ppVecLOB;

	}

	// 3. 위치 산출
	CommonRunPositionEstimation( NULL, & stABTData, pABTExtData );

	// 4. 결과 변환
	memset( & stABTData, 0, sizeof(STR_POSITION_ESTIMATION) );
	//pPEInfo->enValid = stABTData.iPEValid;

	pPEInfo->fLatitude = (float) stABTData.dLatitude;
	pPEInfo->fLongitude = (float) stABTData.dLongitude;

	pPEInfo->fCEP = stABTData.fCEP;
	pPEInfo->fMajorAxis = stABTData.fMajorAxis;
	pPEInfo->fMinorAxis = stABTData.fMinorAxis;
	pPEInfo->fTheta = stABTData.fTheta;

	// 5. 메모리 해지
	FreeSensors();

}

/**
 * @brief     위치 산출 결과와 LOB를 비교하여 LOB를 검증하여 LOB가 이상하면 위치 산출 결과를 버린다.
 * @param     SELPositionEstimationResult * pResult
 * @param     SELSensorPosition * pSensor
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2015-06-23, 오후 5:09
 * @warning
 */
#define ERROR_CHECK_OF_LOB_ERROR_RATIO		(60)			// 단위는 %, LOB 이상 개수를 체크
#define ERROR_CHECK_OF_LOB_DIFFERENCE			(80)			// 단위는 %, LOB 이상 개수를 체크
void CPositionEstimationAlg::VerifyOfLOB( SRxABTData *pABTData )
{
	int iError=0;
	SELDISTLOB distlob;

	int iDistLob;
	float fDistLob;

	if( ! ( pABTData->fCEP < 0 ) ) {
		double *pLatitude, *pLongitude, *pLob;

		pLob = & m_Sensor.pLob[0];
		pLatitude = & m_Sensor.pLatitude[0];
		pLongitude = & m_Sensor.pLongitude[0];
		for( UINT i=0 ; i < m_Sensor.n ; ++i ) {
			ST_IMA->VincentyInverse( & distlob, *pLatitude, *pLongitude, pABTData->dLatitude, pABTData->dLongitude );

			fDistLob = (float) ( distlob.fwdlob - *pLob + 0.5 );
			if( fDistLob < 0 ) {
				iDistLob = (int) ( fDistLob - 0.5 );
			}
			else {
				iDistLob = (int) ( fDistLob + 0.5 );
			}

			iDistLob = ( 360 + iDistLob ) % 360;

			// +- 90도 범위안에 들면 본 방향으로 판단한다.
			if( ! ( ( iDistLob > (360-ERROR_CHECK_OF_LOB_DIFFERENCE) /* && iDistLob <= 360 */ ) ||
			        ( iDistLob >= 0 && iDistLob <= ERROR_CHECK_OF_LOB_DIFFERENCE ) ) ) { //DTEC_Else
				++ iError;
			}

			++ pLob;
			++ pLatitude;
			++ pLongitude;
		}
		//
		if( UDIV( iError * 100, m_Sensor.n ) > ERROR_CHECK_OF_LOB_ERROR_RATIO ) {
			pABTData->iPEValid = _spZero;
			pABTData->fCEP = -1.0;

			pABTData->dLatitude = 0.;
			pABTData->dLongitude = 0.;

			pABTData->fMajorAxis = (float) 0.;
			pABTData->fMinorAxis = (float) 0.;
			pABTData->fTheta = (float) 0.;
			pABTData->fCEP = (float) 0.;
		}
		//TRACE( "\n ++++ 검증 에러 : %d / %d\n" , iError, m_Sensor.n );
	}
}

bool CPositionEstimationAlg::VerifyOfPositionEstimation( SELPE_RESULT *pResult, SELSensorPosition *pSensor )
{
	UINT uI;
	bool bRet=true;
	double dDiffLatitude, dDiffLongitude;

	double *pSensorLatitude, *pSensorLongitude, *pSensorLob;

	pSensorLob = pSensor->pLob;
	pSensorLatitude = pSensor->pLatitude;
	pSensorLongitude = pSensor->pLongitude;
	for( uI=0 ; uI < pSensor->n ; ++uI ) {
		dDiffLatitude = *pSensorLatitude - pResult->dLatitude;
		dDiffLongitude = *pSensorLongitude - pResult->dLongitude;

		// 경도가 0 초과일때 방위는 3/4 사분면에 있어야 한다.
		if( dDiffLongitude > 0 ) {
			if( !( *pSensorLob >= 180 && *pSensorLob <= 360 ) ) {
				pResult->bResult = false;
				pResult->dLongitude = -1;
				pResult->dLatitude = -1;
				break;
			}

		}
		// 경도가 0 미만일때 방위는 1/2 사분면에 있어야 한다.
		else if( dDiffLongitude < 0 ) {
			if( !( *pSensorLob >= 0 && *pSensorLob <= 180 ) ) {
				pResult->bResult = false;
				pResult->dLongitude = -1;
				pResult->dLatitude = -1;
				break;
			}
		}

		++ pSensorLatitude;
		++ pSensorLongitude;

		++ pSensorLob;

	}

	return bRet;

}

/**
 * @brief     위치 산출 결과와 항공가 최종 위치 결과를 비교하여 위치 산출 결과 여부를 최종 결정한다.
 * @param     SELPositionEstimationResult * pResult
 * @param     SELSensorPosition * pSensor
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2015-06-23, 오후 4:27
 * @warning
 */
#define ERROR_CHECK_OF_DISTANCE			(2000)
void CPositionEstimationAlg::VerifyOfPositionEstimation( SELPositionEstimationResult *pResult )
{
	SELDISTLOB distlob;

	if( ! ( pResult->cep_error < 0 ) ) {
		ST_IMA->VincentyInverse( & distlob, pResult->latitude, pResult->longitude, m_Sensor.pLatitude[m_Sensor.n-1], m_Sensor.pLongitude[m_Sensor.n-1] );

		//
		if( distlob.dDistance < ERROR_CHECK_OF_DISTANCE ) {
			pResult->cep_error = -1.0;
		}
	}
}

/**
 * @brief     주 클래스에서 생성한 위치 산출 관련 메모리 할당
 * @param     SELSensorPosition * pSensor
 * @param     int nLob
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2015-06-25, 오후 11:20
 * @warning
 */
void CPositionEstimationAlg::AllocSensors( int nLob )
{
	/*! \debug  신뢰성: LOB 상/한값 설정
			\author 조철희 (churlhee.jo@lignex1.com)
			\date 	2015-10-6 9:54:05
	*/
	m_Sensor.n = (UINT) min( nLob, MAX_OF_LOBS_PE );

	m_Sensor.pLatitude = new double[m_Sensor.n];
	m_Sensor.pLongitude = new double[m_Sensor.n];

	m_Sensor.pUTMX = new double[m_Sensor.n];
	m_Sensor.pUTMY = new double[m_Sensor.n];

	m_Sensor.pLob			 = new double[m_Sensor.n];
	m_Sensor.pTime		 = new time_t[m_Sensor.n];
	m_Sensor.pValid		 = new bool[m_Sensor.n];

}

/**
 * @brief     주 클래스에서 생성한 위치 산출 관련 메모리 해지
 * @param     void
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2015-06-25, 오후 11:21
 * @warning
 */
void CPositionEstimationAlg::FreeSensors()
{
	delete[] m_Sensor.pLatitude;
	delete[] m_Sensor.pLongitude;

	delete[] m_Sensor.pUTMX;
	delete[] m_Sensor.pUTMY;

	delete[] m_Sensor.pLob;
	delete[] m_Sensor.pTime;
	delete[] m_Sensor.pValid;
}

/**
 * @brief     C/E/F 공용 위치 산출 알고리즘을 수행한다. 위치 산출 결과를 예외 처리하여 항공기 및 LOB를 걸러낸다.
 * @param     SELPositionEstimationResult * pResult
 * @param     SELABTDATA_EXT * pABTExtData
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2015-06-25, 오후 11:26
 * @warning
 */
void CPositionEstimationAlg::CommonRunPositionEstimation( SELPE_RESULT *pSELPE_RESULT, SRxABTData *pABTData, SELABTDATA_EXT *pABTExtData, STR_POSITION_ESTIMATION *pPEInfo  )
{

	// 위치 산출
	// 1. 위치 산출 알고리즘을 계산한다.
	RunPositionEstimation( pSELPE_RESULT, pABTData, ADD_PE, STOP, pABTExtData, pPEInfo );

	// 2. 예외처리를 체크하여 위치 산출 결과 여부를 결정한다.
	// 2.1 예외 처리 #1: 항공기 최종 위치 근방에 위치 산출 결과가 나오는지를 검증한다.
	//VerifyOfPositionEstimation( pResult );

	// 2.2 예외 처리 #2: LOB 방향과 위치 산출 결과 방향을 비교해서 위치 산출 결과를 검증한다.
	//VerifyOfLOB( pABTData );
}

//////////////////////////////////////////////////////////////////////////
/*!
 * @brief     위치 산출 알고리즘을 수행하여 최적이 위치 추정 값을 리턴함.
 * @param     SELPositionEstimationResult * pResult
 * @param     EL_POSIOTN_ESTIMATION_ALGORITHM_OPTION eOption
 * @param     EL_TARGET_STATE_OPTION eTargetState
 * @param     SELABTDATA_EXT * pABTExtData
 * @return    void *
 * @version   0.0.1
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-09-09 오후 5:08
 * @warning
 */
void CPositionEstimationAlg::RunPositionEstimation( SELPE_RESULT *pSELPE_RESULT, SRxABTData *pABTData, EL_POSIOTN_ESTIMATION_ALGORITHM_OPTION eOption, EL_TARGET_STATE_OPTION eTargetState, SELABTDATA_EXT *pABTExtData, STR_POSITION_ESTIMATION *pPEInfo )
{
	time_t firstToa=0;

	bool *pValid;

	double dTargetLocDeg[2];
	double dInitPosRad[2];
	double dEEPData[4];

	m_nLob = m_Sensor.n;

	// 위치 정보 초기화
	//pResult->cep_error = -2.0;

	// LOB 개수가 부족할 때 에러로 리턴한다.
	if( m_nLob >= _spTwo && IsVerifyLOB() ) { //DTEC_Else
		// 센서와 LOB를 검증하여 위치 산출의 입력 데이터를 걸러낸다.
		// FilteredByCensorPosition();

		// 위치 산출 실행하기 전에 메모리 할당
		if( true == AllocateBuffer( (int) m_nLob ) ) {
			bool bResult;
			UINT uiFlagInitPos=0;
			double *dTemp=NULL;

			pValid = m_Sensor.pValid;

			dTargetLocDeg[0] = 0.;
			dEEPData[0] = 0.;

			// 위치 산출의 초기값 지정한다.
			if( pPEInfo != nullptr && pPEInfo->enValid == E_EL_PESTAT_SUCCESS ) {
				uiFlagInitPos = 1;

				dInitPosRad[0] = (double) pPEInfo->fLatitude;
				dInitPosRad[1] = (double) pPEInfo->fLongitude;
			}
			else {
				uiFlagInitPos = 0;

				dInitPosRad[0] = 0.;
				dInitPosRad[1] = 0.;
			}

			//bResult = m_theQuadratric.Run( & stResult, m_Sensor.pLatitude, m_Sensor.pLongitude, m_Sensor.pLob, m_nLob );
			//bResult = m_theDistanceLeastSquare.Run( & stResult, m_Sensor.pLatitude, m_Sensor.pLongitude, m_Sensor.pLob, m_nLob );
			//m_theDistanceLeastSquare.CalCEP( & stResult, pABTExtData );

			ConvertLatLong2( m_nLob, & m_Sensor );

#if defined(_UTM_POSITION_)
			bResult = m_theDistanceLeastSquare.Run( pSELPE_RESULT, m_Sensor.pUTMX, m_Sensor.pUTMY, m_Sensor.pLob, m_nLob );
#elif defined(_TM_POSITION_)
			bResult = m_theDistanceLeastSquare.Run( pSELPE_RESULT, m_Sensor.pUTMX, m_Sensor.pUTMY, m_Sensor.pLob, m_nLob );

			if( bResult == true ) {
				m_theGeoCoordConv.SetSrcType( kWgs84, kTmWest );
				m_theGeoCoordConv.SetDstType( kWgs84, kGeographic );
				m_theGeoCoordConv.Conv( pSELPE_RESULT->dEasting, pSELPE_RESULT->dNorthing, pSELPE_RESULT->dLongitude, pSELPE_RESULT->dLatitude );

				VerifyOfPositionEstimation( pSELPE_RESULT, & m_Sensor );
			}
			else {
				pSELPE_RESULT->dLongitude = 0;
				pSELPE_RESULT->dLatitude = 0;
			}

#else
			bResult = m_theDistanceLeastSquare.Run( pSELPositionEstimationResult, m_Sensor.pLatitude, m_Sensor.pLongitude, m_Sensor.pLob, m_nLob );
#endif

			m_theDistanceLeastSquare.CalCEP( pSELPE_RESULT, pABTExtData );
			//LogPrint("\n========================================== UseElintGeoLoc_CLobsDll 시간(%d) : %d ms", m_nLob, (int)((GetTickCount() - dwTime) / 1));

			if( bResult == true ) {
				//m_estEmitterXY.bResult = true;
// 				pABTData->iPEValid = _spOne;
// 				pABTData->dLatitude = stResult.dLatitude;
// 				pABTData->dLongitude = stResult.dLongitude;
// 
// 				pABTData->fMajorAxis = (float) stResult.eep_major_axis;		// dEEPData[0] * 2.0;
// 				pABTData->fMinorAxis = (float) stResult.eep_minor_axis;			// dEEPData[1] * 2.0;
// 				pABTData->fTheta = (float) stResult.eep_theta;					// M2Map( (int) ( dEEPData[2]*10. ) );
// 				pABTData->fCEP = (float) stResult.cep_error;
// 
// 				// 위,경도 값 유효성 체크
// 				if( ( pABTData->dLatitude > 40.0 || pABTData->dLatitude < 33 ) ||
// 					  ( pABTData->dLongitude > 135. || pABTData->dLongitude < 120. ) ||
// 					  ( 0 == _finite( pABTData->dLatitude ) ) ||
// 					  ( 0 == _finite( pABTData->dLongitude ) ) ) { //DTEC_Else
// 					pABTData->iPEValid = _spZero;
// 					pABTData->fCEP = -1.0;
// 				}
			}
// 			else {
// 				pABTData->iPEValid = _spZero;
// 				pABTData->fCEP = -1.0;
// 			}
		}

		// 위치 산출 실행후 메모리 해지
		ReleaseBuffer();
	}
	else {
		pSELPE_RESULT->bResult = false;
		//pABTData->iPEValid = _spZero;
		//pABTData->fCEP = -1.0;
	}

	return;
}

bool CPositionEstimationAlg::IsVerifyLOB()
{
	int i;
	bool bRet=false;

	double dLatitude, dLongitude;
	double *pLatitude, *pLongitude;

	pLatitude = & m_Sensor.pLatitude[0];
	pLongitude = & m_Sensor.pLongitude[0];
	dLatitude = *pLatitude;
	dLongitude = *pLongitude;
	++ pLatitude;
	++ pLongitude;
	for( i=1 ; i < (int) m_Sensor.n ; ++i ) {
		if( *pLatitude != dLatitude || *pLongitude != dLongitude ) {
			bRet = true;
			break;
		}
	
		++ pLatitude;
		++ pLongitude;

	}

	return bRet;
}

void CPositionEstimationAlg::ConvertLatLong2( int nLob, SELSensorPosition *pSensor )
{
	int i;
	double *pX, *pY;
	double *pLat, *pLong;

	pX = pSensor->pUTMX;
	pY = pSensor->pUTMY;
	pLat = pSensor->pLatitude;
	pLong = pSensor->pLongitude;
	for( i=0 ; i < nLob ; ++i ) {
#if defined(_UTM_POSITION_)
		LatLonToUTMXY( *pLat, *pLong, (int) UTM_ZONE, *pY, *pX );
#elif defined(_TM_POSITION_)
		m_theGeoCoordConv.SetSrcType(kWgs84, kGeographic );
		m_theGeoCoordConv.SetDstType(kWgs84, kTmWest );
		m_theGeoCoordConv.Conv( *pLong, *pLat, *pX, *pY );
#else

#endif

		++ pX;
		++ pY;

		++ pLat;
		++ pLong;
		
	}
}

/**
 * @brief     항공기 위치를 고려하여 LOB 유효성을 검증하여 반영해주는 함수
 * @param     void
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2015-06-23, 오후 7:10
 * @warning
 */
#define MAX_OF_CHECK_LOB								(10)
#define THRESHOLD_OF_DISTANCE_OFSENSORS	(50)			// 단위 는 m
void CPositionEstimationAlg::FilteredByCensorPosition()
{
	int i;
	int startLOBIndex;

	bool flag;

	bool *pValid;					// LOB 유효 플레그
	double *pLatitude, *pLongitude;

	SELDISTLOB distlob;

	// 유효 플레그 클리어
	memset( m_Sensor.pValid, 0, m_nLob * sizeof(bool) );

	if( m_Sensor.n <= MAX_OF_LOB ) {
		startLOBIndex = 0;
	}
	else {
		startLOBIndex = 0;
		startLOBIndex = (int) m_Sensor.n - MAX_OF_LOB;
	}

	pValid = & m_Sensor.pValid[startLOBIndex];
	pLatitude = & m_Sensor.pLatitude[startLOBIndex];
	pLongitude = & m_Sensor.pLongitude[startLOBIndex];
	for( i=startLOBIndex ; i < (int) m_Sensor.n-1 ; ++i ) {
		// 위경도 좌표 검증
		flag = true;
		if( IS_VALID_LL( *pLatitude, *pLongitude ) && IS_NOT_ZERO_LL( *pLatitude, *pLongitude ) ) {
// 			double *pLatitude2, *pLongitude2;
//
// 			pLatitude2 = pLatitude + 1;
// 			pLongitude2 = pLongitude + 1;
//
// 			/*! \todo   나머지 데이터에 대해서 비교해야 하는데 마킹을 어디에 하기가 어렵다.
// 									현재는 기본적으로 한군데에서 마킹하는 것으로 함.
// 									// for( ; j <= MAX_OF_CHECK_LOB && (i+j) < m_Sensor.n ; ++j ) {
// 			    \author 조철희 (churlhee.jo@lignex1.com)
// 			    \date 	2015-07-20 17:39:25
// 			*/
// 			if( IS_VALID_LL( *pLatitude2, *pLongitude2 ) ) {
// 				ST_IMA->VincentyInverse( & distlob, *pLatitude, *pLongitude, *pLatitude2, *pLongitude2 );
// 				if( distlob.distance < THRESHOLD_OF_DISTANCE_OFSENSORS ) { //DTEC_Else
// 					flag = false;
// 				}
// 			}

			*pValid = flag;
		}
		else { //DTEC_Else
			*pValid = false;
			TRACE( "\n위/경도 에러 : %.3f/%.3f", *pLatitude, *pLongitude );
		}

		// 대상 포인터 이동
		++ pValid;
		++ pLatitude;
		++ pLongitude;

	}

	if( IS_VALID_LL( m_Sensor.pLatitude[m_Sensor.n-1], m_Sensor.pLongitude[m_Sensor.n-1] ) && IS_NOT_ZERO_LL( *pLatitude, *pLongitude ) ) {
		m_Sensor.pValid[ m_Sensor.n-1 ] = true;
	}

}

//////////////////////////////////////////////////////////////////////////
/*!
 * @brief     위치 산출을 처리하기 위한 메모리 할당
 * @param     int size
 * @return    void
 * @version   0.0.1
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-09-09 오후 6:12
 * @warning
 */
bool CPositionEstimationAlg::AllocateBuffer( int isize )
{
	int nSize;

	/*! \debug  신뢰성: 메모리 크기 지정
			\author 조철희 (churlhee.jo@lignex1.com)
			\date 	2015-10-6 9:51:16
	*/
	if( isize < MAX_LOBS ) {
		nSize = (int) sizeof(SELPE_RESULT) * isize;
		m_pSensorXY = ( SELPE_RESULT * ) malloc( (UINT) nSize );

		/*! \debug  신뢰성: 메모리 크기 지정
				\author 조철희 (churlhee.jo@lignex1.com)
				\date 	2015-10-6 9:51:16
		*/
		nSize = (int) sizeof(double) * isize;
		m_pLob = ( double * ) malloc( (UINT) nSize );
	}
	else {
		m_pSensorXY = NULL;
		m_pLob = NULL;
	}

	return m_pSensorXY != NULL && m_pLob != NULL;

}

//////////////////////////////////////////////////////////////////////////
/*!
 * @brief     위치 산출에 사용한 메모리 해지
 * @param     void
 * @return    void
 * @version   0.0.1
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-09-09 오후 6:12
 * @warning
 */
void CPositionEstimationAlg::ReleaseBuffer()
{
	//EL_UTIL.LogPrint( LOG_DUMMY, "\n 메모리 해지 주소 : %p" , m_SensorXY );

	/*! \debug  신뢰성: NULL 포인터 체크하여 처리
			\author 조철희 (churlhee.jo@lignex1.com)
			\date 	2015-10-5 21:17:57
	*/
	if( m_pSensorXY != NULL ) {
		free( m_pSensorXY );
	}
	m_pSensorXY = NULL;

	if( m_pLob != NULL )	{
		free( m_pLob );
	}
	m_pLob = NULL;

}

/**
 * @brief     이전의 위치 산출 결과를 내적 계산으로 근거로 신규 위치 산출 계산한다.
 * @param     double [2] dTargetLocDeg
 * @param     double [4] dEEPData
 * @param     double [4] dPECoVar
 * @param     double ** m_pdCoVar
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-12-29, 오후 7:04
 * @warning
 */
// bool CPositionEstimationAlg::CalculateTwoEclippse( double dTargetLocDeg[2], double dEEPData[4], STR_POSITION_ESTIMATION *pPEInfo, double dPECoVar[4], double *pdCoVar )
// {
// 	bool bRet;
// 	bool bRet1, bRet2;
// 	double *dTemp;
// 	double dCoVar[4];
// 
// 	double dX1[2];
// 
// 	CMatrix c1(2,2), c2(2,2), c3(2,2), k(2,2);
// 
// 	CMatrix x3(2,1), x1(2,1), x2(2,1);
// 
// 	dCoVar[0] = pdCoVar[0];
// 	dCoVar[1] = pdCoVar[1];
// 
// 	dCoVar[2] = pdCoVar[2];
// 	dCoVar[3] = pdCoVar[3];
// 
// 	c1.SetValue( dPECoVar, 2, 2 );
// 	c2.SetValue( dCoVar, 2, 2 );
// 
// 	k = c1 + c2;
// 	k = k.Inv( & bRet );
// 
// 	if( bRet == true ) {
// 		bRet = false;
// 
// 		k = c1 * k;
// 
// 		dX1[0] = pPEInfo->iLatitude / 1000000.0;
// 		dX1[1] = pPEInfo->iLongitude / 1000000.0;
// 
// 		x1.SetValue( dX1, 2, 1 );
// 		x2.SetValue( dTargetLocDeg, 2, 1 );
// 		x3 = k * ( x2 - x1 );
// 		x3 = x1 + x3;
// 
// 		dTargetLocDeg[0] = x3.GetValue( 1, 1 );
// 		dTargetLocDeg[1] = x3.GetValue( 2, 1 );
// 
// 		c1 = c1.Inv( & bRet1 );
// 		c2 = c2.Inv( & bRet2 );
// 
// 		if( bRet1 == true && bRet2 == true ) {
// 			c3 = c1 + c2;
// 			c3 = c3.Inv( & bRet );
// 
// 			if( bRet == true ) {
// 				pdCoVar[0] = c3.GetValue( 1, 1 );
// 				pdCoVar[1] = c3.GetValue( 1, 2 );
// 
// 				pdCoVar[2] = c3.GetValue( 2, 1 );
// 				pdCoVar[3] = c3.GetValue( 2, 2 );
// 
// 				bRet = true;
// 			}
// 		}
// 	}
// 
// 	return bRet;
// 
// }

float CPositionEstimationAlg::M2Map( int iEEPTiltAngle )
{
	int iTheta=0;
	float fTheta=0.0;

	// 1차 변환
	iTheta = - iEEPTiltAngle + 900;

	// 2차 변환 (지도에 뿌리기 위해서는 양의 값으로 변환)
	if( iTheta < 0 ) { //EX_DTEC_Else
		iTheta += 7200;
	}

	iTheta %= 1800;

	fTheta = (float) ( iTheta / 10. );

	return fTheta;

}