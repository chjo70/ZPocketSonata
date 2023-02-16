﻿// _Define.h: interface for the 분석 소프트웨어의 정의
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NDEFINE_H__454E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)
#define AFX_NDEFINE_H__454E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_

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



#endif // !defined(AFX_NDEFINE_H__454E4EC8_E880_4D0F_B7D9_86F03F2A5E3C__INCLUDED_)
