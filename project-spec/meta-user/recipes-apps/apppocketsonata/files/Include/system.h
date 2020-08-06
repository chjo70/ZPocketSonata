/*
 * 본 문서는 시스템을 정의하는 테이블과 운영체계 또는 컴파일러에 의존하여 정의한다.
 * */

#ifndef _SYSTEM_H
#define _SYSTEM_H


// PDW 최대 크기 정의함. 랜 송수신 데이터 및 분석하기 위한 최대 PDW 개수 정의
#define _MAX_COL_PDW        (1024)


// 랜 데이터 최대 크기
#define _MAX_LANDATA        (1024*256)



/////////////////////////////////////////////////////////////////////////////////////
// 아래는 장치, 쓰레드 간의 명령어 OPCODE 시작 주소를 의미한다.
#define _START_OPCODE_OF_MESSAGE_               (0x00)  // (0xA100)
#define _START_OPCODE_OF_THREAD_MESSAGE_        (0x80)  //(0xA000)




#include "defines.h"

#include "struct.h"
#include "sysmsg.h"
#include "thrmsg.h"
#include "global.h"


//#include "../Utils/ccommonutils.h"

//#include "../Utils/stdstring.h"




#endif // _SYSTEM_H
