/**

    @file      define.h
    @brief
    @details   ~
    @author    Cool Guy
    @date      18.06.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/

#pragma once


// _Define.h: interface for the 분석 소프트웨어의 정의
//
//////////////////////////////////////////////////////////////////////


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../SigAnal/_Define.h"


// 최대 레이더모드 개수
#define MAX_RADARMODE			    (20000)

// 최대 위협 개수
#define MAX_THREAT				    (5000)

/**
 * @def       NO_FLIB_BAND
 * @brief     신호 식별 테이블의 최대 주파수 밴드 개수
     조철희 (churlhee.jo@lignex1.com)
 */
#define	NO_FLIB_BAND				(32)


// 쿼리문 길이
#define MAX_SQL_SIZE                (1024*4)




