//////////////////////////////////////////////////////////////////////////
/*!
 * @file      PositionEstimation.h
 * @brief     위치 산출 알고리즘 구조체 정의
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-09-09 오후 3:53 
 * @warning   
 */

#pragma once

#include <time.h>

// 방탐 분산값
// Analytic CEP를 계산하기 위한 측정값
#define AOA_VARIANCE									(1)						// 단위 : degree

// CEP/EEP 확률 정의
#define PROBABILITY_OF_BEING_INSIDE		(50)					// 단위 : %

/*!
 * @typedef   SELPositionEstimation
 * @brief			위치 산출 결과가 저장할 구조체 정의
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-09-09 오후 4:54
 */
struct SELPositionEstimationResult {
	// 위치 산출 최종 결과
	double latitude;			// 위도
	double longitude;			// 경도

	// CEP
	double cep_error;						// 단위 : m

	// EEP 관련 정보
	// 장축
	double eep_major_axis;			// 단위 : m
	// 단축
	double eep_minor_axis;			// 단위 : m
	// theta
	double eep_theta;						// 각도 : degree

	// EOB 또는 다른 위치 산출 알고리즘에서 얻은 위치 산출 초기값
	double reallatitude;					
	double reallongitude;
	
	SELPositionEstimationResult()
	{
		latitude=0.0;			// 위도
		longitude=0.0;			// 경도
		//latitude_x=0.0;
		//longitude_y=0.0;

		 cep_error=0.0;						// 단위 : m		
		 eep_major_axis=0.0;			// 단위 : m		
		 eep_minor_axis=0.0;			// 단위 : m		
		 eep_theta=0.0;						// 각도 : degree
		 reallatitude=0.0;					
		 reallongitude=0.0;
	}

}  ;

/*!
 * @typedef   SELSensorPosition
 * @brief			항공기 위치, 위경도 좌표와 항공기에서 측정한 타겟의 LOB 값 그리고 기타 정보를 저장한 구조체 정의
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-09-09 오후 5:07
 */
struct SELSensorPosition {
	double *pLatitude;		// 단위 : degree
	double *pLongitude;		// 단위 : degree
	double *pAltitude;		// 단위 : meter

	int iCollectorID;

	double *pX;
	double *pY;
    double *pH;

	double *pLob;				// 단위 : degree
	time_t *pTime;				// 단위 : 초

	bool *pValid;					// LOB 유효 플레그

    unsigned int n;

}  ;


/*!
 * @typedef   SELPE_RESULT
 * @brief		UTM계 구조체 정의
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-09-09 오후 5:44
 */
typedef struct {
	double dLongitude;			// 경도 [도]
	double dLatitude;			// 위도 [도]
	double dAltitude;			// 고도 [m]

	double dEasting;
	double dNorthing;

	//unsigned int time_sec;

	double dEEP_major_axis;     // [m]
	double dEEP_minor_axis;     // [m]
	double dEEP_theta;          // [도]
	double dCEP_error;          // [m]

	bool bResult;

} SELPE_RESULT ;

/*!
 * @typedef   VECTOR
 * @brief			2차원계에서의 벡터 값을 표시
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-10-15 오후 5:03
 */
struct VECTOR {
	double x;
	double y;

} ;

/*!
 * @typedef   SELINIT
 * @brief			Nonlinear 위치 산출을 계산하기 위한 초기 값 구조체 정의
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-10-15 오후 5:03
 */
struct SELINIT {
	VECTOR pe;
	VECTOR speed;
	VECTOR ramp;

}  ;

//! 위치 산출 알고리즘 선택
enum EL_POSIOTN_ESTIMATION_ALGORITHM_OPTION { QUADRATIC=0, DISTANCE_LEAST_SQUARE, LINEAR_LS, NONLINEAR_LS, ADD_PE, AUTO } ;

//! 신호원 정지/등속/등가속 이동시 정의
enum EL_TARGET_STATE_OPTION { STOP=0, CONSTANT, RAMP } ;

