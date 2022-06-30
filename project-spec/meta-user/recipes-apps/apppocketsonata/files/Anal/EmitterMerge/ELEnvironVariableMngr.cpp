#include "stdafx.h"

#ifdef __VXWORKS__
#else
#include <memory.h>
#endif

#include "ELEnvironVariableMngr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#define CRTDBG_MAP_ALLOC
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//////////////////////////////////////////////////////////////////////////
/*!
* @brief     생성자
* @param     void
* @return    void
* @version   0.0.1
* @exception
* @author    이정남 (jeongnam.lee@lignex1.com)
* @date      2016-01-29 오후 5:30 
* @warning   
*/
CELEnvironVariable::CELEnvironVariable(void)
{
	bool bRtn = false;    

	// 기본 설정 값
	m_stEnvironVariable.iDVRatio = 60;							// [%]

	// 신호 식별 설정값
	m_stEnvironVariable.fMarginFrqError = 3.0;				// [MHz]	
	m_stEnvironVariable.fMarginFrqModPeriodErrorRatio = 50;

    m_stEnvironVariable.fMarginPriError = 2.0;			// [us]
	m_stEnvironVariable.fMarginMinRqdPriRangeNestedRatio = 10;		// 지터-스태거 비교시 PRI 마진 값
	m_stEnvironVariable.fMarginPriModPeriodErrorRatio = 30;

    m_stEnvironVariable.fMarginPwError = 100.0;
    m_stEnvironVariable.fMarginErrorRatioCompareToPw = 100.0;

    m_stEnvironVariable.fMarginPaErrorInPulseGroup = 10.0;
    m_stEnvironVariable.fMarginScanPeriodErrorRatio = 10.0;

    m_stEnvironVariable.uiEmmgEmitterDeleteTimeSec = 60;
	m_stEnvironVariable.uiEmmgNumOfMinLobToBeam = 3;
	m_stEnvironVariable.fEobIndfRangeMeters = 10000.0;

	m_stEnvironVariable.iWeightFrqRange = 10;			// 신호식별가중치-주파수범위
	m_stEnvironVariable.iWeightFrqExpRange = 10;   // 신호식별가중치-주파수확장범위
	m_stEnvironVariable.iWeightFrqModPeriod = 10; // 신호식별가중치- 주파수변조주기
	m_stEnvironVariable.iWeightFrqModPosCnt = 10; //신호식별가중치- 주파수변조 포지션수
	m_stEnvironVariable.iWeightFrqModElement = 10; // 신호식별가중치- 주파수변조 엘리먼트
	m_stEnvironVariable.iWeightFrqMainObservedValue = 10; // 신호식별가중치 - 주파수 주 관측값
	m_stEnvironVariable.iWeightPriRange = 10; // 신호식별가중치 - PRI 범위
	m_stEnvironVariable.iWeightPriExpRange = 10; // 신호식별가중치 - PRI 확장 범위
	m_stEnvironVariable.iWeightPriModPeriod = 10; // 신호식별가중치 - PRI 변조 주기
	m_stEnvironVariable.iWeightPriModPosCount = 10; // 신호식별가중치 - PRI 변조 포지션 수
	m_stEnvironVariable.iWeightPriModElement = 10; // 신호식별가중치- PRI 변조 엘리먼트
	m_stEnvironVariable.iWeightPriDifferenceInGroup = 10; // 신호식별가중치 - 그룹내 PRI 차
	m_stEnvironVariable.iWeightPriMainObservedValue = 10; // 신호식별가중치 - PRI 주 관측값
	m_stEnvironVariable.iWeightPaDiffrenceInGroup = 10; // 신호식별가중치 - 그룹 내 PA 차

	m_stEnvironVariable.iMatchRatio = 50;


}

/**
 * @brief     GetEnvrionVariable
 * @return    SEnvironVariable *
 * @exception
 * @author    조철희 (churlhee.jo@lignex1.com)
 * @version   0.0.1
 * @date      2022-01-07, 20:39
 * @warning
 */
SEnvironVariable *CELEnvironVariable::GetEnvrionVariable()
{ 
    return & m_stEnvironVariable; 
}

//////////////////////////////////////////////////////////////////////////
/*!
* @brief     소멸자
* @param     void
* @return    void
* @version   0.0.1
* @exception
* @author    이정남 (jeongnam.lee@lignex1.com)
* @date      2016-01-29 오후 5:30 
* @warning   
*/
CELEnvironVariable::~CELEnvironVariable(void)
{	
	//M_DELETE(m_pImpl)
	//GP_MGR_LOG.ELSetCommonSysLog( E_TYPE_SYSTEM, E_WARNING_NONE, enumAIE_DEVICE, enumELINT_DEVICE, "[매니저 종료] CELEnvironVariable");
}

// CELEnvironVariable::Cleanup::~Cleanup(void)
// {
// 	ReleaseInstance();
// }

//////////////////////////////////////////////////////////////////////////
/*!
* @brief     싱글턴 객체를 반환하는 함수
* @param     void
* @return    CELEnvironVariable *
* @version   0.0.1
* @exception
* @author    이정남 (jeongnam.lee@lignex1.com)
* @date      2016-01-29 오후 5:32 
* @warning   
*/
// CELEnvironVariable* CELEnvironVariable::getInstance()
// {
// 	if(m_pInstance == nullptr)
// 	{	 //EX_DTEC_NullPointCheck
// 		m_pInstance = new CELEnvironVariable;
// 		//static Cleanup cleanup;
// 	}
// 	return m_pInstance;
// }
// 
// /**
// * @brief     IsReadyInstance
// * @param     void
// * @return    bool
// * @exception 
// * @author    조철희 (churlhee.jo@lignex1.com)
// * @version   0.0.1
// * @date      2016-07-26, 오후 12:01 
// * @warning   
// */
// bool CELEnvironVariable::IsReadyInstance()
// {
// 	bool bRtn = false;
// 	if(m_pInstance != nullptr)
// 	{
// 		bRtn = true;
// 	}
// 	return bRtn;
// }
// 
// //////////////////////////////////////////////////////////////////////////
// /*!
// * @brief     싱글턴 객체를 외부에서 파괴하기 위한 함수
// * @param     void
// * @return    void
// * @version   0.0.1
// * @exception
// * @author    이정남 (jeongnam.lee@lignex1.com)
// * @date      2016-01-29 오후 5:32 
// * @warning   
// */
// void CELEnvironVariable::ReleaseInstance()
// {
// 
// 	if( m_pInstance != NULL ) {
//  		delete m_pInstance;
// 		m_pInstance = NULL;
// 	}
// }

void CELEnvironVariable::SetEnvironVaraiable( SEnvironVariable *pSEnvironVariable )
{
	memcpy( & m_stEnvironVariable, pSEnvironVariable, sizeof(SEnvironVariable) );

}
 
// bool CELEnvironVariable::LoadEnvVars(SELEnvVarSet& i_stData)
// {
// 	return (m_pImpl->LoadEnvVars(i_stData) );
// }
// 
// bool CELEnvironVariable::ReloadEnvVars(bool i_bIsServer)
// {
// 	bool bRtn = true;
// 	if(i_bIsServer==true) // 연동기는 화면이 없기때문에 notifyObserver 계열의 명령이 먹지 않는다.
// 	{
// 		// 원래는 화면단에서 인풋 인자를 넣어서 호출해 주는 함수임. 화면도 내용을 담아가고, 함수 호출 시 logic도 메모리가 갱신되는 구조. 여기에서는 interface 상 더미로 넣어줘야 함.
// 		SELEnvVarSet stDummySet; 
// 		LoadEnvVars(stDummySet);
// 	}
// 	else
// 	{
// 		this->notifyObservers(nullptr, nullptr, E_EL_LV_UPDATE_ENV_VAR, NULL);	
// 	}
// 	return bRtn;
// } 
// 
// bool CELEnvironVariable::InsertEnvVarsToDB(SELEnvVarSet& i_stData)
// {
// 	return (m_pImpl->InsertEnvVarDataToDB(i_stData) );
// }
// 
// bool CELEnvironVariable::GetTacRepPriorityStrings(std::vector<std::string>& i_vecData)
// {
// 	return (m_pImpl->GetTacRepPriorityStrings(i_vecData) );
// }
// 
// bool CELEnvironVariable::GetTacRepNationalityStrings(std::vector<std::string>& i_vecData)
// {
// 	return (m_pImpl->GetTacRepNationalityStrings(i_vecData) );
// }
// 
// bool CELEnvironVariable::GetTacElintNationalityStrings(std::vector<std::string>& i_vecData)
// {
// 	return (m_pImpl->GetTacElintNationalityStrings(i_vecData) );
// }
// 
// bool CELEnvironVariable::GetUniformCNationalityStrings(std::vector<std::string>& i_vecData)
// {
// 	return (m_pImpl->GetUniformCNationalityStrings(i_vecData) );
// }
// 
// bool CELEnvironVariable::GetUniformCSigKindStrings(std::vector<std::string>& i_vecData)
// {
// 	return (m_pImpl->GetUniformCSigKindStrings(i_vecData) );
// }
// 
// // 외부 Interface 함수
// 
// //SELTASKDB::SELDBEnvVar* CELEnvironVariable::GetEnvVars()
// //{
// //	return (m_pImpl->GetEnvVars() );
// //}
// 
// SELTASKDB::SELDBEnvVarIdnf* CELEnvironVariable::GetIdnfEnvVars()
// {
// 	return (m_pImpl->GetIdnfEnvVars() );
// }
// 
// unsigned int CELEnvironVariable::GetVarCwChopInterval()
// {
// 	return (m_pImpl->GetVarCwChopInterval() );
// }
// 
// unsigned int CELEnvironVariable::GetVarCwDescisionPw()
// {
// 	return (m_pImpl->GetVarCwDescisionPw() );
// }
// 
// unsigned int CELEnvironVariable::GetVarCwChopCount()
// {
// 	return (m_pImpl->GetVarCwChopCount() );
// }
// 
// //unsigned int CELEnvironVariable::GetVarNRTThreshold()//LJN_DEL
// //{
// //	return (m_pImpl->GetVarNRTThreshold() );
// //}
// 
// unsigned int CELEnvironVariable::GetMtskWbSpUnitCollTime()
// {
// 	return (m_pImpl->GetMtskWbSpUnitCollTime() );
// }
// 
// unsigned int CELEnvironVariable::GetMtskWbSpUnitCollNum()
// {
// 	return (m_pImpl->GetMtskWbSpUnitCollNum() );
// }
// 
// unsigned int CELEnvironVariable::GetMtskSpinDFUnitCollTime()
// {
// 	return (m_pImpl->GetMtskSpinDFUnitCollTime() );
// }
// 
// unsigned int CELEnvironVariable::GetMtskSpinDFUnitCollNum()
// {
// 	return (m_pImpl->GetMtskSpinDFUnitCollNum() );
// }

int CELEnvironVariable::GetMtskDVRatio()
{
	return m_stEnvironVariable.iDVRatio;
}

// // LOB생성을 위한 쵯 LOB 개수
// unsigned int CELEnvironVariable::GetEmmgNumOfMinPulseToLOB()
// {
// 	return (m_pImpl->GetEmmgNumOfMinPulseToLOB() );
// }
// 
// 빔 생성을 위한 최소 LOB 개수
unsigned int CELEnvironVariable::GetEmmgNumOfMinLobToBeam()
{	
	return m_stEnvironVariable.uiEmmgNumOfMinLobToBeam;
}

float CELEnvironVariable::GetEobIndfRangeMeters()
{	
	return m_stEnvironVariable.fEobIndfRangeMeters;
}
 
unsigned int CELEnvironVariable::GetEmmgEmitterDeleteTimeSec()
{	
	return m_stEnvironVariable.uiEmmgEmitterDeleteTimeSec;
}

// bool CELEnvironVariable::GetEmmgUseHgLOBToPosEst()
// {
// 	return (m_pImpl->GetEmmgUseHgLOBToPosEst() );
// }
// 
// unsigned int CELEnvironVariable::GetMiscElinPodTempPeriodSec()
// {
// 	return (m_pImpl->GetMiscElinPodTempPeriodSec() );
// }
// 
// unsigned int CELEnvironVariable::GetHGAInfoPeriodMilSec()
// {
// 	return (m_pImpl->GetHGAInfoPeriodMilSec() );
// }
// 
// void CELEnvironVariable::GetIdnfWeightAndMargin(SELTASKDB::SELDBEnvVarIdnf& i_stData)
// {
// 	return (m_pImpl->GetIdnfWeightAndMargin(i_stData) );
// }
// 
// int CELEnvironVariable::GetMapRgbHgLobFig()
// {
// 	return (m_pImpl->GetMapRgbHgLobFig() );
// }
// 
// unsigned int CELEnvironVariable::GetMapRgbHgLobColor()
// {
// 	return (m_pImpl->GetMapRgbHgLobColor() );
// }
// 
// int CELEnvironVariable::GetMapRgbOtherSiteLobFig()
// {
// 	return (m_pImpl->GetMapRgbOtherSiteLobFig() );
// }
// 
// unsigned int CELEnvironVariable::GetMapRgbOtherSiteLobColor()
// {
// 	return (m_pImpl->GetMapRgbOtherSiteLobColor() );
// }
// 
// int CELEnvironVariable::GetMapRgbDtLobValidFig()
// {
// 	return (m_pImpl->GetMapRgbDtLobValidFig() );
// }
// 
// unsigned int CELEnvironVariable::GetMapRgbDtLobValidColor()
// {
// 	return (m_pImpl->GetMapRgbDtLobValidColor() );
// }
// 
// int CELEnvironVariable::GetMapRgbDtLobInvalidFig()
// {
// 	return (m_pImpl->GetMapRgbDtLobInvalidFig() );
// }
// 
// unsigned int CELEnvironVariable::GetMapRgbDtLobInvalidColor()
// {
// 	return (m_pImpl->GetMapRgbDtLobInvalidColor() );
// }
// 
// bool CELEnvironVariable::GetDisplayPinNumWithThreat()
// {
// 	return (m_pImpl->GetDisplayPinNumWithThreat() );
// }
// //////////////////////////////////////////////////////////////////////////
// unsigned int CELEnvironVariable::GetMapRgbValidPosEstCEPorEEPEmitter()
// {
// 	return (m_pImpl->GetMapRgbValidPosEstCEPorEEPEmitter() );
// }
// 
// unsigned int CELEnvironVariable::GetMapRgbInvalidPosEstCEPorEEPEmitter()
// {
// 	return (m_pImpl->GetMapRgbInvalidPosEstCEPorEEPEmitter() );
// }
// 
// unsigned int CELEnvironVariable::GetMapRgbOldEmitter()
// {
// 	return (m_pImpl->GetMapRgbOldEmitter() );
// }
// 
// unsigned int CELEnvironVariable::GetMapRgbUnknownEmitter()
// {
// 	return (m_pImpl->GetMapRgbUnknownEmitter() );
// }
// 
// unsigned int CELEnvironVariable::GetMapRgbNewEmitter()
// {
// 	return (m_pImpl->GetMapRgbNewEmitter() );
// }
// 
// unsigned int CELEnvironVariable::GetMapRgbValidPosEstCEPorEEPBeam()
// {
// 	return (m_pImpl->GetMapRgbValidPosEstCEPorEEPBeam() );
// }
// 
// unsigned int CELEnvironVariable::GetMapRgbInvalidPosEstCEPorEEPBeam()
// {
// 	return (m_pImpl->GetMapRgbInvalidPosEstCEPorEEPBeam() );
// }
// 
// unsigned int CELEnvironVariable::GetDtAntFovDeg()
// {
// 	return (m_pImpl->GetDtAntFovDeg() );
// }
// 
// unsigned int CELEnvironVariable::GetDtAntRangeMeter()
// {
// 	return (m_pImpl->GetDtAntRangeMeter() );
// }
// 
// unsigned int CELEnvironVariable::GetMapRgbDTAntVisibleArea()
// {
// 	return (m_pImpl->GetMapRgbDTAntVisibleArea() );
// }
// 
// unsigned int CELEnvironVariable::GetMapTextFontSize()
// {
// 	return (m_pImpl->GetMapTextFontSize() );
// }
// 
// unsigned int CELEnvironVariable::GetMapLobLength()
// {
// 	return (m_pImpl->GetMapLobLength() );
// }
// 
// 
// //////////////////////////////////////////////////////////////////////////
// 
// 
// std::string CELEnvironVariable::GetDefault2525BSymbology()
// {
// 	return (m_pImpl->GetDefault2525BSymbology() );
// }
// 
// std::string CELEnvironVariable::GetRptTacRepReceiverAndSender(std::string& i_strElnot, int& i_nPinNum, bool i_bIsFromEmitterWnd)
// {
// 	return (m_pImpl->GetRptTacRepReceiverAndSender(i_strElnot, i_nPinNum, i_bIsFromEmitterWnd) );
// }
// 
// std::string CELEnvironVariable::GetRptTacRepDefaultAddressee(std::string& i_strElnot, int& i_nPinNum, bool i_bIsFromEmitterWnd)
// {
// 	return (m_pImpl->GetRptTacRepDefaultAddressee(i_strElnot, i_nPinNum, i_bIsFromEmitterWnd) );
// }
// 
// std::string CELEnvironVariable::GetRptTacRepDefaultAddressor(std::string& i_strElnot, int& i_nPinNum, bool i_bIsFromEmitterWnd)
// {
// 	return (m_pImpl->GetRptTacRepDefaultAddressor(i_strElnot, i_nPinNum, i_bIsFromEmitterWnd) );
// }
// 
// std::string CELEnvironVariable::GetRptTacRepDefaultSource(std::string& i_strElnot, int& i_nPinNum, bool i_bIsFromEmitterWnd)
// {
// 	return (m_pImpl->GetRptTacRepDefaultSource(i_strElnot, i_nPinNum, i_bIsFromEmitterWnd) );
// }
// 
// std::string CELEnvironVariable::GetRptTacRepDistributor(std::string& i_strElnot, int& i_nPinNum, bool i_bIsFromEmitterWnd)
// {
// 	return (m_pImpl->GetRptTacRepDistributor(i_strElnot, i_nPinNum, i_bIsFromEmitterWnd) );
// }
// 
// std::string CELEnvironVariable::GetRptTacRepDistributorIndicator(std::string& i_strElnot, int& i_nPinNum, bool i_bIsFromEmitterWnd)
// {
// 	return (m_pImpl->GetRptTacRepDistributorIndicator(i_strElnot, i_nPinNum, i_bIsFromEmitterWnd) );
// }
// 
// std::string CELEnvironVariable::GetRptTacRepActy(std::string& i_strElnot, int& i_nPinNum, bool i_bIsFromEmitterWnd)
// {
// 	return (m_pImpl->GetRptTacRepActy(i_strElnot, i_nPinNum, i_bIsFromEmitterWnd) );
// }
// 
// //std::string CELEnvironVariable::GetRptTacRepControlSign(std::string& i_strElnot, int& i_nPinNum, bool i_bIsFromEmitterWnd)
// //{
// //	return (m_pImpl->GetRptTacRepControlSign(i_strElnot, i_nPinNum, i_bIsFromEmitterWnd) );
// //}
// 
// std::string CELEnvironVariable::GetRptTacRepRoute(std::string& i_strElnot, int& i_nPinNum, bool i_bIsFromEmitterWnd)
// {
// 	return (m_pImpl->GetRptTacRepRoute(i_strElnot, i_nPinNum, i_bIsFromEmitterWnd) );
// }
// 
// std::string CELEnvironVariable::GetRptTacRepEndOfSentence(std::string& i_strElnot, int& i_nPinNum, bool i_bIsFromEmitterWnd)
// {
// 	return (m_pImpl->GetRptTacRepEndOfSentence(i_strElnot, i_nPinNum, i_bIsFromEmitterWnd) );
// }
// 
// std::string CELEnvironVariable::GetRptTacRepSendPriority(std::string& i_strElnot, int& i_nPinNum, bool i_bIsFromEmitterWnd)
// {
// 	return (m_pImpl->GetRptTacRepSendPriority(i_strElnot, i_nPinNum, i_bIsFromEmitterWnd) );
// }
// 
// std::string CELEnvironVariable::GetRptTacRepNationality(std::string& i_strElnot, int& i_nPinNum, bool i_bIsFromEmitterWnd)
// {
// 	return (m_pImpl->GetRptTacRepNationality(i_strElnot, i_nPinNum, i_bIsFromEmitterWnd) );
// }
// 
// std::string CELEnvironVariable::GetRptTacRepUserDefineOperationID(std::string& i_strElnot, int& i_nPinNum, bool i_bIsFromEmitterWnd)
// {
// 	return (m_pImpl->GetRptTacRepUserDefineOperationID(i_strElnot, i_nPinNum, i_bIsFromEmitterWnd) );
// }
// 
// std::string CELEnvironVariable::GetRptTacRepUserDefineEquipID(std::string& i_strElnot, int& i_nPinNum, bool i_bIsFromEmitterWnd)
// {
// 	return (m_pImpl->GetRptTacRepUserDefineEquipID(i_strElnot, i_nPinNum, i_bIsFromEmitterWnd) );
// }
// 
// std::string CELEnvironVariable::GetRptTacRepUserDefineEquipNickName(std::string& i_strElnot, int& i_nPinNum, bool i_bIsFromEmitterWnd)
// {
// 	return (m_pImpl->GetRptTacRepUserDefineEquipNickName(i_strElnot, i_nPinNum, i_bIsFromEmitterWnd) );
// }
// 
// std::string CELEnvironVariable::GetRptTacRepUserDefineEquipPinNum(std::string& i_strElnot, int& i_nPinNum, bool i_bIsFromEmitterWnd)
// {
// 	return (m_pImpl->GetRptTacRepUserDefineEquipPinNum(i_strElnot, i_nPinNum, i_bIsFromEmitterWnd) );
// }
// 
// std::string CELEnvironVariable::GetRptTacElintDefaultPublisher(std::string& i_strElnot, int& i_nPinNum, bool i_bIsFromEmitterWnd)
// {
// 	return (m_pImpl->GetRptTacElintDefaultPublisher(i_strElnot, i_nPinNum, i_bIsFromEmitterWnd) );
// }
// 
// std::string CELEnvironVariable::GetRptTacElintDefaultCollector(std::string& i_strElnot, int& i_nPinNum, bool i_bIsFromEmitterWnd)
// {
// 	return (m_pImpl->GetRptTacElintDefaultCollector(i_strElnot, i_nPinNum, i_bIsFromEmitterWnd) );
// }
// 
// 
// std::string CELEnvironVariable::GetRptTacElintNationality(std::string& i_strElnot, int& i_nPinNum, bool i_bIsFromEmitterWnd)
// {
// 	return (m_pImpl->GetRptTacElintNationality(i_strElnot, i_nPinNum, i_bIsFromEmitterWnd) );
// }
// 
// std::string CELEnvironVariable::GetRptUniformCSecretLevel()
// {
// 	return (m_pImpl->GetRptUniformCSecretLevel() );
// }
// 
// std::string CELEnvironVariable::GetRptUniformCSigKind()
// {
// 	return (m_pImpl->GetRptUniformCSigKind() );
// }
// 
// EnumLibType CELEnvironVariable::GetEOBLibType()
// {
// 	return (m_pImpl->GetEOBLibType() );
// }
// 
// EnumLibType CELEnvironVariable::GetCEDLibType()
// {
// 	return (m_pImpl->GetCEDLibType() );
// }
// 
// 
// std::string CELEnvironVariable::GetRptUniformCSensor()
// {
// 	return (m_pImpl->GetRptUniformCSensor() );
// }
// 
// std::string CELEnvironVariable::GetRptUniformCCollector()
// {
// 	return (m_pImpl->GetRptUniformCCollector() );
// }
// 
// std::string CELEnvironVariable::GetRptUniformCPlatform()
// {
// 	return (m_pImpl->GetRptUniformCPlatform() );
// }
// 
// std::string CELEnvironVariable::GetRptUniformCNationality(std::string& i_strElnot, int& i_nPinNum, bool& i_bIsFromEmitterWnd)
// {
// 	return (m_pImpl->GetRptUniformCNationality(i_strElnot, i_nPinNum, i_bIsFromEmitterWnd) );
// }
// 
// std::string CELEnvironVariable::GetRptUnitCode()
// {
// 	return (m_pImpl->GetRptUnitCode());
// }
// 
// void CELEnvironVariable::ToggleLeftFOVDisplay()
// {
// 	m_pImpl->ToggleLeftFOVDisplay();
// }
// 
// void CELEnvironVariable::ToggleRightFOVDisplay()
// {
// 	m_pImpl->ToggleRightFOVDisplay();
// }
// 
// bool CELEnvironVariable::GetLeftFOVDisplay()
// {
// 	return m_pImpl->GetLeftFOVDisplay();
// }
// 
// bool CELEnvironVariable::GetRightFOVDisplay()
// {
// 	return m_pImpl->GetRightFOVDisplay();
// }
// 
// void CELEnvironVariable::UpdateOperCtrlEnvVariables(SOCSystemVariable* i_pstData)
// {
// 	m_pImpl->UpdateOperCtrlEnvVariables(i_pstData);
// }
// 
// //bool CELEnvironVariable::GetUseHGTaskToPosEst(int i_nLinkNum)//LJN_DEL
// //{
// //	return (m_pImpl->GetUseHGTaskToPosEst(i_nLinkNum) );
// //}
// //
// //float CELEnvironVariable::GetDIValidValue(int i_nLinkNum)//LJN_DEL
// //{
// //	return (m_pImpl->GetDIValidValue(i_nLinkNum) );
// //}
