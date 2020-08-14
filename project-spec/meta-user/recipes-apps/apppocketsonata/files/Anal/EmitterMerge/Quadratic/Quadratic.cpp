//////////////////////////////////////////////////////////////////////////
/*!
 * @file      Quadratic.cpp
 * @brief     Quadratic 위치 산출 알고리즘
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-09-09 오후 4:07 
 * @warning   
 */

#include "StdAfx.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "../../SigAnal/_macro.h"
#include "../../SigAnal/_define.h"

#include "Quadratic.h"
#include "../LOBClustering.h"

#include "../UTM.h"


CQuadratic::CQuadratic(void)
{
}


CQuadratic::~CQuadratic(void)
{
}

//////////////////////////////////////////////////////////////////////////
/*!
 * @brief     
 * @param     SELPositionEstimationResult * pResult
 * @param     SELUTMTIME * pSensor
 * @param     int nEle
 * @return    void
 * @version   0.0.1
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-09-09 오후 7:04 
 * @warning   
 */
bool CQuadratic::Run( SELPE_RESULT *pResult, double *pLatitude, double *pLongitude, double *pLob, int nLob )
{
	int i;

	double a, b, c;
	double A, B, D, E, G;
	double B1, B2;
	double sumA, sumB, sumB1, sumB2, sumD, sumE, sumG;
	double sumD2, sumE2, sumG2, sumED2;
	double alpha, omega, gamma;
	double u1, u2;
	double x1, x2, y1, y2;
	double condi1, condi2;

	double *ppLatitude, *ppLongitude;
	double dDistX, dDistY;

	double dTheta;

	memset( pResult, 0, sizeof(SELPE_RESULT) );

	for( i=0 ; i < nLob ; ++i ) {
		printf( "\n [%3d] 위도[%f], 경도[%f], 방위[%f]" , i, pLatitude[i], pLongitude[i], 90.-pLob[i] );
	}

	ppLatitude = pLatitude;
	ppLongitude = pLongitude;

	/*! \bug  	condition에 직접적인 assignment operator를 사용하지 말아야 한다.
	    \author 조철희 (churlhee.jo@lignex1.com)
	    \date 	2014-01-24 16:20:48
	*/
	//sumA = sumB = sumB1 = sumB2 = sumD = sumE = sumG = 0.0;
	sumA = 0.0;
	sumB = 0.0;
	sumB1 = 0.0;
	sumB2 = 0.0;
	sumD = 0.0;
	sumE = 0.0;
	sumG = 0.0;

	// 
	for( i=0 ; i < nLob ; ++i ) {
		dTheta = 90.0 - *pLob;
		dTheta = ( dTheta * M_PI ) / 180.;

		a = sin( dTheta );
		b = -cos( dTheta );
		c = *pLongitude * a + *pLatitude * b;

		A = a * b;
		B1 = a * a;
		B2 = b * b;
		B = B2 - B1;
		D = -( b * c );
		E = a * c;
		G = c * c;

		sumA = A + sumA;
		sumB = B + sumB;
		sumB1 = B1 + sumB1;
		sumB2 = B2 + sumB2; 
		sumD = D + sumD;
		sumE = E + sumE;
		sumG = G + sumG;

		++ pLob;
		++ pLongitude;
		++ pLatitude;
	}

	sumD2 = sumD * sumD;
	sumE2 = sumE * sumE;
	sumG2 = sumG * sumG;
	sumED2 = ( sumE2 + sumD2 ) * ( sumE2 + sumD2 );

	alpha = sumA * ( sumD2 - sumE2 ) + ( sumB * sumD * sumE );
	omega = ( 4 * sumA * sumD * sumE * sumG ) + ( sumB * sumG * ( sumE2 - sumD2 ) ) + sumED2;
	gamma = sumG2 * ( ( sumA * sumE2 ) - ( sumB * sumD * sumE ) - ( sumA * sumD2 ) );

	if( alpha != 0 ) {
		u1 = ( -omega + sqrt( omega*omega - ( 4. * alpha * gamma ) ) ) / ( 2. * alpha );
		u2 = ( -omega - sqrt( omega*omega - ( 4. * alpha * gamma ) ) ) / ( 2. * alpha );
	}
	else {
		return false;
	}

	if( sumE2 != -sumD2 ) {
		x1 = ( sumD * u1 + sumE * sumG ) / ( sumE2 + sumD2 );
		x2 = ( sumD * u2 + sumE * sumG ) / ( sumE2 + sumD2 );

		y1 = ( sumE * u1 - sumD * sumG ) / ( sumE2 + sumD2 );
		y2 = ( sumE * u2 - sumD * sumG ) / ( sumE2 + sumD2 );
	}
	else {
		return false;
	}

	condi1 = (sumB * x1*x1) - ( 4 * sumA * x1 * y1 ) - ( sumB * y1*y1 ) + ( sumE * x1 ) - ( sumD * y1 );
	condi2 = (sumB * x2*x2) - ( 4 * sumA * x2 * y2 ) - ( sumB * y2*y2 ) + ( sumE * x2 ) - ( sumD * y2 );

	pResult->eep_major_axis = -1.0;
	pResult->eep_minor_axis = -1.0;
	pResult->eep_theta = 0.0;
	pResult->cep_error = -1.0;

	// 최종 위치 산출 값을 저장
	if( fabs(condi1) < fabs(condi2) ) {
		pResult->dLongitude = x1;
		pResult->dLatitude = y1;
  }
	else {
		pResult->dLongitude = x2;
		pResult->dLatitude = y2;
	}

	dDistX = fabs( pResult->dLongitude - ppLongitude[0] );
	dDistY = fabs( pResult->dLatitude - ppLatitude[0] );

	if( dDistX < 0.0001 && dDistY < 0.0001 ) {
		pResult->dLongitude = -1;
		pResult->dLatitude = -1;
		return false;
	}

	pResult->bResult = true;

	return true;

}

void CQuadratic::CalCEP( SELPE_RESULT *pResult, SELABTDATA_EXT *pABTExtData )
{
	int i, iNumPE;

	double dValue;
	double dEasting, dNorthing;

	double dENorthing, dEEasting;
	double dSSNorthing, dSSEasting, dSLL, dSNorthing, dSEasting;

	double dR1, dR2;
	double dSumSS, dSumA, dC;

	if( pResult->bResult == true ) {
		if( pABTExtData->bFullOfPE == false && pABTExtData->uiPE <= _spOne ) {

		}
		else {
			LatLonToUTMXY( pResult->dLatitude, pResult->dLongitude, UTM_ZONE, dEasting, dNorthing );

			if( pABTExtData->bFullOfPE == true ) {
				iNumPE = MAX_OF_LOBS_PE;
			}
			else {
				iNumPE = pABTExtData->uiPE;
			}

			// Northing 평균 구하기
			dENorthing = dNorthing;
			for( i=0 ; i < iNumPE ; ++i ) {
				dENorthing += pABTExtData->dNorthing[i];
			}
			dENorthing /= (iNumPE+1);

			// Easting 평균 구하기
			dEEasting = dEasting;
			for( i=0 ; i < iNumPE ; ++i ) {
				dEEasting += pABTExtData->dEasting[i];
			}
			dEEasting /= (iNumPE+1);

			// Northing 분산 구하기
			dSSNorthing = dENorthing - dNorthing;
			dSSNorthing *= dSSNorthing;
			for( i=0 ; i < iNumPE ; ++i ) {
				dValue = dENorthing - pABTExtData->dNorthing[i];
				dSSNorthing += ( dValue * dValue );
			}
			dSSNorthing /= (iNumPE+1);
			dSNorthing = sqrt( dSSNorthing );

			// Easting 분산 구하기
			dSSEasting = dEEasting - dEasting;
			dSSEasting *= dSSEasting;
			for( i=0 ; i < iNumPE ; ++i ) {
				dValue = dEEasting - pABTExtData->dEasting[i];
				dSSEasting += ( dValue * dValue );
			}
			dSSEasting /= (iNumPE+1);
			dSEasting = sqrt( dSSEasting );

			// Easting/Northing 분산 구하기
			dSLL = ( dENorthing - dNorthing ) * ( dEEasting - dEasting );
			for( i=0 ; i < iNumPE ; ++i ) {
				dSLL += ( ( dENorthing - pABTExtData->dNorthing[i] ) * ( dEEasting - pABTExtData->dEasting[i] ) );
			}
			dSLL /= (iNumPE+1);

			// CEP 구하기
			pResult->cep_error = 0.75 * sqrt( dSSNorthing + dSSEasting );

			// EEP 기울기 구하기
			pResult->eep_theta = 0.5 * atan( ( 2. * dSNorthing * dSEasting ) / ( dSNorthing - dSEasting ) );
			pResult->eep_theta = RADIAN2DEGREE( pResult->eep_theta );

			// EEP 장축/단축 구하기
			dC = -2.0 * log( 1.0 - 0.4 );
			dSumSS = dSSNorthing + dSSEasting;
			dSumA = ( dSumSS * dSumSS ) - 4.0 * ( ( dSSNorthing * dSSEasting ) - ( dSLL * dSLL ) );
			dR1 = 0.5 * ( dSumSS + sqrt( dSumA ) );
			dR2 = 0.5 * ( dSumSS - sqrt( dSumA ) );

			pResult->eep_major_axis = sqrt( dR1 * dC );
			pResult->eep_minor_axis = sqrt( dR2 * dC );
		}
	}

	return;
}
