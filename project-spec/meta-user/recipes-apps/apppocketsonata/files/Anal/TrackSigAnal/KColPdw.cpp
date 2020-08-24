// KColPdw.cpp: implementation of the CKColPdw class.
//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#include "KnownSigAnal.h"
#include "KColPdw.h"

#include <string.h>

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : KSPCollectPDW
// 반환되는 형  : int
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-07-27 14:07:34
//
int KSPCollectPDW() {
	return theKSPColPdw->Collect();
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : KSPCollectInit
// 반환되는 형  : 없음
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-25 17:35:09
//
void KSPCollectInit() {
	theKSPColPdw->Init(); 
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKColPdw::CKColPdw
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : SONATA, 2005-09-07 12:49:54
//
CKColPdw::CKColPdw( int coMaxPdw )
{

	// 수집 최대 개수 저장
	m_nMaxPdw = coMaxPdw;

#ifdef _WIN32
	// 전역 변수들 메모리 할당
	for( int i=0 ; i < _spCoKSP ; ++i ) {
		for( int j=0 ; j < KSF_noCell ; ++j ) {
			if( stKPDW[i][j].pPdw == 0 )
				stKPDW[i][j].pPdw = ( TNEW_PDW * ) malloc( m_nMaxPdw * sizeof( TNEW_PDW ) );
		}
	}

#else
	BOOL bRet=TRUE;
	
	// 전역 변수들 메모리 할당
	for( int j=0 ; j < KSF_noCell ; ++j ) {
		stKPDW[j].pPdw = ( TNEW_PDW * ) malloc( m_nMaxPdw * sizeof( TNEW_PDW ) );
		if( stKPDW[j].pPdw == NULL ) {
			printf( "\n [W] stKPDW[%d].pPdw's memory allocation error !" , j );
			bRet = FALSE;
		}
	}

	if( bRet == FALSE )
		printf( "\n [W] 신호 수집 클래스 생성자 실패 !" );

#endif

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKColPdw::~CKColPdw
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : SONATA, 2005-09-07 12:49:56
//
CKColPdw::~CKColPdw()
{

#ifdef _WIN32
	for( int i=0 ; i < _spCoKSP ; ++i ) {
		for( int j=0 ; j < KSF_noCell ; ++j ) {
			if( stKPDW[i][j].pPdw != 0 )
				free( stKPDW[i][j].pPdw );
		}
	}
#else
	for( int j=0 ; j < KSF_noCell ; ++j ) {
		free( stKPDW[j].pPdw );
	}

#endif

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKColPdw::Init
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : SONATA, 2005-09-07 12:57:04
//
void CKColPdw::Init()
{
	vDM_ResetFifo();
	vDM_ClearPerr();

#ifdef _WIN32
	// 전역 변수들 초기화
	for( int i=0 ; i < _spCoKSP ; ++i ) {
		for( int j=0 ; j < KSF_noCell ; ++j ) {
			stKPDW[i][j].count = 0;
		}
	}

#else
	// 전역 변수들 초기화
	for( int j=0 ; j < KSF_noCell ; ++j ) {
		stKPDW[j].count = 0;
	}

#endif

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKColPdw::Collect
// 반환되는 형  : int
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-12-06 11:48:25
//
int CKColPdw::Collect()
{
	int noCh;

	TNEW_PDW tpdw;
	STR_PDWBANK *pChPdw;

	while( TRUE ) {
		if( gKDMFifoFull != _spTrue ) {
			noCh = ReadOnePdw( & tpdw );
		}
    else {
      noCh = GetOnePdw( & tpdw );
      if( noCh == _spFifoEmpty ) {
				WhereIs;
        return( _spFifoEmpty );
      }
		}
		
		// 수집 종료 Pseudo PDW 
		if( noCh == _spEndCollect )
			break;

		if( noCh >= 0 && noCh < KSF_noCell ) {
#ifdef _WIN32
			pChPdw = & stKPDW[0][ noCh ];
#else
			pChPdw = & stKPDW[ noCh ];
#endif

			if( pChPdw->count < m_nMaxPdw ) {
				pChPdw->pPdw[ pChPdw->count ].wpdw[0] = tpdw.wpdw[0];
				pChPdw->pPdw[ pChPdw->count ].wpdw[1] = tpdw.wpdw[1];
				pChPdw->pPdw[ pChPdw->count ].wpdw[2] = tpdw.wpdw[2];
				pChPdw->pPdw[ pChPdw->count ].wpdw[3] = tpdw.wpdw[3];
				++ pChPdw->count;
			}
			else {
				printf( "\n [W] 수집 개수 초과했음!, 채널[%d], 개수[%d] ", noCh, pChPdw->count );
			}
		}
		else {
			printf( "\n [W] 잘못된 채널[%d] 번호 입니다.!" , noCh );
		}

	}
	
	// 패러티 에러 확인
	if( vDM_ParityError() ) {
		gpSysRunStat->dm[gnoPrc] = (UINT) _spFail;

		// 패러티 에러 삭제
		vDM_ClearPerr();
	}

	// 채널 번호 리턴한다.
	noCh = tpdw.item.frequency_l;

#ifdef _WIN32
	pChPdw = & stKPDW[0][ noCh ];
#else
	pChPdw = & stKPDW[ noCh ];
#endif

	printf( "\n" );
	printf( "\n **************************************************************************" );
	printf( "\n 신호 수집 종료, 채널번호[%d], 수집개수[%d]", noCh, pChPdw->count );
	
	return noCh;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKColPdw::ReadOnePdw
// 반환되는 형  : int
// 함 수 인 자  : TNEW_PDW *pNewPdw
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-12-06 13:30:17
//
int CKColPdw::ReadOnePdw( TNEW_PDW *pNewPdw )
{

  while( TRUE ) {
		do {
			if( _spFalse == ReadFifo( & pNewPdw->wpdw[ PHASE1 ] ) )
				return -1;

			// 추적 필터판 채널 수집 종료
			if( pNewPdw->item.band == 0x3 )
				return _spEndCollect;

			// Phase 1 수집 확인.
			if( pNewPdw->item.phase1 != _spZero ) {
				printf( "\n Phase1 Error[%d] !" , pNewPdw->item.phase1 );
			}

		}	while( pNewPdw->item.phase1 != _spZero );

		if( _spFalse == ReadFifo( & pNewPdw->wpdw[ PHASE2 ] ) )
			return -1;
    if( pNewPdw->item.phase2 != _spOne ) {
			printf( "\n 2번째 Phase 에러 발생됨." );
      continue;
    }

		if( ReadFifo( & pNewPdw->wpdw[ PHASE3 ] ) == _spFalse )
			return -1;
    if( pNewPdw->item.phase3 != _spTwo ) {
			printf( "\n 3번째 Phase 에러 발생됨." );
      continue;
		}

		if( ReadFifo( & pNewPdw->wpdw[ PHASE4 ] ) == _spFalse )
			return -1;
    if( pNewPdw->item.phase4 != _spThree) {
			printf( "\n 4번째 Phase 에러 발생됨." );
      continue;
    }

		return (int) pNewPdw->item.channel;
	}

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKColPdw::ReadFifo
// 반환되는 형  : BOOL
// 함 수 인 자  : UINT *phase
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-12-06 13:48:05
//
BOOL CKColPdw::ReadFifo( UINT *phase )
{
	UINT i;

  while( TRUE ) {
		for( i=0 ; i < 50 ; ++i ) {
			if( vDM_FifoEmpty() == _spFalse ) {
				vDM_GetFifo( phase );
				return TRUE;
			}
		}

#ifndef _WIN32
		int errp;
		UINT stat;

    stat = CheckSuspendTask( tp_AnlSig );
    if( stat == Err_Operation )
			continue;
 
    if( stat != TBSQUEUE ) {
      sc_tpriority( tp_GthSig, tp_GthSig, & errp );       // WhereIs;
      if( gKDMHalfFull == _spTrue ) {
        printf( "\n Clear Half Interrupt[%d] !" , gKDMHalfFull );
        gKDMHalfFull = _spFalse;
        vDM_ClearHalfInterrupt( _spTrue );                  // debug, 00-01-18 13:55:49
      }
		}

#endif
 
	}

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKColPdw::GetOnePdw
// 반환되는 형  : int
// 함 수 인 자  : TNEW_PDW *pNewPdw
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-12-06 14:05:38
//
int CKColPdw::GetOnePdw( TNEW_PDW *pNewPdw )
{

  while( TRUE ) {
		do {
			if( GetFifo( & pNewPdw->wpdw[ PHASE1 ] ) == _spFalse )          
				return _spFifoEmpty;

			if( pNewPdw->item.band == 0x3 )
					return _spEndCollect;

			if( pNewPdw->item.phase1 != _spZero ) {
				printf( "\n 1번째 Phase 에러 발생됨." );
			}

		} while( pNewPdw->item.phase1 != _spZero );

    if( GetFifo( & pNewPdw->wpdw[ PHASE2 ] ) == _spFalse )          
			return _spFifoEmpty;
    if( pNewPdw->item.phase2 != _spOne ) {
			printf( "\n 2번째 Phase 에러 발생됨." );
      continue;
    }

    if( GetFifo( & pNewPdw->wpdw[ PHASE3 ] ) == _spFalse )
			return _spFifoEmpty;
    if( pNewPdw->item.phase3 != _spTwo ) {
			printf( "\n 3번째 Phase 에러 발생됨." );
      continue;
    }

    if( GetFifo( & pNewPdw->wpdw[ PHASE4 ] ) == _spFalse )          
			return _spFifoEmpty;
    if( pNewPdw->item.phase4 != _spThree) {
			printf( "\n 4번째 Phase 에러 발생됨." );
      continue;
    }

		return pNewPdw->item.channel;

  }

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKColPdw::GetFifo
// 반환되는 형  : BOOL
// 함 수 인 자  : UINT *phase
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-12-06 14:43:41
//
BOOL CKColPdw::GetFifo( UINT *phase )
{

  if( vDM_FifoEmpty() == _spFalse ) {
		vDM_GetFifo( phase );
		return _spTrue;
  }
  else
    return _spFalse;

}

