/****************************************************************************************
 파 일 명 : ktsig.c
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 목    적 : 타스크 관리
 가    정 :
 저 자 명 : 조철희
 변 경 자 :
 변경내용 : (목적)
 변경일시 : 99-06-25 3:51오후
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
 컴파일 일시 :
*****************************************************************************************/

#include <math.h>

#include "ksp.h"
#include "KVar.h"

#define     _spTotAet       20

extern UINT                           coSimAet;

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : TSK_AnlSig
// 반환되는 형  : TASK
// 함 수 인 자  : void
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-17 13:04:03
//
TASK TSK_AnlSig( void )
{
	STR_TSK_MSG tskMsg;

  int err;

	UINT stAnal;
	UINT noEMT;

  for(;;) {
    tskMsg.w = (UINT) sc_qpend(SQ_AnlSig, _spNoTimeout, &err);
    DISP_TskMsg(&tskMsg, "AnlSig", tskMsg.hd.whcDev);

		stNoCh = tskMsg.in.opData;
   	noEMT = GetTrackChtoAet( gnoPrc-prc_KSP1, tskMsg.in.opData );
		if( (stAnal=GetTrackAnalStep( noEMT )) == _spAnlStep ) {
			GetTrkAetInCommon( & stTrkAet, noEMT );
			if( stTrkAet.aet.noEMT == _spZero || stTrkAet.aet.noEMT == _spInvAET ) {
				printf( "\n\t [W] Invalid Emitter No[%d] !" , stTrkAet.aet.noEMT );
				WhereIs;
			}

			KnownSigAnal( gnoPrc-prc_KSP1, stNoCh );
		}
		else {
			printf( "\n\t [W] Invalid Process[%d] of Track !" , stAnal );
			WhereIs;
		}

	}

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : SendKSPNewAet
// 반환되는 형  : void
// 함 수 인 자  : STR_NEWAET *pAet
// 함 수 인 자  : UINT inEMT
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-17 13:03:55
//
void SendKSPNewAet( STR_NEWAET *pAet, UINT inEMT )
{
	BOOL bret;
	STR_TSK_MSG tskMsg;

	// debug, 03-06-10
	if( pAet[inEMT].aet.frq.max < pAet[inEMT].aet.frq.mean )
		return;
	if( pAet[inEMT].aet.pri.max < pAet[inEMT].aet.pri.mean )
		return;

  gpNewAet = pAet;
  bret = CheckAET( & pAet[inEMT].aet );
  if( bret == _spFalse ) {
      printf( "\n\t [W] Invalid AET !" ); WhereIs;
  }

	if( pAet[inEMT].aet.as.stat != _spUnknown ) {		// debug, 99-12-22 17:40:10
		printf( "\n\t [W] Invalid Scan Stat[%d] !" , pAet[inEMT].aet.as.stat );	WhereIs;
		DISP_FineAet( & pAet[inEMT].aet );
		pAet[inEMT].aet.as.stat = _spUnknown;
	}

	printf( "\n MaetNew*" );

	tskMsg.w32 = MaetNewKSP;
	tskMsg.in.source = gnoPrc;
  tskMsg.in.opData = inEMT;
	tskMsg.in3.stat  = stNoCh;		// debug, 00-09-28 17:14:06
 	Qpost( SQ_SndPrc, tskMsg );

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : SendStatAet
// 반환되는 형  : void
// 함 수 인 자  : STR_UPDAET *pAet
// 함 수 인 자  : UINT stat
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-17 13:03:46
//
void SendStatAet( STR_UPDAET *pAet, UINT stat )
{
  STR_TSK_MSG tskMsg;
	BOOL bret;

	if( pAet->aet.noEMT == _spZero || pAet->aet.noEMT > _spMaxEMTNum ) {            // if buufer full, manage exception ...
   	printf( "\n\t [W] Invalid of Upd AET[%d,%p] !" , pAet->aet.noEMT, pAet );
   	WhereIs;
		DISP_FineAet( & pAet->aet );
		return;
	}

 	tskMsg.w32 = _spZero;
	tskMsg.in.opCode = MaetUp;
	tskMsg.in.opData = pAet->aet.noEMT - 1;

	if( pAet->aet.sigType == CW || pAet->aet.sigType == HIGHPRF )
   	tskMsg.in.stat1 = _spCW;
	else
   	tskMsg.in.stat1 = _spNormal;

 	tskMsg.in.stat2 = stat;

 	gpUpdAet = pAet;

	if( stat == _spAnalSuc ) {
  	bret = CheckAET( & pAet->aet );
  	if( bret == _spFalse ) {
			printf( "\n\t [W] Invalid AET !" );	WhereIs;
    }
    SortSwitchVal( & pAet->aet.frq.swtVal[0], pAet->aet.frq.swtLev );
  	SortSwitchVal( & pAet->aet.pri.swtVal[0], pAet->aet.pri.swtLev );

	}

 	SetTrackAnalStep( pAet->aet.noEMT, _spCotStep );
 	Qpost( SQ_SndPrc, tskMsg );
	if( stat == _spAnalSuc ) {
		// DISP_FineAet( & pAet->aet );
	}
	else {
		printf( "\n Lost[%d] !" , pAet->aet.noEMT );
	}

}	

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : SendKSPUpdAet
// 반환되는 형  : void
// 함 수 인 자  : STR_UPDAET *pAet
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-26 10:58:28
//
void SendKSPUpdAet( STR_UPDAET *pAet )
{
  STR_TSK_MSG tskMsg;
	BOOL bret;

	if( pAet->aet.noEMT == _spZero || pAet->aet.noEMT > _spMaxEMTNum ) {            // if buufer full, manage exception ...
   	printf( "\n\t [W] Invalid of Upd AET[%d,%p] !" , pAet->aet.noEMT, pAet );
   	WhereIs;
		DISP_FineAet( & pAet->aet );
		return;
	}

 	tskMsg.w32 = _spZero;
	tskMsg.in.opCode = MaetUp;
	tskMsg.in.opData = pAet->aet.noEMT - 1;

	if( pAet->aet.sigType == CW || pAet->aet.sigType == HIGHPRF )
   	tskMsg.in.stat1 = _spCW;
	else
   	tskMsg.in.stat1 = _spNormal;

 	tskMsg.in.stat2 = _spAnalSuc;

 	gpUpdAet = pAet;

	bret = CheckAET( & pAet->aet );
	if( bret == _spFalse ) {
		printf( "\n\t [W] Invalid AET !" );	WhereIs;
  }
  //SortSwitchVal( & pAet->aet.frq.swtVal[0], pAet->aet.frq.swtLev );
	//SortSwitchVal( & pAet->aet.pri.swtVal[0], pAet->aet.pri.swtLev );

	SetTrackAnalStep( pAet->aet.noEMT, _spCotStep );
 	Qpost( SQ_SndPrc, tskMsg );

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : SendKSPLostAet
// 반환되는 형  : void
// 함 수 인 자  : STR_TRKAET *pAet
// 함 수 인 자  : int stat
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-02-17 13:03:37
//
void SendKSPLostAet( STR_TRKAET *pAet, int stat )
{
  STR_TSK_MSG tskMsg;

	if( pAet->aet.noEMT == _spZero || pAet->aet.noEMT > _spMaxEMTNum ) {            // if buufer full, manage exception ...
   	printf( "\n\t [W] Invalid of Upd AET[%d,%p] !" , pAet->aet.noEMT, pAet );
   	WhereIs;
		DISP_FineAet( & pAet->aet );
		return;
	}

 	tskMsg.w32 = _spZero;
	tskMsg.in.opCode = MaetUp;
	tskMsg.in.opData = pAet->aet.noEMT - 1;

	if( pAet->aet.sigType == CW || pAet->aet.sigType == HIGHPRF )
   	tskMsg.in.stat1 = _spCW;
	else
   	tskMsg.in.stat1 = _spNormal;

 	tskMsg.in.stat2 = stat;

 	SetTrackAnalStep( pAet->aet.noEMT, _spCotStep );
 	Qpost( SQ_SndPrc, tskMsg );

}

/****************************************************************************************
 함    수 : SetKSPInfo
 목    적 :
 가    정 :
 저 자 명 : 조철희
 변 경 자 :
 변경내용 : (목적)
 변경일시 : 99-07-10 5:41오후
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
*****************************************************************************************/
void
SetKSPInfo( UINT noEMT ) {
	STR_CHINFTAB			 *pComAetKSP;

	pComAetKSP = & gpComAet[noEMT].ksp;

	if( pComAetKSP->t_update == _spInitTime ) {
		printf( "\n\t [W] Invalid Update Time[%lu] !" , pComAetKSP->t_update );
		WhereIs;

	}

	pComAetKSP->t_update = time(NULL);

}



