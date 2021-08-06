/**
 * @brief Vincenty's Formulae를 위한 파라미터들
 */
#pragma once

#include <iostream>

struct sEllipsoid
{
	double dMajorAxis; 	//장축(m)
	double dMinorAxis; 	//단축(m)
	double dFlatness; 	//편평도

	sEllipsoid() : dMajorAxis(0.), dMinorAxis(0.), dFlatness(0.)
	{

	}
};

#ifndef M_PI
#define M_PI ( 3.14159265358979323846 )
#endif

const double D2R = ( M_PI / 180.0 ); 
const double R2D = ( 180.0 / M_PI );

//Ellipsoid 종류에 따른 변환 파라미터
const double WGS84_MAJOR = 6378137.0;
const double WGS84_FLATNESS = 1 / 298.257223563;
const double WGS84_MINOR = WGS84_MAJOR * ( 1 - WGS84_FLATNESS );

const double GRS80_MAJOR = 6378137.0;
const double GRS80_FLATNESS = 1 / 298.257222101;
const double GRS80_MINOR = GRS80_MAJOR * ( 1 - GRS80_FLATNESS );

const double GRS67_MAJOR = 6378160.0;
const double GRS67_FLATNESS = 1 / 298.25;
const double GRS67_MINOR = GRS67_MAJOR * ( 1 - GRS67_FLATNESS );

const double ANS_MAJOR = 6378160.0;
const double ANS_FLATNESS = 1 / 298.25;
const double ANS_MINOR = ANS_MAJOR * ( 1 - ANS_FLATNESS );

const double WGS72_MAJOR = 6378135.0;
const double WGS72_FLATNESS = 1 / 298.26;
const double WGS72_MINOR = WGS72_MAJOR * ( 1 - WGS72_FLATNESS );

const double Clarke1858_MAJOR = 6378293.645;
const double Clarke1858_FLATNESS = 1 / 294.26;
const double Clarke1858_MINOR = Clarke1858_MAJOR * ( 1 - Clarke1858_FLATNESS );

const double Clarke1880_MAJOR = 6378249.145;
const double Clarke1880_FLATNESS = 1 / 293.465;
const double Clarke1880_MINOR = Clarke1880_MAJOR * ( 1 - Clarke1880_FLATNESS );

const double spherical_MAJOR = 6371000;
const double spherical_FLATNESS = 0.0;
const double spherical_MINOR = spherical_MAJOR * ( 1 - spherical_FLATNESS );

/*!
 * @typedef   SELDISTLOB
 * @brief			Inverse method 를 이용한 거리와 방위각
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @date      2013-09-09 오후 9:12
 */
struct SELDISTLOB {
	double dDistance;
	double fwdlob;
	double revlob;

	SELDISTLOB() {
		dDistance = 0.;
		fwdlob = 0.;
		revlob = 0.;
	}

} ;
