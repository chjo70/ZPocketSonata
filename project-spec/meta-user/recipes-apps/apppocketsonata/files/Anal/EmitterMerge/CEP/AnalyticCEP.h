#pragma once

#include "../PositionEstimation.h"

class CAnalyticCEP
{
protected:
    int m_nLob;

    double *m_pUTMX;
    double *m_pUTMY;

public:
    CAnalyticCEP(void);
    ~CAnalyticCEP(void);

    bool CalAnalyticNonlinear( SELPE_RESULT *pResult );
};

