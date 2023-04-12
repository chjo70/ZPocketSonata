//////////////////////////////////////////////////////////////////////////
/*!
 * @file      AnalyticCEP.cpp
 * @brief     
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-09-09 오후 4:07 
 * @warning   
 */


#include "stdafx.h"

#define _USE_MATH_DEFINES

#include <math.h>

#include "../Matrix/Matrix.h"
#include "../UTM/UTM.h"
#include "../Coordinate/Coordinate.h"

#include "AnalyticCEP.h"

#include "../../SigAnal/_Type.h"


/**
 * @brief		객체를 생성합니다.
 * @param		void
 * @return		
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/03/16 14:36:56
 * @warning		
 */
CAnalyticCEP::CAnalyticCEP(void)
{
	//PrintFunction
	UINT i, nLob = 3;

	CMatrix theX((UINT)3, nLob), theInvW(nLob, nLob);

	for (i = 1; i <= nLob; ++i) {
		theX((UINT)1, (UINT)i) = (10 - i * 3) + i;
		theX((UINT)2, (UINT)i) = (10 - i * 2) + i;
		theX((UINT)3, (UINT)i) = (10 + i * 1) + i;
	}

#ifdef _MFC_VER
	//Log( enNormal, "CAnalyticCEP" );
	TRACE("\n CAnalyticCEP... ");

#endif


// 	CMatrix theQ, theXt;
// 
// 	theXt = theX.Transpose();
// 	theQ = theX * theXt;
// 	theQ.Print();
// 
// 	bool bRet;
// 	Inv(theXt, &bRet);

}

/**
 * @brief		객체를 소멸합니다.
 * @param		void
 * @return		
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/03/16 14:36:53
 * @warning		
 */
CAnalyticCEP::~CAnalyticCEP(void)
{
}


/**
 * @brief		CEP 계산을 수행한다.
 * @param		SELPE_RESULT * pResult
 * @return		bool
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/03/16 14:36:47
 * @warning		
 */
bool CAnalyticCEP::CalAnalyticNonlinear( SELPE_RESULT *pResult )
{
    int i;
    bool bRet=true;

    double sigma_doa=1.0, dSigma;

    double dM, dN, dDiv;

    double *pUTMX, *pUTMY;

    pUTMX = m_pUTMX;
    pUTMY = m_pUTMY;

    pResult->dEEP_major_axis = -1;
    pResult->dEEP_minor_axis = -1;
    pResult->dEEP_theta = -1;
    pResult->dCEP_error = -1;

    try
    {
        CMatrix theX( (UINT) 2, (UINT) m_nLob ), theInvW( (UINT) m_nLob, (UINT) m_nLob );

        for( i=1 ; i <= m_nLob ; ++i ) {
            dM = pResult->dEasting - *pUTMX;
            dN = pResult->dNorthing - *pUTMY;

            dDiv = ( dM * dM ) + ( dN * dN );
            theX( (UINT) 1, (UINT) i ) = dN / dDiv;
            theX((UINT) 2, (UINT) i ) = dM / dDiv;

            ++ pUTMX;
            ++ pUTMY;
        }

        theX.Print();

        //theInvW = ( 1. / sigma_doa * M_PI / 180. ) * theInvW.Ident(m_nLob, m_nLob );
        //theInvW.Print();
        dSigma = DEGREE2RADIAN( sigma_doa * sigma_doa );

        CMatrix theQ, theXt;

        theXt = theX.Transpose();
        theQ = theX * theXt;
        theQ.Print();

        theQ = Inv( theQ, & bRet );
        theQ.Print();

        theQ = dSigma * theQ;
        theQ.Print();

        double dPe = -2.0 * log( 1 - 0.5 );
        double dSigma_x_square, dSigma_y_square, dRho_xy, dA_square, dB_square, dSqaure;

        dSigma_x_square = theQ.Get( 1, 1 );
        dSigma_y_square = theQ.Get( 2, 2 );
        dRho_xy = theQ.Get( 2, 1 );

        dSqaure = ( dSigma_x_square - dSigma_y_square );
        dSqaure *= dSqaure;
        dSqaure += ( 4.0 * dRho_xy * dRho_xy );
        dA_square = 0.5 * ( dSigma_x_square + dSigma_y_square + sqrt( dSqaure ) );
        dB_square = 0.5 * ( dSigma_x_square + dSigma_y_square - sqrt( dSqaure ) );

        pResult->dEEP_theta = RADIAN2DEGREE( 0.5 * atan( ( 2. * dRho_xy ) / ( dSigma_x_square - dSigma_y_square ) ) );
        pResult->dEEP_theta = 90.0 - pResult->dEEP_theta;

        if( dA_square > dB_square ) {
            pResult->dEEP_major_axis = sqrt( dA_square * dPe ) / 1000. / 2.;
            pResult->dEEP_minor_axis = sqrt( dB_square * dPe ) / 1000. / 2.;
        }
        else {
            pResult->dEEP_major_axis = sqrt( dB_square * dPe ) / 1000. / 2.;
            pResult->dEEP_minor_axis = sqrt( dA_square * dPe ) / 1000. / 2.;
        }

        pResult->dCEP_error = 0.75 * sqrt( dA_square + dB_square ) / 1000.;
    }
    catch (Exception err) {
        bRet = false;
        printf("Error: %s\n", err.msg);
    }
    catch (...) {
        bRet = false;
        printf("An error occured...\n");
    }

    return bRet;

}
