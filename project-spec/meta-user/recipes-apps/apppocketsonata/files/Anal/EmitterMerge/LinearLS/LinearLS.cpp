//////////////////////////////////////////////////////////////////////////
/*!
 * @file      CLinearLS.cpp
 * @brief     CLinearLS 위치 산출 알고리즘
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-09-09 오후 4:07 
 * @warning   
 */

#include "StdAfx.h"

#include <math.h>

#include "LinearLS.h"
#include "../Matrix/Matrix.h"


CLinearLS::CLinearLS(void)
{
}


CLinearLS::~CLinearLS(void)
{
}

//////////////////////////////////////////////////////////////////////////
/*!
 * @brief     
 * @param     CLinearLS * pResult
 * @param     SELUTMTIME * pSensor
 * @param     int nEle
 * @param     EL_TARGET_STATE_OPTION eTargetState
 * @return    void
 * @version   0.0.1
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-09-09 오후 7:04 
 * @warning   
 */
void CLinearLS::RunLinearLS( SELUTMTIME *pResult, SELUTMTIME *pSensor, double *pLob, int nEle, EL_TARGET_STATE_OPTION eTargetState )
{
	int i;
	double a, b, c, d;

	bool bret;

	try {
		CMatrix H, Ht;
		CMatrix zk = CMatrix( nEle, 1 );
		CMatrix R = CMatrix( 2, 1 );
		CMatrix In = CMatrix( nEle, nEle );

		// 타겟 상태에 따라 이동 또는 정지 행렬 버퍼를 할당
		switch( eTargetState ) {
			case STOP :
				H = CMatrix( nEle, 2 );
				Ht = CMatrix( 2, nEle );
				break;

			case CONSTANT :
				H = CMatrix( nEle, 4 );
				Ht = CMatrix( 4, nEle );
				break;

			case RAMP :
				H = CMatrix( nEle, 6 );
				Ht = CMatrix( 6, nEle );
				break;

			default :
				break;

		}

		memcpy( pResult->zone, pSensor->zone, sizeof(pSensor->zone) );

		// 
		for( i=0 ; i < nEle ; ++i ) {
			a = sin( *pLob );
			b = -cos( *pLob );

			// H 행렬 만들기
			H(i+1, 1 ) = a;
			H(i+1, 2 ) = b;

			// H' 행렬 만들기
			Ht(1, i+1 ) = a;
			Ht(2, i+1 ) = b;

			if( eTargetState == CONSTANT ) {
				c = a * pSensor->time_sec;
				d = b * pSensor->time_sec;

				// H 행렬 만들기
				H(i+1, 3 ) = c;
				H(i+1, 4 ) = d;

				// H' 행렬 만들기
				Ht(3, i+1 ) = c;
				Ht(4, i+1 ) = d;
			}
		
			zk(i+1,1) = ( pSensor->x * a ) + ( pSensor->y * b );

			++pLob;
			++pSensor;

		}

		In = Inv( Ht * H, & bret );

		if( bret == true ) {
			R = Ht * zk;
			R = In * R;

			// 최종 위치 산출 값을 리턴
			pResult->x = R(1, 1);
			pResult->y = R(2, 1);

			pResult->bResult = true;
		}
		else {
			pResult->x = R(1, 1);
			pResult->y = R(2, 1);

			pResult->bResult = false;

		}
	}
	catch (Exception err)
	{
		printf("Error: %s\n", err.msg);
	}
	catch (...)
	{
		printf("An error occured...\n");
	}

}

