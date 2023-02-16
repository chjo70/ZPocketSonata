// GeoCoordConv.h: interface for the CGeoCoordConv class.
//
//////////////////////////////////////////////////////////////////////
// 이 라이브러리는 신상희님의 비쥬얼 베이직 소스를 바탕으로 
// 타프 시스템의 장병진이 C++로 바꾸면서 클래스화 한 것입니다.

// 다음은 원작자의 설명입니다.
// 프로그램은 미국 USGS에서 나온 GCTP(General Cartographic Transformation Program)
// 을 많이 참고하여 만든 것입니다.
// C로 작성되어 있는 GCTP 프로그램은 ftp://edcftp.cr.usgs.gov/pub/software/gctpc/
// 에 접속해 보시면 찾으실 수 있습니다.
// 타원체 변환 루틴은 미국 NIMA와 몇몇 책들을 참고하여 제가 작성하였습니다.
// 변환식은 Molodensky Datum 변환식을 사용하였습니다.
//
  
// 이 소스는 상업적 목적이 아니라면 자유롭게 수정, 배포하실 수 있습니다.
// 다만 상업적 목적으로 사용할 경우에는 반드시 출처를 명시하셔야 합니다.


#if !defined(AFX_GEOCOORDCONV_H__0111FA14_9C35_4356_A57F_4516F949DC5A__INCLUDED_)
#define AFX_GEOCOORDCONV_H__0111FA14_9C35_4356_A57F_4516F949DC5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../SigAnal/_Type.h"

#define _USE_MATH_DEFINES

#include <math.h>

#define D2R(degree) (degree * M_PI / 180.0)
#define R2D(radian) (radian * 180.0 / M_PI)

enum GeoEllips {kBessel1984 = 0, kWgs84 = 1};
enum GeoSystem {kGeographic = 0, kTmWest = 1, kTmMid = 2, kTmEast = 3, kKatec = 4, kUtm52 = 5, kUtm51 = 6};

class CGeoCoordConv  
{
public:
	CGeoCoordConv(
		GeoEllips eSrcEllips = kBessel1984, 
		GeoSystem eSrcSystem = kGeographic,
		GeoEllips eDstEllips = kBessel1984, 
		GeoSystem eDstSystem = kTmMid
		);

	// Set Internal Values
	void SetSrcType(GeoEllips eEllips, GeoSystem eSystem);
	void SetDstType(GeoEllips eEllips, GeoSystem eSystem);

	// Main Convert Function
	void Conv(double dInX, double dInY, double& dOutX, double& dOutY);
	// Global Utility Function
	static void D2Dms(double dInDecimalDegree, int& iOutDegree, int& iOutMinute, double& dOutSecond);

protected:
	void DatumTrans(double dInLon, double dInLat, double& dOutLon, double& dOutLat);
	void Geo2Tm(double lon, double lat, double& x, double& y);
	void Tm2Geo(double x, double y, double& lon, double& lat);

	// Ellips/System Type
	GeoEllips m_eSrcEllips;
	GeoSystem m_eSrcSystem;
	GeoEllips m_eDstEllips;
	GeoSystem m_eDstSystem;

	// Ellips Factor List
	double m_arMajor[2];
	double m_arMinor[2];

	// System Factor List 
	double m_arScaleFactor[7];
	double m_arLonCenter[7];
	double m_arLatCenter[7];
	double m_arFalseNorthing[7];
	double m_arFalseEasting[7];
	
private:
	void InitDatumVar();
	double asinz(double value);
	double e0fn(double es);
	double e1fn(double es);
	double e2fn(double es);
	double e3fn(double es);
	double e4fn(double es);
	double mlfn(double e0, double e1, double e2, double e3, double phi);

	// Internal Value for Tm2Geo
	double m_dSrcE0, m_dSrcE1, m_dSrcE2, m_dSrcE3;
	double m_dSrcE, m_dSrcEs, m_dSrcEsp;
	double m_dSrcMl0, m_dSrcInd;

	// Internal Value for Geo2Tm
	double m_dDstE0, m_dDstE1, m_dDstE2, m_dDstE3;
	double m_dDstE, m_dDstEs, m_dDstEsp;
	double m_dDstMl0, m_dDstInd;

	// Internal Value for DatumTrans
	double m_dTemp;
	double m_dEsTemp;
	int m_iDeltaX;
	int m_iDeltaY;
	int m_iDeltaZ;
	double m_dDeltaA, m_dDeltaF;

};

#endif // !defined(AFX_GEOCOORDCONV_H__0111FA14_9C35_4356_A57F_4516F949DC5A__INCLUDED_)
