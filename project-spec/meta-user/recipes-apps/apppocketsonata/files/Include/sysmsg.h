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
    //unsigned char ucSrcDest;
    //unsigned char ucOpCode;

    unsigned int uiOpCode;
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
    enREQ_MODE = Msys_SetMode,
    enREQ_ANAL_START = Msys_Start,

    enREQ_IBIT = Mbit_ReqIbit,
    enREQ_UBIT = Mbit_ReqUbit,
    enREQ_CBIT = Mbit_ReqCbit,
    enREQ_SBIT = Mbit_StartSbit_V3,

    enREQ_RELOAD_LIBRARY,


    // 디버깅 용
    enREQ_SIM_PDWDATA,  // PDW 데이터 모의
    enREQ_TEST1,
    enREQ_DUMP_LIST = 0xF0,

} ;

// 각각의 명령어에 대한 데이터 구조체 정의
struct STR_REQ_DUMP_LIST {
    unsigned int uiAddress;
    unsigned int uiDataSize;
    unsigned int uiDataLength;
};



//////////////////////////////////////////////////////////////
// 수신 메시지 정의

#define     DUMP_DATA_SIZE              (16*10)

enum enRES_MESSAGE {
    enRES_DUMP_LIST = enREQ_DUMP_LIST,

    // 기존 SONATA 체계 명령어
    enRES_MODE = enREQ_MODE,

    enRES_IBIT = Mbit_ResultEsIbit,
    enRES_UBIT = Mbit_ResultEsUbit,
    enRES_CBIT = Mbit_ResultEsCbit,
    enRES_SBIT = Mbit_ResultEsSbit,

    esAET_NEW_CCU = Maet_New_Ccu,
    esAET_UPD_CCU = Maet_Update_Ccu,
    esAET_LST_CCU = Maet_Lost_Ccu,
    esAET_DEL_CCU = Maet_Delete_Ccu,


} ;

union UNI_ES_IBIT {
    unsigned int w32;

    struct {
      unsigned int : 21;

      unsigned int b3Comu : 1;  // Band 3 communication bit
      unsigned int b2Comu : 1;  // Band 2 communication bit
      unsigned int b1Comu : 1;  // Band 1 communication bit

      unsigned int bRsa : 1;		// RSA General Set IBIT
      unsigned int b3Sp : 1;		// Each Unit IBIT
      unsigned int b2Sp : 1;
      unsigned int b1Sp : 1;

      unsigned int bTsd : 1;
      unsigned int bSdfu : 1;
      unsigned int bPdfu : 1;
      unsigned int bOru : 1;
    } x ;

} ;

union UNI_RXDF_CBIT {
  unsigned int w32;

  struct {
    unsigned int : 26;

    unsigned int bSpin : 1;
    unsigned int bSpout : 1;

    unsigned int bSdfuTp : 1; // SDFU Temperature
    unsigned int bPdfuTp : 1;
    unsigned int bOruSw : 1;  // Oru Switch
    unsigned int bOruTp : 1;  // Oru Temperature
  } x ;
}  ;

union UNI_RSA_CBIT {
  unsigned int w32;
  struct {
    unsigned int : 15;    /* bit22-31 Reserved */

    unsigned int bCip : 1;    /* bit0  제어식별프로세서판 */

    unsigned int bSap : 1;    /* bit3  스캔프로세서판 */
    unsigned int bNsp : 1;    /* bit8  탐지프로세서판 */
    unsigned int bKsp1 : 1;    /* bit11 추적프로세서판1 */
    unsigned int bKsp2 : 1;    /* bit14 추적프로세서판2 */

    unsigned int bKsp3 : 1;    /* bit17 추적프로세서판3 */
    unsigned int bKsp4 : 1;    /* bit20 추적프로세서판4 */
    unsigned int bSaf : 1;    /* bit5  스캔분석필터판 */
    unsigned int bNsf : 1;    /* bit10 탐지필터판 */

    unsigned int bKsf1 : 1;    /* bit13 추적필터판1 */
    unsigned int bKsf2 : 1;    /* bit16 추적필터판2 */
    unsigned int bKsf3 : 1;    /* bit19 추적필터판3 */
    unsigned int bKsf4 : 1;    /* bit22 추적필터판4 */

    unsigned int bAud : 1;    /* bit6  오디오발생판 */
    unsigned int bRcv : 1;    /* bit7  PDW 수신판 */
    unsigned int bPdw : 1;    /* bit2  공용메모리판 */
    unsigned int bCmm : 1;    /* bit2  공용메모리판 */
  } x ;
}  ;

struct STR_ES_CBIT {
    UNI_RXDF_CBIT sp[ 3 ];
    UNI_RSA_CBIT rsa;
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

    UNI_ES_IBIT stESIBit;

    // 모의 데이터 및 장치 시험용
    unsigned char szFile[_MAX_LANDATA];

};

#pragma pack(pop)

#endif // _SYSMSG_H



