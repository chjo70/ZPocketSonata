/**

    @file      ccommonutils.cpp
    @brief
    @details   ~
    @author    조철희
    @date      19.03.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#include "pch.h"

#ifdef _MSC_VER

#include <io.h>
#include <direct.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>


#include <sys/timeb.h>

#include <limits.h>


#include <stdint.h>

#include <sys/utime.h>

#include <fcntl.h>

#include <random>

std::default_random_engine generator;

#elif __VXWORKS__
#include <taskLib.h>
#include <ioLib.h>
#include <usrFsLib.h>


#include <stat.h>

#else
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>

#endif


#include "ccommonutils.h"

#ifndef _GRAPH_
#include "../System/csysconfig.h"

#include "../Anal/SigAnal/_Type.h"
#include "../Anal/Collect/DataFile/DataFile.h"

#include "../Include/globals.h"

#ifdef _LOG_
extern CSingleClient *g_pTheCCUSocket;

#endif

#else


#endif

/**
 * @brief 생성자를 수행합니다.
 */
CCommonUtils::CCommonUtils()
{

}

/**
 * @brief     IsValidMinMax
 * @param     T tMin
 * @param     T tMax
 * @return    bool
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-19 20:09:20
 * @warning
 */
bool CCommonUtils::IsValidMinMax( float fMin, float fMax )
{
    bool bRet = true;

    if( fMin > fMax || is_zero<float>( fMax ) == 0 ) {
        bRet = false;
    }

    return bRet;
}


#ifndef _GRAPH_

/**
 * @brief     GetCollectTime
 * @param     time_t * ptiContactTime
 * @param     unsigned short * ptiContactTimems
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-19 18:56:42
 * @warning
 */
void CCommonUtils::GetCollectTime( unsigned int *ptiContactTime, unsigned short *ptiContactTimems )
{
    struct timespec tsNow;

    CCommonUtils::GetCollectTime( &tsNow );

    *ptiContactTime = (unsigned int) tsNow.tv_sec;

#ifdef _MSC_VER
    *ptiContactTimems = ( unsigned int ) tsNow.tv_usec / ( unsigned int ) 1000;
#else
    *ptiContactTimems = tsNow.tv_nsec;
#endif

}

/**
 * @brief     GetCollectTime
 * @param     time_t * ptiContactTime
 * @param     unsigned int * ptiContactTimems
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-05-10 20:03:06
 * @warning
 */
void CCommonUtils::GetCollectTime( unsigned int *ptiContactTime, unsigned int *ptiContactTimems )
{
    struct timespec tsNow;

    CCommonUtils::GetCollectTime( &tsNow );

    *ptiContactTime = (unsigned int) tsNow.tv_sec;

#ifdef _MSC_VER
    *ptiContactTimems = ( unsigned int ) tsNow.tv_usec / ( unsigned int ) 1000;
#else
    *ptiContactTimems = tsNow.tv_nsec;
#endif

}

// void CCommonUtils::SendLan( UINT uiOpCode )
// {
//     CCommonUtils::SendLan( uiOpCode, NULL, 0 );
//
// }

/**
 * @brief opcode, data 를 입력받아서 랜으로 송신한다.
 * @param uiOpCode
 * @param uiLength
 * @param pData
 */
// void CCommonUtils::SendLan( UINT uiOpCode, void *pData, UINT uiLength )
// {
// #ifdef _USRDLL
//
// #else
// #if defined(_ELINT_) || defined(_XBAND_)
//
// #elif _POCKETSONATA_
// #ifndef _CGI_LIST_
//     // 마스터 보드에서는 랜 메시지를 CCU 장치로 전송한다.
//     if( g_enBoardId == enMaster ) {
//         if( g_pTheCCUSocket != NULL ) {
//             g_pTheCCUSocket->SendLan( uiOpCode, pData, uiLength );
//
//         }
//
//         // EA 경우에 AET 관련 메세지를 전달한다.
// //         if( g_pThePMCSocket != NULL ) { //&& ( uiOpCode == esAET_NEW_CCU || uiOpCode == esAET_UPD_CCU || uiOpCode == esAET_DEL_CCU ) ) {
// //             g_pThePMCSocket->SendLan( uiOpCode, pData, uiLength );
// //         }
//
//     }
//     // 클라이언트 보드 인 경우에는 랜 메시지를 마스터 보드에 전달한다.
//     else {
// //         if( g_pTheZYNQSocket != NULL ) {
// //             //g_pTheZYNQSocket->SendLan( uiOpCode, pData, uiLength );
// //         }
// //         else {
// //
// //         }
//     }
// #endif
// #endif
//
// #endif
//
// }

/**
 * @brief CCommonUtils::CloseSocket
 */
// void CCommonUtils::CloseSocket()
// {
// #ifdef _USRDLL
//
// #else
// #if defined(_ELINT_) || defined(_XBAND_)
//
// #elif _POCKETSONATA_
// #ifndef _CGI_LIST_
//     if( g_enBoardId == enMaster ) {
//         if( g_pTheCCUSocket != NULL ) {
//             g_pTheCCUSocket->CloseSocket();
//         }
//
//     }
//     else {
//
//     }
// #endif
// #endif
//
// #endif
//
// }



#ifdef _MSC_VER

/**
 * @brief     getFILETIMEoffset
 * @return    LARGE_INTEGER
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-05-23 15:14:49
 * @warning
 */
LARGE_INTEGER getFILETIMEoffset()
{
    SYSTEMTIME s;
    FILETIME f;
    LARGE_INTEGER t;

    s.wYear = 1970;
    s.wMonth = 1;
    s.wDay = 1;
    s.wHour = 0;
    s.wMinute = 0;
    s.wSecond = 0;
    s.wMilliseconds = 0;
    SystemTimeToFileTime(&s, &f);
    t.QuadPart = f.dwHighDateTime;
    t.QuadPart = (long long) ( (unsigned long long ) t.QuadPart << 32 );
    t.QuadPart = (long long)((unsigned long long) t.QuadPart | f.dwLowDateTime );
    return (t);
}

/**
 * @brief     gettimeofday
 * @param     struct timeval * tp
 * @param     struct timezone * tzp
 * @return    int
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-05, 14:51
 * @warning
 */
int gettimeofday(struct timeval * tp, struct timezone * tzp)
{
    // Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
    // This magic number is the number of 100 nanosecond intervals since January 1, 1601 (UTC)
    // until 00:00:00 January 1, 1970
    static const uint64_t EPOCH = ((uint64_t) 116444736000000000ULL);

    SYSTEMTIME  system_time;
    FILETIME    file_time;
    uint64_t    uiTime;

    GetSystemTime( &system_time );
    SystemTimeToFileTime( &system_time, &file_time );
    uiTime =  ((uint64_t)file_time.dwLowDateTime )      ;
    uiTime += ((uint64_t)file_time.dwHighDateTime) << 32;

    tp->tv_sec  = (long) ((uiTime - EPOCH) / 10000000L);
    tp->tv_usec = (long) (system_time.wMilliseconds * 1000);
    return 0;

}

/**
 * @brief     clock_gettime
 * @param     int X
 * @param     struct timeval * tv
 * @return    int
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-02-09, 17:34
 * @warning
 */
int clock_gettime(int X, struct timeval *tv)
{
    gettimeofday( tv, NULL );

    return (0);
}

/**
 * @brief     Random
 * @param     float fMin
 * @param     float fMax
 * @return    float
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-05-23 15:15:07
 * @warning
 */
float CCommonUtils::Random( float fMin, float fMax )
{
    float fRet, fRand;
    // std::uniform_int_distribution<float> dist( fMin, fMax );
    fRand = ( float ) rand() / ( float ) RAND_MAX;
    fRet = fMin + ( fRand * ( fMax - fMin ) );

    return fRet;

}

/**
 * @brief     NormalDistribution
 * @param     float fMean
 * @param     float fDevi
 * @return    float
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-07-16 15:13:38
 * @warning
 */
float CCommonUtils::NormalDistribution( float fMean, float fDevi )
{
    float fRet;

    std::normal_distribution<float> distribution( fMean, fDevi );

    fRet = distribution( generator );
    return fRet;

}

/**
 * @brief     Random
 * @param     int iMin
 * @param     int iMax
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-05-23 15:30:15
 * @warning
 */
int CCommonUtils::Random( int iMin, int iMax )
{
    int iRet;

    //iRet = ( rand() % ( iMax - iMin ) ) + iMin + 1;
    iRet = iMin + (int) ( ( ( float ) rand() / ( float ) RAND_MAX ) * (float) ( iMax - iMin + 1 ) );
    return iRet;

}


#endif

/**
 * @brief     현재 시간으로 문자열을 생성한다.
 * @param     char * pString
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-06-30, 17:27
 * @warning
 */
void CCommonUtils::getStringPresentTime( char *pString, size_t szString, bool bASCII )
{
    time_t nowTime=time(NULL);

#ifdef _MSC_VER
    struct tm stTime;
    localtime_s( & stTime, & nowTime );

    if( bASCII == true ) {
        strftime( pString, szString, "%Y_%m_%d_%H_%M_%S", & stTime );
    }
    else {
        strftime( pString, szString, "%Y-%m-%d %H:%M:%S", & stTime );
}

#else
    struct tm *pstTime;

    pstTime = localtime( & nowTime );

    if( bASCII == true ) {
        strftime(pString, szString, "%Y_%m_%d_%H_%M_%S", pstTime);
    }
    else {
        strftime( pString, szString, "%Y-%m-%d %H:%M:%S", pstTime );
    }

#endif

//     if( pstTime != NULL ) {
//         strftime( pString, szString, "%Y-%m-%d %H:%M:%S", pstTime );
//     }
//     else {
//         strcpy_s( pString, szString, "1970-01-01 00:00:00" );
//     }

}

/**
 * @brief     입력한 시간 정보로 문자열로 날짜를 구성한다.
 * @param     char * pString
 * @param     size_t szString
 * @param     time_t tiTime
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-05, 11:09
 * @warning
 */
void CCommonUtils::getStringDesignatedDate( char *pString, size_t szString, time_t tiTime )
{

#ifdef _MSC_VER
    strcpy_s( pString, szString, "1970-01-01 00:00:00" );
#else
    strcpy( pString, "1970-01-01 00:00:00" );
#endif

#ifdef _MSC_VER
    struct tm stTime;

    localtime_s( & stTime, & tiTime );
    strftime( pString, szString, "%Y-%m-%d %H:%M:%S", & stTime );

#else
    struct tm *pstTime;

    pstTime = localtime( & tiTime );

	if (pstTime != NULL) {
		strftime(pString, szString, "%Y-%m-%d %H:%M:%S", pstTime);
	}
	else {
#ifdef _MSC_VER
		*pString = NULL;
#else
        *pString = (char) '\0';
#endif
	}
#endif


}

/**
 * @brief     getStringDesignatedTime
 * @param     char * pString
 * @param     size_t szString
 * @param     time_t tiTime
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-31 12:04:16
 * @warning
 */
void CCommonUtils::getStringDesignatedTime(char *pString, size_t szString, time_t tiTime)
{

#ifdef _MSC_VER
	strcpy_s(pString, szString, "00:00:00");
#else
	strcpy(pString, "1970-01-01 00:00:00");
#endif

#ifdef _MSC_VER
    struct tm stTime;
	localtime_s( & stTime, &tiTime );

    strftime( pString, szString, "%H:%M:%S", & stTime );
#else
    struct tm *pstTime;

    pstTime = localtime( &tiTime );

	if (pstTime != NULL) {
		strftime(pString, szString, "%H:%M:%S", pstTime);
	}
	else {
#ifdef _MSC_VER
		*pString = NULL;
#else
        *pString = (char) '\0';
#endif
	}
#endif

}

/**
 * @brief     getFileNamingDesignatedTime
 * @param     char * pString
 * @param     size_t szString
 * @param     time_t tiTime
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2022-11-04 15:10:51
 * @warning
 */
void CCommonUtils::getFileNamingDesignatedTime(char *pString, size_t szString, time_t tiTime)
{


#ifdef _MSC_VER
    strcpy_s(pString, szString, "1970-01-01 00:00:00");
#else
    strcpy(pString, "1970-01-01 00:00:00");
#endif



#ifdef _MSC_VER
    struct tm stTime;

    localtime_s( &stTime, &tiTime );
    strftime( pString, szString, "%Y-%m-%d %H_%M_%S", & stTime );

#else
    struct tm *pstTime;

    pstTime = localtime( &tiTime );
    if (pstTime != NULL) {
        strftime(pString, szString, "%Y-%m-%d %H_%M_%S", pstTime);
    }
    else {
#ifdef _MSC_VER
        *pString = NULL;
#else
        *pString = (char) '\0';
#endif
    }
#endif

}

/**
 * @brief     GetCollectTime
 * @param     struct timespec * pTimeSpec
 * @param     time_t tColTime
 * @param     unsigned int m_tColTimeMs
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-18, 11:36
 * @warning
 */
void CCommonUtils::GetCollectTime(struct timespec *pTimeSpec, time_t tColTime, unsigned int tColTimeMs )
{
    if (tColTime == 0) {
        clock_gettime(CLOCK_REALTIME, pTimeSpec);
    }
    else {
        pTimeSpec->tv_sec = (long) tColTime;
#ifdef _MSC_VER
        pTimeSpec->tv_usec = (long) tColTimeMs * (long) 1000;
#else
        pTimeSpec->tv_nsec = tColTimeMs * 1000000;
#endif

    }

    return;

}

/**
 * @brief     GetCollectTime
 * @param     struct timespec * pTimeSpec
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-02-03 11:49:46
 * @warning
 */
void CCommonUtils::GetCollectTime( struct timespec *pTimeSpec )
{
    clock_gettime( CLOCK_REALTIME, pTimeSpec );

    return;

}

/**
 * @brief     GetDiffTime
 * @param     struct timespec * pTimeSpec
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-05-20 17:33:38
 * @warning
 */
DWORD CCommonUtils::GetDiffTime( struct timespec *pTimeSpec )
{
    struct timespec tsNow, tsDiff;
    DWORD ret = 0;

    clock_gettime( CLOCK_REALTIME, & tsNow );

#ifdef _MSC_VER
    tsDiff.tv_sec = tsNow.tv_sec - pTimeSpec->tv_sec;
    if( tsNow.tv_usec >= pTimeSpec->tv_usec ) {
        tsDiff.tv_usec = tsNow.tv_usec - pTimeSpec->tv_usec;
    }
    else {
        tsDiff.tv_sec = tsDiff.tv_sec - 1;
        tsDiff.tv_usec = 1000000000 + tsNow.tv_usec - pTimeSpec->tv_usec;
    }

    //printf( "\n tsDiff.tv_sec[%u]", tsDiff.tv_sec );
    //printf( "\n tsDiff.tv_nsec[%u]", tsDiff.tv_usec );

    ret = ( DWORD ) ( ( 1000000000 ) * tsDiff.tv_sec + tsDiff.tv_usec );

#else
    tsDiff.tv_sec = tsNow.tv_sec - pTimeSpec->tv_sec;
    if( tsNow.tv_nsec >= pTimeSpec->tv_nsec ) {
        tsDiff.tv_nsec = tsNow.tv_nsec - pTimeSpec->tv_nsec;
    }
    else {
        tsDiff.tv_sec = tsDiff.tv_sec - 1;
        tsDiff.tv_nsec = 1000000000 + tsNow.tv_nsec - pTimeSpec->tv_nsec;
    }

    ret = ( 1000000000 ) * tsDiff.tv_sec + tsDiff.tv_nsec;

#endif

    return ret;

}

/**
 * @brief     CopyFile
 * @param     const char * src_file
 * @param     const char * dest_file
 * @param     int overwrite
 * @param     int copy_attr
 * @return    int
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-06-30, 17:27
 * @warning
 */
int CCommonUtils::CopySrcToDstFile( const char *src_file, const char *dest_file, int overwrite, int copy_attr )
{
    int iRet=-1;
    int     src_fd;
    int     dest_fd;
    struct  stat sts;
    char    read_data_buf[4096], write_data_buff[4096];
    int     tmp_errno;
    int iSize;

    // printf( "\n\t[%s]을 [%s]으로 복사중..." , src_file, dest_file );

#if defined(__linux__) || defined(__VXWORKS__)
    src_fd = open(src_file, O_RDONLY , 0644 );
#else
    src_fd = open(src_file, O_RDONLY | O_BINARY );

#endif

    if( src_fd != -1) {
        memset( & sts, 0, sizeof(sts) );

        /* 원본 file의 속성을 읽습니다. */
        fstat(src_fd, &sts);

        if(overwrite) { /* 이미 파일이 있으면 overwrite를 하겠다면... */
            dest_fd = open(dest_file, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, sts.st_mode);
        } else {        /* 파일이 있으면, 생성하지 말라고 설정한 경우 */
            dest_fd = open(dest_file, O_WRONLY | O_CREAT | O_EXCL | O_BINARY, sts.st_mode);
        }

        if(dest_fd == -1) {
            tmp_errno = errno;
            _close(src_fd);
            errno = tmp_errno; // close가 초기화한 errno를 복구함
            WhereIs;
            //return -1;
        }
        else {
            do {
                iSize = read(src_fd, read_data_buf, 4096);
                if( iSize <= 0 ) {
                    break;
                }
                iRet += iSize;

                memcpy( write_data_buff, read_data_buf, sizeof(char)*(size_t) iSize );
                while(write(dest_fd, write_data_buff, (unsigned int) iSize ) == -1) {
                    if(errno == EINTR) {
                        /* signal이 발생한 경우에는 재작업 */
                        continue;
                    } else {
                        /* disk가 full났거나 무슨 일이 있음. */
                        tmp_errno = errno;
                        _close(src_fd);
                        _close(dest_fd);
                        errno = tmp_errno;
                    }
                }
            }
            while( true );

            _close(src_fd);
            _close(dest_fd);
        }

        /* 원본 파일의 속성을 복원해야 한다면... */
        if(copy_attr && dest_fd != -1 ) {
            /* 원본 파일의 파일 권한을 복원하기
            * open시에 파일권한을 설정하였지만,
            * 이미 존재했던 파일은 파일권한이 기존 파일의 권한이므로
            * 파일의 권한도 복구합니다.
            */
            // chmod(dest_file, sts.st_mode);

#ifdef __VXWORKS__

#elif defined(__linux__)

#else
        	struct  utimbuf attr;

            /* last access 시간, last modify 시간 복구 */
            attr.actime  = sts.st_atime;
            attr.modtime = sts.st_mtime;
            utime(dest_file, &attr);
#endif

        }
    }

    return iRet;
}

/**
 * @brief CCommonUtils::timespec_diff
 * @param result
 * @param start
 * @param stop
 */
void CCommonUtils::DiffTimespec(struct timespec *result, struct timespec *start, struct timespec *stop )
{
    struct timespec tsNow;

    if( stop != NULL ) {
        tsNow.tv_sec = stop->tv_sec;
#ifdef _MSC_VER
        tsNow.tv_usec = stop->tv_usec;
#else
        tsNow.tv_nsec = stop->tv_nsec;
#endif
    }
    else {
        clock_gettime( CLOCK_REALTIME, & tsNow );
    }

#ifdef _MSC_VER
    if ((tsNow.tv_usec - start->tv_usec) < 0) {
        result->tv_sec = tsNow.tv_sec - start->tv_sec - 1;
        result->tv_usec = tsNow.tv_usec - start->tv_usec + 1000000;
    } else {
        result->tv_sec = tsNow.tv_sec - start->tv_sec;
        result->tv_usec = tsNow.tv_usec - start->tv_usec;
    }
#else
    if ((tsNow.tv_nsec - start->tv_nsec) < 0) {
        result->tv_sec = tsNow.tv_sec - start->tv_sec - 1;
        result->tv_nsec = tsNow.tv_nsec - start->tv_nsec + 1000000000;
    } else {
        result->tv_sec = tsNow.tv_sec - start->tv_sec;
        result->tv_nsec = tsNow.tv_nsec - start->tv_nsec;
    }

#endif

    return;
}


/**
 * @brief     CalcDiffAOA
 * @param     int iAOA1
 * @param     int iAOA2
 * @return    int
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-23, 17:09
 * @warning
 */
int CCommonUtils::CalcDiffAOA( int iAOA1, int iAOA2 )
{
    int iDiffAOA;

    iDiffAOA = _diffabs<int>( iAOA1, iAOA2 );
    if( iDiffAOA > MAX_AOA_BIT / 2 ) {
        iDiffAOA = MAX_AOA_BIT - iDiffAOA;
    }

    return iDiffAOA;
}

/**
 * @brief CCommonUtils::Disp_FinePDW
 * @param pPDWData
 */
void CCommonUtils::Disp_FinePDW( STR_PDWDATA *pPDWData )
{

#ifdef __ZYNQ_BOARD__
    return;

#else
    _PDW *pPDW;
    _TOA ullfirstTOA;

    pPDW = & pPDWData->pstPDW[0];
    ullfirstTOA = pPDW->tTOA;

#if defined(_POCKETSONATA_) || defined(_712_)
    unsigned int i;

    for( i=0 ; i < pPDWData->GetTotalPDW() ; ++i ) {
        printf( "[%4d]\t%012llX(%.1f[us]) %5.1f %.3fMHz[0x%X] %.3fns[0x%X] \n" , i+1, \
                pPDW->tTOA, CPOCKETSONATAPDW::DecodeTOAus( pPDW->tTOA-ullfirstTOA ), \
                CPOCKETSONATAPDW::DecodeDOA( (int) pPDW->uiAOA), \
                CPOCKETSONATAPDW::DecodeFREQMHz( pPDW->uiFreq), pPDW->uiFreq,
                CPOCKETSONATAPDW::DecodePW( (int) pPDW->uiPW), pPDW->uiPW );
        ++ pPDW;
    }
#elif defined(_ELINT_) || defined(_XBAND_)
    unsigned int i;

    for( i=0 ; i < pPDWData->GetTotalPDW() ; ++i ) {
        printf( "[%4d]\t%012llX(%.1f[us]) %5.1f %.3fMHz[0x%X] %.3fns[0x%X] \n" , i+1, \
            pPDW->ullTOA, CEPDW::DecodeTOAus( pPDW->ullTOA-ullfirstTOA, pPDWData->x.el.enBandWidth ), \
            CEPDW::DecodeDOA((int)pPDW->uiAOA), \
            CEPDW::DecodeFREQMHz((int)pPDW->uiFreq), pPDW->uiFreq,
            CEPDW::DecodePW( (int) pPDW->uiPW, pPDWData->x.el.enBandWidth ), pPDW->uiPW );
        ++ pPDW;
    }

#elif defined(_701_)
    unsigned int i;

	for (i = 0; i < pPDWData->GetTotalPDW(); ++i) {
		printf("[%4d]\t%012llX(%.1f[us]) %5.1f %.3fMHz[0x%X] %.3fns[0x%X] \n", i + 1, \
			pPDW->ullTOA, C7PDW::DecodeTOAus(pPDW->ullTOA - ullfirstTOA, pPDWData->x.e7.enBandWidth), \
			C7PDW::DecodeDOA((int)pPDW->uiAOA), \
			C7PDW::DecodeFREQMHz((int)pPDW->uiFreq), pPDW->uiFreq,
			C7PDW::DecodePW((int)pPDW->uiPW, pPDWData->x.e7.enBandWidth), pPDW->uiPW);
		++pPDW;
	}

#endif

    return;

#endif

}



#endif	// _GRAPH_


/**
 * @brief     AllSwapData16
 * @param     void * pData
 * @param     unsigned int uiLength
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-07 10:50:27
 * @warning
 */
void CCommonUtils::AllSwapData16( void *pData, unsigned int uiLength )
{
    UINT i;
    unsigned short *pWord16;

    pWord16 = ( unsigned short * ) pData;
    for( i = 0; i < uiLength; i += sizeof( short ) ) {
        swapByteOrder( *pWord16 );
        ++ pWord16;
    }

}

/**
 * @brief     AllSwapData32
 * @param     void * pData
 * @param     unsigned int uiLength
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-06-07 10:49:11
 * @warning
 */
void CCommonUtils::AllSwapData32( void *pData, unsigned int uiLength )
{
    UINT i;
    UINT *pWord;

    pWord = (UINT *) pData;
    for( i=0 ; i < uiLength; i+=sizeof(int) ) {
        swapByteOrder( *pWord );
        ++ pWord;
    }

}

/**
 * @brief		AllSwapData64
 * @param		void * pData
 * @param		unsigned int uiLength
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/04/11 19:58:15
 * @warning
 */
void CCommonUtils::AllSwapData64( void *pData, unsigned int uiLength )
{
    UINT i;
    unsigned long long int *pWord;

    pWord = ( unsigned long long int * ) pData;
    for( i = 0; i < uiLength; i += sizeof( unsigned long long int ) ) {
        swapByteOrder( *pWord );
        ++pWord;
    }

}

/**
 * @brief		swapByteOrder
 * @param		unsigned short & us
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/11/18 19:16:45
 * @warning
 */
void CCommonUtils::swapByteOrder(unsigned short& us)
{
    us = (us >> 8) | ((us<<8) & (unsigned short) 0xFF00);
}

/**
 * @brief		swapByteOrder
 * @param		unsigned int & ui
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/02/21 19:24:16
 * @warning
 */
void CCommonUtils::swapByteOrder(unsigned int& ui)
{
    ui = (ui >> 24) | ((ui<<8) & 0x00FF0000) | ((ui>>8) & 0x0000FF00) | (ui << 24);
}

/**
 * @brief		swapByteOrder
 * @param		double & di
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2021/11/18 19:06:02
 * @warning
 */
void CCommonUtils::swapByteOrder(double & d)
{
    uint64_t um = (uint64_t) & d;

    d = (double) ( ( ( um & 0xff00000000000000 ) >> 56 ) |
                   ( ( um & 0x00ff000000000000 ) >> 40 ) |
                   ( ( um & 0x0000ff0000000000 ) >> 24 ) |
                   ( ( um & 0x000000ff00000000 ) >> 8 ) |
                   ( ( um & 0x00000000ff000000 ) << 8 ) |
                   ( ( um & 0x0000000000ff0000 ) << 24 ) |
                   ( ( um & 0x000000000000ff00 ) << 40 ) |
                   ( ( um & 0x00000000000000ff ) << 56 ) );
}

/**
 * @brief     swapByteOrder
 * @param		unsigned long long int & d
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/04/11 19:33:36
 * @warning
 */
void CCommonUtils::swapByteOrder( unsigned long long int  &d )
{
    unsigned long long int um = ( unsigned long long int ) d;

    d = ( unsigned long long int ) ( ( ( um & 0xff00000000000000 ) >> 56 ) |
        ( ( um & 0x00ff000000000000 ) >> 40 ) |
        ( ( um & 0x0000ff0000000000 ) >> 24 ) |
        ( ( um & 0x000000ff00000000 ) >> 8 ) |
        ( ( um & 0x00000000ff000000 ) << 8 ) |
        ( ( um & 0x0000000000ff0000 ) << 24 ) |
        ( ( um & 0x000000000000ff00 ) << 40 ) |
        ( ( um & 0x00000000000000ff ) << 56 ) );
}

/**
 * @brief     swapByteOrder
 * @param     double * p
 * @param     int iSize
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-01-10, 13:49
 * @warning
 */
void CCommonUtils::swapByteOrder(double *p, int iSize )
{
    int i;

    for( i=0 ; i < iSize ; ++i ) {
        swapByteOrder( p[i] );
    }
}


/**
 * @brief     SetUnitType
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-02-22, 13:18
 * @warning
 */
// void CCommonUtils::SetUnitType()
// {
// #ifdef _POCKETSONATA_
//     g_enUnitType = en_ZPOCKETSONATA;
// #elif defined(_ELINT_)
//     g_enUnitType = en_ELINT;
// #elif defined(_XBAND_)
//     g_enUnitType = en_XBAND;
// #else
//     g_enUnitType = en_UnknownUnit;
//
// #endif
// }

/**
 * @brief     strcasestr
 * @param     const char * pStr
 * @param     const char * pCompare
 * @return    char *
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-03-14, 16:55
 * @warning
 */
const char *CCommonUtils::strcasestr( const char *pStr, const char *pCompare )
{
    size_t i, j;
    const char *pRet;

    const char *pStr2;

    pRet = NULL;

    size_t iLen = strlen( pStr );
    size_t iTo = strlen( pCompare );

    if( iLen >= iTo ) {
        pStr2 = pStr;
        for( i=0 ; i <= iLen-iTo ; ++i ) {
            for( j=0 ; j < iTo ; ++j ) {
                if( Isalpha( pStr2[j] ) >= 1 ) {
                    int iDiff = pStr2[j] - pCompare[j];
                    if( iDiff != 0x20 && iDiff != -0x20 && iDiff != 0 ) {
                        break;
                    }
                }
                else {
                    if( pStr2[j] != pCompare[j] ) {
                        break;
                    }
                }
            }

            if( j >= iTo ) {
                pRet = pStr2;
                break;
            }

            ++ pStr2;
        }
    }

    return pRet;

}

/**
 * @brief     Isalpha
 * @param     int iCh
 * @return    int
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-03-29, 11:27
 * @warning
 */
int CCommonUtils::Isalpha( int iCh )
{
    int iRet;

    if( iCh >= 'A' && iCh <= 'Z' ) {
        iRet = 1;
    }
    else if( iCh >= 'a' && iCh <= 'z' ) {
        iRet = 2;
    }
    else {
        iRet = 0;
    }

    return iRet;
}

/**
 * @brief     IsMultiplyOverflow
 * @param     size_t uiSize
 * @param     size_t uiItems
 * @return    size_t
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-03-15, 14:18
 * @warning
 */
size_t CCommonUtils::CheckMultiplyOverflow( int iSize, int iItems )
{
    size_t szSize=0;
    int iMultiply;

    try {

		if( iSize <= 0 || iItems <= 0 ) {
            iItems = 10;
            iSize = 10;
			// throw 0;
		}

        //else if( iSize > (INT_MAX / iItems) || iSize < ((int) INT_MIN / iItems) ) {
        else if( iSize > ( INT_MAX / iItems ) ) {
            throw 0;
        }

        else {
			iMultiply = iSize * iItems;

            if( iSize != iMultiply / iItems ) {
                throw 0;
            }

            else {
                szSize = (size_t) iMultiply;
            }
        }

    }
    catch( int iExp ) {
        szSize = (size_t) iExp;
    }

    return szSize;

}

/**
 * @brief     INT2UINT
 * @param     int iValue
 * @return    unsigned int
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-03-28, 19:22
 * @warning
 */
// unsigned int CCommonUtils::INT2UINT( int iValue )
// {
//     unsigned int iRet=0;
//
//     if( iValue >= 0 ) {
//         iRet = iValue;
//     }
//
//     return iRet;
//
// }

/**
 * @brief     파일명으로 데이터형태를 식별합니다.
 * @param     char * pStrPathname
 * @return    ENUM_DataType
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-04-28, 13:47
 * @warning
 */
ENUM_DataType CCommonUtils::WhatDataType( char *pStrPathname )
{
    ENUM_DataType enDataType = en_UnknownData;

    if( NULL != CCommonUtils::strcasestr( pStrPathname, ".pdw" ) || NULL != CCommonUtils::strcasestr( pStrPathname, ".npw" ) || NULL != CCommonUtils::strcasestr( pStrPathname, ".spdw" ) ) {
		if (NULL != CCommonUtils::strcasestr(pStrPathname, ".csv")) {
			enDataType = en_PDW_DATA_CSV;
        }
		else {
			enDataType = en_PDW_DATA;
        }
    }
    else if( NULL != CCommonUtils::strcasestr( pStrPathname, "e4.dat" ) ) {
        enDataType = en_PDW_DATA;
    }
    else if( NULL != CCommonUtils::strcasestr( pStrPathname, ".kpdw" ) ) {
        enDataType = en_PDW_DATA;
    }
    else if( NULL != CCommonUtils::strcasestr( pStrPathname, ".iq" ) || NULL != CCommonUtils::strcasestr( pStrPathname, ".siq" ) ||
        NULL != CCommonUtils::strcasestr( pStrPathname, "e2.dat" ) || NULL != CCommonUtils::strcasestr( pStrPathname, ".eiq" ) ) {
        enDataType = en_IQ_DATA;
    }
    else if( NULL != CCommonUtils::strcasestr( pStrPathname, ".epdw" ) || NULL != CCommonUtils::strcasestr( pStrPathname, ".enpw" ) || NULL != strstr( pStrPathname, ".zpdw" ) ) {
        enDataType = en_PDW_DATA;
    }
    else if( NULL != CCommonUtils::strcasestr( pStrPathname, ".xpdw" ) ) {
        enDataType = en_PDW_DATA;
    }
	else if (NULL != CCommonUtils::strcasestr(pStrPathname, ".7pdw")) {
		enDataType = en_PDW_DATA;
	}
    else {
        //LOGMSG1( enError, "잘못된 파일명 입니다. 데이터 형식을 모릅니다." );
        TRACE( "잘못된 파일명 입니다." );
    }

    return enDataType;

}

/**
 * @brief	  파일명으로 장비명을 식별합니다.
 * @return    ENUM_UnitType
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2020/03/12 19:38:24
 * @warning
 */
ENUM_UnitType CCommonUtils::WhatUnitType( char *pStrPathname )
{
    ENUM_UnitType enUnitType;

    if( NULL != CCommonUtils::strcasestr( pStrPathname, ".midas" ) ) {
        enUnitType = en_MIDAS;
    }
	else if (NULL != CCommonUtils::strcasestr(pStrPathname, ".dat") || NULL != CCommonUtils::strcasestr(pStrPathname, ".701") || NULL != CCommonUtils::strcasestr(pStrPathname, ".7pdw") ) {
		enUnitType = en_701;
	}
    else if( NULL != CCommonUtils::strcasestr( pStrPathname, ".pdw" ) || NULL != CCommonUtils::strcasestr( pStrPathname, ".npw" ) ||
        NULL != CCommonUtils::strcasestr( pStrPathname, ".iq" ) || NULL != CCommonUtils::strcasestr( pStrPathname, ".siq" ) ) {
        enUnitType = en_SONATA;
    }
    else if( NULL != CCommonUtils::strcasestr( pStrPathname, ".spdw" ) ) {
        enUnitType = en_SONATA_SHU;
    }

    else if( NULL != CCommonUtils::strcasestr( pStrPathname, ".kpdw" ) ) {
        enUnitType = en_KFX;
    }
    else if( NULL != CCommonUtils::strcasestr( pStrPathname, ".epdw" ) || NULL != CCommonUtils::strcasestr( pStrPathname, ".enpw" ) ) {
        enUnitType = en_ELINT;
    }
    else if( NULL != CCommonUtils::strcasestr( pStrPathname, ".zpdw" ) || NULL != CCommonUtils::strcasestr( pStrPathname, ".znpw" ) ) {
        enUnitType = en_ZPOCKETSONATA;
    }
    else if( NULL != CCommonUtils::strcasestr( pStrPathname, ".xpdw" ) ) {
        enUnitType = en_XBAND;
    }
    else {
        enUnitType = en_UnknownUnit;
    }

    return enUnitType;

}


/**
 * @brief     입력 값을 기준으로 +- range 범위의 랜덤 값을 리턴한다.
 * @param     int range
 * @return    int
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-05-10, 10:16
 * @warning
 */
int CCommonUtils::Rand( int range )
{
    int random_val = 0;

    if( range == 0 ) {
    }
    else {
        random_val = rand() % (2 * range + 1);
        random_val -= range;
    }

    return random_val;

}

/**
 * @brief     Parsing
 * @param     string strIn
 * @param     vector<string> * pValues
 * @param     string * pStrDelimiter
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-18 10:28:19
 * @warning
 */
void CCommonUtils::Parsing(vector<string> *pValues, string *pStrIn, string & strDelimiter)
{
	size_t pos = 0;
	string token;

	//while ((pos = pStrIn->find(strDelimiter)) != string::npos) {
    while( true ) {
        pos = pStrIn->find( strDelimiter );
        if( pos == string::npos ) {
            break;
        }

		token = pStrIn->substr(0, pos);
		pValues->push_back(token);
		pStrIn->erase( 0, pos + strDelimiter.length());
	}

	pValues->push_back(*pStrIn);

}

#if defined(_GRAPH_) || defined(_701_)
/**
 * @brief     \r\n 으로 라인이 구성이 되어야 제대로 해석이 됨.
 * @param     vector<string> * pValues
 * @param     const char * pData
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-18 11:29:06
 * @warning
 */
unsigned int CCommonUtils::Parsing(vector<string> *pValues, const char *pData )
{
	unsigned int iIndex;
	char szBuffer[100];

	pValues->clear();

#ifdef _MSC_VER
    szBuffer[0] = NULL;
#else
	szBuffer[0] = (char) '\0';
#endif


	iIndex = 0;
	while ( pData[iIndex] != '\n' ) {
		sscanf( & pData[iIndex], "%[^','|'\r']", szBuffer );
		iIndex += (strlen(szBuffer) + 1);
		pValues->push_back( szBuffer );

	}

	return iIndex + 1;

}
#endif

/**
 * @brief     DeleteAllFile
 * @param     char * pszDir
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-24 11:22:41
 * @warning
 */
// void CCommonUtils::DeleteAllFile(char *pszDir)
// {
// #ifdef _MSC_VER
//
// 	// RmDirs(pszDir, 0);
//

// #elif defined(_linux_)
// 	rmdirs( pszDir, 0 );
// #endif
//
// }

/**
 * @brief     DeleteAllFile
 * @param     const char * pszDir
 * @param     int iForce
 * @return    int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-05-20 12:02:13
 * @warning
 */
int CCommonUtils::DeleteAllFile(const char *pszDir )
{
#ifdef __linux__
	DIR *  dir_ptr = NULL;
	struct dirent *file = NULL;
	struct stat   buf;
	char   filename[1024];

	/* 목록을 읽을 디렉토리명으로 DIR *를 return 받습니다. */
	if ((dir_ptr = opendir(path)) == NULL) {
		/* path가 디렉토리가 아니라면 삭제하고 종료합니다. */
		return unlink(path);
	}

	/* 디렉토리의 ���음부터 파일 또는 디렉토리명을 순서대로 한개씩 읽습니다. */
	while ((file = readdir(dir_ptr)) != NULL) {
		// readdir 읽혀진 파일명 중에 현재 디렉토리를 나타네는 . 도 포함되어 있으므로
		// 무한 반복에 빠지지 않으려면 파일명이 . 이면 skip 해야 함
		if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0) {
			continue;
		}

		sprintf(filename, "%s/%s", path, file->d_name);

		/* 파일의 속성(파일의 유형, 크기, 생성/변경 시간 등을 얻기 위하여 */
		if (lstat(filename, &buf) == -1) {
			continue;
		}

		if (S_ISDIR(buf.st_mode)) { // 검색된 이름의 속성이 디렉토리이면
			/* 검색된 파일이 directory이면 재귀호출로 하위 디렉토리를 다시 검색 */
			if (rmdirs(filename, force) == -1 && !force) {
				return -1;
			}
		}
		else if (S_ISREG(buf.st_mode) || S_ISLNK(buf.st_mode)) { // 일반파일 또는 symbolic link 이면
			if (unlink(filename) == -1 && !force) {
				return -1;
			}
		}
	}

	/* open된 directory 정보를 close 합니다. */
	closedir(dir_ptr);

	return rmdir(path);
#elif defined(_MSC_VER)
	if (pszDir[0] != 0) {
		CString strName;
		strName.Format("%s\\*.*", pszDir);

		CFileFind ff;

		bool bFind = ff.FindFile(strName);

		while (bFind) {
            BOOL bRet1, bRet2;

			bFind = ff.FindNextFile();
            bRet1 = ff.IsDots();
            bRet2 = ff.IsDirectory();
			if ( bRet1 == TRUE || bRet2 == TRUE ) {
                continue;
            }
			SetFileAttributes(ff.GetFilePath(), FILE_ATTRIBUTE_NORMAL);
			DeleteFile( ff.GetFilePath() );
		}

		ff.Close();

	}

	return 0;

#else
    STATUS status;

    status = xdelete( pszDir );
    if( OK == status ) {
    }
    else {
        //printf( "\n pszDir[%s]", pszDir );
        //WhereIs;

    }

	return 0;

#endif

}

/**
 * @brief     CountSetBits
 * @param     unsigned int uiValue
 * @return    unsigned int
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-02-28 10:27:05
 * @warning
 */
unsigned int CCommonUtils::CountSetBits( unsigned int uiValue )
{
    unsigned int uiCount=0;

    while( uiValue ) {
        uiCount += (unsigned int) ( uiValue & (unsigned int) 1 );
        uiValue >>= 1;
    }
    return uiCount;
}

/**
 * @brief		GetNoChannel
 * @param		unsigned int uiValue
 * @return		unsigned int
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/03/11 17:15:38
 * @warning
 */
unsigned int CCommonUtils::GetNoChannel( unsigned int & uiValue )
{
    unsigned int uiCount = 0;

    while( uiValue ) {
        if( ( unsigned int ) ( uiValue & ( unsigned int ) 1 ) ) {
            break;
        }
        uiValue >>= 1;
        ++uiCount;
    }

    return uiCount;
}

/**
 * @brief		DisplayMsg
 * @param		STR_LAN_HEADER * pHeader
 * @param		void * pData
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/03/11 17:15:40
 * @warning
 */
void CCommonUtils::MakeStringMessage( std::string *pszString, unsigned int uiOpCode, bool bSend )
{
    switch( uiOpCode ) {
        // 운용 관련 메시지
        case enRES_OP_START:
            *pszString = "시작";
            break;

        case enRES_OP_SHUTDOWN:
            *pszString = "종료";
            break;

        case enRES_OP_RESTART:
            *pszString = "재시작";
            break;

            // 분석 관련 메시지
        case enRES_IBIT:
            *pszString = "초기자체점검";
            break;

        case enRES_UBIT:
            *pszString = "장비자체점검";
            break;

        case enRES_CBIT:
            *pszString = "연속자체점검";
            break;

        case enRES_SETSYS:
            *pszString = "신호분석 변수 설정 요청";
            break;

        case enRES_SYS:
            *pszString = "신호분석 변수 요청";
            break;

        case enTHREAD_DISCONNECTED:
            *pszString = "랜 단락";
            break;

        case enTHREAD_DETECTANAL_START:
            *pszString = "탐지분석 시작";
            break;

        case enTHREAD_DETECTANAL_RESULT:
            *pszString = "탐지분석 결과";
            break;

        case enTHREAD_SCANANAL_START:
            *pszString = "스캔분석 시작";
            break;

        case enTHREAD_SCANANAL_RESULT:
            *pszString = "스캔분석 결과";
            break;

        case enTHREAD_SCANANAL_FAIL:
            *pszString = "스캔분석 실패";
            break;

        case enTHREAD_SCANANAL_ERROR:
            *pszString = "스캔분석 에러";
            break;

        case enTHREAD_REQ_SET_DETECTWINDOWCELL:
            *pszString = "탐지 수집";
            break;

        case enTHREAD_REQ_SCAN_START:
            *pszString = "스캔분석 시작";
            break;

        case enREQ_ANAL_SCAN:
            *pszString = "운용자 스캔 분석";
            break;

//         case enTHREAD_REQ_SET_SCANWINDOWCELL:
//             *pszString = "스캔 수집 요청";
//             break;

        case enREQ_RELOAD_LIBRARY:
            *pszString = "위협 라이브러리 다운로드 시작 요청";
            break;

        case enNUP_THREAT_DATA:
            *pszString = "방사체/빔/LOB 데이터";
            break;

        case enTHREAD_LOG:
            *pszString = "로그";
            break;

        case enRES_SYSERROR:
            *pszString = "에러";
            break;

        default:
            *pszString = "이름 없음";
            break;
    }

    if( bSend == true ) {
        *pszString += " 요청";
    }
    else {
        *pszString += " 응답";
    }

    //LOGMSG4( enDebug, "$랜 송신: Op[%s:0x%04X], Len[%d], Data32[0x%x]" , szOpcode, pHeader->uiOpCode, pHeader->uiLength, (UINT) *pData);
    //LOGMSG3( enDebug, "$랜 송신: Op[%s:0x%04X], Len[%d]", szOpcode, pHeader->uiOpCode, pHeader->uiLength );

}


/**
 * @brief     PrintAllPDW
 * @param     STR_UZPOCKETPDW * pstPDW
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-10 20:25:12
 * @warning
 */
void CCommonUtils::PrintAllPDWs( STR_UZPOCKETPDW *i_pstPDW )
{
    unsigned int ui, uiTotalPDW;

    char szBuffer[300];

    _TOA prellTOA=0;

    UZPOCKETPDW *pstPDW;

    uiTotalPDW = i_pstPDW->GetTotalPDW();

    pstPDW = i_pstPDW->pstPDW;

#ifdef _GRAPH_
    TRACE( "PDW [%d]개를 출력 합니다. -------------------------------------------------", uiTotalPDW );
#else
    //LOGMSG1( enDebug, "PDW [%d]개를 출력 합니다. -------------------------------------------------", uiTotalPDW );
#endif

    for( ui = 0; ui < uiTotalPDW && ui < 10 ; ++ui ) {
        MakeOnePDW( szBuffer, pstPDW );

#ifdef _GRAPH_
        if( ui == 0 || prellTOA < pstPDW->stHwPdwDataRf.ullTOA ) {
            TRACE( " %s", szBuffer );
        }
        else {
            TRACE( "!%s", szBuffer );
        }
#else
        if( ui == 0 || prellTOA < pstPDW->stHwPdwDataRf.ullTOA ) {
            //LOGMSG1( enDebug, " %s", szBuffer );
        }
        else {
            //LOGMSG1( enDebug, "!%s", szBuffer );
        }
#endif

        prellTOA = pstPDW->stHwPdwDataRf.ullTOA;

        ++ pstPDW;
    }

}

/**
 * @brief		PrintOnePDW
 * @param		UZPOCKETPDW * pstPDW
 * @return		void
 * @author		조철희 (churlhee.jo@lignex1.com)
 * @version		0.0.1
 * @date		2023/04/11 20:32:54
 * @warning
 */
void CCommonUtils::PrintOnePDW( UZPOCKETPDW *pstPDW )
{
    char szBuffer[300];

    MakeOnePDW( szBuffer, pstPDW );

#ifdef _GRAPH_
    TRACE( " %s", szBuffer );
#else
    // LOGMSG1( enDebug, " %s", szBuffer );
#endif

}

/**
 * @brief     MakeOnePDW
 * @param     char * pszBuffer
 * @param     UZPOCKETPDW * pstPDW
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-20 11:13:59
 * @warning
 */
void CCommonUtils::MakeOnePDW( char *pszBuffer, UZPOCKETPDW *pstPDW )
{
#ifdef _GRAPH_
    pszBuffer[0] = NULL;

#else

#ifdef FFRQMhzCNV
    unsigned int uiFreq, uiAOA, uiPW;
    int iPA;

    char o_x[2] = { 'O', 'X' };

    uiFreq = UMUL( FFRQMhzCNV( 0, pstPDW->stHwPdwDataRf.uiFreq ), 1 );
    uiAOA = pstPDW->stHwPdwDataRf.uiAOA;
    uiPW = I_PWCNV( pstPDW->stHwPdwDataRf.uiPW );
    iPA = (int) IMUL( PACNV( pstPDW->stHwPdwDataRf.uiPA ), 1 );
    sprintf( pszBuffer, "[%3d] %1d[%1d%1d/%2d %4d[%4d] %4d[MHz] %8d[us] %8d[dBm] 0x%016llx %1c", ( unsigned int ) pstPDW->stHwPdwDataRf.Index, ( unsigned int ) pstPDW->stHwPdwDataRf.CwPulse, \
        ( unsigned int ) pstPDW->stHwPdwDataRf.Pmop, ( unsigned int ) pstPDW->stHwPdwDataRf.Fmop, ( unsigned int ) pstPDW->stHwPdwDataRf.FmopDir, \
        uiAOA, ( unsigned int ) pstPDW->stHwPdwDataRf.uiAOA, uiFreq, uiPW, iPA, pstPDW->stHwPdwDataRf.ullTOA, o_x[pstPDW->stHwPdwDataRf.FalsePdw] );
#else
    pszBuffer[0] = NULL;

#endif

#endif

}

/**
 * @brief     WallMakePrint
 * @param     char * buffer
 * @param     char delimeter
 * @param     int iColumns
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-05-10 15:52:49
 * @warning
 */
void CCommonUtils::WallMakePrint( char *buffer, char delimeter, int iColumns )
{
    int i, iCnt;

    iCnt = ( int ) strlen( buffer );
    for( i = iCnt; i < iColumns ; ++i ) {
        buffer[i] = delimeter;
    }
    buffer[i] = 0;

}

/**
 * @brief     CenterMakePrint
 * @param     char * buffer
 * @param     char delimeter
 * @param     int iColumns
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-17 15:05:32
 * @warning
 */
void CCommonUtils::CenterMakePrint( char *buffer, char delimeter, int iColumns )
{
    int i, iCnt, iCenter;

    iCnt = ( int ) strlen( buffer );
    iCenter = ( iColumns - iCnt ) / 2;

    memcpy( & buffer[iCenter], buffer, (size_t) iCnt * sizeof( char ) );

    for( i = 0 ; i < iCenter ; ++i ) {
        buffer[i] = delimeter;
    }

    i += iCnt;
    for( ; i < iColumns; ++i ) {
        buffer[i] = delimeter;
    }
    buffer[i] = 0;

}

/**
 * @brief     WallMakePrint
 * @param     char delimeter
 * @param     int iColumns
 * @param     char * buffer
 * @param     ...
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-05-14 15:02:41
 * @warning
 */
void CCommonUtils::WallMakePrint( char delimeter, int iColumns, char *fmt, ... )
{
    int i, iCnt;
    char buffer[200] = { 0 };

    va_list args;

    //va_start( args, (const char *) fmt );          /*   */
    va_start( args, fmt );          /*   */
    vsprintf( buffer, fmt, args );
    va_end( args );

    iCnt = ( int ) strlen( buffer );
    for( i = iCnt; i < iColumns; ++i ) {
        buffer[i] = delimeter;
    }
    buffer[i] = 0;

}


