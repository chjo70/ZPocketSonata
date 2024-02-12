/**

    @file      ELEmitterDataType.h
    @brief
    @details   ~
    @author    Cool Guy
    @date      18.06.2023
    @copyright © Cool Guy, 2023. All right reserved.

**/
#pragma once


#ifndef __VXWORKS__
#include <stdio.h>
#include <string.h>
#include <memory.h>
#endif


//#include <string>
#include <list>

using namespace std;

#include "ELMsgDefn.h"

#include "../../Include/system.h"

//#include "../Identify/ELCEDLibDataType2.h"


/**
* [식별자 : D-GR-SDD-XXX]
* [추적성 : R-GR-SRS-XXX]
*
* @file ELEmitterDataType.h
* @brief 방사체 목록창에서 View/Logic 간 발생하는 인터페이스 data 정의
* @author 이정남
* @date 2013.5.25
*
* [개정이력]
*  2013.5.25. 신규작성
*  2013.6.18. std::string strIsFisintTask 데이터 추가
*/

// 위치 산출하기 위한 최대 LOB 갯수 정의
#define MAX_OF_LOBS_PE								(30)					// LOB 최대 갯수
// 빔에서 보관하기 위한 LOB 갯수 정의
#define MAX_OF_LOBS										(100)					// LOB 후보 개수


/************************************************************************************
*   ELINT Logic -> View에 사용되는 자료형 구조체
*************************************************************************************/

/* 1.  E_EL_LV_SHOW_EMITTER_DATA 송신시 data_in에 사용되는 구조체. 리턴없음*/
//#ifndef ST_EMIITERINFO_DISP
//#define ST_EMIITERINFO_DISP
// stEmitterInfoDisp 의 중복 정의를 막기위해 #ifndef.. 사용

#define SIZE_OF_CHAR_EMITTER_INFO	15
#define SIZE_OF_CHAR_MID_INFO		32



//static const I_THREAT_DATA stInitThreatData;

struct I_AET_DATA {
	unsigned short usAetId;
 	unsigned short usThreatId;
 	unsigned short usEmitterId;
 	unsigned short usBeamId;

	unsigned int uiOpInitID;

#if defined(_ELINT_) || defined(_XBAND_)
	unsigned char aucTaskID[LENGTH_OF_TASK_ID];
#endif

};

//static const I_AET_DATA g_stInitAETData;


//static const char* strIdResult[] =
//{
//	"-",
//	"기성",
//	"신출",
//	"불명"
//};
enum EnumIdResult
{
	E_EL_PE_UNK_ID=0,
	E_EL_OLD_ID=1,						// 기성
	E_EL_NEW_ID,							// 신출
	E_EL_UNK_ID								// 불명
};

struct STR_CEDEOBID_INFO {
	EnumIdResult eIdResult;					// 0=기성, 1=신출, 2=불명

	// CED의 레이더 모드 인덱스
	unsigned int uiCoRadarModeIndex;
	unsigned int uiRadarModeIndex[MAX_IDCANDIDATE];

    unsigned int ui3LevelRadarModeIndex[THREE_LEVEL_IDCANDIDATE];

	// CED의 레이더 인덱스
	//int nCoRadarIndex;
	//int nRadarIndex[MAX_IDCANDIDATE];

	// EOB의 위협/장치 인덱스
	int nThreatIndex;
	int nDeviceIndex;

// 	STR_CEDEOBID_INFO::STR_CEDEOBID_INFO() : eIdResult(E_EL_OLD_ID), nCoRadarModeIndex(0), nCoRadarIndex(0), nThreatIndex(0), nDeviceIndex(0)
// 	{
// 		memset( nRadarModeIndex, 0, sizeof(nRadarModeIndex) );
// 		memset( nRadarIndex, 0, sizeof(nRadarIndex) );
// 	}

} ;

// 위치 산출 하기 위한 구조체 정의
struct STR_LOBS {
	float fDoa;
	float fLatitude;
	float fLongitude;
	float fAltitude;

	int iCollectorID;

	unsigned int uiLOBID;				// 클러스터링 하면서 구분을 하기 위한 변수 추가

} ;

/**
 * @enum      E_BEAM_CODE
 * @brief     빔 생성 코드 정의
 * @author    조철희 (churlhee.jo@lignex1.com)
 */
enum E_BEAM_CODE
{
	E_UNKNOWN_CODE=0,
	E_CREATE_FREQ_TYPE_CODE=1,
	E_CREATE_PRI_TYPE_CODE,
	E_CREATE_INTRA_TYPE_CODE,
	E_CREATE_SIGNAL_TYPE_CODE,

	E_CREATE_DIST_CODE,

};

// LOB를 업데이트하기 위한 구조체 정의
struct STR_UPDATE_LOB_ABT_AET {
	unsigned int uiAETID;
	unsigned int uiABTID;
	unsigned int uiLOBID;
	string strAcqTime;

	unsigned int uiSeqNum;

}  ;

enum ENUM_PE_STAT {
	E_EL_PESTAT_UNKNOWN=0,
	E_EL_PESTAT_FAIL,					// 위치 산출 후 에러가 난 상태
	E_EL_PESTAT_SUCCESS,				// 위치 산출 결과가 성공인 상태
	E_EL_PESTAT_NOT_YET,				// LOB가 적어서 위치 산출 수행 이전 상태
	E_EL_PESTAT_IMPOSSIBILITY		// 항공기가 고정 위치로 산출하기 어려운 상태
};

struct STR_POSITION_ESTIMATION {
	ENUM_PE_STAT enValid;
	float fLongitude;							// [deg]
	float fLatitude;							// [deg]
    float fAltidude;							// [m]
	float fCEP;										// [m]
	float fMajorAxis;							// [m]
	float fMinorAxis;							// [m]
	float fTheta;									// [0.1도]
	float fDistanceErrorOfThreat;	// [m]

	//int iManualLongitude;				// [deg], MANUAL_POS_EST_LONG
	//int iManualLatitude;				// [deg], MANUAL_POS_EST_LAT

	bool bApplayOfLOBClustering;// TRUE: 적용, FALSE: 미적용

// 	STR_POSITION_ESTIMATION::STR_POSITION_ESTIMATION() : enValid(E_EL_PESTAT_FAIL), fLongitude(0.0), fLatitude(0.0), fCEP(0), fMajorAxis(0), fMinorAxis(0), fTheta(0), fDistanceErrorOfThreat(0), bApplayOfLOBClustering(false)
// 	{
//
// 	}

} ;


typedef struct STempAmbiBeam
{
	unsigned short usAmbiguousBeamId;
	STempAmbiBeam(){
		usAmbiguousBeamId=0;
	}
}I_AmbiBeam;


/*--------------------------------------------------------------------------------
*						GMI LOB 처리용 데이터 타입 신규 정의 2016.2.13. 이정남
*--------------------------------------------------------------------------------*/
/*! Beam 또는 Emitter 상태를 정의한 enum
 * @enum      E_BEAM_EMITTER_STAT
 * @brief
 * @author    이정남 (jeongnam.lee@lignex1.com)
 * @date      2016-02-13 오전 8:27
 */
enum E_BEAM_EMITTER_STAT
{
	E_ES_NOT_AVAILABLE = 0,			// 객체가 생성되지 않은 경우 (필요성에 대해서는 논의 필요)

	// 내부적으로 위협 상태 정보 값 : 전시할 필요가 없음.
    E_ES_NEW,									// 신규 처리 (상태정보로 활용함, 전시), 활동
	E_ES_UPDATE,								// 활동
	E_ES_LOST,									// 추적 실패(상태 값은 반영할 수 없다. LOB를 전송하지 않기 때문에)
	E_ES_DELETE,								// 미활동 처리
    E_ES_DEACTIVATED,                           // 활동 중지
    E_ES_REACTIVATED,                           // 활동 재개

};

//static const char* strBeamEmitterStat[] =
//{
//	"-",
//
//	"활동(신규)",
//	"활동",
//	"미활동",
//	"중지",
//	"활동(재개)",
//
//};

// 연동기와 지상 POSN간의 OPCODE 정보
enum E_EMITTER_OPCODE
{
	E_EO_NOT_AVAILABLE = 0,					// 객체가 생성되지 않은 경우 (필요성에 대해서는 논의 필요)

	// 아래 코드들은 해당 방사체/빔 목록창에 전시해야 함.
	E_MR_UPDATE_INFO,								// 변경 처리 (ELNOT, 위치 산출 등 변경), 방사체/빔 테이블에 데이터(ELNOT, 위치 산출 정보) 추가
	E_MR_REMOVE_AETABT,							// 방사체/빔 목록창에서 제거
	E_MR_REMOVE_LOB,								// LOB 목록창에서 제거

	// 아래 코드들은 해당 LOB 목록창에 전시해야 함.
	E_MR_CHANGE,										// (방사체/)빔/LOB 번호 변경

	//////////////////////////////////////////////////////////////////////////
	E_MR_UPDATE_STAT,								// 위협 상태 정보, (활동, 미활동 등)

	E_MR_ALERT_UPDATE,							// 경보 처리
	E_MR_REPORT_UPDATE,							// 보고서 처리

	E_MR_REMOVE_AET									// 방사체에서 해당 항목 제거

};

// static const char* strBeamEmitterOpcode[] =
// {
//  	"객제생성안됨",
//
// 	"갱신 ",
// 	"삭제(E/B)",
// 	"삭제(L) ",
//
// 	"변경 ",
// 	//////////////////////////////////////////////////////////////////////////
// 	"상태 ",
//
// 	"경보 ",
// 	"보고서",
//
// 	"삭제(E)",
//
// 	"상태 변동없음(NoChange)"
// };


struct STR_IDENTIFY {
	//int uiSeqNum;

	//////////////////////////////////////////////////////////////////////////
	// LOB 관리에 필요한 변수
    //int iLinkNum;																								// 수신한 위협 에미터의 링크 번호

	bool isFiltered;																						// 수집 필터 여부
	//bool isManualEdited;																				// 수동 편집 여부

	unsigned int uiAETID;
	unsigned int uiABTID;
	//unsigned int uiLOBID;

	unsigned int tiAcqTime;																						// 항공에서 분석 시간, LOB 메시지에 time_t 로 되어 있으면 삭제함.
	unsigned int tiContactTimems;																				// 항공에서 분석 시간

	E_BEAM_EMITTER_STAT enEmitterStat;													// LOB 상태

	unsigned int uiCoLOB;																				// LOB 개수

	int iBeamValidity;

	//////////////////////////////////////////////////////////////////////////
	// 식별 추가 정보
	//
	// 식별 후보 정보
	bool bOverCount;
	//int usCoCandidate;
	//int usThreatId[MAX_IDCANDIDATE];

    // 주파수 호핑의 레벨의 인덱스
    unsigned char idxHopping[MAX_FREQ_PRI_STEP];

    // 주파수 호핑의 레벨의 인덱스
    unsigned char idxDwell[MAX_FREQ_PRI_STEP];

	// 위협 레벨
	//unsigned short usPriorityLevel;

	// 일치율
	int iIdRatio[MAX_IDCANDIDATE];

	// 신규 CED 및 EOB로 식별한 정보
	STR_CEDEOBID_INFO idInfo;

	// 위치 산출 정보
	STR_POSITION_ESTIMATION peInfo;

	//char chELNOT[_MAX_ELNOT_STRING_SIZE_];					// MAX_SIZE_OF_ELNOT

	// EOB 거리 오차 [km]
	double dEOBErrorDistance;

	// 식별 대상
	//EnumLibType sIdObject;

	// 변조 코드
	//char modCode[MAX_SIZE_OF_MODULATIONCODE];

	E_BEAM_CODE eBeamCode;

	//bool bCompFreq;
	//bool bCompPRI;

} ;



/**
 * @typedef   SELLOBDATA_EXT
 * @brief     수신 위협 데이터 구조체 이외에 추가로 들어가는 구조체 정의
 * @author    조철희 (churlhee.jo@lignex1.com)
 */
struct SELLOBDATA_EXT {
	STR_IDENTIFY stIdentify;

	I_AET_DATA aetData;

} ;


struct STR_LOBDATAEXT {
	SRxLOBData stLOBData;
	SELLOBDATA_EXT stLOBDataExt;

}  ;

struct STR_ID_TYPE {
	int iSignalType;
	int iFrqType;
	int iPRIType;
	//int iScanType;
	//int iMOPType;

} ;

struct SELMANUALVAL {
    unsigned int doaInfo : 1;
    unsigned int freqInfo : 1;
    unsigned int priInfo : 1;
    unsigned int pwInfo : 1;
    unsigned int paInfo : 1;
    unsigned int idInfo : 1;
    unsigned int peInfo : 1;

    unsigned int _dummy : 25;

} ;


/**
 * @typedef   UELMANUALVAL
 * @brief     수동 편집 여부를 결정하기 위한 플레그 구조체
 * @author    조철희 (churlhee.jo@lignex1.com)
 */
union UELMANUALVAL {
    SELMANUALVAL x;
    unsigned int val32;

}  ;

enum ENUM_TRACK_PROCESS : unsigned int {
    enTRACK_NotProcessing = 0,				// 추적 초기 상태

    enTRACK_Requesting,					    // 추적 요청 상태
    enTRACK_Closing,

};

/**
    @enum  ENUM_SCAN_PROCESS
    @brief 빔의 스캔 상태 정보
**/
enum ENUM_SCAN_PROCESS {
    enSCAN_NotProcessing=0,                // 스캔 초기 상태

    enSCAN_Requesting,                     // 스캔 수집 요구 상태, 시도를 참고하여 계속 여부를 결정
    enSCAN_Collecting,                     // 스캔 수집 진행 상태
    enSCAN_Success,                        // 스캔 분석 성공으로 종료 상태
	enSCAN_Retrying,                       // 스캔 실패로 재시도 할 경우
	enSCAN_Stopping,                       // 스캔 완전 실패로 스캔 분석 중지

                                           // enSCAN_Canceling,
    // enSCAN_AlreadyDeleting,             // 이미 빔이 삭제 된 상태
	//enSCAN_Initializing,                 // 초기화 요청

	enSCAN_CANTProcessing,

} ;


/**
    @enum  ENUM_CHECK_SCAN_COLLECTING
    @brief 스캔 수집 단계 정보
**/
enum ENUM_CHECK_SCAN_COLLECTING {
    enNEXT_SCAN =0,
    enRETRY_SCAN,
    enSTOP_SCAN,

    enMISSING_SCAN

};

// 스캔 최대 수집 단계 개수
#define SCANCOLLECTION_STEP                     (5)

/**
 * @typedef   SELABTDATA_EXT
 * @brief     ABT 구조체 정의
 * @author    조철희 (churlhee.jo@lignex1.com)
 */
struct SELABTDATA_EXT {
    // 누적된 전체 PDW 개수
    //int nCoTotalPdw;
    //int nCoTotalIQ;

    // 인트라 변조 유무
    //bool bIntraMop;

    // 위치 산출 정보-Covariace 값
    //double dPECoVar[4];

    //float fLastAOA;
    //float fRadarLatitude;
    //float fRadarLongitude;

    // 수동 편집 여부
    //bool bIsManualEdited;

    // 방사체의 활동 상태를 저장
    enum E_BEAM_EMITTER_STAT enBeamEmitterStat;

    // 빔 유효성 갯수
    int nCoBeamValidity;

    // 수동 편집 여부 플레그
    //UELMANUALVAL xManualEdited;

#ifdef _ELINT_
// 	// FISINT용 과제
// 	//bool bIsFISINTTask;
// 	UINT uiOpInitID;
//
//     unsigned int uiSeqNum;

#elif defined(_POCKETSONATA_) || defined(_SONATA_) || defined(_712_)
    bool bReqTrack;                     // 위협 관리에서 추적 수행 여부를 결정하는 플레그

    unsigned int uiGlobalCh;                  // 추적 채널 정보
    ENUM_PCI_DRIVER enPCIDriver;
    ENUM_TRACK_PROCESS enTracking;                     // 추적 수집/분석을 결정하는 여부 플레그

#endif

	// 수동/자동 위치 결과 정보 여부
    //bool bManualPosEstPreferred;
    //float fManualLatitude;
    //float fManualLongitude;

    //SLOBOtherInfo stLOBOtherInfo;

    unsigned int uiLOBPoolIndex;

    //STR_ID_TYPE stIDType;

    ENUM_THREAT_PLATFORM enPlatform;

    //int nCoIdEOB;
    //STR_EOB_RESULT stEOBResult[MAX_CANDIDATE_EOB];

    // 빔 병합 정보
    //bool bCompFreq;
    //bool bCompPRI;

    // 신규 CED 및 EOB로 식별한 정보
    //STR_CEDEOBID_INFO idInfo;

    ENUM_PE_STAT enValid;
    bool bApplayOfLOBClustering;// TRUE: 적용, FALSE: 미적용

    UINT uiPE;
    bool bFullOfPE;
    double dLatitude[MAX_OF_LOBS_PE];
    double dLongitude[MAX_OF_LOBS_PE];
    double dEasting[MAX_OF_LOBS_PE];
    double dNorthing[MAX_OF_LOBS_PE];

    // 스캔 분석 추가 정보
    ENUM_SCAN_PROCESS enScanProcess;
    unsigned int uiScanTry;											///< 스캔 시도 횟수

    unsigned int uiScanCollectingStep;								///< 스캔 수집 시간 스텝수
    unsigned int uiLastScanCollectingStep;							///< 스캔 수집 시간 스텝수
    unsigned int uiRetryScanCollectingStep;							///< 스캔 수집 시간 스텝수

    bool bUserReqScan;                                              ///< 사용자 요구 스캔 플레그

    unsigned int uiReqScanPeriod[SCANCOLLECTION_STEP + 1];

    //bool bIsFISINTTask;
    // UINT uiOpInitID;

    //unsigned int uiSeqNum;

    unsigned uiOpcode;
    time_t tiSendLan;

    STR_IDENTIFY stIdentify;

} ;

struct SELAETDATA_EXT {
	// 누적된 전체 PDW 개수
	unsigned int uiCoPDWOfAnalysis;
	//int nCoTotalIQ;

	// 인트라 변조 유무
	// bool bIntraMop;

	// 방사체 간의 식별을 위한 정보
	//char szEOBELNOT[_MAX_ELNOT_STRING_SIZE_];					// EOB 상의 ELNOT

	// 방사체의 활동 상태를 저장
	enum E_BEAM_EMITTER_STAT enBeamEmitterStat;

	// 수동 편집 여부 플레그
	bool bIsManualEdited;

	bool bIsFISINTTask;

	// 수동 편집 정보
    UELMANUALVAL xMannualEdited;

	int iPinNumber;
	//char szELNOT[_MAX_ELNOT_STRING_SIZE_];

	//int iTaskType;		// 과제 형태

	// 여러개의 미식별 빔 중에서 대표 ABT 번호
	unsigned int uiUnIDABTID;

	// 수동/자동 위치 결과 정보 여부
	bool bManualPosEstPreferred;

    float fManualLatitude;
    float fManualLongitude;

    STR_CEDEOBID_INFO idInfo;


	unsigned int uiSeqNum;


} ;

struct STR_ABTDATAEXT {
	SRxLOBData stLOBData;
	SRxABTData stABTData;
	SELABTDATA_EXT stABTDataExt;

} ;


/*!
 * @typedef   SELIDENTIFICATION_INFO
 * @brief     신호 식별 옵션 창에 대한 구조체 정의 (GMI 병합 처리용 구조체)
 * @author    이정남(jeongnam.lee@lignex1.com)
 * @date      2016-02-13
 */
// typedef struct {
// 	SRxThreatData				stMsgData;		// 항공에서 수신된 메시지의 Data (Header) 정보
// 	SRxThreatDataGroup		stMsgDataGrp;	// 항공에서 수신된 메시지의 DataGrp 정보
// 	SPosEstData stPosEst;							// 지상에서 위치 산출한 정보
// 	I_AET stCDFAet;									// 신호 식별 입력 및 결과 정보
//
// } SELIDENTIFICATION_INFO_MR;

/*! Beam (ABT) 정보를 담고 있는 구조체
 * @struct     SBeamInfoFamily
 * @brief
 * @author    이정남 (jeongnam.lee@lignex1.com)
 * @date      2016-02-13 오전 8:28
 */
#define LENGTH_OF_GMI_CHAR 64
struct SThreatFamilyInfo
{
	E_EMITTER_OPCODE enOpcode;						// 연동기와 POSN간의 명령 값

	unsigned int nSeqNum;									// DB 테이블의 SEQ_NUM

	unsigned int iAETID;									// 방사체 #
	unsigned int iABTID;									// ABT #
	unsigned int iLOBID;									// LOB #

	bool bApplySearchFilter;							// ApplySearchFilterToAlarmAndMapDisplay() 함수 수행 여부

	bool bIsFISINTTask;										// FISINT용 과제

	// 경보 및 보고서 최초/최종 보고 시각
	time_t ti_FirstTime;									// 최초 시각
	time_t ti_FinalTime;								// 최종 시각(경보)

	E_BEAM_CODE eBeamCode;								// 빔 상태 전송, 디버깅을 위한 코드

	E_BEAM_EMITTER_STAT enEmitterStat;					// 위협 상태 정보

	unsigned int iChangedAETID;							// AET #
	unsigned int iChangedABTID;							// ABT #

        SThreatFamilyInfo() : enOpcode(E_EO_NOT_AVAILABLE), nSeqNum(0), iAETID(0), iABTID(0), iLOBID(0),
            bApplySearchFilter(false), bIsFISINTTask(false), ti_FirstTime(0), ti_FinalTime(0), eBeamCode(E_UNKNOWN_CODE), enEmitterStat(E_ES_NOT_AVAILABLE), iChangedAETID(0), iChangedABTID(0)
	{

	}

} ;



typedef struct SEmitterFilter
{
	bool bFrqUse;
	float fFrqMin;
	float fFrqMax;
	bool bPriUse;
	float fPriMin;
	float fPriMax;
	bool bPwUse;
	float fPwMin;
	float fPwMax;
        SEmitterFilter()
		:bFrqUse(false)
                ,fFrqMin(0.0)
                ,fFrqMax(0.0)
		,bPriUse(false)
                ,fPriMin(0.0)
                ,fPriMax(0.0)
		,bPwUse(false)
		,fPwMin(0.0)
		,fPwMax(0.0)
	{
	}
}I_EMITTER_FILTER;


struct SEmitterActivationInfo
{
	int nDetectYear; //초출 년도
	int nDetectMon; // 초출 월
	int nDetectDay; // 추촐 일
	int nDetectTimeHour;	// 초출 시각 (시)
	int nDetectTimeMin;		// 초출 시각 (분)
	int nDetectTimeSec;		// 초출 시각 (초)
	int nRecentUpdateTimeHour;  // 갱신 시각 (시)
	int nRecentUpdateTimeMin;	 // 갱신 시각 (분)
	int nRecentUpdateTimeSec;	 // 갱신 시각 (초)
	int nTotalActTimeHour;			// 총 활동 시간 (시)
	int nTotalActTimeMin;			 // 총 활동 시간 (분)
	int nTotalActTimeSec;			// 총 활동 시간 (초)
	bool bDeactivatedNow;			// 활동종료 여부
	int nDeactivatedTimeHour;			// 활동종료 시간 (시)
	int nDeactivatedTimeMin;			 // 활동종료 시간 (분)
	int nDeactivatedTimeSec;			// 활동종료 시간 (초)
	bool bTimeOfConvergenceIsValid; //
	int nTimeOfConvergenceHour;
	int nTimeOfConvergenceMin;
	int nTimeOfConvergenceSec;
	int nTimeOfConvergenceLobNum;
	int nNumOfDetectionToday;
	int nNumOfTotalLob;
	int nNumOfLobUsedToPosEst;
	int nNumOfTotalPdw;
	bool bIsSoi; // 관심신호인지. 2015.3.30. 이정남. 관심신호는 경보/연관과제 설정 신호인지의 의미임.
	int nFinalAircraftLatitude;
	int nFinalAircraftLongitude;
	int nFinalAircraftDoa;
	SEmitterActivationInfo()
		:nDetectYear(0),
		 nDetectMon(0),
	     nDetectDay(0),
		 nDetectTimeHour(0),
		 nDetectTimeMin(0),
		 nDetectTimeSec(0),
		 nRecentUpdateTimeHour(0),
		 nRecentUpdateTimeMin(0),
		 nRecentUpdateTimeSec(0),
		 nTotalActTimeHour(0),
		 nTotalActTimeMin(0),
		 nTotalActTimeSec(0),
		 bDeactivatedNow(false),
		 nDeactivatedTimeHour(0),
		 nDeactivatedTimeMin(0),
		 nDeactivatedTimeSec(0),
		 bTimeOfConvergenceIsValid(false),
		 nTimeOfConvergenceHour(0),
		 nTimeOfConvergenceMin(0),
		 nTimeOfConvergenceSec(0),
		 nTimeOfConvergenceLobNum(0),
		 nNumOfDetectionToday(0),
		 nNumOfTotalLob(0),
		 nNumOfLobUsedToPosEst(0),
		 nNumOfTotalPdw(0),
		 bIsSoi(false),
		 nFinalAircraftLatitude(0),
		 nFinalAircraftLongitude(0),
         nFinalAircraftDoa(0)
	{};
};

typedef struct stIdntfyReslt
{
    string strIdnfyRsltID;				// "0" 은 자동으로 DB에서 Unique 수로 할당
    string strDtctSigID;						// 단위 : 없음.
    string strIdnfyTime;					// 단위 : 시:분:초
	int	nRadarModeIndex;							// nRadarModeIndex
	int	nThreatIndex;
	int	nDeviceIndex;
	unsigned int uiBeamID;
	int uiLobID;
	int uiAetID;
    unsigned int uiCandidateNum;
    string strMsgAetID;
    string strElnotAir;
    string strElnotGnd;

    stIdntfyReslt()
        :strIdnfyRsltID("")
        ,strDtctSigID("")
        ,strIdnfyTime("")
        ,nRadarModeIndex(0)
        ,nThreatIndex(0)
        ,nDeviceIndex(0)
        ,uiBeamID(0)
		,uiLobID(0)
		,uiAetID(0)
        ,uiCandidateNum(0)
		,strMsgAetID("")
		,strElnotAir("")
		,strElnotGnd("")
	{
	};
}SELIdentify;

/**
 * @typedef   I_PDW_IQ_DATA
 * @brief     PDW 및 IQ 데이터 존재 여부를 보관하는 구조체
 * @author    조철희 (churlhee.jo@lignex1.com)
 */
typedef struct SPDWIQData
{
	bool bPDW;
	bool bIQ;
	SPDWIQData(){
		bIQ = false;
		bPDW = false;
	}
} I_PDW_IQ_DATA;

// 방사체/빔/LOB 상태 정의
#define _ACTIVE_STAT_						"활동"
#define _DEACTIVE_STAT_				"중지"
#define _REACTIVE_STAT_					"재개"
#define _DELETE_STAT_					"미활동"

/*! Emitter 정보를 담고 있는 구조체
 * @struct     SEmitterInfoFamily
 * @brief
 * @author    이정남 (jeongnam.lee@lignex1.com)
 * @date      2016-02-13 오전 8:28
 */
// struct SEmitterInfoFamily
// {
// 	E_BEAM_EMITTER_STAT eStat;					// Emitter Status
// 	char szEmitterIdGnd[LENGTH_OF_GMI_CHAR];							// 지상에서 정의한 Emitter Unique ID
// 	char szPastEmitterIdGnd[LENGTH_OF_GMI_CHAR];					// Emitter Status가 E_MR_NEW_BY_DEMERGE 인 경우, 이전 Emitter ID를 기입.
// 	SELIDENTIFICATION_INFO_MR stEmitter;	// 식별, 위치산출, 제원 등 Emitter 정보
//
// 	SEmitterInfoFamily(){
// 		memset(szEmitterIdGnd, 0, LENGTH_OF_GMI_CHAR);
// 		memset(szPastEmitterIdGnd, 0, LENGTH_OF_GMI_CHAR);
// 	}
// };

/*! Emitter 또는 Beam이 Merge로 인하여 Delete 대상이 생긴 경우, ID를 기록하기 위한 구조체
 * @struct     SDeleteID
 * @brief
 * @author    이정남 (jeongnam.lee@lignex1.com)
 * @date      2016-02-13 오전 8:40
 */
struct SDeleteID
{
	char szIdGnd[LENGTH_OF_GMI_CHAR];					// 삭제 대상인 ID. (Emitter  Unique ID 또는 Beam Unique ID)

	SDeleteID(){
		memset(szIdGnd, 0, LENGTH_OF_GMI_CHAR);
	}
} ;

// VER.3 목록창용 구조체 && ENUM 타입
enum E_GMI_PROC_MSG_INFO_TYPE
{
	E_GMI_LOB = 0,
	E_GMI_ABT,
	E_GMI_AET,
};

// #define LENGTH_OF_SHORT_CHAR 64
// #define LENGTH_OF_FRQ_OR_PRI_SEQ_CHAR 1024
// struct SLobInfoToWnd
// {
// 	unsigned long long ullSeqNum;
// 	char szMissionId[LENGTH_OF_MISSION_ID+1];
// 	char szMissionName[SIZE_OF_TASK_NAME];
// 	char szTaskId[LENGTH_OF_TASK_ID];
// 	char szTaskName[SIZE_OF_TASK_NAME];
// 	int nSearchBandId;
// 	char szTaskType[LENGTH_OF_SHORT_CHAR];
// 	char szDetAntDirection[LENGTH_OF_SHORT_CHAR];
// 	char szLinkNum[LENGTH_OF_SHORT_CHAR];
// 	char szAircraftNum[LENGTH_OF_SHORT_CHAR];
// 	char szRxPath[LENGTH_OF_SHORT_CHAR];
// 	unsigned int uiLobId;
// 	unsigned int uiAbtId;
// 	unsigned int uiAetId;
// 	char szElnotPri[LENGTH_OF_SHORT_CHAR];
// 	char szModeCodePri[LENGTH_OF_SHORT_CHAR];
// 	char szModulationCode[LENGTH_OF_SHORT_CHAR];
// 	char szNickName[LENGTH_OF_SHORT_CHAR];
// 	char szPriFuncCode[LENGTH_OF_SHORT_CHAR];
// 	char szElnotSec[LENGTH_OF_SHORT_CHAR];
// 	char szModeCodeSec[LENGTH_OF_SHORT_CHAR];
// 	char szElnotTert[LENGTH_OF_SHORT_CHAR];
// 	char szModeCodeTert[LENGTH_OF_SHORT_CHAR];
// 	char szSigType[LENGTH_OF_SHORT_CHAR];
// 	int iPolarization;
// 	char szPolarization[LENGTH_OF_SHORT_CHAR];
// 	int iRatioOfPOL;
// 	//int iIsFISINTTask;
// 	char szIsFISINTTask[LENGTH_OF_SHORT_CHAR];
//
// 	int nNumOfPPG;
// 	int nNumOfPulse;
// 	char szTimeInfo[LENGTH_OF_SHORT_CHAR];
// 	char szValidity[LENGTH_OF_SHORT_CHAR];
// 	char szBL[LENGTH_OF_SHORT_CHAR];
// 	int iFov;
// 	int iDoaMean; // 해상도 0.1 deg
// 	int iDoaMax;
// 	int iDoaMin;
// 	int iDoaDev;
// 	int iDoaStd;
// 	int iDIRatio;
// 	char szFrqType[LENGTH_OF_SHORT_CHAR];
// 	char szFrqPatternType[LENGTH_OF_SHORT_CHAR];
// 	char szHasFrqPeriod[LENGTH_OF_SHORT_CHAR];
// 	int nFrqPeriod; // 해상도 10khz
// 	int nFrqPositionCount;
// 	int nFrqElementCount;
// 	int nFrqMean; // 해상도 10khz
// 	int nFrqMax;
// 	int nFrqMin;
// 	int nFrqDev;
// 	int arrFrqSeq[MAX_FREQ_PRI_STEP];
// 	char szFrqSeq[LENGTH_OF_FRQ_OR_PRI_SEQ_CHAR];
// 	char szPriType[LENGTH_OF_SHORT_CHAR];
// 	char szPriPatternType[LENGTH_OF_SHORT_CHAR];
// 	char szHasPriPeriod[LENGTH_OF_SHORT_CHAR];
// 	int nPriPeriod; // us
// 	int nPriPositionCount;
// 	int nPriElementCount;
// 	int nPriMean;
// 	int nPriMax;
// 	int nPriMin;
// 	int nPriDev;
// 	int iPriJitterRatio;
// 	int arrPRISeq[MAX_FREQ_PRI_STEP];
// 	char szPRISeq[LENGTH_OF_FRQ_OR_PRI_SEQ_CHAR];
// 	int nPrfMean;
// 	int nPrfMax;
// 	int nPrfMin;
// 	int nPrfDev;
// 	int iPaMean;
// 	int iPaMax;
// 	int iPaMin;
// 	int iPaDev;
// 	int iPwMean;
// 	int iPwMax;
// 	int iPwMin;
// 	int iPwDev;
// 	char szScanType[LENGTH_OF_SHORT_CHAR];
// 	char szScanTypeDetail[LENGTH_OF_SHORT_CHAR];
// 	int nScanPeriodMicroSec;
// 	float fScanPeriodHz;
// 	char szIntraType[LENGTH_OF_SHORT_CHAR];
// 	char szIntraDetailType[LENGTH_OF_SHORT_CHAR];
// 	int nIntraFrqMean; // 10khz해상도
// 	int nIntraFrqMax;
// 	int nIntraFrqMin;
// 	int nIntraFrqChangeWidth;
// 	int arrPriPerGroup[MAX_PRI_PER_GROUP];
// 	int arrPaDiffPerGroup[MAX_PADIFF_PER_GROUP];
// 	int nAircraftLatitude;
// 	int nAircraftLongitude;
// 	int nAircraftPitch; // 0.1도 해상도
// 	int nAircraftRoll;
// 	int nAircraftHeading;
// 	int nAircraftAltitude;
// 	int nAircraftFOM;
// 	char szIsPDWRestored[LENGTH_OF_SHORT_CHAR];
// 	char szIsIQRestored[LENGTH_OF_SHORT_CHAR];
// 	char szFirstReportTime[LENGTH_OF_SHORT_CHAR];
// 	char szFinalReportTime[LENGTH_OF_SHORT_CHAR];
// 	char szStat[LENGTH_OF_SHORT_CHAR];
// 	int nHour;
// 	int nMin;
// 	int nSec;
// 	int nIsSelect;
// 	unsigned int nAirLobId;
// 	int nIsFiltered;
// 	unsigned int uiNewAbtId;
// 	unsigned int uiNewAetId;
// 	E_EMITTER_OPCODE eOpCodeForUpdate; // 업데이트 되는 내용이 다양해 져서, Update Key를 둬서 식별하기로 함.
//
// 	// 조철희, 시간 순으로 정렬하기 위해 추가된 함수
// 	bool operator<(const SLobInfoToWnd & other )
// 	{
// 		return strcmp( this->szTimeInfo, other.szTimeInfo ) < 0;
// 	}
//
// 	SLobInfoToWnd()
// 		:ullSeqNum(0),
// 		nSearchBandId(0),
// 	uiLobId(0),
// 	uiAbtId(0),
// 	uiAetId(0),
// 	iPolarization(0),
// 	iRatioOfPOL(0),
// 	nNumOfPPG(0),
// 	nNumOfPulse(0),
// 	iDoaMean(0), // 해상도 0.1 deg
// 	iDoaMax(0),
// 	iDoaMin(0),
// 	iDoaDev(0),
// 	iDoaStd(0),
// 	iDIRatio(0),
// 	iFov(0),
// 	nFrqPeriod(0), // 해상도 10khz
// 	nFrqPositionCount(0),
// 	nFrqElementCount(0),
// 	nFrqMean(0), // 해상도 10khz
// 	nFrqMax(0),
// 	nFrqMin(0),
// 	nFrqDev(0),
// 	nPriPeriod(0), // us
// 	nPriPositionCount(0),
// 	nPriElementCount(0),
// 	nPriMean(0),
// 	nPriMax(0),
// 	nPriMin(0),
// 	nPriDev(0),
// 	iPriJitterRatio(0),
// 	iPwMean(0),
// 	iPwMax(0),
// 	iPwMin(0),
// 	iPwDev(0),
// 	nPrfMean(0),
// 	nPrfMax(0),
// 	nPrfMin(0),
// 	nPrfDev(0),
// 	iPaMean(0),
// 	iPaMax(0),
// 	iPaMin(0),
// 	iPaDev(0),
// 	nScanPeriodMicroSec(0),
// 	fScanPeriodHz(0.0),
// 	nIntraFrqMean(0), // 10khz해상도
// 	nIntraFrqMax(0),
// 	nIntraFrqMin(0),
// 	nIntraFrqChangeWidth(0),
// 	nAircraftLatitude(0),
// 	nAircraftLongitude(0),
// 	nAircraftPitch(0), // 0.1도 해상도
// 	nAircraftRoll(0),
// 	nAircraftHeading(0),
// 	nAircraftAltitude(0),
// 	nAircraftFOM(0),
// 	nHour(0),
// 	nMin(0),
// 	nSec(0),
// 	nIsSelect(0),
// 	nAirLobId(0),
// 	nIsFiltered(0),
// 	uiNewAbtId(0),
// 	uiNewAetId(0),
// 	eOpCodeForUpdate(E_EO_NOT_AVAILABLE)
// 	{
// 		memset(szMissionId, 0, LENGTH_OF_MISSION_ID+1);
// 		memset(szMissionName, 0,SIZE_OF_TASK_NAME);
// 		memset(szTaskId, 0,LENGTH_OF_TASK_ID);
// 		memset(szTaskName, 0,SIZE_OF_TASK_NAME);
// 		memset(szTaskType, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szDetAntDirection, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szLinkNum, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szAircraftNum, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szElnotPri, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szModeCodePri, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szModulationCode, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szNickName, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szPriFuncCode, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szElnotSec, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szModeCodeSec, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szElnotTert, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szModeCodeTert, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szSigType, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szTimeInfo, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szValidity, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szBL, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szFrqType, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szFrqPatternType, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szHasFrqPeriod, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szPriType, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szPriPatternType, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szHasPriPeriod, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szScanType, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szScanTypeDetail, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szIntraType, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szIntraDetailType, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szIsPDWRestored, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szIsIQRestored, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szFirstReportTime, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szFinalReportTime, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szStat, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(arrFrqSeq, 0, MAX_FREQ_PRI_STEP*sizeof(int));
// 		memset(arrPRISeq, 0, MAX_FREQ_PRI_STEP*sizeof(int));
// 		memset(arrPriPerGroup, 0, MAX_PRI_PER_GROUP*sizeof(int));
// 		memset(arrPaDiffPerGroup, 0, MAX_PADIFF_PER_GROUP*sizeof(int));
// 		memset(szIsFISINTTask, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szPRISeq, 0, LENGTH_OF_FRQ_OR_PRI_SEQ_CHAR);
// 		memset(szFrqSeq, 0, LENGTH_OF_FRQ_OR_PRI_SEQ_CHAR);
// 		memset(szPolarization, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szRxPath, 0, LENGTH_OF_SHORT_CHAR);//LDRA추가
//
// 	}
// };
//
// struct SAbtInfoToWnd
// {
// 	unsigned long long ullSeqNum;
// 	char szMissionId[LENGTH_OF_MISSION_ID+1];
// 	char szMissionName[SIZE_OF_TASK_NAME];
// 	unsigned int uiAbtId;
// 	unsigned int uiAetId;
// 	int iRadarModeIndex;
// 	int iThreatIndex;
// 	char szTaskType[LENGTH_OF_SHORT_CHAR];
// 	char szElnotPri[LENGTH_OF_SHORT_CHAR];
// 	char szModeCodePri[LENGTH_OF_SHORT_CHAR];
// 	char szModulationCode[LENGTH_OF_SHORT_CHAR];
// 	char szNickName[LENGTH_OF_SHORT_CHAR];
// 	char szPriFuncCode[LENGTH_OF_SHORT_CHAR];
// 	char szPlatform[LENGTH_OF_SHORT_CHAR];
// 	char szPlaceNameKor[LENGTH_OF_SHORT_CHAR]; // 2018-02-22 한글지명 추가
// 	int nRadarModePriority;
// 	float fDistanceErrFromThreat;
// 	int nRadarPriority;
// 	char szSigType[LENGTH_OF_SHORT_CHAR];
// 	int nNumOfPPG;
// 	int nNumOfLOB;
// 	int iDoaMean; // 해상도 0.1 deg
// 	int iDoaMax;
// 	int iDoaMin;
// 	int iDoaDev;
// 	int iDoaStd;
// 	char szFirstDetectTimeInfo[LENGTH_OF_SHORT_CHAR];
// 	char szFinalDetectTimeInfo[LENGTH_OF_SHORT_CHAR];
// 	char szValidity[LENGTH_OF_SHORT_CHAR];
// 	char szFrqType[LENGTH_OF_SHORT_CHAR];
// 	char szFrqPatternType[LENGTH_OF_SHORT_CHAR];
// 	char szHasFrqPeriod[LENGTH_OF_SHORT_CHAR];
// 	int nFrqPeriodMean; // 해상도 10khz
// 	int nFrqPeriodMax; // 해상도 10khz
// 	int nFrqPeriodMin; // 해상도 10khz
// 	int nFrqPositionCount;
// 	int nFrqElementCount;
// 	int nFrqMean; // 해상도 10khz
// 	int nFrqMax;
// 	int nFrqMin;
// 	int nFrqDev;
// 	int arrFrqElement[64];
// 	char szFrqElement[LENGTH_OF_FRQ_OR_PRI_SEQ_CHAR];
// 	char szPriType[LENGTH_OF_SHORT_CHAR];
// 	char szPriPatternType[LENGTH_OF_SHORT_CHAR];
// 	char szHasPriPeriod[LENGTH_OF_SHORT_CHAR];
// 	int nPriPeriodMean; // us
// 	int nPriPeriodMax; // us
// 	int nPriPeriodMin; // us
// 	int nPriPositionCount;
// 	int nPriElementCount;
// 	int nPriMean;
// 	int nPriMax;
// 	int nPriMin;
// 	int nPriDev;
// 	int iPriJitterRatio;
// 	int arrPriElement[64];
// 	char szPriElement[LENGTH_OF_FRQ_OR_PRI_SEQ_CHAR];
// 	int nPwMean;
// 	int nPwMax;
// 	int nPwMin;
// 	int nPwDev;
// 	int nPaMean;
// 	int nPaMax;
// 	int nPaMin;
// 	int nPaDev;
// 	char szScanType[LENGTH_OF_SHORT_CHAR];
// 	int nScanPeriodMinMicroSec;
// 	int nScanPeriodMaxMicroSec;
// 	float fScanPeriodMinHz;
// 	float fScanPeriodMaxHz;
// 	char szHasIntraModulation[LENGTH_OF_SHORT_CHAR];
// 	int nIntraFrqChangeWidthMin;
// 	int nIntraFrqChangeWidthMax;
// 	int arrPriPerGroup[MAX_PRI_PER_GROUP];
// 	int arrPaDiffPerGroup[MAX_PADIFF_PER_GROUP];
// 	// 위치산출 관련
// 	int nPosEstLat;
// 	int nPosEstLong;
// 	int nManualPosEstLat;
// 	int nManualPosEstLong;
// 	int nRepresentPosEstLat;
// 	int nRepresentPosEstLong;
// 	int nAltitude; // meter
// 	int nCEP;// meter
// 	int nLengthOfMajorAxis; // meter
// 	int nLengthOfMinorAxis;
// 	int nEEPTiltAngle; // 0.1도 해상도
// 	int nManualPosEstPreferred; // 수동위치산출을 우선한다는 indicator.
// 	unsigned int uiNewAetId;
// 	E_EMITTER_OPCODE eOpCodeForUpdate; // 업데이트 되는 내용이 다양해 져서, Update Key를 둬서 식별하기로 함.
//
// 	char szFirstReportTime[LENGTH_OF_SHORT_CHAR];
// 	char szFinalReportTime[LENGTH_OF_SHORT_CHAR];
// 	char szFinalAlarmTime[LENGTH_OF_SHORT_CHAR];
// 	char szPolarization[LENGTH_OF_SHORT_CHAR];
// 	char szStat[LENGTH_OF_SHORT_CHAR];
//
// 	SAbtInfoToWnd()
// 		:ullSeqNum(0),
// 	uiAbtId(0),
// 	uiAetId(0),
// 	iRadarModeIndex(0), //LDRA추가
// 	iThreatIndex(0),//LDRA추가
// 	nRadarModePriority(0),
// 	fDistanceErrFromThreat(0.0),
// 	nRadarPriority(0),
// 	nNumOfPPG(0),
// 	nNumOfLOB(0),
// 	iDoaMean(0), // 해상도 0.1 deg
// 	iDoaMax(0),
// 	iDoaMin(0),
// 	iDoaDev(0),
// 	iDoaStd(0),
// 	nFrqPeriodMean(0), // 해상도 10khz
// 	nFrqPeriodMax(0), // 해상도 10khz
// 	nFrqPeriodMin(0), // 해상도 10khz
// 	nFrqPositionCount(0),
// 	nFrqElementCount(0),
// 	nFrqMean(0), // 해상도 10khz
// 	nFrqMax(0),
// 	nFrqMin(0),
// 	nFrqDev(0),
// 	nPriPeriodMean(0), // us
// 	nPriPeriodMax(0), // us
// 	nPriPeriodMin(0), // us
// 	nPriPositionCount(0),
// 	nPriElementCount(0),
// 	nPriMean(0),
// 	nPriMax(0),
// 	nPriMin(0),
// 	nPriDev(0),
// 	iPriJitterRatio(0),
// 	nPwMean(0),
// 	nPwMax(0),
// 	nPwMin(0),
// 	nPwDev(0),
// 	nPaMean(0),
// 	nPaMax(0),
// 	nPaMin(0),
// 	nPaDev(0),
// 	nScanPeriodMinMicroSec(0),
// 	nScanPeriodMaxMicroSec(0),
// 	fScanPeriodMinHz(0),
// 	fScanPeriodMaxHz(0),
// 	nIntraFrqChangeWidthMin(0),
// 	nIntraFrqChangeWidthMax(0),
// 	nPosEstLat(0),
// 	nPosEstLong(0),
// 	nManualPosEstLat(0),
// 	nManualPosEstLong(0),
// 	nRepresentPosEstLat(0),
// 	nRepresentPosEstLong(0),
// 	nAltitude(0), // meter
// 	nCEP(0),// meter
// 	nLengthOfMajorAxis(0), // meter
// 	nLengthOfMinorAxis(0),
// 	nEEPTiltAngle(0),  // 0.1도 해상도
// 	nManualPosEstPreferred(0),
// 	uiNewAetId(0),
// 	eOpCodeForUpdate(E_EO_NOT_AVAILABLE)
// 	{
// 		//@start_이시온
// 		memset(szMissionId, 0,LENGTH_OF_MISSION_ID+1);
// 		memset(szMissionName, 0,SIZE_OF_TASK_NAME);
// 		memset(szTaskType, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szElnotPri, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szModeCodePri, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szModulationCode, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szNickName, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szPriFuncCode, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szPlatform, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szSigType, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szFirstDetectTimeInfo, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szFinalDetectTimeInfo, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szValidity, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szFrqType, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szFrqPatternType, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szHasFrqPeriod, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(arrFrqElement, 0, 64);
// 		memset(szFrqElement,0,LENGTH_OF_FRQ_OR_PRI_SEQ_CHAR);
// 		memset(szPriType, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szPriPatternType, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szHasPriPeriod, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(arrPriElement,0, 64);
// 		memset(szPriElement, 0, LENGTH_OF_FRQ_OR_PRI_SEQ_CHAR);
// 		memset(szScanType, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(szHasIntraModulation, 0,LENGTH_OF_SHORT_CHAR);
// 		memset(arrPriPerGroup, 0, sizeof(int)*MAX_PRI_PER_GROUP);
// 		memset(arrPaDiffPerGroup, 0, sizeof(int)*MAX_PADIFF_PER_GROUP);
// 		memset(szFirstReportTime,0, LENGTH_OF_SHORT_CHAR);
// 		memset(szFinalReportTime,0, LENGTH_OF_SHORT_CHAR);
// 		memset(szFinalAlarmTime,0, LENGTH_OF_SHORT_CHAR);
// 		memset(szPolarization, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szStat, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szPlaceNameKor, 0, LENGTH_OF_SHORT_CHAR);
// 		//@end_이시온
// 	}
// };
//
// struct SAetInfoToWnd
// {
// 	unsigned long long ullSeqNum;
// 	char szMissionId[LENGTH_OF_MISSION_ID+1];
// 	char szMissionName[SIZE_OF_TASK_NAME];
// 	char szTaskType[LENGTH_OF_SHORT_CHAR];
// 	unsigned int uiAetId;
//
// 	//CED 관련 정보
// 	int iRadarIndex;
// 	int iThreatIndex;
// 	char szElnotPri[LENGTH_OF_SHORT_CHAR];
// 	char szIdResult[LENGTH_OF_SHORT_CHAR];
// 	char szNickName[LENGTH_OF_SHORT_CHAR];
// 	char szPriFuncCode[LENGTH_OF_SHORT_CHAR];
// 	int nRadarPriority;
//
// 	//EOB 관련
// 	unsigned int uiPinNum;
// 	char szThreatName[LENGTH_OF_SHORT_CHAR];
// 	char szBENumber[LENGTH_OF_SHORT_CHAR];
// 	char szThreatFuncCode[LENGTH_OF_SHORT_CHAR];
// 	int nThreatPriority;
// 	float fDistanceErrFromThreat; // Nautical Mile
// 	int iEquipNumber;
// 	//char szEquipNumber[LENGTH_OF_SHORT_CHAR];
//
// 	int nNumOfLOB;
// 	int nNumOfBeam;
// 	char szFirstDetectTimeInfo[LENGTH_OF_SHORT_CHAR];
// 	char szFinalDetectTimeInfo[LENGTH_OF_SHORT_CHAR];
// 	char szValidity[LENGTH_OF_SHORT_CHAR];
// 	int nFrqMean; // 해상도 10khz
// 	int nFrqMax;
// 	int nFrqMin;
// 	int nFrqDev;
// 	int nPriMean;
// 	int nPriMax;
// 	int nPriMin;
// 	int nPriDev;
// 	int nPrfMean;
// 	int nPrfMax;
// 	int nPrfMin;
// 	int nPrfDev;
// 	int nPrfMinPPS;
// 	int nPrfMaxPPS;
// 	int nPwMean;
// 	int nPwMax;
// 	int nPwMin;
// 	int nPwDev;
// 	int nPaMean;
// 	int nPaMax;
// 	int nPaMin;
// 	int nPaDev;
// 	// 위치산출 관련
// 	char szPosEstValidity[LENGTH_OF_SHORT_CHAR];
// 	int nPosEstLat; // 자동으로 갱신되는 위치 산출값
// 	int nPosEstLong; // 자동으로 갱신되는 위치 산출값
// 	int nManualPosEstLat; // 고정된 수동위치 산출값
// 	int nManualPosEstLong; // 고정된 수동위치 산출값
// 	int nRepresentPosEstLat; // 대표 위치 위도
// 	int nRepresentPosEstLong; // 대표 위치 경도
// 	int nAltitude; // meter
// 	int nCEP;// meter
// 	int nLengthOfMajorAxis; // meter
// 	int nLengthOfMinorAxis;
// 	int nEEPTiltAngle; // 0.1도 해상도
// 	int nManualPosEstPreferred; // 수동위치산출을 우선한다는 indicator.
//
// 	E_EMITTER_OPCODE eOpCodeForUpdate; // 업데이트 되는 내용이 다양해 져서, Update Key를 둬서 식별하기로 함.
// 	char szManualPosEstPreferred[LENGTH_OF_SHORT_CHAR];
// 	char szFirstReportTime[LENGTH_OF_SHORT_CHAR];
// 	char szFinalReportTime[LENGTH_OF_SHORT_CHAR];
// 	char szFinalAlarmTime[LENGTH_OF_SHORT_CHAR];
//
// 	char szStat[LENGTH_OF_SHORT_CHAR];
//
// 	SAetInfoToWnd()
// 	:ullSeqNum(0)
// 	 ,uiAetId(0)
// 	 ,iRadarIndex(0)
// 	 ,iThreatIndex(0)
// 	 ,nRadarPriority(0)
// 	 ,uiPinNum(0)
// 	 ,nThreatPriority(0)
// 	 ,fDistanceErrFromThreat(0.0) // Nautical Mile
// 	 ,iEquipNumber(0)
// 	 ,nNumOfLOB(0)
// 	 ,nNumOfBeam(0)
// 	 ,nFrqMean(0) // 해상도 10khz
// 	 ,nFrqMax(0)
// 	 ,nFrqMin(0)
// 	 ,nFrqDev(0)
// 	 ,nPriMean(0)
// 	 ,nPriMax(0)
// 	 ,nPriMin(0)
// 	 ,nPriDev(0)
// 	 ,nPrfMean(0)
// 	 ,nPrfMax(0)
// 	 ,nPrfMin(0)
// 	 ,nPrfDev(0)
// 	 ,nPrfMinPPS(0)
// 	 ,nPrfMaxPPS(0)
// 	 ,nPwMean(0)
// 	 ,nPwMax(0)
// 	 ,nPwMin(0)
// 	 ,nPwDev(0)
// 	 ,nPaMean(0)
// 	 ,nPaMax(0)
// 	 ,nPaMin(0)
// 	 ,nPaDev(0)
// 	 ,nPosEstLat(0)
// 	 ,nPosEstLong(0)
// 	 ,nManualPosEstLat(0)
// 	 ,nManualPosEstLong(0)
// 	 ,nRepresentPosEstLat(0)
// 	 ,nRepresentPosEstLong(0)
// 	 ,nAltitude(0) // meter
// 	 ,nCEP(0)// meter
// 	 ,nLengthOfMajorAxis(0) // meter
// 	 ,nLengthOfMinorAxis(0)
// 	 ,nEEPTiltAngle(0) // 0.1도 해상도
// 	 ,nManualPosEstPreferred(0)
// 	 ,eOpCodeForUpdate(E_EO_NOT_AVAILABLE)
// 	 //,szManualPosEstPreferred(0)
// 	{
// 		//@start_이시온
// 		memset(szMissionId, 0, LENGTH_OF_MISSION_ID+1);
// 		memset(szMissionName, 0, SIZE_OF_TASK_NAME);
// 		memset(szTaskType, 0, SIZE_OF_TASK_NAME);
// 		memset(szElnotPri, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szIdResult, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szNickName, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szPriFuncCode, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szThreatName, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szBENumber, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szThreatFuncCode, 0, LENGTH_OF_SHORT_CHAR);
// 		//memset(szEquipNumber, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szFirstDetectTimeInfo, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szFinalDetectTimeInfo, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szValidity, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szPosEstValidity, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szManualPosEstPreferred, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szFirstReportTime, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szFinalReportTime, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szFinalAlarmTime, 0, LENGTH_OF_SHORT_CHAR);
// 		memset(szStat, 0, LENGTH_OF_SHORT_CHAR);
//
// 		//@end_이시온
//
// 	}
// };

// GUI->LOGIC
// struct SCommonListWndSelect
// {
// 	int nAetId;
//     int nAbtId;
// 	int nLobId;
// 	std::string strRecentTime;
// 	SCommonListWndSelect()
// 	:nAetId(0)
// 	,nAbtId(0)
// 	,nLobId(0)
// 	,strRecentTime("")
//     {}
// };


#define NUM_OF_MANUAL_INPUT_COUNT	_	36

#define DF_MANUAL_SIG_SIGTYPE				(0x0000000000000001)		/*신호형태-----*/
#define DF_MANUAL_SIG_MODTYPE				(0x0000000000000002)		/*변조형태-----*/
#define DF_MANUAL_SIG_POLARIZATION		(0x0000000000000004)		/*극성*/
#define DF_MANUAL_DOA_MEAN					(0x0000000000000008)		/*방위각 평균-----*/
#define DF_MANUAL_DOA_MAX					(0x0000000000000010)		/*방위각 최대-----*/
#define DF_MANUAL_DOA_MIN						(0x0000000000000020)		/*방위각 최소-----*/
#define DF_MANUAL_POSEST_NS					(0x0000000000000040)		/*NS*/
#define DF_MANUAL_POSEST_LAT				(0x0000000000000080)		/*위도*/
#define DF_MANUAL_POSEST_EW					(0x0000000000000100)		/*EW*/
#define DF_MANUAL_POSEST_LONG				(0x0000000000000200)		/*경도*/
#define DF_MANUAL_FRQ_FRQTYPE				(0x0000000000000400)		/*주파수 형태-----*/
#define DF_MANUAL_FRQ_MEAN					(0x0000000000000800)		/*주파수 평균-----*/
#define DF_MANUAL_FRQ_MAX						(0x0000000000001000)		/*주파수 최대-----*/
#define DF_MANUAL_FRQ_MIN						(0x0000000000002000)		/*주파수 최소-----*/
#define DF_MANUAL_FRQ_CHNG_WIDTH		(0x0000000000004000)		/*주파수 변경폭*/
#define DF_MANUAL_FRQ_PERIOD				(0x0000000000008000)		/*주기-----*/
#define DF_MANUAL_FRQ_STEP					(0x0000000000010000)		/*단수*/
#define DF_MANUAL_FRQ_LEVEL					(0x0000000000020000)		/*레벨*/
#define DF_MANUAL_PRI_PRITYPE					(0x0000000000040000)		/*PRI 형태-----*/
#define DF_MANUAL_PRI_MEAN					(0x0000000000080000)		/*PRI 평균-----*/
#define DF_MANUAL_PRI_MAX						(0x0000000000100000)		/*PRI 최대-----*/
#define DF_MANUAL_PRI_MIN						(0x0000000000200000)		/*PRI 최소-----*/
#define DF_MANUAL_PRI_CHNG_WIDTH		(0x0000000000400000)		/*PRI 변경폭*/
#define DF_MANUAL_PRI_PERIOD					(0x0000000000800000)		/*주기-----*/
#define DF_MANUAL_PRI_STEP						(0x0000000001000000)		/*단수*/
#define DF_MANUAL_PRI_CHNG_RATIO			(0x0000000002000000)		/*PRI 변경률*/
#define DF_MANUAL_PRI_LEVEL					(0x0000000004000000)		/*레벨*/
#define DF_MANUAL_ELNOT							(0x0000000008000000)		/*ELNOT-----*/
#define DF_MANUAL_PA_MEAN						(0x0000000010000000)		/*PA 평균-----*/
#define DF_MANUAL_PA_MAX						(0x0000000020000000)		/*PA 최대-----*/
#define DF_MANUAL_PA_MIN						(0x0000000040000000)		/*PA 최소-----*/
#define DF_MANUAL_PA_SCAN_TYPE				(0x0000000080000000)		/*스캔타입-----*/
#define DF_MANUAL_PA_SCAN_PERIOD			(0x0000000100000000)		/*스캔주기*/
#define DF_MANUAL_PW_MEAN					(0x0000000200000000)		/*PW 평균*/
#define DF_MANUAL_PW_MAX					(0x0000000400000000)		/*PW 최대*/
#define DF_MANUAL_PW_MIN						(0x0000000800000000)		/*PW 최소*/
#define DF_MANUAL_PIN_NUM					(0x000000100000000)			/*PIN NUMBER _ 2015.10.31. 추가*/

struct SFLTMData
{
	int nFrqType;
	int nPriType;
	int nMeanFrq;
	int nMeanPri;
	int nMeanPw;
	int nMeanPa;
	int nMeanDoa;
	int nAntDir;
        SFLTMData()
		:nFrqType(0)
		,nPriType(0)
		,nMeanFrq(0)
		,nMeanPri(0)
		,nMeanPw(0)
		,nMeanPa(0)
		,nMeanDoa(0)
		,nAntDir(0)
	{};
};


//////////////////////////////////////////////////////////////////////////
// 방사체/빔/LOB 창에서 CED/EOB 창으로 데이터를 전달하기 위한 구조체 정의
// typedef struct {
// 	SRadar stSRadar;
// 	EnumLibType enLibType;
//
// } SELCALLCEDLIB;

// CED 생성시 참조되는 인자
// typedef struct {
// 	int nAETId;
// 	int nABTId;
//
// 	char szMissionId[LENGTH_OF_MISSION_ID+2];
//
// } SELCEDCREATE ;


struct SELCHECKRANGE {
	bool bCheckBox;
	float low;
	float high;
} ;

enum EnumRangeSearchRef {
	enumIncludeAllInput=0,						// 입력범위를 모두포함
	enumOverlapWithInnerInput,				// 입력 범위 내부에 중첩
	enumOverlapWithInput							// 입력 범위와 중첩

} ;


// typedef struct {
// 	//EnumLibType enLibType;	// 기본형 또는 실무형
//
// 	CString strELNOT;
// 	CString strNickName;
// 	int iPin;
// 	EnumFunctionCodes eFunctionCodes_ForGUI;	// 주기능 코드
// 	EnumRadarStatus eStatus;									// 상태
// 	CString strAssocWeapSys;									// 연관 무기 체계
// 	CString strAssocPlatform;									// 연관 플레폼
//
// 	EnumRangeSearchRef eRangeSearchRef;			// 범위 검색 기준
//
// 	SELCHECKRANGE stFreq;											// 주파수 범위
// 	SELCHECKRANGE stPRI;											// PRI 범위
// } SELRADARLIST_SEARCH_FILTER;


struct SELRANGE {
	int low;
	int high;
} ;

// typedef struct stSELRADARMODELIST_SEARCH_FILTER{
// 	EnumLibType enLibType;	// 기본형 또는 실무형
//
// 	// 방사체
// 	CString strELNOT;
// 	CString strNickName;
// 	int iPin;
// 	EnumRadarStatus eStatus;									// 상태
// 	CString strAssocWeapSys;									// 연관 무기 체계
// 	CString strAssocPlatform;									// 연관 플레폼
//
// 	// 모드제원
// 	PlatformCode::EnumPlatformCode ePlatform;
// 	EnumValidationCode eValidation;
// 	EnumFunctionCodes	eFunctionCode;	// 주기능 코드
// 	SignalType::EnumSignalType eSignalType;									//신호형태 (Pulsed, CW, EA) enum형태
// 	ScanType::EnumScanType	eScanPrimaryType;								//주 스캔타입 코드(SCAN_TYPE_CODE 참조)
// 	CString strModulationCode;												//* 변조코드(2) [계산필요]
// 	PolizationCode::EnumPolizationCode ePolarization;
// 	EnumRangeSearchRef eRangeSearchRef;
// 	float fRF_TypicalMin;													//주관측범위: 주파수 Typical 최소(MHz)
// 	float fRF_TypicalMax;													//주관측범위: 주파수 Typical 최대(MHz)
// 	float fPRI_TypicalMin;													//PRI TYPICAL (USEC) 최소
// 	float fPRI_TypicalMax;													//PRI TYPICAL (USEC) 최대
// 	float fScanPrimaryTypicalMin;											//주 스캔 주기값의 TYPICAL (SEC) 최소
// 	float fScanPrimaryTypicalMax;											//주 스캔 주기값의 TYPICAL (SEC) 최대
// 	float fPD_TypicalMin;													//PD TYPICAL 값 (USEC) 최소
// 	float fPD_TypicalMax;													//PD TYPICAL 값 (USEC) 최대
//
// 	// 주파수
// 	ContinuityCode::EnumContinuityCode eRF_Continuity;						//주파수 값분포연속성: RF 변화의 연속성 (CONTINUITY_CODE 참조)
// 	PatternCode::EnumPatternCode eRF_Pattern;								//RF 변화의 패턴 여부 (PATTERN_CODE 참조)
// 	EnumRF_LagacyTypeCode eRF_LagacyType;									//RF_LEGACY_TYPE_CODE 참조
// 	SELRANGE stRF_NumElements;													//NUMBER	PRI ELEMENT 수
// 	SELRANGE stRF_NumPositions;													//NUMBER	PRI POSITION 수
//
// 	// PD
// 	ContinuityCode::EnumContinuityCode ePD_Continuity;						//PD값의 연속성 (CONTINUITY_CODE 참조)
// 	PatternCode::EnumPatternCode ePD_Pattern;								//PD값의 패턴여부 (PATTERN_CODE 참조)
// 	SELRANGE stPD_NumElements;													//PD ELEMENT 수
// 	SELRANGE stPD_NumPositions;													//PD Positon 수
// 	float fPD_PatternPeriodMin;												//PD 패턴주기 (USEC) 최소
// 	float fPD_PatternPeriodMax;												//PD 패턴주기 (USEC) 최대
//
// 	// PRI
// 	ContinuityCode::EnumContinuityCode ePRI_Continuity;						//PRI 변화의 연속성 (CONTINUITY_CODE 참조)
// 	PatternCode::EnumPatternCode ePRI_Pattern;								//NUMBER PRI변화의 패턴여부	(PATTERN_CODE 참조)
// 	EnumPRI_LegacyTypeCode ePRI_LagacyType;									//PRI_LAGACY_TYPE_CODE 참조
// 	SELRANGE stPRI_NumElements;													//NUMBER	PRI ELEMENT 수
// 	SELRANGE stPRI_NumPositions;													//NUMBER	PRI POSITION 수
// 	float fPRI_FramePeriodMin;												//PRI FRAME 주기 (USEC) 최소
// 	float fPRI_FramePeriodMax;												//PRI FRAME 주기 (USEC) 최대
// 	float fPRI_SubframePeriodMin;											//PRI SUBFRAME 주기 (USEC) 최소
// 	float fPRI_SubframePeriodMax;											//PRI SUBFRAME 주기 (USEC) 최대
// 	float fPRI_PPG_Min;														//Pulse Per Group 최소
// 	float fPRI_PPG_Max;														//Pulse Per Group 최대
//
// 	// 펄스내 변조
// 	MOP_CW_ModulationType::EnumMOP_CW_ModulationType eMOP_CW_ModulationType;	//펄스 내 또는 CW 변조형태 (MOP_CW_MOD_TYPE_CODE 참조)
// 	EnumMOP_CW_LegacyType eMOP_CW_LegacyType;					//변조형태의 LEGACY TERM (MOP_CW_LEGACY_TYPE_CODE)
//
// 	stSELRADARMODELIST_SEARCH_FILTER()
// 	{
// 		enLibType = E_EL_LIB_TYPE_NORMAL;	// 기본형 또는 실무형
//
// 		// 방사체
// 		strELNOT="";
// 		strNickName="";
// 		iPin = 0;
// 		eStatus = enumUndefinedRadarStatus;									// 상태
// 		strAssocWeapSys="";									// 연관 무기 체계
// 		strAssocPlatform="";									// 연관 플레폼
//
// 		// 모드제원
// 		ePlatform = PlatformCode::enumUndefinedPlatformCode;
// 		eValidation=enumUndefinedValidationCode;
// 		eFunctionCode=enumUndefinedFunctionCode;	// 주기능 코드
// 		eSignalType=SignalType::enumSignalUndefined;									//신호형태 (Pulsed, CW, EA) enum형태
// 		eScanPrimaryType=ScanType::enumUndefinedScanType;								//주 스캔타입 코드(SCAN_TYPE_CODE 참조)
// 		strModulationCode="";												//* 변조코드(2) [계산필요]
// 		ePolarization=PolizationCode::enumUndefinedPolization;
// 		eRangeSearchRef=enumIncludeAllInput;
// 		fRF_TypicalMin=0.0f;													//주관측범위: 주파수 Typical 최소(MHz)
// 		fRF_TypicalMax=0.0f;													//주관측범위: 주파수 Typical 최대(MHz)
// 		fPRI_TypicalMin=0.0f;													//PRI TYPICAL (USEC) 최소
// 		fPRI_TypicalMax=0.0f;													//PRI TYPICAL (USEC) 최대
// 		fScanPrimaryTypicalMin=0.0f;											//주 스캔 주기값의 TYPICAL (SEC) 최소
// 		fScanPrimaryTypicalMax=0.0f;											//주 스캔 주기값의 TYPICAL (SEC) 최대
// 		fPD_TypicalMin=0.0f;													//PD TYPICAL 값 (USEC) 최소
// 		fPD_TypicalMax=0.0f;													//PD TYPICAL 값 (USEC) 최대
//
// 		// 주파수
// 		eRF_Continuity=ContinuityCode::enumUndefinedContinuityCode;						//주파수 값분포연속성: RF 변화의 연속성 (CONTINUITY_CODE 참조)
// 		eRF_Pattern=PatternCode::enumUndefinedPatternCode;								//RF 변화의 패턴 여부 (PATTERN_CODE 참조)
// 		eRF_LagacyType=enumUndefinedRF_LagacyType;									//RF_LEGACY_TYPE_CODE 참조
// 		stRF_NumElements = SELRANGE();													//NUMBER	PRI ELEMENT 수
// 		stRF_NumPositions = SELRANGE();													//NUMBER	PRI POSITION 수
//
// 		// PD
// 		ePD_Continuity=ContinuityCode::enumUndefinedContinuityCode;						//PD값의 연속성 (CONTINUITY_CODE 참조)
// 		ePD_Pattern=PatternCode::enumUndefinedPatternCode;								//PD값의 패턴여부 (PATTERN_CODE 참조)
// 		stPD_NumElements = SELRANGE();													//PD ELEMENT 수
// 		stPD_NumPositions = SELRANGE();													//PD Positon 수
// 		fPD_PatternPeriodMin=0.0f;												//PD 패턴주기 (USEC) 최소
// 		fPD_PatternPeriodMax=0.0f;												//PD 패턴주기 (USEC) 최대
//
// 		// PRI
// 		ePRI_Continuity=ContinuityCode::enumUndefinedContinuityCode;						//PRI 변화의 연속성 (CONTINUITY_CODE 참조)
// 		ePRI_Pattern=PatternCode::enumUndefinedPatternCode;								//NUMBER PRI변화의 패턴여부	(PATTERN_CODE 참조)
// 		ePRI_LagacyType=enumUndefinedPRI_LegacyType;									//PRI_LAGACY_TYPE_CODE 참조
// 		stPRI_NumElements = SELRANGE();													//NUMBER	PRI ELEMENT 수
// 		stPRI_NumPositions = SELRANGE();													//NUMBER	PRI POSITION 수
// 		fPRI_FramePeriodMin=0.0f;												//PRI FRAME 주기 (USEC) 최소
// 		fPRI_FramePeriodMax=0.0f;												//PRI FRAME 주기 (USEC) 최대
// 		fPRI_SubframePeriodMin=0.0f;											//PRI SUBFRAME 주기 (USEC) 최소
// 		fPRI_SubframePeriodMax=0.0f;											//PRI SUBFRAME 주기 (USEC) 최대
// 		fPRI_PPG_Min=0.0f;														//Pulse Per Group 최소
// 		fPRI_PPG_Max=0.0f;														//Pulse Per Group 최대
//
// 		// 펄스내 변조
// 		eMOP_CW_ModulationType=MOP_CW_ModulationType::enumUndefinedMOP_CW_ModulationType;	//펄스 내 또는 CW 변조형태 (MOP_CW_MOD_TYPE_CODE 참조)
// 		eMOP_CW_LegacyType=enumUndefinedMOP_CW_LegacyType;					//변조형태의 LEGACY TERM (MOP_CW_LEGACY_TYPE_CODE)
// 	}
//
// } SELRADARMODELIST_SEARCH_FILTER;

// typedef struct {
// 	EnumLibType enLibType;	// 기본형 또는 실무형
//
// 	int iPin;
// 	CString strBE_Number;
// 	CString strFacilityName;											//기지명칭 (위협명)
//
// 	EnumFunctionCodes ePrimaryFunction_ForGUI;		//주기능코드
// 	FriendOrFOE::EnumFriendOrFOE eFriendOrFOE;		//적아구분 enum값
//
// 	CString strPlaceNameKor;										//한글지명 (50)
// 	CString strPlaceNameEng;										//영문지명 (50)
//
// 	CString strCategory;												//자체 구분 카테고리 (99999 형식)(5)
// 	CString strADA;														//대공방공구역 (ADA) (AA123 형식) (5)
//
// 	CountryCode::EnumCountryCode eUserCountry;	//사용국가를 enum으로 표현
// 	PlatformCode::EnumPlatformCode ePlatform;			//탑재 플랫폼의 종류 (PLATFORM_CODE 참조)
//
// } SELTHREATLIST_SEARCH_FILTER;

//#endif




/************************************************************************************
*   ELINT View -> Logic에 사용되는 자료형 구조체
*************************************************************************************/


