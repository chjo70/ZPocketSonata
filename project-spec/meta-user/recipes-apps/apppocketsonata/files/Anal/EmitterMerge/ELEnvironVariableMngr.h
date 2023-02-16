#pragma once

#include "../SigAnal/_Type.h"

//#include "..\..\CEFCOMMON\CommonMngr.h"

// namespace SELTASKDB
// {
// 	struct SELDBEnvVar;
// 	struct SELDBEnvVarRpt;
// 	struct SELDBEnvVarIdnf;
// }

#define _DEFAULT_PPG_TYPE_RATE				(10)			// GUI 에 반영할 것
#define _DEFAULT_SIGNAL_TYPE_RATE			(10)
#define _DEFAULT_FREQ_TYPE_RATE				(10)
#define _DEFAULT_PRI_TYPE_RATE				(10)
#define _DEFAULT_PW_RANGE_RATE				(10)
#define _DEFAULT_SCAN_TYPE_RATE				(10)

class CELEnvironVariableImpl;
struct SOCSystemVariable;
struct SELEnvVarSet;

struct SEnvironVariable {
	float fEobIndfRangeMeters;

	UINT uiEmmgNumOfMinLobToBeam;
	UINT uiEmmgEmitterDeleteTimeSec;

	int iDVRatio;

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

	// 식별율
	int iMatchRatio;

} ;

/**
 * [식별자 : CLS-GMU-EL-L-EVM]
 *
 * [추적성 : SRS-G-SCFR-008]
 *
 * @class    CELEnvironVariableMngr
 * @brief  환경변수를 DB에 저장/삭제/변경 관리 할 수 있는 관리 클래스
 *
 * (1) 클래스 설명
 * -   환경변수를 DB에 저장/삭제/변경 관리 할 수 있는 관리 클래스
 *
 * (2) 설계결정사항
 * - 수동과제 운용, 보고서 생성, 전자지도 전시 등에 필요한 환경변수를 DB에 저장/ 관리할 수 있는 기능 필요.
 *
 * (3) 제한 및 예외처리
 * - 해당사항없음
 */
class CELEnvironVariable
{
private:
	SEnvironVariable m_stEnvironVariable;
	
public:
    CELEnvironVariable(void);
    virtual ~CELEnvironVariable(void);	
	
	
public:
	SEnvironVariable *GetEnvrionVariable();

	void SetEnvironVaraiable( SEnvironVariable *pSEnvironVariable );


// /**
// 	* @brief       환경변수 로딩 함수
// 	* @param       SELEnvVarSet & i_stData   환경변수 구조체
// 	* @return      bool   성공 시 true, 실패 시 false
// 	*/
// 	bool LoadEnvVars(SELEnvVarSet& i_stData);
// 	
// 	/**
// 	* @brief       환경변수 재로딩 함수
// 	* @param       bool i_bIsServer   서버 여부
// 	* @return      bool   성공 시 true, 실패 시 false
// 	*/
// 	bool ReloadEnvVars(bool i_bIsServer = false);
// 	
// 	/**
// 	* @brief       환경변수를 DB에 저장하기 위한 함수
// 	* @param       SELEnvVarSet & i_stData   환경변수 구조체
// 	* @return      bool   성공 시 true, 실패 시 false
// 	*/
// 	bool InsertEnvVarsToDB(SELEnvVarSet& i_stData); //SELTASKDB::SELDBEnvVar& i_stData, std::vector<SELTASKDB::SELDBEnvVarRpt>& i_vecRpt);	
// 	
// 	/**
// 	* @brief       TacRep 우선순위 문자열정보 획득함수
// 	* @param       std::vector<std::string> & i_vecData 문자열 벡터   
// 	* @return      bool   성공 시 true, 실패 시 false
// 	*/
// 	bool GetTacRepPriorityStrings(std::vector<std::string>& i_vecData);
// 	
// 	/**
// 	* @brief       TacRep 국적 문자열정보 획득함수
// 	* @param       std::vector<std::string> & i_vecData   국적 문자열 벡터
// 	* @return      bool   성공 시 true, 실패 시 false
// 	*/
// 	bool GetTacRepNationalityStrings(std::vector<std::string>& i_vecData);
// 	
// 	/**
// 	* @brief       TacElint 국적 문자열정보 획득함수
// 	* @param       std::vector<std::string> & i_vecData  국적 문자열 벡터 
// 	* @return      bool   성공 시 true, 실패 시 false
// 	*/
// 	bool GetTacElintNationalityStrings(std::vector<std::string>& i_vecData);
// 	
// 	/**
// 	* @brief       UniformC 국적 문자열정보 획득점수
// 	* @param       std::vector<std::string> & i_vecData  국적 문자열 벡터  
// 	* @return      bool   성공 시 true, 실패 시 false
// 	*/
// 	bool GetUniformCNationalityStrings(std::vector<std::string>& i_vecData);
// 	
// 	/**
// 	* @brief       UniformC 신호종류 문자열정보 획득함수
// 	* @param       std::vector<std::string> & i_vecData  신호종류 문자열 벡터  
// 	* @return      bool   성공 시 true, 실패 시 false
// 	*/
// 	bool GetUniformCSigKindStrings(std::vector<std::string>& i_vecData);
// 	
// 	/**
// 	* @brief       EOB 라이브러리 타입 획득함수
// 	* @return      EnumLibType   라이브러리 타입
// 	*/
// 	EnumLibType GetEOBLibType();
// 	
// 	/**
// 	* @brief       CED 라이브러리 타입 획득함수
// 	* @return      EnumLibType   라이브러리 타입
// 	*/
// 	EnumLibType GetCEDLibType();
// 
// public:	
// 	//SELTASKDB::SELDBEnvVar* GetEnvVars();	//LJN_DEL
// 	
// 	/**
// 	* @brief       신호식별 관련 환경변수 정보 획득함수
// 	* @return      SELTASKDB::SELDBEnvVarIdnf*   신호식별 구조체 포인터
// 	*/
// 	SELTASKDB::SELDBEnvVarIdnf* GetIdnfEnvVars();
// 
// 	
// 	/**
// 	* @brief       CW 초핑간격 환경변수 값 획득함수
// 	* @return      unsigned int   CW 초핑간격 값
// 	*/
// 	unsigned int GetVarCwChopInterval();
// 	
// 	/**
// 	* @brief       CW 판정펄스폭 환경변수 값 획득함수
// 	* @return      unsigned int   CW 판정펄스폭
// 	*/
// 	unsigned int GetVarCwDescisionPw();
// 	
// 	/**
// 	* @brief       CW 초핑카운트 값 획득함수
// 	* @return      unsigned int   CW 초핑카운트 값
// 	*/
// 	unsigned int GetVarCwChopCount();
// 	//unsigned int GetVarNRTThreshold();//LJN_DEL
// 	
// 	
// 	/**
// 	* @brief       광대역스펙트럼 단위수집시간 환경변수 값 획득함수
// 	* @return      unsigned int  단위수집시간 
// 	*/
// 	unsigned int GetMtskWbSpUnitCollTime();
// 	
// 	/**
// 	* @brief       광대역스펙트럼 단위수집개수 환경변수 값 획득함수
// 	* @return      unsigned int   단위수집개수
// 	*/
// 	unsigned int GetMtskWbSpUnitCollNum();
// 	
// 	/**
// 	* @brief       회전방탐 단위수집시간 환경변수 값 획득함수
// 	* @return      unsigned int   단위수집시간
// 	*/
// 	unsigned int GetMtskSpinDFUnitCollTime();
// 	
// 	/**
// 	* @brief       회전방탐 단위수집개수 환경변수 값 획득함수
// 	* @return      unsigned int   단위수집개수
// 	*/
// 	unsigned int GetMtskSpinDFUnitCollNum();
// 	
	/**
	* @brief       DV 비율 환경변수 값 획득함수
	* @return      unsigned int   DV비율
	*/
 	int GetMtskDVRatio();
// 	
// 	
// 	/**
// 	* @brief       LOB생성을 위한 최소 펄스 수 환경변수 값 획득함수
// 	* @return      unsigned int   최소펄스 수
// 	*/
// 	unsigned int GetEmmgNumOfMinPulseToLOB();
	
	/**
	* @brief       빔 형성을 위한 최소 LOB 개수 환경변수 값 획득함수
	* @return      unsigned int   LOB 개수
	*/
 	unsigned int GetEmmgNumOfMinLobToBeam();
	unsigned int GetEmmgEmitterDeleteTimeSec();

	float GetEobIndfRangeMeters();


};

//#define GP_ENVI_VAR CELEnvironVariable::getInstance()

