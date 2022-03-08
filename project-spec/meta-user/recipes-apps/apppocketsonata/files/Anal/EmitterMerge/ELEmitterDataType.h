#ifndef _H_EL_EMITTER_DATATYPE
#define _H_EL_EMITTER_DATATYPE

#ifndef __VXWORKS__
#include <memory.h>
#endif


#include <string>
#include <list>
using namespace std;

#include "ELMsgDefn.h"

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

//#define MAX_IDCANDIDATE					10

// 사용안함.
typedef struct stEmitterInfoDisp
{
	string strEmitterNum;
	string strDirection;
	string strTaskId;
	string strIsFisintTask; // 2013.6.18. 추가
	string strFrqTypeRange;
	string strPRITypeRange;
	string strSJ;
	string strPwRange;
	string strPaRange;
	string strScanTypePeriod;
	string strElintNoteAir;
	string strPrimFuncAir;
	string strPlatformAir;
	string strIdNumberAir;
	string strConsistRateAir;
	string strElintNoteGnd;
	string strPrimFuncGnd;
	string strPlatformGnd;
	string strIdNumberGnd;
	string strConsisitRateGnd;
	string strEstimated;
	string strRptStat;
	string strSOI;
	string strPosEstimated;
	string strActivatedOrNot;
}_EMITTER_INFO;

// MAX_COLUMN 값은 현재 70개 이며 이상이 될때 이 값도 같이 증가시켜야 한다. , 조철희
// 68개로 하면 S/W가 불안함.
// UpdateHeaderCol()를 같이 고처여 함. 왜 이렇게 만들었는지 모르겠네...
#define NUM_OF_EMITTER_FIELD_NAME 90
typedef struct stEmitterInfo
{
	CString strLinkNum;	 //#FA_Q_2502_T1						// "SDF ID";
	CString strEmitterNum;					// "방사체번호",
	CString strSignalNum;						// "신호일련번호",
	CString strMissionId;						// "임무명",
	CString strTaskId;							// "과제ID",
	CString strTaskName;						// "과제명",
	CString strSrchBandId;					// "탐색대역 id"
	CString strDirection;						// "방위[도]",
	CString strMinDirection;				// "최소 방위[도]",
	CString strMaxDirection;				// "최대 방위[도]",
	CString strDirectionDev;				// "방위편차[도]",
	CString strFisintTask;					// "FISINT과제",
	CString strFrqType;							// "주파수형태",
	CString strFrq;									// "주파수[Hz]",
	CString strMinFrq;							// "최소 주파수[Hz]",
	CString strMaxFrq;							// "최대 주파수[Hz]",
	CString strFrqPatternRange;			// "주파수패턴형태/범위[ms]",
	CString strFrqRangeDev;					// "주파수편차[Hz]",
	CString strPriority;						// "우선순위",
	CString strTime;								// "일자/시간",
	CString strModType;							// "변조형태",
	CString strSigType;		//#FA_Q_2502_T1					// "신호형태",
	CString strPw;									// "PW[ns]",
	CString strMinPw;								// "최소 PW[ns]",
	CString strMaxPw;								// "최대 PW[ns]",
	CString strPa;									// "PA[dB]",
	CString strMinPa;								// "최소 PA[dBm]",
	CString strMaxPa;								// "최대 PA[dBm]",
	CString strPriType;							// "PRI형태",
	CString strPri;									// "PRI[ns]",
	CString strMinPri;							// "최소 PRI",
	CString strMaxPri;							// "최대 PRI",
	CString strPRIPatternRange;			// "PRI패턴형태/범위[ns]",
	CString strPrf;									// "PRF범위[PPS]",
	CString strMinPrf;							// "PRF범위[PPS]",
	CString strMaxPrf;							// "PRF범위[PPS]",
	CString strPulsePerGrp;					// "펄스수/그룹",
	CString strSJ;									// "S/J",
	CString strScanTypePeroid;			// "스캔형태/주기",
	CString strAirElintNotation;		// "[A]E-NOT",
	CString strAirFunc;							// "[A]기능부호",
	CString strAirSiteFunc;					// "[A]사이트기능",
	CString strAirThreat;						// "[A]위협",
	CString strAirEqupNo;						// "[A]장비번호",
	CString strAirConsistancyRatio;	// "[A]일치율[%]",
	CString strAirConsistancy;			// "[A]일치도",
	CString strAirGeoCoord;					// "[A]지리좌표",
	CString strAirAlt;							// "[A]고도[m]",
	CString strAirConfIterval;			// "[A]신뢰구간[m]",
	CString strAirCep;							// "[A]CEP[m]",
	CString strAirMajorAxis;				// "[A]장축[m]",
	CString strAirMinorAxis;				// "[A]단축(m)",
	CString strAirMajorAxisAzimuth; // "[A]장축방위[도]",
	CString strGndElintNotation;		// "[G]E-NOT",
	CString strGndPinNr;						// "[G]PIN NR",
	CString strGndFunc;							// "[G]기능부호",
	CString strGndSiteFunc;					// "[G]사이트기능",
	CString strGndThreat;						// "[G]위협",
	CString strGndEqupNo;						// "[G]장비번호",
	CString strGndConsistancyRatio;	// "[G]일치율[%]",
	CString strGndConsistancy;			// "[G]일치도",
	CString strGndGeoLongitude;			// "[G]지리좌표(경도)",
	CString strGndGeoLatitude;			// "[G]지리좌표(위도)",
	CString strGndAlt;							// "[G]고도[m]",
	CString strGndConfIterval;			// "[G]신뢰구간[m]",
	CString strGndCep;							// "[G]CEP[m]",
	CString strGndMajorAxis;				// "[G]장축[m]",
	CString strGndMinorAxis;				// "[G]단축(m)",
	CString strGndMajorAxisAzimuth; // "[G]장축방위[도]",												
	CString strGndBaseName;					// "[G]기지명",
	CString strGndIdInfo;						// "[G]식별정보",
	CString strGndCandidate;				// "[G]식별 후보 목록",
	CString strGndDistError;				// "[G]거리 오차[km]",
	CString strGndDistErrorToNM;		// "[G]거리 오차[nm]",
	CString strGndEOBId;						// "[G] EOB ID",
	CString strFinalReport;					// "최종보고",							
	CString strFinalAlarm;					// "최종경보",							",
	CString strPosEstimation;				// "산출여부",							
	CString strSOI;									// "관심신호"							
	CString strIsStorePDW;					// "PDW 저장여부"
	CString strNumOfCol;						// "수집개수[PDW/IQ]"
	CString strNumOfAmbigiousBeam;	// "모호성",
	CString strNumOfPDWSet;					// "PDW 세트"
	CString strActivatedOrNot;			// "활동여부"
	CString strLobId;								// "LOB #" . 2014.10.8. 추가. 이정남
	CString strDtctId;							// "Dtct ID" . 2015.3.3. 추가. 이정남
	CString strIdCode;							// "식별 코드" . 2015.3.31. 추가. 조철희
	CString strPolization;					// "극성" . 2015.4.1. 추가. 조철희
	CString strTaskOperator;				// "과제 운용사", 2015.4.7. 추가. 조철희
	CString strGndModeSymbol;					// 모드 부호

	stEmitterInfo()
	{
		strLinkNum="";						
		strEmitterNum="";					
		strSignalNum="";					
		strMissionId="";						
		strTaskId="";							
		strTaskName="";					
		strSrchBandId="";					
		strDirection="";						
		strMinDirection="";				// 
		strMaxDirection="";				
		strDirectionDev="";				
		strFisintTask="";					// 
		strFrqType="";						
		strFrq="";								
		strMinFrq="";							
		strMaxFrq="";						
		strFrqPatternRange="";			
		strFrqRangeDev="";				
		strPriority="";						// 
		strTime="";							
		strModType="";						
		strSigType="";						
		strPw="";								
		strMinPw="";							
		strMaxPw="";							
		strPa="";								
		strMinPa="";							
		strMaxPa="";							
		strPriType="";						
		strPri="";								
		strMinPri="";							
		strMaxPri="";							
		strPRIPatternRange="";			
		strPrf="";								
		strMinPrf="";							
		strMaxPrf="";							
		strPulsePerGrp="";					
		strSJ="";								
		strScanTypePeroid="";			
		strAirElintNotation="";		// "[A
		strAirFunc="";						
		strAirSiteFunc="";					
		strAirThreat="";						
		strAirEqupNo="";					
		strAirConsistancyRatio="";	// 
		strAirConsistancy="";			// 
		strAirGeoCoord="";				
		strAirAlt="";							
		strAirConfIterval="";			// 
		strAirCep="";							
		strAirMajorAxis="";				// 
		strAirMinorAxis="";				// 
		strAirMajorAxisAzimuth=""; //
		strGndElintNotation="";		// 
		strGndPinNr="";						
		strGndFunc="";						
		strGndSiteFunc="";					
		strGndThreat="";					
		strGndEqupNo="";					
		strGndConsistancyRatio="";	
		strGndConsistancy="";			
		strGndGeoLongitude="";			
		strGndGeoLatitude="";			
		strGndAlt="";							
		strGndConfIterval="";			// 
		strGndCep="";						
		strGndMajorAxis="";				
		strGndMinorAxis="";				
		strGndMajorAxisAzimuth=""; 
			strGndBaseName="";				
		strGndIdInfo="";						
		strGndCandidate="";				
		strGndDistError="";				
		strGndDistErrorToNM="";		
		strGndEOBId="";					
		strFinalReport="";					
		strFinalAlarm="";					
		strPosEstimation="";				
		strSOI="";								
		strIsStorePDW="";					
		strNumOfCol="";					
		strNumOfAmbigiousBeam="";	
		strNumOfPDWSet="";				
		strActivatedOrNot="";			
		strLobId="";							
		strDtctId="";							
		strIdCode="";							
		strPolization="";					// 
		strTaskOperator="";				
		strGndModeSymbol="";			
	};

//	void stEmitterInfo::SetInterCommInfo(BYTE *i_pbyInData)
//	{
//		int nCount=0;
//		USHORT nSize=0;
//		
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strLinkNum.SetString((const char*)&i_pbyInData[nCount], nSize) ;								// "SDF ID";
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strEmitterNum.SetString((const char*)&i_pbyInData[nCount], nSize);					// "방사체번호",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strSignalNum.SetString((const char*)&i_pbyInData[nCount], nSize);						// "신호일련번호",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strMissionId.SetString((const char*)&i_pbyInData[nCount], nSize);						// "임무명",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strTaskId.SetString((const char*)&i_pbyInData[nCount], nSize);							// "과제ID",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strSrchBandId.SetString((const char*)&i_pbyInData[nCount], nSize);					// "탐색대역 id"
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strDirection.SetString((const char*)&i_pbyInData[nCount], nSize);						// "방위[도]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strDirectionDev.SetString((const char*)&i_pbyInData[nCount], nSize);				// "방위편차[도]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strFisintTask.SetString((const char*)&i_pbyInData[nCount], nSize);					// "FISINT과제",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strFrqType.SetString((const char*)&i_pbyInData[nCount], nSize);				// "주파수형태",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strFrq.SetString((const char*)&i_pbyInData[nCount], nSize);				// "주파수[Hz]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strMinFrq.SetString((const char*)&i_pbyInData[nCount], nSize);				// "최소 주파수[Hz]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strMaxFrq.SetString((const char*)&i_pbyInData[nCount], nSize);				// "최대 주파수[Hz]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strFrqPatternRange.SetString((const char*)&i_pbyInData[nCount], nSize);			// "주파수패턴형태/범위[ms]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strFrqRangeDev.SetString((const char*)&i_pbyInData[nCount], nSize);					// "주파수편차[Hz]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strPriority.SetString((const char*)&i_pbyInData[nCount], nSize);						// "우선순위",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strTime.SetString((const char*)&i_pbyInData[nCount], nSize);								// "일자/시간",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strModType.SetString((const char*)&i_pbyInData[nCount], nSize);							// "변조형태",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strSigType.SetString((const char*)&i_pbyInData[nCount], nSize);							// "신호형태",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strPw.SetString((const char*)&i_pbyInData[nCount], nSize);							// "PW범위[ns]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strMinPw.SetString((const char*)&i_pbyInData[nCount], nSize);							// "PW범위[ns]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strMaxPw.SetString((const char*)&i_pbyInData[nCount], nSize);							// "PW범위[ns]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strPa.SetString((const char*)&i_pbyInData[nCount], nSize);							// "PA범위[dB]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strMinPa.SetString((const char*)&i_pbyInData[nCount], nSize);							// "PA범위[dB]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strMaxPa.SetString((const char*)&i_pbyInData[nCount], nSize);							// "PA범위[dB]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strPriType.SetString((const char*)&i_pbyInData[nCount], nSize);							// "PRI형태",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strPri.SetString((const char*)&i_pbyInData[nCount], nSize);									// "PRI[ns]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strMinPri.SetString((const char*)&i_pbyInData[nCount], nSize);							// "최소 PRI[ns]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strMaxPri.SetString((const char*)&i_pbyInData[nCount], nSize);							// "최대 PRI[ns]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strPRIPatternRange.SetString((const char*)&i_pbyInData[nCount], nSize);			// "PRI패턴형태/범위[ns]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strPrf.SetString((const char*)&i_pbyInData[nCount], nSize);						// "PRF범위[PPS]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strMinPrf.SetString((const char*)&i_pbyInData[nCount], nSize);						// "PRF범위[PPS]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strMaxPrf.SetString((const char*)&i_pbyInData[nCount], nSize);						// "PRF범위[PPS]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strPulsePerGrp.SetString((const char*)&i_pbyInData[nCount], nSize);					// "펄스수/그룹",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strSJ.SetString((const char*)&i_pbyInData[nCount], nSize);									// "S/J",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strScanTypePeroid.SetString((const char*)&i_pbyInData[nCount], nSize);			// "스캔형태/주기",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strAirElintNotation.SetString((const char*)&i_pbyInData[nCount], nSize);		// "[A]E-NOT",
//		nCount+=nSize;
//
//		//memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		//nCount+=sizeof(USHORT);
//		//strAirPinNr.SetString((const char*)&i_pbyInData[nCount], nSize);						// "[A]PIN NR",
//		//nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strAirFunc.SetString((const char*)&i_pbyInData[nCount], nSize);							// "[A]기능부호",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strAirSiteFunc.SetString((const char*)&i_pbyInData[nCount], nSize);					// "[A]사이트기능",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strAirThreat.SetString((const char*)&i_pbyInData[nCount], nSize);						// "[A]위협",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strAirEqupNo.SetString((const char*)&i_pbyInData[nCount], nSize);						// "[A]장비번호",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strAirConsistancy.SetString((const char*)&i_pbyInData[nCount], nSize);			// "[A]일치율[%]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strAirGeoCoord.SetString((const char*)&i_pbyInData[nCount], nSize);					// "[A]지리좌표",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strAirAlt.SetString((const char*)&i_pbyInData[nCount], nSize);							// "[A]고도[m]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strAirConfIterval.SetString((const char*)&i_pbyInData[nCount], nSize);			// "[A]신뢰구간[m]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strAirCep.SetString((const char*)&i_pbyInData[nCount], nSize);							// "[A]CEP[m]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strAirMajorAxis.SetString((const char*)&i_pbyInData[nCount], nSize);				// "[A]장축[m]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strAirMinorAxis.SetString((const char*)&i_pbyInData[nCount], nSize);				//"[A]단축(m)",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strAirMajorAxisAzimuth.SetString((const char*)&i_pbyInData[nCount], nSize); //"[A]장축방위[도]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strGndElintNotation.SetString((const char*)&i_pbyInData[nCount], nSize);		// "[G]E-NOT",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strGndPinNr.SetString((const char*)&i_pbyInData[nCount], nSize);						// "[G]PIN NR",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strGndFunc.SetString((const char*)&i_pbyInData[nCount], nSize);							// "[G]기능부호",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strGndSiteFunc.SetString((const char*)&i_pbyInData[nCount], nSize);					// "[G]사이트기능",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strGndThreat.SetString((const char*)&i_pbyInData[nCount], nSize);						// "[G]위협",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strGndEqupNo.SetString((const char*)&i_pbyInData[nCount], nSize);						// "[G]장비번호",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strGndConsistancy.SetString((const char*)&i_pbyInData[nCount], nSize);			// "[G]일치율[%]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strGndGeoLongitude.SetString((const char*)&i_pbyInData[nCount], nSize);			//"[G]지리좌표(경도)",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strGndGeoLatitude.SetString((const char*)&i_pbyInData[nCount], nSize);			//"[G]지리좌표(위도)",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strGndAlt.SetString((const char*)&i_pbyInData[nCount], nSize);							// "[G]고도[m]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strGndConfIterval.SetString((const char*)&i_pbyInData[nCount], nSize);			// "[G]신뢰구간[m]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strGndCep.SetString((const char*)&i_pbyInData[nCount], nSize);							// "[G]CEP[m]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strGndMajorAxis.SetString((const char*)&i_pbyInData[nCount], nSize);				// "[G]장축[m]",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strGndMinorAxis.SetString((const char*)&i_pbyInData[nCount], nSize);				//"[G]단축(m)",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strGndMajorAxisAzimuth.SetString((const char*)&i_pbyInData[nCount], nSize); //"[G]장축방위[도]",			
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strFinalReport.SetString((const char*)&i_pbyInData[nCount], nSize);					// "최종보고",			
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strFinalAlarm.SetString((const char*)&i_pbyInData[nCount], nSize);					// "최종경보",							",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strPosEstimation.SetString((const char*)&i_pbyInData[nCount], nSize);				// "산출여부",							
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strSOI.SetString((const char*)&i_pbyInData[nCount], nSize);									// "관심신호"	
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strIsStorePDW.SetString((const char*)&i_pbyInData[nCount], nSize);					// "PDW 저장여부"
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strNumOfCol.SetString((const char*)&i_pbyInData[nCount], nSize);						// "수집개수[PDW/IQ]"
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strNumOfAmbigiousBeam.SetString((const char*)&i_pbyInData[nCount], nSize);	// "모호성",
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strNumOfPDWSet.SetString((const char*)&i_pbyInData[nCount], nSize);					// "PDW 세트"
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strIdCode.SetString((const char*)&i_pbyInData[nCount], nSize);							// "식별 코드"
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strPolization.SetString((const char*)&i_pbyInData[nCount], nSize);					// "극성"
//		nCount+=nSize;
//
//		memcpy(&nSize, &i_pbyInData[nCount], sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		strTaskOperator.SetString((const char*)&i_pbyInData[nCount], nSize);		// "과제 운용사"
//		nCount+=nSize;
//
//	}
//	int stEmitterInfo::GetInterCommInfo(BYTE * i_pbyOutData)
//	{
//		int nCount=0;
//		USHORT nSize=0;
//		
//		nSize=strLinkNum.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strLinkNum.GetBuffer(), nSize);								// "SDF ID";
//		nCount+=nSize;
//		
//		nSize=strEmitterNum.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strEmitterNum.GetBuffer(), nSize);					// "방사체번호",
//		nCount+=nSize;
//
//		nSize=strSignalNum.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strSignalNum.GetBuffer(), nSize);						// "신호일련번호",
//		nCount+=nSize;
//
//		nSize=strMissionId.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strMissionId.GetBuffer(), nSize);						// "임무명",
//		nCount+=nSize;
//
//		nSize=strTaskId.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strTaskId.GetBuffer(), nSize);							// "과제ID",
//		nCount+=nSize;
//
//		nSize=strSrchBandId.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strSrchBandId.GetBuffer(), nSize);					// "탐색대역 id"
//		nCount+=nSize;
//
//		nSize=strDirection.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strDirection.GetBuffer(), nSize);						// "방위[도]",
//		nCount+=nSize;
//
//		nSize=strDirectionDev.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strDirectionDev.GetBuffer(), nSize);				// "방위편차[도]",
//		nCount+=nSize;
//
//		nSize=strFisintTask.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strFisintTask.GetBuffer(), nSize);					// "FISINT과제",
//		nCount+=nSize;
//
//		nSize=strFrqType.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strFrqType.GetBuffer(), nSize);				// "주파수형태",
//		nCount+=nSize;
//
//		nSize=strFrq.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strFrq.GetBuffer(), nSize);				// "주파수[Hz]",
//		nCount+=nSize;
//
//		nSize=strMinFrq.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strMinFrq.GetBuffer(), nSize);				// "최소 주파수",
//		nCount+=nSize;
//
//		nSize=strMaxFrq.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strMaxFrq.GetBuffer(), nSize);				// "최대 주파수",
//		nCount+=nSize;
//
//		nSize=strFrqPatternRange.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strFrqPatternRange.GetBuffer(), nSize);			// "주파수패턴형태/범위[ms]",
//		nCount+=nSize;
//
//		nSize=strFrqRangeDev.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strFrqRangeDev.GetBuffer(), nSize);					// "주파수편차[Hz]",
//		nCount+=nSize;
//
//		nSize=strPriority.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strPriority.GetBuffer(), nSize);						// "우선순위",
//		nCount+=nSize;
//
//		nSize=strTime.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strTime.GetBuffer(), nSize);								// "일자/시간",
//		nCount+=nSize;
//
//		nSize=strModType.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strModType.GetBuffer(), nSize);							// "변조형태",
//		nCount+=nSize;
//
//		nSize=strSigType.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strSigType.GetBuffer(), nSize);							// "신호형태",
//		nCount+=nSize;
//
//		nSize=strPw.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strPw.GetBuffer(), nSize);							// "PW범위[ns]",
//		nCount+=nSize;
//
//		nSize=strMinPw.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strMinPw.GetBuffer(), nSize);							// "PW범위[ns]",
//		nCount+=nSize;
//
//		nSize=strMaxPw.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strMaxPw.GetBuffer(), nSize);							// "PW범위[ns]",
//		nCount+=nSize;
//
//		nSize=strPa.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strPa.GetBuffer(), nSize);							// "PA범위[dB]",
//		nCount+=nSize;
//
//		nSize=strMinPa.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strMinPa.GetBuffer(), nSize);							// "PA범위[dB]",
//		nCount+=nSize;
//
//		nSize=strMaxPa.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strMaxPa.GetBuffer(), nSize);							// "PA범위[dB]",
//		nCount+=nSize;
//
//		nSize=strLinkNum.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strPriType.GetBuffer(), nSize);							// "PRI형태",
//		nCount+=nSize;
//
//		nSize=strLinkNum.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strPri.GetBuffer(), nSize);									// "PRI[ns]",
//		nCount+=nSize;
//
//		nSize=strLinkNum.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strMinPri.GetBuffer(), nSize);							// "최소 PRI[ns]",
//		nCount+=nSize;
//
//		nSize=strLinkNum.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strMaxPri.GetBuffer(), nSize);							// "최대 PRI[ns]",
//		nCount+=nSize;
//
//		nSize=strPRIPatternRange.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strPRIPatternRange.GetBuffer(), nSize);			// "PRI패턴형태/범위[ns]",
//		nCount+=nSize;
//
//		nSize=strPrf.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strPrf.GetBuffer(), nSize);						// "PRF범위[PPS]",
//		nCount+=nSize;
//
//		nSize=strMinPrf.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strMinPrf.GetBuffer(), nSize);						// "PRF범위[PPS]",
//		nCount+=nSize;
//
//		nSize=strMaxPrf.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strMaxPrf.GetBuffer(), nSize);						// "PRF범위[PPS]",
//		nCount+=nSize;
//
//		nSize=strPulsePerGrp.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strPulsePerGrp.GetBuffer(), nSize);					// "펄스수/그룹",
//		nCount+=nSize;
//
//		nSize=strSJ.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strSJ.GetBuffer(), nSize);									// "S/J",
//		nCount+=nSize;
//
//		nSize=strScanTypePeroid.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strScanTypePeroid.GetBuffer(), nSize);			// "스캔형태/주기",
//		nCount+=nSize;
//
//		nSize=strAirElintNotation.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strAirElintNotation.GetBuffer(), nSize);		// "[A]E-NOT",
//		nCount+=nSize;
//
//// 		nSize=strAirPinNr.GetLength();
//// 		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//// 		nCount+=sizeof(USHORT);
//// 		memcpy(&i_pbyOutData[nCount], strAirPinNr.GetBuffer(), nSize);						// "[A]PIN NR",
//// 		nCount+=nSize;
//
//		nSize=strAirFunc.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strAirFunc.GetBuffer(), nSize);							// "[A]기능부호",
//		nCount+=nSize;
//
//		nSize=strAirSiteFunc.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strAirSiteFunc.GetBuffer(), nSize);					// "[A]사이트기능",
//		nCount+=nSize;
//
//		nSize=strAirThreat.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strAirThreat.GetBuffer(), nSize);						// "[A]위협",
//		nCount+=nSize;
//
//		nSize=strAirEqupNo.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strAirEqupNo.GetBuffer(), nSize);						// "[A]장비번호",
//		nCount+=nSize;
//
//		nSize=strAirConsistancy.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strAirConsistancy.GetBuffer(), nSize);			// "[A]일치율[%]",
//		nCount+=nSize;
//
//		nSize=strAirGeoCoord.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strAirGeoCoord.GetBuffer(), nSize);					// "[A]지리좌표",
//		nCount+=nSize;
//
//		nSize=strAirAlt.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strAirAlt.GetBuffer(), nSize);							// "[A]고도[m]",
//		nCount+=nSize;
//
//		nSize=strAirConfIterval.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strAirConfIterval.GetBuffer(), nSize);			// "[A]신뢰구간[m]",
//		nCount+=nSize;
//
//		nSize=strAirCep.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strAirCep.GetBuffer(), nSize);							// "[A]CEP[m]",
//		nCount+=nSize;
//
//		nSize=strAirMajorAxis.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strAirMajorAxis.GetBuffer(), nSize);				// "[A]장축[m]",
//		nCount+=nSize;
//
//		nSize=strAirMinorAxis.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strAirMinorAxis.GetBuffer(), nSize);				//"[A]단축(m)",
//		nCount+=nSize;
//
//		nSize=strAirMajorAxisAzimuth.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strAirMajorAxisAzimuth.GetBuffer(), nSize); //"[A]장축방위[도]",
//		nCount+=nSize;
//
//		nSize=strGndElintNotation.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strGndElintNotation.GetBuffer(), nSize);		// "[G]E-NOT",
//		nCount+=nSize;
//
//		nSize=strGndPinNr.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strGndPinNr.GetBuffer(), nSize);						// "[G]PIN NR",
//		nCount+=nSize;
//
//		nSize=strGndFunc.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strGndFunc.GetBuffer(), nSize);							// "[G]기능부호",
//		nCount+=nSize;
//
//		nSize=strGndSiteFunc.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strGndSiteFunc.GetBuffer(), nSize);					// "[G]사이트기능",
//		nCount+=nSize;
//
//		nSize=strGndThreat.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strGndThreat.GetBuffer(), nSize);						// "[G]위협",
//		nCount+=nSize;
//
//		nSize=strLinkNum.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strGndEqupNo.GetBuffer(), nSize);						// "[G]장비번호",
//		nCount+=nSize;
//
//		nSize=strGndConsistancy.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strGndConsistancy.GetBuffer(), nSize);			// "[G]일치율[%]",
//		nCount+=nSize;
//
//		nSize=strGndGeoLatitude.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strGndGeoLatitude.GetBuffer(), nSize);					//"[G]지리좌표",
//		nCount+=nSize;
//
//		nSize=strGndGeoLongitude.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strGndGeoLongitude.GetBuffer(), nSize);					//"[G]지리좌표",
//		nCount+=nSize;
//
//		nSize=strGndAlt.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strGndAlt.GetBuffer(), nSize);							// "[G]고도[m]",
//		nCount+=nSize;
//
//		nSize=strGndConfIterval.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strGndConfIterval.GetBuffer(), nSize);			// "[G]신뢰구간[m]",
//		nCount+=nSize;
//
//		nSize=strGndCep.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strGndCep.GetBuffer(), nSize);							// "[G]CEP[m]",
//		nCount+=nSize;
//
//		nSize=strGndMajorAxis.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strGndMajorAxis.GetBuffer(), nSize);				// "[G]장축[m]",
//		nCount+=nSize;
//
//		nSize=strGndMinorAxis.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strGndMinorAxis.GetBuffer(), nSize);				//"[G]단축(m)",
//		nCount+=nSize;
//
//		nSize=strGndMajorAxisAzimuth.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strGndMajorAxisAzimuth.GetBuffer(), nSize); //"[G]장축방위[도]",			
//		nCount+=nSize;
//
//		nSize=strFinalReport.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strFinalReport.GetBuffer(), nSize);					// "최종보고",			
//		nCount+=nSize;
//		
//		nSize=strFinalAlarm.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strFinalAlarm.GetBuffer(), nSize);					// "최종경보",							",
//		nCount+=nSize;
//
//		nSize=strPosEstimation.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strPosEstimation.GetBuffer(), nSize);				// "산출여부",							
//		nCount+=nSize;
//
//		nSize=strSOI.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strSOI.GetBuffer(), nSize);									// "관심신호"	
//		nCount+=nSize;
//						
//		nSize=strIsStorePDW.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strIsStorePDW.GetBuffer(), nSize);					// "PDW 저장여부"
//		nCount+=nSize;
//
//		nSize=strNumOfCol.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strNumOfCol.GetBuffer(), nSize);						// "수집개수[PDW/IQ]"
//		nCount+=nSize;
//
//		nSize=strNumOfAmbigiousBeam.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strNumOfAmbigiousBeam.GetBuffer(), nSize);	// "모호성",
//		nCount+=nSize;
//
//		nSize=strNumOfPDWSet.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strNumOfPDWSet.GetBuffer(), nSize);					// "PDW 세트"
//		nCount+=nSize;
//
//		nSize=strActivatedOrNot.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strActivatedOrNot.GetBuffer(), nSize);					// "활동여부"
//		nCount+=nSize;
//
//		nSize=strLobId.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strLobId.GetBuffer(), nSize);					// "LOB ID"
//		nCount+=nSize;
//
//		nSize=strDtctId.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strDtctId.GetBuffer(), nSize);					// "DTCT ID"
//		nCount+=nSize;
//
//		nSize=strIdCode.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strIdCode.GetBuffer(), nSize);					// "식별코드"
//		nCount+=nSize;
//
//		nSize=strPolization.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strPolization.GetBuffer(), nSize);			// "극성"
//		nCount+=nSize;
//
//		nSize=strTaskOperator.GetLength();
//		memcpy(&i_pbyOutData[nCount], &nSize, sizeof(USHORT));
//		nCount+=sizeof(USHORT);
//		memcpy(&i_pbyOutData[nCount], strPolization.GetBuffer(), nSize);			// "과제 운용사"
//		nCount+=nSize;
//
//		return nCount;
//	}
} I_EMITTER_STR;		

#define NUM_OF_LOB_LIST_FIELD_NAME 45
static const char* strLobListFieldName [] =
{
	"순번",
	"LINK번호", // 2015.1.5. 이정남 추가
	"E-NOT",
	"식별코드",
	"과제 운용사",
	"일자/시간",
	"LOB#",
	"AET번호",
	"인트라펄스 변조형태",
	"주파수형태",
	"주파수[MHz]",
	"최소 주파수[MHz]",
	"최대 주파수[MHz]",
	"PW[us]",
	"PRI[us]",
	"PRF[KHz]",
	"그룹당펄스수",
	"PIT",
	"포지션수",
	"AMP",
	"RF Dev[MHz]",
	"DOA",
	"AOA",
	"AzStdDev",
	"AMB",
	"Sid",
	"BL",
	"FOV",
	"AC#",
	"AC위치",
	"AC Alt",
	"AC FOM",
	"Hdg",
	"Pitch",
	"Roll",
	"품질",
	"PDW 개수",
	"스캔형태/주기[ms]",
	"PRI변조형태",
	"PRI지터율",
	"최종보고",
	"과제ID",
	"신호ID",
	"분극",
	"펄스수 그룹"
};

typedef struct stLOBInfoDisp
{
	bool bIsSelected;
	CString strElintNotation;	// "ELINT Notation"
	CString strLinkNum;	   //#FA_Q_2502_T1		// Link 번호, 2015.1.5. 이정남 추가
	CString strSrchTime;			// 	"일자/시간"
	CString strLobNum;			// "LOB#"
	CString strEmitterNum;		// "Emitter#"
	CString strModType;			// "변조형태"
	CString strFrqType;			// "주파수형태",
	CString strFrq;					// "주파수[Hz]",
	CString strMinFrq;				// "최소 주파수[Hz]",
	CString strMaxFrq;			// "최대 주파수[Hz]",
	CString strPW;					// "PW",
	CString strPRI;					// "PRI",
	CString strPRF;					// "PRF",
	CString strMinPRF;			// "최소 PRF[PPS]",
	CString strMaxPRF;			// "최대 PRF[PPS]",
	CString strPulsePerGrp;		// "그룹당펄스수",
	CString strPIT;					// "PIT",
	CString strNumOfPos;		// "포지션수",
	CString strAmp;				// "AMP",
	CString strRfDev;				// "RF Dev.",
	CString strDoa;				// "DOA",
	CString strAoa;				// "AOA",
	CString strAzStdDev;		// "AzStdDev",
	CString strAmb	;				// "AMB",
	CString strSid;					// "Sid",
	CString strBL;					// "BL",
	CString strFov;				// "FOV",
	CString strACNum;			// "AC#",
	CString strACPos;				// "AC위치",
	CString strACAlt;				//"AC Alt",
	CString strAcFom;			// "AC FOM",
	CString strHdg;				// "Hdg",
	CString strPitch;				// "Pitch",
	CString strRoll;					// "Roll",
	CString strQuality;			// "품질",
	CString strNumOfPdw;		// "PDW 개수",
	CString strScanTypePeriod;// "스캔형태/주기",
	CString strPriModType;		// "PRI변조형태",
	CString strPriJitterRate;		//"PRI지터율"
	CString strFinalReport;		// "최종보고"
	CString strTaskId;				// "과제ID" 2014.10.08 추가. 이정남.
	CString strTaskName;			// "과제명" 2015.06.03 추가. 조철희
	CString strDtctId;				// DTCT ID . 2015.3.3. 이정남 추가
	CString strIdCode;				// 식별 코드, 2015.4.2. 조철희 추가
	CString strTaskOperator;	// 과제 운용자, 2015.4.7. 조철희 추가
	CString strPolization;	// 극성. 2015.7.15. 이정남 추가
	CString strPPG;	// 펄스수 그룹. 2015.7.15. 이정남 추가

        stLOBInfoDisp()
		:bIsSelected(false)
	{
		strElintNotation="";
		strLinkNum="";			
		strSrchTime="";			
		strLobNum="";			
		strEmitterNum="";		
		strModType="";			
		strFrqType="";					
		strFrq="";							
		strMinFrq="";						
		strMaxFrq="";					
		strPW="";					
		strPRI="";					
		strPRF="";				
		strMinPRF="";			
		strMaxPRF="";			
		strPulsePerGrp="";		
		strPIT="";					
		strNumOfPos="";		
		strAmp="";				
		strRfDev="";				
		strDoa="";				
		strAoa="";				
		strAzStdDev="";		
		strAmb="";				
		strSid="";					
		strBL="";					
		strFov="";				
		strACNum="";			
		strACPos="";				
		strACAlt="";				
		strAcFom="";			
		strHdg="";				
		strPitch="";				
		strRoll="";					
		strQuality="";			
		strNumOfPdw="";		
		strScanTypePeriod="";
		strPriModType="";		
		strPriJitterRate="";		
		strFinalReport="";		
		strTaskId="";				
		strTaskName="";		
		strDtctId="";				
		strIdCode="";			
		strTaskOperator="";	
		strPolization="";
		strPPG="";
	};
}I_LOB_STR;	

// RAW DATA : PDW 데이터 타입
#define NUM_OF_PDW_HEAD_FIELD_NAME 9
static const char *strPdwHeadFieldName[] = {
	"순번",
	"번호",
	/*"PDW Set ID",*/
	"LINK번호",
	"과제 ID",
	"탐색대역번호",
	/*"방사체 번호",*/
	/*"빔 번호",*/
	"LOB 번호",
	"샘플개수",
	"연관 펄스 번호",
	"형태"
};

#define NUM_OF_PDW_BODY_FIELD_NAME 19
static const char *strPdwBodyFieldName[] = {
	"수집시작시간",
	"평균 DTOA[us]",
	"신호형태",
	"극성 유효성[%]",
	/*"FMOP[%]",
	"PMOP[%]",*/
	"Blanking[%]",
	//"채널변경여부",
	/*"BLK[%]",*/
	"DV[%]",
	"FOV(IN)[%]",
	"Ch#",
	"평균 세기[dBm]",
	"평균 주파수[MHz]",
	"평균 방향[도]",
	"극성[%]",
	"PPF",
	"평균 펄스폭[ns]",
	//"I 데이터",
	//"Q 데이터",
	"PRF ID",
	"Spectrum ID",
	//"DtctId",
	//"과제 운용사",
	"파일명",
	"과제명",
	"부 파일명"
};

struct I_PDWIQIF_STR
{
	CString strPdwSetId; // "PDW Set ID",
	CString strLinkNum; //#FA_Q_2502_T1     // "Link 번호",
	CString strTaskId; // "과제 ID",
	CString strSrchBandId; // "탐색대역번호",
	CString strAetNum; // "AET 번호"
	CString strAbtNum; //"ABT 번호". 2016.6.8. 이정남 추가
	CString strLobNum; // "LOB번호",
	CString strPdwCount; // "PDW개수/IQ개수",
	CString strPdwId; // PDW ID, PDW 연관 번호
	CString strDataType; // "형식", : PDW, IQ, IF
	CString strTime; // "수집시작시간",
	CString strToa; // "TOA",
	CString strSignalType; // "신호형태",
	//CString strBitFlag; //"BIT Flag",
	CString strPolFlag; //"극성 유효성",
	CString strFmopFlag; // "FMOP Flag",
	CString strPmopFlag; // "PMOP Flag",
	CString strBlankingTag; // "Blanking Tag",
	CString strChannelChangePOP; // "채널변경여부",
	CString strBLK; // "채널변경방향",
	CString strDI; //"DI",
	CString strFovFlag; // "FOV Flag",
	CString strChannelNum; // "Ch#",
	CString strPa; // "신호세기",
	CString strFrq; // "측정주파수",
	CString strSigDirection; // "신호방향",
	CString strPolarization; // "신호극성",
	CString strPPFTag; // "PPF Tag",
	CString strPw; // "펄스폭",
	CString strIData; // "I데이터"
	CString strQData; // "Q데이터",	
	CString strFilename;		// 파일명CString strDtctId; // DTCT ID
	CString strTaskName;
	CString strFatherFilename;
	CString strDtctId; // "DTCT ID", 2015.3.3. 이정남 추가
		
	UINT nPRFDBSetID;	//화면표시안됨, PRF 목록-DB의 식별 ID로만 사용
	UINT nSpectrumDBSetID;	//화면표시안됨, Spectrum 목록-DB의 식별 ID로만 사용
	
	//@start_WJH
	I_PDWIQIF_STR()
	{	
	//	strPdwSetId= _T("");
	//	strLinkNum=_T("");// "Link 번호",
	//	strTaskId=_T("");		 // "과제 ID",
	//	strSrchBandId=_T(""); // "탐색대역번호",
	//	strAetNum=_T(""); // "AET 번호"
	//	strAbtNum=_T(""); // "ABT 번호". 2016.6.8. 이정남 추가
	//	strLobNum=_T(""); // "LOB번호",
	//	strPdwCount=_T(""); // "PDW개수/IQ개수",
	//	strPdwId=_T(""); // PDW ID, PDW 연관 번호
	//	strDataType=_T(""); // "형식", : PDW, IQ, IF
	//	strTime=_T(""); // "수집시작시간",
	//	strToa=_T(""); // "TOA",
	//	strSignalType=_T(""); // "신호형태",
	//	strBitFlag=_T(""); //"BIT Flag",
	//	strFmopFlag=_T(""); // "FMOP Flag",
	//	strPmopFlag=_T(""); // "PMOP Flag",
	//	strBlankingTag=_T(""); // "Blanking Tag",
	//	strChannelChangePOP=_T(""); // "채널변경여부",
	//	strBLK=_T(""); // "채널변경방향",
	//	strDI=_T(""); //"DI",
	//	strFovFlag=_T(""); // "FOV Flag",
	//	strChannelNum=_T(""); // "Ch#",
	//	strPa=_T(""); // "신호세기",
	//	strFrq=_T(""); // "측정주파수",
	//	strSigDirection=_T(""); // "신호방향",
	//	strPolarization=_T(""); // "신호극성",
	//	strPPFTag=_T(""); // "PPF Tag",
	//	strPw=_T(""); // "펄스폭",
	//	strIData=_T(""); // "I데이터"
	//	strQData=_T(""); // "Q데이터",	
	//	strFilename=_T("");		// 파일명		
	//	strTaskName=_T(""); // DTCT ID				
	//	strFatherFilename=_T("");
		strDtctId=_T(""); // DTCT ID		

		nPRFDBSetID = 0;
		nSpectrumDBSetID = 0;	
	}	  
	//@end_WJH
} ;



//////////////////////////////////////////////////////////////////////////
// 식별 결과 데이터 구조체 정의
//
#define NUM_OF_IDRESULT_BODY_FIELD_NAME			28
static const char *strIdResultBodyFieldName[] = {
	"순번",
	"식별 대상",
	"식별 후보(CED)",
	"ELNOT",
	"Primary Function"
	"위협명",
	"T 우선순위",
	"위협번호",
	"적아구분",
	"에미터명",
	"최대위협반경[km]",
	"E 우선순위",
	"에미터번호",
	"플랫폼",
	"빔명",
	"B 우선순위",
	"신호형태",
	"MOP형식",
	"주파수 형태 및 범위",
	"PRI 형태 및 범위",
	"펄스폭 범위",
	"스캔 형태/범위",
	"극성",
	"빔폭",
	"빔번호",
	"ELIMENT 데이터/수",
	"식별 후보(EOB)",
	"EOB"
};

typedef struct stIdResultInfoStr
{
	int iBeamId;										// "순번",
	int nLinkNo;										// 링크 번호
	CString strCreateTime;					// 수집 시간
	CString strIdRatio;							//"일치율"
	CString strIdObject;						// "식별 대상",
	CString strIdCandidate;					// "식별 후보 번호",
	CString strElNot;								// "ELNOT",
	CString strPriFunc;							// "Primary Function",
	CString strThreatName;					// "위협명",
	CString strPriority;						// "T 우선순위",
	CString strThreatNum;						// "위협번호",
	CString strFriendOrFoe;					// "적아구분",
	CString strEmitterName;					//"에미터명",
	CString strMaxRadius;						//"최대위협반경",
	CString strEPriority;						//"E 우선순위",
	CString strEmitterNum;					//"에미터번호",
	CString strPlatform;						//"플렛폼",
	CString strBeamName;						//"빔명",
	CString strBPriority;						//"B 우선순위",
	CString strSigType;		//#FA_Q_2502_T1					//"신호형태",
	CString strMopType;							//"MOP형식",
	CString strFreqGroup;						//"RF 형태/최대",
	CString strPRIGroup;						//"PRI 형태/범위",
	CString strPWGroup;							//"펄스폭 범위",		
	CString strASPGroup;						//"스캔 형태/범위",
	CString strPolarity;						//"극성",
	CString strBeamWidth;						//"빔폭",
	CString strEtc;									//"기타",
	short sEOBId;										//"식별 (EOB)"
	float fEOBErrorDistance;				//"거리 오차",
	unsigned int uiEOBPinNumber;		//"PIN #"
	CString strEOBBaseName;					//"지명",
	CString strFunctionCode;				//"구분",
	CString strFacilityName;				//"시설이름",
	CString strSiteStatus;					//"Site상태",
	CString strLongitude;						//"경도[도]",
	CString strLatitude;						//"위도[도]",
	float fElivation;								//"고도[km]",
	CString strADA;									//"방공구역",
	CString strBENumber;						//"BE #",
	CString strCategory;						//"카테고리",
	CString strPrimaryFunction;			//"PF(EOB)",
	CString strNomenclature;				//"명명법",
	CString strElintNotation;				//"ELNOT(EOB)",
	CString strEquipStatus;							//"장비상태",

	stIdResultInfoStr() :	iBeamId(0), sEOBId(0), uiEOBPinNumber(0)
	{}
} I_IDRESULT_STR;


//=======> 이하 사용안할 예정
						  
											
struct I_THREAT_DATA {
	unsigned short usSdfId;
	unsigned char szTaskId[LENGTH_OF_TASK_ID];
	unsigned short usSearchBandId;
	unsigned short usSerialNum;
	unsigned char ucAnalysisStatus;
    I_THREAT_DATA(){
		usSdfId=0;
		memset(&szTaskId, 0, LENGTH_OF_TASK_ID);
		usSearchBandId=0;
		usSerialNum=0;
		ucAnalysisStatus=0;
	}
};

//static const I_THREAT_DATA stInitThreatData;

struct I_AET_DATA {
	unsigned short usAetId;
 	unsigned short usThreatId;
 	unsigned short usEmitterId;
 	unsigned short usBeamId;

	unsigned int uiOpInitID;

#if defined(_ELINT_) || defined(_XBAND_)
	unsigned char	aucTaskID[LENGTH_OF_TASK_ID];
#endif

};

//static const I_AET_DATA g_stInitAETData;


static const char* strIdResult[] = 
{
	"-",
	"기성",
	"신출",
	"불명"
};
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
	int nCoRadarModeIndex;
	int nRadarModeIndex[MAX_IDCANDIDATE];

    int n3LevelRadarModeIndex[THREE_LEVEL_IDCANDIDATE];

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
	E_EL_PESTAT_FAIL=0,					// 위치 산출 후 에러가 난 상태
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
	E_ES_DELETE,								// 미활동 처리
    E_ES_DEACTIVATED,                           // 활동 중지
    E_ES_REACTIVATED,                           // 활동 재개

};

static const char* strBeamEmitterStat[] = 
{
	"-",

	"활동(신규)",
	"활동",
	"미활동",
	"중지",
	"활동(재개)",

};

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

static const char* strBeamEmitterOpcode[] = 
{
 	"객제생성안됨",

	"갱신 ",
	"삭제(E/B)",
	"삭제(L) ",

	"변경 ",
	//////////////////////////////////////////////////////////////////////////
	"상태 ",

	"경보 ",
	"보고서",

	"삭제(E)",

	"상태 변동없음(NoChange)"
};


struct I_AET_ANAL {
	int uiSeqNum;

	//////////////////////////////////////////////////////////////////////////
	// LOB 관리에 필요한 변수
        //int iLinkNum;																								// 수신한 위협 에미터의 링크 번호

	bool isFiltered;																						// 수집 필터 여부
	bool isManualEdited;																				// 수동 편집 여부

	unsigned int uiAETID;
	unsigned int uiABTID;
	unsigned int uiLOBID;

	__time32_t tiAcqTime;																						// 항공에서 분석 시간, LOB 메시지에 time_t 로 되어 있으면 삭제함.
	int tiContactTimems;																				// 항공에서 분석 시간

	E_BEAM_EMITTER_STAT enEmitterStat;													// LOB 상태

        //int iTaskType;																							// 과제 형태 종류

	unsigned int uiCoLOB;																				// LOB 개수

	int iBeamValidity;

	//////////////////////////////////////////////////////////////////////////
	// 식별 추가 정보
	//
	// 식별 후보 정보
	bool bOverCount;
	//int usCoCandidate;
	int usThreatId[MAX_IDCANDIDATE];

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

	bool bCompFreq;
	bool bCompPRI;

} ;

//static I_AET_ANAL g_stInitAETAnal;





typedef struct STempAET
{
	I_THREAT_DATA stThreat;
	I_AET_DATA stAet;
	I_AET_ANAL stAnal;
	STempAET(){
		//memset(&stThreat, 0, sizeof(I_THREAT_DATA));
		//memset(&stAet, 0, sizeof(I_AET_DATA));
		//memset(&stAnal, 0, sizeof(I_AET_ANAL));

	/*	g_stInitThreatData;
		g_stInitAETData;
		g_stInitAETAnal;*/
	}
}I_AET;
static const I_AET g_stInitAET;

/**
 * @typedef   SELLOBDATA_EXT
 * @brief     수신 위협 데이터 구조체 이외에 추가로 들어가는 구조체 정의
 * @author    조철희 (churlhee.jo@lignex1.com)
 */
struct SELLOBDATA_EXT {
	I_AET_ANAL aetAnal;
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
    double dPECoVar[4];

    float fLastAOA;
    float fRadarLatitude;
    float fRadarLongitude;

    // 수동 편집 여부
    bool bIsManualEdited;

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

#endif

	// 수동/자동 위치 결과 정보 여부
    bool bManualPosEstPreferred;
    float fManualLatitude;
    float fManualLongitude;

    //SLOBOtherInfo stLOBOtherInfo;

    int iLOBPoolIndex;

    STR_ID_TYPE stIDType;

    enTHREAT_PLATFORM enPlatform;

    int nCoIdEOB;
    //STR_EOB_RESULT stEOBResult[MAX_CANDIDATE_EOB];

    // 빔 병합 정보
    bool bCompFreq;
    bool bCompPRI;

    // 신규 CED 및 EOB로 식별한 정보
    STR_CEDEOBID_INFO idInfo;

    ENUM_PE_STAT enValid;
    bool bApplayOfLOBClustering;// TRUE: 적용, FALSE: 미적용

    UINT uiPE;
    bool bFullOfPE;
    double dLatitude[MAX_OF_LOBS_PE];
    double dLongitude[MAX_OF_LOBS_PE];
    double dEasting[MAX_OF_LOBS_PE];
    double dNorthing[MAX_OF_LOBS_PE];

    // 스캔 분석 추가 정보
    unsigned int uiTry;
    unsigned int uiScanStep;

#if defined(_ELINT_) || defined(_XBAND_) || defined(_POCKETSONATA_)
    //bool bIsFISINTTask;
    UINT uiOpInitID;

    unsigned int uiSeqNum;
#elif _POCKETSONATA_

#endif

    unsigned uiOpcode;
    time_t tiSendLan;

} ;

struct SELAETDATA_EXT {
	// 누적된 전체 PDW 개수
	int nCoTotalPdw;
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
	unsigned int nUnIDABTID;

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

// typedef struct STempPDW
// {
// 	SRxPDWData stData;
// 	SAvgPDWDataRGroup stAvgData;
// 	//std::list<SRXPDWDataRGroup> listGroup; // 2014.07.15.이정남. 사용하지 않아서 주석처리
// 	STempPDW()
// 	{
// 		memset(&stData, 0, sizeof(SRxPDWData));
// 		memset(&stAvgData, 0, sizeof(SRXPDWDataRGroup));
// 		//stData.Init();
// 		//stAvgData.Init();
// 		//listGroup.clear(); // 2014.07.15.이정남. 사용하지 않아서 주석처리
// 	}
// }I_PDW;

// 방사체/LOB 목록창에서 보고서 작성 메뉴 클릭 시 발생
// struct SEmitterInfoForReport
// {
// 	std::string strDtctId;
// 	std::string strTaskId;
// 	int nAetId;
// 	int nLobId;
// 	bool bFromEmitterWnd;
// 	SEmitterInfoForReport()
// 	: strTaskId("")
// 	, strDtctId("")
// 	, nAetId(-1)
// 	, nLobId(-1)
// 	, bFromEmitterWnd(true){};
// };

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
// 	E_EMITTER_OPCODE eOpCodeForUpdate; // 업데이트 되는 내용이 다양해 져서, Update Key를 둬서 식별하기로 함. 이정남. 2018.4.10.
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
// 	E_EMITTER_OPCODE eOpCodeForUpdate; // 업데이트 되는 내용이 다양해 져서, Update Key를 둬서 식별하기로 함. 이정남. 2018.4.10.
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
// 	E_EMITTER_OPCODE eOpCodeForUpdate; // 업데이트 되는 내용이 다양해 져서, Update Key를 둬서 식별하기로 함. 이정남. 2018.4.10.
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

#endif
