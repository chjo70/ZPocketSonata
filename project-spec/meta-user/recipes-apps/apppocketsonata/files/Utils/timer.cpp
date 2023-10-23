/****************************************************************************************
 파 일 명 : timer.cpp
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 목    적 : 다중 클라리언트 랜 소켓 클래스
 가    정 :
 저 자 명 : 조철희
 변 경 자 :
 변경내용 : (목적)
 변경일시 :
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
 컴파일 일시 :
*****************************************************************************************/


#include "pch.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "timer.h"

#include "../Include/globals.h"

// 타스크 및 쓰레드 포인터
vector<CTimer *> g_vecTimer;

int CTimer::m_iCoTimer = 0;

#ifdef __VXWORKS__

void STimerRoutine( timer_t ttimer, _Vx_usr_arg_t iArg );

void STimerRoutine( timer_t ttimer, _Vx_usr_arg_t iArg )
{
    //CTimer *pTimer = ( CTimer * ) pArg;

    //pTimer->TimerRoutine( & ttimer );

}

#endif

/**
 * @brief     CTimer
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-13 18:23:19
 * @warning
 */
CTimer::CTimer()
{

}

/**
 * @brief     CTimer
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-13 18:13:47
 * @warning
 */
CTimer::CTimer( const char *pTimerName )
{

#ifdef _MSC_VER
    m_pThreadFunc = CThread::EntryPoint;

    // 메시지 큐
    m_hEvent = CreateEvent( NULL, FALSE, FALSE, pTimerName );
    if( m_hEvent == NULL ) {
        //Log( enError, "Warning: CreateEvent failed in CThread::CThread..." , m_szThreadName );
    }
    else {
        ++ m_iCoTimer;
    }

    // Sleep 큐
    m_hSleepEvent = CreateEvent( NULL, FALSE, FALSE, pTimerName );
    if( m_hSleepEvent == NULL ) {
        //Log( enError, "Warning: CreateEvent failed in CThread::CThread::Sleep..." , m_szThreadName );
    }

    //Log( enDebug, "Create the task[%s] & queue ID[%d] ..." , m_szThreadName, m_hEvent );

#elif defined(__VXWORKS__)
    //m_iPriority = iThreadPriority;
    //m_MsgKeyID = 0;
    m_bTaskRunStat = false;

    timer_create( CLOCK_REALTIME, NULL, & m_tiTmr );
    timer_connect( m_tiTmr, ( TIMER_CONNECT_FUNC ) STimerRoutine, (_Vx_usr_arg_t) 0 );

    //printf( "\nCreate the task[%s] & queue ID[%d] ..." , m_szThreadName, m_MsgKeyID );

#elif defined(__linux__)
    m_MsgKeyID = 0;

    Log( enDebug, "Create the task[%s] & queue ID[%d] ...", m_szThreadName, m_MsgKeyID );

#else
#error 이 소스는 현재 플레폼에 지원하지 않습니다. 개발자에게 문의하세요..
#endif

    Init();

    // 스레드 벡터에 삽입하기
    g_vecTimer.push_back( this );

}

/**
 * @brief     ~CTimer
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-13 18:13:06
 * @warning
 */
CTimer::~CTimer()
{

    // g_vecTimer.push_back( this );

#ifdef _MSC_VER


#elif __VXWORKS__
    timer_cancel( m_tiTmr );
    timer_delete( m_tiTmr );

#elif __linux__


#endif

}

/**
 * @brief     Init
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-29 10:40:20
 * @warning
 */
void CTimer::Init()
{



}

/**
 * @brief     SetTime
 * @param     unsigned int uiSec
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-29 10:26:05
 * @warning
 */
void CTimer::SetTime( unsigned int uiSec )
{

    TRACE( "\n 타이머 설정 : %d 초", uiSec );

#ifdef _MSC_VER


#elif __VXWORKS__
    struct itimerspec tv;

    tv.it_value.tv_sec = uiSec;
    tv.it_value.tv_nsec = 0;

    timer_settime( m_tiTmr, 0, &tv, NULL );

#elif __linux__


#endif

}

#ifdef __VXWORKS__

/**
 * @brief     TimerRoutine
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-29 10:43:19
 * @warning
 */
void CTimer::TimerRoutine()
{
    printf( "\n Timer..." );

}


#endif
