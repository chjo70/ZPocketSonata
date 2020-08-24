/****************************************************************************************
 파 일 명 : ktmng.c
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

#include "ksp.h"
#include "KVar.h"

extern word32      gDMFifoFull;
extern word32      gDMHalfFull;

/****************************************************************************************
 함    수 : TSK_MngTsk
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
TASK
TSK_MngTsk( void ) {
    STR_TSK_MSG     tskMsg;
    STR_TSK_MSG     sndMsg;
    int             errPend;

    UINT            stat;
  //  UINT            bret;
	// UINT			noCh;
	UINT			noEMT;

  //  TASK_TCB          *tcbinfo;

  //  int            info[3];
	int				noLost;
	int i;
 
    for(;;)
    {
        tskMsg.w = (UINT) sc_qpend(SQ_MngTsk, _spNoTimeout, &errPend);
        DISP_TskMsg(&tskMsg, "MngTsk", tskMsg.hd.whcDev);

    	switch(tskMsg.in.opCode) {
			case MprcStop :
          gpSysPrcStat->prc.opr = _resetSW;
          gpSysPrcStat->prc.sys = _spZero;
					DelAnlTskQue();
					DelSysTskQue();

					PRC_Initialize();

					InitOpAnalVar();

					CreSysQueTsk();
					CreAnlQueTsk();
          gpSysPrcStat->prc.opr = _readyAnal;
          gpSysPrcStat->prc.sys = _spZero;

					vDM_ResetFifo();

					/*! \bug  로그 파일을 재시작 하도록 한다.
					    \date 2007-11-12 09:31:03, 조철희
					*/
					// ReMakeLogfile();

			CASE MfifoFull :
					printf( "\n MfifoFull" );
				vDM_ClearFullInterrupt( _spFalse );

				sc_tsuspend( tp_AnlSig, 0, &errPend );

				printf( "\n Collecting[%d]" , gKDMFifoFull );
				ChangeTaskPriority( tp_MngTsk, tp_GthSig );     // send prc
				while( CheckSuspendTask( tp_GthSig ) != TBSSUSP )
					sc_delay( 1L );
        printf( "\n End." );
        ChangeTaskPriority( tp_MngTsk, tp_GthSig );     // send complete

        sc_tresume( tp_GthSig, 0, &errPend );
        sc_tresume( tp_AnlSig, 0, &errPend );

				gKDMFifoFull = _spFalse;

				sndMsg.w32 =_spZero;
				noLost = _spZero;
      	for( i=0 ; i < KSF_noCell ; ++i ) {
					noEMT = GetTrackChtoAet( gnoPrc-prc_KSP1, i );
        	if( noEMT == _spInvAET ) {
						stKPDW[i].count = _spZero;
        	}
        	else {
						if( gpOrgAet[noEMT].noEMT == _spInvAET ) {
							printf( "\n\t Invalid noEMT[%d]" , noEMT );
							WhereIs;
						}
            if( (stat=GetTrackAnalStep( noEMT )) == _spColStep ) {
							++ noLost;
              SetTrackAnalStep( noEMT, _spCotStep );

              sndMsg.in.opCode = MaetUp;		// Lost by Fifofull
              sndMsg.in.opData = noEMT - 1;
							if( gpOrgAet[noEMT].sigType == CW || gpOrgAet[noEMT].sigType == HIGHPRF )
								sndMsg.in.stat1 = _spCW;
							else
								sndMsg.in.stat1 = _spNormal;

							sndMsg.in.stat2 = _spReCol;
              Qpost( SQ_SndPrc, sndMsg );
            	stKPDW[i].count = _spZero;
						}
					}
        }

        sndMsg.in.opCode = MfifoFull;		// Lost by Fifofull
				sndMsg.in.opData = noLost;
        Qpost( SQ_SndPrc, sndMsg );

     		vKSF_InitBoard( pwb_KSF1 + ( gnoPrc - prc_KSP1 ) );

        vDM_ClearFullInterrupt( _spTrue );              // debug
        vDM_ClearHalfInterrupt( _spTrue );

      	vDM_ResetFifo();
				// 수집 버퍼 초기화
        WhereIs;

			CASE MhalfFull :
					printf( "\n MhalfFull" );
					vDM_ClearHalfInterrupt( _spFalse );
					sc_tpriority( tp_GthSig, tp_HGtSig, & errPend );

//					printf( "\n Fifo Half Full" );

/* 					tcbinfo = sc_tinquiry( info, tp_GthSig, &errPend );
					printf( "\n pri[%d]" , info[1] );
					if( info[1] != tp_HGtSig && info[1] != 256 ) {
  						sc_tpriority( tp_GthSig, tp_HGtSig, & errPend );
						printf( "-> err[%x]" , errPend );
						WhereIs;
					} */
			DEFAULT :
                    printf( "\n\t [W] Invalid opCode[%d]" , tskMsg.in.opCode );
					WhereIs;
					break;
		}
	}

}

