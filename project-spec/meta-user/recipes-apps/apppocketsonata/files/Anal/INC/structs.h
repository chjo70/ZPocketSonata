/*!
  \file     Structs.h
  \brief    interface for the 구조체
	\version  0.0.1
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRUCTS_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_)
#define AFX_STRUCTS_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "system.h"
#include "defines.h"
#include "PDW.h"
#include "../SigAnal/_Define.h"

#include "PDW.h"

#ifdef _MIDAS_

#else
#include "../EmitterMerge/ELMsgDefn.h"
#include "AetIPL.h"
#endif




//////////////////////////////////////////////////////////////////////////
// 초기화 파일 구조체
struct STR_KEY {
	unsigned	 search : 1;
	unsigned		 hand : 1;
	unsigned		 open : 1;
	unsigned		  low : 1;
	unsigned			sep	: 1;
	unsigned			unk : 1;
    unsigned			: 26;

} ;

//union UNI_KEY {
//	STR_KEY x;
//	UINT word;
//
//} ;

//struct STR_INI_DATA {
	// 환경 정보
//	char serverIP[20];

	// 키 값
    //UNI_KEY key;
//
//} ;

//////////////////////////////////////////////////////////////////////////
//


// 채널 보정 데이터
struct STR_CHANNEL_COMPSATION {
	UINT from_address;
	UINT to_address;

	UINT count;
	UINT *pChannelCompensation;		// 최대 크기는 16MB 임. 하드웨어 팀과 협의해서 최대 크기를 결정해야 함.

} ;


// 초단수신기 메시지 구조체 
struct STR_HF_CHANNEL_ADDRESS {
	unsigned  address : 24;
	//unsigned  low   : 8;
	//unsigned  mid   : 8;
	//unsigned  hgh   : 8;
	unsigned   count  : 8;

} ;

struct STR_HF_TEMPERATURE {
	unsigned sign			   :  1;
	unsigned temperature : 10;
	unsigned             : 21;

} ;

// typedef struct {
// 	USHORT year;
// 	UCHAR mon;
// 	UCHAR mday;
// 	UCHAR hour;
// 	UCHAR min;
// } STR_HF_VERSION ;

// typedef union {
// 	UCHAR bit;
// 	USHORT wtemp;
// 	USHORT sw_coltrol_data;
// 	UINT full_addr;
// 	STR_HF_CHANNEL_ADDRESS caddr;
// 	STR_HF_TEMPERATURE temp;
// 	STR_HF_VERSION version;
// 
// 	UCHAR data[MAX_DATA_MESSAGE];
// 
// } UNI_HF_DATA ;

// typedef struct {
// 	UCHAR stx;
// 	UCHAR direction;
// 	UCHAR command;
// 	UCHAR size;
// 
// 	UNI_HF_DATA x;
// 
// 	UCHAR checksum;
// 	UCHAR etx;
// 
// } STR_HF_RECEIVER ;

// 초단수신기의 하드웨어 연동 상태
// typedef struct {
// 	UCHAR hf_recver[TOTAL_RECEIVER];
// 
// } STR_VH_RECIVER_CON_STAT ;


//////////////////////////////////////////////////////////////////////////
// 항공기접속판의 구조체 정의

// 자체점검 구조체
struct STR_LA_BIT {
    unsigned : 7;
	unsigned power_module : 1;		// 전원 모듈
    unsigned : 4;
    unsigned audio : 1;		// 오디오
    unsigned flare : 1;		// 플레어 연도
    unsigned chaff : 1;		// 채프 연동
    unsigned cpu_stat : 1;		// CPU 상태
    unsigned : 16;

}  ;

union UNI_LA_BIT {
	STR_LA_BIT x;
	UINT word;

}  ;

// 보드ID 구조체
struct STR_LA_BOARD_ID {
	UCHAR reserver1: 8;		// 펌웨어 정보
	UCHAR reserver2: 8;		// 제조일련번호
	USHORT id: 8;					// 보드ID: 0xA136

} ;

union UNI_LA_BOARD_ID {
	STR_LA_BOARD_ID x;
	UINT word;

} ;

// 오디오 설정 구조체 정의
struct STR_LA_AUDIO_CONFIG {
	unsigned									 : 13;
	unsigned					req_tone : 2;
	unsigned req_audio_control : 1;
	unsigned									 : 13;
	unsigned					set_tone : 2;
	unsigned set_audio_control : 1;

} ;

union UNI_LA_AUDIO_CONFIG {
	STR_LA_AUDIO_CONFIG x;
	UINT word;

}  ;

// Blanking Mask 설정
struct STR_LA_BLANK_MASK {
	unsigned						: 24;
	unsigned			 blk7 : 1;
	unsigned			 blk6 : 1;
	unsigned			 blk5 : 1;
	unsigned			 blk4 : 1;
	unsigned			 blk3 : 1;
	unsigned			 blk2 : 1;
	unsigned			 blk1 : 1;
	unsigned blk_on_off : 1;

}  ;

union UNI_LA_BLANK_MASK {
	STR_LA_BLANK_MASK x;
	UINT word;

}  ;

struct STR_LA_CMDS {
	unsigned chaff_error : 2;
	unsigned		arm_stat : 1;
	unsigned	power_stat : 1;
	unsigned	 stop_stat : 1;
	unsigned	 fire_stat : 1;
	unsigned flare_error : 2;
	unsigned						 : 5;
	unsigned		req_auto : 1;
	unsigned		req_semi : 1;
	unsigned	req_manual : 1;

	unsigned						 : 13;
	unsigned		set_auto : 1;
	unsigned		set_semi : 1;
	unsigned	set_manual : 1;

}  ;

union UNI_LA_CMDS {
	STR_LA_CMDS x;
	UINT word;

}  ;

// C/F 발사 정보 설정
struct STR_LA_CFINFO {
	unsigned						: 16;
	unsigned			 type : 4;
	unsigned start_flag : 2;
	unsigned			 time : 10;

}  ;

union UNI_LA_CFINFO {
	STR_LA_CFINFO x;
	UINT word;

}  ;

// C/F 발사 제어 요구
struct STR_LA_REQ_FIRE {
	unsigned					 : 22;
	unsigned stop_flag : 2;
	unsigned					 : 6;
	unsigned fire_ctrl : 2;

}  ;

union UNI_LA_REQ_FIRE {
	STR_LA_REQ_FIRE x;
	UINT word;

}  ;

struct STR_LA_CFREMAIN {
	unsigned				: 16;
	unsigned				: 1;
	unsigned _flare : 7;
	unsigned				: 1;
	unsigned _chaff : 7;

}  ;

union UNI_LA_CFREMAIN {
	STR_LA_CFREMAIN x;
	UINT word;

}  ;



//////////////////////////////////////////////////////////////////////////
// 펄스정보생성판의 구조체 정의
struct STR_PG_BOARD_ID {
	UCHAR reserver1 : 8;		// 펌웨어 정보
	UCHAR reserver2 : 8;		// 제조일련번호
	USHORT			 id : 8;					// 보드ID: 0xA137

}  ;

typedef union {
	STR_PG_BOARD_ID x;
	UINT word;

} UNI_PG_BOARD_ID ;


struct STR_PG_BIT {
	unsigned					: 11;		
	unsigned flash_mem: 1;		// 검출 결과
	unsigned sram     : 1;		// 발생 결과
	unsigned lo_6_3		: 1;		// 저장 결과
	unsigned lo_16		: 1;
	unsigned lo_12    : 1;		// 방위 정상
	unsigned board_id : 16;

}  ;

union UNI_PG_BIT {
	STR_PG_BIT x;
	UINT word;

}  ;

// 온도 설정값 구조체 정의
struct STR_PG_TEMPERATURE {
	unsigned			 : 3;
	unsigned temp4 : 5;		// 초단수신기4의 설정 온도.
	unsigned			 : 3;
	unsigned temp3 : 5;		// 초단수신기3의 설정 온도.
	unsigned			 : 3;
	unsigned temp2 : 5;		// 초단수신기2의 설정 온도.
	unsigned			 : 3;
	unsigned temp1 : 5;		// 초단수신기1의 설정 온도.

}  ;

union UNI_PG_TEMPERATURE {
	STR_PG_TEMPERATURE x;
	UINT word;

}  ;

// 임계값 구조체 정의
struct STR_PG_THRESHOLD {
	unsigned pa_threshold			 : 8;			// PA 수신 임계값
	unsigned cw_chopping_count : 8;			// CW Chopping Count
	unsigned fmop_threshold		 : 6;			// FMOP 임계값
	unsigned cw_pulsewidth		 : 10;		// CW 판정 펄스폭

}  ;

union UNI_PG_THRESHOLD {
	STR_PG_THRESHOLD x;
	UINT word;

} ;

// 필터 정보 구조체
struct STR_PG_FILTER_FUNCTION {
	unsigned								: 16;
	unsigned filter1_pass		: 1;
	unsigned filter1_reject : 1;
	unsigned filter2_pass		: 1;
	unsigned filter2_reject : 1;
	unsigned filter3_pass		: 1;
	unsigned filter3_reject : 1;
	unsigned filter4_pass		: 1;
	unsigned filter4_reject : 1;
	unsigned filter5_pass		: 1;
	unsigned filter5_reject : 1;
	unsigned filter6_pass		: 1;
	unsigned filter6_reject : 1;
	unsigned filter7_pass		: 1;
	unsigned filter7_reject : 1;
	unsigned filter8_pass		: 1;
	unsigned filter8_reject : 1;

}  ;

// 신호형태 변수 설정 구조체
struct STR_PG_FILTER_SIGTYPE {
	unsigned noFilter : 3;
	unsigned				  : 25;
	unsigned sigType  : 4;

}  ;

// 주파수 변수 설정 구조체
union UNI_PG_FILTER_FREQ_RANGE {
	UINT word;
	struct {
		unsigned noFilter : 3;
		unsigned					: 1;
		unsigned hgh			: 12;
		unsigned					: 4;
		unsigned low			: 12;
	} x ;

}  ;

// 방위각 변수 설정 구조체
union STR_PG_FILTER_AOA_RANGE {
	UINT word;
	struct {
		unsigned noFilter : 3;
		unsigned					: 4;
		unsigned hgh			: 9;
		unsigned dv				: 1;
		unsigned					: 6;
		unsigned low			: 9;
	} x ;

}  ;

// 펄스폭 변수 설정 구조체
union STR_PG_FILTER_PULSEWIDTH_RANGE {
	UINT word;
	struct {
		unsigned noFilter : 3;
		unsigned hgh			: 13;
		unsigned					: 3;
		unsigned low			: 13;
	} x ;

}  ;

// 신호세기 변수 설정 구조체
union STR_PG_FILTER_SA_RANGE {
	UINT word;
	struct {
		unsigned noFilter : 3;
		unsigned					: 5;
		unsigned hgh			: 8;
		unsigned					: 8;
		unsigned low			: 8;
	} x ;

} ;

// 수집 개수 설정
typedef union {
	UINT word;
	struct {
		unsigned					 : 14;
		unsigned coCollect : 18;		// 수집 개수
	} x ;

} STR_PG_COLLECT_COUNT;

// 펄스정보생성판의 필처 정보 설정 구조체
struct STR_PG_FILTER_INFO {
	STR_PG_FILTER_FUNCTION ff;
	STR_PG_FILTER_SIGTYPE fs;
	UNI_PG_FILTER_FREQ_RANGE ffr;
	STR_PG_FILTER_AOA_RANGE far_;						// 필터 방위영역 설정
	STR_PG_FILTER_PULSEWIDTH_RANGE fpr;			// 필터 펄스폭 설정
	STR_PG_FILTER_SA_RANGE fsr;							// 필터 신호세기 설정
	STR_PG_COLLECT_COUNT cc;								// 수집 개수 설정
	UINT ct;																// 수집 시간 설정

}  ;


union UNI_PG_COUNT_COLLECT_STOP {
	unsigned word;
	struct {
		unsigned count_high : 10;		// 수집 완료/중지했을 때의 상위 수집 개수
		unsigned						: 4;
		unsigned bank				: 2;		// 뱅크 번호, 0x1은 뱅크1이며 0x2는 뱅크2이다.
		unsigned count_low  : 8;		// 수집 완료/중지했을 때의 하위 수집 개수
		unsigned						: 8;
	} x ;

}  ;

union UNI_PG_LO_STAT {
	UINT word;
	struct {
		unsigned				: 29;
		unsigned lo_6_3 : 1;
		unsigned	lo_16 : 1;
		unsigned	lo_12 : 1;
	} x ;

} ;


//////////////////////////////////////////////////////////////////////////
// 채널 방탐 보정 관련 구조체 정의

// 임계값 구조체 정의
struct STR_PGC_THRESHOLD {
	unsigned pa_threshold			 : 8;			// PA 수신 임계값
	unsigned									 : 24;

} ;

union UNI_PGC_THRESHOLD {
	STR_PGC_THRESHOLD x;
	UINT word;

} ;


// 임계값 구조체 정의
struct STR_PGC_ADDRESS {
	unsigned						 : 10;
	unsigned		 channel : 2;
	unsigned temperature : 5;
	unsigned	 frequency : 9;
	unsigned					pa : 6;

} ;

union UNI_PGC_ADDRESS {
	STR_PGC_ADDRESS x;
	UINT word;

} ;


// PDW 구조체
// PDW 구조체는 _pdw.h 파일에 있음


//////////////////////////////////////////////////////////////////////////
// 그래픽처리판의 구조체 정의

// 자체점검 구조체
struct STR_GP_BIT {
	unsigned				 : 13;
	unsigned control : 1;		// 제어기 상태
	unsigned display : 1;		// 시현기 상태
	unsigned		 cpu : 1;		// CPU 상태
	unsigned				 : 16;
} ;

union UNI_GP_BIT {
	STR_GP_BIT x;
	UINT word;

} ;

// 보드ID 구조체
struct STR_GP_BOARD_ID {
	unsigned reserver1: 8;		// 펌웨어 정보
	unsigned reserver2: 8;		// 제조일련번호
	unsigned id : 16;					// 보드ID: 0xA138

} ;

union UNI_GP_BOARD_ID {
	STR_GP_BOARD_ID x;
	UINT word;

}  ;

struct STR_GP_STAT {
	unsigned								: 16;
	unsigned fault_category : 2;
	unsigned								: 2;
	unsigned		 udf_number : 4;
	unsigned			cmds_mode : 2;
	unsigned								: 1;
	unsigned			log_onoff : 1;
	unsigned								: 3;
	unsigned			disp_mode : 1;

} ;

union UNI_GP_STAT {
	STR_GP_STAT x;
	USHORT byte16[2];
	UINT word;

}  ;

// 제어기 버튼 1 - 버튼에 글짜가 보이는 것.
// 아래 구조체는 제어기의 램프를 표시하기 위한 구조체 입니다.
// #ifdef _CONTROL1_
// typedef struct {
// 	unsigned					: 7;
// 	unsigned			 ml : 1;
// 	unsigned			    : 1;
// 	unsigned		  pfm : 1;
// 	unsigned					: 1;
// 	unsigned separate : 1;
// 	unsigned					: 1;
// 	unsigned	unknown : 1;
// 	unsigned					: 1;
// 	unsigned		 high : 1;
// 
// 	unsigned					: 7;
// 	unsigned	 manual : 1;
// 	unsigned			    : 1;
// 	unsigned		fault	: 1;
// 	unsigned					: 1;
// 	unsigned				  : 1;
// 	unsigned				  : 1;
// 	unsigned		 open : 1;
// 	unsigned					: 2;
// 
// } STR_CTRL_LAMPINFO ;
// 
// #elif defined( _CONTROL2_ )
// typedef struct {
// 	unsigned					: 7;
// 	unsigned			 ml : 1;
// 	unsigned					: 1;
// 	unsigned	 manual : 1;
// 	unsigned			cfd : 1;
// 	unsigned		falut : 1;
// 	unsigned			bit : 1;
// 	unsigned priority : 1;
// 	unsigned		 open : 1;
// 	unsigned					: 7;
// 	unsigned			er2 : 1;
// 	unsigned		  low : 1;
// 	unsigned			alt : 1;
// 	unsigned					: 1;
// 	unsigned			er1 : 1;
// 	unsigned					: 1;
// 	unsigned			unk : 1;
// 	unsigned					: 5;
// 
// } STR_CTRL_LAMPINFO ;
// 
// #else
// #pragma message( "제어기 버젼을 정의해야 합니다." )
// 
// #endif

// 수집한 PDW의 제원 정보 구조체 정의
struct STR_ONE_PDW {
	UINT toa;
	int freq;
	int pw;
	UINT bt;
	UINT stat;			// status
	UINT mc;				// 최대 채널
	UINT dv;
	int aoa;
	int pa;
	UINT band;

} ;

#ifndef _ENUM_BANDWIDTH_
#define _ENUM_BANDWIDTH_
typedef enum {
	en5MHZ_BW=0,
	en50MHZ_BW,

} ENUM_BANDWIDTH ;
#endif


struct STR_CW_CONTROL {
	int cw_threshold;
	int cw_init_threshold;
	int noEMT;
	BOOL bCWCtrl;

} ;


// 탐지용 PDW 수집 구조체 정의
typedef STR_PDWDATA STR_NEW_COLLECT_PDW;

// 추적용 PDW 수집 구조체 정의
typedef STR_PDWDATA STR_KWN_COLLECT_PDW;

// 스캔용 PDW 수집 구조체 정의
typedef STR_PDWDATA STR_SCN_COLLECT_PDW;


struct STR_NEW_COLLECT_BANK {
	UINT nBank;
	enum FILTER_STAT nStat[NEW_NO_BANK];

} ;

//////////////////////////////////////////////////////////////////////////
// 에미터 식별 구조체

typedef unsigned int UDFINDEX;

//////////////////////////////////////////////////////////////////////////
// 시스템 로그 관련 구조체 정의
#define LOG_HEADER						(sizeof(time_t)+2*sizeof(UINT))
#define MAX_LOG_PDW						400

// 에미터 상세정보 구조체 정의
// struct STR_AET_DETAIL {
// 	STR_NEWAET aet;
// 	_PDW pdw[MAX_LOG_PDW];
// 
// } ;

// 시스템 로그 구조체 정의
struct STR_LOGMSG {
	UINT opCode;
	UINT dSize;

	time_t log_time;
	
	union {
		char byte;
		char array[MAX_LOG_PDW];
		unsigned int word;
		unsigned int noThreat;
		//STR_THREAT threat;
		//STR_AET_DETAIL aetDet;

		//STR_POWER_ON_INIT init;
		//STR_POWER_ON_IBIT ibit;
		//STR_POWER_ON_PBIT pbit;
		//STR_POWER_ON_CBIT cbit;
	} u ;

} ;


//////////////////////////////////////////////////////////////////////////
// 기본적인 큐 메시지 구조체 
struct STR_QUEUE_MESSAGE {
	USHORT opCode;
	UCHAR address1;
	UCHAR address2;
	UINT opData;

} ;

//PC와 랜 통신을 위한 큐 메시지 구조체 
// struct STR_QUEUE_AET_MESSAGE {
// 	USHORT opCode;
// 	UCHAR address1;
// 	UCHAR address2;
// 	UINT opData;
// 
// 	SRxLOBData stLOB;
// } ;

// 시스템 로그 관련 큐 메시지 구조체 
struct STR_QUEUE_LOG_MESSAGE {
	USHORT opCode;
	UCHAR address1;
	UCHAR address2;
	UINT opData;

	STR_LOGMSG log;
} ;


//////////////////////////////////////////////////////////////////////////
// Chaff/Flare 발사 명령 정의

// Chaff 발사 정보
struct STR_CHAFF_FLARE_ORDER {
	USHORT startDelay;					// res. ms
	USHORT endDelay;
	USHORT payloadCount;
	USHORT payloadInterval;
	USHORT burstCount;
	USHORT burstInterval;
	USHORT salvoCount;
	USHORT salvoInterval;

} ;

// C/F 발사 정보 순서를 만들기 위한 구조체 정의
struct STR_FIRE_INFO {
	UINT fire_time;
	UINT chaff_flare;

} ;

//////////////////////////////////////////////////////////////////////////
// 로그 데이터 구조체

// 로그 데이터 구조체
struct STR_SYSTEMLOG {
	unsigned long size;
	unsigned char *pLogBuffer;

}  ;





#endif // !defined(AFX_STRUCTS_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_)

