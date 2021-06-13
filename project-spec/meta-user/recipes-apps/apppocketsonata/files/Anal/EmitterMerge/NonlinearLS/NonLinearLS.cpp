//////////////////////////////////////////////////////////////////////////
/*!
 * @file      CNonLinearLS.cpp
 * @brief     CNonLinearLS 위치 산출 알고리즘
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-09-09 오후 4:07 
 * @warning   
 */

//#include "StdAfx.h"

#define _USE_MATH_DEFINES

#include <math.h>

#include "NonLinearLS.h"



CNonLinearLS::CNonLinearLS(void)
{
	Dk = CMatrix( 2, 1 );
	Dv = CMatrix( 2, 1 );

}


CNonLinearLS::~CNonLinearLS(void)
{
}

//////////////////////////////////////////////////////////////////////////
/*!
 * @brief     
 * @param     EL_TARGET_STATE_OPTION eTargetState
 * @return    int
 * @version   0.0.1
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-10-15 오후 8:11 
 * @warning   
 */
int CNonLinearLS::GetTargetState( EL_TARGET_STATE_OPTION eTargetState )
{
	if( eTargetState == STOP )
		return 0;
	else if( eTargetState == CONSTANT )
		return 0;
	else
		return 2;

	return 0;

}

//////////////////////////////////////////////////////////////////////////
/*!
 * @brief     
 * @param     CNonLinearLS * pResult
 * @param     SELINIT * pInit
 * @param     SELUTMTIME * pSensor
 * @param     int nEle
 * @return    void
 * @version   0.0.1
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-09-09 오후 7:04 
 * @warning   
 */
void CNonLinearLS::RunNonLinearLS( SELUTMTIME *pResult, SELINIT *pInit, SELUTMTIME *pSensor, double *pLob, int nEle, EL_TARGET_STATE_OPTION eTargetState )
{
	int i;
	double dVal;
	double theta, divide;

	double time_sec2;

	CMatrix A;
	CMatrix Sk, X;
	CMatrix Hk, Zk, Hkt;

	SELINIT loop_init;

	int loop_count;

	double *pStartLob;
	SELUTMTIME *pStartSensor;

	bool bret;

	// 행렬 초기화
	int numTargetState = GetTargetState( eTargetState );
	A = CMatrix( 2, 2*numTargetState+2 );
	X = CMatrix( 2*numTargetState+2, 1 );

	Hk = CMatrix( nEle, 2*numTargetState+2 );
	Zk = CMatrix( nEle, 1 );
	Hkt = CMatrix( 2*numTargetState+2, nEle );

	loop_count = 0;

	// 초기 값 복사
	memcpy( & loop_init, pInit, sizeof( SELINIT ) );

	while( loop_count < 2 ) {
		// 타겟 상태에 따라 이동 또는 정지 행렬 버퍼를 할당
		switch( eTargetState ) {
			case RAMP :
				X(5, 1) = loop_init.ramp.x;
				X(6, 1) = loop_init.ramp.y;

			case CONSTANT :
				X(3, 1) = loop_init.speed.x;
				X(4, 1) = loop_init.speed.y;

			case STOP :
				X(1, 1) = loop_init.pe.x;
				X(2, 1) = loop_init.pe.y;
				break;

			default :
				break;
		}

		pStartSensor = pSensor;
		pStartLob = pLob;

		// Hk 와 Zk 행렬을 구함.
		for( i=1 ; i <= nEle ; ++i ) {
			switch( eTargetState ) {
				case RAMP :
					/*! \bug  	condition에 직접적인 assignment operator를 사용하지 말아야 한다.
					    \author 조철희 (churlhee.jo@lignex1.com)
					    \date 	2014-01-24 16:13:49
					*/
					// A( 1, 5 ) = A( 2, 6 ) = ( pStartSensor->time_sec * pStartSensor->time_sec ) / 2.;
					dVal = ( pStartSensor->time_sec * pStartSensor->time_sec ) / 2.;
					A( 1, 5 ) = dVal;
					A( 2, 6 ) = dVal;

				case CONSTANT :
					/*! \bug  	condition에 직접적인 assignment operator를 사용하지 말아야 한다.
					    \author 조철희 (churlhee.jo@lignex1.com)
					    \date 	2014-01-24 16:13:49
					*/
					//A( 1, 3 ) = A( 2, 4 ) = pStartSensor->time_sec;
					dVal = pStartSensor->time_sec;
					A( 2, 4 ) = dVal;
					A( 1, 3 ) = dVal;

				case STOP :
					/*! \bug  	condition에 직접적인 assignment operator를 사용하지 말아야 한다.
					    \author 조철희 (churlhee.jo@lignex1.com)
					    \date 	2014-01-24 16:16:10
					*/
					//A( 1, 1 ) = A( 2, 2 ) = 1.0;
					A( 1, 1 ) = 1.0;
					A( 2, 2 ) = 1.0;
					break;

				default :
					break;

			}

			Sk = A * X;

			Dk(1, 1) = Sk( 1, 1) - pStartSensor->x;
			Dk(2, 1) = Sk( 2, 1) - pStartSensor->y;

			// Zk 를 계산
			theta = atan( Dk(2, 1) / Dk(1, 1) );
			Zk( i, 1 ) = *pStartLob - theta;

			// Hk 를 계산
			divide = 1. / ( ( Dk(1, 1) * Dk(1, 1) ) + ( Dk( 2, 1) * Dk( 2, 1) ) );
			switch( eTargetState ) {
				case RAMP :
					time_sec2 = ( pStartSensor->time_sec * pStartSensor->time_sec ) / 2.;
					Hk(i, 5) = divide * Dk( 2, 1) * time_sec2;
					Hk(i, 6) = divide * Dk( 1, 1) * time_sec2;

					Hkt( 5, i ) = Hk(i, 5);
					Hkt( 6, i ) = Hk(i, 6);

				case CONSTANT :
					Hk(i, 3) = divide * Dk( 2, 1) * pStartSensor->time_sec;
					Hk(i, 4) = divide * Dk( 1, 1) * pStartSensor->time_sec;

					Hkt( 3, i ) = Hk(i, 3);
					Hkt( 4, i ) = Hk(i, 4);

				case STOP :
					Hk(i, 1) = divide * ( - Dk( 2, 1) );
					Hk(i, 2) = divide * Dk( 1, 1);

					Hkt( 1, i ) = Hk(i, 1);
					Hkt( 2, i ) = Hk(i, 2);
					break;

				default :
					break;

			}

			++ pStartSensor;
			++ pStartLob;

		}

		// 위치 오차 에러 구하기
		// Dv = Inv( Hkt * Hk, & bret ) * Hkt * Zk;
		Dv = Inv( Hkt * Hk, & bret );
		if( bret == true ) {
			Dv = Dv * Hkt * Zk;

			// 초기 위치 업데이트
			loop_init.pe.x += Dv( 1, 1 );
			loop_init.pe.y += Dv( 2, 1 );
		}
		else {
			pResult->bResult = false;
			return;
		}

		++ loop_count;

	}

	// 최종 위치 산출 값을 저장
	pResult->x = loop_init.pe.x;
	pResult->y = loop_init.pe.y;

	pResult->bResult = true;

}

//////////////////////////////////////////////////////////////////////////
/*!
 * @brief     
 * @param     SELPositionEstimationResult * pResult
 * @param     SELUTMTIME * pEmitterXY
 * @param     SELUTMTIME * pSensorXY
 * @param     double * pTrueLob
 * @param     int nEle
 * @return    void
 * @version   0.0.1
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2014-02-11 오후 4:14 
 * @warning   
 */
void CNonLinearLS::CalCEP( SELPositionEstimationResult *pResult, SELPE_RESULT *pEmitterXY, SELPE_RESULT *pSensorXY, double *pTrueLob, int nEle )
{
	int i;

	double *pU, *pMHat;
	double *pBackU, *pBackMHat;

	CMatrix H, Ht;
	CMatrix W, Q;

	bool bret;

	// CEP/EEP 결과 값 초기화
	pResult->cep_error = -1.0;
	pResult->eep_major_axis = -1.0;
	pResult->eep_minor_axis = -1.0;
	pResult->eep_theta = -1.0;

	/*! \debug  신뢰성: 상/하한값을 설정
			\author 조철희 (churlhee.jo@lignex1.com)
			\date 	2015-10-5 20:55:09
	*/
	nEle = min( nEle, MAX_OF_LOBS );

	// 기초 연산값 버퍼 할당
	pU = ( double * ) malloc( sizeof(double) * nEle );
	pMHat = ( double * ) malloc( sizeof(double) * nEle );
	if( pU == NULL || pMHat == NULL ) {
		if( pU != NULL ) free( pU );
		if( pMHat != NULL ) free( pMHat );
		return;
	}

	// 백업 저장
	pBackU = pU;
	pBackMHat = pMHat;

	// 기초 연산값 연산
	for( i=1 ; i <= nEle ; ++i ) {
		*pMHat = ( pEmitterXY->x - pSensorXY->x );
		*pU = ( pEmitterXY->y - pSensorXY->y ) / ( pEmitterXY->x - pSensorXY->x );

		++ pU;
		++ pMHat;

		++ pSensorXY;
	}

	// H 벡터 생성
	pU = pBackU;
	pMHat = pBackMHat;
	H = CMatrix( nEle, 2 );
	Ht = CMatrix( 2, nEle );
	for( i=1 ; i <= nEle ; ++i ) {
		double ddivide;

		ddivide = ( 1. + ( *pU * *pU ) ) * *pMHat;
		H( i, 1 ) = ( -*pU ) / ddivide;
		H( i, 2 ) = ( 1.0 ) / ddivide;

		Ht( 1, i ) = H( i, 1 );
		Ht( 2, i ) = H( i, 2 );

		++ pU;
		++ pMHat;
	}

	free( pBackU );
	free( pBackMHat );

	double aoaVariance = AOA_VARIANCE * M_PI * M_PI / 180. / 180.;
	W = aoaVariance * Diag( nEle );
	W.Print();
	W = Inv( W, & bret );
	if( bret == false )				return;

	Q = Ht * W * H;
	Q.Print();

	if( bret == true ) {
		// EEP / CEP 결과 저장
		double c;
		double randa_1, randa_2;
		double sigma_x_square2;

		double sigma_x_square = Q( 1, 1 );
		double sigma_y_square = Q( 2, 2 );
		double rho_xy = Q( 1, 2 );
		double rho_xy2 = Q( 1, 2 ) * Q( 1, 2 );

		c = -2 * log( 1.0 - ( PROBABILITY_OF_BEING_INSIDE / 100. ) );

		sigma_x_square2 = (sigma_x_square - sigma_y_square);
		sigma_x_square2 *= sigma_x_square2;
		randa_1 = 0.5 * ( ( sigma_x_square + sigma_y_square ) + sqrt( sigma_x_square2 + ( 4 * rho_xy2 ) ) );
		randa_2 = 0.5 * ( ( sigma_x_square + sigma_y_square ) - sqrt( sigma_x_square2 + ( 4 * rho_xy2 ) ) );

		// EEP / CEP 결과 저장
		pResult->eep_major_axis = ( sqrt( randa_1 ) * c ) / 1000.;
		pResult->eep_minor_axis = ( sqrt( randa_2 ) * c ) / 1000.;

		pResult->eep_theta = ( 0.5 * atan( ( 2 * rho_xy ) / ( sigma_x_square - sigma_y_square ) ) ) * ( 180. / M_PI );

		pResult->cep_error = 0.75 * sqrt( randa_1 + randa_2 ) / 1000.;

	}

}
