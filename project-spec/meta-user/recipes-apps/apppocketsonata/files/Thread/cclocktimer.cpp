/*****************************************************************************************

    @file      curbit.cpp
    @brief     자체점검을 처리하는 쓰레드 입니다.
    @details   ~
    @author    조철희
    @date      10.04.2023
    @copyright © Cool Guy, 2023. All right reserved.

*****************************************************************************************/

#include "stdafx.h"

#include "cclocktimer.h"
#include "ccgi.h"

#ifdef __VXWORKS__
#include <hwif/vxBus.h>
#include <hwif/vxbus/vxbLib.h>

#include "vxbM85xxI2c.h"
#include "vxbAdt7481Temp.h"

extern "C" {

    // BSP 수록... 변수명이 global 하게 안 보입니다.
    // extern VXB_DEV_ID pAdt7481Inst;
}

#endif


//#include "../Utils/chwio.h"
#include "../Utils/ccommonutils.h"
#include "../Include/globals.h"




#define _DEBUG_

/**
 * @brief     자체점검 객체를 생성합니다.
 * @param     int iKeyId
 * @param     const char * pClassName
 * @param     bool bArrayLanData
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-02 10:00:08
 * @warning
 */
CClockTimer::CClockTimer( const char *pColokName ) : CTimer( pColokName )
{
    //LOGENTRY;


}

/**
 * @brief     자체점검 객체를 소멸합니다.
 * @param     void
 * @return
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-03-02 10:00:46
 * @warning
 */
CClockTimer::~CClockTimer( void )
{

}

/**
 * @brief     Start
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-29 13:49:19
 * @warning
 */
void CClockTimer::Start()
{
    CTimer::SetTime( 10 );

}

/**
 * @brief     Stop
 * @return    void
 * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   1.0.0
 * @date      2023-08-29 13:49:21
 * @warning
 */
void CClockTimer::Stop()
{

    CTimer::SetTime( 0 );

}