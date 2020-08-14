// GeoCoordConv.cpp: implementation of the CGeoCoordConv class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "GeoCoordConv.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define PI 3.14159265358979
#define EPSLN 0.0000000001
#define S2R 4.84813681109536E-06 // sin(1")

#define X_W2B 128
#define Y_W2B -481
#define Z_W2B -664

//////////////////////////////////////////////////////////////////////
// Construction
//////////////////////////////////////////////////////////////////////
CGeoCoordConv::CGeoCoordConv(GeoEllips eSrcEllips, GeoSystem eSrcSystem, 
							 GeoEllips eDstEllips, GeoSystem eDstSystem)
{
	// Set Type Factor
	m_eSrcEllips = eSrcEllips;
	m_eSrcSystem = eSrcSystem;
	m_eDstEllips = eDstEllips;
	m_eDstSystem = eDstSystem;

	SetSrcType(eSrcEllips, eSrcSystem);
	SetDstType(eDstEllips, eDstSystem);

    // Set Ellips factor
	m_arMajor[kBessel1984] = 6377397.155;
	m_arMinor[kBessel1984] = 6356078.96325;

	m_arMajor[kWgs84] = 6378137.0;
	m_arMinor[kWgs84] = 6356752.3142;
    
	// Set System Factor
	m_arScaleFactor[kGeographic] = 1;
	m_arLonCenter[kGeographic] = 0.0;
	m_arLatCenter[kGeographic] = 0.0;
	m_arFalseNorthing[kGeographic] = 0.0;
	m_arFalseEasting[kGeographic] = 0.0;

	m_arScaleFactor[kTmWest] = 1;
	m_arLonCenter[kTmWest] = 2.18171200985643;
	m_arLatCenter[kTmWest] = 0.663225115757845;
	m_arFalseNorthing[kTmWest] = 500000.0;
	m_arFalseEasting[kTmWest] = 200000.0;

	m_arScaleFactor[kTmMid] = 1;
	m_arLonCenter[kTmMid] = 2.21661859489632;
	m_arLatCenter[kTmMid] = 0.663225115757845;
	m_arFalseNorthing[kTmMid] = 500000.0;
	m_arFalseEasting[kTmMid] = 200000.0;

	m_arScaleFactor[kTmEast] = 1;
	m_arLonCenter[kTmEast] = 2.2515251799362;
	m_arLatCenter[kTmEast] = 0.663225115757845;
	m_arFalseNorthing[kTmEast] = 500000.0;
	m_arFalseEasting[kTmEast] = 200000.0;

	m_arScaleFactor[kKatec] = 0.9999;
	m_arLonCenter[kKatec] = 2.23402144255274;
	m_arLatCenter[kKatec] = 0.663225115757845;
	m_arFalseNorthing[kKatec] = 600000.0;
	m_arFalseEasting[kKatec] = 400000.0;

	m_arScaleFactor[kUtm52] = 0.9996;
	m_arLonCenter[kUtm52] = 2.25147473507269;
	m_arLatCenter[kUtm52] = 0.0;
	m_arFalseNorthing[kUtm52] = 0.0;
	m_arFalseEasting[kUtm52] = 500000.0;

	m_arScaleFactor[kUtm51] = 0.9996;
	m_arLonCenter[kUtm51] = 2.14675497995303;
	m_arLatCenter[kUtm51] = 0.0;
	m_arFalseNorthing[kUtm51] = 0.0;
	m_arFalseEasting[kUtm51] = 500000.0;
}

///////////////////////////////////////////////
// Set Internal Values
void CGeoCoordConv::SetSrcType(enum GeoEllips eEllips, enum GeoSystem eSystem)
{
	m_eSrcEllips = eEllips;
	m_eSrcSystem = eSystem;

	double temp = m_arMinor[m_eSrcEllips] / m_arMajor[m_eSrcEllips];
	m_dSrcEs = 1.0 - temp * temp;
	m_dSrcE = sqrt(m_dSrcEs);
	m_dSrcE0 = e0fn(m_dSrcEs);
	m_dSrcE1 = e1fn(m_dSrcEs);
	m_dSrcE2 = e2fn(m_dSrcEs);
	m_dSrcE3 = e3fn(m_dSrcEs);
	m_dSrcMl0 = m_arMajor[m_eSrcEllips] * mlfn(m_dSrcE0, m_dSrcE1, m_dSrcE2, m_dSrcE3, m_arLatCenter[m_eSrcSystem]);
	m_dSrcEsp = m_dSrcEs / (1.0 - m_dSrcEs);

	if (m_dSrcEs < 0.00001)
	   m_dSrcInd = 1.0;
	else
	   m_dSrcInd = 0.0;

	InitDatumVar();
}

// Set Internal Values
void CGeoCoordConv::SetDstType(enum GeoEllips eEllips, enum GeoSystem eSystem)
{
	m_eDstEllips = eEllips;
	m_eDstSystem = eSystem;

	double temp = m_arMinor[m_eDstEllips] / m_arMajor[m_eDstEllips];
	m_dDstEs = 1.0 - temp * temp;
	m_dDstE = sqrt(m_dDstEs);
	m_dDstE0 = e0fn(m_dDstEs);
	m_dDstE1 = e1fn(m_dDstEs);
	m_dDstE2 = e2fn(m_dDstEs);
	m_dDstE3 = e3fn(m_dDstEs);
	m_dDstMl0 = m_arMajor[m_eDstEllips] * mlfn(m_dDstE0, m_dDstE1, m_dDstE2, m_dDstE3, m_arLatCenter[m_eDstSystem]);
	m_dDstEsp = m_dDstEs / (1.0 - m_dDstEs);

	if (m_dDstEs < 0.00001)
	   m_dDstInd = 1.0;
	else
	   m_dDstInd = 0.0;

	InitDatumVar();
}

///////////////////////////////////////////
// Main Convert Function
void CGeoCoordConv::Conv(double dInX, double dInY, double& dOutX, double& dOutY)
{
	double dInLon, dInLat;
	double dOutLon, dOutLat;

	double dTmX, dTmY;

	// Convert to Radian Geographic
	if (m_eSrcSystem == kGeographic)
	{
		dInLon = D2R(dInX);
		dInLat = D2R(dInY);
	}
	else
	{
		// Geographic calculating
		Tm2Geo(dInX, dInY, dInLon, dInLat);
	}

	if (m_eSrcEllips == m_eDstEllips)
	{
		dOutLon = dInLon;
		dOutLat = dInLat;
	}
	else 
	{
		// Datum transformation using molodensky function
		DatumTrans(dInLon, dInLat, dOutLon, dOutLat);
	}

	// now we should make a output. but it depends on user options
	if (m_eDstSystem == kGeographic) // if output option is latitude & longitude
	{
		dOutX = R2D(dOutLon);
		dOutY = R2D(dOutLat);
	}
	else // if output option is cartesian systems
    {
		// TM or UTM calculating
		Geo2Tm(dOutLon, dOutLat, dTmX, dTmY);

		dOutX = dTmX;
		dOutY = dTmY;
    }
}

/////////////////////////////////////////////
// Global Utility Function
void CGeoCoordConv::D2Dms(double dInDecimalDegree, int &iOutDegree, int &iOutMinute, double &dOutSecond)
{
	double dTmpMinute;

	iOutDegree = (int)dInDecimalDegree;
	dTmpMinute = (dInDecimalDegree - iOutDegree) * 60.0;
	iOutMinute = (int)dTmpMinute;
	dOutSecond = (dTmpMinute - iOutMinute) * 60.0;
	if ((dOutSecond+0.00001) >= 60.0)
	{
		if (iOutMinute == 59)
		{
			iOutDegree++;
			iOutMinute = 0;
			dOutSecond = 0.0;
		}
		else {
			iOutMinute++;
			dOutSecond = 0.0;
		}
	}
}


// Molodensky Datum Transformation function for general datum transformation.
// Coded by Shin, Sanghee(endofcap@geo.giri.co.kr) 24th Feb, 1999
// Reference manual : DEFENSE MAPPING AGENCY TECHNICAL MANUAL 8358.1
// You can read above manual in this home page. http://164.214.2.59/GandG/tm83581/toc.htm
// Converted to C++ by Jang, Byyng-jin(jangbi@taff.co.kr) 20th Ap
void CGeoCoordConv::DatumTrans(double dInLon, double dInLat, double& dOutLon, double& dOutLat)
{
	double dRm, dRn;
	double dDeltaPhi, dDeltaLamda;
//	double dDeltaH;

	dRm = m_arMajor[m_eSrcEllips] * (1.0-m_dEsTemp) / pow(1.0-m_dEsTemp*sin(dInLat)*sin(dInLat), 1.5);
	dRn = m_arMajor[m_eSrcEllips] / sqrt(1.0 - m_dEsTemp*sin(dInLat)*sin(dInLat));

	dDeltaPhi = ((((-m_iDeltaX*sin(dInLat)*cos(dInLon) - m_iDeltaY*sin(dInLat)*sin(dInLon)) + m_iDeltaZ*cos(dInLat)) + m_dDeltaA*dRn*m_dEsTemp*sin(dInLat)*cos(dInLat)/m_arMajor[m_eSrcEllips]) + m_dDeltaF*(dRm/m_dTemp+dRn*m_dTemp)*sin(dInLat)*cos(dInLat))/dRm;
	dDeltaLamda = (-m_iDeltaX * sin(dInLon) + m_iDeltaY * cos(dInLon)) / (dRn * cos(dInLat));
//	dDeltaH = iDeltaX * cos(dInLat) * cos(dInLon) + iDeltaY * cos(dInLat) * sin(dInLon) + iDeltaZ * sin(dInLat) - dDeltaA * m_arMajor[eSrcEllips] / dRn + dDeltaF * dTemp * dRn * sin(dInLat) * sin(dInLat);

	dOutLat = dInLat + dDeltaPhi;
	dOutLon = dInLon + dDeltaLamda;
}

// function for converting longitude, latitude to TM X, Y
void CGeoCoordConv::Geo2Tm(double lon, double lat, double& x, double& y)
{
	double delta_lon; // Delta longitude (Given longitude - center longitude)
	double sin_phi, cos_phi; // sin and cos value
	double al, als; // temporary values
	double b, c, t, tq; // temporary values
	double con, n, ml; // cone constant, small m

	// LL to TM Forward equations from here
	delta_lon = lon - m_arLonCenter[m_eDstSystem];
	sin_phi = sin(lat);
	cos_phi = cos(lat);

	if (m_dDstInd != 0) 
	{
		b = cos_phi * sin(delta_lon);
		if ((fabs(fabs(b) - 1.0)) < 0.0000000001)
		{
			throw (CString)"지정하신 점이 무한대로 갑니다";
		}
	}
	else 
	{
		b = 0;
		x = 0.5 * m_arMajor[m_eDstEllips] * m_arScaleFactor[m_eDstSystem] * log((1.0 + b) / (1.0 - b));
		con = acos(cos_phi * cos(delta_lon) / sqrt(1.0 - b * b));
		if (lat < 0)
		{
		con = -con;
		y = m_arMajor[m_eDstEllips] * m_arScaleFactor[m_eDstSystem] * (con - m_arLatCenter[m_eDstSystem]);
		}
	}

	al = cos_phi * delta_lon;
	als = al * al;
	c = m_dDstEsp * cos_phi * cos_phi;
	tq = tan(lat);
	t = tq * tq;
	con = 1.0 - m_dDstEs * sin_phi * sin_phi;
	n = m_arMajor[m_eDstEllips] / sqrt(con);
	ml = m_arMajor[m_eDstEllips] * mlfn(m_dDstE0, m_dDstE1, m_dDstE2, m_dDstE3, lat);

	x = m_arScaleFactor[m_eDstSystem] * n * al * (1.0 + als / 6.0 * (1.0 - t + c + als / 20.0 * (5.0 - 18.0 * t + t * t + 72.0 * c - 58.0 * m_dDstEsp))) + m_arFalseEasting[m_eDstSystem];
	y = m_arScaleFactor[m_eDstSystem] * (ml - m_dDstMl0 + n * tq * (als * (0.5 + als / 24.0 * (5.0 - t + 9.0 * c + 4.0 * c * c + als / 30.0 * (61.0 - 58.0 * t + t * t + 600.0 * c - 330.0 * m_dDstEsp))))) + m_arFalseNorthing[m_eDstSystem];
}

// function for converting TM X,Y to Longitude and Latitude
void CGeoCoordConv::Tm2Geo(double x, double y, double& lon, double& lat)
{

	double con; // temporary angles
	double phi; // temporary angles
	double delta_Phi; // difference between longitudes
	long i; // counter variable
	double sin_phi, cos_phi, tan_phi; // sin cos and tangent values
	double c, cs, t, ts, n, r, d, ds; // temporary variables
	double f, h, g, temp; // temporary variables

	const long max_iter = 6; // maximun number of iterations

	if (m_dSrcInd != 0)
	{
		f = exp(x / (m_arMajor[m_eSrcEllips] * m_arScaleFactor[m_eSrcSystem]));
		g = 0.5 * (f - 1.0 / f);
		temp = m_arLatCenter[m_eSrcSystem] + y / (m_arMajor[m_eSrcEllips] * m_arScaleFactor[m_eSrcSystem]);
		h = cos(temp);
		con = sqrt((1.0 - h * h) / (1.0 + g * g));
		lat = asinz(con);

		if (temp < 0) 
			lat *= -1;

		if ((g == 0) && (h == 0))
			lon = m_arLonCenter[m_eSrcSystem];
		else
			lon = atan(g / h) + m_arLonCenter[m_eSrcSystem];
	}

	// TM to LL inverse equations from here
  
	x -= m_arFalseEasting[m_eSrcSystem];
	y -= m_arFalseNorthing[m_eSrcSystem];

	con = (m_dSrcMl0 + y / m_arScaleFactor[m_eSrcSystem]) / m_arMajor[m_eSrcEllips];
	phi = con;

	i = 0;
	while(TRUE)
	{
		delta_Phi = ((con + m_dSrcE1 * sin(2.0 * phi) - m_dSrcE2 * sin(4.0 * phi) + m_dSrcE3 * sin(6.0 * phi)) / m_dSrcE0) - phi;
		phi = phi + delta_Phi;
		if (fabs(delta_Phi) <= EPSLN) break;

		if (i >= max_iter) 
			throw (CString)"Latitude failed to converge";

		i++;
	}

	if (fabs(phi) < (PI / 2))
	{
		sin_phi = sin(phi);
		cos_phi = cos(phi);
		tan_phi = tan(phi);
		c = m_dSrcEsp * cos_phi * cos_phi;
		cs = c * c;
		t = tan_phi * tan_phi;
		ts = t * t;
		con = 1.0 - m_dSrcEs * sin_phi * sin_phi;
		n = m_arMajor[m_eSrcEllips] / sqrt(con);
		r = n * (1.0 - m_dSrcEs) / con;
		d = x / (n * m_arScaleFactor[m_eSrcSystem]);
		ds = d * d;
		lat = phi - (n * tan_phi * ds / r) * (0.5 - ds / 24.0 * (5.0 + 3.0 * t + 10.0 * c - 4.0 * cs - 9.0 * m_dSrcEsp - ds / 30.0 * (61.0 + 90.0 * t + 298.0 * c + 45.0 * ts - 252.0 * m_dSrcEsp - 3.0 * cs)));
		lon = m_arLonCenter[m_eSrcSystem] + (d * (1.0 - ds / 6.0 * (1.0 + 2.0 * t + c - ds / 20.0 * (5.0 - 2.0 * c + 28.0 * t - 3.0 * cs + 8.0 * m_dSrcEsp + 24.0 * ts))) / cos_phi);
	}
	else
	{
		lat = PI*0.5 * sin(y);
		lon = m_arLonCenter[m_eSrcSystem];
	}
}

//////////////////////////////////////////
// Internal Value calculation Function
double CGeoCoordConv::e0fn(double x)
{
	return 1.0 - 0.25 * x * (1.0 + x / 16.0 * (3.0 + 1.25 * x));
}

double CGeoCoordConv::e1fn(double x)
{
	return 0.375 * x * (1.0 + 0.25 * x * (1.0 + 0.46875 * x));
}

double CGeoCoordConv::e2fn(double x)
{
	return 0.05859375 * x * x * (1.0 + 0.75 * x);
}

double CGeoCoordConv::e3fn(double x)
{
	return x * x * x * (35.0 / 3072.0);
}

double CGeoCoordConv::e4fn(double x)
{
	double con, com;

    con = 1.0 + x;
    com = 1.0 - x;
    return sqrt(pow(con, con) * pow(com, com));
}

double CGeoCoordConv::mlfn(double e0, double e1, double e2, double e3, double phi)
{
	return e0 * phi - e1 * sin(2.0 * phi) + e2 * sin(4.0 * phi) - e3 * sin(6.0 * phi);
}

double CGeoCoordConv::asinz(double value)
{
    if (fabs(value) > 1.0)
		value = (value>0?1:-1);
    
    return asin(value);
}

void CGeoCoordConv::InitDatumVar()
{
	int iDefFact;
	double dF;

	// direction factor for datum transformation
	// eg) Bessel to Bessel would be 0
	//     WGS84 to Bessel would be 1
	//     BEssel to WGS84 would be -1
	iDefFact = m_eSrcEllips - m_eDstEllips;
	m_iDeltaX = iDefFact * X_W2B;
	m_iDeltaY = iDefFact * Y_W2B;
	m_iDeltaZ = iDefFact * Z_W2B;
	
	m_dTemp = m_arMinor[m_eSrcEllips] / m_arMajor[m_eSrcEllips];
	dF = 1.0 - m_dTemp; // flattening
	m_dEsTemp = 1.0 - m_dTemp * m_dTemp; // e2

	m_dDeltaA = m_arMajor[m_eDstEllips] - m_arMajor[m_eSrcEllips]; // output major axis - input major axis
	m_dDeltaF = m_arMinor[m_eSrcEllips] / m_arMajor[m_eSrcEllips] - m_arMinor[m_eDstEllips] / m_arMajor[m_eDstEllips]; // Output Flattening - input flattening
}
