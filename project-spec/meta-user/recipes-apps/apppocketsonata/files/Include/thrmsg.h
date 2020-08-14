/*
 * 본 문서는 쓰레들간의 내부 메시지를 정의합니다. 메시지들간의 정의와 데이터를 나타냅니다.
 * */


#ifndef _THRMSG_H
#define _THRMSG_H

#include "system.h"
#include "./SONATAPIP/_sysmsg.h"


//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
// 수신 메시지 정의
enum enTHREAD_REQ_MESSAGE {
    // 1. 쓰레드 관리 쓰레드 에서 수신 메시지 정의
    // 1.1 프로세스 종료 메시지
    enTHREAD_REQ_SHUTDOWN = _START_OPCODE_OF_THREAD_MESSAGE_,

    // 2. 신호 수집 쓰레드 에서 수신 메시지 정의
    // 수집 신호 설정 메시지
    enTHREAD_REQ_SETWINDOWCELL,


    // 기존 소나타의 타스크간 메시지 정의
    enTHREAD_MODE = enREQ_MODE,
    enTHREAD_ANAL_START = enREQ_ANAL_START, // = Msys_Start,

    //
    enTHREAD_REQ_SIM_PDWDATA = enREQ_SIM_PDWDATA,


} ;




#endif // _THRMSG_H
