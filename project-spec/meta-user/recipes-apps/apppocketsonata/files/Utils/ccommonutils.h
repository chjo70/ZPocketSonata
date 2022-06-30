#ifndef CCOMMONUTILS_H
#define CCOMMONUTILS_H

//#include "../Include/system.h"
//#include "../Utils/cthread.h"

#include "../Anal/SigAnal/_Type.h"

#include "../Include/struct.h"

#ifdef _MSC_VER
int clock_gettime(int X, struct timeval *tv);
LARGE_INTEGER getFILETIMEoffset();
int gettimeofday(struct timeval * tp, struct timezone * tzp);
#endif


/**
 * @brief     지정된 바이트로 Overflow 체크
 * @param     unsigned long long int ullFileSize
 * @return    T
 * @exception 
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-06-28 10:22:30
 * @warning
 */
template <typename T>
T CheckOverflow( unsigned long long int ullFileSize ) {
    T value;

    if( sizeof(T) == sizeof(int) ) {
        if( ullFileSize > UINT_MAX ) {
            value = UINT_MAX;
        }
        else {
            value = (T) ullFileSize;
        }
    }
    else if( sizeof(T) == sizeof(short) ) {
        if( ullFileSize > SHRT_MAX ) {
            value = SHRT_MAX;
        }
        else {
            value = (T) ullFileSize;
        }
    }
    else {
        if( ullFileSize > INT8_MAX ) {
            value = INT8_MAX;
        }
        else {
            value = (T) ullFileSize;
        }
    }

    return value;

}


class CCommonUtils
{
private:
    

public:
    CCommonUtils();

public:
    static void SendLan( UINT uiOpCode, void *pData, UINT uiLength );
    static void CloseSocket();

    static void DiffTimespec(struct timespec *result, struct timespec *start, struct timespec *stop=NULL );

    static int CalcDiffAOA( int iAOA1, int iAOA2 );

	// SWAP 관련 함수
    static void AllSwapData32( void *pData, unsigned int uiLength );
    static void swapByteOrder( unsigned int& ui );
    static void swapByteOrder(double & d);
    static void swapByteOrder(double *p, int iSize );
    static void swapByteOrder( unsigned short & us);

    static ENUM_COLLECTBANK GetEnumCollectBank( int iCh );

	// 데이터 관련 출력 함수
    static void Disp_FinePDW( STR_PDWDATA *pPDWData );

	// 시간관련 함수
    static DWORD GetTickCount();
    static void getStringPresentTime( char *pString, size_t szString );
    static void getStringDesignatedTime( char *pString, size_t szString, __time32_t tiTime );
    static void GetCollectTime(struct timespec *pTimeSpec, __time32_t tColTime, unsigned int tColTimeMs );
    static void GetCollectTime( struct timespec *pTimeSpec );

    static int CopyFile( const char *src_file, const char *dest_file, int overwrite, int copy_attr );

    static const char *strcasestr( const char *haystack, const char *needle );
    static int Isalpha( int iCh );

    static size_t CheckMultiplyOverflow( int iSize, int iItems );

    // 타입 변환시 사용하는 함수 모음
    //static unsigned int INT2UINT( int iValue );

    static ENUM_DataType WhatDataType( char *pStrPathname );
    static ENUM_UnitType WhatUnitType( char *pStrPathname );

    // 랜덤 값
    static int Rand( int range );

};

#endif // CCOMMONUTILS_H
