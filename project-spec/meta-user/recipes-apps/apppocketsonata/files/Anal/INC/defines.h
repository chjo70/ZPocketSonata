// Defines.h: interface for the Definition
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEFINES_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_)
#define AFX_DEFINES_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "System.h"

#define PROJECT_NAME								"Self-Dev. RWR"


// ��� ����/������ ���� ��.
#define _spPass											(0)
#define _spFail											(UINT) (-1)


//////////////////////////////////////////////////////////////////////////
// Ÿ��ũ Priority
enum { tPRI_MANTSK=110,
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
// OS ���� ���ǹ�
#define MAX_LEN_MSGQ								(256)
#define SIZE_OF_MESSAGE							( sizeof( STR_QUEUE_MESSAGE ) )

// tick count �� ���� ���ǹ�
#define TICK_COUNT									(100)
#define OS_ONE_SEC									(100)
#define OS_TEN_MILLISEC							(1)
#define OS_ONE_MILLISEC							(0.1)

//////////////////////////////////////////////////////////////////////////
//
#define BOOTING_TIME								(60)	// ���� �ð�


//////////////////////////////////////////////////////////////////////////
// �ϵ���� ���ǹ�

// IRQ* ���ͷ�Ʈ ����
#define	IRQ_NUM_OVER_HEAT						(4)		// LO/���� ����
#define	IRQ_CONTROLLER							(1)		// ����� ���ͷ�Ʈ
#define	IRQ_NUM_MAN_CMDS						(6)		// ������ Trigger In(CMDS semi-auto)
#define	IRQ_NUM_COLLECT							(7)

// ���� ����
#define VEC_NUM_COLLECT							(135)
#define VEC_NUM_CONTROLLER					(129)


//////////////////////////////////////////////////////////////////////////
// �ʴܼ��ű� �޽��� ����

// �ʴܼ��ű��� �뿪 ����
#define TOTAL_RECEIVER							(4)

// �ʴܼ��ű� ��ȣ ��Ʈ ��� �� ����
#define HF_BIT_OK										(1)
#define HF_PP_BIT_OK								(0x0FFFFFFF)


// �ʴܼ��ű� ���� �޽��� ����
#define	HEADER_VH_RECEIVER_MESSAGE	( sizeof(UCHAR)*4 )
#define	TAIL_VH_RECEIVER_MESSAGE		( sizeof(UCHAR)*2 )

#define DEFAULT_VH_RECEIVER_MESSAGE	( HEADER_VH_RECEIVER_MESSAGE+TAIL_VH_RECEIVER_MESSAGE )

// �ʴܼ��ű��� �ִ� �޽��� ����
#define MAX_DATA_MESSAGE						(64)

// �ʴܼ��ű��� ä�� ���� ������ �ִ� ũ��
#define MAX_SIZE_CHNNELCOMPENSATION	(0x400000)

// �ʴܼ��ű��� ��� ó���� ���� �ִ� �ҿ� �ð�
#define MAX_TO_HF_PROCESS						(int) ( 100 * OS_ONE_MILLISEC )

// �ʴܼ��ű��� Ÿ�Ӿƿ�
#define MAX_TO_HF_COMM							(int) ( 100 * OS_ONE_MILLISEC )		// ( 1*OS_ONE_SEC )

// �ʴܼ���� ��� �޽��� ����
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
// �޽����������� ����

// �µ� res.
#define PG_TEMP_RES										(5)		

// �޽������������� ��� ó���� ���� �ִ� �ҿ� �ð�
#define MAX_TO_PG_PROCESS							(int) ( 100*OS_ONE_MILLISEC )

// �޽������������� ���� ����
#define MAX_NO_FILTER									(8)

#define PG_ONE_SEC										(50000000)
#define PG_ONE_MILLISEC								(PG_ONE_SEC/1000)
#define PG_ONE_MICROSEC								(PG_ONE_MILLISEC/1000)

#define PG_BIT_OK											(0xa137)			// ���� 16��Ʈ�� ���� ������ �����.
#define PG_INIT_OK										(0x1234a137)

// ���� ä�� 1���� ���������� �Ѵ�. �׸��� ������ 7�� ä�ο� ���ؼ��� ��������� ����Ѵ�.
enum { NO_FILTER_FOR_COLLECTING=0, NO_FILTER_FOR_BIT } ;


// �޽������������� ������ ���� ����
enum CHANNEL_MODE { FORCED_MODE=1, NORMAL_MODE=2 } ;
enum CHANNEL_COMPENSATION { USE_CHANNEL_COMPENSATION=1, NOTUSE_CHANNEL_COMPENSATION } ;
enum CHANNEL_SELECTION { CHANNEL_1=0xE, CHANNEL_2=0xD, CHANNEL_3=0xB, CHANNEL_4=0x7, NOT_USE_CHANNEL=0x0 } ;
enum BLANKING_MODE { NOTUSE_BLANKING_MODE=0, USE_BLANKING_MODE } ;
enum RX_THRESHOLD_MODE { MANUAL_RX_MODE=0, AUTO_RX_MODE, VME_ERROR } ;
//enum BAND_INFO { F_BAND1=0, F_BAND2, F_BAND3, F_BAND4, CD_BAND, BIT_OFFSET } ;
enum FUNCTION { REJECT_FILTER=0x01, PASS_FILTER } ;
//enum MEMORY_BANK { BANK1=0, BANK2, ALL_BANK } ;
enum DIRECTION_VALID { DV_DISABLE=0, DV_ENABLE } ;
enum PULSE_TYPE { NORMAL_PULSE=1, CW_PULSE=2, FMOP_PULSE=4, SHORT_PULSE=7, ALL_PULSE=8 } ;
enum DIRECTION_MODE { EMISSION_MODE=0x1, INJECTION_MODE=0x2 } ;
enum ERASE_MEMORYCHANNEL { ERASE_CHANNEL_1=1, ERASE_CHANNEL_2=2, ERASE_CHANNEL_3=4, ERASE_CHANNEL_4=8 } ;

// �޽����������� ��ɾ�
#define	PG_REQ_INIT										(VME_A24_MSTR_LOCAL+0x400000)
#define	PG_GET_BOARD_ID								(VME_A24_MSTR_LOCAL+0x400004)
#define PG_REQ_BIT										(VME_A24_MSTR_LOCAL+0x400008)
#define PG_GET_BIT_RESULT							(VME_A24_MSTR_LOCAL+0x400008)
#define PG_SET_CHANNEL_MODE						(VME_A24_MSTR_LOCAL+0x40000C)
#define PG_SET_CHANNEL_SWITCH					(VME_A24_MSTR_LOCAL+0x400010)
#define PG_SET_BANDINFO								(VME_A24_MSTR_LOCAL+0x400014)
#define PG_SET_TEMPERATURE						(VME_A24_MSTR_LOCAL+0x400018)
#define PG_GET_TEMPERATURE						(VME_A24_MSTR_LOCAL+0x400018)
#define PG_REQ_MEMOTY_ERASE						(VME_A24_MSTR_LOCAL+0x400020)
#define PG_SET_CCOMPENSATION_ADDR			(VME_A24_MSTR_LOCAL+0x400024)
#define PG_SET_CHANNELCOMPENSATION		(VME_A24_MSTR_LOCAL+0x400028)
#define PG_GET_CHANNELCOMPENSATION		(VME_A24_MSTR_LOCAL+0x40002C)
#define PG_SET_DIRECTION_MODE					(VME_A24_MSTR_LOCAL+0x400030)
#define PG_SET_CHANNELCOMPENSATIONUSE	(VME_A24_MSTR_LOCAL+0x400034)
#define PG_GET_CHANNELCOMPENSATIONUSE	(VME_A24_MSTR_LOCAL+0x400034)
#define PG_SET_THRESHOLD							(VME_A24_MSTR_LOCAL+0x400040)
#define PG_GET_THRESHOLD							(VME_A24_MSTR_LOCAL+0x400040)
#define PG_SET_BLANKING								(VME_A24_MSTR_LOCAL+0x400044)
#define PG_GET_BLANKING								(VME_A24_MSTR_LOCAL+0x400044)
#define PG_SET_RX_THRESHOLD_MODE			(VME_A24_MSTR_LOCAL+0x400048)
#define PG_GET_RX_THRESHOLD_MODE			(VME_A24_MSTR_LOCAL+0x400048)
#define PG_SET_WIDEBAND_RECEIVER_MODE	(VME_A24_MSTR_LOCAL+0x40004C)
#define PG_GET_WIDEBAND_RECEIVER_MODE	(VME_A24_MSTR_LOCAL+0x40004C)
#define PG_SET_PRE_FILTER_FUNCTION		(VME_A24_MSTR_LOCAL+0x400050)
#define PG_SET_FILTER_TYPE						(VME_A24_MSTR_LOCAL+0x400054)
#define PG_SET_FILTER_FREQ						(VME_A24_MSTR_LOCAL+0x400058)
#define PG_SET_FILTER_AOA							(VME_A24_MSTR_LOCAL+0x40005C)
#define PG_SET_FILTER_PW							(VME_A24_MSTR_LOCAL+0x400060)
#define PG_SET_FILTER_SA							(VME_A24_MSTR_LOCAL+0x400064)
#define PG_INIT_FILTER_INFO						(VME_A24_MSTR_LOCAL+0x400068)
#define PG_SET_COLLECT_COUNT					(VME_A24_MSTR_LOCAL+0x400070)
#define PG_SET_COLLECT_TIME						(VME_A24_MSTR_LOCAL+0x400074)
#define PG_REQ_START_COLLECT					(VME_A24_MSTR_LOCAL+0x400078)
#define PG_REQ_STAT_COLLECT						(VME_A24_MSTR_LOCAL+0x40007C)
#define PG_GET_STAT_COLLECT						(VME_A24_MSTR_LOCAL+0x40007C)
#define PG_REQ_LATCH_MEMORYCOUNTER		(VME_A24_MSTR_LOCAL+0x400080)
#define PG_COUNT_COLLECT_STOP					(VME_A24_MSTR_LOCAL+0x400080)
#define PG_INIT_MEMORY_COUNTER				(VME_A24_MSTR_LOCAL+0x400084)

#define PG_COLLECT_STOP								(VME_A24_MSTR_LOCAL+0x40008C)
#define PG_GET_PDW_PHASE1							(VME_A24_MSTR_LOCAL+0x4000A0)
#define PG_GET_PDW_PHASE2							(VME_A24_MSTR_LOCAL+0x4000A4)
#define PG_GET_PDW_PHASE3							(VME_A24_MSTR_LOCAL+0x4000A8)
#define PG_GET_LO_STAT								(VME_A24_MSTR_LOCAL+0x4000C0)

// ��Ž ���� ���� ����
#define	PGC_REQ_INIT									(VME_A24_MSTR_LOCAL+0xCA0000)
#define PGC_SET_THRESHOLD							(VME_A24_MSTR_LOCAL+0xCA0020)
#define PGC_GET_THRESHOLD							(VME_A24_MSTR_LOCAL+0xCA0020)
#define PGC_REQ_START_COLLECT					(VME_A24_MSTR_LOCAL+0xCA0030)
#define PGC_REQ_STOP_COLLECT					(VME_A24_MSTR_LOCAL+0xCA0040)
#define PGC_REQ_ERASE_MEMORY					(VME_A24_MSTR_LOCAL+0xCA0050)
#define PGC_REQ_WRITE_ADDRESS					(VME_A24_MSTR_LOCAL+0xCA0060)
#define PGC_REQ_WRITE_DATA						(VME_A24_MSTR_LOCAL+0xCA0070)


#define GP_MAX_THREAT									(16)
#define	GP_MAX_SYMBOL									(32)

#define OFFSET_X											(40)			// �ּ� �ɹ� ����-X��
#define OFFSET_Y											(40)			// �ּ� �ɹ� ����-Y��

#define GP_MONITOR_LEFT								(20)			// �ּ� ���� �ɹ� ���� ��ġ
#define GP_MONITOR_RIGHT							(236)			// �ִ� ���� �ɹ� ���� ��ġ
#define GP_MONITOR_TOP								(20)			// �ּ� ���� �ɹ� ���� ��ġ
#define GP_MONITOR_BOTTOM							(236)			// �ּ� ���� �ɹ� ���� ��ġ

#define GP_WIDTH_LEFT									(GP_MONITOR_RIGHT-GP_CENTER_X)
#define GP_WIDTH_RIGHT								(GP_CENTER_X-GP_MONITOR_LEFT)
#define GP_HEIGHT_BOTTOM							(GP_MONITOR_BOTTOM-GP_CENTER_Y)
#define GP_HEIGHT_TOP									(GP_CENTER_Y-GP_MONITOR_TOP)

#define	GP_CENTER_X										(128)			// �ɹ� �߾� ���� ��ġ-X��
#define	GP_CENTER_Y										(128)			// �ɹ� �߾� ���� ��ġ-Y��

// �ɹ� ����
#define ENEMY_SYMBOL									0x16
#define FRIEND_SYMBOL									0x10
#define GROUND_SYMBOL									0x00
#define SEA_SYMBOL										0x01
#define AIR_SYMBOL										0x02
#define MISSILE_SYMBOL								0x19
#define	UNKNOWN_SYMBOL_X							0x1C
#define	MISSILE_LAUNCHER1							0x0A
#define	MISSILE_LAUNCHER2							0x0C
#define	MISSILE_LAUNCHER3							0x0E

// �ɹ� ũ�� �� ���� ��ġ
#define TEXT_WIDTH_M									(10)
#define TEXT_WIDTH_S									(10)
#define TEXT_WIDTH_L									(10)
#define	TEXT_INTERVAL									(2)

// �ϳ��� TARGET SEPERATE ���� ����
#define	MAX_SYMBOLS_IN_CLUSTER				(3)


enum FAULT_CATEGORY { FAULT_CLEAR=0, SYSTEM_OK=0, OVERHEAT, FATAL, DEGRADED } ;
enum CMDS_MODE { CMDS_CLEAR=0, CHAFF_FLARE_LINK_OFF=0, CMDS_MANUAL, CMDS_SEMI_AUTO, CMDS_AUTO, CMDS_UPDATE } ;
enum OP_MODE { ESM_MODE=0, RWR_MODE, AUTO_MODE };
enum UDF_NUMBER { UDF_CLEAR=0, UDF_1=1, UDF_2, UDF_3 } ;
enum LOG_STAT { LOG_CLEAR=0, LOG_NOTSAVE=0, LOG_SAVE } ;
enum CTRL_LAMP_INFO { ALL_OFF=0, MISSILE_LAUNCH, LOG, MANUAL_, CMDS, FAULT, BIT, CBIT, TARGET_SEP, TARGET_UNKNOWN, HANDOFF, PRIORITY, OPEN, OPMODE, ER2, ALTITUDE, ALT, ER1, UDF, ALL_ON } ;

#define	MAX_CMDS_THREAT								(1)

#define BLINK_ENABLE									(0xF0)
#define BLINK_DISABLE									(0x00)

#define	INDEX_TO_GP_ADDRESS(A)				( ( A / 2 ) * 0x10 + ( ( A % 2 ) * 4 ) )


//////////////////////////////////////////////////////////////////////////
// ��ȣ�м� ���� ���ǹ�
#define MAX_TO_AP_PROCESS							(1*OS_ONE_SEC)

// �������� ���۰� �������� �� ���� �뿪�� ������ �� ��õ� ȸ���� �ǹ��Ѵ�.
#define MAX_COLLECTING_SUSPEND				(20)

// ������ ����
enum FILTER_STAT { ON_COLLECTING=1, COLLECTING_END, ON_ANALYSIS, ANALYSIS_END } ;

// 
enum ANAL { NEW_ANAL=0, KWN_ANAL, SCN_ANAL } ;

// ��� ����
enum COLLECT_MODE { NORMAL_COLLECT_MODE=0, BIT_MODE, TEST_MODE, CLOSE_MODE } ;


//////////////////////////////////////////////////////////////////////////
// ������ �ĺ�
#define	MAX_EID												(4000)


//////////////////////////////////////////////////////////////////////////
// ���ļ� �ϸ�� ����
#define FIX_FREQ_HARMONIC_MARGIN			(10)



//////////////////////////////////////////////////////////////////////////
// �м� ���(Normal,Simul)
enum ANALYSIS_MODE { NORMAL_MDOE=0, SIMUL_MODE };


// Priority ���� ����
enum KEY_PRIORITY_THREAT { KEY_PRIORITY_NORMAL=0, KEY_PRIORITY_UNKNOWN, KEY_PRIORITY_KNOWN, KEY_PRIORITY_LOWALT } ;
enum COMPARE_PRIORITY { _NEXT_COMPARE=0 /* equal */ , _HIGH_PRIORITY /* break */ , _LOW_PRIORITY /* continue, next threat compare */ } ;

// �ý��� �α�

// �ý��۷α� ������ �װ��������ǿ� ���� ��쿡�� �Ʒ� ���Ǹ� undefine ���� ��.
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


// 1553 RT ����
#define XML_FOLDER												"xml"

#define SCREEN_BUFFER_LOG_FILENAME				"PRGDISK:/screenbuffer.log"

// ����� ��ư ����
#define _CONTROL1_


#endif // !defined(AFX_DEFINES_H__F88C3E13_85CC_4285_9FCA_BBA54209C76E__INCLUDED_)
