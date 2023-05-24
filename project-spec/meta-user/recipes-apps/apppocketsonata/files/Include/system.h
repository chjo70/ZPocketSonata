/*
 * 본 문서는 시스템을 정의하는 테이블과 운영체계 또는 컴파일러에 의존하여 정의한다.
 * */

#pragma once

// 채널 수 정의
#define CO_DETECT_CHANNEL	(1)                         // 탐지용 채널은 1개로 설정함. 현재 PL 전처리필터의 채널이 1개임.

#ifdef _MSC_VER
#define CO_TRACK_CHANNEL	(0)                         //
#else
#define CO_TRACK_CHANNEL	(0)                         //
#endif


#define CO_SCAN_CHANNEL		(3)
#define CO_USER_CHANNEL		(0)
#define TOTAL_CHANNELS		(CO_DETECT_CHANNEL+CO_TRACK_CHANNEL+CO_SCAN_CHANNEL+CO_USER_CHANNEL)
#define MAX_CHANNELS		(TOTAL_CHANNELS)

// PDW 최대 크기 정의함. 랜 송수신 데이터 및 분석하기 위한 최대 PDW 개수 정의
#define _MAX_COL_PDW        (100)


// 랜 데이터 최대 크기
#define _MAX_LANDATA        (200*1024)
#define _MAX_LOBDATA        (_MAX_LANDATA/sizeof(SRxLOBData))



/////////////////////////////////////////////////////////////////////////////////////
// 아래는 장치, 쓰레드 간의 명령어 OPCODE 시작 주소를 의미한다.
#define _START_OPCODE_OF_OPCONTROL_             (0x0101)  // (0xA100)
#define _START_OPCODE_OF_LIBRARY_               (0x0201)  // (0xA100)
#define _START_OPCODE_OF_THREAT_                (0x0301)  // (0xA100)

#define _START_OPCODE_OF_THREAD_MESSAGE_        (0x80)  //(0xA000)


/////////////////////////////////////////////////////////////////////////////////////
// 시스템 변수 기본 설정 값

// 대역별 수신 임계값
#define _DEFAULT_RXTHRESHOLD_BAND1_                 (float) (-60.0)
#define _DEFAULT_RXTHRESHOLD_BAND2_                 (float) (-55.3)
#define _DEFAULT_RXTHRESHOLD_BAND3_                 (float) (-60.2)
#define _DEFAULT_RXTHRESHOLD_BAND4_                 (float) (-70.0)
#define _DEFAULT_RXTHRESHOLD_BAND5_                 (float) (-75.0)
#define _DEFAULT_RXTHRESHOLD_BAND6_                 (float) (-72.1)


// 대역별 방위 병합 오차
#define _DEFAULT_RECEIVER_AOA_ERROR_				(float) (2.0)       // 도(degree)



// 대역별 방위 병합 오차
#define _DEFAULT_AOA_ERROR_							(float) (1.0)       // 도(degree)


// 기본 마진 값
#define _DEFAULT_FREQ_MARGIN_                       (float) (5.0)
#define _DEFAULT_STABLE_MARGIN_                     (float) (2.0)



// 에미터 최소 펄스 신호 개수
#define _DEFAULT_ANAL_MINPULSECOUNT_                (5)

// 최소 신호 삭제 시간 [초]
#define _DEFAULT_DELETETIME_                        (30)
#define _DEFAULT_MIN_EMITTER_DELETETIME             (10)

// 기본 라이브러리 버젼
#define _DEFAULT_LIB_VERSION_                       (0)


#include "defines.h"

#include "struct.h"
#include "sysmsg.h"
#include "thrmsg.h"
#include "global.h"

//#include "../Utils/ccommonutils.h"

//#include "../Utils/stdstring.h"

// 쓰레드에 대한 큐메시지 키 값 정의

#ifdef __VXWORKS__
#define _OFFSET_KEY_                (100)
#elif _MSC_VER
#define _OFFSET_KEY_                (0)
#else
#define _OFFSET_KEY_                (_SHM_MEMORY_KEY)
#endif

// 아래 정의된 키는 vxworks 에서는 priority 로 사용한다.
#ifdef __VXWORKS__
#include <stdio.h>
#define _MSG_CCU_KEY NULL
#define _MSG_TMNGR_KEY NULL
#define _MSG_URBIT_KEY NULL
#define _MSG_RECCCU_KEY NULL
#define _MSG_USERCOL_KEY NULL

#else
enum ENUM_THREAD_KEY {
    _MSG_TMNGR_KEY = (_OFFSET_KEY_) + 1,
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

    _MSG_CGI_KEY,           // 웹 서버에서 메시지를 받기 위한 메시지 ID

    _MSG_PROMPT_KEY,

};

#endif



// 에러 코드 정의 테이블
enum ENUM_ERROR_CODE {
    enERROR_OF_SENDMSG=0xff00,

    enERROR_OF_ARRAY_MARK,


};

enum ENUM_PCI_DRIVER {
    enLEFT_PCI_DRIVER = 0,
    enRIGHT_PCI_DRIVER,
    // enDUAL_PCI_DRIVER,

    en_ELEMENT_PCI_DRIVER

};


struct STR_LOG_INFO {
    int nType;

    int iLine;

};

/**
    @struct STR_COLLECTINFO
    @brief  수집 쓰레드 정보
**/
struct STR_COLLECT_INFO {
    unsigned int uiReqStatus;
    unsigned int uiTotalPDW;

    // 방사체 번호
    unsigned int uiAETID;
    // 빔 번호
    unsigned int uiABTID;
    // 좌/우 PCI 값
    ENUM_PCI_DRIVER enPCIDriver;
    // 수집 뱅크
    ENUM_COLLECTBANK enCollectBank;
    // 위협의 인덱스 정보
    unsigned int uiABTIndex;

    // 채널 번호에 따른 수집 개수
    unsigned int uiCh2TotalPDW[TOTAL_CHANNELS];

    void Set( unsigned int i_uiCh, unsigned int i_uiTotalPDW, unsigned int i_uiAETID, unsigned int i_uiABTID, ENUM_PCI_DRIVER i_enPCIDriver, ENUM_COLLECTBANK i_enCollectBank, unsigned int i_uiABTIndex )
    {
        uiReqStatus = i_uiCh;
        uiTotalPDW = i_uiTotalPDW;
        uiAETID = i_uiAETID;
        uiABTID = i_uiABTID;
        enPCIDriver = i_enPCIDriver;
        enCollectBank = i_enCollectBank;
        uiABTIndex = i_uiABTIndex;

    }

};

/**
    @struct STR_ANALINFO
    @brief  수집한 데이터에서 분석한 LOB 헤더 정보
**/
struct STR_DETANAL_INFO {
    //ENUM_BoardID enBoardID;
    unsigned int uiTotalLOB;

    // 수집한 채널 정보
    unsigned int uiCh;

    // 탐지, 추적, 스캔 수집 뱅크 정의
    ENUM_COLLECTBANK enCollectBank;

    // 좌/우 PCI
    ENUM_PCI_DRIVER enPCIDriver;

    // 방사체 번호
    unsigned int uiAETID;

    // 빔 번호
    unsigned int uiABTID;

    // 방사체/빔/LOB 저장소 인덱스
    unsigned int uiABTIndex;

    void Set( ENUM_PCI_DRIVER i_enPCIDriver, unsigned int i_uiTotalLOB, unsigned int i_uiCh, ENUM_COLLECTBANK i_enCollectBank, unsigned int i_uiAETID, unsigned int i_uiABTID, unsigned int i_uiABTIndex )
    {
        //enBoardID = i_enBoardID;
        enPCIDriver = i_enPCIDriver;
        uiTotalLOB = i_uiTotalLOB;
        uiCh = i_uiCh;
        enCollectBank = i_enCollectBank;
        uiAETID = i_uiAETID;
        uiABTID = i_uiABTID;
        uiABTIndex = i_uiABTIndex;
    }

};

/**
    @struct STR_SCANANAL_INFO
    @brief  스캔 분석 관련 구조체 정의
**/
struct STR_SCANANAL_INFO {
    ENUM_BoardID enBoardID;

    // 수집한 채널 정보
    unsigned int uiCh;

    // 탐지, 추적, 스캔 수집 뱅크 정의
    ENUM_COLLECTBANK enCollectBank;

    // 방사체 번호
    unsigned int uiAETID;
    // 빔 번호
    unsigned int uiABTID;

    // 방사체/빔/LOB 저장소 인덱스
    unsigned int uiABTIndex;

    // 스캔 채널에 대해서 수집 시간 스텝 정보
    unsigned int uiScanStep;

    void Set( ENUM_BoardID i_enBoardID, unsigned int i_uiCh, ENUM_COLLECTBANK i_enCollectBank, unsigned int i_uiAETID, unsigned int i_uiABTID, unsigned int i_uiABTIndex, unsigned int i_uiScanStep )
    {
        enBoardID = i_enBoardID;
        uiCh = i_uiCh;
        enCollectBank = i_enCollectBank;
        uiAETID = i_uiAETID;
        uiABTID = i_uiABTID;
        uiABTIndex = i_uiABTIndex;
        uiScanStep = i_uiScanStep;

    }

};

/**
    @union UNI_MSG_DATA
    @brief 메시지 데이터 구조체
**/
union UNI_MSG_DATA {
    unsigned int uiData;
    time_t tiNow;

    STR_COLLECT_INFO strCollectInfo;
    STR_DETANAL_INFO strDetAnalInfo;
    STR_SCANANAL_INFO strScanAnalInfo;

    STR_LOG_INFO strLogInfo;

    char szData[32 * 2];

    STR_COLLECT_INFO *GetCollectInfo() { return &strCollectInfo; }
    STR_DETANAL_INFO *GetDetectAnalInfo() { return &strDetAnalInfo; }
    STR_SCANANAL_INFO *GetScanAnalInfo() { return &strScanAnalInfo; }

};


