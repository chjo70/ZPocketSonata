// SysPara.cpp: implementation of the CSysPara class.
//
//////////////////////////////////////////////////////////////////////


#include "stdafx.h"

#include "SysPara.h"

#include "../../Include/globals.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSysPara::CSysPara()
{
	Init();
}

CSysPara::~CSysPara()
{

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CSysPara::LoadDefaultSysParameter
		\author   조철희
		\return   void
		\version  0.0.1
		\date     2008-01-24 19:29:08
		\warning
*/
void CSysPara::LoadDefaultSysParameter()
{


	_sp.cm.Rpc = RPC;	// 기준 펄스열의 펄스수 (Reference Pule Count)
	_sp.cm.Stb_Max_Miss = MAX_STB_MISS;
	_sp.cm.Jit_Max_Miss = MAX_JIT_MISS;

	// 에미터 병합의 시스템 변수
	// 각 밴드별 방위 에러 범위
#if defined(_POCKETSONATA_) || defined(_712_)
    float *pfRxDOAError = g_pTheSysConfig->GetAOAGroup();

    _sp.mg.aoa[0] = 0;
    _sp.mg.aoa[enPRC1] = ( unsigned int ) IMUL( 2 * IAOACNV( pfRxDOAError[0] ), 1.0 );
    _sp.mg.aoa[enPRC2] = ( unsigned int ) IMUL( 2 * IAOACNV( pfRxDOAError[1] ), 1.0 );
    _sp.mg.aoa[enPRC3] = ( unsigned int ) IMUL( 2 * IAOACNV( pfRxDOAError[2] ), 1.0 );
    _sp.mg.aoa[enPRC4] = ( unsigned int ) IMUL( 2 * IAOACNV( pfRxDOAError[3] ), 1.0 );
    _sp.mg.aoa[enPRC5] = ( unsigned int ) IMUL( 2 * IAOACNV( pfRxDOAError[4] ), 1.0 );

#else
    _sp.mg.aoa[0] = _spMgAoaEJ;
    _sp.mg.aoa[1] = _spMgAoaEJ;
    _sp.mg.aoa[2] = _spMgAoaEJ;
    _sp.mg.aoa[3] = _spMgAoaEJ;
    _sp.mg.aoa[4] = _spMgAoaEJ;
    _sp.mg.aoa[5] = _spMgAoaCD;

#endif

    _sp.np.Aoa_Hist_Thr = AOA_HIST_THR;	// 방위 히스토그램 범위 임계값 	// 00.02.09

	// 규칙성 PRI 일 경우의 에러 범위
	_sp.mg.fixpri = _spMgFixPri;

	// 지터율 비교할 때의 에러 범위
	_sp.mg.jtrper = _spMgJtrPer;

	// 지터 범위 체크할 때 사용하는 지터율
	_sp.mg.agiprimean = _spMgAgilePriMean;

	_sp.np.Freq_Hist_Thr = 0;

	_sp.mg.agifrqmean = _spMgAgileFrqMean;
	_sp.mg.agifrqin = _spMgAgileFrqIn;
	_sp.mg.agifrqout = _spMgAgileFrqOut;

	_sp.mg.fixfrq[0] = ( UINT ) _spMgFixFrqEJ;
	_sp.mg.fixfrq[1] = (UINT) _spMgFixFrqEJ;
	_sp.mg.fixfrq[2] = (UINT) _spMgFixFrqEJ;
	_sp.mg.fixfrq[3] = (UINT) _spMgFixFrqEJ;
	_sp.mg.fixfrq[4] = (UINT) _spMgFixFrqEJ;
	_sp.mg.fixfrq[5] = (UINT) _spMgFixFrqCD;

	_sp.mg.fixfrq_boundary[1] = (UINT) _spMgFixFrqBoundEJ;
	_sp.mg.fixfrq_boundary[2] = (UINT) _spMgFixFrqBoundEJ;
	_sp.mg.fixfrq_boundary[3] = (UINT) _spMgFixFrqBoundEJ;
	_sp.mg.fixfrq_boundary[4] = (UINT) _spMgFixFrqBoundEJ;
	_sp.mg.fixfrq_boundary[5] = (UINT) _spMgFixFrqBoundCD;

	_sp.mg.pw = (UINT) _spMgPW;

	_sp.mg.frqPrd = _spMgFrqPrd;

	_sp.mg.priPrd = _spMgPriPrd;

	_sp.mg.agipripat = _spMgAgilePriPat;

	// 최소 원형 스캔 주기 정의
	//_sp.sc.thtrkprd = _spThresholdOfTrkSig;

	// CW 최소 개수
	_sp.cm.uiCw_Min_Cnt = _spCWMinPulseCount;

    _spAnalMinPulseCount = _DEFAULT_ANAL_MINPULSECOUNT_;

}

//////////////////////////////////////////////////////////////////////////
/*! \brief    CSysPara::Init
		\author   조철희
		\return   void
		\version  0.0.1
		\date     2008-02-14 13:31:53
		\warning
*/
void CSysPara::Init()
{
	LoadDefaultSysParameter();

}

