/**
 * @brief 두 지점 -> 거리, 방위각 산출
 */

#pragma once

#define _USE_MATH_DEFINES

#include <math.h>

#include "VincentyParam.h" 	 

using namespace std;

namespace GEO {
	const double PIOVER2 = M_PI/2.0;
	const double TWOPI = 6.28318530718;
	const double DE2RA = 0.01745329252;
	const double RA2DE = 57.2957795129;
	const double ERAD = 6378.137;
	const double ERADM = 6378137.0;
	const double AVG_ERAD = 6371.0;
	const double FLATTENING = 1.000000/298.257223563;// Earth flattening (WGS84)
	const double EPS = 0.000000000005;
	const double KM2MI = 0.621371;
	const double GEOSTATIONARY_ALT = 35786.0; // km - approximate value
}

/**
* [식별자 : CLS-GMU-EL-L-PEA]
*
* [추적성 : SRS-G-SAFR-012]
*
* @class	CInverseMethod
* @brief	지표 관련 클래스
*
* (1) 클래스 설명
* - 본 클래스는 두 좌표간의 거리, 방위각 등을 계산해주는 클래스이다.
*
* (2) 설계결정사항
* - 위치 산출 라이브러리는 Geolocation_CLobsDll.dll 이다.
*
* (3) 제한 및 예외처리
* - 해당사항 없음
*/
class CInverseMethod
{
	
public:
	CInverseMethod( );
	~CInverseMethod( );

private:
	double m_dDistance;												///< 두 지점간의 거리 [km]
	double m_dFwdAz;													///< 방위각
	double m_dRevAz;													///< 방위각
	
public:
	bool VincentyInverse( sEllipsoid *e, double lat1, double lon1, double lat2, double lon2 );
	int VincentyInverse( SELDISTLOB *pResult, double lat1, double lon1, double lat2, double lon2 );

	//두 좌표간의 거리
	double GetDistance( ){ return m_dDistance; }

	//두 좌표에서 서로 바라보는 방위각
	double GetFwdAz( ){ return m_dFwdAz * R2D; }
	double GetRevAz( ){ return m_dRevAz * R2D; }

	double GCAzimuth(double lat1, double lon1, double lat2, double lon2, bool bInitialBearing=false );
	double GCDistance(double lat1, double lon1, double lat2, double lon2);
	double EllipsoidDistance(double lat1, double lon1, double lat2, double lon2);
};

