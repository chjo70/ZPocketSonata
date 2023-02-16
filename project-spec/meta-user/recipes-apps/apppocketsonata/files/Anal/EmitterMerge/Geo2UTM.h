/////////////////////////////////////////////////////////////////////////////// 
//																			 // 
//		파일명			: Geo2UTM.h											 // 
//		추적성			: SDD 5.2.12.5										 //
//		프로젝트명		: 종합정보분석체계 CD-201K							 // 
//		설명			: UTM 관련 함수 프로토타입 선언, 구조체,			 //	
//						  Define 정의 헤더 파일								 // 
//		작성자			: 김재경	 										 // 
//		최신 개정일자	: 2007. 08. 10.										 // 
//																			 // 
///////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GEO2UTM_H__1683651A_739D_4BE4_BB12_51F85E00BD27__INCLUDED_)
#define AFX_GEO2UTM_H__1683651A_739D_4BE4_BB12_51F85E00BD27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"

typedef struct 
{
	double x;
	double y;
	char zone[10];

} STR_UTM;

// WGS-84. See list with file "GPS2UTM/constants.h" for id numbers
static int m_RefEllipsoid=23;

void UTMtoLL( double UTMNorthing, double UTMEasting, const char* UTMZone, double& Lat,  double& Long );
char UTMLetterDesignator(double Lat);
void LLtoUTM( double Lat, double Long, double &UTMNorthing, double &UTMEasting, char* UTMZone);
double DegMinSec2Degree( double ll );
double Deg2DegMinSec( double ll );
double Convert_String_To_Degree( char *pszLonLat );

#endif // !defined(AFX_GEO2UTM_H__1683651A_739D_4BE4_BB12_51F85E00BD27__INCLUDED_)
