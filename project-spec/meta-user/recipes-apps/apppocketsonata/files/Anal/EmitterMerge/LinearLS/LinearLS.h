//////////////////////////////////////////////////////////////////////////
/*!
 * @file      CLinearLS.h
 * @brief     CLinearLS 알고리즘을 이용한 위치 산출
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-09-09 오후 4:06 
 * @warning   
 */

#pragma once

#include "../PositionEstimation.h"

class CLinearLS
{
private:


public:
	CLinearLS(void);
	~CLinearLS(void);
	void RunLinearLS( SELSensorPosition *pResult, SELPE_RESULT *pSensor, double *pLob, int nEle, EL_TARGET_STATE_OPTION eTargetState=STOP );

};

