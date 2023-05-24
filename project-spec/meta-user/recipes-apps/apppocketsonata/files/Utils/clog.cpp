/**

    @file      clog.cpp
    @brief
    @details   ~
    @author    조철희
    @date      10.04.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

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

    m_bLogThread = false;

    Init();

}

/**
 * @brief     CLog
 * @param     int iThreadPriority
 * @param     const char * pClassName
 * @param     bool bArrayLanData
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-30 15:32:48
 * @warning
 */
#ifdef _LOG_
CLog::CLog( int iThreadPriority, const char *pClassName, bool bArrayLanData ) : CThread( iThreadPriority, pClassName, bArrayLanData )
#else
CLog::CLog( int iThreadPriority, const char *pClassName, bool bArrayLanData )
#endif
{
    char szDate[LOG_DIR_SIZE];

    m_bLogThread = false;

    Init();

    // 로그 파일 생성 합니다.
#ifdef _MSC_VER
    SYSTEMTIME tmSystem;

    ::GetLocalTime( & tmSystem );
    sprintf( szDate, "/%d_%d_%d.log", tmSystem.wYear, tmSystem.wMonth, tmSystem.wDay );
#else
    struct timeval tv;
    time_t timer;
    struct tm *t;

    gettimeofday( &tv, NULL );
    timer = time( ( time_t * ) & tv.tv_sec );
    t = localtime( &timer );

    sprintf( szDate, "/%d_%d_%d.log", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday );
#endif

    strcpy( m_szLogFullName, m_szLogDir );
    strcat( m_szLogFullName, szDate );


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

#ifdef _LOG_
    m_pMsg = NULL;
#endif

    memset( m_szPresentDirectory, 0, sizeof( m_szPresentDirectory ) );
    getcwd( m_szPresentDirectory, sizeof( m_szPresentDirectory ) );

#ifdef _LOG_RELATIVE_PATH_
    strcpy( m_szLogDir, m_szPresentDirectory );
    strcat( m_szLogDir, LOG_DIRECTORY );
#else
    strcpy( m_szLogDir, LOG_DIRECTORY );

#endif

#ifdef __linux__
    if( 0 == mkdir( m_szLogDir, 0766 ) || errno == EEXIST ) {
#else
    if( 0 == mkdir( m_szLogDir ) || errno == EEXIST ) {
#endif

    }

#ifdef _LOG_
    m_pMsg = GetRecvDataMessage();
#endif

}

#ifdef _LOG_
/**
 * @brief     Run
 * @param     key_t key
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-30 15:34:21
 * @warning
 */
void CLog::Run( key_t key )
{

    CThread::Run();

}

/**
 * @brief     _routine
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-04-30 16:03:14
 * @warning
 */
void CLog::_routine()
{
    m_pMsg = GetRecvDataMessage();

    while( m_bThreadLoop ) {
        if( QMsgRcv() == -1 ) {
            perror( "QMsgRcv(CLog)" );
        }
        else {
            switch( m_pMsg->uiOpCode ) {
                case enTHREAD_LOG:
                    WriteAndPrint();
                    break;

                default:
                    Log( enError, "[%s]에서 잘못된 명령(0x%x)을 수신하였습니다 !!", GetThreadName(), m_pMsg->uiOpCode );
                    break;
            }

        }
    }
}
#else
#endif

/**
 * @brief     WriteAndPrint
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-05-14 11:09:21
 * @warning
 */
void  CLog::WriteAndPrint()
{
#ifdef _LOG_
    char *pszLog;

    pszLog = ( char * ) GetRecvData();
    pszLog[m_pMsg->uiArrayLength] = 0;

    // 1. 화면에 출력 합니다.
#ifdef _MSC_VER
    OutputDebugString( pszLog );
#else
    //puts( & pszLog[1] );
    printf( pszLog );
    // puts 로 대체...
#endif

    // 2. 로그 파일을 생성합니다.
#ifdef _MSC_VER
//     fopen_s( & m_fp, m_szLogFullName, "a+" );
//
//     if( m_fp == NULL ) {
//         char buffer[200];
//
//         sprintf( buffer, "\n 로그 파일[%s] 생성 에러 입니다. 담당자에게 문의하세요 !", m_szLogFullName );
//         OutputDebugString( buffer );
//     }
//     else {
//         fprintf( m_fp, "%s", pszLog );
//         // fflush( m_fp );
//         fclose( m_fp );
//     }

#else
    m_fid = open( m_szLogFullName, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH );

    if( m_fid == 0 ) {
        printf( "\n 로그 파일[%s] 생성 에러 입니다. 담당자에게 문의하세요 !", m_szLogFullName );
    }
    else {
        write( m_fid, pszLog, m_pMsg->uiArrayLength );
        close( m_fid );
    }
#endif

    ++m_uiCoLog;

    // 3. 로그 파일 삭제
    // vxworks 인 경우에 저장 공간이 없으면 로그 파일을 삭제한다.
#if defined(__VXWORKS__) || defined(__linux__)
    if( m_uiCoLog > MAX_LINES_LOGS ) {
        remove( m_szLogFullName );
        printf( "\n[W] 로그 파일의 라인 수[%d]가 초과되어 로그 파일을 삭제합니다 !\n" , MAX_LINES_LOGS );

        m_uiCoLog = 0;
    }
#endif

#endif

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
    char szLog[LOG_DIR_SIZE * 5];

#ifdef _LOG_WHERE
    char szFileLine[LOG_DIR_SIZE];
#endif

    va_list args;

    size_t nLength; // nLengthTime;

	Lock();

    szLog[0] = 0;
#ifdef _MSC_VER
    if( enNoLineFeed != nType ) {
#ifdef _LOG_DATA_ENABLED_
        sprintf( szLog, "\n%d-%02d-%02d %02d:%02d:%02d.%03d", tmSystem.wYear, tmSystem.wMonth, tmSystem.wDay, tmSystem.wHour, tmSystem.wMinute, tmSystem.wSecond, tmSystem.wMilliseconds );
#else
        sprintf( szLog, "\n" );
#endif
    }

#else
    if( enNoLineFeed != nType ) {
#ifdef _LOG_DATA_ENABLED_
        sprintf( szLog, "\n%d-%02d-%02d %02d:%02d:%02d.%03d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, (int)( tv.tv_usec / 1000. ) );
#else
        sprintf( szLog, "\n" );
#endif
    }
#endif

    //nLengthTime = strlen(m_szLog);

    switch( nType ) {
    case enNormal :
        strcat( szLog, "[NORMAL]\t" );
        break;
    case enDebug :
        strcat( szLog, "[DEBUG ]\t" );
        break;
    case enEnd :
        strcat( szLog, "[END   ]\t" );
        break;

    case enLineFeed :
        break;

    case enError :
        strcat( szLog, "[ERROR ]\t" );
        break;

    default :
        break;
    }

    if(fmt != NULL ) {
        nLength = strlen(szLog);
        va_start( args, fmt);
        vsprintf( & szLog[nLength], fmt, args );
        va_end( args );

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

    nLength = strlen(szLog);
    if( nLength > 4 ) {
#if defined(__VXWORKS__)
        if( m_bLogThread == true ) {
            //_func_kprintf( szLog );
            QMsgSnd( enTHREAD_LOG, szLog, strlen(szLog), _spOne, & m_pMsg->x, sizeof( UNI_MSG_DATA ), NULL );
        }
        else {
            printf( szLog );
        }

#else
        if( m_bLogThread == true ) {
#ifdef _LOG_
            QMsgSnd( enTHREAD_LOG, szLog, strlen(szLog), _spOne, & m_pMsg->x, sizeof( UNI_MSG_DATA ), NULL );
#endif
        }
        else {
            TRACE0( szLog );
        }
#endif

    }
    else if( nType == enLineFeed ) {
#ifdef _MFC_VER
        TRACE0( "\n" );
#endif
    }
    else {
        // printf( "AAA" );
    }

    UnLock();


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

    if( m_bLogThread == false ) {
#ifdef _MSC_VER
        //TRACE( "\nLock()" );
        m_cs.Lock();
#elif defined(__VXWORKS__)
        sem_wait( & m_mutex );
#else
    // std::unique_lock<std::mutex> lk(m_mutex);
#endif

    }
    else {
        WhereIs;
    }

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

    if( m_bLogThread == false ) {
#ifdef _MSC_VER
        m_cs.Unlock();
#elif defined(__VXWORKS__)
        sem_post( & m_mutex );
#else

#endif
    }
    else {
        WhereIs;
    }

    m_bcs = false;

}
