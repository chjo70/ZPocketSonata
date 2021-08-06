/********************************************************************************

    @file		Coordinate.cpp
    @auther		bu sugn chun(sungchun.bu@lignex1.com)
    @brief		좌표변환 Class
    @detail		
    @version    0.00.01
    @date	    2014.07.02
    @history	
    @copyright copyright by LIG Nex1.Ltd

*********************************************************************************/

#include "stdafx.h"

#define _USE_MATH_DEFINES

#include <math.h>

#include "Coordinate.h"

#include "../../SigAnal/_Type.h"

#if 0

#else
#include "../Matrix/Matrix.h"
#endif



///생성자
CCoordinate::CCoordinate()
{

}

///소멸자
CCoordinate::~CCoordinate()
{

}

/********************************************************************************

    @brief Calculates the length of the vector (x,y,z). Note the this can be used for
    @detail  
    Calculates the length of the vector (x,y,z). Note the this can be used for

    @param[in] x : the x cartesian co-ordinate.
    @param[in] y : the y cartesian co-ordinate.
    @param[in] z : the z cartesian co-ordinate.
    
    @return The vector length.
    @exception
    @remark
*********************************************************************************/

double CCoordinate::GetVectorLen(double x, double y, double z)
{
    return(sqrt(x*x + y*y + z*z));
}

/********************************************************************************

    @brief Calculates the length of the vector (x,y). Note the this can be used for
    @detail  
    Calculates the length of the vector (x,y). Note the this can be used for

    @param[in] x : the x cartesian co-ordinate.
    @param[in] y : the y cartesian co-ordinate.
    
    @return The vector length.
    @exception
    @remark
*********************************************************************************/
double CCoordinate::GetVectorLen(double x, double y)
{
    return(sqrt(x*x + y*y));
}

/********************************************************************************

    @brief Calculates the distance between LLH1 and LLH2
    @detail  
    Calculates the distance between LLH1 and LLH2

    @param[in] stLlh1 : LLH1 position , (radian)
    @param[in] stLlh2 : LLH2 position , (radian)
    
    @return The vector length.
    @exception
    @remark
*********************************************************************************/
double CCoordinate::CalcDistLLH( const SLlhPos &stLlh1,const SLlhPos &stLlh2)
{
    double distance;
    SCartesian  stXyzPos1, stXyzPos2;

    
    CCoordinate::ConvertLLH2XYZ(stLlh1,&stXyzPos1);
    CCoordinate::ConvertLLH2XYZ(stLlh2,&stXyzPos2);	

    distance = sqrt( (stXyzPos1.x - stXyzPos2.x)*(stXyzPos1.x - stXyzPos2.x) + (stXyzPos1.y - stXyzPos2.y)*(stXyzPos1.y - stXyzPos2.y) +(stXyzPos1.z - stXyzPos2.z)*(stXyzPos1.z - stXyzPos2.z) );

    return distance;
}

/********************************************************************************

    @brief Convert LLH to XYZ
    @detail  
    Convert LLH to XYZ

    @param[in] stLlh : LLH1 position , (radian) 
                      (lat 0~90: north, lat 0~-90: south ,lon 0~180: east, lon 0~-180: west ) 
    @param[out] pstXyzPos : XYZ struct pointer
    
    @return none
    @exception
    @remark
*********************************************************************************/
void CCoordinate::ConvertLLH2XYZ(const SLlhPos &stLlh, SCartesian *pstXyzPos)
{
#if 0
    double n;         /* WGS-84 Radius of curvature in the prime vertical. */
    double a;                                    /* WGS-84 semimajor axis. */
    double e;                                /* WGS-84 first eccentricity. */
    double ome2;                                   /* WGS-84 (1.0E0 - e2). */
    double clat;                                              /* cos(lat). */
    double slat;                                              /* sin(lat). */
    double clon;                                              /* cos(lon). */
    double slon;                                              /* sin(lon). */
    double d,nph;
    double tmp;

    SLlhPos tmpllh;

    tmpllh.lat= llh->lat;
    tmpllh.lon= llh->lon;
    tmpllh.hgt= llh->hgt;
    
    a = 6378137.0E0;
    e = 0.0818191908426E0;
    ome2 = 0.99330562000987;

    clat = cos(tmpllh.lat);
    slat = sin(tmpllh.lat);
    clon = cos(tmpllh.lon);
    slon = sin(tmpllh.lon);
    d = e*slat;

    n = a/sqrt(1.0E0-d*d);
    nph = n + tmpllh.hgt;

    tmp = nph*clat;
    xyz->x = tmp*clon;
    xyz->y = tmp*slon;
    xyz->z = (ome2*n + tmpllh.hgt)*slat;
#else
    double dPhi = stLlh.lat;
    double dLamda = stLlh.lon;
    double h = stLlh.hgt;
    double a =0;
    double b =0;
    double e =0;
    double sinphi =0;
    double cosphi =0;
    double coslam =0;
    double sinlam =0;
    double tmpTan2phi =0;
    double tan2phi =0;
    double tmp =0;
    double tmpden =0;
    double tmp2 =0;

    a = 6378137.0000;	            /// earth semimajor axis in meters
    b = 6356752.3142;	            /// earth semiminor axis in meters	
    e = sqrt (1-(b/a) * (b/a));     /// WGS-84 first eccentricity

    sinphi = sin(dPhi);
    cosphi = cos(dPhi);
    coslam = cos(dLamda);
    sinlam = sin(dLamda);
    tmpTan2phi = (tan(dPhi));
    tan2phi = tmpTan2phi*tmpTan2phi;
    tmp = 1 - e*e;
    tmpden = sqrt( 1 + tmp*tan2phi );

    pstXyzPos->x = (a*coslam)/tmpden + h*coslam*cosphi;

    pstXyzPos->y = (a*sinlam)/tmpden + h*sinlam*cosphi;

    tmp2 = sqrt(1 - e*e*sinphi*sinphi);
    pstXyzPos->z = (a*tmp*sinphi)/tmp2 + h*sinphi;


#endif
}

/********************************************************************************

    @brief Converts from WGS-84 X, Y and Z rectangular co-ordinates to latitude,
    @detail  
    Converts from WGS-84 X, Y and Z rectangular co-ordinates to latitude,

    @param[in] stXyz : xyz position
    @param[out] pstLlh : llh struct pointer(radian) 
                         (lat 0~90: north, lat 0~-90: south ,lon 0~180: east, lon 0~-180: west ) 
    
    @return none
    @exception
    @remark
*********************************************************************************/
void CCoordinate::ConvertXYZ2LLH(const SCartesian &stXyz, SLlhPos *pstLlh)
{
#if 0
    double a;                                    /* WGS-84 semimajor axis. */
    double b;                            /* WGS-84 semiminor (polar) axis. */
    double e;                                /* WGS-84 first eccentricity. */
    double e2;                       /* WGS-84 first eccentricity squared. */
    double eps;                                      /* Convergence limit. */
    double dpi2;                                     /* Convergence limit. */
    double n,d,nph,rho,latold,hgtold;

    eps = 1.0E-13;
    dpi2 = 1.570796326794897E0;

    a = 6378137.0E0;
    b = 6356752.3142E0;
    e = 0.0818191908426E0;
    e2 = 0.00669437999013E0;

    /* If the position is on the Z axis, the computation must be handled as
       a special case to keep it from blowing up. */

    rho = GetVectorLen(xyz->x,xyz->y,0.0);
    if (rho <= eps)
    {
        llh->lat = dpi2;                 /* Come here if we are on the Z axis. */
        if(xyz->z<0.0)
            llh->lat = -llh->lat;
        llh->lon = 0.0E0;
        llh->hgt = fabs(xyz->z) - b;
        return;
    }

    /* Come here in the typical case.  Since latitude and spheroid height
       depend on one another, the solution must be done iteratively. */

    llh->lat = atan2(xyz->z,rho);
    llh->lon = atan2(xyz->y,xyz->x);
    llh->hgt = rho/cos(llh->lat);

    latold = llh->lat + 1.0E0;
    hgtold = llh->hgt + 1.0E0;
    while(fabs(llh->lat - latold)>=eps || fabs(llh->hgt-hgtold)>=0.01)
    {
        /* Require latitude to converge to about the precision of the
           machine, and height to the precision of about a centimeter. */

        latold = llh->lat;
        hgtold = llh->hgt;
        d = e*sin(latold);
        n = a/sqrt(1.0E0 - d*d);
        llh->hgt = rho/cos(latold) - n;
        nph = n + llh->hgt;
        d = 1.0E0 - e2*(n/nph);
        llh->lat = atan2(xyz->z,rho*d);
    }

    llh->lat = llh->lat;
    llh->lon = llh->lon;	
#else
    double x =stXyz.x;
    double y =stXyz.y;
    double z =stXyz.z;
    double x2 =x*x;
    double y2 =y*y;
    double z2 =z*z;
    double a,b,e,b2,e2,ep,r,r2,E2,F,G,c,s,P,Q,ro,tmp,U,V,zo,temp;

    a = 6378137.0000;	        /// earth radius in meters
    b = 6356752.3142;	        /// earth semiminor in meters	
    e = sqrt (1-(b/a)*(b/a));   ///WGS-84 first eccentricity

    b2 = b*b;
    e2 = e*e;
    ep = e*(a/b);
    r = sqrt(x2+y2);
    r2 = r*r;
    E2 = a*a - b*b;
    F = 54.0*b2*z2;
    G = r2 + (1.0 - e2)*z2 - e2*E2;
    c = (e2*e2*F*r2)/(G*G*G);
    s = pow(( 1.0 + c + sqrt(c*c + 2*c) ),(1.0/3.0));
    P = F / (3 * (s+1.0/s+1.0)*(s+1.0/s+1.0) * G*G);
    Q = sqrt(1.0+2.0*e2*e2*P);
    ro = -(P*e2*r)/(1.0+Q) + sqrt((a*a/2.0)*(1+1/Q) - (P*(1-e2)*z2)/(Q*(1+Q)) - P*r2/2.0);
    tmp = (r - e2*ro)*(r - e2*ro);
    U = sqrt( tmp + z2 );
    V = sqrt( tmp + (1.0-e2)*z2);
    zo = (b2*z)/(a*V);

    pstLlh->hgt = U*( 1.0 - b2/(a*V) );

    pstLlh->lat = atan( (z + ep*ep*zo)/r );

    temp = atan(y/x);

    if (x >=0)
    {
        pstLlh->lon = temp;
    }
    else if ((x < 0) & (y >= 0))
    {
        pstLlh->lon = (M_PI + temp);
    }
    else
    {
        pstLlh->lon = (temp - M_PI);
    }
#endif
}

/********************************************************************************

    @brief Converts xyz,orgxyz to enu
    @detail  
    Converts xyz,orgxyz to enu

    @param[in] stCartPos : xyz position
    @param[in] stCartOrgPos : xyz org position
    @param[out] pstEnuPos : enu struct pointer
    
    @return none
    @exception
    @remark
*********************************************************************************/
void CCoordinate::ConvertXYZ2ENU(const SCartesian &stCartPos,const SCartesian &stCartOrgPos,SEnuPos *pstEnuPos)
{
    SCartesian stTempXyz;
    SCartesian stTempOrgXyz;     
    SCartesian stDiffXyz;
    SLlhPos stOrgLlh;
    double dPi=0;
    double dLam=0;
    double dSinPhi =0;
    double dCosPhi =0;
    double dSinLam = 0;
    double dCosLam =0;


    stTempXyz = stCartPos;
    stTempOrgXyz = stCartOrgPos;

    stDiffXyz.x = stTempXyz.x -stTempOrgXyz.x;
    stDiffXyz.y = stTempXyz.y -stTempOrgXyz.y;
    stDiffXyz.z = stTempXyz.z -stTempOrgXyz.z;

    
    ConvertXYZ2LLH(stCartOrgPos,&stOrgLlh);
    
    dPi = stOrgLlh.lat;
    dLam = stOrgLlh.lon;
    dSinPhi = sin(dPi);
    dCosPhi = cos(dPi);
    dSinLam = sin(dLam);
    dCosLam = cos(dLam);
       
    pstEnuPos->east = -1*dSinLam*stDiffXyz.x + dCosLam*stDiffXyz.y;
    pstEnuPos->north = -1*dSinPhi*dCosLam*stDiffXyz.x - dSinPhi*dSinLam*stDiffXyz.y + dCosPhi*stDiffXyz.z;
    pstEnuPos->up = dCosPhi*dCosLam*stDiffXyz.x + dCosPhi*dSinLam*stDiffXyz.y + dSinPhi*stDiffXyz.z;
    
    return;
}


/********************************************************************************

    @brief Convert enu,orgxyz to xyz
    @detail  
    Convert enu,orgxyz to xyz

    @param[in] stEnuPos : enu position 
    @param[in] stCartOrgPos : xyz org position
    @param[out] pstCartPos : xyz struct pointer
    
    @return none
    @exception
    @remark
*********************************************************************************/
void CCoordinate::ConvertENU2XYZ(const SEnuPos &stEnuPos,const SCartesian &stCartOrgPos,SCartesian *pstCartPos)
{
    bool bRet=true;

	SLlhPos stLLHOrgPos;
	double dPhi =0;
	double dLam = 0;
	double dSinphi =0;
	double dCosphi =0;
	double dSinlam =0;
	double dCoslam =0;

	///origin xyz to origin llh
 	ConvertXYZ2LLH(stCartOrgPos,&stLLHOrgPos);

	dPhi = stLLHOrgPos.lat;
	dLam = stLLHOrgPos.lon;

	dSinphi = sin(dPhi);
	dCosphi = cos(dPhi);
	dSinlam = sin(dLam);
	dCoslam = cos(dLam);
	
	///변환 Matrix 생성
#if 0
	double RMatrix[9] ={-1*dSinlam , dCoslam, 0 , -1*dSinphi*dCoslam , -1*dSinphi*dSinlam, dCosphi, dCosphi*dCoslam, dCosphi*dSinlam, dSinphi};
	double InverseRMatrix[9] ={0};
	double dEnuMat[3] = {stEnuPos.east,stEnuPos.north,stEnuPos.up};
	double dDiffXyz[3]={0};
	
	CMatrixConverter::MatrixInverse( RMatrix, InverseRMatrix, 3, 3 );

    CMatrixConverter::MatrixMultiply(InverseRMatrix,dEnuMat,dDiffXyz,3,3,1);

    pstCartPos->x = stCartOrgPos.x + dDiffXyz[0];
    pstCartPos->y = stCartOrgPos.y + dDiffXyz[1];
    pstCartPos->z = stCartOrgPos.z + dDiffXyz[2];

#else
    try {
        CMatrix theEnuMat( 3, 1 );
        CMatrix theRMatrix(3, 3), theInverseRMatrix, theResult;

        theRMatrix( 1, 1 ) = -1*dSinlam;
        theRMatrix( 1, 2 ) = dCoslam;
        theRMatrix( 1, 3 ) = 0;

        theRMatrix( 2, 1 ) = -1*dSinphi*dCoslam;
        theRMatrix( 2, 2 ) = -1*dSinphi*dSinlam;
        theRMatrix( 2, 3 ) = dCosphi;

        theRMatrix( 3, 1 ) = dCosphi*dCoslam;
        theRMatrix( 3, 2 ) = dCosphi*dSinlam;
        theRMatrix( 3, 3 ) = dSinphi;
    
        theInverseRMatrix = Inv( theRMatrix, & bRet );
        //theInverseRMatrix.Print();

        theEnuMat( 1, 1 ) = stEnuPos.east;
        theEnuMat( 2, 1 ) = stEnuPos.north;
        theEnuMat( 3, 1 ) = stEnuPos.up;
        //theEnuMat.Print();
        theResult = theInverseRMatrix * theEnuMat;
        //theResult.Print();

        pstCartPos->x = stCartOrgPos.x + theResult( 1, 1 );
        pstCartPos->y = stCartOrgPos.y + theResult( 2, 1 );
        pstCartPos->z = stCartOrgPos.z + theResult( 3, 1 );

    }
    catch (Exception err) {
        bRet = false;
        printf("Error: %s\n", err.msg);
    }
    catch (...) {
        bRet = false;
        printf("An error occured...\n");
    }

#endif

	
}


/********************************************************************************

    @brief Converts llh,org llh to enu
    @detail  
    Converts llh,org llh to enu

    @param[in] stLLHPos : llh position
                         (lat 0~90: north, lat 0~-90: south ,lon 0~180: east, lon 0~-180: west ) 
    @param[in] stLLHOrgPos :llh org position
                         (lat 0~90: north, lat 0~-90: south ,lon 0~180: east, lon 0~-180: west ) 
    @param[out] pstEnuPos : enu struct pointer
    
    @return none
    @exception
    @remark
*********************************************************************************/
void CCoordinate::ConvertLLH2ENU(const SLlhPos &stLLHPos,const SLlhPos &stLLHOrgPos,SEnuPos *pstEnuPos)
{
    SCartesian stTempXyz;
    SCartesian stTempOrgXyz;     
    SCartesian stDiffXyz;
    SLlhPos stOrgLlh;
    double dPi=0;
    double dLam=0;
    double dSinPhi =0;
    double dCosPhi =0;
    double dSinLam = 0;
    double dCosLam =0;

    ConvertLLH2XYZ(stLLHPos,&stTempXyz);
    ConvertLLH2XYZ(stLLHOrgPos,&stTempOrgXyz);

    stDiffXyz.x = stTempXyz.x -stTempOrgXyz.x;
    stDiffXyz.y = stTempXyz.y -stTempOrgXyz.y;
    stDiffXyz.z = stTempXyz.z -stTempOrgXyz.z;

    
    ConvertXYZ2LLH(stTempOrgXyz,&stOrgLlh);
    
    dPi = stOrgLlh.lat;
    dLam = stOrgLlh.lon;
    dSinPhi = sin(dPi);
    dCosPhi = cos(dPi);
    dSinLam = sin(dLam);
    dCosLam = cos(dLam);
       
    pstEnuPos->east = -1*dSinLam*stDiffXyz.x + dCosLam*stDiffXyz.y;
    pstEnuPos->north = -1*dSinPhi*dCosLam*stDiffXyz.x - dSinPhi*dSinLam*stDiffXyz.y + dCosPhi*stDiffXyz.z;
    pstEnuPos->up = dCosPhi*dCosLam*stDiffXyz.x + dCosPhi*dSinLam*stDiffXyz.y + dSinPhi*stDiffXyz.z;
    
    return;
}


/********************************************************************************

    @brief Converts llh,org llh to enu
    @detail  
    Converts llh,org llh to enu

    @param[in] stLLHPos : enu struct pointer
                         
    @param[in] stLLHOrgPos :llh org position
                         (lat 0~90: north, lat 0~-90: south ,lon 0~180: east, lon 0~-180: west ) 
    @param[out] pstLLHPos : llh struct pointer
						 (lat 0~90: north, lat 0~-90: south ,lon 0~180: east, lon 0~-180: west ) 
    
    @return none
    @exception
    @remark
*********************************************************************************/
void CCoordinate::ConvertENU2LLH(const SEnuPos & stEnuPos,const SLlhPos &stLLHOrgPos, SLlhPos *pstLlhPos )
{
	SCartesian stXyz;
	SCartesian stOrgXyz;

	///OrgLLH to OrgXyz
	ConvertLLH2XYZ(stLLHOrgPos,&stOrgXyz);

	///Destination enu to Destination xyz
	ConvertENU2XYZ(stEnuPos,stOrgXyz,&stXyz);

	///Destination xyz to Destination llh
	ConvertXYZ2LLH(stXyz,pstLlhPos);
}

/********************************************************************************

    @brief Converts degree to deg and min
    @detail  
    Converts degree to deg and min

    @param[in] dInDeg : Degree
    @param[out] pdDeg : Degree pointer
    @param[out] pdMin : Minute pointer
    
    @return none
    @exception
    @remark
*********************************************************************************/
void CCoordinate::ConvertDeg2DegMin(double dInDeg,double *pdDeg,double *pdMin)
{
    //double fractional =0;
    double dDeg =0;
    double dMin =0;

    modf(dInDeg,&dDeg);
    dMin = (dInDeg-dDeg)*60;

    *pdDeg = dDeg;
    *pdMin = dMin;
}

/********************************************************************************

    @brief Converts degree Min to degree
    @detail  
    Converts degree Min to degree

    @param[in] dInDeg : Degree
    @param[in] dInMin : Minute
    @param[out] pdDeg : Degree pointer
    
    @return none
    @exception
    @remark
*********************************************************************************/
void CCoordinate::ConvertDegMin2Deg(double dInDeg , double dInMin,double *pdDeg)
{
    *pdDeg = dInDeg + dInMin*(1/60);
}

/********************************************************************************

    @brief Converts degree to degree min sec
    @detail  
    Converts degree to degree min sec

    @param[in] dInDeg : Degree
    @param[out] pdDeg : Degree pointer     
    @param[out] pdMin : minute pointer
    @param[out] pdSec : second pointer

    @return none
    @exception
    @remark
*********************************************************************************/
void CCoordinate::ConvertDeg2DegMinSec(double dInDeg , double *pdDeg, double *pdMin,double *pdSec)
{
    //double fractional =0;
    double dDeg =0;
    double dMin =0;
    double dSec =0;

    modf(dInDeg,&dDeg);

    modf((dInDeg - dDeg)*60,&dMin);
    dSec = ((dInDeg - dDeg)*60 - dMin) *60;

    *pdDeg = dDeg;
    *pdMin = dMin;
    *pdSec = dSec;
}

/********************************************************************************

    @brief Converts degree min sec to degree
    @detail  
    Converts degree to degree min sec

    @param[in] dInDeg : Degree     
    @param[in] dInMin : minute
    @param[in] dInSec : second
    @param[out] dInDeg : Degree pointer

    @return none
    @exception
    @remark
*********************************************************************************/
void CCoordinate::ConvertDegMinSec2Deg(double dInDeg , double dInMin, double dInSec,double *pdDeg)
{
    *pdDeg = dInDeg + dInMin *(1/60) + dInSec*(1/3600);
}

/********************************************************************************

    @brief Converts degree min to degree min sec
    @detail  
    Converts degree min to degree min sec

    @param[in] dInDeg : Degree     
    @param[in] dInMin : minute
    @param[out] pdDeg : Degree pointer     
    @param[out] pdMin : minute pointer
    @param[out] pdSec : second pointer

    @return none
    @exception
    @remark
*********************************************************************************/
void CCoordinate::ConvertDegMin2DegMinSec(double dInDeg , double dInMin,double *pdDeg,double *pdMin,double *pdSec)
{
    double dDegree =0;

    ConvertDegMin2Deg(dInDeg,dInMin,&dDegree);
    ConvertDeg2DegMinSec(dDegree,pdDeg,pdMin,pdSec);
}

/********************************************************************************

    @brief Converts degree min sec to degree min 
    @detail  
    Converts degree min sec to degree min 

    @param[in] dInDeg : Degree 
    @param[in] dInMin : minute
    @param[in] dInMin : second pointer
    @param[out] pdDeg : Degree pointer     
    @param[out] pdMin : minute pointer

    @return none
    @exception
    @remark
*********************************************************************************/
void CCoordinate::ConvertDegMinSec2DegMin(double dInDeg , double dInMin, double dInSec,double *pdDeg,double *pdMin)
{
    double dDegree =0;
    ConvertDegMinSec2Deg(dInDeg,dInMin,dInSec,&dDegree);
    ConvertDeg2DegMin(dDegree,pdDeg,pdMin);
}
