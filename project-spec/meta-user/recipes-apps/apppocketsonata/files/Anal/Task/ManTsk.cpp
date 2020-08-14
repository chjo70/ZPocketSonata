// ManTsk.cpp: implementation of the CManTsk class.
//
//////////////////////////////////////////////////////////////////////


#ifdef _WIN32
#include "../../A50SigAnal/stdafx.h"

#else
#define _MAIN_GLOBALS_

#include <string.h>
#include <ioLib.h>
#include <taskLib.h>
#include <vxWorks.h>

#endif

#include "../OFP_Main.h"

#include "ManTsk.h"

#include "../../BootShell/ManSbc.h"
#include "../../BootShell/ManFlash.h"
#include "../../BootShell/BootShell.h"


IMPORT CBootShell *theBootShell;
IMPORT CManSbc *theManSbc;


//////////////////////////////////////////////////////////////////////////
/*! \brief    InitClass
		\author   조철희
		\return   void
		\version  0.0.1
		\date     2008-04-25 20:50:04
		\warning
*/
void InitClass()
{
	printf( "\n*Create the all class..." );

#ifndef _WIN32
	theIni = new CIni();
	if( theIni == NULL ) {
		PrintErr( ( "\n [W] 메모리 부족입니다. CIni 객체를 생성할 수 없습니다 !" ) );
	}

	theLogDebug = new CLogDebug( "tLogTsk" , sizeof(STR_QUEUE_LOG_MESSAGE), 1024+1 );
	if( theLogDebug == NULL ) {
		PrintErr( ( "\n [W] 메모리 부족입니다. CLogDebug 객체를 생성할 수 없습니다 !" ) );
	}
	
	theManTsk = new CManTsk( "tManTsk" );
	if( theManTsk == NULL ) {
		PrintErr( ( "\n [W] 메모리 부족입니다. CManTsk 객체를 생성할 수 없습니다 !" ) );
	}

	theSendSerial = new CSendSerial( "tSndSer" );
	if( theSendSerial == NULL ) {
		PrintErr( ( "\n [W] 메모리 부족입니다. CSendSerial 객체를 생성할 수 없습니다 !" ) );
	}
	
	theRecvSerial = new CRecvSerial( "tRcvSer" );
	if( theRecvSerial == NULL ) {
		PrintErr( ( "\n [W] 메모리 부족입니다. CRecvSerial 객체를 생성할 수 없습니다 !" ) );
	}
	
	theRunBit = new CRunBit( "tRunBit" );
	if( theRecvSerial == NULL ) {
		PrintErr( ( "\n [W] 메모리 부족입니다. CRunBit 객체를 생성할 수 없습니다 !" ) );
	}

	theGetPdw = new CGetPdw( "tGetPdw" );
	if( theGetPdw == NULL ) {
		PrintErr( ( "\n [W] 메모리 부족입니다. CGetPdw 객체를 생성할 수 없습니다 !" ) );
	}

	theSigAnal = new CSigAnal( "tSigAnl" );
	if( theSigAnal == NULL ) {
		PrintErr( ( "\n [W] 메모리 부족입니다. CSigAnal 객체를 생성할 수 없습니다 !" ) );
	}

	theTcpIpServer = new CTcpIpServer( "tTcpSrv" );
	if( theTcpIpServer == NULL ) {
		PrintErr( ( "\n [W] 메모리 부족입니다. CTcpIpServer 객체를 생성할 수 없습니다 !" ) );
	}

	theManAet = new CManAet( "tManAet", sizeof(STR_QUEUE_AET_MESSAGE) );
	if( theManAet == NULL ) {
		PrintErr( ( "\n [W] 메모리 부족입니다. CManAet 객체를 생성할 수 없습니다 !" ) );
	}

	theGrDisp = new CGrDisp( "tGrDisp" );
	if( theGrDisp == NULL ) {
		PrintErr( ( "\n [W] 메모리 부족입니다. CGrDisp 객체를 생성할 수 없습니다 !" ) );
	}

	theCtrlCMDS = new CCtrlCMDS( "tCtlCMD", sizeof(STR_QUEUE_LOG_MESSAGE), 100 );
	if( theCtrlCMDS == NULL ) {
		PrintErr( ( "\n [W] 메모리 부족입니다. CCtrlCMDS 객체를 생성할 수 없습니다 !" ) );
	}

	theRT1553 = new CRT1553( "tRT1553" );
	if( theRT1553 == NULL ) {
		PrintErr( ( "\n [W] 메모리 부족입니다. CRT1553 객체를 생성할 수 없습니다 !" ) );
	}

	theAliveMark = new CAliveMark( "tAlveMk" );
	if( theAliveMark == NULL ) {
		PrintErr( ( "\n [W] 메모리 부족입니다. CAliveMark 객체를 생성할 수 없습니다 !" ) );
	}

	/*
	폴링 방식의 키 입력을 수행하게 한다.
	thePollKey = new CPollKey( "tPolKey" );
	if( thePollKey == NULL ) {
		PrintErr( ( "\n [W] 메모리 부족입니다. CPollKey 객체를 생성할 수 없습니다 !" ) );
	}
	*/

#endif

	printf( "end." );

}



//////////////////////////////////////////////////////////////////////////
/*! \brief    기본적으로 생성할 타스크들을 생성한다. 기본적인 우선순의는 main() 보다 커야 한다.
		\author   조철희
		\return   void
		\version  0.0.1
		\date     2008-04-25 20:35:24
		\warning
*/
void InitTasks()
{
	printf( "\n*Create the all tasks..." );

#ifndef _WIN32
	theRecvSerial->TaskSpawn( "tRcvSer", tPRI_RECVSERIAL, VX_STDIO|VX_SUPERVISOR_MODE, 64000 );
	theSendSerial->TaskSpawn( "tSndSer", tPRI_SENDSERIAL, VX_STDIO|VX_SUPERVISOR_MODE, 64000 );
	theRunBit->TaskSpawn( "tRunBit", tPRI_RUNBIT, VX_STDIO|VX_SUPERVISOR_MODE, 64000 );
	theManTsk->TaskSpawn( "tManTsk", tPRI_MANTSK, VX_STDIO|VX_SUPERVISOR_MODE, 64000 );
	theGetPdw->TaskSpawn( "tGetPdw", tPRI_GETPDW, VX_STDIO|VX_SUPERVISOR_MODE, 64000 );
	theSigAnal->TaskSpawn( "tSigAnl", tPRI_SIGANAL, VX_STDIO|VX_SUPERVISOR_MODE, 64000 );
	theManAet->TaskSpawn( "tManAet", tPRI_MANAET, VX_STDIO|VX_SUPERVISOR_MODE, 64000 );
	theGrDisp->TaskSpawn( "tGrDisp", tPRI_GRDISP, VX_STDIO|VX_SUPERVISOR_MODE, 64000 );
	theCtrlCMDS->TaskSpawn( "tCtlCMD", tPRI_CTRLCMDS, VX_STDIO|VX_SUPERVISOR_MODE, 64000 );
	theRT1553->TaskSpawn( "tRT1553", tPRI_RT1553, VX_STDIO|VX_SUPERVISOR_MODE, 64000 );
	theAliveMark->TaskSpawn( "tAlveMk", tPRI_POLLKEY, VX_STDIO|VX_SUPERVISOR_MODE, 64000 );

	// thePollKey->TaskSpawn( "tPolKey", tPRI_POLLKEY, VX_STDIO|VX_SUPERVISOR_MODE, 64000 );
	// theLogDebug->TaskSpawn( "tLgDbg", tPRI_LOGDEBUG, VX_STDIO|VX_SUPERVISOR_MODE, 64000 );

	theTcpIpServer->TaskSpawn( "tTcpSrv", tPRI_TCPSRV, VX_STDIO|VX_SUPERVISOR_MODE, 64000 );

#endif

	printf( "end." );

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    InitUnits
		\author   조철희
		\return   void
		\version  0.0.1
		\date     2008-05-01 11:51:12
		\warning
*/
void InitUnits()
{
	//char *pEnviron;

	//putenv( "TIMEZONE=korea::540:123102:123101" );
	//pEnviron = getenv( "TIMEZONE" );
	//printf( "\n TIMEZONE=%s" , pEnviron );

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    HookSoftwareReset
		\author   조철희
		\return   void
		\version  0.0.59
		\date     2008-11-19 14:55:26
		\warning
*/
void HookSoftwareReset()
{

	printf( "\n Hook Key..." );

#ifndef _WIN32
	int status;
	int stdinFd;

	stdinFd = ioTaskStdGet( 0, 0 );
	status = ioctl( stdinFd, FIOPROTOHOOK, (int) CHookKeyHandler );
	if( status == ERROR ) {
		printf( "\n ioctl error !" );
	}

	status = ioctl( stdinFd, FIOPROTOARG, 1 );
	if( status == ERROR ) {
		printf( "\n ioctl error !" );
	}
#endif

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CHookKeyHandler
		\author   조철희
		\return   BOOL
		\version  1.00
		\date     2007-10-25 14:01:42
		\warning
*/
unsigned int CHookKeyHandler( int i, int ch )
{

	// printf( "\n ch[%d]" , ch );

	if( ch == CTRL_Z ) {
		// printf( "\n Toggle of Log Print..." );
		theLogDebug->LogToggleDebugPrint();
		return FALSE;
	}
	else if( ch == CTRL_X ) {
		theManTsk->SoftReset();
		return FALSE;
	}

	return FALSE;

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    초기자체점검을 실시한다.
		\author   조철희
		\return   void
		\version  0.0.1
		\date     2008-04-30 17:10:48
		\warning
*/
void RequestIBit()
{
	theManTsk->RequestIBit();

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    RequestCBit
		\author   조철희
		\return   void
		\version  0.0.59
		\date     2008-11-20 17:27:12
		\warning
*/
void RequestCBit()
{
	theManTsk->RequestCBit();

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    RequestInit
		\author   조철희
		\return   void
		\version  0.0.24
		\date     2008-05-09 22:04:14
		\warning
*/
void RequestInit()
{
	theManTsk->RequestInit();

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    StartMainAnal
		\author   조철희
		\return   void
		\version  0.0.26
		\date     2008-06-05 18:22:36
		\warning
*/
void StartMainAnal()
{
	theManTsk->StartAnal();
	theManTsk->SetupCBit();

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    SetupCBit
		\author   조철희
		\return   void
		\version  0.0.35
		\date     2008-08-12 14:15:13
		\warning
*/
void SetupCBit()
{
	theManTsk->SetupCBit();

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    RequestToHoldAnal
		\author   조철희
		\return   void
		\version  0.0.30
		\date     2008-07-12 19:21:03
		\warning
*/
void RequestToHoldAnal()
{
	theManTsk->RequestToHoldAnal();

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    StartServer
		\author   조철희
		\return   void
		\version  0.0.28
		\date     2008-06-23 16:26:40
		\warning
*/
void StartServer()
{
	STR_QUEUE_MESSAGE interQMsg;

	interQMsg.opCode = REQ_START_SERVER;	
	theTcpIpServer->SendMessage( & interQMsg );

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    PrintScreenBuffer
		\author   조철희
		\return   void
		\version  0.0.71
		\date     2009-01-30 09:49:04
		\warning
*/
void PrintScreenBuffer()
{
	theLogDebug->PrintScreenBuffer();

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    LogOn
		\author   조철희
		\return   void
		\version  0.0.73
		\date     2009-04-02 17:35:43
		\warning
*/
void LogOn()
{
	theLogDebug->LogOnDebugPrint();

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    LogOff
		\author   조철희
		\return   void
		\version  0.0.73
		\date     2009-04-02 17:35:45
		\warning
*/
void LogOff()
{
	theLogDebug->LogOffDebugPrint();

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    pb
		\author   조철희
		\return   void
		\version  0.0.30
		\date     2008-07-14 10:17:05
		\warning
*/
void pb()
{
	STR_QUEUE_MESSAGE qMsg;

	Printf( "\n Process the Pilot BIT..." );
	
	qMsg.opCode = REQ_USER_PBIT;
	theRunBit->SendMessage( & qMsg );
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    cb
		\author   조철희
		\return   void
		\version  0.0.30
		\date     2008-07-14 10:16:58
		\warning
*/
void cb()
{
	STR_QUEUE_MESSAGE qMsg;

	Printf( "\n Process the Continuous BIT..." );
	
	qMsg.opCode = REQ_USER_PBIT;
	theRunBit->SendMessage( & qMsg );

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    bp
		\author   조철희
		\return   void
		\version  0.0.30
		\date     2008-07-14 13:33:03
		\warning
*/
void bp()
{
	STR_QUEUE_MESSAGE qMsg;

	Printf( "\n Process the Backup pdw files..." );
	printf( "\n Process the Backup pdw files..." );
	
	qMsg.opCode = REQ_BACKUP_PDW;
	theGetPdw->SendMessage( & qMsg );	

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    rp
		\author   조철희
		\return   void
		\version  0.0.50
		\date     2008-10-09 12:56:37
		\warning
*/
void rp()
{
	theGrDisp->StartSavingPDW();

}


//////////////////////////////////////////////////////////////////////////
/*! \brief    bpp
		\author   조철희
		\return   void
		\version  0.0.30
		\date     2008-07-14 18:16:52
		\warning
*/
void bpp()
{

	Printf( "\n Process the Backup pdw files..." );
	theGetPdw->BackupPDWFiles();
}

void test()
{

	theCtrlCMDS->SetAudioConfig( AUDIO_ON, SHORT_TONE );

#ifndef _WIN32
	//taskSpawn( "t1", 81+0, 0, 50000, (FUNCPTR) t1, 0,0,0,0,0,0,0,0,0,0 );
	//taskSpawn( "t2", 81+0, 0, 50000, (FUNCPTR) t2, 0,0,0,0,0,0,0,0,0,0 );
	//taskSpawn( "t3", 81+0, 0, 50000, (FUNCPTR) t3, 0,0,0,0,0,0,0,0,0,0 );
#endif

}

void t1()
{
#ifndef _WIN32
	for( ;; ) {
		theGrDisp->RequestPowerOnIBit();
		theCtrlCMDS->RequestPowerOnIBit();
		theGetPdw->RequestPowerOnIBit1();

	}
#endif


}

void t2()
{
#ifndef _WIN32
	for( ;; ) {
		theGrDisp->RequestPowerOnIBit();
		theCtrlCMDS->RequestPowerOnIBit();
		theGetPdw->RequestPowerOnIBit1();

	}
#endif


}

void t3()
{
#ifndef _WIN32
	for( ;; ) {
		theGrDisp->RequestPowerOnIBit();
		theCtrlCMDS->RequestPowerOnIBit();
		theGetPdw->RequestPowerOnIBit1();

	}
#endif

}


#ifndef _WIN32
void t()
{
	//MEMORY_BANK bank;
	//int count;

	// theGetPdw->intHandlerCollect();

	//theGenPulseInfo->GetCollectingCount(  (enum MEMORY_BANK)1, & bank, & count );
	//Printf( "\n bank[%d], count[%d]" , bank, count );

	for( ;; ) {
		int i;

		Printf( "\n[]" );
		theSendSerial->MakeRequestInitMessage();
		for( i=0 ; i < TOTAL_RECEIVER ; ++i ) {
			theSendSerial->SendAllSerial( i, 10 );
		}
		taskDelay( OS_ONE_SEC );

		theSendSerial->MakeRequestIBitMessage();
		for( i=0 ; i < TOTAL_RECEIVER ; ++i ) {
			theSendSerial->SendAllSerial( i, 10 );
		}

		taskDelay( (int)( 50*OS_ONE_MILLISEC ) );

		// IBIT 결과 요구 메시지를 전송합니다.
		theSendSerial->MakeRequestIBitResultMessage();
		for( i=0 ; i < TOTAL_RECEIVER ; ++i ) {
			theSendSerial->SendAllSerial( i, 10 );
		}
	}

	/*
	theCtrlCMDS->theLinkAircraft->DeleteLog( NORMAL_DELETE );

	for( ;; ) {
		theCtrlCMDS->theLinkAircraft->SetAudioConfig( AUDIO_ON, ALTER_TONE );
		taskDelay( 1L );
		theCtrlCMDS->theLinkAircraft->SetAudioConfig( AUDIO_ON, CONTI_TONE );
		taskDelay( 1L );
		theCtrlCMDS->theLinkAircraft->SetAudioConfig( AUDIO_ON, SHORT_TONE );
		taskDelay( 1L );
	}
	*/

}
#endif

void debug()
{
	printf( "\n*Debug..." );

/*
	UNI_GP_THREAT_IDINFO threat_idinfo;

	//theGrDisp->theGraphicProcessor->RequestPowerOnInit();
	//theGrDisp->theGraphicProcessor->DispFaultCategory( OVERHEAT );
	//theGrDisp->theGraphicProcessor->DispFaultCategory( OVERHEAT );

	threat_idinfo.word = 0;
	threat_idinfo.x.nX = 128;
	threat_idinfo.x.nY = 128;
	threat_idinfo.x.nSymbol = 'X';
	theGrDisp->theGraphicProcessor->DispThreatIdInfo( 0, & threat_idinfo );

	threat_idinfo.x.nX = 0;
	threat_idinfo.x.nY = 128;
	theGrDisp->theGraphicProcessor->DispThreatIdInfo( 1, & threat_idinfo );

	threat_idinfo.x.nX = 255;
	threat_idinfo.x.nY = 128;
	theGrDisp->theGraphicProcessor->DispThreatIdInfo( 2, & threat_idinfo );

	threat_idinfo.x.nX = 128;
	threat_idinfo.x.nY = 0;
	theGrDisp->theGraphicProcessor->DispThreatIdInfo( 3, & threat_idinfo );

	threat_idinfo.x.nX = 128;
	threat_idinfo.x.nY = 255;
	theGrDisp->theGraphicProcessor->DispThreatIdInfo( 4, & threat_idinfo );
*/
	

	STR_QUEUE_MESSAGE interQMsg;
	interQMsg.opCode = REQ_FIRE;
	theCtrlCMDS->SendMessage( & interQMsg );

	// UINT word;
	// word = 0x01;
	// BusWrite32( LA_REQ_INIT, word );

	// BusRead32( LA_GET_CMDS, & word );
	// printf( "\n word[%x]" , word );

}



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CManTsk::CManTsk( char *pTaskName )
{
	strcpy( m_taskName, pTaskName );

	MallocBuffer();

	InitTask();
	InitVar();

}

CManTsk::~CManTsk()
{
	int i;

	// 채널 보정 데이터 버퍼를 할당한다.
	for( i=0 ; i < TOTAL_RECEIVER ; ++i ) {
		free( stPowerOnInit.hf_channel[i].pChannelCompensation );
	}
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CManTsk::InitVar
		\author   조철희
		\return   void
		\version  0.0.24
		\date     2008-05-13 19:39:46
		\warning
*/
void CManTsk::InitVar()
{
	// SetWarmUpFlag( TRUE );

	// ClearPowerOnInitVar();
	// theGrDisp->theGraphicProcessor->DispFaultCategory( SYSTEM_OK );

}


//////////////////////////////////////////////////////////////////////////
/*! \brief    CManTsk::InitTask
		\author   조철희
		\return   void
		\version  0.0.26
		\date     2008-05-28 14:42:05
		\warning
*/
void CManTsk::InitTask()
{


}


//////////////////////////////////////////////////////////////////////////
/*! \brief    CManTsk::MallocBuffer
		\author   조철희
		\return   void
		\version  0.0.26
		\date     2008-05-28 13:39:38
		\warning
*/
void CManTsk::MallocBuffer()
{
	int i;

	// 채널 보정 데이터 버퍼를 할당한다.
	for( i=0 ; i < TOTAL_RECEIVER ; ++i ) {
		stPowerOnInit.hf_channel[i].pChannelCompensation = (UINT *) malloc( MAX_SIZE_CHNNELCOMPENSATION * sizeof(UINT) );
		if( stPowerOnInit.hf_channel[i].pChannelCompensation == NULL ) {
			PrintErr( ( "\n [W] %d번 수신기의 채널 보정용 버퍼를 할당하지 못했습니다 !" , i+1 ) );
		}
	}

}


//////////////////////////////////////////////////////////////////////////
/*! \brief    CManTsk::Run
		\author   조철희
		\return   void
		\version  0.0.1
		\date     2008-04-25 20:39:30
		\warning
*/
void CManTsk::Run()
{

	for(;;) {
		ReceiveMessage();
		if( TRUE == ParseMessage() ) {
			// DisplayResult();
		}

	}

	return;

}


//////////////////////////////////////////////////////////////////////////
/*! \brief    CManTsk::RequestIBit
		\author   조철희
		\return   void
		\version  0.0.1
		\date     2008-04-30 17:11:14
		\warning
*/
void CManTsk::RequestIBit()
{
	STR_QUEUE_MESSAGE qMsg;
	
	qMsg.opCode = REQ_POWER_ON_IBIT;
	SendMessage( & qMsg );

}

void CManTsk::RequestCBit()
{
	STR_QUEUE_MESSAGE qMsg;
	
	qMsg.opCode = REQ_SELF_CBIT;
	theRunBit->SendMessage( & qMsg );
WhereIs;
}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CManTsk::RequestInit
		\author   조철희
		\return   void
		\version  0.0.1
		\date     2008-05-09 18:53:19
		\warning
*/
void CManTsk::RequestInit()
{
	STR_QUEUE_MESSAGE qMsg;

	qMsg.opCode = REQ_POWER_ON_INIT;
	SendMessage( & qMsg );

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CManTsk::StartAnal
		\author   조철희
		\return   void
		\version  0.0.26
		\date     2008-05-27 11:30:22
		\warning
*/
void CManTsk::StartAnal()
{
	STR_QUEUE_MESSAGE qMsg;

	qMsg.opCode = REQ_START_ANAL;
	SendMessage( & qMsg );

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CManTsk::SetupCBit
		\author   조철희
		\return   void
		\version  0.0.33
		\date     2008-07-23 03:53:33
		\warning
*/
void CManTsk::SetupCBit()
{
	STR_QUEUE_MESSAGE qMsg;
	
	qMsg.opCode = REQ_SETUP_CBIT;
	SendMessage( & qMsg );

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CManTsk::RequestToHoldAnal
		\author   조철희
		\return   void
		\version  0.0.30
		\date     2008-07-12 19:21:52
		\warning
*/
void CManTsk::RequestToHoldAnal()
{
	STR_QUEUE_MESSAGE qMsg;
	
	qMsg.opCode = REQ_HOLD_ANAL;
	SendMessage( & qMsg );

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CManTsk::ParseMessage
		\author   조철희
		\return   BOOL
		\version  0.0.1
		\date     2008-05-01 11:33:30
		\warning
*/
BOOL CManTsk::ParseMessage()
{
	STR_QUEUE_MESSAGE *pQMsg;
	STR_QUEUE_MESSAGE interQMsg;

	pQMsg = ( STR_QUEUE_MESSAGE * ) GetQueueMessage();

	switch( pQMsg->opCode ) {
		// 장비 초기화를 위한 처리를 한다.
		case REQ_POWER_ON_INIT :
			InitVar();

			ClearPowerOnInitVar();
			theRunBit->SendMessage( pQMsg );

			theGrDisp->StartWarmUpMessage();

			// 초단수신기로 채널 보정 데이터를 요구한다.
			//RequestUploadChannelData();
			WaitEchoMessage( WAIT_FOREVER  );

			interQMsg.opCode = DISPLAY_CU_INFO;
			interQMsg.opData = REQ_POWER_ON_INIT;
			//theGrDisp->SendMessage( & interQMsg );
			break;

		case REQ_USER_PBIT :
			theRunBit->SendMessage( pQMsg );
			break;

		// 초기 자체 점검 및 운용자 자체 점검을 요청한다.
		case REQ_POWER_ON_IBIT :
			theRunBit->SendMessage( pQMsg );
			WaitEchoMessage( WAIT_FOREVER  );

			// 그래픽 처리판으로 자체점검 결과 전송한다.
			interQMsg.opCode = DISPLAY_CU_INFO;
			interQMsg.opData = pQMsg->opCode;
			theGrDisp->SendMessage( & interQMsg );
			break;

		case REQ_START_ANAL :
			// IBIT 결과와 Warm-Up 메시지 출력할 때까지 대기한다.
#ifndef _WIN32
			// taskDelay( 3*OS_ONE_SEC );
#endif

			theGrDisp->EndWarmUpMessage();

#ifndef _A50_DEMO_
			ReqStartAnal();
#endif
			break;

		case REQ_HOLD_ANAL :
			ReqHoldAnal();
			break;

		case REQ_STOP_ANAL :
			ReqStopAnal();
			break;

		case REQ_KEY_PFM :
			// 분석 초기화
			ReqStopAnal();

			// 화면을 표시한다.
			//interQMsg.opCode = DISPLAY_CU_INFO;
			//interQMsg.opData = DISP_PFM;
			//theGrDisp->SendMessage( & interQMsg );

			StartMainAnal();
			break;

		case REQ_SETUP_CBIT :
			theRunBit->SendMessage( pQMsg );
			break;

		case REQ_ZERORIZE :
			Zerorize();
			break;

		case REQ_DOWNLOAD_UDF :
			DownloadUDF();
			break;

		case REQ_RELOAD_UDF :
			printf( "\n reload udf..." );
#ifndef _WIN32
			theManSbc->CopyToRamdrive( (STR_PRG_INFO *) GET_FLASH_ADRS(UDF1_START_SECTOR), UDF_RAMDISK_FILENAME );
#endif

			ReqStopAnal();
			StartMainAnal();
			break;

		default :
			PrintErr( ( "\n [W] Invalid opcode[%x]" , pQMsg->opCode ) );
			return FALSE;
	}

	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
/*! \brief    CManTsk::ClearPowerOnInitVar
		\author   조철희
		\return   void
		\version  0.0.24
		\date     2008-05-13 19:37:52
		\warning
*/
void CManTsk::ClearPowerOnInitVar()
{
	int i;
	int value;

	// 초단수신기 관련 데이터 초기화
	for( i=0 ; i < TOTAL_RECEIVER ; ++i ) {
		// 초기화 정보는 0xFFFFFFFF 로 함.
		stPowerOnInit.hf_init[i] = _spFail;

		// 초기 버젼 정보는 0xFFFFFFFF 로 함.
		stPowerOnInit.hf_version[i] = _spFail;

		stPowerOnInit.hf_channel[i].count = 0;

		// 초단수신기 온도는 기본 0도로 설정함.
		stPowerOnInit.hf_temperature[i] = 0;
	}

	// 펄스정보생성판 관련 데이터 초기화
	for( i=0 ; i < TOTAL_RECEIVER ; ++i ) {
		// 초기 버젼 정보는 0xFFFFFFFF 로 함.
		stPowerOnInit.pg_version[i] = _spFail;
	}

	value = theIni->ReadInt( "System", "LowBand", INIT_PA_THRESHOLD_BAND1 );
	stPowerOnInit.pg_threshold2[F_BAND1].x.pa_threshold = DB( value ); // DB( INIT_PA_THRESHOLD_BAND1 );
	stPowerOnInit.pg_threshold2[F_BAND1].x.cw_chopping_count = INIT_CW_CHOPPING_COUNT;
	stPowerOnInit.pg_threshold2[F_BAND1].x.fmop_threshold = FMOP( INIT_FMOP_THRESHOLD );
	stPowerOnInit.pg_threshold2[F_BAND1].x.cw_pulsewidth = CW( INIT_CW_PULSEWIDTH );

	value = theIni->ReadInt( "System", "HighBand1", INIT_PA_THRESHOLD_BAND2 );
	stPowerOnInit.pg_threshold2[F_BAND2].x.pa_threshold = DB( value ); // DB( INIT_PA_THRESHOLD_BAND2 );
	stPowerOnInit.pg_threshold2[F_BAND2].x.cw_chopping_count = INIT_CW_CHOPPING_COUNT;
	stPowerOnInit.pg_threshold2[F_BAND2].x.fmop_threshold = FMOP( INIT_FMOP_THRESHOLD );
	stPowerOnInit.pg_threshold2[F_BAND2].x.cw_pulsewidth = CW( INIT_CW_PULSEWIDTH );

	value = theIni->ReadInt( "System", "HighBand2", INIT_PA_THRESHOLD_BAND3 );
	stPowerOnInit.pg_threshold2[F_BAND3].x.pa_threshold = DB( value ); // DB( INIT_PA_THRESHOLD_BAND3 );
	stPowerOnInit.pg_threshold2[F_BAND3].x.cw_chopping_count = INIT_CW_CHOPPING_COUNT;
	stPowerOnInit.pg_threshold2[F_BAND3].x.fmop_threshold = FMOP( INIT_FMOP_THRESHOLD );
	stPowerOnInit.pg_threshold2[F_BAND3].x.cw_pulsewidth = CW( INIT_CW_PULSEWIDTH );

	value = theIni->ReadInt( "System", "HighBand3", INIT_PA_THRESHOLD_BAND4 );
	stPowerOnInit.pg_threshold2[F_BAND4].x.pa_threshold = DB( value ); // DB( INIT_PA_THRESHOLD_BAND4 );
	stPowerOnInit.pg_threshold2[F_BAND4].x.cw_chopping_count = INIT_CW_CHOPPING_COUNT;
	stPowerOnInit.pg_threshold2[F_BAND4].x.fmop_threshold = FMOP( INIT_FMOP_THRESHOLD );
	stPowerOnInit.pg_threshold2[F_BAND4].x.cw_pulsewidth = CW( INIT_CW_PULSEWIDTH );

	value = theIni->ReadInt( "System", "CDBand", INIT_PA_THRESHOLD_CD_BAND );
	stPowerOnInit.pg_threshold2[CD_BAND].x.pa_threshold = CD_DB( value ); // CD_DB( INIT_PA_THRESHOLD_CD_BAND );
	stPowerOnInit.pg_threshold2[CD_BAND].x.cw_chopping_count = INIT_CW_CHOPPING_COUNT;
	stPowerOnInit.pg_threshold2[CD_BAND].x.fmop_threshold = FMOP( INIT_FMOP_THRESHOLD_CD_BAND );
	stPowerOnInit.pg_threshold2[CD_BAND].x.cw_pulsewidth = CW( INIT_CW_PULSEWIDTH );

	for( i=F_BAND1 ; i <= CD_BAND ; ++i ) {
		printf( "\n Band[%d] Val[%x] Threshold[%x]" , i, stPowerOnInit.pg_threshold2[i].word, stPowerOnInit.pg_threshold2[i].x.pa_threshold );
	}

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CManTsk::RequestUploadChannelData
		\author   조철희
		\return   void
		\version  0.0.24
		\date     2008-05-13 22:43:36
		\warning
*/
void CManTsk::RequestUploadChannelData()
{
	STR_QUEUE_MESSAGE *pQMsg;
	STR_QUEUE_MESSAGE interQMsg;

	pQMsg = ( STR_QUEUE_MESSAGE * ) GetQueueMessage();

	interQMsg.opCode = REQ_CHANEL_COMPENSATION;
	interQMsg.opData = pQMsg->opData;

	theSendSerial->SendMessage( & interQMsg );

	if( FALSE == WaitEchoMessage( MAX_TO_HF_COMM ) ) {
		PrintErr( ( "\n [W] 초단수신기와 연결이 되지 않았습니다. 케이블을 확인해주세요 !" ) );
	}

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CManTsk::ReqStartAnal
		\author   조철희
		\return   void
		\version  0.0.26
		\date     2008-05-27 11:36:25
		\warning
*/
void CManTsk::ReqStartAnal()
{
	STR_QUEUE_MESSAGE *pQMsg;

	printf( "\n ReqStartAnal..." );

	pQMsg = ( STR_QUEUE_MESSAGE * ) GetQueueMessage();

	theGetPdw->SendMessage( pQMsg );
	theGrDisp->SendMessage( pQMsg );
	theCtrlCMDS->SendMessage( pQMsg );

}


//////////////////////////////////////////////////////////////////////////
/*! \brief    CManTsk::ReqSwitchControl
		\author   조철희
		\return   void
		\version  0.0.24
		\date     2008-05-14 15:18:39
		\warning
*/
void CManTsk::ReqSwitchControl()
{
	STR_QUEUE_MESSAGE *pQMsg;

	pQMsg = ( STR_QUEUE_MESSAGE * ) GetQueueMessage();
	theSendSerial->SendMessage( pQMsg );

	if( FALSE == WaitEchoMessage( MAX_TO_HF_COMM ) ) {
		PrintErr( ( "\n [W] 초단수신기와 연결이 되지 않았습니다. 케이블을 확인해주세요 !" ) );
	}

}


//////////////////////////////////////////////////////////////////////////
/*! \brief    CManTsk::ReqHoldAnal
		\author   조철희
		\return   void
		\version  0.0.30
		\date     2008-07-12 19:23:54
		\warning
*/
void CManTsk::ReqHoldAnal()
{
	STR_QUEUE_MESSAGE *pQMsg;

	pQMsg = ( STR_QUEUE_MESSAGE * ) GetQueueMessage();
	theGetPdw->SendMessage( pQMsg );

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CManTsk::ReqStopAnal
		\author   조철희
		\return   void
		\version  0.0.41
		\date     2008-08-24 15:30:10
		\warning
*/
void CManTsk::ReqStopAnal()
{
	STR_QUEUE_MESSAGE *pQMsg;

	// 메시지를 관련 타스크로 전달한다.
	pQMsg = ( STR_QUEUE_MESSAGE * ) GetQueueMessage();

	theGetPdw->SendMessageWaitEcho( pQMsg, WAIT_FOREVER );

	theGrDisp->SendMessageWaitEcho( pQMsg, WAIT_FOREVER );

	theRunBit->SendMessageWaitEcho( pQMsg, WAIT_FOREVER );

	theSigAnal->SendMessageWaitEcho( pQMsg, WAIT_FOREVER );

	theManAet->SendMessageWaitEcho( pQMsg, WAIT_FOREVER );

	theCtrlCMDS->SendMessageWaitEcho( pQMsg, WAIT_FOREVER );

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CManTsk::Zerorize
		\author   조철희
		\return   void
		\version  0.0.55
		\date     2008-11-09 09:58:19
		\warning
*/
void CManTsk::Zerorize()
{
#ifndef _WIN32
	int i=0;

	taskLock();

	Printf( "\n Erase all UDF & OFP..." );

	theRecvSerial->Suspend();
	theSendSerial->Suspend();
	theRunBit->Suspend();
	theGetPdw->Suspend();
	theSigAnal->Suspend();
	theManAet->Suspend();
	theGrDisp->Suspend();
	theTcpIpServer->Suspend();
	theAliveMark->Suspend();
	theRT1553->Suspend();
	theCtrlCMDS->Suspend();

	remove( BOOT_TFFS_FILENAME );

	theCtrlCMDS->Zerorize();

	for( ;; ) {
		++ i;
		printf( "@" );

		taskDelay( (int) (1*OS_ONE_SEC) );

		// 화면 깜박임.
		if( i % 2 ) {
			theGrDisp->DispText( VERSION_LOGO_MESSAGE_X, VERSION_LOGO_MESSAGE_Y, "COMPLETE", TRUE, (enum TEXT_SYMBOL_IDX) TEXT_SYMBOL_INDEX );
		}
		else {
			theGrDisp->ClearAllText( TRUE );
		}

	}

	WaitEchoMessage( WAIT_FOREVER  );

#endif

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CManTsk::DownloadUDF
		\author   조철희
		\return   void
		\version  0.0.57
		\date     2008-11-09 15:24:32
		\warning
*/
void CManTsk::DownloadUDF()
{
	STR_QUEUE_MESSAGE interQMsg;

	Printf( "\n\n Download and then write the UDF #1 in the flash rom and ramdrive..." );
#ifndef _WIN32
#ifndef _BOOTSHELL_INCLUDE_
	while( true != theBootShell->DownloadfromTftp( UDF1_FILENAME, UDF_RAMDISK_FILENAME ) ) NanoSleep( 2, 0 );
	theBootShell->WriteIntoFlash( UDF_RAMDISK_FILENAME, UDF_1_Bank );

	remove( UDF_RAMDISK_FILENAME );
#endif
#endif

	interQMsg.opCode = DISP_DOWNLOAD_COMPLETE;
	theGrDisp->SendMessage( & interQMsg );

}



//////////////////////////////////////////////////////////////////////////
/*! \brief    CManTsk::SoftReset
		\author   조철희
		\return   void
		\version  0.0.59
		\date     2008-11-19 15:08:36
		\warning
*/
void CManTsk::SoftReset()
{
	STR_QUEUE_MESSAGE interQMsg;

	theCtrlCMDS->theLinkAircraft->AudioEnable( FALSE );

	interQMsg.opCode = REF_SOFT_RESET;
	theGetPdw->SendMessage( & interQMsg, NO_WAIT );

}