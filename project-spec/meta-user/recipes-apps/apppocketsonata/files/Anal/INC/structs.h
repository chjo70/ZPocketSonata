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

#include "System.h"
#include "../SigAnal/_Define.h"
#include "../EmitterMerge/ELMsgDefn.h"

#include "_pdw.h"
#include "_aetipl.h"

//////////////////////////////////////////////////////////////////////////
// 초기화 파일 구조체
typedef struct {
	unsigned	 search : 1;
	unsigned		 hand : 1;
	unsigned		 open : 1;
	unsigned		  low : 1;
	unsigned			sep	: 1;
	unsigned			unk : 1;
	unsigned					: 26;

} STR_KEY ;

typedef union {
	STR_KEY x;
	UINT word;

} UNI_KEY ;

typedef struct {
	// 환경 정보
	char serverIP[20];

	// 키 값
	UNI_KEY key;

} STR_INI_DATA ;

//////////////////////////////////////////////////////////////////////////
//


// 채널 보정 데이터
typedef struct {
	UINT from_address;
	UINT to_address;

	UINT count;
	UINT *pChannelCompensation;		// 최대 크기는 16MB 임. 하드웨어 팀과 협의해서 최대 크기를 결정해야 함.

} STR_CHANNEL_COMPSATION ;


// 초단수신기 메시지 구조체 
typedef struct {
	unsigned  address : 24;
	//unsigned  low   : 8;
	//unsigned  mid   : 8;
	//unsigned  hgh   : 8;
	unsigned   count  : 8;

} STR_HF_CHANNEL_ADDRESS ;

typedef struct {
	unsigned sign			   :  1;
	unsigned temperature : 10;
	unsigned             : 21;

} STR_HF_TEMPERATURE ;

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
typedef struct {
	unsigned							: 7;	
	unsigned power_module : 1;		// 전원 모듈
	unsigned							: 4;
	unsigned				audio : 1;		// 오디오
	unsigned				flare : 1;		// 플레어 연도
	unsigned				chaff : 1;		// 채프 연동
	unsigned		 cpu_stat : 1;		// CPU 상태
	unsigned							: 16;

} STR_LA_BIT ;

typedef union {
	STR_LA_BIT x;
	UINT word;

} UNI_LA_BIT ;

// 보드ID 구조체
typedef struct {
	UCHAR reserver1: 8;		// 펌웨어 정보
	UCHAR reserver2: 8;		// 제조일련번호
	USHORT id: 8;					// 보드ID: 0xA136

} STR_LA_BOARD_ID ;

typedef union {
	STR_LA_BOARD_ID x;
	UINT word;

} UNI_LA_BOARD_ID ;

// 오디오 설정 구조체 정의
typedef struct {
	unsigned									 : 13;
	unsigned					req_tone : 2;
	unsigned req_audio_control : 1;
	unsigned									 : 13;
	unsigned					set_tone : 2;
	unsigned set_audio_control : 1;

} STR_LA_AUDIO_CONFIG ;

typedef union {
	STR_LA_AUDIO_CONFIG x;
	UINT word;

} UNI_LA_AUDIO_CONFIG ;

// Blanking Mask 설정
typedef struct {
	unsigned						: 24;
	unsigned			 blk7 : 1;
	unsigned			 blk6 : 1;
	unsigned			 blk5 : 1;
	unsigned			 blk4 : 1;
	unsigned			 blk3 : 1;
	unsigned			 blk2 : 1;
	unsigned			 blk1 : 1;
	unsigned blk_on_off : 1;

} STR_LA_BLANK_MASK ;

typedef union {
	STR_LA_BLANK_MASK x;
	UINT word;

} UNI_LA_BLANK_MASK ;

typedef struct {
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

} STR_LA_CMDS ;

typedef union {
	STR_LA_CMDS x;
	UINT word;

} UNI_LA_CMDS ;

// C/F 발사 정보 설정
typedef struct {
	unsigned						: 16;
	unsigned			 type : 4;
	unsigned start_flag : 2;
	unsigned			 time : 10;

} STR_LA_CFINFO ;

typedef union {
	STR_LA_CFINFO x;
	UINT word;

} UNI_LA_CFINFO ;

// C/F 발사 제어 요구
typedef struct {
	unsigned					 : 22;
	unsigned stop_flag : 2;
	unsigned					 : 6;
	unsigned fire_ctrl : 2;

} STR_LA_REQ_FIRE ;

typedef union {
	STR_LA_REQ_FIRE x;
	UINT word;

} UNI_LA_REQ_FIRE ;

typedef struct {
	unsigned				: 16;
	unsigned				: 1;
	unsigned _flare : 7;
	unsigned				: 1;
	unsigned _chaff : 7;

} STR_LA_CFREMAIN ;

typedef union {
	STR_LA_CFREMAIN x;
	UINT word;

} UNI_LA_CFREMAIN ;



//////////////////////////////////////////////////////////////////////////
// 펄스정보생성판의 구조체 정의
typedef struct {
	UCHAR reserver1 : 8;		// 펌웨어 정보
	UCHAR reserver2 : 8;		// 제조일련번호
	USHORT			 id : 8;					// 보드ID: 0xA137

} STR_PG_BOARD_ID ;

typedef union {
	STR_PG_BOARD_ID x;
	UINT word;

} UNI_PG_BOARD_ID ;


typedef struct {
	unsigned					: 11;		
	unsigned flash_mem: 1;		// 검출 결과
	unsigned sram     : 1;		// 발생 결과
	unsigned lo_6_3		: 1;		// 저장 결과
	unsigned lo_16		: 1;
	unsigned lo_12    : 1;		// 방위 정상
	unsigned board_id : 16;

} STR_PG_BIT ;

typedef union {
	STR_PG_BIT x;
	UINT word;

} UNI_PG_BIT ;

// 온도 설정값 구조체 정의
typedef struct {
	unsigned			 : 3;
	unsigned temp4 : 5;		// 초단수신기4의 설정 온도.
	unsigned			 : 3;
	unsigned temp3 : 5;		// 초단수신기3의 설정 온도.
	unsigned			 : 3;
	unsigned temp2 : 5;		// 초단수신기2의 설정 온도.
	unsigned			 : 3;
	unsigned temp1 : 5;		// 초단수신기1의 설정 온도.

} STR_PG_TEMPERATURE ;

typedef union {
	STR_PG_TEMPERATURE x;
	UINT word;

} UNI_PG_TEMPERATURE ;

// 임계값 구조체 정의
typedef struct {
	unsigned pa_threshold			 : 8;			// PA 수신 임계값
	unsigned cw_chopping_count : 8;			// CW Chopping Count
	unsigned fmop_threshold		 : 6;			// FMOP 임계값
	unsigned cw_pulsewidth		 : 10;		// CW 판정 펄스폭

} STR_PG_THRESHOLD ;

typedef union {
	STR_PG_THRESHOLD x;
	UINT word;

} UNI_PG_THRESHOLD ;

// 필터 정보 구조체
typedef struct { 
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

} STR_PG_FILTER_FUNCTION ;

// 신호형태 변수 설정 구조체
typedef struct {
	unsigned noFilter : 3;
	unsigned				  : 25;
	unsigned sigType  : 4;

} STR_PG_FILTER_SIGTYPE ;

// 주파수 변수 설정 구조체
typedef union {
	UINT word;
	struct {
		unsigned noFilter : 3;
		unsigned					: 1;
		unsigned hgh			: 12;
		unsigned					: 4;
		unsigned low			: 12;
	} x ;

} UNI_PG_FILTER_FREQ_RANGE ;

// 방위각 변수 설정 구조체
typedef union {
	UINT word;
	struct {
		unsigned noFilter : 3;
		unsigned					: 4;
		unsigned hgh			: 9;
		unsigned dv				: 1;
		unsigned					: 6;
		unsigned low			: 9;
	} x ;

} STR_PG_FILTER_AOA_RANGE ;

// 펄스폭 변수 설정 구조체
typedef union {
	UINT word;
	struct {
		unsigned noFilter : 3;
		unsigned hgh			: 13;
		unsigned					: 3;
		unsigned low			: 13;
	} x ;

} STR_PG_FILTER_PULSEWIDTH_RANGE ;

// 신호세기 변수 설정 구조체
typedef union {
	UINT word;
	struct {
		unsigned noFilter : 3;
		unsigned					: 5;
		unsigned hgh			: 8;
		unsigned					: 8;
		unsigned low			: 8;
	} x ;

} STR_PG_FILTER_SA_RANGE;

// 수집 개수 설정
typedef union {
	UINT word;
	struct {
		unsigned					 : 14;
		unsigned coCollect : 18;		// 수집 개수
	} x ;

} STR_PG_COLLECT_COUNT;

// 펄스정보생성판의 필처 정보 설정 구조체
typedef struct {
	STR_PG_FILTER_FUNCTION ff;
	STR_PG_FILTER_SIGTYPE fs;
	UNI_PG_FILTER_FREQ_RANGE ffr;
	STR_PG_FILTER_AOA_RANGE far_;						// 필터 방위영역 설정
	STR_PG_FILTER_PULSEWIDTH_RANGE fpr;			// 필터 펄스폭 설정
	STR_PG_FILTER_SA_RANGE fsr;							// 필터 신호세기 설정
	STR_PG_COLLECT_COUNT cc;								// 수집 개수 설정
	UINT ct;																// 수집 시간 설정

} STR_PG_FILTER_INFO ;


typedef union {
	unsigned word;
	struct {
		unsigned count_high : 10;		// 수집 완료/중지했을 때의 상위 수집 개수
		unsigned						: 4;
		unsigned bank				: 2;		// 뱅크 번호, 0x1은 뱅크1이며 0x2는 뱅크2이다.
		unsigned count_low  : 8;		// 수집 완료/중지했을 때의 하위 수집 개수
		unsigned						: 8;
	} x ;

} UNI_PG_COUNT_COLLECT_STOP ;

typedef union {
	UINT word;
	struct {
		unsigned				: 29;
		unsigned lo_6_3 : 1;
		unsigned	lo_16 : 1;
		unsigned	lo_12 : 1;
	} x ;

} UNI_PG_LO_STAT ;


//////////////////////////////////////////////////////////////////////////
// 채널 방탐 보정 관련 구조체 정의

// 임계값 구조체 정의
typedef struct {
	unsigned pa_threshold			 : 8;			// PA 수신 임계값
	unsigned									 : 24;

} STR_PGC_THRESHOLD ;

typedef union {
	STR_PGC_THRESHOLD x;
	UINT word;

} UNI_PGC_THRESHOLD ;


// 임계값 구조체 정의
typedef struct {
	unsigned						 : 10;
	unsigned		 channel : 2;
	unsigned temperature : 5;
	unsigned	 frequency : 9;
	unsigned					pa : 6;

} STR_PGC_ADDRESS ;

typedef union {
	STR_PGC_ADDRESS x;
	UINT word;

} UNI_PGC_ADDRESS ;


// PDW 구조체
// PDW 구조체는 _pdw.h 파일에 있음


//////////////////////////////////////////////////////////////////////////
// 그래픽처리판의 구조체 정의

// 자체점검 구조체
typedef struct {
	unsigned				 : 13;
	unsigned control : 1;		// 제어기 상태
	unsigned display : 1;		// 시현기 상태
	unsigned		 cpu : 1;		// CPU 상태
	unsigned				 : 16;
} STR_GP_BIT ;

typedef union {
	STR_GP_BIT x;
	UINT word;

} UNI_GP_BIT ;

// 보드ID 구조체
typedef struct {
	unsigned reserver1: 8;		// 펌웨어 정보
	unsigned reserver2: 8;		// 제조일련번호
	unsigned id : 16;					// 보드ID: 0xA138

} STR_GP_BOARD_ID ;

typedef union {
	STR_GP_BOARD_ID x;
	UINT word;

} UNI_GP_BOARD_ID ;

typedef struct {
	unsigned								: 16;
	unsigned fault_category : 2;
	unsigned								: 2;
	unsigned		 udf_number : 4;
	unsigned			cmds_mode : 2;
	unsigned								: 1;
	unsigned			log_onoff : 1;
	unsigned								: 3;
	unsigned			disp_mode : 1;

} STR_GP_STAT ;

typedef union {
	STR_GP_STAT x;
	USHORT byte16[2];
	UINT word;

} UNI_GP_STAT ;

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
typedef struct {
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

} STR_ONE_PDW ;

#ifndef ENUM_BANDWIDTH_ENUM
#define ENUM_BANDWIDTH_ENUM
typedef enum {
	en5MHZ_BW=0,
	en50MHZ_BW,

} ENUM_BANDWIDTH ;
#endif

#ifndef _STR_PDWDATA
#define _STR_PDWDATA
typedef struct {
	char	aucTaskID[LENGTH_OF_TASK_ID];
	unsigned int iIsStorePDW;
	int iCollectorID;
	ENUM_BANDWIDTH enBandWidth;

	UINT count;
	_PDW stPDW[MAX_PDW];

} STR_PDWDATA ;
#endif



typedef struct {
	enum CHANNEL_SELECTION channel_selection;
	int noEMT;

} STR_CHANNEL_SELECTION ;

typedef struct {
	int cw_threshold;
	int cw_init_threshold;
	int noEMT;
	BOOL bCWCtrl;

} STR_CW_CONTROL ;


// 탐지용 PDW 수집 구조체 정의
typedef STR_PDWDATA STR_NEW_COLLECT_PDW;

// 추적용 PDW 수집 구조체 정의
typedef STR_PDWDATA STR_KWN_COLLECT_PDW;

// 스캔용 PDW 수집 구조체 정의
typedef STR_PDWDATA STR_SCN_COLLECT_PDW;


typedef struct {
	UINT nBank;
	enum FILTER_STAT nStat[NEW_NO_BANK];

} STR_NEW_COLLECT_BANK ;

//////////////////////////////////////////////////////////////////////////
// 에미터 식별 구조체

typedef unsigned int UDFINDEX;

//////////////////////////////////////////////////////////////////////////
// 시스템 로그 관련 구조체 정의
#define LOG_HEADER						(sizeof(time_t)+2*sizeof(UINT))
#define MAX_LOG_PDW						400

// 에미터 상세정보 구조체 정의
typedef struct {
	STR_NEWAET aet;
	_PDW pdw[MAX_LOG_PDW];

} STR_AET_DETAIL ;

// 시스템 로그 구조체 정의
typedef struct {
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

} STR_LOGMSG ;


//////////////////////////////////////////////////////////////////////////
// 기본적인 큐 메시지 구조체 
typedef struct {
	USHORT opCode;
	UCHAR address1;
	UCHAR address2;
	UINT opData;

} STR_QUEUE_MESSAGE ;

//PC와 랜 통신을 위한 큐 메시지 구조체 
typedef struct {
	USHORT opCode;
	UCHAR address1;
	UCHAR address2;
	UINT opData;

	SRxLOBData stLOB;
} STR_QUEUE_AET_MESSAGE ;

// 시스템 로그 관련 큐 메시지 구조체 
typedef struct {
	USHORT opCode;
	UCHAR address1;
	UCHAR address2;
	UINT opData;

	STR_LOGMSG log;
} STR_QUEUE_LOG_MESSAGE ;


//////////////////////////////////////////////////////////////////////////
// Chaff/Flare 발사 명령 정의

// Chaff 발사 정보
typedef struct {
	USHORT startDelay;					// res. ms
	USHORT endDelay;
	USHORT payloadCount;
	USHORT payloadInterval;
	USHORT burstCount;
	USHORT burstInterval;
	USHORT salvoCount;
	USHORT salvoInterval;

} STR_CHAFF_FLARE_ORDER ;

// C/F 발사 정보 순서를 만들기 위한 구조체 정의
typedef struct {
	UINT fire_time;
	UINT chaff_flare;

} STR_FIRE_INFO;

//////////////////////////////////////////////////////////////////////////
// 로그 데이터 구조체

// 로그 데이터 구조체
typedef struct {
	unsigned long size;
	unsigned char *pLogBuffer;

} STR_SYSTEMLOG ;

// 패킷 헤더 정보
#ifdef _WIN32
typedef struct { 
	unsigned short c_size;
	unsigned char check_sum;
	unsigned char packet_number;

} STR_LOGPACKET_HEADER ;

#else
typedef struct { 
	unsigned char packet_number;
	unsigned char check_sum;
	unsigned short c_size;

} STR_LOGPACKET_HEADER ;
#endif

typedef union {
	UINT word;
	STR_LOGPACKET_HEADER x;

} UNI_LOGPACKET_HEADER ;



#endif // !defined(AFX_STRUCTS_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_)

