/////////////////////////////////////////////////////////////////////////////// 
//																			 // 
//		파일명			: LatLong-UTMconversion.h							 // 
//		추적성			: SDD 5.2.12.4										 //
//		프로젝트명		: 종합정보분석체계 CD-201K							 // 
//		설명			: Ellipsoid 클래스 함수 및 UTM 관련 함수			 //
//						  프로토타입 선언									 //
//		작성자			: 김재경	 										 // 
//		최신 개정일자	: 2007. 08. 10.										 // 
//																			 // 
///////////////////////////////////////////////////////////////////////////////

#include <string.h>

#ifndef LATLONGCONV
#define LATLONGCONV

void LLtoUTM(int ReferenceEllipsoid, const double Lat, const double Long, 
			 double &UTMNorthing, double &UTMEasting, char* UTMZone);
void UTMtoLL(int ReferenceEllipsoid, const double UTMNorthing, const double UTMEasting, const char* UTMZone,
			  double& Lat,  double& Long );
char UTMLetterDesignator(double Lat);
void LLtoSwissGrid(const double Lat, const double Long, 
			 double &SwissNorthing, double &SwissEasting);
void SwissGridtoLL(const double SwissNorthing, const double SwissEasting, 
					double& Lat, double& Long);

struct Ellipsoid {
	int id;
	char ellipsoidName[100];
	double EquatorialRadius; 
	double eccentricitySquared;  

} ;


#endif
