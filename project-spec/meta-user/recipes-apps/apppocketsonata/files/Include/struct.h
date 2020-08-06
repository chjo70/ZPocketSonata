/*
 * 본 문서는 장치들간의 내부 메시지를 정의합니다. 메시지들간의 정의와 데이터를 나타냅니다.
 * */


#ifndef _STRUCT_H
#define _STRUCT_H

//#include "defines.h"
//#include "system.h"

/**
 * @brief ZYNQ 보드의 번호를 정의함.
 */
enum ENUM_BoardID {
    enPRC_Unknown,
    enPRC1=1,
    enPRC2,
    enPRC3,
    enPRC4,
    enPRC5,

    enPRC6,

    enMaster=enPRC3

};

enum ENUM_COLLECT_MODE {
    enUnused=0,

    enCollecting,
    enCompleteCollection,
    enAnalysing,
};

/////////////////////////////////////////////////////////////////////////////////
// 아래는 변수 관련 구조체 내용 입니다.

/**
 * @brief ZYNQ 보드 마다 시스템 설정값 정보 영역이다.
 */
struct STR_CONFIG_VAR {
    ENUM_BoardID enBoardID;        // 보드 ID

} ;

/**
 * @brief 시스템 공용 변수 중에서 ZYNQ 보드의 자체 영역 입니다. ZYNQ 보드 마다 아래 영역은 다른 값을 가질 수 있습니다.
 */
struct STR_SYSTEMVAR_BODY {

} ;


/////////////////////////////////////////////////////////////////////////////////

enum ENUM_SocketMode {
    enServerZYNQ=0,
    enServerCCU,
    enServerPMC,

};

/**
 * @brief 최소/최대 값 구조체 정의
 */
struct STR_LOWHIGH {
    UINT uiLow;
    UINT uiHigh;
};

/**
 * @brief 윈도우 셀 구조체 정의
 */
struct STR_WINDOWCELL {
    /**
     * @brief 사용 여부 플레그 를 의미한다.
     */
    bool bUse;

    unsigned int uiMode;

    /**
     * @brief 채널 정보를 나타낸다. 유일한 채널이다.
     */
    int iChannelNo;

    /**
     * @brief 수집 완료 상태를 나타낸다.
     */
    ENUM_COLLECT_MODE enCollectMode;

    /**
     * @brief 저장된 PDW 개수
     */
    unsigned int uiTotalPDW;

    /**
    * @brief 최대 수집 게수
    */
    unsigned int uiMaxCoPDW;
    unsigned int uiMaxCollectTime;          // 최대 수집 시간 [ms]

    STR_LOWHIGH strAoa;
    STR_LOWHIGH strFreq;
    STR_LOWHIGH strPA;
    STR_LOWHIGH strPW;

    /**
     * @brief 빔 번호
     */
    unsigned int uiBeam;

    /**
     * @brief 누적 PDW 개수
     */
    unsigned int uiAccumulatedCoPDW;

    /**
     * @brief 누적 시간 [ms]
     */
    unsigned int uiAccumulatedTime;

    /**
     * @brief 누적 사용 채널 횟수
     */
    unsigned int uiAccumulatedCoUsed;

};

struct STR_ARRAY_PDW {
    unsigned int uiTotalPDW;

    unsigned int uiSigType[_MAX_COL_PDW];
    unsigned int uiAOA[_MAX_COL_PDW];
    unsigned int uiFreq[_MAX_COL_PDW];
    unsigned int uiPW[_MAX_COL_PDW];
    unsigned int uiPA[_MAX_COL_PDW];

    _TOA llToa[_MAX_COL_PDW];

};

// 수집 뱅크 종류 정의
enum ENUM_COLLECTBANK {
    enDetectCollectBank=0,
    enTrackCollectBank,
    enScanCollectBank,
    enUserCollectBank

};


#endif // _STRUCT_H
