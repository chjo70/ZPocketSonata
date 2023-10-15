// Macros.h: interface for the macro definetion
//
//////////////////////////////////////////////////////////////////////


#pragma once

// 아래는 부트 프로그렘에서 정의한 define 문 입니다.

#include <stdio.h>

#define TICK_COUNT									(100)
#define OS_ONE_SEC									TICK_COUNT
#define OS_TEN_MILLISEC								(1)
#define OS_ONE_MILLISEC								(0.1)

#ifndef WhereIs
#define WhereIs									    TRACE( "...in %s 파일 %d 라인" , strrchr(__FILE__,'/') ? strrchr(__FILE__,'/') : __FILE__ , __LINE__ )
#endif

#ifndef PrintErr
#define PrintErr(A)							        { printf A; WhereIs; }
#endif



