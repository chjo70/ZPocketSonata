#ifndef CLOG_H
#define CLOG_H

#include <stdio.h>
#include <semaphore.h>

#include "../Include/system.h"



#define LOG_DIR_SIZE        (1024)

// 로그 타입 사용자가 원하는 대로 정의
enum LogType {
    enDebug=0,
    enNormal,
    enLineFeed,
    enError,
    enEnd,
};

//#define LOG_LINEFEED

#define LOGMSG( A, B )              LOG->LogMsg( A, __FUNCTION__, __FILE__, __LINE__, B )
#define LOGMSG1( A, B, C )          LOG->LogMsg( A, __FUNCTION__, __FILE__, __LINE__, B, C )
#define LOGMSG2( A, B, C, D )       LOG->LogMsg( A, __FUNCTION__, __FILE__, __LINE__, B, C, D )
#define LOGMSG3( A, B, C, D, E )    LOG->LogMsg( A, __FUNCTION__, __FILE__, __LINE__, B, C, D, E )
#define LOGMSG4( A, B, C, D, E, F ) LOG->LogMsg( A, __FUNCTION__, __FILE__, __LINE__, B, C, D, E, F )


#define LOGENTRY                    LOG->LogMsg( enNormal, __FUNCTION__, __FILE__, __LINE__, NULL )

class CLog
{
private:
    static CLog *pInstance;

    sem_t mutex;

    char m_szPresentDirectory[LOG_DIR_SIZE];
    char m_szLogDir[LOG_DIR_SIZE*2];

    char m_szLog[LOG_DIR_SIZE*5];
    char m_szLogString[LOG_DIR_SIZE*5];

public:
    CLog();

    static CLog* GetInstance()
    { // 게으른 초기화
        if(pInstance == NULL) {
            pInstance = new CLog();
        }
        return pInstance;
    }

    void LogMsg( int nType, char *pMsg );
    void LogMsg( int nType, const char *pszFunction, const char *pszFile, const int iLine, const char *pMsg, ... );

    void LogMsg( int nType, const char *fmt, ... );

};


#define LOG     CLog::GetInstance()

#endif // CLOG_H
