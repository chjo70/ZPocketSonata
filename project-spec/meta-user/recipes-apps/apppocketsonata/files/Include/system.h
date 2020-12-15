/*
 * 본 문서는 시스템을 정의하는 테이블과 운영체계 또는 컴파일러에 의존하여 정의한다.
 * */

#ifndef _SYSTEM_H
#define _SYSTEM_H


// PDW 최대 크기 정의함. 랜 송수신 데이터 및 분석하기 위한 최대 PDW 개수 정의
#define _MAX_COL_PDW        (100)


// 랜 데이터 최대 크기
#define _MAX_LANDATA        (1024*256)



/////////////////////////////////////////////////////////////////////////////////////
// 아래는 장치, 쓰레드 간의 명령어 OPCODE 시작 주소를 의미한다.
#define _START_OPCODE_OF_MESSAGE_               (0x00)  // (0xA100)
#define _START_OPCODE_OF_THREAD_MESSAGE_        (0x80)  //(0xA000)


/////////////////////////////////////////////////////////////////////////////////////
// 시스템 변수 기본 설정 값

// 수신기 임계값
#define _RXTHRESHOLD_BAND1_                 "-60.0"
#define _RXTHRESHOLD_BAND2_                 "-55.3"
#define _RXTHRESHOLD_BAND3_                 "-60.2"
#define _RXTHRESHOLD_BAND4_                 "-70.0"
#define _RXTHRESHOLD_BAND5_                 "-75.0"

// 에미터 최소 펄스 신호 개수
#define _ANAL_MIN_PULSECOUNT_               (5)

// 최소 신호 삭제 시간 [초]
#define _DEFAULT_DELETETIME_                (30)
#define MIN_EMITTER_DELETE_TIME             (10)




#include "defines.h"

#include "struct.h"
#include "sysmsg.h"
#include "thrmsg.h"
#include "global.h"

//#include "../Utils/ccommonutils.h"

//#include "../Utils/stdstring.h"

// 쓰레드에 대한 큐메시지 키 값 정의

#define _SHM_MEMORY_KEY             (333)

enum ENUM_THREAD_KEY {
    _MSG_TMNGR_KEY = (_SHM_MEMORY_KEY) + 1,
    _MSG_URBIT_KEY,
    _MSG_PULTRK_KEY,
    _MSG_JAMTEC_KEY,
    _MSG_RECZYNQ_KEY,
    _MSG_RECCCU_KEY,
    _MSG_ZYNQ_KEY,
    _MSG_CCU_KEY,
    _MSG_PMC_KEY,
    _MSG_ZCGI_KEY,
    _MSG_USERCOL_KEY,

    _MSG_CGI_KEY,

    _MSG_PROMPT_KEY,

};






#endif // _SYSTEM_H
