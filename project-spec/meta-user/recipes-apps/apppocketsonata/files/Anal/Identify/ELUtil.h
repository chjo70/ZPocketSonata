/**

    @file      ELUtil.h
    @brief     EL 유틸 관련 헤더 파일 정의
    @details   ~
    @author    조철희
    @date      26.03.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#pragma once

#include <typeinfo>

#include "../SigAnal/_Macro.h"

#include "../EmitterMerge/IsNumber.h"
#include "../../Utils/MulDiv64.h"


#include "../Collect/DataFile/DataFile.h"


#define	KM_PER_DEGREE_FOR_LATITUDE						(111.111)				// [km/deg]
#define	KM_PER_DEGREE_FOR_LONGITUDE						(88.884)				// [km/deg]

void LogPrint( const char *format, ... );

float DOADiff( float x, float y );

void SetUnitType();


void UTF8ToMultibyte(char *pszMultiByte, size_t iSizeOfMultiByte, const wchar_t *p);
void MultibyteToUTF8( char *pszMultiByte, size_t iSizeOfMultiByte, const wchar_t *p );
int MultiByteToUTF8(wchar_t *pszUniCode, char *pszMultiByte);
int UTF8ToANSI( char *pszAnsiCode, char *pszUTF8 );
int ANSIToUTF8( char *pszUTF8, size_t szLength, char *pszAnsiCode );

UINT CheckHarmonicTOA(_TOA priMean1, _TOA priMean2, _TOA tThreshold);
UINT ExpectedMissingPulses( int ext_type, _TOA priMean1, STR_MINMAX_TOA *pstPRI, _TOA tThreshold );
//UINT CheckMissingPulse( _TOA priMean1, STR_MINMAX_TOA *pPRI, _TOA tThreshold );


///////////////////////////////////////////////////////////////////////////////////
// 템플릿 함수 모음


template <typename T>
UINT TCheckHarmonic( T priMean1, T priMean2, T tThreshold )
{
    UINT ret = 0;

    T r;
    T harmonic;
    T max_mean, min_mean;

    if( priMean1 > priMean2 ) {
        max_mean = priMean1;
        min_mean = priMean2;
    }
    else {
        max_mean = priMean2;
        min_mean = priMean1;
    }

    if( min_mean != 0 ) {
        harmonic = max_mean % min_mean;

        // 10배수 이상이면 STABLE 마진 값을 두배로 해서 harmonic 체크한다.
        T margin_th = tThreshold; // UDIV( max_mean, STB_MARGIN*1000 );

        // 하모닉 체크에서 배수만큼 더한 마진으로 체크한다.
        if( harmonic <= tThreshold + margin_th || min_mean - harmonic <= tThreshold + margin_th ) {
            r = TDIV<T>( max_mean, min_mean );
            // r = (T) MulDiv64((T)1, (T) max_mean, (T) min_mean);
            if( r >= INT_MAX ) {
                ret = INT_MAX;
            }
            else {
                ret = ( UINT ) r;
            }
        }
    }
    else {

    }

    return ret;
}

/**
 * @brief     방위[도]에 대한 임계값을 고려한 방탐 비교
 * @param     T x
 * @param     T y
 * @param     T thresh_value
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-26 13:08:18
 * @warning
 */
template <typename T>
bool TCompDOADiff(T x, T y, T thresh_value )
{
    T tdiff;
    bool bRet;

    tdiff = abs(x - y);

    if( tdiff <= thresh_value || ( 360 - tdiff ) <= thresh_value ) {
        bRet = true;
    }
    else {
        bRet = false;
    }

    return bRet;

}

/**
 * @brief     CompEncodeDOADiff
 * @param     T x
 * @param     T y
 * @param     T thresh_value
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-28 20:59:55
 * @warning
 */
template <typename T>
bool TCompEncodeDOADiff( T x, T y, T thresh_value )
{
    T tdiff;
    bool bRet;

    tdiff = abs( x - y );

    if( tdiff <= thresh_value || ( PDW_DOA_MAX - tdiff ) <= thresh_value ) {
        bRet = true;
    }
    else {
        bRet = false;
    }

    return bRet;

}

/**
 * @brief     방위 범위[도]에 대한 임계값을 고려한 방탐 비교
 * @param     T x
 * @param     T y1
 * @param     T y2
 * @param     T thresh_value
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-26 13:10:11
 * @warning
 */
template <typename T>
bool TCompEncodeDOAMarginDiff( T tx, T ty1, T ty2 )
{
    bool bRet=false;

    if( ty1 < ty2 ) {
        if( ( tx >= ty1 && tx <= ty2 ) ) {
            bRet = true;
        }
    }
    else {
        if( ( ( tx >= ty1 && tx <= ( PDW_DOA_MAX - 1 ) ) || ( tx >= 0 && tx <= ty2 ) ) ) {
            bRet = true;
        }

    }

    return bRet;

}

/**
 * @brief     CompDOAMarginDiff
 * @param     T x
 * @param     T y1
 * @param     T y2
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-28 21:00:16
 * @warning
 */
template <typename T>
bool TCompDOAMarginDiff( T tx, T ty1, T ty2 )
{
    bool bRet = false;

    if( ty1 < ty2 ) {
        if( ( tx >= ty1 && tx <= ty2 ) ) {
            bRet = true;
        }
    }
    else {
        if( ( ( tx >= ty1 && tx <= 0xFFFFFFF ) || ( tx >= 0 && tx <= ty2 ) ) ) {
            bRet = true;
        }
    }

    return bRet;

}

/**
 * @brief     두 PRI 값들 사이에 연속 관계 여부를 계산한다. x2 값이 x1 보다 커야 하며 priMEan 을 기준으로 비교한다.
 * @param     T x1
 * @param     T x2
 * @param     T priMean
 * @param     T margin
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-01-10, 14:41
 * @warning
 */
template <typename T>
bool TIsSamePulse( T x1, T x2, T priMean, T margin )
{
    T diffToa;
    bool bRet=true;

    if( priMean > margin && x2 > x1 ) {
        diffToa = ( x2 - x1 ) % priMean;
        if( diffToa > margin && diffToa < ( priMean - margin ) ) {
            bRet = false;
        }
    }
    else {
        bRet = false;
    }

    return bRet;
}

/**
 * @brief     두 수간의 임계값 차이 내에 들면 정상으로 리턴한다.
 * @param     T x
 * @param     T y
 * @param     T thresh
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-01-10, 14:37
 * @warning
 */
template <typename T>
bool TCompMeanDiff( T x, T y, T thresh )
{
    T diff;
    bool bRet;

    diff = _diffabs<T>( x, y );

    if( diff <= thresh ) {
        bRet = true;
    }
    else {
        bRet = false;
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
float TMeanInArray( T *series, UINT uiCo )
{
    UINT i;
    T tSum;

    tSum = _spZero;
    for (i = 0; i < uiCo ; ++i) {
        tSum += *series++;
    }

    return ( (float) tSum / (float) uiCo );
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
float TSDevInArray(T *tSeries, UINT uiCo, float fMean)
{
    unsigned int i;

    double dDiff;

    float fDiff;
    float fRet= (float) 0;

    if ( uiCo <= _spOne ) {

    }
    else {
        dDiff = _spZero;
        for (i = 0; i < uiCo ; ++i) {
            fDiff = *tSeries++ - fMean;
            //dDiff += ( ((float)diff * (float)diff ) / (float) uiCo );
            dDiff += ( fDiff * fDiff );
        }

        fRet = (float) sqrt( dDiff / (float) uiCo );
    }

    return fRet;

}

/**
 * @brief     ELCompSwitchLevel
 * @param     T * pSeries1
 * @param     T * pSeries2
 * @param     int coSeries
 * @param     T margin
 * @return    bool
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-01-10, 14:36
 * @warning
 */
template <typename T>
bool TELCompSwitchLevel( T *pSeries1, T *pSeries2, int coSeries, T margin )
{
    int j, k;
    T iDiff;
    int index1;

    T *pSeries;

    bool bRet=false;

    if( coSeries == 0 ) {
        // bRet = false;
    }
    else {
        for( j=0 ; j < coSeries ; ++j ) {
            pSeries = pSeries2;
            bRet = true;
            iDiff = 0;
            for( k=j ; k < coSeries+j ; ++k ) {
                index1 = k % coSeries;
                bRet = TCompMeanDiff<T>( pSeries1[index1], *pSeries, margin );
                if( false == bRet ) {
                    break;
                }
                iDiff += _diffabs<T>( pSeries1[index1], *pSeries );
                ++ pSeries;
            }

            if( true == bRet ) {
                // bRet = true;
                break;
            }

        }

    }

    return bRet;

}
//
//template <typename T>
//bool TELCompSwitchLevel( T *pSeries1, T *pSeries2Low, T *pSeriesHigh, int coSeries )
//{
//    int j, k;
//    //T iDiff;
//    int index1;
//
//    T *pSeriesLow, *pSeriesHigh;
//
//    bool bRet = false;
//
//    if( coSeries == 0 ) {
//    }
//    else {
//        for( j = 0; j < coSeries; ++j ) {
//            pSeriesLow = pSeries2Low;
//            pSeriesHigh = pSeries2High;
//            bRet = true;
//            //iDiff = 0;
//            for( k = j; k < coSeries + j; ++k ) {
//                index1 = k % coSeries;
//                bRet = TCompMarginDiff<T>( pSeries1[index1], *pSeriesLow, *pSeriesHigh, 0 );
//                if( false == bRet ) {
//                    break;
//                }
//                //iDiff += _diffabs<T>( pSeries1[index1], *pSeries );
//                ++ pSeries;
//            }
//
//            if( true == bRet ) {
//                // bRet = true;
//                break;
//            }
//
//        }
//
//    }
//
//    return bRet;
//
//}

/**
 * @brief     CompSwitch2Level
 * @param     T * pSeries1
 * @param     T * pSeries2
 * @param     int coSeries1
 * @param     int coSeries2
 * @param     T margin
 * @return    bool
 * @exception 두단은 정렬이 되어 있다는 가정하에 비교가 정상적으로 수행할 수 있습니다.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-01-10, 14:36
 * @warning
 */
template <typename T>
bool TCompSwitch2Level( T *pSeries1, T *pSeries2, int coSeries1, int coSeries2, T margin )
{
    int i;
    int iIndex;

    T *pSeries;

    bool bRet=false;

    if( coSeries1 == 0 || coSeries2 == 0 ) {
    }

    else {
        if( coSeries1 == coSeries2 ) {
            bRet = TELCompSwitchLevel<T>( pSeries1, pSeries2, coSeries1, margin );
        }
        else if( coSeries1 < coSeries2 ) {
            iIndex = 0;
            pSeries = pSeries1;
            for( i=0 ; i < coSeries1 ; ++i, ++pSeries ) {
                bRet = false;
                for( ; iIndex < coSeries2 ; ++iIndex  ) {
                    if( TCompMeanDiff<T>( pSeries2[iIndex], *pSeries, margin ) == true ) {
                        ++ iIndex;
                        bRet = true;
                        break;
                    }
                }

                if( bRet == false ) {
                    break;
                }

            }
        }
        else {
            iIndex = 0;
            pSeries = pSeries2;
            for( i = 0; i < coSeries2 ; ++i, ++pSeries ) {
                bRet = false;
                for( ; iIndex < coSeries1 ; ++iIndex ) {
                    if( TCompMeanDiff<T>( pSeries1[iIndex], *pSeries, margin ) == true ) {
                        ++ iIndex;
                        bRet = true;
                        break;
                    }
                }

                if( bRet == false ) {
                    break;
                }

            }

        }

    }

    return bRet;

}

//template <typename T>
//bool TCompSwitch2Level( T *pSeries1, T *pSeries2Low, T *pSeries2High, int coSeries1, int coSeries2 )
//{
//    int i;
//    int iIndex;
//
//    T *pSeries;
//
//    bool bRet = false;
//
//    if( coSeries1 == 0 || coSeries2 == 0 ) {
//    }
//
//    else {
//        if( coSeries1 == coSeries2 ) {
//            bRet = TELCompSwitchLevel<T>( pSeries1, pSeries2Low, pSeries2Low, coSeries1 );
//        }
//        else if( coSeries1 < coSeries2 ) {
//            iIndex = 0;
//            pSeries = pSeries1;
//            for( i = 0; i < coSeries1; ++i, ++pSeries ) {
//                bRet = false;
//                for( ; iIndex < coSeries2; ++iIndex ) {
//                    if( TCompMarginDiff<T>( *pSeries, pSeries2Low[iIndex], pSeries2High[iIndex], 0 ) == true ) {
//                        ++ iIndex;
//                        bRet = true;
//                        break;
//                    }
//                }
//
//                if( bRet == false ) {
//                    break;
//                }
//
//            }
//        }
//        else {
//            iIndex = 0;
//            pSeriesLow = pSeries2Low;
//            pSeriesHigh = pSeries2High;
//            for( i = 0; i < coSeries2; ++i, ++pSeriesLow, ++pSeriesHigh ) {
//                bRet = false;
//                for( ; iIndex < coSeries1; ++iIndex ) {
//                    if( TCompMarginDiff<T>( pSeries1[iIndex], *pSeriesLow, *pSeriesHigh, margin ) == true ) {
//                        ++ iIndex;
//                        bRet = true;
//                        break;
//                    }
//                }
//
//                if( bRet == false ) {
//                    break;
//                }
//
//            }
//
//        }
//
//    }
//
//    return bRet;
//
//}

//////////////////////////////////////////////////////////////////////////
/*! \brief    입력 값 범위에 임계값을 고려한 입력 값이 이내이면 true, 그렇지 않으면 false를 리턴한다.
    \author   조철희
    \param    x 인자형태 int
    \param    iy1 인자형태 int
    \param    iy2 인자형태 int
    \param    thresh 인자형태 int
    \return   bool
    \version  0.0.1
    \date     2008-02-19 17:44:30
    \warning
*/
template <typename T>
bool TCompMarginDiff( T x, T iy1, T iy2, T thresh )
{
    bool bRet=false;

    const char *pType = typeid( T ).name();

    if( ( strcmp( pType, "y" ) == 0 || strcmp( pType, "unsigned __int64" ) == 0 || strcmp( pType, "unsigned long long int" ) == 0 || strcmp( pType, "unsigned int" ) == 0 ) ) {
        if( iy1 >= thresh ) {
            if( ( x >= iy1- thresh) && ( x <= iy2+ thresh) ) {
                bRet = true;
            }
            else {
                bRet = false;
            }
        }
        else {
            if( x <= iy2 + thresh ) {
                bRet = true;
            }
            else {
                bRet = false;
            }

        }
    }
    else {
        if( ( strcmp( pType, "i" ) == 0 || strcmp( pType, "f" ) == 0 || strcmp( pType, "__int64" ) == 0 || strcmp( pType, "long long int" ) == 0 || strcmp( pType, "int" ) == 0 || strcmp( pType, "float" ) == 0 ) ) {
            if( ( x >= iy1 - thresh ) && ( x <= iy2 + thresh ) ) {
                bRet = true;
            }
            else {
                bRet = false;
            }

        }
        else {
            while( true ) {
                TRACE( "\n std::typeid( T )=%s", pType );
            }

        }
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
//  */
// template <typename T>
// float TCalcJitterRatio(T tRange, T tMean)
// {
// 	float fRet=0.0;
//
// 	// const char *pst = typeid(T).name();
//
//     if( tMean != 0 ) {
//
// #ifdef _MSC_VER
// 	    if (strcmp(typeid(T).name(), "float") == 0) {
// 		    fRet = tRange * (float) 100. / tMean;
//         }
//
// 	    else {
// 		    fRet = (float) tRange * (float) 100. / (float) tMean;
// 	    }
// #else
// 	    if (sizeof(T) == sizeof(float)) {
// 		    fRet = tRange * (float) 100. / tMean;
// 	    }
// 	    else {
// 		    fRet = (float)tRange * (float) 100. / (float)tMean;
// 	    }
// #endif
//
//     }
//     else {
//         TRACE( "PRI 평균이 0 으로 잘못 계산되었습니다." );
//         WhereIs;
//     }
//
// 	return fRet;
// }

/**
 * @brief     TCalcJitterPercent
 * @param     T tRange
 * @param     T tMean
 * @return    float
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-10-24 11:10:46
 * @warning
 */
template <typename T>
float TCalcJitterPercent( T tRange, T tMean )
{
    float fRet = 0.0;

    // const char *pst = typeid(T).name();

    if( tMean != 0 ) {

#ifdef _MSC_VER
        if( strcmp( typeid( T ).name(), "float" ) == 0 ) {
            fRet = tRange * ( float ) 50. / tMean;
        }

        else {
            fRet = ( float ) tRange * ( float ) 50. / ( float ) tMean;
        }
#else
        if( sizeof( T ) == sizeof( float ) ) {
            fRet = tRange * ( float ) 50. / tMean;
        }
        else {
            fRet = ( float ) tRange * ( float ) 50. / ( float ) tMean;
        }
#endif

    }
    else {
        TRACE( "PRI 평균이 0 으로 잘못 계산되었습니다." );
        WhereIs;
    }

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
T TCalOverlapSpace( T low1, T hgh1, T low2, T hgh2 )
{
	T ret=0;

    //if ( low1 == low2 && hgh1 == hgh2)
    if( is_zero<T>( ( T ) ( low1 - low2 ) ) == true && is_zero<T>( ( T ) ( hgh1 - hgh2 ) ) == true ) {
        ret = 1;
    }

    if( hgh1 < low2 || hgh2 < low1 ) {			// |-------|		   |--------|
        ret = 0;								//			   |---|
    }

    //if( hgh1 == low2 || hgh2 == low1 )			// |-------|		   |--------|
    if( is_zero<T>( ( T ) ( hgh1 - low2 ) ) == true && is_zero<T>( ( T ) ( hgh2 - low1 ) ) == true ) {
        ret = 1;                                //		   |---|
    }

    if( low1 > low2 && hgh1 < hgh2 ) { 			//          |--------|
        ret = (T) ( hgh1 - low1 + ( T ) 1 );					//    |------------------|
    }

    if( low1 < low2 && hgh1 > hgh2 ) {			//    |------------------|
        ret = (T) ( hgh2 - low2 + ( T ) 1 );			 					//          |--------|
    }

    if( low1 <= hgh2 && low2 <= low1 ) {			//          |------------|
        ret = ( hgh2 - low1 + ( T ) 1 );     			//    |-----------|
    }

    if( hgh1 >= low2 && hgh1 <= hgh2 ) {   		//    |-----------|
        ret = ( hgh1 - low2 + ( T ) 1 );						//          |------------|
    }

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
bool TIsOverlapSpace( T low1, T hgh1, T low2, T hgh2, T tRatio )
{
    T tOverlapSpace;

    tOverlapSpace = TCalOverlapSpace<T>( low1, hgh1, low2, hgh2 );
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
bool TCompJitJit(T tMean1, T tMin1, T tMax1, T tMean2, T tMin2, T tMax2, unsigned int uiDivide=1 )
{
	bool bRet=false;

	int iOverlap1, iOverlap2;

	T tMax, tMin, tOverlap;

	if ( tMean1 < tMean2 ) {
		tMin = TMUL<T>( tMin1, (T) uiDivide);
		tMax = TMUL<T>( tMax1, (T) uiDivide);
		tOverlap = TCalOverlapSpace<T>( tMin, tMax, tMin2, tMax2);
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
		tOverlap = TCalOverlapSpace<T>(tMin, tMax, tMin1, tMax1);
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

/**
 * @brief     SortLevel
 * @param     int iSwtLev
 * @param     T * pSwtLev
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-21 16:15:03
 * @warning
 */
template <typename T>
int TSortLevel( int iSwtLev, T *pSwtLev, bool bDataUpdate=true )
{
    unsigned int i;

    int iret;
    int min_index, stagger_min_index;

    T tMin_stagger_level;
    T tLevel[MAX_FREQ_PRI_STEP];

    /*! \todo	스태거 레벨을 가장 작은 값부터 레벨값을 시작하게 한다. */
    // 스태거 레벨 에서 가장 작은 레벨값과 인덱스 값을 얻는다.
    min_index = 0;
    tMin_stagger_level = pSwtLev[0];
    for( i = 1; i < ( unsigned int ) iSwtLev && i < MAX_FREQ_PRI_STEP; ++i ) {
        if( false == TCompMeanDiff<T>( tMin_stagger_level, pSwtLev[i], ( T ) _spOneMicrosec ) ) {
            if( tMin_stagger_level > pSwtLev[i] ) {
                min_index = ( int ) i;
                tMin_stagger_level = pSwtLev[i];
            }
        }

    }
    /*! \bug  역방향으로 작은 레벨값을 검색해서 제일 작은 레벨 값을 시작으로 한다.
        \date 2006-08-16 20:18:43, 조철희
    */
    //
    iret = min_index;
    for( i = 1; i < ( unsigned int ) iSwtLev && i < MAX_FREQ_PRI_STEP; ++i ) {
        stagger_min_index = ( int ) ( ( iSwtLev + ( min_index - ( int ) i ) ) % iSwtLev );
        if( true == TCompMeanDiff<T>( pSwtLev[stagger_min_index], tMin_stagger_level, ( T ) _spOneMicrosec ) ) {
            iret = stagger_min_index;
        }
        else {
            break;
        }
    }

    if( bDataUpdate == true ) {
        memcpy( tLevel, pSwtLev, sizeof( T ) * MAX_FREQ_PRI_STEP );

        for( i = 0; i < (unsigned int) iSwtLev && i < MAX_FREQ_PRI_STEP; ++i ) {
            pSwtLev[i] = tLevel[( ( UINT ) iret + i ) % ( UINT ) iSwtLev];
        }
    }

    return iret;

}

/**
 * @brief     IsInElement
 * @param     std::vector<T> * pVector
 * @param     T * pstHopping
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-18 15:27:16
 * @warning
 */
// template <typename T>
// bool IsInElement( std::vector<T> vecVector, T stHopping )
// {
//     bool bRet;
//
//     for( const auto &stElement : vecVector ) {
//         if( stHopping == *stElement ) {
//             bRet = true;
//             break;
//         }
//     }
//
//     return bRet;
// }

template <typename T>
T TModular( T a, T b )
{
    T ret=0;

    if( b != 0 ) {
        ret = a % b;
    }
    else {

    }

    return ret;

}