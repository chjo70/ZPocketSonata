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

#define LOG_LINEFEED                    LOG->LogMsg( enLineFeed, __FUNCTION__, __FILE__, __LINE__, "" )

#define LOGMSG( A, B )                  LOG->LogMsg( A, __FUNCTION__, __FILE__, __LINE__, B )
#define LOGMSG1( A, B, C )              LOG->LogMsg( A, __FUNCTION__, __FILE__, __LINE__, B, C )
#define LOGMSG2( A, B, C, D )           LOG->LogMsg( A, __FUNCTION__, __FILE__, __LINE__, B, C, D )
#define LOGMSG3( A, B, C, D, E )        LOG->LogMsg( A, __FUNCTION__, __FILE__, __LINE__, B, C, D, E )
#define LOGMSG4( A, B, C, D, E, F )     LOG->LogMsg( A, __FUNCTION__, __FILE__, __LINE__, B, C, D, E, F )
#define LOGMSG5( A, B, C, D, E, F, G )  LOG->LogMsg( A, __FUNCTION__, __FILE__, __LINE__, B, C, D, E, F, G )


#define Log                             LOG->LogMsg


#define LOGENTRY                        LOG->LogMsg( enNormal, __FUNCTION__, __FILE__, __LINE__, NULL )

class CLog
{
private:
    static CLog *m_pInstance;

#ifdef _MSC_VER
    static CCriticalSection m_cs;
#else
    static sem_t m_mutex;
#endif

    char m_szPresentDirectory[LOG_DIR_SIZE];
    char m_szLogDir[LOG_DIR_SIZE*2];

    char m_szLog[LOG_DIR_SIZE*5];
    char m_szLogString[LOG_DIR_SIZE*5];

public:
    CLog();
    virtual ~CLog();

    static CLog* GetInstance()
    { // 게으른 초기화
        if(m_pInstance == NULL) {
            m_pInstance = new CLog();
        }
        return m_pInstance;
    }

    static void ReleaseInstance() { 
        if( m_pInstance != NULL ) {
            delete m_pInstance;
            m_pInstance = NULL;
        } 
    }

    void Lock();
    void UnLock();

    //void LogMsg( int nType, char *pMsg );
    void LogMsg( int nType, char *pszFunction, const char *pszFile, const int iLine, const char *pMsg, ... );

    void LogMsg( int nType, char *fmt, ... );

};


#define LOG     CLog::GetInstance()

#endif // CLOG_H
