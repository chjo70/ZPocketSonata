/*
 * 본 문서는 제어조종장치와 재밍신호관치장치들간의 메시지를 정의합니다.
 * */


#ifndef _SYSMSG_H
#define _SYSMSG_H

// 기존 소나타 시스템 메시지 헤더 파일 로딩
#include "./SONATAPIP/_sysmsg.h"
#include "./SONATAPIP/ShuICD.h"

#include "../Anal/INC/AetIPL.h"

#include "../Anal/Collect/DataFile/CRWRCommonVariables.h"

#if TOOL==diab 
#pragma pack( 1 )
#else
#pragma pack( push, 1 )
#endif


struct STR_LAN_HEADER {
    unsigned int uiOpCode;
    unsigned int uiLength;

} ;

//////////////////////////////////////////////////////////////
// 송신 메시지 정의

enum ENUM_MODE {
    enES_MODE=1,
    enEW_MODE,
    enREADY_MODE,

    enANAL_Mode=0x80,

    enANAL_ES_MODE=enANAL_Mode | enES_MODE,
    enANAL_EW_MODE=enANAL_Mode | enEW_MODE,


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

    enREQ_IPL_VERSION = Mipl_ReqVersion,
    enREQ_IPL_START = Mipl_Start,
    enREQ_IPL_DOWNLOAD = Mipl_Download,
    enREQ_IPL_END = Mipl_End,
    enREQ_RELOAD_LIBRARY,

    // 오디오 설정 메시지
    enREQ_AUDIO = Mcnf_Audio,
    enREQ_AUDIO_PARAM = Mcnf_AudioParam,

    // 수신기 설정 메시지
    enREQ_Band_Enable = Mcnf_BandEnable,
    enREQ_FMOP_Threshold = Mcnf_FmopThreshold,
    enREQ_PMOP_Threshold = Mcnf_PMOPThreshold,
    enREQ_RX_Threshold = Mcnf_RxThreshold,

    // 신호 수집 제어
    enREQ_INIT = REQ_INIT,
    enREQ_SET_CONFIG = REQ_SET_CONFIG,
    enREQ_STOP = REQ_STOP,
    enREQ_COL_START = REQ_COL_START,
    enREQ_COL_END = REQ_STOP,
    enREQ_RAWDATA = REQ_RAWDATA,

    // 시스템 변수
    enREQ_SYS=Mcnf_ReqSys,


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
    enRES_MODE = Esys_SetMode,

    enRES_IBIT = Mbit_ResultEsIbit,
    enRES_UBIT = Mbit_ResultEsUbit,
    enRES_CBIT = Mbit_ResultEsCbit,
    enRES_SBIT = Mbit_ResultEsSbit,

    enAET_NEW_CCU = Maet_New_Ccu,
    enAET_UPD_CCU = Maet_Update_Ccu,
    enAET_LST_CCU = Maet_Lost_Ccu,
    enAET_DEL_CCU = Maet_Delete_Ccu,

    enIPL_VERSION = Mipl_Version,
    enIPL_WRITESTATUS = Mipl_WriteStatus,

    enRES_SETSYS = Ecnf_SetSys,

    esRES_SETCONFIG = Mres_SetConfig,
    enRES_COLSTART = Mres_ColStart,
    enRES_RAWDATA = Mres_RawData_ZPDW,

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

struct STR_IPL_VERSION {
    unsigned int uiIPLVersion;
    unsigned int uiStatus;
};

struct STR_IPL_START {
    unsigned int uiIPLVersion;
    unsigned int uiCountOfIPL;
};


/**
 * @brief The STR_RES_DUMP_LIST struct
 */
struct STR_RES_DUMP_LIST {
    STR_REQ_DUMP_LIST strReqDumpList;

    char cData[500];
} ;

struct STR_AUDIO_PARAM {
    int iLowerBC;    // 1:Band1, 2:Band2, 3:Band3
    int iUpperBC;    // 1:Band1, 2:Band2, 3:Band3
    int iLowerFrq;
    int iUpperFrq;
    int iFromAoa;
    int iToAoa;
    int	iFromPa;
    int	iToPa;

} ;

struct STR_BAND_ENABLE {
    int iBand;
    int iOnOff;
};

struct STR_FMOP_THRESHOLD {
    int iBand;
    int iThreshold;
};

struct STR_RX_THRESHOLD {
    int iBand;
    int iThreshold;
    //unsigned int uiCorThreshold;
};

typedef struct STR_FMOP_THRESHOLD STR_PMOP_THRESHOLD;


#ifndef _GRAPH_

/**
 * @brief 랜 메시지 구조체
 */
union UNI_LAN_DATA {
    bool bAudioSW;
    unsigned int uiResult;

    // 수신 메시지 구조체 정의
    STR_REQ_DUMP_LIST strReqDumpList;
    unsigned int uiUnit;

    // 송신 메시지 구조체 정의
    STR_RES_DUMP_LIST strResDumpList;

    // 기존 SONATA 체계 데이터 구조체 정의
    unsigned int uiMode;

    // 자체점검
    UNI_ES_IBIT strESIBit;
    UNI_RSA_CBIT strRSACBit;

    // 오디오
    STR_AUDIO_PARAM strAudioParam;

    // CEDEOB
    STR_IPL_START strIPLStart;
    STR_IPL strIPL;

    // 수신기 설정
    STR_BAND_ENABLE strBandEnable;
    STR_FMOP_THRESHOLD strFMOPThreshold;
    STR_PMOP_THRESHOLD strPMOPThreshold;

    // 수집 제어 관련 메시지
    STR_REQ_SETMODE_RSA strReqSetMode;

    // 모의 데이터 및 장치 시험용
    unsigned char szFile[_MAX_LANDATA];
    SRxLOBData stLOBData[_MAX_LOBDATA];

};

#endif

#if TOOL==diab 
#pragma pack( 4 )
#else
#pragma pack( pop )
#endif


#endif // _SYSMSG_H



