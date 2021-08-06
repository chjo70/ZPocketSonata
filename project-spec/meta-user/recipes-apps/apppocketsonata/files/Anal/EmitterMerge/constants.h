/**
 * @file      constants.h
 * @brief     
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2014-06-23, 오후 12:06 
 * @warning   
 */
/////////////////////////////////////////////////////////////////////////////// 

#ifndef CONSTANTS_H
#define CONSTANTS_H

#define _USE_MATH_DEFINES

#include <math.h>

#include "LatLong-UTMconversion.h"

const double FOURTHPI = ( M_PI / 4.);
const double deg2rad = ( M_PI / 180. );
const double rad2deg = 180.0 / M_PI;

static Ellipsoid ellipsoid[25] = { { -1, "Placeholder", 0, 0 } ,
																	 {  1, "Airy", 6377563, 0.00667054 } ,
																	 {  2, "Australian National", 6378160, 0.006694542 } ,
																	 {  3, "Bessel 1841", 6377397, 0.006674372 } ,
																	 {  4, "Bessel 1841 (Nambia) ", 6377484, 0.006674372 } ,
																	 {  5, "Clarke 1866", 6378206, 0.006768658 } ,
																	 {  6, "Clarke 1880", 6378249, 0.006803511 } ,
																	 {  7, "Everest", 6377276, 0.006637847 } ,
																	 {  8, "Fischer 1960 (Mercury) ", 6378166, 0.006693422 } ,
																	 {  9, "Fischer 1968", 6378150, 0.006693422 } ,
																	 {  10, "GRS 1967", 6378160, 0.006694605 } ,
																	 {  11, "GRS 1980", 6378137, 0.00669438 } ,
																	 {  12, "Helmert 1906", 6378200, 0.006693422 } ,
																	 {  13, "Hough", 6378270, 0.00672267 } ,
																	 {  14, "International", 6378388, 0.00672267 } ,
																	 {  15, "Krassovsky", 6378245, 0.006693422 } ,
																	 {  16, "Modified Airy", 6377340, 0.00667054 } ,
																	 {  17, "Modified Everest", 6377304, 0.006637847 } ,
																	 {  18, "Modified Fischer 1960", 6378155, 0.006693422 } ,
																	 {  19, "South American 1969", 6378160, 0.006694542 } ,
																	 {  20, "WGS 60", 6378165, 0.006693422 } ,
																	 {  21, "WGS 66", 6378145, 0.006694542 } ,
																	 {  22, "WGS-72", 6378135, 0.006694318 } ,
																	 {  23, "WGS-84", 6378137, 0.00669438 } } ;



#endif
