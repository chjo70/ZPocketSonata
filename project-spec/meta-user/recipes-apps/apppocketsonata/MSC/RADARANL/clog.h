#ifndef CLOG_H
#define CLOG_H

#include <stdio.h>

#ifdef _MSC_VER
#include <afxmt.h>

#define getcwd  _getcwd
#define mkdir   _mkdir
#define open    _open
#define write   _write
#define close   _close

#else
#include <semaphore.h>

#endif

#include "../Include/system.h"


#define LOG_EXTRA_SIZE      (50)


#define LOG_DIR_SIZE        (1024)

// 로그 타입 사용자가 원하는 대로 정의
enum LogType {
    enDebug=0,
    enNormal,
    enLineFeed,
    enNoLineFeed,

    enWarning,
    enError,
    enEnd,
};

#define LOG_LINEFEED                    g_pTheLog->LogMsg( enLineFeed, __FUNCTION__, __FILE__, __LINE__, "" )

#define LOGMSG( A, B )                  g_pTheLog->LogMsg( A, __FUNCTION__, __FILE__, __LINE__, B )
#define LOGMSG1( A, B, C )              g_pTheLog->LogMsg( A, __FUNCTION__, __FILE__, __LINE__, B, C )
#define LOGMSG2( A, B, C, D )           g_pTheLog->LogMsg( A, __FUNCTION__, __FILE__, __LINE__, B, C, D )
#define LOGMSG3( A, B, C, D, E )        g_pTheLog->LogMsg( A, __FUNCTION__, __FILE__, __LINE__, B, C, D, E )
#define LOGMSG4( A, B, C, D, E, F )     g_pTheLog->LogMsg( A, __FUNCTION__, __FILE__, __LINE__, B, C, D, E, F )
#define LOGMSG5( A, B, C, D, E, F, G )  g_pTheLog->LogMsg( A, __FUNCTION__, __FILE__, __LINE__, B, C, D, E, F, G )


#define Log                             g_pTheLog->LogMsg


#define LOGENTRY                        g_pTheLog->LogMsg( enNormal, __FUNCTION__, __FILE__, __LINE__, NULL )

class CLog
{
private:
    static bool m_bcs;

#ifdef _MSC_VER
    CCriticalSection m_cs;
#else
    sem_t m_mutex;
#endif

    char m_szPresentDirectory[LOG_DIR_SIZE];
    char m_szLog[LOG_DIR_SIZE*5];
    char m_szLogString[LOG_DIR_SIZE*5];

private:
    char *ANSIToUTF8( const char * pszCode );
    char *UTF8ToANSI( const char *pszCode );

public:
    CLog();
    virtual ~CLog();

    void Lock();
    void UnLock();

    inline bool IsLock() { return m_bcs==true; }

    void LogMsg( int nType, const char *pszFunction, const char *pszFile, const int iLine, const char *pMsg, ... );

    void LogMsg( int nType, const char *fmt, ... );

};



#endif // CLOG_H
