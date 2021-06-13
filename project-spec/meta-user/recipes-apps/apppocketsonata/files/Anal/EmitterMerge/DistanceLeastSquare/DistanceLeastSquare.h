//////////////////////////////////////////////////////////////////////////
/*!
 * @file      DistanceLeastSquare.h
 * @brief     DistanceLeastSquare 알고리즘을 이용한 위치 산출
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-09-09 오후 4:06 
 * @warning   
 */

#pragma once

#include "../PositionEstimation.h"
#include "../ELEmitterDataType.h"

#include "../Matrix/Matrix.h"

#include "../CEP/AnalyticCEP.h"

class CDistanceLeastSquare : public CAnalyticCEP
{
private:

public:
	CDistanceLeastSquare(void);
	~CDistanceLeastSquare(void);

	bool Run( SELPE_RESULT *pResult, double *pLatitude, double *pLongitude, double *pLob, int nLob );
	bool CalCEP( SELPE_RESULT *pResult, SELABTDATA_EXT *pABTExtData );

	void CalCEP( SELPositionEstimationResult *pResult, SELPE_RESULT *pEmitterXY, SELPE_RESULT *pSensorXY, double *pTrueLob, int nEle );

};

