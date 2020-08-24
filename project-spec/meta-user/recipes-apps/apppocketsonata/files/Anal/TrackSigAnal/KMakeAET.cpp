// KMakeAET.cpp: implementation of the CKMakeAET class.
//
//////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// PC용 상위 클래스에 전달하기 위한 선언
#ifdef _WIN32
#include "../../AdvSigAnal/stdafx.h"
#include "../../AdvSigAnal/AdvSigAnal.h"

#include "../../AdvSigAnal/MainFrm.h"
#include "../../AdvSigAnal/AdvSigAnalDoc.h"
#include "../../AdvSigAnal/AdvSigAnalView.h"
#endif

#include "KnownSigAnal.h"
#include "KMakeAET.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CMakeAET
// 반환되는 형  : CKMakeAET::CKMakeAET() :
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-07-28 14:09:48
//
//##ModelId=42E98F300031
CKMakeAET::CKMakeAET( void *pParent, int coMaxPdw ) : CMakeAET( coMaxPdw )
{
	m_pKnownSigAnal = ( CKnownSigAnal * ) pParent;
	 
	// 초기에 한번만 초기화한다.
	m_CoNewAet = 0;

	m_pAet = GetAet();
	m_pEmitter = GetEmitter();
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::~CKMakeAET
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-07-28 18:14:06
//
//##ModelId=42E98F300032
CKMakeAET::~CKMakeAET()
{

}

//////////////////////////////////////////////////////////////////////
//
//! \brief    CKMakeAET::Init
//! \author   조철희
//! \return   void
//! \version  1.37
//! \date     2006-08-29 10:11:11
//! \warning
//
void CKMakeAET::Init()
{

}

//////////////////////////////////////////////////////////////////////
//
//! \brief    PRI 분석을 통해서 P-AET를 근더로 에미터를 생성한다.
//! \author   조철희
//! \return   void
//! \version  1.37
//! \date     2006-08-29 10:10:16
//! \warning
//
void CKMakeAET::MakeAET()
{
	// 초기화
	Init();

	CMakeAET::MakeAET();
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::KnownMakeAET
// 반환되는 형  : BOOL
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-07-28 18:47:54
//
//##ModelId=42E98F300030
BOOL CKMakeAET::KnownMakeAET()
{
	int i;
	UINT maxPulse;
	int idxEmitter;
	STR_EMITTER *pEmitter;

	CMakeAET::MakeAET();

	/*! \bug  m_IdxUpdAet 초기화
	    \date 2006-06-26 13:43:57, 조철희
	*/
	m_IdxUpdAet = -1;

	// 추적 성공인지를 체크한다.
	// 추출된 펄스열로 에미터가 1개 만들어 지면 추
	if( m_CoAet >= 1 ) {
		// 추적에서 2개 이상의 추적 변경에미터 분석될 때는 가장 많은 펄스열로 분석된것만 추적 Update 로 인정하고
		// 나머지 다른 에미터들은 펄스열 마킹만한다.
		maxPulse = 0;
		for( i=0 ; i < m_CoAet ; ++i ) {
			// 추적할 PRI 값과 추적한 PRI 값이 같아야 추적 성공으로 한다.
			//-- 조철희 2006-01-25 14:00:31 --//
			if( CompPRI( & m_pAet[i].aet.pri, & stTrkAet.aet.pri ) == TRUE ) {
				m_pAet[i].aet.noEMT = stTrkAet.aet.noEMT;

				if( maxPulse < m_pAet[i].ext.noExt ) {
					maxPulse = m_pAet[i].ext.noExt;
					m_IdxUpdAet = i;
				}
			}

			/*! \bug  에미터로 생성된 펄스열들만 마킹을 해서 새로운 에미터 분석시에 분석하지 못하게 한다.
			    \date 2006-06-29 13:53:26, 조철희
			*/
			// 추출된 펄스 Marking
			idxEmitter = m_pAet[i].ext.idxEmitter;
			pEmitter = & m_pEmitter[idxEmitter];
			MarkToEmitterPdwIndex( pEmitter, EXTRACT_MARK );
		}

		// 추출한 펄스열들은 EXTRACT_MARK 을 해서 재 분석을 안 하도록 한다.
		//for( i=0 ; i < m_CoSeg ; ++i ) {
			//MarkToPdwIndex( m_pSeg[i].pdw.pIndex, m_pSeg[i].pdw.count, EXTRACT_MARK );
		//}

	}

	return m_IdxUpdAet >= 0;

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::CompPRI
// 반환되는 형  : BOOL
// 함 수 인 자  : STR_PRI *pNewPri
// 함 수 인 자  : STR_PRI *pTrkPri
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-25 14:03:44
//
BOOL CKMakeAET::CompPRI( STR_PRI *pNewPri, STR_PRI *pTrkPri )
{
	int i;
	int pri_margin;

	switch( pNewPri->type ) {
		case _STABLE :
			return TRUE;

		case _STAGGER :
			if( pTrkPri->type == _JITTER )
				return TRUE;
			else if( pTrkPri->type == _STAGGER ) {
				if( pNewPri->swtLev == pTrkPri->swtLev ) {
					for( i=0 ; i < pNewPri->swtLev ; ++i ) {
						if( CompMeanDiff( pNewPri->swtVal[i], pTrkPri->swtVal[i], 2*STABLE_MARGIN ) == FALSE ) {
	  					return FALSE;
						}
					}
				}
				else {
					return FALSE;
				}
			}
			break;

		case _PATTERN :
			return TRUE;

		case _DWELL :
			return TRUE;

		case _JITTER :
			// 스태거 추적 신호를 추적분석을 해서
			// 지터로 분석하게 되면 범위를 체크해서 새로운 에미터 생성 또는
			// 추적 실패 여부를 결정한다.
			//-- 조철희 2006-05-09 16:19:35 --//
			/*! \bug  변화폭을 5 usdptj 20 us로 수정함. 
			    \date 2006-09-04 10:47:24, 조철희
			*/
			pri_margin = 20 * ONE_MICROSEC;
			if( pTrkPri->type == _STAGGER ) {
				if( _spFalse == CompMeanDiff( pTrkPri->min, pNewPri->min, pri_margin ) )
					return FALSE;
				if( _spFalse == CompMeanDiff( pTrkPri->max, pNewPri->max, pri_margin ) )
					return FALSE;

				return TRUE;
			}
			else {
				return TRUE;
			}

	}
/*
	diff = _spZero;
	b1ret = _spFalse;
	for( i=0 ; i < pNewAet->aet.pri.swtLev ; ++i ) {
		b2ret = _spFalse;
		priMean = pNewAet->aet.pri.swtVal[i];

		for( j=0 ; j < pNewAet->aet.pri.swtLev ; ++j ) {
			b2ret = CompMeanDiff( priMean, pAet->pri.swtVal[j], _sp.mg.fixpri );

			if( b2ret == _spTrue ) {
	  		diff += _abs( (int) ( pAet->pri.swtVal[j] - priMean ) );		// Call Cal...
				break;
			}
		}

		if( b2ret == _spFalse ) {
    		return _spMaxVal32;
		}
		else
			b1ret = _spTrue;

	}		*/

	return TRUE;
	
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::MakeUpAET
// 반환되는 형  : void
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : SONATA, 2005-09-07 15:04:06
//
void CKMakeAET::MakeUpAET()
{
	int count;
	int coUpdAet;
	STR_NEWAET *pNewAet;
	STR_UPDAET *pUpdAet;
	
	count = GetCoAet();
	pNewAet = GetNewAet();
	pUpdAet = GetUpdAet();

	coUpdAet = 0;

	// 추적 성공일때...
	// 새로운 에미터와 추적 에미터와의 하모닉 체크해서 새로운 에미터를 제거하도록 한다.
	//-- 조철희 2005-10-24 11:33:36 --//
	if( pUpdAet != NULL ) {
		// 추적 성공 에미터와 추적할 에미터 제원과 비교해서 하모닉 체크해서 유사 에미터로 판정한다.
		//-- 조철희 2005-12-07 19:16:44 --//
		if( CheckHarmonic( & stTrkAet.aet.pri, & pUpdAet->aet.pri ) >= 2 ) {
			memcpy( & pUpdAet->aet.pri, & stTrkAet.aet.pri, sizeof( STR_PRI ) );
		}

		for( int i=0 ; i < count ; ++i ) {
			if( m_pAet[i].aet.noEMT != 0 ) {
				pUpdAet->aet.as.type = stTrkAet.aet.as.type;
				pUpdAet->aet.as.prd = stTrkAet.aet.as.prd;
				pUpdAet->aet.as.stat = stTrkAet.aet.as.stat;
				++ coUpdAet;
			}
		}
	}
	// 추적 에미터가 발견되지 않을 때는 새로운 에미터 제원으로 추적 업데이트한다.
	else if( count >= 1 ) {
		STR_NEWAET *pDummyAet;

		// ART 제원을 SWAP 하기 위한 버퍼
		pDummyAet = & m_pAet[ MAX_AET ];

		for( int i=0 ; i < count ; ++i ) {
			if( CheckHarmonic( & stTrkAet.aet, & pNewAet->aet ) == TRUE ) {
				// 하모닉 관계 에미터 제원 값을 수정한다.
				// 추적 성공임을 표시한다.
				pNewAet->aet.noEMT = stTrkAet.aet.noEMT;

				// 방위 정보는 최근 정보로 한다.
				// PRI  값은 하모닉 관계로 추적 에미터 제원으로 한다.
				memcpy( & pNewAet->aet.pri, & stTrkAet.aet.pri, sizeof( STR_PRI ) );

				// 유사 에미터를 결정한 에미터를 예비 버퍼에 복사한다.
				memcpy( pDummyAet, pNewAet, sizeof( STR_NEWAET ) );

				// 유사 에미터 까지 에미터를 이동한다.
				for( int j=i-1 ; j >= 0 ; --j ) {
					memcpy( & m_pAet[j+1], & m_pAet[j], sizeof( STR_NEWAET ) );
				}
				memcpy( & m_pAet[0], pDummyAet, sizeof( STR_NEWAET ) );

				m_IdxUpdAet = 0;

				coUpdAet = 1;

				break;
			}

			++ pNewAet;
		}
	}

	m_CoNewAet = count - coUpdAet;

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::IsUpdateAet
// 반환되는 형  : BOOL
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-09-08 10:14:57
//
BOOL CKMakeAET::IsUpdateAet()
{
	// 추적 성공 또는 실패인지를 검사한다.
	return m_pAet[0].aet.noEMT != _spZero;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::CheckHarmonic
// 반환되는 형  : UINT
// 함 수 인 자  : STR_AET *pAet1
// 함 수 인 자  : STR_AET *pAet2
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-09-08 11:01:32
//
UINT CKMakeAET::CheckHarmonic(STR_AET *pAet1, STR_AET *pAet2)
{
	int i;

	int nHarmonic;

	if( pAet1 == NULL || pAet2 == NULL ) {
		printf( "\n\t [W] Invalid comparion of AET !" );
		return 0;
	}

	// 추적할 것이 STAGGER 일때 새로운 에미터가 Jitter라고 하면 새로운 에미터를 송신하지 않는다.
	if( pAet1->pri.type == _STAGGER && pAet2->pri.type == _JITTER ) {
		if( TRUE == CompMeanDiff( pAet2->pri.min, pAet1->pri.min, STABLE_MARGIN ) &&
				TRUE == CompMeanDiff( pAet2->pri.max, pAet1->pri.max, STABLE_MARGIN ) )
		return 1;

		/*! \bug  Jitter 신호는 하모닉 체크해서 최대한 없앤다.
		    \date 2006-08-25 09:37:36, 조철희
		*/		
	// 사례 1번
	// 추적할 에미터 타입이 지터인데 추적에서 지터 추출이 안되고 
	// 새로운 에미터 분석에서 스태거 분석이 될 경우에 새로운 에미터로 보고하게 한다.
	//
	// 재현
	// 파일명: D:\RSA-TFT\소나타 ES TFT\해상 신호\A00_소나타OT 해상신호\광명함\WM-423\wm-423_s333_scans.pdw 파일을
	// 

	// 사례 2번
	// 추적할 에미터 타입이 스태거인데 추적에서 스태거 추출이 안되고 
	// 새로운 에미터 분석에서 지터로 분석된다면 하모닉 체크로 해서 추적 성공으로 할 수 있다.
	// 재현
	// 파일명: D:\RSA-TFT\소나타 ES TFT\해상 신호\A15-noAnal\sps-64.pdw 파일을
	//

	// 사례 2번
	// 추적할 에미터 타입이 스태거인데 추적에서 스태거 추출이 안되고 
	// 새로운 에미터 분석에서 지터로 분석된다면 하모닉 체크로 해서 추적 성공으로 할 수 있다.
	// 재현
	// 파일명: D:\RSA-TFT\소나타 ES TFT\해상 신호\A20-2Step\jitter_2step.pdw 파일을 참조함.
	//

/*
		if( pAet1->pri.mean > pAet2->pri.mean )
			return _max( 1, UDIV( pAet1->pri.mean, pAet2->pri.mean ) );
		else {
			// Stagger & Jitter 인 경유에는 PRI 범위가 일치 해야 한다.
			//-- 조철희 2005-12-14 17:32:32 --//
			// return _max( 1, UDIV( pAet2->pri.mean, pAet1->pri.mean ) );

			return CheckHarmonic( & pAet1->pri, & pAet2->pri ) == 1;
		}
		*/
	}
	else if( pAet1->pri.type == _JITTER && pAet2->pri.type == _JITTER ) {
		nHarmonic = CheckHarmonic( & pAet1->pri, & pAet2->pri );
		if( nHarmonic >= 2 && 0 == CalOverlapSpace( pAet1->pw.max, pAet1->pw.min, pAet2->pw.max, pAet2->pw.min ) )
			return 0;
		return nHarmonic;
	}
	/*! \bug  지터와 Stable 비교는 무시한다.
	    \date 2006-09-05 08:51:47, 조철희
	*/
	else if( pAet1->pri.type == _JITTER && pAet2->pri.type == _STABLE ) {
		return 0;
		// return CheckHarmonic( pAet1->pri.mean, pAet2->pri.mean );	
	}
	/*! \bug  지터와 Stable 비교는 무시한다.
	    \date 2006-09-05 08:51:47, 조철희
	*/
	else if( pAet1->pri.type == _STABLE && pAet2->pri.type == _JITTER ) {
		return 0;
		// return CheckHarmonic( pAet1->pri.mean, pAet2->pri.mean );	
	}
	else if( pAet1->pri.type == _STAGGER && pAet2->pri.type == _STABLE ) {
		int framePri;

		if( CompMeanDiff( pAet1->pri.mean, pAet2->pri.mean, STABLE_MARGIN ) ) {
			return 1;
		}

		framePri = 0;
		for( int i=0 ; i < pAet1->pri.swtLev ; ++i ) {
			framePri += pAet1->pri.swtVal[i];
		}

		return CheckHarmonic( framePri, pAet2->pri.mean );
	}
	else if( pAet1->pri.type == _STABLE && pAet2->pri.type == _STAGGER ) {
		int framePri;

		if( CompMeanDiff( pAet1->pri.mean, pAet2->pri.mean, STABLE_MARGIN ) ) {
			return 1;
		}
		else {
			framePri = 0;
			for( int i=0 ; i < pAet2->pri.swtLev ; ++i ) {
				framePri += pAet2->pri.swtVal[i];
			}

			return CheckHarmonic( framePri, pAet1->pri.mean );
		}
	}
	//-- 조철희 2005-10-25 19:01:09 --//
	else if( pAet1->pri.type == _STABLE && pAet2->pri.type == _STABLE ) {
		return CheckHarmonic( pAet1->pri.mean, pAet2->pri.mean );	
	}
	else if( pAet1->pri.type == _DWELL && pAet2->pri.type == _STABLE ) {
		for( i=0 ; i < stTrkAet.aet.pri.swtLev ; ++i ) {
			BOOL bRet;

			bRet = CheckHarmonic( stTrkAet.aet.pri.swtVal[i], pAet2->pri.mean );
			if( bRet != 0 )
				return bRet;
		}
	}
	else if( pAet1->pri.type == _STAGGER && pAet2->pri.type == _STAGGER ) {
		return CheckStaggerHarmonic( & pAet1->pri, & pAet2->pri );
	}
	/*! \bug  
	    \date 2006-09-26 18:34:38, 조철희
	*/
	/*
	else if( pAet1->pri.type == _JITTER && pAet2->pri.type == _PATTERN ) {
		nHarmonic = CheckHarmonic( & pAet1->pri, & pAet2->pri );

		if( nHarmonic >= 2 && 0 == CalOverlapSpace( pAet1->pw.max, pAet1->pw.min, pAet2->pw.max, pAet2->pw.min ) )
			return 0;
		return nHarmonic;
	}
	else if( pAet1->pri.type == _PATTERN && pAet2->pri.type == _JITTER ) {
		nHarmonic = CheckHarmonic( & pAet1->pri, & pAet2->pri );

		if( nHarmonic >= 2 && 0 == CalOverlapSpace( pAet1->pw.max, pAet1->pw.min, pAet2->pw.max, pAet2->pw.min ) )
			return 0;
		return nHarmonic;
	}
	*/
	
	return 0;
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CKMakeAET::CheckStaggerHarmonic
//!	\author  조철희
//!	\param	 pPri1	인자형태 STR_PRI *
//!	\param	 pPri2	인자형태 STR_PRI *
//!	\return	 UINT
//! \version 1.0
//! \date		 2006-07-24 10:16:27
//! \warning
//
UINT CKMakeAET::CheckStaggerHarmonic( STR_PRI *pPri1, STR_PRI *pPri2 )
{
	int i;

	if( pPri1->swtLev != pPri2->swtLev )
		return 0;

	for( i=0 ; i < pPri1->swtLev ; ++i ) {
		if( FALSE == CompMeanDiff( pPri1->swtVal[i], pPri2->swtVal[i], 8 * ONE_MICROSEC ) ) {
			return 0;
		}
	}

	return 1;

}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::CheckHarmonic
// 반환되는 형  : UINT
// 함 수 인 자  : STR_PRI *pPri1
// 함 수 인 자  : STR_PRI *pPri2
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-10-24 14:03:54
//
UINT CKMakeAET::CheckHarmonic( STR_PRI *pPri1, STR_PRI *pPri2 )
{
	int overlap_ratio;
	int overlap_space;
	int exp_pri_min, exp_pri_max;

	float fdiv_jitter_ratio;

	STR_PRI *pMaxPri, *pMinPri;

	if( pPri1->mean > pPri2->mean ) {
		pMaxPri = pPri1;
		pMinPri = pPri2;
	}
	else {
		pMaxPri = pPri2;
		pMinPri = pPri1;
	}

	fdiv_jitter_ratio = FDIV( pMaxPri->mean, pMinPri->mean );
	exp_pri_min = UMUL( fdiv_jitter_ratio, pMinPri->min );
	exp_pri_max = UMUL( fdiv_jitter_ratio, pMinPri->max );

	overlap_space = CalOverlapSpace( pMaxPri->max, pMaxPri->min, exp_pri_max, exp_pri_min );
	if( overlap_space != 0 ) {
		overlap_ratio = UDIV( overlap_space * 100 , pMaxPri->max - pMaxPri->min );
		if( overlap_ratio < 80 ) {
			overlap_ratio = UDIV( ( pMaxPri->max - pMaxPri->min ) * 100 , overlap_space );
			if( overlap_ratio >= 80 )
				return (int) ( fdiv_jitter_ratio + 0.5 );
		}
		else
			return (int) ( fdiv_jitter_ratio + 0.5 );
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CKMakeAET::CheckHarmonic
//!	\author  조철희
//!	\param	 mean1	인자형태 UINT
//!	\param	 mean2	인자형태 UINT
//!	\return	 UINT
//! \version 1.0
//! \date		 2006-07-24 09:26:16
//! \warning
//
UINT CKMakeAET::CheckHarmonic(UINT mean1, UINT mean2 )
{
	return m_pKnownSigAnal->CheckHarmonic( mean1, mean2 );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::GetCoNewAet
// 반환되는 형  : int
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-10-24 13:57:54
//
int CKMakeAET::GetCoNewAet()
{
	return m_CoNewAet;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : *CKMakeAET::GetNewAet
// 반환되는 형  : STR_NEWAET
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-10-24 11:41:29
//
STR_NEWAET *CKMakeAET::GetNewAet() 
{

	for( int i=0 ; i < m_CoAet ; ++i ) {
		if( m_pAet[i].aet.noEMT == 0 )
			return & m_pAet[i];
	}
	
	return NULL;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::GetIndexNewAet
// 반환되는 형  : int
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-26 11:02:51
//
int CKMakeAET::GetIndexNewAet()
{

	for( int i=0 ; i < m_CoAet ; ++i ) {
		if( m_pAet[i].aet.noEMT == 0 )
			return i;
	}
	
	return -1;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : *GetUpdAet
// 반환되는 형  : STR_UPDAET
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2005-10-24 11:42:24
//
STR_UPDAET *CKMakeAET::GetUpdAet() 
{
	if( m_IdxUpdAet >= 0 )
		return & m_pAet[m_IdxUpdAet];
	else
		return NULL;
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::CalcAoaMeanByHistAoa
// 반환되는 형  : int
// 함 수 인 자  : STR_PDWINDEX *pSrcIndex
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:17:23
//
int CKMakeAET::CalcAoaMeanByHistAoa( STR_PDWINDEX *pSrcIndex )
{
	return m_pKnownSigAnal->CalcAoaMeanByHistAoa( pSrcIndex );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::GetColPdw
// 반환되는 형  : int
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:17:27
//
int CKMakeAET::GetColPdw()
{
	return m_pKnownSigAnal->GetColPdw();
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::CalcPAMean
// 반환되는 형  : int
// 함 수 인 자  : PDWINDEX *pPdwIndex
// 함 수 인 자  : int count
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:17:30
//
int CKMakeAET::CalcPAMean(PDWINDEX *pPdwIndex, int count )
{
	return m_pKnownSigAnal->CalcPAMean( pPdwIndex, count );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::VerifyPW
// 반환되는 형  : int
// 함 수 인 자  : PDWINDEX *pPdwIndex
// 함 수 인 자  : int count
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:17:32
//
int CKMakeAET::VerifyPW( PDWINDEX *pPdwIndex, int count )
{
	return m_pKnownSigAnal->VerifyPW( pPdwIndex, count );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::MarkToPdwIndex
// 반환되는 형  : void
// 함 수 인 자  : PDWINDEX *pPdwIndex
// 함 수 인 자  : int count
// 함 수 인 자  : int mark_type
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:17:35
//
void CKMakeAET::MarkToPdwIndex( PDWINDEX *pPdwIndex, int count, int mark_type )
{
	m_pKnownSigAnal->MarkToPdwIndex( pPdwIndex, count, mark_type );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::SaveEmitterPdwFile
// 반환되는 형  : void
// 함 수 인 자  : STR_EMITTER *pEmitter
// 함 수 인 자  : int index
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:17:37
//
void CKMakeAET::SaveEmitterPdwFile(STR_EMITTER *pEmitter, int index )
{
	m_pKnownSigAnal->SaveEmitterPdwFile( pEmitter, index );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::GetCoSeg
// 반환되는 형  : int
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:17:39
//
int CKMakeAET::GetCoSeg()
{
	return m_pKnownSigAnal->GetCoSeg();
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::GetCoEmitter
// 반환되는 형  : int
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:17:42
//
int CKMakeAET::GetCoEmitter()
{
	return m_pKnownSigAnal->GetCoEmitter();
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : *CKMakeAET::GetPulseSeg
// 반환되는 형  : STR_PULSE_TRAIN_SEG
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:17:44
//
STR_PULSE_TRAIN_SEG *CKMakeAET::GetPulseSeg()
{
	return m_pKnownSigAnal->GetPulseSeg();
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : *CKMakeAET::GetEmitter
// 반환되는 형  : STR_EMITTER
// 함 수 인 자  : 없음
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2006-01-23 10:17:47
//
STR_EMITTER *CKMakeAET::GetEmitter()
{
	return m_pKnownSigAnal->GetEmitter();
}

//////////////////////////////////////////////////////////////////////
//
//!	\brief	 CKMakeAET::CalcFreqMedian
//!	\author  조철희
//!	\param	 pSeg	인자형태 STR_PULSE_TRAIN_SEG *
//!	\return	 UINT
//! \version 1.0
//! \date		 2006-05-09 14:59:01
//! \bug
//! \warning
//
UINT CKMakeAET::CalcFreqMedian( STR_PULSE_TRAIN_SEG *pSeg )
{
	return m_pKnownSigAnal->MedianFreq( NULL, pSeg->pdw.pIndex, pSeg->pdw.count );
}

//////////////////////////////////////////////////////////////////////
//
// 함 수 이 름  : CKMakeAET::CalDtoaMeanMinMax
// 반환되는 형  : void
// 함 수 인 자  : STR_PULSE_TRAIN_SEG *pSeg
// 함 수 인 자  : STR_LOWHIGH *pRange
// 함 수 설 명  : 
// 최 종 변 경  : 조철희, 2013-12-06 10:26:05
//
void CKMakeAET::CalDtoaMeanMinMax( STR_PULSE_TRAIN_SEG *pSeg, STR_LOWHIGH *pRange )
{
	m_pKnownSigAnal->CalDtoaMeanMinMax( pSeg, pRange );

}

