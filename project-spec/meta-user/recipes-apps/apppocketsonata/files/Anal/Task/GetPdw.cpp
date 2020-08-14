// GetPdw.cpp: implementation of the CGetPdw class.
//
//////////////////////////////////////////////////////////////////////

// PC용 상위 클래스에 전달하기 위한 선언

#include "stdafx.h"

#ifdef _WIN32
#include <io.h>
#include <fcntl.h>

#else
#include <vxworks.h>

#include <ioLib.h>
#include <iv.h>
#include <intLib.h>
#include <sysLib.h>
#include <loglib.h>
#include <tftpLib.h>
#include <rebootLib.h>

#include "../../BootShell/ManSbc.h"

#endif

#include "../OFP_Main.h"

#include "GetPdw.h"

const char strAnal[3][10] = { "NEW", "KSP", "SCN" } ;
const char strPDWFileName[ALL_BAND+1][30] = { "PRGDISK:/col_band0.pdw", "PRGDISK:/col_band1.pdw", "PRGDISK:/col_band2.pdw", "PRGDISK:/col_band3.pdw", "PRGDISK:/col_cdband.pdw", "PRGDISK:/col_all.pdw" } ;
const char strLocalPDWFileName[ALL_BAND+1][30] = { "대역(2-6GHz).pdw", "대역(6-10GHz).pdw", "대역(10-14GHz).pdw", "대역(14-18GHz).pdw", "CD밴드.pdw", "ALL밴드.pdw" } ;

UINT stChannelSelectionSwitch[ALL_BAND] = { 0x0, 0x0e, 0x0d, 0x0b, 0x7 } ;

int stCo=0;

bool gstbSimulator=true;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGetPdw::CGetPdw( char *pTaskName )
{
	strcpy_s( m_taskName, pTaskName );

	MallocBuffer();

	InitVar();
	InitTask();

}

CGetPdw::~CGetPdw()
{
	free( m_pCollectPdw );
	free( m_pBitCollectPdw );

	free( *(m_pbSendAnal+NEW_ANAL) );
	free( *(m_pbSendAnal+KWN_ANAL) );
	free( *(m_pbSendAnal+SCN_ANAL) );
	free( m_pbSendAnal );
	//free( m_stPDWData[BANK1].pPdw);
	//free( m_stPDWData[BANK2].pPdw);

	//delete m_thePdwFilter;
	//delete theGenPulseInfo;

}

/**
  * @brief		선택한 PDW 파일명을 설정하고 PDW 파일 핸들러를 세팅한다.
  * @param		CString strFilename
  * @return 	void
*/
bool CGetPdw::Init( CString strFilename )
{
	m_bStartFlag = true;

	m_strPDWFilename = strFilename;

	ClosePDWFile();

	if (m_PDWFile.Open(m_strPDWFilename.GetBuffer(), CFile::modeRead | CFile::typeBinary) == TRUE) {
		m_bOpen = true;
	}
	else {
		m_bOpen = false;
	}

	return m_bOpen;

}

void CGetPdw::ClosePDWFile()
{

	if (m_bOpen == true) {
		m_PDWFile.Close();
		m_bOpen = false;
	}

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::InitVar
		\author   조철희
		\return   void
		\version  0.0.26
		\date     2008-05-27 11:52:43
		\warning
*/
void CGetPdw::InitVar()
{
	int i;

	m_bStartFlag = false;

	m_nTotalCountOfPDW = 0;
	m_nCountOfPDW = 0;

	m_mode = NORMAL_COLLECT_MODE;

	// 메모리 뱅크는 기본 시작이 0 부터 시작한다.
	//m_ci.enMemoryBank = BANK1;

	//m_ci.x.bMode = 1;
	//m_ci.x.count = 0;
	//m_ci.x.nStat = ANALYSIS_END;

	//m_nMaxChannel[i].channel_selection = NOT_USE_CHANNEL;
	//m_nMaxChannel[i].noEMT = -1;

	//m_nCWControl[i].noEMT = -1;
	//m_nCWControl[i].bCWCtrl = FALSE;
	//m_nCWControl[i].cw_init_threshold = m_nCWControl[i].cw_threshold = GetInitCWThreshold( (enum BAND_INFO) i );

	// 필터 설정 여부를 초기화한다.
	//m_fi.bUse = FALSE;

	// m_nBitBand = CD_BAND;

	m_nBitMode = 0;

	// Send Anal 메시지 클리어
	i = _abs(-4);

	for (i = 0; i < _max(KNOWN_NO_FILTER, SCAN_NO_FILTER); ++i) {
		SetSendAnal(NEW_ANAL, i);
	}
	for (i = 0; i < _max(KNOWN_NO_FILTER, SCAN_NO_FILTER); ++i) {
		SetSendAnal(KWN_ANAL, i);
	}
	for (i = 0; i < _max(KNOWN_NO_FILTER, SCAN_NO_FILTER); ++i) {
		SetSendAnal(SCN_ANAL, i);
	}

	//m_thePdwFilter->InitVar();
	//theGenPulseInfo->InitVar();

	m_FilterFrq[0].low = 0x23f;		// 575			//  498.75 MHz
	m_FilterFrq[0].hgh = 0xEC1;		// 3777			// 2001.25 MHz

	m_FilterFrq[1].low = 0x96F;		// 575			
	m_FilterFrq[1].hgh = 0xAFF;		// 3777

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::InitTask
		\author   조철희
		\return   void
		\version  0.0.26
		\date     2008-05-27 11:52:46
		\warning
*/
void CGetPdw::InitTask()
{
#ifndef _WIN32
	STATUS rst;

	rst = sysIntDisable( IRQ_NUM_COLLECT );
	if( rst == ERROR ) {
		PrintErr( ( "\n [W] IRQ%d에 대한 인터럽트 발생 에러가 발생했습니다." , IRQ_NUM_COLLECT ) );
	}

	rst = intConnect( INUM_TO_IVEC(VEC_NUM_COLLECT), (VOIDFUNCPTR) IsrWrapper, (int) this );
	if( rst == ERROR ) {
		PrintErr( ( "\n [W] IRQ%d에 %d를 연결하는데 에러가 발생했습니다." , IRQ_NUM_COLLECT, VEC_NUM_COLLECT ) );
	}

	CreatePDWFiles();

#endif

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::MallocBuffer
		\author   조철희
		\return   void
		\version  0.0.26
		\date     2008-05-28 13:40:09
		\warning
*/
void CGetPdw::MallocBuffer()
{

	m_pCollectPdw = (_PDW *)malloc(sizeof(_PDW)* PDW_ONE_BLOCK_SIZE);
	if( m_pCollectPdw == NULL ) {
		PrintErr( ( "\n [W] 수집용 버퍼를 할당하지 못했습니다 !" ) );
	}

	m_pBitCollectPdw = ( _PDW * ) malloc( sizeof( _PDW ) * MAX_BIT_COLLECT_COUNT );
	if( m_pBitCollectPdw == NULL ) {
		PrintErr( ( "\n [W] 비트 수집용 버퍼를 할당하지 못했습니다 !" ) );
	}

	//theGenPulseInfo = new CGenPulseInfo;
// 	if (theGenPulseInfo == NULL) {
// 		PrintErr( ( "\n [W] 메모리 부족입니다. CGenPulseInfo 객체를 생성할 수 없습니다 !" ) );
// 	}

	// 송신 메시지 여부 결과 버퍼 할당
	m_pbSendAnal = ( BOOL ** ) malloc( sizeof( BOOL * ) * ( SCN_ANAL+1 ) );
	if( m_pbSendAnal == NULL ) {
		PrintErr( ( "\n [W] 버퍼를 할당하지 못했습니다 !" ) );
	}
	*(m_pbSendAnal+NEW_ANAL) = ( BOOL * ) malloc( sizeof( BOOL ) * _max( KNOWN_NO_FILTER, SCAN_NO_FILTER ) );
	if( *(m_pbSendAnal+NEW_ANAL) == NULL ) {
		PrintErr( ( "\n [W] 버퍼를 할당하지 못했습니다 !" ) );
	}
	*(m_pbSendAnal+KWN_ANAL) = ( BOOL * ) malloc( sizeof( BOOL ) * _max( KNOWN_NO_FILTER, SCAN_NO_FILTER ) );
	if( *(m_pbSendAnal+KWN_ANAL) == NULL ) {
		PrintErr( ( "\n [W] 버퍼를 할당하지 못했습니다 !" ) );
	}
	*(m_pbSendAnal+SCN_ANAL) = ( BOOL * ) malloc( sizeof( BOOL ) * _max( KNOWN_NO_FILTER, SCAN_NO_FILTER ) );
	if( *(m_pbSendAnal+SCN_ANAL) == NULL ) {
		PrintErr( ( "\n [W] 버퍼를 할당하지 못했습니다 !" ) );
	}

// 	for (i = 0 ; i <= BANK2; ++i) {
// 		m_stPDWData[i].pPdw = (_PDW *)malloc(sizeof(_PDW)* MAX_PDW);
// 		if (m_stPDWData[i].pPdw == NULL) {
// 			PrintErr(("\n [W] 버퍼를 할당하지 못했습니다 !"));
// 		}
// 	}

}


//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::ClearInit
		\author   조철희
		\return   void
		\version  0.0.26
		\date     2008-05-27 13:05:37
		\warning
*/
void CGetPdw::ClearInit()
{
#ifndef _WIN32
	STATUS rst;

	// 수집 인터럽트를 Disbale 한다.
	rst = sysIntDisable( IRQ_NUM_COLLECT );
	if( rst == ERROR ) {
		PrintErr( ( "\n [W] The IRQ %d Disable Error !" , IRQ_NUM_COLLECT ) );
	}

	InitVar();

#endif

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::StartAnal
		\author   조철희
		\return   void
		\version  0.0.26
		\date     2008-05-27 19:19:34
		\warning
*/
bool CGetPdw::Start()
{
	bool bRet=FALSE;
	//STR_PDWDATA *pPdw;

	// 수집 모드를 정상으로 설정한다.
	SetMode( NORMAL_COLLECT_MODE );

#ifndef _WIN32
	STATUS rst;

	rst = sysIntDisable( IRQ_NUM_COLLECT );
	if( rst == ERROR ) {
		PrintErr( ( "\n [W] IRQ %d Disable Error !" , IRQ_NUM_COLLECT ) );
	}

	// 신호 분석하기 위한 하드웨어 초기화를 수행한다.
	//theGenPulseInfo->RequestPowerOnInit();

	//////////////////////////////////////////////////////////////////////////
	// 신호 수집을 하기 위한 초기화를 수행한다.
	InitVar();

	// 전술모드에서 시험모드로 진행시에 이전에 설정한 수집 인터럽트가 발생되어
	// 수집 오류를 처리하게 된다.
	//
	// taskDelay( 5*OS_ONE_SEC );

	rst = sysIntEnable( IRQ_NUM_COLLECT );
	if( rst == ERROR ) {
		PrintErr( ( "\n [W] IRQ %d Enable Error !" , IRQ_NUM_COLLECT ) );
	}

#else
	if (m_nCountOfPDW != 0) {
		m_SendQMsg.uiOpcode = REQ_STEP_ANAL;
		m_SendQMsg.usSize = sizeof(STR_PDWDATA) - ( ( _MAX_PDW - m_nCountOfPDW ) * sizeof(_PDW) );
			//sizeof(_PDW)* m_nCountOfPDW + sizeof(m_SendQMsg.x.stPDWData.count);

		strcpy( m_SendQMsg.x.stPDWData.aucTaskID, "과제 없음" );
		m_SendQMsg.x.stPDWData.enBandWidth = en5MHZ_BW;
		m_SendQMsg.x.stPDWData.iCollectorID = RADARCOL_1;
		m_SendQMsg.x.stPDWData.iIsStorePDW = 1;

		m_SendQMsg.x.stPDWData.count = m_nCountOfPDW;
		memcpy( & m_SendQMsg.x.stPDWData.stPDW, m_pCollectPdw, sizeof(_PDW)* m_nCountOfPDW );
		SendMessage(&m_SendQMsg);

		bRet = true;
	}

#endif

	return bRet;

}


//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::Run
		\author   조철희
		\return   void
		\version  0.0.26
		\date     2008-05-27 11:52:48
		\warning
*/
void CGetPdw::Run()
{
#ifdef _WIN32
	bool bRslt = true;
	SQMsg stMsg;

	while( IsRunning() == TRUE) {
 		m_cond.Wait(); // 시그널을 기다리는 중이다. 

 		bRslt = GetMsgFromQ(stMsg);

		if(bRslt)
 		{
			ParseMessage( & stMsg );			//
 		}
 		else // 큐에 더 이상 메시지가 없다는 이야기다.
 		{
 			m_cond.LIGResetEvent();
 		}				
	}

#else
	for( ;; ) {
		ReceiveMessage();

		if( TRUE == ParseMessage() ) {
			
		}
	}
#endif

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::ParseMessage
		\author   조철희
		\return   BOOL
		\version  0.0.26
		\date     2008-05-27 11:53:11
		\warning
*/
BOOL CGetPdw::ParseMessage( SQMsg *psqMsg )
{

	switch ( psqMsg->uiOpcode ) {
		// 메시지 처리
		case REQ_SENDCOLLECTINGLIST :
			ReqSendCollectingList( psqMsg );
			break;

		//////////////////////////////////////////////////////////////////////////
		case REQ_STEP_ANAL:
			CollectingPDW(FALSE, & psqMsg->x.stPDWData );
			StorePDWFile();

			SendMessageToAnalTask(psqMsg );
			break;

		case REQ_POWER_ON_IBIT :
			SetMode( BIT_MODE );
			RequestPowerOnIBit();
			//theRunBit->SendEchoMessage();
			break;

		case REQ_USER_PBIT :
		case REQ_SELF_CBIT :
			m_nBitMode = psqMsg->uiOpcode;
			break;

		// 처음 수집을 시작할 때와 수집 제어를 하기 위한 것.
		case REQ_START_ANAL :
			//StartAnal();

			// 추적필터로 추적되지 않은 에미터에 대해서 삭제 처리 체크하는 타이머 동작하게 함.
			//theManAet->RequestSetupTime( MANAET_RUN_PERIOD );
			// break 없이 아래 문을 수행해야 함.

		case REQ_START_COLLECT :
			ScheduleCollect();
			break;

		// PDW 정보를 수집하기 위한 것.
		case REQ_COLLECTING_PDW :
			// 펄스정보생성판으로부터 PDW를 수신한다.
			CollectingPDW( FALSE, NULL );
			SavePDW();

			// 수집 후, BIT를 수행한다.
			RunRFPathBit();

			// 다음번 메모리 뱅크에 수집하도록 설정한다.
			ScheduleCollect();

			// 소프트웨어 필터판을 이용해서 각 채널에 PDW를 저장한다.
			//CollectByFilter();

			// 탐지 수집 플레그를 "COLLECTING_END" 마킹을 한다.
			//SetColStat( NEW_ANAL, 0, COLLECTING_END );

			// 스캔분석을 위한 수집 플레그를 마킹한다.
			//UpdateScanMode( m_ci.nBand );

			// 분석 타스크로 메시지를 전송한다.
			//SendAllSigAnal();
			break;

		case REQ_HOLD_ANAL :
			Printf( "\n Hold tGetPdw..." );
			WaitEchoMessage();
			break;

		case REQ_STOP_ANAL :
		case REQ_KEY_PFM :
		case REQ_RELOAD_UDF :
			StopAnal();
			break;

		// 수집 모드에서의 PDW 수집
		case REQ_COLLECT_FOR_BAND :
			//StartAnal();
			SetCollect();
			break;

		case REQ_COLLECTING_PDW_FOR_BAND :
			CollectingPDW( FALSE, NULL );
			SendPdwData();

			// 신호 분석을 수행 한다.
			//theSigAnal->m_theNewSigAnal->Start( pPDWData );

			// StopAnal();
			break;

		case REQ_BACKUP_PDW :
			BackupPDWFiles();
			break;

		case REQ_REMOVE_PDW :
			RemovePDWFiles();
			ClosePDWFiles();
			CreatePDWFiles();
			break;

		case REQ_COLLECTING_ERROR :
			PrintErr( ( "\n [W] 수집 에러입니다 !" ) );
			break;

		case REQ_HOLD_COLLECT :
			WhereIs;
			break;

		case REF_SOFT_RESET :
#ifndef _WIN32
			reboot(0);
#endif
			break;

		default :
			PrintErr(("\n [W] 잘못된 메시지[0x%x]를 수신했습니다.", psqMsg->uiOpcode));
			return FALSE;
	}
	
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::ScheduleCollect
		\author   조철희
		\return   void
		\version  0.0.26
		\date     2008-05-27 18:44:36
		\warning
*/
void CGetPdw::ScheduleCollect()
{

	// 수집할 밴드를 설정한다.
	//NextBand();

	// 초단수신기에 스위치 제어를 설정한다.
	//SendSwitchControl();

	// 수집 모드에 따라서 필터 영역을 설정한다.
	//SetFreqAoaPwSa();

	// 시간 및 수집 개수를 정한다.
	//SetCountTime();

	// 펄스정보생성판으로 전달한다.
	//SetCollectParameter( NO_FILTER_FOR_COLLECTING );

	// Printf( "\n Set up Band: %d, Mem. Bank: %d" , m_ci.nBand, m_ci.nMemoryBank );
	// Printf( "\n noChannel(%d) Collection Time(%d), Collect Number(%d)" , m_fi.no, m_fi.nCollectTime, m_fi.coCollect );

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::SetCollect
		\author   조철희
		\return   void
		\version  0.0.44
		\date     2008-09-19 14:09:38
		\warning
*/
void CGetPdw::SetCollect()
{

	// 수집 모드를 시험모드로 설정한다.
	m_mode = TEST_MODE;

	//m_ci.nBand = m_nBand;
	//m_ci.enMemoryBank = BANK1;

	// 초단수신기에 스위치 제어를 설정한다.
	SendSwitchControl();

	// 수집 모드에 따라서 필터 영역을 설정한다.
	SetFreqAoaPwSa();

	// 시간 및 수집 개수를 정한다.
	//SetCountTime();

	// 펄스정보생성판으로 전달한다.
	SetCollectParameter( NO_FILTER_FOR_COLLECTING );

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::NextBand
		\author   조철희
		\return   void
		\version  0.0.26
		\date     2008-05-29 09:26:44
		\warning
*/
// void CGetPdw::NextBand()
// {
// 	if( m_mode == BIT_MODE ) {
// 		int iBand;
// 
// 		iBand = (int) ( m_ci.nBand + 1 );
// 		iBand = iBand > F_BAND4 ? F_BAND1 : iBand;
// 
// 		m_ci.nBand = ( enum BAND_INFO ) iBand;
// 
// 		Printf( "\n Bit Band[%d]" , m_ci.nBand );
// 	}
// 
// 	// 대역 설정 모드는 평시 모드와 전투 모드 로 나뉜다.
// 	// 평시 모드는 아래와 같이,
// 	// 순차적으로 대역1->대역2->대역3->대역4->C/D 밴드->대역1 순서로 순차적인 흐름을 한다.
// 	// 전투 모드는,
// 	// 평시 모드처럼 순차적으로 대역을 설정하지만 UDF를 참조해서 위협이 있는 대역만 설정한다.
// 	else {
// 		int iBand, nWait=1;
// 
// 		iBand = (int) ( m_ci.nBand + 1 );
// 		iBand = iBand > CD_BAND ? F_BAND1 : iBand;
// 
// 		m_ci.nBand = ( enum BAND_INFO ) iBand;
// 
// 		while( TRUE ) {
// 			// theSigAnal->MsgQShow();
// 			// MsgQShow();
// 
// 			PrintErr( ( "\n [W] %d 번째, 분석 속도가 느려서 %d 대역을 수집 대기합니다." , nWait, iBand ) );
// #ifndef _WIN32
// 			if( ERROR == taskDelay( OS_ONE_SEC ) )
// 				PrintErr( ( "\n error !" ) );
// #endif
// 
// 			++ nWait;
// 			if( nWait > MAX_COLLECTING_SUSPEND )
// 				break;
// 			// m_thePdwFilter->PrintFullNewCol();
// 		}
// 
// 		Printf( "\n Forced to collect in %d band" , iBand );
// 
// 		// 신호 분석 타스크를 확인해서 재생성할수도 있다.
// 
// 	}
// 
// 	// 메모리 뱅크는 다음 뱅크를 선택한다.
// 	if( m_ci.nMemoryBank == BANK1 )
// 		m_ci.nMemoryBank = BANK2;
// 	else
// 		m_ci.nMemoryBank = BANK1;
// 
// }

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::SetFreqAoaPwSa
		\author   조철희
		\param    noFilter 인자형태 int
		\return   void
		\version  0.0.26
		\date     2008-05-29 09:52:33
		\warning
*/
void CGetPdw::SetFreqAoaPwSa()
{
	// 수집할 주파수, 방위 영역은 이전 분석 결과에 따라서 수집 영역을 결정한다.
	WideFreqAoaPwSa();

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::WideFreqAoaPwSa
		\author   조철희
		\return   void
		\version  0.0.26
		\date     2008-05-28 12:15:12
		\warning
*/
void CGetPdw::WideFreqAoaPwSa()
{

	// 필터판 설정
// 	if( m_mode == NORMAL_COLLECT_MODE ) {
// 		m_fi.nChannel = m_nMaxChannel[ m_ci.nBand ].channel_selection;
// 		m_fi.nDV = DV_DISABLE;
// 	}
// 	else {
// 		m_fi.nChannel = NOT_USE_CHANNEL;
// 		m_fi.nDV = DV_DISABLE;
// 	}
// 
// 	m_fi.nFunction = PASS_FILTER;
// 
// 	m_fi.nMode = NORMAL_MODE;
// 	m_fi.nPulseType = ( enum PULSE_TYPE ) ALL_PULSE;
// 
// 	// 필터판의 범위 설정
// 	// 1. 방위 설정
// 	m_fi.aoa.low = 0x0;
// 	m_fi.aoa.hgh = 0xFFFFFFFF;
// 
// 	// 2. 대역별 주파수 범위 설정
// 	switch( m_ci.nBand ) {
// 		case CD_BAND :
// 			m_fi.frq.low = m_FilterFrq[1].low;			//  498.75 MHz
// 			m_fi.frq.hgh = m_FilterFrq[1].hgh;			// 2001.25 MHz
// 			break;
// 
// 		default :
// 			m_fi.frq.low = m_FilterFrq[0].low;			// 1998.75 MHz, 10001.25 MHz, 14001.25 MHz, 13998.75 MHz
// 			m_fi.frq.hgh = m_FilterFrq[0].hgh;			// 6001.25 MHz,  5998.75 MHz,  9998.75 MHz, 18001.25 MHz
// 			break;
// 	}
// 
// 	// 3. 펄스폭 설정
// 	// 70ns 이상의 PDW만 수집하도록 한다.
// 	if( m_mode == NORMAL_COLLECT_MODE )
// 		m_fi.pw.low = 8;
// 	else
// 		m_fi.pw.low = 0x0;
// 	m_fi.pw.hgh = 0xFFFFFFFF;
// 
// 	// 신호세기 설정
// 	m_fi.sa.low = 0x0;
// 	m_fi.sa.hgh = 0xFFFFFFFF;

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::SetCountTime
		\author   조철희
		\param    bMode 인자형태 BOOL
		\return   void
		\version  0.0.26
		\date     2008-05-29 10:26:47
		\warning
*/
// void CGetPdw::SetCountTime()
// {
// 	UINT nCollectTime;
// 
// 	// 전술 모드시의 수집 개수와 시간 설정을 처리
// 	switch( m_mode ) {
// 		case NORMAL_COLLECT_MODE :
// 			// 수집 개수와 시간은 UDF 의 위협을 참조해서 수집 시간과 수집 개수를 정한다.
// 			//
// 			// 스캔 분석할 에미터가 있을 때는 기본값으로 수집 시간과 개수를 정한다.
// 			if( (nCollectTime=m_thePdwFilter->GetScanThreatInBand( m_ci.nBand ) ) ) {
// 				Printf( "\n scan...[%d]" , nCollectTime );		WhereIs;
// 				m_fi.coCollect = SCN_COLLECT_PDW;
// 				m_fi.nCollectTime = nCollectTime * PG_ONE_MILLISEC;
// 			}
// 			// 스캔 분석할 에미터가 없을 때는 기본값으로 수집 시간과 개수를 정한다.
// 			else {
// 				m_fi.coCollect = DEFAULT_CO_COLLECTION;
// 				m_fi.nCollectTime = DEFAULT_COLLECTION_TIME;	//200 * PG_ONE_MILLISEC;	// 1000 * PG_ONE_MILLISEC;
// 
// 			}
// 			break;
// 
// 		case BIT_MODE :
// 			// BIT 일때 신호 수집 개수 및 시간
// 			m_fi.coCollect = BIT_PDW_COUNT;								// 10개
// 			m_fi.nCollectTime = BIT_PDW_COLLECT_TIMEOUT;	// 1000 * PG_ONE_MILLISEC;
// 			// printf( "\n bitmode[%d, %d]" , m_fi.coCollect, m_fi.nCollectTime );
// 			break;
// 
// 		case TEST_MODE :
// 			// 수집 개수와 시간은 UDF의 위협을 참조해서 수집 시간과 수집 개수를 정한다.
// 			m_fi.coCollect = 250; // MAX_COLLECT_COUNT;
// 			m_fi.nCollectTime = 3000 * PG_ONE_MILLISEC; // 1000 * PG_ONE_MILLISEC;
// 			break;
// 
// 		case CLOSE_MODE :
// 			WhereIs;
// 			break;
// 
// 	}
// 
// }


//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::SetCollectParameter
		\author   조철희
		\param    nFilter 인자형태 int
		\return   void
		\version  0.0.26
		\date     2008-05-27 12:43:12
		\warning
*/
void CGetPdw::SetCollectParameter( int nFilter )
{

	//m_fi.no = nFilter;
	//m_fi.bUse = TRUE;
	//m_fi.nBank = m_ci.enMemoryBank;
	//m_fi.nBand = m_ci.nBand;

	// 메모리 뱅크를 기억하게 한다.
	//m_ci.x.nBank = m_fi.nBank;

	// CW 임계값을 제어한다.
	//ControlCWThreshold( m_fi.nBand );

	//theGenPulseInfo->SetCollectParameter( & m_fi );

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::intHandlerCollect
		\author   조철희
		\return   void
		\version  0.0.26
		\date     2008-05-27 18:00:10
		\warning
*/
void CGetPdw::intHandlerCollect()
{
	//STR_QUEUE_MESSAGE qMsg;

#ifndef _WIN32
	// logMsg( "Complete collection interrupt..[%d,%d,%d]\n", m_mode, m_ci.nBand, stCo,0,0,0 );
#endif

// 	qMsg.opData = m_ci.nBand;
// 	if( m_mode == NORMAL_COLLECT_MODE )
// 		qMsg.opCode = REQ_COLLECTING_PDW;
// 	else if( m_mode == TEST_MODE )
// 		qMsg.opCode = REQ_COLLECTING_PDW_FOR_BAND;
// 	else {
// 		return;
// 	}
// 
// 	SendMessage( & qMsg, NO_WAIT );

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::IsrWrapper
		\author   조철희
		\param    pSelf 인자형태 CGetPdw *
		\return   void
		\version  0.0.27
		\date     2008-06-18 09:42:29
		\warning
*/
void CGetPdw::IsrWrapper( CGetPdw *pSelf )
{
	pSelf->intHandlerCollect();

}

/**
  * @brief		로딩할 PDW 파일을 블 단위로 파일을 로딩한다.
  * @return 	void
*/
void CGetPdw::ReadPDWFileBlock()
{

	m_nCountOfPDW = m_PDWFile.Read(m_pCollectPdw, sizeof(_PDW)* PDW_ONE_BLOCK_SIZE);
	m_nCountOfPDW /= sizeof(_PDW);

	if( m_nCountOfPDW == 0 ) {
		m_bEndOfFile = true;
	}
	else {
		m_bEndOfFile = false;
		m_nTotalCountOfPDW += m_nCountOfPDW;
	}

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    PDW 파일을 블럭 로딩하여 처리한다.
		\author   조철희
		\param    bBitMode 인자형태 BOOL
		\param    pPDWData 인자형태 STR_PDWDATA *
		\return   void
		\version  0.0.26
		\date     2008-05-27 19:25:14
		\warning
*/
void CGetPdw::CollectingPDW(BOOL bBitMode, STR_PDWDATA *pstMsgPDWData )
{
	int i, count;

	STR_PDWDATA *pstPDWData;
	_PDW *pBankPDW;

	_PDW *pstPDW;

	_spOneSec = FDIV( 1000000000, _toaRes[en5MHZ_BW] );
	_spOneMilli = FDIV( 1000000, _toaRes[en5MHZ_BW] );
	_spOneMicrosec = FDIV( 1000, _toaRes[en5MHZ_BW] );
	_spOneNanosec = FDIV( 1, _toaRes[en5MHZ_BW] );

	_spAMPres = 0.25;

	if( bBitMode == TRUE ) {
		//m_nBand = GetFilterBand();
		//pstPdw = pCollectPdw;
	}
	else {
		pstPDW = (_PDW *) & pstMsgPDWData->stPDW;
	}

	// 수집 뱅크 결정
// 	if (m_ci.enMemoryBank == BANK1) {
// 		bank = BANK2;
// 	}
// 	else {
// 		bank = BANK1;
// 	}
// 
// 	m_ci.enMemoryBank = bank;

	count = pstMsgPDWData->count;

	if( GetMode() == BIT_MODE ) {
		Printf( "\n BIT Co[%d]" , count );
	}
	else {
		Printf( "\n Norm Co[%d]" , count );
	}

	pstPDWData = & m_stPDWData;
	pBankPDW = pstPDWData->stPDW;

	//m_ci.x.nBank = bank;
	pstPDWData->count = 0;
	//m_ci.x.count = 0;
	for( i=0 ; i < count ; ++i ) {
		//theGenPulseInfo->GetOnePdw( pstPDW );

		/*! \bug  수집한 PDW 중에서 이상이 있는 PDW는 버린다.
		    \date 2009-06-22 18:34:01, 조철희
		*/
		// 펄스폭이 0 인것은 버린다.
#ifdef _ELINT_
		if ( pstPDW->iPW == 0) {
			continue;
		}
#else
		if ( pstPDW->item.pw == 0) {
			continue;
		}
#endif

		// 밴드값을 수집 PDW에 추가 저장함.
		//pCollectPdw->word[3] = 0x0;
		memcpy(pBankPDW, pstPDW, sizeof(_PDW) );

		pstPDWData->count++;

		++ pBankPDW;
		++ pstPDW;
	}

	// 수집 종료 마킹
	if (pstPDWData->count != 0) {
		//m_pCollectPdw[count].item.flag = 0xFF;
		//m_ci.x.count = pstPDWData->count;
	}
	else {
		// PDW 초기화
		memset( & m_pCollectPdw[0], 0, sizeof(_PDW) );
		//m_pCollectPdw[0].word[0] = m_pCollectPdw[0].word[1] = m_pCollectPdw[0].word[2] = m_pCollectPdw[0].word[3] = 0;

		//m_pCollectPdw[0].x.band = m_nBand;
		//m_pCollectPdw[0].item.flag = 0xFF;
		//m_ci.x.count = 0;
	}

	PrintAllPDW( & pstMsgPDWData->stPDW[0], pstPDWData->count );

}

/**
  * @brief		수집 타스크에서 수신한 PDW 데이터를 파일로 저장한다.
  * @return 	void
*/
void CGetPdw::StorePDWFile()
{
// 	if (m_StorePDWFile.Open()) {
// 
// 	}
	// theLogDebug->DebugPrintf( )

}


//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::PrintAllPDW
		\author   조철희
		\param    pPdw 인자형태 _PDW *
		\param    count 인자형태 UINT
		\return   void
		\version  0.0.26
		\date     2008-05-28 12:48:29
		\warning
*/
void CGetPdw::PrintAllPDW( _PDW *pCollectPdw, UINT count )
{
	UINT i;

	gPaRes[0].max = 0;

	if( count != 0 ) {
		Printf( "\n===== [PDW 개수 : %d] =====" , count );
		Printf( "\nNO\t\tTOA[us]\t\t\t\tPW[ns]\t\t\t\t\tFreq(MHz)\t\tAoa(Dv)\t\tPW\tPA\tTOA\tPW" );
		for( i=0 ; i < count && i < 200 ; ++i ) {
			//Printf( "\n%3d(%1d)\t%5d\t%3d%2d\t%8d]", AOACNV(pCollectPdw->x.aoa), pCollectPdw->x.dv, FRQCNV( m_nBand, pCollectPdw->x.freq ), PWCNV(pCollectPdw->x.pw), PACNV(pCollectPdw->x.pa), pCollectPdw->x.toa );
			//Printf("\n[0x%08x][0x%08x][0x%08x][0x%08x]", pCollectPdw->word[0], pCollectPdw->word[1], pCollectPdw->word[2], pCollectPdw->word[3]);
#ifdef _ELINT_
			Printf( "\n{%03d}\t%10d(%8lld), \t\t%7d\t%7d\t%5d\t%4.2f", 
				i+1,
				TOAusCNV( pCollectPdw->llTOA ), pCollectPdw->llTOA, TOAusCNV(pCollectPdw->iPW), FRQMhzCNV( 0, pCollectPdw->iFreq ), AOACNV(pCollectPdw->iAOA), PACNV(pCollectPdw->iPA ) );
// 				pCollectPdw->iPulseType, -1, -1, \
// 				AOACNV(pCollectPdw->iAOA), pCollectPdw->iAOA, \
// 				0, PACNV(pCollectPdw->iPA, 0), pCollectPdw->iPA, 0 );

#else
			Printf( "\n{%03d}\t%10d[%10d]\t%8d\t%8d[0x%x]\t%x\t%x\t%x\t%d[%x]\t%x\t%d[%x]\t[%x]", \
								i,
								TOAusCNV(pCollectPdw->item.toa), pCollectPdw->item.toa, PWCNV(pCollectPdw->item.pw), \
								FRQCNV(pCollectPdw->item.band, pCollectPdw->item.freq), pCollectPdw->item.freq, \
								pCollectPdw->item.stat, pCollectPdw->item.max_channel, pCollectPdw->item.dv, \
								AOACNV(pCollectPdw->item.aoa), pCollectPdw->item.aoa, \
								pCollectPdw->item.filter_tag, PACNV(pCollectPdw->item.amplitude, pCollectPdw->item.band), pCollectPdw->item.amplitude, pCollectPdw->item.band );
#endif
			++ pCollectPdw;

		}
	}

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::GetFilterChannel
		\author   조철희
		\return   int
		\version  0.0.26
		\date     2008-05-28 16:18:43
		\warning
*/
int CGetPdw::GetFilterChannel()
{
	
	return 0;

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::CollectByFilter
		\author   조철희
		\return   void
		\version  0.0.29
		\date     2008-07-09 10:55:32
		\warning
*/
// void CGetPdw::CollectByFilter()
// {
// 	int count;
// 
// 	count = m_ci.x[m_nBand].count;
// 	m_thePdwFilter->CollectByFilter( m_pCollectPdw, count, m_nBand );
// 
// }

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::SendAllSigAnal
		\author   조철희
		\return   void
		\version  0.0.29
		\date     2008-07-09 13:07:09
		\warning
*/
// void CGetPdw::SendAllSigAnal()
// {
// 	int i;
// 	STR_PDWFILTER_INFO *pFilter;
// 
// 	SendSigAnal( NEW_ANAL, 0 );
// 
// 	pFilter = m_thePdwFilter->GetTrkFilter( 0 );
// 	for( i=0 ; i < KNOWN_NO_FILTER ; ++i ) {
// 		if( pFilter->bUse == TRUE && pFilter->bComplete == TRUE && IsSendAnal( KWN_ANAL, i ) == FALSE ) {
// 			SetSendAnal( KWN_ANAL, i );
// 			SendSigAnal( KWN_ANAL, i );
// 		}
// 		++ pFilter;
// 
// 	}
// 
// 	pFilter = m_thePdwFilter->GetScnFilter( 0 );
// 	for( i=0 ; i < SCAN_NO_FILTER ; ++i ) {
// 		if( pFilter->bUse == TRUE && pFilter->bComplete == TRUE && IsSendAnal( SCN_ANAL, i ) == FALSE ) {
// 			Printf( "\n SCAN" );	WhereIs;
// 			SetSendAnal( SCN_ANAL, i );
// 			SendSigAnal( SCN_ANAL, i );
// 
// 		}
// 		++ pFilter;
// 	}
// 
// }

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::SendSigAnal
		\author   조철희
		\param    Anal 인자형태 enum ANAL
		\param    noFilter 인자형태 int
		\return   void
		\version  0.0.29
		\date     2008-07-09 14:22:36
		\warning
*/
void CGetPdw::SendSigAnal( enum ANAL Anal, int noFilter )
{
	STR_QUEUE_MESSAGE interQMsg;

	if( KWN_ANAL == Anal ) {
		// int noEMT = m_thePdwFilter->GetNoEMT( Anal, noFilter );
		// Printf( "\n Send[%d, %d]" , noEMT, noFilter );
	}

	// 분석 시작 명령을 전달한다.
	interQMsg.opCode = REQ_START_ANAL;
	interQMsg.opData = noFilter;
	interQMsg.address1 = (UCHAR) Anal;
	//interQMsg.address2 = (UCHAR) m_nBand;
	//theSigAnal->SendMessage( & interQMsg );

	//STR_PDWDATA *pPDWData = m_thePdwFilter->GetPDWData( Anal, noFilter );
	// Printf( "\n Send Anal[%s,%d,%d]" , strAnal[Anal], noFilter, pPDWData->count );

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::SavePDW
		\author   조철희
		\return   void
		\version  0.0.30
		\date     2008-07-12 15:27:34
		\warning
*/
void CGetPdw::SavePDW()
{
#ifdef _WIN32
	Printf( "\n Saving PDW..." );

#else
	int nWrite;
	_PDW *pCollectPdw;

	// FILE *fd1, *fd2;

	if( GetMode() == BIT_MODE ) {
		pCollectPdw = m_pBitCollectPdw;
	}
	else {
		pCollectPdw = m_pCollectPdw;
	}

	//fd1 = fopen( strPDWFileName[m_nBand], "ab+" );
	//fd2 = fopen( strPDWFileName[ALL_BAND], "ab+" );

	// 특정 대역에 수집한 PDW를 저장
	//nWrite = fwrite( (char *) pCollectPdw, sizeof( _PDW ), m_ci.x[m_nBand].count, fd1 );
	nWrite = write( m_PdwFile[m_nBand], (char *) pCollectPdw, sizeof( _PDW )*m_ci.x[m_nBand].count );

	// 모든 대역에 순차적인 신호를 저장
	//nWrite = fwrite( (char *) pCollectPdw, sizeof( _PDW ), m_ci.x[ALL_BAND].count, fd2 );
	nWrite = write( m_PdwFile[ALL_BAND], (char *) pCollectPdw, sizeof( _PDW )*m_ci.x[m_nBand].count );

	//fclose( fd1 ); fclose( fd2 );

	// printf( "\n[%d]" , nWrite );
	if( nWrite <= 0 ) {
		Printf( "\n Clear All PDW files..." );

		RemovePDWFiles();
		ClosePDWFiles();
		CreatePDWFiles();
	}

#endif

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::BackupPDWFiles
		\author   조철희
		\return   BOOL
		\version  0.0.30
		\date     2008-07-12 19:55:12
		\warning
*/
BOOL CGetPdw::BackupPDWFiles()
{
#ifndef _WIN32
	int i;
	int fid;
	TFTP_DESC	*spTftpDesc;

	Printf( "\n Backup the PDW files..." );
	printf( "\n Backup the PDW files..." );

	for( i=0 ; i <= ALL_BAND ; ++i ) {
		char filename[50];

		fid = open( strPDWFileName[i], O_RDWR, 0644 );

		if( ( spTftpDesc = tftpInit() ) == NULL ) {
			WhereIs;
			close( fid );
			return false;
		}

		/*	tftp 설정을 초기화 */
		if( ( tftpPeerSet( spTftpDesc, stBootParams.had /* TFTP_SERVER_IP */, TFTP_PORT ) == ERROR ) ||
				( tftpModeSet (spTftpDesc, TFTP_MODE ) == ERROR ) ) {
			(void) tftpQuit (spTftpDesc);
			return false;
		}

		sprintf( filename, "%s" , strLocalPDWFileName[i] );
		Printf( "\n Writing the pdw files[%s, %d]" , filename, fid );
		Printf( "\n Writing the pdw files[%s, %d]" , filename, fid );
		if(	ERROR == tftpCopy( stBootParams.had /* TFTP_SERVER_IP */, 0, filename, "put", "binary", fid ) ) {
			PrintErr( ( "\n [W] Can't transfer the PDW files..." ) );
			close( fid );
			(void) tftpQuit (spTftpDesc);
			return false;
		}

		// 2차 서버에 전송
		/*
		if( strcmp( TFTP_SERVER_IP, stBootParams.had ) == 0 ) {
			printf( "\n*2차 서버에 PDW 전달..." );
		}
		*/

		close( fid );
		(void) tftpQuit (spTftpDesc);

		printf( "\n The %s file is completed transfer !" , strPDWFileName[i] );

	}
#endif

	Printf( "\n Complete...\n" );
	printf( "\n Complete...\n" );
	return true;

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::RemovePDWFiles
		\author   조철희
		\return   void
		\version  0.0.49
		\date     2008-10-06 12:11:40
		\warning
*/
void CGetPdw::RemovePDWFiles()
{
#ifndef _WIN32
	int i;

	for( i=0 ; i <= ALL_BAND ; ++i ) {
		STATUS stat;

		stat = remove( & strPDWFileName[i][0] );

		if( stat == OK )
			Printf( "\n Remove the PDW file[%s]" , strPDWFileName[i] );
		else
			Printf( "\n Error of Removing PDW file[%s]" , strPDWFileName[i] );
	}

#endif

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::SendSwitchControl
		\author   조철희
		\param    offset 인자형태 int
		\return   void
		\version  0.0.33
		\date     2008-07-24 17:19:15
		\warning
*/
void CGetPdw::SendSwitchControl( int offset )
{
// 	STR_QUEUE_MESSAGE interQMsg;
// 
// 	if( m_mode == BIT_MODE ) {
// 		// 초단수신기의 스위치를 대역에 맞춰서 옮긴다.
// 		interQMsg.opCode = REQ_SWITCH_CONTROL;
// 		interQMsg.opData = m_ci.nBand + BIT_OFFSET;
// 		interQMsg.address1 = 1;
// 
// 		// Printf( "\n SendSwitchControl...BIT" );
// 	}
// 	else {
// 		// 초단수신기의 스위치를 대역에 맞춰서 옮긴다.
// 		interQMsg.opCode = REQ_SWITCH_CONTROL;
// 		interQMsg.opData = m_ci.nBand;
// 		interQMsg.address1 = 1;
// 
// 		// Printf( "\n SendSwitchControl...Normal" );
// 	}
// 
// #ifndef _WIN32
// 	theSendSerial->SendMessage( & interQMsg );
// #endif
// 
// 	/*! \bug  최소 지연 시간은 수신기 개수 만큼 대기한다.
// 	    \date 2008-12-17 19:11:52, 조철희
// 	*/
// 	if( FALSE == WaitEchoMessage( (TOTAL_RECEIVER+1)*MAX_TO_HF_COMM ) )
// 		PrintErr( ( "\n [W] 초단수신기와 연결이 되지 않았습니다. 케이블을 확인해주세요 !" ) );

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::StopAnal
		\author   조철희
		\return   void
		\version  0.0.41
		\date     2008-08-24 15:40:27
		\warning
*/
void CGetPdw::StopAnal()
{
#ifndef _WIN32
	sysIntDisable( IRQ_NUM_COLLECT );

	taskDelay(10L);
#endif

	EmptyQueue();
	InitVar();

	// WaitEchoMessage( OS_ONE_MILLISEC(10) );
	SendEchoMessage();

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::SendPdwData
		\author   조철희
		\return   void
		\version  0.0.44
		\date     2008-09-19 15:07:25
		\warning
*/
void CGetPdw::SendPdwData()
{
// 	m_sndLanMsg.nOpcode = REQ_PDW_DATA;
// 	m_sndLanMsg.nDataSize = sizeof( _PDW ) * m_ci.x[m_nBand].count;
// 	if( m_pCollectPdw[0].word[0] != 0 && m_ci.x[m_nBand].count != 1 ) {
// 		memcpy( & m_sndLanMsg.u.byte, m_pCollectPdw, m_sndLanMsg.nDataSize );
// 
// 		//theTcpIpServer->SendLanMessage( & m_sndLanMsg );
// 	}
// 	else {
// 		printf( "\n*No Send" );
// 	}

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::ClearPBit
		\author   조철희
		\return   void
		\version  0.0.48
		\date     2008-10-02 13:28:22
		\warning
*/
void CGetPdw::ClearPBit()
{
	//stPowerOnPbit.pp_bit.word = _spFail;
	//theGenPulseInfo->ClearPBit();

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::ClearIBit
		\author   조철희
		\return   void
		\version  0.0.48
		\date     2008-10-02 13:55:45
		\warning
*/
void CGetPdw::ClearIBit()
{
	//stPowerOnIbit.pp_bit.word = _spFail;
	//theGenPulseInfo->ClearIBit();

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::ClearCBit
		\author   조철희
		\return   void
		\version  0.0.49
		\date     2008-10-07 18:00:13
		\warning
*/
void CGetPdw::ClearCBit()
{
	//stPowerOnCbit.pp_bit.word = _spFail;
	//theGenPulseInfo->ClearCBit();

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::SetTrackFilter
		\author   조철희
		\param    pFilterInfo 인자형태 STR_PDWFILTER_INFO *
		\return   void
		\version  0.0.48
		\date     2008-10-06 21:11:59
		\warning
*/
// void CGetPdw::SetTrackFilter( STR_PDWFILTER_INFO *pFilterInfo ) 
// { 
// 	ClearSendAnal( KWN_ANAL, pFilterInfo->noFilter );
// 	m_thePdwFilter->SetTrackFilter( pFilterInfo ); 
// 
// }

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::SetScanFilter
		\author   조철희
		\param    pFilterInfo 인자형태 STR_PDWFILTER_INFO *
		\return   void
		\version  0.0.63
		\date     2008-12-12 13:37:20
		\warning
*/
// void CGetPdw::SetScanFilter( STR_PDWFILTER_INFO *pFilterInfo ) 
// { 
// 	ClearSendAnal( SCN_ANAL, pFilterInfo->noFilter );
// 	m_thePdwFilter->SetScanFilter( pFilterInfo ); 
// 
// }

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::CloseTrackFilter
		\author   조철희
		\param    noFilter 인자형태 int
		\return   void
		\version  0.0.48
		\date     2008-10-06 21:20:47
		\warning
*/
// void CGetPdw::CloseTrackFilter( int noFilter ) 
// { 
// 	SetSendAnal( KWN_ANAL, noFilter );
// 	m_thePdwFilter->CloseTrackFilter( noFilter );
// 
// }

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::CloseScanFilter
		\author   조철희
		\param    noFilter 인자형태 int
		\return   void
		\version  0.0.73
		\date     2009-03-04 19:32:05
		\warning
*/
// void CGetPdw::CloseScanFilter( int noFilter ) 
// { 
// 	SetSendAnal( SCN_ANAL, noFilter );
// 	m_thePdwFilter->CloseScanFilter( noFilter );
// 
// }

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::RequestPowerOnIBit
		\author   조철희
		\return   void
		\version  0.0.51
		\date     2008-10-10 11:12:47
		\warning
*/
void CGetPdw::RequestPowerOnIBit() 
{
	
	//RunBITAllPDW( & stPowerOnIbit.pp_bit );

	// Printf( "\n IBit Result[0x%x]", stPowerOnIbit.pp_bit.word );

	// 펄스정보생판의 IBIT 결과 요구
	//theGenPulseInfo->RequestPowerOnIBit();

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::RunBITAllPDW
		\author   조철희
		\param    pPPBit 인자형태 UNI_PP_BIT *
		\return   void
		\version  0.0.59
		\date     2008-11-21 10:41:13
		\warning
*/
// void CGetPdw::RunBITAllPDW( UNI_PP_BIT *pPPBit )
// {
// // 	int i;
// // 	int backup_count;
// // 	enum BAND_INFO backup_band, backup_ci_band;
// // 
// // 	// 현재 대역을 저장한다.
// // 	backup_band = m_nBand;
// // 	backup_count = m_ci.x[m_nBand].count;
// // 	backup_ci_band = m_ci.nBand;
// // 
// // 	// 다음 밴드를 결정해서 설정하기 때문에, 필터판의 대역은 이전 밴드로 설정하게 한다. 
// // 	m_ci.nBand = CD_BAND;
// // 
// // 	for( i=F_BAND1 ; i <= F_BAND4 ; ++i ) {
// // 		UINT nBitResult;
// // 
// // 		ScheduleCollect();
// // 
// // #ifndef _WIN32
// // 		// taskDelay( (int) ( 400 * OS_ONE_MILLISEC ) );
// // 
// // #endif
// // 
// // 		CollectingPDW( TRUE );
// // 		// printf( "\n Band[%d], Count[%d]" , i, m_ci.x[m_nBand].count );
// // 		// SavePDW();
// // 
// // 		// PDW 펄스열 검증
// // 		nBitResult = VerifyBITPDW() == TRUE ? 0 : 1;
// // 
// // 		// 비트 결과 저장
// // 		if( i == F_BAND1 )
// // 			pPPBit->x.bitBand_1 = nBitResult;
// // 		else if( i == F_BAND2 )
// // 			pPPBit->x.bitBand_2 = nBitResult;
// // 		else if( i == F_BAND3 )
// // 			pPPBit->x.bitBand_3 = nBitResult;
// // 		else
// // 			pPPBit->x.bitBand_4 = nBitResult;
// // 	}
// // 
// // 	// 현재 대역을 복구한다.
// // 	m_nBand = backup_band;
// // 	m_ci.x[m_nBand].count = backup_count;
// // 	m_ci.nBand = backup_ci_band;
// 
// }


//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::RequestUserPBit
		\author   조철희
		\return   void
		\version  0.0.49
		\date     2008-10-07 17:42:23
		\warning
*/
// void CGetPdw::RequestUserPBit()
// {
// #ifndef _WIN32
// 	sysIntDisable( IRQ_NUM_COLLECT );
// #endif
// 
// 	Printf( "\n\n Processing the PBIT in tGetPdw..." );
// 
// 	SetMode( BIT_MODE );
// 
// 	RunBITAllPDW( & stPowerOnPbit.pp_bit );
// 
// 	Printf( "\n PBit Result[0x%x]", stPowerOnPbit.pp_bit.word );
// 
// #ifndef _WIN32
// 	// 인터럽트 설정 이후에 바로 인터럽트 서비스 루틴이 발생한다.
// 	sysIntEnable( IRQ_NUM_COLLECT );
// 
// 	taskDelay( (int)( 10*OS_ONE_MILLISEC ) );
// #endif
// 
// 	// 비트 모드 종료
// 	m_nBitMode = 0;
// 
// 	SetMode( NORMAL_COLLECT_MODE );
// 
// 	//////////////////////////////////////////////////////////////////////////
// 	// 펄스정보생성판의 PBIT 메시지를 처리합니다.
// 	//theGenPulseInfo->RequestUserPBit();
// 
// 	// 상부 타스크에게 PBIT 완료를 전달한다.
// 	//theRunBit->SendEchoMessage();
// 
// }
// 
// //////////////////////////////////////////////////////////////////////////
// /*! \brief    CGetPdw::RequestPowerOnCBit
// 		\author   조철희
// 		\return   void
// 		\version  0.0.49
// 		\date     2008-10-07 17:43:37
// 		\warning
// */
// void CGetPdw::RequestPowerOnCBit()
// {
// 
// #ifndef _WIN32
// 	sysIntDisable( IRQ_NUM_COLLECT );
// #endif
// 
// 	Printf( "\n\n Processing the CBIT in tGetPdw..." );
// 
// 	SetMode( BIT_MODE );
// 
// 	RunBITAllPDW( & stPowerOnCbit.pp_bit );
// 
// #ifndef _WIN32
// 	// 인터럽트 설정 이후에 바로 인터럽트 서비스 루틴이 발생한다.
// 	sysIntEnable( IRQ_NUM_COLLECT );
// 
// 	taskDelay( (int)( 10*OS_ONE_MILLISEC ) );
// #endif
// 
// 	// 비트 모드 종료
// 	m_nBitMode = 0;
// 
// 	SetMode( NORMAL_COLLECT_MODE );
// 
// 	//////////////////////////////////////////////////////////////////////////
// 	// 펄스정보생성판의 CBIT 메시지를 처리합니다.
// 	//theGenPulseInfo->RequestPowerOnCBit();
// 
// 	// 상부 타스크에게 CBIT 완료를 전달한다.
// 	//theRunBit->SendEchoMessage();
// 
// }

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::CreatePDWFiles
		\author   조철희
		\return   void
		\version  0.0.50
		\date     2008-10-09 14:13:51
		\warning
*/
void CGetPdw::CreatePDWFiles()
{

	// PDW 파일을 저장하기 위한 사전 파일을 생성한다.
	for( int i=0 ; i <= ALL_BAND ; ++i ) {
		// int fd;
		m_PdwFile[i] = open( strPDWFileName[i], O_CREAT | O_RDWR | O_APPEND, 0644 );
		if( m_PdwFile[i] == ERROR ) {
			PrintErr( ( "\n [W] Can't create PDW file[%d]..." , i ) );
		}
		// close( fd );

	}

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::ClosePDWFiles
		\author   조철희
		\return   void
		\version  0.0.50
		\date     2008-10-09 14:15:05
		\warning
*/
void CGetPdw::ClosePDWFiles()
{
	for( int i=0 ; i <= ALL_BAND ; ++i ) {
		close( m_PdwFile[i] );
	}

}


//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::VerifyBITPDW
		\author   조철희
		\return   BOOL
		\version  0.0.51
		\date     2008-10-22 14:57:09
		\warning
*/
BOOL CGetPdw::VerifyBITPDW()
{
// 	int i, pdw_count;
// 	_PDW *pCollectPdw;	
// 
// 	if( FALSE && (pdw_count=m_ci.x[m_nBand].count) != BIT_PDW_COUNT )
// 		return FALSE;
// 
// 	return TRUE;
// 
// 	// PDW 제원 비교
// 	pCollectPdw = m_pCollectPdw;
// 	for( i=0 ; i < pdw_count ; ++i ) {
// 		UINT val;
// 
// 		// 방위 검증
// 		val = pCollectPdw->x.aoa;
// 		printf( "\n AOA[%x]" , val );
// 		if( CompMeanDiff( val, BIT_AOA, BIT_AOA_MARGIN ) )
// 			return FALSE;
// 
// 		// 주파수 검증
// 		val = pCollectPdw->x.freq;
// 		printf( "\n Freq[%x]" , val );
// 		if( CompMeanDiff( val, BIT_FREQ, BIT_FREQ_MARGIN ) )
// 			return FALSE;
// 
// 		// PA 검증
// 		val = pCollectPdw->x.pa;
// 		printf( "\n PA[%x]" , val );
// 		if( CompMeanDiff( val, BIT_PA, BIT_PA_MARGIN ) )
// 			return FALSE;
// 
// 		// PW 검증
// 		val = pCollectPdw->x.pw;
// 		printf( "\n PW[%x]" , val );
// 		if( CompMeanDiff( val, BIT_PW, BIT_PW_MARGIN ) )
// 			return FALSE;
// 
// 		// Direction Valid 검증
// 		val = pCollectPdw->x.dv;
// 		printf( "\n DV[%x]" , val );
// 		if( val == 0 )
// 			return FALSE;
// 
// 		// STAT 검증
// 		val = pCollectPdw->x.stat;
// 		printf( "\n Stat[%x]" , val );
// 		if( val == 0 )
// 			return FALSE;
// 
// 		++ pCollectPdw;
// 
// 	}
// 
// 	PrintAllPDW( m_pCollectPdw, pdw_count );

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::CompMeanDiff
		\author   조철희
		\param    x 인자형태 int
		\param    y 인자형태 int
		\param    thresh 인자형태 int
		\return   BOOL
		\version  0.0.52
		\date     2008-10-24 11:24:38
		\warning
*/
BOOL CGetPdw::CompMeanDiff(int x, int y, int thresh)
{
  int diff;

  diff = _diffabs( x, y );

  if( diff <= thresh )
    return TRUE;
  else
		return FALSE;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::SetMaxChannel
		\author   조철희
		\param    pAet 인자형태 STR_AET *
		\param    channel_selection 인자형태 enum CHANNEL_SELECTION
		\return   void
		\version  0.0.53
		\date     2008-11-03 19:55:44
		\warning
*/
void CGetPdw::SetMaxChannel( STR_AET *pAet, enum CHANNEL_SELECTION channel_selection )
{
	m_nMaxChannel[pAet->frq.band-1].channel_selection = channel_selection;
	if( NOT_USE_CHANNEL == channel_selection )
		m_nMaxChannel[pAet->frq.band-1].noEMT = -1;
	else {
		m_nMaxChannel[pAet->frq.band-1].noEMT = pAet->noEMT;
		Printf( "\n*Set Max Channel[0x%x], noEMT[%d], Band[%d]" , channel_selection, pAet->noEMT, pAet->frq.band-1 );
	}

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::CouldUseMaxChannel
		\author   조철희
		\param    band 인자형태 enum BAND_INFO
		\return   BOOL
		\version  0.0.53
		\date     2008-11-03 19:54:12
		\warning
*/
BOOL CGetPdw::CouldUseMaxChannel( enum BAND_INFO band )
{
	if( m_nMaxChannel[band].noEMT == -1 )
		return TRUE;
	else
		return FALSE;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::ClearMaxChannel
		\author   조철희
		\param    pAet 인자형태 STR_AET *
		\return   void
		\version  0.0.53
		\date     2008-11-03 21:07:28
		\warning
*/
void CGetPdw::ClearMaxChannel( STR_AET *pAet )
{

	if( m_nMaxChannel[pAet->frq.band-1].noEMT == pAet->noEMT ) {
		SetMaxChannel( pAet, NOT_USE_CHANNEL );
		Printf( "\n*Clear Max Channel noEMT[%d], Band[%d]" , pAet->noEMT, pAet->frq.band-1 );
	}

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::IsUseCWControl
		\author   조철희
		\param    band 인자형태 enum BAND_INFO
		\return   BOOL
		\version  0.0.53
		\date     2008-11-04 17:20:01
		\warning
*/
BOOL CGetPdw::IsUseCWControl( enum BAND_INFO band )
{
	if( m_nCWControl[band].noEMT == -1 )
		return FALSE;
	else
		return TRUE;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::SetCWThreshold
		\author   조철희
		\param    pAet 인자형태 STR_AET *
		\return   void
		\version  0.0.53
		\date     2008-11-04 17:23:43
		\warning
*/
// void CGetPdw::SetCWThreshold( STR_AET *pAet )
// {
// 	int band;
// 	int pa=PACNV( (pAet->pa.max+10), pAet->frq.band );
// 
// 	band = pAet->frq.band - 1;
// 
// 	if( m_nCWControl[band].noEMT == -1 )
// 		m_nCWControl[band].bCWCtrl = TRUE;
// 
// 	m_nCWControl[band].noEMT = pAet->noEMT;
// 	if( band == CD_BAND )
// 		m_nCWControl[band].cw_threshold = CD_DB( pa );
// 	else
// 		m_nCWControl[band].cw_threshold = DB( pa );
// 
// 	
// 	// m_nCWControl[band].cw_init_threshold = GetInitCWThreshold( (enum BAND_INFO) band );
// 	Printf( "\n*Set CW Threshold[%ddBm], noEMT[%d], Band[%d]" , pa, pAet->noEMT, band );
// 
// }

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::ClearCWMark
		\author   조철희
		\param    pAet 인자형태 STR_AET *
		\return   void
		\version  0.0.53
		\date     2008-11-04 17:32:16
		\warning
*/
// void CGetPdw::ClearCWMark( STR_AET *pAet )
// {
// 	int band;
// 
// 	band = pAet->frq.band - 1;
// 	if( m_nCWControl[band].noEMT == pAet->noEMT ) {
// 		m_nCWControl[band].noEMT = -1;
// 		m_nCWControl[band].bCWCtrl = FALSE;
// 
// 		stPowerOnInit.pg_threshold2[band].x.pa_threshold = m_nCWControl[band].cw_init_threshold;
// 
// 		Printf( "\n*Clear CW Threshold noEMT[%d], Band[%d]" , pAet->noEMT, band );
// 	}
// 
// }
// 
// //////////////////////////////////////////////////////////////////////////
// /*! \brief    CGetPdw::ControlCWThreshold
// 		\author   조철희
// 		\param    band 인자형태 enum BAND_INFO
// 		\return   void
// 		\version  0.0.53
// 		\date     2008-11-04 19:42:45
// 		\warning
// */
// void CGetPdw::ControlCWThreshold( enum BAND_INFO band )
// {
// 	if( m_nCWControl[band].bCWCtrl == TRUE ) {
// 		stPowerOnInit.pg_threshold2[band].x.pa_threshold = m_nCWControl[band].cw_threshold;
// 		//printf( "\n PA Threshold High : " );
// 	}
// 	else {
// 		if( m_nBitMode != 0 ) {
// 			stPowerOnInit.pg_threshold2[band].x.pa_threshold = GetInitCWThreshold( (enum BAND_INFO) band );
// 			//printf( "\n m_nBitMode[%d]" , m_nBitMode );
// 		}
// 		else {
// 			stPowerOnInit.pg_threshold2[band].x.pa_threshold = m_nCWControl[band].cw_init_threshold;
// 			//printf( "\n PA Threshold Low : " );
// 		}
// 	}
// 	//printf( "Band[%d, %d]" , band, PACNV( stPowerOnInit.pg_threshold2[band].x.pa_threshold, band+1 ) );
// 
// 	if( IsUseCWControl( band ) == TRUE ) {
// 		m_nCWControl[band].bCWCtrl = ! m_nCWControl[band].bCWCtrl;
// 	}
// 
// }
// 
// //////////////////////////////////////////////////////////////////////////
// /*! \brief    CGetPdw::GetInitCWThreshold
// 		\author   조철희
// 		\param    band 인자형태 enum BAND_INFO
// 		\return   int
// 		\version  0.0.53
// 		\date     2008-11-04 20:12:22
// 		\warning
// */
// int CGetPdw::GetInitCWThreshold( enum BAND_INFO band )
// {
// 	int value=0;
// // 
// // 	switch( band ) {
// // 		case F_BAND1 :
// // 			value = theIni->ReadInt( "System", "LowBand", INIT_PA_THRESHOLD_BAND1 );
// // 			return DB( value );
// // 		case F_BAND2 :
// // 			value = theIni->ReadInt( "System", "HighBand1", INIT_PA_THRESHOLD_BAND2 );
// // 			return DB( value );
// // 		case F_BAND3 :
// // 			value = theIni->ReadInt( "System", "HighBand2", INIT_PA_THRESHOLD_BAND3 );
// // 			return DB( value );
// // 		case F_BAND4 :
// // 			value = theIni->ReadInt( "System", "HighBand3", INIT_PA_THRESHOLD_BAND4 );
// // 			return DB( value );
// // 		case CD_BAND :
// // 		default :
// // 			value = theIni->ReadInt( "System", "CDBand", INIT_PA_THRESHOLD_CD_BAND );
// // 			return CD_DB( value );
// // 	}
// 
// 	return value;
// 
// }
// 
// //////////////////////////////////////////////////////////////////////////
// /*! \brief    CGetPdw::InitCWThreshold
// 		\author   조철희
// 		\param    pThreshold 인자형태 float *
// 		\return   void
// 		\version  0.0.62
// 		\date     2008-12-08 14:10:02
// 		\warning
// */
// void CGetPdw::InitCWThreshold( float *pThreshold )
// {
// // 	m_nCWControl[F_BAND1].cw_init_threshold = DB( pThreshold[F_BAND1] );
// // 	m_nCWControl[F_BAND2].cw_init_threshold = DB( pThreshold[F_BAND2] );
// // 	m_nCWControl[F_BAND3].cw_init_threshold = DB( pThreshold[F_BAND3] );
// // 	m_nCWControl[F_BAND4].cw_init_threshold = DB( pThreshold[F_BAND4] );
// // 
// // 	m_nCWControl[CD_BAND].cw_init_threshold = CD_DB( pThreshold[CD_BAND] );
// 
// }

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::RunRFPathBit
		\author   조철희
		\return   void
		\version  0.0.59
		\date     2008-11-20 18:50:01
		\warning
*/
void CGetPdw::RunRFPathBit()
{
// 	if( m_nBitMode == REQ_USER_PBIT ) {
// 		RequestUserPBit();
// 	}
// 	else if( m_nBitMode == REQ_SELF_CBIT ) {
// 		RequestPowerOnCBit();
// 	}

}
// 
// //////////////////////////////////////////////////////////////////////////
// /*! \brief    CGetPdw::SetFilterFreq
// 		\author   조철희
// 		\param    pFilterFreq 인자형태 STR_LOWHIGH *
// 		\return   void
// 		\version  0.0.63
// 		\date     2008-12-11 13:52:08
// 		\warning
// */
// void CGetPdw::SetFilterFreq( STR_LOWHIGH *pFilterFreq )
// {
// // 	m_FilterFrq[0].low = pFilterFreq[0].low;
// // 	m_FilterFrq[0].hgh = pFilterFreq[0].hgh;
// // 
// // 	m_FilterFrq[1].low = pFilterFreq[1].low;
// // 	m_FilterFrq[1].hgh = pFilterFreq[1].hgh;
// 
// }
// 
//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::SetColStat
		\author   조철희
		\param    Anal 인자형태 enum ANAL
		\param    noFilter 인자형태 int
		\param    stat 인자형태 enum FILTER_STAT
		\return   void
		\version  0.1.00
		\date     2009-09-30 16:40:33
		\warning
*/
void CGetPdw::SetColStat( enum ANAL Anal, int noFilter, enum FILTER_STAT stat ) 
{ 
	// m_thePdwFilter->SetColStat( Anal, noFilter, stat ); 

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CGetPdw::GetIniThreshold
		\author   조철희
		\param    band 인자형태 enum BAND_INFO
		\return   int
		\version  0.1.09
		\date     2009-11-04 21:51:07
		\warning
*/
int CGetPdw::GetIniThreshold( enum BAND_INFO band )
{
	int threshold=0;

// 	switch( band ) {
// 		case F_BAND1 :
// 			threshold = theIni->ReadInt( "System", "LowBand", INIT_PA_THRESHOLD_BAND1 );
// 			break;
// 		case F_BAND2 :
// 			threshold = theIni->ReadInt( "System", "HighBand1", INIT_PA_THRESHOLD_BAND2 );
// 			break;
// 		case F_BAND3 :
// 			threshold = theIni->ReadInt( "System", "HighBand2", INIT_PA_THRESHOLD_BAND3 );
// 			break;
// 		case F_BAND4 :
// 			threshold = theIni->ReadInt( "System", "HighBand3", INIT_PA_THRESHOLD_BAND4 );
// 			break;
// 		case CD_BAND :
// 		default :
// 			threshold = theIni->ReadInt( "System", "CDBand", INIT_PA_THRESHOLD_CD_BAND );
// 			break;
// 	}
	return threshold;
}


/**
  * @brief		
  * @param		SQMsg * psqMsg
  * @return 	void
*/
void CGetPdw::SendMessageToAnalTask(SQMsg *psqMsg, int iIndexOfCollectingList )
{
// 	SQMsg stSendQMsg;
// 
// 	stSendQMsg.uiOpcode = psqMsg->uiOpcode;
// 	stSendQMsg.usSize = sizeof(_PDW) * psqMsg->x.stPDWData.count;
// 	stSendQMsg.x.stPDWData.count = psqMsg->x.stPDWData.count;
// 
// 	stSendQMsg.x.stPDWData.iIsStorePDW = TRUE;
// 	stSendQMsg.x.stPDWData.iCollectorID = RADARCOL_1;
// 	stSendQMsg.x.stPDWData.enBandWidth = en5MHZ_BW;
// 
// 	// 수집 과제 목록을 선택
// 	memcpy( stSendQMsg.x.stPDWData.aucTaskID, m_stCollectingList.stCollectingData[iIndexOfCollectingList].aucTaskID, LENGTH_OF_TASK_ID );
// 
// 	memcpy( stSendQMsg.x.stPDWData.stPDW, m_stPDWData.stPDW, stSendQMsg.usSize );
	theSigAnalTask->SendMessage( psqMsg );

}

/**
  * @brief		수집 과제 요구
  * @param		SCollectingList * pstCollectingList
  * @return 	void
*/
void CGetPdw::ReqSendCollectingList( SCollectingList *pstCollectingList )
{
	//SQMsg stSendQMsg;

	m_SendQMsg.uiOpcode = REQ_SENDCOLLECTINGLIST;
	m_SendQMsg.usSize = sizeof(SCollectingData)* pstCollectingList->uiNumOfList;

	memcpy(&m_SendQMsg.x.stCollectingList, pstCollectingList, m_SendQMsg.usSize );
	SendMessage(&m_SendQMsg);

}

/**
  * @brief		
  * @param		SQMsg * psqMsg
  * @return 	void
*/
void CGetPdw::ReqSendCollectingList(SQMsg *psqMsg)
{
	memcpy( & m_stCollectingList, & psqMsg->x.stCollectingList, psqMsg->usSize );
}
