// ELUtil.h: interface for the CUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UTIL_H__43C28AC5_E619_4079_AEF1_4C680C7CA6B5__INCLUDED_)
#define AFX_UTIL_H__43C28AC5_E619_4079_AEF1_4C680C7CA6B5__INCLUDED_

#include "../SigAnal/_Macro.h"

#include "../../Utils/MulDiv64.h"
#include "../EmitterMerge/IsNumber.h"


#define	KM_PER_DEGREE_FOR_LATITUDE						(111.111)				// [km/deg]
#define	KM_PER_DEGREE_FOR_LONGITUDE						(88.884)				// [km/deg]

void LogPrint( const char *format, ... );


void SetUnitType();

float DOADiff(float x, float y);

void UTF8ToMultibyte(char *pszMultiByte, size_t iSizeOfMultiByte, const wchar_t *p);
int MultiByteToUTF8(wchar_t *pszUniCode, int iMaxSizeOfUnicode, char *pszMultiByte);

UINT CheckHarmonicTOA(_TOA priMean1, _TOA priMean2, _TOA tThreshold);


///////////////////////////////////////////////////////////////////////////////////
// 템플릿 함수 모음

template <typename T>
BOOL CompAoaDiff(T x, T y, T thresh_value ) 
{
    T diff;
    BOOL bRet;

    diff = abs(x - y);

    if (diff <= thresh_value || (MAX_AOA - diff) <= thresh_value)
        bRet = TRUE;
    else
        bRet = FALSE;

    return bRet;

}

/**
 * @brief     두 PRI 값들 사이에 연속 관계 여부를 계산한다. x2 값이 x1 보다 커야 하며 priMEan 을 기준으로 비교한다.
 * @param     T x1
 * @param     T x2
 * @param     T priMean
 * @param     T margin
 * @return    BOOL
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-01-10, 14:41
 * @warning
 */
template <typename T>
BOOL IsSamePulse( T x1, T x2, T priMean, T margin )
{
    T diffToa;
    BOOL bRet=TRUE;

    if( priMean > margin && x2 > x1 ) {
        diffToa = ( x2 - x1 ) % priMean;
        if( diffToa > margin && diffToa < ( priMean - margin ) ) {
            bRet = FALSE;
        }
    }
    else {
        bRet = FALSE;
    }

    return bRet;
}

/**
 * @brief     두 수간의 임계값 차이 내에 들면 정상으로 리턴한다.
 * @param     T x
 * @param     T y
 * @param     T thresh
 * @return    BOOL
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-01-10, 14:37
 * @warning
 */
template <typename T>
BOOL CompMeanDiff( T x, T y, T thresh )
{
    T diff;
    BOOL bRet;

    diff = _diffabs<T>( x, y );

    if( diff <= thresh ) {
        bRet = TRUE;
    }
    else {
        bRet = FALSE;
    }

    return bRet;
}

/**
 * @brief     어레이 값들에 대해서 평균 값을 계산한다.
 * @param     T * series
 * @param     UINT co
 * @return    float
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-15, 18:08
 * @warning
 */
template <typename T>
float MeanInArray( T *series, UINT co)
{
    UINT i;
    T sum;

    sum = _spZero;
    for (i = 0; i < co; ++i) {
        sum += *series++;
    }

    return ( (float)sum / (float)co);
}

/**
 * @brief     SDevInArray
 * @param     T * series
 * @param     UINT co
 * @param     float mean
 * @return    float
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-15, 18:11
 * @warning
 */
template <typename T>
float SDevInArray(T *series, UINT co, float mean)
{
    register unsigned int i;

    double sdiff;

    float diff;
    float fRet;

    if (co <= _spOne) {
        fRet = _spZero;
    }
    else {
        sdiff = _spZero;
        for (i = 0; i < co; ++i) {
            diff = *series++ - mean;
            sdiff += ((float)diff * (float)diff / (float)co);
        }

        fRet = (float)sqrt(sdiff);
    }

    return fRet;

}

/**
 * @brief     ELCompSwitchLevel
 * @param     T * pSeries1
 * @param     T * pSeries2
 * @param     int coSeries
 * @param     T margin
 * @return    BOOL
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-01-10, 14:36
 * @warning
 */
template <typename T>
BOOL ELCompSwitchLevel( T *pSeries1, T *pSeries2, int coSeries, T margin )
{
    int j, k;
    T iDiff;
    int index1;

    T *pSeries;

    BOOL bRet=FALSE;

    if( coSeries == 0 ) {
        // bRet = FALSE;
    }
    else {
        for( j=0 ; j < coSeries ; ++j ) {
            pSeries = pSeries2;
            bRet = TRUE;
            iDiff = 0;
            for( k=j ; k < coSeries+j ; ++k ) {
                index1 = k % coSeries;
                bRet = CompMeanDiff<T>( pSeries1[index1], *pSeries, margin );
                if( FALSE == bRet ) {
                    break;
                }
                iDiff += _diffabs<T>( pSeries1[index1], *pSeries );
                ++ pSeries;
            }

            if( TRUE == bRet ) {
                // bRet = TRUE;
                break;
            }

        }

    }

    return bRet;

}

/**
 * @brief     CompSwitch2Level
 * @param     T * pSeries1
 * @param     T * pSeries2
 * @param     int coSeries1
 * @param     int coSeries2
 * @param     T margin
 * @return    BOOL
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-01-10, 14:36
 * @warning
 */
template <typename T>
BOOL CompSwitch2Level( T *pSeries1, T *pSeries2, int coSeries1, int coSeries2, T margin )
{
    int i, j;
    int index1;

    T *pSeries;

    BOOL bRet=FALSE;

    if( coSeries1 == 0 || coSeries2 == 0 ) {
        // bRet = FALSE;
    }

    else {
        if( coSeries1 == coSeries2 ) {
            bRet = ELCompSwitchLevel<T>( pSeries1, pSeries2, coSeries1, margin );
        }
        else if( coSeries1 < coSeries2 ) {
            for( i=0 ; i < coSeries2-coSeries1 ; ++i ) {
                pSeries = pSeries2;
                index1 = i;
                for( j=0 ; j < coSeries1 ; ++j ) {
                    bRet = CompMeanDiff( pSeries1[index1], *pSeries, margin );
                    if( bRet == FALSE ) {
                        break;
                    }
                    ++ pSeries;
                    ++ index1;
                }

                if( bRet == TRUE ) {
                    break;
                }
            }
        }
        else {
            for( i=0 ; i < coSeries1-coSeries2 ; ++i ) {
                pSeries = pSeries2;
                index1 = i;
                for( j=0 ; j < coSeries2 ; ++j ) {
                    bRet = CompMeanDiff( pSeries1[index1], *pSeries, margin );
                    if( bRet == FALSE ) {
                        break;
                    }
                    ++ pSeries;
                    ++ index1;
                }

                if( bRet == TRUE ) {
                    break;
                }
            }
        }

    }

    return bRet;

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    입력 값 범위에 임계값을 고려한 입력 값이 이내이면 TRUE, 그렇지 않으면 FALSE를 리턴한다.
    \author   조철희
    \param    x 인자형태 int
    \param    iy1 인자형태 int
    \param    iy2 인자형태 int
    \param    thresh 인자형태 int
    \return   BOOL
    \version  0.0.1
    \date     2008-02-19 17:44:30
    \warning
*/
template <typename T>
BOOL CompMarginDiff( T x, T iy1, T iy2, T thresh )
{
    BOOL bRet;

    if( ( x >= iy1- thresh) && ( x <= iy2+ thresh) ) {
        bRet = TRUE;
    }
    else {
        bRet = FALSE;
    }
    return bRet;
}

/**
 * @brief     지터율을 계산한다.
 * @param     T tRange
 * @param     T tMean
 * @return    float
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-06-22 11:44:46
 * @warning
 */
template <typename T>
float TCalcJitterRatio(T tRange, T tMean)
{
	float fRet=0.0;

	// const char *pst = typeid(T).name();
	
#ifdef _MSC_VER
	if (strcmp(typeid(T).name(), "float") == 0) {
		fRet = tRange * (float) 100. / tMean;
	}
	else {
		fRet = (float) tRange * (float) 100. / (float) tMean;
	}
#else
	if (sizeof(T) == sizeof(float)) {
		fRet = tRange * (float) 100. / tMean;
	}
	else {
		fRet = (float)tRange * (float) 100. / (float)tMean;
	}

#endif

	return fRet;
}

/**
 * @brief     두 범위 간의 겹치는 영역을 계산한다.
 * @param     T hgh1
 * @param     T low1
 * @param     T hgh2
 * @param     T low2
 * @return    T
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-01-10, 14:36
 * @warning
 */
template <typename T>
T CalOverlapSpace( T low1, T hgh1, T low2, T hgh2 )
{
	T ret=0;

    //if ( low1 == low2 && hgh1 == hgh2)
	if ( is_zero<T>( (T)(low1-low2) ) == true && is_zero<T>( (T)(hgh1 - hgh2)) == true)
        ret = 1;

    if( hgh1 < low2 || hgh2 < low1 )			// |-------|		   |--------|
        ret = 0;								//			   |---|

    if( hgh1 == low2 || hgh2 == low1 )			// |-------|		   |--------|
        ret = 1;                                //		   |---|

    if( low1 > low2 && hgh1 < hgh2 ) 			//          |--------|
        ret = ( hgh1 - low1 + (T) 1 );					//    |------------------|

    if( low1 < low2 && hgh1 > hgh2 )			//    |------------------|
        ret = ( hgh2 - low2 + (T)1 );			 					//          |--------|

    if( low1 <= hgh2 && low2 <= low1 )			//          |------------|
        ret = ( hgh2 - low1 + (T)1);     			//    |-----------|

    if( hgh1 >= low2 && hgh1 <= hgh2 )   		//    |-----------|
        ret = ( hgh1 - low2 + (T)1 );						//          |------------|

    return ret;
}

/**
 * @brief     임계값 (tRatio) 이상 여부를 확인하여 중복 여부를 리턴한다.
 * @param     T hgh1
 * @param     T low1
 * @param     T hgh2
 * @param     T low2
 * @param     T tRatio
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-01-10, 14:36
 * @warning
 */
template <typename T>
bool IsOverlapSpace( T low1, T hgh1, T low2, T hgh2, T tRatio )
{
    T tOverlapSpace;

    tOverlapSpace = CalOverlapSpace<T>( low1, hgh1, low2, hgh2 );
    return tOverlapSpace >= tRatio;

}

/**
 * @brief     지터율 신호 양 신호에 대해서 비교한다.
 * @param     T tMean1
 * @param     T tMin1
 * @param     T tMax1
 * @param     T tMean2
 * @param     T tMin2
 * @param     T tMax2
 * @param     unsigned int uiDivide
 * @return    bool
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-06-28 12:12:21
 * @warning
 */
template <typename T>
bool CompJitJit(T tMean1, T tMin1, T tMax1, T tMean2, T tMin2, T tMax2, unsigned int uiDivide=1 )
{
	bool bRet=false;

	int iOverlap1, iOverlap2;

	T tMax, tMin, tOverlap;

	if ( tMean1 < tMean2 ) {
		tMin = TMUL<T>( tMin1, (T) uiDivide);
		tMax = TMUL<T>( tMax1, (T) uiDivide);
		tOverlap = CalOverlapSpace<T>( tMin, tMax, tMin2, tMax2);
		tOverlap = TMUL<T>(tOverlap, (T) 100);

		/*! \debug  분모가 0인 경우가 발생함. (stPRI.tMax = stPRI.tMin 일때)
			\author 조철희 (churlhee.jo@lignex1.com)
			\date 	2022-06-22 14:43:03
		*/
		iOverlap1 = (int)TDIV<T>(tOverlap, (tMax - tMin) + 1);
		iOverlap2 = (int)TDIV<T>(tOverlap, (tMax2 - tMin2) + 1);
	}
	else {
		tMin = TMUL<T>(tMin2, (T) uiDivide);
		tMax = TMUL<T>(tMax2, (T)uiDivide);
		tOverlap = CalOverlapSpace<T>(tMin, tMax, tMin1, tMax1);
		tOverlap = TMUL<T>(tOverlap, (T)100);

		iOverlap1 = (int)TDIV<T>(tOverlap, (tMax1 - tMin1) + 1);
		iOverlap2 = (int)TDIV<T>(tOverlap, (tMax - tMin) + 1);
	}

	// 겹쳐진 영역을 체크해서 결정한다.
	if ((iOverlap1 > 50 && iOverlap2 > 50) && (iOverlap1 > 90 || iOverlap2 > 90)) {
		bRet = true;
	}
	else {
		//uiDivide = 0;
	}

	return bRet;
}


#endif // !defined(AFX_UTIL_H__43C28AC5_E619_4079_AEF1_4C680C7CA6B5__INCLUDED_)
