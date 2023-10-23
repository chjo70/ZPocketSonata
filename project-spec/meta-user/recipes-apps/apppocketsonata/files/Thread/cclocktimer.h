/**

    @file      cclocktimer.h
    @brief
    @details   ~
    @author    Cool Guy
    @date      13.08.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#pragma once



#include "../Utils/timer.h"
#include "../Utils/clog.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
// 아래는 이 쓰레드에서 사용하는 클래스를 정의합니다.
//#include "../Utils/cgpio.h"

#define _AXI_DATATEST_          (0xAABBEEF0)

/**
 *
 * @brief	  신호분석 CSC의 자체점검을 담당합니다.
 * @details	  신호분석 연동 제어 기능을 수행한다
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-01-16 10:54:00
 * @warning
 *
 */
class CClockTimer : public CTimer
{
private:

public:

private:


public:
    CClockTimer( const char *pColokName=NULL );			                            ///< 초기 멤버 변수값 등을 설정하는 객체 생성자 입니다.
    virtual ~CClockTimer();															///< 종료 메시지와 메모리 해지를 처리하는 객체 소먈자 입니다.

    void Start();
    void Stop();

};


