#ifndef _H_EDB_RSLT_DATATYPE
#define _H_EDB_RSLT_DATATYPE

#include "ELThreat.h"

#include "./ELEmitterDataType.h"
//#include "../../ELINT/DATATYPE/ELGMIMsgDefn.h"
#include "./ELMsgDefn.h"

#include <string>
using namespace std;

#define E_STORE_DTAT_AN_REC_TOT_COL			8
#define E_STORE_DATA_AN_RSLT_TOT_COL		3
#define E_ACQ_SIG_TOT_COL					8
#define E_TACREP_TOT_COL					10
#define E_TACELINT_TOT_COL					11
#define E_UNIFORM_C_TOT_COL					10

#define	E_IDNTFY_RESULT_TOT_COL				13
#define	E_REPORT_TOT_COL				16
#define E_REPORT_ADDRESS_TOT_COL	3
#define E_TACREP_SERIAL_NUM_TOT_COL	6

#define MAX_EL_REPORT_DATA_SIZE			40000

#define	MAX_CANDIDATE_EOB							(5)

typedef struct stStoreDataAnRec
{
	string			strWorkID;
	unsigned int	uiDtctSigID;
	string			strUpperWorkID;
	string			strStartTime;
	string			strNeedsTime;
	string			strAnFactor;
	string			strAnFactorVal;
	string			strAnRsltFName;
}SELDBStoreDataAnRec;


typedef struct stTACREP
{
	unsigned int	uiTACREPID;
	string			strDtctSigID;
	unsigned int	uiSerialNo;
	unsigned int	uiReportType;
	unsigned int	uiSourceCode;
	string			strWriteDate;
	string			strSignalStaTime;
	string			strSignalEndTime;
	unsigned int	uiReportFileSize;
	string			strReportFileName;
}SELDBTACREP;

typedef struct stTACELINT
{
	string			strTACELINTID;
	string			strTaskID;
	unsigned int	uiSearchBandID;
	string			strAETID;
	unsigned int	uiSerialNo;
	unsigned int	uiReportType;
	string			strSourceCode;
	string			strWriteDate;
	string			strSignalStaTime;
	string			strSignalEndTime;
	string			strReportFileName;
	stTACELINT() :
		strTACELINTID(""),
		strTaskID(""),
		uiSearchBandID(0),
		strAETID(""),
		uiSerialNo(0),
		uiReportType(0),
		strSourceCode(""),
		strWriteDate(""),
		strSignalStaTime(""),
		strSignalEndTime(""),
		strReportFileName("")
	{}
}SELDBTACELINT;

typedef struct stUniformC
{
	unsigned int	uiUniformID;
	string			strDtctSigID;
	unsigned int	uiSerialNo;
	unsigned int	uiReportType;
	unsigned int	uiSourceCode;
	string			strWriteDate;
	string			strSignalStaTime;
	string			strSignalEndTime;
	unsigned int	uiReportFileSize;
	string			strReportFileName;
}SELDBUniformC;

// enum ENUM_ELREPORT_TYPE
// {
// 	E_REPORT_TE	 = 1,
// 	E_REPORT_TR,
// 	E_REPORT_BU,
// 	E_REPORT_EU,
// 	E_DTAIL_REPORT,
// };
//
// typedef struct stGRReportELBasicInfo  //ELINT 보고서 정보
// {
// 	//string			strTableID;			//DB삭제 Key정보
// 	//string			strReportID;		//보고서ID
// 	//string			strReportType;		//보고서형태
// 	//string			strSerialNo;		//시리얼넘버
// 	//string			strWriteData;		//작성날짜
// 	//unsigned int	uiAetID;
// 	//unsigned int	uiLobID;
// 	//string			strTaskID;
// 	////string			strELNOT;			//ELNOT
// 	//string			strReportStat;		//보고서상태
// 	//string			strTransTime;		//전송시간
// 	////unsigned char  szReportContent[MAX_EL_REPORT_DATA_SIZE];
// 	////string			strReportContent;	//보고서내용
// 	//string			strReportMemo;
// 	//string			strOperId;
// 	//string			strDTCTId;
// 	//unsigned int	uiNumOfRPT;
// 	//unsigned int	uiBuffSize;
//
// 	/////////////////////////////////////////////////////////////
// 	string			strMissionName;
// 	string			strTaskName;
// 	string			strELNOT;
// 	string			strCreateTime;
// 	unsigned int	uiPinNum;
// 	float			fLat;
// 	float			fLong;
// 	unsigned char  szReportContent[MAX_EL_REPORT_DATA_SIZE];
// 	string			strTableId; //For Delete/HIDE
// 	unsigned int	uiBuffSize;
// 	string			strReportType;		//보고서형태
// 	unsigned int	uiLobID;
// 	unsigned int	uiAetID;
// 	unsigned int    uiAbtID;
// 	string			strTransTime;		//전송시간
// 	string			strMissionID;
// 	string			strTaskID;
// 	string			strSerialNo;		//시리얼넘버
// 	string			strReportStat;		//보고서상태
// 	string			strReportID;		//보고서ID
// 	string			strOperId;
// 	string			strLinkNo; //링크정보
//
// 	stGRReportELBasicInfo::stGRReportELBasicInfo()
// 	{
// 		//strTableID = "";
// 		//strReportID = "";
// 		//strReportType = "";
// 		//strSerialNo = "";
// 		//strWriteData = "";
// 		//uiAetID = 0;
// 		//uiLobID = 0;
// 		//strTaskID = "";
// 		//strELNOT = "";
// 		//strReportStat = "";
// 		//strTransTime = "";
// 		////strReportContent = "";
// 		//strReportMemo = "";
// 		//strOperId = "";
// 		//strDTCTId = "";
// 		//uiNumOfRPT = 0;
// 		//uiBuffSize = 0;
//
// 		strMissionName = "";
// 		strTaskName = "";
// 		strELNOT = "";
// 		strCreateTime = "";
// 		uiPinNum = 0;
// 		fLat = 0.0;
// 		fLong = 0.0;
// 		uiBuffSize = 0;
// 		strReportType = "";
// 		uiLobID = 0;
// 		uiAetID = 0;
// 		uiAbtID = 0;
// 		strTransTime = "";
// 		strTaskID = "";
// 		strMissionID = "";
// 		strSerialNo = "";
// 		strReportStat = "";
// 		strReportID = "";
// 		strOperId = "";
// 		strLinkNo = "";
// 		memset(szReportContent, 0, MAX_EL_REPORT_DATA_SIZE);
// 	};
// }SGRReportELBasicInfo;
//
// typedef struct stELReport
// {
// 	string			strTableID;
// 	string			strReportID;
// 	unsigned int	uiReportType;
// 	string			strSerialNo;
// 	string			strCreateTime;
// 	unsigned int	uiAetID;
// 	unsigned int	uiAbtID;
// 	unsigned int	uiLobID;
// 	string			strTaskID;
// 	string			strELNOT;
// 	unsigned int	uiReportStatus;
// 	string			strTransmitTime;
// 	string			strReportContent; // 4000 바이트 한계 용량 때문에 사용하지 않음. szReportContent 사용. 2015.3.25. 이정남.
// 	string			strReportMemo;
// 	string			strOperId;
// 	string			strDtctId;
// 	unsigned int	nNumOfRptObj;
// 	unsigned char  szReportContent[MAX_EL_REPORT_DATA_SIZE];
// 	int					nBufferSize;
// 	string			strUpdateTime;
// 	string			strMissionID;
//     unsigned int uiPinNum;
// 	float				fLat;
// 	float				fLong;
// 	string strMissionName;
// 	string strTaskName;
//
// 	stELReport::stELReport()
// 		:uiReportType(0)
// 		,uiAetID(0)
// 		,uiAbtID(0)
// 		,uiLobID(0)
// 		,uiReportStatus(0)
// 		,nNumOfRptObj(0)
// 		,strTableID("")
// 		,strReportID("")
// 		,strSerialNo("")
// 		,strCreateTime("")
// 		,strTaskID("")
// 		,strELNOT("")
// 		,strTransmitTime("")
// 		,strReportContent("")
// 		,strReportMemo("")
// 		,strOperId("")
// 		,strDtctId("")
// 		,nBufferSize(0)
// 		,strUpdateTime("")
// 		,strMissionID("")
//         ,uiPinNum(0)
// 		,fLat(0.0)
// 		,fLong(0.0)
// 		,strMissionName("")
// 		,strTaskName("")
// 	{
// 		memset(szReportContent, 0, MAX_EL_REPORT_DATA_SIZE);
// 	};
// }SELDBReport;
//
// typedef struct stELReportAddressee
// {
// 	string			strAddresseeID;
// 	string			strReportID;
// 	string			strAdrresseeName;
// 	stELReportAddressee::stELReportAddressee()
// 		:strAddresseeID("")
// 		,strReportID("")
// 		,strAdrresseeName("")
// 	{
// 	};
// }SELDBReportAddressee;

struct SLOBOtherInfo {
    char szElnotPri[_MAX_ELNOT_STRING_SIZE_];
    char szModeCodePri[_MAX_SIZE_OF_MODECODE];
    char szModulationCode[_MAX_SIZE_OF_MODULATIONCODE];
    char szNickName[_MAX_NICKNAME_STRING_SIZE_];
    char szPriFuncCode[_MAX_SIZE_OF_FUNCTIONCODE];
    char szElnotSec[_MAX_ELNOT_STRING_SIZE_];
    char szModeCodeSec[_MAX_SIZE_OF_MODECODE];
    char szElnotTert[_MAX_ELNOT_STRING_SIZE_];
    char szModeCodeTert[_MAX_SIZE_OF_MODECODE];

    // 빔/방사차에서 공용으로 사용하기 위해서 연동기에 넘겨주기 위한 변수 정의
    int iRadarPriority;
    int iRadarModePriority;

    bool bUpdate;			// 연동기에서 사용함. POSN 에서는 사용하지 않음

} ;

/**
 * @typedef   SELEXTDB
 * @brief     DB에 데이터를 기록하기 위한 데이터 모음
 * @author    조철희 (churlhee.jo@lignex1.com)
 */
struct SELEXTDB {
    unsigned int uiSeqNum;
    unsigned int uiAETID;
    unsigned int uiABTID;
    unsigned int uiLOBID;

    //char acTaskName[SIZE_OF_TASK_NAME];

    //int iLatitude;
    //int iLongitude;

    //////////////////////////////////////////////////////////////////////////
    // 식별 정보 (CED)
    int iRadarModeIndex;																				// 레이더 모드 인덱스

    //char szIdInfo[_MAX_SIZE_OF_IDINFO];													// 식별 정보(기출, 신출, 불명)

    //char szPrimaryELNOT[_MAX_ELNOT_STRING_SIZE_];
    //char szPrimaryModeCode[_MAX_SIZE_OF_MODECODE];								// 1번째 ELNOT

    //char szSecondaryELNOT[_MAX_ELNOT_STRING_SIZE_];
    //char szSecondaryModeCode[_MAX_SIZE_OF_MODECODE];							// 2번째 ELNOT

    //char szThirdELNOT[_MAX_ELNOT_STRING_SIZE_];												// 3번째 ELNOT
    //char szThirdModeCode[_MAX_SIZE_OF_MODECODE];

    //char szNickName[_MAX_NICKNAME_STRING_SIZE_];											// Nickname 명
    //char szModulationCode[_MAX_SIZE_OF_MODULATIONCODE];					// Modulation Code
    //char szFunctioncode[_MAX_SIZE_OF_FUNCTIONCODE];							// 기능 코드명

    //int iPlatform;																							// 플랫폼
    //char szPlatformCode[MAX_SIZE_OF_PLATFORMCODE];							// 플랫폼 코드
    int iRadarPriority;																					// 레이더 모드 우선순위
    int iRadarModePriority;																			// 레이더 우선순위

    //////////////////////////////////////////////////////////////////////////
    // 식별 정보 (EOB)
    int iThreatIndex;																						// 위협 인덱스
    int iPinNumber;																							// PIN Number
    char szPlaceNameKor[_MAX_SIZE_OF_KOREASITENAME_];								// 위협명
    char szBENumber[_MAX_SIZE_OF_BENUMBER];											// BENumber
    char szThreatFunctionCode[_MAX_SIZE_OF_FUNCTIONCODE];				// 위협 기능 코드
    int iThreatPriority;																				// 위협 우선 순위
    int iThreatDistance;																				// 위협 간의 거리 오차 [nm]
    int iEquipNumber;																						// 장비 번호

    // 보고서 정보
    time_t tiFinalRpt;																					// 최종 보고서 생성 시간
    time_t tiFirstRpt;																					// 최초 보고서 생성 시간

    // 수동 편집 여브
    bool bIsManualEdited;

    int iDOADiff;

}  ;

// typedef struct {
// 	unsigned int uiAETID;
// 	unsigned int uiABTID;
// 	unsigned int uiLOBID;
// 	int		iSignalType;
// 	int	  iPulsePerGrp;
// 	int		iRecentHour;
// 	int		iRecentMin;
// 	int		iRecentSec;
// 	int		iBL;
// 	//int		iFov;
// 	int		iMeanDOA;							// [0.1도]
// 	int		iMaxDOA;
// 	int		iMinDOA;
// 	int		iDoaDeviation;
// 	int		iDIRatio;							// [0.1%]
// 	int		iFreqType;
// 	int		iFreqPatternType;
// 	int		iIsFreqPeriod;
// 	int		iFreqChangePeriod;	  // [us]
// 	int		iFreqPositionCount;
// 	int		iFreqElementCount;
// 	int		iMeanFreq;										// [10KHz]
// 	int		iMaxFreq;
// 	int		iMinFreq;
// 	int		iFreqDeviation;								// 기존대로
// 	int		iFreqSeq[MAX_FREQ_PRI_STEP];	// 주파수 단값
// 	int		iPRIType;
// 	int		iPRIPatternType;
// 	int		iIsPRIPeriod;
// 	int		iPRIChangePeriod;							// [us]
// 	int		iPRIPositionCount;
// 	int		iPRIElementCount;
// 	int		iMeanPRI;											// [1ns]
// 	int		iMaxPRI;
// 	int		iMinPRI;
// 	int		iPRIDeviation;								// [1ns]
// 	int		iPRIJitterRatio;							// 0.1%
// 	int		iPRISeq[MAX_FREQ_PRI_STEP];
// 	int		iMeanPW;											// 1ns
// 	int		iMaxPW;
// 	int		iMinPW;
// 	int		iPWDeviation;
// 	int		iMeanPA;											// 기존대로
// 	int		iMaxPA;
// 	int		iMinPA;
// 	int		iPADeviation;									// 기존대로
// 	int		iScanType;
// 	int		iDetailScanType;
// 	int		iScanPeriod;									// [usec]
// 	int		iMOPType;											// 인트라 타입
// 	int		iDetailMOPType;								// 인트라 세부 타입. 항공에서 줄 수 있는것인지(?)
// 	int		iMOPMaxFreq;									// ??
// 	int		iMOPMinFreq;
// 	int		iMOPMeanFreq;
// 	int		iMOPFreqDeviation;
// 	int		iPRIPGSeq[32];
// 	int		iPAPGSeq[32];
// 	int		iFOM;
// 	int		iIsStorePDW;
// 	int		iIsStoreIQ;
// 	int		iNumOfPDW;
// 	int		iNumOfIQ;
// 	int		iPolarization;								// 극성.
// 	int		iRatioOfPOL;									// 극성 신뢰도.
// 	int		iIsFISINTTask;
// 	int		iRollAngle;										// 기존대로
// 	int		iPitchAngle;
// 	int		iHeadingAngle;
// 	int		iAltitude;
// 	double	dAircraftLatitude;
// 	double	dAircraftLongitude;
// } SLOBData ;

struct STR_FREQ_PRI_PW_PA_INFO {
	float fMean;
	float fMax;
	float fMin;
	float fDeviation;

        STR_FREQ_PRI_PW_PA_INFO() : fMean(0), fMax(0), fMin(0), fDeviation(0)
	{

	}

} ;

struct STR_DOA_INFO {
	float fMean;
	float fMax;
	float fMin;
	//int iDeviation;
	//int iSDeviation;

        STR_DOA_INFO() : fMean(0), fMax(0), fMin(0) /* iDeviation(0),  iSDeviation(0)*/
	{

	}

} ;

struct SELAETDATA {
    // 기초 정보
    unsigned int uiAETID;

    unsigned int uiCoLOB;
    unsigned int uiCoABT;

    unsigned int tiFirstSeenTime;
    //UINT firstSeenMillisec;
    unsigned int tiLastSeenTime;
    //UINT lastSeenMillisec;

    int iValidity;

    STR_FREQ_PRI_PW_PA_INFO freqInfo;
    STR_FREQ_PRI_PW_PA_INFO priInfo;
    STR_FREQ_PRI_PW_PA_INFO pwInfo;
    STR_FREQ_PRI_PW_PA_INFO paInfo;

    // CED/EOB 식별 정보
    STR_CEDEOBID_INFO idInfo;

    // 위치 산출 정보
    STR_POSITION_ESTIMATION peInfo;

    unsigned int tiFinalAlarmTime;

}  ;

struct STR_SIGTYPE_INFO {
	int iSignalType;
	char modCode[2];

        STR_SIGTYPE_INFO() : iSignalType(0) //, iPolarization(0)
	{
		memset( modCode, 0, sizeof(modCode) );
	}

} ;

struct STR_FREQ_PRI_DINFO {
	int iType;
	int iPatternType;
	//int iIsPeriod;
	//int iChangePeriod;
	float fChangePeriodMin;
	float fChangePeriodMax;
	float fChangePeriodMean;
	int iPositionCount;
	//int iElementCount;
	float fSeq[MAX_FREQ_PRI_STEP];
	float fPRIJitterRatio;

        STR_FREQ_PRI_DINFO() : iType(0), iPatternType(0), /* iIsPeriod(0), iChangePeriod(0),*/ fChangePeriodMin(0), fChangePeriodMax(0), fChangePeriodMean(0), iPositionCount(0), fPRIJitterRatio(0)
	{
		memset( fSeq, 0, sizeof(fSeq) );
	}

} ;

// struct STR_PULSE_GROUP_DINFO {
// 	int iPulsePerGrp;
// 	int iPRIPGSeq[MAX_PRI_PER_GROUP];
// 	int iPAPGSeq[MAX_PADIFF_PER_GROUP];
//
// 	STR_PULSE_GROUP_DINFO::STR_PULSE_GROUP_DINFO() : iPulsePerGrp(0)
// 	{
// 		memset( iPRIPGSeq, 0, sizeof(iPRIPGSeq) );
// 		memset( iPAPGSeq, 0, sizeof(iPAPGSeq) );
// 	}
//
// } ;

struct STR_SCAN_INFO {
    int iType;
    int iDetailType;
    int iPeriod;
    int iPeriodMin;
    int iPeriodMax;
    int iPeriodMean;

    STR_SCAN_INFO() : iType(0), iDetailType(0), iPeriod(0), iPeriodMin(0), iPeriodMax(0), iPeriodMean(0)
    {

    }

} ;

struct STR_INTRA_INFO {
	int iType;
	int iDetailType;
	int iMaxFreq;
	int iMinFreq;
	int iMeanFreq;
	int iMaxFreqDeviation;
	int iMinFreqDeviation;
	int iMeanFreqDeviation;

        STR_INTRA_INFO() : iType(0), iDetailType(0), iMaxFreq(0), iMinFreq(0), iMeanFreq(0), iMaxFreqDeviation(0), iMinFreqDeviation(0), iMeanFreqDeviation(0)
	{

	}

} ;

// struct SELABTDATA {
// 	// 기초 정보
// 	unsigned int uiAETID;
// 	unsigned int uiABTID;
//
// 	STR_SIGTYPE_INFO sigInfo;
//
// 	unsigned int uiCoLOB;
//
// 	time_t tiFirstSeenTime;
// 	time_t tiLastSeenTime;
//
// 	int iValidity;
//
// 	//STR_DOA_INFO doaInfo;
//
// 	STR_FREQ_PRI_DINFO freqDInfo;
// 	STR_FREQ_PRI_PW_PA_INFO freqInfo;
// 	STR_FREQ_PRI_DINFO priDInfo;
// 	STR_FREQ_PRI_PW_PA_INFO priInfo;
//
// 	//STR_PULSE_GROUP_DINFO pulseDInfo;
//
// 	STR_FREQ_PRI_PW_PA_INFO pwInfo;
// 	//STR_SCAN_INFO scanInfo;
// 	STR_FREQ_PRI_PW_PA_INFO paInfo;
//
// 	//STR_INTRA_INFO intraInfo;
//
// 	// CED/EOB 식별 정보
// 	STR_CEDEOBID_INFO idInfo;
//
// 	// 위치 산출 정보
// 	STR_POSITION_ESTIMATION peInfo;
//
// 	// 알람 정보
// 	time_t finalAlarmTime;
//
// } ;

// /**
//  * @typedef   SELABTDATA_EXT
//  * @brief     ABT 구조체 정의
//  * @author    조철희 (churlhee.jo@lignex1.com)
//  */
// typedef struct {
// 	// 누적된 전체 PDW 개수
// 	//int nCoTotalPdw;
// 	//int nCoTotalIQ;
//
// 	// 인트라 변조 유무
// 	//bool bIntraMop;
//
// 	// 위치 산출 정보-Covariace 값
// 	double dPECoVar[4];
//
// 	float fLastAOA;
// 	double dRadarCollectionLatitude;
// 	double dRadarCollectionLongitude;
//
// 	// 수동 편집 여부
// 	//bool bIsManualEdited;
//
// 	// 방사체의 활동 상태를 저장
// 	enum E_BEAM_EMITTER_STAT enBeamEmitterStat;
//
// 	// 빔 유효성 갯수
// 	int nCoBeamValidity;
//
// 	// 수동 편집 여부 플레그
// 	//UELMANUALVAL xManualEdited;
//
// 	// FISINT용 과제
// 	bool bIsFISINTTask;
//
// 	// 수동/자동 위치 결과 정보 여부
// 	//bool bManualPosEstPreferred;
// 	unsigned int uiSeqNum;
//
// 	//SLOBOtherInfo stLOBOtherInfo;
//
// 	int iLOBPoolIndex;
//
// 	STR_ID_TYPE stIDType;
//
// 	//time_t tiLOBfirstReportedTime;
// 	//time_t tiLOBfinalReportedTime;
//
// 	int nCoIdEOB;
// 	//STR_EOB_RESULT stEOBResult[MAX_CANDIDATE_EOB];
//
// 	// 빔 병합 정보
// 	bool bCompFreq;
// 	bool bCompPRI;
//
// 	// 신규 CED 및 EOB로 식별한 정보
// 	STR_CEDEOBID_INFO idInfo;
//
// 	ENUM_PE_STAT enValid;
// 	bool bApplayOfLOBClustering;// TRUE: 적용, FALSE: 미적용
//
// } SELABTDATA_EXT;
//
// typedef struct {
// 	// 누적된 전체 PDW 개수
// 	int nCoTotalPdw;
// 	//int nCoTotalIQ;
//
// 	// 인트라 변조 유무
// 	// bool bIntraMop;
//
// 	// 방사체 간의 식별을 위한 정보
// 	//char szEOBELNOT[_MAX_ELNOT_STRING_SIZE_];					// EOB 상의 ELNOT
//
// 	// 방사체의 활동 상태를 저장
// 	enum E_BEAM_EMITTER_STAT enBeamEmitterStat;
//
// 	// 수동 편집 여부 플레그
// 	bool bIsManualEdited;
//
// 	bool bIsFISINTTask;
//
// 	// 수동 편집 정보
// 	//UELMANUALVAL xMannualEdited;
//
// 	int iPinNumber;
// 	//char szELNOT[_MAX_ELNOT_STRING_SIZE_];
//
// 	//int iTaskType;		// 과제 형태
//
// 	// 여러개의 미식별 빔 중에서 대표 ABT 번호
// 	unsigned int nUnIDABTID;
//
// 	// 수동/자동 위치 결과 정보 여부
// 	bool bManualPosEstPreferred;
// 	unsigned int uiSeqNum;
//
//
// } SELAETDATA_EXT;

struct SELLOB {
	SRxLOBData stLOBData;

} ;

struct SELABT {
	SRxABTData stABTData;
	SELABTDATA_EXT stABTExtData;

} ;

struct SELAET {
        SRxAETData stAETData;
	SELAETDATA_EXT stAETExtData;

} ;

/**
 * @typedef   위협 관리에서 사용할 LOB 구조체 정의
 * @brief     설명을 요약해서 기입해주세요.
 * @author    조철희 (churlhee.jo@lignex1.com)
 */
struct UELTHREAT {
	SELLOB uniLOB;
	SELABT uniABT;
	SELAET uniAET;

}  ;

/**
 * @brief The SELMERGE_CANDIDATE struct
 */
struct SELMERGE_CANDIDATE {
	SELINDEX idx;
	float fLevel;

	E_BEAM_EMITTER_STAT eStat;						// LOB 상태

	unsigned int nSeqNum;									// DB 테이블의 SEQ_NUM

	//bool bIsFISINTTask;										// FISINT용 과제

	//char szELNOT[_MAX_ELNOT_STRING_SIZE_];///< 빔의 ELNOT 정보

} ;

struct SELMERGE_BEAM {
    CELThreat *pThreatAET;
    CELThreat *pThreatABT;
};

typedef SELMERGE_BEAM SELSEPERATE_BEAM;

// typedef struct {
// 	UINT uiSeqNum[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	UINT iRecentHour[MAX_SIZE_OF_ARRAY_INSERT];
// 	UINT iRecentMin[MAX_SIZE_OF_ARRAY_INSERT];
// 	UINT iRecentSec[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	char szAcquireTime[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_DATETIME];
// 	UINT iLinkNum[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	char szMissionID[MAX_SIZE_OF_ARRAY_INSERT][DEF_MISSION_ID_LENGTH];
// 	char szMissionName[MAX_SIZE_OF_ARRAY_INSERT][DEF_MISSION_NAME_LENGTH];
//
// 	char szTaskID[MAX_SIZE_OF_ARRAY_INSERT][LENGTH_OF_TASK_ID+2];
// 	char szTaskName[MAX_SIZE_OF_ARRAY_INSERT][SIZE_OF_TASK_NAME+2];
//
// 	UINT iTaskType[MAX_SIZE_OF_ARRAY_INSERT];
// 	UINT iSearchBandID[MAX_SIZE_OF_ARRAY_INSERT];
// 	UINT iRxPath[MAX_SIZE_OF_ARRAY_INSERT];
// 	UINT iDetAntDirection[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	UINT uiLOBID[MAX_SIZE_OF_ARRAY_INSERT];
// 	UINT uiABTID[MAX_SIZE_OF_ARRAY_INSERT];
// 	UINT uiAETID[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	char szPrimaryELNOT[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_ELNOT];
// 	char szPrimaryModeCode[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_MODECODE];
//
// 	char szSecondaryELNOT[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_ELNOT];
// 	char szSecondaryModeCode[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_MODECODE];
//
// 	char szThirdELNOT[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_ELNOT];
// 	char szThirdModeCode[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_MODECODE];
//
// 	char szModulationCode[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_MODULATIONCODE];
// 	char szNickName[MAX_SIZE_OF_ARRAY_INSERT][_MAX_NICKNAME_STRING_SIZE_];
// 	char szFunctioncode[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_FUNCTIONCODE];
//
// 	int iSignalType[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iPolarization[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iRatioOfPOL[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iIsFISINTTask[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	int iPulsePerGrp[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iNumOfPDW[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iBL[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iFov[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	int iMeanDOA[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iMinDOA[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iMaxDOA[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iDOADiff[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iDOADeviation[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iDIRatio[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	int iFreqType[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iFreqPatternType[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iIsFreqPeriod[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iFreqChangePeriod[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iFreqPositionCount[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iFreqElementCount[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iMeanFreq[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iMaxFreq[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iMinFreq[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iFreqDeviation[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	int iPRIType[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iPRIPatternType[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iIsPRIPeriod[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iPRIChangePeriod[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iPRIPositionCount[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iPRIElementCount[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iMeanPRI[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iMaxPRI[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iMinPRI[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iPRIDeviation[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iPRIJitterRatio[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	int iMeanPW[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iMinPW[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iMaxPW[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iPWDeviation[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	int iMeanPA[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iMinPA[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iMaxPA[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iPADeviation[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	int iScanType[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iDetailScanType[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iScanPeriod[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	int iMOPType[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iDetailMOPType[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iMOPMeanFreq[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iMOPMinFreq[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iMOPMaxFreq[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iMOPFreqDeviation[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	int iLatitude[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iLongitude[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iPitchAngle[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iRollAngle[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iHeadingAngle[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iAltitude[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	int iFOM[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iIsStorePDW[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iIsStoreIQ[MAX_SIZE_OF_ARRAY_INSERT];
// 	int isFiltered[MAX_SIZE_OF_ARRAY_INSERT];
// 	int bIsManualEdited[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iBeamValidity[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	int iDummy[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	char szFinalRpt[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_DATETIME];
// 	char szFirstRpt[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_DATETIME];
//
// 	UINT uiALOBID[MAX_SIZE_OF_ARRAY_INSERT];
// 	UINT uiAABTID[MAX_SIZE_OF_ARRAY_INSERT];
// 	UINT uiAAETID[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	UINT iStat[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iDummy2[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	char szRcvTime[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_DATETIME];
//
// 	//
// 	bool bLink2;
//
// } SELArrLOB;

// typedef struct {
// 	UINT uiSeqNum[MAX_SIZE_OF_ARRAY_INSERT];
// 	char szMissionID[MAX_SIZE_OF_ARRAY_INSERT][DEF_MISSION_ID_LENGTH];
// 	char szMissionName[MAX_SIZE_OF_ARRAY_INSERT][DEF_MISSION_NAME_LENGTH];
// 	UINT uiABTID[MAX_SIZE_OF_ARRAY_INSERT];
// 	UINT uiAETID[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iRadarModeIndex[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iThreatIndex[MAX_SIZE_OF_ARRAY_INSERT];
// 	char szPrimaryELNOT[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_ELNOT];
// 	char szPrimaryModeCode[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_MODECODE];
// 	char szModulationCode[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_MODULATIONCODE];
// 	char szNickName[MAX_SIZE_OF_ARRAY_INSERT][_MAX_NICKNAME_STRING_SIZE_];
// 	char szFunctioncode[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_FUNCTIONCODE];
// 	char szPlatformCode[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_PLATFORMCODE];
// 	char szPlaceNameKor[MAX_SIZE_OF_ARRAY_INSERT][_MAX_SIZE_OF_THREATNAME_];
// 	int iRadarModePriority[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iRadarPriority[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	int iSignalType[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iPolarization[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iTaskType[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iPulsePerGrp[MAX_SIZE_OF_ARRAY_INSERT];
// 	int nCoLOB[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	char szFirstSeenTime[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_DATETIME];
// 	char szLastSeenTime[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_DATETIME];
//
// 	int bValidity[MAX_SIZE_OF_ARRAY_INSERT];
// 	int freqDInfoType[MAX_SIZE_OF_ARRAY_INSERT];
// 	int freqDInfoPatternType[MAX_SIZE_OF_ARRAY_INSERT];
// 	int freqDInfoIsPeriod[MAX_SIZE_OF_ARRAY_INSERT];
// 	int freqDInfoChangePeriodMean[MAX_SIZE_OF_ARRAY_INSERT];
// 	int freqDInfoChangePeriodMax[MAX_SIZE_OF_ARRAY_INSERT];
// 	int freqDInfoChangePeriodMin[MAX_SIZE_OF_ARRAY_INSERT];
// 	int freqDInfoPositionCount[MAX_SIZE_OF_ARRAY_INSERT];
// 	int freqDInfoElementCount[MAX_SIZE_OF_ARRAY_INSERT];
// 	int freqInfoMean[MAX_SIZE_OF_ARRAY_INSERT];
// 	int freqInfoMax[MAX_SIZE_OF_ARRAY_INSERT];
// 	int freqInfoMin[MAX_SIZE_OF_ARRAY_INSERT];
// 	int freqInfoDeviation[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	int priDInfoType[MAX_SIZE_OF_ARRAY_INSERT];
// 	int priDInfoPatternType[MAX_SIZE_OF_ARRAY_INSERT];
// 	int priDInfoIsPeriod[MAX_SIZE_OF_ARRAY_INSERT];
// 	int priDInfoChangePeriodMean[MAX_SIZE_OF_ARRAY_INSERT];
// 	int priDInfoChangePeriodMax[MAX_SIZE_OF_ARRAY_INSERT];
// 	int priDInfoChangePeriodMin[MAX_SIZE_OF_ARRAY_INSERT];
// 	int priDInfoPositionCount[MAX_SIZE_OF_ARRAY_INSERT];
// 	int priDInfoElementCount[MAX_SIZE_OF_ARRAY_INSERT];
// 	int priInfoMean[MAX_SIZE_OF_ARRAY_INSERT];
// 	int priInfoMax[MAX_SIZE_OF_ARRAY_INSERT];
// 	int priInfoMin[MAX_SIZE_OF_ARRAY_INSERT];
// 	int priInfoDeviation[MAX_SIZE_OF_ARRAY_INSERT];
// 	int priInfoPRIJitterRatio[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	int pwInfoMean[MAX_SIZE_OF_ARRAY_INSERT];
// 	int pwInfoMax[MAX_SIZE_OF_ARRAY_INSERT];
// 	int pwInfoMin[MAX_SIZE_OF_ARRAY_INSERT];
// 	int pwInfoDeviation[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	int paInfoMean[MAX_SIZE_OF_ARRAY_INSERT];
// 	int paInfoMax[MAX_SIZE_OF_ARRAY_INSERT];
// 	int paInfoMin[MAX_SIZE_OF_ARRAY_INSERT];
// 	int paInfoDeviation[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	int scanInfoType[MAX_SIZE_OF_ARRAY_INSERT];
// 	int scanInfoPeriodMin[MAX_SIZE_OF_ARRAY_INSERT];
// 	int scanInfoPeriodMax[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	int iIntraMop[MAX_SIZE_OF_ARRAY_INSERT];
// 	int intraInfoMaxFreq[MAX_SIZE_OF_ARRAY_INSERT];
// 	int intraInfoMinFreq[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	int peInfoenValid[MAX_SIZE_OF_ARRAY_INSERT];
// 	int peInfoenLatitude[MAX_SIZE_OF_ARRAY_INSERT];
// 	int peInfoenLongitude[MAX_SIZE_OF_ARRAY_INSERT];
// 	int peInfoenAltidude[MAX_SIZE_OF_ARRAY_INSERT];
// 	int peInfoenCEP[MAX_SIZE_OF_ARRAY_INSERT];
// 	int peInfoenMajorAxis[MAX_SIZE_OF_ARRAY_INSERT];
// 	int peInfoenMinorAxis[MAX_SIZE_OF_ARRAY_INSERT];
// 	int peInfoenTheta[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	char szFirstReportedTime[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_DATETIME];
// 	char szFinalReportedTime[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_DATETIME];
// 	char szFinalAlarmTime[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_DATETIME];
//
// 	int iIsManualEdited[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iLinkNum[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iManualPosEstPreferred[MAX_SIZE_OF_ARRAY_INSERT];
// 	int peInfoManualLatitude[MAX_SIZE_OF_ARRAY_INSERT];
// 	int peInfoManualLongitude[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iThreatDistance[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	enum E_BEAM_EMITTER_STAT enBeamEmitterStat[MAX_SIZE_OF_ARRAY_INSERT];
//
// } SELArrABT;

// typedef struct {
// 	UINT uiSeqNum[MAX_SIZE_OF_ARRAY_INSERT*4];
//
// 	char szMissionID[MAX_SIZE_OF_ARRAY_INSERT*4][DEF_MISSION_ID_LENGTH];
// 	char szTaskID[MAX_SIZE_OF_ARRAY_INSERT*4][LENGTH_OF_TASK_ID+2];
//
// 	UINT uiLOBID[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	UINT uiABTID[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	UINT uiAETID[MAX_SIZE_OF_ARRAY_INSERT*4];
//
// 	UINT iLinkNum[MAX_SIZE_OF_ARRAY_INSERT*4];
//
// 	UINT iDataType[MAX_SIZE_OF_ARRAY_INSERT*4];
//
// 	UINT iPositionCount[MAX_SIZE_OF_ARRAY_INSERT*4];
//
// 	int iSeq01[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq02[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq03[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq04[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq05[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq06[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq07[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq08[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq09[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq10[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq11[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq12[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq13[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq14[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq15[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq16[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq17[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq18[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq19[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq20[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq21[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq22[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq23[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq24[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq25[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq26[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq27[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq28[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq29[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq30[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq31[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq32[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq33[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq34[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq35[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq36[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq37[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq38[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq39[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq40[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq41[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq42[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq43[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq44[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq45[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq46[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq47[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq48[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq49[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq50[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq51[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq52[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq53[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq54[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq55[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq56[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq57[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq58[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq59[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq60[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq61[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq62[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq63[MAX_SIZE_OF_ARRAY_INSERT*4];
// 	int iSeq64[MAX_SIZE_OF_ARRAY_INSERT*4];
//
// 	//
// 	bool bLink2[MAX_SIZE_OF_ARRAY_INSERT*4];
//
// } SELArrLOBABT_Position;

// typedef struct {
// 	UINT uiSeqNum[MAX_SIZE_OF_ARRAY_INSERT];
// 	char acMissionID[MAX_SIZE_OF_ARRAY_INSERT][DEF_MISSION_ID_LENGTH];
// 	char acMissionName[MAX_SIZE_OF_ARRAY_INSERT][DEF_MISSION_NAME_LENGTH];
// 	UINT uiAETID[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iTaskType[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	int iRadarModeIndex[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iThreatIndex[MAX_SIZE_OF_ARRAY_INSERT];
// 	char szIdInfo[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_IDINFO];
// 	char szPrimaryELNOT[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_ELNOT];
// 	char szPrimaryModeCode[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_MODECODE];
//
// 	char szNickName[MAX_SIZE_OF_ARRAY_INSERT][_MAX_NICKNAME_STRING_SIZE_];
// 	char szFunctioncode[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_FUNCTIONCODE];
// 	int iRadarPriority[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iPinNumber[MAX_SIZE_OF_ARRAY_INSERT];
// 	char szPlaceNameKor[MAX_SIZE_OF_ARRAY_INSERT][_MAX_SIZE_OF_KOREASITENAME_];
// 	char szBENumber[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_BENUMBER];
// 	char szThreatFunctionCode[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_FUNCTIONCODE];
// 	int iThreatPriority[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iThreatDistance[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iEquipNumber[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	int nCoLOB[MAX_SIZE_OF_ARRAY_INSERT];
// 	int nCoABT[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	char szFirstSeenTime[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_DATETIME];
// 	char szLastSeenTime[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_DATETIME];
//
// 	int bValidity[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	int freqInfoMean[MAX_SIZE_OF_ARRAY_INSERT];
// 	int freqInfoMax[MAX_SIZE_OF_ARRAY_INSERT];
// 	int freqInfoMin[MAX_SIZE_OF_ARRAY_INSERT];
// 	int freqInfoDeviation[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	int priInfoMean[MAX_SIZE_OF_ARRAY_INSERT];
// 	int priInfoMax[MAX_SIZE_OF_ARRAY_INSERT];
// 	int priInfoMin[MAX_SIZE_OF_ARRAY_INSERT];
// 	int priInfoDeviation[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	int pwInfoMean[MAX_SIZE_OF_ARRAY_INSERT];
// 	int pwInfoMax[MAX_SIZE_OF_ARRAY_INSERT];
// 	int pwInfoMin[MAX_SIZE_OF_ARRAY_INSERT];
// 	int pwInfoDeviation[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	int paInfoMean[MAX_SIZE_OF_ARRAY_INSERT];
// 	int paInfoMax[MAX_SIZE_OF_ARRAY_INSERT];
// 	int paInfoMin[MAX_SIZE_OF_ARRAY_INSERT];
// 	int paInfoDeviation[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	int peInfoenValid[MAX_SIZE_OF_ARRAY_INSERT];
// 	int peInfoenLatitude[MAX_SIZE_OF_ARRAY_INSERT];
// 	int peInfoenLongitude[MAX_SIZE_OF_ARRAY_INSERT];
// 	int peInfoenAltidude[MAX_SIZE_OF_ARRAY_INSERT];
// 	int peInfoenCEP[MAX_SIZE_OF_ARRAY_INSERT];
// 	int peInfoenMajorAxis[MAX_SIZE_OF_ARRAY_INSERT];
// 	int peInfoenMinorAxis[MAX_SIZE_OF_ARRAY_INSERT];
// 	int peInfoenTheta[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	char szFirstReportedTime[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_DATETIME];
// 	char szFinalReportedTime[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_DATETIME];
// 	char szFinalAlarmTime[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_DATETIME];
//
// 	int iIsManualEdited[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iLinkNum[MAX_SIZE_OF_ARRAY_INSERT];
// 	int iManualPosEstPreferred[MAX_SIZE_OF_ARRAY_INSERT];
// 	int peInfoManualLatitude[MAX_SIZE_OF_ARRAY_INSERT];
// 	int peInfoManualLongitude[MAX_SIZE_OF_ARRAY_INSERT];
//
// 	enum E_BEAM_EMITTER_STAT enBeamEmitterStat[MAX_SIZE_OF_ARRAY_INSERT];
//
// } SELArrAET;
//
// typedef struct {
// 	char szTable[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_TABLE_NAME];
// 	char szCondition[MAX_SIZE_OF_ARRAY_INSERT][MAX_SIZE_OF_DELETE_CONDITION];
//
// } SELArrDelAETABT;

#endif

