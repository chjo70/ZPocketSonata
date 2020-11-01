#include "clog.h"

#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>

CLog* CLog::pInstance = nullptr;

/**
 * @brief CLog::CLog
 */
CLog::CLog()
{
    if( sem_init( & m_mutex, 1, 1 ) < 0 ) {
        perror( "세마포어 실패" );
    }

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
#ifndef _CGI_
    int fid;

    char szDate[LOG_DIR_SIZE];

#ifdef _LOG_WHERE
    char szFileLine[LOG_DIR_SIZE];
#endif

    va_list args;

    int nLength, nLengthTime;

    sem_wait( & m_mutex );

#ifdef _LOG_RELATIVE_PATH_
    getcwd( m_szPresentDirectory, sizeof(m_szPresentDirectory) );

    strcpy( m_szLogDir, m_szPresentDirectory );
    strcat( m_szLogDir, LOG_DIRECTORY );
#else
    strcpy( m_szLogDir, LOG_DIRECTORY );

#endif

    if( 0 == mkdir( m_szLogDir, 0776 ) || errno == EEXIST ) {
        time_t timer;
        struct tm* t;
        struct timeval tv;

        gettimeofday( &tv,NULL);
        timer = time( & tv.tv_sec );
        t = localtime(&timer);

        sprintf( szDate, "/%d_%d_%d.log", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday );
        strcat( m_szLogDir, szDate );

        fid = open(m_szLogDir, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH );
        if( fid != 0 ) {
            sprintf( m_szLog, "\n%d-%02d-%02d %02d:%02d:%02d.%03d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, (int)( tv.tv_usec / 1000. ) );

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
                m_szLog[0] = 0;
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

                if( nType == enDebug ) {
                    puts( & m_szLog[nLength] );
                }
                else if( nType == enError ) {
                    puts( & m_szLog[nLengthTime] );
                }
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

            nLength = strlen(m_szLog);
            if( nLength > 36 ) {
                write( fid, m_szLog, nLength );
            }

            close( fid );
        }
    }

    sem_post( & m_mutex );
#endif

}

/**
 * @brief CLog::LogMsg
 * @param nType
 * @param fmt
 */
void CLog::LogMsg( int nType, const char *fmt, ... )
{
    va_list args;

    va_start( args, fmt );
    vsprintf( m_szLogString, fmt, args );
    va_end( args );

    LOGMSG( nType, m_szLogString );

}
