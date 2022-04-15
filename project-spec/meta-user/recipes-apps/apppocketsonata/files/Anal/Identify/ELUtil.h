// ELUtil.h: interface for the CUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UTIL_H__43C28AC5_E619_4079_AEF1_4C680C7CA6B5__INCLUDED_)
#define AFX_UTIL_H__43C28AC5_E619_4079_AEF1_4C680C7CA6B5__INCLUDED_

#include "../SigAnal/_Macro.h"


#define	KM_PER_DEGREE_FOR_LATITUDE						(111.111)				// [km/deg]
#define	KM_PER_DEGREE_FOR_LONGITUDE						(88.884)				// [km/deg]

//BOOL ELCompSwitchLevel( int *pSeries1, int *pSeries2, int coSeries, int margin );
//BOOL CompTOAMeanDiff( unsigned long long int x, unsigned long long int y, int thresh );
BOOL CompAoaDiff( float x, float y, float fthresh );
float AoaDiff( float x, float y);
void LogPrint( const char *format, ... );

bool Is_FZero( const float &value );
bool Is_DZero( const double &dvalue );
bool Is_FNotZero( const float &value );
bool Is_DNotZero( const double &dvalue );

/**
 * @brief     IsSamePulseTrain
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
BOOL IsSamePulseTrain( T x1, T x2, T priMean, T margin )
{
    T diffToa;
    BOOL bRet=TRUE;

    if( priMean > margin ) {
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
 * @brief     CompMeanDiff
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
        \param    y1 인자형태 int
        \param    y2 인자형태 int
        \param    thresh 인자형태 int
        \return   BOOL
        \version  0.0.1
        \date     2008-02-19 17:44:30
        \warning
*/
template <typename T>
BOOL CompMarginDiff( T x, T iy1, T iy2, T fthresh )
{
    BOOL bRet;

    if( ( x >= iy1-fthresh ) && ( x <= iy2+fthresh ) ) {
        bRet = TRUE;
    }
    else {
        bRet = FALSE;
    }
    return bRet;
}

/**
 * @brief     CalOverlapSpace
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
T CalOverlapSpace(T hgh1, T low1, T hgh2, T low2)
{
	T ret=0;

    if( hgh1 < low2 || hgh2 < low1 )				// |-------|		|--------|
        ret = 0;															//			 |---|

    if( hgh1 == low2 || hgh2 == low1 )			// debug, 99-12-22 09:36:19
        ret = 1;

    if( low1 >= low2 &&	hgh1 <= hgh2 ) 			//          |--------|
        ret = hgh1 - low1 + 1;								//    |------------------|

    if( low1 <= low2 && hgh1 >= hgh2 )			//    |------------------|
        ret = hgh2 - low2 + 1;			 					//          |--------|

    if( low1 <= hgh2 && low2 <= low1 )			//          |------------|
        ret = ( hgh2 - low1 + 1);     			//    |-----------|

    if( hgh1 >= low2 && hgh1 <= hgh2 )   		//    |-----------|
        ret = ( hgh1 - low2 + 1 );						//          |------------|

    return ret;
}

/**
 * @brief     IsOverlapSpace
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
bool IsOverlapSpace(T hgh1, T low1, T hgh2, T low2, T tRatio )
{
    T tOverlapSpace;

    tOverlapSpace = CalOverlapSpace<T>( hgh1, low1, hgh2, low2 );
    return tOverlapSpace >= tRatio;

}


#endif // !defined(AFX_UTIL_H__43C28AC5_E619_4079_AEF1_4C680C7CA6B5__INCLUDED_)
