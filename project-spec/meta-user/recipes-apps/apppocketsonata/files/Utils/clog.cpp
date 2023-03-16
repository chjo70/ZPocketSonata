
#include "stdafx.h"

#ifdef _MSC_VER
#include <io.h>
#include <direct.h>

#define _LOG_RELATIVE_PATH_

#else
#include <unistd.h>
#include <sys/time.h>

#ifdef __VXWORKS__
#include <private/kwriteLibP.h>
#endif

#endif

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <sys/stat.h>

#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>


#include "../Include/globals.h"

bool CLog::m_bcs=false;

unsigned int CLog::m_uiCoLog = 0;

/**
 * @brief     로그 책체를 생성합니다.
 * @return    
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-02-27 10:39:06
 * @warning
 */
CLog::CLog()
{
#ifdef _MSC_VER
#else
    if( sem_init( & m_mutex, 1, 1 ) < 0 ) {
        perror( "세마포어 실패" );
    }
#endif

#ifdef __VXWORKS__

#else

#endif

    memset( m_szPresentDirectory, 0, sizeof(m_szPresentDirectory) );
    getcwd( m_szPresentDirectory, sizeof(m_szPresentDirectory) );

    Init();

}

/**
 * @brief     ~CLog
 * @return    
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-02-27 10:37:57
 * @warning
 */
CLog::~CLog()
{
    printf( "CLOG 소멸 !!\n" );
}

/**
 * @brief     객체 초기화를 수행합니다.
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-02-27 10:38:38
 * @warning
 */
void CLog::Init()
{
    m_uiCoLog = 0;
}

/**
 * @brief CLog::LogMsg
 * @param nType
 * @param pszFunction
 * @param pszFile
 * @param iLine
 * @param pStr
 */
void CLog::LogMsg( int nType, const char *pszFunction, const char *pszFile, const int iLine, const char *fmt, ... )
{
#ifndef _CGI_LIST_
#ifdef _MSC_VER
    FILE *fp=NULL;
#else
    int fid;
#endif

    char szLogDir[LOG_DIR_SIZE*2];
    char szLogFullName[LOG_DIR_SIZE*2];
    char szDate[LOG_DIR_SIZE];

#ifdef _LOG_WHERE
    char szFileLine[LOG_DIR_SIZE];
#endif

    va_list args;

    size_t nLength, nLengthTime;

	Lock();

#ifdef _LOG_RELATIVE_PATH_
    strcpy( szLogDir, m_szPresentDirectory );
    strcat( szLogDir, LOG_DIRECTORY );
#else
    strcpy( szLogDir, LOG_DIRECTORY );

#endif

#ifdef __linux__
    if( 0 == mkdir( szLogDir, 0766 ) || errno == EEXIST ) {
#else
    if( 0 == mkdir( szLogDir ) || errno == EEXIST ) {
#endif

#ifdef _MSC_VER
        SYSTEMTIME tmSystem;

        ::GetLocalTime( & tmSystem );
        sprintf( szDate, "/%d_%d_%d.log", tmSystem.wYear, tmSystem.wMonth, tmSystem.wDay );
#else
        struct timeval tv;
        time_t timer;
        struct tm* t;

        gettimeofday( &tv,NULL);
        timer = time( (time_t *) & tv.tv_sec );
        t = localtime(&timer);

        sprintf( szDate, "/%d_%d_%d.log", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday );
#endif

        strcpy( szLogFullName, szLogDir );
        strcat( szLogFullName, szDate );
        //strcat( szLogDir, szDate );

#ifdef _MSC_VER
        fopen_s( & fp, szLogFullName, "a+" );
        //fid = open(szLogFullName, O_APPEND | O_WRONLY | O_BINARY );
#else
        fid = open(szLogFullName, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH );
#endif

        m_szLog[0] = NULL;
#ifdef _MSC_VER
        if( fp != NULL ) {
            if( enNoLineFeed != nType ) {
#ifdef _LOG_DATA_ENABLED_
                sprintf( m_szLog, "\n%d-%02d-%02d %02d:%02d:%02d.%03d", tmSystem.wYear, tmSystem.wMonth, tmSystem.wDay, tmSystem.wHour, tmSystem.wMinute, tmSystem.wSecond, tmSystem.wMilliseconds );
#else
                sprintf( m_szLog, "\n" );
#endif
            }

#else
        if( fid != 0 ) {
            if( enNoLineFeed != nType ) {
#ifdef _LOG_DATA_ENABLED_
                sprintf( m_szLog, "\n%d-%02d-%02d %02d:%02d:%02d.%03d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, (int)( tv.tv_usec / 1000. ) );
#else
                sprintf( m_szLog, "\n" );
#endif
            }
#endif

            nLengthTime = strlen(m_szLog);

            switch( nType ) {
            case enNormal :
                strcat( m_szLog, "[NORMAL]\t" );
                break;
            case enDebug :
                strcat( m_szLog, "[DEBUG ]\t" );
                break;
            case enEnd :
                strcat( m_szLog, "[END   ]\t" );
                break;

            case enLineFeed :
                break;

            case enError :
                strcat( m_szLog, "[ERROR ]\t" );
                break;

            default :
                break;
            }

            if(fmt != NULL ) {
                nLength = strlen(m_szLog);
                va_start( args, fmt);
                vsprintf( & m_szLog[nLength], fmt, args );
                va_end( args );

#ifdef __VXWORKS__
                // fflush( stdout );

#endif
                //strcat( & m_szLog[nLength], fmt );

#ifdef _LOG_WHERE
                sprintf( szFileLine, "\t\tat [%s:%d{%s}]" , pszFile, iLine, pszFunction );
#endif
            }
            else {
#ifdef _LOG_WHERE
                sprintf( szFileLine, "[%s:%d{%s}]" , pszFile, iLine, pszFunction );
#endif
            }

#ifdef _LOG_WHERE
            if( szFileLine[0] != 0 ) {
                strcat( m_szLog, szFileLine );
            }
#endif

            //sprintf( szExtra, "[%2d]" , int iThreadID );
            //strcat( m_szLog, szExtra );

            nLength = strlen(m_szLog);
            if( nLength > 10 || nType == enLineFeed ) {
                ++m_uiCoLog;
#ifdef _MSC_VER
                fprintf( fp, "%s" , m_szLog );
                fflush( fp );

#else
                write( fid, m_szLog, nLength );
                
                
#endif

                if( nType == enDebug || nType == enLineFeed ) {
#if defined(__VXWORKS__)
                    _func_kprintf( m_szLog );
#else
                    TRACE0( m_szLog );
#endif
            }
                else if( nType == enNormal ) {
#if defined(__VXWORKS__)
                    _func_kprintf( m_szLog );
#else
                    TRACE0( m_szLog );
#endif
                }
                else if( nType == enError ) {
#if defined(__VXWORKS__)
                    _func_kprintf( m_szLog );
#else
                    TRACE0( m_szLog );
#endif
                }
                else {

                }

            }
#ifdef _MSC_VER
            fclose( fp );
#else
            close( fid );
#endif

            // 로그 파일 삭제
            // vxworks 인 경우에 저장 공간이 없으면 로그 파일을 삭제한다.
#if defined(__VXWORKS__) || defined(__linux__)
            if( m_uiCoLog > MAX_LINES_LOGS ) {
                remove( szLogFullName );
                printf( "포그 파일을 삭제합니다!!!" );

                m_uiCoLog = 0;
            }
#endif

        }
    }
 
	UnLock();

#endif

}

/**
 * @brief     Lock
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-08-23, 10:23
 * @warning
 */
void CLog::Lock() 
{

#ifdef _MSC_VER
    //TRACE( "\nLock()" );
    m_cs.Lock();
#elif defined(__VXWORKS__)
    sem_wait( & m_mutex );
#else
    // std::unique_lock<std::mutex> lk(m_mutex);
#endif
    m_bcs = true;


}

/**
 * @brief     UnLock
 * @return    void
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-08-23, 10:23
 * @warning
 */
void CLog::UnLock() 
{
    //TRACE( "\nUnLock()" );

#ifdef _MSC_VER
    m_cs.Unlock();
#elif defined(__VXWORKS__)
    sem_post( & m_mutex );    
#else

#endif
    m_bcs = false;

}

/**
 * @brief CLog::LogMsg
 * @param nType
 * @param fmt
 */
void CLog::LogMsg( int nType, const char *fmt, ... )
{
    va_list args;
    char szLogString[LOG_DIR_SIZE*5];

    va_start( args, fmt );
#ifdef _MSC_VER
    vsprintf_s( szLogString, sizeof(szLogString), fmt, args );
#else
    vsprintf( szLogString, fmt, args );
#endif
    va_end( args );

    //char *pTemp = UTF8ToANSI( szLogString );
    LOGMSG( nType, (const char *) szLogString );
    //delete pTemp;

}

/**
 * @brief     ANSIToUTF8
 * @param     const char * pszCode
 * @return    char *
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-10-27, 13:16
 * @warning
 */
// char *CLog::ANSIToUTF8( const char * pszCode )
// {
// #ifdef _MFC_VER
//     int iLength, nLength2;
//     BSTR	bstrCode; 
//     char*	pszUTFCode = NULL;
// 
//     iLength = MultiByteToWideChar(CP_ACP, 0, pszCode, lstrlen(pszCode), NULL, NULL); 
//     bstrCode = SysAllocStringLen(NULL, (unsigned int) iLength ); 
//     MultiByteToWideChar(CP_ACP, 0, pszCode, lstrlen(pszCode), bstrCode, iLength);
// 
//     nLength2 = WideCharToMultiByte(CP_UTF8, 0, bstrCode, -1, pszUTFCode, 0, NULL, NULL); 
//     pszUTFCode = (char*) malloc( nLength2+1); 
//     WideCharToMultiByte(CP_UTF8, 0, bstrCode, -1, pszUTFCode, nLength2, NULL, NULL); 
// 
//     return pszUTFCode;
// #else
//     return NULL;
// 
// #endif
// 
// }

/**
 * @brief     UTF8ToANSI
 * @param     const char * pszCode
 * @return    char*
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2021-10-27, 13:16
 * @warning
 */
// int CLog::UTF8ToANSI( char *pszDest, int iDestSize, const char *pszSrc )
// {
// #ifdef _MSC_VER
//     WCHAR szUnicode[255];
//     char szAnsi[255];
// 
//     BSTR    bstrWide;
//     char*   pszAnsi;
//     int     nSize;
// 
//     nSize = MultiByteToWideChar( CP_UTF8, 0, pszSrc, -1, NULL, NULL);
//     //bstrWide = SysAllocStringLen(NULL, nLength);
// 
//     int iUnicodeSize = MultiByteToWideChar(CP_UTF8, 0, pszSrc, -1, szUnicode, nSize );
// 
//     int nAnsiSize = WideCharToMultiByte(CP_ACP, 0, szUnicode, iUnicodeSize, szAnsi, sizeof(szAnsi), NULL, NULL);
// 
//     //WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, pszAnsi, nLength, NULL, NULL);
//     //SysFreeString(bstrWide);
// 
//     memcpy(pszDest, szAnsi, nAnsiSize);
// 
//     pszDest[nAnsiSize] = 0;
// 
//     return nAnsiSize;
// #else
//     return 0;
// #endif
// 
// }
