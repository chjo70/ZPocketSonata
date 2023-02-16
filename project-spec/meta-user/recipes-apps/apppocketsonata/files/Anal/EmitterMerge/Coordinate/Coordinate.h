#ifndef COORDINATE_H_
#define COORDINATE_H_

///1. header include
//#include "../typedef.h"
#if 0 
#include "MatrixConverter.h"
#endif

///2.namespace
///3.define 
#define RAD2DEG		    (57.2957795130) 
#define DEG2RAD		    (0.017453292519)

///4.constant define
///5.typedef define 
///6.enum type

///7.struct define
/**
    @struct SCartesian
    @brief Cartesian vector.
*/
typedef struct cartStruct
{
    double x;               /// x co-ordinate
    double y;               /// y co-ordinate
    double z;               /// z co-ordinate
}SCartesian;                      

/**
    @struct SLlhPos
    @brief LLH position 
*/
typedef struct llhStruct
{
    double lat;             ///Latitude co-ordinate (radian)
    double lon;             ///Longitude co-ordinate (radian)
    double hgt;             ///Height co-ordinate (meter)
}SLlhPos;

/**
    @struct SEnuPos
    @brief enu position 
*/
typedef struct enuStruct
{
    double east;            ///east
    double north;           ///north 
    double up;              ///up
}SEnuPos;

///8.extern variable define
/**
    @class CCoordinate
    @brief Coordinate class
*/
class CCoordinate
{   
///멤버변수
public:

private:

///멤버함수
public:

    ///생성자 
    CCoordinate();

    ///소멸자
    virtual ~CCoordinate();


    ///vector length
    static double GetVectorLen(double x, double y, double z);

    static double GetVectorLen(double x, double y);

    ///llh2xyz
    static void ConvertLLH2XYZ(const SLlhPos &stLlh, SCartesian *pstXyzPos);

    ///xyz2llh
    static void ConvertXYZ2LLH(const SCartesian &stXyzPos, SLlhPos *pstLlh);

    ///distance between llh1 and llh2
    static double CalcDistLLH( const SLlhPos &stLlh1, const SLlhPos &stLlh2);

    ///xyz2enu
    static void ConvertXYZ2ENU(const SCartesian &stCartPos,const SCartesian &stCartOrgPos,SEnuPos *pstEnuPos);

	///enu2xyz(추가)
    static void ConvertENU2XYZ(const SEnuPos &stEnuPos,const SCartesian &stCartOrgPos,SCartesian *pstCartPos);

    ///llh2enu
    static void ConvertLLH2ENU(const SLlhPos &stLLHPos,const SLlhPos &stLLHOrgPos,SEnuPos *pstEnuPos);

	///enu2llh(추가)
	static void ConvertENU2LLH(const SEnuPos & stEnuPos,const SLlhPos &stLLHOrgPos, SLlhPos *pstLlhPos );

    ///enu2xyz
 
    ///deg to deg min(LLH 좌표값 단위 변환)
    static void ConvertDeg2DegMin(double dInDeg,double *pdDeg,double *pdMin);

    ///deg min to deg(LLH 좌표값 단위 변환)
    static void ConvertDegMin2Deg(double dInDeg , double dInMin,double *pdDeg);

    ///deg to deg min sec(LLH 좌표값 단위 변환)
    static void ConvertDeg2DegMinSec(double dInDeg , double *pdDeg, double *pdMin,double *pdSec);

    ///deg min sec to deg(LLH 좌표값 단위 변환)
    static void ConvertDegMinSec2Deg(double dInDeg , double dInMin, double dInSec,double *pdDeg);

    ///deg min to deg min sec(LLH 좌표값 단위 변환)
    static void ConvertDegMin2DegMinSec(double dInDeg , double dInMin,double *pdDeg,double *pdMin,double *pdSec);

    ///deg min sec to deg min(LLH 좌표값 단위 변환)
    static void ConvertDegMinSec2DegMin(double dInDeg , double dInMin, double dInSec,double *pdDeg,double *pdMin);

private:

};

#endif  ///COORDINATE_H_