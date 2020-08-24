/*
 * 본 문서는 제어조종장치와 재밍신호관치장치들간의 메시지를 정의합니다.
 * */


#ifndef _SYSMSG_H
#define _SYSMSG_H


// 기존 소나타 시스템 메시지 헤더 파일 로딩
#include "./SONATAPIP/_sysmsg.h"

#include "../Collect/DataFile/CRWRCommonVariables.h"

#pragma pack(push, 1)

struct STR_LAN_HEADER {
    unsigned char ucSrcDest;
    unsigned char ucOpCode;

    unsigned int uiLength;

} ;

//////////////////////////////////////////////////////////////
// 송신 메시지 정의

enum ENUM_MODE {
    enES_MODE=0,
    enEW_MODE,
    enREADY_MODE,

    enANAL_Mode
};


enum enREQ_MESSAGE {
    // 타겟 명령어 정의
    enREQ_URBIT = _START_OPCODE_OF_MESSAGE_,

    // 기존 SONATA 체계 명령어
    enREQ_MODE,         // Msys_SetMode,
    enREQ_ANAL_START,   // = Msys_Start,

    enREQ_IBIT,         // = Mbit_ReqIbit,
    enREQ_UBIT,         // = Mbit_ReqUbit,
    enREQ_CBIT,         // = Mbit_ReqCbit,


    // 디버깅 용
    enREQ_SIM_PDWDATA,  // PDW 데이터 모의
    enREQ_TEST1,
    enREQ_DUMP_LIST = 0xF0,

} ;

// 각각의 명령어에 대한 데이터 구조체 정의
struct STR_REQ_DUMP_LIST {
    UINT uiAddress;
    UINT uiDataSize;
    UINT uiDataLength;
};



//////////////////////////////////////////////////////////////
// 수신 메시지 정의

#define     DUMP_DATA_SIZE              (16*10)

enum enRES_MESSAGE {
    enRES_DUMP_LIST = enREQ_DUMP_LIST,

    // 기존 SONATA 체계 명령어
    enRES_MODE = enREQ_MODE,
    enRES_IBIT = enREQ_IBIT,
    enRES_UBIT = enREQ_UBIT,
    enRES_CBIT = enREQ_CBIT,


} ;

/**
 * @brief The STR_RES_DUMP_LIST struct
 */
struct STR_RES_DUMP_LIST {
    STR_REQ_DUMP_LIST strReqDumpList;

    char cData[500];
} ;

/**
 * @brief 랜 메시지 구조체
 */
union UNI_LAN_DATA {
    UINT uiResult;

    // 수신 메시지 구조체 정의
    STR_REQ_DUMP_LIST strReqDumpList;
    UINT uiUnit;

    // 송신 메시지 구조체 정의
    STR_RES_DUMP_LIST strResDumpList;

    // 기존 SONATA 체계 데이터 구조체 정의
    UINT uiMode;

    // 모의 데이터 및 장치 시험용
    //UDRCPDW strPDW[_MAX_COL_PDW];
    unsigned char szFile[_MAX_LANDATA];

};

#pragma pack(pop)

#endif // _SYSMSG_H



