/*
 * 본 문서는 쓰레들간의 내부 메시지를 정의합니다. 메시지들간의 정의와 데이터를 나타냅니다.
 * */


#pragma once

#include "system.h"
#include "./SONATAPIP/_sysmsg.h"


//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
// 수신 메시지 정의
enum enTHREAD_REQ_MESSAGE : unsigned int {
    // 1. 쓰레드 관리 쓰레드 에서 수신 메시지 정의
    // 1.1 프로세스 종료 메시지
    enTHREAD_REQ_START = _START_OPCODE_OF_THREAD_MESSAGE_,
    enTHREAD_REQ_SHUTDOWN,
    enTHREAD_REQ_RESTART,

    // 비정상 랜 소켓 단락
    enTHREAD_DISCONNECTED,

    // 2. 신호 수집 쓰레드 에서 수신 메시지 정의
    enTHREAD_REQ_COMPLETECOL,

    // 탐지 수집 신호 완료 메시지
    enTHREAD_REQ_DETECT_COLSTOP,
    enTHREAD_REQ_TRACK_COLSTOP,
    enTHREAD_REQ_SCAN_COLSTOP,
    enTHREAD_REQ_SET_DETECTWINDOWCELL,

    // 추적 수집 신호 설정 메시지
    enTHREAD_REQ_SET_TRACKWINDOWCELL,
    enTHREAD_REQ_CLOSE_TRACKWINDOWCELL,

    // 스캔 수집 신호 설정 메시지
    enTHREAD_REQ_SCAN_START,
    //enTHREAD_REQ_SET_SCANWINDOWCELL,
    enTHREAD_REQ_CLOSE_SCANWINDOWCELL,


    // 제어 메시지
    //enTHREAD_MODE = enREQ_MODE,

    // 분석 관련 제어 메시지
    // 탐지 분석 결과
    enTHREAD_DETECTANAL_START,                  //< 탐지 분석 시작 또는 병합/식별 시작 메시지
    enTHREAD_DETECTANAL_RESULT,                 //< 탐지 분석 결과 메시지
    enTHREAD_DETECTANAL_END,

    enTHREAD_KNOWNANAL_START,
    enTHREAD_KNOWNANAL_END,
    enTHREAD_KNOWNANAL_FAIL,

    // 스캔 분석 결과
    enTHREAD_SCANANAL_START,                    //< 스캔 분석 시작 또는 병합/식별 시작 메시지
    enTHREAD_SCANANAL_RESULT,
    enTHREAD_SCANANAL_FAIL,                    //< 스캔 수집 및 분석 실패 메시지
    enTHREAD_SCANANAL_ERROR,                   //< 스캔 수집을 수행할 수 없을 때 (이미 위협이 삭제된 경우)
    enTHREAD_SCANANAL_END,

    enTHREAD_DELETE_THREAT,
    enTHREAD_TIMER,

    // 라이브러리 관련 메시지
    enTHREAD_RELOAD_LIBRARY = enREQ_RELOAD_LIBRARY,
    //enTHREAD_IPLVERSION = enIPL_VERSION,
    //enTHREAD_REQ_IPLVERSION = enREQ_IPL_VERSION,

    //enTHREAD_IPL_START = enREQ_IPL_START,
    //enTHREAD_IPL_DOWNLOAD = enREQ_IPL_DOWNLOAD,
    //enTHREAD_IPL_END = enREQ_IPL_END,

    // 자체점검 관련 메시지
    enTHREAD_REQ_IBIT = enREQ_IBIT,
    enTHREAD_REQ_UBIT = enREQ_UBIT,
    enTHREAD_REQ_CBIT = enREQ_CBIT,
    enTHREAD_REQ_SBIT = enREQ_SBIT,

    // 수집 제어 관련 메시지
    enTHREAD_REQ_SETCONFIG = enREQ_SET_CONFIG,
    //enTHREAD_REQ_STOP = enREQ_STOP,
    enTHREAD_REQ_COLSTART = enREQ_COL_START,
    enTHREAD_REQ_COLEND = enREQ_STOP,
    enTHREAD_REQ_RAWDATA = enREQ_RAWDATA,

    // 관리 관련 메시지
    enTHREAD_REQ_CLEANUP,

    // 로그 관련 메시지
    enTHREAD_LOG,

    // CGI 명령 관련 메시지
    enCGI_REQ_IBIT = 0xF000,
    enCGI_REQ_UBIT,
    enCGI_REQ_CBIT,
    enCGI_REQ_SBIT,
    enCGI_FETCH,
    enCGI_REQ_SPECTRUM,

    //
    enTHREAD_REQ_SIM_PDWDATA = enREQ_SIM_PDWDATA,

    // 타스크 상태 및 정보 전시
    enMONITOR,

    enTHREAD_EXIT,


} ;



