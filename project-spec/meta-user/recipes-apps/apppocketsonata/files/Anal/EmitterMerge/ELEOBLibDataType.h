
#pragma once

#include <vector>
using namespace std;

#ifndef ENUM_LIB_TYPE
#define ENUM_LIB_TYPE
enum EnumLibType	//라이브러리 타입
{
	E_EL_LIB_TYPE_NORMAL=0,	//기본형
	E_EL_LIB_TYPE_PRACTICAL	//실무형
};
#endif

enum EnumEOBDirection
{
	E_EL_EOB_DIRECTION_ADDINIT =-1, //EOB 추가시 초기값
	E_EL_EOB_DIRECTION_EAST=0,	//동
	E_EL_EOB_DIRECTION_WEST,	//서
	E_EL_EOB_DIRECTION_SOUTH,	//남
	E_EL_EOB_DIRECTION_NORTH	//북
};

struct SEOBLibData	//EOB 데이터
{
	UINT		nEOBNo;		//순번 (*ID)
	EnumLibType eLibType;	//라이브러리종류: 일반형/실무형
	CString strBaseName;
	CString strLatitude;
	CString strLongitude;

	//추가됨*
	EnumEOBDirection eDirection;	//방향 (*추가됨)
	UINT	nEmitterID;				//에미터ID (*추가됨)
	CString strPinNumber;			//Pin Number (*추가됨)

	SEOBLibData():
		eLibType(E_EL_LIB_TYPE_NORMAL),
		nEOBNo(0),
		strBaseName(""),
		strLatitude(""),
		strLongitude(""),
		eDirection(E_EL_EOB_DIRECTION_EAST),
		nEmitterID(0),
		strPinNumber("")
	{
	}
};
static const SEOBLibData g_stInitEOBLibData;

#define NUM_OF_EOBLIB_FIELD_NAME 7    
static const char* pchEOBFieldName[] =
{
	"순번",
	//"라이브러리",
	"기지명",
	"위도[degree]",
	"경도[degree]",
	"방향",
	"에미터ID",
	"Pin Number",
};

struct SEOBNewLibData	//EOB 데이터 (신규)
{
	UINT		nNumber;				//순번 (*ID)
	UINT		nEOBID;				//EOB ID
	UINT		nPinNumber;			//Pin Number (최대 5자 내의 숫자임)
	CString	strBaseName;			//지명 (한글 입력가능)
	CString	strFunctionCode;		//구분
	CString	strFacilityName;		//시설이름
	char		chSiteStatus;			//Site 상태 (영문 1자임)
	CString	strLongitude;			//경도 (8자 - 도: 3자 숫자, 분: 2자 숫자, 초: 2자 숫자, N 혹은 S)
	CString	strLatitude;			//위도 (7자 - 도: 2자 숫자, 분: 2자 숫자, 초: 2자 숫자, W혹은 E)
	float		fElivation;				//고도 (숫자, 음수 입력가능, 소수점 1자리까지 가능)
	CString	strADA;				//방공구역 (5자 - 영문 2자, 숫자3자)
	CString	strBENumber;			//BE Number (영문 2자)
	CString	strCategory;			//카테고리 (숫자 5자)
	CString	strPrimaryFunction;	//Primary Function (영문 2자)
	CString	strDTC;				//최초반영시간 (년(4자)-월(2자)-시(2자))
	CString	strDTLI;				//DTLI (년(4자)-월(2자)-시(2자))
	UINT		nEquipNo;				//장비번호 (숫자 1자리)
	CString	strNomenclature;		//명명법
	vector<CString>	vecElintNotation;		//ELINT Notation
	char		chEquipStatus;		//장비상태 (영문 1자)
	CString	strDTFI;				//DTFI (년(4자)-월(2자)-시(2자))

	EnumLibType eLibType;	//라이브러리종류: 일반형/실무형

	SEOBNewLibData():
		eLibType(E_EL_LIB_TYPE_NORMAL),
		nNumber(0),
		nEOBID(0),
		nPinNumber(0),
		strBaseName(""),
		strFunctionCode(""),
		strFacilityName(""),
		chSiteStatus(' '),
		strLongitude(""),
		strLatitude(""),
		fElivation(0.0),
		strADA(""),
		strBENumber(""),
		strCategory(""),
		strPrimaryFunction(""),
		strDTC(""),
		strDTLI(""),
		nEquipNo(0),
		strNomenclature(""),
		chEquipStatus(' '),
		strDTFI("")
	{}
	double SEOBNewLibData::GetLongitude(){
		double dRet;
		if (strLongitude.GetLength()!=8)
			dRet = 0;
		else
		{
			double dbLongitude = _ttof(strLongitude.Left(3))+_ttof(strLongitude.Mid(3,2))*1.0/60.0+_ttof(strLongitude.Mid(5,2))*1.0/60.0/60.0;
			dRet = dbLongitude;
		}
		return dRet;
	}
	double SEOBNewLibData::GetLatitude(){
		double dRet;
		if (strLatitude.GetLength()!=7) {
			dRet = 0;
		}
		else
		{
			double dbLatitude = _ttof(strLatitude.Left(2))+_ttof(strLatitude.Mid(2,2))*1.0/60.0+_ttof(strLatitude.Mid(4,2))*1.0/60.0/60.0;
			dRet = dbLatitude;
		}
		return dRet;
	}
};
static const SEOBNewLibData g_stInitEOBNewLibData;

#define NUM_OF_NEW_EOBLIB_FIELD_NAME 21
static const char* pchNewEOBFieldName[] =
{
	"순번",
	"EOB ID",
	"Pin Number",
	"지명",
	"구분",
	"시설이름",
	"Site 상태"
	"경도[degree]",
	"위도[degree]",
	"고도[m]",
	"방공구역",
	"BE Number",
	"카테고리",
	"Primary Function",
	"최초반영시간",
	"DTLI",
	"장비번호",
	"명명법",
	"Elint Notation",
	"장비상태",
	"DTFI"
};

struct SEOBEditCompleteResult
{
	bool bSuccess;	//성공여부
	UINT nEOBID; //EOB ID
	CString strErrorMsg;	//에러메시지 (실패일 경우만)
	SEOBEditCompleteResult():
		bSuccess(true),
		nEOBID(0),
		strErrorMsg("")
	{}
};

struct SEOBImportErrorMsg
{
	UINT nNo;	//데이터 번호
	CString strErrorItem;	//오류항목
	CString strEOBID;	//EOB ID
	CString strErrorMsg;	//오류
	SEOBImportErrorMsg():
		nNo(1),
		strErrorMsg("")
	{}
};

//////////////////////////////////////////////////////////////////////
struct SEOBInternalData	//EOB 내부 데이터
{
	UINT		nEOBNo;		//순번 (*ID)
	EnumLibType eLibType;	//라이브러리종류: 일반형/실무형
	CString strBaseName;
	double dbLatitude;
	double dbLongitude;

	//추가됨*
	EnumEOBDirection eDirection;	//방향 (*추가됨)
	UINT	nEmitterID;				//에미터ID (*추가됨)
	CString strPinNumber;			//Pin Number (*추가됨)

	SEOBInternalData():
	eLibType(E_EL_LIB_TYPE_NORMAL),
		nEOBNo(0),
		strBaseName(""),
		dbLatitude(0),
		dbLongitude(0),
		eDirection(E_EL_EOB_DIRECTION_EAST),
		nEmitterID(0),
		strPinNumber("")
	{
	}
	void Init()
	{
		eLibType = E_EL_LIB_TYPE_NORMAL;
			nEOBNo = 0;
			strBaseName.Empty();
			dbLatitude = 0;
			dbLongitude = 0;
			eDirection = E_EL_EOB_DIRECTION_EAST;
			nEmitterID = 0;
			strPinNumber.Empty();
	}
};
//static const SEOBInternalData g_stInitEOBInternalData;
/////////////////////////////////////////////////////////////////////
