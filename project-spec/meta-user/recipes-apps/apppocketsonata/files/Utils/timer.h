/**

    @file      timer.h
    @brief
    @details   ~
    @author    Cool Guy
    @date      13.08.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#pragma once


#ifdef _MSC_VER

#include <iostream>
#include <queue>

#include "cthread.h"

#if _MSC_VER <= 1600 || _AFXDLL

#else
#include <mutex>
#include <atomic>
#include <condition_variable>

#endif

using namespace std;



#else
#include <pthread.h>
#include <unistd.h>

#endif

#ifdef __linux__
#include <sys/msg.h>
#include <sys/ipc.h>
#include <regex.h>
#include <semaphore.h>
#elif defined(__VXWORKS__)
#include <timers.h>
#include <unistd.h>
#include <tickLib.h>
#include <semaphore.h>

#endif

#define LENGTH_OF_THREADNAME                 (30)

class CTimer
{

private:
#ifdef _MSC_VER
    CThreadContext m_MainThread;

    LPTHREAD_START_ROUTINE	m_pThreadFunc;	//	The Worker Thread Function Pointer

    HANDLE m_hEvent;
    HANDLE m_hSleepEvent;


#if _MSC_VER <= 1600 || _AFXDLL
    CCriticalSection m_cs;
#else
    std::mutex m_mutex;
#endif

#elif defined(__VXWORKS__)
    timer_t m_tiTmr;

    // 타스크 관련 멤버 변수
    TASK_ID m_TaskID;
    //int m_iPriority;
    bool m_bTaskRunStat;

#elif defined(__linux__)

#else
#endif

    static int m_iCoTimer;

    char m_szTimerName[LENGTH_OF_THREADNAME];

public:
    CTimer();
    CTimer( const char *pTimerName );
    virtual ~CTimer();

    void Init();
    void SetTime( unsigned int uiSec );

#ifdef __VXWORKS__
    void TimerRoutine();

#endif

private:


public:

};


