#include "./SigAnal/stdafx.h"

#include "ParamMngr.h"

// 자료 재전송 하기 위한 테스트 : 모의기로 LOB를 전송하여 연동기에서 LINK2 데이터를 갖고 와서 처리
//#define _RETRANSMIT_TEST_

CParamMngr* CParamMngr::m_pInstance = NULL;

CParamMngr::CParamMngr(void)
	:m_b701DLL(false)
	,m_bPosServerMode(false)
	,m_bPdwIsV2(true)
	,m_bIqIsV2(true)
	,m_bEmitterIsV2(true)
    ,m_bIsMaster(false)
    ,m_bIsLinkShare(false)
    ,m_bIsEmitterMerge(0)
    ,m_bIsIdentifyFreqBasedTask(false)
    ,m_bIsLOBClustering(false)
    ,m_nPOSN2GMI_LINK(0)
    ,m_iDistanceForBeamMerge(0)
    ,m_nLOBNum(0)
    ,m_nMinIDMatchRatio(0)
    ,m_nMaxListItemsOfLOB(0)
	,m_bElintTrace(false)
	,m_bLineNum(false)
	,m_bTimeInfo(false)
	,m_bIsPOSN(false)
    ,m_nAcceleration(10)
	,m_nHwBlanking(0)
	,m_nHWBlankChannel(0)
	,m_nRawPdwSend(0)
	,m_nDBAccessPeriod(1000)
    ,m_nThresholdOfFOV(0)
    ,m_fEffectiveDOADiff1(0)
    ,m_fEffectiveDOADiff2(0)
    ,m_fEffectiveDOADiff3(0)
    ,m_fEffectiveDistOfEOB(0)
    ,m_iEffectiveDist(0)
    ,m_iDeleteThreatWhenCoLOB(0)
	,m_nNumOfPdwProcessing(256)
    ,m_bSimulatorMode(false)
	,m_uiEmitterCEPRadius(0)
	,m_uiEmitterEEPMajorAxis(0)
	,m_uiEmitterEEPMinorAxis(0)
	,m_uiBeamEEPMajorAxis(0)
	,m_uiBeamEEPMinorAxis(0)
	,m_bDisplayValidEmitterOnly(true)
	,m_bDisplayValidBeamOnly(true)
	,m_uiNumOfLOBPerFetch(80)
	,m_uiNumOfPDWPerFetch(80)
	,m_uiNumOfLOBPerFetch_Supervisor(50)
	,m_uiNumOfPDWPerFetch_Supervisor(50)
    ,m_bIsValidLOB(false)

{
	
	LoadParameter();

}


void CParamMngr::LoadParameter()
{
    //char readBuf[100] = {0};

    //char envini_path[100] = "RadarAnl.ini";
    //CString	strTemp = _T("");
    //int iPort = 0;


}

CParamMngr::~CParamMngr(void)
{	
}

CParamMngr* CParamMngr::getInstance()
{
	if(!m_pInstance)
	{
		m_pInstance = new CParamMngr;
	}
	return m_pInstance;	
}

void CParamMngr::ReleaseInstance()
{
	if(m_pInstance)
	{
		delete m_pInstance; 
		m_pInstance = NULL;
	}
}

int CParamMngr::GetPdwRawDataSendParam()
{
    //char readBuf[100] = {0};
    //char *envini_path = (".\\..\\COMMON\\TestConfig.ini");
		
    //GetPrivateProfileString(("ELINT_PDW_RAW_DATA_SEND"), ("PDW_RAW_DATA_SEND"), NULL, readBuf, _countof(readBuf), envini_path);
    //m_nRawPdwSend = _ttoi(readBuf);

	return m_nRawPdwSend;
}

int CParamMngr::GetNumOfPdwProcessing()
{
    //char readBuf[100] = {0};
    //char *envini_path = (".\\..\\COMMON\\TestConfig.ini");

    //GetPrivateProfileString(("NUM_OF_PDW_PROCESSING"), ("NUM_OF_PDW"), NULL, readBuf, _countof(readBuf), envini_path);
    //m_nNumOfPdwProcessing = _ttoi(readBuf);

	return m_nNumOfPdwProcessing;
}
