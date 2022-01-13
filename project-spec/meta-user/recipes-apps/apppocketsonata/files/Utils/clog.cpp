
#include "stdafx.h"

#ifdef _MSC_VER
#include <io.h>
#include <direct.h>

#define _LOG_RELATIVE_PATH_

#else
#include <unistd.h>
#include <sys/time.h>
#endif

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>


#include "../Include/globals.h"

bool CLog::m_bcs=false;

#ifdef _MSC_VER
CCriticalSection CLog::m_cs;
#else
sem_t CLog::m_mutex;
#endif

/**
 * @brief CLog::CLog
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

}

CLog::~CLog()
{
    printf( "CLOG 소멸 !!\n" );
}

/**
 * @brief CLog::LogMsg
 * @param nType
 * @param pszFunction
 * @param pszFile
 * @param iLine
 * @param pStr
 */
void CLog::LogMsg( int nType, const char *pszFunction, const char *pszFile, const int iLine, const char *pMsg, ... )
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

    int nLength, nLengthTime;

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

        // vxworks 인 경우에 저장 공간이 없으면 로그 파일을 삭제한다.
#ifdef __VXWORKS__

#endif

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

            if( pMsg != NULL ) {
                nLength = strlen(m_szLog);
                va_start( args, pMsg );
                vsprintf( & m_szLog[nLength], pMsg, args );
                va_end( args );

                if( nType == enDebug || nType == enLineFeed ) {
                    puts( & m_szLog[nLength] );
                }
                else if( nType == enNormal ) {
                    puts( & m_szLog[nLength] );
                }
                else if( nType == enError ) {
                    puts( & m_szLog[nLengthTime] );
                }
#ifdef __VXWORKS__
                fflush( stdout );

#endif
                //strcat( & m_szLog[nLength], pMsg );

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
            if( nLength > 20 || nType == enLineFeed ) {
#ifdef _MSC_VER
                fprintf( fp, "%s" , m_szLog );
                fflush( fp );

                TRACE0( m_szLog );
#else
                write( fid, m_szLog, nLength );
#endif
            }
#ifdef _MSC_VER
            fclose( fp );
#else
            close( fid );
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
#elif __VXWORKS__
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
#elif __VXWORKS__
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
    LOGMSG( nType, szLogString );
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
char *CLog::ANSIToUTF8( const char * pszCode )
{
#ifdef _MFC_VER
    int		nLength, nLength2;
    BSTR	bstrCode; 
    char*	pszUTFCode = NULL;

    nLength = MultiByteToWideChar(CP_ACP, 0, pszCode, lstrlen(pszCode), NULL, NULL); 
    bstrCode = SysAllocStringLen(NULL, nLength); 
    MultiByteToWideChar(CP_ACP, 0, pszCode, lstrlen(pszCode), bstrCode, nLength);

    nLength2 = WideCharToMultiByte(CP_UTF8, 0, bstrCode, -1, pszUTFCode, 0, NULL, NULL); 
    pszUTFCode = (char*)malloc(nLength2+1); 
    WideCharToMultiByte(CP_UTF8, 0, bstrCode, -1, pszUTFCode, nLength2, NULL, NULL); 

    return pszUTFCode;
#else
    return NULL;

#endif

}

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
char* CLog::UTF8ToANSI( const char *pszCode )
{
#ifdef _MFC_VER
    BSTR    bstrWide;
    char*   pszAnsi;
    int     nLength;

    nLength = MultiByteToWideChar(CP_UTF8, 0, pszCode, lstrlen(pszCode) + 1, NULL, NULL);
    bstrWide = SysAllocStringLen(NULL, nLength);

    MultiByteToWideChar(CP_UTF8, 0, pszCode, lstrlen(pszCode) + 1, bstrWide, nLength);

    nLength = WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, NULL, 0, NULL, NULL);
    pszAnsi = new char[nLength];

    WideCharToMultiByte(CP_ACP, 0, bstrWide, -1, pszAnsi, nLength, NULL, NULL);
    SysFreeString(bstrWide);

    return pszAnsi;
#else
    return NULL;
#endif

}
