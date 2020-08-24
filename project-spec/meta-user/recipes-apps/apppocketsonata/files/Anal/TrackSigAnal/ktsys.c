/****************************************************************************************
 파 일 명 : ktsys.c
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 목    적 : 기본 타스크 생성 및 초기화 처리
 가    정 :
 저 자 명 : 조철희
 변 경 자 :
 변경내용 : (목적)
 변경일시 : 99-06-25 2:59오후
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
 컴파일 일시 :
*****************************************************************************************/

#define _MAIN_

//#include <setjmp.h>

#include "../INC/_define.h"
#include "../INC/_common.h"

#include "KDefine.h"
#include "KStruct.h"

#include "ksp.h"

#include "KVar.h"

#ifndef _VXWORKS_
extern unsigned long sys_unused_high;
extern unsigned long sys_unused_low;
extern unsigned long sys_vrtx_ws_addr;

unsigned long sc_getfree()
{
  return sys_unused_high - sys_unused_low;
}

unsigned long sc_getwsaddr()
{
  return sys_vrtx_ws_addr;
}
#endif

extern word32 gKDMFifoFull;
extern word32 gKDMHalfFull;

extern char _gSetJmp[ _spMaxTaskNum ];    // setjump flag, in _common.h
extern jmp_buf gJmpBuff[ _spMaxTaskNum ];    // CPU reg. for jump, in _common.h

void TestSMMsgQueue();
void ConsoleStandardOut();

//////////////////////////////////////////////////////////////////////
// vxworks 및 tvme8240 보드로 적용하기 위한 수정 작업
#ifdef _VXWORKS_
void MAIN( void )
{
#else
  TASK main( void ) {
#endif
//////////////////////////////////////////////////////////////////////

	int						 err;

#ifdef _LOG_CONSOLE_ENABLE_
	ConsoleStandardOut();
#endif

	ConsoleStandardOut();

  if( (err=BootSBC(prc_KSP1)) != RET_OK ) {                 // SBC Information Init.
      printf( "\n\t[Warning] Fail to initilize of SBC[%d]." , err );
			while( 1 ) { sc_delay( 10000000 ); }
  }

  gpDebug->co = _spZero;

  gpSysPrcStat->prc.opr = _resetSW;
  gpSysPrcStat->prc.sys = _spZero;

  InitOpAnalVar();

  if( (err=MQueueCreate(SQ_MngTsk, _spSysQSize )) != RET_OK ||
      (err=TaskCreate(TSK_MngTsk, tp_MngTsk, tp_MngTsk)) != RET_OK ||
      (err=CreSysQueTsk()) != RET_OK ||
	(err=CreAnlQueTsk()) != RET_OK ) {
          printf( "\n\t [W] Insufficient resource of Create Task (Queue)[%d] !!" , err );
          printf( "\n\t\t Please call the LG Precison, Ltd." );
        WhereIs;
		return;
  }

	CompileRevision();

	LoadSystemParameter();

#ifndef _VXWORKS_
    TaskDelete( tp_Main, 0 );
#endif
		
}

/****************************************************************************************
 함    수 : spawn_main
 목    적 : 
 가    정 :
 저 자 명 : 조철희
 변 경 자 :
 변경내용 : (목적)
 변경일시 : 99-06-25 5:41오후
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
*****************************************************************************************/ 
//////////////////////////////////////////////////////////////////////
// vxworks 및 tvme8240 보드로 적용하기 위한 수정 작업
#ifdef _VXWORKS_
int main( void )
#else
void
spawn_main( void ) 
#endif
//////////////////////////////////////////////////////////////////////
{
    int     errScre;

//////////////////////////////////////////////////////////////////////
// vxworks 및 tvme8240 보드로 적용하기 위한 수정 작업
#ifdef _VXWORKS_
  sc_tcreate( MAIN, tp_Main, tp_Main, &errScre );
	return 0;
#else
  sc_tcreate( main, tp_Main, tp_Main, &errScre );
#endif
//////////////////////////////////////////////////////////////////////

}

/****************************************************************************************
 함    수 : InitOpAnalVar
 목    적 : 
 가    정 :
 저 자 명 : 조철희
 변 경 자 :
 변경내용 : (목적)
 변경일시 : 99-06-25 5:41오후
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
*****************************************************************************************/
void
InitOpAnalVar(void) {

  memset( &_gSetJmp, 0, sizeof( _gSetJmp ) );
  memset( &gJmpBuff, 0, sizeof( gJmpBuff ) );

  gpSysRunStat->rCoLivePrc = 1;
  gSysRsaStat.bLivePrc[ 1 ] = gNameOfPrc[ prc_CIP ];

  gpOrgAet = ( STR_AET * ) ( ahwVME_CMS + aCIP_BasAET );
  gpComAet = ( STR_COMAET * ) ( ahwVME_CMS + aCIP_ComAET );

  //gpNewAet = & GnEWAet;
  pQueNew = pQueAetAddr[ gnoPrc ];

  gKDMFifoFull = gKDMHalfFull = _spFalse;
  vDM_ClearFullInterrupt( _spTrue );              // debug
  vDM_ClearHalfInterrupt( _spTrue );

  //  CMS_InitMemory( ahwVME_CMS+aTrkChn2AET, sizeof( UINT ) * (_spCoKSP * KSF_noCell), 0 );

  InitColVar();

} 

/****************************************************************************************
 함    수 : CreAnlTsk
 목    적 :
 가    정 :
 저 자 명 : 조철희
 변 경 자 :
 변경내용 : (목적)
 변경일시 : 99-06-25 5:41오후
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
*****************************************************************************************/
UINT
CreAnlTsk(void) {
    int     err;
 
    err=TaskCreate(TSK_AnlSig, tp_AnlSig, tp_AnlSig);
    err=TaskCreate(TSK_GthSig, tp_GthSig, tp_GthSig);
 
    return err;

}

/****************************************************************************************
 함    수 : DelAnlTsk
 목    적 :
 가    정 :
 저 자 명 : 조철희
 변 경 자 :
 변경내용 : (목적)
 변경일시 : 99-06-25 5:41오후
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
*****************************************************************************************/
UINT
DelAnlTsk(void) {
    int     err;
 
    err=TaskDelete(tp_GthSig, 0);
    err=TaskDelete(tp_AnlSig, 0);
 
    return err;
 
}

/****************************************************************************************
 함    수 : CreAnlQue
 목    적 :
 가    정 :
 저 자 명 : 조철희
 변 경 자 :
 변경내용 : (목적)
 변경일시 : 99-06-25 5:41오후
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
*****************************************************************************************/
UINT
CreAnlQue(void) {
    int     err;
 
    err=MQueueCreate(SQ_AnlSig, _spSysQSize );
 
    return err;
 
}

/****************************************************************************************
 함    수 : DelAnlQue
 목    적 :
 가    정 :
 저 자 명 : 조철희
 변 경 자 :
 변경내용 : (목적)
 변경일시 : 99-06-25 5:41오후
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
*****************************************************************************************/
UINT
DelAnlQue(void) {
    int     err;
 
    err=MQueueDelete(SQ_AnlSig, 0 );
 
    return err;
 
}

/////////////////////////////////////////////////////////////////////////////////////////
//		Dummy function for common function
//
TASK TSK_RcvSIO(void) { }
TASK TSK_SndSIO(void) { }
 
void EFG_create(void) { }
void SIO_Connect(void) { }
void SIO_CloseDesc(int nport) { }
void MsysError( UINT opcode, UINT opdata ) { }
BOOL CheckFlashROMIPL( void ) { return true; }
 
BOOL RS422_Bit(void) { return RET_OK; }
UINT EFG_delete(void) { return RET_OK; }

void LoadSBitAet( void ) {  }
BOOL NewTrackWinCellforSBit( void ) { return true; }
BOOL CompMergeAet( STR_NEWAET *pat ) { return true; }
void FLT_CheckSysInit( void ) { }

void ScControl( STR_AET *pAet, STR_TSK_MSG tskMsg ) { }
int QueueSIODelete( STR_QUEUE_SIO *pQueue ) { return 0; }
UINT RC_UrBit( void ) { return true; }
void SetRxdfMode( UINT band, UINT val ) { }
void DISP_TrueFalse( bool valBool, char *str ) { }

void _Debug_GetPdw( UINT noPrc ){ }

#ifdef _VXWORKS_

//////////////////////////////////////////////////////////////////////
//

#include <msgQSmLib.h>
#include <msgQLib.h>
#include <smMemLib.h>
#include <smObjLib.h>

MSG_Q_ID smRequestQId[10];

TASK RcvPRC( void ) 
{ 
	int i;
	MSG_Q_ID smReceiveQId;  /* request shared message queue */ 
	REQUEST_MSG request;       /* request text */ 

	char dbname[100];

	printf( "\n Init the SrvPRC..." );

	/* create a shared message queue to handle requests */ 
	if( ( smReceiveQId = msgQSmCreate( _spMaxQueueNum, sizeof(REQUEST_MSG), MSG_Q_FIFO ) ) == NULL ) {
		WhereIs;
		return;
	}
	printf( "\n smReceiveQId[%p]" , smRequestQId );

	/* add newly created request message queue to name database */
	
	// printf( "%s" , dbname );
	for( i=prc_SAP ; i <= prc_KSP4 ; ++i ) {
		sprintf( dbname, "RcvREQ%d" , i );
		WhereIs;
		if( smNameAdd( dbname, smReceiveQId /* (void *) smObjLocalToGlobal(pSharedBuff) */ , T_SM_MSG_Q ) == ERROR ) {
			WhereIs;
			return;
		}
	}

	printf( "\n Ready for Receiving..." );
	for(;;) {
		if( msgQReceive( smReceiveQId, (char *) & request, sizeof (REQUEST_MSG), WAIT_FOREVER ) == ERROR ) {
			WhereIs;
		}

    if( msgQSend( request.replyQId, (char *) & request, sizeof (REQUEST_MSG), WAIT_FOREVER, MSG_PRI_NORMAL) == ERROR ) {
			printf( "\n [W] Sending error !" );
			WhereIs;
		}

		printf( "\n Received the following message: %x, source[%d]", request.tskMsg.w32, request.tskMsg.in.source ); 
	}

}

TASK SndPRC( void )
{
	MSG_Q_ID smRequestQId; /* request message queue */ 
	MSG_Q_ID smReplyQId;   /* reply message queue */ 
	REQUEST_MSG request;      /* request text */ 
	int objType;      /* dummy variable for smNameFind */ 

	char dbname[100];

	taskDelay( 100L );

	sprintf( dbname, "RcvREQ%d" , sysProcNumGet() );
	WhereIs;
	/* get request queue ID using its name */
	if( smNameFind( dbname, (void **) & smRequestQId, & objType, WAIT_FOREVER ) == ERROR ) {
		printf( "\n Error of the finding name in database !" );
		WhereIs;
	}

	printf( "\n smRequestQId[%p]", smRequestQId );

	/* create reply queue, build request and send it to server */ 
	if ((smReplyQId = msgQSmCreate( _spMaxQueueNum, sizeof(REQUEST_MSG), MSG_Q_FIFO) ) == NULL ) {
		WhereIs;
		return;
	}

WhereIs;
	for( ; ; ) {
		printf( "\n Send message..." );
 
    request.replyQId = (MSG_Q_ID) htonl ((int) smReplyQId);

		request.tskMsg.w32 = 0x0123456;
		request.tskMsg.in.source = sysProcNumGet();
 
    if( msgQSend( smRequestQId, (char *) & request, sizeof (REQUEST_MSG), WAIT_FOREVER, MSG_PRI_NORMAL) == ERROR ) {
			printf( "\n [W] Sending error !" );
			WhereIs;
		}

		if( msgQReceive( smReplyQId, (char *) & request, sizeof (REQUEST_MSG), WAIT_FOREVER ) == ERROR ) {
			WhereIs;
		}
	}
	
}

void TestSMMsgQueue()
{
	// 메일박스 테스트
	if( gnoPrc == prc_CIP ) {
		taskSpawn( "tRcvPrc", 101, 0, 64000, (FUNCPTR) RcvPRC, 0,0,0,0,0,0,0,0,0,0 );

	}
	else {
		taskSpawn( "tSndPrc", 101, 0, 64000, (FUNCPTR) SndPRC, 0,0,0,0,0,0,0,0,0,0 );

	}
}

#endif


void DMTest() {
	int i;

	printf( "\n vDM_MakeBitData..." );
	for( i=0 ; i < 600*16*4 ; ++i )
		vDM_MakeBitData();
	printf( "\n End..." );

}