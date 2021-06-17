//////////////////////////////////////////////////////////////////////////
/*!
 * @file      CInverseMethod.cpp
 * @brief     지구의 위경도 및 방위각 관련 클래스
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-09-14 오후 4:35
 * @warning
 */


#include "stdafx.h"


#include "../../SigAnal/_Type.h"

#include "CInverseMethod.h"

//#include "../Geo2UTM/Geo2UTM.h"

CInverseMethod*  CInverseMethod::m_pInstance = 0;				///< 정적 초기화


/**
 * @brief     지구의 위경도 및 방위각 관련 객체를 생성한다.
 * @param     void
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-03-07, 오후 6:46
 * @warning
 */
CInverseMethod::CInverseMethod()
{
	m_dDistance = 0.0;
	m_dFwdAz = 0.0;
	m_dRevAz = 0.0;

	double lat1, lon1, lat2, lon2;

	// 타겟 : 왕산
	lat2 = 37.4692;
	lon2 = 126.3625;

	double doa;

	// 신불
	lat1 = 37.4528;
	lon1 = 126.4839;
	doa = GCAzimuth(lat1, lon1, lat2, lon2, true );

	// 관제수신소
	lat1 = 37.4859;
	lon1 = 126.4587;
	doa = GCAzimuth(lat1, lon1, lat2, lon2, true );

	// 소방대분소
	lat1 = 37.45348;
	lon1 = 126.42333;
	doa = GCAzimuth(lat1, lon1, lat2, lon2, true );
}

/**
 * @brief     객체 소멸자를 처리한다.
 * @param     void
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-03-07, 오후 6:46
 * @warning
 */
CInverseMethod::~CInverseMethod( )
{
	// 소멸자에세 객체를 메모리에서 해지함.

}

/**
 * @brief     Finalize
 * @param     void
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-03-07, 오후 6:49
 * @warning
 */
void CInverseMethod::Finalize()
{
	delete m_pInstance;
}


//////////////////////////////////////////////////////////////////////////
/*!
 * @brief     객체를 생성한다.
 * @param     void
 * @return    CInverseMethod *
 * @version   0.0.1
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-09-09 오후 8:56
 * @warning
 */
CInverseMethod* CInverseMethod::GetInstance()
{
	if( m_pInstance == NULL ) {
		m_pInstance = new CInverseMethod();
	}

	return m_pInstance;
}

/**
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
 Vincenty Inverse Solution of Geodesics on the Ellipsoid (c) Chris Veness 2002-2011

 from: Vincenty inverse formula - T Vincenty, "Direct and Inverse Solutions of Geodesics on the
       Ellipsoid with application of nested equations", Survey Review, vol XXII no 176, 1975
       http://www.ngs.noaa.gov/PUBS_LIB/inverse.pdf
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 * Calculates geodetic distance between two points specified by latitude/longitude using
 * Vincenty inverse formula for ellipsoids
 *
 * source: http://www.movable-type.co.uk/scripts/latlong-vincenty.html
 *
 * e pointer to ellipsoid struct
 * lat, lon in radians,
 * fwdAz, revAz in radians,
 * s in meters
 *
*/

/**
 * @brief     위경도만 타원체 정보만 입력하도록 수정
 * @param     sEllipsoid * e
 * @param     double lat1
 * @param     double lon1
 * @param     double lat2
 * @param     double lon2
 * @return    int
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-03-07, 오후 6:46
 * @warning
 */
bool CInverseMethod::VincentyInverse( sEllipsoid *e, double lat1, double lon1, double lat2, double lon2 )	//#FA_Q_4020_T1
{

	lat1 = lat1 * D2R;
	lon1 = lon1 * D2R;
	lat2 = lat2 * D2R;
	lon2 = lon2 * D2R;

	double L = (lon2 - lon1);
	double U1 = atan((1 - e->dFlatness) * tan(lat1));
	double U2 = atan((1 - e->dFlatness) * tan(lat2));
	double sinU1 = sin(U1), cosU1 = cos(U1);
	double sinU2 = sin(U2), cosU2 = cos(U2);

	double lambda = L, lambdaP;
	int iterLimit = 100;
	double cosSqAlpha, cosSigma, sigma, cos2SigmaM, sinLambda, sinSigma, cosLambda, sinAlpha;
	double eps = 1000;
	do
	{
		sinLambda = sin(lambda);
		cosLambda = cos(lambda);
		sinSigma = sqrt( (cosU2 * sinLambda) * (cosU2 * sinLambda) + (cosU1 * sinU2 - sinU1 * cosU2 * cosLambda) * (cosU1 * sinU2 - sinU1 * cosU2 * cosLambda));
		if ( ! ( sinSigma > 0 || sinSigma < 0 ) )
		{	//DTEC_Else
			m_dDistance = 0.0;
			return true;
		}

		cosSigma = sinU1 * sinU2 + cosU1 * cosU2 * cosLambda;
		sigma = atan2(sinSigma, cosSigma);
		sinAlpha = cosU1 * cosU2 * sinLambda / sinSigma;
		cosSqAlpha = 1 - sinAlpha * sinAlpha;
		cos2SigmaM = cosSigma - 2 * sinU1 * sinU2 / cosSqAlpha;

		double C = e->dFlatness / 16 * cosSqAlpha * (4 + e->dFlatness * (4 - 3 * cosSqAlpha));
		lambdaP = lambda;
		lambda = L + (1 - C) * e->dFlatness * sinAlpha * (sigma + C * sinSigma * (cos2SigmaM + C * cosSigma * ( -1 + 2 * cos2SigmaM * cos2SigmaM)));
		eps = fabs(lambda - lambdaP);
	}
	while (eps > 1e-12 && --iterLimit > 0);

	if (iterLimit == 0) { //DTEC_Else
		return false; // formula failed to converge
	}

	double uSq = cosSqAlpha * (e->dMajorAxis * e->dMajorAxis - e->dMinorAxis * e->dMinorAxis) / (e->dMinorAxis * e->dMinorAxis);
	double A = 1 + uSq / 16384 * (4096 + uSq * (-768 + uSq * (320 - 175 * uSq)));
	double B = uSq / 1024 * (256 + uSq * (-128 + uSq * (74 - 47 * uSq)));
	double deltaSigma = B * sinSigma * ( cos2SigmaM + B / 4 * ( cosSigma * (-1 + 2 * cos2SigmaM * cos2SigmaM ) - B / 6 * cos2SigmaM * ( -3 + 4 * sinSigma * sinSigma) * (-3 + 4 * cos2SigmaM * cos2SigmaM)));
	double _s = e->dMinorAxis * A * (sigma - deltaSigma);

	double _fwdAz = atan2(cosU2 * sinLambda, cosU1 * sinU2 - sinU1 * cosU2 * cosLambda); //y,x
	double _revAz = atan2(cosU1 * sinLambda, -sinU1 * cosU2 + cosU1 * sinU2 * cosLambda);

	if( _fwdAz < 0.0 ) { //DTEC_Else
		_fwdAz = _fwdAz + M_PI + M_PI;
	}

	if( _revAz < 0.0 ) { //DTEC_Else
		_revAz = _revAz + M_PI + M_PI;
	}

	m_dDistance =  _s;
	m_dFwdAz = _fwdAz;
	m_dRevAz = _revAz;

	return true;
}

//////////////////////////////////////////////////////////////////////////
/*!
 * @brief     도분초에 대한 방위각과 거리를 리턴
 * @param     SELDISTLOB * pResult
 * @param     double lat1 (도분초)
 * @param     double lon1 (도분초)
 * @param     double lat2 (도분초)
 * @param     double lon2 (도분초)
 * @return    int
 * @version   0.0.1
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-09-09 오후 9:14
 * @warning
 */
int CInverseMethod::VincentyInverse( SELDISTLOB *pResult, double lat1, double lon1, double lat2, double lon2 )
{
	int bRet;
	sEllipsoid stEllipsoid=sEllipsoid(); //타원체 정의

	stEllipsoid.dMajorAxis = WGS84_MAJOR;
	stEllipsoid.dMinorAxis = WGS84_MINOR;
	stEllipsoid.dFlatness = WGS84_FLATNESS;

	bRet = VincentyInverse( & stEllipsoid, lat1, lon1, lat2, lon2 );
	pResult->dDistance = m_dDistance;
	pResult->fwdlob = m_dFwdAz * R2D;
	pResult->revlob = m_dRevAz * R2D;

	return bRet;

}

/**
 * @brief     두 지점의 거리를 계산한다.
 * @param     double lat1
 * @param     double lon1
 * @param     double lat2
 * @param     double lon2
 * @return    double
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2017-03-07, 오후 6:46
 * @warning
 */
double CInverseMethod::EllipsoidDistance(double lat1, double lon1, double lat2, double lon2)
{
	double dDistance = 0.0;
	double  faz, baz;
	double  r = 1.0 - GEO::FLATTENING;
	double  tu1, tu2, cu1, su1, cu2, x, sx, cx, sy, cy, y, sa, c2a, cz, e, c, d;
	double  cosy1, cosy2;
	dDistance = 0.0;

	//if( (lon1 == lon2) && (lat1 == lat2)) {
	if( ! ( lon1 > lon2 || lon1 < lon2 ) && ! ( lat1 > lat2 || lat1 < lat2 ) ) {
		dDistance = 0.0;
	}
	else {

		lon1 *= GEO::DE2RA;
		lon2 *= GEO::DE2RA;
		lat1 *= GEO::DE2RA;
		lat2 *= GEO::DE2RA;

		cosy1 = cos(lat1);
		cosy2 = cos(lat2);

		if( ! ( cosy1 < 0 || cosy1 > 0 ) ) {
			cosy1 = 0.0000000001;
		}
		//if(cosy1 == 0.0) cosy1 = 0.0000000001;
		if( ! ( cosy2 < 0 || cosy2 > 0 ) ) {
			cosy2 = 0.0000000001;
		}
		//if(cosy2 == 0.0) cosy2 = 0.0000000001;

		tu1 = r * sin(lat1) / cosy1;
		tu2 = r * sin(lat2) / cosy2;
		cu1 = 1.0 / sqrt(tu1 * tu1 + 1.0);
		su1 = cu1 * tu1;
		cu2 = 1.0 / sqrt(tu2 * tu2 + 1.0);
		x = lon2 - lon1;

		dDistance = cu1 * cu2;
		baz = dDistance * tu2;
		faz = baz * tu1;

		do	{
			sx = sin(x);
			cx = cos(x);
			tu1 = cu2 * sx;
			tu2 = baz - su1 * cu2 * cx;
			sy = sqrt(tu1 * tu1 + tu2 * tu2);
			cy = dDistance * cx + faz;
			y = atan2(sy, cy);
			sa = dDistance * sx / sy;
			c2a = -sa * sa + 1.0;
			cz = faz + faz;
			if(c2a > 0.0) {
				cz = -cz / c2a + cy;
			}
			e = cz * cz * 2. - 1.0;
			c = ((-3.0 * c2a + 4.0) * GEO::FLATTENING + 4.0) * c2a * GEO::FLATTENING / 16.0;
			d = x;
			x = ((e * cy * c + cz) * sy * c + y) * sa;
			x = (1.0 - c) * x * GEO::FLATTENING + lon2 - lon1;
		} while(fabs(d - x) > GEO::EPS);

		x = sqrt((1.0 / r / r - 1.0) * c2a + 1.0) + 1.0;
		x = (x - 2.0) / x;
		c = 1.0 - x;
		c = (x * x / 4.0 + 1.0) / c;
		d = (0.375 * x * x - 1.0) * x;
		x = e * cy;
		dDistance = 1.0 - e - e;
		dDistance = ((((sy * sy * 4.0 - 3.0) * dDistance * cz * d / 6.0 - x) * d / 4.0 + cz) * sy * d + y) * c * GEO::ERAD * r;
	}

	return dDistance;
}

/**
 * @brief     두 지점에서의 방위 편차를 계산한다.
 * @param     double lat1
 * @param     double lon1
 * @param     double lat2
 * @param     double lon2
 * @return    double
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2018-05-21, 오후 2:03
 * @warning
 */
double CInverseMethod::GCAzimuth(double lat1, double lon1, double lat2, double lon2, bool bInitialBearing)	//#FA_Q_4020_T1
{
	double result = 0.0;

	INT32 ilat1 = (INT32)(0.50 + lat1 * 360000.0);
	INT32 ilat2 = (INT32)(0.50 + lat2 * 360000.0);
	INT32 ilon1 = (INT32)(0.50 + lon1 * 360000.0);
	INT32 ilon2 = (INT32)(0.50 + lon2 * 360000.0);

	lat1 *= GEO::DE2RA;
	lon1 *= GEO::DE2RA;
	lat2 *= GEO::DE2RA;
	lon2 *= GEO::DE2RA;

	if ((ilat1 == ilat2) && (ilon1 == ilon2))
	{	//DTEC_Else
		return result;
	}
	else if (ilon1 == ilon2)
	{	//DTEC_Else
		if (ilat1 > ilat2) { //DTEC_Else
			result = 180.0;
		}
	}
	else
	{
		if( bInitialBearing == true ) {
			double angle = atan2(cos(lat2) * sin(lon2 - lon1), sin(lat2) * cos(lat1) - sin(lat1) * cos(lat2) * cos(lon2 - lon1));
			result = (angle * GEO::RA2DE);
			result += ( 360.0 * 2 );
			result = fmod( result, 360.0 );
		}
		else {
			double angle = atan2(cos(lat1) * sin(lon1 - lon2), sin(lat1) * cos(lat2) - sin(lat2) * cos(lat1) * cos(lon1 - lon2));
			result = (angle * GEO::RA2DE);
			result += ( 360.0 * 2 );
			result += ( 180.0 );
			result = fmod( result, 360.0 );
		}
	}

	return result;
}

#define RADIUS_OF_EARTH			(6371e3)
double CInverseMethod::GCDistance(double lat1, double lon1, double lat2, double lon2)
{
	double dLat, dLon;
	double result = 0.0;
	double dLatSin, dLonSin;

	lat1 *= GEO::DE2RA;
	lon1 *= GEO::DE2RA;
	lat2 *= GEO::DE2RA;
	lon2 *= GEO::DE2RA;

	dLat = ( lat2 - lat1 );
	dLon = ( lon2 - lon1 );

	dLatSin = sin( dLat / 2.0 );
	dLonSin = sin( dLon / 2.0 );
	double angle = dLatSin * dLatSin + cos( lat1 ) * cos( lat2 ) * dLonSin * dLonSin;

	result = RADIUS_OF_EARTH * ( 2.0 * atan2( sqrt(angle), sqrt(1-angle) ) );

	return result;
}


