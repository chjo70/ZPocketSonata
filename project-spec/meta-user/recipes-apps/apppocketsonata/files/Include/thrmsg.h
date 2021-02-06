/*
 * 본 문서는 쓰레들간의 내부 메시지를 정의합니다. 메시지들간의 정의와 데이터를 나타냅니다.
 * */


#ifndef _THRMSG_H
#define _THRMSG_H

#include "system.h"
//#include "./SONATAPIP/_sysmsg.h"


//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
// 수신 메시지 정의
enum enTHREAD_REQ_MESSAGE {
    // 1. 쓰레드 관리 쓰레드 에서 수신 메시지 정의
    // 1.1 프로세스 종료 메시지
    enTHREAD_REQ_SHUTDOWN = _START_OPCODE_OF_THREAD_MESSAGE_,

    // 2. 신호 수집 쓰레드 에서 수신 메시지 정의
    // 추적 수집 신호 설정 메시지
    enTHREAD_REQ_SET_TRACKWINDOWCELL,
    enTHREAD_REQ_CLOSE_TRACKWINDOWCELL,

    // 스캔 수집 신호 설정 메시지
    enTHREAD_REQ_SET_SCANWINDOWCELL,
    enTHREAD_REQ_CLOSE_SCANWINDOWCELL,


    // 제어 메시지
    enTHREAD_MODE = enREQ_MODE,

    // 분석 관련 메시지
    enTHREAD_DETECTANAL_START = enREQ_ANAL_START,
    enTHREAD_DETECTANAL_END,
    enTHREAD_KNOWNANAL_START,
    enTHREAD_KNOWNANAL_END,
    enTHREAD_SCANANAL_START,
    enTHREAD_SCANANAL_END,

    // 라이브러리 관련 메시지
    enTHREAD_RELOAD_LIBRARY = enREQ_RELOAD_LIBRARY,
    enTHREAD_IPLVERSION = esIPL_VERSION,
    enTHREAD_REQ_IPLVERSION = enREQ_IPL_VERSION,

    enTHREAD_IPL_START = enREQ_IPL_START,
    enTHREAD_IPL_DOWNLOAD = enREQ_IPL_DOWNLOAD,
    enTHREAD_IPL_END = enREQ_IPL_END,

    // 자체점검 관련 메시지
    enTHREAD_REQ_IBIT = enREQ_IBIT,
    enTHREAD_REQ_UBIT = enREQ_UBIT,
    enTHREAD_REQ_CBIT = enREQ_CBIT,
    enTHREAD_REQ_SBIT = enREQ_SBIT,

    // 수집 제어 관련 메시지
    enTHREAD_REQ_SETCONFIG = enREQ_SET_CONFIG,
    enTHREAD_REQ_STOP = enREQ_STOP,
    enTHREAD_REQ_COLSTART = enREQ_COL_START,
    enTHREAD_REQ_RAWDATA = enREQ_RAWDATA,

    // CGI 명령 관련 메시지
    enCGI_REQ_IBIT = 0xF000,
    enCGI_REQ_UBIT,
    enCGI_REQ_CBIT,
    enCGI_REQ_SBIT,
    enCGI_FETCH,
    enCGI_REQ_SPECTRUM,

    //
    enTHREAD_REQ_SIM_PDWDATA = enREQ_SIM_PDWDATA,


} ;




#endif // _THRMSG_H
