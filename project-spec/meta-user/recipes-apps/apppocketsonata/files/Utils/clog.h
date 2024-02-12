/**

    @file      clog.h
    @brief
    @details   ~
    @author    조철희
    @date      30.04.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#pragma once


#include <stdio.h>

#ifdef _MSC_VER
#include <afxmt.h>

#else
#include <semaphore.h>

#endif



#include "clogname.h"

#ifdef _LOG_
#include "../Utils/cthread.h"
#endif


#include "../Include/system.h"


#define LOG_EXTRA_SIZE      (50)

#define MAX_LINES_LOGS      (5000)

#define MAX_SCREEN_COLUMNS  (90)

#define MAX_MESSAGE_COLUMNS (80)


#define LOG_DIR_SIZE        (1024*5)


// 로그 출력에 함수 라인 을 포함할때 아래를 정의 합니다.
//#define _LOG_WHERE

// 로그 헤더에 날짜를 추가 하도록 정의 합니다.
//#define _LOG_DATA_ENABLED_



#ifdef _LOG_ANALTYPE_
bool IsLogAnalType( LogType enLogType );

#endif


/**

    @class   CLog
    @brief
    @details ~

**/
#ifdef _LOG_
class CLog : public CThread
#else
class CLog
#endif
{
private:
    static bool m_bcs;

    bool m_bLogThread;

    static unsigned int m_uiCoLog;

#ifdef _LOG_
    STR_MessageData *m_pMsg;
#endif

#ifdef _MSC_VER

#ifndef _CONSOLE
    CCriticalSection m_cs;
#endif

#else
    sem_t m_mutex;
#endif
    char m_szLogFullName[LOG_DIR_SIZE * 2];

    char m_szPresentDirectory[LOG_DIR_SIZE];

    char m_szLogString[LOG_DIR_SIZE*5];
    char m_szLogDir[LOG_DIR_SIZE * 2];

#ifndef _CGI_LIST_
#ifdef _MSC_VER
    FILE *m_fp = NULL;
#else
    int m_fid;
#endif
#endif

private:

private:
    void Init();

    void  WriteAndPrint();

public:
    CLog();
    CLog( int iThreadPriority, const char *pClassName, bool bArrayLanData );
    virtual ~CLog();

    void Lock();
    void UnLock();

    inline bool IsLock() { return m_bcs==true; }

    void LogMsg( int nType, const char *pszFunction, const char *pszFile, const int iLine, const char *pThreadName, const char *fmt, ... );
    //void LogMsg( int nType, const char *fmt, ... );

    void Start();

public:
#ifdef _LOG_
    void Run( key_t key = IPC_PRIVATE );
    void _routine();


    const char *GetThreadName() { return m_szThreadName; }
    STR_MessageData *GetParentMessage() { return m_pMsg; }                          ///< 메시지 데이터를 리턴 합니다.
#endif

    const char *GetLogDirectory()
    {
        return m_szLogDir;
    }

    const char *GetLogFullName()
    {
        return m_szLogFullName;
    }


};
