//////////////////////////////////////////////////////////////////////////

#ifndef _H_ELINT_TASK_DATATYPE
#define _H_ELINT_TASK_DATATYPE
// Fisint Data Type 정의

#include <string>
using namespace std;

#include "../Identify/ELCEDLibDataType.h"


// #define TASK_MNGR_TOT_COL			23
// #define TASK_DETAIL_TOT_COL			51
// #define HIGH_GAIN_ANT_TOT_COL		9
// #define PRE_PROC_FILTER_TOT_COL		20
// #define SW_BLANKING_TOT_COL			10
// #define HW_BLANKING_TOT_COL			9
// #define HIGH_GAIN_NB_SETUP_TOT_COL	14
// #define E_CED_THREAT_TOT_COL		4
// #define E_THRAT_ALARM_TOT_COL		4
// #define E_AREA_ALARM_TOT_COL		3
// #define	E_WB_CHANN_TOT_COL			3
// #define E_LOG_TOT_COL				12
// #define	E_PDW_IQ_IF_LIST_TOT_COL	38
// #define	E_TSG_TOT_COL				10
// #define	E_OPER_CTRL_STATUS_TOT_COL	40
// #define E_NOISE_LEVEL_TOT_COL		5
// #define E_WB_SPEC_STATUS_TOT_COL	7
// #define E_WB_SPEC_LIST_TOT_COL	15
// #define E_WB_SPEC_SCANBAND_TOT_COL	9
// #define E_WB_SPEC_LIST_TO_SCANBAND_TO_LIST E_WB_SPEC_LIST_TOT_COL+E_WB_SPEC_SCANBAND_TOT_COL
// #define E_TASK_SET_TOT_COL		4
// #define E_TASK_SET_CANDIDATE_TOT_COL	4
// #define E_ALARM_AND_ASSOC_TASK_TOT_COL	14
// #define E_ALARM_TABLE_SELECT_INFO_TOT_COL 3
// #define E_ALARM_EMITTER_TOT_COL 13
// #define E_ALARM_IDENTIFY_TOT_COL 5
// #define E_ALARM_ASSOC_TASK_TOT_COL 11
// #define E_ALARM_AIRCRAFT_TOT_COL 3
// #define E_ALARM_POS_TOT_COL 9
// #define E_ALARM_LINK_TOT_COL 5
// #define E_ALARM_LINK_OPER_TOT_COL 4
// #define E_AET_MANUAL_INPUT_TOT_COL 10
// #define E_ELINT_MISSION_TRIAL_TOT_COL 5
// #define E_ENV_VAR_TOT_COL 70
// #define E_ENV_VAR_RPT_TOT_COL 15
// #define E_ENV_VAR_IDNF_TOT_COL 32
// 
// #define GET_MAX_ARR_VALUE 64
// #define ARR_BUF_SIZE 36	 
// #define ARR_BUF_NOTE_SIZE 300
// #define ARR_BUF_NORMAL_LENG 100
// #define	ARR_NOTE_BIG_BUFFER_LENG 1025
// 
// #define ARR_EL_INSERT_SIZE			500
// 
// namespace SELTASKDB {
// 
// //typedef struct stLogInfo
// //{
// //	string			strLogID; //EL_XXX, FL_XXX
// //	string			strMissionID;
// //	string			strTaskID;		 
// //	string			strLogDirection; //Tx, Rx, None
// //	string			strReceiverID;		
// //	unsigned int	uiPosnID;
// //	string			strSourcePath; //지상, 항공, 
// //	string			strTargetPath; //
// //	string			strLogGrtnTime; //ex) 2013-07-16 11:15:45.54 or 13-07-16 11:15:45.54
// //	string			strLogType; //Error, System, DB, 내부메시지, 외부메시지
// //	string 			strWarningLevel; //Critical, Major, Minor
// //	string			strLogData;
// //}SELDBLogInfo;
// 
// //================================
// // 1. TABLE : ELINT 과제
// //================================
// typedef struct stELDBTaskSum
// {	
// 	string strTaskId;
// 	unsigned short	usSdfId;
// 	string strMissionId;
// 	string strMissionName;
// 	string strOperatorId;
// 	string strEquipId;
// 	string strTaskCreatorId;
// 	unsigned int nTaskPriority;
// 	unsigned char ucAircraftNum;
// 	unsigned char ucLinkNum;
// 	string strCreateTime;
// 	string strStartTime;
// 	string strFinishTime;
// 	string strTaskName;
// 	unsigned char ucTaskType;
// 	unsigned char ucTaskStatus;
// 	bool bIsRelativeTask;
// 	unsigned char ucEmerTaskType; //추가	
// 	bool bIsShowTask;
// 	bool bIsCheckTask;
// 	bool bIsUploadTask;
// 	float fStartFrq;
// 	float fEndFrq;
// 	int nNumOfSrchBand;
// 
// 	stELDBTaskSum::stELDBTaskSum()
// 	{
// 		strTaskId = "";
// 		usSdfId = 0;
// 		strMissionId = ""; //2014.06.03. 이정남 추가 (누락되어 있었음)
// 		strOperatorId = "";
// 		strEquipId = "";
// 		strTaskCreatorId = "";
// 		nTaskPriority = 0;
// 		ucAircraftNum = 0;
// 		ucLinkNum = 0;
// 		strCreateTime = "";
// 		strStartTime = "";
// 		strFinishTime = "";
// 		strTaskName = "";
// 		ucTaskType = 0;
// 		ucTaskStatus = 0;
// 		bIsRelativeTask = 0;
// 		ucEmerTaskType = 0; //추가
// 		bIsShowTask = 0;
// 		bIsCheckTask = 0;
// 		bIsUploadTask = 0;
// 		fStartFrq = 0.0;
// 		fEndFrq = 0.0;
// 		nNumOfSrchBand = 0;
// 
// 	};
// }SELDBTaskSum;
// 
// typedef struct SELTaskInfo
// {	
// 	int iTaskType;
// 	int iDetAntDirection;
// 	int iLinkNum;
// 	string strAircraftNum;
// 	int iRxPath;
// 	int iIsPDWRestored;
// 	int iIsIQRestored;
// 
// 	SELTaskInfo::SELTaskInfo()
// 	{
// 		iTaskType = -1;
// 		iDetAntDirection = -1;
// 		iLinkNum = -1;
// 		strAircraftNum = "";
// 		iRxPath = 0;
// 		iIsPDWRestored = 0;
// 		iIsIQRestored = 0;
// 	};
// }SELTaskInfo;
//  
// 
// 
// //================================
// // 2. TABLE : 탐색대역
// //================================
// typedef struct stELDBTaskDetail
// {
// 	unsigned short nSearchBandId;
// 	string strTaskId;
// 	float fSearchStartFrq;	// 시작 주파수, 소수점 1자리
// 	float fSearchEndFrq;		// 종료 주파수, 소수점 1자리
// 	unsigned char ucDetectIFBandwidth;
// 	unsigned char ucHighGainIFBandwidth;
// 	unsigned char ucRxPath;
// 	unsigned char ucRFBand;	
// 	unsigned char ucPolarization;
// 	unsigned char ucRxThresholdMode;
// 	float fRxThresholdValue;// 소수점 2자리
// 	unsigned char ucAntennaDirection;
// 	float fAcquisitionTime; //신호수집시간
// 	unsigned int nNumOfAcqPulse; //신호수집 펄스수
// 	unsigned short nNumOfAcqTimes; // 신호수집 횟수
// 	float fDwellTime; // 신호유무확인시간
// 	unsigned char ucSignalCheckPulseNumber; // 신호유무확인펄스수
// 	unsigned short nCWDecisionPW; // cw판정펄스폭
// 	unsigned char ucNumOfCWChopping; // cw 초핑횟수
// 	unsigned short nCWChoppingInterval; // cw 초핑 간격
// 	unsigned char ucNBDRBandwidth; // 디지털 수신판 대역폭
// 	unsigned int nWBDRBandwidth; // 디지털 수신판 대역폭
// 	unsigned char ucBlankingMode;
// 	float fFOVLimit;
// 	bool bIsFisintTask;
// 	bool bDeinterAoaSelected;
// 	bool bDeinterFrqSelected;
// 	bool bDeinterPwSelected;
// 	bool bDeinterPriSelected;
// 	unsigned char ucRecordAnalResult;
// 	unsigned char ucRecordPDW;
// 	unsigned char ucRecordIQ;	
// 	unsigned char ucHWBlankChannel;
// 	unsigned short usNumOfSWBlank;
// 	string strMemo;		
// 	string strRelativeTaskId;
// 	unsigned char ucRelativeTaskTrigerCond; // 현재 icd에 없는 내용이다.
// 	unsigned short usWBChannelSelection;	
// 	float fSearchCenterFrq;
// 	unsigned char ucRxProhibitFrqPdwProcessMode;
// 	unsigned char ucRepeatCount;
// 	bool bDirectionInvalid;
// 	bool bPloarizationInvalid;
// 	unsigned char ucTaskType; 
// 	bool bScanAnalysis;
// 	bool bIntraAnalysis;
// 	unsigned char ucSrchBandRepeatCount;
// 	int nDwellCount;
// 	bool bRemoveFOVOverPulse;
// 	bool bUseHighBandBRF;
// 	bool bUseLowBandBRF;
// 
// 	stELDBTaskDetail::stELDBTaskDetail()		
// 	{
// 		nSearchBandId = 0;
// 		strTaskId = "";
// 		fSearchStartFrq = 0.0;
// 		fSearchEndFrq= 0.0;
// 		ucDetectIFBandwidth = 0;
// 		ucHighGainIFBandwidth = 0;
// 		ucRxPath = 0;
// 		ucRFBand = 0;	
// 		ucPolarization = 0;
// 		ucRxThresholdMode = 0;
// 		fRxThresholdValue = 0.0;
// 		ucAntennaDirection  = 0;
// 		fAcquisitionTime  = 0.0; 
// 		nNumOfAcqPulse  = 0; 
// 		nNumOfAcqTimes = 0; 
// 		fDwellTime = 0.0;
// 		ucSignalCheckPulseNumber = 0;
// 		nCWDecisionPW = 0;
// 		ucNumOfCWChopping = 0;
// 		nCWChoppingInterval = 0;
// 		ucNBDRBandwidth = 0; 
// 		nWBDRBandwidth = 0;
// 		ucBlankingMode = 0;
// 		fFOVLimit = 0;
// 		bIsFisintTask = 0;
// 		bDeinterAoaSelected = 0;
// 		bDeinterFrqSelected = 0;
// 		bDeinterPwSelected = 0;
// 		bDeinterPriSelected = 0;
// 		ucRecordAnalResult = 0;
// 		ucRecordPDW = 0;
// 		ucRecordIQ = 0;	
// 		ucHWBlankChannel = 0;
// 		usNumOfSWBlank = 0;
// 		strMemo = "";		
// 		strRelativeTaskId = "";
// 		ucRelativeTaskTrigerCond = 0; // 현재 icd에 없는 내용이다.
// 		usWBChannelSelection = 0;
// 		fSearchCenterFrq = 0.0;
// 		ucRxProhibitFrqPdwProcessMode = 0;
// 		 ucRepeatCount = 0;
// 		 bDirectionInvalid = false;
// 		 bPloarizationInvalid = false;
// 		 ucTaskType = 0;
// 		 bScanAnalysis = false;
// 		 bIntraAnalysis = false;
// 		 ucSrchBandRepeatCount = 1;
// 		 nDwellCount = 1;
// 		 bRemoveFOVOverPulse= false;
// 		 bUseHighBandBRF=false;
// 		 bUseLowBandBRF=false;
// 	};	
// }SELDBTaskDetail;
// 
// typedef struct stArrELDBTaskInfo
// {	
// 	char cTaskId[GET_MAX_ARR_VALUE][ARR_BUF_SIZE];	
// 	unsigned short	usSdfId[GET_MAX_ARR_VALUE];
// 	char cMissionId[GET_MAX_ARR_VALUE][ARR_BUF_SIZE];	
// 	char cOperatorId[GET_MAX_ARR_VALUE][ARR_BUF_SIZE];	
// 	char cEquipId[GET_MAX_ARR_VALUE][ARR_BUF_SIZE];	
// 	char cTaskCreatorId[GET_MAX_ARR_VALUE][ARR_BUF_SIZE];	
// 	unsigned int nTaskPriority[GET_MAX_ARR_VALUE];
// 	unsigned char ucAircraftNum[GET_MAX_ARR_VALUE];
// 	unsigned char ucLinkNum[GET_MAX_ARR_VALUE];
// 	char cCreateTime[GET_MAX_ARR_VALUE][ARR_BUF_SIZE];	
// 	char cStartTime[GET_MAX_ARR_VALUE][ARR_BUF_SIZE];	
// 	char cFinishTime[GET_MAX_ARR_VALUE][ARR_BUF_SIZE];	
// 	char cTaskName[GET_MAX_ARR_VALUE][ARR_BUF_NORMAL_LENG];	
// 	unsigned char ucTaskType[GET_MAX_ARR_VALUE];
// 	unsigned char ucTaskStatus[GET_MAX_ARR_VALUE];
// 	bool bIsRelativeTask[GET_MAX_ARR_VALUE];
// 	unsigned char ucEmerTaskType[GET_MAX_ARR_VALUE]; 
// 	bool bIsShowTask[GET_MAX_ARR_VALUE];
// 	bool bIsCheckTask[GET_MAX_ARR_VALUE];
// 	bool bIsUploadTask[GET_MAX_ARR_VALUE];
// 	float fStartFrq[GET_MAX_ARR_VALUE];
// 	float fEndFrq[GET_MAX_ARR_VALUE];
// 	int nNumOfSrchBand[GET_MAX_ARR_VALUE]; /////////////////////////////////////////////////
// 	unsigned short nSearchBandId[GET_MAX_ARR_VALUE];
// 	char cDtailTaskId[GET_MAX_ARR_VALUE][ARR_BUF_SIZE];	
// 	float fSearchStartFrq[GET_MAX_ARR_VALUE];	// 시작 주파수, 소수점 1자리
// 	float fSearchEndFrq[GET_MAX_ARR_VALUE];		// 종료 주파수, 소수점 1자리
// 	unsigned char ucDetectIFBandwidth[GET_MAX_ARR_VALUE];
// 	unsigned char ucHighGainIFBandwidth[GET_MAX_ARR_VALUE];
// 	unsigned char ucRxPath[GET_MAX_ARR_VALUE];
// 	unsigned char ucRFBand[GET_MAX_ARR_VALUE];	
// 	unsigned char ucPolarization[GET_MAX_ARR_VALUE];
// 	unsigned char ucRxThresholdMode[GET_MAX_ARR_VALUE];
// 	float fRxThresholdValue[GET_MAX_ARR_VALUE]; //소수점 2자리
// 	unsigned char ucAntennaDirection[GET_MAX_ARR_VALUE];
// 	float fAcquisitionTime[GET_MAX_ARR_VALUE]; //신호수집시간
// 	unsigned int nNumOfAcqPulse[GET_MAX_ARR_VALUE]; //신호수집 펄스수
// 	unsigned short nNumOfAcqTimes[GET_MAX_ARR_VALUE]; // 신호수집 횟수
// 	float fDwellTime[GET_MAX_ARR_VALUE]; // 신호유무확인시간
// 	unsigned char ucSignalCheckPulseNumber[GET_MAX_ARR_VALUE]; // 신호유무확인펄스수
// 	unsigned short nCWDecisionPW[GET_MAX_ARR_VALUE]; // cw판정펄스폭
// 	unsigned char ucNumOfCWChopping[GET_MAX_ARR_VALUE]; // cw 초핑횟수
// 	unsigned short nCWChoppingInterval[GET_MAX_ARR_VALUE]; // cw 초핑 간격
// 	unsigned char ucNBDRBandwidth[GET_MAX_ARR_VALUE]; // 디지털 수신판 대역폭
// 	unsigned int nWBDRBandwidth[GET_MAX_ARR_VALUE]; // 디지털 수신판 대역폭
// 	unsigned char ucBlankingMode[GET_MAX_ARR_VALUE];
// 	float fFOVLimit[GET_MAX_ARR_VALUE];
// 	bool bIsFisintTask[GET_MAX_ARR_VALUE];
// 	bool bDeinterAoaSelected[GET_MAX_ARR_VALUE];
// 	bool bDeinterFrqSelected[GET_MAX_ARR_VALUE];
// 	bool bDeinterPwSelected[GET_MAX_ARR_VALUE];
// 	bool bDeinterPriSelected[GET_MAX_ARR_VALUE];
// 	unsigned char ucRecordAnalResult[GET_MAX_ARR_VALUE];
// 	unsigned char ucRecordPDW[GET_MAX_ARR_VALUE];
// 	unsigned char ucRecordIQ[GET_MAX_ARR_VALUE];	
// 	unsigned char ucHWBlankChannel[GET_MAX_ARR_VALUE];
// 	unsigned short usNumOfSWBlank[GET_MAX_ARR_VALUE];
// 	char cMemo[GET_MAX_ARR_VALUE][ARR_NOTE_BIG_BUFFER_LENG];			
// 	char cRelativeTaskId[GET_MAX_ARR_VALUE][ARR_BUF_SIZE];	
// 	unsigned char ucRelativeTaskTrigerCond[GET_MAX_ARR_VALUE]; // 현재 icd에 없는 내용이다.
// 	unsigned short usWBChannelSelection[GET_MAX_ARR_VALUE];	
// 	float fSearchCenterFrq[GET_MAX_ARR_VALUE];
// 	unsigned char ucRxProhibitFrqPdwProcessMode[GET_MAX_ARR_VALUE];
// 	unsigned char ucRepeatCount[GET_MAX_ARR_VALUE];
// 	bool bDirectionInvalid[GET_MAX_ARR_VALUE];
// 	bool bPloarizationInvalid[GET_MAX_ARR_VALUE];
// 	unsigned char ucDtailTaskType[GET_MAX_ARR_VALUE]; 
// 	bool bScanAnalysis[GET_MAX_ARR_VALUE];
// 	bool bIntraAnalysis[GET_MAX_ARR_VALUE];	
// 
// 	stArrELDBTaskInfo::stArrELDBTaskInfo()
// 	{		
// 		memset(&cTaskId[0], '\0', ARR_BUF_SIZE);
// 		memset(&cMissionId[0], '\0', ARR_BUF_SIZE);
// 		memset(&cOperatorId[0], '\0', ARR_BUF_SIZE);
// 		memset(&cEquipId[0], '\0', ARR_BUF_SIZE);
// 		memset(&cTaskCreatorId[0], '\0', ARR_BUF_SIZE);		
// 		memset(&cCreateTime[0], '\0', ARR_BUF_SIZE);
// 		memset(&cStartTime[0], '\0', ARR_BUF_SIZE);
// 		memset(&cFinishTime[0], '\0', ARR_BUF_SIZE);
// 		memset(&cTaskName[0], '\0', ARR_BUF_NORMAL_LENG);
// 		memset(&cDtailTaskId[0], '\0', ARR_BUF_SIZE);
// 		memset(&cMemo[0], '\0', ARR_NOTE_BIG_BUFFER_LENG);
// 		memset(&cRelativeTaskId[0], '\0', ARR_BUF_SIZE);
// 	};
// }SELArrDBTaskInfo;
// 
// 
// //================================
// // 3. TABLE : 고이득안테나제어
// //================================
// typedef struct stELDBHighGainAnt
// {
// 	unsigned short nSearchBandId;
// 	string strTaskId;
// 	unsigned char ucHighGainAntennaMode;
// 	float	 fAngle;
// 	float	 fMaxAngle;
// 	double dLatitude; // 소수점 7자리
// 	double dLongitude; // 소수점 7자리
// 	unsigned int nSpeed;
// 	unsigned int nAcceleration;
// 
// 	stELDBHighGainAnt::stELDBHighGainAnt()
// 	{
// 		nSearchBandId = 0;
// 		strTaskId = "";
// 		ucHighGainAntennaMode = 0;
// 		fAngle = 0;
// 		fMaxAngle = 0;
// 		dLatitude = 0.0;
// 		dLongitude = 0.0;
// 		nSpeed = 0;
// 		nAcceleration = 0;
// 	};
// }SELDBHighGainAnt;
// 
// //================================
// //4. TABLE : 전처리필터
// //================================
// typedef struct stELDBPreProceFilter
// {
// 	unsigned short nSearchBandId;
// 	string strTaskId;
// 	unsigned char ucFilterId;
// 	unsigned char ucFilterType;
// 	bool bIsDVEnable;
// 	bool IsFreqFilterApply;
// 	float fFilterMinFreq;	// 소수점 1자리
// 	float fFilterMaxFreq;	// 소수점 1자리
// 	bool bIsPAFilterApply;
// 	float fFilterMinPA;		//소수점 2자리
// 	float fFilterMaxPA;	//소수점 2자리	
// 	bool IsPWFilterApply;
// 	float fFilterMinPW;	//소수점 2자리
// 	float fFilterMaxPW;	//소수점 2자리
// 	bool bIsAOAFilterApply;
// 	float fFilterMinAOA;	// 소수점 1자리
// 	float fFilterMaxAOA;	// 소수점 1자리
// 	bool bIsPolarizationFilterApply;
// 	unsigned char ucFilterPolrarization;
// 	bool bIsCWFilterApply;
// 
// 	stELDBPreProceFilter::stELDBPreProceFilter()
// 	{
// 		nSearchBandId = 0;
// 		strTaskId = "";
// 		ucFilterId = 0;
// 		ucFilterType = 0;
// 		bIsDVEnable = 0;
// 		IsFreqFilterApply = 0;
// 		fFilterMinFreq = 0.0;
// 		fFilterMaxFreq = 0.0;
// 		bIsPAFilterApply = 0;
// 		fFilterMinPA = 0.0;
// 		fFilterMaxPA = 0.0;
// 		IsPWFilterApply = 0;
// 		fFilterMinPW = 0.0;
// 		fFilterMaxPW = 0.0;
// 		bIsAOAFilterApply = 0;
// 		fFilterMinAOA = 0.0;	
// 		fFilterMaxAOA = 0.0;
// 		bIsPolarizationFilterApply = 0;
// 		ucFilterPolrarization = 0;
// 		bIsCWFilterApply = 0;
// 	};
// 
// }SELDBPreProcFilter;
// 
// //================================
// //5. TABLE : SW 블랭킹
// //================================
// typedef struct stELDBSwBlanking
// {
// 	unsigned short nSearchBandId;
// 	string strTaskId;
// 	string strSwBlankName;
// 	float fFrqMin;
// 	float fFrqMax;
// 	unsigned int nPriMin;
// 	unsigned int nPriMax;
// 	unsigned int nPwMin;
// 	unsigned int nPwMax;
// 	unsigned int nIsUsed;
// 
// 	stELDBSwBlanking::stELDBSwBlanking()
// 	{
// 		nSearchBandId = 0;
// 		strTaskId = "";
// 		strSwBlankName = "";
// 		fFrqMin = 0.0;
// 		fFrqMax = 0.0;
// 		nPriMin = 0;
// 		nPriMax = 0;
// 		nPwMin = 0;
// 		nPwMax = 0;	
// 		nIsUsed = 0;
// 	};
// }SELDBSwBlanking;
// 
// //================================
// //5. TABLE : SW 블랭킹
// //================================
// typedef struct stELDBHWBlanking
// {
// 	unsigned short nSearchBandId;
// 	string strTaskId;
// 	string strHWBlankName;
// 	float fFrqMin;
// 	float fFrqMax;
// 	unsigned int nPriMin;
// 	unsigned int nPriMax;
// 	unsigned int nPwMin;
// 	unsigned int nPwMax;
// 
// 	stELDBHWBlanking::stELDBHWBlanking()
// 	{
// 		nSearchBandId = 0;
// 		strTaskId = "";
// 		strHWBlankName = "";
// 		fFrqMin = 0.0;
// 		fFrqMax = 0.0;
// 		nPriMin = 0;
// 		nPriMax = 0;
// 		nPwMin = 0;
// 		nPwMax = 0;	
// 	};
// }SELDBHWBlanking;
// 
// 
// //================================
// //6. TABLE : 고감도 협대역 설정
// //================================
// typedef struct stELDBHighGainNBSetup
// {
// 	unsigned short nSearchBandId;
// 	string strTaskId;
// 	unsigned char ucRecordSpectrum;
// 	unsigned char ucRecordPRF;
// 	unsigned char ucRecordIF;	
// 	float			fSptrStartFreq;
// 	float			fSptrEndFreq;
// 	unsigned int	nSptrAcqTime;
// 	float			fPRFStartFreq;
// 	float			fPRFEndFreq;
// 	unsigned int	nPRFAcqTime; 
// 	float			fIFStartFreq;
// 	float			fIFEndFreq;
// 	unsigned int	nIFAcqTime;
// 
// 	stELDBHighGainNBSetup::stELDBHighGainNBSetup()
// 	{
// 		nSearchBandId = 0;
// 		strTaskId = "";
// 		ucRecordSpectrum = 0;
// 		ucRecordPRF = 0;
// 		ucRecordIF = 0;
// 		fSptrStartFreq = 0.0;
// 		fSptrEndFreq = 0.0;
// 		nSptrAcqTime = 0;
// 		fPRFStartFreq = 0.0;
// 		fPRFEndFreq = 0.0;
// 		nPRFAcqTime = 0; 
// 		fIFStartFreq = 0.0;
// 		fIFEndFreq = 0.0;
// 		nIFAcqTime = 0;
// 	};
// }SELDBHighGainNBSetup;
// 
// typedef struct stELDBCEDThraat
// {
// 	unsigned short nSearchBandId;
// 	string strTaskId;
// 	unsigned short nThreatID;
// 	int nIsPracticalLib;
// 
// 	stELDBCEDThraat::stELDBCEDThraat()
// 	{
// 		nSearchBandId = 0;
// 		strTaskId = "";
// 		nThreatID = 0;
// 		nIsPracticalLib = -1;
// 	};
// }SELDBCEDThreat;
// 
// typedef struct stELDBThraatAlarm
// {
// 	unsigned short nSearchBandId;
// 	string strTaskId;
// 	unsigned short nThreatID;
// 	string strAlarmID;
// 
// 	stELDBThraatAlarm::stELDBThraatAlarm()
// 	{
// 		nSearchBandId = 0;
// 		strTaskId = "";
// 		nThreatID = 0;
// 		strAlarmID = "";
// 	};
// }SELDBThraatAlarm;
// 
// typedef struct stELDBAreaAlarm
// {
// 	string strAreaAlarmID;
// 	unsigned short nSearchBandId;
// 	string strTaskId;
// 	
// 	stELDBAreaAlarm::stELDBAreaAlarm()
// 	{
// 		strAreaAlarmID = "";
// 		nSearchBandId = 0;
// 		strTaskId = "";
// 	};
// }SELDBAreaAlarm;
// 
// typedef struct stELDBWBChannel
// {
// 	unsigned short nSearchBandId;
// 	string strTaskId;
// 	unsigned char ucChannID;
// 	
// 	stELDBWBChannel::stELDBWBChannel()
// 	{
// 		nSearchBandId = 0;
// 		strTaskId = "";
// 		ucChannID = 0;		
// 	};
// }SELDBWBChannel;
// 
// //ELINT과제 ~7개 연관 테이블 조인 구조체
// 
// typedef struct stELDBTaskToWBChannel
// {
// 	SELDBTaskSum			stTaskSum;
// 	SELDBTaskDetail			stTaskDetail;
// 	SELDBHighGainAnt		stHighGainAnt;
// 	SELDBPreProcFilter		stPreProcFilter;
// 	SELDBSwBlanking			stSwBlanking;
// 	SELDBHWBlanking			stHWBlanking;
// 	SELDBHighGainNBSetup	stHighGainNBSetup;
// 	SELDBCEDThreat			stCEDThraat;
// 	SELDBThraatAlarm		stThraatAlarm;
// 	SELDBAreaAlarm			stAreaAlarm;
// 	SELDBWBChannel			stWBChannel;
// }SELDBTaskToWBChannel;
// 
// 
// typedef struct stELDBJoinTask
// {
// 	SELDBTaskSum			stTaskSum;
// 	SELDBTaskDetail			stTaskDetail;	
// 	SELDBPreProcFilter		stPreProcFilter;
// 	SELDBSwBlanking			stSwBlanking;
// 	SELDBCEDThreat			stCEDThraat;
// 	SELDBHighGainAnt		stHighGainAnt;
// 	SELDBHighGainNBSetup	stHighGainNBSetup;	
// }SELJoinDBTask;
// 
// typedef struct stELDBTaskToTaskDetail
// {
// 	SELDBTaskSum			stTaskSum;
// 	SELDBTaskDetail			stTaskDetail;
// }SELDBBTaskToTaskDetail;
// 
// enum ENUM_ELTASK_TYPE
// {
// 	E_TASK_HNB = 1,
// 	E_TASK_HWB,
// 	E_TASK_DNB,
// 	E_TASK_DWB,
// };
// 
// typedef struct stTaskELBasicInfo //ELINT 과제 정보
// {
// 	string			strMissionID;		//임무 ID - 추가
// 	string			strTaskID;			//과제 ID
// 	string			strTaskName;		//과제명
// 	string			strStartTime;		//시작 시간
// 	string			strFinishTime;		//종료 시간
// 	string			strTaskCreatOPID;	//과제 생성자
// 	string			strOperatorID;		//과제 운용사
// 	string			strCreateTime;		//생성 시간
// 	unsigned int	uiAirNo;			//항공기 번호- 추가
// 	unsigned int	uiLinkNo;           //링크 번호 - 추가 삭제
// 	string				strLinkNo;
// 	unsigned short  SearchBandId;		//탐색대역 ID
// 	float			fSearchStartFrq;	//시작주파수
// 	float			fSearchEndFrq;		//종료주파수
// 	unsigned char	ucIFBandwidth;		//IF출력대역폭
// 	unsigned char	ucRxThresholdMode;	//수신임계치 모드
// 	float			fRxThresholdValue;	//수신임계치
// 	float	fAcquisitionTime;	//신호수집시간
// 	unsigned int	uiNumOfAcqPulse;	//신호수집 펄스수
// 	string			strMissionName; // 임무명 추가
// }_TASKELBASICDOCINFO_;
// 
// typedef struct stJoinCKELDBTaskToWBChannel
// {
// 	bool	bTaskMngr;
// 	bool	bTaskDetail;
// 	bool	bProcFilter;
// 	bool	bSWBlank;
// 	bool	bCEDThreat;
// 	bool	bHGainAnt;
// 	bool	bHGainNBSet;
// 	
// 	unsigned int uiFieldsize;
// 
// 	stJoinCKELDBTaskToWBChannel::stJoinCKELDBTaskToWBChannel()
// 	{
// 		bTaskMngr = FALSE;
// 		bTaskDetail = FALSE;		
// 		bProcFilter = FALSE;
// 		bSWBlank = FALSE;		
// 		bCEDThreat = FALSE;
// 		bHGainAnt = FALSE;
// 		bHGainNBSet = FALSE;
// 	
// 		uiFieldsize = 0;
// 	};
// 
// }SELDBTaskJoinCK;
// 
// 
// typedef struct stJoinCKELDBTaskToWBChannelOld
// {
// 	bool	bTaskMngr;
// 	bool	bTaskDetail;
// 	bool	bHGainAnt;
// 	bool	bProcFilter;
// 	bool	bSWBlank;
// 	bool	bHWBlank;
// 	bool	bHGainNBSet;
// 	bool	bCEDThreat;
// 	bool	bThreatAlarm;
// 	bool	bAreaAlarm;
// 	bool	bWBChann;
// 	unsigned int uiFieldsize;
// 
// 	stJoinCKELDBTaskToWBChannelOld::stJoinCKELDBTaskToWBChannelOld()
// 	{
// 		bTaskMngr = FALSE;
// 		bTaskDetail = FALSE;
// 		bHGainAnt = FALSE;
// 		bProcFilter = FALSE;
// 		bSWBlank = FALSE;
// 		bHWBlank = FALSE;
// 		bHGainNBSet = FALSE;
// 		bCEDThreat = FALSE;
// 		bThreatAlarm = FALSE;
// 		bAreaAlarm = FALSE;
// 		bWBChann = FALSE;	
// 		uiFieldsize = 0;
// 	};
// 
// }SELDBTaskJoinCKOld;
// 
// //================================
// // 운용제어 DB 구조체
// //================================
// 
// typedef struct rxProhbitFreq
// {
// 	int		linkNo;
// 	int		id;
// 	float	minFreq;
// 	float	maxFreq;
// 	string	memo;
// }_PROHIBIT_FREQ;
// 
// typedef struct systemVariable
// {
// 	int		linkNo;
// 	float	CWDecisionPW;
// 	int		numOfCWChop;
// 	int		CWChopInterval;
// 	int		numOfPlsLob;
// 	int		numOfLobEmt;
// 	bool	SCSitypeCheck;
// 	bool	SCSitypeSet;
// 	int		SCSitypeRate;
// 	bool	SCFrtypeCheck;
// 	bool	SCFrtypeSet;
// 	int		SCFrtypeRate;
// 	bool	SCFreqCheck;
// 	int		SCFreqSet;
// 	int		SCFreqRate;
// 	bool	SCFreqCPCheck;
// 	int		SCFreqCPSet;
// 	int		SCFreqCPRate;
// 	bool	SCPolarCheck;
// 	bool	SCPolarSet;
// 	int		SCPolarRate;
// 	bool	SCMopCheck;
// 	bool	SCMopSet;
// 	int		SCMopRate;
// 	bool	SCPWCheck;
// 	int		SCPWSet;
// 	int		SCPWRate;
// 	bool	SCPrtypeCheck;
// 	bool	SCPrtypeSet;
// 	int		SCPrtypeRate;
// 	bool	SCPriCheck;
// 	int		SCPriSet;
// 	int		SCPriRate;
// 	bool	SCPriCPCheck;
// 	int		SCPriCPSet;
// 	int		SCPriCPRate;
// 	bool	SCSCtypeCheck;
// 	bool	SCSCtypeSet;
// 	int		SCSCtypeRate;
// 	bool	SCSCProdCheck;
// 	int		SCSCProdSet;
// 	int		SCSCProdRate;
// 	bool	SCLocaTNCheck;
// 	int		SCLocaTNSet;
// 	int		SCLocaTNRate;
// 	int		SCECertainMin;
// 	int		SCEUncertnMin;
// 	int		SCEUncertnMax;
// 	int		SCECantdsMax;
// 	int		iPodTempPeriod;
// 	UINT	iCEDDefaultIdentifyLibType;
// 	UINT	iUnIdentifiedEmitterDeleteTime;	//미식별 에미터 삭제 시간(초)
// 	UINT	iHGADirectionTxPeriod;	//고이득안테나 방위각정보 전송주기(ms)
// 	UINT	iWBSManualTaskAcqTime;		//광대역 스펙트럼 수동과제 회당 수집시간(ms)
// 	UINT	iAutoReportCreationLimit;	//보고서 자동생성 임계값(%)
// 	bool	bHGTaskPosEstimation;	//고이득 과제 위치산출
// 	float	fMinDI;
// 	float	fMaxDI;	
// 	UINT	iEOBDefaultIdentifyLibType;
// 	UINT	iSDManualTaskAcqTime;
// 	UINT	iWBSManualTaskNumOfAcq;
// 	UINT	iSDManualTaskNumOfAcq;	
// 	float	fBlankTacanDmeStartFreq;
// 	float	fBlankTacanDmeStopFreq;
// 	float	fBlankWeatherStartFreq;
// 	float	fBlankWeatherStopFreq;
// 	float	fBlankIffStartFreq;
// 	float	fBlankIffStopFreq;
// 	float	fBlankTcasStartFreq;
// 	float	fBlankTcasStopFreq;
// 
// 	systemVariable::systemVariable(){
// 		linkNo=0;
// 		CWDecisionPW=0;
// 		numOfCWChop=0;
// 		CWChopInterval=0;
// 		numOfPlsLob=0;
// 		numOfLobEmt=0;
// 		SCSitypeCheck=0;
// 		SCSitypeSet=0;
// 		SCSitypeRate=0;
// 		SCFrtypeCheck=0;
// 		SCFrtypeSet=0;
// 		SCFrtypeRate=0;
// 		SCFreqCheck=0;
// 		SCFreqSet=0;
// 		SCFreqRate=0;
// 		SCFreqCPCheck=0;
// 		SCFreqCPSet=0;
// 		SCFreqCPRate=0;
// 		SCPolarCheck=0;
// 		SCPolarSet=0;
// 		SCPolarRate=0;
// 		SCMopCheck=0;
// 		SCMopSet=0;
// 		SCMopRate=0;
// 		SCPWCheck=0;
// 		SCPWSet=0;
// 		SCPWRate=0;
// 		SCPrtypeCheck=0;
// 		SCPrtypeSet=0;
// 		SCPrtypeRate=0;
// 		SCPriCheck=0;
// 		SCPriSet=0;
// 		SCPriRate=0;
// 		SCPriCPCheck=0;
// 		SCPriCPSet=0;
// 		SCPriCPRate=0;
// 		SCSCtypeCheck=0;
// 		SCSCtypeSet=0;
// 		SCSCtypeRate=0;
// 		SCSCProdCheck=0;
// 		SCSCProdSet=0;
// 		SCSCProdRate=0;
// 		SCLocaTNCheck=0;
// 		SCLocaTNSet=0;
// 		SCLocaTNRate=0;
// 		SCECertainMin=0;
// 		SCEUncertnMin=0;
// 		SCEUncertnMax=0;
// 		SCECantdsMax=0;
// 		iPodTempPeriod=0;
// 		iCEDDefaultIdentifyLibType=0;
// 		iUnIdentifiedEmitterDeleteTime=100;
// 		iHGADirectionTxPeriod=500;
// 		iWBSManualTaskAcqTime=1000;
// 		iAutoReportCreationLimit=100;
// 		bHGTaskPosEstimation=true;
// 		fMinDI=0.0;
// 		fMaxDI=(float) 359.9;
// 		iEOBDefaultIdentifyLibType=0;
// 		iSDManualTaskAcqTime=0;
// 		iWBSManualTaskNumOfAcq=0;
// 		iSDManualTaskNumOfAcq=0;
// 		fBlankTacanDmeStartFreq = 0.0;
// 		fBlankTacanDmeStopFreq = 0.0;
// 		fBlankWeatherStartFreq = 0.0;
// 		fBlankWeatherStopFreq = 0.0;
// 		fBlankIffStartFreq = 0.0;
// 		fBlankIffStopFreq = 0.0;
// 		fBlankTcasStartFreq = 0.0;
// 		fBlankTcasStopFreq = 0.0;
// 	}
// }_SYSTEM_VARIABLE;
// 
// enum JOIN_TASK_TYPE 
// {
// 	DTCT_WB = 0,
// 	DTCT_NB,
// 	HIGH_GAIN_WB,
// 	HIGH_GAIN_NB,
// 	TASK_ALL
// }; 
// 
// //PDW/IQ/IF 목록창
// typedef struct stELPDWIQIFList
// {
// 	string			strPDWSetID;
// 	string			strTaskID;
// 	string			strSearchBandID;
// 	string			strLinkNum; //#FA_Q_2502_T1
// 	string			strAETNo;
// 	string			strABTNo;
// 	string			strLOBNo;
// 	string			strNumOfData;
// 	string			strPDWID;
// 	string			strDataType;
// 	string			strDTOA;
// 	string			strSignalType;
// 	string			strPolFlag;
// 	string			strFMOPFlag;
// 	string			strPMOPFlag;
// 	string			strBlankingTag;
// 	string			strCHChangePop;
// 	string			strBLK;
// 	string			strDIVaLID;
// 	string			strFOVFlag;
// 	string			strCHNo;
// 	string			strPA;
// 	string			strFreq;
// 	string			strDOA;
// 	string			strPolarization;
// 	string			strPPTTag;
// 	string			strPW;
// 	string			strIData;
// 	string			strQData;
// 	string			strPRFSetID;
// 	string			strSpectrumSetID;
// 	string			strRawDataID;
// 	string			strPulseArrivalTime;
// 	string			strDtctID;
// 	string			strFileName;
// 	string			strMissionID;
// 	string			strTaskName;
// 	unsigned long long ullSeqNum;
// 	
// 	stELPDWIQIFList::stELPDWIQIFList():
// 		ullSeqNum(0)	
// 		,strPDWSetID("")
// 		,strTaskID("")
// 		,strSearchBandID("")
// 		,strLinkNum("")
// 		,strAETNo("")
// 		,strABTNo("")
// 		,strLOBNo("")
// 		,strNumOfData("")
// 		,strPDWID("")
// 		,strDataType("")
// 		,strDTOA("")
// 		,strSignalType("")
// 		,strPolFlag("")
// 		,strFMOPFlag("")
// 		,strPMOPFlag("")
// 		,strBlankingTag("")
// 		,strCHChangePop("")
// 		,strBLK("")
// 		,strDIVaLID("")
// 		,strFOVFlag("")
// 		,strCHNo("")
// 		,strPA("")
// 		,strFreq("")
// 		,strDOA("")
// 		,strPolarization("")
// 		,strPPTTag("")
// 		,strPW("")
// 		,strIData("")
// 		,strQData("")
// 		,strPRFSetID("")
// 		,strSpectrumSetID("")
// 		,strRawDataID("")
// 		,strPulseArrivalTime("")
// 		,strDtctID("")
// 		,strFileName("")
// 		,strMissionID("")
// 		,strTaskName("")
// 	{};
// }SELDBPDWIQIFList;
// 
// 
// typedef struct stELArrPDWIQIFList
// {
// 	char cPDWSetID[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cTaskID[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cSearchBandID[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cLinkNum[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cAETNo[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];	
// 	char cLOBNo[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cNumOfData[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cPDWID[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cDataType[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cDTOA[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cSignalType[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cPolFlag[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cFMOPFlag[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cPMOPFlag[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cBlankingTag[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cCHChangePop[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cBLK[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cDIVaLID[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cFOVFlag[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cCHNo[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cPA[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cFreq[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cDOA[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cPolarization[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cPPTTag[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cPW[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cIData[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cQData[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cPRFSetID[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cSpectrumSetID[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cRawDataID[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cPulseArrivalTime[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cDtctID[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cFileName[ARR_EL_INSERT_SIZE][ARR_BUF_NOTE_SIZE];
// 	char cMissionID[ARR_EL_INSERT_SIZE][ARR_BUF_NORMAL_LENG];
// 	char cTaskName[ARR_EL_INSERT_SIZE][ARR_BUF_NOTE_SIZE];
// 	UINT uiSeqNum[ARR_EL_INSERT_SIZE];
// 	UINT uiABTNo[ARR_EL_INSERT_SIZE];
// 	stELArrPDWIQIFList::stELArrPDWIQIFList()
// 	{
// 		memset(cPDWSetID, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cTaskID, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cSearchBandID, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cLinkNum, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cAETNo, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cLOBNo, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cNumOfData, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cPDWID, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cDataType, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cDTOA, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cSignalType, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cPolFlag, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cFMOPFlag, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cPMOPFlag, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cBlankingTag, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cCHChangePop, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cBLK, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cDIVaLID, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cFOVFlag, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cCHNo, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cPA, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cFreq, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cDOA, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cPolarization, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cPPTTag, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cPW, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cIData, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cQData, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cPRFSetID, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cSpectrumSetID, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cRawDataID, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cPulseArrivalTime, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cDtctID, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cFileName, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NOTE_SIZE);
// 		memset(cMissionID, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NORMAL_LENG);
// 		memset(cTaskName, 0, ARR_EL_INSERT_SIZE*ARR_BUF_NOTE_SIZE);
// 		memset(uiSeqNum, 0, sizeof(unsigned int) * ARR_EL_INSERT_SIZE);
// 		memset(uiABTNo,0, sizeof(unsigned int) * ARR_EL_INSERT_SIZE);
// 	};
// }SELDBArrPDWIQIFList;
// 
// typedef struct stELTSG
// {
// 	unsigned int	uiLinkNo;
// 	unsigned int	uiTypeOfReceiver;
// 	unsigned int	uiTypeOfSignal;
// 	float			fFreq;	
// 	unsigned int	uiPRI;
// 	unsigned int	uiPW;
// 	int			iPA;
// 	unsigned int	uiStartOfStop;
// 	unsigned int	uiBand;
// 	unsigned int	uiResult;
// 	
// stELTSG::stELTSG():
// 		uiLinkNo(0),
// 		uiTypeOfReceiver(0),
// 		uiTypeOfSignal(0),
// 		fFreq(0),
// 		uiPRI(0),
// 		uiPW(0),
// 		iPA(0),
// 		uiStartOfStop(0),
// 		uiBand(0),
// 		uiResult(0)
// 	{}
// }SELDBELTSG;
// 
// typedef struct stELOperCtrlStatus
// {
// 	unsigned int	uiLinkNo;
// 	unsigned int	uiAngleOfDetAnt;
// 	unsigned int	uiHGAntAutStat;
// 	unsigned int	uiHGAntAutoAcc;
// 	unsigned int	uiHGAntOprStat;
// 	string			strHGAntOperator;
// 	string			strAcqStartTime;
// 	string			strAcqEndTime;
// 	unsigned int	uiCalReqStat;	
// 	unsigned int	uiCalProgress;
// 	unsigned int	uiCalDetResult;
// 	unsigned int	uiCalHGResult;
// 	unsigned int	uiSelectTask;
// 	unsigned int	uiAcqStartMode;
// 	unsigned int	uiAcqStopMode;
// 	unsigned int	uiOperationStatus;
// 	unsigned int	uiTaskTxResult;
// 	unsigned int	uiAcqStartResult;
// 	unsigned int	uiAcqStopResult;
// 	unsigned int	uiSbcResetStatus;
// 	unsigned int	uiSbcResetResult;
// 	unsigned int	uiDetCtrlResult;
// 	unsigned int	uiHgCtrlOperStat;
// 	unsigned int	uiHgCtrlMode;
// 	unsigned int	uiHgCtrlSpeed;
// 	double			dbHgCtrlLatitude;
// 	double			dbHgCtrlLongitude;
// 	float			fHgCtrlAngle;
// 	float			fHgCtrlMaxAn;
// 	unsigned int	uiHgCtrlAccel;
// 	unsigned int	uiHgCtrlResult;
// 	unsigned int	uiHgCurMode;
// 	float			fHgCurAngle;
// 	unsigned int	uiHgCurCtrlAble;
// 	string			strPodTemp;
// 	string			strHgCtrlSwitchTime;
// 	unsigned int	uiSimulatorMode;
// 	string			strMyIP;
// 	string			strServerIP;
// 	string			strMissionID;
// 
// stELOperCtrlStatus::stELOperCtrlStatus():
// 	 	uiLinkNo(0),
// 	 	uiAngleOfDetAnt(0),
// 	 	uiHGAntAutStat(0),
// 	 	uiHGAntAutoAcc(0),
// 	 	uiHGAntOprStat(0),
// 	 	uiCalReqStat(0),	
// 	 	uiCalProgress(0),
// 	 	uiCalDetResult(0),
// 	 	uiCalHGResult(0),
// 	 	uiSelectTask(0),
// 	 	uiAcqStartMode(0),
// 	 	uiAcqStopMode(0),
// 	 	uiOperationStatus(0),
// 	 	uiTaskTxResult(0),
// 	 	uiAcqStartResult(0),
// 	 	uiAcqStopResult(0),
// 	 	uiSbcResetStatus(0),
// 	 	uiSbcResetResult(0),
// 	 	uiDetCtrlResult(0),
// 	 	uiHgCtrlOperStat(0),
// 	 	uiHgCtrlMode(0),
// 	 	uiHgCtrlSpeed(0),
// 		dbHgCtrlLatitude(0.0),
// 		dbHgCtrlLongitude(0.0),
// 		fHgCtrlAngle(0.0),
// 		fHgCtrlMaxAn(0.0),
// 	 	uiHgCtrlAccel(0),
// 	 	uiHgCtrlResult(0),
// 	 	uiHgCurMode(0),
// 		fHgCurAngle(0.0),
// 	 	uiHgCurCtrlAble(0),
// 		uiSimulatorMode(0)	,
// 		strPodTemp(""),
// 		strHGAntOperator(""),
// 		strHgCtrlSwitchTime("")	
// 	{}
// }SELDBELOperCtrlStatus;
// 
// typedef struct stELNoiseLevel
// {
// 	string			strNoiseID;
// 	unsigned short  usSearchBandID;
// 	string			strTaskId;
// 	unsigned int	uiNoiseLevel;
// 	unsigned int	uiCreateTime;
// 
// 	stELNoiseLevel::stELNoiseLevel():
// 	strNoiseID(""),
// 		usSearchBandID(0),
// 		strTaskId(""),
// 		uiNoiseLevel(0),
// 		uiCreateTime(0)
// 	{}
// }SELDBNoiseLevel;
// 
// typedef struct stWBSpecStatus
// {
// 	unsigned char	ucLinkNO;
// 	unsigned char	ucAcqStauts;
// 	string			strCurTaskID;
// 	unsigned int	uiCurBandID;
// 	unsigned int	uiListAcqCnt;
// 	unsigned int	uiAllAcqCnt;
// 	unsigned char	ucLimitFreqAply;
// 
// 	stWBSpecStatus::stWBSpecStatus():
// 		ucLinkNO(0),
// 		ucAcqStauts(0),
// 		strCurTaskID(""),
// 		uiCurBandID(0),
// 		uiListAcqCnt(0),
// 		uiAllAcqCnt(0),
// 		ucLimitFreqAply(0)
// 	{}
// }SELDBWBSpecStatus;
// 
// struct SELDBWBSpecList
// {
// 	unsigned char	ucLinkNO;
// 	string			strListName;
// 	string			strTaskID;
// 	unsigned char	ucRxLimitMode;
// 	float			fRxLimitVal;
// 	unsigned char	ucPolarization;
// 	unsigned char	ucRepeatMode;
// 	unsigned int	uiNumOfRepeat;
// 	unsigned char	ucAntDirection;
// 	unsigned char	ucRxPath;
// 	unsigned int	uiListAcqTime;
// 	unsigned int	uiAllAcqTime;
// 	unsigned char	ucHWBlankUse;
// 	unsigned int	uiBlankChannl;
// 	bool			bShowProhibitSignal;
// 
// 	SELDBWBSpecList::SELDBWBSpecList():
// 		ucLinkNO(0),
// 		strListName(""),
// 		strTaskID(""),
// 		ucRxLimitMode(0),
// 		fRxLimitVal(0),
// 		ucPolarization(0),
// 		ucRepeatMode(0),
// 		uiNumOfRepeat(0),
// 		ucAntDirection(0),
// 		ucRxPath(0),
// 		uiListAcqTime(0),
// 		uiAllAcqTime(0),
// 		ucHWBlankUse(0),
// 		uiBlankChannl(0),
// 		bShowProhibitSignal(true)
// 	{}
// };
// 
// struct SELDBWBSpecScanBand
// {
// 	unsigned int	uiBandID;
// 	unsigned char	ucLinkNO;
// 	string			strListName;
// 	string			strTaskID;
// 	unsigned char	ucSelectCheck;
// 	float			fStartFreq;
// 	float			fEndFreq;
// 	unsigned int	uiAcqTime;
// 	unsigned int	uiPatrolBW;
// 
// 	SELDBWBSpecScanBand::SELDBWBSpecScanBand():
// 		uiBandID(0),
// 		ucLinkNO(0),
// 		strListName(""),
// 		strTaskID(""),
// 		ucSelectCheck(0),
// 		fStartFreq(0),
// 		fEndFreq(0),
// 		uiAcqTime(0),
// 		uiPatrolBW(0)
// 	{}
// };
// 
// struct SELDBWBSpecListToScanBand
// {
// 	SELDBWBSpecList				stWBSList;
// 	SELDBWBSpecScanBand		stWBSScanBand;
// };
// 
// // 과제 SET 관련 구조체
// struct SELDBTaskSet
// {
// 	string strTaskSetID;
// 	string strTaskSetName;
// 	string strCreateTime;
// 	string strMemo;
// 	SELDBTaskSet::SELDBTaskSet():
// 		strTaskSetID(""),
// 		strTaskSetName(""),
// 		strCreateTime(""),
// 		strMemo("")
// 	{}
// };
// 
// // 과제 SET 후보 구조체
// struct SELDBTaskSetCandidate
// {
// 	string strTaskSetID;
// 	string strTaskID;
// 	string strTaskName;
// 	int nTaskSetOrder;
// 	SELDBTaskSetCandidate::SELDBTaskSetCandidate():
// 		strTaskSetID(""),
// 		strTaskID(""),
// 		strTaskName(""),
// 		nTaskSetOrder(0)
// 	{}
// };
// 
// 
// // *** 알람 및 연관과제 설정 ** //
// struct SELDBAlarmAndAssocTask
// {
// 	string strAlarmTaskTableId;
// 	string strTitle;
// 	string strEmitterTableId;
// 	string strIdentifyTableId;
// 	string strPosTableId;
// 	string strAircraftTableId;
// 	string strAlarmTableId;
// 	string strAssocTaskTableId;
// 	string strOperatorIdCreated;
// 	int		iIsUsed;
// 	int		iIsMapDrawEmitter;
// 	int		iIsMapDrawThreat;
// 	int		iIsMapDrawAbt;
// 	int		iIsMapDrawLob;
// 	SELDBAlarmAndAssocTask::SELDBAlarmAndAssocTask():
// 		strAlarmTaskTableId(""),
// 		strTitle(""),
// 		strEmitterTableId(""),
// 		strIdentifyTableId(""),
// 		strPosTableId(""),
// 		strAircraftTableId(""),
// 		strAlarmTableId(""),
// 		strAssocTaskTableId(""),
// 		strOperatorIdCreated(""),
// 		iIsUsed(0),
// 		iIsMapDrawEmitter(0),
// 		iIsMapDrawThreat(0),
// 		iIsMapDrawAbt(0),
// 		iIsMapDrawLob(0)
// 		{}
// };
// 
// // 에미터 제원 정보
// struct SELDBAlarmEmitter
// {
// 	string strAlarmEmitterTableId;
// 	string strAlarmTaskTableId;
// 	string strElnot;
// 	string strModSign;
// 	string	strFuncSign;
// 	int		iEEPMajorAxis;
// 	float	fRFMin;
// 	float fRFMax;
// 	int		iPRIMin;
// 	int		iPRIMax;
// 	int		iPWMin;
// 	int		iPWMax;
// 	int		iPulsePerGrp;
// 
// 	SELDBAlarmEmitter::SELDBAlarmEmitter():
// 		strAlarmEmitterTableId(""),
// 		strAlarmTaskTableId(""),
// 		strElnot(""),
// 		strModSign(""),
// 		strFuncSign(""),
// 		iEEPMajorAxis(-1),
// 		fRFMin(0.0),
// 		fRFMax(0.0),
// 		iPRIMin(-1),
// 		iPRIMax(-1),
// 		iPWMin(-1),
// 		iPWMax(-1),
// 		iPulsePerGrp(-1)	
// 		{}
// };
// 
// // 식별 정보
// struct SELDBAlarmIdentify
// {
//   string strAlarmIdentifyTableId;
//   string strAlarmTaskTableId; 
//   int		iPinNum;
//   string strBeNum;
//   string strFuncCode;
// 
//   SELDBAlarmIdentify::SELDBAlarmIdentify():
//   strAlarmIdentifyTableId(""),
// 	strAlarmTaskTableId(""),
// 	strBeNum(""),
// 	strFuncCode(""),
// 	iPinNum(-1)
//   {}
// };
// 
// // 연관과제 설정 제원
// struct SELDBAlarmAssocTask
// {
// 	string strAssocTaskTableId;
// 	string strAlarmTaskTableId;
// 	string strSrchTaskName;
// 	string strSrchTaskId;
// 	string strHgTaskName;
// 	string strHgTaskId;
// 	int iSimultCollect;
// 	int iRunImmediately;
// 	int	iRepetitionSet;
// 	int iPeriodicity;
// 	int iNumOfRepeat;
// 
// 	SELDBAlarmAssocTask::SELDBAlarmAssocTask():
// 		strAssocTaskTableId(""),
// 		strAlarmTaskTableId(""),
// 		strSrchTaskName(""),
// 		strSrchTaskId(""),
// 		strHgTaskName(""),
// 		strHgTaskId(""),
// 		iSimultCollect(-1),
// 		iRunImmediately(-1),
// 		iRepetitionSet(-1),
// 		iPeriodicity(-1),
// 		iNumOfRepeat(-1)
// 		{}
// };
// 
// // 신호수집항공기 정보
// struct SELDBAlarmAircraft
// {
// 	string strAlarmAircraftTableId;
// 	string strAlarmTaskTableId;
// 	int		iAircraft;
// 	
// 	SELDBAlarmAircraft::SELDBAlarmAircraft():
// 		strAlarmAircraftTableId(""),
// 		strAlarmTaskTableId(""),
// 		iAircraft(-1)
// 		{}
// };
// 
// // 위치제원 정보
// struct SELDBAlarmPos
// {
// 	string strAlarmPosTableId;
// 	string strAlarmTaskTableId;
// 	double dLat;
// 	double dLong;
// 	int		iErrDistance;
// 	int		iPosType;
// 	string strNameAreaInterest;
// 	string strIdAreaInterest;
// 	string strPinNum;
// 	
// 	SELDBAlarmPos::SELDBAlarmPos():
// 		strAlarmPosTableId(""),
// 		strAlarmTaskTableId(""),
// 		dLat(0.0),
// 		dLong(0.0),
// 		iErrDistance(-1),
// 		iPosType(-1),
// 		strNameAreaInterest(""),
// 		strIdAreaInterest(""),
// 		strPinNum("")
// 		{}
// };
// 
// // 경보 설정 정보
// struct SELDBAlarmLink
// {
// 	string strAlarmLinkTableId;
// 	string strAlarmTaskTableId;
// 	string strAlarmId;
// 	string strAlarmName;
// 	int		iAlarmPriority;
// 	
// 	SELDBAlarmLink::SELDBAlarmLink():
// 		strAlarmLinkTableId(""),
// 		strAlarmTaskTableId(""),
// 		strAlarmId(""),
// 		strAlarmName(""),
// 		iAlarmPriority(-1)
// 		{}
// };
// 
// // 경보 대상 설정 정보
// struct SELDBAlarmLinkOper
// {
// 	string strAlarmLinkOperTableId;
// 	string strAlarmLinkTableId;
// 	string strAlarmTaskTableId;
// 	string strOperId;
// 	
// 	SELDBAlarmLinkOper::SELDBAlarmLinkOper():
// 		strAlarmLinkOperTableId(""),	
// 		strAlarmLinkTableId(""),
// 		strAlarmTaskTableId(""),
// 		strOperId("")
// 		{}
// };
// 
// // 경보 선택 운용자 설정 정보
// struct SELDBAlarmTableSlelct
// {
// 	string strAlarmTableSelectId;
// 	string strAlarmTaskTableId;
// 	string strOperId;
// 		
// 	SELDBAlarmTableSlelct::SELDBAlarmTableSlelct():
// 		strAlarmTableSelectId(""),	
// 		strAlarmTaskTableId(""),
// 		strOperId("")	
// 		{}
// };
// 
// // 임무 시도 횟수 정보
// struct SELDBMissionTrial
// {
// 	string strTableId;
// 	string strMissionId;
// 	int		iCount;
// 	int	iTrialMode;
// 	string strIP;
// 	
// 	SELDBMissionTrial::SELDBMissionTrial():
// 		strTableId(""),	
// 		strMissionId(""),
// 		iCount(0),
// 		iTrialMode(0),
// 		strIP("")
// 		{}
// };
// 
// // 환경변수
// struct SELDBEnvVar
// {
// 	unsigned long long ullSeqId;	
// 	int iVarCwDecPw;
// 	int iVarCwChopCount;
// 	int iVarCwChopSpan;
// 	int iVarNrtThreshold;
// 	int iMtskWbSpCollTime;
// 	int iMtskWbSpCollNum;
// 	int iMtskSpinDFCollTime;
// 	int iMtskSpinDFCollNum;
// 	int iMtskDVRatio; // 2016.2.8. 추가. LOB 방탐유효 판단을 위한 DV 비율
// 	int iEmmgNumOfMinPulseToLob;
// 	int iEmmgNumOfMinLobToBeam;
// 	int iEmmgEmitterDelTime;	
// 	int iEmmgUseHgLOBToPosEst; // 2016.2.8. 추가. 고감도경로수집 LOB 위치산출활용
// 	int iMiscPodTempPeriodSec;
// 	int iMiscHgAntInfoPeriodMilSec;
// 	int iMiscLatLongDisplayOption;
// 	int iMiscDistanceUnit;
// 	int iMapDispWithPinNum;
// 	int iMapRgbDtAntRange;	
// 	int iMapRgbDtAntRangeFig;
// 	int iMapRgbAetKnown;
// 	int iMapRgbAetKnownFig;
// 	int iMapRgbAetUnknown;
// 	int iMapRgbAetUnknownFig;
// 	int iMapRgbAetNew;
// 	int iMapRgbAetNewFig;
// 	int iMapRgbAetValidPosEst;
// 	int iMapRgbAetValidPosEstFig;
// 	int iMapRgbAetInvalidPosEst;
// 	int iMapRgbAetInvalidPosEstFig;
// 	int iMapRgbAbtValidPosEst;
// 	int iMapRgbAbtValidPosEstFig;
// 	int iMapRgbAbtInvalidPosEst;
// 	int iMapRgbAbtInvalidPosEstFig;
// 	int iMapRgbDtLobValid;
// 	int iMapRgbDtLobValidFig;
// 	int iMapRgbDtLobInvalid;
// 	int iMapRgbDtLobInvalidFig;
// 	int iMapRgbHgLob;
// 	int iMapRgbHgLobFig;
// 	int iMapRgbOtherSiteLob;
// 	int iMapRgbOtherSiteLobFig;
// 	int iMapRgbThreatDefaultSymbol;
// 	int iMapRgbThreatDefaultSymbolFig;
// 	int iMapDtAntFOVDeg;  // 2016.2.8. 추가. 탐지안테나 가시 범위 - 각도 (DEG)
// 	int iMapDtAntRangeMeter;  // 2016.2.8. 추가. 탐지안테나 가시 범위 - 길이 (METER)
// 	int iMapLobLength; //2017.12.07. 추가
// 	int iTextSize; //2017.12.07. 추가
// 	int iBitMapSize; 
// 	char szBitMap[204800]; // BitMap 저장용 (2525b symbol) 여유잡고. 200 KB. 통상 100 KB 이내 크기임.
// 	string strOperId;
// 	string strTime;
// 	// TacRep
// 	string strRptTacRepRcvrAndSender; // 수신/송신 국소
// 	string strRptTacRepDefaultAddressee; // 기본 수신처
// 	string strRptTacRepDistributor; // 배부처
// 	string strRptTacRepDefaultAddressor; // 출처
// 	string strRptTacRepSourceSender; // 송신처 
// 	string strRptTacRepRoute; // 중계
// 	string strRptTacRepEndOfHeader; // 전문형태
// 	string strRptTacRepSendPriority;	
// 	// Tacelint
// 	string strRptTacElintPublisher; // 발행부서
// 	string strRptTacElintCollector; // 수집소
// 
// 	// Uniform C
// 	string strRptUniformCSecretLevel; // 비밀등급
// 	string strRptUniformCSensor; // 수집센서
// 	string strRptUniformCCollector; // 수집소 출처
// 	string strRptUniformCPlatform; // 수집 플렛폼
// 	string strRptUniformCSigKind; // 신호 긴급성
// 
// 	// 2525B SymbolCode
// 	string str2525BDefaultSymbology;
// 	
// 	string strUnitCode; // 부대부호 (2자리) 2017.12.07 추가
// 	SELDBEnvVar::SELDBEnvVar():
// 	ullSeqId(0),
// 	strOperId(""),
// 	strTime(""),
// 	iVarCwDecPw(130),
// 	iVarCwChopCount(5),
// 	iVarCwChopSpan(500),
// 	iVarNrtThreshold(3),
// 	iMtskWbSpCollTime(500),
// 	iMtskWbSpCollNum(100),
// 	iMtskSpinDFCollTime(50),
// 	iMtskSpinDFCollNum(50),
// 	iMtskDVRatio(60),
// 	iEmmgNumOfMinPulseToLob(50),
// 	iEmmgNumOfMinLobToBeam(5),
// 	iEmmgEmitterDelTime(5),
// 	iEmmgUseHgLOBToPosEst(0),
// 	iBitMapSize(0),
// 	iTextSize(3),
// 	iMapLobLength(400000),
// 	strUnitCode("AA"),
// 	strRptTacRepRcvrAndSender(""), // 수신국소
// 	strRptTacRepDefaultAddressee(""),
// 	strRptTacRepDistributor(""),
// 	strRptTacRepDefaultAddressor(""),
// 	strRptTacRepSourceSender(""),
// 	strRptTacRepSendPriority(""),
// 	strRptTacRepRoute(""),
// 	strRptTacRepEndOfHeader(""),
// 	strRptTacElintPublisher(""),
// 	strRptTacElintCollector(""),
// 	strRptUniformCSecretLevel(""),
// 	strRptUniformCSensor(""),
// 	strRptUniformCCollector(""),
// 	strRptUniformCPlatform(""),
// 	strRptUniformCSigKind(""),
// 	str2525BDefaultSymbology("IPGPSRU-------E"),
// 	iMiscPodTempPeriodSec(5),
// 	iMiscHgAntInfoPeriodMilSec(200),
// 	iMiscLatLongDisplayOption(0),
// 	iMiscDistanceUnit(0),
// 	iMapDispWithPinNum(0),
// 	iMapRgbDtAntRange(0),
// 	iMapRgbAetKnown(0),
// 	iMapRgbAetUnknown(0),
// 	iMapRgbAetNew(0),
// 	iMapRgbAetValidPosEst(0),
// 	iMapRgbAetInvalidPosEst(0),
// 	iMapRgbAbtValidPosEst(0),
// 	iMapRgbAbtInvalidPosEst(0),
// 	iMapRgbDtLobValid(0),
// 	iMapRgbDtLobInvalid(0),
// 	iMapRgbHgLob(0),
// 	iMapRgbOtherSiteLob(0),
// 	iMapRgbThreatDefaultSymbol(0),
// 	iMapRgbDtAntRangeFig(0), // 도형 모양
// 	iMapRgbAetKnownFig(0),
// 	iMapRgbAetUnknownFig(0),
// 	iMapRgbAetNewFig(0),
// 	iMapRgbAetValidPosEstFig(0),
// 	iMapRgbAetInvalidPosEstFig(0),
// 	iMapRgbAbtValidPosEstFig(0),
// 	iMapRgbAbtInvalidPosEstFig(0),
// 	iMapRgbDtLobValidFig(0),
// 	iMapRgbDtLobInvalidFig(0),
// 	iMapRgbHgLobFig(0),
// 	iMapRgbOtherSiteLobFig(0),
// 	iMapRgbThreatDefaultSymbolFig(0),
// 	iMapDtAntFOVDeg(60),
// 	iMapDtAntRangeMeter(400000) 	
// 		{
// 	memset(&szBitMap, 0, 204800); // BitMap 저장용 (2525b symbol)
// };
// 
// 	void operator=(const SELDBEnvVar &i_rhs){
// 		ullSeqId											=					i_rhs.ullSeqId;	
// 		iVarCwDecPw								=					i_rhs.iVarCwDecPw;
// 		iVarCwChopCount							=						   i_rhs.iVarCwChopCount;
// 		 iVarCwChopSpan							=						i_rhs.iVarCwChopSpan;
// 		 iVarNrtThreshold							=					   i_rhs.iVarNrtThreshold;
// 		 iMtskWbSpCollTime						=						i_rhs.iMtskWbSpCollTime;
// 		 iMtskWbSpCollNum						=					   i_rhs.iMtskWbSpCollNum;
// 		 iMtskSpinDFCollTime						=						i_rhs.iMtskSpinDFCollTime;
// 		 iMtskSpinDFCollNum						=					   i_rhs.iMtskSpinDFCollNum;
// 		 iMtskDVRatio								=						 i_rhs.iMtskDVRatio; // 2016.2.8. 추가. L
// 		 iEmmgNumOfMinPulseToLob			=						i_rhs.iEmmgNumOfMinPulseToLob;
// 		 iEmmgNumOfMinLobToBeam		=					  i_rhs.iEmmgNumOfMinLobToBeam;
// 		 iEmmgEmitterDelTime					=						i_rhs.iEmmgEmitterDelTime;	
// 		 iEmmgUseHgLOBToPosEst			=						 i_rhs.iEmmgUseHgLOBToPosEst; // 201
// 		 iMiscPodTempPeriodSec				=						 i_rhs.iMiscPodTempPeriodSec;
// 		 iMiscHgAntInfoPeriodMilSec			=						 i_rhs.iMiscHgAntInfoPeriodMilSec;
// 		 iMiscLatLongDisplayOption			=							  i_rhs.iMiscLatLongDisplayOption;
// 		 iMiscDistanceUnit							=					   i_rhs.iMiscDistanceUnit;
// 		 iMapDispWithPinNum						=					   i_rhs.iMapDispWithPinNum;
// 		 iMapRgbDtAntRange						=					i_rhs.iMapRgbDtAntRange;	
// 		 iMapRgbDtAntRangeFig					=						 i_rhs.iMapRgbDtAntRangeFig;
// 		 iMapRgbAetKnown						=						   i_rhs.iMapRgbAetKnown;
// 		 iMapRgbAetKnownFig					=						  i_rhs.iMapRgbAetKnownFig;
// 		 iMapRgbAetUnknown					=							 i_rhs.iMapRgbAetUnknown;
// 		 iMapRgbAetUnknownFig				=							i_rhs.iMapRgbAetUnknownFig;
// 		 iMapRgbAetNew							=							 i_rhs.iMapRgbAetNew;
// 		 iMapRgbAetNewFig						=						   i_rhs.iMapRgbAetNewFig;
// 		 iMapRgbAetValidPosEst					=						  i_rhs.iMapRgbAetValidPosEst;
// 		 iMapRgbAetValidPosEstFig				=						 i_rhs.iMapRgbAetValidPosEstFig;
// 		 iMapRgbAetInvalidPosEst				=						  i_rhs.iMapRgbAetInvalidPosEst;
// 		 iMapRgbAetInvalidPosEstFig			=						 i_rhs.iMapRgbAetInvalidPosEstFig;
// 		 iMapRgbAbtValidPosEst					=						  i_rhs.iMapRgbAbtValidPosEst;
// 		 iMapRgbAbtValidPosEstFig				=						 i_rhs.iMapRgbAbtValidPosEstFig;
// 		 iMapRgbAbtInvalidPosEst				=						  i_rhs.iMapRgbAbtInvalidPosEst;
// 		 iMapRgbAbtInvalidPosEstFig			=						 i_rhs.iMapRgbAbtInvalidPosEstFig;
// 		 iMapRgbDtLobValid						=							 i_rhs.iMapRgbDtLobValid;
// 		 iMapRgbDtLobValidFig					=						   i_rhs.iMapRgbDtLobValidFig;
// 		 iMapRgbDtLobInvalid						=						i_rhs.iMapRgbDtLobInvalid;
// 		 iMapRgbDtLobInvalidFig					=					   i_rhs.iMapRgbDtLobInvalidFig;
// 		 iMapRgbHgLob								=						  i_rhs.iMapRgbHgLob;
// 		 iMapRgbHgLobFig							=						 i_rhs.iMapRgbHgLobFig;
// 		 iMapRgbOtherSiteLob					=						   i_rhs.iMapRgbOtherSiteLob;
// 		 iMapRgbOtherSiteLobFig				=						  i_rhs.iMapRgbOtherSiteLobFig;
// 		 iMapRgbThreatDefaultSymbol		=						  i_rhs.iMapRgbThreatDefaultSymbol;
// 		 iMapRgbThreatDefaultSymbolFig	=							 i_rhs.iMapRgbThreatDefaultSymbolFig;
// 		 iMapDtAntFOVDeg 						=					 i_rhs.iMapDtAntFOVDeg;  // 2016.2.8. 
// 		 iMapDtAntRangeMeter					=					i_rhs.iMapDtAntRangeMeter;  // 2016.2
// 		 iMapLobLength								=					i_rhs.iMapLobLength; //2017.12.07. 추
// 		 iTextSize										=					i_rhs.iTextSize; //2017.12.07. 추가
// 		 iBitMapSize 									=					  i_rhs.iBitMapSize; 
// 
// 		//memcpy((void*)&ullSeqId, (void*)(const_cast<SELDBEnvVar*>(&i_rhs)), sizeof(unsigned long long ) +sizeof(int)*49) ;
// 		memcpy((void*)szBitMap, (void*)const_cast<char*>(i_rhs.szBitMap), 204800);
// 		strOperId = i_rhs.strOperId;
// 		strTime = i_rhs.strTime;
// 		strUnitCode = i_rhs.strUnitCode;
// 		strRptTacRepRcvrAndSender = i_rhs.strRptTacRepRcvrAndSender; // 수신국소
// 		strRptTacRepDefaultAddressee = i_rhs.strRptTacRepDefaultAddressee;
// 		strRptTacRepDistributor = i_rhs.strRptTacRepDistributor;
// 		strRptTacRepDefaultAddressor = i_rhs.strRptTacRepDefaultAddressor;
// 		strRptTacRepSourceSender = i_rhs.strRptTacRepSourceSender;
// 		strRptTacRepRoute = i_rhs.strRptTacRepRoute;
// 		strRptTacRepEndOfHeader = i_rhs.strRptTacRepEndOfHeader;	
// 		strRptTacRepSendPriority = i_rhs.strRptTacRepSendPriority;
// 		strRptTacElintPublisher = i_rhs.strRptTacElintPublisher;
// 		strRptTacElintCollector = i_rhs.strRptTacElintCollector;
// 		strRptUniformCSecretLevel = i_rhs.strRptUniformCSecretLevel;
// 		strRptUniformCSensor = i_rhs.strRptUniformCSensor;
// 		strRptUniformCCollector = i_rhs.strRptUniformCCollector;
// 		strRptUniformCPlatform = i_rhs.strRptUniformCPlatform;
// 		strRptUniformCSigKind = i_rhs.strRptUniformCSigKind;
// 		str2525BDefaultSymbology = i_rhs.str2525BDefaultSymbology;
// 	}	
// };
// 
// // 환경변수 (보고서 개별생성규칙)
// struct SELDBEnvVarRpt
// {
// 	unsigned long long ullSeqId;	
// 	unsigned long long ullEnvSeqId;	
// 	int iIsUse;
// 	int iPinNum;
// 	string strNationality;
// 	string strSendPriority;
// 	string strElnot;
//   string strAddressee;
// 	string strDistributor;
// 	string strRptType;
// 	string strActy;
// 	string strL9F1;
// 	string strL9F5;
// 	string strL9F6;
// 	string strL9F7;
// 
// 	SELDBEnvVarRpt::SELDBEnvVarRpt():
// 	ullSeqId(0),
// 	ullEnvSeqId(0),
// 	iIsUse(0),
// 	iPinNum(0),
// 	strNationality(""), 
// 	strSendPriority(""),
// 	strElnot(""),
// 	strAddressee(""),
// 	strDistributor(""),
// 	strRptType(""),
// 	strActy(""),
// 	strL9F1(""),
// 	strL9F5(""),
// 	strL9F6(""),
// 	strL9F7("")
// 		{};
// 
// 	void operator=(const SELDBEnvVarRpt &i_rhs){
// 		//memcpy((void*)&ullSeqId, (void*)(const_cast<SELDBEnvVarRpt*>(&i_rhs)), sizeof(unsigned long long )*2 +sizeof(int)*2) ;
// 		
// 		ullSeqId = i_rhs.ullSeqId;	
// 		ullEnvSeqId = i_rhs.ullEnvSeqId;	
// 		iIsUse = i_rhs.iIsUse;
// 		iPinNum= i_rhs.iPinNum;
// 		strNationality = i_rhs.strNationality;
// 		strSendPriority = i_rhs.strSendPriority;
// 		strAddressee = i_rhs.strAddressee;
// 		strDistributor = i_rhs.strDistributor;
// 		strRptType = i_rhs.strRptType;		
// 		strElnot = i_rhs.strElnot;
// 		strActy = i_rhs.strActy;
// 		strL9F1 = i_rhs.strL9F1;
// 		strL9F5 = i_rhs.strL9F5;
// 		strL9F6 = i_rhs.strL9F6;
// 		strL9F7 = i_rhs.strL9F7;
// 	}	
// };

// 환경변수 (식별 가중치 규칙)
struct SELDBEnvVarIdnf {
	//unsigned long long ullSeqId;	
	//unsigned long long ullEnvSeqId;
	int iEobIndfRangeNM;   // EOB 기본식별반경 (NM)


	//EnumLibType eCEDDefaultLibType; // 기본식별대상 라이브러리 CED. 기본형 : 0, 실무형 : 1
	//EnumLibType eEOBDefaultLibType; // 기본식별대상 라이브러리 EOB. 기본형 : 0, 실무형 : 1

	int iWeightFrqRange;			// 신호식별가중치-주파수범위
	int iWeightFrqExpRange;   // 신호식별가중치-주파수확장범위
	int iWeightFrqModPeriod; // 신호식별가중치- 주파수변조주기
	int iWeightFrqModPosCnt; //신호식별가중치- 주파수변조 포지션수
	int iWeightFrqModElement; // 신호식별가중치- 주파수변조 엘리먼트
	int iWeightFrqMainObservedValue; // 신호식별가중치 - 주파수 주 관측값
	int iWeightPriRange; // 신호식별가중치 - PRI 범위
	int iWeightPriExpRange; // 신호식별가중치 - PRI 확장 범위
	int iWeightPriModPeriod; // 신호식별가중치 - PRI 변조 주기
	int iWeightPriModPosCount; // 신호식별가중치 - PRI 변조 포지션 수
	int iWeightPriModElement; // 신호식별가중치- PRI 변조 엘리먼트
	int iWeightPriDifferenceInGroup; // 신호식별가중치 - 그룹내 PRI 차
	int iWeightPriMainObservedValue; // 신호식별가중치 - PRI 주 관측값
	int iWeightPaDiffrenceInGroup; // 신호식별가중치 - 그룹 내 PA 차
	int iWeightScanType; // 신호식별가중치 - 스캔형태
	int iWeightScanPeriod; // 신호식별가중치 - 스캔주기
	int iWeightIntraModType; // 신호식별가중치 - 펄스내 변조형태

	int iMarginFrqError; // 신호식별마진 - 주파수 오차
	int iMarginPriError; // 신호식별마진 - PRI 오차
	int iMarginPwError; // 신호식별마진 - PW 오차
	int iMarginErrorRatioCompareToPw; // 신호식별마진 - PW대비오차율
	int iMarginFrqModPeriodErrorRatio; // 신호식별마진 - 주파수 변조주기 오차율
	int iMarginPriModPeriodErrorRatio; // 신호식별마진 - PRI변조주기 오차율
	int iMarginMinRqdFrqRangeNestedRatio; // 신호식별마진 - 최소요구 주파수범위 중첩율
	int iMarginMinRqdPriRangeNestedRatio; // 신호식별마진 - 최소요구 PRI범위 중첩율
	int iMarginPaErrorInPulseGroup; // 신호식별마진 -  펄스그룹 내 신호세기차 오차
	int iMarginScanPeriodErrorRatio; // 신호식별마진 - 스캔주기 오차율

	float fMarginFrqError; // (float) 신호식별마진 - 주파수 오차
	float fMarginPriError; // (float) 신호식별마진 - PRI 오차
	float fMarginPwError; // (float) 신호식별마진 - PW 오차
	float fMarginErrorRatioCompareToPw; // (float) 신호식별마진 - PW대비오차율
	float fMarginFrqModPeriodErrorRatio; // (float) 신호식별마진 - 주파수 변조주기 오차율
	float fMarginPriModPeriodErrorRatio; // (float) 신호식별마진 - PRI변조주기 오차율
	float fMarginMinRqdFrqRangeNestedRatio; // (float) 신호식별마진 - 최소요구 주파수범위 중첩율
	float fMarginMinRqdPriRangeNestedRatio; // (float) 신호식별마진 - 최소요구 PRI범위 중첩율
	float fMarginPaErrorInPulseGroup; // (float) 신호식별마진 -  펄스그룹 내 신호세기차 오차
	float fMarginScanPeriodErrorRatio; // (float) 신호식별마진 - 스캔주기 오차율

// 	// 운용제어창에서 관리하는 정보. 연동기로 보내주는 루틴을 통합관리하기 위해서 db에 저장하지는 않지만 환경변수 구조체에서 관리함. 2016.9.28. 이정남
// 	bool bUseHGTaskToPosEstLink1;
// 	bool bUseHGTaskToPosEstLink2;
	float fDIValidLink1;
	float fDIValidLink2;
	
} ;


#endif

