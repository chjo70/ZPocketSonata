//////////////////////////////////////////////////////////////////////////
/*!
 * @file      ELOperationCtrlDataType.h
 * @brief     
 * @author    이성용 (sungyong.lee@lignex1.com)
 * @date      2013-06-17 오후 5:42 
 * @warning   
 */

#ifndef _H_EL_OPERATION_CTRL_DATA_TYPE
#define _H_EL_OPERATION_CTRL_DATA_TYPE
//#include "ELTaskCreateDataType.h"
#include <vector>
using namespace std;

//#include "ELCEDLibDataType.h"       // CED 데이터 타입

// 신호/주파수/PRI 형태 일치율 정의
// #define _DEFAULT_PPG_TYPE_RATE				(10)			// GUI 에 반영할 것
// #define _DEFAULT_SIGNAL_TYPE_RATE			(10)
// #define _DEFAULT_FREQ_TYPE_RATE				(10)
// #define _DEFAULT_PRI_TYPE_RATE				(10)
// #define _DEFAULT_PW_RANGE_RATE				(10)
// 
// 
// enum E_SBC_PROGRESS
// {
// 	E_SBC_IDLE=0,
// 	E_SBC_RCVD_SDF_RCV_READY_RQST_MSG,
// 	E_SBC_TX_SDF_RCV_READY_RQST_ACK_MSG,
// 	E_SBC_RCVING_SDF_MSG,
// 	E_SBC_COMPL_FOLDER_GENERATION,
// 	E_SBC_COMPL_DT_CAL,
// 	E_SBC_COML_HG_CAL,
// 	E_SBC_RCVD_SDF_MSG,
// 	E_SBC_UNDEFINED,
// };
// 
// static const char* szSBCProgress[] = 
// {
// 	"Idle",
// 	"[SDF수신준비요구] 수신완료",
// 	"[SDF수신준비요구응답] 전송완료",
// 	"[SDF전송] 수신중",
// 	"폴더구성 완료",
// 	"탐지보정 완료",
// 	"고감도보정 완료",
// 	"[SDF] 수신완료",
// 	"미정의 상태번호 수신"
// };
// ///////////////////////////////////////////////////////////////////
// // 운용제어
// ///////////////////////////////////////////////////////////////////
// /*!
//  * @struct     SOCRxProhibitFreqInfo
//  * @brief 
//  * @author    이성용 (sungyong.lee@lignex1.com)
//  * @date      2013-06-17 오후 5:42 
//  */
// struct SOCLinkNo
// {
// 	UINT nLinkNo;
// 	SOCLinkNo::SOCLinkNo(){
// 		nLinkNo=(unsigned int)1;
// 	}	
// };
// 
// struct SOCRxProhibitFreqRaw
// {
// 	double dbMinFreq;	//최소주파수
// 	double dbMaxFreq;	//최대주파수
// 	CString strMemo;	//메모
// 	SOCRxProhibitFreqRaw()
// 		:dbMinFreq(0.0)
// 		,dbMaxFreq(0.0)
// 	{
// 		strMemo="";
// 	}
// };
// 
// struct SOCRxProhibitFreqInfo: public SOCLinkNo
// {
// 	vector<SOCRxProhibitFreqRaw> vecInfo;
// 	//bool bUseForAnalysis;	//수신배제 주파수 신호 신호분석에 활용
// 	//bool bDropPDW;		//수신배제 주파수 PDW 버리기
// 	SOCRxProhibitFreqInfo()
// 		//bUseForAnalysis(false),
// 		//bDropPDW(true)
// 
// 	{
// 		//@Start_원종효
// 		vecInfo.clear();
// 		nLinkNo = 1;
// 		//@End_원종효
// 	}
// };
// 
// struct SOCCalibrationInfo: public SOCLinkNo	//오차교정(보정)
// {
// 	//bool bDRPathDetection;	//DR경로 탐지
// 	//bool bDRHighGain;		//DR경로 고감도 
// 	bool bOnlineDetection;	//온라인 탐지
// 	bool bOnHighGain;		//온라인 고감도
// 	bool bBasedOnTask;		//과제기반 보정 수행여부
// 	SOCCalibrationInfo::SOCCalibrationInfo(){
// 		//bDRPathDetection	= true;
// 		//bDRHighGain			= true;
// 		bOnlineDetection	= true;
// 		bOnHighGain		= true;
// 		bBasedOnTask = true;
// 	}
// };
// //BIT 구조체
// 
// enum EnumBitStatus	//자체점검 (고장진단) 상태
// {
// 	E_EL_BS_NORMAL=0,	//정상 (파란색)
// 	E_EL_BS_ACT_ABLE,	//임무가능 (노란색)
// 	E_EL_BS_FAULT,		//고장	(빨간색)
// 	E_EL_BS_UNKNOWN,	//미수행 (흰색) **추가됨
// };
// 
// //#pragma pack(push, 1)
// struct SEIBITInfo
// {
// 	EnumBitStatus eDetectionAntennaRadom_left;	//"탐지안테나/레이돔" (좌)
// 	EnumBitStatus eDetectionAntennaRadom_right;	//"탐지안테나/레이돔" (우)
// 	EnumBitStatus eDetectionSignalReceiver;	//"탐지신호 수신장치"
// 	EnumBitStatus eSignalProcessor;	//"신호처리장치"
// 	EnumBitStatus eHighGainAntennaRadom;	//"고이득안테나/레이돔"
// 	EnumBitStatus eHighGainSignalReceiver;	//"고감도신호 수신장치"
// 	EnumBitStatus eHighGain_Controller;	//"고이득안테나 제어장치"	
// 	EnumBitStatus eStorage;	//"저장장치"
// 	
// 	SEIBITInfo() :
// 		eDetectionAntennaRadom_left(E_EL_BS_UNKNOWN),
//         eDetectionAntennaRadom_right(E_EL_BS_UNKNOWN),
// 		eDetectionSignalReceiver(E_EL_BS_UNKNOWN),
// 		eSignalProcessor(E_EL_BS_UNKNOWN),
// 		eHighGainAntennaRadom(E_EL_BS_UNKNOWN),
// 		eHighGainSignalReceiver(E_EL_BS_UNKNOWN),	
// 		eHighGain_Controller(E_EL_BS_UNKNOWN)	,
// 		eStorage(E_EL_BS_UNKNOWN)
// 	{}
// 	virtual SEIBITInfo::~SEIBITInfo(){}
// };
// struct SPBITInfo : SEIBITInfo
// {
// 	SPBITInfo::SPBITInfo(){
// 	}
// };
// struct SCBITInfo : SEIBITInfo
// {
// 	SCBITInfo::SCBITInfo(){}
// };
// struct SIBITInfo : SEIBITInfo
// {
// 	SIBITInfo::SIBITInfo(){}
// };
// //#pragma pack(pop, 1)
// 
// struct SOCEIBITInfo: public SOCLinkNo	//(운용제어) 고장진단(점검상태)
// {
// 	SPBITInfo stPBIT;	//운용자자체점검
// 	SCBITInfo stCBIT;	//연속자체점검
// 	SIBITInfo stIBIT;	//초기자체점검
// };
// 
// enum EnumBitType : BYTE
// {
// 	E_EL_BIT_PBIT =0,
// 	E_EL_BIT_CBIT,
// 	E_EL_BIT_IBIT
// };
// 
// enum EnumEquipStatus	//장비상태
// {
// 	E_EL_ES_ACTIVE =0,		//ACTIVE
// 	E_EL_ES_INACTIVE =1,	//INACTIVE
// };
// enum EnumMissionStatus
// {
// 	E_EL_MS_GOING_ON =0,	//운용중
// 	E_EL_MS_STAND_BY =1,	//대기중
// 	E_EL_MS_COMPLETE=2,	//완료
// };
// 
// struct SOCMissionInfo : public SOCLinkNo	//(운용제어) 임무정보
// {
// 	CString strMissionID;	//임무ID
// 	CString strMissionName;	//임무명
// 	EnumEquipStatus eEquipStatus;
// 	CTime tStartTime;	//시작일시
// 	CTime tEndTime;		//마감일시
// 	CString strCreator;	//생성자
// 	EnumMissionStatus eMissionStatus;
// 	SOCMissionInfo::SOCMissionInfo(){
// 		eEquipStatus		= E_EL_ES_ACTIVE;
// 		tStartTime			= CTime::GetCurrentTime();
// 		tEndTime			= CTime::GetCurrentTime();
// 		eMissionStatus		= E_EL_MS_STAND_BY;
// 		strMissionID.Format("");
// 		strMissionName.Format("");
// 		strCreator.Format("");
// 	}
// };
// 
// struct SOCMissionInfoNEW : public SOCLinkNo	//임무목록
// {
// 	CString strMissionID;
// 	CString strMissionName;
// 	CString strCreator;
// 	
// 	CString strEquipStatus;
// 	CString strMissionStatus;
// 	CString strOperatingTime;
// 	
// 	CString strMissionStartTime; //13-07-16 11:55:06
// 	CString strMissionEndTime;
// 
// 	CString strWaitingTime;
// 
// 	SOCMissionInfoNEW()
// 	{
// 		strMissionID.Format("");
// 		strMissionName.Format("");
// 		strCreator.Format("");
// 
// 		strEquipStatus.Format("");
// 		strMissionStatus.Format("");
// 		strOperatingTime.Format("");
// 
// 		strMissionStartTime.Format("");
// 		strMissionEndTime.Format("");
// 
// 		strWaitingTime.Format("");
// 	}
// };
// 
// 
// struct SOCTaskInfo : public SOCLinkNo	//과제정보
// {
// 	UINT nNumOfWBDetectionTask;	//탐지 광대역 과제 수
// 	UINT nNumOfNBDetectionTask;	//탐지 협대역 과제 수
// 	UINT nNumOfWBHGTask;		//고감도 광대역 과제 수
// 	UINT nNumOfNBHGTask;		//고감도 협대역 과제 수
// 	CString strTaskStartTime;
// 	CString strTaskEndTime;
// 	/////////////////////////////////////////////////
// 	//CString strTaskID;
// 	//CString strTaskName;
// 	//CString strStartFreq;
// 	//CString strEndFreq;
// 	//EnumTaskStatus e_TaskStatus;
// 	//bool bIsAutoRxLimitMode;
// 	//int nRxLimitValue;
// 	
// 	SOCTaskInfo::SOCTaskInfo(){
// 		nNumOfWBDetectionTask=0;
// 		nNumOfNBDetectionTask=0;
// 		nNumOfWBHGTask=0;
// 		nNumOfNBHGTask=0;
// 		//e_TaskStatus=E_EL_TS_ACQ_ING;
// 		//bIsAutoRxLimitMode=true;
// 		//nRxLimitValue=0;
// 		//@Start_원종효
// 		strTaskStartTime = _T("");
// 		strTaskEndTime = _T("");
// 		//@End_원종효
// 	}
// 	
// };
// 
// enum EnumDetectionAntennaDirection	: BYTE//탐색안테나 방향
// {
// 	E_EL_DAD_LEFT=0,	//좌측
// 	E_EL_DAD_RIGHT	//우측
// };
// 
// struct SOCDetectionAntennaDirection : public SOCLinkNo	//탐색안테나 방향
// {
// 	EnumDetectionAntennaDirection eDirection;
// 	SOCDetectionAntennaDirection::SOCDetectionAntennaDirection(){
// 		eDirection=E_EL_DAD_LEFT;
// 	}
// };
// 
// // 분석제어판 상태는 삭제됨
// //enum EnumSBCStatus	//분석제어판 상태
// //{
// //	E_EL_SBCS_OPERATION,	//운용(중)
// //	E_EL_SBCS_STOP			//중지
// //};
// 
// //struct SOCSBCStatus	//분석제어판 상태
// //{
// //	UINT nLinkNo;	//#1 or #2
// //	EnumSBCStatus eStatus;
// //	OCSBCStatus::OCSBCStatus(){
// //		nLinkNo=1;
// //		eStatus=E_EL_SBCS_STOP;
// //	}
// //};
// 
// enum EnumHGAntennaAllocStatus	//고이득 안테나 상태
// {
// 	E_HGAA_ELINT_AUTO_TASK=0,	//ELINT 자동 과제
// 	E_HGAA_ELINT_MANUAL_TASK=1,	//ELINT 수동 과제
// 	//E_HGAA_FISINT_AUTO_TASK,	//FISINT 자동 과제
// 	//E_HGAA_FISINT_MANUAL_TASK,	//FISINT 수동 과제
// 	E_HGAA_ELINT_STAND_BY=4,	//ELINT 대기
// 	E_HGAA_FISINT=5,	//FISINT
// };
// 
// enum EnumHGAntennaCtrlAuthorityStatus	//고이득 안테나 제어권
// {
// 	E_HGACAS_ELINT_AUTHORITY = 0,	//ELINT 전용 제어
// 	E_HGACAS_FISINT_AUTHORITY = 1,	//FISINT 전용 제어
// //	E_HGACAS_AUTO_AUTHORITY,	//자동 제어
// 	E_HGACAS_NONE_AUTHORITY,
// 
// 	E_MAX_HGACAS_AUTHORITY				// 최대 문자열 갯수
// };
// static const char *stHGAntennaCtrlAuthorityStatus[] = { "ELINT 전용 제어", "FISINT 전용 제어", "-" } ;
// 
// struct SOCAntennaStatus: public SOCLinkNo	//안테나 상태
// {
// 	EnumDetectionAntennaDirection eDAD;
// 	EnumDetectionAntennaDirection eRequestDAD;	//운용자가 요구한 안테나 방향(RadioButton) (추가됨*)
// 	CString strHGOperator;	//고이득 안테나 운용사
// 	UINT nHGElapsedTimeinSec;	//고이득 안테나 운용시간
// 	
// 	EnumHGAntennaAllocStatus eHGAA;								// 고이득 안테나 상태
// 	EnumHGAntennaCtrlAuthorityStatus eHGACAS;			// 고이득 안테나 제어권
// 	
// 	bool bHGAntennaAutoAccpet;	//고이득 안테나 제어권 요청 자동수락
// 	
// 	SOCAntennaStatus() :
// 		eDAD(E_EL_DAD_LEFT),
// 		eRequestDAD(E_EL_DAD_LEFT),
// 		nHGElapsedTimeinSec(0),
// 		eHGAA(E_HGAA_ELINT_AUTO_TASK),
// 		eHGACAS(E_HGACAS_ELINT_AUTHORITY),
// 		bHGAntennaAutoAccpet(false)
// 	{
// 		strHGOperator="";
// 	}
// 
// };
// 
// enum EnumHGAntennaCtrlAuthorityButton	//고이득 안테나 제어권 (버튼)
// {
// 	E_HGCAB_REQUEST,	//제어권 요청
// 	E_HGCAB_CANCLE,		//제어권 해지
// 	E_HGCAB_FORCE_RECALL,	//제어권 강제 회수 (*추가됨)
// };
// struct SOCHGAntennaCtrlAuthorityButton: public SOCLinkNo
// {
// 	EnumHGAntennaCtrlAuthorityButton eButton;
// 	SOCHGAntennaCtrlAuthorityButton::SOCHGAntennaCtrlAuthorityButton(){
// 		eButton=E_HGCAB_REQUEST;
// 	}
// };
// 
// struct SOCCheckBoxSetting: public SOCLinkNo	//체크박스의 설정 여부
// {
// 	bool bCheckBoxSet;	//체크박스 설정시 true
// 	SOCCheckBoxSetting::SOCCheckBoxSetting(){
// 		bCheckBoxSet=false;
// 	}
// };
// 
enum EnumSCRKindTypeSet	//신호일치율 설정 - 종류 일치일 경우
{
	E_SCRKTS_EXACTLY=0,	//정확히 일치
};

enum EnumSCRErrorSet	//신호일치율 설정 - 오차 범위일 경우
{
	E_SCRES_1=1,		//+-1
	E_SCRES_5,			//+-5
	E_SCRES_10,			//+=10
	E_SCRES_20,			//+=20
	E_SCRES_50,			//+-50
	E_SCRES_100,		//+=100
};

struct SOCSCRSetBase	//신호일치율 설정
{
	bool bCheck;	//체크 (선택)
	UINT nSCRate;	//일치율 (1%단위)
	SOCSCRSetBase(){
		bCheck=true;
		nSCRate=0;
	}
};
struct SOCSCRKindTypeSet : public SOCSCRSetBase	//방식: 종류일치일 경우 신호일치율 설정
{
	EnumSCRKindTypeSet eSet;
	SOCSCRKindTypeSet(){
		eSet=E_SCRKTS_EXACTLY;
	}
};
struct SOCSCRErrorSet: public SOCSCRSetBase	//방식: 오차범위일 경우 신호일치율 설정
{
	EnumSCRErrorSet eSet;
	SOCSCRErrorSet(){
		eSet=E_SCRES_1;
	}
};

enum EnumSCREffect	//신호일치율 효과(%)
{
	E_SCRE_0_PERCENT=0,
	E_SCRE_10_PERCENT,
	E_SCRE_20_PERCENT,
	E_SCRE_30_PERCENT,
	E_SCRE_40_PERCENT,
	E_SCRE_50_PERCENT,
	E_SCRE_60_PERCENT,
	E_SCRE_70_PERCENT,
	E_SCRE_80_PERCENT,
	E_SCRE_90_PERCENT,
	E_SCRE_100_PERCENT,
};

// #ifndef ENUM_LIB_TYPE
// #define ENUM_LIB_TYPE
// enum EnumLibType	//라이브러리 타입
// {
// 	E_EL_LIB_TYPE_NORMAL=0,	//기본형
// 	E_EL_LIB_TYPE_PRACTICAL	//실무형
// };
// #endif


// struct SOCSystemVariable 
// {
// 	UINT nCWDecisionPW;					//CW판정폭
// 	UINT nNumOfCWChopping;				//CW 초핑횟수
// 	UINT nCWChoppingGap;				//CW 초핑 간격
// 
// 	UINT nNumOfPulseForLOBCreation;		//LOB 생성을 위한 최소 펄스수
// 	UINT nNumOfLOBForBeamCreation;	//빔 생성을 위한 최소 LOB수
// 
// 	SOCSCRKindTypeSet stSignalType;		//신호일치율 설정: 신호형태
// 	SOCSCRKindTypeSet stFreqType;		//주파수 형태 (방식은 종류 일치임)
// 	SOCSCRErrorSet stFreq;				//주파수
// 	SOCSCRErrorSet stFreqChangePeriod;	//주파수 변경주기
// 	//SOCSCRKindTypeSet stPolarity;		//극성
// 	//SOCSCRKindTypeSet stMOPAnalysis;	//MOP 분석
// 	SOCSCRErrorSet stPW;				//PW
// 	SOCSCRKindTypeSet stPRIType;		//PRI형태
// 	SOCSCRErrorSet stPRI;				//PRI
// 	SOCSCRErrorSet stPRIChangePeriod;	//PRI 변경주기
// 	SOCSCRKindTypeSet stScanType;		//스캔형태
// 	SOCSCRErrorSet stScanPeriod;		//스캔주기
// 	SOCSCRErrorSet stLocation;			//위치
// 
// 	EnumSCREffect eCertainMin;			//신호일치율 효과: 확실-하한 (콤보박스 단위 10%)
// 	EnumSCREffect eUnCertainMin;		//불확실-하한			(콤보박스 단위 10%)
// 	EnumSCREffect eUnCertainMax;		//불확실-상한 (확실-하한과 동일한 %여야 함)	(콤보박스 단위 10%)
// 	EnumSCREffect eCANTDecisionMax;		//판단불가-상한 (불확실-하한과 동일한 %여야 함)	(콤보박스 단위 10%)
// 
// 	UINT nUnIdentifiedEmitterDeleteTime;	//미식별 에미터 삭제 시간(초)
// 	UINT nHGADirectionTxPeriod;	//고이득안테나 방위각정보 전송주기(ms)
// 
// 	//EnumLibType eIdentifyDefaultLib;	//식별대상 라이브러리(삭제예정**)
// 	bool bHGTaskPosEstimation;	//고이득 과제 위치산출
// 
// 	float fMinDI;	//방탐유효성 최소값
// 	float fMaxDI;	//방탐유효성 최대값
// 
// 	SOCSystemVariable::SOCSystemVariable(){
// 		nCWDecisionPW=100;
// 		nNumOfCWChopping=3;
// 		nCWChoppingGap=200;
// 		nNumOfPulseForLOBCreation=100;
// 		nNumOfLOBForBeamCreation=100;
// 
// 		//stSignalType.eSet = E_SCRKTS_EXACTLY;
// 		//stFreqType.eSet = E_SCRKTS_EXACTLY;
// 		//stFreq.eSet = E_SCRES_1;
// 		//stFreqChangePeriod.eSet = E_SCRES_1;
// 		//stPolarity.eSet = E_SCRKTS_EXACTLY;
// 		//stMOPAnalysis.eSet = E_SCRKTS_EXACTLY;
// 		//stPW.eSet = E_SCRES_1;
// 		//stPRIType.eSet = E_SCRKTS_EXACTLY;
// 		//stPRI.eSet = E_SCRES_1;
// 		//stPRIChangePeriod.eSet = E_SCRES_1;
// 		//stScanType.eSet = E_SCRKTS_EXACTLY;
// 		//stScanPeriod.eSet = E_SCRES_1;
// 		//stLocation.eSet = E_SCRES_1;
// 
// 		eCertainMin=E_SCRE_80_PERCENT;
// 		eUnCertainMax=eCertainMin;
// 		eUnCertainMin=E_SCRE_60_PERCENT;
// 		eCANTDecisionMax=eUnCertainMin;
// 
// 		//nPODTempTxPeriod=5;
// 		nUnIdentifiedEmitterDeleteTime=0;
// 		nHGADirectionTxPeriod=0;
// 
// 		//nAutoReportCreationLimit=0;
// 
// 		bHGTaskPosEstimation = true;
// 
// 		fMinDI = 0.0;
// 		fMaxDI = (float) 359.9;
// 
// 		//eCEDIdentifyDefaultLib=E_EL_LIB_TYPE_PRACTICAL;
// 		//eEOBIdentifyDefaultLib=E_EL_LIB_TYPE_PRACTICAL;
// 		//nSpinDFManualTaskAcqTime = 0;
// 		//nWBSManualTaskAcqTime = 0;
// 		//@start_이시온
// 		//nWBSManualTaskAcqNum = 0;
// 		//@end_이시온
// 		//nSpinDFManualTaskAcqTime = 0;
// 		//nSpinDFManualTaskAcqNum =0;	
// 		//fTacanDmeStartFreq = 0.0; 
// 		//fTacanDmeStopFreq = 0.0; 
// 		//fWeatherStartFreq = 0.0; 
// 		//fWeatherStopFreq = 0.0; 
// 		//fIffStartFreq = 0.0;
// 		//fIffStopFreq = 0.0; 
// 		//fTcasStartFreq = 0.0;
// 		//fTcasStopFreq = 0.0; 
// 	}
// };
// 
// struct SOCElintPODTemp: public SOCLinkNo	//ELINT POD온도
// {
// 	//int nPodTemp;	//POD 온도 (정수)
// 	CString strPodTemp; // 탐지신호수신장치 온도
// 	CString strHGTemp; // 고감도수신장치 온도
// 	CString strSPBTemp; // 신호처리장치 온도
// 	SOCElintPODTemp::SOCElintPODTemp() :
// 		strPodTemp("-"),
// 		strHGTemp("-"),
// 		strSPBTemp("-")
// 	{
// 	}
// };
// 
// enum EnumCalibrationResult : BYTE
// {
// 	E_CR_NORMAL=0,	//정상
// 	E_CR_FAULT,		//비정상
// 	E_CR_UNKNOWN,	//미수행 (추가됨**)
// };
// 
// struct SOCCalibrationStatus : public SOCLinkNo // 보정 진행상태 및 결과
// {
// 	UINT nProgressStatus;	//진행상태 (프로그레스바, 0~100%)
// 	EnumCalibrationResult eDetectResult;	//탐지 (보정) 결과
// 	EnumCalibrationResult eHGResult;		//고감도 (보정) 결과
// 	SOCCalibrationStatus::SOCCalibrationStatus(){
// 		nProgressStatus=0;
// 		eDetectResult=E_CR_UNKNOWN;
// 		eHGResult=E_CR_UNKNOWN;
// 	}
// };
// 
// //struct SOCInitializeData	//ELINT 운용제어 전체 초기화 구조체 (삭제예정)
// //{
// //	SOCMissionInfo stMissionInfo;						//임무운용-임무정보
// //	SOCTaskInfo stTaskInfo;								//임무운용-과제정보
// //	SOCAntennaStatus stAntennaStatus;					//임무운용-탐색 안테나 방향, 분석 제어판 상태, 고이득 안테나 상태, 고이득 안테나 제어권 상태 등..
// //	SOCEIBITInfo stBitInfo;								//고장진단-항공 ELINT 점검상태
// //	SOCCalibrationStatus stCalibrationStatus;			//오차교정-보정 진행상태 및 결과
// //	OCElintPODTemp stPODTemp;							//오차교정-POD 온도
// //	vector<SOCRxProhibitFreqInfo> vecProhibitFreqInfo;	//수신배제주파수-수신배제 주파수 목록
// //	SOCSystemVariable stSystemVariable;					//시스템변수
// //};
// 
// enum EnumOCButton
// {
// 	E_EL_OCB_ACQ_START=0,	//수집시작버튼
// 	E_EL_OCB_ACQ_END,		//수집마감버튼
// 	E_EL_OCB_PAUSE,			//일시정지버튼
// 	E_EL_OCB_TASK_LOAD,		//과제불러오기버튼
// 	E_EL_OCB_TASK_CRATE,	//과제생성버튼
// 	E_EL_OCB_DET_AN_APPLY,	//장비제어-탐색안테나-적용버튼을 포함한 Radio버튼 편집 가능 여부
// 	E_EL_OCB_HG_AN_AUTH_FORCE_RECALL,	//고이득 안테나 제어권-강제회수버튼
// 	E_EL_OCB_HG_AN_AUTH_REQUEST,		//제어권요청버튼
// 	E_EL_OCB_HG_AN_AUTH_AUTO_ACCEPT,		//제어권자동수락 (CheckBox) (*추가됨)
// 	E_EL_OCB_SBC_RESET,		//SBC 리셋버튼(고장진단 탭)
// 	E_EL_OCB_RUN_CAL,		//보정수행버튼(오차교정 탭) 을 포함한 체크버튼 편집 가능 여부
// 	E_EL_OCB_PROHIBIT_FREQ,	//수신배제 주파수의 버튼 3개를 포함한 편집 가능 여부
// 	E_EL_OCB_SYSTEM_VARIABLE,	//시스템 변수의 적용 버튼을 포함한 편집 가능 여부
// };
// 
// struct SOCButtonStatus: public SOCLinkNo
// {
// 	EnumOCButton eButton;	//버튼 종류
// 	bool bEnable;			//버튼 Enable(true)/Disable(false) 여부
// 	bool bPause;			//버튼의 이름이 "일시정지(true)" 혹은 "재시작(false)"으로 표시 (*일시정지버튼일 경우만 해당)
// 	SOCButtonStatus():
// 		eButton(E_EL_OCB_ACQ_START),
// 		bEnable(true),
// 		bPause(true)
// 	{}
// };
// 
// struct SOCAuthorityAcceptOrReject : public SOCLinkNo
// {
// 	bool bAccept;	 // 수락여부
// 	SOCAuthorityAcceptOrReject() :
// 		bAccept(true)
// 	{}
// };
// 
// // 2014.11.14. 이정남. 과제세트 관련 구조체 추가
// struct SOpCtWndTaskSetList: public SOCLinkNo	// 과제세트 이름.
// {
// 	std::list<SELTaskSet> stListTaskSet;	
// 	SOpCtWndTaskSetList::SOpCtWndTaskSetList()
// 	{
// 		stListTaskSet = std::list<SELTaskSet>();
// 	};
// };
// 
// struct SOpCtWndTaskSetSelected: public SOCLinkNo	// 과제세트 이름.
// {
// 	std::string strTaskSetId;	
// 	SOpCtWndTaskSetSelected::SOpCtWndTaskSetSelected()
// 	:strTaskSetId(""){};
// };
// //UI에서 과제세트 관리를 위한 구조체 
// struct SOpCtWndTaskSet
// {
// 	CString strTaskSetID;
// 	CString strTaskSetName;
// 	SOpCtWndTaskSet(){
// 		strTaskSetID.Format("");
// 		strTaskSetName.Format("");
// 	}
// };
#endif