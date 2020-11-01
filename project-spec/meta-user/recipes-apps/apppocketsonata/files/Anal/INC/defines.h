// Defines.h: interface for the Definition
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEFINES_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_)
#define AFX_DEFINES_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "system.h"

#define PROJECT_NAME								"Self-Dev. RWR"


// 장비 정상/비정상 정의 값.
#define _spPass											(0)
#define _spFail											(UINT) (-1)


//////////////////////////////////////////////////////////////////////////
// 타스크 Priority
enum ENUM_TASK_PRIORITY {
    tPRI_MANTSK=110,
    tPRI_ALIVEMARK,

    tPRI_RECVSERIAL,
    tPRI_SENDSERIAL,

    tPRI_RT1553,
    tPRI_CTRLCMDS,
    tPRI_RUNBIT,

    //tPRI_RECVSERIAL,
    //tPRI_SENDSERIAL,

    tPRI_POLLKEY,
    tPRI_GRDISP,
    tPRI_GETPDW,
    tPRI_MANAET,
    tPRI_SIGANAL,
    tPRI_LOGDEBUG,
    tPRI_TCPSRV } ;

//////////////////////////////////////////////////////////////////////////
// OS 관련 정의문
#define MAX_LEN_MSGQ								(256)
#define SIZE_OF_MESSAGE							( sizeof( STR_QUEUE_MESSAGE ) )

// tick count 에 따른 정의문
#define TICK_COUNT									(100)
#define OS_ONE_SEC									(100)
#define OS_TEN_MILLISEC							(1)
#define OS_ONE_MILLISEC							(0.1)

//////////////////////////////////////////////////////////////////////////
//
#define BOOTING_TIME								(60)	// 부팅 시간


//////////////////////////////////////////////////////////////////////////
// 하드웨어 정의문

// IRQ* 인터럽트 정의
#define	IRQ_NUM_OVER_HEAT						(4)		// LO/과열 정보
#define	IRQ_CONTROLLER							(1)		// 제어기 인터럽트
#define	IRQ_NUM_MAN_CMDS						(6)		// 조종사 Trigger In(CMDS semi-auto)
#define	IRQ_NUM_COLLECT							(7)

// 벡터 정의
#define VEC_NUM_COLLECT							(135)
#define VEC_NUM_CONTROLLER					(129)


//////////////////////////////////////////////////////////////////////////
// 초단수신기 메시지 정의

// 초단수신기의 대역 개수
#define TOTAL_RECEIVER							(4)

// 초단수신기 양호 비트 결과 값 정의
#define HF_BIT_OK										(1)
#define HF_PP_BIT_OK								(0x0FFFFFFF)


// 초단수신기 관련 메시지 정의
#define	HEADER_VH_RECEIVER_MESSAGE	( sizeof(UCHAR)*4 )
#define	TAIL_VH_RECEIVER_MESSAGE		( sizeof(UCHAR)*2 )

#define DEFAULT_VH_RECEIVER_MESSAGE	( HEADER_VH_RECEIVER_MESSAGE+TAIL_VH_RECEIVER_MESSAGE )

// 초단수신기의 최대 메시지 길이
#define MAX_DATA_MESSAGE						(64)

// 초단수신기의 채널 보정 데이터 최대 크기
#define MAX_SIZE_CHNNELCOMPENSATION	(0x400000)

// 초단수신기의 명령 처리에 대한 최대 소요 시간
#define MAX_TO_HF_PROCESS						(int) ( 100 * OS_ONE_MILLISEC )

// 초단수신기의 타임아웃
#define MAX_TO_HF_COMM							(int) ( 100 * OS_ONE_MILLISEC )		// ( 1*OS_ONE_SEC )

// 초단수긴기 통신 메시지 정의
#define VH_REQ_INIT									(0x01)
#define VH_RES_INIT									(0x02)
#define VH_REQ_IBIT									(0x03)
#define VH_RES_IBIT									(0x04)
#define VH_REQ_IBIT_RESULT					(0x05)
#define VH_RES_IBIT_RESULT					(0x06)
#define VH_REQ_PBIT									(0x07)
#define VH_RES_PBIT									(0x08)
#define VH_REQ_PBIT_RESULT					(0x09)
#define VH_RES_PBIT_RESULT					(0x0A)
#define VH_REQ_CBIT									(0x0B)
#define VH_RES_CBIT									(0x0C)
#define VH_REQ_CBIT_RESULT					(0x0D)
#define VH_RES_CBIT_RESULT					(0x0E)
#define VH_REQ_CHANNEL_READY				(0x11)
#define VH_RES_CHANNEL_READY				(0x12)
#define VH_REQ_CHANNEL_SEND					(0x13)
#define VH_RES_CHANNEL_SEND					(0x14)
#define VH_REQ_TEMPERATURE_CHECK		(0x15)
#define VH_RES_TEMPERATURE_CHECK		(0x16)
#define VH_REQ_TEMPERATURE_RESULT		(0x17)
#define VH_RES_TEMPERATURE_RESULT		(0x18)
#define VH_REQ_SWITCH_CONTROL				(0x19)
#define VH_RES_SWITCH_CONTROL				(0x1A)
#define VH_REQ_VERSION							(0x1B)
#define VH_RES_VERSION							(0x1C)

#define VH_ERR_REQUEST							(0xE4)
#define VH_ERR_ETX									(0xE6)
#define VH_ERR_COMMAND							(0xEA)
#define VH_ERR_CHECKSUM							(0xEC)
#define VH_ERR_SLAVEFULL						(0xEE)


//////////////////////////////////////////////////////////////////////////
// 펄스정보생성판 정의

// 온도 res.
#define PG_TEMP_RES										(5)		

// 펄스정보생성판의 명령 처리에 대한 최대 소요 시간
#define MAX_TO_PG_PROCESS							(int) ( 100*OS_ONE_MILLISEC )

// 펄스정보생성판의 필터 개수
#define MAX_NO_FILTER									(8)

#define PG_ONE_SEC										(50000000)
#define PG_ONE_MILLISEC								(PG_ONE_SEC/1000)
#define PG_ONE_MICROSEC								(PG_ONE_MILLISEC/1000)

#define PG_BIT_OK											(0xa137)			// 상위 16비트는 읽을 때마다 변경됨.
#define PG_INIT_OK										(0x1234a137)

// 필터 채널 1번은 수집용으로 한다. 그리고 나머지 7개 채널에 대해서는 제어용으로 사용한다.
enum { NO_FILTER_FOR_COLLECTING=0, NO_FILTER_FOR_BIT } ;


// 하나의 TARGET SEPERATE 관련 정의
#define	MAX_SYMBOLS_IN_CLUSTER				(3)


#define	MAX_CMDS_THREAT								(1)

#define BLINK_ENABLE									(0xF0)
#define BLINK_DISABLE									(0x00)

#define	INDEX_TO_GP_ADDRESS(A)				( ( A / 2 ) * 0x10 + ( ( A % 2 ) * 4 ) )


//////////////////////////////////////////////////////////////////////////
// 신호분석 관련 정의문
#define MAX_TO_AP_PROCESS							(1*OS_ONE_SEC)

// 수집중인 버퍼가 수집중일 때 수집 대역을 설정할 때 재시도 회수를 의미한다.
#define MAX_COLLECTING_SUSPEND				(20)

// 필터판 상태
enum FILTER_STAT { ON_COLLECTING=1, COLLECTING_END, ON_ANALYSIS, ANALYSIS_END } ;

// 
enum ANAL { NEW_ANAL=0, KWN_ANAL, SCN_ANAL } ;

// 모드 상태
enum COLLECT_MODE { NORMAL_COLLECT_MODE=0, BIT_MODE, TEST_MODE, CLOSE_MODE } ;


//////////////////////////////////////////////////////////////////////////
// 에미터 식별
#define	MAX_EID												(4000)


//////////////////////////////////////////////////////////////////////////
// 주파수 하모닉 정의
#define FIX_FREQ_HARMONIC_MARGIN			(10)



//////////////////////////////////////////////////////////////////////////
// 분석 모드(Normal,Simul)
enum ANALYSIS_MODE { NORMAL_MDOE=0, SIMUL_MODE };


// Priority 순서 정의
enum KEY_PRIORITY_THREAT { KEY_PRIORITY_NORMAL=0, KEY_PRIORITY_UNKNOWN, KEY_PRIORITY_KNOWN, KEY_PRIORITY_LOWALT } ;
enum COMPARE_PRIORITY { _NEXT_COMPARE=0 /* equal */ , _HIGH_PRIORITY /* break */ , _LOW_PRIORITY /* continue, next threat compare */ } ;

// 시스템 로그

// 시스템로그 파일이 항공기접속판에 있을 경우에는 아래 정의를 undefine 으로 함.
#define _SYSTEMLOG_FILESYSTEM_

#define	KILO_BYTE													(1024)

#define LIMIT_BYTE_OF_LOG_DRIVE						((10*MAX_LOGBUFFER_SIZE+6000)/KILO_BYTE)

#ifdef _WIN32
#define LOG_FILE_DRIVE										"d:\\backupsys\\tftpboot\\"
#define SYSTEM_LOG_DIRECTORY							"d:\\backupsys\\tftpboot\\SystemLog"
#define WEB_HOST_DIRECTORY								"d:\\backupsys\\tftpboot\\web"

#else
#define LOG_FILE_DRIVE										"/tffs0"
#define SYSTEM_LOG_DIRECTORY							"/tffs0/SystemLog"
#define WEB_HOST_DIRECTORY								"host:web"

#endif


#define SCREEN_BUFFER_LOG_FILENAME				"PRGDISK:/screenbuffer.log"


#endif // !defined(AFX_DEFINES_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_)
