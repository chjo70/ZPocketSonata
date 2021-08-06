#ifndef _H_EL_SCEDLIB_DATA_TYPE
#define _H_EL_SCEDLIB_DATA_TYPE

#pragma once
#include <vector>
#include <map>
using namespace std;

#ifdef _MSC_VER
#else
#include "../SigAnal/_Type.h"
#endif


static const char* strCEDSignalType [] =
{
	"Normal Pulse",
	"CW"
};
#define NUM_OF_CED_SIGNAL_TYPE 2
enum EnumCEDSignalType	//신호형태
{
	E_EL_SIG_ERROR = -3,			// 잘못된 신호 형태
	E_EL_SIG_NO_SELECT	= -2, // 해당사항없음
	E_EL_SIG_ADD_INIT =-1,    // 추가시 초기값 추가 
	E_EL_SIG_NORMAL_PULSE=0,	// NP (Normal Pulse)
	E_EL_SIG_CW,							// CW
};

static const char* strCEDFreqType [] =
{
	"Fixed",
	"Agile",
	"Hopping",
	"Pattern"
};
#define NUM_OF_CED_FREQ_TYPE 4
enum EnumFreqType	//주파수형태
{
	E_EL_FREQ_NO_SELECT = -2,	// 해당사항없음
	E_EL_FREQ_ADD_INIT =-1,   // 추가시 초기값 추가 

	E_EL_FREQ_FIXED=0,				// FIXED
	E_EL_FREQ_HOPPING,				// Hopping
	E_EL_FREQ_AGILE,					// Agile
	E_EL_FREQ_PATTERN					// Pattern
};

static const char* strCEDPriType [] =
{
	"Stable",
	"Stagger",
	"D&S",
	"Pattern"
	"Jitter",
};
#define NUM_OF_CED_PRI_TYPE 5
enum EnumPRIType	//PRI형태
{
	E_EL_PRI_NO_SELECT = -2,	//해당사항없음
	E_EL_PRI_ADD_INIT =-1,       //추가시 초기값 추가 

	E_EL_PRI_STABLE=0,			//Stable
	E_EL_PRI_STAGGER,			//Stagger
	E_EL_PRI_DwellAndSwitch,	//Dwell&Switch
	E_EL_PRI_PATTERN,			//Pattern
	E_EL_PRI_JITTER,			//Jitter
	
};

static const char* strCEDScanType [] =
{
	"Unknown",
	"Tracking",
	"Search"
};
#define NUM_OF_CED_SCAN_TYPE 3
//start_static_0919
enum EnumCEDScanType	//스캔형태	//#FA_Q_2502_T2
{
	E_EL_SC_NO_SELECT = -2, //해당사항없음
	E_EL_SC_ADD_INIT =-1,    //추가시 초기값 추가 
	E_EL_SC_UNKNOWN=0,	    //UnKnown
	E_EL_SC_TRACKING,		// 추적
	E_EL_SC_SEARCH,			// 탐색
	E_EL_SC_SECTOR			// 섹터형 스캔
};
//end_static_0919

static const char* strCEDMOPType [] =
{
	"Unknown",
	"NM",
	"PSK(P)",
	"FSK(F)",
	"LFM(F)",
	"NLFM(F)"
};
#define NUM_OF_CED_MOP_TYPE 6
enum EnumMOPType	//MOP형태
{
	E_EL_MOP_ERROR = -3,	// 잘못된 MOP 값
	E_EL_MOP_NO_SELECT = -2,	//해당사항없음
	E_EL_MOP_ADD_INIT =-1, //추가시 초기값 추가 
	E_EL_MOP_UNKNOWN=0, //UnKnown
	/*! \debug  위협 에미터에서 NM 분석하기 때문에 NM 항목을 CED에 추가
	    \author 조철희 (churlhee.jo@lignex1.com)
	    \date 	2014-12-30 15:45:29
	*/
	E_EL_MOP_NON_MODULATION, // Non-Modulation
	E_EL_MOP_PMOP_PSK,		// PMOP(PSK)
	E_EL_MOP_FMOP_FSK,	//FMOP(FSK)
	E_EL_MOP_FMOP_LFM,	//FMOP(LFM)
	E_EL_MOP_FMOP_NLFM,	//FMOP(NLFM)
};

static const char* strCEDPolType [] =
{
	"V",
	"H",
	"LC",
	"RC",
	"RS",
	"LS"
};
#define NUM_OF_CED_POL_TYPE 5       //20151001 CodeSonar수정  //
enum EnumPolizationType	//극성
{
	E_EL_PZ_NO_SELECT = -2,	//해당사항없음
	E_EL_PZ_ADD_INIT =-1, //추가시 초기값 추가 
	E_EL_PZ_V=0,	//V (Vertical)
	E_EL_PZ_H,		//H	(Horizontal)
	E_EL_PZ_LC,		//LC
	E_EL_PZ_RC,		//RC
	E_EL_PZ_RS,		//RS
	E_EL_PZ_LS,		//LS
	E_EL_PZ_UNKNOWN
};

static const char* strCEDFreqPatternType[] =
{
	"Unknown",
	"사인",
	"SL+",
	"SL-",
	"삼각"
};
#define NUM_OF_CED_FREQ_PATTERN_TYPE 5
enum EnumFreqPatternType	//주파수 패턴타입
{
	E_EL_FPT_NO_SELECT = -2,	//해당사항없음
	E_EL_FPT_ADD_INIT = -1, //미선택
	E_EL_FPT_UNKNOWN=0,
	E_EL_FPT_SIGN,
	E_EL_FPT_SW_PLUS,
	E_EL_FPT_SW_MINUS,
	E_EL_FPT_TRIANGLUAR,
};

static const char* strCEDPRIPatternType[] =
{
	"Unknown",
	"사인",
	"SL+",
	"SL-",
	"삼각"
};
#define NUM_OF_CED_PRI_PATTERN_TYPE 5
enum EnumPRIPatternType	//주파수 패턴타입
{
	E_EL_PPT_NO_SELECT = -2,	//해당사항없음
	E_EL_PPT_ADD_INIT = -1, //미선택
	E_EL_PPT_UNKNOWN=0,
	E_EL_PPT_SIGN,
	E_EL_PPT_SW_PLUS,
	E_EL_PPT_SW_MINUS,
	E_EL_PPT_TRIANGLUAR,
};

struct SCEDSTGElimentData	//스태거 ELIMENT 데이터
{
	UINT nElimentID;	//ELIMENT ID
	float fMinPRI;		//최소스태거PRI
	float fMaxPRI;		//최대스태거PRI
	SCEDSTGElimentData() :
		nElimentID(0),
        fMinPRI(0),
        fMaxPRI(0) {

    }

	void Init(){
		nElimentID=0;
		fMaxPRI=0;
		fMinPRI=0;
	}
};

struct SCEDSTGData	//스태거데이터
{
	UINT						nSTGID;				//스태거ID
	UINT						nSTGNumOfEliments;	//스태거 단수 (**화면표시)
	vector<SCEDSTGElimentData>	vecSTGEliment;		//ELIMENT 데이터

	SCEDSTGData()
        :nSTGID(0)
        ,nSTGNumOfEliments(0)
	{
	}
	void Init(){
		nSTGNumOfEliments=0;
		vecSTGEliment.clear();
	}	
};

///////////////////////////////////////////////////////////////////////////
// 추가됨
struct SCEDHOPElimentData	//호핑 ELIMENT 데이터
{
	UINT nElimentID;	//ELIMENT ID
	float fMinFreq;		//최소호핑주파수
	float fMaxFreq;	//최대호핑주파수
	SCEDHOPElimentData() :
		nElimentID(0),
        fMinFreq(0),
        fMaxFreq(0)
	{}
	void Init(){
		nElimentID=0;
		fMaxFreq=0;
		fMinFreq=0;
	}
};

struct SCEDHOPData	//호핑데이터
{
	UINT						nHOPID;				//호핑 ID
	UINT						nHOPNumOfEliments;	//호핑 단수 (**화면표시)
	vector<SCEDHOPElimentData>	vecHOPEliment;		//ELIMENT 데이터

	SCEDHOPData() :
        nHOPID(0),
        nHOPNumOfEliments(0)
	{
	}
	void Init(){
		nHOPNumOfEliments=0;
		vecHOPEliment.clear();
	}
};

///////////////////////////////////////////////////////////////////////////


enum EnumLoadType {
	E_EL_NO_LOAD=0,

	E_EL_LOAD_CED,
	E_EL_LOADXML_CED,
	E_EL_LOAD_EOB,
	E_EL_LOAD_COMPLETE,

	E_EL_LOAD_ALL
};

// static const char* strLIBType [] =
// {
// 	"기본형",
// 	"실무형",
// };
// #define NUM_OF_LIB_TYPE 2
// 
// #ifndef ENUM_LIB_TYPE
// #define ENUM_LIB_TYPE
// enum EnumLibType	//라이브러리 타입
// {
// 	E_EL_LIB_TYPE_NORMAL=0,		//기본형
// 	E_EL_LIB_TYPE_PRACTICAL		//실무형
// };
// #endif
// 
// #ifndef ENUM_CED_TYPE
// #define ENUM_CED_TYPE
// enum EnumCEDType
// {
// 	E_CED_THREAT=0,
// 	E_CED_EMITTER,
// 	E_CED_BEAM
// };
// #endif

struct SCEDData	//CED 데이터
{
	//라이브러리 종류
	//EnumLibType	eLibType;

	//ID(Header)
	//EnumCEDType eCEDType;	//위협, 에미터, 빔

	UINT	nThreatID;		//위협번호 (* ID)
	UINT	nEmitterID;	//에미터번호 (* ID)
	UINT	nBeamID;		//빔번호 (* ID)

	//위협정보
	CString	strThreatName;	//위협명
	UINT		nTPriority;			//T 우선순위
	bool		bIsEnemy;			//적아구분 (적/아)
	UINT		nNumOfAETForDeterminePulse;	//펄스결정을 위한 AET수
	
	//에미터정보
	CString	strElintNotation;		//ELINT Notation
	CString	strEmitterName;		//에미터명
	int		nMaxThreatRadius;	//최대위협반경
	UINT		nEPriority;				//E 우선순위
	CString	strPlatform;			//플래폼
	CString	strPrimaryFuction;	//PRIMARY Fuction
	CString	strElintNotationNickName;		//EN 별명
	CString	strElintNotationWeaponName;	//EN Weapon명
	float		fXtalOscillatorFreq;	//크리스탈 오실레이터 주파수
	CString	strPinNumber;			//Pin Number
	CString	strEquip;				//장비
	
	//빔정보
	CString					strBeamName;	//빔명
	UINT						nBPriority;			//B 우선순위
	EnumCEDSignalType			eSignalType;		//신호형태
	EnumFreqType			eFreqType;		//주파수형태
	float						fMinRF;			//RF최소
	float						fMaxRF;			//RF최대
	EnumFreqPatternType	eFreqPatternType;		//주파수 패턴형태
	UINT						nRFBandWidth;			//RF변경폭
	float						fMinRFChangePeriod;	//최소RF변경주기
	float						fMaxRFChangePeriod;	//최대RF변경주기

	EnumPRIType			ePRIType;					//PRI형태
	float						fMinPRI;					//최소PRI
	float						fMaxPRI;					//최대PRI
	float						fJitterRate;					//PRI지터율
	EnumPRIPatternType		ePRIPatternType;			//PRI 패턴형태
	UINT						nMinPRIPatternPeriod;	//최소 PRI 패턴주기
	UINT						nMaxPRIPatternPeriod;	//최대 PRI 패턴주기

	float						fMinPW;					//최소PW
	float						fMaxPW;					//최대PW
	EnumMOPType			eMOPType;				//MOP형식
	EnumCEDScanType			eScanType;				//스캔형태
	UINT						nMaxScanPeriod;			//최대스캔주기
	UINT						nMinScanPeriod;			//최소스캔주기

	EnumPolizationType		ePolization;		//극성
	float						fBeamWidth;		//빔폭	

	SCEDSTGData			stSTGData;		//스태거 데이터 (PRI타입이 스태거, D&S 일 경우에만 유효함 (ePRIType==E_EL_PRI_STAGGER || ePRIType==E_EL_PRI_DwellAndSwitch))
	SCEDHOPData			stHOPData;		//호핑 데이터 (주파수형태가 호핑일 경우에만 유효함 (eFreqType==E_EL_FREQ_HOPPING))

	bool				bIsBeacon;	//Beacon여부 (추가됨*)
	UINT				nPulsePerGroup;	//Group당 펄스 수 (추가됨*)
	UINT				nPRIPerGroup;	//Group당 PRI (ns) (추가됨*)
	UINT				nPRIInGroup;	//Group내 PRI (ns) (추가됨*)
	vector<float>		vecPWInGroup;	//Group내 PW
	vector<float>		vecPAInGroup;	//Group내 PA
	vector<float>		vecFreqInGroup;	//Group내 Freq

	SCEDData(){
		Init();
	}
	void Init(){
		//eLibType=E_EL_LIB_TYPE_NORMAL;
		//eCEDType=E_CED_BEAM;
        strThreatName = "";
		nTPriority=0;
		nThreatID=0;
		bIsEnemy=true;
		nNumOfAETForDeterminePulse=0;

        strEmitterName = "";
		nMaxThreatRadius=0;
		nEPriority=0;	
		nEmitterID=0;
		nBPriority=0;
        strPlatform = "";
        strElintNotation = "";
        strPrimaryFuction = "";
        strPinNumber ="";
        strEquip="";
        strElintNotationNickName="";
        strElintNotationWeaponName="";
		fXtalOscillatorFreq=0;

        strBeamName="";
		eSignalType=E_EL_SIG_NO_SELECT;
		ePRIType=E_EL_PRI_NO_SELECT;
		eFreqType=E_EL_FREQ_NO_SELECT;
		eScanType=E_EL_SC_NO_SELECT;
		fJitterRate=0;	
		nRFBandWidth=0;		
		eMOPType=E_EL_MOP_NO_SELECT;			
		nMaxScanPeriod=0;		
		nMinScanPeriod=0;	
		fMaxRF=0;			
		fMinRF=0;			
		fMaxRFChangePeriod=0;	
		fMinRFChangePeriod=0;	
		fMinPRI=0;		
		fMaxPRI=0;		
		fMinPW=0;			
		fMaxPW=0;			
		ePolization=E_EL_PZ_NO_SELECT;	
		fBeamWidth=0;
		nBeamID=0;

		stSTGData.Init();
		stHOPData.Init();	

		eFreqPatternType = E_EL_FPT_NO_SELECT;
		ePRIPatternType = E_EL_PPT_NO_SELECT;
		nMaxPRIPatternPeriod=0;
		nMinPRIPatternPeriod=0;	

		bIsBeacon=false;
		nPulsePerGroup=0;
		nPRIPerGroup=0;
		nPRIInGroup=0;
	}
};
// struct SEditCompleteResult
// {
// 	bool bSuccess;	//성공여부
// 	EnumCEDType eCEDType;	//종류(빔, 에미터, 빔)
// 	UINT nThreatID; //종류가 위협일 경우
// 	UINT nEmitterID;	//종류가 에미터일 경우
// 	UINT nBeamID;	//종류가 빔일 경우
// 	CString strErrorMsg;	//에러메시지 (실패일 경우만)
// 	SEditCompleteResult():
// 		bSuccess(true),
// 		eCEDType(E_CED_BEAM),
// 		nThreatID(0),
// 		nEmitterID(0),
// 		nBeamID(0),
// 		strErrorMsg("")
// 	{}
// };
struct SCEDImportErrorMsg
{
	//EnumLibType eLibType;
	UINT nNo;	//데이터 번호
	CString strErrorItem;	//오류항목
	CString strThreatID; //위협번호
	CString strEmitterID;	//에미터번호
	CString strBeamID;	//빔번호
	CString strErrorMsg;	//오류
	SCEDImportErrorMsg():
		//eLibType(E_EL_LIB_TYPE_NORMAL),
		nNo(1),
		strThreatID(""),
		strEmitterID(""),
		strBeamID(""),
		strErrorMsg("")
	{}
};
struct SCED_ID
{
	UINT nThreatID;
	UINT nEmitterID;
	UINT nBeamID;
	SCED_ID():
		nThreatID(0),
		nEmitterID(0),
		nBeamID(0)
	{}
};
////////////////////////////////////////////////////////////////////////////


struct SCEDThreatData	//위협정보
{
	//EnumLibType eLibType;	//라이브러리 타입
	UINT	nThreatID;		//위협번호 (* ID)

	CString strThreatName;	//위협명
	UINT	nTPriority;		//T 우선순위
	bool	bIsEnemy;			//적아구분	
	UINT	nNumOfAETForDeterminePulse;	//펄스결정을 위한 AET수
	
	SCEDThreatData():
		nThreatID(0),
		strThreatName(""),
		nTPriority(1),
		bIsEnemy(true),
		//eLibType(E_EL_LIB_TYPE_NORMAL),
		nNumOfAETForDeterminePulse(0)
	{}
};

struct SCEDEmitterData	//에미터정보
{
	//EnumLibType eLibType;		//라이브러리 타입
	UINT	nThreatID;			//위협번호 (* ID)
	int	nEmitterID;			//에미터번호 (* ID)

	CString strElintNotation;	//ELINT Notation
	CString strEmitterName;		//에미터명
	UINT	nMaxThreatRadius;	//최대위협반경
	int	nEPriority;			//E 우선순위
	CString strPlatform;		//플랫폼, Flatform 을 Platform 으로 변경, 조철희
	CString strPrimaryFuction;	//PRIMARY Fuction	
	CString strElintNotationNickName;	//EN 별명
	CString strElintNotationWeaponName;	//EN Weapon명
	float	fXtalOscillatorFreq;		//크리스탈 오실레이터 주파수
	CString strPinNumber;		//Pin Number
	CString strEquip;				//장비	
	
	SCEDEmitterData():
		nThreatID(0),
		nEmitterID(0),
        strElintNotation(""),
		strEmitterName(""),
		nMaxThreatRadius(0),
		nEPriority(1),
		strPlatform(""),		
		strPrimaryFuction(""),
        strElintNotationNickName(""),
        strElintNotationWeaponName(""),
        fXtalOscillatorFreq(0),
		//eLibType(E_EL_LIB_TYPE_NORMAL),
		strPinNumber(""),
        strEquip("")
	{}
};

struct SCEDBeamData	//빔정보
{
	//EnumLibType			eLibType;		//라이브러리 타입
    UINT nThreatID;		//위협번호 (* ID)
    UINT nEmitterID;		//에미터번호 (* ID)
    UINT nBeamID;		//빔번호 (* ID)
    CString strBeamName;	//빔명
    UINT nBPriority;		//B 우선순위
    EnumCEDSignalType eSignalType;	//신호형태
    EnumFreqType eFreqType;		//주파수형태
    float fMinRF;			//RF최소
    float fMaxRF;			//RF최대
	EnumFreqPatternType	eFreqPatternType;	//주파수 패턴형태
    UINT nRFBandWidth;	//RF변경폭
    float fMinRFChangePeriod;	//최소RF변경주기
    float fMaxRFChangePeriod;	//최대RF변경주기

    EnumPRIType	ePRIType;		//PRI형태
    float fMinPRI;		//최소PRI
    float fMaxPRI;		//최대PRI
    float fJitterRate;	//PRI지터율
    EnumPRIPatternType ePRIPatternType;	//PRI 패턴형태
    UINT nMinPRIPatternPeriod;	//최소 PRI 패턴주기
    UINT nMaxPRIPatternPeriod;	//최대 PRI 패턴주기
    float fMinPW;			//최소PW
    float fMaxPW;			//최대PW

    EnumMOPType	eMOPType;		//MOP형식
    EnumCEDScanType eScanType;		//스캔형태
    UINT nMinScanPeriod;	//최소스캔주기
    UINT nMaxScanPeriod;	//최대스캔주기
    EnumPolizationType ePolization;	//극성
    float fBeamWidth;		//빔폭
	
    UINT nNumOfHOP;			//호핑 단수
    UINT nNumOfSTG;			//스태거 및 D&S 단수
	vector<SCEDHOPElimentData>	vecHOPEliment;	//호핑엘리먼트
	vector<SCEDSTGElimentData>	vecSTGEliment;	//스태거엘리먼트

    bool bIsBeacon;	//Beacon여부 (추가됨*)
    UINT nPulsePerGroup;	//Group당 펄스 수 (추가됨*)
    UINT nPRIPerGroup;	//Group당 PRI (ns) (추가됨*)
    UINT nPRIInGroup;	//Group내 PRI (ns) (추가됨*)
    vector<float> vecPWInGroup;	//Group내 PW (추가됨)
    vector<float> vecPAInGroup;	//Group내 PA (추가됨)
    vector<float> vecFreqInGroup;	//Group내 주파수 (추가됨)

	SCEDBeamData():
		nThreatID(0),
		nEmitterID(0),
		nBeamID(0),
		strBeamName(""),
		nBPriority(0),
		eSignalType(E_EL_SIG_NORMAL_PULSE),
		eFreqType(E_EL_FREQ_FIXED),
        fMinRF(0),
        fMaxRF(0),
        eFreqPatternType(E_EL_FPT_UNKNOWN),	//주파수 패턴형태
        nRFBandWidth(0),
        fMinRFChangePeriod(0),
        fMaxRFChangePeriod(0),
		ePRIType(E_EL_PRI_STABLE),
        fMinPRI(0),
        fMaxPRI(0),
        fJitterRate(0),
        ePRIPatternType(E_EL_PPT_UNKNOWN),	//PRI 패턴형태
        nMinPRIPatternPeriod(0),		//최소 PRI 패턴주기
        nMaxPRIPatternPeriod(0),	//최대 PRI 패턴주기
        fMinPW(0),
        fMaxPW(0),
        eMOPType(E_EL_MOP_UNKNOWN),
		eScanType(E_EL_SC_UNKNOWN),
        nMinScanPeriod(0),
		nMaxScanPeriod(0),
		ePolization(E_EL_PZ_V),
		fBeamWidth(0),

		//eLibType(E_EL_LIB_TYPE_NORMAL),
        nNumOfHOP(0),
        nNumOfSTG(0),

		bIsBeacon(false),	//Group여부 (추가됨*)
		nPulsePerGroup(0),	//Group당 펄스 수 (추가됨*)
		nPRIPerGroup(0),	//Group당 PRI (ns) (추가됨*)
		nPRIInGroup(0)	//Group내 PRI (ns) (추가됨*)
	{}
};

struct SCEDEmitterTreeData : public SCEDEmitterData
{
	map<UINT, SCEDBeamData> mapBeam;
	SCEDEmitterTreeData()
	{
		Init();
	}
	void Init(){
		mapBeam.clear();
	}
	void operator=(const SCEDEmitterData &i_stSrc){
		SCEDEmitterData::operator=(i_stSrc);
	}
};


struct SCEDThreatTreeData : public SCEDThreatData
{
	map<UINT, SCEDEmitterTreeData> mapEmitter;
	SCEDThreatTreeData()
	{
		Init();
	}
	void Init(){
		mapEmitter.clear();
	}
	void operator=(const SCEDThreatData &i_stSrc){
		SCEDThreatData::operator=(i_stSrc);
	}
};
struct SCEDCreateTask
{
	int TaskType;
	float fMinRF;
	float fMaxRF;

};

#endif
