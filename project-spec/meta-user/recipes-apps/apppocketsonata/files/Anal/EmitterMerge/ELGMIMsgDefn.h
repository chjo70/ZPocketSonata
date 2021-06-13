#ifndef _H_EL_GMI_MSG
#define _H_EL_GMI_MSG

#include <time.h>

//#include "ELDataType.h"
#include "ELEmitterDataType.h"
#include "ElintRsltDataTypedb.h"


/*---------------------------------------------------------------------------------
*-----------------------------  TO GMI 메시지 Sub Command 정의----------------------
*----------------------------------------------------------------------------------*/ 

/* =========================== GMI에서 수행하는 Sub Command ========================*/
enum {
	// POSN에서 방사체 정보 수정시  Sub Command 정의
	SUBCMDCODE_EL_GMI_MANUAL_POS_EST_APPLIED=0x01,
	SUBCMDCODE_EL_GMI_UNLOCK_MANUAL_POS_EST_RESULT,

	// 수집점검 시 POSN간 동기화하기 위한  Sub Command 정의
	SUBCMDCODE_EL_GMI_SIGGEN_APPLIED,
	SUBCMDCODE_EL_GMI_SIGGEN_POS_EST_RESULT,

	// LOB 필터를 POS에서 갱신 후 RELOAD 명령을 연동기에 날려주기 위한 Sub Command 정의.
	SUBCMDCODE_EL_GMI_RELOAD_LOB_FILTER_INFO,

	// 자동위치 산출 (LOB 체크박스에서 유효/무효 선택 후) 적용 결과를 연동기에 알려주기 위한 Sub Command 정의.
	SUBCMDCODE_EL_GMI_LOB_APPLIED,

	// LOB DB 삭제 후 AET 관리에서 관련 LOB를 제거하고 다시 제원 산출(?)을 해야함. 이에 따른 Sub Command 정의.
	SUBCMDCODE_EL_GMI_LOB_DELETED_FROM_DB_AT_POSITION,

	// 식별 데이터 변경
	SUBCMDCODE_EL_GMI_CEDEOB_UPDATE_APPLIED,

	// 임무 시작, 종료
	SUBCMDCODE_EL_GMI_MISSION_CONTROL_APPLIED,

	// 시스템 변수 적용
	SUBCMDCODE_EL_GMI_SYSTEM_VAR_APPLIED,

	// 환경 변수 적용
	SUBCMDCODE_EL_GMI_ENV_VAR_APPLIED,

	// 연동기로 시스템 변수 로딩 요청 (TestConfig.ini)
	SUBCMDCODE_EL_GMI_LOAD_CONFIG_INI,

	// 수동 및 타체계 LOB (분석결과) 추가 처리
	SUBCMDCODE_EL_GMI_LOB_ADDED,

	// 체계 운용에서 임무 시작 처리
	SUBCMDCODE_EL_MISSION_START,

	// 개발자 모드로 위협 관리를 초기화하고자 할 때 처리
	SUBCMDCODE_EL_THREAT_INITIALIZE,
	
	// 특정 위협 삭제
	SUBCMDCODE_EL_REMOVE_THREAT,

	// 특정 LOB 삭제
	SUBCMDCODE_EL_DELETE_LOB,

	// 다운로드 LOB 전송
	SUBCMDCODE_EL_GMI_DOWNLOAD_LOB_ADDED,

	// ELNOT 및 기타 정보 포함한 LOB 전송
	SUBCMDCODE_EL_GMI_DOWNLOAD_LOB_ADDED_AND_ELNOT,

	// 선택 LOB로부터 추가된 LOB 전송
	SUBCMDCODE_EL_GMI_ADD_NEW_LOB_FROM_COPIED_LOB,

	// 탐색필터 내용 변경 . 연동기 처리는 없으며 연동기에서 POS으로 동기화 요청을 날려주기 위함.
	SUBCMDCODE_EL_GMI_BYPASS_TO_RELOAD_SRCH_FILTER,

	// 자동수집 목록 요청
	SUBCMDCODE_EL_STORAGE_LIST,

	// 빔의 위치산출 정보를 수동으로 갱신
	SUBCMDCODE_EL_GMI_MANUAL_POS_EST_APPLIED_TO_BEAM,

	// 보고서 생성시간
	SUBCMDCODE_EL_GMI_REPORT_TIME,

	// 경보 시간
	SUBCMDCODE_EL_GMI_ALERT_TIME,

	// PRF톤 수집 요청
	SUBCMDCODE_EL_PRFTONE_START,

	// 운용 시작
	SUBCMDCODE_EL_OPERATION_CONTROL,

	// 운용 상태 (수집 중지 상태)
	SUBCMDCODE_EL_OPERATION_CONTROL_EXT,

	// LOB 삭제 (위치 산출)
	SUBCMDCODE_EL_REMOVE_LOB_FROM_PE,

	// 특정 위협 미활동
	SUBCMDCODE_EL_DELETE_THREAT,

	// 새로운 방사체 생성을 위해 전자지도에서 선택된 LOB들의 보냄
	SUBCMDCODE_EL_GMI_SELECTED_LOBS_FROM_DMAP_TO_GENERATE_NEW_EMITTER,

	// 새로운 방사체 생성을 위해 전자지도에서 선택된 LOB들의 보냄
	SUBCMDCODE_EL_GMI_SELECTED_LOBS_AS_ONE_SET_FROM_DMAP_TO_GENERATE_NEW_EMITTER,

	// 생성된 방사체/빔 번호를 POSN 에게 전시한다.
	SUBCMDCODE_EL_SHOW_AETID_GENERATED_NEW_EMITTER,

};


/* =========================== POS에서 수행하는 Sub Command ========================*/
enum {	
	SUBCMDCODE_EL_POS_RELOAD_AET_BY_MANUAL_POS_EST_DONE=0x01,
	SUBCMDCODE_EL_NOT_USED_02,
	SUBCMDCODE_EL_NOT_USED_03,
	SUBCMDCODE_EL_NOT_USED_04,
	SUBCMDCODE_EL_POS_RELOAD_LOB_FILTER_INFO_TO_SYNC,
	SUBCMDCODE_EL_NOT_USED_06,
	SUBCMDCODE_EL_POS_LOB_DELETED_FROM_DB_AT_POSITION_TO_SYNC,

	// CED/EOB 변경 처리 요청
	//SUBCMDCODE_EL_POS_CEDEOB_UPDATE_POSITION_TO_SYNC,

	SUBCMDCODE_EL_NOT_USED_08,
	SUBCMDCODE_EL_NOT_USED_09,
	SUBCMDCODE_EL_NOT_USED_10,
	SUBCMDCODE_EL_POS_ENV_VAR_APPLIED		,
	SUBCMDCODE_EL_SHOW_SPTR_DATA_TO_PDW_IQ_IF_WND	,
	SUBCMDCODE_EL_ORDER_TO_CHECK_SEQ_NUM,
};


/*-----------------------------------------------------------
 *							GMI   -> POSN 메시지
 *-----------------------------------------------------------*/
#define OPER_ID_GMI_SEND_MSG	555

// struct SGMIBase
// {
// 	int nLinkNum;
// 	bool bIsOnlyForLog;
// 	char szDebugText[512];
// 	SGMIBase::SGMIBase()
// 		:nLinkNum(_LINK1)
// 		,bIsOnlyForLog(false)
// 	{
// 		memset(szDebugText, 0, 512);
// 	};
// };

// #define MAX_FAMILYINFO						(512)
#define MAX_DELETE_FAMILT_INFO			(20)
#define MAX_LOB_ARRAY_INFO					(256)
// struct SGMILobMsg : public SGMIBase
// {	
// 	unsigned long long ullSeqId;
// 	int nInfoSize;
// 	bool bIsFisintTask;
// 	SThreatFamilyInfo arr_stInfo[MAX_FAMILYINFO];
// 	SGMILobMsg::SGMILobMsg()		
// 		:ullSeqId(0)
// 		,nInfoSize(-1)
// 		,bIsFisintTask(false)
// 		{
// 			memset(arr_stInfo, 0, sizeof(arr_stInfo) );
// 		};
// };

// struct SGMIRawDataMsg : public SGMIBase
// {
// 	unsigned long long ullSeqId;
// 	SGMIRawDataMsg::SGMIRawDataMsg()
// 		:ullSeqId(0){};
// };

/*-----------------------------------------------------------
 *							POSN -> GMI 메시지
 *-----------------------------------------------------------*/
#define OPER_ID_POS_TO_GMI_SEND_MSG_LINK1	556
#define OPER_ID_POS_TO_GMI_SEND_MSG_LINK2	(10000+OPER_ID_POS_TO_GMI_SEND_MSG_LINK1)

//////////////////////////////////////////////////////////////////////////
// 1번 PAYLOAD 메시지 정의 :
struct SELEmitterEdited
{
    //char szMissionId[LENGTH_OF_MISSION_ID];
    int	 nAETId;
    int  nABTId;
    int  nLOBId;

    // 수정 그룹 비티맵
    //UELMANUALVAL userManual;

    // 방사체 정보 데이터
    SELAETDATA aetData;

    // 위치 정보 우선 정보 (자동 또는 수동 위치 산출)
    bool bManualPosEstPreferred;

    unsigned int uiSeqNum;

    // PIN #
    int iPinNumber;
    char szELNOT[_MAX_ELNOT_STRING_SIZE_];

    // 경보 및 보고서 최초/최종 보고 시각
    time_t ti_FirstTime;									// 최초 시각
    time_t ti_FinalTime;									// 최종 시각

    E_BEAM_EMITTER_STAT enEmitterStat;

    unsigned int iChangedAETID;							// AET #
    unsigned int iChangedABTID;							// ABT #

//    SELEmitterEdited::SELEmitterEdited() : enEmitterStat(E_ES_NOT_AVAILABLE)
//    {
//    }

};

struct SELLOBValidity
{
	int	nAETId;
	int nABTId;			// 1 
	int nLOBId;			// 0

};

struct SELOPERATIONLIB {
	int iOperation;					// 삭제, 편집, 추가, NO-Operation
	int iNumber;						// 레이더 또는 위협 번호

} ;


// typedef struct {
// 	EnumLoadType enLoadType;
// 	//bool bCEDUpdate;				// CED를 불러들였을 때 플레그임.
// 	//bool bEOBUpdate;				// EOB를 불러들였을 때 플레그임.
// 
// 	EnumLibType enLibType;	// 기본형 또는 실무형
// 
// 	SELOPERATIONLIB stCED;
// 	SELOPERATIONLIB stEOB;
// 
// } SELLIBUPDATE;

// typedef struct {
// 	SELLIBUPDATE stCEDLibUpdate;
// 	SELLIBUPDATE stEOBLibUpdate;
// 
// } SELCEDEOBUPDATE;

// typedef struct {
// 	SRxLOBHeader sLOBData;
// 	SRxLOBDataGroup sLOBDataGroup;
// 
// } SRxLOBDataAndGroup;

struct SRxLOBDataAndGroupIdArray {
	int nLobCount;
	int nAetId[MAX_LOB_ARRAY_INFO];
	int nAbtId[MAX_LOB_ARRAY_INFO];
	int nLobId[MAX_LOB_ARRAY_INFO];
	unsigned long long ullSeqNum[MAX_LOB_ARRAY_INFO];

} ;

// typedef struct {
// 	SRxLOBData sLOBData;
// 	SRxLOBDataGroup sLOBDataGroup;
// 
// 	SLOBOtherInfo sLOBOtherInfo;
// 
// } SRxLOBDataAndGroupAndOtherInfo;

enum ENStorageListButton {
	enStartOfStorageRequest=0,
	enStopOfStorageRequest,

	enCancelOfStorageRequest,

} ;

typedef enum {
	enStartOfControl=0,
	enStopOfControl,

	enHaltOfControl,

} ENManualControlStatus, ENOperationControl;

struct SELStorageButton {
	ENStorageListButton enStorageListButton;				// 진행 상태를 버튼 상태로 함.

	int nLinkNo;
	int nStorageKinds;
	bool bIFTotalMetaRequestMode;
	bool bIFTotalMetaViewMode;
} ;

struct SELPRFTONE_STATUS {
	int nLinkNo;
	ENManualControlStatus enControlStatus;

} ;

struct SELOPERATION_CONTROL {
	int nLinkNo;
	ENManualControlStatus enControlStatus;

} ;

// typedef struct {
// 	int	 nAETId;
// 	int  nABTId;
// 	int  nLOBId;
// 
// 	char szMissionId[DEF_MISSION_ID_LENGTH];		// 임무ID, 기본 검색에서 보고서 생성시 처리 추가
// 	UINT uiSeqNum;															// 임무ID, 기본 검색에서 보고서 생성시 처리 추가
// 
// 	time_t tFirstReportTime;
// 	//time_t tFinalReportTime;
// 
// } SELReportTime;

struct SELAlertTime {
	int	 nAETId;
	int  nABTId;
	int  nLOBId;

	time_t tFinalAlarmTime;

	unsigned long long ullseqnum;

} ;


// 아래에 위에처럼 추가하세요 
//////////////////////////////////////////////////////////////////////////

// BUS 메시지
// struct SElintUserMsg
// {
// 	int nSubCommand;
// 	char szOperatorId[16]; // operator id.
// 	int nLinkNum;
// 
// 	struct UELUSERMAN {
// 		char			szBuf[2048];
// 
// 		// 방사체 수동 편집 정보
// 		SELEmitterEdited sELEmitterEdited;
// 
// 		// LOB Validity
// 		SELLOBValidity sELLOBValidity;
// 
// 		// CED/EOB 업데이트
// 		SELCEDEOBUPDATE sCEDEOBUpdate;
// 
// 		// LOB 관련 연동기 처리
// 		SRxLOBDataAndGroup sLOBDataAndGroup;
// 
// 		// LOB 복사 후 연동기 처리
// 		SRxLOBDataAndGroupAndOtherInfo sLOBDataAndGroupAndOtherInfo;
// 
// 		// 저장 목록 버튼 상태
// 		SELStorageButton sStorageButton;
// 
// 		// 보고서 관련 시간
// 		SELReportTime sReportTime;
// 
// 		// 경보 관련 시간
// 		SELAlertTime sAlertTime;
// 
// 		// PRF 톤 제어
// 		SELPRFTONE_STATUS sPRFToneStutus;
// 
// 		// 운용 제어 모드 상태
// 		SELOPERATION_CONTROL sOperationControl;
// 
// 		// 방사체형성을 위해 전자지도에서 선택한 객체 ARRAY
// 		SRxLOBDataAndGroupIdArray sLOBDataAndGroupArray;
// 
// 		// 신호 발생한 정보는 DB로 데이터를 쓰고 GMI에게 보고하는 처리로 함.
// 		// SELDBELTSG sSELDBELTSG;
// 
// 	} x ;
// 
// 	SElintUserMsg::SElintUserMsg()
// 		:nSubCommand(0)
// 		,nLinkNum(0)
// 	{
// 		memset( & szOperatorId, 0, sizeof(szOperatorId) );
// 		memset( & x.szBuf, 0, sizeof(x.szBuf) );
// 		memset( & x.sELEmitterEdited, 0, sizeof(x.sELEmitterEdited) );
// 		memset( & x.sELLOBValidity, 0, sizeof(x.sELLOBValidity) );
// 		memset( & x.sCEDEOBUpdate, 0, sizeof(x.sCEDEOBUpdate) );
// 		memset( & x.sLOBDataAndGroup, 0, sizeof(x.sLOBDataAndGroup) );
// 		memset( & x.sLOBDataAndGroupAndOtherInfo, 0, sizeof(x.sLOBDataAndGroupAndOtherInfo) );
// 		memset( & x.sStorageButton, 0, sizeof(x.sStorageButton) );
// 		memset( & x.sReportTime, 0, sizeof(x.sReportTime) );
// 		memset( & x.sAlertTime, 0, sizeof(x.sAlertTime) );
// 		memset( & x.sPRFToneStutus, 0, sizeof(x.sPRFToneStutus) );
// 		memset( & x.sOperationControl, 0, sizeof(x.sOperationControl) );
// 		memset( & x.sLOBDataAndGroupArray, 0, sizeof(SRxLOBDataAndGroupIdArray) );
// 	}
// 
// };


/*!
 * @struct     SGmiTxSigComm
 * @brief		LOB/BEAM/EMITTER 공통 속성 GMI MSG 구조체
 * @author    이정남 (jeongnam.lee@lignex1.com)
 * @date      2016-02-13 오후 2:13 
 */
// struct SGmiTxSigComm
// {
// 	char szMissionId[LENGTH_OF_MISSION_ID]; // 임무id
// 	char szMissionName[LENGTH_OF_GMI_CHAR];	// 임무명
// 	char szEmitterId[LENGTH_OF_GMI_CHAR]; // 방사체id (문자)
// 	char szElnotPrimary[LENGTH_OF_GMI_CHAR]; 	// 전정부호 1순위
// 	char szNickName[LENGTH_OF_GMI_CHAR]; // NickName
// 	char szPrimaryCode[LENGTH_OF_GMI_CHAR];
// 	
// 	bool bIsValid; // 유효성
// 	unsigned int uiEmitterId;
// 	unsigned int uiFrqMin; // Code Value 임에 주의. Encoding 필요.
// 	unsigned int uiFrqMax;
// 	unsigned int uiFrqMean;
// 	unsigned int uiFrqDev;
// 	unsigned int uiPriMin; // us
// 	unsigned int uiPriMax;
// 	unsigned int uiPriMean;
// 	unsigned int uiPriDev;
// 	float	fPrfMinKHz; // KHz
// 	float	fPrfMaxKHz;
// 	float fPrfMinPPS; //PPS
// 	float fPrfMaxPPS;
// 	unsigned int uiPWMin; // us
// 	unsigned int uiPwMax;
// 	unsigned int uiPwMean;
// 	unsigned int uiPwDev;
// 	float uiPaMin;   // dbm
// 	float uiPaMax;
// 	float uiPaMean;
// 	float uiPaDev;
// 
// 	SGmiTxSigComm()
// 		:bIsValid(false)
// 		,uiEmitterId(0)
// 		,uiFrqMin(0)
// 		,uiFrqMax(0)
// 		,uiFrqMean(0)
// 		,uiFrqDev(0)
// 		,uiPriMin(0)
// 		,uiPriMax(0)
// 		,uiPriMean(0)
// 		,uiPriDev(0)
// 		,fPrfMinKHz(0.0)
// 		,fPrfMaxKHz(0.0)
// 		,fPrfMinPPS(0.0) 
// 		,fPrfMaxPPS(0.0)
// 		,uiPWMin(0)
// 		,uiPwMax(0)
// 		,uiPwMean(0)
// 		,uiPwDev(0)
// 	{
// 		memset(szMissionId, 0, LENGTH_OF_MISSION_ID);
// 		memset(szMissionName, 0, LENGTH_OF_GMI_CHAR);
// 		memset(szEmitterId, 0, LENGTH_OF_GMI_CHAR);
// 		memset(szElnotPrimary, 0, LENGTH_OF_GMI_CHAR);
// 		memset(szNickName, 0, LENGTH_OF_GMI_CHAR);
// 		memset(szPrimaryCode, 0, LENGTH_OF_GMI_CHAR);		
// 	}
// };

/*!
 * @struct     SGmiTxLOBMsg
 * @brief		LOB GMI 메시지 구조체
 * @author    이정남 (jeongnam.lee@lignex1.com)
 * @date      2016-02-13 오후 2:13 
 */
// struct SGmiTxLOBMsg : public SGmiTxSigComm
// {
// 	char szTaskId[LENGTH_OF_TASK_ID]; // 과제id
// 	char szTaskName[LENGTH_OF_GMI_CHAR];	// 임무명
// 	char szLobId[LENGTH_OF_GMI_CHAR];	// LobId 문자형
// 	char szBeamId[LENGTH_OF_GMI_CHAR];	// BeamId 문자형
// 	char szModeCodePrimay[LENGTH_OF_GMI_CHAR];	// Mode Code 1순위
// 	char szModulationCode[LENGTH_OF_GMI_CHAR];	// 변조코드
// 	char szPrimaryFunctoinCode[LENGTH_OF_GMI_CHAR];	// 주기능코드
// 	char szElnotSecondary[LENGTH_OF_GMI_CHAR]; 	// 전정부호 2순위
// 	char szModeCodeSecondary[LENGTH_OF_GMI_CHAR];	// Mode Code 2순위
// 	char szElnotTertiary[LENGTH_OF_GMI_CHAR]; 	// 전정부호 3순위
// 	char szModeCodeTertiary[LENGTH_OF_GMI_CHAR];	// Mode Code 3순위
// 	char szSignalType[LENGTH_OF_GMI_CHAR];	// 신호형태
// 	char szBL[LENGTH_OF_GMI_CHAR];	// BL
// 	char szFov[LENGTH_OF_GMI_CHAR];	// FOV
// 	char szFrqModType[LENGTH_OF_GMI_CHAR];	// 주파수 변조형태
// 	char szFrqPatternType[LENGTH_OF_GMI_CHAR];	// 주파수 패턴형태
// 	char szFrqModPeriodicity[LENGTH_OF_GMI_CHAR];	// 주파수 변조 주기성
// 	char szNumOfFrqPos[LENGTH_OF_GMI_CHAR];	// 주파수 포지션 수. Ex) 4P/3E Seq : 1,2,3,1
// 	char szFrqModSequence[LENGTH_OF_GMI_CHAR];	// 주파수 변조 시퀀스
// 	char szPriModType[LENGTH_OF_GMI_CHAR];	// PRI 변조형태
// 	char szPriPatternType[LENGTH_OF_GMI_CHAR];	// PRI 패턴 형태
// 	char szPriModPeriodicity[LENGTH_OF_GMI_CHAR];	// PRI 변조 주기성
// 	char szNumOfPriPos[LENGTH_OF_GMI_CHAR];	// PRI 포지션 수. Ex) 4P/3E Seq : 1,2,3,1
// 	char szPriModSequence[LENGTH_OF_GMI_CHAR];	// PRI 변조 시퀀스
// 	char szScanType[LENGTH_OF_GMI_CHAR];	// 스캔 타입 (추적형/탐색형)
// 	char szDetailScanInfo[LENGTH_OF_GMI_CHAR];	// 세부 스캔형태
// 	char szIntraType[LENGTH_OF_GMI_CHAR];	// 인트라 형태
// 	char szIntraDetailType[LENGTH_OF_GMI_CHAR];	// 인트라 세부 형태	
// 	char szAircraftFOM[LENGTH_OF_GMI_CHAR];	// 항공기 FOM
// 
// 	unsigned int uiSearchBandId; // 탐색대역
// 	unsigned char ucTaskType; // 과제종류
// 	unsigned char ucDetectAntDirection; // 탐지안테나 방향 (좌/우)
// 	int	nLinkNum; // 링크번호
// 	unsigned int nAircraftTailNum; // 항공기 동체 번호
// 	unsigned int nLobId;
// 	unsigned int nBeamId;
// 	unsigned int nPulsePerGrp; // 그룹당 펄스 수
// 	unsigned char ucCollectTimeHour; // 수집 일시 (시)
// 	unsigned char ucCollectTimeMin; // 수집 일시 (분)
// 	unsigned char ucCollectTimeSec; // 수집 일시 (초)
// 	float fDoaMin; // DOA 
// 	float fDoaMax;
// 	float fDoaMean;
// 	float fDoaDev; // 편차
// 	float fDoaSTD; // 표준편차
// 	unsigned char ucDIratio;  // DI 비율 (%)
// 	unsigned int uiFrqModPeriodicity; // 주파수 변조주기 us
// 	unsigned int uiNumOfFrqElement; // 주파수 엘리먼트 수
// 	unsigned int uiPriModPeriodicity; // PRI 변조주기 us
// 	unsigned int uiNumOfPriElement; // PRI 엘리먼트 수
// 	unsigned char ucPriJitterRate; // pri 지터율
// 	unsigned int uiScanPeriodMicroSec; // 스캔주기 (초)
// 	unsigned int uiScanPeriodHz; // 스캔주기 (Hz)
// 	unsigned int uiIntraFrqMin; // intra 주파수 min (RF, MHz) : Code Value임에 주의
// 	unsigned int uiIntraFrqMax; //
// 	unsigned int uiIntraFrqMean; //
// 	unsigned int uiIntraFrqChangeSpan; // 인트라 주파수 변경폭 (KHz)
// 	unsigned int arrPriPerGrp[64]; // 그룹 내 pri
// 	unsigned int arrPaPerGrp[64]; // 그룹 내 pa 차
// 	double dAircraftLat; // 항공기 위도
// 	double dAircraftLong; // 항공기 경도
// 	float fAircraftRoll; // 항공기 roll 각
// 	float fAircraftPitch; // 항공기 pitch 각
// 	float fAircraftHeading; // 항고익 heading 각
// 	bool bPdwRestore; // pdw 저장여부
// 	bool bIqRestore; // IQ 저장영부	
// 	
// 	SGmiTxLOBMsg()
// 	:uiSearchBandId(0) 
// 	,ucTaskType(0)
// 	,ucDetectAntDirection(0) 
// 	,nLinkNum(1) 
// 	,nAircraftTailNum(0) 
// 	,nLobId(0)
// 	,nBeamId(0)
// 	,nPulsePerGrp(0) 
// 	,ucCollectTimeHour(0) 
// 	,ucCollectTimeMin(0) 
// 	,ucCollectTimeSec(0) 
// 	,fDoaMin(0.0) 
// 	,fDoaMax(0.0)
// 	,fDoaMean(0.0)
// 	,fDoaDev(0.0)
// 	,fDoaSTD(0.0)
// 	,ucDIratio(0)
// 	,uiFrqModPeriodicity(0)
// 	,uiNumOfFrqElement(0) 
// 	,uiPriModPeriodicity(0)
// 	,uiNumOfPriElement(0)
// 	,ucPriJitterRate(0)
// 	,uiScanPeriodMicroSec(0)
// 	,uiScanPeriodHz(0)
// 	,uiIntraFrqMin(0)
// 	,uiIntraFrqMax(0)
// 	,uiIntraFrqMean(0)
// 	,uiIntraFrqChangeSpan(0)
// 	,dAircraftLat(0.0)
// 	,dAircraftLong(0.0)
// 	,fAircraftRoll(0.0)
// 	,fAircraftPitch(0.0)
// 	,fAircraftHeading(0.0)
// 	,bPdwRestore(false)
// 	,bIqRestore(false)
// 	{
// 		memset(szTaskId, 0, LENGTH_OF_TASK_ID); // 과제id
// 		memset(szTaskName, 0, LENGTH_OF_GMI_CHAR);	// 임무명
// 		memset(szLobId, 0, LENGTH_OF_GMI_CHAR);	// LobId 문자형
// 		memset(szBeamId, 0, LENGTH_OF_GMI_CHAR);	// BeamId 문자형
// 		memset(szModeCodePrimay, 0, LENGTH_OF_GMI_CHAR);	// Mode Code 1순위
// 		memset(szModulationCode, 0, LENGTH_OF_GMI_CHAR);	// 변조코드
// 		memset(szPrimaryFunctoinCode, 0, LENGTH_OF_GMI_CHAR);	// 주기능코드
// 		memset(szElnotSecondary, 0, LENGTH_OF_GMI_CHAR); 	// 전정부호 2순위
// 		memset(szModeCodeSecondary, 0, LENGTH_OF_GMI_CHAR);	// Mode Code 2순위
// 		memset(szElnotTertiary, 0, LENGTH_OF_GMI_CHAR); 	// 전정부호 3순위
// 		memset(szModeCodeTertiary, 0, LENGTH_OF_GMI_CHAR);	// Mode Code 3순위
// 		memset(szSignalType, 0, LENGTH_OF_GMI_CHAR);	// 신호형태
// 		memset(szBL, 0, LENGTH_OF_GMI_CHAR);	// BL
// 		memset(szFov, 0, LENGTH_OF_GMI_CHAR);	// FOV
// 		memset(szFrqModType, 0, LENGTH_OF_GMI_CHAR);	// 주파수 변조형태
// 		memset(szFrqPatternType, 0, LENGTH_OF_GMI_CHAR);	// 주파수 패턴형태
// 		memset(szFrqModPeriodicity, 0, LENGTH_OF_GMI_CHAR);	// 주파수 변조 주기성
// 		memset(szNumOfFrqPos, 0, LENGTH_OF_GMI_CHAR);	// 주파수 포지션 수. Ex) 4P/3E Seq : 1,2,3,1
// 		memset(szFrqModSequence, 0, LENGTH_OF_GMI_CHAR);	// 주파수 변조 시퀀스
// 		memset(szPriModType, 0, LENGTH_OF_GMI_CHAR);	// PRI 변조형태
// 		memset(szPriPatternType, 0, LENGTH_OF_GMI_CHAR);	// PRI 패턴 형태
// 		memset(szPriModPeriodicity, 0, LENGTH_OF_GMI_CHAR);	// PRI 변조 주기성
// 		memset(szNumOfPriPos, 0, LENGTH_OF_GMI_CHAR);	// PRI 포지션 수. Ex) 4P/3E Seq : 1,2,3,1
// 		memset(szPriModSequence, 0, LENGTH_OF_GMI_CHAR);	// PRI 변조 시퀀스
// 		memset(szScanType, 0, LENGTH_OF_GMI_CHAR);	// 스캔 타입 (추적형/탐색형)
// 		memset(szDetailScanInfo, 0, LENGTH_OF_GMI_CHAR);	// 세부 스캔형태
// 		memset(szIntraType, 0, LENGTH_OF_GMI_CHAR);	// 인트라 형태
// 		memset(szIntraDetailType, 0, LENGTH_OF_GMI_CHAR);	// 인트라 세부 형태
// 		memset(arrPriPerGrp, 0, 64);	// 그룹 내 PRI
// 		memset(arrPaPerGrp, 0, 64);	// 그룹 내 PA 차
// 		memset(szAircraftFOM, 0, LENGTH_OF_GMI_CHAR);	// 항공기 FOM
// 	}
// };

// struct SGmiTxBeamMsg : public SGmiTxSigComm
// {
// 	char szBeamId[LENGTH_OF_GMI_CHAR];	// BeamId 문자형
// 	char szModeCodePrimay[LENGTH_OF_GMI_CHAR];	// Mode Code 1순위
// 	char szModulationCode[LENGTH_OF_GMI_CHAR];	// 변조코드 1순위
// 	char szPlatform[LENGTH_OF_GMI_CHAR];	// 플랫폼
// 	char szSignalType[LENGTH_OF_GMI_CHAR];	// 신호형태
// 	char szFrqModType[LENGTH_OF_GMI_CHAR];	// 주파수 변조형태
// 	char szFrqPatternType[LENGTH_OF_GMI_CHAR];	// 주파수 패턴형태
// 	char szFrqModPeriodicity[LENGTH_OF_GMI_CHAR];	// 주파수 변조 주기성
// 	char szNumOfFrqPos[LENGTH_OF_GMI_CHAR];	// 주파수 포지션 수. Ex) 4P/3E Seq : 1,2,3,1
// 	
// 	unsigned int uiRadarModePriority; // 레이더 모드 우선순위
// 	unsigned int uiRadarPriority; // 레이더 우선순위
// 	unsigned int nPulsePerGrp; // 그룹당 펄스 수
// 	unsigned int uiNumOfLob; // LOB 수
// 	unsigned char ucCollectStartTimeHour; // 수집 시작 일시 (시)
// 	unsigned char ucCollectStartTimeMin; // 수집 시작 일시 (분)
// 	unsigned char ucCollectStartTimeSec; // 수집 시작 일시 (초)
// 	unsigned char ucCollectFinalTimeHour; // 수집 최종 일시 (시)
// 	unsigned char ucCollectFinalTimeMin; // 수집 최종  일시 (분)
// 	unsigned char ucCollectFinalTimeSec; // 수집 최종  일시 (초)
// 	unsigned int uiFrqModPeriodicityMin; // 주파수 변조주기 us (Code 값)
// 	unsigned int uiFrqModPeriodicityMax;
// 	unsigned int uiFrqModPeriodicityMean;
// 	unsigned int uiNumOfFrqElement; // 주파수 엘리먼트 수
// 	unsigned int arrFrqElement[128]; // 주파수 엘리먼트 값
// 	unsigned int uiPriModPeriodMin; // PRI 변조주기 min (us)
// 	unsigned int uiPriModPeriodMax; // PRI 변조주기 max
// 	unsigned int uiPriModPeriodMean; // PRI 변조주기 mean
// 	unsigned int uiNumOfPriElement; // PRI 엘리먼트 수
// 	unsigned char ucPriJitterRate; // pri 지터율
// 	unsigned int arrPriElement[128]; // PRI 엘리먼트 
// 	unsigned int uiScanPeriodMicroSecMin; // 최소스캔주기 min (초)
// 	unsigned int uiScanPeriodHzMin; // 최소스캔주기 min (Hz)
// 	unsigned int uiScanPeriodMicroSecMax; // 최대스캔주기 min (초)
// 	unsigned int uiScanPeriodHzMax; // 최대스캔주기 min (Hz)
// 	bool bIntraModAvaiable; // 인트라변조 유무
// 	unsigned int uiIntraFrqChangeSpanMin; // 인트라 주파수 변경폭 최소(KHz)
// 	unsigned int uiIntraFrqChangeSpanMax; // 인트라 주파수 변경폭 최대(KHz)
// 	unsigned int arrPriPerGrp[64]; // 그룹 내 pri
// 	unsigned int arrPaPerGrp[64]; // 그룹 내 pa 차
// 	double dPosEstLat; // 위치 위도
// 	double dPosEstLong; // 위치 경도
// 	double dAltitude; // 고도
// 	double dCEP; // CEP
// 	double dMajorAxis; // 장축 (m)
// 	double dMinorAxis; // 단축 (m)
// 	float fEEPTiltAngle; // eep 기울기 각
// 		
// 	SGmiTxBeamMsg()
// 	:uiRadarModePriority(0)
// 	,uiRadarPriority(0)
// 	,nPulsePerGrp(0)
// 	,uiNumOfLob(0)
// 	,ucCollectStartTimeHour(0)
// 	,ucCollectStartTimeMin(0)
// 	,ucCollectStartTimeSec(0)
// 	,ucCollectFinalTimeHour(0)
// 	,ucCollectFinalTimeMin(0)
// 	,ucCollectFinalTimeSec(0)
// 	,uiFrqModPeriodicityMin(0)
// 	,uiFrqModPeriodicityMax(0)
// 	,uiFrqModPeriodicityMean(0)
// 	,uiNumOfFrqElement(0)
// 	,uiPriModPeriodMin(0)
// 	,uiPriModPeriodMax(0)
// 	,uiPriModPeriodMean(0)
// 	,uiNumOfPriElement(0)
// 	,ucPriJitterRate(0)
// 	,uiScanPeriodMicroSecMin(0)
// 	,uiScanPeriodHzMin(0)
// 	,uiScanPeriodMicroSecMax(0)
// 	,uiScanPeriodHzMax(0)
// 	,bIntraModAvaiable(false)
// 	,uiIntraFrqChangeSpanMin(0)
// 	,uiIntraFrqChangeSpanMax(0)
// 	,dPosEstLat(0.0)
// 	,dPosEstLong(0.0)
// 	,dAltitude(0.0)
// 	,dCEP(0.0)
// 	,dMajorAxis(0.0)
// 	,dMinorAxis(0.0)
// 	,fEEPTiltAngle(0.0)
// 	{
// 		memset(arrFrqElement, 0, 128);
// 		memset(arrPriElement, 0, 128);
// 		memset(arrPriPerGrp, 0, 64);
// 		memset(arrPaPerGrp, 0, 64);
// 
// 		memset(szBeamId, 0,LENGTH_OF_GMI_CHAR);	// BeamId 문자형
// 		memset(szModeCodePrimay, 0,LENGTH_OF_GMI_CHAR);	// Mode Code 1순위
// 		memset(szModulationCode, 0,LENGTH_OF_GMI_CHAR);	// 변조코드 1순위
// 		memset(szPlatform, 0,LENGTH_OF_GMI_CHAR);	// 플랫폼
// 		memset(szSignalType, 0,LENGTH_OF_GMI_CHAR);	// 신호형태
// 		memset(szFrqModType, 0,LENGTH_OF_GMI_CHAR);	// 주파수 변조형태
// 		memset(szFrqPatternType, 0,LENGTH_OF_GMI_CHAR);	// 주파수 패턴형태
// 		memset(szFrqModPeriodicity, 0,LENGTH_OF_GMI_CHAR);	// 주파수 변조 주기성
// 		memset(szNumOfFrqPos, 0,LENGTH_OF_GMI_CHAR);	// 주파수 포지션 수. Ex) 4P/3E Seq : 1,2,3,1
// 		
// 	}
// };
#endif
