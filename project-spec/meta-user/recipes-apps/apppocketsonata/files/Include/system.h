/*
 * 본 문서는 시스템을 정의하는 테이블과 운영체계 또는 컴파일러에 의존하여 정의한다.
 * */

#pragma once



 // 채널 수 정의
#define CO_DETECT_CHANNEL	(1)                         // 탐지용 채널은 1개로 설정함. 현재 PL 전처리필터의 채널이 1개임.


#if defined(_POCKETSONATA_) || defined(_SONATA_)
#ifdef __VXWORKS__
#define CO_TRACK_CHANNEL	(14)
#define CO_SCAN_CHANNEL		(4)

#else
#define CO_TRACK_CHANNEL	(14)             // 14
#define CO_SCAN_CHANNEL		(4)

#endif

#define CO_PREFILTER_CHANNEL    (CO_TRACK_CHANNEL)        // 전처리 필터는 추적 필터 개수만큼 적용합니다.

#else
#define CO_TRACK_CHANNEL	(0)
#define CO_SCAN_CHANNEL		(0)

#define CO_PREFILTER_CHANNEL    CO_TRACK_CHANNEL

#endif



#define APPLIED_DETECT      ( ( 1 << CO_DETECT_CHANNEL) - 1 )
#define APPLIED_TRACK       ( ( 1 << CO_TRACK_CHANNEL) - 1 )
#define APPLIED_SCAN        ( ( 1 << CO_SCAN_CHANNEL) - 1 )


#define CO_USER_CHANNEL		(0)
#define TOTAL_CHANNELS		(CO_DETECT_CHANNEL+CO_TRACK_CHANNEL+CO_SCAN_CHANNEL+CO_USER_CHANNEL)
#define MAX_CHANNELS		(TOTAL_CHANNELS)

// PDW 최대 크기 정의함. 랜 송수신 데이터 및 분석하기 위한 최대 PDW 개수 정의
#define _MAX_COL_PDW        (100)


// 랜 데이터 최대 크기
//#define _MAX_LANDATA        (50*1024)
//#define _MAX_LOBDATA        (_MAX_LANDATA/sizeof(struct SRxLOBData))



/////////////////////////////////////////////////////////////////////////////////////
// 아래는 장치, 쓰레드 간의 명령어 OPCODE 시작 주소를 의미한다.
#define _START_OPCODE_OF_OPCONTROL_             (0x0101)  // (0xA100)
#define _START_OPCODE_OF_LIBRARY_               (0x0201)  // (0xA100)
#define _START_OPCODE_OF_THREAT_                (0x0301)  // (0xA100)
#define _START_OPCODE_OF_OPSYSVAR_              (0x0401)
#define _START_OPCODE_OF_SYSERROR_              (0x0F01)

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



// 방위 그룹화시 피크에서 좌우 반경 범위로 설정 정의
#define _DEFAULT_AOA_GROUP_							(float) (1.0)       // 도(degree)


// 방위 그룹화시 피크에서 좌우 반경 범위로 설정 정의
#define _DEFAULT_FRQ_GROUP_							(float) (1000.0)    // 도(KHz)


// 기본 마진 값
#define _DEFAULT_FREQ_MARGIN_                       (float) (5.0)
#define _DEFAULT_STABLE_MARGIN_                     (float) (2.0)

#define _DEFAULT_AOA_GROUP_MARGIN_                  (7)

#define _DEFAULT_STEADY_MIN_PA_DBM                  (-50)

#define _DEFAULT_CONICAL_MIN_PERIOD_MS              (5)
#define _DEFAULT_CONICAL_MAX_PERIOD_MS              (500)

#define _DEFAULT_WINDOWCELL_DOA_RANGE_              (10.0)
#define _DEFAULT_WINDOWCELL_FRQ_RANGE_              (5.0)
#define _DEFAULT_WINDOWCELL_FRQ_HOPPING_RATIO_      (27.0)


// 에미터 최소 펄스 신호 개수
#define _DEFAULT_ANAL_MINPULSECOUNT_                (5)

// 최소 신호 삭제 시간 [초]
#define _DEFAULT_DELETETIME_                        (30)
#define _DEFAULT_MIN_EMITTER_DELETETIME             (10)

#define _DEFAULT_COUNT_OF_LOB_                      (10)
#define _DEFAULT_MAX_COUNT_OF_LOB_                  (100)

// 기본 라이브러리 버젼
#define _DEFAULT_LIB_VERSION_                       (0)

// CPU 온도 경고 임계값
#define _DEFAULT_CPU_TEMP_WARNING_                  (90)


/**
    @enum  ENUM_ROBUST_ANAL
    @brief 정밀 분석 세부 플레그 설정
**/
enum ENUM_ROBUST_ANAL : unsigned int {
    enNO_ROBUST_ANALYSIS = 0,

    enFREQ_ROBUST_ANALYSIS,
    enPRI_ROBUST_ANALYSIS,

    enFREQ_PRI_ROBUST_ANALYSIS

};


#include "defines.h"

#include "struct.h"
#include "sysmsg.h"
#include "thrmsg.h"
#include "global.h"

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
#define _MSG_CCU_DEBUG_KEY NULL

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
    _MSG_CCU_DEBUG_KEY,
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





enum ENUM_PCI_DRIVER : unsigned int {
    enLEFT_PCI_DRIVER = 0,
    enRIGHT_PCI_DRIVER,
    // enDUAL_PCI_DRIVER,

    enUNKNOWN_PCI_DRIVER,

    en_ELEMENT_PCI_DRIVER

};

struct STR_LOG_INFO {
    int nType;

    int iLine;

};

#ifndef SRxScanData_STRUCT
#define SRxScanData_STRUCT
struct STR_SCANRESULT {
    EN_SCANRESULT enResult;
    unsigned int uiScanPeriod;          //! 스캔 주기
    ENUM_AET_SCAN_TYPE enScanType;      //! 스캔 형태

    float fCoScanCollectingPDW;
    float fScanDurationms;      // [ms]


    // 신호 세기 관련 정보
    unsigned int uiMedianPA;
    STR_MINMAX stPA;

};
#endif

/**
    @struct STR_COLLECTINFO
    @brief  수집 쓰레드 정보
**/
typedef struct stSTR_COLLECT_INFO {
    unsigned int uiReqStatus[3];
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

    void Set( unsigned int uiReqStatus_0, unsigned int uiReqStatus_1, unsigned int i_uiTotalPDW, unsigned int i_uiAETID, unsigned int i_uiABTID, ENUM_PCI_DRIVER i_enPCIDriver, ENUM_COLLECTBANK i_enCollectBank, unsigned int i_uiABTIndex )
    {
        uiReqStatus[0] = uiReqStatus_0;
        uiReqStatus[1] = uiReqStatus_1;
        uiReqStatus[2] = uiReqStatus_1;

        uiTotalPDW = i_uiTotalPDW;
        uiAETID = i_uiAETID;
        uiABTID = i_uiABTID;
        enPCIDriver = i_enPCIDriver;
        enCollectBank = i_enCollectBank;
        uiABTIndex = i_uiABTIndex;

    }

} STR_COLLECT_INFO;

/**
    @struct STR_ANALINFO
    @brief  수집한 데이터에서 분석한 LOB 헤더 정보
**/
typedef struct stSTR_DETANAL_INFO {
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
        enPCIDriver = i_enPCIDriver;
        uiTotalLOB = i_uiTotalLOB;
        uiCh = i_uiCh;
        enCollectBank = i_enCollectBank;
        uiAETID = i_uiAETID;
        uiABTID = i_uiABTID;
        uiABTIndex = i_uiABTIndex;
    }

} STR_DETANAL_INFO;

/**
    @struct STR_TRKANALINFO
    @brief  수집한 데이터에서 분석한 LOB 헤더 정보
**/
typedef struct stSTR_TRKANAL_INFO {
    //ENUM_BoardID enBoardID;
    unsigned int uiTotalLOB;

    // 수집한 채널 정보
    unsigned int uiGlobalCh;

    // 탐지, 추적, 스캔 수집 뱅크 정의
    ENUM_COLLECTBANK enCollectBank;

    // 좌/우 PCI
    ENUM_PCI_DRIVER enPCIDriver;

    // 방사체 번호
    unsigned int uiAETID;

    // 빔 번호
    unsigned int uiABTID;

    // 정밀 분석 플레그
    ENUM_ROBUST_ANAL enRobustAnal;

    STR_WINDOWCELL_INFO stTrackWinCellInfo;

    void Set( unsigned int i_uiGlobalCh, ENUM_PCI_DRIVER i_enPCIDriver, unsigned int i_uiTotalLOB, ENUM_COLLECTBANK i_enCollectBank, unsigned int i_uiAETID, unsigned int i_uiABTID, ENUM_ROBUST_ANAL i_enRobustAnal )
    {
        enPCIDriver = i_enPCIDriver;
        uiTotalLOB = i_uiTotalLOB;
        uiGlobalCh = i_uiGlobalCh;
        enCollectBank = i_enCollectBank;
        uiAETID = i_uiAETID;
        uiABTID = i_uiABTID;
        enRobustAnal = i_enRobustAnal;
    }

} STR_TRKANAL_INFO;

/**
    @struct STR_SCANANAL_INFO
    @brief  스캔 분석 관련 구조체 정의
**/
typedef struct stSTR_SCANANAL_INFO {
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

    // 스캔 채널에 대해서 수집 시간 정보
    unsigned int uiReqScanPeriod;

    // 스캔 분석 결과
    STR_SCANRESULT stScanResult;


    /**
     * @brief     Set
     * @param     ENUM_BoardID i_enBoardID
     * @param     unsigned int i_uiCh
     * @param     ENUM_COLLECTBANK i_enCollectBank
     * @param     unsigned int i_uiAETID
     * @param     unsigned int i_uiABTID
     * @param     unsigned int i_uiABTIndex
     * @param     unsigned int i_uiScanStep
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-08-17 09:08:01
     * @warning
     */
    void Set( unsigned int i_uiCh, ENUM_COLLECTBANK i_enCollectBank, unsigned int i_uiAETID, unsigned int i_uiABTID, unsigned int i_uiABTIndex, unsigned int i_uiReqScanPeriod, unsigned int i_uiScanStep )
    {
        uiCh = i_uiCh;
        enCollectBank = i_enCollectBank;
        uiAETID = i_uiAETID;
        uiABTID = i_uiABTID;
        uiABTIndex = i_uiABTIndex;
        uiReqScanPeriod = i_uiReqScanPeriod;
        uiScanStep = i_uiScanStep;

        memset( & stScanResult, 0, sizeof( stScanResult ) );

        stScanResult.enResult = _spAnalFail;
        stScanResult.enScanType = ENUM_AET_SCAN_TYPE::E_AET_SCAN_UNKNOWN;

    }

    /**
     * @brief     Set
     * @param     ENUM_BoardID i_enBoardID
     * @param     unsigned int i_uiCh
     * @param     ENUM_COLLECTBANK i_enCollectBank
     * @param     unsigned int i_uiAETID
     * @param     unsigned int i_uiABTID
     * @param     unsigned int i_uiABTIndex
     * @param     unsigned int i_uiScanStep
     * @param     STR_SCANRESULT i_scanResult
     * @return    void
     * @exception 예외사항을 입력해주거나 '해당사항 없음' 으로 해주세요.
     * @author    조철희 (churlhee.jo@lignex1.com)
     * @version   1.0.0
     * @date      2023-08-17 09:08:04
     * @warning
     */
    void Set( unsigned int i_uiCh, ENUM_COLLECTBANK i_enCollectBank, unsigned int i_uiAETID, unsigned int i_uiABTID, unsigned int i_uiABTIndex, unsigned int i_uiReqScanPeriod, unsigned int i_uiScanStep, STR_SCANRESULT *i_pscanResult)
    {
        uiCh = i_uiCh;
        enCollectBank = i_enCollectBank;
        uiAETID = i_uiAETID;
        uiABTID = i_uiABTID;
        uiABTIndex = i_uiABTIndex;
        uiScanStep = i_uiScanStep;
        uiReqScanPeriod = i_uiReqScanPeriod;

        if( i_pscanResult != NULL ) {
            stScanResult = *i_pscanResult;
        }

    }

} STR_SCANANAL_INFO;

/**
    @union UNI_MSG_DATA
    @brief 메시지 데이터 구조체
**/
union UNI_MSG_DATA {
    unsigned int uiData;
    time_t tiNow;
    __time32_t tiNow32;

    SELDELETE stDelete;
    SELLOST stLost;
    SEL_RESULT_DELETE_USERSCAN stResultDeleteUserScan;

    SELREQSCAN stReqScan;
    ENUM_AET_USER_SCAN_STAT enUserScanStat;

    STR_COLLECT_INFO strCollectInfo;
    STR_DETANAL_INFO strDetAnalInfo;
    STR_TRKANAL_INFO strTrkAnalInfo;
    STR_SCANANAL_INFO strScanAnalInfo;

    STR_LOG_INFO strLogInfo;

    SELUSERSCANRESULT stUserScanResult;

    char szData[32 * 2];

    STR_COLLECT_INFO *GetCollectInfo() { return &strCollectInfo; }
    STR_DETANAL_INFO *GetDetectAnalInfo() { return &strDetAnalInfo; }
    STR_TRKANAL_INFO *GetTrackAnalInfo() { return &strTrkAnalInfo; }
    STR_SCANANAL_INFO *GetScanAnalInfo() { return &strScanAnalInfo; }

};

// 로그 타입 사용자가 원하는 대로 정의
enum LogType {
    enDebug = 0,
    enNormal,
    enLineFeed,
    enNoLineFeed,

    enWarning,
    enError,
    enEnd,

    enNull
};
