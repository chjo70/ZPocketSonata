/*
 * 본 문서는 장치들간의 내부 메시지를 정의합니다. 메시지들간의 정의와 데이터를 나타냅니다.
 * */


#ifndef _STRUCT_H
#define _STRUCT_H

#include "defines.h"
#include "system.h"

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

    UINT uiMode;

    /**
     * @brief 채널 정보를 나타낸다. 유일한 채널이다.
     */
    int iChannelNo;

    /**
     * @brief 수집 완료 상태를 나타낸다.
     */
    bool bComplete;

    /**
    * @brief 최대 수집 게수
    */
    UINT uiMaxCoPDW;
    UINT uiMaxCollectTime;          // 최대 수집 시간 [ms]

    STR_LOWHIGH strAoa;
    STR_LOWHIGH strFreq;
    STR_LOWHIGH strPA;
    STR_LOWHIGH strPW;

    /**
     * @brief 빔 번호
     */
    UINT uiBeam;

    /**
     * @brief 누적 PDW 개수
     */
    UINT uiAccumulatedCoPDW;

    /**
     * @brief 누적 시간 [ms]
     */
    UINT uiAccumulatedTime;

    /**
     * @brief 채널 사용 횟수
     */
    UINT uiAccumulatedCoUse;

};

struct STR_PDW {
    UINT uiCoPDW;

    UINT uiSigType[MAX_PDW];
    UINT uiAOA[MAX_PDW];
    UINT uiFreq[MAX_PDW];
    UINT uiPW[MAX_PDW];
    UINT uiPA[MAX_PDW];

};

// 수집 뱅크 종류 정의
enum ENUM_COLLECTBANK {
    enDetectCollectBank=0,
    enTrackCollectBank,
    enScanCollectBank,
    enUserCollectBank

};


#endif // _STRUCT_H
