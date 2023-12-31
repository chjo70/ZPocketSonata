/**

    @file      ccommonutils.h
    @brief
    @details   ~
    @author    조철희
    @date      3.04.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#pragma once

#include <string>
#include <memory>
#include <algorithm>
#include <stdexcept>


#include "../Anal/INC/OS.h"

//#include "../Include/struct.h"
#include "../Anal/SigAnal/_Type.h"

//#include "../Include/struct.h"
#include "../Include/thrmsg.h"

#include "clog.h"

#include "../Anal/EmitterMerge/IsNumber.h"

#ifdef _MSC_VER
#include <string>


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

    const char *pType = typeid( T ).name();

#ifdef __VXWORKS__

    printf( "\n CheckOverflow : %s" , pType );

#endif

//     if( sizeof(T) == sizeof(int) ) {
//         if( ullFileSize > INT32_MAX ) {
//             value = INT32_MAX;
//         }
//         else {
//             value = (T) ullFileSize;
//         }
//     }
//     else if( sizeof(T) == sizeof(short) ) {
//         if( ullFileSize > SHRT_MAX ) {
//             value = SHRT_MAX;
//         }
//         else {
//             value = (T) ullFileSize;
//         }
//     }
    if( strcmp( pType, "__int64" ) == 0 || strcmp( pType, "unsigned __int64" ) == 0 || strcmp( pType, "unsigned int" ) == 0 ) {
        if( ullFileSize > INT32_MAX ) {
            value = INT32_MAX;
        }
        else {
            value = ( T ) ullFileSize;
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

/**
 * @brief		string_format
 * @param		const std::string & format
 * @param		Args ... args
 * @return		std::string
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/02/22 14:51:38
 * @warning
 */
template<typename ... Args>
std::string string_format( const char *pFormat, Args ... args )
{
#ifdef __VXWORKS__
	std::string strPrintf;

	int iSize = snprintf( 0, 0, pFormat, args ... ) + 1; // Extra space for '\0'
	if( iSize <= 0 ) {
		throw std::runtime_error( "Error during formatting." );
	}

	char* pBuff;
	pBuff = ( char* ) malloc( sizeof( char ) * iSize );
	snprintf( pBuff, iSize, pFormat, args ... );

	strPrintf = std::string( pBuff, pBuff + iSize - 1 ); // We don't want the '\0' inside
	free( pBuff );

	return strPrintf;

#else
    unsigned int uiSize = (unsigned int) snprintf( nullptr, 0, pFormat, args ... ) + 1; // Extra space for '\0'
    if( uiSize <= 0 ) { throw std::runtime_error( "Error during formatting." ); }
    std::unique_ptr<char[]> buf( new char[uiSize] );
    snprintf( buf.get(), uiSize, pFormat, args ... );
    return std::string( buf.get(), buf.get() + uiSize - 1 ); // We don't want the '\0' inside
#endif

}


class CCommonUtils
{
private:


public:
    CCommonUtils();

public:
    //static void SendLan( UINT uiOpCode );
    //static void SendLan( UINT uiOpCode, void *pData, UINT uiLength );
    //static void CloseSocket();

    static bool IsValidMinMax( float fMin, float fMax );

    static void DiffTimespec(struct timespec *result, struct timespec *start, struct timespec *stop=NULL, char *pStrMessage=NULL );

    static int CalcDiffAOA( int iAOA1, int iAOA2 );

	// SWAP 관련 함수
    static void AllSwapData16( void *pData, unsigned int uiLength );
    static void AllSwapData64( void *pData, unsigned int uiLength );
    static void AllSwapData32( void *pData, size_t szLength );

    static void swapByteOrder( unsigned int& ui );
    static void swapByteOrder( unsigned long long int &d);
    static void swapByteOrder(double & d);
    static void swapByteOrder(double *p, int iSize );
    static void swapByteOrder( unsigned short & us);

    //static ENUM_COLLECTBANK GetEnumCollectBank( int iCh );

	// 데이터 관련 출력 함수
    static void Disp_FinePDW( STR_PDWDATA *pPDWData );

	// 시간관련 함수
    static struct tm *GetLocaltime( time_t *ptiTime );
    static void getStringPresentTime( char *pString, size_t szString, bool bASCII =false );
    static void getStringDesignatedDate( char *pString, size_t szString, time_t tiTime );
	static void getStringDesignatedTime(char *pString, size_t szString, time_t tiTime);
    static void getFileNamingDesignatedTime(char *pString, size_t szString, time_t tiTime);
    static void GetCollectTime(struct timespec *pTimeSpec, time_t tColTime, unsigned int tColTimeMs );
    static void GetCollectTime( unsigned int *ptiContactTime, unsigned int *ptiContactTimems );
    static void GetCollectTime( struct timespec *pTimeSpec );
    static void GetCollectTime( unsigned int *ptiContactTime, unsigned short *ptiContactTimems );
    static DWORD GetDiffTime( struct timespec *pTimeSpec );

    static int CopySrcToDstFile( const char *src_file, const char *dest_file, int overwrite, int copy_attr );

    static const char *strcasestr( const char *haystack, const char *needle );
    static int Isalpha( int iCh );

    static size_t CheckMultiplyOverflow( int iSize, int iItems );

    static void PrintAllPDWs( STR_UZPOCKETPDW *pstPDW );
    static void PrintOnePDW( UZPOCKETPDW *pstPDW );
    static void MakeOnePDW( char *pszBuffer, UZPOCKETPDW *pstPDW );

    static void WallMakePrint( char *buffer, char delimeter, int iColumns= MAX_SCREEN_COLUMNS );
    static void CenterMakePrint( char *buffer, char delimeter, int iColumns = MAX_SCREEN_COLUMNS );
    static void WallMakePrint( char delimeter, int iColumns,  char *buffer, ... );

    static float Random( float fMin, float fMax );
    static int Random( int iMin, int iMax );

    static float NormalDistribution( float fMean, float fDevi );

    static unsigned long long int GetRawFileSize( char *pPathFileName );
    static unsigned long long int DiskFreeSpace( char *szDiskName );

    // 타입 변환시 사용하는 함수 모음
    //static unsigned int INT2UINT( int iValue );

    static ENUM_DataType WhatDataType( char *pStrPathname );
    static ENUM_UnitType WhatUnitType( char *pStrPathname );

    // 랜덤 값
    static int Rand( int range );

	// 문자열 파싱
	static void Parsing(vector<string> *pValues, string *pStrIn, string & strDelimiter);
	static unsigned int Parsing(vector<string> *pValues, const char *pData);

	// 폴더 및 파일 삭제
	static int DeleteAllFile(const char *pszDir );

	// 비트 관련 함수
    static unsigned int CountSetBits( const unsigned int uiValue );
    static unsigned int GetNoChannel( unsigned int &uiValue );

#ifdef __VXWORKS__
    // 랜/타스크 메시지 정의
    static void MakeStringMessage( std::string *pszString, unsigned int uiOpCode, bool bSend );
#else
    static void MakeStringMessage( std::string *pszString, unsigned int uiOpCode, bool bSend );
#endif

};


