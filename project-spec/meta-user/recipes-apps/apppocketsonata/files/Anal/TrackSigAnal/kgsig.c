/****************************************************************************************
 파 일 명 : kgsig.c
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 목    적 : 타스크 관리
 가    정 :
 저 자 명 : 조철희
 변 경 자 :
 변경내용 : (목적)
 변경일시 : 99-06-25 3:51오후
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
 컴파일 일시 :
*****************************************************************************************/

#include "ksp.h"
#include "KVar.h"

extern word32      gDMFifoFull;
extern word32      gDMHalfFull;

void CollectTest( void );

#define	_spColPdw							(50)

#ifdef _CHECKDTOA_
STR_FLAG                       *flg;
STR_CHPDW               gNPdw;

/****************************************************************************************
 함    수 : ReadFifo
 목    적 : 추적 FIFO READ
 가    정 :
 저 자 명 : 조철희
 변 경 자 :
 변경내용 : (목적)
 변경일시 : 99-07-06 5:41오후
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
*****************************************************************************************/
BOOL
ReadFifo( UINT *phase ) {
	USHRT					bperr;

	UINT					bret;

    while( 1 ) {
        if( vDM_FifoEmpty() == _spFalse ) {
            vDM_GetFifo( phase );
            return _spTrue;
        }

        if( vDM_ParityError() == _spTrue ) {
            bret = vDM_ClearPerr();
            ++ flg->kp[gnoPrc-prc_KSP1].noDmPhase;
            printf( "\n\t [W] DM Parity Error occurred [%d] !" , bret );
        }

        vKSF_ReadPerr( pwb_KSF1+(gnoPrc-prc_KSP1), & bperr );
        if( bperr == _spTrue ) {
            bret = vKSF_ClearPerr( pwb_KSF1 + ( gnoPrc - prc_KSP1 ) );
            ++ flg->kp[gnoPrc-prc_KSP1].noFtPhase;
            printf( "\n\t [W] Filter Parity Error occurred [%d] !" , bret );
        }

        if( flg->key == 'Q' ) {
            flg->kp[gnoPrc-prc_KSP1].stat = _spOne;
            WhereIs;
            return _spFalse;
		}
 
    }

}

/****************************************************************************************
 함    수 : ReadOnePdw
 목    적 :
 가    정 :
 저 자 명 : 조철희
 변 경 자 :
 변경내용 : (목적)
 변경일시 : 99-07-12 5:41오후
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
*****************************************************************************************/
UINT
ReadOnePdw( TNEW_PDW *pNewPdw ) {
	BOOL						bret;

    while ( 1 ) {
        do {
            bret = ReadFifo( & pNewPdw->wpdw[_spZero] );
			if( bret == _spFalse )      return -1;

            if( pNewPdw->item.band == 0x3 )
                return _spEndCollect;
            if( pNewPdw->item.phase1 != _spZero ) {
                printf( "\n Phase1 Error[%d] !" , pNewPdw->item.phase1 );
            }

        }
        while( pNewPdw->item.phase1 != _spZero );

        bret = ReadFifo( & pNewPdw->wpdw[_spOne] );
		if( bret == _spFalse )      return -1;
        if( pNewPdw->item.phase2 != _spOne ) {
            printf( "\n Phase2 Error[%d] !" , pNewPdw->item.phase2 );
            WhereIs;
            continue;
        }

        bret = ReadFifo( & pNewPdw->wpdw[_spTwo] );
		if( bret == _spFalse )      return -1;
        if( pNewPdw->item.phase3 != _spTwo ) {
            printf( "\n Phase3 Error[%d] !" , pNewPdw->item.phase3 );
            WhereIs;
            continue;
        }

        bret = ReadFifo( & pNewPdw->wpdw[_spThree] );
		if( bret == _spFalse )      return -1;
        if( pNewPdw->item.phase4 != _spThree) {
            printf( "\n Phase4 Error[%d] !" , pNewPdw->item.phase4 );
            WhereIs;
            continue;
        }

        return pNewPdw->item.channel;
    }

}

/****************************************************************************************
 함    수 : TSK_GthSig
 목    적 :
 가    정 :
 저 자 명 : 조철희
 변 경 자 :
 변경내용 : (목적)
 변경일시 : 99-12-01 5:41오후
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
*****************************************************************************************/
TASK
TSK_GthSig( void ) {

    flg = (STR_FLAG *) ( ahwVME_CMS+aFLG_START);

    InitColVar();

    flg->stat = flg->key = _spZero;

    flg->kp[gnoPrc-prc_KSP1].id = 0x43484B50;

    sc_delay( 200L );

    WaitUntillNotValue( & flg->stat, 'K', 100 );
    printf( "\n Key[%1c]" , flg->key );
    if( flg->key == 'V' ) {
		CheckCount( & flg->kp[ gnoPrc-prc_KSP1 ].noCol );
	}
	else {
    	for( ;; ) {
        	printf( "\n\t 수집을 초기화합니다." );
			InitColVar();

        	printf( "\n\t 신호를 수집하고있습니다..." );
        	CollectPdw();
		}

    }
 
}

/****************************************************************************************
 함    수 : CollectPdw
 목    적 :
 가    정 :
 저 자 명 : 조철희
 변 경 자 :
 변경내용 : (목적)
 변경일시 : 99-07-06 5:41오후
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
*****************************************************************************************/
UINT
CollectPdw(void ) {
    UINT                            noCh;
    TNEW_PDW                        nPdw;
    STR_CHPDW                    *pChPdw;
 
    UINT                          coFifo;
 
    UINT                          preToa;
    UINT                          nowToa;
 
    UINT                        dtoa;
 
    UINT                            bret;

    USHRT                       bperr;
 

	STR_LOWHIGH						pri;

    flg = (STR_FLAG *) ( ahwVME_CMS+aFLG_START);

    coFifo = _spZero;
    noCh = ReadOnePdw( & nPdw );
	if( noCh == -1 )				return;
   	flg->kp[gnoPrc-prc_KSP1].noCol = _spZero;
   	flg->kp[gnoPrc-prc_KSP1].noMis = _spZero;
   	flg->kp[gnoPrc-prc_KSP1].noPhase = _spZero;
   	flg->kp[gnoPrc-prc_KSP1].noDmPhase = _spZero;
   	flg->kp[gnoPrc-prc_KSP1].noFtPhase = _spZero;
   	++ flg->kp[gnoPrc-prc_KSP1].noCol;

    preToa = ReadTOA( & nPdw );

    pri.low = flg->kp[gnoPrc-prc_KSP1].pri.low;
    pri.hgh = flg->kp[gnoPrc-prc_KSP1].pri.hgh;

    while( 1 ) {
        noCh = ReadOnePdw( & nPdw );
		if( noCh == -1 )				return;
       	++ flg->kp[gnoPrc-prc_KSP1].noCol;

        nowToa = ReadTOA( & nPdw );

        if( noCh == _spEndCollect ) {
            if( nPdw.item.frequency_l > KSF_noCell ) {
                printf( "\n\t [W] Invalid the peudo channel[%d] !" , nPdw.item.frequency_l );
                WhereIs;
            }
            for( ;; ) {
                printf( "\n Pseudo channel : %d" , nPdw.item.frequency_l ); WhereIs;
            }
            return nPdw.item.frequency_l;
        }

        if( noCh > KSF_noCell ) {
            printf( "\n\t [W] Invalid PDW's channel[%d] !" , noCh );
            WhereIs;
            continue;
        }

        dtoa = nowToa - preToa;
        bret = CompMarginDiff( dtoa, pri.low, pri.hgh, _spZero );
        if( bret != _spTrue ) {
       		++ flg->kp[gnoPrc-prc_KSP1].noMis;
            printf( "!" );
          	DISP_FinePDW( & nPdw );
        }
        preToa = nowToa;

		if( flg->key == 'Q' )
			return 0;
    }
 
}

#else

/****************************************************************************************
 함    수 : TSK_GthSig
 목    적 :
 가    정 :
 저 자 명 : 조철희
 변 경 자 :
 변경내용 : (목적)
 변경일시 : 99-07-06 5:41오후
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
*****************************************************************************************/
TASK TSK_GthSig( void ) 
{
	STR_TSK_MSG tskMsg;

  int errp;

	UINT noCh;
	UINT noEMT;

	STR_UPDAET updAet;

	int coOv;

	tskMsg.w32 = MprcStartCIPNSP;

  InitColVar();

  for(;;) {
    printf("\n\t [GthSig]" );

		noCh = KSPCollectPDW();
    if( noCh == _spFifoEmpty ) {
     	printf("\nSuspend...");
      sc_tsuspend( tp_Self, tp_Self, &errp );
      printf( "\n errp[%d]" , errp );
      WhereIs;
      continue;
    }

		updAet.aet.noEMT = noEMT = GetTrackChtoAet( gnoPrc-prc_KSP1, noCh );
		printf( "\n 채널번호[%d], 수집개수[%d], 에미터번호[%d]", noCh, stKPDW[noCh].count, noEMT );	

    if( noEMT == _spZero || noEMT > _spMaxEMTNum ) {
    	printf( "\n\t [W] Invalid Track AET in Ch[%d] !" , noCh );
			printf( "\n\t Close WinCell noCh[%d]" , noCh );
 			vKSF_CloseWindow( pwb_KSF1+(gnoPrc-prc_KSP1), noCh );
			WhereIs;
			stKPDW[noCh].count = _spZero;
			continue;
    }

		updAet.aet.sigType = gpOrgAet[ noEMT ].sigType;	WhereIs;
		if( GetTrackAnalStep( noEMT ) == _spColStep ) {
	  	coOv = gpComAet[noEMT].ksp.coOvAET;
			SetTrackAnalStep( noEMT, _spAnlStep );
      if( stKPDW[noCh].count < _spAnalMinPulseCount || stKPDW[noCh].count > KSP_MAX_PDW+10 || \
				stKPDW[noCh].count == -1 ) {
WhereIs;					
				stKPDW[noCh].count = _spZero;
				SendStatAet( & updAet, _spInsuPul );
				
			}
			else {
				tskMsg.in.opData = noCh;
				Qpost( SQ_AnlSig, tskMsg );
			}

		}
		else {
			printf( "\n\t [W] Invalid Track progress[%d]" , GetTrackAnalStep( noEMT ) );
			printf( "\n\t Close WinCell noCh[%d]" , noCh );
 			vKSF_CloseWindow( pwb_KSF1+(gnoPrc-prc_KSP1), noCh );
			WhereIs;
		}

	}

}

/****************************************************************************************
 함    수 : CollectPdw
 목    적 :
 가    정 :
 저 자 명 : 조철희
 변 경 자 :
 변경내용 : (목적)
 변경일시 : 99-07-06 5:41오후
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
*****************************************************************************************/
UINT
CollectPdw( void ) {
    UINT                            noCh;
    TNEW_PDW                        nPdw;
    STR_PDWBANK				     *pChPdw;

    while( 1 ) {
        if( gKDMFifoFull != _spTrue )
            noCh = ReadOnePdw( & nPdw );
        else {
            noCh = GetOnePdw( & nPdw );
            if( noCh == _spFifoEmpty ) {
                WhereIs;
                return _spFifoEmpty;
            }
        }

        if( noCh == _spEndCollect ) {
            printf( "\n Pseudo channel : %d" , nPdw.item.frequency_l );
            if( nPdw.item.frequency_l > KSF_noCell ) {
                printf( "\n\t [W] Invalid the peudo channel[%d] !" , nPdw.item.frequency_l );
                WhereIs;
                continue;
            }
//          gChPdw[ nPdw.item.frequency_l ].fPseudo = _spTrue;
            return nPdw.item.frequency_l;
        }

        if( noCh > KSF_noCell ) {
            printf( "\n\t [W] Invalid PDW's channel[%d] !" , noCh );
            WhereIs;
            continue;
        }

      	pChPdw = & stKPDW[ noCh ];
        if( pChPdw->count < MAX_PDW )
            memcpy32( & pChPdw->pPdw[ pChPdw->count++ ], & nPdw, sizeof( TNEW_PDW ) );
        else {
//          sc_putc('e');
            printf( "\n PDW[%d] %8x, %8x, %8x, %8x",noCh, nPdw.wpdw[0], nPdw.wpdw[1], nPdw.wpdw[2],
nPdw.wpdw[3]);
        }

    }

}

/****************************************************************************************
 함    수 : ReadOnePdw
 목    적 :
 가    정 :
 저 자 명 : 조철희
 변 경 자 :
 변경내용 : (목적)
 변경일시 : 99-07-12 5:41오후
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
*****************************************************************************************/
UINT
ReadOnePdw( TNEW_PDW *pNewPdw ) {

    while ( 1 ) {
        do {
            ReadFifo( & pNewPdw->wpdw[_spZero] );
            if( pNewPdw->item.band == 0x3 )
                return _spEndCollect;
            if( pNewPdw->item.phase1 != _spZero ) {
            	printf( "\n Phase1 Error[%d] !" , pNewPdw->item.phase1 );
            }

        }
        while( pNewPdw->item.phase1 != _spZero );

        ReadFifo( & pNewPdw->wpdw[_spOne] );
        if( pNewPdw->item.phase2 != _spOne ) {
            printf( "\n Phase2 Error[%d] !" , pNewPdw->item.phase2 );
            WhereIs;
            continue;
        }

        ReadFifo( & pNewPdw->wpdw[_spTwo] );
        if( pNewPdw->item.phase3 != _spTwo ) {
            printf( "\n Phase3 Error[%d] !" , pNewPdw->item.phase3 );
            WhereIs;
            continue;
        }

        ReadFifo( & pNewPdw->wpdw[_spThree] );
        if( pNewPdw->item.phase4 != _spThree) {
            printf( "\n Phase4 Error[%d] !" , pNewPdw->item.phase4 );
            WhereIs;
            continue;
        }

        return pNewPdw->item.channel;
    }

}

/****************************************************************************************
 함    수 : ReadFifo
 목    적 : 추적 FIFO READ
 가    정 :
 저 자 명 : 조철희
 변 경 자 :
 변경내용 : (목적)
 변경일시 : 99-07-06 5:41오후
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
*****************************************************************************************/
BOOL
ReadFifo( UINT *phase ) {
    UINT     i;
    int      errp;
    // UINT     count;
    UINT     stat1;

    // TASK_TCB          *tcbinfo;

    // int                  info[3];

 
    while( 1 ) {
        for( i=0 ; i < _spColPdw ; ++i ) {
            if( vDM_FifoEmpty() == _spFalse ) {
                vDM_GetFifo( phase );
                return _spTrue;
            }
        }
 
		// debug in check parity...		
        if( vDM_ParityError() ) {
            sc_putc( 'P' );
            gpSysRunStat->dm[gnoPrc] = _spFail;
//          vDM_ClearPerr();				// debug, 00-07-13 19:35:11
        }
 
        stat1 = CheckSuspendTask( tp_AnlSig );
//      RPrintf( "\n AnlSig : %d, ExtPul : %d" , stat1, stat2 );
 
        if( stat1 == Err_Operation )
            continue;
 
      	if( stat1 != TBSQUEUE ) {
            sc_tpriority( tp_GthSig, tp_GthSig, & errp );       // WhereIs;
            if( gDMHalfFull == _spTrue ) {
                printf( "\n Clear Half Interrupt[%d] !" , gDMHalfFull );
                gDMHalfFull = _spFalse;
                vDM_ClearHalfInterrupt( _spTrue );                  // debug, 00-01-18 13:55:49
            }
		}
 
//      RPrintf( "\n QueCount : %d" , count );
 
    }

}

#endif


/****************************************************************************************
 함    수 : SendPulExt
 목    적 :
 가    정 :
 저 자 명 : 조철희
 변 경 자 :
 변경내용 : (목적)
 변경일시 : 99-12-07 20:29:52
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
*****************************************************************************************/
void
SendPulExt( UINT noCh ) {
    STR_TSK_MSG                 tskMsg;

	int								 i;

    UINT                         noEMT;

    STR_UPDAET                  updAet;

    int                           coOv;

    updAet.aet.noEMT = noEMT = GetTrackChtoAet( gnoPrc-prc_KSP1, noCh );
    printf( "\n Ch[%d] No[%d] of AET[%d]" , noCh, stKPDW[noCh].count, noEMT );
    if( noEMT == _spZero || noEMT > _spMaxEMTNum ) {
        printf( "\n\t [W] Invalid Track AET in Ch[%d] !" , noCh );
        printf( "\n\t Close WinCell noCh[%d]" , noCh );
        vKSF_CloseWindow( pwb_KSF1+(gnoPrc-prc_KSP1), noCh );
        WhereIs;
//      gPdw[ noCh ].co = _spZero;
		return;
    }

    printf( "\n noEMT[%d], pointer %p" , noEMT, & gpComAet[ noEMT ].ksp.coOvAET );
    printf( "\n fPrecStag[%d], fPrecFrqPat[%d], fPrecPriPat[%d]" ,
    			gpComAet[noEMT].ksp.fPrecStag, gpComAet[noEMT].ksp.fPrecFrqPat,
                gpComAet[noEMT].ksp.fPrecPriPat );

    updAet.aet.sigType = gpOrgAet[ noEMT ].sigType;
    if( GetTrackAnalStep( noEMT ) == _spColStep ) {
        coOv = gpComAet[noEMT].ksp.coOvAET;
        printf( "\n CoOv[%d]" , gpComAet[noEMT].ksp.coOvAET );
        for( i=0 ; i < coOv ; ++i ) {
            printf( "%d," , gpComAet[noEMT].ksp.inOvAET[i] );
        }

        SetTrackAnalStep( noEMT, _spAnlStep );

//      if( gChpdw[noCh].count < MPC || gChpdw[noCh].count > MAX_PDW+10 || 
		// debug, 00-10-16 18:32:13, Jo
        if( stKPDW[noCh].count < _sp.cm.Mpc || stKPDW[noCh].count > MAX_PDW+10 || \
            stKPDW[noCh].count == -1 ) {

            stKPDW[noCh].count = _spZero;
            printf( " \n\n Fail UPDATE In <kgsig.c> Collect !!!( Less Pulse ) collect pulse [ %d ] ", stKPDW[noCh].count );
            SendStatAet( & updAet, _spInsuPul );
        }
        else {
            tskMsg.in.opData = noCh;
            Qpost( SQ_AnlSig, tskMsg );
        }

    }

}

/****************************************************************************************
 함    수 : InitColVar
 목    적 :
 가    정 :
 저 자 명 : 조철희
 변 경 자 :
 변경내용 : (목적)
 변경일시 : 99-07-06 5:41오후
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 입력정의 :
 출력정의 :
 관련모듈 :
 자료구조 : (전역변수)
 에러처리/복귀순서:
*****************************************************************************************/
void
InitColVar( void ) {

	KSPCollectInit();
	
	// memset32( & stKPDW[0], _spZero, sizeof( STR_PDWBANK ) * _spCoMaxCh );
 
}
 
void
CollectTest( void ) {
	CELL_WORDS					cw;
	int				  i;

	Hold;

    vRCV_InitBoard();
    vAUD_InitBoard();
    vNSF_InitBoard();
	vKSF_InitBoard( pwb_KSF1 + ( gnoPrc - prc_KSP1 ) );
    vRCV_SetModeControl_Mode( RCV_MODE_PDW );

	printf( "\n Set wincell " );
	for( i=0 ; i < KSF_noCell ; ++i )	{
    	cw.w0.ksf.use = _spEnable;
    	cw.w0.ksf.check_stat = _spEnable;

    	cw.w1.ksf.stat = 0;
    	cw.w1.ksf.bc   = ( i % 3 );

    	cw.w0.ksf.from_aoa = 0;
    	cw.w0.ksf.to_aoa   = _spMaxVal32;

    	cw.w1.ksf.lower_frq = 0;
    	cw.w1.ksf.upper_frq = _spMaxVal32;

    	cw.w2.ksf.lower_pw = _spZero;
    	cw.w2.ksf.upper_pw = _spMaxVal32;

    	cw.w3.ksf.late  = _spZero;      /* LATE     Default = 0 */
    	cw.w3.ksf.p_req = _spZero;        /* pseudo-PDW request Default = 0 */
    	cw.w3.ksf.p_ena = _spDisable;      /* pulse counter enable */
    	cw.w3.ksf.t_ena = _spDisable;      /* timer counter enable */

		cw.w3.ksf.t_cnt = 70;
    	cw.w3.ksf.p_cnt = 240;

		vKSF_SetCellWords( pwb_KSF1 + ( gnoPrc - prc_KSP1 ) ,i, & cw );

	}

//	Hold;

//	PRC_Initialize();
	
}

